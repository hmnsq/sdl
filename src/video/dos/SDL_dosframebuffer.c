/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DOSVESA

#ضمن "../../SDL_properties_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_dosframebuffer_c.h"
#ضمن "SDL_dosmodes.h"
#ضمن "SDL_dosmouse.h"
#ضمن "SDL_dosvideo.h"

#ضمن <pc.h>           // for inportb, outportb
#ضمن <sys/movedata.h> // for dosmemput (banked framebuffer writes)

// note that DOS_SURFACE's value is the same string that the dummy driver uses.
#define DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
تعريفنوع بنية DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool direct_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    صحيح vram_pitch;
    صحيح vram_w;
    صحيح vram_h;
    صحيح bpp; // bytes per pixel

    // dosmemput path state (use_dosmemput)
    Uint32 vram_phys;      // base address for dosmemput (e.g. 0xA0000)
    bool banked_multibank; // true if fb doesn't fit in one bank window
    Uint32 win_gran_bytes; // bank granularity in bytes
    Uint32 win_size_bytes; // bank window size in bytes
    Uint32 win_base;       // window base address (segment << 4)
    Uint32 win_func_ptr;   // real-mode far pointer to bank-switch function

    // nearptr path state (use_dosmemput == false)
    Uint8 *vram_ptr; // nearptr into VRAM (LFB)

    // Cached per-frame values (set at create time, avoid repeated lookups)
    Uint8 *pixels;      // == surface->pixels (stable after create)
    صحيح src_pitch;      // == surface->pitch
    Uint32 fb_size;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_match; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

ساكن DOSFramebufferState fb_state;

// Convert cursor to the current format.
ساكن SDL_Surface *GetConvertedCursorSurface(SDL_CursorData *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    𐡄𐡍 (!pal) {
        أرجع عدم;
    }

    Uint32 pal_version = pal ? pal->version : 0;

    𐡄𐡍 (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_version == pal_version) {
        أرجع curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = عدم;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    صحيح w = src->w;
    صحيح h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    𐡄𐡍 (!conv) {
        أرجع عدم;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    𐡄𐡍 (conv_pal) {
        SDL_SetPaletteColors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool used[256];
    SDL_zeroa(used);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, عدم, conv, عدم);
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    لكل (صحيح y = 0; y < h; y++) {
        ثابت Uint32 *srcrow = (ثابت Uint32 *)((ثابت Uint8 *)src->pixels + y * src->pitch);
        ثابت Uint8 *convrow = (ثابت Uint8 *)conv->pixels + y * conv->pitch;
        لكل (صحيح x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            𐡄𐡍 (srcA > 0) {
                used[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    لكل (صحيح i = 0; i < 256; i++) {
        𐡄𐡍 (!used[i]) {
            colorkey = (Uint32)i;
            اكسر;
        }
    }

    // Second pass: set transparent pixels to the colorkey index.
    لكل (صحيح y = 0; y < h; y++) {
        ثابت Uint32 *srcrow = (ثابت Uint32 *)((ثابت Uint8 *)src->pixels + y * src->pitch);
        Uint8 *convrow = (Uint8 *)conv->pixels + y * conv->pitch;
        لكل (صحيح x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            𐡄𐡍 (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_SetSurfaceColorKey(conv, true, colorkey);
    SDL_SetSurfaceBlendMode(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_version = pal_version;
    أرجع conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
فراغ DOSVESA_InvalidateCachedFramebuffer(فراغ)
{
    fb_state.direct_fb = false;
    fb_state.vram_ptr = عدم;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = عدم;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
ساكن SDL_Surface *CreateSystemSurface(SDL_VideoData *data, صحيح w, صحيح h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    𐡄𐡍 (!surface) {
        أرجع عدم;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    𐡄𐡍 (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        𐡄𐡍 (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            لكل (صحيح i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_SetPaletteColors(palette, black, 0, 256);
        }
        data->palette_version = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_INDEX, 0);
        لكل (صحيح i = 0; i < 256; i++) {
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
        }
    }

    أرجع surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
ساكن bool CreateNormalFramebuffer(SDL_VideoDevice *device, SDL_Window *window,
                                    SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_VideoData *data = device->internal;
    ثابت SDL_DisplayMode *mode = &data->current_mode;
    ثابت SDL_DisplayModeData *mdata = mode->internal;
    ثابت SDL_PixelFormat surface_format = mode->format;
    صحيح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
    𐡄𐡍 (!surface) {
        أرجع false;
    }

    SDL_Surface *lfb_surface = عدم;

    𐡄𐡍 (!data->banked_mode) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        صحيح back_page = data->page_flip_available ? (1 - data->current_page) : 0;
        فراغ *lfb_pixels = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
        lfb_surface = SDL_CreateSurfaceFrom(mode->w, mode->h, surface_format, lfb_pixels, mdata->pitch);
        𐡄𐡍 (!lfb_surface) {
            SDL_DestroySurface(surface);
            أرجع false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        𐡄𐡍 (src_palette) {
            SDL_SetSurfacePalette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    𐡄𐡍 (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    أرجع true;
}

bool DOSVESA_CreateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_zero(fb_state);

    SDL_VideoData *data = device->internal;
    ثابت SDL_DisplayMode *mode = &data->current_mode;
    ثابت SDL_DisplayModeData *mdata = mode->internal;
    ثابت SDL_PixelFormat surface_format = mode->format;
    صحيح w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    𐡄𐡍 (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_DIRECT_FRAMEBUFFER, false)) {
        صحيح vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        𐡄𐡍 (mdata->win_a_segment && mdata->win_size > 0 &&
            (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } وإلا 𐡄𐡍 (!data->banked_mode && data->mapping.size) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        𐡄𐡍 (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
            𐡄𐡍 (!surface) {
                أرجع false;
            }

            SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DOS_SURFACE, surface);

            fb_state.surface = surface;
            fb_state.direct_fb = true;
            fb_state.vram_pitch = vram_pitch;
            fb_state.vram_w = mdata->w;
            fb_state.vram_h = mdata->h;
            fb_state.bpp = SDL_BYTESPERPIXEL(surface_format);
            fb_state.pixels = (Uint8 *)surface->pixels;
            fb_state.src_pitch = surface->pitch;
            fb_state.fb_size = (Uint32)vram_pitch * mdata->h;
            fb_state.pitches_match = (surface->pitch == vram_pitch);

            // Prefer dosmemput via the banked VGA window (0xA0000). Real
            // hardware testing shows dosmemput is significantly faster
            // than nearptr writes to DPMI-mapped LFB, even with bank
            // switching overhead at higher resolutions.
            //
            // The banked window always maps to page 0, so page flipping is
            // not possible through this path. We accept tearing: the app
            // opted into the direct-FB hint for maximum throughput, and
            // games like Quake never used page flipping for their software
            // renderers anyway.
            𐡄𐡍 (mdata->win_a_segment && mdata->win_size > 0 &&
                (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_bytes = (Uint32)mdata->win_size * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = عدم;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_base = fb_state.vram_phys;
                fb_state.win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_size_bytes = win_bytes;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_size > win_bytes);
            } وإلا 𐡄𐡍 (!data->banked_mode && data->mapping.size) {
                // Fallback: nearptr to LFB.
                صحيح back_page = data->page_flip_available ? (1 - data->current_page) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } وإلا {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                أرجع CreateNormalFramebuffer(device, window, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            أرجع true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    أرجع CreateNormalFramebuffer(device, window, format, pixels, pitch);
}

bool DOSVESA_SetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, صحيح vsync)
{
    𐡄𐡍 (vsync < 0) {
        أرجع SDL_SetError("Unsupported vsync type");
    }
    SDL_WindowData *data = window->internal;
    data->framebuffer_vsync = vsync;
    أرجع true;
}

bool DOSVESA_GetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, صحيح *vsync)
{
    𐡄𐡍 (vsync) {
        SDL_WindowData *data = window->internal;
        *vsync = data->framebuffer_vsync;
    }
    أرجع true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE فراغ SwitchBank(صحيح bank, صحيح *current_bank, Uint32 win_func_ptr)
{
    𐡄𐡍 (bank == *current_bank) {
        أرجع;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    𐡄𐡍 (win_func_ptr) {
        regs.x.cs = (Uint16)(win_func_ptr >> 16);
        regs.x.ip = (Uint16)(win_func_ptr & 0xFFFF);
        __dpmi_simulate_real_mode_procedure_retf(&regs);
    } وإلا {
        regs.x.ax = 0x4F05;
        __dpmi_int(0x10, &regs);
    }
    *current_bank = bank;
}

// Copy a contiguous byte range from system RAM to VRAM through the banked
// window, switching banks as needed.
SDL_FORCE_INLINE فراغ BankedDosmemput(ثابت Uint8 *src, Uint32 total_bytes, Uint32 dst_offset,
                                      Uint32 win_gran_bytes, Uint32 win_size_bytes,
                                      Uint32 win_base, Uint32 win_func_ptr,
                                      صحيح *current_bank)
{
    Uint32 src_off = 0;
    طالما (total_bytes > 0) {
        صحيح bank = (صحيح)(dst_offset / win_gran_bytes);
        Uint32 off_in_win = dst_offset % win_gran_bytes;
        Uint32 avail = win_size_bytes - off_in_win;
        Uint32 n = total_bytes;
        𐡄𐡍 (n > avail) {
            n = avail;
        }
        SwitchBank(bank, current_bank, win_func_ptr);
        dosmemput(src + src_off, n, win_base + off_in_win);
        src_off += n;
        dst_offset += n;
        total_bytes -= n;
    }
}

// Bank-switched copy of a rectangular region from a system RAM surface to the
// VGA banked window.  `src_rect` is in source-surface coordinates; `dst_x` and
// `dst_y` give the top-left of the *surface's* position on screen (the
// centering offset).  The routine handles bank boundaries correctly even when a
// scanline spans two banks.
//
// `current_bank` is an in/out parameter so that consecutive calls (one per dirty
// rect) can avoid redundant bank switches when rects happen to fall in the same
// bank.  Initialise it to -1 before the first call.
ساكن فراغ BankedFramebufferCopyRect(ثابت SDL_DisplayModeData *mdata,
                                      ثابت SDL_Surface *src,
                                      ثابت SDL_Rect *src_rect,
                                      صحيح dst_x, صحيح dst_y,
                                      Uint32 win_gran_bytes,
                                      Uint32 win_size_bytes,
                                      Uint32 win_base,
                                      صحيح *current_bank,
                                      Uint32 win_func_ptr)
{
    ثابت Uint16 dst_pitch = mdata->pitch;
    ثابت صحيح bytes_per_pixel = SDL_BYTESPERPIXEL(src->format);
    ثابت صحيح row_bytes = src_rect->w * bytes_per_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    𐡄𐡍 (row_bytes == src->pitch && row_bytes == dst_pitch) {
        ثابت Uint8 *src_data = (ثابت Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_data, (Uint32)(row_bytes * src_rect->h), dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
        أرجع;
    }

    لكل (صحيح y = 0; y < src_rect->h; y++) {
        ثابت Uint8 *src_row = (ثابت Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_row, (Uint32)row_bytes, dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
    }
}

ساكن فراغ WaitForVBlank(فراغ)
{
    طالما (inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    طالما (!(inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

ساكن فراغ ProgramVGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_INDEX, 0);
    لكل (صحيح i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_DATA, palette->colors[i].r >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].g >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_UpdateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_VideoData *vdata = device->internal;

    // ===================================================================
    //  Direct-FB fast path: copy system-RAM to VRAM, program palette,
    //  optionally page-flip. No cursor compositing, no SDL_BlitSurface.
    //
    //  This path prefers banked dosmemput (through the VGA window at
    //  0xA0000) over nearptr writes to the DPMI-mapped LFB. Real
    //  hardware testing on multiple NVIDIA cards showed dosmemput is
    //  significantly faster, even with bank-switching overhead at
    //  higher resolutions. The nearptr LFB path is only used as a
    // fallback if no usable banked window is available.
    // ===================================================================
    𐡄𐡍 (fb_state.direct_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        𐡄𐡍 (window->surface) {
            SDL_Palette *pal = window->surface->palette;
            𐡄𐡍 (pal && pal->version != vdata->palette_version) {
                vdata->palette_version = pal->version;
                ProgramVGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        𐡄𐡍 (numrects <= 0) {
            أرجع true;
        }

        𐡄𐡍 (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            ثابت صحيح src_pitch = fb_state.src_pitch;
            ثابت صحيح dst_pitch = fb_state.vram_pitch;
            ثابت Uint8 *pixels = fb_state.pixels;

            𐡄𐡍 (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                𐡄𐡍 (fb_state.pitches_match) {
                    dosmemput(pixels, fb_state.fb_size, fb_state.vram_phys);
                } وإلا {
                    لكل (صحيح i = 0; i < numrects; i++) {
                        صحيح rx = rects[i].x, ry = rects[i].y;
                        صحيح rw = rects[i].w, rh = rects[i].h;
                        𐡄𐡍 (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        𐡄𐡍 (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        𐡄𐡍 (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        𐡄𐡍 (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        𐡄𐡍 (rw <= 0 || rh <= 0) {
                            استمر;
                        }
                        ثابت صحيح bx = rx * fb_state.bpp;
                        ثابت صحيح bw = rw * fb_state.bpp;
                        ثابت Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        لكل (صحيح row = 0; row < rh; row++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } وإلا {
                // Multi-bank: bank-switch as needed.
                ثابت Uint32 gran = fb_state.win_gran_bytes;
                ثابت Uint32 wsize = fb_state.win_size_bytes;
                ثابت Uint32 wbase = fb_state.win_base;
                ثابت Uint32 wfunc = fb_state.win_func_ptr;
                صحيح current_bank = -1;

                𐡄𐡍 (fb_state.pitches_match) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_size, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } وإلا {
                    // Per-rect with bank switching.
                    لكل (صحيح i = 0; i < numrects; i++) {
                        صحيح rx = rects[i].x, ry = rects[i].y;
                        صحيح rw = rects[i].w, rh = rects[i].h;
                        𐡄𐡍 (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        𐡄𐡍 (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        𐡄𐡍 (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        𐡄𐡍 (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        𐡄𐡍 (rw <= 0 || rh <= 0) {
                            استمر;
                        }
                        ثابت صحيح bx = rx * fb_state.bpp;
                        ثابت صحيح bw = rw * fb_state.bpp;

                        لكل (صحيح row = 0; row < rh; row++) {
                            ثابت Uint8 *sp = pixels + (ry + row) * src_pitch + bx;
                            Uint32 dst_offset = (Uint32)(ry + row) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_offset,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } وإلا {
            // nearptr path (LFB fallback)
            𐡄𐡍 (fb_state.pitches_match) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_size);
            } وإلا {
                ثابت صحيح bpp = fb_state.bpp;
                ثابت صحيح src_pitch = fb_state.src_pitch;
                ثابت صحيح dst_pitch = fb_state.vram_pitch;
                ثابت Uint8 *pixels = fb_state.pixels;

                لكل (صحيح i = 0; i < numrects; i++) {
                    صحيح rx = rects[i].x, ry = rects[i].y;
                    صحيح rw = rects[i].w, rh = rects[i].h;
                    𐡄𐡍 (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    𐡄𐡍 (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    𐡄𐡍 (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    𐡄𐡍 (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    𐡄𐡍 (rw <= 0 || rh <= 0) {
                        استمر;
                    }
                    ثابت صحيح bw = rw * bpp;
                    ثابت Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    لكل (صحيح row = 0; row < rh; row++) {
                        SDL_memcpy(dp, sp, bw);
                        sp += src_pitch;
                        dp += dst_pitch;
                    }
                }
            }
        }

        // Page flipping is only used with the nearptr LFB path. The banked
        // dosmemput path always writes to page 0 (the visible page) and
        // accepts tearing, avoiding a BIOS call.
        𐡄𐡍 (!fb_state.use_dosmemput && vdata->page_flip_available) {
            ثابت SDL_DisplayModeData *mdata = vdata->current_mode.internal;
            صحيح back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = first_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_page = back_page;

            صحيح new_back = 1 - vdata->current_page;
            fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        }

        أرجع true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    𐡄𐡍 (!src) {
        src = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DOS_SURFACE, عدم);
    }
    𐡄𐡍 (!src) {
        أرجع SDL_SetError("Couldn't find DOS surface for window");
    }

    ثابت SDL_DisplayModeData *mdata = vdata->current_mode.internal;
    SDL_WindowData *windata = window->internal;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = عدم;
    bool dac_needs_update = false;

    𐡄𐡍 (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = window->surface ? SDL_GetSurfacePalette(window->surface) : عدم;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        𐡄𐡍 (win_palette && src_palette && win_palette != src_palette &&
            win_palette->version != src_palette->version) {
            SDL_SetPaletteColors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            𐡄𐡍 (!vdata->banked_mode && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                𐡄𐡍 (dst_palette && dst_palette != src_palette) {
                    SDL_SetPaletteColors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        𐡄𐡍 (dac_palette && dac_palette->version != vdata->palette_version) {
            dac_needs_update = true;
        }
    }

    𐡄𐡍 (vdata->banked_mode) {
        // --- Banked framebuffer path (dirty-rect aware) ---
        // We composite the cursor onto the source surface (in system RAM),
        // then bank-copy only the dirty rectangles to the VGA window.  We
        // need to undo the cursor composite afterwards so the app's surface
        // isn't permanently modified.

        ثابت صحيح dst_x = ((صحيح)mdata->w - src->w) / 2;
        ثابت صحيح dst_y = ((صحيح)mdata->h - src->h) / 2;

        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = عدم;
        SDL_Rect cursorrect;
        SDL_Rect cursor_clipped; // cursorrect clipped to src bounds
        SDL_Surface *cursor_save = عدم;
        bool have_cursor_rect = false;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : عدم;
        𐡄𐡍 (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        𐡄𐡍 (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            𐡄𐡍 (cursor) {
                cursorrect.x = SDL_clamp((صحيح)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = SDL_clamp((صحيح)mouse->y, 0, window->h) - cur->internal->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                𐡄𐡍 (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                𐡄𐡍 (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                𐡄𐡍 (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                𐡄𐡍 (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                𐡄𐡍 (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    𐡄𐡍 (cursor_save) {
                        𐡄𐡍 (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            𐡄𐡍 (sp) {
                                SDL_SetSurfacePalette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, عدم);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, عدم, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        ثابت صحيح vsync_interval = windata->framebuffer_vsync;
        𐡄𐡍 (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        𐡄𐡍 (dac_needs_update) {
            vdata->palette_version = dac_palette->version;
            ProgramVGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        ثابت Uint32 win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
        ثابت Uint32 win_size_bytes = (Uint32)mdata->win_size * 1024;
        ثابت Uint32 win_base = (Uint32)mdata->win_a_segment << 4;
        صحيح current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        لكل (صحيح r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            𐡄𐡍 (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            𐡄𐡍 (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            𐡄𐡍 (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            𐡄𐡍 (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            𐡄𐡍 (rect.w <= 0 || rect.h <= 0) {
                استمر;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            𐡄𐡍 (have_cursor_rect && !cursor_covered) {
                𐡄𐡍 (rect.x <= cursor_clipped.x &&
                    rect.y <= cursor_clipped.y &&
                    rect.x + rect.w >= cursor_clipped.x + cursor_clipped.w &&
                    rect.y + rect.h >= cursor_clipped.y + cursor_clipped.h) {
                    cursor_covered = true;
                }
            }

            BankedFramebufferCopyRect(mdata, src, &rect, dst_x, dst_y,
                                      win_gran_bytes, win_size_bytes, win_base,
                                      &current_bank, mdata->win_func_ptr);
        }

        // If no dirty rect covered the cursor, copy the cursor region separately.
        𐡄𐡍 (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_bytes, win_size_bytes, win_base,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        𐡄𐡍 (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, عدم, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } وإلا {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        𐡄𐡍 (!dst) {
            أرجع SDL_SetError("Couldn't find VESA linear framebuffer surface for window");
        }

        ثابت SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = عدم;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : عدم;
        𐡄𐡍 (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        𐡄𐡍 (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            𐡄𐡍 (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((صحيح)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((صحيح)mouse->y, 0, window->h) - cur->internal->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        𐡄𐡍 (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            ثابت Uint8 *sp = (ثابت Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            𐡄𐡍 (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } وإلا {
                لكل (صحيح row = 0; row < dstrect.h; row++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } وإلا {
            // Blit to the back page (or the only page, if no page-flipping)
            𐡄𐡍 (!SDL_BlitSurface(src, عدم, dst, &dstrect)) {
                أرجع false;
            }
        }

        𐡄𐡍 (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, dst);
            𐡄𐡍 (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, عدم, dst, &cursorrect)) {
                أرجع false;
            }
        }

        𐡄𐡍 (vdata->page_flip_available) {
            // Page-flip with optional vsync.
            ثابت صحيح vsync_interval = windata->framebuffer_vsync;
            صحيح back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            𐡄𐡍 (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            𐡄𐡍 (dac_needs_update) {
                vdata->palette_version = dac_palette->version;
                ProgramVGADAC(dac_palette);
            }

            // Flip: make the back page (which we just drew to) the visible page.
            // Always use subfunction 0x0080 (set display start, don't wait) —
            // vsync is controlled by our manual vblank wait above.
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0; // first pixel in scan line
            regs.x.dx = first_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_page = back_page;

            // Update LFB surface to point at the new back page (the old front page)
            صحيح new_back = 1 - vdata->current_page;
            dst->pixels = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        } وإلا {
            // No page-flipping: wait for vsync, then update DAC atomically
            ثابت صحيح vsync_interval = windata->framebuffer_vsync;
            𐡄𐡍 (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            𐡄𐡍 (dac_needs_update) {
                vdata->palette_version = dac_palette->version;
                ProgramVGADAC(dac_palette);
            }
        }
    }

    أرجع true;
}

فراغ DOSVESA_DestroyWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (فراغ)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_GetWindowProperties(window), DOS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_DOSVESA

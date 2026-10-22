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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DOSVESA

#अन्तर्भाव "../../SDL_properties_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_dosframebuffer_c.h"
#अन्तर्भाव "SDL_dosmodes.h"
#अन्तर्भाव "SDL_dosmouse.h"
#अन्तर्भाव "SDL_dosvideo.h"

#अन्तर्भाव <pc.h>           // for inportb, outportb
#अन्तर्भाव <sys/movedata.h> // for dosmemput (banked framebuffer writes)

// note that DOS_SURFACE's value is the same string that the dummy driver uses.
#define DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
प्रकारनिर्देश संरचना DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool direct_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    पूर्णाङ्क vram_pitch;
    पूर्णाङ्क vram_w;
    पूर्णाङ्क vram_h;
    पूर्णाङ्क bpp; // bytes per pixel

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
    पूर्णाङ्क src_pitch;      // == surface->pitch
    Uint32 fb_size;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_match; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

स्थिर DOSFramebufferState fb_state;

// Convert cursor to the current format.
स्थिर SDL_Surface *GetConvertedCursorSurface(SDL_CursorData *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    यदि (!pal) {
        प्रत्यागम रिक्त;
    }

    Uint32 pal_version = pal ? pal->version : 0;

    यदि (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_version == pal_version) {
        प्रत्यागम curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = रिक्त;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    पूर्णाङ्क w = src->w;
    पूर्णाङ्क h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    यदि (!conv) {
        प्रत्यागम रिक्त;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    यदि (conv_pal) {
        SDL_SetPaletteColors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool used[256];
    SDL_zeroa(used);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, रिक्त, conv, रिक्त);
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    प्रति (पूर्णाङ्क y = 0; y < h; y++) {
        ध्रुव Uint32 *srcrow = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src->pixels + y * src->pitch);
        ध्रुव Uint8 *convrow = (ध्रुव Uint8 *)conv->pixels + y * conv->pitch;
        प्रति (पूर्णाङ्क x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            यदि (srcA > 0) {
                used[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    प्रति (पूर्णाङ्क i = 0; i < 256; i++) {
        यदि (!used[i]) {
            colorkey = (Uint32)i;
            भङ्ग;
        }
    }

    // Second pass: set transparent pixels to the colorkey index.
    प्रति (पूर्णाङ्क y = 0; y < h; y++) {
        ध्रुव Uint32 *srcrow = (ध्रुव Uint32 *)((ध्रुव Uint8 *)src->pixels + y * src->pitch);
        Uint8 *convrow = (Uint8 *)conv->pixels + y * conv->pitch;
        प्रति (पूर्णाङ्क x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            यदि (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_Set_Surface_Color_कुंजी(conv, true, colorkey);
    SDL_SetSurfaceBlendMode(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_version = pal_version;
    प्रत्यागम conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
शून्य DOSVESA_InvalidateCachedFramebuffer(शून्य)
{
    fb_state.direct_fb = false;
    fb_state.vram_ptr = रिक्त;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = रिक्त;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
स्थिर SDL_Surface *CreateSystemSurface(SDL_VideoData *data, पूर्णाङ्क w, पूर्णाङ्क h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    यदि (!surface) {
        प्रत्यागम रिक्त;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    यदि (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        यदि (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            प्रति (पूर्णाङ्क i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_SetPaletteColors(palette, black, 0, 256);
        }
        data->palette_version = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_INDEX, 0);
        प्रति (पूर्णाङ्क i = 0; i < 256; i++) {
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
        }
    }

    प्रत्यागम surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
स्थिर bool CreateNormalFramebuffer(SDL_VideoDevice *device, SDL_Window *window,
                                    SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_VideoData *data = device->internal;
    ध्रुव SDL_DisplayMode *mode = &data->current_mode;
    ध्रुव SDL_DisplayModeData *mdata = mode->internal;
    ध्रुव SDL_PixelFormat surface_format = mode->format;
    पूर्णाङ्क w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
    यदि (!surface) {
        प्रत्यागम false;
    }

    SDL_Surface *lfb_surface = रिक्त;

    यदि (!data->banked_mode) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        पूर्णाङ्क back_page = data->page_flip_available ? (1 - data->current_page) : 0;
        शून्य *lfb_pixels = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
        lfb_surface = SDL_CreateSurfaceFrom(mode->w, mode->h, surface_format, lfb_pixels, mdata->pitch);
        यदि (!lfb_surface) {
            SDL_DestroySurface(surface);
            प्रत्यागम false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        यदि (src_palette) {
            SDL_SetSurfacePalette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    यदि (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    प्रत्यागम true;
}

bool DOSVESA_CreateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_zero(fb_state);

    SDL_VideoData *data = device->internal;
    ध्रुव SDL_DisplayMode *mode = &data->current_mode;
    ध्रुव SDL_DisplayModeData *mdata = mode->internal;
    ध्रुव SDL_PixelFormat surface_format = mode->format;
    पूर्णाङ्क w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    यदि (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_DIRECT_FRAMEBUFFER, false)) {
        पूर्णाङ्क vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        यदि (mdata->win_a_segment && mdata->win_size > 0 &&
            (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } अन्यथा यदि (!data->banked_mode && data->mapping.size) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        यदि (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
            यदि (!surface) {
                प्रत्यागम false;
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
            यदि (mdata->win_a_segment && mdata->win_size > 0 &&
                (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_bytes = (Uint32)mdata->win_size * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = रिक्त;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_base = fb_state.vram_phys;
                fb_state.win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_size_bytes = win_bytes;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_size > win_bytes);
            } अन्यथा यदि (!data->banked_mode && data->mapping.size) {
                // Fallback: nearptr to LFB.
                पूर्णाङ्क back_page = data->page_flip_available ? (1 - data->current_page) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } अन्यथा {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                प्रत्यागम CreateNormalFramebuffer(device, window, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            प्रत्यागम true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    प्रत्यागम CreateNormalFramebuffer(device, window, format, pixels, pitch);
}

bool DOSVESA_SetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, पूर्णाङ्क vsync)
{
    यदि (vsync < 0) {
        प्रत्यागम SDL_SetError("Unsupported vsync type");
    }
    SDL_WindowData *data = window->internal;
    data->framebuffer_vsync = vsync;
    प्रत्यागम true;
}

bool DOSVESA_GetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, पूर्णाङ्क *vsync)
{
    यदि (vsync) {
        SDL_WindowData *data = window->internal;
        *vsync = data->framebuffer_vsync;
    }
    प्रत्यागम true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE शून्य SwitchBank(पूर्णाङ्क bank, पूर्णाङ्क *current_bank, Uint32 win_func_ptr)
{
    यदि (bank == *current_bank) {
        प्रत्यागम;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    यदि (win_func_ptr) {
        regs.x.cs = (Uint16)(win_func_ptr >> 16);
        regs.x.ip = (Uint16)(win_func_ptr & 0xFFFF);
        __dpmi_simulate_real_mode_procedure_retf(&regs);
    } अन्यथा {
        regs.x.ax = 0x4F05;
        __dpmi_int(0x10, &regs);
    }
    *current_bank = bank;
}

// Copy a contiguous byte range from system RAM to VRAM through the banked
// window, switching banks as needed.
SDL_FORCE_INLINE शून्य BankedDosmemput(ध्रुव Uint8 *src, Uint32 total_bytes, Uint32 dst_offset,
                                      Uint32 win_gran_bytes, Uint32 win_size_bytes,
                                      Uint32 win_base, Uint32 win_func_ptr,
                                      पूर्णाङ्क *current_bank)
{
    Uint32 src_off = 0;
    यावत् (total_bytes > 0) {
        पूर्णाङ्क bank = (पूर्णाङ्क)(dst_offset / win_gran_bytes);
        Uint32 off_in_win = dst_offset % win_gran_bytes;
        Uint32 avail = win_size_bytes - off_in_win;
        Uint32 n = total_bytes;
        यदि (n > avail) {
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
स्थिर शून्य BankedFramebufferCopyRect(ध्रुव SDL_DisplayModeData *mdata,
                                      ध्रुव SDL_Surface *src,
                                      ध्रुव SDL_Rect *src_rect,
                                      पूर्णाङ्क dst_x, पूर्णाङ्क dst_y,
                                      Uint32 win_gran_bytes,
                                      Uint32 win_size_bytes,
                                      Uint32 win_base,
                                      पूर्णाङ्क *current_bank,
                                      Uint32 win_func_ptr)
{
    ध्रुव Uint16 dst_pitch = mdata->pitch;
    ध्रुव पूर्णाङ्क bytes_per_pixel = SDL_BYTESPERPIXEL(src->format);
    ध्रुव पूर्णाङ्क row_bytes = src_rect->w * bytes_per_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    यदि (row_bytes == src->pitch && row_bytes == dst_pitch) {
        ध्रुव Uint8 *src_data = (ध्रुव Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_data, (Uint32)(row_bytes * src_rect->h), dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
        प्रत्यागम;
    }

    प्रति (पूर्णाङ्क y = 0; y < src_rect->h; y++) {
        ध्रुव Uint8 *src_row = (ध्रुव Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_row, (Uint32)row_bytes, dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
    }
}

स्थिर शून्य WaitForVBlank(शून्य)
{
    यावत् (inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    यावत् (!(inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

स्थिर शून्य ProgramVGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_INDEX, 0);
    प्रति (पूर्णाङ्क i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_DATA, palette->colors[i].r >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].g >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_UpdateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
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
    यदि (fb_state.direct_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        यदि (window->surface) {
            SDL_Palette *pal = window->surface->palette;
            यदि (pal && pal->version != vdata->palette_version) {
                vdata->palette_version = pal->version;
                ProgramVGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        यदि (numrects <= 0) {
            प्रत्यागम true;
        }

        यदि (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            ध्रुव पूर्णाङ्क src_pitch = fb_state.src_pitch;
            ध्रुव पूर्णाङ्क dst_pitch = fb_state.vram_pitch;
            ध्रुव Uint8 *pixels = fb_state.pixels;

            यदि (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                यदि (fb_state.pitches_match) {
                    dosmemput(pixels, fb_state.fb_size, fb_state.vram_phys);
                } अन्यथा {
                    प्रति (पूर्णाङ्क i = 0; i < numrects; i++) {
                        पूर्णाङ्क rx = rects[i].x, ry = rects[i].y;
                        पूर्णाङ्क rw = rects[i].w, rh = rects[i].h;
                        यदि (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        यदि (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        यदि (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        यदि (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        यदि (rw <= 0 || rh <= 0) {
                            अनुवर्त;
                        }
                        ध्रुव पूर्णाङ्क bx = rx * fb_state.bpp;
                        ध्रुव पूर्णाङ्क bw = rw * fb_state.bpp;
                        ध्रुव Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        प्रति (पूर्णाङ्क row = 0; row < rh; row++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } अन्यथा {
                // Multi-bank: bank-switch as needed.
                ध्रुव Uint32 gran = fb_state.win_gran_bytes;
                ध्रुव Uint32 wsize = fb_state.win_size_bytes;
                ध्रुव Uint32 wbase = fb_state.win_base;
                ध्रुव Uint32 wfunc = fb_state.win_func_ptr;
                पूर्णाङ्क current_bank = -1;

                यदि (fb_state.pitches_match) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_size, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } अन्यथा {
                    // Per-rect with bank switching.
                    प्रति (पूर्णाङ्क i = 0; i < numrects; i++) {
                        पूर्णाङ्क rx = rects[i].x, ry = rects[i].y;
                        पूर्णाङ्क rw = rects[i].w, rh = rects[i].h;
                        यदि (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        यदि (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        यदि (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        यदि (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        यदि (rw <= 0 || rh <= 0) {
                            अनुवर्त;
                        }
                        ध्रुव पूर्णाङ्क bx = rx * fb_state.bpp;
                        ध्रुव पूर्णाङ्क bw = rw * fb_state.bpp;

                        प्रति (पूर्णाङ्क row = 0; row < rh; row++) {
                            ध्रुव Uint8 *sp = pixels + (ry + row) * src_pitch + bx;
                            Uint32 dst_offset = (Uint32)(ry + row) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_offset,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } अन्यथा {
            // nearptr path (LFB fallback)
            यदि (fb_state.pitches_match) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_size);
            } अन्यथा {
                ध्रुव पूर्णाङ्क bpp = fb_state.bpp;
                ध्रुव पूर्णाङ्क src_pitch = fb_state.src_pitch;
                ध्रुव पूर्णाङ्क dst_pitch = fb_state.vram_pitch;
                ध्रुव Uint8 *pixels = fb_state.pixels;

                प्रति (पूर्णाङ्क i = 0; i < numrects; i++) {
                    पूर्णाङ्क rx = rects[i].x, ry = rects[i].y;
                    पूर्णाङ्क rw = rects[i].w, rh = rects[i].h;
                    यदि (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    यदि (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    यदि (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    यदि (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    यदि (rw <= 0 || rh <= 0) {
                        अनुवर्त;
                    }
                    ध्रुव पूर्णाङ्क bw = rw * bpp;
                    ध्रुव Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    प्रति (पूर्णाङ्क row = 0; row < rh; row++) {
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
        यदि (!fb_state.use_dosmemput && vdata->page_flip_available) {
            ध्रुव SDL_DisplayModeData *mdata = vdata->current_mode.internal;
            पूर्णाङ्क back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = first_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_page = back_page;

            पूर्णाङ्क new_back = 1 - vdata->current_page;
            fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        }

        प्रत्यागम true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    यदि (!src) {
        src = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DOS_SURFACE, रिक्त);
    }
    यदि (!src) {
        प्रत्यागम SDL_SetError("Couldn't find DOS surface for window");
    }

    ध्रुव SDL_DisplayModeData *mdata = vdata->current_mode.internal;
    SDL_WindowData *windata = window->internal;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = रिक्त;
    bool dac_needs_update = false;

    यदि (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = window->surface ? SDL_GetSurfacePalette(window->surface) : रिक्त;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        यदि (win_palette && src_palette && win_palette != src_palette &&
            win_palette->version != src_palette->version) {
            SDL_SetPaletteColors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            यदि (!vdata->banked_mode && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                यदि (dst_palette && dst_palette != src_palette) {
                    SDL_SetPaletteColors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        यदि (dac_palette && dac_palette->version != vdata->palette_version) {
            dac_needs_update = true;
        }
    }

    यदि (vdata->banked_mode) {
        // --- Banked framebuffer path (dirty-rect aware) ---
        // We composite the cursor onto the source surface (in system RAM),
        // then bank-copy only the dirty rectangles to the VGA window.  We
        // need to undo the cursor composite afterwards so the app's surface
        // isn't permanently modified.

        ध्रुव पूर्णाङ्क dst_x = ((पूर्णाङ्क)mdata->w - src->w) / 2;
        ध्रुव पूर्णाङ्क dst_y = ((पूर्णाङ्क)mdata->h - src->h) / 2;

        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = रिक्त;
        SDL_Rect cursorrect;
        SDL_Rect cursor_clipped; // cursorrect clipped to src bounds
        SDL_Surface *cursor_save = रिक्त;
        bool have_cursor_rect = false;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : रिक्त;
        यदि (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        यदि (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            यदि (cursor) {
                cursorrect.x = SDL_clamp((पूर्णाङ्क)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = SDL_clamp((पूर्णाङ्क)mouse->y, 0, window->h) - cur->internal->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                यदि (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                यदि (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                यदि (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                यदि (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                यदि (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    यदि (cursor_save) {
                        यदि (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            यदि (sp) {
                                SDL_SetSurfacePalette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, रिक्त);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, रिक्त, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        ध्रुव पूर्णाङ्क vsync_interval = windata->framebuffer_vsync;
        यदि (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        यदि (dac_needs_update) {
            vdata->palette_version = dac_palette->version;
            ProgramVGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        ध्रुव Uint32 win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
        ध्रुव Uint32 win_size_bytes = (Uint32)mdata->win_size * 1024;
        ध्रुव Uint32 win_base = (Uint32)mdata->win_a_segment << 4;
        पूर्णाङ्क current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        प्रति (पूर्णाङ्क r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            यदि (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            यदि (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            यदि (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            यदि (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            यदि (rect.w <= 0 || rect.h <= 0) {
                अनुवर्त;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            यदि (have_cursor_rect && !cursor_covered) {
                यदि (rect.x <= cursor_clipped.x &&
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
        यदि (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_bytes, win_size_bytes, win_base,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        यदि (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, रिक्त, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } अन्यथा {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        यदि (!dst) {
            प्रत्यागम SDL_SetError("Couldn't find VESA linear framebuffer surface for window");
        }

        ध्रुव SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = रिक्त;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : रिक्त;
        यदि (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        यदि (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            यदि (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((पूर्णाङ्क)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((पूर्णाङ्क)mouse->y, 0, window->h) - cur->internal->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        यदि (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            ध्रुव Uint8 *sp = (ध्रुव Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            यदि (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } अन्यथा {
                प्रति (पूर्णाङ्क row = 0; row < dstrect.h; row++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } अन्यथा {
            // Blit to the back page (or the only page, if no page-flipping)
            यदि (!SDL_BlitSurface(src, रिक्त, dst, &dstrect)) {
                प्रत्यागम false;
            }
        }

        यदि (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, dst);
            यदि (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, रिक्त, dst, &cursorrect)) {
                प्रत्यागम false;
            }
        }

        यदि (vdata->page_flip_available) {
            // Page-flip with optional vsync.
            ध्रुव पूर्णाङ्क vsync_interval = windata->framebuffer_vsync;
            पूर्णाङ्क back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            यदि (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            यदि (dac_needs_update) {
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
            पूर्णाङ्क new_back = 1 - vdata->current_page;
            dst->pixels = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        } अन्यथा {
            // No page-flipping: wait for vsync, then update DAC atomically
            ध्रुव पूर्णाङ्क vsync_interval = windata->framebuffer_vsync;
            यदि (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            यदि (dac_needs_update) {
                vdata->palette_version = dac_palette->version;
                ProgramVGADAC(dac_palette);
            }
        }
    }

    प्रत्यागम true;
}

शून्य DOSVESA_DestroyWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (शून्य)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_GetWindowProperties(window), DOS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_DOSVESA

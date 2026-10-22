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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DOSVESA

#અન્તર્ભાવ "../../SDL_properties_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_dosframebuffer_c.h"
#અન્તર્ભાવ "SDL_dosmodes.h"
#અન્તર્ભાવ "SDL_dosmouse.h"
#અન્તર્ભાવ "SDL_dosvideo.h"

#અન્તર્ભાવ <pc.h>           // for inportb, outportb
#અન્તર્ભાવ <sys/movedata.h> // for dosmemput (banked framebuffer writes)

// note that DOS_SURFACE's value is the same string that the dummy driver uses.
#define DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
પ્રકારવ્યાખ્યા સંરચના DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool direct_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    પૂર્ણાંક vram_pitch;
    પૂર્ણાંક vram_w;
    પૂર્ણાંક vram_h;
    પૂર્ણાંક bpp; // bytes per pixel

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
    પૂર્ણાંક src_pitch;      // == surface->pitch
    Uint32 fb_size;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_match; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

સ્થિર DOSFramebufferState fb_state;

// Convert cursor to the current format.
સ્થિર SDL_Surface *GetConvertedCursorSurface(SDL_CursorData *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    જો (!pal) {
        પાછા ખાલી;
    }

    Uint32 pal_version = pal ? pal->version : 0;

    જો (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_version == pal_version) {
        પાછા curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = ખાલી;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    પૂર્ણાંક w = src->w;
    પૂર્ણાંક h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    જો (!conv) {
        પાછા ખાલી;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    જો (conv_pal) {
        SDL_SetPaletteColors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool used[256];
    SDL_zeroa(used);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, ખાલી, conv, ખાલી);
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    માટે (પૂર્ણાંક y = 0; y < h; y++) {
        અચલ Uint32 *srcrow = (અચલ Uint32 *)((અચલ Uint8 *)src->pixels + y * src->pitch);
        અચલ Uint8 *convrow = (અચલ Uint8 *)conv->pixels + y * conv->pitch;
        માટે (પૂર્ણાંક x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            જો (srcA > 0) {
                used[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    માટે (પૂર્ણાંક i = 0; i < 256; i++) {
        જો (!used[i]) {
            colorkey = (Uint32)i;
            તોડો;
        }
    }

    // Second pass: set transparent pixels to the colorkey index.
    માટે (પૂર્ણાંક y = 0; y < h; y++) {
        અચલ Uint32 *srcrow = (અચલ Uint32 *)((અચલ Uint8 *)src->pixels + y * src->pitch);
        Uint8 *convrow = (Uint8 *)conv->pixels + y * conv->pitch;
        માટે (પૂર્ણાંક x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            જો (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_Set_Surface_Color_ચાવી(conv, true, colorkey);
    SDL_SetSurfaceBlendMode(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_version = pal_version;
    પાછા conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
શૂન્ય DOSVESA_InvalidateCachedFramebuffer(શૂન્ય)
{
    fb_state.direct_fb = false;
    fb_state.vram_ptr = ખાલી;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = ખાલી;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
સ્થિર SDL_Surface *CreateSystemSurface(SDL_VideoData *data, પૂર્ણાંક w, પૂર્ણાંક h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    જો (!surface) {
        પાછા ખાલી;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    જો (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        જો (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            માટે (પૂર્ણાંક i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_SetPaletteColors(palette, black, 0, 256);
        }
        data->palette_version = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_INDEX, 0);
        માટે (પૂર્ણાંક i = 0; i < 256; i++) {
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
            outportb(VGA_DAC_DATA, 0);
        }
    }

    પાછા surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
સ્થિર bool CreateNormalFramebuffer(SDL_VideoDevice *device, SDL_Window *window,
                                    SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_VideoData *data = device->internal;
    અચલ SDL_DisplayMode *mode = &data->current_mode;
    અચલ SDL_DisplayModeData *mdata = mode->internal;
    અચલ SDL_PixelFormat surface_format = mode->format;
    પૂર્ણાંક w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
    જો (!surface) {
        પાછા false;
    }

    SDL_Surface *lfb_surface = ખાલી;

    જો (!data->banked_mode) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        પૂર્ણાંક back_page = data->page_flip_available ? (1 - data->current_page) : 0;
        શૂન્ય *lfb_pixels = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
        lfb_surface = SDL_CreateSurfaceFrom(mode->w, mode->h, surface_format, lfb_pixels, mdata->pitch);
        જો (!lfb_surface) {
            SDL_DestroySurface(surface);
            પાછા false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        જો (src_palette) {
            SDL_SetSurfacePalette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    જો (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_SetSurfaceProperty(SDL_GetWindowProperties(window), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    પાછા true;
}

bool DOSVESA_CreateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_zero(fb_state);

    SDL_VideoData *data = device->internal;
    અચલ SDL_DisplayMode *mode = &data->current_mode;
    અચલ SDL_DisplayModeData *mdata = mode->internal;
    અચલ SDL_PixelFormat surface_format = mode->format;
    પૂર્ણાંક w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    જો (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_DIRECT_FRAMEBUFFER, false)) {
        પૂર્ણાંક vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        જો (mdata->win_a_segment && mdata->win_size > 0 &&
            (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } નહીંતર જો (!data->banked_mode && data->mapping.size) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        જો (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(data, w, h, surface_format);
            જો (!surface) {
                પાછા false;
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
            જો (mdata->win_a_segment && mdata->win_size > 0 &&
                (mdata->win_a_attributes & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_bytes = (Uint32)mdata->win_size * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = ખાલી;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_base = fb_state.vram_phys;
                fb_state.win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_size_bytes = win_bytes;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_size > win_bytes);
            } નહીંતર જો (!data->banked_mode && data->mapping.size) {
                // Fallback: nearptr to LFB.
                પૂર્ણાંક back_page = data->page_flip_available ? (1 - data->current_page) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(data->mapping.address) + data->page_offset[back_page];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } નહીંતર {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                પાછા CreateNormalFramebuffer(device, window, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            પાછા true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    પાછા CreateNormalFramebuffer(device, window, format, pixels, pitch);
}

bool DOSVESA_SetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, પૂર્ણાંક vsync)
{
    જો (vsync < 0) {
        પાછા SDL_SetError("Unsupported vsync type");
    }
    SDL_WindowData *data = window->internal;
    data->framebuffer_vsync = vsync;
    પાછા true;
}

bool DOSVESA_GetWindowFramebufferVSync(SDL_VideoDevice *device, SDL_Window *window, પૂર્ણાંક *vsync)
{
    જો (vsync) {
        SDL_WindowData *data = window->internal;
        *vsync = data->framebuffer_vsync;
    }
    પાછા true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE શૂન્ય SwitchBank(પૂર્ણાંક bank, પૂર્ણાંક *current_bank, Uint32 win_func_ptr)
{
    જો (bank == *current_bank) {
        પાછા;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    જો (win_func_ptr) {
        regs.x.cs = (Uint16)(win_func_ptr >> 16);
        regs.x.ip = (Uint16)(win_func_ptr & 0xFFFF);
        __dpmi_simulate_real_mode_procedure_retf(&regs);
    } નહીંતર {
        regs.x.ax = 0x4F05;
        __dpmi_int(0x10, &regs);
    }
    *current_bank = bank;
}

// Copy a contiguous byte range from system RAM to VRAM through the banked
// window, switching banks as needed.
SDL_FORCE_INLINE શૂન્ય BankedDosmemput(અચલ Uint8 *src, Uint32 total_bytes, Uint32 dst_offset,
                                      Uint32 win_gran_bytes, Uint32 win_size_bytes,
                                      Uint32 win_base, Uint32 win_func_ptr,
                                      પૂર્ણાંક *current_bank)
{
    Uint32 src_off = 0;
    જ્યારે (total_bytes > 0) {
        પૂર્ણાંક bank = (પૂર્ણાંક)(dst_offset / win_gran_bytes);
        Uint32 off_in_win = dst_offset % win_gran_bytes;
        Uint32 avail = win_size_bytes - off_in_win;
        Uint32 n = total_bytes;
        જો (n > avail) {
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
સ્થિર શૂન્ય BankedFramebufferCopyRect(અચલ SDL_DisplayModeData *mdata,
                                      અચલ SDL_Surface *src,
                                      અચલ SDL_Rect *src_rect,
                                      પૂર્ણાંક dst_x, પૂર્ણાંક dst_y,
                                      Uint32 win_gran_bytes,
                                      Uint32 win_size_bytes,
                                      Uint32 win_base,
                                      પૂર્ણાંક *current_bank,
                                      Uint32 win_func_ptr)
{
    અચલ Uint16 dst_pitch = mdata->pitch;
    અચલ પૂર્ણાંક bytes_per_pixel = SDL_BYTESPERPIXEL(src->format);
    અચલ પૂર્ણાંક row_bytes = src_rect->w * bytes_per_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    જો (row_bytes == src->pitch && row_bytes == dst_pitch) {
        અચલ Uint8 *src_data = (અચલ Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_data, (Uint32)(row_bytes * src_rect->h), dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
        પાછા;
    }

    માટે (પૂર્ણાંક y = 0; y < src_rect->h; y++) {
        અચલ Uint8 *src_row = (અચલ Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * bytes_per_pixel;
        Uint32 dst_offset = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * bytes_per_pixel;
        BankedDosmemput(src_row, (Uint32)row_bytes, dst_offset,
                        win_gran_bytes, win_size_bytes, win_base, win_func_ptr, current_bank);
    }
}

સ્થિર શૂન્ય WaitForVBlank(શૂન્ય)
{
    જ્યારે (inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    જ્યારે (!(inportb(VGA_STATUS_PORT) & VGA_STATUS_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

સ્થિર શૂન્ય ProgramVGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_INDEX, 0);
    માટે (પૂર્ણાંક i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_DATA, palette->colors[i].r >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].g >> 2);
        outportb(VGA_DAC_DATA, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_UpdateWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window, અચલ SDL_Rect *rects, પૂર્ણાંક numrects)
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
    જો (fb_state.direct_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        જો (window->surface) {
            SDL_Palette *pal = window->surface->palette;
            જો (pal && pal->version != vdata->palette_version) {
                vdata->palette_version = pal->version;
                ProgramVGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        જો (numrects <= 0) {
            પાછા true;
        }

        જો (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            અચલ પૂર્ણાંક src_pitch = fb_state.src_pitch;
            અચલ પૂર્ણાંક dst_pitch = fb_state.vram_pitch;
            અચલ Uint8 *pixels = fb_state.pixels;

            જો (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                જો (fb_state.pitches_match) {
                    dosmemput(pixels, fb_state.fb_size, fb_state.vram_phys);
                } નહીંતર {
                    માટે (પૂર્ણાંક i = 0; i < numrects; i++) {
                        પૂર્ણાંક rx = rects[i].x, ry = rects[i].y;
                        પૂર્ણાંક rw = rects[i].w, rh = rects[i].h;
                        જો (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        જો (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        જો (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        જો (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        જો (rw <= 0 || rh <= 0) {
                            ચાલુ;
                        }
                        અચલ પૂર્ણાંક bx = rx * fb_state.bpp;
                        અચલ પૂર્ણાંક bw = rw * fb_state.bpp;
                        અચલ Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        માટે (પૂર્ણાંક row = 0; row < rh; row++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } નહીંતર {
                // Multi-bank: bank-switch as needed.
                અચલ Uint32 gran = fb_state.win_gran_bytes;
                અચલ Uint32 wsize = fb_state.win_size_bytes;
                અચલ Uint32 wbase = fb_state.win_base;
                અચલ Uint32 wfunc = fb_state.win_func_ptr;
                પૂર્ણાંક current_bank = -1;

                જો (fb_state.pitches_match) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_size, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } નહીંતર {
                    // Per-rect with bank switching.
                    માટે (પૂર્ણાંક i = 0; i < numrects; i++) {
                        પૂર્ણાંક rx = rects[i].x, ry = rects[i].y;
                        પૂર્ણાંક rw = rects[i].w, rh = rects[i].h;
                        જો (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        જો (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        જો (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        જો (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        જો (rw <= 0 || rh <= 0) {
                            ચાલુ;
                        }
                        અચલ પૂર્ણાંક bx = rx * fb_state.bpp;
                        અચલ પૂર્ણાંક bw = rw * fb_state.bpp;

                        માટે (પૂર્ણાંક row = 0; row < rh; row++) {
                            અચલ Uint8 *sp = pixels + (ry + row) * src_pitch + bx;
                            Uint32 dst_offset = (Uint32)(ry + row) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_offset,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } નહીંતર {
            // nearptr path (LFB fallback)
            જો (fb_state.pitches_match) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_size);
            } નહીંતર {
                અચલ પૂર્ણાંક bpp = fb_state.bpp;
                અચલ પૂર્ણાંક src_pitch = fb_state.src_pitch;
                અચલ પૂર્ણાંક dst_pitch = fb_state.vram_pitch;
                અચલ Uint8 *pixels = fb_state.pixels;

                માટે (પૂર્ણાંક i = 0; i < numrects; i++) {
                    પૂર્ણાંક rx = rects[i].x, ry = rects[i].y;
                    પૂર્ણાંક rw = rects[i].w, rh = rects[i].h;
                    જો (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    જો (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    જો (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    જો (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    જો (rw <= 0 || rh <= 0) {
                        ચાલુ;
                    }
                    અચલ પૂર્ણાંક bw = rw * bpp;
                    અચલ Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    માટે (પૂર્ણાંક row = 0; row < rh; row++) {
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
        જો (!fb_state.use_dosmemput && vdata->page_flip_available) {
            અચલ SDL_DisplayModeData *mdata = vdata->current_mode.internal;
            પૂર્ણાંક back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = first_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_page = back_page;

            પૂર્ણાંક new_back = 1 - vdata->current_page;
            fb_state.vram_ptr = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        }

        પાછા true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    જો (!src) {
        src = (SDL_Surface *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), DOS_SURFACE, ખાલી);
    }
    જો (!src) {
        પાછા SDL_SetError("Couldn't find DOS surface for window");
    }

    અચલ SDL_DisplayModeData *mdata = vdata->current_mode.internal;
    SDL_WindowData *windata = window->internal;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = ખાલી;
    bool dac_needs_update = false;

    જો (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = window->surface ? SDL_GetSurfacePalette(window->surface) : ખાલી;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        જો (win_palette && src_palette && win_palette != src_palette &&
            win_palette->version != src_palette->version) {
            SDL_SetPaletteColors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            જો (!vdata->banked_mode && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                જો (dst_palette && dst_palette != src_palette) {
                    SDL_SetPaletteColors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        જો (dac_palette && dac_palette->version != vdata->palette_version) {
            dac_needs_update = true;
        }
    }

    જો (vdata->banked_mode) {
        // --- Banked framebuffer path (dirty-rect aware) ---
        // We composite the cursor onto the source surface (in system RAM),
        // then bank-copy only the dirty rectangles to the VGA window.  We
        // need to undo the cursor composite afterwards so the app's surface
        // isn't permanently modified.

        અચલ પૂર્ણાંક dst_x = ((પૂર્ણાંક)mdata->w - src->w) / 2;
        અચલ પૂર્ણાંક dst_y = ((પૂર્ણાંક)mdata->h - src->h) / 2;

        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = ખાલી;
        SDL_Rect cursorrect;
        SDL_Rect cursor_clipped; // cursorrect clipped to src bounds
        SDL_Surface *cursor_save = ખાલી;
        bool have_cursor_rect = false;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : ખાલી;
        જો (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        જો (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            જો (cursor) {
                cursorrect.x = SDL_clamp((પૂર્ણાંક)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = SDL_clamp((પૂર્ણાંક)mouse->y, 0, window->h) - cur->internal->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                જો (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                જો (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                જો (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                જો (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                જો (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    જો (cursor_save) {
                        જો (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            જો (sp) {
                                SDL_SetSurfacePalette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, ખાલી);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, ખાલી, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        અચલ પૂર્ણાંક vsync_interval = windata->framebuffer_vsync;
        જો (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        જો (dac_needs_update) {
            vdata->palette_version = dac_palette->version;
            ProgramVGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        અચલ Uint32 win_gran_bytes = (Uint32)mdata->win_granularity * 1024;
        અચલ Uint32 win_size_bytes = (Uint32)mdata->win_size * 1024;
        અચલ Uint32 win_base = (Uint32)mdata->win_a_segment << 4;
        પૂર્ણાંક current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        માટે (પૂર્ણાંક r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            જો (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            જો (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            જો (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            જો (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            જો (rect.w <= 0 || rect.h <= 0) {
                ચાલુ;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            જો (have_cursor_rect && !cursor_covered) {
                જો (rect.x <= cursor_clipped.x &&
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
        જો (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_bytes, win_size_bytes, win_base,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        જો (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, ખાલી, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } નહીંતર {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        જો (!dst) {
            પાછા SDL_SetError("Couldn't find VESA linear framebuffer surface for window");
        }

        અચલ SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = ખાલી;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : ખાલી;
        જો (cur && cur->animation) {
            cur = cur->animation->frames[cur->animation->current_frame];
        }
        જો (mouse && mouse->internal && !mouse->relative_mode && mouse->cursor_visible && cur && cur->internal) {
            cursor = cur->internal->surface;
            જો (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((પૂર્ણાંક)mouse->x, 0, window->w) - cur->internal->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((પૂર્ણાંક)mouse->y, 0, window->h) - cur->internal->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        જો (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            અચલ Uint8 *sp = (અચલ Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            જો (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } નહીંતર {
                માટે (પૂર્ણાંક row = 0; row < dstrect.h; row++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } નહીંતર {
            // Blit to the back page (or the only page, if no page-flipping)
            જો (!SDL_BlitSurface(src, ખાલી, dst, &dstrect)) {
                પાછા false;
            }
        }

        જો (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->internal, dst);
            જો (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, ખાલી, dst, &cursorrect)) {
                પાછા false;
            }
        }

        જો (vdata->page_flip_available) {
            // Page-flip with optional vsync.
            અચલ પૂર્ણાંક vsync_interval = windata->framebuffer_vsync;
            પૂર્ણાંક back_page = 1 - vdata->current_page;
            Uint16 first_scanline = (Uint16)(vdata->page_offset[back_page] / mdata->pitch);

            જો (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            જો (dac_needs_update) {
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
            પૂર્ણાંક new_back = 1 - vdata->current_page;
            dst->pixels = (Uint8 *)DOS_PhysicalToLinear(vdata->mapping.address) + vdata->page_offset[new_back];
        } નહીંતર {
            // No page-flipping: wait for vsync, then update DAC atomically
            અચલ પૂર્ણાંક vsync_interval = windata->framebuffer_vsync;
            જો (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            જો (dac_needs_update) {
                vdata->palette_version = dac_palette->version;
                ProgramVGADAC(dac_palette);
            }
        }
    }

    પાછા true;
}

શૂન્ય DOSVESA_DestroyWindowFramebuffer(SDL_VideoDevice *device, SDL_Window *window)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (શૂન્ય)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_GetWindowProperties(window), DOS_SURFACE);
}

#endif // SDL_VIDEO_DRIVER_DOSVESA

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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DOSVESA

#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_properties_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosframebuffer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <pc.h>           // for inportb, outportb
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/movedata.h> // for dosmemput (banked framebuffer writes)

// note that DOS_SURFACE's value is the same string that the dummy driver uses.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool ਸਿੱਧਾ_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    ਪੂਰਨ vram_pitch;
    ਪੂਰਨ vram_w;
    ਪੂਰਨ vram_h;
    ਪੂਰਨ bpp; // bytes per pixel

    // dosmemput path state (use_dosmemput)
    Uint32 vram_phys;      // base address for dosmemput (e.g. 0xA0000)
    bool banked_multibank; // true if fb doesn't fit in one bank window
    Uint32 win_gran_ਬਾਈਟਾਂ; // bank granularity in bytes
    Uint32 win_ਮਾਪ_ਬਾਈਟਾਂ; // bank window size in bytes
    Uint32 win_ਅਧਾਰ;       // window base address (segment << 4)
    Uint32 win_func_ptr;   // real-mode far pointer to bank-switch function

    // nearptr path state (use_dosmemput == false)
    Uint8 *vram_ptr; // nearptr into VRAM (LFB)

    // Cached per-frame values (set at create time, avoid repeated lookups)
    Uint8 *pixels;      // == surface->pixels (stable after create)
    ਪੂਰਨ src_pitch;      // == surface->pitch
    Uint32 fb_ਮਾਪ;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_ਮੇਲ; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

ਸਥਿਰ DOSFramebufferState fb_state;

// Convert cursor to the current format.
ਸਥਿਰ SDL_Surface *GetConvertedCursorSurface(SDL_Cursor_ਅੰਕੜੇ *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    ਜੇ (!pal) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    Uint32 pal_ਸੰਸਕਰਣ = pal ? pal->ਸੰਸਕਰਣ : 0;

    ਜੇ (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_ਸੰਸਕਰਣ == pal_ਸੰਸਕਰਣ) {
        ਵਾਪਸ curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = ਨਿਰਾ;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    ਪੂਰਨ w = src->w;
    ਪੂਰਨ h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    ਜੇ (!conv) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    ਜੇ (conv_pal) {
        SDL_ਸੈੱਟ_Palette_Colors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool ਵਰਤਿਆ[256];
    SDL_zeroa(ਵਰਤਿਆ);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, ਨਿਰਾ, conv, ਨਿਰਾ);
    SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    ਲਈ (ਪੂਰਨ y = 0; y < h; y++) {
        ਅਚਲ Uint32 *srcrow = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src->pixels + y * src->pitch);
        ਅਚਲ Uint8 *convrow = (ਅਚਲ Uint8 *)conv->pixels + y * conv->pitch;
        ਲਈ (ਪੂਰਨ x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            ਜੇ (srcA > 0) {
                ਵਰਤਿਆ[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < 256; i++) {
        ਜੇ (!ਵਰਤਿਆ[i]) {
            colorkey = (Uint32)i;
            ਰੋਕੋ;
        }
    }

    // Second pass: set transparent pixels to the colorkey index.
    ਲਈ (ਪੂਰਨ y = 0; y < h; y++) {
        ਅਚਲ Uint32 *srcrow = (ਅਚਲ Uint32 *)((ਅਚਲ Uint8 *)src->pixels + y * src->pitch);
        Uint8 *convrow = (Uint8 *)conv->pixels + y * conv->pitch;
        ਲਈ (ਪੂਰਨ x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            ਜੇ (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_ਸੈੱਟ_Surface_Color_ਕੁੰਜੀ(conv, true, colorkey);
    SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_ਸੰਸਕਰਣ = pal_ਸੰਸਕਰਣ;
    ਵਾਪਸ conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
ਖਾਲੀ DOSVESA_InvalidateCachedFramebuffer(ਖਾਲੀ)
{
    fb_state.ਸਿੱਧਾ_fb = false;
    fb_state.vram_ptr = ਨਿਰਾ;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = ਨਿਰਾ;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
ਸਥਿਰ SDL_Surface *CreateSystemSurface(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, ਪੂਰਨ w, ਪੂਰਨ h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ਜੇ (!surface) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    ਜੇ (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ਜੇ (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            ਲਈ (ਪੂਰਨ i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_ਸੈੱਟ_Palette_Colors(palette, black, 0, 256);
        }
        ਅੰਕੜੇ->palette_ਸੰਸਕਰਣ = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_ਸੂਚਕਾਂਕ, 0);
        ਲਈ (ਪੂਰਨ i = 0; i < 256; i++) {
            outportb(VGA_DAC_ਅੰਕੜੇ, 0);
            outportb(VGA_DAC_ਅੰਕੜੇ, 0);
            outportb(VGA_DAC_ਅੰਕੜੇ, 0);
        }
    }

    ਵਾਪਸ surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
ਸਥਿਰ bool Create_ਸਾਧਾਰਨ_Framebuffer(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                    SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ = &ਅੰਕੜੇ->current_ਬਹੁਲਕ;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *mdata = ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
    ਅਚਲ SDL_PixelFormat surface_format = ਬਹੁਲਕ->format;
    ਪੂਰਨ w, h;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(ਅੰਕੜੇ, w, h, surface_format);
    ਜੇ (!surface) {
        ਵਾਪਸ false;
    }

    SDL_Surface *lfb_surface = ਨਿਰਾ;

    ਜੇ (!ਅੰਕੜੇ->banked_ਬਹੁਲਕ) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        ਪੂਰਨ ਪਿੱਠ_ਪੰਨਾ = ਅੰਕੜੇ->ਪੰਨਾ_flip_ਉਪਲਬਧ ? (1 - ਅੰਕੜੇ->current_ਪੰਨਾ) : 0;
        ਖਾਲੀ *lfb_pixels = (Uint8 *)DOS_Physical_ਮੰਜ਼ਿਲ_ਰੇਖਿਕ(ਅੰਕੜੇ->mapping.ਪਤਾ) + ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[ਪਿੱਠ_ਪੰਨਾ];
        lfb_surface = SDL_CreateSurfaceFrom(ਬਹੁਲਕ->w, ਬਹੁਲਕ->h, surface_format, lfb_pixels, mdata->pitch);
        ਜੇ (!lfb_surface) {
            SDL_DestroySurface(surface);
            ਵਾਪਸ false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        ਜੇ (src_palette) {
            SDL_ਸੈੱਟ_Surface_Palette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    ਜੇ (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_ਸੈੱਟ_Surface_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ਵਾਪਸ true;
}

bool DOSVESA_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_zero(fb_state);

    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = device->ਅੰਦਰੂਨੀ;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ = &ਅੰਕੜੇ->current_ਬਹੁਲਕ;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *mdata = ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
    ਅਚਲ SDL_PixelFormat surface_format = ਬਹੁਲਕ->format;
    ਪੂਰਨ w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_ਸਿੱਧਾ_FRAMEBUFFER, false)) {
        ਪੂਰਨ vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        ਜੇ (mdata->win_a_segment && mdata->win_ਮਾਪ > 0 &&
            (mdata->win_a_ਗੁਣ & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } ਨਹੀਂਤਾਂ ਜੇ (!ਅੰਕੜੇ->banked_ਬਹੁਲਕ && ਅੰਕੜੇ->mapping.ਮਾਪ) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        ਜੇ (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(ਅੰਕੜੇ, w, h, surface_format);
            ਜੇ (!surface) {
                ਵਾਪਸ false;
            }

            SDL_ਸੈੱਟ_Surface_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), DOS_SURFACE, surface);

            fb_state.surface = surface;
            fb_state.ਸਿੱਧਾ_fb = true;
            fb_state.vram_pitch = vram_pitch;
            fb_state.vram_w = mdata->w;
            fb_state.vram_h = mdata->h;
            fb_state.bpp = SDL_BYTESPERPIXEL(surface_format);
            fb_state.pixels = (Uint8 *)surface->pixels;
            fb_state.src_pitch = surface->pitch;
            fb_state.fb_ਮਾਪ = (Uint32)vram_pitch * mdata->h;
            fb_state.pitches_ਮੇਲ = (surface->pitch == vram_pitch);

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
            ਜੇ (mdata->win_a_segment && mdata->win_ਮਾਪ > 0 &&
                (mdata->win_a_ਗੁਣ & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_ਬਾਈਟਾਂ = (Uint32)mdata->win_ਮਾਪ * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = ਨਿਰਾ;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_ਅਧਾਰ = fb_state.vram_phys;
                fb_state.win_gran_ਬਾਈਟਾਂ = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_ਮਾਪ_ਬਾਈਟਾਂ = win_ਬਾਈਟਾਂ;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_ਮਾਪ > win_ਬਾਈਟਾਂ);
            } ਨਹੀਂਤਾਂ ਜੇ (!ਅੰਕੜੇ->banked_ਬਹੁਲਕ && ਅੰਕੜੇ->mapping.ਮਾਪ) {
                // Fallback: nearptr to LFB.
                ਪੂਰਨ ਪਿੱਠ_ਪੰਨਾ = ਅੰਕੜੇ->ਪੰਨਾ_flip_ਉਪਲਬਧ ? (1 - ਅੰਕੜੇ->current_ਪੰਨਾ) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_Physical_ਮੰਜ਼ਿਲ_ਰੇਖਿਕ(ਅੰਕੜੇ->mapping.ਪਤਾ) + ਅੰਕੜੇ->ਪੰਨਾ_ਵਿੱਥ[ਪਿੱਠ_ਪੰਨਾ];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } ਨਹੀਂਤਾਂ {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                ਵਾਪਸ Create_ਸਾਧਾਰਨ_Framebuffer(device, ਖਿੜਕੀ, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            ਵਾਪਸ true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    ਵਾਪਸ Create_ਸਾਧਾਰਨ_Framebuffer(device, ਖਿੜਕੀ, format, pixels, pitch);
}

bool DOSVESA_ਸੈੱਟ_ਖਿੜਕੀ_Framebuffer_VSync(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ vsync)
{
    ਜੇ (vsync < 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unsupported vsync type");
    }
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅੰਕੜੇ->framebuffer_vsync = vsync;
    ਵਾਪਸ true;
}

bool DOSVESA_Get_ਖਿੜਕੀ_Framebuffer_VSync(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *vsync)
{
    ਜੇ (vsync) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        *vsync = ਅੰਕੜੇ->framebuffer_vsync;
    }
    ਵਾਪਸ true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE ਖਾਲੀ SwitchBank(ਪੂਰਨ bank, ਪੂਰਨ *current_bank, Uint32 win_func_ptr)
{
    ਜੇ (bank == *current_bank) {
        ਵਾਪਸ;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    ਜੇ (win_func_ptr) {
        regs.x.cs = (Uint16)(win_func_ptr >> 16);
        regs.x.ip = (Uint16)(win_func_ptr & 0xFFFF);
        __dpmi_simulate_real_mode_procedure_retf(&regs);
    } ਨਹੀਂਤਾਂ {
        regs.x.ax = 0x4F05;
        __dpmi_int(0x10, &regs);
    }
    *current_bank = bank;
}

// Copy a contiguous byte range from system RAM to VRAM through the banked
// window, switching banks as needed.
SDL_FORCE_INLINE ਖਾਲੀ BankedDosmemput(ਅਚਲ Uint8 *src, Uint32 ਕੁੱਲ_ਬਾਈਟਾਂ, Uint32 dst_ਵਿੱਥ,
                                      Uint32 win_gran_ਬਾਈਟਾਂ, Uint32 win_ਮਾਪ_ਬਾਈਟਾਂ,
                                      Uint32 win_ਅਧਾਰ, Uint32 win_func_ptr,
                                      ਪੂਰਨ *current_bank)
{
    Uint32 src_off = 0;
    ਜਦੋਂ (ਕੁੱਲ_ਬਾਈਟਾਂ > 0) {
        ਪੂਰਨ bank = (ਪੂਰਨ)(dst_ਵਿੱਥ / win_gran_ਬਾਈਟਾਂ);
        Uint32 off_ਵਿੱਚ_win = dst_ਵਿੱਥ % win_gran_ਬਾਈਟਾਂ;
        Uint32 avail = win_ਮਾਪ_ਬਾਈਟਾਂ - off_ਵਿੱਚ_win;
        Uint32 n = ਕੁੱਲ_ਬਾਈਟਾਂ;
        ਜੇ (n > avail) {
            n = avail;
        }
        SwitchBank(bank, current_bank, win_func_ptr);
        dosmemput(src + src_off, n, win_ਅਧਾਰ + off_ਵਿੱਚ_win);
        src_off += n;
        dst_ਵਿੱਥ += n;
        ਕੁੱਲ_ਬਾਈਟਾਂ -= n;
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
ਸਥਿਰ ਖਾਲੀ BankedFramebufferCopyRect(ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *mdata,
                                      ਅਚਲ SDL_Surface *src,
                                      ਅਚਲ SDL_Rect *src_rect,
                                      ਪੂਰਨ dst_x, ਪੂਰਨ dst_y,
                                      Uint32 win_gran_ਬਾਈਟਾਂ,
                                      Uint32 win_ਮਾਪ_ਬਾਈਟਾਂ,
                                      Uint32 win_ਅਧਾਰ,
                                      ਪੂਰਨ *current_bank,
                                      Uint32 win_func_ptr)
{
    ਅਚਲ Uint16 dst_pitch = mdata->pitch;
    ਅਚਲ ਪੂਰਨ ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel = SDL_BYTESPERPIXEL(src->format);
    ਅਚਲ ਪੂਰਨ ਪੰਕਤੀ_ਬਾਈਟਾਂ = src_rect->w * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    ਜੇ (ਪੰਕਤੀ_ਬਾਈਟਾਂ == src->pitch && ਪੰਕਤੀ_ਬਾਈਟਾਂ == dst_pitch) {
        ਅਚਲ Uint8 *src_ਅੰਕੜੇ = (ਅਚਲ Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        Uint32 dst_ਵਿੱਥ = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        BankedDosmemput(src_ਅੰਕੜੇ, (Uint32)(ਪੰਕਤੀ_ਬਾਈਟਾਂ * src_rect->h), dst_ਵਿੱਥ,
                        win_gran_ਬਾਈਟਾਂ, win_ਮਾਪ_ਬਾਈਟਾਂ, win_ਅਧਾਰ, win_func_ptr, current_bank);
        ਵਾਪਸ;
    }

    ਲਈ (ਪੂਰਨ y = 0; y < src_rect->h; y++) {
        ਅਚਲ Uint8 *src_ਪੰਕਤੀ = (ਅਚਲ Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        Uint32 dst_ਵਿੱਥ = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
        BankedDosmemput(src_ਪੰਕਤੀ, (Uint32)ਪੰਕਤੀ_ਬਾਈਟਾਂ, dst_ਵਿੱਥ,
                        win_gran_ਬਾਈਟਾਂ, win_ਮਾਪ_ਬਾਈਟਾਂ, win_ਅਧਾਰ, win_func_ptr, current_bank);
    }
}

ਸਥਿਰ ਖਾਲੀ WaitForVBlank(ਖਾਲੀ)
{
    ਜਦੋਂ (inportb(VGA_ਸਥਿਤੀ_ਪੋਰਟ) & VGA_ਸਥਿਤੀ_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    ਜਦੋਂ (!(inportb(VGA_ਸਥਿਤੀ_ਪੋਰਟ) & VGA_ਸਥਿਤੀ_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

ਸਥਿਰ ਖਾਲੀ ਪ੍ਰੋਗਰਾਮ_VGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_ਸੂਚਕਾਂਕ, 0);
    ਲਈ (ਪੂਰਨ i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_ਅੰਕੜੇ, palette->colors[i].r >> 2);
        outportb(VGA_DAC_ਅੰਕੜੇ, palette->colors[i].g >> 2);
        outportb(VGA_DAC_ਅੰਕੜੇ, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    SDL_Video_ਅੰਕੜੇ *vdata = device->ਅੰਦਰੂਨੀ;

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
    ਜੇ (fb_state.ਸਿੱਧਾ_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        ਜੇ (ਖਿੜਕੀ->surface) {
            SDL_Palette *pal = ਖਿੜਕੀ->surface->palette;
            ਜੇ (pal && pal->ਸੰਸਕਰਣ != vdata->palette_ਸੰਸਕਰਣ) {
                vdata->palette_ਸੰਸਕਰਣ = pal->ਸੰਸਕਰਣ;
                ਪ੍ਰੋਗਰਾਮ_VGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        ਜੇ (numrects <= 0) {
            ਵਾਪਸ true;
        }

        ਜੇ (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            ਅਚਲ ਪੂਰਨ src_pitch = fb_state.src_pitch;
            ਅਚਲ ਪੂਰਨ dst_pitch = fb_state.vram_pitch;
            ਅਚਲ Uint8 *pixels = fb_state.pixels;

            ਜੇ (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                ਜੇ (fb_state.pitches_ਮੇਲ) {
                    dosmemput(pixels, fb_state.fb_ਮਾਪ, fb_state.vram_phys);
                } ਨਹੀਂਤਾਂ {
                    ਲਈ (ਪੂਰਨ i = 0; i < numrects; i++) {
                        ਪੂਰਨ rx = rects[i].x, ry = rects[i].y;
                        ਪੂਰਨ rw = rects[i].w, rh = rects[i].h;
                        ਜੇ (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        ਜੇ (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        ਜੇ (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        ਜੇ (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        ਜੇ (rw <= 0 || rh <= 0) {
                            ਜਾਰੀ;
                        }
                        ਅਚਲ ਪੂਰਨ bx = rx * fb_state.bpp;
                        ਅਚਲ ਪੂਰਨ bw = rw * fb_state.bpp;
                        ਅਚਲ Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        ਲਈ (ਪੂਰਨ ਪੰਕਤੀ = 0; ਪੰਕਤੀ < rh; ਪੰਕਤੀ++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } ਨਹੀਂਤਾਂ {
                // Multi-bank: bank-switch as needed.
                ਅਚਲ Uint32 gran = fb_state.win_gran_ਬਾਈਟਾਂ;
                ਅਚਲ Uint32 wsize = fb_state.win_ਮਾਪ_ਬਾਈਟਾਂ;
                ਅਚਲ Uint32 wbase = fb_state.win_ਅਧਾਰ;
                ਅਚਲ Uint32 wfunc = fb_state.win_func_ptr;
                ਪੂਰਨ current_bank = -1;

                ਜੇ (fb_state.pitches_ਮੇਲ) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_ਮਾਪ, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } ਨਹੀਂਤਾਂ {
                    // Per-rect with bank switching.
                    ਲਈ (ਪੂਰਨ i = 0; i < numrects; i++) {
                        ਪੂਰਨ rx = rects[i].x, ry = rects[i].y;
                        ਪੂਰਨ rw = rects[i].w, rh = rects[i].h;
                        ਜੇ (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        ਜੇ (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        ਜੇ (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        ਜੇ (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        ਜੇ (rw <= 0 || rh <= 0) {
                            ਜਾਰੀ;
                        }
                        ਅਚਲ ਪੂਰਨ bx = rx * fb_state.bpp;
                        ਅਚਲ ਪੂਰਨ bw = rw * fb_state.bpp;

                        ਲਈ (ਪੂਰਨ ਪੰਕਤੀ = 0; ਪੰਕਤੀ < rh; ਪੰਕਤੀ++) {
                            ਅਚਲ Uint8 *sp = pixels + (ry + ਪੰਕਤੀ) * src_pitch + bx;
                            Uint32 dst_ਵਿੱਥ = (Uint32)(ry + ਪੰਕਤੀ) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_ਵਿੱਥ,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } ਨਹੀਂਤਾਂ {
            // nearptr path (LFB fallback)
            ਜੇ (fb_state.pitches_ਮੇਲ) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_ਮਾਪ);
            } ਨਹੀਂਤਾਂ {
                ਅਚਲ ਪੂਰਨ bpp = fb_state.bpp;
                ਅਚਲ ਪੂਰਨ src_pitch = fb_state.src_pitch;
                ਅਚਲ ਪੂਰਨ dst_pitch = fb_state.vram_pitch;
                ਅਚਲ Uint8 *pixels = fb_state.pixels;

                ਲਈ (ਪੂਰਨ i = 0; i < numrects; i++) {
                    ਪੂਰਨ rx = rects[i].x, ry = rects[i].y;
                    ਪੂਰਨ rw = rects[i].w, rh = rects[i].h;
                    ਜੇ (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    ਜੇ (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    ਜੇ (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    ਜੇ (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    ਜੇ (rw <= 0 || rh <= 0) {
                        ਜਾਰੀ;
                    }
                    ਅਚਲ ਪੂਰਨ bw = rw * bpp;
                    ਅਚਲ Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    ਲਈ (ਪੂਰਨ ਪੰਕਤੀ = 0; ਪੰਕਤੀ < rh; ਪੰਕਤੀ++) {
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
        ਜੇ (!fb_state.use_dosmemput && vdata->ਪੰਨਾ_flip_ਉਪਲਬਧ) {
            ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *mdata = vdata->current_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ;
            ਪੂਰਨ ਪਿੱਠ_ਪੰਨਾ = 1 - vdata->current_ਪੰਨਾ;
            Uint16 ਪਹਿਲਾ_scanline = (Uint16)(vdata->ਪੰਨਾ_ਵਿੱਥ[ਪਿੱਠ_ਪੰਨਾ] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = ਪਹਿਲਾ_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_ਪੰਨਾ = ਪਿੱਠ_ਪੰਨਾ;

            ਪੂਰਨ new_ਪਿੱਠ = 1 - vdata->current_ਪੰਨਾ;
            fb_state.vram_ptr = (Uint8 *)DOS_Physical_ਮੰਜ਼ਿਲ_ਰੇਖਿਕ(vdata->mapping.ਪਤਾ) + vdata->ਪੰਨਾ_ਵਿੱਥ[new_ਪਿੱਠ];
        }

        ਵਾਪਸ true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    ਜੇ (!src) {
        src = (SDL_Surface *)SDL_Get_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), DOS_SURFACE, ਨਿਰਾ);
    }
    ਜੇ (!src) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find DOS surface for window");
    }

    ਅਚਲ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *mdata = vdata->current_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = ਨਿਰਾ;
    bool dac_needs_update = false;

    ਜੇ (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = ਖਿੜਕੀ->surface ? SDL_GetSurfacePalette(ਖਿੜਕੀ->surface) : ਨਿਰਾ;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        ਜੇ (win_palette && src_palette && win_palette != src_palette &&
            win_palette->ਸੰਸਕਰਣ != src_palette->ਸੰਸਕਰਣ) {
            SDL_ਸੈੱਟ_Palette_Colors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            ਜੇ (!vdata->banked_ਬਹੁਲਕ && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                ਜੇ (dst_palette && dst_palette != src_palette) {
                    SDL_ਸੈੱਟ_Palette_Colors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        ਜੇ (dac_palette && dac_palette->ਸੰਸਕਰਣ != vdata->palette_ਸੰਸਕਰਣ) {
            dac_needs_update = true;
        }
    }

    ਜੇ (vdata->banked_ਬਹੁਲਕ) {
        // --- Banked framebuffer path (dirty-rect aware) ---
        // We composite the cursor onto the source surface (in system RAM),
        // then bank-copy only the dirty rectangles to the VGA window.  We
        // need to undo the cursor composite afterwards so the app's surface
        // isn't permanently modified.

        ਅਚਲ ਪੂਰਨ dst_x = ((ਪੂਰਨ)mdata->w - src->w) / 2;
        ਅਚਲ ਪੂਰਨ dst_y = ((ਪੂਰਨ)mdata->h - src->h) / 2;

        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = ਨਿਰਾ;
        SDL_Rect cursorrect;
        SDL_Rect cursor_clipped; // cursorrect clipped to src bounds
        SDL_Surface *cursor_save = ਨਿਰਾ;
        bool have_cursor_rect = false;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : ਨਿਰਾ;
        ਜੇ (cur && cur->animation) {
            cur = cur->animation->ਚੌਖਟੇ[cur->animation->current_ਚੌਖਟਾ];
        }
        ਜੇ (mouse && mouse->ਅੰਦਰੂਨੀ && !mouse->relative_ਬਹੁਲਕ && mouse->cursor_visible && cur && cur->ਅੰਦਰੂਨੀ) {
            cursor = cur->ਅੰਦਰੂਨੀ->surface;
            ਜੇ (cursor) {
                cursorrect.x = SDL_clamp((ਪੂਰਨ)mouse->x, 0, ਖਿੜਕੀ->w) - cur->ਅੰਦਰੂਨੀ->hot_x;
                cursorrect.y = SDL_clamp((ਪੂਰਨ)mouse->y, 0, ਖਿੜਕੀ->h) - cur->ਅੰਦਰੂਨੀ->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                ਜੇ (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                ਜੇ (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                ਜੇ (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                ਜੇ (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                ਜੇ (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    ਜੇ (cursor_save) {
                        ਜੇ (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            ਜੇ (sp) {
                                SDL_ਸੈੱਟ_Surface_Palette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, ਨਿਰਾ);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->ਅੰਦਰੂਨੀ, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, ਨਿਰਾ, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        ਅਚਲ ਪੂਰਨ vsync_interval = windata->framebuffer_vsync;
        ਜੇ (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        ਜੇ (dac_needs_update) {
            vdata->palette_ਸੰਸਕਰਣ = dac_palette->ਸੰਸਕਰਣ;
            ਪ੍ਰੋਗਰਾਮ_VGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        ਅਚਲ Uint32 win_gran_ਬਾਈਟਾਂ = (Uint32)mdata->win_granularity * 1024;
        ਅਚਲ Uint32 win_ਮਾਪ_ਬਾਈਟਾਂ = (Uint32)mdata->win_ਮਾਪ * 1024;
        ਅਚਲ Uint32 win_ਅਧਾਰ = (Uint32)mdata->win_a_segment << 4;
        ਪੂਰਨ current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        ਲਈ (ਪੂਰਨ r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            ਜੇ (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            ਜੇ (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            ਜੇ (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            ਜੇ (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            ਜੇ (rect.w <= 0 || rect.h <= 0) {
                ਜਾਰੀ;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            ਜੇ (have_cursor_rect && !cursor_covered) {
                ਜੇ (rect.x <= cursor_clipped.x &&
                    rect.y <= cursor_clipped.y &&
                    rect.x + rect.w >= cursor_clipped.x + cursor_clipped.w &&
                    rect.y + rect.h >= cursor_clipped.y + cursor_clipped.h) {
                    cursor_covered = true;
                }
            }

            BankedFramebufferCopyRect(mdata, src, &rect, dst_x, dst_y,
                                      win_gran_ਬਾਈਟਾਂ, win_ਮਾਪ_ਬਾਈਟਾਂ, win_ਅਧਾਰ,
                                      &current_bank, mdata->win_func_ptr);
        }

        // If no dirty rect covered the cursor, copy the cursor region separately.
        ਜੇ (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_ਬਾਈਟਾਂ, win_ਮਾਪ_ਬਾਈਟਾਂ, win_ਅਧਾਰ,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        ਜੇ (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, ਨਿਰਾ, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } ਨਹੀਂਤਾਂ {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        ਜੇ (!dst) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find VESA linear framebuffer surface for window");
        }

        ਅਚਲ SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = ਨਿਰਾ;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : ਨਿਰਾ;
        ਜੇ (cur && cur->animation) {
            cur = cur->animation->ਚੌਖਟੇ[cur->animation->current_ਚੌਖਟਾ];
        }
        ਜੇ (mouse && mouse->ਅੰਦਰੂਨੀ && !mouse->relative_ਬਹੁਲਕ && mouse->cursor_visible && cur && cur->ਅੰਦਰੂਨੀ) {
            cursor = cur->ਅੰਦਰੂਨੀ->surface;
            ਜੇ (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((ਪੂਰਨ)mouse->x, 0, ਖਿੜਕੀ->w) - cur->ਅੰਦਰੂਨੀ->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((ਪੂਰਨ)mouse->y, 0, ਖਿੜਕੀ->h) - cur->ਅੰਦਰੂਨੀ->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        ਜੇ (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            ਅਚਲ Uint8 *sp = (ਅਚਲ Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            ਜੇ (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } ਨਹੀਂਤਾਂ {
                ਲਈ (ਪੂਰਨ ਪੰਕਤੀ = 0; ਪੰਕਤੀ < dstrect.h; ਪੰਕਤੀ++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } ਨਹੀਂਤਾਂ {
            // Blit to the back page (or the only page, if no page-flipping)
            ਜੇ (!SDL_BlitSurface(src, ਨਿਰਾ, dst, &dstrect)) {
                ਵਾਪਸ false;
            }
        }

        ਜੇ (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->ਅੰਦਰੂਨੀ, dst);
            ਜੇ (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, ਨਿਰਾ, dst, &cursorrect)) {
                ਵਾਪਸ false;
            }
        }

        ਜੇ (vdata->ਪੰਨਾ_flip_ਉਪਲਬਧ) {
            // Page-flip with optional vsync.
            ਅਚਲ ਪੂਰਨ vsync_interval = windata->framebuffer_vsync;
            ਪੂਰਨ ਪਿੱਠ_ਪੰਨਾ = 1 - vdata->current_ਪੰਨਾ;
            Uint16 ਪਹਿਲਾ_scanline = (Uint16)(vdata->ਪੰਨਾ_ਵਿੱਥ[ਪਿੱਠ_ਪੰਨਾ] / mdata->pitch);

            ਜੇ (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            ਜੇ (dac_needs_update) {
                vdata->palette_ਸੰਸਕਰਣ = dac_palette->ਸੰਸਕਰਣ;
                ਪ੍ਰੋਗਰਾਮ_VGADAC(dac_palette);
            }

            // Flip: make the back page (which we just drew to) the visible page.
            // Always use subfunction 0x0080 (set display start, don't wait) —
            // vsync is controlled by our manual vblank wait above.
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0; // first pixel in scan line
            regs.x.dx = ਪਹਿਲਾ_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_ਪੰਨਾ = ਪਿੱਠ_ਪੰਨਾ;

            // Update LFB surface to point at the new back page (the old front page)
            ਪੂਰਨ new_ਪਿੱਠ = 1 - vdata->current_ਪੰਨਾ;
            dst->pixels = (Uint8 *)DOS_Physical_ਮੰਜ਼ਿਲ_ਰੇਖਿਕ(vdata->mapping.ਪਤਾ) + vdata->ਪੰਨਾ_ਵਿੱਥ[new_ਪਿੱਠ];
        } ਨਹੀਂਤਾਂ {
            // No page-flipping: wait for vsync, then update DAC atomically
            ਅਚਲ ਪੂਰਨ vsync_interval = windata->framebuffer_vsync;
            ਜੇ (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            ਜੇ (dac_needs_update) {
                vdata->palette_ਸੰਸਕਰਣ = dac_palette->ਸੰਸਕਰਣ;
                ਪ੍ਰੋਗਰਾਮ_VGADAC(dac_palette);
            }
        }
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ DOSVESA_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *device, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (ਖਾਲੀ)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), DOS_SURFACE);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_DOSVESA

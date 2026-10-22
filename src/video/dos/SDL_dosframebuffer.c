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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_DOSVESA

#ಅನ್ತರ್ಭಾವ "../../SDL_properties_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosframebuffer_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_dosvideo.h"

#ಅನ್ತರ್ಭಾವ <pc.h>           // for inportb, outportb
#ಅನ್ತರ್ಭಾವ <sys/movedata.h> // for dosmemput (banked framebuffer writes)

// note that DOS_SURFACE's value is the same string that the dummy driver uses.
#ವ್ಯಾಖ್ಯಾನಿಸು DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool ನೇರ_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    ಪೂರ್ಣಾಂಕ vram_pitch;
    ಪೂರ್ಣಾಂಕ vram_w;
    ಪೂರ್ಣಾಂಕ vram_h;
    ಪೂರ್ಣಾಂಕ bpp; // bytes per pixel

    // dosmemput path state (use_dosmemput)
    Uint32 vram_phys;      // base address for dosmemput (e.g. 0xA0000)
    bool banked_multibank; // true if fb doesn't fit in one bank window
    Uint32 win_gran_ಬೈಟುಗಳು; // bank granularity in bytes
    Uint32 win_ಗಾತ್ರ_ಬೈಟುಗಳು; // bank window size in bytes
    Uint32 win_ತಳ;       // window base address (segment << 4)
    Uint32 win_func_ptr;   // real-mode far pointer to bank-switch function

    // nearptr path state (use_dosmemput == false)
    Uint8 *vram_ptr; // nearptr into VRAM (LFB)

    // Cached per-frame values (set at create time, avoid repeated lookups)
    Uint8 *pixels;      // == surface->pixels (stable after create)
    ಪೂರ್ಣಾಂಕ src_pitch;      // == surface->pitch
    Uint32 fb_ಗಾತ್ರ;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_ಹೊಂದಿಕೆ; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

ಸ್ಥಿರ DOSFramebufferState fb_state;

// Convert cursor to the current format.
ಸ್ಥಿರ SDL_Surface *GetConvertedCursorSurface(SDL_Cursor_ದತ್ತಾಂಶ *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    ಆದರೆ (!pal) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    Uint32 pal_ಆವೃತ್ತಿ = pal ? pal->ಆವೃತ್ತಿ : 0;

    ಆದರೆ (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_ಆವೃತ್ತಿ == pal_ಆವೃತ್ತಿ) {
        ಹಿಂತಿರುಗಿ curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = ಖಾಲಿ;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    ಪೂರ್ಣಾಂಕ w = src->w;
    ಪೂರ್ಣಾಂಕ h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    ಆದರೆ (!conv) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    ಆದರೆ (conv_pal) {
        SDL_ಗಣ_Palette_Colors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool ಬಳಸಿದ[256];
    SDL_zeroa(ಬಳಸಿದ);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, ಖಾಲಿ, conv, ಖಾಲಿ);
    SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < h; y++) {
        ಸ್ಥಿರಾಂಕ Uint32 *srcrow = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src->pixels + y * src->pitch);
        ಸ್ಥಿರಾಂಕ Uint8 *convrow = (ಸ್ಥಿರಾಂಕ Uint8 *)conv->pixels + y * conv->pitch;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            ಆದರೆ (srcA > 0) {
                ಬಳಸಿದ[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 256; i++) {
        ಆದರೆ (!ಬಳಸಿದ[i]) {
            colorkey = (Uint32)i;
            ನಿಲ್ಲಿಸು;
        }
    }

    // Second pass: set transparent pixels to the colorkey index.
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < h; y++) {
        ಸ್ಥಿರಾಂಕ Uint32 *srcrow = (ಸ್ಥಿರಾಂಕ Uint32 *)((ಸ್ಥಿರಾಂಕ Uint8 *)src->pixels + y * src->pitch);
        Uint8 *convrow = (Uint8 *)conv->pixels + y * conv->pitch;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            ಆದರೆ (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_ಗಣ_Surface_Color_ಕೀಲಿ(conv, true, colorkey);
    SDL_ಗಣ_Surface_Blend_ಬಹುಲಕ(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_ಆವೃತ್ತಿ = pal_ಆವೃತ್ತಿ;
    ಹಿಂತಿರುಗಿ conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
ಶೂನ್ಯ DOSVESA_InvalidateCachedFramebuffer(ಶೂನ್ಯ)
{
    fb_state.ನೇರ_fb = false;
    fb_state.vram_ptr = ಖಾಲಿ;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = ಖಾಲಿ;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
ಸ್ಥಿರ SDL_Surface *CreateSystemSurface(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    ಆದರೆ (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        ಆದರೆ (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_ಗಣ_Palette_Colors(palette, black, 0, 256);
        }
        ದತ್ತಾಂಶ->palette_ಆವೃತ್ತಿ = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_ಸೂಚ್ಯಂಕ, 0);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 256; i++) {
            outportb(VGA_DAC_ದತ್ತಾಂಶ, 0);
            outportb(VGA_DAC_ದತ್ತಾಂಶ, 0);
            outportb(VGA_DAC_ದತ್ತಾಂಶ, 0);
        }
    }

    ಹಿಂತಿರುಗಿ surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
ಸ್ಥಿರ bool Create_ಸಾಮಾನ್ಯ_Framebuffer(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                                    SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ = &ದತ್ತಾಂಶ->current_ಬಹುಲಕ;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *mdata = ಬಹುಲಕ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormat surface_format = ಬಹುಲಕ->format;
    ಪೂರ್ಣಾಂಕ w, h;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(ದತ್ತಾಂಶ, w, h, surface_format);
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_Surface *lfb_surface = ಖಾಲಿ;

    ಆದರೆ (!ದತ್ತಾಂಶ->banked_ಬಹುಲಕ) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ_ಪುಟ = ದತ್ತಾಂಶ->ಪುಟ_flip_ಲಭ್ಯ ? (1 - ದತ್ತಾಂಶ->current_ಪುಟ) : 0;
        ಶೂನ್ಯ *lfb_pixels = (Uint8 *)DOS_Physical_ಗಮ್ಯ_ರೇಖೀಯ(ದತ್ತಾಂಶ->mapping.ವಿಳಾಸ) + ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[ಹಿಂಭಾಗ_ಪುಟ];
        lfb_surface = SDL_CreateSurfaceFrom(ಬಹುಲಕ->w, ಬಹುಲಕ->h, surface_format, lfb_pixels, mdata->pitch);
        ಆದರೆ (!lfb_surface) {
            SDL_DestroySurface(surface);
            ಹಿಂತಿರುಗಿ false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        ಆದರೆ (src_palette) {
            SDL_ಗಣ_Surface_Palette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    ಆದರೆ (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_ಗಣ_Surface_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    ಹಿಂತಿರುಗಿ true;
}

bool DOSVESA_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_zero(fb_state);

    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = device->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ = &ದತ್ತಾಂಶ->current_ಬಹುಲಕ;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *mdata = ಬಹುಲಕ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormat surface_format = ಬಹುಲಕ->format;
    ಪೂರ್ಣಾಂಕ w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_ನೇರ_FRAMEBUFFER, false)) {
        ಪೂರ್ಣಾಂಕ vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        ಆದರೆ (mdata->win_a_segment && mdata->win_ಗಾತ್ರ > 0 &&
            (mdata->win_a_ಗುಣಲಕ್ಷಣಗಳು & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ದತ್ತಾಂಶ->banked_ಬಹುಲಕ && ದತ್ತಾಂಶ->mapping.ಗಾತ್ರ_2) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        ಆದರೆ (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(ದತ್ತಾಂಶ, w, h, surface_format);
            ಆದರೆ (!surface) {
                ಹಿಂತಿರುಗಿ false;
            }

            SDL_ಗಣ_Surface_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), DOS_SURFACE, surface);

            fb_state.surface = surface;
            fb_state.ನೇರ_fb = true;
            fb_state.vram_pitch = vram_pitch;
            fb_state.vram_w = mdata->w;
            fb_state.vram_h = mdata->h;
            fb_state.bpp = SDL_BYTESPERPIXEL(surface_format);
            fb_state.pixels = (Uint8 *)surface->pixels;
            fb_state.src_pitch = surface->pitch;
            fb_state.fb_ಗಾತ್ರ = (Uint32)vram_pitch * mdata->h;
            fb_state.pitches_ಹೊಂದಿಕೆ = (surface->pitch == vram_pitch);

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
            ಆದರೆ (mdata->win_a_segment && mdata->win_ಗಾತ್ರ > 0 &&
                (mdata->win_a_ಗುಣಲಕ್ಷಣಗಳು & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_ಬೈಟುಗಳು = (Uint32)mdata->win_ಗಾತ್ರ * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = ಖಾಲಿ;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_ತಳ = fb_state.vram_phys;
                fb_state.win_gran_ಬೈಟುಗಳು = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_ಗಾತ್ರ_ಬೈಟುಗಳು = win_ಬೈಟುಗಳು;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_ಗಾತ್ರ > win_ಬೈಟುಗಳು);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ದತ್ತಾಂಶ->banked_ಬಹುಲಕ && ದತ್ತಾಂಶ->mapping.ಗಾತ್ರ_2) {
                // Fallback: nearptr to LFB.
                ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ_ಪುಟ = ದತ್ತಾಂಶ->ಪುಟ_flip_ಲಭ್ಯ ? (1 - ದತ್ತಾಂಶ->current_ಪುಟ) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_Physical_ಗಮ್ಯ_ರೇಖೀಯ(ದತ್ತಾಂಶ->mapping.ವಿಳಾಸ) + ದತ್ತಾಂಶ->ಪುಟ_ಸ್ಥಾನಾಂತರ[ಹಿಂಭಾಗ_ಪುಟ];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                ಹಿಂತಿರುಗಿ Create_ಸಾಮಾನ್ಯ_Framebuffer(device, ಕಿಟಕಿ, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            ಹಿಂತಿರುಗಿ true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    ಹಿಂತಿರುಗಿ Create_ಸಾಮಾನ್ಯ_Framebuffer(device, ಕಿಟಕಿ, format, pixels, pitch);
}

bool DOSVESA_ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ vsync)
{
    ಆದರೆ (vsync < 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unsupported vsync type");
    }
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ದತ್ತಾಂಶ->framebuffer_vsync = vsync;
    ಹಿಂತಿರುಗಿ true;
}

bool DOSVESA_Get_ಕಿಟಕಿ_Framebuffer_VSync(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *vsync)
{
    ಆದರೆ (vsync) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        *vsync = ದತ್ತಾಂಶ->framebuffer_vsync;
    }
    ಹಿಂತಿರುಗಿ true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE ಶೂನ್ಯ SwitchBank(ಪೂರ್ಣಾಂಕ bank, ಪೂರ್ಣಾಂಕ *current_bank, Uint32 win_func_ptr)
{
    ಆದರೆ (bank == *current_bank) {
        ಹಿಂತಿರುಗಿ;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    ಆದರೆ (win_func_ptr) {
        regs.x.cs = (Uint16)(win_func_ptr >> 16);
        regs.x.ip = (Uint16)(win_func_ptr & 0xFFFF);
        __dpmi_simulate_real_mode_procedure_retf(&regs);
    } ಇಲ್ಲದಿದ್ದರೆ {
        regs.x.ax = 0x4F05;
        __dpmi_int(0x10, &regs);
    }
    *current_bank = bank;
}

// Copy a contiguous byte range from system RAM to VRAM through the banked
// window, switching banks as needed.
SDL_FORCE_INLINE ಶೂನ್ಯ BankedDosmemput(ಸ್ಥಿರಾಂಕ Uint8 *src, Uint32 ಒಟ್ಟು_ಬೈಟುಗಳು, Uint32 dst_ಸ್ಥಾನಾಂತರ,
                                      Uint32 win_gran_ಬೈಟುಗಳು, Uint32 win_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                      Uint32 win_ತಳ, Uint32 win_func_ptr,
                                      ಪೂರ್ಣಾಂಕ *current_bank)
{
    Uint32 src_off = 0;
    ಆಗ (ಒಟ್ಟು_ಬೈಟುಗಳು > 0) {
        ಪೂರ್ಣಾಂಕ bank = (ಪೂರ್ಣಾಂಕ)(dst_ಸ್ಥಾನಾಂತರ / win_gran_ಬೈಟುಗಳು);
        Uint32 off_ಒಳ_win = dst_ಸ್ಥಾನಾಂತರ % win_gran_ಬೈಟುಗಳು;
        Uint32 avail = win_ಗಾತ್ರ_ಬೈಟುಗಳು - off_ಒಳ_win;
        Uint32 n = ಒಟ್ಟು_ಬೈಟುಗಳು;
        ಆದರೆ (n > avail) {
            n = avail;
        }
        SwitchBank(bank, current_bank, win_func_ptr);
        dosmemput(src + src_off, n, win_ತಳ + off_ಒಳ_win);
        src_off += n;
        dst_ಸ್ಥಾನಾಂತರ += n;
        ಒಟ್ಟು_ಬೈಟುಗಳು -= n;
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
ಸ್ಥಿರ ಶೂನ್ಯ BankedFramebufferCopyRect(ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *mdata,
                                      ಸ್ಥಿರಾಂಕ SDL_Surface *src,
                                      ಸ್ಥಿರಾಂಕ SDL_Rect *src_rect,
                                      ಪೂರ್ಣಾಂಕ dst_x, ಪೂರ್ಣಾಂಕ dst_y,
                                      Uint32 win_gran_ಬೈಟುಗಳು,
                                      Uint32 win_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                      Uint32 win_ತಳ,
                                      ಪೂರ್ಣಾಂಕ *current_bank,
                                      Uint32 win_func_ptr)
{
    ಸ್ಥಿರಾಂಕ Uint16 dst_pitch = mdata->pitch;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_ಪ್ರತಿ_pixel = SDL_BYTESPERPIXEL(src->format);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು_ಬೈಟುಗಳು = src_rect->w * ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    ಆದರೆ (ಅಡ್ಡಸಾಲು_ಬೈಟುಗಳು == src->pitch && ಅಡ್ಡಸಾಲು_ಬೈಟುಗಳು == dst_pitch) {
        ಸ್ಥಿರಾಂಕ Uint8 *src_ದತ್ತಾಂಶ = (ಸ್ಥಿರಾಂಕ Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        Uint32 dst_ಸ್ಥಾನಾಂತರ = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        BankedDosmemput(src_ದತ್ತಾಂಶ, (Uint32)(ಅಡ್ಡಸಾಲು_ಬೈಟುಗಳು * src_rect->h), dst_ಸ್ಥಾನಾಂತರ,
                        win_gran_ಬೈಟುಗಳು, win_ಗಾತ್ರ_ಬೈಟುಗಳು, win_ತಳ, win_func_ptr, current_bank);
        ಹಿಂತಿರುಗಿ;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = 0; y < src_rect->h; y++) {
        ಸ್ಥಿರಾಂಕ Uint8 *src_ಅಡ್ಡಸಾಲು = (ಸ್ಥಿರಾಂಕ Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        Uint32 dst_ಸ್ಥಾನಾಂತರ = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
        BankedDosmemput(src_ಅಡ್ಡಸಾಲು, (Uint32)ಅಡ್ಡಸಾಲು_ಬೈಟುಗಳು, dst_ಸ್ಥಾನಾಂತರ,
                        win_gran_ಬೈಟುಗಳು, win_ಗಾತ್ರ_ಬೈಟುಗಳು, win_ತಳ, win_func_ptr, current_bank);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ WaitForVBlank(ಶೂನ್ಯ)
{
    ಆಗ (inportb(VGA_ಸ್ಥಿತಿ_ಪೋರ್ಟ್) & VGA_ಸ್ಥಿತಿ_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    ಆಗ (!(inportb(VGA_ಸ್ಥಿತಿ_ಪೋರ್ಟ್) & VGA_ಸ್ಥಿತಿ_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಕಾರ್ಯಕ್ರಮ_VGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_ಸೂಚ್ಯಂಕ, 0);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_ದತ್ತಾಂಶ, palette->colors[i].r >> 2);
        outportb(VGA_DAC_ದತ್ತಾಂಶ, palette->colors[i].g >> 2);
        outportb(VGA_DAC_ದತ್ತಾಂಶ, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    SDL_Video_ದತ್ತಾಂಶ *vdata = device->ಆಂತರಿಕ;

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
    ಆದರೆ (fb_state.ನೇರ_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        ಆದರೆ (ಕಿಟಕಿ->surface) {
            SDL_Palette *pal = ಕಿಟಕಿ->surface->palette;
            ಆದರೆ (pal && pal->ಆವೃತ್ತಿ != vdata->palette_ಆವೃತ್ತಿ) {
                vdata->palette_ಆವೃತ್ತಿ = pal->ಆವೃತ್ತಿ;
                ಕಾರ್ಯಕ್ರಮ_VGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        ಆದರೆ (numrects <= 0) {
            ಹಿಂತಿರುಗಿ true;
        }

        ಆದರೆ (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_pitch = fb_state.src_pitch;
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_pitch = fb_state.vram_pitch;
            ಸ್ಥಿರಾಂಕ Uint8 *pixels = fb_state.pixels;

            ಆದರೆ (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                ಆದರೆ (fb_state.pitches_ಹೊಂದಿಕೆ) {
                    dosmemput(pixels, fb_state.fb_ಗಾತ್ರ, fb_state.vram_phys);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < numrects; i++) {
                        ಪೂರ್ಣಾಂಕ rx = rects[i].x, ry = rects[i].y;
                        ಪೂರ್ಣಾಂಕ rw = rects[i].w, rh = rects[i].h;
                        ಆದರೆ (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        ಆದರೆ (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        ಆದರೆ (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        ಆದರೆ (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        ಆದರೆ (rw <= 0 || rh <= 0) {
                            ಮುಂದುವರಿ;
                        }
                        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bx = rx * fb_state.bpp;
                        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bw = rw * fb_state.bpp;
                        ಸ್ಥಿರಾಂಕ Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು = 0; ಅಡ್ಡಸಾಲು < rh; ಅಡ್ಡಸಾಲು++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Multi-bank: bank-switch as needed.
                ಸ್ಥಿರಾಂಕ Uint32 gran = fb_state.win_gran_ಬೈಟುಗಳು;
                ಸ್ಥಿರಾಂಕ Uint32 wsize = fb_state.win_ಗಾತ್ರ_ಬೈಟುಗಳು;
                ಸ್ಥಿರಾಂಕ Uint32 wbase = fb_state.win_ತಳ;
                ಸ್ಥಿರಾಂಕ Uint32 wfunc = fb_state.win_func_ptr;
                ಪೂರ್ಣಾಂಕ current_bank = -1;

                ಆದರೆ (fb_state.pitches_ಹೊಂದಿಕೆ) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_ಗಾತ್ರ, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    // Per-rect with bank switching.
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < numrects; i++) {
                        ಪೂರ್ಣಾಂಕ rx = rects[i].x, ry = rects[i].y;
                        ಪೂರ್ಣಾಂಕ rw = rects[i].w, rh = rects[i].h;
                        ಆದರೆ (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        ಆದರೆ (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        ಆದರೆ (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        ಆದರೆ (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        ಆದರೆ (rw <= 0 || rh <= 0) {
                            ಮುಂದುವರಿ;
                        }
                        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bx = rx * fb_state.bpp;
                        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bw = rw * fb_state.bpp;

                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು = 0; ಅಡ್ಡಸಾಲು < rh; ಅಡ್ಡಸಾಲು++) {
                            ಸ್ಥಿರಾಂಕ Uint8 *sp = pixels + (ry + ಅಡ್ಡಸಾಲು) * src_pitch + bx;
                            Uint32 dst_ಸ್ಥಾನಾಂತರ = (Uint32)(ry + ಅಡ್ಡಸಾಲು) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_ಸ್ಥಾನಾಂತರ,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            // nearptr path (LFB fallback)
            ಆದರೆ (fb_state.pitches_ಹೊಂದಿಕೆ) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_ಗಾತ್ರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bpp = fb_state.bpp;
                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ src_pitch = fb_state.src_pitch;
                ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_pitch = fb_state.vram_pitch;
                ಸ್ಥಿರಾಂಕ Uint8 *pixels = fb_state.pixels;

                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < numrects; i++) {
                    ಪೂರ್ಣಾಂಕ rx = rects[i].x, ry = rects[i].y;
                    ಪೂರ್ಣಾಂಕ rw = rects[i].w, rh = rects[i].h;
                    ಆದರೆ (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    ಆದರೆ (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    ಆದರೆ (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    ಆದರೆ (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    ಆದರೆ (rw <= 0 || rh <= 0) {
                        ಮುಂದುವರಿ;
                    }
                    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bw = rw * bpp;
                    ಸ್ಥಿರಾಂಕ Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು = 0; ಅಡ್ಡಸಾಲು < rh; ಅಡ್ಡಸಾಲು++) {
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
        ಆದರೆ (!fb_state.use_dosmemput && vdata->ಪುಟ_flip_ಲಭ್ಯ) {
            ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *mdata = vdata->current_ಬಹುಲಕ.ಆಂತರಿಕ;
            ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ_ಪುಟ = 1 - vdata->current_ಪುಟ;
            Uint16 ಮೊದಲ_scanline = (Uint16)(vdata->ಪುಟ_ಸ್ಥಾನಾಂತರ[ಹಿಂಭಾಗ_ಪುಟ] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = ಮೊದಲ_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_ಪುಟ = ಹಿಂಭಾಗ_ಪುಟ;

            ಪೂರ್ಣಾಂಕ new_ಹಿಂಭಾಗ = 1 - vdata->current_ಪುಟ;
            fb_state.vram_ptr = (Uint8 *)DOS_Physical_ಗಮ್ಯ_ರೇಖೀಯ(vdata->mapping.ವಿಳಾಸ) + vdata->ಪುಟ_ಸ್ಥಾನಾಂತರ[new_ಹಿಂಭಾಗ];
        }

        ಹಿಂತಿರುಗಿ true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    ಆದರೆ (!src) {
        src = (SDL_Surface *)SDL_Get_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), DOS_SURFACE, ಖಾಲಿ);
    }
    ಆದರೆ (!src) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find DOS surface for window");
    }

    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *mdata = vdata->current_ಬಹುಲಕ.ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windata = ಕಿಟಕಿ->ಆಂತರಿಕ;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = ಖಾಲಿ;
    bool dac_needs_update = false;

    ಆದರೆ (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = ಕಿಟಕಿ->surface ? SDL_GetSurfacePalette(ಕಿಟಕಿ->surface) : ಖಾಲಿ;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        ಆದರೆ (win_palette && src_palette && win_palette != src_palette &&
            win_palette->ಆವೃತ್ತಿ != src_palette->ಆವೃತ್ತಿ) {
            SDL_ಗಣ_Palette_Colors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            ಆದರೆ (!vdata->banked_ಬಹುಲಕ && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                ಆದರೆ (dst_palette && dst_palette != src_palette) {
                    SDL_ಗಣ_Palette_Colors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        ಆದರೆ (dac_palette && dac_palette->ಆವೃತ್ತಿ != vdata->palette_ಆವೃತ್ತಿ) {
            dac_needs_update = true;
        }
    }

    ಆದರೆ (vdata->banked_ಬಹುಲಕ) {
        // --- Banked framebuffer path (dirty-rect aware) ---
        // We composite the cursor onto the source surface (in system RAM),
        // then bank-copy only the dirty rectangles to the VGA window.  We
        // need to undo the cursor composite afterwards so the app's surface
        // isn't permanently modified.

        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_x = ((ಪೂರ್ಣಾಂಕ)mdata->w - src->w) / 2;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ dst_y = ((ಪೂರ್ಣಾಂಕ)mdata->h - src->h) / 2;

        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = ಖಾಲಿ;
        SDL_Rect cursorrect;
        SDL_Rect cursor_clipped; // cursorrect clipped to src bounds
        SDL_Surface *cursor_save = ಖಾಲಿ;
        bool have_cursor_rect = false;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : ಖಾಲಿ;
        ಆದರೆ (cur && cur->animation) {
            cur = cur->animation->ಚೌಕಟ್ಟುಗಳು[cur->animation->current_ಚೌಕಟ್ಟು];
        }
        ಆದರೆ (mouse && mouse->ಆಂತರಿಕ && !mouse->relative_ಬಹುಲಕ && mouse->cursor_visible && cur && cur->ಆಂತರಿಕ) {
            cursor = cur->ಆಂತರಿಕ->surface;
            ಆದರೆ (cursor) {
                cursorrect.x = SDL_clamp((ಪೂರ್ಣಾಂಕ)mouse->x, 0, ಕಿಟಕಿ->w) - cur->ಆಂತರಿಕ->hot_x;
                cursorrect.y = SDL_clamp((ಪೂರ್ಣಾಂಕ)mouse->y, 0, ಕಿಟಕಿ->h) - cur->ಆಂತರಿಕ->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                ಆದರೆ (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                ಆದರೆ (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                ಆದರೆ (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                ಆದರೆ (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                ಆದರೆ (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    ಆದರೆ (cursor_save) {
                        ಆದರೆ (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            ಆದರೆ (sp) {
                                SDL_ಗಣ_Surface_Palette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, ಖಾಲಿ);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->ಆಂತರಿಕ, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, ಖಾಲಿ, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ vsync_interval = windata->framebuffer_vsync;
        ಆದರೆ (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        ಆದರೆ (dac_needs_update) {
            vdata->palette_ಆವೃತ್ತಿ = dac_palette->ಆವೃತ್ತಿ;
            ಕಾರ್ಯಕ್ರಮ_VGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        ಸ್ಥಿರಾಂಕ Uint32 win_gran_ಬೈಟುಗಳು = (Uint32)mdata->win_granularity * 1024;
        ಸ್ಥಿರಾಂಕ Uint32 win_ಗಾತ್ರ_ಬೈಟುಗಳು = (Uint32)mdata->win_ಗಾತ್ರ * 1024;
        ಸ್ಥಿರಾಂಕ Uint32 win_ತಳ = (Uint32)mdata->win_a_segment << 4;
        ಪೂರ್ಣಾಂಕ current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            ಆದರೆ (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            ಆದರೆ (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            ಆದರೆ (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            ಆದರೆ (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            ಆದರೆ (rect.w <= 0 || rect.h <= 0) {
                ಮುಂದುವರಿ;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            ಆದರೆ (have_cursor_rect && !cursor_covered) {
                ಆದರೆ (rect.x <= cursor_clipped.x &&
                    rect.y <= cursor_clipped.y &&
                    rect.x + rect.w >= cursor_clipped.x + cursor_clipped.w &&
                    rect.y + rect.h >= cursor_clipped.y + cursor_clipped.h) {
                    cursor_covered = true;
                }
            }

            BankedFramebufferCopyRect(mdata, src, &rect, dst_x, dst_y,
                                      win_gran_ಬೈಟುಗಳು, win_ಗಾತ್ರ_ಬೈಟುಗಳು, win_ತಳ,
                                      &current_bank, mdata->win_func_ptr);
        }

        // If no dirty rect covered the cursor, copy the cursor region separately.
        ಆದರೆ (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_ಬೈಟುಗಳು, win_ಗಾತ್ರ_ಬೈಟುಗಳು, win_ತಳ,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        ಆದರೆ (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, ಖಾಲಿ, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } ಇಲ್ಲದಿದ್ದರೆ {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        ಆದರೆ (!dst) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find VESA linear framebuffer surface for window");
        }

        ಸ್ಥಿರಾಂಕ SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = ಖಾಲಿ;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : ಖಾಲಿ;
        ಆದರೆ (cur && cur->animation) {
            cur = cur->animation->ಚೌಕಟ್ಟುಗಳು[cur->animation->current_ಚೌಕಟ್ಟು];
        }
        ಆದರೆ (mouse && mouse->ಆಂತರಿಕ && !mouse->relative_ಬಹುಲಕ && mouse->cursor_visible && cur && cur->ಆಂತರಿಕ) {
            cursor = cur->ಆಂತರಿಕ->surface;
            ಆದರೆ (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((ಪೂರ್ಣಾಂಕ)mouse->x, 0, ಕಿಟಕಿ->w) - cur->ಆಂತರಿಕ->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((ಪೂರ್ಣಾಂಕ)mouse->y, 0, ಕಿಟಕಿ->h) - cur->ಆಂತರಿಕ->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        ಆದರೆ (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            ಸ್ಥಿರಾಂಕ Uint8 *sp = (ಸ್ಥಿರಾಂಕ Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            ಆದರೆ (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು = 0; ಅಡ್ಡಸಾಲು < dstrect.h; ಅಡ್ಡಸಾಲು++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Blit to the back page (or the only page, if no page-flipping)
            ಆದರೆ (!SDL_BlitSurface(src, ಖಾಲಿ, dst, &dstrect)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }

        ಆದರೆ (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->ಆಂತರಿಕ, dst);
            ಆದರೆ (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, ಖಾಲಿ, dst, &cursorrect)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }

        ಆದರೆ (vdata->ಪುಟ_flip_ಲಭ್ಯ) {
            // Page-flip with optional vsync.
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ vsync_interval = windata->framebuffer_vsync;
            ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ_ಪುಟ = 1 - vdata->current_ಪುಟ;
            Uint16 ಮೊದಲ_scanline = (Uint16)(vdata->ಪುಟ_ಸ್ಥಾನಾಂತರ[ಹಿಂಭಾಗ_ಪುಟ] / mdata->pitch);

            ಆದರೆ (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            ಆದರೆ (dac_needs_update) {
                vdata->palette_ಆವೃತ್ತಿ = dac_palette->ಆವೃತ್ತಿ;
                ಕಾರ್ಯಕ್ರಮ_VGADAC(dac_palette);
            }

            // Flip: make the back page (which we just drew to) the visible page.
            // Always use subfunction 0x0080 (set display start, don't wait) —
            // vsync is controlled by our manual vblank wait above.
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0; // first pixel in scan line
            regs.x.dx = ಮೊದಲ_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_ಪುಟ = ಹಿಂಭಾಗ_ಪುಟ;

            // Update LFB surface to point at the new back page (the old front page)
            ಪೂರ್ಣಾಂಕ new_ಹಿಂಭಾಗ = 1 - vdata->current_ಪುಟ;
            dst->pixels = (Uint8 *)DOS_Physical_ಗಮ್ಯ_ರೇಖೀಯ(vdata->mapping.ವಿಳಾಸ) + vdata->ಪುಟ_ಸ್ಥಾನಾಂತರ[new_ಹಿಂಭಾಗ];
        } ಇಲ್ಲದಿದ್ದರೆ {
            // No page-flipping: wait for vsync, then update DAC atomically
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ vsync_interval = windata->framebuffer_vsync;
            ಆದರೆ (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            ಆದರೆ (dac_needs_update) {
                vdata->palette_ಆವೃತ್ತಿ = dac_palette->ಆವೃತ್ತಿ;
                ಕಾರ್ಯಕ್ರಮ_VGADAC(dac_palette);
            }
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ DOSVESA_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *device, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (ಶೂನ್ಯ)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), DOS_SURFACE);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_DOSVESA

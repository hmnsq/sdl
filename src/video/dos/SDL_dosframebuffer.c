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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_DOSVESA

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
#وصف_ڪريو DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
تعريفنوع بنية DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool سڌو_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    صحيح vram_pitch;
    صحيح vram_w;
    صحيح vram_h;
    صحيح bpp; // bytes per pixel

    // dosmemput path state (use_dosmemput)
    Uint32 vram_phys;      // base address for dosmemput (e.g. 0xA0000)
    bool banked_multibank; // true if fb doesn't fit in one bank window
    Uint32 win_gran_بائيٽون; // bank granularity in bytes
    Uint32 win_سائيز_بائيٽون; // bank window size in bytes
    Uint32 win_بنياد;       // window base address (segment << 4)
    Uint32 win_func_ptr;   // real-mode far pointer to bank-switch function

    // nearptr path state (use_dosmemput == false)
    Uint8 *vram_ptr; // nearptr into VRAM (LFB)

    // Cached per-frame values (set at create time, avoid repeated lookups)
    Uint8 *pixels;      // == surface->pixels (stable after create)
    صحيح src_pitch;      // == surface->pitch
    Uint32 fb_سائيز;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_ميلاپ; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

ساكن DOSFramebufferState fb_state;

// Convert cursor to the current format.
ساكن SDL_Surface *GetConvertedCursorSurface(SDL_Cursor_معلومات *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    إذا (!pal) {
        أرجع عدم;
    }

    Uint32 pal_نسخو = pal ? pal->نسخو : 0;

    إذا (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_نسخو == pal_نسخو) {
        أرجع curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = عدم;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    صحيح w = src->w;
    صحيح h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    إذا (!conv) {
        أرجع عدم;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    إذا (conv_pal) {
        SDL_سيٽ_Palette_Colors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool استعمال_ٿيل[256];
    SDL_zeroa(استعمال_ٿيل);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_سيٽ_Surface_Blend_گهڻائي(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, عدم, conv, عدم);
    SDL_سيٽ_Surface_Blend_گهڻائي(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    لكل (صحيح y = 0; y < h; y++) {
        ثابت Uint32 *srcrow = (ثابت Uint32 *)((ثابت Uint8 *)src->pixels + y * src->pitch);
        ثابت Uint8 *convrow = (ثابت Uint8 *)conv->pixels + y * conv->pitch;
        لكل (صحيح x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            إذا (srcA > 0) {
                استعمال_ٿيل[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    لكل (صحيح i = 0; i < 256; i++) {
        إذا (!استعمال_ٿيل[i]) {
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
            إذا (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_سيٽ_Surface_Color_ڪنجي(conv, true, colorkey);
    SDL_سيٽ_Surface_Blend_گهڻائي(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_نسخو = pal_نسخو;
    أرجع conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
فراغ DOSVESA_InvalidateCachedFramebuffer(فراغ)
{
    fb_state.سڌو_fb = false;
    fb_state.vram_ptr = عدم;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = عدم;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
ساكن SDL_Surface *CreateSystemSurface(SDL_Video_معلومات *معلومات, صحيح w, صحيح h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    إذا (!surface) {
        أرجع عدم;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    إذا (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        إذا (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            لكل (صحيح i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_سيٽ_Palette_Colors(palette, black, 0, 256);
        }
        معلومات->palette_نسخو = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_اشاريو, 0);
        لكل (صحيح i = 0; i < 256; i++) {
            outportb(VGA_DAC_معلومات, 0);
            outportb(VGA_DAC_معلومات, 0);
            outportb(VGA_DAC_معلومات, 0);
        }
    }

    أرجع surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
ساكن bool Create_عام_Framebuffer(SDL_VideoDevice *device, SDL_دري *دري,
                                    SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_Video_معلومات *معلومات = device->اندروني;
    ثابت SDL_Display_گهڻائي *گهڻائي = &معلومات->current_گهڻائي;
    ثابت SDL_Display_گهڻائي_معلومات *mdata = گهڻائي->اندروني;
    ثابت SDL_PixelFormat surface_format = گهڻائي->format;
    صحيح w, h;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(معلومات, w, h, surface_format);
    إذا (!surface) {
        أرجع false;
    }

    SDL_Surface *lfb_surface = عدم;

    إذا (!معلومات->banked_گهڻائي) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        صحيح پٺ_صفحو = معلومات->صفحو_flip_موجود ? (1 - معلومات->current_صفحو) : 0;
        فراغ *lfb_pixels = (Uint8 *)DOS_Physical_منزل_لڪيري(معلومات->mapping.پتو) + معلومات->صفحو_وٿي[پٺ_صفحو];
        lfb_surface = SDL_CreateSurfaceFrom(گهڻائي->w, گهڻائي->h, surface_format, lfb_pixels, mdata->pitch);
        إذا (!lfb_surface) {
            SDL_DestroySurface(surface);
            أرجع false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        إذا (src_palette) {
            SDL_سيٽ_Surface_Palette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    إذا (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_سيٽ_Surface_Property(SDL_Get_دري_Properties(دري), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    أرجع true;
}

bool DOSVESA_Create_دري_Framebuffer(SDL_VideoDevice *device, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_zero(fb_state);

    SDL_Video_معلومات *معلومات = device->اندروني;
    ثابت SDL_Display_گهڻائي *گهڻائي = &معلومات->current_گهڻائي;
    ثابت SDL_Display_گهڻائي_معلومات *mdata = گهڻائي->اندروني;
    ثابت SDL_PixelFormat surface_format = گهڻائي->format;
    صحيح w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    إذا (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_سڌو_FRAMEBUFFER, false)) {
        صحيح vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        إذا (mdata->win_a_segment && mdata->win_سائيز > 0 &&
            (mdata->win_a_خاصيتون & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } وإلا إذا (!معلومات->banked_گهڻائي && معلومات->mapping.سائيز) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        إذا (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(معلومات, w, h, surface_format);
            إذا (!surface) {
                أرجع false;
            }

            SDL_سيٽ_Surface_Property(SDL_Get_دري_Properties(دري), DOS_SURFACE, surface);

            fb_state.surface = surface;
            fb_state.سڌو_fb = true;
            fb_state.vram_pitch = vram_pitch;
            fb_state.vram_w = mdata->w;
            fb_state.vram_h = mdata->h;
            fb_state.bpp = SDL_BYTESPERPIXEL(surface_format);
            fb_state.pixels = (Uint8 *)surface->pixels;
            fb_state.src_pitch = surface->pitch;
            fb_state.fb_سائيز = (Uint32)vram_pitch * mdata->h;
            fb_state.pitches_ميلاپ = (surface->pitch == vram_pitch);

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
            إذا (mdata->win_a_segment && mdata->win_سائيز > 0 &&
                (mdata->win_a_خاصيتون & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_بائيٽون = (Uint32)mdata->win_سائيز * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = عدم;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_بنياد = fb_state.vram_phys;
                fb_state.win_gran_بائيٽون = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_سائيز_بائيٽون = win_بائيٽون;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_سائيز > win_بائيٽون);
            } وإلا إذا (!معلومات->banked_گهڻائي && معلومات->mapping.سائيز) {
                // Fallback: nearptr to LFB.
                صحيح پٺ_صفحو = معلومات->صفحو_flip_موجود ? (1 - معلومات->current_صفحو) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_Physical_منزل_لڪيري(معلومات->mapping.پتو) + معلومات->صفحو_وٿي[پٺ_صفحو];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } وإلا {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                أرجع Create_عام_Framebuffer(device, دري, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            أرجع true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    أرجع Create_عام_Framebuffer(device, دري, format, pixels, pitch);
}

bool DOSVESA_سيٽ_دري_Framebuffer_VSync(SDL_VideoDevice *device, SDL_دري *دري, صحيح vsync)
{
    إذا (vsync < 0) {
        أرجع SDL_سيٽ_Error("Unsupported vsync type");
    }
    SDL_دري_معلومات *معلومات = دري->اندروني;
    معلومات->framebuffer_vsync = vsync;
    أرجع true;
}

bool DOSVESA_Get_دري_Framebuffer_VSync(SDL_VideoDevice *device, SDL_دري *دري, صحيح *vsync)
{
    إذا (vsync) {
        SDL_دري_معلومات *معلومات = دري->اندروني;
        *vsync = معلومات->framebuffer_vsync;
    }
    أرجع true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE فراغ SwitchBank(صحيح bank, صحيح *current_bank, Uint32 win_func_ptr)
{
    إذا (bank == *current_bank) {
        أرجع;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    إذا (win_func_ptr) {
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
SDL_FORCE_INLINE فراغ BankedDosmemput(ثابت Uint8 *src, Uint32 ڪل_بائيٽون, Uint32 dst_وٿي,
                                      Uint32 win_gran_بائيٽون, Uint32 win_سائيز_بائيٽون,
                                      Uint32 win_بنياد, Uint32 win_func_ptr,
                                      صحيح *current_bank)
{
    Uint32 src_off = 0;
    طالما (ڪل_بائيٽون > 0) {
        صحيح bank = (صحيح)(dst_وٿي / win_gran_بائيٽون);
        Uint32 off_اندريون_win = dst_وٿي % win_gran_بائيٽون;
        Uint32 avail = win_سائيز_بائيٽون - off_اندريون_win;
        Uint32 n = ڪل_بائيٽون;
        إذا (n > avail) {
            n = avail;
        }
        SwitchBank(bank, current_bank, win_func_ptr);
        dosmemput(src + src_off, n, win_بنياد + off_اندريون_win);
        src_off += n;
        dst_وٿي += n;
        ڪل_بائيٽون -= n;
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
ساكن فراغ BankedFramebufferCopyRect(ثابت SDL_Display_گهڻائي_معلومات *mdata,
                                      ثابت SDL_Surface *src,
                                      ثابت SDL_Rect *src_rect,
                                      صحيح dst_x, صحيح dst_y,
                                      Uint32 win_gran_بائيٽون,
                                      Uint32 win_سائيز_بائيٽون,
                                      Uint32 win_بنياد,
                                      صحيح *current_bank,
                                      Uint32 win_func_ptr)
{
    ثابت Uint16 dst_pitch = mdata->pitch;
    ثابت صحيح بائيٽون_في_pixel = SDL_BYTESPERPIXEL(src->format);
    ثابت صحيح صف_بائيٽون = src_rect->w * بائيٽون_في_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    إذا (صف_بائيٽون == src->pitch && صف_بائيٽون == dst_pitch) {
        ثابت Uint8 *src_معلومات = (ثابت Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * بائيٽون_في_pixel;
        Uint32 dst_وٿي = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * بائيٽون_في_pixel;
        BankedDosmemput(src_معلومات, (Uint32)(صف_بائيٽون * src_rect->h), dst_وٿي,
                        win_gran_بائيٽون, win_سائيز_بائيٽون, win_بنياد, win_func_ptr, current_bank);
        أرجع;
    }

    لكل (صحيح y = 0; y < src_rect->h; y++) {
        ثابت Uint8 *src_صف = (ثابت Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * بائيٽون_في_pixel;
        Uint32 dst_وٿي = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * بائيٽون_في_pixel;
        BankedDosmemput(src_صف, (Uint32)صف_بائيٽون, dst_وٿي,
                        win_gran_بائيٽون, win_سائيز_بائيٽون, win_بنياد, win_func_ptr, current_bank);
    }
}

ساكن فراغ WaitForVBlank(فراغ)
{
    طالما (inportb(VGA_حالت_پورٽ) & VGA_حالت_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    طالما (!(inportb(VGA_حالت_پورٽ) & VGA_حالت_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

ساكن فراغ پروگرام_VGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_اشاريو, 0);
    لكل (صحيح i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_معلومات, palette->colors[i].r >> 2);
        outportb(VGA_DAC_معلومات, palette->colors[i].g >> 2);
        outportb(VGA_DAC_معلومات, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_Update_دري_Framebuffer(SDL_VideoDevice *device, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_Video_معلومات *vdata = device->اندروني;

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
    إذا (fb_state.سڌو_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        إذا (دري->surface) {
            SDL_Palette *pal = دري->surface->palette;
            إذا (pal && pal->نسخو != vdata->palette_نسخو) {
                vdata->palette_نسخو = pal->نسخو;
                پروگرام_VGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        إذا (numrects <= 0) {
            أرجع true;
        }

        إذا (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            ثابت صحيح src_pitch = fb_state.src_pitch;
            ثابت صحيح dst_pitch = fb_state.vram_pitch;
            ثابت Uint8 *pixels = fb_state.pixels;

            إذا (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                إذا (fb_state.pitches_ميلاپ) {
                    dosmemput(pixels, fb_state.fb_سائيز, fb_state.vram_phys);
                } وإلا {
                    لكل (صحيح i = 0; i < numrects; i++) {
                        صحيح rx = rects[i].x, ry = rects[i].y;
                        صحيح rw = rects[i].w, rh = rects[i].h;
                        إذا (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        إذا (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        إذا (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        إذا (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        إذا (rw <= 0 || rh <= 0) {
                            استمر;
                        }
                        ثابت صحيح bx = rx * fb_state.bpp;
                        ثابت صحيح bw = rw * fb_state.bpp;
                        ثابت Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        لكل (صحيح صف = 0; صف < rh; صف++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } وإلا {
                // Multi-bank: bank-switch as needed.
                ثابت Uint32 gran = fb_state.win_gran_بائيٽون;
                ثابت Uint32 wsize = fb_state.win_سائيز_بائيٽون;
                ثابت Uint32 wbase = fb_state.win_بنياد;
                ثابت Uint32 wfunc = fb_state.win_func_ptr;
                صحيح current_bank = -1;

                إذا (fb_state.pitches_ميلاپ) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_سائيز, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } وإلا {
                    // Per-rect with bank switching.
                    لكل (صحيح i = 0; i < numrects; i++) {
                        صحيح rx = rects[i].x, ry = rects[i].y;
                        صحيح rw = rects[i].w, rh = rects[i].h;
                        إذا (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        إذا (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        إذا (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        إذا (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        إذا (rw <= 0 || rh <= 0) {
                            استمر;
                        }
                        ثابت صحيح bx = rx * fb_state.bpp;
                        ثابت صحيح bw = rw * fb_state.bpp;

                        لكل (صحيح صف = 0; صف < rh; صف++) {
                            ثابت Uint8 *sp = pixels + (ry + صف) * src_pitch + bx;
                            Uint32 dst_وٿي = (Uint32)(ry + صف) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_وٿي,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } وإلا {
            // nearptr path (LFB fallback)
            إذا (fb_state.pitches_ميلاپ) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_سائيز);
            } وإلا {
                ثابت صحيح bpp = fb_state.bpp;
                ثابت صحيح src_pitch = fb_state.src_pitch;
                ثابت صحيح dst_pitch = fb_state.vram_pitch;
                ثابت Uint8 *pixels = fb_state.pixels;

                لكل (صحيح i = 0; i < numrects; i++) {
                    صحيح rx = rects[i].x, ry = rects[i].y;
                    صحيح rw = rects[i].w, rh = rects[i].h;
                    إذا (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    إذا (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    إذا (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    إذا (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    إذا (rw <= 0 || rh <= 0) {
                        استمر;
                    }
                    ثابت صحيح bw = rw * bpp;
                    ثابت Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    لكل (صحيح صف = 0; صف < rh; صف++) {
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
        إذا (!fb_state.use_dosmemput && vdata->صفحو_flip_موجود) {
            ثابت SDL_Display_گهڻائي_معلومات *mdata = vdata->current_گهڻائي.اندروني;
            صحيح پٺ_صفحو = 1 - vdata->current_صفحو;
            Uint16 پهريون_scanline = (Uint16)(vdata->صفحو_وٿي[پٺ_صفحو] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = پهريون_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_صفحو = پٺ_صفحو;

            صحيح new_پٺ = 1 - vdata->current_صفحو;
            fb_state.vram_ptr = (Uint8 *)DOS_Physical_منزل_لڪيري(vdata->mapping.پتو) + vdata->صفحو_وٿي[new_پٺ];
        }

        أرجع true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    إذا (!src) {
        src = (SDL_Surface *)SDL_Get_اشارو_Property(SDL_Get_دري_Properties(دري), DOS_SURFACE, عدم);
    }
    إذا (!src) {
        أرجع SDL_سيٽ_Error("Couldn't find DOS surface for window");
    }

    ثابت SDL_Display_گهڻائي_معلومات *mdata = vdata->current_گهڻائي.اندروني;
    SDL_دري_معلومات *windata = دري->اندروني;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = عدم;
    bool dac_needs_update = false;

    إذا (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = دري->surface ? SDL_GetSurfacePalette(دري->surface) : عدم;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        إذا (win_palette && src_palette && win_palette != src_palette &&
            win_palette->نسخو != src_palette->نسخو) {
            SDL_سيٽ_Palette_Colors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            إذا (!vdata->banked_گهڻائي && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                إذا (dst_palette && dst_palette != src_palette) {
                    SDL_سيٽ_Palette_Colors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        إذا (dac_palette && dac_palette->نسخو != vdata->palette_نسخو) {
            dac_needs_update = true;
        }
    }

    إذا (vdata->banked_گهڻائي) {
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
        إذا (cur && cur->animation) {
            cur = cur->animation->چوکٺا[cur->animation->current_چوکٺو];
        }
        إذا (mouse && mouse->اندروني && !mouse->relative_گهڻائي && mouse->cursor_visible && cur && cur->اندروني) {
            cursor = cur->اندروني->surface;
            إذا (cursor) {
                cursorrect.x = SDL_clamp((صحيح)mouse->x, 0, دري->w) - cur->اندروني->hot_x;
                cursorrect.y = SDL_clamp((صحيح)mouse->y, 0, دري->h) - cur->اندروني->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                إذا (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                إذا (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                إذا (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                إذا (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                إذا (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    إذا (cursor_save) {
                        إذا (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            إذا (sp) {
                                SDL_سيٽ_Surface_Palette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, عدم);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->اندروني, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, عدم, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        ثابت صحيح vsync_interval = windata->framebuffer_vsync;
        إذا (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        إذا (dac_needs_update) {
            vdata->palette_نسخو = dac_palette->نسخو;
            پروگرام_VGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        ثابت Uint32 win_gran_بائيٽون = (Uint32)mdata->win_granularity * 1024;
        ثابت Uint32 win_سائيز_بائيٽون = (Uint32)mdata->win_سائيز * 1024;
        ثابت Uint32 win_بنياد = (Uint32)mdata->win_a_segment << 4;
        صحيح current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        لكل (صحيح r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            إذا (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            إذا (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            إذا (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            إذا (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            إذا (rect.w <= 0 || rect.h <= 0) {
                استمر;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            إذا (have_cursor_rect && !cursor_covered) {
                إذا (rect.x <= cursor_clipped.x &&
                    rect.y <= cursor_clipped.y &&
                    rect.x + rect.w >= cursor_clipped.x + cursor_clipped.w &&
                    rect.y + rect.h >= cursor_clipped.y + cursor_clipped.h) {
                    cursor_covered = true;
                }
            }

            BankedFramebufferCopyRect(mdata, src, &rect, dst_x, dst_y,
                                      win_gran_بائيٽون, win_سائيز_بائيٽون, win_بنياد,
                                      &current_bank, mdata->win_func_ptr);
        }

        // If no dirty rect covered the cursor, copy the cursor region separately.
        إذا (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_بائيٽون, win_سائيز_بائيٽون, win_بنياد,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        إذا (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, عدم, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } وإلا {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        إذا (!dst) {
            أرجع SDL_سيٽ_Error("Couldn't find VESA linear framebuffer surface for window");
        }

        ثابت SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = عدم;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : عدم;
        إذا (cur && cur->animation) {
            cur = cur->animation->چوکٺا[cur->animation->current_چوکٺو];
        }
        إذا (mouse && mouse->اندروني && !mouse->relative_گهڻائي && mouse->cursor_visible && cur && cur->اندروني) {
            cursor = cur->اندروني->surface;
            إذا (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((صحيح)mouse->x, 0, دري->w) - cur->اندروني->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((صحيح)mouse->y, 0, دري->h) - cur->اندروني->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        إذا (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            ثابت Uint8 *sp = (ثابت Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            إذا (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } وإلا {
                لكل (صحيح صف = 0; صف < dstrect.h; صف++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } وإلا {
            // Blit to the back page (or the only page, if no page-flipping)
            إذا (!SDL_BlitSurface(src, عدم, dst, &dstrect)) {
                أرجع false;
            }
        }

        إذا (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->اندروني, dst);
            إذا (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, عدم, dst, &cursorrect)) {
                أرجع false;
            }
        }

        إذا (vdata->صفحو_flip_موجود) {
            // Page-flip with optional vsync.
            ثابت صحيح vsync_interval = windata->framebuffer_vsync;
            صحيح پٺ_صفحو = 1 - vdata->current_صفحو;
            Uint16 پهريون_scanline = (Uint16)(vdata->صفحو_وٿي[پٺ_صفحو] / mdata->pitch);

            إذا (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            إذا (dac_needs_update) {
                vdata->palette_نسخو = dac_palette->نسخو;
                پروگرام_VGADAC(dac_palette);
            }

            // Flip: make the back page (which we just drew to) the visible page.
            // Always use subfunction 0x0080 (set display start, don't wait) —
            // vsync is controlled by our manual vblank wait above.
            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0; // first pixel in scan line
            regs.x.dx = پهريون_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_صفحو = پٺ_صفحو;

            // Update LFB surface to point at the new back page (the old front page)
            صحيح new_پٺ = 1 - vdata->current_صفحو;
            dst->pixels = (Uint8 *)DOS_Physical_منزل_لڪيري(vdata->mapping.پتو) + vdata->صفحو_وٿي[new_پٺ];
        } وإلا {
            // No page-flipping: wait for vsync, then update DAC atomically
            ثابت صحيح vsync_interval = windata->framebuffer_vsync;
            إذا (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            إذا (dac_needs_update) {
                vdata->palette_نسخو = dac_palette->نسخو;
                پروگرام_VGADAC(dac_palette);
            }
        }
    }

    أرجع true;
}

فراغ DOSVESA_Destroy_دري_Framebuffer(SDL_VideoDevice *device, SDL_دري *دري)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (فراغ)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_Get_دري_Properties(دري), DOS_SURFACE);
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_DOSVESA

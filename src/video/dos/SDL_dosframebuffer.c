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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_DOSVESA

#شامل "../../SDL_properties_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "SDL_dosframebuffer_c.h"
#شامل "SDL_dosmodes.h"
#شامل "SDL_dosmouse.h"
#شامل "SDL_dosvideo.h"

#شامل <pc.h>           // for inportb, outportb
#شامل <sys/movedata.h> // for dosmemput (banked framebuffer writes)

// note that DOS_SURFACE's value is the same string that the dummy driver uses.
#تعریف_کرو DOS_SURFACE "SDL.internal.window.surface"

//  Consolidated framebuffer state (DOS has only one window)
قسمتعریف ساخت DOSFramebufferState
{
    SDL_Surface *surface;     // system-RAM surface (app renders here)
    SDL_Surface *lfb_surface; // LFB surface (pixels in VRAM), NULL for direct-FB path
    bool براہ_راست_fb;           // true when the fast direct-FB hint path is active
    bool use_dosmemput;       // true = dosmemput (banked), false = nearptr (LFB)
    صحیح vram_pitch;
    صحیح vram_w;
    صحیح vram_h;
    صحیح bpp; // bytes per pixel

    // dosmemput path state (use_dosmemput)
    Uint32 vram_phys;      // base address for dosmemput (e.g. 0xA0000)
    bool banked_multibank; // true if fb doesn't fit in one bank window
    Uint32 win_gran_بائٹیں; // bank granularity in bytes
    Uint32 win_سائز_بائٹیں; // bank window size in bytes
    Uint32 win_بنیاد;       // window base address (segment << 4)
    Uint32 win_func_ptr;   // real-mode far pointer to bank-switch function

    // nearptr path state (use_dosmemput == false)
    Uint8 *vram_ptr; // nearptr into VRAM (LFB)

    // Cached per-frame values (set at create time, avoid repeated lookups)
    Uint8 *pixels;      // == surface->pixels (stable after create)
    صحیح src_pitch;      // == surface->pitch
    Uint32 fb_سائز;     // total framebuffer bytes (pitch * h) for full-surface fast path
    bool pitches_مطابقت; // src_pitch == vram_pitch (enables single-copy fast path)
} DOSFramebufferState;

ساکن DOSFramebufferState fb_state;

// Convert cursor to the current format.
ساکن SDL_Surface *GetConvertedCursorSurface(SDL_Cursor_ڈیٹا *curdata, SDL_Surface *dst)
{
    SDL_Palette *pal = SDL_GetSurfacePalette(dst);
    اگر (!pal) {
        واپس تہی;
    }

    Uint32 pal_نسخہ = pal ? pal->نسخہ : 0;

    اگر (curdata->converted_surface &&
        curdata->converted_surface->format == dst->format &&
        curdata->converted_palette_نسخہ == pal_نسخہ) {
        واپس curdata->converted_surface;
    }

    SDL_DestroySurface(curdata->converted_surface);
    curdata->converted_surface = تہی;

    SDL_Surface *src = curdata->surface;
    SDL_assert(src->format == SDL_PIXELFORMAT_ARGB8888);

    صحیح w = src->w;
    صحیح h = src->h;
    SDL_Surface *conv = SDL_CreateSurfaceUninitialized(w, h, dst->format);
    اگر (!conv) {
        واپس تہی;
    }

    // Copy the destination palette.
    SDL_Palette *conv_pal = SDL_CreateSurfacePalette(conv);
    اگر (conv_pal) {
        SDL_سیٹ_Palette_Colors(conv_pal, pal->colors, 0, pal->ncolors);
    }

    // Track which palette indices are used by opaque pixels.
    bool مستعمل[256];
    SDL_zeroa(مستعمل);

    // First pass: blit with BLENDMODE_NONE to get raw color-matched indices.
    SDL_سیٹ_Surface_Blend_منوال(src, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(src, تہی, conv, تہی);
    SDL_سیٹ_Surface_Blend_منوال(src, SDL_BLENDMODE_BLEND);

    // Mark which indices are used by non-transparent source pixels.
    برائے (صحیح y = 0; y < h; y++) {
        ثابت Uint32 *srcrow = (ثابت Uint32 *)((ثابت Uint8 *)src->pixels + y * src->pitch);
        ثابت Uint8 *convrow = (ثابت Uint8 *)conv->pixels + y * conv->pitch;
        برائے (صحیح x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            اگر (srcA > 0) {
                مستعمل[convrow[x]] = true;
            }
        }
    }

    // Find an unused index for the colorkey.
    Uint32 colorkey = 0;
    برائے (صحیح i = 0; i < 256; i++) {
        اگر (!مستعمل[i]) {
            colorkey = (Uint32)i;
            توڑو;
        }
    }

    // Second pass: set transparent pixels to the colorkey index.
    برائے (صحیح y = 0; y < h; y++) {
        ثابت Uint32 *srcrow = (ثابت Uint32 *)((ثابت Uint8 *)src->pixels + y * src->pitch);
        Uint8 *convrow = (Uint8 *)conv->pixels + y * conv->pitch;
        برائے (صحیح x = 0; x < w; x++) {
            Uint8 srcA = (Uint8)(srcrow[x] >> 24);
            اگر (srcA == 0) {
                convrow[x] = (Uint8)colorkey;
            }
        }
    }

    SDL_سیٹ_Surface_Color_کلید(conv, true, colorkey);
    SDL_سیٹ_Surface_Blend_منوال(conv, SDL_BLENDMODE_NONE);

    curdata->converted_surface = conv;
    curdata->converted_palette_نسخہ = pal_نسخہ;
    واپس conv;
}

//  Invalidation (called from SetDisplayMode before freeing DPMI mapping)
خالی DOSVESA_InvalidateCachedFramebuffer(خالی)
{
    fb_state.براہ_راست_fb = false;
    fb_state.vram_ptr = تہی;
    fb_state.vram_phys = 0;
    fb_state.use_dosmemput = false;
    // Clear the LFB surface pointer so UpdateWindowFramebuffer won't try
    // to blit into VRAM after the DPMI mapping has been freed.
    fb_state.lfb_surface = تہی;
}

// Create a system-RAM surface (with a blank palette if INDEX8 and update the VGA DAC).
ساکن SDL_Surface *CreateSystemSurface(SDL_Video_ڈیٹا *ڈیٹا, صحیح w, صحیح h, SDL_PixelFormat surface_format)
{
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(w, h, surface_format);
    اگر (!surface) {
        واپس تہی;
    }

    // For 8-bit indexed modes, both surfaces need palettes.
    // Share the same palette object so palette updates propagate to both.
    اگر (surface_format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *palette = SDL_CreateSurfacePalette(surface);
        اگر (palette) {
            // Initialize palette to all-black so that transitions start
            // from black instead of flashing uninitialized (white) colors.
            SDL_Color black[256];
            SDL_zeroa(black);
            برائے (صحیح i = 0; i < 256; i++) {
                black[i].a = SDL_ALPHA_OPAQUE;
            }
            SDL_سیٹ_Palette_Colors(palette, black, 0, 256);
        }
        ڈیٹا->palette_نسخہ = 0; // force DAC update on first present

        // Also program the VGA DAC to all-black right now, so no flash
        // of stale/white palette colors before the first present.
        outportb(VGA_DAC_WRITE_اشاریہ, 0);
        برائے (صحیح i = 0; i < 256; i++) {
            outportb(VGA_DAC_ڈیٹا, 0);
            outportb(VGA_DAC_ڈیٹا, 0);
            outportb(VGA_DAC_ڈیٹا, 0);
        }
    }

    واپس surface;
}

// Normal (non-direct-FB) path: system-RAM surface with optional LFB blit,
// cursor compositing, palette sync, vsync, and page-flipping.
ساکن bool Create_معمول_Framebuffer(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی,
                                    SDL_PixelFormat *format, خالی **pixels, صحیح *pitch)
{
    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;
    ثابت SDL_Display_منوال *منوال = &ڈیٹا->current_منوال;
    ثابت SDL_Display_منوال_ڈیٹا *mdata = منوال->اندرونی_2;
    ثابت SDL_PixelFormat surface_format = منوال->format;
    صحیح w, h;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);

    SDL_Surface *surface = CreateSystemSurface(ڈیٹا, w, h, surface_format);
    اگر (!surface) {
        واپس false;
    }

    SDL_Surface *lfb_surface = تہی;

    اگر (!ڈیٹا->banked_منوال) {
        // LFB path: Make a surface that uses video memory directly, to let SDL do the blitting for us.
        // Point the LFB surface at the back page for tear-free double-buffering.
        صحیح عقب_صفحہ = ڈیٹا->صفحہ_flip_دستیاب ? (1 - ڈیٹا->current_صفحہ) : 0;
        خالی *lfb_pixels = (Uint8 *)DOS_Physical_مقصد_خطی(ڈیٹا->mapping.پتہ) + ڈیٹا->صفحہ_انحراف[عقب_صفحہ];
        lfb_surface = SDL_CreateSurfaceFrom(منوال->w, منوال->h, surface_format, lfb_pixels, mdata->pitch);
        اگر (!lfb_surface) {
            SDL_DestroySurface(surface);
            واپس false;
        }
        fb_state.lfb_surface = lfb_surface;

        // Share the palette so updates propagate to both surfaces.
        SDL_Palette *src_palette = SDL_GetSurfacePalette(surface);
        اگر (src_palette) {
            SDL_سیٹ_Surface_Palette(lfb_surface, src_palette);
        }
    }

    // clear the framebuffer completely, in case another window at a larger size was using this before us.
    اگر (lfb_surface) {
        SDL_ClearSurface(lfb_surface, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    // (For banked mode, the framebuffer was already zeroed in DOSVESA_SetDisplayMode.)

    // Save the info and return!
    fb_state.surface = surface;
    SDL_سیٹ_Surface_Property(SDL_Get_کھڑکی_Properties(کھڑکی), DOS_SURFACE, surface);

    *format = surface_format;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    واپس true;
}

bool DOSVESA_Create_کھڑکی_Framebuffer(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, خالی **pixels, صحیح *pitch)
{
    SDL_zero(fb_state);

    SDL_Video_ڈیٹا *ڈیٹا = device->اندرونی_2;
    ثابت SDL_Display_منوال *منوال = &ڈیٹا->current_منوال;
    ثابت SDL_Display_منوال_ڈیٹا *mdata = منوال->اندرونی_2;
    ثابت SDL_PixelFormat surface_format = منوال->format;
    صحیح w, h;

    // writing to video RAM shows up as the screen refreshes, done or not, and it might have a weird pitch, so give the app a buffer of system RAM.
    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);

    // Try to set up fast path where UpdateWindowFramebuffer copies system-RAM directly to VRAM.
    اگر (SDL_GetHintBoolean(SDL_HINT_DOS_ALLOW_براہ_راست_FRAMEBUFFER, false)) {
        صحیح vram_pitch = mdata->pitch;

        // Check if we have any usable VRAM access path (banked or LFB).
        bool have_vram = false;

        اگر (mdata->win_a_segment && mdata->win_سائز > 0 &&
            (mdata->win_a_اوصاف & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
            // Banked window available. Use dosmemput path (preferred).
            have_vram = true;
        } ورنہ اگر (!ڈیٹا->banked_منوال && ڈیٹا->mapping.سائز) {
            // LFB only, use nearptr fallback.
            have_vram = true;
        }

        اگر (have_vram) {
            SDL_Surface *surface = CreateSystemSurface(ڈیٹا, w, h, surface_format);
            اگر (!surface) {
                واپس false;
            }

            SDL_سیٹ_Surface_Property(SDL_Get_کھڑکی_Properties(کھڑکی), DOS_SURFACE, surface);

            fb_state.surface = surface;
            fb_state.براہ_راست_fb = true;
            fb_state.vram_pitch = vram_pitch;
            fb_state.vram_w = mdata->w;
            fb_state.vram_h = mdata->h;
            fb_state.bpp = SDL_BYTESPERPIXEL(surface_format);
            fb_state.pixels = (Uint8 *)surface->pixels;
            fb_state.src_pitch = surface->pitch;
            fb_state.fb_سائز = (Uint32)vram_pitch * mdata->h;
            fb_state.pitches_مطابقت = (surface->pitch == vram_pitch);

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
            اگر (mdata->win_a_segment && mdata->win_سائز > 0 &&
                (mdata->win_a_اوصاف & VBE_WINATTR_USABLE) == VBE_WINATTR_USABLE) {
                Uint32 win_بائٹیں = (Uint32)mdata->win_سائز * 1024;
                fb_state.use_dosmemput = true;
                fb_state.vram_ptr = تہی;
                fb_state.vram_phys = (Uint32)mdata->win_a_segment << 4;
                fb_state.win_بنیاد = fb_state.vram_phys;
                fb_state.win_gran_بائٹیں = (Uint32)mdata->win_granularity * 1024;
                fb_state.win_سائز_بائٹیں = win_بائٹیں;
                fb_state.win_func_ptr = mdata->win_func_ptr;
                fb_state.banked_multibank = (fb_state.fb_سائز > win_بائٹیں);
            } ورنہ اگر (!ڈیٹا->banked_منوال && ڈیٹا->mapping.سائز) {
                // Fallback: nearptr to LFB.
                صحیح عقب_صفحہ = ڈیٹا->صفحہ_flip_دستیاب ? (1 - ڈیٹا->current_صفحہ) : 0;
                fb_state.vram_ptr = (Uint8 *)DOS_Physical_مقصد_خطی(ڈیٹا->mapping.پتہ) + ڈیٹا->صفحہ_انحراف[عقب_صفحہ];
                fb_state.vram_phys = 0;
                fb_state.use_dosmemput = false;
                fb_state.banked_multibank = false;
            } ورنہ {
                // No usable VRAM path. Shouldn't happen, but bail out.
                SDL_DestroySurface(surface);
                واپس Create_معمول_Framebuffer(device, کھڑکی, format, pixels, pitch);
            }
            *format = surface_format;
            *pixels = surface->pixels;
            *pitch = surface->pitch;
            واپس true;
        }
        // else: couldn't get a direct pointer, fall through to normal path.
    }

    واپس Create_معمول_Framebuffer(device, کھڑکی, format, pixels, pitch);
}

bool DOSVESA_سیٹ_کھڑکی_Framebuffer_VSync(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, صحیح vsync)
{
    اگر (vsync < 0) {
        واپس SDL_سیٹ_Error("Unsupported vsync type");
    }
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    ڈیٹا->framebuffer_vsync = vsync;
    واپس true;
}

bool DOSVESA_Get_کھڑکی_Framebuffer_VSync(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, صحیح *vsync)
{
    اگر (vsync) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
        *vsync = ڈیٹا->framebuffer_vsync;
    }
    واپس true;
}

// Switch the VGA bank window if needed. Returns without doing anything
// if the requested bank is already active.
SDL_FORCE_INLINE خالی SwitchBank(صحیح bank, صحیح *current_bank, Uint32 win_func_ptr)
{
    اگر (bank == *current_bank) {
        واپس;
    }
    __dpmi_regs regs;
    SDL_zero(regs);
    regs.x.bx = 0; // Window A
    regs.x.dx = (Uint16)bank;
    اگر (win_func_ptr) {
        regs.x.cs = (Uint16)(win_func_ptr >> 16);
        regs.x.ip = (Uint16)(win_func_ptr & 0xFFFF);
        __dpmi_simulate_real_mode_procedure_retf(&regs);
    } ورنہ {
        regs.x.ax = 0x4F05;
        __dpmi_int(0x10, &regs);
    }
    *current_bank = bank;
}

// Copy a contiguous byte range from system RAM to VRAM through the banked
// window, switching banks as needed.
SDL_FORCE_INLINE خالی BankedDosmemput(ثابت Uint8 *src, Uint32 کل_بائٹیں, Uint32 dst_انحراف,
                                      Uint32 win_gran_بائٹیں, Uint32 win_سائز_بائٹیں,
                                      Uint32 win_بنیاد, Uint32 win_func_ptr,
                                      صحیح *current_bank)
{
    Uint32 src_off = 0;
    جب (کل_بائٹیں > 0) {
        صحیح bank = (صحیح)(dst_انحراف / win_gran_بائٹیں);
        Uint32 off_اندر_win = dst_انحراف % win_gran_بائٹیں;
        Uint32 avail = win_سائز_بائٹیں - off_اندر_win;
        Uint32 n = کل_بائٹیں;
        اگر (n > avail) {
            n = avail;
        }
        SwitchBank(bank, current_bank, win_func_ptr);
        dosmemput(src + src_off, n, win_بنیاد + off_اندر_win);
        src_off += n;
        dst_انحراف += n;
        کل_بائٹیں -= n;
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
ساکن خالی BankedFramebufferCopyRect(ثابت SDL_Display_منوال_ڈیٹا *mdata,
                                      ثابت SDL_Surface *src,
                                      ثابت SDL_Rect *src_rect,
                                      صحیح dst_x, صحیح dst_y,
                                      Uint32 win_gran_بائٹیں,
                                      Uint32 win_سائز_بائٹیں,
                                      Uint32 win_بنیاد,
                                      صحیح *current_bank,
                                      Uint32 win_func_ptr)
{
    ثابت Uint16 dst_pitch = mdata->pitch;
    ثابت صحیح بائٹیں_فی_pixel = SDL_BYTESPERPIXEL(src->format);
    ثابت صحیح صف_بائٹیں = src_rect->w * بائٹیں_فی_pixel;

    // Fast path: if the source row width matches src pitch AND the destination
    // row width matches dst pitch, the data is contiguous in both source and
    // destination — we can copy it as one flat block, minimizing dosmemput calls.
    اگر (صف_بائٹیں == src->pitch && صف_بائٹیں == dst_pitch) {
        ثابت Uint8 *src_ڈیٹا = (ثابت Uint8 *)src->pixels + src_rect->y * src->pitch + src_rect->x * بائٹیں_فی_pixel;
        Uint32 dst_انحراف = (Uint32)(dst_y + src_rect->y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * بائٹیں_فی_pixel;
        BankedDosmemput(src_ڈیٹا, (Uint32)(صف_بائٹیں * src_rect->h), dst_انحراف,
                        win_gran_بائٹیں, win_سائز_بائٹیں, win_بنیاد, win_func_ptr, current_bank);
        واپس;
    }

    برائے (صحیح y = 0; y < src_rect->h; y++) {
        ثابت Uint8 *src_صف = (ثابت Uint8 *)src->pixels + (src_rect->y + y) * src->pitch + src_rect->x * بائٹیں_فی_pixel;
        Uint32 dst_انحراف = (Uint32)(dst_y + src_rect->y + y) * dst_pitch + (Uint32)(dst_x + src_rect->x) * بائٹیں_فی_pixel;
        BankedDosmemput(src_صف, (Uint32)صف_بائٹیں, dst_انحراف,
                        win_gran_بائٹیں, win_سائز_بائٹیں, win_بنیاد, win_func_ptr, current_bank);
    }
}

ساکن خالی WaitForVBlank(خالی)
{
    جب (inportb(VGA_حالت_پورٹ) & VGA_حالت_VBLANK) {
        SDL_CPUPauseInstruction();
    }
    جب (!(inportb(VGA_حالت_پورٹ) & VGA_حالت_VBLANK)) {
        SDL_CPUPauseInstruction();
    }
}

ساکن خالی پروگرام_VGADAC(SDL_Palette *palette)
{
    outportb(VGA_DAC_WRITE_اشاریہ, 0);
    برائے (صحیح i = 0; i < palette->ncolors && i < 256; i++) {
        outportb(VGA_DAC_ڈیٹا, palette->colors[i].r >> 2);
        outportb(VGA_DAC_ڈیٹا, palette->colors[i].g >> 2);
        outportb(VGA_DAC_ڈیٹا, palette->colors[i].b >> 2);
    }
}

bool DOSVESA_Update_کھڑکی_Framebuffer(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحیح numrects)
{
    SDL_Video_ڈیٹا *vdata = device->اندرونی_2;

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
    اگر (fb_state.براہ_راست_fb && (fb_state.vram_ptr || fb_state.vram_phys)) {

        // Palette update.
        اگر (کھڑکی->surface) {
            SDL_Palette *pal = کھڑکی->surface->palette;
            اگر (pal && pal->نسخہ != vdata->palette_نسخہ) {
                vdata->palette_نسخہ = pal->نسخہ;
                پروگرام_VGADAC(pal);
            }
        }

        // No rectangles to update, so just program the palette and return.
        // This is useful for pure palette animations.
        اگر (numrects <= 0) {
            واپس true;
        }

        اگر (fb_state.use_dosmemput) {
            // dosmemput path (banked window, possibly multi-bank)
            ثابت صحیح src_pitch = fb_state.src_pitch;
            ثابت صحیح dst_pitch = fb_state.vram_pitch;
            ثابت Uint8 *pixels = fb_state.pixels;

            اگر (!fb_state.banked_multibank) {
                // Single-bank: entire FB fits in one window (e.g. mode 13h).
                // Full-surface fast path when pitches match.
                اگر (fb_state.pitches_مطابقت) {
                    dosmemput(pixels, fb_state.fb_سائز, fb_state.vram_phys);
                } ورنہ {
                    برائے (صحیح i = 0; i < numrects; i++) {
                        صحیح rx = rects[i].x, ry = rects[i].y;
                        صحیح rw = rects[i].w, rh = rects[i].h;
                        اگر (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        اگر (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        اگر (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        اگر (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        اگر (rw <= 0 || rh <= 0) {
                            جاری;
                        }
                        ثابت صحیح bx = rx * fb_state.bpp;
                        ثابت صحیح bw = rw * fb_state.bpp;
                        ثابت Uint8 *sp = pixels + ry * src_pitch + bx;
                        Uint32 dst_off = fb_state.vram_phys + ry * dst_pitch + bx;
                        برائے (صحیح صف = 0; صف < rh; صف++) {
                            dosmemput(sp, bw, dst_off);
                            sp += src_pitch;
                            dst_off += dst_pitch;
                        }
                    }
                }
            } ورنہ {
                // Multi-bank: bank-switch as needed.
                ثابت Uint32 gran = fb_state.win_gran_بائٹیں;
                ثابت Uint32 wsize = fb_state.win_سائز_بائٹیں;
                ثابت Uint32 wbase = fb_state.win_بنیاد;
                ثابت Uint32 wfunc = fb_state.win_func_ptr;
                صحیح current_bank = -1;

                اگر (fb_state.pitches_مطابقت) {
                    // Contiguous: stream the entire framebuffer through banks.
                    BankedDosmemput(pixels, fb_state.fb_سائز, 0,
                                    gran, wsize, wbase, wfunc, &current_bank);
                } ورنہ {
                    // Per-rect with bank switching.
                    برائے (صحیح i = 0; i < numrects; i++) {
                        صحیح rx = rects[i].x, ry = rects[i].y;
                        صحیح rw = rects[i].w, rh = rects[i].h;
                        اگر (rx < 0) {
                            rw += rx;
                            rx = 0;
                        }
                        اگر (ry < 0) {
                            rh += ry;
                            ry = 0;
                        }
                        اگر (rx + rw > fb_state.vram_w) {
                            rw = fb_state.vram_w - rx;
                        }
                        اگر (ry + rh > fb_state.vram_h) {
                            rh = fb_state.vram_h - ry;
                        }
                        اگر (rw <= 0 || rh <= 0) {
                            جاری;
                        }
                        ثابت صحیح bx = rx * fb_state.bpp;
                        ثابت صحیح bw = rw * fb_state.bpp;

                        برائے (صحیح صف = 0; صف < rh; صف++) {
                            ثابت Uint8 *sp = pixels + (ry + صف) * src_pitch + bx;
                            Uint32 dst_انحراف = (Uint32)(ry + صف) * dst_pitch + bx;
                            BankedDosmemput(sp, (Uint32)bw, dst_انحراف,
                                            gran, wsize, wbase, wfunc, &current_bank);
                        }
                    }
                }
            }
        } ورنہ {
            // nearptr path (LFB fallback)
            اگر (fb_state.pitches_مطابقت) {
                SDL_memcpy(fb_state.vram_ptr, fb_state.pixels, fb_state.fb_سائز);
            } ورنہ {
                ثابت صحیح bpp = fb_state.bpp;
                ثابت صحیح src_pitch = fb_state.src_pitch;
                ثابت صحیح dst_pitch = fb_state.vram_pitch;
                ثابت Uint8 *pixels = fb_state.pixels;

                برائے (صحیح i = 0; i < numrects; i++) {
                    صحیح rx = rects[i].x, ry = rects[i].y;
                    صحیح rw = rects[i].w, rh = rects[i].h;
                    اگر (rx < 0) {
                        rw += rx;
                        rx = 0;
                    }
                    اگر (ry < 0) {
                        rh += ry;
                        ry = 0;
                    }
                    اگر (rx + rw > fb_state.vram_w) {
                        rw = fb_state.vram_w - rx;
                    }
                    اگر (ry + rh > fb_state.vram_h) {
                        rh = fb_state.vram_h - ry;
                    }
                    اگر (rw <= 0 || rh <= 0) {
                        جاری;
                    }
                    ثابت صحیح bw = rw * bpp;
                    ثابت Uint8 *sp = pixels + ry * src_pitch + rx * bpp;
                    Uint8 *dp = fb_state.vram_ptr + ry * dst_pitch + rx * bpp;
                    برائے (صحیح صف = 0; صف < rh; صف++) {
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
        اگر (!fb_state.use_dosmemput && vdata->صفحہ_flip_دستیاب) {
            ثابت SDL_Display_منوال_ڈیٹا *mdata = vdata->current_منوال.اندرونی_2;
            صحیح عقب_صفحہ = 1 - vdata->current_صفحہ;
            Uint16 پہلا_scanline = (Uint16)(vdata->صفحہ_انحراف[عقب_صفحہ] / mdata->pitch);

            __dpmi_regs regs;
            SDL_zero(regs);
            regs.x.ax = 0x4F07;
            regs.x.bx = 0x0080;
            regs.x.cx = 0;
            regs.x.dx = پہلا_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_صفحہ = عقب_صفحہ;

            صحیح new_عقب = 1 - vdata->current_صفحہ;
            fb_state.vram_ptr = (Uint8 *)DOS_Physical_مقصد_خطی(vdata->mapping.پتہ) + vdata->صفحہ_انحراف[new_عقب];
        }

        واپس true;
    }

    // ===================================================================
    //  Normal path: system-RAM to LFB surface (or banked copy)
    //  with cursor compositing, palette sync, vsync, and page-flipping.
    // ===================================================================

    SDL_Surface *src = fb_state.surface;
    اگر (!src) {
        src = (SDL_Surface *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), DOS_SURFACE, تہی);
    }
    اگر (!src) {
        واپس SDL_سیٹ_Error("Couldn't find DOS surface for window");
    }

    ثابت SDL_Display_منوال_ڈیٹا *mdata = vdata->current_منوال.اندرونی_2;
    SDL_کھڑکی_ڈیٹا *windata = کھڑکی->اندرونی_2;

    // For 8-bit indexed modes, sync palette data between surfaces so the
    // blit uses the correct color mapping.  The actual VGA DAC programming
    // is deferred until vertical blanking to avoid visible palette flicker.
    SDL_Palette *dac_palette = تہی;
    bool dac_needs_update = false;

    اگر (src->format == SDL_PIXELFORMAT_INDEX8) {
        SDL_Palette *win_palette = کھڑکی->surface ? SDL_GetSurfacePalette(کھڑکی->surface) : تہی;
        SDL_Palette *src_palette = SDL_GetSurfacePalette(src);

        // Sync: if the app set colors on the window surface palette,
        // copy them to the internal surface so the blit works correctly.
        اگر (win_palette && src_palette && win_palette != src_palette &&
            win_palette->نسخہ != src_palette->نسخہ) {
            SDL_سیٹ_Palette_Colors(src_palette, win_palette->colors, 0,
                                 SDL_min(win_palette->ncolors, src_palette->ncolors));

            اگر (!vdata->banked_منوال && fb_state.lfb_surface) {
                // Also update the LFB surface palette for correct blitting
                SDL_Palette *dst_palette = SDL_GetSurfacePalette(fb_state.lfb_surface);
                اگر (dst_palette && dst_palette != src_palette) {
                    SDL_سیٹ_Palette_Colors(dst_palette, win_palette->colors, 0,
                                         SDL_min(win_palette->ncolors, dst_palette->ncolors));
                }
            }
        }

        // Determine whether the VGA DAC needs reprogramming.
        dac_palette = win_palette ? win_palette : src_palette;
        اگر (dac_palette && dac_palette->نسخہ != vdata->palette_نسخہ) {
            dac_needs_update = true;
        }
    }

    اگر (vdata->banked_منوال) {
        // --- Banked framebuffer path (dirty-rect aware) ---
        // We composite the cursor onto the source surface (in system RAM),
        // then bank-copy only the dirty rectangles to the VGA window.  We
        // need to undo the cursor composite afterwards so the app's surface
        // isn't permanently modified.

        ثابت صحیح dst_x = ((صحیح)mdata->w - src->w) / 2;
        ثابت صحیح dst_y = ((صحیح)mdata->h - src->h) / 2;

        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = تہی;
        SDL_Rect cursorrect;
        SDL_Rect cursor_clipped; // cursorrect clipped to src bounds
        SDL_Surface *cursor_save = تہی;
        bool have_cursor_rect = false;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : تہی;
        اگر (cur && cur->animation) {
            cur = cur->animation->چوکھٹے[cur->animation->current_چوکھٹا];
        }
        اگر (mouse && mouse->اندرونی_2 && !mouse->relative_منوال && mouse->cursor_visible && cur && cur->اندرونی_2) {
            cursor = cur->اندرونی_2->surface;
            اگر (cursor) {
                cursorrect.x = SDL_clamp((صحیح)mouse->x, 0, کھڑکی->w) - cur->اندرونی_2->hot_x;
                cursorrect.y = SDL_clamp((صحیح)mouse->y, 0, کھڑکی->h) - cur->اندرونی_2->hot_y;
                cursorrect.w = cursor->w;
                cursorrect.h = cursor->h;

                // Clip cursor rect to src bounds for save/restore.
                cursor_clipped = cursorrect;
                اگر (cursor_clipped.x < 0) {
                    cursor_clipped.w += cursor_clipped.x;
                    cursor_clipped.x = 0;
                }
                اگر (cursor_clipped.y < 0) {
                    cursor_clipped.h += cursor_clipped.y;
                    cursor_clipped.y = 0;
                }
                اگر (cursor_clipped.x + cursor_clipped.w > src->w) {
                    cursor_clipped.w = src->w - cursor_clipped.x;
                }
                اگر (cursor_clipped.y + cursor_clipped.h > src->h) {
                    cursor_clipped.h = src->h - cursor_clipped.y;
                }

                اگر (cursor_clipped.w > 0 && cursor_clipped.h > 0) {
                    have_cursor_rect = true;

                    // Save the pixels under the cursor so we can restore them after the copy.
                    cursor_save = SDL_CreateSurfaceUninitialized(cursor_clipped.w, cursor_clipped.h, src->format);
                    اگر (cursor_save) {
                        اگر (src->format == SDL_PIXELFORMAT_INDEX8) {
                            SDL_Palette *sp = SDL_GetSurfacePalette(src);
                            اگر (sp) {
                                SDL_سیٹ_Surface_Palette(cursor_save, sp);
                            }
                        }
                        SDL_BlitSurface(src, &cursor_clipped, cursor_save, تہی);
                    }
                }

                // Composite cursor onto the source surface.
                {
                    SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->اندرونی_2, src);
                    SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, تہی, src, &cursorrect);
                }
            }
        }

        // Wait for vsync before the copy to reduce tearing.
        ثابت صحیح vsync_interval = windata->framebuffer_vsync;
        اگر (vsync_interval > 0 || dac_needs_update) {
            WaitForVBlank();
        }

        اگر (dac_needs_update) {
            vdata->palette_نسخہ = dac_palette->نسخہ;
            پروگرام_VGADAC(dac_palette);
        }

        // Bank-switched copy of only the dirty rectangles.
        // Pre-compute constants shared across all rect copies.
        ثابت Uint32 win_gran_بائٹیں = (Uint32)mdata->win_granularity * 1024;
        ثابت Uint32 win_سائز_بائٹیں = (Uint32)mdata->win_سائز * 1024;
        ثابت Uint32 win_بنیاد = (Uint32)mdata->win_a_segment << 4;
        صحیح current_bank = -1;

        // Track whether the cursor region was already covered by a dirty rect
        // so we don't copy it twice.
        bool cursor_covered = false;

        برائے (صحیح r = 0; r < numrects; r++) {
            // Clip the dirty rect to the source surface bounds.
            SDL_Rect rect = rects[r];
            اگر (rect.x < 0) {
                rect.w += rect.x;
                rect.x = 0;
            }
            اگر (rect.y < 0) {
                rect.h += rect.y;
                rect.y = 0;
            }
            اگر (rect.x + rect.w > src->w) {
                rect.w = src->w - rect.x;
            }
            اگر (rect.y + rect.h > src->h) {
                rect.h = src->h - rect.y;
            }
            اگر (rect.w <= 0 || rect.h <= 0) {
                جاری;
            }

            // If the cursor is visible, check whether this rect fully covers it.
            اگر (have_cursor_rect && !cursor_covered) {
                اگر (rect.x <= cursor_clipped.x &&
                    rect.y <= cursor_clipped.y &&
                    rect.x + rect.w >= cursor_clipped.x + cursor_clipped.w &&
                    rect.y + rect.h >= cursor_clipped.y + cursor_clipped.h) {
                    cursor_covered = true;
                }
            }

            BankedFramebufferCopyRect(mdata, src, &rect, dst_x, dst_y,
                                      win_gran_بائٹیں, win_سائز_بائٹیں, win_بنیاد,
                                      &current_bank, mdata->win_func_ptr);
        }

        // If no dirty rect covered the cursor, copy the cursor region separately.
        اگر (have_cursor_rect && !cursor_covered) {
            BankedFramebufferCopyRect(mdata, src, &cursor_clipped, dst_x, dst_y,
                                      win_gran_بائٹیں, win_سائز_بائٹیں, win_بنیاد,
                                      &current_bank, mdata->win_func_ptr);
        }

        // Restore the source surface pixels under the cursor.
        اگر (cursor_save) {
            SDL_Rect restore_rect = cursor_clipped;
            SDL_BlitSurface(cursor_save, تہی, src, &restore_rect);
            SDL_DestroySurface(cursor_save);
        }

    } ورنہ {
        // --- LFB path ---
        SDL_Surface *dst = fb_state.lfb_surface;
        اگر (!dst) {
            واپس SDL_سیٹ_Error("Couldn't find VESA linear framebuffer surface for window");
        }

        ثابت SDL_Rect dstrect = { (dst->w - src->w) / 2, (dst->h - src->h) / 2, src->w, src->h };
        SDL_Mouse *mouse = SDL_GetMouse();
        SDL_Surface *cursor = تہی;
        SDL_Rect cursorrect;

        SDL_Cursor *cur = mouse ? mouse->cur_cursor : تہی;
        اگر (cur && cur->animation) {
            cur = cur->animation->چوکھٹے[cur->animation->current_چوکھٹا];
        }
        اگر (mouse && mouse->اندرونی_2 && !mouse->relative_منوال && mouse->cursor_visible && cur && cur->اندرونی_2) {
            cursor = cur->اندرونی_2->surface;
            اگر (cursor) {
                cursorrect.x = dstrect.x + SDL_clamp((صحیح)mouse->x, 0, کھڑکی->w) - cur->اندرونی_2->hot_x;
                cursorrect.y = dstrect.y + SDL_clamp((صحیح)mouse->y, 0, کھڑکی->h) - cur->اندرونی_2->hot_y;
            }
        }

        // If both surfaces are INDEX8 and same size, skip the SDL blit
        // machinery (which does per-pixel palette remapping even for
        // identical palettes), copy directly to the LFB surface using
        // SDL_memcpy.
        اگر (src->format == SDL_PIXELFORMAT_INDEX8 &&
            dst->format == SDL_PIXELFORMAT_INDEX8 &&
            src->w == dstrect.w && src->h == dstrect.h) {
            ثابت Uint8 *sp = (ثابت Uint8 *)src->pixels;
            Uint8 *dp = (Uint8 *)dst->pixels + dstrect.y * dst->pitch + dstrect.x;
            اگر (src->pitch == dstrect.w && dst->pitch == dstrect.w) {
                SDL_memcpy(dp, sp, (size_t)dstrect.w * dstrect.h);
            } ورنہ {
                برائے (صحیح صف = 0; صف < dstrect.h; صف++) {
                    SDL_memcpy(dp, sp, dstrect.w);
                    sp += src->pitch;
                    dp += dst->pitch;
                }
            }
        } ورنہ {
            // Blit to the back page (or the only page, if no page-flipping)
            اگر (!SDL_BlitSurface(src, تہی, dst, &dstrect)) {
                واپس false;
            }
        }

        اگر (cursor) {
            SDL_Surface *blit_cursor = GetConvertedCursorSurface(cur->اندرونی_2, dst);
            اگر (!SDL_BlitSurface(blit_cursor ? blit_cursor : cursor, تہی, dst, &cursorrect)) {
                واپس false;
            }
        }

        اگر (vdata->صفحہ_flip_دستیاب) {
            // Page-flip with optional vsync.
            ثابت صحیح vsync_interval = windata->framebuffer_vsync;
            صحیح عقب_صفحہ = 1 - vdata->current_صفحہ;
            Uint16 پہلا_scanline = (Uint16)(vdata->صفحہ_انحراف[عقب_صفحہ] / mdata->pitch);

            اگر (vsync_interval > 0 || dac_needs_update) {
                // Wait for vblank so the flip and DAC update appear together.
                WaitForVBlank();
            }

            اگر (dac_needs_update) {
                vdata->palette_نسخہ = dac_palette->نسخہ;
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
            regs.x.dx = پہلا_scanline;
            __dpmi_int(0x10, &regs);

            vdata->current_صفحہ = عقب_صفحہ;

            // Update LFB surface to point at the new back page (the old front page)
            صحیح new_عقب = 1 - vdata->current_صفحہ;
            dst->pixels = (Uint8 *)DOS_Physical_مقصد_خطی(vdata->mapping.پتہ) + vdata->صفحہ_انحراف[new_عقب];
        } ورنہ {
            // No page-flipping: wait for vsync, then update DAC atomically
            ثابت صحیح vsync_interval = windata->framebuffer_vsync;
            اگر (vsync_interval > 0 || dac_needs_update) {
                WaitForVBlank();
            }

            اگر (dac_needs_update) {
                vdata->palette_نسخہ = dac_palette->نسخہ;
                پروگرام_VGADAC(dac_palette);
            }
        }
    }

    واپس true;
}

خالی DOSVESA_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *device, SDL_کھڑکی *کھڑکی)
{
    // Note: we intentionally do NOT call SDL_ClearSurface on the LFB surface
    // here. SetDisplayMode already blanks the framebuffer (both pages) when
    // setting a new mode, and the LFB surface's pixels pointer may be stale
    // if the DPMI mapping was freed before this function is called.
    (خالی)device;
    SDL_zero(fb_state);
    SDL_ClearProperty(SDL_Get_کھڑکی_Properties(کھڑکی), DOS_SURFACE);
}

#اگر_ختم // SDL_VIDEO_DRIVER_DOSVESA

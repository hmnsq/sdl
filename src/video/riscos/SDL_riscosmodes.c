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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RISCOS

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_riscosmodes.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <kernel.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <swis.h>

ਗਿਣਤੀ
{
    ਬਹੁਲਕ_FLAG_565 = 1 << 7,

    ਬਹੁਲਕ_FLAG_ਰੰਗ_SPACE = 0xF << 12,

    ਬਹੁਲਕ_FLAG_TBGR = 0,
    ਬਹੁਲਕ_FLAG_TRGB = 1 << 14,
    ਬਹੁਲਕ_FLAG_ABGR = 1 << 15,
    ਬਹੁਲਕ_FLAG_ARGB = ਬਹੁਲਕ_FLAG_TRGB | ਬਹੁਲਕ_FLAG_ABGR
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ
{
    SDL_PixelFormat pixel_format;
    ਪੂਰਨ modeflags, ncolour, log2bpp;
} ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, ਬਹੁਲਕ_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, ਬਹੁਲਕ_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, ਬਹੁਲਕ_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, ਬਹੁਲਕ_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, ਬਹੁਲਕ_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, ਬਹੁਲਕ_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, ਬਹੁਲਕ_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, ਬਹੁਲਕ_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, ਬਹੁਲਕ_FLAG_TBGR | ਬਹੁਲਕ_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, ਬਹੁਲਕ_FLAG_TRGB | ਬਹੁਲਕ_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, ਬਹੁਲਕ_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, ਬਹੁਲਕ_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, ਬਹੁਲਕ_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, ਬਹੁਲਕ_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, ਬਹੁਲਕ_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, ਬਹੁਲਕ_FLAG_ARGB, -1, 5 }
};

ਸਥਿਰ SDL_PixelFormat RISCOS_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_Pixel_Format(ਪੂਰਨ ncolour, ਪੂਰਨ modeflags, ਪੂਰਨ log2bpp)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < SDL_arraysize(ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_pixelformat); i++) {
        ਜੇ (log2bpp == ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_pixelformat[i].log2bpp &&
            (ncolour == ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (ਬਹੁਲਕ_FLAG_565 | ਬਹੁਲਕ_FLAG_ਰੰਗ_SPACE)) == ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_pixelformat[i].modeflags) {
            ਵਾਪਸ ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_pixelformat[i].pixel_format;
        }
    }

    ਵਾਪਸ SDL_PIXELFORMAT_UNKNOWN;
}

ਸਥਿਰ size_t measure_ਬਹੁਲਕ_ਖੰਡ(ਅਚਲ ਪੂਰਨ *ਖੰਡ)
{
    size_t ਖੰਡ_ਮਾਪ = ((ਖੰਡ[0] & 0xFF) == 3) ? 7 : 5;
    ਜਦੋਂ (ਖੰਡ[ਖੰਡ_ਮਾਪ] != -1) {
        ਖੰਡ_ਮਾਪ += 2;
    }
    ਖੰਡ_ਮਾਪ++;

    ਵਾਪਸ ਖੰਡ_ਮਾਪ * 4;
}

ਸਥਿਰ ਪੂਰਨ read_ਬਹੁਲਕ_variable(ਪੂਰਨ *ਖੰਡ, ਪੂਰਨ var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (ਪੂਰਨ)ਖੰਡ;
    regs.r[1] = var;
    _kernel_swi(OS_Read_ਬਹੁਲਕ_Variable, &regs, &regs);
    ਵਾਪਸ regs.r[2];
}

ਸਥਿਰ bool read_ਬਹੁਲਕ_ਖੰਡ(ਪੂਰਨ *ਖੰਡ, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ, bool extended)
{
    ਪੂਰਨ xres, yres, ncolour, modeflags, log2bpp, ਦਰ;

    ਜੇ ((ਖੰਡ[0] & 0xFF) == 1) {
        xres = ਖੰਡ[1];
        yres = ਖੰਡ[2];
        log2bpp = ਖੰਡ[3];
        ਦਰ = ਖੰਡ[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = ਬਹੁਲਕ_FLAG_TBGR;
    } ਨਹੀਂਤਾਂ ਜੇ ((ਖੰਡ[0] & 0xFF) == 3) {
        xres = ਖੰਡ[1];
        yres = ਖੰਡ[2];
        ncolour = ਖੰਡ[3];
        modeflags = ਖੰਡ[4];
        log2bpp = ਖੰਡ[5];
        ਦਰ = ਖੰਡ[6];
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ false;
    }

    ਜੇ (extended) {
        xres = read_ਬਹੁਲਕ_variable(ਖੰਡ, 11) + 1;
        yres = read_ਬਹੁਲਕ_variable(ਖੰਡ, 12) + 1;
        log2bpp = read_ਬਹੁਲਕ_variable(ਖੰਡ, 9);
        ncolour = read_ਬਹੁਲਕ_variable(ਖੰਡ, 3);
        modeflags = read_ਬਹੁਲਕ_variable(ਖੰਡ, 0);
    }

    SDL_zerop(ਬਹੁਲਕ);
    ਬਹੁਲਕ->w = xres;
    ਬਹੁਲਕ->h = yres;
    ਬਹੁਲਕ->format = RISCOS_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_Pixel_Format(ncolour, modeflags, log2bpp);
    ਬਹੁਲਕ->refresh_ਦਰ = (ਦਸ਼ਮਲਵ)ਦਰ;

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ *convert_ਬਹੁਲਕ_ਖੰਡ(ਅਚਲ ਪੂਰਨ *ਖੰਡ)
{
    ਪੂਰਨ xres, yres, log2bpp, ਦਰ, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    ਪੂਰਨ *dst;

    ਜੇ ((ਖੰਡ[0] & 0xFF) == 1) {
        xres = ਖੰਡ[1];
        yres = ਖੰਡ[2];
        log2bpp = ਖੰਡ[3];
        ਦਰ = ਖੰਡ[4];
    } ਨਹੀਂਤਾਂ ਜੇ ((ਖੰਡ[0] & 0xFF) == 3) {
        xres = ਖੰਡ[1];
        yres = ਖੰਡ[2];
        ncolour = ਖੰਡ[3];
        modeflags = ਖੰਡ[4];
        log2bpp = ਖੰਡ[5];
        ਦਰ = ਖੰਡ[6];
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ ਨਿਰਾ;
    }

    dst = SDL_malloc(40);
    ਜੇ (!dst) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = ਦਰ;
    ਜੇ (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    ਜੇ (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    ਵਾਪਸ dst;
}

ਸਥਿਰ ਖਾਲੀ *copy_ਸਮ੍ਰਿਤੀ(ਅਚਲ ਖਾਲੀ *src, size_t ਮਾਪ, size_t alloc)
{
    ਖਾਲੀ *dst = SDL_malloc(alloc);
    ਜੇ (dst) {
        SDL_memcpy(dst, src, ਮਾਪ);
    }
    ਵਾਪਸ dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    ਪੂਰਨ *current_ਬਹੁਲਕ;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t ਮਾਪ;

    regs.r[0] = 1;
    error = _kernel_swi(OS_Screen_ਬਹੁਲਕ, &regs, &regs);
    ਜੇ (error) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_ਬਹੁਲਕ = (ਪੂਰਨ *)regs.r[1];
    ਜੇ (!read_ਬਹੁਲਕ_ਖੰਡ(current_ਬਹੁਲਕ, &ਬਹੁਲਕ, true)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unsupported mode block format %d", current_ਬਹੁਲਕ[0]);
    }

    ਮਾਪ = measure_ਬਹੁਲਕ_ਖੰਡ(current_ਬਹੁਲਕ);
    ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = copy_ਸਮ੍ਰਿਤੀ(current_ਬਹੁਲਕ, ਮਾਪ, ਮਾਪ);
    ਜੇ (!ਬਹੁਲਕ.ਅੰਦਰੂਨੀ) {
        ਵਾਪਸ false;
    }

    ਜੇ (SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ) == 0) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    ਖਾਲੀ *ਖੰਡ, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_Screen_ਬਹੁਲਕ, &regs, &regs);
    ਜੇ (error) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    ਖੰਡ = SDL_malloc(-regs.r[7]);
    ਜੇ (!ਖੰਡ) {
        ਵਾਪਸ false;
    }

    regs.r[6] = (ਪੂਰਨ)ਖੰਡ;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_Screen_ਬਹੁਲਕ, &regs, &regs);
    ਜੇ (error) {
        SDL_free(ਖੰਡ);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    ਲਈ (pos = ਖੰਡ; pos < (ਖਾਲੀ *)regs.r[6]; pos += *((ਪੂਰਨ *)pos)) {
        ਜੇ (!read_ਬਹੁਲਕ_ਖੰਡ(pos + 4, &ਬਹੁਲਕ, false)) {
            ਜਾਰੀ;
        }

        ਜੇ (ਬਹੁਲਕ.format == SDL_PIXELFORMAT_UNKNOWN) {
            ਜਾਰੀ;
        }

        ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = convert_ਬਹੁਲਕ_ਖੰਡ(pos + 4);
        ਜੇ (!ਬਹੁਲਕ.ਅੰਦਰੂਨੀ) {
            SDL_free(ਖੰਡ);
            ਵਾਪਸ false;
        }

        ਜੇ (!SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ)) {
            SDL_free(ਬਹੁਲਕ.ਅੰਦਰੂਨੀ);
        }
    }

    SDL_free(ਖੰਡ);
    ਵਾਪਸ true;
}

bool RISCOS_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    ਅਚਲ ਅੱਖਰ disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    ਪੂਰਨ i;

    regs.r[0] = 0;
    regs.r[1] = (ਪੂਰਨ)ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
    error = _kernel_swi(OS_Screen_ਬਹੁਲਕ, &regs, &regs);
    ਜੇ (error) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    ਲਈ (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    ਵਾਪਸ true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_RISCOS

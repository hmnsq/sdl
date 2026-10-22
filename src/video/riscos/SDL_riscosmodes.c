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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"

#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscosmodes.h"

#ضمن <kernel.h>
#ضمن <swis.h>

تعداد
{
    گهڻائي_FLAG_565 = 1 << 7,

    گهڻائي_FLAG_رنگ_SPACE = 0xF << 12,

    گهڻائي_FLAG_TBGR = 0,
    گهڻائي_FLAG_TRGB = 1 << 14,
    گهڻائي_FLAG_ABGR = 1 << 15,
    گهڻائي_FLAG_ARGB = گهڻائي_FLAG_TRGB | گهڻائي_FLAG_ABGR
};

ساكن ثابت بنية
{
    SDL_PixelFormat pixel_format;
    صحيح modeflags, ncolour, log2bpp;
} گهڻائي_منزل_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, گهڻائي_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, گهڻائي_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, گهڻائي_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, گهڻائي_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, گهڻائي_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, گهڻائي_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, گهڻائي_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, گهڻائي_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, گهڻائي_FLAG_TBGR | گهڻائي_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, گهڻائي_FLAG_TRGB | گهڻائي_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, گهڻائي_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, گهڻائي_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, گهڻائي_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, گهڻائي_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, گهڻائي_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, گهڻائي_FLAG_ARGB, -1, 5 }
};

ساكن SDL_PixelFormat RISCOS_گهڻائي_منزل_Pixel_Format(صحيح ncolour, صحيح modeflags, صحيح log2bpp)
{
    صحيح i;

    لكل (i = 0; i < SDL_arraysize(گهڻائي_منزل_pixelformat); i++) {
        إذا (log2bpp == گهڻائي_منزل_pixelformat[i].log2bpp &&
            (ncolour == گهڻائي_منزل_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (گهڻائي_FLAG_565 | گهڻائي_FLAG_رنگ_SPACE)) == گهڻائي_منزل_pixelformat[i].modeflags) {
            أرجع گهڻائي_منزل_pixelformat[i].pixel_format;
        }
    }

    أرجع SDL_PIXELFORMAT_UNKNOWN;
}

ساكن size_t measure_گهڻائي_بلاڪ(ثابت صحيح *بلاڪ)
{
    size_t بلاڪ_سائيز = ((بلاڪ[0] & 0xFF) == 3) ? 7 : 5;
    طالما (بلاڪ[بلاڪ_سائيز] != -1) {
        بلاڪ_سائيز += 2;
    }
    بلاڪ_سائيز++;

    أرجع بلاڪ_سائيز * 4;
}

ساكن صحيح read_گهڻائي_variable(صحيح *بلاڪ, صحيح var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (صحيح)بلاڪ;
    regs.r[1] = var;
    _kernel_swi(OS_Read_گهڻائي_Variable, &regs, &regs);
    أرجع regs.r[2];
}

ساكن bool read_گهڻائي_بلاڪ(صحيح *بلاڪ, SDL_Display_گهڻائي *گهڻائي, bool extended)
{
    صحيح xres, yres, ncolour, modeflags, log2bpp, شرح;

    إذا ((بلاڪ[0] & 0xFF) == 1) {
        xres = بلاڪ[1];
        yres = بلاڪ[2];
        log2bpp = بلاڪ[3];
        شرح = بلاڪ[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = گهڻائي_FLAG_TBGR;
    } وإلا إذا ((بلاڪ[0] & 0xFF) == 3) {
        xres = بلاڪ[1];
        yres = بلاڪ[2];
        ncolour = بلاڪ[3];
        modeflags = بلاڪ[4];
        log2bpp = بلاڪ[5];
        شرح = بلاڪ[6];
    } وإلا {
        أرجع false;
    }

    إذا (extended) {
        xres = read_گهڻائي_variable(بلاڪ, 11) + 1;
        yres = read_گهڻائي_variable(بلاڪ, 12) + 1;
        log2bpp = read_گهڻائي_variable(بلاڪ, 9);
        ncolour = read_گهڻائي_variable(بلاڪ, 3);
        modeflags = read_گهڻائي_variable(بلاڪ, 0);
    }

    SDL_zerop(گهڻائي);
    گهڻائي->w = xres;
    گهڻائي->h = yres;
    گهڻائي->format = RISCOS_گهڻائي_منزل_Pixel_Format(ncolour, modeflags, log2bpp);
    گهڻائي->refresh_شرح = (عائم)شرح;

    أرجع true;
}

ساكن فراغ *convert_گهڻائي_بلاڪ(ثابت صحيح *بلاڪ)
{
    صحيح xres, yres, log2bpp, شرح, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    صحيح *dst;

    إذا ((بلاڪ[0] & 0xFF) == 1) {
        xres = بلاڪ[1];
        yres = بلاڪ[2];
        log2bpp = بلاڪ[3];
        شرح = بلاڪ[4];
    } وإلا إذا ((بلاڪ[0] & 0xFF) == 3) {
        xres = بلاڪ[1];
        yres = بلاڪ[2];
        ncolour = بلاڪ[3];
        modeflags = بلاڪ[4];
        log2bpp = بلاڪ[5];
        شرح = بلاڪ[6];
    } وإلا {
        أرجع عدم;
    }

    dst = SDL_malloc(40);
    إذا (!dst) {
        أرجع عدم;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = شرح;
    إذا (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    إذا (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    أرجع dst;
}

ساكن فراغ *copy_يادگيري(ثابت فراغ *src, size_t سائيز, size_t alloc)
{
    فراغ *dst = SDL_malloc(alloc);
    إذا (dst) {
        SDL_memcpy(dst, src, سائيز);
    }
    أرجع dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_Display_گهڻائي گهڻائي;
    صحيح *current_گهڻائي;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t سائيز;

    regs.r[0] = 1;
    error = _kernel_swi(OS_Screen_گهڻائي, &regs, &regs);
    إذا (error) {
        أرجع SDL_سيٽ_Error("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_گهڻائي = (صحيح *)regs.r[1];
    إذا (!read_گهڻائي_بلاڪ(current_گهڻائي, &گهڻائي, true)) {
        أرجع SDL_سيٽ_Error("Unsupported mode block format %d", current_گهڻائي[0]);
    }

    سائيز = measure_گهڻائي_بلاڪ(current_گهڻائي);
    گهڻائي.اندروني = copy_يادگيري(current_گهڻائي, سائيز, سائيز);
    إذا (!گهڻائي.اندروني) {
        أرجع false;
    }

    إذا (SDL_جوڙيو_Basic_Video_Display(&گهڻائي) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_گهڻائي گهڻائي;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    فراغ *بلاڪ, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_Screen_گهڻائي, &regs, &regs);
    إذا (error) {
        أرجع SDL_سيٽ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    بلاڪ = SDL_malloc(-regs.r[7]);
    إذا (!بلاڪ) {
        أرجع false;
    }

    regs.r[6] = (صحيح)بلاڪ;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_Screen_گهڻائي, &regs, &regs);
    إذا (error) {
        SDL_free(بلاڪ);
        أرجع SDL_سيٽ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    لكل (pos = بلاڪ; pos < (فراغ *)regs.r[6]; pos += *((صحيح *)pos)) {
        إذا (!read_گهڻائي_بلاڪ(pos + 4, &گهڻائي, false)) {
            استمر;
        }

        إذا (گهڻائي.format == SDL_PIXELFORMAT_UNKNOWN) {
            استمر;
        }

        گهڻائي.اندروني = convert_گهڻائي_بلاڪ(pos + 4);
        إذا (!گهڻائي.اندروني) {
            SDL_free(بلاڪ);
            أرجع false;
        }

        إذا (!SDL_جوڙيو_Fullscreen_Display_گهڻائي(display, &گهڻائي)) {
            SDL_free(گهڻائي.اندروني);
        }
    }

    SDL_free(بلاڪ);
    أرجع true;
}

bool RISCOS_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي)
{
    ثابت حرف disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    صحيح i;

    regs.r[0] = 0;
    regs.r[1] = (صحيح)گهڻائي->اندروني;
    error = _kernel_swi(OS_Screen_گهڻائي, &regs, &regs);
    إذا (error) {
        أرجع SDL_سيٽ_Error("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    لكل (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    أرجع true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_RISCOS

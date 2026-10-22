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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"

#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscosmodes.h"

#ضمن <kernel.h>
#ضمن <swis.h>

تعداد
{
    منوال_FLAG_565 = 1 << 7,

    منوال_FLAG_رنگ_SPACE = 0xF << 12,

    منوال_FLAG_TBGR = 0,
    منوال_FLAG_TRGB = 1 << 14,
    منوال_FLAG_ABGR = 1 << 15,
    منوال_FLAG_ARGB = منوال_FLAG_TRGB | منوال_FLAG_ABGR
};

ساكن ثابت بنية
{
    SDL_PixelFormat pixel_format;
    صحيح modeflags, ncolour, log2bpp;
} منوال_منزل_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, منوال_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, منوال_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, منوال_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, منوال_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, منوال_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, منوال_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, منوال_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, منوال_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, منوال_FLAG_TBGR | منوال_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, منوال_FLAG_TRGB | منوال_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, منوال_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, منوال_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, منوال_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, منوال_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, منوال_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, منوال_FLAG_ARGB, -1, 5 }
};

ساكن SDL_PixelFormat RISCOS_منوال_منزل_Pixel_Format(صحيح ncolour, صحيح modeflags, صحيح log2bpp)
{
    صحيح i;

    لكل (i = 0; i < SDL_arraysize(منوال_منزل_pixelformat); i++) {
        إذا (log2bpp == منوال_منزل_pixelformat[i].log2bpp &&
            (ncolour == منوال_منزل_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (منوال_FLAG_565 | منوال_FLAG_رنگ_SPACE)) == منوال_منزل_pixelformat[i].modeflags) {
            أرجع منوال_منزل_pixelformat[i].pixel_format;
        }
    }

    أرجع SDL_PIXELFORMAT_UNKNOWN;
}

ساكن size_t measure_منوال_بلاک(ثابت صحيح *بلاک)
{
    size_t بلاک_ناپ = ((بلاک[0] & 0xFF) == 3) ? 7 : 5;
    طالما (بلاک[بلاک_ناپ] != -1) {
        بلاک_ناپ += 2;
    }
    بلاک_ناپ++;

    أرجع بلاک_ناپ * 4;
}

ساكن صحيح read_منوال_variable(صحيح *بلاک, صحيح var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (صحيح)بلاک;
    regs.r[1] = var;
    _kernel_swi(OS_Read_منوال_Variable, &regs, &regs);
    أرجع regs.r[2];
}

ساكن bool read_منوال_بلاک(صحيح *بلاک, SDL_Display_منوال *منوال, bool extended)
{
    صحيح xres, yres, ncolour, modeflags, log2bpp, شرح;

    إذا ((بلاک[0] & 0xFF) == 1) {
        xres = بلاک[1];
        yres = بلاک[2];
        log2bpp = بلاک[3];
        شرح = بلاک[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = منوال_FLAG_TBGR;
    } وإلا إذا ((بلاک[0] & 0xFF) == 3) {
        xres = بلاک[1];
        yres = بلاک[2];
        ncolour = بلاک[3];
        modeflags = بلاک[4];
        log2bpp = بلاک[5];
        شرح = بلاک[6];
    } وإلا {
        أرجع false;
    }

    إذا (extended) {
        xres = read_منوال_variable(بلاک, 11) + 1;
        yres = read_منوال_variable(بلاک, 12) + 1;
        log2bpp = read_منوال_variable(بلاک, 9);
        ncolour = read_منوال_variable(بلاک, 3);
        modeflags = read_منوال_variable(بلاک, 0);
    }

    SDL_zerop(منوال);
    منوال->w = xres;
    منوال->h = yres;
    منوال->format = RISCOS_منوال_منزل_Pixel_Format(ncolour, modeflags, log2bpp);
    منوال->refresh_شرح = (عائم)شرح;

    أرجع true;
}

ساكن فراغ *convert_منوال_بلاک(ثابت صحيح *بلاک)
{
    صحيح xres, yres, log2bpp, شرح, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    صحيح *dst;

    إذا ((بلاک[0] & 0xFF) == 1) {
        xres = بلاک[1];
        yres = بلاک[2];
        log2bpp = بلاک[3];
        شرح = بلاک[4];
    } وإلا إذا ((بلاک[0] & 0xFF) == 3) {
        xres = بلاک[1];
        yres = بلاک[2];
        ncolour = بلاک[3];
        modeflags = بلاک[4];
        log2bpp = بلاک[5];
        شرح = بلاک[6];
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

ساكن فراغ *copy_حافظہ(ثابت فراغ *src, size_t ناپ, size_t alloc)
{
    فراغ *dst = SDL_malloc(alloc);
    إذا (dst) {
        SDL_memcpy(dst, src, ناپ);
    }
    أرجع dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;
    صحيح *current_منوال;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t ناپ;

    regs.r[0] = 1;
    error = _kernel_swi(OS_Screen_منوال, &regs, &regs);
    إذا (error) {
        أرجع SDL_سیٹ_Error("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_منوال = (صحيح *)regs.r[1];
    إذا (!read_منوال_بلاک(current_منوال, &منوال, true)) {
        أرجع SDL_سیٹ_Error("Unsupported mode block format %d", current_منوال[0]);
    }

    ناپ = measure_منوال_بلاک(current_منوال);
    منوال.اندرونی = copy_حافظہ(current_منوال, ناپ, ناپ);
    إذا (!منوال.اندرونی) {
        أرجع false;
    }

    إذا (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_منوال منوال;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    فراغ *بلاک, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_Screen_منوال, &regs, &regs);
    إذا (error) {
        أرجع SDL_سیٹ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    بلاک = SDL_malloc(-regs.r[7]);
    إذا (!بلاک) {
        أرجع false;
    }

    regs.r[6] = (صحيح)بلاک;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_Screen_منوال, &regs, &regs);
    إذا (error) {
        SDL_free(بلاک);
        أرجع SDL_سیٹ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    لكل (pos = بلاک; pos < (فراغ *)regs.r[6]; pos += *((صحيح *)pos)) {
        إذا (!read_منوال_بلاک(pos + 4, &منوال, false)) {
            استمر;
        }

        إذا (منوال.format == SDL_PIXELFORMAT_UNKNOWN) {
            استمر;
        }

        منوال.اندرونی = convert_منوال_بلاک(pos + 4);
        إذا (!منوال.اندرونی) {
            SDL_free(بلاک);
            أرجع false;
        }

        إذا (!SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال)) {
            SDL_free(منوال.اندرونی);
        }
    }

    SDL_free(بلاک);
    أرجع true;
}

bool RISCOS_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    ثابت حرف disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    صحيح i;

    regs.r[0] = 0;
    regs.r[1] = (صحيح)منوال->اندرونی;
    error = _kernel_swi(OS_Screen_منوال, &regs, &regs);
    إذا (error) {
        أرجع SDL_سیٹ_Error("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    لكل (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    أرجع true;
}

#جے_انت // SDL_VIDEO_DRIVER_RISCOS

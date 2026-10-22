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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_RISCOS

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"

#ضمن "SDL_riscosvideo.h"
#ضمن "SDL_riscosmodes.h"

#ضمن <kernel.h>
#ضمن <swis.h>

تعداد
{
    نما_FLAG_565 = 1 << 7,

    نما_FLAG_رنگ_SPACE = 0xF << 12,

    نما_FLAG_TBGR = 0,
    نما_FLAG_TRGB = 1 << 14,
    نما_FLAG_ABGR = 1 << 15,
    نما_FLAG_ARGB = نما_FLAG_TRGB | نما_FLAG_ABGR
};

ساكن ثابت بنية
{
    SDL_PixelFormat pixel_format;
    صحيح modeflags, ncolour, log2bpp;
} نما_مقصد_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, نما_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, نما_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, نما_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, نما_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, نما_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, نما_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, نما_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, نما_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, نما_FLAG_TBGR | نما_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, نما_FLAG_TRGB | نما_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, نما_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, نما_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, نما_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, نما_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, نما_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, نما_FLAG_ARGB, -1, 5 }
};

ساكن SDL_PixelFormat RISCOS_نما_مقصد_Pixel_Format(صحيح ncolour, صحيح modeflags, صحيح log2bpp)
{
    صحيح i;

    لكل (i = 0; i < SDL_arraysize(نما_مقصد_pixelformat); i++) {
        إذا (log2bpp == نما_مقصد_pixelformat[i].log2bpp &&
            (ncolour == نما_مقصد_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (نما_FLAG_565 | نما_FLAG_رنگ_SPACE)) == نما_مقصد_pixelformat[i].modeflags) {
            أرجع نما_مقصد_pixelformat[i].pixel_format;
        }
    }

    أرجع SDL_PIXELFORMAT_UNKNOWN;
}

ساكن size_t measure_نما_بلوک(ثابت صحيح *بلوک)
{
    size_t بلوک_اندازه = ((بلوک[0] & 0xFF) == 3) ? 7 : 5;
    طالما (بلوک[بلوک_اندازه] != -1) {
        بلوک_اندازه += 2;
    }
    بلوک_اندازه++;

    أرجع بلوک_اندازه * 4;
}

ساكن صحيح read_نما_variable(صحيح *بلوک, صحيح var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (صحيح)بلوک;
    regs.r[1] = var;
    _kernel_swi(OS_Read_نما_Variable, &regs, &regs);
    أرجع regs.r[2];
}

ساكن bool read_نما_بلوک(صحيح *بلوک, SDL_Display_نما *نما, bool extended)
{
    صحيح xres, yres, ncolour, modeflags, log2bpp, نرخ;

    إذا ((بلوک[0] & 0xFF) == 1) {
        xres = بلوک[1];
        yres = بلوک[2];
        log2bpp = بلوک[3];
        نرخ = بلوک[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = نما_FLAG_TBGR;
    } وإلا إذا ((بلوک[0] & 0xFF) == 3) {
        xres = بلوک[1];
        yres = بلوک[2];
        ncolour = بلوک[3];
        modeflags = بلوک[4];
        log2bpp = بلوک[5];
        نرخ = بلوک[6];
    } وإلا {
        أرجع false;
    }

    إذا (extended) {
        xres = read_نما_variable(بلوک, 11) + 1;
        yres = read_نما_variable(بلوک, 12) + 1;
        log2bpp = read_نما_variable(بلوک, 9);
        ncolour = read_نما_variable(بلوک, 3);
        modeflags = read_نما_variable(بلوک, 0);
    }

    SDL_zerop(نما);
    نما->w = xres;
    نما->h = yres;
    نما->format = RISCOS_نما_مقصد_Pixel_Format(ncolour, modeflags, log2bpp);
    نما->refresh_نرخ = (عائم)نرخ;

    أرجع true;
}

ساكن فراغ *convert_نما_بلوک(ثابت صحيح *بلوک)
{
    صحيح xres, yres, log2bpp, نرخ, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    صحيح *dst;

    إذا ((بلوک[0] & 0xFF) == 1) {
        xres = بلوک[1];
        yres = بلوک[2];
        log2bpp = بلوک[3];
        نرخ = بلوک[4];
    } وإلا إذا ((بلوک[0] & 0xFF) == 3) {
        xres = بلوک[1];
        yres = بلوک[2];
        ncolour = بلوک[3];
        modeflags = بلوک[4];
        log2bpp = بلوک[5];
        نرخ = بلوک[6];
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
    dst[pos++] = نرخ;
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

ساكن فراغ *copy_حافظه(ثابت فراغ *src, size_t اندازه, size_t alloc)
{
    فراغ *dst = SDL_malloc(alloc);
    إذا (dst) {
        SDL_memcpy(dst, src, اندازه);
    }
    أرجع dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_Display_نما نما;
    صحيح *current_نما;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t اندازه;

    regs.r[0] = 1;
    error = _kernel_swi(OS_Screen_نما, &regs, &regs);
    إذا (error) {
        أرجع SDL_مجموعه_Error("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_نما = (صحيح *)regs.r[1];
    إذا (!read_نما_بلوک(current_نما, &نما, true)) {
        أرجع SDL_مجموعه_Error("Unsupported mode block format %d", current_نما[0]);
    }

    اندازه = measure_نما_بلوک(current_نما);
    نما.داخلی = copy_حافظه(current_نما, اندازه, اندازه);
    إذا (!نما.داخلی) {
        أرجع false;
    }

    إذا (SDL_جمع_کن_Basic_Video_Display(&نما) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_نما نما;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    فراغ *بلوک, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_Screen_نما, &regs, &regs);
    إذا (error) {
        أرجع SDL_مجموعه_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    بلوک = SDL_malloc(-regs.r[7]);
    إذا (!بلوک) {
        أرجع false;
    }

    regs.r[6] = (صحيح)بلوک;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_Screen_نما, &regs, &regs);
    إذا (error) {
        SDL_free(بلوک);
        أرجع SDL_مجموعه_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    لكل (pos = بلوک; pos < (فراغ *)regs.r[6]; pos += *((صحيح *)pos)) {
        إذا (!read_نما_بلوک(pos + 4, &نما, false)) {
            استمر;
        }

        إذا (نما.format == SDL_PIXELFORMAT_UNKNOWN) {
            استمر;
        }

        نما.داخلی = convert_نما_بلوک(pos + 4);
        إذا (!نما.داخلی) {
            SDL_free(بلوک);
            أرجع false;
        }

        إذا (!SDL_جمع_کن_Fullscreen_Display_نما(display, &نما)) {
            SDL_free(نما.داخلی);
        }
    }

    SDL_free(بلوک);
    أرجع true;
}

bool RISCOS_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    ثابت حرف disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    صحيح i;

    regs.r[0] = 0;
    regs.r[1] = (صحيح)نما->داخلی;
    error = _kernel_swi(OS_Screen_نما, &regs, &regs);
    إذا (error) {
        أرجع SDL_مجموعه_Error("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    لكل (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    أرجع true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_RISCOS

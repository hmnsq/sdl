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

#ifdef SDL_VIDEO_DRIVER_RISCOS

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_mouse_c.h"

#شامل "SDL_riscosvideo.h"
#شامل "SDL_riscosmodes.h"

#شامل <kernel.h>
#شامل <swis.h>

شمارش
{
    MODE_FLAG_565 = 1 << 7,

    MODE_FLAG_COLOUR_SPACE = 0xF << 12,

    MODE_FLAG_TBGR = 0,
    MODE_FLAG_TRGB = 1 << 14,
    MODE_FLAG_ABGR = 1 << 15,
    MODE_FLAG_ARGB = MODE_FLAG_TRGB | MODE_FLAG_ABGR
};

ایستا ثابت ساختار
{
    SDL_PixelFormat pixel_format;
    صحیح modeflags, ncolour, log2bpp;
} mode_to_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, MODE_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, MODE_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, MODE_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, MODE_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, MODE_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, MODE_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, MODE_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, MODE_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, MODE_FLAG_TBGR | MODE_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, MODE_FLAG_TRGB | MODE_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, MODE_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, MODE_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, MODE_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, MODE_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, MODE_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, MODE_FLAG_ARGB, -1, 5 }
};

ایستا SDL_PixelFormat RISCOS_ModeToPixelFormat(صحیح ncolour, صحیح modeflags, صحیح log2bpp)
{
    صحیح i;

    برای (i = 0; i < SDL_arraysize(mode_to_pixelformat); i++) {
        اگر (log2bpp == mode_to_pixelformat[i].log2bpp &&
            (ncolour == mode_to_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (MODE_FLAG_565 | MODE_FLAG_COLOUR_SPACE)) == mode_to_pixelformat[i].modeflags) {
            بازگشت mode_to_pixelformat[i].pixel_format;
        }
    }

    بازگشت SDL_PIXELFORMAT_UNKNOWN;
}

ایستا size_t measure_mode_block(ثابت صحیح *block)
{
    size_t blockSize = ((block[0] & 0xFF) == 3) ? 7 : 5;
    وقتی (block[blockSize] != -1) {
        blockSize += 2;
    }
    blockSize++;

    بازگشت blockSize * 4;
}

ایستا صحیح read_mode_variable(صحیح *block, صحیح var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (صحیح)block;
    regs.r[1] = var;
    _kernel_swi(OS_ReadModeVariable, &regs, &regs);
    بازگشت regs.r[2];
}

ایستا bool read_mode_block(صحیح *block, SDL_DisplayMode *mode, bool extended)
{
    صحیح xres, yres, ncolour, modeflags, log2bpp, rate;

    اگر ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = MODE_FLAG_TBGR;
    } وگرنه اگر ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } وگرنه {
        بازگشت false;
    }

    اگر (extended) {
        xres = read_mode_variable(block, 11) + 1;
        yres = read_mode_variable(block, 12) + 1;
        log2bpp = read_mode_variable(block, 9);
        ncolour = read_mode_variable(block, 3);
        modeflags = read_mode_variable(block, 0);
    }

    SDL_zerop(mode);
    mode->w = xres;
    mode->h = yres;
    mode->format = RISCOS_ModeToPixelFormat(ncolour, modeflags, log2bpp);
    mode->refresh_rate = (اعشاری)rate;

    بازگشت true;
}

ایستا تهی *convert_mode_block(ثابت صحیح *block)
{
    صحیح xres, yres, log2bpp, rate, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    صحیح *dst;

    اگر ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
    } وگرنه اگر ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } وگرنه {
        بازگشت پوچ;
    }

    dst = SDL_malloc(40);
    اگر (!dst) {
        بازگشت پوچ;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = rate;
    اگر (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    اگر (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    بازگشت dst;
}

ایستا تهی *copy_memory(ثابت تهی *src, size_t size, size_t alloc)
{
    تهی *dst = SDL_malloc(alloc);
    اگر (dst) {
        SDL_memcpy(dst, src, size);
    }
    بازگشت dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;
    صحیح *current_mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t size;

    regs.r[0] = 1;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    اگر (error) {
        بازگشت SDL_SetError("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_mode = (صحیح *)regs.r[1];
    اگر (!read_mode_block(current_mode, &mode, true)) {
        بازگشت SDL_SetError("Unsupported mode block format %d", current_mode[0]);
    }

    size = measure_mode_block(current_mode);
    mode.internal = copy_memory(current_mode, size, size);
    اگر (!mode.internal) {
        بازگشت false;
    }

    اگر (SDL_AddBasicVideoDisplay(&mode) == 0) {
        بازگشت false;
    }
    بازگشت true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayMode mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    تهی *block, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    اگر (error) {
        بازگشت SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    block = SDL_malloc(-regs.r[7]);
    اگر (!block) {
        بازگشت false;
    }

    regs.r[6] = (صحیح)block;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    اگر (error) {
        SDL_free(block);
        بازگشت SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    برای (pos = block; pos < (تهی *)regs.r[6]; pos += *((صحیح *)pos)) {
        اگر (!read_mode_block(pos + 4, &mode, false)) {
            ادامه;
        }

        اگر (mode.format == SDL_PIXELFORMAT_UNKNOWN) {
            ادامه;
        }

        mode.internal = convert_mode_block(pos + 4);
        اگر (!mode.internal) {
            SDL_free(block);
            بازگشت false;
        }

        اگر (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(mode.internal);
        }
    }

    SDL_free(block);
    بازگشت true;
}

bool RISCOS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ثابت نویسه disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    صحیح i;

    regs.r[0] = 0;
    regs.r[1] = (صحیح)mode->internal;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    اگر (error) {
        بازگشت SDL_SetError("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    برای (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    بازگشت true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS

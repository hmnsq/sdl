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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"

#অন্তর্ভাব "SDL_riscosvideo.h"
#অন্তর্ভাব "SDL_riscosmodes.h"

#অন্তর্ভাব <kernel.h>
#অন্তর্ভাব <swis.h>

গণনা
{
    MODE_FLAG_565 = 1 << 7,

    MODE_FLAG_COLOUR_SPACE = 0xF << 12,

    MODE_FLAG_TBGR = 0,
    MODE_FLAG_TRGB = 1 << 14,
    MODE_FLAG_ABGR = 1 << 15,
    MODE_FLAG_ARGB = MODE_FLAG_TRGB | MODE_FLAG_ABGR
};

স্থির ধ্রুবক কাঠামো
{
    SDL_PixelFormat pixel_format;
    পূর্ণসংখ্যা modeflags, ncolour, log2bpp;
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

স্থির SDL_PixelFormat RISCOS_ModeToPixelFormat(পূর্ণসংখ্যা ncolour, পূর্ণসংখ্যা modeflags, পূর্ণসংখ্যা log2bpp)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < SDL_arraysize(mode_to_pixelformat); i++) {
        যদি (log2bpp == mode_to_pixelformat[i].log2bpp &&
            (ncolour == mode_to_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (MODE_FLAG_565 | MODE_FLAG_COLOUR_SPACE)) == mode_to_pixelformat[i].modeflags) {
            ফেরত mode_to_pixelformat[i].pixel_format;
        }
    }

    ফেরত SDL_PIXELFORMAT_UNKNOWN;
}

স্থির size_t measure_mode_block(ধ্রুবক পূর্ণসংখ্যা *block)
{
    size_t block_আকার = ((block[0] & 0xFF) == 3) ? 7 : 5;
    যখন (block[block_আকার] != -1) {
        block_আকার += 2;
    }
    block_আকার++;

    ফেরত block_আকার * 4;
}

স্থির পূর্ণসংখ্যা read_mode_variable(পূর্ণসংখ্যা *block, পূর্ণসংখ্যা var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (পূর্ণসংখ্যা)block;
    regs.r[1] = var;
    _kernel_swi(OS_ReadModeVariable, &regs, &regs);
    ফেরত regs.r[2];
}

স্থির bool read_mode_block(পূর্ণসংখ্যা *block, SDL_DisplayMode *mode, bool extended)
{
    পূর্ণসংখ্যা xres, yres, ncolour, modeflags, log2bpp, rate;

    যদি ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = MODE_FLAG_TBGR;
    } অন্যথা যদি ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } অন্যথা {
        ফেরত false;
    }

    যদি (extended) {
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
    mode->refresh_rate = (দশমিক)rate;

    ফেরত true;
}

স্থির শূন্য *convert_mode_block(ধ্রুবক পূর্ণসংখ্যা *block)
{
    পূর্ণসংখ্যা xres, yres, log2bpp, rate, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    পূর্ণসংখ্যা *dst;

    যদি ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
    } অন্যথা যদি ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } অন্যথা {
        ফেরত ফাঁকা;
    }

    dst = SDL_malloc(40);
    যদি (!dst) {
        ফেরত ফাঁকা;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = rate;
    যদি (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    যদি (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    ফেরত dst;
}

স্থির শূন্য *copy_memory(ধ্রুবক শূন্য *src, size_t আকার_2, size_t alloc)
{
    শূন্য *dst = SDL_malloc(alloc);
    যদি (dst) {
        SDL_memcpy(dst, src, আকার_2);
    }
    ফেরত dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;
    পূর্ণসংখ্যা *current_mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t আকার_2;

    regs.r[0] = 1;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    যদি (error) {
        ফেরত SDL_SetError("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_mode = (পূর্ণসংখ্যা *)regs.r[1];
    যদি (!read_mode_block(current_mode, &mode, true)) {
        ফেরত SDL_SetError("Unsupported mode block format %d", current_mode[0]);
    }

    আকার_2 = measure_mode_block(current_mode);
    mode.internal = copy_memory(current_mode, আকার_2, আকার_2);
    যদি (!mode.internal) {
        ফেরত false;
    }

    যদি (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ফেরত false;
    }
    ফেরত true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayMode mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    শূন্য *block, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    যদি (error) {
        ফেরত SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    block = SDL_malloc(-regs.r[7]);
    যদি (!block) {
        ফেরত false;
    }

    regs.r[6] = (পূর্ণসংখ্যা)block;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    যদি (error) {
        SDL_free(block);
        ফেরত SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    জন্য (pos = block; pos < (শূন্য *)regs.r[6]; pos += *((পূর্ণসংখ্যা *)pos)) {
        যদি (!read_mode_block(pos + 4, &mode, false)) {
            চালু;
        }

        যদি (mode.format == SDL_PIXELFORMAT_UNKNOWN) {
            চালু;
        }

        mode.internal = convert_mode_block(pos + 4);
        যদি (!mode.internal) {
            SDL_free(block);
            ফেরত false;
        }

        যদি (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(mode.internal);
        }
    }

    SDL_free(block);
    ফেরত true;
}

bool RISCOS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ধ্রুবক অক্ষর disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    পূর্ণসংখ্যা i;

    regs.r[0] = 0;
    regs.r[1] = (পূর্ণসংখ্যা)mode->internal;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    যদি (error) {
        ফেরত SDL_SetError("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    জন্য (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    ফেরত true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS

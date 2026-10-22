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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

#அந்தர்பாவ "SDL_riscosvideo.h"
#அந்தர்பாவ "SDL_riscosmodes.h"

#அந்தர்பாவ <kernel.h>
#அந்தர்பாவ <swis.h>

எண்ணிக்கை
{
    MODE_FLAG_565 = 1 << 7,

    MODE_FLAG_COLOUR_SPACE = 0xF << 12,

    MODE_FLAG_TBGR = 0,
    MODE_FLAG_TRGB = 1 << 14,
    MODE_FLAG_ABGR = 1 << 15,
    MODE_FLAG_ARGB = MODE_FLAG_TRGB | MODE_FLAG_ABGR
};

நிலையான மாறிலி கட்டமைப்பு
{
    SDL_PixelFormat pixel_format;
    முழு modeflags, ncolour, log2bpp;
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

நிலையான SDL_PixelFormat RISCOS_ModeToPixelFormat(முழு ncolour, முழு modeflags, முழு log2bpp)
{
    முழு i;

    க்கு (i = 0; i < SDL_arraysize(mode_to_pixelformat); i++) {
        எனில் (log2bpp == mode_to_pixelformat[i].log2bpp &&
            (ncolour == mode_to_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (MODE_FLAG_565 | MODE_FLAG_COLOUR_SPACE)) == mode_to_pixelformat[i].modeflags) {
            திரும்பு mode_to_pixelformat[i].pixel_format;
        }
    }

    திரும்பு SDL_PIXELFORMAT_UNKNOWN;
}

நிலையான size_t measure_mode_block(மாறிலி முழு *block)
{
    size_t blockSize = ((block[0] & 0xFF) == 3) ? 7 : 5;
    போது (block[blockSize] != -1) {
        blockSize += 2;
    }
    blockSize++;

    திரும்பு blockSize * 4;
}

நிலையான முழு read_mode_variable(முழு *block, முழு var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (முழு)block;
    regs.r[1] = var;
    _kernel_swi(OS_ReadModeVariable, &regs, &regs);
    திரும்பு regs.r[2];
}

நிலையான bool read_mode_block(முழு *block, SDL_DisplayMode *mode, bool extended)
{
    முழு xres, yres, ncolour, modeflags, log2bpp, rate;

    எனில் ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = MODE_FLAG_TBGR;
    } இல்லையெனில் எனில் ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } இல்லையெனில் {
        திரும்பு false;
    }

    எனில் (extended) {
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
    mode->refresh_rate = (தசம)rate;

    திரும்பு true;
}

நிலையான வெறுமை *convert_mode_block(மாறிலி முழு *block)
{
    முழு xres, yres, log2bpp, rate, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    முழு *dst;

    எனில் ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
    } இல்லையெனில் எனில் ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } இல்லையெனில் {
        திரும்பு வெற்று;
    }

    dst = SDL_malloc(40);
    எனில் (!dst) {
        திரும்பு வெற்று;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = rate;
    எனில் (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    எனில் (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    திரும்பு dst;
}

நிலையான வெறுமை *copy_memory(மாறிலி வெறுமை *src, size_t size, size_t alloc)
{
    வெறுமை *dst = SDL_malloc(alloc);
    எனில் (dst) {
        SDL_memcpy(dst, src, size);
    }
    திரும்பு dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;
    முழு *current_mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t size;

    regs.r[0] = 1;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    எனில் (error) {
        திரும்பு SDL_SetError("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_mode = (முழு *)regs.r[1];
    எனில் (!read_mode_block(current_mode, &mode, true)) {
        திரும்பு SDL_SetError("Unsupported mode block format %d", current_mode[0]);
    }

    size = measure_mode_block(current_mode);
    mode.internal = copy_memory(current_mode, size, size);
    எனில் (!mode.internal) {
        திரும்பு false;
    }

    எனில் (SDL_AddBasicVideoDisplay(&mode) == 0) {
        திரும்பு false;
    }
    திரும்பு true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayMode mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    வெறுமை *block, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    எனில் (error) {
        திரும்பு SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    block = SDL_malloc(-regs.r[7]);
    எனில் (!block) {
        திரும்பு false;
    }

    regs.r[6] = (முழு)block;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    எனில் (error) {
        SDL_free(block);
        திரும்பு SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    க்கு (pos = block; pos < (வெறுமை *)regs.r[6]; pos += *((முழு *)pos)) {
        எனில் (!read_mode_block(pos + 4, &mode, false)) {
            தொடர்;
        }

        எனில் (mode.format == SDL_PIXELFORMAT_UNKNOWN) {
            தொடர்;
        }

        mode.internal = convert_mode_block(pos + 4);
        எனில் (!mode.internal) {
            SDL_free(block);
            திரும்பு false;
        }

        எனில் (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(mode.internal);
        }
    }

    SDL_free(block);
    திரும்பு true;
}

bool RISCOS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    மாறிலி எழுத்து disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    முழு i;

    regs.r[0] = 0;
    regs.r[1] = (முழு)mode->internal;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    எனில் (error) {
        திரும்பு SDL_SetError("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    க்கு (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    திரும்பு true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS

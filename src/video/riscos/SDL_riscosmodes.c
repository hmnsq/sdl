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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_RISCOS

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_riscosvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_riscosmodes.h"

#ଅନ୍ତର୍ଭାଵ <kernel.h>
#ଅନ୍ତର୍ଭାଵ <swis.h>

ଗଣନା
{
    MODE_FLAG_565 = 1 << 7,

    MODE_FLAG_COLOUR_SPACE = 0xF << 12,

    MODE_FLAG_TBGR = 0,
    MODE_FLAG_TRGB = 1 << 14,
    MODE_FLAG_ABGR = 1 << 15,
    MODE_FLAG_ARGB = MODE_FLAG_TRGB | MODE_FLAG_ABGR
};

ସ୍ଥିର ଅଚଳ ସଂରଚନା
{
    SDL_PixelFormat pixel_format;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା modeflags, ncolour, log2bpp;
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

ସ୍ଥିର SDL_PixelFormat RISCOS_ModeToPixelFormat(ପୂର୍ଣ୍ଣସଂଖ୍ୟା ncolour, ପୂର୍ଣ୍ଣସଂଖ୍ୟା modeflags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା log2bpp)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < SDL_arraysize(mode_to_pixelformat); i++) {
        ଯଦି (log2bpp == mode_to_pixelformat[i].log2bpp &&
            (ncolour == mode_to_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (MODE_FLAG_565 | MODE_FLAG_COLOUR_SPACE)) == mode_to_pixelformat[i].modeflags) {
            ଫେରନ୍ତୁ mode_to_pixelformat[i].pixel_format;
        }
    }

    ଫେରନ୍ତୁ SDL_PIXELFORMAT_UNKNOWN;
}

ସ୍ଥିର size_t measure_mode_block(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *block)
{
    size_t blockSize = ((block[0] & 0xFF) == 3) ? 7 : 5;
    ଯେତେବେଳେ (block[blockSize] != -1) {
        blockSize += 2;
    }
    blockSize++;

    ଫେରନ୍ତୁ blockSize * 4;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_mode_variable(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *block, ପୂର୍ଣ୍ଣସଂଖ୍ୟା var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)block;
    regs.r[1] = var;
    _kernel_swi(OS_ReadModeVariable, &regs, &regs);
    ଫେରନ୍ତୁ regs.r[2];
}

ସ୍ଥିର bool read_mode_block(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *block, SDL_DisplayMode *mode, bool extended)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା xres, yres, ncolour, modeflags, log2bpp, rate;

    ଯଦି ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = MODE_FLAG_TBGR;
    } ଅନ୍ୟଥା ଯଦି ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (extended) {
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
    mode->refresh_rate = (ଦଶମିକ)rate;

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ *convert_mode_block(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *block)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା xres, yres, log2bpp, rate, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst;

    ଯଦି ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
    } ଅନ୍ୟଥା ଯଦି ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    dst = SDL_malloc(40);
    ଯଦି (!dst) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = rate;
    ଯଦି (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    ଯଦି (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    ଫେରନ୍ତୁ dst;
}

ସ୍ଥିର ଶୂନ୍ୟ *copy_memory(ଅଚଳ ଶୂନ୍ୟ *src, size_t size, size_t alloc)
{
    ଶୂନ୍ୟ *dst = SDL_malloc(alloc);
    ଯଦି (dst) {
        SDL_memcpy(dst, src, size);
    }
    ଫେରନ୍ତୁ dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *current_mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t size;

    regs.r[0] = 1;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    ଯଦି (error) {
        ଫେରନ୍ତୁ SDL_SetError("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_mode = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)regs.r[1];
    ଯଦି (!read_mode_block(current_mode, &mode, true)) {
        ଫେରନ୍ତୁ SDL_SetError("Unsupported mode block format %d", current_mode[0]);
    }

    size = measure_mode_block(current_mode);
    mode.internal = copy_memory(current_mode, size, size);
    ଯଦି (!mode.internal) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayMode mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    ଶୂନ୍ୟ *block, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    ଯଦି (error) {
        ଫେରନ୍ତୁ SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    block = SDL_malloc(-regs.r[7]);
    ଯଦି (!block) {
        ଫେରନ୍ତୁ false;
    }

    regs.r[6] = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)block;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    ଯଦି (error) {
        SDL_free(block);
        ଫେରନ୍ତୁ SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    ପାଇଁ (pos = block; pos < (ଶୂନ୍ୟ *)regs.r[6]; pos += *((ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)pos)) {
        ଯଦି (!read_mode_block(pos + 4, &mode, false)) {
            ଜାରି;
        }

        ଯଦି (mode.format == SDL_PIXELFORMAT_UNKNOWN) {
            ଜାରି;
        }

        mode.internal = convert_mode_block(pos + 4);
        ଯଦି (!mode.internal) {
            SDL_free(block);
            ଫେରନ୍ତୁ false;
        }

        ଯଦି (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(mode.internal);
        }
    }

    SDL_free(block);
    ଫେରନ୍ତୁ true;
}

bool RISCOS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ଅଚଳ ଅକ୍ଷର disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    regs.r[0] = 0;
    regs.r[1] = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)mode->internal;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    ଯଦି (error) {
        ଫେରନ୍ତୁ SDL_SetError("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    ପାଇଁ (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    ଫେରନ୍ତୁ true;
}

#endif // SDL_VIDEO_DRIVER_RISCOS

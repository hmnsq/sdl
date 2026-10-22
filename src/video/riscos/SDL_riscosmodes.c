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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_RISCOS

#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_mouse_c.h"

#समावेश "SDL_riscosvideo.h"
#समावेश "SDL_riscosmodes.h"

#समावेश <kernel.h>
#समावेश <swis.h>

क्रमागत
{
    MODE_FLAG_565 = 1 << 7,

    MODE_FLAG_COLOUR_SPACE = 0xF << 12,

    MODE_FLAG_TBGR = 0,
    MODE_FLAG_TRGB = 1 << 14,
    MODE_FLAG_ABGR = 1 << 15,
    MODE_FLAG_ARGB = MODE_FLAG_TRGB | MODE_FLAG_ABGR
};

अटल स्थिर काष्ठा
{
    SDL_PixelFormat pixel_format;
    पूर्णांक modeflags, ncolour, log2bpp;
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

अटल SDL_PixelFormat RISCOS_ModeToPixelFormat(पूर्णांक ncolour, पूर्णांक modeflags, पूर्णांक log2bpp)
{
    पूर्णांक i;

    क्रम (i = 0; i < SDL_arraysize(mode_to_pixelformat); i++) {
        अगर (log2bpp == mode_to_pixelformat[i].log2bpp &&
            (ncolour == mode_to_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (MODE_FLAG_565 | MODE_FLAG_COLOUR_SPACE)) == mode_to_pixelformat[i].modeflags) {
            वापस mode_to_pixelformat[i].pixel_format;
        }
    }

    वापस SDL_PIXELFORMAT_UNKNOWN;
}

अटल माप_प्रकार measure_mode_block(स्थिर पूर्णांक *block)
{
    माप_प्रकार block_आकार = ((block[0] & 0xFF) == 3) ? 7 : 5;
    जबतक (block[block_आकार] != -1) {
        block_आकार += 2;
    }
    block_आकार++;

    वापस block_आकार * 4;
}

अटल पूर्णांक read_mode_variable(पूर्णांक *block, पूर्णांक var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (पूर्णांक)block;
    regs.r[1] = var;
    _kernel_swi(OS_ReadModeVariable, &regs, &regs);
    वापस regs.r[2];
}

अटल bool read_mode_block(पूर्णांक *block, SDL_DisplayMode *mode, bool extended)
{
    पूर्णांक xres, yres, ncolour, modeflags, log2bpp, rate;

    अगर ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = MODE_FLAG_TBGR;
    } अन्यथा अगर ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } अन्यथा {
        वापस false;
    }

    अगर (extended) {
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
    mode->refresh_rate = (भग्न)rate;

    वापस true;
}

अटल व्योम *convert_mode_block(स्थिर पूर्णांक *block)
{
    पूर्णांक xres, yres, log2bpp, rate, ncolour = 0, modeflags = 0;
    माप_प्रकार pos = 0;
    पूर्णांक *dst;

    अगर ((block[0] & 0xFF) == 1) {
        xres = block[1];
        yres = block[2];
        log2bpp = block[3];
        rate = block[4];
    } अन्यथा अगर ((block[0] & 0xFF) == 3) {
        xres = block[1];
        yres = block[2];
        ncolour = block[3];
        modeflags = block[4];
        log2bpp = block[5];
        rate = block[6];
    } अन्यथा {
        वापस शून्य;
    }

    dst = SDL_malloc(40);
    अगर (!dst) {
        वापस शून्य;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = rate;
    अगर (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    अगर (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    वापस dst;
}

अटल व्योम *copy_memory(स्थिर व्योम *src, माप_प्रकार आकार, माप_प्रकार alloc)
{
    व्योम *dst = SDL_malloc(alloc);
    अगर (dst) {
        SDL_memcpy(dst, src, आकार);
    }
    वापस dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;
    पूर्णांक *current_mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    माप_प्रकार आकार;

    regs.r[0] = 1;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    अगर (error) {
        वापस SDL_SetError("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_mode = (पूर्णांक *)regs.r[1];
    अगर (!read_mode_block(current_mode, &mode, true)) {
        वापस SDL_SetError("Unsupported mode block format %d", current_mode[0]);
    }

    आकार = measure_mode_block(current_mode);
    mode.internal = copy_memory(current_mode, आकार, आकार);
    अगर (!mode.internal) {
        वापस false;
    }

    अगर (SDL_AddBasicVideoDisplay(&mode) == 0) {
        वापस false;
    }
    वापस true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayMode mode;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    व्योम *block, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    अगर (error) {
        वापस SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    block = SDL_malloc(-regs.r[7]);
    अगर (!block) {
        वापस false;
    }

    regs.r[6] = (पूर्णांक)block;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    अगर (error) {
        SDL_free(block);
        वापस SDL_SetError("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    क्रम (pos = block; pos < (व्योम *)regs.r[6]; pos += *((पूर्णांक *)pos)) {
        अगर (!read_mode_block(pos + 4, &mode, false)) {
            जारी;
        }

        अगर (mode.format == SDL_PIXELFORMAT_UNKNOWN) {
            जारी;
        }

        mode.internal = convert_mode_block(pos + 4);
        अगर (!mode.internal) {
            SDL_free(block);
            वापस false;
        }

        अगर (!SDL_AddFullscreenDisplayMode(display, &mode)) {
            SDL_free(mode.internal);
        }
    }

    SDL_free(block);
    वापस true;
}

bool RISCOS_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    स्थिर अक्षर disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    पूर्णांक i;

    regs.r[0] = 0;
    regs.r[1] = (पूर्णांक)mode->internal;
    error = _kernel_swi(OS_ScreenMode, &regs, &regs);
    अगर (error) {
        वापस SDL_SetError("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    क्रम (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    वापस true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_RISCOS

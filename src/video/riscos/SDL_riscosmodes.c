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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RISCOS

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

#अन्तर्भाव "SDL_riscosvideo.h"
#अन्तर्भाव "SDL_riscosmodes.h"

#अन्तर्भाव <kernel.h>
#अन्तर्भाव <swis.h>

गणना
{
    बहुलकम्_FLAG_565 = 1 << 7,

    बहुलकम्_FLAG_रङ्गः_SPACE = 0xF << 12,

    बहुलकम्_FLAG_TBGR = 0,
    बहुलकम्_FLAG_TRGB = 1 << 14,
    बहुलकम्_FLAG_ABGR = 1 << 15,
    बहुलकम्_FLAG_ARGB = बहुलकम्_FLAG_TRGB | बहुलकम्_FLAG_ABGR
};

स्थिर ध्रुव संरचना
{
    SDL_PixelFormat pixel_format;
    पूर्णाङ्क modeflags, ncolour, log2bpp;
} बहुलकम्_गन्तव्यम्_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, बहुलकम्_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, बहुलकम्_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, बहुलकम्_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, बहुलकम्_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, बहुलकम्_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, बहुलकम्_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, बहुलकम्_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, बहुलकम्_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, बहुलकम्_FLAG_TBGR | बहुलकम्_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, बहुलकम्_FLAG_TRGB | बहुलकम्_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, बहुलकम्_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, बहुलकम्_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, बहुलकम्_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, बहुलकम्_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, बहुलकम्_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, बहुलकम्_FLAG_ARGB, -1, 5 }
};

स्थिर SDL_PixelFormat RISCOS_बहुलकम्_गन्तव्यम्_Pixel_Format(पूर्णाङ्क ncolour, पूर्णाङ्क modeflags, पूर्णाङ्क log2bpp)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < SDL_arraysize(बहुलकम्_गन्तव्यम्_pixelformat); i++) {
        यदि (log2bpp == बहुलकम्_गन्तव्यम्_pixelformat[i].log2bpp &&
            (ncolour == बहुलकम्_गन्तव्यम्_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (बहुलकम्_FLAG_565 | बहुलकम्_FLAG_रङ्गः_SPACE)) == बहुलकम्_गन्तव्यम्_pixelformat[i].modeflags) {
            प्रत्यागम बहुलकम्_गन्तव्यम्_pixelformat[i].pixel_format;
        }
    }

    प्रत्यागम SDL_PIXELFORMAT_UNKNOWN;
}

स्थिर size_t measure_बहुलकम्_खण्डम्(ध्रुव पूर्णाङ्क *खण्डम्)
{
    size_t खण्डम्_आकार = ((खण्डम्[0] & 0xFF) == 3) ? 7 : 5;
    यावत् (खण्डम्[खण्डम्_आकार] != -1) {
        खण्डम्_आकार += 2;
    }
    खण्डम्_आकार++;

    प्रत्यागम खण्डम्_आकार * 4;
}

स्थिर पूर्णाङ्क read_बहुलकम्_variable(पूर्णाङ्क *खण्डम्, पूर्णाङ्क var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (पूर्णाङ्क)खण्डम्;
    regs.r[1] = var;
    _kernel_swi(OS_Read_बहुलकम्_Variable, &regs, &regs);
    प्रत्यागम regs.r[2];
}

स्थिर bool read_बहुलकम्_खण्डम्(पूर्णाङ्क *खण्डम्, SDL_Display_बहुलकम् *बहुलकम्, bool extended)
{
    पूर्णाङ्क xres, yres, ncolour, modeflags, log2bpp, दरः;

    यदि ((खण्डम्[0] & 0xFF) == 1) {
        xres = खण्डम्[1];
        yres = खण्डम्[2];
        log2bpp = खण्डम्[3];
        दरः = खण्डम्[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = बहुलकम्_FLAG_TBGR;
    } अन्यथा यदि ((खण्डम्[0] & 0xFF) == 3) {
        xres = खण्डम्[1];
        yres = खण्डम्[2];
        ncolour = खण्डम्[3];
        modeflags = खण्डम्[4];
        log2bpp = खण्डम्[5];
        दरः = खण्डम्[6];
    } अन्यथा {
        प्रत्यागम false;
    }

    यदि (extended) {
        xres = read_बहुलकम्_variable(खण्डम्, 11) + 1;
        yres = read_बहुलकम्_variable(खण्डम्, 12) + 1;
        log2bpp = read_बहुलकम्_variable(खण्डम्, 9);
        ncolour = read_बहुलकम्_variable(खण्डम्, 3);
        modeflags = read_बहुलकम्_variable(खण्डम्, 0);
    }

    SDL_zerop(बहुलकम्);
    बहुलकम्->w = xres;
    बहुलकम्->h = yres;
    बहुलकम्->format = RISCOS_बहुलकम्_गन्तव्यम्_Pixel_Format(ncolour, modeflags, log2bpp);
    बहुलकम्->refresh_दरः = (भिन्न)दरः;

    प्रत्यागम true;
}

स्थिर शून्य *convert_बहुलकम्_खण्डम्(ध्रुव पूर्णाङ्क *खण्डम्)
{
    पूर्णाङ्क xres, yres, log2bpp, दरः, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    पूर्णाङ्क *dst;

    यदि ((खण्डम्[0] & 0xFF) == 1) {
        xres = खण्डम्[1];
        yres = खण्डम्[2];
        log2bpp = खण्डम्[3];
        दरः = खण्डम्[4];
    } अन्यथा यदि ((खण्डम्[0] & 0xFF) == 3) {
        xres = खण्डम्[1];
        yres = खण्डम्[2];
        ncolour = खण्डम्[3];
        modeflags = खण्डम्[4];
        log2bpp = खण्डम्[5];
        दरः = खण्डम्[6];
    } अन्यथा {
        प्रत्यागम रिक्त;
    }

    dst = SDL_malloc(40);
    यदि (!dst) {
        प्रत्यागम रिक्त;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = दरः;
    यदि (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    यदि (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    प्रत्यागम dst;
}

स्थिर शून्य *copy_स्मृतिः(ध्रुव शून्य *src, size_t आकार, size_t alloc)
{
    शून्य *dst = SDL_malloc(alloc);
    यदि (dst) {
        SDL_memcpy(dst, src, आकार);
    }
    प्रत्यागम dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_Display_बहुलकम् बहुलकम्;
    पूर्णाङ्क *current_बहुलकम्;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t आकार;

    regs.r[0] = 1;
    error = _kernel_swi(OS_Screen_बहुलकम्, &regs, &regs);
    यदि (error) {
        प्रत्यागम SDL_समुच्चयः_Error("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_बहुलकम् = (पूर्णाङ्क *)regs.r[1];
    यदि (!read_बहुलकम्_खण्डम्(current_बहुलकम्, &बहुलकम्, true)) {
        प्रत्यागम SDL_समुच्चयः_Error("Unsupported mode block format %d", current_बहुलकम्[0]);
    }

    आकार = measure_बहुलकम्_खण्डम्(current_बहुलकम्);
    बहुलकम्.आन्तरिकम् = copy_स्मृतिः(current_बहुलकम्, आकार, आकार);
    यदि (!बहुलकम्.आन्तरिकम्) {
        प्रत्यागम false;
    }

    यदि (SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्) == 0) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_बहुलकम् बहुलकम्;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    शून्य *खण्डम्, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_Screen_बहुलकम्, &regs, &regs);
    यदि (error) {
        प्रत्यागम SDL_समुच्चयः_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    खण्डम् = SDL_malloc(-regs.r[7]);
    यदि (!खण्डम्) {
        प्रत्यागम false;
    }

    regs.r[6] = (पूर्णाङ्क)खण्डम्;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_Screen_बहुलकम्, &regs, &regs);
    यदि (error) {
        SDL_free(खण्डम्);
        प्रत्यागम SDL_समुच्चयः_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    प्रति (pos = खण्डम्; pos < (शून्य *)regs.r[6]; pos += *((पूर्णाङ्क *)pos)) {
        यदि (!read_बहुलकम्_खण्डम्(pos + 4, &बहुलकम्, false)) {
            अनुवर्त;
        }

        यदि (बहुलकम्.format == SDL_PIXELFORMAT_UNKNOWN) {
            अनुवर्त;
        }

        बहुलकम्.आन्तरिकम् = convert_बहुलकम्_खण्डम्(pos + 4);
        यदि (!बहुलकम्.आन्तरिकम्) {
            SDL_free(खण्डम्);
            प्रत्यागम false;
        }

        यदि (!SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्)) {
            SDL_free(बहुलकम्.आन्तरिकम्);
        }
    }

    SDL_free(खण्डम्);
    प्रत्यागम true;
}

bool RISCOS_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    ध्रुव वर्ण disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    पूर्णाङ्क i;

    regs.r[0] = 0;
    regs.r[1] = (पूर्णाङ्क)बहुलकम्->आन्तरिकम्;
    error = _kernel_swi(OS_Screen_बहुलकम्, &regs, &regs);
    यदि (error) {
        प्रत्यागम SDL_समुच्चयः_Error("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    प्रति (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    प्रत्यागम true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_RISCOS

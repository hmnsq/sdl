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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_RISCOS

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

#అన్తర్భావ "SDL_riscosvideo.h"
#అన్తర్భావ "SDL_riscosmodes.h"

#అన్తర్భావ <kernel.h>
#అన్తర్భావ <swis.h>

గణన
{
    బహుళకం_FLAG_565 = 1 << 7,

    బహుళకం_FLAG_రంగు_SPACE = 0xF << 12,

    బహుళకం_FLAG_TBGR = 0,
    బహుళకం_FLAG_TRGB = 1 << 14,
    బహుళకం_FLAG_ABGR = 1 << 15,
    బహుళకం_FLAG_ARGB = బహుళకం_FLAG_TRGB | బహుళకం_FLAG_ABGR
};

స్థిర స్థిరరాశి నిర్మాణం
{
    SDL_PixelFormat pixel_format;
    పూర్ణాంకం modeflags, ncolour, log2bpp;
} బహుళకం_గమ్యం_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, బహుళకం_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, బహుళకం_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, బహుళకం_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, బహుళకం_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, బహుళకం_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, బహుళకం_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, బహుళకం_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, బహుళకం_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, బహుళకం_FLAG_TBGR | బహుళకం_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, బహుళకం_FLAG_TRGB | బహుళకం_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, బహుళకం_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, బహుళకం_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, బహుళకం_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, బహుళకం_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, బహుళకం_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, బహుళకం_FLAG_ARGB, -1, 5 }
};

స్థిర SDL_PixelFormat RISCOS_బహుళకం_గమ్యం_Pixel_Format(పూర్ణాంకం ncolour, పూర్ణాంకం modeflags, పూర్ణాంకం log2bpp)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < SDL_arraysize(బహుళకం_గమ్యం_pixelformat); i++) {
        ఒకవేళ (log2bpp == బహుళకం_గమ్యం_pixelformat[i].log2bpp &&
            (ncolour == బహుళకం_గమ్యం_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (బహుళకం_FLAG_565 | బహుళకం_FLAG_రంగు_SPACE)) == బహుళకం_గమ్యం_pixelformat[i].modeflags) {
            తిరిగి బహుళకం_గమ్యం_pixelformat[i].pixel_format;
        }
    }

    తిరిగి SDL_PIXELFORMAT_UNKNOWN;
}

స్థిర size_t measure_బహుళకం_ఖండం(స్థిరరాశి పూర్ణాంకం *ఖండం)
{
    size_t ఖండం_కొలత = ((ఖండం[0] & 0xFF) == 3) ? 7 : 5;
    అయితే (ఖండం[ఖండం_కొలత] != -1) {
        ఖండం_కొలత += 2;
    }
    ఖండం_కొలత++;

    తిరిగి ఖండం_కొలత * 4;
}

స్థిర పూర్ణాంకం read_బహుళకం_variable(పూర్ణాంకం *ఖండం, పూర్ణాంకం var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (పూర్ణాంకం)ఖండం;
    regs.r[1] = var;
    _kernel_swi(OS_Read_బహుళకం_Variable, &regs, &regs);
    తిరిగి regs.r[2];
}

స్థిర bool read_బహుళకం_ఖండం(పూర్ణాంకం *ఖండం, SDL_Display_బహుళకం *బహుళకం, bool extended)
{
    పూర్ణాంకం xres, yres, ncolour, modeflags, log2bpp, రేటు;

    ఒకవేళ ((ఖండం[0] & 0xFF) == 1) {
        xres = ఖండం[1];
        yres = ఖండం[2];
        log2bpp = ఖండం[3];
        రేటు = ఖండం[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = బహుళకం_FLAG_TBGR;
    } లేకపోతే ఒకవేళ ((ఖండం[0] & 0xFF) == 3) {
        xres = ఖండం[1];
        yres = ఖండం[2];
        ncolour = ఖండం[3];
        modeflags = ఖండం[4];
        log2bpp = ఖండం[5];
        రేటు = ఖండం[6];
    } లేకపోతే {
        తిరిగి false;
    }

    ఒకవేళ (extended) {
        xres = read_బహుళకం_variable(ఖండం, 11) + 1;
        yres = read_బహుళకం_variable(ఖండం, 12) + 1;
        log2bpp = read_బహుళకం_variable(ఖండం, 9);
        ncolour = read_బహుళకం_variable(ఖండం, 3);
        modeflags = read_బహుళకం_variable(ఖండం, 0);
    }

    SDL_zerop(బహుళకం);
    బహుళకం->w = xres;
    బహుళకం->h = yres;
    బహుళకం->format = RISCOS_బహుళకం_గమ్యం_Pixel_Format(ncolour, modeflags, log2bpp);
    బహుళకం->refresh_రేటు = (దశాంశం)రేటు;

    తిరిగి true;
}

స్థిర శూన్య *convert_బహుళకం_ఖండం(స్థిరరాశి పూర్ణాంకం *ఖండం)
{
    పూర్ణాంకం xres, yres, log2bpp, రేటు, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    పూర్ణాంకం *dst;

    ఒకవేళ ((ఖండం[0] & 0xFF) == 1) {
        xres = ఖండం[1];
        yres = ఖండం[2];
        log2bpp = ఖండం[3];
        రేటు = ఖండం[4];
    } లేకపోతే ఒకవేళ ((ఖండం[0] & 0xFF) == 3) {
        xres = ఖండం[1];
        yres = ఖండం[2];
        ncolour = ఖండం[3];
        modeflags = ఖండం[4];
        log2bpp = ఖండం[5];
        రేటు = ఖండం[6];
    } లేకపోతే {
        తిరిగి ఖాళీ;
    }

    dst = SDL_malloc(40);
    ఒకవేళ (!dst) {
        తిరిగి ఖాళీ;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = రేటు;
    ఒకవేళ (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    ఒకవేళ (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    తిరిగి dst;
}

స్థిర శూన్య *copy_జ్ఞాపకం(స్థిరరాశి శూన్య *src, size_t కొలత, size_t alloc)
{
    శూన్య *dst = SDL_malloc(alloc);
    ఒకవేళ (dst) {
        SDL_memcpy(dst, src, కొలత);
    }
    తిరిగి dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_Display_బహుళకం బహుళకం;
    పూర్ణాంకం *current_బహుళకం;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t కొలత;

    regs.r[0] = 1;
    error = _kernel_swi(OS_Screen_బహుళకం, &regs, &regs);
    ఒకవేళ (error) {
        తిరిగి SDL_సమితి_Error("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_బహుళకం = (పూర్ణాంకం *)regs.r[1];
    ఒకవేళ (!read_బహుళకం_ఖండం(current_బహుళకం, &బహుళకం, true)) {
        తిరిగి SDL_సమితి_Error("Unsupported mode block format %d", current_బహుళకం[0]);
    }

    కొలత = measure_బహుళకం_ఖండం(current_బహుళకం);
    బహుళకం.అంతర్గత = copy_జ్ఞాపకం(current_బహుళకం, కొలత, కొలత);
    ఒకవేళ (!బహుళకం.అంతర్గత) {
        తిరిగి false;
    }

    ఒకవేళ (SDL_కూడు_Basic_Video_Display(&బహుళకం) == 0) {
        తిరిగి false;
    }
    తిరిగి true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_బహుళకం బహుళకం;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    శూన్య *ఖండం, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_Screen_బహుళకం, &regs, &regs);
    ఒకవేళ (error) {
        తిరిగి SDL_సమితి_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    ఖండం = SDL_malloc(-regs.r[7]);
    ఒకవేళ (!ఖండం) {
        తిరిగి false;
    }

    regs.r[6] = (పూర్ణాంకం)ఖండం;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_Screen_బహుళకం, &regs, &regs);
    ఒకవేళ (error) {
        SDL_free(ఖండం);
        తిరిగి SDL_సమితి_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    కొరకు (pos = ఖండం; pos < (శూన్య *)regs.r[6]; pos += *((పూర్ణాంకం *)pos)) {
        ఒకవేళ (!read_బహుళకం_ఖండం(pos + 4, &బహుళకం, false)) {
            కొనసాగు;
        }

        ఒకవేళ (బహుళకం.format == SDL_PIXELFORMAT_UNKNOWN) {
            కొనసాగు;
        }

        బహుళకం.అంతర్గత = convert_బహుళకం_ఖండం(pos + 4);
        ఒకవేళ (!బహుళకం.అంతర్గత) {
            SDL_free(ఖండం);
            తిరిగి false;
        }

        ఒకవేళ (!SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం)) {
            SDL_free(బహుళకం.అంతర్గత);
        }
    }

    SDL_free(ఖండం);
    తిరిగి true;
}

bool RISCOS_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    స్థిరరాశి అక్షరం disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    పూర్ణాంకం i;

    regs.r[0] = 0;
    regs.r[1] = (పూర్ణాంకం)బహుళకం->అంతర్గత;
    error = _kernel_swi(OS_Screen_బహుళకం, &regs, &regs);
    ఒకవేళ (error) {
        తిరిగి SDL_సమితి_Error("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    కొరకు (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    తిరిగి true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_RISCOS

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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RISCOS

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_riscosvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_riscosmodes.h"

#ಅನ್ತರ್ಭಾವ <kernel.h>
#ಅನ್ತರ್ಭಾವ <swis.h>

ಎಣಿಕೆ
{
    ಬಹುಲಕ_FLAG_565 = 1 << 7,

    ಬಹುಲಕ_FLAG_ಬಣ್ಣ_SPACE = 0xF << 12,

    ಬಹುಲಕ_FLAG_TBGR = 0,
    ಬಹುಲಕ_FLAG_TRGB = 1 << 14,
    ಬಹುಲಕ_FLAG_ABGR = 1 << 15,
    ಬಹುಲಕ_FLAG_ARGB = ಬಹುಲಕ_FLAG_TRGB | ಬಹುಲಕ_FLAG_ABGR
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ
{
    SDL_PixelFormat pixel_format;
    ಪೂರ್ಣಾಂಕ modeflags, ncolour, log2bpp;
} ಬಹುಲಕ_ಗಮ್ಯ_pixelformat[] = {
    // { SDL_PIXELFORMAT_INDEX1LSB, 0, 1, 0 },
    // { SDL_PIXELFORMAT_INDEX2LSB, 0, 3, 1 },
    // { SDL_PIXELFORMAT_INDEX4LSB, 0, 15, 2 },
    // { SDL_PIXELFORMAT_INDEX8,    MODE_FLAG_565, 255, 3 },
    { SDL_PIXELFORMAT_XBGR1555, ಬಹುಲಕ_FLAG_TBGR, 65535, 4 },
    { SDL_PIXELFORMAT_XRGB1555, ಬಹುಲಕ_FLAG_TRGB, 65535, 4 },
    { SDL_PIXELFORMAT_ABGR1555, ಬಹುಲಕ_FLAG_ABGR, 65535, 4 },
    { SDL_PIXELFORMAT_ARGB1555, ಬಹುಲಕ_FLAG_ARGB, 65535, 4 },
    { SDL_PIXELFORMAT_XBGR4444, ಬಹುಲಕ_FLAG_TBGR, 4095, 4 },
    { SDL_PIXELFORMAT_XRGB4444, ಬಹುಲಕ_FLAG_TRGB, 4095, 4 },
    { SDL_PIXELFORMAT_ABGR4444, ಬಹುಲಕ_FLAG_ABGR, 4095, 4 },
    { SDL_PIXELFORMAT_ARGB4444, ಬಹುಲಕ_FLAG_ARGB, 4095, 4 },
    { SDL_PIXELFORMAT_BGR565, ಬಹುಲಕ_FLAG_TBGR | ಬಹುಲಕ_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_RGB565, ಬಹುಲಕ_FLAG_TRGB | ಬಹುಲಕ_FLAG_565, 65535, 4 },
    { SDL_PIXELFORMAT_BGR24, ಬಹುಲಕ_FLAG_TBGR, 16777215, 6 },
    { SDL_PIXELFORMAT_RGB24, ಬಹುಲಕ_FLAG_TRGB, 16777215, 6 },
    { SDL_PIXELFORMAT_XBGR8888, ಬಹುಲಕ_FLAG_TBGR, -1, 5 },
    { SDL_PIXELFORMAT_XRGB8888, ಬಹುಲಕ_FLAG_TRGB, -1, 5 },
    { SDL_PIXELFORMAT_ABGR8888, ಬಹುಲಕ_FLAG_ABGR, -1, 5 },
    { SDL_PIXELFORMAT_ARGB8888, ಬಹುಲಕ_FLAG_ARGB, -1, 5 }
};

ಸ್ಥಿರ SDL_PixelFormat RISCOS_ಬಹುಲಕ_ಗಮ್ಯ_Pixel_Format(ಪೂರ್ಣಾಂಕ ncolour, ಪೂರ್ಣಾಂಕ modeflags, ಪೂರ್ಣಾಂಕ log2bpp)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < SDL_arraysize(ಬಹುಲಕ_ಗಮ್ಯ_pixelformat); i++) {
        ಆದರೆ (log2bpp == ಬಹುಲಕ_ಗಮ್ಯ_pixelformat[i].log2bpp &&
            (ncolour == ಬಹುಲಕ_ಗಮ್ಯ_pixelformat[i].ncolour || ncolour == 0) &&
            (modeflags & (ಬಹುಲಕ_FLAG_565 | ಬಹುಲಕ_FLAG_ಬಣ್ಣ_SPACE)) == ಬಹುಲಕ_ಗಮ್ಯ_pixelformat[i].modeflags) {
            ಹಿಂತಿರುಗಿ ಬಹುಲಕ_ಗಮ್ಯ_pixelformat[i].pixel_format;
        }
    }

    ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_UNKNOWN;
}

ಸ್ಥಿರ size_t measure_ಬಹುಲಕ_ಖಂಡ(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಖಂಡ)
{
    size_t ಖಂಡ_ಗಾತ್ರ = ((ಖಂಡ[0] & 0xFF) == 3) ? 7 : 5;
    ಆಗ (ಖಂಡ[ಖಂಡ_ಗಾತ್ರ] != -1) {
        ಖಂಡ_ಗಾತ್ರ += 2;
    }
    ಖಂಡ_ಗಾತ್ರ++;

    ಹಿಂತಿರುಗಿ ಖಂಡ_ಗಾತ್ರ * 4;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ read_ಬಹುಲಕ_variable(ಪೂರ್ಣಾಂಕ *ಖಂಡ, ಪೂರ್ಣಾಂಕ var)
{
    _kernel_swi_regs regs;
    regs.r[0] = (ಪೂರ್ಣಾಂಕ)ಖಂಡ;
    regs.r[1] = var;
    _kernel_swi(OS_Read_ಬಹುಲಕ_Variable, &regs, &regs);
    ಹಿಂತಿರುಗಿ regs.r[2];
}

ಸ್ಥಿರ bool read_ಬಹುಲಕ_ಖಂಡ(ಪೂರ್ಣಾಂಕ *ಖಂಡ, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ, bool extended)
{
    ಪೂರ್ಣಾಂಕ xres, yres, ncolour, modeflags, log2bpp, ದರ;

    ಆದರೆ ((ಖಂಡ[0] & 0xFF) == 1) {
        xres = ಖಂಡ[1];
        yres = ಖಂಡ[2];
        log2bpp = ಖಂಡ[3];
        ದರ = ಖಂಡ[4];
        ncolour = (1 << (1 << log2bpp)) - 1;
        modeflags = ಬಹುಲಕ_FLAG_TBGR;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಖಂಡ[0] & 0xFF) == 3) {
        xres = ಖಂಡ[1];
        yres = ಖಂಡ[2];
        ncolour = ಖಂಡ[3];
        modeflags = ಖಂಡ[4];
        log2bpp = ಖಂಡ[5];
        ದರ = ಖಂಡ[6];
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (extended) {
        xres = read_ಬಹುಲಕ_variable(ಖಂಡ, 11) + 1;
        yres = read_ಬಹುಲಕ_variable(ಖಂಡ, 12) + 1;
        log2bpp = read_ಬಹುಲಕ_variable(ಖಂಡ, 9);
        ncolour = read_ಬಹುಲಕ_variable(ಖಂಡ, 3);
        modeflags = read_ಬಹುಲಕ_variable(ಖಂಡ, 0);
    }

    SDL_zerop(ಬಹುಲಕ);
    ಬಹುಲಕ->w = xres;
    ಬಹುಲಕ->h = yres;
    ಬಹುಲಕ->format = RISCOS_ಬಹುಲಕ_ಗಮ್ಯ_Pixel_Format(ncolour, modeflags, log2bpp);
    ಬಹುಲಕ->refresh_ದರ = (ದಶಮಾಂಶ)ದರ;

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ *convert_ಬಹುಲಕ_ಖಂಡ(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *ಖಂಡ)
{
    ಪೂರ್ಣಾಂಕ xres, yres, log2bpp, ದರ, ncolour = 0, modeflags = 0;
    size_t pos = 0;
    ಪೂರ್ಣಾಂಕ *dst;

    ಆದರೆ ((ಖಂಡ[0] & 0xFF) == 1) {
        xres = ಖಂಡ[1];
        yres = ಖಂಡ[2];
        log2bpp = ಖಂಡ[3];
        ದರ = ಖಂಡ[4];
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಖಂಡ[0] & 0xFF) == 3) {
        xres = ಖಂಡ[1];
        yres = ಖಂಡ[2];
        ncolour = ಖಂಡ[3];
        modeflags = ಖಂಡ[4];
        log2bpp = ಖಂಡ[5];
        ದರ = ಖಂಡ[6];
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    dst = SDL_malloc(40);
    ಆದರೆ (!dst) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    dst[pos++] = 1;
    dst[pos++] = xres;
    dst[pos++] = yres;
    dst[pos++] = log2bpp;
    dst[pos++] = ದರ;
    ಆದರೆ (ncolour != 0) {
        dst[pos++] = 3;
        dst[pos++] = ncolour;
    }
    ಆದರೆ (modeflags != 0) {
        dst[pos++] = 0;
        dst[pos++] = modeflags;
    }
    dst[pos++] = -1;

    ಹಿಂತಿರುಗಿ dst;
}

ಸ್ಥಿರ ಶೂನ್ಯ *copy_ಸ್ಮರಣೆ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src, size_t ಗಾತ್ರ_2, size_t alloc)
{
    ಶೂನ್ಯ *dst = SDL_malloc(alloc);
    ಆದರೆ (dst) {
        SDL_memcpy(dst, src, ಗಾತ್ರ_2);
    }
    ಹಿಂತಿರುಗಿ dst;
}

bool RISCOS_InitModes(SDL_VideoDevice *_this)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    ಪೂರ್ಣಾಂಕ *current_ಬಹುಲಕ;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    size_t ಗಾತ್ರ_2;

    regs.r[0] = 1;
    error = _kernel_swi(OS_Screen_ಬಹುಲಕ, &regs, &regs);
    ಆದರೆ (error) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to retrieve the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    current_ಬಹುಲಕ = (ಪೂರ್ಣಾಂಕ *)regs.r[1];
    ಆದರೆ (!read_ಬಹುಲಕ_ಖಂಡ(current_ಬಹುಲಕ, &ಬಹುಲಕ, true)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unsupported mode block format %d", current_ಬಹುಲಕ[0]);
    }

    ಗಾತ್ರ_2 = measure_ಬಹುಲಕ_ಖಂಡ(current_ಬಹುಲಕ);
    ಬಹುಲಕ.ಆಂತರಿಕ = copy_ಸ್ಮರಣೆ(current_ಬಹುಲಕ, ಗಾತ್ರ_2, ಗಾತ್ರ_2);
    ಆದರೆ (!ಬಹುಲಕ.ಆಂತರಿಕ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool RISCOS_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    ಶೂನ್ಯ *ಖಂಡ, *pos;

    regs.r[0] = 2;
    regs.r[2] = 0;
    regs.r[6] = 0;
    regs.r[7] = 0;
    error = _kernel_swi(OS_Screen_ಬಹುಲಕ, &regs, &regs);
    ಆದರೆ (error) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    ಖಂಡ = SDL_malloc(-regs.r[7]);
    ಆದರೆ (!ಖಂಡ) {
        ಹಿಂತಿರುಗಿ false;
    }

    regs.r[6] = (ಪೂರ್ಣಾಂಕ)ಖಂಡ;
    regs.r[7] = -regs.r[7];
    error = _kernel_swi(OS_Screen_ಬಹುಲಕ, &regs, &regs);
    ಆದರೆ (error) {
        SDL_free(ಖಂಡ);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to enumerate screen modes: %s (%i)", error->errmess, error->errnum);
    }

    ಗಾಗಿ (pos = ಖಂಡ; pos < (ಶೂನ್ಯ *)regs.r[6]; pos += *((ಪೂರ್ಣಾಂಕ *)pos)) {
        ಆದರೆ (!read_ಬಹುಲಕ_ಖಂಡ(pos + 4, &ಬಹುಲಕ, false)) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ (ಬಹುಲಕ.format == SDL_PIXELFORMAT_UNKNOWN) {
            ಮುಂದುವರಿ;
        }

        ಬಹುಲಕ.ಆಂತರಿಕ = convert_ಬಹುಲಕ_ಖಂಡ(pos + 4);
        ಆದರೆ (!ಬಹುಲಕ.ಆಂತರಿಕ) {
            SDL_free(ಖಂಡ);
            ಹಿಂತಿರುಗಿ false;
        }

        ಆದರೆ (!SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ)) {
            SDL_free(ಬಹುಲಕ.ಆಂತರಿಕ);
        }
    }

    SDL_free(ಖಂಡ);
    ಹಿಂತಿರುಗಿ true;
}

bool RISCOS_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ disable_cursor[] = { 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    _kernel_swi_regs regs;
    _kernel_oserror *error;
    ಪೂರ್ಣಾಂಕ i;

    regs.r[0] = 0;
    regs.r[1] = (ಪೂರ್ಣಾಂಕ)ಬಹುಲಕ->ಆಂತರಿಕ;
    error = _kernel_swi(OS_Screen_ಬಹುಲಕ, &regs, &regs);
    ಆದರೆ (error) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unable to set the current screen mode: %s (%i)", error->errmess, error->errnum);
    }

    // Turn the text cursor off
    ಗಾಗಿ (i = 0; i < SDL_arraysize(disable_cursor); i++) {
        _kernel_oswrch(disable_cursor[i]);
    }

    // Update cursor visibility, since it may have been disabled by the mode change.
    SDL_RedrawCursor();

    ಹಿಂತಿರುಗಿ true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RISCOS

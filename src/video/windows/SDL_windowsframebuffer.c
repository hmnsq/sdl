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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"

bool WIN_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    bool isstack;
    size_t ಗಾತ್ರ_2;
    LPBITMAPINFO info;
    HBITMAP hbm;
    ಪೂರ್ಣಾಂಕ w, h;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    // Free the old framebuffer surface
    ಆದರೆ (ದತ್ತಾಂಶ->mdc) {
        DeleteDC(ದತ್ತಾಂಶ->mdc);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->hbm) {
        DeleteObject(ದತ್ತಾಂಶ->hbm);
    }

    // Find out the format of the screen
    ಗಾತ್ರ_2 = ಗಾತ್ರ(BITMAPINFOHEADER) + 256 * ಗಾತ್ರ(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, ಗಾತ್ರ_2, &isstack);
    ಆದರೆ (!info) {
        ಹಿಂತಿರುಗಿ false;
    }

    SDL_memset(info, 0, ಗಾತ್ರ_2);
    info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಗಾತ್ರ = ಗಾತ್ರ(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(ದತ್ತಾಂಶ->hdc, 1, 1);
    GetDIBits(ದತ್ತಾಂಶ->hdc, hbm, 0, 0, ಖಾಲಿ, info, DIB_RGB_COLORS);
    GetDIBits(ದತ್ತಾಂಶ->hdc, hbm, 0, 0, ಖಾಲಿ, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    ಆದರೆ (info->bmi_ಶೀರ್ಷಿಕೆ.biCompression == BI_BITFIELDS) {
        ಪೂರ್ಣಾಂಕ bpp;
        Uint32 *masks;

        bpp = info->bmi_ಶೀರ್ಷಿಕೆ.biPlanes * info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಬಿಟ್_ಎಣಿಕೆ;
        masks = (Uint32 *)((Uint8 *)info + info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಗಾತ್ರ);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    ಆದರೆ (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, ಗಾತ್ರ_2);
        info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಗಾತ್ರ = ಗಾತ್ರ(BITMAPINFOHEADER);
        info->bmi_ಶೀರ್ಷಿಕೆ.biPlanes = 1;
        info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಬಿಟ್_ಎಣಿಕೆ = 32;
        info->bmi_ಶೀರ್ಷಿಕೆ.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        ಆದರೆ (need_alpha) {
            ಪೂರ್ಣಾಂಕ tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಗಾತ್ರ);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಅಗಲ = w;
    info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಎತ್ತರ = -h; // negative for topdown bitmap
    info->bmi_ಶೀರ್ಷಿಕೆ.bi_ಗಾತ್ರ_Image = (DWORD)h * (*pitch);

    ದತ್ತಾಂಶ->mdc = CreateCompatibleDC(ದತ್ತಾಂಶ->hdc);
    ದತ್ತಾಂಶ->hbm = CreateDIBSection(ದತ್ತಾಂಶ->hdc, info, DIB_RGB_COLORS, pixels, ಖಾಲಿ, 0);
    SDL_small_free(info, isstack);

    ಆದರೆ (!ದತ್ತಾಂಶ->hbm) {
        ಹಿಂತಿರುಗಿ WIN_ಗಣ_Error("Unable to create DIB");
    }
    SelectObject(ದತ್ತಾಂಶ->mdc, ದತ್ತಾಂಶ->hbm);

    ಹಿಂತಿರುಗಿ true;
}

bool WIN_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < numrects; ++i) {
        ಬಿಟ್_Blt(ದತ್ತಾಂಶ->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               ದತ್ತಾಂಶ->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        // The window wasn't fully initialized
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->mdc) {
        DeleteDC(ದತ್ತಾಂಶ->mdc);
        ದತ್ತಾಂಶ->mdc = ಖಾಲಿ;
    }
    ಆದರೆ (ದತ್ತಾಂಶ->hbm) {
        DeleteObject(ದತ್ತಾಂಶ->hbm);
        ದತ್ತಾಂಶ->hbm = ಖಾಲಿ;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS

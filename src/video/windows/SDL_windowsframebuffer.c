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

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsvideo.h"

bool WIN_Create_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    bool isstack;
    size_t سائيز;
    LPBITMAPINFO info;
    HBITMAP hbm;
    صحيح w, h;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    // Free the old framebuffer surface
    إذا (معلومات->mdc) {
        DeleteDC(معلومات->mdc);
    }
    إذا (معلومات->hbm) {
        DeleteObject(معلومات->hbm);
    }

    // Find out the format of the screen
    سائيز = حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, سائيز, &isstack);
    إذا (!info) {
        أرجع false;
    }

    SDL_memset(info, 0, سائيز);
    info->bmi_سرو.bi_سائيز = حجم(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(معلومات->hdc, 1, 1);
    GetDIBits(معلومات->hdc, hbm, 0, 0, عدم, info, DIB_RGB_COLORS);
    GetDIBits(معلومات->hdc, hbm, 0, 0, عدم, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (دري->flags & SDL_دري_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    إذا (info->bmi_سرو.biCompression == BI_BITFIELDS) {
        صحيح bpp;
        Uint32 *masks;

        bpp = info->bmi_سرو.biPlanes * info->bmi_سرو.bi_ٻٽو_انگ_ڳڻپ;
        masks = (Uint32 *)((Uint8 *)info + info->bmi_سرو.bi_سائيز);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    إذا (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, سائيز);
        info->bmi_سرو.bi_سائيز = حجم(BITMAPINFOHEADER);
        info->bmi_سرو.biPlanes = 1;
        info->bmi_سرو.bi_ٻٽو_انگ_ڳڻپ = 32;
        info->bmi_سرو.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        إذا (need_alpha) {
            صحيح tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmi_سرو.bi_سائيز);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmi_سرو.bi_ويڪر = w;
    info->bmi_سرو.bi_اوچائي = -h; // negative for topdown bitmap
    info->bmi_سرو.bi_سائيز_Image = (DWORD)h * (*pitch);

    معلومات->mdc = CreateCompatibleDC(معلومات->hdc);
    معلومات->hbm = CreateDIBSection(معلومات->hdc, info, DIB_RGB_COLORS, pixels, عدم, 0);
    SDL_small_free(info, isstack);

    إذا (!معلومات->hbm) {
        أرجع WIN_سيٽ_Error("Unable to create DIB");
    }
    SelectObject(معلومات->mdc, معلومات->hbm);

    أرجع true;
}

bool WIN_Update_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    صحيح i;

    لكل (i = 0; i < numrects; ++i) {
        ٻٽو_انگ_Blt(معلومات->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               معلومات->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    أرجع true;
}

فراغ WIN_Destroy_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (!معلومات) {
        // The window wasn't fully initialized
        أرجع;
    }

    إذا (معلومات->mdc) {
        DeleteDC(معلومات->mdc);
        معلومات->mdc = عدم;
    }
    إذا (معلومات->hbm) {
        DeleteObject(معلومات->hbm);
        معلومات->hbm = عدم;
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS

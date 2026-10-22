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

bool WIN_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    bool isstack;
    size_t ناپ;
    LPBITMAPINFO info;
    HBITMAP hbm;
    صحيح w, h;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);

    // Free the old framebuffer surface
    إذا (انکڑے->mdc) {
        DeleteDC(انکڑے->mdc);
    }
    إذا (انکڑے->hbm) {
        DeleteObject(انکڑے->hbm);
    }

    // Find out the format of the screen
    ناپ = حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, ناپ, &isstack);
    إذا (!info) {
        أرجع false;
    }

    SDL_memset(info, 0, ناپ);
    info->bmi_سرخی.bi_ناپ = حجم(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(انکڑے->hdc, 1, 1);
    GetDIBits(انکڑے->hdc, hbm, 0, 0, عدم, info, DIB_RGB_COLORS);
    GetDIBits(انکڑے->hdc, hbm, 0, 0, عدم, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    إذا (info->bmi_سرخی.biCompression == BI_BITFIELDS) {
        صحيح bpp;
        Uint32 *masks;

        bpp = info->bmi_سرخی.biPlanes * info->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی;
        masks = (Uint32 *)((Uint8 *)info + info->bmi_سرخی.bi_ناپ);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    إذا (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, ناپ);
        info->bmi_سرخی.bi_ناپ = حجم(BITMAPINFOHEADER);
        info->bmi_سرخی.biPlanes = 1;
        info->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی = 32;
        info->bmi_سرخی.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        إذا (need_alpha) {
            صحيح tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmi_سرخی.bi_ناپ);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmi_سرخی.bi_چوڑائی = w;
    info->bmi_سرخی.bi_اچائی = -h; // negative for topdown bitmap
    info->bmi_سرخی.bi_ناپ_Image = (DWORD)h * (*pitch);

    انکڑے->mdc = CreateCompatibleDC(انکڑے->hdc);
    انکڑے->hbm = CreateDIBSection(انکڑے->hdc, info, DIB_RGB_COLORS, pixels, عدم, 0);
    SDL_small_free(info, isstack);

    إذا (!انکڑے->hbm) {
        أرجع WIN_سیٹ_Error("Unable to create DIB");
    }
    SelectObject(انکڑے->mdc, انکڑے->hbm);

    أرجع true;
}

bool WIN_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    صحيح i;

    لكل (i = 0; i < numrects; ++i) {
        ثنائی_ہندسہ_Blt(انکڑے->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               انکڑے->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    أرجع true;
}

فراغ WIN_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;

    إذا (!انکڑے) {
        // The window wasn't fully initialized
        أرجع;
    }

    إذا (انکڑے->mdc) {
        DeleteDC(انکڑے->mdc);
        انکڑے->mdc = عدم;
    }
    إذا (انکڑے->hbm) {
        DeleteObject(انکڑے->hbm);
        انکڑے->hbm = عدم;
    }
}

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS

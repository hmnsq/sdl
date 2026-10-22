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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsvideo.h"

bool WIN_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, خالی **pixels, صحیح *pitch)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    bool isstack;
    size_t سائز;
    LPBITMAPINFO info;
    HBITMAP hbm;
    صحیح w, h;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);

    // Free the old framebuffer surface
    اگر (ڈیٹا->mdc) {
        DeleteDC(ڈیٹا->mdc);
    }
    اگر (ڈیٹا->hbm) {
        DeleteObject(ڈیٹا->hbm);
    }

    // Find out the format of the screen
    سائز = حجم(BITMAPINFOHEADER) + 256 * حجم(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, سائز, &isstack);
    اگر (!info) {
        واپس false;
    }

    SDL_memset(info, 0, سائز);
    info->bmi_سرخی.bi_سائز = حجم(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(ڈیٹا->hdc, 1, 1);
    GetDIBits(ڈیٹا->hdc, hbm, 0, 0, تہی, info, DIB_RGB_COLORS);
    GetDIBits(ڈیٹا->hdc, hbm, 0, 0, تہی, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    اگر (info->bmi_سرخی.biCompression == BI_BITFIELDS) {
        صحیح bpp;
        Uint32 *masks;

        bpp = info->bmi_سرخی.biPlanes * info->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی;
        masks = (Uint32 *)((Uint8 *)info + info->bmi_سرخی.bi_سائز);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    اگر (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, سائز);
        info->bmi_سرخی.bi_سائز = حجم(BITMAPINFOHEADER);
        info->bmi_سرخی.biPlanes = 1;
        info->bmi_سرخی.bi_ثنائی_ہندسہ_گنتی = 32;
        info->bmi_سرخی.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        اگر (need_alpha) {
            صحیح tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmi_سرخی.bi_سائز);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmi_سرخی.bi_چوڑائی = w;
    info->bmi_سرخی.bi_اونچائی = -h; // negative for topdown bitmap
    info->bmi_سرخی.bi_سائز_Image = (DWORD)h * (*pitch);

    ڈیٹا->mdc = CreateCompatibleDC(ڈیٹا->hdc);
    ڈیٹا->hbm = CreateDIBSection(ڈیٹا->hdc, info, DIB_RGB_COLORS, pixels, تہی, 0);
    SDL_small_free(info, isstack);

    اگر (!ڈیٹا->hbm) {
        واپس WIN_سیٹ_Error("Unable to create DIB");
    }
    SelectObject(ڈیٹا->mdc, ڈیٹا->hbm);

    واپس true;
}

bool WIN_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحیح numrects)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    صحیح i;

    برائے (i = 0; i < numrects; ++i) {
        ثنائی_ہندسہ_Blt(ڈیٹا->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               ڈیٹا->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    واپس true;
}

خالی WIN_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (!ڈیٹا) {
        // The window wasn't fully initialized
        واپس;
    }

    اگر (ڈیٹا->mdc) {
        DeleteDC(ڈیٹا->mdc);
        ڈیٹا->mdc = تہی;
    }
    اگر (ڈیٹا->hbm) {
        DeleteObject(ڈیٹا->hbm);
        ڈیٹا->hbm = تہی;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS

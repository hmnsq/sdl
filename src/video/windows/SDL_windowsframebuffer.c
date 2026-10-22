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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"

bool WIN_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    bool isstack;
    size_t ਮਾਪ;
    LPBITMAPINFO info;
    HBITMAP hbm;
    ਪੂਰਨ w, h;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    // Free the old framebuffer surface
    ਜੇ (ਅੰਕੜੇ->mdc) {
        DeleteDC(ਅੰਕੜੇ->mdc);
    }
    ਜੇ (ਅੰਕੜੇ->hbm) {
        DeleteObject(ਅੰਕੜੇ->hbm);
    }

    // Find out the format of the screen
    ਮਾਪ = ਆਕਾਰ(BITMAPINFOHEADER) + 256 * ਆਕਾਰ(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, ਮਾਪ, &isstack);
    ਜੇ (!info) {
        ਵਾਪਸ false;
    }

    SDL_memset(info, 0, ਮਾਪ);
    info->bmi_ਸਿਰਲੇਖ.bi_ਮਾਪ = ਆਕਾਰ(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(ਅੰਕੜੇ->hdc, 1, 1);
    GetDIBits(ਅੰਕੜੇ->hdc, hbm, 0, 0, ਨਿਰਾ, info, DIB_RGB_COLORS);
    GetDIBits(ਅੰਕੜੇ->hdc, hbm, 0, 0, ਨਿਰਾ, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    ਜੇ (info->bmi_ਸਿਰਲੇਖ.biCompression == BI_BITFIELDS) {
        ਪੂਰਨ bpp;
        Uint32 *masks;

        bpp = info->bmi_ਸਿਰਲੇਖ.biPlanes * info->bmi_ਸਿਰਲੇਖ.bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ;
        masks = (Uint32 *)((Uint8 *)info + info->bmi_ਸਿਰਲੇਖ.bi_ਮਾਪ);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    ਜੇ (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, ਮਾਪ);
        info->bmi_ਸਿਰਲੇਖ.bi_ਮਾਪ = ਆਕਾਰ(BITMAPINFOHEADER);
        info->bmi_ਸਿਰਲੇਖ.biPlanes = 1;
        info->bmi_ਸਿਰਲੇਖ.bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ = 32;
        info->bmi_ਸਿਰਲੇਖ.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        ਜੇ (need_alpha) {
            ਪੂਰਨ tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmi_ਸਿਰਲੇਖ.bi_ਮਾਪ);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmi_ਸਿਰਲੇਖ.bi_ਚੌੜਾਈ = w;
    info->bmi_ਸਿਰਲੇਖ.bi_ਉਚਾਈ = -h; // negative for topdown bitmap
    info->bmi_ਸਿਰਲੇਖ.bi_ਮਾਪ_Image = (DWORD)h * (*pitch);

    ਅੰਕੜੇ->mdc = CreateCompatibleDC(ਅੰਕੜੇ->hdc);
    ਅੰਕੜੇ->hbm = CreateDIBSection(ਅੰਕੜੇ->hdc, info, DIB_RGB_COLORS, pixels, ਨਿਰਾ, 0);
    SDL_small_free(info, isstack);

    ਜੇ (!ਅੰਕੜੇ->hbm) {
        ਵਾਪਸ WIN_ਸੈੱਟ_Error("Unable to create DIB");
    }
    SelectObject(ਅੰਕੜੇ->mdc, ਅੰਕੜੇ->hbm);

    ਵਾਪਸ true;
}

bool WIN_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < numrects; ++i) {
        ਦੋਆਧਾਰੀ_ਅੰਕ_Blt(ਅੰਕੜੇ->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               ਅੰਕੜੇ->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ WIN_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (!ਅੰਕੜੇ) {
        // The window wasn't fully initialized
        ਵਾਪਸ;
    }

    ਜੇ (ਅੰਕੜੇ->mdc) {
        DeleteDC(ਅੰਕੜੇ->mdc);
        ਅੰਕੜੇ->mdc = ਨਿਰਾ;
    }
    ਜੇ (ਅੰਕੜੇ->hbm) {
        DeleteObject(ਅੰਕੜੇ->hbm);
        ਅੰਕੜੇ->hbm = ਨਿਰਾ;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS

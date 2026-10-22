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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#அந்தர்பாவ "SDL_windowsvideo.h"

bool WIN_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, வெறுமை **pixels, முழு *pitch)
{
    SDL_WindowData *data = window->internal;
    bool isstack;
    size_t size;
    LPBITMAPINFO info;
    HBITMAP hbm;
    முழு w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    எனில் (data->mdc) {
        DeleteDC(data->mdc);
    }
    எனில் (data->hbm) {
        DeleteObject(data->hbm);
    }

    // Find out the format of the screen
    size = அளவு(BITMAPINFOHEADER) + 256 * அளவு(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, size, &isstack);
    எனில் (!info) {
        திரும்பு false;
    }

    SDL_memset(info, 0, size);
    info->bmiHeader.biSize = அளவு(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(data->hdc, 1, 1);
    GetDIBits(data->hdc, hbm, 0, 0, வெற்று, info, DIB_RGB_COLORS);
    GetDIBits(data->hdc, hbm, 0, 0, வெற்று, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (window->flags & SDL_WINDOW_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    எனில் (info->bmiHeader.biCompression == BI_BITFIELDS) {
        முழு bpp;
        Uint32 *masks;

        bpp = info->bmiHeader.biPlanes * info->bmiHeader.bi_Bit_மொத்தம்;
        masks = (Uint32 *)((Uint8 *)info + info->bmiHeader.biSize);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    எனில் (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, size);
        info->bmiHeader.biSize = அளவு(BITMAPINFOHEADER);
        info->bmiHeader.biPlanes = 1;
        info->bmiHeader.bi_Bit_மொத்தம் = 32;
        info->bmiHeader.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        எனில் (need_alpha) {
            முழு tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmiHeader.biSize);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmiHeader.biWidth = w;
    info->bmiHeader.biHeight = -h; // negative for topdown bitmap
    info->bmiHeader.biSizeImage = (DWORD)h * (*pitch);

    data->mdc = CreateCompatibleDC(data->hdc);
    data->hbm = CreateDIBSection(data->hdc, info, DIB_RGB_COLORS, pixels, வெற்று, 0);
    SDL_small_free(info, isstack);

    எனில் (!data->hbm) {
        திரும்பு WIN_SetError("Unable to create DIB");
    }
    SelectObject(data->mdc, data->hbm);

    திரும்பு true;
}

bool WIN_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rects, முழு numrects)
{
    SDL_WindowData *data = window->internal;
    முழு i;

    க்கு (i = 0; i < numrects; ++i) {
        BitBlt(data->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               data->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    திரும்பு true;
}

வெறுமை WIN_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    எனில் (!data) {
        // The window wasn't fully initialized
        திரும்பு;
    }

    எனில் (data->mdc) {
        DeleteDC(data->mdc);
        data->mdc = வெற்று;
    }
    எனில் (data->hbm) {
        DeleteObject(data->hbm);
        data->hbm = வெற்று;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

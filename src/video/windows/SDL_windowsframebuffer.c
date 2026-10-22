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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#અન્તર્ભાવ "SDL_windowsvideo.h"

bool WIN_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_WindowData *data = window->internal;
    bool isstack;
    size_t size;
    LPBITMAPINFO info;
    HBITMAP hbm;
    પૂર્ણાંક w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    જો (data->mdc) {
        DeleteDC(data->mdc);
    }
    જો (data->hbm) {
        DeleteObject(data->hbm);
    }

    // Find out the format of the screen
    size = કદ(BITMAPINFOHEADER) + 256 * કદ(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, size, &isstack);
    જો (!info) {
        પાછા false;
    }

    SDL_memset(info, 0, size);
    info->bmiHeader.biSize = કદ(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(data->hdc, 1, 1);
    GetDIBits(data->hdc, hbm, 0, 0, ખાલી, info, DIB_RGB_COLORS);
    GetDIBits(data->hdc, hbm, 0, 0, ખાલી, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (window->flags & SDL_WINDOW_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    જો (info->bmiHeader.biCompression == BI_BITFIELDS) {
        પૂર્ણાંક bpp;
        Uint32 *masks;

        bpp = info->bmiHeader.biPlanes * info->bmiHeader.bi_Bit_ગણતરી;
        masks = (Uint32 *)((Uint8 *)info + info->bmiHeader.biSize);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    જો (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, size);
        info->bmiHeader.biSize = કદ(BITMAPINFOHEADER);
        info->bmiHeader.biPlanes = 1;
        info->bmiHeader.bi_Bit_ગણતરી = 32;
        info->bmiHeader.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        જો (need_alpha) {
            પૂર્ણાંક tmpbpp;
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
    data->hbm = CreateDIBSection(data->hdc, info, DIB_RGB_COLORS, pixels, ખાલી, 0);
    SDL_small_free(info, isstack);

    જો (!data->hbm) {
        પાછા WIN_SetError("Unable to create DIB");
    }
    SelectObject(data->mdc, data->hbm);

    પાછા true;
}

bool WIN_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects, પૂર્ણાંક numrects)
{
    SDL_WindowData *data = window->internal;
    પૂર્ણાંક i;

    માટે (i = 0; i < numrects; ++i) {
        BitBlt(data->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               data->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    પાછા true;
}

શૂન્ય WIN_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;

    જો (!data) {
        // The window wasn't fully initialized
        પાછા;
    }

    જો (data->mdc) {
        DeleteDC(data->mdc);
        data->mdc = ખાલી;
    }
    જો (data->hbm) {
        DeleteObject(data->hbm);
        data->hbm = ખાલી;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

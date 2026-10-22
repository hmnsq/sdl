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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#অন্তর্ভাব "SDL_windowsvideo.h"

bool WIN_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণসংখ্যা *pitch)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    bool isstack;
    size_t আকার_2;
    LPBITMAPINFO info;
    HBITMAP hbm;
    পূর্ণসংখ্যা w, h;

    SDL_Get_Window_আকার_In_Pixels(window, &w, &h);

    // Free the old framebuffer surface
    যদি (তথ্য->mdc) {
        DeleteDC(তথ্য->mdc);
    }
    যদি (তথ্য->hbm) {
        DeleteObject(তথ্য->hbm);
    }

    // Find out the format of the screen
    আকার_2 = আকার(BITMAPINFOHEADER) + 256 * আকার(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, আকার_2, &isstack);
    যদি (!info) {
        ফেরত false;
    }

    SDL_memset(info, 0, আকার_2);
    info->bmiHeader.bi_আকার = আকার(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(তথ্য->hdc, 1, 1);
    GetDIBits(তথ্য->hdc, hbm, 0, 0, ফাঁকা, info, DIB_RGB_COLORS);
    GetDIBits(তথ্য->hdc, hbm, 0, 0, ফাঁকা, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (window->flags & SDL_WINDOW_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    যদি (info->bmiHeader.biCompression == BI_BITFIELDS) {
        পূর্ণসংখ্যা bpp;
        Uint32 *masks;

        bpp = info->bmiHeader.biPlanes * info->bmiHeader.bi_Bit_গুনতি;
        masks = (Uint32 *)((Uint8 *)info + info->bmiHeader.bi_আকার);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    যদি (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, আকার_2);
        info->bmiHeader.bi_আকার = আকার(BITMAPINFOHEADER);
        info->bmiHeader.biPlanes = 1;
        info->bmiHeader.bi_Bit_গুনতি = 32;
        info->bmiHeader.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        যদি (need_alpha) {
            পূর্ণসংখ্যা tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmiHeader.bi_আকার);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmiHeader.biWidth = w;
    info->bmiHeader.biHeight = -h; // negative for topdown bitmap
    info->bmiHeader.bi_আকার_Image = (DWORD)h * (*pitch);

    তথ্য->mdc = CreateCompatibleDC(তথ্য->hdc);
    তথ্য->hbm = CreateDIBSection(তথ্য->hdc, info, DIB_RGB_COLORS, pixels, ফাঁকা, 0);
    SDL_small_free(info, isstack);

    যদি (!তথ্য->hbm) {
        ফেরত WIN_SetError("Unable to create DIB");
    }
    SelectObject(তথ্য->mdc, তথ্য->hbm);

    ফেরত true;
}

bool WIN_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects, পূর্ণসংখ্যা numrects)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < numrects; ++i) {
        BitBlt(তথ্য->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               তথ্য->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    ফেরত true;
}

শূন্য WIN_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (!তথ্য) {
        // The window wasn't fully initialized
        ফেরত;
    }

    যদি (তথ্য->mdc) {
        DeleteDC(তথ্য->mdc);
        তথ্য->mdc = ফাঁকা;
    }
    যদি (তথ্য->hbm) {
        DeleteObject(তথ্য->hbm);
        তথ্য->hbm = ফাঁকা;
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

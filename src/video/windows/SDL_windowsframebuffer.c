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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#समावेश "SDL_windowsvideo.h"

bool WIN_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    bool isstack;
    माप_प्रकार आकार;
    LPBITMAPINFO info;
    HBITMAP hbm;
    पूर्णांक w, h;

    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);

    // Free the old framebuffer surface
    अगर (तथ्य->mdc) {
        DeleteDC(तथ्य->mdc);
    }
    अगर (तथ्य->hbm) {
        DeleteObject(तथ्य->hbm);
    }

    // Find out the format of the screen
    आकार = माप(BITMAPINFOHEADER) + 256 * माप(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, आकार, &isstack);
    अगर (!info) {
        वापस false;
    }

    SDL_memset(info, 0, आकार);
    info->bmiHeader.bi_आकार = माप(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(तथ्य->hdc, 1, 1);
    GetDIBits(तथ्य->hdc, hbm, 0, 0, शून्य, info, DIB_RGB_COLORS);
    GetDIBits(तथ्य->hdc, hbm, 0, 0, शून्य, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (window->flags & SDL_WINDOW_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    अगर (info->bmiHeader.biCompression == BI_BITFIELDS) {
        पूर्णांक bpp;
        Uint32 *masks;

        bpp = info->bmiHeader.biPlanes * info->bmiHeader.bi_Bit_गिनती;
        masks = (Uint32 *)((Uint8 *)info + info->bmiHeader.bi_आकार);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    अगर (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, आकार);
        info->bmiHeader.bi_आकार = माप(BITMAPINFOHEADER);
        info->bmiHeader.biPlanes = 1;
        info->bmiHeader.bi_Bit_गिनती = 32;
        info->bmiHeader.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        अगर (need_alpha) {
            पूर्णांक tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmiHeader.bi_आकार);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmiHeader.biWidth = w;
    info->bmiHeader.biHeight = -h; // negative for topdown bitmap
    info->bmiHeader.bi_आकार_Image = (DWORD)h * (*pitch);

    तथ्य->mdc = CreateCompatibleDC(तथ्य->hdc);
    तथ्य->hbm = CreateDIBSection(तथ्य->hdc, info, DIB_RGB_COLORS, pixels, शून्य, 0);
    SDL_small_free(info, isstack);

    अगर (!तथ्य->hbm) {
        वापस WIN_SetError("Unable to create DIB");
    }
    SelectObject(तथ्य->mdc, तथ्य->hbm);

    वापस true;
}

bool WIN_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    पूर्णांक i;

    क्रम (i = 0; i < numrects; ++i) {
        BitBlt(तथ्य->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               तथ्य->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    वापस true;
}

व्योम WIN_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (!तथ्य) {
        // The window wasn't fully initialized
        वापस;
    }

    अगर (तथ्य->mdc) {
        DeleteDC(तथ्य->mdc);
        तथ्य->mdc = शून्य;
    }
    अगर (तथ्य->hbm) {
        DeleteObject(तथ्य->hbm);
        तथ्य->hbm = शून्य;
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS

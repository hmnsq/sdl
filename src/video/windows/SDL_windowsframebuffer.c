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
#अन्तर्भाव "SDL_internal.h"

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsvideo.h"

bool WIN_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    bool isstack;
    size_t आकार;
    LPBITMAPINFO info;
    HBITMAP hbm;
    पूर्णाङ्क w, h;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);

    // Free the old framebuffer surface
    यदि (दत्त->mdc) {
        DeleteDC(दत्त->mdc);
    }
    यदि (दत्त->hbm) {
        DeleteObject(दत्त->hbm);
    }

    // Find out the format of the screen
    आकार = परिमाण(BITMAPINFOHEADER) + 256 * परिमाण(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, आकार, &isstack);
    यदि (!info) {
        प्रत्यागम false;
    }

    SDL_memset(info, 0, आकार);
    info->bmi_शीर्षकम्.bi_आकार = परिमाण(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(दत्त->hdc, 1, 1);
    GetDIBits(दत्त->hdc, hbm, 0, 0, रिक्त, info, DIB_RGB_COLORS);
    GetDIBits(दत्त->hdc, hbm, 0, 0, रिक्त, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    यदि (info->bmi_शीर्षकम्.biCompression == BI_BITFIELDS) {
        पूर्णाङ्क bpp;
        Uint32 *masks;

        bpp = info->bmi_शीर्षकम्.biPlanes * info->bmi_शीर्षकम्.bi_Bit_गणनम्;
        masks = (Uint32 *)((Uint8 *)info + info->bmi_शीर्षकम्.bi_आकार);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    यदि (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, आकार);
        info->bmi_शीर्षकम्.bi_आकार = परिमाण(BITMAPINFOHEADER);
        info->bmi_शीर्षकम्.biPlanes = 1;
        info->bmi_शीर्षकम्.bi_Bit_गणनम् = 32;
        info->bmi_शीर्षकम्.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        यदि (need_alpha) {
            पूर्णाङ्क tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmi_शीर्षकम्.bi_आकार);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmi_शीर्षकम्.bi_विस्तारः = w;
    info->bmi_शीर्षकम्.biHeight = -h; // negative for topdown bitmap
    info->bmi_शीर्षकम्.bi_आकार_Image = (DWORD)h * (*pitch);

    दत्त->mdc = CreateCompatibleDC(दत्त->hdc);
    दत्त->hbm = CreateDIBSection(दत्त->hdc, info, DIB_RGB_COLORS, pixels, रिक्त, 0);
    SDL_small_free(info, isstack);

    यदि (!दत्त->hbm) {
        प्रत्यागम WIN_समुच्चयः_Error("Unable to create DIB");
    }
    SelectObject(दत्त->mdc, दत्त->hbm);

    प्रत्यागम true;
}

bool WIN_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    पूर्णाङ्क i;

    प्रति (i = 0; i < numrects; ++i) {
        BitBlt(दत्त->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               दत्त->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    प्रत्यागम true;
}

शून्य WIN_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (!दत्त) {
        // The window wasn't fully initialized
        प्रत्यागम;
    }

    यदि (दत्त->mdc) {
        DeleteDC(दत्त->mdc);
        दत्त->mdc = रिक्त;
    }
    यदि (दत्त->hbm) {
        DeleteObject(दत्त->hbm);
        दत्त->hbm = रिक्त;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS

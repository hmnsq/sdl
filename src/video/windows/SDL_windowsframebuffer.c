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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#అన్తర్భావ "SDL_windowsvideo.h"

bool WIN_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format, శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    bool isstack;
    size_t కొలత;
    LPBITMAPINFO info;
    HBITMAP hbm;
    పూర్ణాంకం w, h;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);

    // Free the old framebuffer surface
    ఒకవేళ (దత్తాంశం->mdc) {
        DeleteDC(దత్తాంశం->mdc);
    }
    ఒకవేళ (దత్తాంశం->hbm) {
        DeleteObject(దత్తాంశం->hbm);
    }

    // Find out the format of the screen
    కొలత = పరిమాణం(BITMAPINFOHEADER) + 256 * పరిమాణం(RGBQUAD);
    info = (LPBITMAPINFO)SDL_small_alloc(Uint8, కొలత, &isstack);
    ఒకవేళ (!info) {
        తిరిగి false;
    }

    SDL_memset(info, 0, కొలత);
    info->bmi_శీర్షిక.bi_కొలత = పరిమాణం(BITMAPINFOHEADER);

    // The second call to GetDIBits() fills in the bitfields
    hbm = CreateCompatibleBitmap(దత్తాంశం->hdc, 1, 1);
    GetDIBits(దత్తాంశం->hdc, hbm, 0, 0, ఖాళీ, info, DIB_RGB_COLORS);
    GetDIBits(దత్తాంశం->hdc, hbm, 0, 0, ఖాళీ, info, DIB_RGB_COLORS);
    DeleteObject(hbm);

    // Check if a transparent channel is required
    bool need_alpha = (కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) != 0;

    *format = SDL_PIXELFORMAT_UNKNOWN;
    ఒకవేళ (info->bmi_శీర్షిక.biCompression == BI_BITFIELDS) {
        పూర్ణాంకం bpp;
        Uint32 *masks;

        bpp = info->bmi_శీర్షిక.biPlanes * info->bmi_శీర్షిక.bi_బిట్టు_లెక్క;
        masks = (Uint32 *)((Uint8 *)info + info->bmi_శీర్షిక.bi_కొలత);
        *format = SDL_GetPixelFormatForMasks(bpp, masks[0], masks[1], masks[2], 0);
    }
    ఒకవేళ (*format == SDL_PIXELFORMAT_UNKNOWN || need_alpha) {
        // We'll use RGB or BGRA32 format for now
        *format = need_alpha ? SDL_PIXELFORMAT_BGRA32 : SDL_PIXELFORMAT_XRGB8888;

        // Create a new one
        SDL_memset(info, 0, కొలత);
        info->bmi_శీర్షిక.bi_కొలత = పరిమాణం(BITMAPINFOHEADER);
        info->bmi_శీర్షిక.biPlanes = 1;
        info->bmi_శీర్షిక.bi_బిట్టు_లెక్క = 32;
        info->bmi_శీర్షిక.biCompression = need_alpha ? BI_BITFIELDS : BI_RGB;

        ఒకవేళ (need_alpha) {
            పూర్ణాంకం tmpbpp;
            Uint32 *bgr32masks = (Uint32 *)((Uint8 *)info + info->bmi_శీర్షిక.bi_కొలత);
            SDL_GetMasksForPixelFormat(SDL_PIXELFORMAT_BGRA32, &tmpbpp, &bgr32masks[0], &bgr32masks[1], &bgr32masks[2], &bgr32masks[3]);
        }
    }

    // Fill in the size information
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);
    info->bmi_శీర్షిక.bi_వెడల్పు = w;
    info->bmi_శీర్షిక.bi_ఎత్తు = -h; // negative for topdown bitmap
    info->bmi_శీర్షిక.bi_కొలత_Image = (DWORD)h * (*pitch);

    దత్తాంశం->mdc = CreateCompatibleDC(దత్తాంశం->hdc);
    దత్తాంశం->hbm = CreateDIBSection(దత్తాంశం->hdc, info, DIB_RGB_COLORS, pixels, ఖాళీ, 0);
    SDL_small_free(info, isstack);

    ఒకవేళ (!దత్తాంశం->hbm) {
        తిరిగి WIN_సమితి_Error("Unable to create DIB");
    }
    SelectObject(దత్తాంశం->mdc, దత్తాంశం->hbm);

    తిరిగి true;
}

bool WIN_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects, పూర్ణాంకం numrects)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < numrects; ++i) {
        బిట్టు_Blt(దత్తాంశం->hdc, rects[i].x, rects[i].y, rects[i].w, rects[i].h,
               దత్తాంశం->mdc, rects[i].x, rects[i].y, SRCCOPY);
    }
    తిరిగి true;
}

శూన్య WIN_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (!దత్తాంశం) {
        // The window wasn't fully initialized
        తిరిగి;
    }

    ఒకవేళ (దత్తాంశం->mdc) {
        DeleteDC(దత్తాంశం->mdc);
        దత్తాంశం->mdc = ఖాళీ;
    }
    ఒకవేళ (దత్తాంశం->hbm) {
        DeleteObject(దత్తాంశం->hbm);
        దత్తాంశం->hbm = ఖాళీ;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS

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

#ifdef SDL_VIDEO_DRIVER_HAIKU

#شامل "SDL_bframebuffer.h"

#شامل <AppKit.h>
#شامل <InterfaceKit.h>
#شامل "SDL_bmodes.h"
#شامل "SDL_BWin.h"

#شامل "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
بیرونی "C" {
#endif

ایستا SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    بازگشت (SDL_BWin *)(window->internal);
}

ایستا SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    بازگشت SDL_Looper;
}

منطقی HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, تهی ** pixels, صحیح *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    اگر (!bscreen.IsValid()) {
        بازگشت نادرست;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->LockBuffer();

    bwin->CreateView();

    // format
    display_mode bmode;
    bscreen.GetMode(&bmode);
    *format = HAIKU_ColorSpaceToSDLPxFormat(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    اگر (bitmap) {
        delete bitmap;
    }
    bitmap = جدید BBitmap(bwin->Bounds(), (color_space)bmode.space,
            نادرست,    // Views not accepted
            درست);    // Contiguous memory required

    اگر (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        بازگشت SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    بازگشت درست;
}



منطقی HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      ثابت SDL_Rect * rects, صحیح numrects) {
    اگر (!window) {
        بازگشت درست;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    بازگشت درست;
}

تهی HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(پوچ);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

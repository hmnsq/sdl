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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#ಅನ್ತರ್ಭಾವ "SDL_bframebuffer.h"

#ಅನ್ತರ್ಭಾವ <AppKit.h>
#ಅನ್ತರ್ಭಾವ <InterfaceKit.h>
#ಅನ್ತರ್ಭಾವ "SDL_bmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"

#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

ಸ್ಥಿರ SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ (SDL_BWin *)(window->internal);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಪ್ರತ್ಯಾಗಮ SDL_Looper;
}

ತಾರ್ಕಿಕ HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, ಶೂನ್ಯ ** pixels, ಪೂರ್ಣಾಙ್ಕ *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    ಯದಿ (!bscreen.IsValid()) {
        ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
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

    ಯದಿ (bitmap) {
        delete bitmap;
    }
    bitmap = ನೂತನ BBitmap(bwin->Bounds(), (color_space)bmode.space,
            ಅಸತ್ಯ,    // Views not accepted
            ಸತ್ಯ);    // Contiguous memory required

    ಯದಿ (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}



ತಾರ್ಕಿಕ HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      ಧ್ರುವ SDL_Rect * rects, ಪೂರ್ಣಾಙ್ಕ numrects) {
    ಯದಿ (!window) {
        ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(ರಿಕ್ತ);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

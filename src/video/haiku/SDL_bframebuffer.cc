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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#ଅନ୍ତର୍ଭାଵ "SDL_bframebuffer.h"

#ଅନ୍ତର୍ଭାଵ <AppKit.h>
#ଅନ୍ତର୍ଭାଵ <InterfaceKit.h>
#ଅନ୍ତର୍ଭାଵ "SDL_bmodes.h"
#ଅନ୍ତର୍ଭାଵ "SDL_BWin.h"

#ଅନ୍ତର୍ଭାଵ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

ସ୍ଥିର SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ଫେରନ୍ତୁ (SDL_BWin *)(window->internal);
}

ସ୍ଥିର SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ଫେରନ୍ତୁ SDL_Looper;
}

ତାର୍କିକ HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, ଶୂନ୍ୟ ** pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    ଯଦି (!bscreen.IsValid()) {
        ଫେରନ୍ତୁ ମିଥ୍ୟା;
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

    ଯଦି (bitmap) {
        delete bitmap;
    }
    bitmap = ନୂତନ BBitmap(bwin->Bounds(), (color_space)bmode.space,
            ମିଥ୍ୟା,    // Views not accepted
            ସତ୍ୟ);    // Contiguous memory required

    ଯଦି (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        ଫେରନ୍ତୁ SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    ଫେରନ୍ତୁ ସତ୍ୟ;
}



ତାର୍କିକ HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      ଅଚଳ SDL_Rect * rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects) {
    ଯଦି (!window) {
        ଫେରନ୍ତୁ ସତ୍ୟ;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଶୂନ୍ୟ HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(ଖାଲି);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

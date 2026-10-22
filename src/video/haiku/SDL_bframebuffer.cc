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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_bframebuffer.h"

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#ضمن "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
خارجي "C" {
#endif

ساكن SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ܦܢܐ (SDL_BWin *)(window->internal);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ܦܢܐ SDL_Looper;
}

منطقي HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, فراغ ** pixels, صحيح *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    ܐܢ (!bscreen.IsValid()) {
        ܦܢܐ ܕܓܠܐ;
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

    ܐܢ (bitmap) {
        delete bitmap;
    }
    bitmap = جديد BBitmap(bwin->Bounds(), (color_space)bmode.space,
            ܕܓܠܐ,    // Views not accepted
            ܫܪܪܐ);    // Contiguous memory required

    ܐܢ (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        ܦܢܐ SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    ܦܢܐ ܫܪܪܐ;
}



منطقي HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      ثابت SDL_Rect * rects, صحيح numrects) {
    ܐܢ (!window) {
        ܦܢܐ ܫܪܪܐ;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    ܦܢܐ ܫܪܪܐ;
}

فراغ HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(عدم);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

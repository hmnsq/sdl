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

#ifdef SDL_VIDEO_DRIVER_HAIKU

#અન્તર્ભાવ "SDL_bframebuffer.h"

#અન્તર્ભાવ <AppKit.h>
#અન્તર્ભાવ <InterfaceKit.h>
#અન્તર્ભાવ "SDL_bmodes.h"
#અન્તર્ભાવ "SDL_BWin.h"

#અન્તર્ભાવ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
બાહ્ય "C" {
#endif

સ્થિર SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    પાછા (SDL_BWin *)(window->internal);
}

સ્થિર SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    પાછા SDL_Looper;
}

તાર્કિક HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, શૂન્ય ** pixels, પૂર્ણાંક *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    જો (!bscreen.IsValid()) {
        પાછા ખોટું;
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

    જો (bitmap) {
        delete bitmap;
    }
    bitmap = નવું BBitmap(bwin->Bounds(), (color_space)bmode.space,
            ખોટું,    // Views not accepted
            સાચું);    // Contiguous memory required

    જો (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        પાછા SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    પાછા સાચું;
}



તાર્કિક HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      અચલ SDL_Rect * rects, પૂર્ણાંક numrects) {
    જો (!window) {
        પાછા સાચું;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    પાછા સાચું;
}

શૂન્ય HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(ખાલી);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

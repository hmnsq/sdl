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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#അന്തര്ഭാവ "SDL_bframebuffer.h"

#അന്തര്ഭാവ <AppKit.h>
#അന്തര്ഭാവ <InterfaceKit.h>
#അന്തര്ഭാവ "SDL_bmodes.h"
#അന്തര്ഭാവ "SDL_BWin.h"

#അന്തര്ഭാവ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

സ്ഥിതം SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    തിരികെ (SDL_BWin *)(window->internal);
}

സ്ഥിതം SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    തിരികെ SDL_Looper;
}

തർക്കം HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, ശൂന്യം ** pixels, പൂർണ്ണസംഖ്യ *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    എങ്കിൽ (!bscreen.IsValid()) {
        തിരികെ അസത്യം;
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

    എങ്കിൽ (bitmap) {
        delete bitmap;
    }
    bitmap = പുതിയ BBitmap(bwin->Bounds(), (color_space)bmode.space,
            അസത്യം,    // Views not accepted
            സത്യം);    // Contiguous memory required

    എങ്കിൽ (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        തിരികെ SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    തിരികെ സത്യം;
}



തർക്കം HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      സ്ഥിരം SDL_Rect * rects, പൂർണ്ണസംഖ്യ numrects) {
    എങ്കിൽ (!window) {
        തിരികെ സത്യം;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    തിരികെ സത്യം;
}

ശൂന്യം HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(ശൂന്യ);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

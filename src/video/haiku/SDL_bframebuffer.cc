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

#अगर_घोषित SDL_VIDEO_DRIVER_HAIKU

#समावेश "SDL_bframebuffer.h"

#समावेश <AppKit.h>
#समावेश <InterfaceKit.h>
#समावेश "SDL_bmodes.h"
#समावेश "SDL_BWin.h"

#समावेश "../../core/haiku/SDL_BApp.h"

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

अटल SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    वापस (SDL_BWin *)(window->internal);
}

अटल SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    वापस SDL_Looper;
}

bool HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, व्योम ** pixels, पूर्णांक *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    अगर (!bscreen.IsValid()) {
        वापस false;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->Lock_बफर();

    bwin->CreateView();

    // format
    display_mode bmode;
    bscreen.GetMode(&bmode);
    *format = HAIKU_ColorSpaceToSDLPxFormat(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    अगर (bitmap) {
        मिटाओ bitmap;
    }
    bitmap = नया BBitmap(bwin->Bounds(), (color_space)bmode.space,
            false,    // Views not accepted
            true);    // Contiguous memory required

    अगर (bitmap->InitCheck() != B_OK) {
        मिटाओ bitmap;
        वापस SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->Unlock_बफर();
    वापस true;
}



bool HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      स्थिर SDL_Rect * rects, पूर्णांक numrects) {
    अगर (!window) {
        वापस true;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    वापस true;
}

व्योम HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->Lock_बफर();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    मिटाओ bitmap;
    bwin->SetBitmap(शून्य);

    bwin->RemoveView();

    bwin->Unlock_बफर();
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU

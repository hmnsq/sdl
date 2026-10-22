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

#ifdef SDL_VIDEO_DRIVER_HAIKU

#अन्तर्भाव "SDL_bframebuffer.h"

#अन्तर्भाव <AppKit.h>
#अन्तर्भाव <InterfaceKit.h>
#अन्तर्भाव "SDL_bmodes.h"
#अन्तर्भाव "SDL_BWin.h"

#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
बाह्य "C" {
#endif

स्थिर SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    फर्काऊ (SDL_BWin *)(window->internal);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    फर्काऊ SDL_Looper;
}

तार्किक HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, शून्य ** pixels, पूर्णाङ्क *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    यदि (!bscreen.IsValid()) {
        फर्काऊ असत्य;
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

    यदि (bitmap) {
        delete bitmap;
    }
    bitmap = नूतन BBitmap(bwin->Bounds(), (color_space)bmode.space,
            असत्य,    // Views not accepted
            सत्य);    // Contiguous memory required

    यदि (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        फर्काऊ SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    फर्काऊ सत्य;
}



तार्किक HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      अचर SDL_Rect * rects, पूर्णाङ्क numrects) {
    यदि (!window) {
        फर्काऊ सत्य;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    फर्काऊ सत्य;
}

शून्य HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(रिक्त);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#অন্তর্ভাব "SDL_bframebuffer.h"

#অন্তর্ভাব <AppKit.h>
#অন্তর্ভাব <InterfaceKit.h>
#অন্তর্ভাব "SDL_bmodes.h"
#অন্তর্ভাব "SDL_BWin.h"

#অন্তর্ভাব "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
বাহ্য "C" {
#endif

স্থির SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    প্রত্যাগম (SDL_BWin *)(window->internal);
}

স্থির SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    প্রত্যাগম SDL_Looper;
}

তার্কিক HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, শূন্য ** pixels, পূর্ণাঙ্ক *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    যদি (!bscreen.IsValid()) {
        প্রত্যাগম অসত্য;
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

    যদি (bitmap) {
        delete bitmap;
    }
    bitmap = নূতন BBitmap(bwin->Bounds(), (color_space)bmode.space,
            অসত্য,    // Views not accepted
            সত্য);    // Contiguous memory required

    যদি (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        প্রত্যাগম SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    প্রত্যাগম সত্য;
}



তার্কিক HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      ধ্রুব SDL_Rect * rects, পূর্ণাঙ্ক numrects) {
    যদি (!window) {
        প্রত্যাগম সত্য;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    প্রত্যাগম সত্য;
}

শূন্য HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(রিক্ত);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

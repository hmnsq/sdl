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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#அந்தர்பாவ "SDL_bframebuffer.h"

#அந்தர்பாவ <AppKit.h>
#அந்தர்பாவ <InterfaceKit.h>
#அந்தர்பாவ "SDL_bmodes.h"
#அந்தர்பாவ "SDL_BWin.h"

#அந்தர்பாவ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
வெளி "C" {
#endif

நிலையான SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    திரும்பு (SDL_BWin *)(window->internal);
}

நிலையான SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    திரும்பு SDL_Looper;
}

தருக்க HAIKU_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window, SDL_PixelFormat * format, வெறுமை ** pixels, முழு *pitch)
{
    SDL_BWin *bwin = _ToBeWin(window);
    BScreen bscreen;
    எனில் (!bscreen.IsValid()) {
        திரும்பு பொய்;
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

    எனில் (bitmap) {
        delete bitmap;
    }
    bitmap = புதிய BBitmap(bwin->Bounds(), (color_space)bmode.space,
            பொய்,    // Views not accepted
            உண்மை);    // Contiguous memory required

    எனில் (bitmap->InitCheck() != B_OK) {
        delete bitmap;
        திரும்பு SDL_SetError("Could not initialize back buffer!");
    }


    bwin->SetBitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->Bits();

    // pitch = width of window, in bytes
    *pitch = bitmap->BytesPerRow();

    bwin->UnlockBuffer();
    திரும்பு உண்மை;
}



தருக்க HAIKU_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window,
                                      மாறிலி SDL_Rect * rects, முழு numrects) {
    எனில் (!window) {
        திரும்பு உண்மை;
    }

    SDL_BWin *bwin = _ToBeWin(window);

    bwin->PostMessage(BWIN_UPDATE_FRAMEBUFFER);

    திரும்பு உண்மை;
}

வெறுமை HAIKU_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window * window) {
    SDL_BWin *bwin = _ToBeWin(window);

    bwin->LockBuffer();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    delete bitmap;
    bwin->SetBitmap(வெற்று);

    bwin->RemoveView();

    bwin->UnlockBuffer();
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

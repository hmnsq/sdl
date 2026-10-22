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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_HAIKU

#ಅನ್ತರ್ಭಾವ "SDL_bframebuffer.h"

#ಅನ್ತರ್ಭಾವ <AppKit.h>
#ಅನ್ತರ್ಭಾವ <InterfaceKit.h>
#ಅನ್ತರ್ಭಾವ "SDL_bmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"

#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ SDL_INLINE SDL_BWin *ಗಮ್ಯ_Be_Win(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ (SDL_BWin *)(ಕಿಟಕಿ->ಆಂತರಿಕ);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಹಿಂತಿರುಗಿ SDL_Looper;
}

ತಾರ್ಕಿಕ HAIKU_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, SDL_PixelFormat * format, ಶೂನ್ಯ ** pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_BWin *bwin = ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ);
    BScreen bscreen;
    ಆದರೆ (!bscreen.IsValid()) {
        ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->ಬೀಗ_ಬಫರ್();

    bwin->CreateView();

    // format
    display_ಬಹುಲಕ_2 bmode;
    bscreen.Get_ಬಹುಲಕ(&bmode);
    *format = HAIKU_Color_Space_ಗಮ್ಯ_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    ಆದರೆ (bitmap) {
        ಅಳಿಸು bitmap;
    }
    bitmap = ಹೊಸ BBitmap(bwin->Bounds(), (color_space)bmode.space,
            ಸುಳ್ಳು,    // Views not accepted
            ನಿಜ);    // Contiguous memory required

    ಆದರೆ (bitmap->InitCheck() != B_OK) {
        ಅಳಿಸು bitmap;
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not initialize back buffer!");
    }


    bwin->ಗಣ_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->ಬಿಟ್ಟುಗಳು_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->ಬೈಟುಗಳು_ಪ್ರತಿ_ಅಡ್ಡಸಾಲು();

    bwin->Unlock_ಬಫರ್();
    ಹಿಂತಿರುಗಿ ನಿಜ;
}



ತಾರ್ಕಿಕ HAIKU_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ,
                                      ಸ್ಥಿರಾಂಕ SDL_Rect * rects, ಪೂರ್ಣಾಂಕ numrects) {
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ ನಿಜ;
    }

    SDL_BWin *bwin = ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ);

    bwin->Post_ಸಂದೇಶ(BWIN_UPDATE_FRAMEBUFFER);

    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಶೂನ್ಯ HAIKU_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ) {
    SDL_BWin *bwin = ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ);

    bwin->ಬೀಗ_ಬಫರ್();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    ಅಳಿಸು bitmap;
    bwin->ಗಣ_Bitmap(ಖಾಲಿ);

    bwin->RemoveView();

    bwin->Unlock_ಬಫರ್();
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_HAIKU

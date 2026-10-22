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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_HAIKU

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bframebuffer.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <AppKit.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <InterfaceKit.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_BWin.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/haiku/SDL_BApp.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

ਸਥਿਰ SDL_INLINE SDL_BWin *ਮੰਜ਼ਿਲ_Be_Win(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ (SDL_BWin *)(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
}

ਸਥਿਰ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ਵਾਪਸ SDL_Looper;
}

ਤਾਰਕਿਕ HAIKU_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, SDL_PixelFormat * format, ਖਾਲੀ ** pixels, ਪੂਰਨ *pitch)
{
    SDL_BWin *bwin = ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ);
    BScreen bscreen;
    ਜੇ (!bscreen.IsValid()) {
        ਵਾਪਸ ਝੂਠ;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->ਤਾਲਾ_ਬਫਰ();

    bwin->CreateView();

    // format
    display_ਬਹੁਲਕ_2 bmode;
    bscreen.Get_ਬਹੁਲਕ(&bmode);
    *format = HAIKU_Color_Space_ਮੰਜ਼ਿਲ_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    ਜੇ (bitmap) {
        ਮਿਟਾਓ bitmap;
    }
    bitmap = ਨਵਾਂ BBitmap(bwin->Bounds(), (color_space)bmode.space,
            ਝੂਠ,    // Views not accepted
            ਸੱਚ);    // Contiguous memory required

    ਜੇ (bitmap->InitCheck() != B_OK) {
        ਮਿਟਾਓ bitmap;
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not initialize back buffer!");
    }


    bwin->ਸੈੱਟ_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->ਬਿੱਟ_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਪੰਕਤੀ();

    bwin->Unlock_ਬਫਰ();
    ਵਾਪਸ ਸੱਚ;
}



ਤਾਰਕਿਕ HAIKU_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ,
                                      ਅਚਲ SDL_Rect * rects, ਪੂਰਨ numrects) {
    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ ਸੱਚ;
    }

    SDL_BWin *bwin = ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ);

    bwin->Post_ਸੁਨੇਹਾ(BWIN_UPDATE_FRAMEBUFFER);

    ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ HAIKU_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ) {
    SDL_BWin *bwin = ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ);

    bwin->ਤਾਲਾ_ਬਫਰ();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    ਮਿਟਾਓ bitmap;
    bwin->ਸੈੱਟ_Bitmap(ਨਿਰਾ);

    bwin->RemoveView();

    bwin->Unlock_ਬਫਰ();
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU

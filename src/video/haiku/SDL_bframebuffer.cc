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

#که_تعریف_شوی SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_bframebuffer.h"

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#ضمن "../../core/haiku/SDL_BApp.h"

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_کړکۍ *کړکۍ)
{
    أرجع (SDL_BWin *)(کړکۍ->دننی);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

منطقي HAIKU_Create_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, SDL_PixelFormat * format, فراغ ** pixels, صحيح *pitch)
{
    SDL_BWin *bwin = منزل_Be_Win(کړکۍ);
    BScreen bscreen;
    إذا (!bscreen.IsValid()) {
        أرجع خطأ;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->قلف_بفر();

    bwin->CreateView();

    // format
    display_ډېرپېښ_2 bmode;
    bscreen.Get_ډېرپېښ(&bmode);
    *format = HAIKU_Color_Space_منزل_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    إذا (bitmap) {
        ړنګول bitmap;
    }
    bitmap = جديد BBitmap(bwin->Bounds(), (color_space)bmode.space,
            خطأ,    // Views not accepted
            ریښتیا);    // Contiguous memory required

    إذا (bitmap->InitCheck() != B_OK) {
        ړنګول bitmap;
        أرجع SDL_سېټ_Error("Could not initialize back buffer!");
    }


    bwin->سېټ_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->بټونه_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->بایټونه_فی_لیکه();

    bwin->Unlock_بفر();
    أرجع ریښتیا;
}



منطقي HAIKU_Update_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ,
                                      ثابت SDL_Rect * rects, صحيح numrects) {
    إذا (!کړکۍ) {
        أرجع ریښتیا;
    }

    SDL_BWin *bwin = منزل_Be_Win(کړکۍ);

    bwin->Post_پیغام(BWIN_UPDATE_FRAMEBUFFER);

    أرجع ریښتیا;
}

فراغ HAIKU_Destroy_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ) {
    SDL_BWin *bwin = منزل_Be_Win(کړکۍ);

    bwin->قلف_بفر();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    ړنګول bitmap;
    bwin->سېټ_Bitmap(عدم);

    bwin->RemoveView();

    bwin->Unlock_بفر();
}

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_VIDEO_DRIVER_HAIKU

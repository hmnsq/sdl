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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_bframebuffer.h"

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#ضمن "../../core/haiku/SDL_BApp.h"

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_دري *دري)
{
    أرجع (SDL_BWin *)(دري->اندروني);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

منطقي HAIKU_Create_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري * دري, SDL_PixelFormat * format, فراغ ** pixels, صحيح *pitch)
{
    SDL_BWin *bwin = منزل_Be_Win(دري);
    BScreen bscreen;
    إذا (!bscreen.IsValid()) {
        أرجع خطأ;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->تالو_بفر();

    bwin->CreateView();

    // format
    display_گهڻائي_2 bmode;
    bscreen.Get_گهڻائي(&bmode);
    *format = HAIKU_Color_Space_منزل_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    إذا (bitmap) {
        ميٽيو bitmap;
    }
    bitmap = جديد BBitmap(bwin->Bounds(), (color_space)bmode.space,
            خطأ,    // Views not accepted
            سچ);    // Contiguous memory required

    إذا (bitmap->InitCheck() != B_OK) {
        ميٽيو bitmap;
        أرجع SDL_سيٽ_Error("Could not initialize back buffer!");
    }


    bwin->سيٽ_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->بٽ_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->بائيٽون_في_صف();

    bwin->Unlock_بفر();
    أرجع سچ;
}



منطقي HAIKU_Update_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري * دري,
                                      ثابت SDL_Rect * rects, صحيح numrects) {
    إذا (!دري) {
        أرجع سچ;
    }

    SDL_BWin *bwin = منزل_Be_Win(دري);

    bwin->Post_پيغام(BWIN_UPDATE_FRAMEBUFFER);

    أرجع سچ;
}

فراغ HAIKU_Destroy_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري * دري) {
    SDL_BWin *bwin = منزل_Be_Win(دري);

    bwin->تالو_بفر();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    ميٽيو bitmap;
    bwin->سيٽ_Bitmap(عدم);

    bwin->RemoveView();

    bwin->Unlock_بفر();
}

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_HAIKU

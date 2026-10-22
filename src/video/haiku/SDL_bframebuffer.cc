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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_bframebuffer.h"

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#ضمن "../../core/haiku/SDL_BApp.h"

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

ساكن SDL_INLINE SDL_BWin *مقصد_Be_Win(SDL_پنجره *پنجره)
{
    أرجع (SDL_BWin *)(پنجره->داخلی);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

منطقي HAIKU_Create_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره * پنجره, SDL_PixelFormat * format, فراغ ** pixels, صحيح *pitch)
{
    SDL_BWin *bwin = مقصد_Be_Win(پنجره);
    BScreen bscreen;
    إذا (!bscreen.IsValid()) {
        أرجع خطأ;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->قفل_میانگیر();

    bwin->CreateView();

    // format
    display_نما_2 bmode;
    bscreen.Get_نما(&bmode);
    *format = HAIKU_Color_Space_مقصد_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    إذا (bitmap) {
        حذف bitmap;
    }
    bitmap = جديد BBitmap(bwin->Bounds(), (color_space)bmode.space,
            خطأ,    // Views not accepted
            درست);    // Contiguous memory required

    إذا (bitmap->InitCheck() != B_OK) {
        حذف bitmap;
        أرجع SDL_مجموعه_Error("Could not initialize back buffer!");
    }


    bwin->مجموعه_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->بیتها_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->بایتها_در_هر_ردیف();

    bwin->Unlock_میانگیر();
    أرجع درست;
}



منطقي HAIKU_Update_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره * پنجره,
                                      ثابت SDL_Rect * rects, صحيح numrects) {
    إذا (!پنجره) {
        أرجع درست;
    }

    SDL_BWin *bwin = مقصد_Be_Win(پنجره);

    bwin->Post_پیام(BWIN_UPDATE_FRAMEBUFFER);

    أرجع درست;
}

فراغ HAIKU_Destroy_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره * پنجره) {
    SDL_BWin *bwin = مقصد_Be_Win(پنجره);

    bwin->قفل_میانگیر();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    حذف bitmap;
    bwin->مجموعه_Bitmap(عدم);

    bwin->RemoveView();

    bwin->Unlock_میانگیر();
}

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // SDL_VIDEO_DRIVER_HAIKU

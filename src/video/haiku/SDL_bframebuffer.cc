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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_bframebuffer.h"

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#ضمن "../../core/haiku/SDL_BApp.h"

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_کھڑکی *کھڑکی)
{
    أرجع (SDL_BWin *)(کھڑکی->اندرونی);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

منطقي HAIKU_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_PixelFormat * format, فراغ ** pixels, صحيح *pitch)
{
    SDL_BWin *bwin = منزل_Be_Win(کھڑکی);
    BScreen bscreen;
    إذا (!bscreen.IsValid()) {
        أرجع خطأ;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->جندرا_بفر();

    bwin->CreateView();

    // format
    display_منوال_2 bmode;
    bscreen.Get_منوال(&bmode);
    *format = HAIKU_Color_Space_منزل_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    إذا (bitmap) {
        مٹاؤ bitmap;
    }
    bitmap = جديد BBitmap(bwin->Bounds(), (color_space)bmode.space,
            خطأ,    // Views not accepted
            سچ);    // Contiguous memory required

    إذا (bitmap->InitCheck() != B_OK) {
        مٹاؤ bitmap;
        أرجع SDL_سیٹ_Error("Could not initialize back buffer!");
    }


    bwin->سیٹ_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->بٹ_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->بائٹاں_فی_صف();

    bwin->Unlock_بفر();
    أرجع سچ;
}



منطقي HAIKU_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی,
                                      ثابت SDL_Rect * rects, صحيح numrects) {
    إذا (!کھڑکی) {
        أرجع سچ;
    }

    SDL_BWin *bwin = منزل_Be_Win(کھڑکی);

    bwin->Post_سنیہا(BWIN_UPDATE_FRAMEBUFFER);

    أرجع سچ;
}

فراغ HAIKU_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی) {
    SDL_BWin *bwin = منزل_Be_Win(کھڑکی);

    bwin->جندرا_بفر();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    مٹاؤ bitmap;
    bwin->سیٹ_Bitmap(عدم);

    bwin->RemoveView();

    bwin->Unlock_بفر();
}

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // SDL_VIDEO_DRIVER_HAIKU

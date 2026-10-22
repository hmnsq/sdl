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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU

#شامل "SDL_bframebuffer.h"

#شامل <AppKit.h>
#شامل <InterfaceKit.h>
#شامل "SDL_bmodes.h"
#شامل "SDL_BWin.h"

#شامل "../../core/haiku/SDL_BApp.h"

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

ساکن SDL_INLINE SDL_BWin *مقصد_Be_Win(SDL_کھڑکی *کھڑکی)
{
    واپس (SDL_BWin *)(کھڑکی->اندرونی_2);
}

ساکن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    واپس SDL_Looper;
}

منطقی HAIKU_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_PixelFormat * format, خالی ** pixels, صحیح *pitch)
{
    SDL_BWin *bwin = مقصد_Be_Win(کھڑکی);
    BScreen bscreen;
    اگر (!bscreen.IsValid()) {
        واپس جھوٹ;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->تالا_بفر();

    bwin->CreateView();

    // format
    display_منوال_2 bmode;
    bscreen.Get_منوال(&bmode);
    *format = HAIKU_Color_Space_مقصد_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    اگر (bitmap) {
        حذف bitmap;
    }
    bitmap = نیا BBitmap(bwin->Bounds(), (color_space)bmode.space,
            جھوٹ,    // Views not accepted
            سچ);    // Contiguous memory required

    اگر (bitmap->InitCheck() != B_OK) {
        حذف bitmap;
        واپس SDL_سیٹ_Error("Could not initialize back buffer!");
    }


    bwin->سیٹ_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->بٹ_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->بائٹیں_فی_صف();

    bwin->Unlock_بفر();
    واپس سچ;
}



منطقی HAIKU_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی,
                                      ثابت SDL_Rect * rects, صحیح numrects) {
    اگر (!کھڑکی) {
        واپس سچ;
    }

    SDL_BWin *bwin = مقصد_Be_Win(کھڑکی);

    bwin->Post_پیغام(BWIN_UPDATE_FRAMEBUFFER);

    واپس سچ;
}

خالی HAIKU_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی) {
    SDL_BWin *bwin = مقصد_Be_Win(کھڑکی);

    bwin->تالا_بفر();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    حذف bitmap;
    bwin->سیٹ_Bitmap(تہی);

    bwin->RemoveView();

    bwin->Unlock_بفر();
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_HAIKU

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
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_BWin.h"
#ضمن <new>

// Define a path to window's BWIN data
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

ساكن منطقي Init_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    پنجره_look look = B_TITLED_پنجره_LOOK;

    BRect bounds(
        پنجره->x,
        پنجره->y,
        پنجره->x + پنجره->w - 1,    //BeWindows have an off-by-one px w/h thing
        پنجره->y + پنجره->h - 1
    );

    إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        // TODO: Add support for this flag
    }
    إذا (!(پنجره->flags & SDL_پنجره_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    إذا (پنجره->flags & SDL_پنجره_BORDERLESS) {
        look = B_NO_BORDER_پنجره_LOOK;
    }

    SDL_BWin *bwin = جديد(std::nothrow) SDL_BWin(bounds, look, flags);
    إذا (!bwin) {
        أرجع خطأ;
    }

    پنجره->داخلی = (SDL_پنجره_داده *)bwin;
    int32 winID = _GetBeLooper()->GetID(پنجره);
    bwin->مجموعه_ID(winID);

    أرجع درست;
}

منطقي HAIKU_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    إذا (!Init_پنجره(_this, پنجره, create_props)) {
        أرجع خطأ;
    }

    // Start window loop
    مقصد_Be_Win(پنجره)->Show();
    أرجع درست;
}

فراغ HAIKU_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_مجموعه_TITLE);
    پیام_2.جمع_کن_String("window-title", پنجره->title);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

منطقي HAIKU_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_MOVE_پنجره);
    پیام_2.جمع_کن_Int32("window-x", پنجره->pending.x);
    پیام_2.جمع_کن_Int32("window-y", پنجره->pending.y);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
    أرجع درست;
}

فراغ HAIKU_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_RESIZE_پنجره);
    پیام_2.جمع_کن_Int32("window-w", پنجره->pending.w - 1);
    پیام_2.جمع_کن_Int32("window-h", پنجره->pending.h - 1);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره * پنجره, منطقي bordered)
{
    BMessage پیام_2(BWIN_مجموعه_BORDERED);
    پیام_2.جمع_کن_Bool("window-border", bordered != خطأ);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره * پنجره, منطقي resizable)
{
    BMessage پیام_2(BWIN_مجموعه_RESIZABLE);
    پیام_2.جمع_کن_Bool("window-resizable", resizable != خطأ);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_SHOW_پنجره);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_HIDE_پنجره);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_SHOW_پنجره);    // Activate this window and move to front
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_MAXIMIZE_پنجره);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_MINIMIZE_پنجره);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

فراغ HAIKU_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_RESTORE_پنجره);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

SDL_Fullscreen_نتیجه HAIKU_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage پیام_2(BWIN_FULLSCREEN);
    پیام_2.جمع_کن_Bool("fullscreen", !!fullscreen);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}


فراغ HAIKU_مجموعه_پنجره_Minimum_اندازه(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    BMessage پیام_2(BWIN_MINIMUM_اندازه_پنجره);
    پیام_2.جمع_کن_Int32("window-w", پنجره->w -1);
    پیام_2.جمع_کن_Int32("window-h", پنجره->h -1);
    مقصد_Be_Win(پنجره)->Post_پیام(&پیام_2);
}

منطقي HAIKU_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره * پنجره, منطقي grabbed)
{
    // TODO: Implement this!
    أرجع SDL_Unsupported();
}

منطقي HAIKU_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره * پنجره, SDL_پنجره *والد)
{
    أرجع درست;
}

منطقي HAIKU_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, منطقي modal)
{
    إذا (modal) {
        مقصد_Be_Win(پنجره)->مجموعه_Look(B_MODAL_پنجره_LOOK);
        مقصد_Be_Win(پنجره)->مجموعه_Feel(B_MODAL_SUBSET_پنجره_FEEL);
        مقصد_Be_Win(پنجره)->جمع_کن_مقصد_Subset(مقصد_Be_Win(پنجره->والد));
    } وإلا {
        پنجره_look look = (پنجره->flags & SDL_پنجره_BORDERLESS) ? B_NO_BORDER_پنجره_LOOK : B_TITLED_پنجره_LOOK;
        مقصد_Be_Win(پنجره)->RemoveFromSubset(مقصد_Be_Win(پنجره->والد));
        مقصد_Be_Win(پنجره)->مجموعه_Look(look);
        مقصد_Be_Win(پنجره)->مجموعه_Feel(B_نرمال_پنجره_FEEL);
    }

    أرجع درست;
}

فراغ HAIKU_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره * پنجره)
{
    مقصد_Be_Win(پنجره)->قفل_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(مقصد_Be_Win(پنجره));
    مقصد_Be_Win(پنجره)->Quit();
    پنجره->داخلی = عدم;
}

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // SDL_VIDEO_DRIVER_HAIKU

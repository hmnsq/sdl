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
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_BWin.h"
#ضمن <new>

// Define a path to window's BWIN data
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

ساكن منطقي Init_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    کړکۍ_look look = B_TITLED_کړکۍ_LOOK;

    BRect bounds(
        کړکۍ->x,
        کړکۍ->y,
        کړکۍ->x + کړکۍ->w - 1,    //BeWindows have an off-by-one px w/h thing
        کړکۍ->y + کړکۍ->h - 1
    );

    إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        // TODO: Add support for this flag
    }
    إذا (!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    إذا (کړکۍ->flags & SDL_کړکۍ_BORDERLESS) {
        look = B_NO_BORDER_کړکۍ_LOOK;
    }

    SDL_BWin *bwin = جديد(std::nothrow) SDL_BWin(bounds, look, flags);
    إذا (!bwin) {
        أرجع خطأ;
    }

    کړکۍ->دننی = (SDL_کړکۍ_معلومات *)bwin;
    int32 winID = _GetBeLooper()->GetID(کړکۍ);
    bwin->سېټ_ID(winID);

    أرجع ریښتیا;
}

منطقي HAIKU_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    إذا (!Init_کړکۍ(_this, کړکۍ, create_props)) {
        أرجع خطأ;
    }

    // Start window loop
    منزل_Be_Win(کړکۍ)->Show();
    أرجع ریښتیا;
}

فراغ HAIKU_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_سېټ_TITLE);
    پیغام_2.جمع_کړه_String("window-title", کړکۍ->title);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

منطقي HAIKU_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_MOVE_کړکۍ);
    پیغام_2.جمع_کړه_Int32("window-x", کړکۍ->pending.x);
    پیغام_2.جمع_کړه_Int32("window-y", کړکۍ->pending.y);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
    أرجع ریښتیا;
}

فراغ HAIKU_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_RESIZE_کړکۍ);
    پیغام_2.جمع_کړه_Int32("window-w", کړکۍ->pending.w - 1);
    پیغام_2.جمع_کړه_Int32("window-h", کړکۍ->pending.h - 1);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, منطقي bordered)
{
    BMessage پیغام_2(BWIN_سېټ_BORDERED);
    پیغام_2.جمع_کړه_Bool("window-border", bordered != خطأ);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, منطقي resizable)
{
    BMessage پیغام_2(BWIN_سېټ_RESIZABLE);
    پیغام_2.جمع_کړه_Bool("window-resizable", resizable != خطأ);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_SHOW_کړکۍ);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_HIDE_کړکۍ);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_SHOW_کړکۍ);    // Activate this window and move to front
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_MAXIMIZE_کړکۍ);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_MINIMIZE_کړکۍ);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

فراغ HAIKU_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_RESTORE_کړکۍ);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

SDL_Fullscreen_پایله HAIKU_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage پیغام_2(BWIN_FULLSCREEN);
    پیغام_2.جمع_کړه_Bool("fullscreen", !!fullscreen);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}


فراغ HAIKU_سېټ_کړکۍ_Minimum_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    BMessage پیغام_2(BWIN_MINIMUM_اندازه_کړکۍ);
    پیغام_2.جمع_کړه_Int32("window-w", کړکۍ->w -1);
    پیغام_2.جمع_کړه_Int32("window-h", کړکۍ->h -1);
    منزل_Be_Win(کړکۍ)->Post_پیغام(&پیغام_2);
}

منطقي HAIKU_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, منطقي grabbed)
{
    // TODO: Implement this!
    أرجع SDL_Unsupported();
}

منطقي HAIKU_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ, SDL_کړکۍ *پلار)
{
    أرجع ریښتیا;
}

منطقي HAIKU_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, منطقي modal)
{
    إذا (modal) {
        منزل_Be_Win(کړکۍ)->سېټ_Look(B_MODAL_کړکۍ_LOOK);
        منزل_Be_Win(کړکۍ)->سېټ_Feel(B_MODAL_SUBSET_کړکۍ_FEEL);
        منزل_Be_Win(کړکۍ)->جمع_کړه_منزل_Subset(منزل_Be_Win(کړکۍ->پلار));
    } وإلا {
        کړکۍ_look look = (کړکۍ->flags & SDL_کړکۍ_BORDERLESS) ? B_NO_BORDER_کړکۍ_LOOK : B_TITLED_کړکۍ_LOOK;
        منزل_Be_Win(کړکۍ)->RemoveFromSubset(منزل_Be_Win(کړکۍ->پلار));
        منزل_Be_Win(کړکۍ)->سېټ_Look(look);
        منزل_Be_Win(کړکۍ)->سېټ_Feel(B_نورمال_کړکۍ_FEEL);
    }

    أرجع ریښتیا;
}

فراغ HAIKU_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ * کړکۍ)
{
    منزل_Be_Win(کړکۍ)->قلف_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(منزل_Be_Win(کړکۍ));
    منزل_Be_Win(کړکۍ)->Quit();
    کړکۍ->دننی = عدم;
}

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_VIDEO_DRIVER_HAIKU

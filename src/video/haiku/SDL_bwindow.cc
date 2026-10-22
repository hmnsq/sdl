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
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_BWin.h"
#ضمن <new>

// Define a path to window's BWIN data
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

ساكن منطقي Init_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    کھڑکی_look look = B_TITLED_کھڑکی_LOOK;

    BRect bounds(
        کھڑکی->x,
        کھڑکی->y,
        کھڑکی->x + کھڑکی->w - 1,    //BeWindows have an off-by-one px w/h thing
        کھڑکی->y + کھڑکی->h - 1
    );

    إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        // TODO: Add support for this flag
    }
    إذا (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    إذا (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
        look = B_NO_BORDER_کھڑکی_LOOK;
    }

    SDL_BWin *bwin = جديد(std::nothrow) SDL_BWin(bounds, look, flags);
    إذا (!bwin) {
        أرجع خطأ;
    }

    کھڑکی->اندرونی = (SDL_کھڑکی_انکڑے *)bwin;
    int32 winID = _GetBeLooper()->GetID(کھڑکی);
    bwin->سیٹ_ID(winID);

    أرجع سچ;
}

منطقي HAIKU_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    إذا (!Init_کھڑکی(_this, کھڑکی, create_props)) {
        أرجع خطأ;
    }

    // Start window loop
    منزل_Be_Win(کھڑکی)->Show();
    أرجع سچ;
}

فراغ HAIKU_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_سیٹ_TITLE);
    پیغام.جوڑو_String("window-title", کھڑکی->title);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

منطقي HAIKU_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_MOVE_کھڑکی);
    پیغام.جوڑو_Int32("window-x", کھڑکی->pending.x);
    پیغام.جوڑو_Int32("window-y", کھڑکی->pending.y);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
    أرجع سچ;
}

فراغ HAIKU_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_RESIZE_کھڑکی);
    پیغام.جوڑو_Int32("window-w", کھڑکی->pending.w - 1);
    پیغام.جوڑو_Int32("window-h", کھڑکی->pending.h - 1);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, منطقي bordered)
{
    BMessage پیغام(BWIN_سیٹ_BORDERED);
    پیغام.جوڑو_Bool("window-border", bordered != خطأ);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, منطقي resizable)
{
    BMessage پیغام(BWIN_سیٹ_RESIZABLE);
    پیغام.جوڑو_Bool("window-resizable", resizable != خطأ);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_SHOW_کھڑکی);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_HIDE_کھڑکی);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_SHOW_کھڑکی);    // Activate this window and move to front
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_MAXIMIZE_کھڑکی);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_MINIMIZE_کھڑکی);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

فراغ HAIKU_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_RESTORE_کھڑکی);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

SDL_Fullscreen_نتیجہ HAIKU_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage پیغام(BWIN_FULLSCREEN);
    پیغام.جوڑو_Bool("fullscreen", !!fullscreen);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}


فراغ HAIKU_سیٹ_کھڑکی_Minimum_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام(BWIN_MINIMUM_ناپ_کھڑکی);
    پیغام.جوڑو_Int32("window-w", کھڑکی->w -1);
    پیغام.جوڑو_Int32("window-h", کھڑکی->h -1);
    منزل_Be_Win(کھڑکی)->Post_سنیہا(&پیغام);
}

منطقي HAIKU_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, منطقي grabbed)
{
    // TODO: Implement this!
    أرجع SDL_Unsupported();
}

منطقي HAIKU_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_کھڑکی *ماپا)
{
    أرجع سچ;
}

منطقي HAIKU_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, منطقي modal)
{
    إذا (modal) {
        منزل_Be_Win(کھڑکی)->سیٹ_Look(B_MODAL_کھڑکی_LOOK);
        منزل_Be_Win(کھڑکی)->سیٹ_Feel(B_MODAL_SUBSET_کھڑکی_FEEL);
        منزل_Be_Win(کھڑکی)->جوڑو_منزل_Subset(منزل_Be_Win(کھڑکی->ماپا));
    } وإلا {
        کھڑکی_look look = (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) ? B_NO_BORDER_کھڑکی_LOOK : B_TITLED_کھڑکی_LOOK;
        منزل_Be_Win(کھڑکی)->RemoveFromSubset(منزل_Be_Win(کھڑکی->ماپا));
        منزل_Be_Win(کھڑکی)->سیٹ_Look(look);
        منزل_Be_Win(کھڑکی)->سیٹ_Feel(B_عام_کھڑکی_FEEL);
    }

    أرجع سچ;
}

فراغ HAIKU_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    منزل_Be_Win(کھڑکی)->جندرا_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(منزل_Be_Win(کھڑکی));
    منزل_Be_Win(کھڑکی)->Quit();
    کھڑکی->اندرونی = عدم;
}

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // SDL_VIDEO_DRIVER_HAIKU

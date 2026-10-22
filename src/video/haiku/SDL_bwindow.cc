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
#شامل "../SDL_sysvideo.h"

#شامل "SDL_BWin.h"
#شامل <new>

// Define a path to window's BWIN data
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

ساکن منطقی Init_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    کھڑکی_look look = B_TITLED_کھڑکی_LOOK;

    BRect bounds(
        کھڑکی->x,
        کھڑکی->y,
        کھڑکی->x + کھڑکی->w - 1,    //BeWindows have an off-by-one px w/h thing
        کھڑکی->y + کھڑکی->h - 1
    );

    اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        // TODO: Add support for this flag
    }
    اگر (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    اگر (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) {
        look = B_NO_BORDER_کھڑکی_LOOK;
    }

    SDL_BWin *bwin = نیا(std::nothrow) SDL_BWin(bounds, look, flags);
    اگر (!bwin) {
        واپس جھوٹ;
    }

    کھڑکی->اندرونی_2 = (SDL_کھڑکی_ڈیٹا *)bwin;
    int32 winID = _GetBeLooper()->GetID(کھڑکی);
    bwin->سیٹ_ID(winID);

    واپس سچ;
}

منطقی HAIKU_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    اگر (!Init_کھڑکی(_this, کھڑکی, create_props)) {
        واپس جھوٹ;
    }

    // Start window loop
    مقصد_Be_Win(کھڑکی)->Show();
    واپس سچ;
}

خالی HAIKU_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_سیٹ_TITLE);
    پیغام_2.جوڑو_String("window-title", کھڑکی->title);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

منطقی HAIKU_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_MOVE_کھڑکی);
    پیغام_2.جوڑو_Int32("window-x", کھڑکی->pending.x);
    پیغام_2.جوڑو_Int32("window-y", کھڑکی->pending.y);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
    واپس سچ;
}

خالی HAIKU_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_RESIZE_کھڑکی);
    پیغام_2.جوڑو_Int32("window-w", کھڑکی->pending.w - 1);
    پیغام_2.جوڑو_Int32("window-h", کھڑکی->pending.h - 1);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, منطقی bordered)
{
    BMessage پیغام_2(BWIN_سیٹ_BORDERED);
    پیغام_2.جوڑو_Bool("window-border", bordered != جھوٹ);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, منطقی resizable)
{
    BMessage پیغام_2(BWIN_سیٹ_RESIZABLE);
    پیغام_2.جوڑو_Bool("window-resizable", resizable != جھوٹ);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_SHOW_کھڑکی);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_HIDE_کھڑکی);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_SHOW_کھڑکی);    // Activate this window and move to front
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_MAXIMIZE_کھڑکی);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_MINIMIZE_کھڑکی);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

خالی HAIKU_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_RESTORE_کھڑکی);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

SDL_Fullscreen_نتیجہ HAIKU_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage پیغام_2(BWIN_FULLSCREEN);
    پیغام_2.جوڑو_Bool("fullscreen", !!fullscreen);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
    واپس SDL_FULLSCREEN_SUCCEEDED;
}


خالی HAIKU_سیٹ_کھڑکی_Minimum_سائز(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    BMessage پیغام_2(BWIN_MINIMUM_سائز_کھڑکی);
    پیغام_2.جوڑو_Int32("window-w", کھڑکی->w -1);
    پیغام_2.جوڑو_Int32("window-h", کھڑکی->h -1);
    مقصد_Be_Win(کھڑکی)->Post_پیغام(&پیغام_2);
}

منطقی HAIKU_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, منطقی grabbed)
{
    // TODO: Implement this!
    واپس SDL_Unsupported();
}

منطقی HAIKU_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی, SDL_کھڑکی *والد)
{
    واپس سچ;
}

منطقی HAIKU_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, منطقی modal)
{
    اگر (modal) {
        مقصد_Be_Win(کھڑکی)->سیٹ_Look(B_MODAL_کھڑکی_LOOK);
        مقصد_Be_Win(کھڑکی)->سیٹ_Feel(B_MODAL_SUBSET_کھڑکی_FEEL);
        مقصد_Be_Win(کھڑکی)->جوڑو_مقصد_Subset(مقصد_Be_Win(کھڑکی->والد));
    } ورنہ {
        کھڑکی_look look = (کھڑکی->flags & SDL_کھڑکی_BORDERLESS) ? B_NO_BORDER_کھڑکی_LOOK : B_TITLED_کھڑکی_LOOK;
        مقصد_Be_Win(کھڑکی)->RemoveFromSubset(مقصد_Be_Win(کھڑکی->والد));
        مقصد_Be_Win(کھڑکی)->سیٹ_Look(look);
        مقصد_Be_Win(کھڑکی)->سیٹ_Feel(B_معمول_کھڑکی_FEEL);
    }

    واپس سچ;
}

خالی HAIKU_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی * کھڑکی)
{
    مقصد_Be_Win(کھڑکی)->تالا_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(مقصد_Be_Win(کھڑکی));
    مقصد_Be_Win(کھڑکی)->Quit();
    کھڑکی->اندرونی_2 = تہی;
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_HAIKU

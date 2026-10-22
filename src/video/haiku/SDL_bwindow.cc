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
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_BWin.h"
#ضمن <new>

// Define a path to window's BWIN data
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

ساكن منطقي Init_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    دري_look look = B_TITLED_دري_LOOK;

    BRect bounds(
        دري->x,
        دري->y,
        دري->x + دري->w - 1,    //BeWindows have an off-by-one px w/h thing
        دري->y + دري->h - 1
    );

    إذا (دري->flags & SDL_دري_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    إذا (دري->flags & SDL_دري_OPENGL) {
        // TODO: Add support for this flag
    }
    إذا (!(دري->flags & SDL_دري_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    إذا (دري->flags & SDL_دري_BORDERLESS) {
        look = B_NO_BORDER_دري_LOOK;
    }

    SDL_BWin *bwin = جديد(std::nothrow) SDL_BWin(bounds, look, flags);
    إذا (!bwin) {
        أرجع خطأ;
    }

    دري->اندروني = (SDL_دري_معلومات *)bwin;
    int32 winID = _GetBeLooper()->GetID(دري);
    bwin->سيٽ_ID(winID);

    أرجع سچ;
}

منطقي HAIKU_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    إذا (!Init_دري(_this, دري, create_props)) {
        أرجع خطأ;
    }

    // Start window loop
    منزل_Be_Win(دري)->Show();
    أرجع سچ;
}

فراغ HAIKU_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_سيٽ_TITLE);
    نياپو.جوڙيو_String("window-title", دري->title);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

منطقي HAIKU_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_MOVE_دري);
    نياپو.جوڙيو_Int32("window-x", دري->pending.x);
    نياپو.جوڙيو_Int32("window-y", دري->pending.y);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
    أرجع سچ;
}

فراغ HAIKU_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_RESIZE_دري);
    نياپو.جوڙيو_Int32("window-w", دري->pending.w - 1);
    نياپو.جوڙيو_Int32("window-h", دري->pending.h - 1);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري * دري, منطقي bordered)
{
    BMessage نياپو(BWIN_سيٽ_BORDERED);
    نياپو.جوڙيو_Bool("window-border", bordered != خطأ);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري * دري, منطقي resizable)
{
    BMessage نياپو(BWIN_سيٽ_RESIZABLE);
    نياپو.جوڙيو_Bool("window-resizable", resizable != خطأ);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_Show_دري(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_SHOW_دري);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_Hide_دري(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_HIDE_دري);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_Raise_دري(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_SHOW_دري);    // Activate this window and move to front
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_Maximize_دري(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_MAXIMIZE_دري);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_Minimize_دري(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_MINIMIZE_دري);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

فراغ HAIKU_Restore_دري(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_RESTORE_دري);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

SDL_Fullscreen_نتيجو HAIKU_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage نياپو(BWIN_FULLSCREEN);
    نياپو.جوڙيو_Bool("fullscreen", !!fullscreen);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}


فراغ HAIKU_سيٽ_دري_Minimum_سائيز(SDL_VideoDevice *_this, SDL_دري * دري)
{
    BMessage نياپو(BWIN_MINIMUM_سائيز_دري);
    نياپو.جوڙيو_Int32("window-w", دري->w -1);
    نياپو.جوڙيو_Int32("window-h", دري->h -1);
    منزل_Be_Win(دري)->Post_پيغام(&نياپو);
}

منطقي HAIKU_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري * دري, منطقي grabbed)
{
    // TODO: Implement this!
    أرجع SDL_Unsupported();
}

منطقي HAIKU_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري * دري, SDL_دري *والد)
{
    أرجع سچ;
}

منطقي HAIKU_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, منطقي modal)
{
    إذا (modal) {
        منزل_Be_Win(دري)->سيٽ_Look(B_MODAL_دري_LOOK);
        منزل_Be_Win(دري)->سيٽ_Feel(B_MODAL_SUBSET_دري_FEEL);
        منزل_Be_Win(دري)->جوڙيو_منزل_Subset(منزل_Be_Win(دري->والد));
    } وإلا {
        دري_look look = (دري->flags & SDL_دري_BORDERLESS) ? B_NO_BORDER_دري_LOOK : B_TITLED_دري_LOOK;
        منزل_Be_Win(دري)->RemoveFromSubset(منزل_Be_Win(دري->والد));
        منزل_Be_Win(دري)->سيٽ_Look(look);
        منزل_Be_Win(دري)->سيٽ_Feel(B_عام_دري_FEEL);
    }

    أرجع سچ;
}

فراغ HAIKU_Destroy_دري(SDL_VideoDevice *_this, SDL_دري * دري)
{
    منزل_Be_Win(دري)->تالو_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(منزل_Be_Win(دري));
    منزل_Be_Win(دري)->Quit();
    دري->اندروني = عدم;
}

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_HAIKU

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

#ifdef SDL_VIDEO_DRIVER_HAIKU
#ضمن "../SDL_sysvideo.h"

#ضمن "SDL_BWin.h"
#ضمن <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
خارجي "C" {
#endif

ساكن SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    أرجع (SDL_BWin *)(window->internal);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

ساكن منطقي _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    إذا (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    إذا (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    إذا (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = جديد(std::nothrow) SDL_BWin(bounds, look, flags);
    إذا (!bwin) {
        أرجع خطأ;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    أرجع true;
}

منطقي HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    إذا (!_InitWindow(_this, window, create_props)) {
        أرجع خطأ;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    أرجع true;
}

فراغ HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_SET_TITLE);
    پەیام.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&پەیام);
}

منطقي HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_MOVE_WINDOW);
    پەیام.AddInt32("window-x", window->pending.x);
    پەیام.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&پەیام);
    أرجع true;
}

فراغ HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_RESIZE_WINDOW);
    پەیام.AddInt32("window-w", window->pending.w - 1);
    پەیام.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, منطقي bordered)
{
    BMessage پەیام(BWIN_SET_BORDERED);
    پەیام.AddBool("window-border", bordered != خطأ);
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, منطقي resizable)
{
    BMessage پەیام(BWIN_SET_RESIZABLE);
    پەیام.AddBool("window-resizable", resizable != خطأ);
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&پەیام);
}

فراغ HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&پەیام);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage پەیام(BWIN_FULLSCREEN);
    پەیام.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&پەیام);
    أرجع SDL_FULLSCREEN_SUCCEEDED;
}


فراغ HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage پەیام(BWIN_MINIMUM_SIZE_WINDOW);
    پەیام.AddInt32("window-w", window->w -1);
    پەیام.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&پەیام);
}

منطقي HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, منطقي grabbed)
{
    // TODO: Implement this!
    أرجع SDL_Unsupported();
}

منطقي HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    أرجع true;
}

منطقي HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, منطقي modal)
{
    إذا (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } وإلا {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    أرجع true;
}

فراغ HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = عدم;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

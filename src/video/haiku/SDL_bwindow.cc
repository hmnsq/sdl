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
    إرجاع (SDL_BWin *)(window->internal);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    إرجاع SDL_Looper;
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
        إرجاع خطأ;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    إرجاع true;
}

منطقي HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    إذا (!_InitWindow(_this, window, create_props)) {
        إرجاع خطأ;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    إرجاع true;
}

فراغ HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_SET_TITLE);
    رسالة.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&رسالة);
}

منطقي HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_MOVE_WINDOW);
    رسالة.AddInt32("window-x", window->pending.x);
    رسالة.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&رسالة);
    إرجاع true;
}

فراغ HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_RESIZE_WINDOW);
    رسالة.AddInt32("window-w", window->pending.w - 1);
    رسالة.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, منطقي bordered)
{
    BMessage رسالة(BWIN_SET_BORDERED);
    رسالة.AddBool("window-border", bordered != خطأ);
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, منطقي resizable)
{
    BMessage رسالة(BWIN_SET_RESIZABLE);
    رسالة.AddBool("window-resizable", resizable != خطأ);
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&رسالة);
}

فراغ HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&رسالة);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage رسالة(BWIN_FULLSCREEN);
    رسالة.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&رسالة);
    إرجاع SDL_FULLSCREEN_SUCCEEDED;
}


فراغ HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage رسالة(BWIN_MINIMUM_SIZE_WINDOW);
    رسالة.AddInt32("window-w", window->w -1);
    رسالة.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&رسالة);
}

منطقي HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, منطقي grabbed)
{
    // TODO: Implement this!
    إرجاع SDL_Unsupported();
}

منطقي HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    إرجاع true;
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

    إرجاع true;
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

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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

ಸ್ಥಿರ SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ (SDL_BWin *)(window->internal);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಪ್ರತ್ಯಾಗಮ SDL_Looper;
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    ಯದಿ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    ಯದಿ (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = ನೂತನ(std::nothrow) SDL_BWin(bounds, look, flags);
    ಯದಿ (!bwin) {
        ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    ಯದಿ (!_InitWindow(_this, window, create_props)) {
        ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_SET_TITLE);
    ಸಂದೇಶ.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ತಾರ್ಕಿಕ HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_MOVE_WINDOW);
    ಸಂದೇಶ.AddInt32("window-x", window->pending.x);
    ಸಂದೇಶ.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_RESIZE_WINDOW);
    ಸಂದೇಶ.AddInt32("window-w", window->pending.w - 1);
    ಸಂದೇಶ.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, ತಾರ್ಕಿಕ bordered)
{
    BMessage ಸಂದೇಶ(BWIN_SET_BORDERED);
    ಸಂದೇಶ.AddBool("window-border", bordered != ಅಸತ್ಯ);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, ತಾರ್ಕಿಕ resizable)
{
    BMessage ಸಂದೇಶ(BWIN_SET_RESIZABLE);
    ಸಂದೇಶ.AddBool("window-resizable", resizable != ಅಸತ್ಯ);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ಶೂನ್ಯ HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage ಸಂದೇಶ(BWIN_FULLSCREEN);
    ಸಂದೇಶ.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
    ಪ್ರತ್ಯಾಗಮ SDL_FULLSCREEN_SUCCEEDED;
}


ಶೂನ್ಯ HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ಸಂದೇಶ(BWIN_MINIMUM_SIZE_WINDOW);
    ಸಂದೇಶ.AddInt32("window-w", window->w -1);
    ಸಂದೇಶ.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&ಸಂದೇಶ);
}

ತಾರ್ಕಿಕ HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, ತಾರ್ಕಿಕ grabbed)
{
    // TODO: Implement this!
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

ತಾರ್ಕಿಕ HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, ತಾರ್ಕಿಕ modal)
{
    ಯದಿ (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } ಅನ್ಯಥಾ {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = ರಿಕ್ತ;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

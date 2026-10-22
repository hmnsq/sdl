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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU
#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव "SDL_BWin.h"
#अन्तर्भाव <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
बाह्य "C" {
#endif

स्थिर SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    प्रत्यागम (SDL_BWin *)(window->internal);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    प्रत्यागम SDL_Looper;
}

स्थिर तार्किक _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    जइ (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    जइ (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    जइ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    जइ (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = नूतन(std::nothrow) SDL_BWin(bounds, look, flags);
    जइ (!bwin) {
        प्रत्यागम मिच्छ;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    प्रत्यागम सच्च;
}

तार्किक HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    जइ (!_InitWindow(_this, window, create_props)) {
        प्रत्यागम मिच्छ;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    प्रत्यागम सच्च;
}

शून्य HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_SET_TITLE);
    सन्देशः.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

तार्किक HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_MOVE_WINDOW);
    सन्देशः.AddInt32("window-x", window->pending.x);
    सन्देशः.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&सन्देशः);
    प्रत्यागम सच्च;
}

शून्य HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_RESIZE_WINDOW);
    सन्देशः.AddInt32("window-w", window->pending.w - 1);
    सन्देशः.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, तार्किक bordered)
{
    BMessage सन्देशः(BWIN_SET_BORDERED);
    सन्देशः.AddBool("window-border", bordered != मिच्छ);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, तार्किक resizable)
{
    BMessage सन्देशः(BWIN_SET_RESIZABLE);
    सन्देशः.AddBool("window-resizable", resizable != मिच्छ);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

शून्य HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage सन्देशः(BWIN_FULLSCREEN);
    सन्देशः.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&सन्देशः);
    प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
}


शून्य HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage सन्देशः(BWIN_MINIMUM_SIZE_WINDOW);
    सन्देशः.AddInt32("window-w", window->w -1);
    सन्देशः.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&सन्देशः);
}

तार्किक HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, तार्किक grabbed)
{
    // TODO: Implement this!
    प्रत्यागम SDL_Unsupported();
}

तार्किक HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    प्रत्यागम सच्च;
}

तार्किक HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, तार्किक modal)
{
    जइ (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } अण्णहा {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    प्रत्यागम सच्च;
}

शून्य HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = रिक्त;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

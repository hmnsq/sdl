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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_HAIKU
#समावेश "../SDL_sysvideo.h"

#समावेश "SDL_BWin.h"
#समावेश <new>

// Define a path to window's BWIN data
#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

अटल SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    वापस (SDL_BWin *)(window->internal);
}

अटल SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    वापस SDL_Looper;
}

अटल bool _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    अगर (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    अगर (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = नया(std::nothrow) SDL_BWin(bounds, look, flags);
    अगर (!bwin) {
        वापस false;
    }

    window->internal = (SDL_Window_तथ्य *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    वापस true;
}

bool HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    अगर (!_InitWindow(_this, window, create_props)) {
        वापस false;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    वापस true;
}

व्योम HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_SET_TITLE);
    संदेश.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&संदेश);
}

bool HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_MOVE_WINDOW);
    संदेश.AddInt32("window-x", window->pending.x);
    संदेश.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&संदेश);
    वापस true;
}

व्योम HAIKU_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_RESIZE_WINDOW);
    संदेश.AddInt32("window-w", window->pending.w - 1);
    संदेश.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, bool bordered)
{
    BMessage संदेश(BWIN_SET_BORDERED);
    संदेश.AddBool("window-border", bordered != false);
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, bool resizable)
{
    BMessage संदेश(BWIN_SET_RESIZABLE);
    संदेश.AddBool("window-resizable", resizable != false);
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&संदेश);
}

व्योम HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&संदेश);
}

SDL_Fullscreen_परिणाम HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage संदेश(BWIN_FULLSCREEN);
    संदेश.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&संदेश);
    वापस SDL_FULLSCREEN_SUCCEEDED;
}


व्योम HAIKU_Set_Window_Minimum_आकार(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage संदेश(BWIN_MINIMUM_आकार_WINDOW);
    संदेश.AddInt32("window-w", window->w -1);
    संदेश.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&संदेश);
}

bool HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, bool grabbed)
{
    // TODO: Implement this!
    वापस SDL_Unsupported();
}

bool HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    वापस true;
}

bool HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
    अगर (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } अन्यथा {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    वापस true;
}

व्योम HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = शून्य;
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU

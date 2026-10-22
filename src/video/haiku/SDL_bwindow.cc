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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU
#അന്തര്ഭാവ "../SDL_sysvideo.h"

#അന്തര്ഭാവ "SDL_BWin.h"
#അന്തര്ഭാവ <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

സ്ഥിതം SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    തിരികെ (SDL_BWin *)(window->internal);
}

സ്ഥിതം SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    തിരികെ SDL_Looper;
}

സ്ഥിതം തർക്കം _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    എങ്കിൽ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    എങ്കിൽ (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = പുതിയ(std::nothrow) SDL_BWin(bounds, look, flags);
    എങ്കിൽ (!bwin) {
        തിരികെ അസത്യം;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    തിരികെ സത്യം;
}

തർക്കം HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    എങ്കിൽ (!_InitWindow(_this, window, create_props)) {
        തിരികെ അസത്യം;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    തിരികെ സത്യം;
}

ശൂന്യം HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_SET_TITLE);
    സന്ദേശം.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

തർക്കം HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_MOVE_WINDOW);
    സന്ദേശം.AddInt32("window-x", window->pending.x);
    സന്ദേശം.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
    തിരികെ സത്യം;
}

ശൂന്യം HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_RESIZE_WINDOW);
    സന്ദേശം.AddInt32("window-w", window->pending.w - 1);
    സന്ദേശം.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, തർക്കം bordered)
{
    BMessage സന്ദേശം(BWIN_SET_BORDERED);
    സന്ദേശം.AddBool("window-border", bordered != അസത്യം);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, തർക്കം resizable)
{
    BMessage സന്ദേശം(BWIN_SET_RESIZABLE);
    സന്ദേശം.AddBool("window-resizable", resizable != അസത്യം);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

ശൂന്യം HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage സന്ദേശം(BWIN_FULLSCREEN);
    സന്ദേശം.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
    തിരികെ SDL_FULLSCREEN_SUCCEEDED;
}


ശൂന്യം HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage സന്ദേശം(BWIN_MINIMUM_SIZE_WINDOW);
    സന്ദേശം.AddInt32("window-w", window->w -1);
    സന്ദേശം.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&സന്ദേശം);
}

തർക്കം HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, തർക്കം grabbed)
{
    // TODO: Implement this!
    തിരികെ SDL_Unsupported();
}

തർക്കം HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    തിരികെ സത്യം;
}

തർക്കം HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, തർക്കം modal)
{
    എങ്കിൽ (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } അല്ലെങ്കിൽ {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    തിരികെ സത്യം;
}

ശൂന്യം HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = ശൂന്യ;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

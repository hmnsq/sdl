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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

#ଅନ୍ତର୍ଭାଵ "SDL_BWin.h"
#ଅନ୍ତର୍ଭାଵ <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

ସ୍ଥିର SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ଫେରନ୍ତୁ (SDL_BWin *)(window->internal);
}

ସ୍ଥିର SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ଫେରନ୍ତୁ SDL_Looper;
}

ସ୍ଥିର ତାର୍କିକ _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    ଯଦି (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    ଯଦି (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = ନୂତନ(std::nothrow) SDL_BWin(bounds, look, flags);
    ଯଦି (!bwin) {
        ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    ଯଦି (!_InitWindow(_this, window, create_props)) {
        ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଶୂନ୍ୟ HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_SET_TITLE);
    ସନ୍ଦେଶ.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ତାର୍କିକ HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_MOVE_WINDOW);
    ସନ୍ଦେଶ.AddInt32("window-x", window->pending.x);
    ସନ୍ଦେଶ.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଶୂନ୍ୟ HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_RESIZE_WINDOW);
    ସନ୍ଦେଶ.AddInt32("window-w", window->pending.w - 1);
    ସନ୍ଦେଶ.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, ତାର୍କିକ bordered)
{
    BMessage ସନ୍ଦେଶ(BWIN_SET_BORDERED);
    ସନ୍ଦେଶ.AddBool("window-border", bordered != ମିଥ୍ୟା);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, ତାର୍କିକ resizable)
{
    BMessage ସନ୍ଦେଶ(BWIN_SET_RESIZABLE);
    ସନ୍ଦେଶ.AddBool("window-resizable", resizable != ମିଥ୍ୟା);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ଶୂନ୍ୟ HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage ସନ୍ଦେଶ(BWIN_FULLSCREEN);
    ସନ୍ଦେଶ.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
    ଫେରନ୍ତୁ SDL_FULLSCREEN_SUCCEEDED;
}


ଶୂନ୍ୟ HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage ସନ୍ଦେଶ(BWIN_MINIMUM_SIZE_WINDOW);
    ସନ୍ଦେଶ.AddInt32("window-w", window->w -1);
    ସନ୍ଦେଶ.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&ସନ୍ଦେଶ);
}

ତାର୍କିକ HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, ତାର୍କିକ grabbed)
{
    // TODO: Implement this!
    ଫେରନ୍ତୁ SDL_Unsupported();
}

ତାର୍କିକ HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, ତାର୍କିକ modal)
{
    ଯଦି (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } ଅନ୍ୟଥା {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଶୂନ୍ୟ HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = ଖାଲି;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

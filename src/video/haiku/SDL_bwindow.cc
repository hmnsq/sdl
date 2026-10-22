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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU
#અન્તર્ભાવ "../SDL_sysvideo.h"

#અન્તર્ભાવ "SDL_BWin.h"
#અન્તર્ભાવ <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
બાહ્ય "C" {
#endif

સ્થિર SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    પાછા (SDL_BWin *)(window->internal);
}

સ્થિર SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    પાછા SDL_Looper;
}

સ્થિર તાર્કિક _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    જો (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    જો (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    જો (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    જો (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = નવું(std::nothrow) SDL_BWin(bounds, look, flags);
    જો (!bwin) {
        પાછા ખોટું;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    પાછા સાચું;
}

તાર્કિક HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    જો (!_InitWindow(_this, window, create_props)) {
        પાછા ખોટું;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    પાછા સાચું;
}

શૂન્ય HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_SET_TITLE);
    સંદેશ.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

તાર્કિક HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_MOVE_WINDOW);
    સંદેશ.AddInt32("window-x", window->pending.x);
    સંદેશ.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&સંદેશ);
    પાછા સાચું;
}

શૂન્ય HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_RESIZE_WINDOW);
    સંદેશ.AddInt32("window-w", window->pending.w - 1);
    સંદેશ.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, તાર્કિક bordered)
{
    BMessage સંદેશ(BWIN_SET_BORDERED);
    સંદેશ.AddBool("window-border", bordered != ખોટું);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, તાર્કિક resizable)
{
    BMessage સંદેશ(BWIN_SET_RESIZABLE);
    સંદેશ.AddBool("window-resizable", resizable != ખોટું);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

શૂન્ય HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage સંદેશ(BWIN_FULLSCREEN);
    સંદેશ.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&સંદેશ);
    પાછા SDL_FULLSCREEN_SUCCEEDED;
}


શૂન્ય HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage સંદેશ(BWIN_MINIMUM_SIZE_WINDOW);
    સંદેશ.AddInt32("window-w", window->w -1);
    સંદેશ.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&સંદેશ);
}

તાર્કિક HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, તાર્કિક grabbed)
{
    // TODO: Implement this!
    પાછા SDL_Unsupported();
}

તાર્કિક HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    પાછા સાચું;
}

તાર્કિક HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, તાર્કિક modal)
{
    જો (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } નહીંતર {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    પાછા સાચું;
}

શૂન્ય HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = ખાલી;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU
#অন্তর্ভাৱ "../SDL_sysvideo.h"

#অন্তর্ভাৱ "SDL_BWin.h"
#অন্তর্ভাৱ <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
বাহ্য "C" {
#endif

স্থির SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ঘূৰাই (SDL_BWin *)(window->internal);
}

স্থির SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ঘূৰাই SDL_Looper;
}

স্থির তার্কিক _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    যদি (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    যদি (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = নূতন(std::nothrow) SDL_BWin(bounds, look, flags);
    যদি (!bwin) {
        ঘূৰাই মিছা;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    ঘূৰাই সঁচা;
}

তার্কিক HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    যদি (!_InitWindow(_this, window, create_props)) {
        ঘূৰাই মিছা;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    ঘূৰাই সঁচা;
}

শূন্য HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_SET_TITLE);
    বাৰ্তা.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

তার্কিক HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_MOVE_WINDOW);
    বাৰ্তা.AddInt32("window-x", window->pending.x);
    বাৰ্তা.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
    ঘূৰাই সঁচা;
}

শূন্য HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_RESIZE_WINDOW);
    বাৰ্তা.AddInt32("window-w", window->pending.w - 1);
    বাৰ্তা.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, তার্কিক bordered)
{
    BMessage বাৰ্তা(BWIN_SET_BORDERED);
    বাৰ্তা.AddBool("window-border", bordered != মিছা);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, তার্কিক resizable)
{
    BMessage বাৰ্তা(BWIN_SET_RESIZABLE);
    বাৰ্তা.AddBool("window-resizable", resizable != মিছা);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

শূন্য HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage বাৰ্তা(BWIN_FULLSCREEN);
    বাৰ্তা.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
    ঘূৰাই SDL_FULLSCREEN_SUCCEEDED;
}


শূন্য HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage বাৰ্তা(BWIN_MINIMUM_SIZE_WINDOW);
    বাৰ্তা.AddInt32("window-w", window->w -1);
    বাৰ্তা.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&বাৰ্তা);
}

তার্কিক HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, তার্কিক grabbed)
{
    // TODO: Implement this!
    ঘূৰাই SDL_Unsupported();
}

তার্কিক HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    ঘূৰাই সঁচা;
}

তার্কিক HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, তার্কিক modal)
{
    যদি (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } অন্যথা {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    ঘূৰাই সঁচা;
}

শূন্য HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = রিক্ত;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

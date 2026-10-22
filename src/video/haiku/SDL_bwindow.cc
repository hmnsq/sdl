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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU
#அந்தர்பாவ "../SDL_sysvideo.h"

#அந்தர்பாவ "SDL_BWin.h"
#அந்தர்பாவ <new>

// Define a path to window's BWIN data
#ifdef __cplusplus
வெளி "C" {
#endif

நிலையான SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    திரும்பு (SDL_BWin *)(window->internal);
}

நிலையான SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    திரும்பு SDL_Looper;
}

நிலையான தருக்க _InitWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    window_look look = B_TITLED_WINDOW_LOOK;

    BRect bounds(
        window->x,
        window->y,
        window->x + window->w - 1,    //BeWindows have an off-by-one px w/h thing
        window->y + window->h - 1
    );

    எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    எனில் (window->flags & SDL_WINDOW_OPENGL) {
        // TODO: Add support for this flag
    }
    எனில் (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    எனில் (window->flags & SDL_WINDOW_BORDERLESS) {
        look = B_NO_BORDER_WINDOW_LOOK;
    }

    SDL_BWin *bwin = புதிய(std::nothrow) SDL_BWin(bounds, look, flags);
    எனில் (!bwin) {
        திரும்பு பொய்;
    }

    window->internal = (SDL_WindowData *)bwin;
    int32 winID = _GetBeLooper()->GetID(window);
    bwin->SetID(winID);

    திரும்பு உண்மை;
}

தருக்க HAIKU_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    எனில் (!_InitWindow(_this, window, create_props)) {
        திரும்பு பொய்;
    }

    // Start window loop
    _ToBeWin(window)->Show();
    திரும்பு உண்மை;
}

வெறுமை HAIKU_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_SET_TITLE);
    செய்தி.AddString("window-title", window->title);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

தருக்க HAIKU_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_MOVE_WINDOW);
    செய்தி.AddInt32("window-x", window->pending.x);
    செய்தி.AddInt32("window-y", window->pending.y);
    _ToBeWin(window)->PostMessage(&செய்தி);
    திரும்பு உண்மை;
}

வெறுமை HAIKU_SetWindowSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_RESIZE_WINDOW);
    செய்தி.AddInt32("window-w", window->pending.w - 1);
    செய்தி.AddInt32("window-h", window->pending.h - 1);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window * window, தருக்க bordered)
{
    BMessage செய்தி(BWIN_SET_BORDERED);
    செய்தி.AddBool("window-border", bordered != பொய்);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window * window, தருக்க resizable)
{
    BMessage செய்தி(BWIN_SET_RESIZABLE);
    செய்தி.AddBool("window-resizable", resizable != பொய்);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_ShowWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_SHOW_WINDOW);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_HideWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_HIDE_WINDOW);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_RaiseWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_SHOW_WINDOW);    // Activate this window and move to front
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_MAXIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_MINIMIZE_WINDOW);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

வெறுமை HAIKU_RestoreWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_RESTORE_WINDOW);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

SDL_FullscreenResult HAIKU_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage செய்தி(BWIN_FULLSCREEN);
    செய்தி.AddBool("fullscreen", !!fullscreen);
    _ToBeWin(window)->PostMessage(&செய்தி);
    திரும்பு SDL_FULLSCREEN_SUCCEEDED;
}


வெறுமை HAIKU_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window * window)
{
    BMessage செய்தி(BWIN_MINIMUM_SIZE_WINDOW);
    செய்தி.AddInt32("window-w", window->w -1);
    செய்தி.AddInt32("window-h", window->h -1);
    _ToBeWin(window)->PostMessage(&செய்தி);
}

தருக்க HAIKU_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window * window, தருக்க grabbed)
{
    // TODO: Implement this!
    திரும்பு SDL_Unsupported();
}

தருக்க HAIKU_SetWindowParent(SDL_VideoDevice *_this, SDL_Window * window, SDL_Window *parent)
{
    திரும்பு உண்மை;
}

தருக்க HAIKU_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, தருக்க modal)
{
    எனில் (modal) {
        _ToBeWin(window)->SetLook(B_MODAL_WINDOW_LOOK);
        _ToBeWin(window)->SetFeel(B_MODAL_SUBSET_WINDOW_FEEL);
        _ToBeWin(window)->AddToSubset(_ToBeWin(window->parent));
    } இல்லையெனில் {
        window_look look = (window->flags & SDL_WINDOW_BORDERLESS) ? B_NO_BORDER_WINDOW_LOOK : B_TITLED_WINDOW_LOOK;
        _ToBeWin(window)->RemoveFromSubset(_ToBeWin(window->parent));
        _ToBeWin(window)->SetLook(look);
        _ToBeWin(window)->SetFeel(B_NORMAL_WINDOW_FEEL);
    }

    திரும்பு உண்மை;
}

வெறுமை HAIKU_DestroyWindow(SDL_VideoDevice *_this, SDL_Window * window)
{
    _ToBeWin(window)->LockLooper();    // This MUST be locked
    _GetBeLooper()->ClearID(_ToBeWin(window));
    _ToBeWin(window)->Quit();
    window->internal = வெற்று;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

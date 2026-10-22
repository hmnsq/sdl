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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_HAIKU
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_BWin.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <new>

// Define a path to window's BWIN data
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

ਸਥਿਰ SDL_INLINE SDL_BWin *ਮੰਜ਼ਿਲ_Be_Win(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ (SDL_BWin *)(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
}

ਸਥਿਰ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ਵਾਪਸ SDL_Looper;
}

ਸਥਿਰ ਤਾਰਕਿਕ Init_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    ਖਿੜਕੀ_look look = B_TITLED_ਖਿੜਕੀ_LOOK;

    BRect bounds(
        ਖਿੜਕੀ->x,
        ਖਿੜਕੀ->y,
        ਖਿੜਕੀ->x + ਖਿੜਕੀ->w - 1,    //BeWindows have an off-by-one px w/h thing
        ਖਿੜਕੀ->y + ਖਿੜਕੀ->h - 1
    );

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        // TODO: Add support for this flag
    }
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) {
        look = B_NO_BORDER_ਖਿੜਕੀ_LOOK;
    }

    SDL_BWin *bwin = ਨਵਾਂ(std::nothrow) SDL_BWin(bounds, look, flags);
    ਜੇ (!bwin) {
        ਵਾਪਸ ਝੂਠ;
    }

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)bwin;
    int32 winID = _GetBeLooper()->GetID(ਖਿੜਕੀ);
    bwin->ਸੈੱਟ_ID(winID);

    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ HAIKU_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    ਜੇ (!Init_ਖਿੜਕੀ(_this, ਖਿੜਕੀ, create_props)) {
        ਵਾਪਸ ਝੂਠ;
    }

    // Start window loop
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Show();
    ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_ਸੈੱਟ_TITLE);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_String("window-title", ਖਿੜਕੀ->title);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਤਾਰਕਿਕ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_MOVE_ਖਿੜਕੀ);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-x", ਖਿੜਕੀ->pending.x);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-y", ਖਿੜਕੀ->pending.y);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
    ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_RESIZE_ਖਿੜਕੀ);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-w", ਖਿੜਕੀ->pending.w - 1);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-h", ਖਿੜਕੀ->pending.h - 1);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, ਤਾਰਕਿਕ bordered)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_ਸੈੱਟ_BORDERED);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Bool("window-border", bordered != ਝੂਠ);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, ਤਾਰਕਿਕ resizable)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_ਸੈੱਟ_RESIZABLE);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Bool("window-resizable", resizable != ਝੂਠ);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_SHOW_ਖਿੜਕੀ);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_HIDE_ਖਿੜਕੀ);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_SHOW_ਖਿੜਕੀ);    // Activate this window and move to front
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_MAXIMIZE_ਖਿੜਕੀ);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_MINIMIZE_ਖਿੜਕੀ);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਖਾਲੀ HAIKU_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_RESTORE_ਖਿੜਕੀ);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

SDL_Fullscreen_ਨਤੀਜਾ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage ਸੁਨੇਹਾ_2(BWIN_FULLSCREEN);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Bool("fullscreen", !!fullscreen);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
    ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
}


ਖਾਲੀ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    BMessage ਸੁਨੇਹਾ_2(BWIN_MINIMUM_ਮਾਪ_ਖਿੜਕੀ);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-w", ਖਿੜਕੀ->w -1);
    ਸੁਨੇਹਾ_2.ਜੋੜੋ_Int32("window-h", ਖਿੜਕੀ->h -1);
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Post_ਸੁਨੇਹਾ(&ਸੁਨੇਹਾ_2);
}

ਤਾਰਕਿਕ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, ਤਾਰਕਿਕ grabbed)
{
    // TODO: Implement this!
    ਵਾਪਸ SDL_Unsupported();
}

ਤਾਰਕਿਕ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ)
{
    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਤਾਰਕਿਕ modal)
{
    ਜੇ (modal) {
        ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->ਸੈੱਟ_Look(B_MODAL_ਖਿੜਕੀ_LOOK);
        ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->ਸੈੱਟ_Feel(B_MODAL_SUBSET_ਖਿੜਕੀ_FEEL);
        ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->ਜੋੜੋ_ਮੰਜ਼ਿਲ_Subset(ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ->ਮਾਪਾ));
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ_look look = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) ? B_NO_BORDER_ਖਿੜਕੀ_LOOK : B_TITLED_ਖਿੜਕੀ_LOOK;
        ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->RemoveFromSubset(ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ->ਮਾਪਾ));
        ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->ਸੈੱਟ_Look(look);
        ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->ਸੈੱਟ_Feel(B_ਸਾਧਾਰਨ_ਖਿੜਕੀ_FEEL);
    }

    ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ HAIKU_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ * ਖਿੜਕੀ)
{
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->ਤਾਲਾ_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ));
    ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ)->Quit();
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU

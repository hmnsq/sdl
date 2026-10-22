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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_HAIKU
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ <new>

// Define a path to window's BWIN data
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ SDL_INLINE SDL_BWin *ಗಮ್ಯ_Be_Win(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ (SDL_BWin *)(ಕಿಟಕಿ->ಆಂತರಿಕ);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಹಿಂತಿರುಗಿ SDL_Looper;
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ Init_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    ಕಿಟಕಿ_look look = B_TITLED_ಕಿಟಕಿ_LOOK;

    BRect bounds(
        ಕಿಟಕಿ->x,
        ಕಿಟಕಿ->y,
        ಕಿಟಕಿ->x + ಕಿಟಕಿ->w - 1,    //BeWindows have an off-by-one px w/h thing
        ಕಿಟಕಿ->y + ಕಿಟಕಿ->h - 1
    );

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        // TODO: Add support for this flag
    }
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) {
        look = B_NO_BORDER_ಕಿಟಕಿ_LOOK;
    }

    SDL_BWin *bwin = ಹೊಸ(std::nothrow) SDL_BWin(bounds, look, flags);
    ಆದರೆ (!bwin) {
        ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

    ಕಿಟಕಿ->ಆಂತರಿಕ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)bwin;
    int32 winID = _GetBeLooper()->GetID(ಕಿಟಕಿ);
    bwin->ಗಣ_ID(winID);

    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ತಾರ್ಕಿಕ HAIKU_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    ಆದರೆ (!Init_ಕಿಟಕಿ(_this, ಕಿಟಕಿ, create_props)) {
        ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

    // Start window loop
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Show();
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_ಗಣ_TITLE);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_String("window-title", ಕಿಟಕಿ->title);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ತಾರ್ಕಿಕ HAIKU_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_MOVE_ಕಿಟಕಿ);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-x", ಕಿಟಕಿ->pending.x);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-y", ಕಿಟಕಿ->pending.y);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_RESIZE_ಕಿಟಕಿ);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-w", ಕಿಟಕಿ->pending.w - 1);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-h", ಕಿಟಕಿ->pending.h - 1);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, ತಾರ್ಕಿಕ bordered)
{
    BMessage ಸಂದೇಶ_2(BWIN_ಗಣ_BORDERED);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Bool("window-border", bordered != ಸುಳ್ಳು);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, ತಾರ್ಕಿಕ resizable)
{
    BMessage ಸಂದೇಶ_2(BWIN_ಗಣ_RESIZABLE);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Bool("window-resizable", resizable != ಸುಳ್ಳು);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_SHOW_ಕಿಟಕಿ);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_HIDE_ಕಿಟಕಿ);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_SHOW_ಕಿಟಕಿ);    // Activate this window and move to front
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_MAXIMIZE_ಕಿಟಕಿ);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_MINIMIZE_ಕಿಟಕಿ);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ಶೂನ್ಯ HAIKU_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_RESTORE_ಕಿಟಕಿ);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

SDL_Fullscreen_ಫಲಿತಾಂಶ HAIKU_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage ಸಂದೇಶ_2(BWIN_FULLSCREEN);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Bool("fullscreen", !!fullscreen);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
}


ಶೂನ್ಯ HAIKU_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    BMessage ಸಂದೇಶ_2(BWIN_MINIMUM_ಗಾತ್ರ_ಕಿಟಕಿ);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-w", ಕಿಟಕಿ->w -1);
    ಸಂದೇಶ_2.ಕೂಡಿಸು_Int32("window-h", ಕಿಟಕಿ->h -1);
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Post_ಸಂದೇಶ(&ಸಂದೇಶ_2);
}

ತಾರ್ಕಿಕ HAIKU_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, ತಾರ್ಕಿಕ grabbed)
{
    // TODO: Implement this!
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

ತಾರ್ಕಿಕ HAIKU_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ)
{
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ತಾರ್ಕಿಕ HAIKU_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ತಾರ್ಕಿಕ modal)
{
    ಆದರೆ (modal) {
        ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->ಗಣ_Look(B_MODAL_ಕಿಟಕಿ_LOOK);
        ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->ಗಣ_Feel(B_MODAL_SUBSET_ಕಿಟಕಿ_FEEL);
        ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->ಕೂಡಿಸು_ಗಮ್ಯ_Subset(ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ->ಪೋಷಕ));
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ_look look = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) ? B_NO_BORDER_ಕಿಟಕಿ_LOOK : B_TITLED_ಕಿಟಕಿ_LOOK;
        ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->RemoveFromSubset(ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ->ಪೋಷಕ));
        ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->ಗಣ_Look(look);
        ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->ಗಣ_Feel(B_ಸಾಮಾನ್ಯ_ಕಿಟಕಿ_FEEL);
    }

    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಶೂನ್ಯ HAIKU_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ * ಕಿಟಕಿ)
{
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->ಬೀಗ_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ));
    ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ)->Quit();
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_HAIKU

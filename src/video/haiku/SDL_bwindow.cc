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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_HAIKU
#अन्तर्भाव "../SDL_sysvideo.h"

#अन्तर्भाव "SDL_BWin.h"
#अन्तर्भाव <new>

// Define a path to window's BWIN data
#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

स्थिर SDL_INLINE SDL_BWin *गन्तव्यम्_Be_Win(SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम (SDL_BWin *)(गवाक्षः->आन्तरिकम्);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    प्रत्यागम SDL_Looper;
}

स्थिर तार्किक Init_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    गवाक्षः_look look = B_TITLED_गवाक्षः_LOOK;

    BRect bounds(
        गवाक्षः->x,
        गवाक्षः->y,
        गवाक्षः->x + गवाक्षः->w - 1,    //BeWindows have an off-by-one px w/h thing
        गवाक्षः->y + गवाक्षः->h - 1
    );

    यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        // TODO: Add support for this flag
    }
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    यदि (गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) {
        look = B_NO_BORDER_गवाक्षः_LOOK;
    }

    SDL_BWin *bwin = नूतन(std::nothrow) SDL_BWin(bounds, look, flags);
    यदि (!bwin) {
        प्रत्यागम असत्य;
    }

    गवाक्षः->आन्तरिकम् = (SDL_गवाक्षः_दत्त *)bwin;
    int32 winID = _GetBeLooper()->GetID(गवाक्षः);
    bwin->समुच्चयः_ID(winID);

    प्रत्यागम सत्य;
}

तार्किक HAIKU_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    यदि (!Init_गवाक्षः(_this, गवाक्षः, create_props)) {
        प्रत्यागम असत्य;
    }

    // Start window loop
    गन्तव्यम्_Be_Win(गवाक्षः)->Show();
    प्रत्यागम सत्य;
}

शून्य HAIKU_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_समुच्चयः_TITLE);
    सन्देशः_2.सङ्कलय_String("window-title", गवाक्षः->title);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

तार्किक HAIKU_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_MOVE_गवाक्षः);
    सन्देशः_2.सङ्कलय_Int32("window-x", गवाक्षः->pending.x);
    सन्देशः_2.सङ्कलय_Int32("window-y", गवाक्षः->pending.y);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
    प्रत्यागम सत्य;
}

शून्य HAIKU_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_RESIZE_गवाक्षः);
    सन्देशः_2.सङ्कलय_Int32("window-w", गवाक्षः->pending.w - 1);
    सन्देशः_2.सङ्कलय_Int32("window-h", गवाक्षः->pending.h - 1);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, तार्किक bordered)
{
    BMessage सन्देशः_2(BWIN_समुच्चयः_BORDERED);
    सन्देशः_2.सङ्कलय_Bool("window-border", bordered != असत्य);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, तार्किक resizable)
{
    BMessage सन्देशः_2(BWIN_समुच्चयः_RESIZABLE);
    सन्देशः_2.सङ्कलय_Bool("window-resizable", resizable != असत्य);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_SHOW_गवाक्षः);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_HIDE_गवाक्षः);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_SHOW_गवाक्षः);    // Activate this window and move to front
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_MAXIMIZE_गवाक्षः);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_MINIMIZE_गवाक्षः);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

शून्य HAIKU_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_RESTORE_गवाक्षः);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

SDL_Fullscreen_परिणाम HAIKU_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage सन्देशः_2(BWIN_FULLSCREEN);
    सन्देशः_2.सङ्कलय_Bool("fullscreen", !!fullscreen);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
    प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
}


शून्य HAIKU_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    BMessage सन्देशः_2(BWIN_MINIMUM_आकार_गवाक्षः);
    सन्देशः_2.सङ्कलय_Int32("window-w", गवाक्षः->w -1);
    सन्देशः_2.सङ्कलय_Int32("window-h", गवाक्षः->h -1);
    गन्तव्यम्_Be_Win(गवाक्षः)->Post_सन्देशः(&सन्देशः_2);
}

तार्किक HAIKU_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, तार्किक grabbed)
{
    // TODO: Implement this!
    प्रत्यागम SDL_Unsupported();
}

तार्किक HAIKU_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, SDL_गवाक्षः *parent)
{
    प्रत्यागम सत्य;
}

तार्किक HAIKU_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, तार्किक modal)
{
    यदि (modal) {
        गन्तव्यम्_Be_Win(गवाक्षः)->समुच्चयः_Look(B_MODAL_गवाक्षः_LOOK);
        गन्तव्यम्_Be_Win(गवाक्षः)->समुच्चयः_Feel(B_MODAL_SUBSET_गवाक्षः_FEEL);
        गन्तव्यम्_Be_Win(गवाक्षः)->सङ्कलय_गन्तव्यम्_Subset(गन्तव्यम्_Be_Win(गवाक्षः->parent));
    } अन्यथा {
        गवाक्षः_look look = (गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) ? B_NO_BORDER_गवाक्षः_LOOK : B_TITLED_गवाक्षः_LOOK;
        गन्तव्यम्_Be_Win(गवाक्षः)->RemoveFromSubset(गन्तव्यम्_Be_Win(गवाक्षः->parent));
        गन्तव्यम्_Be_Win(गवाक्षः)->समुच्चयः_Look(look);
        गन्तव्यम्_Be_Win(गवाक्षः)->समुच्चयः_Feel(B_प्रसामान्यम्_गवाक्षः_FEEL);
    }

    प्रत्यागम सत्य;
}

शून्य HAIKU_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः)
{
    गन्तव्यम्_Be_Win(गवाक्षः)->तालकम्_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(गन्तव्यम्_Be_Win(गवाक्षः));
    गन्तव्यम्_Be_Win(गवाक्षः)->Quit();
    गवाक्षः->आन्तरिकम् = रिक्त;
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_HAIKU

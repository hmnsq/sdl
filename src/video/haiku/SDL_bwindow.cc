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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_HAIKU
#అన్తర్భావ "../SDL_sysvideo.h"

#అన్తర్భావ "SDL_BWin.h"
#అన్తర్భావ <new>

// Define a path to window's BWIN data
#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

స్థిర SDL_INLINE SDL_BWin *గమ్యం_Be_Win(SDL_కిటికీ *కిటికీ)
{
    తిరిగి (SDL_BWin *)(కిటికీ->అంతర్గత);
}

స్థిర SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    తిరిగి SDL_Looper;
}

స్థిర తార్కిక Init_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    uint32 flags = 0;
    కిటికీ_look look = B_TITLED_కిటికీ_LOOK;

    BRect bounds(
        కిటికీ->x,
        కిటికీ->y,
        కిటికీ->x + కిటికీ->w - 1,    //BeWindows have an off-by-one px w/h thing
        కిటికీ->y + కిటికీ->h - 1
    );

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) {
        // TODO: Add support for this flag
    }
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        // TODO: Add support for this flag
    }
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE)) {
        flags |= B_NOT_RESIZABLE | B_NOT_ZOOMABLE;
    }
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_BORDERLESS) {
        look = B_NO_BORDER_కిటికీ_LOOK;
    }

    SDL_BWin *bwin = కొత్త(std::nothrow) SDL_BWin(bounds, look, flags);
    ఒకవేళ (!bwin) {
        తిరిగి అబద్ధం;
    }

    కిటికీ->అంతర్గత = (SDL_కిటికీ_దత్తాంశం *)bwin;
    int32 winID = _GetBeLooper()->GetID(కిటికీ);
    bwin->సమితి_ID(winID);

    తిరిగి నిజం;
}

తార్కిక HAIKU_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    ఒకవేళ (!Init_కిటికీ(_this, కిటికీ, create_props)) {
        తిరిగి అబద్ధం;
    }

    // Start window loop
    గమ్యం_Be_Win(కిటికీ)->Show();
    తిరిగి నిజం;
}

శూన్య HAIKU_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_సమితి_TITLE);
    సందేశం_2.కూడు_String("window-title", కిటికీ->title);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

తార్కిక HAIKU_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_MOVE_కిటికీ);
    సందేశం_2.కూడు_Int32("window-x", కిటికీ->pending.x);
    సందేశం_2.కూడు_Int32("window-y", కిటికీ->pending.y);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
    తిరిగి నిజం;
}

శూన్య HAIKU_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_RESIZE_కిటికీ);
    సందేశం_2.కూడు_Int32("window-w", కిటికీ->pending.w - 1);
    సందేశం_2.కూడు_Int32("window-h", కిటికీ->pending.h - 1);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, తార్కిక bordered)
{
    BMessage సందేశం_2(BWIN_సమితి_BORDERED);
    సందేశం_2.కూడు_Bool("window-border", bordered != అబద్ధం);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, తార్కిక resizable)
{
    BMessage సందేశం_2(BWIN_సమితి_RESIZABLE);
    సందేశం_2.కూడు_Bool("window-resizable", resizable != అబద్ధం);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_SHOW_కిటికీ);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_HIDE_కిటికీ);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_SHOW_కిటికీ);    // Activate this window and move to front
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_MAXIMIZE_కిటికీ);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_MINIMIZE_కిటికీ);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

శూన్య HAIKU_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_RESTORE_కిటికీ);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

SDL_Fullscreen_ఫలితం HAIKU_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay * display, SDL_FullscreenOp fullscreen)
{
    // Haiku tracks all video display information
    BMessage సందేశం_2(BWIN_FULLSCREEN);
    సందేశం_2.కూడు_Bool("fullscreen", !!fullscreen);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
    తిరిగి SDL_FULLSCREEN_SUCCEEDED;
}


శూన్య HAIKU_సమితి_కిటికీ_Minimum_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    BMessage సందేశం_2(BWIN_MINIMUM_కొలత_కిటికీ);
    సందేశం_2.కూడు_Int32("window-w", కిటికీ->w -1);
    సందేశం_2.కూడు_Int32("window-h", కిటికీ->h -1);
    గమ్యం_Be_Win(కిటికీ)->Post_సందేశం(&సందేశం_2);
}

తార్కిక HAIKU_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, తార్కిక grabbed)
{
    // TODO: Implement this!
    తిరిగి SDL_Unsupported();
}

తార్కిక HAIKU_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, SDL_కిటికీ *మాతృ)
{
    తిరిగి నిజం;
}

తార్కిక HAIKU_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, తార్కిక modal)
{
    ఒకవేళ (modal) {
        గమ్యం_Be_Win(కిటికీ)->సమితి_Look(B_MODAL_కిటికీ_LOOK);
        గమ్యం_Be_Win(కిటికీ)->సమితి_Feel(B_MODAL_SUBSET_కిటికీ_FEEL);
        గమ్యం_Be_Win(కిటికీ)->కూడు_గమ్యం_Subset(గమ్యం_Be_Win(కిటికీ->మాతృ));
    } లేకపోతే {
        కిటికీ_look look = (కిటికీ->flags & SDL_కిటికీ_BORDERLESS) ? B_NO_BORDER_కిటికీ_LOOK : B_TITLED_కిటికీ_LOOK;
        గమ్యం_Be_Win(కిటికీ)->RemoveFromSubset(గమ్యం_Be_Win(కిటికీ->మాతృ));
        గమ్యం_Be_Win(కిటికీ)->సమితి_Look(look);
        గమ్యం_Be_Win(కిటికీ)->సమితి_Feel(B_సాధారణ_కిటికీ_FEEL);
    }

    తిరిగి నిజం;
}

శూన్య HAIKU_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ)
{
    గమ్యం_Be_Win(కిటికీ)->తాళం_Looper();    // This MUST be locked
    _GetBeLooper()->ClearID(గమ్యం_Be_Win(కిటికీ));
    గమ్యం_Be_Win(కిటికీ)->Quit();
    కిటికీ->అంతర్గత = ఖాళీ;
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_HAIKU

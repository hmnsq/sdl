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
#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_HAIKU

#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ <Url.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "SDL_bkeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_bwindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_bclipboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_bvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_bopengl.h"
#ಅನ್ತರ್ಭಾವ "SDL_bmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_bframebuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_bevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_bmessagebox.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

ಸ್ಥಿರ SDL_INLINE SDL_BWin *ಗಮ್ಯ_Be_Win(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ) {
    ಹಿಂತಿರುಗಿ (SDL_BWin *)(ಕಿಟಕಿ->ಆಂತರಿಕ);
}

ಸ್ಥಿರ SDL_VideoDevice * HAIKU_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));

    device->ಆಂತರಿಕ = ಖಾಲಿ; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->ಗಣ_Display_ಬಹುಲಕ = HAIKU_ಗಣ_Display_ಬಹುಲಕ;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = HAIKU_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Position = HAIKU_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = HAIKU_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Show_ಕಿಟಕಿ = HAIKU_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = HAIKU_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = HAIKU_Raise_ಕಿಟಕಿ;
    device->Maximize_ಕಿಟಕಿ = HAIKU_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = HAIKU_Minimize_ಕಿಟಕಿ;
    device->Restore_ಕಿಟಕಿ = HAIKU_Restore_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Bordered = HAIKU_ಗಣ_ಕಿಟಕಿ_Bordered;
    device->ಗಣ_ಕಿಟಕಿ_Resizable = HAIKU_ಗಣ_ಕಿಟಕಿ_Resizable;
    device->ಗಣ_ಕಿಟಕಿ_Fullscreen = HAIKU_ಗಣ_ಕಿಟಕಿ_Fullscreen;
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Grab = HAIKU_ಗಣ_ಕಿಟಕಿ_Mouse_Grab;
    device->ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ = HAIKU_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ;
    device->ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ = HAIKU_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ;
    device->ಗಣ_ಕಿಟಕಿ_Modal = HAIKU_ಗಣ_ಕಿಟಕಿ_Modal;
    device->Destroy_ಕಿಟಕಿ = HAIKU_Destroy_ಕಿಟಕಿ;
    device->Create_ಕಿಟಕಿ_Framebuffer = HAIKU_Create_ಕಿಟಕಿ_Framebuffer;
    device->Update_ಕಿಟಕಿ_Framebuffer = HAIKU_Update_ಕಿಟಕಿ_Framebuffer;
    device->Destroy_ಕಿಟಕಿ_Framebuffer = HAIKU_Destroy_ಕಿಟಕಿ_Framebuffer;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    device->GL_ತುಂಬು_Library = HAIKU_GL_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = HAIKU_GL_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = HAIKU_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = HAIKU_GL_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = HAIKU_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#ಆದರೆ_ಅಂತ್ಯ

    device->ಗಣ_Clipboard_ಪಠ್ಯ = HAIKU_ಗಣ_Clipboard_ಪಠ್ಯ;
    device->Get_Clipboard_ಪಠ್ಯ = HAIKU_Get_Clipboard_ಪಠ್ಯ;
    device->Has_Clipboard_ಪಠ್ಯ = HAIKU_Has_Clipboard_ಪಠ್ಯ;

    device->ಬಿಡುಗಡೆ = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_Show_ಸಂದೇಶ_Box,
    ಸುಳ್ಳು
};

ಶೂನ್ಯ HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    BCursor *cursor;
};

ಸ್ಥಿರ SDL_Cursor *HAIKU_Create_Cursor_And_ದತ್ತಾಂಶ(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
        ಆದರೆ (!ದತ್ತಾಂಶ) {
            SDL_free(cursor);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        ದತ್ತಾಂಶ->cursor = bcursor;
        cursor->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    }
    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    ಆಯ್ಕೆ(id)
    {
        #ವ್ಯಾಖ್ಯಾನಿಸು CURSORCASE(sdlname, bname) ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; ನಿಲ್ಲಿಸು
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(ಪಠ್ಯ_2, I_BEAM);
        CURSORCASE(WAIT, ಪ್ರಗತಿ);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(ಪ್ರಗತಿ, ಪ್ರಗತಿ);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(ಸೂಚಕ, FOLLOW_LINK);
        CURSORCASE(NW_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(N_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(NE_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(E_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(SE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(S_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(SW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(W_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(CONTEXT_MENU, CONTEXT_MENU);
        CURSORCASE(HELP, HELP);
        CURSORCASE(CELL, CROSS_HAIR);
        CURSORCASE(VERTICAL_ಪಠ್ಯ, I_BEAM_HORIZONTAL);
        CURSORCASE(ALIAS, CREATE_LINK);
        CURSORCASE(COPY, COPY);
        CURSORCASE(NO_DROP, NOT_ALLOWED);
        CURSORCASE(GRAB, GRAB);
        CURSORCASE(GRABBING, GRABBING);
        CURSORCASE(ಲಂಬಸಾಲು_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(ಅಡ್ಡಸಾಲು_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_ಒಳ, ZOOM_ಒಳ);
        CURSORCASE(ZOOM_ಹೊರಹೋಗು, ZOOM_ಹೊರಹೋಗು);
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CURSORCASE
        ಪೂರ್ವನಿಯೋಜಿತ:
            SDL_assert(0);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ HAIKU_Create_Cursor_And_ದತ್ತಾಂಶ(ಹೊಸ BCursor(cursorId));
}

ಸ್ಥಿರ SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಹಿಂತಿರುಗಿ HAIKU_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = cursor->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ) {
        ಅಳಿಸು ದತ್ತಾಂಶ->cursor;
    }
    SDL_free(ದತ್ತಾಂಶ);
    SDL_free(cursor);
}

ಸ್ಥಿರ SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ಆದರೆ (!converted) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

	BBitmap *cursorBitmap = ಹೊಸ BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->ಗಣ_ಬಿಟ್ಟುಗಳು(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    ಹಿಂತಿರುಗಿ HAIKU_Create_Cursor_And_ದತ್ತಾಂಶ(ಹೊಸ BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	ಆದರೆ (!mouse) {
		ಹಿಂತಿರುಗಿ ನಿಜ;
	}

	ಆದರೆ (cursor) {
		BCursor *hCursor = cursor->ಆಂತರಿಕ->cursor;
		be_app->ಗಣ_Cursor(hCursor);
	} ಇಲ್ಲದಿದ್ದರೆ {
		BCursor *hCursor = ಹೊಸ BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->ಗಣ_Cursor(hCursor);
		ಅಳಿಸು hCursor;
	}

	ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ HAIKU_ಗಣ_Relative_Mouse_ಬಹುಲಕ(ತಾರ್ಕಿಕ enabled)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = SDL_GetMouseFocus();
    ಆದರೆ (!ಕಿಟಕಿ) {
      ಹಿಂತಿರುಗಿ ನಿಜ;
    }

	SDL_BWin *bewin = ಗಮ್ಯ_Be_Win(ಕಿಟಕಿ);
	BView *_SDL_View = bewin->GetGLView();
	ಆದರೆ (!_SDL_View) {
		_SDL_View = bewin->GetView();
		ಆದರೆ (!_SDL_View)
			ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

	bewin->ಬೀಗ();
	ಆದರೆ (enabled)
		_SDL_View->ಗಣ_Event_ಮುಖವಾಡ(B_ಸೂಚಕ_EVENTS, B_NO_ಸೂಚಕ_HISTORY);
	ಇಲ್ಲದಿದ್ದರೆ
		_SDL_View->ಗಣ_Event_ಮುಖವಾಡ(0, 0);
	bewin->Unlock();

    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಸ್ಥಿರ ಶೂನ್ಯ HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	ಆದರೆ (!mouse) {
		ಹಿಂತಿರುಗಿ;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->ಗಣ_Relative_Mouse_ಬಹುಲಕ = HAIKU_ಗಣ_Relative_Mouse_ಬಹುಲಕ;

	SDL_ಗಣ_Default_Cursor(HAIKU_CreateDefaultCursor());
}

ತಾರ್ಕಿಕ HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    ಆದರೆ (!SDL_InitBeApp()) {
        ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_ಕೂಡಿಸು_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ಖಾಲಿ);
    SDL_ಕೂಡಿಸು_Mouse(SDL_DEFAULT_MOUSE_ID, ಖಾಲಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_ತುಂಬು_Library(_this, ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ

    // We're done!
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಶೂನ್ಯ HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
ಬಾಹ್ಯ "C"
ತಾರ್ಕಿಕ HAIKU_OpenURL(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *url)
{
#ಆದರೆ B_HAIKU_ಆವೃತ್ತಿ <= B_HAIKU_ಆವೃತ್ತಿ_1_BETA_5
    BUrl burl(url);
#ಇಲ್ಲದಿದ್ದರೆ
    BUrl burl(url, ನಿಜ);
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿರಾಂಕ ಸ್ಥಿತಿ_t rc = burl.OpenWithPreferredApplication(ಸುಳ್ಳು);
    ಆದರೆ (rc != B_NO_ERROR) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("URL open failed (err=%d)", (ಪೂರ್ಣಾಂಕ)rc);
    }
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_HAIKU

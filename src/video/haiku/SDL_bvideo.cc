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

#ifdef SDL_VIDEO_DRIVER_HAIKU

#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"
#ಅನ್ತರ್ಭಾವ <Url.h>

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif

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

ಸ್ಥಿರ SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window) {
    ಪ್ರತ್ಯಾಗಮ (SDL_BWin *)(window->internal);
}

ಸ್ಥಿರ SDL_VideoDevice * HAIKU_CreateDevice(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));

    device->internal = ರಿಕ್ತ; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->SetDisplayMode = HAIKU_SetDisplayMode;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_CreateWindow;
    device->SetWindowTitle = HAIKU_SetWindowTitle;
    device->SetWindowPosition = HAIKU_SetWindowPosition;
    device->SetWindowSize = HAIKU_SetWindowSize;
    device->ShowWindow = HAIKU_ShowWindow;
    device->HideWindow = HAIKU_HideWindow;
    device->RaiseWindow = HAIKU_RaiseWindow;
    device->MaximizeWindow = HAIKU_MaximizeWindow;
    device->MinimizeWindow = HAIKU_MinimizeWindow;
    device->RestoreWindow = HAIKU_RestoreWindow;
    device->SetWindowBordered = HAIKU_SetWindowBordered;
    device->SetWindowResizable = HAIKU_SetWindowResizable;
    device->SetWindowFullscreen = HAIKU_SetWindowFullscreen;
    device->SetWindowMouseGrab = HAIKU_SetWindowMouseGrab;
    device->SetWindowMinimumSize = HAIKU_SetWindowMinimumSize;
    device->SetWindowParent = HAIKU_SetWindowParent;
    device->SetWindowModal = HAIKU_SetWindowModal;
    device->DestroyWindow = HAIKU_DestroyWindow;
    device->CreateWindowFramebuffer = HAIKU_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = HAIKU_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = HAIKU_DestroyWindowFramebuffer;

#ifdef SDL_VIDEO_OPENGL
    device->GL_LoadLibrary = HAIKU_GL_LoadLibrary;
    device->GL_GetProcAddress = HAIKU_GL_GetProcAddress;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_SetSwapInterval = HAIKU_GL_SetSwapInterval;
    device->GL_GetSwapInterval = HAIKU_GL_GetSwapInterval;
    device->GL_SwapWindow = HAIKU_GL_SwapWindow;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#endif

    device->SetClipboardText = HAIKU_SetClipboardText;
    device->GetClipboardText = HAIKU_GetClipboardText;
    device->HasClipboardText = HAIKU_HasClipboardText;

    device->ಮುಕ್ತ = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ಪ್ರತ್ಯಾಗಮ device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_ShowMessageBox,
    ಅಸತ್ಯ
};

ಶೂನ್ಯ HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ಸಂರಚನಾ SDL_CursorData
{
    BCursor *cursor;
};

ಸ್ಥಿರ SDL_Cursor *HAIKU_CreateCursorAndData(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಪರಿಮಾಣ(*cursor));
    ಯದಿ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ಪರಿಮಾಣ(*data));
        ಯದಿ (!data) {
            SDL_free(cursor);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        data->cursor = bcursor;
        cursor->internal = data;
    }
    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    ವಿಕಲ್ಪ(id)
    {
        #define CURSORCASE(sdlname, bname) ಪಕ್ಷ SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; ಭಙ್ಗ
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(TEXT, I_BEAM);
        CURSORCASE(WAIT, PROGRESS);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(PROGRESS, PROGRESS);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(POINTER, FOLLOW_LINK);
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
        CURSORCASE(VERTICAL_TEXT, I_BEAM_HORIZONTAL);
        CURSORCASE(ALIAS, CREATE_LINK);
        CURSORCASE(COPY, COPY);
        CURSORCASE(NO_DROP, NOT_ALLOWED);
        CURSORCASE(GRAB, GRAB);
        CURSORCASE(GRABBING, GRABBING);
        CURSORCASE(COL_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(ROW_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_IN, ZOOM_IN);
        CURSORCASE(ZOOM_OUT, ZOOM_OUT);
        #undef CURSORCASE
        ಸ್ವಭಾವ:
            SDL_assert(0);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ HAIKU_CreateCursorAndData(ನೂತನ BCursor(cursorId));
}

ಸ್ಥಿರ SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಪ್ರತ್ಯಾಗಮ HAIKU_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *data = cursor->internal;

    ಯದಿ (data) {
        delete data->cursor;
    }
    SDL_free(data);
    SDL_free(cursor);
}

ಸ್ಥಿರ SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ಯದಿ (!converted) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

	BBitmap *cursorBitmap = ನೂತನ BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->SetBits(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    ಪ್ರತ್ಯಾಗಮ HAIKU_CreateCursorAndData(ನೂತನ BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	ಯದಿ (!mouse) {
		ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}

	ಯದಿ (cursor) {
		BCursor *hCursor = cursor->internal->cursor;
		be_app->SetCursor(hCursor);
	} ಅನ್ಯಥಾ {
		BCursor *hCursor = ನೂತನ BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->SetCursor(hCursor);
		delete hCursor;
	}

	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ HAIKU_SetRelativeMouseMode(ತಾರ್ಕಿಕ enabled)
{
    SDL_Window *window = SDL_GetMouseFocus();
    ಯದಿ (!window) {
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

	SDL_BWin *bewin = _ToBeWin(window);
	BView *_SDL_View = bewin->GetGLView();
	ಯದಿ (!_SDL_View) {
		_SDL_View = bewin->GetView();
		ಯದಿ (!_SDL_View)
			ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

	bewin->Lock();
	ಯದಿ (enabled)
		_SDL_View->SetEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	ಅನ್ಯಥಾ
		_SDL_View->SetEventMask(0, 0);
	bewin->Unlock();

    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಸ್ಥಿರ ಶೂನ್ಯ HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	ಯದಿ (!mouse) {
		ಪ್ರತ್ಯಾಗಮ;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->SetRelativeMouseMode = HAIKU_SetRelativeMouseMode;

	SDL_SetDefaultCursor(HAIKU_CreateDefaultCursor());
}

ತಾರ್ಕಿಕ HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    ಯದಿ (!SDL_InitBeApp()) {
        ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ರಿಕ್ತ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ರಿಕ್ತ);

#ifdef SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_LoadLibrary(_this, ರಿಕ್ತ);
#endif

    // We're done!
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
ಬಾಹ್ಯ "C"
ತಾರ್ಕಿಕ HAIKU_OpenURL(ಧ್ರುವ ವರ್ಣ *url)
{
#ಯದಿ B_HAIKU_VERSION <= B_HAIKU_VERSION_1_BETA_5
    BUrl burl(url);
#ಅನ್ಯಥಾ
    BUrl burl(url, ಸತ್ಯ);
#endif
    ಧ್ರುವ status_t rc = burl.OpenWithPreferredApplication(ಅಸತ್ಯ);
    ಯದಿ (rc != B_NO_ERROR) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("URL open failed (err=%d)", (ಪೂರ್ಣಾಙ್ಕ)rc);
    }
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

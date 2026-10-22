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

#അന്തര്ഭാവ "SDL_internal.h"
#അന്തര്ഭാവ "../../core/haiku/SDL_BApp.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#അന്തര്ഭാവ "SDL_BWin.h"
#അന്തര്ഭാവ <Url.h>

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

#അന്തര്ഭാവ "SDL_bkeyboard.h"
#അന്തര്ഭാവ "SDL_bwindow.h"
#അന്തര്ഭാവ "SDL_bclipboard.h"
#അന്തര്ഭാവ "SDL_bvideo.h"
#അന്തര്ഭാവ "SDL_bopengl.h"
#അന്തര്ഭാവ "SDL_bmodes.h"
#അന്തര്ഭാവ "SDL_bframebuffer.h"
#അന്തര്ഭാവ "SDL_bevents.h"
#അന്തര്ഭാവ "SDL_bmessagebox.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"

സ്ഥിതം SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window) {
    തിരികെ (SDL_BWin *)(window->internal);
}

സ്ഥിതം SDL_VideoDevice * HAIKU_CreateDevice(ശൂന്യം)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));

    device->internal = ശൂന്യ; /* FIXME: Is this the cause of some of the
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

    device->സ്വതന്ത്രം = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    തിരികെ device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_ShowMessageBox,
    അസത്യം
};

ശൂന്യം HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ഘടന SDL_CursorData
{
    BCursor *cursor;
};

സ്ഥിതം SDL_Cursor *HAIKU_CreateCursorAndData(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*data));
        എങ്കിൽ (!data) {
            SDL_free(cursor);
            തിരികെ ശൂന്യ;
        }
        data->cursor = bcursor;
        cursor->internal = data;
    }
    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    തിരഞ്ഞെടുപ്പ്(id)
    {
        #define CURSORCASE(sdlname, bname) അവസ്ഥ SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; നിർത്തുക
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
        സ്ഥിരസ്ഥിതി:
            SDL_assert(0);
            തിരികെ ശൂന്യ;
    }

    തിരികെ HAIKU_CreateCursorAndData(പുതിയ BCursor(cursorId));
}

സ്ഥിതം SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    തിരികെ HAIKU_CreateSystemCursor(id);
}

സ്ഥിതം ശൂന്യം HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *data = cursor->internal;

    എങ്കിൽ (data) {
        delete data->cursor;
    }
    SDL_free(data);
    SDL_free(cursor);
}

സ്ഥിതം SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    എങ്കിൽ (!converted) {
        തിരികെ ശൂന്യ;
    }

	BBitmap *cursorBitmap = പുതിയ BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->SetBits(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    തിരികെ HAIKU_CreateCursorAndData(പുതിയ BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

സ്ഥിതം തർക്കം HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	എങ്കിൽ (!mouse) {
		തിരികെ സത്യം;
	}

	എങ്കിൽ (cursor) {
		BCursor *hCursor = cursor->internal->cursor;
		be_app->SetCursor(hCursor);
	} അല്ലെങ്കിൽ {
		BCursor *hCursor = പുതിയ BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->SetCursor(hCursor);
		delete hCursor;
	}

	തിരികെ സത്യം;
}

സ്ഥിതം തർക്കം HAIKU_SetRelativeMouseMode(തർക്കം enabled)
{
    SDL_Window *window = SDL_GetMouseFocus();
    എങ്കിൽ (!window) {
      തിരികെ സത്യം;
    }

	SDL_BWin *bewin = _ToBeWin(window);
	BView *_SDL_View = bewin->GetGLView();
	എങ്കിൽ (!_SDL_View) {
		_SDL_View = bewin->GetView();
		എങ്കിൽ (!_SDL_View)
			തിരികെ അസത്യം;
	}

	bewin->Lock();
	എങ്കിൽ (enabled)
		_SDL_View->SetEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	അല്ലെങ്കിൽ
		_SDL_View->SetEventMask(0, 0);
	bewin->Unlock();

    തിരികെ സത്യം;
}

സ്ഥിതം ശൂന്യം HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	എങ്കിൽ (!mouse) {
		തിരികെ;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->SetRelativeMouseMode = HAIKU_SetRelativeMouseMode;

	SDL_SetDefaultCursor(HAIKU_CreateDefaultCursor());
}

തർക്കം HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    എങ്കിൽ (!SDL_InitBeApp()) {
        തിരികെ അസത്യം;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, ശൂന്യ);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, ശൂന്യ);

#ifdef SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_LoadLibrary(_this, ശൂന്യ);
#endif

    // We're done!
    തിരികെ സത്യം;
}

ശൂന്യം HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
ബാഹ്യ "C"
തർക്കം HAIKU_OpenURL(സ്ഥിരം അക്ഷരം *url)
{
#എങ്കിൽ B_HAIKU_VERSION <= B_HAIKU_VERSION_1_BETA_5
    BUrl burl(url);
#അല്ലെങ്കിൽ
    BUrl burl(url, സത്യം);
#endif
    സ്ഥിരം status_t rc = burl.OpenWithPreferredApplication(അസത്യം);
    എങ്കിൽ (rc != B_NO_ERROR) {
        തിരികെ SDL_SetError("URL open failed (err=%d)", (പൂർണ്ണസംഖ്യ)rc);
    }
    തിരികെ സത്യം;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

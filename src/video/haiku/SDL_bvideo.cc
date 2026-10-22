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
#অন্তর্ভাৱ "../../core/haiku/SDL_BApp.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#অন্তর্ভাৱ "SDL_BWin.h"
#অন্তর্ভাৱ <Url.h>

#ifdef __cplusplus
বাহ্য "C" {
#endif

#অন্তর্ভাৱ "SDL_bkeyboard.h"
#অন্তর্ভাৱ "SDL_bwindow.h"
#অন্তর্ভাৱ "SDL_bclipboard.h"
#অন্তর্ভাৱ "SDL_bvideo.h"
#অন্তর্ভাৱ "SDL_bopengl.h"
#অন্তর্ভাৱ "SDL_bmodes.h"
#অন্তর্ভাৱ "SDL_bframebuffer.h"
#অন্তর্ভাৱ "SDL_bevents.h"
#অন্তর্ভাৱ "SDL_bmessagebox.h"
#অন্তর্ভাৱ "../../events/SDL_keyboard_c.h"
#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"

স্থির SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window) {
    ঘূৰাই (SDL_BWin *)(window->internal);
}

স্থির SDL_VideoDevice * HAIKU_CreateDevice(শূন্য)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, পরিমাণ(SDL_VideoDevice));

    device->internal = রিক্ত; /* FIXME: Is this the cause of some of the
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

    device->মুক্ত = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ঘূৰাই device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_ShowMessageBox,
    মিছা
};

শূন্য HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

সংরচনা SDL_CursorData
{
    BCursor *cursor;
};

স্থির SDL_Cursor *HAIKU_CreateCursorAndData(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, পরিমাণ(*cursor));
    যদি (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, পরিমাণ(*data));
        যদি (!data) {
            SDL_free(cursor);
            ঘূৰাই রিক্ত;
        }
        data->cursor = bcursor;
        cursor->internal = data;
    }
    ঘূৰাই cursor;
}

স্থির SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    ৱিকল্প(id)
    {
        #define CURSORCASE(sdlname, bname) পক্ষ SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; ভঙ্গ
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
        স্ৱভাৱ:
            SDL_assert(0);
            ঘূৰাই রিক্ত;
    }

    ঘূৰাই HAIKU_CreateCursorAndData(নূতন BCursor(cursorId));
}

স্থির SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ঘূৰাই HAIKU_CreateSystemCursor(id);
}

স্থির শূন্য HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *data = cursor->internal;

    যদি (data) {
        delete data->cursor;
    }
    SDL_free(data);
    SDL_free(cursor);
}

স্থির SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    যদি (!converted) {
        ঘূৰাই রিক্ত;
    }

	BBitmap *cursorBitmap = নূতন BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->SetBits(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    ঘূৰাই HAIKU_CreateCursorAndData(নূতন BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

স্থির তার্কিক HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	যদি (!mouse) {
		ঘূৰাই সঁচা;
	}

	যদি (cursor) {
		BCursor *hCursor = cursor->internal->cursor;
		be_app->SetCursor(hCursor);
	} অন্যথা {
		BCursor *hCursor = নূতন BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->SetCursor(hCursor);
		delete hCursor;
	}

	ঘূৰাই সঁচা;
}

স্থির তার্কিক HAIKU_SetRelativeMouseMode(তার্কিক enabled)
{
    SDL_Window *window = SDL_GetMouseFocus();
    যদি (!window) {
      ঘূৰাই সঁচা;
    }

	SDL_BWin *bewin = _ToBeWin(window);
	BView *_SDL_View = bewin->GetGLView();
	যদি (!_SDL_View) {
		_SDL_View = bewin->GetView();
		যদি (!_SDL_View)
			ঘূৰাই মিছা;
	}

	bewin->Lock();
	যদি (enabled)
		_SDL_View->SetEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	অন্যথা
		_SDL_View->SetEventMask(0, 0);
	bewin->Unlock();

    ঘূৰাই সঁচা;
}

স্থির শূন্য HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	যদি (!mouse) {
		ঘূৰাই;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->SetRelativeMouseMode = HAIKU_SetRelativeMouseMode;

	SDL_SetDefaultCursor(HAIKU_CreateDefaultCursor());
}

তার্কিক HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    যদি (!SDL_InitBeApp()) {
        ঘূৰাই মিছা;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, রিক্ত);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, রিক্ত);

#ifdef SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_LoadLibrary(_this, রিক্ত);
#endif

    // We're done!
    ঘূৰাই সঁচা;
}

শূন্য HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
বাহ্য "C"
তার্কিক HAIKU_OpenURL(ধ্রুৱ ৱর্ণ *url)
{
#যদি B_HAIKU_VERSION <= B_HAIKU_VERSION_1_BETA_5
    BUrl burl(url);
#অন্যথা
    BUrl burl(url, সঁচা);
#endif
    ধ্রুৱ status_t rc = burl.OpenWithPreferredApplication(মিছা);
    যদি (rc != B_NO_ERROR) {
        ঘূৰাই SDL_SetError("URL open failed (err=%d)", (পূর্ণাঙ্ক)rc);
    }
    ঘূৰাই সঁচা;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

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
#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#अन्तर्भाव "SDL_BWin.h"
#अन्तर्भाव <Url.h>

#ifdef __cplusplus
बाह्य "C" {
#endif

#अन्तर्भाव "SDL_bkeyboard.h"
#अन्तर्भाव "SDL_bwindow.h"
#अन्तर्भाव "SDL_bclipboard.h"
#अन्तर्भाव "SDL_bvideo.h"
#अन्तर्भाव "SDL_bopengl.h"
#अन्तर्भाव "SDL_bmodes.h"
#अन्तर्भाव "SDL_bframebuffer.h"
#अन्तर्भाव "SDL_bevents.h"
#अन्तर्भाव "SDL_bmessagebox.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

स्थिर SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window) {
    परत (SDL_BWin *)(window->internal);
}

स्थिर SDL_VideoDevice * HAIKU_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, आकार(SDL_VideoDevice));

    device->internal = रिक्त; /* FIXME: Is this the cause of some of the
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

    device->मुक्त = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    परत device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_ShowMessageBox,
    असत्य
};

शून्य HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

संरचना SDL_CursorData
{
    BCursor *cursor;
};

स्थिर SDL_Cursor *HAIKU_CreateCursorAndData(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, आकार(*cursor));
    जर (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, आकार(*data));
        जर (!data) {
            SDL_free(cursor);
            परत रिक्त;
        }
        data->cursor = bcursor;
        cursor->internal = data;
    }
    परत cursor;
}

स्थिर SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    निवड(id)
    {
        #define CURSORCASE(sdlname, bname) स्थिती SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; थांबा
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
        पूर्वनिर्धारित:
            SDL_assert(0);
            परत रिक्त;
    }

    परत HAIKU_CreateCursorAndData(नवीन BCursor(cursorId));
}

स्थिर SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    परत HAIKU_CreateSystemCursor(id);
}

स्थिर शून्य HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *data = cursor->internal;

    जर (data) {
        delete data->cursor;
    }
    SDL_free(data);
    SDL_free(cursor);
}

स्थिर SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    जर (!converted) {
        परत रिक्त;
    }

	BBitmap *cursorBitmap = नवीन BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->SetBits(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    परत HAIKU_CreateCursorAndData(नवीन BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

स्थिर तार्किक HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	जर (!mouse) {
		परत सत्य;
	}

	जर (cursor) {
		BCursor *hCursor = cursor->internal->cursor;
		be_app->SetCursor(hCursor);
	} अन्यथा {
		BCursor *hCursor = नवीन BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->SetCursor(hCursor);
		delete hCursor;
	}

	परत सत्य;
}

स्थिर तार्किक HAIKU_SetRelativeMouseMode(तार्किक enabled)
{
    SDL_Window *window = SDL_GetMouseFocus();
    जर (!window) {
      परत सत्य;
    }

	SDL_BWin *bewin = _ToBeWin(window);
	BView *_SDL_View = bewin->GetGLView();
	जर (!_SDL_View) {
		_SDL_View = bewin->GetView();
		जर (!_SDL_View)
			परत असत्य;
	}

	bewin->Lock();
	जर (enabled)
		_SDL_View->SetEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	अन्यथा
		_SDL_View->SetEventMask(0, 0);
	bewin->Unlock();

    परत सत्य;
}

स्थिर शून्य HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	जर (!mouse) {
		परत;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->SetRelativeMouseMode = HAIKU_SetRelativeMouseMode;

	SDL_SetDefaultCursor(HAIKU_CreateDefaultCursor());
}

तार्किक HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    जर (!SDL_InitBeApp()) {
        परत असत्य;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, रिक्त);

#ifdef SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_LoadLibrary(_this, रिक्त);
#endif

    // We're done!
    परत सत्य;
}

शून्य HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
बाह्य "C"
तार्किक HAIKU_OpenURL(स्थिरांक अक्षर *url)
{
#जर B_HAIKU_VERSION <= B_HAIKU_VERSION_1_BETA_5
    BUrl burl(url);
#अन्यथा
    BUrl burl(url, सत्य);
#endif
    स्थिरांक status_t rc = burl.OpenWithPreferredApplication(असत्य);
    जर (rc != B_NO_ERROR) {
        परत SDL_SetError("URL open failed (err=%d)", (पूर्णांक)rc);
    }
    परत सत्य;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

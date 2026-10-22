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

#समावेश "SDL_internal.h"
#समावेश "../../core/haiku/SDL_BApp.h"

#अगर_घोषित SDL_VIDEO_DRIVER_HAIKU

#समावेश "SDL_BWin.h"
#समावेश <Url.h>

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

#समावेश "SDL_bkeyboard.h"
#समावेश "SDL_bwindow.h"
#समावेश "SDL_bclipboard.h"
#समावेश "SDL_bvideo.h"
#समावेश "SDL_bopengl.h"
#समावेश "SDL_bmodes.h"
#समावेश "SDL_bframebuffer.h"
#समावेश "SDL_bevents.h"
#समावेश "SDL_bmessagebox.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_mouse_c.h"

अटल SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window) {
    वापस (SDL_BWin *)(window->internal);
}

अटल SDL_VideoDevice * HAIKU_CreateDevice(व्योम)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, माप(SDL_VideoDevice));

    device->internal = शून्य; /* FIXME: Is this the cause of some of the
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
    device->Set_Window_आकार = HAIKU_Set_Window_आकार;
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
    device->Set_Window_Minimum_आकार = HAIKU_Set_Window_Minimum_आकार;
    device->SetWindowParent = HAIKU_SetWindowParent;
    device->SetWindowModal = HAIKU_SetWindowModal;
    device->DestroyWindow = HAIKU_DestroyWindow;
    device->CreateWindowFramebuffer = HAIKU_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = HAIKU_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = HAIKU_DestroyWindowFramebuffer;

#अगर_घोषित SDL_VIDEO_OPENGL
    device->GL_LoadLibrary = HAIKU_GL_LoadLibrary;
    device->GL_GetProcAddress = HAIKU_GL_GetProcAddress;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_SetSwapInterval = HAIKU_GL_SetSwapInterval;
    device->GL_GetSwapInterval = HAIKU_GL_GetSwapInterval;
    device->GL_SwapWindow = HAIKU_GL_SwapWindow;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#पूर्ण_अगर

    device->SetClipboardText = HAIKU_SetClipboardText;
    device->GetClipboardText = HAIKU_GetClipboardText;
    device->HasClipboardText = HAIKU_HasClipboardText;

    device->मुक्त = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    वापस device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_ShowMessageBox,
    false
};

व्योम HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

काष्ठा SDL_Cursor_तथ्य
{
    BCursor *cursor;
};

अटल SDL_Cursor *HAIKU_Create_Cursor_And_तथ्य(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, माप(*cursor));
    अगर (cursor) {
        SDL_Cursor_तथ्य *तथ्य = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*तथ्य));
        अगर (!तथ्य) {
            SDL_free(cursor);
            वापस शून्य;
        }
        तथ्य->cursor = bcursor;
        cursor->internal = तथ्य;
    }
    वापस cursor;
}

अटल SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    चयन(id)
    {
        #घोषणा CURSORCASE(sdlname, bname) हाल SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; अवरोध
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
        #अघोषित CURSORCASE
        शेष:
            SDL_assert(0);
            वापस शून्य;
    }

    वापस HAIKU_Create_Cursor_And_तथ्य(नया BCursor(cursorId));
}

अटल SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    वापस HAIKU_CreateSystemCursor(id);
}

अटल व्योम HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_तथ्य *तथ्य = cursor->internal;

    अगर (तथ्य) {
        मिटाओ तथ्य->cursor;
    }
    SDL_free(तथ्य);
    SDL_free(cursor);
}

अटल SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    अगर (!converted) {
        वापस शून्य;
    }

	BBitmap *cursorBitmap = नया BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->SetBits(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    वापस HAIKU_Create_Cursor_And_तथ्य(नया BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

अटल bool HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	अगर (!mouse) {
		वापस true;
	}

	अगर (cursor) {
		BCursor *hCursor = cursor->internal->cursor;
		be_app->SetCursor(hCursor);
	} अन्यथा {
		BCursor *hCursor = नया BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->SetCursor(hCursor);
		मिटाओ hCursor;
	}

	वापस true;
}

अटल bool HAIKU_SetRelativeMouseMode(bool enabled)
{
    SDL_Window *window = SDL_GetMouseFocus();
    अगर (!window) {
      वापस true;
    }

	SDL_BWin *bewin = _ToBeWin(window);
	BView *_SDL_View = bewin->GetGLView();
	अगर (!_SDL_View) {
		_SDL_View = bewin->GetView();
		अगर (!_SDL_View)
			वापस false;
	}

	bewin->Lock();
	अगर (enabled)
		_SDL_View->SetEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	अन्यथा
		_SDL_View->SetEventMask(0, 0);
	bewin->Unlock();

    वापस true;
}

अटल व्योम HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	अगर (!mouse) {
		वापस;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->SetRelativeMouseMode = HAIKU_SetRelativeMouseMode;

	SDL_SetDefaultCursor(HAIKU_CreateDefaultCursor());
}

bool HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    अगर (!SDL_InitBeApp()) {
        वापस false;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_AddKeyboard(SDL_DEFAULT_KEYBOARD_ID, शून्य);
    SDL_AddMouse(SDL_DEFAULT_MOUSE_ID, शून्य);

#अगर_घोषित SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_LoadLibrary(_this, शून्य);
#पूर्ण_अगर

    // We're done!
    वापस true;
}

व्योम HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
बाह्य "C"
bool HAIKU_OpenURL(स्थिर अक्षर *url)
{
#अगर B_HAIKU_VERSION <= B_HAIKU_VERSION_1_BETA_5
    BUrl burl(url);
#अन्यथा
    BUrl burl(url, true);
#पूर्ण_अगर
    स्थिर status_t rc = burl.OpenWithPreferredApplication(false);
    अगर (rc != B_NO_ERROR) {
        वापस SDL_SetError("URL open failed (err=%d)", (पूर्णांक)rc);
    }
    वापस true;
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU

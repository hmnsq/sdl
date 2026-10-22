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
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/haiku/SDL_BApp.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_HAIKU

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_BWin.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <Url.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bkeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bclipboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bopengl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bframebuffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bmessagebox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

ਸਥਿਰ SDL_INLINE SDL_BWin *ਮੰਜ਼ਿਲ_Be_Win(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ) {
    ਵਾਪਸ (SDL_BWin *)(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
}

ਸਥਿਰ SDL_VideoDevice * HAIKU_CreateDevice(ਖਾਲੀ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));

    device->ਅੰਦਰੂਨੀ = ਨਿਰਾ; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = HAIKU_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->Show_ਖਿੜਕੀ = HAIKU_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = HAIKU_Hide_ਖਿੜਕੀ;
    device->Raise_ਖਿੜਕੀ = HAIKU_Raise_ਖਿੜਕੀ;
    device->Maximize_ਖਿੜਕੀ = HAIKU_Maximize_ਖਿੜਕੀ;
    device->Minimize_ਖਿੜਕੀ = HAIKU_Minimize_ਖਿੜਕੀ;
    device->Restore_ਖਿੜਕੀ = HAIKU_Restore_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Bordered = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Bordered;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Resizable = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Resizable;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Modal = HAIKU_ਸੈੱਟ_ਖਿੜਕੀ_Modal;
    device->Destroy_ਖਿੜਕੀ = HAIKU_Destroy_ਖਿੜਕੀ;
    device->Create_ਖਿੜਕੀ_Framebuffer = HAIKU_Create_ਖਿੜਕੀ_Framebuffer;
    device->Update_ਖਿੜਕੀ_Framebuffer = HAIKU_Update_ਖਿੜਕੀ_Framebuffer;
    device->Destroy_ਖਿੜਕੀ_Framebuffer = HAIKU_Destroy_ਖਿੜਕੀ_Framebuffer;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    device->GL_ਲੱਦੋ_Library = HAIKU_GL_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = HAIKU_GL_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = HAIKU_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = HAIKU_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = HAIKU_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#ਜੇ_ਅੰਤ

    device->ਸੈੱਟ_Clipboard_ਪਾਠ = HAIKU_ਸੈੱਟ_Clipboard_ਪਾਠ;
    device->Get_Clipboard_ਪਾਠ = HAIKU_Get_Clipboard_ਪਾਠ;
    device->Has_Clipboard_ਪਾਠ = HAIKU_Has_Clipboard_ਪਾਠ;

    device->ਮੁਕਤ = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    ਵਾਪਸ device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_Show_ਸੁਨੇਹਾ_Box,
    ਝੂਠ
};

ਖਾਲੀ HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    BCursor *cursor;
};

ਸਥਿਰ SDL_Cursor *HAIKU_Create_Cursor_And_ਅੰਕੜੇ(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
        ਜੇ (!ਅੰਕੜੇ) {
            SDL_free(cursor);
            ਵਾਪਸ ਨਿਰਾ;
        }
        ਅੰਕੜੇ->cursor = bcursor;
        cursor->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    }
    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    ਚੋਣ(id)
    {
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CURSORCASE(sdlname, bname) ਹਾਲਤ SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; ਰੋਕੋ
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(ਪਾਠ_2, I_BEAM);
        CURSORCASE(WAIT, ਤਰੱਕੀ);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(ਤਰੱਕੀ, ਤਰੱਕੀ);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(ਸੂਚਕ, FOLLOW_LINK);
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
        CURSORCASE(VERTICAL_ਪਾਠ, I_BEAM_HORIZONTAL);
        CURSORCASE(ALIAS, CREATE_LINK);
        CURSORCASE(COPY, COPY);
        CURSORCASE(NO_DROP, NOT_ALLOWED);
        CURSORCASE(GRAB, GRAB);
        CURSORCASE(GRABBING, GRABBING);
        CURSORCASE(ਖਾਨਾ_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(ਪੰਕਤੀ_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_ਵਿੱਚ, ZOOM_ਵਿੱਚ);
        CURSORCASE(ZOOM_ਬਾਹਰਲਾ, ZOOM_ਬਾਹਰਲਾ);
        #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CURSORCASE
        ਮੂਲ:
            SDL_assert(0);
            ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ HAIKU_Create_Cursor_And_ਅੰਕੜੇ(ਨਵਾਂ BCursor(cursorId));
}

ਸਥਿਰ SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ਵਾਪਸ HAIKU_CreateSystemCursor(id);
}

ਸਥਿਰ ਖਾਲੀ HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = cursor->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ) {
        ਮਿਟਾਓ ਅੰਕੜੇ->cursor;
    }
    SDL_free(ਅੰਕੜੇ);
    SDL_free(cursor);
}

ਸਥਿਰ SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ਜੇ (!converted) {
        ਵਾਪਸ ਨਿਰਾ;
    }

	BBitmap *cursorBitmap = ਨਵਾਂ BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->ਸੈੱਟ_ਬਿੱਟ(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    ਵਾਪਸ HAIKU_Create_Cursor_And_ਅੰਕੜੇ(ਨਵਾਂ BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ਸਥਿਰ ਤਾਰਕਿਕ HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	ਜੇ (!mouse) {
		ਵਾਪਸ ਸੱਚ;
	}

	ਜੇ (cursor) {
		BCursor *hCursor = cursor->ਅੰਦਰੂਨੀ->cursor;
		be_app->ਸੈੱਟ_Cursor(hCursor);
	} ਨਹੀਂਤਾਂ {
		BCursor *hCursor = ਨਵਾਂ BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->ਸੈੱਟ_Cursor(hCursor);
		ਮਿਟਾਓ hCursor;
	}

	ਵਾਪਸ ਸੱਚ;
}

ਸਥਿਰ ਤਾਰਕਿਕ HAIKU_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(ਤਾਰਕਿਕ enabled)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = SDL_GetMouseFocus();
    ਜੇ (!ਖਿੜਕੀ) {
      ਵਾਪਸ ਸੱਚ;
    }

	SDL_BWin *bewin = ਮੰਜ਼ਿਲ_Be_Win(ਖਿੜਕੀ);
	BView *_SDL_View = bewin->GetGLView();
	ਜੇ (!_SDL_View) {
		_SDL_View = bewin->GetView();
		ਜੇ (!_SDL_View)
			ਵਾਪਸ ਝੂਠ;
	}

	bewin->ਤਾਲਾ();
	ਜੇ (enabled)
		_SDL_View->ਸੈੱਟ_Event_ਨਕਾਬ(B_ਸੂਚਕ_EVENTS, B_NO_ਸੂਚਕ_HISTORY);
	ਨਹੀਂਤਾਂ
		_SDL_View->ਸੈੱਟ_Event_ਨਕਾਬ(0, 0);
	bewin->Unlock();

    ਵਾਪਸ ਸੱਚ;
}

ਸਥਿਰ ਖਾਲੀ HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	ਜੇ (!mouse) {
		ਵਾਪਸ;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = HAIKU_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ;

	SDL_ਸੈੱਟ_Default_Cursor(HAIKU_CreateDefaultCursor());
}

ਤਾਰਕਿਕ HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    ਜੇ (!SDL_InitBeApp()) {
        ਵਾਪਸ ਝੂਠ;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_ਜੋੜੋ_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ਨਿਰਾ);
    SDL_ਜੋੜੋ_Mouse(SDL_DEFAULT_MOUSE_ID, ਨਿਰਾ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_ਲੱਦੋ_Library(_this, ਨਿਰਾ);
#ਜੇ_ਅੰਤ

    // We're done!
    ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
ਬਾਹਰੀ "C"
ਤਾਰਕਿਕ HAIKU_OpenURL(ਅਚਲ ਅੱਖਰ *url)
{
#ਜੇ B_HAIKU_ਸੰਸਕਰਣ <= B_HAIKU_ਸੰਸਕਰਣ_1_BETA_5
    BUrl burl(url);
#ਨਹੀਂਤਾਂ
    BUrl burl(url, ਸੱਚ);
#ਜੇ_ਅੰਤ
    ਅਚਲ ਸਥਿਤੀ_t rc = burl.OpenWithPreferredApplication(ਝੂਠ);
    ਜੇ (rc != B_NO_ERROR) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("URL open failed (err=%d)", (ਪੂਰਨ)rc);
    }
    ਵਾਪਸ ਸੱਚ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU

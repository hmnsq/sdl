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

#ضمن "SDL_internal.h"
#ضمن "../../core/haiku/SDL_BApp.h"

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_BWin.h"
#ضمن <Url.h>

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

#ضمن "SDL_bkeyboard.h"
#ضمن "SDL_bwindow.h"
#ضمن "SDL_bclipboard.h"
#ضمن "SDL_bvideo.h"
#ضمن "SDL_bopengl.h"
#ضمن "SDL_bmodes.h"
#ضمن "SDL_bframebuffer.h"
#ضمن "SDL_bevents.h"
#ضمن "SDL_bmessagebox.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_mouse_c.h"

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_کھڑکی *کھڑکی) {
    أرجع (SDL_BWin *)(کھڑکی->اندرونی);
}

ساكن SDL_VideoDevice * HAIKU_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, حجم(SDL_VideoDevice));

    device->اندرونی = عدم; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->سیٹ_Display_منوال = HAIKU_سیٹ_Display_منوال;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = HAIKU_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = HAIKU_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_ناپ = HAIKU_سیٹ_کھڑکی_ناپ;
    device->Show_کھڑکی = HAIKU_Show_کھڑکی;
    device->Hide_کھڑکی = HAIKU_Hide_کھڑکی;
    device->Raise_کھڑکی = HAIKU_Raise_کھڑکی;
    device->Maximize_کھڑکی = HAIKU_Maximize_کھڑکی;
    device->Minimize_کھڑکی = HAIKU_Minimize_کھڑکی;
    device->Restore_کھڑکی = HAIKU_Restore_کھڑکی;
    device->سیٹ_کھڑکی_Bordered = HAIKU_سیٹ_کھڑکی_Bordered;
    device->سیٹ_کھڑکی_Resizable = HAIKU_سیٹ_کھڑکی_Resizable;
    device->سیٹ_کھڑکی_Fullscreen = HAIKU_سیٹ_کھڑکی_Fullscreen;
    device->سیٹ_کھڑکی_Mouse_Grab = HAIKU_سیٹ_کھڑکی_Mouse_Grab;
    device->سیٹ_کھڑکی_Minimum_ناپ = HAIKU_سیٹ_کھڑکی_Minimum_ناپ;
    device->سیٹ_کھڑکی_ماپا = HAIKU_سیٹ_کھڑکی_ماپا;
    device->سیٹ_کھڑکی_Modal = HAIKU_سیٹ_کھڑکی_Modal;
    device->Destroy_کھڑکی = HAIKU_Destroy_کھڑکی;
    device->Create_کھڑکی_Framebuffer = HAIKU_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = HAIKU_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = HAIKU_Destroy_کھڑکی_Framebuffer;

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    device->GL_لدو_Library = HAIKU_GL_لدو_Library;
    device->GL_Get_Proc_پتہ = HAIKU_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = HAIKU_GL_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = HAIKU_GL_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = HAIKU_GL_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#جے_انت

    device->سیٹ_Clipboard_متن = HAIKU_سیٹ_Clipboard_متن;
    device->Get_Clipboard_متن = HAIKU_Get_Clipboard_متن;
    device->Has_Clipboard_متن = HAIKU_Has_Clipboard_متن;

    device->حرر = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    أرجع device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_Show_سنیہا_Box,
    خطأ
};

فراغ HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->اندرونی);
    SDL_free(device);
}

بنية SDL_Cursor_انکڑے
{
    BCursor *cursor;
};

ساكن SDL_Cursor *HAIKU_Create_Cursor_And_انکڑے(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_انکڑے *انکڑے = (SDL_Cursor_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
        إذا (!انکڑے) {
            SDL_free(cursor);
            أرجع عدم;
        }
        انکڑے->cursor = bcursor;
        cursor->اندرونی = انکڑے;
    }
    أرجع cursor;
}

ساكن SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    بدل(id)
    {
        #تعریف_کرو CURSORCASE(sdlname, bname) حالة SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; اكسر
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(متن_2, I_BEAM);
        CURSORCASE(WAIT, ترقی);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(ترقی, ترقی);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(اشارہ_گر, FOLLOW_LINK);
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
        CURSORCASE(VERTICAL_متن, I_BEAM_HORIZONTAL);
        CURSORCASE(ALIAS, CREATE_LINK);
        CURSORCASE(COPY, COPY);
        CURSORCASE(NO_DROP, NOT_ALLOWED);
        CURSORCASE(GRAB, GRAB);
        CURSORCASE(GRABBING, GRABBING);
        CURSORCASE(خانہ_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(صف_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_وچ, ZOOM_وچ);
        CURSORCASE(ZOOM_باہرلا, ZOOM_باہرلا);
        #تعریف_رد CURSORCASE
        افتراضي:
            SDL_assert(0);
            أرجع عدم;
    }

    أرجع HAIKU_Create_Cursor_And_انکڑے(جديد BCursor(cursorId));
}

ساكن SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع HAIKU_CreateSystemCursor(id);
}

ساكن فراغ HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_انکڑے *انکڑے = cursor->اندرونی;

    إذا (انکڑے) {
        مٹاؤ انکڑے->cursor;
    }
    SDL_free(انکڑے);
    SDL_free(cursor);
}

ساكن SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    إذا (!converted) {
        أرجع عدم;
    }

	BBitmap *cursorBitmap = جديد BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->سیٹ_بٹ(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    أرجع HAIKU_Create_Cursor_And_انکڑے(جديد BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ساكن منطقي HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	إذا (!mouse) {
		أرجع سچ;
	}

	إذا (cursor) {
		BCursor *hCursor = cursor->اندرونی->cursor;
		be_app->سیٹ_Cursor(hCursor);
	} وإلا {
		BCursor *hCursor = جديد BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->سیٹ_Cursor(hCursor);
		مٹاؤ hCursor;
	}

	أرجع سچ;
}

ساكن منطقي HAIKU_سیٹ_Relative_Mouse_منوال(منطقي enabled)
{
    SDL_کھڑکی *کھڑکی = SDL_GetMouseFocus();
    إذا (!کھڑکی) {
      أرجع سچ;
    }

	SDL_BWin *bewin = منزل_Be_Win(کھڑکی);
	BView *_SDL_View = bewin->GetGLView();
	إذا (!_SDL_View) {
		_SDL_View = bewin->GetView();
		إذا (!_SDL_View)
			أرجع خطأ;
	}

	bewin->جندرا();
	إذا (enabled)
		_SDL_View->سیٹ_Event_نقاب(B_اشارہ_گر_EVENTS, B_NO_اشارہ_گر_HISTORY);
	وإلا
		_SDL_View->سیٹ_Event_نقاب(0, 0);
	bewin->Unlock();

    أرجع سچ;
}

ساكن فراغ HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	إذا (!mouse) {
		أرجع;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->سیٹ_Relative_Mouse_منوال = HAIKU_سیٹ_Relative_Mouse_منوال;

	SDL_سیٹ_Default_Cursor(HAIKU_CreateDefaultCursor());
}

منطقي HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    إذا (!SDL_InitBeApp()) {
        أرجع خطأ;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_لدو_Library(_this, عدم);
#جے_انت

    // We're done!
    أرجع سچ;
}

فراغ HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
خارجي "C"
منطقي HAIKU_OpenURL(ثابت حرف *url)
{
#إذا B_HAIKU_نسخہ <= B_HAIKU_نسخہ_1_BETA_5
    BUrl burl(url);
#وإلا
    BUrl burl(url, سچ);
#جے_انت
    ثابت حالت_t rc = burl.OpenWithPreferredApplication(خطأ);
    إذا (rc != B_NO_ERROR) {
        أرجع SDL_سیٹ_Error("URL open failed (err=%d)", (صحيح)rc);
    }
    أرجع سچ;
}

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // SDL_VIDEO_DRIVER_HAIKU

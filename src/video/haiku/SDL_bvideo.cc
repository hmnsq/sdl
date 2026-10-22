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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_BWin.h"
#ضمن <Url.h>

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

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

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_دري *دري) {
    أرجع (SDL_BWin *)(دري->اندروني);
}

ساكن SDL_VideoDevice * HAIKU_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, حجم(SDL_VideoDevice));

    device->اندروني = عدم; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->سيٽ_Display_گهڻائي = HAIKU_سيٽ_Display_گهڻائي;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_دري;
    device->سيٽ_دري_Title = HAIKU_سيٽ_دري_Title;
    device->سيٽ_دري_Position = HAIKU_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = HAIKU_سيٽ_دري_سائيز;
    device->Show_دري = HAIKU_Show_دري;
    device->Hide_دري = HAIKU_Hide_دري;
    device->Raise_دري = HAIKU_Raise_دري;
    device->Maximize_دري = HAIKU_Maximize_دري;
    device->Minimize_دري = HAIKU_Minimize_دري;
    device->Restore_دري = HAIKU_Restore_دري;
    device->سيٽ_دري_Bordered = HAIKU_سيٽ_دري_Bordered;
    device->سيٽ_دري_Resizable = HAIKU_سيٽ_دري_Resizable;
    device->سيٽ_دري_Fullscreen = HAIKU_سيٽ_دري_Fullscreen;
    device->سيٽ_دري_Mouse_Grab = HAIKU_سيٽ_دري_Mouse_Grab;
    device->سيٽ_دري_Minimum_سائيز = HAIKU_سيٽ_دري_Minimum_سائيز;
    device->سيٽ_دري_والد = HAIKU_سيٽ_دري_والد;
    device->سيٽ_دري_Modal = HAIKU_سيٽ_دري_Modal;
    device->Destroy_دري = HAIKU_Destroy_دري;
    device->Create_دري_Framebuffer = HAIKU_Create_دري_Framebuffer;
    device->Update_دري_Framebuffer = HAIKU_Update_دري_Framebuffer;
    device->Destroy_دري_Framebuffer = HAIKU_Destroy_دري_Framebuffer;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    device->GL_ڀريو_Library = HAIKU_GL_ڀريو_Library;
    device->GL_Get_Proc_پتو = HAIKU_GL_Get_Proc_پتو;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = HAIKU_GL_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = HAIKU_GL_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = HAIKU_GL_مٽا_سٽا_دري;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#جيڪڏهن_پورو

    device->سيٽ_Clipboard_متن = HAIKU_سيٽ_Clipboard_متن;
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
    HAIKU_Show_پيغام_Box,
    خطأ
};

فراغ HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->اندروني);
    SDL_free(device);
}

بنية SDL_Cursor_معلومات
{
    BCursor *cursor;
};

ساكن SDL_Cursor *HAIKU_Create_Cursor_And_معلومات(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_معلومات *معلومات = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*معلومات));
        إذا (!معلومات) {
            SDL_free(cursor);
            أرجع عدم;
        }
        معلومات->cursor = bcursor;
        cursor->اندروني = معلومات;
    }
    أرجع cursor;
}

ساكن SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    بدل(id)
    {
        #وصف_ڪريو CURSORCASE(sdlname, bname) حالة SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; اكسر
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(متن_2, I_BEAM);
        CURSORCASE(WAIT, ترقي);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(ترقي, ترقي);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(اشارو, FOLLOW_LINK);
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
        CURSORCASE(کانو_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(صف_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_اندريون, ZOOM_اندريون);
        CURSORCASE(ZOOM_ٻاهريون, ZOOM_ٻاهريون);
        #وصف_رد CURSORCASE
        افتراضي:
            SDL_assert(0);
            أرجع عدم;
    }

    أرجع HAIKU_Create_Cursor_And_معلومات(جديد BCursor(cursorId));
}

ساكن SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع HAIKU_CreateSystemCursor(id);
}

ساكن فراغ HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_معلومات *معلومات = cursor->اندروني;

    إذا (معلومات) {
        ميٽيو معلومات->cursor;
    }
    SDL_free(معلومات);
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
	cursorBitmap->سيٽ_بٽ(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    أرجع HAIKU_Create_Cursor_And_معلومات(جديد BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ساكن منطقي HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	إذا (!mouse) {
		أرجع سچ;
	}

	إذا (cursor) {
		BCursor *hCursor = cursor->اندروني->cursor;
		be_app->سيٽ_Cursor(hCursor);
	} وإلا {
		BCursor *hCursor = جديد BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->سيٽ_Cursor(hCursor);
		ميٽيو hCursor;
	}

	أرجع سچ;
}

ساكن منطقي HAIKU_سيٽ_Relative_Mouse_گهڻائي(منطقي enabled)
{
    SDL_دري *دري = SDL_GetMouseFocus();
    إذا (!دري) {
      أرجع سچ;
    }

	SDL_BWin *bewin = منزل_Be_Win(دري);
	BView *_SDL_View = bewin->GetGLView();
	إذا (!_SDL_View) {
		_SDL_View = bewin->GetView();
		إذا (!_SDL_View)
			أرجع خطأ;
	}

	bewin->تالو();
	إذا (enabled)
		_SDL_View->سيٽ_Event_نقاب(B_اشارو_EVENTS, B_NO_اشارو_HISTORY);
	وإلا
		_SDL_View->سيٽ_Event_نقاب(0, 0);
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
	mouse->سيٽ_Relative_Mouse_گهڻائي = HAIKU_سيٽ_Relative_Mouse_گهڻائي;

	SDL_سيٽ_Default_Cursor(HAIKU_CreateDefaultCursor());
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
    SDL_جوڙيو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جوڙيو_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_ڀريو_Library(_this, عدم);
#جيڪڏهن_پورو

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
#إذا B_HAIKU_نسخو <= B_HAIKU_نسخو_1_BETA_5
    BUrl burl(url);
#وإلا
    BUrl burl(url, سچ);
#جيڪڏهن_پورو
    ثابت حالت_t rc = burl.OpenWithPreferredApplication(خطأ);
    إذا (rc != B_NO_ERROR) {
        أرجع SDL_سيٽ_Error("URL open failed (err=%d)", (صحيح)rc);
    }
    أرجع سچ;
}

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_HAIKU

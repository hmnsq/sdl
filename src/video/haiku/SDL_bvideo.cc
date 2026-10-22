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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_BWin.h"
#ضمن <Url.h>

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

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

ساكن SDL_INLINE SDL_BWin *مقصد_Be_Win(SDL_پنجره *پنجره) {
    أرجع (SDL_BWin *)(پنجره->داخلی);
}

ساكن SDL_VideoDevice * HAIKU_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, حجم(SDL_VideoDevice));

    device->داخلی = عدم; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->مجموعه_Display_نما = HAIKU_مجموعه_Display_نما;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_پنجره;
    device->مجموعه_پنجره_Title = HAIKU_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Position = HAIKU_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = HAIKU_مجموعه_پنجره_اندازه;
    device->Show_پنجره = HAIKU_Show_پنجره;
    device->Hide_پنجره = HAIKU_Hide_پنجره;
    device->Raise_پنجره = HAIKU_Raise_پنجره;
    device->Maximize_پنجره = HAIKU_Maximize_پنجره;
    device->Minimize_پنجره = HAIKU_Minimize_پنجره;
    device->Restore_پنجره = HAIKU_Restore_پنجره;
    device->مجموعه_پنجره_Bordered = HAIKU_مجموعه_پنجره_Bordered;
    device->مجموعه_پنجره_Resizable = HAIKU_مجموعه_پنجره_Resizable;
    device->مجموعه_پنجره_Fullscreen = HAIKU_مجموعه_پنجره_Fullscreen;
    device->مجموعه_پنجره_Mouse_Grab = HAIKU_مجموعه_پنجره_Mouse_Grab;
    device->مجموعه_پنجره_Minimum_اندازه = HAIKU_مجموعه_پنجره_Minimum_اندازه;
    device->مجموعه_پنجره_والد = HAIKU_مجموعه_پنجره_والد;
    device->مجموعه_پنجره_Modal = HAIKU_مجموعه_پنجره_Modal;
    device->Destroy_پنجره = HAIKU_Destroy_پنجره;
    device->Create_پنجره_Framebuffer = HAIKU_Create_پنجره_Framebuffer;
    device->Update_پنجره_Framebuffer = HAIKU_Update_پنجره_Framebuffer;
    device->Destroy_پنجره_Framebuffer = HAIKU_Destroy_پنجره_Framebuffer;

#اگر_تعریف_شده SDL_VIDEO_OPENGL
    device->GL_بارگیری_Library = HAIKU_GL_بارگیری_Library;
    device->GL_Get_Proc_آدرس = HAIKU_GL_Get_Proc_آدرس;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = HAIKU_GL_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = HAIKU_GL_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = HAIKU_GL_جابجا_پنجره;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#پایان_اگر

    device->مجموعه_Clipboard_متن = HAIKU_مجموعه_Clipboard_متن;
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
    HAIKU_Show_پیام_Box,
    خطأ
};

فراغ HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->داخلی);
    SDL_free(device);
}

بنية SDL_Cursor_داده
{
    BCursor *cursor;
};

ساكن SDL_Cursor *HAIKU_Create_Cursor_And_داده(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_داده *داده = (SDL_Cursor_داده *)SDL_calloc(1, حجم(*داده));
        إذا (!داده) {
            SDL_free(cursor);
            أرجع عدم;
        }
        داده->cursor = bcursor;
        cursor->داخلی = داده;
    }
    أرجع cursor;
}

ساكن SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    بدل(id)
    {
        #تعریف_کن CURSORCASE(sdlname, bname) حالة SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; اكسر
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(متن_2, I_BEAM);
        CURSORCASE(WAIT, پیشرفت);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(پیشرفت, پیشرفت);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(اشاره_گر, FOLLOW_LINK);
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
        CURSORCASE(ستون_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(ردیف_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_درون, ZOOM_درون);
        CURSORCASE(ZOOM_بیرون, ZOOM_بیرون);
        #لغو_تعریف CURSORCASE
        افتراضي:
            SDL_assert(0);
            أرجع عدم;
    }

    أرجع HAIKU_Create_Cursor_And_داده(جديد BCursor(cursorId));
}

ساكن SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع HAIKU_CreateSystemCursor(id);
}

ساكن فراغ HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_داده *داده = cursor->داخلی;

    إذا (داده) {
        حذف داده->cursor;
    }
    SDL_free(داده);
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
	cursorBitmap->مجموعه_بیتها(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    أرجع HAIKU_Create_Cursor_And_داده(جديد BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ساكن منطقي HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	إذا (!mouse) {
		أرجع درست;
	}

	إذا (cursor) {
		BCursor *hCursor = cursor->داخلی->cursor;
		be_app->مجموعه_Cursor(hCursor);
	} وإلا {
		BCursor *hCursor = جديد BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->مجموعه_Cursor(hCursor);
		حذف hCursor;
	}

	أرجع درست;
}

ساكن منطقي HAIKU_مجموعه_Relative_Mouse_نما(منطقي enabled)
{
    SDL_پنجره *پنجره = SDL_GetMouseFocus();
    إذا (!پنجره) {
      أرجع درست;
    }

	SDL_BWin *bewin = مقصد_Be_Win(پنجره);
	BView *_SDL_View = bewin->GetGLView();
	إذا (!_SDL_View) {
		_SDL_View = bewin->GetView();
		إذا (!_SDL_View)
			أرجع خطأ;
	}

	bewin->قفل();
	إذا (enabled)
		_SDL_View->مجموعه_Event_ماسک(B_اشاره_گر_EVENTS, B_NO_اشاره_گر_HISTORY);
	وإلا
		_SDL_View->مجموعه_Event_ماسک(0, 0);
	bewin->Unlock();

    أرجع درست;
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
	mouse->مجموعه_Relative_Mouse_نما = HAIKU_مجموعه_Relative_Mouse_نما;

	SDL_مجموعه_Default_Cursor(HAIKU_CreateDefaultCursor());
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
    SDL_جمع_کن_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جمع_کن_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

#اگر_تعریف_شده SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_بارگیری_Library(_this, عدم);
#پایان_اگر

    // We're done!
    أرجع درست;
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
#إذا B_HAIKU_نسخه <= B_HAIKU_نسخه_1_BETA_5
    BUrl burl(url);
#وإلا
    BUrl burl(url, درست);
#پایان_اگر
    ثابت وضعیت_t rc = burl.OpenWithPreferredApplication(خطأ);
    إذا (rc != B_NO_ERROR) {
        أرجع SDL_مجموعه_Error("URL open failed (err=%d)", (صحيح)rc);
    }
    أرجع درست;
}

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // SDL_VIDEO_DRIVER_HAIKU

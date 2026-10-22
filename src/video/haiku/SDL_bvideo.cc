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

#که_تعریف_شوی SDL_VIDEO_DRIVER_HAIKU

#ضمن "SDL_BWin.h"
#ضمن <Url.h>

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

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

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_کړکۍ *کړکۍ) {
    أرجع (SDL_BWin *)(کړکۍ->دننی);
}

ساكن SDL_VideoDevice * HAIKU_CreateDevice(فراغ)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, حجم(SDL_VideoDevice));

    device->دننی = عدم; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->سېټ_Display_ډېرپېښ = HAIKU_سېټ_Display_ډېرپېښ;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = HAIKU_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Position = HAIKU_سېټ_کړکۍ_Position;
    device->سېټ_کړکۍ_اندازه = HAIKU_سېټ_کړکۍ_اندازه;
    device->Show_کړکۍ = HAIKU_Show_کړکۍ;
    device->Hide_کړکۍ = HAIKU_Hide_کړکۍ;
    device->Raise_کړکۍ = HAIKU_Raise_کړکۍ;
    device->Maximize_کړکۍ = HAIKU_Maximize_کړکۍ;
    device->Minimize_کړکۍ = HAIKU_Minimize_کړکۍ;
    device->Restore_کړکۍ = HAIKU_Restore_کړکۍ;
    device->سېټ_کړکۍ_Bordered = HAIKU_سېټ_کړکۍ_Bordered;
    device->سېټ_کړکۍ_Resizable = HAIKU_سېټ_کړکۍ_Resizable;
    device->سېټ_کړکۍ_Fullscreen = HAIKU_سېټ_کړکۍ_Fullscreen;
    device->سېټ_کړکۍ_Mouse_Grab = HAIKU_سېټ_کړکۍ_Mouse_Grab;
    device->سېټ_کړکۍ_Minimum_اندازه = HAIKU_سېټ_کړکۍ_Minimum_اندازه;
    device->سېټ_کړکۍ_پلار = HAIKU_سېټ_کړکۍ_پلار;
    device->سېټ_کړکۍ_Modal = HAIKU_سېټ_کړکۍ_Modal;
    device->Destroy_کړکۍ = HAIKU_Destroy_کړکۍ;
    device->Create_کړکۍ_Framebuffer = HAIKU_Create_کړکۍ_Framebuffer;
    device->Update_کړکۍ_Framebuffer = HAIKU_Update_کړکۍ_Framebuffer;
    device->Destroy_کړکۍ_Framebuffer = HAIKU_Destroy_کړکۍ_Framebuffer;

#که_تعریف_شوی SDL_VIDEO_OPENGL
    device->GL_بارول_Library = HAIKU_GL_بارول_Library;
    device->GL_Get_Proc_پته = HAIKU_GL_Get_Proc_پته;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = HAIKU_GL_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = HAIKU_GL_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = HAIKU_GL_بدلون_کړکۍ;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#د_که_پای

    device->سېټ_Clipboard_متن = HAIKU_سېټ_Clipboard_متن;
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
    HAIKU_Show_پیغام_Box,
    خطأ
};

فراغ HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->دننی);
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
        cursor->دننی = معلومات;
    }
    أرجع cursor;
}

ساكن SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    بدل(id)
    {
        #تعریف_کړه CURSORCASE(sdlname, bname) حالة SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; اكسر
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(متن_2, I_BEAM);
        CURSORCASE(WAIT, پرمختګ);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(پرمختګ, پرمختګ);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(اشاره_ګر, FOLLOW_LINK);
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
        CURSORCASE(لیکه_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_دننه, ZOOM_دننه);
        CURSORCASE(ZOOM_بهر, ZOOM_بهر);
        #تعریف_لغوه CURSORCASE
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
    SDL_Cursor_معلومات *معلومات = cursor->دننی;

    إذا (معلومات) {
        ړنګول معلومات->cursor;
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
	cursorBitmap->سېټ_بټونه(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    أرجع HAIKU_Create_Cursor_And_معلومات(جديد BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ساكن منطقي HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	إذا (!mouse) {
		أرجع ریښتیا;
	}

	إذا (cursor) {
		BCursor *hCursor = cursor->دننی->cursor;
		be_app->سېټ_Cursor(hCursor);
	} وإلا {
		BCursor *hCursor = جديد BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->سېټ_Cursor(hCursor);
		ړنګول hCursor;
	}

	أرجع ریښتیا;
}

ساكن منطقي HAIKU_سېټ_Relative_Mouse_ډېرپېښ(منطقي enabled)
{
    SDL_کړکۍ *کړکۍ = SDL_GetMouseFocus();
    إذا (!کړکۍ) {
      أرجع ریښتیا;
    }

	SDL_BWin *bewin = منزل_Be_Win(کړکۍ);
	BView *_SDL_View = bewin->GetGLView();
	إذا (!_SDL_View) {
		_SDL_View = bewin->GetView();
		إذا (!_SDL_View)
			أرجع خطأ;
	}

	bewin->قلف();
	إذا (enabled)
		_SDL_View->سېټ_Event_ماسک(B_اشاره_ګر_EVENTS, B_NO_اشاره_ګر_HISTORY);
	وإلا
		_SDL_View->سېټ_Event_ماسک(0, 0);
	bewin->Unlock();

    أرجع ریښتیا;
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
	mouse->سېټ_Relative_Mouse_ډېرپېښ = HAIKU_سېټ_Relative_Mouse_ډېرپېښ;

	SDL_سېټ_Default_Cursor(HAIKU_CreateDefaultCursor());
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
    SDL_جمع_کړه_Keyboard(SDL_DEFAULT_KEYBOARD_ID, عدم);
    SDL_جمع_کړه_Mouse(SDL_DEFAULT_MOUSE_ID, عدم);

#که_تعریف_شوی SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_بارول_Library(_this, عدم);
#د_که_پای

    // We're done!
    أرجع ریښتیا;
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
    BUrl burl(url, ریښتیا);
#د_که_پای
    ثابت حالت_t rc = burl.OpenWithPreferredApplication(خطأ);
    إذا (rc != B_NO_ERROR) {
        أرجع SDL_سېټ_Error("URL open failed (err=%d)", (صحيح)rc);
    }
    أرجع ریښتیا;
}

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_VIDEO_DRIVER_HAIKU

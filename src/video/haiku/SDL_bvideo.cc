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

#شامل "SDL_internal.h"
#شامل "../../core/haiku/SDL_BApp.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU

#شامل "SDL_BWin.h"
#شامل <Url.h>

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

#شامل "SDL_bkeyboard.h"
#شامل "SDL_bwindow.h"
#شامل "SDL_bclipboard.h"
#شامل "SDL_bvideo.h"
#شامل "SDL_bopengl.h"
#شامل "SDL_bmodes.h"
#شامل "SDL_bframebuffer.h"
#شامل "SDL_bevents.h"
#شامل "SDL_bmessagebox.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_mouse_c.h"

ساکن SDL_INLINE SDL_BWin *مقصد_Be_Win(SDL_کھڑکی *کھڑکی) {
    واپس (SDL_BWin *)(کھڑکی->اندرونی_2);
}

ساکن SDL_VideoDevice * HAIKU_CreateDevice(خالی)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, حجم(SDL_VideoDevice));

    device->اندرونی_2 = تہی; /* FIXME: Is this the cause of some of the
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
    device->سیٹ_کھڑکی_سائز = HAIKU_سیٹ_کھڑکی_سائز;
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
    device->سیٹ_کھڑکی_Minimum_سائز = HAIKU_سیٹ_کھڑکی_Minimum_سائز;
    device->سیٹ_کھڑکی_والد = HAIKU_سیٹ_کھڑکی_والد;
    device->سیٹ_کھڑکی_Modal = HAIKU_سیٹ_کھڑکی_Modal;
    device->Destroy_کھڑکی = HAIKU_Destroy_کھڑکی;
    device->Create_کھڑکی_Framebuffer = HAIKU_Create_کھڑکی_Framebuffer;
    device->Update_کھڑکی_Framebuffer = HAIKU_Update_کھڑکی_Framebuffer;
    device->Destroy_کھڑکی_Framebuffer = HAIKU_Destroy_کھڑکی_Framebuffer;

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    device->GL_بھرو_Library = HAIKU_GL_بھرو_Library;
    device->GL_Get_Proc_پتہ = HAIKU_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = HAIKU_GL_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = HAIKU_GL_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = HAIKU_GL_تبادلہ_کھڑکی;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#اگر_ختم

    device->سیٹ_Clipboard_متن = HAIKU_سیٹ_Clipboard_متن;
    device->Get_Clipboard_متن = HAIKU_Get_Clipboard_متن;
    device->Has_Clipboard_متن = HAIKU_Has_Clipboard_متن;

    device->آزاد = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    واپس device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_Show_پیغام_Box,
    جھوٹ
};

خالی HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساخت SDL_Cursor_ڈیٹا
{
    BCursor *cursor;
};

ساکن SDL_Cursor *HAIKU_Create_Cursor_And_ڈیٹا(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    اگر (cursor) {
        SDL_Cursor_ڈیٹا *ڈیٹا = (SDL_Cursor_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
        اگر (!ڈیٹا) {
            SDL_free(cursor);
            واپس تہی;
        }
        ڈیٹا->cursor = bcursor;
        cursor->اندرونی_2 = ڈیٹا;
    }
    واپس cursor;
}

ساکن SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    انتخاب(id)
    {
        #تعریف_کرو CURSORCASE(sdlname, bname) حالت SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; توڑو
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(متن_2, I_BEAM);
        CURSORCASE(WAIT, پیش_رفت);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(پیش_رفت, پیش_رفت);
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
        CURSORCASE(ستون_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(صف_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_اندر, ZOOM_اندر);
        CURSORCASE(ZOOM_برآمد, ZOOM_برآمد);
        #تعریف_منسوخ CURSORCASE
        طےشدہ:
            SDL_assert(0);
            واپس تہی;
    }

    واپس HAIKU_Create_Cursor_And_ڈیٹا(نیا BCursor(cursorId));
}

ساکن SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    واپس HAIKU_CreateSystemCursor(id);
}

ساکن خالی HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_ڈیٹا *ڈیٹا = cursor->اندرونی_2;

    اگر (ڈیٹا) {
        حذف ڈیٹا->cursor;
    }
    SDL_free(ڈیٹا);
    SDL_free(cursor);
}

ساکن SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, صحیح hot_x, صحیح hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    اگر (!converted) {
        واپس تہی;
    }

	BBitmap *cursorBitmap = نیا BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->سیٹ_بٹ(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    واپس HAIKU_Create_Cursor_And_ڈیٹا(نیا BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

ساکن منطقی HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	اگر (!mouse) {
		واپس سچ;
	}

	اگر (cursor) {
		BCursor *hCursor = cursor->اندرونی_2->cursor;
		be_app->سیٹ_Cursor(hCursor);
	} ورنہ {
		BCursor *hCursor = نیا BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->سیٹ_Cursor(hCursor);
		حذف hCursor;
	}

	واپس سچ;
}

ساکن منطقی HAIKU_سیٹ_Relative_Mouse_منوال(منطقی enabled)
{
    SDL_کھڑکی *کھڑکی = SDL_GetMouseFocus();
    اگر (!کھڑکی) {
      واپس سچ;
    }

	SDL_BWin *bewin = مقصد_Be_Win(کھڑکی);
	BView *_SDL_View = bewin->GetGLView();
	اگر (!_SDL_View) {
		_SDL_View = bewin->GetView();
		اگر (!_SDL_View)
			واپس جھوٹ;
	}

	bewin->تالا();
	اگر (enabled)
		_SDL_View->سیٹ_Event_نقاب(B_اشارہ_گر_EVENTS, B_NO_اشارہ_گر_HISTORY);
	ورنہ
		_SDL_View->سیٹ_Event_نقاب(0, 0);
	bewin->Unlock();

    واپس سچ;
}

ساکن خالی HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	اگر (!mouse) {
		واپس;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->سیٹ_Relative_Mouse_منوال = HAIKU_سیٹ_Relative_Mouse_منوال;

	SDL_سیٹ_Default_Cursor(HAIKU_CreateDefaultCursor());
}

منطقی HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    اگر (!SDL_InitBeApp()) {
        واپس جھوٹ;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_جوڑو_Keyboard(SDL_DEFAULT_KEYBOARD_ID, تہی);
    SDL_جوڑو_Mouse(SDL_DEFAULT_MOUSE_ID, تہی);

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_بھرو_Library(_this, تہی);
#اگر_ختم

    // We're done!
    واپس سچ;
}

خالی HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
خارجی "C"
منطقی HAIKU_OpenURL(ثابت حرف *url)
{
#اگر B_HAIKU_نسخہ <= B_HAIKU_نسخہ_1_BETA_5
    BUrl burl(url);
#ورنہ
    BUrl burl(url, سچ);
#اگر_ختم
    ثابت حالت_t rc = burl.OpenWithPreferredApplication(جھوٹ);
    اگر (rc != B_NO_ERROR) {
        واپس SDL_سیٹ_Error("URL open failed (err=%d)", (صحیح)rc);
    }
    واپس سچ;
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_HAIKU

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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_HAIKU

#अन्तर्भाव "SDL_BWin.h"
#अन्तर्भाव <Url.h>

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

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

स्थिर SDL_INLINE SDL_BWin *गन्तव्यम्_Be_Win(SDL_गवाक्षः *गवाक्षः) {
    प्रत्यागम (SDL_BWin *)(गवाक्षः->आन्तरिकम्);
}

स्थिर SDL_VideoDevice * HAIKU_CreateDevice(शून्य)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, परिमाण(SDL_VideoDevice));

    device->आन्तरिकम् = रिक्त; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->समुच्चयः_Display_बहुलकम् = HAIKU_समुच्चयः_Display_बहुलकम्;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = HAIKU_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Position = HAIKU_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = HAIKU_समुच्चयः_गवाक्षः_आकार;
    device->Show_गवाक्षः = HAIKU_Show_गवाक्षः;
    device->Hide_गवाक्षः = HAIKU_Hide_गवाक्षः;
    device->Raise_गवाक्षः = HAIKU_Raise_गवाक्षः;
    device->Maximize_गवाक्षः = HAIKU_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = HAIKU_Minimize_गवाक्षः;
    device->Restore_गवाक्षः = HAIKU_Restore_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Bordered = HAIKU_समुच्चयः_गवाक्षः_Bordered;
    device->समुच्चयः_गवाक्षः_Resizable = HAIKU_समुच्चयः_गवाक्षः_Resizable;
    device->समुच्चयः_गवाक्षः_Fullscreen = HAIKU_समुच्चयः_गवाक्षः_Fullscreen;
    device->समुच्चयः_गवाक्षः_Mouse_Grab = HAIKU_समुच्चयः_गवाक्षः_Mouse_Grab;
    device->समुच्चयः_गवाक्षः_Minimum_आकार = HAIKU_समुच्चयः_गवाक्षः_Minimum_आकार;
    device->समुच्चयः_गवाक्षः_Parent = HAIKU_समुच्चयः_गवाक्षः_Parent;
    device->समुच्चयः_गवाक्षः_Modal = HAIKU_समुच्चयः_गवाक्षः_Modal;
    device->Destroy_गवाक्षः = HAIKU_Destroy_गवाक्षः;
    device->Create_गवाक्षः_Framebuffer = HAIKU_Create_गवाक्षः_Framebuffer;
    device->Update_गवाक्षः_Framebuffer = HAIKU_Update_गवाक्षः_Framebuffer;
    device->Destroy_गवाक्षः_Framebuffer = HAIKU_Destroy_गवाक्षः_Framebuffer;

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    device->GL_आरोपय_Library = HAIKU_GL_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = HAIKU_GL_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = HAIKU_GL_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = HAIKU_GL_GetSwapInterval;
    device->GL_Swap_गवाक्षः = HAIKU_GL_Swap_गवाक्षः;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#यदि_अन्तः

    device->समुच्चयः_Clipboard_Text = HAIKU_समुच्चयः_Clipboard_Text;
    device->GetClipboardText = HAIKU_GetClipboardText;
    device->HasClipboardText = HAIKU_HasClipboardText;

    device->मुक्त = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    प्रत्यागम device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_Show_सन्देशः_Box,
    असत्य
};

शून्य HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

संरचना SDL_Cursor_दत्त
{
    BCursor *cursor;
};

स्थिर SDL_Cursor *HAIKU_Create_Cursor_And_दत्त(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (cursor) {
        SDL_Cursor_दत्त *दत्त = (SDL_Cursor_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
        यदि (!दत्त) {
            SDL_free(cursor);
            प्रत्यागम रिक्त;
        }
        दत्त->cursor = bcursor;
        cursor->आन्तरिकम् = दत्त;
    }
    प्रत्यागम cursor;
}

स्थिर SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    विकल्प(id)
    {
        #परिभाषय CURSORCASE(sdlname, bname) पक्ष SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; भङ्ग
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(TEXT, I_BEAM);
        CURSORCASE(WAIT, प्रगतिः);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(प्रगतिः, प्रगतिः);
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
        CURSORCASE(ZOOM_अन्तर्, ZOOM_अन्तर्);
        CURSORCASE(ZOOM_बहिर्गमनम्, ZOOM_बहिर्गमनम्);
        #अपरिभाषय CURSORCASE
        स्वभाव:
            SDL_assert(0);
            प्रत्यागम रिक्त;
    }

    प्रत्यागम HAIKU_Create_Cursor_And_दत्त(नूतन BCursor(cursorId));
}

स्थिर SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    प्रत्यागम HAIKU_CreateSystemCursor(id);
}

स्थिर शून्य HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_दत्त *दत्त = cursor->आन्तरिकम्;

    यदि (दत्त) {
        विलोपय दत्त->cursor;
    }
    SDL_free(दत्त);
    SDL_free(cursor);
}

स्थिर SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    यदि (!converted) {
        प्रत्यागम रिक्त;
    }

	BBitmap *cursorBitmap = नूतन BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->समुच्चयः_द्वयङ्काः(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    प्रत्यागम HAIKU_Create_Cursor_And_दत्त(नूतन BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

स्थिर तार्किक HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	यदि (!mouse) {
		प्रत्यागम सत्य;
	}

	यदि (cursor) {
		BCursor *hCursor = cursor->आन्तरिकम्->cursor;
		be_app->समुच्चयः_Cursor(hCursor);
	} अन्यथा {
		BCursor *hCursor = नूतन BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->समुच्चयः_Cursor(hCursor);
		विलोपय hCursor;
	}

	प्रत्यागम सत्य;
}

स्थिर तार्किक HAIKU_समुच्चयः_Relative_Mouse_बहुलकम्(तार्किक enabled)
{
    SDL_गवाक्षः *गवाक्षः = SDL_GetMouseFocus();
    यदि (!गवाक्षः) {
      प्रत्यागम सत्य;
    }

	SDL_BWin *bewin = गन्तव्यम्_Be_Win(गवाक्षः);
	BView *_SDL_View = bewin->GetGLView();
	यदि (!_SDL_View) {
		_SDL_View = bewin->GetView();
		यदि (!_SDL_View)
			प्रत्यागम असत्य;
	}

	bewin->तालकम्();
	यदि (enabled)
		_SDL_View->समुच्चयः_Event_आवरणम्(B_POINTER_EVENTS, B_NO_POINTER_HISTORY);
	अन्यथा
		_SDL_View->समुच्चयः_Event_आवरणम्(0, 0);
	bewin->Unlock();

    प्रत्यागम सत्य;
}

स्थिर शून्य HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	यदि (!mouse) {
		प्रत्यागम;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->समुच्चयः_Relative_Mouse_बहुलकम् = HAIKU_समुच्चयः_Relative_Mouse_बहुलकम्;

	SDL_समुच्चयः_Default_Cursor(HAIKU_CreateDefaultCursor());
}

तार्किक HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    यदि (!SDL_InitBeApp()) {
        प्रत्यागम असत्य;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_सङ्कलय_Keyboard(SDL_DEFAULT_KEYBOARD_ID, रिक्त);
    SDL_सङ्कलय_Mouse(SDL_DEFAULT_MOUSE_ID, रिक्त);

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_आरोपय_Library(_this, रिक्त);
#यदि_अन्तः

    // We're done!
    प्रत्यागम सत्य;
}

शून्य HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
बाह्य "C"
तार्किक HAIKU_OpenURL(ध्रुव वर्ण *url)
{
#यदि B_HAIKU_संस्करणम् <= B_HAIKU_संस्करणम्_1_BETA_5
    BUrl burl(url);
#अन्यथा
    BUrl burl(url, सत्य);
#यदि_अन्तः
    ध्रुव स्थितिः_t rc = burl.OpenWithPreferredApplication(असत्य);
    यदि (rc != B_NO_ERROR) {
        प्रत्यागम SDL_समुच्चयः_Error("URL open failed (err=%d)", (पूर्णाङ्क)rc);
    }
    प्रत्यागम सत्य;
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_HAIKU

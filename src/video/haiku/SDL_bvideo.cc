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

#అన్తర్భావ "SDL_internal.h"
#అన్తర్భావ "../../core/haiku/SDL_BApp.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_HAIKU

#అన్తర్భావ "SDL_BWin.h"
#అన్తర్భావ <Url.h>

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

#అన్తర్భావ "SDL_bkeyboard.h"
#అన్తర్భావ "SDL_bwindow.h"
#అన్తర్భావ "SDL_bclipboard.h"
#అన్తర్భావ "SDL_bvideo.h"
#అన్తర్భావ "SDL_bopengl.h"
#అన్తర్భావ "SDL_bmodes.h"
#అన్తర్భావ "SDL_bframebuffer.h"
#అన్తర్భావ "SDL_bevents.h"
#అన్తర్భావ "SDL_bmessagebox.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

స్థిర SDL_INLINE SDL_BWin *గమ్యం_Be_Win(SDL_కిటికీ *కిటికీ) {
    తిరిగి (SDL_BWin *)(కిటికీ->అంతర్గత);
}

స్థిర SDL_VideoDevice * HAIKU_CreateDevice(శూన్య)
{
    SDL_VideoDevice *device;

    // Initialize all variables that we clean on shutdown
    device = (SDL_VideoDevice *) SDL_calloc(1, పరిమాణం(SDL_VideoDevice));

    device->అంతర్గత = ఖాళీ; /* FIXME: Is this the cause of some of the
                                  SDL_Quit() errors? */

// TODO: Figure out if any initialization needs to go here

    // Set the function pointers
    device->VideoInit = HAIKU_VideoInit;
    device->VideoQuit = HAIKU_VideoQuit;
    device->GetDisplayBounds = HAIKU_GetDisplayBounds;
    device->GetDisplayModes = HAIKU_GetDisplayModes;
    device->సమితి_Display_బహుళకం = HAIKU_సమితి_Display_బహుళకం;
    device->PumpEvents = HAIKU_PumpEvents;

    device->CreateSDLWindow = HAIKU_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = HAIKU_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Position = HAIKU_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = HAIKU_సమితి_కిటికీ_కొలత;
    device->Show_కిటికీ = HAIKU_Show_కిటికీ;
    device->Hide_కిటికీ = HAIKU_Hide_కిటికీ;
    device->Raise_కిటికీ = HAIKU_Raise_కిటికీ;
    device->Maximize_కిటికీ = HAIKU_Maximize_కిటికీ;
    device->Minimize_కిటికీ = HAIKU_Minimize_కిటికీ;
    device->Restore_కిటికీ = HAIKU_Restore_కిటికీ;
    device->సమితి_కిటికీ_Bordered = HAIKU_సమితి_కిటికీ_Bordered;
    device->సమితి_కిటికీ_Resizable = HAIKU_సమితి_కిటికీ_Resizable;
    device->సమితి_కిటికీ_Fullscreen = HAIKU_సమితి_కిటికీ_Fullscreen;
    device->సమితి_కిటికీ_Mouse_Grab = HAIKU_సమితి_కిటికీ_Mouse_Grab;
    device->సమితి_కిటికీ_Minimum_కొలత = HAIKU_సమితి_కిటికీ_Minimum_కొలత;
    device->సమితి_కిటికీ_మాతృ = HAIKU_సమితి_కిటికీ_మాతృ;
    device->సమితి_కిటికీ_Modal = HAIKU_సమితి_కిటికీ_Modal;
    device->Destroy_కిటికీ = HAIKU_Destroy_కిటికీ;
    device->Create_కిటికీ_Framebuffer = HAIKU_Create_కిటికీ_Framebuffer;
    device->Update_కిటికీ_Framebuffer = HAIKU_Update_కిటికీ_Framebuffer;
    device->Destroy_కిటికీ_Framebuffer = HAIKU_Destroy_కిటికీ_Framebuffer;

#నిర్వచితమైతే SDL_VIDEO_OPENGL
    device->GL_ఎక్కించు_Library = HAIKU_GL_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = HAIKU_GL_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = HAIKU_GL_UnloadLibrary;
    device->GL_CreateContext = HAIKU_GL_CreateContext;
    device->GL_MakeCurrent = HAIKU_GL_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = HAIKU_GL_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = HAIKU_GL_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = HAIKU_GL_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = HAIKU_GL_DestroyContext;
#అయితే_ముగింపు

    device->సమితి_Clipboard_పాఠ్యం = HAIKU_సమితి_Clipboard_పాఠ్యం;
    device->Get_Clipboard_పాఠ్యం = HAIKU_Get_Clipboard_పాఠ్యం;
    device->Has_Clipboard_పాఠ్యం = HAIKU_Has_Clipboard_పాఠ్యం;

    device->విడుదల = HAIKU_DeleteDevice;

    // TODO: Is this needed?
    device->device_caps = VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER;

    తిరిగి device;
}

VideoBootStrap HAIKU_bootstrap = {
    "haiku", "Haiku graphics",
    HAIKU_CreateDevice,
    HAIKU_Show_సందేశం_Box,
    అబద్ధం
};

శూన్య HAIKU_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    BCursor *cursor;
};

స్థిర SDL_Cursor *HAIKU_Create_Cursor_And_దత్తాంశం(BCursor *bcursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *దత్తాంశం = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
        ఒకవేళ (!దత్తాంశం) {
            SDL_free(cursor);
            తిరిగి ఖాళీ;
        }
        దత్తాంశం->cursor = bcursor;
        cursor->అంతర్గత = దత్తాంశం;
    }
    తిరిగి cursor;
}

స్థిర SDL_Cursor * HAIKU_CreateSystemCursor(SDL_SystemCursor id)
{
    BCursorID cursorId = B_CURSOR_ID_SYSTEM_DEFAULT;

    ఎంపిక(id)
    {
        #నిర్వచించు CURSORCASE(sdlname, bname) స్థితి SDL_SYSTEM_CURSOR_##sdlname: cursorId = B_CURSOR_ID_##bname; ఆపు
        CURSORCASE(DEFAULT, SYSTEM_DEFAULT);
        CURSORCASE(పాఠ్యం_2, I_BEAM);
        CURSORCASE(WAIT, పురోగతి);
        CURSORCASE(CROSSHAIR, CROSS_HAIR);
        CURSORCASE(పురోగతి, పురోగతి);
        CURSORCASE(NWSE_RESIZE, RESIZE_NORTH_WEST_SOUTH_EAST);
        CURSORCASE(NESW_RESIZE, RESIZE_NORTH_EAST_SOUTH_WEST);
        CURSORCASE(EW_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(NS_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(MOVE, MOVE);
        CURSORCASE(NOT_ALLOWED, NOT_ALLOWED);
        CURSORCASE(సూచిక, FOLLOW_LINK);
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
        CURSORCASE(VERTICAL_పాఠ్యం, I_BEAM_HORIZONTAL);
        CURSORCASE(ALIAS, CREATE_LINK);
        CURSORCASE(COPY, COPY);
        CURSORCASE(NO_DROP, NOT_ALLOWED);
        CURSORCASE(GRAB, GRAB);
        CURSORCASE(GRABBING, GRABBING);
        CURSORCASE(నిలువు_RESIZE, RESIZE_EAST_WEST);
        CURSORCASE(అడ్డువరుస_RESIZE, RESIZE_NORTH_SOUTH);
        CURSORCASE(ALL_SCROLL, MOVE);
        CURSORCASE(ZOOM_లోపల, ZOOM_లోపల);
        CURSORCASE(ZOOM_బహిర్గతం, ZOOM_బహిర్గతం);
        #నిర్వచనం_రద్దు CURSORCASE
        అప్రమేయ:
            SDL_assert(0);
            తిరిగి ఖాళీ;
    }

    తిరిగి HAIKU_Create_Cursor_And_దత్తాంశం(కొత్త BCursor(cursorId));
}

స్థిర SDL_Cursor * HAIKU_CreateDefaultCursor()
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    తిరిగి HAIKU_CreateSystemCursor(id);
}

స్థిర శూన్య HAIKU_FreeCursor(SDL_Cursor * cursor)
{
    SDL_Cursor_దత్తాంశం *దత్తాంశం = cursor->అంతర్గత;

    ఒకవేళ (దత్తాంశం) {
        తొలగించు దత్తాంశం->cursor;
    }
    SDL_free(దత్తాంశం);
    SDL_free(cursor);
}

స్థిర SDL_Cursor * HAIKU_CreateCursor(SDL_Surface * surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ఒకవేళ (!converted) {
        తిరిగి ఖాళీ;
    }

	BBitmap *cursorBitmap = కొత్త BBitmap(BRect(0, 0, surface->w - 1, surface->h - 1), B_RGBA32);
	cursorBitmap->సమితి_బిట్లు(converted->pixels, converted->h * converted->pitch, 0, B_RGBA32);
    SDL_DestroySurface(converted);

    తిరిగి HAIKU_Create_Cursor_And_దత్తాంశం(కొత్త BCursor(cursorBitmap, BPoint(hot_x, hot_y)));
}

స్థిర తార్కిక HAIKU_ShowCursor(SDL_Cursor *cursor)
{
	SDL_Mouse *mouse = SDL_GetMouse();

	ఒకవేళ (!mouse) {
		తిరిగి నిజం;
	}

	ఒకవేళ (cursor) {
		BCursor *hCursor = cursor->అంతర్గత->cursor;
		be_app->సమితి_Cursor(hCursor);
	} లేకపోతే {
		BCursor *hCursor = కొత్త BCursor(B_CURSOR_ID_NO_CURSOR);
		be_app->సమితి_Cursor(hCursor);
		తొలగించు hCursor;
	}

	తిరిగి నిజం;
}

స్థిర తార్కిక HAIKU_సమితి_Relative_Mouse_బహుళకం(తార్కిక enabled)
{
    SDL_కిటికీ *కిటికీ = SDL_GetMouseFocus();
    ఒకవేళ (!కిటికీ) {
      తిరిగి నిజం;
    }

	SDL_BWin *bewin = గమ్యం_Be_Win(కిటికీ);
	BView *_SDL_View = bewin->GetGLView();
	ఒకవేళ (!_SDL_View) {
		_SDL_View = bewin->GetView();
		ఒకవేళ (!_SDL_View)
			తిరిగి అబద్ధం;
	}

	bewin->తాళం();
	ఒకవేళ (enabled)
		_SDL_View->సమితి_Event_ముసుగు(B_సూచిక_EVENTS, B_NO_సూచిక_HISTORY);
	లేకపోతే
		_SDL_View->సమితి_Event_ముసుగు(0, 0);
	bewin->Unlock();

    తిరిగి నిజం;
}

స్థిర శూన్య HAIKU_MouseInit(SDL_VideoDevice *_this)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	ఒకవేళ (!mouse) {
		తిరిగి;
	}
	mouse->CreateCursor = HAIKU_CreateCursor;
	mouse->CreateSystemCursor = HAIKU_CreateSystemCursor;
	mouse->ShowCursor = HAIKU_ShowCursor;
	mouse->FreeCursor = HAIKU_FreeCursor;
	mouse->సమితి_Relative_Mouse_బహుళకం = HAIKU_సమితి_Relative_Mouse_బహుళకం;

	SDL_సమితి_Default_Cursor(HAIKU_CreateDefaultCursor());
}

తార్కిక HAIKU_VideoInit(SDL_VideoDevice *_this)
{
    // Initialize the Be Application for appserver interaction
    ఒకవేళ (!SDL_InitBeApp()) {
        తిరిగి అబద్ధం;
    }

    // Initialize video modes
    HAIKU_InitModes(_this);

    // Init the keymap
    HAIKU_InitOSKeymap();

    HAIKU_MouseInit(_this);

    // Assume we have a mouse and keyboard
    SDL_కూడు_Keyboard(SDL_DEFAULT_KEYBOARD_ID, ఖాళీ);
    SDL_కూడు_Mouse(SDL_DEFAULT_MOUSE_ID, ఖాళీ);

#నిర్వచితమైతే SDL_VIDEO_OPENGL
        // testgl application doesn't load library, just tries to load symbols
        // is it correct? if so we have to load library here
    HAIKU_GL_ఎక్కించు_Library(_this, ఖాళీ);
#అయితే_ముగింపు

    // We're done!
    తిరిగి నిజం;
}

శూన్య HAIKU_VideoQuit(SDL_VideoDevice *_this)
{

    HAIKU_QuitModes(_this);

    SDL_QuitBeApp();
}

// just sticking this function in here so it's in a C++ source file.
బాహ్య "C"
తార్కిక HAIKU_OpenURL(స్థిరరాశి అక్షరం *url)
{
#ఒకవేళ B_HAIKU_సంస్కరణ <= B_HAIKU_సంస్కరణ_1_BETA_5
    BUrl burl(url);
#లేకపోతే
    BUrl burl(url, నిజం);
#అయితే_ముగింపు
    స్థిరరాశి స్థితి_t rc = burl.OpenWithPreferredApplication(అబద్ధం);
    ఒకవేళ (rc != B_NO_ERROR) {
        తిరిగి SDL_సమితి_Error("URL open failed (err=%d)", (పూర్ణాంకం)rc);
    }
    తిరిగి నిజం;
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_HAIKU

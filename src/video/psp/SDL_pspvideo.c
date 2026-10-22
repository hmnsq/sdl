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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_keyboard_c.h"

// PSP declarations
#അന്തര്ഭാവ "SDL_pspvideo.h"
#അന്തര്ഭാവ "SDL_pspevents_c.h"
#അന്തര്ഭാവ "SDL_pspgl_c.h"
#അന്തര്ഭാവ "../../render/psp/SDL_render_psp_c.h"

#അന്തര്ഭാവ <psputility.h>
#അന്തര്ഭാവ <pspgu.h>
#അന്തര്ഭാവ <pspdisplay.h>
#അന്തര്ഭാവ <vram.h>

/* unused
static bool PSP_initialized = false;
*/

സ്ഥിതം ശൂന്യം PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

സ്ഥിതം SDL_VideoDevice *PSP_Create(ശൂന്യം)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, വലുപ്പം(SDL_VideoDevice));
    എങ്കിൽ (!device) {
        തിരികെ ശൂന്യ;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, വലുപ്പം(SDL_VideoData));
    എങ്കിൽ (!phdata) {
        SDL_free(device);
        തിരികെ ശൂന്യ;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, വലുപ്പം(SDL_GLDriverData));
    എങ്കിൽ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        തിരികെ ശൂന്യ;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->അക്കം_displays = 0;

    // Set device free function
    device->സ്വതന്ത്രം = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->SetDisplayMode = PSP_SetDisplayMode;
    device->CreateSDLWindow = PSP_CreateWindow;
    device->SetWindowTitle = PSP_SetWindowTitle;
    device->SetWindowPosition = PSP_SetWindowPosition;
    device->SetWindowSize = PSP_SetWindowSize;
    device->ShowWindow = PSP_ShowWindow;
    device->HideWindow = PSP_HideWindow;
    device->RaiseWindow = PSP_RaiseWindow;
    device->MaximizeWindow = PSP_MaximizeWindow;
    device->MinimizeWindow = PSP_MinimizeWindow;
    device->RestoreWindow = PSP_RestoreWindow;
    device->DestroyWindow = PSP_DestroyWindow;
    device->GL_LoadLibrary = PSP_GL_LoadLibrary;
    device->GL_GetProcAddress = PSP_GL_GetProcAddress;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_SetSwapInterval = PSP_GL_SetSwapInterval;
    device->GL_GetSwapInterval = PSP_GL_GetSwapInterval;
    device->GL_SwapWindow = PSP_GL_SwapWindow;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    തിരികെ device;
}

സ്ഥിതം ശൂന്യം configure_dialog(psp_Utility_സന്ദേശം_Dialog_Params *dialog, size_t dialog_size)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_size);
	dialog->base.size = dialog_size;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->base.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->base.buttonSwap);

	// set thread priorities
	// TODO: understand how these work
	dialog->base.soundThread = 0x10;
	dialog->base.graphicsThread = 0x11;
	dialog->base.fontThread = 0x12;
	dialog->base.accessThread = 0x13;
}

സ്ഥിതം ശൂന്യം *setup_temporal_gu(ശൂന്യം *list)
{
    // Using GU_PSM_8888 for the framebuffer
	പൂർണ്ണസംഖ്യ bpp = 4;

	ശൂന്യം *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    ശൂന്യം *backbuffer = doublebuffer;
    ശൂന്യം *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

    sceGuInit();

    sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888, vrelptr(frontbuffer), PSP_FRAME_BUFFER_WIDTH);
    sceGuDispBuffer(PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT, vrelptr(backbuffer), PSP_FRAME_BUFFER_WIDTH);

    sceGuOffset(2048 - (PSP_SCREEN_WIDTH >> 1), 2048 - (PSP_SCREEN_HEIGHT >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT);

    sceGuDisable(GU_DEPTH_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuFinish();
    sceGuSync(0,0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

	തിരികെ doublebuffer;
}

സ്ഥിതം ശൂന്യം term_temporal_gu(ശൂന്യം *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID)
{
	unsigned അക്ഷരം list[64] __attribute__((aligned(64)));
	psp_Utility_സന്ദേശം_Dialog_Params dialog;
	പൂർണ്ണസംഖ്യ status;
    ശൂന്യം *guBuffer = ശൂന്യ;

	// check if it's possible to use existing video context
	എങ്കിൽ (SDL_GetKeyboardFocus() == ശൂന്യ) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, വലുപ്പം(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, വലുപ്പം(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	എങ്കിൽ (messageboxdata->numbuttons > 2)
		തിരികെ SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	എങ്കിൽ (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	എങ്കിൽ (sce_Utility_സന്ദേശം_Dialog_Init_Start(&dialog) != 0)
		തിരികെ SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	ചെയ്യുക
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_സന്ദേശം_Dialog_Get_Status();

		തിരഞ്ഞെടുപ്പ് (status)
		{
			അവസ്ഥ PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_സന്ദേശം_Dialog_Update(1);
				നിർത്തുക;

			അവസ്ഥ PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_സന്ദേശം_Dialog_Shutdown_Start();
				നിർത്തുക;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} ആകുമ്പോൾ (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	എങ്കിൽ (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	എങ്കിൽ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	അല്ലെങ്കിൽ എങ്കിൽ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	അല്ലെങ്കിൽ
		*buttonID = messageboxdata->buttons[0].buttonID;

	തിരികെ true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_ShowMessageBox,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;

    എങ്കിൽ (!PSP_EventInit(_this)) {
        തിരികെ false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    എങ്കിൽ (SDL_AddBasicVideoDisplay(&mode) == 0) {
        തിരികെ false;
    }
    തിരികെ true;
}

ശൂന്യം PSP_VideoQuit(SDL_VideoDevice *_this)
{
    PSP_EventQuit(_this);
}

bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_DisplayMode mode;

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_AddFullscreenDisplayMode(display, &mode);

    // 16 bpp secondary mode
    mode.format = SDL_PIXELFORMAT_BGR565;
    SDL_AddFullscreenDisplayMode(display, &mode);
    തിരികെ true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    തിരികെ true;
}

#define EGLCHK(stmt)                           \
    ചെയ്യുക {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        എങ്കിൽ (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            തിരികെ true;                          \
        }                                      \
    } ആകുമ്പോൾ (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, വലുപ്പം(SDL_WindowData));
    എങ്കിൽ (!wdata) {
        തിരികെ false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    തിരികെ true;
}

ശൂന്യം PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    തിരികെ SDL_Unsupported();
}
ശൂന്യം PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ശൂന്യം PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ശൂന്യം PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ശൂന്യം PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ശൂന്യം PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ശൂന്യം PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ശൂന്യം PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ശൂന്യം PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    തിരികെ true;
}

ശൂന്യം PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    അക്ഷരം list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    പൂർണ്ണസംഖ്യ done = 0;
    പൂർണ്ണസംഖ്യ നിവേശം_text_length = 128;
    ശൂന്യം *received_text = SDL_calloc(നിവേശം_text_length, വലുപ്പം(Uint16));
    എങ്കിൽ (!received_text) {
        തിരികെ;
    }
    ശൂന്യം *received_text_start = received_text;
    ശൂന്യം *text_string = ശൂന്യ;
    ശൂന്യം *string_to_send = ശൂന്യ;

    SDL_iconv_t iconv = ശൂന്യ;
    size_t outbytesleft = നിവേശം_text_length;
    size_t inbytesleft = നിവേശം_text_length * വലുപ്പം(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.വരികൾ = 1;
    data.unk_24 = 1;
    തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Type(props)) {
    സ്ഥിരസ്ഥിതി:
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        നിർത്തുക;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_സംഖ്യ_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        നിർത്തുക;
    }
    data.desc = ശൂന്യ;
    data.intext = ശൂന്യ;
    data.outtextlength = നിവേശം_text_length;
    data.outtextlimit = നിവേശം_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = വലുപ്പം(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
    params.base.graphicsThread = 17;
    params.base.accessThread = 19;
    params.base.fontThread = 18;
    params.base.soundThread = 16;
    params.datacount = 1;
    params.data = &data;

    sceUtilityOskInitStart(&params);

    SDL_SendScreenKeyboardShown();

    ആകുമ്പോൾ (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        എങ്കിൽ (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        തിരഞ്ഞെടുപ്പ് (sceUtilityOskGetStatus()) {
        അവസ്ഥ PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            നിർത്തുക;
        അവസ്ഥ PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            നിർത്തുക;
        അവസ്ഥ PSP_UTILITY_DIALOG_NONE:
            done = 1;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            നിർത്തുക;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    എങ്കിൽ ((size_t)iconv == SDL_ICONV_ERROR) {
        പോകുക done;
    }

    string_to_send = SDL_calloc(നിവേശം_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    എങ്കിൽ (!string_to_send) {
        SDL_iconv_close(iconv);
        പോകുക done;
    }

    text_string = string_to_send;
    outbytesleft = നിവേശം_text_length * 3;
    iconv_result = SDL_iconv(iconv, (സ്ഥിരം അക്ഷരം **)&received_text, (size_t *)&inbytesleft, (അക്ഷരം **)&text_string, &outbytesleft);
    എങ്കിൽ (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

ശൂന്യം PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

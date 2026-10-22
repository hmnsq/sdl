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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../events/SDL_keyboard_c.h"

// PSP declarations
#அந்தர்பாவ "SDL_pspvideo.h"
#அந்தர்பாவ "SDL_pspevents_c.h"
#அந்தர்பாவ "SDL_pspgl_c.h"
#அந்தர்பாவ "../../render/psp/SDL_render_psp_c.h"

#அந்தர்பாவ <psputility.h>
#அந்தர்பாவ <pspgu.h>
#அந்தர்பாவ <pspdisplay.h>
#அந்தர்பாவ <vram.h>

/* unused
static bool PSP_initialized = false;
*/

நிலையான வெறுமை PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

நிலையான SDL_VideoDevice *PSP_Create(வெறுமை)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, அளவு(SDL_VideoDevice));
    எனில் (!device) {
        திரும்பு வெற்று;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, அளவு(SDL_VideoData));
    எனில் (!phdata) {
        SDL_free(device);
        திரும்பு வெற்று;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, அளவு(SDL_GLDriverData));
    எனில் (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        திரும்பு வெற்று;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->இலக்கம்_displays = 0;

    // Set device free function
    device->விடுவி = PSP_Destroy;

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

    திரும்பு device;
}

நிலையான வெறுமை configure_dialog(psp_Utility_செய்தி_Dialog_Params *dialog, size_t dialog_size)
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

நிலையான வெறுமை *setup_temporal_gu(வெறுமை *list)
{
    // Using GU_PSM_8888 for the framebuffer
	முழு bpp = 4;

	வெறுமை *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    வெறுமை *backbuffer = doublebuffer;
    வெறுமை *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

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

	திரும்பு doublebuffer;
}

நிலையான வெறுமை term_temporal_gu(வெறுமை *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID)
{
	unsigned எழுத்து list[64] __attribute__((aligned(64)));
	psp_Utility_செய்தி_Dialog_Params dialog;
	முழு status;
    வெறுமை *guBuffer = வெற்று;

	// check if it's possible to use existing video context
	எனில் (SDL_GetKeyboardFocus() == வெற்று) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, அளவு(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, அளவு(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	எனில் (messageboxdata->numbuttons > 2)
		திரும்பு SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	எனில் (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	எனில் (sce_Utility_செய்தி_Dialog_Init_Start(&dialog) != 0)
		திரும்பு SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	செய்
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_செய்தி_Dialog_Get_Status();

		தேர்வு (status)
		{
			நிலை PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_செய்தி_Dialog_Update(1);
				நிறுத்து;

			நிலை PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_செய்தி_Dialog_Shutdown_Start();
				நிறுத்து;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} போது (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	எனில் (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	எனில் (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	இல்லையெனில் எனில் (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	இல்லையெனில்
		*buttonID = messageboxdata->buttons[0].buttonID;

	திரும்பு true;
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

    எனில் (!PSP_EventInit(_this)) {
        திரும்பு false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    எனில் (SDL_AddBasicVideoDisplay(&mode) == 0) {
        திரும்பு false;
    }
    திரும்பு true;
}

வெறுமை PSP_VideoQuit(SDL_VideoDevice *_this)
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
    திரும்பு true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    திரும்பு true;
}

#define EGLCHK(stmt)                           \
    செய் {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        எனில் (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            திரும்பு true;                          \
        }                                      \
    } போது (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, அளவு(SDL_WindowData));
    எனில் (!wdata) {
        திரும்பு false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    திரும்பு true;
}

வெறுமை PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    திரும்பு SDL_Unsupported();
}
வெறுமை PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
வெறுமை PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    திரும்பு true;
}

வெறுமை PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    எழுத்து list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    முழு done = 0;
    முழு உள்ளீடு_text_length = 128;
    வெறுமை *received_text = SDL_calloc(உள்ளீடு_text_length, அளவு(Uint16));
    எனில் (!received_text) {
        திரும்பு;
    }
    வெறுமை *received_text_start = received_text;
    வெறுமை *text_string = வெற்று;
    வெறுமை *string_to_send = வெற்று;

    SDL_iconv_t iconv = வெற்று;
    size_t outbytesleft = உள்ளீடு_text_length;
    size_t inbytesleft = உள்ளீடு_text_length * அளவு(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.வரிகள் = 1;
    data.unk_24 = 1;
    தேர்வு (SDL_Get_Text_உள்ளீடு_Type(props)) {
    இயல்பு:
    நிலை SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_எண்:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        நிறுத்து;
    நிலை SDL_TEXTINPUT_TYPE_எண்_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        நிறுத்து;
    }
    data.desc = வெற்று;
    data.intext = வெற்று;
    data.outtextlength = உள்ளீடு_text_length;
    data.outtextlimit = உள்ளீடு_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = அளவு(params);
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

    போது (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        எனில் (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        தேர்வு (sceUtilityOskGetStatus()) {
        நிலை PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            நிறுத்து;
        நிலை PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            நிறுத்து;
        நிலை PSP_UTILITY_DIALOG_NONE:
            done = 1;
            நிறுத்து;
        இயல்பு:
            நிறுத்து;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    எனில் ((size_t)iconv == SDL_ICONV_ERROR) {
        செல் done;
    }

    string_to_send = SDL_calloc(உள்ளீடு_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    எனில் (!string_to_send) {
        SDL_iconv_close(iconv);
        செல் done;
    }

    text_string = string_to_send;
    outbytesleft = உள்ளீடு_text_length * 3;
    iconv_result = SDL_iconv(iconv, (மாறிலி எழுத்து **)&received_text, (size_t *)&inbytesleft, (எழுத்து **)&text_string, &outbytesleft);
    எனில் (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

வெறுமை PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

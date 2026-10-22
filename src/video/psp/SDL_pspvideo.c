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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"

// PSP declarations
#ಅನ್ತರ್ಭಾವ "SDL_pspvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_pspevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_pspgl_c.h"
#ಅನ್ತರ್ಭಾವ "../../render/psp/SDL_render_psp_c.h"

#ಅನ್ತರ್ಭಾವ <psputility.h>
#ಅನ್ತರ್ಭಾವ <pspgu.h>
#ಅನ್ತರ್ಭಾವ <pspdisplay.h>
#ಅನ್ತರ್ಭಾವ <vram.h>

/* unused
static bool PSP_initialized = false;
*/

ಸ್ಥಿರ ಶೂನ್ಯ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *PSP_Create(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (!device) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoData));
    ಯದಿ (!phdata) {
        SDL_free(device);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_GLDriverData));
    ಯದಿ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಮುಕ್ತ = PSP_Destroy;

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

    ಪ್ರತ್ಯಾಗಮ device;
}

ಸ್ಥಿರ ಶೂನ್ಯ configure_dialog(psp_Utility_ಸಂದೇಶ_Dialog_Params *dialog, size_t dialog_size)
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

ಸ್ಥಿರ ಶೂನ್ಯ *setup_temporal_gu(ಶೂನ್ಯ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	ಪೂರ್ಣಾಙ್ಕ bpp = 4;

	ಶೂನ್ಯ *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    ಶೂನ್ಯ *backbuffer = doublebuffer;
    ಶೂನ್ಯ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

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

	ಪ್ರತ್ಯಾಗಮ doublebuffer;
}

ಸ್ಥಿರ ಶೂನ್ಯ term_temporal_gu(ಶೂನ್ಯ *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
	unsigned ವರ್ಣ list[64] __attribute__((aligned(64)));
	psp_Utility_ಸಂದೇಶ_Dialog_Params dialog;
	ಪೂರ್ಣಾಙ್ಕ status;
    ಶೂನ್ಯ *guBuffer = ರಿಕ್ತ;

	// check if it's possible to use existing video context
	ಯದಿ (SDL_GetKeyboardFocus() == ರಿಕ್ತ) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, ಪರಿಮಾಣ(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, ಪರಿಮಾಣ(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	ಯದಿ (messageboxdata->numbuttons > 2)
		ಪ್ರತ್ಯಾಗಮ SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	ಯದಿ (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	ಯದಿ (sce_Utility_ಸಂದೇಶ_Dialog_Init_Start(&dialog) != 0)
		ಪ್ರತ್ಯಾಗಮ SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	ಕುರು
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_ಸಂದೇಶ_Dialog_Get_Status();

		ವಿಕಲ್ಪ (status)
		{
			ಪಕ್ಷ PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_ಸಂದೇಶ_Dialog_Update(1);
				ಭಙ್ಗ;

			ಪಕ್ಷ PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_ಸಂದೇಶ_Dialog_Shutdown_Start();
				ಭಙ್ಗ;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} ಯಾವತ್ (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	ಯದಿ (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	ಯದಿ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	ಅನ್ಯಥಾ ಯದಿ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	ಅನ್ಯಥಾ
		*buttonID = messageboxdata->buttons[0].buttonID;

	ಪ್ರತ್ಯಾಗಮ true;
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

    ಯದಿ (!PSP_EventInit(_this)) {
        ಪ್ರತ್ಯಾಗಮ false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    ಯದಿ (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ PSP_VideoQuit(SDL_VideoDevice *_this)
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
    ಪ್ರತ್ಯಾಗಮ true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

#define EGLCHK(stmt)                           \
    ಕುರು {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ಯದಿ (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            ಪ್ರತ್ಯಾಗಮ true;                          \
        }                                      \
    } ಯಾವತ್ (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_WindowData));
    ಯದಿ (!wdata) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}
ಶೂನ್ಯ PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    ವರ್ಣ list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    ಪೂರ್ಣಾಙ್ಕ done = 0;
    ಪೂರ್ಣಾಙ್ಕ ಒಳಹರಿವು_text_length = 128;
    ಶೂನ್ಯ *received_text = SDL_calloc(ಒಳಹರಿವು_text_length, ಪರಿಮಾಣ(Uint16));
    ಯದಿ (!received_text) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    ಶೂನ್ಯ *received_text_start = received_text;
    ಶೂನ್ಯ *text_string = ರಿಕ್ತ;
    ಶೂನ್ಯ *string_to_send = ರಿಕ್ತ;

    SDL_iconv_t iconv = ರಿಕ್ತ;
    size_t outbytesleft = ಒಳಹರಿವು_text_length;
    size_t inbytesleft = ಒಳಹರಿವು_text_length * ಪರಿಮಾಣ(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.ಸಾಲುಗಳು = 1;
    data.unk_24 = 1;
    ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
    ಸ್ವಭಾವ:
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ಭಙ್ಗ;
    }
    data.desc = ರಿಕ್ತ;
    data.intext = ರಿಕ್ತ;
    data.outtextlength = ಒಳಹರಿವು_text_length;
    data.outtextlimit = ಒಳಹರಿವು_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = ಪರಿಮಾಣ(params);
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

    ಯಾವತ್ (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        ಯದಿ (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        ವಿಕಲ್ಪ (sceUtilityOskGetStatus()) {
        ಪಕ್ಷ PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            ಭಙ್ಗ;
        ಪಕ್ಷ PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            ಭಙ್ಗ;
        ಪಕ್ಷ PSP_UTILITY_DIALOG_NONE:
            done = 1;
            ಭಙ್ಗ;
        ಸ್ವಭಾವ:
            ಭಙ್ಗ;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    ಯದಿ ((size_t)iconv == SDL_ICONV_ERROR) {
        ಗಚ್ಛ done;
    }

    string_to_send = SDL_calloc(ಒಳಹರಿವು_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    ಯದಿ (!string_to_send) {
        SDL_iconv_close(iconv);
        ಗಚ್ಛ done;
    }

    text_string = string_to_send;
    outbytesleft = ಒಳಹರಿವು_text_length * 3;
    iconv_result = SDL_iconv(iconv, (ಧ್ರುವ ವರ್ಣ **)&received_text, (size_t *)&inbytesleft, (ವರ್ಣ **)&text_string, &outbytesleft);
    ಯದಿ (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

ಶೂನ್ಯ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

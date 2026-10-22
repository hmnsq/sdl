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

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_keyboard_c.h"

// PSP declarations
#شامل "SDL_pspvideo.h"
#شامل "SDL_pspevents_c.h"
#شامل "SDL_pspgl_c.h"
#شامل "../../render/psp/SDL_render_psp_c.h"

#شامل <psputility.h>
#شامل <pspgu.h>
#شامل <pspdisplay.h>
#شامل <vram.h>

/* unused
static bool PSP_initialized = false;
*/

ایستا تهی PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ایستا SDL_VideoDevice *PSP_Create(تهی)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, اندازه(SDL_VideoDevice));
    اگر (!device) {
        بازگشت پوچ;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, اندازه(SDL_VideoData));
    اگر (!phdata) {
        SDL_free(device);
        بازگشت پوچ;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, اندازه(SDL_GLDriverData));
    اگر (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        بازگشت پوچ;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->رقم_displays = 0;

    // Set device free function
    device->آزاد = PSP_Destroy;

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

    بازگشت device;
}

ایستا تهی configure_dialog(psp_Utility_پیام_Dialog_Params *dialog, size_t dialog_size)
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

ایستا تهی *setup_temporal_gu(تهی *list)
{
    // Using GU_PSM_8888 for the framebuffer
	صحیح bpp = 4;

	تهی *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    تهی *backbuffer = doublebuffer;
    تهی *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

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

	بازگشت doublebuffer;
}

ایستا تهی term_temporal_gu(تهی *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID)
{
	unsigned نویسه list[64] __attribute__((aligned(64)));
	psp_Utility_پیام_Dialog_Params dialog;
	صحیح status;
    تهی *guBuffer = پوچ;

	// check if it's possible to use existing video context
	اگر (SDL_GetKeyboardFocus() == پوچ) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, اندازه(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, اندازه(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	اگر (messageboxdata->numbuttons > 2)
		بازگشت SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	اگر (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	اگر (sce_Utility_پیام_Dialog_Init_Start(&dialog) != 0)
		بازگشت SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	انجامبده
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_پیام_Dialog_Get_Status();

		انتخاب (status)
		{
			حالت PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_پیام_Dialog_Update(1);
				بشکن;

			حالت PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_پیام_Dialog_Shutdown_Start();
				بشکن;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} وقتی (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	اگر (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	اگر (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	وگرنه اگر (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	وگرنه
		*buttonID = messageboxdata->buttons[0].buttonID;

	بازگشت true;
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

    اگر (!PSP_EventInit(_this)) {
        بازگشت false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    اگر (SDL_AddBasicVideoDisplay(&mode) == 0) {
        بازگشت false;
    }
    بازگشت true;
}

تهی PSP_VideoQuit(SDL_VideoDevice *_this)
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
    بازگشت true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    بازگشت true;
}

#define EGLCHK(stmt)                           \
    انجامبده {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        اگر (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            بازگشت true;                          \
        }                                      \
    } وقتی (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, اندازه(SDL_WindowData));
    اگر (!wdata) {
        بازگشت false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    بازگشت true;
}

تهی PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    بازگشت SDL_Unsupported();
}
تهی PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
تهی PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
تهی PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
تهی PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
تهی PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
تهی PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
تهی PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
تهی PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    بازگشت true;
}

تهی PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    نویسه list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    صحیح done = 0;
    صحیح درون_داد_text_length = 128;
    تهی *received_text = SDL_calloc(درون_داد_text_length, اندازه(Uint16));
    اگر (!received_text) {
        بازگشت;
    }
    تهی *received_text_start = received_text;
    تهی *text_string = پوچ;
    تهی *string_to_send = پوچ;

    SDL_iconv_t iconv = پوچ;
    size_t outbytesleft = درون_داد_text_length;
    size_t inbytesleft = درون_داد_text_length * اندازه(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.سطرها = 1;
    data.unk_24 = 1;
    انتخاب (SDL_Get_Text_درون_داد_Type(props)) {
    پیشفرض:
    حالت SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_عدد:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        بشکن;
    حالت SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        بشکن;
    }
    data.desc = پوچ;
    data.intext = پوچ;
    data.outtextlength = درون_داد_text_length;
    data.outtextlimit = درون_داد_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = اندازه(params);
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

    وقتی (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        اگر (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        انتخاب (sceUtilityOskGetStatus()) {
        حالت PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            بشکن;
        حالت PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            بشکن;
        حالت PSP_UTILITY_DIALOG_NONE:
            done = 1;
            بشکن;
        پیشفرض:
            بشکن;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    اگر ((size_t)iconv == SDL_ICONV_ERROR) {
        برو done;
    }

    string_to_send = SDL_calloc(درون_داد_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    اگر (!string_to_send) {
        SDL_iconv_close(iconv);
        برو done;
    }

    text_string = string_to_send;
    outbytesleft = درون_داد_text_length * 3;
    iconv_result = SDL_iconv(iconv, (ثابت نویسه **)&received_text, (size_t *)&inbytesleft, (نویسه **)&text_string, &outbytesleft);
    اگر (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

تهی PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

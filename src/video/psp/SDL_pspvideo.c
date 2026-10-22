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

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"

// PSP declarations
#ضمن "SDL_pspvideo.h"
#ضمن "SDL_pspevents_c.h"
#ضمن "SDL_pspgl_c.h"
#ضمن "../../render/psp/SDL_render_psp_c.h"

#ضمن <psputility.h>
#ضمن <pspgu.h>
#ضمن <pspdisplay.h>
#ضمن <vram.h>

/* unused
static bool PSP_initialized = false;
*/

ساكن فراغ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ساكن SDL_VideoDevice *PSP_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, حجم(SDL_VideoData));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, حجم(SDL_GLDriverData));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->ژمارە_displays = 0;

    // Set device free function
    device->حرر = PSP_Destroy;

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

    أرجع device;
}

ساكن فراغ configure_dialog(psp_Utility_پەیام_Dialog_Params *dialog, size_t dialog_size)
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

ساكن فراغ *setup_temporal_gu(فراغ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	صحيح bpp = 4;

	فراغ *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    فراغ *backbuffer = doublebuffer;
    فراغ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

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

	أرجع doublebuffer;
}

ساكن فراغ term_temporal_gu(فراغ *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID)
{
	unsigned حرف list[64] __attribute__((aligned(64)));
	psp_Utility_پەیام_Dialog_Params dialog;
	صحيح status;
    فراغ *guBuffer = عدم;

	// check if it's possible to use existing video context
	إذا (SDL_GetKeyboardFocus() == عدم) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, حجم(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, حجم(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	إذا (messageboxdata->numbuttons > 2)
		أرجع SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	إذا (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	إذا (sce_Utility_پەیام_Dialog_Init_Start(&dialog) != 0)
		أرجع SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	افعل
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_پەیام_Dialog_Get_Status();

		بدل (status)
		{
			حالة PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_پەیام_Dialog_Update(1);
				اكسر;

			حالة PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_پەیام_Dialog_Shutdown_Start();
				اكسر;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} طالما (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	إذا (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	وإلا إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	وإلا
		*buttonID = messageboxdata->buttons[0].buttonID;

	أرجع true;
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

    إذا (!PSP_EventInit(_this)) {
        أرجع false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_AddBasicVideoDisplay(&mode) == 0) {
        أرجع false;
    }
    أرجع true;
}

فراغ PSP_VideoQuit(SDL_VideoDevice *_this)
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
    أرجع true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    أرجع true;
}

#define EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            أرجع true;                          \
        }                                      \
    } طالما (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, حجم(SDL_WindowData));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    أرجع true;
}

فراغ PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    أرجع SDL_Unsupported();
}
فراغ PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
فراغ PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
فراغ PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
فراغ PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
فراغ PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
فراغ PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
فراغ PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
فراغ PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    حرف list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    صحيح done = 0;
    صحيح تێخستن_text_length = 128;
    فراغ *received_text = SDL_calloc(تێخستن_text_length, حجم(Uint16));
    إذا (!received_text) {
        أرجع;
    }
    فراغ *received_text_start = received_text;
    فراغ *text_string = عدم;
    فراغ *string_to_send = عدم;

    SDL_iconv_t iconv = عدم;
    size_t outbytesleft = تێخستن_text_length;
    size_t inbytesleft = تێخستن_text_length * حجم(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.هێڵەکان = 1;
    data.unk_24 = 1;
    بدل (SDL_Get_Text_تێخستن_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_ژمار:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_ژمار_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_ژمار_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    }
    data.desc = عدم;
    data.intext = عدم;
    data.outtextlength = تێخستن_text_length;
    data.outtextlimit = تێخستن_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = حجم(params);
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

    طالما (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        إذا (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        بدل (sceUtilityOskGetStatus()) {
        حالة PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            اكسر;
        حالة PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            اكسر;
        حالة PSP_UTILITY_DIALOG_NONE:
            done = 1;
            اكسر;
        افتراضي:
            اكسر;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    إذا ((size_t)iconv == SDL_ICONV_ERROR) {
        اذهب done;
    }

    string_to_send = SDL_calloc(تێخستن_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    إذا (!string_to_send) {
        SDL_iconv_close(iconv);
        اذهب done;
    }

    text_string = string_to_send;
    outbytesleft = تێخستن_text_length * 3;
    iconv_result = SDL_iconv(iconv, (ثابت حرف **)&received_text, (size_t *)&inbytesleft, (حرف **)&text_string, &outbytesleft);
    إذا (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

فراغ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

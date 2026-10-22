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

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"

// PSP declarations
#अन्तर्भाव "SDL_pspvideo.h"
#अन्तर्भाव "SDL_pspevents_c.h"
#अन्तर्भाव "SDL_pspgl_c.h"
#अन्तर्भाव "../../render/psp/SDL_render_psp_c.h"

#अन्तर्भाव <psputility.h>
#अन्तर्भाव <pspgu.h>
#अन्तर्भाव <pspdisplay.h>
#अन्तर्भाव <vram.h>

/* unused
static bool PSP_initialized = false;
*/

स्थिर शून्य PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *PSP_Create(शून्य)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, परिमाण(SDL_VideoData));
    यदि (!phdata) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, परिमाण(SDL_GLDriverData));
    यदि (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        प्रत्यागम रिक्त;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->अंक_displays = 0;

    // Set device free function
    device->मुक्त = PSP_Destroy;

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

    प्रत्यागम device;
}

स्थिर शून्य configure_dialog(psp_Utility_संदेश_Dialog_Params *dialog, size_t dialog_size)
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

स्थिर शून्य *setup_temporal_gu(शून्य *list)
{
    // Using GU_PSM_8888 for the framebuffer
	पूर्णाङ्क bpp = 4;

	शून्य *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    शून्य *backbuffer = doublebuffer;
    शून्य *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

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

	प्रत्यागम doublebuffer;
}

स्थिर शून्य term_temporal_gu(शून्य *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
	unsigned वर्ण list[64] __attribute__((aligned(64)));
	psp_Utility_संदेश_Dialog_Params dialog;
	पूर्णाङ्क status;
    शून्य *guBuffer = रिक्त;

	// check if it's possible to use existing video context
	यदि (SDL_GetKeyboardFocus() == रिक्त) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, परिमाण(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, परिमाण(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	यदि (messageboxdata->numbuttons > 2)
		प्रत्यागम SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	यदि (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	यदि (sce_Utility_संदेश_Dialog_Init_Start(&dialog) != 0)
		प्रत्यागम SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	कुरु
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_संदेश_Dialog_Get_Status();

		विकल्प (status)
		{
			पक्ष PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_संदेश_Dialog_Update(1);
				भङ्ग;

			पक्ष PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_संदेश_Dialog_Shutdown_Start();
				भङ्ग;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} यावत् (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	यदि (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	यदि (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	अन्यथा यदि (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	अन्यथा
		*buttonID = messageboxdata->buttons[0].buttonID;

	प्रत्यागम true;
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

    यदि (!PSP_EventInit(_this)) {
        प्रत्यागम false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    यदि (SDL_AddBasicVideoDisplay(&mode) == 0) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

शून्य PSP_VideoQuit(SDL_VideoDevice *_this)
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
    प्रत्यागम true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    प्रत्यागम true;
}

#define EGLCHK(stmt)                           \
    कुरु {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        यदि (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            प्रत्यागम true;                          \
        }                                      \
    } यावत् (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, परिमाण(SDL_WindowData));
    यदि (!wdata) {
        प्रत्यागम false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    प्रत्यागम true;
}

शून्य PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    प्रत्यागम SDL_Unsupported();
}
शून्य PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
शून्य PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
शून्य PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
शून्य PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
शून्य PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
शून्य PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
शून्य PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
शून्य PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    प्रत्यागम true;
}

शून्य PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    वर्ण list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    पूर्णाङ्क done = 0;
    पूर्णाङ्क निवेश_text_length = 128;
    शून्य *received_text = SDL_calloc(निवेश_text_length, परिमाण(Uint16));
    यदि (!received_text) {
        प्रत्यागम;
    }
    शून्य *received_text_start = received_text;
    शून्य *text_string = रिक्त;
    शून्य *string_to_send = रिक्त;

    SDL_iconv_t iconv = रिक्त;
    size_t outbytesleft = निवेश_text_length;
    size_t inbytesleft = निवेश_text_length * परिमाण(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.पंक्तियाँ = 1;
    data.unk_24 = 1;
    विकल्प (SDL_Get_Text_निवेश_Type(props)) {
    स्वभाव:
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_संख्या:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        भङ्ग;
    }
    data.desc = रिक्त;
    data.intext = रिक्त;
    data.outtextlength = निवेश_text_length;
    data.outtextlimit = निवेश_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = परिमाण(params);
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

    यावत् (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        यदि (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        विकल्प (sceUtilityOskGetStatus()) {
        पक्ष PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            भङ्ग;
        पक्ष PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            भङ्ग;
        पक्ष PSP_UTILITY_DIALOG_NONE:
            done = 1;
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    यदि ((size_t)iconv == SDL_ICONV_ERROR) {
        गच्छ done;
    }

    string_to_send = SDL_calloc(निवेश_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    यदि (!string_to_send) {
        SDL_iconv_close(iconv);
        गच्छ done;
    }

    text_string = string_to_send;
    outbytesleft = निवेश_text_length * 3;
    iconv_result = SDL_iconv(iconv, (ध्रुव वर्ण **)&received_text, (size_t *)&inbytesleft, (वर्ण **)&text_string, &outbytesleft);
    यदि (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

शून्य PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

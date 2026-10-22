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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_PSP

// SDL internals
#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_keyboard_c.h"

// PSP declarations
#समावेश "SDL_pspvideo.h"
#समावेश "SDL_pspevents_c.h"
#समावेश "SDL_pspgl_c.h"
#समावेश "../../render/psp/SDL_render_psp_c.h"

#समावेश <psputility.h>
#समावेश <pspgu.h>
#समावेश <pspdisplay.h>
#समावेश <vram.h>

/* unused
static bool PSP_initialized = false;
*/

अटल व्योम PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

अटल SDL_VideoDevice *PSP_Create(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *phdata;
    SDL_GLDriver_तथ्य *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!phdata) {
        SDL_free(device);
        वापस शून्य;
    }

    gldata = (SDL_GLDriver_तथ्य *)SDL_calloc(1, माप(SDL_GLDriver_तथ्य));
    अगर (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        वापस शून्य;
    }
    device->gl_तथ्य = gldata;

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
    device->Set_Window_आकार = PSP_Set_Window_आकार;
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

    वापस device;
}

अटल व्योम configure_dialog(psp_Utility_संदेश_Dialog_Params *dialog, माप_प्रकार dialog_आकार)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_आकार);
	dialog->base.आकार = dialog_आकार;

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

अटल व्योम *setup_temporal_gu(व्योम *list)
{
    // Using GU_PSM_8888 for the framebuffer
	पूर्णांक bpp = 4;

	व्योम *doublebuffer = vramalloc(PSP_FRAME_बफर_आकार * bpp * 2);
    व्योम *backbuffer = doublebuffer;
    व्योम *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_बफर_आकार * bpp;

    sceGuInit();

    sceGuStart(GU_DIRECT,list);
	sce_Gu_Draw_बफर(GU_PSM_8888, vrelptr(frontbuffer), PSP_FRAME_बफर_WIDTH);
    sce_Gu_Disp_बफर(PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT, vrelptr(backbuffer), PSP_FRAME_बफर_WIDTH);

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

	वापस doublebuffer;
}

अटल व्योम term_temporal_gu(व्योम *gu_बफर)
{
	sceGuTerm();
	vfree(gu_बफर);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
	अचिन्हित अक्षर list[64] __attribute__((aligned(64)));
	psp_Utility_संदेश_Dialog_Params dialog;
	पूर्णांक status;
    व्योम *gu_बफर = शून्य;

	// check if it's possible to use existing video context
	अगर (SDL_GetKeyboardFocus() == शून्य) {
		gu_बफर = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, माप(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, माप(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	अगर (messageboxdata->numbuttons > 2)
		वापस SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	अगर (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	अगर (sce_Utility_संदेश_Dialog_Init_Start(&dialog) != 0)
		वापस SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	करो
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_बफर_BIT|GU_DEPTH_बफर_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_संदेश_Dialog_Get_Status();

		चयन (status)
		{
			हाल PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_संदेश_Dialog_Update(1);
				अवरोध;

			हाल PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_संदेश_Dialog_Shutdown_Start();
				अवरोध;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} जबतक (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	अगर (gu_बफर)
	{
		term_temporal_gu(gu_बफर);
	}

	// success
	अगर (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_परिणाम_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	अन्यथा अगर (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_परिणाम_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	अन्यथा
		*buttonID = messageboxdata->buttons[0].buttonID;

	वापस true;
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

    अगर (!PSP_EventInit(_this)) {
        वापस false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    अगर (SDL_AddBasicVideoDisplay(&mode) == 0) {
        वापस false;
    }
    वापस true;
}

व्योम PSP_VideoQuit(SDL_VideoDevice *_this)
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
    वापस true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    वापस true;
}

#घोषणा EGLCHK(stmt)                           \
    करो {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        अगर (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            वापस true;                          \
        }                                      \
    } जबतक (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_तथ्य *wdata;

    // Allocate window internal data
    wdata = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));
    अगर (!wdata) {
        वापस false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    वापस true;
}

व्योम PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    वापस SDL_Unsupported();
}
व्योम PSP_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    वापस true;
}

व्योम PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    अक्षर list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    पूर्णांक done = 0;
    पूर्णांक निवेश_text_लंबाई = 128;
    व्योम *received_text = SDL_calloc(निवेश_text_लंबाई, माप(Uint16));
    अगर (!received_text) {
        वापस;
    }
    व्योम *received_text_start = received_text;
    व्योम *text_string = शून्य;
    व्योम *string_to_send = शून्य;

    SDL_iconv_t iconv = शून्य;
    माप_प्रकार outbytesleft = निवेश_text_लंबाई;
    माप_प्रकार inbytesleft = निवेश_text_लंबाई * माप(Uint16);
    माप_प्रकार iconv_परिणाम = 0;

    Sce_Utility_Osk_तथ्य तथ्य;
    SceUtilityOskParams params;

    तथ्य.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    तथ्य.पंक्तियाँ = 1;
    तथ्य.unk_24 = 1;
    चयन (SDL_Get_Text_निवेश_Type(props)) {
    शेष:
    हाल SDL_TEXTINPUT_TYPE_TEXT:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_NAME:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
        तथ्य.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        अवरोध;
    }
    तथ्य.desc = शून्य;
    तथ्य.intext = शून्य;
    तथ्य.outtextlength = निवेश_text_लंबाई;
    तथ्य.outtextlimit = निवेश_text_लंबाई;
    तथ्य.outtext = (अचिन्हित लघु *)received_text;

    params.base.आकार = माप(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
    params.base.graphicsThread = 17;
    params.base.accessThread = 19;
    params.base.fontThread = 18;
    params.base.soundThread = 16;
    params.datacount = 1;
    params.तथ्य = &तथ्य;

    sceUtilityOskInitStart(&params);

    SDL_SendScreenKeyboardShown();

    जबतक (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_बफर_BIT);
        अगर (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_बफर_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        चयन (sceUtilityOskGetStatus()) {
        हाल PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            अवरोध;
        हाल PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            अवरोध;
        हाल PSP_UTILITY_DIALOG_NONE:
            done = 1;
            अवरोध;
        शेष:
            अवरोध;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    अगर ((माप_प्रकार)iconv == SDL_ICONV_ERROR) {
        जाओ done;
    }

    string_to_send = SDL_calloc(निवेश_text_लंबाई, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    अगर (!string_to_send) {
        SDL_iconv_close(iconv);
        जाओ done;
    }

    text_string = string_to_send;
    outbytesleft = निवेश_text_लंबाई * 3;
    iconv_परिणाम = SDL_iconv(iconv, (स्थिर अक्षर **)&received_text, (माप_प्रकार *)&inbytesleft, (अक्षर **)&text_string, &outbytesleft);
    अगर (iconv_परिणाम == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

व्योम PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_PSP

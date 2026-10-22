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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"

// PSP declarations
#অন্তর্ভাব "SDL_pspvideo.h"
#অন্তর্ভাব "SDL_pspevents_c.h"
#অন্তর্ভাব "SDL_pspgl_c.h"
#অন্তর্ভাব "../../render/psp/SDL_render_psp_c.h"

#অন্তর্ভাব <psputility.h>
#অন্তর্ভাব <pspgu.h>
#অন্তর্ভাব <pspdisplay.h>
#অন্তর্ভাব <vram.h>

/* unused
static bool PSP_initialized = false;
*/

স্থির শূন্য PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

স্থির SDL_VideoDevice *PSP_Create(শূন্য)
{
    SDL_VideoDevice *device;
    SDL_Video_তথ্য *phdata;
    SDL_GLDriver_তথ্য *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, আকার(SDL_VideoDevice));
    যদি (!device) {
        ফেরত ফাঁকা;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_তথ্য *)SDL_calloc(1, আকার(SDL_Video_তথ্য));
    যদি (!phdata) {
        SDL_free(device);
        ফেরত ফাঁকা;
    }

    gldata = (SDL_GLDriver_তথ্য *)SDL_calloc(1, আকার(SDL_GLDriver_তথ্য));
    যদি (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ফেরত ফাঁকা;
    }
    device->gl_তথ্য = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->অঙ্ক_displays = 0;

    // Set device free function
    device->মুক্ত = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->SetDisplayMode = PSP_SetDisplayMode;
    device->CreateSDLWindow = PSP_CreateWindow;
    device->SetWindowTitle = PSP_SetWindowTitle;
    device->SetWindowPosition = PSP_SetWindowPosition;
    device->Set_Window_আকার = PSP_Set_Window_আকার;
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

    ফেরত device;
}

স্থির শূন্য configure_dialog(psp_Utility_বার্তা_Dialog_Params *dialog, size_t dialog_আকার)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_আকার);
	dialog->base.আকার_2 = dialog_আকার;

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

স্থির শূন্য *setup_temporal_gu(শূন্য *list)
{
    // Using GU_PSM_8888 for the framebuffer
	পূর্ণসংখ্যা bpp = 4;

	শূন্য *doublebuffer = vramalloc(PSP_FRAME_বাফার_আকার * bpp * 2);
    শূন্য *backbuffer = doublebuffer;
    শূন্য *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_বাফার_আকার * bpp;

    sceGuInit();

    sceGuStart(GU_DIRECT,list);
	sce_Gu_Draw_বাফার(GU_PSM_8888, vrelptr(frontbuffer), PSP_FRAME_বাফার_WIDTH);
    sce_Gu_Disp_বাফার(PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT, vrelptr(backbuffer), PSP_FRAME_বাফার_WIDTH);

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

	ফেরত doublebuffer;
}

স্থির শূন্য term_temporal_gu(শূন্য *gu_বাফার)
{
	sceGuTerm();
	vfree(gu_বাফার);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID)
{
	unsigned অক্ষর list[64] __attribute__((aligned(64)));
	psp_Utility_বার্তা_Dialog_Params dialog;
	পূর্ণসংখ্যা status;
    শূন্য *gu_বাফার = ফাঁকা;

	// check if it's possible to use existing video context
	যদি (SDL_GetKeyboardFocus() == ফাঁকা) {
		gu_বাফার = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, আকার(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, আকার(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	যদি (messageboxdata->numbuttons > 2)
		ফেরত SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	যদি (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	যদি (sce_Utility_বার্তা_Dialog_Init_Start(&dialog) != 0)
		ফেরত SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	করো
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_বাফার_BIT|GU_DEPTH_বাফার_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_বার্তা_Dialog_Get_Status();

		নির্বাচন (status)
		{
			ক্ষেত্র PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_বার্তা_Dialog_Update(1);
				বিরতি;

			ক্ষেত্র PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_বার্তা_Dialog_Shutdown_Start();
				বিরতি;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} যখন (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	যদি (gu_বাফার)
	{
		term_temporal_gu(gu_বাফার);
	}

	// success
	যদি (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ফলাফল_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	অন্যথা যদি (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ফলাফল_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	অন্যথা
		*buttonID = messageboxdata->buttons[0].buttonID;

	ফেরত true;
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

    যদি (!PSP_EventInit(_this)) {
        ফেরত false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    যদি (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ফেরত false;
    }
    ফেরত true;
}

শূন্য PSP_VideoQuit(SDL_VideoDevice *_this)
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
    ফেরত true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ফেরত true;
}

#define EGLCHK(stmt)                           \
    করো {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        যদি (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            ফেরত true;                          \
        }                                      \
    } যখন (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_তথ্য *wdata;

    // Allocate window internal data
    wdata = (SDL_Window_তথ্য *)SDL_calloc(1, আকার(SDL_Window_তথ্য));
    যদি (!wdata) {
        ফেরত false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    ফেরত true;
}

শূন্য PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    ফেরত SDL_Unsupported();
}
শূন্য PSP_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
শূন্য PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ফেরত true;
}

শূন্য PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    অক্ষর list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    পূর্ণসংখ্যা done = 0;
    পূর্ণসংখ্যা প্রবেশ_text_দৈর্ঘ্য = 128;
    শূন্য *received_text = SDL_calloc(প্রবেশ_text_দৈর্ঘ্য, আকার(Uint16));
    যদি (!received_text) {
        ফেরত;
    }
    শূন্য *received_text_start = received_text;
    শূন্য *text_string = ফাঁকা;
    শূন্য *string_to_send = ফাঁকা;

    SDL_iconv_t iconv = ফাঁকা;
    size_t outbytesleft = প্রবেশ_text_দৈর্ঘ্য;
    size_t inbytesleft = প্রবেশ_text_দৈর্ঘ্য * আকার(Uint16);
    size_t iconv_ফলাফল = 0;

    Sce_Utility_Osk_তথ্য তথ্য;
    SceUtilityOskParams params;

    তথ্য.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    তথ্য.সারিগুলি = 1;
    তথ্য.unk_24 = 1;
    নির্বাচন (SDL_Get_Text_প্রবেশ_Type(props)) {
    পূর্বনির্ধারিত:
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_NAME:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_HIDDEN:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        বিরতি;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_সংখ্যা_PASSWORD_VISIBLE:
        তথ্য.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        বিরতি;
    }
    তথ্য.desc = ফাঁকা;
    তথ্য.intext = ফাঁকা;
    তথ্য.outtextlength = প্রবেশ_text_দৈর্ঘ্য;
    তথ্য.outtextlimit = প্রবেশ_text_দৈর্ঘ্য;
    তথ্য.outtext = (unsigned short *)received_text;

    params.base.আকার_2 = আকার(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
    params.base.graphicsThread = 17;
    params.base.accessThread = 19;
    params.base.fontThread = 18;
    params.base.soundThread = 16;
    params.datacount = 1;
    params.তথ্য = &তথ্য;

    sceUtilityOskInitStart(&params);

    SDL_SendScreenKeyboardShown();

    যখন (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_বাফার_BIT);
        যদি (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_বাফার_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        নির্বাচন (sceUtilityOskGetStatus()) {
        ক্ষেত্র PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            বিরতি;
        ক্ষেত্র PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            বিরতি;
        ক্ষেত্র PSP_UTILITY_DIALOG_NONE:
            done = 1;
            বিরতি;
        পূর্বনির্ধারিত:
            বিরতি;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    যদি ((size_t)iconv == SDL_ICONV_ERROR) {
        যাও done;
    }

    string_to_send = SDL_calloc(প্রবেশ_text_দৈর্ঘ্য, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    যদি (!string_to_send) {
        SDL_iconv_close(iconv);
        যাও done;
    }

    text_string = string_to_send;
    outbytesleft = প্রবেশ_text_দৈর্ঘ্য * 3;
    iconv_ফলাফল = SDL_iconv(iconv, (ধ্রুবক অক্ষর **)&received_text, (size_t *)&inbytesleft, (অক্ষর **)&text_string, &outbytesleft);
    যদি (iconv_ফলাফল == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

শূন্য PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

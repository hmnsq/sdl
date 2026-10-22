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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"

// PSP declarations
#ଅନ୍ତର୍ଭାଵ "SDL_pspvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_pspevents_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_pspgl_c.h"
#ଅନ୍ତର୍ଭାଵ "../../render/psp/SDL_render_psp_c.h"

#ଅନ୍ତର୍ଭାଵ <psputility.h>
#ଅନ୍ତର୍ଭାଵ <pspgu.h>
#ଅନ୍ତର୍ଭାଵ <pspdisplay.h>
#ଅନ୍ତର୍ଭାଵ <vram.h>

/* unused
static bool PSP_initialized = false;
*/

ସ୍ଥିର ଶୂନ୍ୟ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ସ୍ଥିର SDL_VideoDevice *PSP_Create(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, ଆକାର(SDL_VideoData));
    ଯଦି (!phdata) {
        SDL_free(device);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, ଆକାର(SDL_GLDriverData));
    ଯଦି (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->ଅଙ୍କ_displays = 0;

    // Set device free function
    device->ମୁକ୍ତ = PSP_Destroy;

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

    ଫେରନ୍ତୁ device;
}

ସ୍ଥିର ଶୂନ୍ୟ configure_dialog(psp_Utility_ସନ୍ଦେଶ_Dialog_Params *dialog, size_t dialog_size)
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

ସ୍ଥିର ଶୂନ୍ୟ *setup_temporal_gu(ଶୂନ୍ୟ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା bpp = 4;

	ଶୂନ୍ୟ *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    ଶୂନ୍ୟ *backbuffer = doublebuffer;
    ଶୂନ୍ୟ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

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

	ଫେରନ୍ତୁ doublebuffer;
}

ସ୍ଥିର ଶୂନ୍ୟ term_temporal_gu(ଶୂନ୍ୟ *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID)
{
	unsigned ଅକ୍ଷର list[64] __attribute__((aligned(64)));
	psp_Utility_ସନ୍ଦେଶ_Dialog_Params dialog;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା status;
    ଶୂନ୍ୟ *guBuffer = ଖାଲି;

	// check if it's possible to use existing video context
	ଯଦି (SDL_GetKeyboardFocus() == ଖାଲି) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, ଆକାର(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, ଆକାର(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	ଯଦି (messageboxdata->numbuttons > 2)
		ଫେରନ୍ତୁ SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	ଯଦି (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	ଯଦି (sce_Utility_ସନ୍ଦେଶ_Dialog_Init_Start(&dialog) != 0)
		ଫେରନ୍ତୁ SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	କର
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_ସନ୍ଦେଶ_Dialog_Get_Status();

		ବାଛ (status)
		{
			ସ୍ଥିତି PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_ସନ୍ଦେଶ_Dialog_Update(1);
				ଭାଙ୍ଗ;

			ସ୍ଥିତି PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_ସନ୍ଦେଶ_Dialog_Shutdown_Start();
				ଭାଙ୍ଗ;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} ଯେତେବେଳେ (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	ଯଦି (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	ଯଦି (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	ଅନ୍ୟଥା ଯଦି (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	ଅନ୍ୟଥା
		*buttonID = messageboxdata->buttons[0].buttonID;

	ଫେରନ୍ତୁ true;
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

    ଯଦି (!PSP_EventInit(_this)) {
        ଫେରନ୍ତୁ false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    ଯଦି (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ PSP_VideoQuit(SDL_VideoDevice *_this)
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
    ଫେରନ୍ତୁ true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    ଫେରନ୍ତୁ true;
}

#define EGLCHK(stmt)                           \
    କର {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ଯଦି (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            ଫେରନ୍ତୁ true;                          \
        }                                      \
    } ଯେତେବେଳେ (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, ଆକାର(SDL_WindowData));
    ଯଦି (!wdata) {
        ଫେରନ୍ତୁ false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}
ଶୂନ୍ୟ PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    ଅକ୍ଷର list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା done = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ନିବେଶ_text_length = 128;
    ଶୂନ୍ୟ *received_text = SDL_calloc(ନିବେଶ_text_length, ଆକାର(Uint16));
    ଯଦି (!received_text) {
        ଫେରନ୍ତୁ;
    }
    ଶୂନ୍ୟ *received_text_start = received_text;
    ଶୂନ୍ୟ *text_string = ଖାଲି;
    ଶୂନ୍ୟ *string_to_send = ଖାଲି;

    SDL_iconv_t iconv = ଖାଲି;
    size_t outbytesleft = ନିବେଶ_text_length;
    size_t inbytesleft = ନିବେଶ_text_length * ଆକାର(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.ଧାଡ଼ିଗୁଡ଼ିକ = 1;
    data.unk_24 = 1;
    ବାଛ (SDL_Get_Text_ନିବେଶ_Type(props)) {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ଭାଙ୍ଗ;
    }
    data.desc = ଖାଲି;
    data.intext = ଖାଲି;
    data.outtextlength = ନିବେଶ_text_length;
    data.outtextlimit = ନିବେଶ_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = ଆକାର(params);
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

    ଯେତେବେଳେ (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        ଯଦି (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        ବାଛ (sceUtilityOskGetStatus()) {
        ସ୍ଥିତି PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            ଭାଙ୍ଗ;
        ସ୍ଥିତି PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            ଭାଙ୍ଗ;
        ସ୍ଥିତି PSP_UTILITY_DIALOG_NONE:
            done = 1;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    ଯଦି ((size_t)iconv == SDL_ICONV_ERROR) {
        ଯାଅ done;
    }

    string_to_send = SDL_calloc(ନିବେଶ_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    ଯଦି (!string_to_send) {
        SDL_iconv_close(iconv);
        ଯାଅ done;
    }

    text_string = string_to_send;
    outbytesleft = ନିବେଶ_text_length * 3;
    iconv_result = SDL_iconv(iconv, (ଅଚଳ ଅକ୍ଷର **)&received_text, (size_t *)&inbytesleft, (ଅକ୍ଷର **)&text_string, &outbytesleft);
    ଯଦି (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

ଶୂନ୍ୟ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

// SDL internals
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../events/SDL_keyboard_c.h"

// PSP declarations
#અન્તર્ભાવ "SDL_pspvideo.h"
#અન્તર્ભાવ "SDL_pspevents_c.h"
#અન્તર્ભાવ "SDL_pspgl_c.h"
#અન્તર્ભાવ "../../render/psp/SDL_render_psp_c.h"

#અન્તર્ભાવ <psputility.h>
#અન્તર્ભાવ <pspgu.h>
#અન્તર્ભાવ <pspdisplay.h>
#અન્તર્ભાવ <vram.h>

/* unused
static bool PSP_initialized = false;
*/

સ્થિર શૂન્ય PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

સ્થિર SDL_VideoDevice *PSP_Create(શૂન્ય)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
    SDL_GLDriverData *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, કદ(SDL_VideoDevice));
    જો (!device) {
        પાછા ખાલી;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, કદ(SDL_VideoData));
    જો (!phdata) {
        SDL_free(device);
        પાછા ખાલી;
    }

    gldata = (SDL_GLDriverData *)SDL_calloc(1, કદ(SDL_GLDriverData));
    જો (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        પાછા ખાલી;
    }
    device->gl_data = gldata;

    device->internal = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->અંક_displays = 0;

    // Set device free function
    device->મુક્ત = PSP_Destroy;

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

    પાછા device;
}

સ્થિર શૂન્ય configure_dialog(psp_Utility_સંદેશ_Dialog_Params *dialog, size_t dialog_size)
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

સ્થિર શૂન્ય *setup_temporal_gu(શૂન્ય *list)
{
    // Using GU_PSM_8888 for the framebuffer
	પૂર્ણાંક bpp = 4;

	શૂન્ય *doublebuffer = vramalloc(PSP_FRAME_BUFFER_SIZE * bpp * 2);
    શૂન્ય *backbuffer = doublebuffer;
    શૂન્ય *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_BUFFER_SIZE * bpp;

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

	પાછા doublebuffer;
}

સ્થિર શૂન્ય term_temporal_gu(શૂન્ય *guBuffer)
{
	sceGuTerm();
	vfree(guBuffer);
	sceDisplayWaitVblankStart();
}

bool PSP_ShowMessageBox(અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID)
{
	unsigned અક્ષર list[64] __attribute__((aligned(64)));
	psp_Utility_સંદેશ_Dialog_Params dialog;
	પૂર્ણાંક status;
    શૂન્ય *guBuffer = ખાલી;

	// check if it's possible to use existing video context
	જો (SDL_GetKeyboardFocus() == ખાલી) {
		guBuffer = setup_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, કદ(dialog));

	// setup dialog options for text
	dialog.mode = PSP_UTILITY_MSGDIALOG_MODE_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.message, કદ(dialog.message), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->message);

	// too many buttons
	જો (messageboxdata->numbuttons > 2)
		પાછા SDL_SetError("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	જો (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	જો (sce_Utility_સંદેશ_Dialog_Init_Start(&dialog) != 0)
		પાછા SDL_SetError("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	status = PSP_UTILITY_DIALOG_NONE;
	કરો
	{
		sceGuStart(GU_DIRECT, list);
		sceGuClearColor(0);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		status = sce_Utility_સંદેશ_Dialog_Get_Status();

		પસંદગી (status)
		{
			સ્થિતિ PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_સંદેશ_Dialog_Update(1);
				તોડો;

			સ્થિતિ PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_સંદેશ_Dialog_Shutdown_Start();
				તોડો;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} જ્યારે (status != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	જો (guBuffer)
	{
		term_temporal_gu(guBuffer);
	}

	// success
	જો (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	નહીંતર જો (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	નહીંતર
		*buttonID = messageboxdata->buttons[0].buttonID;

	પાછા true;
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

    જો (!PSP_EventInit(_this)) {
        પાછા false;  // error string would already be set
    }

    SDL_zero(mode);
    mode.w = PSP_SCREEN_WIDTH;
    mode.h = PSP_SCREEN_HEIGHT;
    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    જો (SDL_AddBasicVideoDisplay(&mode) == 0) {
        પાછા false;
    }
    પાછા true;
}

શૂન્ય PSP_VideoQuit(SDL_VideoDevice *_this)
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
    પાછા true;
}

bool PSP_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    પાછા true;
}

#define EGLCHK(stmt)                           \
    કરો {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        જો (err != EGL_SUCCESS) {              \
            SDL_SetError("EGL error %d", err); \
            પાછા true;                          \
        }                                      \
    } જ્યારે (0)

bool PSP_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, કદ(SDL_WindowData));
    જો (!wdata) {
        પાછા false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    પાછા true;
}

શૂન્ય PSP_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool PSP_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    પાછા SDL_Unsupported();
}
શૂન્ય PSP_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
શૂન્ય PSP_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
શૂન્ય PSP_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
શૂન્ય PSP_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
શૂન્ય PSP_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
શૂન્ય PSP_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
શૂન્ય PSP_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
શૂન્ય PSP_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    પાછા true;
}

શૂન્ય PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    અક્ષર list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    પૂર્ણાંક done = 0;
    પૂર્ણાંક આગત_text_length = 128;
    શૂન્ય *received_text = SDL_calloc(આગત_text_length, કદ(Uint16));
    જો (!received_text) {
        પાછા;
    }
    શૂન્ય *received_text_start = received_text;
    શૂન્ય *text_string = ખાલી;
    શૂન્ય *string_to_send = ખાલી;

    SDL_iconv_t iconv = ખાલી;
    size_t outbytesleft = આગત_text_length;
    size_t inbytesleft = આગત_text_length * કદ(Uint16);
    size_t iconv_result = 0;

    SceUtilityOskData data;
    SceUtilityOskParams params;

    data.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    data.લીટીઓ = 1;
    data.unk_24 = 1;
    પસંદગી (SDL_Get_Text_આગત_Type(props)) {
    મૂળભૂત:
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા_PASSWORD_HIDDEN:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        તોડો;
    સ્થિતિ SDL_TEXTINPUT_TYPE_સંખ્યા_PASSWORD_VISIBLE:
        data.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        તોડો;
    }
    data.desc = ખાલી;
    data.intext = ખાલી;
    data.outtextlength = આગત_text_length;
    data.outtextlimit = આગત_text_length;
    data.outtext = (unsigned short *)received_text;

    params.base.size = કદ(params);
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

    જ્યારે (!done) {
        sceGuStart(GU_DIRECT, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        જો (sceGuGetStatus(GU_DEPTH_TEST)) {
            sceGuClearDepth(0);
            sceGuClear(GU_DEPTH_BUFFER_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        પસંદગી (sceUtilityOskGetStatus()) {
        સ્થિતિ PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            તોડો;
        સ્થિતિ PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            તોડો;
        સ્થિતિ PSP_UTILITY_DIALOG_NONE:
            done = 1;
            તોડો;
        મૂળભૂત:
            તોડો;
        }
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    જો ((size_t)iconv == SDL_ICONV_ERROR) {
        જાઓ done;
    }

    string_to_send = SDL_calloc(આગત_text_length, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    જો (!string_to_send) {
        SDL_iconv_close(iconv);
        જાઓ done;
    }

    text_string = string_to_send;
    outbytesleft = આગત_text_length * 3;
    iconv_result = SDL_iconv(iconv, (અચલ અક્ષર **)&received_text, (size_t *)&inbytesleft, (અક્ષર **)&text_string, &outbytesleft);
    જો (iconv_result == 0) {
        SDL_SendKeyboardText(string_to_send);
    }

    SDL_iconv_close(iconv);

done:
    SDL_free(string_to_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

શૂન્ય PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
}

#endif // SDL_VIDEO_DRIVER_PSP

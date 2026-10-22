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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_PSP

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

/*अप्रयुक्तम्
static bool PSP_initialized = false;
*/

स्थिर शून्य PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *PSP_Create(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *phdata;
    SDL_GLDriver_दत्त *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!phdata) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }

    gldata = (SDL_GLDriver_दत्त *)SDL_calloc(1, परिमाण(SDL_GLDriver_दत्त));
    यदि (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        प्रत्यागम रिक्त;
    }
    device->gl_दत्त = gldata;

    device->आन्तरिकम् = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->अङ्कः_displays = 0;

    // Set device free function
    device->मुक्त = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->समुच्चयः_Display_बहुलकम् = PSP_समुच्चयः_Display_बहुलकम्;
    device->CreateSDLWindow = PSP_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = PSP_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Position = PSP_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = PSP_समुच्चयः_गवाक्षः_आकार;
    device->Show_गवाक्षः = PSP_Show_गवाक्षः;
    device->Hide_गवाक्षः = PSP_Hide_गवाक्षः;
    device->Raise_गवाक्षः = PSP_Raise_गवाक्षः;
    device->Maximize_गवाक्षः = PSP_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = PSP_Minimize_गवाक्षः;
    device->Restore_गवाक्षः = PSP_Restore_गवाक्षः;
    device->Destroy_गवाक्षः = PSP_Destroy_गवाक्षः;
    device->GL_आरोपय_Library = PSP_GL_आरोपय_Library;
    device->GL_Get_Proc_स्थानाङ्कः = PSP_GL_Get_Proc_स्थानाङ्कः;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = PSP_GL_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = PSP_GL_GetSwapInterval;
    device->GL_Swap_गवाक्षः = PSP_GL_Swap_गवाक्षः;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    प्रत्यागम device;
}

स्थिर शून्य configure_dialog(psp_Utility_सन्देशः_Dialog_Params *dialog, size_t dialog_आकार)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_आकार);
	dialog->आधारः.आकार = dialog_आकार;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->आधारः.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->आधारः.buttonSwap);

	// set thread priorities
	// TODO: understand how these work
	dialog->आधारः.soundThread = 0x10;
	dialog->आधारः.graphicsThread = 0x11;
	dialog->आधारः.fontThread = 0x12;
	dialog->आधारः.accessThread = 0x13;
}

स्थिर शून्य *सज्जता_temporal_gu(शून्य *list)
{
    // Using GU_PSM_8888 for the framebuffer
	पूर्णाङ्क bpp = 4;

	शून्य *doublebuffer = vramalloc(PSP_FRAME_बफर_आकार * bpp * 2);
    शून्य *backbuffer = doublebuffer;
    शून्य *frontbuffer = ((uint8_t *)doublebuffer) + PSP_FRAME_बफर_आकार * bpp;

    sceGuInit();

    sceGuStart(GU_प्रत्यक्षम्,list);
	sce_Gu_Draw_बफर(GU_PSM_8888, vrelptr(frontbuffer), PSP_FRAME_बफर_विस्तारः);
    sce_Gu_Disp_बफर(PSP_SCREEN_विस्तारः, PSP_SCREEN_HEIGHT, vrelptr(backbuffer), PSP_FRAME_बफर_विस्तारः);

    sce_Gu_विस्थापनम्(2048 - (PSP_SCREEN_विस्तारः >> 1), 2048 - (PSP_SCREEN_HEIGHT >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_विस्तारः, PSP_SCREEN_HEIGHT);

    sceGuDisable(GU_गभीरता_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_विस्तारः, PSP_SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuFinish();
    sceGuSync(0,0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

	प्रत्यागम doublebuffer;
}

स्थिर शून्य पदांशः_temporal_gu(शून्य *gu_बफर)
{
	sce_Gu_पदांशः();
	vfree(gu_बफर);
	sceDisplayWaitVblankStart();
}

bool PSP_Show_सन्देशः_Box(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID)
{
	अचिह्नित वर्ण list[64] __attribute__((aligned(64)));
	psp_Utility_सन्देशः_Dialog_Params dialog;
	पूर्णाङ्क स्थितिः;
    शून्य *gu_बफर = रिक्त;

	// check if it's possible to use existing video context
	यदि (SDL_GetKeyboardFocus() == रिक्त) {
		gu_बफर = सज्जता_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, परिमाण(dialog));

	// setup dialog options for text
	dialog.बहुलकम् = PSP_UTILITY_MSGDIALOG_बहुलकम्_TEXT;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.सन्देशः, परिमाण(dialog.सन्देशः), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->सन्देशः);

	// too many buttons
	यदि (messageboxdata->numbuttons > 2)
		प्रत्यागम SDL_समुच्चयः_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	यदि (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	यदि (sce_Utility_सन्देशः_Dialog_Init_Start(&dialog) != 0)
		प्रत्यागम SDL_समुच्चयः_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	स्थितिः = PSP_UTILITY_DIALOG_NONE;
	कुरु
	{
		sceGuStart(GU_प्रत्यक्षम्, list);
		sceGuClearColor(0);
		sce_Gu_Clear_गभीरता(0);
		sceGuClear(GU_COLOR_बफर_BIT|GU_गभीरता_बफर_BIT);
		sceGuFinish();
		sceGuSync(0,0);

		स्थितिः = sce_Utility_सन्देशः_Dialog_Get_स्थितिः();

		विकल्प (स्थितिः)
		{
			पक्ष PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_सन्देशः_Dialog_Update(1);
				भङ्ग;

			पक्ष PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_सन्देशः_Dialog_Shutdown_Start();
				भङ्ग;
		}

		sceDisplayWaitVblankStart();
		sceGuSwapBuffers();

	} यावत् (स्थितिः != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	यदि (gu_बफर)
	{
		पदांशः_temporal_gu(gu_बफर);
	}

	// success
	यदि (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_परिणाम_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	अन्यथा यदि (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_परिणाम_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	अन्यथा
		*buttonID = messageboxdata->buttons[0].buttonID;

	प्रत्यागम true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_Show_सन्देशः_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_बहुलकम् बहुलकम्;

    यदि (!PSP_EventInit(_this)) {
        प्रत्यागम false;  // error string would already be set
    }

    SDL_zero(बहुलकम्);
    बहुलकम्.w = PSP_SCREEN_विस्तारः;
    बहुलकम्.h = PSP_SCREEN_HEIGHT;
    बहुलकम्.refresh_दरः = 60.0f;

    // 32 bpp for default
    बहुलकम्.format = SDL_PIXELFORMAT_ABGR8888;

    यदि (SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्) == 0) {
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
    SDL_Display_बहुलकम् बहुलकम्;

    SDL_zero(बहुलकम्);
    बहुलकम्.w = PSP_SCREEN_विस्तारः;
    बहुलकम्.h = PSP_SCREEN_HEIGHT;
    बहुलकम्.refresh_दरः = 60.0f;

    // 32 bpp for default
    बहुलकम्.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्);

    // 16 bpp secondary mode
    बहुलकम्.format = SDL_PIXELFORMAT_BGR565;
    SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्);
    प्रत्यागम true;
}

bool PSP_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    प्रत्यागम true;
}

#परिभाषय EGLCHK(stmt)                           \
    कुरु {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        यदि (err != EGL_SUCCESS) {              \
            SDL_समुच्चयः_Error("EGL error %d", err); \
            प्रत्यागम true;                          \
        }                                      \
    } यावत् (0)

bool PSP_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *wdata;

    // Allocate window internal data
    wdata = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!wdata) {
        प्रत्यागम false;
    }

    // Setup driver data for this window
    गवाक्षः->आन्तरिकम् = wdata;

    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);

    // Window has been successfully created
    प्रत्यागम true;
}

शून्य PSP_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
bool PSP_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम SDL_Unsupported();
}
शून्य PSP_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य PSP_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य PSP_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य PSP_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य PSP_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य PSP_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य PSP_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य PSP_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    प्रत्यागम true;
}

शून्य PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    वर्ण list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    पूर्णाङ्क समाप्तम् = 0;
    पूर्णाङ्क निवेशः_text_दीर्घता = 128;
    शून्य *received_text = SDL_calloc(निवेशः_text_दीर्घता, परिमाण(Uint16));
    यदि (!received_text) {
        प्रत्यागम;
    }
    शून्य *received_text_start = received_text;
    शून्य *text_string = रिक्त;
    शून्य *string_गन्तव्यम्_send = रिक्त;

    SDL_iconv_t iconv = रिक्त;
    size_t outbytesleft = निवेशः_text_दीर्घता;
    size_t inbytesleft = निवेशः_text_दीर्घता * परिमाण(Uint16);
    size_t iconv_परिणाम = 0;

    Sce_Utility_Osk_दत्त दत्त;
    SceUtilityOskParams params;

    दत्त.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    दत्त.पङ्क्तयः = 1;
    दत्त.unk_24 = 1;
    विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
    स्वभाव:
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_HIDDEN:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_VISIBLE:
        दत्त.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        भङ्ग;
    }
    दत्त.desc = रिक्त;
    दत्त.intext = रिक्त;
    दत्त.outtextlength = निवेशः_text_दीर्घता;
    दत्त.outtextlimit = निवेशः_text_दीर्घता;
    दत्त.outtext = (अचिह्नित ह्रस्व *)received_text;

    params.आधारः.आकार = परिमाण(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.आधारः.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.आधारः.buttonSwap);
    params.आधारः.graphicsThread = 17;
    params.आधारः.accessThread = 19;
    params.आधारः.fontThread = 18;
    params.आधारः.soundThread = 16;
    params.datacount = 1;
    params.दत्त = &दत्त;

    sceUtilityOskInitStart(&params);

    SDL_SendScreenKeyboardShown();

    यावत् (!समाप्तम्) {
        sceGuStart(GU_प्रत्यक्षम्, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_बफर_BIT);
        यदि (sce_Gu_Get_स्थितिः(GU_गभीरता_TEST)) {
            sce_Gu_Clear_गभीरता(0);
            sceGuClear(GU_गभीरता_बफर_BIT);
        }
        sceGuFinish();
        sceGuSync(0, 0);

        विकल्प (sce_Utility_Osk_Get_स्थितिः()) {
        पक्ष PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            भङ्ग;
        पक्ष PSP_UTILITY_DIALOG_QUIT:
            sceUtilityOskShutdownStart();
            भङ्ग;
        पक्ष PSP_UTILITY_DIALOG_NONE:
            समाप्तम् = 1;
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
        गच्छ समाप्तम्;
    }

    string_गन्तव्यम्_send = SDL_calloc(निवेशः_text_दीर्घता, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    यदि (!string_गन्तव्यम्_send) {
        SDL_iconv_close(iconv);
        गच्छ समाप्तम्;
    }

    text_string = string_गन्तव्यम्_send;
    outbytesleft = निवेशः_text_दीर्घता * 3;
    iconv_परिणाम = SDL_iconv(iconv, (ध्रुव वर्ण **)&received_text, (size_t *)&inbytesleft, (वर्ण **)&text_string, &outbytesleft);
    यदि (iconv_परिणाम == 0) {
        SDL_SendKeyboardText(string_गन्तव्यम्_send);
    }

    SDL_iconv_close(iconv);

समाप्तम्:
    SDL_free(string_गन्तव्यम्_send);
    SDL_free(received_text_start);

    SDL_SendScreenKeyboardHidden();
}

शून्य PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_PSP

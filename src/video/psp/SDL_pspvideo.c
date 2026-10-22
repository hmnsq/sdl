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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_PSP

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

/*غیر_مستعمل
static bool PSP_initialized = false;
*/

ساکن خالی PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن SDL_VideoDevice *PSP_Create(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *phdata;
    SDL_GLDriver_ڈیٹا *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!phdata) {
        SDL_free(device);
        واپس تہی;
    }

    gldata = (SDL_GLDriver_ڈیٹا *)SDL_calloc(1, حجم(SDL_GLDriver_ڈیٹا));
    اگر (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        واپس تہی;
    }
    device->gl_ڈیٹا = gldata;

    device->اندرونی_2 = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->آزاد = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->سیٹ_Display_منوال = PSP_سیٹ_Display_منوال;
    device->CreateSDLWindow = PSP_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = PSP_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = PSP_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_سائز = PSP_سیٹ_کھڑکی_سائز;
    device->Show_کھڑکی = PSP_Show_کھڑکی;
    device->Hide_کھڑکی = PSP_Hide_کھڑکی;
    device->Raise_کھڑکی = PSP_Raise_کھڑکی;
    device->Maximize_کھڑکی = PSP_Maximize_کھڑکی;
    device->Minimize_کھڑکی = PSP_Minimize_کھڑکی;
    device->Restore_کھڑکی = PSP_Restore_کھڑکی;
    device->Destroy_کھڑکی = PSP_Destroy_کھڑکی;
    device->GL_بھرو_Library = PSP_GL_بھرو_Library;
    device->GL_Get_Proc_پتہ = PSP_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = PSP_GL_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = PSP_GL_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = PSP_GL_تبادلہ_کھڑکی;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    واپس device;
}

ساکن خالی configure_dialog(psp_Utility_پیغام_Dialog_Params *dialog, size_t dialog_سائز)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_سائز);
	dialog->بنیاد.سائز = dialog_سائز;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->بنیاد.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->بنیاد.button_تبادلہ);

	// set thread priorities
	// TODO: understand how these work
	dialog->بنیاد.soundThread = 0x10;
	dialog->بنیاد.graphicsThread = 0x11;
	dialog->بنیاد.fontThread = 0x12;
	dialog->بنیاد.accessThread = 0x13;
}

ساکن خالی *تیاری_temporal_gu(خالی *list)
{
    // Using GU_PSM_8888 for the framebuffer
	صحیح bpp = 4;

	خالی *doublebuffer = vramalloc(PSP_چوکھٹا_بفر_سائز * bpp * 2);
    خالی *backbuffer = doublebuffer;
    خالی *frontbuffer = ((uint8_t *)doublebuffer) + PSP_چوکھٹا_بفر_سائز * bpp;

    sceGuInit();

    sce_Gu_آغاز(GU_براہ_راست,list);
	sce_Gu_Draw_بفر(GU_PSM_8888, vrelptr(frontbuffer), PSP_چوکھٹا_بفر_چوڑائی);
    sce_Gu_Disp_بفر(PSP_SCREEN_چوڑائی, PSP_SCREEN_اونچائی, vrelptr(backbuffer), PSP_چوکھٹا_بفر_چوڑائی);

    sce_Gu_انحراف(2048 - (PSP_SCREEN_چوڑائی >> 1), 2048 - (PSP_SCREEN_اونچائی >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_چوڑائی, PSP_SCREEN_اونچائی);

    sceGuDisable(GU_گہرائی_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_چوڑائی, PSP_SCREEN_اونچائی);
    sceGuEnable(GU_SCISSOR_TEST);

    sce_Gu_اختتام();
    sceGuSync(0,0);

    sce_Display_Wait_Vblank_آغاز();
    sceGuDisplay(GU_TRUE);

	واپس doublebuffer;
}

ساکن خالی رکن_temporal_gu(خالی *gu_بفر)
{
	sce_Gu_رکن();
	vfree(gu_بفر);
	sce_Display_Wait_Vblank_آغاز();
}

bool PSP_Show_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
	غیرعلامتی حرف list[64] __attribute__((aligned(64)));
	psp_Utility_پیغام_Dialog_Params dialog;
	صحیح حالت_2;
    خالی *gu_بفر = تہی;

	// check if it's possible to use existing video context
	اگر (SDL_GetKeyboardFocus() == تہی) {
		gu_بفر = تیاری_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, حجم(dialog));

	// setup dialog options for text
	dialog.منوال = PSP_UTILITY_MSGDIALOG_منوال_متن;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_متن;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.پیغام, حجم(dialog.پیغام), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->پیغام);

	// too many buttons
	اگر (messageboxdata->numbuttons > 2)
		واپس SDL_سیٹ_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	اگر (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	اگر (sce_Utility_پیغام_Dialog_Init_آغاز(&dialog) != 0)
		واپس SDL_سیٹ_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	حالت_2 = PSP_UTILITY_DIALOG_NONE;
	کرو
	{
		sce_Gu_آغاز(GU_براہ_راست, list);
		sceGuClearColor(0);
		sce_Gu_Clear_گہرائی(0);
		sceGuClear(GU_COLOR_بفر_ثنائی_ہندسہ|GU_گہرائی_بفر_ثنائی_ہندسہ);
		sce_Gu_اختتام();
		sceGuSync(0,0);

		حالت_2 = sce_Utility_پیغام_Dialog_Get_حالت();

		انتخاب (حالت_2)
		{
			حالت PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_پیغام_Dialog_Update(1);
				توڑو;

			حالت PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_پیغام_Dialog_Shutdown_آغاز();
				توڑو;
		}

		sce_Display_Wait_Vblank_آغاز();
		sce_Gu_تبادلہ_Buffers();

	} جب (حالت_2 != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	اگر (gu_بفر)
	{
		رکن_temporal_gu(gu_بفر);
	}

	// success
	اگر (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_نتیجہ_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	ورنہ اگر (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_نتیجہ_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	ورنہ
		*buttonID = messageboxdata->buttons[0].buttonID;

	واپس true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_Show_پیغام_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;

    اگر (!PSP_EventInit(_this)) {
        واپس false;  // error string would already be set
    }

    SDL_zero(منوال);
    منوال.w = PSP_SCREEN_چوڑائی;
    منوال.h = PSP_SCREEN_اونچائی;
    منوال.refresh_شرح = 60.0f;

    // 32 bpp for default
    منوال.format = SDL_PIXELFORMAT_ABGR8888;

    اگر (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        واپس false;
    }
    واپس true;
}

خالی PSP_VideoQuit(SDL_VideoDevice *_this)
{
    PSP_EventQuit(_this);
}

bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_منوال منوال;

    SDL_zero(منوال);
    منوال.w = PSP_SCREEN_چوڑائی;
    منوال.h = PSP_SCREEN_اونچائی;
    منوال.refresh_شرح = 60.0f;

    // 32 bpp for default
    منوال.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال);

    // 16 bpp secondary mode
    منوال.format = SDL_PIXELFORMAT_BGR565;
    SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال);
    واپس true;
}

bool PSP_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    واپس true;
}

#تعریف_کرو EGLCHK(stmt)                           \
    کرو {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        اگر (err != EGL_SUCCESS) {              \
            SDL_سیٹ_Error("EGL error %d", err); \
            واپس true;                          \
        }                                      \
    } جب (0)

bool PSP_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *wdata;

    // Allocate window internal data
    wdata = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (!wdata) {
        واپس false;
    }

    // Setup driver data for this window
    کھڑکی->اندرونی_2 = wdata;

    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    // Window has been successfully created
    واپس true;
}

خالی PSP_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool PSP_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    واپس SDL_Unsupported();
}
خالی PSP_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی PSP_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی PSP_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی PSP_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی PSP_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی PSP_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی PSP_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی PSP_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    واپس true;
}

خالی PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    حرف list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    صحیح مکمل = 0;
    صحیح داخلہ_متن_لمبائی = 128;
    خالی *received_متن = SDL_calloc(داخلہ_متن_لمبائی, حجم(Uint16));
    اگر (!received_متن) {
        واپس;
    }
    خالی *received_متن_آغاز = received_متن;
    خالی *متن_string = تہی;
    خالی *string_مقصد_send = تہی;

    SDL_iconv_t iconv = تہی;
    size_t outbytesleft = داخلہ_متن_لمبائی;
    size_t inbytesleft = داخلہ_متن_لمبائی * حجم(Uint16);
    size_t iconv_نتیجہ = 0;

    Sce_Utility_Osk_ڈیٹا ڈیٹا;
    SceUtilityOskParams params;

    ڈیٹا.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    ڈیٹا.سطریں = 1;
    ڈیٹا.unk_24 = 1;
    انتخاب (SDL_Get_متن_داخلہ_Type(props)) {
    طےشدہ:
    حالت SDL_TEXTINPUT_TYPE_متن:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_NAME:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_EMAIL:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_USERNAME:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
        ڈیٹا.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        توڑو;
    }
    ڈیٹا.desc = تہی;
    ڈیٹا.intext = تہی;
    ڈیٹا.outtextlength = داخلہ_متن_لمبائی;
    ڈیٹا.outtextlimit = داخلہ_متن_لمبائی;
    ڈیٹا.outtext = (غیرعلامتی مختصر *)received_متن;

    params.بنیاد.سائز = حجم(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.بنیاد.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.بنیاد.button_تبادلہ);
    params.بنیاد.graphicsThread = 17;
    params.بنیاد.accessThread = 19;
    params.بنیاد.fontThread = 18;
    params.بنیاد.soundThread = 16;
    params.datacount = 1;
    params.ڈیٹا = &ڈیٹا;

    sce_Utility_Osk_Init_آغاز(&params);

    SDL_SendScreenKeyboardShown();

    جب (!مکمل) {
        sce_Gu_آغاز(GU_براہ_راست, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_بفر_ثنائی_ہندسہ);
        اگر (sce_Gu_Get_حالت(GU_گہرائی_TEST)) {
            sce_Gu_Clear_گہرائی(0);
            sceGuClear(GU_گہرائی_بفر_ثنائی_ہندسہ);
        }
        sce_Gu_اختتام();
        sceGuSync(0, 0);

        انتخاب (sce_Utility_Osk_Get_حالت()) {
        حالت PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            توڑو;
        حالت PSP_UTILITY_DIALOG_QUIT:
            sce_Utility_Osk_Shutdown_آغاز();
            توڑو;
        حالت PSP_UTILITY_DIALOG_NONE:
            مکمل = 1;
            توڑو;
        طےشدہ:
            توڑو;
        }
        sce_Display_Wait_Vblank_آغاز();
        sce_Gu_تبادلہ_Buffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    اگر ((size_t)iconv == SDL_ICONV_ERROR) {
        جاؤ مکمل;
    }

    string_مقصد_send = SDL_calloc(داخلہ_متن_لمبائی, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    اگر (!string_مقصد_send) {
        SDL_iconv_close(iconv);
        جاؤ مکمل;
    }

    متن_string = string_مقصد_send;
    outbytesleft = داخلہ_متن_لمبائی * 3;
    iconv_نتیجہ = SDL_iconv(iconv, (ثابت حرف **)&received_متن, (size_t *)&inbytesleft, (حرف **)&متن_string, &outbytesleft);
    اگر (iconv_نتیجہ == 0) {
        SDL_Send_Keyboard_متن(string_مقصد_send);
    }

    SDL_iconv_close(iconv);

مکمل:
    SDL_free(string_مقصد_send);
    SDL_free(received_متن_آغاز);

    SDL_SendScreenKeyboardHidden();
}

خالی PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}

#اگر_ختم // SDL_VIDEO_DRIVER_PSP

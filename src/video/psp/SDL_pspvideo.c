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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_PSP

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

/*بن_ورتیا
static bool PSP_initialized = false;
*/

ساكن فراغ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *PSP_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *phdata;
    SDL_GLDriver_انکڑے *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    gldata = (SDL_GLDriver_انکڑے *)SDL_calloc(1, حجم(SDL_GLDriver_انکڑے));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_انکڑے = gldata;

    device->اندرونی = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->سیٹ_Display_منوال = PSP_سیٹ_Display_منوال;
    device->CreateSDLWindow = PSP_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = PSP_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = PSP_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_ناپ = PSP_سیٹ_کھڑکی_ناپ;
    device->Show_کھڑکی = PSP_Show_کھڑکی;
    device->Hide_کھڑکی = PSP_Hide_کھڑکی;
    device->Raise_کھڑکی = PSP_Raise_کھڑکی;
    device->Maximize_کھڑکی = PSP_Maximize_کھڑکی;
    device->Minimize_کھڑکی = PSP_Minimize_کھڑکی;
    device->Restore_کھڑکی = PSP_Restore_کھڑکی;
    device->Destroy_کھڑکی = PSP_Destroy_کھڑکی;
    device->GL_لدو_Library = PSP_GL_لدو_Library;
    device->GL_Get_Proc_پتہ = PSP_GL_Get_Proc_پتہ;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = PSP_GL_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = PSP_GL_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = PSP_GL_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

ساكن فراغ configure_dialog(psp_Utility_پیغام_Dialog_Params *dialog, size_t dialog_ناپ)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_ناپ);
	dialog->ادھار.ناپ = dialog_ناپ;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->ادھار.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->ادھار.button_وٹاندرا);

	// set thread priorities
	// TODO: understand how these work
	dialog->ادھار.soundThread = 0x10;
	dialog->ادھار.graphicsThread = 0x11;
	dialog->ادھار.fontThread = 0x12;
	dialog->ادھار.accessThread = 0x13;
}

ساكن فراغ *تیاری_temporal_gu(فراغ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	صحيح bpp = 4;

	فراغ *doublebuffer = vramalloc(PSP_چوکھٹا_بفر_ناپ * bpp * 2);
    فراغ *backbuffer = doublebuffer;
    فراغ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_چوکھٹا_بفر_ناپ * bpp;

    sceGuInit();

    sce_Gu_شروع(GU_سدھا,list);
	sce_Gu_Draw_بفر(GU_PSM_8888, vrelptr(frontbuffer), PSP_چوکھٹا_بفر_چوڑائی);
    sce_Gu_Disp_بفر(PSP_SCREEN_چوڑائی, PSP_SCREEN_اچائی, vrelptr(backbuffer), PSP_چوکھٹا_بفر_چوڑائی);

    sce_Gu_وتھ(2048 - (PSP_SCREEN_چوڑائی >> 1), 2048 - (PSP_SCREEN_اچائی >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_چوڑائی, PSP_SCREEN_اچائی);

    sceGuDisable(GU_ڈونگھائی_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_چوڑائی, PSP_SCREEN_اچائی);
    sceGuEnable(GU_SCISSOR_TEST);

    sce_Gu_انت();
    sceGuSync(0,0);

    sce_Display_Wait_Vblank_شروع();
    sceGuDisplay(GU_TRUE);

	أرجع doublebuffer;
}

ساكن فراغ رکن_temporal_gu(فراغ *gu_بفر)
{
	sce_Gu_رکن();
	vfree(gu_بفر);
	sce_Display_Wait_Vblank_شروع();
}

bool PSP_Show_سنیہا_Box(ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID)
{
	بنانشانی حرف list[64] __attribute__((aligned(64)));
	psp_Utility_پیغام_Dialog_Params dialog;
	صحيح حالت;
    فراغ *gu_بفر = عدم;

	// check if it's possible to use existing video context
	إذا (SDL_GetKeyboardFocus() == عدم) {
		gu_بفر = تیاری_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, حجم(dialog));

	// setup dialog options for text
	dialog.منوال = PSP_UTILITY_MSGDIALOG_منوال_متن;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_متن;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.سنیہا, حجم(dialog.سنیہا), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->سنیہا);

	// too many buttons
	إذا (messageboxdata->numbuttons > 2)
		أرجع SDL_سیٹ_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	إذا (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	إذا (sce_Utility_پیغام_Dialog_Init_شروع(&dialog) != 0)
		أرجع SDL_سیٹ_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	حالت = PSP_UTILITY_DIALOG_NONE;
	افعل
	{
		sce_Gu_شروع(GU_سدھا, list);
		sceGuClearColor(0);
		sce_Gu_Clear_ڈونگھائی(0);
		sceGuClear(GU_COLOR_بفر_ثنائی_ہندسہ|GU_ڈونگھائی_بفر_ثنائی_ہندسہ);
		sce_Gu_انت();
		sceGuSync(0,0);

		حالت = sce_Utility_پیغام_Dialog_Get_حالت();

		بدل (حالت)
		{
			حالة PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_پیغام_Dialog_Update(1);
				اكسر;

			حالة PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_پیغام_Dialog_Shutdown_شروع();
				اكسر;
		}

		sce_Display_Wait_Vblank_شروع();
		sce_Gu_وٹاندرا_Buffers();

	} طالما (حالت != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	إذا (gu_بفر)
	{
		رکن_temporal_gu(gu_بفر);
	}

	// success
	إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_نتیجہ_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	وإلا إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_نتیجہ_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	وإلا
		*buttonID = messageboxdata->buttons[0].buttonID;

	أرجع true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_Show_سنیہا_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;

    إذا (!PSP_EventInit(_this)) {
        أرجع false;  // error string would already be set
    }

    SDL_zero(منوال);
    منوال.w = PSP_SCREEN_چوڑائی;
    منوال.h = PSP_SCREEN_اچائی;
    منوال.refresh_شرح = 60.0f;

    // 32 bpp for default
    منوال.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
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
    SDL_Display_منوال منوال;

    SDL_zero(منوال);
    منوال.w = PSP_SCREEN_چوڑائی;
    منوال.h = PSP_SCREEN_اچائی;
    منوال.refresh_شرح = 60.0f;

    // 32 bpp for default
    منوال.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال);

    // 16 bpp secondary mode
    منوال.format = SDL_PIXELFORMAT_BGR565;
    SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال);
    أرجع true;
}

bool PSP_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    أرجع true;
}

#تعریف_کرو EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_سیٹ_Error("EGL error %d", err); \
            أرجع true;                          \
        }                                      \
    } طالما (0)

bool PSP_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *wdata;

    // Allocate window internal data
    wdata = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    کھڑکی->اندرونی = wdata;

    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    // Window has been successfully created
    أرجع true;
}

فراغ PSP_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool PSP_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    أرجع SDL_Unsupported();
}
فراغ PSP_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ PSP_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ PSP_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ PSP_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ PSP_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ PSP_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ PSP_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ PSP_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    حرف list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    صحيح پورا = 0;
    صحيح داخلہ_متن_لمائی = 128;
    فراغ *received_متن = SDL_calloc(داخلہ_متن_لمائی, حجم(Uint16));
    إذا (!received_متن) {
        أرجع;
    }
    فراغ *received_متن_شروع = received_متن;
    فراغ *متن_string = عدم;
    فراغ *string_منزل_send = عدم;

    SDL_iconv_t iconv = عدم;
    size_t outbytesleft = داخلہ_متن_لمائی;
    size_t inbytesleft = داخلہ_متن_لمائی * حجم(Uint16);
    size_t iconv_نتیجہ = 0;

    Sce_Utility_Osk_انکڑے انکڑے;
    SceUtilityOskParams params;

    انکڑے.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    انکڑے.سطریں = 1;
    انکڑے.unk_24 = 1;
    بدل (SDL_Get_متن_داخلہ_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_متن:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_USERNAME:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
        انکڑے.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    }
    انکڑے.desc = عدم;
    انکڑے.intext = عدم;
    انکڑے.outtextlength = داخلہ_متن_لمائی;
    انکڑے.outtextlimit = داخلہ_متن_لمائی;
    انکڑے.outtext = (بنانشانی چھوٹا *)received_متن;

    params.ادھار.ناپ = حجم(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.ادھار.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.ادھار.button_وٹاندرا);
    params.ادھار.graphicsThread = 17;
    params.ادھار.accessThread = 19;
    params.ادھار.fontThread = 18;
    params.ادھار.soundThread = 16;
    params.datacount = 1;
    params.انکڑے = &انکڑے;

    sce_Utility_Osk_Init_شروع(&params);

    SDL_SendScreenKeyboardShown();

    طالما (!پورا) {
        sce_Gu_شروع(GU_سدھا, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_بفر_ثنائی_ہندسہ);
        إذا (sce_Gu_Get_حالت(GU_ڈونگھائی_TEST)) {
            sce_Gu_Clear_ڈونگھائی(0);
            sceGuClear(GU_ڈونگھائی_بفر_ثنائی_ہندسہ);
        }
        sce_Gu_انت();
        sceGuSync(0, 0);

        بدل (sce_Utility_Osk_Get_حالت()) {
        حالة PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            اكسر;
        حالة PSP_UTILITY_DIALOG_QUIT:
            sce_Utility_Osk_Shutdown_شروع();
            اكسر;
        حالة PSP_UTILITY_DIALOG_NONE:
            پورا = 1;
            اكسر;
        افتراضي:
            اكسر;
        }
        sce_Display_Wait_Vblank_شروع();
        sce_Gu_وٹاندرا_Buffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    إذا ((size_t)iconv == SDL_ICONV_ERROR) {
        اذهب پورا;
    }

    string_منزل_send = SDL_calloc(داخلہ_متن_لمائی, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    إذا (!string_منزل_send) {
        SDL_iconv_close(iconv);
        اذهب پورا;
    }

    متن_string = string_منزل_send;
    outbytesleft = داخلہ_متن_لمائی * 3;
    iconv_نتیجہ = SDL_iconv(iconv, (ثابت حرف **)&received_متن, (size_t *)&inbytesleft, (حرف **)&متن_string, &outbytesleft);
    إذا (iconv_نتیجہ == 0) {
        SDL_Send_Keyboard_متن(string_منزل_send);
    }

    SDL_iconv_close(iconv);

پورا:
    SDL_free(string_منزل_send);
    SDL_free(received_متن_شروع);

    SDL_SendScreenKeyboardHidden();
}

فراغ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}

#جے_انت // SDL_VIDEO_DRIVER_PSP

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

#که_تعریف_شوی SDL_VIDEO_DRIVER_PSP

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

/*ناکارول_شوی
static bool PSP_initialized = false;
*/

ساكن فراغ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->دننی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *PSP_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *phdata;
    SDL_GLDriver_معلومات *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    gldata = (SDL_GLDriver_معلومات *)SDL_calloc(1, حجم(SDL_GLDriver_معلومات));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_معلومات = gldata;

    device->دننی = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->سېټ_Display_ډېرپېښ = PSP_سېټ_Display_ډېرپېښ;
    device->CreateSDLWindow = PSP_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = PSP_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Position = PSP_سېټ_کړکۍ_Position;
    device->سېټ_کړکۍ_اندازه = PSP_سېټ_کړکۍ_اندازه;
    device->Show_کړکۍ = PSP_Show_کړکۍ;
    device->Hide_کړکۍ = PSP_Hide_کړکۍ;
    device->Raise_کړکۍ = PSP_Raise_کړکۍ;
    device->Maximize_کړکۍ = PSP_Maximize_کړکۍ;
    device->Minimize_کړکۍ = PSP_Minimize_کړکۍ;
    device->Restore_کړکۍ = PSP_Restore_کړکۍ;
    device->Destroy_کړکۍ = PSP_Destroy_کړکۍ;
    device->GL_بارول_Library = PSP_GL_بارول_Library;
    device->GL_Get_Proc_پته = PSP_GL_Get_Proc_پته;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = PSP_GL_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = PSP_GL_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = PSP_GL_بدلون_کړکۍ;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

ساكن فراغ configure_dialog(psp_Utility_پیغام_Dialog_Params *dialog, size_t dialog_اندازه)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_اندازه);
	dialog->بنسټ.اندازه = dialog_اندازه;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->بنسټ.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->بنسټ.button_بدلون);

	// set thread priorities
	// TODO: understand how these work
	dialog->بنسټ.soundThread = 0x10;
	dialog->بنسټ.graphicsThread = 0x11;
	dialog->بنسټ.fontThread = 0x12;
	dialog->بنسټ.accessThread = 0x13;
}

ساكن فراغ *تیاری_temporal_gu(فراغ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	صحيح bpp = 4;

	فراغ *doublebuffer = vramalloc(PSP_چوکاټ_بفر_اندازه * bpp * 2);
    فراغ *backbuffer = doublebuffer;
    فراغ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_چوکاټ_بفر_اندازه * bpp;

    sceGuInit();

    sce_Gu_پیل(GU_مستقیم,list);
	sce_Gu_Draw_بفر(GU_PSM_8888, vrelptr(frontbuffer), PSP_چوکاټ_بفر_پلنوالی);
    sce_Gu_Disp_بفر(PSP_SCREEN_پلنوالی, PSP_SCREEN_لوړوالی, vrelptr(backbuffer), PSP_چوکاټ_بفر_پلنوالی);

    sce_Gu_دننه_واټن(2048 - (PSP_SCREEN_پلنوالی >> 1), 2048 - (PSP_SCREEN_لوړوالی >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_پلنوالی, PSP_SCREEN_لوړوالی);

    sceGuDisable(GU_ژوروالی_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_پلنوالی, PSP_SCREEN_لوړوالی);
    sceGuEnable(GU_SCISSOR_TEST);

    sce_Gu_پای();
    sceGuSync(0,0);

    sce_Display_Wait_Vblank_پیل();
    sceGuDisplay(GU_TRUE);

	أرجع doublebuffer;
}

ساكن فراغ غړی_temporal_gu(فراغ *gu_بفر)
{
	sce_Gu_غړی();
	vfree(gu_بفر);
	sce_Display_Wait_Vblank_پیل();
}

bool PSP_Show_پیغام_Box(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
	بینښه حرف list[64] __attribute__((aligned(64)));
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
	dialog.ډېرپېښ = PSP_UTILITY_MSGDIALOG_ډېرپېښ_متن;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_متن;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.پیغام, حجم(dialog.پیغام), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->پیغام);

	// too many buttons
	إذا (messageboxdata->numbuttons > 2)
		أرجع SDL_سېټ_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	إذا (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	إذا (sce_Utility_پیغام_Dialog_Init_پیل(&dialog) != 0)
		أرجع SDL_سېټ_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	حالت = PSP_UTILITY_DIALOG_NONE;
	افعل
	{
		sce_Gu_پیل(GU_مستقیم, list);
		sceGuClearColor(0);
		sce_Gu_Clear_ژوروالی(0);
		sceGuClear(GU_COLOR_بفر_بټ|GU_ژوروالی_بفر_بټ);
		sce_Gu_پای();
		sceGuSync(0,0);

		حالت = sce_Utility_پیغام_Dialog_Get_حالت();

		بدل (حالت)
		{
			حالة PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_پیغام_Dialog_Update(1);
				اكسر;

			حالة PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_پیغام_Dialog_Shutdown_پیل();
				اكسر;
		}

		sce_Display_Wait_Vblank_پیل();
		sce_Gu_بدلون_Buffers();

	} طالما (حالت != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	إذا (gu_بفر)
	{
		غړی_temporal_gu(gu_بفر);
	}

	// success
	إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_پایله_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	وإلا إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_پایله_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	وإلا
		*buttonID = messageboxdata->buttons[0].buttonID;

	أرجع true;
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
    SDL_Display_ډېرپېښ ډېرپېښ;

    إذا (!PSP_EventInit(_this)) {
        أرجع false;  // error string would already be set
    }

    SDL_zero(ډېرپېښ);
    ډېرپېښ.w = PSP_SCREEN_پلنوالی;
    ډېرپېښ.h = PSP_SCREEN_لوړوالی;
    ډېرپېښ.refresh_شرح = 60.0f;

    // 32 bpp for default
    ډېرپېښ.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ) == 0) {
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
    SDL_Display_ډېرپېښ ډېرپېښ;

    SDL_zero(ډېرپېښ);
    ډېرپېښ.w = PSP_SCREEN_پلنوالی;
    ډېرپېښ.h = PSP_SCREEN_لوړوالی;
    ډېرپېښ.refresh_شرح = 60.0f;

    // 32 bpp for default
    ډېرپېښ.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(display, &ډېرپېښ);

    // 16 bpp secondary mode
    ډېرپېښ.format = SDL_PIXELFORMAT_BGR565;
    SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(display, &ډېرپېښ);
    أرجع true;
}

bool PSP_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    أرجع true;
}

#تعریف_کړه EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_سېټ_Error("EGL error %d", err); \
            أرجع true;                          \
        }                                      \
    } طالما (0)

bool PSP_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *wdata;

    // Allocate window internal data
    wdata = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    کړکۍ->دننی = wdata;

    SDL_سېټ_Keyboard_Focus(کړکۍ);

    // Window has been successfully created
    أرجع true;
}

فراغ PSP_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
bool PSP_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    أرجع SDL_Unsupported();
}
فراغ PSP_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ PSP_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ PSP_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ PSP_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ PSP_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ PSP_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ PSP_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ PSP_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    حرف list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    صحيح بشپړ = 0;
    صحيح ننوت_متن_اوږدتیا = 128;
    فراغ *received_متن = SDL_calloc(ننوت_متن_اوږدتیا, حجم(Uint16));
    إذا (!received_متن) {
        أرجع;
    }
    فراغ *received_متن_پیل = received_متن;
    فراغ *متن_string = عدم;
    فراغ *string_منزل_send = عدم;

    SDL_iconv_t iconv = عدم;
    size_t outbytesleft = ننوت_متن_اوږدتیا;
    size_t inbytesleft = ننوت_متن_اوږدتیا * حجم(Uint16);
    size_t iconv_پایله = 0;

    Sce_Utility_Osk_معلومات معلومات;
    SceUtilityOskParams params;

    معلومات.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    معلومات.کرښې = 1;
    معلومات.unk_24 = 1;
    بدل (SDL_Get_متن_ننوت_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_متن:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_USERNAME:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_شمېره:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_شمېره_PASSWORD_HIDDEN:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_شمېره_PASSWORD_VISIBLE:
        معلومات.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    }
    معلومات.desc = عدم;
    معلومات.intext = عدم;
    معلومات.outtextlength = ننوت_متن_اوږدتیا;
    معلومات.outtextlimit = ننوت_متن_اوږدتیا;
    معلومات.outtext = (بینښه لنډ *)received_متن;

    params.بنسټ.اندازه = حجم(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.بنسټ.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.بنسټ.button_بدلون);
    params.بنسټ.graphicsThread = 17;
    params.بنسټ.accessThread = 19;
    params.بنسټ.fontThread = 18;
    params.بنسټ.soundThread = 16;
    params.datacount = 1;
    params.معلومات = &معلومات;

    sce_Utility_Osk_Init_پیل(&params);

    SDL_SendScreenKeyboardShown();

    طالما (!بشپړ) {
        sce_Gu_پیل(GU_مستقیم, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_بفر_بټ);
        إذا (sce_Gu_Get_حالت(GU_ژوروالی_TEST)) {
            sce_Gu_Clear_ژوروالی(0);
            sceGuClear(GU_ژوروالی_بفر_بټ);
        }
        sce_Gu_پای();
        sceGuSync(0, 0);

        بدل (sce_Utility_Osk_Get_حالت()) {
        حالة PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            اكسر;
        حالة PSP_UTILITY_DIALOG_QUIT:
            sce_Utility_Osk_Shutdown_پیل();
            اكسر;
        حالة PSP_UTILITY_DIALOG_NONE:
            بشپړ = 1;
            اكسر;
        افتراضي:
            اكسر;
        }
        sce_Display_Wait_Vblank_پیل();
        sce_Gu_بدلون_Buffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    إذا ((size_t)iconv == SDL_ICONV_ERROR) {
        اذهب بشپړ;
    }

    string_منزل_send = SDL_calloc(ننوت_متن_اوږدتیا, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    إذا (!string_منزل_send) {
        SDL_iconv_close(iconv);
        اذهب بشپړ;
    }

    متن_string = string_منزل_send;
    outbytesleft = ننوت_متن_اوږدتیا * 3;
    iconv_پایله = SDL_iconv(iconv, (ثابت حرف **)&received_متن, (size_t *)&inbytesleft, (حرف **)&متن_string, &outbytesleft);
    إذا (iconv_پایله == 0) {
        SDL_Send_Keyboard_متن(string_منزل_send);
    }

    SDL_iconv_close(iconv);

بشپړ:
    SDL_free(string_منزل_send);
    SDL_free(received_متن_پیل);

    SDL_SendScreenKeyboardHidden();
}

فراغ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}

#د_که_پای // SDL_VIDEO_DRIVER_PSP

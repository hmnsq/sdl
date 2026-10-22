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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_PSP

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

/*استفادهنشده
static bool PSP_initialized = false;
*/

ساكن فراغ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->داخلی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *PSP_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *phdata;
    SDL_GLDriver_داده *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }

    gldata = (SDL_GLDriver_داده *)SDL_calloc(1, حجم(SDL_GLDriver_داده));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_داده = gldata;

    device->داخلی = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->رقم_displays = 0;

    // Set device free function
    device->حرر = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->مجموعه_Display_نما = PSP_مجموعه_Display_نما;
    device->CreateSDLWindow = PSP_Create_پنجره;
    device->مجموعه_پنجره_Title = PSP_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Position = PSP_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = PSP_مجموعه_پنجره_اندازه;
    device->Show_پنجره = PSP_Show_پنجره;
    device->Hide_پنجره = PSP_Hide_پنجره;
    device->Raise_پنجره = PSP_Raise_پنجره;
    device->Maximize_پنجره = PSP_Maximize_پنجره;
    device->Minimize_پنجره = PSP_Minimize_پنجره;
    device->Restore_پنجره = PSP_Restore_پنجره;
    device->Destroy_پنجره = PSP_Destroy_پنجره;
    device->GL_بارگیری_Library = PSP_GL_بارگیری_Library;
    device->GL_Get_Proc_آدرس = PSP_GL_Get_Proc_آدرس;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = PSP_GL_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = PSP_GL_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = PSP_GL_جابجا_پنجره;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

ساكن فراغ configure_dialog(psp_Utility_پیام_Dialog_Params *dialog, size_t dialog_اندازه)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_اندازه);
	dialog->پایه.اندازه = dialog_اندازه;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->پایه.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->پایه.button_جابجا);

	// set thread priorities
	// TODO: understand how these work
	dialog->پایه.soundThread = 0x10;
	dialog->پایه.graphicsThread = 0x11;
	dialog->پایه.fontThread = 0x12;
	dialog->پایه.accessThread = 0x13;
}

ساكن فراغ *راهاندازی_temporal_gu(فراغ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	صحيح bpp = 4;

	فراغ *doublebuffer = vramalloc(PSP_قاب_میانگیر_اندازه * bpp * 2);
    فراغ *backbuffer = doublebuffer;
    فراغ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_قاب_میانگیر_اندازه * bpp;

    sceGuInit();

    sce_Gu_شروع(GU_مستقیم,list);
	sce_Gu_Draw_میانگیر(GU_PSM_8888, vrelptr(frontbuffer), PSP_قاب_میانگیر_عرض);
    sce_Gu_Disp_میانگیر(PSP_SCREEN_عرض, PSP_SCREEN_ارتفاع, vrelptr(backbuffer), PSP_قاب_میانگیر_عرض);

    sce_Gu_جابه_جایی(2048 - (PSP_SCREEN_عرض >> 1), 2048 - (PSP_SCREEN_ارتفاع >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_عرض, PSP_SCREEN_ارتفاع);

    sceGuDisable(GU_عمق_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_عرض, PSP_SCREEN_ارتفاع);
    sceGuEnable(GU_SCISSOR_TEST);

    sce_Gu_پایان();
    sceGuSync(0,0);

    sce_Display_Wait_Vblank_شروع();
    sceGuDisplay(GU_TRUE);

	أرجع doublebuffer;
}

ساكن فراغ جمله_temporal_gu(فراغ *gu_میانگیر)
{
	sce_Gu_جمله();
	vfree(gu_میانگیر);
	sce_Display_Wait_Vblank_شروع();
}

bool PSP_Show_پیام_Box(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
	بیعلامت حرف list[64] __attribute__((aligned(64)));
	psp_Utility_پیام_Dialog_Params dialog;
	صحيح وضعیت;
    فراغ *gu_میانگیر = عدم;

	// check if it's possible to use existing video context
	إذا (SDL_GetKeyboardFocus() == عدم) {
		gu_میانگیر = راهاندازی_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, حجم(dialog));

	// setup dialog options for text
	dialog.نما = PSP_UTILITY_MSGDIALOG_نما_متن;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_متن;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.پیام, حجم(dialog.پیام), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->پیام);

	// too many buttons
	إذا (messageboxdata->numbuttons > 2)
		أرجع SDL_مجموعه_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	إذا (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	إذا (sce_Utility_پیام_Dialog_Init_شروع(&dialog) != 0)
		أرجع SDL_مجموعه_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	وضعیت = PSP_UTILITY_DIALOG_NONE;
	افعل
	{
		sce_Gu_شروع(GU_مستقیم, list);
		sceGuClearColor(0);
		sce_Gu_Clear_عمق(0);
		sceGuClear(GU_COLOR_میانگیر_بیت|GU_عمق_میانگیر_بیت);
		sce_Gu_پایان();
		sceGuSync(0,0);

		وضعیت = sce_Utility_پیام_Dialog_Get_وضعیت();

		بدل (وضعیت)
		{
			حالة PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_پیام_Dialog_Update(1);
				اكسر;

			حالة PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_پیام_Dialog_Shutdown_شروع();
				اكسر;
		}

		sce_Display_Wait_Vblank_شروع();
		sce_Gu_جابجا_Buffers();

	} طالما (وضعیت != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	إذا (gu_میانگیر)
	{
		جمله_temporal_gu(gu_میانگیر);
	}

	// success
	إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_نتیجه_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	وإلا إذا (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_نتیجه_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	وإلا
		*buttonID = messageboxdata->buttons[0].buttonID;

	أرجع true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_Show_پیام_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_نما نما;

    إذا (!PSP_EventInit(_this)) {
        أرجع false;  // error string would already be set
    }

    SDL_zero(نما);
    نما.w = PSP_SCREEN_عرض;
    نما.h = PSP_SCREEN_ارتفاع;
    نما.refresh_نرخ = 60.0f;

    // 32 bpp for default
    نما.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_جمع_کن_Basic_Video_Display(&نما) == 0) {
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
    SDL_Display_نما نما;

    SDL_zero(نما);
    نما.w = PSP_SCREEN_عرض;
    نما.h = PSP_SCREEN_ارتفاع;
    نما.refresh_نرخ = 60.0f;

    // 32 bpp for default
    نما.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_جمع_کن_Fullscreen_Display_نما(display, &نما);

    // 16 bpp secondary mode
    نما.format = SDL_PIXELFORMAT_BGR565;
    SDL_جمع_کن_Fullscreen_Display_نما(display, &نما);
    أرجع true;
}

bool PSP_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    أرجع true;
}

#تعریف_کن EGLCHK(stmt)                           \
    افعل {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        إذا (err != EGL_SUCCESS) {              \
            SDL_مجموعه_Error("EGL error %d", err); \
            أرجع true;                          \
        }                                      \
    } طالما (0)

bool PSP_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *wdata;

    // Allocate window internal data
    wdata = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    پنجره->داخلی = wdata;

    SDL_مجموعه_Keyboard_Focus(پنجره);

    // Window has been successfully created
    أرجع true;
}

فراغ PSP_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
bool PSP_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    أرجع SDL_Unsupported();
}
فراغ PSP_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ PSP_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ PSP_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ PSP_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ PSP_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ PSP_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ PSP_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ PSP_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

فراغ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    حرف list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    صحيح انجامشده = 0;
    صحيح درون_داد_متن_درازی = 128;
    فراغ *received_متن = SDL_calloc(درون_داد_متن_درازی, حجم(Uint16));
    إذا (!received_متن) {
        أرجع;
    }
    فراغ *received_متن_شروع = received_متن;
    فراغ *متن_string = عدم;
    فراغ *string_مقصد_send = عدم;

    SDL_iconv_t iconv = عدم;
    size_t outbytesleft = درون_داد_متن_درازی;
    size_t inbytesleft = درون_داد_متن_درازی * حجم(Uint16);
    size_t iconv_نتیجه = 0;

    Sce_Utility_Osk_داده داده;
    SceUtilityOskParams params;

    داده.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    داده.سطرها = 1;
    داده.unk_24 = 1;
    بدل (SDL_Get_متن_درون_داد_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_متن:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_USERNAME:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
        داده.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        اكسر;
    }
    داده.desc = عدم;
    داده.intext = عدم;
    داده.outtextlength = درون_داد_متن_درازی;
    داده.outtextlimit = درون_داد_متن_درازی;
    داده.outtext = (بیعلامت کوتاه *)received_متن;

    params.پایه.اندازه = حجم(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.پایه.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.پایه.button_جابجا);
    params.پایه.graphicsThread = 17;
    params.پایه.accessThread = 19;
    params.پایه.fontThread = 18;
    params.پایه.soundThread = 16;
    params.datacount = 1;
    params.داده = &داده;

    sce_Utility_Osk_Init_شروع(&params);

    SDL_SendScreenKeyboardShown();

    طالما (!انجامشده) {
        sce_Gu_شروع(GU_مستقیم, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_میانگیر_بیت);
        إذا (sce_Gu_Get_وضعیت(GU_عمق_TEST)) {
            sce_Gu_Clear_عمق(0);
            sceGuClear(GU_عمق_میانگیر_بیت);
        }
        sce_Gu_پایان();
        sceGuSync(0, 0);

        بدل (sce_Utility_Osk_Get_وضعیت()) {
        حالة PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            اكسر;
        حالة PSP_UTILITY_DIALOG_QUIT:
            sce_Utility_Osk_Shutdown_شروع();
            اكسر;
        حالة PSP_UTILITY_DIALOG_NONE:
            انجامشده = 1;
            اكسر;
        افتراضي:
            اكسر;
        }
        sce_Display_Wait_Vblank_شروع();
        sce_Gu_جابجا_Buffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    إذا ((size_t)iconv == SDL_ICONV_ERROR) {
        اذهب انجامشده;
    }

    string_مقصد_send = SDL_calloc(درون_داد_متن_درازی, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    إذا (!string_مقصد_send) {
        SDL_iconv_close(iconv);
        اذهب انجامشده;
    }

    متن_string = string_مقصد_send;
    outbytesleft = درون_داد_متن_درازی * 3;
    iconv_نتیجه = SDL_iconv(iconv, (ثابت حرف **)&received_متن, (size_t *)&inbytesleft, (حرف **)&متن_string, &outbytesleft);
    إذا (iconv_نتیجه == 0) {
        SDL_Send_Keyboard_متن(string_مقصد_send);
    }

    SDL_iconv_close(iconv);

انجامشده:
    SDL_free(string_مقصد_send);
    SDL_free(received_متن_شروع);

    SDL_SendScreenKeyboardHidden();
}

فراغ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}

#پایان_اگر // SDL_VIDEO_DRIVER_PSP

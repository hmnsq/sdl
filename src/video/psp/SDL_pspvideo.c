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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_PSP

// SDL internals
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"

// PSP declarations
#అన్తర్భావ "SDL_pspvideo.h"
#అన్తర్భావ "SDL_pspevents_c.h"
#అన్తర్భావ "SDL_pspgl_c.h"
#అన్తర్భావ "../../render/psp/SDL_render_psp_c.h"

#అన్తర్భావ <psputility.h>
#అన్తర్భావ <pspgu.h>
#అన్తర్భావ <pspdisplay.h>
#అన్తర్భావ <vram.h>

/*వాడని
static bool PSP_initialized = false;
*/

స్థిర శూన్య PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->అంతర్గత);
    SDL_free(device);
}

స్థిర SDL_VideoDevice *PSP_Create(శూన్య)
{
    SDL_VideoDevice *device;
    SDL_Video_దత్తాంశం *phdata;
    SDL_GLDriver_దత్తాంశం *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, పరిమాణం(SDL_VideoDevice));
    ఒకవేళ (!device) {
        తిరిగి ఖాళీ;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Video_దత్తాంశం));
    ఒకవేళ (!phdata) {
        SDL_free(device);
        తిరిగి ఖాళీ;
    }

    gldata = (SDL_GLDriver_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_GLDriver_దత్తాంశం));
    ఒకవేళ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        తిరిగి ఖాళీ;
    }
    device->gl_దత్తాంశం = gldata;

    device->అంతర్గత = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->అంకె_displays = 0;

    // Set device free function
    device->విడుదల = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->సమితి_Display_బహుళకం = PSP_సమితి_Display_బహుళకం;
    device->CreateSDLWindow = PSP_Create_కిటికీ;
    device->సమితి_కిటికీ_Title = PSP_సమితి_కిటికీ_Title;
    device->సమితి_కిటికీ_Position = PSP_సమితి_కిటికీ_Position;
    device->సమితి_కిటికీ_కొలత = PSP_సమితి_కిటికీ_కొలత;
    device->Show_కిటికీ = PSP_Show_కిటికీ;
    device->Hide_కిటికీ = PSP_Hide_కిటికీ;
    device->Raise_కిటికీ = PSP_Raise_కిటికీ;
    device->Maximize_కిటికీ = PSP_Maximize_కిటికీ;
    device->Minimize_కిటికీ = PSP_Minimize_కిటికీ;
    device->Restore_కిటికీ = PSP_Restore_కిటికీ;
    device->Destroy_కిటికీ = PSP_Destroy_కిటికీ;
    device->GL_ఎక్కించు_Library = PSP_GL_ఎక్కించు_Library;
    device->GL_Get_Proc_చిరునామా = PSP_GL_Get_Proc_చిరునామా;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_సమితి_మార్పిడి_Interval = PSP_GL_సమితి_మార్పిడి_Interval;
    device->GL_Get_మార్పిడి_Interval = PSP_GL_Get_మార్పిడి_Interval;
    device->GL_మార్పిడి_కిటికీ = PSP_GL_మార్పిడి_కిటికీ;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    తిరిగి device;
}

స్థిర శూన్య configure_dialog(psp_Utility_సందేశం_Dialog_Params *dialog, size_t dialog_కొలత)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_కొలత);
	dialog->పునాది.కొలత = dialog_కొలత;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->పునాది.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->పునాది.button_మార్పిడి);

	// set thread priorities
	// TODO: understand how these work
	dialog->పునాది.soundThread = 0x10;
	dialog->పునాది.graphicsThread = 0x11;
	dialog->పునాది.fontThread = 0x12;
	dialog->పునాది.accessThread = 0x13;
}

స్థిర శూన్య *అమరిక_temporal_gu(శూన్య *list)
{
    // Using GU_PSM_8888 for the framebuffer
	పూర్ణాంకం bpp = 4;

	శూన్య *doublebuffer = vramalloc(PSP_చట్రం_బఫరు_కొలత * bpp * 2);
    శూన్య *backbuffer = doublebuffer;
    శూన్య *frontbuffer = ((uint8_t *)doublebuffer) + PSP_చట్రం_బఫరు_కొలత * bpp;

    sceGuInit();

    sce_Gu_ప్రారంభం(GU_ప్రత్యక్ష,list);
	sce_Gu_Draw_బఫరు(GU_PSM_8888, vrelptr(frontbuffer), PSP_చట్రం_బఫరు_వెడల్పు);
    sce_Gu_Disp_బఫరు(PSP_SCREEN_వెడల్పు, PSP_SCREEN_ఎత్తు, vrelptr(backbuffer), PSP_చట్రం_బఫరు_వెడల్పు);

    sce_Gu_స్థానభ్రంశం(2048 - (PSP_SCREEN_వెడల్పు >> 1), 2048 - (PSP_SCREEN_ఎత్తు >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_వెడల్పు, PSP_SCREEN_ఎత్తు);

    sceGuDisable(GU_లోతు_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_వెడల్పు, PSP_SCREEN_ఎత్తు);
    sceGuEnable(GU_SCISSOR_TEST);

    sce_Gu_ముగింపు();
    sceGuSync(0,0);

    sce_Display_Wait_Vblank_ప్రారంభం();
    sceGuDisplay(GU_TRUE);

	తిరిగి doublebuffer;
}

స్థిర శూన్య పదం_temporal_gu(శూన్య *gu_బఫరు)
{
	sce_Gu_పదం();
	vfree(gu_బఫరు);
	sce_Display_Wait_Vblank_ప్రారంభం();
}

bool PSP_Show_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
	గుర్తులేని అక్షరం list[64] __attribute__((aligned(64)));
	psp_Utility_సందేశం_Dialog_Params dialog;
	పూర్ణాంకం స్థితి_2;
    శూన్య *gu_బఫరు = ఖాళీ;

	// check if it's possible to use existing video context
	ఒకవేళ (SDL_GetKeyboardFocus() == ఖాళీ) {
		gu_బఫరు = అమరిక_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, పరిమాణం(dialog));

	// setup dialog options for text
	dialog.బహుళకం = PSP_UTILITY_MSGDIALOG_బహుళకం_పాఠ్యం;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_పాఠ్యం;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.సందేశం, పరిమాణం(dialog.సందేశం), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->సందేశం);

	// too many buttons
	ఒకవేళ (messageboxdata->numbuttons > 2)
		తిరిగి SDL_సమితి_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	ఒకవేళ (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	ఒకవేళ (sce_Utility_సందేశం_Dialog_Init_ప్రారంభం(&dialog) != 0)
		తిరిగి SDL_సమితి_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	స్థితి_2 = PSP_UTILITY_DIALOG_NONE;
	చేయి
	{
		sce_Gu_ప్రారంభం(GU_ప్రత్యక్ష, list);
		sceGuClearColor(0);
		sce_Gu_Clear_లోతు(0);
		sceGuClear(GU_COLOR_బఫరు_బిట్టు|GU_లోతు_బఫరు_బిట్టు);
		sce_Gu_ముగింపు();
		sceGuSync(0,0);

		స్థితి_2 = sce_Utility_సందేశం_Dialog_Get_స్థితి();

		ఎంపిక (స్థితి_2)
		{
			స్థితి PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_సందేశం_Dialog_Update(1);
				ఆపు;

			స్థితి PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_సందేశం_Dialog_Shutdown_ప్రారంభం();
				ఆపు;
		}

		sce_Display_Wait_Vblank_ప్రారంభం();
		sce_Gu_మార్పిడి_Buffers();

	} అయితే (స్థితి_2 != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	ఒకవేళ (gu_బఫరు)
	{
		పదం_temporal_gu(gu_బఫరు);
	}

	// success
	ఒకవేళ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ఫలితం_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	లేకపోతే ఒకవేళ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ఫలితం_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	లేకపోతే
		*buttonID = messageboxdata->buttons[0].buttonID;

	తిరిగి true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_Show_సందేశం_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_బహుళకం బహుళకం;

    ఒకవేళ (!PSP_EventInit(_this)) {
        తిరిగి false;  // error string would already be set
    }

    SDL_zero(బహుళకం);
    బహుళకం.w = PSP_SCREEN_వెడల్పు;
    బహుళకం.h = PSP_SCREEN_ఎత్తు;
    బహుళకం.refresh_రేటు = 60.0f;

    // 32 bpp for default
    బహుళకం.format = SDL_PIXELFORMAT_ABGR8888;

    ఒకవేళ (SDL_కూడు_Basic_Video_Display(&బహుళకం) == 0) {
        తిరిగి false;
    }
    తిరిగి true;
}

శూన్య PSP_VideoQuit(SDL_VideoDevice *_this)
{
    PSP_EventQuit(_this);
}

bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_బహుళకం బహుళకం;

    SDL_zero(బహుళకం);
    బహుళకం.w = PSP_SCREEN_వెడల్పు;
    బహుళకం.h = PSP_SCREEN_ఎత్తు;
    బహుళకం.refresh_రేటు = 60.0f;

    // 32 bpp for default
    బహుళకం.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం);

    // 16 bpp secondary mode
    బహుళకం.format = SDL_PIXELFORMAT_BGR565;
    SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం);
    తిరిగి true;
}

bool PSP_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    తిరిగి true;
}

#నిర్వచించు EGLCHK(stmt)                           \
    చేయి {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ఒకవేళ (err != EGL_SUCCESS) {              \
            SDL_సమితి_Error("EGL error %d", err); \
            తిరిగి true;                          \
        }                                      \
    } అయితే (0)

bool PSP_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *wdata;

    // Allocate window internal data
    wdata = (SDL_కిటికీ_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_కిటికీ_దత్తాంశం));
    ఒకవేళ (!wdata) {
        తిరిగి false;
    }

    // Setup driver data for this window
    కిటికీ->అంతర్గత = wdata;

    SDL_సమితి_Keyboard_Focus(కిటికీ);

    // Window has been successfully created
    తిరిగి true;
}

శూన్య PSP_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
bool PSP_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    తిరిగి SDL_Unsupported();
}
శూన్య PSP_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య PSP_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య PSP_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య PSP_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య PSP_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య PSP_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య PSP_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}
శూన్య PSP_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    తిరిగి true;
}

శూన్య PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props)
{
    అక్షరం list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    పూర్ణాంకం పూర్తి = 0;
    పూర్ణాంకం ఆదానం_పాఠ్యం_నిడివి = 128;
    శూన్య *received_పాఠ్యం = SDL_calloc(ఆదానం_పాఠ్యం_నిడివి, పరిమాణం(Uint16));
    ఒకవేళ (!received_పాఠ్యం) {
        తిరిగి;
    }
    శూన్య *received_పాఠ్యం_ప్రారంభం = received_పాఠ్యం;
    శూన్య *పాఠ్యం_string = ఖాళీ;
    శూన్య *string_గమ్యం_send = ఖాళీ;

    SDL_iconv_t iconv = ఖాళీ;
    size_t outbytesleft = ఆదానం_పాఠ్యం_నిడివి;
    size_t inbytesleft = ఆదానం_పాఠ్యం_నిడివి * పరిమాణం(Uint16);
    size_t iconv_ఫలితం = 0;

    Sce_Utility_Osk_దత్తాంశం దత్తాంశం;
    SceUtilityOskParams params;

    దత్తాంశం.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    దత్తాంశం.పంక్తులు = 1;
    దత్తాంశం.unk_24 = 1;
    ఎంపిక (SDL_Get_పాఠ్యం_ఆదానం_Type(props)) {
    అప్రమేయ:
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_NAME:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_EMAIL:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_USERNAME:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_HIDDEN:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_పాఠ్యం_PASSWORD_VISIBLE:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_HIDDEN:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ఆపు;
    స్థితి SDL_TEXTINPUT_TYPE_సంఖ్య_PASSWORD_VISIBLE:
        దత్తాంశం.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ఆపు;
    }
    దత్తాంశం.desc = ఖాళీ;
    దత్తాంశం.intext = ఖాళీ;
    దత్తాంశం.outtextlength = ఆదానం_పాఠ్యం_నిడివి;
    దత్తాంశం.outtextlimit = ఆదానం_పాఠ్యం_నిడివి;
    దత్తాంశం.outtext = (గుర్తులేని పొట్టి *)received_పాఠ్యం;

    params.పునాది.కొలత = పరిమాణం(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.పునాది.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.పునాది.button_మార్పిడి);
    params.పునాది.graphicsThread = 17;
    params.పునాది.accessThread = 19;
    params.పునాది.fontThread = 18;
    params.పునాది.soundThread = 16;
    params.datacount = 1;
    params.దత్తాంశం = &దత్తాంశం;

    sce_Utility_Osk_Init_ప్రారంభం(&params);

    SDL_SendScreenKeyboardShown();

    అయితే (!పూర్తి) {
        sce_Gu_ప్రారంభం(GU_ప్రత్యక్ష, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_బఫరు_బిట్టు);
        ఒకవేళ (sce_Gu_Get_స్థితి(GU_లోతు_TEST)) {
            sce_Gu_Clear_లోతు(0);
            sceGuClear(GU_లోతు_బఫరు_బిట్టు);
        }
        sce_Gu_ముగింపు();
        sceGuSync(0, 0);

        ఎంపిక (sce_Utility_Osk_Get_స్థితి()) {
        స్థితి PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            ఆపు;
        స్థితి PSP_UTILITY_DIALOG_QUIT:
            sce_Utility_Osk_Shutdown_ప్రారంభం();
            ఆపు;
        స్థితి PSP_UTILITY_DIALOG_NONE:
            పూర్తి = 1;
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }
        sce_Display_Wait_Vblank_ప్రారంభం();
        sce_Gu_మార్పిడి_Buffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    ఒకవేళ ((size_t)iconv == SDL_ICONV_ERROR) {
        వెళ్ళు పూర్తి;
    }

    string_గమ్యం_send = SDL_calloc(ఆదానం_పాఠ్యం_నిడివి, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    ఒకవేళ (!string_గమ్యం_send) {
        SDL_iconv_close(iconv);
        వెళ్ళు పూర్తి;
    }

    పాఠ్యం_string = string_గమ్యం_send;
    outbytesleft = ఆదానం_పాఠ్యం_నిడివి * 3;
    iconv_ఫలితం = SDL_iconv(iconv, (స్థిరరాశి అక్షరం **)&received_పాఠ్యం, (size_t *)&inbytesleft, (అక్షరం **)&పాఠ్యం_string, &outbytesleft);
    ఒకవేళ (iconv_ఫలితం == 0) {
        SDL_Send_Keyboard_పాఠ్యం(string_గమ్యం_send);
    }

    SDL_iconv_close(iconv);

పూర్తి:
    SDL_free(string_గమ్యం_send);
    SDL_free(received_పాఠ్యం_ప్రారంభం);

    SDL_SendScreenKeyboardHidden();
}

శూన్య PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_PSP

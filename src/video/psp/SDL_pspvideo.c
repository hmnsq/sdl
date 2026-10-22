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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_PSP

// SDL internals
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"

// PSP declarations
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pspvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pspevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pspgl_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../render/psp/SDL_render_psp_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <psputility.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <pspgu.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <pspdisplay.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <vram.h>

/*ਅਣਵਰਤਿਆ
static bool PSP_initialized = false;
*/

ਸਥਿਰ ਖਾਲੀ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *PSP_Create(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *phdata;
    SDL_GLDriver_ਅੰਕੜੇ *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!phdata) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }

    gldata = (SDL_GLDriver_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_GLDriver_ਅੰਕੜੇ));
    ਜੇ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ਵਾਪਸ ਨਿਰਾ;
    }
    device->gl_ਅੰਕੜੇ = gldata;

    device->ਅੰਦਰੂਨੀ = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->ਅੰਕ_displays = 0;

    // Set device free function
    device->ਮੁਕਤ = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->ਸੈੱਟ_Display_ਬਹੁਲਕ = PSP_ਸੈੱਟ_Display_ਬਹੁਲਕ;
    device->CreateSDLWindow = PSP_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = PSP_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = PSP_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = PSP_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->Show_ਖਿੜਕੀ = PSP_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = PSP_Hide_ਖਿੜਕੀ;
    device->Raise_ਖਿੜਕੀ = PSP_Raise_ਖਿੜਕੀ;
    device->Maximize_ਖਿੜਕੀ = PSP_Maximize_ਖਿੜਕੀ;
    device->Minimize_ਖਿੜਕੀ = PSP_Minimize_ਖਿੜਕੀ;
    device->Restore_ਖਿੜਕੀ = PSP_Restore_ਖਿੜਕੀ;
    device->Destroy_ਖਿੜਕੀ = PSP_Destroy_ਖਿੜਕੀ;
    device->GL_ਲੱਦੋ_Library = PSP_GL_ਲੱਦੋ_Library;
    device->GL_Get_Proc_ਪਤਾ = PSP_GL_Get_Proc_ਪਤਾ;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = PSP_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = PSP_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = PSP_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ਵਾਪਸ device;
}

ਸਥਿਰ ਖਾਲੀ configure_dialog(psp_Utility_ਸੁਨੇਹਾ_Dialog_Params *dialog, size_t dialog_ਮਾਪ)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_ਮਾਪ);
	dialog->ਅਧਾਰ.ਮਾਪ = dialog_ਮਾਪ;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->ਅਧਾਰ.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->ਅਧਾਰ.button_ਅਦਲਾ_ਬਦਲੀ);

	// set thread priorities
	// TODO: understand how these work
	dialog->ਅਧਾਰ.soundThread = 0x10;
	dialog->ਅਧਾਰ.graphicsThread = 0x11;
	dialog->ਅਧਾਰ.fontThread = 0x12;
	dialog->ਅਧਾਰ.accessThread = 0x13;
}

ਸਥਿਰ ਖਾਲੀ *ਤਿਆਰੀ_temporal_gu(ਖਾਲੀ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	ਪੂਰਨ bpp = 4;

	ਖਾਲੀ *doublebuffer = vramalloc(PSP_ਚੌਖਟਾ_ਬਫਰ_ਮਾਪ * bpp * 2);
    ਖਾਲੀ *backbuffer = doublebuffer;
    ਖਾਲੀ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_ਚੌਖਟਾ_ਬਫਰ_ਮਾਪ * bpp;

    sceGuInit();

    sce_Gu_ਸ਼ੁਰੂ(GU_ਸਿੱਧਾ,list);
	sce_Gu_Draw_ਬਫਰ(GU_PSM_8888, vrelptr(frontbuffer), PSP_ਚੌਖਟਾ_ਬਫਰ_ਚੌੜਾਈ);
    sce_Gu_Disp_ਬਫਰ(PSP_SCREEN_ਚੌੜਾਈ, PSP_SCREEN_ਉਚਾਈ, vrelptr(backbuffer), PSP_ਚੌਖਟਾ_ਬਫਰ_ਚੌੜਾਈ);

    sce_Gu_ਵਿੱਥ(2048 - (PSP_SCREEN_ਚੌੜਾਈ >> 1), 2048 - (PSP_SCREEN_ਉਚਾਈ >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_ਚੌੜਾਈ, PSP_SCREEN_ਉਚਾਈ);

    sceGuDisable(GU_ਡੂੰਘਾਈ_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_ਚੌੜਾਈ, PSP_SCREEN_ਉਚਾਈ);
    sceGuEnable(GU_SCISSOR_TEST);

    sce_Gu_ਅੰਤ();
    sceGuSync(0,0);

    sce_Display_Wait_Vblank_ਸ਼ੁਰੂ();
    sceGuDisplay(GU_TRUE);

	ਵਾਪਸ doublebuffer;
}

ਸਥਿਰ ਖਾਲੀ ਪਦ_temporal_gu(ਖਾਲੀ *gu_ਬਫਰ)
{
	sce_Gu_ਪਦ();
	vfree(gu_ਬਫਰ);
	sce_Display_Wait_Vblank_ਸ਼ੁਰੂ();
}

bool PSP_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ list[64] __attribute__((aligned(64)));
	psp_Utility_ਸੁਨੇਹਾ_Dialog_Params dialog;
	ਪੂਰਨ ਸਥਿਤੀ;
    ਖਾਲੀ *gu_ਬਫਰ = ਨਿਰਾ;

	// check if it's possible to use existing video context
	ਜੇ (SDL_GetKeyboardFocus() == ਨਿਰਾ) {
		gu_ਬਫਰ = ਤਿਆਰੀ_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, ਆਕਾਰ(dialog));

	// setup dialog options for text
	dialog.ਬਹੁਲਕ = PSP_UTILITY_MSGDIALOG_ਬਹੁਲਕ_ਪਾਠ;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_ਪਾਠ;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.ਸੁਨੇਹਾ, ਆਕਾਰ(dialog.ਸੁਨੇਹਾ), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->ਸੁਨੇਹਾ);

	// too many buttons
	ਜੇ (messageboxdata->numbuttons > 2)
		ਵਾਪਸ SDL_ਸੈੱਟ_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	ਜੇ (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	ਜੇ (sce_Utility_ਸੁਨੇਹਾ_Dialog_Init_ਸ਼ੁਰੂ(&dialog) != 0)
		ਵਾਪਸ SDL_ਸੈੱਟ_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	ਸਥਿਤੀ = PSP_UTILITY_DIALOG_NONE;
	ਕਰੋ
	{
		sce_Gu_ਸ਼ੁਰੂ(GU_ਸਿੱਧਾ, list);
		sceGuClearColor(0);
		sce_Gu_Clear_ਡੂੰਘਾਈ(0);
		sceGuClear(GU_COLOR_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ|GU_ਡੂੰਘਾਈ_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ);
		sce_Gu_ਅੰਤ();
		sceGuSync(0,0);

		ਸਥਿਤੀ = sce_Utility_ਸੁਨੇਹਾ_Dialog_Get_ਸਥਿਤੀ();

		ਚੋਣ (ਸਥਿਤੀ)
		{
			ਹਾਲਤ PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_ਸੁਨੇਹਾ_Dialog_Update(1);
				ਰੋਕੋ;

			ਹਾਲਤ PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_ਸੁਨੇਹਾ_Dialog_Shutdown_ਸ਼ੁਰੂ();
				ਰੋਕੋ;
		}

		sce_Display_Wait_Vblank_ਸ਼ੁਰੂ();
		sce_Gu_ਅਦਲਾ_ਬਦਲੀ_Buffers();

	} ਜਦੋਂ (ਸਥਿਤੀ != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	ਜੇ (gu_ਬਫਰ)
	{
		ਪਦ_temporal_gu(gu_ਬਫਰ);
	}

	// success
	ਜੇ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ਨਤੀਜਾ_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	ਨਹੀਂਤਾਂ ਜੇ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ਨਤੀਜਾ_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	ਨਹੀਂਤਾਂ
		*buttonID = messageboxdata->buttons[0].buttonID;

	ਵਾਪਸ true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_Show_ਸੁਨੇਹਾ_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    ਜੇ (!PSP_EventInit(_this)) {
        ਵਾਪਸ false;  // error string would already be set
    }

    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.w = PSP_SCREEN_ਚੌੜਾਈ;
    ਬਹੁਲਕ.h = PSP_SCREEN_ਉਚਾਈ;
    ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;

    // 32 bpp for default
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_ABGR8888;

    ਜੇ (SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ) == 0) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ PSP_VideoQuit(SDL_VideoDevice *_this)
{
    PSP_EventQuit(_this);
}

bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.w = PSP_SCREEN_ਚੌੜਾਈ;
    ਬਹੁਲਕ.h = PSP_SCREEN_ਉਚਾਈ;
    ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;

    // 32 bpp for default
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ);

    // 16 bpp secondary mode
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_BGR565;
    SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ);
    ਵਾਪਸ true;
}

bool PSP_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    ਵਾਪਸ true;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EGLCHK(stmt)                           \
    ਕਰੋ {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ਜੇ (err != EGL_SUCCESS) {              \
            SDL_ਸੈੱਟ_Error("EGL error %d", err); \
            ਵਾਪਸ true;                          \
        }                                      \
    } ਜਦੋਂ (0)

bool PSP_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata;

    // Allocate window internal data
    wdata = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (!wdata) {
        ਵਾਪਸ false;
    }

    // Setup driver data for this window
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = wdata;

    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);

    // Window has been successfully created
    ਵਾਪਸ true;
}

ਖਾਲੀ PSP_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
bool PSP_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ SDL_Unsupported();
}
ਖਾਲੀ PSP_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ PSP_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ PSP_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ PSP_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ PSP_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ PSP_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ PSP_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ PSP_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ਵਾਪਸ true;
}

ਖਾਲੀ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    ਅੱਖਰ list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    ਪੂਰਨ ਪੂਰਾ = 0;
    ਪੂਰਨ ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ = 128;
    ਖਾਲੀ *received_ਪਾਠ = SDL_calloc(ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ, ਆਕਾਰ(Uint16));
    ਜੇ (!received_ਪਾਠ) {
        ਵਾਪਸ;
    }
    ਖਾਲੀ *received_ਪਾਠ_ਸ਼ੁਰੂ = received_ਪਾਠ;
    ਖਾਲੀ *ਪਾਠ_string = ਨਿਰਾ;
    ਖਾਲੀ *string_ਮੰਜ਼ਿਲ_send = ਨਿਰਾ;

    SDL_iconv_t iconv = ਨਿਰਾ;
    size_t outbytesleft = ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ;
    size_t inbytesleft = ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ * ਆਕਾਰ(Uint16);
    size_t iconv_ਨਤੀਜਾ = 0;

    Sce_Utility_Osk_ਅੰਕੜੇ ਅੰਕੜੇ;
    SceUtilityOskParams params;

    ਅੰਕੜੇ.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    ਅੰਕੜੇ.ਸਤਰਾਂ = 1;
    ਅੰਕੜੇ.unk_24 = 1;
    ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
    ਮੂਲ:
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_NAME:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_EMAIL:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_USERNAME:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_HIDDEN:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_VISIBLE:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_HIDDEN:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_VISIBLE:
        ਅੰਕੜੇ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ਰੋਕੋ;
    }
    ਅੰਕੜੇ.desc = ਨਿਰਾ;
    ਅੰਕੜੇ.intext = ਨਿਰਾ;
    ਅੰਕੜੇ.outtextlength = ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ;
    ਅੰਕੜੇ.outtextlimit = ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ;
    ਅੰਕੜੇ.outtext = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ *)received_ਪਾਠ;

    params.ਅਧਾਰ.ਮਾਪ = ਆਕਾਰ(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.ਅਧਾਰ.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.ਅਧਾਰ.button_ਅਦਲਾ_ਬਦਲੀ);
    params.ਅਧਾਰ.graphicsThread = 17;
    params.ਅਧਾਰ.accessThread = 19;
    params.ਅਧਾਰ.fontThread = 18;
    params.ਅਧਾਰ.soundThread = 16;
    params.datacount = 1;
    params.ਅੰਕੜੇ = &ਅੰਕੜੇ;

    sce_Utility_Osk_Init_ਸ਼ੁਰੂ(&params);

    SDL_SendScreenKeyboardShown();

    ਜਦੋਂ (!ਪੂਰਾ) {
        sce_Gu_ਸ਼ੁਰੂ(GU_ਸਿੱਧਾ, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ);
        ਜੇ (sce_Gu_Get_ਸਥਿਤੀ(GU_ਡੂੰਘਾਈ_TEST)) {
            sce_Gu_Clear_ਡੂੰਘਾਈ(0);
            sceGuClear(GU_ਡੂੰਘਾਈ_ਬਫਰ_ਦੋਆਧਾਰੀ_ਅੰਕ);
        }
        sce_Gu_ਅੰਤ();
        sceGuSync(0, 0);

        ਚੋਣ (sce_Utility_Osk_Get_ਸਥਿਤੀ()) {
        ਹਾਲਤ PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            ਰੋਕੋ;
        ਹਾਲਤ PSP_UTILITY_DIALOG_QUIT:
            sce_Utility_Osk_Shutdown_ਸ਼ੁਰੂ();
            ਰੋਕੋ;
        ਹਾਲਤ PSP_UTILITY_DIALOG_NONE:
            ਪੂਰਾ = 1;
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }
        sce_Display_Wait_Vblank_ਸ਼ੁਰੂ();
        sce_Gu_ਅਦਲਾ_ਬਦਲੀ_Buffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    ਜੇ ((size_t)iconv == SDL_ICONV_ERROR) {
        ਜਾਓ ਪੂਰਾ;
    }

    string_ਮੰਜ਼ਿਲ_send = SDL_calloc(ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    ਜੇ (!string_ਮੰਜ਼ਿਲ_send) {
        SDL_iconv_close(iconv);
        ਜਾਓ ਪੂਰਾ;
    }

    ਪਾਠ_string = string_ਮੰਜ਼ਿਲ_send;
    outbytesleft = ਨਿਵੇਸ਼_ਪਾਠ_ਲੰਮਾਈ * 3;
    iconv_ਨਤੀਜਾ = SDL_iconv(iconv, (ਅਚਲ ਅੱਖਰ **)&received_ਪਾਠ, (size_t *)&inbytesleft, (ਅੱਖਰ **)&ਪਾਠ_string, &outbytesleft);
    ਜੇ (iconv_ਨਤੀਜਾ == 0) {
        SDL_Send_Keyboard_ਪਾਠ(string_ਮੰਜ਼ਿਲ_send);
    }

    SDL_iconv_close(iconv);

ਪੂਰਾ:
    SDL_free(string_ਮੰਜ਼ਿਲ_send);
    SDL_free(received_ਪਾਠ_ਸ਼ੁਰੂ);

    SDL_SendScreenKeyboardHidden();
}

ਖਾਲੀ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_PSP

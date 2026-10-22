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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_PSP

// SDL internals
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"

// PSP declarations
#ಅನ್ತರ್ಭಾವ "SDL_pspvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_pspevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_pspgl_c.h"
#ಅನ್ತರ್ಭಾವ "../../render/psp/SDL_render_psp_c.h"

#ಅನ್ತರ್ಭಾವ <psputility.h>
#ಅನ್ತರ್ಭಾವ <pspgu.h>
#ಅನ್ತರ್ಭಾವ <pspdisplay.h>
#ಅನ್ತರ್ಭಾವ <vram.h>

/*ಬಳಸದ
static bool PSP_initialized = false;
*/

ಸ್ಥಿರ ಶೂನ್ಯ PSP_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *PSP_Create(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *phdata;
    SDL_GLDriver_ದತ್ತಾಂಶ *gldata;

    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize internal PSP specific data
    phdata = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!phdata) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    gldata = (SDL_GLDriver_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_GLDriver_ದತ್ತಾಂಶ));
    ಆದರೆ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    device->gl_ದತ್ತಾಂಶ = gldata;

    device->ಆಂತರಿಕ = phdata;

    phdata->egl_initialized = true;

    // Setup amount of available displays
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಬಿಡುಗಡೆ = PSP_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = PSP_VideoInit;
    device->VideoQuit = PSP_VideoQuit;
    device->GetDisplayModes = PSP_GetDisplayModes;
    device->ಗಣ_Display_ಬಹುಲಕ = PSP_ಗಣ_Display_ಬಹುಲಕ;
    device->CreateSDLWindow = PSP_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = PSP_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Position = PSP_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = PSP_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Show_ಕಿಟಕಿ = PSP_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = PSP_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = PSP_Raise_ಕಿಟಕಿ;
    device->Maximize_ಕಿಟಕಿ = PSP_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = PSP_Minimize_ಕಿಟಕಿ;
    device->Restore_ಕಿಟಕಿ = PSP_Restore_ಕಿಟಕಿ;
    device->Destroy_ಕಿಟಕಿ = PSP_Destroy_ಕಿಟಕಿ;
    device->GL_ತುಂಬು_Library = PSP_GL_ತುಂಬು_Library;
    device->GL_Get_Proc_ವಿಳಾಸ = PSP_GL_Get_Proc_ವಿಳಾಸ;
    device->GL_UnloadLibrary = PSP_GL_UnloadLibrary;
    device->GL_CreateContext = PSP_GL_CreateContext;
    device->GL_MakeCurrent = PSP_GL_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = PSP_GL_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = PSP_GL_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = PSP_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = PSP_GL_DestroyContext;
    device->HasScreenKeyboardSupport = PSP_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = PSP_ShowScreenKeyboard;
    device->HideScreenKeyboard = PSP_HideScreenKeyboard;

    device->PumpEvents = PSP_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಹಿಂತಿರುಗಿ device;
}

ಸ್ಥಿರ ಶೂನ್ಯ configure_dialog(psp_Utility_ಸಂದೇಶ_Dialog_Params *dialog, size_t dialog_ಗಾತ್ರ)
{
	// clear structure and setup size
	SDL_memset(dialog, 0, dialog_ಗಾತ್ರ);
	dialog->ತಳ.ಗಾತ್ರ_2 = dialog_ಗಾತ್ರ;

	// set language
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &dialog->ತಳ.language);

	// set X/O swap
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &dialog->ತಳ.button_ಅದಲುಬದಲು);

	// set thread priorities
	// TODO: understand how these work
	dialog->ತಳ.soundThread = 0x10;
	dialog->ತಳ.graphicsThread = 0x11;
	dialog->ತಳ.fontThread = 0x12;
	dialog->ತಳ.accessThread = 0x13;
}

ಸ್ಥಿರ ಶೂನ್ಯ *ಸಿದ್ಧತೆ_temporal_gu(ಶೂನ್ಯ *list)
{
    // Using GU_PSM_8888 for the framebuffer
	ಪೂರ್ಣಾಂಕ bpp = 4;

	ಶೂನ್ಯ *doublebuffer = vramalloc(PSP_ಚೌಕಟ್ಟು_ಬಫರ್_ಗಾತ್ರ * bpp * 2);
    ಶೂನ್ಯ *backbuffer = doublebuffer;
    ಶೂನ್ಯ *frontbuffer = ((uint8_t *)doublebuffer) + PSP_ಚೌಕಟ್ಟು_ಬಫರ್_ಗಾತ್ರ * bpp;

    sceGuInit();

    sce_Gu_ಆರಂಭ(GU_ನೇರ,list);
	sce_Gu_Draw_ಬಫರ್(GU_PSM_8888, vrelptr(frontbuffer), PSP_ಚೌಕಟ್ಟು_ಬಫರ್_ಅಗಲ);
    sce_Gu_Disp_ಬಫರ್(PSP_SCREEN_ಅಗಲ, PSP_SCREEN_ಎತ್ತರ, vrelptr(backbuffer), PSP_ಚೌಕಟ್ಟು_ಬಫರ್_ಅಗಲ);

    sce_Gu_ಸ್ಥಾನಾಂತರ(2048 - (PSP_SCREEN_ಅಗಲ >> 1), 2048 - (PSP_SCREEN_ಎತ್ತರ >> 1));
    sceGuViewport(2048, 2048, PSP_SCREEN_ಅಗಲ, PSP_SCREEN_ಎತ್ತರ);

    sceGuDisable(GU_ಆಳ_TEST);

    // Scissoring
    sceGuScissor(0, 0, PSP_SCREEN_ಅಗಲ, PSP_SCREEN_ಎತ್ತರ);
    sceGuEnable(GU_SCISSOR_TEST);

    sce_Gu_ಮುಕ್ತಾಯ();
    sceGuSync(0,0);

    sce_Display_Wait_Vblank_ಆರಂಭ();
    sceGuDisplay(GU_TRUE);

	ಹಿಂತಿರುಗಿ doublebuffer;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಪದ_temporal_gu(ಶೂನ್ಯ *gu_ಬಫರ್)
{
	sce_Gu_ಪದ();
	vfree(gu_ಬಫರ್);
	sce_Display_Wait_Vblank_ಆರಂಭ();
}

bool PSP_Show_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ list[64] __attribute__((aligned(64)));
	psp_Utility_ಸಂದೇಶ_Dialog_Params dialog;
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;
    ಶೂನ್ಯ *gu_ಬಫರ್ = ಖಾಲಿ;

	// check if it's possible to use existing video context
	ಆದರೆ (SDL_GetKeyboardFocus() == ಖಾಲಿ) {
		gu_ಬಫರ್ = ಸಿದ್ಧತೆ_temporal_gu(list);
	}

	// configure dialog
	configure_dialog(&dialog, ಗಾತ್ರ(dialog));

	// setup dialog options for text
	dialog.ಬಹುಲಕ = PSP_UTILITY_MSGDIALOG_ಬಹುಲಕ_ಪಠ್ಯ;
	dialog.options = PSP_UTILITY_MSGDIALOG_OPTION_ಪಠ್ಯ;

	// copy the message in, 512 bytes max
	SDL_snprintf(dialog.ಸಂದೇಶ, ಗಾತ್ರ(dialog.ಸಂದೇಶ), "%s\r\n\r\n%s", messageboxdata->title, messageboxdata->ಸಂದೇಶ);

	// too many buttons
	ಆದರೆ (messageboxdata->numbuttons > 2)
		ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("messageboxdata->numbuttons valid values are 0, 1, 2");

	// we only have two options, "yes/no" or "ok"
	ಆದರೆ (messageboxdata->numbuttons == 2)
		dialog.options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS | PSP_UTILITY_MSGDIALOG_OPTION_DEFAULT_NO;

	// start dialog
	ಆದರೆ (sce_Utility_ಸಂದೇಶ_Dialog_Init_ಆರಂಭ(&dialog) != 0)
		ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("sceUtilityMsgDialogInitStart() failed for some reason");

	// loop while the dialog is active
	ಸ್ಥಿತಿ_2 = PSP_UTILITY_DIALOG_NONE;
	ಮಾಡು
	{
		sce_Gu_ಆರಂಭ(GU_ನೇರ, list);
		sceGuClearColor(0);
		sce_Gu_Clear_ಆಳ(0);
		sceGuClear(GU_COLOR_ಬಫರ್_ಬಿಟ್|GU_ಆಳ_ಬಫರ್_ಬಿಟ್);
		sce_Gu_ಮುಕ್ತಾಯ();
		sceGuSync(0,0);

		ಸ್ಥಿತಿ_2 = sce_Utility_ಸಂದೇಶ_Dialog_Get_ಸ್ಥಿತಿ();

		ಆಯ್ಕೆ (ಸ್ಥಿತಿ_2)
		{
			ಸ್ಥಿತಿ PSP_UTILITY_DIALOG_VISIBLE:
				sce_Utility_ಸಂದೇಶ_Dialog_Update(1);
				ನಿಲ್ಲಿಸು;

			ಸ್ಥಿತಿ PSP_UTILITY_DIALOG_QUIT:
				sce_Utility_ಸಂದೇಶ_Dialog_Shutdown_ಆರಂಭ();
				ನಿಲ್ಲಿಸು;
		}

		sce_Display_Wait_Vblank_ಆರಂಭ();
		sce_Gu_ಅದಲುಬದಲು_Buffers();

	} ಆಗ (ಸ್ಥಿತಿ_2 != PSP_UTILITY_DIALOG_NONE);

    // cleanup
	ಆದರೆ (gu_ಬಫರ್)
	{
		ಪದ_temporal_gu(gu_ಬಫರ್);
	}

	// success
	ಆದರೆ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ಫಲಿತಾಂಶ_YES)
		*buttonID = messageboxdata->buttons[0].buttonID;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_ಫಲಿತಾಂಶ_NO)
		*buttonID = messageboxdata->buttons[1].buttonID;
	ಇಲ್ಲದಿದ್ದರೆ
		*buttonID = messageboxdata->buttons[0].buttonID;

	ಹಿಂತಿರುಗಿ true;
}

VideoBootStrap PSP_bootstrap = {
    "psp",
    "PSP Video Driver",
    PSP_Create,
    PSP_Show_ಸಂದೇಶ_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool PSP_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    ಆದರೆ (!PSP_EventInit(_this)) {
        ಹಿಂತಿರುಗಿ false;  // error string would already be set
    }

    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.w = PSP_SCREEN_ಅಗಲ;
    ಬಹುಲಕ.h = PSP_SCREEN_ಎತ್ತರ;
    ಬಹುಲಕ.refresh_ದರ = 60.0f;

    // 32 bpp for default
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_ABGR8888;

    ಆದರೆ (SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ PSP_VideoQuit(SDL_VideoDevice *_this)
{
    PSP_EventQuit(_this);
}

bool PSP_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.w = PSP_SCREEN_ಅಗಲ;
    ಬಹುಲಕ.h = PSP_SCREEN_ಎತ್ತರ;
    ಬಹುಲಕ.refresh_ದರ = 60.0f;

    // 32 bpp for default
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_ABGR8888;
    SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ);

    // 16 bpp secondary mode
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_BGR565;
    SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ);
    ಹಿಂತಿರುಗಿ true;
}

bool PSP_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿಸು EGLCHK(stmt)                           \
    ಮಾಡು {                                       \
        EGLint err;                            \
                                               \
        stmt;                                  \
        err = eglGetError();                   \
        ಆದರೆ (err != EGL_SUCCESS) {              \
            SDL_ಗಣ_Error("EGL error %d", err); \
            ಹಿಂತಿರುಗಿ true;                          \
        }                                      \
    } ಆಗ (0)

bool PSP_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata;

    // Allocate window internal data
    wdata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!wdata) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Setup driver data for this window
    ಕಿಟಕಿ->ಆಂತರಿಕ = wdata;

    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);

    // Window has been successfully created
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ PSP_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
bool PSP_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}
ಶೂನ್ಯ PSP_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ PSP_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ PSP_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ PSP_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ PSP_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ PSP_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ PSP_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ PSP_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}

bool PSP_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ PSP_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    ಅಕ್ಷರ list[0x20000] __attribute__((aligned(64))); // Needed for sceGuStart to work
    ಪೂರ್ಣಾಂಕ ಮುಗಿದ = 0;
    ಪೂರ್ಣಾಂಕ ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ = 128;
    ಶೂನ್ಯ *received_ಪಠ್ಯ = SDL_calloc(ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ, ಗಾತ್ರ(Uint16));
    ಆದರೆ (!received_ಪಠ್ಯ) {
        ಹಿಂತಿರುಗಿ;
    }
    ಶೂನ್ಯ *received_ಪಠ್ಯ_ಆರಂಭ = received_ಪಠ್ಯ;
    ಶೂನ್ಯ *ಪಠ್ಯ_string = ಖಾಲಿ;
    ಶೂನ್ಯ *string_ಗಮ್ಯ_send = ಖಾಲಿ;

    SDL_iconv_t iconv = ಖಾಲಿ;
    size_t outbytesleft = ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ;
    size_t inbytesleft = ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ * ಗಾತ್ರ(Uint16);
    size_t iconv_ಫಲಿತಾಂಶ = 0;

    Sce_Utility_Osk_ದತ್ತಾಂಶ ದತ್ತಾಂಶ;
    SceUtilityOskParams params;

    ದತ್ತಾಂಶ.language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
    ದತ್ತಾಂಶ.ಸಾಲುಗಳು = 1;
    ದತ್ತಾಂಶ.unk_24 = 1;
    ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(props)) {
    ಪೂರ್ವನಿಯೋಜಿತ:
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_NAME:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_EMAIL:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_USERNAME:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_PASSWORD_HIDDEN:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_PASSWORD_VISIBLE:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
        ದತ್ತಾಂಶ.inputtype = PSP_UTILITY_OSK_INPUTTYPE_LATIN_DIGIT;
        ನಿಲ್ಲಿಸು;
    }
    ದತ್ತಾಂಶ.desc = ಖಾಲಿ;
    ದತ್ತಾಂಶ.intext = ಖಾಲಿ;
    ದತ್ತಾಂಶ.outtextlength = ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ;
    ದತ್ತಾಂಶ.outtextlimit = ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ;
    ದತ್ತಾಂಶ.outtext = (ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ *)received_ಪಠ್ಯ;

    params.ತಳ.ಗಾತ್ರ_2 = ಗಾತ್ರ(params);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.ತಳ.language);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.ತಳ.button_ಅದಲುಬದಲು);
    params.ತಳ.graphicsThread = 17;
    params.ತಳ.accessThread = 19;
    params.ತಳ.fontThread = 18;
    params.ತಳ.soundThread = 16;
    params.datacount = 1;
    params.ದತ್ತಾಂಶ = &ದತ್ತಾಂಶ;

    sce_Utility_Osk_Init_ಆರಂಭ(&params);

    SDL_SendScreenKeyboardShown();

    ಆಗ (!ಮುಗಿದ) {
        sce_Gu_ಆರಂಭ(GU_ನೇರ, list);
        sceGuClearColor(0);
        sceGuClear(GU_COLOR_ಬಫರ್_ಬಿಟ್);
        ಆದರೆ (sce_Gu_Get_ಸ್ಥಿತಿ(GU_ಆಳ_TEST)) {
            sce_Gu_Clear_ಆಳ(0);
            sceGuClear(GU_ಆಳ_ಬಫರ್_ಬಿಟ್);
        }
        sce_Gu_ಮುಕ್ತಾಯ();
        sceGuSync(0, 0);

        ಆಯ್ಕೆ (sce_Utility_Osk_Get_ಸ್ಥಿತಿ()) {
        ಸ್ಥಿತಿ PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityOskUpdate(1);
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ PSP_UTILITY_DIALOG_QUIT:
            sce_Utility_Osk_Shutdown_ಆರಂಭ();
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ PSP_UTILITY_DIALOG_NONE:
            ಮುಗಿದ = 1;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        sce_Display_Wait_Vblank_ಆರಂಭ();
        sce_Gu_ಅದಲುಬದಲು_Buffers();
    }

    // Convert input list to strings
    iconv = SDL_iconv_open("UTF-8", "UCS-2-INTERNAL");
    ಆದರೆ ((size_t)iconv == SDL_ICONV_ERROR) {
        ಹೋಗು ಮುಗಿದ;
    }

    string_ಗಮ್ಯ_send = SDL_calloc(ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ, 3); // utf-8 characters can use up to 4 bytes, but the PSP keyboard has characters up to 3
    ಆದರೆ (!string_ಗಮ್ಯ_send) {
        SDL_iconv_close(iconv);
        ಹೋಗು ಮುಗಿದ;
    }

    ಪಠ್ಯ_string = string_ಗಮ್ಯ_send;
    outbytesleft = ಒಳಹರಿವು_ಪಠ್ಯ_ಉದ್ದಳತೆ * 3;
    iconv_ಫಲಿತಾಂಶ = SDL_iconv(iconv, (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **)&received_ಪಠ್ಯ, (size_t *)&inbytesleft, (ಅಕ್ಷರ **)&ಪಠ್ಯ_string, &outbytesleft);
    ಆದರೆ (iconv_ಫಲಿತಾಂಶ == 0) {
        SDL_Send_Keyboard_ಪಠ್ಯ(string_ಗಮ್ಯ_send);
    }

    SDL_iconv_close(iconv);

ಮುಗಿದ:
    SDL_free(string_ಗಮ್ಯ_send);
    SDL_free(received_ಪಠ್ಯ_ಆರಂಭ);

    SDL_SendScreenKeyboardHidden();
}

ಶೂನ್ಯ PSP_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_PSP

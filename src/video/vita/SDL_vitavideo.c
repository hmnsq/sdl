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

#ifdef SDL_VIDEO_DRIVER_VITA

// SDL internals
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_keyboard_c.h"

// VITA declarations
#ಅನ್ತರ್ಭಾವ <psp2/kernel/processmgr.h>
#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitatouch.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitakeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitamouse_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitaframebuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitamessagebox.h"

#ಯದಿ defined(SDL_VIDEO_VITA_PVR)
#define VITA_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#define VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#define VITA_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define VITA_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#define VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#endif

SDL_Window *Vita_Window;

ಸ್ಥಿರ ಶೂನ್ಯ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *VITA_Create(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
#ifdef SDL_VIDEO_VITA_PIB
    SDL_GLDriverData *gldata;
#endif
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoDevice));
    ಯದಿ (!device) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_VideoData));
    ಯದಿ (!phdata) {
        SDL_free(device);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
#ifdef SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriverData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_GLDriverData));
    ಯದಿ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    device->gl_data = gldata;
    phdata->egl_initialized = true;
#endif
    phdata->ime_active = false;

    device->internal = phdata;

    // Setup amount of available displays and current display
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಮುಕ್ತ = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_CreateWindow;
    device->SetWindowTitle = VITA_SetWindowTitle;
    device->SetWindowPosition = VITA_SetWindowPosition;
    device->SetWindowSize = VITA_SetWindowSize;
    device->ShowWindow = VITA_ShowWindow;
    device->HideWindow = VITA_HideWindow;
    device->RaiseWindow = VITA_RaiseWindow;
    device->MaximizeWindow = VITA_MaximizeWindow;
    device->MinimizeWindow = VITA_MinimizeWindow;
    device->RestoreWindow = VITA_RestoreWindow;
    device->SetWindowMouseGrab = VITA_SetWindowGrab;
    device->SetWindowKeyboardGrab = VITA_SetWindowGrab;
    device->DestroyWindow = VITA_DestroyWindow;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#ಯದಿ defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#ifdef SDL_VIDEO_VITA_PVR_OGL
    ಯದಿ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_LoadLibrary = VITA_GL_LoadLibrary;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_GetProcAddress = VITA_GL_GetProcAddress;
    } ಅನ್ಯಥಾ {
#endif
        device->GL_LoadLibrary = VITA_GLES_LoadLibrary;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_GetProcAddress = VITA_GLES_GetProcAddress;
#ifdef SDL_VIDEO_VITA_PVR_OGL
    }
#endif

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_SetSwapInterval = VITA_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = VITA_GLES_GetSwapInterval;
    device->GL_SwapWindow = VITA_GLES_SwapWindow;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#endif

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಪ್ರತ್ಯಾಗಮ device;
}

VideoBootStrap VITA_bootstrap = {
    "vita",
    "VITA Video Driver",
    VITA_Create,
    VITA_ShowMessageBox,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_DisplayMode mode;
#ifdef SDL_VIDEO_VITA_PVR
    ಧ್ರುವ ವರ್ಣ *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#endif
    SDL_zero(mode);

#ifdef SDL_VIDEO_VITA_PVR
    ಯದಿ (res) {
        // 1088i for PSTV (Or Sharpscale)
        ಯದಿ (SDL_strncmp(res, "1080", 4) == 0) {
            mode.w = 1920;
            mode.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        ಅನ್ಯಥಾ ಯದಿ (SDL_strncmp(res, "720", 3) == 0) {
            mode.w = 1280;
            mode.h = 725;
        }
    }
    // 544p
    ಅನ್ಯಥಾ {
#endif
        mode.w = 960;
        mode.h = 544;
#ifdef SDL_VIDEO_VITA_PVR
    }
#endif

    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    ಯದಿ (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;
#ifdef SDL_VIDEO_VITA_PVR
    Psp2NativeWindow win;
    ಪೂರ್ಣಾಙ್ಕ temp_major = 2;
    ಪೂರ್ಣಾಙ್ಕ temp_minor = 1;
    ಪೂರ್ಣಾಙ್ಕ temp_profile = 0;
#endif

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_WindowData));
    ಯದಿ (!wdata) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    // Vita can only have one window
    ಯದಿ (Vita_Window) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Only one window supported");
    }

    Vita_Window = window;

#ifdef SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_WINDOW;
    win.ಅಂಕೆ_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    ಯದಿ (window->w == 1920) {
        win.windowSize = PSP2_WINDOW_1920X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    ಅನ್ಯಥಾ ಯದಿ (window->w == 1280) {
        win.windowSize = PSP2_WINDOW_1280X725;
    }
    // 544p
    ಅನ್ಯಥಾ {
        win.windowSize = PSP2_WINDOW_960X544;
    }
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        ಯದಿ (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            temp_major = _this->gl_config.major_version;
            temp_minor = _this->gl_config.minor_version;
            temp_profile = _this->gl_config.profile_mask;

            _this->gl_config.major_version = 2;
            _this->gl_config.minor_version = 1;
            _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, window, &win);
        ಯದಿ (wdata->egl_surface == EGL_NO_SURFACE) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Could not create GLES window surface");
        }
        ಯದಿ (use_opengl) {
            // Revert
            _this->gl_config.major_version = temp_major;
            _this->gl_config.minor_version = temp_minor;
            _this->gl_config.profile_mask = temp_profile;
        }
    }
#endif

    // fix input, we need to find a better way
    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}
ಶೂನ್ಯ VITA_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ಶೂನ್ಯ VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);

    window->internal = ರಿಕ್ತ;
    Vita_Window = ರಿಕ್ತ;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ true;
}

#ifndef SCE_IME_LANGUAGE_ENGLISH_US
#define SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#endif

ಸ್ಥಿರ ಶೂನ್ಯ utf16_to_utf8(ಧ್ರುವ uint16_t *src, uint8_t *dst)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; src[i]; i++) {
        ಯದಿ (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } ಅನ್ಯಥಾ ಯದಿ (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } ಅನ್ಯಥಾ ಯದಿ ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } ಅನ್ಯಥಾ {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#ifdef SDL_VIDEO_VITA_PVR
SceWChar16 libime_out[SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1];
ವರ್ಣ libime_initval[8] = { 1 };
SceImeCaret caret_rev;

ಶೂನ್ಯ VITA_ImeEventHandler(ಶೂನ್ಯ *arg, ಧ್ರುವ SceImeEventData *e)
{
    SDL_VideoData *videodata = (SDL_VideoData *)arg;
    uint8_t utf8_buffer[SCE_IME_MAX_TEXT_LENGTH];
    ವಿಕಲ್ಪ (e->id) {
    ಪಕ್ಷ SCE_IME_EVENT_UPDATE_TEXT:
        ಯದಿ (e->param.text.caretIndex == 0) {
            SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sceImeSetText((SceWChar16 *)libime_initval, 4);
        } ಅನ್ಯಥಾ {
            utf16_to_utf8((SceWChar16 *)&libime_out[1], utf8_buffer);
            ಯದಿ (utf8_buffer[0] == ' ') {
                SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_SPACE);
            } ಅನ್ಯಥಾ {
                SDL_SendKeyboardText((ಧ್ರುವ ವರ್ಣ *)utf8_buffer);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1) * ಪರಿಮಾಣ(SceWChar16)));
            caret_rev.index = 1;
            sceImeSetCaret(&caret_rev);
            sceImeSetText((SceWChar16 *)libime_initval, 4);
        }
        ಭಙ್ಗ;
    ಪಕ್ಷ SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_RETURN);
        ಭಙ್ಗ;
    ಪಕ್ಷ SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_active = false;
        SDL_SendScreenKeyboardHidden();
        ಭಙ್ಗ;
    }
}
#endif // SDL_VIDEO_VITA_PVR

ಶೂನ್ಯ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;
    SceInt32 res;

#ifdef SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_BUFFER_SIZE / ಪರಿಮಾಣ(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1) * ಪರಿಮಾಣ(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
    ಸ್ವಭಾವ:
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT:
        param.type = SCE_IME_TYPE_DEFAULT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
        param.type = SCE_IME_TYPE_ಸಂಖ್ಯೆ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_ಸಂಖ್ಯೆ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_ಸಂಖ್ಯೆ;
        ಭಙ್ಗ;
    }
    param.option = 0;
    ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    ಯದಿ (!SDL_Get_Text_ಒಳಹರಿವು_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    ಯದಿ (SDL_Get_Text_ಒಳಹರಿವು_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.ಒಳಹರಿವು_Text_Buffer = libime_out;
    param.maxTextLength = SCE_IME_MAX_TEXT_LENGTH;
    param.handler = VITA_ImeEventHandler;
    param.filter = ರಿಕ್ತ;
    param.initialText = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    ಯದಿ (res < 0) {
        SDL_SetError("Failed to init IME");
        ಪ್ರತ್ಯಾಗಮ;
    }

#ಅನ್ಯಥಾ
    SceWChar16 *title = u"";
    SceWChar16 *text = u"";

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.supportedLanguages = 0;
    param.languagesForced = SCE_FALSE;
    param.type = SCE_IME_TYPE_DEFAULT;
    param.option = 0;
    param.textBoxMode = SCE_IME_DIALOG_TEXTBOX_MODE_WITH_CLEAR;
    param.maxTextLength = SCE_IME_DIALOG_MAX_TEXT_LENGTH;

    param.title = title;
    param.initialText = text;
    param.ಒಳಹರಿವು_Text_Buffer = videodata->ime_buffer;

    res = sceImeDialogInit(&param);
    ಯದಿ (res < 0) {
        SDL_SetError("Failed to init IME dialog");
        ಪ್ರತ್ಯಾಗಮ;
    }

#endif

    videodata->ime_active = true;

    SDL_SendScreenKeyboardShown();
}

ಶೂನ್ಯ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifndef SDL_VIDEO_VITA_PVR
    SDL_VideoData *videodata = _this->internal;

    SceCommonDialogStatus dialogStatus = sceImeDialogGetStatus();

    ವಿಕಲ್ಪ (dialogStatus) {
    ಸ್ವಭಾವ:
    ಪಕ್ಷ SCE_COMMON_DIALOG_STATUS_NONE:
    ಪಕ್ಷ SCE_COMMON_DIALOG_STATUS_RUNNING:
        ಭಙ್ಗ;
    ಪಕ್ಷ SCE_COMMON_DIALOG_STATUS_FINISHED:
        sceImeDialogTerm();
        ಭಙ್ಗ;
    }

    videodata->ime_active = false;

    SDL_SendScreenKeyboardHidden();
#endif
}

ಶೂನ್ಯ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#ifndef SDL_VIDEO_VITA_PVR
    SDL_VideoData *videodata = _this->internal;
#endif

    ಯದಿ (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#ifndef SDL_VIDEO_VITA_PVR
    ಯದಿ (videodata->ime_active == true) {
        // update IME status. Terminate, if finished
        SceCommonDialogStatus dialogStatus = sceImeDialogGetStatus();
        ಯದಿ (dialogStatus == SCE_COMMON_DIALOG_STATUS_FINISHED) {
            uint8_t utf8_buffer[SCE_IME_DIALOG_MAX_TEXT_LENGTH];

            SceImeDialogResult result;
            SDL_zero(result);
            sceImeDialogGetResult(&result);

            // Convert UTF16 to UTF8
            utf16_to_utf8(videodata->ime_buffer, utf8_buffer);

            // Send SDL event
            SDL_SendKeyboardText((ಧ್ರುವ ವರ್ಣ *)utf8_buffer);

            // Send enter key only on enter
            ಯದಿ (result.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sceImeDialogTerm();

            videodata->ime_active = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#endif
}

#endif // SDL_VIDEO_DRIVER_VITA

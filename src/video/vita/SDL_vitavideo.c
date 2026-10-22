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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

// SDL internals
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_keyboard_c.h"

// VITA declarations
#ଅନ୍ତର୍ଭାଵ <psp2/kernel/processmgr.h>
#ଅନ୍ତର୍ଭାଵ "SDL_vitavideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitatouch.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitakeyboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitamouse_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitaframebuffer.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitamessagebox.h"

#ଯଦି defined(SDL_VIDEO_VITA_PVR)
#define VITA_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#define VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#define VITA_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#define VITA_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#define VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#endif

SDL_Window *Vita_Window;

ସ୍ଥିର ଶୂନ୍ୟ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

ସ୍ଥିର SDL_VideoDevice *VITA_Create(ଶୂନ୍ୟ)
{
    SDL_VideoDevice *device;
    SDL_VideoData *phdata;
#ifdef SDL_VIDEO_VITA_PIB
    SDL_GLDriverData *gldata;
#endif
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ଆକାର(SDL_VideoDevice));
    ଯଦି (!device) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_VideoData *)SDL_calloc(1, ଆକାର(SDL_VideoData));
    ଯଦି (!phdata) {
        SDL_free(device);
        ଫେରନ୍ତୁ ଖାଲି;
    }
#ifdef SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriverData *)SDL_calloc(1, ଆକାର(SDL_GLDriverData));
    ଯଦି (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    device->gl_data = gldata;
    phdata->egl_initialized = true;
#endif
    phdata->ime_active = false;

    device->internal = phdata;

    // Setup amount of available displays and current display
    device->ଅଙ୍କ_displays = 0;

    // Set device free function
    device->ମୁକ୍ତ = VITA_Destroy;

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

#ଯଦି defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#ifdef SDL_VIDEO_VITA_PVR_OGL
    ଯଦି (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_LoadLibrary = VITA_GL_LoadLibrary;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_GetProcAddress = VITA_GL_GetProcAddress;
    } ଅନ୍ୟଥା {
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

    ଫେରନ୍ତୁ device;
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
    ଅଚଳ ଅକ୍ଷର *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#endif
    SDL_zero(mode);

#ifdef SDL_VIDEO_VITA_PVR
    ଯଦି (res) {
        // 1088i for PSTV (Or Sharpscale)
        ଯଦି (SDL_strncmp(res, "1080", 4) == 0) {
            mode.w = 1920;
            mode.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        ଅନ୍ୟଥା ଯଦି (SDL_strncmp(res, "720", 3) == 0) {
            mode.w = 1280;
            mode.h = 725;
        }
    }
    // 544p
    ଅନ୍ୟଥା {
#endif
        mode.w = 960;
        mode.h = 544;
#ifdef SDL_VIDEO_VITA_PVR
    }
#endif

    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    ଯଦି (SDL_AddBasicVideoDisplay(&mode) == 0) {
        ଫେରନ୍ତୁ false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *wdata;
#ifdef SDL_VIDEO_VITA_PVR
    Psp2NativeWindow win;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା temp_major = 2;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା temp_minor = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା temp_profile = 0;
#endif

    // Allocate window internal data
    wdata = (SDL_WindowData *)SDL_calloc(1, ଆକାର(SDL_WindowData));
    ଯଦି (!wdata) {
        ଫେରନ୍ତୁ false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    // Vita can only have one window
    ଯଦି (Vita_Window) {
        ଫେରନ୍ତୁ SDL_SetError("Only one window supported");
    }

    Vita_Window = window;

#ifdef SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_WINDOW;
    win.ଅଙ୍କ_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    ଯଦି (window->w == 1920) {
        win.windowSize = PSP2_WINDOW_1920X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    ଅନ୍ୟଥା ଯଦି (window->w == 1280) {
        win.windowSize = PSP2_WINDOW_1280X725;
    }
    // 544p
    ଅନ୍ୟଥା {
        win.windowSize = PSP2_WINDOW_960X544;
    }
    ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        ଯଦି (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            temp_major = _this->gl_config.major_version;
            temp_minor = _this->gl_config.minor_version;
            temp_profile = _this->gl_config.profile_mask;

            _this->gl_config.major_version = 2;
            _this->gl_config.minor_version = 1;
            _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, window, &win);
        ଯଦି (wdata->egl_surface == EGL_NO_SURFACE) {
            ଫେରନ୍ତୁ SDL_SetError("Could not create GLES window surface");
        }
        ଯଦି (use_opengl) {
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
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}
ଶୂନ୍ୟ VITA_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
ଶୂନ୍ୟ VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data;

    data = window->internal;
    SDL_free(data);

    window->internal = ଖାଲି;
    Vita_Window = ଖାଲି;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ true;
}

#ifndef SCE_IME_LANGUAGE_ENGLISH_US
#define SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#endif

ସ୍ଥିର ଶୂନ୍ୟ utf16_to_utf8(ଅଚଳ uint16_t *src, uint8_t *dst)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; src[i]; i++) {
        ଯଦି (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } ଅନ୍ୟଥା ଯଦି (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } ଅନ୍ୟଥା ଯଦି ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } ଅନ୍ୟଥା {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#ifdef SDL_VIDEO_VITA_PVR
SceWChar16 libime_out[SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1];
ଅକ୍ଷର libime_initval[8] = { 1 };
SceImeCaret caret_rev;

ଶୂନ୍ୟ VITA_ImeEventHandler(ଶୂନ୍ୟ *arg, ଅଚଳ SceImeEventData *e)
{
    SDL_VideoData *videodata = (SDL_VideoData *)arg;
    uint8_t utf8_buffer[SCE_IME_MAX_TEXT_LENGTH];
    ବାଛ (e->id) {
    ସ୍ଥିତି SCE_IME_EVENT_UPDATE_TEXT:
        ଯଦି (e->param.text.caretIndex == 0) {
            SDL_Send_Keyboard_ଚାବି_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sceImeSetText((SceWChar16 *)libime_initval, 4);
        } ଅନ୍ୟଥା {
            utf16_to_utf8((SceWChar16 *)&libime_out[1], utf8_buffer);
            ଯଦି (utf8_buffer[0] == ' ') {
                SDL_Send_Keyboard_ଚାବି_Auto_Release(0, SDL_SCANCODE_SPACE);
            } ଅନ୍ୟଥା {
                SDL_SendKeyboardText((ଅଚଳ ଅକ୍ଷର *)utf8_buffer);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1) * ଆକାର(SceWChar16)));
            caret_rev.index = 1;
            sceImeSetCaret(&caret_rev);
            sceImeSetText((SceWChar16 *)libime_initval, 4);
        }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_ଚାବି_Auto_Release(0, SDL_SCANCODE_RETURN);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_active = false;
        SDL_SendScreenKeyboardHidden();
        ଭାଙ୍ଗ;
    }
}
#endif // SDL_VIDEO_VITA_PVR

ଶୂନ୍ୟ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_VideoData *videodata = _this->internal;
    SceInt32 res;

#ifdef SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_BUFFER_SIZE / ଆକାର(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1) * ଆକାର(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    ବାଛ (SDL_Get_Text_ନିବେଶ_Type(props)) {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT:
        param.type = SCE_IME_TYPE_DEFAULT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା:
        param.type = SCE_IME_TYPE_ସଂଖ୍ୟା;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_ସଂଖ୍ୟା;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_ସଂଖ୍ୟା_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_ସଂଖ୍ୟା;
        ଭାଙ୍ଗ;
    }
    param.option = 0;
    ଯଦି (SDL_Get_Text_ନିବେଶ_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    ଯଦି (!SDL_Get_Text_ନିବେଶ_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    ଯଦି (SDL_Get_Text_ନିବେଶ_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.ନିବେଶ_Text_Buffer = libime_out;
    param.maxTextLength = SCE_IME_MAX_TEXT_LENGTH;
    param.handler = VITA_ImeEventHandler;
    param.filter = ଖାଲି;
    param.initialText = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    ଯଦି (res < 0) {
        SDL_SetError("Failed to init IME");
        ଫେରନ୍ତୁ;
    }

#ଅନ୍ୟଥା
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
    param.ନିବେଶ_Text_Buffer = videodata->ime_buffer;

    res = sceImeDialogInit(&param);
    ଯଦି (res < 0) {
        SDL_SetError("Failed to init IME dialog");
        ଫେରନ୍ତୁ;
    }

#endif

    videodata->ime_active = true;

    SDL_SendScreenKeyboardShown();
}

ଶୂନ୍ୟ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
#ifndef SDL_VIDEO_VITA_PVR
    SDL_VideoData *videodata = _this->internal;

    SceCommonDialogStatus dialogStatus = sceImeDialogGetStatus();

    ବାଛ (dialogStatus) {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
    ସ୍ଥିତି SCE_COMMON_DIALOG_STATUS_NONE:
    ସ୍ଥିତି SCE_COMMON_DIALOG_STATUS_RUNNING:
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SCE_COMMON_DIALOG_STATUS_FINISHED:
        sceImeDialogTerm();
        ଭାଙ୍ଗ;
    }

    videodata->ime_active = false;

    SDL_SendScreenKeyboardHidden();
#endif
}

ଶୂନ୍ୟ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#ifndef SDL_VIDEO_VITA_PVR
    SDL_VideoData *videodata = _this->internal;
#endif

    ଯଦି (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#ifndef SDL_VIDEO_VITA_PVR
    ଯଦି (videodata->ime_active == true) {
        // update IME status. Terminate, if finished
        SceCommonDialogStatus dialogStatus = sceImeDialogGetStatus();
        ଯଦି (dialogStatus == SCE_COMMON_DIALOG_STATUS_FINISHED) {
            uint8_t utf8_buffer[SCE_IME_DIALOG_MAX_TEXT_LENGTH];

            SceImeDialogResult result;
            SDL_zero(result);
            sceImeDialogGetResult(&result);

            // Convert UTF16 to UTF8
            utf16_to_utf8(videodata->ime_buffer, utf8_buffer);

            // Send SDL event
            SDL_SendKeyboardText((ଅଚଳ ଅକ୍ଷର *)utf8_buffer);

            // Send enter key only on enter
            ଯଦି (result.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_ଚାବି_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sceImeDialogTerm();

            videodata->ime_active = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#endif
}

#endif // SDL_VIDEO_DRIVER_VITA

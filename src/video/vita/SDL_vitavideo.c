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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_VITA

// SDL internals
#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../events/SDL_keyboard_c.h"

// VITA declarations
#समावेश <psp2/kernel/processmgr.h>
#समावेश "SDL_vitavideo.h"
#समावेश "SDL_vitatouch.h"
#समावेश "SDL_vitakeyboard.h"
#समावेश "SDL_vitamouse_c.h"
#समावेश "SDL_vitaframebuffer.h"
#समावेश "SDL_vitamessagebox.h"

#अगर defined(SDL_VIDEO_VITA_PVR)
#घोषणा VITA_GLES_GetProcAddress  SDL_EGL_GetProcAddressInternal
#घोषणा VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#घोषणा VITA_GLES_SetSwapInterval SDL_EGL_SetSwapInterval
#घोषणा VITA_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#घोषणा VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#पूर्ण_अगर

SDL_Window *Vita_Window;

अटल व्योम VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->internal);
    SDL_free(device);
}

अटल SDL_VideoDevice *VITA_Create(व्योम)
{
    SDL_VideoDevice *device;
    SDL_Video_तथ्य *phdata;
#अगर_घोषित SDL_VIDEO_VITA_PIB
    SDL_GLDriver_तथ्य *gldata;
#पूर्ण_अगर
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, माप(SDL_VideoDevice));
    अगर (!device) {
        वापस शून्य;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_तथ्य *)SDL_calloc(1, माप(SDL_Video_तथ्य));
    अगर (!phdata) {
        SDL_free(device);
        वापस शून्य;
    }
#अगर_घोषित SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_तथ्य *)SDL_calloc(1, माप(SDL_GLDriver_तथ्य));
    अगर (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        वापस शून्य;
    }
    device->gl_तथ्य = gldata;
    phdata->egl_initialized = true;
#पूर्ण_अगर
    phdata->ime_active = false;

    device->internal = phdata;

    // Setup amount of available displays and current display
    device->अंक_displays = 0;

    // Set device free function
    device->मुक्त = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_CreateWindow;
    device->SetWindowTitle = VITA_SetWindowTitle;
    device->SetWindowPosition = VITA_SetWindowPosition;
    device->Set_Window_आकार = VITA_Set_Window_आकार;
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

#अगर defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#अगर_घोषित SDL_VIDEO_VITA_PVR_OGL
    अगर (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_LoadLibrary = VITA_GL_LoadLibrary;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_GetProcAddress = VITA_GL_GetProcAddress;
    } अन्यथा {
#पूर्ण_अगर
        device->GL_LoadLibrary = VITA_GLES_LoadLibrary;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_GetProcAddress = VITA_GLES_GetProcAddress;
#अगर_घोषित SDL_VIDEO_VITA_PVR_OGL
    }
#पूर्ण_अगर

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_SetSwapInterval = VITA_GLES_SetSwapInterval;
    device->GL_GetSwapInterval = VITA_GLES_GetSwapInterval;
    device->GL_SwapWindow = VITA_GLES_SwapWindow;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#पूर्ण_अगर

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    वापस device;
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
#अगर_घोषित SDL_VIDEO_VITA_PVR
    स्थिर अक्षर *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#पूर्ण_अगर
    SDL_zero(mode);

#अगर_घोषित SDL_VIDEO_VITA_PVR
    अगर (res) {
        // 1088i for PSTV (Or Sharpscale)
        अगर (SDL_strncmp(res, "1080", 4) == 0) {
            mode.w = 1920;
            mode.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        अन्यथा अगर (SDL_strncmp(res, "720", 3) == 0) {
            mode.w = 1280;
            mode.h = 725;
        }
    }
    // 544p
    अन्यथा {
#पूर्ण_अगर
        mode.w = 960;
        mode.h = 544;
#अगर_घोषित SDL_VIDEO_VITA_PVR
    }
#पूर्ण_अगर

    mode.refresh_rate = 60.0f;

    // 32 bpp for default
    mode.format = SDL_PIXELFORMAT_ABGR8888;

    अगर (SDL_AddBasicVideoDisplay(&mode) == 0) {
        वापस false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    वापस true;
}

व्योम VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_तथ्य *wdata;
#अगर_घोषित SDL_VIDEO_VITA_PVR
    Psp2NativeWindow win;
    पूर्णांक अस्थायी_major = 2;
    पूर्णांक अस्थायी_minor = 1;
    पूर्णांक अस्थायी_profile = 0;
#पूर्ण_अगर

    // Allocate window internal data
    wdata = (SDL_Window_तथ्य *)SDL_calloc(1, माप(SDL_Window_तथ्य));
    अगर (!wdata) {
        वापस false;
    }

    // Setup driver data for this window
    window->internal = wdata;

    // Vita can only have one window
    अगर (Vita_Window) {
        वापस SDL_SetError("Only one window supported");
    }

    Vita_Window = window;

#अगर_घोषित SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_WINDOW;
    win.अंक_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    अगर (window->w == 1920) {
        win.window_आकार = PSP2_WINDOW_1920X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    अन्यथा अगर (window->w == 1280) {
        win.window_आकार = PSP2_WINDOW_1280X725;
    }
    // 544p
    अन्यथा {
        win.window_आकार = PSP2_WINDOW_960X544;
    }
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        अगर (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            अस्थायी_major = _this->gl_config.major_version;
            अस्थायी_minor = _this->gl_config.minor_version;
            अस्थायी_profile = _this->gl_config.profile_mask;

            _this->gl_config.major_version = 2;
            _this->gl_config.minor_version = 1;
            _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, window, &win);
        अगर (wdata->egl_surface == EGL_NO_SURFACE) {
            वापस SDL_SetError("Could not create GLES window surface");
        }
        अगर (use_opengl) {
            // Revert
            _this->gl_config.major_version = अस्थायी_major;
            _this->gl_config.minor_version = अस्थायी_minor;
            _this->gl_config.profile_mask = अस्थायी_profile;
        }
    }
#पूर्ण_अगर

    // fix input, we need to find a better way
    SDL_SetKeyboardFocus(window);

    // Window has been successfully created
    वापस true;
}

व्योम VITA_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool VITA_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    वापस SDL_Unsupported();
}
व्योम VITA_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम VITA_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम VITA_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम VITA_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम VITA_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम VITA_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
व्योम VITA_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
}
bool VITA_SetWindowGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    वापस true;
}

व्योम VITA_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य;

    तथ्य = window->internal;
    SDL_free(तथ्य);

    window->internal = शून्य;
    Vita_Window = शून्य;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    वापस true;
}

#अगर_अघोषित SCE_IME_LANGUAGE_ENGLISH_US
#घोषणा SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#पूर्ण_अगर

अटल व्योम utf16_to_utf8(स्थिर uint16_t *src, uint8_t *dst)
{
    पूर्णांक i;
    क्रम (i = 0; src[i]; i++) {
        अगर (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } अन्यथा अगर (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } अन्यथा अगर ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } अन्यथा {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#अगर_घोषित SDL_VIDEO_VITA_PVR
SceWChar16 libime_out[SCE_IME_MAX_PREEDIT_लंबाई + SCE_IME_MAX_TEXT_लंबाई + 1];
अक्षर libime_initval[8] = { 1 };
SceImeCaret caret_rev;

व्योम VITA_ImeEventHandler(व्योम *arg, स्थिर Sce_Ime_Event_तथ्य *e)
{
    SDL_Video_तथ्य *videodata = (SDL_Video_तथ्य *)arg;
    uint8_t utf8_बफर[SCE_IME_MAX_TEXT_लंबाई];
    चयन (e->id) {
    हाल SCE_IME_EVENT_UPDATE_TEXT:
        अगर (e->param.text.caret_सूचकांक == 0) {
            SDL_Send_Keyboard_कुंजी_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sceImeSetText((SceWChar16 *)libime_initval, 4);
        } अन्यथा {
            utf16_to_utf8((SceWChar16 *)&libime_out[1], utf8_बफर);
            अगर (utf8_बफर[0] == ' ') {
                SDL_Send_Keyboard_कुंजी_Auto_Release(0, SDL_SCANCODE_SPACE);
            } अन्यथा {
                SDL_SendKeyboardText((स्थिर अक्षर *)utf8_बफर);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_लंबाई + SCE_IME_MAX_TEXT_लंबाई + 1) * माप(SceWChar16)));
            caret_rev.सूचकांक = 1;
            sceImeSetCaret(&caret_rev);
            sceImeSetText((SceWChar16 *)libime_initval, 4);
        }
        अवरोध;
    हाल SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_कुंजी_Auto_Release(0, SDL_SCANCODE_RETURN);
        अवरोध;
    हाल SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_active = false;
        SDL_SendScreenKeyboardHidden();
        अवरोध;
    }
}
#पूर्ण_अगर // SDL_VIDEO_VITA_PVR

व्योम VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID props)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SceInt32 res;

#अगर_घोषित SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_बफर_आकार / माप(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_out, 0, ((SCE_IME_MAX_PREEDIT_लंबाई + SCE_IME_MAX_TEXT_लंबाई + 1) * माप(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    चयन (SDL_Get_Text_निवेश_Type(props)) {
    शेष:
    हाल SDL_TEXTINPUT_TYPE_TEXT:
        param.type = SCE_IME_TYPE_DEFAULT;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या:
        param.type = SCE_IME_TYPE_संख्या;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_संख्या;
        अवरोध;
    हाल SDL_TEXTINPUT_TYPE_संख्या_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_संख्या;
        अवरोध;
    }
    param.option = 0;
    अगर (SDL_Get_Text_निवेश_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    अगर (!SDL_Get_Text_निवेश_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    अगर (SDL_Get_Text_निवेश_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.निवेश_Text_बफर = libime_out;
    param.max_Text_लंबाई = SCE_IME_MAX_TEXT_लंबाई;
    param.handler = VITA_ImeEventHandler;
    param.filter = शून्य;
    param.initialText = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    अगर (res < 0) {
        SDL_SetError("Failed to init IME");
        वापस;
    }

#अन्यथा
    SceWChar16 *title = u"";
    SceWChar16 *text = u"";

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.supportedLanguages = 0;
    param.languagesForced = SCE_FALSE;
    param.type = SCE_IME_TYPE_DEFAULT;
    param.option = 0;
    param.textBoxMode = SCE_IME_DIALOG_TEXTBOX_MODE_WITH_CLEAR;
    param.max_Text_लंबाई = SCE_IME_DIALOG_MAX_TEXT_लंबाई;

    param.title = title;
    param.initialText = text;
    param.निवेश_Text_बफर = videodata->ime_बफर;

    res = sceImeDialogInit(&param);
    अगर (res < 0) {
        SDL_SetError("Failed to init IME dialog");
        वापस;
    }

#पूर्ण_अगर

    videodata->ime_active = true;

    SDL_SendScreenKeyboardShown();
}

व्योम VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_Window *window)
{
#अगर_अघोषित SDL_VIDEO_VITA_PVR
    SDL_Video_तथ्य *videodata = _this->internal;

    SceCommonDialogStatus dialogStatus = sceImeDialogGetStatus();

    चयन (dialogStatus) {
    शेष:
    हाल SCE_COMMON_DIALOG_STATUS_NONE:
    हाल SCE_COMMON_DIALOG_STATUS_RUNNING:
        अवरोध;
    हाल SCE_COMMON_DIALOG_STATUS_FINISHED:
        sceImeDialogTerm();
        अवरोध;
    }

    videodata->ime_active = false;

    SDL_SendScreenKeyboardHidden();
#पूर्ण_अगर
}

व्योम VITA_PumpEvents(SDL_VideoDevice *_this)
{
#अगर_अघोषित SDL_VIDEO_VITA_PVR
    SDL_Video_तथ्य *videodata = _this->internal;
#पूर्ण_अगर

    अगर (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#अगर_अघोषित SDL_VIDEO_VITA_PVR
    अगर (videodata->ime_active == true) {
        // update IME status. Terminate, if finished
        SceCommonDialogStatus dialogStatus = sceImeDialogGetStatus();
        अगर (dialogStatus == SCE_COMMON_DIALOG_STATUS_FINISHED) {
            uint8_t utf8_बफर[SCE_IME_DIALOG_MAX_TEXT_लंबाई];

            Sce_Ime_Dialog_परिणाम परिणाम;
            SDL_zero(परिणाम);
            sce_Ime_Dialog_Get_परिणाम(&परिणाम);

            // Convert UTF16 to UTF8
            utf16_to_utf8(videodata->ime_बफर, utf8_बफर);

            // Send SDL event
            SDL_SendKeyboardText((स्थिर अक्षर *)utf8_बफर);

            // Send enter key only on enter
            अगर (परिणाम.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_कुंजी_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sceImeDialogTerm();

            videodata->ime_active = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#पूर्ण_अगर
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VITA

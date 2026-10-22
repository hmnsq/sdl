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

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VITA

// SDL internals
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"

// VITA declarations
#अन्तर्भाव <psp2/kernel/processmgr.h>
#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitatouch.h"
#अन्तर्भाव "SDL_vitakeyboard.h"
#अन्तर्भाव "SDL_vitamouse_c.h"
#अन्तर्भाव "SDL_vitaframebuffer.h"
#अन्तर्भाव "SDL_vitamessagebox.h"

#यदि defined(SDL_VIDEO_VITA_PVR)
#परिभाषय VITA_GLES_Get_Proc_स्थानाङ्कः  SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्
#परिभाषय VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#परिभाषय VITA_GLES_समुच्चयः_Swap_Interval SDL_EGL_समुच्चयः_Swap_Interval
#परिभाषय VITA_GLES_GetSwapInterval SDL_EGL_GetSwapInterval
#परिभाषय VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#यदि_अन्तः

SDL_गवाक्षः *Vita_गवाक्षः;

स्थिर शून्य VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->आन्तरिकम्);
    SDL_free(device);
}

स्थिर SDL_VideoDevice *VITA_Create(शून्य)
{
    SDL_VideoDevice *device;
    SDL_Video_दत्त *phdata;
#यदि_परिभाषितम् SDL_VIDEO_VITA_PIB
    SDL_GLDriver_दत्त *gldata;
#यदि_अन्तः
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, परिमाण(SDL_VideoDevice));
    यदि (!device) {
        प्रत्यागम रिक्त;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_दत्त *)SDL_calloc(1, परिमाण(SDL_Video_दत्त));
    यदि (!phdata) {
        SDL_free(device);
        प्रत्यागम रिक्त;
    }
#यदि_परिभाषितम् SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_दत्त *)SDL_calloc(1, परिमाण(SDL_GLDriver_दत्त));
    यदि (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        प्रत्यागम रिक्त;
    }
    device->gl_दत्त = gldata;
    phdata->egl_initialized = true;
#यदि_अन्तः
    phdata->ime_सक्रिय = false;

    device->आन्तरिकम् = phdata;

    // Setup amount of available displays and current display
    device->अङ्कः_displays = 0;

    // Set device free function
    device->मुक्त = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Title = VITA_समुच्चयः_गवाक्षः_Title;
    device->समुच्चयः_गवाक्षः_Position = VITA_समुच्चयः_गवाक्षः_Position;
    device->समुच्चयः_गवाक्षः_आकार = VITA_समुच्चयः_गवाक्षः_आकार;
    device->Show_गवाक्षः = VITA_Show_गवाक्षः;
    device->Hide_गवाक्षः = VITA_Hide_गवाक्षः;
    device->Raise_गवाक्षः = VITA_Raise_गवाक्षः;
    device->Maximize_गवाक्षः = VITA_Maximize_गवाक्षः;
    device->Minimize_गवाक्षः = VITA_Minimize_गवाक्षः;
    device->Restore_गवाक्षः = VITA_Restore_गवाक्षः;
    device->समुच्चयः_गवाक्षः_Mouse_Grab = VITA_समुच्चयः_गवाक्षः_Grab;
    device->समुच्चयः_गवाक्षः_Keyboard_Grab = VITA_समुच्चयः_गवाक्षः_Grab;
    device->Destroy_गवाक्षः = VITA_Destroy_गवाक्षः;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#यदि defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR_OGL
    यदि (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_आरोपय_Library = VITA_GL_आरोपय_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_स्थानाङ्कः = VITA_GL_Get_Proc_स्थानाङ्कः;
    } अन्यथा {
#यदि_अन्तः
        device->GL_आरोपय_Library = VITA_GLES_आरोपय_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_स्थानाङ्कः = VITA_GLES_Get_Proc_स्थानाङ्कः;
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR_OGL
    }
#यदि_अन्तः

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_समुच्चयः_Swap_Interval = VITA_GLES_समुच्चयः_Swap_Interval;
    device->GL_GetSwapInterval = VITA_GLES_GetSwapInterval;
    device->GL_Swap_गवाक्षः = VITA_GLES_Swap_गवाक्षः;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#यदि_अन्तः

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    प्रत्यागम device;
}

VideoBootStrap VITA_bootstrap = {
    "vita",
    "VITA Video Driver",
    VITA_Create,
    VITA_Show_सन्देशः_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_बहुलकम् बहुलकम्;
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
    ध्रुव वर्ण *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#यदि_अन्तः
    SDL_zero(बहुलकम्);

#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
    यदि (res) {
        // 1088i for PSTV (Or Sharpscale)
        यदि (SDL_strncmp(res, "1080", 4) == 0) {
            बहुलकम्.w = 1920;
            बहुलकम्.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        अन्यथा यदि (SDL_strncmp(res, "720", 3) == 0) {
            बहुलकम्.w = 1280;
            बहुलकम्.h = 725;
        }
    }
    // 544p
    अन्यथा {
#यदि_अन्तः
        बहुलकम्.w = 960;
        बहुलकम्.h = 544;
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
    }
#यदि_अन्तः

    बहुलकम्.refresh_दरः = 60.0f;

    // 32 bpp for default
    बहुलकम्.format = SDL_PIXELFORMAT_ABGR8888;

    यदि (SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्) == 0) {
        प्रत्यागम false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    प्रत्यागम true;
}

शून्य VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *wdata;
#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
    Psp2_Native_गवाक्षः win;
    पूर्णाङ्क अस्थायी_major = 2;
    पूर्णाङ्क अस्थायी_minor = 1;
    पूर्णाङ्क अस्थायी_profile = 0;
#यदि_अन्तः

    // Allocate window internal data
    wdata = (SDL_गवाक्षः_दत्त *)SDL_calloc(1, परिमाण(SDL_गवाक्षः_दत्त));
    यदि (!wdata) {
        प्रत्यागम false;
    }

    // Setup driver data for this window
    गवाक्षः->आन्तरिकम् = wdata;

    // Vita can only have one window
    यदि (Vita_गवाक्षः) {
        प्रत्यागम SDL_समुच्चयः_Error("Only one window supported");
    }

    Vita_गवाक्षः = गवाक्षः;

#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_गवाक्षः;
    win.अङ्कः_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    यदि (गवाक्षः->w == 1920) {
        win.गवाक्षः_आकार = PSP2_गवाक्षः_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    अन्यथा यदि (गवाक्षः->w == 1280) {
        win.गवाक्षः_आकार = PSP2_गवाक्षः_1280_X725;
    }
    // 544p
    अन्यथा {
        win.गवाक्षः_आकार = PSP2_गवाक्षः_960_X544;
    }
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        यदि (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            अस्थायी_major = _this->gl_config.major_संस्करणम्;
            अस्थायी_minor = _this->gl_config.minor_संस्करणम्;
            अस्थायी_profile = _this->gl_config.profile_आवरणम्;

            _this->gl_config.major_संस्करणम् = 2;
            _this->gl_config.minor_संस्करणम् = 1;
            _this->gl_config.profile_आवरणम् = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, &win);
        यदि (wdata->egl_surface == EGL_NO_SURFACE) {
            प्रत्यागम SDL_समुच्चयः_Error("Could not create GLES window surface");
        }
        यदि (use_opengl) {
            // Revert
            _this->gl_config.major_संस्करणम् = अस्थायी_major;
            _this->gl_config.minor_संस्करणम् = अस्थायी_minor;
            _this->gl_config.profile_आवरणम् = अस्थायी_profile;
        }
    }
#यदि_अन्तः

    // fix input, we need to find a better way
    SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);

    // Window has been successfully created
    प्रत्यागम true;
}

शून्य VITA_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
bool VITA_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम SDL_Unsupported();
}
शून्य VITA_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य VITA_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य VITA_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य VITA_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य VITA_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य VITA_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
शून्य VITA_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
}
bool VITA_समुच्चयः_गवाक्षः_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    प्रत्यागम true;
}

शून्य VITA_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त;

    दत्त = गवाक्षः->आन्तरिकम्;
    SDL_free(दत्त);

    गवाक्षः->आन्तरिकम् = रिक्त;
    Vita_गवाक्षः = रिक्त;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    प्रत्यागम true;
}

#यदि_अपरिभाषितम् SCE_IME_LANGUAGE_ENGLISH_US
#परिभाषय SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#यदि_अन्तः

स्थिर शून्य utf16_गन्तव्यम्_utf8(ध्रुव uint16_t *src, uint8_t *dst)
{
    पूर्णाङ्क i;
    प्रति (i = 0; src[i]; i++) {
        यदि (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } अन्यथा यदि (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } अन्यथा यदि ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
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

#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR
SceWChar16 libime_बहिर्गमनम्[SCE_IME_MAX_PREEDIT_दीर्घता + SCE_IME_MAX_TEXT_दीर्घता + 1];
वर्ण libime_initval[8] = { 1 };
SceImeCaret caret_rev;

शून्य VITA_ImeEventHandler(शून्य *arg, ध्रुव Sce_Ime_Event_दत्त *e)
{
    SDL_Video_दत्त *videodata = (SDL_Video_दत्त *)arg;
    uint8_t utf8_बफर[SCE_IME_MAX_TEXT_दीर्घता];
    विकल्प (e->id) {
    पक्ष SCE_IME_EVENT_UPDATE_TEXT:
        यदि (e->param.text.caret_सूचकांक == 0) {
            SDL_Send_Keyboard_कुञ्चिका_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_समुच्चयः_Text((SceWChar16 *)libime_initval, 4);
        } अन्यथा {
            utf16_गन्तव्यम्_utf8((SceWChar16 *)&libime_बहिर्गमनम्[1], utf8_बफर);
            यदि (utf8_बफर[0] == ' ') {
                SDL_Send_Keyboard_कुञ्चिका_Auto_Release(0, SDL_SCANCODE_SPACE);
            } अन्यथा {
                SDL_SendKeyboardText((ध्रुव वर्ण *)utf8_बफर);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_बहिर्गमनम्, 0, ((SCE_IME_MAX_PREEDIT_दीर्घता + SCE_IME_MAX_TEXT_दीर्घता + 1) * परिमाण(SceWChar16)));
            caret_rev.सूचकांक = 1;
            sce_Ime_समुच्चयः_Caret(&caret_rev);
            sce_Ime_समुच्चयः_Text((SceWChar16 *)libime_initval, 4);
        }
        भङ्ग;
    पक्ष SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_कुञ्चिका_Auto_Release(0, SDL_SCANCODE_RETURN);
        भङ्ग;
    पक्ष SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_सक्रिय = false;
        SDL_SendScreenKeyboardHidden();
        भङ्ग;
    }
}
#यदि_अन्तः // SDL_VIDEO_VITA_PVR

शून्य VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SceInt32 res;

#यदि_परिभाषितम् SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_बफर_आकार / परिमाण(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_बहिर्गमनम्, 0, ((SCE_IME_MAX_PREEDIT_दीर्घता + SCE_IME_MAX_TEXT_दीर्घता + 1) * परिमाण(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
    स्वभाव:
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        param.type = SCE_IME_TYPE_DEFAULT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या:
        param.type = SCE_IME_TYPE_सङ्ख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_सङ्ख्या;
        भङ्ग;
    पक्ष SDL_TEXTINPUT_TYPE_सङ्ख्या_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_सङ्ख्या;
        भङ्ग;
    }
    param.option = 0;
    यदि (SDL_Get_Text_निवेशः_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    यदि (!SDL_Get_Text_निवेशः_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    यदि (SDL_Get_Text_निवेशः_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.निवेशः_Text_बफर = libime_बहिर्गमनम्;
    param.max_Text_दीर्घता = SCE_IME_MAX_TEXT_दीर्घता;
    param.handler = VITA_ImeEventHandler;
    param.filter = रिक्त;
    param.initialText = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    यदि (res < 0) {
        SDL_समुच्चयः_Error("Failed to init IME");
        प्रत्यागम;
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
    param.text_Box_बहुलकम् = SCE_IME_DIALOG_TEXTBOX_बहुलकम्_WITH_CLEAR;
    param.max_Text_दीर्घता = SCE_IME_DIALOG_MAX_TEXT_दीर्घता;

    param.title = title;
    param.initialText = text;
    param.निवेशः_Text_बफर = videodata->ime_बफर;

    res = sceImeDialogInit(&param);
    यदि (res < 0) {
        SDL_समुच्चयः_Error("Failed to init IME dialog");
        प्रत्यागम;
    }

#यदि_अन्तः

    videodata->ime_सक्रिय = true;

    SDL_SendScreenKeyboardShown();
}

शून्य VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
#यदि_अपरिभाषितम् SDL_VIDEO_VITA_PVR
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;

    Sce_Common_Dialog_स्थितिः dialog_स्थितिः = sce_Ime_Dialog_Get_स्थितिः();

    विकल्प (dialog_स्थितिः) {
    स्वभाव:
    पक्ष SCE_COMMON_DIALOG_स्थितिः_NONE:
    पक्ष SCE_COMMON_DIALOG_स्थितिः_RUNNING:
        भङ्ग;
    पक्ष SCE_COMMON_DIALOG_स्थितिः_परिसमाप्तम्:
        sce_Ime_Dialog_पदांशः();
        भङ्ग;
    }

    videodata->ime_सक्रिय = false;

    SDL_SendScreenKeyboardHidden();
#यदि_अन्तः
}

शून्य VITA_PumpEvents(SDL_VideoDevice *_this)
{
#यदि_अपरिभाषितम् SDL_VIDEO_VITA_PVR
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
#यदि_अन्तः

    यदि (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#यदि_अपरिभाषितम् SDL_VIDEO_VITA_PVR
    यदि (videodata->ime_सक्रिय == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_स्थितिः dialog_स्थितिः = sce_Ime_Dialog_Get_स्थितिः();
        यदि (dialog_स्थितिः == SCE_COMMON_DIALOG_स्थितिः_परिसमाप्तम्) {
            uint8_t utf8_बफर[SCE_IME_DIALOG_MAX_TEXT_दीर्घता];

            Sce_Ime_Dialog_परिणाम परिणाम;
            SDL_zero(परिणाम);
            sce_Ime_Dialog_Get_परिणाम(&परिणाम);

            // Convert UTF16 to UTF8
            utf16_गन्तव्यम्_utf8(videodata->ime_बफर, utf8_बफर);

            // Send SDL event
            SDL_SendKeyboardText((ध्रुव वर्ण *)utf8_बफर);

            // Send enter key only on enter
            यदि (परिणाम.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_कुञ्चिका_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_पदांशः();

            videodata->ime_सक्रिय = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#यदि_अन्तः
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_VITA

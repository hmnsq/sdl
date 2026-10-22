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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

// SDL internals
#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/SDL_keyboard_c.h"

// VITA declarations
#شامل <psp2/kernel/processmgr.h>
#شامل "SDL_vitavideo.h"
#شامل "SDL_vitatouch.h"
#شامل "SDL_vitakeyboard.h"
#شامل "SDL_vitamouse_c.h"
#شامل "SDL_vitaframebuffer.h"
#شامل "SDL_vitamessagebox.h"

#اگر defined(SDL_VIDEO_VITA_PVR)
#تعریف_کرو VITA_GLES_Get_Proc_پتہ  SDL_EGL_Get_Proc_پتہ_اندرونی
#تعریف_کرو VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کرو VITA_GLES_سیٹ_تبادلہ_Interval SDL_EGL_سیٹ_تبادلہ_Interval
#تعریف_کرو VITA_GLES_Get_تبادلہ_Interval SDL_EGL_Get_تبادلہ_Interval
#تعریف_کرو VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#اگر_ختم

SDL_کھڑکی *Vita_کھڑکی;

ساکن خالی VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی_2);
    SDL_free(device);
}

ساکن SDL_VideoDevice *VITA_Create(خالی)
{
    SDL_VideoDevice *device;
    SDL_Video_ڈیٹا *phdata;
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PIB
    SDL_GLDriver_ڈیٹا *gldata;
#اگر_ختم
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    اگر (!device) {
        واپس تہی;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_ڈیٹا *)SDL_calloc(1, حجم(SDL_Video_ڈیٹا));
    اگر (!phdata) {
        SDL_free(device);
        واپس تہی;
    }
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_ڈیٹا *)SDL_calloc(1, حجم(SDL_GLDriver_ڈیٹا));
    اگر (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        واپس تہی;
    }
    device->gl_ڈیٹا = gldata;
    phdata->egl_initialized = true;
#اگر_ختم
    phdata->ime_فعال = false;

    device->اندرونی_2 = phdata;

    // Setup amount of available displays and current display
    device->عدد_displays = 0;

    // Set device free function
    device->آزاد = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = VITA_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = VITA_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_سائز = VITA_سیٹ_کھڑکی_سائز;
    device->Show_کھڑکی = VITA_Show_کھڑکی;
    device->Hide_کھڑکی = VITA_Hide_کھڑکی;
    device->Raise_کھڑکی = VITA_Raise_کھڑکی;
    device->Maximize_کھڑکی = VITA_Maximize_کھڑکی;
    device->Minimize_کھڑکی = VITA_Minimize_کھڑکی;
    device->Restore_کھڑکی = VITA_Restore_کھڑکی;
    device->سیٹ_کھڑکی_Mouse_Grab = VITA_سیٹ_کھڑکی_Grab;
    device->سیٹ_کھڑکی_Keyboard_Grab = VITA_سیٹ_کھڑکی_Grab;
    device->Destroy_کھڑکی = VITA_Destroy_کھڑکی;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#اگر defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
    اگر (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_بھرو_Library = VITA_GL_بھرو_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_پتہ = VITA_GL_Get_Proc_پتہ;
    } ورنہ {
#اگر_ختم
        device->GL_بھرو_Library = VITA_GLES_بھرو_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_پتہ = VITA_GLES_Get_Proc_پتہ;
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
    }
#اگر_ختم

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_سیٹ_تبادلہ_Interval = VITA_GLES_سیٹ_تبادلہ_Interval;
    device->GL_Get_تبادلہ_Interval = VITA_GLES_Get_تبادلہ_Interval;
    device->GL_تبادلہ_کھڑکی = VITA_GLES_تبادلہ_کھڑکی;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#اگر_ختم

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    واپس device;
}

VideoBootStrap VITA_bootstrap = {
    "vita",
    "VITA Video Driver",
    VITA_Create,
    VITA_Show_پیغام_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    ثابت حرف *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#اگر_ختم
    SDL_zero(منوال);

#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    اگر (res) {
        // 1088i for PSTV (Or Sharpscale)
        اگر (SDL_strncmp(res, "1080", 4) == 0) {
            منوال.w = 1920;
            منوال.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        ورنہ اگر (SDL_strncmp(res, "720", 3) == 0) {
            منوال.w = 1280;
            منوال.h = 725;
        }
    }
    // 544p
    ورنہ {
#اگر_ختم
        منوال.w = 960;
        منوال.h = 544;
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    }
#اگر_ختم

    منوال.refresh_شرح = 60.0f;

    // 32 bpp for default
    منوال.format = SDL_PIXELFORMAT_ABGR8888;

    اگر (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        واپس false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    واپس true;
}

خالی VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_ڈیٹا *wdata;
#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    Psp2_Native_کھڑکی win;
    صحیح عارضی_major = 2;
    صحیح عارضی_minor = 1;
    صحیح عارضی_profile = 0;
#اگر_ختم

    // Allocate window internal data
    wdata = (SDL_کھڑکی_ڈیٹا *)SDL_calloc(1, حجم(SDL_کھڑکی_ڈیٹا));
    اگر (!wdata) {
        واپس false;
    }

    // Setup driver data for this window
    کھڑکی->اندرونی_2 = wdata;

    // Vita can only have one window
    اگر (Vita_کھڑکی) {
        واپس SDL_سیٹ_Error("Only one window supported");
    }

    Vita_کھڑکی = کھڑکی;

#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_کھڑکی;
    win.عدد_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    اگر (کھڑکی->w == 1920) {
        win.کھڑکی_سائز = PSP2_کھڑکی_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    ورنہ اگر (کھڑکی->w == 1280) {
        win.کھڑکی_سائز = PSP2_کھڑکی_1280_X725;
    }
    // 544p
    ورنہ {
        win.کھڑکی_سائز = PSP2_کھڑکی_960_X544;
    }
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        اگر (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            عارضی_major = _this->gl_config.major_نسخہ;
            عارضی_minor = _this->gl_config.minor_نسخہ;
            عارضی_profile = _this->gl_config.profile_نقاب;

            _this->gl_config.major_نسخہ = 2;
            _this->gl_config.minor_نسخہ = 1;
            _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, &win);
        اگر (wdata->egl_surface == EGL_NO_SURFACE) {
            واپس SDL_سیٹ_Error("Could not create GLES window surface");
        }
        اگر (use_opengl) {
            // Revert
            _this->gl_config.major_نسخہ = عارضی_major;
            _this->gl_config.minor_نسخہ = عارضی_minor;
            _this->gl_config.profile_نقاب = عارضی_profile;
        }
    }
#اگر_ختم

    // fix input, we need to find a better way
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    // Window has been successfully created
    واپس true;
}

خالی VITA_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool VITA_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    واپس SDL_Unsupported();
}
خالی VITA_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی VITA_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی VITA_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی VITA_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی VITA_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی VITA_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
خالی VITA_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool VITA_سیٹ_کھڑکی_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    واپس true;
}

خالی VITA_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا;

    ڈیٹا = کھڑکی->اندرونی_2;
    SDL_free(ڈیٹا);

    کھڑکی->اندرونی_2 = تہی;
    Vita_کھڑکی = تہی;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    واپس true;
}

#اگر_غیر_تعریف_شدہ SCE_IME_LANGUAGE_ENGLISH_US
#تعریف_کرو SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#اگر_ختم

ساکن خالی utf16_مقصد_utf8(ثابت uint16_t *src, uint8_t *dst)
{
    صحیح i;
    برائے (i = 0; src[i]; i++) {
        اگر (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } ورنہ اگر (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } ورنہ اگر ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } ورنہ {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR
SceWChar16 libime_برآمد[SCE_IME_MAX_PREEDIT_لمبائی + SCE_IME_MAX_متن_لمبائی + 1];
حرف libime_initval[8] = { 1 };
SceImeCaret caret_rev;

خالی VITA_ImeEventHandler(خالی *arg, ثابت Sce_Ime_Event_ڈیٹا *e)
{
    SDL_Video_ڈیٹا *videodata = (SDL_Video_ڈیٹا *)arg;
    uint8_t utf8_بفر[SCE_IME_MAX_متن_لمبائی];
    انتخاب (e->id) {
    حالت SCE_IME_EVENT_UPDATE_متن:
        اگر (e->param.متن.caret_اشاریہ == 0) {
            SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_سیٹ_متن((SceWChar16 *)libime_initval, 4);
        } ورنہ {
            utf16_مقصد_utf8((SceWChar16 *)&libime_برآمد[1], utf8_بفر);
            اگر (utf8_بفر[0] == ' ') {
                SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_SPACE);
            } ورنہ {
                SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_برآمد, 0, ((SCE_IME_MAX_PREEDIT_لمبائی + SCE_IME_MAX_متن_لمبائی + 1) * حجم(SceWChar16)));
            caret_rev.اشاریہ = 1;
            sce_Ime_سیٹ_Caret(&caret_rev);
            sce_Ime_سیٹ_متن((SceWChar16 *)libime_initval, 4);
        }
        توڑو;
    حالت SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_RETURN);
        توڑو;
    حالت SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_فعال = false;
        SDL_SendScreenKeyboardHidden();
        توڑو;
    }
}
#اگر_ختم // SDL_VIDEO_VITA_PVR

خالی VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
    SceInt32 res;

#اگر_تعریف_شدہ SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_بفر_سائز / حجم(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_برآمد, 0, ((SCE_IME_MAX_PREEDIT_لمبائی + SCE_IME_MAX_متن_لمبائی + 1) * حجم(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    انتخاب (SDL_Get_متن_داخلہ_Type(props)) {
    طےشدہ:
    حالت SDL_TEXTINPUT_TYPE_متن:
        param.type = SCE_IME_TYPE_DEFAULT;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر:
        param.type = SCE_IME_TYPE_نمبر;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_نمبر;
        توڑو;
    حالت SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_نمبر;
        توڑو;
    }
    param.option = 0;
    اگر (SDL_Get_متن_داخلہ_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    اگر (!SDL_Get_متن_داخلہ_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    اگر (SDL_Get_متن_داخلہ_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.داخلہ_متن_بفر = libime_برآمد;
    param.max_متن_لمبائی = SCE_IME_MAX_متن_لمبائی;
    param.handler = VITA_ImeEventHandler;
    param.filter = تہی;
    param.initial_متن = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    اگر (res < 0) {
        SDL_سیٹ_Error("Failed to init IME");
        واپس;
    }

#ورنہ
    SceWChar16 *title = u"";
    SceWChar16 *متن = u"";

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.supportedLanguages = 0;
    param.languagesForced = SCE_FALSE;
    param.type = SCE_IME_TYPE_DEFAULT;
    param.option = 0;
    param.متن_Box_منوال = SCE_IME_DIALOG_TEXTBOX_منوال_WITH_CLEAR;
    param.max_متن_لمبائی = SCE_IME_DIALOG_MAX_متن_لمبائی;

    param.title = title;
    param.initial_متن = متن;
    param.داخلہ_متن_بفر = videodata->ime_بفر;

    res = sceImeDialogInit(&param);
    اگر (res < 0) {
        SDL_سیٹ_Error("Failed to init IME dialog");
        واپس;
    }

#اگر_ختم

    videodata->ime_فعال = true;

    SDL_SendScreenKeyboardShown();
}

خالی VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#اگر_غیر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;

    Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();

    انتخاب (dialog_حالت) {
    طےشدہ:
    حالت SCE_COMMON_DIALOG_حالت_NONE:
    حالت SCE_COMMON_DIALOG_حالت_RUNNING:
        توڑو;
    حالت SCE_COMMON_DIALOG_حالت_ختم_شدہ:
        sce_Ime_Dialog_رکن();
        توڑو;
    }

    videodata->ime_فعال = false;

    SDL_SendScreenKeyboardHidden();
#اگر_ختم
}

خالی VITA_PumpEvents(SDL_VideoDevice *_this)
{
#اگر_غیر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    SDL_Video_ڈیٹا *videodata = _this->اندرونی_2;
#اگر_ختم

    اگر (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#اگر_غیر_تعریف_شدہ SDL_VIDEO_VITA_PVR
    اگر (videodata->ime_فعال == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();
        اگر (dialog_حالت == SCE_COMMON_DIALOG_حالت_ختم_شدہ) {
            uint8_t utf8_بفر[SCE_IME_DIALOG_MAX_متن_لمبائی];

            Sce_Ime_Dialog_نتیجہ نتیجہ;
            SDL_zero(نتیجہ);
            sce_Ime_Dialog_Get_نتیجہ(&نتیجہ);

            // Convert UTF16 to UTF8
            utf16_مقصد_utf8(videodata->ime_بفر, utf8_بفر);

            // Send SDL event
            SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);

            // Send enter key only on enter
            اگر (نتیجہ.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_رکن();

            videodata->ime_فعال = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#اگر_ختم
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA

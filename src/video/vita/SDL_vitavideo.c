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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

// SDL internals
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../events/SDL_keyboard_c.h"

// VITA declarations
#ضمن <psp2/kernel/processmgr.h>
#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitatouch.h"
#ضمن "SDL_vitakeyboard.h"
#ضمن "SDL_vitamouse_c.h"
#ضمن "SDL_vitaframebuffer.h"
#ضمن "SDL_vitamessagebox.h"

#إذا defined(SDL_VIDEO_VITA_PVR)
#تعریف_کرو VITA_GLES_Get_Proc_پتہ  SDL_EGL_Get_Proc_پتہ_اندرونی
#تعریف_کرو VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کرو VITA_GLES_سیٹ_وٹاندرا_Interval SDL_EGL_سیٹ_وٹاندرا_Interval
#تعریف_کرو VITA_GLES_Get_وٹاندرا_Interval SDL_EGL_Get_وٹاندرا_Interval
#تعریف_کرو VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#جے_انت

SDL_کھڑکی *Vita_کھڑکی;

ساكن فراغ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندرونی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *VITA_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_انکڑے *phdata;
#جے_تعریف_شدہ SDL_VIDEO_VITA_PIB
    SDL_GLDriver_انکڑے *gldata;
#جے_انت
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_انکڑے *)SDL_calloc(1, حجم(SDL_Video_انکڑے));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }
#جے_تعریف_شدہ SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_انکڑے *)SDL_calloc(1, حجم(SDL_GLDriver_انکڑے));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_انکڑے = gldata;
    phdata->egl_initialized = true;
#جے_انت
    phdata->ime_سرگرم = false;

    device->اندرونی = phdata;

    // Setup amount of available displays and current display
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_کھڑکی;
    device->سیٹ_کھڑکی_Title = VITA_سیٹ_کھڑکی_Title;
    device->سیٹ_کھڑکی_Position = VITA_سیٹ_کھڑکی_Position;
    device->سیٹ_کھڑکی_ناپ = VITA_سیٹ_کھڑکی_ناپ;
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

#إذا defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_لدو_Library = VITA_GL_لدو_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_پتہ = VITA_GL_Get_Proc_پتہ;
    } وإلا {
#جے_انت
        device->GL_لدو_Library = VITA_GLES_لدو_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_پتہ = VITA_GLES_Get_Proc_پتہ;
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR_OGL
    }
#جے_انت

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_سیٹ_وٹاندرا_Interval = VITA_GLES_سیٹ_وٹاندرا_Interval;
    device->GL_Get_وٹاندرا_Interval = VITA_GLES_Get_وٹاندرا_Interval;
    device->GL_وٹاندرا_کھڑکی = VITA_GLES_وٹاندرا_کھڑکی;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#جے_انت

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    أرجع device;
}

VideoBootStrap VITA_bootstrap = {
    "vita",
    "VITA Video Driver",
    VITA_Create,
    VITA_Show_سنیہا_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_منوال منوال;
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR
    ثابت حرف *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#جے_انت
    SDL_zero(منوال);

#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR
    إذا (res) {
        // 1088i for PSTV (Or Sharpscale)
        إذا (SDL_strncmp(res, "1080", 4) == 0) {
            منوال.w = 1920;
            منوال.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        وإلا إذا (SDL_strncmp(res, "720", 3) == 0) {
            منوال.w = 1280;
            منوال.h = 725;
        }
    }
    // 544p
    وإلا {
#جے_انت
        منوال.w = 960;
        منوال.h = 544;
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR
    }
#جے_انت

    منوال.refresh_شرح = 60.0f;

    // 32 bpp for default
    منوال.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_جوڑو_Basic_Video_Display(&منوال) == 0) {
        أرجع false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    أرجع true;
}

فراغ VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props)
{
    SDL_کھڑکی_انکڑے *wdata;
#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR
    Psp2_Native_کھڑکی win;
    صحيح عارضی_major = 2;
    صحيح عارضی_minor = 1;
    صحيح عارضی_profile = 0;
#جے_انت

    // Allocate window internal data
    wdata = (SDL_کھڑکی_انکڑے *)SDL_calloc(1, حجم(SDL_کھڑکی_انکڑے));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    کھڑکی->اندرونی = wdata;

    // Vita can only have one window
    إذا (Vita_کھڑکی) {
        أرجع SDL_سیٹ_Error("Only one window supported");
    }

    Vita_کھڑکی = کھڑکی;

#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_کھڑکی;
    win.عدد_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    إذا (کھڑکی->w == 1920) {
        win.کھڑکی_ناپ = PSP2_کھڑکی_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    وإلا إذا (کھڑکی->w == 1280) {
        win.کھڑکی_ناپ = PSP2_کھڑکی_1280_X725;
    }
    // 544p
    وإلا {
        win.کھڑکی_ناپ = PSP2_کھڑکی_960_X544;
    }
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        إذا (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            عارضی_major = _this->gl_config.major_نسخہ;
            عارضی_minor = _this->gl_config.minor_نسخہ;
            عارضی_profile = _this->gl_config.profile_نقاب;

            _this->gl_config.major_نسخہ = 2;
            _this->gl_config.minor_نسخہ = 1;
            _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, کھڑکی, &win);
        إذا (wdata->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سیٹ_Error("Could not create GLES window surface");
        }
        إذا (use_opengl) {
            // Revert
            _this->gl_config.major_نسخہ = عارضی_major;
            _this->gl_config.minor_نسخہ = عارضی_minor;
            _this->gl_config.profile_نقاب = عارضی_profile;
        }
    }
#جے_انت

    // fix input, we need to find a better way
    SDL_سیٹ_Keyboard_Focus(کھڑکی);

    // Window has been successfully created
    أرجع true;
}

فراغ VITA_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool VITA_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    أرجع SDL_Unsupported();
}
فراغ VITA_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ VITA_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ VITA_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ VITA_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ VITA_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ VITA_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
فراغ VITA_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
}
bool VITA_سیٹ_کھڑکی_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed)
{
    أرجع true;
}

فراغ VITA_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے;

    انکڑے = کھڑکی->اندرونی;
    SDL_free(انکڑے);

    کھڑکی->اندرونی = عدم;
    Vita_کھڑکی = عدم;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

#جے_بنا_تعریف SCE_IME_LANGUAGE_ENGLISH_US
#تعریف_کرو SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#جے_انت

ساكن فراغ utf16_منزل_utf8(ثابت uint16_t *src, uint8_t *dst)
{
    صحيح i;
    لكل (i = 0; src[i]; i++) {
        إذا (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } وإلا إذا (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } وإلا إذا ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } وإلا {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR
SceWChar16 libime_باہرلا[SCE_IME_MAX_PREEDIT_لمائی + SCE_IME_MAX_متن_لمائی + 1];
حرف libime_initval[8] = { 1 };
SceImeCaret caret_rev;

فراغ VITA_ImeEventHandler(فراغ *arg, ثابت Sce_Ime_Event_انکڑے *e)
{
    SDL_Video_انکڑے *videodata = (SDL_Video_انکڑے *)arg;
    uint8_t utf8_بفر[SCE_IME_MAX_متن_لمائی];
    بدل (e->id) {
    حالة SCE_IME_EVENT_UPDATE_متن:
        إذا (e->param.متن.caret_اشاریہ == 0) {
            SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_سیٹ_متن((SceWChar16 *)libime_initval, 4);
        } وإلا {
            utf16_منزل_utf8((SceWChar16 *)&libime_باہرلا[1], utf8_بفر);
            إذا (utf8_بفر[0] == ' ') {
                SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_SPACE);
            } وإلا {
                SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_باہرلا, 0, ((SCE_IME_MAX_PREEDIT_لمائی + SCE_IME_MAX_متن_لمائی + 1) * حجم(SceWChar16)));
            caret_rev.اشاریہ = 1;
            sce_Ime_سیٹ_Caret(&caret_rev);
            sce_Ime_سیٹ_متن((SceWChar16 *)libime_initval, 4);
        }
        اكسر;
    حالة SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_RETURN);
        اكسر;
    حالة SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_سرگرم = false;
        SDL_SendScreenKeyboardHidden();
        اكسر;
    }
}
#جے_انت // SDL_VIDEO_VITA_PVR

فراغ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    SDL_Video_انکڑے *videodata = _this->اندرونی;
    SceInt32 res;

#جے_تعریف_شدہ SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_بفر_ناپ / حجم(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_باہرلا, 0, ((SCE_IME_MAX_PREEDIT_لمائی + SCE_IME_MAX_متن_لمائی + 1) * حجم(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    بدل (SDL_Get_متن_داخلہ_Type(props)) {
    افتراضي:
    حالة SDL_TEXTINPUT_TYPE_متن:
        param.type = SCE_IME_TYPE_DEFAULT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_متن_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر:
        param.type = SCE_IME_TYPE_نمبر;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_نمبر;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_نمبر_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_نمبر;
        اكسر;
    }
    param.option = 0;
    إذا (SDL_Get_متن_داخلہ_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    إذا (!SDL_Get_متن_داخلہ_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    إذا (SDL_Get_متن_داخلہ_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.داخلہ_متن_بفر = libime_باہرلا;
    param.max_متن_لمائی = SCE_IME_MAX_متن_لمائی;
    param.handler = VITA_ImeEventHandler;
    param.filter = عدم;
    param.initial_متن = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    إذا (res < 0) {
        SDL_سیٹ_Error("Failed to init IME");
        أرجع;
    }

#وإلا
    SceWChar16 *title = u"";
    SceWChar16 *متن = u"";

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.supportedLanguages = 0;
    param.languagesForced = SCE_FALSE;
    param.type = SCE_IME_TYPE_DEFAULT;
    param.option = 0;
    param.متن_Box_منوال = SCE_IME_DIALOG_TEXTBOX_منوال_WITH_CLEAR;
    param.max_متن_لمائی = SCE_IME_DIALOG_MAX_متن_لمائی;

    param.title = title;
    param.initial_متن = متن;
    param.داخلہ_متن_بفر = videodata->ime_بفر;

    res = sceImeDialogInit(&param);
    إذا (res < 0) {
        SDL_سیٹ_Error("Failed to init IME dialog");
        أرجع;
    }

#جے_انت

    videodata->ime_سرگرم = true;

    SDL_SendScreenKeyboardShown();
}

فراغ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
#جے_بنا_تعریف SDL_VIDEO_VITA_PVR
    SDL_Video_انکڑے *videodata = _this->اندرونی;

    Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();

    بدل (dialog_حالت) {
    افتراضي:
    حالة SCE_COMMON_DIALOG_حالت_NONE:
    حالة SCE_COMMON_DIALOG_حالت_RUNNING:
        اكسر;
    حالة SCE_COMMON_DIALOG_حالت_مکمل:
        sce_Ime_Dialog_رکن();
        اكسر;
    }

    videodata->ime_سرگرم = false;

    SDL_SendScreenKeyboardHidden();
#جے_انت
}

فراغ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#جے_بنا_تعریف SDL_VIDEO_VITA_PVR
    SDL_Video_انکڑے *videodata = _this->اندرونی;
#جے_انت

    إذا (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#جے_بنا_تعریف SDL_VIDEO_VITA_PVR
    إذا (videodata->ime_سرگرم == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();
        إذا (dialog_حالت == SCE_COMMON_DIALOG_حالت_مکمل) {
            uint8_t utf8_بفر[SCE_IME_DIALOG_MAX_متن_لمائی];

            Sce_Ime_Dialog_نتیجہ نتیجہ;
            SDL_zero(نتیجہ);
            sce_Ime_Dialog_Get_نتیجہ(&نتیجہ);

            // Convert UTF16 to UTF8
            utf16_منزل_utf8(videodata->ime_بفر, utf8_بفر);

            // Send SDL event
            SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);

            // Send enter key only on enter
            إذا (نتیجہ.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_رکن();

            videodata->ime_سرگرم = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#جے_انت
}

#جے_انت // SDL_VIDEO_DRIVER_VITA

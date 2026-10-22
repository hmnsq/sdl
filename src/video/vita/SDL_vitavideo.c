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

#که_تعریف_شوی SDL_VIDEO_DRIVER_VITA

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
#تعریف_کړه VITA_GLES_Get_Proc_پته  SDL_EGL_Get_Proc_پته_دننی
#تعریف_کړه VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کړه VITA_GLES_سېټ_بدلون_Interval SDL_EGL_سېټ_بدلون_Interval
#تعریف_کړه VITA_GLES_Get_بدلون_Interval SDL_EGL_Get_بدلون_Interval
#تعریف_کړه VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#د_که_پای

SDL_کړکۍ *Vita_کړکۍ;

ساكن فراغ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->دننی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *VITA_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *phdata;
#که_تعریف_شوی SDL_VIDEO_VITA_PIB
    SDL_GLDriver_معلومات *gldata;
#د_که_پای
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_معلومات *)SDL_calloc(1, حجم(SDL_Video_معلومات));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }
#که_تعریف_شوی SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_معلومات *)SDL_calloc(1, حجم(SDL_GLDriver_معلومات));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_معلومات = gldata;
    phdata->egl_initialized = true;
#د_که_پای
    phdata->ime_فعال = false;

    device->دننی = phdata;

    // Setup amount of available displays and current display
    device->عدد_displays = 0;

    // Set device free function
    device->حرر = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_کړکۍ;
    device->سېټ_کړکۍ_Title = VITA_سېټ_کړکۍ_Title;
    device->سېټ_کړکۍ_Position = VITA_سېټ_کړکۍ_Position;
    device->سېټ_کړکۍ_اندازه = VITA_سېټ_کړکۍ_اندازه;
    device->Show_کړکۍ = VITA_Show_کړکۍ;
    device->Hide_کړکۍ = VITA_Hide_کړکۍ;
    device->Raise_کړکۍ = VITA_Raise_کړکۍ;
    device->Maximize_کړکۍ = VITA_Maximize_کړکۍ;
    device->Minimize_کړکۍ = VITA_Minimize_کړکۍ;
    device->Restore_کړکۍ = VITA_Restore_کړکۍ;
    device->سېټ_کړکۍ_Mouse_Grab = VITA_سېټ_کړکۍ_Grab;
    device->سېټ_کړکۍ_Keyboard_Grab = VITA_سېټ_کړکۍ_Grab;
    device->Destroy_کړکۍ = VITA_Destroy_کړکۍ;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#إذا defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#که_تعریف_شوی SDL_VIDEO_VITA_PVR_OGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_بارول_Library = VITA_GL_بارول_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_پته = VITA_GL_Get_Proc_پته;
    } وإلا {
#د_که_پای
        device->GL_بارول_Library = VITA_GLES_بارول_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_پته = VITA_GLES_Get_Proc_پته;
#که_تعریف_شوی SDL_VIDEO_VITA_PVR_OGL
    }
#د_که_پای

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_سېټ_بدلون_Interval = VITA_GLES_سېټ_بدلون_Interval;
    device->GL_Get_بدلون_Interval = VITA_GLES_Get_بدلون_Interval;
    device->GL_بدلون_کړکۍ = VITA_GLES_بدلون_کړکۍ;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#د_که_پای

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
    VITA_Show_پیغام_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ډېرپېښ ډېرپېښ;
#که_تعریف_شوی SDL_VIDEO_VITA_PVR
    ثابت حرف *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#د_که_پای
    SDL_zero(ډېرپېښ);

#که_تعریف_شوی SDL_VIDEO_VITA_PVR
    إذا (res) {
        // 1088i for PSTV (Or Sharpscale)
        إذا (SDL_strncmp(res, "1080", 4) == 0) {
            ډېرپېښ.w = 1920;
            ډېرپېښ.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        وإلا إذا (SDL_strncmp(res, "720", 3) == 0) {
            ډېرپېښ.w = 1280;
            ډېرپېښ.h = 725;
        }
    }
    // 544p
    وإلا {
#د_که_پای
        ډېرپېښ.w = 960;
        ډېرپېښ.h = 544;
#که_تعریف_شوی SDL_VIDEO_VITA_PVR
    }
#د_که_پای

    ډېرپېښ.refresh_شرح = 60.0f;

    // 32 bpp for default
    ډېرپېښ.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ) == 0) {
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

bool VITA_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props)
{
    SDL_کړکۍ_معلومات *wdata;
#که_تعریف_شوی SDL_VIDEO_VITA_PVR
    Psp2_Native_کړکۍ win;
    صحيح لنډمهاله_major = 2;
    صحيح لنډمهاله_minor = 1;
    صحيح لنډمهاله_profile = 0;
#د_که_پای

    // Allocate window internal data
    wdata = (SDL_کړکۍ_معلومات *)SDL_calloc(1, حجم(SDL_کړکۍ_معلومات));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    کړکۍ->دننی = wdata;

    // Vita can only have one window
    إذا (Vita_کړکۍ) {
        أرجع SDL_سېټ_Error("Only one window supported");
    }

    Vita_کړکۍ = کړکۍ;

#که_تعریف_شوی SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_کړکۍ;
    win.عدد_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    إذا (کړکۍ->w == 1920) {
        win.کړکۍ_اندازه = PSP2_کړکۍ_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    وإلا إذا (کړکۍ->w == 1280) {
        win.کړکۍ_اندازه = PSP2_کړکۍ_1280_X725;
    }
    // 544p
    وإلا {
        win.کړکۍ_اندازه = PSP2_کړکۍ_960_X544;
    }
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        إذا (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            لنډمهاله_major = _this->gl_config.major_نسخه;
            لنډمهاله_minor = _this->gl_config.minor_نسخه;
            لنډمهاله_profile = _this->gl_config.profile_ماسک;

            _this->gl_config.major_نسخه = 2;
            _this->gl_config.minor_نسخه = 1;
            _this->gl_config.profile_ماسک = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, کړکۍ, &win);
        إذا (wdata->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سېټ_Error("Could not create GLES window surface");
        }
        إذا (use_opengl) {
            // Revert
            _this->gl_config.major_نسخه = لنډمهاله_major;
            _this->gl_config.minor_نسخه = لنډمهاله_minor;
            _this->gl_config.profile_ماسک = لنډمهاله_profile;
        }
    }
#د_که_پای

    // fix input, we need to find a better way
    SDL_سېټ_Keyboard_Focus(کړکۍ);

    // Window has been successfully created
    أرجع true;
}

فراغ VITA_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
bool VITA_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    أرجع SDL_Unsupported();
}
فراغ VITA_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ VITA_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ VITA_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ VITA_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ VITA_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ VITA_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
فراغ VITA_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
}
bool VITA_سېټ_کړکۍ_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed)
{
    أرجع true;
}

فراغ VITA_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات;

    معلومات = کړکۍ->دننی;
    SDL_free(معلومات);

    کړکۍ->دننی = عدم;
    Vita_کړکۍ = عدم;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

#که_نه_تعریف_شوی SCE_IME_LANGUAGE_ENGLISH_US
#تعریف_کړه SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#د_که_پای

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

#که_تعریف_شوی SDL_VIDEO_VITA_PVR
SceWChar16 libime_بهر[SCE_IME_MAX_PREEDIT_اوږدتیا + SCE_IME_MAX_متن_اوږدتیا + 1];
حرف libime_initval[8] = { 1 };
SceImeCaret caret_rev;

فراغ VITA_ImeEventHandler(فراغ *arg, ثابت Sce_Ime_Event_معلومات *e)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)arg;
    uint8_t utf8_بفر[SCE_IME_MAX_متن_اوږدتیا];
    بدل (e->id) {
    حالة SCE_IME_EVENT_UPDATE_متن:
        إذا (e->param.متن.caret_شاخص == 0) {
            SDL_Send_Keyboard_کلی_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_سېټ_متن((SceWChar16 *)libime_initval, 4);
        } وإلا {
            utf16_منزل_utf8((SceWChar16 *)&libime_بهر[1], utf8_بفر);
            إذا (utf8_بفر[0] == ' ') {
                SDL_Send_Keyboard_کلی_Auto_Release(0, SDL_SCANCODE_SPACE);
            } وإلا {
                SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_بهر, 0, ((SCE_IME_MAX_PREEDIT_اوږدتیا + SCE_IME_MAX_متن_اوږدتیا + 1) * حجم(SceWChar16)));
            caret_rev.شاخص = 1;
            sce_Ime_سېټ_Caret(&caret_rev);
            sce_Ime_سېټ_متن((SceWChar16 *)libime_initval, 4);
        }
        اكسر;
    حالة SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_کلی_Auto_Release(0, SDL_SCANCODE_RETURN);
        اكسر;
    حالة SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_فعال = false;
        SDL_SendScreenKeyboardHidden();
        اكسر;
    }
}
#د_که_پای // SDL_VIDEO_VITA_PVR

فراغ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    SDL_Video_معلومات *videodata = _this->دننی;
    SceInt32 res;

#که_تعریف_شوی SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_بفر_اندازه / حجم(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_بهر, 0, ((SCE_IME_MAX_PREEDIT_اوږدتیا + SCE_IME_MAX_متن_اوږدتیا + 1) * حجم(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    بدل (SDL_Get_متن_ننوت_Type(props)) {
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
    حالة SDL_TEXTINPUT_TYPE_شمېره:
        param.type = SCE_IME_TYPE_شمېره;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_شمېره_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_شمېره;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_شمېره_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_شمېره;
        اكسر;
    }
    param.option = 0;
    إذا (SDL_Get_متن_ننوت_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    إذا (!SDL_Get_متن_ننوت_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    إذا (SDL_Get_متن_ننوت_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.ننوت_متن_بفر = libime_بهر;
    param.max_متن_اوږدتیا = SCE_IME_MAX_متن_اوږدتیا;
    param.handler = VITA_ImeEventHandler;
    param.filter = عدم;
    param.initial_متن = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    إذا (res < 0) {
        SDL_سېټ_Error("Failed to init IME");
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
    param.متن_Box_ډېرپېښ = SCE_IME_DIALOG_TEXTBOX_ډېرپېښ_WITH_CLEAR;
    param.max_متن_اوږدتیا = SCE_IME_DIALOG_MAX_متن_اوږدتیا;

    param.title = title;
    param.initial_متن = متن;
    param.ننوت_متن_بفر = videodata->ime_بفر;

    res = sceImeDialogInit(&param);
    إذا (res < 0) {
        SDL_سېټ_Error("Failed to init IME dialog");
        أرجع;
    }

#د_که_پای

    videodata->ime_فعال = true;

    SDL_SendScreenKeyboardShown();
}

فراغ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
#که_نه_تعریف_شوی SDL_VIDEO_VITA_PVR
    SDL_Video_معلومات *videodata = _this->دننی;

    Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();

    بدل (dialog_حالت) {
    افتراضي:
    حالة SCE_COMMON_DIALOG_حالت_NONE:
    حالة SCE_COMMON_DIALOG_حالت_RUNNING:
        اكسر;
    حالة SCE_COMMON_DIALOG_حالت_پای_ته_رسېدلی:
        sce_Ime_Dialog_غړی();
        اكسر;
    }

    videodata->ime_فعال = false;

    SDL_SendScreenKeyboardHidden();
#د_که_پای
}

فراغ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#که_نه_تعریف_شوی SDL_VIDEO_VITA_PVR
    SDL_Video_معلومات *videodata = _this->دننی;
#د_که_پای

    إذا (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#که_نه_تعریف_شوی SDL_VIDEO_VITA_PVR
    إذا (videodata->ime_فعال == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();
        إذا (dialog_حالت == SCE_COMMON_DIALOG_حالت_پای_ته_رسېدلی) {
            uint8_t utf8_بفر[SCE_IME_DIALOG_MAX_متن_اوږدتیا];

            Sce_Ime_Dialog_پایله پایله;
            SDL_zero(پایله);
            sce_Ime_Dialog_Get_پایله(&پایله);

            // Convert UTF16 to UTF8
            utf16_منزل_utf8(videodata->ime_بفر, utf8_بفر);

            // Send SDL event
            SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);

            // Send enter key only on enter
            إذا (پایله.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_کلی_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_غړی();

            videodata->ime_فعال = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#د_که_پای
}

#د_که_پای // SDL_VIDEO_DRIVER_VITA

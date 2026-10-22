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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VITA

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
#وصف_ڪريو VITA_GLES_Get_Proc_پتو  SDL_EGL_Get_Proc_پتو_اندروني
#وصف_ڪريو VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#وصف_ڪريو VITA_GLES_سيٽ_مٽا_سٽا_Interval SDL_EGL_سيٽ_مٽا_سٽا_Interval
#وصف_ڪريو VITA_GLES_Get_مٽا_سٽا_Interval SDL_EGL_Get_مٽا_سٽا_Interval
#وصف_ڪريو VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#جيڪڏهن_پورو

SDL_دري *Vita_دري;

ساكن فراغ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->اندروني);
    SDL_free(device);
}

ساكن SDL_VideoDevice *VITA_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_معلومات *phdata;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PIB
    SDL_GLDriver_معلومات *gldata;
#جيڪڏهن_پورو
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
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_معلومات *)SDL_calloc(1, حجم(SDL_GLDriver_معلومات));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_معلومات = gldata;
    phdata->egl_initialized = true;
#جيڪڏهن_پورو
    phdata->ime_سرگرم = false;

    device->اندروني = phdata;

    // Setup amount of available displays and current display
    device->انگ_displays = 0;

    // Set device free function
    device->حرر = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_دري;
    device->سيٽ_دري_Title = VITA_سيٽ_دري_Title;
    device->سيٽ_دري_Position = VITA_سيٽ_دري_Position;
    device->سيٽ_دري_سائيز = VITA_سيٽ_دري_سائيز;
    device->Show_دري = VITA_Show_دري;
    device->Hide_دري = VITA_Hide_دري;
    device->Raise_دري = VITA_Raise_دري;
    device->Maximize_دري = VITA_Maximize_دري;
    device->Minimize_دري = VITA_Minimize_دري;
    device->Restore_دري = VITA_Restore_دري;
    device->سيٽ_دري_Mouse_Grab = VITA_سيٽ_دري_Grab;
    device->سيٽ_دري_Keyboard_Grab = VITA_سيٽ_دري_Grab;
    device->Destroy_دري = VITA_Destroy_دري;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#إذا defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR_OGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_ڀريو_Library = VITA_GL_ڀريو_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_پتو = VITA_GL_Get_Proc_پتو;
    } وإلا {
#جيڪڏهن_پورو
        device->GL_ڀريو_Library = VITA_GLES_ڀريو_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_پتو = VITA_GLES_Get_Proc_پتو;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR_OGL
    }
#جيڪڏهن_پورو

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_سيٽ_مٽا_سٽا_Interval = VITA_GLES_سيٽ_مٽا_سٽا_Interval;
    device->GL_Get_مٽا_سٽا_Interval = VITA_GLES_Get_مٽا_سٽا_Interval;
    device->GL_مٽا_سٽا_دري = VITA_GLES_مٽا_سٽا_دري;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#جيڪڏهن_پورو

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
    VITA_Show_پيغام_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_گهڻائي گهڻائي;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR
    ثابت حرف *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#جيڪڏهن_پورو
    SDL_zero(گهڻائي);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR
    إذا (res) {
        // 1088i for PSTV (Or Sharpscale)
        إذا (SDL_strncmp(res, "1080", 4) == 0) {
            گهڻائي.w = 1920;
            گهڻائي.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        وإلا إذا (SDL_strncmp(res, "720", 3) == 0) {
            گهڻائي.w = 1280;
            گهڻائي.h = 725;
        }
    }
    // 544p
    وإلا {
#جيڪڏهن_پورو
        گهڻائي.w = 960;
        گهڻائي.h = 544;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR
    }
#جيڪڏهن_پورو

    گهڻائي.refresh_شرح = 60.0f;

    // 32 bpp for default
    گهڻائي.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_جوڙيو_Basic_Video_Display(&گهڻائي) == 0) {
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

bool VITA_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *wdata;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR
    Psp2_Native_دري win;
    صحيح عارضي_major = 2;
    صحيح عارضي_minor = 1;
    صحيح عارضي_profile = 0;
#جيڪڏهن_پورو

    // Allocate window internal data
    wdata = (SDL_دري_معلومات *)SDL_calloc(1, حجم(SDL_دري_معلومات));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    دري->اندروني = wdata;

    // Vita can only have one window
    إذا (Vita_دري) {
        أرجع SDL_سيٽ_Error("Only one window supported");
    }

    Vita_دري = دري;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_دري;
    win.انگ_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    إذا (دري->w == 1920) {
        win.دري_سائيز = PSP2_دري_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    وإلا إذا (دري->w == 1280) {
        win.دري_سائيز = PSP2_دري_1280_X725;
    }
    // 544p
    وإلا {
        win.دري_سائيز = PSP2_دري_960_X544;
    }
    إذا (دري->flags & SDL_دري_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        إذا (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            عارضي_major = _this->gl_config.major_نسخو;
            عارضي_minor = _this->gl_config.minor_نسخو;
            عارضي_profile = _this->gl_config.profile_نقاب;

            _this->gl_config.major_نسخو = 2;
            _this->gl_config.minor_نسخو = 1;
            _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, دري, &win);
        إذا (wdata->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_سيٽ_Error("Could not create GLES window surface");
        }
        إذا (use_opengl) {
            // Revert
            _this->gl_config.major_نسخو = عارضي_major;
            _this->gl_config.minor_نسخو = عارضي_minor;
            _this->gl_config.profile_نقاب = عارضي_profile;
        }
    }
#جيڪڏهن_پورو

    // fix input, we need to find a better way
    SDL_سيٽ_Keyboard_Focus(دري);

    // Window has been successfully created
    أرجع true;
}

فراغ VITA_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
bool VITA_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري)
{
    أرجع SDL_Unsupported();
}
فراغ VITA_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ VITA_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ VITA_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ VITA_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ VITA_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ VITA_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
فراغ VITA_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
}
bool VITA_سيٽ_دري_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed)
{
    أرجع true;
}

فراغ VITA_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات;

    معلومات = دري->اندروني;
    SDL_free(معلومات);

    دري->اندروني = عدم;
    Vita_دري = عدم;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

#جيڪڏهن_وصف_نه_ٿيل SCE_IME_LANGUAGE_ENGLISH_US
#وصف_ڪريو SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#جيڪڏهن_پورو

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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR
SceWChar16 libime_ٻاهريون[SCE_IME_MAX_PREEDIT_ڊيگهائي + SCE_IME_MAX_متن_ڊيگهائي + 1];
حرف libime_initval[8] = { 1 };
SceImeCaret caret_rev;

فراغ VITA_ImeEventHandler(فراغ *arg, ثابت Sce_Ime_Event_معلومات *e)
{
    SDL_Video_معلومات *videodata = (SDL_Video_معلومات *)arg;
    uint8_t utf8_بفر[SCE_IME_MAX_متن_ڊيگهائي];
    بدل (e->id) {
    حالة SCE_IME_EVENT_UPDATE_متن:
        إذا (e->param.متن.caret_اشاريو == 0) {
            SDL_Send_Keyboard_ڪنجي_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_سيٽ_متن((SceWChar16 *)libime_initval, 4);
        } وإلا {
            utf16_منزل_utf8((SceWChar16 *)&libime_ٻاهريون[1], utf8_بفر);
            إذا (utf8_بفر[0] == ' ') {
                SDL_Send_Keyboard_ڪنجي_Auto_Release(0, SDL_SCANCODE_SPACE);
            } وإلا {
                SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_ٻاهريون, 0, ((SCE_IME_MAX_PREEDIT_ڊيگهائي + SCE_IME_MAX_متن_ڊيگهائي + 1) * حجم(SceWChar16)));
            caret_rev.اشاريو = 1;
            sce_Ime_سيٽ_Caret(&caret_rev);
            sce_Ime_سيٽ_متن((SceWChar16 *)libime_initval, 4);
        }
        اكسر;
    حالة SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_ڪنجي_Auto_Release(0, SDL_SCANCODE_RETURN);
        اكسر;
    حالة SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_سرگرم = false;
        SDL_SendScreenKeyboardHidden();
        اكسر;
    }
}
#جيڪڏهن_پورو // SDL_VIDEO_VITA_PVR

فراغ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID props)
{
    SDL_Video_معلومات *videodata = _this->اندروني;
    SceInt32 res;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_بفر_سائيز / حجم(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_ٻاهريون, 0, ((SCE_IME_MAX_PREEDIT_ڊيگهائي + SCE_IME_MAX_متن_ڊيگهائي + 1) * حجم(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    بدل (SDL_Get_متن_داخلا_Type(props)) {
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
    حالة SDL_TEXTINPUT_TYPE_عدد:
        param.type = SCE_IME_TYPE_عدد;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_عدد;
        اكسر;
    حالة SDL_TEXTINPUT_TYPE_عدد_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_عدد;
        اكسر;
    }
    param.option = 0;
    إذا (SDL_Get_متن_داخلا_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    إذا (!SDL_Get_متن_داخلا_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    إذا (SDL_Get_متن_داخلا_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.داخلا_متن_بفر = libime_ٻاهريون;
    param.max_متن_ڊيگهائي = SCE_IME_MAX_متن_ڊيگهائي;
    param.handler = VITA_ImeEventHandler;
    param.filter = عدم;
    param.initial_متن = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    إذا (res < 0) {
        SDL_سيٽ_Error("Failed to init IME");
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
    param.متن_Box_گهڻائي = SCE_IME_DIALOG_TEXTBOX_گهڻائي_WITH_CLEAR;
    param.max_متن_ڊيگهائي = SCE_IME_DIALOG_MAX_متن_ڊيگهائي;

    param.title = title;
    param.initial_متن = متن;
    param.داخلا_متن_بفر = videodata->ime_بفر;

    res = sceImeDialogInit(&param);
    إذا (res < 0) {
        SDL_سيٽ_Error("Failed to init IME dialog");
        أرجع;
    }

#جيڪڏهن_پورو

    videodata->ime_سرگرم = true;

    SDL_SendScreenKeyboardShown();
}

فراغ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_دري *دري)
{
#جيڪڏهن_وصف_نه_ٿيل SDL_VIDEO_VITA_PVR
    SDL_Video_معلومات *videodata = _this->اندروني;

    Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();

    بدل (dialog_حالت) {
    افتراضي:
    حالة SCE_COMMON_DIALOG_حالت_NONE:
    حالة SCE_COMMON_DIALOG_حالت_RUNNING:
        اكسر;
    حالة SCE_COMMON_DIALOG_حالت_ختم:
        sce_Ime_Dialog_رڪن();
        اكسر;
    }

    videodata->ime_سرگرم = false;

    SDL_SendScreenKeyboardHidden();
#جيڪڏهن_پورو
}

فراغ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_نه_ٿيل SDL_VIDEO_VITA_PVR
    SDL_Video_معلومات *videodata = _this->اندروني;
#جيڪڏهن_پورو

    إذا (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#جيڪڏهن_وصف_نه_ٿيل SDL_VIDEO_VITA_PVR
    إذا (videodata->ime_سرگرم == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_حالت dialog_حالت = sce_Ime_Dialog_Get_حالت();
        إذا (dialog_حالت == SCE_COMMON_DIALOG_حالت_ختم) {
            uint8_t utf8_بفر[SCE_IME_DIALOG_MAX_متن_ڊيگهائي];

            Sce_Ime_Dialog_نتيجو نتيجو;
            SDL_zero(نتيجو);
            sce_Ime_Dialog_Get_نتيجو(&نتيجو);

            // Convert UTF16 to UTF8
            utf16_منزل_utf8(videodata->ime_بفر, utf8_بفر);

            // Send SDL event
            SDL_Send_Keyboard_متن((ثابت حرف *)utf8_بفر);

            // Send enter key only on enter
            إذا (نتيجو.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_ڪنجي_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_رڪن();

            videodata->ime_سرگرم = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#جيڪڏهن_پورو
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_VITA

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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_VITA

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
#تعریف_کن VITA_GLES_Get_Proc_آدرس  SDL_EGL_Get_Proc_آدرس_داخلی
#تعریف_کن VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#تعریف_کن VITA_GLES_مجموعه_جابجا_Interval SDL_EGL_مجموعه_جابجا_Interval
#تعریف_کن VITA_GLES_Get_جابجا_Interval SDL_EGL_Get_جابجا_Interval
#تعریف_کن VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#پایان_اگر

SDL_پنجره *Vita_پنجره;

ساكن فراغ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->داخلی);
    SDL_free(device);
}

ساكن SDL_VideoDevice *VITA_Create(فراغ)
{
    SDL_VideoDevice *device;
    SDL_Video_داده *phdata;
#اگر_تعریف_شده SDL_VIDEO_VITA_PIB
    SDL_GLDriver_داده *gldata;
#پایان_اگر
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, حجم(SDL_VideoDevice));
    إذا (!device) {
        أرجع عدم;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_داده *)SDL_calloc(1, حجم(SDL_Video_داده));
    إذا (!phdata) {
        SDL_free(device);
        أرجع عدم;
    }
#اگر_تعریف_شده SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_داده *)SDL_calloc(1, حجم(SDL_GLDriver_داده));
    إذا (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        أرجع عدم;
    }
    device->gl_داده = gldata;
    phdata->egl_initialized = true;
#پایان_اگر
    phdata->ime_فعال = false;

    device->داخلی = phdata;

    // Setup amount of available displays and current display
    device->رقم_displays = 0;

    // Set device free function
    device->حرر = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_پنجره;
    device->مجموعه_پنجره_Title = VITA_مجموعه_پنجره_Title;
    device->مجموعه_پنجره_Position = VITA_مجموعه_پنجره_Position;
    device->مجموعه_پنجره_اندازه = VITA_مجموعه_پنجره_اندازه;
    device->Show_پنجره = VITA_Show_پنجره;
    device->Hide_پنجره = VITA_Hide_پنجره;
    device->Raise_پنجره = VITA_Raise_پنجره;
    device->Maximize_پنجره = VITA_Maximize_پنجره;
    device->Minimize_پنجره = VITA_Minimize_پنجره;
    device->Restore_پنجره = VITA_Restore_پنجره;
    device->مجموعه_پنجره_Mouse_Grab = VITA_مجموعه_پنجره_Grab;
    device->مجموعه_پنجره_Keyboard_Grab = VITA_مجموعه_پنجره_Grab;
    device->Destroy_پنجره = VITA_Destroy_پنجره;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#إذا defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#اگر_تعریف_شده SDL_VIDEO_VITA_PVR_OGL
    إذا (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_بارگیری_Library = VITA_GL_بارگیری_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_آدرس = VITA_GL_Get_Proc_آدرس;
    } وإلا {
#پایان_اگر
        device->GL_بارگیری_Library = VITA_GLES_بارگیری_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_آدرس = VITA_GLES_Get_Proc_آدرس;
#اگر_تعریف_شده SDL_VIDEO_VITA_PVR_OGL
    }
#پایان_اگر

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_مجموعه_جابجا_Interval = VITA_GLES_مجموعه_جابجا_Interval;
    device->GL_Get_جابجا_Interval = VITA_GLES_Get_جابجا_Interval;
    device->GL_جابجا_پنجره = VITA_GLES_جابجا_پنجره;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#پایان_اگر

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
    VITA_Show_پیام_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_نما نما;
#اگر_تعریف_شده SDL_VIDEO_VITA_PVR
    ثابت حرف *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#پایان_اگر
    SDL_zero(نما);

#اگر_تعریف_شده SDL_VIDEO_VITA_PVR
    إذا (res) {
        // 1088i for PSTV (Or Sharpscale)
        إذا (SDL_strncmp(res, "1080", 4) == 0) {
            نما.w = 1920;
            نما.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        وإلا إذا (SDL_strncmp(res, "720", 3) == 0) {
            نما.w = 1280;
            نما.h = 725;
        }
    }
    // 544p
    وإلا {
#پایان_اگر
        نما.w = 960;
        نما.h = 544;
#اگر_تعریف_شده SDL_VIDEO_VITA_PVR
    }
#پایان_اگر

    نما.refresh_نرخ = 60.0f;

    // 32 bpp for default
    نما.format = SDL_PIXELFORMAT_ABGR8888;

    إذا (SDL_جمع_کن_Basic_Video_Display(&نما) == 0) {
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

bool VITA_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props)
{
    SDL_پنجره_داده *wdata;
#اگر_تعریف_شده SDL_VIDEO_VITA_PVR
    Psp2_Native_پنجره win;
    صحيح موقت_major = 2;
    صحيح موقت_minor = 1;
    صحيح موقت_profile = 0;
#پایان_اگر

    // Allocate window internal data
    wdata = (SDL_پنجره_داده *)SDL_calloc(1, حجم(SDL_پنجره_داده));
    إذا (!wdata) {
        أرجع false;
    }

    // Setup driver data for this window
    پنجره->داخلی = wdata;

    // Vita can only have one window
    إذا (Vita_پنجره) {
        أرجع SDL_مجموعه_Error("Only one window supported");
    }

    Vita_پنجره = پنجره;

#اگر_تعریف_شده SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_پنجره;
    win.رقم_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    إذا (پنجره->w == 1920) {
        win.پنجره_اندازه = PSP2_پنجره_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    وإلا إذا (پنجره->w == 1280) {
        win.پنجره_اندازه = PSP2_پنجره_1280_X725;
    }
    // 544p
    وإلا {
        win.پنجره_اندازه = PSP2_پنجره_960_X544;
    }
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        إذا (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            موقت_major = _this->gl_config.major_نسخه;
            موقت_minor = _this->gl_config.minor_نسخه;
            موقت_profile = _this->gl_config.profile_ماسک;

            _this->gl_config.major_نسخه = 2;
            _this->gl_config.minor_نسخه = 1;
            _this->gl_config.profile_ماسک = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, پنجره, &win);
        إذا (wdata->egl_surface == EGL_NO_SURFACE) {
            أرجع SDL_مجموعه_Error("Could not create GLES window surface");
        }
        إذا (use_opengl) {
            // Revert
            _this->gl_config.major_نسخه = موقت_major;
            _this->gl_config.minor_نسخه = موقت_minor;
            _this->gl_config.profile_ماسک = موقت_profile;
        }
    }
#پایان_اگر

    // fix input, we need to find a better way
    SDL_مجموعه_Keyboard_Focus(پنجره);

    // Window has been successfully created
    أرجع true;
}

فراغ VITA_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
bool VITA_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    أرجع SDL_Unsupported();
}
فراغ VITA_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ VITA_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ VITA_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ VITA_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ VITA_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ VITA_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
فراغ VITA_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
}
bool VITA_مجموعه_پنجره_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed)
{
    أرجع true;
}

فراغ VITA_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده;

    داده = پنجره->داخلی;
    SDL_free(داده);

    پنجره->داخلی = عدم;
    Vita_پنجره = عدم;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    أرجع true;
}

#اگر_تعریف_نشده SCE_IME_LANGUAGE_ENGLISH_US
#تعریف_کن SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#پایان_اگر

ساكن فراغ utf16_مقصد_utf8(ثابت uint16_t *src, uint8_t *dst)
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

#اگر_تعریف_شده SDL_VIDEO_VITA_PVR
SceWChar16 libime_بیرون[SCE_IME_MAX_PREEDIT_درازی + SCE_IME_MAX_متن_درازی + 1];
حرف libime_initval[8] = { 1 };
SceImeCaret caret_rev;

فراغ VITA_ImeEventHandler(فراغ *arg, ثابت Sce_Ime_Event_داده *e)
{
    SDL_Video_داده *videodata = (SDL_Video_داده *)arg;
    uint8_t utf8_میانگیر[SCE_IME_MAX_متن_درازی];
    بدل (e->id) {
    حالة SCE_IME_EVENT_UPDATE_متن:
        إذا (e->param.متن.caret_شاخص == 0) {
            SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_مجموعه_متن((SceWChar16 *)libime_initval, 4);
        } وإلا {
            utf16_مقصد_utf8((SceWChar16 *)&libime_بیرون[1], utf8_میانگیر);
            إذا (utf8_میانگیر[0] == ' ') {
                SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_SPACE);
            } وإلا {
                SDL_Send_Keyboard_متن((ثابت حرف *)utf8_میانگیر);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_بیرون, 0, ((SCE_IME_MAX_PREEDIT_درازی + SCE_IME_MAX_متن_درازی + 1) * حجم(SceWChar16)));
            caret_rev.شاخص = 1;
            sce_Ime_مجموعه_Caret(&caret_rev);
            sce_Ime_مجموعه_متن((SceWChar16 *)libime_initval, 4);
        }
        اكسر;
    حالة SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_RETURN);
        اكسر;
    حالة SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_فعال = false;
        SDL_SendScreenKeyboardHidden();
        اكسر;
    }
}
#پایان_اگر // SDL_VIDEO_VITA_PVR

فراغ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SceInt32 res;

#اگر_تعریف_شده SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_میانگیر_اندازه / حجم(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_بیرون, 0, ((SCE_IME_MAX_PREEDIT_درازی + SCE_IME_MAX_متن_درازی + 1) * حجم(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    بدل (SDL_Get_متن_درون_داد_Type(props)) {
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
    إذا (SDL_Get_متن_درون_داد_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    إذا (!SDL_Get_متن_درون_داد_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    إذا (SDL_Get_متن_درون_داد_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.درون_داد_متن_میانگیر = libime_بیرون;
    param.max_متن_درازی = SCE_IME_MAX_متن_درازی;
    param.handler = VITA_ImeEventHandler;
    param.filter = عدم;
    param.initial_متن = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    إذا (res < 0) {
        SDL_مجموعه_Error("Failed to init IME");
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
    param.متن_Box_نما = SCE_IME_DIALOG_TEXTBOX_نما_WITH_CLEAR;
    param.max_متن_درازی = SCE_IME_DIALOG_MAX_متن_درازی;

    param.title = title;
    param.initial_متن = متن;
    param.درون_داد_متن_میانگیر = videodata->ime_میانگیر;

    res = sceImeDialogInit(&param);
    إذا (res < 0) {
        SDL_مجموعه_Error("Failed to init IME dialog");
        أرجع;
    }

#پایان_اگر

    videodata->ime_فعال = true;

    SDL_SendScreenKeyboardShown();
}

فراغ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
#اگر_تعریف_نشده SDL_VIDEO_VITA_PVR
    SDL_Video_داده *videodata = _this->داخلی;

    Sce_Common_Dialog_وضعیت dialog_وضعیت = sce_Ime_Dialog_Get_وضعیت();

    بدل (dialog_وضعیت) {
    افتراضي:
    حالة SCE_COMMON_DIALOG_وضعیت_NONE:
    حالة SCE_COMMON_DIALOG_وضعیت_RUNNING:
        اكسر;
    حالة SCE_COMMON_DIALOG_وضعیت_پایانیافته:
        sce_Ime_Dialog_جمله();
        اكسر;
    }

    videodata->ime_فعال = false;

    SDL_SendScreenKeyboardHidden();
#پایان_اگر
}

فراغ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#اگر_تعریف_نشده SDL_VIDEO_VITA_PVR
    SDL_Video_داده *videodata = _this->داخلی;
#پایان_اگر

    إذا (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#اگر_تعریف_نشده SDL_VIDEO_VITA_PVR
    إذا (videodata->ime_فعال == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_وضعیت dialog_وضعیت = sce_Ime_Dialog_Get_وضعیت();
        إذا (dialog_وضعیت == SCE_COMMON_DIALOG_وضعیت_پایانیافته) {
            uint8_t utf8_میانگیر[SCE_IME_DIALOG_MAX_متن_درازی];

            Sce_Ime_Dialog_نتیجه نتیجه;
            SDL_zero(نتیجه);
            sce_Ime_Dialog_Get_نتیجه(&نتیجه);

            // Convert UTF16 to UTF8
            utf16_مقصد_utf8(videodata->ime_میانگیر, utf8_میانگیر);

            // Send SDL event
            SDL_Send_Keyboard_متن((ثابت حرف *)utf8_میانگیر);

            // Send enter key only on enter
            إذا (نتیجه.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_کلید_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_جمله();

            videodata->ime_فعال = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#پایان_اگر
}

#پایان_اگر // SDL_VIDEO_DRIVER_VITA

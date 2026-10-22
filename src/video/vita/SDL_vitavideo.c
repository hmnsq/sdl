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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA

// SDL internals
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"

// VITA declarations
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/kernel/processmgr.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitatouch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitakeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitamouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitaframebuffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitamessagebox.h"

#ਜੇ defined(SDL_VIDEO_VITA_PVR)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VITA_GLES_Get_Proc_ਪਤਾ  SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VITA_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VITA_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval SDL_EGL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#ਜੇ_ਅੰਤ

SDL_ਖਿੜਕੀ *Vita_ਖਿੜਕੀ;

ਸਥਿਰ ਖਾਲੀ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->ਅੰਦਰੂਨੀ);
    SDL_free(device);
}

ਸਥਿਰ SDL_VideoDevice *VITA_Create(ਖਾਲੀ)
{
    SDL_VideoDevice *device;
    SDL_Video_ਅੰਕੜੇ *phdata;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PIB
    SDL_GLDriver_ਅੰਕੜੇ *gldata;
#ਜੇ_ਅੰਤ
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ਆਕਾਰ(SDL_VideoDevice));
    ਜੇ (!device) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Video_ਅੰਕੜੇ));
    ਜੇ (!phdata) {
        SDL_free(device);
        ਵਾਪਸ ਨਿਰਾ;
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_GLDriver_ਅੰਕੜੇ));
    ਜੇ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ਵਾਪਸ ਨਿਰਾ;
    }
    device->gl_ਅੰਕੜੇ = gldata;
    phdata->egl_initialized = true;
#ਜੇ_ਅੰਤ
    phdata->ime_ਸਰਗਰਮ = false;

    device->ਅੰਦਰੂਨੀ = phdata;

    // Setup amount of available displays and current display
    device->ਅੰਕ_displays = 0;

    // Set device free function
    device->ਮੁਕਤ = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Title = VITA_ਸੈੱਟ_ਖਿੜਕੀ_Title;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Position = VITA_ਸੈੱਟ_ਖਿੜਕੀ_Position;
    device->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ = VITA_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ;
    device->Show_ਖਿੜਕੀ = VITA_Show_ਖਿੜਕੀ;
    device->Hide_ਖਿੜਕੀ = VITA_Hide_ਖਿੜਕੀ;
    device->Raise_ਖਿੜਕੀ = VITA_Raise_ਖਿੜਕੀ;
    device->Maximize_ਖਿੜਕੀ = VITA_Maximize_ਖਿੜਕੀ;
    device->Minimize_ਖਿੜਕੀ = VITA_Minimize_ਖਿੜਕੀ;
    device->Restore_ਖਿੜਕੀ = VITA_Restore_ਖਿੜਕੀ;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab = VITA_ਸੈੱਟ_ਖਿੜਕੀ_Grab;
    device->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab = VITA_ਸੈੱਟ_ਖਿੜਕੀ_Grab;
    device->Destroy_ਖਿੜਕੀ = VITA_Destroy_ਖਿੜਕੀ;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#ਜੇ defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR_OGL
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_ਲੱਦੋ_Library = VITA_GL_ਲੱਦੋ_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_ਪਤਾ = VITA_GL_Get_Proc_ਪਤਾ;
    } ਨਹੀਂਤਾਂ {
#ਜੇ_ਅੰਤ
        device->GL_ਲੱਦੋ_Library = VITA_GLES_ਲੱਦੋ_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_ਪਤਾ = VITA_GLES_Get_Proc_ਪਤਾ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR_OGL
    }
#ਜੇ_ਅੰਤ

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval = VITA_GLES_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval = VITA_GLES_Get_ਅਦਲਾ_ਬਦਲੀ_Interval;
    device->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = VITA_GLES_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#ਜੇ_ਅੰਤ

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ਵਾਪਸ device;
}

VideoBootStrap VITA_bootstrap = {
    "vita",
    "VITA Video Driver",
    VITA_Create,
    VITA_Show_ਸੁਨੇਹਾ_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    ਅਚਲ ਅੱਖਰ *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#ਜੇ_ਅੰਤ
    SDL_zero(ਬਹੁਲਕ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    ਜੇ (res) {
        // 1088i for PSTV (Or Sharpscale)
        ਜੇ (SDL_strncmp(res, "1080", 4) == 0) {
            ਬਹੁਲਕ.w = 1920;
            ਬਹੁਲਕ.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        ਨਹੀਂਤਾਂ ਜੇ (SDL_strncmp(res, "720", 3) == 0) {
            ਬਹੁਲਕ.w = 1280;
            ਬਹੁਲਕ.h = 725;
        }
    }
    // 544p
    ਨਹੀਂਤਾਂ {
#ਜੇ_ਅੰਤ
        ਬਹੁਲਕ.w = 960;
        ਬਹੁਲਕ.h = 544;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    }
#ਜੇ_ਅੰਤ

    ਬਹੁਲਕ.refresh_ਦਰ = 60.0f;

    // 32 bpp for default
    ਬਹੁਲਕ.format = SDL_PIXELFORMAT_ABGR8888;

    ਜੇ (SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ) == 0) {
        ਵਾਪਸ false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    ਵਾਪਸ true;
}

ਖਾਲੀ VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    Psp2_Native_ਖਿੜਕੀ win;
    ਪੂਰਨ ਆਰਜ਼ੀ_major = 2;
    ਪੂਰਨ ਆਰਜ਼ੀ_minor = 1;
    ਪੂਰਨ ਆਰਜ਼ੀ_profile = 0;
#ਜੇ_ਅੰਤ

    // Allocate window internal data
    wdata = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ));
    ਜੇ (!wdata) {
        ਵਾਪਸ false;
    }

    // Setup driver data for this window
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = wdata;

    // Vita can only have one window
    ਜੇ (Vita_ਖਿੜਕੀ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Only one window supported");
    }

    Vita_ਖਿੜਕੀ = ਖਿੜਕੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_ਖਿੜਕੀ;
    win.ਅੰਕ_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    ਜੇ (ਖਿੜਕੀ->w == 1920) {
        win.ਖਿੜਕੀ_ਮਾਪ = PSP2_ਖਿੜਕੀ_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->w == 1280) {
        win.ਖਿੜਕੀ_ਮਾਪ = PSP2_ਖਿੜਕੀ_1280_X725;
    }
    // 544p
    ਨਹੀਂਤਾਂ {
        win.ਖਿੜਕੀ_ਮਾਪ = PSP2_ਖਿੜਕੀ_960_X544;
    }
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        ਜੇ (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            ਆਰਜ਼ੀ_major = _this->gl_config.major_ਸੰਸਕਰਣ;
            ਆਰਜ਼ੀ_minor = _this->gl_config.minor_ਸੰਸਕਰਣ;
            ਆਰਜ਼ੀ_profile = _this->gl_config.profile_ਨਕਾਬ;

            _this->gl_config.major_ਸੰਸਕਰਣ = 2;
            _this->gl_config.minor_ਸੰਸਕਰਣ = 1;
            _this->gl_config.profile_ਨਕਾਬ = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, &win);
        ਜੇ (wdata->egl_surface == EGL_NO_SURFACE) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Could not create GLES window surface");
        }
        ਜੇ (use_opengl) {
            // Revert
            _this->gl_config.major_ਸੰਸਕਰਣ = ਆਰਜ਼ੀ_major;
            _this->gl_config.minor_ਸੰਸਕਰਣ = ਆਰਜ਼ੀ_minor;
            _this->gl_config.profile_ਨਕਾਬ = ਆਰਜ਼ੀ_profile;
        }
    }
#ਜੇ_ਅੰਤ

    // fix input, we need to find a better way
    SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);

    // Window has been successfully created
    ਵਾਪਸ true;
}

ਖਾਲੀ VITA_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
bool VITA_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ SDL_Unsupported();
}
ਖਾਲੀ VITA_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ VITA_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ VITA_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ VITA_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ VITA_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ VITA_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
ਖਾਲੀ VITA_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}
bool VITA_ਸੈੱਟ_ਖਿੜਕੀ_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    ਵਾਪਸ true;
}

ਖਾਲੀ VITA_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;

    ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_free(ਅੰਕੜੇ);

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    Vita_ਖਿੜਕੀ = ਨਿਰਾ;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ਵਾਪਸ true;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SCE_IME_LANGUAGE_ENGLISH_US
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ utf16_ਮੰਜ਼ਿਲ_utf8(ਅਚਲ uint16_t *src, uint8_t *dst)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; src[i]; i++) {
        ਜੇ (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } ਨਹੀਂਤਾਂ ਜੇ (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } ਨਹੀਂਤਾਂ ਜੇ ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } ਨਹੀਂਤਾਂ {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
SceWChar16 libime_ਬਾਹਰਲਾ[SCE_IME_MAX_PREEDIT_ਲੰਮਾਈ + SCE_IME_MAX_ਪਾਠ_ਲੰਮਾਈ + 1];
ਅੱਖਰ libime_initval[8] = { 1 };
SceImeCaret caret_rev;

ਖਾਲੀ VITA_ImeEventHandler(ਖਾਲੀ *arg, ਅਚਲ Sce_Ime_Event_ਅੰਕੜੇ *e)
{
    SDL_Video_ਅੰਕੜੇ *videodata = (SDL_Video_ਅੰਕੜੇ *)arg;
    uint8_t utf8_ਬਫਰ[SCE_IME_MAX_ਪਾਠ_ਲੰਮਾਈ];
    ਚੋਣ (e->id) {
    ਹਾਲਤ SCE_IME_EVENT_UPDATE_ਪਾਠ:
        ਜੇ (e->param.ਪਾਠ.caret_ਸੂਚਕਾਂਕ == 0) {
            SDL_Send_Keyboard_ਕੁੰਜੀ_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_ਸੈੱਟ_ਪਾਠ((SceWChar16 *)libime_initval, 4);
        } ਨਹੀਂਤਾਂ {
            utf16_ਮੰਜ਼ਿਲ_utf8((SceWChar16 *)&libime_ਬਾਹਰਲਾ[1], utf8_ਬਫਰ);
            ਜੇ (utf8_ਬਫਰ[0] == ' ') {
                SDL_Send_Keyboard_ਕੁੰਜੀ_Auto_Release(0, SDL_SCANCODE_SPACE);
            } ਨਹੀਂਤਾਂ {
                SDL_Send_Keyboard_ਪਾਠ((ਅਚਲ ਅੱਖਰ *)utf8_ਬਫਰ);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_ਬਾਹਰਲਾ, 0, ((SCE_IME_MAX_PREEDIT_ਲੰਮਾਈ + SCE_IME_MAX_ਪਾਠ_ਲੰਮਾਈ + 1) * ਆਕਾਰ(SceWChar16)));
            caret_rev.ਸੂਚਕਾਂਕ = 1;
            sce_Ime_ਸੈੱਟ_Caret(&caret_rev);
            sce_Ime_ਸੈੱਟ_ਪਾਠ((SceWChar16 *)libime_initval, 4);
        }
        ਰੋਕੋ;
    ਹਾਲਤ SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_ਕੁੰਜੀ_Auto_Release(0, SDL_SCANCODE_RETURN);
        ਰੋਕੋ;
    ਹਾਲਤ SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_ਸਰਗਰਮ = false;
        SDL_SendScreenKeyboardHidden();
        ਰੋਕੋ;
    }
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_VITA_PVR

ਖਾਲੀ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SceInt32 res;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_ਬਫਰ_ਮਾਪ / ਆਕਾਰ(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_ਬਾਹਰਲਾ, 0, ((SCE_IME_MAX_PREEDIT_ਲੰਮਾਈ + SCE_IME_MAX_ਪਾਠ_ਲੰਮਾਈ + 1) * ਆਕਾਰ(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
    ਮੂਲ:
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ:
        param.type = SCE_IME_TYPE_DEFAULT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ:
        param.type = SCE_IME_TYPE_ਸੰਖਿਆ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_ਸੰਖਿਆ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਸੰਖਿਆ_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_ਸੰਖਿਆ;
        ਰੋਕੋ;
    }
    param.option = 0;
    ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    ਜੇ (!SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    ਜੇ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.ਨਿਵੇਸ਼_ਪਾਠ_ਬਫਰ = libime_ਬਾਹਰਲਾ;
    param.max_ਪਾਠ_ਲੰਮਾਈ = SCE_IME_MAX_ਪਾਠ_ਲੰਮਾਈ;
    param.handler = VITA_ImeEventHandler;
    param.filter = ਨਿਰਾ;
    param.initial_ਪਾਠ = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    ਜੇ (res < 0) {
        SDL_ਸੈੱਟ_Error("Failed to init IME");
        ਵਾਪਸ;
    }

#ਨਹੀਂਤਾਂ
    SceWChar16 *title = u"";
    SceWChar16 *ਪਾਠ = u"";

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.supportedLanguages = 0;
    param.languagesForced = SCE_FALSE;
    param.type = SCE_IME_TYPE_DEFAULT;
    param.option = 0;
    param.ਪਾਠ_Box_ਬਹੁਲਕ = SCE_IME_DIALOG_TEXTBOX_ਬਹੁਲਕ_WITH_CLEAR;
    param.max_ਪਾਠ_ਲੰਮਾਈ = SCE_IME_DIALOG_MAX_ਪਾਠ_ਲੰਮਾਈ;

    param.title = title;
    param.initial_ਪਾਠ = ਪਾਠ;
    param.ਨਿਵੇਸ਼_ਪਾਠ_ਬਫਰ = videodata->ime_ਬਫਰ;

    res = sceImeDialogInit(&param);
    ਜੇ (res < 0) {
        SDL_ਸੈੱਟ_Error("Failed to init IME dialog");
        ਵਾਪਸ;
    }

#ਜੇ_ਅੰਤ

    videodata->ime_ਸਰਗਰਮ = true;

    SDL_SendScreenKeyboardShown();
}

ਖਾਲੀ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;

    Sce_Common_Dialog_ਸਥਿਤੀ dialog_ਸਥਿਤੀ = sce_Ime_Dialog_Get_ਸਥਿਤੀ();

    ਚੋਣ (dialog_ਸਥਿਤੀ) {
    ਮੂਲ:
    ਹਾਲਤ SCE_COMMON_DIALOG_ਸਥਿਤੀ_NONE:
    ਹਾਲਤ SCE_COMMON_DIALOG_ਸਥਿਤੀ_RUNNING:
        ਰੋਕੋ;
    ਹਾਲਤ SCE_COMMON_DIALOG_ਸਥਿਤੀ_ਮੁਕੰਮਲ:
        sce_Ime_Dialog_ਪਦ();
        ਰੋਕੋ;
    }

    videodata->ime_ਸਰਗਰਮ = false;

    SDL_SendScreenKeyboardHidden();
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
#ਜੇ_ਅੰਤ

    ਜੇ (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_VITA_PVR
    ਜੇ (videodata->ime_ਸਰਗਰਮ == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_ਸਥਿਤੀ dialog_ਸਥਿਤੀ = sce_Ime_Dialog_Get_ਸਥਿਤੀ();
        ਜੇ (dialog_ਸਥਿਤੀ == SCE_COMMON_DIALOG_ਸਥਿਤੀ_ਮੁਕੰਮਲ) {
            uint8_t utf8_ਬਫਰ[SCE_IME_DIALOG_MAX_ਪਾਠ_ਲੰਮਾਈ];

            Sce_Ime_Dialog_ਨਤੀਜਾ ਨਤੀਜਾ;
            SDL_zero(ਨਤੀਜਾ);
            sce_Ime_Dialog_Get_ਨਤੀਜਾ(&ਨਤੀਜਾ);

            // Convert UTF16 to UTF8
            utf16_ਮੰਜ਼ਿਲ_utf8(videodata->ime_ਬਫਰ, utf8_ਬਫਰ);

            // Send SDL event
            SDL_Send_Keyboard_ਪਾਠ((ਅਚਲ ਅੱਖਰ *)utf8_ਬਫਰ);

            // Send enter key only on enter
            ਜੇ (ਨਤੀਜਾ.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_ਕੁੰਜੀ_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_ਪਦ();

            videodata->ime_ਸਰਗਰਮ = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA

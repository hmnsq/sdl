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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA

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

#ಆದರೆ defined(SDL_VIDEO_VITA_PVR)
#ವ್ಯಾಖ್ಯಾನಿಸು VITA_GLES_Get_Proc_ವಿಳಾಸ  SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ
#ವ್ಯಾಖ್ಯಾನಿಸು VITA_GLES_UnloadLibrary   SDL_EGL_UnloadLibrary
#ವ್ಯಾಖ್ಯಾನಿಸು VITA_GLES_ಗಣ_ಅದಲುಬದಲು_Interval SDL_EGL_ಗಣ_ಅದಲುಬದಲು_Interval
#ವ್ಯಾಖ್ಯಾನಿಸು VITA_GLES_Get_ಅದಲುಬದಲು_Interval SDL_EGL_Get_ಅದಲುಬದಲು_Interval
#ವ್ಯಾಖ್ಯಾನಿಸು VITA_GLES_DestroyContext   SDL_EGL_DestroyContext
#ಆದರೆ_ಅಂತ್ಯ

SDL_ಕಿಟಕಿ *Vita_ಕಿಟಕಿ;

ಸ್ಥಿರ ಶೂನ್ಯ VITA_Destroy(SDL_VideoDevice *device)
{
    SDL_free(device->ಆಂತರಿಕ);
    SDL_free(device);
}

ಸ್ಥಿರ SDL_VideoDevice *VITA_Create(ಶೂನ್ಯ)
{
    SDL_VideoDevice *device;
    SDL_Video_ದತ್ತಾಂಶ *phdata;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PIB
    SDL_GLDriver_ದತ್ತಾಂಶ *gldata;
#ಆದರೆ_ಅಂತ್ಯ
    // Initialize SDL_VideoDevice structure
    device = (SDL_VideoDevice *)SDL_calloc(1, ಗಾತ್ರ(SDL_VideoDevice));
    ಆದರೆ (!device) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Initialize internal VITA specific data
    phdata = (SDL_Video_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Video_ದತ್ತಾಂಶ));
    ಆದರೆ (!phdata) {
        SDL_free(device);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PIB

    gldata = (SDL_GLDriver_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_GLDriver_ದತ್ತಾಂಶ));
    ಆದರೆ (!gldata) {
        SDL_free(device);
        SDL_free(phdata);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    device->gl_ದತ್ತಾಂಶ = gldata;
    phdata->egl_initialized = true;
#ಆದರೆ_ಅಂತ್ಯ
    phdata->ime_ಸಕ್ರಿಯ = false;

    device->ಆಂತರಿಕ = phdata;

    // Setup amount of available displays and current display
    device->ಅಂಕೆ_displays = 0;

    // Set device free function
    device->ಬಿಡುಗಡೆ = VITA_Destroy;

    // Setup all functions which we can handle
    device->VideoInit = VITA_VideoInit;
    device->VideoQuit = VITA_VideoQuit;
    device->CreateSDLWindow = VITA_Create_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Title = VITA_ಗಣ_ಕಿಟಕಿ_Title;
    device->ಗಣ_ಕಿಟಕಿ_Position = VITA_ಗಣ_ಕಿಟಕಿ_Position;
    device->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ = VITA_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ;
    device->Show_ಕಿಟಕಿ = VITA_Show_ಕಿಟಕಿ;
    device->Hide_ಕಿಟಕಿ = VITA_Hide_ಕಿಟಕಿ;
    device->Raise_ಕಿಟಕಿ = VITA_Raise_ಕಿಟಕಿ;
    device->Maximize_ಕಿಟಕಿ = VITA_Maximize_ಕಿಟಕಿ;
    device->Minimize_ಕಿಟಕಿ = VITA_Minimize_ಕಿಟಕಿ;
    device->Restore_ಕಿಟಕಿ = VITA_Restore_ಕಿಟಕಿ;
    device->ಗಣ_ಕಿಟಕಿ_Mouse_Grab = VITA_ಗಣ_ಕಿಟಕಿ_Grab;
    device->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab = VITA_ಗಣ_ಕಿಟಕಿ_Grab;
    device->Destroy_ಕಿಟಕಿ = VITA_Destroy_ಕಿಟಕಿ;

    /*
        // Disabled, causes issues on high-framerate updates. SDL still emulates this.
        // TODO: Is VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER needed?
        device->CreateWindowFramebuffer = VITA_CreateWindowFramebuffer;
        device->UpdateWindowFramebuffer = VITA_UpdateWindowFramebuffer;
        device->DestroyWindowFramebuffer = VITA_DestroyWindowFramebuffer;
    */

#ಆದರೆ defined(SDL_VIDEO_VITA_PIB) || defined(SDL_VIDEO_VITA_PVR)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR_OGL
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false)) {
        device->GL_ತುಂಬು_Library = VITA_GL_ತುಂಬು_Library;
        device->GL_CreateContext = VITA_GL_CreateContext;
        device->GL_Get_Proc_ವಿಳಾಸ = VITA_GL_Get_Proc_ವಿಳಾಸ;
    } ಇಲ್ಲದಿದ್ದರೆ {
#ಆದರೆ_ಅಂತ್ಯ
        device->GL_ತುಂಬು_Library = VITA_GLES_ತುಂಬು_Library;
        device->GL_CreateContext = VITA_GLES_CreateContext;
        device->GL_Get_Proc_ವಿಳಾಸ = VITA_GLES_Get_Proc_ವಿಳಾಸ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR_OGL
    }
#ಆದರೆ_ಅಂತ್ಯ

    device->GL_UnloadLibrary = VITA_GLES_UnloadLibrary;
    device->GL_MakeCurrent = VITA_GLES_MakeCurrent;
    device->GL_ಗಣ_ಅದಲುಬದಲು_Interval = VITA_GLES_ಗಣ_ಅದಲುಬದಲು_Interval;
    device->GL_Get_ಅದಲುಬದಲು_Interval = VITA_GLES_Get_ಅದಲುಬದಲು_Interval;
    device->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ = VITA_GLES_ಅದಲುಬದಲು_ಕಿಟಕಿ;
    device->GL_DestroyContext = VITA_GLES_DestroyContext;
#ಆದರೆ_ಅಂತ್ಯ

    device->HasScreenKeyboardSupport = VITA_HasScreenKeyboardSupport;
    device->ShowScreenKeyboard = VITA_ShowScreenKeyboard;
    device->HideScreenKeyboard = VITA_HideScreenKeyboard;

    device->PumpEvents = VITA_PumpEvents;

    device->device_caps = VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY;

    ಹಿಂತಿರುಗಿ device;
}

VideoBootStrap VITA_bootstrap = {
    "vita",
    "VITA Video Driver",
    VITA_Create,
    VITA_Show_ಸಂದೇಶ_Box,
    false
};

/*****************************************************************************/
// SDL Video and Display initialization/handling functions
/*****************************************************************************/
bool VITA_VideoInit(SDL_VideoDevice *_this)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *res = SDL_GetHint(SDL_HINT_VITA_RESOLUTION);
#ಆದರೆ_ಅಂತ್ಯ
    SDL_zero(ಬಹುಲಕ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
    ಆದರೆ (res) {
        // 1088i for PSTV (Or Sharpscale)
        ಆದರೆ (SDL_strncmp(res, "1080", 4) == 0) {
            ಬಹುಲಕ.w = 1920;
            ಬಹುಲಕ.h = 1088;
        }
        // 725p for PSTV (Or Sharpscale)
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strncmp(res, "720", 3) == 0) {
            ಬಹುಲಕ.w = 1280;
            ಬಹುಲಕ.h = 725;
        }
    }
    // 544p
    ಇಲ್ಲದಿದ್ದರೆ {
#ಆದರೆ_ಅಂತ್ಯ
        ಬಹುಲಕ.w = 960;
        ಬಹುಲಕ.h = 544;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಬಹುಲಕ.refresh_ದರ = 60.0f;

    // 32 bpp for default
    ಬಹುಲಕ.format = SDL_PIXELFORMAT_ABGR8888;

    ಆದರೆ (SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    VITA_InitTouch();
    VITA_InitKeyboard();
    VITA_InitMouse();

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ VITA_VideoQuit(SDL_VideoDevice *_this)
{
    VITA_QuitTouch();
}

bool VITA_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wdata;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
    Psp2_Native_ಕಿಟಕಿ win;
    ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_major = 2;
    ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_minor = 1;
    ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_profile = 0;
#ಆದರೆ_ಅಂತ್ಯ

    // Allocate window internal data
    wdata = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ));
    ಆದರೆ (!wdata) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Setup driver data for this window
    ಕಿಟಕಿ->ಆಂತರಿಕ = wdata;

    // Vita can only have one window
    ಆದರೆ (Vita_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Only one window supported");
    }

    Vita_ಕಿಟಕಿ = ಕಿಟಕಿ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
    win.type = PSP2_DRAWABLE_TYPE_ಕಿಟಕಿ;
    win.ಅಂಕೆ_Flip_Buffers = 2;
    win.flipChainThrdAffinity = 0x20000;

    // 1088i for PSTV (Or Sharpscale)
    ಆದರೆ (ಕಿಟಕಿ->w == 1920) {
        win.ಕಿಟಕಿ_ಗಾತ್ರ = PSP2_ಕಿಟಕಿ_1920_X1088;
    }
    // 725p for PSTV (Or Sharpscale)
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->w == 1280) {
        win.ಕಿಟಕಿ_ಗಾತ್ರ = PSP2_ಕಿಟಕಿ_1280_X725;
    }
    // 544p
    ಇಲ್ಲದಿದ್ದರೆ {
        win.ಕಿಟಕಿ_ಗಾತ್ರ = PSP2_ಕಿಟಕಿ_960_X544;
    }
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        bool use_opengl = SDL_GetHintBoolean(SDL_HINT_VITA_PVR_OPENGL, false);
        ಆದರೆ (use_opengl) {
            // Set version to 2.1 and PROFILE to ES
            ತಾತ್ಕಾಲಿಕ_major = _this->gl_config.major_ಆವೃತ್ತಿ;
            ತಾತ್ಕಾಲಿಕ_minor = _this->gl_config.minor_ಆವೃತ್ತಿ;
            ತಾತ್ಕಾಲಿಕ_profile = _this->gl_config.profile_ಮುಖವಾಡ;

            _this->gl_config.major_ಆವೃತ್ತಿ = 2;
            _this->gl_config.minor_ಆವೃತ್ತಿ = 1;
            _this->gl_config.profile_ಮುಖವಾಡ = SDL_GL_CONTEXT_PROFILE_ES;
        }
        wdata->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, &win);
        ಆದರೆ (wdata->egl_surface == EGL_NO_SURFACE) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Could not create GLES window surface");
        }
        ಆದರೆ (use_opengl) {
            // Revert
            _this->gl_config.major_ಆವೃತ್ತಿ = ತಾತ್ಕಾಲಿಕ_major;
            _this->gl_config.minor_ಆವೃತ್ತಿ = ತಾತ್ಕಾಲಿಕ_minor;
            _this->gl_config.profile_ಮುಖವಾಡ = ತಾತ್ಕಾಲಿಕ_profile;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // fix input, we need to find a better way
    SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);

    // Window has been successfully created
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ VITA_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
bool VITA_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}
ಶೂನ್ಯ VITA_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ VITA_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ VITA_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ VITA_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ VITA_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ VITA_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
ಶೂನ್ಯ VITA_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}
bool VITA_ಗಣ_ಕಿಟಕಿ_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ VITA_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_free(ದತ್ತಾಂಶ);

    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
    Vita_ಕಿಟಕಿ = ಖಾಲಿ;
}

bool VITA_HasScreenKeyboardSupport(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SCE_IME_LANGUAGE_ENGLISH_US
#ವ್ಯಾಖ್ಯಾನಿಸು SCE_IME_LANGUAGE_ENGLISH_US SCE_IME_LANGUAGE_ENGLISH
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ utf16_ಗಮ್ಯ_utf8(ಸ್ಥಿರಾಂಕ uint16_t *src, uint8_t *dst)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; src[i]; i++) {
        ಆದರೆ (!(src[i] & 0xFF80)) {
            *(dst++) = src[i] & 0xFF;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(src[i] & 0xF800)) {
            *(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
            *(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
            *(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
            *(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
            *(dst++) = (src[i + 1] & 0x3F) | 0x80;
            i += 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
            *(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
            *(dst++) = (src[i] & 0x3F) | 0x80;
        }
    }

    *dst = '\0';
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR
SceWChar16 libime_ಹೊರಹೋಗು[SCE_IME_MAX_PREEDIT_ಉದ್ದಳತೆ + SCE_IME_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ + 1];
ಅಕ್ಷರ libime_initval[8] = { 1 };
SceImeCaret caret_rev;

ಶೂನ್ಯ VITA_ImeEventHandler(ಶೂನ್ಯ *arg, ಸ್ಥಿರಾಂಕ Sce_Ime_Event_ದತ್ತಾಂಶ *e)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = (SDL_Video_ದತ್ತಾಂಶ *)arg;
    uint8_t utf8_ಬಫರ್[SCE_IME_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ];
    ಆಯ್ಕೆ (e->id) {
    ಸ್ಥಿತಿ SCE_IME_EVENT_UPDATE_ಪಠ್ಯ:
        ಆದರೆ (e->param.ಪಠ್ಯ.caret_ಸೂಚ್ಯಂಕ == 0) {
            SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_BACKSPACE);
            sce_Ime_ಗಣ_ಪಠ್ಯ((SceWChar16 *)libime_initval, 4);
        } ಇಲ್ಲದಿದ್ದರೆ {
            utf16_ಗಮ್ಯ_utf8((SceWChar16 *)&libime_ಹೊರಹೋಗು[1], utf8_ಬಫರ್);
            ಆದರೆ (utf8_ಬಫರ್[0] == ' ') {
                SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_SPACE);
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_Send_Keyboard_ಪಠ್ಯ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)utf8_ಬಫರ್);
            }
            SDL_zero(caret_rev);
            SDL_memset(libime_ಹೊರಹೋಗು, 0, ((SCE_IME_MAX_PREEDIT_ಉದ್ದಳತೆ + SCE_IME_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ + 1) * ಗಾತ್ರ(SceWChar16)));
            caret_rev.ಸೂಚ್ಯಂಕ = 1;
            sce_Ime_ಗಣ_Caret(&caret_rev);
            sce_Ime_ಗಣ_ಪಠ್ಯ((SceWChar16 *)libime_initval, 4);
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SCE_IME_EVENT_PRESS_ENTER:
        SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_RETURN);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SCE_IME_EVENT_PRESS_CLOSE:
        sceImeClose();
        videodata->ime_ಸಕ್ರಿಯ = false;
        SDL_SendScreenKeyboardHidden();
        ನಿಲ್ಲಿಸು;
    }
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_VITA_PVR

ಶೂನ್ಯ VITA_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SceInt32 res;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_VITA_PVR

    SceUInt32 libime_work[SCE_IME_WORK_ಬಫರ್_ಗಾತ್ರ / ಗಾತ್ರ(SceInt32)];
    SceImeParam param;

    sceImeParamInit(&param);

    SDL_memset(libime_ಹೊರಹೋಗು, 0, ((SCE_IME_MAX_PREEDIT_ಉದ್ದಳತೆ + SCE_IME_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ + 1) * ಗಾತ್ರ(SceWChar16)));

    param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH_US;
    param.languagesForced = SCE_FALSE;
    ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(props)) {
    ಪೂರ್ವನಿಯೋಜಿತ:
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ:
        param.type = SCE_IME_TYPE_DEFAULT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_NAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_EMAIL:
        param.type = SCE_IME_TYPE_MAIL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_USERNAME:
        param.type = SCE_IME_TYPE_DEFAULT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_DEFAULT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_DEFAULT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ:
        param.type = SCE_IME_TYPE_ಸಂಖ್ಯೆ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_HIDDEN:
        param.type = SCE_IME_TYPE_ಸಂಖ್ಯೆ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ_PASSWORD_VISIBLE:
        param.type = SCE_IME_TYPE_ಸಂಖ್ಯೆ;
        ನಿಲ್ಲಿಸು;
    }
    param.option = 0;
    ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Capitalization(props) != SDL_CAPITALIZE_SENTENCES) {
        param.option |= SCE_IME_OPTION_NO_AUTO_CAPITALIZATION;
    }
    ಆದರೆ (!SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Autocorrect(props)) {
        param.option |= SCE_IME_OPTION_NO_ASSISTANCE;
    }
    ಆದರೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Multiline(props)) {
        param.option |= SCE_IME_OPTION_MULTILINE;
    }
    param.ಒಳಹರಿವು_ಪಠ್ಯ_ಬಫರ್ = libime_ಹೊರಹೋಗು;
    param.max_ಪಠ್ಯ_ಉದ್ದಳತೆ = SCE_IME_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ;
    param.handler = VITA_ImeEventHandler;
    param.filter = ಖಾಲಿ;
    param.initial_ಪಠ್ಯ = (SceWChar16 *)libime_initval;
    param.arg = videodata;
    param.work = libime_work;

    res = sceImeOpen(&param);
    ಆದರೆ (res < 0) {
        SDL_ಗಣ_Error("Failed to init IME");
        ಹಿಂತಿರುಗಿ;
    }

#ಇಲ್ಲದಿದ್ದರೆ
    SceWChar16 *title = u"";
    SceWChar16 *ಪಠ್ಯ = u"";

    SceImeDialogParam param;
    sceImeDialogParamInit(&param);

    param.supportedLanguages = 0;
    param.languagesForced = SCE_FALSE;
    param.type = SCE_IME_TYPE_DEFAULT;
    param.option = 0;
    param.ಪಠ್ಯ_Box_ಬಹುಲಕ = SCE_IME_DIALOG_TEXTBOX_ಬಹುಲಕ_WITH_CLEAR;
    param.max_ಪಠ್ಯ_ಉದ್ದಳತೆ = SCE_IME_DIALOG_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ;

    param.title = title;
    param.initial_ಪಠ್ಯ = ಪಠ್ಯ;
    param.ಒಳಹರಿವು_ಪಠ್ಯ_ಬಫರ್ = videodata->ime_ಬಫರ್;

    res = sceImeDialogInit(&param);
    ಆದರೆ (res < 0) {
        SDL_ಗಣ_Error("Failed to init IME dialog");
        ಹಿಂತಿರುಗಿ;
    }

#ಆದರೆ_ಅಂತ್ಯ

    videodata->ime_ಸಕ್ರಿಯ = true;

    SDL_SendScreenKeyboardShown();
}

ಶೂನ್ಯ VITA_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_VITA_PVR
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;

    Sce_Common_Dialog_ಸ್ಥಿತಿ dialog_ಸ್ಥಿತಿ = sce_Ime_Dialog_Get_ಸ್ಥಿತಿ();

    ಆಯ್ಕೆ (dialog_ಸ್ಥಿತಿ) {
    ಪೂರ್ವನಿಯೋಜಿತ:
    ಸ್ಥಿತಿ SCE_COMMON_DIALOG_ಸ್ಥಿತಿ_NONE:
    ಸ್ಥಿತಿ SCE_COMMON_DIALOG_ಸ್ಥಿತಿ_RUNNING:
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SCE_COMMON_DIALOG_ಸ್ಥಿತಿ_ಪೂರ್ಣಗೊಂಡ:
        sce_Ime_Dialog_ಪದ();
        ನಿಲ್ಲಿಸು;
    }

    videodata->ime_ಸಕ್ರಿಯ = false;

    SDL_SendScreenKeyboardHidden();
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ VITA_PumpEvents(SDL_VideoDevice *_this)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_VITA_PVR
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (_this->suspend_screensaver) {
        // cancel all idle timers to prevent vita going to sleep
        sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DEFAULT);
    }

    VITA_PollTouch();
    VITA_PollKeyboard();
    VITA_PollMouse();

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_VITA_PVR
    ಆದರೆ (videodata->ime_ಸಕ್ರಿಯ == true) {
        // update IME status. Terminate, if finished
        Sce_Common_Dialog_ಸ್ಥಿತಿ dialog_ಸ್ಥಿತಿ = sce_Ime_Dialog_Get_ಸ್ಥಿತಿ();
        ಆದರೆ (dialog_ಸ್ಥಿತಿ == SCE_COMMON_DIALOG_ಸ್ಥಿತಿ_ಪೂರ್ಣಗೊಂಡ) {
            uint8_t utf8_ಬಫರ್[SCE_IME_DIALOG_MAX_ಪಠ್ಯ_ಉದ್ದಳತೆ];

            Sce_Ime_Dialog_ಫಲಿತಾಂಶ ಫಲಿತಾಂಶ;
            SDL_zero(ಫಲಿತಾಂಶ);
            sce_Ime_Dialog_Get_ಫಲಿತಾಂಶ(&ಫಲಿತಾಂಶ);

            // Convert UTF16 to UTF8
            utf16_ಗಮ್ಯ_utf8(videodata->ime_ಬಫರ್, utf8_ಬಫರ್);

            // Send SDL event
            SDL_Send_Keyboard_ಪಠ್ಯ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)utf8_ಬಫರ್);

            // Send enter key only on enter
            ಆದರೆ (ಫಲಿತಾಂಶ.button == SCE_IME_DIALOG_BUTTON_ENTER) {
                SDL_Send_Keyboard_ಕೀಲಿ_Auto_Release(0, SDL_SCANCODE_RETURN);
            }

            sce_Ime_Dialog_ಪದ();

            videodata->ime_ಸಕ್ರಿಯ = false;

            SDL_SendScreenKeyboardHidden();
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA

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

// The high-level video driver subsystem

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_clipboard_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_surface_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_rect_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_hints_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_properties_c.h"
#ಅನ್ತರ್ಭಾವ "../timer/SDL_timer_c.h"
#ಅನ್ತರ್ಭಾವ "../camera/SDL_camera_c.h"
#ಅನ್ತರ್ಭಾವ "../render/SDL_sysrender.h"
#ಅನ್ತರ್ಭಾವ "../main/SDL_main_callbacks.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL

#ಆದರೆ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles.h>
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ಆದರೆ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles2.h>
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_CONTEXT_RELEASE_BEHAVIOR
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#ಆದರೆ_ಅಂತ್ಯ

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#ವ್ಯಾಖ್ಯಾನಿಸು GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#ಆದರೆ_ಅಂತ್ಯ

// This is always the same number between the various EXT/ARB/GLES extensions.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_FRAMEBUFFER_SRGB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_FRAMEBUFFER_SRGB 0x8DB9
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_EMSCRIPTEN
#ಅನ್ತರ್ಭಾವ <emscripten.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_3DS
#ಅನ್ತರ್ಭಾವ <3ds.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_RGBA_FLOAT_ಬಹುಲಕ_ARB
#ವ್ಯಾಖ್ಯಾನಿಸು GL_RGBA_FLOAT_ಬಹುಲಕ_ARB 0x8820
#ಆದರೆ_ಅಂತ್ಯ /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ಸ್ಥಿರ VideoBootStrap *bootstrap[] = {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ಖಾಸಗಿ
    &ಖಾಸಗಿ_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
    &X11_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_ಒಳಹರಿವು_LINUXEV
    &DUMMY_evdev_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#ಆದರೆ_ಅಂತ್ಯ
    ಖಾಲಿ
};

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಫಲಿತಾಂಶ)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(ಕಿಟಕಿ, SDL_OBJECT_TYPE_ಕಿಟಕಿ)) {     \
        SDL_ಗಣ_Error("Invalid window");                                 \
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;                                                  \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_DISPLAY_MAGIC(display, ಫಲಿತಾಂಶ)                            \
    CHECK_PARAM(!display) {                                             \
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;                                                  \
    }                                                                   \

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, ಫಲಿತಾಂಶ)                          \
    CHECK_PARAM(SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {                          \
        SDL_ಗಣ_Error("Operation invalid on popup windows");             \
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;                                                  \
    }

#ಆದರೆ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
ಬಾಹ್ಯ bool Cocoa_Is_ಕಿಟಕಿ_ಒಳ_Fullscreen_Space(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_Is_ಕಿಟಕಿ_ಒಳ_Fullscreen_Space_Transition(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Cocoa_ಗಣ_ಕಿಟಕಿ_Fullscreen_Space(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool state, bool blocking);
ಬಾಹ್ಯ bool Cocoa_IsShowingModalDialog(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_UIKIT
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_UpdateLifecycleObserver(ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_Display_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಸ್ಥಿರ ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_Display_Scale_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಸ್ಥಿರ ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

// Convenience functions for reading driver flags
ಸ್ಥಿರ bool SDL_ಬಹುಲಕ_Switching_Emulated(SDL_VideoDevice *_this)
{
    ಆದರೆ (_this->device_caps & VIDEO_DEVICE_CAPS_ಬಹುಲಕ_SWITCHING_EMULATED) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ಸ್ಥಿರ bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ಸ್ಥಿರ bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ಸ್ಥಿರ bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ಸ್ಥಿರ bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ಸ್ಥಿರ bool syncHint;

ಸ್ಥಿರ ಶೂನ್ಯ SDL_SyncHintWatcher(ಶೂನ್ಯ *userdata, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *old_ಮೌಲ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಮೌಲ್ಯ)
{
    syncHint = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, false);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_SyncIfRequired(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (syncHint) {
        SDL_Sync_ಕಿಟಕಿ(ಕಿಟಕಿ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_Update_ಕಿಟಕಿ_Hierarchy(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ)
{
    // Unlink the window from the existing parent.
    ಆದರೆ (ಕಿಟಕಿ->ಪೋಷಕ) {
        ಆದರೆ (ಕಿಟಕಿ->ಮುಂದಿನ_sibling) {
            ಕಿಟಕಿ->ಮುಂದಿನ_sibling->prev_sibling = ಕಿಟಕಿ->prev_sibling;
        }
        ಆದರೆ (ಕಿಟಕಿ->prev_sibling) {
            ಕಿಟಕಿ->prev_sibling->ಮುಂದಿನ_sibling = ಕಿಟಕಿ->ಮುಂದಿನ_sibling;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->ಪೋಷಕ->ಮೊದಲ_ಮಗು = ಕಿಟಕಿ->ಮುಂದಿನ_sibling;
        }

        ಕಿಟಕಿ->ಪೋಷಕ = ಖಾಲಿ;
    }

    ಆದರೆ (ಪೋಷಕ) {
        ಕಿಟಕಿ->ಪೋಷಕ = ಪೋಷಕ;

        ಕಿಟಕಿ->ಮುಂದಿನ_sibling = ಪೋಷಕ->ಮೊದಲ_ಮಗು;
        ಆದರೆ (ಪೋಷಕ->ಮೊದಲ_ಮಗು) {
            ಪೋಷಕ->ಮೊದಲ_ಮಗು->prev_sibling = ಕಿಟಕಿ;
        }
        ಪೋಷಕ->ಮೊದಲ_ಮಗು = ಕಿಟಕಿ;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ "SDL.internal.window.texturedata"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    ಶೂನ್ಯ *pixels;
    ಪೂರ್ಣಾಂಕ pitch;
    ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_ಪ್ರತಿ_pixel;
} SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ;

ಸ್ಥಿರ Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#ಆದರೆ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !ಗುರಿ_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ಆದರೆ (_this->GL_CreateContext) {
        ಹಿಂತಿರುಗಿ SDL_ಕಿಟಕಿ_OPENGL;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(SDL_VIDEO_METAL) && (ಗುರಿ_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ಆದರೆ (_this->Metal_CreateView) {
        ಹಿಂತಿರುಗಿ SDL_ಕಿಟಕಿ_METAL;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ಆದರೆ (SDL_strcmp(_this->name, "openvr") == 0) {
        ಹಿಂತಿರುಗಿ SDL_ಕಿಟಕಿ_OPENGL;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ bool SDL_Create_ಕಿಟಕಿ_Texture(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *)SDL_Get_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ, ಖಾಲಿ);
    ಸ್ಥಿರಾಂಕ bool transparent = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) ? true : false;
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ w, h;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormat *texture_formats;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_Renderer *renderer = ಖಾಲಿ;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *render_driver = ಖಾಲಿ;

        // See if there's a render driver being requested
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ಆದರೆ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ಆದರೆ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ಆದರೆ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = ಖಾಲಿ;
        }

        ಅಕ್ಷರ *render_driver_copy = ಖಾಲಿ;
        ಆದರೆ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ಆದರೆ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                ಅಕ್ಷರ *prev = render_driver_copy;
                ಅಕ್ಷರ *ptr = prev;
                ಆಗ ((ptr = SDL_strchr(ptr, ',')) != ಖಾಲಿ) {
                    *ptr = '\0';
                    ಸ್ಥಿರಾಂಕ bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ಆದರೆ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ptr++;
                        prev = ptr;
                    }
                }

                ಆದರೆ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ಆದರೆ (render_driver) {
            renderer = SDL_CreateRenderer(ಕಿಟಕಿ, render_driver);
            SDL_free(render_driver_copy);
            ಆದರೆ (!renderer) {
                // The error for this specific renderer has already been set
                ಹಿಂತಿರುಗಿ false;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_assert(render_driver_copy == ಖಾಲಿ);
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಒಟ್ಟು = SDL_Get_ಅಂಕೆ_Render_Drivers();
            ಗಾಗಿ (i = 0; i < ಒಟ್ಟು; ++i) {
                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = SDL_GetRenderDriver(i);
                ಆದರೆ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(ಕಿಟಕಿ, name);
                    ಆದರೆ (renderer) {
                        ನಿಲ್ಲಿಸು; // this will work.
                    }
                }
            }
            ಆದರೆ (!renderer) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ಖಾಲಿ); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
        ಆದರೆ (!ದತ್ತಾಂಶ) {
            SDL_DestroyRenderer(renderer);
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ (!SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ, ದತ್ತಾಂಶ)) {
            SDL_DestroyRenderer(renderer);
            ಹಿಂತಿರುಗಿ false;
        }

        ದತ್ತಾಂಶ->renderer = renderer;
    }

    texture_formats = (ಸ್ಥಿರಾಂಕ SDL_PixelFormat *)SDL_Get_ಸೂಚಕ_Property(SDL_GetRendererProperties(ದತ್ತಾಂಶ->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_ಸೂಚಕ, ಖಾಲಿ);
    ಆದರೆ (!texture_formats) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Free any old texture and pixel data
    ಆದರೆ (ದತ್ತಾಂಶ->texture) {
        SDL_DestroyTexture(ದತ್ತಾಂಶ->texture);
        ದತ್ತಾಂಶ->texture = ಖಾಲಿ;
    }
    SDL_free(ದತ್ತಾಂಶ->pixels);
    ದತ್ತಾಂಶ->pixels = ಖಾಲಿ;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    ಗಾಗಿ (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ಆದರೆ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10_ಬಿಟ್(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            ನಿಲ್ಲಿಸು;
        }
    }

    ದತ್ತಾಂಶ->texture = SDL_CreateTexture(ದತ್ತಾಂಶ->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    ಆದರೆ (!ದತ್ತಾಂಶ->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ಹಿಂತಿರುಗಿ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_ಗಣ_Texture_Blend_ಬಹುಲಕ(ದತ್ತಾಂಶ->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    ದತ್ತಾಂಶ->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel = SDL_BYTESPERPIXEL(*format);
    ದತ್ತಾಂಶ->pitch = (((w * ದತ್ತಾಂಶ->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ಸ್ಥಿರಾಂಕ size_t allocsize = (size_t)h * ದತ್ತಾಂಶ->pitch;
        ದತ್ತಾಂಶ->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ಆದರೆ (!ದತ್ತಾಂಶ->pixels) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    *pixels = ದತ್ತಾಂಶ->pixels;
    *pitch = ದತ್ತಾಂಶ->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_ಗಣ_Render_Viewport(ದತ್ತಾಂಶ->renderer, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Texture_VSync(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ vsync)
{
    SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *)SDL_Get_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ, ಖಾಲಿ);
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (!ದತ್ತಾಂಶ->renderer) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Render_VSync(ದತ್ತಾಂಶ->renderer, vsync);
}

ಸ್ಥಿರ bool SDL_Get_ಕಿಟಕಿ_Texture_VSync(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *vsync)
{
    SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *)SDL_Get_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ, ಖಾಲಿ);
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (!ದತ್ತಾಂಶ->renderer) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ SDL_GetRenderVSync(ದತ್ತಾಂಶ->renderer, vsync);
}

ಸ್ಥಿರ bool SDL_Update_ಕಿಟಕಿ_Texture(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects, ಪೂರ್ಣಾಂಕ numrects)
{
    SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    SDL_Rect rect;
    ಶೂನ್ಯ *src;
    ಪೂರ್ಣಾಂಕ w, h;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    ದತ್ತಾಂಶ = (SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *)SDL_Get_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ, ಖಾಲಿ);
    ಆದರೆ (!ದತ್ತಾಂಶ || !ದತ್ತಾಂಶ->texture) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ಆದರೆ (SDL_Get_ಹರವು_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (ಶೂನ್ಯ *)((Uint8 *)ದತ್ತಾಂಶ->pixels +
                       rect.y * ದತ್ತಾಂಶ->pitch +
                       rect.x * ದತ್ತಾಂಶ->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel);
        ಆದರೆ (!SDL_UpdateTexture(ದತ್ತಾಂಶ->texture, &rect, src, ದತ್ತಾಂಶ->pitch)) {
            ಹಿಂತಿರುಗಿ false;
        }

        ಆದರೆ (!SDL_RenderTexture(ದತ್ತಾಂಶ->renderer, ದತ್ತಾಂಶ->texture, ಖಾಲಿ, ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }

        SDL_RenderPresent(ದತ್ತಾಂಶ->renderer);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_Destroy_ಕಿಟಕಿ_Texture(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    ಆದರೆ (SDL_HasProperty(props, SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ)) {
        SDL_ಕಿಟಕಿ_Texture_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = SDL_Get_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ, ಖಾಲಿ);

        ಆದರೆ (ದತ್ತಾಂಶ->texture) {
            SDL_DestroyTexture(ದತ್ತಾಂಶ->texture);
        }
        ಆದರೆ (ದತ್ತಾಂಶ->renderer) {
            SDL_DestroyRenderer(ದತ್ತಾಂಶ->renderer);
        }
        SDL_free(ದತ್ತಾಂಶ->pixels);
        SDL_free(ದತ್ತಾಂಶ);

        SDL_ClearProperty(props, SDL_PROP_ಕಿಟಕಿ_TEXTUREDATA_ಸೂಚಕ);
    }
}

ಸ್ಥಿರ SDL_VideoDevice *_this = ಖಾಲಿ;
ಸ್ಥಿರ SDL_AtomicInt SDL_messagebox_ಎಣಿಕೆ;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDLCALL cmpmodes(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *A, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *B)
{
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *a = (ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *)A;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *b = (ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *)B;
    ಪೂರ್ಣಾಂಕ a_refresh_ದರ = (ಪೂರ್ಣಾಂಕ)(a->refresh_ದರ * 100);
    ಪೂರ್ಣಾಂಕ b_refresh_ದರ = (ಪೂರ್ಣಾಂಕ)(b->refresh_ದರ * 100);
    ಪೂರ್ಣಾಂಕ a_pixel_density = (ಪೂರ್ಣಾಂಕ)(a->pixel_density * 100);
    ಪೂರ್ಣಾಂಕ b_pixel_density = (ಪೂರ್ಣಾಂಕ)(b->pixel_density * 100);

    ಆದರೆ (a->w != b->w) {
        ಹಿಂತಿರುಗಿ b->w - a->w;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (a->h != b->h) {
        ಹಿಂತಿರುಗಿ b->h - a->h;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ಹಿಂತಿರುಗಿ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ಹಿಂತಿರುಗಿ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (a_refresh_ದರ != b_refresh_ದರ) {
        ಹಿಂತಿರುಗಿ b_refresh_ದರ - a_refresh_ದರ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (a_pixel_density != b_pixel_density) {
        ಹಿಂತಿರುಗಿ a_pixel_density - b_pixel_density;
    }
    ಹಿಂತಿರುಗಿ 0;
}

bool SDL_UninitializedVideo(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

ಪೂರ್ಣಾಂಕ SDL_Get_ಅಂಕೆ_Video_Drivers(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಅಂಕೆ_drivers = -1;

    ಆದರೆ (ಅಂಕೆ_drivers >= 0) {
        ಹಿಂತಿರುಗಿ ಅಂಕೆ_drivers;
    }

    ಅಂಕೆ_drivers = 0;

    // Build a list of unique video drivers.
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; bootstrap[i] != ಖಾಲಿ; ++i) {
        bool duplicate = false;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < i; ++j) {
            ಆದರೆ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                ನಿಲ್ಲಿಸು;
            }
        }

        ಆದರೆ (!duplicate) {
            deduped_bootstrap[ಅಂಕೆ_drivers++] = bootstrap[i];
        }
    }

    ಹಿಂತಿರುಗಿ ಅಂಕೆ_drivers;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_GetVideoDriver(ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ)
{
    CHECK_PARAM(ಸೂಚ್ಯಂಕ < 0 || ಸೂಚ್ಯಂಕ >= SDL_Get_ಅಂಕೆ_Video_Drivers()) {
        SDL_InvalidParamError("index");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ deduped_bootstrap[ಸೂಚ್ಯಂಕ]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    ಪೂರ್ಣಾಂಕ i = 0;

    // Check to make sure we don't overwrite '_this'
    ಆದರೆ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ಆದರೆ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        ಹೋಗು pre_driver_error;
    }
    init_events = true;
    ಆದರೆ (!SDL_InitKeyboard()) {
        ಹೋಗು pre_driver_error;
    }
    init_keyboard = true;
    ಆದರೆ (!SDL_PreInitMouse()) {
        ಹೋಗು pre_driver_error;
    }
    init_mouse = true;
    ಆದರೆ (!SDL_InitTouch()) {
        ಹೋಗು pre_driver_error;
    }
    init_touch = true;
    ಆದರೆ (!SDL_InitPen()) {
        ಹೋಗು pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ಖಾಲಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ಆದರೆ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ಆದರೆ (driver_name && *driver_name != 0) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *driver_attempt = driver_name;
        ಆಗ (driver_attempt && *driver_attempt != 0 && !video) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *driver_attempt_ಕೊನೆ = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_ಕೊನೆ) ? (driver_attempt_ಕೊನೆ - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            ಗಾಗಿ (i = 0; bootstrap[i]; ++i) {
                ಆದರೆ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ಆದರೆ (video) {
                        ನಿಲ್ಲಿಸು;
                    }
                }
            }

            driver_attempt = (driver_attempt_ಕೊನೆ) ? (driver_attempt_ಕೊನೆ + 1) : ಖಾಲಿ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ಆದರೆ (video) {
                ನಿಲ್ಲಿಸು;
            }
        }
    }
    ಆದರೆ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (driver_name) {
            SDL_ಗಣ_Error("%s not available", driver_name);
            ಹೋಗು pre_driver_error;
        }
        SDL_ಗಣ_Error("No available video device");
        ಹೋಗು pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ಖಾಲಿ;
    SDL_GL_Reset_ಗುಣಲಕ್ಷಣಗಳು();

    // Initialize the video subsystem
    ಆದರೆ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ಹಿಂತಿರುಗಿ false;
    }

    // Make sure some displays were added
    ಆದರೆ (_this->ಅಂಕೆ_displays == 0) {
        SDL_QuitVideo();
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("The video driver did not add any displays");
    }

    SDL_ಕೂಡಿಸು_Hint_Callback(SDL_HINT_VIDEO_SYNC_ಕಿಟಕಿ_OPERATIONS, SDL_SyncHintWatcher, ಖಾಲಿ);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ಆದರೆ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ಹಿಂತಿರುಗಿ true;

pre_driver_error:
    SDL_assert(_this == ಖಾಲಿ);
    ಆದರೆ (init_pen) {
        SDL_QuitPen();
    }
    ಆದರೆ (init_touch) {
        SDL_QuitTouch();
    }
    ಆದರೆ (init_mouse) {
        SDL_QuitMouse();
    }
    ಆದರೆ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ಆದರೆ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_GetCurrentVideoDriver(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ _this;
}

bool SDL_OnVideoThread(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

ಶೂನ್ಯ SDL_ಗಣ_System_Theme(SDL_SystemTheme theme)
{
    ಆದರೆ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_ಬದಲಾಯಿತು_Event();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(ಶೂನ್ಯ)
{
    ಆದರೆ (_this) {
        ಹಿಂತಿರುಗಿ _this->system_theme;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ಶೂನ್ಯ SDL_UpdateDesktopBounds(ಶೂನ್ಯ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ಖಾಲಿ);
    ಆದರೆ (displays) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ಆದರೆ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ಆದರೆ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_Finalize_Display_ಬಹುಲಕ(SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    // Make sure all the fields are set up correctly
    ಆದರೆ (ಬಹುಲಕ->pixel_density <= 0.0f) {
        ಬಹುಲಕ->pixel_density = 1.0f;
    }

    ಆದರೆ (ಬಹುಲಕ->refresh_ದರ_numerator > 0) {
        ಆದರೆ (ಬಹುಲಕ->refresh_ದರ_denominator <= 0) {
            ಬಹುಲಕ->refresh_ದರ_denominator = 1;
        }
        ಬಹುಲಕ->refresh_ದರ = (ದಶಮಾಂಶ)ಬಹುಲಕ->refresh_ದರ_numerator / ಬಹುಲಕ->refresh_ದರ_denominator;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_CalculateFraction(ಬಹುಲಕ->refresh_ದರ, &ಬಹುಲಕ->refresh_ದರ_numerator, &ಬಹುಲಕ->refresh_ದರ_denominator);
    }
    ಬಹುಲಕ->refresh_ದರ = SDL_roundf(ಬಹುಲಕ->refresh_ದರ * 100) / 100.0f;
}

SDL_DisplayID SDL_ಕೂಡಿಸು_Basic_Video_Display(ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *desktop_ಬಹುಲಕ)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ಆದರೆ (desktop_ಬಹುಲಕ) {
        SDL_memcpy(&display.desktop_ಬಹುಲಕ, desktop_ಬಹುಲಕ, ಗಾತ್ರ(display.desktop_ಬಹುಲಕ));
    }
    ಹಿಂತಿರುಗಿ SDL_ಕೂಡಿಸು_Video_Display(&display, false);
}

SDL_DisplayID SDL_ಕೂಡಿಸು_Video_Display(ಸ್ಥಿರಾಂಕ SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    ಪೂರ್ಣಾಂಕ i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(ಗಾತ್ರ(*new_display));
    ಆದರೆ (!new_display) {
        ಹಿಂತಿರುಗಿ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->ಅಂಕೆ_displays + 1) * ಗಾತ್ರ(*displays));
    ಆದರೆ (!displays) {
        SDL_free(new_display);
        ಹಿಂತಿರುಗಿ 0;
    }
    _this->displays = displays;
    _this->displays[_this->ಅಂಕೆ_displays++] = new_display;

    id = SDL_Get_ಮುಂದಿನ_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ಆದರೆ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಅಕ್ಷರ name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ಆದರೆ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_ಬಹುಲಕ.displayID = id;
    new_display->current_ಬಹುಲಕ = &new_display->desktop_ಬಹುಲಕ;
    SDL_Finalize_Display_ಬಹುಲಕ(&new_display->desktop_ಬಹುಲಕ);

    ಗಾಗಿ (i = 0; i < new_display->ಅಂಕೆ_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_ಗಣ_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    ಆದರೆ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ಹಿಂತಿರುಗಿ id;
}

ಶೂನ್ಯ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

    // See if any windows have changed to the new display
    ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        SDL_Check_ಕಿಟಕಿ_Display_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
    }
}

ಶೂನ್ಯ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

ಶೂನ್ಯ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    ಪೂರ್ಣಾಂಕ display_ಸೂಚ್ಯಂಕ = SDL_Get_Display_ಸೂಚ್ಯಂಕ(displayID);
    ಆದರೆ (display_ಸೂಚ್ಯಂಕ < 0) {
        ಹಿಂತಿರುಗಿ;
    }

    display = _this->displays[display_ಸೂಚ್ಯಂಕ];

    ಆದರೆ (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_ಬಹುಲಕ.ಆಂತರಿಕ);
    display->desktop_ಬಹುಲಕ.ಆಂತರಿಕ = ಖಾಲಿ;
    SDL_free(display->ಆಂತರಿಕ);
    display->ಆಂತರಿಕ = ಖಾಲಿ;
    SDL_free(display);

    ಆದರೆ (display_ಸೂಚ್ಯಂಕ < (_this->ಅಂಕೆ_displays - 1)) {
        SDL_memmove(&_this->displays[display_ಸೂಚ್ಯಂಕ], &_this->displays[display_ಸೂಚ್ಯಂಕ + 1], (_this->ಅಂಕೆ_displays - display_ಸೂಚ್ಯಂಕ - 1) * ಗಾತ್ರ(_this->displays[display_ಸೂಚ್ಯಂಕ]));
    }
    --_this->ಅಂಕೆ_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಪೂರ್ಣಾಂಕ i;
    SDL_DisplayID *displays;

    ಆದರೆ (!_this) {
        ಆದರೆ (ಎಣಿಕೆ_2) {
            *ಎಣಿಕೆ_2 = 0;
        }

        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->ಅಂಕೆ_displays + 1) * ಗಾತ್ರ(*displays));
    ಆದರೆ (displays) {
        ಆದರೆ (ಎಣಿಕೆ_2) {
            *ಎಣಿಕೆ_2 = _this->ಅಂಕೆ_displays;
        }

        ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ಎಣಿಕೆ_2) {
            *ಎಣಿಕೆ_2 = 0;
        }
    }
    ಹಿಂತಿರುಗಿ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    ಪೂರ್ಣಾಂಕ display_ಸೂಚ್ಯಂಕ;

    display_ಸೂಚ್ಯಂಕ = SDL_Get_Display_ಸೂಚ್ಯಂಕ(displayID);
    ಆದರೆ (display_ಸೂಚ್ಯಂಕ < 0) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ _this->displays[display_ಸೂಚ್ಯಂಕ];
}

ಸ್ಥಿರ SDL_DisplayID Get_Display_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        displayID = ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.displayID;
    }

    ಆದರೆ (!displayID) {
        displayID = SDL_Get_Display_For_ಕಿಟಕಿ_Position(ಕಿಟಕಿ);
    }
    ಹಿಂತಿರುಗಿ displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0);

    ಹಿಂತಿರುಗಿ SDL_GetVideoDisplay(Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ));
}

SDL_DisplayID SDL_GetPrimaryDisplay(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this || _this->ಅಂಕೆ_displays == 0) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ 0;
    }
    ಹಿಂತಿರುಗಿ _this->displays[0]->id;
}

ಪೂರ್ಣಾಂಕ SDL_Get_Display_ಸೂಚ್ಯಂಕ(SDL_DisplayID displayID)
{
    ಪೂರ್ಣಾಂಕ display_ಸೂಚ್ಯಂಕ;

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ -1;
    }

    ಗಾಗಿ (display_ಸೂಚ್ಯಂಕ = 0; display_ಸೂಚ್ಯಂಕ < _this->ಅಂಕೆ_displays; ++display_ಸೂಚ್ಯಂಕ) {
        ಆದರೆ (displayID == _this->displays[display_ಸೂಚ್ಯಂಕ]->id) {
            ಹಿಂತಿರುಗಿ display_ಸೂಚ್ಯಂಕ;
        }
    }
    SDL_ಗಣ_Error("Invalid display");
    ಹಿಂತಿರುಗಿ -1;
}

SDL_Display_ದತ್ತಾಂಶ *SDL_Get_Display_Driver_ದತ್ತಾಂಶ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ display->ಆಂತರಿಕ;
}

SDL_Display_ದತ್ತಾಂಶ *SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0);

    ಹಿಂತಿರುಗಿ SDL_Get_Display_Driver_ದತ್ತಾಂಶ(Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ಆದರೆ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ಹಿಂತಿರುಗಿ display->props;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("rect");
    }

    ಆದರೆ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ಆದರೆ (_this->GetDisplayBounds(_this, display, rect)) {
            ಹಿಂತಿರುಗಿ true;
        }
    }

    // Assume that the displays are left to right
    ಆದರೆ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_ಸೂಚ್ಯಂಕ(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_ಬಹುಲಕ->w;
    rect->h = display->current_ಬಹುಲಕ->h;
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ಹಿಂತಿರುಗಿ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("rect");
    }

    ಆದರೆ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ಆದರೆ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ಹಿಂತಿರುಗಿ true;
        }
    }

    // Oh well, just give the entire display bounds.
    ಹಿಂತಿರುಗಿ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ಆದರೆ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ಹಿಂತಿರುಗಿ display->natural_orientation;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Default to landscape if the driver hasn't set it
        ಹಿಂತಿರುಗಿ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ಆದರೆ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ಹಿಂತಿರುಗಿ display->current_orientation;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Default to landscape if the driver hasn't set it
        ಹಿಂತಿರುಗಿ SDL_ORIENTATION_LANDSCAPE;
    }
}

ಶೂನ್ಯ SDL_ಗಣ_Display_Content_Scale(SDL_VideoDisplay *display, ದಶಮಾಂಶ scale)
{
    ಆದರೆ (scale != display->content_scale) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_ಬದಲಾಯಿತು, 0, 0);

        // Check the windows on this display
        ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            ಆದರೆ (display->id == ಕಿಟಕಿ->displayID) {
                SDL_Check_ಕಿಟಕಿ_Display_Scale_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
            }
        }
    }
}

ದಶಮಾಂಶ SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ಹಿಂತಿರುಗಿ display->content_scale;
}

ಶೂನ್ಯ SDL_ಗಣ_ಕಿಟಕಿ_HDRProperties(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_HDROutputProperties *HDR, bool send_event)
{
    ಸ್ಥಿರಾಂಕ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ಆದರೆ (ಕಿಟಕಿ->HDR.HDR_headroom != HDR_clamped.HDR_headroom || ಕಿಟಕಿ->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID ಕಿಟಕಿ_props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);

        SDL_ಗಣ_Float_Property(ಕಿಟಕಿ_props, SDL_PROP_ಕಿಟಕಿ_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_ಗಣ_Float_Property(ಕಿಟಕಿ_props, SDL_PROP_ಕಿಟಕಿ_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_ಗಣ_Boolean_Property(ಕಿಟಕಿ_props, SDL_PROP_ಕಿಟಕಿ_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&ಕಿಟಕಿ->HDR, &HDR_clamped);

        ಆದರೆ (send_event) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_HDR_STATE_ಬದಲಾಯಿತು, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

ಶೂನ್ಯ SDL_ಗಣ_Display_HDRProperties(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_HDROutputProperties *HDR)
{
    ಸ್ಥಿರಾಂಕ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ಸ್ಥಿರಾಂಕ bool ಬದಲಾಯಿತು = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	ಆದರೆ (ಬದಲಾಯಿತು) {
		SDL_ಗಣ_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ಆದರೆ (ಬದಲಾಯಿತು && !SDL_DriverSendsHDRChanges(_this)) {
        ಗಾಗಿ (SDL_ಕಿಟಕಿ *w = display->device->windows; w; w = w->ಮುಂದಿನ) {
            ಆದರೆ (Get_Display_For_ಕಿಟಕಿ(w) == display->id) {
                SDL_ಗಣ_ಕಿಟಕಿ_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ಆದರೆ (display->ಅಂಕೆ_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *SDL_Get_Fullscreen_ಬಹುಲಕ_ಹೊಂದಿಕೆ(ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_VideoDisplay *display;
    SDL_Display_ಬಹುಲಕ fullscreen_ಬಹುಲಕ;

    ಆದರೆ (ಬಹುಲಕ->w <= 0 || ಬಹುಲಕ->h <= 0) {
        // Use the desktop mode
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_memcpy(&fullscreen_ಬಹುಲಕ, ಬಹುಲಕ, ಗಾತ್ರ(fullscreen_ಬಹುಲಕ));
    ಆದರೆ (fullscreen_ಬಹುಲಕ.displayID == 0) {
        fullscreen_ಬಹುಲಕ.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_ಬಹುಲಕ(&fullscreen_ಬಹುಲಕ);

    ಬಹುಲಕ = ಖಾಲಿ;

    display = SDL_GetVideoDisplay(fullscreen_ಬಹುಲಕ.displayID);
    ಆದರೆ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ಆದರೆ (!ಬಹುಲಕ) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < display->ಅಂಕೆ_fullscreen_modes; ++i) {
                ಆದರೆ (SDL_memcmp(&fullscreen_ಬಹುಲಕ, &display->fullscreen_modes[i], ಗಾತ್ರ(fullscreen_ಬಹುಲಕ)) == 0) {
                    ಬಹುಲಕ = &display->fullscreen_modes[i];
                    ನಿಲ್ಲಿಸು;
                }
            }
        }

        // Search for a mode with the same characteristics
        ಆದರೆ (!ಬಹುಲಕ) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < display->ಅಂಕೆ_fullscreen_modes; ++i) {
                ಆದರೆ (cmpmodes(&fullscreen_ಬಹುಲಕ, &display->fullscreen_modes[i]) == 0) {
                    ಬಹುಲಕ = &display->fullscreen_modes[i];
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }
    ಹಿಂತಿರುಗಿ ಬಹುಲಕ;
}

bool SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Display_ಬಹುಲಕ *modes;
    SDL_Display_ಬಹುಲಕ new_ಬಹುಲಕ;
    ಪೂರ್ಣಾಂಕ i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_ಬಹುಲಕ, ಬಹುಲಕ, ಗಾತ್ರ(new_ಬಹುಲಕ));
    new_ಬಹುಲಕ.displayID = display->id;
    SDL_Finalize_Display_ಬಹುಲಕ(&new_ಬಹುಲಕ);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->ಅಂಕೆ_fullscreen_modes;
    ಗಾಗಿ (i = 0; i < nmodes; ++i) {
        ಆದರೆ (cmpmodes(&new_ಬಹುಲಕ, &modes[i]) == 0) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    // Go ahead and add the new mode
    ಆದರೆ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_ಬಹುಲಕ *)SDL_malloc((display->max_fullscreen_modes + 32) * ಗಾತ್ರ(*modes));
        ಆದರೆ (!modes) {
            ಹಿಂತಿರುಗಿ false;
        }

        ಆದರೆ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * ಗಾತ್ರ(*modes));
            ಗಾಗಿ (i = 0; i < nmodes; ++i) {
                ಆದರೆ (display->current_ಬಹುಲಕ == &display->fullscreen_modes[i]) {
                    display->current_ಬಹುಲಕ = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->ಅಂಕೆ_fullscreen_modes++], &new_ಬಹುಲಕ, ಗಾತ್ರ(new_ಬಹುಲಕ));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->ಅಂಕೆ_fullscreen_modes,
              ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ), cmpmodes);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = display->ಅಂಕೆ_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].ಆಂತರಿಕ);
        display->fullscreen_modes[i].ಆಂತರಿಕ = ಖಾಲಿ;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ಖಾಲಿ;
    display->ಅಂಕೆ_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_ಬಹುಲಕ = &display->desktop_ಬಹುಲಕ;
}

SDL_Display_ಬಹುಲಕ **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_modes;
    SDL_Display_ಬಹುಲಕ **ಫಲಿತಾಂಶ;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ಆದರೆ (ಎಣಿಕೆ_2) {
        *ಎಣಿಕೆ_2 = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ಖಾಲಿ);

    SDL_UpdateFullscreenDisplayModes(display);

    ಅಂಕೆ_modes = display->ಅಂಕೆ_fullscreen_modes;
    ಫಲಿತಾಂಶ = (SDL_Display_ಬಹುಲಕ **)SDL_malloc((ಅಂಕೆ_modes + 1) * ಗಾತ್ರ(*ಫಲಿತಾಂಶ) + ಅಂಕೆ_modes * ಗಾತ್ರ(**ಫಲಿತಾಂಶ));
    ಆದರೆ (ಫಲಿತಾಂಶ) {
        SDL_Display_ಬಹುಲಕ *modes = (SDL_Display_ಬಹುಲಕ *)((Uint8 *)ಫಲಿತಾಂಶ + ((ಅಂಕೆ_modes + 1) * ಗಾತ್ರ(*ಫಲಿತಾಂಶ)));
        ಆದರೆ (ಅಂಕೆ_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, ಅಂಕೆ_modes * ಗಾತ್ರ(*modes));
        }
        ಗಾಗಿ (i = 0; i < ಅಂಕೆ_modes; ++i) {
            ಫಲಿತಾಂಶ[i] = modes++;
        }
        ಫಲಿತಾಂಶ[i] = ಖಾಲಿ;

        ಆದರೆ (ಎಣಿಕೆ_2) {
            *ಎಣಿಕೆ_2 = ಅಂಕೆ_modes;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ಎಣಿಕೆ_2) {
            *ಎಣಿಕೆ_2 = 0;
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_Get_Closest_Fullscreen_Display_ಬಹುಲಕ(SDL_DisplayID displayID, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ದಶಮಾಂಶ refresh_ದರ, bool include_ಮೇಲಿನ_density_modes, SDL_Display_ಬಹುಲಕ *ಫಲಿತಾಂಶ)
{
    CHECK_PARAM(!ಫಲಿತಾಂಶ) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ, *closest = ಖಾಲಿ;
    ದಶಮಾಂಶ aspect_ಅನುಪಾತ;
    ಪೂರ್ಣಾಂಕ i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(ಫಲಿತಾಂಶ);

    CHECK_DISPLAY_MAGIC(display, false);

    ಆದರೆ (h > 0) {
        aspect_ಅನುಪಾತ = (ದಶಮಾಂಶ)w / h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        aspect_ಅನುಪಾತ = 1.0f;
    }

    ಆದರೆ (refresh_ದರ == 0.0f) {
        refresh_ದರ = display->desktop_ಬಹುಲಕ.refresh_ದರ;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    ಗಾಗಿ (i = 0; i < display->ಅಂಕೆ_fullscreen_modes; ++i) {
        ಬಹುಲಕ = &display->fullscreen_modes[i];

        ಆದರೆ (w > ಬಹುಲಕ->w) {
            // Out of sorted modes large enough here
            ನಿಲ್ಲಿಸು;
        }
        ಆದರೆ (h > ಬಹುಲಕ->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (ಬಹುಲಕ->pixel_density > 1.0f && !include_ಮೇಲಿನ_density_modes) {
            ಮುಂದುವರಿ;
        }
        ಆದರೆ (closest) {
            ದಶಮಾಂಶ current_aspect_ಅನುಪಾತ = (ದಶಮಾಂಶ)ಬಹುಲಕ->w / ಬಹುಲಕ->h;
            ದಶಮಾಂಶ closest_aspect_ಅನುಪಾತ = (ದಶಮಾಂಶ)closest->w / closest->h;
            ಆದರೆ (SDL_fabsf(aspect_ಅನುಪಾತ - closest_aspect_ಅನುಪಾತ) < SDL_fabsf(aspect_ಅನುಪಾತ - current_aspect_ಅನುಪಾತ)) {
                // The mode we already found has a better aspect ratio match
                ಮುಂದುವರಿ;
            }

            ಆದರೆ (ಬಹುಲಕ->w == closest->w && ಬಹುಲಕ->h == closest->h) {
                ಆದರೆ (SDL_fabsf(closest->refresh_ದರ - refresh_ದರ) < SDL_fabsf(ಬಹುಲಕ->refresh_ದರ - refresh_ದರ)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    ಮುಂದುವರಿ;
                }
                ಆದರೆ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(ಬಹುಲಕ->format)) {
                    // Prefer the highest color depth
                    ಮುಂದುವರಿ;
                }
            }
        }

        closest = ಬಹುಲಕ;
    }
    ಆದರೆ (!closest) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(ಫಲಿತಾಂಶ, closest);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool Display_ಬಹುಲಕ_ಬದಲಾಯಿತು(ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *old_ಬಹುಲಕ, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *new_ಬಹುಲಕ)
{
    ಹಿಂತಿರುಗಿ ((old_ಬಹುಲಕ->displayID && old_ಬಹುಲಕ->displayID != new_ಬಹುಲಕ->displayID) ||
            (old_ಬಹುಲಕ->format && old_ಬಹುಲಕ->format != new_ಬಹುಲಕ->format) ||
            (old_ಬಹುಲಕ->w && old_ಬಹುಲಕ->h && (old_ಬಹುಲಕ->w != new_ಬಹುಲಕ->w ||old_ಬಹುಲಕ->h != new_ಬಹುಲಕ->h)) ||
            (old_ಬಹುಲಕ->pixel_density != 0.0f && old_ಬಹುಲಕ->pixel_density != new_ಬಹುಲಕ->pixel_density) ||
            (old_ಬಹುಲಕ->refresh_ದರ != 0.0f && old_ಬಹುಲಕ->refresh_ದರ != new_ಬಹುಲಕ->refresh_ದರ));
}

ಶೂನ್ಯ SDL_ಗಣ_Desktop_Display_ಬಹುಲಕ(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Display_ಬಹುಲಕ ಕೊನೆಯ_ಬಹುಲಕ;

    ಆದರೆ (display->fullscreen_ಸಕ್ರಿಯ) {
        // This is a temporary mode change, don't save the desktop mode
        ಹಿಂತಿರುಗಿ;
    }

    SDL_copyp(&ಕೊನೆಯ_ಬಹುಲಕ, &display->desktop_ಬಹುಲಕ);

    SDL_free(display->desktop_ಬಹುಲಕ.ಆಂತರಿಕ);
    SDL_copyp(&display->desktop_ಬಹುಲಕ, ಬಹುಲಕ);
    display->desktop_ಬಹುಲಕ.displayID = display->id;
    SDL_Finalize_Display_ಬಹುಲಕ(&display->desktop_ಬಹುಲಕ);

    ಆದರೆ (Display_ಬಹುಲಕ_ಬದಲಾಯಿತು(&ಕೊನೆಯ_ಬಹುಲಕ, &display->desktop_ಬಹುಲಕ)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_ಬಹುಲಕ_ಬದಲಾಯಿತು, ಬಹುಲಕ->w, ಬಹುಲಕ->h);
        ಆದರೆ (display->current_ಬಹುಲಕ == &display->desktop_ಬಹುಲಕ) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_ಬಹುಲಕ_ಬದಲಾಯಿತು, ಬಹುಲಕ->w, ಬಹುಲಕ->h);
        }
    }
}

ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *SDL_Get_Desktop_Display_ಬಹುಲಕ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ &display->desktop_ಬಹುಲಕ;
}

ಶೂನ್ಯ SDL_ಗಣ_Current_Display_ಬಹುಲಕ(SDL_VideoDisplay *display, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Display_ಬಹುಲಕ ಕೊನೆಯ_ಬಹುಲಕ;

    ಆದರೆ (display->current_ಬಹುಲಕ) {
        SDL_copyp(&ಕೊನೆಯ_ಬಹುಲಕ, display->current_ಬಹುಲಕ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_zero(ಕೊನೆಯ_ಬಹುಲಕ);
    }

    display->current_ಬಹುಲಕ = ಬಹುಲಕ;

    ಆದರೆ (Display_ಬಹುಲಕ_ಬದಲಾಯಿತು(&ಕೊನೆಯ_ಬಹುಲಕ, ಬಹುಲಕ)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_ಬಹುಲಕ_ಬದಲಾಯಿತು, ಬಹುಲಕ->w, ಬಹುಲಕ->h);
    }
}

ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *SDL_Get_Current_Display_ಬಹುಲಕ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ display->current_ಬಹುಲಕ;
}

bool SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ಆದರೆ (SDL_ಬಹುಲಕ_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!ಬಹುಲಕ) {
        ಬಹುಲಕ = &display->desktop_ಬಹುಲಕ;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_PLATFORM_RISCOS
    ಆದರೆ (ಬಹುಲಕ == display->current_ಬಹುಲಕ) {
        ಹಿಂತಿರುಗಿ true;
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Actually change the display mode
    ಆದರೆ (_this->ಗಣ_Display_ಬಹುಲಕ) {
        bool ಫಲಿತಾಂಶ;

        _this->setting_display_ಬಹುಲಕ = true;
        ಫಲಿತಾಂಶ = _this->ಗಣ_Display_ಬಹುಲಕ(_this, display, ಬಹುಲಕ);
        _this->setting_display_ಬಹುಲಕ = false;
        ಆದರೆ (!ಫಲಿತಾಂಶ) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    SDL_ಗಣ_Current_Display_ಬಹುಲಕ(display, ಬಹುಲಕ);

    ಹಿಂತಿರುಗಿ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ಸ್ಥಿರ ಶೂನ್ಯ SDL_Get_Closest_ಬಿಂದು_On_Rect(ಸ್ಥಿರಾಂಕ SDL_Rect *rect, SDL_ಬಿಂದು *ಬಿಂದು)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಬಲ = rect->x + rect->w - 1;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ bottom = rect->y + rect->h - 1;

    ಆದರೆ (ಬಿಂದು->x < rect->x) {
        ಬಿಂದು->x = rect->x;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಬಿಂದು->x > ಬಲ) {
        ಬಿಂದು->x = ಬಲ;
    }

    ಆದರೆ (ಬಿಂದು->y < rect->y) {
        ಬಿಂದು->y = rect->y;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಬಿಂದು->y > bottom) {
        ಬಿಂದು->y = bottom;
    }
}

ಸ್ಥಿರ SDL_DisplayID GetDisplayForRect(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    ಪೂರ್ಣಾಂಕ i, dist;
    SDL_DisplayID closest = 0;
    ಪೂರ್ಣಾಂಕ closest_dist = 0x7FFFFFFF;
    SDL_ಬಿಂದು closest_ಬಿಂದು_on_display;
    SDL_ಬಿಂದು delta;
    SDL_ಬಿಂದು center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    ಆದರೆ (_this) {
        ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ಆದರೆ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ಖಾಲಿ)) {
                ಹಿಂತಿರುಗಿ display->id;
            }

            // Snap window center to the display rect
            closest_ಬಿಂದು_on_display = center;
            SDL_Get_Closest_ಬಿಂದು_On_Rect(&display_rect, &closest_ಬಿಂದು_on_display);

            delta.x = center.x - closest_ಬಿಂದು_on_display.x;
            delta.y = center.y - closest_ಬಿಂದು_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ಆದರೆ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ಆದರೆ (closest == 0) {
        SDL_ಗಣ_Error("Couldn't find any displays");
    }

    ಹಿಂತಿರುಗಿ closest;
}

ಶೂನ್ಯ SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ rel_x, ಪೂರ್ಣಾಂಕ rel_y, ಪೂರ್ಣಾಂಕ *abs_x, ಪೂರ್ಣಾಂಕ *abs_y)
{
    SDL_ಕಿಟಕಿ *w;

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        // Calculate the total offset of the popup from the parents
        ಗಾಗಿ (w = ಕಿಟಕಿ->ಪೋಷಕ; w; w = w->ಪೋಷಕ) {
            rel_x += w->x;
            rel_y += w->y;

            ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(w)) {
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಆದರೆ (abs_x) {
        *abs_x = rel_x;
    }
    ಆದರೆ (abs_y) {
        *abs_y = rel_y;
    }
}

ಶೂನ್ಯ SDL_Global_ಗಮ್ಯ_Relative_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ abs_x, ಪೂರ್ಣಾಂಕ abs_y, ಪೂರ್ಣಾಂಕ *rel_x, ಪೂರ್ಣಾಂಕ *rel_y)
{
    SDL_ಕಿಟಕಿ *w;

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        // Convert absolute window coordinates to relative for a popup
        ಗಾಗಿ (w = ಕಿಟಕಿ->ಪೋಷಕ; w; w = w->ಪೋಷಕ) {
            abs_x -= w->x;
            abs_y -= w->y;

            ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(w)) {
                ನಿಲ್ಲಿಸು;
            }
        }
    }

    ಆದರೆ (rel_x) {
        *rel_x = abs_x;
    }
    ಆದರೆ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_Get_Display_For_ಬಿಂದು(ಸ್ಥಿರಾಂಕ SDL_ಬಿಂದು *ಬಿಂದು)
{
    CHECK_PARAM(!ಬಿಂದು) {
        SDL_InvalidParamError("point");
        ಹಿಂತಿರುಗಿ 0;
    }

    ಹಿಂತಿರುಗಿ GetDisplayForRect(ಬಿಂದು->x, ಬಿಂದು->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ಸ್ಥಿರಾಂಕ SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ಹಿಂತಿರುಗಿ 0;
    }

    ಹಿಂತಿರುಗಿ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ಸ್ಥಿರ SDL_DisplayID GetDisplayAtOrigin(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_Rect rect;
        ಸ್ಥಿರಾಂಕ SDL_DisplayID cur_id = _this->displays[i]->id;
        ಆದರೆ (SDL_GetDisplayBounds(cur_id, &rect)) {
            ಆದರೆ (x == rect.x && y == rect.y) {
                ಹಿಂತಿರುಗಿ cur_id;
            }
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

SDL_DisplayID SDL_Get_Display_For_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಪೂರ್ಣಾಂಕ x, y;
    SDL_DisplayID displayID = 0;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0);

    ಆದರೆ (_this->Get_Display_For_ಕಿಟಕಿ) {
        displayID = _this->Get_Display_For_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_ಗಮ್ಯ_Global_For_ಕಿಟಕಿ(ಕಿಟಕಿ, ಕಿಟಕಿ->x, ಕಿಟಕಿ->y, &x, &y);

    ಆದರೆ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ಇಲ್ಲದಿದ್ದರೆ {
            displayID = GetDisplayForRect(x, y, ಕಿಟಕಿ->w, ಕಿಟಕಿ->h);
        }
    }
    ಆದರೆ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ಹಿಂತಿರುಗಿ displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_DisplayID displayID = 0;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಖಾಲಿ);

    // An explicit fullscreen display overrides all
    ಆದರೆ (ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.displayID) {
        displayID = ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ಆದರೆ (!displayID) {
        displayID = ಕಿಟಕಿ->pending_displayID;
    }
    ಆದರೆ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ x = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.x : ಕಿಟಕಿ->x;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ y = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.y : ಕಿಟಕಿ->y;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ w = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ಕಿಟಕಿ->w;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ h = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ಕಿಟಕಿ->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ಆದರೆ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ಆದರೆ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ಹಿಂತಿರುಗಿ SDL_GetVideoDisplay(displayID);
}

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_PROP_SDL2_COMPAT_ಕಿಟಕಿ_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID ಕಿಟಕಿ_props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಆದರೆ (fs_display) {
        SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(ಕಿಟಕಿ_props, SDL_PROP_SDL2_COMPAT_ಕಿಟಕಿ_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ClearProperty(ಕಿಟಕಿ_props, SDL_PROP_SDL2_COMPAT_ಕಿಟಕಿ_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ಹಿಂತಿರುಗಿ Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_Display_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (SDL_SendsDisplayChanges(_this)) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_ಕಿಟಕಿ_Position(ಕಿಟಕಿ);

    ಆದರೆ (displayID != ಕಿಟಕಿ->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect ಕಿಟಕಿ_rect;
        SDL_Rect old_overlap, new_overlap;

        ಆದರೆ (SDL_GetDisplayBounds(ಕಿಟಕಿ->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            ಕಿಟಕಿ_rect.x = ಕಿಟಕಿ->x;
            ಕಿಟಕಿ_rect.y = ಕಿಟಕಿ->y;
            ಕಿಟಕಿ_rect.w = ಕಿಟಕಿ->w;
            ಕಿಟಕಿ_rect.h = ಕಿಟಕಿ->h;

            ಆದರೆ (SDL_GetRectIntersection(&old_bounds, &ಕಿಟಕಿ_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &ಕಿಟಕಿ_rect, &new_overlap)) {
                ಪೂರ್ಣಾಂಕ old_area = old_overlap.w * old_overlap.h;
                ಪೂರ್ಣಾಂಕ new_area = new_overlap.w * new_overlap.h;
                ದಶಮಾಂಶ new_overlap_ಅನುಪಾತ = (new_area / ((ದಶಮಾಂಶ)old_area + new_area));
                ಆದರೆ (new_overlap_ಅನುಪಾತ < 0.80) {
                    ಹಿಂತಿರುಗಿ;
                }
            }
        }
    }

    ಆದರೆ (displayID != ಕಿಟಕಿ->displayID) {
        ಪೂರ್ಣಾಂಕ i, display_ಸೂಚ್ಯಂಕ;

        // Sanity check our fullscreen windows
        display_ಸೂಚ್ಯಂಕ = SDL_Get_Display_ಸೂಚ್ಯಂಕ(displayID);
        ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ಆದರೆ (display->fullscreen_ಕಿಟಕಿ == ಕಿಟಕಿ) {
                ಆದರೆ (display_ಸೂಚ್ಯಂಕ != i) {
                    ಆದರೆ (display_ಸೂಚ್ಯಂಕ < 0) {
                        display_ಸೂಚ್ಯಂಕ = i;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        SDL_VideoDisplay *new_display = _this->displays[display_ಸೂಚ್ಯಂಕ];

                        // The window was moved to a different display
                        ಆದರೆ (new_display->fullscreen_ಕಿಟಕಿ &&
                            new_display->fullscreen_ಕಿಟಕಿ != ಕಿಟಕಿ) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_ಕಿಟಕಿ(new_display->fullscreen_ಕಿಟಕಿ);
                        }
                        new_display->fullscreen_ಕಿಟಕಿ = ಕಿಟಕಿ;
                        display->fullscreen_ಕಿಟಕಿ = ಖಾಲಿ;
                    }
                }
                ನಿಲ್ಲಿಸು;
            }
        }

        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_DISPLAY_ಬದಲಾಯಿತು, (ಪೂರ್ಣಾಂಕ)displayID, 0);
    }
}

ದಶಮಾಂಶ SDL_Get_ಕಿಟಕಿ_Pixel_Density(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_w, ಕಿಟಕಿ_h, pixel_w, pixel_h;
    ದಶಮಾಂಶ pixel_density = 1.0f;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0.0f);

    ಆದರೆ (SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ(ಕಿಟಕಿ, &ಕಿಟಕಿ_w, &ಕಿಟಕಿ_h) &&
        SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &pixel_w, &pixel_h)) {
        pixel_density = (ದಶಮಾಂಶ)pixel_w / ಕಿಟಕಿ_w;
    }
    ಹಿಂತಿರುಗಿ pixel_density;
}

ದಶಮಾಂಶ SDL_Get_ಕಿಟಕಿ_Display_Scale(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0.0f);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->display_scale;
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_Display_Scale_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ದಶಮಾಂಶ display_scale;

    ಆದರೆ (_this->Get_ಕಿಟಕಿ_Content_Scale) {
        display_scale = _this->Get_ಕಿಟಕಿ_Content_Scale(_this, ಕಿಟಕಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ pixel_density = SDL_Get_ಕಿಟಕಿ_Pixel_Density(ಕಿಟಕಿ);
        ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ content_scale = SDL_GetDisplayContentScale(ಕಿಟಕಿ->displayID);

        display_scale = pixel_density * content_scale;
    }

    ಆದರೆ (display_scale != ಕಿಟಕಿ->display_scale) {
        ಕಿಟಕಿ->display_scale = display_scale;
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_DISPLAY_SCALE_ಬದಲಾಯಿತು, 0, 0);
    }
}

bool SDL_Update_Fullscreen_ಬಹುಲಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ಖಾಲಿ;
    SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ i;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಕಿಟಕಿ->fullscreen_exclusive = false;
    ಕಿಟಕಿ->update_fullscreen_on_display_ಬದಲಾಯಿತು = false;

    // If we are in the process of hiding don't go back to fullscreen
    ಆದರೆ (ಕಿಟಕಿ->is_destroying || ಕಿಟಕಿ->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ಆದರೆ (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_ಕಿಟಕಿ(ಕಿಟಕಿ);
        ಆದರೆ (!display) {
            // This should never happen, but it did...
            ಹೋಗು ಮುಗಿದ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            display = _this->displays[i];
            ಆದರೆ (display->fullscreen_ಕಿಟಕಿ == ಕಿಟಕಿ) {
                ನಿಲ್ಲಿಸು;
            }
        }
        ಆದರೆ (!display || i == _this->ಅಂಕೆ_displays) {
            // Already not fullscreen on any display
            display = ಖಾಲಿ;
        }
    }

    ಆದರೆ (fullscreen) {
        ಬಹುಲಕ = (SDL_Display_ಬಹುಲಕ *)SDL_Get_ಕಿಟಕಿ_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ);
        ಆದರೆ (ಬಹುಲಕ) {
            ಕಿಟಕಿ->fullscreen_exclusive = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ);
        }
    }

#ಆದರೆ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ಆದರೆ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ಆದರೆ (ಕಿಟಕಿ->is_destroying && !ಕಿಟಕಿ->ಕೊನೆಯ_fullscreen_exclusive_display) {
            ಕಿಟಕಿ->fullscreen_exclusive = false;
            ಆದರೆ (display) {
                display->fullscreen_ಕಿಟಕಿ = ಖಾಲಿ;
            }
            ಹೋಗು ಮುಗಿದ;
        }
        ಆದರೆ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ಆದರೆ (fullscreen && Cocoa_Is_ಕಿಟಕಿ_ಒಳ_Fullscreen_Space(ಕಿಟಕಿ) && !ಕಿಟಕಿ->ಕೊನೆಯ_fullscreen_exclusive_display && ಕಿಟಕಿ->fullscreen_exclusive) {
                ಆದರೆ (!Cocoa_ಗಣ_ಕಿಟಕಿ_Fullscreen_Space(ಕಿಟಕಿ, false, true)) {
                    ಹೋಗು error;
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fullscreen && ಕಿಟಕಿ->ಕೊನೆಯ_fullscreen_exclusive_display && !ಕಿಟಕಿ->fullscreen_exclusive) {
                ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                    SDL_VideoDisplay *ಕೊನೆಯ_display = _this->displays[i];
                    ಆದರೆ (ಕೊನೆಯ_display->fullscreen_ಕಿಟಕಿ == ಕಿಟಕಿ) {
                        SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(ಕೊನೆಯ_display, ಖಾಲಿ);
                        ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Fullscreen) {
                            _this->ಗಣ_ಕಿಟಕಿ_Fullscreen(_this, ಕಿಟಕಿ, ಕೊನೆಯ_display, false);
                        }
                        ಕೊನೆಯ_display->fullscreen_ಕಿಟಕಿ = ಖಾಲಿ;
                    }
                }
            }

            ಆದರೆ (Cocoa_ಗಣ_ಕಿಟಕಿ_Fullscreen_Space(ಕಿಟಕಿ, !!fullscreen, syncHint)) {
                ಹೋಗು ಮುಗಿದ;
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (display) {
        // Restore the video mode on other displays if needed
        ಗಾಗಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ಆದರೆ (other != display && other->fullscreen_ಕಿಟಕಿ == ಕಿಟಕಿ) {
                SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(other, ಖಾಲಿ);
                other->fullscreen_ಕಿಟಕಿ = ಖಾಲಿ;
            }
        }
    }

    ಆದರೆ (fullscreen) {
        ಪೂರ್ಣಾಂಕ ಬಹುಲಕ_w = 0, ಬಹುಲಕ_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ಆದರೆ (display->fullscreen_ಕಿಟಕಿ &&
            display->fullscreen_ಕಿಟಕಿ != ಕಿಟಕಿ) {
            SDL_Minimize_ಕಿಟಕಿ(display->fullscreen_ಕಿಟಕಿ);
        }

        display->fullscreen_ಸಕ್ರಿಯ = ಕಿಟಕಿ->fullscreen_exclusive;

        ಆದರೆ (!SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(display, ಬಹುಲಕ)) {
            ಹೋಗು error;
        }
        ಆದರೆ (commit) {
            SDL_Fullscreen_ಫಲಿತಾಂಶ ret = SDL_FULLSCREEN_SUCCEEDED;
            ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Fullscreen) {
                ret = _this->ಗಣ_ಕಿಟಕಿ_Fullscreen(_this, ಕಿಟಕಿ, display, fullscreen);
            } ಇಲ್ಲದಿದ್ದರೆ {
                resized = true;
            }

            ಆದರೆ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
                    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ENTER_FULLSCREEN, 0, 0);
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_ಸಕ್ರಿಯ = false;
                ಹೋಗು error;
            }
        }

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
            display->fullscreen_ಕಿಟಕಿ = ಕಿಟಕಿ;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ಆದರೆ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ಆದರೆ (ಬಹುಲಕ) {
                    ಬಹುಲಕ_w = ಬಹುಲಕ->w;
                    ಬಹುಲಕ_h = ಬಹುಲಕ->h;
                    SDL_GetDisplayBounds(ಬಹುಲಕ->displayID, &displayRect);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಬಹುಲಕ_w = display->desktop_ಬಹುಲಕ.w;
                    ಬಹುಲಕ_h = display->desktop_ಬಹುಲಕ.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ಆದರೆ (ಕಿಟಕಿ->w != ಬಹುಲಕ_w || ಕಿಟಕಿ->h != ಬಹುಲಕ_h) {
                    resized = true;
                }

                SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, displayRect.x, displayRect.y);

                ಆದರೆ (resized) {
                    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಬಹುಲಕ_w, ಬಹುಲಕ_h);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    SDL_On_ಕಿಟಕಿ_Resized(ಕಿಟಕಿ);
                }
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        bool resized = false;

        // Restore the desktop mode
        ಆದರೆ (display) {
            display->fullscreen_ಸಕ್ರಿಯ = false;

            SDL_ಗಣ_Display_ಬಹುಲಕ_For_Display(display, ಖಾಲಿ);
        }
        ಆದರೆ (commit) {
            SDL_Fullscreen_ಫಲಿತಾಂಶ ret = SDL_FULLSCREEN_SUCCEEDED;
            ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Fullscreen) {
                SDL_VideoDisplay *ತುಂಬಿದ_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_ಕಿಟಕಿ(ಕಿಟಕಿ);
                ಆದರೆ (ತುಂಬಿದ_screen_display) {
                    ret = _this->ಗಣ_ಕಿಟಕಿ_Fullscreen(_this, ಕಿಟಕಿ, ತುಂಬಿದ_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                resized = true;
            }

            ಆದರೆ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
                    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_LEAVE_FULLSCREEN, 0, 0);
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret == SDL_FULLSCREEN_FAILED) {
                ಹೋಗು error;
            }
        }

        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
            ಆದರೆ (display) {
                display->fullscreen_ಕಿಟಕಿ = ಖಾಲಿ;
            }

            ಆದರೆ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, ಕಿಟಕಿ->windowed.x, ಕಿಟಕಿ->windowed.y);
                ಆದರೆ (resized) {
                    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಕಿಟಕಿ->windowed.w, ಕಿಟಕಿ->windowed.h);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    SDL_On_ಕಿಟಕಿ_Resized(ಕಿಟಕಿ);
                }
            }
        }
    }

ಮುಗಿದ:
    ಕಿಟಕಿ->ಕೊನೆಯ_fullscreen_exclusive_display = display && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && ಕಿಟಕಿ->fullscreen_exclusive ? display->id : 0;
    ಹಿಂತಿರುಗಿ true;

error:
    ಆದರೆ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ಹಿಂತಿರುಗಿ false;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Fullscreen_ಬಹುಲಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (ಬಹುಲಕ) {
        ಆದರೆ (!SDL_Get_Fullscreen_ಬಹುಲಕ_ಹೊಂದಿಕೆ(ಬಹುಲಕ)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ, ಬಹುಲಕ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_zero(ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ, &ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ);

#ಆದರೆ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ಆದರೆ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_ಕಿಟಕಿ_ಒಳ_Fullscreen_Space_Transition(ಕಿಟಕಿ)) {
        SDL_Sync_ಕಿಟಕಿ(ಕಿಟಕಿ);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (SDL_ಕಿಟಕಿ_FULLSCREEN_VISIBLE(ಕಿಟಕಿ)) {
        SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(ಕಿಟಕಿ);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *SDL_Get_ಕಿಟಕಿ_Fullscreen_ಬಹುಲಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಖಾಲಿ);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, ಖಾಲಿ);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        ಹಿಂತಿರುಗಿ SDL_Get_Fullscreen_ಬಹುಲಕ_ಹೊಂದಿಕೆ(&ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Get_Fullscreen_ಬಹುಲಕ_ಹೊಂದಿಕೆ(&ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ);
    }
}

ಶೂನ್ಯ *SDL_Get_ಕಿಟಕಿ_ICCProfile(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2)
{
    ಆದರೆ (!_this->Get_ಕಿಟಕಿ_ICCProfile) {
        SDL_Unsupported();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ _this->Get_ಕಿಟಕಿ_ICCProfile(_this, ಕಿಟಕಿ, ಗಾತ್ರ_2);
}

SDL_PixelFormat SDL_Get_ಕಿಟಕಿ_Pixel_Format(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_DisplayID displayID;
    ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಬಹುಲಕ = SDL_Get_Current_Display_ಬಹುಲಕ(displayID);
    ಆದರೆ (ಬಹುಲಕ) {
        ಹಿಂತಿರುಗಿ ಬಹುಲಕ->format;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#ವ್ಯಾಖ್ಯಾನಿಸು CREATE_FLAGS \
    (SDL_ಕಿಟಕಿ_OPENGL | SDL_ಕಿಟಕಿ_BORDERLESS | SDL_ಕಿಟಕಿ_RESIZABLE | SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY | SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ | SDL_ಕಿಟಕಿ_POPUP_MENU | SDL_ಕಿಟಕಿ_UTILITY | SDL_ಕಿಟಕಿ_TOOLTIP | SDL_ಕಿಟಕಿ_VULKAN | SDL_ಕಿಟಕಿ_MINIMIZED | SDL_ಕಿಟಕಿ_METAL | SDL_ಕಿಟಕಿ_TRANSPARENT | SDL_ಕಿಟಕಿ_NOT_FOCUSABLE | SDL_ಕಿಟಕಿ_FILL_DOCUMENT)

ಸ್ಥಿರ SDL_INLINE bool IsAcceptingDragAndDrop(ಶೂನ್ಯ)
{
    ಆದರೆ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_ಪಠ್ಯ)) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

// prepare a newly-created window
ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ PrepareDragAndDropSupport(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(ಕಿಟಕಿ, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
ಶೂನ್ಯ SDL_ToggleDragAndDropSupport(ಶೂನ್ಯ)
{
    ಆದರೆ (_this && _this->AcceptDragAndDrop) {
        ಸ್ಥಿರಾಂಕ bool enable = IsAcceptingDragAndDrop();
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
        ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            _this->AcceptDragAndDrop(ಕಿಟಕಿ, enable);
        }
    }
}

SDL_ಕಿಟಕಿ ** SDLCALL SDL_GetWindows(ಪೂರ್ಣಾಂಕ *ಎಣಿಕೆ_2)
{
    ಆದರೆ (ಎಣಿಕೆ_2) {
        *ಎಣಿಕೆ_2 = 0;
    }

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_added = 0;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_windows = 0;
    ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        ++ಅಂಕೆ_windows;
    }

    SDL_ಕಿಟಕಿ **windows = (SDL_ಕಿಟಕಿ **)SDL_malloc((ಅಂಕೆ_windows + 1) * ಗಾತ್ರ(*windows));
    ಆದರೆ (!windows) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
        windows[ಅಂಕೆ_added++] = ಕಿಟಕಿ;
        ಆದರೆ (ಅಂಕೆ_added == ಅಂಕೆ_windows) {
            // Race condition? Multi-threading not supported, ignore it
            ನಿಲ್ಲಿಸು;
        }
    }
    windows[ಅಂಕೆ_added] = ಖಾಲಿ;

    ಆದರೆ (ಎಣಿಕೆ_2) {
        *ಎಣಿಕೆ_2 = ಅಂಕೆ_added;
    }
    ಹಿಂತಿರುಗಿ windows;
}

ಸ್ಥಿರ ಶೂನ್ಯ Apply_ಕಿಟಕಿ_Flags(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags)
{
    ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        ಆದರೆ (!(flags & (SDL_ಕಿಟಕಿ_MINIMIZED | SDL_ಕಿಟಕಿ_MAXIMIZED))) {
            SDL_Restore_ಕಿಟಕಿ(ಕಿಟಕಿ);
        }
        ಆದರೆ (flags & SDL_ಕಿಟಕಿ_MAXIMIZED) {
            SDL_Maximize_ಕಿಟಕಿ(ಕಿಟಕಿ);
        }

        SDL_ಗಣ_ಕಿಟಕಿ_Fullscreen(ಕಿಟಕಿ, (flags & SDL_ಕಿಟಕಿ_FULLSCREEN) != 0);

        ಆದರೆ (flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
            SDL_Minimize_ಕಿಟಕಿ(ಕಿಟಕಿ);
        }

        ಆದರೆ (flags & SDL_ಕಿಟಕಿ_MODAL) {
            SDL_ಗಣ_ಕಿಟಕಿ_Modal(ಕಿಟಕಿ, true);
        }

        ಆದರೆ (flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED) {
            SDL_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(ಕಿಟಕಿ, true);
        }
        ಆದರೆ (flags & SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED) {
            SDL_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(ಕಿಟಕಿ, true);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_ಮುಕ್ತಾಯ_ಕಿಟಕಿ_Creation(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags)
{
    PrepareDragAndDropSupport(ಕಿಟಕಿ);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ಇಲ್ಲದಿದ್ದರೆ {
        Apply_ಕಿಟಕಿ_Flags(ಕಿಟಕಿ, flags);
        ಆದರೆ (!(flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
            SDL_Show_ಕಿಟಕಿ(ಕಿಟಕಿ);
        }
    }

#ಆದರೆ defined(SDL_PLATFORM_LINUX)
    ಆದರೆ (!SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_ಗಣ_ಕಿಟಕಿ_ಪ್ರಗತಿ_State(ಕಿಟಕಿ, SDL_ಪ್ರಗತಿ_STATE_NONE);
        SDL_ಗಣ_ಕಿಟಕಿ_ಪ್ರಗತಿ_ಮೌಲ್ಯ(ಕಿಟಕಿ, 0.0f);
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ bool SDL_ContextNotSupported(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ಸ್ಥಿರ bool SDL_DllNotSupported(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ಸ್ಥಿರ ರಚನೆ {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *property_name;
    SDL_ಕಿಟಕಿ_Flags flag;
    bool invert_ಮೌಲ್ಯ;
} SDL_ಕಿಟಕಿ_Flag_Properties[] = {
    { SDL_PROP_ಕಿಟಕಿ_CREATE_ALWAYS_ON_ತುದಿ_BOOLEAN,      SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ,       false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_BORDERLESS_BOOLEAN,         SDL_ಕಿಟಕಿ_BORDERLESS,          false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_FOCUSABLE_BOOLEAN,          SDL_ಕಿಟಕಿ_NOT_FOCUSABLE,       true },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_FULLSCREEN_BOOLEAN,         SDL_ಕಿಟಕಿ_FULLSCREEN,          false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_HIDDEN_BOOLEAN,             SDL_ಕಿಟಕಿ_HIDDEN,              false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_ಮೇಲಿನ_PIXEL_DENSITY_BOOLEAN, SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY,  false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_MAXIMIZED_BOOLEAN,          SDL_ಕಿಟಕಿ_MAXIMIZED,           false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_MENU_BOOLEAN,               SDL_ಕಿಟಕಿ_POPUP_MENU,          false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_METAL_BOOLEAN,              SDL_ಕಿಟಕಿ_METAL,               false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_MINIMIZED_BOOLEAN,          SDL_ಕಿಟಕಿ_MINIMIZED,           false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_MODAL_BOOLEAN,              SDL_ಕಿಟಕಿ_MODAL,               false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_ಕಿಟಕಿ_MOUSE_GRABBED,       false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_OPENGL_BOOLEAN,             SDL_ಕಿಟಕಿ_OPENGL,              false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_RESIZABLE_BOOLEAN,          SDL_ಕಿಟಕಿ_RESIZABLE,           false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_TRANSPARENT_BOOLEAN,        SDL_ಕಿಟಕಿ_TRANSPARENT,         false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_TOOLTIP_BOOLEAN,            SDL_ಕಿಟಕಿ_TOOLTIP,             false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_UTILITY_BOOLEAN,            SDL_ಕಿಟಕಿ_UTILITY,             false },
    { SDL_PROP_ಕಿಟಕಿ_CREATE_VULKAN_BOOLEAN,             SDL_ಕಿಟಕಿ_VULKAN,              false }
};

ಸ್ಥಿರ SDL_ಕಿಟಕಿ_Flags SDL_Get_ಕಿಟಕಿ_Flag_Properties(SDL_PropertiesID props)
{
    ಚಿಹ್ನೆರಹಿತ i;
    SDL_ಕಿಟಕಿ_Flags flags = (SDL_ಕಿಟಕಿ_Flags)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_FLAGS_ಸಂಖ್ಯೆ, 0);

    ಗಾಗಿ (i = 0; i < SDL_arraysize(SDL_ಕಿಟಕಿ_Flag_Properties); ++i) {
        ಆದರೆ (SDL_ಕಿಟಕಿ_Flag_Properties[i].invert_ಮೌಲ್ಯ) {
            ಆದರೆ (!SDL_GetBooleanProperty(props, SDL_ಕಿಟಕಿ_Flag_Properties[i].property_name, true)) {
                flags |= SDL_ಕಿಟಕಿ_Flag_Properties[i].flag;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (SDL_GetBooleanProperty(props, SDL_ಕಿಟಕಿ_Flag_Properties[i].property_name, false)) {
                flags |= SDL_ಕಿಟಕಿ_Flag_Properties[i].flag;
            }
        }
    }
    ಹಿಂತಿರುಗಿ flags;
}

SDL_ಕಿಟಕಿ *SDL_Create_ಕಿಟಕಿ_With_Properties(SDL_PropertiesID props)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *title = SDL_GetStringProperty(props, SDL_PROP_ಕಿಟಕಿ_CREATE_TITLE_STRING, ಖಾಲಿ);
    ಪೂರ್ಣಾಂಕ x = (ಪೂರ್ಣಾಂಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_X_ಸಂಖ್ಯೆ, SDL_WINDOWPOS_UNDEFINED);
    ಪೂರ್ಣಾಂಕ y = (ಪೂರ್ಣಾಂಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_Y_ಸಂಖ್ಯೆ, SDL_WINDOWPOS_UNDEFINED);
    ಪೂರ್ಣಾಂಕ w = (ಪೂರ್ಣಾಂಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಅಗಲ_ಸಂಖ್ಯೆ, 0);
    ಪೂರ್ಣಾಂಕ h = (ಪೂರ್ಣಾಂಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಎತ್ತರ_ಸಂಖ್ಯೆ, 0);
    SDL_ಕಿಟಕಿ *ಪೋಷಕ = (SDL_ಕಿಟಕಿ *)SDL_Get_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಪೋಷಕ_ಸೂಚಕ, ಖಾಲಿ);
    SDL_ಕಿಟಕಿ_Flags flags = SDL_Get_ಕಿಟಕಿ_Flag_Properties(props);
    SDL_ಕಿಟಕಿ_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_ಕಿಟಕಿ_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    ಆದರೆ (!_this) {
        // Initialize the video system if needed
        ಆದರೆ (!SDL_Init(SDL_INIT_VIDEO)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // Make clang-tidy happy
        ಆದರೆ (!_this) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_MODAL) && !SDL_ObjectValid(ಪೋಷಕ, SDL_OBJECT_TYPE_ಕಿಟಕಿ)) {
        SDL_ಗಣ_Error("Modal windows must specify a parent window");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ ((flags & (SDL_ಕಿಟಕಿ_TOOLTIP | SDL_ಕಿಟಕಿ_POPUP_MENU)) != 0) {
        ಆದರೆ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_ಕಿಟಕಿ_SUPPORT)) {
            SDL_Unsupported();
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // Tooltip and popup menu window must specify a parent window
        ಆದರೆ (!SDL_ObjectValid(ಪೋಷಕ, SDL_OBJECT_TYPE_ಕಿಟಕಿ)) {
            SDL_ಗಣ_Error("Tooltip and popup menu windows must specify a parent window");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        // Remove invalid flags
        flags &= ~(SDL_ಕಿಟಕಿ_MINIMIZED | SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_ಕಿಟಕಿ_UTILITY | SDL_ಕಿಟಕಿ_TOOLTIP | SDL_ಕಿಟಕಿ_POPUP_MENU | SDL_ಕಿಟಕಿ_MODAL);
    ಆದರೆ (type_flags & (type_flags - 1)) {
        SDL_ಗಣ_Error("Conflicting window type flags specified: 0x%.8x", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)type_flags);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Make sure the display list is up to date for window placement
    ಆದರೆ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ಆದರೆ (w < 1) {
        w = 1;
    }
    ಆದರೆ (h < 1) {
        h = 1;
    }

    ಆದರೆ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ಆದರೆ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ಆದರೆ (displayID == 0 || SDL_Get_Display_ಸೂಚ್ಯಂಕ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ಆದರೆ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ಆದರೆ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ಆದರೆ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ಆದರೆ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ಆದರೆ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_ಕಿಟಕಿ_OPENGL | SDL_ಕಿಟಕಿ_METAL | SDL_ಕಿಟಕಿ_VULKAN);
    ಆದರೆ (graphics_flags & (graphics_flags - 1)) {
        SDL_ಗಣ_Error("Conflicting window graphics flags specified: 0x%.8x", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)graphics_flags);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // Some platforms have certain graphics backends enabled by default
    ಆದರೆ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_OPENGL) {
        ಆದರೆ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        ಆದರೆ (!SDL_GL_ತುಂಬು_Library(ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_VULKAN) {
        ಆದರೆ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        ಆದರೆ (!SDL_Vulkan_ತುಂಬು_Library(ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_METAL) {
        ಆದರೆ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ *)SDL_calloc(1, ಗಾತ್ರ(*ಕಿಟಕಿ));
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    SDL_ಗಣ_Object_Valid(ಕಿಟಕಿ, SDL_OBJECT_TYPE_ಕಿಟಕಿ, true);
    ಕಿಟಕಿ->id = SDL_Get_ಮುಂದಿನ_Object_ID();
    ಕಿಟಕಿ->floating.x = ಕಿಟಕಿ->windowed.x = ಕಿಟಕಿ->x = x;
    ಕಿಟಕಿ->floating.y = ಕಿಟಕಿ->windowed.y = ಕಿಟಕಿ->y = y;
    ಕಿಟಕಿ->floating.w = ಕಿಟಕಿ->windowed.w = ಕಿಟಕಿ->w = w;
    ಕಿಟಕಿ->floating.h = ಕಿಟಕಿ->windowed.h = ಕಿಟಕಿ->h = h;
    ಕಿಟಕಿ->undefined_x = undefined_x;
    ಕಿಟಕಿ->undefined_y = undefined_y;
    ಕಿಟಕಿ->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಆದರೆ (display) {
        SDL_ಗಣ_ಕಿಟಕಿ_HDRProperties(ಕಿಟಕಿ, &display->HDR, false);
    }

    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        ಕಿಟಕಿ->x = bounds.x;
        ಕಿಟಕಿ->y = bounds.y;
        ಕಿಟಕಿ->w = bounds.w;
        ಕಿಟಕಿ->h = bounds.h;
        ಕಿಟಕಿ->pending_flags |= SDL_ಕಿಟಕಿ_FULLSCREEN;
        flags |= SDL_ಕಿಟಕಿ_FULLSCREEN;
    }

    ಕಿಟಕಿ->flags = ((flags & CREATE_FLAGS) | SDL_ಕಿಟಕಿ_HIDDEN);
    ಕಿಟಕಿ->display_scale = 1.0f;
    ಕಿಟಕಿ->opacity = 1.0f;
    ಕಿಟಕಿ->ಮುಂದಿನ = _this->windows;
    ಕಿಟಕಿ->is_destroying = false;
    ಕಿಟಕಿ->displayID = Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಕಿಟಕಿ->external_graphics_context = external_graphics_context;
    ಕಿಟಕಿ->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_ಕಿಟಕಿ_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Fill_Document) {
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ಆದರೆ (_this->windows) {
        _this->windows->prev = ಕಿಟಕಿ;
    }
    _this->windows = ಕಿಟಕಿ;

    // Set the parent before creation.
    SDL_Update_ಕಿಟಕಿ_Hierarchy(ಕಿಟಕಿ, ಪೋಷಕ);

    ಆದರೆ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, ಕಿಟಕಿ, props)) {
        SDL_ತಳ್ಳು_Error();
        SDL_Destroy_ಕಿಟಕಿ(ಕಿಟಕಿ);
        SDL_ತೆಗೆ_Error();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ಆದರೆ !defined(SDL_PLATFORM_WINDOWS)
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MINIMIZED;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (title) {
        SDL_ಗಣ_ಕಿಟಕಿ_Title(ಕಿಟಕಿ, title);
    }
    SDL_ಮುಕ್ತಾಯ_ಕಿಟಕಿ_Creation(ಕಿಟಕಿ, flags);

    // Make sure window pixel size is up to date
    SDL_Check_ಕಿಟಕಿ_Pixel_ಗಾತ್ರ_ಬದಲಾಯಿತು(ಕಿಟಕಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#ಆದರೆ_ಅಂತ್ಯ

    SDL_ClearError();

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ;
}

SDL_ಕಿಟಕಿ *SDL_Create_ಕಿಟಕಿ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *title, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, SDL_ಕಿಟಕಿ_Flags flags)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    SDL_PropertiesID props = SDL_CreateProperties();
    ಆದರೆ (title && *title) {
        SDL_ಗಣ_String_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_TITLE_STRING, title);
    }
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಅಗಲ_ಸಂಖ್ಯೆ, w);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಎತ್ತರ_ಸಂಖ್ಯೆ, h);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_FLAGS_ಸಂಖ್ಯೆ, flags);
    ಕಿಟಕಿ = SDL_Create_ಕಿಟಕಿ_With_Properties(props);
    SDL_DestroyProperties(props);
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ;
}

SDL_ಕಿಟಕಿ *SDL_Create_Popup_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಪೋಷಕ, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_x, ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_y, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, SDL_ಕಿಟಕಿ_Flags flags)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ಆದರೆ (!(flags & (SDL_ಕಿಟಕಿ_TOOLTIP | SDL_ಕಿಟಕಿ_POPUP_MENU))) {
        SDL_ಗಣ_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಪೋಷಕ_ಸೂಚಕ, ಪೋಷಕ);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_X_ಸಂಖ್ಯೆ, ಸ್ಥಾನಾಂತರ_x);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_Y_ಸಂಖ್ಯೆ, ಸ್ಥಾನಾಂತರ_y);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಅಗಲ_ಸಂಖ್ಯೆ, w);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_ಎತ್ತರ_ಸಂಖ್ಯೆ, h);
    SDL_ಗಣ_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_CREATE_FLAGS_ಸಂಖ್ಯೆ, flags);
    ಕಿಟಕಿ = SDL_Create_ಕಿಟಕಿ_With_Properties(props);
    SDL_DestroyProperties(props);
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ;
}

ಸ್ಥಿರ bool SDL_Reconfigure_ಕಿಟಕಿ_ಆಂತರಿಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ಆದರೆ (!_this->Reconfigure_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_Flags graphics_flags = flags & (SDL_ಕಿಟಕಿ_OPENGL | SDL_ಕಿಟಕಿ_METAL | SDL_ಕಿಟಕಿ_VULKAN);
    ಆದರೆ (graphics_flags & (graphics_flags - 1)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Conflicting window flags specified");
    }

    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_OPENGL) && !_this->GL_CreateContext) {
        ಹಿಂತಿರುಗಿ SDL_ContextNotSupported("OpenGL");
    }
    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_VULKAN) && !_this->Vulkan_CreateSurface) {
        ಹಿಂತಿರುಗಿ SDL_ContextNotSupported("Vulkan");
    }
    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_METAL) && !_this->Metal_CreateView) {
        ಹಿಂತಿರುಗಿ SDL_ContextNotSupported("Metal");
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ಆದರೆ (ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_OPENGL | SDL_ಕಿಟಕಿ_METAL | SDL_ಕಿಟಕಿ_VULKAN)) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ಆದರೆ (!_this->Reconfigure_ಕಿಟಕಿ(_this, ಕಿಟಕಿ, 0)) {
            ಹಿಂತಿರುಗಿ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        ಕಿಟಕಿ->flags &= ~(SDL_ಕಿಟಕಿ_OPENGL | SDL_ಕಿಟಕಿ_METAL | SDL_ಕಿಟಕಿ_VULKAN);
    }

    SDL_Destroy_ಕಿಟಕಿ_Surface(ಕಿಟಕಿ);

    ಆದರೆ (graphics_flags & SDL_ಕಿಟಕಿ_OPENGL) {
        loaded_opengl = SDL_GL_ತುಂಬು_Library(ಖಾಲಿ);
        ಆದರೆ (!loaded_opengl) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (graphics_flags & SDL_ಕಿಟಕಿ_VULKAN) {
        loaded_vulkan = SDL_Vulkan_ತುಂಬು_Library(ಖಾಲಿ);
        ಆದರೆ (!loaded_vulkan) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ಆದರೆ (!_this->Reconfigure_ಕಿಟಕಿ(_this, ಕಿಟಕಿ, graphics_flags)) {
        ಆದರೆ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ಆದರೆ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ಹಿಂತಿರುಗಿ false;
    }

    ಕಿಟಕಿ->flags |= graphics_flags;

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Recreate_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_ತುಂಬು = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_ತುಂಬು = false;
    SDL_ಕಿಟಕಿ_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_ಕಿಟಕಿ_OPENGL | SDL_ಕಿಟಕಿ_METAL | SDL_ಕಿಟಕಿ_VULKAN);
    ಆದರೆ (graphics_flags & (graphics_flags - 1)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Conflicting window flags specified");
    }

    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_OPENGL) && !_this->GL_CreateContext) {
        ಹಿಂತಿರುಗಿ SDL_ContextNotSupported("OpenGL");
    }
    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_VULKAN) && !_this->Vulkan_CreateSurface) {
        ಹಿಂತಿರುಗಿ SDL_ContextNotSupported("Vulkan");
    }
    ಆದರೆ ((flags & SDL_ಕಿಟಕಿ_METAL) && !_this->Metal_CreateView) {
        ಹಿಂತಿರುಗಿ SDL_ContextNotSupported("Metal");
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_ಕಿಟಕಿ_EXTERNAL;
    } ಇಲ್ಲದಿದ್ದರೆ {
        flags &= ~SDL_ಕಿಟಕಿ_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MODAL) {
        SDL_ಗಣ_ಕಿಟಕಿ_Modal(ಕಿಟಕಿ, false);
    }

    // Restore video mode, etc.
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
        ಸ್ಥಿರಾಂಕ bool restore_on_show = ಕಿಟಕಿ->restore_on_show;
        SDL_Hide_ಕಿಟಕಿ(ಕಿಟಕಿ);
        ಕಿಟಕಿ->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_ಕಿಟಕಿ_Surface(ಕಿಟಕಿ);

    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) != (flags & SDL_ಕಿಟಕಿ_OPENGL)) {
        ಆದರೆ (flags & SDL_ಕಿಟಕಿ_OPENGL) {
            need_gl_ತುಂಬು = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            need_gl_unload = true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        need_gl_unload = true;
        need_gl_ತುಂಬು = true;
    }

    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN) != (flags & SDL_ಕಿಟಕಿ_VULKAN)) {
        ಆದರೆ (flags & SDL_ಕಿಟಕಿ_VULKAN) {
            need_vulkan_ತುಂಬು = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            need_vulkan_unload = true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_ತುಂಬು = true;
    }

    ಆದರೆ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ಆದರೆ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ಆದರೆ (_this->Destroy_ಕಿಟಕಿ && !(flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
        _this->Destroy_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (need_gl_ತುಂಬು) {
        ಆದರೆ (!SDL_GL_ತುಂಬು_Library(ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
        loaded_opengl = true;
    }

    ಆದರೆ (need_vulkan_ತುಂಬು) {
        ಆದರೆ (!SDL_Vulkan_ತುಂಬು_Library(ಖಾಲಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
        loaded_vulkan = true;
    }

    ಕಿಟಕಿ->flags = ((flags & CREATE_FLAGS) | SDL_ಕಿಟಕಿ_HIDDEN);
    ಕಿಟಕಿ->is_destroying = false;

    ಆದರೆ (_this->CreateSDLWindow && !(flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        ಕಿಟಕಿ->x = ಕಿಟಕಿ->windowed.x = ಕಿಟಕಿ->floating.x;
        ಕಿಟಕಿ->y = ಕಿಟಕಿ->windowed.y = ಕಿಟಕಿ->floating.y;
        ಕಿಟಕಿ->w = ಕಿಟಕಿ->windowed.w = ಕಿಟಕಿ->floating.w;
        ಕಿಟಕಿ->h = ಕಿಟಕಿ->windowed.h = ಕಿಟಕಿ->floating.h;

        ಆದರೆ (!_this->CreateSDLWindow(_this, ಕಿಟಕಿ, 0)) {
            ಆದರೆ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_OPENGL;
            }
            ಆದರೆ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_VULKAN;
            }
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_EXTERNAL;
    }

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Title && ಕಿಟಕಿ->title) {
        _this->ಗಣ_ಕಿಟಕಿ_Title(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Icon && ಕಿಟಕಿ->icon) {
        _this->ಗಣ_ಕಿಟಕಿ_Icon(_this, ಕಿಟಕಿ, ಕಿಟಕಿ->icon);
    }

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ && (ಕಿಟಕಿ->min_w || ಕಿಟಕಿ->min_h)) {
        _this->ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ && (ಕಿಟಕಿ->max_w || ಕಿಟಕಿ->max_h)) {
        _this->ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ && (ಕಿಟಕಿ->min_aspect > 0.0f || ಕಿಟಕಿ->max_aspect > 0.0f)) {
        _this->ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(_this, ಕಿಟಕಿ);
    }

    ಆದರೆ (ಕಿಟಕಿ->ದೊರಕಿತು_test) {
        _this->ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(ಕಿಟಕಿ, true);
    }

    SDL_ಮುಕ್ತಾಯ_ಕಿಟಕಿ_Creation(ಕಿಟಕಿ, flags);

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Reconfigure_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ಆದರೆ (!SDL_Reconfigure_ಕಿಟಕಿ_ಆಂತರಿಕ(ಕಿಟಕಿ, flags)) {
        ಹಿಂತಿರುಗಿ SDL_Recreate_ಕಿಟಕಿ(ಕಿಟಕಿ, flags);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_HasWindows(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ _this && _this->windows;
}

SDL_ಕಿಟಕಿ_ID SDL_Get_ಕಿಟಕಿ_ID(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->id;
}

SDL_ಕಿಟಕಿ *SDL_Get_ಕಿಟಕಿ_From_ID(SDL_ಕಿಟಕಿ_ID id)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (id) {
        ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            ಆದರೆ (ಕಿಟಕಿ->id == id) {
                ಹಿಂತಿರುಗಿ ಕಿಟಕಿ;
            }
        }
    }
    SDL_ಗಣ_Error("Invalid window ID");
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

SDL_ಕಿಟಕಿ *SDL_Get_ಕಿಟಕಿ_ಪೋಷಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->ಪೋಷಕ;
}

SDL_PropertiesID SDL_Get_ಕಿಟಕಿ_Properties(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0);

    ಆದರೆ (ಕಿಟಕಿ->props == 0) {
        ಕಿಟಕಿ->props = SDL_CreateProperties();
    }
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->props;
}

SDL_ಕಿಟಕಿ_Flags SDL_Get_ಕಿಟಕಿ_Flags(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, 0);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->flags | ಕಿಟಕಿ->pending_flags;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Title(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *title)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (title == ಕಿಟಕಿ->title) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಆದರೆ (!title) {
        title = "";
    }
    ಆದರೆ (ಕಿಟಕಿ->title && SDL_strcmp(title, ಕಿಟಕಿ->title) == 0) {
        ಹಿಂತಿರುಗಿ true;
    }

    SDL_free(ಕಿಟಕಿ->title);

    ಕಿಟಕಿ->title = SDL_strdup(title);

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Title) {
        _this->ಗಣ_ಕಿಟಕಿ_Title(_this, ಕಿಟಕಿ);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_Get_ಕಿಟಕಿ_Title(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, "");

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->title ? ಕಿಟಕಿ->title : "";
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Icon(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    CHECK_PARAM(!icon) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(ಕಿಟಕಿ->icon);

    // Convert the icon into ARGB8888
    ಕಿಟಕಿ->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ಆದರೆ (!ಕಿಟಕಿ->icon) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Icon) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಹಿಂತಿರುಗಿ _this->ಗಣ_ಕಿಟಕಿ_Icon(_this, ಕಿಟಕಿ, ಕಿಟಕಿ->icon);
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    SDL_DisplayID original_displayID;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ w = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ಕಿಟಕಿ->windowed.w;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ h = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ಕಿಟಕಿ->windowed.h;

    original_displayID = Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
    ಕಿಟಕಿ->pending_displayID = 0;

    ಆದರೆ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = ಕಿಟಕಿ->windowed.x;
    }
    ಆದರೆ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = ಕಿಟಕಿ->windowed.y;
    }
    ಆದರೆ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ಆದರೆ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ಆದರೆ (displayID == 0 || SDL_Get_Display_ಸೂಚ್ಯಂಕ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        ಕಿಟಕಿ->pending_displayID = displayID;

        SDL_zero(bounds);
        ಆದರೆ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ಆದರೆ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }
        ಆದರೆ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ಆದರೆ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        /* See if the requested window position matches the origin of any displays and set
         * the pending fullscreen display ID if it does. This needs to be set early in case
         * the window is prevented from moving to the exact origin due to struts.
         */
        ಕಿಟಕಿ->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    ಕಿಟಕಿ->pending.x = x;
    ಕಿಟಕಿ->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    ಆದರೆ (!_this->Sync_ಕಿಟಕಿ && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ಕಿಟಕಿ->floating.x = ಕಿಟಕಿ->windowed.x = x;
        ಕಿಟಕಿ->floating.y = ಕಿಟಕಿ->windowed.y = y;
    }
    ಕಿಟಕಿ->undefined_x = false;
    ಕಿಟಕಿ->undefined_y = false;
    ಕಿಟಕಿ->ಕೊನೆಯ_position_pending = true;

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Position) {
        ಸ್ಥಿರಾಂಕ bool ಫಲಿತಾಂಶ = _this->ಗಣ_ಕಿಟಕಿ_Position(_this, ಕಿಟಕಿ);
        ಆದರೆ (ಫಲಿತಾಂಶ) {
            SDL_SyncIfRequired(ಕಿಟಕಿ);
        }
        ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
    }

    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool SDL_Get_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *x, ಪೂರ್ಣಾಂಕ *y)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ಇಲ್ಲದಿದ್ದರೆ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) != 0);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (use_display_origin) {
        SDL_DisplayID displayID;

        ಆದರೆ (x) {
            *x = 0;
        }
        ಆದರೆ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
        ಆದರೆ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ಆದರೆ (x) {
                *x = bounds.x;
            }
            ಆದರೆ (y) {
                *y = bounds.y;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ bool use_pending = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) && ಕಿಟಕಿ->ಕೊನೆಯ_position_pending;
        ಆದರೆ (x) {
            *x = use_pending ? ಕಿಟಕಿ->pending.x : ಕಿಟಕಿ->x;
        }
        ಆದರೆ (y) {
            *y = use_pending ? ಕಿಟಕಿ->pending.y : ಕಿಟಕಿ->y;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Bordered) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಸ್ಥಿರಾಂಕ bool want = bordered;
    ಸ್ಥಿರಾಂಕ bool have = !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS);
    ಆದರೆ (want != have) {
        ಆದರೆ (want) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_BORDERLESS;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_BORDERLESS;
        }
        _this->ಗಣ_ಕಿಟಕಿ_Bordered(_this, ಕಿಟಕಿ, want);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Resizable) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಸ್ಥಿರಾಂಕ bool want = resizable;
    ಸ್ಥಿರಾಂಕ bool have = ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) != 0);
    ಆದರೆ (want != have) {
        ಆದರೆ (want) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_RESIZABLE;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_RESIZABLE;
            SDL_copyp(&ಕಿಟಕಿ->windowed, &ಕಿಟಕಿ->floating);
        }
        _this->ಗಣ_ಕಿಟಕಿ_Resizable(_this, ಕಿಟಕಿ, want);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool on_ತುದಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಸ್ಥಿರಾಂಕ bool want = on_ತುದಿ;
    ಸ್ಥಿರಾಂಕ bool have = ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ) != 0);
    ಆದರೆ (want != have) {
        ಆದರೆ (want) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_ALWAYS_ON_ತುದಿ;
        }
        _this->ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(_this, ಕಿಟಕಿ, want);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    CHECK_PARAM(w <= 0) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    ದಶಮಾಂಶ new_aspect = w / (ದಶಮಾಂಶ)h;
    ಆದರೆ (ಕಿಟಕಿ->max_aspect > 0.0f && new_aspect > ಕಿಟಕಿ->max_aspect) {
        w = (ಪೂರ್ಣಾಂಕ)SDL_roundf(h * ಕಿಟಕಿ->max_aspect);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->min_aspect > 0.0f && new_aspect < ಕಿಟಕಿ->min_aspect) {
        h = (ಪೂರ್ಣಾಂಕ)SDL_roundf(w / ಕಿಟಕಿ->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ಆದರೆ (ಕಿಟಕಿ->min_w && w < ಕಿಟಕಿ->min_w) {
        w = ಕಿಟಕಿ->min_w;
    }
    ಆದರೆ (ಕಿಟಕಿ->max_w && w > ಕಿಟಕಿ->max_w) {
        w = ಕಿಟಕಿ->max_w;
    }
    ಆದರೆ (ಕಿಟಕಿ->min_h && h < ಕಿಟಕಿ->min_h) {
        h = ಕಿಟಕಿ->min_h;
    }
    ಆದರೆ (ಕಿಟಕಿ->max_h && h > ಕಿಟಕಿ->max_h) {
        h = ಕಿಟಕಿ->max_h;
    }

    ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending = true;
    ಕಿಟಕಿ->pending.w = w;
    ಕಿಟಕಿ->pending.h = h;

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ) {
        _this->ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(_this, ಕಿಟಕಿ);
        SDL_SyncIfRequired(ಕಿಟಕಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    ಆದರೆ (w) {
        *w = ಕಿಟಕಿ->w;
    }
    ಆದರೆ (h) {
        *h = ಕಿಟಕಿ->h;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ min_aspect, ದಶಮಾಂಶ max_aspect)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಕಿಟಕಿ->min_aspect = min_aspect;
    ಕಿಟಕಿ->max_aspect = max_aspect;

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ) {
        _this->ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(_this, ಕಿಟಕಿ);
    }

    // Ensure that window has the correct aspect ratio
    ಪೂರ್ಣಾಂಕ w = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ಕಿಟಕಿ->floating.w;
    ಪೂರ್ಣಾಂಕ h = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ಕಿಟಕಿ->floating.h;
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(ಕಿಟಕಿ, w, h);
}

bool SDL_Get_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ *min_aspect, ದಶಮಾಂಶ *max_aspect)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (min_aspect) {
        *min_aspect = ಕಿಟಕಿ->min_aspect;
    }
    ಆದರೆ (max_aspect) {
        *max_aspect = ಕಿಟಕಿ->max_aspect;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *ತುದಿ, ಪೂರ್ಣಾಂಕ *ಎಡ, ಪೂರ್ಣಾಂಕ *bottom, ಪೂರ್ಣಾಂಕ *ಬಲ)
{
    ಪೂರ್ಣಾಂಕ dummy = 0;

    ಆದರೆ (!ತುದಿ) {
        ತುದಿ = &dummy;
    }
    ಆದರೆ (!ಎಡ) {
        ಎಡ = &dummy;
    }
    ಆದರೆ (!ಬಲ) {
        ಬಲ = &dummy;
    }
    ಆದರೆ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *ತುದಿ = *ಎಡ = *bottom = *ಬಲ = 0;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಹಿಂತಿರುಗಿ _this->Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ(_this, ಕಿಟಕಿ, ತುದಿ, ಎಡ, bottom, ಬಲ);
}

bool SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h)
{
    ಪೂರ್ಣಾಂಕ filter;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!w) {
        w = &filter;
    }

    ಆದರೆ (!h) {
        h = &filter;
    }

    ಆದರೆ (_this->Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels) {
        _this->Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(_this, ಕಿಟಕಿ, w, h);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_DisplayID displayID = Get_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ);
        ಸ್ಥಿರಾಂಕ SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ;

        SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ(ಕಿಟಕಿ, w, h);

        ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && SDL_Get_ಕಿಟಕಿ_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ)) {
            ಬಹುಲಕ = SDL_Get_Current_Display_ಬಹುಲಕ(displayID);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬಹುಲಕ = SDL_Get_Desktop_Display_ಬಹುಲಕ(displayID);
        }
        ಆದರೆ (ಬಹುಲಕ) {
            *w = (ಪೂರ್ಣಾಂಕ)SDL_ceilf(*w * ಬಹುಲಕ->pixel_density);
            *h = (ಪೂರ್ಣಾಂಕ)SDL_ceilf(*h * ಬಹುಲಕ->pixel_density);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ min_w, ಪೂರ್ಣಾಂಕ min_h)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_PARAM(min_w < 0) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((ಕಿಟಕಿ->max_w && min_w > ಕಿಟಕಿ->max_w) || (ಕಿಟಕಿ->max_h && min_h > ಕಿಟಕಿ->max_h)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    ಕಿಟಕಿ->min_w = min_w;
    ಕಿಟಕಿ->min_h = min_h;

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ) {
        _this->ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(_this, ಕಿಟಕಿ);
    }

    // Ensure that window is not smaller than minimal size
    ಪೂರ್ಣಾಂಕ w = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ಕಿಟಕಿ->floating.w;
    ಪೂರ್ಣಾಂಕ h = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ಕಿಟಕಿ->floating.h;
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(ಕಿಟಕಿ, w, h);
}

bool SDL_Get_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *min_w, ಪೂರ್ಣಾಂಕ *min_h)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    ಆದರೆ (min_w) {
        *min_w = ಕಿಟಕಿ->min_w;
    }
    ಆದರೆ (min_h) {
        *min_h = ಕಿಟಕಿ->min_h;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ max_w, ಪೂರ್ಣಾಂಕ max_h)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_PARAM(max_w < 0) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("max_h");
    }

    ಆದರೆ ((max_w && max_w < ಕಿಟಕಿ->min_w) ||
        (max_h && max_h < ಕಿಟಕಿ->min_h)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    ಕಿಟಕಿ->max_w = max_w;
    ಕಿಟಕಿ->max_h = max_h;

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ) {
        _this->ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(_this, ಕಿಟಕಿ);
    }

    // Ensure that window is not larger than maximal size
    ಪೂರ್ಣಾಂಕ w = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.w : ಕಿಟಕಿ->floating.w;
    ಪೂರ್ಣಾಂಕ h = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending ? ಕಿಟಕಿ->pending.h : ಕಿಟಕಿ->floating.h;
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(ಕಿಟಕಿ, w, h);
}

bool SDL_Get_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *max_w, ಪೂರ್ಣಾಂಕ *max_h)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    ಆದರೆ (max_w) {
        *max_w = ಕಿಟಕಿ->max_w;
    }
    ಆದರೆ (max_h) {
        *max_h = ಕಿಟಕಿ->max_h;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Show_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ *ಮಗು;
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
        ಹಿಂತಿರುಗಿ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ಆದರೆ (ಕಿಟಕಿ->ಪೋಷಕ && (ಕಿಟಕಿ->ಪೋಷಕ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
        ಕಿಟಕಿ->restore_on_show = true;
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (_this->Show_ಕಿಟಕಿ) {
        _this->Show_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
        SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
    }
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);

    // Restore child windows
    ಗಾಗಿ (ಮಗು = ಕಿಟಕಿ->ಮೊದಲ_ಮಗು; ಮಗು; ಮಗು = ಮಗು->ಮುಂದಿನ_sibling) {
        ಆದರೆ (!ಮಗು->restore_on_show && (ಮಗು->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
            ನಿಲ್ಲಿಸು;
        }
        SDL_Show_ಕಿಟಕಿ(ಮಗು);
        ಮಗು->restore_on_show = false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Hide_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ *ಮಗು;
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಕಿಟಕಿ->restore_on_show = false;
        ಹಿಂತಿರುಗಿ true;
    }

    // Hide all child windows
    ಗಾಗಿ (ಮಗು = ಕಿಟಕಿ->ಮೊದಲ_ಮಗು; ಮಗು; ಮಗು = ಮಗು->ಮುಂದಿನ_sibling) {
        ಆದರೆ (ಮಗು->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
            ನಿಲ್ಲಿಸು;
        }
        SDL_Hide_ಕಿಟಕಿ(ಮಗು);
        ಮಗು->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ಸ್ಥಿರಾಂಕ SDL_ಕಿಟಕಿ_Flags pending_ಮುಖವಾಡ = (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_MINIMIZED | SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED | SDL_ಕಿಟಕಿ_MOUSE_GRABBED);
    ಕಿಟಕಿ->pending_flags = (ಕಿಟಕಿ->flags & pending_ಮುಖವಾಡ);

    ಕಿಟಕಿ->is_hiding = true;
    ಆದರೆ (_this->Hide_ಕಿಟಕಿ) {
        _this->Hide_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
        SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
    }
    ಕಿಟಕಿ->is_hiding = false;
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_HIDDEN, 0, 0);
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Raise_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಆದರೆ (_this->Raise_ಕಿಟಕಿ) {
        _this->Raise_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Maximize_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->Maximize_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಕಿಟಕಿ->pending_flags |= SDL_ಕಿಟಕಿ_MAXIMIZED;
        ಹಿಂತಿರುಗಿ true;
    }

    _this->Maximize_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    SDL_SyncIfRequired(ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Minimize_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->Minimize_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಕಿಟಕಿ->pending_flags |= SDL_ಕಿಟಕಿ_MINIMIZED;
        ಹಿಂತಿರುಗಿ true;
    }

    _this->Minimize_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    SDL_SyncIfRequired(ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Restore_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->Restore_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಕಿಟಕಿ->pending_flags &= ~(SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_MINIMIZED);
        ಹಿಂತಿರುಗಿ true;
    }

    _this->Restore_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    SDL_SyncIfRequired(ಕಿಟಕಿ);
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool fullscreen)
{
    bool ಫಲಿತಾಂಶ;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಆದರೆ (fullscreen) {
            ಕಿಟಕಿ->pending_flags |= SDL_ಕಿಟಕಿ_FULLSCREEN;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->pending_flags &= ~SDL_ಕಿಟಕಿ_FULLSCREEN;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ, &ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ);
    }

    ಫಲಿತಾಂಶ = SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ಆದರೆ (!fullscreen || !ಫಲಿತಾಂಶ) {
        // Clear the current fullscreen mode.
        SDL_zero(ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ);
    }

    ಆದರೆ (ಫಲಿತಾಂಶ) {
        SDL_SyncIfRequired(ಕಿಟಕಿ);
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_Sync_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (_this->Sync_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ _this->Sync_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ true;
    }
}

ಸ್ಥಿರ bool ShouldAttemptTextureFramebuffer(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ಆದರೆ (!_this->Create_ಕಿಟಕಿ_Framebuffer) {
        ಹಿಂತಿರುಗಿ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ಆದರೆ (hint && *hint) {
        ಆದರೆ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ಇಲ್ಲದಿದ್ದರೆ {
            attempt_texture_framebuffer = true;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            attempt_texture_framebuffer = false;
        }
    }
    ಹಿಂತಿರುಗಿ attempt_texture_framebuffer;
}

ಸ್ಥಿರ SDL_Surface *SDL_Create_ಕಿಟಕಿ_Framebuffer(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    ಶೂನ್ಯ *pixels = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ pitch = 0;
    bool created_framebuffer = false;
    ಪೂರ್ಣಾಂಕ w, h;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    ಆದರೆ (!_this->checked_texture_framebuffer) {
        ಆದರೆ (ShouldAttemptTextureFramebuffer()) {
            ಆದರೆ (!SDL_Create_ಕಿಟಕಿ_Texture(_this, ಕಿಟಕಿ, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ಇಲ್ಲದಿದ್ದರೆ {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_ಕಿಟಕಿ_Framebuffer = SDL_Create_ಕಿಟಕಿ_Texture;
                _this->ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync = SDL_ಗಣ_ಕಿಟಕಿ_Texture_VSync;
                _this->Get_ಕಿಟಕಿ_Framebuffer_VSync = SDL_Get_ಕಿಟಕಿ_Texture_VSync;
                _this->Update_ಕಿಟಕಿ_Framebuffer = SDL_Update_ಕಿಟಕಿ_Texture;
                _this->Destroy_ಕಿಟಕಿ_Framebuffer = SDL_Destroy_ಕಿಟಕಿ_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    ಆದರೆ (!created_framebuffer) {
        ಆದರೆ (!_this->Create_ಕಿಟಕಿ_Framebuffer || !_this->Update_ಕಿಟಕಿ_Framebuffer) {
            SDL_ಗಣ_Error("Window framebuffer support not available");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        ಆದರೆ (!_this->Create_ಕಿಟಕಿ_Framebuffer(_this, ಕಿಟಕಿ, &format, &pixels, &pitch)) {
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    ಆದರೆ (ಕಿಟಕಿ->surface) {
        // We may have gone recursive and already created the surface
        ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->surface;
    }

    ಹಿಂತಿರುಗಿ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_ಕಿಟಕಿ_Has_Surface(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->surface ? true : false;
}

SDL_Surface *SDL_Get_ಕಿಟಕಿ_Surface(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಖಾಲಿ);

    ಆದರೆ (!ಕಿಟಕಿ->surface_valid) {
        ಆದರೆ (ಕಿಟಕಿ->surface) {
            ಕಿಟಕಿ->surface->ಆಂತರಿಕ_flags &= ~SDL_ಆಂತರಿಕ_SURFACE_DONTFREE;
            SDL_DestroySurface(ಕಿಟಕಿ->surface);
            ಕಿಟಕಿ->surface = ಖಾಲಿ;
        }

        ಕಿಟಕಿ->surface = SDL_Create_ಕಿಟಕಿ_Framebuffer(ಕಿಟಕಿ);
        ಆದರೆ (ಕಿಟಕಿ->surface) {
            ಕಿಟಕಿ->surface_valid = true;
            ಕಿಟಕಿ->surface->ಆಂತರಿಕ_flags |= SDL_ಆಂತರಿಕ_SURFACE_DONTFREE;
        }
    }
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->surface;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Surface_VSync(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ vsync)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }
    ಹಿಂತಿರುಗಿ _this->ಗಣ_ಕಿಟಕಿ_Framebuffer_VSync(_this, ಕಿಟಕಿ, vsync);
}

bool SDL_Get_ಕಿಟಕಿ_Surface_VSync(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *vsync)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->Get_ಕಿಟಕಿ_Framebuffer_VSync) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }
    ಹಿಂತಿರುಗಿ _this->Get_ಕಿಟಕಿ_Framebuffer_VSync(_this, ಕಿಟಕಿ, vsync);
}

bool SDL_Update_ಕಿಟಕಿ_Surface(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Rect ತುಂಬಿದ_rect;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ತುಂಬಿದ_rect.x = 0;
    ತುಂಬಿದ_rect.y = 0;
    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &ತುಂಬಿದ_rect.w, &ತುಂಬಿದ_rect.h);

    ಹಿಂತಿರುಗಿ SDL_Update_ಕಿಟಕಿ_Surface_Rects(ಕಿಟಕಿ, &ತುಂಬಿದ_rect, 1);
}

bool SDL_Update_ಕಿಟಕಿ_Surface_Rects(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects,
                                 ಪೂರ್ಣಾಂಕ numrects)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!ಕಿಟಕಿ->surface_valid) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ಹಿಂತಿರುಗಿ _this->Update_ಕಿಟಕಿ_Framebuffer(_this, ಕಿಟಕಿ, rects, numrects);
}

bool SDL_Destroy_ಕಿಟಕಿ_Surface(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->surface) {
        ಕಿಟಕಿ->surface->ಆಂತರಿಕ_flags &= ~SDL_ಆಂತರಿಕ_SURFACE_DONTFREE;
        SDL_DestroySurface(ಕಿಟಕಿ->surface);
        ಕಿಟಕಿ->surface = ಖಾಲಿ;
        ಕಿಟಕಿ->surface_valid = false;
    }

    ಆದರೆ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ಆದರೆ (_this->Destroy_ಕಿಟಕಿ_Framebuffer) {
            _this->Destroy_ಕಿಟಕಿ_Framebuffer(_this, ಕಿಟಕಿ);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity)
{
    bool ಫಲಿತಾಂಶ;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Opacity) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (opacity < 0.0f) {
        opacity = 0.0f;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    ಫಲಿತಾಂಶ = _this->ಗಣ_ಕಿಟಕಿ_Opacity(_this, ಕಿಟಕಿ, opacity);
    ಆದರೆ (ಫಲಿತಾಂಶ) {
        ಕಿಟಕಿ->opacity = opacity;
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ದಶಮಾಂಶ SDL_Get_ಕಿಟಕಿ_Opacity(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, -1.0f);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->opacity;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (ಪೋಷಕ) {
        CHECK_ಕಿಟಕಿ_MAGIC(ಪೋಷಕ, false);
        CHECK_ಕಿಟಕಿ_NOT_POPUP(ಪೋಷಕ, false);
    }

    ಆದರೆ (ಕಿಟಕಿ == ಪೋಷಕ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Cannot set the parent of a window to itself.");
    }

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MODAL) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ಆದರೆ (ಕಿಟಕಿ->ಪೋಷಕ == ಪೋಷಕ) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಸ್ಥಿರಾಂಕ bool ret = _this->ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(_this, ಕಿಟಕಿ, ಪೋಷಕ);
    SDL_Update_ಕಿಟಕಿ_Hierarchy(ಕಿಟಕಿ, ret ? ಪೋಷಕ : ಖಾಲಿ);

    ಹಿಂತಿರುಗಿ ret;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Modal(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Modal) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಆದರೆ (modal) {
        ಆದರೆ (!ಕಿಟಕಿ->ಪೋಷಕ) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_MODAL;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MODAL) {
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MODAL;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ true; // Already not modal, so nothing to do.
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ _this->ಗಣ_ಕಿಟಕಿ_Modal(_this, ಕಿಟಕಿ, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ **new_focus)
{
    SDL_ಕಿಟಕಿ *focus = ಕಿಟಕಿ->ಪೋಷಕ;
    bool ಗಣ_focus = !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ಆಗ (SDL_ಕಿಟಕಿ_IS_POPUP(focus) && ((focus->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->ಪೋಷಕ;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ಆದರೆ (!ಗಣ_focus) {
            ಗಣ_focus = !!(focus->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS);
        }
    }

    *new_focus = focus;
    ಹಿಂತಿರುಗಿ ಗಣ_focus;
}

bool SDL_ShouldFocusPopup(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ *toplevel_ಪೋಷಕ;
    ಗಾಗಿ (toplevel_ಪೋಷಕ = ಕಿಟಕಿ->ಪೋಷಕ; SDL_ಕಿಟಕಿ_IS_POPUP(toplevel_ಪೋಷಕ); toplevel_ಪೋಷಕ = toplevel_ಪೋಷಕ->ಪೋಷಕ) {
    }

    SDL_ಕಿಟಕಿ *current_focus = toplevel_ಪೋಷಕ->keyboard_focus;
    bool ಸಿಕ್ಕಿತು_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_ಕಿಟಕಿ *w;
    ಗಾಗಿ (w = current_focus; w != toplevel_ಪೋಷಕ; w = w->ಪೋಷಕ) {
        ಆದರೆ (w == ಕಿಟಕಿ) {
            ಸಿಕ್ಕಿತು_higher_focus = true;
            ನಿಲ್ಲಿಸು;
        }
    }

    ಹಿಂತಿರುಗಿ !ಸಿಕ್ಕಿತು_higher_focus || w == toplevel_ಪೋಷಕ;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಸ್ಥಿರಾಂಕ bool want = (focusable != false); // normalize the flag.
    ಸ್ಥಿರಾಂಕ bool have = !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE);
    ಆದರೆ ((want != have) && (_this->ಗಣ_ಕಿಟಕಿ_Focusable)) {
        ಆದರೆ (want) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_NOT_FOCUSABLE;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_NOT_FOCUSABLE;
        }
        ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Focusable(_this, ಕಿಟಕಿ, want)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Fill_Document(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool fill)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಸ್ಥಿರಾಂಕ bool want = (fill != false); // normalize the flag.
    ಸ್ಥಿರಾಂಕ bool have = ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FILL_DOCUMENT) != 0);
    ಆದರೆ ((want != have) && (_this->ಗಣ_ಕಿಟಕಿ_Fill_Document)) {
        ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Fill_Document(_this, ಕಿಟಕಿ, want)) {
            ಹಿಂತಿರುಗಿ false;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (want) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_FILL_DOCUMENT;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_FILL_DOCUMENT;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_Update_ಕಿಟಕಿ_Grab(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    bool keyboard_grabbed, mouse_grabbed;

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS) {
        ಆದರೆ (SDL_GetMouse()->relative_ಬಹುಲಕ || (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            mouse_grabbed = false;
        }

        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            keyboard_grabbed = false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ಆದರೆ (mouse_grabbed || keyboard_grabbed) {
        ಆದರೆ (_this->grabbed_ಕಿಟಕಿ && (_this->grabbed_ಕಿಟಕಿ != ಕಿಟಕಿ)) {
            // stealing a grab from another window!
            _this->grabbed_ಕಿಟಕಿ->flags &= ~(SDL_ಕಿಟಕಿ_MOUSE_GRABBED | SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED);
            ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Mouse_Grab) {
                _this->ಗಣ_ಕಿಟಕಿ_Mouse_Grab(_this, _this->grabbed_ಕಿಟಕಿ, false);
            }
            ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab) {
                _this->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(_this, _this->grabbed_ಕಿಟಕಿ, false);
            }
        }
        _this->grabbed_ಕಿಟಕಿ = ಕಿಟಕಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->grabbed_ಕಿಟಕಿ == ಕಿಟಕಿ) {
        _this->grabbed_ಕಿಟಕಿ = ಖಾಲಿ; // ungrabbing input.
    }

    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Mouse_Grab) {
        ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Mouse_Grab(_this, ಕಿಟಕಿ, mouse_grabbed)) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MOUSE_GRABBED;
        }
    }
    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab) {
        ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(_this, ಕಿಟಕಿ, keyboard_grabbed)) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED;
        }
    }

    ಆದರೆ (_this->grabbed_ಕಿಟಕಿ && !(_this->grabbed_ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MOUSE_GRABBED | SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED))) {
        _this->grabbed_ಕಿಟಕಿ = ಖಾಲಿ;
    }
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಆದರೆ (grabbed) {
            ಕಿಟಕಿ->pending_flags |= SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->pending_flags &= ~SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!!grabbed == !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED)) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಆದರೆ (grabbed) {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED;
    }
    SDL_Update_ಕಿಟಕಿ_Grab(ಕಿಟಕಿ);

    ಆದರೆ (grabbed && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED)) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN) {
        ಆದರೆ (grabbed) {
            ಕಿಟಕಿ->pending_flags |= SDL_ಕಿಟಕಿ_MOUSE_GRABBED;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->pending_flags &= ~SDL_ಕಿಟಕಿ_MOUSE_GRABBED;
        }
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!!grabbed == !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED)) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಆದರೆ (grabbed) {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_MOUSE_GRABBED;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MOUSE_GRABBED;
    }
    SDL_Update_ಕಿಟಕಿ_Grab(ಕಿಟಕಿ);

    ಆದರೆ (grabbed && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED)) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Get_ಕಿಟಕಿ_Keyboard_Grab(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ == _this->grabbed_ಕಿಟಕಿ && (_this->grabbed_ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED);
}

bool SDL_Get_ಕಿಟಕಿ_Mouse_Grab(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ == _this->grabbed_ಕಿಟಕಿ && (_this->grabbed_ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_GRABBED);
}

SDL_ಕಿಟಕಿ *SDL_Get_Grabbed_ಕಿಟಕಿ(ಶೂನ್ಯ)
{
    ಆದರೆ (_this && _this->grabbed_ಕಿಟಕಿ &&
        (_this->grabbed_ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MOUSE_GRABBED | SDL_ಕಿಟಕಿ_KEYBOARD_GRABBED)) != 0) {
        ಹಿಂತಿರುಗಿ _this->grabbed_ಕಿಟಕಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Mouse_Rect(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rect)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_Mouse_Rect) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ಆದರೆ (!rect) {
        rect = &zero;
    }

    ಆದರೆ (SDL_memcmp(&ಕಿಟಕಿ->mouse_rect, rect, ಗಾತ್ರ(*rect)) == 0) {
        ಹಿಂತಿರುಗಿ true;
    }
    SDL_memcpy(&ಕಿಟಕಿ->mouse_rect, rect, ಗಾತ್ರ(*rect));

    ಹಿಂತಿರುಗಿ _this->ಗಣ_ಕಿಟಕಿ_Mouse_Rect(_this, ಕಿಟಕಿ);
}

ಸ್ಥಿರಾಂಕ SDL_Rect *SDL_Get_ಕಿಟಕಿ_Mouse_Rect(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಖಾಲಿ);

    ಆದರೆ (SDL_Rect_ಖಾಲಿಗಳು(&ಕಿಟಕಿ->mouse_rect)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ &ಕಿಟಕಿ->mouse_rect;
    }
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Relative_Mouse_ಬಹುಲಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    ಆದರೆ (enabled == SDL_Get_ಕಿಟಕಿ_Relative_Mouse_ಬಹುಲಕ(ಕಿಟಕಿ)) {
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (enabled) {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ;
    }

    ಆದರೆ (!SDL_Update_Relative_Mouse_ಬಹುಲಕ()) {
        ಆದರೆ (enabled) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ;
        }
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Get_ಕಿಟಕಿ_Relative_Mouse_ಬಹುಲಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_RELATIVE_ಬಹುಲಕ) {
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ false;
    }
}

bool SDL_Flash_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (_this->Flash_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ _this->Flash_ಕಿಟಕಿ(_this, ಕಿಟಕಿ, operation);
    }

    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool SDL_ಗಣ_ಕಿಟಕಿ_ಪ್ರಗತಿ_State(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಪ್ರಗತಿ_State state)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    CHECK_PARAM(state < SDL_ಪ್ರಗತಿ_STATE_NONE || state > SDL_ಪ್ರಗತಿ_STATE_ERROR) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("state");
    }

    ಕಿಟಕಿ->ಪ್ರಗತಿ_state = state;

    ಆದರೆ (_this->Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ) {
        ಆದರೆ (!_this->Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ(_this, ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

SDL_ಪ್ರಗತಿ_State SDL_Get_ಕಿಟಕಿ_ಪ್ರಗತಿ_State(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, SDL_ಪ್ರಗತಿ_STATE_INVALID);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, SDL_ಪ್ರಗತಿ_STATE_INVALID);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->ಪ್ರಗತಿ_state;
}

bool SDL_ಗಣ_ಕಿಟಕಿ_ಪ್ರಗತಿ_ಮೌಲ್ಯ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ ಮೌಲ್ಯ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಮೌಲ್ಯ = SDL_clamp(ಮೌಲ್ಯ, 0.0f, 1.f);

    ಕಿಟಕಿ->ಪ್ರಗತಿ_ಮೌಲ್ಯ = ಮೌಲ್ಯ;

    ಆದರೆ (_this->Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ) {
        ಆದರೆ (!_this->Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ(_this, ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ದಶಮಾಂಶ SDL_Get_ಕಿಟಕಿ_ಪ್ರಗತಿ_ಮೌಲ್ಯ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, -1.0f);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, -1.0f);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->ಪ್ರಗತಿ_ಮೌಲ್ಯ;
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Shown(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Set window state if we have pending window flags cached
    Apply_ಕಿಟಕಿ_Flags(ಕಿಟಕಿ, ಕಿಟಕಿ->pending_flags);
    ಕಿಟಕಿ->pending_flags = 0;
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Hidden(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    ಕಿಟಕಿ->pending_flags |= (ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_LEAVE, false);
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Display_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    ಆದರೆ (ಕಿಟಕಿ->update_fullscreen_on_display_ಬದಲಾಯಿತು && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
        ಸ್ಥಿರಾಂಕ bool auto_ಬಹುಲಕ_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_ಹೊಂದಿಕೆ_EXCLUSIVE_ಬಹುಲಕ_ON_MOVE, true);

        ಆದರೆ (auto_ಬಹುಲಕ_switch && (ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.w != 0 || ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_ಕಿಟಕಿ_Position(ಕಿಟಕಿ);
            bool include_ಮೇಲಿನ_density_modes = false;

            ಆದರೆ (ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.pixel_density > 1.0f) {
                include_ಮೇಲಿನ_density_modes = true;
            }
            ಸ್ಥಿರಾಂಕ bool ಸಿಕ್ಕಿತು_ಹೊಂದಿಕೆ = SDL_Get_Closest_Fullscreen_Display_ಬಹುಲಕ(displayID, ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.w, ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.h,
                                                                         ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.refresh_ದರ, include_ಮೇಲಿನ_density_modes, &ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ಆದರೆ (!ಸಿಕ್ಕಿತು_ಹೊಂದಿಕೆ ||
                ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.w != ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w ||
                ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ.h != ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.h) {
                SDL_zero(ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_zero(ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ);
        }

        ಆದರೆ (SDL_ಕಿಟಕಿ_FULLSCREEN_VISIBLE(ಕಿಟಕಿ)) {
            SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_ಕಿಟಕಿ_Pixel_ಗಾತ್ರ_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Moved(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Check_ಕಿಟಕಿ_Display_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Resized(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Check_ಕಿಟಕಿ_Display_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
    SDL_Check_ಕಿಟಕಿ_Pixel_ಗಾತ್ರ_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
    SDL_Check_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_ಬದಲಾಯಿತು(ಕಿಟಕಿ);

    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) && _this->Update_ಕಿಟಕಿ_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_ಸೂಚಕ_Property(ಕಿಟಕಿ->props, SDL_PROP_ಕಿಟಕಿ_SHAPE_ಸೂಚಕ, ಖಾಲಿ);
        ಆದರೆ (surface) {
            _this->Update_ಕಿಟಕಿ_Shape(_this, ಕಿಟಕಿ, surface);
        }
    }
}

ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_Pixel_ಗಾತ್ರ_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಪೂರ್ಣಾಂಕ pixel_w = 0, pixel_h = 0;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &pixel_w, &pixel_h);
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_PIXEL_ಗಾತ್ರ_ಬದಲಾಯಿತು, pixel_w, pixel_h);

    SDL_Check_ಕಿಟಕಿ_Display_Scale_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Pixel_ಗಾತ್ರ_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಕಿಟಕಿ->surface_valid = false;
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_ಜೀವಂತ_Resize_Update(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Send an expose event so the application can redraw
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_Check_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Rect rect;

    rect.x = ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ಎಡ;
    rect.y = ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ತುದಿ;
    rect.w = ಕಿಟಕಿ->w - (ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ಬಲ + ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ಎಡ);
    rect.h = ಕಿಟಕಿ->h - (ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ತುದಿ + ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_bottom);
    ಆದರೆ (SDL_memcmp(&rect, &ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_rect, ಗಾತ್ರ(rect)) != 0) {
        SDL_copyp(&ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_rect, &rect);
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_AREA_ಬದಲಾಯಿತು, 0, 0);
    }
}

ಶೂನ್ಯ SDL_ಗಣ_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_Insets(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ ಎಡ, ಪೂರ್ಣಾಂಕ ಬಲ, ಪೂರ್ಣಾಂಕ ತುದಿ, ಪೂರ್ಣಾಂಕ bottom)
{
    ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ಎಡ = ಎಡ;
    ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ಬಲ = ಬಲ;
    ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_ತುದಿ = ತುದಿ;
    ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_inset_bottom = bottom;
    SDL_Check_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area_ಬದಲಾಯಿತು(ಕಿಟಕಿ);
}

bool SDL_Get_ಕಿಟಕಿ_ಸುರಕ್ಷಿತ_Area(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Rect *rect)
{
    ಆದರೆ (rect) {
        SDL_zerop(rect);
    }

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (rect) {
        ಆದರೆ (SDL_Rect_ಖಾಲಿಗಳು(&ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_rect)) {
            rect->w = ಕಿಟಕಿ->w;
            rect->h = ಕಿಟಕಿ->h;
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_copyp(rect, &ಕಿಟಕಿ->ಸುರಕ್ಷಿತ_rect);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Minimized(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Maximized(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Restored(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) {
        SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Enter(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (_this->On_ಕಿಟಕಿ_Enter) {
        _this->On_ಕಿಟಕಿ_Enter(_this, ಕಿಟಕಿ);
    }
    SDL_Update_Relative_Mouse_ಬಹುಲಕ();
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Leave(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Update_Relative_Mouse_ಬಹುಲಕ();
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Focus_Gained(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ಆದರೆ (mouse && mouse->relative_ಬಹುಲಕ) {
        SDL_ಗಣ_Mouse_Focus(ಕಿಟಕಿ);
    }

    SDL_Update_ಕಿಟಕಿ_Grab(ಕಿಟಕಿ);
}

ಸ್ಥಿರ bool SDL_ShouldMinimizeOnFocusLoss(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint;

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) || ಕಿಟಕಿ->is_destroying) {
        ಹಿಂತಿರುಗಿ false;
    }

#ಆದರೆ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ಆದರೆ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ಆದರೆ (Cocoa_IsShowingModalDialog(ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (Cocoa_Is_ಕಿಟಕಿ_ಒಳ_Fullscreen_Space(ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_PLATFORM_ANDROID
    {
        ಬಾಹ್ಯ bool Android_JNI_ShouldMinimizeOnFocusLoss(ಶೂನ್ಯ);
        ಆದರೆ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ಆದರೆ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ಆದರೆ (ಕಿಟಕಿ->fullscreen_exclusive && !SDL_ಬಹುಲಕ_Switching_Emulated(_this)) {
            ಹಿಂತಿರುಗಿ true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಹಿಂತಿರುಗಿ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

ಶೂನ್ಯ SDL_On_ಕಿಟಕಿ_Focus_ಕಳೆದುಹೋದ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Update_ಕಿಟಕಿ_Grab(ಕಿಟಕಿ);

    ಆದರೆ (SDL_ShouldMinimizeOnFocusLoss(ಕಿಟಕಿ)) {
        SDL_Minimize_ಕಿಟಕಿ(ಕಿಟಕಿ);
    }
}

SDL_ಕಿಟಕಿ *SDL_GetToplevelForKeyboardFocus(ಶೂನ್ಯ)
{
    SDL_ಕಿಟಕಿ *focus = SDL_GetKeyboardFocus();

    ಆದರೆ (focus) {
        // Get the toplevel parent window.
        ಆಗ (focus->ಪೋಷಕ) {
            focus = focus->ಪೋಷಕ;
        }
    }

    ಹಿಂತಿರುಗಿ focus;
}

bool SDL_ಕೂಡಿಸು_ಕಿಟಕಿ_Renderer(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(ಕಿಟಕಿ->renderers, (ಕಿಟಕಿ->ಅಂಕೆ_renderers + 1) * ಗಾತ್ರ(*renderers));
    ಆದರೆ (!renderers) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಕಿಟಕಿ->renderers = renderers;
    ಕಿಟಕಿ->renderers[ಕಿಟಕಿ->ಅಂಕೆ_renderers++] = renderer;

    SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_RENDERER_ಸೂಚಕ, renderer);
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_Remove_ಕಿಟಕಿ_Renderer(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Renderer *renderer)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಕಿಟಕಿ->ಅಂಕೆ_renderers; ++i) {
        ಆದರೆ (ಕಿಟಕಿ->renderers[i] == renderer) {
            ಆದರೆ (i < (ಕಿಟಕಿ->ಅಂಕೆ_renderers - 1)) {
                SDL_memmove(&ಕಿಟಕಿ->renderers[i], &ಕಿಟಕಿ->renderers[i + 1], (ಕಿಟಕಿ->ಅಂಕೆ_renderers - i - 1) * ಗಾತ್ರ(ಕಿಟಕಿ->renderers[i]));
            }
            --ಕಿಟಕಿ->ಅಂಕೆ_renderers;
            ನಿಲ್ಲಿಸು;
        }
    }

    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    ಆದರೆ (SDL_Get_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_RENDERER_ಸೂಚಕ, ಖಾಲಿ) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_ಕಿಟಕಿ_RENDERER_ಸೂಚಕ);
    }
}

ಶೂನ್ಯ SDL_Destroy_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ,);

    ಕಿಟಕಿ->is_destroying = true;

    // Destroy any child windows of this window
    ಆಗ (ಕಿಟಕಿ->ಮೊದಲ_ಮಗು) {
        SDL_Destroy_ಕಿಟಕಿ(ಕಿಟಕಿ->ಮೊದಲ_ಮಗು);
    }

    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_DESTROYED, 0, 0);

    SDL_Destroy_ಕಿಟಕಿ_Surface(ಕಿಟಕಿ);

    SDL_Renderer *renderer = SDL_GetRenderer(ಕಿಟಕಿ);
    ಆದರೆ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_LEAVE, true);
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
        SDL_Hide_ಕಿಟಕಿ(ಕಿಟಕಿ);
    }

    SDL_DestroyProperties(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props);

    SDL_Destroy_ಕಿಟಕಿ_Texture(_this, ಕಿಟಕಿ);
    SDL_DestroyProperties(ಕಿಟಕಿ->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ಆದರೆ (_this->ಗಣ_ಕಿಟಕಿ_Modal && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MODAL)) {
        _this->ಗಣ_ಕಿಟಕಿ_Modal(_this, ಕಿಟಕಿ, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        ಆದರೆ (_this->displays[i]->fullscreen_ಕಿಟಕಿ == ಕಿಟಕಿ) {
            _this->displays[i]->fullscreen_ಕಿಟಕಿ = ಖಾಲಿ;
        }
    }

    // Make sure this window no longer has focus
    ಆದರೆ (SDL_GetKeyboardFocus() == ಕಿಟಕಿ) {
        SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
    }
    ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ಆದರೆ (SDL_GetMouseFocus() == ಕಿಟಕಿ) {
        SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
    }

    // Make no context current if this is the current context window
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        ಆದರೆ (_this->current_glwin == ಕಿಟಕಿ) {
            SDL_GL_MakeCurrent(ಕಿಟಕಿ, ಖಾಲಿ);
        }
    }

    ಆದರೆ (_this->Destroy_ಕಿಟಕಿ) {
        _this->Destroy_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ಆದರೆ (_this->grabbed_ಕಿಟಕಿ == ಕಿಟಕಿ) {
        _this->grabbed_ಕಿಟಕಿ = ಖಾಲಿ; // ungrabbing input.
    }

    ಆದರೆ (_this->current_glwin == ಕಿಟಕಿ) {
        _this->current_glwin = ಖಾಲಿ;
    }

    SDL_Compare_And_ಅದಲುಬದಲು_Atomic_ಸೂಚಕ(&_this->wakeup_ಕಿಟಕಿ, ಕಿಟಕಿ, ಖಾಲಿ);

    // Now invalidate magic
    SDL_ಗಣ_Object_Valid(ಕಿಟಕಿ, SDL_OBJECT_TYPE_ಕಿಟಕಿ, false);

    // Free memory associated with the window
    SDL_free(ಕಿಟಕಿ->title);
    SDL_DestroySurface(ಕಿಟಕಿ->icon);

    // Unlink the window from its siblings.
    SDL_Update_ಕಿಟಕಿ_Hierarchy(ಕಿಟಕಿ, ಖಾಲಿ);

    // Unlink the window from the global window list
    ಆದರೆ (ಕಿಟಕಿ->ಮುಂದಿನ) {
        ಕಿಟಕಿ->ಮುಂದಿನ->prev = ಕಿಟಕಿ->prev;
    }
    ಆದರೆ (ಕಿಟಕಿ->prev) {
        ಕಿಟಕಿ->prev->ಮುಂದಿನ = ಕಿಟಕಿ->ಮುಂದಿನ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        _this->windows = ಕಿಟಕಿ->ಮುಂದಿನ;
    }

    SDL_free(ಕಿಟಕಿ->renderers);
    SDL_free(ಕಿಟಕಿ);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#ಆದರೆ_ಅಂತ್ಯ
}

bool SDL_ScreenSaverEnabled(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }
    ಆದರೆ (!_this->suspend_screensaver) {
        ಹಿಂತಿರುಗಿ true;
    }
    _this->suspend_screensaver = false;
    ಆದರೆ (_this->SuspendScreenSaver) {
        ಹಿಂತಿರುಗಿ _this->SuspendScreenSaver(_this);
    }

    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }
    ಆದರೆ (_this->suspend_screensaver) {
        ಹಿಂತಿರುಗಿ true;
    }
    _this->suspend_screensaver = true;
    ಆದರೆ (_this->SuspendScreenSaver) {
        ಹಿಂತಿರುಗಿ _this->SuspendScreenSaver(_this);
    }

    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

ಶೂನ್ಯ SDL_QuitVideo(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ಆದರೆ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#ಆದರೆ_ಅಂತ್ಯ
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ಆಗ (_this->windows) {
        SDL_Destroy_ಕಿಟಕಿ(_this->windows);
    }

    ಆದರೆ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ಆದರೆ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    ಗಾಗಿ (i = _this->ಅಂಕೆ_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->ಅಂಕೆ_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ಖಾಲಿ;

    SDL_Cancel_Clipboard_ದತ್ತಾಂಶ(0);

    ಆದರೆ (_this->primary_selection_ಪಠ್ಯ) {
        SDL_free(_this->primary_selection_ಪಠ್ಯ);
        _this->primary_selection_ಪಠ್ಯ = ಖಾಲಿ;
    }
    _this->ಬಿಡುಗಡೆ(_this);
    _this = ಖಾಲಿ;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_ತುಂಬು_Library(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    bool ಫಲಿತಾಂಶ;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }
    ಆದರೆ (_this->gl_config.driver_loaded) {
        ಆದರೆ (ಮಾರ್ಗ && SDL_strcmp(ಮಾರ್ಗ, _this->gl_config.driver_ಮಾರ್ಗ) != 0) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenGL library already loaded");
        }
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!_this->GL_ತುಂಬು_Library) {
            ಹಿಂತಿರುಗಿ SDL_DllNotSupported("OpenGL");
        }
        ಫಲಿತಾಂಶ = _this->GL_ತುಂಬು_Library(_this, ಮಾರ್ಗ);
    }
    ಆದರೆ (ಫಲಿತಾಂಶ) {
        ++_this->gl_config.driver_loaded;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

SDL_Function_ಸೂಚಕ SDL_GL_Get_Proc_ವಿಳಾಸ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
    SDL_Function_ಸೂಚಕ func;

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    func = ಖಾಲಿ;
    ಆದರೆ (_this->GL_Get_Proc_ವಿಳಾಸ) {
        ಆದರೆ (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_ವಿಳಾಸ(_this, proc);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_ಗಣ_Error("No GL driver has been loaded");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ಹಿಂತಿರುಗಿ func;
}

SDL_Function_ಸೂಚಕ SDL_EGL_Get_Proc_ವಿಳಾಸ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *proc)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    SDL_Function_ಸೂಚಕ func;

    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    func = ಖಾಲಿ;

    ಆದರೆ (_this->egl_ದತ್ತಾಂಶ) {
        func = SDL_EGL_Get_Proc_ವಿಳಾಸ_ಆಂತರಿಕ(_this, proc);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("No EGL library has been loaded");
    }

    ಹಿಂತಿರುಗಿ func;
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಗಣ_Error("SDL was not built with EGL support");
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ SDL_GL_UnloadLibrary(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (_this->gl_config.driver_loaded > 0) {
        ಆದರೆ (--_this->gl_config.driver_loaded > 0) {
            ಹಿಂತಿರುಗಿ;
        }
        ಆದರೆ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ಆದರೆ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ GLenum (APIENTRY* PFNGLGETERRORPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿರಾಂಕ GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_VIDEO_OPENGL
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಸ್ಥಿರಾಂಕ GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint ಸೂಚ್ಯಂಕ);
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ SDL_INLINE bool is_At_ಕನಿಷ್ಠ_GL3(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *verstr)
{
    ಹಿಂತಿರುಗಿ verstr && (SDL_atoi(verstr) >= 3);
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extension)
{
#ಆದರೆ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *extensions;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಆರಂಭ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ಆದರೆ (where || *extension == '\0') {
        ಹಿಂತಿರುಗಿ false;
    }
    // See if there's a hint or environment variable override
    ಆರಂಭ = SDL_GetHint(extension);
    ಆದರೆ (ಆರಂಭ && *ಆರಂಭ == '0') {
        ಹಿಂತಿರುಗಿ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetString");
    ಆದರೆ (!glGetStringFunc) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (is_At_ಕನಿಷ್ಠ_GL3((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)glGetStringFunc(GL_ಆವೃತ್ತಿ))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint ಅಂಕೆ_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetIntegerv");
        ಆದರೆ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ಹಿಂತಿರುಗಿ false;
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GL_ಅಂಕೆ_EXTENSIONS
#ವ್ಯಾಖ್ಯಾನಿಸು GL_ಅಂಕೆ_EXTENSIONS 0x821D
#ಆದರೆ_ಅಂತ್ಯ
        glGetIntegervFunc(GL_ಅಂಕೆ_EXTENSIONS, &ಅಂಕೆ_exts);
        ಗಾಗಿ (i = 0; i < ಅಂಕೆ_exts; i++) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *thisext = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)glGetStringiFunc(GL_EXTENSIONS, i);
            ಆದರೆ (SDL_strcmp(thisext, extension) == 0) {
                ಹಿಂತಿರುಗಿ true;
            }
        }

        ಹಿಂತಿರುಗಿ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)glGetStringFunc(GL_EXTENSIONS);
    ಆದರೆ (!extensions) {
        ಹಿಂತಿರುಗಿ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    ಆರಂಭ = extensions;

    ಗಾಗಿ (;;) {
        where = SDL_strstr(ಆರಂಭ, extension);
        ಆದರೆ (!where) {
            ನಿಲ್ಲಿಸು;
        }

        terminator = where + SDL_strlen(extension);
        ಆದರೆ (where == extensions || *(where - 1) == ' ') {
            ಆದರೆ (*terminator == ' ' || *terminator == '\0') {
                ಹಿಂತಿರುಗಿ true;
            }
        }

        ಆರಂಭ = terminator;
    }
    ಹಿಂತಿರುಗಿ false;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ false;
#ಆದರೆ_ಅಂತ್ಯ
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
ಶೂನ್ಯ SDL_GL_DeduceMaxSupportedESProfile(ಪೂರ್ಣಾಂಕ *major, ಪೂರ್ಣಾಂಕ *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#ಆದರೆ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ಆದರೆ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *major = 2;
        *minor = 0;
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ SDL_EGL_ಗಣ_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   ಶೂನ್ಯ *userdata)
{
    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

ಶೂನ್ಯ SDL_GL_Reset_ಗುಣಲಕ್ಷಣಗಳು(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ;
    }

    _this->egl_platformattrib_callback = ಖಾಲಿ;
    _this->egl_surfaceattrib_callback = ಖಾಲಿ;
    _this->egl_contextattrib_callback = ಖಾಲಿ;
    _this->egl_attrib_callback_userdata = ಖಾಲಿ;

    _this->gl_config.red_ಗಾತ್ರ = 8;
    _this->gl_config.green_ಗಾತ್ರ = 8;
    _this->gl_config.blue_ಗಾತ್ರ = 8;
    _this->gl_config.alpha_ಗಾತ್ರ = 8;
    _this->gl_config.ಬಫರ್_ಗಾತ್ರ = 0;
    _this->gl_config.ಆಳ_ಗಾತ್ರ = 16;
    _this->gl_config.stencil_ಗಾತ್ರ = 0;
    _this->gl_config.double_ಬಫರ್ = 1;
    _this->gl_config.accum_red_ಗಾತ್ರ = 0;
    _this->gl_config.accum_green_ಗಾತ್ರ = 0;
    _this->gl_config.accum_blue_ಗಾತ್ರ = 0;
    _this->gl_config.accum_alpha_ಗಾತ್ರ = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    _this->gl_config.major_ಆವೃತ್ತಿ = 2;
    _this->gl_config.minor_ಆವೃತ್ತಿ = 1;
    _this->gl_config.profile_ಮುಖವಾಡ = 0;
#ಅಥವಾಆದರೆ defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_ಆವೃತ್ತಿ = 2;
    _this->gl_config.minor_ಆವೃತ್ತಿ = 0;
    _this->gl_config.profile_ಮುಖವಾಡ = SDL_GL_CONTEXT_PROFILE_ES;
#ಅಥವಾಆದರೆ defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_ಆವೃತ್ತಿ = 1;
    _this->gl_config.minor_ಆವೃತ್ತಿ = 1;
    _this->gl_config.profile_ಮುಖವಾಡ = SDL_GL_CONTEXT_PROFILE_ES;
#ಆದರೆ_ಅಂತ್ಯ

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    ಆದರೆ (_this->GL_ಗಣ_Default_Profile_Config) {
        _this->GL_ಗಣ_Default_Profile_Config(_this);
    }
}

bool SDL_GL_ಗಣ_Attribute(SDL_GLAttr attr, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ)
{
#ಆದರೆ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool ಫಲಿತಾಂಶ;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }
    ಫಲಿತಾಂಶ = true;
    ಆಯ್ಕೆ (attr) {
    ಸ್ಥಿತಿ SDL_GL_RED_ಗಾತ್ರ:
        _this->gl_config.red_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_GREEN_ಗಾತ್ರ:
        _this->gl_config.green_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_BLUE_ಗಾತ್ರ:
        _this->gl_config.blue_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ALPHA_ಗಾತ್ರ:
        _this->gl_config.alpha_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_ಬಫರ್ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ಬಫರ್_ಗಾತ್ರ:
        _this->gl_config.ಬಫರ್_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ಆಳ_ಗಾತ್ರ:
        _this->gl_config.ಆಳ_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_STENCIL_ಗಾತ್ರ:
        _this->gl_config.stencil_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCUM_RED_ಗಾತ್ರ:
        _this->gl_config.accum_red_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCUM_GREEN_ಗಾತ್ರ:
        _this->gl_config.accum_green_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCUM_BLUE_ಗಾತ್ರ:
        _this->gl_config.accum_blue_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCUM_ALPHA_ಗಾತ್ರ:
        _this->gl_config.accum_alpha_ಗಾತ್ರ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_STEREO:
        _this->gl_config.stereo = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_MAJOR_ಆವೃತ್ತಿ:
        _this->gl_config.major_ಆವೃತ್ತಿ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_MINOR_ಆವೃತ್ತಿ:
        _this->gl_config.minor_ಆವೃತ್ತಿ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_FLAGS:
        ಆದರೆ (ಮೌಲ್ಯ & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Unknown OpenGL context flag %d", ಮೌಲ್ಯ);
            ನಿಲ್ಲಿಸು;
        }
        _this->gl_config.flags = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_PROFILE_ಮುಖವಾಡ:
        ಆದರೆ (ಮೌಲ್ಯ != 0 &&
            ಮೌಲ್ಯ != SDL_GL_CONTEXT_PROFILE_CORE &&
            ಮೌಲ್ಯ != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            ಮೌಲ್ಯ != SDL_GL_CONTEXT_PROFILE_ES) {
            ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Unknown OpenGL context profile %d", ಮೌಲ್ಯ);
            ನಿಲ್ಲಿಸು;
        }
        _this->gl_config.profile_ಮುಖವಾಡ = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = ಮೌಲ್ಯ;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಫಲಿತಾಂಶ = SDL_ಗಣ_Error("Unknown OpenGL attribute");
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, ಪೂರ್ಣಾಂಕ *ಮೌಲ್ಯ)
{
#ಆದರೆ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_ಹಿಂಭಾಗ_ಎಡ;
    GLenum attachmentattrib = 0;
#ಆದರೆ_ಅಂತ್ಯ

    CHECK_PARAM(!ಮೌಲ್ಯ) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *ಮೌಲ್ಯ = 0;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    ಆಯ್ಕೆ (attr) {
    ಸ್ಥಿತಿ SDL_GL_RED_ಗಾತ್ರ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_ಗಾತ್ರ;
#ಆದರೆ_ಅಂತ್ಯ
        attrib = GL_RED_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_BLUE_ಗಾತ್ರ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_ಗಾತ್ರ;
#ಆದರೆ_ಅಂತ್ಯ
        attrib = GL_BLUE_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_GREEN_ಗಾತ್ರ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_ಗಾತ್ರ;
#ಆದರೆ_ಅಂತ್ಯ
        attrib = GL_GREEN_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ALPHA_ಗಾತ್ರ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_ಗಾತ್ರ;
#ಆದರೆ_ಅಂತ್ಯ
        attrib = GL_ALPHA_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_DOUBLEBUFFER:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        ನಿಲ್ಲಿಸು;
#ಇಲ್ಲದಿದ್ದರೆ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *ಮೌಲ್ಯ = _this->gl_config.double_ಬಫರ್;
        ಹಿಂತಿರುಗಿ true;
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ SDL_GL_ಆಳ_ಗಾತ್ರ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        attachment = GL_ಆಳ;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ಆಳ_ಗಾತ್ರ;
#ಆದರೆ_ಅಂತ್ಯ
        attrib = GL_ಆಳ_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_STENCIL_ಗಾತ್ರ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_ಗಾತ್ರ;
#ಆದರೆ_ಅಂತ್ಯ
        attrib = GL_STENCIL_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    ಸ್ಥಿತಿ SDL_GL_ACCUM_RED_ಗಾತ್ರ:
        attrib = GL_ACCUM_RED_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCUM_GREEN_ಗಾತ್ರ:
        attrib = GL_ACCUM_GREEN_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCUM_BLUE_ಗಾತ್ರ:
        attrib = GL_ACCUM_BLUE_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ACCUM_ALPHA_ಗಾತ್ರ:
        attrib = GL_ACCUM_ALPHA_ಬಿಟ್ಟುಗಳು;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_STEREO:
        attrib = GL_STEREO;
        ನಿಲ್ಲಿಸು;
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿತಿ SDL_GL_ACCUM_RED_ಗಾತ್ರ:
    ಸ್ಥಿತಿ SDL_GL_ACCUM_GREEN_ಗಾತ್ರ:
    ಸ್ಥಿತಿ SDL_GL_ACCUM_BLUE_ಗಾತ್ರ:
    ಸ್ಥಿತಿ SDL_GL_ACCUM_ALPHA_ಗಾತ್ರ:
    ಸ್ಥಿತಿ SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *ಮೌಲ್ಯ = 0;
        ಹಿಂತಿರುಗಿ true;
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_GL_ಬಫರ್_ಗಾತ್ರ:
    {
        ಪೂರ್ಣಾಂಕ rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        ಆದರೆ (!SDL_GL_GetAttribute(SDL_GL_RED_ಗಾತ್ರ, &rsize)) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ (!SDL_GL_GetAttribute(SDL_GL_GREEN_ಗಾತ್ರ, &gsize)) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ (!SDL_GL_GetAttribute(SDL_GL_BLUE_ಗಾತ್ರ, &bsize)) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_ಗಾತ್ರ, &asize)) {
            ಹಿಂತಿರುಗಿ false;
        }

        *ಮೌಲ್ಯ = rsize + gsize + bsize + asize;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *ಮೌಲ್ಯ = (_this->gl_config.accelerated != 0);
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_RETAINED_BACKING:
    {
        *ಮೌಲ್ಯ = _this->gl_config.retained_backing;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_MAJOR_ಆವೃತ್ತಿ:
    {
        *ಮೌಲ್ಯ = _this->gl_config.major_ಆವೃತ್ತಿ;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_MINOR_ಆವೃತ್ತಿ:
    {
        *ಮೌಲ್ಯ = _this->gl_config.minor_ಆವೃತ್ತಿ;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_FLAGS:
    {
        *ಮೌಲ್ಯ = _this->gl_config.flags;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_PROFILE_ಮುಖವಾಡ:
    {
        *ಮೌಲ್ಯ = _this->gl_config.profile_ಮುಖವಾಡ;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *ಮೌಲ್ಯ = _this->gl_config.share_with_current_context;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *ಮೌಲ್ಯ = _this->gl_config.framebuffer_srgb_capable;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_CONTEXT_NO_ERROR:
    {
        *ಮೌಲ್ಯ = _this->gl_config.no_error;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_EGL_PLATFORM:
    {
        *ಮೌಲ್ಯ = _this->gl_config.egl_platform;
        ಹಿಂತಿರುಗಿ true;
    }
    ಸ್ಥಿತಿ SDL_GL_FLOATBUFFERS:
    {
        ಆದರೆ (_this->gl_config.HAS_GL_ARB_color_ಬಫರ್_float) {
            attrib = GL_RGBA_FLOAT_ಬಹುಲಕ_ARB;
            ನಿಲ್ಲಿಸು;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ 0;
        }
    }
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unknown OpenGL attribute");
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetString");
    ಆದರೆ (!glGetStringFunc) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (attachmentattrib && is_At_ಕನಿಷ್ಠ_GL3((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)glGetStringFunc(GL_ಆವೃತ್ತಿ))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_ವಿಳಾಸ("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glBindFramebuffer");
        ಆದರೆ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetFramebufferAttachmentParameteriv");
        ಆದರೆ (glGetFramebufferAttachmentParameterivFunc) {
            ಆದರೆ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ಆದರೆ (attachment == GL_ಆಳ || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ಆದರೆ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)ಮೌಲ್ಯ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                *ಮೌಲ್ಯ = 0;
            }
            ಆದರೆ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetIntegerv");
        ಆದರೆ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)ಮೌಲ್ಯ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetError");
    ಆದರೆ (!glGetErrorFunc) {
        ಹಿಂತಿರುಗಿ false;
    }

    error = glGetErrorFunc();
    ಆದರೆ (error != GL_NO_ERROR) {
        ಆದರೆ (error == GL_INVALID_ENUM) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenGL error: GL_INVALID_ENUM");
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (error == GL_INVALID_ಮೌಲ್ಯ) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenGL error: GL_INVALID_VALUE");
        }
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ಆದರೆ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *ಮೌಲ್ಯ = (*ಮೌಲ್ಯ == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_OPENGL
}

#ವ್ಯಾಖ್ಯಾನಿಸು NOT_AN_OPENGL_ಕಿಟಕಿ "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_GLContext ctx = ಖಾಲಿ;
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಖಾಲಿ);

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL)) {
        SDL_ಗಣ_Error(NOT_AN_OPENGL_ಕಿಟಕಿ);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

#ಆದರೆ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ಪೂರ್ಣಾಂಕ srgb_requested = -1;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ಆದರೆ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#ಆದರೆ_ಅಂತ್ಯ

    ctx = _this->GL_CreateContext(_this, ಕಿಟಕಿ);

    // Creating a context is assumed to make it current in the SDL driver.
    ಆದರೆ (ctx) {
        _this->current_glwin = ಕಿಟಕಿ;
        _this->current_glctx = ctx;
        SDL_ಗಣ_TLS(&_this->current_glwin_tls, ಕಿಟಕಿ, ಖಾಲಿ);
        SDL_ಗಣ_TLS(&_this->current_glctx_tls, ctx, ಖಾಲಿ);
    }

#ಆದರೆ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ಆದರೆ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_ವಿಳಾಸ(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_ವಿಳಾಸ("glGetString");
        ಆದರೆ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ಆದರೆ (_this->gl_config.profile_ಮುಖವಾಡ & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ಇಲ್ಲದಿದ್ದರೆ {
                supported = is_At_ಕನಿಷ್ಠ_GL3((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)glGetStringFunc(GL_ಆವೃತ್ತಿ)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ಆದರೆ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ ctx;
}

bool SDL_GL_MakeCurrent(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_GLContext context)
{
    bool ಫಲಿತಾಂಶ;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }

    ಆದರೆ (ಕಿಟಕಿ == SDL_GL_Get_Current_ಕಿಟಕಿ() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ಹಿಂತಿರುಗಿ true;
    }

    ಆದರೆ (!context) {
        ಕಿಟಕಿ = ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ) {
        CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL)) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(NOT_AN_OPENGL_ಕಿಟಕಿ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!_this->gl_allow_no_surface) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Use of OpenGL without a window is not supported on this platform");
    }

    ಫಲಿತಾಂಶ = _this->GL_MakeCurrent(_this, ಕಿಟಕಿ, context);
    ಆದರೆ (ಫಲಿತಾಂಶ) {
        _this->current_glwin = ಕಿಟಕಿ;
        _this->current_glctx = context;
        SDL_ಗಣ_TLS(&_this->current_glwin_tls, ಕಿಟಕಿ, ಖಾಲಿ);
        SDL_ಗಣ_TLS(&_this->current_glctx_tls, context, ಖಾಲಿ);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

SDL_ಕಿಟಕಿ *SDL_GL_Get_Current_ಕಿಟಕಿ(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ (SDL_ಕಿಟಕಿ *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ EGL_NO_DISPLAY;
    }
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        SDL_ಗಣ_Error("There is no current EGL display");
        ಹಿಂತಿರುಗಿ EGL_NO_DISPLAY;
    }
    ಹಿಂತಿರುಗಿ _this->egl_ದತ್ತಾಂಶ->egl_display;
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಗಣ_Error("SDL was not built with EGL support");
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        SDL_ಗಣ_Error("There is no current EGL display");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ _this->egl_ದತ್ತಾಂಶ->egl_config;
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಗಣ_Error("SDL was not built with EGL support");
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
}

SDL_EGLConfig SDL_EGL_Get_ಕಿಟಕಿ_Surface(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (!_this->egl_ದತ್ತಾಂಶ) {
        SDL_ಗಣ_Error("There is no current EGL display");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (_this->GL_GetEGLSurface) {
        ಹಿಂತಿರುಗಿ _this->GL_GetEGLSurface(_this, ಕಿಟಕಿ);
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಗಣ_Error("SDL was not built with EGL support");
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
}

bool SDL_GL_ಗಣ_ಅದಲುಬದಲು_Interval(ಪೂರ್ಣಾಂಕ interval)
{
    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_GL_GetCurrentContext() == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No OpenGL context has been made current");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->GL_ಗಣ_ಅದಲುಬದಲು_Interval) {
        ಹಿಂತಿರುಗಿ _this->GL_ಗಣ_ಅದಲುಬದಲು_Interval(_this, interval);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_ಅದಲುಬದಲು_Interval(ಪೂರ್ಣಾಂಕ *interval)
{
    CHECK_PARAM(!interval) {
       ಹಿಂತಿರುಗಿ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("no video driver");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_GL_GetCurrentContext() == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("no current context");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (_this->GL_Get_ಅದಲುಬದಲು_Interval) {
        ಹಿಂತಿರುಗಿ _this->GL_Get_ಅದಲುಬದಲು_Interval(_this, interval);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("not implemented");
    }
}

bool SDL_GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error(NOT_AN_OPENGL_ಕಿಟಕಿ);
    }

    ಆದರೆ (SDL_GL_Get_Current_ಕಿಟಕಿ() != ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("The specified window has not been made current");
    }

    ಹಿಂತಿರುಗಿ _this->GL_ಅದಲುಬದಲು_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("context");
    }

    ಆದರೆ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ಖಾಲಿ, ಖಾಲಿ);
    }

    ಹಿಂತಿರುಗಿ _this->GL_DestroyContext(_this, context);
}

#ಆದರೆ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ಸ್ಥಿರ ಶೂನ್ಯ Create_ಮುಖವಾಡ_From_Color_ಕೀಲಿ_Or_Alpha(SDL_Surface *icon, Uint8 *ಮುಖವಾಡ, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ x, y;
    Uint32 colorkey;
#ವ್ಯಾಖ್ಯಾನಿಸು ಗಣ_MASKBIT(icon, x, y, ಮುಖವಾಡ) \
    ಮುಖವಾಡ[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    ಆಯ್ಕೆ (SDL_BYTESPERPIXEL(icon->format)) {
    ಸ್ಥಿತಿ 1:
        {
            Uint8 *pixels;
            ಗಾಗಿ (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                ಗಾಗಿ (x = 0; x < icon->w; ++x) {
                    ಆದರೆ (*pixels++ == colorkey) {
                        ಗಣ_MASKBIT(icon, x, y, ಮುಖವಾಡ);
                    }
                }
            }
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ 2:
        {
            Uint16 *pixels;
            ಗಾಗಿ (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                ಗಾಗಿ (x = 0; x < icon->w; ++x) {
                    ಆದರೆ ((flags & 1) && *pixels == colorkey) {
                        ಗಣ_MASKBIT(icon, x, y, ಮುಖವಾಡ);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        ಗಣ_MASKBIT(icon, x, y, ಮುಖವಾಡ);
                    }
                    pixels++;
                }
            }
        }
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ 4:
        {
            Uint32 *pixels;
            ಗಾಗಿ (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                ಗಾಗಿ (x = 0; x < icon->w; ++x) {
                    ಆದರೆ ((flags & 1) && *pixels == colorkey) {
                        ಗಣ_MASKBIT(icon, x, y, ಮುಖವಾಡ);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        ಗಣ_MASKBIT(icon, x, y, ಮುಖವಾಡ);
                    }
                    pixels++;
                }
            }
        }
        ನಿಲ್ಲಿಸು;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
ಶೂನ್ಯ SDL_WM_ಗಣ_Icon(SDL_Surface *icon, Uint8 *ಮುಖವಾಡ)
{
    ಆದರೆ (icon && _this->ಗಣ_Icon) {
        // Generate a mask if necessary, and create the icon!
        ಆದರೆ (ಮುಖವಾಡ == ಖಾಲಿ) {
            ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ_len = icon->h * (icon->w + 7) / 8;
            ಪೂರ್ಣಾಂಕ flags = 0;
            ಮುಖವಾಡ = (Uint8 *) SDL_malloc(ಮುಖವಾಡ_len);
            ಆದರೆ (ಮುಖವಾಡ == ಖಾಲಿ) {
                ಹಿಂತಿರುಗಿ;
            }
            SDL_memset(ಮುಖವಾಡ, ~0, ಮುಖವಾಡ_len);
            ಆದರೆ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ಆದರೆ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ಆದರೆ (flags) {
                Create_ಮುಖವಾಡ_From_Color_ಕೀಲಿ_Or_Alpha(icon, ಮುಖವಾಡ, flags);
            }
            _this->ಗಣ_Icon(_this, icon, ಮುಖವಾಡ);
            SDL_free(ಮುಖವಾಡ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            _this->ಗಣ_Icon(_this, icon, ಮುಖವಾಡ);
        }
    }
}
#ಆದರೆ_ಅಂತ್ಯ

SDL_ಪಠ್ಯ_ಒಳಹರಿವು_Type SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(SDL_PropertiesID props)
{
    ಹಿಂತಿರುಗಿ (SDL_ಪಠ್ಯ_ಒಳಹರಿವು_Type)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ, SDL_TEXTINPUT_TYPE_ಪಠ್ಯ);
}

SDL_Capitalization SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Capitalization(SDL_PropertiesID props)
{
    ಆದರೆ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ಸಂಖ್ಯೆ)) {
        ಹಿಂತಿರುಗಿ (SDL_Capitalization)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ಸಂಖ್ಯೆ, SDL_CAPITALIZE_NONE);
    }

    ಆಯ್ಕೆ (SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Type(props)) {
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ:
        ಹಿಂತಿರುಗಿ SDL_CAPITALIZE_SENTENCES;
    ಸ್ಥಿತಿ SDL_TEXTINPUT_TYPE_ಪಠ್ಯ_NAME:
        ಹಿಂತಿರುಗಿ SDL_CAPITALIZE_ಪದಗಳು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Autocorrect(SDL_PropertiesID props)
{
    ಹಿಂತಿರುಗಿ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Multiline(SDL_PropertiesID props)
{
    ಆದರೆ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ಹಿಂತಿರುಗಿ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_RETURN_ಕೀಲಿ_HIDES_IME, false)) {
        ಹಿಂತಿರುಗಿ false;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ true;
    }
}

ಸ್ಥಿರ bool AutoShowingScreenKeyboard(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ಆದರೆ (!hint) {
        // This hint is currently only used by the X11 video driver
        ಆದರೆ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ಆದರೆ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ false;
    }
}

bool SDL_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ SDL_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು_With_Properties(ಕಿಟಕಿ, 0);
}

bool SDL_ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು_With_Properties(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID props)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props) {
        SDL_DestroyProperties(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props);
        ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props = 0;
    }

    ಆದರೆ (props) {
        ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props = SDL_CreateProperties();
        ಆದರೆ (!ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props) {
            ಹಿಂತಿರುಗಿ false;
        }
        ಆದರೆ (!SDL_CopyProperties(props, ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_props)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }

    ಆದರೆ (_this->ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Properties) {
        _this->ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Properties(_this, ಕಿಟಕಿ, props);
    }

    ಆದರೆ (!ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ) {
        // Start the text input system
        ಆದರೆ (_this->ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು) {
            ಆದರೆ (!_this->ಆರಂಭ_ಪಠ್ಯ_ಒಳಹರಿವು(_this, ಕಿಟಕಿ, props)) {
                ಹಿಂತಿರುಗಿ false;
            }
        }
        ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ = true;
    }

    // Show the on-screen keyboard, if desired
    ಆದರೆ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(ಕಿಟಕಿ)) {
        ಆದರೆ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, ಕಿಟಕಿ, props);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ;
}

bool SDL_Stop_ಪಠ್ಯ_ಒಳಹರಿವು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ) {
        // Stop the text input system
        ಆದರೆ (_this->Stop_ಪಠ್ಯ_ಒಳಹರಿವು) {
            _this->Stop_ಪಠ್ಯ_ಒಳಹರಿವು(_this, ಕಿಟಕಿ);
        }
        ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_ಸಕ್ರಿಯ = false;
    }

    // Hide the on-screen keyboard, if desired
    ಆದರೆ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(ಕಿಟಕಿ)) {
        ಆದರೆ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, ಕಿಟಕಿ);
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ಗಣ_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rect, ಪೂರ್ಣಾಂಕ cursor)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (rect) {
        SDL_copyp(&ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect, rect);
        ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor = cursor;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_zero(ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect);
        ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor = 0;
    }

    ಆದರೆ (_this && _this->Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area) {
        ಆದರೆ (!_this->Update_ಪಠ್ಯ_ಒಳಹರಿವು_Area(_this, ಕಿಟಕಿ)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_Get_ಪಠ್ಯ_ಒಳಹರಿವು_Area(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Rect *rect, ಪೂರ್ಣಾಂಕ *cursor)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (rect) {
        SDL_copyp(rect, &ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_rect);
    }
    ಆದರೆ (cursor) {
        *cursor = ಕಿಟಕಿ->ಪಠ್ಯ_ಒಳಹರಿವು_cursor;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_ClearComposition(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (_this->ClearComposition) {
        ಹಿಂತಿರುಗಿ _this->ClearComposition(_this, ಕಿಟಕಿ);
    }
    ಹಿಂತಿರುಗಿ true;
}

bool SDL_HasScreenKeyboardSupport(ಶೂನ್ಯ)
{
    ಆದರೆ (_this && _this->HasScreenKeyboardSupport) {
        ಹಿಂತಿರುಗಿ _this->HasScreenKeyboardSupport(_this);
    }
    ಹಿಂತಿರುಗಿ false;
}

bool SDL_ScreenKeyboardShown(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಹಿಂತಿರುಗಿ _this->screen_keyboard_shown;
}

ಶೂನ್ಯ SDL_SendScreenKeyboardShown(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this || _this->screen_keyboard_shown) {
        ಹಿಂತಿರುಗಿ;
    }

    _this->screen_keyboard_shown = true;

    ಆದರೆ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ತಳ್ಳು_Event(&event);
    }
}

ಶೂನ್ಯ SDL_SendScreenKeyboardHidden(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this || !_this->screen_keyboard_shown) {
        ಹಿಂತಿರುಗಿ;
    }

    _this->screen_keyboard_shown = false;

    ಆದರೆ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ತಳ್ಳು_Event(&event);
    }
}

ಪೂರ್ಣಾಂಕ SDL_Get_ಸಂದೇಶ_Box_ಎಣಿಕೆ(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_GetAtomicInt(&SDL_messagebox_ಎಣಿಕೆ);
}

bool SDL_Show_ಸಂದೇಶ_Box(ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ *messageboxdata, ಪೂರ್ಣಾಂಕ *buttonID)
{
    ಪೂರ್ಣಾಂಕ dummybutton;
    bool ಫಲಿತಾಂಶ = false;
    bool show_cursor_prev;
    SDL_ಕಿಟಕಿ *current_ಕಿಟಕಿ;
    SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ mbdata;

    CHECK_PARAM(!messageboxdata) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    ಅಕ್ಷರ *titlecpy = ಖಾಲಿ;
    ಅಕ್ಷರ *msgcpy = ಖಾಲಿ;
    ಆದರೆ (messageboxdata->title) {
        ಸ್ಥಿರಾಂಕ size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(ಅಕ್ಷರ, slen, &titleisstack);
        ಆದರೆ (!titlecpy) {
            ಹಿಂತಿರುಗಿ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ಆದರೆ (messageboxdata->ಸಂದೇಶ) {
        ಸ್ಥಿರಾಂಕ size_t slen = SDL_strlen(messageboxdata->ಸಂದೇಶ) + 1;
        msgcpy = SDL_small_alloc(ಅಕ್ಷರ, slen, &msgisstack);
        ಆದರೆ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ಹಿಂತಿರುಗಿ false;
        }
        SDL_memcpy(msgcpy, messageboxdata->ಸಂದೇಶ, slen);
    }

    (ಶೂನ್ಯ)SDL_AtomicIncRef(&SDL_messagebox_ಎಣಿಕೆ);

    current_ಕಿಟಕಿ = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_ಗಣ_Relative_Mouse_ಬಹುಲಕ(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    ಆದರೆ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, ಗಾತ್ರ(*messageboxdata));
    mbdata.title = titlecpy;
    ಆದರೆ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.ಸಂದೇಶ = msgcpy;
    ಆದರೆ (!mbdata.ಸಂದೇಶ) {
        mbdata.ಸಂದೇಶ = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ಆದರೆ (_this && _this->Show_ಸಂದೇಶ_Box) {
        ಫಲಿತಾಂಶ = _this->Show_ಸಂದೇಶ_Box(_this, messageboxdata, buttonID);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // It's completely fine to call this function before video is initialized
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ಆದರೆ (driver_name && *driver_name != 0) {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *driver_attempt = driver_name;
            ಆಗ (driver_attempt && (*driver_attempt != 0) && !ಫಲಿತಾಂಶ) {
                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *driver_attempt_ಕೊನೆ = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_ಕೊನೆ) ? (driver_attempt_ಕೊನೆ - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; bootstrap[i]; ++i) {
                    ಆದರೆ (bootstrap[i]->Show_ಸಂದೇಶ_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ಆದರೆ (bootstrap[i]->Show_ಸಂದೇಶ_Box(messageboxdata, buttonID)) {
                            ಫಲಿತಾಂಶ = true;
                        }
                        ನಿಲ್ಲಿಸು;
                    }
                }

                driver_attempt = (driver_attempt_ಕೊನೆ) ? (driver_attempt_ಕೊನೆ + 1) : ಖಾಲಿ;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; bootstrap[i]; ++i) {
                ಆದರೆ (bootstrap[i]->Show_ಸಂದೇಶ_Box && bootstrap[i]->Show_ಸಂದೇಶ_Box(messageboxdata, buttonID)) {
                    ಫಲಿತಾಂಶ = true;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
    }

    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *error = SDL_GetError();

        ಆದರೆ (!*error) {
            SDL_ಗಣ_Error("No message system available");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ClearError();
    }

    (ಶೂನ್ಯ)SDL_AtomicDecRef(&SDL_messagebox_ಎಣಿಕೆ);

    ಆದರೆ (current_ಕಿಟಕಿ) {
        SDL_Raise_ಕಿಟಕಿ(current_ಕಿಟಕಿ);
    }

    ಆದರೆ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_ಬಹುಲಕ();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool SDL_Show_Simple_ಸಂದೇಶ_Box(SDL_ಸಂದೇಶ_Box_Flags flags, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *title, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ಆದರೆ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_ಬಲ;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_ಬಲ = gsp_Has_Gpu_ಬಲ();
    ಆದರೆ (!has_Gpu_ಬಲ)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_ಪಠ್ಯ_ಶಬ್ದ_WRAP, CFG_LANGUAGE_EN);
    error_ಪಠ್ಯ(&errCnf, ಸಂದೇಶ);
    errorDisp(&errCnf);

    ಆದರೆ (!has_Gpu_ಬಲ)
        gfxExit();

    ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_ಸಂದೇಶ_Box_ದತ್ತಾಂಶ ದತ್ತಾಂಶ;
    SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ button;

    SDL_zero(ದತ್ತಾಂಶ);
    ದತ್ತಾಂಶ.flags = flags;
    ದತ್ತಾಂಶ.title = title;
    ದತ್ತಾಂಶ.ಸಂದೇಶ = ಸಂದೇಶ;
    ದತ್ತಾಂಶ.numbuttons = 1;
    ದತ್ತಾಂಶ.buttons = &button;
    ದತ್ತಾಂಶ.ಕಿಟಕಿ = ಕಿಟಕಿ;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.ಪಠ್ಯ = "OK";

    ಹಿಂತಿರುಗಿ SDL_Show_ಸಂದೇಶ_Box(&ದತ್ತಾಂಶ, ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ
}

bool SDL_ShouldAllowTopmost(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_GetHintBoolean(SDL_HINT_ಕಿಟಕಿ_ALLOW_TOPMOST, true);
}

bool SDL_Show_ಕಿಟಕಿ_System_Menu(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);
    CHECK_ಕಿಟಕಿ_NOT_POPUP(ಕಿಟಕಿ, false);

    ಆದರೆ (_this->Show_ಕಿಟಕಿ_System_Menu) {
        _this->Show_ಕಿಟಕಿ_System_Menu(ಕಿಟಕಿ, x, y);
        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool SDL_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ದೊರಕಿತು_Test callback, ಶೂನ್ಯ *callback_ದತ್ತಾಂಶ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }

    ಕಿಟಕಿ->ದೊರಕಿತು_test = callback;
    ಕಿಟಕಿ->ದೊರಕಿತು_test_ದತ್ತಾಂಶ = callback_ದತ್ತಾಂಶ;

    ಹಿಂತಿರುಗಿ _this->ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(ಕಿಟಕಿ, callback != ಖಾಲಿ);
}

bool SDL_ಗಣ_ಕಿಟಕಿ_Shape(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    ಆದರೆ (!props) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ಆದರೆ (!surface) {
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        surface = ಖಾಲಿ;
    }

    ಆದರೆ (!SDL_ಗಣ_Surface_Property(props, SDL_PROP_ಕಿಟಕಿ_SHAPE_ಸೂಚಕ, surface)) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (_this->Update_ಕಿಟಕಿ_Shape) {
        ಆದರೆ (!_this->Update_ಕಿಟಕಿ_Shape(_this, ಕಿಟಕಿ, surface)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

/*
 * Functions used by iOS application delegates
 */
ಶೂನ್ಯ SDL_OnApplicationWillTerminate(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

ಶೂನ್ಯ SDL_On_Application_Did_Receive_ಸ್ಮರಣೆ_Warning(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_ಕೆಳಗಿನ_ಸ್ಮರಣೆ);
}

ಶೂನ್ಯ SDL_OnApplicationWillEnterBackground(ಶೂನ್ಯ)
{
    ಆದರೆ (_this) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
        ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
        }
        SDL_ಗಣ_Keyboard_Focus(ಖಾಲಿ);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

ಶೂನ್ಯ SDL_OnApplicationDidEnterBackground(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

ಶೂನ್ಯ SDL_OnApplicationWillEnterForeground(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

ಶೂನ್ಯ SDL_OnApplicationDidEnterForeground(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    ಆದರೆ (_this) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
        ಗಾಗಿ (ಕಿಟಕಿ = _this->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
        }
    }
}

#ವ್ಯಾಖ್ಯಾನಿಸು NOT_A_VULKAN_ಕಿಟಕಿ "The specified window isn't a Vulkan window"

bool SDL_Vulkan_ತುಂಬು_Library(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ)
{
    bool ಫಲಿತಾಂಶ;

    ಆದರೆ (!_this) {
        ಹಿಂತಿರುಗಿ SDL_UninitializedVideo();
    }
    ಆದರೆ (_this->vulkan_config.loader_loaded) {
        ಆದರೆ (ಮಾರ್ಗ && SDL_strcmp(ಮಾರ್ಗ, _this->vulkan_config.loader_ಮಾರ್ಗ) != 0) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Vulkan loader library already loaded");
        }
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!_this->Vulkan_ತುಂಬು_Library) {
            ಹಿಂತಿರುಗಿ SDL_DllNotSupported("Vulkan");
        }
        ಫಲಿತಾಂಶ = _this->Vulkan_ತುಂಬು_Library(_this, ಮಾರ್ಗ);
    }
    ಆದರೆ (ಫಲಿತಾಂಶ) {
        _this->vulkan_config.loader_loaded++;
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

SDL_Function_ಸೂಚಕ SDL_Vulkan_GetVkGetInstanceProcAddr(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (!_this->vulkan_config.loader_loaded) {
        SDL_ಗಣ_Error("No Vulkan loader has been loaded");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ (SDL_Function_ಸೂಚಕ)_this->vulkan_config.vkGetInstanceProcAddr;
}

ಶೂನ್ಯ SDL_Vulkan_UnloadLibrary(ಶೂನ್ಯ)
{
    ಆದರೆ (!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (_this->vulkan_config.loader_loaded > 0) {
        ಆದರೆ (--_this->vulkan_config.loader_loaded > 0) {
            ಹಿಂತಿರುಗಿ;
        }
        ಆದರೆ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

ಅಕ್ಷರ ಸ್ಥಿರಾಂಕ * ಸ್ಥಿರಾಂಕ *SDL_Vulkan_GetInstanceExtensions(Uint32 *ಎಣಿಕೆ_2)
{
    Uint32 tmpcount = 0;
    ಆದರೆ (!ಎಣಿಕೆ_2) {
        ಎಣಿಕೆ_2 = &tmpcount;
    }

    ಆದರೆ (!_this->Vulkan_GetInstanceExtensions) {
        *ಎಣಿಕೆ_2 = 0;
        SDL_Unsupported();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ _this->Vulkan_GetInstanceExtensions(_this, ಎಣಿಕೆ_2);
}

bool SDL_Vulkan_CreateSurface(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                                  VkInstance instance,
                                  ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, false);

    ಆದರೆ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ಹಿಂತಿರುಗಿ false;
    }

    CHECK_PARAM(!instance) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ಹಿಂತಿರುಗಿ SDL_InvalidParamError("surface");
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN)) {
        // No problem, we can convert to Vulkan
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_METAL) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_METAL;
            // Nothing more to do for Metal.
        }
        ಆದರೆ (SDL_Vulkan_ತುಂಬು_Library(ಖಾಲಿ)) {
            ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_VULKAN;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("failed to load Vulkan library");
        }
    }

    ಹಿಂತಿರುಗಿ _this->Vulkan_CreateSurface(_this, ಕಿಟಕಿ, instance, allocator, surface);
}

ಶೂನ್ಯ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ಸ್ಥಿರಾಂಕ ರಚನೆ Vk_ಹಂಚಿಕೆ_Callbacks *allocator)
{
    ಆದರೆ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 ಸರತಿ_Family_ಸೂಚ್ಯಂಕ)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ಹಿಂತಿರುಗಿ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ಹಿಂತಿರುಗಿ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (_this->Vulkan_GetPresentationSupport) {
        ಹಿಂತಿರುಗಿ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, ಸರತಿ_Family_ಸೂಚ್ಯಂಕ);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ಹಿಂತಿರುಗಿ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    CHECK_ಕಿಟಕಿ_MAGIC(ಕಿಟಕಿ, ಖಾಲಿ);

    ಆದರೆ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_METAL)) {
        // No problem, we can convert to Metal
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_VULKAN) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_METAL;
    }

    ಹಿಂತಿರುಗಿ _this->Metal_CreateView(_this, ಕಿಟಕಿ);
}

ಶೂನ್ಯ SDL_Metal_DestroyView(SDL_MetalView view)
{
    ಆದರೆ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

ಶೂನ್ಯ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ಆದರೆ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        ಹಿಂತಿರುಗಿ _this->Metal_GetLayer(_this, view);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಗಣ_Error("Metal is not supported.");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

#ಆದರೆ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_GetCSSCursorName(SDL_SystemCursor id, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    ಆಯ್ಕೆ (id) {
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_DEFAULT:
        ಹಿಂತಿರುಗಿ "default";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪಠ್ಯ:
        ಹಿಂತಿರುಗಿ "text";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_WAIT:
        ಹಿಂತಿರುಗಿ "wait";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CROSSHAIR:
        ಹಿಂತಿರುಗಿ "crosshair";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪ್ರಗತಿ:
        ಹಿಂತಿರುಗಿ "progress";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ಆದರೆ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ಹಿಂತಿರುಗಿ "nwse-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ಆದರೆ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ಹಿಂತಿರುಗಿ "nesw-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_EW_RESIZE:
        ಆದರೆ (fallback_name) {
            *fallback_name = "col-resize";
        }
        ಹಿಂತಿರುಗಿ "ew-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NS_RESIZE:
        ಆದರೆ (fallback_name) {
            *fallback_name = "row-resize";
        }
        ಹಿಂತಿರುಗಿ "ns-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_MOVE:
        ಆದರೆ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ಹಿಂತಿರುಗಿ "move";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ಹಿಂತಿರುಗಿ "not-allowed";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಸೂಚಕ:
        ಹಿಂತಿರುಗಿ "pointer";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NW_RESIZE:
        ಹಿಂತಿರುಗಿ "nw-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_N_RESIZE:
        ಹಿಂತಿರುಗಿ "n-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NE_RESIZE:
        ಹಿಂತಿರುಗಿ "ne-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_E_RESIZE:
        ಹಿಂತಿರುಗಿ "e-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SE_RESIZE:
        ಹಿಂತಿರುಗಿ "se-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_S_RESIZE:
        ಹಿಂತಿರುಗಿ "s-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SW_RESIZE:
        ಹಿಂತಿರುಗಿ "sw-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_W_RESIZE:
        ಹಿಂತಿರುಗಿ "w-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ಹಿಂತಿರುಗಿ "context-menu";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_HELP:
        ಹಿಂತಿರುಗಿ "help";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CELL:
        ಹಿಂತಿರುಗಿ "cell";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_VERTICAL_ಪಠ್ಯ:
        ಹಿಂತಿರುಗಿ "vertical-text";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALIAS:
        ಹಿಂತಿರುಗಿ "alias";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_COPY:
        ಹಿಂತಿರುಗಿ "copy";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NO_DROP:
        ಹಿಂತಿರುಗಿ "no-drop";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRAB:
        ಹಿಂತಿರುಗಿ "grab";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRABBING:
        ಹಿಂತಿರುಗಿ "grabbing";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಲಂಬಸಾಲು_RESIZE:
        ಹಿಂತಿರುಗಿ "col-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಅಡ್ಡಸಾಲು_RESIZE:
        ಹಿಂತಿರುಗಿ "row-resize";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ಆದರೆ (fallback_name) {
            *fallback_name = "move";
        }
        ಹಿಂತಿರುಗಿ "all-scroll";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಒಳ:
        ಹಿಂತಿರುಗಿ "zoom-in";

    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಹೊರಹೋಗು:
        ಹಿಂತಿರುಗಿ "zoom-out";

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ "default";
    }
}
#ಆದರೆ_ಅಂತ್ಯ

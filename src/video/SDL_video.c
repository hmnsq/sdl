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

// The high-level video driver subsystem

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_clipboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_egl_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_surface_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_pixels_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_rect_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_video_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_hints_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_properties_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../timer/SDL_timer_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../camera/SDL_camera_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../render/SDL_sysrender.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../main/SDL_main_callbacks.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengl.h>
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL

#ਜੇ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengles.h>
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ਜੇ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ਅਨ੍ਤਰ੍ਭਾਵ <SDL3/SDL_opengles2.h>
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_CONTEXT_RELEASE_BEHAVIOR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#ਜੇ_ਅੰਤ

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#ਜੇ_ਅੰਤ

// This is always the same number between the various EXT/ARB/GLES extensions.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_FRAMEBUFFER_SRGB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_FRAMEBUFFER_SRGB 0x8DB9
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_EMSCRIPTEN
#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_3DS
#ਅਨ੍ਤਰ੍ਭਾਵ <3ds.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_RGBA_FLOAT_ਬਹੁਲਕ_ARB
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_RGBA_FLOAT_ਬਹੁਲਕ_ARB 0x8820
#ਜੇ_ਅੰਤ /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ਸਥਿਰ VideoBootStrap *bootstrap[] = {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ਨਿੱਜੀ
    &ਨਿੱਜੀ_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#ਜੇ_ਅੰਤ
    &X11_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_ਨਿਵੇਸ਼_LINUXEV
    &DUMMY_evdev_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#ਜੇ_ਅੰਤ
    ਨਿਰਾ
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਤੀਜਾ)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        ਵਾਪਸ ਨਤੀਜਾ;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(ਖਿੜਕੀ, SDL_OBJECT_TYPE_ਖਿੜਕੀ)) {     \
        SDL_ਸੈੱਟ_Error("Invalid window");                                 \
        ਵਾਪਸ ਨਤੀਜਾ;                                                  \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_DISPLAY_MAGIC(display, ਨਤੀਜਾ)                            \
    CHECK_PARAM(!display) {                                             \
        ਵਾਪਸ ਨਤੀਜਾ;                                                  \
    }                                                                   \

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, ਨਤੀਜਾ)                          \
    CHECK_PARAM(SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {                          \
        SDL_ਸੈੱਟ_Error("Operation invalid on popup windows");             \
        ਵਾਪਸ ਨਤੀਜਾ;                                                  \
    }

#ਜੇ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
ਬਾਹਰੀ bool Cocoa_Is_ਖਿੜਕੀ_ਵਿੱਚ_Fullscreen_Space(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_Is_ਖਿੜਕੀ_ਵਿੱਚ_Fullscreen_Space_Transition(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_Space(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool state, bool blocking);
ਬਾਹਰੀ bool Cocoa_IsShowingModalDialog(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_UIKIT
ਬਾਹਰੀ ਖਾਲੀ SDL_UpdateLifecycleObserver(ਖਾਲੀ);
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_Display_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਸਥਿਰ ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_Display_Scale_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਸਥਿਰ ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

// Convenience functions for reading driver flags
ਸਥਿਰ bool SDL_ਬਹੁਲਕ_Switching_Emulated(SDL_VideoDevice *_this)
{
    ਜੇ (_this->device_caps & VIDEO_DEVICE_CAPS_ਬਹੁਲਕ_SWITCHING_EMULATED) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ਵਾਪਸ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ਸਥਿਰ bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ਵਾਪਸ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ਸਥਿਰ bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ਵਾਪਸ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ਸਥਿਰ bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ਵਾਪਸ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ਸਥਿਰ bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ਵਾਪਸ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ਸਥਿਰ bool syncHint;

ਸਥਿਰ ਖਾਲੀ SDL_SyncHintWatcher(ਖਾਲੀ *userdata, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *old_ਮੁੱਲ, ਅਚਲ ਅੱਖਰ *new_ਮੁੱਲ)
{
    syncHint = SDL_GetStringBoolean(new_ਮੁੱਲ, false);
}

ਸਥਿਰ ਖਾਲੀ SDL_SyncIfRequired(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (syncHint) {
        SDL_Sync_ਖਿੜਕੀ(ਖਿੜਕੀ);
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_Update_ਖਿੜਕੀ_Hierarchy(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ)
{
    // Unlink the window from the existing parent.
    ਜੇ (ਖਿੜਕੀ->ਮਾਪਾ) {
        ਜੇ (ਖਿੜਕੀ->ਅਗਲਾ_sibling) {
            ਖਿੜਕੀ->ਅਗਲਾ_sibling->prev_sibling = ਖਿੜਕੀ->prev_sibling;
        }
        ਜੇ (ਖਿੜਕੀ->prev_sibling) {
            ਖਿੜਕੀ->prev_sibling->ਅਗਲਾ_sibling = ਖਿੜਕੀ->ਅਗਲਾ_sibling;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->ਮਾਪਾ->ਪਹਿਲਾ_ਬੱਚਾ = ਖਿੜਕੀ->ਅਗਲਾ_sibling;
        }

        ਖਿੜਕੀ->ਮਾਪਾ = ਨਿਰਾ;
    }

    ਜੇ (ਮਾਪਾ) {
        ਖਿੜਕੀ->ਮਾਪਾ = ਮਾਪਾ;

        ਖਿੜਕੀ->ਅਗਲਾ_sibling = ਮਾਪਾ->ਪਹਿਲਾ_ਬੱਚਾ;
        ਜੇ (ਮਾਪਾ->ਪਹਿਲਾ_ਬੱਚਾ) {
            ਮਾਪਾ->ਪਹਿਲਾ_ਬੱਚਾ->prev_sibling = ਖਿੜਕੀ;
        }
        ਮਾਪਾ->ਪਹਿਲਾ_ਬੱਚਾ = ਖਿੜਕੀ;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ "SDL.internal.window.texturedata"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    ਖਾਲੀ *pixels;
    ਪੂਰਨ pitch;
    ਪੂਰਨ ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel;
} SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ;

ਸਥਿਰ Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#ਜੇ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !ਨਿਸ਼ਾਨਾ_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ਜੇ (_this->GL_CreateContext) {
        ਵਾਪਸ SDL_ਖਿੜਕੀ_OPENGL;
    }
#ਜੇ_ਅੰਤ
#ਜੇ defined(SDL_VIDEO_METAL) && (ਨਿਸ਼ਾਨਾ_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ਜੇ (_this->Metal_CreateView) {
        ਵਾਪਸ SDL_ਖਿੜਕੀ_METAL;
    }
#ਜੇ_ਅੰਤ
#ਜੇ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ਜੇ (SDL_strcmp(_this->name, "openvr") == 0) {
        ਵਾਪਸ SDL_ਖਿੜਕੀ_OPENGL;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 0;
}

ਸਥਿਰ bool SDL_Create_ਖਿੜਕੀ_Texture(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format, ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *)SDL_Get_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ, ਨਿਰਾ);
    ਅਚਲ bool transparent = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) ? true : false;
    ਪੂਰਨ i;
    ਪੂਰਨ w, h;
    ਅਚਲ SDL_PixelFormat *texture_formats;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    ਜੇ (!ਅੰਕੜੇ) {
        SDL_Renderer *renderer = ਨਿਰਾ;
        ਅਚਲ ਅੱਖਰ *render_driver = ਨਿਰਾ;

        // See if there's a render driver being requested
        ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ਜੇ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ਜੇ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ਜੇ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = ਨਿਰਾ;
        }

        ਅੱਖਰ *render_driver_copy = ਨਿਰਾ;
        ਜੇ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ਜੇ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                ਅੱਖਰ *prev = render_driver_copy;
                ਅੱਖਰ *ptr = prev;
                ਜਦੋਂ ((ptr = SDL_strchr(ptr, ',')) != ਨਿਰਾ) {
                    *ptr = '\0';
                    ਅਚਲ bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ਜੇ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } ਨਹੀਂਤਾਂ {
                        ptr++;
                        prev = ptr;
                    }
                }

                ਜੇ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ਜੇ (render_driver) {
            renderer = SDL_CreateRenderer(ਖਿੜਕੀ, render_driver);
            SDL_free(render_driver_copy);
            ਜੇ (!renderer) {
                // The error for this specific renderer has already been set
                ਵਾਪਸ false;
            }
        } ਨਹੀਂਤਾਂ {
            SDL_assert(render_driver_copy == ਨਿਰਾ);
            ਅਚਲ ਪੂਰਨ ਕੁੱਲ = SDL_Get_ਅੰਕ_Render_Drivers();
            ਲਈ (i = 0; i < ਕੁੱਲ; ++i) {
                ਅਚਲ ਅੱਖਰ *name = SDL_GetRenderDriver(i);
                ਜੇ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(ਖਿੜਕੀ, name);
                    ਜੇ (renderer) {
                        ਰੋਕੋ; // this will work.
                    }
                }
            }
            ਜੇ (!renderer) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ਨਿਰਾ); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
        ਜੇ (!ਅੰਕੜੇ) {
            SDL_DestroyRenderer(renderer);
            ਵਾਪਸ false;
        }
        ਜੇ (!SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ, ਅੰਕੜੇ)) {
            SDL_DestroyRenderer(renderer);
            ਵਾਪਸ false;
        }

        ਅੰਕੜੇ->renderer = renderer;
    }

    texture_formats = (ਅਚਲ SDL_PixelFormat *)SDL_Get_ਸੂਚਕ_Property(SDL_GetRendererProperties(ਅੰਕੜੇ->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_ਸੂਚਕ, ਨਿਰਾ);
    ਜੇ (!texture_formats) {
        ਵਾਪਸ false;
    }

    // Free any old texture and pixel data
    ਜੇ (ਅੰਕੜੇ->texture) {
        SDL_DestroyTexture(ਅੰਕੜੇ->texture);
        ਅੰਕੜੇ->texture = ਨਿਰਾ;
    }
    SDL_free(ਅੰਕੜੇ->pixels);
    ਅੰਕੜੇ->pixels = ਨਿਰਾ;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    ਲਈ (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ਜੇ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10_ਦੋਆਧਾਰੀ_ਅੰਕ(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            ਰੋਕੋ;
        }
    }

    ਅੰਕੜੇ->texture = SDL_CreateTexture(ਅੰਕੜੇ->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    ਜੇ (!ਅੰਕੜੇ->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ਵਾਪਸ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_ਸੈੱਟ_Texture_Blend_ਬਹੁਲਕ(ਅੰਕੜੇ->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    ਅੰਕੜੇ->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel = SDL_BYTESPERPIXEL(*format);
    ਅੰਕੜੇ->pitch = (((w * ਅੰਕੜੇ->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ਅਚਲ size_t allocsize = (size_t)h * ਅੰਕੜੇ->pitch;
        ਅੰਕੜੇ->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ਜੇ (!ਅੰਕੜੇ->pixels) {
            ਵਾਪਸ false;
        }
    }

    *pixels = ਅੰਕੜੇ->pixels;
    *pitch = ਅੰਕੜੇ->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_ਸੈੱਟ_Render_Viewport(ਅੰਕੜੇ->renderer, ਨਿਰਾ);

    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Texture_VSync(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ vsync)
{
    SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *ਅੰਕੜੇ;

    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *)SDL_Get_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ, ਨਿਰਾ);
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }
    ਜੇ (!ਅੰਕੜੇ->renderer) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ SDL_ਸੈੱਟ_Render_VSync(ਅੰਕੜੇ->renderer, vsync);
}

ਸਥਿਰ bool SDL_Get_ਖਿੜਕੀ_Texture_VSync(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *vsync)
{
    SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *ਅੰਕੜੇ;

    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *)SDL_Get_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ, ਨਿਰਾ);
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }
    ਜੇ (!ਅੰਕੜੇ->renderer) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ SDL_GetRenderVSync(ਅੰਕੜੇ->renderer, vsync);
}

ਸਥਿਰ bool SDL_Update_ਖਿੜਕੀ_Texture(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects, ਪੂਰਨ numrects)
{
    SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *ਅੰਕੜੇ;
    SDL_Rect rect;
    ਖਾਲੀ *src;
    ਪੂਰਨ w, h;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    ਅੰਕੜੇ = (SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *)SDL_Get_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ, ਨਿਰਾ);
    ਜੇ (!ਅੰਕੜੇ || !ਅੰਕੜੇ->texture) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ਜੇ (SDL_Get_ਵਿਸਤਾਰ_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (ਖਾਲੀ *)((Uint8 *)ਅੰਕੜੇ->pixels +
                       rect.y * ਅੰਕੜੇ->pitch +
                       rect.x * ਅੰਕੜੇ->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_pixel);
        ਜੇ (!SDL_UpdateTexture(ਅੰਕੜੇ->texture, &rect, src, ਅੰਕੜੇ->pitch)) {
            ਵਾਪਸ false;
        }

        ਜੇ (!SDL_RenderTexture(ਅੰਕੜੇ->renderer, ਅੰਕੜੇ->texture, ਨਿਰਾ, ਨਿਰਾ)) {
            ਵਾਪਸ false;
        }

        SDL_RenderPresent(ਅੰਕੜੇ->renderer);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ SDL_Destroy_ਖਿੜਕੀ_Texture(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    ਜੇ (SDL_HasProperty(props, SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ)) {
        SDL_ਖਿੜਕੀ_Texture_ਅੰਕੜੇ *ਅੰਕੜੇ = SDL_Get_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ, ਨਿਰਾ);

        ਜੇ (ਅੰਕੜੇ->texture) {
            SDL_DestroyTexture(ਅੰਕੜੇ->texture);
        }
        ਜੇ (ਅੰਕੜੇ->renderer) {
            SDL_DestroyRenderer(ਅੰਕੜੇ->renderer);
        }
        SDL_free(ਅੰਕੜੇ->pixels);
        SDL_free(ਅੰਕੜੇ);

        SDL_ClearProperty(props, SDL_PROP_ਖਿੜਕੀ_TEXTUREDATA_ਸੂਚਕ);
    }
}

ਸਥਿਰ SDL_VideoDevice *_this = ਨਿਰਾ;
ਸਥਿਰ SDL_AtomicInt SDL_messagebox_ਗਿਣਤੀ;

ਸਥਿਰ ਪੂਰਨ SDLCALL cmpmodes(ਅਚਲ ਖਾਲੀ *A, ਅਚਲ ਖਾਲੀ *B)
{
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *a = (ਅਚਲ SDL_Display_ਬਹੁਲਕ *)A;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *b = (ਅਚਲ SDL_Display_ਬਹੁਲਕ *)B;
    ਪੂਰਨ a_refresh_ਦਰ = (ਪੂਰਨ)(a->refresh_ਦਰ * 100);
    ਪੂਰਨ b_refresh_ਦਰ = (ਪੂਰਨ)(b->refresh_ਦਰ * 100);
    ਪੂਰਨ a_pixel_density = (ਪੂਰਨ)(a->pixel_density * 100);
    ਪੂਰਨ b_pixel_density = (ਪੂਰਨ)(b->pixel_density * 100);

    ਜੇ (a->w != b->w) {
        ਵਾਪਸ b->w - a->w;
    } ਨਹੀਂਤਾਂ ਜੇ (a->h != b->h) {
        ਵਾਪਸ b->h - a->h;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ਵਾਪਸ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ਵਾਪਸ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ਨਹੀਂਤਾਂ ਜੇ (a_refresh_ਦਰ != b_refresh_ਦਰ) {
        ਵਾਪਸ b_refresh_ਦਰ - a_refresh_ਦਰ;
    } ਨਹੀਂਤਾਂ ਜੇ (a_pixel_density != b_pixel_density) {
        ਵਾਪਸ a_pixel_density - b_pixel_density;
    }
    ਵਾਪਸ 0;
}

bool SDL_UninitializedVideo(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ਸਥਿਰ ਅਚਲ VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

ਪੂਰਨ SDL_Get_ਅੰਕ_Video_Drivers(ਖਾਲੀ)
{
    ਸਥਿਰ ਪੂਰਨ ਅੰਕ_drivers = -1;

    ਜੇ (ਅੰਕ_drivers >= 0) {
        ਵਾਪਸ ਅੰਕ_drivers;
    }

    ਅੰਕ_drivers = 0;

    // Build a list of unique video drivers.
    ਲਈ (ਪੂਰਨ i = 0; bootstrap[i] != ਨਿਰਾ; ++i) {
        bool duplicate = false;
        ਲਈ (ਪੂਰਨ j = 0; j < i; ++j) {
            ਜੇ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                ਰੋਕੋ;
            }
        }

        ਜੇ (!duplicate) {
            deduped_bootstrap[ਅੰਕ_drivers++] = bootstrap[i];
        }
    }

    ਵਾਪਸ ਅੰਕ_drivers;
}

ਅਚਲ ਅੱਖਰ *SDL_GetVideoDriver(ਪੂਰਨ ਸੂਚਕਾਂਕ)
{
    CHECK_PARAM(ਸੂਚਕਾਂਕ < 0 || ਸੂਚਕਾਂਕ >= SDL_Get_ਅੰਕ_Video_Drivers()) {
        SDL_InvalidParamError("index");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ deduped_bootstrap[ਸੂਚਕਾਂਕ]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ਅਚਲ ਅੱਖਰ *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    ਪੂਰਨ i = 0;

    // Check to make sure we don't overwrite '_this'
    ਜੇ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ਜੇ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        ਜਾਓ pre_driver_error;
    }
    init_events = true;
    ਜੇ (!SDL_InitKeyboard()) {
        ਜਾਓ pre_driver_error;
    }
    init_keyboard = true;
    ਜੇ (!SDL_PreInitMouse()) {
        ਜਾਓ pre_driver_error;
    }
    init_mouse = true;
    ਜੇ (!SDL_InitTouch()) {
        ਜਾਓ pre_driver_error;
    }
    init_touch = true;
    ਜੇ (!SDL_InitPen()) {
        ਜਾਓ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ਨਿਰਾ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ਜੇ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#ਜੇ_ਅੰਤ
    ਜੇ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ਜੇ (driver_name && *driver_name != 0) {
        ਅਚਲ ਅੱਖਰ *driver_attempt = driver_name;
        ਜਦੋਂ (driver_attempt && *driver_attempt != 0 && !video) {
            ਅਚਲ ਅੱਖਰ *driver_attempt_ਸਿਰਾ = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_ਸਿਰਾ) ? (driver_attempt_ਸਿਰਾ - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            ਲਈ (i = 0; bootstrap[i]; ++i) {
                ਜੇ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ਜੇ (video) {
                        ਰੋਕੋ;
                    }
                }
            }

            driver_attempt = (driver_attempt_ਸਿਰਾ) ? (driver_attempt_ਸਿਰਾ + 1) : ਨਿਰਾ;
        }
    } ਨਹੀਂਤਾਂ {
        ਲਈ (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ਜੇ (video) {
                ਰੋਕੋ;
            }
        }
    }
    ਜੇ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (driver_name) {
            SDL_ਸੈੱਟ_Error("%s not available", driver_name);
            ਜਾਓ pre_driver_error;
        }
        SDL_ਸੈੱਟ_Error("No available video device");
        ਜਾਓ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ਨਿਰਾ;
    SDL_GL_Reset_ਗੁਣ();

    // Initialize the video subsystem
    ਜੇ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ਵਾਪਸ false;
    }

    // Make sure some displays were added
    ਜੇ (_this->ਅੰਕ_displays == 0) {
        SDL_QuitVideo();
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("The video driver did not add any displays");
    }

    SDL_ਜੋੜੋ_Hint_Callback(SDL_HINT_VIDEO_SYNC_ਖਿੜਕੀ_OPERATIONS, SDL_SyncHintWatcher, ਨਿਰਾ);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ਜੇ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ਵਾਪਸ true;

pre_driver_error:
    SDL_assert(_this == ਨਿਰਾ);
    ਜੇ (init_pen) {
        SDL_QuitPen();
    }
    ਜੇ (init_touch) {
        SDL_QuitTouch();
    }
    ਜੇ (init_mouse) {
        SDL_QuitMouse();
    }
    ਜੇ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ਜੇ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ਵਾਪਸ false;
}

ਅਚਲ ਅੱਖਰ *SDL_GetCurrentVideoDriver(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(ਖਾਲੀ)
{
    ਵਾਪਸ _this;
}

bool SDL_OnVideoThread(ਖਾਲੀ)
{
    ਵਾਪਸ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

ਖਾਲੀ SDL_ਸੈੱਟ_System_Theme(SDL_SystemTheme theme)
{
    ਜੇ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_ਬਦਲਿਆ_Event();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(ਖਾਲੀ)
{
    ਜੇ (_this) {
        ਵਾਪਸ _this->system_theme;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ਖਾਲੀ SDL_UpdateDesktopBounds(ਖਾਲੀ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ਨਿਰਾ);
    ਜੇ (displays) {
        ਲਈ (ਪੂਰਨ i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ਜੇ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ਜੇ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ਨਹੀਂਤਾਂ {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ਸਥਿਰ ਖਾਲੀ SDL_Finalize_Display_ਬਹੁਲਕ(SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    // Make sure all the fields are set up correctly
    ਜੇ (ਬਹੁਲਕ->pixel_density <= 0.0f) {
        ਬਹੁਲਕ->pixel_density = 1.0f;
    }

    ਜੇ (ਬਹੁਲਕ->refresh_ਦਰ_numerator > 0) {
        ਜੇ (ਬਹੁਲਕ->refresh_ਦਰ_denominator <= 0) {
            ਬਹੁਲਕ->refresh_ਦਰ_denominator = 1;
        }
        ਬਹੁਲਕ->refresh_ਦਰ = (ਦਸ਼ਮਲਵ)ਬਹੁਲਕ->refresh_ਦਰ_numerator / ਬਹੁਲਕ->refresh_ਦਰ_denominator;
    } ਨਹੀਂਤਾਂ {
        SDL_CalculateFraction(ਬਹੁਲਕ->refresh_ਦਰ, &ਬਹੁਲਕ->refresh_ਦਰ_numerator, &ਬਹੁਲਕ->refresh_ਦਰ_denominator);
    }
    ਬਹੁਲਕ->refresh_ਦਰ = SDL_roundf(ਬਹੁਲਕ->refresh_ਦਰ * 100) / 100.0f;
}

SDL_DisplayID SDL_ਜੋੜੋ_Basic_Video_Display(ਅਚਲ SDL_Display_ਬਹੁਲਕ *desktop_ਬਹੁਲਕ)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ਜੇ (desktop_ਬਹੁਲਕ) {
        SDL_memcpy(&display.desktop_ਬਹੁਲਕ, desktop_ਬਹੁਲਕ, ਆਕਾਰ(display.desktop_ਬਹੁਲਕ));
    }
    ਵਾਪਸ SDL_ਜੋੜੋ_Video_Display(&display, false);
}

SDL_DisplayID SDL_ਜੋੜੋ_Video_Display(ਅਚਲ SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    ਪੂਰਨ i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(ਆਕਾਰ(*new_display));
    ਜੇ (!new_display) {
        ਵਾਪਸ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->ਅੰਕ_displays + 1) * ਆਕਾਰ(*displays));
    ਜੇ (!displays) {
        SDL_free(new_display);
        ਵਾਪਸ 0;
    }
    _this->displays = displays;
    _this->displays[_this->ਅੰਕ_displays++] = new_display;

    id = SDL_Get_ਅਗਲਾ_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ਜੇ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ਨਹੀਂਤਾਂ {
        ਅੱਖਰ name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ਜੇ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_ਬਹੁਲਕ.displayID = id;
    new_display->current_ਬਹੁਲਕ = &new_display->desktop_ਬਹੁਲਕ;
    SDL_Finalize_Display_ਬਹੁਲਕ(&new_display->desktop_ਬਹੁਲਕ);

    ਲਈ (i = 0; i < new_display->ਅੰਕ_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_ਸੈੱਟ_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    ਜੇ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ਵਾਪਸ id;
}

ਖਾਲੀ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

    // See if any windows have changed to the new display
    ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        SDL_Check_ਖਿੜਕੀ_Display_ਬਦਲਿਆ(ਖਿੜਕੀ);
    }
}

ਖਾਲੀ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

ਖਾਲੀ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    ਪੂਰਨ display_ਸੂਚਕਾਂਕ = SDL_Get_Display_ਸੂਚਕਾਂਕ(displayID);
    ਜੇ (display_ਸੂਚਕਾਂਕ < 0) {
        ਵਾਪਸ;
    }

    display = _this->displays[display_ਸੂਚਕਾਂਕ];

    ਜੇ (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ);
    display->desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    SDL_free(display->ਅੰਦਰੂਨੀ);
    display->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    SDL_free(display);

    ਜੇ (display_ਸੂਚਕਾਂਕ < (_this->ਅੰਕ_displays - 1)) {
        SDL_memmove(&_this->displays[display_ਸੂਚਕਾਂਕ], &_this->displays[display_ਸੂਚਕਾਂਕ + 1], (_this->ਅੰਕ_displays - display_ਸੂਚਕਾਂਕ - 1) * ਆਕਾਰ(_this->displays[display_ਸੂਚਕਾਂਕ]));
    }
    --_this->ਅੰਕ_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਪੂਰਨ i;
    SDL_DisplayID *displays;

    ਜੇ (!_this) {
        ਜੇ (ਗਿਣਤੀ_2) {
            *ਗਿਣਤੀ_2 = 0;
        }

        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->ਅੰਕ_displays + 1) * ਆਕਾਰ(*displays));
    ਜੇ (displays) {
        ਜੇ (ਗਿਣਤੀ_2) {
            *ਗਿਣਤੀ_2 = _this->ਅੰਕ_displays;
        }

        ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਗਿਣਤੀ_2) {
            *ਗਿਣਤੀ_2 = 0;
        }
    }
    ਵਾਪਸ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    ਪੂਰਨ display_ਸੂਚਕਾਂਕ;

    display_ਸੂਚਕਾਂਕ = SDL_Get_Display_ਸੂਚਕਾਂਕ(displayID);
    ਜੇ (display_ਸੂਚਕਾਂਕ < 0) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ _this->displays[display_ਸੂਚਕਾਂਕ];
}

ਸਥਿਰ SDL_DisplayID Get_Display_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        displayID = ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.displayID;
    }

    ਜੇ (!displayID) {
        displayID = SDL_Get_Display_For_ਖਿੜਕੀ_Position(ਖਿੜਕੀ);
    }
    ਵਾਪਸ displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0);

    ਵਾਪਸ SDL_GetVideoDisplay(Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ));
}

SDL_DisplayID SDL_GetPrimaryDisplay(ਖਾਲੀ)
{
    ਜੇ (!_this || _this->ਅੰਕ_displays == 0) {
        SDL_UninitializedVideo();
        ਵਾਪਸ 0;
    }
    ਵਾਪਸ _this->displays[0]->id;
}

ਪੂਰਨ SDL_Get_Display_ਸੂਚਕਾਂਕ(SDL_DisplayID displayID)
{
    ਪੂਰਨ display_ਸੂਚਕਾਂਕ;

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ -1;
    }

    ਲਈ (display_ਸੂਚਕਾਂਕ = 0; display_ਸੂਚਕਾਂਕ < _this->ਅੰਕ_displays; ++display_ਸੂਚਕਾਂਕ) {
        ਜੇ (displayID == _this->displays[display_ਸੂਚਕਾਂਕ]->id) {
            ਵਾਪਸ display_ਸੂਚਕਾਂਕ;
        }
    }
    SDL_ਸੈੱਟ_Error("Invalid display");
    ਵਾਪਸ -1;
}

SDL_Display_ਅੰਕੜੇ *SDL_Get_Display_Driver_ਅੰਕੜੇ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ਨਿਰਾ);

    ਵਾਪਸ display->ਅੰਦਰੂਨੀ;
}

SDL_Display_ਅੰਕੜੇ *SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0);

    ਵਾਪਸ SDL_Get_Display_Driver_ਅੰਕੜੇ(Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ਜੇ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ਵਾਪਸ display->props;
}

ਅਚਲ ਅੱਖਰ *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ਨਿਰਾ);

    ਵਾਪਸ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ਵਾਪਸ SDL_InvalidParamError("rect");
    }

    ਜੇ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ਜੇ (_this->GetDisplayBounds(_this, display, rect)) {
            ਵਾਪਸ true;
        }
    }

    // Assume that the displays are left to right
    ਜੇ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ਨਹੀਂਤਾਂ {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_ਸੂਚਕਾਂਕ(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_ਬਹੁਲਕ->w;
    rect->h = display->current_ਬਹੁਲਕ->h;
    ਵਾਪਸ true;
}

ਸਥਿਰ ਪੂਰਨ ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ਵਾਪਸ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ਵਾਪਸ SDL_InvalidParamError("rect");
    }

    ਜੇ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ਵਾਪਸ true;
    }

    ਜੇ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ਜੇ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ਵਾਪਸ true;
        }
    }

    // Oh well, just give the entire display bounds.
    ਵਾਪਸ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ਜੇ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ਵਾਪਸ display->natural_orientation;
    } ਨਹੀਂਤਾਂ {
        // Default to landscape if the driver hasn't set it
        ਵਾਪਸ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ਜੇ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ਵਾਪਸ display->current_orientation;
    } ਨਹੀਂਤਾਂ {
        // Default to landscape if the driver hasn't set it
        ਵਾਪਸ SDL_ORIENTATION_LANDSCAPE;
    }
}

ਖਾਲੀ SDL_ਸੈੱਟ_Display_Content_Scale(SDL_VideoDisplay *display, ਦਸ਼ਮਲਵ scale)
{
    ਜੇ (scale != display->content_scale) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_ਬਦਲਿਆ, 0, 0);

        // Check the windows on this display
        ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            ਜੇ (display->id == ਖਿੜਕੀ->displayID) {
                SDL_Check_ਖਿੜਕੀ_Display_Scale_ਬਦਲਿਆ(ਖਿੜਕੀ);
            }
        }
    }
}

ਦਸ਼ਮਲਵ SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ਵਾਪਸ display->content_scale;
}

ਖਾਲੀ SDL_ਸੈੱਟ_ਖਿੜਕੀ_HDRProperties(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_HDROutputProperties *HDR, bool send_event)
{
    ਅਚਲ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ਜੇ (ਖਿੜਕੀ->HDR.HDR_headroom != HDR_clamped.HDR_headroom || ਖਿੜਕੀ->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID ਖਿੜਕੀ_props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);

        SDL_ਸੈੱਟ_Float_Property(ਖਿੜਕੀ_props, SDL_PROP_ਖਿੜਕੀ_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_ਸੈੱਟ_Float_Property(ਖਿੜਕੀ_props, SDL_PROP_ਖਿੜਕੀ_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_ਸੈੱਟ_Boolean_Property(ਖਿੜਕੀ_props, SDL_PROP_ਖਿੜਕੀ_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&ਖਿੜਕੀ->HDR, &HDR_clamped);

        ਜੇ (send_event) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_HDR_STATE_ਬਦਲਿਆ, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

ਖਾਲੀ SDL_ਸੈੱਟ_Display_HDRProperties(SDL_VideoDisplay *display, ਅਚਲ SDL_HDROutputProperties *HDR)
{
    ਅਚਲ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ਅਚਲ bool ਬਦਲਿਆ = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	ਜੇ (ਬਦਲਿਆ) {
		SDL_ਸੈੱਟ_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ਜੇ (ਬਦਲਿਆ && !SDL_DriverSendsHDRChanges(_this)) {
        ਲਈ (SDL_ਖਿੜਕੀ *w = display->device->windows; w; w = w->ਅਗਲਾ) {
            ਜੇ (Get_Display_For_ਖਿੜਕੀ(w) == display->id) {
                SDL_ਸੈੱਟ_ਖਿੜਕੀ_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ਜੇ (display->ਅੰਕ_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ਸਥਿਰ ਅਚਲ SDL_Display_ਬਹੁਲਕ *SDL_Get_Fullscreen_ਬਹੁਲਕ_ਮੇਲ(ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_VideoDisplay *display;
    SDL_Display_ਬਹੁਲਕ fullscreen_ਬਹੁਲਕ;

    ਜੇ (ਬਹੁਲਕ->w <= 0 || ਬਹੁਲਕ->h <= 0) {
        // Use the desktop mode
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_memcpy(&fullscreen_ਬਹੁਲਕ, ਬਹੁਲਕ, ਆਕਾਰ(fullscreen_ਬਹੁਲਕ));
    ਜੇ (fullscreen_ਬਹੁਲਕ.displayID == 0) {
        fullscreen_ਬਹੁਲਕ.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_ਬਹੁਲਕ(&fullscreen_ਬਹੁਲਕ);

    ਬਹੁਲਕ = ਨਿਰਾ;

    display = SDL_GetVideoDisplay(fullscreen_ਬਹੁਲਕ.displayID);
    ਜੇ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ਜੇ (!ਬਹੁਲਕ) {
            ਲਈ (ਪੂਰਨ i = 0; i < display->ਅੰਕ_fullscreen_modes; ++i) {
                ਜੇ (SDL_memcmp(&fullscreen_ਬਹੁਲਕ, &display->fullscreen_modes[i], ਆਕਾਰ(fullscreen_ਬਹੁਲਕ)) == 0) {
                    ਬਹੁਲਕ = &display->fullscreen_modes[i];
                    ਰੋਕੋ;
                }
            }
        }

        // Search for a mode with the same characteristics
        ਜੇ (!ਬਹੁਲਕ) {
            ਲਈ (ਪੂਰਨ i = 0; i < display->ਅੰਕ_fullscreen_modes; ++i) {
                ਜੇ (cmpmodes(&fullscreen_ਬਹੁਲਕ, &display->fullscreen_modes[i]) == 0) {
                    ਬਹੁਲਕ = &display->fullscreen_modes[i];
                    ਰੋਕੋ;
                }
            }
        }
    }
    ਵਾਪਸ ਬਹੁਲਕ;
}

bool SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(SDL_VideoDisplay *display, ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Display_ਬਹੁਲਕ *modes;
    SDL_Display_ਬਹੁਲਕ new_ਬਹੁਲਕ;
    ਪੂਰਨ i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_ਬਹੁਲਕ, ਬਹੁਲਕ, ਆਕਾਰ(new_ਬਹੁਲਕ));
    new_ਬਹੁਲਕ.displayID = display->id;
    SDL_Finalize_Display_ਬਹੁਲਕ(&new_ਬਹੁਲਕ);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->ਅੰਕ_fullscreen_modes;
    ਲਈ (i = 0; i < nmodes; ++i) {
        ਜੇ (cmpmodes(&new_ਬਹੁਲਕ, &modes[i]) == 0) {
            ਵਾਪਸ false;
        }
    }

    // Go ahead and add the new mode
    ਜੇ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_ਬਹੁਲਕ *)SDL_malloc((display->max_fullscreen_modes + 32) * ਆਕਾਰ(*modes));
        ਜੇ (!modes) {
            ਵਾਪਸ false;
        }

        ਜੇ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * ਆਕਾਰ(*modes));
            ਲਈ (i = 0; i < nmodes; ++i) {
                ਜੇ (display->current_ਬਹੁਲਕ == &display->fullscreen_modes[i]) {
                    display->current_ਬਹੁਲਕ = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->ਅੰਕ_fullscreen_modes++], &new_ਬਹੁਲਕ, ਆਕਾਰ(new_ਬਹੁਲਕ));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->ਅੰਕ_fullscreen_modes,
              ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ), cmpmodes);

    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ਪੂਰਨ i;

    ਲਈ (i = display->ਅੰਕ_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].ਅੰਦਰੂਨੀ);
        display->fullscreen_modes[i].ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ਨਿਰਾ;
    display->ਅੰਕ_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_ਬਹੁਲਕ = &display->desktop_ਬਹੁਲਕ;
}

SDL_Display_ਬਹੁਲਕ **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਪੂਰਨ i;
    ਪੂਰਨ ਅੰਕ_modes;
    SDL_Display_ਬਹੁਲਕ **ਨਤੀਜਾ;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ਜੇ (ਗਿਣਤੀ_2) {
        *ਗਿਣਤੀ_2 = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ਨਿਰਾ);

    SDL_UpdateFullscreenDisplayModes(display);

    ਅੰਕ_modes = display->ਅੰਕ_fullscreen_modes;
    ਨਤੀਜਾ = (SDL_Display_ਬਹੁਲਕ **)SDL_malloc((ਅੰਕ_modes + 1) * ਆਕਾਰ(*ਨਤੀਜਾ) + ਅੰਕ_modes * ਆਕਾਰ(**ਨਤੀਜਾ));
    ਜੇ (ਨਤੀਜਾ) {
        SDL_Display_ਬਹੁਲਕ *modes = (SDL_Display_ਬਹੁਲਕ *)((Uint8 *)ਨਤੀਜਾ + ((ਅੰਕ_modes + 1) * ਆਕਾਰ(*ਨਤੀਜਾ)));
        ਜੇ (ਅੰਕ_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, ਅੰਕ_modes * ਆਕਾਰ(*modes));
        }
        ਲਈ (i = 0; i < ਅੰਕ_modes; ++i) {
            ਨਤੀਜਾ[i] = modes++;
        }
        ਨਤੀਜਾ[i] = ਨਿਰਾ;

        ਜੇ (ਗਿਣਤੀ_2) {
            *ਗਿਣਤੀ_2 = ਅੰਕ_modes;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਗਿਣਤੀ_2) {
            *ਗਿਣਤੀ_2 = 0;
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_Get_Closest_Fullscreen_Display_ਬਹੁਲਕ(SDL_DisplayID displayID, ਪੂਰਨ w, ਪੂਰਨ h, ਦਸ਼ਮਲਵ refresh_ਦਰ, bool include_ਉੱਚਾ_density_modes, SDL_Display_ਬਹੁਲਕ *ਨਤੀਜਾ)
{
    CHECK_PARAM(!ਨਤੀਜਾ) {
        ਵਾਪਸ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ, *closest = ਨਿਰਾ;
    ਦਸ਼ਮਲਵ aspect_ਅਨੁਪਾਤ;
    ਪੂਰਨ i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(ਨਤੀਜਾ);

    CHECK_DISPLAY_MAGIC(display, false);

    ਜੇ (h > 0) {
        aspect_ਅਨੁਪਾਤ = (ਦਸ਼ਮਲਵ)w / h;
    } ਨਹੀਂਤਾਂ {
        aspect_ਅਨੁਪਾਤ = 1.0f;
    }

    ਜੇ (refresh_ਦਰ == 0.0f) {
        refresh_ਦਰ = display->desktop_ਬਹੁਲਕ.refresh_ਦਰ;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    ਲਈ (i = 0; i < display->ਅੰਕ_fullscreen_modes; ++i) {
        ਬਹੁਲਕ = &display->fullscreen_modes[i];

        ਜੇ (w > ਬਹੁਲਕ->w) {
            // Out of sorted modes large enough here
            ਰੋਕੋ;
        }
        ਜੇ (h > ਬਹੁਲਕ->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            ਜਾਰੀ;
        }
        ਜੇ (ਬਹੁਲਕ->pixel_density > 1.0f && !include_ਉੱਚਾ_density_modes) {
            ਜਾਰੀ;
        }
        ਜੇ (closest) {
            ਦਸ਼ਮਲਵ current_aspect_ਅਨੁਪਾਤ = (ਦਸ਼ਮਲਵ)ਬਹੁਲਕ->w / ਬਹੁਲਕ->h;
            ਦਸ਼ਮਲਵ closest_aspect_ਅਨੁਪਾਤ = (ਦਸ਼ਮਲਵ)closest->w / closest->h;
            ਜੇ (SDL_fabsf(aspect_ਅਨੁਪਾਤ - closest_aspect_ਅਨੁਪਾਤ) < SDL_fabsf(aspect_ਅਨੁਪਾਤ - current_aspect_ਅਨੁਪਾਤ)) {
                // The mode we already found has a better aspect ratio match
                ਜਾਰੀ;
            }

            ਜੇ (ਬਹੁਲਕ->w == closest->w && ਬਹੁਲਕ->h == closest->h) {
                ਜੇ (SDL_fabsf(closest->refresh_ਦਰ - refresh_ਦਰ) < SDL_fabsf(ਬਹੁਲਕ->refresh_ਦਰ - refresh_ਦਰ)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    ਜਾਰੀ;
                }
                ਜੇ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(ਬਹੁਲਕ->format)) {
                    // Prefer the highest color depth
                    ਜਾਰੀ;
                }
            }
        }

        closest = ਬਹੁਲਕ;
    }
    ਜੇ (!closest) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(ਨਤੀਜਾ, closest);

    ਵਾਪਸ true;
}

ਸਥਿਰ bool Display_ਬਹੁਲਕ_ਬਦਲਿਆ(ਅਚਲ SDL_Display_ਬਹੁਲਕ *old_ਬਹੁਲਕ, ਅਚਲ SDL_Display_ਬਹੁਲਕ *new_ਬਹੁਲਕ)
{
    ਵਾਪਸ ((old_ਬਹੁਲਕ->displayID && old_ਬਹੁਲਕ->displayID != new_ਬਹੁਲਕ->displayID) ||
            (old_ਬਹੁਲਕ->format && old_ਬਹੁਲਕ->format != new_ਬਹੁਲਕ->format) ||
            (old_ਬਹੁਲਕ->w && old_ਬਹੁਲਕ->h && (old_ਬਹੁਲਕ->w != new_ਬਹੁਲਕ->w ||old_ਬਹੁਲਕ->h != new_ਬਹੁਲਕ->h)) ||
            (old_ਬਹੁਲਕ->pixel_density != 0.0f && old_ਬਹੁਲਕ->pixel_density != new_ਬਹੁਲਕ->pixel_density) ||
            (old_ਬਹੁਲਕ->refresh_ਦਰ != 0.0f && old_ਬਹੁਲਕ->refresh_ਦਰ != new_ਬਹੁਲਕ->refresh_ਦਰ));
}

ਖਾਲੀ SDL_ਸੈੱਟ_Desktop_Display_ਬਹੁਲਕ(SDL_VideoDisplay *display, ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Display_ਬਹੁਲਕ ਆਖਰੀ_ਬਹੁਲਕ;

    ਜੇ (display->fullscreen_ਸਰਗਰਮ) {
        // This is a temporary mode change, don't save the desktop mode
        ਵਾਪਸ;
    }

    SDL_copyp(&ਆਖਰੀ_ਬਹੁਲਕ, &display->desktop_ਬਹੁਲਕ);

    SDL_free(display->desktop_ਬਹੁਲਕ.ਅੰਦਰੂਨੀ);
    SDL_copyp(&display->desktop_ਬਹੁਲਕ, ਬਹੁਲਕ);
    display->desktop_ਬਹੁਲਕ.displayID = display->id;
    SDL_Finalize_Display_ਬਹੁਲਕ(&display->desktop_ਬਹੁਲਕ);

    ਜੇ (Display_ਬਹੁਲਕ_ਬਦਲਿਆ(&ਆਖਰੀ_ਬਹੁਲਕ, &display->desktop_ਬਹੁਲਕ)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_ਬਹੁਲਕ_ਬਦਲਿਆ, ਬਹੁਲਕ->w, ਬਹੁਲਕ->h);
        ਜੇ (display->current_ਬਹੁਲਕ == &display->desktop_ਬਹੁਲਕ) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_ਬਹੁਲਕ_ਬਦਲਿਆ, ਬਹੁਲਕ->w, ਬਹੁਲਕ->h);
        }
    }
}

ਅਚਲ SDL_Display_ਬਹੁਲਕ *SDL_Get_Desktop_Display_ਬਹੁਲਕ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ਨਿਰਾ);

    ਵਾਪਸ &display->desktop_ਬਹੁਲਕ;
}

ਖਾਲੀ SDL_ਸੈੱਟ_Current_Display_ਬਹੁਲਕ(SDL_VideoDisplay *display, ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Display_ਬਹੁਲਕ ਆਖਰੀ_ਬਹੁਲਕ;

    ਜੇ (display->current_ਬਹੁਲਕ) {
        SDL_copyp(&ਆਖਰੀ_ਬਹੁਲਕ, display->current_ਬਹੁਲਕ);
    } ਨਹੀਂਤਾਂ {
        SDL_zero(ਆਖਰੀ_ਬਹੁਲਕ);
    }

    display->current_ਬਹੁਲਕ = ਬਹੁਲਕ;

    ਜੇ (Display_ਬਹੁਲਕ_ਬਦਲਿਆ(&ਆਖਰੀ_ਬਹੁਲਕ, ਬਹੁਲਕ)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_ਬਹੁਲਕ_ਬਦਲਿਆ, ਬਹੁਲਕ->w, ਬਹੁਲਕ->h);
    }
}

ਅਚਲ SDL_Display_ਬਹੁਲਕ *SDL_Get_Current_Display_ਬਹੁਲਕ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ਨਿਰਾ);

    ਵਾਪਸ display->current_ਬਹੁਲਕ;
}

bool SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ਜੇ (SDL_ਬਹੁਲਕ_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ਵਾਪਸ true;
    }

    ਜੇ (!ਬਹੁਲਕ) {
        ਬਹੁਲਕ = &display->desktop_ਬਹੁਲਕ;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_RISCOS
    ਜੇ (ਬਹੁਲਕ == display->current_ਬਹੁਲਕ) {
        ਵਾਪਸ true;
    }
#ਜੇ_ਅੰਤ

    // Actually change the display mode
    ਜੇ (_this->ਸੈੱਟ_Display_ਬਹੁਲਕ) {
        bool ਨਤੀਜਾ;

        _this->setting_display_ਬਹੁਲਕ = true;
        ਨਤੀਜਾ = _this->ਸੈੱਟ_Display_ਬਹੁਲਕ(_this, display, ਬਹੁਲਕ);
        _this->setting_display_ਬਹੁਲਕ = false;
        ਜੇ (!ਨਤੀਜਾ) {
            ਵਾਪਸ false;
        }
    }

    SDL_ਸੈੱਟ_Current_Display_ਬਹੁਲਕ(display, ਬਹੁਲਕ);

    ਵਾਪਸ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ਸਥਿਰ ਖਾਲੀ SDL_Get_Closest_ਬਿੰਦੂ_On_Rect(ਅਚਲ SDL_Rect *rect, SDL_ਬਿੰਦੂ *ਬਿੰਦੂ)
{
    ਅਚਲ ਪੂਰਨ ਸੱਜਾ = rect->x + rect->w - 1;
    ਅਚਲ ਪੂਰਨ bottom = rect->y + rect->h - 1;

    ਜੇ (ਬਿੰਦੂ->x < rect->x) {
        ਬਿੰਦੂ->x = rect->x;
    } ਨਹੀਂਤਾਂ ਜੇ (ਬਿੰਦੂ->x > ਸੱਜਾ) {
        ਬਿੰਦੂ->x = ਸੱਜਾ;
    }

    ਜੇ (ਬਿੰਦੂ->y < rect->y) {
        ਬਿੰਦੂ->y = rect->y;
    } ਨਹੀਂਤਾਂ ਜੇ (ਬਿੰਦੂ->y > bottom) {
        ਬਿੰਦੂ->y = bottom;
    }
}

ਸਥਿਰ SDL_DisplayID GetDisplayForRect(ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ w, ਪੂਰਨ h)
{
    ਪੂਰਨ i, dist;
    SDL_DisplayID closest = 0;
    ਪੂਰਨ closest_dist = 0x7FFFFFFF;
    SDL_ਬਿੰਦੂ closest_ਬਿੰਦੂ_on_display;
    SDL_ਬਿੰਦੂ delta;
    SDL_ਬਿੰਦੂ center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    ਜੇ (_this) {
        ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ਜੇ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ਨਿਰਾ)) {
                ਵਾਪਸ display->id;
            }

            // Snap window center to the display rect
            closest_ਬਿੰਦੂ_on_display = center;
            SDL_Get_Closest_ਬਿੰਦੂ_On_Rect(&display_rect, &closest_ਬਿੰਦੂ_on_display);

            delta.x = center.x - closest_ਬਿੰਦੂ_on_display.x;
            delta.y = center.y - closest_ਬਿੰਦੂ_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ਜੇ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ਜੇ (closest == 0) {
        SDL_ਸੈੱਟ_Error("Couldn't find any displays");
    }

    ਵਾਪਸ closest;
}

ਖਾਲੀ SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ rel_x, ਪੂਰਨ rel_y, ਪੂਰਨ *abs_x, ਪੂਰਨ *abs_y)
{
    SDL_ਖਿੜਕੀ *w;

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        // Calculate the total offset of the popup from the parents
        ਲਈ (w = ਖਿੜਕੀ->ਮਾਪਾ; w; w = w->ਮਾਪਾ) {
            rel_x += w->x;
            rel_y += w->y;

            ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(w)) {
                ਰੋਕੋ;
            }
        }
    }

    ਜੇ (abs_x) {
        *abs_x = rel_x;
    }
    ਜੇ (abs_y) {
        *abs_y = rel_y;
    }
}

ਖਾਲੀ SDL_Global_ਮੰਜ਼ਿਲ_Relative_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ abs_x, ਪੂਰਨ abs_y, ਪੂਰਨ *rel_x, ਪੂਰਨ *rel_y)
{
    SDL_ਖਿੜਕੀ *w;

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        // Convert absolute window coordinates to relative for a popup
        ਲਈ (w = ਖਿੜਕੀ->ਮਾਪਾ; w; w = w->ਮਾਪਾ) {
            abs_x -= w->x;
            abs_y -= w->y;

            ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(w)) {
                ਰੋਕੋ;
            }
        }
    }

    ਜੇ (rel_x) {
        *rel_x = abs_x;
    }
    ਜੇ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_Get_Display_For_ਬਿੰਦੂ(ਅਚਲ SDL_ਬਿੰਦੂ *ਬਿੰਦੂ)
{
    CHECK_PARAM(!ਬਿੰਦੂ) {
        SDL_InvalidParamError("point");
        ਵਾਪਸ 0;
    }

    ਵਾਪਸ GetDisplayForRect(ਬਿੰਦੂ->x, ਬਿੰਦੂ->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ਅਚਲ SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ਵਾਪਸ 0;
    }

    ਵਾਪਸ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ਸਥਿਰ SDL_DisplayID GetDisplayAtOrigin(ਪੂਰਨ x, ਪੂਰਨ y)
{
    ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
        SDL_Rect rect;
        ਅਚਲ SDL_DisplayID cur_id = _this->displays[i]->id;
        ਜੇ (SDL_GetDisplayBounds(cur_id, &rect)) {
            ਜੇ (x == rect.x && y == rect.y) {
                ਵਾਪਸ cur_id;
            }
        }
    }

    ਵਾਪਸ 0;
}

SDL_DisplayID SDL_Get_Display_For_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਪੂਰਨ x, y;
    SDL_DisplayID displayID = 0;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0);

    ਜੇ (_this->Get_Display_For_ਖਿੜਕੀ) {
        displayID = _this->Get_Display_For_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_ਮੰਜ਼ਿਲ_Global_For_ਖਿੜਕੀ(ਖਿੜਕੀ, ਖਿੜਕੀ->x, ਖਿੜਕੀ->y, &x, &y);

    ਜੇ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ਨਹੀਂਤਾਂ {
            displayID = GetDisplayForRect(x, y, ਖਿੜਕੀ->w, ਖਿੜਕੀ->h);
        }
    }
    ਜੇ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ਵਾਪਸ displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_DisplayID displayID = 0;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਿਰਾ);

    // An explicit fullscreen display overrides all
    ਜੇ (ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.displayID) {
        displayID = ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ਜੇ (!displayID) {
        displayID = ਖਿੜਕੀ->pending_displayID;
    }
    ਜੇ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ਅਚਲ ਪੂਰਨ x = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.x : ਖਿੜਕੀ->x;
        ਅਚਲ ਪੂਰਨ y = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.y : ਖਿੜਕੀ->y;
        ਅਚਲ ਪੂਰਨ w = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਖਿੜਕੀ->w;
        ਅਚਲ ਪੂਰਨ h = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਖਿੜਕੀ->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ਜੇ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ਜੇ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ਵਾਪਸ SDL_GetVideoDisplay(displayID);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_PROP_SDL2_COMPAT_ਖਿੜਕੀ_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID ਖਿੜਕੀ_props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਜੇ (fs_display) {
        SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(ਖਿੜਕੀ_props, SDL_PROP_SDL2_COMPAT_ਖਿੜਕੀ_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ਨਹੀਂਤਾਂ {
        SDL_ClearProperty(ਖਿੜਕੀ_props, SDL_PROP_SDL2_COMPAT_ਖਿੜਕੀ_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ਵਾਪਸ Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
}

ਸਥਿਰ ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_Display_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (SDL_SendsDisplayChanges(_this)) {
        ਵਾਪਸ;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_ਖਿੜਕੀ_Position(ਖਿੜਕੀ);

    ਜੇ (displayID != ਖਿੜਕੀ->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect ਖਿੜਕੀ_rect;
        SDL_Rect old_overlap, new_overlap;

        ਜੇ (SDL_GetDisplayBounds(ਖਿੜਕੀ->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            ਖਿੜਕੀ_rect.x = ਖਿੜਕੀ->x;
            ਖਿੜਕੀ_rect.y = ਖਿੜਕੀ->y;
            ਖਿੜਕੀ_rect.w = ਖਿੜਕੀ->w;
            ਖਿੜਕੀ_rect.h = ਖਿੜਕੀ->h;

            ਜੇ (SDL_GetRectIntersection(&old_bounds, &ਖਿੜਕੀ_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &ਖਿੜਕੀ_rect, &new_overlap)) {
                ਪੂਰਨ old_area = old_overlap.w * old_overlap.h;
                ਪੂਰਨ new_area = new_overlap.w * new_overlap.h;
                ਦਸ਼ਮਲਵ new_overlap_ਅਨੁਪਾਤ = (new_area / ((ਦਸ਼ਮਲਵ)old_area + new_area));
                ਜੇ (new_overlap_ਅਨੁਪਾਤ < 0.80) {
                    ਵਾਪਸ;
                }
            }
        }
    }

    ਜੇ (displayID != ਖਿੜਕੀ->displayID) {
        ਪੂਰਨ i, display_ਸੂਚਕਾਂਕ;

        // Sanity check our fullscreen windows
        display_ਸੂਚਕਾਂਕ = SDL_Get_Display_ਸੂਚਕਾਂਕ(displayID);
        ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ਜੇ (display->fullscreen_ਖਿੜਕੀ == ਖਿੜਕੀ) {
                ਜੇ (display_ਸੂਚਕਾਂਕ != i) {
                    ਜੇ (display_ਸੂਚਕਾਂਕ < 0) {
                        display_ਸੂਚਕਾਂਕ = i;
                    } ਨਹੀਂਤਾਂ {
                        SDL_VideoDisplay *new_display = _this->displays[display_ਸੂਚਕਾਂਕ];

                        // The window was moved to a different display
                        ਜੇ (new_display->fullscreen_ਖਿੜਕੀ &&
                            new_display->fullscreen_ਖਿੜਕੀ != ਖਿੜਕੀ) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_ਖਿੜਕੀ(new_display->fullscreen_ਖਿੜਕੀ);
                        }
                        new_display->fullscreen_ਖਿੜਕੀ = ਖਿੜਕੀ;
                        display->fullscreen_ਖਿੜਕੀ = ਨਿਰਾ;
                    }
                }
                ਰੋਕੋ;
            }
        }

        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_DISPLAY_ਬਦਲਿਆ, (ਪੂਰਨ)displayID, 0);
    }
}

ਦਸ਼ਮਲਵ SDL_Get_ਖਿੜਕੀ_Pixel_Density(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਪੂਰਨ ਖਿੜਕੀ_w, ਖਿੜਕੀ_h, pixel_w, pixel_h;
    ਦਸ਼ਮਲਵ pixel_density = 1.0f;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0.0f);

    ਜੇ (SDL_Get_ਖਿੜਕੀ_ਮਾਪ(ਖਿੜਕੀ, &ਖਿੜਕੀ_w, &ਖਿੜਕੀ_h) &&
        SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &pixel_w, &pixel_h)) {
        pixel_density = (ਦਸ਼ਮਲਵ)pixel_w / ਖਿੜਕੀ_w;
    }
    ਵਾਪਸ pixel_density;
}

ਦਸ਼ਮਲਵ SDL_Get_ਖਿੜਕੀ_Display_Scale(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0.0f);

    ਵਾਪਸ ਖਿੜਕੀ->display_scale;
}

ਸਥਿਰ ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_Display_Scale_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਦਸ਼ਮਲਵ display_scale;

    ਜੇ (_this->Get_ਖਿੜਕੀ_Content_Scale) {
        display_scale = _this->Get_ਖਿੜਕੀ_Content_Scale(_this, ਖਿੜਕੀ);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ ਦਸ਼ਮਲਵ pixel_density = SDL_Get_ਖਿੜਕੀ_Pixel_Density(ਖਿੜਕੀ);
        ਅਚਲ ਦਸ਼ਮਲਵ content_scale = SDL_GetDisplayContentScale(ਖਿੜਕੀ->displayID);

        display_scale = pixel_density * content_scale;
    }

    ਜੇ (display_scale != ਖਿੜਕੀ->display_scale) {
        ਖਿੜਕੀ->display_scale = display_scale;
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_DISPLAY_SCALE_ਬਦਲਿਆ, 0, 0);
    }
}

bool SDL_Update_Fullscreen_ਬਹੁਲਕ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ਨਿਰਾ;
    SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ = ਨਿਰਾ;
    ਪੂਰਨ i;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਖਿੜਕੀ->fullscreen_exclusive = false;
    ਖਿੜਕੀ->update_fullscreen_on_display_ਬਦਲਿਆ = false;

    // If we are in the process of hiding don't go back to fullscreen
    ਜੇ (ਖਿੜਕੀ->is_destroying || ਖਿੜਕੀ->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ਜੇ (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_ਖਿੜਕੀ(ਖਿੜਕੀ);
        ਜੇ (!display) {
            // This should never happen, but it did...
            ਜਾਓ ਪੂਰਾ;
        }
    } ਨਹੀਂਤਾਂ {
        ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
            display = _this->displays[i];
            ਜੇ (display->fullscreen_ਖਿੜਕੀ == ਖਿੜਕੀ) {
                ਰੋਕੋ;
            }
        }
        ਜੇ (!display || i == _this->ਅੰਕ_displays) {
            // Already not fullscreen on any display
            display = ਨਿਰਾ;
        }
    }

    ਜੇ (fullscreen) {
        ਬਹੁਲਕ = (SDL_Display_ਬਹੁਲਕ *)SDL_Get_ਖਿੜਕੀ_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ);
        ਜੇ (ਬਹੁਲਕ) {
            ਖਿੜਕੀ->fullscreen_exclusive = true;
        } ਨਹੀਂਤਾਂ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ);
        }
    }

#ਜੇ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ਜੇ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ਜੇ (ਖਿੜਕੀ->is_destroying && !ਖਿੜਕੀ->ਆਖਰੀ_fullscreen_exclusive_display) {
            ਖਿੜਕੀ->fullscreen_exclusive = false;
            ਜੇ (display) {
                display->fullscreen_ਖਿੜਕੀ = ਨਿਰਾ;
            }
            ਜਾਓ ਪੂਰਾ;
        }
        ਜੇ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ਜੇ (fullscreen && Cocoa_Is_ਖਿੜਕੀ_ਵਿੱਚ_Fullscreen_Space(ਖਿੜਕੀ) && !ਖਿੜਕੀ->ਆਖਰੀ_fullscreen_exclusive_display && ਖਿੜਕੀ->fullscreen_exclusive) {
                ਜੇ (!Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_Space(ਖਿੜਕੀ, false, true)) {
                    ਜਾਓ error;
                }
            } ਨਹੀਂਤਾਂ ਜੇ (fullscreen && ਖਿੜਕੀ->ਆਖਰੀ_fullscreen_exclusive_display && !ਖਿੜਕੀ->fullscreen_exclusive) {
                ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
                    SDL_VideoDisplay *ਆਖਰੀ_display = _this->displays[i];
                    ਜੇ (ਆਖਰੀ_display->fullscreen_ਖਿੜਕੀ == ਖਿੜਕੀ) {
                        SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(ਆਖਰੀ_display, ਨਿਰਾ);
                        ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen) {
                            _this->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(_this, ਖਿੜਕੀ, ਆਖਰੀ_display, false);
                        }
                        ਆਖਰੀ_display->fullscreen_ਖਿੜਕੀ = ਨਿਰਾ;
                    }
                }
            }

            ਜੇ (Cocoa_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_Space(ਖਿੜਕੀ, !!fullscreen, syncHint)) {
                ਜਾਓ ਪੂਰਾ;
            }
        }
    }
#ਜੇ_ਅੰਤ

    ਜੇ (display) {
        // Restore the video mode on other displays if needed
        ਲਈ (i = 0; i < _this->ਅੰਕ_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ਜੇ (other != display && other->fullscreen_ਖਿੜਕੀ == ਖਿੜਕੀ) {
                SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(other, ਨਿਰਾ);
                other->fullscreen_ਖਿੜਕੀ = ਨਿਰਾ;
            }
        }
    }

    ਜੇ (fullscreen) {
        ਪੂਰਨ ਬਹੁਲਕ_w = 0, ਬਹੁਲਕ_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ਜੇ (display->fullscreen_ਖਿੜਕੀ &&
            display->fullscreen_ਖਿੜਕੀ != ਖਿੜਕੀ) {
            SDL_Minimize_ਖਿੜਕੀ(display->fullscreen_ਖਿੜਕੀ);
        }

        display->fullscreen_ਸਰਗਰਮ = ਖਿੜਕੀ->fullscreen_exclusive;

        ਜੇ (!SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(display, ਬਹੁਲਕ)) {
            ਜਾਓ error;
        }
        ਜੇ (commit) {
            SDL_Fullscreen_ਨਤੀਜਾ ret = SDL_FULLSCREEN_SUCCEEDED;
            ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen) {
                ret = _this->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(_this, ਖਿੜਕੀ, display, fullscreen);
            } ਨਹੀਂਤਾਂ {
                resized = true;
            }

            ਜੇ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
                    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ENTER_FULLSCREEN, 0, 0);
                }
            } ਨਹੀਂਤਾਂ ਜੇ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_ਸਰਗਰਮ = false;
                ਜਾਓ error;
            }
        }

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
            display->fullscreen_ਖਿੜਕੀ = ਖਿੜਕੀ;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ਜੇ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ਜੇ (ਬਹੁਲਕ) {
                    ਬਹੁਲਕ_w = ਬਹੁਲਕ->w;
                    ਬਹੁਲਕ_h = ਬਹੁਲਕ->h;
                    SDL_GetDisplayBounds(ਬਹੁਲਕ->displayID, &displayRect);
                } ਨਹੀਂਤਾਂ {
                    ਬਹੁਲਕ_w = display->desktop_ਬਹੁਲਕ.w;
                    ਬਹੁਲਕ_h = display->desktop_ਬਹੁਲਕ.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ਜੇ (ਖਿੜਕੀ->w != ਬਹੁਲਕ_w || ਖਿੜਕੀ->h != ਬਹੁਲਕ_h) {
                    resized = true;
                }

                SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, displayRect.x, displayRect.y);

                ਜੇ (resized) {
                    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਬਹੁਲਕ_w, ਬਹੁਲਕ_h);
                } ਨਹੀਂਤਾਂ {
                    SDL_On_ਖਿੜਕੀ_Resized(ਖਿੜਕੀ);
                }
            }
        }
    } ਨਹੀਂਤਾਂ {
        bool resized = false;

        // Restore the desktop mode
        ਜੇ (display) {
            display->fullscreen_ਸਰਗਰਮ = false;

            SDL_ਸੈੱਟ_Display_ਬਹੁਲਕ_For_Display(display, ਨਿਰਾ);
        }
        ਜੇ (commit) {
            SDL_Fullscreen_ਨਤੀਜਾ ret = SDL_FULLSCREEN_SUCCEEDED;
            ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen) {
                SDL_VideoDisplay *ਭਰਿਆ_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_ਖਿੜਕੀ(ਖਿੜਕੀ);
                ਜੇ (ਭਰਿਆ_screen_display) {
                    ret = _this->ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(_this, ਖਿੜਕੀ, ਭਰਿਆ_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ਨਹੀਂਤਾਂ {
                resized = true;
            }

            ਜੇ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
                    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_LEAVE_FULLSCREEN, 0, 0);
                }
            } ਨਹੀਂਤਾਂ ਜੇ (ret == SDL_FULLSCREEN_FAILED) {
                ਜਾਓ error;
            }
        }

        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
            ਜੇ (display) {
                display->fullscreen_ਖਿੜਕੀ = ਨਿਰਾ;
            }

            ਜੇ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, ਖਿੜਕੀ->windowed.x, ਖਿੜਕੀ->windowed.y);
                ਜੇ (resized) {
                    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਖਿੜਕੀ->windowed.w, ਖਿੜਕੀ->windowed.h);
                } ਨਹੀਂਤਾਂ {
                    SDL_On_ਖਿੜਕੀ_Resized(ਖਿੜਕੀ);
                }
            }
        }
    }

ਪੂਰਾ:
    ਖਿੜਕੀ->ਆਖਰੀ_fullscreen_exclusive_display = display && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && ਖਿੜਕੀ->fullscreen_exclusive ? display->id : 0;
    ਵਾਪਸ true;

error:
    ਜੇ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ਵਾਪਸ false;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen_ਬਹੁਲਕ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (ਬਹੁਲਕ) {
        ਜੇ (!SDL_Get_Fullscreen_ਬਹੁਲਕ_ਮੇਲ(ਬਹੁਲਕ)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ, ਬਹੁਲਕ);
    } ਨਹੀਂਤਾਂ {
        SDL_zero(ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ, &ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ);

#ਜੇ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ਜੇ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_ਖਿੜਕੀ_ਵਿੱਚ_Fullscreen_Space_Transition(ਖਿੜਕੀ)) {
        SDL_Sync_ਖਿੜਕੀ(ਖਿੜਕੀ);
    }
#ਜੇ_ਅੰਤ
    ਜੇ (SDL_ਖਿੜਕੀ_FULLSCREEN_VISIBLE(ਖਿੜਕੀ)) {
        SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(ਖਿੜਕੀ);
    }

    ਵਾਪਸ true;
}

ਅਚਲ SDL_Display_ਬਹੁਲਕ *SDL_Get_ਖਿੜਕੀ_Fullscreen_ਬਹੁਲਕ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਿਰਾ);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, ਨਿਰਾ);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        ਵਾਪਸ SDL_Get_Fullscreen_ਬਹੁਲਕ_ਮੇਲ(&ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Get_Fullscreen_ਬਹੁਲਕ_ਮੇਲ(&ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ);
    }
}

ਖਾਲੀ *SDL_Get_ਖਿੜਕੀ_ICCProfile(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ)
{
    ਜੇ (!_this->Get_ਖਿੜਕੀ_ICCProfile) {
        SDL_Unsupported();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ _this->Get_ਖਿੜਕੀ_ICCProfile(_this, ਖਿੜਕੀ, ਮਾਪ);
}

SDL_PixelFormat SDL_Get_ਖਿੜਕੀ_Pixel_Format(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_DisplayID displayID;
    ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਬਹੁਲਕ = SDL_Get_Current_Display_ਬਹੁਲਕ(displayID);
    ਜੇ (ਬਹੁਲਕ) {
        ਵਾਪਸ ਬਹੁਲਕ->format;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CREATE_FLAGS \
    (SDL_ਖਿੜਕੀ_OPENGL | SDL_ਖਿੜਕੀ_BORDERLESS | SDL_ਖਿੜਕੀ_RESIZABLE | SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY | SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ | SDL_ਖਿੜਕੀ_POPUP_MENU | SDL_ਖਿੜਕੀ_UTILITY | SDL_ਖਿੜਕੀ_TOOLTIP | SDL_ਖਿੜਕੀ_VULKAN | SDL_ਖਿੜਕੀ_MINIMIZED | SDL_ਖਿੜਕੀ_METAL | SDL_ਖਿੜਕੀ_TRANSPARENT | SDL_ਖਿੜਕੀ_NOT_FOCUSABLE | SDL_ਖਿੜਕੀ_FILL_DOCUMENT)

ਸਥਿਰ SDL_INLINE bool IsAcceptingDragAndDrop(ਖਾਲੀ)
{
    ਜੇ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_ਪਾਠ)) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

// prepare a newly-created window
ਸਥਿਰ SDL_INLINE ਖਾਲੀ PrepareDragAndDropSupport(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(ਖਿੜਕੀ, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
ਖਾਲੀ SDL_ToggleDragAndDropSupport(ਖਾਲੀ)
{
    ਜੇ (_this && _this->AcceptDragAndDrop) {
        ਅਚਲ bool enable = IsAcceptingDragAndDrop();
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
        ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            _this->AcceptDragAndDrop(ਖਿੜਕੀ, enable);
        }
    }
}

SDL_ਖਿੜਕੀ ** SDLCALL SDL_GetWindows(ਪੂਰਨ *ਗਿਣਤੀ_2)
{
    ਜੇ (ਗਿਣਤੀ_2) {
        *ਗਿਣਤੀ_2 = 0;
    }

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    ਪੂਰਨ ਅੰਕ_added = 0;
    ਪੂਰਨ ਅੰਕ_windows = 0;
    ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        ++ਅੰਕ_windows;
    }

    SDL_ਖਿੜਕੀ **windows = (SDL_ਖਿੜਕੀ **)SDL_malloc((ਅੰਕ_windows + 1) * ਆਕਾਰ(*windows));
    ਜੇ (!windows) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        windows[ਅੰਕ_added++] = ਖਿੜਕੀ;
        ਜੇ (ਅੰਕ_added == ਅੰਕ_windows) {
            // Race condition? Multi-threading not supported, ignore it
            ਰੋਕੋ;
        }
    }
    windows[ਅੰਕ_added] = ਨਿਰਾ;

    ਜੇ (ਗਿਣਤੀ_2) {
        *ਗਿਣਤੀ_2 = ਅੰਕ_added;
    }
    ਵਾਪਸ windows;
}

ਸਥਿਰ ਖਾਲੀ Apply_ਖਿੜਕੀ_Flags(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags)
{
    ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        ਜੇ (!(flags & (SDL_ਖਿੜਕੀ_MINIMIZED | SDL_ਖਿੜਕੀ_MAXIMIZED))) {
            SDL_Restore_ਖਿੜਕੀ(ਖਿੜਕੀ);
        }
        ਜੇ (flags & SDL_ਖਿੜਕੀ_MAXIMIZED) {
            SDL_Maximize_ਖਿੜਕੀ(ਖਿੜਕੀ);
        }

        SDL_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(ਖਿੜਕੀ, (flags & SDL_ਖਿੜਕੀ_FULLSCREEN) != 0);

        ਜੇ (flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
            SDL_Minimize_ਖਿੜਕੀ(ਖਿੜਕੀ);
        }

        ਜੇ (flags & SDL_ਖਿੜਕੀ_MODAL) {
            SDL_ਸੈੱਟ_ਖਿੜਕੀ_Modal(ਖਿੜਕੀ, true);
        }

        ਜੇ (flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED) {
            SDL_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(ਖਿੜਕੀ, true);
        }
        ਜੇ (flags & SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED) {
            SDL_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(ਖਿੜਕੀ, true);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ SDL_ਅੰਤ_ਖਿੜਕੀ_Creation(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags)
{
    PrepareDragAndDropSupport(ਖਿੜਕੀ);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ਨਹੀਂਤਾਂ {
        Apply_ਖਿੜਕੀ_Flags(ਖਿੜਕੀ, flags);
        ਜੇ (!(flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
            SDL_Show_ਖਿੜਕੀ(ਖਿੜਕੀ);
        }
    }

#ਜੇ defined(SDL_PLATFORM_LINUX)
    ਜੇ (!SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਤਰੱਕੀ_State(ਖਿੜਕੀ, SDL_ਤਰੱਕੀ_STATE_NONE);
        SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਤਰੱਕੀ_ਮੁੱਲ(ਖਿੜਕੀ, 0.0f);
    }
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ bool SDL_ContextNotSupported(ਅਚਲ ਅੱਖਰ *name)
{
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ਸਥਿਰ bool SDL_DllNotSupported(ਅਚਲ ਅੱਖਰ *name)
{
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ਸਥਿਰ ਬਣਤਰ {
    ਅਚਲ ਅੱਖਰ *property_name;
    SDL_ਖਿੜਕੀ_Flags flag;
    bool invert_ਮੁੱਲ;
} SDL_ਖਿੜਕੀ_Flag_Properties[] = {
    { SDL_PROP_ਖਿੜਕੀ_CREATE_ALWAYS_ON_ਸਿਖਰ_BOOLEAN,      SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ,       false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_BORDERLESS_BOOLEAN,         SDL_ਖਿੜਕੀ_BORDERLESS,          false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_FOCUSABLE_BOOLEAN,          SDL_ਖਿੜਕੀ_NOT_FOCUSABLE,       true },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_FULLSCREEN_BOOLEAN,         SDL_ਖਿੜਕੀ_FULLSCREEN,          false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_HIDDEN_BOOLEAN,             SDL_ਖਿੜਕੀ_HIDDEN,              false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_ਉੱਚਾ_PIXEL_DENSITY_BOOLEAN, SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY,  false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_MAXIMIZED_BOOLEAN,          SDL_ਖਿੜਕੀ_MAXIMIZED,           false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_MENU_BOOLEAN,               SDL_ਖਿੜਕੀ_POPUP_MENU,          false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_METAL_BOOLEAN,              SDL_ਖਿੜਕੀ_METAL,               false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_MINIMIZED_BOOLEAN,          SDL_ਖਿੜਕੀ_MINIMIZED,           false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_MODAL_BOOLEAN,              SDL_ਖਿੜਕੀ_MODAL,               false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_ਖਿੜਕੀ_MOUSE_GRABBED,       false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_OPENGL_BOOLEAN,             SDL_ਖਿੜਕੀ_OPENGL,              false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_RESIZABLE_BOOLEAN,          SDL_ਖਿੜਕੀ_RESIZABLE,           false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_TRANSPARENT_BOOLEAN,        SDL_ਖਿੜਕੀ_TRANSPARENT,         false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_TOOLTIP_BOOLEAN,            SDL_ਖਿੜਕੀ_TOOLTIP,             false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_UTILITY_BOOLEAN,            SDL_ਖਿੜਕੀ_UTILITY,             false },
    { SDL_PROP_ਖਿੜਕੀ_CREATE_VULKAN_BOOLEAN,             SDL_ਖਿੜਕੀ_VULKAN,              false }
};

ਸਥਿਰ SDL_ਖਿੜਕੀ_Flags SDL_Get_ਖਿੜਕੀ_Flag_Properties(SDL_PropertiesID props)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ i;
    SDL_ਖਿੜਕੀ_Flags flags = (SDL_ਖਿੜਕੀ_Flags)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_FLAGS_ਸੰਖਿਆ, 0);

    ਲਈ (i = 0; i < SDL_arraysize(SDL_ਖਿੜਕੀ_Flag_Properties); ++i) {
        ਜੇ (SDL_ਖਿੜਕੀ_Flag_Properties[i].invert_ਮੁੱਲ) {
            ਜੇ (!SDL_GetBooleanProperty(props, SDL_ਖਿੜਕੀ_Flag_Properties[i].property_name, true)) {
                flags |= SDL_ਖਿੜਕੀ_Flag_Properties[i].flag;
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (SDL_GetBooleanProperty(props, SDL_ਖਿੜਕੀ_Flag_Properties[i].property_name, false)) {
                flags |= SDL_ਖਿੜਕੀ_Flag_Properties[i].flag;
            }
        }
    }
    ਵਾਪਸ flags;
}

SDL_ਖਿੜਕੀ *SDL_Create_ਖਿੜਕੀ_With_Properties(SDL_PropertiesID props)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    ਅਚਲ ਅੱਖਰ *title = SDL_GetStringProperty(props, SDL_PROP_ਖਿੜਕੀ_CREATE_TITLE_STRING, ਨਿਰਾ);
    ਪੂਰਨ x = (ਪੂਰਨ)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_X_ਸੰਖਿਆ, SDL_WINDOWPOS_UNDEFINED);
    ਪੂਰਨ y = (ਪੂਰਨ)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_Y_ਸੰਖਿਆ, SDL_WINDOWPOS_UNDEFINED);
    ਪੂਰਨ w = (ਪੂਰਨ)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਚੌੜਾਈ_ਸੰਖਿਆ, 0);
    ਪੂਰਨ h = (ਪੂਰਨ)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਉਚਾਈ_ਸੰਖਿਆ, 0);
    SDL_ਖਿੜਕੀ *ਮਾਪਾ = (SDL_ਖਿੜਕੀ *)SDL_Get_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਮਾਪਾ_ਸੂਚਕ, ਨਿਰਾ);
    SDL_ਖਿੜਕੀ_Flags flags = SDL_Get_ਖਿੜਕੀ_Flag_Properties(props);
    SDL_ਖਿੜਕੀ_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_ਖਿੜਕੀ_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    ਜੇ (!_this) {
        // Initialize the video system if needed
        ਜੇ (!SDL_Init(SDL_INIT_VIDEO)) {
            ਵਾਪਸ ਨਿਰਾ;
        }

        // Make clang-tidy happy
        ਜੇ (!_this) {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਜੇ ((flags & SDL_ਖਿੜਕੀ_MODAL) && !SDL_ObjectValid(ਮਾਪਾ, SDL_OBJECT_TYPE_ਖਿੜਕੀ)) {
        SDL_ਸੈੱਟ_Error("Modal windows must specify a parent window");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ ((flags & (SDL_ਖਿੜਕੀ_TOOLTIP | SDL_ਖਿੜਕੀ_POPUP_MENU)) != 0) {
        ਜੇ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_ਖਿੜਕੀ_SUPPORT)) {
            SDL_Unsupported();
            ਵਾਪਸ ਨਿਰਾ;
        }

        // Tooltip and popup menu window must specify a parent window
        ਜੇ (!SDL_ObjectValid(ਮਾਪਾ, SDL_OBJECT_TYPE_ਖਿੜਕੀ)) {
            SDL_ਸੈੱਟ_Error("Tooltip and popup menu windows must specify a parent window");
            ਵਾਪਸ ਨਿਰਾ;
        }

        // Remove invalid flags
        flags &= ~(SDL_ਖਿੜਕੀ_MINIMIZED | SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_ਖਿੜਕੀ_UTILITY | SDL_ਖਿੜਕੀ_TOOLTIP | SDL_ਖਿੜਕੀ_POPUP_MENU | SDL_ਖਿੜਕੀ_MODAL);
    ਜੇ (type_flags & (type_flags - 1)) {
        SDL_ਸੈੱਟ_Error("Conflicting window type flags specified: 0x%.8x", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)type_flags);
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Make sure the display list is up to date for window placement
    ਜੇ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ਜੇ (w < 1) {
        w = 1;
    }
    ਜੇ (h < 1) {
        h = 1;
    }

    ਜੇ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ਜੇ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ਨਹੀਂਤਾਂ ਜੇ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ਜੇ (displayID == 0 || SDL_Get_Display_ਸੂਚਕਾਂਕ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ਜੇ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ਜੇ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ਜੇ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ਜੇ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ਜੇ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_ਖਿੜਕੀ_OPENGL | SDL_ਖਿੜਕੀ_METAL | SDL_ਖਿੜਕੀ_VULKAN);
    ਜੇ (graphics_flags & (graphics_flags - 1)) {
        SDL_ਸੈੱਟ_Error("Conflicting window graphics flags specified: 0x%.8x", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)graphics_flags);
        ਵਾਪਸ ਨਿਰਾ;
    }

    // Some platforms have certain graphics backends enabled by default
    ਜੇ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ਜੇ (flags & SDL_ਖਿੜਕੀ_OPENGL) {
        ਜੇ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ਵਾਪਸ ਨਿਰਾ;
        }
        ਜੇ (!SDL_GL_ਲੱਦੋ_Library(ਨਿਰਾ)) {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਜੇ (flags & SDL_ਖਿੜਕੀ_VULKAN) {
        ਜੇ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ਵਾਪਸ ਨਿਰਾ;
        }
        ਜੇ (!SDL_Vulkan_ਲੱਦੋ_Library(ਨਿਰਾ)) {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਜੇ (flags & SDL_ਖਿੜਕੀ_METAL) {
        ਜੇ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ *)SDL_calloc(1, ਆਕਾਰ(*ਖਿੜਕੀ));
    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    SDL_ਸੈੱਟ_Object_Valid(ਖਿੜਕੀ, SDL_OBJECT_TYPE_ਖਿੜਕੀ, true);
    ਖਿੜਕੀ->id = SDL_Get_ਅਗਲਾ_Object_ID();
    ਖਿੜਕੀ->floating.x = ਖਿੜਕੀ->windowed.x = ਖਿੜਕੀ->x = x;
    ਖਿੜਕੀ->floating.y = ਖਿੜਕੀ->windowed.y = ਖਿੜਕੀ->y = y;
    ਖਿੜਕੀ->floating.w = ਖਿੜਕੀ->windowed.w = ਖਿੜਕੀ->w = w;
    ਖਿੜਕੀ->floating.h = ਖਿੜਕੀ->windowed.h = ਖਿੜਕੀ->h = h;
    ਖਿੜਕੀ->undefined_x = undefined_x;
    ਖਿੜਕੀ->undefined_y = undefined_y;
    ਖਿੜਕੀ->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਜੇ (display) {
        SDL_ਸੈੱਟ_ਖਿੜਕੀ_HDRProperties(ਖਿੜਕੀ, &display->HDR, false);
    }

    ਜੇ (flags & SDL_ਖਿੜਕੀ_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        ਖਿੜਕੀ->x = bounds.x;
        ਖਿੜਕੀ->y = bounds.y;
        ਖਿੜਕੀ->w = bounds.w;
        ਖਿੜਕੀ->h = bounds.h;
        ਖਿੜਕੀ->pending_flags |= SDL_ਖਿੜਕੀ_FULLSCREEN;
        flags |= SDL_ਖਿੜਕੀ_FULLSCREEN;
    }

    ਖਿੜਕੀ->flags = ((flags & CREATE_FLAGS) | SDL_ਖਿੜਕੀ_HIDDEN);
    ਖਿੜਕੀ->display_scale = 1.0f;
    ਖਿੜਕੀ->opacity = 1.0f;
    ਖਿੜਕੀ->ਅਗਲਾ = _this->windows;
    ਖਿੜਕੀ->is_destroying = false;
    ਖਿੜਕੀ->displayID = Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਖਿੜਕੀ->external_graphics_context = external_graphics_context;
    ਖਿੜਕੀ->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_ਖਿੜਕੀ_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document) {
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ਜੇ (_this->windows) {
        _this->windows->prev = ਖਿੜਕੀ;
    }
    _this->windows = ਖਿੜਕੀ;

    // Set the parent before creation.
    SDL_Update_ਖਿੜਕੀ_Hierarchy(ਖਿੜਕੀ, ਮਾਪਾ);

    ਜੇ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, ਖਿੜਕੀ, props)) {
        SDL_ਧੱਕੋ_Error();
        SDL_Destroy_ਖਿੜਕੀ(ਖਿੜਕੀ);
        SDL_ਕੱਢੋ_Error();
        ਵਾਪਸ ਨਿਰਾ;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ਜੇ !defined(SDL_PLATFORM_WINDOWS)
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MINIMIZED;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (title) {
        SDL_ਸੈੱਟ_ਖਿੜਕੀ_Title(ਖਿੜਕੀ, title);
    }
    SDL_ਅੰਤ_ਖਿੜਕੀ_Creation(ਖਿੜਕੀ, flags);

    // Make sure window pixel size is up to date
    SDL_Check_ਖਿੜਕੀ_Pixel_ਮਾਪ_ਬਦਲਿਆ(ਖਿੜਕੀ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#ਜੇ_ਅੰਤ

    SDL_ClearError();

    ਵਾਪਸ ਖਿੜਕੀ;
}

SDL_ਖਿੜਕੀ *SDL_Create_ਖਿੜਕੀ(ਅਚਲ ਅੱਖਰ *title, ਪੂਰਨ w, ਪੂਰਨ h, SDL_ਖਿੜਕੀ_Flags flags)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    SDL_PropertiesID props = SDL_CreateProperties();
    ਜੇ (title && *title) {
        SDL_ਸੈੱਟ_String_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_TITLE_STRING, title);
    }
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਚੌੜਾਈ_ਸੰਖਿਆ, w);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਉਚਾਈ_ਸੰਖਿਆ, h);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_FLAGS_ਸੰਖਿਆ, flags);
    ਖਿੜਕੀ = SDL_Create_ਖਿੜਕੀ_With_Properties(props);
    SDL_DestroyProperties(props);
    ਵਾਪਸ ਖਿੜਕੀ;
}

SDL_ਖਿੜਕੀ *SDL_Create_Popup_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਮਾਪਾ, ਪੂਰਨ ਵਿੱਥ_x, ਪੂਰਨ ਵਿੱਥ_y, ਪੂਰਨ w, ਪੂਰਨ h, SDL_ਖਿੜਕੀ_Flags flags)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ਜੇ (!(flags & (SDL_ਖਿੜਕੀ_TOOLTIP | SDL_ਖਿੜਕੀ_POPUP_MENU))) {
        SDL_ਸੈੱਟ_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਮਾਪਾ_ਸੂਚਕ, ਮਾਪਾ);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_X_ਸੰਖਿਆ, ਵਿੱਥ_x);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_Y_ਸੰਖਿਆ, ਵਿੱਥ_y);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਚੌੜਾਈ_ਸੰਖਿਆ, w);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_ਉਚਾਈ_ਸੰਖਿਆ, h);
    SDL_ਸੈੱਟ_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_CREATE_FLAGS_ਸੰਖਿਆ, flags);
    ਖਿੜਕੀ = SDL_Create_ਖਿੜਕੀ_With_Properties(props);
    SDL_DestroyProperties(props);
    ਵਾਪਸ ਖਿੜਕੀ;
}

ਸਥਿਰ bool SDL_Reconfigure_ਖਿੜਕੀ_ਅੰਦਰੂਨੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ਜੇ (!_this->Reconfigure_ਖਿੜਕੀ) {
        ਵਾਪਸ false;
    }

    ਅਚਲ SDL_ਖਿੜਕੀ_Flags graphics_flags = flags & (SDL_ਖਿੜਕੀ_OPENGL | SDL_ਖਿੜਕੀ_METAL | SDL_ਖਿੜਕੀ_VULKAN);
    ਜੇ (graphics_flags & (graphics_flags - 1)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Conflicting window flags specified");
    }

    ਜੇ ((flags & SDL_ਖਿੜਕੀ_OPENGL) && !_this->GL_CreateContext) {
        ਵਾਪਸ SDL_ContextNotSupported("OpenGL");
    }
    ਜੇ ((flags & SDL_ਖਿੜਕੀ_VULKAN) && !_this->Vulkan_CreateSurface) {
        ਵਾਪਸ SDL_ContextNotSupported("Vulkan");
    }
    ਜੇ ((flags & SDL_ਖਿੜਕੀ_METAL) && !_this->Metal_CreateView) {
        ਵਾਪਸ SDL_ContextNotSupported("Metal");
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ਜੇ (ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_OPENGL | SDL_ਖਿੜਕੀ_METAL | SDL_ਖਿੜਕੀ_VULKAN)) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ਜੇ (!_this->Reconfigure_ਖਿੜਕੀ(_this, ਖਿੜਕੀ, 0)) {
            ਵਾਪਸ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        ਖਿੜਕੀ->flags &= ~(SDL_ਖਿੜਕੀ_OPENGL | SDL_ਖਿੜਕੀ_METAL | SDL_ਖਿੜਕੀ_VULKAN);
    }

    SDL_Destroy_ਖਿੜਕੀ_Surface(ਖਿੜਕੀ);

    ਜੇ (graphics_flags & SDL_ਖਿੜਕੀ_OPENGL) {
        loaded_opengl = SDL_GL_ਲੱਦੋ_Library(ਨਿਰਾ);
        ਜੇ (!loaded_opengl) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (graphics_flags & SDL_ਖਿੜਕੀ_VULKAN) {
        loaded_vulkan = SDL_Vulkan_ਲੱਦੋ_Library(ਨਿਰਾ);
        ਜੇ (!loaded_vulkan) {
            ਵਾਪਸ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ਜੇ (!_this->Reconfigure_ਖਿੜਕੀ(_this, ਖਿੜਕੀ, graphics_flags)) {
        ਜੇ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ਜੇ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ਵਾਪਸ false;
    }

    ਖਿੜਕੀ->flags |= graphics_flags;

    ਵਾਪਸ true;
}

bool SDL_Recreate_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_ਲੱਦੋ = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_ਲੱਦੋ = false;
    SDL_ਖਿੜਕੀ_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_ਖਿੜਕੀ_OPENGL | SDL_ਖਿੜਕੀ_METAL | SDL_ਖਿੜਕੀ_VULKAN);
    ਜੇ (graphics_flags & (graphics_flags - 1)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Conflicting window flags specified");
    }

    ਜੇ ((flags & SDL_ਖਿੜਕੀ_OPENGL) && !_this->GL_CreateContext) {
        ਵਾਪਸ SDL_ContextNotSupported("OpenGL");
    }
    ਜੇ ((flags & SDL_ਖਿੜਕੀ_VULKAN) && !_this->Vulkan_CreateSurface) {
        ਵਾਪਸ SDL_ContextNotSupported("Vulkan");
    }
    ਜੇ ((flags & SDL_ਖਿੜਕੀ_METAL) && !_this->Metal_CreateView) {
        ਵਾਪਸ SDL_ContextNotSupported("Metal");
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_ਖਿੜਕੀ_EXTERNAL;
    } ਨਹੀਂਤਾਂ {
        flags &= ~SDL_ਖਿੜਕੀ_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MODAL) {
        SDL_ਸੈੱਟ_ਖਿੜਕੀ_Modal(ਖਿੜਕੀ, false);
    }

    // Restore video mode, etc.
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
        ਅਚਲ bool restore_on_show = ਖਿੜਕੀ->restore_on_show;
        SDL_Hide_ਖਿੜਕੀ(ਖਿੜਕੀ);
        ਖਿੜਕੀ->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_ਖਿੜਕੀ_Surface(ਖਿੜਕੀ);

    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) != (flags & SDL_ਖਿੜਕੀ_OPENGL)) {
        ਜੇ (flags & SDL_ਖਿੜਕੀ_OPENGL) {
            need_gl_ਲੱਦੋ = true;
        } ਨਹੀਂਤਾਂ {
            need_gl_unload = true;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        need_gl_unload = true;
        need_gl_ਲੱਦੋ = true;
    }

    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN) != (flags & SDL_ਖਿੜਕੀ_VULKAN)) {
        ਜੇ (flags & SDL_ਖਿੜਕੀ_VULKAN) {
            need_vulkan_ਲੱਦੋ = true;
        } ਨਹੀਂਤਾਂ {
            need_vulkan_unload = true;
        }
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_ਲੱਦੋ = true;
    }

    ਜੇ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ਜੇ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ਜੇ (_this->Destroy_ਖਿੜਕੀ && !(flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
        _this->Destroy_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (need_gl_ਲੱਦੋ) {
        ਜੇ (!SDL_GL_ਲੱਦੋ_Library(ਨਿਰਾ)) {
            ਵਾਪਸ false;
        }
        loaded_opengl = true;
    }

    ਜੇ (need_vulkan_ਲੱਦੋ) {
        ਜੇ (!SDL_Vulkan_ਲੱਦੋ_Library(ਨਿਰਾ)) {
            ਵਾਪਸ false;
        }
        loaded_vulkan = true;
    }

    ਖਿੜਕੀ->flags = ((flags & CREATE_FLAGS) | SDL_ਖਿੜਕੀ_HIDDEN);
    ਖਿੜਕੀ->is_destroying = false;

    ਜੇ (_this->CreateSDLWindow && !(flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        ਖਿੜਕੀ->x = ਖਿੜਕੀ->windowed.x = ਖਿੜਕੀ->floating.x;
        ਖਿੜਕੀ->y = ਖਿੜਕੀ->windowed.y = ਖਿੜਕੀ->floating.y;
        ਖਿੜਕੀ->w = ਖਿੜਕੀ->windowed.w = ਖਿੜਕੀ->floating.w;
        ਖਿੜਕੀ->h = ਖਿੜਕੀ->windowed.h = ਖਿੜਕੀ->floating.h;

        ਜੇ (!_this->CreateSDLWindow(_this, ਖਿੜਕੀ, 0)) {
            ਜੇ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_OPENGL;
            }
            ਜੇ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_VULKAN;
            }
            ਵਾਪਸ false;
        }
    }

    ਜੇ (flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_EXTERNAL;
    }

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Title && ਖਿੜਕੀ->title) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Title(_this, ਖਿੜਕੀ);
    }

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Icon && ਖਿੜਕੀ->icon) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Icon(_this, ਖਿੜਕੀ, ਖਿੜਕੀ->icon);
    }

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ && (ਖਿੜਕੀ->min_w || ਖਿੜਕੀ->min_h)) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ && (ਖਿੜਕੀ->max_w || ਖਿੜਕੀ->max_h)) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ && (ਖਿੜਕੀ->min_aspect > 0.0f || ਖਿੜਕੀ->max_aspect > 0.0f)) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(_this, ਖਿੜਕੀ);
    }

    ਜੇ (ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(ਖਿੜਕੀ, true);
    }

    SDL_ਅੰਤ_ਖਿੜਕੀ_Creation(ਖਿੜਕੀ, flags);

    ਵਾਪਸ true;
}

bool SDL_Reconfigure_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ਜੇ (!SDL_Reconfigure_ਖਿੜਕੀ_ਅੰਦਰੂਨੀ(ਖਿੜਕੀ, flags)) {
        ਵਾਪਸ SDL_Recreate_ਖਿੜਕੀ(ਖਿੜਕੀ, flags);
    }

    ਵਾਪਸ true;
}

bool SDL_HasWindows(ਖਾਲੀ)
{
    ਵਾਪਸ _this && _this->windows;
}

SDL_ਖਿੜਕੀ_ID SDL_Get_ਖਿੜਕੀ_ID(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0);

    ਵਾਪਸ ਖਿੜਕੀ->id;
}

SDL_ਖਿੜਕੀ *SDL_Get_ਖਿੜਕੀ_From_ID(SDL_ਖਿੜਕੀ_ID id)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (id) {
        ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            ਜੇ (ਖਿੜਕੀ->id == id) {
                ਵਾਪਸ ਖਿੜਕੀ;
            }
        }
    }
    SDL_ਸੈੱਟ_Error("Invalid window ID");
    ਵਾਪਸ ਨਿਰਾ;
}

SDL_ਖਿੜਕੀ *SDL_Get_ਖਿੜਕੀ_ਮਾਪਾ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਿਰਾ);

    ਵਾਪਸ ਖਿੜਕੀ->ਮਾਪਾ;
}

SDL_PropertiesID SDL_Get_ਖਿੜਕੀ_Properties(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0);

    ਜੇ (ਖਿੜਕੀ->props == 0) {
        ਖਿੜਕੀ->props = SDL_CreateProperties();
    }
    ਵਾਪਸ ਖਿੜਕੀ->props;
}

SDL_ਖਿੜਕੀ_Flags SDL_Get_ਖਿੜਕੀ_Flags(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, 0);

    ਵਾਪਸ ਖਿੜਕੀ->flags | ਖਿੜਕੀ->pending_flags;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ ਅੱਖਰ *title)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (title == ਖਿੜਕੀ->title) {
        ਵਾਪਸ true;
    }
    ਜੇ (!title) {
        title = "";
    }
    ਜੇ (ਖਿੜਕੀ->title && SDL_strcmp(title, ਖਿੜਕੀ->title) == 0) {
        ਵਾਪਸ true;
    }

    SDL_free(ਖਿੜਕੀ->title);

    ਖਿੜਕੀ->title = SDL_strdup(title);

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Title) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Title(_this, ਖਿੜਕੀ);
    }
    ਵਾਪਸ true;
}

ਅਚਲ ਅੱਖਰ *SDL_Get_ਖਿੜਕੀ_Title(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, "");

    ਵਾਪਸ ਖਿੜਕੀ->title ? ਖਿੜਕੀ->title : "";
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    CHECK_PARAM(!icon) {
        ਵਾਪਸ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(ਖਿੜਕੀ->icon);

    // Convert the icon into ARGB8888
    ਖਿੜਕੀ->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ਜੇ (!ਖਿੜਕੀ->icon) {
        ਵਾਪਸ false;
    }

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Icon) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਵਾਪਸ _this->ਸੈੱਟ_ਖਿੜਕੀ_Icon(_this, ਖਿੜਕੀ, ਖਿੜਕੀ->icon);
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y)
{
    SDL_DisplayID original_displayID;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਅਚਲ ਪੂਰਨ w = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਖਿੜਕੀ->windowed.w;
    ਅਚਲ ਪੂਰਨ h = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਖਿੜਕੀ->windowed.h;

    original_displayID = Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
    ਖਿੜਕੀ->pending_displayID = 0;

    ਜੇ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = ਖਿੜਕੀ->windowed.x;
    }
    ਜੇ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = ਖਿੜਕੀ->windowed.y;
    }
    ਜੇ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ਜੇ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ਜੇ (displayID == 0 || SDL_Get_Display_ਸੂਚਕਾਂਕ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        ਖਿੜਕੀ->pending_displayID = displayID;

        SDL_zero(bounds);
        ਜੇ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ਜੇ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ਵਾਪਸ false;
            }
        }
        ਜੇ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ਜੇ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ਨਹੀਂਤਾਂ {
        /* See if the requested window position matches the origin of any displays and set
         * the pending fullscreen display ID if it does. This needs to be set early in case
         * the window is prevented from moving to the exact origin due to struts.
         */
        ਖਿੜਕੀ->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    ਖਿੜਕੀ->pending.x = x;
    ਖਿੜਕੀ->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    ਜੇ (!_this->Sync_ਖਿੜਕੀ && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਖਿੜਕੀ->floating.x = ਖਿੜਕੀ->windowed.x = x;
        ਖਿੜਕੀ->floating.y = ਖਿੜਕੀ->windowed.y = y;
    }
    ਖਿੜਕੀ->undefined_x = false;
    ਖਿੜਕੀ->undefined_y = false;
    ਖਿੜਕੀ->ਆਖਰੀ_position_pending = true;

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Position) {
        ਅਚਲ bool ਨਤੀਜਾ = _this->ਸੈੱਟ_ਖਿੜਕੀ_Position(_this, ਖਿੜਕੀ);
        ਜੇ (ਨਤੀਜਾ) {
            SDL_SyncIfRequired(ਖਿੜਕੀ);
        }
        ਵਾਪਸ ਨਤੀਜਾ;
    }

    ਵਾਪਸ SDL_Unsupported();
}

bool SDL_Get_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *x, ਪੂਰਨ *y)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ਨਹੀਂਤਾਂ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) != 0);
#ਜੇ_ਅੰਤ
    ਜੇ (use_display_origin) {
        SDL_DisplayID displayID;

        ਜੇ (x) {
            *x = 0;
        }
        ਜੇ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
        ਜੇ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ਜੇ (x) {
                *x = bounds.x;
            }
            ਜੇ (y) {
                *y = bounds.y;
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ bool use_pending = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) && ਖਿੜਕੀ->ਆਖਰੀ_position_pending;
        ਜੇ (x) {
            *x = use_pending ? ਖਿੜਕੀ->pending.x : ਖਿੜਕੀ->x;
        }
        ਜੇ (y) {
            *y = use_pending ? ਖਿੜਕੀ->pending.y : ਖਿੜਕੀ->y;
        }
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Bordered) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਅਚਲ bool want = bordered;
    ਅਚਲ bool have = !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS);
    ਜੇ (want != have) {
        ਜੇ (want) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_BORDERLESS;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_BORDERLESS;
        }
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Bordered(_this, ਖਿੜਕੀ, want);
    }

    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Resizable) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਅਚਲ bool want = resizable;
    ਅਚਲ bool have = ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) != 0);
    ਜੇ (want != have) {
        ਜੇ (want) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_RESIZABLE;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_RESIZABLE;
            SDL_copyp(&ਖਿੜਕੀ->windowed, &ਖਿੜਕੀ->floating);
        }
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Resizable(_this, ਖਿੜਕੀ, want);
    }

    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool on_ਸਿਖਰ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਅਚਲ bool want = on_ਸਿਖਰ;
    ਅਚਲ bool have = ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ) != 0);
    ਜੇ (want != have) {
        ਜੇ (want) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_ALWAYS_ON_ਸਿਖਰ;
        }
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(_this, ਖਿੜਕੀ, want);
    }

    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ w, ਪੂਰਨ h)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    CHECK_PARAM(w <= 0) {
        ਵਾਪਸ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ਵਾਪਸ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    ਦਸ਼ਮਲਵ new_aspect = w / (ਦਸ਼ਮਲਵ)h;
    ਜੇ (ਖਿੜਕੀ->max_aspect > 0.0f && new_aspect > ਖਿੜਕੀ->max_aspect) {
        w = (ਪੂਰਨ)SDL_roundf(h * ਖਿੜਕੀ->max_aspect);
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->min_aspect > 0.0f && new_aspect < ਖਿੜਕੀ->min_aspect) {
        h = (ਪੂਰਨ)SDL_roundf(w / ਖਿੜਕੀ->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ਜੇ (ਖਿੜਕੀ->min_w && w < ਖਿੜਕੀ->min_w) {
        w = ਖਿੜਕੀ->min_w;
    }
    ਜੇ (ਖਿੜਕੀ->max_w && w > ਖਿੜਕੀ->max_w) {
        w = ਖਿੜਕੀ->max_w;
    }
    ਜੇ (ਖਿੜਕੀ->min_h && h < ਖਿੜਕੀ->min_h) {
        h = ਖਿੜਕੀ->min_h;
    }
    ਜੇ (ਖਿੜਕੀ->max_h && h > ਖਿੜਕੀ->max_h) {
        h = ਖਿੜਕੀ->max_h;
    }

    ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending = true;
    ਖਿੜਕੀ->pending.w = w;
    ਖਿੜਕੀ->pending.h = h;

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(_this, ਖਿੜਕੀ);
        SDL_SyncIfRequired(ਖਿੜਕੀ);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_Unsupported();
    }
    ਵਾਪਸ true;
}

bool SDL_Get_ਖਿੜਕੀ_ਮਾਪ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    ਜੇ (w) {
        *w = ਖਿੜਕੀ->w;
    }
    ਜੇ (h) {
        *h = ਖਿੜਕੀ->h;
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ min_aspect, ਦਸ਼ਮਲਵ max_aspect)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਖਿੜਕੀ->min_aspect = min_aspect;
    ਖਿੜਕੀ->max_aspect = max_aspect;

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(_this, ਖਿੜਕੀ);
    }

    // Ensure that window has the correct aspect ratio
    ਪੂਰਨ w = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਖਿੜਕੀ->floating.w;
    ਪੂਰਨ h = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਖਿੜਕੀ->floating.h;
    ਵਾਪਸ SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(ਖਿੜਕੀ, w, h);
}

bool SDL_Get_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ *min_aspect, ਦਸ਼ਮਲਵ *max_aspect)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (min_aspect) {
        *min_aspect = ਖਿੜਕੀ->min_aspect;
    }
    ਜੇ (max_aspect) {
        *max_aspect = ਖਿੜਕੀ->max_aspect;
    }
    ਵਾਪਸ true;
}

bool SDL_Get_ਖਿੜਕੀ_Borders_ਮਾਪ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *ਸਿਖਰ, ਪੂਰਨ *ਖੱਬਾ, ਪੂਰਨ *bottom, ਪੂਰਨ *ਸੱਜਾ)
{
    ਪੂਰਨ dummy = 0;

    ਜੇ (!ਸਿਖਰ) {
        ਸਿਖਰ = &dummy;
    }
    ਜੇ (!ਖੱਬਾ) {
        ਖੱਬਾ = &dummy;
    }
    ਜੇ (!ਸੱਜਾ) {
        ਸੱਜਾ = &dummy;
    }
    ਜੇ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *ਸਿਖਰ = *ਖੱਬਾ = *bottom = *ਸੱਜਾ = 0;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!_this->Get_ਖਿੜਕੀ_Borders_ਮਾਪ) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਵਾਪਸ _this->Get_ਖਿੜਕੀ_Borders_ਮਾਪ(_this, ਖਿੜਕੀ, ਸਿਖਰ, ਖੱਬਾ, bottom, ਸੱਜਾ);
}

bool SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h)
{
    ਪੂਰਨ filter;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!w) {
        w = &filter;
    }

    ਜੇ (!h) {
        h = &filter;
    }

    ਜੇ (_this->Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels) {
        _this->Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(_this, ਖਿੜਕੀ, w, h);
    } ਨਹੀਂਤਾਂ {
        SDL_DisplayID displayID = Get_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ);
        ਅਚਲ SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ;

        SDL_Get_ਖਿੜਕੀ_ਮਾਪ(ਖਿੜਕੀ, w, h);

        ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && SDL_Get_ਖਿੜਕੀ_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ)) {
            ਬਹੁਲਕ = SDL_Get_Current_Display_ਬਹੁਲਕ(displayID);
        } ਨਹੀਂਤਾਂ {
            ਬਹੁਲਕ = SDL_Get_Desktop_Display_ਬਹੁਲਕ(displayID);
        }
        ਜੇ (ਬਹੁਲਕ) {
            *w = (ਪੂਰਨ)SDL_ceilf(*w * ਬਹੁਲਕ->pixel_density);
            *h = (ਪੂਰਨ)SDL_ceilf(*h * ਬਹੁਲਕ->pixel_density);
        }
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ min_w, ਪੂਰਨ min_h)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_PARAM(min_w < 0) {
        ਵਾਪਸ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ਵਾਪਸ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((ਖਿੜਕੀ->max_w && min_w > ਖਿੜਕੀ->max_w) || (ਖਿੜਕੀ->max_h && min_h > ਖਿੜਕੀ->max_h)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    ਖਿੜਕੀ->min_w = min_w;
    ਖਿੜਕੀ->min_h = min_h;

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(_this, ਖਿੜਕੀ);
    }

    // Ensure that window is not smaller than minimal size
    ਪੂਰਨ w = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਖਿੜਕੀ->floating.w;
    ਪੂਰਨ h = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਖਿੜਕੀ->floating.h;
    ਵਾਪਸ SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(ਖਿੜਕੀ, w, h);
}

bool SDL_Get_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *min_w, ਪੂਰਨ *min_h)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    ਜੇ (min_w) {
        *min_w = ਖਿੜਕੀ->min_w;
    }
    ਜੇ (min_h) {
        *min_h = ਖਿੜਕੀ->min_h;
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ max_w, ਪੂਰਨ max_h)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_PARAM(max_w < 0) {
        ਵਾਪਸ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ਵਾਪਸ SDL_InvalidParamError("max_h");
    }

    ਜੇ ((max_w && max_w < ਖਿੜਕੀ->min_w) ||
        (max_h && max_h < ਖਿੜਕੀ->min_h)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    ਖਿੜਕੀ->max_w = max_w;
    ਖਿੜਕੀ->max_h = max_h;

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(_this, ਖਿੜਕੀ);
    }

    // Ensure that window is not larger than maximal size
    ਪੂਰਨ w = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.w : ਖਿੜਕੀ->floating.w;
    ਪੂਰਨ h = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending ? ਖਿੜਕੀ->pending.h : ਖਿੜਕੀ->floating.h;
    ਵਾਪਸ SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(ਖਿੜਕੀ, w, h);
}

bool SDL_Get_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *max_w, ਪੂਰਨ *max_h)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    ਜੇ (max_w) {
        *max_w = ਖਿੜਕੀ->max_w;
    }
    ਜੇ (max_h) {
        *max_h = ਖਿੜਕੀ->max_h;
    }
    ਵਾਪਸ true;
}

bool SDL_Show_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ *ਬੱਚਾ;
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
        ਵਾਪਸ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ਜੇ (ਖਿੜਕੀ->ਮਾਪਾ && (ਖਿੜਕੀ->ਮਾਪਾ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
        ਖਿੜਕੀ->restore_on_show = true;
        ਵਾਪਸ true;
    }

    ਜੇ (_this->Show_ਖਿੜਕੀ) {
        _this->Show_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
        SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
    }
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);

    // Restore child windows
    ਲਈ (ਬੱਚਾ = ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ; ਬੱਚਾ; ਬੱਚਾ = ਬੱਚਾ->ਅਗਲਾ_sibling) {
        ਜੇ (!ਬੱਚਾ->restore_on_show && (ਬੱਚਾ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
            ਰੋਕੋ;
        }
        SDL_Show_ਖਿੜਕੀ(ਬੱਚਾ);
        ਬੱਚਾ->restore_on_show = false;
    }
    ਵਾਪਸ true;
}

bool SDL_Hide_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ *ਬੱਚਾ;
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਖਿੜਕੀ->restore_on_show = false;
        ਵਾਪਸ true;
    }

    // Hide all child windows
    ਲਈ (ਬੱਚਾ = ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ; ਬੱਚਾ; ਬੱਚਾ = ਬੱਚਾ->ਅਗਲਾ_sibling) {
        ਜੇ (ਬੱਚਾ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
            ਰੋਕੋ;
        }
        SDL_Hide_ਖਿੜਕੀ(ਬੱਚਾ);
        ਬੱਚਾ->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ਅਚਲ SDL_ਖਿੜਕੀ_Flags pending_ਨਕਾਬ = (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_MINIMIZED | SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED | SDL_ਖਿੜਕੀ_MOUSE_GRABBED);
    ਖਿੜਕੀ->pending_flags = (ਖਿੜਕੀ->flags & pending_ਨਕਾਬ);

    ਖਿੜਕੀ->is_hiding = true;
    ਜੇ (_this->Hide_ਖਿੜਕੀ) {
        _this->Hide_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
        SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
    }
    ਖਿੜਕੀ->is_hiding = false;
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_HIDDEN, 0, 0);
    ਵਾਪਸ true;
}

bool SDL_Raise_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਵਾਪਸ true;
    }
    ਜੇ (_this->Raise_ਖਿੜਕੀ) {
        _this->Raise_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }
    ਵਾਪਸ true;
}

bool SDL_Maximize_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (!_this->Maximize_ਖਿੜਕੀ) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਖਿੜਕੀ->pending_flags |= SDL_ਖਿੜਕੀ_MAXIMIZED;
        ਵਾਪਸ true;
    }

    _this->Maximize_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    SDL_SyncIfRequired(ਖਿੜਕੀ);
    ਵਾਪਸ true;
}

bool SDL_Minimize_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (!_this->Minimize_ਖਿੜਕੀ) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਖਿੜਕੀ->pending_flags |= SDL_ਖਿੜਕੀ_MINIMIZED;
        ਵਾਪਸ true;
    }

    _this->Minimize_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    SDL_SyncIfRequired(ਖਿੜਕੀ);
    ਵਾਪਸ true;
}

bool SDL_Restore_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (!_this->Restore_ਖਿੜਕੀ) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਖਿੜਕੀ->pending_flags &= ~(SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_MINIMIZED);
        ਵਾਪਸ true;
    }

    _this->Restore_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    SDL_SyncIfRequired(ਖਿੜਕੀ);
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool fullscreen)
{
    bool ਨਤੀਜਾ;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਜੇ (fullscreen) {
            ਖਿੜਕੀ->pending_flags |= SDL_ਖਿੜਕੀ_FULLSCREEN;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->pending_flags &= ~SDL_ਖਿੜਕੀ_FULLSCREEN;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ, &ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ);
    }

    ਨਤੀਜਾ = SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ਜੇ (!fullscreen || !ਨਤੀਜਾ) {
        // Clear the current fullscreen mode.
        SDL_zero(ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ);
    }

    ਜੇ (ਨਤੀਜਾ) {
        SDL_SyncIfRequired(ਖਿੜਕੀ);
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_Sync_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (_this->Sync_ਖਿੜਕੀ) {
        ਵਾਪਸ _this->Sync_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ true;
    }
}

ਸਥਿਰ bool ShouldAttemptTextureFramebuffer(ਖਾਲੀ)
{
    ਅਚਲ ਅੱਖਰ *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ਜੇ (!_this->Create_ਖਿੜਕੀ_Framebuffer) {
        ਵਾਪਸ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ਜੇ (hint && *hint) {
        ਜੇ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ਨਹੀਂਤਾਂ {
            attempt_texture_framebuffer = true;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ਨਹੀਂਤਾਂ {
            attempt_texture_framebuffer = false;
        }
    }
    ਵਾਪਸ attempt_texture_framebuffer;
}

ਸਥਿਰ SDL_Surface *SDL_Create_ਖਿੜਕੀ_Framebuffer(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    ਖਾਲੀ *pixels = ਨਿਰਾ;
    ਪੂਰਨ pitch = 0;
    bool created_framebuffer = false;
    ਪੂਰਨ w, h;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    ਜੇ (!_this->checked_texture_framebuffer) {
        ਜੇ (ShouldAttemptTextureFramebuffer()) {
            ਜੇ (!SDL_Create_ਖਿੜਕੀ_Texture(_this, ਖਿੜਕੀ, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ਨਹੀਂਤਾਂ {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_ਖਿੜਕੀ_Framebuffer = SDL_Create_ਖਿੜਕੀ_Texture;
                _this->ਸੈੱਟ_ਖਿੜਕੀ_Framebuffer_VSync = SDL_ਸੈੱਟ_ਖਿੜਕੀ_Texture_VSync;
                _this->Get_ਖਿੜਕੀ_Framebuffer_VSync = SDL_Get_ਖਿੜਕੀ_Texture_VSync;
                _this->Update_ਖਿੜਕੀ_Framebuffer = SDL_Update_ਖਿੜਕੀ_Texture;
                _this->Destroy_ਖਿੜਕੀ_Framebuffer = SDL_Destroy_ਖਿੜਕੀ_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    ਜੇ (!created_framebuffer) {
        ਜੇ (!_this->Create_ਖਿੜਕੀ_Framebuffer || !_this->Update_ਖਿੜਕੀ_Framebuffer) {
            SDL_ਸੈੱਟ_Error("Window framebuffer support not available");
            ਵਾਪਸ ਨਿਰਾ;
        }

        ਜੇ (!_this->Create_ਖਿੜਕੀ_Framebuffer(_this, ਖਿੜਕੀ, &format, &pixels, &pitch)) {
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    ਜੇ (ਖਿੜਕੀ->surface) {
        // We may have gone recursive and already created the surface
        ਵਾਪਸ ਖਿੜਕੀ->surface;
    }

    ਵਾਪਸ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_ਖਿੜਕੀ_Has_Surface(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਵਾਪਸ ਖਿੜਕੀ->surface ? true : false;
}

SDL_Surface *SDL_Get_ਖਿੜਕੀ_Surface(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਿਰਾ);

    ਜੇ (!ਖਿੜਕੀ->surface_valid) {
        ਜੇ (ਖਿੜਕੀ->surface) {
            ਖਿੜਕੀ->surface->ਅੰਦਰੂਨੀ_flags &= ~SDL_ਅੰਦਰੂਨੀ_SURFACE_DONTFREE;
            SDL_DestroySurface(ਖਿੜਕੀ->surface);
            ਖਿੜਕੀ->surface = ਨਿਰਾ;
        }

        ਖਿੜਕੀ->surface = SDL_Create_ਖਿੜਕੀ_Framebuffer(ਖਿੜਕੀ);
        ਜੇ (ਖਿੜਕੀ->surface) {
            ਖਿੜਕੀ->surface_valid = true;
            ਖਿੜਕੀ->surface->ਅੰਦਰੂਨੀ_flags |= SDL_ਅੰਦਰੂਨੀ_SURFACE_DONTFREE;
        }
    }
    ਵਾਪਸ ਖਿੜਕੀ->surface;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Surface_VSync(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ vsync)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Framebuffer_VSync) {
        ਵਾਪਸ SDL_Unsupported();
    }
    ਵਾਪਸ _this->ਸੈੱਟ_ਖਿੜਕੀ_Framebuffer_VSync(_this, ਖਿੜਕੀ, vsync);
}

bool SDL_Get_ਖਿੜਕੀ_Surface_VSync(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *vsync)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!_this->Get_ਖਿੜਕੀ_Framebuffer_VSync) {
        ਵਾਪਸ SDL_Unsupported();
    }
    ਵਾਪਸ _this->Get_ਖਿੜਕੀ_Framebuffer_VSync(_this, ਖਿੜਕੀ, vsync);
}

bool SDL_Update_ਖਿੜਕੀ_Surface(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Rect ਭਰਿਆ_rect;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਭਰਿਆ_rect.x = 0;
    ਭਰਿਆ_rect.y = 0;
    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &ਭਰਿਆ_rect.w, &ਭਰਿਆ_rect.h);

    ਵਾਪਸ SDL_Update_ਖਿੜਕੀ_Surface_Rects(ਖਿੜਕੀ, &ਭਰਿਆ_rect, 1);
}

bool SDL_Update_ਖਿੜਕੀ_Surface_Rects(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects,
                                 ਪੂਰਨ numrects)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!ਖਿੜਕੀ->surface_valid) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ਵਾਪਸ _this->Update_ਖਿੜਕੀ_Framebuffer(_this, ਖਿੜਕੀ, rects, numrects);
}

bool SDL_Destroy_ਖਿੜਕੀ_Surface(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->surface) {
        ਖਿੜਕੀ->surface->ਅੰਦਰੂਨੀ_flags &= ~SDL_ਅੰਦਰੂਨੀ_SURFACE_DONTFREE;
        SDL_DestroySurface(ਖਿੜਕੀ->surface);
        ਖਿੜਕੀ->surface = ਨਿਰਾ;
        ਖਿੜਕੀ->surface_valid = false;
    }

    ਜੇ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ਜੇ (_this->Destroy_ਖਿੜਕੀ_Framebuffer) {
            _this->Destroy_ਖਿੜਕੀ_Framebuffer(_this, ਖਿੜਕੀ);
        }
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity)
{
    bool ਨਤੀਜਾ;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Opacity) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (opacity < 0.0f) {
        opacity = 0.0f;
    } ਨਹੀਂਤਾਂ ਜੇ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    ਨਤੀਜਾ = _this->ਸੈੱਟ_ਖਿੜਕੀ_Opacity(_this, ਖਿੜਕੀ, opacity);
    ਜੇ (ਨਤੀਜਾ) {
        ਖਿੜਕੀ->opacity = opacity;
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਦਸ਼ਮਲਵ SDL_Get_ਖਿੜਕੀ_Opacity(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, -1.0f);

    ਵਾਪਸ ਖਿੜਕੀ->opacity;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (ਮਾਪਾ) {
        CHECK_ਖਿੜਕੀ_MAGIC(ਮਾਪਾ, false);
        CHECK_ਖਿੜਕੀ_NOT_POPUP(ਮਾਪਾ, false);
    }

    ਜੇ (ਖਿੜਕੀ == ਮਾਪਾ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Cannot set the parent of a window to itself.");
    }

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MODAL) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ਜੇ (ਖਿੜਕੀ->ਮਾਪਾ == ਮਾਪਾ) {
        ਵਾਪਸ true;
    }

    ਅਚਲ bool ret = _this->ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(_this, ਖਿੜਕੀ, ਮਾਪਾ);
    SDL_Update_ਖਿੜਕੀ_Hierarchy(ਖਿੜਕੀ, ret ? ਮਾਪਾ : ਨਿਰਾ);

    ਵਾਪਸ ret;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Modal) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (modal) {
        ਜੇ (!ਖਿੜਕੀ->ਮਾਪਾ) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_MODAL;
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MODAL) {
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MODAL;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ true; // Already not modal, so nothing to do.
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਵਾਪਸ true;
    }

    ਵਾਪਸ _this->ਸੈੱਟ_ਖਿੜਕੀ_Modal(_this, ਖਿੜਕੀ, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ **new_focus)
{
    SDL_ਖਿੜਕੀ *focus = ਖਿੜਕੀ->ਮਾਪਾ;
    bool ਸੈੱਟ_focus = !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ਜਦੋਂ (SDL_ਖਿੜਕੀ_IS_POPUP(focus) && ((focus->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->ਮਾਪਾ;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ਜੇ (!ਸੈੱਟ_focus) {
            ਸੈੱਟ_focus = !!(focus->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS);
        }
    }

    *new_focus = focus;
    ਵਾਪਸ ਸੈੱਟ_focus;
}

bool SDL_ShouldFocusPopup(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ *toplevel_ਮਾਪਾ;
    ਲਈ (toplevel_ਮਾਪਾ = ਖਿੜਕੀ->ਮਾਪਾ; SDL_ਖਿੜਕੀ_IS_POPUP(toplevel_ਮਾਪਾ); toplevel_ਮਾਪਾ = toplevel_ਮਾਪਾ->ਮਾਪਾ) {
    }

    SDL_ਖਿੜਕੀ *current_focus = toplevel_ਮਾਪਾ->keyboard_focus;
    bool ਮਿਲਿਆ_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_ਖਿੜਕੀ *w;
    ਲਈ (w = current_focus; w != toplevel_ਮਾਪਾ; w = w->ਮਾਪਾ) {
        ਜੇ (w == ਖਿੜਕੀ) {
            ਮਿਲਿਆ_higher_focus = true;
            ਰੋਕੋ;
        }
    }

    ਵਾਪਸ !ਮਿਲਿਆ_higher_focus || w == toplevel_ਮਾਪਾ;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਅਚਲ bool want = (focusable != false); // normalize the flag.
    ਅਚਲ bool have = !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE);
    ਜੇ ((want != have) && (_this->ਸੈੱਟ_ਖਿੜਕੀ_Focusable)) {
        ਜੇ (want) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_NOT_FOCUSABLE;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_NOT_FOCUSABLE;
        }
        ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Focusable(_this, ਖਿੜਕੀ, want)) {
            ਵਾਪਸ false;
        }
    }

    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool fill)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਅਚਲ bool want = (fill != false); // normalize the flag.
    ਅਚਲ bool have = ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FILL_DOCUMENT) != 0);
    ਜੇ ((want != have) && (_this->ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document)) {
        ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Fill_Document(_this, ਖਿੜਕੀ, want)) {
            ਵਾਪਸ false;
        } ਨਹੀਂਤਾਂ ਜੇ (want) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_FILL_DOCUMENT;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_FILL_DOCUMENT;
        }
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_Update_ਖਿੜਕੀ_Grab(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    bool keyboard_grabbed, mouse_grabbed;

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS) {
        ਜੇ (SDL_GetMouse()->relative_ਬਹੁਲਕ || (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ਨਹੀਂਤਾਂ {
            mouse_grabbed = false;
        }

        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ਨਹੀਂਤਾਂ {
            keyboard_grabbed = false;
        }
    } ਨਹੀਂਤਾਂ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ਜੇ (mouse_grabbed || keyboard_grabbed) {
        ਜੇ (_this->grabbed_ਖਿੜਕੀ && (_this->grabbed_ਖਿੜਕੀ != ਖਿੜਕੀ)) {
            // stealing a grab from another window!
            _this->grabbed_ਖਿੜਕੀ->flags &= ~(SDL_ਖਿੜਕੀ_MOUSE_GRABBED | SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED);
            ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab) {
                _this->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(_this, _this->grabbed_ਖਿੜਕੀ, false);
            }
            ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab) {
                _this->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(_this, _this->grabbed_ਖਿੜਕੀ, false);
            }
        }
        _this->grabbed_ਖਿੜਕੀ = ਖਿੜਕੀ;
    } ਨਹੀਂਤਾਂ ਜੇ (_this->grabbed_ਖਿੜਕੀ == ਖਿੜਕੀ) {
        _this->grabbed_ਖਿੜਕੀ = ਨਿਰਾ; // ungrabbing input.
    }

    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab) {
        ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(_this, ਖਿੜਕੀ, mouse_grabbed)) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MOUSE_GRABBED;
        }
    }
    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab) {
        ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(_this, ਖਿੜਕੀ, keyboard_grabbed)) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED;
        }
    }

    ਜੇ (_this->grabbed_ਖਿੜਕੀ && !(_this->grabbed_ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MOUSE_GRABBED | SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED))) {
        _this->grabbed_ਖਿੜਕੀ = ਨਿਰਾ;
    }
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਜੇ (grabbed) {
            ਖਿੜਕੀ->pending_flags |= SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->pending_flags &= ~SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (!!grabbed == !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED)) {
        ਵਾਪਸ true;
    }
    ਜੇ (grabbed) {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED;
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED;
    }
    SDL_Update_ਖਿੜਕੀ_Grab(ਖਿੜਕੀ);

    ਜੇ (grabbed && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED)) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਜੇ (grabbed) {
            ਖਿੜਕੀ->pending_flags |= SDL_ਖਿੜਕੀ_MOUSE_GRABBED;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->pending_flags &= ~SDL_ਖਿੜਕੀ_MOUSE_GRABBED;
        }
        ਵਾਪਸ true;
    }

    ਜੇ (!!grabbed == !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED)) {
        ਵਾਪਸ true;
    }
    ਜੇ (grabbed) {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_MOUSE_GRABBED;
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MOUSE_GRABBED;
    }
    SDL_Update_ਖਿੜਕੀ_Grab(ਖਿੜਕੀ);

    ਜੇ (grabbed && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED)) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool SDL_Get_ਖਿੜਕੀ_Keyboard_Grab(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    ਵਾਪਸ ਖਿੜਕੀ == _this->grabbed_ਖਿੜਕੀ && (_this->grabbed_ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED);
}

bool SDL_Get_ਖਿੜਕੀ_Mouse_Grab(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    ਵਾਪਸ ਖਿੜਕੀ == _this->grabbed_ਖਿੜਕੀ && (_this->grabbed_ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_GRABBED);
}

SDL_ਖਿੜਕੀ *SDL_Get_Grabbed_ਖਿੜਕੀ(ਖਾਲੀ)
{
    ਜੇ (_this && _this->grabbed_ਖਿੜਕੀ &&
        (_this->grabbed_ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MOUSE_GRABBED | SDL_ਖਿੜਕੀ_KEYBOARD_GRABBED)) != 0) {
        ਵਾਪਸ _this->grabbed_ਖਿੜਕੀ;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ ਨਿਰਾ;
    }
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rect)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect) {
        ਵਾਪਸ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ਜੇ (!rect) {
        rect = &zero;
    }

    ਜੇ (SDL_memcmp(&ਖਿੜਕੀ->mouse_rect, rect, ਆਕਾਰ(*rect)) == 0) {
        ਵਾਪਸ true;
    }
    SDL_memcpy(&ਖਿੜਕੀ->mouse_rect, rect, ਆਕਾਰ(*rect));

    ਵਾਪਸ _this->ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(_this, ਖਿੜਕੀ);
}

ਅਚਲ SDL_Rect *SDL_Get_ਖਿੜਕੀ_Mouse_Rect(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਿਰਾ);

    ਜੇ (SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਖਿੜਕੀ->mouse_rect)) {
        ਵਾਪਸ ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ &ਖਿੜਕੀ->mouse_rect;
    }
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Relative_Mouse_ਬਹੁਲਕ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    ਜੇ (enabled == SDL_Get_ਖਿੜਕੀ_Relative_Mouse_ਬਹੁਲਕ(ਖਿੜਕੀ)) {
        ਵਾਪਸ true;
    }

    ਜੇ (enabled) {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ;
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ;
    }

    ਜੇ (!SDL_Update_Relative_Mouse_ਬਹੁਲਕ()) {
        ਜੇ (enabled) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ;
        }
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool SDL_Get_ਖਿੜਕੀ_Relative_Mouse_ਬਹੁਲਕ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_RELATIVE_ਬਹੁਲਕ) {
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ false;
    }
}

bool SDL_Flash_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (_this->Flash_ਖਿੜਕੀ) {
        ਵਾਪਸ _this->Flash_ਖਿੜਕੀ(_this, ਖਿੜਕੀ, operation);
    }

    ਵਾਪਸ SDL_Unsupported();
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਤਰੱਕੀ_State(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਤਰੱਕੀ_State state)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    CHECK_PARAM(state < SDL_ਤਰੱਕੀ_STATE_NONE || state > SDL_ਤਰੱਕੀ_STATE_ERROR) {
        ਵਾਪਸ SDL_InvalidParamError("state");
    }

    ਖਿੜਕੀ->ਤਰੱਕੀ_state = state;

    ਜੇ (_this->Apply_ਖਿੜਕੀ_ਤਰੱਕੀ) {
        ਜੇ (!_this->Apply_ਖਿੜਕੀ_ਤਰੱਕੀ(_this, ਖਿੜਕੀ)) {
            ਵਾਪਸ false;
        }
    }

    ਵਾਪਸ true;
}

SDL_ਤਰੱਕੀ_State SDL_Get_ਖਿੜਕੀ_ਤਰੱਕੀ_State(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, SDL_ਤਰੱਕੀ_STATE_INVALID);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, SDL_ਤਰੱਕੀ_STATE_INVALID);

    ਵਾਪਸ ਖਿੜਕੀ->ਤਰੱਕੀ_state;
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਤਰੱਕੀ_ਮੁੱਲ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ ਮੁੱਲ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਮੁੱਲ = SDL_clamp(ਮੁੱਲ, 0.0f, 1.f);

    ਖਿੜਕੀ->ਤਰੱਕੀ_ਮੁੱਲ = ਮੁੱਲ;

    ਜੇ (_this->Apply_ਖਿੜਕੀ_ਤਰੱਕੀ) {
        ਜੇ (!_this->Apply_ਖਿੜਕੀ_ਤਰੱਕੀ(_this, ਖਿੜਕੀ)) {
            ਵਾਪਸ false;
        }
    }

    ਵਾਪਸ true;
}

ਦਸ਼ਮਲਵ SDL_Get_ਖਿੜਕੀ_ਤਰੱਕੀ_ਮੁੱਲ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, -1.0f);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, -1.0f);

    ਵਾਪਸ ਖਿੜਕੀ->ਤਰੱਕੀ_ਮੁੱਲ;
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Shown(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Set window state if we have pending window flags cached
    Apply_ਖਿੜਕੀ_Flags(ਖਿੜਕੀ, ਖਿੜਕੀ->pending_flags);
    ਖਿੜਕੀ->pending_flags = 0;
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Hidden(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    ਖਿੜਕੀ->pending_flags |= (ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_LEAVE, false);
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Display_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    ਜੇ (ਖਿੜਕੀ->update_fullscreen_on_display_ਬਦਲਿਆ && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
        ਅਚਲ bool auto_ਬਹੁਲਕ_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_ਮੇਲ_EXCLUSIVE_ਬਹੁਲਕ_ON_MOVE, true);

        ਜੇ (auto_ਬਹੁਲਕ_switch && (ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.w != 0 || ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_ਖਿੜਕੀ_Position(ਖਿੜਕੀ);
            bool include_ਉੱਚਾ_density_modes = false;

            ਜੇ (ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.pixel_density > 1.0f) {
                include_ਉੱਚਾ_density_modes = true;
            }
            ਅਚਲ bool ਮਿਲਿਆ_ਮੇਲ = SDL_Get_Closest_Fullscreen_Display_ਬਹੁਲਕ(displayID, ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.w, ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.h,
                                                                         ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.refresh_ਦਰ, include_ਉੱਚਾ_density_modes, &ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ਜੇ (!ਮਿਲਿਆ_ਮੇਲ ||
                ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.w != ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w ||
                ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ.h != ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.h) {
                SDL_zero(ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ);
            }
        } ਨਹੀਂਤਾਂ {
            SDL_zero(ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ);
        }

        ਜੇ (SDL_ਖਿੜਕੀ_FULLSCREEN_VISIBLE(ਖਿੜਕੀ)) {
            SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_ਖਿੜਕੀ_Pixel_ਮਾਪ_ਬਦਲਿਆ(ਖਿੜਕੀ);
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Moved(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Check_ਖਿੜਕੀ_Display_ਬਦਲਿਆ(ਖਿੜਕੀ);
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Resized(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Check_ਖਿੜਕੀ_Display_ਬਦਲਿਆ(ਖਿੜਕੀ);
    SDL_Check_ਖਿੜਕੀ_Pixel_ਮਾਪ_ਬਦਲਿਆ(ਖਿੜਕੀ);
    SDL_Check_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_ਬਦਲਿਆ(ਖਿੜਕੀ);

    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) && _this->Update_ਖਿੜਕੀ_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_ਸੂਚਕ_Property(ਖਿੜਕੀ->props, SDL_PROP_ਖਿੜਕੀ_SHAPE_ਸੂਚਕ, ਨਿਰਾ);
        ਜੇ (surface) {
            _this->Update_ਖਿੜਕੀ_Shape(_this, ਖਿੜਕੀ, surface);
        }
    }
}

ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_Pixel_ਮਾਪ_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਪੂਰਨ pixel_w = 0, pixel_h = 0;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &pixel_w, &pixel_h);
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_PIXEL_ਮਾਪ_ਬਦਲਿਆ, pixel_w, pixel_h);

    SDL_Check_ਖਿੜਕੀ_Display_Scale_ਬਦਲਿਆ(ਖਿੜਕੀ);
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Pixel_ਮਾਪ_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਖਿੜਕੀ->surface_valid = false;
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_ਜੀਵਤ_Resize_Update(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ਨਹੀਂਤਾਂ {
        // Send an expose event so the application can redraw
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ਸਥਿਰ ਖਾਲੀ SDL_Check_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Rect rect;

    rect.x = ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਖੱਬਾ;
    rect.y = ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਸਿਖਰ;
    rect.w = ਖਿੜਕੀ->w - (ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਸੱਜਾ + ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਖੱਬਾ);
    rect.h = ਖਿੜਕੀ->h - (ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਸਿਖਰ + ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_bottom);
    ਜੇ (SDL_memcmp(&rect, &ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_rect, ਆਕਾਰ(rect)) != 0) {
        SDL_copyp(&ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_rect, &rect);
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_AREA_ਬਦਲਿਆ, 0, 0);
    }
}

ਖਾਲੀ SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_Insets(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ ਖੱਬਾ, ਪੂਰਨ ਸੱਜਾ, ਪੂਰਨ ਸਿਖਰ, ਪੂਰਨ bottom)
{
    ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਖੱਬਾ = ਖੱਬਾ;
    ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਸੱਜਾ = ਸੱਜਾ;
    ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_ਸਿਖਰ = ਸਿਖਰ;
    ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_inset_bottom = bottom;
    SDL_Check_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area_ਬਦਲਿਆ(ਖਿੜਕੀ);
}

bool SDL_Get_ਖਿੜਕੀ_ਸੁਰੱਖਿਅਤ_Area(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Rect *rect)
{
    ਜੇ (rect) {
        SDL_zerop(rect);
    }

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (rect) {
        ਜੇ (SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_rect)) {
            rect->w = ਖਿੜਕੀ->w;
            rect->h = ਖਿੜਕੀ->h;
        } ਨਹੀਂਤਾਂ {
            SDL_copyp(rect, &ਖਿੜਕੀ->ਸੁਰੱਖਿਅਤ_rect);
        }
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Minimized(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Maximized(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Restored(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) {
        SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Enter(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (_this->On_ਖਿੜਕੀ_Enter) {
        _this->On_ਖਿੜਕੀ_Enter(_this, ਖਿੜਕੀ);
    }
    SDL_Update_Relative_Mouse_ਬਹੁਲਕ();
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Leave(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Update_Relative_Mouse_ਬਹੁਲਕ();
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Focus_Gained(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ਜੇ (mouse && mouse->relative_ਬਹੁਲਕ) {
        SDL_ਸੈੱਟ_Mouse_Focus(ਖਿੜਕੀ);
    }

    SDL_Update_ਖਿੜਕੀ_Grab(ਖਿੜਕੀ);
}

ਸਥਿਰ bool SDL_ShouldMinimizeOnFocusLoss(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਅਚਲ ਅੱਖਰ *hint;

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) || ਖਿੜਕੀ->is_destroying) {
        ਵਾਪਸ false;
    }

#ਜੇ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ਜੇ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ਜੇ (Cocoa_IsShowingModalDialog(ਖਿੜਕੀ)) {
            ਵਾਪਸ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ਨਹੀਂਤਾਂ ਜੇ (Cocoa_Is_ਖਿੜਕੀ_ਵਿੱਚ_Fullscreen_Space(ਖਿੜਕੀ)) {
            ਵਾਪਸ false;
        }
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_PLATFORM_ANDROID
    {
        ਬਾਹਰੀ bool Android_JNI_ShouldMinimizeOnFocusLoss(ਖਾਲੀ);
        ਜੇ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ਵਾਪਸ false;
        }
    }
#ਜੇ_ਅੰਤ

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ਜੇ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ਜੇ (ਖਿੜਕੀ->fullscreen_exclusive && !SDL_ਬਹੁਲਕ_Switching_Emulated(_this)) {
            ਵਾਪਸ true;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ false;
        }
    }
    ਵਾਪਸ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

ਖਾਲੀ SDL_On_ਖਿੜਕੀ_Focus_ਗੁਆਚਾ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Update_ਖਿੜਕੀ_Grab(ਖਿੜਕੀ);

    ਜੇ (SDL_ShouldMinimizeOnFocusLoss(ਖਿੜਕੀ)) {
        SDL_Minimize_ਖਿੜਕੀ(ਖਿੜਕੀ);
    }
}

SDL_ਖਿੜਕੀ *SDL_GetToplevelForKeyboardFocus(ਖਾਲੀ)
{
    SDL_ਖਿੜਕੀ *focus = SDL_GetKeyboardFocus();

    ਜੇ (focus) {
        // Get the toplevel parent window.
        ਜਦੋਂ (focus->ਮਾਪਾ) {
            focus = focus->ਮਾਪਾ;
        }
    }

    ਵਾਪਸ focus;
}

bool SDL_ਜੋੜੋ_ਖਿੜਕੀ_Renderer(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(ਖਿੜਕੀ->renderers, (ਖਿੜਕੀ->ਅੰਕ_renderers + 1) * ਆਕਾਰ(*renderers));
    ਜੇ (!renderers) {
        ਵਾਪਸ false;
    }

    ਖਿੜਕੀ->renderers = renderers;
    ਖਿੜਕੀ->renderers[ਖਿੜਕੀ->ਅੰਕ_renderers++] = renderer;

    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_RENDERER_ਸੂਚਕ, renderer);
    ਵਾਪਸ true;
}

ਖਾਲੀ SDL_Remove_ਖਿੜਕੀ_Renderer(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Renderer *renderer)
{
    ਲਈ (ਪੂਰਨ i = 0; i < ਖਿੜਕੀ->ਅੰਕ_renderers; ++i) {
        ਜੇ (ਖਿੜਕੀ->renderers[i] == renderer) {
            ਜੇ (i < (ਖਿੜਕੀ->ਅੰਕ_renderers - 1)) {
                SDL_memmove(&ਖਿੜਕੀ->renderers[i], &ਖਿੜਕੀ->renderers[i + 1], (ਖਿੜਕੀ->ਅੰਕ_renderers - i - 1) * ਆਕਾਰ(ਖਿੜਕੀ->renderers[i]));
            }
            --ਖਿੜਕੀ->ਅੰਕ_renderers;
            ਰੋਕੋ;
        }
    }

    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    ਜੇ (SDL_Get_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_RENDERER_ਸੂਚਕ, ਨਿਰਾ) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_ਖਿੜਕੀ_RENDERER_ਸੂਚਕ);
    }
}

ਖਾਲੀ SDL_Destroy_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ,);

    ਖਿੜਕੀ->is_destroying = true;

    // Destroy any child windows of this window
    ਜਦੋਂ (ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ) {
        SDL_Destroy_ਖਿੜਕੀ(ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ);
    }

    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_DESTROYED, 0, 0);

    SDL_Destroy_ਖਿੜਕੀ_Surface(ਖਿੜਕੀ);

    SDL_Renderer *renderer = SDL_GetRenderer(ਖਿੜਕੀ);
    ਜੇ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_LEAVE, true);
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
        SDL_Hide_ਖਿੜਕੀ(ਖਿੜਕੀ);
    }

    SDL_DestroyProperties(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props);

    SDL_Destroy_ਖਿੜਕੀ_Texture(_this, ਖਿੜਕੀ);
    SDL_DestroyProperties(ਖਿੜਕੀ->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ਜੇ (_this->ਸੈੱਟ_ਖਿੜਕੀ_Modal && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MODAL)) {
        _this->ਸੈੱਟ_ਖਿੜਕੀ_Modal(_this, ਖਿੜਕੀ, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
        ਜੇ (_this->displays[i]->fullscreen_ਖਿੜਕੀ == ਖਿੜਕੀ) {
            _this->displays[i]->fullscreen_ਖਿੜਕੀ = ਨਿਰਾ;
        }
    }

    // Make sure this window no longer has focus
    ਜੇ (SDL_GetKeyboardFocus() == ਖਿੜਕੀ) {
        SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
    }
    ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ਜੇ (SDL_GetMouseFocus() == ਖਿੜਕੀ) {
        SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
    }

    // Make no context current if this is the current context window
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        ਜੇ (_this->current_glwin == ਖਿੜਕੀ) {
            SDL_GL_MakeCurrent(ਖਿੜਕੀ, ਨਿਰਾ);
        }
    }

    ਜੇ (_this->Destroy_ਖਿੜਕੀ) {
        _this->Destroy_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ਜੇ (_this->grabbed_ਖਿੜਕੀ == ਖਿੜਕੀ) {
        _this->grabbed_ਖਿੜਕੀ = ਨਿਰਾ; // ungrabbing input.
    }

    ਜੇ (_this->current_glwin == ਖਿੜਕੀ) {
        _this->current_glwin = ਨਿਰਾ;
    }

    SDL_Compare_And_ਅਦਲਾ_ਬਦਲੀ_Atomic_ਸੂਚਕ(&_this->wakeup_ਖਿੜਕੀ, ਖਿੜਕੀ, ਨਿਰਾ);

    // Now invalidate magic
    SDL_ਸੈੱਟ_Object_Valid(ਖਿੜਕੀ, SDL_OBJECT_TYPE_ਖਿੜਕੀ, false);

    // Free memory associated with the window
    SDL_free(ਖਿੜਕੀ->title);
    SDL_DestroySurface(ਖਿੜਕੀ->icon);

    // Unlink the window from its siblings.
    SDL_Update_ਖਿੜਕੀ_Hierarchy(ਖਿੜਕੀ, ਨਿਰਾ);

    // Unlink the window from the global window list
    ਜੇ (ਖਿੜਕੀ->ਅਗਲਾ) {
        ਖਿੜਕੀ->ਅਗਲਾ->prev = ਖਿੜਕੀ->prev;
    }
    ਜੇ (ਖਿੜਕੀ->prev) {
        ਖਿੜਕੀ->prev->ਅਗਲਾ = ਖਿੜਕੀ->ਅਗਲਾ;
    } ਨਹੀਂਤਾਂ {
        _this->windows = ਖਿੜਕੀ->ਅਗਲਾ;
    }

    SDL_free(ਖਿੜਕੀ->renderers);
    SDL_free(ਖਿੜਕੀ);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#ਜੇ_ਅੰਤ
}

bool SDL_ScreenSaverEnabled(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }
    ਜੇ (!_this->suspend_screensaver) {
        ਵਾਪਸ true;
    }
    _this->suspend_screensaver = false;
    ਜੇ (_this->SuspendScreenSaver) {
        ਵਾਪਸ _this->SuspendScreenSaver(_this);
    }

    ਵਾਪਸ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }
    ਜੇ (_this->suspend_screensaver) {
        ਵਾਪਸ true;
    }
    _this->suspend_screensaver = true;
    ਜੇ (_this->SuspendScreenSaver) {
        ਵਾਪਸ _this->SuspendScreenSaver(_this);
    }

    ਵਾਪਸ SDL_Unsupported();
}

ਖਾਲੀ SDL_QuitVideo(ਖਾਲੀ)
{
    ਪੂਰਨ i;

    ਜੇ (!_this) {
        ਵਾਪਸ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ਜੇ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#ਜੇ_ਅੰਤ
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ਜਦੋਂ (_this->windows) {
        SDL_Destroy_ਖਿੜਕੀ(_this->windows);
    }

    ਜੇ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ਜੇ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    ਲਈ (i = _this->ਅੰਕ_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->ਅੰਕ_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ਨਿਰਾ;

    SDL_Cancel_Clipboard_ਅੰਕੜੇ(0);

    ਜੇ (_this->primary_selection_ਪਾਠ) {
        SDL_free(_this->primary_selection_ਪਾਠ);
        _this->primary_selection_ਪਾਠ = ਨਿਰਾ;
    }
    _this->ਮੁਕਤ(_this);
    _this = ਨਿਰਾ;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_ਲੱਦੋ_Library(ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    bool ਨਤੀਜਾ;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }
    ਜੇ (_this->gl_config.driver_loaded) {
        ਜੇ (ਰਸਤਾ && SDL_strcmp(ਰਸਤਾ, _this->gl_config.driver_ਰਸਤਾ) != 0) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenGL library already loaded");
        }
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!_this->GL_ਲੱਦੋ_Library) {
            ਵਾਪਸ SDL_DllNotSupported("OpenGL");
        }
        ਨਤੀਜਾ = _this->GL_ਲੱਦੋ_Library(_this, ਰਸਤਾ);
    }
    ਜੇ (ਨਤੀਜਾ) {
        ++_this->gl_config.driver_loaded;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

SDL_Function_ਸੂਚਕ SDL_GL_Get_Proc_ਪਤਾ(ਅਚਲ ਅੱਖਰ *proc)
{
    SDL_Function_ਸੂਚਕ func;

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    func = ਨਿਰਾ;
    ਜੇ (_this->GL_Get_Proc_ਪਤਾ) {
        ਜੇ (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_ਪਤਾ(_this, proc);
        } ਨਹੀਂਤਾਂ {
            SDL_ਸੈੱਟ_Error("No GL driver has been loaded");
        }
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ਵਾਪਸ func;
}

SDL_Function_ਸੂਚਕ SDL_EGL_Get_Proc_ਪਤਾ(ਅਚਲ ਅੱਖਰ *proc)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    SDL_Function_ਸੂਚਕ func;

    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    func = ਨਿਰਾ;

    ਜੇ (_this->egl_ਅੰਕੜੇ) {
        func = SDL_EGL_Get_Proc_ਪਤਾ_ਅੰਦਰੂਨੀ(_this, proc);
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("No EGL library has been loaded");
    }

    ਵਾਪਸ func;
#ਨਹੀਂਤਾਂ
    SDL_ਸੈੱਟ_Error("SDL was not built with EGL support");
    ਵਾਪਸ ਨਿਰਾ;
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ SDL_GL_UnloadLibrary(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ;
    }
    ਜੇ (_this->gl_config.driver_loaded > 0) {
        ਜੇ (--_this->gl_config.driver_loaded > 0) {
            ਵਾਪਸ;
        }
        ਜੇ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ਜੇ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
ਕਿਸਮਪਰਿਭਾਸ਼ਾ GLenum (APIENTRY* PFNGLGETERRORPROC) (ਖਾਲੀ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅਚਲ GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint ਸੂਚਕਾਂਕ);
#ਜੇ_ਅੰਤ

ਸਥਿਰ SDL_INLINE bool is_At_ਘੱਟ_ਤੋਂ_ਘੱਟ_GL3(ਅਚਲ ਅੱਖਰ *verstr)
{
    ਵਾਪਸ verstr && (SDL_atoi(verstr) >= 3);
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ਅਚਲ ਅੱਖਰ *extension)
{
#ਜੇ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ਅਚਲ ਅੱਖਰ *extensions;
    ਅਚਲ ਅੱਖਰ *ਸ਼ੁਰੂ;
    ਅਚਲ ਅੱਖਰ *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ਜੇ (where || *extension == '\0') {
        ਵਾਪਸ false;
    }
    // See if there's a hint or environment variable override
    ਸ਼ੁਰੂ = SDL_GetHint(extension);
    ਜੇ (ਸ਼ੁਰੂ && *ਸ਼ੁਰੂ == '0') {
        ਵਾਪਸ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetString");
    ਜੇ (!glGetStringFunc) {
        ਵਾਪਸ false;
    }

    ਜੇ (is_At_ਘੱਟ_ਤੋਂ_ਘੱਟ_GL3((ਅਚਲ ਅੱਖਰ *)glGetStringFunc(GL_ਸੰਸਕਰਣ))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint ਅੰਕ_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetIntegerv");
        ਜੇ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ਵਾਪਸ false;
        }

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GL_ਅੰਕ_EXTENSIONS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GL_ਅੰਕ_EXTENSIONS 0x821D
#ਜੇ_ਅੰਤ
        glGetIntegervFunc(GL_ਅੰਕ_EXTENSIONS, &ਅੰਕ_exts);
        ਲਈ (i = 0; i < ਅੰਕ_exts; i++) {
            ਅਚਲ ਅੱਖਰ *thisext = (ਅਚਲ ਅੱਖਰ *)glGetStringiFunc(GL_EXTENSIONS, i);
            ਜੇ (SDL_strcmp(thisext, extension) == 0) {
                ਵਾਪਸ true;
            }
        }

        ਵਾਪਸ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ਅਚਲ ਅੱਖਰ *)glGetStringFunc(GL_EXTENSIONS);
    ਜੇ (!extensions) {
        ਵਾਪਸ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    ਸ਼ੁਰੂ = extensions;

    ਲਈ (;;) {
        where = SDL_strstr(ਸ਼ੁਰੂ, extension);
        ਜੇ (!where) {
            ਰੋਕੋ;
        }

        terminator = where + SDL_strlen(extension);
        ਜੇ (where == extensions || *(where - 1) == ' ') {
            ਜੇ (*terminator == ' ' || *terminator == '\0') {
                ਵਾਪਸ true;
            }
        }

        ਸ਼ੁਰੂ = terminator;
    }
    ਵਾਪਸ false;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ false;
#ਜੇ_ਅੰਤ
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
ਖਾਲੀ SDL_GL_DeduceMaxSupportedESProfile(ਪੂਰਨ *major, ਪੂਰਨ *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#ਜੇ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ਜੇ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ਨਹੀਂਤਾਂ {
        *major = 2;
        *minor = 0;
    }
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ SDL_EGL_ਸੈੱਟ_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   ਖਾਲੀ *userdata)
{
    ਜੇ (!_this) {
        ਵਾਪਸ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

ਖਾਲੀ SDL_GL_Reset_ਗੁਣ(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        ਵਾਪਸ;
    }

    _this->egl_platformattrib_callback = ਨਿਰਾ;
    _this->egl_surfaceattrib_callback = ਨਿਰਾ;
    _this->egl_contextattrib_callback = ਨਿਰਾ;
    _this->egl_attrib_callback_userdata = ਨਿਰਾ;

    _this->gl_config.red_ਮਾਪ = 8;
    _this->gl_config.green_ਮਾਪ = 8;
    _this->gl_config.blue_ਮਾਪ = 8;
    _this->gl_config.alpha_ਮਾਪ = 8;
    _this->gl_config.ਬਫਰ_ਮਾਪ = 0;
    _this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ = 16;
    _this->gl_config.stencil_ਮਾਪ = 0;
    _this->gl_config.double_ਬਫਰ = 1;
    _this->gl_config.accum_red_ਮਾਪ = 0;
    _this->gl_config.accum_green_ਮਾਪ = 0;
    _this->gl_config.accum_blue_ਮਾਪ = 0;
    _this->gl_config.accum_alpha_ਮਾਪ = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    _this->gl_config.major_ਸੰਸਕਰਣ = 2;
    _this->gl_config.minor_ਸੰਸਕਰਣ = 1;
    _this->gl_config.profile_ਨਕਾਬ = 0;
#ਜਾਂਜੇ defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_ਸੰਸਕਰਣ = 2;
    _this->gl_config.minor_ਸੰਸਕਰਣ = 0;
    _this->gl_config.profile_ਨਕਾਬ = SDL_GL_CONTEXT_PROFILE_ES;
#ਜਾਂਜੇ defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_ਸੰਸਕਰਣ = 1;
    _this->gl_config.minor_ਸੰਸਕਰਣ = 1;
    _this->gl_config.profile_ਨਕਾਬ = SDL_GL_CONTEXT_PROFILE_ES;
#ਜੇ_ਅੰਤ

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    ਜੇ (_this->GL_ਸੈੱਟ_Default_Profile_Config) {
        _this->GL_ਸੈੱਟ_Default_Profile_Config(_this);
    }
}

bool SDL_GL_ਸੈੱਟ_Attribute(SDL_GLAttr attr, ਪੂਰਨ ਮੁੱਲ)
{
#ਜੇ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool ਨਤੀਜਾ;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }
    ਨਤੀਜਾ = true;
    ਚੋਣ (attr) {
    ਹਾਲਤ SDL_GL_RED_ਮਾਪ:
        _this->gl_config.red_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_GREEN_ਮਾਪ:
        _this->gl_config.green_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_BLUE_ਮਾਪ:
        _this->gl_config.blue_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ALPHA_ਮਾਪ:
        _this->gl_config.alpha_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_ਬਫਰ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ਬਫਰ_ਮਾਪ:
        _this->gl_config.ਬਫਰ_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ਡੂੰਘਾਈ_ਮਾਪ:
        _this->gl_config.ਡੂੰਘਾਈ_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_STENCIL_ਮਾਪ:
        _this->gl_config.stencil_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCUM_RED_ਮਾਪ:
        _this->gl_config.accum_red_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCUM_GREEN_ਮਾਪ:
        _this->gl_config.accum_green_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCUM_BLUE_ਮਾਪ:
        _this->gl_config.accum_blue_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCUM_ALPHA_ਮਾਪ:
        _this->gl_config.accum_alpha_ਮਾਪ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_STEREO:
        _this->gl_config.stereo = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_MAJOR_ਸੰਸਕਰਣ:
        _this->gl_config.major_ਸੰਸਕਰਣ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_MINOR_ਸੰਸਕਰਣ:
        _this->gl_config.minor_ਸੰਸਕਰਣ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_FLAGS:
        ਜੇ (ਮੁੱਲ & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Unknown OpenGL context flag %d", ਮੁੱਲ);
            ਰੋਕੋ;
        }
        _this->gl_config.flags = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_PROFILE_ਨਕਾਬ:
        ਜੇ (ਮੁੱਲ != 0 &&
            ਮੁੱਲ != SDL_GL_CONTEXT_PROFILE_CORE &&
            ਮੁੱਲ != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            ਮੁੱਲ != SDL_GL_CONTEXT_PROFILE_ES) {
            ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Unknown OpenGL context profile %d", ਮੁੱਲ);
            ਰੋਕੋ;
        }
        _this->gl_config.profile_ਨਕਾਬ = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = ਮੁੱਲ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = ਮੁੱਲ;
        ਰੋਕੋ;
    ਮੂਲ:
        ਨਤੀਜਾ = SDL_ਸੈੱਟ_Error("Unknown OpenGL attribute");
        ਰੋਕੋ;
    }
    ਵਾਪਸ ਨਤੀਜਾ;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_Unsupported();
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, ਪੂਰਨ *ਮੁੱਲ)
{
#ਜੇ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_ਪਿੱਠ_ਖੱਬਾ;
    GLenum attachmentattrib = 0;
#ਜੇ_ਅੰਤ

    CHECK_PARAM(!ਮੁੱਲ) {
        ਵਾਪਸ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *ਮੁੱਲ = 0;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    ਚੋਣ (attr) {
    ਹਾਲਤ SDL_GL_RED_ਮਾਪ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_ਮਾਪ;
#ਜੇ_ਅੰਤ
        attrib = GL_RED_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_BLUE_ਮਾਪ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_ਮਾਪ;
#ਜੇ_ਅੰਤ
        attrib = GL_BLUE_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_GREEN_ਮਾਪ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_ਮਾਪ;
#ਜੇ_ਅੰਤ
        attrib = GL_GREEN_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ALPHA_ਮਾਪ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_ਮਾਪ;
#ਜੇ_ਅੰਤ
        attrib = GL_ALPHA_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_DOUBLEBUFFER:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        ਰੋਕੋ;
#ਨਹੀਂਤਾਂ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *ਮੁੱਲ = _this->gl_config.double_ਬਫਰ;
        ਵਾਪਸ true;
#ਜੇ_ਅੰਤ
    ਹਾਲਤ SDL_GL_ਡੂੰਘਾਈ_ਮਾਪ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        attachment = GL_ਡੂੰਘਾਈ;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ਡੂੰਘਾਈ_ਮਾਪ;
#ਜੇ_ਅੰਤ
        attrib = GL_ਡੂੰਘਾਈ_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_STENCIL_ਮਾਪ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_ਮਾਪ;
#ਜੇ_ਅੰਤ
        attrib = GL_STENCIL_ਬਿੱਟ;
        ਰੋਕੋ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    ਹਾਲਤ SDL_GL_ACCUM_RED_ਮਾਪ:
        attrib = GL_ACCUM_RED_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCUM_GREEN_ਮਾਪ:
        attrib = GL_ACCUM_GREEN_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCUM_BLUE_ਮਾਪ:
        attrib = GL_ACCUM_BLUE_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ACCUM_ALPHA_ਮਾਪ:
        attrib = GL_ACCUM_ALPHA_ਬਿੱਟ;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_STEREO:
        attrib = GL_STEREO;
        ਰੋਕੋ;
#ਨਹੀਂਤਾਂ
    ਹਾਲਤ SDL_GL_ACCUM_RED_ਮਾਪ:
    ਹਾਲਤ SDL_GL_ACCUM_GREEN_ਮਾਪ:
    ਹਾਲਤ SDL_GL_ACCUM_BLUE_ਮਾਪ:
    ਹਾਲਤ SDL_GL_ACCUM_ALPHA_ਮਾਪ:
    ਹਾਲਤ SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *ਮੁੱਲ = 0;
        ਵਾਪਸ true;
#ਜੇ_ਅੰਤ
    ਹਾਲਤ SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_GL_ਬਫਰ_ਮਾਪ:
    {
        ਪੂਰਨ rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        ਜੇ (!SDL_GL_GetAttribute(SDL_GL_RED_ਮਾਪ, &rsize)) {
            ਵਾਪਸ false;
        }
        ਜੇ (!SDL_GL_GetAttribute(SDL_GL_GREEN_ਮਾਪ, &gsize)) {
            ਵਾਪਸ false;
        }
        ਜੇ (!SDL_GL_GetAttribute(SDL_GL_BLUE_ਮਾਪ, &bsize)) {
            ਵਾਪਸ false;
        }
        ਜੇ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_ਮਾਪ, &asize)) {
            ਵਾਪਸ false;
        }

        *ਮੁੱਲ = rsize + gsize + bsize + asize;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *ਮੁੱਲ = (_this->gl_config.accelerated != 0);
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_RETAINED_BACKING:
    {
        *ਮੁੱਲ = _this->gl_config.retained_backing;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_CONTEXT_MAJOR_ਸੰਸਕਰਣ:
    {
        *ਮੁੱਲ = _this->gl_config.major_ਸੰਸਕਰਣ;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_CONTEXT_MINOR_ਸੰਸਕਰਣ:
    {
        *ਮੁੱਲ = _this->gl_config.minor_ਸੰਸਕਰਣ;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_CONTEXT_FLAGS:
    {
        *ਮੁੱਲ = _this->gl_config.flags;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_CONTEXT_PROFILE_ਨਕਾਬ:
    {
        *ਮੁੱਲ = _this->gl_config.profile_ਨਕਾਬ;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *ਮੁੱਲ = _this->gl_config.share_with_current_context;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *ਮੁੱਲ = _this->gl_config.framebuffer_srgb_capable;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_CONTEXT_NO_ERROR:
    {
        *ਮੁੱਲ = _this->gl_config.no_error;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_EGL_PLATFORM:
    {
        *ਮੁੱਲ = _this->gl_config.egl_platform;
        ਵਾਪਸ true;
    }
    ਹਾਲਤ SDL_GL_FLOATBUFFERS:
    {
        ਜੇ (_this->gl_config.HAS_GL_ARB_color_ਬਫਰ_float) {
            attrib = GL_RGBA_FLOAT_ਬਹੁਲਕ_ARB;
            ਰੋਕੋ;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ 0;
        }
    }
    ਮੂਲ:
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unknown OpenGL attribute");
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetString");
    ਜੇ (!glGetStringFunc) {
        ਵਾਪਸ false;
    }

    ਜੇ (attachmentattrib && is_At_ਘੱਟ_ਤੋਂ_ਘੱਟ_GL3((ਅਚਲ ਅੱਖਰ *)glGetStringFunc(GL_ਸੰਸਕਰਣ))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_ਪਤਾ("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_ਪਤਾ("glBindFramebuffer");
        ਜੇ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetFramebufferAttachmentParameteriv");
        ਜੇ (glGetFramebufferAttachmentParameterivFunc) {
            ਜੇ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ਜੇ (attachment == GL_ਡੂੰਘਾਈ || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ਜੇ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)ਮੁੱਲ);
            } ਨਹੀਂਤਾਂ {
                *ਮੁੱਲ = 0;
            }
            ਜੇ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetIntegerv");
        ਜੇ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)ਮੁੱਲ);
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetError");
    ਜੇ (!glGetErrorFunc) {
        ਵਾਪਸ false;
    }

    error = glGetErrorFunc();
    ਜੇ (error != GL_NO_ERROR) {
        ਜੇ (error == GL_INVALID_ENUM) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenGL error: GL_INVALID_ENUM");
        } ਨਹੀਂਤਾਂ ਜੇ (error == GL_INVALID_ਮੁੱਲ) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenGL error: GL_INVALID_VALUE");
        }
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ਜੇ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *ਮੁੱਲ = (*ਮੁੱਲ == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ SDL_Unsupported();
#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NOT_AN_OPENGL_ਖਿੜਕੀ "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_GLContext ctx = ਨਿਰਾ;
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਿਰਾ);

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL)) {
        SDL_ਸੈੱਟ_Error(NOT_AN_OPENGL_ਖਿੜਕੀ);
        ਵਾਪਸ ਨਿਰਾ;
    }

#ਜੇ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ਪੂਰਨ srgb_requested = -1;
    ਅਚਲ ਅੱਖਰ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ਜੇ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#ਜੇ_ਅੰਤ

    ctx = _this->GL_CreateContext(_this, ਖਿੜਕੀ);

    // Creating a context is assumed to make it current in the SDL driver.
    ਜੇ (ctx) {
        _this->current_glwin = ਖਿੜਕੀ;
        _this->current_glctx = ctx;
        SDL_ਸੈੱਟ_TLS(&_this->current_glwin_tls, ਖਿੜਕੀ, ਨਿਰਾ);
        SDL_ਸੈੱਟ_TLS(&_this->current_glctx_tls, ctx, ਨਿਰਾ);
    }

#ਜੇ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ਜੇ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_ਪਤਾ(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_ਪਤਾ("glGetString");
        ਜੇ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ਜੇ (_this->gl_config.profile_ਨਕਾਬ & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ਨਹੀਂਤਾਂ {
                supported = is_At_ਘੱਟ_ਤੋਂ_ਘੱਟ_GL3((ਅਚਲ ਅੱਖਰ *)glGetStringFunc(GL_ਸੰਸਕਰਣ)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ਜੇ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ ctx;
}

bool SDL_GL_MakeCurrent(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context)
{
    bool ਨਤੀਜਾ;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }

    ਜੇ (ਖਿੜਕੀ == SDL_GL_Get_Current_ਖਿੜਕੀ() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ਵਾਪਸ true;
    }

    ਜੇ (!context) {
        ਖਿੜਕੀ = ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ) {
        CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL)) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error(NOT_AN_OPENGL_ਖਿੜਕੀ);
        }
    } ਨਹੀਂਤਾਂ ਜੇ (!_this->gl_allow_no_surface) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Use of OpenGL without a window is not supported on this platform");
    }

    ਨਤੀਜਾ = _this->GL_MakeCurrent(_this, ਖਿੜਕੀ, context);
    ਜੇ (ਨਤੀਜਾ) {
        _this->current_glwin = ਖਿੜਕੀ;
        _this->current_glctx = context;
        SDL_ਸੈੱਟ_TLS(&_this->current_glwin_tls, ਖਿੜਕੀ, ਨਿਰਾ);
        SDL_ਸੈੱਟ_TLS(&_this->current_glctx_tls, context, ਨਿਰਾ);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

SDL_ਖਿੜਕੀ *SDL_GL_Get_Current_ਖਿੜਕੀ(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ (SDL_ਖਿੜਕੀ *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(ਖਾਲੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ EGL_NO_DISPLAY;
    }
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        SDL_ਸੈੱਟ_Error("There is no current EGL display");
        ਵਾਪਸ EGL_NO_DISPLAY;
    }
    ਵਾਪਸ _this->egl_ਅੰਕੜੇ->egl_display;
#ਨਹੀਂਤਾਂ
    SDL_ਸੈੱਟ_Error("SDL was not built with EGL support");
    ਵਾਪਸ ਨਿਰਾ;
#ਜੇ_ਅੰਤ
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(ਖਾਲੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        SDL_ਸੈੱਟ_Error("There is no current EGL display");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ _this->egl_ਅੰਕੜੇ->egl_config;
#ਨਹੀਂਤਾਂ
    SDL_ਸੈੱਟ_Error("SDL was not built with EGL support");
    ਵਾਪਸ ਨਿਰਾ;
#ਜੇ_ਅੰਤ
}

SDL_EGLConfig SDL_EGL_Get_ਖਿੜਕੀ_Surface(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (!_this->egl_ਅੰਕੜੇ) {
        SDL_ਸੈੱਟ_Error("There is no current EGL display");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (_this->GL_GetEGLSurface) {
        ਵਾਪਸ _this->GL_GetEGLSurface(_this, ਖਿੜਕੀ);
    }
    ਵਾਪਸ ਨਿਰਾ;
#ਨਹੀਂਤਾਂ
    SDL_ਸੈੱਟ_Error("SDL was not built with EGL support");
    ਵਾਪਸ ਨਿਰਾ;
#ਜੇ_ਅੰਤ
}

bool SDL_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(ਪੂਰਨ interval)
{
    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_GL_GetCurrentContext() == ਨਿਰਾ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No OpenGL context has been made current");
    } ਨਹੀਂਤਾਂ ਜੇ (_this->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval) {
        ਵਾਪਸ _this->GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(_this, interval);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(ਪੂਰਨ *interval)
{
    CHECK_PARAM(!interval) {
       ਵਾਪਸ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("no video driver");
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_GL_GetCurrentContext() == ਨਿਰਾ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("no current context");
    } ਨਹੀਂਤਾਂ ਜੇ (_this->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval) {
        ਵਾਪਸ _this->GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(_this, interval);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("not implemented");
    }
}

bool SDL_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error(NOT_AN_OPENGL_ਖਿੜਕੀ);
    }

    ਜੇ (SDL_GL_Get_Current_ਖਿੜਕੀ() != ਖਿੜਕੀ) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("The specified window has not been made current");
    }

    ਵਾਪਸ _this->GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ਵਾਪਸ SDL_InvalidParamError("context");
    }

    ਜੇ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ਨਿਰਾ, ਨਿਰਾ);
    }

    ਵਾਪਸ _this->GL_DestroyContext(_this, context);
}

#ਜੇ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ਸਥਿਰ ਖਾਲੀ Create_ਨਕਾਬ_From_Color_ਕੁੰਜੀ_Or_Alpha(SDL_Surface *icon, Uint8 *ਨਕਾਬ, ਪੂਰਨ flags)
{
    ਪੂਰਨ x, y;
    Uint32 colorkey;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੈੱਟ_MASKBIT(icon, x, y, ਨਕਾਬ) \
    ਨਕਾਬ[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    ਚੋਣ (SDL_BYTESPERPIXEL(icon->format)) {
    ਹਾਲਤ 1:
        {
            Uint8 *pixels;
            ਲਈ (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                ਲਈ (x = 0; x < icon->w; ++x) {
                    ਜੇ (*pixels++ == colorkey) {
                        ਸੈੱਟ_MASKBIT(icon, x, y, ਨਕਾਬ);
                    }
                }
            }
        }
        ਰੋਕੋ;

    ਹਾਲਤ 2:
        {
            Uint16 *pixels;
            ਲਈ (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                ਲਈ (x = 0; x < icon->w; ++x) {
                    ਜੇ ((flags & 1) && *pixels == colorkey) {
                        ਸੈੱਟ_MASKBIT(icon, x, y, ਨਕਾਬ);
                    } ਨਹੀਂਤਾਂ ਜੇ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        ਸੈੱਟ_MASKBIT(icon, x, y, ਨਕਾਬ);
                    }
                    pixels++;
                }
            }
        }
        ਰੋਕੋ;

    ਹਾਲਤ 4:
        {
            Uint32 *pixels;
            ਲਈ (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                ਲਈ (x = 0; x < icon->w; ++x) {
                    ਜੇ ((flags & 1) && *pixels == colorkey) {
                        ਸੈੱਟ_MASKBIT(icon, x, y, ਨਕਾਬ);
                    } ਨਹੀਂਤਾਂ ਜੇ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        ਸੈੱਟ_MASKBIT(icon, x, y, ਨਕਾਬ);
                    }
                    pixels++;
                }
            }
        }
        ਰੋਕੋ;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
ਖਾਲੀ SDL_WM_ਸੈੱਟ_Icon(SDL_Surface *icon, Uint8 *ਨਕਾਬ)
{
    ਜੇ (icon && _this->ਸੈੱਟ_Icon) {
        // Generate a mask if necessary, and create the icon!
        ਜੇ (ਨਕਾਬ == ਨਿਰਾ) {
            ਪੂਰਨ ਨਕਾਬ_len = icon->h * (icon->w + 7) / 8;
            ਪੂਰਨ flags = 0;
            ਨਕਾਬ = (Uint8 *) SDL_malloc(ਨਕਾਬ_len);
            ਜੇ (ਨਕਾਬ == ਨਿਰਾ) {
                ਵਾਪਸ;
            }
            SDL_memset(ਨਕਾਬ, ~0, ਨਕਾਬ_len);
            ਜੇ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ਜੇ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ਜੇ (flags) {
                Create_ਨਕਾਬ_From_Color_ਕੁੰਜੀ_Or_Alpha(icon, ਨਕਾਬ, flags);
            }
            _this->ਸੈੱਟ_Icon(_this, icon, ਨਕਾਬ);
            SDL_free(ਨਕਾਬ);
        } ਨਹੀਂਤਾਂ {
            _this->ਸੈੱਟ_Icon(_this, icon, ਨਕਾਬ);
        }
    }
}
#ਜੇ_ਅੰਤ

SDL_ਪਾਠ_ਨਿਵੇਸ਼_Type SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(SDL_PropertiesID props)
{
    ਵਾਪਸ (SDL_ਪਾਠ_ਨਿਵੇਸ਼_Type)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_TEXTINPUT_TYPE_ਸੰਖਿਆ, SDL_TEXTINPUT_TYPE_ਪਾਠ);
}

SDL_Capitalization SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Capitalization(SDL_PropertiesID props)
{
    ਜੇ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ਸੰਖਿਆ)) {
        ਵਾਪਸ (SDL_Capitalization)SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ਸੰਖਿਆ, SDL_CAPITALIZE_NONE);
    }

    ਚੋਣ (SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Type(props)) {
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ:
        ਵਾਪਸ SDL_CAPITALIZE_SENTENCES;
    ਹਾਲਤ SDL_TEXTINPUT_TYPE_ਪਾਠ_NAME:
        ਵਾਪਸ SDL_CAPITALIZE_ਸ਼ਬਦ;
    ਮੂਲ:
        ਵਾਪਸ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Autocorrect(SDL_PropertiesID props)
{
    ਵਾਪਸ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Multiline(SDL_PropertiesID props)
{
    ਜੇ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ਵਾਪਸ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ਜੇ (SDL_GetHintBoolean(SDL_HINT_RETURN_ਕੁੰਜੀ_HIDES_IME, false)) {
        ਵਾਪਸ false;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ true;
    }
}

ਸਥਿਰ bool AutoShowingScreenKeyboard(ਖਾਲੀ)
{
    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ਜੇ (!hint) {
        // This hint is currently only used by the X11 video driver
        ਜੇ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ਜੇ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ false;
    }
}

bool SDL_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ SDL_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼_With_Properties(ਖਿੜਕੀ, 0);
}

bool SDL_ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼_With_Properties(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID props)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props) {
        SDL_DestroyProperties(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props);
        ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props = 0;
    }

    ਜੇ (props) {
        ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props = SDL_CreateProperties();
        ਜੇ (!ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props) {
            ਵਾਪਸ false;
        }
        ਜੇ (!SDL_CopyProperties(props, ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_props)) {
            ਵਾਪਸ false;
        }
    }

    ਜੇ (_this->ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Properties) {
        _this->ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Properties(_this, ਖਿੜਕੀ, props);
    }

    ਜੇ (!ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ) {
        // Start the text input system
        ਜੇ (_this->ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼) {
            ਜੇ (!_this->ਸ਼ੁਰੂ_ਪਾਠ_ਨਿਵੇਸ਼(_this, ਖਿੜਕੀ, props)) {
                ਵਾਪਸ false;
            }
        }
        ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ = true;
    }

    // Show the on-screen keyboard, if desired
    ਜੇ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(ਖਿੜਕੀ)) {
        ਜੇ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, ਖਿੜਕੀ, props);
        }
    }
    ਵਾਪਸ true;
}

bool SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਵਾਪਸ ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ;
}

bool SDL_Stop_ਪਾਠ_ਨਿਵੇਸ਼(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ) {
        // Stop the text input system
        ਜੇ (_this->Stop_ਪਾਠ_ਨਿਵੇਸ਼) {
            _this->Stop_ਪਾਠ_ਨਿਵੇਸ਼(_this, ਖਿੜਕੀ);
        }
        ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ = false;
    }

    // Hide the on-screen keyboard, if desired
    ਜੇ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(ਖਿੜਕੀ)) {
        ਜੇ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, ਖਿੜਕੀ);
        }
    }
    ਵਾਪਸ true;
}

bool SDL_ਸੈੱਟ_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rect, ਪੂਰਨ cursor)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (rect) {
        SDL_copyp(&ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect, rect);
        ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor = cursor;
    } ਨਹੀਂਤਾਂ {
        SDL_zero(ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect);
        ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor = 0;
    }

    ਜੇ (_this && _this->Update_ਪਾਠ_ਨਿਵੇਸ਼_Area) {
        ਜੇ (!_this->Update_ਪਾਠ_ਨਿਵੇਸ਼_Area(_this, ਖਿੜਕੀ)) {
            ਵਾਪਸ false;
        }
    }
    ਵਾਪਸ true;
}

bool SDL_Get_ਪਾਠ_ਨਿਵੇਸ਼_Area(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Rect *rect, ਪੂਰਨ *cursor)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (rect) {
        SDL_copyp(rect, &ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_rect);
    }
    ਜੇ (cursor) {
        *cursor = ਖਿੜਕੀ->ਪਾਠ_ਨਿਵੇਸ਼_cursor;
    }
    ਵਾਪਸ true;
}

bool SDL_ClearComposition(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (_this->ClearComposition) {
        ਵਾਪਸ _this->ClearComposition(_this, ਖਿੜਕੀ);
    }
    ਵਾਪਸ true;
}

bool SDL_HasScreenKeyboardSupport(ਖਾਲੀ)
{
    ਜੇ (_this && _this->HasScreenKeyboardSupport) {
        ਵਾਪਸ _this->HasScreenKeyboardSupport(_this);
    }
    ਵਾਪਸ false;
}

bool SDL_ScreenKeyboardShown(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਵਾਪਸ _this->screen_keyboard_shown;
}

ਖਾਲੀ SDL_SendScreenKeyboardShown(ਖਾਲੀ)
{
    ਜੇ (!_this || _this->screen_keyboard_shown) {
        ਵਾਪਸ;
    }

    _this->screen_keyboard_shown = true;

    ਜੇ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ਧੱਕੋ_Event(&event);
    }
}

ਖਾਲੀ SDL_SendScreenKeyboardHidden(ਖਾਲੀ)
{
    ਜੇ (!_this || !_this->screen_keyboard_shown) {
        ਵਾਪਸ;
    }

    _this->screen_keyboard_shown = false;

    ਜੇ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ਧੱਕੋ_Event(&event);
    }
}

ਪੂਰਨ SDL_Get_ਸੁਨੇਹਾ_Box_ਗਿਣਤੀ(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_GetAtomicInt(&SDL_messagebox_ਗਿਣਤੀ);
}

bool SDL_Show_ਸੁਨੇਹਾ_Box(ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ *messageboxdata, ਪੂਰਨ *buttonID)
{
    ਪੂਰਨ dummybutton;
    bool ਨਤੀਜਾ = false;
    bool show_cursor_prev;
    SDL_ਖਿੜਕੀ *current_ਖਿੜਕੀ;
    SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ mbdata;

    CHECK_PARAM(!messageboxdata) {
        ਵਾਪਸ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    ਅੱਖਰ *titlecpy = ਨਿਰਾ;
    ਅੱਖਰ *msgcpy = ਨਿਰਾ;
    ਜੇ (messageboxdata->title) {
        ਅਚਲ size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(ਅੱਖਰ, slen, &titleisstack);
        ਜੇ (!titlecpy) {
            ਵਾਪਸ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ਜੇ (messageboxdata->ਸੁਨੇਹਾ) {
        ਅਚਲ size_t slen = SDL_strlen(messageboxdata->ਸੁਨੇਹਾ) + 1;
        msgcpy = SDL_small_alloc(ਅੱਖਰ, slen, &msgisstack);
        ਜੇ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ਵਾਪਸ false;
        }
        SDL_memcpy(msgcpy, messageboxdata->ਸੁਨੇਹਾ, slen);
    }

    (ਖਾਲੀ)SDL_AtomicIncRef(&SDL_messagebox_ਗਿਣਤੀ);

    current_ਖਿੜਕੀ = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    ਜੇ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, ਆਕਾਰ(*messageboxdata));
    mbdata.title = titlecpy;
    ਜੇ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.ਸੁਨੇਹਾ = msgcpy;
    ਜੇ (!mbdata.ਸੁਨੇਹਾ) {
        mbdata.ਸੁਨੇਹਾ = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ਜੇ (_this && _this->Show_ਸੁਨੇਹਾ_Box) {
        ਨਤੀਜਾ = _this->Show_ਸੁਨੇਹਾ_Box(_this, messageboxdata, buttonID);
    } ਨਹੀਂਤਾਂ {
        // It's completely fine to call this function before video is initialized
        ਅਚਲ ਅੱਖਰ *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ਜੇ (driver_name && *driver_name != 0) {
            ਅਚਲ ਅੱਖਰ *driver_attempt = driver_name;
            ਜਦੋਂ (driver_attempt && (*driver_attempt != 0) && !ਨਤੀਜਾ) {
                ਅਚਲ ਅੱਖਰ *driver_attempt_ਸਿਰਾ = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_ਸਿਰਾ) ? (driver_attempt_ਸਿਰਾ - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                ਲਈ (ਪੂਰਨ i = 0; bootstrap[i]; ++i) {
                    ਜੇ (bootstrap[i]->Show_ਸੁਨੇਹਾ_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ਜੇ (bootstrap[i]->Show_ਸੁਨੇਹਾ_Box(messageboxdata, buttonID)) {
                            ਨਤੀਜਾ = true;
                        }
                        ਰੋਕੋ;
                    }
                }

                driver_attempt = (driver_attempt_ਸਿਰਾ) ? (driver_attempt_ਸਿਰਾ + 1) : ਨਿਰਾ;
            }
        } ਨਹੀਂਤਾਂ {
            ਲਈ (ਪੂਰਨ i = 0; bootstrap[i]; ++i) {
                ਜੇ (bootstrap[i]->Show_ਸੁਨੇਹਾ_Box && bootstrap[i]->Show_ਸੁਨੇਹਾ_Box(messageboxdata, buttonID)) {
                    ਨਤੀਜਾ = true;
                    ਰੋਕੋ;
                }
            }
        }
    }

    ਜੇ (!ਨਤੀਜਾ) {
        ਅਚਲ ਅੱਖਰ *error = SDL_GetError();

        ਜੇ (!*error) {
            SDL_ਸੈੱਟ_Error("No message system available");
        }
    } ਨਹੀਂਤਾਂ {
        SDL_ClearError();
    }

    (ਖਾਲੀ)SDL_AtomicDecRef(&SDL_messagebox_ਗਿਣਤੀ);

    ਜੇ (current_ਖਿੜਕੀ) {
        SDL_Raise_ਖਿੜਕੀ(current_ਖਿੜਕੀ);
    }

    ਜੇ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_ਬਹੁਲਕ();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ਵਾਪਸ ਨਤੀਜਾ;
}

bool SDL_Show_Simple_ਸੁਨੇਹਾ_Box(SDL_ਸੁਨੇਹਾ_Box_Flags flags, ਅਚਲ ਅੱਖਰ *title, ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_ਸੱਜਾ;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_ਸੱਜਾ = gsp_Has_Gpu_ਸੱਜਾ();
    ਜੇ (!has_Gpu_ਸੱਜਾ)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_ਪਾਠ_ਸ਼ਬਦ_WRAP, CFG_LANGUAGE_EN);
    error_ਪਾਠ(&errCnf, ਸੁਨੇਹਾ);
    errorDisp(&errCnf);

    ਜੇ (!has_Gpu_ਸੱਜਾ)
        gfxExit();

    ਵਾਪਸ true;
#ਨਹੀਂਤਾਂ
    SDL_ਸੁਨੇਹਾ_Box_ਅੰਕੜੇ ਅੰਕੜੇ;
    SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ button;

    SDL_zero(ਅੰਕੜੇ);
    ਅੰਕੜੇ.flags = flags;
    ਅੰਕੜੇ.title = title;
    ਅੰਕੜੇ.ਸੁਨੇਹਾ = ਸੁਨੇਹਾ;
    ਅੰਕੜੇ.numbuttons = 1;
    ਅੰਕੜੇ.buttons = &button;
    ਅੰਕੜੇ.ਖਿੜਕੀ = ਖਿੜਕੀ;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.ਪਾਠ = "OK";

    ਵਾਪਸ SDL_Show_ਸੁਨੇਹਾ_Box(&ਅੰਕੜੇ, ਨਿਰਾ);
#ਜੇ_ਅੰਤ
}

bool SDL_ShouldAllowTopmost(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_GetHintBoolean(SDL_HINT_ਖਿੜਕੀ_ALLOW_TOPMOST, true);
}

bool SDL_Show_ਖਿੜਕੀ_System_Menu(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);
    CHECK_ਖਿੜਕੀ_NOT_POPUP(ਖਿੜਕੀ, false);

    ਜੇ (_this->Show_ਖਿੜਕੀ_System_Menu) {
        _this->Show_ਖਿੜਕੀ_System_Menu(ਖਿੜਕੀ, x, y);
        ਵਾਪਸ true;
    }

    ਵਾਪਸ SDL_Unsupported();
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਪ੍ਰਾਪਤੀ_Test callback, ਖਾਲੀ *callback_ਅੰਕੜੇ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!_this->ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test = callback;
    ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test_ਅੰਕੜੇ = callback_ਅੰਕੜੇ;

    ਵਾਪਸ _this->ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(ਖਿੜਕੀ, callback != ਨਿਰਾ);
}

bool SDL_ਸੈੱਟ_ਖਿੜਕੀ_Shape(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    ਜੇ (!props) {
        ਵਾਪਸ false;
    }

    ਜੇ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ਜੇ (!surface) {
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        surface = ਨਿਰਾ;
    }

    ਜੇ (!SDL_ਸੈੱਟ_Surface_Property(props, SDL_PROP_ਖਿੜਕੀ_SHAPE_ਸੂਚਕ, surface)) {
        ਵਾਪਸ false;
    }

    ਜੇ (_this->Update_ਖਿੜਕੀ_Shape) {
        ਜੇ (!_this->Update_ਖਿੜਕੀ_Shape(_this, ਖਿੜਕੀ, surface)) {
            ਵਾਪਸ false;
        }
    }
    ਵਾਪਸ true;
}

/*
 * Functions used by iOS application delegates
 */
ਖਾਲੀ SDL_OnApplicationWillTerminate(ਖਾਲੀ)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

ਖਾਲੀ SDL_On_Application_Did_Receive_ਸਮ੍ਰਿਤੀ_Warning(ਖਾਲੀ)
{
    SDL_SendAppEvent(SDL_EVENT_ਨੀਵਾਂ_ਸਮ੍ਰਿਤੀ);
}

ਖਾਲੀ SDL_OnApplicationWillEnterBackground(ਖਾਲੀ)
{
    ਜੇ (_this) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
        ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
        }
        SDL_ਸੈੱਟ_Keyboard_Focus(ਨਿਰਾ);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

ਖਾਲੀ SDL_OnApplicationDidEnterBackground(ਖਾਲੀ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

ਖਾਲੀ SDL_OnApplicationWillEnterForeground(ਖਾਲੀ)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

ਖਾਲੀ SDL_OnApplicationDidEnterForeground(ਖਾਲੀ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    ਜੇ (_this) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
        ਲਈ (ਖਿੜਕੀ = _this->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
        }
    }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NOT_A_VULKAN_ਖਿੜਕੀ "The specified window isn't a Vulkan window"

bool SDL_Vulkan_ਲੱਦੋ_Library(ਅਚਲ ਅੱਖਰ *ਰਸਤਾ)
{
    bool ਨਤੀਜਾ;

    ਜੇ (!_this) {
        ਵਾਪਸ SDL_UninitializedVideo();
    }
    ਜੇ (_this->vulkan_config.loader_loaded) {
        ਜੇ (ਰਸਤਾ && SDL_strcmp(ਰਸਤਾ, _this->vulkan_config.loader_ਰਸਤਾ) != 0) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Vulkan loader library already loaded");
        }
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!_this->Vulkan_ਲੱਦੋ_Library) {
            ਵਾਪਸ SDL_DllNotSupported("Vulkan");
        }
        ਨਤੀਜਾ = _this->Vulkan_ਲੱਦੋ_Library(_this, ਰਸਤਾ);
    }
    ਜੇ (ਨਤੀਜਾ) {
        _this->vulkan_config.loader_loaded++;
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

SDL_Function_ਸੂਚਕ SDL_Vulkan_GetVkGetInstanceProcAddr(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (!_this->vulkan_config.loader_loaded) {
        SDL_ਸੈੱਟ_Error("No Vulkan loader has been loaded");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ (SDL_Function_ਸੂਚਕ)_this->vulkan_config.vkGetInstanceProcAddr;
}

ਖਾਲੀ SDL_Vulkan_UnloadLibrary(ਖਾਲੀ)
{
    ਜੇ (!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ;
    }
    ਜੇ (_this->vulkan_config.loader_loaded > 0) {
        ਜੇ (--_this->vulkan_config.loader_loaded > 0) {
            ਵਾਪਸ;
        }
        ਜੇ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

ਅੱਖਰ ਅਚਲ * ਅਚਲ *SDL_Vulkan_GetInstanceExtensions(Uint32 *ਗਿਣਤੀ_2)
{
    Uint32 tmpcount = 0;
    ਜੇ (!ਗਿਣਤੀ_2) {
        ਗਿਣਤੀ_2 = &tmpcount;
    }

    ਜੇ (!_this->Vulkan_GetInstanceExtensions) {
        *ਗਿਣਤੀ_2 = 0;
        SDL_Unsupported();
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ _this->Vulkan_GetInstanceExtensions(_this, ਗਿਣਤੀ_2);
}

bool SDL_Vulkan_CreateSurface(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                  VkInstance instance,
                                  ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, false);

    ਜੇ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ਵਾਪਸ false;
    }

    CHECK_PARAM(!instance) {
        ਵਾਪਸ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ਵਾਪਸ SDL_InvalidParamError("surface");
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN)) {
        // No problem, we can convert to Vulkan
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_METAL) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_METAL;
            // Nothing more to do for Metal.
        }
        ਜੇ (SDL_Vulkan_ਲੱਦੋ_Library(ਨਿਰਾ)) {
            ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_VULKAN;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("failed to load Vulkan library");
        }
    }

    ਵਾਪਸ _this->Vulkan_CreateSurface(_this, ਖਿੜਕੀ, instance, allocator, surface);
}

ਖਾਲੀ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ਅਚਲ ਬਣਤਰ Vk_ਵੰਡ_Callbacks *allocator)
{
    ਜੇ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ਵਾਪਸ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ਵਾਪਸ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ਵਾਪਸ false;
    }

    ਜੇ (_this->Vulkan_GetPresentationSupport) {
        ਵਾਪਸ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, ਕਤਾਰ_Family_ਸੂਚਕਾਂਕ);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ਵਾਪਸ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    CHECK_ਖਿੜਕੀ_MAGIC(ਖਿੜਕੀ, ਨਿਰਾ);

    ਜੇ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_METAL)) {
        // No problem, we can convert to Metal
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_VULKAN) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_METAL;
    }

    ਵਾਪਸ _this->Metal_CreateView(_this, ਖਿੜਕੀ);
}

ਖਾਲੀ SDL_Metal_DestroyView(SDL_MetalView view)
{
    ਜੇ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

ਖਾਲੀ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ਜੇ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ਵਾਪਸ ਨਿਰਾ;
        }
        ਵਾਪਸ _this->Metal_GetLayer(_this, view);
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Error("Metal is not supported.");
        ਵਾਪਸ ਨਿਰਾ;
    }
}

#ਜੇ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ਅਚਲ ਅੱਖਰ *SDL_GetCSSCursorName(SDL_SystemCursor id, ਅਚਲ ਅੱਖਰ **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    ਚੋਣ (id) {
    ਹਾਲਤ SDL_SYSTEM_CURSOR_DEFAULT:
        ਵਾਪਸ "default";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪਾਠ:
        ਵਾਪਸ "text";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_WAIT:
        ਵਾਪਸ "wait";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_CROSSHAIR:
        ਵਾਪਸ "crosshair";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਤਰੱਕੀ:
        ਵਾਪਸ "progress";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ਜੇ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ਵਾਪਸ "nwse-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ਜੇ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ਵਾਪਸ "nesw-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_EW_RESIZE:
        ਜੇ (fallback_name) {
            *fallback_name = "col-resize";
        }
        ਵਾਪਸ "ew-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_NS_RESIZE:
        ਜੇ (fallback_name) {
            *fallback_name = "row-resize";
        }
        ਵਾਪਸ "ns-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_MOVE:
        ਜੇ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ਵਾਪਸ "move";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ਵਾਪਸ "not-allowed";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਸੂਚਕ:
        ਵਾਪਸ "pointer";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_NW_RESIZE:
        ਵਾਪਸ "nw-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_N_RESIZE:
        ਵਾਪਸ "n-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_NE_RESIZE:
        ਵਾਪਸ "ne-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_E_RESIZE:
        ਵਾਪਸ "e-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_SE_RESIZE:
        ਵਾਪਸ "se-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_S_RESIZE:
        ਵਾਪਸ "s-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_SW_RESIZE:
        ਵਾਪਸ "sw-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_W_RESIZE:
        ਵਾਪਸ "w-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ਵਾਪਸ "context-menu";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_HELP:
        ਵਾਪਸ "help";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_CELL:
        ਵਾਪਸ "cell";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_VERTICAL_ਪਾਠ:
        ਵਾਪਸ "vertical-text";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALIAS:
        ਵਾਪਸ "alias";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_COPY:
        ਵਾਪਸ "copy";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_NO_DROP:
        ਵਾਪਸ "no-drop";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRAB:
        ਵਾਪਸ "grab";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRABBING:
        ਵਾਪਸ "grabbing";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਖਾਨਾ_RESIZE:
        ਵਾਪਸ "col-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪੰਕਤੀ_RESIZE:
        ਵਾਪਸ "row-resize";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ਜੇ (fallback_name) {
            *fallback_name = "move";
        }
        ਵਾਪਸ "all-scroll";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਵਿੱਚ:
        ਵਾਪਸ "zoom-in";

    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਬਾਹਰਲਾ:
        ਵਾਪਸ "zoom-out";

    ਮੂਲ:
        ਵਾਪਸ "default";
    }
}
#ਜੇ_ਅੰਤ

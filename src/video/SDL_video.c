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

#ifdef SDL_VIDEO_OPENGL
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#ಯದಿ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ಯದಿ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ಅನ್ತರ್ಭಾವ <SDL3/SDL_opengles2.h>
#endif // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#ifndef GL_CONTEXT_RELEASE_BEHAVIOR
#define GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#endif

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#ifndef GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#endif

// This is always the same number between the various EXT/ARB/GLES extensions.
#ifndef GL_FRAMEBUFFER_SRGB
#define GL_FRAMEBUFFER_SRGB 0x8DB9
#endif

#ifdef SDL_PLATFORM_EMSCRIPTEN
#ಅನ್ತರ್ಭಾವ <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#ಅನ್ತರ್ಭಾವ <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ಸ್ಥಿರ VideoBootStrap *bootstrap[] = {
#ifdef SDL_VIDEO_DRIVER_PRIVATE
    &PRIVATE_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_X11
#ifdef SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#endif
    &X11_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#ifdef SDL_ಒಳಹರಿವು_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    ರಿಕ್ತ
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        ಪ್ರತ್ಯಾಗಮ result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ಪ್ರತ್ಯಾಗಮ result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        ಪ್ರತ್ಯಾಗಮ result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ಪ್ರತ್ಯಾಗಮ result;                                                  \
    }

#ಯದಿ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
ಬಾಹ್ಯ bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
ಬಾಹ್ಯ bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_UpdateLifecycleObserver(ಶೂನ್ಯ);
#endif

ಸ್ಥಿರ ಶೂನ್ಯ SDL_CheckWindowDisplayChanged(SDL_Window *window);
ಸ್ಥಿರ ಶೂನ್ಯ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
ಸ್ಥಿರ ಶೂನ್ಯ SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
ಸ್ಥಿರ bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    ಯದಿ (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ಸ್ಥಿರ bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ಸ್ಥಿರ bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ಸ್ಥಿರ bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ಸ್ಥಿರ bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ಸ್ಥಿರ bool syncHint;

ಸ್ಥಿರ ಶೂನ್ಯ SDL_SyncHintWatcher(ಶೂನ್ಯ *userdata, ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *old_ಮೌಲ್ಯ, ಧ್ರುವ ವರ್ಣ *new_ಮೌಲ್ಯ)
{
    syncHint = SDL_GetStringBoolean(new_ಮೌಲ್ಯ, false);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_SyncIfRequired(SDL_Window *window)
{
    ಯದಿ (syncHint) {
        SDL_SyncWindow(window);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    ಯದಿ (window->parent) {
        ಯದಿ (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        ಯದಿ (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } ಅನ್ಯಥಾ {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = ರಿಕ್ತ;
    }

    ಯದಿ (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        ಯದಿ (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    ಶೂನ್ಯ *pixels;
    ಪೂರ್ಣಾಙ್ಕ pitch;
    ಪೂರ್ಣಾಙ್ಕ bytes_per_pixel;
} SDL_WindowTextureData;

ಸ್ಥಿರ Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#ಯದಿ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ಯದಿ (_this->GL_CreateContext) {
        ಪ್ರತ್ಯಾಗಮ SDL_WINDOW_OPENGL;
    }
#endif
#ಯದಿ defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ಯದಿ (_this->Metal_CreateView) {
        ಪ್ರತ್ಯಾಗಮ SDL_WINDOW_METAL;
    }
#endif
#ಯದಿ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ಯದಿ (SDL_strcmp(_this->name, "openvr") == 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_WINDOW_OPENGL;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಙ್ಕ *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ರಿಕ್ತ);
    ಧ್ರುವ bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪೂರ್ಣಾಙ್ಕ w, h;
    ಧ್ರುವ SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    ಯದಿ (!data) {
        SDL_Renderer *renderer = ರಿಕ್ತ;
        ಧ್ರುವ ವರ್ಣ *render_driver = ರಿಕ್ತ;

        // See if there's a render driver being requested
        ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ಯದಿ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ಯದಿ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ಯದಿ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = ರಿಕ್ತ;
        }

        ವರ್ಣ *render_driver_copy = ರಿಕ್ತ;
        ಯದಿ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ಯದಿ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                ವರ್ಣ *prev = render_driver_copy;
                ವರ್ಣ *ptr = prev;
                ಯಾವತ್ ((ptr = SDL_strchr(ptr, ',')) != ರಿಕ್ತ) {
                    *ptr = '\0';
                    ಧ್ರುವ bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ಯದಿ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } ಅನ್ಯಥಾ {
                        ptr++;
                        prev = ptr;
                    }
                }

                ಯದಿ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ಯದಿ (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            ಯದಿ (!renderer) {
                // The error for this specific renderer has already been set
                ಪ್ರತ್ಯಾಗಮ false;
            }
        } ಅನ್ಯಥಾ {
            SDL_assert(render_driver_copy == ರಿಕ್ತ);
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ total = SDL_Get_ಅಂಕೆ_Render_Drivers();
            ಪ್ರತಿ (i = 0; i < total; ++i) {
                ಧ್ರುವ ವರ್ಣ *name = SDL_GetRenderDriver(i);
                ಯದಿ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    ಯದಿ (renderer) {
                        ಭಙ್ಗ; // this will work.
                    }
                }
            }
            ಯದಿ (!renderer) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ರಿಕ್ತ); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, ಪರಿಮಾಣ(*data));
        ಯದಿ (!data) {
            SDL_DestroyRenderer(renderer);
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಯದಿ (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            ಪ್ರತ್ಯಾಗಮ false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ಧ್ರುವ SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, ರಿಕ್ತ);
    ಯದಿ (!texture_formats) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Free any old texture and pixel data
    ಯದಿ (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = ರಿಕ್ತ;
    }
    SDL_free(data->pixels);
    data->pixels = ರಿಕ್ತ;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    ಪ್ರತಿ (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ಯದಿ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            ಭಙ್ಗ;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    ಯದಿ (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ಪ್ರತ್ಯಾಗಮ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ಧ್ರುವ size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ಯದಿ (!data->pixels) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, ರಿಕ್ತ);

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ರಿಕ್ತ);
    ಯದಿ (!data) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (!data->renderer) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_SetRenderVSync(data->renderer, vsync);
}

ಸ್ಥಿರ bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ರಿಕ್ತ);
    ಯದಿ (!data) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (!data->renderer) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_GetRenderVSync(data->renderer, vsync);
}

ಸ್ಥಿರ bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rects, ಪೂರ್ಣಾಙ್ಕ numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    ಶೂನ್ಯ *src;
    ಪೂರ್ಣಾಙ್ಕ w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ರಿಕ್ತ);
    ಯದಿ (!data || !data->texture) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ಯದಿ (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (ಶೂನ್ಯ *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        ಯದಿ (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        ಯದಿ (!SDL_RenderTexture(data->renderer, data->texture, ರಿಕ್ತ, ರಿಕ್ತ)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        SDL_RenderPresent(data->renderer);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ಯದಿ (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ರಿಕ್ತ);

        ಯದಿ (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        ಯದಿ (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

ಸ್ಥಿರ SDL_VideoDevice *_this = ರಿಕ್ತ;
ಸ್ಥಿರ SDL_AtomicInt SDL_messagebox_ಎಣಿಕೆ;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ SDLCALL cmpmodes(ಧ್ರುವ ಶೂನ್ಯ *A, ಧ್ರುವ ಶೂನ್ಯ *B)
{
    ಧ್ರುವ SDL_DisplayMode *a = (ಧ್ರುವ SDL_DisplayMode *)A;
    ಧ್ರುವ SDL_DisplayMode *b = (ಧ್ರುವ SDL_DisplayMode *)B;
    ಪೂರ್ಣಾಙ್ಕ a_refresh_rate = (ಪೂರ್ಣಾಙ್ಕ)(a->refresh_rate * 100);
    ಪೂರ್ಣಾಙ್ಕ b_refresh_rate = (ಪೂರ್ಣಾಙ್ಕ)(b->refresh_rate * 100);
    ಪೂರ್ಣಾಙ್ಕ a_pixel_density = (ಪೂರ್ಣಾಙ್ಕ)(a->pixel_density * 100);
    ಪೂರ್ಣಾಙ್ಕ b_pixel_density = (ಪೂರ್ಣಾಙ್ಕ)(b->pixel_density * 100);

    ಯದಿ (a->w != b->w) {
        ಪ್ರತ್ಯಾಗಮ b->w - a->w;
    } ಅನ್ಯಥಾ ಯದಿ (a->h != b->h) {
        ಪ್ರತ್ಯಾಗಮ b->h - a->h;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ಅನ್ಯಥಾ ಯದಿ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ಪ್ರತ್ಯಾಗಮ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ಅನ್ಯಥಾ ಯದಿ (a_refresh_rate != b_refresh_rate) {
        ಪ್ರತ್ಯಾಗಮ b_refresh_rate - a_refresh_rate;
    } ಅನ್ಯಥಾ ಯದಿ (a_pixel_density != b_pixel_density) {
        ಪ್ರತ್ಯಾಗಮ a_pixel_density - b_pixel_density;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

bool SDL_UninitializedVideo(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ಸ್ಥಿರ ಧ್ರುವ VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

ಪೂರ್ಣಾಙ್ಕ SDL_Get_ಅಂಕೆ_Video_Drivers(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_drivers = -1;

    ಯದಿ (ಅಂಕೆ_drivers >= 0) {
        ಪ್ರತ್ಯಾಗಮ ಅಂಕೆ_drivers;
    }

    ಅಂಕೆ_drivers = 0;

    // Build a list of unique video drivers.
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; bootstrap[i] != ರಿಕ್ತ; ++i) {
        bool duplicate = false;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < i; ++j) {
            ಯದಿ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                ಭಙ್ಗ;
            }
        }

        ಯದಿ (!duplicate) {
            deduped_bootstrap[ಅಂಕೆ_drivers++] = bootstrap[i];
        }
    }

    ಪ್ರತ್ಯಾಗಮ ಅಂಕೆ_drivers;
}

ಧ್ರುವ ವರ್ಣ *SDL_GetVideoDriver(ಪೂರ್ಣಾಙ್ಕ index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_ಅಂಕೆ_Video_Drivers()) {
        SDL_InvalidParamError("index");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ಧ್ರುವ ವರ್ಣ *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    ಪೂರ್ಣಾಙ್ಕ i = 0;

    // Check to make sure we don't overwrite '_this'
    ಯದಿ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ಯದಿ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        ಗಚ್ಛ pre_driver_error;
    }
    init_events = true;
    ಯದಿ (!SDL_InitKeyboard()) {
        ಗಚ್ಛ pre_driver_error;
    }
    init_keyboard = true;
    ಯದಿ (!SDL_PreInitMouse()) {
        ಗಚ್ಛ pre_driver_error;
    }
    init_mouse = true;
    ಯದಿ (!SDL_InitTouch()) {
        ಗಚ್ಛ pre_driver_error;
    }
    init_touch = true;
    ಯದಿ (!SDL_InitPen()) {
        ಗಚ್ಛ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ರಿಕ್ತ;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ಯದಿ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    ಯದಿ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ಯದಿ (driver_name && *driver_name != 0) {
        ಧ್ರುವ ವರ್ಣ *driver_attempt = driver_name;
        ಯಾವತ್ (driver_attempt && *driver_attempt != 0 && !video) {
            ಧ್ರುವ ವರ್ಣ *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            ಪ್ರತಿ (i = 0; bootstrap[i]; ++i) {
                ಯದಿ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ಯದಿ (video) {
                        ಭಙ್ಗ;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ರಿಕ್ತ;
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ಯದಿ (video) {
                ಭಙ್ಗ;
            }
        }
    }
    ಯದಿ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ಅನ್ಯಥಾ {
        ಯದಿ (driver_name) {
            SDL_SetError("%s not available", driver_name);
            ಗಚ್ಛ pre_driver_error;
        }
        SDL_SetError("No available video device");
        ಗಚ್ಛ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ರಿಕ್ತ;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    ಯದಿ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Make sure some displays were added
    ಯದಿ (_this->ಅಂಕೆ_displays == 0) {
        SDL_QuitVideo();
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, ರಿಕ್ತ);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ಯದಿ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ಪ್ರತ್ಯಾಗಮ true;

pre_driver_error:
    SDL_assert(_this == ರಿಕ್ತ);
    ಯದಿ (init_pen) {
        SDL_QuitPen();
    }
    ಯದಿ (init_touch) {
        SDL_QuitTouch();
    }
    ಯದಿ (init_mouse) {
        SDL_QuitMouse();
    }
    ಯದಿ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ಯದಿ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಧ್ರುವ ವರ್ಣ *SDL_GetCurrentVideoDriver(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ _this;
}

bool SDL_OnVideoThread(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

ಶೂನ್ಯ SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    ಯದಿ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(ಶೂನ್ಯ)
{
    ಯದಿ (_this) {
        ಪ್ರತ್ಯಾಗಮ _this->system_theme;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ಶೂನ್ಯ SDL_UpdateDesktopBounds(ಶೂನ್ಯ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ರಿಕ್ತ);
    ಯದಿ (displays) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ಯದಿ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ಯದಿ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ಅನ್ಯಥಾ {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    ಯದಿ (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    ಯದಿ (mode->refresh_rate_numerator > 0) {
        ಯದಿ (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (ಭಿನ್ನ)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } ಅನ್ಯಥಾ {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ಧ್ರುವ SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ಯದಿ (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, ಪರಿಮಾಣ(display.desktop_mode));
    }
    ಪ್ರತ್ಯಾಗಮ SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ಧ್ರುವ SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    ಪೂರ್ಣಾಙ್ಕ i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(ಪರಿಮಾಣ(*new_display));
    ಯದಿ (!new_display) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->ಅಂಕೆ_displays + 1) * ಪರಿಮಾಣ(*displays));
    ಯದಿ (!displays) {
        SDL_free(new_display);
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    _this->displays = displays;
    _this->displays[_this->ಅಂಕೆ_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ಯದಿ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ಅನ್ಯಥಾ {
        ವರ್ಣ name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ಯದಿ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    ಪ್ರತಿ (i = 0; i < new_display->ಅಂಕೆ_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    ಯದಿ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ಪ್ರತ್ಯಾಗಮ id;
}

ಶೂನ್ಯ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

ಶೂನ್ಯ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

ಶೂನ್ಯ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    ಪೂರ್ಣಾಙ್ಕ display_index = SDL_GetDisplayIndex(displayID);
    ಯದಿ (display_index < 0) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    display = _this->displays[display_index];

    ಯದಿ (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = ರಿಕ್ತ;
    SDL_free(display->internal);
    display->internal = ರಿಕ್ತ;
    SDL_free(display);

    ಯದಿ (display_index < (_this->ಅಂಕೆ_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->ಅಂಕೆ_displays - display_index - 1) * ಪರಿಮಾಣ(_this->displays[display_index]));
    }
    --_this->ಅಂಕೆ_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    SDL_DisplayID *displays;

    ಯದಿ (!_this) {
        ಯದಿ (ಎಣಿಕೆ) {
            *ಎಣಿಕೆ = 0;
        }

        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->ಅಂಕೆ_displays + 1) * ಪರಿಮಾಣ(*displays));
    ಯದಿ (displays) {
        ಯದಿ (ಎಣಿಕೆ) {
            *ಎಣಿಕೆ = _this->ಅಂಕೆ_displays;
        }

        ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ಅನ್ಯಥಾ {
        ಯದಿ (ಎಣಿಕೆ) {
            *ಎಣಿಕೆ = 0;
        }
    }
    ಪ್ರತ್ಯಾಗಮ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    ಪೂರ್ಣಾಙ್ಕ display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    ಯದಿ (display_index < 0) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ _this->displays[display_index];
}

ಸ್ಥಿರ SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    ಯದಿ (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    ಪ್ರತ್ಯಾಗಮ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ಪ್ರತ್ಯಾಗಮ SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(ಶೂನ್ಯ)
{
    ಯದಿ (!_this || _this->ಅಂಕೆ_displays == 0) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಪ್ರತ್ಯಾಗಮ _this->displays[0]->id;
}

ಪೂರ್ಣಾಙ್ಕ SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    ಪೂರ್ಣಾಙ್ಕ display_index;

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ -1;
    }

    ಪ್ರತಿ (display_index = 0; display_index < _this->ಅಂಕೆ_displays; ++display_index) {
        ಯದಿ (displayID == _this->displays[display_index]->id) {
            ಪ್ರತ್ಯಾಗಮ display_index;
        }
    }
    SDL_SetError("Invalid display");
    ಪ್ರತ್ಯಾಗಮ -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ರಿಕ್ತ);

    ಪ್ರತ್ಯಾಗಮ display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ಪ್ರತ್ಯಾಗಮ SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ಯದಿ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ಪ್ರತ್ಯಾಗಮ display->props;
}

ಧ್ರುವ ವರ್ಣ *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ರಿಕ್ತ);

    ಪ್ರತ್ಯಾಗಮ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("rect");
    }

    ಯದಿ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ಯದಿ (_this->GetDisplayBounds(_this, display, rect)) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }

    // Assume that the displays are left to right
    ಯದಿ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ಅನ್ಯಥಾ {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ಪ್ರತ್ಯಾಗಮ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("rect");
    }

    ಯದಿ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ಯದಿ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }

    // Oh well, just give the entire display bounds.
    ಪ್ರತ್ಯಾಗಮ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ಯದಿ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ಪ್ರತ್ಯಾಗಮ display->natural_orientation;
    } ಅನ್ಯಥಾ {
        // Default to landscape if the driver hasn't set it
        ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ಯದಿ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ಪ್ರತ್ಯಾಗಮ display->current_orientation;
    } ಅನ್ಯಥಾ {
        // Default to landscape if the driver hasn't set it
        ಪ್ರತ್ಯಾಗಮ SDL_ORIENTATION_LANDSCAPE;
    }
}

ಶೂನ್ಯ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ಭಿನ್ನ scale)
{
    ಯದಿ (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
            ಯದಿ (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

ಭಿನ್ನ SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ಪ್ರತ್ಯಾಗಮ display->content_scale;
}

ಶೂನ್ಯ SDL_SetWindowHDRProperties(SDL_Window *window, ಧ್ರುವ SDL_HDROutputProperties *HDR, bool send_event)
{
    ಧ್ರುವ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ಯದಿ (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        ಯದಿ (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

ಶೂನ್ಯ SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ಧ್ರುವ SDL_HDROutputProperties *HDR)
{
    ಧ್ರುವ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ಧ್ರುವ bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	ಯದಿ (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ಯದಿ (changed && !SDL_DriverSendsHDRChanges(_this)) {
        ಪ್ರತಿ (SDL_Window *w = display->device->windows; w; w = w->next) {
            ಯದಿ (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ಯದಿ (display->ಅಂಕೆ_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ಸ್ಥಿರ ಧ್ರುವ SDL_DisplayMode *SDL_GetFullscreenModeMatch(ಧ್ರುವ SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    ಯದಿ (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_memcpy(&fullscreen_mode, mode, ಪರಿಮಾಣ(fullscreen_mode));
    ಯದಿ (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = ರಿಕ್ತ;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    ಯದಿ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ಯದಿ (!mode) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < display->ಅಂಕೆ_fullscreen_modes; ++i) {
                ಯದಿ (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], ಪರಿಮಾಣ(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    ಭಙ್ಗ;
                }
            }
        }

        // Search for a mode with the same characteristics
        ಯದಿ (!mode) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < display->ಅಂಕೆ_fullscreen_modes; ++i) {
                ಯದಿ (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    ಭಙ್ಗ;
                }
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ಧ್ರುವ SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    ಪೂರ್ಣಾಙ್ಕ i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, ಪರಿಮಾಣ(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->ಅಂಕೆ_fullscreen_modes;
    ಪ್ರತಿ (i = 0; i < nmodes; ++i) {
        ಯದಿ (cmpmodes(&new_mode, &modes[i]) == 0) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    // Go ahead and add the new mode
    ಯದಿ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * ಪರಿಮಾಣ(*modes));
        ಯದಿ (!modes) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        ಯದಿ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * ಪರಿಮಾಣ(*modes));
            ಪ್ರತಿ (i = 0; i < nmodes; ++i) {
                ಯದಿ (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->ಅಂಕೆ_fullscreen_modes++], &new_mode, ಪರಿಮಾಣ(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->ಅಂಕೆ_fullscreen_modes,
              ಪರಿಮಾಣ(SDL_DisplayMode), cmpmodes);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = display->ಅಂಕೆ_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = ರಿಕ್ತ;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ರಿಕ್ತ;
    display->ಅಂಕೆ_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ಯದಿ (ಎಣಿಕೆ) {
        *ಎಣಿಕೆ = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ರಿಕ್ತ);

    SDL_UpdateFullscreenDisplayModes(display);

    ಅಂಕೆ_modes = display->ಅಂಕೆ_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((ಅಂಕೆ_modes + 1) * ಪರಿಮಾಣ(*result) + ಅಂಕೆ_modes * ಪರಿಮಾಣ(**result));
    ಯದಿ (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((ಅಂಕೆ_modes + 1) * ಪರಿಮಾಣ(*result)));
        ಯದಿ (ಅಂಕೆ_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, ಅಂಕೆ_modes * ಪರಿಮಾಣ(*modes));
        }
        ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = ರಿಕ್ತ;

        ಯದಿ (ಎಣಿಕೆ) {
            *ಎಣಿಕೆ = ಅಂಕೆ_modes;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (ಎಣಿಕೆ) {
            *ಎಣಿಕೆ = 0;
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಭಿನ್ನ refresh_rate, bool include_ಮೇಲಿನ_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ಧ್ರುವ SDL_DisplayMode *mode, *closest = ರಿಕ್ತ;
    ಭಿನ್ನ aspect_ratio;
    ಪೂರ್ಣಾಙ್ಕ i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    ಯದಿ (h > 0) {
        aspect_ratio = (ಭಿನ್ನ)w / h;
    } ಅನ್ಯಥಾ {
        aspect_ratio = 1.0f;
    }

    ಯದಿ (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    ಪ್ರತಿ (i = 0; i < display->ಅಂಕೆ_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        ಯದಿ (w > mode->w) {
            // Out of sorted modes large enough here
            ಭಙ್ಗ;
        }
        ಯದಿ (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            ಅನುವರ್ತ;
        }
        ಯದಿ (mode->pixel_density > 1.0f && !include_ಮೇಲಿನ_density_modes) {
            ಅನುವರ್ತ;
        }
        ಯದಿ (closest) {
            ಭಿನ್ನ current_aspect_ratio = (ಭಿನ್ನ)mode->w / mode->h;
            ಭಿನ್ನ closest_aspect_ratio = (ಭಿನ್ನ)closest->w / closest->h;
            ಯದಿ (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                ಅನುವರ್ತ;
            }

            ಯದಿ (mode->w == closest->w && mode->h == closest->h) {
                ಯದಿ (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    ಅನುವರ್ತ;
                }
                ಯದಿ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    ಅನುವರ್ತ;
                }
            }
        }

        closest = mode;
    }
    ಯದಿ (!closest) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool DisplayModeChanged(ಧ್ರುವ SDL_DisplayMode *old_mode, ಧ್ರುವ SDL_DisplayMode *new_mode)
{
    ಪ್ರತ್ಯಾಗಮ ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

ಶೂನ್ಯ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ಧ್ರುವ SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ಯದಿ (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    ಯದಿ (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        ಯದಿ (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ಧ್ರುವ SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ರಿಕ್ತ);

    ಪ್ರತ್ಯಾಗಮ &display->desktop_mode;
}

ಶೂನ್ಯ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ಧ್ರುವ SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ಯದಿ (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } ಅನ್ಯಥಾ {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    ಯದಿ (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ಧ್ರುವ SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ರಿಕ್ತ);

    ಪ್ರತ್ಯಾಗಮ display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ಯದಿ (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    ಯದಿ (mode == display->current_mode) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
#endif

    // Actually change the display mode
    ಯದಿ (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        ಯದಿ (!result) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ಪ್ರತ್ಯಾಗಮ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ಸ್ಥಿರ ಶೂನ್ಯ SDL_GetClosestPointOnRect(ಧ್ರುವ SDL_Rect *rect, SDL_Point *point)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ ಬಲ = rect->x + rect->w - 1;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ bottom = rect->y + rect->h - 1;

    ಯದಿ (point->x < rect->x) {
        point->x = rect->x;
    } ಅನ್ಯಥಾ ಯದಿ (point->x > ಬಲ) {
        point->x = ಬಲ;
    }

    ಯದಿ (point->y < rect->y) {
        point->y = rect->y;
    } ಅನ್ಯಥಾ ಯದಿ (point->y > bottom) {
        point->y = bottom;
    }
}

ಸ್ಥಿರ SDL_DisplayID GetDisplayForRect(ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    ಪೂರ್ಣಾಙ್ಕ i, dist;
    SDL_DisplayID closest = 0;
    ಪೂರ್ಣಾಙ್ಕ closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    ಯದಿ (_this) {
        ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ಯದಿ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ರಿಕ್ತ)) {
                ಪ್ರತ್ಯಾಗಮ display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ಯದಿ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ಯದಿ (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    ಪ್ರತ್ಯಾಗಮ closest;
}

ಶೂನ್ಯ SDL_RelativeToGlobalForWindow(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ rel_x, ಪೂರ್ಣಾಙ್ಕ rel_y, ಪೂರ್ಣಾಙ್ಕ *abs_x, ಪೂರ್ಣಾಙ್ಕ *abs_y)
{
    SDL_Window *w;

    ಯದಿ (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        ಪ್ರತಿ (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            ಯದಿ (!SDL_WINDOW_IS_POPUP(w)) {
                ಭಙ್ಗ;
            }
        }
    }

    ಯದಿ (abs_x) {
        *abs_x = rel_x;
    }
    ಯದಿ (abs_y) {
        *abs_y = rel_y;
    }
}

ಶೂನ್ಯ SDL_GlobalToRelativeForWindow(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ abs_x, ಪೂರ್ಣಾಙ್ಕ abs_y, ಪೂರ್ಣಾಙ್ಕ *rel_x, ಪೂರ್ಣಾಙ್ಕ *rel_y)
{
    SDL_Window *w;

    ಯದಿ (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        ಪ್ರತಿ (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            ಯದಿ (!SDL_WINDOW_IS_POPUP(w)) {
                ಭಙ್ಗ;
            }
        }
    }

    ಯದಿ (rel_x) {
        *rel_x = abs_x;
    }
    ಯದಿ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ಧ್ರುವ SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಪ್ರತ್ಯಾಗಮ GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ಧ್ರುವ SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಪ್ರತ್ಯಾಗಮ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ಸ್ಥಿರ SDL_DisplayID GetDisplayAtOrigin(ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        SDL_Rect rect;
        ಧ್ರುವ SDL_DisplayID cur_id = _this->displays[i]->id;
        ಯದಿ (SDL_GetDisplayBounds(cur_id, &rect)) {
            ಯದಿ (x == rect.x && y == rect.y) {
                ಪ್ರತ್ಯಾಗಮ cur_id;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    ಯದಿ (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    ಯದಿ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ಅನ್ಯಥಾ {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    ಯದಿ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ಪ್ರತ್ಯಾಗಮ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, ರಿಕ್ತ);

    // An explicit fullscreen display overrides all
    ಯದಿ (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ಯದಿ (!displayID) {
        displayID = window->pending_displayID;
    }
    ಯದಿ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ x = window->last_position_pending ? window->pending.x : window->x;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ y = window->last_position_pending ? window->pending.y : window->y;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ w = window->last_size_pending ? window->pending.w : window->w;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ಯದಿ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ಯದಿ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ಪ್ರತ್ಯಾಗಮ SDL_GetVideoDisplay(displayID);
}

#define SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_GetDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID window_props = SDL_GetWindowProperties(window);
    SDL_VideoDisplay *fs_display = SDL_GetVideoDisplayForFullscreenWindow(window);
    ಯದಿ (fs_display) {
        SDL_Set_ಸಂಖ್ಯೆ_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ಅನ್ಯಥಾ {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ಪ್ರತ್ಯಾಗಮ GetDisplayForWindow(window);
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    ಯದಿ (SDL_SendsDisplayChanges(_this)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    ಯದಿ (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        ಯದಿ (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            ಯದಿ (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                ಪೂರ್ಣಾಙ್ಕ old_area = old_overlap.w * old_overlap.h;
                ಪೂರ್ಣಾಙ್ಕ new_area = new_overlap.w * new_overlap.h;
                ಭಿನ್ನ new_overlap_ratio = (new_area / ((ಭಿನ್ನ)old_area + new_area));
                ಯದಿ (new_overlap_ratio < 0.80) {
                    ಪ್ರತ್ಯಾಗಮ;
                }
            }
        }
    }

    ಯದಿ (displayID != window->displayID) {
        ಪೂರ್ಣಾಙ್ಕ i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ಯದಿ (display->fullscreen_window == window) {
                ಯದಿ (display_index != i) {
                    ಯದಿ (display_index < 0) {
                        display_index = i;
                    } ಅನ್ಯಥಾ {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        ಯದಿ (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = ರಿಕ್ತ;
                    }
                }
                ಭಙ್ಗ;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (ಪೂರ್ಣಾಙ್ಕ)displayID, 0);
    }
}

ಭಿನ್ನ SDL_GetWindowPixelDensity(SDL_Window *window)
{
    ಪೂರ್ಣಾಙ್ಕ window_w, window_h, pixel_w, pixel_h;
    ಭಿನ್ನ pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    ಯದಿ (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (ಭಿನ್ನ)pixel_w / window_w;
    }
    ಪ್ರತ್ಯಾಗಮ pixel_density;
}

ಭಿನ್ನ SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ಪ್ರತ್ಯಾಗಮ window->display_scale;
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    ಭಿನ್ನ display_scale;

    ಯದಿ (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ ಭಿನ್ನ pixel_density = SDL_GetWindowPixelDensity(window);
        ಧ್ರುವ ಭಿನ್ನ content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    ಯದಿ (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ರಿಕ್ತ;
    SDL_DisplayMode *mode = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    ಯದಿ (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ಯದಿ (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        ಯದಿ (!display) {
            // This should never happen, but it did...
            ಗಚ್ಛ done;
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            display = _this->displays[i];
            ಯದಿ (display->fullscreen_window == window) {
                ಭಙ್ಗ;
            }
        }
        ಯದಿ (!display || i == _this->ಅಂಕೆ_displays) {
            // Already not fullscreen on any display
            display = ರಿಕ್ತ;
        }
    }

    ಯದಿ (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        ಯದಿ (mode) {
            window->fullscreen_exclusive = true;
        } ಅನ್ಯಥಾ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#ಯದಿ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ಯದಿ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ಯದಿ (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            ಯದಿ (display) {
                display->fullscreen_window = ರಿಕ್ತ;
            }
            ಗಚ್ಛ done;
        }
        ಯದಿ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ಯದಿ (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                ಯದಿ (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    ಗಚ್ಛ error;
                }
            } ಅನ್ಯಥಾ ಯದಿ (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    ಯದಿ (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, ರಿಕ್ತ);
                        ಯದಿ (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = ರಿಕ್ತ;
                    }
                }
            }

            ಯದಿ (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                ಗಚ್ಛ done;
            }
        }
    }
#endif

    ಯದಿ (display) {
        // Restore the video mode on other displays if needed
        ಪ್ರತಿ (i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ಯದಿ (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, ರಿಕ್ತ);
                other->fullscreen_window = ರಿಕ್ತ;
            }
        }
    }

    ಯದಿ (fullscreen) {
        ಪೂರ್ಣಾಙ್ಕ mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ಯದಿ (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        ಯದಿ (!SDL_SetDisplayModeForDisplay(display, mode)) {
            ಗಚ್ಛ error;
        }
        ಯದಿ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ಯದಿ (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } ಅನ್ಯಥಾ {
                resized = true;
            }

            ಯದಿ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } ಅನ್ಯಥಾ ಯದಿ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                ಗಚ್ಛ error;
            }
        }

        ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ಯದಿ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ಯದಿ (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } ಅನ್ಯಥಾ {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ಯದಿ (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                ಯದಿ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } ಅನ್ಯಥಾ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } ಅನ್ಯಥಾ {
        bool resized = false;

        // Restore the desktop mode
        ಯದಿ (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, ರಿಕ್ತ);
        }
        ಯದಿ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ಯದಿ (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                ಯದಿ (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ಅನ್ಯಥಾ {
                resized = true;
            }

            ಯದಿ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } ಅನ್ಯಥಾ ಯದಿ (ret == SDL_FULLSCREEN_FAILED) {
                ಗಚ್ಛ error;
            }
        }

        ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            ಯದಿ (display) {
                display->fullscreen_window = ರಿಕ್ತ;
            }

            ಯದಿ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                ಯದಿ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } ಅನ್ಯಥಾ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    ಪ್ರತ್ಯಾಗಮ true;

error:
    ಯದಿ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ಧ್ರುವ SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (mode) {
        ಯದಿ (!SDL_GetFullscreenModeMatch(mode)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } ಅನ್ಯಥಾ {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#ಯದಿ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ಯದಿ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    ಯದಿ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಧ್ರುವ SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ರಿಕ್ತ);
    CHECK_WINDOW_NOT_POPUP(window, ರಿಕ್ತ);

    ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
        ಪ್ರತ್ಯಾಗಮ SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

ಶೂನ್ಯ *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    ಯದಿ (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ಧ್ರುವ SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    ಯದಿ (mode) {
        ಪ್ರತ್ಯಾಗಮ mode->format;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ಮೇಲಿನ_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_ತುದಿ | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

ಸ್ಥಿರ SDL_INLINE bool IsAcceptingDragAndDrop(ಶೂನ್ಯ)
{
    ಯದಿ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

// prepare a newly-created window
ಸ್ಥಿರ SDL_INLINE ಶೂನ್ಯ PrepareDragAndDropSupport(SDL_Window *window)
{
    ಯದಿ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
ಶೂನ್ಯ SDL_ToggleDragAndDropSupport(ಶೂನ್ಯ)
{
    ಯದಿ (_this && _this->AcceptDragAndDrop) {
        ಧ್ರುವ bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(ಪೂರ್ಣಾಙ್ಕ *ಎಣಿಕೆ)
{
    ಯದಿ (ಎಣಿಕೆ) {
        *ಎಣಿಕೆ = 0;
    }

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_Window *window;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_added = 0;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_windows = 0;
    ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
        ++ಅಂಕೆ_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((ಅಂಕೆ_windows + 1) * ಪರಿಮಾಣ(*windows));
    ಯದಿ (!windows) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
        windows[ಅಂಕೆ_added++] = window;
        ಯದಿ (ಅಂಕೆ_added == ಅಂಕೆ_windows) {
            // Race condition? Multi-threading not supported, ignore it
            ಭಙ್ಗ;
        }
    }
    windows[ಅಂಕೆ_added] = ರಿಕ್ತ;

    ಯದಿ (ಎಣಿಕೆ) {
        *ಎಣಿಕೆ = ಅಂಕೆ_added;
    }
    ಪ್ರತ್ಯಾಗಮ windows;
}

ಸ್ಥಿರ ಶೂನ್ಯ ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    ಯದಿ (!SDL_WINDOW_IS_POPUP(window)) {
        ಯದಿ (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        ಯದಿ (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        ಯದಿ (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        ಯದಿ (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        ಯದಿ (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        ಯದಿ (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    ಯದಿ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ಅನ್ಯಥಾ {
        ApplyWindowFlags(window, flags);
        ಯದಿ (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#ಯದಿ defined(SDL_PLATFORM_LINUX)
    ಯದಿ (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_ಮೌಲ್ಯ(window, 0.0f);
    }
#endif
}

ಸ್ಥಿರ bool SDL_ContextNotSupported(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪ್ರತ್ಯಾಗಮ SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ಸ್ಥಿರ bool SDL_DllNotSupported(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪ್ರತ್ಯಾಗಮ SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ಸ್ಥಿರ ಸಂರಚನಾ {
    ಧ್ರುವ ವರ್ಣ *property_name;
    SDL_WindowFlags flag;
    bool invert_ಮೌಲ್ಯ;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_ತುದಿ_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_ತುದಿ,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_ಮೇಲಿನ_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_ಮೇಲಿನ_PIXEL_DENSITY,  false },
    { SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN,          SDL_WINDOW_MAXIMIZED,           false },
    { SDL_PROP_WINDOW_CREATE_MENU_BOOLEAN,               SDL_WINDOW_POPUP_MENU,          false },
    { SDL_PROP_WINDOW_CREATE_METAL_BOOLEAN,              SDL_WINDOW_METAL,               false },
    { SDL_PROP_WINDOW_CREATE_MINIMIZED_BOOLEAN,          SDL_WINDOW_MINIMIZED,           false },
    { SDL_PROP_WINDOW_CREATE_MODAL_BOOLEAN,              SDL_WINDOW_MODAL,               false },
    { SDL_PROP_WINDOW_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_WINDOW_MOUSE_GRABBED,       false },
    { SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN,             SDL_WINDOW_OPENGL,              false },
    { SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN,          SDL_WINDOW_RESIZABLE,           false },
    { SDL_PROP_WINDOW_CREATE_TRANSPARENT_BOOLEAN,        SDL_WINDOW_TRANSPARENT,         false },
    { SDL_PROP_WINDOW_CREATE_TOOLTIP_BOOLEAN,            SDL_WINDOW_TOOLTIP,             false },
    { SDL_PROP_WINDOW_CREATE_UTILITY_BOOLEAN,            SDL_WINDOW_UTILITY,             false },
    { SDL_PROP_WINDOW_CREATE_VULKAN_BOOLEAN,             SDL_WINDOW_VULKAN,              false }
};

ಸ್ಥಿರ SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_ಸಂಖ್ಯೆ, 0);

    ಪ್ರತಿ (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        ಯದಿ (SDL_WindowFlagProperties[i].invert_ಮೌಲ್ಯ) {
            ಯದಿ (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } ಅನ್ಯಥಾ {
            ಯದಿ (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ಧ್ರುವ ವರ್ಣ *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, ರಿಕ್ತ);
    ಪೂರ್ಣಾಙ್ಕ x = (ಪೂರ್ಣಾಙ್ಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_X_ಸಂಖ್ಯೆ, SDL_WINDOWPOS_UNDEFINED);
    ಪೂರ್ಣಾಙ್ಕ y = (ಪೂರ್ಣಾಙ್ಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_Y_ಸಂಖ್ಯೆ, SDL_WINDOWPOS_UNDEFINED);
    ಪೂರ್ಣಾಙ್ಕ w = (ಪೂರ್ಣಾಙ್ಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_ಸಂಖ್ಯೆ, 0);
    ಪೂರ್ಣಾಙ್ಕ h = (ಪೂರ್ಣಾಙ್ಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_ಸಂಖ್ಯೆ, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, ರಿಕ್ತ);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    ಯದಿ (!_this) {
        // Initialize the video system if needed
        ಯದಿ (!SDL_Init(SDL_INIT_VIDEO)) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        // Make clang-tidy happy
        ಯದಿ (!_this) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    ಯದಿ ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        ಯದಿ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        // Tooltip and popup menu window must specify a parent window
        ಯದಿ (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    ಯದಿ (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned ಪೂರ್ಣಾಙ್ಕ)type_flags);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Make sure the display list is up to date for window placement
    ಯದಿ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ಯದಿ (w < 1) {
        w = 1;
    }
    ಯದಿ (h < 1) {
        h = 1;
    }

    ಯದಿ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ಯದಿ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ಅನ್ಯಥಾ ಯದಿ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ಯದಿ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ಯದಿ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ಯದಿ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ಯದಿ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ಯದಿ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ಯದಿ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ಯದಿ (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned ಪೂರ್ಣಾಙ್ಕ)graphics_flags);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // Some platforms have certain graphics backends enabled by default
    ಯದಿ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ಯದಿ (flags & SDL_WINDOW_OPENGL) {
        ಯದಿ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        ಯದಿ (!SDL_GL_LoadLibrary(ರಿಕ್ತ)) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    ಯದಿ (flags & SDL_WINDOW_VULKAN) {
        ಯದಿ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        ಯದಿ (!SDL_Vulkan_LoadLibrary(ರಿಕ್ತ)) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    ಯದಿ (flags & SDL_WINDOW_METAL) {
        ಯದಿ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, ಪರಿಮಾಣ(*window));
    ಯದಿ (!window) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, true);
    window->id = SDL_GetNextObjectID();
    window->floating.x = window->windowed.x = window->x = x;
    window->floating.y = window->windowed.y = window->y = y;
    window->floating.w = window->windowed.w = window->w = w;
    window->floating.h = window->windowed.h = window->h = h;
    window->undefined_x = undefined_x;
    window->undefined_y = undefined_y;
    window->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    ಯದಿ (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    ಯದಿ (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        window->x = bounds.x;
        window->y = bounds.y;
        window->w = bounds.w;
        window->h = bounds.h;
        window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->display_scale = 1.0f;
    window->opacity = 1.0f;
    window->next = _this->windows;
    window->is_destroying = false;
    window->displayID = GetDisplayForWindow(window);
    window->external_graphics_context = external_graphics_context;
    window->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    ಯದಿ (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ಯದಿ (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    ಯದಿ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_ತಳ್ಳು_Error();
        SDL_DestroyWindow(window);
        SDL_ತೆಗೆ_Error();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ಯದಿ !defined(SDL_PLATFORM_WINDOWS)
    ಯದಿ (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    ಯದಿ (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ಪ್ರತ್ಯಾಗಮ window;
}

SDL_Window *SDL_CreateWindow(ಧ್ರುವ ವರ್ಣ *title, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    ಯದಿ (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_ಸಂಖ್ಯೆ, w);
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_ಸಂಖ್ಯೆ, h);
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_ಸಂಖ್ಯೆ, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ಪ್ರತ್ಯಾಗಮ window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, ಪೂರ್ಣಾಙ್ಕ offset_x, ಪೂರ್ಣಾಙ್ಕ offset_y, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ಯದಿ (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_X_ಸಂಖ್ಯೆ, offset_x);
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_Y_ಸಂಖ್ಯೆ, offset_y);
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_ಸಂಖ್ಯೆ, w);
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_ಸಂಖ್ಯೆ, h);
    SDL_Set_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_ಸಂಖ್ಯೆ, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ಪ್ರತ್ಯಾಗಮ window;
}

ಸ್ಥಿರ bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ಯದಿ (!_this->ReconfigureWindow) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಧ್ರುವ SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ಯದಿ (graphics_flags & (graphics_flags - 1)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Conflicting window flags specified");
    }

    ಯದಿ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ಪ್ರತ್ಯಾಗಮ SDL_ContextNotSupported("OpenGL");
    }
    ಯದಿ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ಪ್ರತ್ಯಾಗಮ SDL_ContextNotSupported("Vulkan");
    }
    ಯದಿ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ಪ್ರತ್ಯಾಗಮ SDL_ContextNotSupported("Metal");
    }

    ಯದಿ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ಯದಿ (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ಯದಿ (!_this->ReconfigureWindow(_this, window, 0)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ಯದಿ (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    ಯದಿ (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(ರಿಕ್ತ);
        ಯದಿ (!loaded_opengl) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ ಯದಿ (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(ರಿಕ್ತ);
        ಯದಿ (!loaded_vulkan) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ಯದಿ (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        ಯದಿ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ಯದಿ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ಪ್ರತ್ಯಾಗಮ false;
    }

    window->flags |= graphics_flags;

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_RecreateWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_load = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_load = false;
    SDL_WindowFlags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ಯದಿ (graphics_flags & (graphics_flags - 1)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Conflicting window flags specified");
    }

    ಯದಿ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ಪ್ರತ್ಯಾಗಮ SDL_ContextNotSupported("OpenGL");
    }
    ಯದಿ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ಪ್ರತ್ಯಾಗಮ SDL_ContextNotSupported("Vulkan");
    }
    ಯದಿ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ಪ್ರತ್ಯಾಗಮ SDL_ContextNotSupported("Metal");
    }

    ಯದಿ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } ಅನ್ಯಥಾ {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ಯದಿ (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    ಯದಿ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ಧ್ರುವ bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    ಯದಿ ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        ಯದಿ (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } ಅನ್ಯಥಾ {
            need_gl_unload = true;
        }
    } ಅನ್ಯಥಾ ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    ಯದಿ ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        ಯದಿ (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } ಅನ್ಯಥಾ {
            need_vulkan_unload = true;
        }
    } ಅನ್ಯಥಾ ಯದಿ (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    ಯದಿ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ಯದಿ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ಯದಿ (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    ಯದಿ (need_gl_load) {
        ಯದಿ (!SDL_GL_LoadLibrary(ರಿಕ್ತ)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        loaded_opengl = true;
    }

    ಯದಿ (need_vulkan_load) {
        ಯದಿ (!SDL_Vulkan_LoadLibrary(ರಿಕ್ತ)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    ಯದಿ (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        ಯದಿ (!_this->CreateSDLWindow(_this, window, 0)) {
            ಯದಿ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            ಯದಿ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಯದಿ (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    ಯದಿ (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    ಯದಿ (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    ಯದಿ (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    ಯದಿ (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    ಯದಿ (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    ಯದಿ (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ಯದಿ (!SDL_ReconfigureWindowInternal(window, flags)) {
        ಪ್ರತ್ಯಾಗಮ SDL_RecreateWindow(window, flags);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_HasWindows(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ಪ್ರತ್ಯಾಗಮ window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (id) {
        ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
            ಯದಿ (window->id == id) {
                ಪ್ರತ್ಯಾಗಮ window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ರಿಕ್ತ);

    ಪ್ರತ್ಯಾಗಮ window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ಯದಿ (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ಪ್ರತ್ಯಾಗಮ window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ಪ್ರತ್ಯಾಗಮ window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ಧ್ರುವ ವರ್ಣ *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (title == window->title) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಯದಿ (!title) {
        title = "";
    }
    ಯದಿ (window->title && SDL_strcmp(title, window->title) == 0) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    ಯದಿ (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಧ್ರುವ ವರ್ಣ *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ಪ್ರತ್ಯಾಗಮ window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ಯದಿ (!window->icon) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (!_this->SetWindowIcon) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಪ್ರತ್ಯಾಗಮ _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    ಯದಿ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    ಯದಿ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    ಯದಿ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ಯದಿ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ಅನ್ಯಥಾ ಯದಿ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ಯದಿ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        ಯದಿ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ಯದಿ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }
        ಯದಿ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ಯದಿ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ಅನ್ಯಥಾ {
        /* See if the requested window position matches the origin of any displays and set
         * the pending fullscreen display ID if it does. This needs to be set early in case
         * the window is prevented from moving to the exact origin due to struts.
         */
        window->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    window->pending.x = x;
    window->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    ಯದಿ (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    ಯದಿ (_this->SetWindowPosition) {
        ಧ್ರುವ bool result = _this->SetWindowPosition(_this, window);
        ಯದಿ (result) {
            SDL_SyncIfRequired(window);
        }
        ಪ್ರತ್ಯಾಗಮ result;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *x, ಪೂರ್ಣಾಙ್ಕ *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ಅನ್ಯಥಾ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    ಯದಿ (use_display_origin) {
        SDL_DisplayID displayID;

        ಯದಿ (x) {
            *x = 0;
        }
        ಯದಿ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        ಯದಿ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ಯದಿ (x) {
                *x = bounds.x;
            }
            ಯದಿ (y) {
                *y = bounds.y;
            }
        }
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        ಯದಿ (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        ಯದಿ (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (!_this->SetWindowBordered) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಧ್ರುವ bool want = bordered;
    ಧ್ರುವ bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    ಯದಿ (want != have) {
        ಯದಿ (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } ಅನ್ಯಥಾ {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (!_this->SetWindowResizable) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಧ್ರುವ bool want = resizable;
    ಧ್ರುವ bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    ಯದಿ (want != have) {
        ಯದಿ (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ಅನ್ಯಥಾ {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_Set_Window_Always_On_ತುದಿ(SDL_Window *window, bool on_ತುದಿ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (!_this->Set_Window_Always_On_ತುದಿ) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಧ್ರುವ bool want = on_ತುದಿ;
    ಧ್ರುವ bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_ತುದಿ) != 0);
    ಯದಿ (want != have) {
        ಯದಿ (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_ತುದಿ;
        } ಅನ್ಯಥಾ {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_ತುದಿ;
        }
        _this->Set_Window_Always_On_ತುದಿ(_this, window, want);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowSize(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    ಭಿನ್ನ new_aspect = w / (ಭಿನ್ನ)h;
    ಯದಿ (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(h * window->max_aspect);
    } ಅನ್ಯಥಾ ಯದಿ (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ಯದಿ (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    ಯದಿ (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    ಯದಿ (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    ಯದಿ (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    ಯದಿ (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_GetWindowSize(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *w, ಪೂರ್ಣಾಙ್ಕ *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ಯದಿ (w) {
        *w = window->w;
    }
    ಯದಿ (h) {
        *h = window->h;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, ಭಿನ್ನ min_aspect, ಭಿನ್ನ max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    ಯದಿ (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    ಪೂರ್ಣಾಙ್ಕ w = window->last_size_pending ? window->pending.w : window->floating.w;
    ಪೂರ್ಣಾಙ್ಕ h = window->last_size_pending ? window->pending.h : window->floating.h;
    ಪ್ರತ್ಯಾಗಮ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, ಭಿನ್ನ *min_aspect, ಭಿನ್ನ *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    ಯದಿ (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *ತುದಿ, ಪೂರ್ಣಾಙ್ಕ *ಎಡ, ಪೂರ್ಣಾಙ್ಕ *bottom, ಪೂರ್ಣಾಙ್ಕ *ಬಲ)
{
    ಪೂರ್ಣಾಙ್ಕ dummy = 0;

    ಯದಿ (!ತುದಿ) {
        ತುದಿ = &dummy;
    }
    ಯದಿ (!ಎಡ) {
        ಎಡ = &dummy;
    }
    ಯದಿ (!ಬಲ) {
        ಬಲ = &dummy;
    }
    ಯದಿ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *ತುದಿ = *ಎಡ = *bottom = *ಬಲ = 0;

    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!_this->GetWindowBordersSize) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಪ್ರತ್ಯಾಗಮ _this->GetWindowBordersSize(_this, window, ತುದಿ, ಎಡ, bottom, ಬಲ);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *w, ಪೂರ್ಣಾಙ್ಕ *h)
{
    ಪೂರ್ಣಾಙ್ಕ filter;

    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!w) {
        w = &filter;
    }

    ಯದಿ (!h) {
        h = &filter;
    }

    ಯದಿ (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } ಅನ್ಯಥಾ {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ಧ್ರುವ SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        ಯದಿ ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } ಅನ್ಯಥಾ {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        ಯದಿ (mode) {
            *w = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceilf(*w * mode->pixel_density);
            *h = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ min_w, ಪೂರ್ಣಾಙ್ಕ min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    ಯದಿ (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    ಪೂರ್ಣಾಙ್ಕ w = window->last_size_pending ? window->pending.w : window->floating.w;
    ಪೂರ್ಣಾಙ್ಕ h = window->last_size_pending ? window->pending.h : window->floating.h;
    ಪ್ರತ್ಯಾಗಮ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *min_w, ಪೂರ್ಣಾಙ್ಕ *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ಯದಿ (min_w) {
        *min_w = window->min_w;
    }
    ಯದಿ (min_h) {
        *min_h = window->min_h;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ max_w, ಪೂರ್ಣಾಙ್ಕ max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("max_h");
    }

    ಯದಿ ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    ಯದಿ (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    ಪೂರ್ಣಾಙ್ಕ w = window->last_size_pending ? window->pending.w : window->floating.w;
    ಪೂರ್ಣಾಙ್ಕ h = window->last_size_pending ? window->pending.h : window->floating.h;
    ಪ್ರತ್ಯಾಗಮ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *max_w, ಪೂರ್ಣಾಙ್ಕ *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ಯದಿ (max_w) {
        *max_w = window->max_w;
    }
    ಯದಿ (max_h) {
        *max_h = window->max_h;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ಯದಿ (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } ಅನ್ಯಥಾ {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    ಪ್ರತಿ (child = window->first_child; child; child = child->next_sibling) {
        ಯದಿ (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            ಭಙ್ಗ;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // Hide all child windows
    ಪ್ರತಿ (child = window->first_child; child; child = child->next_sibling) {
        ಯದಿ (child->flags & SDL_WINDOW_HIDDEN) {
            ಭಙ್ಗ;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ಧ್ರುವ SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    ಯದಿ (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } ಅನ್ಯಥಾ {
        SDL_SetMouseFocus(ರಿಕ್ತ);
        SDL_SetKeyboardFocus(ರಿಕ್ತ);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಯದಿ (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (!_this->MaximizeWindow) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ಪ್ರತ್ಯಾಗಮ true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (!_this->MinimizeWindow) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ಪ್ರತ್ಯಾಗಮ true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (!_this->RestoreWindow) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ಪ್ರತ್ಯಾಗಮ true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        ಯದಿ (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } ಅನ್ಯಥಾ {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ಯದಿ (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    ಯದಿ (result) {
        SDL_SyncIfRequired(window);
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (_this->SyncWindow) {
        ಪ್ರತ್ಯಾಗಮ _this->SyncWindow(_this, window);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ true;
    }
}

ಸ್ಥಿರ bool ShouldAttemptTextureFramebuffer(ಶೂನ್ಯ)
{
    ಧ್ರುವ ವರ್ಣ *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ಯದಿ (!_this->CreateWindowFramebuffer) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ಯದಿ (hint && *hint) {
        ಯದಿ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ಅನ್ಯಥಾ {
            attempt_texture_framebuffer = true;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ಅನ್ಯಥಾ {
            attempt_texture_framebuffer = false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ attempt_texture_framebuffer;
}

ಸ್ಥಿರ SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    ಶೂನ್ಯ *pixels = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ pitch = 0;
    bool created_framebuffer = false;
    ಪೂರ್ಣಾಙ್ಕ w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    ಯದಿ (!_this->checked_texture_framebuffer) {
        ಯದಿ (ShouldAttemptTextureFramebuffer()) {
            ಯದಿ (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ಅನ್ಯಥಾ {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->CreateWindowFramebuffer = SDL_CreateWindowTexture;
                _this->SetWindowFramebufferVSync = SDL_SetWindowTextureVSync;
                _this->GetWindowFramebufferVSync = SDL_GetWindowTextureVSync;
                _this->UpdateWindowFramebuffer = SDL_UpdateWindowTexture;
                _this->DestroyWindowFramebuffer = SDL_DestroyWindowTexture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    ಯದಿ (!created_framebuffer) {
        ಯದಿ (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        ಯದಿ (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    ಯದಿ (window->surface) {
        // We may have gone recursive and already created the surface
        ಪ್ರತ್ಯಾಗಮ window->surface;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಪ್ರತ್ಯಾಗಮ window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ರಿಕ್ತ);

    ಯದಿ (!window->surface_valid) {
        ಯದಿ (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = ರಿಕ್ತ;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        ಯದಿ (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ಪ್ರತ್ಯಾಗಮ window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!_this->SetWindowFramebufferVSync) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }
    ಪ್ರತ್ಯಾಗಮ _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!_this->GetWindowFramebufferVSync) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }
    ಪ್ರತ್ಯಾಗಮ _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    ಪ್ರತ್ಯಾಗಮ SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ಧ್ರುವ SDL_Rect *rects,
                                 ಪೂರ್ಣಾಙ್ಕ numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!window->surface_valid) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ಪ್ರತ್ಯಾಗಮ _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = ರಿಕ್ತ;
        window->surface_valid = false;
    }

    ಯದಿ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ಯದಿ (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, ಭಿನ್ನ opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!_this->SetWindowOpacity) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (opacity < 0.0f) {
        opacity = 0.0f;
    } ಅನ್ಯಥಾ ಯದಿ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    ಯದಿ (result) {
        window->opacity = opacity;
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

ಭಿನ್ನ SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ಪ್ರತ್ಯಾಗಮ window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    ಯದಿ (window == parent) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Cannot set the parent of a window to itself.");
    }

    ಯದಿ (!_this->SetWindowParent) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (window->flags & SDL_WINDOW_MODAL) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ಯದಿ (window->parent == parent) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಧ್ರುವ bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : ರಿಕ್ತ);

    ಪ್ರತ್ಯಾಗಮ ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (!_this->SetWindowModal) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (modal) {
        ಯದಿ (!window->parent) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } ಅನ್ಯಥಾ ಯದಿ (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ true; // Already not modal, so nothing to do.
    }

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಪ್ರತ್ಯಾಗಮ _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ಯಾವತ್ (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ಯದಿ (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS);
        }
    }

    *new_focus = focus;
    ಪ್ರತ್ಯಾಗಮ set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    ಪ್ರತಿ (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    ಪ್ರತಿ (w = current_focus; w != toplevel_parent; w = w->parent) {
        ಯದಿ (w == window) {
            found_higher_focus = true;
            ಭಙ್ಗ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಧ್ರುವ bool want = (focusable != false); // normalize the flag.
    ಧ್ರುವ bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    ಯದಿ ((want != have) && (_this->SetWindowFocusable)) {
        ಯದಿ (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } ಅನ್ಯಥಾ {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        ಯದಿ (!_this->SetWindowFocusable(_this, window, want)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಧ್ರುವ bool want = (fill != false); // normalize the flag.
    ಧ್ರುವ bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    ಯದಿ ((want != have) && (_this->SetWindowFillDocument)) {
        ಯದಿ (!_this->SetWindowFillDocument(_this, window, want)) {
            ಪ್ರತ್ಯಾಗಮ false;
        } ಅನ್ಯಥಾ ಯದಿ (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } ಅನ್ಯಥಾ {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    ಯದಿ (window->flags & SDL_WINDOW_ಒಳಹರಿವು_FOCUS) {
        ಯದಿ (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ಅನ್ಯಥಾ {
            mouse_grabbed = false;
        }

        ಯದಿ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ಅನ್ಯಥಾ {
            keyboard_grabbed = false;
        }
    } ಅನ್ಯಥಾ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ಯದಿ (mouse_grabbed || keyboard_grabbed) {
        ಯದಿ (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            ಯದಿ (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            ಯದಿ (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } ಅನ್ಯಥಾ ಯದಿ (_this->grabbed_window == window) {
        _this->grabbed_window = ರಿಕ್ತ; // ungrabbing input.
    }

    ಯದಿ (_this->SetWindowMouseGrab) {
        ಯದಿ (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    ಯದಿ (_this->SetWindowKeyboardGrab) {
        ಯದಿ (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    ಯದಿ (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = ರಿಕ್ತ;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        ಯದಿ (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } ಅನ್ಯಥಾ {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಯದಿ (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } ಅನ್ಯಥಾ {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ಯದಿ (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (window->flags & SDL_WINDOW_HIDDEN) {
        ಯದಿ (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } ಅನ್ಯಥಾ {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಯದಿ (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } ಅನ್ಯಥಾ {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ಯದಿ (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ಪ್ರತ್ಯಾಗಮ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ಪ್ರತ್ಯಾಗಮ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(ಶೂನ್ಯ)
{
    ಯದಿ (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ಪ್ರತ್ಯಾಗಮ _this->grabbed_window;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ಧ್ರುವ SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!_this->SetWindowMouseRect) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ಯದಿ (!rect) {
        rect = &zero;
    }

    ಯದಿ (SDL_memcmp(&window->mouse_rect, rect, ಪರಿಮಾಣ(*rect)) == 0) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    SDL_memcpy(&window->mouse_rect, rect, ಪರಿಮಾಣ(*rect));

    ಪ್ರತ್ಯಾಗಮ _this->SetWindowMouseRect(_this, window);
}

ಧ್ರುವ SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ರಿಕ್ತ);

    ಯದಿ (SDL_RectEmpty(&window->mouse_rect)) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ &window->mouse_rect;
    }
}

bool SDL_SetWindowRelativeMouseMode(SDL_Window *window, bool enabled)
{
    CHECK_WINDOW_MAGIC(window, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    ಯದಿ (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } ಅನ್ಯಥಾ {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    ಯದಿ (!SDL_UpdateRelativeMouseMode()) {
        ಯದಿ (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } ಅನ್ಯಥಾ {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ಪ್ರತ್ಯಾಗಮ true;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (_this->FlashWindow) {
        ಪ್ರತ್ಯಾಗಮ _this->FlashWindow(_this, window, operation);
    }

    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    ಯದಿ (_this->ApplyWindowProgress) {
        ಯದಿ (!_this->ApplyWindowProgress(_this, window)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ಪ್ರತ್ಯಾಗಮ window->progress_state;
}

bool SDL_Set_Window_Progress_ಮೌಲ್ಯ(SDL_Window *window, ಭಿನ್ನ ಮೌಲ್ಯ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಮೌಲ್ಯ = SDL_clamp(ಮೌಲ್ಯ, 0.0f, 1.f);

    window->progress_ಮೌಲ್ಯ = ಮೌಲ್ಯ;

    ಯದಿ (_this->ApplyWindowProgress) {
        ಯದಿ (!_this->ApplyWindowProgress(_this, window)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಭಿನ್ನ SDL_Get_Window_Progress_ಮೌಲ್ಯ(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ಪ್ರತ್ಯಾಗಮ window->progress_ಮೌಲ್ಯ;
}

ಶೂನ್ಯ SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

ಶೂನ್ಯ SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

ಶೂನ್ಯ SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    ಯದಿ (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ಧ್ರುವ bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        ಯದಿ (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_ಮೇಲಿನ_density_modes = false;

            ಯದಿ (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_ಮೇಲಿನ_density_modes = true;
            }
            ಧ್ರುವ bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_ಮೇಲಿನ_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ಯದಿ (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } ಅನ್ಯಥಾ {
            SDL_zero(window->current_fullscreen_mode);
        }

        ಯದಿ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

ಶೂನ್ಯ SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

ಶೂನ್ಯ SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    ಯದಿ ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, ರಿಕ್ತ);
        ಯದಿ (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

ಶೂನ್ಯ SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    ಪೂರ್ಣಾಙ್ಕ pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

ಶೂನ್ಯ SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

ಶೂನ್ಯ SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    ಯದಿ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ಅನ್ಯಥಾ {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ಸ್ಥಿರ ಶೂನ್ಯ SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_ಎಡ;
    rect.y = window->safe_inset_ತುದಿ;
    rect.w = window->w - (window->safe_inset_ಬಲ + window->safe_inset_ಎಡ);
    rect.h = window->h - (window->safe_inset_ತುದಿ + window->safe_inset_bottom);
    ಯದಿ (SDL_memcmp(&rect, &window->safe_rect, ಪರಿಮಾಣ(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

ಶೂನ್ಯ SDL_SetWindowSafeAreaInsets(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ ಎಡ, ಪೂರ್ಣಾಙ್ಕ ಬಲ, ಪೂರ್ಣಾಙ್ಕ ತುದಿ, ಪೂರ್ಣಾಙ್ಕ bottom)
{
    window->safe_inset_ಎಡ = ಎಡ;
    window->safe_inset_ಬಲ = ಬಲ;
    window->safe_inset_ತುದಿ = ತುದಿ;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    ಯದಿ (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (rect) {
        ಯದಿ (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } ಅನ್ಯಥಾ {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ SDL_OnWindowMinimized(SDL_Window *window)
{
    ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

ಶೂನ್ಯ SDL_OnWindowMaximized(SDL_Window *window)
{
}

ಶೂನ್ಯ SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    ಯದಿ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

ಶೂನ್ಯ SDL_OnWindowEnter(SDL_Window *window)
{
    ಯದಿ (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

ಶೂನ್ಯ SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

ಶೂನ್ಯ SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ಯದಿ (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

ಸ್ಥಿರ bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ಧ್ರುವ ವರ್ಣ *hint;

    ಯದಿ (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

#ಯದಿ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ಯದಿ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ಯದಿ (Cocoa_IsShowingModalDialog(window)) {
            ಪ್ರತ್ಯಾಗಮ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ಅನ್ಯಥಾ ಯದಿ (Cocoa_IsWindowInFullscreenSpace(window)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        ಬಾಹ್ಯ bool Android_JNI_ShouldMinimizeOnFocusLoss(ಶೂನ್ಯ);
        ಯದಿ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ಯದಿ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ಯದಿ (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ಪ್ರತ್ಯಾಗಮ true;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

ಶೂನ್ಯ SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    ಯದಿ (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(ಶೂನ್ಯ)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    ಯದಿ (focus) {
        // Get the toplevel parent window.
        ಯಾವತ್ (focus->parent) {
            focus = focus->parent;
        }
    }

    ಪ್ರತ್ಯಾಗಮ focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->ಅಂಕೆ_renderers + 1) * ಪರಿಮಾಣ(*renderers));
    ಯದಿ (!renderers) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    window->renderers = renderers;
    window->renderers[window->ಅಂಕೆ_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < window->ಅಂಕೆ_renderers; ++i) {
        ಯದಿ (window->renderers[i] == renderer) {
            ಯದಿ (i < (window->ಅಂಕೆ_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->ಅಂಕೆ_renderers - i - 1) * ಪರಿಮಾಣ(window->renderers[i]));
            }
            --window->ಅಂಕೆ_renderers;
            ಭಙ್ಗ;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ಯದಿ (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, ರಿಕ್ತ) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

ಶೂನ್ಯ SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    ಯಾವತ್ (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    ಯದಿ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    ಯದಿ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_ಒಳಹರಿವು_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ಯದಿ (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
        ಯದಿ (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = ರಿಕ್ತ;
        }
    }

    // Make sure this window no longer has focus
    ಯದಿ (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(ರಿಕ್ತ);
    }
    ಯದಿ ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ಯದಿ (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(ರಿಕ್ತ);
    }

    // Make no context current if this is the current context window
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        ಯದಿ (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, ರಿಕ್ತ);
        }
    }

    ಯದಿ (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ಯದಿ (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ಯದಿ (_this->grabbed_window == window) {
        _this->grabbed_window = ರಿಕ್ತ; // ungrabbing input.
    }

    ಯದಿ (_this->current_glwin == window) {
        _this->current_glwin = ರಿಕ್ತ;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, ರಿಕ್ತ);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, ರಿಕ್ತ);

    // Unlink the window from the global window list
    ಯದಿ (window->next) {
        window->next->prev = window->prev;
    }
    ಯದಿ (window->prev) {
        window->prev->next = window->next;
    } ಅನ್ಯಥಾ {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }
    ಯದಿ (!_this->suspend_screensaver) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    _this->suspend_screensaver = false;
    ಯದಿ (_this->SuspendScreenSaver) {
        ಪ್ರತ್ಯಾಗಮ _this->SuspendScreenSaver(_this);
    }

    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }
    ಯದಿ (_this->suspend_screensaver) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    _this->suspend_screensaver = true;
    ಯದಿ (_this->SuspendScreenSaver) {
        ಪ್ರತ್ಯಾಗಮ _this->SuspendScreenSaver(_this);
    }

    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

ಶೂನ್ಯ SDL_QuitVideo(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ಯದಿ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ಯಾವತ್ (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    ಯದಿ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ಯದಿ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    ಪ್ರತಿ (i = _this->ಅಂಕೆ_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->ಅಂಕೆ_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ರಿಕ್ತ;

    SDL_CancelClipboardData(0);

    ಯದಿ (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = ರಿಕ್ತ;
    }
    _this->ಮುಕ್ತ(_this);
    _this = ರಿಕ್ತ;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(ಧ್ರುವ ವರ್ಣ *path)
{
    bool result;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }
    ಯದಿ (_this->gl_config.driver_loaded) {
        ಯದಿ (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } ಅನ್ಯಥಾ {
        ಯದಿ (!_this->GL_LoadLibrary) {
            ಪ್ರತ್ಯಾಗಮ SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    ಯದಿ (result) {
        ++_this->gl_config.driver_loaded;
    } ಅನ್ಯಥಾ {
        ಯದಿ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ಧ್ರುವ ವರ್ಣ *proc)
{
    SDL_FunctionPointer func;

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    func = ರಿಕ್ತ;
    ಯದಿ (_this->GL_GetProcAddress) {
        ಯದಿ (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } ಅನ್ಯಥಾ {
            SDL_SetError("No GL driver has been loaded");
        }
    } ಅನ್ಯಥಾ {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ಪ್ರತ್ಯಾಗಮ func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ಧ್ರುವ ವರ್ಣ *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    func = ರಿಕ್ತ;

    ಯದಿ (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } ಅನ್ಯಥಾ {
        SDL_SetError("No EGL library has been loaded");
    }

    ಪ್ರತ್ಯಾಗಮ func;
#ಅನ್ಯಥಾ
    SDL_SetError("SDL was not built with EGL support");
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
#endif
}

ಶೂನ್ಯ SDL_GL_UnloadLibrary(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ;
    }
    ಯದಿ (_this->gl_config.driver_loaded > 0) {
        ಯದಿ (--_this->gl_config.driver_loaded > 0) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        ಯದಿ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ಯದಿ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
ಪ್ರಕಾರನಿರ್ದೇಶ GLenum (APIENTRY* PFNGLGETERRORPROC) (ಶೂನ್ಯ);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
ಪ್ರಕಾರನಿರ್ದೇಶ ಧ್ರುವ GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
ಪ್ರಕಾರನಿರ್ದೇಶ ಧ್ರುವ GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

ಸ್ಥಿರ SDL_INLINE bool isAtLeastGL3(ಧ್ರುವ ವರ್ಣ *verstr)
{
    ಪ್ರತ್ಯಾಗಮ verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ಧ್ರುವ ವರ್ಣ *extension)
{
#ಯದಿ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ಧ್ರುವ ವರ್ಣ *extensions;
    ಧ್ರುವ ವರ್ಣ *start;
    ಧ್ರುವ ವರ್ಣ *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ಯದಿ (where || *extension == '\0') {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    ಯದಿ (start && *start == '0') {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ಯದಿ (!glGetStringFunc) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (isAtLeastGL3((ಧ್ರುವ ವರ್ಣ *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint ಅಂಕೆ_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ಯದಿ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

#ifndef GL_ಅಂಕೆ_EXTENSIONS
#define GL_ಅಂಕೆ_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_ಅಂಕೆ_EXTENSIONS, &ಅಂಕೆ_exts);
        ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_exts; i++) {
            ಧ್ರುವ ವರ್ಣ *thisext = (ಧ್ರುವ ವರ್ಣ *)glGetStringiFunc(GL_EXTENSIONS, i);
            ಯದಿ (SDL_strcmp(thisext, extension) == 0) {
                ಪ್ರತ್ಯಾಗಮ true;
            }
        }

        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ಧ್ರುವ ವರ್ಣ *)glGetStringFunc(GL_EXTENSIONS);
    ಯದಿ (!extensions) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    ಪ್ರತಿ (;;) {
        where = SDL_strstr(start, extension);
        ಯದಿ (!where) {
            ಭಙ್ಗ;
        }

        terminator = where + SDL_strlen(extension);
        ಯದಿ (where == extensions || *(where - 1) == ' ') {
            ಯದಿ (*terminator == ' ' || *terminator == '\0') {
                ಪ್ರತ್ಯಾಗಮ true;
            }
        }

        start = terminator;
    }
    ಪ್ರತ್ಯಾಗಮ false;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
ಶೂನ್ಯ SDL_GL_DeduceMaxSupportedESProfile(ಪೂರ್ಣಾಙ್ಕ *major, ಪೂರ್ಣಾಙ್ಕ *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#ಯದಿ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ಯದಿ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ಅನ್ಯಥಾ ಯದಿ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ಅನ್ಯಥಾ {
        *major = 2;
        *minor = 0;
    }
#endif
}

ಶೂನ್ಯ SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   ಶೂನ್ಯ *userdata)
{
    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

ಶೂನ್ಯ SDL_GL_ResetAttributes(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    _this->egl_platformattrib_callback = ರಿಕ್ತ;
    _this->egl_surfaceattrib_callback = ರಿಕ್ತ;
    _this->egl_contextattrib_callback = ರಿಕ್ತ;
    _this->egl_attrib_callback_userdata = ರಿಕ್ತ;

    _this->gl_config.red_size = 8;
    _this->gl_config.green_size = 8;
    _this->gl_config.blue_size = 8;
    _this->gl_config.alpha_size = 8;
    _this->gl_config.buffer_size = 0;
    _this->gl_config.depth_size = 16;
    _this->gl_config.stencil_size = 0;
    _this->gl_config.double_buffer = 1;
    _this->gl_config.accum_red_size = 0;
    _this->gl_config.accum_green_size = 0;
    _this->gl_config.accum_blue_size = 0;
    _this->gl_config.accum_alpha_size = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#ifdef SDL_VIDEO_OPENGL
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 1;
    _this->gl_config.profile_mask = 0;
#ನೋಚೇದ್ಯದಿ defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#ನೋಚೇದ್ಯದಿ defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_version = 1;
    _this->gl_config.minor_version = 1;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#endif

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    ಯದಿ (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ)
{
#ಯದಿ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }
    result = true;
    ವಿಕಲ್ಪ (attr) {
    ಪಕ್ಷ SDL_GL_RED_SIZE:
        _this->gl_config.red_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_STEREO:
        _this->gl_config.stereo = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_FLAGS:
        ಯದಿ (ಮೌಲ್ಯ & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", ಮೌಲ್ಯ);
            ಭಙ್ಗ;
        }
        _this->gl_config.flags = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_PROFILE_MASK:
        ಯದಿ (ಮೌಲ್ಯ != 0 &&
            ಮೌಲ್ಯ != SDL_GL_CONTEXT_PROFILE_CORE &&
            ಮೌಲ್ಯ != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            ಮೌಲ್ಯ != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", ಮೌಲ್ಯ);
            ಭಙ್ಗ;
        }
        _this->gl_config.profile_mask = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = ಮೌಲ್ಯ;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        result = SDL_SetError("Unknown OpenGL attribute");
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ result;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, ಪೂರ್ಣಾಙ್ಕ *ಮೌಲ್ಯ)
{
#ಯದಿ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#ifdef SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_BACK_ಎಡ;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!ಮೌಲ್ಯ) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *ಮೌಲ್ಯ = 0;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    ವಿಕಲ್ಪ (attr) {
    ಪಕ್ಷ SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        ಭಙ್ಗ;
#ಅನ್ಯಥಾ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *ಮೌಲ್ಯ = _this->gl_config.double_buffer;
        ಪ್ರತ್ಯಾಗಮ true;
#endif
    ಪಕ್ಷ SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        ಭಙ್ಗ;
#ifdef SDL_VIDEO_OPENGL
    ಪಕ್ಷ SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_STEREO:
        attrib = GL_STEREO;
        ಭಙ್ಗ;
#ಅನ್ಯಥಾ
    ಪಕ್ಷ SDL_GL_ACCUM_RED_SIZE:
    ಪಕ್ಷ SDL_GL_ACCUM_GREEN_SIZE:
    ಪಕ್ಷ SDL_GL_ACCUM_BLUE_SIZE:
    ಪಕ್ಷ SDL_GL_ACCUM_ALPHA_SIZE:
    ಪಕ್ಷ SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *ಮೌಲ್ಯ = 0;
        ಪ್ರತ್ಯಾಗಮ true;
#endif
    ಪಕ್ಷ SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_GL_BUFFER_SIZE:
    {
        ಪೂರ್ಣಾಙ್ಕ rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        ಯದಿ (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಯದಿ (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಯದಿ (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಯದಿ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }

        *ಮೌಲ್ಯ = rsize + gsize + bsize + asize;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *ಮೌಲ್ಯ = (_this->gl_config.accelerated != 0);
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_RETAINED_BACKING:
    {
        *ಮೌಲ್ಯ = _this->gl_config.retained_backing;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *ಮೌಲ್ಯ = _this->gl_config.major_version;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *ಮೌಲ್ಯ = _this->gl_config.minor_version;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_CONTEXT_FLAGS:
    {
        *ಮೌಲ್ಯ = _this->gl_config.flags;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *ಮೌಲ್ಯ = _this->gl_config.profile_mask;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *ಮೌಲ್ಯ = _this->gl_config.share_with_current_context;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *ಮೌಲ್ಯ = _this->gl_config.framebuffer_srgb_capable;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_CONTEXT_NO_ERROR:
    {
        *ಮೌಲ್ಯ = _this->gl_config.no_error;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_EGL_PLATFORM:
    {
        *ಮೌಲ್ಯ = _this->gl_config.egl_platform;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪಕ್ಷ SDL_GL_FLOATBUFFERS:
    {
        ಯದಿ (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            ಭಙ್ಗ;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ಯದಿ (!glGetStringFunc) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (attachmentattrib && isAtLeastGL3((ಧ್ರುವ ವರ್ಣ *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        ಯದಿ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        ಯದಿ (glGetFramebufferAttachmentParameterivFunc) {
            ಯದಿ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ಯದಿ (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ಯದಿ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)ಮೌಲ್ಯ);
            } ಅನ್ಯಥಾ {
                *ಮೌಲ್ಯ = 0;
            }
            ಯದಿ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ಯದಿ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)ಮೌಲ್ಯ);
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    ಯದಿ (!glGetErrorFunc) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    error = glGetErrorFunc();
    ಯದಿ (error != GL_NO_ERROR) {
        ಯದಿ (error == GL_INVALID_ENUM) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } ಅನ್ಯಥಾ ಯದಿ (error == GL_INVALID_ಮೌಲ್ಯ) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ಯದಿ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *ಮೌಲ್ಯ = (*ಮೌಲ್ಯ == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ಪ್ರತ್ಯಾಗಮ true;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = ರಿಕ್ತ;
    CHECK_WINDOW_MAGIC(window, ರಿಕ್ತ);

    ಯದಿ (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

#ಯದಿ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ಪೂರ್ಣಾಙ್ಕ srgb_requested = -1;
    ಧ್ರುವ ವರ್ಣ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ಯದಿ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    ಯದಿ (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, ರಿಕ್ತ);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, ರಿಕ್ತ);
    }

#ಯದಿ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ಯದಿ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        ಯದಿ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ಯದಿ (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ಅನ್ಯಥಾ {
                supported = isAtLeastGL3((ಧ್ರುವ ವರ್ಣ *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ಯದಿ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ಪ್ರತ್ಯಾಗಮ ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }

    ಯದಿ (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಯದಿ (!context) {
        window = ರಿಕ್ತ;
    } ಅನ್ಯಥಾ ಯದಿ (window) {
        CHECK_WINDOW_MAGIC(window, false);

        ಯದಿ (!(window->flags & SDL_WINDOW_OPENGL)) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } ಅನ್ಯಥಾ ಯದಿ (!_this->gl_allow_no_surface) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    ಯದಿ (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, ರಿಕ್ತ);
        SDL_SetTLS(&_this->current_glctx_tls, context, ರಿಕ್ತ);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

SDL_Window *SDL_GL_GetCurrentWindow(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(ಶೂನ್ಯ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ EGL_NO_DISPLAY;
    }
    ಯದಿ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ಪ್ರತ್ಯಾಗಮ EGL_NO_DISPLAY;
    }
    ಪ್ರತ್ಯಾಗಮ _this->egl_data->egl_display;
#ಅನ್ಯಥಾ
    SDL_SetError("SDL was not built with EGL support");
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(ಶೂನ್ಯ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ _this->egl_data->egl_config;
#ಅನ್ಯಥಾ
    SDL_SetError("SDL was not built with EGL support");
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (_this->GL_GetEGLSurface) {
        ಪ್ರತ್ಯಾಗಮ _this->GL_GetEGLSurface(_this, window);
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
#ಅನ್ಯಥಾ
    SDL_SetError("SDL was not built with EGL support");
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
#endif
}

bool SDL_GL_SetSwapInterval(ಪೂರ್ಣಾಙ್ಕ interval)
{
    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    } ಅನ್ಯಥಾ ಯದಿ (SDL_GL_GetCurrentContext() == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No OpenGL context has been made current");
    } ಅನ್ಯಥಾ ಯದಿ (_this->GL_SetSwapInterval) {
        ಪ್ರತ್ಯಾಗಮ _this->GL_SetSwapInterval(_this, interval);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(ಪೂರ್ಣಾಙ್ಕ *interval)
{
    CHECK_PARAM(!interval) {
       ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("no video driver");
    } ಅನ್ಯಥಾ ಯದಿ (SDL_GL_GetCurrentContext() == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("no current context");
    } ಅನ್ಯಥಾ ಯದಿ (_this->GL_GetSwapInterval) {
        ಪ್ರತ್ಯಾಗಮ _this->GL_GetSwapInterval(_this, interval);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!(window->flags & SDL_WINDOW_OPENGL)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    ಯದಿ (SDL_GL_GetCurrentWindow() != window) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("The specified window has not been made current");
    }

    ಪ್ರತ್ಯಾಗಮ _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("context");
    }

    ಯದಿ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ರಿಕ್ತ, ರಿಕ್ತ);
    }

    ಪ್ರತ್ಯಾಗಮ _this->GL_DestroyContext(_this, context);
}

#ಯದಿ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ಸ್ಥಿರ ಶೂನ್ಯ Create_Mask_From_Color_ಕೀಲಿ_Or_Alpha(SDL_Surface *icon, Uint8 *mask, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    ವಿಕಲ್ಪ (SDL_BYTESPERPIXEL(icon->format)) {
    ಪಕ್ಷ 1:
        {
            Uint8 *pixels;
            ಪ್ರತಿ (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                ಪ್ರತಿ (x = 0; x < icon->w; ++x) {
                    ಯದಿ (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ 2:
        {
            Uint16 *pixels;
            ಪ್ರತಿ (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                ಪ್ರತಿ (x = 0; x < icon->w; ++x) {
                    ಯದಿ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ಅನ್ಯಥಾ ಯದಿ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        ಭಙ್ಗ;

    ಪಕ್ಷ 4:
        {
            Uint32 *pixels;
            ಪ್ರತಿ (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                ಪ್ರತಿ (x = 0; x < icon->w; ++x) {
                    ಯದಿ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ಅನ್ಯಥಾ ಯದಿ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        ಭಙ್ಗ;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
ಶೂನ್ಯ SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    ಯದಿ (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        ಯದಿ (mask == ರಿಕ್ತ) {
            ಪೂರ್ಣಾಙ್ಕ mask_len = icon->h * (icon->w + 7) / 8;
            ಪೂರ್ಣಾಙ್ಕ flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            ಯದಿ (mask == ರಿಕ್ತ) {
                ಪ್ರತ್ಯಾಗಮ;
            }
            SDL_memset(mask, ~0, mask_len);
            ಯದಿ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ಯದಿ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ಯದಿ (flags) {
                Create_Mask_From_Color_ಕೀಲಿ_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } ಅನ್ಯಥಾ {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_ಒಳಹರಿವು_Type SDL_Get_Text_ಒಳಹರಿವು_Type(SDL_PropertiesID props)
{
    ಪ್ರತ್ಯಾಗಮ (SDL_Text_ಒಳಹರಿವು_Type)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_TEXTINPUT_TYPE_ಸಂಖ್ಯೆ, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_ಒಳಹರಿವು_Capitalization(SDL_PropertiesID props)
{
    ಯದಿ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ಸಂಖ್ಯೆ)) {
        ಪ್ರತ್ಯಾಗಮ (SDL_Capitalization)SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ಸಂಖ್ಯೆ, SDL_CAPITALIZE_NONE);
    }

    ವಿಕಲ್ಪ (SDL_Get_Text_ಒಳಹರಿವು_Type(props)) {
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT:
        ಪ್ರತ್ಯಾಗಮ SDL_CAPITALIZE_SENTENCES;
    ಪಕ್ಷ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ಪ್ರತ್ಯಾಗಮ SDL_CAPITALIZE_ಪದಗಳು;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_ಒಳಹರಿವು_Autocorrect(SDL_PropertiesID props)
{
    ಪ್ರತ್ಯಾಗಮ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_ಒಳಹರಿವು_Multiline(SDL_PropertiesID props)
{
    ಯದಿ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ಪ್ರತ್ಯಾಗಮ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ಯದಿ (SDL_GetHintBoolean(SDL_HINT_RETURN_ಕೀಲಿ_HIDES_IME, false)) {
        ಪ್ರತ್ಯಾಗಮ false;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ true;
    }
}

ಸ್ಥಿರ bool AutoShowingScreenKeyboard(ಶೂನ್ಯ)
{
    ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ಯದಿ (!hint) {
        // This hint is currently only used by the X11 video driver
        ಯದಿ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ಯದಿ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ಪ್ರತ್ಯಾಗಮ true;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ false;
    }
}

bool SDL_Start_Text_ಒಳಹರಿವು(SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Start_Text_ಒಳಹರಿವು_With_Properties(window, 0);
}

bool SDL_Start_Text_ಒಳಹರಿವು_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (window->text_ಒಳಹರಿವು_props) {
        SDL_DestroyProperties(window->text_ಒಳಹರಿವು_props);
        window->text_ಒಳಹರಿವು_props = 0;
    }

    ಯದಿ (props) {
        window->text_ಒಳಹರಿವು_props = SDL_CreateProperties();
        ಯದಿ (!window->text_ಒಳಹರಿವು_props) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        ಯದಿ (!SDL_CopyProperties(props, window->text_ಒಳಹರಿವು_props)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }

    ಯದಿ (_this->Set_Text_ಒಳಹರಿವು_Properties) {
        _this->Set_Text_ಒಳಹರಿವು_Properties(_this, window, props);
    }

    ಯದಿ (!window->text_ಒಳಹರಿವು_active) {
        // Start the text input system
        ಯದಿ (_this->Start_Text_ಒಳಹರಿವು) {
            ಯದಿ (!_this->Start_Text_ಒಳಹರಿವು(_this, window, props)) {
                ಪ್ರತ್ಯಾಗಮ false;
            }
        }
        window->text_ಒಳಹರಿವು_active = true;
    }

    // Show the on-screen keyboard, if desired
    ಯದಿ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        ಯದಿ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_Text_ಒಳಹರಿವು_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಪ್ರತ್ಯಾಗಮ window->text_ಒಳಹರಿವು_active;
}

bool SDL_Stop_Text_ಒಳಹರಿವು(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (window->text_ಒಳಹರಿವು_active) {
        // Stop the text input system
        ಯದಿ (_this->Stop_Text_ಒಳಹರಿವು) {
            _this->Stop_Text_ಒಳಹರಿವು(_this, window);
        }
        window->text_ಒಳಹರಿವು_active = false;
    }

    // Hide the on-screen keyboard, if desired
    ಯದಿ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        ಯದಿ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_Set_Text_ಒಳಹರಿವು_Area(SDL_Window *window, ಧ್ರುವ SDL_Rect *rect, ಪೂರ್ಣಾಙ್ಕ cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (rect) {
        SDL_copyp(&window->text_ಒಳಹರಿವು_rect, rect);
        window->text_ಒಳಹರಿವು_cursor = cursor;
    } ಅನ್ಯಥಾ {
        SDL_zero(window->text_ಒಳಹರಿವು_rect);
        window->text_ಒಳಹರಿವು_cursor = 0;
    }

    ಯದಿ (_this && _this->Update_Text_ಒಳಹರಿವು_Area) {
        ಯದಿ (!_this->Update_Text_ಒಳಹರಿವು_Area(_this, window)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_Get_Text_ಒಳಹರಿವು_Area(SDL_Window *window, SDL_Rect *rect, ಪೂರ್ಣಾಙ್ಕ *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (rect) {
        SDL_copyp(rect, &window->text_ಒಳಹರಿವು_rect);
    }
    ಯದಿ (cursor) {
        *cursor = window->text_ಒಳಹರಿವು_cursor;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (_this->ClearComposition) {
        ಪ್ರತ್ಯಾಗಮ _this->ClearComposition(_this, window);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool SDL_HasScreenKeyboardSupport(ಶೂನ್ಯ)
{
    ಯದಿ (_this && _this->HasScreenKeyboardSupport) {
        ಪ್ರತ್ಯಾಗಮ _this->HasScreenKeyboardSupport(_this);
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಪ್ರತ್ಯಾಗಮ _this->screen_keyboard_shown;
}

ಶೂನ್ಯ SDL_SendScreenKeyboardShown(ಶೂನ್ಯ)
{
    ಯದಿ (!_this || _this->screen_keyboard_shown) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    _this->screen_keyboard_shown = true;

    ಯದಿ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ತಳ್ಳು_Event(&event);
    }
}

ಶೂನ್ಯ SDL_SendScreenKeyboardHidden(ಶೂನ್ಯ)
{
    ಯದಿ (!_this || !_this->screen_keyboard_shown) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    _this->screen_keyboard_shown = false;

    ಯದಿ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ತಳ್ಳು_Event(&event);
    }
}

ಪೂರ್ಣಾಙ್ಕ SDL_Get_Message_Box_ಎಣಿಕೆ(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ SDL_GetAtomicInt(&SDL_messagebox_ಎಣಿಕೆ);
}

bool SDL_ShowMessageBox(ಧ್ರುವ SDL_MessageBoxData *messageboxdata, ಪೂರ್ಣಾಙ್ಕ *buttonID)
{
    ಪೂರ್ಣಾಙ್ಕ dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    ವರ್ಣ *titlecpy = ರಿಕ್ತ;
    ವರ್ಣ *msgcpy = ರಿಕ್ತ;
    ಯದಿ (messageboxdata->title) {
        ಧ್ರುವ size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(ವರ್ಣ, slen, &titleisstack);
        ಯದಿ (!titlecpy) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ಯದಿ (messageboxdata->message) {
        ಧ್ರುವ size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(ವರ್ಣ, slen, &msgisstack);
        ಯದಿ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ಪ್ರತ್ಯಾಗಮ false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (ಶೂನ್ಯ)SDL_AtomicIncRef(&SDL_messagebox_ಎಣಿಕೆ);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    ಯದಿ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, ಪರಿಮಾಣ(*messageboxdata));
    mbdata.title = titlecpy;
    ಯದಿ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    ಯದಿ (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ಯದಿ (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } ಅನ್ಯಥಾ {
        // It's completely fine to call this function before video is initialized
        ಧ್ರುವ ವರ್ಣ *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ಯದಿ (driver_name && *driver_name != 0) {
            ಧ್ರುವ ವರ್ಣ *driver_attempt = driver_name;
            ಯಾವತ್ (driver_attempt && (*driver_attempt != 0) && !result) {
                ಧ್ರುವ ವರ್ಣ *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; bootstrap[i]; ++i) {
                    ಯದಿ (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ಯದಿ (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        ಭಙ್ಗ;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ರಿಕ್ತ;
            }
        } ಅನ್ಯಥಾ {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; bootstrap[i]; ++i) {
                ಯದಿ (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    ಭಙ್ಗ;
                }
            }
        }
    }

    ಯದಿ (!result) {
        ಧ್ರುವ ವರ್ಣ *error = SDL_GetError();

        ಯದಿ (!*error) {
            SDL_SetError("No message system available");
        }
    } ಅನ್ಯಥಾ {
        SDL_ClearError();
    }

    (ಶೂನ್ಯ)SDL_AtomicDecRef(&SDL_messagebox_ಎಣಿಕೆ);

    ಯದಿ (current_window) {
        SDL_RaiseWindow(current_window);
    }

    ಯದಿ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ಪ್ರತ್ಯಾಗಮ result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ಧ್ರುವ ವರ್ಣ *title, ಧ್ರುವ ವರ್ಣ *message, SDL_Window *window)
{
#ಯದಿ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_ಬಲ;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_ಬಲ = gsp_Has_Gpu_ಬಲ();
    ಯದಿ (!has_Gpu_ಬಲ)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    ಯದಿ (!has_Gpu_ಬಲ)
        gfxExit();

    ಪ್ರತ್ಯಾಗಮ true;
#ಅನ್ಯಥಾ
    SDL_MessageBoxData data;
    SDL_MessageBoxButtonData button;

    SDL_zero(data);
    data.flags = flags;
    data.title = title;
    data.message = message;
    data.numbuttons = 1;
    data.buttons = &button;
    data.window = window;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.text = "OK";

    ಪ್ರತ್ಯಾಗಮ SDL_ShowMessageBox(&data, ರಿಕ್ತ);
#endif
}

bool SDL_ShouldAllowTopmost(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ಯದಿ (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ಪ್ರತ್ಯಾಗಮ true;
    }

    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, ಶೂನ್ಯ *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!_this->SetWindowHitTest) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    ಪ್ರತ್ಯಾಗಮ _this->SetWindowHitTest(window, callback != ರಿಕ್ತ);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    ಯದಿ (!props) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ಯದಿ (!surface) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        surface = ರಿಕ್ತ;
    }

    ಯದಿ (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (_this->UpdateWindowShape) {
        ಯದಿ (!_this->UpdateWindowShape(_this, window, surface)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

/*
 * Functions used by iOS application delegates
 */
ಶೂನ್ಯ SDL_OnApplicationWillTerminate(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

ಶೂನ್ಯ SDL_OnApplicationDidReceiveMemoryWarning(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_ಕೆಳಗಿನ_MEMORY);
}

ಶೂನ್ಯ SDL_OnApplicationWillEnterBackground(ಶೂನ್ಯ)
{
    ಯದಿ (_this) {
        SDL_Window *window;
        ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(ರಿಕ್ತ);
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

    ಯದಿ (_this) {
        SDL_Window *window;
        ಪ್ರತಿ (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ಧ್ರುವ ವರ್ಣ *path)
{
    bool result;

    ಯದಿ (!_this) {
        ಪ್ರತ್ಯಾಗಮ SDL_UninitializedVideo();
    }
    ಯದಿ (_this->vulkan_config.loader_loaded) {
        ಯದಿ (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } ಅನ್ಯಥಾ {
        ಯದಿ (!_this->Vulkan_LoadLibrary) {
            ಪ್ರತ್ಯಾಗಮ SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    ಯದಿ (result) {
        _this->vulkan_config.loader_loaded++;
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

ಶೂನ್ಯ SDL_Vulkan_UnloadLibrary(ಶೂನ್ಯ)
{
    ಯದಿ (!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ;
    }
    ಯದಿ (_this->vulkan_config.loader_loaded > 0) {
        ಯದಿ (--_this->vulkan_config.loader_loaded > 0) {
            ಪ್ರತ್ಯಾಗಮ;
        }
        ಯದಿ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

ವರ್ಣ ಧ್ರುವ * ಧ್ರುವ *SDL_Vulkan_GetInstanceExtensions(Uint32 *ಎಣಿಕೆ)
{
    Uint32 tmpcount = 0;
    ಯದಿ (!ಎಣಿಕೆ) {
        ಎಣಿಕೆ = &tmpcount;
    }

    ಯದಿ (!_this->Vulkan_GetInstanceExtensions) {
        *ಎಣಿಕೆ = 0;
        SDL_Unsupported();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ _this->Vulkan_GetInstanceExtensions(_this, ಎಣಿಕೆ);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    ಯದಿ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ಪ್ರತ್ಯಾಗಮ false;
    }

    CHECK_PARAM(!instance) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ಪ್ರತ್ಯಾಗಮ SDL_InvalidParamError("surface");
    }

    ಯದಿ (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ಯದಿ (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        ಯದಿ (SDL_Vulkan_LoadLibrary(ರಿಕ್ತ)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("failed to load Vulkan library");
        }
    }

    ಪ್ರತ್ಯಾಗಮ _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

ಶೂನ್ಯ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ಧ್ರುವ ಸಂರಚನಾ VkAllocationCallbacks *allocator)
{
    ಯದಿ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ಪ್ರತ್ಯಾಗಮ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ಪ್ರತ್ಯಾಗಮ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (_this->Vulkan_GetPresentationSupport) {
        ಪ್ರತ್ಯಾಗಮ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ಪ್ರತ್ಯಾಗಮ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ರಿಕ್ತ);

    ಯದಿ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        ಯದಿ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ಯದಿ (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    ಪ್ರತ್ಯಾಗಮ _this->Metal_CreateView(_this, window);
}

ಶೂನ್ಯ SDL_Metal_DestroyView(SDL_MetalView view)
{
    ಯದಿ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

ಶೂನ್ಯ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ಯದಿ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        ಪ್ರತ್ಯಾಗಮ _this->Metal_GetLayer(_this, view);
    } ಅನ್ಯಥಾ {
        SDL_SetError("Metal is not supported.");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

#ಯದಿ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ಧ್ರುವ ವರ್ಣ *SDL_GetCSSCursorName(SDL_SystemCursor id, ಧ್ರುವ ವರ್ಣ **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    ವಿಕಲ್ಪ (id) {
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_DEFAULT:
        ಪ್ರತ್ಯಾಗಮ "default";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_TEXT:
        ಪ್ರತ್ಯಾಗಮ "text";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_WAIT:
        ಪ್ರತ್ಯಾಗಮ "wait";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CROSSHAIR:
        ಪ್ರತ್ಯಾಗಮ "crosshair";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_PROGRESS:
        ಪ್ರತ್ಯಾಗಮ "progress";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ಯದಿ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ಪ್ರತ್ಯಾಗಮ "nwse-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ಯದಿ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ಪ್ರತ್ಯಾಗಮ "nesw-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_EW_RESIZE:
        ಯದಿ (fallback_name) {
            *fallback_name = "col-resize";
        }
        ಪ್ರತ್ಯಾಗಮ "ew-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NS_RESIZE:
        ಯದಿ (fallback_name) {
            *fallback_name = "row-resize";
        }
        ಪ್ರತ್ಯಾಗಮ "ns-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_MOVE:
        ಯದಿ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ಪ್ರತ್ಯಾಗಮ "move";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ಪ್ರತ್ಯಾಗಮ "not-allowed";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_POINTER:
        ಪ್ರತ್ಯಾಗಮ "pointer";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NW_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "nw-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_N_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "n-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NE_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "ne-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_E_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "e-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SE_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "se-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_S_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "s-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SW_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "sw-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_W_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "w-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ಪ್ರತ್ಯಾಗಮ "context-menu";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_HELP:
        ಪ್ರತ್ಯಾಗಮ "help";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CELL:
        ಪ್ರತ್ಯಾಗಮ "cell";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ಪ್ರತ್ಯಾಗಮ "vertical-text";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALIAS:
        ಪ್ರತ್ಯಾಗಮ "alias";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COPY:
        ಪ್ರತ್ಯಾಗಮ "copy";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NO_DROP:
        ಪ್ರತ್ಯಾಗಮ "no-drop";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRAB:
        ಪ್ರತ್ಯಾಗಮ "grab";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRABBING:
        ಪ್ರತ್ಯಾಗಮ "grabbing";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COL_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "col-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ಪ್ರತ್ಯಾಗಮ "row-resize";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ಯದಿ (fallback_name) {
            *fallback_name = "move";
        }
        ಪ್ರತ್ಯಾಗಮ "all-scroll";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_IN:
        ಪ್ರತ್ಯಾಗಮ "zoom-in";

    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ಪ್ರತ್ಯಾಗಮ "zoom-out";

    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ "default";
    }
}
#endif

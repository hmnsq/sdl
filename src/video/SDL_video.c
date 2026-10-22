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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

// The high-level video driver subsystem

#ଅନ୍ତର୍ଭାଵ "SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_clipboard_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_egl_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_surface_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_pixels_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_rect_c.h"
#ଅନ୍ତର୍ଭାଵ "SDL_video_c.h"
#ଅନ୍ତର୍ଭାଵ "../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_hints_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_properties_c.h"
#ଅନ୍ତର୍ଭାଵ "../timer/SDL_timer_c.h"
#ଅନ୍ତର୍ଭାଵ "../camera/SDL_camera_c.h"
#ଅନ୍ତର୍ଭାଵ "../render/SDL_sysrender.h"
#ଅନ୍ତର୍ଭାଵ "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#ଯଦି defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ଯଦି defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ଅନ୍ତର୍ଭାଵ <SDL3/SDL_opengles2.h>
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
#ଅନ୍ତର୍ଭାଵ <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#ଅନ୍ତର୍ଭାଵ <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ସ୍ଥିର VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_ନିବେଶ_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    ଖାଲି
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        ଫେରନ୍ତୁ result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ଫେରନ୍ତୁ result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        ଫେରନ୍ତୁ result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ଫେରନ୍ତୁ result;                                                  \
    }

#ଯଦି defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
ବାହ୍ୟ bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
ବାହ୍ୟ bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
ବାହ୍ୟ bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
ବାହ୍ୟ bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
ବାହ୍ୟ ଶୂନ୍ୟ SDL_UpdateLifecycleObserver(ଶୂନ୍ୟ);
#endif

ସ୍ଥିର ଶୂନ୍ୟ SDL_CheckWindowDisplayChanged(SDL_Window *window);
ସ୍ଥିର ଶୂନ୍ୟ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
ସ୍ଥିର ଶୂନ୍ୟ SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
ସ୍ଥିର bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    ଯଦି (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ସ୍ଥିର bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ସ୍ଥିର bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ସ୍ଥିର bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ସ୍ଥିର bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ସ୍ଥିର bool syncHint;

ସ୍ଥିର ଶୂନ୍ୟ SDL_SyncHintWatcher(ଶୂନ୍ୟ *userdata, ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ ଅକ୍ଷର *old_ମୂଲ୍ୟ, ଅଚଳ ଅକ୍ଷର *new_ମୂଲ୍ୟ)
{
    syncHint = SDL_GetStringBoolean(new_ମୂଲ୍ୟ, false);
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_SyncIfRequired(SDL_Window *window)
{
    ଯଦି (syncHint) {
        SDL_SyncWindow(window);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    ଯଦି (window->parent) {
        ଯଦି (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        ଯଦି (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } ଅନ୍ୟଥା {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = ଖାଲି;
    }

    ଯଦି (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        ଯଦି (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    ଶୂନ୍ୟ *pixels;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bytes_per_pixel;
} SDL_WindowTextureData;

ସ୍ଥିର Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#ଯଦି (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ଯଦି (_this->GL_CreateContext) {
        ଫେରନ୍ତୁ SDL_WINDOW_OPENGL;
    }
#endif
#ଯଦି defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ଯଦି (_this->Metal_CreateView) {
        ଫେରନ୍ତୁ SDL_WINDOW_METAL;
    }
#endif
#ଯଦି defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ଯଦି (SDL_strcmp(_this->name, "openvr") == 0) {
        ଫେରନ୍ତୁ SDL_WINDOW_OPENGL;
    }
#endif
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ଶୂନ୍ୟ **pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ଖାଲି);
    ଅଚଳ bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;
    ଅଚଳ SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    ଯଦି (!data) {
        SDL_Renderer *renderer = ଖାଲି;
        ଅଚଳ ଅକ୍ଷର *render_driver = ଖାଲି;

        // See if there's a render driver being requested
        ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ଯଦି (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ଯଦି (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ଯଦି (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = ଖାଲି;
        }

        ଅକ୍ଷର *render_driver_copy = ଖାଲି;
        ଯଦି (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ଯଦି (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                ଅକ୍ଷର *prev = render_driver_copy;
                ଅକ୍ଷର *ptr = prev;
                ଯେତେବେଳେ ((ptr = SDL_strchr(ptr, ',')) != ଖାଲି) {
                    *ptr = '\0';
                    ଅଚଳ bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ଯଦି (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } ଅନ୍ୟଥା {
                        ptr++;
                        prev = ptr;
                    }
                }

                ଯଦି (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ଯଦି (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            ଯଦି (!renderer) {
                // The error for this specific renderer has already been set
                ଫେରନ୍ତୁ false;
            }
        } ଅନ୍ୟଥା {
            SDL_assert(render_driver_copy == ଖାଲି);
            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା total = SDL_Get_ଅଙ୍କ_Render_Drivers();
            ପାଇଁ (i = 0; i < total; ++i) {
                ଅଚଳ ଅକ୍ଷର *name = SDL_GetRenderDriver(i);
                ଯଦି (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    ଯଦି (renderer) {
                        ଭାଙ୍ଗ; // this will work.
                    }
                }
            }
            ଯଦି (!renderer) {
                ଫେରନ୍ତୁ SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ଖାଲି); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, ଆକାର(*data));
        ଯଦି (!data) {
            SDL_DestroyRenderer(renderer);
            ଫେରନ୍ତୁ false;
        }
        ଯଦି (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            ଫେରନ୍ତୁ false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ଅଚଳ SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, ଖାଲି);
    ଯଦି (!texture_formats) {
        ଫେରନ୍ତୁ false;
    }

    // Free any old texture and pixel data
    ଯଦି (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = ଖାଲି;
    }
    SDL_free(data->pixels);
    data->pixels = ଖାଲି;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    ପାଇଁ (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ଯଦି (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            ଭାଙ୍ଗ;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    ଯଦି (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ଫେରନ୍ତୁ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ଅଚଳ size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ଯଦି (!data->pixels) {
            ଫେରନ୍ତୁ false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, ଖାଲି);

    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ଖାଲି);
    ଯଦି (!data) {
        ଫେରନ୍ତୁ false;
    }
    ଯଦି (!data->renderer) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ SDL_SetRenderVSync(data->renderer, vsync);
}

ସ୍ଥିର bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ଖାଲି);
    ଯଦି (!data) {
        ଫେରନ୍ତୁ false;
    }
    ଯଦି (!data->renderer) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ SDL_GetRenderVSync(data->renderer, vsync);
}

ସ୍ଥିର bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ଅଚଳ SDL_Rect *rects, ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    ଶୂନ୍ୟ *src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ଖାଲି);
    ଯଦି (!data || !data->texture) {
        ଫେରନ୍ତୁ SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ଯଦି (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (ଶୂନ୍ୟ *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        ଯଦି (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            ଫେରନ୍ତୁ false;
        }

        ଯଦି (!SDL_RenderTexture(data->renderer, data->texture, ଖାଲି, ଖାଲି)) {
            ଫେରନ୍ତୁ false;
        }

        SDL_RenderPresent(data->renderer);
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ଯଦି (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ଖାଲି);

        ଯଦି (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        ଯଦି (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

ସ୍ଥିର SDL_VideoDevice *_this = ଖାଲି;
ସ୍ଥିର SDL_AtomicInt SDL_messagebox_ଗଣନା;

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDLCALL cmpmodes(ଅଚଳ ଶୂନ୍ୟ *A, ଅଚଳ ଶୂନ୍ୟ *B)
{
    ଅଚଳ SDL_DisplayMode *a = (ଅଚଳ SDL_DisplayMode *)A;
    ଅଚଳ SDL_DisplayMode *b = (ଅଚଳ SDL_DisplayMode *)B;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା a_refresh_rate = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(a->refresh_rate * 100);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା b_refresh_rate = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(b->refresh_rate * 100);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା a_pixel_density = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(a->pixel_density * 100);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା b_pixel_density = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(b->pixel_density * 100);

    ଯଦି (a->w != b->w) {
        ଫେରନ୍ତୁ b->w - a->w;
    } ଅନ୍ୟଥା ଯଦି (a->h != b->h) {
        ଫେରନ୍ତୁ b->h - a->h;
    } ଅନ୍ୟଥା ଯଦି (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ଫେରନ୍ତୁ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ଅନ୍ୟଥା ଯଦି (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ଫେରନ୍ତୁ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ଅନ୍ୟଥା ଯଦି (a_refresh_rate != b_refresh_rate) {
        ଫେରନ୍ତୁ b_refresh_rate - a_refresh_rate;
    } ଅନ୍ୟଥା ଯଦି (a_pixel_density != b_pixel_density) {
        ଫେରନ୍ତୁ a_pixel_density - b_pixel_density;
    }
    ଫେରନ୍ତୁ 0;
}

bool SDL_UninitializedVideo(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ସ୍ଥିର ଅଚଳ VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_Get_ଅଙ୍କ_Video_Drivers(ଶୂନ୍ୟ)
{
    ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_drivers = -1;

    ଯଦି (ଅଙ୍କ_drivers >= 0) {
        ଫେରନ୍ତୁ ଅଙ୍କ_drivers;
    }

    ଅଙ୍କ_drivers = 0;

    // Build a list of unique video drivers.
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; bootstrap[i] != ଖାଲି; ++i) {
        bool duplicate = false;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < i; ++j) {
            ଯଦି (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                ଭାଙ୍ଗ;
            }
        }

        ଯଦି (!duplicate) {
            deduped_bootstrap[ଅଙ୍କ_drivers++] = bootstrap[i];
        }
    }

    ଫେରନ୍ତୁ ଅଙ୍କ_drivers;
}

ଅଚଳ ଅକ୍ଷର *SDL_GetVideoDriver(ପୂର୍ଣ୍ଣସଂଖ୍ୟା index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_ଅଙ୍କ_Video_Drivers()) {
        SDL_InvalidParamError("index");
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ଅଚଳ ଅକ୍ଷର *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;

    // Check to make sure we don't overwrite '_this'
    ଯଦି (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ଯଦି (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        ଯାଅ pre_driver_error;
    }
    init_events = true;
    ଯଦି (!SDL_InitKeyboard()) {
        ଯାଅ pre_driver_error;
    }
    init_keyboard = true;
    ଯଦି (!SDL_PreInitMouse()) {
        ଯାଅ pre_driver_error;
    }
    init_mouse = true;
    ଯଦି (!SDL_InitTouch()) {
        ଯାଅ pre_driver_error;
    }
    init_touch = true;
    ଯଦି (!SDL_InitPen()) {
        ଯାଅ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ଖାଲି;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ଯଦି (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    ଯଦି (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ଯଦି (driver_name && *driver_name != 0) {
        ଅଚଳ ଅକ୍ଷର *driver_attempt = driver_name;
        ଯେତେବେଳେ (driver_attempt && *driver_attempt != 0 && !video) {
            ଅଚଳ ଅକ୍ଷର *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            ପାଇଁ (i = 0; bootstrap[i]; ++i) {
                ଯଦି (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ଯଦି (video) {
                        ଭାଙ୍ଗ;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ଖାଲି;
        }
    } ଅନ୍ୟଥା {
        ପାଇଁ (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ଯଦି (video) {
                ଭାଙ୍ଗ;
            }
        }
    }
    ଯଦି (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ଅନ୍ୟଥା {
        ଯଦି (driver_name) {
            SDL_SetError("%s not available", driver_name);
            ଯାଅ pre_driver_error;
        }
        SDL_SetError("No available video device");
        ଯାଅ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ଖାଲି;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    ଯଦି (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ଫେରନ୍ତୁ false;
    }

    // Make sure some displays were added
    ଯଦି (_this->ଅଙ୍କ_displays == 0) {
        SDL_QuitVideo();
        ଫେରନ୍ତୁ SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, ଖାଲି);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ଯଦି (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ଫେରନ୍ତୁ true;

pre_driver_error:
    SDL_assert(_this == ଖାଲି);
    ଯଦି (init_pen) {
        SDL_QuitPen();
    }
    ଯଦି (init_touch) {
        SDL_QuitTouch();
    }
    ଯଦି (init_mouse) {
        SDL_QuitMouse();
    }
    ଯଦି (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ଯଦି (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ଫେରନ୍ତୁ false;
}

ଅଚଳ ଅକ୍ଷର *SDL_GetCurrentVideoDriver(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ _this;
}

bool SDL_OnVideoThread(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

ଶୂନ୍ୟ SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    ଯଦି (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(ଶୂନ୍ୟ)
{
    ଯଦି (_this) {
        ଫେରନ୍ତୁ _this->system_theme;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ଶୂନ୍ୟ SDL_UpdateDesktopBounds(ଶୂନ୍ୟ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ଖାଲି);
    ଯଦି (displays) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ଯଦି (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ଯଦି (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ଅନ୍ୟଥା {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    ଯଦି (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    ଯଦି (mode->refresh_rate_numerator > 0) {
        ଯଦି (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (ଦଶମିକ)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } ଅନ୍ୟଥା {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ଅଚଳ SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ଯଦି (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, ଆକାର(display.desktop_mode));
    }
    ଫେରନ୍ତୁ SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ଅଚଳ SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(ଆକାର(*new_display));
    ଯଦି (!new_display) {
        ଫେରନ୍ତୁ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->ଅଙ୍କ_displays + 1) * ଆକାର(*displays));
    ଯଦି (!displays) {
        SDL_free(new_display);
        ଫେରନ୍ତୁ 0;
    }
    _this->displays = displays;
    _this->displays[_this->ଅଙ୍କ_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ଯଦି (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ଅନ୍ୟଥା {
        ଅକ୍ଷର name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ଯଦି (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    ପାଇଁ (i = 0; i < new_display->ଅଙ୍କ_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    ଯଦି (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ଫେରନ୍ତୁ id;
}

ଶୂନ୍ୟ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    ପାଇଁ (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

ଶୂନ୍ୟ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

ଶୂନ୍ୟ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_index = SDL_GetDisplayIndex(displayID);
    ଯଦି (display_index < 0) {
        ଫେରନ୍ତୁ;
    }

    display = _this->displays[display_index];

    ଯଦି (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = ଖାଲି;
    SDL_free(display->internal);
    display->internal = ଖାଲି;
    SDL_free(display);

    ଯଦି (display_index < (_this->ଅଙ୍କ_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->ଅଙ୍କ_displays - display_index - 1) * ଆକାର(_this->displays[display_index]));
    }
    --_this->ଅଙ୍କ_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଗଣନା_2)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    SDL_DisplayID *displays;

    ଯଦି (!_this) {
        ଯଦି (ଗଣନା_2) {
            *ଗଣନା_2 = 0;
        }

        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->ଅଙ୍କ_displays + 1) * ଆକାର(*displays));
    ଯଦି (displays) {
        ଯଦି (ଗଣନା_2) {
            *ଗଣନା_2 = _this->ଅଙ୍କ_displays;
        }

        ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ଅନ୍ୟଥା {
        ଯଦି (ଗଣନା_2) {
            *ଗଣନା_2 = 0;
        }
    }
    ଫେରନ୍ତୁ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    ଯଦି (display_index < 0) {
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ _this->displays[display_index];
}

ସ୍ଥିର SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    ଯଦି (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    ଫେରନ୍ତୁ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ଫେରନ୍ତୁ SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(ଶୂନ୍ୟ)
{
    ଯଦି (!_this || _this->ଅଙ୍କ_displays == 0) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ 0;
    }
    ଫେରନ୍ତୁ _this->displays[0]->id;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_index;

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ -1;
    }

    ପାଇଁ (display_index = 0; display_index < _this->ଅଙ୍କ_displays; ++display_index) {
        ଯଦି (displayID == _this->displays[display_index]->id) {
            ଫେରନ୍ତୁ display_index;
        }
    }
    SDL_SetError("Invalid display");
    ଫେରନ୍ତୁ -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ଖାଲି);

    ଫେରନ୍ତୁ display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ଫେରନ୍ତୁ SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ଯଦି (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ଫେରନ୍ତୁ display->props;
}

ଅଚଳ ଅକ୍ଷର *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ଖାଲି);

    ଫେରନ୍ତୁ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("rect");
    }

    ଯଦି (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ଯଦି (_this->GetDisplayBounds(_this, display, rect)) {
            ଫେରନ୍ତୁ true;
        }
    }

    // Assume that the displays are left to right
    ଯଦି (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ଅନ୍ୟଥା {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ଫେରନ୍ତୁ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("rect");
    }

    ଯଦି (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ଯଦି (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ଫେରନ୍ତୁ true;
        }
    }

    // Oh well, just give the entire display bounds.
    ଫେରନ୍ତୁ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ଯଦି (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ଫେରନ୍ତୁ display->natural_orientation;
    } ଅନ୍ୟଥା {
        // Default to landscape if the driver hasn't set it
        ଫେରନ୍ତୁ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ଯଦି (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ଫେରନ୍ତୁ display->current_orientation;
    } ଅନ୍ୟଥା {
        // Default to landscape if the driver hasn't set it
        ଫେରନ୍ତୁ SDL_ORIENTATION_LANDSCAPE;
    }
}

ଶୂନ୍ୟ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ଦଶମିକ scale)
{
    ଯଦି (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        ପାଇଁ (window = _this->windows; window; window = window->next) {
            ଯଦି (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

ଦଶମିକ SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ଫେରନ୍ତୁ display->content_scale;
}

ଶୂନ୍ୟ SDL_SetWindowHDRProperties(SDL_Window *window, ଅଚଳ SDL_HDROutputProperties *HDR, bool send_event)
{
    ଅଚଳ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ଯଦି (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        ଯଦି (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

ଶୂନ୍ୟ SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ଅଚଳ SDL_HDROutputProperties *HDR)
{
    ଅଚଳ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ଅଚଳ bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	ଯଦି (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ଯଦି (changed && !SDL_DriverSendsHDRChanges(_this)) {
        ପାଇଁ (SDL_Window *w = display->device->windows; w; w = w->next) {
            ଯଦି (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ଯଦି (display->ଅଙ୍କ_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ସ୍ଥିର ଅଚଳ SDL_DisplayMode *SDL_GetFullscreenModeMatch(ଅଚଳ SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    ଯଦି (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_memcpy(&fullscreen_mode, mode, ଆକାର(fullscreen_mode));
    ଯଦି (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = ଖାଲି;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    ଯଦି (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ଯଦି (!mode) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < display->ଅଙ୍କ_fullscreen_modes; ++i) {
                ଯଦି (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], ଆକାର(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    ଭାଙ୍ଗ;
                }
            }
        }

        // Search for a mode with the same characteristics
        ଯଦି (!mode) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < display->ଅଙ୍କ_fullscreen_modes; ++i) {
                ଯଦି (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    ଭାଙ୍ଗ;
                }
            }
        }
    }
    ଫେରନ୍ତୁ mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ଅଚଳ SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, ଆକାର(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->ଅଙ୍କ_fullscreen_modes;
    ପାଇଁ (i = 0; i < nmodes; ++i) {
        ଯଦି (cmpmodes(&new_mode, &modes[i]) == 0) {
            ଫେରନ୍ତୁ false;
        }
    }

    // Go ahead and add the new mode
    ଯଦି (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * ଆକାର(*modes));
        ଯଦି (!modes) {
            ଫେରନ୍ତୁ false;
        }

        ଯଦି (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * ଆକାର(*modes));
            ପାଇଁ (i = 0; i < nmodes; ++i) {
                ଯଦି (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->ଅଙ୍କ_fullscreen_modes++], &new_mode, ଆକାର(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->ଅଙ୍କ_fullscreen_modes,
              ଆକାର(SDL_DisplayMode), cmpmodes);

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = display->ଅଙ୍କ_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = ଖାଲି;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ଖାଲି;
    display->ଅଙ୍କ_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଗଣନା_2)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ଯଦି (ଗଣନା_2) {
        *ଗଣନା_2 = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ଖାଲି);

    SDL_UpdateFullscreenDisplayModes(display);

    ଅଙ୍କ_modes = display->ଅଙ୍କ_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((ଅଙ୍କ_modes + 1) * ଆକାର(*result) + ଅଙ୍କ_modes * ଆକାର(**result));
    ଯଦି (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((ଅଙ୍କ_modes + 1) * ଆକାର(*result)));
        ଯଦି (ଅଙ୍କ_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, ଅଙ୍କ_modes * ଆକାର(*modes));
        }
        ପାଇଁ (i = 0; i < ଅଙ୍କ_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = ଖାଲି;

        ଯଦି (ଗଣନା_2) {
            *ଗଣନା_2 = ଅଙ୍କ_modes;
        }
    } ଅନ୍ୟଥା {
        ଯଦି (ଗଣନା_2) {
            *ଗଣନା_2 = 0;
        }
    }
    ଫେରନ୍ତୁ result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ଦଶମିକ refresh_rate, bool include_ଉପର_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ଅଚଳ SDL_DisplayMode *mode, *closest = ଖାଲି;
    ଦଶମିକ aspect_ratio;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    ଯଦି (h > 0) {
        aspect_ratio = (ଦଶମିକ)w / h;
    } ଅନ୍ୟଥା {
        aspect_ratio = 1.0f;
    }

    ଯଦି (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    ପାଇଁ (i = 0; i < display->ଅଙ୍କ_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        ଯଦି (w > mode->w) {
            // Out of sorted modes large enough here
            ଭାଙ୍ଗ;
        }
        ଯଦି (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            ଜାରି;
        }
        ଯଦି (mode->pixel_density > 1.0f && !include_ଉପର_density_modes) {
            ଜାରି;
        }
        ଯଦି (closest) {
            ଦଶମିକ current_aspect_ratio = (ଦଶମିକ)mode->w / mode->h;
            ଦଶମିକ closest_aspect_ratio = (ଦଶମିକ)closest->w / closest->h;
            ଯଦି (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                ଜାରି;
            }

            ଯଦି (mode->w == closest->w && mode->h == closest->h) {
                ଯଦି (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    ଜାରି;
                }
                ଯଦି (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    ଜାରି;
                }
            }
        }

        closest = mode;
    }
    ଯଦି (!closest) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool DisplayModeChanged(ଅଚଳ SDL_DisplayMode *old_mode, ଅଚଳ SDL_DisplayMode *new_mode)
{
    ଫେରନ୍ତୁ ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

ଶୂନ୍ୟ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ଅଚଳ SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ଯଦି (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ଫେରନ୍ତୁ;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    ଯଦି (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        ଯଦି (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ଅଚଳ SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ଖାଲି);

    ଫେରନ୍ତୁ &display->desktop_mode;
}

ଶୂନ୍ୟ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ଅଚଳ SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ଯଦି (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } ଅନ୍ୟଥା {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    ଯଦି (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ଅଚଳ SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ଖାଲି);

    ଫେରନ୍ତୁ display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ଯଦି (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    ଯଦି (mode == display->current_mode) {
        ଫେରନ୍ତୁ true;
    }
#endif

    // Actually change the display mode
    ଯଦି (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        ଯଦି (!result) {
            ଫେରନ୍ତୁ false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ଫେରନ୍ତୁ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ସ୍ଥିର ଶୂନ୍ୟ SDL_GetClosestPointOnRect(ଅଚଳ SDL_Rect *rect, SDL_Point *point)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ = rect->x + rect->w - 1;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା bottom = rect->y + rect->h - 1;

    ଯଦି (point->x < rect->x) {
        point->x = rect->x;
    } ଅନ୍ୟଥା ଯଦି (point->x > ଡାହାଣ) {
        point->x = ଡାହାଣ;
    }

    ଯଦି (point->y < rect->y) {
        point->y = rect->y;
    } ଅନ୍ୟଥା ଯଦି (point->y > bottom) {
        point->y = bottom;
    }
}

ସ୍ଥିର SDL_DisplayID GetDisplayForRect(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, dist;
    SDL_DisplayID closest = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    ଯଦି (_this) {
        ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ଯଦି (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ଖାଲି)) {
                ଫେରନ୍ତୁ display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ଯଦି (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ଯଦି (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    ଫେରନ୍ତୁ closest;
}

ଶୂନ୍ୟ SDL_RelativeToGlobalForWindow(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rel_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rel_y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *abs_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *abs_y)
{
    SDL_Window *w;

    ଯଦି (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        ପାଇଁ (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            ଯଦି (!SDL_WINDOW_IS_POPUP(w)) {
                ଭାଙ୍ଗ;
            }
        }
    }

    ଯଦି (abs_x) {
        *abs_x = rel_x;
    }
    ଯଦି (abs_y) {
        *abs_y = rel_y;
    }
}

ଶୂନ୍ୟ SDL_GlobalToRelativeForWindow(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା abs_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା abs_y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *rel_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *rel_y)
{
    SDL_Window *w;

    ଯଦି (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        ପାଇଁ (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            ଯଦି (!SDL_WINDOW_IS_POPUP(w)) {
                ଭାଙ୍ଗ;
            }
        }
    }

    ଯଦି (rel_x) {
        *rel_x = abs_x;
    }
    ଯଦି (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ଅଚଳ SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ଫେରନ୍ତୁ 0;
    }

    ଫେରନ୍ତୁ GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ଅଚଳ SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ଫେରନ୍ତୁ 0;
    }

    ଫେରନ୍ତୁ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ସ୍ଥିର SDL_DisplayID GetDisplayAtOrigin(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
        SDL_Rect rect;
        ଅଚଳ SDL_DisplayID cur_id = _this->displays[i]->id;
        ଯଦି (SDL_GetDisplayBounds(cur_id, &rect)) {
            ଯଦି (x == rect.x && y == rect.y) {
                ଫେରନ୍ତୁ cur_id;
            }
        }
    }

    ଫେରନ୍ତୁ 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    ଯଦି (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    ଯଦି (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ଅନ୍ୟଥା {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    ଯଦି (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ଫେରନ୍ତୁ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, ଖାଲି);

    // An explicit fullscreen display overrides all
    ଯଦି (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ଯଦି (!displayID) {
        displayID = window->pending_displayID;
    }
    ଯଦି (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = window->last_position_pending ? window->pending.x : window->x;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = window->last_position_pending ? window->pending.y : window->y;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = window->last_size_pending ? window->pending.w : window->w;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ଯଦି (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ଯଦି (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ଫେରନ୍ତୁ SDL_GetVideoDisplay(displayID);
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
    ଯଦି (fs_display) {
        SDL_Set_ସଂଖ୍ୟା_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ଅନ୍ୟଥା {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ଫେରନ୍ତୁ GetDisplayForWindow(window);
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    ଯଦି (SDL_SendsDisplayChanges(_this)) {
        ଫେରନ୍ତୁ;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    ଯଦି (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        ଯଦି (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            ଯଦି (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା old_area = old_overlap.w * old_overlap.h;
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_area = new_overlap.w * new_overlap.h;
                ଦଶମିକ new_overlap_ratio = (new_area / ((ଦଶମିକ)old_area + new_area));
                ଯଦି (new_overlap_ratio < 0.80) {
                    ଫେରନ୍ତୁ;
                }
            }
        }
    }

    ଯଦି (displayID != window->displayID) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ଯଦି (display->fullscreen_window == window) {
                ଯଦି (display_index != i) {
                    ଯଦି (display_index < 0) {
                        display_index = i;
                    } ଅନ୍ୟଥା {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        ଯଦି (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = ଖାଲି;
                    }
                }
                ଭାଙ୍ଗ;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)displayID, 0);
    }
}

ଦଶମିକ SDL_GetWindowPixelDensity(SDL_Window *window)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା window_w, window_h, pixel_w, pixel_h;
    ଦଶମିକ pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    ଯଦି (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (ଦଶମିକ)pixel_w / window_w;
    }
    ଫେରନ୍ତୁ pixel_density;
}

ଦଶମିକ SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ଫେରନ୍ତୁ window->display_scale;
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    ଦଶମିକ display_scale;

    ଯଦି (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } ଅନ୍ୟଥା {
        ଅଚଳ ଦଶମିକ pixel_density = SDL_GetWindowPixelDensity(window);
        ଅଚଳ ଦଶମିକ content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    ଯଦି (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ଖାଲି;
    SDL_DisplayMode *mode = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    ଯଦି (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ଯଦି (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        ଯଦି (!display) {
            // This should never happen, but it did...
            ଯାଅ done;
        }
    } ଅନ୍ୟଥା {
        ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
            display = _this->displays[i];
            ଯଦି (display->fullscreen_window == window) {
                ଭାଙ୍ଗ;
            }
        }
        ଯଦି (!display || i == _this->ଅଙ୍କ_displays) {
            // Already not fullscreen on any display
            display = ଖାଲି;
        }
    }

    ଯଦି (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        ଯଦି (mode) {
            window->fullscreen_exclusive = true;
        } ଅନ୍ୟଥା {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#ଯଦି defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ଯଦି (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ଯଦି (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            ଯଦି (display) {
                display->fullscreen_window = ଖାଲି;
            }
            ଯାଅ done;
        }
        ଯଦି (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ଯଦି (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                ଯଦି (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    ଯାଅ error;
                }
            } ଅନ୍ୟଥା ଯଦି (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    ଯଦି (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, ଖାଲି);
                        ଯଦି (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = ଖାଲି;
                    }
                }
            }

            ଯଦି (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                ଯାଅ done;
            }
        }
    }
#endif

    ଯଦି (display) {
        // Restore the video mode on other displays if needed
        ପାଇଁ (i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ଯଦି (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, ଖାଲି);
                other->fullscreen_window = ଖାଲି;
            }
        }
    }

    ଯଦି (fullscreen) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ଯଦି (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        ଯଦି (!SDL_SetDisplayModeForDisplay(display, mode)) {
            ଯାଅ error;
        }
        ଯଦି (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ଯଦି (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } ଅନ୍ୟଥା {
                resized = true;
            }

            ଯଦି (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } ଅନ୍ୟଥା ଯଦି (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                ଯାଅ error;
            }
        }

        ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ଯଦି (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ଯଦି (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } ଅନ୍ୟଥା {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ଯଦି (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                ଯଦି (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } ଅନ୍ୟଥା {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } ଅନ୍ୟଥା {
        bool resized = false;

        // Restore the desktop mode
        ଯଦି (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, ଖାଲି);
        }
        ଯଦି (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ଯଦି (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                ଯଦି (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ଅନ୍ୟଥା {
                resized = true;
            }

            ଯଦି (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } ଅନ୍ୟଥା ଯଦି (ret == SDL_FULLSCREEN_FAILED) {
                ଯାଅ error;
            }
        }

        ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            ଯଦି (display) {
                display->fullscreen_window = ଖାଲି;
            }

            ଯଦି (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                ଯଦି (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } ଅନ୍ୟଥା {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    ଫେରନ୍ତୁ true;

error:
    ଯଦି (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ଫେରନ୍ତୁ false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ଅଚଳ SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (mode) {
        ଯଦି (!SDL_GetFullscreenModeMatch(mode)) {
            ଫେରନ୍ତୁ SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } ଅନ୍ୟଥା {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#ଯଦି defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ଯଦି (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    ଯଦି (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    ଫେରନ୍ତୁ true;
}

ଅଚଳ SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ଖାଲି);
    CHECK_WINDOW_NOT_POPUP(window, ଖାଲି);

    ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
        ଫେରନ୍ତୁ SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

ଶୂନ୍ୟ *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    ଯଦି (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ଅଚଳ SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    ଯଦି (mode) {
        ଫେରନ୍ତୁ mode->format;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ଉପର_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

ସ୍ଥିର SDL_INLINE bool IsAcceptingDragAndDrop(ଶୂନ୍ୟ)
{
    ଯଦି (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

// prepare a newly-created window
ସ୍ଥିର SDL_INLINE ଶୂନ୍ୟ PrepareDragAndDropSupport(SDL_Window *window)
{
    ଯଦି (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
ଶୂନ୍ୟ SDL_ToggleDragAndDropSupport(ଶୂନ୍ୟ)
{
    ଯଦି (_this && _this->AcceptDragAndDrop) {
        ଅଚଳ bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        ପାଇଁ (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଗଣନା_2)
{
    ଯଦି (ଗଣନା_2) {
        *ଗଣନା_2 = 0;
    }

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_Window *window;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_added = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_windows = 0;
    ପାଇଁ (window = _this->windows; window; window = window->next) {
        ++ଅଙ୍କ_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((ଅଙ୍କ_windows + 1) * ଆକାର(*windows));
    ଯଦି (!windows) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ପାଇଁ (window = _this->windows; window; window = window->next) {
        windows[ଅଙ୍କ_added++] = window;
        ଯଦି (ଅଙ୍କ_added == ଅଙ୍କ_windows) {
            // Race condition? Multi-threading not supported, ignore it
            ଭାଙ୍ଗ;
        }
    }
    windows[ଅଙ୍କ_added] = ଖାଲି;

    ଯଦି (ଗଣନା_2) {
        *ଗଣନା_2 = ଅଙ୍କ_added;
    }
    ଫେରନ୍ତୁ windows;
}

ସ୍ଥିର ଶୂନ୍ୟ ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    ଯଦି (!SDL_WINDOW_IS_POPUP(window)) {
        ଯଦି (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        ଯଦି (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        ଯଦି (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        ଯଦି (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        ଯଦି (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        ଯଦି (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    ଯଦି (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ଅନ୍ୟଥା {
        ApplyWindowFlags(window, flags);
        ଯଦି (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#ଯଦି defined(SDL_PLATFORM_LINUX)
    ଯଦି (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_ମୂଲ୍ୟ(window, 0.0f);
    }
#endif
}

ସ୍ଥିର bool SDL_ContextNotSupported(ଅଚଳ ଅକ୍ଷର *name)
{
    ଫେରନ୍ତୁ SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ସ୍ଥିର bool SDL_DllNotSupported(ଅଚଳ ଅକ୍ଷର *name)
{
    ଫେରନ୍ତୁ SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ସ୍ଥିର ସଂରଚନା {
    ଅଚଳ ଅକ୍ଷର *property_name;
    SDL_WindowFlags flag;
    bool invert_ମୂଲ୍ୟ;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_ଶୀର୍ଷ_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_ଉପର_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_ଉପର_PIXEL_DENSITY,  false },
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

ସ୍ଥିର SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_ସଂଖ୍ୟା, 0);

    ପାଇଁ (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        ଯଦି (SDL_WindowFlagProperties[i].invert_ମୂଲ୍ୟ) {
            ଯଦି (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } ଅନ୍ୟଥା {
            ଯଦି (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    ଫେରନ୍ତୁ flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ଅଚଳ ଅକ୍ଷର *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, ଖାଲି);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_X_ସଂଖ୍ୟା, SDL_WINDOWPOS_UNDEFINED);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_Y_ସଂଖ୍ୟା, SDL_WINDOWPOS_UNDEFINED);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_ସଂଖ୍ୟା, 0);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_ସଂଖ୍ୟା, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, ଖାଲି);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    ଯଦି (!_this) {
        // Initialize the video system if needed
        ଯଦି (!SDL_Init(SDL_INIT_VIDEO)) {
            ଫେରନ୍ତୁ ଖାଲି;
        }

        // Make clang-tidy happy
        ଯଦି (!_this) {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    ଯଦି ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        ଯଦି (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ଫେରନ୍ତୁ ଖାଲି;
        }

        // Tooltip and popup menu window must specify a parent window
        ଯଦି (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ଫେରନ୍ତୁ ଖାଲି;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    ଯଦି (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)type_flags);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Make sure the display list is up to date for window placement
    ଯଦି (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ଯଦି (w < 1) {
        w = 1;
    }
    ଯଦି (h < 1) {
        h = 1;
    }

    ଯଦି (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ଯଦି ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ଅନ୍ୟଥା ଯଦି ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ଯଦି (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ଯଦି (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ଯଦି (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ଯଦି (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ଯଦି (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ଯଦି (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ଯଦି (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା)graphics_flags);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    // Some platforms have certain graphics backends enabled by default
    ଯଦି (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ଯଦି (flags & SDL_WINDOW_OPENGL) {
        ଯଦି (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ଫେରନ୍ତୁ ଖାଲି;
        }
        ଯଦି (!SDL_GL_LoadLibrary(ଖାଲି)) {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    ଯଦି (flags & SDL_WINDOW_VULKAN) {
        ଯଦି (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ଫେରନ୍ତୁ ଖାଲି;
        }
        ଯଦି (!SDL_Vulkan_LoadLibrary(ଖାଲି)) {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    ଯଦି (flags & SDL_WINDOW_METAL) {
        ଯଦି (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, ଆକାର(*window));
    ଯଦି (!window) {
        ଫେରନ୍ତୁ ଖାଲି;
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
    ଯଦି (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    ଯଦି (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    ଯଦି (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ଯଦି (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    ଯଦି (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_ଠେଲ_Error();
        SDL_DestroyWindow(window);
        SDL_କାଢ଼_Error();
        ଫେରନ୍ତୁ ଖାଲି;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ଯଦି !defined(SDL_PLATFORM_WINDOWS)
    ଯଦି (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    ଯଦି (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ଫେରନ୍ତୁ window;
}

SDL_Window *SDL_CreateWindow(ଅଚଳ ଅକ୍ଷର *title, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    ଯଦି (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_ସଂଖ୍ୟା, w);
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_ସଂଖ୍ୟା, h);
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_ସଂଖ୍ୟା, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ଫେରନ୍ତୁ window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ଯଦି (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_X_ସଂଖ୍ୟା, offset_x);
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_Y_ସଂଖ୍ୟା, offset_y);
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_ସଂଖ୍ୟା, w);
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_ସଂଖ୍ୟା, h);
    SDL_Set_ସଂଖ୍ୟା_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_ସଂଖ୍ୟା, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ଫେରନ୍ତୁ window;
}

ସ୍ଥିର bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ଯଦି (!_this->ReconfigureWindow) {
        ଫେରନ୍ତୁ false;
    }

    ଅଚଳ SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ଯଦି (graphics_flags & (graphics_flags - 1)) {
        ଫେରନ୍ତୁ SDL_SetError("Conflicting window flags specified");
    }

    ଯଦି ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ଫେରନ୍ତୁ SDL_ContextNotSupported("OpenGL");
    }
    ଯଦି ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ଫେରନ୍ତୁ SDL_ContextNotSupported("Vulkan");
    }
    ଯଦି ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ଫେରନ୍ତୁ SDL_ContextNotSupported("Metal");
    }

    ଯଦି (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ଯଦି (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ଯଦି (!_this->ReconfigureWindow(_this, window, 0)) {
            ଫେରନ୍ତୁ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ଯଦି (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    ଯଦି (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(ଖାଲି);
        ଯଦି (!loaded_opengl) {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା ଯଦି (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(ଖାଲି);
        ଯଦି (!loaded_vulkan) {
            ଫେରନ୍ତୁ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ଯଦି (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        ଯଦି (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ଯଦି (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ଫେରନ୍ତୁ false;
    }

    window->flags |= graphics_flags;

    ଫେରନ୍ତୁ true;
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
    ଯଦି (graphics_flags & (graphics_flags - 1)) {
        ଫେରନ୍ତୁ SDL_SetError("Conflicting window flags specified");
    }

    ଯଦି ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ଫେରନ୍ତୁ SDL_ContextNotSupported("OpenGL");
    }
    ଯଦି ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ଫେରନ୍ତୁ SDL_ContextNotSupported("Vulkan");
    }
    ଯଦି ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ଫେରନ୍ତୁ SDL_ContextNotSupported("Metal");
    }

    ଯଦି (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } ଅନ୍ୟଥା {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ଯଦି (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    ଯଦି (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ଅଚଳ bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    ଯଦି ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        ଯଦି (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } ଅନ୍ୟଥା {
            need_gl_unload = true;
        }
    } ଅନ୍ୟଥା ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    ଯଦି ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        ଯଦି (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } ଅନ୍ୟଥା {
            need_vulkan_unload = true;
        }
    } ଅନ୍ୟଥା ଯଦି (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    ଯଦି (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ଯଦି (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ଯଦି (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    ଯଦି (need_gl_load) {
        ଯଦି (!SDL_GL_LoadLibrary(ଖାଲି)) {
            ଫେରନ୍ତୁ false;
        }
        loaded_opengl = true;
    }

    ଯଦି (need_vulkan_load) {
        ଯଦି (!SDL_Vulkan_LoadLibrary(ଖାଲି)) {
            ଫେରନ୍ତୁ false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    ଯଦି (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        ଯଦି (!_this->CreateSDLWindow(_this, window, 0)) {
            ଯଦି (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            ଯଦି (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            ଫେରନ୍ତୁ false;
        }
    }

    ଯଦି (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    ଯଦି (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    ଯଦି (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    ଯଦି (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    ଯଦି (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    ଯଦି (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    ଯଦି (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ଫେରନ୍ତୁ true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ଯଦି (!SDL_ReconfigureWindowInternal(window, flags)) {
        ଫେରନ୍ତୁ SDL_RecreateWindow(window, flags);
    }

    ଫେରନ୍ତୁ true;
}

bool SDL_HasWindows(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ଫେରନ୍ତୁ window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯଦି (id) {
        ପାଇଁ (window = _this->windows; window; window = window->next) {
            ଯଦି (window->id == id) {
                ଫେରନ୍ତୁ window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ଫେରନ୍ତୁ ଖାଲି;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ଖାଲି);

    ଫେରନ୍ତୁ window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ଯଦି (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ଫେରନ୍ତୁ window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ଫେରନ୍ତୁ window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ଅଚଳ ଅକ୍ଷର *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (title == window->title) {
        ଫେରନ୍ତୁ true;
    }
    ଯଦି (!title) {
        title = "";
    }
    ଯଦି (window->title && SDL_strcmp(title, window->title) == 0) {
        ଫେରନ୍ତୁ true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    ଯଦି (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ଫେରନ୍ତୁ true;
}

ଅଚଳ ଅକ୍ଷର *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ଫେରନ୍ତୁ window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ଯଦି (!window->icon) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (!_this->SetWindowIcon) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଫେରନ୍ତୁ _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    ଯଦି (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    ଯଦି (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    ଯଦି (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ଯଦି (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ଅନ୍ୟଥା ଯଦି (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ଯଦି (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        ଯଦି (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ଯଦି (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ଫେରନ୍ତୁ false;
            }
        }
        ଯଦି (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ଯଦି (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ଅନ୍ୟଥା {
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
    ଯଦି (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    ଯଦି (_this->SetWindowPosition) {
        ଅଚଳ bool result = _this->SetWindowPosition(_this, window);
        ଯଦି (result) {
            SDL_SyncIfRequired(window);
        }
        ଫେରନ୍ତୁ result;
    }

    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ଅନ୍ୟଥା
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    ଯଦି (use_display_origin) {
        SDL_DisplayID displayID;

        ଯଦି (x) {
            *x = 0;
        }
        ଯଦି (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        ଯଦି (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ଯଦି (x) {
                *x = bounds.x;
            }
            ଯଦି (y) {
                *y = bounds.y;
            }
        }
    } ଅନ୍ୟଥା {
        ଅଚଳ bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        ଯଦି (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        ଯଦି (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (!_this->SetWindowBordered) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଅଚଳ bool want = bordered;
    ଅଚଳ bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    ଯଦି (want != have) {
        ଯଦି (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } ଅନ୍ୟଥା {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (!_this->SetWindowResizable) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଅଚଳ bool want = resizable;
    ଅଚଳ bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    ଯଦି (want != have) {
        ଯଦି (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ଅନ୍ୟଥା {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ଫେରନ୍ତୁ true;
}

bool SDL_Set_Window_Always_On_ଶୀର୍ଷ(SDL_Window *window, bool on_ଶୀର୍ଷ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (!_this->Set_Window_Always_On_ଶୀର୍ଷ) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଅଚଳ bool want = on_ଶୀର୍ଷ;
    ଅଚଳ bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ) != 0);
    ଯଦି (want != have) {
        ଯଦି (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ;
        } ଅନ୍ୟଥା {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_ଶୀର୍ଷ;
        }
        _this->Set_Window_Always_On_ଶୀର୍ଷ(_this, window, want);
    }

    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowSize(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    ଦଶମିକ new_aspect = w / (ଦଶମିକ)h;
    ଯଦି (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(h * window->max_aspect);
    } ଅନ୍ୟଥା ଯଦି (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ଯଦି (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    ଯଦି (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    ଯଦି (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    ଯଦି (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    ଯଦି (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_GetWindowSize(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ଯଦି (w) {
        *w = window->w;
    }
    ଯଦି (h) {
        *h = window->h;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, ଦଶମିକ min_aspect, ଦଶମିକ max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    ଯଦି (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = window->last_size_pending ? window->pending.w : window->floating.w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = window->last_size_pending ? window->pending.h : window->floating.h;
    ଫେରନ୍ତୁ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, ଦଶମିକ *min_aspect, ଦଶମିକ *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    ଯଦି (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଶୀର୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ବାମ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *bottom, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଡାହାଣ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy = 0;

    ଯଦି (!ଶୀର୍ଷ) {
        ଶୀର୍ଷ = &dummy;
    }
    ଯଦି (!ବାମ) {
        ବାମ = &dummy;
    }
    ଯଦି (!ଡାହାଣ) {
        ଡାହାଣ = &dummy;
    }
    ଯଦି (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *ଶୀର୍ଷ = *ବାମ = *bottom = *ଡାହାଣ = 0;

    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!_this->GetWindowBordersSize) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଫେରନ୍ତୁ _this->GetWindowBordersSize(_this, window, ଶୀର୍ଷ, ବାମ, bottom, ଡାହାଣ);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା filter;

    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!w) {
        w = &filter;
    }

    ଯଦି (!h) {
        h = &filter;
    }

    ଯଦି (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } ଅନ୍ୟଥା {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ଅଚଳ SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        ଯଦି ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } ଅନ୍ୟଥା {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        ଯଦି (mode) {
            *w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_ceilf(*w * mode->pixel_density);
            *h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ଫେରନ୍ତୁ SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    ଯଦି (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = window->last_size_pending ? window->pending.w : window->floating.w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = window->last_size_pending ? window->pending.h : window->floating.h;
    ଫେରନ୍ତୁ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *min_w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ଯଦି (min_w) {
        *min_w = window->min_w;
    }
    ଯଦି (min_h) {
        *min_h = window->min_h;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("max_h");
    }

    ଯଦି ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ଫେରନ୍ତୁ SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    ଯଦି (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = window->last_size_pending ? window->pending.w : window->floating.w;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = window->last_size_pending ? window->pending.h : window->floating.h;
    ଫେରନ୍ତୁ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *max_w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ଯଦି (max_w) {
        *max_w = window->max_w;
    }
    ଯଦି (max_h) {
        *max_h = window->max_h;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ଫେରନ୍ତୁ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ଯଦି (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } ଅନ୍ୟଥା {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    ପାଇଁ (child = window->first_child; child; child = child->next_sibling) {
        ଯଦି (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            ଭାଙ୍ଗ;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ଫେରନ୍ତୁ true;
    }

    // Hide all child windows
    ପାଇଁ (child = window->first_child; child; child = child->next_sibling) {
        ଯଦି (child->flags & SDL_WINDOW_HIDDEN) {
            ଭାଙ୍ଗ;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ଅଚଳ SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    ଯଦି (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } ଅନ୍ୟଥା {
        SDL_SetMouseFocus(ଖାଲି);
        SDL_SetKeyboardFocus(ଖାଲି);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ଫେରନ୍ତୁ true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        ଫେରନ୍ତୁ true;
    }
    ଯଦି (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (!_this->MaximizeWindow) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଯଦି (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ଫେରନ୍ତୁ SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ଫେରନ୍ତୁ true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ଫେରନ୍ତୁ true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (!_this->MinimizeWindow) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ଫେରନ୍ତୁ true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ଫେରନ୍ତୁ true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (!_this->RestoreWindow) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ଫେରନ୍ତୁ true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        ଯଦି (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } ଅନ୍ୟଥା {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ଯଦି (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    ଯଦି (result) {
        SDL_SyncIfRequired(window);
    }

    ଫେରନ୍ତୁ result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (_this->SyncWindow) {
        ଫେରନ୍ତୁ _this->SyncWindow(_this, window);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ true;
    }
}

ସ୍ଥିର bool ShouldAttemptTextureFramebuffer(ଶୂନ୍ୟ)
{
    ଅଚଳ ଅକ୍ଷର *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ଯଦି (!_this->CreateWindowFramebuffer) {
        ଫେରନ୍ତୁ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ଯଦି (hint && *hint) {
        ଯଦି (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ଅନ୍ୟଥା {
            attempt_texture_framebuffer = true;
        }
    } ଅନ୍ୟଥା {
        ଯଦି (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ଅନ୍ୟଥା {
            attempt_texture_framebuffer = false;
        }
    }
    ଫେରନ୍ତୁ attempt_texture_framebuffer;
}

ସ୍ଥିର SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    ଶୂନ୍ୟ *pixels = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch = 0;
    bool created_framebuffer = false;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    ଯଦି (!_this->checked_texture_framebuffer) {
        ଯଦି (ShouldAttemptTextureFramebuffer()) {
            ଯଦି (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ଅନ୍ୟଥା {
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

    ଯଦି (!created_framebuffer) {
        ଯଦି (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            ଫେରନ୍ତୁ ଖାଲି;
        }

        ଯଦି (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ଫେରନ୍ତୁ ଖାଲି;
        }
    }

    ଯଦି (window->surface) {
        // We may have gone recursive and already created the surface
        ଫେରନ୍ତୁ window->surface;
    }

    ଫେରନ୍ତୁ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଫେରନ୍ତୁ window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ଖାଲି);

    ଯଦି (!window->surface_valid) {
        ଯଦି (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = ଖାଲି;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        ଯଦି (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ଫେରନ୍ତୁ window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!_this->SetWindowFramebufferVSync) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }
    ଫେରନ୍ତୁ _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!_this->GetWindowFramebufferVSync) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }
    ଫେରନ୍ତୁ _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    ଫେରନ୍ତୁ SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ଅଚଳ SDL_Rect *rects,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!window->surface_valid) {
        ଫେରନ୍ତୁ SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ଫେରନ୍ତୁ _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = ଖାଲି;
        window->surface_valid = false;
    }

    ଯଦି (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ଯଦି (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, ଦଶମିକ opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!_this->SetWindowOpacity) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଯଦି (opacity < 0.0f) {
        opacity = 0.0f;
    } ଅନ୍ୟଥା ଯଦି (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    ଯଦି (result) {
        window->opacity = opacity;
    }

    ଫେରନ୍ତୁ result;
}

ଦଶମିକ SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ଫେରନ୍ତୁ window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    ଯଦି (window == parent) {
        ଫେରନ୍ତୁ SDL_SetError("Cannot set the parent of a window to itself.");
    }

    ଯଦି (!_this->SetWindowParent) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଯଦି (window->flags & SDL_WINDOW_MODAL) {
        ଫେରନ୍ତୁ SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ଯଦି (window->parent == parent) {
        ଫେରନ୍ତୁ true;
    }

    ଅଚଳ bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : ଖାଲି);

    ଫେରନ୍ତୁ ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (!_this->SetWindowModal) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଯଦି (modal) {
        ଯଦି (!window->parent) {
            ଫେରନ୍ତୁ SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } ଅନ୍ୟଥା ଯଦି (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ true; // Already not modal, so nothing to do.
    }

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        ଫେରନ୍ତୁ true;
    }

    ଫେରନ୍ତୁ _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_ନିବେଶ_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ଯେତେବେଳେ (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ଯଦି (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_ନିବେଶ_FOCUS);
        }
    }

    *new_focus = focus;
    ଫେରନ୍ତୁ set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    ପାଇଁ (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    ପାଇଁ (w = current_focus; w != toplevel_parent; w = w->parent) {
        ଯଦି (w == window) {
            found_higher_focus = true;
            ଭାଙ୍ଗ;
        }
    }

    ଫେରନ୍ତୁ !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଅଚଳ bool want = (focusable != false); // normalize the flag.
    ଅଚଳ bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    ଯଦି ((want != have) && (_this->SetWindowFocusable)) {
        ଯଦି (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } ଅନ୍ୟଥା {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        ଯଦି (!_this->SetWindowFocusable(_this, window, want)) {
            ଫେରନ୍ତୁ false;
        }
    }

    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଅଚଳ bool want = (fill != false); // normalize the flag.
    ଅଚଳ bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    ଯଦି ((want != have) && (_this->SetWindowFillDocument)) {
        ଯଦି (!_this->SetWindowFillDocument(_this, window, want)) {
            ଫେରନ୍ତୁ false;
        } ଅନ୍ୟଥା ଯଦି (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } ଅନ୍ୟଥା {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    ଯଦି (window->flags & SDL_WINDOW_ନିବେଶ_FOCUS) {
        ଯଦି (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ଅନ୍ୟଥା {
            mouse_grabbed = false;
        }

        ଯଦି (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ଅନ୍ୟଥା {
            keyboard_grabbed = false;
        }
    } ଅନ୍ୟଥା {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ଯଦି (mouse_grabbed || keyboard_grabbed) {
        ଯଦି (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            ଯଦି (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            ଯଦି (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } ଅନ୍ୟଥା ଯଦି (_this->grabbed_window == window) {
        _this->grabbed_window = ଖାଲି; // ungrabbing input.
    }

    ଯଦି (_this->SetWindowMouseGrab) {
        ଯଦି (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    ଯଦି (_this->SetWindowKeyboardGrab) {
        ଯଦି (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    ଯଦି (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = ଖାଲି;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        ଯଦି (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } ଅନ୍ୟଥା {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ଫେରନ୍ତୁ true;
    }
    ଯଦି (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } ଅନ୍ୟଥା {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ଯଦି (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (window->flags & SDL_WINDOW_HIDDEN) {
        ଯଦି (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } ଅନ୍ୟଥା {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ଫେରନ୍ତୁ true;
    }
    ଯଦି (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } ଅନ୍ୟଥା {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ଯଦି (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ଫେରନ୍ତୁ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ଫେରନ୍ତୁ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(ଶୂନ୍ୟ)
{
    ଯଦି (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ଫେରନ୍ତୁ _this->grabbed_window;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ ଖାଲି;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ଅଚଳ SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!_this->SetWindowMouseRect) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ଯଦି (!rect) {
        rect = &zero;
    }

    ଯଦି (SDL_memcmp(&window->mouse_rect, rect, ଆକାର(*rect)) == 0) {
        ଫେରନ୍ତୁ true;
    }
    SDL_memcpy(&window->mouse_rect, rect, ଆକାର(*rect));

    ଫେରନ୍ତୁ _this->SetWindowMouseRect(_this, window);
}

ଅଚଳ SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ଖାଲି);

    ଯଦି (SDL_RectEmpty(&window->mouse_rect)) {
        ଫେରନ୍ତୁ ଖାଲି;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ &window->mouse_rect;
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

    ଯଦି (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } ଅନ୍ୟଥା {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    ଯଦି (!SDL_UpdateRelativeMouseMode()) {
        ଯଦି (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } ଅନ୍ୟଥା {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ଫେରନ୍ତୁ true;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (_this->FlashWindow) {
        ଫେରନ୍ତୁ _this->FlashWindow(_this, window, operation);
    }

    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    ଯଦି (_this->ApplyWindowProgress) {
        ଯଦି (!_this->ApplyWindowProgress(_this, window)) {
            ଫେରନ୍ତୁ false;
        }
    }

    ଫେରନ୍ତୁ true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ଫେରନ୍ତୁ window->progress_state;
}

bool SDL_Set_Window_Progress_ମୂଲ୍ୟ(SDL_Window *window, ଦଶମିକ ମୂଲ୍ୟ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ମୂଲ୍ୟ = SDL_clamp(ମୂଲ୍ୟ, 0.0f, 1.f);

    window->progress_ମୂଲ୍ୟ = ମୂଲ୍ୟ;

    ଯଦି (_this->ApplyWindowProgress) {
        ଯଦି (!_this->ApplyWindowProgress(_this, window)) {
            ଫେରନ୍ତୁ false;
        }
    }

    ଫେରନ୍ତୁ true;
}

ଦଶମିକ SDL_Get_Window_Progress_ମୂଲ୍ୟ(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ଫେରନ୍ତୁ window->progress_ମୂଲ୍ୟ;
}

ଶୂନ୍ୟ SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

ଶୂନ୍ୟ SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

ଶୂନ୍ୟ SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    ଯଦି (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ଅଚଳ bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        ଯଦି (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_ଉପର_density_modes = false;

            ଯଦି (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_ଉପର_density_modes = true;
            }
            ଅଚଳ bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_ଉପର_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ଯଦି (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } ଅନ୍ୟଥା {
            SDL_zero(window->current_fullscreen_mode);
        }

        ଯଦି (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

ଶୂନ୍ୟ SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

ଶୂନ୍ୟ SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    ଯଦି ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, ଖାଲି);
        ଯଦି (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

ଶୂନ୍ୟ SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

ଶୂନ୍ୟ SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

ଶୂନ୍ୟ SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    ଯଦି (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ଅନ୍ୟଥା {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ସ୍ଥିର ଶୂନ୍ୟ SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_ବାମ;
    rect.y = window->safe_inset_ଶୀର୍ଷ;
    rect.w = window->w - (window->safe_inset_ଡାହାଣ + window->safe_inset_ବାମ);
    rect.h = window->h - (window->safe_inset_ଶୀର୍ଷ + window->safe_inset_bottom);
    ଯଦି (SDL_memcmp(&rect, &window->safe_rect, ଆକାର(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

ଶୂନ୍ୟ SDL_SetWindowSafeAreaInsets(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଡାହାଣ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଶୀର୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bottom)
{
    window->safe_inset_ବାମ = ବାମ;
    window->safe_inset_ଡାହାଣ = ଡାହାଣ;
    window->safe_inset_ଶୀର୍ଷ = ଶୀର୍ଷ;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    ଯଦି (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (rect) {
        ଯଦି (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } ଅନ୍ୟଥା {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ SDL_OnWindowMinimized(SDL_Window *window)
{
    ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

ଶୂନ୍ୟ SDL_OnWindowMaximized(SDL_Window *window)
{
}

ଶୂନ୍ୟ SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    ଯଦି (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

ଶୂନ୍ୟ SDL_OnWindowEnter(SDL_Window *window)
{
    ଯଦି (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

ଶୂନ୍ୟ SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

ଶୂନ୍ୟ SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ଯଦି (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

ସ୍ଥିର bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ଅଚଳ ଅକ୍ଷର *hint;

    ଯଦି (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ଫେରନ୍ତୁ false;
    }

#ଯଦି defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ଯଦି (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ଯଦି (Cocoa_IsShowingModalDialog(window)) {
            ଫେରନ୍ତୁ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ଅନ୍ୟଥା ଯଦି (Cocoa_IsWindowInFullscreenSpace(window)) {
            ଫେରନ୍ତୁ false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        ବାହ୍ୟ bool Android_JNI_ShouldMinimizeOnFocusLoss(ଶୂନ୍ୟ);
        ଯଦି (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ଫେରନ୍ତୁ false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ଯଦି (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ଯଦି (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ଫେରନ୍ତୁ true;
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ false;
        }
    }
    ଫେରନ୍ତୁ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

ଶୂନ୍ୟ SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    ଯଦି (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(ଶୂନ୍ୟ)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    ଯଦି (focus) {
        // Get the toplevel parent window.
        ଯେତେବେଳେ (focus->parent) {
            focus = focus->parent;
        }
    }

    ଫେରନ୍ତୁ focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->ଅଙ୍କ_renderers + 1) * ଆକାର(*renderers));
    ଯଦି (!renderers) {
        ଫେରନ୍ତୁ false;
    }

    window->renderers = renderers;
    window->renderers[window->ଅଙ୍କ_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < window->ଅଙ୍କ_renderers; ++i) {
        ଯଦି (window->renderers[i] == renderer) {
            ଯଦି (i < (window->ଅଙ୍କ_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->ଅଙ୍କ_renderers - i - 1) * ଆକାର(window->renderers[i]));
            }
            --window->ଅଙ୍କ_renderers;
            ଭାଙ୍ଗ;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ଯଦି (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, ଖାଲି) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

ଶୂନ୍ୟ SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    ଯେତେବେଳେ (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    ଯଦି (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    ଯଦି (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_ନିବେଶ_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ଯଦି (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
        ଯଦି (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = ଖାଲି;
        }
    }

    // Make sure this window no longer has focus
    ଯଦି (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(ଖାଲି);
    }
    ଯଦି ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ଯଦି (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(ଖାଲି);
    }

    // Make no context current if this is the current context window
    ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        ଯଦି (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, ଖାଲି);
        }
    }

    ଯଦି (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ଯଦି (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ଯଦି (_this->grabbed_window == window) {
        _this->grabbed_window = ଖାଲି; // ungrabbing input.
    }

    ଯଦି (_this->current_glwin == window) {
        _this->current_glwin = ଖାଲି;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, ଖାଲି);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, ଖାଲି);

    // Unlink the window from the global window list
    ଯଦି (window->next) {
        window->next->prev = window->prev;
    }
    ଯଦି (window->prev) {
        window->prev->next = window->next;
    } ଅନ୍ୟଥା {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }
    ଯଦି (!_this->suspend_screensaver) {
        ଫେରନ୍ତୁ true;
    }
    _this->suspend_screensaver = false;
    ଯଦି (_this->SuspendScreenSaver) {
        ଫେରନ୍ତୁ _this->SuspendScreenSaver(_this);
    }

    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }
    ଯଦି (_this->suspend_screensaver) {
        ଫେରନ୍ତୁ true;
    }
    _this->suspend_screensaver = true;
    ଯଦି (_this->SuspendScreenSaver) {
        ଫେରନ୍ତୁ _this->SuspendScreenSaver(_this);
    }

    ଫେରନ୍ତୁ SDL_Unsupported();
}

ଶୂନ୍ୟ SDL_QuitVideo(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ଯଦି 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ଯେତେବେଳେ (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    ଯଦି (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ଯଦି (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    ପାଇଁ (i = _this->ଅଙ୍କ_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->ଅଙ୍କ_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ଖାଲି;

    SDL_CancelClipboardData(0);

    ଯଦି (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = ଖାଲି;
    }
    _this->ମୁକ୍ତ(_this);
    _this = ଖାଲି;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(ଅଚଳ ଅକ୍ଷର *path)
{
    bool result;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }
    ଯଦି (_this->gl_config.driver_loaded) {
        ଯଦି (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ଫେରନ୍ତୁ SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } ଅନ୍ୟଥା {
        ଯଦି (!_this->GL_LoadLibrary) {
            ଫେରନ୍ତୁ SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    ଯଦି (result) {
        ++_this->gl_config.driver_loaded;
    } ଅନ୍ୟଥା {
        ଯଦି (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ଫେରନ୍ତୁ result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ଅଚଳ ଅକ୍ଷର *proc)
{
    SDL_FunctionPointer func;

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    func = ଖାଲି;
    ଯଦି (_this->GL_GetProcAddress) {
        ଯଦି (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } ଅନ୍ୟଥା {
            SDL_SetError("No GL driver has been loaded");
        }
    } ଅନ୍ୟଥା {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ଫେରନ୍ତୁ func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ଅଚଳ ଅକ୍ଷର *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    func = ଖାଲି;

    ଯଦି (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } ଅନ୍ୟଥା {
        SDL_SetError("No EGL library has been loaded");
    }

    ଫେରନ୍ତୁ func;
#ଅନ୍ୟଥା
    SDL_SetError("SDL was not built with EGL support");
    ଫେରନ୍ତୁ ଖାଲି;
#endif
}

ଶୂନ୍ୟ SDL_GL_UnloadLibrary(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ;
    }
    ଯଦି (_this->gl_config.driver_loaded > 0) {
        ଯଦି (--_this->gl_config.driver_loaded > 0) {
            ଫେରନ୍ତୁ;
        }
        ଯଦି (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ଯଦି defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
ପ୍ରକାରବ୍ୟାଖ୍ୟା GLenum (APIENTRY* PFNGLGETERRORPROC) (ଶୂନ୍ୟ);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅଚଳ GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଅଚଳ GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

ସ୍ଥିର SDL_INLINE bool isAtLeastGL3(ଅଚଳ ଅକ୍ଷର *verstr)
{
    ଫେରନ୍ତୁ verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ଅଚଳ ଅକ୍ଷର *extension)
{
#ଯଦି defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ଅଚଳ ଅକ୍ଷର *extensions;
    ଅଚଳ ଅକ୍ଷର *start;
    ଅଚଳ ଅକ୍ଷର *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ଯଦି (where || *extension == '\0') {
        ଫେରନ୍ତୁ false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    ଯଦି (start && *start == '0') {
        ଫେରନ୍ତୁ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ଯଦି (!glGetStringFunc) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (isAtLeastGL3((ଅଚଳ ଅକ୍ଷର *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint ଅଙ୍କ_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ଯଦି ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ଫେରନ୍ତୁ false;
        }

#ifndef GL_ଅଙ୍କ_EXTENSIONS
#define GL_ଅଙ୍କ_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_ଅଙ୍କ_EXTENSIONS, &ଅଙ୍କ_exts);
        ପାଇଁ (i = 0; i < ଅଙ୍କ_exts; i++) {
            ଅଚଳ ଅକ୍ଷର *thisext = (ଅଚଳ ଅକ୍ଷର *)glGetStringiFunc(GL_EXTENSIONS, i);
            ଯଦି (SDL_strcmp(thisext, extension) == 0) {
                ଫେରନ୍ତୁ true;
            }
        }

        ଫେରନ୍ତୁ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ଅଚଳ ଅକ୍ଷର *)glGetStringFunc(GL_EXTENSIONS);
    ଯଦି (!extensions) {
        ଫେରନ୍ତୁ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    ପାଇଁ (;;) {
        where = SDL_strstr(start, extension);
        ଯଦି (!where) {
            ଭାଙ୍ଗ;
        }

        terminator = where + SDL_strlen(extension);
        ଯଦି (where == extensions || *(where - 1) == ' ') {
            ଯଦି (*terminator == ' ' || *terminator == '\0') {
                ଫେରନ୍ତୁ true;
            }
        }

        start = terminator;
    }
    ଫେରନ୍ତୁ false;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
ଶୂନ୍ୟ SDL_GL_DeduceMaxSupportedESProfile(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *major, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#ଯଦି defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ଯଦି (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ଅନ୍ୟଥା ଯଦି (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ଅନ୍ୟଥା ଯଦି (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ଅନ୍ୟଥା {
        *major = 2;
        *minor = 0;
    }
#endif
}

ଶୂନ୍ୟ SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   ଶୂନ୍ୟ *userdata)
{
    ଯଦି (!_this) {
        ଫେରନ୍ତୁ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

ଶୂନ୍ୟ SDL_GL_ResetAttributes(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        ଫେରନ୍ତୁ;
    }

    _this->egl_platformattrib_callback = ଖାଲି;
    _this->egl_surfaceattrib_callback = ଖାଲି;
    _this->egl_contextattrib_callback = ଖାଲି;
    _this->egl_attrib_callback_userdata = ଖାଲି;

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
#ନଚେତଯଦି defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#ନଚେତଯଦି defined(SDL_VIDEO_OPENGL_ES)
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

    ଯଦି (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ)
{
#ଯଦି defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }
    result = true;
    ବାଛ (attr) {
    ସ୍ଥିତି SDL_GL_RED_SIZE:
        _this->gl_config.red_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_STEREO:
        _this->gl_config.stereo = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_FLAGS:
        ଯଦି (ମୂଲ୍ୟ & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", ମୂଲ୍ୟ);
            ଭାଙ୍ଗ;
        }
        _this->gl_config.flags = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_PROFILE_MASK:
        ଯଦି (ମୂଲ୍ୟ != 0 &&
            ମୂଲ୍ୟ != SDL_GL_CONTEXT_PROFILE_CORE &&
            ମୂଲ୍ୟ != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            ମୂଲ୍ୟ != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", ମୂଲ୍ୟ);
            ଭାଙ୍ଗ;
        }
        _this->gl_config.profile_mask = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = ମୂଲ୍ୟ;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        result = SDL_SetError("Unknown OpenGL attribute");
        ଭାଙ୍ଗ;
    }
    ଫେରନ୍ତୁ result;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ମୂଲ୍ୟ)
{
#ଯଦି defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_ବାମ;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!ମୂଲ୍ୟ) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *ମୂଲ୍ୟ = 0;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    ବାଛ (attr) {
    ସ୍ଥିତି SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        ଭାଙ୍ଗ;
#ଅନ୍ୟଥା
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *ମୂଲ୍ୟ = _this->gl_config.double_buffer;
        ଫେରନ୍ତୁ true;
#endif
    ସ୍ଥିତି SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        ଭାଙ୍ଗ;
#ifdef SDL_VIDEO_OPENGL
    ସ୍ଥିତି SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_STEREO:
        attrib = GL_STEREO;
        ଭାଙ୍ଗ;
#ଅନ୍ୟଥା
    ସ୍ଥିତି SDL_GL_ACCUM_RED_SIZE:
    ସ୍ଥିତି SDL_GL_ACCUM_GREEN_SIZE:
    ସ୍ଥିତି SDL_GL_ACCUM_BLUE_SIZE:
    ସ୍ଥିତି SDL_GL_ACCUM_ALPHA_SIZE:
    ସ୍ଥିତି SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *ମୂଲ୍ୟ = 0;
        ଫେରନ୍ତୁ true;
#endif
    ସ୍ଥିତି SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_GL_BUFFER_SIZE:
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        ଯଦି (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            ଫେରନ୍ତୁ false;
        }
        ଯଦି (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            ଫେରନ୍ତୁ false;
        }
        ଯଦି (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            ଫେରନ୍ତୁ false;
        }
        ଯଦି (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            ଫେରନ୍ତୁ false;
        }

        *ମୂଲ୍ୟ = rsize + gsize + bsize + asize;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *ମୂଲ୍ୟ = (_this->gl_config.accelerated != 0);
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_RETAINED_BACKING:
    {
        *ମୂଲ୍ୟ = _this->gl_config.retained_backing;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *ମୂଲ୍ୟ = _this->gl_config.major_version;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *ମୂଲ୍ୟ = _this->gl_config.minor_version;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_CONTEXT_FLAGS:
    {
        *ମୂଲ୍ୟ = _this->gl_config.flags;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *ମୂଲ୍ୟ = _this->gl_config.profile_mask;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *ମୂଲ୍ୟ = _this->gl_config.share_with_current_context;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *ମୂଲ୍ୟ = _this->gl_config.framebuffer_srgb_capable;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_CONTEXT_NO_ERROR:
    {
        *ମୂଲ୍ୟ = _this->gl_config.no_error;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_EGL_PLATFORM:
    {
        *ମୂଲ୍ୟ = _this->gl_config.egl_platform;
        ଫେରନ୍ତୁ true;
    }
    ସ୍ଥିତି SDL_GL_FLOATBUFFERS:
    {
        ଯଦି (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            ଭାଙ୍ଗ;
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ 0;
        }
    }
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ଯଦି (!glGetStringFunc) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (attachmentattrib && isAtLeastGL3((ଅଚଳ ଅକ୍ଷର *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        ଯଦି (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        ଯଦି (glGetFramebufferAttachmentParameterivFunc) {
            ଯଦି (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ଯଦି (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ଯଦି (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)ମୂଲ୍ୟ);
            } ଅନ୍ୟଥା {
                *ମୂଲ୍ୟ = 0;
            }
            ଯଦି (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ଯଦି (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)ମୂଲ୍ୟ);
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    ଯଦି (!glGetErrorFunc) {
        ଫେରନ୍ତୁ false;
    }

    error = glGetErrorFunc();
    ଯଦି (error != GL_NO_ERROR) {
        ଯଦି (error == GL_INVALID_ENUM) {
            ଫେରନ୍ତୁ SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } ଅନ୍ୟଥା ଯଦି (error == GL_INVALID_ମୂଲ୍ୟ) {
            ଫେରନ୍ତୁ SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ଫେରନ୍ତୁ SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ଯଦି (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *ମୂଲ୍ୟ = (*ମୂଲ୍ୟ == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ଫେରନ୍ତୁ true;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = ଖାଲି;
    CHECK_WINDOW_MAGIC(window, ଖାଲି);

    ଯଦି (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ଫେରନ୍ତୁ ଖାଲି;
    }

#ଯଦି defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା srgb_requested = -1;
    ଅଚଳ ଅକ୍ଷର *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ଯଦି (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    ଯଦି (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, ଖାଲି);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, ଖାଲି);
    }

#ଯଦି defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ଯଦି (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        ଯଦି (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ଯଦି (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ଅନ୍ୟଥା {
                supported = isAtLeastGL3((ଅଚଳ ଅକ୍ଷର *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ଯଦି (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ଫେରନ୍ତୁ ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }

    ଯଦି (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ଫେରନ୍ତୁ true;
    }

    ଯଦି (!context) {
        window = ଖାଲି;
    } ଅନ୍ୟଥା ଯଦି (window) {
        CHECK_WINDOW_MAGIC(window, false);

        ଯଦି (!(window->flags & SDL_WINDOW_OPENGL)) {
            ଫେରନ୍ତୁ SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } ଅନ୍ୟଥା ଯଦି (!_this->gl_allow_no_surface) {
        ଫେରନ୍ତୁ SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    ଯଦି (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, ଖାଲି);
        SDL_SetTLS(&_this->current_glctx_tls, context, ଖାଲି);
    }
    ଫେରନ୍ତୁ result;
}

SDL_Window *SDL_GL_GetCurrentWindow(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(ଶୂନ୍ୟ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ EGL_NO_DISPLAY;
    }
    ଯଦି (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ଫେରନ୍ତୁ EGL_NO_DISPLAY;
    }
    ଫେରନ୍ତୁ _this->egl_data->egl_display;
#ଅନ୍ୟଥା
    SDL_SetError("SDL was not built with EGL support");
    ଫେରନ୍ତୁ ଖାଲି;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(ଶୂନ୍ୟ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯଦି (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ _this->egl_data->egl_config;
#ଅନ୍ୟଥା
    SDL_SetError("SDL was not built with EGL support");
    ଫେରନ୍ତୁ ଖାଲି;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯଦି (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯଦି (_this->GL_GetEGLSurface) {
        ଫେରନ୍ତୁ _this->GL_GetEGLSurface(_this, window);
    }
    ଫେରନ୍ତୁ ଖାଲି;
#ଅନ୍ୟଥା
    SDL_SetError("SDL was not built with EGL support");
    ଫେରନ୍ତୁ ଖାଲି;
#endif
}

bool SDL_GL_SetSwapInterval(ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval)
{
    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    } ଅନ୍ୟଥା ଯଦି (SDL_GL_GetCurrentContext() == ଖାଲି) {
        ଫେରନ୍ତୁ SDL_SetError("No OpenGL context has been made current");
    } ଅନ୍ୟଥା ଯଦି (_this->GL_SetSwapInterval) {
        ଫେରନ୍ତୁ _this->GL_SetSwapInterval(_this, interval);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *interval)
{
    CHECK_PARAM(!interval) {
       ଫେରନ୍ତୁ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_SetError("no video driver");
    } ଅନ୍ୟଥା ଯଦି (SDL_GL_GetCurrentContext() == ଖାଲି) {
        ଫେରନ୍ତୁ SDL_SetError("no current context");
    } ଅନ୍ୟଥା ଯଦି (_this->GL_GetSwapInterval) {
        ଫେରନ୍ତୁ _this->GL_GetSwapInterval(_this, interval);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!(window->flags & SDL_WINDOW_OPENGL)) {
        ଫେରନ୍ତୁ SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    ଯଦି (SDL_GL_GetCurrentWindow() != window) {
        ଫେରନ୍ତୁ SDL_SetError("The specified window has not been made current");
    }

    ଫେରନ୍ତୁ _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("context");
    }

    ଯଦି (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ଖାଲି, ଖାଲି);
    }

    ଫେରନ୍ତୁ _this->GL_DestroyContext(_this, context);
}

#ଯଦି 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ସ୍ଥିର ଶୂନ୍ୟ Create_Mask_From_Color_ଚାବି_Or_Alpha(SDL_Surface *icon, Uint8 *mask, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    ବାଛ (SDL_BYTESPERPIXEL(icon->format)) {
    ସ୍ଥିତି 1:
        {
            Uint8 *pixels;
            ପାଇଁ (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                ପାଇଁ (x = 0; x < icon->w; ++x) {
                    ଯଦି (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି 2:
        {
            Uint16 *pixels;
            ପାଇଁ (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                ପାଇଁ (x = 0; x < icon->w; ++x) {
                    ଯଦି ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ଅନ୍ୟଥା ଯଦି ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        ଭାଙ୍ଗ;

    ସ୍ଥିତି 4:
        {
            Uint32 *pixels;
            ପାଇଁ (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                ପାଇଁ (x = 0; x < icon->w; ++x) {
                    ଯଦି ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ଅନ୍ୟଥା ଯଦି ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        ଭାଙ୍ଗ;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
ଶୂନ୍ୟ SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    ଯଦି (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        ଯଦି (mask == ଖାଲି) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask_len = icon->h * (icon->w + 7) / 8;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            ଯଦି (mask == ଖାଲି) {
                ଫେରନ୍ତୁ;
            }
            SDL_memset(mask, ~0, mask_len);
            ଯଦି (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ଯଦି (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ଯଦି (flags) {
                Create_Mask_From_Color_ଚାବି_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } ଅନ୍ୟଥା {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_ନିବେଶ_Type SDL_Get_Text_ନିବେଶ_Type(SDL_PropertiesID props)
{
    ଫେରନ୍ତୁ (SDL_Text_ନିବେଶ_Type)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_TEXTINPUT_TYPE_ସଂଖ୍ୟା, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_ନିବେଶ_Capitalization(SDL_PropertiesID props)
{
    ଯଦି (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ସଂଖ୍ୟା)) {
        ଫେରନ୍ତୁ (SDL_Capitalization)SDL_Get_ସଂଖ୍ୟା_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_ସଂଖ୍ୟା, SDL_CAPITALIZE_NONE);
    }

    ବାଛ (SDL_Get_Text_ନିବେଶ_Type(props)) {
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT:
        ଫେରନ୍ତୁ SDL_CAPITALIZE_SENTENCES;
    ସ୍ଥିତି SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ଫେରନ୍ତୁ SDL_CAPITALIZE_ଶବ୍ଦଗୁଡ଼ିକ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_ନିବେଶ_Autocorrect(SDL_PropertiesID props)
{
    ଫେରନ୍ତୁ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_ନିବେଶ_Multiline(SDL_PropertiesID props)
{
    ଯଦି (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ଫେରନ୍ତୁ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ଯଦି (SDL_GetHintBoolean(SDL_HINT_RETURN_ଚାବି_HIDES_IME, false)) {
        ଫେରନ୍ତୁ false;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ true;
    }
}

ସ୍ଥିର bool AutoShowingScreenKeyboard(ଶୂନ୍ୟ)
{
    ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ଯଦି (!hint) {
        // This hint is currently only used by the X11 video driver
        ଯଦି (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ଯଦି (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ଫେରନ୍ତୁ true;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ false;
    }
}

bool SDL_Start_Text_ନିବେଶ(SDL_Window *window)
{
    ଫେରନ୍ତୁ SDL_Start_Text_ନିବେଶ_With_Properties(window, 0);
}

bool SDL_Start_Text_ନିବେଶ_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (window->text_ନିବେଶ_props) {
        SDL_DestroyProperties(window->text_ନିବେଶ_props);
        window->text_ନିବେଶ_props = 0;
    }

    ଯଦି (props) {
        window->text_ନିବେଶ_props = SDL_CreateProperties();
        ଯଦି (!window->text_ନିବେଶ_props) {
            ଫେରନ୍ତୁ false;
        }
        ଯଦି (!SDL_CopyProperties(props, window->text_ନିବେଶ_props)) {
            ଫେରନ୍ତୁ false;
        }
    }

    ଯଦି (_this->Set_Text_ନିବେଶ_Properties) {
        _this->Set_Text_ନିବେଶ_Properties(_this, window, props);
    }

    ଯଦି (!window->text_ନିବେଶ_active) {
        // Start the text input system
        ଯଦି (_this->Start_Text_ନିବେଶ) {
            ଯଦି (!_this->Start_Text_ନିବେଶ(_this, window, props)) {
                ଫେରନ୍ତୁ false;
            }
        }
        window->text_ନିବେଶ_active = true;
    }

    // Show the on-screen keyboard, if desired
    ଯଦି (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        ଯଦି (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_Text_ନିବେଶ_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଫେରନ୍ତୁ window->text_ନିବେଶ_active;
}

bool SDL_Stop_Text_ନିବେଶ(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (window->text_ନିବେଶ_active) {
        // Stop the text input system
        ଯଦି (_this->Stop_Text_ନିବେଶ) {
            _this->Stop_Text_ନିବେଶ(_this, window);
        }
        window->text_ନିବେଶ_active = false;
    }

    // Hide the on-screen keyboard, if desired
    ଯଦି (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        ଯଦି (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_Set_Text_ନିବେଶ_Area(SDL_Window *window, ଅଚଳ SDL_Rect *rect, ପୂର୍ଣ୍ଣସଂଖ୍ୟା cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (rect) {
        SDL_copyp(&window->text_ନିବେଶ_rect, rect);
        window->text_ନିବେଶ_cursor = cursor;
    } ଅନ୍ୟଥା {
        SDL_zero(window->text_ନିବେଶ_rect);
        window->text_ନିବେଶ_cursor = 0;
    }

    ଯଦି (_this && _this->Update_Text_ନିବେଶ_Area) {
        ଯଦି (!_this->Update_Text_ନିବେଶ_Area(_this, window)) {
            ଫେରନ୍ତୁ false;
        }
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_Get_Text_ନିବେଶ_Area(SDL_Window *window, SDL_Rect *rect, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (rect) {
        SDL_copyp(rect, &window->text_ନିବେଶ_rect);
    }
    ଯଦି (cursor) {
        *cursor = window->text_ନିବେଶ_cursor;
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (_this->ClearComposition) {
        ଫେରନ୍ତୁ _this->ClearComposition(_this, window);
    }
    ଫେରନ୍ତୁ true;
}

bool SDL_HasScreenKeyboardSupport(ଶୂନ୍ୟ)
{
    ଯଦି (_this && _this->HasScreenKeyboardSupport) {
        ଫେରନ୍ତୁ _this->HasScreenKeyboardSupport(_this);
    }
    ଫେରନ୍ତୁ false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଫେରନ୍ତୁ _this->screen_keyboard_shown;
}

ଶୂନ୍ୟ SDL_SendScreenKeyboardShown(ଶୂନ୍ୟ)
{
    ଯଦି (!_this || _this->screen_keyboard_shown) {
        ଫେରନ୍ତୁ;
    }

    _this->screen_keyboard_shown = true;

    ଯଦି (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ଠେଲ_Event(&event);
    }
}

ଶୂନ୍ୟ SDL_SendScreenKeyboardHidden(ଶୂନ୍ୟ)
{
    ଯଦି (!_this || !_this->screen_keyboard_shown) {
        ଫେରନ୍ତୁ;
    }

    _this->screen_keyboard_shown = false;

    ଯଦି (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ଠେଲ_Event(&event);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_Get_Message_Box_ଗଣନା(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ SDL_GetAtomicInt(&SDL_messagebox_ଗଣନା);
}

bool SDL_ShowMessageBox(ଅଚଳ SDL_MessageBoxData *messageboxdata, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *buttonID)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ଫେରନ୍ତୁ SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    ଅକ୍ଷର *titlecpy = ଖାଲି;
    ଅକ୍ଷର *msgcpy = ଖାଲି;
    ଯଦି (messageboxdata->title) {
        ଅଚଳ size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(ଅକ୍ଷର, slen, &titleisstack);
        ଯଦି (!titlecpy) {
            ଫେରନ୍ତୁ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ଯଦି (messageboxdata->message) {
        ଅଚଳ size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(ଅକ୍ଷର, slen, &msgisstack);
        ଯଦି (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ଫେରନ୍ତୁ false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (ଶୂନ୍ୟ)SDL_AtomicIncRef(&SDL_messagebox_ଗଣନା);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    ଯଦି (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, ଆକାର(*messageboxdata));
    mbdata.title = titlecpy;
    ଯଦି (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    ଯଦି (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ଯଦି (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } ଅନ୍ୟଥା {
        // It's completely fine to call this function before video is initialized
        ଅଚଳ ଅକ୍ଷର *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ଯଦି (driver_name && *driver_name != 0) {
            ଅଚଳ ଅକ୍ଷର *driver_attempt = driver_name;
            ଯେତେବେଳେ (driver_attempt && (*driver_attempt != 0) && !result) {
                ଅଚଳ ଅକ୍ଷର *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; bootstrap[i]; ++i) {
                    ଯଦି (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ଯଦି (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        ଭାଙ୍ଗ;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ଖାଲି;
            }
        } ଅନ୍ୟଥା {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; bootstrap[i]; ++i) {
                ଯଦି (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    ଭାଙ୍ଗ;
                }
            }
        }
    }

    ଯଦି (!result) {
        ଅଚଳ ଅକ୍ଷର *error = SDL_GetError();

        ଯଦି (!*error) {
            SDL_SetError("No message system available");
        }
    } ଅନ୍ୟଥା {
        SDL_ClearError();
    }

    (ଶୂନ୍ୟ)SDL_AtomicDecRef(&SDL_messagebox_ଗଣନା);

    ଯଦି (current_window) {
        SDL_RaiseWindow(current_window);
    }

    ଯଦି (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ଫେରନ୍ତୁ result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ଅଚଳ ଅକ୍ଷର *title, ଅଚଳ ଅକ୍ଷର *message, SDL_Window *window)
{
#ଯଦି defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_ଡାହାଣ;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_ଡାହାଣ = gsp_Has_Gpu_ଡାହାଣ();
    ଯଦି (!has_Gpu_ଡାହାଣ)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    ଯଦି (!has_Gpu_ଡାହାଣ)
        gfxExit();

    ଫେରନ୍ତୁ true;
#ଅନ୍ୟଥା
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

    ଫେରନ୍ତୁ SDL_ShowMessageBox(&data, ଖାଲି);
#endif
}

bool SDL_ShouldAllowTopmost(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ଯଦି (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ଫେରନ୍ତୁ true;
    }

    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, ଶୂନ୍ୟ *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!_this->SetWindowHitTest) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    ଫେରନ୍ତୁ _this->SetWindowHitTest(window, callback != ଖାଲି);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ଫେରନ୍ତୁ SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    ଯଦି (!props) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ଯଦି (!surface) {
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା {
        surface = ଖାଲି;
    }

    ଯଦି (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (_this->UpdateWindowShape) {
        ଯଦି (!_this->UpdateWindowShape(_this, window, surface)) {
            ଫେରନ୍ତୁ false;
        }
    }
    ଫେରନ୍ତୁ true;
}

/*
 * Functions used by iOS application delegates
 */
ଶୂନ୍ୟ SDL_OnApplicationWillTerminate(ଶୂନ୍ୟ)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

ଶୂନ୍ୟ SDL_OnApplicationDidReceiveMemoryWarning(ଶୂନ୍ୟ)
{
    SDL_SendAppEvent(SDL_EVENT_ତଳ_MEMORY);
}

ଶୂନ୍ୟ SDL_OnApplicationWillEnterBackground(ଶୂନ୍ୟ)
{
    ଯଦି (_this) {
        SDL_Window *window;
        ପାଇଁ (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(ଖାଲି);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

ଶୂନ୍ୟ SDL_OnApplicationDidEnterBackground(ଶୂନ୍ୟ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

ଶୂନ୍ୟ SDL_OnApplicationWillEnterForeground(ଶୂନ୍ୟ)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

ଶୂନ୍ୟ SDL_OnApplicationDidEnterForeground(ଶୂନ୍ୟ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    ଯଦି (_this) {
        SDL_Window *window;
        ପାଇଁ (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ଅଚଳ ଅକ୍ଷର *path)
{
    bool result;

    ଯଦି (!_this) {
        ଫେରନ୍ତୁ SDL_UninitializedVideo();
    }
    ଯଦି (_this->vulkan_config.loader_loaded) {
        ଯଦି (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ଫେରନ୍ତୁ SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } ଅନ୍ୟଥା {
        ଯଦି (!_this->Vulkan_LoadLibrary) {
            ଫେରନ୍ତୁ SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    ଯଦି (result) {
        _this->vulkan_config.loader_loaded++;
    }
    ଫେରନ୍ତୁ result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯଦି (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

ଶୂନ୍ୟ SDL_Vulkan_UnloadLibrary(ଶୂନ୍ୟ)
{
    ଯଦି (!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ;
    }
    ଯଦି (_this->vulkan_config.loader_loaded > 0) {
        ଯଦି (--_this->vulkan_config.loader_loaded > 0) {
            ଫେରନ୍ତୁ;
        }
        ଯଦି (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

ଅକ୍ଷର ଅଚଳ * ଅଚଳ *SDL_Vulkan_GetInstanceExtensions(Uint32 *ଗଣନା_2)
{
    Uint32 tmpcount = 0;
    ଯଦି (!ଗଣନା_2) {
        ଗଣନା_2 = &tmpcount;
    }

    ଯଦି (!_this->Vulkan_GetInstanceExtensions) {
        *ଗଣନା_2 = 0;
        SDL_Unsupported();
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ _this->Vulkan_GetInstanceExtensions(_this, ଗଣନା_2);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    ଯଦି (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ଫେରନ୍ତୁ false;
    }

    CHECK_PARAM(!instance) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ଫେରନ୍ତୁ SDL_InvalidParamError("surface");
    }

    ଯଦି (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ଯଦି (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        ଯଦି (SDL_Vulkan_LoadLibrary(ଖାଲି)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ SDL_SetError("failed to load Vulkan library");
        }
    }

    ଫେରନ୍ତୁ _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

ଶୂନ୍ୟ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ଅଚଳ ସଂରଚନା VkAllocationCallbacks *allocator)
{
    ଯଦି (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ଫେରନ୍ତୁ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ଫେରନ୍ତୁ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (_this->Vulkan_GetPresentationSupport) {
        ଫେରନ୍ତୁ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ଫେରନ୍ତୁ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ଖାଲି);

    ଯଦି (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        ଯଦି (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ଯଦି (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    ଫେରନ୍ତୁ _this->Metal_CreateView(_this, window);
}

ଶୂନ୍ୟ SDL_Metal_DestroyView(SDL_MetalView view)
{
    ଯଦି (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

ଶୂନ୍ୟ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ଯଦି (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ଫେରନ୍ତୁ ଖାଲି;
        }
        ଫେରନ୍ତୁ _this->Metal_GetLayer(_this, view);
    } ଅନ୍ୟଥା {
        SDL_SetError("Metal is not supported.");
        ଫେରନ୍ତୁ ଖାଲି;
    }
}

#ଯଦି defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ଅଚଳ ଅକ୍ଷର *SDL_GetCSSCursorName(SDL_SystemCursor id, ଅଚଳ ଅକ୍ଷର **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    ବାଛ (id) {
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_DEFAULT:
        ଫେରନ୍ତୁ "default";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_TEXT:
        ଫେରନ୍ତୁ "text";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_WAIT:
        ଫେରନ୍ତୁ "wait";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CROSSHAIR:
        ଫେରନ୍ତୁ "crosshair";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_PROGRESS:
        ଫେରନ୍ତୁ "progress";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ଯଦି (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ଫେରନ୍ତୁ "nwse-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ଯଦି (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ଫେରନ୍ତୁ "nesw-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_EW_RESIZE:
        ଯଦି (fallback_name) {
            *fallback_name = "col-resize";
        }
        ଫେରନ୍ତୁ "ew-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NS_RESIZE:
        ଯଦି (fallback_name) {
            *fallback_name = "row-resize";
        }
        ଫେରନ୍ତୁ "ns-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_MOVE:
        ଯଦି (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ଫେରନ୍ତୁ "move";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ଫେରନ୍ତୁ "not-allowed";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_POINTER:
        ଫେରନ୍ତୁ "pointer";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NW_RESIZE:
        ଫେରନ୍ତୁ "nw-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_N_RESIZE:
        ଫେରନ୍ତୁ "n-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NE_RESIZE:
        ଫେରନ୍ତୁ "ne-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_E_RESIZE:
        ଫେରନ୍ତୁ "e-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SE_RESIZE:
        ଫେରନ୍ତୁ "se-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_S_RESIZE:
        ଫେରନ୍ତୁ "s-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SW_RESIZE:
        ଫେରନ୍ତୁ "sw-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_W_RESIZE:
        ଫେରନ୍ତୁ "w-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ଫେରନ୍ତୁ "context-menu";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_HELP:
        ଫେରନ୍ତୁ "help";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CELL:
        ଫେରନ୍ତୁ "cell";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ଫେରନ୍ତୁ "vertical-text";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALIAS:
        ଫେରନ୍ତୁ "alias";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COPY:
        ଫେରନ୍ତୁ "copy";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NO_DROP:
        ଫେରନ୍ତୁ "no-drop";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRAB:
        ଫେରନ୍ତୁ "grab";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRABBING:
        ଫେରନ୍ତୁ "grabbing";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COL_RESIZE:
        ଫେରନ୍ତୁ "col-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ଫେରନ୍ତୁ "row-resize";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ଯଦି (fallback_name) {
            *fallback_name = "move";
        }
        ଫେରନ୍ତୁ "all-scroll";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_IN:
        ଫେରନ୍ତୁ "zoom-in";

    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ଫେରନ୍ତୁ "zoom-out";

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ "default";
    }
}
#endif

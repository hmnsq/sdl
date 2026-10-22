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

// The high-level video driver subsystem

#ضمن "SDL_sysvideo.h"
#ضمن "SDL_clipboard_c.h"
#ضمن "SDL_egl_c.h"
#ضمن "SDL_surface_c.h"
#ضمن "SDL_pixels_c.h"
#ضمن "SDL_rect_c.h"
#ضمن "SDL_video_c.h"
#ضمن "../events/SDL_events_c.h"
#ضمن "../SDL_hints_c.h"
#ضمن "../SDL_properties_c.h"
#ضمن "../timer/SDL_timer_c.h"
#ضمن "../camera/SDL_camera_c.h"
#ضمن "../render/SDL_sysrender.h"
#ضمن "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#ضمن <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#ܐܢ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ܐܢ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles2.h>
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
#ضمن <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#ضمن <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ساكن VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_INPUT_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    عدم
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        ܦܢܐ result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ܦܢܐ result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        ܦܢܐ result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ܦܢܐ result;                                                  \
    }

#ܐܢ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
خارجي bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
خارجي bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
خارجي bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
خارجي bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
خارجي فراغ SDL_UpdateLifecycleObserver(فراغ);
#endif

ساكن فراغ SDL_CheckWindowDisplayChanged(SDL_Window *window);
ساكن فراغ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
ساكن فراغ SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
ساكن bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    ܐܢ (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

ساكن bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ܦܢܐ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ساكن bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ܦܢܐ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ساكن bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ܦܢܐ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ساكن bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ܦܢܐ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ساكن bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ܦܢܐ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ساكن bool syncHint;

ساكن فراغ SDL_SyncHintWatcher(فراغ *userdata, ثابت حرف *name, ثابت حرف *oldValue, ثابت حرف *newValue)
{
    syncHint = SDL_GetStringBoolean(newValue, false);
}

ساكن فراغ SDL_SyncIfRequired(SDL_Window *window)
{
    ܐܢ (syncHint) {
        SDL_SyncWindow(window);
    }
}

ساكن فراغ SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    ܐܢ (window->parent) {
        ܐܢ (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        ܐܢ (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } ܐܚܪܢܐ {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = عدم;
    }

    ܐܢ (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        ܐܢ (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

تعريفنوع بنية
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    فراغ *pixels;
    صحيح pitch;
    صحيح bytes_per_pixel;
} SDL_WindowTextureData;

ساكن Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#ܐܢ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ܐܢ (_this->GL_CreateContext) {
        ܦܢܐ SDL_WINDOW_OPENGL;
    }
#endif
#ܐܢ defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ܐܢ (_this->Metal_CreateView) {
        ܦܢܐ SDL_WINDOW_METAL;
    }
#endif
#ܐܢ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ܐܢ (SDL_strcmp(_this->name, "openvr") == 0) {
        ܦܢܐ SDL_WINDOW_OPENGL;
    }
#endif
    ܦܢܐ 0;
}

ساكن bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    ثابت bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    صحيح i;
    صحيح w, h;
    ثابت SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    ܐܢ (!data) {
        SDL_Renderer *renderer = عدم;
        ثابت حرف *render_driver = عدم;

        // See if there's a render driver being requested
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ܐܢ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ܐܢ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ܐܢ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = عدم;
        }

        حرف *render_driver_copy = عدم;
        ܐܢ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ܐܢ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                حرف *prev = render_driver_copy;
                حرف *ptr = prev;
                ܟܡܐ ((ptr = SDL_strchr(ptr, ',')) != عدم) {
                    *ptr = '\0';
                    ثابت bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ܐܢ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } ܐܚܪܢܐ {
                        ptr++;
                        prev = ptr;
                    }
                }

                ܐܢ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ܐܢ (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            ܐܢ (!renderer) {
                // The error for this specific renderer has already been set
                ܦܢܐ false;
            }
        } ܐܚܪܢܐ {
            SDL_assert(render_driver_copy == عدم);
            ثابت صحيح total = SDL_GetNumRenderDrivers();
            لكل (i = 0; i < total; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                ܐܢ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    ܐܢ (renderer) {
                        اكسر; // this will work.
                    }
                }
            }
            ܐܢ (!renderer) {
                ܦܢܐ SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != عدم); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, حجم(*data));
        ܐܢ (!data) {
            SDL_DestroyRenderer(renderer);
            ܦܢܐ false;
        }
        ܐܢ (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            ܦܢܐ false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, عدم);
    ܐܢ (!texture_formats) {
        ܦܢܐ false;
    }

    // Free any old texture and pixel data
    ܐܢ (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = عدم;
    }
    SDL_free(data->pixels);
    data->pixels = عدم;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    لكل (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ܐܢ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            اكسر;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    ܐܢ (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ܦܢܐ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ܐܢ (!data->pixels) {
            ܦܢܐ false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, عدم);

    ܦܢܐ true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحيح vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    ܐܢ (!data) {
        ܦܢܐ false;
    }
    ܐܢ (!data->renderer) {
        ܦܢܐ false;
    }
    ܦܢܐ SDL_SetRenderVSync(data->renderer, vsync);
}

ساكن bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحيح *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    ܐܢ (!data) {
        ܦܢܐ false;
    }
    ܐܢ (!data->renderer) {
        ܦܢܐ false;
    }
    ܦܢܐ SDL_GetRenderVSync(data->renderer, vsync);
}

ساكن bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    فراغ *src;
    صحيح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    ܐܢ (!data || !data->texture) {
        ܦܢܐ SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ܐܢ (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (فراغ *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        ܐܢ (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            ܦܢܐ false;
        }

        ܐܢ (!SDL_RenderTexture(data->renderer, data->texture, عدم, عدم)) {
            ܦܢܐ false;
        }

        SDL_RenderPresent(data->renderer);
    }
    ܦܢܐ true;
}

ساكن فراغ SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ܐܢ (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);

        ܐܢ (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        ܐܢ (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

ساكن SDL_VideoDevice *_this = عدم;
ساكن SDL_AtomicInt SDL_messagebox_count;

ساكن صحيح SDLCALL cmpmodes(ثابت فراغ *A, ثابت فراغ *B)
{
    ثابت SDL_DisplayMode *a = (ثابت SDL_DisplayMode *)A;
    ثابت SDL_DisplayMode *b = (ثابت SDL_DisplayMode *)B;
    صحيح a_refresh_rate = (صحيح)(a->refresh_rate * 100);
    صحيح b_refresh_rate = (صحيح)(b->refresh_rate * 100);
    صحيح a_pixel_density = (صحيح)(a->pixel_density * 100);
    صحيح b_pixel_density = (صحيح)(b->pixel_density * 100);

    ܐܢ (a->w != b->w) {
        ܦܢܐ b->w - a->w;
    } ܐܚܪܢܐ ܐܢ (a->h != b->h) {
        ܦܢܐ b->h - a->h;
    } ܐܚܪܢܐ ܐܢ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ܦܢܐ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ܐܚܪܢܐ ܐܢ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ܦܢܐ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ܐܚܪܢܐ ܐܢ (a_refresh_rate != b_refresh_rate) {
        ܦܢܐ b_refresh_rate - a_refresh_rate;
    } ܐܚܪܢܐ ܐܢ (a_pixel_density != b_pixel_density) {
        ܦܢܐ a_pixel_density - b_pixel_density;
    }
    ܦܢܐ 0;
}

bool SDL_UninitializedVideo(فراغ)
{
    ܦܢܐ SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ساكن ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحيح SDL_GetNumVideoDrivers(فراغ)
{
    ساكن صحيح num_drivers = -1;

    ܐܢ (num_drivers >= 0) {
        ܦܢܐ num_drivers;
    }

    num_drivers = 0;

    // Build a list of unique video drivers.
    لكل (صحيح i = 0; bootstrap[i] != عدم; ++i) {
        bool duplicate = false;
        لكل (صحيح j = 0; j < i; ++j) {
            ܐܢ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                اكسر;
            }
        }

        ܐܢ (!duplicate) {
            deduped_bootstrap[num_drivers++] = bootstrap[i];
        }
    }

    ܦܢܐ num_drivers;
}

ثابت حرف *SDL_GetVideoDriver(صحيح index)
{
    CHECK_PARAM(index < 0 || index >= SDL_GetNumVideoDrivers()) {
        SDL_InvalidParamError("index");
        ܦܢܐ عدم;
    }
    ܦܢܐ deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ثابت حرف *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    صحيح i = 0;

    // Check to make sure we don't overwrite '_this'
    ܐܢ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ܐܢ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        اذهب pre_driver_error;
    }
    init_events = true;
    ܐܢ (!SDL_InitKeyboard()) {
        اذهب pre_driver_error;
    }
    init_keyboard = true;
    ܐܢ (!SDL_PreInitMouse()) {
        اذهب pre_driver_error;
    }
    init_mouse = true;
    ܐܢ (!SDL_InitTouch()) {
        اذهب pre_driver_error;
    }
    init_touch = true;
    ܐܢ (!SDL_InitPen()) {
        اذهب pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = عدم;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ܐܢ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    ܐܢ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ܐܢ (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        ܟܡܐ (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            لكل (i = 0; bootstrap[i]; ++i) {
                ܐܢ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ܐܢ (video) {
                        اكسر;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : عدم;
        }
    } ܐܚܪܢܐ {
        لكل (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ܐܢ (video) {
                اكسر;
            }
        }
    }
    ܐܢ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ܐܚܪܢܐ {
        ܐܢ (driver_name) {
            SDL_SetError("%s not available", driver_name);
            اذهب pre_driver_error;
        }
        SDL_SetError("No available video device");
        اذهب pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = عدم;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    ܐܢ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ܦܢܐ false;
    }

    // Make sure some displays were added
    ܐܢ (_this->num_displays == 0) {
        SDL_QuitVideo();
        ܦܢܐ SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, عدم);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ܐܢ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ܦܢܐ true;

pre_driver_error:
    SDL_assert(_this == عدم);
    ܐܢ (init_pen) {
        SDL_QuitPen();
    }
    ܐܢ (init_touch) {
        SDL_QuitTouch();
    }
    ܐܢ (init_mouse) {
        SDL_QuitMouse();
    }
    ܐܢ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ܐܢ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ܦܢܐ false;
}

ثابت حرف *SDL_GetCurrentVideoDriver(فراغ)
{
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    ܦܢܐ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(فراغ)
{
    ܦܢܐ _this;
}

bool SDL_OnVideoThread(فراغ)
{
    ܦܢܐ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

فراغ SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    ܐܢ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(فراغ)
{
    ܐܢ (_this) {
        ܦܢܐ _this->system_theme;
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

فراغ SDL_UpdateDesktopBounds(فراغ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    ܐܢ (displays) {
        لكل (صحيح i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ܐܢ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ܐܢ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ܐܚܪܢܐ {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ساكن فراغ SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    ܐܢ (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    ܐܢ (mode->refresh_rate_numerator > 0) {
        ܐܢ (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (عائم)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } ܐܚܪܢܐ {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ثابت SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ܐܢ (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, حجم(display.desktop_mode));
    }
    ܦܢܐ SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحيح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(حجم(*new_display));
    ܐܢ (!new_display) {
        ܦܢܐ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->num_displays + 1) * حجم(*displays));
    ܐܢ (!displays) {
        SDL_free(new_display);
        ܦܢܐ 0;
    }
    _this->displays = displays;
    _this->displays[_this->num_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ܐܢ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ܐܚܪܢܐ {
        حرف name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ܐܢ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    لكل (i = 0; i < new_display->num_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    ܐܢ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ܦܢܐ id;
}

فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    لكل (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

فراغ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    صحيح display_index = SDL_GetDisplayIndex(displayID);
    ܐܢ (display_index < 0) {
        ܦܢܐ;
    }

    display = _this->displays[display_index];

    ܐܢ (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = عدم;
    SDL_free(display->internal);
    display->internal = عدم;
    SDL_free(display);

    ܐܢ (display_index < (_this->num_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->num_displays - display_index - 1) * حجم(_this->displays[display_index]));
    }
    --_this->num_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحيح *count)
{
    صحيح i;
    SDL_DisplayID *displays;

    ܐܢ (!_this) {
        ܐܢ (count) {
            *count = 0;
        }

        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->num_displays + 1) * حجم(*displays));
    ܐܢ (displays) {
        ܐܢ (count) {
            *count = _this->num_displays;
        }

        لكل (i = 0; i < _this->num_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ܐܚܪܢܐ {
        ܐܢ (count) {
            *count = 0;
        }
    }
    ܦܢܐ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحيح display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    ܐܢ (display_index < 0) {
        ܦܢܐ عدم;
    }
    ܦܢܐ _this->displays[display_index];
}

ساكن SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ܐܢ (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    ܐܢ (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    ܦܢܐ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ܦܢܐ SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(فراغ)
{
    ܐܢ (!_this || _this->num_displays == 0) {
        SDL_UninitializedVideo();
        ܦܢܐ 0;
    }
    ܦܢܐ _this->displays[0]->id;
}

صحيح SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    صحيح display_index;

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ -1;
    }

    لكل (display_index = 0; display_index < _this->num_displays; ++display_index) {
        ܐܢ (displayID == _this->displays[display_index]->id) {
            ܦܢܐ display_index;
        }
    }
    SDL_SetError("Invalid display");
    ܦܢܐ -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    ܦܢܐ display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ܦܢܐ SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ܐܢ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ܦܢܐ display->props;
}

ثابت حرف *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    ܦܢܐ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ܦܢܐ SDL_InvalidParamError("rect");
    }

    ܐܢ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ܐܢ (_this->GetDisplayBounds(_this, display, rect)) {
            ܦܢܐ true;
        }
    }

    // Assume that the displays are left to right
    ܐܢ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ܐܚܪܢܐ {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ܦܢܐ true;
}

ساكن صحيح ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ܦܢܐ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ܦܢܐ SDL_InvalidParamError("rect");
    }

    ܐܢ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ܦܢܐ true;
    }

    ܐܢ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ܐܢ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ܦܢܐ true;
        }
    }

    // Oh well, just give the entire display bounds.
    ܦܢܐ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ܐܢ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ܦܢܐ display->natural_orientation;
    } ܐܚܪܢܐ {
        // Default to landscape if the driver hasn't set it
        ܦܢܐ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ܐܢ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ܦܢܐ display->current_orientation;
    } ܐܚܪܢܐ {
        // Default to landscape if the driver hasn't set it
        ܦܢܐ SDL_ORIENTATION_LANDSCAPE;
    }
}

فراغ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, عائم scale)
{
    ܐܢ (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        لكل (window = _this->windows; window; window = window->next) {
            ܐܢ (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

عائم SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ܦܢܐ display->content_scale;
}

فراغ SDL_SetWindowHDRProperties(SDL_Window *window, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ܐܢ (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        ܐܢ (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

فراغ SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ثابت bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	ܐܢ (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ܐܢ (changed && !SDL_DriverSendsHDRChanges(_this)) {
        لكل (SDL_Window *w = display->device->windows; w; w = w->next) {
            ܐܢ (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ساكن فراغ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ܐܢ (display->num_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ساكن ثابت SDL_DisplayMode *SDL_GetFullscreenModeMatch(ثابت SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    ܐܢ (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ܦܢܐ عدم;
    }

    SDL_memcpy(&fullscreen_mode, mode, حجم(fullscreen_mode));
    ܐܢ (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = عدم;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    ܐܢ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ܐܢ (!mode) {
            لكل (صحيح i = 0; i < display->num_fullscreen_modes; ++i) {
                ܐܢ (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], حجم(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }

        // Search for a mode with the same characteristics
        ܐܢ (!mode) {
            لكل (صحيح i = 0; i < display->num_fullscreen_modes; ++i) {
                ܐܢ (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }
    }
    ܦܢܐ mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    صحيح i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, حجم(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->num_fullscreen_modes;
    لكل (i = 0; i < nmodes; ++i) {
        ܐܢ (cmpmodes(&new_mode, &modes[i]) == 0) {
            ܦܢܐ false;
        }
    }

    // Go ahead and add the new mode
    ܐܢ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        ܐܢ (!modes) {
            ܦܢܐ false;
        }

        ܐܢ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            لكل (i = 0; i < nmodes; ++i) {
                ܐܢ (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->num_fullscreen_modes++], &new_mode, حجم(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->num_fullscreen_modes,
              حجم(SDL_DisplayMode), cmpmodes);

    ܦܢܐ true;
}

فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحيح i;

    لكل (i = display->num_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = عدم;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = عدم;
    display->num_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحيح *count)
{
    صحيح i;
    صحيح num_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ܐܢ (count) {
        *count = 0;
    }

    CHECK_DISPLAY_MAGIC(display, عدم);

    SDL_UpdateFullscreenDisplayModes(display);

    num_modes = display->num_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((num_modes + 1) * حجم(*result) + num_modes * حجم(**result));
    ܐܢ (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((num_modes + 1) * حجم(*result)));
        ܐܢ (num_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, num_modes * حجم(*modes));
        }
        لكل (i = 0; i < num_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = عدم;

        ܐܢ (count) {
            *count = num_modes;
        }
    } ܐܚܪܢܐ {
        ܐܢ (count) {
            *count = 0;
        }
    }
    ܦܢܐ result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, صحيح w, صحيح h, عائم refresh_rate, bool include_high_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        ܦܢܐ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_DisplayMode *mode, *closest = عدم;
    عائم aspect_ratio;
    صحيح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    ܐܢ (h > 0) {
        aspect_ratio = (عائم)w / h;
    } ܐܚܪܢܐ {
        aspect_ratio = 1.0f;
    }

    ܐܢ (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    لكل (i = 0; i < display->num_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        ܐܢ (w > mode->w) {
            // Out of sorted modes large enough here
            اكسر;
        }
        ܐܢ (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            استمر;
        }
        ܐܢ (mode->pixel_density > 1.0f && !include_high_density_modes) {
            استمر;
        }
        ܐܢ (closest) {
            عائم current_aspect_ratio = (عائم)mode->w / mode->h;
            عائم closest_aspect_ratio = (عائم)closest->w / closest->h;
            ܐܢ (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                استمر;
            }

            ܐܢ (mode->w == closest->w && mode->h == closest->h) {
                ܐܢ (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    استمر;
                }
                ܐܢ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    استمر;
                }
            }
        }

        closest = mode;
    }
    ܐܢ (!closest) {
        ܦܢܐ SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    ܦܢܐ true;
}

ساكن bool DisplayModeChanged(ثابت SDL_DisplayMode *old_mode, ثابت SDL_DisplayMode *new_mode)
{
    ܦܢܐ ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

فراغ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ܐܢ (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ܦܢܐ;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    ܐܢ (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        ܐܢ (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ثابت SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    ܦܢܐ &display->desktop_mode;
}

فراغ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ܐܢ (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } ܐܚܪܢܐ {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    ܐܢ (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ثابت SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    ܦܢܐ display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ܐܢ (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ܦܢܐ true;
    }

    ܐܢ (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    ܐܢ (mode == display->current_mode) {
        ܦܢܐ true;
    }
#endif

    // Actually change the display mode
    ܐܢ (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        ܐܢ (!result) {
            ܦܢܐ false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ܦܢܐ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساكن فراغ SDL_GetClosestPointOnRect(ثابت SDL_Rect *rect, SDL_Point *point)
{
    ثابت صحيح right = rect->x + rect->w - 1;
    ثابت صحيح bottom = rect->y + rect->h - 1;

    ܐܢ (point->x < rect->x) {
        point->x = rect->x;
    } ܐܚܪܢܐ ܐܢ (point->x > right) {
        point->x = right;
    }

    ܐܢ (point->y < rect->y) {
        point->y = rect->y;
    } ܐܚܪܢܐ ܐܢ (point->y > bottom) {
        point->y = bottom;
    }
}

ساكن SDL_DisplayID GetDisplayForRect(صحيح x, صحيح y, صحيح w, صحيح h)
{
    صحيح i, dist;
    SDL_DisplayID closest = 0;
    صحيح closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    ܐܢ (_this) {
        لكل (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ܐܢ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, عدم)) {
                ܦܢܐ display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ܐܢ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ܐܢ (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    ܦܢܐ closest;
}

فراغ SDL_RelativeToGlobalForWindow(SDL_Window *window, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y)
{
    SDL_Window *w;

    ܐܢ (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        لكل (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            ܐܢ (!SDL_WINDOW_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    ܐܢ (abs_x) {
        *abs_x = rel_x;
    }
    ܐܢ (abs_y) {
        *abs_y = rel_y;
    }
}

فراغ SDL_GlobalToRelativeForWindow(SDL_Window *window, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y)
{
    SDL_Window *w;

    ܐܢ (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        لكل (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            ܐܢ (!SDL_WINDOW_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    ܐܢ (rel_x) {
        *rel_x = abs_x;
    }
    ܐܢ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ثابت SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ܦܢܐ 0;
    }

    ܦܢܐ GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ثابت SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ܦܢܐ 0;
    }

    ܦܢܐ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ساكن SDL_DisplayID GetDisplayAtOrigin(صحيح x, صحيح y)
{
    لكل (صحيح i = 0; i < _this->num_displays; ++i) {
        SDL_Rect rect;
        ثابت SDL_DisplayID cur_id = _this->displays[i]->id;
        ܐܢ (SDL_GetDisplayBounds(cur_id, &rect)) {
            ܐܢ (x == rect.x && y == rect.y) {
                ܦܢܐ cur_id;
            }
        }
    }

    ܦܢܐ 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    صحيح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    ܐܢ (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    ܐܢ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ܐܢ (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ܐܚܪܢܐ {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    ܐܢ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ܦܢܐ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, عدم);

    // An explicit fullscreen display overrides all
    ܐܢ (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ܐܢ (!displayID) {
        displayID = window->pending_displayID;
    }
    ܐܢ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحيح x = window->last_position_pending ? window->pending.x : window->x;
        ثابت صحيح y = window->last_position_pending ? window->pending.y : window->y;
        ثابت صحيح w = window->last_size_pending ? window->pending.w : window->w;
        ثابت صحيح h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ܐܢ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ܐܢ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ܦܢܐ SDL_GetVideoDisplay(displayID);
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
    ܐܢ (fs_display) {
        SDL_SetNumberProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ܐܚܪܢܐ {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ܦܢܐ GetDisplayForWindow(window);
}

ساكن فراغ SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    ܐܢ (SDL_SendsDisplayChanges(_this)) {
        ܦܢܐ;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    ܐܢ (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        ܐܢ (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            ܐܢ (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                صحيح old_area = old_overlap.w * old_overlap.h;
                صحيح new_area = new_overlap.w * new_overlap.h;
                عائم new_overlap_ratio = (new_area / ((عائم)old_area + new_area));
                ܐܢ (new_overlap_ratio < 0.80) {
                    ܦܢܐ;
                }
            }
        }
    }

    ܐܢ (displayID != window->displayID) {
        صحيح i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        لكل (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ܐܢ (display->fullscreen_window == window) {
                ܐܢ (display_index != i) {
                    ܐܢ (display_index < 0) {
                        display_index = i;
                    } ܐܚܪܢܐ {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        ܐܢ (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = عدم;
                    }
                }
                اكسر;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (صحيح)displayID, 0);
    }
}

عائم SDL_GetWindowPixelDensity(SDL_Window *window)
{
    صحيح window_w, window_h, pixel_w, pixel_h;
    عائم pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    ܐܢ (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (عائم)pixel_w / window_w;
    }
    ܦܢܐ pixel_density;
}

عائم SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ܦܢܐ window->display_scale;
}

ساكن فراغ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    عائم display_scale;

    ܐܢ (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } ܐܚܪܢܐ {
        ثابت عائم pixel_density = SDL_GetWindowPixelDensity(window);
        ثابت عائم content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    ܐܢ (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = عدم;
    SDL_DisplayMode *mode = عدم;
    صحيح i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    ܐܢ (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ܐܢ (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        ܐܢ (!display) {
            // This should never happen, but it did...
            اذهب done;
        }
    } ܐܚܪܢܐ {
        لكل (i = 0; i < _this->num_displays; ++i) {
            display = _this->displays[i];
            ܐܢ (display->fullscreen_window == window) {
                اكسر;
            }
        }
        ܐܢ (!display || i == _this->num_displays) {
            // Already not fullscreen on any display
            display = عدم;
        }
    }

    ܐܢ (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        ܐܢ (mode) {
            window->fullscreen_exclusive = true;
        } ܐܚܪܢܐ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#ܐܢ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ܐܢ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ܐܢ (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            ܐܢ (display) {
                display->fullscreen_window = عدم;
            }
            اذهب done;
        }
        ܐܢ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ܐܢ (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                ܐܢ (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    اذهب error;
                }
            } ܐܚܪܢܐ ܐܢ (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                لكل (i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    ܐܢ (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, عدم);
                        ܐܢ (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = عدم;
                    }
                }
            }

            ܐܢ (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                اذهب done;
            }
        }
    }
#endif

    ܐܢ (display) {
        // Restore the video mode on other displays if needed
        لكل (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ܐܢ (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, عدم);
                other->fullscreen_window = عدم;
            }
        }
    }

    ܐܢ (fullscreen) {
        صحيح mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ܐܢ (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        ܐܢ (!SDL_SetDisplayModeForDisplay(display, mode)) {
            اذهب error;
        }
        ܐܢ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ܐܢ (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } ܐܚܪܢܐ {
                resized = true;
            }

            ܐܢ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ܐܢ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } ܐܚܪܢܐ ܐܢ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                اذهب error;
            }
        }

        ܐܢ (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ܐܢ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ܐܢ (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } ܐܚܪܢܐ {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ܐܢ (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                ܐܢ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } ܐܚܪܢܐ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } ܐܚܪܢܐ {
        bool resized = false;

        // Restore the desktop mode
        ܐܢ (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, عدم);
        }
        ܐܢ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ܐܢ (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                ܐܢ (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ܐܚܪܢܐ {
                resized = true;
            }

            ܐܢ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ܐܢ (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } ܐܚܪܢܐ ܐܢ (ret == SDL_FULLSCREEN_FAILED) {
                اذهب error;
            }
        }

        ܐܢ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            ܐܢ (display) {
                display->fullscreen_window = عدم;
            }

            ܐܢ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                ܐܢ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } ܐܚܪܢܐ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    ܦܢܐ true;

error:
    ܐܢ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ܦܢܐ false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ثابت SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (mode) {
        ܐܢ (!SDL_GetFullscreenModeMatch(mode)) {
            ܦܢܐ SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } ܐܚܪܢܐ {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#ܐܢ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ܐܢ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    ܐܢ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    ܦܢܐ true;
}

ثابت SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);
    CHECK_WINDOW_NOT_POPUP(window, عدم);

    ܐܢ (window->flags & SDL_WINDOW_FULLSCREEN) {
        ܦܢܐ SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

فراغ *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    ܐܢ (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ܦܢܐ عدم;
    }
    ܦܢܐ _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ثابت SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    ܐܢ (mode) {
        ܦܢܐ mode->format;
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

ساكن SDL_INLINE bool IsAcceptingDragAndDrop(فراغ)
{
    ܐܢ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

// prepare a newly-created window
ساكن SDL_INLINE فراغ PrepareDragAndDropSupport(SDL_Window *window)
{
    ܐܢ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
فراغ SDL_ToggleDragAndDropSupport(فراغ)
{
    ܐܢ (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        لكل (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(صحيح *count)
{
    ܐܢ (count) {
        *count = 0;
    }

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }

    SDL_Window *window;
    صحيح num_added = 0;
    صحيح num_windows = 0;
    لكل (window = _this->windows; window; window = window->next) {
        ++num_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((num_windows + 1) * حجم(*windows));
    ܐܢ (!windows) {
        ܦܢܐ عدم;
    }

    لكل (window = _this->windows; window; window = window->next) {
        windows[num_added++] = window;
        ܐܢ (num_added == num_windows) {
            // Race condition? Multi-threading not supported, ignore it
            اكسر;
        }
    }
    windows[num_added] = عدم;

    ܐܢ (count) {
        *count = num_added;
    }
    ܦܢܐ windows;
}

ساكن فراغ ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    ܐܢ (!SDL_WINDOW_IS_POPUP(window)) {
        ܐܢ (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        ܐܢ (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        ܐܢ (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        ܐܢ (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        ܐܢ (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        ܐܢ (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

ساكن فراغ SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    ܐܢ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ܐܚܪܢܐ {
        ApplyWindowFlags(window, flags);
        ܐܢ (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#ܐܢ defined(SDL_PLATFORM_LINUX)
    ܐܢ (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_SetWindowProgressValue(window, 0.0f);
    }
#endif
}

ساكن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    ܦܢܐ SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساكن bool SDL_DllNotSupported(ثابت حرف *name)
{
    ܦܢܐ SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ساكن بنية {
    ثابت حرف *property_name;
    SDL_WindowFlags flag;
    bool invert_value;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_TOP,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_HIGH_PIXEL_DENSITY,  false },
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

ساكن SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, 0);

    لكل (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        ܐܢ (SDL_WindowFlagProperties[i].invert_value) {
            ܐܢ (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } ܐܚܪܢܐ {
            ܐܢ (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    ܦܢܐ flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ثابت حرف *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, عدم);
    صحيح x = (صحيح)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    صحيح y = (صحيح)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    صحيح w = (صحيح)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 0);
    صحيح h = (صحيح)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, عدم);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    ܐܢ (!_this) {
        // Initialize the video system if needed
        ܐܢ (!SDL_Init(SDL_INIT_VIDEO)) {
            ܦܢܐ عدم;
        }

        // Make clang-tidy happy
        ܐܢ (!_this) {
            ܦܢܐ عدم;
        }
    }

    ܐܢ ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ܦܢܐ عدم;
    }

    ܐܢ ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        ܐܢ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ܦܢܐ عدم;
        }

        // Tooltip and popup menu window must specify a parent window
        ܐܢ (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ܦܢܐ عدم;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    ܐܢ (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned صحيح)type_flags);
        ܦܢܐ عدم;
    }

    // Make sure the display list is up to date for window placement
    ܐܢ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ܐܢ (w < 1) {
        w = 1;
    }
    ܐܢ (h < 1) {
        h = 1;
    }

    ܐܢ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ܐܢ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ܐܚܪܢܐ ܐܢ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ܐܢ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ܐܢ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ܐܢ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ܐܢ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ܐܢ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ܐܢ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ܐܢ (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned صحيح)graphics_flags);
        ܦܢܐ عدم;
    }

    // Some platforms have certain graphics backends enabled by default
    ܐܢ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ܐܢ (flags & SDL_WINDOW_OPENGL) {
        ܐܢ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ܦܢܐ عدم;
        }
        ܐܢ (!SDL_GL_LoadLibrary(عدم)) {
            ܦܢܐ عدم;
        }
    }

    ܐܢ (flags & SDL_WINDOW_VULKAN) {
        ܐܢ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ܦܢܐ عدم;
        }
        ܐܢ (!SDL_Vulkan_LoadLibrary(عدم)) {
            ܦܢܐ عدم;
        }
    }

    ܐܢ (flags & SDL_WINDOW_METAL) {
        ܐܢ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ܦܢܐ عدم;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, حجم(*window));
    ܐܢ (!window) {
        ܦܢܐ عدم;
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
    ܐܢ (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    ܐܢ (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    ܐܢ (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ܐܢ (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    ܐܢ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_PushError();
        SDL_DestroyWindow(window);
        SDL_PopError();
        ܦܢܐ عدم;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ܐܢ !defined(SDL_PLATFORM_WINDOWS)
    ܐܢ (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    ܐܢ (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ܦܢܐ window;
}

SDL_Window *SDL_CreateWindow(ثابت حرف *title, صحيح w, صحيح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    ܐܢ (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ܦܢܐ window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, صحيح offset_x, صحيح offset_y, صحيح w, صحيح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ܐܢ (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ܦܢܐ عدم;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, offset_x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, offset_y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ܦܢܐ window;
}

ساكن bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ܐܢ (!_this->ReconfigureWindow) {
        ܦܢܐ false;
    }

    ثابت SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ܐܢ (graphics_flags & (graphics_flags - 1)) {
        ܦܢܐ SDL_SetError("Conflicting window flags specified");
    }

    ܐܢ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ܦܢܐ SDL_ContextNotSupported("OpenGL");
    }
    ܐܢ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ܦܢܐ SDL_ContextNotSupported("Vulkan");
    }
    ܐܢ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ܦܢܐ SDL_ContextNotSupported("Metal");
    }

    ܐܢ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ܐܢ (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ܐܢ (!_this->ReconfigureWindow(_this, window, 0)) {
            ܦܢܐ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ܐܢ (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ܐܢ (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    ܐܢ (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(عدم);
        ܐܢ (!loaded_opengl) {
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ ܐܢ (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(عدم);
        ܐܢ (!loaded_vulkan) {
            ܦܢܐ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ܐܢ (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        ܐܢ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ܐܢ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ܦܢܐ false;
    }

    window->flags |= graphics_flags;

    ܦܢܐ true;
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
    ܐܢ (graphics_flags & (graphics_flags - 1)) {
        ܦܢܐ SDL_SetError("Conflicting window flags specified");
    }

    ܐܢ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ܦܢܐ SDL_ContextNotSupported("OpenGL");
    }
    ܐܢ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ܦܢܐ SDL_ContextNotSupported("Vulkan");
    }
    ܐܢ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ܦܢܐ SDL_ContextNotSupported("Metal");
    }

    ܐܢ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } ܐܚܪܢܐ {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ܐܢ (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    ܐܢ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ثابت bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    ܐܢ ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        ܐܢ (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } ܐܚܪܢܐ {
            need_gl_unload = true;
        }
    } ܐܚܪܢܐ ܐܢ (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    ܐܢ ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        ܐܢ (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } ܐܚܪܢܐ {
            need_vulkan_unload = true;
        }
    } ܐܚܪܢܐ ܐܢ (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    ܐܢ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ܐܢ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ܐܢ (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    ܐܢ (need_gl_load) {
        ܐܢ (!SDL_GL_LoadLibrary(عدم)) {
            ܦܢܐ false;
        }
        loaded_opengl = true;
    }

    ܐܢ (need_vulkan_load) {
        ܐܢ (!SDL_Vulkan_LoadLibrary(عدم)) {
            ܦܢܐ false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    ܐܢ (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        ܐܢ (!_this->CreateSDLWindow(_this, window, 0)) {
            ܐܢ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            ܐܢ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            ܦܢܐ false;
        }
    }

    ܐܢ (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    ܐܢ (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    ܐܢ (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    ܐܢ (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    ܐܢ (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    ܐܢ (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    ܐܢ (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ܦܢܐ true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ܐܢ (!SDL_ReconfigureWindowInternal(window, flags)) {
        ܦܢܐ SDL_RecreateWindow(window, flags);
    }

    ܦܢܐ true;
}

bool SDL_HasWindows(فراغ)
{
    ܦܢܐ _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ܦܢܐ window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    ܐܢ (id) {
        لكل (window = _this->windows; window; window = window->next) {
            ܐܢ (window->id == id) {
                ܦܢܐ window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ܦܢܐ عدم;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    ܦܢܐ window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ܐܢ (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ܦܢܐ window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ܦܢܐ window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ثابت حرف *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (title == window->title) {
        ܦܢܐ true;
    }
    ܐܢ (!title) {
        title = "";
    }
    ܐܢ (window->title && SDL_strcmp(title, window->title) == 0) {
        ܦܢܐ true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    ܐܢ (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ܦܢܐ true;
}

ثابت حرف *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ܦܢܐ window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ܦܢܐ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ܐܢ (!window->icon) {
        ܦܢܐ false;
    }

    ܐܢ (!_this->SetWindowIcon) {
        ܦܢܐ SDL_Unsupported();
    }

    ܦܢܐ _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, صحيح x, صحيح y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ثابت صحيح w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ثابت صحيح h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    ܐܢ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    ܐܢ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    ܐܢ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ܐܢ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ܐܚܪܢܐ ܐܢ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ܐܢ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        ܐܢ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ܐܢ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ܦܢܐ false;
            }
        }
        ܐܢ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ܐܢ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ܐܚܪܢܐ {
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
    ܐܢ (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    ܐܢ (_this->SetWindowPosition) {
        ثابت bool result = _this->SetWindowPosition(_this, window);
        ܐܢ (result) {
            SDL_SyncIfRequired(window);
        }
        ܦܢܐ result;
    }

    ܦܢܐ SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, صحيح *x, صحيح *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ܐܚܪܢܐ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    ܐܢ (use_display_origin) {
        SDL_DisplayID displayID;

        ܐܢ (x) {
            *x = 0;
        }
        ܐܢ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        ܐܢ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ܐܢ (x) {
                *x = bounds.x;
            }
            ܐܢ (y) {
                *y = bounds.y;
            }
        }
    } ܐܚܪܢܐ {
        ثابت bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        ܐܢ (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        ܐܢ (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ܦܢܐ true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (!_this->SetWindowBordered) {
        ܦܢܐ SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    ܐܢ (want != have) {
        ܐܢ (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } ܐܚܪܢܐ {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ܦܢܐ true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (!_this->SetWindowResizable) {
        ܦܢܐ SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    ܐܢ (want != have) {
        ܐܢ (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ܐܚܪܢܐ {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ܦܢܐ true;
}

bool SDL_SetWindowAlwaysOnTop(SDL_Window *window, bool on_top)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (!_this->SetWindowAlwaysOnTop) {
        ܦܢܐ SDL_Unsupported();
    }

    ثابت bool want = on_top;
    ثابت bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_TOP) != 0);
    ܐܢ (want != have) {
        ܐܢ (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        } ܐܚܪܢܐ {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_TOP;
        }
        _this->SetWindowAlwaysOnTop(_this, window, want);
    }

    ܦܢܐ true;
}

bool SDL_SetWindowSize(SDL_Window *window, صحيح w, صحيح h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ܦܢܐ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ܦܢܐ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    عائم new_aspect = w / (عائم)h;
    ܐܢ (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (صحيح)SDL_roundf(h * window->max_aspect);
    } ܐܚܪܢܐ ܐܢ (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (صحيح)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ܐܢ (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    ܐܢ (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    ܐܢ (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    ܐܢ (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    ܐܢ (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_Unsupported();
    }
    ܦܢܐ true;
}

bool SDL_GetWindowSize(SDL_Window *window, صحيح *w, صحيح *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ܐܢ (w) {
        *w = window->w;
    }
    ܐܢ (h) {
        *h = window->h;
    }
    ܦܢܐ true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, عائم min_aspect, عائم max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    ܐܢ (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    ܦܢܐ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, عائم *min_aspect, عائم *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    ܐܢ (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ܦܢܐ true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, صحيح *top, صحيح *left, صحيح *bottom, صحيح *right)
{
    صحيح dummy = 0;

    ܐܢ (!top) {
        top = &dummy;
    }
    ܐܢ (!left) {
        left = &dummy;
    }
    ܐܢ (!right) {
        right = &dummy;
    }
    ܐܢ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *top = *left = *bottom = *right = 0;

    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!_this->GetWindowBordersSize) {
        ܦܢܐ SDL_Unsupported();
    }

    ܦܢܐ _this->GetWindowBordersSize(_this, window, top, left, bottom, right);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, صحيح *w, صحيح *h)
{
    صحيح filter;

    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!w) {
        w = &filter;
    }

    ܐܢ (!h) {
        h = &filter;
    }

    ܐܢ (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } ܐܚܪܢܐ {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ثابت SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        ܐܢ ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } ܐܚܪܢܐ {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        ܐܢ (mode) {
            *w = (صحيح)SDL_ceilf(*w * mode->pixel_density);
            *h = (صحيح)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ܦܢܐ true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, صحيح min_w, صحيح min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ܦܢܐ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ܦܢܐ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ܦܢܐ SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    ܐܢ (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    ܦܢܐ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, صحيح *min_w, صحيح *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ܐܢ (min_w) {
        *min_w = window->min_w;
    }
    ܐܢ (min_h) {
        *min_h = window->min_h;
    }
    ܦܢܐ true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, صحيح max_w, صحيح max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ܦܢܐ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ܦܢܐ SDL_InvalidParamError("max_h");
    }

    ܐܢ ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ܦܢܐ SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    ܐܢ (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    ܦܢܐ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, صحيح *max_w, صحيح *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ܐܢ (max_w) {
        *max_w = window->max_w;
    }
    ܐܢ (max_h) {
        *max_h = window->max_h;
    }
    ܦܢܐ true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ܦܢܐ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ܐܢ (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ܦܢܐ true;
    }

    ܐܢ (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } ܐܚܪܢܐ {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    لكل (child = window->first_child; child; child = child->next_sibling) {
        ܐܢ (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            اكسر;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ܦܢܐ true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ܦܢܐ true;
    }

    // Hide all child windows
    لكل (child = window->first_child; child; child = child->next_sibling) {
        ܐܢ (child->flags & SDL_WINDOW_HIDDEN) {
            اكسر;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    ܐܢ (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } ܐܚܪܢܐ {
        SDL_SetMouseFocus(عدم);
        SDL_SetKeyboardFocus(عدم);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ܦܢܐ true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        ܦܢܐ true;
    }
    ܐܢ (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ܦܢܐ true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (!_this->MaximizeWindow) {
        ܦܢܐ SDL_Unsupported();
    }

    ܐܢ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ܦܢܐ SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ܦܢܐ true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ܦܢܐ true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (!_this->MinimizeWindow) {
        ܦܢܐ SDL_Unsupported();
    }

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ܦܢܐ true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ܦܢܐ true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (!_this->RestoreWindow) {
        ܦܢܐ SDL_Unsupported();
    }

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ܦܢܐ true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ܦܢܐ true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        ܐܢ (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } ܐܚܪܢܐ {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ܦܢܐ true;
    }

    ܐܢ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ܐܢ (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    ܐܢ (result) {
        SDL_SyncIfRequired(window);
    }

    ܦܢܐ result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (_this->SyncWindow) {
        ܦܢܐ _this->SyncWindow(_this, window);
    } ܐܚܪܢܐ {
        ܦܢܐ true;
    }
}

ساكن bool ShouldAttemptTextureFramebuffer(فراغ)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ܐܢ (!_this->CreateWindowFramebuffer) {
        ܦܢܐ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ܐܢ (hint && *hint) {
        ܐܢ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ܐܚܪܢܐ {
            attempt_texture_framebuffer = true;
        }
    } ܐܚܪܢܐ {
        ܐܢ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ܐܚܪܢܐ {
            attempt_texture_framebuffer = false;
        }
    }
    ܦܢܐ attempt_texture_framebuffer;
}

ساكن SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    فراغ *pixels = عدم;
    صحيح pitch = 0;
    bool created_framebuffer = false;
    صحيح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    ܐܢ (!_this->checked_texture_framebuffer) {
        ܐܢ (ShouldAttemptTextureFramebuffer()) {
            ܐܢ (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ܐܚܪܢܐ {
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

    ܐܢ (!created_framebuffer) {
        ܐܢ (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            ܦܢܐ عدم;
        }

        ܐܢ (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ܦܢܐ عدم;
        }
    }

    ܐܢ (window->surface) {
        // We may have gone recursive and already created the surface
        ܦܢܐ window->surface;
    }

    ܦܢܐ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܦܢܐ window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    ܐܢ (!window->surface_valid) {
        ܐܢ (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = عدم;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        ܐܢ (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ܦܢܐ window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, صحيح vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!_this->SetWindowFramebufferVSync) {
        ܦܢܐ SDL_Unsupported();
    }
    ܦܢܐ _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, صحيح *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!_this->GetWindowFramebufferVSync) {
        ܦܢܐ SDL_Unsupported();
    }
    ܦܢܐ _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    ܦܢܐ SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ثابت SDL_Rect *rects,
                                 صحيح numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!window->surface_valid) {
        ܦܢܐ SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ܦܢܐ _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = عدم;
        window->surface_valid = false;
    }

    ܐܢ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ܐܢ (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ܦܢܐ true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, عائم opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!_this->SetWindowOpacity) {
        ܦܢܐ SDL_Unsupported();
    }

    ܐܢ (opacity < 0.0f) {
        opacity = 0.0f;
    } ܐܚܪܢܐ ܐܢ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    ܐܢ (result) {
        window->opacity = opacity;
    }

    ܦܢܐ result;
}

عائم SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ܦܢܐ window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    ܐܢ (window == parent) {
        ܦܢܐ SDL_SetError("Cannot set the parent of a window to itself.");
    }

    ܐܢ (!_this->SetWindowParent) {
        ܦܢܐ SDL_Unsupported();
    }

    ܐܢ (window->flags & SDL_WINDOW_MODAL) {
        ܦܢܐ SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ܐܢ (window->parent == parent) {
        ܦܢܐ true;
    }

    ثابت bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : عدم);

    ܦܢܐ ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (!_this->SetWindowModal) {
        ܦܢܐ SDL_Unsupported();
    }

    ܐܢ (modal) {
        ܐܢ (!window->parent) {
            ܦܢܐ SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } ܐܚܪܢܐ ܐܢ (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } ܐܚܪܢܐ {
        ܦܢܐ true; // Already not modal, so nothing to do.
    }

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        ܦܢܐ true;
    }

    ܦܢܐ _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_INPUT_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ܟܡܐ (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ܐܢ (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_INPUT_FOCUS);
        }
    }

    *new_focus = focus;
    ܦܢܐ set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    لكل (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    لكل (w = current_focus; w != toplevel_parent; w = w->parent) {
        ܐܢ (w == window) {
            found_higher_focus = true;
            اكسر;
        }
    }

    ܦܢܐ !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    ܐܢ ((want != have) && (_this->SetWindowFocusable)) {
        ܐܢ (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } ܐܚܪܢܐ {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        ܐܢ (!_this->SetWindowFocusable(_this, window, want)) {
            ܦܢܐ false;
        }
    }

    ܦܢܐ true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    ܐܢ ((want != have) && (_this->SetWindowFillDocument)) {
        ܐܢ (!_this->SetWindowFillDocument(_this, window, want)) {
            ܦܢܐ false;
        } ܐܚܪܢܐ ܐܢ (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } ܐܚܪܢܐ {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ܦܢܐ true;
}

فراغ SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    ܐܢ (window->flags & SDL_WINDOW_INPUT_FOCUS) {
        ܐܢ (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ܐܚܪܢܐ {
            mouse_grabbed = false;
        }

        ܐܢ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ܐܚܪܢܐ {
            keyboard_grabbed = false;
        }
    } ܐܚܪܢܐ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ܐܢ (mouse_grabbed || keyboard_grabbed) {
        ܐܢ (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            ܐܢ (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            ܐܢ (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } ܐܚܪܢܐ ܐܢ (_this->grabbed_window == window) {
        _this->grabbed_window = عدم; // ungrabbing input.
    }

    ܐܢ (_this->SetWindowMouseGrab) {
        ܐܢ (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    ܐܢ (_this->SetWindowKeyboardGrab) {
        ܐܢ (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    ܐܢ (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = عدم;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        ܐܢ (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } ܐܚܪܢܐ {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        ܦܢܐ true;
    }

    ܐܢ (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ܦܢܐ true;
    }
    ܐܢ (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } ܐܚܪܢܐ {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ܐܢ (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ܦܢܐ false;
    }
    ܦܢܐ true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (window->flags & SDL_WINDOW_HIDDEN) {
        ܐܢ (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } ܐܚܪܢܐ {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        ܦܢܐ true;
    }

    ܐܢ (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ܦܢܐ true;
    }
    ܐܢ (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } ܐܚܪܢܐ {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ܐܢ (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ܦܢܐ false;
    }
    ܦܢܐ true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ܦܢܐ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ܦܢܐ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(فراغ)
{
    ܐܢ (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ܦܢܐ _this->grabbed_window;
    } ܐܚܪܢܐ {
        ܦܢܐ عدم;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ثابت SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!_this->SetWindowMouseRect) {
        ܦܢܐ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ܐܢ (!rect) {
        rect = &zero;
    }

    ܐܢ (SDL_memcmp(&window->mouse_rect, rect, حجم(*rect)) == 0) {
        ܦܢܐ true;
    }
    SDL_memcpy(&window->mouse_rect, rect, حجم(*rect));

    ܦܢܐ _this->SetWindowMouseRect(_this, window);
}

ثابت SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    ܐܢ (SDL_RectEmpty(&window->mouse_rect)) {
        ܦܢܐ عدم;
    } ܐܚܪܢܐ {
        ܦܢܐ &window->mouse_rect;
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

    ܐܢ (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        ܦܢܐ true;
    }

    ܐܢ (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } ܐܚܪܢܐ {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    ܐܢ (!SDL_UpdateRelativeMouseMode()) {
        ܐܢ (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } ܐܚܪܢܐ {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        ܦܢܐ false;
    }
    ܦܢܐ true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ܦܢܐ true;
    } ܐܚܪܢܐ {
        ܦܢܐ false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (_this->FlashWindow) {
        ܦܢܐ _this->FlashWindow(_this, window, operation);
    }

    ܦܢܐ SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ܦܢܐ SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    ܐܢ (_this->ApplyWindowProgress) {
        ܐܢ (!_this->ApplyWindowProgress(_this, window)) {
            ܦܢܐ false;
        }
    }

    ܦܢܐ true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ܦܢܐ window->progress_state;
}

bool SDL_SetWindowProgressValue(SDL_Window *window, عائم value)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    value = SDL_clamp(value, 0.0f, 1.f);

    window->progress_value = value;

    ܐܢ (_this->ApplyWindowProgress) {
        ܐܢ (!_this->ApplyWindowProgress(_this, window)) {
            ܦܢܐ false;
        }
    }

    ܦܢܐ true;
}

عائم SDL_GetWindowProgressValue(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ܦܢܐ window->progress_value;
}

فراغ SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

فراغ SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

فراغ SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    ܐܢ (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ثابت bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        ܐܢ (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_high_density_modes = false;

            ܐܢ (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_high_density_modes = true;
            }
            ثابت bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_high_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ܐܢ (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } ܐܚܪܢܐ {
            SDL_zero(window->current_fullscreen_mode);
        }

        ܐܢ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

فراغ SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

فراغ SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    ܐܢ ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, عدم);
        ܐܢ (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

فراغ SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    صحيح pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

فراغ SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

فراغ SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    ܐܢ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ܐܚܪܢܐ {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ساكن فراغ SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_left;
    rect.y = window->safe_inset_top;
    rect.w = window->w - (window->safe_inset_right + window->safe_inset_left);
    rect.h = window->h - (window->safe_inset_top + window->safe_inset_bottom);
    ܐܢ (SDL_memcmp(&rect, &window->safe_rect, حجم(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

فراغ SDL_SetWindowSafeAreaInsets(SDL_Window *window, صحيح left, صحيح right, صحيح top, صحيح bottom)
{
    window->safe_inset_left = left;
    window->safe_inset_right = right;
    window->safe_inset_top = top;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    ܐܢ (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (rect) {
        ܐܢ (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } ܐܚܪܢܐ {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    ܦܢܐ true;
}

فراغ SDL_OnWindowMinimized(SDL_Window *window)
{
    ܐܢ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

فراغ SDL_OnWindowMaximized(SDL_Window *window)
{
}

فراغ SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    ܐܢ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

فراغ SDL_OnWindowEnter(SDL_Window *window)
{
    ܐܢ (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

فراغ SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

فراغ SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ܐܢ (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

ساكن bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ثابت حرف *hint;

    ܐܢ (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ܦܢܐ false;
    }

#ܐܢ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ܐܢ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ܐܢ (Cocoa_IsShowingModalDialog(window)) {
            ܦܢܐ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ܐܚܪܢܐ ܐܢ (Cocoa_IsWindowInFullscreenSpace(window)) {
            ܦܢܐ false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        خارجي bool Android_JNI_ShouldMinimizeOnFocusLoss(فراغ);
        ܐܢ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ܦܢܐ false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ܐܢ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ܐܢ (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ܦܢܐ true;
        } ܐܚܪܢܐ {
            ܦܢܐ false;
        }
    }
    ܦܢܐ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

فراغ SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    ܐܢ (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(فراغ)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    ܐܢ (focus) {
        // Get the toplevel parent window.
        ܟܡܐ (focus->parent) {
            focus = focus->parent;
        }
    }

    ܦܢܐ focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->num_renderers + 1) * حجم(*renderers));
    ܐܢ (!renderers) {
        ܦܢܐ false;
    }

    window->renderers = renderers;
    window->renderers[window->num_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ܦܢܐ true;
}

فراغ SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    لكل (صحيح i = 0; i < window->num_renderers; ++i) {
        ܐܢ (window->renderers[i] == renderer) {
            ܐܢ (i < (window->num_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->num_renderers - i - 1) * حجم(window->renderers[i]));
            }
            --window->num_renderers;
            اكسر;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ܐܢ (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, عدم) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

فراغ SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    ܟܡܐ (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    ܐܢ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    ܐܢ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_input_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ܐܢ (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    لكل (صحيح i = 0; i < _this->num_displays; ++i) {
        ܐܢ (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = عدم;
        }
    }

    // Make sure this window no longer has focus
    ܐܢ (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(عدم);
    }
    ܐܢ ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ܐܢ (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(عدم);
    }

    // Make no context current if this is the current context window
    ܐܢ (window->flags & SDL_WINDOW_OPENGL) {
        ܐܢ (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, عدم);
        }
    }

    ܐܢ (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ܐܢ (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ܐܢ (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ܐܢ (_this->grabbed_window == window) {
        _this->grabbed_window = عدم; // ungrabbing input.
    }

    ܐܢ (_this->current_glwin == window) {
        _this->current_glwin = عدم;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, عدم);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, عدم);

    // Unlink the window from the global window list
    ܐܢ (window->next) {
        window->next->prev = window->prev;
    }
    ܐܢ (window->prev) {
        window->prev->next = window->next;
    } ܐܚܪܢܐ {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(فراغ)
{
    ܐܢ (!_this) {
        ܦܢܐ true;
    }
    ܦܢܐ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(فراغ)
{
    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }
    ܐܢ (!_this->suspend_screensaver) {
        ܦܢܐ true;
    }
    _this->suspend_screensaver = false;
    ܐܢ (_this->SuspendScreenSaver) {
        ܦܢܐ _this->SuspendScreenSaver(_this);
    }

    ܦܢܐ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(فراغ)
{
    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }
    ܐܢ (_this->suspend_screensaver) {
        ܦܢܐ true;
    }
    _this->suspend_screensaver = true;
    ܐܢ (_this->SuspendScreenSaver) {
        ܦܢܐ _this->SuspendScreenSaver(_this);
    }

    ܦܢܐ SDL_Unsupported();
}

فراغ SDL_QuitVideo(فراغ)
{
    صحيح i;

    ܐܢ (!_this) {
        ܦܢܐ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ܐܢ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ܟܡܐ (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    ܐܢ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ܐܢ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    لكل (i = _this->num_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->num_displays == 0);
    SDL_free(_this->displays);
    _this->displays = عدم;

    SDL_CancelClipboardData(0);

    ܐܢ (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = عدم;
    }
    _this->حرر(_this);
    _this = عدم;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(ثابت حرف *path)
{
    bool result;

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }
    ܐܢ (_this->gl_config.driver_loaded) {
        ܐܢ (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ܦܢܐ SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } ܐܚܪܢܐ {
        ܐܢ (!_this->GL_LoadLibrary) {
            ܦܢܐ SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    ܐܢ (result) {
        ++_this->gl_config.driver_loaded;
    } ܐܚܪܢܐ {
        ܐܢ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ܦܢܐ result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ثابت حرف *proc)
{
    SDL_FunctionPointer func;

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    func = عدم;
    ܐܢ (_this->GL_GetProcAddress) {
        ܐܢ (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } ܐܚܪܢܐ {
            SDL_SetError("No GL driver has been loaded");
        }
    } ܐܚܪܢܐ {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ܦܢܐ func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ثابت حرف *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    func = عدم;

    ܐܢ (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } ܐܚܪܢܐ {
        SDL_SetError("No EGL library has been loaded");
    }

    ܦܢܐ func;
#ܐܚܪܢܐ
    SDL_SetError("SDL was not built with EGL support");
    ܦܢܐ عدم;
#endif
}

فراغ SDL_GL_UnloadLibrary(فراغ)
{
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ;
    }
    ܐܢ (_this->gl_config.driver_loaded > 0) {
        ܐܢ (--_this->gl_config.driver_loaded > 0) {
            ܦܢܐ;
        }
        ܐܢ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ܐܢ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
تعريفنوع GLenum (APIENTRY* PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

ساكن SDL_INLINE bool isAtLeastGL3(ثابت حرف *verstr)
{
    ܦܢܐ verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت حرف *extension)
{
#ܐܢ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت حرف *extensions;
    ثابت حرف *start;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ܐܢ (where || *extension == '\0') {
        ܦܢܐ false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    ܐܢ (start && *start == '0') {
        ܦܢܐ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ܐܢ (!glGetStringFunc) {
        ܦܢܐ false;
    }

    ܐܢ (isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint num_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ܐܢ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ܦܢܐ false;
        }

#ifndef GL_NUM_EXTENSIONS
#define GL_NUM_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_NUM_EXTENSIONS, &num_exts);
        لكل (i = 0; i < num_exts; i++) {
            ثابت حرف *thisext = (ثابت حرف *)glGetStringiFunc(GL_EXTENSIONS, i);
            ܐܢ (SDL_strcmp(thisext, extension) == 0) {
                ܦܢܐ true;
            }
        }

        ܦܢܐ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ثابت حرف *)glGetStringFunc(GL_EXTENSIONS);
    ܐܢ (!extensions) {
        ܦܢܐ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    لكل (;;) {
        where = SDL_strstr(start, extension);
        ܐܢ (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        ܐܢ (where == extensions || *(where - 1) == ' ') {
            ܐܢ (*terminator == ' ' || *terminator == '\0') {
                ܦܢܐ true;
            }
        }

        start = terminator;
    }
    ܦܢܐ false;
#ܐܚܪܢܐ
    ܦܢܐ false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
فراغ SDL_GL_DeduceMaxSupportedESProfile(صحيح *major, صحيح *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#ܐܢ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ܐܢ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ܐܚܪܢܐ ܐܢ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ܐܚܪܢܐ ܐܢ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ܐܚܪܢܐ {
        *major = 2;
        *minor = 0;
    }
#endif
}

فراغ SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   فراغ *userdata)
{
    ܐܢ (!_this) {
        ܦܢܐ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

فراغ SDL_GL_ResetAttributes(فراغ)
{
    ܐܢ (!_this) {
        ܦܢܐ;
    }

    _this->egl_platformattrib_callback = عدم;
    _this->egl_surfaceattrib_callback = عدم;
    _this->egl_contextattrib_callback = عدم;
    _this->egl_attrib_callback_userdata = عدم;

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
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES)
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

    ܐܢ (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, صحيح value)
{
#ܐܢ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }
    result = true;
    بدل (attr) {
    حالة SDL_GL_RED_SIZE:
        _this->gl_config.red_size = value;
        اكسر;
    حالة SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = value;
        اكسر;
    حالة SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = value;
        اكسر;
    حالة SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = value;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = value;
        اكسر;
    حالة SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = value;
        اكسر;
    حالة SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = value;
        اكسر;
    حالة SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = value;
        اكسر;
    حالة SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = value;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = value;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = value;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = value;
        اكسر;
    حالة SDL_GL_STEREO:
        _this->gl_config.stereo = value;
        اكسر;
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = value;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = value;
        اكسر;
    حالة SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = value;
        اكسر;
    حالة SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = value;
        اكسر;
    حالة SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = value;
        اكسر;
    حالة SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = value;
        اكسر;
    حالة SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = value;
        اكسر;
    حالة SDL_GL_CONTEXT_FLAGS:
        ܐܢ (value & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", value);
            اكسر;
        }
        _this->gl_config.flags = value;
        اكسر;
    حالة SDL_GL_CONTEXT_PROFILE_MASK:
        ܐܢ (value != 0 &&
            value != SDL_GL_CONTEXT_PROFILE_CORE &&
            value != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            value != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", value);
            اكسر;
        }
        _this->gl_config.profile_mask = value;
        اكسر;
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = value;
        اكسر;
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = value;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = value;
        اكسر;
    حالة SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = value;
        اكسر;
    حالة SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = value;
        اكسر;
    حالة SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = value;
        اكسر;
    افتراضي:
        result = SDL_SetError("Unknown OpenGL attribute");
        اكسر;
    }
    ܦܢܐ result;
#ܐܚܪܢܐ
    ܦܢܐ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحيح *value)
{
#ܐܢ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_LEFT;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!value) {
        ܦܢܐ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *value = 0;

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    بدل (attr) {
    حالة SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        اكسر;
    حالة SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        اكسر;
    حالة SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        اكسر;
    حالة SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        اكسر;
#ܐܚܪܢܐ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *value = _this->gl_config.double_buffer;
        ܦܢܐ true;
#endif
    حالة SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        اكسر;
    حالة SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        اكسر;
#ifdef SDL_VIDEO_OPENGL
    حالة SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        اكسر;
    حالة SDL_GL_STEREO:
        attrib = GL_STEREO;
        اكسر;
#ܐܚܪܢܐ
    حالة SDL_GL_ACCUM_RED_SIZE:
    حالة SDL_GL_ACCUM_GREEN_SIZE:
    حالة SDL_GL_ACCUM_BLUE_SIZE:
    حالة SDL_GL_ACCUM_ALPHA_SIZE:
    حالة SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *value = 0;
        ܦܢܐ true;
#endif
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        اكسر;
    حالة SDL_GL_BUFFER_SIZE:
    {
        صحيح rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        ܐܢ (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            ܦܢܐ false;
        }
        ܐܢ (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            ܦܢܐ false;
        }
        ܐܢ (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            ܦܢܐ false;
        }
        ܐܢ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            ܦܢܐ false;
        }

        *value = rsize + gsize + bsize + asize;
        ܦܢܐ true;
    }
    حالة SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *value = (_this->gl_config.accelerated != 0);
        ܦܢܐ true;
    }
    حالة SDL_GL_RETAINED_BACKING:
    {
        *value = _this->gl_config.retained_backing;
        ܦܢܐ true;
    }
    حالة SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *value = _this->gl_config.major_version;
        ܦܢܐ true;
    }
    حالة SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *value = _this->gl_config.minor_version;
        ܦܢܐ true;
    }
    حالة SDL_GL_CONTEXT_FLAGS:
    {
        *value = _this->gl_config.flags;
        ܦܢܐ true;
    }
    حالة SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *value = _this->gl_config.profile_mask;
        ܦܢܐ true;
    }
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *value = _this->gl_config.share_with_current_context;
        ܦܢܐ true;
    }
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *value = _this->gl_config.framebuffer_srgb_capable;
        ܦܢܐ true;
    }
    حالة SDL_GL_CONTEXT_NO_ERROR:
    {
        *value = _this->gl_config.no_error;
        ܦܢܐ true;
    }
    حالة SDL_GL_EGL_PLATFORM:
    {
        *value = _this->gl_config.egl_platform;
        ܦܢܐ true;
    }
    حالة SDL_GL_FLOATBUFFERS:
    {
        ܐܢ (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            اكسر;
        } ܐܚܪܢܐ {
            ܦܢܐ 0;
        }
    }
    افتراضي:
        ܦܢܐ SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ܐܢ (!glGetStringFunc) {
        ܦܢܐ false;
    }

    ܐܢ (attachmentattrib && isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        ܐܢ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        ܐܢ (glGetFramebufferAttachmentParameterivFunc) {
            ܐܢ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ܐܢ (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ܐܢ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)value);
            } ܐܚܪܢܐ {
                *value = 0;
            }
            ܐܢ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ܐܚܪܢܐ {
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ܐܢ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)value);
        } ܐܚܪܢܐ {
            ܦܢܐ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    ܐܢ (!glGetErrorFunc) {
        ܦܢܐ false;
    }

    error = glGetErrorFunc();
    ܐܢ (error != GL_NO_ERROR) {
        ܐܢ (error == GL_INVALID_ENUM) {
            ܦܢܐ SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } ܐܚܪܢܐ ܐܢ (error == GL_INVALID_VALUE) {
            ܦܢܐ SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ܦܢܐ SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ܐܢ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *value = (*value == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ܦܢܐ true;
#ܐܚܪܢܐ
    ܦܢܐ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = عدم;
    CHECK_WINDOW_MAGIC(window, عدم);

    ܐܢ (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ܦܢܐ عدم;
    }

#ܐܢ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحيح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ܐܢ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    ܐܢ (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, عدم);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, عدم);
    }

#ܐܢ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ܐܢ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        ܐܢ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ܐܢ (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ܐܚܪܢܐ {
                supported = isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ܐܢ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ܦܢܐ ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }

    ܐܢ (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ܦܢܐ true;
    }

    ܐܢ (!context) {
        window = عدم;
    } ܐܚܪܢܐ ܐܢ (window) {
        CHECK_WINDOW_MAGIC(window, false);

        ܐܢ (!(window->flags & SDL_WINDOW_OPENGL)) {
            ܦܢܐ SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } ܐܚܪܢܐ ܐܢ (!_this->gl_allow_no_surface) {
        ܦܢܐ SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    ܐܢ (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, عدم);
        SDL_SetTLS(&_this->current_glctx_tls, context, عدم);
    }
    ܦܢܐ result;
}

SDL_Window *SDL_GL_GetCurrentWindow(فراغ)
{
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    ܦܢܐ (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(فراغ)
{
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    ܦܢܐ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(فراغ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ EGL_NO_DISPLAY;
    }
    ܐܢ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ܦܢܐ EGL_NO_DISPLAY;
    }
    ܦܢܐ _this->egl_data->egl_display;
#ܐܚܪܢܐ
    SDL_SetError("SDL was not built with EGL support");
    ܦܢܐ عدم;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(فراغ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    ܐܢ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ܦܢܐ عدم;
    }
    ܦܢܐ _this->egl_data->egl_config;
#ܐܚܪܢܐ
    SDL_SetError("SDL was not built with EGL support");
    ܦܢܐ عدم;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    ܐܢ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ܦܢܐ عدم;
    }
    ܐܢ (_this->GL_GetEGLSurface) {
        ܦܢܐ _this->GL_GetEGLSurface(_this, window);
    }
    ܦܢܐ عدم;
#ܐܚܪܢܐ
    SDL_SetError("SDL was not built with EGL support");
    ܦܢܐ عدم;
#endif
}

bool SDL_GL_SetSwapInterval(صحيح interval)
{
    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    } ܐܚܪܢܐ ܐܢ (SDL_GL_GetCurrentContext() == عدم) {
        ܦܢܐ SDL_SetError("No OpenGL context has been made current");
    } ܐܚܪܢܐ ܐܢ (_this->GL_SetSwapInterval) {
        ܦܢܐ _this->GL_SetSwapInterval(_this, interval);
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(صحيح *interval)
{
    CHECK_PARAM(!interval) {
       ܦܢܐ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ܐܢ (!_this) {
        ܦܢܐ SDL_SetError("no video driver");
    } ܐܚܪܢܐ ܐܢ (SDL_GL_GetCurrentContext() == عدم) {
        ܦܢܐ SDL_SetError("no current context");
    } ܐܚܪܢܐ ܐܢ (_this->GL_GetSwapInterval) {
        ܦܢܐ _this->GL_GetSwapInterval(_this, interval);
    } ܐܚܪܢܐ {
        ܦܢܐ SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!(window->flags & SDL_WINDOW_OPENGL)) {
        ܦܢܐ SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    ܐܢ (SDL_GL_GetCurrentWindow() != window) {
        ܦܢܐ SDL_SetError("The specified window has not been made current");
    }

    ܦܢܐ _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ܦܢܐ SDL_InvalidParamError("context");
    }

    ܐܢ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(عدم, عدم);
    }

    ܦܢܐ _this->GL_DestroyContext(_this, context);
}

#ܐܢ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ساكن فراغ CreateMaskFromColorKeyOrAlpha(SDL_Surface *icon, Uint8 *mask, صحيح flags)
{
    صحيح x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    بدل (SDL_BYTESPERPIXEL(icon->format)) {
    حالة 1:
        {
            Uint8 *pixels;
            لكل (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                لكل (x = 0; x < icon->w; ++x) {
                    ܐܢ (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        اكسر;

    حالة 2:
        {
            Uint16 *pixels;
            لكل (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                لكل (x = 0; x < icon->w; ++x) {
                    ܐܢ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ܐܚܪܢܐ ܐܢ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        اكسر;

    حالة 4:
        {
            Uint32 *pixels;
            لكل (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                لكل (x = 0; x < icon->w; ++x) {
                    ܐܢ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ܐܚܪܢܐ ܐܢ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        اكسر;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
فراغ SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    ܐܢ (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        ܐܢ (mask == عدم) {
            صحيح mask_len = icon->h * (icon->w + 7) / 8;
            صحيح flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            ܐܢ (mask == عدم) {
                ܦܢܐ;
            }
            SDL_memset(mask, ~0, mask_len);
            ܐܢ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ܐܢ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ܐܢ (flags) {
                CreateMaskFromColorKeyOrAlpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } ܐܚܪܢܐ {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_TextInputType SDL_GetTextInputType(SDL_PropertiesID props)
{
    ܦܢܐ (SDL_TextInputType)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_TYPE_NUMBER, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_GetTextInputCapitalization(SDL_PropertiesID props)
{
    ܐܢ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER)) {
        ܦܢܐ (SDL_Capitalization)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER, SDL_CAPITALIZE_NONE);
    }

    بدل (SDL_GetTextInputType(props)) {
    حالة SDL_TEXTINPUT_TYPE_TEXT:
        ܦܢܐ SDL_CAPITALIZE_SENTENCES;
    حالة SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ܦܢܐ SDL_CAPITALIZE_WORDS;
    افتراضي:
        ܦܢܐ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_GetTextInputAutocorrect(SDL_PropertiesID props)
{
    ܦܢܐ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_GetTextInputMultiline(SDL_PropertiesID props)
{
    ܐܢ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ܦܢܐ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ܐܢ (SDL_GetHintBoolean(SDL_HINT_RETURN_KEY_HIDES_IME, false)) {
        ܦܢܐ false;
    } ܐܚܪܢܐ {
        ܦܢܐ true;
    }
}

ساكن bool AutoShowingScreenKeyboard(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ܐܢ (!hint) {
        // This hint is currently only used by the X11 video driver
        ܐܢ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ܐܢ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ܦܢܐ true;
    } ܐܚܪܢܐ {
        ܦܢܐ false;
    }
}

bool SDL_StartTextInput(SDL_Window *window)
{
    ܦܢܐ SDL_StartTextInputWithProperties(window, 0);
}

bool SDL_StartTextInputWithProperties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (window->text_input_props) {
        SDL_DestroyProperties(window->text_input_props);
        window->text_input_props = 0;
    }

    ܐܢ (props) {
        window->text_input_props = SDL_CreateProperties();
        ܐܢ (!window->text_input_props) {
            ܦܢܐ false;
        }
        ܐܢ (!SDL_CopyProperties(props, window->text_input_props)) {
            ܦܢܐ false;
        }
    }

    ܐܢ (_this->SetTextInputProperties) {
        _this->SetTextInputProperties(_this, window, props);
    }

    ܐܢ (!window->text_input_active) {
        // Start the text input system
        ܐܢ (_this->StartTextInput) {
            ܐܢ (!_this->StartTextInput(_this, window, props)) {
                ܦܢܐ false;
            }
        }
        window->text_input_active = true;
    }

    // Show the on-screen keyboard, if desired
    ܐܢ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        ܐܢ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    ܦܢܐ true;
}

bool SDL_TextInputActive(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܦܢܐ window->text_input_active;
}

bool SDL_StopTextInput(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (window->text_input_active) {
        // Stop the text input system
        ܐܢ (_this->StopTextInput) {
            _this->StopTextInput(_this, window);
        }
        window->text_input_active = false;
    }

    // Hide the on-screen keyboard, if desired
    ܐܢ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        ܐܢ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    ܦܢܐ true;
}

bool SDL_SetTextInputArea(SDL_Window *window, ثابت SDL_Rect *rect, صحيح cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (rect) {
        SDL_copyp(&window->text_input_rect, rect);
        window->text_input_cursor = cursor;
    } ܐܚܪܢܐ {
        SDL_zero(window->text_input_rect);
        window->text_input_cursor = 0;
    }

    ܐܢ (_this && _this->UpdateTextInputArea) {
        ܐܢ (!_this->UpdateTextInputArea(_this, window)) {
            ܦܢܐ false;
        }
    }
    ܦܢܐ true;
}

bool SDL_GetTextInputArea(SDL_Window *window, SDL_Rect *rect, صحيح *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (rect) {
        SDL_copyp(rect, &window->text_input_rect);
    }
    ܐܢ (cursor) {
        *cursor = window->text_input_cursor;
    }
    ܦܢܐ true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (_this->ClearComposition) {
        ܦܢܐ _this->ClearComposition(_this, window);
    }
    ܦܢܐ true;
}

bool SDL_HasScreenKeyboardSupport(فراغ)
{
    ܐܢ (_this && _this->HasScreenKeyboardSupport) {
        ܦܢܐ _this->HasScreenKeyboardSupport(_this);
    }
    ܦܢܐ false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܦܢܐ _this->screen_keyboard_shown;
}

فراغ SDL_SendScreenKeyboardShown(فراغ)
{
    ܐܢ (!_this || _this->screen_keyboard_shown) {
        ܦܢܐ;
    }

    _this->screen_keyboard_shown = true;

    ܐܢ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

فراغ SDL_SendScreenKeyboardHidden(فراغ)
{
    ܐܢ (!_this || !_this->screen_keyboard_shown) {
        ܦܢܐ;
    }

    _this->screen_keyboard_shown = false;

    ܐܢ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

صحيح SDL_GetMessageBoxCount(فراغ)
{
    ܦܢܐ SDL_GetAtomicInt(&SDL_messagebox_count);
}

bool SDL_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID)
{
    صحيح dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        ܦܢܐ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ܦܢܐ SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    حرف *titlecpy = عدم;
    حرف *msgcpy = عدم;
    ܐܢ (messageboxdata->title) {
        ثابت size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(حرف, slen, &titleisstack);
        ܐܢ (!titlecpy) {
            ܦܢܐ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ܐܢ (messageboxdata->message) {
        ثابت size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        ܐܢ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ܦܢܐ false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (فراغ)SDL_AtomicIncRef(&SDL_messagebox_count);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    ܐܢ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, حجم(*messageboxdata));
    mbdata.title = titlecpy;
    ܐܢ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    ܐܢ (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ܐܢ (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } ܐܚܪܢܐ {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ܐܢ (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            ܟܡܐ (driver_attempt && (*driver_attempt != 0) && !result) {
                ثابت حرف *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                لكل (صحيح i = 0; bootstrap[i]; ++i) {
                    ܐܢ (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ܐܢ (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        اكسر;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : عدم;
            }
        } ܐܚܪܢܐ {
            لكل (صحيح i = 0; bootstrap[i]; ++i) {
                ܐܢ (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    اكسر;
                }
            }
        }
    }

    ܐܢ (!result) {
        ثابت حرف *error = SDL_GetError();

        ܐܢ (!*error) {
            SDL_SetError("No message system available");
        }
    } ܐܚܪܢܐ {
        SDL_ClearError();
    }

    (فراغ)SDL_AtomicDecRef(&SDL_messagebox_count);

    ܐܢ (current_window) {
        SDL_RaiseWindow(current_window);
    }

    ܐܢ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ܦܢܐ result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ثابت حرف *title, ثابت حرف *message, SDL_Window *window)
{
#ܐܢ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool hasGpuRight;

    // If the video subsystem has not been initialised, set up graphics temporarily
    hasGpuRight = gspHasGpuRight();
    ܐܢ (!hasGpuRight)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    ܐܢ (!hasGpuRight)
        gfxExit();

    ܦܢܐ true;
#ܐܚܪܢܐ
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

    ܦܢܐ SDL_ShowMessageBox(&data, عدم);
#endif
}

bool SDL_ShouldAllowTopmost(فراغ)
{
    ܦܢܐ SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, صحيح x, صحيح y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ܐܢ (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ܦܢܐ true;
    }

    ܦܢܐ SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, فراغ *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!_this->SetWindowHitTest) {
        ܦܢܐ SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    ܦܢܐ _this->SetWindowHitTest(window, callback != عدم);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ܦܢܐ SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    ܐܢ (!props) {
        ܦܢܐ false;
    }

    ܐܢ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ܐܢ (!surface) {
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ {
        surface = عدم;
    }

    ܐܢ (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ܦܢܐ false;
    }

    ܐܢ (_this->UpdateWindowShape) {
        ܐܢ (!_this->UpdateWindowShape(_this, window, surface)) {
            ܦܢܐ false;
        }
    }
    ܦܢܐ true;
}

/*
 * Functions used by iOS application delegates
 */
فراغ SDL_OnApplicationWillTerminate(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

فراغ SDL_OnApplicationDidReceiveMemoryWarning(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_LOW_MEMORY);
}

فراغ SDL_OnApplicationWillEnterBackground(فراغ)
{
    ܐܢ (_this) {
        SDL_Window *window;
        لكل (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(عدم);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

فراغ SDL_OnApplicationDidEnterBackground(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

فراغ SDL_OnApplicationWillEnterForeground(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

فراغ SDL_OnApplicationDidEnterForeground(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    ܐܢ (_this) {
        SDL_Window *window;
        لكل (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ثابت حرف *path)
{
    bool result;

    ܐܢ (!_this) {
        ܦܢܐ SDL_UninitializedVideo();
    }
    ܐܢ (_this->vulkan_config.loader_loaded) {
        ܐܢ (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ܦܢܐ SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } ܐܚܪܢܐ {
        ܐܢ (!_this->Vulkan_LoadLibrary) {
            ܦܢܐ SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    ܐܢ (result) {
        _this->vulkan_config.loader_loaded++;
    }
    ܦܢܐ result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(فراغ)
{
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ عدم;
    }
    ܐܢ (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ܦܢܐ عدم;
    }
    ܦܢܐ (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

فراغ SDL_Vulkan_UnloadLibrary(فراغ)
{
    ܐܢ (!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ;
    }
    ܐܢ (_this->vulkan_config.loader_loaded > 0) {
        ܐܢ (--_this->vulkan_config.loader_loaded > 0) {
            ܦܢܐ;
        }
        ܐܢ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *count)
{
    Uint32 tmpcount = 0;
    ܐܢ (!count) {
        count = &tmpcount;
    }

    ܐܢ (!_this->Vulkan_GetInstanceExtensions) {
        *count = 0;
        SDL_Unsupported();
        ܦܢܐ عدم;
    }

    ܦܢܐ _this->Vulkan_GetInstanceExtensions(_this, count);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ثابت بنية VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    ܐܢ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ܦܢܐ false;
    }

    CHECK_PARAM(!instance) {
        ܦܢܐ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ܦܢܐ SDL_InvalidParamError("surface");
    }

    ܐܢ (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        ܐܢ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ܐܢ (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        ܐܢ (SDL_Vulkan_LoadLibrary(عدم)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } ܐܚܪܢܐ {
            ܦܢܐ SDL_SetError("failed to load Vulkan library");
        }
    }

    ܦܢܐ _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

فراغ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية VkAllocationCallbacks *allocator)
{
    ܐܢ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ܦܢܐ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ܦܢܐ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ܦܢܐ false;
    }

    ܐܢ (_this->Vulkan_GetPresentationSupport) {
        ܦܢܐ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ܦܢܐ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    ܐܢ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ܦܢܐ عدم;
    }

    ܐܢ (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        ܐܢ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ܐܢ (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    ܦܢܐ _this->Metal_CreateView(_this, window);
}

فراغ SDL_Metal_DestroyView(SDL_MetalView view)
{
    ܐܢ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

فراغ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ܐܢ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ܦܢܐ عدم;
        }
        ܦܢܐ _this->Metal_GetLayer(_this, view);
    } ܐܚܪܢܐ {
        SDL_SetError("Metal is not supported.");
        ܦܢܐ عدم;
    }
}

#ܐܢ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ثابت حرف *SDL_GetCSSCursorName(SDL_SystemCursor id, ثابت حرف **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    بدل (id) {
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
        ܦܢܐ "default";

    حالة SDL_SYSTEM_CURSOR_TEXT:
        ܦܢܐ "text";

    حالة SDL_SYSTEM_CURSOR_WAIT:
        ܦܢܐ "wait";

    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
        ܦܢܐ "crosshair";

    حالة SDL_SYSTEM_CURSOR_PROGRESS:
        ܦܢܐ "progress";

    حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ܐܢ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ܦܢܐ "nwse-resize";

    حالة SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ܐܢ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ܦܢܐ "nesw-resize";

    حالة SDL_SYSTEM_CURSOR_EW_RESIZE:
        ܐܢ (fallback_name) {
            *fallback_name = "col-resize";
        }
        ܦܢܐ "ew-resize";

    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
        ܐܢ (fallback_name) {
            *fallback_name = "row-resize";
        }
        ܦܢܐ "ns-resize";

    حالة SDL_SYSTEM_CURSOR_MOVE:
        ܐܢ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ܦܢܐ "move";

    حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ܦܢܐ "not-allowed";

    حالة SDL_SYSTEM_CURSOR_POINTER:
        ܦܢܐ "pointer";

    حالة SDL_SYSTEM_CURSOR_NW_RESIZE:
        ܦܢܐ "nw-resize";

    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
        ܦܢܐ "n-resize";

    حالة SDL_SYSTEM_CURSOR_NE_RESIZE:
        ܦܢܐ "ne-resize";

    حالة SDL_SYSTEM_CURSOR_E_RESIZE:
        ܦܢܐ "e-resize";

    حالة SDL_SYSTEM_CURSOR_SE_RESIZE:
        ܦܢܐ "se-resize";

    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
        ܦܢܐ "s-resize";

    حالة SDL_SYSTEM_CURSOR_SW_RESIZE:
        ܦܢܐ "sw-resize";

    حالة SDL_SYSTEM_CURSOR_W_RESIZE:
        ܦܢܐ "w-resize";

    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ܦܢܐ "context-menu";

    حالة SDL_SYSTEM_CURSOR_HELP:
        ܦܢܐ "help";

    حالة SDL_SYSTEM_CURSOR_CELL:
        ܦܢܐ "cell";

    حالة SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ܦܢܐ "vertical-text";

    حالة SDL_SYSTEM_CURSOR_ALIAS:
        ܦܢܐ "alias";

    حالة SDL_SYSTEM_CURSOR_COPY:
        ܦܢܐ "copy";

    حالة SDL_SYSTEM_CURSOR_NO_DROP:
        ܦܢܐ "no-drop";

    حالة SDL_SYSTEM_CURSOR_GRAB:
        ܦܢܐ "grab";

    حالة SDL_SYSTEM_CURSOR_GRABBING:
        ܦܢܐ "grabbing";

    حالة SDL_SYSTEM_CURSOR_COL_RESIZE:
        ܦܢܐ "col-resize";

    حالة SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ܦܢܐ "row-resize";

    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ܐܢ (fallback_name) {
            *fallback_name = "move";
        }
        ܦܢܐ "all-scroll";

    حالة SDL_SYSTEM_CURSOR_ZOOM_IN:
        ܦܢܐ "zoom-in";

    حالة SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ܦܢܐ "zoom-out";

    افتراضي:
        ܦܢܐ "default";
    }
}
#endif

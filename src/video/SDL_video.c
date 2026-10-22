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

#إذا defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#إذا defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
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
#ifdef SDL_شغرو_LINUXEV
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
        أرجع result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        أرجع result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        أرجع result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        أرجع result;                                                  \
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
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
    إذا (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        أرجع true;
    }
    أرجع false;
}

ساكن bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ساكن bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ساكن bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ساكن bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ساكن bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ساكن bool syncHint;

ساكن فراغ SDL_SyncHintWatcher(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_درج, ثابت حرف *new_درج)
{
    syncHint = SDL_GetStringBoolean(new_درج, false);
}

ساكن فراغ SDL_SyncIfRequired(SDL_Window *window)
{
    إذا (syncHint) {
        SDL_SyncWindow(window);
    }
}

ساكن فراغ SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    إذا (window->parent) {
        إذا (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        إذا (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } وإلا {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = عدم;
    }

    إذا (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        إذا (parent->first_child) {
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
#إذا (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    إذا (_this->GL_CreateContext) {
        أرجع SDL_WINDOW_OPENGL;
    }
#endif
#إذا defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    إذا (_this->Metal_CreateView) {
        أرجع SDL_WINDOW_METAL;
    }
#endif
#إذا defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    إذا (SDL_strcmp(_this->name, "openvr") == 0) {
        أرجع SDL_WINDOW_OPENGL;
    }
#endif
    أرجع 0;
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

    إذا (!data) {
        SDL_Renderer *renderer = عدم;
        ثابت حرف *render_driver = عدم;

        // See if there's a render driver being requested
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        إذا (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        إذا (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        إذا (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = عدم;
        }

        حرف *render_driver_copy = عدم;
        إذا (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            إذا (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                حرف *prev = render_driver_copy;
                حرف *ptr = prev;
                طالما ((ptr = SDL_strchr(ptr, ',')) != عدم) {
                    *ptr = '\0';
                    ثابت bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    إذا (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } وإلا {
                        ptr++;
                        prev = ptr;
                    }
                }

                إذا (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        إذا (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            إذا (!renderer) {
                // The error for this specific renderer has already been set
                أرجع false;
            }
        } وإلا {
            SDL_assert(render_driver_copy == عدم);
            ثابت صحيح total = SDL_Get_لمب_Render_Drivers();
            لكل (i = 0; i < total; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                إذا (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    إذا (renderer) {
                        اكسر; // this will work.
                    }
                }
            }
            إذا (!renderer) {
                أرجع SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != عدم); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, حجم(*data));
        إذا (!data) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }
        إذا (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, عدم);
    إذا (!texture_formats) {
        أرجع false;
    }

    // Free any old texture and pixel data
    إذا (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = عدم;
    }
    SDL_free(data->pixels);
    data->pixels = عدم;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    لكل (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        إذا (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
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
    إذا (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        أرجع false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        إذا (!data->pixels) {
            أرجع false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, عدم);

    أرجع true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحيح vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    إذا (!data) {
        أرجع false;
    }
    إذا (!data->renderer) {
        أرجع false;
    }
    أرجع SDL_SetRenderVSync(data->renderer, vsync);
}

ساكن bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحيح *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    إذا (!data) {
        أرجع false;
    }
    إذا (!data->renderer) {
        أرجع false;
    }
    أرجع SDL_GetRenderVSync(data->renderer, vsync);
}

ساكن bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    فراغ *src;
    صحيح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    إذا (!data || !data->texture) {
        أرجع SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    إذا (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (فراغ *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        إذا (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            أرجع false;
        }

        إذا (!SDL_RenderTexture(data->renderer, data->texture, عدم, عدم)) {
            أرجع false;
        }

        SDL_RenderPresent(data->renderer);
    }
    أرجع true;
}

ساكن فراغ SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    إذا (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);

        إذا (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        إذا (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

ساكن SDL_VideoDevice *_this = عدم;
ساكن SDL_AtomicInt SDL_messagebox_كدي;

ساكن صحيح SDLCALL cmpmodes(ثابت فراغ *A, ثابت فراغ *B)
{
    ثابت SDL_DisplayMode *a = (ثابت SDL_DisplayMode *)A;
    ثابت SDL_DisplayMode *b = (ثابت SDL_DisplayMode *)B;
    صحيح a_refresh_rate = (صحيح)(a->refresh_rate * 100);
    صحيح b_refresh_rate = (صحيح)(b->refresh_rate * 100);
    صحيح a_pixel_density = (صحيح)(a->pixel_density * 100);
    صحيح b_pixel_density = (صحيح)(b->pixel_density * 100);

    إذا (a->w != b->w) {
        أرجع b->w - a->w;
    } وإلا إذا (a->h != b->h) {
        أرجع b->h - a->h;
    } وإلا إذا (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        أرجع SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } وإلا إذا (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        أرجع SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } وإلا إذا (a_refresh_rate != b_refresh_rate) {
        أرجع b_refresh_rate - a_refresh_rate;
    } وإلا إذا (a_pixel_density != b_pixel_density) {
        أرجع a_pixel_density - b_pixel_density;
    }
    أرجع 0;
}

bool SDL_UninitializedVideo(فراغ)
{
    أرجع SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ساكن ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحيح SDL_Get_لمب_Video_Drivers(فراغ)
{
    ساكن صحيح لمب_drivers = -1;

    إذا (لمب_drivers >= 0) {
        أرجع لمب_drivers;
    }

    لمب_drivers = 0;

    // Build a list of unique video drivers.
    لكل (صحيح i = 0; bootstrap[i] != عدم; ++i) {
        bool duplicate = false;
        لكل (صحيح j = 0; j < i; ++j) {
            إذا (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                اكسر;
            }
        }

        إذا (!duplicate) {
            deduped_bootstrap[لمب_drivers++] = bootstrap[i];
        }
    }

    أرجع لمب_drivers;
}

ثابت حرف *SDL_GetVideoDriver(صحيح index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_لمب_Video_Drivers()) {
        SDL_InvalidParamError("index");
        أرجع عدم;
    }
    أرجع deduped_bootstrap[index]->name;
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
    إذا (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    إذا (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        اذهب pre_driver_error;
    }
    init_events = true;
    إذا (!SDL_InitKeyboard()) {
        اذهب pre_driver_error;
    }
    init_keyboard = true;
    إذا (!SDL_PreInitMouse()) {
        اذهب pre_driver_error;
    }
    init_mouse = true;
    إذا (!SDL_InitTouch()) {
        اذهب pre_driver_error;
    }
    init_touch = true;
    إذا (!SDL_InitPen()) {
        اذهب pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = عدم;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    إذا (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    إذا (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    إذا (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        طالما (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            لكل (i = 0; bootstrap[i]; ++i) {
                إذا (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    إذا (video) {
                        اكسر;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : عدم;
        }
    } وإلا {
        لكل (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            إذا (video) {
                اكسر;
            }
        }
    }
    إذا (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } وإلا {
        إذا (driver_name) {
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
    إذا (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        أرجع false;
    }

    // Make sure some displays were added
    إذا (_this->لمب_displays == 0) {
        SDL_QuitVideo();
        أرجع SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, عدم);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    إذا (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    أرجع true;

pre_driver_error:
    SDL_assert(_this == عدم);
    إذا (init_pen) {
        SDL_QuitPen();
    }
    إذا (init_touch) {
        SDL_QuitTouch();
    }
    إذا (init_mouse) {
        SDL_QuitMouse();
    }
    إذا (init_keyboard) {
        SDL_QuitKeyboard();
    }
    إذا (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    أرجع false;
}

ثابت حرف *SDL_GetCurrentVideoDriver(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(فراغ)
{
    أرجع _this;
}

bool SDL_OnVideoThread(فراغ)
{
    أرجع (_this && SDL_GetCurrentThreadID() == _this->thread);
}

فراغ SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    إذا (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(فراغ)
{
    إذا (_this) {
        أرجع _this->system_theme;
    } وإلا {
        أرجع SDL_SYSTEM_THEME_UNKNOWN;
    }
}

فراغ SDL_UpdateDesktopBounds(فراغ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    إذا (displays) {
        لكل (صحيح i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            إذا (SDL_GetDisplayBounds(displays[i], &bounds)) {
                إذا (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } وإلا {
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
    إذا (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    إذا (mode->refresh_rate_numerator > 0) {
        إذا (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (عائم)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } وإلا {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ثابت SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    إذا (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, حجم(display.desktop_mode));
    }
    أرجع SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحيح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(حجم(*new_display));
    إذا (!new_display) {
        أرجع 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->لمب_displays + 1) * حجم(*displays));
    إذا (!displays) {
        SDL_free(new_display);
        أرجع 0;
    }
    _this->displays = displays;
    _this->displays[_this->لمب_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    إذا (display->name) {
        new_display->name = SDL_strdup(display->name);
    } وإلا {
        حرف name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    إذا (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    لكل (i = 0; i < new_display->لمب_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    إذا (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    أرجع id;
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
    إذا (display_index < 0) {
        أرجع;
    }

    display = _this->displays[display_index];

    إذا (send_event) {
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

    إذا (display_index < (_this->لمب_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->لمب_displays - display_index - 1) * حجم(_this->displays[display_index]));
    }
    --_this->لمب_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحيح *كدي)
{
    صحيح i;
    SDL_DisplayID *displays;

    إذا (!_this) {
        إذا (كدي) {
            *كدي = 0;
        }

        SDL_UninitializedVideo();
        أرجع عدم;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->لمب_displays + 1) * حجم(*displays));
    إذا (displays) {
        إذا (كدي) {
            *كدي = _this->لمب_displays;
        }

        لكل (i = 0; i < _this->لمب_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } وإلا {
        إذا (كدي) {
            *كدي = 0;
        }
    }
    أرجع displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحيح display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    إذا (display_index < 0) {
        أرجع عدم;
    }
    أرجع _this->displays[display_index];
}

ساكن SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    إذا (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    أرجع SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(فراغ)
{
    إذا (!_this || _this->لمب_displays == 0) {
        SDL_UninitializedVideo();
        أرجع 0;
    }
    أرجع _this->displays[0]->id;
}

صحيح SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    صحيح display_index;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع -1;
    }

    لكل (display_index = 0; display_index < _this->لمب_displays; ++display_index) {
        إذا (displayID == _this->displays[display_index]->id) {
            أرجع display_index;
        }
    }
    SDL_SetError("Invalid display");
    أرجع -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    أرجع SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    إذا (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    أرجع display->props;
}

ثابت حرف *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        أرجع SDL_InvalidParamError("rect");
    }

    إذا (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        إذا (_this->GetDisplayBounds(_this, display, rect)) {
            أرجع true;
        }
    }

    // Assume that the displays are left to right
    إذا (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } وإلا {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    أرجع true;
}

ساكن صحيح ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    أرجع hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        أرجع SDL_InvalidParamError("rect");
    }

    إذا (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        أرجع true;
    }

    إذا (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        إذا (_this->GetDisplayUsableBounds(_this, display, rect)) {
            أرجع true;
        }
    }

    // Oh well, just give the entire display bounds.
    أرجع SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    إذا (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        أرجع display->natural_orientation;
    } وإلا {
        // Default to landscape if the driver hasn't set it
        أرجع SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    إذا (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        أرجع display->current_orientation;
    } وإلا {
        // Default to landscape if the driver hasn't set it
        أرجع SDL_ORIENTATION_LANDSCAPE;
    }
}

فراغ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, عائم scale)
{
    إذا (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        لكل (window = _this->windows; window; window = window->next) {
            إذا (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

عائم SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    أرجع display->content_scale;
}

فراغ SDL_SetWindowHDRProperties(SDL_Window *window, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    إذا (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        إذا (send_event) {
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

	إذا (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    إذا (changed && !SDL_DriverSendsHDRChanges(_this)) {
        لكل (SDL_Window *w = display->device->windows; w; w = w->next) {
            إذا (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ساكن فراغ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    إذا (display->لمب_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ساكن ثابت SDL_DisplayMode *SDL_GetFullscreenModeMatch(ثابت SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    إذا (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        أرجع عدم;
    }

    SDL_memcpy(&fullscreen_mode, mode, حجم(fullscreen_mode));
    إذا (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = عدم;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    إذا (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        إذا (!mode) {
            لكل (صحيح i = 0; i < display->لمب_fullscreen_modes; ++i) {
                إذا (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], حجم(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }

        // Search for a mode with the same characteristics
        إذا (!mode) {
            لكل (صحيح i = 0; i < display->لمب_fullscreen_modes; ++i) {
                إذا (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }
    }
    أرجع mode;
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
    nmodes = display->لمب_fullscreen_modes;
    لكل (i = 0; i < nmodes; ++i) {
        إذا (cmpmodes(&new_mode, &modes[i]) == 0) {
            أرجع false;
        }
    }

    // Go ahead and add the new mode
    إذا (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        إذا (!modes) {
            أرجع false;
        }

        إذا (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            لكل (i = 0; i < nmodes; ++i) {
                إذا (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->لمب_fullscreen_modes++], &new_mode, حجم(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->لمب_fullscreen_modes,
              حجم(SDL_DisplayMode), cmpmodes);

    أرجع true;
}

فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحيح i;

    لكل (i = display->لمب_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = عدم;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = عدم;
    display->لمب_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحيح *كدي)
{
    صحيح i;
    صحيح لمب_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    إذا (كدي) {
        *كدي = 0;
    }

    CHECK_DISPLAY_MAGIC(display, عدم);

    SDL_UpdateFullscreenDisplayModes(display);

    لمب_modes = display->لمب_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((لمب_modes + 1) * حجم(*result) + لمب_modes * حجم(**result));
    إذا (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((لمب_modes + 1) * حجم(*result)));
        إذا (لمب_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, لمب_modes * حجم(*modes));
        }
        لكل (i = 0; i < لمب_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = عدم;

        إذا (كدي) {
            *كدي = لمب_modes;
        }
    } وإلا {
        إذا (كدي) {
            *كدي = 0;
        }
    }
    أرجع result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, صحيح w, صحيح h, عائم refresh_rate, bool include_سم_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        أرجع SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_DisplayMode *mode, *closest = عدم;
    عائم aspect_ratio;
    صحيح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    إذا (h > 0) {
        aspect_ratio = (عائم)w / h;
    } وإلا {
        aspect_ratio = 1.0f;
    }

    إذا (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    لكل (i = 0; i < display->لمب_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        إذا (w > mode->w) {
            // Out of sorted modes large enough here
            اكسر;
        }
        إذا (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            استمر;
        }
        إذا (mode->pixel_density > 1.0f && !include_سم_density_modes) {
            استمر;
        }
        إذا (closest) {
            عائم current_aspect_ratio = (عائم)mode->w / mode->h;
            عائم closest_aspect_ratio = (عائم)closest->w / closest->h;
            إذا (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                استمر;
            }

            إذا (mode->w == closest->w && mode->h == closest->h) {
                إذا (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    استمر;
                }
                إذا (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    استمر;
                }
            }
        }

        closest = mode;
    }
    إذا (!closest) {
        أرجع SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    أرجع true;
}

ساكن bool DisplayModeChanged(ثابت SDL_DisplayMode *old_mode, ثابت SDL_DisplayMode *new_mode)
{
    أرجع ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

فراغ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    إذا (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        أرجع;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    إذا (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        إذا (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ثابت SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع &display->desktop_mode;
}

فراغ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    إذا (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } وإلا {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    إذا (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ثابت SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    إذا (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        أرجع true;
    }

    إذا (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    إذا (mode == display->current_mode) {
        أرجع true;
    }
#endif

    // Actually change the display mode
    إذا (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        إذا (!result) {
            أرجع false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    أرجع true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساكن فراغ SDL_GetClosestPointOnRect(ثابت SDL_Rect *rect, SDL_Point *point)
{
    ثابت صحيح دام = rect->x + rect->w - 1;
    ثابت صحيح bottom = rect->y + rect->h - 1;

    إذا (point->x < rect->x) {
        point->x = rect->x;
    } وإلا إذا (point->x > دام) {
        point->x = دام;
    }

    إذا (point->y < rect->y) {
        point->y = rect->y;
    } وإلا إذا (point->y > bottom) {
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

    إذا (_this) {
        لكل (i = 0; i < _this->لمب_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            إذا (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, عدم)) {
                أرجع display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            إذا (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    إذا (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    أرجع closest;
}

فراغ SDL_RelativeToGlobalForWindow(SDL_Window *window, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y)
{
    SDL_Window *w;

    إذا (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        لكل (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            إذا (!SDL_WINDOW_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    إذا (abs_x) {
        *abs_x = rel_x;
    }
    إذا (abs_y) {
        *abs_y = rel_y;
    }
}

فراغ SDL_GlobalToRelativeForWindow(SDL_Window *window, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y)
{
    SDL_Window *w;

    إذا (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        لكل (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            إذا (!SDL_WINDOW_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    إذا (rel_x) {
        *rel_x = abs_x;
    }
    إذا (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ثابت SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        أرجع 0;
    }

    أرجع GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ثابت SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        أرجع 0;
    }

    أرجع GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ساكن SDL_DisplayID GetDisplayAtOrigin(صحيح x, صحيح y)
{
    لكل (صحيح i = 0; i < _this->لمب_displays; ++i) {
        SDL_Rect rect;
        ثابت SDL_DisplayID cur_id = _this->displays[i]->id;
        إذا (SDL_GetDisplayBounds(cur_id, &rect)) {
            إذا (x == rect.x && y == rect.y) {
                أرجع cur_id;
            }
        }
    }

    أرجع 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    صحيح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    إذا (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    إذا (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } وإلا {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    إذا (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, عدم);

    // An explicit fullscreen display overrides all
    إذا (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    إذا (!displayID) {
        displayID = window->pending_displayID;
    }
    إذا (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحيح x = window->last_position_pending ? window->pending.x : window->x;
        ثابت صحيح y = window->last_position_pending ? window->pending.y : window->y;
        ثابت صحيح w = window->last_size_pending ? window->pending.w : window->w;
        ثابت صحيح h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        إذا (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    إذا (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    أرجع SDL_GetVideoDisplay(displayID);
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
    إذا (fs_display) {
        SDL_Set_لمب_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } وإلا {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    أرجع GetDisplayForWindow(window);
}

ساكن فراغ SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    إذا (SDL_SendsDisplayChanges(_this)) {
        أرجع;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    إذا (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        إذا (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            إذا (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                صحيح old_area = old_overlap.w * old_overlap.h;
                صحيح new_area = new_overlap.w * new_overlap.h;
                عائم new_overlap_ratio = (new_area / ((عائم)old_area + new_area));
                إذا (new_overlap_ratio < 0.80) {
                    أرجع;
                }
            }
        }
    }

    إذا (displayID != window->displayID) {
        صحيح i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        لكل (i = 0; i < _this->لمب_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            إذا (display->fullscreen_window == window) {
                إذا (display_index != i) {
                    إذا (display_index < 0) {
                        display_index = i;
                    } وإلا {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        إذا (new_display->fullscreen_window &&
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

    إذا (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (عائم)pixel_w / window_w;
    }
    أرجع pixel_density;
}

عائم SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    أرجع window->display_scale;
}

ساكن فراغ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    عائم display_scale;

    إذا (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } وإلا {
        ثابت عائم pixel_density = SDL_GetWindowPixelDensity(window);
        ثابت عائم content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    إذا (display_scale != window->display_scale) {
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
    إذا (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    إذا (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        إذا (!display) {
            // This should never happen, but it did...
            اذهب done;
        }
    } وإلا {
        لكل (i = 0; i < _this->لمب_displays; ++i) {
            display = _this->displays[i];
            إذا (display->fullscreen_window == window) {
                اكسر;
            }
        }
        إذا (!display || i == _this->لمب_displays) {
            // Already not fullscreen on any display
            display = عدم;
        }
    }

    إذا (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        إذا (mode) {
            window->fullscreen_exclusive = true;
        } وإلا {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            إذا (display) {
                display->fullscreen_window = عدم;
            }
            اذهب done;
        }
        إذا (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            إذا (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                إذا (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    اذهب error;
                }
            } وإلا إذا (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                لكل (i = 0; i < _this->لمب_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    إذا (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, عدم);
                        إذا (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = عدم;
                    }
                }
            }

            إذا (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                اذهب done;
            }
        }
    }
#endif

    إذا (display) {
        // Restore the video mode on other displays if needed
        لكل (i = 0; i < _this->لمب_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            إذا (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, عدم);
                other->fullscreen_window = عدم;
            }
        }
    }

    إذا (fullscreen) {
        صحيح mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        إذا (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        إذا (!SDL_SetDisplayModeForDisplay(display, mode)) {
            اذهب error;
        }
        إذا (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                اذهب error;
            }
        }

        إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                إذا (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } وإلا {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                إذا (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                إذا (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } وإلا {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } وإلا {
        bool resized = false;

        // Restore the desktop mode
        إذا (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, عدم);
        }
        إذا (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                إذا (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                اذهب error;
            }
        }

        إذا (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            إذا (display) {
                display->fullscreen_window = عدم;
            }

            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                إذا (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } وإلا {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    أرجع true;

error:
    إذا (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    أرجع false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ثابت SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (mode) {
        إذا (!SDL_GetFullscreenModeMatch(mode)) {
            أرجع SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } وإلا {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    إذا (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    أرجع true;
}

ثابت SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);
    CHECK_WINDOW_NOT_POPUP(window, عدم);

    إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
        أرجع SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } وإلا {
        أرجع SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

فراغ *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    إذا (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        أرجع عدم;
    }
    أرجع _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ثابت SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    إذا (mode) {
        أرجع mode->format;
    } وإلا {
        أرجع SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_سم_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_كولي | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

ساكن SDL_INLINE bool IsAcceptingDragAndDrop(فراغ)
{
    إذا (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        أرجع true;
    }
    أرجع false;
}

// prepare a newly-created window
ساكن SDL_INLINE فراغ PrepareDragAndDropSupport(SDL_Window *window)
{
    إذا (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
فراغ SDL_ToggleDragAndDropSupport(فراغ)
{
    إذا (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        لكل (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(صحيح *كدي)
{
    إذا (كدي) {
        *كدي = 0;
    }

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    SDL_Window *window;
    صحيح لمب_added = 0;
    صحيح لمب_windows = 0;
    لكل (window = _this->windows; window; window = window->next) {
        ++لمب_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((لمب_windows + 1) * حجم(*windows));
    إذا (!windows) {
        أرجع عدم;
    }

    لكل (window = _this->windows; window; window = window->next) {
        windows[لمب_added++] = window;
        إذا (لمب_added == لمب_windows) {
            // Race condition? Multi-threading not supported, ignore it
            اكسر;
        }
    }
    windows[لمب_added] = عدم;

    إذا (كدي) {
        *كدي = لمب_added;
    }
    أرجع windows;
}

ساكن فراغ ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    إذا (!SDL_WINDOW_IS_POPUP(window)) {
        إذا (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        إذا (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        إذا (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        إذا (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        إذا (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        إذا (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

ساكن فراغ SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    إذا (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } وإلا {
        ApplyWindowFlags(window, flags);
        إذا (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#إذا defined(SDL_PLATFORM_LINUX)
    إذا (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_درج(window, 0.0f);
    }
#endif
}

ساكن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    أرجع SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساكن bool SDL_DllNotSupported(ثابت حرف *name)
{
    أرجع SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ساكن بنية {
    ثابت حرف *property_name;
    SDL_WindowFlags flag;
    bool invert_درج;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_كولي_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_كولي,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_سم_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_سم_PIXEL_DENSITY,  false },
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
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_لمب_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_لمب, 0);

    لكل (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        إذا (SDL_WindowFlagProperties[i].invert_درج) {
            إذا (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } وإلا {
            إذا (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    أرجع flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ثابت حرف *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, عدم);
    صحيح x = (صحيح)SDL_Get_لمب_Property(props, SDL_PROP_WINDOW_CREATE_X_لمب, SDL_WINDOWPOS_UNDEFINED);
    صحيح y = (صحيح)SDL_Get_لمب_Property(props, SDL_PROP_WINDOW_CREATE_Y_لمب, SDL_WINDOWPOS_UNDEFINED);
    صحيح w = (صحيح)SDL_Get_لمب_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_لمب, 0);
    صحيح h = (صحيح)SDL_Get_لمب_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_لمب, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, عدم);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    إذا (!_this) {
        // Initialize the video system if needed
        إذا (!SDL_Init(SDL_INIT_VIDEO)) {
            أرجع عدم;
        }

        // Make clang-tidy happy
        إذا (!_this) {
            أرجع عدم;
        }
    }

    إذا ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        أرجع عدم;
    }

    إذا ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        إذا (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            أرجع عدم;
        }

        // Tooltip and popup menu window must specify a parent window
        إذا (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            أرجع عدم;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    إذا (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned صحيح)type_flags);
        أرجع عدم;
    }

    // Make sure the display list is up to date for window placement
    إذا (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    إذا (w < 1) {
        w = 1;
    }
    إذا (h < 1) {
        h = 1;
    }

    إذا (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        إذا ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وإلا إذا ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        إذا (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        إذا (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            إذا (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            إذا (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned صحيح)graphics_flags);
        أرجع عدم;
    }

    // Some platforms have certain graphics backends enabled by default
    إذا (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    إذا (flags & SDL_WINDOW_OPENGL) {
        إذا (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            أرجع عدم;
        }
        إذا (!SDL_GL_LoadLibrary(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_WINDOW_VULKAN) {
        إذا (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            أرجع عدم;
        }
        إذا (!SDL_Vulkan_LoadLibrary(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_WINDOW_METAL) {
        إذا (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            أرجع عدم;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, حجم(*window));
    إذا (!window) {
        أرجع عدم;
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
    إذا (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    إذا (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    إذا (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    إذا (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    إذا (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_تور_Error();
        SDL_DestroyWindow(window);
        SDL_چرو_Error();
        أرجع عدم;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#إذا !defined(SDL_PLATFORM_WINDOWS)
    إذا (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    إذا (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    أرجع window;
}

SDL_Window *SDL_CreateWindow(ثابت حرف *title, صحيح w, صحيح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    إذا (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_لمب, w);
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_لمب, h);
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_لمب, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    أرجع window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, صحيح offset_x, صحيح offset_y, صحيح w, صحيح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    إذا (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        أرجع عدم;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_X_لمب, offset_x);
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_Y_لمب, offset_y);
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_لمب, w);
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_لمب, h);
    SDL_Set_لمب_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_لمب, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    أرجع window;
}

ساكن bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    إذا (!_this->ReconfigureWindow) {
        أرجع false;
    }

    ثابت SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_SetError("Conflicting window flags specified");
    }

    إذا ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        إذا (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            أرجع false;
        }
    } وإلا {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        إذا (!_this->ReconfigureWindow(_this, window, 0)) {
            أرجع false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        إذا (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        إذا (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    إذا (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(عدم);
        إذا (!loaded_opengl) {
            أرجع false;
        }
    } وإلا إذا (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(عدم);
        إذا (!loaded_vulkan) {
            أرجع false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    إذا (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        إذا (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        إذا (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        أرجع false;
    }

    window->flags |= graphics_flags;

    أرجع true;
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
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_SetError("Conflicting window flags specified");
    }

    إذا ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } وإلا {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    إذا (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    إذا (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ثابت bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    إذا ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        إذا (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } وإلا {
            need_gl_unload = true;
        }
    } وإلا إذا (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    إذا ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        إذا (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } وإلا {
            need_vulkan_unload = true;
        }
    } وإلا إذا (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    إذا (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    إذا (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    إذا (need_gl_load) {
        إذا (!SDL_GL_LoadLibrary(عدم)) {
            أرجع false;
        }
        loaded_opengl = true;
    }

    إذا (need_vulkan_load) {
        إذا (!SDL_Vulkan_LoadLibrary(عدم)) {
            أرجع false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    إذا (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        إذا (!_this->CreateSDLWindow(_this, window, 0)) {
            إذا (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            إذا (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            أرجع false;
        }
    }

    إذا (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    إذا (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    إذا (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    إذا (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    إذا (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    إذا (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    إذا (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    أرجع true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    إذا (!SDL_ReconfigureWindowInternal(window, flags)) {
        أرجع SDL_RecreateWindow(window, flags);
    }

    أرجع true;
}

bool SDL_HasWindows(فراغ)
{
    أرجع _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    أرجع window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (id) {
        لكل (window = _this->windows; window; window = window->next) {
            إذا (window->id == id) {
                أرجع window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    أرجع عدم;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    أرجع window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    إذا (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    أرجع window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    أرجع window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ثابت حرف *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (title == window->title) {
        أرجع true;
    }
    إذا (!title) {
        title = "";
    }
    إذا (window->title && SDL_strcmp(title, window->title) == 0) {
        أرجع true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    إذا (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    أرجع true;
}

ثابت حرف *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    أرجع window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        أرجع SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    إذا (!window->icon) {
        أرجع false;
    }

    إذا (!_this->SetWindowIcon) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, صحيح x, صحيح y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ثابت صحيح w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ثابت صحيح h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    إذا (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    إذا (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    إذا (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        إذا (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وإلا إذا (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        إذا (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        إذا (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            إذا (!SDL_GetDisplayBounds(displayID, &bounds)) {
                أرجع false;
            }
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } وإلا {
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
    إذا (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    إذا (_this->SetWindowPosition) {
        ثابت bool result = _this->SetWindowPosition(_this, window);
        إذا (result) {
            SDL_SyncIfRequired(window);
        }
        أرجع result;
    }

    أرجع SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, صحيح *x, صحيح *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#وإلا
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    إذا (use_display_origin) {
        SDL_DisplayID displayID;

        إذا (x) {
            *x = 0;
        }
        إذا (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        إذا (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            إذا (x) {
                *x = bounds.x;
            }
            إذا (y) {
                *y = bounds.y;
            }
        }
    } وإلا {
        ثابت bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        إذا (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        إذا (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    أرجع true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (!_this->SetWindowBordered) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    إذا (want != have) {
        إذا (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } وإلا {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    أرجع true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (!_this->SetWindowResizable) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    إذا (want != have) {
        إذا (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } وإلا {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    أرجع true;
}

bool SDL_Set_Window_Always_On_كولي(SDL_Window *window, bool on_كولي)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (!_this->Set_Window_Always_On_كولي) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = on_كولي;
    ثابت bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_كولي) != 0);
    إذا (want != have) {
        إذا (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_كولي;
        } وإلا {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_كولي;
        }
        _this->Set_Window_Always_On_كولي(_this, window, want);
    }

    أرجع true;
}

bool SDL_SetWindowSize(SDL_Window *window, صحيح w, صحيح h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        أرجع SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        أرجع SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    عائم new_aspect = w / (عائم)h;
    إذا (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (صحيح)SDL_roundf(h * window->max_aspect);
    } وإلا إذا (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (صحيح)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    إذا (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    إذا (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    إذا (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    إذا (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    إذا (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

bool SDL_GetWindowSize(SDL_Window *window, صحيح *w, صحيح *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    إذا (w) {
        *w = window->w;
    }
    إذا (h) {
        *h = window->h;
    }
    أرجع true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, عائم min_aspect, عائم max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    إذا (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    أرجع SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, عائم *min_aspect, عائم *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    إذا (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    أرجع true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, صحيح *كولي, صحيح *هغو, صحيح *bottom, صحيح *دام)
{
    صحيح dummy = 0;

    إذا (!كولي) {
        كولي = &dummy;
    }
    إذا (!هغو) {
        هغو = &dummy;
    }
    إذا (!دام) {
        دام = &dummy;
    }
    إذا (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *كولي = *هغو = *bottom = *دام = 0;

    CHECK_WINDOW_MAGIC(window, false);

    إذا (!_this->GetWindowBordersSize) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->GetWindowBordersSize(_this, window, كولي, هغو, bottom, دام);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, صحيح *w, صحيح *h)
{
    صحيح filter;

    CHECK_WINDOW_MAGIC(window, false);

    إذا (!w) {
        w = &filter;
    }

    إذا (!h) {
        h = &filter;
    }

    إذا (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } وإلا {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ثابت SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        إذا ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } وإلا {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        إذا (mode) {
            *w = (صحيح)SDL_ceilf(*w * mode->pixel_density);
            *h = (صحيح)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    أرجع true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, صحيح min_w, صحيح min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        أرجع SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        أرجع SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        أرجع SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    إذا (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    أرجع SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, صحيح *min_w, صحيح *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    إذا (min_w) {
        *min_w = window->min_w;
    }
    إذا (min_h) {
        *min_h = window->min_h;
    }
    أرجع true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, صحيح max_w, صحيح max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        أرجع SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        أرجع SDL_InvalidParamError("max_h");
    }

    إذا ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        أرجع SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    إذا (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    أرجع SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, صحيح *max_w, صحيح *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    إذا (max_w) {
        *max_w = window->max_w;
    }
    إذا (max_h) {
        *max_h = window->max_h;
    }
    أرجع true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!(window->flags & SDL_WINDOW_HIDDEN)) {
        أرجع true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    إذا (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        أرجع true;
    }

    إذا (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } وإلا {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    لكل (child = window->first_child; child; child = child->next_sibling) {
        إذا (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            اكسر;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    أرجع true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        أرجع true;
    }

    // Hide all child windows
    لكل (child = window->first_child; child; child = child->next_sibling) {
        إذا (child->flags & SDL_WINDOW_HIDDEN) {
            اكسر;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    إذا (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } وإلا {
        SDL_SetMouseFocus(عدم);
        SDL_SetKeyboardFocus(عدم);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    أرجع true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        أرجع true;
    }
    إذا (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    أرجع true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (!_this->MaximizeWindow) {
        أرجع SDL_Unsupported();
    }

    إذا (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        أرجع SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        أرجع true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    أرجع true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (!_this->MinimizeWindow) {
        أرجع SDL_Unsupported();
    }

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        أرجع true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    أرجع true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (!_this->RestoreWindow) {
        أرجع SDL_Unsupported();
    }

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        أرجع true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    أرجع true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        إذا (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } وإلا {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        أرجع true;
    }

    إذا (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    إذا (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    إذا (result) {
        SDL_SyncIfRequired(window);
    }

    أرجع result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (_this->SyncWindow) {
        أرجع _this->SyncWindow(_this, window);
    } وإلا {
        أرجع true;
    }
}

ساكن bool ShouldAttemptTextureFramebuffer(فراغ)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    إذا (!_this->CreateWindowFramebuffer) {
        أرجع true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    إذا (hint && *hint) {
        إذا (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } وإلا {
            attempt_texture_framebuffer = true;
        }
    } وإلا {
        إذا (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } وإلا {
            attempt_texture_framebuffer = false;
        }
    }
    أرجع attempt_texture_framebuffer;
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
    إذا (!_this->checked_texture_framebuffer) {
        إذا (ShouldAttemptTextureFramebuffer()) {
            إذا (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } وإلا {
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

    إذا (!created_framebuffer) {
        إذا (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            أرجع عدم;
        }

        إذا (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            أرجع عدم;
        }
    }

    إذا (window->surface) {
        // We may have gone recursive and already created the surface
        أرجع window->surface;
    }

    أرجع SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    أرجع window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    إذا (!window->surface_valid) {
        إذا (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = عدم;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        إذا (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    أرجع window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, صحيح vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!_this->SetWindowFramebufferVSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, صحيح *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!_this->GetWindowFramebufferVSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    أرجع SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ثابت SDL_Rect *rects,
                                 صحيح numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!window->surface_valid) {
        أرجع SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    أرجع _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = عدم;
        window->surface_valid = false;
    }

    إذا (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        إذا (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    أرجع true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, عائم opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    إذا (!_this->SetWindowOpacity) {
        أرجع SDL_Unsupported();
    }

    إذا (opacity < 0.0f) {
        opacity = 0.0f;
    } وإلا إذا (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    إذا (result) {
        window->opacity = opacity;
    }

    أرجع result;
}

عائم SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    أرجع window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    إذا (window == parent) {
        أرجع SDL_SetError("Cannot set the parent of a window to itself.");
    }

    إذا (!_this->SetWindowParent) {
        أرجع SDL_Unsupported();
    }

    إذا (window->flags & SDL_WINDOW_MODAL) {
        أرجع SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    إذا (window->parent == parent) {
        أرجع true;
    }

    ثابت bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : عدم);

    أرجع ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (!_this->SetWindowModal) {
        أرجع SDL_Unsupported();
    }

    إذا (modal) {
        إذا (!window->parent) {
            أرجع SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } وإلا إذا (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } وإلا {
        أرجع true; // Already not modal, so nothing to do.
    }

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        أرجع true;
    }

    أرجع _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_شغرو_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    طالما (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        إذا (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_شغرو_FOCUS);
        }
    }

    *new_focus = focus;
    أرجع set_focus;
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
        إذا (w == window) {
            found_higher_focus = true;
            اكسر;
        }
    }

    أرجع !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    إذا ((want != have) && (_this->SetWindowFocusable)) {
        إذا (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } وإلا {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        إذا (!_this->SetWindowFocusable(_this, window, want)) {
            أرجع false;
        }
    }

    أرجع true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    إذا ((want != have) && (_this->SetWindowFillDocument)) {
        إذا (!_this->SetWindowFillDocument(_this, window, want)) {
            أرجع false;
        } وإلا إذا (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } وإلا {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    أرجع true;
}

فراغ SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    إذا (window->flags & SDL_WINDOW_شغرو_FOCUS) {
        إذا (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } وإلا {
            mouse_grabbed = false;
        }

        إذا (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } وإلا {
            keyboard_grabbed = false;
        }
    } وإلا {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    إذا (mouse_grabbed || keyboard_grabbed) {
        إذا (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            إذا (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            إذا (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } وإلا إذا (_this->grabbed_window == window) {
        _this->grabbed_window = عدم; // ungrabbing input.
    }

    إذا (_this->SetWindowMouseGrab) {
        إذا (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    إذا (_this->SetWindowKeyboardGrab) {
        إذا (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    إذا (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = عدم;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        إذا (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } وإلا {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } وإلا {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    إذا (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (window->flags & SDL_WINDOW_HIDDEN) {
        إذا (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } وإلا {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } وإلا {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    إذا (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    أرجع window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    أرجع window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(فراغ)
{
    إذا (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        أرجع _this->grabbed_window;
    } وإلا {
        أرجع عدم;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ثابت SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!_this->SetWindowMouseRect) {
        أرجع SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    إذا (!rect) {
        rect = &zero;
    }

    إذا (SDL_memcmp(&window->mouse_rect, rect, حجم(*rect)) == 0) {
        أرجع true;
    }
    SDL_memcpy(&window->mouse_rect, rect, حجم(*rect));

    أرجع _this->SetWindowMouseRect(_this, window);
}

ثابت SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    إذا (SDL_RectEmpty(&window->mouse_rect)) {
        أرجع عدم;
    } وإلا {
        أرجع &window->mouse_rect;
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

    إذا (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        أرجع true;
    }

    إذا (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } وإلا {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    إذا (!SDL_UpdateRelativeMouseMode()) {
        إذا (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } وإلا {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        أرجع false;
    }
    أرجع true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (_this->FlashWindow) {
        أرجع _this->FlashWindow(_this, window, operation);
    }

    أرجع SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        أرجع SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    إذا (_this->ApplyWindowProgress) {
        إذا (!_this->ApplyWindowProgress(_this, window)) {
            أرجع false;
        }
    }

    أرجع true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    أرجع window->progress_state;
}

bool SDL_Set_Window_Progress_درج(SDL_Window *window, عائم درج)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    درج = SDL_clamp(درج, 0.0f, 1.f);

    window->progress_درج = درج;

    إذا (_this->ApplyWindowProgress) {
        إذا (!_this->ApplyWindowProgress(_this, window)) {
            أرجع false;
        }
    }

    أرجع true;
}

عائم SDL_Get_Window_Progress_درج(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    أرجع window->progress_درج;
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
    إذا (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ثابت bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        إذا (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_سم_density_modes = false;

            إذا (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_سم_density_modes = true;
            }
            ثابت bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_سم_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            إذا (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } وإلا {
            SDL_zero(window->current_fullscreen_mode);
        }

        إذا (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
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

    إذا ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, عدم);
        إذا (surface) {
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
    إذا (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } وإلا {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ساكن فراغ SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_هغو;
    rect.y = window->safe_inset_كولي;
    rect.w = window->w - (window->safe_inset_دام + window->safe_inset_هغو);
    rect.h = window->h - (window->safe_inset_كولي + window->safe_inset_bottom);
    إذا (SDL_memcmp(&rect, &window->safe_rect, حجم(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

فراغ SDL_SetWindowSafeAreaInsets(SDL_Window *window, صحيح هغو, صحيح دام, صحيح كولي, صحيح bottom)
{
    window->safe_inset_هغو = هغو;
    window->safe_inset_دام = دام;
    window->safe_inset_كولي = كولي;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    إذا (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    إذا (rect) {
        إذا (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } وإلا {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    أرجع true;
}

فراغ SDL_OnWindowMinimized(SDL_Window *window)
{
    إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
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

    إذا (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

فراغ SDL_OnWindowEnter(SDL_Window *window)
{
    إذا (_this->OnWindowEnter) {
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

    إذا (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

ساكن bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ثابت حرف *hint;

    إذا (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        أرجع false;
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (Cocoa_IsShowingModalDialog(window)) {
            أرجع false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } وإلا إذا (Cocoa_IsWindowInFullscreenSpace(window)) {
            أرجع false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        خارجي bool Android_JNI_ShouldMinimizeOnFocusLoss(فراغ);
        إذا (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            أرجع false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    إذا (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        إذا (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            أرجع true;
        } وإلا {
            أرجع false;
        }
    }
    أرجع SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

فراغ SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    إذا (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(فراغ)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    إذا (focus) {
        // Get the toplevel parent window.
        طالما (focus->parent) {
            focus = focus->parent;
        }
    }

    أرجع focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->لمب_renderers + 1) * حجم(*renderers));
    إذا (!renderers) {
        أرجع false;
    }

    window->renderers = renderers;
    window->renderers[window->لمب_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    أرجع true;
}

فراغ SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    لكل (صحيح i = 0; i < window->لمب_renderers; ++i) {
        إذا (window->renderers[i] == renderer) {
            إذا (i < (window->لمب_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->لمب_renderers - i - 1) * حجم(window->renderers[i]));
            }
            --window->لمب_renderers;
            اكسر;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    إذا (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, عدم) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

فراغ SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    طالما (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    إذا (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    إذا (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_شغرو_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    إذا (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    لكل (صحيح i = 0; i < _this->لمب_displays; ++i) {
        إذا (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = عدم;
        }
    }

    // Make sure this window no longer has focus
    إذا (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(عدم);
    }
    إذا ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    إذا (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(عدم);
    }

    // Make no context current if this is the current context window
    إذا (window->flags & SDL_WINDOW_OPENGL) {
        إذا (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, عدم);
        }
    }

    إذا (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    إذا (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    إذا (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->grabbed_window == window) {
        _this->grabbed_window = عدم; // ungrabbing input.
    }

    إذا (_this->current_glwin == window) {
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
    إذا (window->next) {
        window->next->prev = window->prev;
    }
    إذا (window->prev) {
        window->prev->next = window->next;
    } وإلا {
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
    إذا (!_this) {
        أرجع true;
    }
    أرجع !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(فراغ)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (!_this->suspend_screensaver) {
        أرجع true;
    }
    _this->suspend_screensaver = false;
    إذا (_this->SuspendScreenSaver) {
        أرجع _this->SuspendScreenSaver(_this);
    }

    أرجع SDL_Unsupported();
}

bool SDL_DisableScreenSaver(فراغ)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->suspend_screensaver) {
        أرجع true;
    }
    _this->suspend_screensaver = true;
    إذا (_this->SuspendScreenSaver) {
        أرجع _this->SuspendScreenSaver(_this);
    }

    أرجع SDL_Unsupported();
}

فراغ SDL_QuitVideo(فراغ)
{
    صحيح i;

    إذا (!_this) {
        أرجع;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#إذا 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    طالما (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    إذا (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    إذا (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    لكل (i = _this->لمب_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->لمب_displays == 0);
    SDL_free(_this->displays);
    _this->displays = عدم;

    SDL_CancelClipboardData(0);

    إذا (_this->primary_selection_text) {
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

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->gl_config.driver_loaded) {
        إذا (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            أرجع SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } وإلا {
        إذا (!_this->GL_LoadLibrary) {
            أرجع SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    إذا (result) {
        ++_this->gl_config.driver_loaded;
    } وإلا {
        إذا (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    أرجع result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ثابت حرف *proc)
{
    SDL_FunctionPointer func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;
    إذا (_this->GL_GetProcAddress) {
        إذا (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } وإلا {
            SDL_SetError("No GL driver has been loaded");
        }
    } وإلا {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    أرجع func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ثابت حرف *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;

    إذا (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } وإلا {
        SDL_SetError("No EGL library has been loaded");
    }

    أرجع func;
#وإلا
    SDL_SetError("SDL was not built with EGL support");
    أرجع عدم;
#endif
}

فراغ SDL_GL_UnloadLibrary(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع;
    }
    إذا (_this->gl_config.driver_loaded > 0) {
        إذا (--_this->gl_config.driver_loaded > 0) {
            أرجع;
        }
        إذا (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
تعريفنوع GLenum (APIENTRY* PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

ساكن SDL_INLINE bool isAtLeastGL3(ثابت حرف *verstr)
{
    أرجع verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت حرف *extension)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت حرف *extensions;
    ثابت حرف *start;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    إذا (where || *extension == '\0') {
        أرجع false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    إذا (start && *start == '0') {
        أرجع false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint لمب_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        إذا ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            أرجع false;
        }

#ifndef GL_لمب_EXTENSIONS
#define GL_لمب_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_لمب_EXTENSIONS, &لمب_exts);
        لكل (i = 0; i < لمب_exts; i++) {
            ثابت حرف *thisext = (ثابت حرف *)glGetStringiFunc(GL_EXTENSIONS, i);
            إذا (SDL_strcmp(thisext, extension) == 0) {
                أرجع true;
            }
        }

        أرجع false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ثابت حرف *)glGetStringFunc(GL_EXTENSIONS);
    إذا (!extensions) {
        أرجع false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    لكل (;;) {
        where = SDL_strstr(start, extension);
        إذا (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        إذا (where == extensions || *(where - 1) == ' ') {
            إذا (*terminator == ' ' || *terminator == '\0') {
                أرجع true;
            }
        }

        start = terminator;
    }
    أرجع false;
#وإلا
    أرجع false;
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
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    إذا (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } وإلا إذا (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } وإلا إذا (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } وإلا {
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
    إذا (!_this) {
        أرجع;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

فراغ SDL_GL_ResetAttributes(فراغ)
{
    إذا (!_this) {
        أرجع;
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

    إذا (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, صحيح درج)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    result = true;
    بدل (attr) {
    حالة SDL_GL_RED_SIZE:
        _this->gl_config.red_size = درج;
        اكسر;
    حالة SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = درج;
        اكسر;
    حالة SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = درج;
        اكسر;
    حالة SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = درج;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = درج;
        اكسر;
    حالة SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = درج;
        اكسر;
    حالة SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = درج;
        اكسر;
    حالة SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = درج;
        اكسر;
    حالة SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = درج;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = درج;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = درج;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = درج;
        اكسر;
    حالة SDL_GL_STEREO:
        _this->gl_config.stereo = درج;
        اكسر;
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = درج;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = درج;
        اكسر;
    حالة SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = درج;
        اكسر;
    حالة SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = درج;
        اكسر;
    حالة SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = درج;
        اكسر;
    حالة SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = درج;
        اكسر;
    حالة SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = درج;
        اكسر;
    حالة SDL_GL_CONTEXT_FLAGS:
        إذا (درج & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", درج);
            اكسر;
        }
        _this->gl_config.flags = درج;
        اكسر;
    حالة SDL_GL_CONTEXT_PROFILE_MASK:
        إذا (درج != 0 &&
            درج != SDL_GL_CONTEXT_PROFILE_CORE &&
            درج != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            درج != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", درج);
            اكسر;
        }
        _this->gl_config.profile_mask = درج;
        اكسر;
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = درج;
        اكسر;
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = درج;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = درج;
        اكسر;
    حالة SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = درج;
        اكسر;
    حالة SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = درج;
        اكسر;
    حالة SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = درج;
        اكسر;
    افتراضي:
        result = SDL_SetError("Unknown OpenGL attribute");
        اكسر;
    }
    أرجع result;
#وإلا
    أرجع SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحيح *درج)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_هغو;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!درج) {
        أرجع SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *درج = 0;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
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
#وإلا
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *درج = _this->gl_config.double_buffer;
        أرجع true;
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
#وإلا
    حالة SDL_GL_ACCUM_RED_SIZE:
    حالة SDL_GL_ACCUM_GREEN_SIZE:
    حالة SDL_GL_ACCUM_BLUE_SIZE:
    حالة SDL_GL_ACCUM_ALPHA_SIZE:
    حالة SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *درج = 0;
        أرجع true;
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
        إذا (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            أرجع false;
        }

        *درج = rsize + gsize + bsize + asize;
        أرجع true;
    }
    حالة SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *درج = (_this->gl_config.accelerated != 0);
        أرجع true;
    }
    حالة SDL_GL_RETAINED_BACKING:
    {
        *درج = _this->gl_config.retained_backing;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *درج = _this->gl_config.major_version;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *درج = _this->gl_config.minor_version;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_FLAGS:
    {
        *درج = _this->gl_config.flags;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *درج = _this->gl_config.profile_mask;
        أرجع true;
    }
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *درج = _this->gl_config.share_with_current_context;
        أرجع true;
    }
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *درج = _this->gl_config.framebuffer_srgb_capable;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_NO_ERROR:
    {
        *درج = _this->gl_config.no_error;
        أرجع true;
    }
    حالة SDL_GL_EGL_PLATFORM:
    {
        *درج = _this->gl_config.egl_platform;
        أرجع true;
    }
    حالة SDL_GL_FLOATBUFFERS:
    {
        إذا (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            اكسر;
        } وإلا {
            أرجع 0;
        }
    }
    افتراضي:
        أرجع SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (attachmentattrib && isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        إذا (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        إذا (glGetFramebufferAttachmentParameterivFunc) {
            إذا (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            إذا (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            إذا (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)درج);
            } وإلا {
                *درج = 0;
            }
            إذا (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } وإلا {
            أرجع false;
        }
    } وإلا
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        إذا (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)درج);
        } وإلا {
            أرجع false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    إذا (!glGetErrorFunc) {
        أرجع false;
    }

    error = glGetErrorFunc();
    إذا (error != GL_NO_ERROR) {
        إذا (error == GL_INVALID_ENUM) {
            أرجع SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } وإلا إذا (error == GL_INVALID_درج) {
            أرجع SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        أرجع SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    إذا (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *درج = (*درج == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    أرجع true;
#وإلا
    أرجع SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = عدم;
    CHECK_WINDOW_MAGIC(window, عدم);

    إذا (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        أرجع عدم;
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحيح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    إذا (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    إذا (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, عدم);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, عدم);
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    إذا (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        إذا (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            إذا (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } وإلا {
                supported = isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            إذا (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    أرجع ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        أرجع true;
    }

    إذا (!context) {
        window = عدم;
    } وإلا إذا (window) {
        CHECK_WINDOW_MAGIC(window, false);

        إذا (!(window->flags & SDL_WINDOW_OPENGL)) {
            أرجع SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } وإلا إذا (!_this->gl_allow_no_surface) {
        أرجع SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    إذا (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, عدم);
        SDL_SetTLS(&_this->current_glctx_tls, context, عدم);
    }
    أرجع result;
}

SDL_Window *SDL_GL_GetCurrentWindow(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(فراغ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع EGL_NO_DISPLAY;
    }
    إذا (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        أرجع EGL_NO_DISPLAY;
    }
    أرجع _this->egl_data->egl_display;
#وإلا
    SDL_SetError("SDL was not built with EGL support");
    أرجع عدم;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(فراغ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        أرجع عدم;
    }
    أرجع _this->egl_data->egl_config;
#وإلا
    SDL_SetError("SDL was not built with EGL support");
    أرجع عدم;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        أرجع عدم;
    }
    إذا (_this->GL_GetEGLSurface) {
        أرجع _this->GL_GetEGLSurface(_this, window);
    }
    أرجع عدم;
#وإلا
    SDL_SetError("SDL was not built with EGL support");
    أرجع عدم;
#endif
}

bool SDL_GL_SetSwapInterval(صحيح interval)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_SetError("No OpenGL context has been made current");
    } وإلا إذا (_this->GL_SetSwapInterval) {
        أرجع _this->GL_SetSwapInterval(_this, interval);
    } وإلا {
        أرجع SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(صحيح *interval)
{
    CHECK_PARAM(!interval) {
       أرجع SDL_InvalidParamError("interval");
    }

    *interval = 0;

    إذا (!_this) {
        أرجع SDL_SetError("no video driver");
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_SetError("no current context");
    } وإلا إذا (_this->GL_GetSwapInterval) {
        أرجع _this->GL_GetSwapInterval(_this, interval);
    } وإلا {
        أرجع SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!(window->flags & SDL_WINDOW_OPENGL)) {
        أرجع SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    إذا (SDL_GL_GetCurrentWindow() != window) {
        أرجع SDL_SetError("The specified window has not been made current");
    }

    أرجع _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        أرجع SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        أرجع SDL_InvalidParamError("context");
    }

    إذا (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(عدم, عدم);
    }

    أرجع _this->GL_DestroyContext(_this, context);
}

#إذا 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ساكن فراغ Create_Mask_From_Color_مبودي_Or_Alpha(SDL_Surface *icon, Uint8 *mask, صحيح flags)
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
                    إذا (*pixels++ == colorkey) {
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
                    إذا ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } وإلا إذا ((flags & 2)
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
                    إذا ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } وإلا إذا ((flags & 2)
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
    إذا (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        إذا (mask == عدم) {
            صحيح mask_len = icon->h * (icon->w + 7) / 8;
            صحيح flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            إذا (mask == عدم) {
                أرجع;
            }
            SDL_memset(mask, ~0, mask_len);
            إذا (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            إذا (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            إذا (flags) {
                Create_Mask_From_Color_مبودي_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } وإلا {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_شغرو_Type SDL_Get_Text_شغرو_Type(SDL_PropertiesID props)
{
    أرجع (SDL_Text_شغرو_Type)SDL_Get_لمب_Property(props, SDL_PROP_TEXTINPUT_TYPE_لمب, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_شغرو_Capitalization(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_لمب)) {
        أرجع (SDL_Capitalization)SDL_Get_لمب_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_لمب, SDL_CAPITALIZE_NONE);
    }

    بدل (SDL_Get_Text_شغرو_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_TEXT:
        أرجع SDL_CAPITALIZE_SENTENCES;
    حالة SDL_TEXTINPUT_TYPE_TEXT_NAME:
        أرجع SDL_CAPITALIZE_كلموم;
    افتراضي:
        أرجع SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_شغرو_Autocorrect(SDL_PropertiesID props)
{
    أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_شغرو_Multiline(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_RETURN_مبودي_HIDES_IME, false)) {
        أرجع false;
    } وإلا {
        أرجع true;
    }
}

ساكن bool AutoShowingScreenKeyboard(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    إذا (!hint) {
        // This hint is currently only used by the X11 video driver
        إذا (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    إذا (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

bool SDL_Start_Text_شغرو(SDL_Window *window)
{
    أرجع SDL_Start_Text_شغرو_With_Properties(window, 0);
}

bool SDL_Start_Text_شغرو_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (window->text_شغرو_props) {
        SDL_DestroyProperties(window->text_شغرو_props);
        window->text_شغرو_props = 0;
    }

    إذا (props) {
        window->text_شغرو_props = SDL_CreateProperties();
        إذا (!window->text_شغرو_props) {
            أرجع false;
        }
        إذا (!SDL_CopyProperties(props, window->text_شغرو_props)) {
            أرجع false;
        }
    }

    إذا (_this->Set_Text_شغرو_Properties) {
        _this->Set_Text_شغرو_Properties(_this, window, props);
    }

    إذا (!window->text_شغرو_active) {
        // Start the text input system
        إذا (_this->Start_Text_شغرو) {
            إذا (!_this->Start_Text_شغرو(_this, window, props)) {
                أرجع false;
            }
        }
        window->text_شغرو_active = true;
    }

    // Show the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        إذا (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    أرجع true;
}

bool SDL_Text_شغرو_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    أرجع window->text_شغرو_active;
}

bool SDL_Stop_Text_شغرو(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (window->text_شغرو_active) {
        // Stop the text input system
        إذا (_this->Stop_Text_شغرو) {
            _this->Stop_Text_شغرو(_this, window);
        }
        window->text_شغرو_active = false;
    }

    // Hide the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        إذا (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    أرجع true;
}

bool SDL_Set_Text_شغرو_Area(SDL_Window *window, ثابت SDL_Rect *rect, صحيح cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (rect) {
        SDL_copyp(&window->text_شغرو_rect, rect);
        window->text_شغرو_cursor = cursor;
    } وإلا {
        SDL_zero(window->text_شغرو_rect);
        window->text_شغرو_cursor = 0;
    }

    إذا (_this && _this->Update_Text_شغرو_Area) {
        إذا (!_this->Update_Text_شغرو_Area(_this, window)) {
            أرجع false;
        }
    }
    أرجع true;
}

bool SDL_Get_Text_شغرو_Area(SDL_Window *window, SDL_Rect *rect, صحيح *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (rect) {
        SDL_copyp(rect, &window->text_شغرو_rect);
    }
    إذا (cursor) {
        *cursor = window->text_شغرو_cursor;
    }
    أرجع true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (_this->ClearComposition) {
        أرجع _this->ClearComposition(_this, window);
    }
    أرجع true;
}

bool SDL_HasScreenKeyboardSupport(فراغ)
{
    إذا (_this && _this->HasScreenKeyboardSupport) {
        أرجع _this->HasScreenKeyboardSupport(_this);
    }
    أرجع false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    أرجع _this->screen_keyboard_shown;
}

فراغ SDL_SendScreenKeyboardShown(فراغ)
{
    إذا (!_this || _this->screen_keyboard_shown) {
        أرجع;
    }

    _this->screen_keyboard_shown = true;

    إذا (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_تور_Event(&event);
    }
}

فراغ SDL_SendScreenKeyboardHidden(فراغ)
{
    إذا (!_this || !_this->screen_keyboard_shown) {
        أرجع;
    }

    _this->screen_keyboard_shown = false;

    إذا (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_تور_Event(&event);
    }
}

صحيح SDL_Get_Message_Box_كدي(فراغ)
{
    أرجع SDL_GetAtomicInt(&SDL_messagebox_كدي);
}

bool SDL_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID)
{
    صحيح dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        أرجع SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        أرجع SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    حرف *titlecpy = عدم;
    حرف *msgcpy = عدم;
    إذا (messageboxdata->title) {
        ثابت size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(حرف, slen, &titleisstack);
        إذا (!titlecpy) {
            أرجع false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    إذا (messageboxdata->message) {
        ثابت size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        إذا (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            أرجع false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (فراغ)SDL_AtomicIncRef(&SDL_messagebox_كدي);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    إذا (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, حجم(*messageboxdata));
    mbdata.title = titlecpy;
    إذا (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    إذا (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    إذا (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } وإلا {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        إذا (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            طالما (driver_attempt && (*driver_attempt != 0) && !result) {
                ثابت حرف *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                لكل (صحيح i = 0; bootstrap[i]; ++i) {
                    إذا (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        إذا (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        اكسر;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : عدم;
            }
        } وإلا {
            لكل (صحيح i = 0; bootstrap[i]; ++i) {
                إذا (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    اكسر;
                }
            }
        }
    }

    إذا (!result) {
        ثابت حرف *error = SDL_GetError();

        إذا (!*error) {
            SDL_SetError("No message system available");
        }
    } وإلا {
        SDL_ClearError();
    }

    (فراغ)SDL_AtomicDecRef(&SDL_messagebox_كدي);

    إذا (current_window) {
        SDL_RaiseWindow(current_window);
    }

    إذا (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    أرجع result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ثابت حرف *title, ثابت حرف *message, SDL_Window *window)
{
#إذا defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_دام;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_دام = gsp_Has_Gpu_دام();
    إذا (!has_Gpu_دام)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    إذا (!has_Gpu_دام)
        gfxExit();

    أرجع true;
#وإلا
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

    أرجع SDL_ShowMessageBox(&data, عدم);
#endif
}

bool SDL_ShouldAllowTopmost(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, صحيح x, صحيح y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    إذا (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        أرجع true;
    }

    أرجع SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, فراغ *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!_this->SetWindowHitTest) {
        أرجع SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    أرجع _this->SetWindowHitTest(window, callback != عدم);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    إذا (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        أرجع SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    إذا (!props) {
        أرجع false;
    }

    إذا (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        إذا (!surface) {
            أرجع false;
        }
    } وإلا {
        surface = عدم;
    }

    إذا (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        أرجع false;
    }

    إذا (_this->UpdateWindowShape) {
        إذا (!_this->UpdateWindowShape(_this, window, surface)) {
            أرجع false;
        }
    }
    أرجع true;
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
    SDL_SendAppEvent(SDL_EVENT_كس_MEMORY);
}

فراغ SDL_OnApplicationWillEnterBackground(فراغ)
{
    إذا (_this) {
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

    إذا (_this) {
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

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->vulkan_config.loader_loaded) {
        إذا (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            أرجع SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } وإلا {
        إذا (!_this->Vulkan_LoadLibrary) {
            أرجع SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    إذا (result) {
        _this->vulkan_config.loader_loaded++;
    }
    أرجع result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        أرجع عدم;
    }
    أرجع (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

فراغ SDL_Vulkan_UnloadLibrary(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع;
    }
    إذا (_this->vulkan_config.loader_loaded > 0) {
        إذا (--_this->vulkan_config.loader_loaded > 0) {
            أرجع;
        }
        إذا (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *كدي)
{
    Uint32 tmpcount = 0;
    إذا (!كدي) {
        كدي = &tmpcount;
    }

    إذا (!_this->Vulkan_GetInstanceExtensions) {
        *كدي = 0;
        SDL_Unsupported();
        أرجع عدم;
    }

    أرجع _this->Vulkan_GetInstanceExtensions(_this, كدي);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ثابت بنية VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    إذا (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        أرجع false;
    }

    CHECK_PARAM(!instance) {
        أرجع SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        إذا (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        إذا (SDL_Vulkan_LoadLibrary(عدم)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } وإلا {
            أرجع SDL_SetError("failed to load Vulkan library");
        }
    }

    أرجع _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

فراغ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية VkAllocationCallbacks *allocator)
{
    إذا (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        أرجع false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        أرجع false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        أرجع false;
    }

    إذا (_this->Vulkan_GetPresentationSupport) {
        أرجع _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    أرجع true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    إذا (!_this->Metal_CreateView) {
        SDL_Unsupported();
        أرجع عدم;
    }

    إذا (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        إذا (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    أرجع _this->Metal_CreateView(_this, window);
}

فراغ SDL_Metal_DestroyView(SDL_MetalView view)
{
    إذا (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

فراغ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    إذا (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            أرجع عدم;
        }
        أرجع _this->Metal_GetLayer(_this, view);
    } وإلا {
        SDL_SetError("Metal is not supported.");
        أرجع عدم;
    }
}

#إذا defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ثابت حرف *SDL_GetCSSCursorName(SDL_SystemCursor id, ثابت حرف **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    بدل (id) {
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
        أرجع "default";

    حالة SDL_SYSTEM_CURSOR_TEXT:
        أرجع "text";

    حالة SDL_SYSTEM_CURSOR_WAIT:
        أرجع "wait";

    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
        أرجع "crosshair";

    حالة SDL_SYSTEM_CURSOR_PROGRESS:
        أرجع "progress";

    حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        إذا (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        أرجع "nwse-resize";

    حالة SDL_SYSTEM_CURSOR_NESW_RESIZE:
        إذا (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        أرجع "nesw-resize";

    حالة SDL_SYSTEM_CURSOR_EW_RESIZE:
        إذا (fallback_name) {
            *fallback_name = "col-resize";
        }
        أرجع "ew-resize";

    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
        إذا (fallback_name) {
            *fallback_name = "row-resize";
        }
        أرجع "ns-resize";

    حالة SDL_SYSTEM_CURSOR_MOVE:
        إذا (fallback_name) {
            *fallback_name = "all-scroll";
        }
        أرجع "move";

    حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        أرجع "not-allowed";

    حالة SDL_SYSTEM_CURSOR_POINTER:
        أرجع "pointer";

    حالة SDL_SYSTEM_CURSOR_NW_RESIZE:
        أرجع "nw-resize";

    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
        أرجع "n-resize";

    حالة SDL_SYSTEM_CURSOR_NE_RESIZE:
        أرجع "ne-resize";

    حالة SDL_SYSTEM_CURSOR_E_RESIZE:
        أرجع "e-resize";

    حالة SDL_SYSTEM_CURSOR_SE_RESIZE:
        أرجع "se-resize";

    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
        أرجع "s-resize";

    حالة SDL_SYSTEM_CURSOR_SW_RESIZE:
        أرجع "sw-resize";

    حالة SDL_SYSTEM_CURSOR_W_RESIZE:
        أرجع "w-resize";

    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        أرجع "context-menu";

    حالة SDL_SYSTEM_CURSOR_HELP:
        أرجع "help";

    حالة SDL_SYSTEM_CURSOR_CELL:
        أرجع "cell";

    حالة SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        أرجع "vertical-text";

    حالة SDL_SYSTEM_CURSOR_ALIAS:
        أرجع "alias";

    حالة SDL_SYSTEM_CURSOR_COPY:
        أرجع "copy";

    حالة SDL_SYSTEM_CURSOR_NO_DROP:
        أرجع "no-drop";

    حالة SDL_SYSTEM_CURSOR_GRAB:
        أرجع "grab";

    حالة SDL_SYSTEM_CURSOR_GRABBING:
        أرجع "grabbing";

    حالة SDL_SYSTEM_CURSOR_COL_RESIZE:
        أرجع "col-resize";

    حالة SDL_SYSTEM_CURSOR_ROW_RESIZE:
        أرجع "row-resize";

    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        إذا (fallback_name) {
            *fallback_name = "move";
        }
        أرجع "all-scroll";

    حالة SDL_SYSTEM_CURSOR_ZOOM_IN:
        أرجع "zoom-in";

    حالة SDL_SYSTEM_CURSOR_ZOOM_OUT:
        أرجع "zoom-out";

    افتراضي:
        أرجع "default";
    }
}
#endif

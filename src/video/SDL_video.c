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

#אם defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#אם defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
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
        החזר result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        החזר result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        החזר result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        החזר result;                                                  \
    }

#אם defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
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
    אם (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        החזר true;
    }
    החזר false;
}

ساكن bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    החזר !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ساكن bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    החזר !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ساكن bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    החזר !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ساكن bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    החזר !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ساكن bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    החזר !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ساكن bool syncHint;

ساكن فراغ SDL_SyncHintWatcher(فراغ *userdata, ثابت حرف *name, ثابت حرف *oldValue, ثابت حرف *newValue)
{
    syncHint = SDL_GetStringBoolean(newValue, false);
}

ساكن فراغ SDL_SyncIfRequired(SDL_Window *window)
{
    אם (syncHint) {
        SDL_SyncWindow(window);
    }
}

ساكن فراغ SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    אם (window->parent) {
        אם (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        אם (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } אחרת {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = عدم;
    }

    אם (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        אם (parent->first_child) {
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
#אם (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    אם (_this->GL_CreateContext) {
        החזר SDL_WINDOW_OPENGL;
    }
#endif
#אם defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    אם (_this->Metal_CreateView) {
        החזר SDL_WINDOW_METAL;
    }
#endif
#אם defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    אם (SDL_strcmp(_this->name, "openvr") == 0) {
        החזר SDL_WINDOW_OPENGL;
    }
#endif
    החזר 0;
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

    אם (!data) {
        SDL_Renderer *renderer = عدم;
        ثابت حرف *render_driver = عدم;

        // See if there's a render driver being requested
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        אם (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        אם (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        אם (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = عدم;
        }

        حرف *render_driver_copy = عدم;
        אם (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            אם (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                حرف *prev = render_driver_copy;
                حرف *ptr = prev;
                כלעוד ((ptr = SDL_strchr(ptr, ',')) != عدم) {
                    *ptr = '\0';
                    ثابت bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    אם (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } אחרת {
                        ptr++;
                        prev = ptr;
                    }
                }

                אם (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        אם (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            אם (!renderer) {
                // The error for this specific renderer has already been set
                החזר false;
            }
        } אחרת {
            SDL_assert(render_driver_copy == عدم);
            ثابت صحيح total = SDL_GetNumRenderDrivers();
            עבור (i = 0; i < total; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                אם (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    אם (renderer) {
                        اكسر; // this will work.
                    }
                }
            }
            אם (!renderer) {
                החזר SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != عدم); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, حجم(*data));
        אם (!data) {
            SDL_DestroyRenderer(renderer);
            החזר false;
        }
        אם (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            החזר false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, عدم);
    אם (!texture_formats) {
        החזר false;
    }

    // Free any old texture and pixel data
    אם (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = عدم;
    }
    SDL_free(data->pixels);
    data->pixels = عدم;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    עבור (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        אם (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
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
    אם (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        החזר false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        אם (!data->pixels) {
            החזר false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, عدم);

    החזר true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحيح vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    אם (!data) {
        החזר false;
    }
    אם (!data->renderer) {
        החזר false;
    }
    החזר SDL_SetRenderVSync(data->renderer, vsync);
}

ساكن bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحيح *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    אם (!data) {
        החזר false;
    }
    אם (!data->renderer) {
        החזר false;
    }
    החזר SDL_GetRenderVSync(data->renderer, vsync);
}

ساكن bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    فراغ *src;
    صحيح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);
    אם (!data || !data->texture) {
        החזר SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    אם (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (فراغ *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        אם (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            החזר false;
        }

        אם (!SDL_RenderTexture(data->renderer, data->texture, عدم, عدم)) {
            החזר false;
        }

        SDL_RenderPresent(data->renderer);
    }
    החזר true;
}

ساكن فراغ SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    אם (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, عدم);

        אם (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        אם (data->renderer) {
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

    אם (a->w != b->w) {
        החזר b->w - a->w;
    } אחרת אם (a->h != b->h) {
        החזר b->h - a->h;
    } אחרת אם (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        החזר SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } אחרת אם (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        החזר SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } אחרת אם (a_refresh_rate != b_refresh_rate) {
        החזר b_refresh_rate - a_refresh_rate;
    } אחרת אם (a_pixel_density != b_pixel_density) {
        החזר a_pixel_density - b_pixel_density;
    }
    החזר 0;
}

bool SDL_UninitializedVideo(فراغ)
{
    החזר SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ساكن ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحيح SDL_GetNumVideoDrivers(فراغ)
{
    ساكن صحيح num_drivers = -1;

    אם (num_drivers >= 0) {
        החזר num_drivers;
    }

    num_drivers = 0;

    // Build a list of unique video drivers.
    עבור (صحيح i = 0; bootstrap[i] != عدم; ++i) {
        bool duplicate = false;
        עבור (صحيح j = 0; j < i; ++j) {
            אם (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                اكسر;
            }
        }

        אם (!duplicate) {
            deduped_bootstrap[num_drivers++] = bootstrap[i];
        }
    }

    החזר num_drivers;
}

ثابت حرف *SDL_GetVideoDriver(صحيح index)
{
    CHECK_PARAM(index < 0 || index >= SDL_GetNumVideoDrivers()) {
        SDL_InvalidParamError("index");
        החזר عدم;
    }
    החזר deduped_bootstrap[index]->name;
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
    אם (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    אם (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        اذهب pre_driver_error;
    }
    init_events = true;
    אם (!SDL_InitKeyboard()) {
        اذهب pre_driver_error;
    }
    init_keyboard = true;
    אם (!SDL_PreInitMouse()) {
        اذهب pre_driver_error;
    }
    init_mouse = true;
    אם (!SDL_InitTouch()) {
        اذهب pre_driver_error;
    }
    init_touch = true;
    אם (!SDL_InitPen()) {
        اذهب pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = عدم;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    אם (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    אם (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    אם (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        כלעוד (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            עבור (i = 0; bootstrap[i]; ++i) {
                אם (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    אם (video) {
                        اكسر;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : عدم;
        }
    } אחרת {
        עבור (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            אם (video) {
                اكسر;
            }
        }
    }
    אם (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } אחרת {
        אם (driver_name) {
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
    אם (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        החזר false;
    }

    // Make sure some displays were added
    אם (_this->num_displays == 0) {
        SDL_QuitVideo();
        החזר SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, عدم);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    אם (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    החזר true;

pre_driver_error:
    SDL_assert(_this == عدم);
    אם (init_pen) {
        SDL_QuitPen();
    }
    אם (init_touch) {
        SDL_QuitTouch();
    }
    אם (init_mouse) {
        SDL_QuitMouse();
    }
    אם (init_keyboard) {
        SDL_QuitKeyboard();
    }
    אם (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    החזר false;
}

ثابت حرف *SDL_GetCurrentVideoDriver(فراغ)
{
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    החזר _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(فراغ)
{
    החזר _this;
}

bool SDL_OnVideoThread(فراغ)
{
    החזר (_this && SDL_GetCurrentThreadID() == _this->thread);
}

فراغ SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    אם (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(فراغ)
{
    אם (_this) {
        החזר _this->system_theme;
    } אחרת {
        החזר SDL_SYSTEM_THEME_UNKNOWN;
    }
}

فراغ SDL_UpdateDesktopBounds(فراغ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    אם (displays) {
        עבור (صحيح i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            אם (SDL_GetDisplayBounds(displays[i], &bounds)) {
                אם (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } אחרת {
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
    אם (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    אם (mode->refresh_rate_numerator > 0) {
        אם (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (عائم)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } אחרת {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ثابت SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    אם (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, حجم(display.desktop_mode));
    }
    החזר SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحيح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(حجم(*new_display));
    אם (!new_display) {
        החזר 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->num_displays + 1) * حجم(*displays));
    אם (!displays) {
        SDL_free(new_display);
        החזר 0;
    }
    _this->displays = displays;
    _this->displays[_this->num_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    אם (display->name) {
        new_display->name = SDL_strdup(display->name);
    } אחרת {
        حرف name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    אם (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    עבור (i = 0; i < new_display->num_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    אם (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    החזר id;
}

فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    עבור (window = _this->windows; window; window = window->next) {
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
    אם (display_index < 0) {
        החזר;
    }

    display = _this->displays[display_index];

    אם (send_event) {
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

    אם (display_index < (_this->num_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->num_displays - display_index - 1) * حجم(_this->displays[display_index]));
    }
    --_this->num_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحيح *count)
{
    صحيح i;
    SDL_DisplayID *displays;

    אם (!_this) {
        אם (count) {
            *count = 0;
        }

        SDL_UninitializedVideo();
        החזר عدم;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->num_displays + 1) * حجم(*displays));
    אם (displays) {
        אם (count) {
            *count = _this->num_displays;
        }

        עבור (i = 0; i < _this->num_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } אחרת {
        אם (count) {
            *count = 0;
        }
    }
    החזר displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحيح display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    אם (display_index < 0) {
        החזר عدم;
    }
    החזר _this->displays[display_index];
}

ساكن SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    אם (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    אם (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    החזר displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    החזר SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(فراغ)
{
    אם (!_this || _this->num_displays == 0) {
        SDL_UninitializedVideo();
        החזר 0;
    }
    החזר _this->displays[0]->id;
}

صحيح SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    صحيح display_index;

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר -1;
    }

    עבור (display_index = 0; display_index < _this->num_displays; ++display_index) {
        אם (displayID == _this->displays[display_index]->id) {
            החזר display_index;
        }
    }
    SDL_SetError("Invalid display");
    החזר -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    החזר display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    החזר SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    אם (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    החזר display->props;
}

ثابت حرف *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    החזר display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        החזר SDL_InvalidParamError("rect");
    }

    אם (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        אם (_this->GetDisplayBounds(_this, display, rect)) {
            החזר true;
        }
    }

    // Assume that the displays are left to right
    אם (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } אחרת {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    החזר true;
}

ساكن صحيح ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    החזר hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        החזר SDL_InvalidParamError("rect");
    }

    אם (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        החזר true;
    }

    אם (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        אם (_this->GetDisplayUsableBounds(_this, display, rect)) {
            החזר true;
        }
    }

    // Oh well, just give the entire display bounds.
    החזר SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    אם (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        החזר display->natural_orientation;
    } אחרת {
        // Default to landscape if the driver hasn't set it
        החזר SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    אם (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        החזר display->current_orientation;
    } אחרת {
        // Default to landscape if the driver hasn't set it
        החזר SDL_ORIENTATION_LANDSCAPE;
    }
}

فراغ SDL_SetDisplayContentScale(SDL_VideoDisplay *display, عائم scale)
{
    אם (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        עבור (window = _this->windows; window; window = window->next) {
            אם (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

عائم SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    החזר display->content_scale;
}

فراغ SDL_SetWindowHDRProperties(SDL_Window *window, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    אם (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        אם (send_event) {
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

	אם (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    אם (changed && !SDL_DriverSendsHDRChanges(_this)) {
        עבור (SDL_Window *w = display->device->windows; w; w = w->next) {
            אם (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ساكن فراغ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    אם (display->num_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ساكن ثابت SDL_DisplayMode *SDL_GetFullscreenModeMatch(ثابت SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    אם (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        החזר عدم;
    }

    SDL_memcpy(&fullscreen_mode, mode, حجم(fullscreen_mode));
    אם (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = عدم;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    אם (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        אם (!mode) {
            עבור (صحيح i = 0; i < display->num_fullscreen_modes; ++i) {
                אם (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], حجم(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }

        // Search for a mode with the same characteristics
        אם (!mode) {
            עבור (صحيح i = 0; i < display->num_fullscreen_modes; ++i) {
                אם (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }
    }
    החזר mode;
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
    עבור (i = 0; i < nmodes; ++i) {
        אם (cmpmodes(&new_mode, &modes[i]) == 0) {
            החזר false;
        }
    }

    // Go ahead and add the new mode
    אם (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        אם (!modes) {
            החזר false;
        }

        אם (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            עבור (i = 0; i < nmodes; ++i) {
                אם (display->current_mode == &display->fullscreen_modes[i]) {
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

    החזר true;
}

فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحيح i;

    עבור (i = display->num_fullscreen_modes; i--;) {
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

    אם (count) {
        *count = 0;
    }

    CHECK_DISPLAY_MAGIC(display, عدم);

    SDL_UpdateFullscreenDisplayModes(display);

    num_modes = display->num_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((num_modes + 1) * حجم(*result) + num_modes * حجم(**result));
    אם (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((num_modes + 1) * حجم(*result)));
        אם (num_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, num_modes * حجم(*modes));
        }
        עבור (i = 0; i < num_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = عدم;

        אם (count) {
            *count = num_modes;
        }
    } אחרת {
        אם (count) {
            *count = 0;
        }
    }
    החזר result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, صحيح w, صحيح h, عائم refresh_rate, bool include_high_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        החזר SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_DisplayMode *mode, *closest = عدم;
    عائم aspect_ratio;
    صحيح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    אם (h > 0) {
        aspect_ratio = (عائم)w / h;
    } אחרת {
        aspect_ratio = 1.0f;
    }

    אם (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    עבור (i = 0; i < display->num_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        אם (w > mode->w) {
            // Out of sorted modes large enough here
            اكسر;
        }
        אם (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            استمر;
        }
        אם (mode->pixel_density > 1.0f && !include_high_density_modes) {
            استمر;
        }
        אם (closest) {
            عائم current_aspect_ratio = (عائم)mode->w / mode->h;
            عائم closest_aspect_ratio = (عائم)closest->w / closest->h;
            אם (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                استمر;
            }

            אם (mode->w == closest->w && mode->h == closest->h) {
                אם (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    استمر;
                }
                אם (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    استمر;
                }
            }
        }

        closest = mode;
    }
    אם (!closest) {
        החזר SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    החזר true;
}

ساكن bool DisplayModeChanged(ثابت SDL_DisplayMode *old_mode, ثابت SDL_DisplayMode *new_mode)
{
    החזר ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

فراغ SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    אם (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        החזר;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    אם (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        אם (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ثابت SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    החזר &display->desktop_mode;
}

فراغ SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    אם (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } אחרת {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    אם (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ثابت SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    החזר display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    אם (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        החזר true;
    }

    אם (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    אם (mode == display->current_mode) {
        החזר true;
    }
#endif

    // Actually change the display mode
    אם (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        אם (!result) {
            החזר false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    החזר true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساكن فراغ SDL_GetClosestPointOnRect(ثابت SDL_Rect *rect, SDL_Point *point)
{
    ثابت صحيح right = rect->x + rect->w - 1;
    ثابت صحيح bottom = rect->y + rect->h - 1;

    אם (point->x < rect->x) {
        point->x = rect->x;
    } אחרת אם (point->x > right) {
        point->x = right;
    }

    אם (point->y < rect->y) {
        point->y = rect->y;
    } אחרת אם (point->y > bottom) {
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

    אם (_this) {
        עבור (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            אם (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, عدم)) {
                החזר display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            אם (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    אם (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    החזר closest;
}

فراغ SDL_RelativeToGlobalForWindow(SDL_Window *window, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y)
{
    SDL_Window *w;

    אם (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        עבור (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            אם (!SDL_WINDOW_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    אם (abs_x) {
        *abs_x = rel_x;
    }
    אם (abs_y) {
        *abs_y = rel_y;
    }
}

فراغ SDL_GlobalToRelativeForWindow(SDL_Window *window, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y)
{
    SDL_Window *w;

    אם (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        עבור (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            אם (!SDL_WINDOW_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    אם (rel_x) {
        *rel_x = abs_x;
    }
    אם (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ثابت SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        החזר 0;
    }

    החזר GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ثابت SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        החזר 0;
    }

    החזר GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ساكن SDL_DisplayID GetDisplayAtOrigin(صحيح x, صحيح y)
{
    עבור (صحيح i = 0; i < _this->num_displays; ++i) {
        SDL_Rect rect;
        ثابت SDL_DisplayID cur_id = _this->displays[i]->id;
        אם (SDL_GetDisplayBounds(cur_id, &rect)) {
            אם (x == rect.x && y == rect.y) {
                החזר cur_id;
            }
        }
    }

    החזר 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    صحيح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    אם (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    אם (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        אם (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } אחרת {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    אם (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    החזר displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, عدم);

    // An explicit fullscreen display overrides all
    אם (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    אם (!displayID) {
        displayID = window->pending_displayID;
    }
    אם (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحيح x = window->last_position_pending ? window->pending.x : window->x;
        ثابت صحيح y = window->last_position_pending ? window->pending.y : window->y;
        ثابت صحيح w = window->last_size_pending ? window->pending.w : window->w;
        ثابت صحيح h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        אם (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    אם (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    החזר SDL_GetVideoDisplay(displayID);
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
    אם (fs_display) {
        SDL_SetNumberProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } אחרת {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    החזר GetDisplayForWindow(window);
}

ساكن فراغ SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    אם (SDL_SendsDisplayChanges(_this)) {
        החזר;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    אם (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        אם (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            אם (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                صحيح old_area = old_overlap.w * old_overlap.h;
                صحيح new_area = new_overlap.w * new_overlap.h;
                عائم new_overlap_ratio = (new_area / ((عائم)old_area + new_area));
                אם (new_overlap_ratio < 0.80) {
                    החזר;
                }
            }
        }
    }

    אם (displayID != window->displayID) {
        صحيح i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        עבור (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            אם (display->fullscreen_window == window) {
                אם (display_index != i) {
                    אם (display_index < 0) {
                        display_index = i;
                    } אחרת {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        אם (new_display->fullscreen_window &&
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

    אם (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (عائم)pixel_w / window_w;
    }
    החזר pixel_density;
}

عائم SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    החזר window->display_scale;
}

ساكن فراغ SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    عائم display_scale;

    אם (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } אחרת {
        ثابت عائم pixel_density = SDL_GetWindowPixelDensity(window);
        ثابت عائم content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    אם (display_scale != window->display_scale) {
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
    אם (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    אם (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        אם (!display) {
            // This should never happen, but it did...
            اذهب done;
        }
    } אחרת {
        עבור (i = 0; i < _this->num_displays; ++i) {
            display = _this->displays[i];
            אם (display->fullscreen_window == window) {
                اكسر;
            }
        }
        אם (!display || i == _this->num_displays) {
            // Already not fullscreen on any display
            display = عدم;
        }
    }

    אם (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        אם (mode) {
            window->fullscreen_exclusive = true;
        } אחרת {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#אם defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    אם (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        אם (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            אם (display) {
                display->fullscreen_window = عدم;
            }
            اذهب done;
        }
        אם (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            אם (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                אם (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    اذهب error;
                }
            } אחרת אם (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                עבור (i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    אם (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, عدم);
                        אם (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = عدم;
                    }
                }
            }

            אם (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                اذهب done;
            }
        }
    }
#endif

    אם (display) {
        // Restore the video mode on other displays if needed
        עבור (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            אם (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, عدم);
                other->fullscreen_window = عدم;
            }
        }
    }

    אם (fullscreen) {
        صحيح mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        אם (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        אם (!SDL_SetDisplayModeForDisplay(display, mode)) {
            اذهب error;
        }
        אם (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            אם (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } אחרת {
                resized = true;
            }

            אם (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                אם (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } אחרת אם (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                اذهب error;
            }
        }

        אם (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            אם (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                אם (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } אחרת {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                אם (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                אם (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } אחרת {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } אחרת {
        bool resized = false;

        // Restore the desktop mode
        אם (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, عدم);
        }
        אם (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            אם (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                אם (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } אחרת {
                resized = true;
            }

            אם (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                אם (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } אחרת אם (ret == SDL_FULLSCREEN_FAILED) {
                اذهب error;
            }
        }

        אם (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            אם (display) {
                display->fullscreen_window = عدم;
            }

            אם (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                אם (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } אחרת {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    החזר true;

error:
    אם (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    החזר false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ثابت SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (mode) {
        אם (!SDL_GetFullscreenModeMatch(mode)) {
            החזר SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } אחרת {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#אם defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    אם (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    אם (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    החזר true;
}

ثابت SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);
    CHECK_WINDOW_NOT_POPUP(window, عدم);

    אם (window->flags & SDL_WINDOW_FULLSCREEN) {
        החזר SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } אחרת {
        החזר SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

فراغ *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    אם (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        החזר عدم;
    }
    החזר _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ثابت SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    אם (mode) {
        החזר mode->format;
    } אחרת {
        החזר SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

ساكن SDL_INLINE bool IsAcceptingDragAndDrop(فراغ)
{
    אם (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        החזר true;
    }
    החזר false;
}

// prepare a newly-created window
ساكن SDL_INLINE فراغ PrepareDragAndDropSupport(SDL_Window *window)
{
    אם (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
فراغ SDL_ToggleDragAndDropSupport(فراغ)
{
    אם (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        עבור (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(صحيح *count)
{
    אם (count) {
        *count = 0;
    }

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }

    SDL_Window *window;
    صحيح num_added = 0;
    صحيح num_windows = 0;
    עבור (window = _this->windows; window; window = window->next) {
        ++num_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((num_windows + 1) * حجم(*windows));
    אם (!windows) {
        החזר عدم;
    }

    עבור (window = _this->windows; window; window = window->next) {
        windows[num_added++] = window;
        אם (num_added == num_windows) {
            // Race condition? Multi-threading not supported, ignore it
            اكسر;
        }
    }
    windows[num_added] = عدم;

    אם (count) {
        *count = num_added;
    }
    החזר windows;
}

ساكن فراغ ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    אם (!SDL_WINDOW_IS_POPUP(window)) {
        אם (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        אם (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        אם (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        אם (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        אם (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        אם (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

ساكن فراغ SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    אם (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } אחרת {
        ApplyWindowFlags(window, flags);
        אם (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#אם defined(SDL_PLATFORM_LINUX)
    אם (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_SetWindowProgressValue(window, 0.0f);
    }
#endif
}

ساكن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    החזר SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساكن bool SDL_DllNotSupported(ثابت حرف *name)
{
    החזר SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
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

    עבור (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        אם (SDL_WindowFlagProperties[i].invert_value) {
            אם (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } אחרת {
            אם (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    החזר flags;
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

    אם (!_this) {
        // Initialize the video system if needed
        אם (!SDL_Init(SDL_INIT_VIDEO)) {
            החזר عدم;
        }

        // Make clang-tidy happy
        אם (!_this) {
            החזר عدم;
        }
    }

    אם ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        החזר عدم;
    }

    אם ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        אם (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            החזר عدم;
        }

        // Tooltip and popup menu window must specify a parent window
        אם (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            החזר عدم;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    אם (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned صحيح)type_flags);
        החזר عدم;
    }

    // Make sure the display list is up to date for window placement
    אם (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    אם (w < 1) {
        w = 1;
    }
    אם (h < 1) {
        h = 1;
    }

    אם (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        אם ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } אחרת אם ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        אם (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        אם (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        אם (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            אם (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        אם (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            אם (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    אם (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned صحيح)graphics_flags);
        החזר عدم;
    }

    // Some platforms have certain graphics backends enabled by default
    אם (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    אם (flags & SDL_WINDOW_OPENGL) {
        אם (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            החזר عدم;
        }
        אם (!SDL_GL_LoadLibrary(عدم)) {
            החזר عدم;
        }
    }

    אם (flags & SDL_WINDOW_VULKAN) {
        אם (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            החזר عدم;
        }
        אם (!SDL_Vulkan_LoadLibrary(عدم)) {
            החזר عدم;
        }
    }

    אם (flags & SDL_WINDOW_METAL) {
        אם (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            החזר عدم;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, حجم(*window));
    אם (!window) {
        החזר عدم;
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
    אם (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    אם (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    אם (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    אם (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    אם (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_PushError();
        SDL_DestroyWindow(window);
        SDL_PopError();
        החזר عدم;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#אם !defined(SDL_PLATFORM_WINDOWS)
    אם (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    אם (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    החזר window;
}

SDL_Window *SDL_CreateWindow(ثابت حرف *title, صحيح w, صحيح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    אם (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    החזר window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, صحيح offset_x, صحيح offset_y, صحيح w, صحيح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    אם (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        החזר عدم;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, offset_x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, offset_y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    החזר window;
}

ساكن bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    אם (!_this->ReconfigureWindow) {
        החזר false;
    }

    ثابت SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    אם (graphics_flags & (graphics_flags - 1)) {
        החזר SDL_SetError("Conflicting window flags specified");
    }

    אם ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        החזר SDL_ContextNotSupported("OpenGL");
    }
    אם ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        החזר SDL_ContextNotSupported("Vulkan");
    }
    אם ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        החזר SDL_ContextNotSupported("Metal");
    }

    אם (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        אם (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            החזר false;
        }
    } אחרת {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        אם (!_this->ReconfigureWindow(_this, window, 0)) {
            החזר false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        אם (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        אם (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    אם (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(عدم);
        אם (!loaded_opengl) {
            החזר false;
        }
    } אחרת אם (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(عدم);
        אם (!loaded_vulkan) {
            החזר false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    אם (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        אם (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        אם (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        החזר false;
    }

    window->flags |= graphics_flags;

    החזר true;
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
    אם (graphics_flags & (graphics_flags - 1)) {
        החזר SDL_SetError("Conflicting window flags specified");
    }

    אם ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        החזר SDL_ContextNotSupported("OpenGL");
    }
    אם ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        החזר SDL_ContextNotSupported("Vulkan");
    }
    אם ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        החזר SDL_ContextNotSupported("Metal");
    }

    אם (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } אחרת {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    אם (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    אם (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ثابت bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    אם ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        אם (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } אחרת {
            need_gl_unload = true;
        }
    } אחרת אם (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    אם ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        אם (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } אחרת {
            need_vulkan_unload = true;
        }
    } אחרת אם (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    אם (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    אם (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    אם (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    אם (need_gl_load) {
        אם (!SDL_GL_LoadLibrary(عدم)) {
            החזר false;
        }
        loaded_opengl = true;
    }

    אם (need_vulkan_load) {
        אם (!SDL_Vulkan_LoadLibrary(عدم)) {
            החזר false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    אם (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        אם (!_this->CreateSDLWindow(_this, window, 0)) {
            אם (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            אם (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            החזר false;
        }
    }

    אם (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    אם (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    אם (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    אם (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    אם (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    אם (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    אם (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    החזר true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    אם (!SDL_ReconfigureWindowInternal(window, flags)) {
        החזר SDL_RecreateWindow(window, flags);
    }

    החזר true;
}

bool SDL_HasWindows(فراغ)
{
    החזר _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    החזר window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    אם (id) {
        עבור (window = _this->windows; window; window = window->next) {
            אם (window->id == id) {
                החזר window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    החזר عدم;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    החזר window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    אם (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    החזר window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    החזר window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ثابت حرف *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (title == window->title) {
        החזר true;
    }
    אם (!title) {
        title = "";
    }
    אם (window->title && SDL_strcmp(title, window->title) == 0) {
        החזר true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    אם (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    החזר true;
}

ثابت حرف *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    החזר window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        החזר SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    אם (!window->icon) {
        החזר false;
    }

    אם (!_this->SetWindowIcon) {
        החזר SDL_Unsupported();
    }

    החזר _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, صحيح x, صحيح y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ثابت صحيح w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ثابت صحيح h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    אם (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    אם (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    אם (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        אם (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } אחרת אם (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        אם (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        אם (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            אם (!SDL_GetDisplayBounds(displayID, &bounds)) {
                החזר false;
            }
        }
        אם (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        אם (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } אחרת {
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
    אם (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    אם (_this->SetWindowPosition) {
        ثابت bool result = _this->SetWindowPosition(_this, window);
        אם (result) {
            SDL_SyncIfRequired(window);
        }
        החזר result;
    }

    החזר SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, صحيح *x, صحيح *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#אחרת
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    אם (use_display_origin) {
        SDL_DisplayID displayID;

        אם (x) {
            *x = 0;
        }
        אם (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        אם (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            אם (x) {
                *x = bounds.x;
            }
            אם (y) {
                *y = bounds.y;
            }
        }
    } אחרת {
        ثابت bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        אם (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        אם (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    החזר true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (!_this->SetWindowBordered) {
        החזר SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    אם (want != have) {
        אם (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } אחרת {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    החזר true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (!_this->SetWindowResizable) {
        החזר SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    אם (want != have) {
        אם (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } אחרת {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    החזר true;
}

bool SDL_SetWindowAlwaysOnTop(SDL_Window *window, bool on_top)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (!_this->SetWindowAlwaysOnTop) {
        החזר SDL_Unsupported();
    }

    ثابت bool want = on_top;
    ثابت bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_TOP) != 0);
    אם (want != have) {
        אם (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        } אחרת {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_TOP;
        }
        _this->SetWindowAlwaysOnTop(_this, window, want);
    }

    החזר true;
}

bool SDL_SetWindowSize(SDL_Window *window, صحيح w, صحيح h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        החזר SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        החזר SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    عائم new_aspect = w / (عائم)h;
    אם (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (صحيح)SDL_roundf(h * window->max_aspect);
    } אחרת אם (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (صحيح)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    אם (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    אם (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    אם (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    אם (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    אם (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } אחרת {
        החזר SDL_Unsupported();
    }
    החזר true;
}

bool SDL_GetWindowSize(SDL_Window *window, صحيح *w, صحيح *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    אם (w) {
        *w = window->w;
    }
    אם (h) {
        *h = window->h;
    }
    החזר true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, عائم min_aspect, عائم max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    אם (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    החזר SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, عائم *min_aspect, عائم *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    אם (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    החזר true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, صحيح *top, صحيح *left, صحيح *bottom, صحيح *right)
{
    صحيح dummy = 0;

    אם (!top) {
        top = &dummy;
    }
    אם (!left) {
        left = &dummy;
    }
    אם (!right) {
        right = &dummy;
    }
    אם (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *top = *left = *bottom = *right = 0;

    CHECK_WINDOW_MAGIC(window, false);

    אם (!_this->GetWindowBordersSize) {
        החזר SDL_Unsupported();
    }

    החזר _this->GetWindowBordersSize(_this, window, top, left, bottom, right);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, صحيح *w, صحيح *h)
{
    صحيح filter;

    CHECK_WINDOW_MAGIC(window, false);

    אם (!w) {
        w = &filter;
    }

    אם (!h) {
        h = &filter;
    }

    אם (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } אחרת {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ثابت SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        אם ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } אחרת {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        אם (mode) {
            *w = (صحيح)SDL_ceilf(*w * mode->pixel_density);
            *h = (صحيح)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    החזר true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, صحيح min_w, صحيح min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        החזר SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        החזר SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        החזר SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    אם (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    החזר SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, صحيح *min_w, صحيح *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    אם (min_w) {
        *min_w = window->min_w;
    }
    אם (min_h) {
        *min_h = window->min_h;
    }
    החזר true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, صحيح max_w, صحيح max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        החזר SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        החזר SDL_InvalidParamError("max_h");
    }

    אם ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        החזר SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    אם (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    صحيح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحيح h = window->last_size_pending ? window->pending.h : window->floating.h;
    החזר SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, صحيح *max_w, صحيح *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    אם (max_w) {
        *max_w = window->max_w;
    }
    אם (max_h) {
        *max_h = window->max_h;
    }
    החזר true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    אם (!(window->flags & SDL_WINDOW_HIDDEN)) {
        החזר true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    אם (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        החזר true;
    }

    אם (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } אחרת {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    עבור (child = window->first_child; child; child = child->next_sibling) {
        אם (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            اكسر;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    החזר true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        החזר true;
    }

    // Hide all child windows
    עבור (child = window->first_child; child; child = child->next_sibling) {
        אם (child->flags & SDL_WINDOW_HIDDEN) {
            اكسر;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    אם (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } אחרת {
        SDL_SetMouseFocus(عدم);
        SDL_SetKeyboardFocus(عدم);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    החזר true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        החזר true;
    }
    אם (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    החזר true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (!_this->MaximizeWindow) {
        החזר SDL_Unsupported();
    }

    אם (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        החזר SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        החזר true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    החזר true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (!_this->MinimizeWindow) {
        החזר SDL_Unsupported();
    }

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        החזר true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    החזר true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (!_this->RestoreWindow) {
        החזר SDL_Unsupported();
    }

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        החזר true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    החזר true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        אם (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } אחרת {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        החזר true;
    }

    אם (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    אם (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    אם (result) {
        SDL_SyncIfRequired(window);
    }

    החזר result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (_this->SyncWindow) {
        החזר _this->SyncWindow(_this, window);
    } אחרת {
        החזר true;
    }
}

ساكن bool ShouldAttemptTextureFramebuffer(فراغ)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    אם (!_this->CreateWindowFramebuffer) {
        החזר true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    אם (hint && *hint) {
        אם (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } אחרת {
            attempt_texture_framebuffer = true;
        }
    } אחרת {
        אם (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } אחרת {
            attempt_texture_framebuffer = false;
        }
    }
    החזר attempt_texture_framebuffer;
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
    אם (!_this->checked_texture_framebuffer) {
        אם (ShouldAttemptTextureFramebuffer()) {
            אם (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } אחרת {
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

    אם (!created_framebuffer) {
        אם (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            החזר عدم;
        }

        אם (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            החזר عدم;
        }
    }

    אם (window->surface) {
        // We may have gone recursive and already created the surface
        החזר window->surface;
    }

    החזר SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    החזר window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    אם (!window->surface_valid) {
        אם (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = عدم;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        אם (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    החזר window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, صحيح vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (!_this->SetWindowFramebufferVSync) {
        החזר SDL_Unsupported();
    }
    החזר _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, صحيح *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (!_this->GetWindowFramebufferVSync) {
        החזר SDL_Unsupported();
    }
    החזר _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    החזר SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ثابت SDL_Rect *rects,
                                 صحيح numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (!window->surface_valid) {
        החזר SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    החזר _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = عدم;
        window->surface_valid = false;
    }

    אם (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        אם (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    החזר true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, عائم opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    אם (!_this->SetWindowOpacity) {
        החזר SDL_Unsupported();
    }

    אם (opacity < 0.0f) {
        opacity = 0.0f;
    } אחרת אם (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    אם (result) {
        window->opacity = opacity;
    }

    החזר result;
}

عائم SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    החזר window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    אם (window == parent) {
        החזר SDL_SetError("Cannot set the parent of a window to itself.");
    }

    אם (!_this->SetWindowParent) {
        החזר SDL_Unsupported();
    }

    אם (window->flags & SDL_WINDOW_MODAL) {
        החזר SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    אם (window->parent == parent) {
        החזר true;
    }

    ثابت bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : عدم);

    החזר ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (!_this->SetWindowModal) {
        החזר SDL_Unsupported();
    }

    אם (modal) {
        אם (!window->parent) {
            החזר SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } אחרת אם (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } אחרת {
        החזר true; // Already not modal, so nothing to do.
    }

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        החזר true;
    }

    החזר _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_INPUT_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    כלעוד (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        אם (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_INPUT_FOCUS);
        }
    }

    *new_focus = focus;
    החזר set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    עבור (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    עבור (w = current_focus; w != toplevel_parent; w = w->parent) {
        אם (w == window) {
            found_higher_focus = true;
            اكسر;
        }
    }

    החזר !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    אם ((want != have) && (_this->SetWindowFocusable)) {
        אם (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } אחרת {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        אם (!_this->SetWindowFocusable(_this, window, want)) {
            החזר false;
        }
    }

    החזר true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    אם ((want != have) && (_this->SetWindowFillDocument)) {
        אם (!_this->SetWindowFillDocument(_this, window, want)) {
            החזר false;
        } אחרת אם (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } אחרת {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    החזר true;
}

فراغ SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    אם (window->flags & SDL_WINDOW_INPUT_FOCUS) {
        אם (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } אחרת {
            mouse_grabbed = false;
        }

        אם (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } אחרת {
            keyboard_grabbed = false;
        }
    } אחרת {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    אם (mouse_grabbed || keyboard_grabbed) {
        אם (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            אם (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            אם (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } אחרת אם (_this->grabbed_window == window) {
        _this->grabbed_window = عدم; // ungrabbing input.
    }

    אם (_this->SetWindowMouseGrab) {
        אם (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    אם (_this->SetWindowKeyboardGrab) {
        אם (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    אם (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = عدم;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        אם (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } אחרת {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        החזר true;
    }

    אם (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        החזר true;
    }
    אם (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } אחרת {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    אם (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        החזר false;
    }
    החזר true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (window->flags & SDL_WINDOW_HIDDEN) {
        אם (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } אחרת {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        החזר true;
    }

    אם (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        החזר true;
    }
    אם (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } אחרת {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    אם (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        החזר false;
    }
    החזר true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    החזר window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    החזר window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(فراغ)
{
    אם (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        החזר _this->grabbed_window;
    } אחרת {
        החזר عدم;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ثابت SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (!_this->SetWindowMouseRect) {
        החזר SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    אם (!rect) {
        rect = &zero;
    }

    אם (SDL_memcmp(&window->mouse_rect, rect, حجم(*rect)) == 0) {
        החזר true;
    }
    SDL_memcpy(&window->mouse_rect, rect, حجم(*rect));

    החזר _this->SetWindowMouseRect(_this, window);
}

ثابت SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    אם (SDL_RectEmpty(&window->mouse_rect)) {
        החזר عدم;
    } אחרת {
        החזר &window->mouse_rect;
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

    אם (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        החזר true;
    }

    אם (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } אחרת {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    אם (!SDL_UpdateRelativeMouseMode()) {
        אם (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } אחרת {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        החזר false;
    }
    החזר true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        החזר true;
    } אחרת {
        החזר false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (_this->FlashWindow) {
        החזר _this->FlashWindow(_this, window, operation);
    }

    החזר SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        החזר SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    אם (_this->ApplyWindowProgress) {
        אם (!_this->ApplyWindowProgress(_this, window)) {
            החזר false;
        }
    }

    החזר true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    החזר window->progress_state;
}

bool SDL_SetWindowProgressValue(SDL_Window *window, عائم value)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    value = SDL_clamp(value, 0.0f, 1.f);

    window->progress_value = value;

    אם (_this->ApplyWindowProgress) {
        אם (!_this->ApplyWindowProgress(_this, window)) {
            החזר false;
        }
    }

    החזר true;
}

عائم SDL_GetWindowProgressValue(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    החזר window->progress_value;
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
    אם (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ثابت bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        אם (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_high_density_modes = false;

            אם (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_high_density_modes = true;
            }
            ثابت bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_high_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            אם (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } אחרת {
            SDL_zero(window->current_fullscreen_mode);
        }

        אם (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
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

    אם ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, عدم);
        אם (surface) {
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
    אם (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } אחרת {
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
    אם (SDL_memcmp(&rect, &window->safe_rect, حجم(rect)) != 0) {
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
    אם (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    אם (rect) {
        אם (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } אחרת {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    החזר true;
}

فراغ SDL_OnWindowMinimized(SDL_Window *window)
{
    אם (window->flags & SDL_WINDOW_FULLSCREEN) {
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

    אם (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

فراغ SDL_OnWindowEnter(SDL_Window *window)
{
    אם (_this->OnWindowEnter) {
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

    אם (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

ساكن bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ثابت حرف *hint;

    אם (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        החזר false;
    }

#אם defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    אם (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        אם (Cocoa_IsShowingModalDialog(window)) {
            החזר false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } אחרת אם (Cocoa_IsWindowInFullscreenSpace(window)) {
            החזר false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        خارجي bool Android_JNI_ShouldMinimizeOnFocusLoss(فراغ);
        אם (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            החזר false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    אם (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        אם (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            החזר true;
        } אחרת {
            החזר false;
        }
    }
    החזר SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

فراغ SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    אם (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(فراغ)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    אם (focus) {
        // Get the toplevel parent window.
        כלעוד (focus->parent) {
            focus = focus->parent;
        }
    }

    החזר focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->num_renderers + 1) * حجم(*renderers));
    אם (!renderers) {
        החזר false;
    }

    window->renderers = renderers;
    window->renderers[window->num_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    החזר true;
}

فراغ SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    עבור (صحيح i = 0; i < window->num_renderers; ++i) {
        אם (window->renderers[i] == renderer) {
            אם (i < (window->num_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->num_renderers - i - 1) * حجم(window->renderers[i]));
            }
            --window->num_renderers;
            اكسر;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    אם (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, عدم) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

فراغ SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    כלעוד (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    אם (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    אם (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_input_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    אם (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    עבור (صحيح i = 0; i < _this->num_displays; ++i) {
        אם (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = عدم;
        }
    }

    // Make sure this window no longer has focus
    אם (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(عدم);
    }
    אם ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    אם (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(عدم);
    }

    // Make no context current if this is the current context window
    אם (window->flags & SDL_WINDOW_OPENGL) {
        אם (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, عدم);
        }
    }

    אם (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    אם (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    אם (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    אם (_this->grabbed_window == window) {
        _this->grabbed_window = عدم; // ungrabbing input.
    }

    אם (_this->current_glwin == window) {
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
    אם (window->next) {
        window->next->prev = window->prev;
    }
    אם (window->prev) {
        window->prev->next = window->next;
    } אחרת {
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
    אם (!_this) {
        החזר true;
    }
    החזר !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(فراغ)
{
    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }
    אם (!_this->suspend_screensaver) {
        החזר true;
    }
    _this->suspend_screensaver = false;
    אם (_this->SuspendScreenSaver) {
        החזר _this->SuspendScreenSaver(_this);
    }

    החזר SDL_Unsupported();
}

bool SDL_DisableScreenSaver(فراغ)
{
    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }
    אם (_this->suspend_screensaver) {
        החזר true;
    }
    _this->suspend_screensaver = true;
    אם (_this->SuspendScreenSaver) {
        החזר _this->SuspendScreenSaver(_this);
    }

    החזר SDL_Unsupported();
}

فراغ SDL_QuitVideo(فراغ)
{
    صحيح i;

    אם (!_this) {
        החזר;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#אם 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    כלעוד (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    אם (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    אם (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    עבור (i = _this->num_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->num_displays == 0);
    SDL_free(_this->displays);
    _this->displays = عدم;

    SDL_CancelClipboardData(0);

    אם (_this->primary_selection_text) {
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

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }
    אם (_this->gl_config.driver_loaded) {
        אם (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            החזר SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } אחרת {
        אם (!_this->GL_LoadLibrary) {
            החזר SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    אם (result) {
        ++_this->gl_config.driver_loaded;
    } אחרת {
        אם (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    החזר result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ثابت حرف *proc)
{
    SDL_FunctionPointer func;

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    func = عدم;
    אם (_this->GL_GetProcAddress) {
        אם (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } אחרת {
            SDL_SetError("No GL driver has been loaded");
        }
    } אחרת {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    החזר func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ثابت حرف *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    func = عدم;

    אם (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } אחרת {
        SDL_SetError("No EGL library has been loaded");
    }

    החזר func;
#אחרת
    SDL_SetError("SDL was not built with EGL support");
    החזר عدم;
#endif
}

فراغ SDL_GL_UnloadLibrary(فراغ)
{
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר;
    }
    אם (_this->gl_config.driver_loaded > 0) {
        אם (--_this->gl_config.driver_loaded > 0) {
            החזר;
        }
        אם (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#אם defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
تعريفنوع GLenum (APIENTRY* PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

ساكن SDL_INLINE bool isAtLeastGL3(ثابت حرف *verstr)
{
    החזר verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت حرف *extension)
{
#אם defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت حرف *extensions;
    ثابت حرف *start;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    אם (where || *extension == '\0') {
        החזר false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    אם (start && *start == '0') {
        החזר false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    אם (!glGetStringFunc) {
        החזר false;
    }

    אם (isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint num_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        אם ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            החזר false;
        }

#ifndef GL_NUM_EXTENSIONS
#define GL_NUM_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_NUM_EXTENSIONS, &num_exts);
        עבור (i = 0; i < num_exts; i++) {
            ثابت حرف *thisext = (ثابت حرف *)glGetStringiFunc(GL_EXTENSIONS, i);
            אם (SDL_strcmp(thisext, extension) == 0) {
                החזר true;
            }
        }

        החזר false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ثابت حرف *)glGetStringFunc(GL_EXTENSIONS);
    אם (!extensions) {
        החזר false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    עבור (;;) {
        where = SDL_strstr(start, extension);
        אם (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        אם (where == extensions || *(where - 1) == ' ') {
            אם (*terminator == ' ' || *terminator == '\0') {
                החזר true;
            }
        }

        start = terminator;
    }
    החזר false;
#אחרת
    החזר false;
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
#אם defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    אם (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } אחרת אם (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } אחרת אם (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } אחרת {
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
    אם (!_this) {
        החזר;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

فراغ SDL_GL_ResetAttributes(فراغ)
{
    אם (!_this) {
        החזר;
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

    אם (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, صحيح value)
{
#אם defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    אם (!_this) {
        החזר SDL_UninitializedVideo();
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
        אם (value & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", value);
            اكسر;
        }
        _this->gl_config.flags = value;
        اكسر;
    حالة SDL_GL_CONTEXT_PROFILE_MASK:
        אם (value != 0 &&
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
    החזר result;
#אחרת
    החזר SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحيح *value)
{
#אם defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
        החזר SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *value = 0;

    אם (!_this) {
        החזר SDL_UninitializedVideo();
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
#אחרת
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *value = _this->gl_config.double_buffer;
        החזר true;
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
#אחרת
    حالة SDL_GL_ACCUM_RED_SIZE:
    حالة SDL_GL_ACCUM_GREEN_SIZE:
    حالة SDL_GL_ACCUM_BLUE_SIZE:
    حالة SDL_GL_ACCUM_ALPHA_SIZE:
    حالة SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *value = 0;
        החזר true;
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
        אם (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            החזר false;
        }
        אם (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            החזר false;
        }
        אם (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            החזר false;
        }
        אם (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            החזר false;
        }

        *value = rsize + gsize + bsize + asize;
        החזר true;
    }
    حالة SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *value = (_this->gl_config.accelerated != 0);
        החזר true;
    }
    حالة SDL_GL_RETAINED_BACKING:
    {
        *value = _this->gl_config.retained_backing;
        החזר true;
    }
    حالة SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *value = _this->gl_config.major_version;
        החזר true;
    }
    حالة SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *value = _this->gl_config.minor_version;
        החזר true;
    }
    حالة SDL_GL_CONTEXT_FLAGS:
    {
        *value = _this->gl_config.flags;
        החזר true;
    }
    حالة SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *value = _this->gl_config.profile_mask;
        החזר true;
    }
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *value = _this->gl_config.share_with_current_context;
        החזר true;
    }
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *value = _this->gl_config.framebuffer_srgb_capable;
        החזר true;
    }
    حالة SDL_GL_CONTEXT_NO_ERROR:
    {
        *value = _this->gl_config.no_error;
        החזר true;
    }
    حالة SDL_GL_EGL_PLATFORM:
    {
        *value = _this->gl_config.egl_platform;
        החזר true;
    }
    حالة SDL_GL_FLOATBUFFERS:
    {
        אם (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            اكسر;
        } אחרת {
            החזר 0;
        }
    }
    افتراضي:
        החזר SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    אם (!glGetStringFunc) {
        החזר false;
    }

    אם (attachmentattrib && isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        אם (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        אם (glGetFramebufferAttachmentParameterivFunc) {
            אם (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            אם (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            אם (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)value);
            } אחרת {
                *value = 0;
            }
            אם (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } אחרת {
            החזר false;
        }
    } אחרת
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        אם (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)value);
        } אחרת {
            החזר false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    אם (!glGetErrorFunc) {
        החזר false;
    }

    error = glGetErrorFunc();
    אם (error != GL_NO_ERROR) {
        אם (error == GL_INVALID_ENUM) {
            החזר SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } אחרת אם (error == GL_INVALID_VALUE) {
            החזר SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        החזר SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    אם (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *value = (*value == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    החזר true;
#אחרת
    החזר SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = عدم;
    CHECK_WINDOW_MAGIC(window, عدم);

    אם (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        החזר عدم;
    }

#אם defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحيح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    אם (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    אם (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, عدم);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, عدم);
    }

#אם defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    אם (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        אם (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            אם (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } אחרת {
                supported = isAtLeastGL3((ثابت حرف *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            אם (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    החזר ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }

    אם (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        החזר true;
    }

    אם (!context) {
        window = عدم;
    } אחרת אם (window) {
        CHECK_WINDOW_MAGIC(window, false);

        אם (!(window->flags & SDL_WINDOW_OPENGL)) {
            החזר SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } אחרת אם (!_this->gl_allow_no_surface) {
        החזר SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    אם (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, عدم);
        SDL_SetTLS(&_this->current_glctx_tls, context, عدم);
    }
    החזר result;
}

SDL_Window *SDL_GL_GetCurrentWindow(فراغ)
{
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    החזר (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(فراغ)
{
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    החזר (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(فراغ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר EGL_NO_DISPLAY;
    }
    אם (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        החזר EGL_NO_DISPLAY;
    }
    החזר _this->egl_data->egl_display;
#אחרת
    SDL_SetError("SDL was not built with EGL support");
    החזר عدم;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(فراغ)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    אם (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        החזר عدم;
    }
    החזר _this->egl_data->egl_config;
#אחרת
    SDL_SetError("SDL was not built with EGL support");
    החזר عدم;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    אם (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        החזר عدم;
    }
    אם (_this->GL_GetEGLSurface) {
        החזר _this->GL_GetEGLSurface(_this, window);
    }
    החזר عدم;
#אחרת
    SDL_SetError("SDL was not built with EGL support");
    החזר عدم;
#endif
}

bool SDL_GL_SetSwapInterval(صحيح interval)
{
    אם (!_this) {
        החזר SDL_UninitializedVideo();
    } אחרת אם (SDL_GL_GetCurrentContext() == عدم) {
        החזר SDL_SetError("No OpenGL context has been made current");
    } אחרת אם (_this->GL_SetSwapInterval) {
        החזר _this->GL_SetSwapInterval(_this, interval);
    } אחרת {
        החזר SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(صحيح *interval)
{
    CHECK_PARAM(!interval) {
       החזר SDL_InvalidParamError("interval");
    }

    *interval = 0;

    אם (!_this) {
        החזר SDL_SetError("no video driver");
    } אחרת אם (SDL_GL_GetCurrentContext() == عدم) {
        החזר SDL_SetError("no current context");
    } אחרת אם (_this->GL_GetSwapInterval) {
        החזר _this->GL_GetSwapInterval(_this, interval);
    } אחרת {
        החזר SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (!(window->flags & SDL_WINDOW_OPENGL)) {
        החזר SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    אם (SDL_GL_GetCurrentWindow() != window) {
        החזר SDL_SetError("The specified window has not been made current");
    }

    החזר _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        החזר SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        החזר SDL_InvalidParamError("context");
    }

    אם (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(عدم, عدم);
    }

    החזר _this->GL_DestroyContext(_this, context);
}

#אם 0 // FIXME
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
            עבור (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                עבור (x = 0; x < icon->w; ++x) {
                    אם (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        اكسر;

    حالة 2:
        {
            Uint16 *pixels;
            עבור (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                עבור (x = 0; x < icon->w; ++x) {
                    אם ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } אחרת אם ((flags & 2)
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
            עבור (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                עבור (x = 0; x < icon->w; ++x) {
                    אם ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } אחרת אם ((flags & 2)
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
    אם (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        אם (mask == عدم) {
            صحيح mask_len = icon->h * (icon->w + 7) / 8;
            صحيح flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            אם (mask == عدم) {
                החזר;
            }
            SDL_memset(mask, ~0, mask_len);
            אם (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            אם (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            אם (flags) {
                CreateMaskFromColorKeyOrAlpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } אחרת {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_TextInputType SDL_GetTextInputType(SDL_PropertiesID props)
{
    החזר (SDL_TextInputType)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_TYPE_NUMBER, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_GetTextInputCapitalization(SDL_PropertiesID props)
{
    אם (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER)) {
        החזר (SDL_Capitalization)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER, SDL_CAPITALIZE_NONE);
    }

    بدل (SDL_GetTextInputType(props)) {
    حالة SDL_TEXTINPUT_TYPE_TEXT:
        החזר SDL_CAPITALIZE_SENTENCES;
    حالة SDL_TEXTINPUT_TYPE_TEXT_NAME:
        החזר SDL_CAPITALIZE_WORDS;
    افتراضي:
        החזר SDL_CAPITALIZE_NONE;
    }
}

bool SDL_GetTextInputAutocorrect(SDL_PropertiesID props)
{
    החזר SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_GetTextInputMultiline(SDL_PropertiesID props)
{
    אם (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        החזר SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    אם (SDL_GetHintBoolean(SDL_HINT_RETURN_KEY_HIDES_IME, false)) {
        החזר false;
    } אחרת {
        החזר true;
    }
}

ساكن bool AutoShowingScreenKeyboard(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    אם (!hint) {
        // This hint is currently only used by the X11 video driver
        אם (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    אם (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        החזר true;
    } אחרת {
        החזר false;
    }
}

bool SDL_StartTextInput(SDL_Window *window)
{
    החזר SDL_StartTextInputWithProperties(window, 0);
}

bool SDL_StartTextInputWithProperties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (window->text_input_props) {
        SDL_DestroyProperties(window->text_input_props);
        window->text_input_props = 0;
    }

    אם (props) {
        window->text_input_props = SDL_CreateProperties();
        אם (!window->text_input_props) {
            החזר false;
        }
        אם (!SDL_CopyProperties(props, window->text_input_props)) {
            החזר false;
        }
    }

    אם (_this->SetTextInputProperties) {
        _this->SetTextInputProperties(_this, window, props);
    }

    אם (!window->text_input_active) {
        // Start the text input system
        אם (_this->StartTextInput) {
            אם (!_this->StartTextInput(_this, window, props)) {
                החזר false;
            }
        }
        window->text_input_active = true;
    }

    // Show the on-screen keyboard, if desired
    אם (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        אם (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    החזר true;
}

bool SDL_TextInputActive(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    החזר window->text_input_active;
}

bool SDL_StopTextInput(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (window->text_input_active) {
        // Stop the text input system
        אם (_this->StopTextInput) {
            _this->StopTextInput(_this, window);
        }
        window->text_input_active = false;
    }

    // Hide the on-screen keyboard, if desired
    אם (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        אם (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    החזר true;
}

bool SDL_SetTextInputArea(SDL_Window *window, ثابت SDL_Rect *rect, صحيح cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (rect) {
        SDL_copyp(&window->text_input_rect, rect);
        window->text_input_cursor = cursor;
    } אחרת {
        SDL_zero(window->text_input_rect);
        window->text_input_cursor = 0;
    }

    אם (_this && _this->UpdateTextInputArea) {
        אם (!_this->UpdateTextInputArea(_this, window)) {
            החזר false;
        }
    }
    החזר true;
}

bool SDL_GetTextInputArea(SDL_Window *window, SDL_Rect *rect, صحيح *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (rect) {
        SDL_copyp(rect, &window->text_input_rect);
    }
    אם (cursor) {
        *cursor = window->text_input_cursor;
    }
    החזר true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (_this->ClearComposition) {
        החזר _this->ClearComposition(_this, window);
    }
    החזר true;
}

bool SDL_HasScreenKeyboardSupport(فراغ)
{
    אם (_this && _this->HasScreenKeyboardSupport) {
        החזר _this->HasScreenKeyboardSupport(_this);
    }
    החזר false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    החזר _this->screen_keyboard_shown;
}

فراغ SDL_SendScreenKeyboardShown(فراغ)
{
    אם (!_this || _this->screen_keyboard_shown) {
        החזר;
    }

    _this->screen_keyboard_shown = true;

    אם (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

فراغ SDL_SendScreenKeyboardHidden(فراغ)
{
    אם (!_this || !_this->screen_keyboard_shown) {
        החזר;
    }

    _this->screen_keyboard_shown = false;

    אם (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

صحيح SDL_GetMessageBoxCount(فراغ)
{
    החזר SDL_GetAtomicInt(&SDL_messagebox_count);
}

bool SDL_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحيح *buttonID)
{
    صحيح dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        החזר SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        החזר SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    حرف *titlecpy = عدم;
    حرف *msgcpy = عدم;
    אם (messageboxdata->title) {
        ثابت size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(حرف, slen, &titleisstack);
        אם (!titlecpy) {
            החזר false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    אם (messageboxdata->message) {
        ثابت size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        אם (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            החזר false;
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

    אם (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, حجم(*messageboxdata));
    mbdata.title = titlecpy;
    אם (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    אם (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    אם (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } אחרת {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        אם (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            כלעוד (driver_attempt && (*driver_attempt != 0) && !result) {
                ثابت حرف *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                עבור (صحيح i = 0; bootstrap[i]; ++i) {
                    אם (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        אם (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        اكسر;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : عدم;
            }
        } אחרת {
            עבור (صحيح i = 0; bootstrap[i]; ++i) {
                אם (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    اكسر;
                }
            }
        }
    }

    אם (!result) {
        ثابت حرف *error = SDL_GetError();

        אם (!*error) {
            SDL_SetError("No message system available");
        }
    } אחרת {
        SDL_ClearError();
    }

    (فراغ)SDL_AtomicDecRef(&SDL_messagebox_count);

    אם (current_window) {
        SDL_RaiseWindow(current_window);
    }

    אם (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    החזר result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ثابت حرف *title, ثابت حرف *message, SDL_Window *window)
{
#אם defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool hasGpuRight;

    // If the video subsystem has not been initialised, set up graphics temporarily
    hasGpuRight = gspHasGpuRight();
    אם (!hasGpuRight)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    אם (!hasGpuRight)
        gfxExit();

    החזר true;
#אחרת
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

    החזר SDL_ShowMessageBox(&data, عدم);
#endif
}

bool SDL_ShouldAllowTopmost(فراغ)
{
    החזר SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, صحيح x, صحيح y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    אם (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        החזר true;
    }

    החזר SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, فراغ *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (!_this->SetWindowHitTest) {
        החזר SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    החזר _this->SetWindowHitTest(window, callback != عدم);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    אם (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        החזר SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    אם (!props) {
        החזר false;
    }

    אם (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        אם (!surface) {
            החזר false;
        }
    } אחרת {
        surface = عدم;
    }

    אם (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        החזר false;
    }

    אם (_this->UpdateWindowShape) {
        אם (!_this->UpdateWindowShape(_this, window, surface)) {
            החזר false;
        }
    }
    החזר true;
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
    אם (_this) {
        SDL_Window *window;
        עבור (window = _this->windows; window; window = window->next) {
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

    אם (_this) {
        SDL_Window *window;
        עבור (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ثابت حرف *path)
{
    bool result;

    אם (!_this) {
        החזר SDL_UninitializedVideo();
    }
    אם (_this->vulkan_config.loader_loaded) {
        אם (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            החזר SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } אחרת {
        אם (!_this->Vulkan_LoadLibrary) {
            החזר SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    אם (result) {
        _this->vulkan_config.loader_loaded++;
    }
    החזר result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(فراغ)
{
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר عدم;
    }
    אם (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        החזר عدم;
    }
    החזר (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

فراغ SDL_Vulkan_UnloadLibrary(فراغ)
{
    אם (!_this) {
        SDL_UninitializedVideo();
        החזר;
    }
    אם (_this->vulkan_config.loader_loaded > 0) {
        אם (--_this->vulkan_config.loader_loaded > 0) {
            החזר;
        }
        אם (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *count)
{
    Uint32 tmpcount = 0;
    אם (!count) {
        count = &tmpcount;
    }

    אם (!_this->Vulkan_GetInstanceExtensions) {
        *count = 0;
        SDL_Unsupported();
        החזר عدم;
    }

    החזר _this->Vulkan_GetInstanceExtensions(_this, count);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ثابت بنية VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    אם (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        החזר false;
    }

    CHECK_PARAM(!instance) {
        החזר SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        החזר SDL_InvalidParamError("surface");
    }

    אם (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        אם (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        אם (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        אם (SDL_Vulkan_LoadLibrary(عدم)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } אחרת {
            החזר SDL_SetError("failed to load Vulkan library");
        }
    }

    החזר _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

فراغ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية VkAllocationCallbacks *allocator)
{
    אם (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        החזר false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        החזר false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        החזר false;
    }

    אם (_this->Vulkan_GetPresentationSupport) {
        החזר _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    החזר true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, عدم);

    אם (!_this->Metal_CreateView) {
        SDL_Unsupported();
        החזר عدم;
    }

    אם (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        אם (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        אם (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    החזר _this->Metal_CreateView(_this, window);
}

فراغ SDL_Metal_DestroyView(SDL_MetalView view)
{
    אם (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

فراغ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    אם (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            החזר عدم;
        }
        החזר _this->Metal_GetLayer(_this, view);
    } אחרת {
        SDL_SetError("Metal is not supported.");
        החזר عدم;
    }
}

#אם defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ثابت حرف *SDL_GetCSSCursorName(SDL_SystemCursor id, ثابت حرف **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    بدل (id) {
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
        החזר "default";

    حالة SDL_SYSTEM_CURSOR_TEXT:
        החזר "text";

    حالة SDL_SYSTEM_CURSOR_WAIT:
        החזר "wait";

    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
        החזר "crosshair";

    حالة SDL_SYSTEM_CURSOR_PROGRESS:
        החזר "progress";

    حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        אם (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        החזר "nwse-resize";

    حالة SDL_SYSTEM_CURSOR_NESW_RESIZE:
        אם (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        החזר "nesw-resize";

    حالة SDL_SYSTEM_CURSOR_EW_RESIZE:
        אם (fallback_name) {
            *fallback_name = "col-resize";
        }
        החזר "ew-resize";

    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
        אם (fallback_name) {
            *fallback_name = "row-resize";
        }
        החזר "ns-resize";

    حالة SDL_SYSTEM_CURSOR_MOVE:
        אם (fallback_name) {
            *fallback_name = "all-scroll";
        }
        החזר "move";

    حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        החזר "not-allowed";

    حالة SDL_SYSTEM_CURSOR_POINTER:
        החזר "pointer";

    حالة SDL_SYSTEM_CURSOR_NW_RESIZE:
        החזר "nw-resize";

    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
        החזר "n-resize";

    حالة SDL_SYSTEM_CURSOR_NE_RESIZE:
        החזר "ne-resize";

    حالة SDL_SYSTEM_CURSOR_E_RESIZE:
        החזר "e-resize";

    حالة SDL_SYSTEM_CURSOR_SE_RESIZE:
        החזר "se-resize";

    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
        החזר "s-resize";

    حالة SDL_SYSTEM_CURSOR_SW_RESIZE:
        החזר "sw-resize";

    حالة SDL_SYSTEM_CURSOR_W_RESIZE:
        החזר "w-resize";

    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        החזר "context-menu";

    حالة SDL_SYSTEM_CURSOR_HELP:
        החזר "help";

    حالة SDL_SYSTEM_CURSOR_CELL:
        החזר "cell";

    حالة SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        החזר "vertical-text";

    حالة SDL_SYSTEM_CURSOR_ALIAS:
        החזר "alias";

    حالة SDL_SYSTEM_CURSOR_COPY:
        החזר "copy";

    حالة SDL_SYSTEM_CURSOR_NO_DROP:
        החזר "no-drop";

    حالة SDL_SYSTEM_CURSOR_GRAB:
        החזר "grab";

    حالة SDL_SYSTEM_CURSOR_GRABBING:
        החזר "grabbing";

    حالة SDL_SYSTEM_CURSOR_COL_RESIZE:
        החזר "col-resize";

    حالة SDL_SYSTEM_CURSOR_ROW_RESIZE:
        החזר "row-resize";

    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        אם (fallback_name) {
            *fallback_name = "move";
        }
        החזר "all-scroll";

    حالة SDL_SYSTEM_CURSOR_ZOOM_IN:
        החזר "zoom-in";

    حالة SDL_SYSTEM_CURSOR_ZOOM_OUT:
        החזר "zoom-out";

    افتراضي:
        החזר "default";
    }
}
#endif

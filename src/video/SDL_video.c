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

#شامل "SDL_internal.h"

// The high-level video driver subsystem

#شامل "SDL_sysvideo.h"
#شامل "SDL_clipboard_c.h"
#شامل "SDL_egl_c.h"
#شامل "SDL_surface_c.h"
#شامل "SDL_pixels_c.h"
#شامل "SDL_rect_c.h"
#شامل "SDL_video_c.h"
#شامل "../events/SDL_events_c.h"
#شامل "../SDL_hints_c.h"
#شامل "../SDL_properties_c.h"
#شامل "../timer/SDL_timer_c.h"
#شامل "../camera/SDL_camera_c.h"
#شامل "../render/SDL_sysrender.h"
#شامل "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#شامل <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#اگر defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#شامل <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#اگر defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#شامل <SDL3/SDL_opengles2.h>
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
#شامل <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#شامل <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ایستا VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_درون_داد_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    پوچ
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        بازگشت result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        بازگشت result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        بازگشت result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        بازگشت result;                                                  \
    }

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
بیرونی bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
بیرونی bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
بیرونی bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
بیرونی bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
بیرونی تهی SDL_UpdateLifecycleObserver(تهی);
#endif

ایستا تهی SDL_CheckWindowDisplayChanged(SDL_Window *window);
ایستا تهی SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
ایستا تهی SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
ایستا bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    اگر (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        بازگشت true;
    }
    بازگشت false;
}

ایستا bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    بازگشت !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ایستا bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    بازگشت !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ایستا bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    بازگشت !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ایستا bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    بازگشت !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ایستا bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    بازگشت !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ایستا bool syncHint;

ایستا تهی SDL_SyncHintWatcher(تهی *userdata, ثابت نویسه *name, ثابت نویسه *old_مقدار, ثابت نویسه *new_مقدار)
{
    syncHint = SDL_GetStringBoolean(new_مقدار, false);
}

ایستا تهی SDL_SyncIfRequired(SDL_Window *window)
{
    اگر (syncHint) {
        SDL_SyncWindow(window);
    }
}

ایستا تهی SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    اگر (window->parent) {
        اگر (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        اگر (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } وگرنه {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = پوچ;
    }

    اگر (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        اگر (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

تعریفنوع ساختار
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    تهی *pixels;
    صحیح pitch;
    صحیح bytes_per_pixel;
} SDL_WindowTextureData;

ایستا Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#اگر (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    اگر (_this->GL_CreateContext) {
        بازگشت SDL_WINDOW_OPENGL;
    }
#endif
#اگر defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    اگر (_this->Metal_CreateView) {
        بازگشت SDL_WINDOW_METAL;
    }
#endif
#اگر defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    اگر (SDL_strcmp(_this->name, "openvr") == 0) {
        بازگشت SDL_WINDOW_OPENGL;
    }
#endif
    بازگشت 0;
}

ایستا bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, تهی **pixels, صحیح *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, پوچ);
    ثابت bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    صحیح i;
    صحیح w, h;
    ثابت SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    اگر (!data) {
        SDL_Renderer *renderer = پوچ;
        ثابت نویسه *render_driver = پوچ;

        // See if there's a render driver being requested
        ثابت نویسه *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        اگر (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        اگر (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        اگر (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = پوچ;
        }

        نویسه *render_driver_copy = پوچ;
        اگر (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            اگر (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                نویسه *prev = render_driver_copy;
                نویسه *ptr = prev;
                وقتی ((ptr = SDL_strchr(ptr, ',')) != پوچ) {
                    *ptr = '\0';
                    ثابت bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    اگر (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } وگرنه {
                        ptr++;
                        prev = ptr;
                    }
                }

                اگر (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        اگر (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            اگر (!renderer) {
                // The error for this specific renderer has already been set
                بازگشت false;
            }
        } وگرنه {
            SDL_assert(render_driver_copy == پوچ);
            ثابت صحیح total = SDL_Get_رقم_Render_Drivers();
            برای (i = 0; i < total; ++i) {
                ثابت نویسه *name = SDL_GetRenderDriver(i);
                اگر (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    اگر (renderer) {
                        بشکن; // this will work.
                    }
                }
            }
            اگر (!renderer) {
                بازگشت SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != پوچ); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, اندازه(*data));
        اگر (!data) {
            SDL_DestroyRenderer(renderer);
            بازگشت false;
        }
        اگر (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            بازگشت false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, پوچ);
    اگر (!texture_formats) {
        بازگشت false;
    }

    // Free any old texture and pixel data
    اگر (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = پوچ;
    }
    SDL_free(data->pixels);
    data->pixels = پوچ;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    برای (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        اگر (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            بشکن;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    اگر (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        بازگشت false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        اگر (!data->pixels) {
            بازگشت false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, پوچ);

    بازگشت true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحیح vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, پوچ);
    اگر (!data) {
        بازگشت false;
    }
    اگر (!data->renderer) {
        بازگشت false;
    }
    بازگشت SDL_SetRenderVSync(data->renderer, vsync);
}

ایستا bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, صحیح *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, پوچ);
    اگر (!data) {
        بازگشت false;
    }
    اگر (!data->renderer) {
        بازگشت false;
    }
    بازگشت SDL_GetRenderVSync(data->renderer, vsync);
}

ایستا bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects, صحیح numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    تهی *src;
    صحیح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, پوچ);
    اگر (!data || !data->texture) {
        بازگشت SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    اگر (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (تهی *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        اگر (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            بازگشت false;
        }

        اگر (!SDL_RenderTexture(data->renderer, data->texture, پوچ, پوچ)) {
            بازگشت false;
        }

        SDL_RenderPresent(data->renderer);
    }
    بازگشت true;
}

ایستا تهی SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    اگر (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, پوچ);

        اگر (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        اگر (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

ایستا SDL_VideoDevice *_this = پوچ;
ایستا SDL_AtomicInt SDL_messagebox_شمار;

ایستا صحیح SDLCALL cmpmodes(ثابت تهی *A, ثابت تهی *B)
{
    ثابت SDL_DisplayMode *a = (ثابت SDL_DisplayMode *)A;
    ثابت SDL_DisplayMode *b = (ثابت SDL_DisplayMode *)B;
    صحیح a_refresh_rate = (صحیح)(a->refresh_rate * 100);
    صحیح b_refresh_rate = (صحیح)(b->refresh_rate * 100);
    صحیح a_pixel_density = (صحیح)(a->pixel_density * 100);
    صحیح b_pixel_density = (صحیح)(b->pixel_density * 100);

    اگر (a->w != b->w) {
        بازگشت b->w - a->w;
    } وگرنه اگر (a->h != b->h) {
        بازگشت b->h - a->h;
    } وگرنه اگر (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        بازگشت SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } وگرنه اگر (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        بازگشت SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } وگرنه اگر (a_refresh_rate != b_refresh_rate) {
        بازگشت b_refresh_rate - a_refresh_rate;
    } وگرنه اگر (a_pixel_density != b_pixel_density) {
        بازگشت a_pixel_density - b_pixel_density;
    }
    بازگشت 0;
}

bool SDL_UninitializedVideo(تهی)
{
    بازگشت SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ایستا ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحیح SDL_Get_رقم_Video_Drivers(تهی)
{
    ایستا صحیح رقم_drivers = -1;

    اگر (رقم_drivers >= 0) {
        بازگشت رقم_drivers;
    }

    رقم_drivers = 0;

    // Build a list of unique video drivers.
    برای (صحیح i = 0; bootstrap[i] != پوچ; ++i) {
        bool duplicate = false;
        برای (صحیح j = 0; j < i; ++j) {
            اگر (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                بشکن;
            }
        }

        اگر (!duplicate) {
            deduped_bootstrap[رقم_drivers++] = bootstrap[i];
        }
    }

    بازگشت رقم_drivers;
}

ثابت نویسه *SDL_GetVideoDriver(صحیح index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_رقم_Video_Drivers()) {
        SDL_InvalidParamError("index");
        بازگشت پوچ;
    }
    بازگشت deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ثابت نویسه *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    صحیح i = 0;

    // Check to make sure we don't overwrite '_this'
    اگر (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    اگر (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        برو pre_driver_error;
    }
    init_events = true;
    اگر (!SDL_InitKeyboard()) {
        برو pre_driver_error;
    }
    init_keyboard = true;
    اگر (!SDL_PreInitMouse()) {
        برو pre_driver_error;
    }
    init_mouse = true;
    اگر (!SDL_InitTouch()) {
        برو pre_driver_error;
    }
    init_touch = true;
    اگر (!SDL_InitPen()) {
        برو pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = پوچ;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    اگر (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    اگر (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    اگر (driver_name && *driver_name != 0) {
        ثابت نویسه *driver_attempt = driver_name;
        وقتی (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت نویسه *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            برای (i = 0; bootstrap[i]; ++i) {
                اگر (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    اگر (video) {
                        بشکن;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : پوچ;
        }
    } وگرنه {
        برای (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            اگر (video) {
                بشکن;
            }
        }
    }
    اگر (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } وگرنه {
        اگر (driver_name) {
            SDL_SetError("%s not available", driver_name);
            برو pre_driver_error;
        }
        SDL_SetError("No available video device");
        برو pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = پوچ;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    اگر (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        بازگشت false;
    }

    // Make sure some displays were added
    اگر (_this->رقم_displays == 0) {
        SDL_QuitVideo();
        بازگشت SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, پوچ);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    اگر (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    بازگشت true;

pre_driver_error:
    SDL_assert(_this == پوچ);
    اگر (init_pen) {
        SDL_QuitPen();
    }
    اگر (init_touch) {
        SDL_QuitTouch();
    }
    اگر (init_mouse) {
        SDL_QuitMouse();
    }
    اگر (init_keyboard) {
        SDL_QuitKeyboard();
    }
    اگر (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    بازگشت false;
}

ثابت نویسه *SDL_GetCurrentVideoDriver(تهی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    بازگشت _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(تهی)
{
    بازگشت _this;
}

bool SDL_OnVideoThread(تهی)
{
    بازگشت (_this && SDL_GetCurrentThreadID() == _this->thread);
}

تهی SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    اگر (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(تهی)
{
    اگر (_this) {
        بازگشت _this->system_theme;
    } وگرنه {
        بازگشت SDL_SYSTEM_THEME_UNKNOWN;
    }
}

تهی SDL_UpdateDesktopBounds(تهی)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(پوچ);
    اگر (displays) {
        برای (صحیح i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            اگر (SDL_GetDisplayBounds(displays[i], &bounds)) {
                اگر (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } وگرنه {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ایستا تهی SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    اگر (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    اگر (mode->refresh_rate_numerator > 0) {
        اگر (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (اعشاری)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } وگرنه {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ثابت SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    اگر (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, اندازه(display.desktop_mode));
    }
    بازگشت SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحیح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(اندازه(*new_display));
    اگر (!new_display) {
        بازگشت 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->رقم_displays + 1) * اندازه(*displays));
    اگر (!displays) {
        SDL_free(new_display);
        بازگشت 0;
    }
    _this->displays = displays;
    _this->displays[_this->رقم_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    اگر (display->name) {
        new_display->name = SDL_strdup(display->name);
    } وگرنه {
        نویسه name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    اگر (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    برای (i = 0; i < new_display->رقم_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    اگر (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    بازگشت id;
}

تهی SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    برای (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

تهی SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

تهی SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    صحیح display_index = SDL_GetDisplayIndex(displayID);
    اگر (display_index < 0) {
        بازگشت;
    }

    display = _this->displays[display_index];

    اگر (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = پوچ;
    SDL_free(display->internal);
    display->internal = پوچ;
    SDL_free(display);

    اگر (display_index < (_this->رقم_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->رقم_displays - display_index - 1) * اندازه(_this->displays[display_index]));
    }
    --_this->رقم_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحیح *شمار)
{
    صحیح i;
    SDL_DisplayID *displays;

    اگر (!_this) {
        اگر (شمار) {
            *شمار = 0;
        }

        SDL_UninitializedVideo();
        بازگشت پوچ;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->رقم_displays + 1) * اندازه(*displays));
    اگر (displays) {
        اگر (شمار) {
            *شمار = _this->رقم_displays;
        }

        برای (i = 0; i < _this->رقم_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } وگرنه {
        اگر (شمار) {
            *شمار = 0;
        }
    }
    بازگشت displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحیح display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    اگر (display_index < 0) {
        بازگشت پوچ;
    }
    بازگشت _this->displays[display_index];
}

ایستا SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    اگر (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    بازگشت displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    بازگشت SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(تهی)
{
    اگر (!_this || _this->رقم_displays == 0) {
        SDL_UninitializedVideo();
        بازگشت 0;
    }
    بازگشت _this->displays[0]->id;
}

صحیح SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    صحیح display_index;

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت -1;
    }

    برای (display_index = 0; display_index < _this->رقم_displays; ++display_index) {
        اگر (displayID == _this->displays[display_index]->id) {
            بازگشت display_index;
        }
    }
    SDL_SetError("Invalid display");
    بازگشت -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, پوچ);

    بازگشت display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    بازگشت SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    اگر (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    بازگشت display->props;
}

ثابت نویسه *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, پوچ);

    بازگشت display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        بازگشت SDL_InvalidParamError("rect");
    }

    اگر (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        اگر (_this->GetDisplayBounds(_this, display, rect)) {
            بازگشت true;
        }
    }

    // Assume that the displays are left to right
    اگر (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } وگرنه {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    بازگشت true;
}

ایستا صحیح ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ثابت نویسه *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    بازگشت hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        بازگشت SDL_InvalidParamError("rect");
    }

    اگر (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        بازگشت true;
    }

    اگر (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        اگر (_this->GetDisplayUsableBounds(_this, display, rect)) {
            بازگشت true;
        }
    }

    // Oh well, just give the entire display bounds.
    بازگشت SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    اگر (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        بازگشت display->natural_orientation;
    } وگرنه {
        // Default to landscape if the driver hasn't set it
        بازگشت SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    اگر (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        بازگشت display->current_orientation;
    } وگرنه {
        // Default to landscape if the driver hasn't set it
        بازگشت SDL_ORIENTATION_LANDSCAPE;
    }
}

تهی SDL_SetDisplayContentScale(SDL_VideoDisplay *display, اعشاری scale)
{
    اگر (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        برای (window = _this->windows; window; window = window->next) {
            اگر (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

اعشاری SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    بازگشت display->content_scale;
}

تهی SDL_SetWindowHDRProperties(SDL_Window *window, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    اگر (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        اگر (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

تهی SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ثابت bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	اگر (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    اگر (changed && !SDL_DriverSendsHDRChanges(_this)) {
        برای (SDL_Window *w = display->device->windows; w; w = w->next) {
            اگر (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ایستا تهی SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    اگر (display->رقم_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ایستا ثابت SDL_DisplayMode *SDL_GetFullscreenModeMatch(ثابت SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    اگر (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        بازگشت پوچ;
    }

    SDL_memcpy(&fullscreen_mode, mode, اندازه(fullscreen_mode));
    اگر (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = پوچ;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    اگر (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        اگر (!mode) {
            برای (صحیح i = 0; i < display->رقم_fullscreen_modes; ++i) {
                اگر (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], اندازه(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    بشکن;
                }
            }
        }

        // Search for a mode with the same characteristics
        اگر (!mode) {
            برای (صحیح i = 0; i < display->رقم_fullscreen_modes; ++i) {
                اگر (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    بشکن;
                }
            }
        }
    }
    بازگشت mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    صحیح i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, اندازه(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->رقم_fullscreen_modes;
    برای (i = 0; i < nmodes; ++i) {
        اگر (cmpmodes(&new_mode, &modes[i]) == 0) {
            بازگشت false;
        }
    }

    // Go ahead and add the new mode
    اگر (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * اندازه(*modes));
        اگر (!modes) {
            بازگشت false;
        }

        اگر (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * اندازه(*modes));
            برای (i = 0; i < nmodes; ++i) {
                اگر (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->رقم_fullscreen_modes++], &new_mode, اندازه(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->رقم_fullscreen_modes,
              اندازه(SDL_DisplayMode), cmpmodes);

    بازگشت true;
}

تهی SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحیح i;

    برای (i = display->رقم_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = پوچ;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = پوچ;
    display->رقم_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحیح *شمار)
{
    صحیح i;
    صحیح رقم_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    اگر (شمار) {
        *شمار = 0;
    }

    CHECK_DISPLAY_MAGIC(display, پوچ);

    SDL_UpdateFullscreenDisplayModes(display);

    رقم_modes = display->رقم_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((رقم_modes + 1) * اندازه(*result) + رقم_modes * اندازه(**result));
    اگر (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((رقم_modes + 1) * اندازه(*result)));
        اگر (رقم_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, رقم_modes * اندازه(*modes));
        }
        برای (i = 0; i < رقم_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = پوچ;

        اگر (شمار) {
            *شمار = رقم_modes;
        }
    } وگرنه {
        اگر (شمار) {
            *شمار = 0;
        }
    }
    بازگشت result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, صحیح w, صحیح h, اعشاری refresh_rate, bool include_بالا_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        بازگشت SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_DisplayMode *mode, *closest = پوچ;
    اعشاری aspect_ratio;
    صحیح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    اگر (h > 0) {
        aspect_ratio = (اعشاری)w / h;
    } وگرنه {
        aspect_ratio = 1.0f;
    }

    اگر (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    برای (i = 0; i < display->رقم_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        اگر (w > mode->w) {
            // Out of sorted modes large enough here
            بشکن;
        }
        اگر (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            ادامه;
        }
        اگر (mode->pixel_density > 1.0f && !include_بالا_density_modes) {
            ادامه;
        }
        اگر (closest) {
            اعشاری current_aspect_ratio = (اعشاری)mode->w / mode->h;
            اعشاری closest_aspect_ratio = (اعشاری)closest->w / closest->h;
            اگر (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                ادامه;
            }

            اگر (mode->w == closest->w && mode->h == closest->h) {
                اگر (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    ادامه;
                }
                اگر (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    ادامه;
                }
            }
        }

        closest = mode;
    }
    اگر (!closest) {
        بازگشت SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    بازگشت true;
}

ایستا bool DisplayModeChanged(ثابت SDL_DisplayMode *old_mode, ثابت SDL_DisplayMode *new_mode)
{
    بازگشت ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

تهی SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    اگر (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        بازگشت;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    اگر (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        اگر (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ثابت SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, پوچ);

    بازگشت &display->desktop_mode;
}

تهی SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ثابت SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    اگر (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } وگرنه {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    اگر (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ثابت SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, پوچ);

    بازگشت display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    اگر (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        بازگشت true;
    }

    اگر (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    اگر (mode == display->current_mode) {
        بازگشت true;
    }
#endif

    // Actually change the display mode
    اگر (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        اگر (!result) {
            بازگشت false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    بازگشت true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ایستا تهی SDL_GetClosestPointOnRect(ثابت SDL_Rect *rect, SDL_Point *point)
{
    ثابت صحیح راست = rect->x + rect->w - 1;
    ثابت صحیح bottom = rect->y + rect->h - 1;

    اگر (point->x < rect->x) {
        point->x = rect->x;
    } وگرنه اگر (point->x > راست) {
        point->x = راست;
    }

    اگر (point->y < rect->y) {
        point->y = rect->y;
    } وگرنه اگر (point->y > bottom) {
        point->y = bottom;
    }
}

ایستا SDL_DisplayID GetDisplayForRect(صحیح x, صحیح y, صحیح w, صحیح h)
{
    صحیح i, dist;
    SDL_DisplayID closest = 0;
    صحیح closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    اگر (_this) {
        برای (i = 0; i < _this->رقم_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            اگر (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, پوچ)) {
                بازگشت display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            اگر (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    اگر (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    بازگشت closest;
}

تهی SDL_RelativeToGlobalForWindow(SDL_Window *window, صحیح rel_x, صحیح rel_y, صحیح *abs_x, صحیح *abs_y)
{
    SDL_Window *w;

    اگر (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        برای (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            اگر (!SDL_WINDOW_IS_POPUP(w)) {
                بشکن;
            }
        }
    }

    اگر (abs_x) {
        *abs_x = rel_x;
    }
    اگر (abs_y) {
        *abs_y = rel_y;
    }
}

تهی SDL_GlobalToRelativeForWindow(SDL_Window *window, صحیح abs_x, صحیح abs_y, صحیح *rel_x, صحیح *rel_y)
{
    SDL_Window *w;

    اگر (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        برای (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            اگر (!SDL_WINDOW_IS_POPUP(w)) {
                بشکن;
            }
        }
    }

    اگر (rel_x) {
        *rel_x = abs_x;
    }
    اگر (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ثابت SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        بازگشت 0;
    }

    بازگشت GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ثابت SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        بازگشت 0;
    }

    بازگشت GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ایستا SDL_DisplayID GetDisplayAtOrigin(صحیح x, صحیح y)
{
    برای (صحیح i = 0; i < _this->رقم_displays; ++i) {
        SDL_Rect rect;
        ثابت SDL_DisplayID cur_id = _this->displays[i]->id;
        اگر (SDL_GetDisplayBounds(cur_id, &rect)) {
            اگر (x == rect.x && y == rect.y) {
                بازگشت cur_id;
            }
        }
    }

    بازگشت 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    صحیح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    اگر (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    اگر (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } وگرنه {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    اگر (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    بازگشت displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, پوچ);

    // An explicit fullscreen display overrides all
    اگر (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    اگر (!displayID) {
        displayID = window->pending_displayID;
    }
    اگر (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحیح x = window->last_position_pending ? window->pending.x : window->x;
        ثابت صحیح y = window->last_position_pending ? window->pending.y : window->y;
        ثابت صحیح w = window->last_size_pending ? window->pending.w : window->w;
        ثابت صحیح h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        اگر (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    اگر (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    بازگشت SDL_GetVideoDisplay(displayID);
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
    اگر (fs_display) {
        SDL_Set_عدد_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } وگرنه {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    بازگشت GetDisplayForWindow(window);
}

ایستا تهی SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    اگر (SDL_SendsDisplayChanges(_this)) {
        بازگشت;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    اگر (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        اگر (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            اگر (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                صحیح old_area = old_overlap.w * old_overlap.h;
                صحیح new_area = new_overlap.w * new_overlap.h;
                اعشاری new_overlap_ratio = (new_area / ((اعشاری)old_area + new_area));
                اگر (new_overlap_ratio < 0.80) {
                    بازگشت;
                }
            }
        }
    }

    اگر (displayID != window->displayID) {
        صحیح i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        برای (i = 0; i < _this->رقم_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            اگر (display->fullscreen_window == window) {
                اگر (display_index != i) {
                    اگر (display_index < 0) {
                        display_index = i;
                    } وگرنه {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        اگر (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = پوچ;
                    }
                }
                بشکن;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (صحیح)displayID, 0);
    }
}

اعشاری SDL_GetWindowPixelDensity(SDL_Window *window)
{
    صحیح window_w, window_h, pixel_w, pixel_h;
    اعشاری pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    اگر (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (اعشاری)pixel_w / window_w;
    }
    بازگشت pixel_density;
}

اعشاری SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    بازگشت window->display_scale;
}

ایستا تهی SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    اعشاری display_scale;

    اگر (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } وگرنه {
        ثابت اعشاری pixel_density = SDL_GetWindowPixelDensity(window);
        ثابت اعشاری content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    اگر (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = پوچ;
    SDL_DisplayMode *mode = پوچ;
    صحیح i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    اگر (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    اگر (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        اگر (!display) {
            // This should never happen, but it did...
            برو done;
        }
    } وگرنه {
        برای (i = 0; i < _this->رقم_displays; ++i) {
            display = _this->displays[i];
            اگر (display->fullscreen_window == window) {
                بشکن;
            }
        }
        اگر (!display || i == _this->رقم_displays) {
            // Already not fullscreen on any display
            display = پوچ;
        }
    }

    اگر (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        اگر (mode) {
            window->fullscreen_exclusive = true;
        } وگرنه {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    اگر (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        اگر (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            اگر (display) {
                display->fullscreen_window = پوچ;
            }
            برو done;
        }
        اگر (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            اگر (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                اگر (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    برو error;
                }
            } وگرنه اگر (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                برای (i = 0; i < _this->رقم_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    اگر (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, پوچ);
                        اگر (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = پوچ;
                    }
                }
            }

            اگر (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                برو done;
            }
        }
    }
#endif

    اگر (display) {
        // Restore the video mode on other displays if needed
        برای (i = 0; i < _this->رقم_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            اگر (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, پوچ);
                other->fullscreen_window = پوچ;
            }
        }
    }

    اگر (fullscreen) {
        صحیح mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        اگر (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        اگر (!SDL_SetDisplayModeForDisplay(display, mode)) {
            برو error;
        }
        اگر (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            اگر (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } وگرنه {
                resized = true;
            }

            اگر (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                اگر (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } وگرنه اگر (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                برو error;
            }
        }

        اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            اگر (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                اگر (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } وگرنه {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                اگر (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                اگر (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } وگرنه {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } وگرنه {
        bool resized = false;

        // Restore the desktop mode
        اگر (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, پوچ);
        }
        اگر (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            اگر (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                اگر (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } وگرنه {
                resized = true;
            }

            اگر (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } وگرنه اگر (ret == SDL_FULLSCREEN_FAILED) {
                برو error;
            }
        }

        اگر (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            اگر (display) {
                display->fullscreen_window = پوچ;
            }

            اگر (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                اگر (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } وگرنه {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    بازگشت true;

error:
    اگر (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    بازگشت false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ثابت SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (mode) {
        اگر (!SDL_GetFullscreenModeMatch(mode)) {
            بازگشت SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } وگرنه {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    اگر (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    اگر (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    بازگشت true;
}

ثابت SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, پوچ);
    CHECK_WINDOW_NOT_POPUP(window, پوچ);

    اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
        بازگشت SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } وگرنه {
        بازگشت SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

تهی *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    اگر (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        بازگشت پوچ;
    }
    بازگشت _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ثابت SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    اگر (mode) {
        بازگشت mode->format;
    } وگرنه {
        بازگشت SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_بالا_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_بالاترین | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

ایستا SDL_INLINE bool IsAcceptingDragAndDrop(تهی)
{
    اگر (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        بازگشت true;
    }
    بازگشت false;
}

// prepare a newly-created window
ایستا SDL_INLINE تهی PrepareDragAndDropSupport(SDL_Window *window)
{
    اگر (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
تهی SDL_ToggleDragAndDropSupport(تهی)
{
    اگر (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        برای (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(صحیح *شمار)
{
    اگر (شمار) {
        *شمار = 0;
    }

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }

    SDL_Window *window;
    صحیح رقم_added = 0;
    صحیح رقم_windows = 0;
    برای (window = _this->windows; window; window = window->next) {
        ++رقم_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((رقم_windows + 1) * اندازه(*windows));
    اگر (!windows) {
        بازگشت پوچ;
    }

    برای (window = _this->windows; window; window = window->next) {
        windows[رقم_added++] = window;
        اگر (رقم_added == رقم_windows) {
            // Race condition? Multi-threading not supported, ignore it
            بشکن;
        }
    }
    windows[رقم_added] = پوچ;

    اگر (شمار) {
        *شمار = رقم_added;
    }
    بازگشت windows;
}

ایستا تهی ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    اگر (!SDL_WINDOW_IS_POPUP(window)) {
        اگر (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        اگر (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        اگر (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        اگر (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        اگر (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        اگر (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

ایستا تهی SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    اگر (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } وگرنه {
        ApplyWindowFlags(window, flags);
        اگر (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#اگر defined(SDL_PLATFORM_LINUX)
    اگر (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_مقدار(window, 0.0f);
    }
#endif
}

ایستا bool SDL_ContextNotSupported(ثابت نویسه *name)
{
    بازگشت SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ایستا bool SDL_DllNotSupported(ثابت نویسه *name)
{
    بازگشت SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ایستا ساختار {
    ثابت نویسه *property_name;
    SDL_WindowFlags flag;
    bool invert_مقدار;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_بالاترین_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_بالاترین,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_بالا_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_بالا_PIXEL_DENSITY,  false },
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

ایستا SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_عدد_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_عدد, 0);

    برای (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        اگر (SDL_WindowFlagProperties[i].invert_مقدار) {
            اگر (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } وگرنه {
            اگر (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    بازگشت flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ثابت نویسه *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, پوچ);
    صحیح x = (صحیح)SDL_Get_عدد_Property(props, SDL_PROP_WINDOW_CREATE_X_عدد, SDL_WINDOWPOS_UNDEFINED);
    صحیح y = (صحیح)SDL_Get_عدد_Property(props, SDL_PROP_WINDOW_CREATE_Y_عدد, SDL_WINDOWPOS_UNDEFINED);
    صحیح w = (صحیح)SDL_Get_عدد_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_عدد, 0);
    صحیح h = (صحیح)SDL_Get_عدد_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_عدد, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, پوچ);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    اگر (!_this) {
        // Initialize the video system if needed
        اگر (!SDL_Init(SDL_INIT_VIDEO)) {
            بازگشت پوچ;
        }

        // Make clang-tidy happy
        اگر (!_this) {
            بازگشت پوچ;
        }
    }

    اگر ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        بازگشت پوچ;
    }

    اگر ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        اگر (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            بازگشت پوچ;
        }

        // Tooltip and popup menu window must specify a parent window
        اگر (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            بازگشت پوچ;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    اگر (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned صحیح)type_flags);
        بازگشت پوچ;
    }

    // Make sure the display list is up to date for window placement
    اگر (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    اگر (w < 1) {
        w = 1;
    }
    اگر (h < 1) {
        h = 1;
    }

    اگر (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        اگر ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وگرنه اگر ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        اگر (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        اگر (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            اگر (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            اگر (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    اگر (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned صحیح)graphics_flags);
        بازگشت پوچ;
    }

    // Some platforms have certain graphics backends enabled by default
    اگر (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    اگر (flags & SDL_WINDOW_OPENGL) {
        اگر (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            بازگشت پوچ;
        }
        اگر (!SDL_GL_LoadLibrary(پوچ)) {
            بازگشت پوچ;
        }
    }

    اگر (flags & SDL_WINDOW_VULKAN) {
        اگر (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            بازگشت پوچ;
        }
        اگر (!SDL_Vulkan_LoadLibrary(پوچ)) {
            بازگشت پوچ;
        }
    }

    اگر (flags & SDL_WINDOW_METAL) {
        اگر (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            بازگشت پوچ;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, اندازه(*window));
    اگر (!window) {
        بازگشت پوچ;
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
    اگر (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    اگر (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    اگر (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    اگر (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    اگر (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_افزودن_Error();
        SDL_DestroyWindow(window);
        SDL_برداشت_Error();
        بازگشت پوچ;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#اگر !defined(SDL_PLATFORM_WINDOWS)
    اگر (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    اگر (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    بازگشت window;
}

SDL_Window *SDL_CreateWindow(ثابت نویسه *title, صحیح w, صحیح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    اگر (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_عدد, w);
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_عدد, h);
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_عدد, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    بازگشت window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, صحیح offset_x, صحیح offset_y, صحیح w, صحیح h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    اگر (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        بازگشت پوچ;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_X_عدد, offset_x);
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_Y_عدد, offset_y);
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_عدد, w);
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_عدد, h);
    SDL_Set_عدد_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_عدد, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    بازگشت window;
}

ایستا bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    اگر (!_this->ReconfigureWindow) {
        بازگشت false;
    }

    ثابت SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    اگر (graphics_flags & (graphics_flags - 1)) {
        بازگشت SDL_SetError("Conflicting window flags specified");
    }

    اگر ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        بازگشت SDL_ContextNotSupported("OpenGL");
    }
    اگر ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        بازگشت SDL_ContextNotSupported("Vulkan");
    }
    اگر ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        بازگشت SDL_ContextNotSupported("Metal");
    }

    اگر (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        اگر (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            بازگشت false;
        }
    } وگرنه {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        اگر (!_this->ReconfigureWindow(_this, window, 0)) {
            بازگشت false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        اگر (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        اگر (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    اگر (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(پوچ);
        اگر (!loaded_opengl) {
            بازگشت false;
        }
    } وگرنه اگر (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(پوچ);
        اگر (!loaded_vulkan) {
            بازگشت false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    اگر (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        اگر (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        اگر (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        بازگشت false;
    }

    window->flags |= graphics_flags;

    بازگشت true;
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
    اگر (graphics_flags & (graphics_flags - 1)) {
        بازگشت SDL_SetError("Conflicting window flags specified");
    }

    اگر ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        بازگشت SDL_ContextNotSupported("OpenGL");
    }
    اگر ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        بازگشت SDL_ContextNotSupported("Vulkan");
    }
    اگر ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        بازگشت SDL_ContextNotSupported("Metal");
    }

    اگر (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } وگرنه {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    اگر (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    اگر (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ثابت bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    اگر ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        اگر (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } وگرنه {
            need_gl_unload = true;
        }
    } وگرنه اگر (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    اگر ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        اگر (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } وگرنه {
            need_vulkan_unload = true;
        }
    } وگرنه اگر (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    اگر (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    اگر (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    اگر (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    اگر (need_gl_load) {
        اگر (!SDL_GL_LoadLibrary(پوچ)) {
            بازگشت false;
        }
        loaded_opengl = true;
    }

    اگر (need_vulkan_load) {
        اگر (!SDL_Vulkan_LoadLibrary(پوچ)) {
            بازگشت false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    اگر (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        اگر (!_this->CreateSDLWindow(_this, window, 0)) {
            اگر (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            اگر (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            بازگشت false;
        }
    }

    اگر (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    اگر (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    اگر (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    اگر (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    اگر (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    اگر (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    اگر (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    بازگشت true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    اگر (!SDL_ReconfigureWindowInternal(window, flags)) {
        بازگشت SDL_RecreateWindow(window, flags);
    }

    بازگشت true;
}

bool SDL_HasWindows(تهی)
{
    بازگشت _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    بازگشت window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    اگر (id) {
        برای (window = _this->windows; window; window = window->next) {
            اگر (window->id == id) {
                بازگشت window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    بازگشت پوچ;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, پوچ);

    بازگشت window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    اگر (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    بازگشت window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    بازگشت window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ثابت نویسه *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (title == window->title) {
        بازگشت true;
    }
    اگر (!title) {
        title = "";
    }
    اگر (window->title && SDL_strcmp(title, window->title) == 0) {
        بازگشت true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    اگر (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    بازگشت true;
}

ثابت نویسه *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    بازگشت window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        بازگشت SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    اگر (!window->icon) {
        بازگشت false;
    }

    اگر (!_this->SetWindowIcon) {
        بازگشت SDL_Unsupported();
    }

    بازگشت _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, صحیح x, صحیح y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ثابت صحیح w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ثابت صحیح h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    اگر (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    اگر (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    اگر (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        اگر (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وگرنه اگر (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        اگر (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        اگر (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            اگر (!SDL_GetDisplayBounds(displayID, &bounds)) {
                بازگشت false;
            }
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } وگرنه {
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
    اگر (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    اگر (_this->SetWindowPosition) {
        ثابت bool result = _this->SetWindowPosition(_this, window);
        اگر (result) {
            SDL_SyncIfRequired(window);
        }
        بازگشت result;
    }

    بازگشت SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, صحیح *x, صحیح *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#وگرنه
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    اگر (use_display_origin) {
        SDL_DisplayID displayID;

        اگر (x) {
            *x = 0;
        }
        اگر (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        اگر (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            اگر (x) {
                *x = bounds.x;
            }
            اگر (y) {
                *y = bounds.y;
            }
        }
    } وگرنه {
        ثابت bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        اگر (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        اگر (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    بازگشت true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (!_this->SetWindowBordered) {
        بازگشت SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    اگر (want != have) {
        اگر (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } وگرنه {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    بازگشت true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (!_this->SetWindowResizable) {
        بازگشت SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    اگر (want != have) {
        اگر (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } وگرنه {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    بازگشت true;
}

bool SDL_Set_Window_Always_On_بالاترین(SDL_Window *window, bool on_بالاترین)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (!_this->Set_Window_Always_On_بالاترین) {
        بازگشت SDL_Unsupported();
    }

    ثابت bool want = on_بالاترین;
    ثابت bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_بالاترین) != 0);
    اگر (want != have) {
        اگر (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_بالاترین;
        } وگرنه {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_بالاترین;
        }
        _this->Set_Window_Always_On_بالاترین(_this, window, want);
    }

    بازگشت true;
}

bool SDL_SetWindowSize(SDL_Window *window, صحیح w, صحیح h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        بازگشت SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        بازگشت SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    اعشاری new_aspect = w / (اعشاری)h;
    اگر (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (صحیح)SDL_roundf(h * window->max_aspect);
    } وگرنه اگر (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (صحیح)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    اگر (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    اگر (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    اگر (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    اگر (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    اگر (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } وگرنه {
        بازگشت SDL_Unsupported();
    }
    بازگشت true;
}

bool SDL_GetWindowSize(SDL_Window *window, صحیح *w, صحیح *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    اگر (w) {
        *w = window->w;
    }
    اگر (h) {
        *h = window->h;
    }
    بازگشت true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, اعشاری min_aspect, اعشاری max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    اگر (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    صحیح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحیح h = window->last_size_pending ? window->pending.h : window->floating.h;
    بازگشت SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, اعشاری *min_aspect, اعشاری *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    اگر (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    بازگشت true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, صحیح *بالاترین, صحیح *چپ, صحیح *bottom, صحیح *راست)
{
    صحیح dummy = 0;

    اگر (!بالاترین) {
        بالاترین = &dummy;
    }
    اگر (!چپ) {
        چپ = &dummy;
    }
    اگر (!راست) {
        راست = &dummy;
    }
    اگر (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *بالاترین = *چپ = *bottom = *راست = 0;

    CHECK_WINDOW_MAGIC(window, false);

    اگر (!_this->GetWindowBordersSize) {
        بازگشت SDL_Unsupported();
    }

    بازگشت _this->GetWindowBordersSize(_this, window, بالاترین, چپ, bottom, راست);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, صحیح *w, صحیح *h)
{
    صحیح filter;

    CHECK_WINDOW_MAGIC(window, false);

    اگر (!w) {
        w = &filter;
    }

    اگر (!h) {
        h = &filter;
    }

    اگر (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } وگرنه {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ثابت SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        اگر ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } وگرنه {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        اگر (mode) {
            *w = (صحیح)SDL_ceilf(*w * mode->pixel_density);
            *h = (صحیح)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    بازگشت true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, صحیح min_w, صحیح min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        بازگشت SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        بازگشت SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        بازگشت SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    اگر (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    صحیح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحیح h = window->last_size_pending ? window->pending.h : window->floating.h;
    بازگشت SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, صحیح *min_w, صحیح *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    اگر (min_w) {
        *min_w = window->min_w;
    }
    اگر (min_h) {
        *min_h = window->min_h;
    }
    بازگشت true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, صحیح max_w, صحیح max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        بازگشت SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        بازگشت SDL_InvalidParamError("max_h");
    }

    اگر ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        بازگشت SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    اگر (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    صحیح w = window->last_size_pending ? window->pending.w : window->floating.w;
    صحیح h = window->last_size_pending ? window->pending.h : window->floating.h;
    بازگشت SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, صحیح *max_w, صحیح *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    اگر (max_w) {
        *max_w = window->max_w;
    }
    اگر (max_h) {
        *max_h = window->max_h;
    }
    بازگشت true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!(window->flags & SDL_WINDOW_HIDDEN)) {
        بازگشت true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    اگر (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        بازگشت true;
    }

    اگر (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } وگرنه {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    برای (child = window->first_child; child; child = child->next_sibling) {
        اگر (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            بشکن;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    بازگشت true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        بازگشت true;
    }

    // Hide all child windows
    برای (child = window->first_child; child; child = child->next_sibling) {
        اگر (child->flags & SDL_WINDOW_HIDDEN) {
            بشکن;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    اگر (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } وگرنه {
        SDL_SetMouseFocus(پوچ);
        SDL_SetKeyboardFocus(پوچ);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    بازگشت true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        بازگشت true;
    }
    اگر (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    بازگشت true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (!_this->MaximizeWindow) {
        بازگشت SDL_Unsupported();
    }

    اگر (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        بازگشت SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        بازگشت true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    بازگشت true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (!_this->MinimizeWindow) {
        بازگشت SDL_Unsupported();
    }

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        بازگشت true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    بازگشت true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (!_this->RestoreWindow) {
        بازگشت SDL_Unsupported();
    }

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        بازگشت true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    بازگشت true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        اگر (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } وگرنه {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        بازگشت true;
    }

    اگر (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    اگر (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    اگر (result) {
        SDL_SyncIfRequired(window);
    }

    بازگشت result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (_this->SyncWindow) {
        بازگشت _this->SyncWindow(_this, window);
    } وگرنه {
        بازگشت true;
    }
}

ایستا bool ShouldAttemptTextureFramebuffer(تهی)
{
    ثابت نویسه *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    اگر (!_this->CreateWindowFramebuffer) {
        بازگشت true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    اگر (hint && *hint) {
        اگر (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } وگرنه {
            attempt_texture_framebuffer = true;
        }
    } وگرنه {
        اگر (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } وگرنه {
            attempt_texture_framebuffer = false;
        }
    }
    بازگشت attempt_texture_framebuffer;
}

ایستا SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    تهی *pixels = پوچ;
    صحیح pitch = 0;
    bool created_framebuffer = false;
    صحیح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    اگر (!_this->checked_texture_framebuffer) {
        اگر (ShouldAttemptTextureFramebuffer()) {
            اگر (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } وگرنه {
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

    اگر (!created_framebuffer) {
        اگر (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            بازگشت پوچ;
        }

        اگر (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            بازگشت پوچ;
        }
    }

    اگر (window->surface) {
        // We may have gone recursive and already created the surface
        بازگشت window->surface;
    }

    بازگشت SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    بازگشت window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, پوچ);

    اگر (!window->surface_valid) {
        اگر (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = پوچ;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        اگر (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    بازگشت window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, صحیح vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!_this->SetWindowFramebufferVSync) {
        بازگشت SDL_Unsupported();
    }
    بازگشت _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, صحیح *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!_this->GetWindowFramebufferVSync) {
        بازگشت SDL_Unsupported();
    }
    بازگشت _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    بازگشت SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ثابت SDL_Rect *rects,
                                 صحیح numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!window->surface_valid) {
        بازگشت SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    بازگشت _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = پوچ;
        window->surface_valid = false;
    }

    اگر (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        اگر (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    بازگشت true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, اعشاری opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    اگر (!_this->SetWindowOpacity) {
        بازگشت SDL_Unsupported();
    }

    اگر (opacity < 0.0f) {
        opacity = 0.0f;
    } وگرنه اگر (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    اگر (result) {
        window->opacity = opacity;
    }

    بازگشت result;
}

اعشاری SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    بازگشت window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    اگر (window == parent) {
        بازگشت SDL_SetError("Cannot set the parent of a window to itself.");
    }

    اگر (!_this->SetWindowParent) {
        بازگشت SDL_Unsupported();
    }

    اگر (window->flags & SDL_WINDOW_MODAL) {
        بازگشت SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    اگر (window->parent == parent) {
        بازگشت true;
    }

    ثابت bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : پوچ);

    بازگشت ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (!_this->SetWindowModal) {
        بازگشت SDL_Unsupported();
    }

    اگر (modal) {
        اگر (!window->parent) {
            بازگشت SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } وگرنه اگر (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } وگرنه {
        بازگشت true; // Already not modal, so nothing to do.
    }

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        بازگشت true;
    }

    بازگشت _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_درون_داد_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    وقتی (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        اگر (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_درون_داد_FOCUS);
        }
    }

    *new_focus = focus;
    بازگشت set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    برای (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    برای (w = current_focus; w != toplevel_parent; w = w->parent) {
        اگر (w == window) {
            found_higher_focus = true;
            بشکن;
        }
    }

    بازگشت !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    اگر ((want != have) && (_this->SetWindowFocusable)) {
        اگر (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } وگرنه {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        اگر (!_this->SetWindowFocusable(_this, window, want)) {
            بازگشت false;
        }
    }

    بازگشت true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    اگر ((want != have) && (_this->SetWindowFillDocument)) {
        اگر (!_this->SetWindowFillDocument(_this, window, want)) {
            بازگشت false;
        } وگرنه اگر (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } وگرنه {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    بازگشت true;
}

تهی SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    اگر (window->flags & SDL_WINDOW_درون_داد_FOCUS) {
        اگر (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } وگرنه {
            mouse_grabbed = false;
        }

        اگر (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } وگرنه {
            keyboard_grabbed = false;
        }
    } وگرنه {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    اگر (mouse_grabbed || keyboard_grabbed) {
        اگر (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            اگر (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            اگر (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } وگرنه اگر (_this->grabbed_window == window) {
        _this->grabbed_window = پوچ; // ungrabbing input.
    }

    اگر (_this->SetWindowMouseGrab) {
        اگر (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    اگر (_this->SetWindowKeyboardGrab) {
        اگر (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    اگر (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = پوچ;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        اگر (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } وگرنه {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        بازگشت true;
    }

    اگر (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        بازگشت true;
    }
    اگر (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } وگرنه {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    اگر (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        بازگشت false;
    }
    بازگشت true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (window->flags & SDL_WINDOW_HIDDEN) {
        اگر (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } وگرنه {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        بازگشت true;
    }

    اگر (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        بازگشت true;
    }
    اگر (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } وگرنه {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    اگر (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        بازگشت false;
    }
    بازگشت true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    بازگشت window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    بازگشت window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(تهی)
{
    اگر (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        بازگشت _this->grabbed_window;
    } وگرنه {
        بازگشت پوچ;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ثابت SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!_this->SetWindowMouseRect) {
        بازگشت SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    اگر (!rect) {
        rect = &zero;
    }

    اگر (SDL_memcmp(&window->mouse_rect, rect, اندازه(*rect)) == 0) {
        بازگشت true;
    }
    SDL_memcpy(&window->mouse_rect, rect, اندازه(*rect));

    بازگشت _this->SetWindowMouseRect(_this, window);
}

ثابت SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, پوچ);

    اگر (SDL_RectEmpty(&window->mouse_rect)) {
        بازگشت پوچ;
    } وگرنه {
        بازگشت &window->mouse_rect;
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

    اگر (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        بازگشت true;
    }

    اگر (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } وگرنه {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    اگر (!SDL_UpdateRelativeMouseMode()) {
        اگر (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } وگرنه {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        بازگشت false;
    }
    بازگشت true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        بازگشت true;
    } وگرنه {
        بازگشت false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (_this->FlashWindow) {
        بازگشت _this->FlashWindow(_this, window, operation);
    }

    بازگشت SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        بازگشت SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    اگر (_this->ApplyWindowProgress) {
        اگر (!_this->ApplyWindowProgress(_this, window)) {
            بازگشت false;
        }
    }

    بازگشت true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    بازگشت window->progress_state;
}

bool SDL_Set_Window_Progress_مقدار(SDL_Window *window, اعشاری مقدار)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    مقدار = SDL_clamp(مقدار, 0.0f, 1.f);

    window->progress_مقدار = مقدار;

    اگر (_this->ApplyWindowProgress) {
        اگر (!_this->ApplyWindowProgress(_this, window)) {
            بازگشت false;
        }
    }

    بازگشت true;
}

اعشاری SDL_Get_Window_Progress_مقدار(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    بازگشت window->progress_مقدار;
}

تهی SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

تهی SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

تهی SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    اگر (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ثابت bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        اگر (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_بالا_density_modes = false;

            اگر (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_بالا_density_modes = true;
            }
            ثابت bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_بالا_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            اگر (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } وگرنه {
            SDL_zero(window->current_fullscreen_mode);
        }

        اگر (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

تهی SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

تهی SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    اگر ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, پوچ);
        اگر (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

تهی SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    صحیح pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

تهی SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

تهی SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    اگر (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } وگرنه {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ایستا تهی SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_چپ;
    rect.y = window->safe_inset_بالاترین;
    rect.w = window->w - (window->safe_inset_راست + window->safe_inset_چپ);
    rect.h = window->h - (window->safe_inset_بالاترین + window->safe_inset_bottom);
    اگر (SDL_memcmp(&rect, &window->safe_rect, اندازه(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

تهی SDL_SetWindowSafeAreaInsets(SDL_Window *window, صحیح چپ, صحیح راست, صحیح بالاترین, صحیح bottom)
{
    window->safe_inset_چپ = چپ;
    window->safe_inset_راست = راست;
    window->safe_inset_بالاترین = بالاترین;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    اگر (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    اگر (rect) {
        اگر (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } وگرنه {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    بازگشت true;
}

تهی SDL_OnWindowMinimized(SDL_Window *window)
{
    اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

تهی SDL_OnWindowMaximized(SDL_Window *window)
{
}

تهی SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    اگر (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

تهی SDL_OnWindowEnter(SDL_Window *window)
{
    اگر (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

تهی SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

تهی SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    اگر (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

ایستا bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ثابت نویسه *hint;

    اگر (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        بازگشت false;
    }

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    اگر (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        اگر (Cocoa_IsShowingModalDialog(window)) {
            بازگشت false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } وگرنه اگر (Cocoa_IsWindowInFullscreenSpace(window)) {
            بازگشت false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        بیرونی bool Android_JNI_ShouldMinimizeOnFocusLoss(تهی);
        اگر (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            بازگشت false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    اگر (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        اگر (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            بازگشت true;
        } وگرنه {
            بازگشت false;
        }
    }
    بازگشت SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

تهی SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    اگر (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(تهی)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    اگر (focus) {
        // Get the toplevel parent window.
        وقتی (focus->parent) {
            focus = focus->parent;
        }
    }

    بازگشت focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->رقم_renderers + 1) * اندازه(*renderers));
    اگر (!renderers) {
        بازگشت false;
    }

    window->renderers = renderers;
    window->renderers[window->رقم_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    بازگشت true;
}

تهی SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    برای (صحیح i = 0; i < window->رقم_renderers; ++i) {
        اگر (window->renderers[i] == renderer) {
            اگر (i < (window->رقم_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->رقم_renderers - i - 1) * اندازه(window->renderers[i]));
            }
            --window->رقم_renderers;
            بشکن;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    اگر (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, پوچ) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

تهی SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    وقتی (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    اگر (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    اگر (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_درون_داد_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    اگر (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    برای (صحیح i = 0; i < _this->رقم_displays; ++i) {
        اگر (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = پوچ;
        }
    }

    // Make sure this window no longer has focus
    اگر (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(پوچ);
    }
    اگر ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    اگر (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(پوچ);
    }

    // Make no context current if this is the current context window
    اگر (window->flags & SDL_WINDOW_OPENGL) {
        اگر (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, پوچ);
        }
    }

    اگر (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    اگر (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    اگر (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    اگر (_this->grabbed_window == window) {
        _this->grabbed_window = پوچ; // ungrabbing input.
    }

    اگر (_this->current_glwin == window) {
        _this->current_glwin = پوچ;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, پوچ);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, پوچ);

    // Unlink the window from the global window list
    اگر (window->next) {
        window->next->prev = window->prev;
    }
    اگر (window->prev) {
        window->prev->next = window->next;
    } وگرنه {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(تهی)
{
    اگر (!_this) {
        بازگشت true;
    }
    بازگشت !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(تهی)
{
    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }
    اگر (!_this->suspend_screensaver) {
        بازگشت true;
    }
    _this->suspend_screensaver = false;
    اگر (_this->SuspendScreenSaver) {
        بازگشت _this->SuspendScreenSaver(_this);
    }

    بازگشت SDL_Unsupported();
}

bool SDL_DisableScreenSaver(تهی)
{
    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }
    اگر (_this->suspend_screensaver) {
        بازگشت true;
    }
    _this->suspend_screensaver = true;
    اگر (_this->SuspendScreenSaver) {
        بازگشت _this->SuspendScreenSaver(_this);
    }

    بازگشت SDL_Unsupported();
}

تهی SDL_QuitVideo(تهی)
{
    صحیح i;

    اگر (!_this) {
        بازگشت;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#اگر 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    وقتی (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    اگر (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    اگر (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    برای (i = _this->رقم_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->رقم_displays == 0);
    SDL_free(_this->displays);
    _this->displays = پوچ;

    SDL_CancelClipboardData(0);

    اگر (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = پوچ;
    }
    _this->آزاد(_this);
    _this = پوچ;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(ثابت نویسه *path)
{
    bool result;

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }
    اگر (_this->gl_config.driver_loaded) {
        اگر (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            بازگشت SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } وگرنه {
        اگر (!_this->GL_LoadLibrary) {
            بازگشت SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    اگر (result) {
        ++_this->gl_config.driver_loaded;
    } وگرنه {
        اگر (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    بازگشت result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ثابت نویسه *proc)
{
    SDL_FunctionPointer func;

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    func = پوچ;
    اگر (_this->GL_GetProcAddress) {
        اگر (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } وگرنه {
            SDL_SetError("No GL driver has been loaded");
        }
    } وگرنه {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    بازگشت func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ثابت نویسه *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    func = پوچ;

    اگر (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } وگرنه {
        SDL_SetError("No EGL library has been loaded");
    }

    بازگشت func;
#وگرنه
    SDL_SetError("SDL was not built with EGL support");
    بازگشت پوچ;
#endif
}

تهی SDL_GL_UnloadLibrary(تهی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت;
    }
    اگر (_this->gl_config.driver_loaded > 0) {
        اگر (--_this->gl_config.driver_loaded > 0) {
            بازگشت;
        }
        اگر (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
تعریفنوع GLenum (APIENTRY* PFNGLGETERRORPROC) (تهی);
تعریفنوع تهی (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
تعریفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
تعریفنوع تهی (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
تعریفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

ایستا SDL_INLINE bool isAtLeastGL3(ثابت نویسه *verstr)
{
    بازگشت verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت نویسه *extension)
{
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت نویسه *extensions;
    ثابت نویسه *start;
    ثابت نویسه *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    اگر (where || *extension == '\0') {
        بازگشت false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    اگر (start && *start == '0') {
        بازگشت false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    اگر (!glGetStringFunc) {
        بازگشت false;
    }

    اگر (isAtLeastGL3((ثابت نویسه *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint رقم_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        اگر ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            بازگشت false;
        }

#ifndef GL_رقم_EXTENSIONS
#define GL_رقم_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_رقم_EXTENSIONS, &رقم_exts);
        برای (i = 0; i < رقم_exts; i++) {
            ثابت نویسه *thisext = (ثابت نویسه *)glGetStringiFunc(GL_EXTENSIONS, i);
            اگر (SDL_strcmp(thisext, extension) == 0) {
                بازگشت true;
            }
        }

        بازگشت false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ثابت نویسه *)glGetStringFunc(GL_EXTENSIONS);
    اگر (!extensions) {
        بازگشت false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    برای (;;) {
        where = SDL_strstr(start, extension);
        اگر (!where) {
            بشکن;
        }

        terminator = where + SDL_strlen(extension);
        اگر (where == extensions || *(where - 1) == ' ') {
            اگر (*terminator == ' ' || *terminator == '\0') {
                بازگشت true;
            }
        }

        start = terminator;
    }
    بازگشت false;
#وگرنه
    بازگشت false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
تهی SDL_GL_DeduceMaxSupportedESProfile(صحیح *major, صحیح *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    اگر (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } وگرنه اگر (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } وگرنه اگر (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } وگرنه {
        *major = 2;
        *minor = 0;
    }
#endif
}

تهی SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   تهی *userdata)
{
    اگر (!_this) {
        بازگشت;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

تهی SDL_GL_ResetAttributes(تهی)
{
    اگر (!_this) {
        بازگشت;
    }

    _this->egl_platformattrib_callback = پوچ;
    _this->egl_surfaceattrib_callback = پوچ;
    _this->egl_contextattrib_callback = پوچ;
    _this->egl_attrib_callback_userdata = پوچ;

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
#وگرنهاگر defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#وگرنهاگر defined(SDL_VIDEO_OPENGL_ES)
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

    اگر (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, صحیح مقدار)
{
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }
    result = true;
    انتخاب (attr) {
    حالت SDL_GL_RED_SIZE:
        _this->gl_config.red_size = مقدار;
        بشکن;
    حالت SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = مقدار;
        بشکن;
    حالت SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = مقدار;
        بشکن;
    حالت SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = مقدار;
        بشکن;
    حالت SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = مقدار;
        بشکن;
    حالت SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = مقدار;
        بشکن;
    حالت SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = مقدار;
        بشکن;
    حالت SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = مقدار;
        بشکن;
    حالت SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = مقدار;
        بشکن;
    حالت SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = مقدار;
        بشکن;
    حالت SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = مقدار;
        بشکن;
    حالت SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = مقدار;
        بشکن;
    حالت SDL_GL_STEREO:
        _this->gl_config.stereo = مقدار;
        بشکن;
    حالت SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = مقدار;
        بشکن;
    حالت SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = مقدار;
        بشکن;
    حالت SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = مقدار;
        بشکن;
    حالت SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = مقدار;
        بشکن;
    حالت SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = مقدار;
        بشکن;
    حالت SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = مقدار;
        بشکن;
    حالت SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = مقدار;
        بشکن;
    حالت SDL_GL_CONTEXT_FLAGS:
        اگر (مقدار & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", مقدار);
            بشکن;
        }
        _this->gl_config.flags = مقدار;
        بشکن;
    حالت SDL_GL_CONTEXT_PROFILE_MASK:
        اگر (مقدار != 0 &&
            مقدار != SDL_GL_CONTEXT_PROFILE_CORE &&
            مقدار != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            مقدار != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", مقدار);
            بشکن;
        }
        _this->gl_config.profile_mask = مقدار;
        بشکن;
    حالت SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = مقدار;
        بشکن;
    حالت SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = مقدار;
        بشکن;
    حالت SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = مقدار;
        بشکن;
    حالت SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = مقدار;
        بشکن;
    حالت SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = مقدار;
        بشکن;
    حالت SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = مقدار;
        بشکن;
    پیشفرض:
        result = SDL_SetError("Unknown OpenGL attribute");
        بشکن;
    }
    بازگشت result;
#وگرنه
    بازگشت SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحیح *مقدار)
{
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_چپ;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!مقدار) {
        بازگشت SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *مقدار = 0;

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    انتخاب (attr) {
    حالت SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        بشکن;
    حالت SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        بشکن;
    حالت SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        بشکن;
    حالت SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        بشکن;
    حالت SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        بشکن;
#وگرنه
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *مقدار = _this->gl_config.double_buffer;
        بازگشت true;
#endif
    حالت SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        بشکن;
    حالت SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        بشکن;
#ifdef SDL_VIDEO_OPENGL
    حالت SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        بشکن;
    حالت SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        بشکن;
    حالت SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        بشکن;
    حالت SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        بشکن;
    حالت SDL_GL_STEREO:
        attrib = GL_STEREO;
        بشکن;
#وگرنه
    حالت SDL_GL_ACCUM_RED_SIZE:
    حالت SDL_GL_ACCUM_GREEN_SIZE:
    حالت SDL_GL_ACCUM_BLUE_SIZE:
    حالت SDL_GL_ACCUM_ALPHA_SIZE:
    حالت SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *مقدار = 0;
        بازگشت true;
#endif
    حالت SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        بشکن;
    حالت SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        بشکن;
    حالت SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        بشکن;
    حالت SDL_GL_BUFFER_SIZE:
    {
        صحیح rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        اگر (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            بازگشت false;
        }
        اگر (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            بازگشت false;
        }
        اگر (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            بازگشت false;
        }
        اگر (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            بازگشت false;
        }

        *مقدار = rsize + gsize + bsize + asize;
        بازگشت true;
    }
    حالت SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *مقدار = (_this->gl_config.accelerated != 0);
        بازگشت true;
    }
    حالت SDL_GL_RETAINED_BACKING:
    {
        *مقدار = _this->gl_config.retained_backing;
        بازگشت true;
    }
    حالت SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *مقدار = _this->gl_config.major_version;
        بازگشت true;
    }
    حالت SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *مقدار = _this->gl_config.minor_version;
        بازگشت true;
    }
    حالت SDL_GL_CONTEXT_FLAGS:
    {
        *مقدار = _this->gl_config.flags;
        بازگشت true;
    }
    حالت SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *مقدار = _this->gl_config.profile_mask;
        بازگشت true;
    }
    حالت SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *مقدار = _this->gl_config.share_with_current_context;
        بازگشت true;
    }
    حالت SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *مقدار = _this->gl_config.framebuffer_srgb_capable;
        بازگشت true;
    }
    حالت SDL_GL_CONTEXT_NO_ERROR:
    {
        *مقدار = _this->gl_config.no_error;
        بازگشت true;
    }
    حالت SDL_GL_EGL_PLATFORM:
    {
        *مقدار = _this->gl_config.egl_platform;
        بازگشت true;
    }
    حالت SDL_GL_FLOATBUFFERS:
    {
        اگر (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            بشکن;
        } وگرنه {
            بازگشت 0;
        }
    }
    پیشفرض:
        بازگشت SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    اگر (!glGetStringFunc) {
        بازگشت false;
    }

    اگر (attachmentattrib && isAtLeastGL3((ثابت نویسه *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        اگر (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        اگر (glGetFramebufferAttachmentParameterivFunc) {
            اگر (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            اگر (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            اگر (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)مقدار);
            } وگرنه {
                *مقدار = 0;
            }
            اگر (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } وگرنه {
            بازگشت false;
        }
    } وگرنه
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        اگر (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)مقدار);
        } وگرنه {
            بازگشت false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    اگر (!glGetErrorFunc) {
        بازگشت false;
    }

    error = glGetErrorFunc();
    اگر (error != GL_NO_ERROR) {
        اگر (error == GL_INVALID_ENUM) {
            بازگشت SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } وگرنه اگر (error == GL_INVALID_مقدار) {
            بازگشت SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        بازگشت SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    اگر (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *مقدار = (*مقدار == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    بازگشت true;
#وگرنه
    بازگشت SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = پوچ;
    CHECK_WINDOW_MAGIC(window, پوچ);

    اگر (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        بازگشت پوچ;
    }

#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحیح srgb_requested = -1;
    ثابت نویسه *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    اگر (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    اگر (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, پوچ);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, پوچ);
    }

#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    اگر (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        اگر (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            اگر (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } وگرنه {
                supported = isAtLeastGL3((ثابت نویسه *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            اگر (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    بازگشت ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }

    اگر (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        بازگشت true;
    }

    اگر (!context) {
        window = پوچ;
    } وگرنه اگر (window) {
        CHECK_WINDOW_MAGIC(window, false);

        اگر (!(window->flags & SDL_WINDOW_OPENGL)) {
            بازگشت SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } وگرنه اگر (!_this->gl_allow_no_surface) {
        بازگشت SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    اگر (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, پوچ);
        SDL_SetTLS(&_this->current_glctx_tls, context, پوچ);
    }
    بازگشت result;
}

SDL_Window *SDL_GL_GetCurrentWindow(تهی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    بازگشت (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(تهی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    بازگشت (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(تهی)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت EGL_NO_DISPLAY;
    }
    اگر (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        بازگشت EGL_NO_DISPLAY;
    }
    بازگشت _this->egl_data->egl_display;
#وگرنه
    SDL_SetError("SDL was not built with EGL support");
    بازگشت پوچ;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(تهی)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    اگر (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        بازگشت پوچ;
    }
    بازگشت _this->egl_data->egl_config;
#وگرنه
    SDL_SetError("SDL was not built with EGL support");
    بازگشت پوچ;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    اگر (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        بازگشت پوچ;
    }
    اگر (_this->GL_GetEGLSurface) {
        بازگشت _this->GL_GetEGLSurface(_this, window);
    }
    بازگشت پوچ;
#وگرنه
    SDL_SetError("SDL was not built with EGL support");
    بازگشت پوچ;
#endif
}

bool SDL_GL_SetSwapInterval(صحیح interval)
{
    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    } وگرنه اگر (SDL_GL_GetCurrentContext() == پوچ) {
        بازگشت SDL_SetError("No OpenGL context has been made current");
    } وگرنه اگر (_this->GL_SetSwapInterval) {
        بازگشت _this->GL_SetSwapInterval(_this, interval);
    } وگرنه {
        بازگشت SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(صحیح *interval)
{
    CHECK_PARAM(!interval) {
       بازگشت SDL_InvalidParamError("interval");
    }

    *interval = 0;

    اگر (!_this) {
        بازگشت SDL_SetError("no video driver");
    } وگرنه اگر (SDL_GL_GetCurrentContext() == پوچ) {
        بازگشت SDL_SetError("no current context");
    } وگرنه اگر (_this->GL_GetSwapInterval) {
        بازگشت _this->GL_GetSwapInterval(_this, interval);
    } وگرنه {
        بازگشت SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!(window->flags & SDL_WINDOW_OPENGL)) {
        بازگشت SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    اگر (SDL_GL_GetCurrentWindow() != window) {
        بازگشت SDL_SetError("The specified window has not been made current");
    }

    بازگشت _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        بازگشت SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        بازگشت SDL_InvalidParamError("context");
    }

    اگر (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(پوچ, پوچ);
    }

    بازگشت _this->GL_DestroyContext(_this, context);
}

#اگر 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ایستا تهی Create_Mask_From_Color_کلید_Or_Alpha(SDL_Surface *icon, Uint8 *mask, صحیح flags)
{
    صحیح x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    انتخاب (SDL_BYTESPERPIXEL(icon->format)) {
    حالت 1:
        {
            Uint8 *pixels;
            برای (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                برای (x = 0; x < icon->w; ++x) {
                    اگر (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        بشکن;

    حالت 2:
        {
            Uint16 *pixels;
            برای (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                برای (x = 0; x < icon->w; ++x) {
                    اگر ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } وگرنه اگر ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        بشکن;

    حالت 4:
        {
            Uint32 *pixels;
            برای (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                برای (x = 0; x < icon->w; ++x) {
                    اگر ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } وگرنه اگر ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        بشکن;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
تهی SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    اگر (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        اگر (mask == پوچ) {
            صحیح mask_len = icon->h * (icon->w + 7) / 8;
            صحیح flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            اگر (mask == پوچ) {
                بازگشت;
            }
            SDL_memset(mask, ~0, mask_len);
            اگر (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            اگر (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            اگر (flags) {
                Create_Mask_From_Color_کلید_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } وگرنه {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_درون_داد_Type SDL_Get_Text_درون_داد_Type(SDL_PropertiesID props)
{
    بازگشت (SDL_Text_درون_داد_Type)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_TYPE_عدد, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_درون_داد_Capitalization(SDL_PropertiesID props)
{
    اگر (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_عدد)) {
        بازگشت (SDL_Capitalization)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_عدد, SDL_CAPITALIZE_NONE);
    }

    انتخاب (SDL_Get_Text_درون_داد_Type(props)) {
    حالت SDL_TEXTINPUT_TYPE_TEXT:
        بازگشت SDL_CAPITALIZE_SENTENCES;
    حالت SDL_TEXTINPUT_TYPE_TEXT_NAME:
        بازگشت SDL_CAPITALIZE_واژگان;
    پیشفرض:
        بازگشت SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_درون_داد_Autocorrect(SDL_PropertiesID props)
{
    بازگشت SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_درون_داد_Multiline(SDL_PropertiesID props)
{
    اگر (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        بازگشت SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    اگر (SDL_GetHintBoolean(SDL_HINT_RETURN_کلید_HIDES_IME, false)) {
        بازگشت false;
    } وگرنه {
        بازگشت true;
    }
}

ایستا bool AutoShowingScreenKeyboard(تهی)
{
    ثابت نویسه *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    اگر (!hint) {
        // This hint is currently only used by the X11 video driver
        اگر (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    اگر (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        بازگشت true;
    } وگرنه {
        بازگشت false;
    }
}

bool SDL_Start_Text_درون_داد(SDL_Window *window)
{
    بازگشت SDL_Start_Text_درون_داد_With_Properties(window, 0);
}

bool SDL_Start_Text_درون_داد_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (window->text_درون_داد_props) {
        SDL_DestroyProperties(window->text_درون_داد_props);
        window->text_درون_داد_props = 0;
    }

    اگر (props) {
        window->text_درون_داد_props = SDL_CreateProperties();
        اگر (!window->text_درون_داد_props) {
            بازگشت false;
        }
        اگر (!SDL_CopyProperties(props, window->text_درون_داد_props)) {
            بازگشت false;
        }
    }

    اگر (_this->Set_Text_درون_داد_Properties) {
        _this->Set_Text_درون_داد_Properties(_this, window, props);
    }

    اگر (!window->text_درون_داد_active) {
        // Start the text input system
        اگر (_this->Start_Text_درون_داد) {
            اگر (!_this->Start_Text_درون_داد(_this, window, props)) {
                بازگشت false;
            }
        }
        window->text_درون_داد_active = true;
    }

    // Show the on-screen keyboard, if desired
    اگر (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        اگر (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    بازگشت true;
}

bool SDL_Text_درون_داد_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    بازگشت window->text_درون_داد_active;
}

bool SDL_Stop_Text_درون_داد(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (window->text_درون_داد_active) {
        // Stop the text input system
        اگر (_this->Stop_Text_درون_داد) {
            _this->Stop_Text_درون_داد(_this, window);
        }
        window->text_درون_داد_active = false;
    }

    // Hide the on-screen keyboard, if desired
    اگر (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        اگر (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    بازگشت true;
}

bool SDL_Set_Text_درون_داد_Area(SDL_Window *window, ثابت SDL_Rect *rect, صحیح cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (rect) {
        SDL_copyp(&window->text_درون_داد_rect, rect);
        window->text_درون_داد_cursor = cursor;
    } وگرنه {
        SDL_zero(window->text_درون_داد_rect);
        window->text_درون_داد_cursor = 0;
    }

    اگر (_this && _this->Update_Text_درون_داد_Area) {
        اگر (!_this->Update_Text_درون_داد_Area(_this, window)) {
            بازگشت false;
        }
    }
    بازگشت true;
}

bool SDL_Get_Text_درون_داد_Area(SDL_Window *window, SDL_Rect *rect, صحیح *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (rect) {
        SDL_copyp(rect, &window->text_درون_داد_rect);
    }
    اگر (cursor) {
        *cursor = window->text_درون_داد_cursor;
    }
    بازگشت true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (_this->ClearComposition) {
        بازگشت _this->ClearComposition(_this, window);
    }
    بازگشت true;
}

bool SDL_HasScreenKeyboardSupport(تهی)
{
    اگر (_this && _this->HasScreenKeyboardSupport) {
        بازگشت _this->HasScreenKeyboardSupport(_this);
    }
    بازگشت false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    بازگشت _this->screen_keyboard_shown;
}

تهی SDL_SendScreenKeyboardShown(تهی)
{
    اگر (!_this || _this->screen_keyboard_shown) {
        بازگشت;
    }

    _this->screen_keyboard_shown = true;

    اگر (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_افزودن_Event(&event);
    }
}

تهی SDL_SendScreenKeyboardHidden(تهی)
{
    اگر (!_this || !_this->screen_keyboard_shown) {
        بازگشت;
    }

    _this->screen_keyboard_shown = false;

    اگر (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_افزودن_Event(&event);
    }
}

صحیح SDL_Get_Message_Box_شمار(تهی)
{
    بازگشت SDL_GetAtomicInt(&SDL_messagebox_شمار);
}

bool SDL_ShowMessageBox(ثابت SDL_MessageBoxData *messageboxdata, صحیح *buttonID)
{
    صحیح dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        بازگشت SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        بازگشت SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    نویسه *titlecpy = پوچ;
    نویسه *msgcpy = پوچ;
    اگر (messageboxdata->title) {
        ثابت size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(نویسه, slen, &titleisstack);
        اگر (!titlecpy) {
            بازگشت false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    اگر (messageboxdata->message) {
        ثابت size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(نویسه, slen, &msgisstack);
        اگر (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            بازگشت false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (تهی)SDL_AtomicIncRef(&SDL_messagebox_شمار);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    اگر (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, اندازه(*messageboxdata));
    mbdata.title = titlecpy;
    اگر (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    اگر (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    اگر (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } وگرنه {
        // It's completely fine to call this function before video is initialized
        ثابت نویسه *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        اگر (driver_name && *driver_name != 0) {
            ثابت نویسه *driver_attempt = driver_name;
            وقتی (driver_attempt && (*driver_attempt != 0) && !result) {
                ثابت نویسه *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                برای (صحیح i = 0; bootstrap[i]; ++i) {
                    اگر (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        اگر (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        بشکن;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : پوچ;
            }
        } وگرنه {
            برای (صحیح i = 0; bootstrap[i]; ++i) {
                اگر (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    بشکن;
                }
            }
        }
    }

    اگر (!result) {
        ثابت نویسه *error = SDL_GetError();

        اگر (!*error) {
            SDL_SetError("No message system available");
        }
    } وگرنه {
        SDL_ClearError();
    }

    (تهی)SDL_AtomicDecRef(&SDL_messagebox_شمار);

    اگر (current_window) {
        SDL_RaiseWindow(current_window);
    }

    اگر (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    بازگشت result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ثابت نویسه *title, ثابت نویسه *message, SDL_Window *window)
{
#اگر defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_راست;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_راست = gsp_Has_Gpu_راست();
    اگر (!has_Gpu_راست)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    اگر (!has_Gpu_راست)
        gfxExit();

    بازگشت true;
#وگرنه
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

    بازگشت SDL_ShowMessageBox(&data, پوچ);
#endif
}

bool SDL_ShouldAllowTopmost(تهی)
{
    بازگشت SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, صحیح x, صحیح y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    اگر (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        بازگشت true;
    }

    بازگشت SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, تهی *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!_this->SetWindowHitTest) {
        بازگشت SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    بازگشت _this->SetWindowHitTest(window, callback != پوچ);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    اگر (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        بازگشت SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    اگر (!props) {
        بازگشت false;
    }

    اگر (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        اگر (!surface) {
            بازگشت false;
        }
    } وگرنه {
        surface = پوچ;
    }

    اگر (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        بازگشت false;
    }

    اگر (_this->UpdateWindowShape) {
        اگر (!_this->UpdateWindowShape(_this, window, surface)) {
            بازگشت false;
        }
    }
    بازگشت true;
}

/*
 * Functions used by iOS application delegates
 */
تهی SDL_OnApplicationWillTerminate(تهی)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

تهی SDL_OnApplicationDidReceiveMemoryWarning(تهی)
{
    SDL_SendAppEvent(SDL_EVENT_کم_MEMORY);
}

تهی SDL_OnApplicationWillEnterBackground(تهی)
{
    اگر (_this) {
        SDL_Window *window;
        برای (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(پوچ);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

تهی SDL_OnApplicationDidEnterBackground(تهی)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

تهی SDL_OnApplicationWillEnterForeground(تهی)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

تهی SDL_OnApplicationDidEnterForeground(تهی)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    اگر (_this) {
        SDL_Window *window;
        برای (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ثابت نویسه *path)
{
    bool result;

    اگر (!_this) {
        بازگشت SDL_UninitializedVideo();
    }
    اگر (_this->vulkan_config.loader_loaded) {
        اگر (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            بازگشت SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } وگرنه {
        اگر (!_this->Vulkan_LoadLibrary) {
            بازگشت SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    اگر (result) {
        _this->vulkan_config.loader_loaded++;
    }
    بازگشت result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(تهی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت پوچ;
    }
    اگر (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        بازگشت پوچ;
    }
    بازگشت (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

تهی SDL_Vulkan_UnloadLibrary(تهی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        بازگشت;
    }
    اگر (_this->vulkan_config.loader_loaded > 0) {
        اگر (--_this->vulkan_config.loader_loaded > 0) {
            بازگشت;
        }
        اگر (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

نویسه ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *شمار)
{
    Uint32 tmpcount = 0;
    اگر (!شمار) {
        شمار = &tmpcount;
    }

    اگر (!_this->Vulkan_GetInstanceExtensions) {
        *شمار = 0;
        SDL_Unsupported();
        بازگشت پوچ;
    }

    بازگشت _this->Vulkan_GetInstanceExtensions(_this, شمار);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ثابت ساختار VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    اگر (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        بازگشت false;
    }

    CHECK_PARAM(!instance) {
        بازگشت SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        بازگشت SDL_InvalidParamError("surface");
    }

    اگر (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        اگر (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        اگر (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        اگر (SDL_Vulkan_LoadLibrary(پوچ)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } وگرنه {
            بازگشت SDL_SetError("failed to load Vulkan library");
        }
    }

    بازگشت _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

تهی SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت ساختار VkAllocationCallbacks *allocator)
{
    اگر (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        بازگشت false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        بازگشت false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        بازگشت false;
    }

    اگر (_this->Vulkan_GetPresentationSupport) {
        بازگشت _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    بازگشت true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, پوچ);

    اگر (!_this->Metal_CreateView) {
        SDL_Unsupported();
        بازگشت پوچ;
    }

    اگر (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        اگر (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        اگر (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    بازگشت _this->Metal_CreateView(_this, window);
}

تهی SDL_Metal_DestroyView(SDL_MetalView view)
{
    اگر (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

تهی *SDL_Metal_GetLayer(SDL_MetalView view)
{
    اگر (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            بازگشت پوچ;
        }
        بازگشت _this->Metal_GetLayer(_this, view);
    } وگرنه {
        SDL_SetError("Metal is not supported.");
        بازگشت پوچ;
    }
}

#اگر defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ثابت نویسه *SDL_GetCSSCursorName(SDL_SystemCursor id, ثابت نویسه **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    انتخاب (id) {
    حالت SDL_SYSTEM_CURSOR_DEFAULT:
        بازگشت "default";

    حالت SDL_SYSTEM_CURSOR_TEXT:
        بازگشت "text";

    حالت SDL_SYSTEM_CURSOR_WAIT:
        بازگشت "wait";

    حالت SDL_SYSTEM_CURSOR_CROSSHAIR:
        بازگشت "crosshair";

    حالت SDL_SYSTEM_CURSOR_PROGRESS:
        بازگشت "progress";

    حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        اگر (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        بازگشت "nwse-resize";

    حالت SDL_SYSTEM_CURSOR_NESW_RESIZE:
        اگر (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        بازگشت "nesw-resize";

    حالت SDL_SYSTEM_CURSOR_EW_RESIZE:
        اگر (fallback_name) {
            *fallback_name = "col-resize";
        }
        بازگشت "ew-resize";

    حالت SDL_SYSTEM_CURSOR_NS_RESIZE:
        اگر (fallback_name) {
            *fallback_name = "row-resize";
        }
        بازگشت "ns-resize";

    حالت SDL_SYSTEM_CURSOR_MOVE:
        اگر (fallback_name) {
            *fallback_name = "all-scroll";
        }
        بازگشت "move";

    حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        بازگشت "not-allowed";

    حالت SDL_SYSTEM_CURSOR_POINTER:
        بازگشت "pointer";

    حالت SDL_SYSTEM_CURSOR_NW_RESIZE:
        بازگشت "nw-resize";

    حالت SDL_SYSTEM_CURSOR_N_RESIZE:
        بازگشت "n-resize";

    حالت SDL_SYSTEM_CURSOR_NE_RESIZE:
        بازگشت "ne-resize";

    حالت SDL_SYSTEM_CURSOR_E_RESIZE:
        بازگشت "e-resize";

    حالت SDL_SYSTEM_CURSOR_SE_RESIZE:
        بازگشت "se-resize";

    حالت SDL_SYSTEM_CURSOR_S_RESIZE:
        بازگشت "s-resize";

    حالت SDL_SYSTEM_CURSOR_SW_RESIZE:
        بازگشت "sw-resize";

    حالت SDL_SYSTEM_CURSOR_W_RESIZE:
        بازگشت "w-resize";

    حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        بازگشت "context-menu";

    حالت SDL_SYSTEM_CURSOR_HELP:
        بازگشت "help";

    حالت SDL_SYSTEM_CURSOR_CELL:
        بازگشت "cell";

    حالت SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        بازگشت "vertical-text";

    حالت SDL_SYSTEM_CURSOR_ALIAS:
        بازگشت "alias";

    حالت SDL_SYSTEM_CURSOR_COPY:
        بازگشت "copy";

    حالت SDL_SYSTEM_CURSOR_NO_DROP:
        بازگشت "no-drop";

    حالت SDL_SYSTEM_CURSOR_GRAB:
        بازگشت "grab";

    حالت SDL_SYSTEM_CURSOR_GRABBING:
        بازگشت "grabbing";

    حالت SDL_SYSTEM_CURSOR_COL_RESIZE:
        بازگشت "col-resize";

    حالت SDL_SYSTEM_CURSOR_ROW_RESIZE:
        بازگشت "row-resize";

    حالت SDL_SYSTEM_CURSOR_ALL_SCROLL:
        اگر (fallback_name) {
            *fallback_name = "move";
        }
        بازگشت "all-scroll";

    حالت SDL_SYSTEM_CURSOR_ZOOM_IN:
        بازگشت "zoom-in";

    حالت SDL_SYSTEM_CURSOR_ZOOM_OUT:
        بازگشت "zoom-out";

    پیشفرض:
        بازگشت "default";
    }
}
#endif

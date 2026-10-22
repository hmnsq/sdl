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

#include "SDL_internal.h"

// The high-level video driver subsystem

#include "SDL_sysvideo.h"
#include "SDL_clipboard_c.h"
#include "SDL_egl_c.h"
#include "SDL_surface_c.h"
#include "SDL_pixels_c.h"
#include "SDL_rect_c.h"
#include "SDL_video_c.h"
#include "../events/SDL_events_c.h"
#include "../SDL_hints_c.h"
#include "../SDL_properties_c.h"
#include "../timer/SDL_timer_c.h"
#include "../camera/SDL_camera_c.h"
#include "../render/SDL_sysrender.h"
#include "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#include <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#නම් defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#include <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#නම් defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#include <SDL3/SDL_opengles2.h>
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
#include <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#include <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
static VideoBootStrap *bootstrap[] = {
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
    NULL
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        ආපසු result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ආපසු result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        ආපසු result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ආපසු result;                                                  \
    }

#නම් defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
extern bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
extern bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
extern bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
extern bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
extern void SDL_UpdateLifecycleObserver(void);
#endif

static void SDL_CheckWindowDisplayChanged(SDL_Window *window);
static void SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
static void SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
static bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    නම් (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ආපසු true;
    }
    ආපසු false;
}

static bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ආපසු !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

static bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ආපසු !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

static bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ආපසු !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

static bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ආපසු !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

static bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ආපසු !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
static bool syncHint;

static void SDL_SyncHintWatcher(void *userdata, const var_na *name, const var_na *oldValue, const var_na *newValue)
{
    syncHint = SDL_GetStringBoolean(newValue, false);
}

static void SDL_SyncIfRequired(SDL_Window *window)
{
    නම් (syncHint) {
        SDL_SyncWindow(window);
    }
}

static void SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    නම් (window->parent) {
        නම් (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        නම් (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } නැතහොත් {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = NULL;
    }

    නම් (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        නම් (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

typedef sa_nracanaa
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    void *pixels;
    පූර්ණ_සංඛ්‍යා pitch;
    පූර්ණ_සංඛ්‍යා bytes_per_pixel;
} SDL_WindowTextureData;

static Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#නම් (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    නම් (_this->GL_CreateContext) {
        ආපසු SDL_WINDOW_OPENGL;
    }
#endif
#නම් defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    නම් (_this->Metal_CreateView) {
        ආපසු SDL_WINDOW_METAL;
    }
#endif
#නම් defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    නම් (SDL_strcmp(_this->name, "openvr") == 0) {
        ආපසු SDL_WINDOW_OPENGL;
    }
#endif
    ආපසු 0;
}

static bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, void **pixels, පූර්ණ_සංඛ්‍යා *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    const bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    පූර්ණ_සංඛ්‍යා i;
    පූර්ණ_සංඛ්‍යා w, h;
    const SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    නම් (!data) {
        SDL_Renderer *renderer = NULL;
        const var_na *render_driver = NULL;

        // See if there's a render driver being requested
        const var_na *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        නම් (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        නම් (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        නම් (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = NULL;
        }

        var_na *render_driver_copy = NULL;
        නම් (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            නම් (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                var_na *prev = render_driver_copy;
                var_na *ptr = prev;
                අතරතුර ((ptr = SDL_strchr(ptr, ',')) != NULL) {
                    *ptr = '\0';
                    const bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    නම් (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } නැතහොත් {
                        ptr++;
                        prev = ptr;
                    }
                }

                නම් (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        නම් (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            නම් (!renderer) {
                // The error for this specific renderer has already been set
                ආපසු false;
            }
        } නැතහොත් {
            SDL_assert(render_driver_copy == NULL);
            const පූර්ණ_සංඛ්‍යා total = SDL_GetNumRenderDrivers();
            සඳහා (i = 0; i < total; ++i) {
                const var_na *name = SDL_GetRenderDriver(i);
                නම් (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    නම් (renderer) {
                        bha_nga; // this will work.
                    }
                }
            }
            නම් (!renderer) {
                ආපසු SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != NULL); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, parimaa_na(*data));
        නම් (!data) {
            SDL_DestroyRenderer(renderer);
            ආපසු false;
        }
        නම් (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            ආපසු false;
        }

        data->renderer = renderer;
    }

    texture_formats = (const SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, NULL);
    නම් (!texture_formats) {
        ආපසු false;
    }

    // Free any old texture and pixel data
    නම් (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = NULL;
    }
    SDL_free(data->pixels);
    data->pixels = NULL;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    සඳහා (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        නම් (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            bha_nga;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    නම් (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ආපසු false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        const size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        නම් (!data->pixels) {
            ආපසු false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, NULL);

    ආපසු true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, පූර්ණ_සංඛ්‍යා vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    නම් (!data) {
        ආපසු false;
    }
    නම් (!data->renderer) {
        ආපසු false;
    }
    ආපසු SDL_SetRenderVSync(data->renderer, vsync);
}

static bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, පූර්ණ_සංඛ්‍යා *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    නම් (!data) {
        ආපසු false;
    }
    නම් (!data->renderer) {
        ආපසු false;
    }
    ආපසු SDL_GetRenderVSync(data->renderer, vsync);
}

static bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects, පූර්ණ_සංඛ්‍යා numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    void *src;
    පූර්ණ_සංඛ්‍යා w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    නම් (!data || !data->texture) {
        ආපසු SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    නම් (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (void *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        නම් (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            ආපසු false;
        }

        නම් (!SDL_RenderTexture(data->renderer, data->texture, NULL, NULL)) {
            ආපසු false;
        }

        SDL_RenderPresent(data->renderer);
    }
    ආපසු true;
}

static void SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    නම් (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);

        නම් (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        නම් (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

static SDL_VideoDevice *_this = NULL;
static SDL_AtomicInt SDL_messagebox_count;

static පූර්ණ_සංඛ්‍යා SDLCALL cmpmodes(const void *A, const void *B)
{
    const SDL_DisplayMode *a = (const SDL_DisplayMode *)A;
    const SDL_DisplayMode *b = (const SDL_DisplayMode *)B;
    පූර්ණ_සංඛ්‍යා a_refresh_rate = (පූර්ණ_සංඛ්‍යා)(a->refresh_rate * 100);
    පූර්ණ_සංඛ්‍යා b_refresh_rate = (පූර්ණ_සංඛ්‍යා)(b->refresh_rate * 100);
    පූර්ණ_සංඛ්‍යා a_pixel_density = (පූර්ණ_සංඛ්‍යා)(a->pixel_density * 100);
    පූර්ණ_සංඛ්‍යා b_pixel_density = (පූර්ණ_සංඛ්‍යා)(b->pixel_density * 100);

    නම් (a->w != b->w) {
        ආපසු b->w - a->w;
    } නැතහොත් නම් (a->h != b->h) {
        ආපසු b->h - a->h;
    } නැතහොත් නම් (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ආපසු SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } නැතහොත් නම් (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ආපසු SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } නැතහොත් නම් (a_refresh_rate != b_refresh_rate) {
        ආපසු b_refresh_rate - a_refresh_rate;
    } නැතහොත් නම් (a_pixel_density != b_pixel_density) {
        ආපසු a_pixel_density - b_pixel_density;
    }
    ආපසු 0;
}

bool SDL_UninitializedVideo(void)
{
    ආපසු SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
static const VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

පූර්ණ_සංඛ්‍යා SDL_GetNumVideoDrivers(void)
{
    static පූර්ණ_සංඛ්‍යා num_drivers = -1;

    නම් (num_drivers >= 0) {
        ආපසු num_drivers;
    }

    num_drivers = 0;

    // Build a list of unique video drivers.
    සඳහා (පූර්ණ_සංඛ්‍යා i = 0; bootstrap[i] != NULL; ++i) {
        bool duplicate = false;
        සඳහා (පූර්ණ_සංඛ්‍යා j = 0; j < i; ++j) {
            නම් (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                bha_nga;
            }
        }

        නම් (!duplicate) {
            deduped_bootstrap[num_drivers++] = bootstrap[i];
        }
    }

    ආපසු num_drivers;
}

const var_na *SDL_GetVideoDriver(පූර්ණ_සංඛ්‍යා index)
{
    CHECK_PARAM(index < 0 || index >= SDL_GetNumVideoDrivers()) {
        SDL_InvalidParamError("index");
        ආපසු NULL;
    }
    ආපසු deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(const var_na *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    පූර්ණ_සංඛ්‍යා i = 0;

    // Check to make sure we don't overwrite '_this'
    නම් (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    නම් (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        goto pre_driver_error;
    }
    init_events = true;
    නම් (!SDL_InitKeyboard()) {
        goto pre_driver_error;
    }
    init_keyboard = true;
    නම් (!SDL_PreInitMouse()) {
        goto pre_driver_error;
    }
    init_mouse = true;
    නම් (!SDL_InitTouch()) {
        goto pre_driver_error;
    }
    init_touch = true;
    නම් (!SDL_InitPen()) {
        goto pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = NULL;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    නම් (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    නම් (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    නම් (driver_name && *driver_name != 0) {
        const var_na *driver_attempt = driver_name;
        අතරතුර (driver_attempt && *driver_attempt != 0 && !video) {
            const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            සඳහා (i = 0; bootstrap[i]; ++i) {
                නම් (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    නම් (video) {
                        bha_nga;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
        }
    } නැතහොත් {
        සඳහා (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            නම් (video) {
                bha_nga;
            }
        }
    }
    නම් (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } නැතහොත් {
        නම් (driver_name) {
            SDL_SetError("%s not available", driver_name);
            goto pre_driver_error;
        }
        SDL_SetError("No available video device");
        goto pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = NULL;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    නම් (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ආපසු false;
    }

    // Make sure some displays were added
    නම් (_this->num_displays == 0) {
        SDL_QuitVideo();
        ආපසු SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, NULL);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    නම් (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ආපසු true;

pre_driver_error:
    SDL_assert(_this == NULL);
    නම් (init_pen) {
        SDL_QuitPen();
    }
    නම් (init_touch) {
        SDL_QuitTouch();
    }
    නම් (init_mouse) {
        SDL_QuitMouse();
    }
    නම් (init_keyboard) {
        SDL_QuitKeyboard();
    }
    නම් (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ආපසු false;
}

const var_na *SDL_GetCurrentVideoDriver(void)
{
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    ආපසු _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(void)
{
    ආපසු _this;
}

bool SDL_OnVideoThread(void)
{
    ආපසු (_this && SDL_GetCurrentThreadID() == _this->thread);
}

void SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    නම් (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(void)
{
    නම් (_this) {
        ආපසු _this->system_theme;
    } නැතහොත් {
        ආපසු SDL_SYSTEM_THEME_UNKNOWN;
    }
}

void SDL_UpdateDesktopBounds(void)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(NULL);
    නම් (displays) {
        සඳහා (පූර්ණ_සංඛ්‍යා i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            නම් (SDL_GetDisplayBounds(displays[i], &bounds)) {
                නම් (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } නැතහොත් {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

static void SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    නම් (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    නම් (mode->refresh_rate_numerator > 0) {
        නම් (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (float)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } නැතහොත් {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(const SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    නම් (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, parimaa_na(display.desktop_mode));
    }
    ආපසු SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(const SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    පූර්ණ_සංඛ්‍යා i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(parimaa_na(*new_display));
    නම් (!new_display) {
        ආපසු 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->num_displays + 1) * parimaa_na(*displays));
    නම් (!displays) {
        SDL_free(new_display);
        ආපසු 0;
    }
    _this->displays = displays;
    _this->displays[_this->num_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    නම් (display->name) {
        new_display->name = SDL_strdup(display->name);
    } නැතහොත් {
        var_na name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    නම් (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    සඳහා (i = 0; i < new_display->num_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    නම් (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ආපසු id;
}

void SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    සඳහා (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

void SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

void SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    පූර්ණ_සංඛ්‍යා display_index = SDL_GetDisplayIndex(displayID);
    නම් (display_index < 0) {
        ආපසු;
    }

    display = _this->displays[display_index];

    නම් (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = NULL;
    SDL_free(display->internal);
    display->internal = NULL;
    SDL_free(display);

    නම් (display_index < (_this->num_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->num_displays - display_index - 1) * parimaa_na(_this->displays[display_index]));
    }
    --_this->num_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(පූර්ණ_සංඛ්‍යා *count)
{
    පූර්ණ_සංඛ්‍යා i;
    SDL_DisplayID *displays;

    නම් (!_this) {
        නම් (count) {
            *count = 0;
        }

        SDL_UninitializedVideo();
        ආපසු NULL;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->num_displays + 1) * parimaa_na(*displays));
    නම් (displays) {
        නම් (count) {
            *count = _this->num_displays;
        }

        සඳහා (i = 0; i < _this->num_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } නැතහොත් {
        නම් (count) {
            *count = 0;
        }
    }
    ආපසු displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    පූර්ණ_සංඛ්‍යා display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    නම් (display_index < 0) {
        ආපසු NULL;
    }
    ආපසු _this->displays[display_index];
}

static SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    නම් (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    නම් (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    ආපසු displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ආපසු SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(void)
{
    නම් (!_this || _this->num_displays == 0) {
        SDL_UninitializedVideo();
        ආපසු 0;
    }
    ආපසු _this->displays[0]->id;
}

පූර්ණ_සංඛ්‍යා SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    පූර්ණ_සංඛ්‍යා display_index;

    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු -1;
    }

    සඳහා (display_index = 0; display_index < _this->num_displays; ++display_index) {
        නම් (displayID == _this->displays[display_index]->id) {
            ආපසු display_index;
        }
    }
    SDL_SetError("Invalid display");
    ආපසු -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ආපසු display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ආපසු SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    නම් (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ආපසු display->props;
}

const var_na *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ආපසු display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ආපසු SDL_InvalidParamError("rect");
    }

    නම් (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        නම් (_this->GetDisplayBounds(_this, display, rect)) {
            ආපසු true;
        }
    }

    // Assume that the displays are left to right
    නම් (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } නැතහොත් {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ආපසු true;
}

static පූර්ණ_සංඛ්‍යා ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ආපසු hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ආපසු SDL_InvalidParamError("rect");
    }

    නම් (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ආපසු true;
    }

    නම් (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        නම් (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ආපසු true;
        }
    }

    // Oh well, just give the entire display bounds.
    ආපසු SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    නම් (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ආපසු display->natural_orientation;
    } නැතහොත් {
        // Default to landscape if the driver hasn't set it
        ආපසු SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    නම් (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ආපසු display->current_orientation;
    } නැතහොත් {
        // Default to landscape if the driver hasn't set it
        ආපසු SDL_ORIENTATION_LANDSCAPE;
    }
}

void SDL_SetDisplayContentScale(SDL_VideoDisplay *display, float scale)
{
    නම් (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        සඳහා (window = _this->windows; window; window = window->next) {
            නම් (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

float SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ආපසු display->content_scale;
}

void SDL_SetWindowHDRProperties(SDL_Window *window, const SDL_HDROutputProperties *HDR, bool send_event)
{
    const SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    නම් (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        නම් (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

void SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, const SDL_HDROutputProperties *HDR)
{
    const SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    const bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	නම් (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    නම් (changed && !SDL_DriverSendsHDRChanges(_this)) {
        සඳහා (SDL_Window *w = display->device->windows; w; w = w->next) {
            නම් (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

static void SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    නම් (display->num_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
static const SDL_DisplayMode *SDL_GetFullscreenModeMatch(const SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    නම් (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ආපසු NULL;
    }

    SDL_memcpy(&fullscreen_mode, mode, parimaa_na(fullscreen_mode));
    නම් (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = NULL;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    නම් (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        නම් (!mode) {
            සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < display->num_fullscreen_modes; ++i) {
                නම් (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], parimaa_na(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }

        // Search for a mode with the same characteristics
        නම් (!mode) {
            සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < display->num_fullscreen_modes; ++i) {
                නම් (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }
    }
    ආපසු mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    පූර්ණ_සංඛ්‍යා i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, parimaa_na(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->num_fullscreen_modes;
    සඳහා (i = 0; i < nmodes; ++i) {
        නම් (cmpmodes(&new_mode, &modes[i]) == 0) {
            ආපසු false;
        }
    }

    // Go ahead and add the new mode
    නම් (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * parimaa_na(*modes));
        නම් (!modes) {
            ආපසු false;
        }

        නම් (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * parimaa_na(*modes));
            සඳහා (i = 0; i < nmodes; ++i) {
                නම් (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->num_fullscreen_modes++], &new_mode, parimaa_na(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->num_fullscreen_modes,
              parimaa_na(SDL_DisplayMode), cmpmodes);

    ආපසු true;
}

void SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    පූර්ණ_සංඛ්‍යා i;

    සඳහා (i = display->num_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = NULL;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = NULL;
    display->num_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, පූර්ණ_සංඛ්‍යා *count)
{
    පූර්ණ_සංඛ්‍යා i;
    පූර්ණ_සංඛ්‍යා num_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    නම් (count) {
        *count = 0;
    }

    CHECK_DISPLAY_MAGIC(display, NULL);

    SDL_UpdateFullscreenDisplayModes(display);

    num_modes = display->num_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((num_modes + 1) * parimaa_na(*result) + num_modes * parimaa_na(**result));
    නම් (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((num_modes + 1) * parimaa_na(*result)));
        නම් (num_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, num_modes * parimaa_na(*modes));
        }
        සඳහා (i = 0; i < num_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = NULL;

        නම් (count) {
            *count = num_modes;
        }
    } නැතහොත් {
        නම් (count) {
            *count = 0;
        }
    }
    ආපසු result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, පූර්ණ_සංඛ්‍යා w, පූර්ණ_සංඛ්‍යා h, float refresh_rate, bool include_high_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        ආපසු SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    const SDL_DisplayMode *mode, *closest = NULL;
    float aspect_ratio;
    පූර්ණ_සංඛ්‍යා i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    නම් (h > 0) {
        aspect_ratio = (float)w / h;
    } නැතහොත් {
        aspect_ratio = 1.0f;
    }

    නම් (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    සඳහා (i = 0; i < display->num_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        නම් (w > mode->w) {
            // Out of sorted modes large enough here
            bha_nga;
        }
        නම් (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            continue;
        }
        නම් (mode->pixel_density > 1.0f && !include_high_density_modes) {
            continue;
        }
        නම් (closest) {
            float current_aspect_ratio = (float)mode->w / mode->h;
            float closest_aspect_ratio = (float)closest->w / closest->h;
            නම් (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                continue;
            }

            නම් (mode->w == closest->w && mode->h == closest->h) {
                නම් (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    continue;
                }
                නම් (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    continue;
                }
            }
        }

        closest = mode;
    }
    නම් (!closest) {
        ආපසු SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    ආපසු true;
}

static bool DisplayModeChanged(const SDL_DisplayMode *old_mode, const SDL_DisplayMode *new_mode)
{
    ආපසු ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

void SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    නම් (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ආපසු;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    නම් (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        නම් (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

const SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ආපසු &display->desktop_mode;
}

void SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    නම් (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } නැතහොත් {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    නම් (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

const SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ආපසු display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    නම් (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ආපසු true;
    }

    නම් (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    නම් (mode == display->current_mode) {
        ආපසු true;
    }
#endif

    // Actually change the display mode
    නම් (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        නම් (!result) {
            ආපසු false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ආපසු true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
static void SDL_GetClosestPointOnRect(const SDL_Rect *rect, SDL_Point *point)
{
    const පූර්ණ_සංඛ්‍යා right = rect->x + rect->w - 1;
    const පූර්ණ_සංඛ්‍යා bottom = rect->y + rect->h - 1;

    නම් (point->x < rect->x) {
        point->x = rect->x;
    } නැතහොත් නම් (point->x > right) {
        point->x = right;
    }

    නම් (point->y < rect->y) {
        point->y = rect->y;
    } නැතහොත් නම් (point->y > bottom) {
        point->y = bottom;
    }
}

static SDL_DisplayID GetDisplayForRect(පූර්ණ_සංඛ්‍යා x, පූර්ණ_සංඛ්‍යා y, පූර්ණ_සංඛ්‍යා w, පූර්ණ_සංඛ්‍යා h)
{
    පූර්ණ_සංඛ්‍යා i, dist;
    SDL_DisplayID closest = 0;
    පූර්ණ_සංඛ්‍යා closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    නම් (_this) {
        සඳහා (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            නම් (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, NULL)) {
                ආපසු display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            නම් (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    නම් (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    ආපසු closest;
}

void SDL_RelativeToGlobalForWindow(SDL_Window *window, පූර්ණ_සංඛ්‍යා rel_x, පූර්ණ_සංඛ්‍යා rel_y, පූර්ණ_සංඛ්‍යා *abs_x, පූර්ණ_සංඛ්‍යා *abs_y)
{
    SDL_Window *w;

    නම් (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        සඳහා (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            නම් (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    නම් (abs_x) {
        *abs_x = rel_x;
    }
    නම් (abs_y) {
        *abs_y = rel_y;
    }
}

void SDL_GlobalToRelativeForWindow(SDL_Window *window, පූර්ණ_සංඛ්‍යා abs_x, පූර්ණ_සංඛ්‍යා abs_y, පූර්ණ_සංඛ්‍යා *rel_x, පූර්ණ_සංඛ්‍යා *rel_y)
{
    SDL_Window *w;

    නම් (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        සඳහා (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            නම් (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    නම් (rel_x) {
        *rel_x = abs_x;
    }
    නම් (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(const SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ආපසු 0;
    }

    ආපසු GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(const SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ආපසු 0;
    }

    ආපසු GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

static SDL_DisplayID GetDisplayAtOrigin(පූර්ණ_සංඛ්‍යා x, පූර්ණ_සංඛ්‍යා y)
{
    සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < _this->num_displays; ++i) {
        SDL_Rect rect;
        const SDL_DisplayID cur_id = _this->displays[i]->id;
        නම් (SDL_GetDisplayBounds(cur_id, &rect)) {
            නම් (x == rect.x && y == rect.y) {
                ආපසු cur_id;
            }
        }
    }

    ආපසු 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    පූර්ණ_සංඛ්‍යා x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    නම් (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    නම් (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        නම් (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } නැතහොත් {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    නම් (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ආපසු displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, NULL);

    // An explicit fullscreen display overrides all
    නම් (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    නම් (!displayID) {
        displayID = window->pending_displayID;
    }
    නම් (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        const පූර්ණ_සංඛ්‍යා x = window->last_position_pending ? window->pending.x : window->x;
        const පූර්ණ_සංඛ්‍යා y = window->last_position_pending ? window->pending.y : window->y;
        const පූර්ණ_සංඛ්‍යා w = window->last_size_pending ? window->pending.w : window->w;
        const පූර්ණ_සංඛ්‍යා h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        නම් (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    නම් (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ආපසු SDL_GetVideoDisplay(displayID);
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
    නම් (fs_display) {
        SDL_SetNumberProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } නැතහොත් {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ආපසු GetDisplayForWindow(window);
}

static void SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    නම් (SDL_SendsDisplayChanges(_this)) {
        ආපසු;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    නම් (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        නම් (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            නම් (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                පූර්ණ_සංඛ්‍යා old_area = old_overlap.w * old_overlap.h;
                පූර්ණ_සංඛ්‍යා new_area = new_overlap.w * new_overlap.h;
                float new_overlap_ratio = (new_area / ((float)old_area + new_area));
                නම් (new_overlap_ratio < 0.80) {
                    ආපසු;
                }
            }
        }
    }

    නම් (displayID != window->displayID) {
        පූර්ණ_සංඛ්‍යා i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        සඳහා (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            නම් (display->fullscreen_window == window) {
                නම් (display_index != i) {
                    නම් (display_index < 0) {
                        display_index = i;
                    } නැතහොත් {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        නම් (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = NULL;
                    }
                }
                bha_nga;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (පූර්ණ_සංඛ්‍යා)displayID, 0);
    }
}

float SDL_GetWindowPixelDensity(SDL_Window *window)
{
    පූර්ණ_සංඛ්‍යා window_w, window_h, pixel_w, pixel_h;
    float pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    නම් (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (float)pixel_w / window_w;
    }
    ආපසු pixel_density;
}

float SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ආපසු window->display_scale;
}

static void SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    float display_scale;

    නම් (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } නැතහොත් {
        const float pixel_density = SDL_GetWindowPixelDensity(window);
        const float content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    නම් (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = NULL;
    SDL_DisplayMode *mode = NULL;
    පූර්ණ_සංඛ්‍යා i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    නම් (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    නම් (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        නම් (!display) {
            // This should never happen, but it did...
            goto done;
        }
    } නැතහොත් {
        සඳහා (i = 0; i < _this->num_displays; ++i) {
            display = _this->displays[i];
            නම් (display->fullscreen_window == window) {
                bha_nga;
            }
        }
        නම් (!display || i == _this->num_displays) {
            // Already not fullscreen on any display
            display = NULL;
        }
    }

    නම් (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        නම් (mode) {
            window->fullscreen_exclusive = true;
        } නැතහොත් {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#නම් defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    නම් (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        නම් (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            නම් (display) {
                display->fullscreen_window = NULL;
            }
            goto done;
        }
        නම් (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            නම් (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                නම් (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    goto error;
                }
            } නැතහොත් නම් (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                සඳහා (i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    නම් (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, NULL);
                        නම් (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = NULL;
                    }
                }
            }

            නම් (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                goto done;
            }
        }
    }
#endif

    නම් (display) {
        // Restore the video mode on other displays if needed
        සඳහා (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            නම් (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, NULL);
                other->fullscreen_window = NULL;
            }
        }
    }

    නම් (fullscreen) {
        පූර්ණ_සංඛ්‍යා mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        නම් (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        නම් (!SDL_SetDisplayModeForDisplay(display, mode)) {
            goto error;
        }
        නම් (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            නම් (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } නැතහොත් {
                resized = true;
            }

            නම් (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                නම් (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } නැතහොත් නම් (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                goto error;
            }
        }

        නම් (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            නම් (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                නම් (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } නැතහොත් {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                නම් (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                නම් (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } නැතහොත් {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } නැතහොත් {
        bool resized = false;

        // Restore the desktop mode
        නම් (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, NULL);
        }
        නම් (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            නම් (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                නම් (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } නැතහොත් {
                resized = true;
            }

            නම් (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                නම් (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } නැතහොත් නම් (ret == SDL_FULLSCREEN_FAILED) {
                goto error;
            }
        }

        නම් (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            නම් (display) {
                display->fullscreen_window = NULL;
            }

            නම් (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                නම් (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } නැතහොත් {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    ආපසු true;

error:
    නම් (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ආපසු false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, const SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (mode) {
        නම් (!SDL_GetFullscreenModeMatch(mode)) {
            ආපසු SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } නැතහොත් {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#නම් defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    නම් (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    නම් (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    ආපසු true;
}

const SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);
    CHECK_WINDOW_NOT_POPUP(window, NULL);

    නම් (window->flags & SDL_WINDOW_FULLSCREEN) {
        ආපසු SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } නැතහොත් {
        ආපසු SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

void *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    නම් (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ආපසු NULL;
    }
    ආපසු _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    const SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    නම් (mode) {
        ආපසු mode->format;
    } නැතහොත් {
        ආපසු SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

static SDL_INLINE bool IsAcceptingDragAndDrop(void)
{
    නම් (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ආපසු true;
    }
    ආපසු false;
}

// prepare a newly-created window
static SDL_INLINE void PrepareDragAndDropSupport(SDL_Window *window)
{
    නම් (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
void SDL_ToggleDragAndDropSupport(void)
{
    නම් (_this && _this->AcceptDragAndDrop) {
        const bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        සඳහා (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(පූර්ණ_සංඛ්‍යා *count)
{
    නම් (count) {
        *count = 0;
    }

    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }

    SDL_Window *window;
    පූර්ණ_සංඛ්‍යා num_added = 0;
    පූර්ණ_සංඛ්‍යා num_windows = 0;
    සඳහා (window = _this->windows; window; window = window->next) {
        ++num_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((num_windows + 1) * parimaa_na(*windows));
    නම් (!windows) {
        ආපසු NULL;
    }

    සඳහා (window = _this->windows; window; window = window->next) {
        windows[num_added++] = window;
        නම් (num_added == num_windows) {
            // Race condition? Multi-threading not supported, ignore it
            bha_nga;
        }
    }
    windows[num_added] = NULL;

    නම් (count) {
        *count = num_added;
    }
    ආපසු windows;
}

static void ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    නම් (!SDL_WINDOW_IS_POPUP(window)) {
        නම් (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        නම් (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        නම් (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        නම් (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        නම් (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        නම් (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

static void SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    නම් (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } නැතහොත් {
        ApplyWindowFlags(window, flags);
        නම් (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#නම් defined(SDL_PLATFORM_LINUX)
    නම් (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_SetWindowProgressValue(window, 0.0f);
    }
#endif
}

static bool SDL_ContextNotSupported(const var_na *name)
{
    ආපසු SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

static bool SDL_DllNotSupported(const var_na *name)
{
    ආපසු SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

static sa_nracanaa {
    const var_na *property_name;
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

static SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, 0);

    සඳහා (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        නම් (SDL_WindowFlagProperties[i].invert_value) {
            නම් (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } නැතහොත් {
            නම් (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    ආපසු flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    const var_na *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, NULL);
    පූර්ණ_සංඛ්‍යා x = (පූර්ණ_සංඛ්‍යා)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    පූර්ණ_සංඛ්‍යා y = (පූර්ණ_සංඛ්‍යා)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    පූර්ණ_සංඛ්‍යා w = (පූර්ණ_සංඛ්‍යා)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 0);
    පූර්ණ_සංඛ්‍යා h = (පූර්ණ_සංඛ්‍යා)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, NULL);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    නම් (!_this) {
        // Initialize the video system if needed
        නම් (!SDL_Init(SDL_INIT_VIDEO)) {
            ආපසු NULL;
        }

        // Make clang-tidy happy
        නම් (!_this) {
            ආපසු NULL;
        }
    }

    නම් ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ආපසු NULL;
    }

    නම් ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        නම් (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ආපසු NULL;
        }

        // Tooltip and popup menu window must specify a parent window
        නම් (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ආපසු NULL;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    නම් (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned පූර්ණ_සංඛ්‍යා)type_flags);
        ආපසු NULL;
    }

    // Make sure the display list is up to date for window placement
    නම් (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    නම් (w < 1) {
        w = 1;
    }
    නම් (h < 1) {
        h = 1;
    }

    නම් (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        නම් ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } නැතහොත් නම් ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        නම් (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        නම් (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        නම් (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            නම් (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        නම් (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            නම් (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    නම් (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned පූර්ණ_සංඛ්‍යා)graphics_flags);
        ආපසු NULL;
    }

    // Some platforms have certain graphics backends enabled by default
    නම් (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    නම් (flags & SDL_WINDOW_OPENGL) {
        නම් (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ආපසු NULL;
        }
        නම් (!SDL_GL_LoadLibrary(NULL)) {
            ආපසු NULL;
        }
    }

    නම් (flags & SDL_WINDOW_VULKAN) {
        නම් (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ආපසු NULL;
        }
        නම් (!SDL_Vulkan_LoadLibrary(NULL)) {
            ආපසු NULL;
        }
    }

    නම් (flags & SDL_WINDOW_METAL) {
        නම් (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ආපසු NULL;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, parimaa_na(*window));
    නම් (!window) {
        ආපසු NULL;
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
    නම් (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    නම් (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    නම් (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    නම් (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    නම් (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_PushError();
        SDL_DestroyWindow(window);
        SDL_PopError();
        ආපසු NULL;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#නම් !defined(SDL_PLATFORM_WINDOWS)
    නම් (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    නම් (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ආපසු window;
}

SDL_Window *SDL_CreateWindow(const var_na *title, පූර්ණ_සංඛ්‍යා w, පූර්ණ_සංඛ්‍යා h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    නම් (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ආපසු window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, පූර්ණ_සංඛ්‍යා offset_x, පූර්ණ_සංඛ්‍යා offset_y, පූර්ණ_සංඛ්‍යා w, පූර්ණ_සංඛ්‍යා h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    නම් (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ආපසු NULL;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, offset_x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, offset_y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ආපසු window;
}

static bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    නම් (!_this->ReconfigureWindow) {
        ආපසු false;
    }

    const SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    නම් (graphics_flags & (graphics_flags - 1)) {
        ආපසු SDL_SetError("Conflicting window flags specified");
    }

    නම් ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ආපසු SDL_ContextNotSupported("OpenGL");
    }
    නම් ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ආපසු SDL_ContextNotSupported("Vulkan");
    }
    නම් ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ආපසු SDL_ContextNotSupported("Metal");
    }

    නම් (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        නම් (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ආපසු false;
        }
    } නැතහොත් {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        නම් (!_this->ReconfigureWindow(_this, window, 0)) {
            ආපසු false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        නම් (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        නම් (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    නම් (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(NULL);
        නම් (!loaded_opengl) {
            ආපසු false;
        }
    } නැතහොත් නම් (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(NULL);
        නම් (!loaded_vulkan) {
            ආපසු false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    නම් (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        නම් (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        නම් (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ආපසු false;
    }

    window->flags |= graphics_flags;

    ආපසු true;
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
    නම් (graphics_flags & (graphics_flags - 1)) {
        ආපසු SDL_SetError("Conflicting window flags specified");
    }

    නම් ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ආපසු SDL_ContextNotSupported("OpenGL");
    }
    නම් ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ආපසු SDL_ContextNotSupported("Vulkan");
    }
    නම් ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ආපසු SDL_ContextNotSupported("Metal");
    }

    නම් (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } නැතහොත් {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    නම් (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    නම් (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        const bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    නම් ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        නම් (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } නැතහොත් {
            need_gl_unload = true;
        }
    } නැතහොත් නම් (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    නම් ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        නම් (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } නැතහොත් {
            need_vulkan_unload = true;
        }
    } නැතහොත් නම් (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    නම් (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    නම් (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    නම් (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    නම් (need_gl_load) {
        නම් (!SDL_GL_LoadLibrary(NULL)) {
            ආපසු false;
        }
        loaded_opengl = true;
    }

    නම් (need_vulkan_load) {
        නම් (!SDL_Vulkan_LoadLibrary(NULL)) {
            ආපසු false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    නම් (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        නම් (!_this->CreateSDLWindow(_this, window, 0)) {
            නම් (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            නම් (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            ආපසු false;
        }
    }

    නම් (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    නම් (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    නම් (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    නම් (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    නම් (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    නම් (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    නම් (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ආපසු true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    නම් (!SDL_ReconfigureWindowInternal(window, flags)) {
        ආපසු SDL_RecreateWindow(window, flags);
    }

    ආපසු true;
}

bool SDL_HasWindows(void)
{
    ආපසු _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ආපසු window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    නම් (id) {
        සඳහා (window = _this->windows; window; window = window->next) {
            නම් (window->id == id) {
                ආපසු window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ආපසු NULL;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ආපසු window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    නම් (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ආපසු window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ආපසු window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, const var_na *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (title == window->title) {
        ආපසු true;
    }
    නම් (!title) {
        title = "";
    }
    නම් (window->title && SDL_strcmp(title, window->title) == 0) {
        ආපසු true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    නම් (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ආපසු true;
}

const var_na *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ආපසු window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ආපසු SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    නම් (!window->icon) {
        ආපසු false;
    }

    නම් (!_this->SetWindowIcon) {
        ආපසු SDL_Unsupported();
    }

    ආපසු _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, පූර්ණ_සංඛ්‍යා x, පූර්ණ_සංඛ්‍යා y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    const පූර්ණ_සංඛ්‍යා w = window->last_size_pending ? window->pending.w : window->windowed.w;
    const පූර්ණ_සංඛ්‍යා h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    නම් (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    නම් (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    නම් (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        නම් (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } නැතහොත් නම් (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        නම් (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        නම් (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            නම් (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ආපසු false;
            }
        }
        නම් (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        නම් (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } නැතහොත් {
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
    නම් (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    නම් (_this->SetWindowPosition) {
        const bool result = _this->SetWindowPosition(_this, window);
        නම් (result) {
            SDL_SyncIfRequired(window);
        }
        ආපසු result;
    }

    ආපසු SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, පූර්ණ_සංඛ්‍යා *x, පූර්ණ_සංඛ්‍යා *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#නැතහොත්
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    නම් (use_display_origin) {
        SDL_DisplayID displayID;

        නම් (x) {
            *x = 0;
        }
        නම් (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        නම් (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            නම් (x) {
                *x = bounds.x;
            }
            නම් (y) {
                *y = bounds.y;
            }
        }
    } නැතහොත් {
        const bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        නම් (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        නම් (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ආපසු true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (!_this->SetWindowBordered) {
        ආපසු SDL_Unsupported();
    }

    const bool want = bordered;
    const bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    නම් (want != have) {
        නම් (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } නැතහොත් {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ආපසු true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (!_this->SetWindowResizable) {
        ආපසු SDL_Unsupported();
    }

    const bool want = resizable;
    const bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    නම් (want != have) {
        නම් (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } නැතහොත් {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ආපසු true;
}

bool SDL_SetWindowAlwaysOnTop(SDL_Window *window, bool on_top)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (!_this->SetWindowAlwaysOnTop) {
        ආපසු SDL_Unsupported();
    }

    const bool want = on_top;
    const bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_TOP) != 0);
    නම් (want != have) {
        නම් (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        } නැතහොත් {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_TOP;
        }
        _this->SetWindowAlwaysOnTop(_this, window, want);
    }

    ආපසු true;
}

bool SDL_SetWindowSize(SDL_Window *window, පූර්ණ_සංඛ්‍යා w, පූර්ණ_සංඛ්‍යා h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ආපසු SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ආපසු SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    float new_aspect = w / (float)h;
    නම් (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (පූර්ණ_සංඛ්‍යා)SDL_roundf(h * window->max_aspect);
    } නැතහොත් නම් (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (පූර්ණ_සංඛ්‍යා)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    නම් (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    නම් (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    නම් (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    නම් (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    නම් (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } නැතහොත් {
        ආපසු SDL_Unsupported();
    }
    ආපසු true;
}

bool SDL_GetWindowSize(SDL_Window *window, පූර්ණ_සංඛ්‍යා *w, පූර්ණ_සංඛ්‍යා *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    නම් (w) {
        *w = window->w;
    }
    නම් (h) {
        *h = window->h;
    }
    ආපසු true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, float min_aspect, float max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    නම් (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    පූර්ණ_සංඛ්‍යා w = window->last_size_pending ? window->pending.w : window->floating.w;
    පූර්ණ_සංඛ්‍යා h = window->last_size_pending ? window->pending.h : window->floating.h;
    ආපසු SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, float *min_aspect, float *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    නම් (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ආපසු true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, පූර්ණ_සංඛ්‍යා *top, පූර්ණ_සංඛ්‍යා *left, පූර්ණ_සංඛ්‍යා *bottom, පූර්ණ_සංඛ්‍යා *right)
{
    පූර්ණ_සංඛ්‍යා dummy = 0;

    නම් (!top) {
        top = &dummy;
    }
    නම් (!left) {
        left = &dummy;
    }
    නම් (!right) {
        right = &dummy;
    }
    නම් (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *top = *left = *bottom = *right = 0;

    CHECK_WINDOW_MAGIC(window, false);

    නම් (!_this->GetWindowBordersSize) {
        ආපසු SDL_Unsupported();
    }

    ආපසු _this->GetWindowBordersSize(_this, window, top, left, bottom, right);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, පූර්ණ_සංඛ්‍යා *w, පූර්ණ_සංඛ්‍යා *h)
{
    පූර්ණ_සංඛ්‍යා filter;

    CHECK_WINDOW_MAGIC(window, false);

    නම් (!w) {
        w = &filter;
    }

    නම් (!h) {
        h = &filter;
    }

    නම් (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } නැතහොත් {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        const SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        නම් ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } නැතහොත් {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        නම් (mode) {
            *w = (පූර්ණ_සංඛ්‍යා)SDL_ceilf(*w * mode->pixel_density);
            *h = (පූර්ණ_සංඛ්‍යා)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ආපසු true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, පූර්ණ_සංඛ්‍යා min_w, පූර්ණ_සංඛ්‍යා min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ආපසු SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ආපසු SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ආපසු SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    නම් (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    පූර්ණ_සංඛ්‍යා w = window->last_size_pending ? window->pending.w : window->floating.w;
    පූර්ණ_සංඛ්‍යා h = window->last_size_pending ? window->pending.h : window->floating.h;
    ආපසු SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, පූර්ණ_සංඛ්‍යා *min_w, පූර්ණ_සංඛ්‍යා *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    නම් (min_w) {
        *min_w = window->min_w;
    }
    නම් (min_h) {
        *min_h = window->min_h;
    }
    ආපසු true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, පූර්ණ_සංඛ්‍යා max_w, පූර්ණ_සංඛ්‍යා max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ආපසු SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ආපසු SDL_InvalidParamError("max_h");
    }

    නම් ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ආපසු SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    නම් (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    පූර්ණ_සංඛ්‍යා w = window->last_size_pending ? window->pending.w : window->floating.w;
    පූර්ණ_සංඛ්‍යා h = window->last_size_pending ? window->pending.h : window->floating.h;
    ආපසු SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, පූර්ණ_සංඛ්‍යා *max_w, පූර්ණ_සංඛ්‍යා *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    නම් (max_w) {
        *max_w = window->max_w;
    }
    නම් (max_h) {
        *max_h = window->max_h;
    }
    ආපසු true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ආපසු true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    නම් (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ආපසු true;
    }

    නම් (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } නැතහොත් {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    සඳහා (child = window->first_child; child; child = child->next_sibling) {
        නම් (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            bha_nga;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ආපසු true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ආපසු true;
    }

    // Hide all child windows
    සඳහා (child = window->first_child; child; child = child->next_sibling) {
        නම් (child->flags & SDL_WINDOW_HIDDEN) {
            bha_nga;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    const SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    නම් (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } නැතහොත් {
        SDL_SetMouseFocus(NULL);
        SDL_SetKeyboardFocus(NULL);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ආපසු true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        ආපසු true;
    }
    නම් (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ආපසු true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (!_this->MaximizeWindow) {
        ආපසු SDL_Unsupported();
    }

    නම් (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ආපසු SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ආපසු true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ආපසු true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (!_this->MinimizeWindow) {
        ආපසු SDL_Unsupported();
    }

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ආපසු true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ආපසු true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (!_this->RestoreWindow) {
        ආපසු SDL_Unsupported();
    }

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ආපසු true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ආපසු true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        නම් (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } නැතහොත් {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ආපසු true;
    }

    නම් (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    නම් (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    නම් (result) {
        SDL_SyncIfRequired(window);
    }

    ආපසු result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (_this->SyncWindow) {
        ආපසු _this->SyncWindow(_this, window);
    } නැතහොත් {
        ආපසු true;
    }
}

static bool ShouldAttemptTextureFramebuffer(void)
{
    const var_na *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    නම් (!_this->CreateWindowFramebuffer) {
        ආපසු true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    නම් (hint && *hint) {
        නම් (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } නැතහොත් {
            attempt_texture_framebuffer = true;
        }
    } නැතහොත් {
        නම් (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } නැතහොත් {
            attempt_texture_framebuffer = false;
        }
    }
    ආපසු attempt_texture_framebuffer;
}

static SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    void *pixels = NULL;
    පූර්ණ_සංඛ්‍යා pitch = 0;
    bool created_framebuffer = false;
    පූර්ණ_සංඛ්‍යා w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    නම් (!_this->checked_texture_framebuffer) {
        නම් (ShouldAttemptTextureFramebuffer()) {
            නම් (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } නැතහොත් {
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

    නම් (!created_framebuffer) {
        නම් (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            ආපසු NULL;
        }

        නම් (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ආපසු NULL;
        }
    }

    නම් (window->surface) {
        // We may have gone recursive and already created the surface
        ආපසු window->surface;
    }

    ආපසු SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ආපසු window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    නම් (!window->surface_valid) {
        නම් (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = NULL;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        නම් (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ආපසු window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, පූර්ණ_සංඛ්‍යා vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!_this->SetWindowFramebufferVSync) {
        ආපසු SDL_Unsupported();
    }
    ආපසු _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, පූර්ණ_සංඛ්‍යා *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!_this->GetWindowFramebufferVSync) {
        ආපසු SDL_Unsupported();
    }
    ආපසු _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    ආපසු SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, const SDL_Rect *rects,
                                 පූර්ණ_සංඛ්‍යා numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!window->surface_valid) {
        ආපසු SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ආපසු _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = NULL;
        window->surface_valid = false;
    }

    නම් (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        නම් (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ආපසු true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, float opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    නම් (!_this->SetWindowOpacity) {
        ආපසු SDL_Unsupported();
    }

    නම් (opacity < 0.0f) {
        opacity = 0.0f;
    } නැතහොත් නම් (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    නම් (result) {
        window->opacity = opacity;
    }

    ආපසු result;
}

float SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ආපසු window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    නම් (window == parent) {
        ආපසු SDL_SetError("Cannot set the parent of a window to itself.");
    }

    නම් (!_this->SetWindowParent) {
        ආපසු SDL_Unsupported();
    }

    නම් (window->flags & SDL_WINDOW_MODAL) {
        ආපසු SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    නම් (window->parent == parent) {
        ආපසු true;
    }

    const bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : NULL);

    ආපසු ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (!_this->SetWindowModal) {
        ආපසු SDL_Unsupported();
    }

    නම් (modal) {
        නම් (!window->parent) {
            ආපසු SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } නැතහොත් නම් (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } නැතහොත් {
        ආපසු true; // Already not modal, so nothing to do.
    }

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        ආපසු true;
    }

    ආපසු _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_INPUT_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    අතරතුර (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        නම් (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_INPUT_FOCUS);
        }
    }

    *new_focus = focus;
    ආපසු set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    සඳහා (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    සඳහා (w = current_focus; w != toplevel_parent; w = w->parent) {
        නම් (w == window) {
            found_higher_focus = true;
            bha_nga;
        }
    }

    ආපසු !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (focusable != false); // normalize the flag.
    const bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    නම් ((want != have) && (_this->SetWindowFocusable)) {
        නම් (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } නැතහොත් {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        නම් (!_this->SetWindowFocusable(_this, window, want)) {
            ආපසු false;
        }
    }

    ආපසු true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (fill != false); // normalize the flag.
    const bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    නම් ((want != have) && (_this->SetWindowFillDocument)) {
        නම් (!_this->SetWindowFillDocument(_this, window, want)) {
            ආපසු false;
        } නැතහොත් නම් (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } නැතහොත් {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ආපසු true;
}

void SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    නම් (window->flags & SDL_WINDOW_INPUT_FOCUS) {
        නම් (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } නැතහොත් {
            mouse_grabbed = false;
        }

        නම් (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } නැතහොත් {
            keyboard_grabbed = false;
        }
    } නැතහොත් {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    නම් (mouse_grabbed || keyboard_grabbed) {
        නම් (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            නම් (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            නම් (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } නැතහොත් නම් (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    නම් (_this->SetWindowMouseGrab) {
        නම් (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    නම් (_this->SetWindowKeyboardGrab) {
        නම් (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    නම් (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = NULL;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        නම් (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } නැතහොත් {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        ආපසු true;
    }

    නම් (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ආපසු true;
    }
    නම් (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } නැතහොත් {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    නම් (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ආපසු false;
    }
    ආපසු true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (window->flags & SDL_WINDOW_HIDDEN) {
        නම් (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } නැතහොත් {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        ආපසු true;
    }

    නම් (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ආපසු true;
    }
    නම් (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } නැතහොත් {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    නම් (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ආපසු false;
    }
    ආපසු true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ආපසු window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ආපසු window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(void)
{
    නම් (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ආපසු _this->grabbed_window;
    } නැතහොත් {
        ආපසු NULL;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, const SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!_this->SetWindowMouseRect) {
        ආපසු SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    නම් (!rect) {
        rect = &zero;
    }

    නම් (SDL_memcmp(&window->mouse_rect, rect, parimaa_na(*rect)) == 0) {
        ආපසු true;
    }
    SDL_memcpy(&window->mouse_rect, rect, parimaa_na(*rect));

    ආපසු _this->SetWindowMouseRect(_this, window);
}

const SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    නම් (SDL_RectEmpty(&window->mouse_rect)) {
        ආපසු NULL;
    } නැතහොත් {
        ආපසු &window->mouse_rect;
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

    නම් (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        ආපසු true;
    }

    නම් (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } නැතහොත් {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    නම් (!SDL_UpdateRelativeMouseMode()) {
        නම් (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } නැතහොත් {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        ආපසු false;
    }
    ආපසු true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ආපසු true;
    } නැතහොත් {
        ආපසු false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (_this->FlashWindow) {
        ආපසු _this->FlashWindow(_this, window, operation);
    }

    ආපසු SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ආපසු SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    නම් (_this->ApplyWindowProgress) {
        නම් (!_this->ApplyWindowProgress(_this, window)) {
            ආපසු false;
        }
    }

    ආපසු true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ආපසු window->progress_state;
}

bool SDL_SetWindowProgressValue(SDL_Window *window, float value)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    value = SDL_clamp(value, 0.0f, 1.f);

    window->progress_value = value;

    නම් (_this->ApplyWindowProgress) {
        නම් (!_this->ApplyWindowProgress(_this, window)) {
            ආපසු false;
        }
    }

    ආපසු true;
}

float SDL_GetWindowProgressValue(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ආපසු window->progress_value;
}

void SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

void SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

void SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    නම් (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        const bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        නම් (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_high_density_modes = false;

            නම් (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_high_density_modes = true;
            }
            const bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_high_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            නම් (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } නැතහොත් {
            SDL_zero(window->current_fullscreen_mode);
        }

        නම් (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

void SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

void SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    නම් ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, NULL);
        නම් (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

void SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    පූර්ණ_සංඛ්‍යා pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

void SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

void SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    නම් (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } නැතහොත් {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

static void SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_left;
    rect.y = window->safe_inset_top;
    rect.w = window->w - (window->safe_inset_right + window->safe_inset_left);
    rect.h = window->h - (window->safe_inset_top + window->safe_inset_bottom);
    නම් (SDL_memcmp(&rect, &window->safe_rect, parimaa_na(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

void SDL_SetWindowSafeAreaInsets(SDL_Window *window, පූර්ණ_සංඛ්‍යා left, පූර්ණ_සංඛ්‍යා right, පූර්ණ_සංඛ්‍යා top, පූර්ණ_සංඛ්‍යා bottom)
{
    window->safe_inset_left = left;
    window->safe_inset_right = right;
    window->safe_inset_top = top;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    නම් (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    නම් (rect) {
        නම් (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } නැතහොත් {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    ආපසු true;
}

void SDL_OnWindowMinimized(SDL_Window *window)
{
    නම් (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

void SDL_OnWindowMaximized(SDL_Window *window)
{
}

void SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    නම් (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

void SDL_OnWindowEnter(SDL_Window *window)
{
    නම් (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

void SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

void SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    නම් (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

static bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    const var_na *hint;

    නම් (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ආපසු false;
    }

#නම් defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    නම් (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        නම් (Cocoa_IsShowingModalDialog(window)) {
            ආපසු false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } නැතහොත් නම් (Cocoa_IsWindowInFullscreenSpace(window)) {
            ආපසු false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        extern bool Android_JNI_ShouldMinimizeOnFocusLoss(void);
        නම් (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ආපසු false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    නම් (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        නම් (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ආපසු true;
        } නැතහොත් {
            ආපසු false;
        }
    }
    ආපසු SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

void SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    නම් (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(void)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    නම් (focus) {
        // Get the toplevel parent window.
        අතරතුර (focus->parent) {
            focus = focus->parent;
        }
    }

    ආපසු focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->num_renderers + 1) * parimaa_na(*renderers));
    නම් (!renderers) {
        ආපසු false;
    }

    window->renderers = renderers;
    window->renderers[window->num_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ආපසු true;
}

void SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < window->num_renderers; ++i) {
        නම් (window->renderers[i] == renderer) {
            නම් (i < (window->num_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->num_renderers - i - 1) * parimaa_na(window->renderers[i]));
            }
            --window->num_renderers;
            bha_nga;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    නම් (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, NULL) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

void SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    අතරතුර (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    නම් (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    නම් (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_input_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    නම් (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < _this->num_displays; ++i) {
        නම් (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = NULL;
        }
    }

    // Make sure this window no longer has focus
    නම් (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(NULL);
    }
    නම් ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    නම් (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(NULL);
    }

    // Make no context current if this is the current context window
    නම් (window->flags & SDL_WINDOW_OPENGL) {
        නම් (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, NULL);
        }
    }

    නම් (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    නම් (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    නම් (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    නම් (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    නම් (_this->current_glwin == window) {
        _this->current_glwin = NULL;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, NULL);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, NULL);

    // Unlink the window from the global window list
    නම් (window->next) {
        window->next->prev = window->prev;
    }
    නම් (window->prev) {
        window->prev->next = window->next;
    } නැතහොත් {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(void)
{
    නම් (!_this) {
        ආපසු true;
    }
    ආපසු !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(void)
{
    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    }
    නම් (!_this->suspend_screensaver) {
        ආපසු true;
    }
    _this->suspend_screensaver = false;
    නම් (_this->SuspendScreenSaver) {
        ආපසු _this->SuspendScreenSaver(_this);
    }

    ආපසු SDL_Unsupported();
}

bool SDL_DisableScreenSaver(void)
{
    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    }
    නම් (_this->suspend_screensaver) {
        ආපසු true;
    }
    _this->suspend_screensaver = true;
    නම් (_this->SuspendScreenSaver) {
        ආපසු _this->SuspendScreenSaver(_this);
    }

    ආපසු SDL_Unsupported();
}

void SDL_QuitVideo(void)
{
    පූර්ණ_සංඛ්‍යා i;

    නම් (!_this) {
        ආපසු;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#නම් 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    අතරතුර (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    නම් (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    නම් (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    සඳහා (i = _this->num_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->num_displays == 0);
    SDL_free(_this->displays);
    _this->displays = NULL;

    SDL_CancelClipboardData(0);

    නම් (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = NULL;
    }
    _this->free(_this);
    _this = NULL;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(const var_na *path)
{
    bool result;

    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    }
    නම් (_this->gl_config.driver_loaded) {
        නම් (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ආපසු SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } නැතහොත් {
        නම් (!_this->GL_LoadLibrary) {
            ආපසු SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    නම් (result) {
        ++_this->gl_config.driver_loaded;
    } නැතහොත් {
        නම් (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ආපසු result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(const var_na *proc)
{
    SDL_FunctionPointer func;

    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    func = NULL;
    නම් (_this->GL_GetProcAddress) {
        නම් (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } නැතහොත් {
            SDL_SetError("No GL driver has been loaded");
        }
    } නැතහොත් {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ආපසු func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(const var_na *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    func = NULL;

    නම් (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } නැතහොත් {
        SDL_SetError("No EGL library has been loaded");
    }

    ආපසු func;
#නැතහොත්
    SDL_SetError("SDL was not built with EGL support");
    ආපසු NULL;
#endif
}

void SDL_GL_UnloadLibrary(void)
{
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු;
    }
    නම් (_this->gl_config.driver_loaded > 0) {
        නම් (--_this->gl_config.driver_loaded > 0) {
            ආපසු;
        }
        නම් (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#නම් defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
typedef GLenum (APIENTRY* PFNGLGETERRORPROC) (void);
typedef void (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

static SDL_INLINE bool isAtLeastGL3(const var_na *verstr)
{
    ආපසු verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(const var_na *extension)
{
#නම් defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    const var_na *extensions;
    const var_na *start;
    const var_na *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    නම් (where || *extension == '\0') {
        ආපසු false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    නම් (start && *start == '0') {
        ආපසු false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    නම් (!glGetStringFunc) {
        ආපසු false;
    }

    නම් (isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint num_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        නම් ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ආපසු false;
        }

#ifndef GL_NUM_EXTENSIONS
#define GL_NUM_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_NUM_EXTENSIONS, &num_exts);
        සඳහා (i = 0; i < num_exts; i++) {
            const var_na *thisext = (const var_na *)glGetStringiFunc(GL_EXTENSIONS, i);
            නම් (SDL_strcmp(thisext, extension) == 0) {
                ආපසු true;
            }
        }

        ආපසු false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (const var_na *)glGetStringFunc(GL_EXTENSIONS);
    නම් (!extensions) {
        ආපසු false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    සඳහා (;;) {
        where = SDL_strstr(start, extension);
        නම් (!where) {
            bha_nga;
        }

        terminator = where + SDL_strlen(extension);
        නම් (where == extensions || *(where - 1) == ' ') {
            නම් (*terminator == ' ' || *terminator == '\0') {
                ආපසු true;
            }
        }

        start = terminator;
    }
    ආපසු false;
#නැතහොත්
    ආපසු false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
void SDL_GL_DeduceMaxSupportedESProfile(පූර්ණ_සංඛ්‍යා *major, පූර්ණ_සංඛ්‍යා *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#නම් defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    නම් (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } නැතහොත් නම් (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } නැතහොත් නම් (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } නැතහොත් {
        *major = 2;
        *minor = 0;
    }
#endif
}

void SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   void *userdata)
{
    නම් (!_this) {
        ආපසු;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

void SDL_GL_ResetAttributes(void)
{
    නම් (!_this) {
        ආපසු;
    }

    _this->egl_platformattrib_callback = NULL;
    _this->egl_surfaceattrib_callback = NULL;
    _this->egl_contextattrib_callback = NULL;
    _this->egl_attrib_callback_userdata = NULL;

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
#elif defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#elif defined(SDL_VIDEO_OPENGL_ES)
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

    නම් (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, පූර්ණ_සංඛ්‍යා value)
{
#නම් defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    }
    result = true;
    switch (attr) {
    pak_sa SDL_GL_RED_SIZE:
        _this->gl_config.red_size = value;
        bha_nga;
    pak_sa SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = value;
        bha_nga;
    pak_sa SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = value;
        bha_nga;
    pak_sa SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = value;
        bha_nga;
    pak_sa SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = value;
        bha_nga;
    pak_sa SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = value;
        bha_nga;
    pak_sa SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = value;
        bha_nga;
    pak_sa SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = value;
        bha_nga;
    pak_sa SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = value;
        bha_nga;
    pak_sa SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = value;
        bha_nga;
    pak_sa SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = value;
        bha_nga;
    pak_sa SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = value;
        bha_nga;
    pak_sa SDL_GL_STEREO:
        _this->gl_config.stereo = value;
        bha_nga;
    pak_sa SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = value;
        bha_nga;
    pak_sa SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = value;
        bha_nga;
    pak_sa SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = value;
        bha_nga;
    pak_sa SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = value;
        bha_nga;
    pak_sa SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_FLAGS:
        නම් (value & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", value);
            bha_nga;
        }
        _this->gl_config.flags = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
        නම් (value != 0 &&
            value != SDL_GL_CONTEXT_PROFILE_CORE &&
            value != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            value != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", value);
            bha_nga;
        }
        _this->gl_config.profile_mask = value;
        bha_nga;
    pak_sa SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = value;
        bha_nga;
    pak_sa SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = value;
        bha_nga;
    pak_sa SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = value;
        bha_nga;
    default:
        result = SDL_SetError("Unknown OpenGL attribute");
        bha_nga;
    }
    ආපසු result;
#නැතහොත්
    ආපසු SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, පූර්ණ_සංඛ්‍යා *value)
{
#නම් defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
        ආපසු SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *value = 0;

    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    }

    switch (attr) {
    pak_sa SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        bha_nga;
    pak_sa SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        bha_nga;
    pak_sa SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        bha_nga;
    pak_sa SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        bha_nga;
    pak_sa SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        bha_nga;
#නැතහොත්
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *value = _this->gl_config.double_buffer;
        ආපසු true;
#endif
    pak_sa SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        bha_nga;
    pak_sa SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        bha_nga;
#ifdef SDL_VIDEO_OPENGL
    pak_sa SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        bha_nga;
    pak_sa SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        bha_nga;
    pak_sa SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        bha_nga;
    pak_sa SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        bha_nga;
    pak_sa SDL_GL_STEREO:
        attrib = GL_STEREO;
        bha_nga;
#නැතහොත්
    pak_sa SDL_GL_ACCUM_RED_SIZE:
    pak_sa SDL_GL_ACCUM_GREEN_SIZE:
    pak_sa SDL_GL_ACCUM_BLUE_SIZE:
    pak_sa SDL_GL_ACCUM_ALPHA_SIZE:
    pak_sa SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *value = 0;
        ආපසු true;
#endif
    pak_sa SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        bha_nga;
    pak_sa SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        bha_nga;
    pak_sa SDL_GL_BUFFER_SIZE:
    {
        පූර්ණ_සංඛ්‍යා rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        නම් (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            ආපසු false;
        }
        නම් (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            ආපසු false;
        }
        නම් (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            ආපසු false;
        }
        නම් (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            ආපසු false;
        }

        *value = rsize + gsize + bsize + asize;
        ආපසු true;
    }
    pak_sa SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *value = (_this->gl_config.accelerated != 0);
        ආපසු true;
    }
    pak_sa SDL_GL_RETAINED_BACKING:
    {
        *value = _this->gl_config.retained_backing;
        ආපසු true;
    }
    pak_sa SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *value = _this->gl_config.major_version;
        ආපසු true;
    }
    pak_sa SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *value = _this->gl_config.minor_version;
        ආපසු true;
    }
    pak_sa SDL_GL_CONTEXT_FLAGS:
    {
        *value = _this->gl_config.flags;
        ආපසු true;
    }
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *value = _this->gl_config.profile_mask;
        ආපසු true;
    }
    pak_sa SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *value = _this->gl_config.share_with_current_context;
        ආපසු true;
    }
    pak_sa SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *value = _this->gl_config.framebuffer_srgb_capable;
        ආපසු true;
    }
    pak_sa SDL_GL_CONTEXT_NO_ERROR:
    {
        *value = _this->gl_config.no_error;
        ආපසු true;
    }
    pak_sa SDL_GL_EGL_PLATFORM:
    {
        *value = _this->gl_config.egl_platform;
        ආපසු true;
    }
    pak_sa SDL_GL_FLOATBUFFERS:
    {
        නම් (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            bha_nga;
        } නැතහොත් {
            ආපසු 0;
        }
    }
    default:
        ආපසු SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    නම් (!glGetStringFunc) {
        ආපසු false;
    }

    නම් (attachmentattrib && isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        නම් (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        නම් (glGetFramebufferAttachmentParameterivFunc) {
            නම් (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            නම් (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            නම් (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)value);
            } නැතහොත් {
                *value = 0;
            }
            නම් (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } නැතහොත් {
            ආපසු false;
        }
    } නැතහොත්
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        නම් (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)value);
        } නැතහොත් {
            ආපසු false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    නම් (!glGetErrorFunc) {
        ආපසු false;
    }

    error = glGetErrorFunc();
    නම් (error != GL_NO_ERROR) {
        නම් (error == GL_INVALID_ENUM) {
            ආපසු SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } නැතහොත් නම් (error == GL_INVALID_VALUE) {
            ආපසු SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ආපසු SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    නම් (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *value = (*value == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ආපසු true;
#නැතහොත්
    ආපසු SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = NULL;
    CHECK_WINDOW_MAGIC(window, NULL);

    නම් (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ආපසු NULL;
    }

#නම් defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    පූර්ණ_සංඛ්‍යා srgb_requested = -1;
    const var_na *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    නම් (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    නම් (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, NULL);
    }

#නම් defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    නම් (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        නම් (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            නම් (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } නැතහොත් {
                supported = isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            නම් (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ආපසු ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    }

    නම් (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ආපසු true;
    }

    නම් (!context) {
        window = NULL;
    } නැතහොත් නම් (window) {
        CHECK_WINDOW_MAGIC(window, false);

        නම් (!(window->flags & SDL_WINDOW_OPENGL)) {
            ආපසු SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } නැතහොත් නම් (!_this->gl_allow_no_surface) {
        ආපසු SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    නම් (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, context, NULL);
    }
    ආපසු result;
}

SDL_Window *SDL_GL_GetCurrentWindow(void)
{
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    ආපසු (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(void)
{
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    ආපසු (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු EGL_NO_DISPLAY;
    }
    නම් (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ආපසු EGL_NO_DISPLAY;
    }
    ආපසු _this->egl_data->egl_display;
#නැතහොත්
    SDL_SetError("SDL was not built with EGL support");
    ආපසු NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    නම් (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ආපසු NULL;
    }
    ආපසු _this->egl_data->egl_config;
#නැතහොත්
    SDL_SetError("SDL was not built with EGL support");
    ආපසු NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    නම් (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ආපසු NULL;
    }
    නම් (_this->GL_GetEGLSurface) {
        ආපසු _this->GL_GetEGLSurface(_this, window);
    }
    ආපසු NULL;
#නැතහොත්
    SDL_SetError("SDL was not built with EGL support");
    ආපසු NULL;
#endif
}

bool SDL_GL_SetSwapInterval(පූර්ණ_සංඛ්‍යා interval)
{
    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    } නැතහොත් නම් (SDL_GL_GetCurrentContext() == NULL) {
        ආපසු SDL_SetError("No OpenGL context has been made current");
    } නැතහොත් නම් (_this->GL_SetSwapInterval) {
        ආපසු _this->GL_SetSwapInterval(_this, interval);
    } නැතහොත් {
        ආපසු SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(පූර්ණ_සංඛ්‍යා *interval)
{
    CHECK_PARAM(!interval) {
       ආපසු SDL_InvalidParamError("interval");
    }

    *interval = 0;

    නම් (!_this) {
        ආපසු SDL_SetError("no video driver");
    } නැතහොත් නම් (SDL_GL_GetCurrentContext() == NULL) {
        ආපසු SDL_SetError("no current context");
    } නැතහොත් නම් (_this->GL_GetSwapInterval) {
        ආපසු _this->GL_GetSwapInterval(_this, interval);
    } නැතහොත් {
        ආපසු SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!(window->flags & SDL_WINDOW_OPENGL)) {
        ආපසු SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    නම් (SDL_GL_GetCurrentWindow() != window) {
        ආපසු SDL_SetError("The specified window has not been made current");
    }

    ආපසු _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ආපසු SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ආපසු SDL_InvalidParamError("context");
    }

    නම් (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(NULL, NULL);
    }

    ආපසු _this->GL_DestroyContext(_this, context);
}

#නම් 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
static void CreateMaskFromColorKeyOrAlpha(SDL_Surface *icon, Uint8 *mask, පූර්ණ_සංඛ්‍යා flags)
{
    පූර්ණ_සංඛ්‍යා x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    switch (SDL_BYTESPERPIXEL(icon->format)) {
    pak_sa 1:
        {
            Uint8 *pixels;
            සඳහා (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                සඳහා (x = 0; x < icon->w; ++x) {
                    නම් (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        bha_nga;

    pak_sa 2:
        {
            Uint16 *pixels;
            සඳහා (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                සඳහා (x = 0; x < icon->w; ++x) {
                    නම් ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } නැතහොත් නම් ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        bha_nga;

    pak_sa 4:
        {
            Uint32 *pixels;
            සඳහා (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                සඳහා (x = 0; x < icon->w; ++x) {
                    නම් ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } නැතහොත් නම් ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        bha_nga;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
void SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    නම් (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        නම් (mask == NULL) {
            පූර්ණ_සංඛ්‍යා mask_len = icon->h * (icon->w + 7) / 8;
            පූර්ණ_සංඛ්‍යා flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            නම් (mask == NULL) {
                ආපසු;
            }
            SDL_memset(mask, ~0, mask_len);
            නම් (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            නම් (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            නම් (flags) {
                CreateMaskFromColorKeyOrAlpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } නැතහොත් {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_TextInputType SDL_GetTextInputType(SDL_PropertiesID props)
{
    ආපසු (SDL_TextInputType)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_TYPE_NUMBER, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_GetTextInputCapitalization(SDL_PropertiesID props)
{
    නම් (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER)) {
        ආපසු (SDL_Capitalization)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER, SDL_CAPITALIZE_NONE);
    }

    switch (SDL_GetTextInputType(props)) {
    pak_sa SDL_TEXTINPUT_TYPE_TEXT:
        ආපසු SDL_CAPITALIZE_SENTENCES;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ආපසු SDL_CAPITALIZE_WORDS;
    default:
        ආපසු SDL_CAPITALIZE_NONE;
    }
}

bool SDL_GetTextInputAutocorrect(SDL_PropertiesID props)
{
    ආපසු SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_GetTextInputMultiline(SDL_PropertiesID props)
{
    නම් (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ආපසු SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    නම් (SDL_GetHintBoolean(SDL_HINT_RETURN_KEY_HIDES_IME, false)) {
        ආපසු false;
    } නැතහොත් {
        ආපසු true;
    }
}

static bool AutoShowingScreenKeyboard(void)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    නම් (!hint) {
        // This hint is currently only used by the X11 video driver
        නම් (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    නම් (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ආපසු true;
    } නැතහොත් {
        ආපසු false;
    }
}

bool SDL_StartTextInput(SDL_Window *window)
{
    ආපසු SDL_StartTextInputWithProperties(window, 0);
}

bool SDL_StartTextInputWithProperties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (window->text_input_props) {
        SDL_DestroyProperties(window->text_input_props);
        window->text_input_props = 0;
    }

    නම් (props) {
        window->text_input_props = SDL_CreateProperties();
        නම් (!window->text_input_props) {
            ආපසු false;
        }
        නම් (!SDL_CopyProperties(props, window->text_input_props)) {
            ආපසු false;
        }
    }

    නම් (_this->SetTextInputProperties) {
        _this->SetTextInputProperties(_this, window, props);
    }

    නම් (!window->text_input_active) {
        // Start the text input system
        නම් (_this->StartTextInput) {
            නම් (!_this->StartTextInput(_this, window, props)) {
                ආපසු false;
            }
        }
        window->text_input_active = true;
    }

    // Show the on-screen keyboard, if desired
    නම් (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        නම් (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    ආපසු true;
}

bool SDL_TextInputActive(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ආපසු window->text_input_active;
}

bool SDL_StopTextInput(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (window->text_input_active) {
        // Stop the text input system
        නම් (_this->StopTextInput) {
            _this->StopTextInput(_this, window);
        }
        window->text_input_active = false;
    }

    // Hide the on-screen keyboard, if desired
    නම් (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        නම් (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    ආපසු true;
}

bool SDL_SetTextInputArea(SDL_Window *window, const SDL_Rect *rect, පූර්ණ_සංඛ්‍යා cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (rect) {
        SDL_copyp(&window->text_input_rect, rect);
        window->text_input_cursor = cursor;
    } නැතහොත් {
        SDL_zero(window->text_input_rect);
        window->text_input_cursor = 0;
    }

    නම් (_this && _this->UpdateTextInputArea) {
        නම් (!_this->UpdateTextInputArea(_this, window)) {
            ආපසු false;
        }
    }
    ආපසු true;
}

bool SDL_GetTextInputArea(SDL_Window *window, SDL_Rect *rect, පූර්ණ_සංඛ්‍යා *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (rect) {
        SDL_copyp(rect, &window->text_input_rect);
    }
    නම් (cursor) {
        *cursor = window->text_input_cursor;
    }
    ආපසු true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (_this->ClearComposition) {
        ආපසු _this->ClearComposition(_this, window);
    }
    ආපසු true;
}

bool SDL_HasScreenKeyboardSupport(void)
{
    නම් (_this && _this->HasScreenKeyboardSupport) {
        ආපසු _this->HasScreenKeyboardSupport(_this);
    }
    ආපසු false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ආපසු _this->screen_keyboard_shown;
}

void SDL_SendScreenKeyboardShown(void)
{
    නම් (!_this || _this->screen_keyboard_shown) {
        ආපසු;
    }

    _this->screen_keyboard_shown = true;

    නම් (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

void SDL_SendScreenKeyboardHidden(void)
{
    නම් (!_this || !_this->screen_keyboard_shown) {
        ආපසු;
    }

    _this->screen_keyboard_shown = false;

    නම් (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

පූර්ණ_සංඛ්‍යා SDL_GetMessageBoxCount(void)
{
    ආපසු SDL_GetAtomicInt(&SDL_messagebox_count);
}

bool SDL_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, පූර්ණ_සංඛ්‍යා *buttonID)
{
    පූර්ණ_සංඛ්‍යා dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        ආපසු SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ආපසු SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    var_na *titlecpy = NULL;
    var_na *msgcpy = NULL;
    නම් (messageboxdata->title) {
        const size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(var_na, slen, &titleisstack);
        නම් (!titlecpy) {
            ආපසු false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    නම් (messageboxdata->message) {
        const size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(var_na, slen, &msgisstack);
        නම් (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ආපසු false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (void)SDL_AtomicIncRef(&SDL_messagebox_count);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    නම් (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, parimaa_na(*messageboxdata));
    mbdata.title = titlecpy;
    නම් (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    නම් (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    නම් (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } නැතහොත් {
        // It's completely fine to call this function before video is initialized
        const var_na *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        නම් (driver_name && *driver_name != 0) {
            const var_na *driver_attempt = driver_name;
            අතරතුර (driver_attempt && (*driver_attempt != 0) && !result) {
                const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                සඳහා (පූර්ණ_සංඛ්‍යා i = 0; bootstrap[i]; ++i) {
                    නම් (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        නම් (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        bha_nga;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
            }
        } නැතහොත් {
            සඳහා (පූර්ණ_සංඛ්‍යා i = 0; bootstrap[i]; ++i) {
                නම් (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    bha_nga;
                }
            }
        }
    }

    නම් (!result) {
        const var_na *error = SDL_GetError();

        නම් (!*error) {
            SDL_SetError("No message system available");
        }
    } නැතහොත් {
        SDL_ClearError();
    }

    (void)SDL_AtomicDecRef(&SDL_messagebox_count);

    නම් (current_window) {
        SDL_RaiseWindow(current_window);
    }

    නම් (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ආපසු result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, const var_na *title, const var_na *message, SDL_Window *window)
{
#නම් defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool hasGpuRight;

    // If the video subsystem has not been initialised, set up graphics temporarily
    hasGpuRight = gspHasGpuRight();
    නම් (!hasGpuRight)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    නම් (!hasGpuRight)
        gfxExit();

    ආපසු true;
#නැතහොත්
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

    ආපසු SDL_ShowMessageBox(&data, NULL);
#endif
}

bool SDL_ShouldAllowTopmost(void)
{
    ආපසු SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, පූර්ණ_සංඛ්‍යා x, පූර්ණ_සංඛ්‍යා y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    නම් (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ආපසු true;
    }

    ආපසු SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, void *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!_this->SetWindowHitTest) {
        ආපසු SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    ආපසු _this->SetWindowHitTest(window, callback != NULL);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    නම් (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ආපසු SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    නම් (!props) {
        ආපසු false;
    }

    නම් (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        නම් (!surface) {
            ආපසු false;
        }
    } නැතහොත් {
        surface = NULL;
    }

    නම් (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ආපසු false;
    }

    නම් (_this->UpdateWindowShape) {
        නම් (!_this->UpdateWindowShape(_this, window, surface)) {
            ආපසු false;
        }
    }
    ආපසු true;
}

/*
 * Functions used by iOS application delegates
 */
void SDL_OnApplicationWillTerminate(void)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

void SDL_OnApplicationDidReceiveMemoryWarning(void)
{
    SDL_SendAppEvent(SDL_EVENT_LOW_MEMORY);
}

void SDL_OnApplicationWillEnterBackground(void)
{
    නම් (_this) {
        SDL_Window *window;
        සඳහා (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(NULL);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

void SDL_OnApplicationDidEnterBackground(void)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

void SDL_OnApplicationWillEnterForeground(void)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

void SDL_OnApplicationDidEnterForeground(void)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    නම් (_this) {
        SDL_Window *window;
        සඳහා (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(const var_na *path)
{
    bool result;

    නම් (!_this) {
        ආපසු SDL_UninitializedVideo();
    }
    නම් (_this->vulkan_config.loader_loaded) {
        නම් (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ආපසු SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } නැතහොත් {
        නම් (!_this->Vulkan_LoadLibrary) {
            ආපසු SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    නම් (result) {
        _this->vulkan_config.loader_loaded++;
    }
    ආපසු result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(void)
{
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු NULL;
    }
    නම් (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ආපසු NULL;
    }
    ආපසු (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

void SDL_Vulkan_UnloadLibrary(void)
{
    නම් (!_this) {
        SDL_UninitializedVideo();
        ආපසු;
    }
    නම් (_this->vulkan_config.loader_loaded > 0) {
        නම් (--_this->vulkan_config.loader_loaded > 0) {
            ආපසු;
        }
        නම් (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

var_na const * const *SDL_Vulkan_GetInstanceExtensions(Uint32 *count)
{
    Uint32 tmpcount = 0;
    නම් (!count) {
        count = &tmpcount;
    }

    නම් (!_this->Vulkan_GetInstanceExtensions) {
        *count = 0;
        SDL_Unsupported();
        ආපසු NULL;
    }

    ආපසු _this->Vulkan_GetInstanceExtensions(_this, count);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  const sa_nracanaa VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    නම් (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ආපසු false;
    }

    CHECK_PARAM(!instance) {
        ආපසු SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ආපසු SDL_InvalidParamError("surface");
    }

    නම් (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        නම් (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        නම් (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        නම් (SDL_Vulkan_LoadLibrary(NULL)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } නැතහොත් {
            ආපසු SDL_SetError("failed to load Vulkan library");
        }
    }

    ආපසු _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

void SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               const sa_nracanaa VkAllocationCallbacks *allocator)
{
    නම් (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ආපසු false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ආපසු false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ආපසු false;
    }

    නම් (_this->Vulkan_GetPresentationSupport) {
        ආපසු _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ආපසු true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    නම් (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ආපසු NULL;
    }

    නම් (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        නම් (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        නම් (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    ආපසු _this->Metal_CreateView(_this, window);
}

void SDL_Metal_DestroyView(SDL_MetalView view)
{
    නම් (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

void *SDL_Metal_GetLayer(SDL_MetalView view)
{
    නම් (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ආපසු NULL;
        }
        ආපසු _this->Metal_GetLayer(_this, view);
    } නැතහොත් {
        SDL_SetError("Metal is not supported.");
        ආපසු NULL;
    }
}

#නම් defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
const var_na *SDL_GetCSSCursorName(SDL_SystemCursor id, const var_na **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    switch (id) {
    pak_sa SDL_SYSTEM_CURSOR_DEFAULT:
        ආපසු "default";

    pak_sa SDL_SYSTEM_CURSOR_TEXT:
        ආපසු "text";

    pak_sa SDL_SYSTEM_CURSOR_WAIT:
        ආපසු "wait";

    pak_sa SDL_SYSTEM_CURSOR_CROSSHAIR:
        ආපසු "crosshair";

    pak_sa SDL_SYSTEM_CURSOR_PROGRESS:
        ආපසු "progress";

    pak_sa SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        නම් (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ආපසු "nwse-resize";

    pak_sa SDL_SYSTEM_CURSOR_NESW_RESIZE:
        නම් (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ආපසු "nesw-resize";

    pak_sa SDL_SYSTEM_CURSOR_EW_RESIZE:
        නම් (fallback_name) {
            *fallback_name = "col-resize";
        }
        ආපසු "ew-resize";

    pak_sa SDL_SYSTEM_CURSOR_NS_RESIZE:
        නම් (fallback_name) {
            *fallback_name = "row-resize";
        }
        ආපසු "ns-resize";

    pak_sa SDL_SYSTEM_CURSOR_MOVE:
        නම් (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ආපසු "move";

    pak_sa SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ආපසු "not-allowed";

    pak_sa SDL_SYSTEM_CURSOR_POINTER:
        ආපසු "pointer";

    pak_sa SDL_SYSTEM_CURSOR_NW_RESIZE:
        ආපසු "nw-resize";

    pak_sa SDL_SYSTEM_CURSOR_N_RESIZE:
        ආපසු "n-resize";

    pak_sa SDL_SYSTEM_CURSOR_NE_RESIZE:
        ආපසු "ne-resize";

    pak_sa SDL_SYSTEM_CURSOR_E_RESIZE:
        ආපසු "e-resize";

    pak_sa SDL_SYSTEM_CURSOR_SE_RESIZE:
        ආපසු "se-resize";

    pak_sa SDL_SYSTEM_CURSOR_S_RESIZE:
        ආපසු "s-resize";

    pak_sa SDL_SYSTEM_CURSOR_SW_RESIZE:
        ආපසු "sw-resize";

    pak_sa SDL_SYSTEM_CURSOR_W_RESIZE:
        ආපසු "w-resize";

    pak_sa SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ආපසු "context-menu";

    pak_sa SDL_SYSTEM_CURSOR_HELP:
        ආපසු "help";

    pak_sa SDL_SYSTEM_CURSOR_CELL:
        ආපසු "cell";

    pak_sa SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ආපසු "vertical-text";

    pak_sa SDL_SYSTEM_CURSOR_ALIAS:
        ආපසු "alias";

    pak_sa SDL_SYSTEM_CURSOR_COPY:
        ආපසු "copy";

    pak_sa SDL_SYSTEM_CURSOR_NO_DROP:
        ආපසු "no-drop";

    pak_sa SDL_SYSTEM_CURSOR_GRAB:
        ආපසු "grab";

    pak_sa SDL_SYSTEM_CURSOR_GRABBING:
        ආපසු "grabbing";

    pak_sa SDL_SYSTEM_CURSOR_COL_RESIZE:
        ආපසු "col-resize";

    pak_sa SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ආපසු "row-resize";

    pak_sa SDL_SYSTEM_CURSOR_ALL_SCROLL:
        නම් (fallback_name) {
            *fallback_name = "move";
        }
        ආපසු "all-scroll";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_IN:
        ආපසු "zoom-in";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ආපසු "zoom-out";

    default:
        ආපසු "default";
    }
}
#endif

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

#ᨀᨘ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#include <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ᨀᨘ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
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
        ᨀᨘᨒ result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ᨀᨘᨒ result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        ᨀᨘᨒ result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ᨀᨘᨒ result;                                                  \
    }

#ᨀᨘ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
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
    ᨀᨘ (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ᨀᨘᨒ true;
    }
    ᨀᨘᨒ false;
}

static bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ᨀᨘᨒ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

static bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ᨀᨘᨒ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

static bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ᨀᨘᨒ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

static bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ᨀᨘᨒ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

static bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ᨀᨘᨒ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
static bool syncHint;

static void SDL_SyncHintWatcher(void *userdata, const var_na *name, const var_na *oldValue, const var_na *newValue)
{
    syncHint = SDL_GetStringBoolean(newValue, false);
}

static void SDL_SyncIfRequired(SDL_Window *window)
{
    ᨀᨘ (syncHint) {
        SDL_SyncWindow(window);
    }
}

static void SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    ᨀᨘ (window->parent) {
        ᨀᨘ (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        ᨀᨘ (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } ᨀᨘᨁ {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = NULL;
    }

    ᨀᨘ (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        ᨀᨘ (parent->first_child) {
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
    puur_naa_nka pitch;
    puur_naa_nka bytes_per_pixel;
} SDL_WindowTextureData;

static Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#ᨀᨘ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ᨀᨘ (_this->GL_CreateContext) {
        ᨀᨘᨒ SDL_WINDOW_OPENGL;
    }
#endif
#ᨀᨘ defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ᨀᨘ (_this->Metal_CreateView) {
        ᨀᨘᨒ SDL_WINDOW_METAL;
    }
#endif
#ᨀᨘ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ᨀᨘ (SDL_strcmp(_this->name, "openvr") == 0) {
        ᨀᨘᨒ SDL_WINDOW_OPENGL;
    }
#endif
    ᨀᨘᨒ 0;
}

static bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, void **pixels, puur_naa_nka *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    const bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    puur_naa_nka i;
    puur_naa_nka w, h;
    const SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    ᨀᨘ (!data) {
        SDL_Renderer *renderer = NULL;
        const var_na *render_driver = NULL;

        // See if there's a render driver being requested
        const var_na *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ᨀᨘ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ᨀᨘ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ᨀᨘ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = NULL;
        }

        var_na *render_driver_copy = NULL;
        ᨀᨘ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ᨀᨘ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                var_na *prev = render_driver_copy;
                var_na *ptr = prev;
                ᨀᨛ ((ptr = SDL_strchr(ptr, ',')) != NULL) {
                    *ptr = '\0';
                    const bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ᨀᨘ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } ᨀᨘᨁ {
                        ptr++;
                        prev = ptr;
                    }
                }

                ᨀᨘ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ᨀᨘ (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            ᨀᨘ (!renderer) {
                // The error for this specific renderer has already been set
                ᨀᨘᨒ false;
            }
        } ᨀᨘᨁ {
            SDL_assert(render_driver_copy == NULL);
            const puur_naa_nka total = SDL_GetNumRenderDrivers();
            for (i = 0; i < total; ++i) {
                const var_na *name = SDL_GetRenderDriver(i);
                ᨀᨘ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    ᨀᨘ (renderer) {
                        bha_nga; // this will work.
                    }
                }
            }
            ᨀᨘ (!renderer) {
                ᨀᨘᨒ SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != NULL); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, parimaa_na(*data));
        ᨀᨘ (!data) {
            SDL_DestroyRenderer(renderer);
            ᨀᨘᨒ false;
        }
        ᨀᨘ (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            ᨀᨘᨒ false;
        }

        data->renderer = renderer;
    }

    texture_formats = (const SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, NULL);
    ᨀᨘ (!texture_formats) {
        ᨀᨘᨒ false;
    }

    // Free any old texture and pixel data
    ᨀᨘ (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = NULL;
    }
    SDL_free(data->pixels);
    data->pixels = NULL;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    for (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ᨀᨘ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
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
    ᨀᨘ (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ᨀᨘᨒ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        const size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ᨀᨘ (!data->pixels) {
            ᨀᨘᨒ false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, NULL);

    ᨀᨘᨒ true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, puur_naa_nka vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    ᨀᨘ (!data) {
        ᨀᨘᨒ false;
    }
    ᨀᨘ (!data->renderer) {
        ᨀᨘᨒ false;
    }
    ᨀᨘᨒ SDL_SetRenderVSync(data->renderer, vsync);
}

static bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, puur_naa_nka *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    ᨀᨘ (!data) {
        ᨀᨘᨒ false;
    }
    ᨀᨘ (!data->renderer) {
        ᨀᨘᨒ false;
    }
    ᨀᨘᨒ SDL_GetRenderVSync(data->renderer, vsync);
}

static bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects, puur_naa_nka numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    void *src;
    puur_naa_nka w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    ᨀᨘ (!data || !data->texture) {
        ᨀᨘᨒ SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ᨀᨘ (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (void *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        ᨀᨘ (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            ᨀᨘᨒ false;
        }

        ᨀᨘ (!SDL_RenderTexture(data->renderer, data->texture, NULL, NULL)) {
            ᨀᨘᨒ false;
        }

        SDL_RenderPresent(data->renderer);
    }
    ᨀᨘᨒ true;
}

static void SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ᨀᨘ (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);

        ᨀᨘ (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        ᨀᨘ (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

static SDL_VideoDevice *_this = NULL;
static SDL_AtomicInt SDL_messagebox_count;

static puur_naa_nka SDLCALL cmpmodes(const void *A, const void *B)
{
    const SDL_DisplayMode *a = (const SDL_DisplayMode *)A;
    const SDL_DisplayMode *b = (const SDL_DisplayMode *)B;
    puur_naa_nka a_refresh_rate = (puur_naa_nka)(a->refresh_rate * 100);
    puur_naa_nka b_refresh_rate = (puur_naa_nka)(b->refresh_rate * 100);
    puur_naa_nka a_pixel_density = (puur_naa_nka)(a->pixel_density * 100);
    puur_naa_nka b_pixel_density = (puur_naa_nka)(b->pixel_density * 100);

    ᨀᨘ (a->w != b->w) {
        ᨀᨘᨒ b->w - a->w;
    } ᨀᨘᨁ ᨀᨘ (a->h != b->h) {
        ᨀᨘᨒ b->h - a->h;
    } ᨀᨘᨁ ᨀᨘ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ᨀᨘᨒ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ᨀᨘᨁ ᨀᨘ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ᨀᨘᨒ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ᨀᨘᨁ ᨀᨘ (a_refresh_rate != b_refresh_rate) {
        ᨀᨘᨒ b_refresh_rate - a_refresh_rate;
    } ᨀᨘᨁ ᨀᨘ (a_pixel_density != b_pixel_density) {
        ᨀᨘᨒ a_pixel_density - b_pixel_density;
    }
    ᨀᨘᨒ 0;
}

bool SDL_UninitializedVideo(void)
{
    ᨀᨘᨒ SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
static const VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

puur_naa_nka SDL_GetNumVideoDrivers(void)
{
    static puur_naa_nka num_drivers = -1;

    ᨀᨘ (num_drivers >= 0) {
        ᨀᨘᨒ num_drivers;
    }

    num_drivers = 0;

    // Build a list of unique video drivers.
    for (puur_naa_nka i = 0; bootstrap[i] != NULL; ++i) {
        bool duplicate = false;
        for (puur_naa_nka j = 0; j < i; ++j) {
            ᨀᨘ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                bha_nga;
            }
        }

        ᨀᨘ (!duplicate) {
            deduped_bootstrap[num_drivers++] = bootstrap[i];
        }
    }

    ᨀᨘᨒ num_drivers;
}

const var_na *SDL_GetVideoDriver(puur_naa_nka index)
{
    CHECK_PARAM(index < 0 || index >= SDL_GetNumVideoDrivers()) {
        SDL_InvalidParamError("index");
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ deduped_bootstrap[index]->name;
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
    puur_naa_nka i = 0;

    // Check to make sure we don't overwrite '_this'
    ᨀᨘ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ᨀᨘ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        goto pre_driver_error;
    }
    init_events = true;
    ᨀᨘ (!SDL_InitKeyboard()) {
        goto pre_driver_error;
    }
    init_keyboard = true;
    ᨀᨘ (!SDL_PreInitMouse()) {
        goto pre_driver_error;
    }
    init_mouse = true;
    ᨀᨘ (!SDL_InitTouch()) {
        goto pre_driver_error;
    }
    init_touch = true;
    ᨀᨘ (!SDL_InitPen()) {
        goto pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = NULL;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ᨀᨘ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    ᨀᨘ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ᨀᨘ (driver_name && *driver_name != 0) {
        const var_na *driver_attempt = driver_name;
        ᨀᨛ (driver_attempt && *driver_attempt != 0 && !video) {
            const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            for (i = 0; bootstrap[i]; ++i) {
                ᨀᨘ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ᨀᨘ (video) {
                        bha_nga;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
        }
    } ᨀᨘᨁ {
        for (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ᨀᨘ (video) {
                bha_nga;
            }
        }
    }
    ᨀᨘ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ᨀᨘᨁ {
        ᨀᨘ (driver_name) {
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
    ᨀᨘ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ᨀᨘᨒ false;
    }

    // Make sure some displays were added
    ᨀᨘ (_this->num_displays == 0) {
        SDL_QuitVideo();
        ᨀᨘᨒ SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, NULL);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ᨀᨘ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ᨀᨘᨒ true;

pre_driver_error:
    SDL_assert(_this == NULL);
    ᨀᨘ (init_pen) {
        SDL_QuitPen();
    }
    ᨀᨘ (init_touch) {
        SDL_QuitTouch();
    }
    ᨀᨘ (init_mouse) {
        SDL_QuitMouse();
    }
    ᨀᨘ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ᨀᨘ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ᨀᨘᨒ false;
}

const var_na *SDL_GetCurrentVideoDriver(void)
{
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(void)
{
    ᨀᨘᨒ _this;
}

bool SDL_OnVideoThread(void)
{
    ᨀᨘᨒ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

void SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    ᨀᨘ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(void)
{
    ᨀᨘ (_this) {
        ᨀᨘᨒ _this->system_theme;
    } ᨀᨘᨁ {
        ᨀᨘᨒ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

void SDL_UpdateDesktopBounds(void)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(NULL);
    ᨀᨘ (displays) {
        for (puur_naa_nka i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ᨀᨘ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ᨀᨘ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ᨀᨘᨁ {
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
    ᨀᨘ (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    ᨀᨘ (mode->refresh_rate_numerator > 0) {
        ᨀᨘ (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (float)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } ᨀᨘᨁ {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(const SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ᨀᨘ (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, parimaa_na(display.desktop_mode));
    }
    ᨀᨘᨒ SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(const SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    puur_naa_nka i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(parimaa_na(*new_display));
    ᨀᨘ (!new_display) {
        ᨀᨘᨒ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->num_displays + 1) * parimaa_na(*displays));
    ᨀᨘ (!displays) {
        SDL_free(new_display);
        ᨀᨘᨒ 0;
    }
    _this->displays = displays;
    _this->displays[_this->num_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ᨀᨘ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ᨀᨘᨁ {
        var_na name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ᨀᨘ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    for (i = 0; i < new_display->num_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    ᨀᨘ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ᨀᨘᨒ id;
}

void SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    for (window = _this->windows; window; window = window->next) {
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
    puur_naa_nka display_index = SDL_GetDisplayIndex(displayID);
    ᨀᨘ (display_index < 0) {
        ᨀᨘᨒ;
    }

    display = _this->displays[display_index];

    ᨀᨘ (send_event) {
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

    ᨀᨘ (display_index < (_this->num_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->num_displays - display_index - 1) * parimaa_na(_this->displays[display_index]));
    }
    --_this->num_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(puur_naa_nka *count)
{
    puur_naa_nka i;
    SDL_DisplayID *displays;

    ᨀᨘ (!_this) {
        ᨀᨘ (count) {
            *count = 0;
        }

        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->num_displays + 1) * parimaa_na(*displays));
    ᨀᨘ (displays) {
        ᨀᨘ (count) {
            *count = _this->num_displays;
        }

        for (i = 0; i < _this->num_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ᨀᨘᨁ {
        ᨀᨘ (count) {
            *count = 0;
        }
    }
    ᨀᨘᨒ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    puur_naa_nka display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    ᨀᨘ (display_index < 0) {
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ _this->displays[display_index];
}

static SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ᨀᨘ (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    ᨀᨘ (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    ᨀᨘᨒ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᨀᨘᨒ SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(void)
{
    ᨀᨘ (!_this || _this->num_displays == 0) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ 0;
    }
    ᨀᨘᨒ _this->displays[0]->id;
}

puur_naa_nka SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    puur_naa_nka display_index;

    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ -1;
    }

    for (display_index = 0; display_index < _this->num_displays; ++display_index) {
        ᨀᨘ (displayID == _this->displays[display_index]->id) {
            ᨀᨘᨒ display_index;
        }
    }
    SDL_SetError("Invalid display");
    ᨀᨘᨒ -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᨀᨘᨒ display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᨀᨘᨒ SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ᨀᨘ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ᨀᨘᨒ display->props;
}

const var_na *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᨀᨘᨒ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ᨀᨘᨒ SDL_InvalidParamError("rect");
    }

    ᨀᨘ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ᨀᨘ (_this->GetDisplayBounds(_this, display, rect)) {
            ᨀᨘᨒ true;
        }
    }

    // Assume that the displays are left to right
    ᨀᨘ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ᨀᨘᨁ {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ᨀᨘᨒ true;
}

static puur_naa_nka ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ᨀᨘᨒ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ᨀᨘᨒ SDL_InvalidParamError("rect");
    }

    ᨀᨘ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ᨀᨘᨒ true;
    }

    ᨀᨘ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ᨀᨘ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ᨀᨘᨒ true;
        }
    }

    // Oh well, just give the entire display bounds.
    ᨀᨘᨒ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ᨀᨘ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ᨀᨘᨒ display->natural_orientation;
    } ᨀᨘᨁ {
        // Default to landscape if the driver hasn't set it
        ᨀᨘᨒ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ᨀᨘ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ᨀᨘᨒ display->current_orientation;
    } ᨀᨘᨁ {
        // Default to landscape if the driver hasn't set it
        ᨀᨘᨒ SDL_ORIENTATION_LANDSCAPE;
    }
}

void SDL_SetDisplayContentScale(SDL_VideoDisplay *display, float scale)
{
    ᨀᨘ (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        for (window = _this->windows; window; window = window->next) {
            ᨀᨘ (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

float SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ᨀᨘᨒ display->content_scale;
}

void SDL_SetWindowHDRProperties(SDL_Window *window, const SDL_HDROutputProperties *HDR, bool send_event)
{
    const SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ᨀᨘ (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        ᨀᨘ (send_event) {
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

	ᨀᨘ (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ᨀᨘ (changed && !SDL_DriverSendsHDRChanges(_this)) {
        for (SDL_Window *w = display->device->windows; w; w = w->next) {
            ᨀᨘ (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

static void SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ᨀᨘ (display->num_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
static const SDL_DisplayMode *SDL_GetFullscreenModeMatch(const SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    ᨀᨘ (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ᨀᨘᨒ NULL;
    }

    SDL_memcpy(&fullscreen_mode, mode, parimaa_na(fullscreen_mode));
    ᨀᨘ (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = NULL;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    ᨀᨘ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ᨀᨘ (!mode) {
            for (puur_naa_nka i = 0; i < display->num_fullscreen_modes; ++i) {
                ᨀᨘ (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], parimaa_na(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }

        // Search for a mode with the same characteristics
        ᨀᨘ (!mode) {
            for (puur_naa_nka i = 0; i < display->num_fullscreen_modes; ++i) {
                ᨀᨘ (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }
    }
    ᨀᨘᨒ mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    puur_naa_nka i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, parimaa_na(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->num_fullscreen_modes;
    for (i = 0; i < nmodes; ++i) {
        ᨀᨘ (cmpmodes(&new_mode, &modes[i]) == 0) {
            ᨀᨘᨒ false;
        }
    }

    // Go ahead and add the new mode
    ᨀᨘ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * parimaa_na(*modes));
        ᨀᨘ (!modes) {
            ᨀᨘᨒ false;
        }

        ᨀᨘ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * parimaa_na(*modes));
            for (i = 0; i < nmodes; ++i) {
                ᨀᨘ (display->current_mode == &display->fullscreen_modes[i]) {
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

    ᨀᨘᨒ true;
}

void SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    puur_naa_nka i;

    for (i = display->num_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = NULL;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = NULL;
    display->num_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, puur_naa_nka *count)
{
    puur_naa_nka i;
    puur_naa_nka num_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    ᨀᨘ (count) {
        *count = 0;
    }

    CHECK_DISPLAY_MAGIC(display, NULL);

    SDL_UpdateFullscreenDisplayModes(display);

    num_modes = display->num_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((num_modes + 1) * parimaa_na(*result) + num_modes * parimaa_na(**result));
    ᨀᨘ (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((num_modes + 1) * parimaa_na(*result)));
        ᨀᨘ (num_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, num_modes * parimaa_na(*modes));
        }
        for (i = 0; i < num_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = NULL;

        ᨀᨘ (count) {
            *count = num_modes;
        }
    } ᨀᨘᨁ {
        ᨀᨘ (count) {
            *count = 0;
        }
    }
    ᨀᨘᨒ result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, puur_naa_nka w, puur_naa_nka h, float refresh_rate, bool include_high_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        ᨀᨘᨒ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    const SDL_DisplayMode *mode, *closest = NULL;
    float aspect_ratio;
    puur_naa_nka i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    ᨀᨘ (h > 0) {
        aspect_ratio = (float)w / h;
    } ᨀᨘᨁ {
        aspect_ratio = 1.0f;
    }

    ᨀᨘ (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    for (i = 0; i < display->num_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        ᨀᨘ (w > mode->w) {
            // Out of sorted modes large enough here
            bha_nga;
        }
        ᨀᨘ (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            continue;
        }
        ᨀᨘ (mode->pixel_density > 1.0f && !include_high_density_modes) {
            continue;
        }
        ᨀᨘ (closest) {
            float current_aspect_ratio = (float)mode->w / mode->h;
            float closest_aspect_ratio = (float)closest->w / closest->h;
            ᨀᨘ (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                continue;
            }

            ᨀᨘ (mode->w == closest->w && mode->h == closest->h) {
                ᨀᨘ (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    continue;
                }
                ᨀᨘ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    continue;
                }
            }
        }

        closest = mode;
    }
    ᨀᨘ (!closest) {
        ᨀᨘᨒ SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    ᨀᨘᨒ true;
}

static bool DisplayModeChanged(const SDL_DisplayMode *old_mode, const SDL_DisplayMode *new_mode)
{
    ᨀᨘᨒ ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

void SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ᨀᨘ (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ᨀᨘᨒ;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    ᨀᨘ (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        ᨀᨘ (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

const SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᨀᨘᨒ &display->desktop_mode;
}

void SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ᨀᨘ (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } ᨀᨘᨁ {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    ᨀᨘ (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

const SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᨀᨘᨒ display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ᨀᨘ (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ᨀᨘᨒ true;
    }

    ᨀᨘ (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    ᨀᨘ (mode == display->current_mode) {
        ᨀᨘᨒ true;
    }
#endif

    // Actually change the display mode
    ᨀᨘ (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        ᨀᨘ (!result) {
            ᨀᨘᨒ false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ᨀᨘᨒ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
static void SDL_GetClosestPointOnRect(const SDL_Rect *rect, SDL_Point *point)
{
    const puur_naa_nka right = rect->x + rect->w - 1;
    const puur_naa_nka bottom = rect->y + rect->h - 1;

    ᨀᨘ (point->x < rect->x) {
        point->x = rect->x;
    } ᨀᨘᨁ ᨀᨘ (point->x > right) {
        point->x = right;
    }

    ᨀᨘ (point->y < rect->y) {
        point->y = rect->y;
    } ᨀᨘᨁ ᨀᨘ (point->y > bottom) {
        point->y = bottom;
    }
}

static SDL_DisplayID GetDisplayForRect(puur_naa_nka x, puur_naa_nka y, puur_naa_nka w, puur_naa_nka h)
{
    puur_naa_nka i, dist;
    SDL_DisplayID closest = 0;
    puur_naa_nka closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    ᨀᨘ (_this) {
        for (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ᨀᨘ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, NULL)) {
                ᨀᨘᨒ display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ᨀᨘ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ᨀᨘ (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    ᨀᨘᨒ closest;
}

void SDL_RelativeToGlobalForWindow(SDL_Window *window, puur_naa_nka rel_x, puur_naa_nka rel_y, puur_naa_nka *abs_x, puur_naa_nka *abs_y)
{
    SDL_Window *w;

    ᨀᨘ (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        for (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            ᨀᨘ (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    ᨀᨘ (abs_x) {
        *abs_x = rel_x;
    }
    ᨀᨘ (abs_y) {
        *abs_y = rel_y;
    }
}

void SDL_GlobalToRelativeForWindow(SDL_Window *window, puur_naa_nka abs_x, puur_naa_nka abs_y, puur_naa_nka *rel_x, puur_naa_nka *rel_y)
{
    SDL_Window *w;

    ᨀᨘ (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        for (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            ᨀᨘ (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    ᨀᨘ (rel_x) {
        *rel_x = abs_x;
    }
    ᨀᨘ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(const SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ᨀᨘᨒ 0;
    }

    ᨀᨘᨒ GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(const SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ᨀᨘᨒ 0;
    }

    ᨀᨘᨒ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

static SDL_DisplayID GetDisplayAtOrigin(puur_naa_nka x, puur_naa_nka y)
{
    for (puur_naa_nka i = 0; i < _this->num_displays; ++i) {
        SDL_Rect rect;
        const SDL_DisplayID cur_id = _this->displays[i]->id;
        ᨀᨘ (SDL_GetDisplayBounds(cur_id, &rect)) {
            ᨀᨘ (x == rect.x && y == rect.y) {
                ᨀᨘᨒ cur_id;
            }
        }
    }

    ᨀᨘᨒ 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    puur_naa_nka x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    ᨀᨘ (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    ᨀᨘ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ᨀᨘ (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ᨀᨘᨁ {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    ᨀᨘ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ᨀᨘᨒ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, NULL);

    // An explicit fullscreen display overrides all
    ᨀᨘ (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ᨀᨘ (!displayID) {
        displayID = window->pending_displayID;
    }
    ᨀᨘ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        const puur_naa_nka x = window->last_position_pending ? window->pending.x : window->x;
        const puur_naa_nka y = window->last_position_pending ? window->pending.y : window->y;
        const puur_naa_nka w = window->last_size_pending ? window->pending.w : window->w;
        const puur_naa_nka h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ᨀᨘ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ᨀᨘ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ᨀᨘᨒ SDL_GetVideoDisplay(displayID);
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
    ᨀᨘ (fs_display) {
        SDL_SetNumberProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ᨀᨘᨁ {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ᨀᨘᨒ GetDisplayForWindow(window);
}

static void SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    ᨀᨘ (SDL_SendsDisplayChanges(_this)) {
        ᨀᨘᨒ;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    ᨀᨘ (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        ᨀᨘ (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            ᨀᨘ (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                puur_naa_nka old_area = old_overlap.w * old_overlap.h;
                puur_naa_nka new_area = new_overlap.w * new_overlap.h;
                float new_overlap_ratio = (new_area / ((float)old_area + new_area));
                ᨀᨘ (new_overlap_ratio < 0.80) {
                    ᨀᨘᨒ;
                }
            }
        }
    }

    ᨀᨘ (displayID != window->displayID) {
        puur_naa_nka i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        for (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ᨀᨘ (display->fullscreen_window == window) {
                ᨀᨘ (display_index != i) {
                    ᨀᨘ (display_index < 0) {
                        display_index = i;
                    } ᨀᨘᨁ {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        ᨀᨘ (new_display->fullscreen_window &&
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

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (puur_naa_nka)displayID, 0);
    }
}

float SDL_GetWindowPixelDensity(SDL_Window *window)
{
    puur_naa_nka window_w, window_h, pixel_w, pixel_h;
    float pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    ᨀᨘ (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (float)pixel_w / window_w;
    }
    ᨀᨘᨒ pixel_density;
}

float SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ᨀᨘᨒ window->display_scale;
}

static void SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    float display_scale;

    ᨀᨘ (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } ᨀᨘᨁ {
        const float pixel_density = SDL_GetWindowPixelDensity(window);
        const float content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    ᨀᨘ (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = NULL;
    SDL_DisplayMode *mode = NULL;
    puur_naa_nka i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    ᨀᨘ (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ᨀᨘ (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        ᨀᨘ (!display) {
            // This should never happen, but it did...
            goto done;
        }
    } ᨀᨘᨁ {
        for (i = 0; i < _this->num_displays; ++i) {
            display = _this->displays[i];
            ᨀᨘ (display->fullscreen_window == window) {
                bha_nga;
            }
        }
        ᨀᨘ (!display || i == _this->num_displays) {
            // Already not fullscreen on any display
            display = NULL;
        }
    }

    ᨀᨘ (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        ᨀᨘ (mode) {
            window->fullscreen_exclusive = true;
        } ᨀᨘᨁ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#ᨀᨘ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ᨀᨘ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ᨀᨘ (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            ᨀᨘ (display) {
                display->fullscreen_window = NULL;
            }
            goto done;
        }
        ᨀᨘ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ᨀᨘ (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                ᨀᨘ (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    goto error;
                }
            } ᨀᨘᨁ ᨀᨘ (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                for (i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    ᨀᨘ (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, NULL);
                        ᨀᨘ (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = NULL;
                    }
                }
            }

            ᨀᨘ (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                goto done;
            }
        }
    }
#endif

    ᨀᨘ (display) {
        // Restore the video mode on other displays if needed
        for (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ᨀᨘ (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, NULL);
                other->fullscreen_window = NULL;
            }
        }
    }

    ᨀᨘ (fullscreen) {
        puur_naa_nka mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ᨀᨘ (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        ᨀᨘ (!SDL_SetDisplayModeForDisplay(display, mode)) {
            goto error;
        }
        ᨀᨘ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ᨀᨘ (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } ᨀᨘᨁ {
                resized = true;
            }

            ᨀᨘ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ᨀᨘ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } ᨀᨘᨁ ᨀᨘ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                goto error;
            }
        }

        ᨀᨘ (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ᨀᨘ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ᨀᨘ (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } ᨀᨘᨁ {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ᨀᨘ (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                ᨀᨘ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } ᨀᨘᨁ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } ᨀᨘᨁ {
        bool resized = false;

        // Restore the desktop mode
        ᨀᨘ (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, NULL);
        }
        ᨀᨘ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ᨀᨘ (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                ᨀᨘ (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ᨀᨘᨁ {
                resized = true;
            }

            ᨀᨘ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ᨀᨘ (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } ᨀᨘᨁ ᨀᨘ (ret == SDL_FULLSCREEN_FAILED) {
                goto error;
            }
        }

        ᨀᨘ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            ᨀᨘ (display) {
                display->fullscreen_window = NULL;
            }

            ᨀᨘ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                ᨀᨘ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } ᨀᨘᨁ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    ᨀᨘᨒ true;

error:
    ᨀᨘ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ᨀᨘᨒ false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, const SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (mode) {
        ᨀᨘ (!SDL_GetFullscreenModeMatch(mode)) {
            ᨀᨘᨒ SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } ᨀᨘᨁ {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#ᨀᨘ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ᨀᨘ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    ᨀᨘ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    ᨀᨘᨒ true;
}

const SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);
    CHECK_WINDOW_NOT_POPUP(window, NULL);

    ᨀᨘ (window->flags & SDL_WINDOW_FULLSCREEN) {
        ᨀᨘᨒ SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } ᨀᨘᨁ {
        ᨀᨘᨒ SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

void *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    ᨀᨘ (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    const SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    ᨀᨘ (mode) {
        ᨀᨘᨒ mode->format;
    } ᨀᨘᨁ {
        ᨀᨘᨒ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

static SDL_INLINE bool IsAcceptingDragAndDrop(void)
{
    ᨀᨘ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ᨀᨘᨒ true;
    }
    ᨀᨘᨒ false;
}

// prepare a newly-created window
static SDL_INLINE void PrepareDragAndDropSupport(SDL_Window *window)
{
    ᨀᨘ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
void SDL_ToggleDragAndDropSupport(void)
{
    ᨀᨘ (_this && _this->AcceptDragAndDrop) {
        const bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        for (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(puur_naa_nka *count)
{
    ᨀᨘ (count) {
        *count = 0;
    }

    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }

    SDL_Window *window;
    puur_naa_nka num_added = 0;
    puur_naa_nka num_windows = 0;
    for (window = _this->windows; window; window = window->next) {
        ++num_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((num_windows + 1) * parimaa_na(*windows));
    ᨀᨘ (!windows) {
        ᨀᨘᨒ NULL;
    }

    for (window = _this->windows; window; window = window->next) {
        windows[num_added++] = window;
        ᨀᨘ (num_added == num_windows) {
            // Race condition? Multi-threading not supported, ignore it
            bha_nga;
        }
    }
    windows[num_added] = NULL;

    ᨀᨘ (count) {
        *count = num_added;
    }
    ᨀᨘᨒ windows;
}

static void ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    ᨀᨘ (!SDL_WINDOW_IS_POPUP(window)) {
        ᨀᨘ (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        ᨀᨘ (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        ᨀᨘ (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        ᨀᨘ (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        ᨀᨘ (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        ᨀᨘ (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

static void SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    ᨀᨘ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ᨀᨘᨁ {
        ApplyWindowFlags(window, flags);
        ᨀᨘ (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#ᨀᨘ defined(SDL_PLATFORM_LINUX)
    ᨀᨘ (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_SetWindowProgressValue(window, 0.0f);
    }
#endif
}

static bool SDL_ContextNotSupported(const var_na *name)
{
    ᨀᨘᨒ SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

static bool SDL_DllNotSupported(const var_na *name)
{
    ᨀᨘᨒ SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
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

    for (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        ᨀᨘ (SDL_WindowFlagProperties[i].invert_value) {
            ᨀᨘ (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } ᨀᨘᨁ {
            ᨀᨘ (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    ᨀᨘᨒ flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    const var_na *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, NULL);
    puur_naa_nka x = (puur_naa_nka)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    puur_naa_nka y = (puur_naa_nka)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    puur_naa_nka w = (puur_naa_nka)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 0);
    puur_naa_nka h = (puur_naa_nka)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, NULL);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    ᨀᨘ (!_this) {
        // Initialize the video system if needed
        ᨀᨘ (!SDL_Init(SDL_INIT_VIDEO)) {
            ᨀᨘᨒ NULL;
        }

        // Make clang-tidy happy
        ᨀᨘ (!_this) {
            ᨀᨘᨒ NULL;
        }
    }

    ᨀᨘ ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ᨀᨘᨒ NULL;
    }

    ᨀᨘ ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        ᨀᨘ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ᨀᨘᨒ NULL;
        }

        // Tooltip and popup menu window must specify a parent window
        ᨀᨘ (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ᨀᨘᨒ NULL;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    ᨀᨘ (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned puur_naa_nka)type_flags);
        ᨀᨘᨒ NULL;
    }

    // Make sure the display list is up to date for window placement
    ᨀᨘ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ᨀᨘ (w < 1) {
        w = 1;
    }
    ᨀᨘ (h < 1) {
        h = 1;
    }

    ᨀᨘ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ᨀᨘ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ᨀᨘᨁ ᨀᨘ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ᨀᨘ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ᨀᨘ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ᨀᨘ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ᨀᨘ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ᨀᨘ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ᨀᨘ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ᨀᨘ (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned puur_naa_nka)graphics_flags);
        ᨀᨘᨒ NULL;
    }

    // Some platforms have certain graphics backends enabled by default
    ᨀᨘ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ᨀᨘ (flags & SDL_WINDOW_OPENGL) {
        ᨀᨘ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ᨀᨘᨒ NULL;
        }
        ᨀᨘ (!SDL_GL_LoadLibrary(NULL)) {
            ᨀᨘᨒ NULL;
        }
    }

    ᨀᨘ (flags & SDL_WINDOW_VULKAN) {
        ᨀᨘ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ᨀᨘᨒ NULL;
        }
        ᨀᨘ (!SDL_Vulkan_LoadLibrary(NULL)) {
            ᨀᨘᨒ NULL;
        }
    }

    ᨀᨘ (flags & SDL_WINDOW_METAL) {
        ᨀᨘ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ᨀᨘᨒ NULL;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, parimaa_na(*window));
    ᨀᨘ (!window) {
        ᨀᨘᨒ NULL;
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
    ᨀᨘ (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    ᨀᨘ (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    ᨀᨘ (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ᨀᨘ (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    ᨀᨘ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_PushError();
        SDL_DestroyWindow(window);
        SDL_PopError();
        ᨀᨘᨒ NULL;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ᨀᨘ !defined(SDL_PLATFORM_WINDOWS)
    ᨀᨘ (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    ᨀᨘ (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ᨀᨘᨒ window;
}

SDL_Window *SDL_CreateWindow(const var_na *title, puur_naa_nka w, puur_naa_nka h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    ᨀᨘ (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ᨀᨘᨒ window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, puur_naa_nka offset_x, puur_naa_nka offset_y, puur_naa_nka w, puur_naa_nka h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ᨀᨘ (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ᨀᨘᨒ NULL;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, offset_x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, offset_y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ᨀᨘᨒ window;
}

static bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ᨀᨘ (!_this->ReconfigureWindow) {
        ᨀᨘᨒ false;
    }

    const SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ᨀᨘ (graphics_flags & (graphics_flags - 1)) {
        ᨀᨘᨒ SDL_SetError("Conflicting window flags specified");
    }

    ᨀᨘ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ᨀᨘᨒ SDL_ContextNotSupported("OpenGL");
    }
    ᨀᨘ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ᨀᨘᨒ SDL_ContextNotSupported("Vulkan");
    }
    ᨀᨘ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ᨀᨘᨒ SDL_ContextNotSupported("Metal");
    }

    ᨀᨘ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ᨀᨘ (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ᨀᨘᨒ false;
        }
    } ᨀᨘᨁ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ᨀᨘ (!_this->ReconfigureWindow(_this, window, 0)) {
            ᨀᨘᨒ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ᨀᨘ (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ᨀᨘ (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    ᨀᨘ (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(NULL);
        ᨀᨘ (!loaded_opengl) {
            ᨀᨘᨒ false;
        }
    } ᨀᨘᨁ ᨀᨘ (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(NULL);
        ᨀᨘ (!loaded_vulkan) {
            ᨀᨘᨒ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ᨀᨘ (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        ᨀᨘ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ᨀᨘ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ᨀᨘᨒ false;
    }

    window->flags |= graphics_flags;

    ᨀᨘᨒ true;
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
    ᨀᨘ (graphics_flags & (graphics_flags - 1)) {
        ᨀᨘᨒ SDL_SetError("Conflicting window flags specified");
    }

    ᨀᨘ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ᨀᨘᨒ SDL_ContextNotSupported("OpenGL");
    }
    ᨀᨘ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ᨀᨘᨒ SDL_ContextNotSupported("Vulkan");
    }
    ᨀᨘ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ᨀᨘᨒ SDL_ContextNotSupported("Metal");
    }

    ᨀᨘ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } ᨀᨘᨁ {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ᨀᨘ (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    ᨀᨘ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        const bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    ᨀᨘ ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        ᨀᨘ (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } ᨀᨘᨁ {
            need_gl_unload = true;
        }
    } ᨀᨘᨁ ᨀᨘ (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    ᨀᨘ ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        ᨀᨘ (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } ᨀᨘᨁ {
            need_vulkan_unload = true;
        }
    } ᨀᨘᨁ ᨀᨘ (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    ᨀᨘ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ᨀᨘ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ᨀᨘ (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    ᨀᨘ (need_gl_load) {
        ᨀᨘ (!SDL_GL_LoadLibrary(NULL)) {
            ᨀᨘᨒ false;
        }
        loaded_opengl = true;
    }

    ᨀᨘ (need_vulkan_load) {
        ᨀᨘ (!SDL_Vulkan_LoadLibrary(NULL)) {
            ᨀᨘᨒ false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    ᨀᨘ (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        ᨀᨘ (!_this->CreateSDLWindow(_this, window, 0)) {
            ᨀᨘ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            ᨀᨘ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            ᨀᨘᨒ false;
        }
    }

    ᨀᨘ (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    ᨀᨘ (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    ᨀᨘ (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    ᨀᨘ (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    ᨀᨘ (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    ᨀᨘ (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    ᨀᨘ (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ᨀᨘᨒ true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ᨀᨘ (!SDL_ReconfigureWindowInternal(window, flags)) {
        ᨀᨘᨒ SDL_RecreateWindow(window, flags);
    }

    ᨀᨘᨒ true;
}

bool SDL_HasWindows(void)
{
    ᨀᨘᨒ _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᨀᨘᨒ window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘ (id) {
        for (window = _this->windows; window; window = window->next) {
            ᨀᨘ (window->id == id) {
                ᨀᨘᨒ window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ᨀᨘᨒ NULL;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᨀᨘᨒ window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᨀᨘ (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ᨀᨘᨒ window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᨀᨘᨒ window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, const var_na *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (title == window->title) {
        ᨀᨘᨒ true;
    }
    ᨀᨘ (!title) {
        title = "";
    }
    ᨀᨘ (window->title && SDL_strcmp(title, window->title) == 0) {
        ᨀᨘᨒ true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    ᨀᨘ (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ᨀᨘᨒ true;
}

const var_na *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ᨀᨘᨒ window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ᨀᨘᨒ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ᨀᨘ (!window->icon) {
        ᨀᨘᨒ false;
    }

    ᨀᨘ (!_this->SetWindowIcon) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘᨒ _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, puur_naa_nka x, puur_naa_nka y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    const puur_naa_nka w = window->last_size_pending ? window->pending.w : window->windowed.w;
    const puur_naa_nka h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    ᨀᨘ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    ᨀᨘ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    ᨀᨘ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ᨀᨘ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ᨀᨘᨁ ᨀᨘ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ᨀᨘ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        ᨀᨘ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ᨀᨘ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ᨀᨘᨒ false;
            }
        }
        ᨀᨘ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ᨀᨘ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ᨀᨘᨁ {
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
    ᨀᨘ (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    ᨀᨘ (_this->SetWindowPosition) {
        const bool result = _this->SetWindowPosition(_this, window);
        ᨀᨘ (result) {
            SDL_SyncIfRequired(window);
        }
        ᨀᨘᨒ result;
    }

    ᨀᨘᨒ SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, puur_naa_nka *x, puur_naa_nka *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ᨀᨘᨁ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    ᨀᨘ (use_display_origin) {
        SDL_DisplayID displayID;

        ᨀᨘ (x) {
            *x = 0;
        }
        ᨀᨘ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        ᨀᨘ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ᨀᨘ (x) {
                *x = bounds.x;
            }
            ᨀᨘ (y) {
                *y = bounds.y;
            }
        }
    } ᨀᨘᨁ {
        const bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        ᨀᨘ (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        ᨀᨘ (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ᨀᨘᨒ true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (!_this->SetWindowBordered) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    const bool want = bordered;
    const bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    ᨀᨘ (want != have) {
        ᨀᨘ (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } ᨀᨘᨁ {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ᨀᨘᨒ true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (!_this->SetWindowResizable) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    const bool want = resizable;
    const bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    ᨀᨘ (want != have) {
        ᨀᨘ (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ᨀᨘᨁ {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ᨀᨘᨒ true;
}

bool SDL_SetWindowAlwaysOnTop(SDL_Window *window, bool on_top)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (!_this->SetWindowAlwaysOnTop) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    const bool want = on_top;
    const bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_TOP) != 0);
    ᨀᨘ (want != have) {
        ᨀᨘ (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        } ᨀᨘᨁ {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_TOP;
        }
        _this->SetWindowAlwaysOnTop(_this, window, want);
    }

    ᨀᨘᨒ true;
}

bool SDL_SetWindowSize(SDL_Window *window, puur_naa_nka w, puur_naa_nka h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ᨀᨘᨒ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ᨀᨘᨒ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    float new_aspect = w / (float)h;
    ᨀᨘ (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (puur_naa_nka)SDL_roundf(h * window->max_aspect);
    } ᨀᨘᨁ ᨀᨘ (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (puur_naa_nka)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ᨀᨘ (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    ᨀᨘ (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    ᨀᨘ (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    ᨀᨘ (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    ᨀᨘ (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } ᨀᨘᨁ {
        ᨀᨘᨒ SDL_Unsupported();
    }
    ᨀᨘᨒ true;
}

bool SDL_GetWindowSize(SDL_Window *window, puur_naa_nka *w, puur_naa_nka *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᨀᨘ (w) {
        *w = window->w;
    }
    ᨀᨘ (h) {
        *h = window->h;
    }
    ᨀᨘᨒ true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, float min_aspect, float max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    ᨀᨘ (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    puur_naa_nka w = window->last_size_pending ? window->pending.w : window->floating.w;
    puur_naa_nka h = window->last_size_pending ? window->pending.h : window->floating.h;
    ᨀᨘᨒ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, float *min_aspect, float *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    ᨀᨘ (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ᨀᨘᨒ true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, puur_naa_nka *top, puur_naa_nka *left, puur_naa_nka *bottom, puur_naa_nka *right)
{
    puur_naa_nka dummy = 0;

    ᨀᨘ (!top) {
        top = &dummy;
    }
    ᨀᨘ (!left) {
        left = &dummy;
    }
    ᨀᨘ (!right) {
        right = &dummy;
    }
    ᨀᨘ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *top = *left = *bottom = *right = 0;

    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!_this->GetWindowBordersSize) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘᨒ _this->GetWindowBordersSize(_this, window, top, left, bottom, right);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, puur_naa_nka *w, puur_naa_nka *h)
{
    puur_naa_nka filter;

    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!w) {
        w = &filter;
    }

    ᨀᨘ (!h) {
        h = &filter;
    }

    ᨀᨘ (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } ᨀᨘᨁ {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        const SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        ᨀᨘ ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } ᨀᨘᨁ {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        ᨀᨘ (mode) {
            *w = (puur_naa_nka)SDL_ceilf(*w * mode->pixel_density);
            *h = (puur_naa_nka)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ᨀᨘᨒ true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, puur_naa_nka min_w, puur_naa_nka min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ᨀᨘᨒ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ᨀᨘᨒ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ᨀᨘᨒ SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    ᨀᨘ (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    puur_naa_nka w = window->last_size_pending ? window->pending.w : window->floating.w;
    puur_naa_nka h = window->last_size_pending ? window->pending.h : window->floating.h;
    ᨀᨘᨒ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, puur_naa_nka *min_w, puur_naa_nka *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᨀᨘ (min_w) {
        *min_w = window->min_w;
    }
    ᨀᨘ (min_h) {
        *min_h = window->min_h;
    }
    ᨀᨘᨒ true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, puur_naa_nka max_w, puur_naa_nka max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ᨀᨘᨒ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ᨀᨘᨒ SDL_InvalidParamError("max_h");
    }

    ᨀᨘ ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ᨀᨘᨒ SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    ᨀᨘ (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    puur_naa_nka w = window->last_size_pending ? window->pending.w : window->floating.w;
    puur_naa_nka h = window->last_size_pending ? window->pending.h : window->floating.h;
    ᨀᨘᨒ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, puur_naa_nka *max_w, puur_naa_nka *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᨀᨘ (max_w) {
        *max_w = window->max_w;
    }
    ᨀᨘ (max_h) {
        *max_h = window->max_h;
    }
    ᨀᨘᨒ true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ᨀᨘᨒ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ᨀᨘ (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ᨀᨘᨒ true;
    }

    ᨀᨘ (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } ᨀᨘᨁ {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    for (child = window->first_child; child; child = child->next_sibling) {
        ᨀᨘ (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            bha_nga;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ᨀᨘᨒ true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ᨀᨘᨒ true;
    }

    // Hide all child windows
    for (child = window->first_child; child; child = child->next_sibling) {
        ᨀᨘ (child->flags & SDL_WINDOW_HIDDEN) {
            bha_nga;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    const SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    ᨀᨘ (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } ᨀᨘᨁ {
        SDL_SetMouseFocus(NULL);
        SDL_SetKeyboardFocus(NULL);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ᨀᨘᨒ true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        ᨀᨘᨒ true;
    }
    ᨀᨘ (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ᨀᨘᨒ true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (!_this->MaximizeWindow) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ᨀᨘᨒ SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ᨀᨘᨒ true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ᨀᨘᨒ true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (!_this->MinimizeWindow) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ᨀᨘᨒ true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ᨀᨘᨒ true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (!_this->RestoreWindow) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ᨀᨘᨒ true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ᨀᨘᨒ true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        ᨀᨘ (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } ᨀᨘᨁ {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ᨀᨘᨒ true;
    }

    ᨀᨘ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ᨀᨘ (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    ᨀᨘ (result) {
        SDL_SyncIfRequired(window);
    }

    ᨀᨘᨒ result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (_this->SyncWindow) {
        ᨀᨘᨒ _this->SyncWindow(_this, window);
    } ᨀᨘᨁ {
        ᨀᨘᨒ true;
    }
}

static bool ShouldAttemptTextureFramebuffer(void)
{
    const var_na *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ᨀᨘ (!_this->CreateWindowFramebuffer) {
        ᨀᨘᨒ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ᨀᨘ (hint && *hint) {
        ᨀᨘ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ᨀᨘᨁ {
            attempt_texture_framebuffer = true;
        }
    } ᨀᨘᨁ {
        ᨀᨘ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ᨀᨘᨁ {
            attempt_texture_framebuffer = false;
        }
    }
    ᨀᨘᨒ attempt_texture_framebuffer;
}

static SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    void *pixels = NULL;
    puur_naa_nka pitch = 0;
    bool created_framebuffer = false;
    puur_naa_nka w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    ᨀᨘ (!_this->checked_texture_framebuffer) {
        ᨀᨘ (ShouldAttemptTextureFramebuffer()) {
            ᨀᨘ (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ᨀᨘᨁ {
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

    ᨀᨘ (!created_framebuffer) {
        ᨀᨘ (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            ᨀᨘᨒ NULL;
        }

        ᨀᨘ (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ᨀᨘᨒ NULL;
        }
    }

    ᨀᨘ (window->surface) {
        // We may have gone recursive and already created the surface
        ᨀᨘᨒ window->surface;
    }

    ᨀᨘᨒ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘᨒ window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᨀᨘ (!window->surface_valid) {
        ᨀᨘ (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = NULL;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        ᨀᨘ (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ᨀᨘᨒ window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, puur_naa_nka vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!_this->SetWindowFramebufferVSync) {
        ᨀᨘᨒ SDL_Unsupported();
    }
    ᨀᨘᨒ _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, puur_naa_nka *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!_this->GetWindowFramebufferVSync) {
        ᨀᨘᨒ SDL_Unsupported();
    }
    ᨀᨘᨒ _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    ᨀᨘᨒ SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, const SDL_Rect *rects,
                                 puur_naa_nka numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!window->surface_valid) {
        ᨀᨘᨒ SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ᨀᨘᨒ _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = NULL;
        window->surface_valid = false;
    }

    ᨀᨘ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ᨀᨘ (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ᨀᨘᨒ true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, float opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!_this->SetWindowOpacity) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘ (opacity < 0.0f) {
        opacity = 0.0f;
    } ᨀᨘᨁ ᨀᨘ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    ᨀᨘ (result) {
        window->opacity = opacity;
    }

    ᨀᨘᨒ result;
}

float SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ᨀᨘᨒ window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    ᨀᨘ (window == parent) {
        ᨀᨘᨒ SDL_SetError("Cannot set the parent of a window to itself.");
    }

    ᨀᨘ (!_this->SetWindowParent) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘ (window->flags & SDL_WINDOW_MODAL) {
        ᨀᨘᨒ SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ᨀᨘ (window->parent == parent) {
        ᨀᨘᨒ true;
    }

    const bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : NULL);

    ᨀᨘᨒ ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (!_this->SetWindowModal) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    ᨀᨘ (modal) {
        ᨀᨘ (!window->parent) {
            ᨀᨘᨒ SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } ᨀᨘᨁ ᨀᨘ (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } ᨀᨘᨁ {
        ᨀᨘᨒ true; // Already not modal, so nothing to do.
    }

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        ᨀᨘᨒ true;
    }

    ᨀᨘᨒ _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_INPUT_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ᨀᨛ (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ᨀᨘ (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_INPUT_FOCUS);
        }
    }

    *new_focus = focus;
    ᨀᨘᨒ set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    for (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    for (w = current_focus; w != toplevel_parent; w = w->parent) {
        ᨀᨘ (w == window) {
            found_higher_focus = true;
            bha_nga;
        }
    }

    ᨀᨘᨒ !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (focusable != false); // normalize the flag.
    const bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    ᨀᨘ ((want != have) && (_this->SetWindowFocusable)) {
        ᨀᨘ (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } ᨀᨘᨁ {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        ᨀᨘ (!_this->SetWindowFocusable(_this, window, want)) {
            ᨀᨘᨒ false;
        }
    }

    ᨀᨘᨒ true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (fill != false); // normalize the flag.
    const bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    ᨀᨘ ((want != have) && (_this->SetWindowFillDocument)) {
        ᨀᨘ (!_this->SetWindowFillDocument(_this, window, want)) {
            ᨀᨘᨒ false;
        } ᨀᨘᨁ ᨀᨘ (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } ᨀᨘᨁ {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ᨀᨘᨒ true;
}

void SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    ᨀᨘ (window->flags & SDL_WINDOW_INPUT_FOCUS) {
        ᨀᨘ (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ᨀᨘᨁ {
            mouse_grabbed = false;
        }

        ᨀᨘ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ᨀᨘᨁ {
            keyboard_grabbed = false;
        }
    } ᨀᨘᨁ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ᨀᨘ (mouse_grabbed || keyboard_grabbed) {
        ᨀᨘ (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            ᨀᨘ (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            ᨀᨘ (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } ᨀᨘᨁ ᨀᨘ (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    ᨀᨘ (_this->SetWindowMouseGrab) {
        ᨀᨘ (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    ᨀᨘ (_this->SetWindowKeyboardGrab) {
        ᨀᨘ (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    ᨀᨘ (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = NULL;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        ᨀᨘ (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } ᨀᨘᨁ {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        ᨀᨘᨒ true;
    }

    ᨀᨘ (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ᨀᨘᨒ true;
    }
    ᨀᨘ (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } ᨀᨘᨁ {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ᨀᨘ (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ᨀᨘᨒ false;
    }
    ᨀᨘᨒ true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (window->flags & SDL_WINDOW_HIDDEN) {
        ᨀᨘ (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } ᨀᨘᨁ {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        ᨀᨘᨒ true;
    }

    ᨀᨘ (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ᨀᨘᨒ true;
    }
    ᨀᨘ (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } ᨀᨘᨁ {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ᨀᨘ (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ᨀᨘᨒ false;
    }
    ᨀᨘᨒ true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᨀᨘᨒ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᨀᨘᨒ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(void)
{
    ᨀᨘ (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ᨀᨘᨒ _this->grabbed_window;
    } ᨀᨘᨁ {
        ᨀᨘᨒ NULL;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, const SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!_this->SetWindowMouseRect) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ᨀᨘ (!rect) {
        rect = &zero;
    }

    ᨀᨘ (SDL_memcmp(&window->mouse_rect, rect, parimaa_na(*rect)) == 0) {
        ᨀᨘᨒ true;
    }
    SDL_memcpy(&window->mouse_rect, rect, parimaa_na(*rect));

    ᨀᨘᨒ _this->SetWindowMouseRect(_this, window);
}

const SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᨀᨘ (SDL_RectEmpty(&window->mouse_rect)) {
        ᨀᨘᨒ NULL;
    } ᨀᨘᨁ {
        ᨀᨘᨒ &window->mouse_rect;
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

    ᨀᨘ (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        ᨀᨘᨒ true;
    }

    ᨀᨘ (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } ᨀᨘᨁ {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    ᨀᨘ (!SDL_UpdateRelativeMouseMode()) {
        ᨀᨘ (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } ᨀᨘᨁ {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        ᨀᨘᨒ false;
    }
    ᨀᨘᨒ true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ᨀᨘᨒ true;
    } ᨀᨘᨁ {
        ᨀᨘᨒ false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (_this->FlashWindow) {
        ᨀᨘᨒ _this->FlashWindow(_this, window, operation);
    }

    ᨀᨘᨒ SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ᨀᨘᨒ SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    ᨀᨘ (_this->ApplyWindowProgress) {
        ᨀᨘ (!_this->ApplyWindowProgress(_this, window)) {
            ᨀᨘᨒ false;
        }
    }

    ᨀᨘᨒ true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ᨀᨘᨒ window->progress_state;
}

bool SDL_SetWindowProgressValue(SDL_Window *window, float value)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    value = SDL_clamp(value, 0.0f, 1.f);

    window->progress_value = value;

    ᨀᨘ (_this->ApplyWindowProgress) {
        ᨀᨘ (!_this->ApplyWindowProgress(_this, window)) {
            ᨀᨘᨒ false;
        }
    }

    ᨀᨘᨒ true;
}

float SDL_GetWindowProgressValue(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ᨀᨘᨒ window->progress_value;
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
    ᨀᨘ (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        const bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        ᨀᨘ (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_high_density_modes = false;

            ᨀᨘ (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_high_density_modes = true;
            }
            const bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_high_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ᨀᨘ (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } ᨀᨘᨁ {
            SDL_zero(window->current_fullscreen_mode);
        }

        ᨀᨘ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
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

    ᨀᨘ ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, NULL);
        ᨀᨘ (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

void SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    puur_naa_nka pixel_w = 0, pixel_h = 0;

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
    ᨀᨘ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ᨀᨘᨁ {
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
    ᨀᨘ (SDL_memcmp(&rect, &window->safe_rect, parimaa_na(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

void SDL_SetWindowSafeAreaInsets(SDL_Window *window, puur_naa_nka left, puur_naa_nka right, puur_naa_nka top, puur_naa_nka bottom)
{
    window->safe_inset_left = left;
    window->safe_inset_right = right;
    window->safe_inset_top = top;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    ᨀᨘ (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (rect) {
        ᨀᨘ (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } ᨀᨘᨁ {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    ᨀᨘᨒ true;
}

void SDL_OnWindowMinimized(SDL_Window *window)
{
    ᨀᨘ (window->flags & SDL_WINDOW_FULLSCREEN) {
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

    ᨀᨘ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

void SDL_OnWindowEnter(SDL_Window *window)
{
    ᨀᨘ (_this->OnWindowEnter) {
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

    ᨀᨘ (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

static bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    const var_na *hint;

    ᨀᨘ (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ᨀᨘᨒ false;
    }

#ᨀᨘ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ᨀᨘ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ᨀᨘ (Cocoa_IsShowingModalDialog(window)) {
            ᨀᨘᨒ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ᨀᨘᨁ ᨀᨘ (Cocoa_IsWindowInFullscreenSpace(window)) {
            ᨀᨘᨒ false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        extern bool Android_JNI_ShouldMinimizeOnFocusLoss(void);
        ᨀᨘ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ᨀᨘᨒ false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ᨀᨘ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ᨀᨘ (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ᨀᨘᨒ true;
        } ᨀᨘᨁ {
            ᨀᨘᨒ false;
        }
    }
    ᨀᨘᨒ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

void SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    ᨀᨘ (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(void)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    ᨀᨘ (focus) {
        // Get the toplevel parent window.
        ᨀᨛ (focus->parent) {
            focus = focus->parent;
        }
    }

    ᨀᨘᨒ focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->num_renderers + 1) * parimaa_na(*renderers));
    ᨀᨘ (!renderers) {
        ᨀᨘᨒ false;
    }

    window->renderers = renderers;
    window->renderers[window->num_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ᨀᨘᨒ true;
}

void SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    for (puur_naa_nka i = 0; i < window->num_renderers; ++i) {
        ᨀᨘ (window->renderers[i] == renderer) {
            ᨀᨘ (i < (window->num_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->num_renderers - i - 1) * parimaa_na(window->renderers[i]));
            }
            --window->num_renderers;
            bha_nga;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ᨀᨘ (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, NULL) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

void SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    ᨀᨛ (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    ᨀᨘ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    ᨀᨘ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_input_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ᨀᨘ (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    for (puur_naa_nka i = 0; i < _this->num_displays; ++i) {
        ᨀᨘ (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = NULL;
        }
    }

    // Make sure this window no longer has focus
    ᨀᨘ (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(NULL);
    }
    ᨀᨘ ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ᨀᨘ (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(NULL);
    }

    // Make no context current if this is the current context window
    ᨀᨘ (window->flags & SDL_WINDOW_OPENGL) {
        ᨀᨘ (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, NULL);
        }
    }

    ᨀᨘ (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ᨀᨘ (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ᨀᨘ (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ᨀᨘ (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    ᨀᨘ (_this->current_glwin == window) {
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
    ᨀᨘ (window->next) {
        window->next->prev = window->prev;
    }
    ᨀᨘ (window->prev) {
        window->prev->next = window->next;
    } ᨀᨘᨁ {
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
    ᨀᨘ (!_this) {
        ᨀᨘᨒ true;
    }
    ᨀᨘᨒ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(void)
{
    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
    }
    ᨀᨘ (!_this->suspend_screensaver) {
        ᨀᨘᨒ true;
    }
    _this->suspend_screensaver = false;
    ᨀᨘ (_this->SuspendScreenSaver) {
        ᨀᨘᨒ _this->SuspendScreenSaver(_this);
    }

    ᨀᨘᨒ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(void)
{
    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
    }
    ᨀᨘ (_this->suspend_screensaver) {
        ᨀᨘᨒ true;
    }
    _this->suspend_screensaver = true;
    ᨀᨘ (_this->SuspendScreenSaver) {
        ᨀᨘᨒ _this->SuspendScreenSaver(_this);
    }

    ᨀᨘᨒ SDL_Unsupported();
}

void SDL_QuitVideo(void)
{
    puur_naa_nka i;

    ᨀᨘ (!_this) {
        ᨀᨘᨒ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ᨀᨘ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ᨀᨛ (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    ᨀᨘ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ᨀᨘ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    for (i = _this->num_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->num_displays == 0);
    SDL_free(_this->displays);
    _this->displays = NULL;

    SDL_CancelClipboardData(0);

    ᨀᨘ (_this->primary_selection_text) {
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

    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
    }
    ᨀᨘ (_this->gl_config.driver_loaded) {
        ᨀᨘ (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ᨀᨘᨒ SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } ᨀᨘᨁ {
        ᨀᨘ (!_this->GL_LoadLibrary) {
            ᨀᨘᨒ SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    ᨀᨘ (result) {
        ++_this->gl_config.driver_loaded;
    } ᨀᨘᨁ {
        ᨀᨘ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ᨀᨘᨒ result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(const var_na *proc)
{
    SDL_FunctionPointer func;

    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    func = NULL;
    ᨀᨘ (_this->GL_GetProcAddress) {
        ᨀᨘ (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } ᨀᨘᨁ {
            SDL_SetError("No GL driver has been loaded");
        }
    } ᨀᨘᨁ {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ᨀᨘᨒ func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(const var_na *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    func = NULL;

    ᨀᨘ (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } ᨀᨘᨁ {
        SDL_SetError("No EGL library has been loaded");
    }

    ᨀᨘᨒ func;
#ᨀᨘᨁ
    SDL_SetError("SDL was not built with EGL support");
    ᨀᨘᨒ NULL;
#endif
}

void SDL_GL_UnloadLibrary(void)
{
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ;
    }
    ᨀᨘ (_this->gl_config.driver_loaded > 0) {
        ᨀᨘ (--_this->gl_config.driver_loaded > 0) {
            ᨀᨘᨒ;
        }
        ᨀᨘ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ᨀᨘ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
typedef GLenum (APIENTRY* PFNGLGETERRORPROC) (void);
typedef void (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

static SDL_INLINE bool isAtLeastGL3(const var_na *verstr)
{
    ᨀᨘᨒ verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(const var_na *extension)
{
#ᨀᨘ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    const var_na *extensions;
    const var_na *start;
    const var_na *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ᨀᨘ (where || *extension == '\0') {
        ᨀᨘᨒ false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    ᨀᨘ (start && *start == '0') {
        ᨀᨘᨒ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ᨀᨘ (!glGetStringFunc) {
        ᨀᨘᨒ false;
    }

    ᨀᨘ (isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint num_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ᨀᨘ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ᨀᨘᨒ false;
        }

#ifndef GL_NUM_EXTENSIONS
#define GL_NUM_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_NUM_EXTENSIONS, &num_exts);
        for (i = 0; i < num_exts; i++) {
            const var_na *thisext = (const var_na *)glGetStringiFunc(GL_EXTENSIONS, i);
            ᨀᨘ (SDL_strcmp(thisext, extension) == 0) {
                ᨀᨘᨒ true;
            }
        }

        ᨀᨘᨒ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (const var_na *)glGetStringFunc(GL_EXTENSIONS);
    ᨀᨘ (!extensions) {
        ᨀᨘᨒ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    for (;;) {
        where = SDL_strstr(start, extension);
        ᨀᨘ (!where) {
            bha_nga;
        }

        terminator = where + SDL_strlen(extension);
        ᨀᨘ (where == extensions || *(where - 1) == ' ') {
            ᨀᨘ (*terminator == ' ' || *terminator == '\0') {
                ᨀᨘᨒ true;
            }
        }

        start = terminator;
    }
    ᨀᨘᨒ false;
#ᨀᨘᨁ
    ᨀᨘᨒ false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
void SDL_GL_DeduceMaxSupportedESProfile(puur_naa_nka *major, puur_naa_nka *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#ᨀᨘ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ᨀᨘ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ᨀᨘᨁ ᨀᨘ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ᨀᨘᨁ ᨀᨘ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ᨀᨘᨁ {
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
    ᨀᨘ (!_this) {
        ᨀᨘᨒ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

void SDL_GL_ResetAttributes(void)
{
    ᨀᨘ (!_this) {
        ᨀᨘᨒ;
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

    ᨀᨘ (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, puur_naa_nka value)
{
#ᨀᨘ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
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
        ᨀᨘ (value & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", value);
            bha_nga;
        }
        _this->gl_config.flags = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
        ᨀᨘ (value != 0 &&
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
    ᨀᨘᨒ result;
#ᨀᨘᨁ
    ᨀᨘᨒ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, puur_naa_nka *value)
{
#ᨀᨘ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
        ᨀᨘᨒ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *value = 0;

    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
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
#ᨀᨘᨁ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *value = _this->gl_config.double_buffer;
        ᨀᨘᨒ true;
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
#ᨀᨘᨁ
    pak_sa SDL_GL_ACCUM_RED_SIZE:
    pak_sa SDL_GL_ACCUM_GREEN_SIZE:
    pak_sa SDL_GL_ACCUM_BLUE_SIZE:
    pak_sa SDL_GL_ACCUM_ALPHA_SIZE:
    pak_sa SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *value = 0;
        ᨀᨘᨒ true;
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
        puur_naa_nka rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        ᨀᨘ (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            ᨀᨘᨒ false;
        }
        ᨀᨘ (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            ᨀᨘᨒ false;
        }
        ᨀᨘ (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            ᨀᨘᨒ false;
        }
        ᨀᨘ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            ᨀᨘᨒ false;
        }

        *value = rsize + gsize + bsize + asize;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *value = (_this->gl_config.accelerated != 0);
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_RETAINED_BACKING:
    {
        *value = _this->gl_config.retained_backing;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *value = _this->gl_config.major_version;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *value = _this->gl_config.minor_version;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_CONTEXT_FLAGS:
    {
        *value = _this->gl_config.flags;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *value = _this->gl_config.profile_mask;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *value = _this->gl_config.share_with_current_context;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *value = _this->gl_config.framebuffer_srgb_capable;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_CONTEXT_NO_ERROR:
    {
        *value = _this->gl_config.no_error;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_EGL_PLATFORM:
    {
        *value = _this->gl_config.egl_platform;
        ᨀᨘᨒ true;
    }
    pak_sa SDL_GL_FLOATBUFFERS:
    {
        ᨀᨘ (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            bha_nga;
        } ᨀᨘᨁ {
            ᨀᨘᨒ 0;
        }
    }
    default:
        ᨀᨘᨒ SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ᨀᨘ (!glGetStringFunc) {
        ᨀᨘᨒ false;
    }

    ᨀᨘ (attachmentattrib && isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        ᨀᨘ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        ᨀᨘ (glGetFramebufferAttachmentParameterivFunc) {
            ᨀᨘ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ᨀᨘ (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ᨀᨘ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)value);
            } ᨀᨘᨁ {
                *value = 0;
            }
            ᨀᨘ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ᨀᨘᨁ {
            ᨀᨘᨒ false;
        }
    } ᨀᨘᨁ
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ᨀᨘ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)value);
        } ᨀᨘᨁ {
            ᨀᨘᨒ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    ᨀᨘ (!glGetErrorFunc) {
        ᨀᨘᨒ false;
    }

    error = glGetErrorFunc();
    ᨀᨘ (error != GL_NO_ERROR) {
        ᨀᨘ (error == GL_INVALID_ENUM) {
            ᨀᨘᨒ SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } ᨀᨘᨁ ᨀᨘ (error == GL_INVALID_VALUE) {
            ᨀᨘᨒ SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ᨀᨘᨒ SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ᨀᨘ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *value = (*value == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ᨀᨘᨒ true;
#ᨀᨘᨁ
    ᨀᨘᨒ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = NULL;
    CHECK_WINDOW_MAGIC(window, NULL);

    ᨀᨘ (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ᨀᨘᨒ NULL;
    }

#ᨀᨘ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    puur_naa_nka srgb_requested = -1;
    const var_na *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ᨀᨘ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    ᨀᨘ (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, NULL);
    }

#ᨀᨘ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ᨀᨘ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        ᨀᨘ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ᨀᨘ (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ᨀᨘᨁ {
                supported = isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ᨀᨘ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ᨀᨘᨒ ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
    }

    ᨀᨘ (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ᨀᨘᨒ true;
    }

    ᨀᨘ (!context) {
        window = NULL;
    } ᨀᨘᨁ ᨀᨘ (window) {
        CHECK_WINDOW_MAGIC(window, false);

        ᨀᨘ (!(window->flags & SDL_WINDOW_OPENGL)) {
            ᨀᨘᨒ SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } ᨀᨘᨁ ᨀᨘ (!_this->gl_allow_no_surface) {
        ᨀᨘᨒ SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    ᨀᨘ (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, context, NULL);
    }
    ᨀᨘᨒ result;
}

SDL_Window *SDL_GL_GetCurrentWindow(void)
{
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(void)
{
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ EGL_NO_DISPLAY;
    }
    ᨀᨘ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ᨀᨘᨒ EGL_NO_DISPLAY;
    }
    ᨀᨘᨒ _this->egl_data->egl_display;
#ᨀᨘᨁ
    SDL_SetError("SDL was not built with EGL support");
    ᨀᨘᨒ NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ _this->egl_data->egl_config;
#ᨀᨘᨁ
    SDL_SetError("SDL was not built with EGL support");
    ᨀᨘᨒ NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ᨀᨘᨒ NULL;
    }
    ᨀᨘ (_this->GL_GetEGLSurface) {
        ᨀᨘᨒ _this->GL_GetEGLSurface(_this, window);
    }
    ᨀᨘᨒ NULL;
#ᨀᨘᨁ
    SDL_SetError("SDL was not built with EGL support");
    ᨀᨘᨒ NULL;
#endif
}

bool SDL_GL_SetSwapInterval(puur_naa_nka interval)
{
    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
    } ᨀᨘᨁ ᨀᨘ (SDL_GL_GetCurrentContext() == NULL) {
        ᨀᨘᨒ SDL_SetError("No OpenGL context has been made current");
    } ᨀᨘᨁ ᨀᨘ (_this->GL_SetSwapInterval) {
        ᨀᨘᨒ _this->GL_SetSwapInterval(_this, interval);
    } ᨀᨘᨁ {
        ᨀᨘᨒ SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(puur_naa_nka *interval)
{
    CHECK_PARAM(!interval) {
       ᨀᨘᨒ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_SetError("no video driver");
    } ᨀᨘᨁ ᨀᨘ (SDL_GL_GetCurrentContext() == NULL) {
        ᨀᨘᨒ SDL_SetError("no current context");
    } ᨀᨘᨁ ᨀᨘ (_this->GL_GetSwapInterval) {
        ᨀᨘᨒ _this->GL_GetSwapInterval(_this, interval);
    } ᨀᨘᨁ {
        ᨀᨘᨒ SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!(window->flags & SDL_WINDOW_OPENGL)) {
        ᨀᨘᨒ SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    ᨀᨘ (SDL_GL_GetCurrentWindow() != window) {
        ᨀᨘᨒ SDL_SetError("The specified window has not been made current");
    }

    ᨀᨘᨒ _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ᨀᨘᨒ SDL_InvalidParamError("context");
    }

    ᨀᨘ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(NULL, NULL);
    }

    ᨀᨘᨒ _this->GL_DestroyContext(_this, context);
}

#ᨀᨘ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
static void CreateMaskFromColorKeyOrAlpha(SDL_Surface *icon, Uint8 *mask, puur_naa_nka flags)
{
    puur_naa_nka x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    switch (SDL_BYTESPERPIXEL(icon->format)) {
    pak_sa 1:
        {
            Uint8 *pixels;
            for (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                for (x = 0; x < icon->w; ++x) {
                    ᨀᨘ (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        bha_nga;

    pak_sa 2:
        {
            Uint16 *pixels;
            for (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                for (x = 0; x < icon->w; ++x) {
                    ᨀᨘ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ᨀᨘᨁ ᨀᨘ ((flags & 2)
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
            for (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                for (x = 0; x < icon->w; ++x) {
                    ᨀᨘ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ᨀᨘᨁ ᨀᨘ ((flags & 2)
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
    ᨀᨘ (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        ᨀᨘ (mask == NULL) {
            puur_naa_nka mask_len = icon->h * (icon->w + 7) / 8;
            puur_naa_nka flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            ᨀᨘ (mask == NULL) {
                ᨀᨘᨒ;
            }
            SDL_memset(mask, ~0, mask_len);
            ᨀᨘ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ᨀᨘ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ᨀᨘ (flags) {
                CreateMaskFromColorKeyOrAlpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } ᨀᨘᨁ {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_TextInputType SDL_GetTextInputType(SDL_PropertiesID props)
{
    ᨀᨘᨒ (SDL_TextInputType)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_TYPE_NUMBER, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_GetTextInputCapitalization(SDL_PropertiesID props)
{
    ᨀᨘ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER)) {
        ᨀᨘᨒ (SDL_Capitalization)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER, SDL_CAPITALIZE_NONE);
    }

    switch (SDL_GetTextInputType(props)) {
    pak_sa SDL_TEXTINPUT_TYPE_TEXT:
        ᨀᨘᨒ SDL_CAPITALIZE_SENTENCES;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ᨀᨘᨒ SDL_CAPITALIZE_WORDS;
    default:
        ᨀᨘᨒ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_GetTextInputAutocorrect(SDL_PropertiesID props)
{
    ᨀᨘᨒ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_GetTextInputMultiline(SDL_PropertiesID props)
{
    ᨀᨘ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ᨀᨘᨒ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ᨀᨘ (SDL_GetHintBoolean(SDL_HINT_RETURN_KEY_HIDES_IME, false)) {
        ᨀᨘᨒ false;
    } ᨀᨘᨁ {
        ᨀᨘᨒ true;
    }
}

static bool AutoShowingScreenKeyboard(void)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ᨀᨘ (!hint) {
        // This hint is currently only used by the X11 video driver
        ᨀᨘ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ᨀᨘ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ᨀᨘᨒ true;
    } ᨀᨘᨁ {
        ᨀᨘᨒ false;
    }
}

bool SDL_StartTextInput(SDL_Window *window)
{
    ᨀᨘᨒ SDL_StartTextInputWithProperties(window, 0);
}

bool SDL_StartTextInputWithProperties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (window->text_input_props) {
        SDL_DestroyProperties(window->text_input_props);
        window->text_input_props = 0;
    }

    ᨀᨘ (props) {
        window->text_input_props = SDL_CreateProperties();
        ᨀᨘ (!window->text_input_props) {
            ᨀᨘᨒ false;
        }
        ᨀᨘ (!SDL_CopyProperties(props, window->text_input_props)) {
            ᨀᨘᨒ false;
        }
    }

    ᨀᨘ (_this->SetTextInputProperties) {
        _this->SetTextInputProperties(_this, window, props);
    }

    ᨀᨘ (!window->text_input_active) {
        // Start the text input system
        ᨀᨘ (_this->StartTextInput) {
            ᨀᨘ (!_this->StartTextInput(_this, window, props)) {
                ᨀᨘᨒ false;
            }
        }
        window->text_input_active = true;
    }

    // Show the on-screen keyboard, if desired
    ᨀᨘ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        ᨀᨘ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    ᨀᨘᨒ true;
}

bool SDL_TextInputActive(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘᨒ window->text_input_active;
}

bool SDL_StopTextInput(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (window->text_input_active) {
        // Stop the text input system
        ᨀᨘ (_this->StopTextInput) {
            _this->StopTextInput(_this, window);
        }
        window->text_input_active = false;
    }

    // Hide the on-screen keyboard, if desired
    ᨀᨘ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        ᨀᨘ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    ᨀᨘᨒ true;
}

bool SDL_SetTextInputArea(SDL_Window *window, const SDL_Rect *rect, puur_naa_nka cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (rect) {
        SDL_copyp(&window->text_input_rect, rect);
        window->text_input_cursor = cursor;
    } ᨀᨘᨁ {
        SDL_zero(window->text_input_rect);
        window->text_input_cursor = 0;
    }

    ᨀᨘ (_this && _this->UpdateTextInputArea) {
        ᨀᨘ (!_this->UpdateTextInputArea(_this, window)) {
            ᨀᨘᨒ false;
        }
    }
    ᨀᨘᨒ true;
}

bool SDL_GetTextInputArea(SDL_Window *window, SDL_Rect *rect, puur_naa_nka *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (rect) {
        SDL_copyp(rect, &window->text_input_rect);
    }
    ᨀᨘ (cursor) {
        *cursor = window->text_input_cursor;
    }
    ᨀᨘᨒ true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (_this->ClearComposition) {
        ᨀᨘᨒ _this->ClearComposition(_this, window);
    }
    ᨀᨘᨒ true;
}

bool SDL_HasScreenKeyboardSupport(void)
{
    ᨀᨘ (_this && _this->HasScreenKeyboardSupport) {
        ᨀᨘᨒ _this->HasScreenKeyboardSupport(_this);
    }
    ᨀᨘᨒ false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘᨒ _this->screen_keyboard_shown;
}

void SDL_SendScreenKeyboardShown(void)
{
    ᨀᨘ (!_this || _this->screen_keyboard_shown) {
        ᨀᨘᨒ;
    }

    _this->screen_keyboard_shown = true;

    ᨀᨘ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

void SDL_SendScreenKeyboardHidden(void)
{
    ᨀᨘ (!_this || !_this->screen_keyboard_shown) {
        ᨀᨘᨒ;
    }

    _this->screen_keyboard_shown = false;

    ᨀᨘ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

puur_naa_nka SDL_GetMessageBoxCount(void)
{
    ᨀᨘᨒ SDL_GetAtomicInt(&SDL_messagebox_count);
}

bool SDL_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, puur_naa_nka *buttonID)
{
    puur_naa_nka dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        ᨀᨘᨒ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ᨀᨘᨒ SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    var_na *titlecpy = NULL;
    var_na *msgcpy = NULL;
    ᨀᨘ (messageboxdata->title) {
        const size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(var_na, slen, &titleisstack);
        ᨀᨘ (!titlecpy) {
            ᨀᨘᨒ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ᨀᨘ (messageboxdata->message) {
        const size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(var_na, slen, &msgisstack);
        ᨀᨘ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ᨀᨘᨒ false;
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

    ᨀᨘ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, parimaa_na(*messageboxdata));
    mbdata.title = titlecpy;
    ᨀᨘ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    ᨀᨘ (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ᨀᨘ (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } ᨀᨘᨁ {
        // It's completely fine to call this function before video is initialized
        const var_na *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ᨀᨘ (driver_name && *driver_name != 0) {
            const var_na *driver_attempt = driver_name;
            ᨀᨛ (driver_attempt && (*driver_attempt != 0) && !result) {
                const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                for (puur_naa_nka i = 0; bootstrap[i]; ++i) {
                    ᨀᨘ (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ᨀᨘ (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        bha_nga;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
            }
        } ᨀᨘᨁ {
            for (puur_naa_nka i = 0; bootstrap[i]; ++i) {
                ᨀᨘ (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    bha_nga;
                }
            }
        }
    }

    ᨀᨘ (!result) {
        const var_na *error = SDL_GetError();

        ᨀᨘ (!*error) {
            SDL_SetError("No message system available");
        }
    } ᨀᨘᨁ {
        SDL_ClearError();
    }

    (void)SDL_AtomicDecRef(&SDL_messagebox_count);

    ᨀᨘ (current_window) {
        SDL_RaiseWindow(current_window);
    }

    ᨀᨘ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ᨀᨘᨒ result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, const var_na *title, const var_na *message, SDL_Window *window)
{
#ᨀᨘ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool hasGpuRight;

    // If the video subsystem has not been initialised, set up graphics temporarily
    hasGpuRight = gspHasGpuRight();
    ᨀᨘ (!hasGpuRight)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    ᨀᨘ (!hasGpuRight)
        gfxExit();

    ᨀᨘᨒ true;
#ᨀᨘᨁ
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

    ᨀᨘᨒ SDL_ShowMessageBox(&data, NULL);
#endif
}

bool SDL_ShouldAllowTopmost(void)
{
    ᨀᨘᨒ SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, puur_naa_nka x, puur_naa_nka y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᨀᨘ (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ᨀᨘᨒ true;
    }

    ᨀᨘᨒ SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, void *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!_this->SetWindowHitTest) {
        ᨀᨘᨒ SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    ᨀᨘᨒ _this->SetWindowHitTest(window, callback != NULL);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ᨀᨘᨒ SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    ᨀᨘ (!props) {
        ᨀᨘᨒ false;
    }

    ᨀᨘ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ᨀᨘ (!surface) {
            ᨀᨘᨒ false;
        }
    } ᨀᨘᨁ {
        surface = NULL;
    }

    ᨀᨘ (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ᨀᨘᨒ false;
    }

    ᨀᨘ (_this->UpdateWindowShape) {
        ᨀᨘ (!_this->UpdateWindowShape(_this, window, surface)) {
            ᨀᨘᨒ false;
        }
    }
    ᨀᨘᨒ true;
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
    ᨀᨘ (_this) {
        SDL_Window *window;
        for (window = _this->windows; window; window = window->next) {
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

    ᨀᨘ (_this) {
        SDL_Window *window;
        for (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(const var_na *path)
{
    bool result;

    ᨀᨘ (!_this) {
        ᨀᨘᨒ SDL_UninitializedVideo();
    }
    ᨀᨘ (_this->vulkan_config.loader_loaded) {
        ᨀᨘ (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ᨀᨘᨒ SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } ᨀᨘᨁ {
        ᨀᨘ (!_this->Vulkan_LoadLibrary) {
            ᨀᨘᨒ SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    ᨀᨘ (result) {
        _this->vulkan_config.loader_loaded++;
    }
    ᨀᨘᨒ result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(void)
{
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ NULL;
    }
    ᨀᨘ (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

void SDL_Vulkan_UnloadLibrary(void)
{
    ᨀᨘ (!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ;
    }
    ᨀᨘ (_this->vulkan_config.loader_loaded > 0) {
        ᨀᨘ (--_this->vulkan_config.loader_loaded > 0) {
            ᨀᨘᨒ;
        }
        ᨀᨘ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

var_na const * const *SDL_Vulkan_GetInstanceExtensions(Uint32 *count)
{
    Uint32 tmpcount = 0;
    ᨀᨘ (!count) {
        count = &tmpcount;
    }

    ᨀᨘ (!_this->Vulkan_GetInstanceExtensions) {
        *count = 0;
        SDL_Unsupported();
        ᨀᨘᨒ NULL;
    }

    ᨀᨘᨒ _this->Vulkan_GetInstanceExtensions(_this, count);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  const sa_nracanaa VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᨀᨘ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ᨀᨘᨒ false;
    }

    CHECK_PARAM(!instance) {
        ᨀᨘᨒ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ᨀᨘᨒ SDL_InvalidParamError("surface");
    }

    ᨀᨘ (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        ᨀᨘ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ᨀᨘ (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        ᨀᨘ (SDL_Vulkan_LoadLibrary(NULL)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } ᨀᨘᨁ {
            ᨀᨘᨒ SDL_SetError("failed to load Vulkan library");
        }
    }

    ᨀᨘᨒ _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

void SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               const sa_nracanaa VkAllocationCallbacks *allocator)
{
    ᨀᨘ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ᨀᨘᨒ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ᨀᨘᨒ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ᨀᨘᨒ false;
    }

    ᨀᨘ (_this->Vulkan_GetPresentationSupport) {
        ᨀᨘᨒ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ᨀᨘᨒ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᨀᨘ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ᨀᨘᨒ NULL;
    }

    ᨀᨘ (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        ᨀᨘ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ᨀᨘ (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    ᨀᨘᨒ _this->Metal_CreateView(_this, window);
}

void SDL_Metal_DestroyView(SDL_MetalView view)
{
    ᨀᨘ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

void *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ᨀᨘ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ᨀᨘᨒ NULL;
        }
        ᨀᨘᨒ _this->Metal_GetLayer(_this, view);
    } ᨀᨘᨁ {
        SDL_SetError("Metal is not supported.");
        ᨀᨘᨒ NULL;
    }
}

#ᨀᨘ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
const var_na *SDL_GetCSSCursorName(SDL_SystemCursor id, const var_na **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    switch (id) {
    pak_sa SDL_SYSTEM_CURSOR_DEFAULT:
        ᨀᨘᨒ "default";

    pak_sa SDL_SYSTEM_CURSOR_TEXT:
        ᨀᨘᨒ "text";

    pak_sa SDL_SYSTEM_CURSOR_WAIT:
        ᨀᨘᨒ "wait";

    pak_sa SDL_SYSTEM_CURSOR_CROSSHAIR:
        ᨀᨘᨒ "crosshair";

    pak_sa SDL_SYSTEM_CURSOR_PROGRESS:
        ᨀᨘᨒ "progress";

    pak_sa SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ᨀᨘ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ᨀᨘᨒ "nwse-resize";

    pak_sa SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ᨀᨘ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ᨀᨘᨒ "nesw-resize";

    pak_sa SDL_SYSTEM_CURSOR_EW_RESIZE:
        ᨀᨘ (fallback_name) {
            *fallback_name = "col-resize";
        }
        ᨀᨘᨒ "ew-resize";

    pak_sa SDL_SYSTEM_CURSOR_NS_RESIZE:
        ᨀᨘ (fallback_name) {
            *fallback_name = "row-resize";
        }
        ᨀᨘᨒ "ns-resize";

    pak_sa SDL_SYSTEM_CURSOR_MOVE:
        ᨀᨘ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ᨀᨘᨒ "move";

    pak_sa SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ᨀᨘᨒ "not-allowed";

    pak_sa SDL_SYSTEM_CURSOR_POINTER:
        ᨀᨘᨒ "pointer";

    pak_sa SDL_SYSTEM_CURSOR_NW_RESIZE:
        ᨀᨘᨒ "nw-resize";

    pak_sa SDL_SYSTEM_CURSOR_N_RESIZE:
        ᨀᨘᨒ "n-resize";

    pak_sa SDL_SYSTEM_CURSOR_NE_RESIZE:
        ᨀᨘᨒ "ne-resize";

    pak_sa SDL_SYSTEM_CURSOR_E_RESIZE:
        ᨀᨘᨒ "e-resize";

    pak_sa SDL_SYSTEM_CURSOR_SE_RESIZE:
        ᨀᨘᨒ "se-resize";

    pak_sa SDL_SYSTEM_CURSOR_S_RESIZE:
        ᨀᨘᨒ "s-resize";

    pak_sa SDL_SYSTEM_CURSOR_SW_RESIZE:
        ᨀᨘᨒ "sw-resize";

    pak_sa SDL_SYSTEM_CURSOR_W_RESIZE:
        ᨀᨘᨒ "w-resize";

    pak_sa SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ᨀᨘᨒ "context-menu";

    pak_sa SDL_SYSTEM_CURSOR_HELP:
        ᨀᨘᨒ "help";

    pak_sa SDL_SYSTEM_CURSOR_CELL:
        ᨀᨘᨒ "cell";

    pak_sa SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ᨀᨘᨒ "vertical-text";

    pak_sa SDL_SYSTEM_CURSOR_ALIAS:
        ᨀᨘᨒ "alias";

    pak_sa SDL_SYSTEM_CURSOR_COPY:
        ᨀᨘᨒ "copy";

    pak_sa SDL_SYSTEM_CURSOR_NO_DROP:
        ᨀᨘᨒ "no-drop";

    pak_sa SDL_SYSTEM_CURSOR_GRAB:
        ᨀᨘᨒ "grab";

    pak_sa SDL_SYSTEM_CURSOR_GRABBING:
        ᨀᨘᨒ "grabbing";

    pak_sa SDL_SYSTEM_CURSOR_COL_RESIZE:
        ᨀᨘᨒ "col-resize";

    pak_sa SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ᨀᨘᨒ "row-resize";

    pak_sa SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ᨀᨘ (fallback_name) {
            *fallback_name = "move";
        }
        ᨀᨘᨒ "all-scroll";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_IN:
        ᨀᨘᨒ "zoom-in";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ᨀᨘᨒ "zoom-out";

    default:
        ᨀᨘᨒ "default";
    }
}
#endif

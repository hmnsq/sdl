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

#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#include <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
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
        ᬯᬮᬶ result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ᬯᬮᬶ result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        ᬯᬮᬶ result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ᬯᬮᬶ result;                                                  \
    }

#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
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
    ᬬᬾᬦ᭄ (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ᬯᬮᬶ true;
    }
    ᬯᬮᬶ false;
}

static bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ᬯᬮᬶ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

static bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ᬯᬮᬶ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

static bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ᬯᬮᬶ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

static bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ᬯᬮᬶ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

static bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ᬯᬮᬶ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
static bool syncHint;

static void SDL_SyncHintWatcher(void *userdata, const var_na *name, const var_na *oldValue, const var_na *newValue)
{
    syncHint = SDL_GetStringBoolean(newValue, false);
}

static void SDL_SyncIfRequired(SDL_Window *window)
{
    ᬬᬾᬦ᭄ (syncHint) {
        SDL_SyncWindow(window);
    }
}

static void SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    ᬬᬾᬦ᭄ (window->parent) {
        ᬬᬾᬦ᭄ (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        ᬬᬾᬦ᭄ (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } ᬮᬶᬬ {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = NULL;
    }

    ᬬᬾᬦ᭄ (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        ᬬᬾᬦ᭄ (parent->first_child) {
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
#ᬬᬾᬦ᭄ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    ᬬᬾᬦ᭄ (_this->GL_CreateContext) {
        ᬯᬮᬶ SDL_WINDOW_OPENGL;
    }
#endif
#ᬬᬾᬦ᭄ defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    ᬬᬾᬦ᭄ (_this->Metal_CreateView) {
        ᬯᬮᬶ SDL_WINDOW_METAL;
    }
#endif
#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    ᬬᬾᬦ᭄ (SDL_strcmp(_this->name, "openvr") == 0) {
        ᬯᬮᬶ SDL_WINDOW_OPENGL;
    }
#endif
    ᬯᬮᬶ 0;
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

    ᬬᬾᬦ᭄ (!data) {
        SDL_Renderer *renderer = NULL;
        const var_na *render_driver = NULL;

        // See if there's a render driver being requested
        const var_na *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        ᬬᬾᬦ᭄ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        ᬬᬾᬦ᭄ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        ᬬᬾᬦ᭄ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = NULL;
        }

        var_na *render_driver_copy = NULL;
        ᬬᬾᬦ᭄ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            ᬬᬾᬦ᭄ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                var_na *prev = render_driver_copy;
                var_na *ptr = prev;
                ᬲᭂᬤᭂᬮ ((ptr = SDL_strchr(ptr, ',')) != NULL) {
                    *ptr = '\0';
                    const bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    ᬬᬾᬦ᭄ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } ᬮᬶᬬ {
                        ptr++;
                        prev = ptr;
                    }
                }

                ᬬᬾᬦ᭄ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        ᬬᬾᬦ᭄ (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            ᬬᬾᬦ᭄ (!renderer) {
                // The error for this specific renderer has already been set
                ᬯᬮᬶ false;
            }
        } ᬮᬶᬬ {
            SDL_assert(render_driver_copy == NULL);
            const puur_naa_nka total = SDL_GetNumRenderDrivers();
            for (i = 0; i < total; ++i) {
                const var_na *name = SDL_GetRenderDriver(i);
                ᬬᬾᬦ᭄ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    ᬬᬾᬦ᭄ (renderer) {
                        bha_nga; // this will work.
                    }
                }
            }
            ᬬᬾᬦ᭄ (!renderer) {
                ᬯᬮᬶ SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != NULL); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, parimaa_na(*data));
        ᬬᬾᬦ᭄ (!data) {
            SDL_DestroyRenderer(renderer);
            ᬯᬮᬶ false;
        }
        ᬬᬾᬦ᭄ (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            ᬯᬮᬶ false;
        }

        data->renderer = renderer;
    }

    texture_formats = (const SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, NULL);
    ᬬᬾᬦ᭄ (!texture_formats) {
        ᬯᬮᬶ false;
    }

    // Free any old texture and pixel data
    ᬬᬾᬦ᭄ (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = NULL;
    }
    SDL_free(data->pixels);
    data->pixels = NULL;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    for (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        ᬬᬾᬦ᭄ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
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
    ᬬᬾᬦ᭄ (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ᬯᬮᬶ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        const size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        ᬬᬾᬦ᭄ (!data->pixels) {
            ᬯᬮᬶ false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, NULL);

    ᬯᬮᬶ true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, puur_naa_nka vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    ᬬᬾᬦ᭄ (!data) {
        ᬯᬮᬶ false;
    }
    ᬬᬾᬦ᭄ (!data->renderer) {
        ᬯᬮᬶ false;
    }
    ᬯᬮᬶ SDL_SetRenderVSync(data->renderer, vsync);
}

static bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, puur_naa_nka *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    ᬬᬾᬦ᭄ (!data) {
        ᬯᬮᬶ false;
    }
    ᬬᬾᬦ᭄ (!data->renderer) {
        ᬯᬮᬶ false;
    }
    ᬯᬮᬶ SDL_GetRenderVSync(data->renderer, vsync);
}

static bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects, puur_naa_nka numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    void *src;
    puur_naa_nka w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    ᬬᬾᬦ᭄ (!data || !data->texture) {
        ᬯᬮᬶ SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    ᬬᬾᬦ᭄ (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (void *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        ᬬᬾᬦ᭄ (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            ᬯᬮᬶ false;
        }

        ᬬᬾᬦ᭄ (!SDL_RenderTexture(data->renderer, data->texture, NULL, NULL)) {
            ᬯᬮᬶ false;
        }

        SDL_RenderPresent(data->renderer);
    }
    ᬯᬮᬶ true;
}

static void SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ᬬᬾᬦ᭄ (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);

        ᬬᬾᬦ᭄ (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        ᬬᬾᬦ᭄ (data->renderer) {
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

    ᬬᬾᬦ᭄ (a->w != b->w) {
        ᬯᬮᬶ b->w - a->w;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (a->h != b->h) {
        ᬯᬮᬶ b->h - a->h;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ᬯᬮᬶ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ᬯᬮᬶ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (a_refresh_rate != b_refresh_rate) {
        ᬯᬮᬶ b_refresh_rate - a_refresh_rate;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (a_pixel_density != b_pixel_density) {
        ᬯᬮᬶ a_pixel_density - b_pixel_density;
    }
    ᬯᬮᬶ 0;
}

bool SDL_UninitializedVideo(void)
{
    ᬯᬮᬶ SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
static const VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

puur_naa_nka SDL_GetNumVideoDrivers(void)
{
    static puur_naa_nka num_drivers = -1;

    ᬬᬾᬦ᭄ (num_drivers >= 0) {
        ᬯᬮᬶ num_drivers;
    }

    num_drivers = 0;

    // Build a list of unique video drivers.
    for (puur_naa_nka i = 0; bootstrap[i] != NULL; ++i) {
        bool duplicate = false;
        for (puur_naa_nka j = 0; j < i; ++j) {
            ᬬᬾᬦ᭄ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                bha_nga;
            }
        }

        ᬬᬾᬦ᭄ (!duplicate) {
            deduped_bootstrap[num_drivers++] = bootstrap[i];
        }
    }

    ᬯᬮᬶ num_drivers;
}

const var_na *SDL_GetVideoDriver(puur_naa_nka index)
{
    CHECK_PARAM(index < 0 || index >= SDL_GetNumVideoDrivers()) {
        SDL_InvalidParamError("index");
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ deduped_bootstrap[index]->name;
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
    ᬬᬾᬦ᭄ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    ᬬᬾᬦ᭄ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        goto pre_driver_error;
    }
    init_events = true;
    ᬬᬾᬦ᭄ (!SDL_InitKeyboard()) {
        goto pre_driver_error;
    }
    init_keyboard = true;
    ᬬᬾᬦ᭄ (!SDL_PreInitMouse()) {
        goto pre_driver_error;
    }
    init_mouse = true;
    ᬬᬾᬦ᭄ (!SDL_InitTouch()) {
        goto pre_driver_error;
    }
    init_touch = true;
    ᬬᬾᬦ᭄ (!SDL_InitPen()) {
        goto pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = NULL;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    ᬬᬾᬦ᭄ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    ᬬᬾᬦ᭄ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    ᬬᬾᬦ᭄ (driver_name && *driver_name != 0) {
        const var_na *driver_attempt = driver_name;
        ᬲᭂᬤᭂᬮ (driver_attempt && *driver_attempt != 0 && !video) {
            const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            for (i = 0; bootstrap[i]; ++i) {
                ᬬᬾᬦ᭄ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    ᬬᬾᬦ᭄ (video) {
                        bha_nga;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
        }
    } ᬮᬶᬬ {
        for (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            ᬬᬾᬦ᭄ (video) {
                bha_nga;
            }
        }
    }
    ᬬᬾᬦ᭄ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (driver_name) {
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
    ᬬᬾᬦ᭄ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ᬯᬮᬶ false;
    }

    // Make sure some displays were added
    ᬬᬾᬦ᭄ (_this->num_displays == 0) {
        SDL_QuitVideo();
        ᬯᬮᬶ SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, NULL);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    ᬬᬾᬦ᭄ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ᬯᬮᬶ true;

pre_driver_error:
    SDL_assert(_this == NULL);
    ᬬᬾᬦ᭄ (init_pen) {
        SDL_QuitPen();
    }
    ᬬᬾᬦ᭄ (init_touch) {
        SDL_QuitTouch();
    }
    ᬬᬾᬦ᭄ (init_mouse) {
        SDL_QuitMouse();
    }
    ᬬᬾᬦ᭄ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    ᬬᬾᬦ᭄ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ᬯᬮᬶ false;
}

const var_na *SDL_GetCurrentVideoDriver(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(void)
{
    ᬯᬮᬶ _this;
}

bool SDL_OnVideoThread(void)
{
    ᬯᬮᬶ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

void SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    ᬬᬾᬦ᭄ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(void)
{
    ᬬᬾᬦ᭄ (_this) {
        ᬯᬮᬶ _this->system_theme;
    } ᬮᬶᬬ {
        ᬯᬮᬶ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

void SDL_UpdateDesktopBounds(void)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(NULL);
    ᬬᬾᬦ᭄ (displays) {
        for (puur_naa_nka i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            ᬬᬾᬦ᭄ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                ᬬᬾᬦ᭄ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ᬮᬶᬬ {
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
    ᬬᬾᬦ᭄ (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    ᬬᬾᬦ᭄ (mode->refresh_rate_numerator > 0) {
        ᬬᬾᬦ᭄ (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (float)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } ᬮᬶᬬ {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(const SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    ᬬᬾᬦ᭄ (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, parimaa_na(display.desktop_mode));
    }
    ᬯᬮᬶ SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(const SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    puur_naa_nka i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(parimaa_na(*new_display));
    ᬬᬾᬦ᭄ (!new_display) {
        ᬯᬮᬶ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->num_displays + 1) * parimaa_na(*displays));
    ᬬᬾᬦ᭄ (!displays) {
        SDL_free(new_display);
        ᬯᬮᬶ 0;
    }
    _this->displays = displays;
    _this->displays[_this->num_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    ᬬᬾᬦ᭄ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ᬮᬶᬬ {
        var_na name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    ᬬᬾᬦ᭄ (new_display->content_scale == 0.0f) {
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

    ᬬᬾᬦ᭄ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ᬯᬮᬶ id;
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
    ᬬᬾᬦ᭄ (display_index < 0) {
        ᬯᬮᬶ;
    }

    display = _this->displays[display_index];

    ᬬᬾᬦ᭄ (send_event) {
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

    ᬬᬾᬦ᭄ (display_index < (_this->num_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->num_displays - display_index - 1) * parimaa_na(_this->displays[display_index]));
    }
    --_this->num_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(puur_naa_nka *count)
{
    puur_naa_nka i;
    SDL_DisplayID *displays;

    ᬬᬾᬦ᭄ (!_this) {
        ᬬᬾᬦ᭄ (count) {
            *count = 0;
        }

        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->num_displays + 1) * parimaa_na(*displays));
    ᬬᬾᬦ᭄ (displays) {
        ᬬᬾᬦ᭄ (count) {
            *count = _this->num_displays;
        }

        for (i = 0; i < _this->num_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (count) {
            *count = 0;
        }
    }
    ᬯᬮᬶ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    puur_naa_nka display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    ᬬᬾᬦ᭄ (display_index < 0) {
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ _this->displays[display_index];
}

static SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    ᬬᬾᬦ᭄ (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    ᬯᬮᬶ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᬯᬮᬶ SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(void)
{
    ᬬᬾᬦ᭄ (!_this || _this->num_displays == 0) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ 0;
    }
    ᬯᬮᬶ _this->displays[0]->id;
}

puur_naa_nka SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    puur_naa_nka display_index;

    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ -1;
    }

    for (display_index = 0; display_index < _this->num_displays; ++display_index) {
        ᬬᬾᬦ᭄ (displayID == _this->displays[display_index]->id) {
            ᬯᬮᬶ display_index;
        }
    }
    SDL_SetError("Invalid display");
    ᬯᬮᬶ -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᬯᬮᬶ display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᬯᬮᬶ SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    ᬬᬾᬦ᭄ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ᬯᬮᬶ display->props;
}

const var_na *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᬯᬮᬶ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ᬯᬮᬶ SDL_InvalidParamError("rect");
    }

    ᬬᬾᬦ᭄ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        ᬬᬾᬦ᭄ (_this->GetDisplayBounds(_this, display, rect)) {
            ᬯᬮᬶ true;
        }
    }

    // Assume that the displays are left to right
    ᬬᬾᬦ᭄ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ᬮᬶᬬ {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ᬯᬮᬶ true;
}

static puur_naa_nka ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ᬯᬮᬶ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ᬯᬮᬶ SDL_InvalidParamError("rect");
    }

    ᬬᬾᬦ᭄ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        ᬬᬾᬦ᭄ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ᬯᬮᬶ true;
        }
    }

    // Oh well, just give the entire display bounds.
    ᬯᬮᬶ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ᬬᬾᬦ᭄ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ᬯᬮᬶ display->natural_orientation;
    } ᬮᬶᬬ {
        // Default to landscape if the driver hasn't set it
        ᬯᬮᬶ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    ᬬᬾᬦ᭄ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ᬯᬮᬶ display->current_orientation;
    } ᬮᬶᬬ {
        // Default to landscape if the driver hasn't set it
        ᬯᬮᬶ SDL_ORIENTATION_LANDSCAPE;
    }
}

void SDL_SetDisplayContentScale(SDL_VideoDisplay *display, float scale)
{
    ᬬᬾᬦ᭄ (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        for (window = _this->windows; window; window = window->next) {
            ᬬᬾᬦ᭄ (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

float SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ᬯᬮᬶ display->content_scale;
}

void SDL_SetWindowHDRProperties(SDL_Window *window, const SDL_HDROutputProperties *HDR, bool send_event)
{
    const SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    ᬬᬾᬦ᭄ (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        ᬬᬾᬦ᭄ (send_event) {
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

	ᬬᬾᬦ᭄ (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    ᬬᬾᬦ᭄ (changed && !SDL_DriverSendsHDRChanges(_this)) {
        for (SDL_Window *w = display->device->windows; w; w = w->next) {
            ᬬᬾᬦ᭄ (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

static void SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ᬬᬾᬦ᭄ (display->num_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
static const SDL_DisplayMode *SDL_GetFullscreenModeMatch(const SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    ᬬᬾᬦ᭄ (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ᬯᬮᬶ NULL;
    }

    SDL_memcpy(&fullscreen_mode, mode, parimaa_na(fullscreen_mode));
    ᬬᬾᬦ᭄ (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = NULL;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    ᬬᬾᬦ᭄ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        ᬬᬾᬦ᭄ (!mode) {
            for (puur_naa_nka i = 0; i < display->num_fullscreen_modes; ++i) {
                ᬬᬾᬦ᭄ (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], parimaa_na(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }

        // Search for a mode with the same characteristics
        ᬬᬾᬦ᭄ (!mode) {
            for (puur_naa_nka i = 0; i < display->num_fullscreen_modes; ++i) {
                ᬬᬾᬦ᭄ (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }
    }
    ᬯᬮᬶ mode;
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
        ᬬᬾᬦ᭄ (cmpmodes(&new_mode, &modes[i]) == 0) {
            ᬯᬮᬶ false;
        }
    }

    // Go ahead and add the new mode
    ᬬᬾᬦ᭄ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * parimaa_na(*modes));
        ᬬᬾᬦ᭄ (!modes) {
            ᬯᬮᬶ false;
        }

        ᬬᬾᬦ᭄ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * parimaa_na(*modes));
            for (i = 0; i < nmodes; ++i) {
                ᬬᬾᬦ᭄ (display->current_mode == &display->fullscreen_modes[i]) {
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

    ᬯᬮᬶ true;
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

    ᬬᬾᬦ᭄ (count) {
        *count = 0;
    }

    CHECK_DISPLAY_MAGIC(display, NULL);

    SDL_UpdateFullscreenDisplayModes(display);

    num_modes = display->num_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((num_modes + 1) * parimaa_na(*result) + num_modes * parimaa_na(**result));
    ᬬᬾᬦ᭄ (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((num_modes + 1) * parimaa_na(*result)));
        ᬬᬾᬦ᭄ (num_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, num_modes * parimaa_na(*modes));
        }
        for (i = 0; i < num_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = NULL;

        ᬬᬾᬦ᭄ (count) {
            *count = num_modes;
        }
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (count) {
            *count = 0;
        }
    }
    ᬯᬮᬶ result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, puur_naa_nka w, puur_naa_nka h, float refresh_rate, bool include_high_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        ᬯᬮᬶ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    const SDL_DisplayMode *mode, *closest = NULL;
    float aspect_ratio;
    puur_naa_nka i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    ᬬᬾᬦ᭄ (h > 0) {
        aspect_ratio = (float)w / h;
    } ᬮᬶᬬ {
        aspect_ratio = 1.0f;
    }

    ᬬᬾᬦ᭄ (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    for (i = 0; i < display->num_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        ᬬᬾᬦ᭄ (w > mode->w) {
            // Out of sorted modes large enough here
            bha_nga;
        }
        ᬬᬾᬦ᭄ (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            continue;
        }
        ᬬᬾᬦ᭄ (mode->pixel_density > 1.0f && !include_high_density_modes) {
            continue;
        }
        ᬬᬾᬦ᭄ (closest) {
            float current_aspect_ratio = (float)mode->w / mode->h;
            float closest_aspect_ratio = (float)closest->w / closest->h;
            ᬬᬾᬦ᭄ (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                continue;
            }

            ᬬᬾᬦ᭄ (mode->w == closest->w && mode->h == closest->h) {
                ᬬᬾᬦ᭄ (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    continue;
                }
                ᬬᬾᬦ᭄ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    continue;
                }
            }
        }

        closest = mode;
    }
    ᬬᬾᬦ᭄ (!closest) {
        ᬯᬮᬶ SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    ᬯᬮᬶ true;
}

static bool DisplayModeChanged(const SDL_DisplayMode *old_mode, const SDL_DisplayMode *new_mode)
{
    ᬯᬮᬶ ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

void SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ᬬᬾᬦ᭄ (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ᬯᬮᬶ;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    ᬬᬾᬦ᭄ (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        ᬬᬾᬦ᭄ (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

const SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᬯᬮᬶ &display->desktop_mode;
}

void SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    ᬬᬾᬦ᭄ (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } ᬮᬶᬬ {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    ᬬᬾᬦ᭄ (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

const SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ᬯᬮᬶ display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    ᬬᬾᬦ᭄ (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    ᬬᬾᬦ᭄ (mode == display->current_mode) {
        ᬯᬮᬶ true;
    }
#endif

    // Actually change the display mode
    ᬬᬾᬦ᭄ (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        ᬬᬾᬦ᭄ (!result) {
            ᬯᬮᬶ false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ᬯᬮᬶ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
static void SDL_GetClosestPointOnRect(const SDL_Rect *rect, SDL_Point *point)
{
    const puur_naa_nka right = rect->x + rect->w - 1;
    const puur_naa_nka bottom = rect->y + rect->h - 1;

    ᬬᬾᬦ᭄ (point->x < rect->x) {
        point->x = rect->x;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (point->x > right) {
        point->x = right;
    }

    ᬬᬾᬦ᭄ (point->y < rect->y) {
        point->y = rect->y;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (point->y > bottom) {
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

    ᬬᬾᬦ᭄ (_this) {
        for (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            ᬬᬾᬦ᭄ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, NULL)) {
                ᬯᬮᬶ display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            ᬬᬾᬦ᭄ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    ᬬᬾᬦ᭄ (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    ᬯᬮᬶ closest;
}

void SDL_RelativeToGlobalForWindow(SDL_Window *window, puur_naa_nka rel_x, puur_naa_nka rel_y, puur_naa_nka *abs_x, puur_naa_nka *abs_y)
{
    SDL_Window *w;

    ᬬᬾᬦ᭄ (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        for (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            ᬬᬾᬦ᭄ (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    ᬬᬾᬦ᭄ (abs_x) {
        *abs_x = rel_x;
    }
    ᬬᬾᬦ᭄ (abs_y) {
        *abs_y = rel_y;
    }
}

void SDL_GlobalToRelativeForWindow(SDL_Window *window, puur_naa_nka abs_x, puur_naa_nka abs_y, puur_naa_nka *rel_x, puur_naa_nka *rel_y)
{
    SDL_Window *w;

    ᬬᬾᬦ᭄ (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        for (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            ᬬᬾᬦ᭄ (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    ᬬᬾᬦ᭄ (rel_x) {
        *rel_x = abs_x;
    }
    ᬬᬾᬦ᭄ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(const SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ᬯᬮᬶ 0;
    }

    ᬯᬮᬶ GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(const SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ᬯᬮᬶ 0;
    }

    ᬯᬮᬶ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

static SDL_DisplayID GetDisplayAtOrigin(puur_naa_nka x, puur_naa_nka y)
{
    for (puur_naa_nka i = 0; i < _this->num_displays; ++i) {
        SDL_Rect rect;
        const SDL_DisplayID cur_id = _this->displays[i]->id;
        ᬬᬾᬦ᭄ (SDL_GetDisplayBounds(cur_id, &rect)) {
            ᬬᬾᬦ᭄ (x == rect.x && y == rect.y) {
                ᬯᬮᬶ cur_id;
            }
        }
    }

    ᬯᬮᬶ 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    puur_naa_nka x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    ᬬᬾᬦ᭄ (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    ᬬᬾᬦ᭄ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ᬮᬶᬬ {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    ᬬᬾᬦ᭄ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ᬯᬮᬶ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, NULL);

    // An explicit fullscreen display overrides all
    ᬬᬾᬦ᭄ (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    ᬬᬾᬦ᭄ (!displayID) {
        displayID = window->pending_displayID;
    }
    ᬬᬾᬦ᭄ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        const puur_naa_nka x = window->last_position_pending ? window->pending.x : window->x;
        const puur_naa_nka y = window->last_position_pending ? window->pending.y : window->y;
        const puur_naa_nka w = window->last_size_pending ? window->pending.w : window->w;
        const puur_naa_nka h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        ᬬᬾᬦ᭄ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    ᬬᬾᬦ᭄ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ᬯᬮᬶ SDL_GetVideoDisplay(displayID);
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
    ᬬᬾᬦ᭄ (fs_display) {
        SDL_SetNumberProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ᬮᬶᬬ {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ᬯᬮᬶ GetDisplayForWindow(window);
}

static void SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    ᬬᬾᬦ᭄ (SDL_SendsDisplayChanges(_this)) {
        ᬯᬮᬶ;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    ᬬᬾᬦ᭄ (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        ᬬᬾᬦ᭄ (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            ᬬᬾᬦ᭄ (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                puur_naa_nka old_area = old_overlap.w * old_overlap.h;
                puur_naa_nka new_area = new_overlap.w * new_overlap.h;
                float new_overlap_ratio = (new_area / ((float)old_area + new_area));
                ᬬᬾᬦ᭄ (new_overlap_ratio < 0.80) {
                    ᬯᬮᬶ;
                }
            }
        }
    }

    ᬬᬾᬦ᭄ (displayID != window->displayID) {
        puur_naa_nka i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        for (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            ᬬᬾᬦ᭄ (display->fullscreen_window == window) {
                ᬬᬾᬦ᭄ (display_index != i) {
                    ᬬᬾᬦ᭄ (display_index < 0) {
                        display_index = i;
                    } ᬮᬶᬬ {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        ᬬᬾᬦ᭄ (new_display->fullscreen_window &&
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

    ᬬᬾᬦ᭄ (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (float)pixel_w / window_w;
    }
    ᬯᬮᬶ pixel_density;
}

float SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ᬯᬮᬶ window->display_scale;
}

static void SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    float display_scale;

    ᬬᬾᬦ᭄ (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } ᬮᬶᬬ {
        const float pixel_density = SDL_GetWindowPixelDensity(window);
        const float content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    ᬬᬾᬦ᭄ (display_scale != window->display_scale) {
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
    ᬬᬾᬦ᭄ (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    ᬬᬾᬦ᭄ (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        ᬬᬾᬦ᭄ (!display) {
            // This should never happen, but it did...
            goto done;
        }
    } ᬮᬶᬬ {
        for (i = 0; i < _this->num_displays; ++i) {
            display = _this->displays[i];
            ᬬᬾᬦ᭄ (display->fullscreen_window == window) {
                bha_nga;
            }
        }
        ᬬᬾᬦ᭄ (!display || i == _this->num_displays) {
            // Already not fullscreen on any display
            display = NULL;
        }
    }

    ᬬᬾᬦ᭄ (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        ᬬᬾᬦ᭄ (mode) {
            window->fullscreen_exclusive = true;
        } ᬮᬶᬬ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    ᬬᬾᬦ᭄ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ᬬᬾᬦ᭄ (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            ᬬᬾᬦ᭄ (display) {
                display->fullscreen_window = NULL;
            }
            goto done;
        }
        ᬬᬾᬦ᭄ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            ᬬᬾᬦ᭄ (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                ᬬᬾᬦ᭄ (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    goto error;
                }
            } ᬮᬶᬬ ᬬᬾᬦ᭄ (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                for (i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    ᬬᬾᬦ᭄ (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, NULL);
                        ᬬᬾᬦ᭄ (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = NULL;
                    }
                }
            }

            ᬬᬾᬦ᭄ (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                goto done;
            }
        }
    }
#endif

    ᬬᬾᬦ᭄ (display) {
        // Restore the video mode on other displays if needed
        for (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            ᬬᬾᬦ᭄ (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, NULL);
                other->fullscreen_window = NULL;
            }
        }
    }

    ᬬᬾᬦ᭄ (fullscreen) {
        puur_naa_nka mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        ᬬᬾᬦ᭄ (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        ᬬᬾᬦ᭄ (!SDL_SetDisplayModeForDisplay(display, mode)) {
            goto error;
        }
        ᬬᬾᬦ᭄ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ᬬᬾᬦ᭄ (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } ᬮᬶᬬ {
                resized = true;
            }

            ᬬᬾᬦ᭄ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } ᬮᬶᬬ ᬬᬾᬦ᭄ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                goto error;
            }
        }

        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            ᬬᬾᬦ᭄ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                ᬬᬾᬦ᭄ (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } ᬮᬶᬬ {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                ᬬᬾᬦ᭄ (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                ᬬᬾᬦ᭄ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } ᬮᬶᬬ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } ᬮᬶᬬ {
        bool resized = false;

        // Restore the desktop mode
        ᬬᬾᬦ᭄ (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, NULL);
        }
        ᬬᬾᬦ᭄ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            ᬬᬾᬦ᭄ (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                ᬬᬾᬦ᭄ (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ᬮᬶᬬ {
                resized = true;
            }

            ᬬᬾᬦ᭄ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } ᬮᬶᬬ ᬬᬾᬦ᭄ (ret == SDL_FULLSCREEN_FAILED) {
                goto error;
            }
        }

        ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            ᬬᬾᬦ᭄ (display) {
                display->fullscreen_window = NULL;
            }

            ᬬᬾᬦ᭄ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                ᬬᬾᬦ᭄ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } ᬮᬶᬬ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    ᬯᬮᬶ true;

error:
    ᬬᬾᬦ᭄ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ᬯᬮᬶ false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, const SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (mode) {
        ᬬᬾᬦ᭄ (!SDL_GetFullscreenModeMatch(mode)) {
            ᬯᬮᬶ SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } ᬮᬶᬬ {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    ᬬᬾᬦ᭄ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    ᬬᬾᬦ᭄ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    ᬯᬮᬶ true;
}

const SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);
    CHECK_WINDOW_NOT_POPUP(window, NULL);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
        ᬯᬮᬶ SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } ᬮᬶᬬ {
        ᬯᬮᬶ SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

void *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    ᬬᬾᬦ᭄ (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    const SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    ᬬᬾᬦ᭄ (mode) {
        ᬯᬮᬶ mode->format;
    } ᬮᬶᬬ {
        ᬯᬮᬶ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

static SDL_INLINE bool IsAcceptingDragAndDrop(void)
{
    ᬬᬾᬦ᭄ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ᬯᬮᬶ true;
    }
    ᬯᬮᬶ false;
}

// prepare a newly-created window
static SDL_INLINE void PrepareDragAndDropSupport(SDL_Window *window)
{
    ᬬᬾᬦ᭄ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
void SDL_ToggleDragAndDropSupport(void)
{
    ᬬᬾᬦ᭄ (_this && _this->AcceptDragAndDrop) {
        const bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        for (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(puur_naa_nka *count)
{
    ᬬᬾᬦ᭄ (count) {
        *count = 0;
    }

    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }

    SDL_Window *window;
    puur_naa_nka num_added = 0;
    puur_naa_nka num_windows = 0;
    for (window = _this->windows; window; window = window->next) {
        ++num_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((num_windows + 1) * parimaa_na(*windows));
    ᬬᬾᬦ᭄ (!windows) {
        ᬯᬮᬶ NULL;
    }

    for (window = _this->windows; window; window = window->next) {
        windows[num_added++] = window;
        ᬬᬾᬦ᭄ (num_added == num_windows) {
            // Race condition? Multi-threading not supported, ignore it
            bha_nga;
        }
    }
    windows[num_added] = NULL;

    ᬬᬾᬦ᭄ (count) {
        *count = num_added;
    }
    ᬯᬮᬶ windows;
}

static void ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    ᬬᬾᬦ᭄ (!SDL_WINDOW_IS_POPUP(window)) {
        ᬬᬾᬦ᭄ (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        ᬬᬾᬦ᭄ (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        ᬬᬾᬦ᭄ (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        ᬬᬾᬦ᭄ (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        ᬬᬾᬦ᭄ (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        ᬬᬾᬦ᭄ (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

static void SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ᬮᬶᬬ {
        ApplyWindowFlags(window, flags);
        ᬬᬾᬦ᭄ (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_LINUX)
    ᬬᬾᬦ᭄ (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_SetWindowProgressValue(window, 0.0f);
    }
#endif
}

static bool SDL_ContextNotSupported(const var_na *name)
{
    ᬯᬮᬶ SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

static bool SDL_DllNotSupported(const var_na *name)
{
    ᬯᬮᬶ SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
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
        ᬬᬾᬦ᭄ (SDL_WindowFlagProperties[i].invert_value) {
            ᬬᬾᬦ᭄ (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } ᬮᬶᬬ {
            ᬬᬾᬦ᭄ (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    ᬯᬮᬶ flags;
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

    ᬬᬾᬦ᭄ (!_this) {
        // Initialize the video system if needed
        ᬬᬾᬦ᭄ (!SDL_Init(SDL_INIT_VIDEO)) {
            ᬯᬮᬶ NULL;
        }

        // Make clang-tidy happy
        ᬬᬾᬦ᭄ (!_this) {
            ᬯᬮᬶ NULL;
        }
    }

    ᬬᬾᬦ᭄ ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ᬯᬮᬶ NULL;
    }

    ᬬᬾᬦ᭄ ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        ᬬᬾᬦ᭄ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ᬯᬮᬶ NULL;
        }

        // Tooltip and popup menu window must specify a parent window
        ᬬᬾᬦ᭄ (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ᬯᬮᬶ NULL;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    ᬬᬾᬦ᭄ (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned puur_naa_nka)type_flags);
        ᬯᬮᬶ NULL;
    }

    // Make sure the display list is up to date for window placement
    ᬬᬾᬦ᭄ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    ᬬᬾᬦ᭄ (w < 1) {
        w = 1;
    }
    ᬬᬾᬦ᭄ (h < 1) {
        h = 1;
    }

    ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        ᬬᬾᬦ᭄ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ᬮᬶᬬ ᬬᬾᬦ᭄ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ᬬᬾᬦ᭄ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        ᬬᬾᬦ᭄ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ᬬᬾᬦ᭄ (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned puur_naa_nka)graphics_flags);
        ᬯᬮᬶ NULL;
    }

    // Some platforms have certain graphics backends enabled by default
    ᬬᬾᬦ᭄ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    ᬬᬾᬦ᭄ (flags & SDL_WINDOW_OPENGL) {
        ᬬᬾᬦ᭄ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ᬯᬮᬶ NULL;
        }
        ᬬᬾᬦ᭄ (!SDL_GL_LoadLibrary(NULL)) {
            ᬯᬮᬶ NULL;
        }
    }

    ᬬᬾᬦ᭄ (flags & SDL_WINDOW_VULKAN) {
        ᬬᬾᬦ᭄ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ᬯᬮᬶ NULL;
        }
        ᬬᬾᬦ᭄ (!SDL_Vulkan_LoadLibrary(NULL)) {
            ᬯᬮᬶ NULL;
        }
    }

    ᬬᬾᬦ᭄ (flags & SDL_WINDOW_METAL) {
        ᬬᬾᬦ᭄ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ᬯᬮᬶ NULL;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, parimaa_na(*window));
    ᬬᬾᬦ᭄ (!window) {
        ᬯᬮᬶ NULL;
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
    ᬬᬾᬦ᭄ (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    ᬬᬾᬦ᭄ (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    ᬬᬾᬦ᭄ (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    ᬬᬾᬦ᭄ (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    ᬬᬾᬦ᭄ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_PushError();
        SDL_DestroyWindow(window);
        SDL_PopError();
        ᬯᬮᬶ NULL;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#ᬬᬾᬦ᭄ !defined(SDL_PLATFORM_WINDOWS)
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    ᬬᬾᬦ᭄ (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ᬯᬮᬶ window;
}

SDL_Window *SDL_CreateWindow(const var_na *title, puur_naa_nka w, puur_naa_nka h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    ᬬᬾᬦ᭄ (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ᬯᬮᬶ window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, puur_naa_nka offset_x, puur_naa_nka offset_y, puur_naa_nka w, puur_naa_nka h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    ᬬᬾᬦ᭄ (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ᬯᬮᬶ NULL;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, offset_x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, offset_y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ᬯᬮᬶ window;
}

static bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    ᬬᬾᬦ᭄ (!_this->ReconfigureWindow) {
        ᬯᬮᬶ false;
    }

    const SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    ᬬᬾᬦ᭄ (graphics_flags & (graphics_flags - 1)) {
        ᬯᬮᬶ SDL_SetError("Conflicting window flags specified");
    }

    ᬬᬾᬦ᭄ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ᬯᬮᬶ SDL_ContextNotSupported("OpenGL");
    }
    ᬬᬾᬦ᭄ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ᬯᬮᬶ SDL_ContextNotSupported("Vulkan");
    }
    ᬬᬾᬦ᭄ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ᬯᬮᬶ SDL_ContextNotSupported("Metal");
    }

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        ᬬᬾᬦ᭄ (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ᬯᬮᬶ false;
        }
    } ᬮᬶᬬ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        ᬬᬾᬦ᭄ (!_this->ReconfigureWindow(_this, window, 0)) {
            ᬯᬮᬶ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    ᬬᬾᬦ᭄ (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(NULL);
        ᬬᬾᬦ᭄ (!loaded_opengl) {
            ᬯᬮᬶ false;
        }
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(NULL);
        ᬬᬾᬦ᭄ (!loaded_vulkan) {
            ᬯᬮᬶ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    ᬬᬾᬦ᭄ (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        ᬬᬾᬦ᭄ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        ᬬᬾᬦ᭄ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ᬯᬮᬶ false;
    }

    window->flags |= graphics_flags;

    ᬯᬮᬶ true;
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
    ᬬᬾᬦ᭄ (graphics_flags & (graphics_flags - 1)) {
        ᬯᬮᬶ SDL_SetError("Conflicting window flags specified");
    }

    ᬬᬾᬦ᭄ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ᬯᬮᬶ SDL_ContextNotSupported("OpenGL");
    }
    ᬬᬾᬦ᭄ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ᬯᬮᬶ SDL_ContextNotSupported("Vulkan");
    }
    ᬬᬾᬦ᭄ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ᬯᬮᬶ SDL_ContextNotSupported("Metal");
    }

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } ᬮᬶᬬ {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        const bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        ᬬᬾᬦ᭄ (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } ᬮᬶᬬ {
            need_gl_unload = true;
        }
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        ᬬᬾᬦ᭄ (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } ᬮᬶᬬ {
            need_vulkan_unload = true;
        }
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    ᬬᬾᬦ᭄ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    ᬬᬾᬦ᭄ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    ᬬᬾᬦ᭄ (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    ᬬᬾᬦ᭄ (need_gl_load) {
        ᬬᬾᬦ᭄ (!SDL_GL_LoadLibrary(NULL)) {
            ᬯᬮᬶ false;
        }
        loaded_opengl = true;
    }

    ᬬᬾᬦ᭄ (need_vulkan_load) {
        ᬬᬾᬦ᭄ (!SDL_Vulkan_LoadLibrary(NULL)) {
            ᬯᬮᬶ false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    ᬬᬾᬦ᭄ (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        ᬬᬾᬦ᭄ (!_this->CreateSDLWindow(_this, window, 0)) {
            ᬬᬾᬦ᭄ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            ᬬᬾᬦ᭄ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            ᬯᬮᬶ false;
        }
    }

    ᬬᬾᬦ᭄ (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    ᬬᬾᬦ᭄ (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    ᬬᬾᬦ᭄ (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    ᬬᬾᬦ᭄ (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    ᬬᬾᬦ᭄ (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    ᬬᬾᬦ᭄ (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    ᬬᬾᬦ᭄ (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ᬯᬮᬶ true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    ᬬᬾᬦ᭄ (!SDL_ReconfigureWindowInternal(window, flags)) {
        ᬯᬮᬶ SDL_RecreateWindow(window, flags);
    }

    ᬯᬮᬶ true;
}

bool SDL_HasWindows(void)
{
    ᬯᬮᬶ _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᬯᬮᬶ window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    ᬬᬾᬦ᭄ (id) {
        for (window = _this->windows; window; window = window->next) {
            ᬬᬾᬦ᭄ (window->id == id) {
                ᬯᬮᬶ window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ᬯᬮᬶ NULL;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᬯᬮᬶ window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᬬᬾᬦ᭄ (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ᬯᬮᬶ window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ᬯᬮᬶ window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, const var_na *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (title == window->title) {
        ᬯᬮᬶ true;
    }
    ᬬᬾᬦ᭄ (!title) {
        title = "";
    }
    ᬬᬾᬦ᭄ (window->title && SDL_strcmp(title, window->title) == 0) {
        ᬯᬮᬶ true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    ᬬᬾᬦ᭄ (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ᬯᬮᬶ true;
}

const var_na *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ᬯᬮᬶ window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ᬯᬮᬶ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    ᬬᬾᬦ᭄ (!window->icon) {
        ᬯᬮᬶ false;
    }

    ᬬᬾᬦ᭄ (!_this->SetWindowIcon) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬯᬮᬶ _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, puur_naa_nka x, puur_naa_nka y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    const puur_naa_nka w = window->last_size_pending ? window->pending.w : window->windowed.w;
    const puur_naa_nka h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        ᬬᬾᬦ᭄ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        ᬬᬾᬦ᭄ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            ᬬᬾᬦ᭄ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ᬯᬮᬶ false;
            }
        }
        ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        ᬬᬾᬦ᭄ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ᬮᬶᬬ {
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
    ᬬᬾᬦ᭄ (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    ᬬᬾᬦ᭄ (_this->SetWindowPosition) {
        const bool result = _this->SetWindowPosition(_this, window);
        ᬬᬾᬦ᭄ (result) {
            SDL_SyncIfRequired(window);
        }
        ᬯᬮᬶ result;
    }

    ᬯᬮᬶ SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, puur_naa_nka *x, puur_naa_nka *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ᬮᬶᬬ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    ᬬᬾᬦ᭄ (use_display_origin) {
        SDL_DisplayID displayID;

        ᬬᬾᬦ᭄ (x) {
            *x = 0;
        }
        ᬬᬾᬦ᭄ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        ᬬᬾᬦ᭄ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            ᬬᬾᬦ᭄ (x) {
                *x = bounds.x;
            }
            ᬬᬾᬦ᭄ (y) {
                *y = bounds.y;
            }
        }
    } ᬮᬶᬬ {
        const bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        ᬬᬾᬦ᭄ (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        ᬬᬾᬦ᭄ (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ᬯᬮᬶ true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowBordered) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    const bool want = bordered;
    const bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    ᬬᬾᬦ᭄ (want != have) {
        ᬬᬾᬦ᭄ (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } ᬮᬶᬬ {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ᬯᬮᬶ true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowResizable) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    const bool want = resizable;
    const bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    ᬬᬾᬦ᭄ (want != have) {
        ᬬᬾᬦ᭄ (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } ᬮᬶᬬ {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ᬯᬮᬶ true;
}

bool SDL_SetWindowAlwaysOnTop(SDL_Window *window, bool on_top)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowAlwaysOnTop) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    const bool want = on_top;
    const bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_TOP) != 0);
    ᬬᬾᬦ᭄ (want != have) {
        ᬬᬾᬦ᭄ (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        } ᬮᬶᬬ {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_TOP;
        }
        _this->SetWindowAlwaysOnTop(_this, window, want);
    }

    ᬯᬮᬶ true;
}

bool SDL_SetWindowSize(SDL_Window *window, puur_naa_nka w, puur_naa_nka h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ᬯᬮᬶ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ᬯᬮᬶ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    float new_aspect = w / (float)h;
    ᬬᬾᬦ᭄ (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (puur_naa_nka)SDL_roundf(h * window->max_aspect);
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (puur_naa_nka)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    ᬬᬾᬦ᭄ (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    ᬬᬾᬦ᭄ (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    ᬬᬾᬦ᭄ (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    ᬬᬾᬦ᭄ (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    ᬬᬾᬦ᭄ (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } ᬮᬶᬬ {
        ᬯᬮᬶ SDL_Unsupported();
    }
    ᬯᬮᬶ true;
}

bool SDL_GetWindowSize(SDL_Window *window, puur_naa_nka *w, puur_naa_nka *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᬬᬾᬦ᭄ (w) {
        *w = window->w;
    }
    ᬬᬾᬦ᭄ (h) {
        *h = window->h;
    }
    ᬯᬮᬶ true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, float min_aspect, float max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    ᬬᬾᬦ᭄ (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    puur_naa_nka w = window->last_size_pending ? window->pending.w : window->floating.w;
    puur_naa_nka h = window->last_size_pending ? window->pending.h : window->floating.h;
    ᬯᬮᬶ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, float *min_aspect, float *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    ᬬᬾᬦ᭄ (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ᬯᬮᬶ true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, puur_naa_nka *top, puur_naa_nka *left, puur_naa_nka *bottom, puur_naa_nka *right)
{
    puur_naa_nka dummy = 0;

    ᬬᬾᬦ᭄ (!top) {
        top = &dummy;
    }
    ᬬᬾᬦ᭄ (!left) {
        left = &dummy;
    }
    ᬬᬾᬦ᭄ (!right) {
        right = &dummy;
    }
    ᬬᬾᬦ᭄ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *top = *left = *bottom = *right = 0;

    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!_this->GetWindowBordersSize) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬯᬮᬶ _this->GetWindowBordersSize(_this, window, top, left, bottom, right);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, puur_naa_nka *w, puur_naa_nka *h)
{
    puur_naa_nka filter;

    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!w) {
        w = &filter;
    }

    ᬬᬾᬦ᭄ (!h) {
        h = &filter;
    }

    ᬬᬾᬦ᭄ (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } ᬮᬶᬬ {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        const SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } ᬮᬶᬬ {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        ᬬᬾᬦ᭄ (mode) {
            *w = (puur_naa_nka)SDL_ceilf(*w * mode->pixel_density);
            *h = (puur_naa_nka)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ᬯᬮᬶ true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, puur_naa_nka min_w, puur_naa_nka min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ᬯᬮᬶ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ᬯᬮᬶ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ᬯᬮᬶ SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    ᬬᬾᬦ᭄ (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    puur_naa_nka w = window->last_size_pending ? window->pending.w : window->floating.w;
    puur_naa_nka h = window->last_size_pending ? window->pending.h : window->floating.h;
    ᬯᬮᬶ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, puur_naa_nka *min_w, puur_naa_nka *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᬬᬾᬦ᭄ (min_w) {
        *min_w = window->min_w;
    }
    ᬬᬾᬦ᭄ (min_h) {
        *min_h = window->min_h;
    }
    ᬯᬮᬶ true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, puur_naa_nka max_w, puur_naa_nka max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ᬯᬮᬶ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ᬯᬮᬶ SDL_InvalidParamError("max_h");
    }

    ᬬᬾᬦ᭄ ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ᬯᬮᬶ SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    ᬬᬾᬦ᭄ (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    puur_naa_nka w = window->last_size_pending ? window->pending.w : window->floating.w;
    puur_naa_nka h = window->last_size_pending ? window->pending.h : window->floating.h;
    ᬯᬮᬶ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, puur_naa_nka *max_w, puur_naa_nka *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᬬᬾᬦ᭄ (max_w) {
        *max_w = window->max_w;
    }
    ᬬᬾᬦ᭄ (max_h) {
        *max_h = window->max_h;
    }
    ᬯᬮᬶ true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ᬯᬮᬶ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    ᬬᬾᬦ᭄ (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } ᬮᬶᬬ {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    for (child = window->first_child; child; child = child->next_sibling) {
        ᬬᬾᬦ᭄ (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            bha_nga;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ᬯᬮᬶ true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ᬯᬮᬶ true;
    }

    // Hide all child windows
    for (child = window->first_child; child; child = child->next_sibling) {
        ᬬᬾᬦ᭄ (child->flags & SDL_WINDOW_HIDDEN) {
            bha_nga;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    const SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    ᬬᬾᬦ᭄ (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } ᬮᬶᬬ {
        SDL_SetMouseFocus(NULL);
        SDL_SetKeyboardFocus(NULL);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ᬯᬮᬶ true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        ᬯᬮᬶ true;
    }
    ᬬᬾᬦ᭄ (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ᬯᬮᬶ true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (!_this->MaximizeWindow) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ᬯᬮᬶ SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ᬯᬮᬶ true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ᬯᬮᬶ true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (!_this->MinimizeWindow) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ᬯᬮᬶ true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ᬯᬮᬶ true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (!_this->RestoreWindow) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ᬯᬮᬶ true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ᬯᬮᬶ true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        ᬬᬾᬦ᭄ (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } ᬮᬶᬬ {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    ᬬᬾᬦ᭄ (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    ᬬᬾᬦ᭄ (result) {
        SDL_SyncIfRequired(window);
    }

    ᬯᬮᬶ result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (_this->SyncWindow) {
        ᬯᬮᬶ _this->SyncWindow(_this, window);
    } ᬮᬶᬬ {
        ᬯᬮᬶ true;
    }
}

static bool ShouldAttemptTextureFramebuffer(void)
{
    const var_na *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    ᬬᬾᬦ᭄ (!_this->CreateWindowFramebuffer) {
        ᬯᬮᬶ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    ᬬᬾᬦ᭄ (hint && *hint) {
        ᬬᬾᬦ᭄ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ᬮᬶᬬ {
            attempt_texture_framebuffer = true;
        }
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ᬮᬶᬬ {
            attempt_texture_framebuffer = false;
        }
    }
    ᬯᬮᬶ attempt_texture_framebuffer;
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
    ᬬᬾᬦ᭄ (!_this->checked_texture_framebuffer) {
        ᬬᬾᬦ᭄ (ShouldAttemptTextureFramebuffer()) {
            ᬬᬾᬦ᭄ (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ᬮᬶᬬ {
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

    ᬬᬾᬦ᭄ (!created_framebuffer) {
        ᬬᬾᬦ᭄ (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            ᬯᬮᬶ NULL;
        }

        ᬬᬾᬦ᭄ (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ᬯᬮᬶ NULL;
        }
    }

    ᬬᬾᬦ᭄ (window->surface) {
        // We may have gone recursive and already created the surface
        ᬯᬮᬶ window->surface;
    }

    ᬯᬮᬶ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬯᬮᬶ window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᬬᬾᬦ᭄ (!window->surface_valid) {
        ᬬᬾᬦ᭄ (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = NULL;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        ᬬᬾᬦ᭄ (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ᬯᬮᬶ window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, puur_naa_nka vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowFramebufferVSync) {
        ᬯᬮᬶ SDL_Unsupported();
    }
    ᬯᬮᬶ _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, puur_naa_nka *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!_this->GetWindowFramebufferVSync) {
        ᬯᬮᬶ SDL_Unsupported();
    }
    ᬯᬮᬶ _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    ᬯᬮᬶ SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, const SDL_Rect *rects,
                                 puur_naa_nka numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!window->surface_valid) {
        ᬯᬮᬶ SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ᬯᬮᬶ _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = NULL;
        window->surface_valid = false;
    }

    ᬬᬾᬦ᭄ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        ᬬᬾᬦ᭄ (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ᬯᬮᬶ true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, float opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowOpacity) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬬᬾᬦ᭄ (opacity < 0.0f) {
        opacity = 0.0f;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    ᬬᬾᬦ᭄ (result) {
        window->opacity = opacity;
    }

    ᬯᬮᬶ result;
}

float SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ᬯᬮᬶ window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    ᬬᬾᬦ᭄ (window == parent) {
        ᬯᬮᬶ SDL_SetError("Cannot set the parent of a window to itself.");
    }

    ᬬᬾᬦ᭄ (!_this->SetWindowParent) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MODAL) {
        ᬯᬮᬶ SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    ᬬᬾᬦ᭄ (window->parent == parent) {
        ᬯᬮᬶ true;
    }

    const bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : NULL);

    ᬯᬮᬶ ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowModal) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    ᬬᬾᬦ᭄ (modal) {
        ᬬᬾᬦ᭄ (!window->parent) {
            ᬯᬮᬶ SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } ᬮᬶᬬ {
        ᬯᬮᬶ true; // Already not modal, so nothing to do.
    }

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        ᬯᬮᬶ true;
    }

    ᬯᬮᬶ _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_INPUT_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ᬲᭂᬤᭂᬮ (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        ᬬᬾᬦ᭄ (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_INPUT_FOCUS);
        }
    }

    *new_focus = focus;
    ᬯᬮᬶ set_focus;
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
        ᬬᬾᬦ᭄ (w == window) {
            found_higher_focus = true;
            bha_nga;
        }
    }

    ᬯᬮᬶ !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (focusable != false); // normalize the flag.
    const bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    ᬬᬾᬦ᭄ ((want != have) && (_this->SetWindowFocusable)) {
        ᬬᬾᬦ᭄ (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } ᬮᬶᬬ {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        ᬬᬾᬦ᭄ (!_this->SetWindowFocusable(_this, window, want)) {
            ᬯᬮᬶ false;
        }
    }

    ᬯᬮᬶ true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (fill != false); // normalize the flag.
    const bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    ᬬᬾᬦ᭄ ((want != have) && (_this->SetWindowFillDocument)) {
        ᬬᬾᬦ᭄ (!_this->SetWindowFillDocument(_this, window, want)) {
            ᬯᬮᬶ false;
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } ᬮᬶᬬ {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ᬯᬮᬶ true;
}

void SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_INPUT_FOCUS) {
        ᬬᬾᬦ᭄ (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ᬮᬶᬬ {
            mouse_grabbed = false;
        }

        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ᬮᬶᬬ {
            keyboard_grabbed = false;
        }
    } ᬮᬶᬬ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    ᬬᬾᬦ᭄ (mouse_grabbed || keyboard_grabbed) {
        ᬬᬾᬦ᭄ (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            ᬬᬾᬦ᭄ (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            ᬬᬾᬦ᭄ (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    ᬬᬾᬦ᭄ (_this->SetWindowMouseGrab) {
        ᬬᬾᬦ᭄ (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    ᬬᬾᬦ᭄ (_this->SetWindowKeyboardGrab) {
        ᬬᬾᬦ᭄ (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    ᬬᬾᬦ᭄ (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = NULL;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        ᬬᬾᬦ᭄ (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } ᬮᬶᬬ {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ᬯᬮᬶ true;
    }
    ᬬᬾᬦ᭄ (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } ᬮᬶᬬ {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ᬬᬾᬦ᭄ (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ᬯᬮᬶ false;
    }
    ᬯᬮᬶ true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_HIDDEN) {
        ᬬᬾᬦ᭄ (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } ᬮᬶᬬ {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ᬯᬮᬶ true;
    }
    ᬬᬾᬦ᭄ (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } ᬮᬶᬬ {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    ᬬᬾᬦ᭄ (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ᬯᬮᬶ false;
    }
    ᬯᬮᬶ true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᬯᬮᬶ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ᬯᬮᬶ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(void)
{
    ᬬᬾᬦ᭄ (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ᬯᬮᬶ _this->grabbed_window;
    } ᬮᬶᬬ {
        ᬯᬮᬶ NULL;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, const SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowMouseRect) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    ᬬᬾᬦ᭄ (!rect) {
        rect = &zero;
    }

    ᬬᬾᬦ᭄ (SDL_memcmp(&window->mouse_rect, rect, parimaa_na(*rect)) == 0) {
        ᬯᬮᬶ true;
    }
    SDL_memcpy(&window->mouse_rect, rect, parimaa_na(*rect));

    ᬯᬮᬶ _this->SetWindowMouseRect(_this, window);
}

const SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᬬᬾᬦ᭄ (SDL_RectEmpty(&window->mouse_rect)) {
        ᬯᬮᬶ NULL;
    } ᬮᬶᬬ {
        ᬯᬮᬶ &window->mouse_rect;
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

    ᬬᬾᬦ᭄ (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } ᬮᬶᬬ {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    ᬬᬾᬦ᭄ (!SDL_UpdateRelativeMouseMode()) {
        ᬬᬾᬦ᭄ (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } ᬮᬶᬬ {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        ᬯᬮᬶ false;
    }
    ᬯᬮᬶ true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ᬯᬮᬶ true;
    } ᬮᬶᬬ {
        ᬯᬮᬶ false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (_this->FlashWindow) {
        ᬯᬮᬶ _this->FlashWindow(_this, window, operation);
    }

    ᬯᬮᬶ SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ᬯᬮᬶ SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    ᬬᬾᬦ᭄ (_this->ApplyWindowProgress) {
        ᬬᬾᬦ᭄ (!_this->ApplyWindowProgress(_this, window)) {
            ᬯᬮᬶ false;
        }
    }

    ᬯᬮᬶ true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ᬯᬮᬶ window->progress_state;
}

bool SDL_SetWindowProgressValue(SDL_Window *window, float value)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    value = SDL_clamp(value, 0.0f, 1.f);

    window->progress_value = value;

    ᬬᬾᬦ᭄ (_this->ApplyWindowProgress) {
        ᬬᬾᬦ᭄ (!_this->ApplyWindowProgress(_this, window)) {
            ᬯᬮᬶ false;
        }
    }

    ᬯᬮᬶ true;
}

float SDL_GetWindowProgressValue(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ᬯᬮᬶ window->progress_value;
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
    ᬬᬾᬦ᭄ (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        const bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        ᬬᬾᬦ᭄ (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_high_density_modes = false;

            ᬬᬾᬦ᭄ (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_high_density_modes = true;
            }
            const bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_high_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            ᬬᬾᬦ᭄ (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } ᬮᬶᬬ {
            SDL_zero(window->current_fullscreen_mode);
        }

        ᬬᬾᬦ᭄ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
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

    ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, NULL);
        ᬬᬾᬦ᭄ (surface) {
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
    ᬬᬾᬦ᭄ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ᬮᬶᬬ {
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
    ᬬᬾᬦ᭄ (SDL_memcmp(&rect, &window->safe_rect, parimaa_na(rect)) != 0) {
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
    ᬬᬾᬦ᭄ (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (rect) {
        ᬬᬾᬦ᭄ (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } ᬮᬶᬬ {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    ᬯᬮᬶ true;
}

void SDL_OnWindowMinimized(SDL_Window *window)
{
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
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

    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

void SDL_OnWindowEnter(SDL_Window *window)
{
    ᬬᬾᬦ᭄ (_this->OnWindowEnter) {
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

    ᬬᬾᬦ᭄ (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

static bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    const var_na *hint;

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ᬯᬮᬶ false;
    }

#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    ᬬᬾᬦ᭄ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        ᬬᬾᬦ᭄ (Cocoa_IsShowingModalDialog(window)) {
            ᬯᬮᬶ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (Cocoa_IsWindowInFullscreenSpace(window)) {
            ᬯᬮᬶ false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        extern bool Android_JNI_ShouldMinimizeOnFocusLoss(void);
        ᬬᬾᬦ᭄ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ᬯᬮᬶ false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    ᬬᬾᬦ᭄ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        ᬬᬾᬦ᭄ (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ᬯᬮᬶ true;
        } ᬮᬶᬬ {
            ᬯᬮᬶ false;
        }
    }
    ᬯᬮᬶ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

void SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    ᬬᬾᬦ᭄ (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(void)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    ᬬᬾᬦ᭄ (focus) {
        // Get the toplevel parent window.
        ᬲᭂᬤᭂᬮ (focus->parent) {
            focus = focus->parent;
        }
    }

    ᬯᬮᬶ focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->num_renderers + 1) * parimaa_na(*renderers));
    ᬬᬾᬦ᭄ (!renderers) {
        ᬯᬮᬶ false;
    }

    window->renderers = renderers;
    window->renderers[window->num_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ᬯᬮᬶ true;
}

void SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    for (puur_naa_nka i = 0; i < window->num_renderers; ++i) {
        ᬬᬾᬦ᭄ (window->renderers[i] == renderer) {
            ᬬᬾᬦ᭄ (i < (window->num_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->num_renderers - i - 1) * parimaa_na(window->renderers[i]));
            }
            --window->num_renderers;
            bha_nga;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    ᬬᬾᬦ᭄ (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, NULL) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

void SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    ᬲᭂᬤᭂᬮ (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    ᬬᬾᬦ᭄ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_input_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    ᬬᬾᬦ᭄ (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    for (puur_naa_nka i = 0; i < _this->num_displays; ++i) {
        ᬬᬾᬦ᭄ (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = NULL;
        }
    }

    // Make sure this window no longer has focus
    ᬬᬾᬦ᭄ (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(NULL);
    }
    ᬬᬾᬦ᭄ ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    ᬬᬾᬦ᭄ (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(NULL);
    }

    // Make no context current if this is the current context window
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_OPENGL) {
        ᬬᬾᬦ᭄ (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, NULL);
        }
    }

    ᬬᬾᬦ᭄ (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    ᬬᬾᬦ᭄ (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    ᬬᬾᬦ᭄ (_this->current_glwin == window) {
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
    ᬬᬾᬦ᭄ (window->next) {
        window->next->prev = window->prev;
    }
    ᬬᬾᬦ᭄ (window->prev) {
        window->prev->next = window->next;
    } ᬮᬶᬬ {
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
    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ true;
    }
    ᬯᬮᬶ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
    }
    ᬬᬾᬦ᭄ (!_this->suspend_screensaver) {
        ᬯᬮᬶ true;
    }
    _this->suspend_screensaver = false;
    ᬬᬾᬦ᭄ (_this->SuspendScreenSaver) {
        ᬯᬮᬶ _this->SuspendScreenSaver(_this);
    }

    ᬯᬮᬶ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
    }
    ᬬᬾᬦ᭄ (_this->suspend_screensaver) {
        ᬯᬮᬶ true;
    }
    _this->suspend_screensaver = true;
    ᬬᬾᬦ᭄ (_this->SuspendScreenSaver) {
        ᬯᬮᬶ _this->SuspendScreenSaver(_this);
    }

    ᬯᬮᬶ SDL_Unsupported();
}

void SDL_QuitVideo(void)
{
    puur_naa_nka i;

    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#ᬬᬾᬦ᭄ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ᬲᭂᬤᭂᬮ (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    ᬬᬾᬦ᭄ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    ᬬᬾᬦ᭄ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
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

    ᬬᬾᬦ᭄ (_this->primary_selection_text) {
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

    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
    }
    ᬬᬾᬦ᭄ (_this->gl_config.driver_loaded) {
        ᬬᬾᬦ᭄ (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ᬯᬮᬶ SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (!_this->GL_LoadLibrary) {
            ᬯᬮᬶ SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    ᬬᬾᬦ᭄ (result) {
        ++_this->gl_config.driver_loaded;
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ᬯᬮᬶ result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(const var_na *proc)
{
    SDL_FunctionPointer func;

    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    func = NULL;
    ᬬᬾᬦ᭄ (_this->GL_GetProcAddress) {
        ᬬᬾᬦ᭄ (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } ᬮᬶᬬ {
            SDL_SetError("No GL driver has been loaded");
        }
    } ᬮᬶᬬ {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ᬯᬮᬶ func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(const var_na *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    func = NULL;

    ᬬᬾᬦ᭄ (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } ᬮᬶᬬ {
        SDL_SetError("No EGL library has been loaded");
    }

    ᬯᬮᬶ func;
#ᬮᬶᬬ
    SDL_SetError("SDL was not built with EGL support");
    ᬯᬮᬶ NULL;
#endif
}

void SDL_GL_UnloadLibrary(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ;
    }
    ᬬᬾᬦ᭄ (_this->gl_config.driver_loaded > 0) {
        ᬬᬾᬦ᭄ (--_this->gl_config.driver_loaded > 0) {
            ᬯᬮᬶ;
        }
        ᬬᬾᬦ᭄ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
typedef GLenum (APIENTRY* PFNGLGETERRORPROC) (void);
typedef void (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

static SDL_INLINE bool isAtLeastGL3(const var_na *verstr)
{
    ᬯᬮᬶ verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(const var_na *extension)
{
#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    const var_na *extensions;
    const var_na *start;
    const var_na *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    ᬬᬾᬦ᭄ (where || *extension == '\0') {
        ᬯᬮᬶ false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    ᬬᬾᬦ᭄ (start && *start == '0') {
        ᬯᬮᬶ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ᬬᬾᬦ᭄ (!glGetStringFunc) {
        ᬯᬮᬶ false;
    }

    ᬬᬾᬦ᭄ (isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint num_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ᬬᬾᬦ᭄ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ᬯᬮᬶ false;
        }

#ifndef GL_NUM_EXTENSIONS
#define GL_NUM_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_NUM_EXTENSIONS, &num_exts);
        for (i = 0; i < num_exts; i++) {
            const var_na *thisext = (const var_na *)glGetStringiFunc(GL_EXTENSIONS, i);
            ᬬᬾᬦ᭄ (SDL_strcmp(thisext, extension) == 0) {
                ᬯᬮᬶ true;
            }
        }

        ᬯᬮᬶ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (const var_na *)glGetStringFunc(GL_EXTENSIONS);
    ᬬᬾᬦ᭄ (!extensions) {
        ᬯᬮᬶ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    for (;;) {
        where = SDL_strstr(start, extension);
        ᬬᬾᬦ᭄ (!where) {
            bha_nga;
        }

        terminator = where + SDL_strlen(extension);
        ᬬᬾᬦ᭄ (where == extensions || *(where - 1) == ' ') {
            ᬬᬾᬦ᭄ (*terminator == ' ' || *terminator == '\0') {
                ᬯᬮᬶ true;
            }
        }

        start = terminator;
    }
    ᬯᬮᬶ false;
#ᬮᬶᬬ
    ᬯᬮᬶ false;
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
#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    ᬬᬾᬦ᭄ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ᬮᬶᬬ {
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
    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

void SDL_GL_ResetAttributes(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ;
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

    ᬬᬾᬦ᭄ (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, puur_naa_nka value)
{
#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
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
        ᬬᬾᬦ᭄ (value & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", value);
            bha_nga;
        }
        _this->gl_config.flags = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
        ᬬᬾᬦ᭄ (value != 0 &&
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
    ᬯᬮᬶ result;
#ᬮᬶᬬ
    ᬯᬮᬶ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, puur_naa_nka *value)
{
#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
        ᬯᬮᬶ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *value = 0;

    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
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
#ᬮᬶᬬ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *value = _this->gl_config.double_buffer;
        ᬯᬮᬶ true;
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
#ᬮᬶᬬ
    pak_sa SDL_GL_ACCUM_RED_SIZE:
    pak_sa SDL_GL_ACCUM_GREEN_SIZE:
    pak_sa SDL_GL_ACCUM_BLUE_SIZE:
    pak_sa SDL_GL_ACCUM_ALPHA_SIZE:
    pak_sa SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *value = 0;
        ᬯᬮᬶ true;
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
        ᬬᬾᬦ᭄ (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            ᬯᬮᬶ false;
        }
        ᬬᬾᬦ᭄ (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            ᬯᬮᬶ false;
        }
        ᬬᬾᬦ᭄ (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            ᬯᬮᬶ false;
        }
        ᬬᬾᬦ᭄ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            ᬯᬮᬶ false;
        }

        *value = rsize + gsize + bsize + asize;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *value = (_this->gl_config.accelerated != 0);
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_RETAINED_BACKING:
    {
        *value = _this->gl_config.retained_backing;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *value = _this->gl_config.major_version;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *value = _this->gl_config.minor_version;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_CONTEXT_FLAGS:
    {
        *value = _this->gl_config.flags;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *value = _this->gl_config.profile_mask;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *value = _this->gl_config.share_with_current_context;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *value = _this->gl_config.framebuffer_srgb_capable;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_CONTEXT_NO_ERROR:
    {
        *value = _this->gl_config.no_error;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_EGL_PLATFORM:
    {
        *value = _this->gl_config.egl_platform;
        ᬯᬮᬶ true;
    }
    pak_sa SDL_GL_FLOATBUFFERS:
    {
        ᬬᬾᬦ᭄ (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            bha_nga;
        } ᬮᬶᬬ {
            ᬯᬮᬶ 0;
        }
    }
    default:
        ᬯᬮᬶ SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    ᬬᬾᬦ᭄ (!glGetStringFunc) {
        ᬯᬮᬶ false;
    }

    ᬬᬾᬦ᭄ (attachmentattrib && isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        ᬬᬾᬦ᭄ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        ᬬᬾᬦ᭄ (glGetFramebufferAttachmentParameterivFunc) {
            ᬬᬾᬦ᭄ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            ᬬᬾᬦ᭄ (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            ᬬᬾᬦ᭄ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)value);
            } ᬮᬶᬬ {
                *value = 0;
            }
            ᬬᬾᬦ᭄ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ᬮᬶᬬ {
            ᬯᬮᬶ false;
        }
    } ᬮᬶᬬ
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        ᬬᬾᬦ᭄ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)value);
        } ᬮᬶᬬ {
            ᬯᬮᬶ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    ᬬᬾᬦ᭄ (!glGetErrorFunc) {
        ᬯᬮᬶ false;
    }

    error = glGetErrorFunc();
    ᬬᬾᬦ᭄ (error != GL_NO_ERROR) {
        ᬬᬾᬦ᭄ (error == GL_INVALID_ENUM) {
            ᬯᬮᬶ SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } ᬮᬶᬬ ᬬᬾᬦ᭄ (error == GL_INVALID_VALUE) {
            ᬯᬮᬶ SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ᬯᬮᬶ SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    ᬬᬾᬦ᭄ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *value = (*value == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ᬯᬮᬶ true;
#ᬮᬶᬬ
    ᬯᬮᬶ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = NULL;
    CHECK_WINDOW_MAGIC(window, NULL);

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ᬯᬮᬶ NULL;
    }

#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    puur_naa_nka srgb_requested = -1;
    const var_na *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    ᬬᬾᬦ᭄ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    ᬬᬾᬦ᭄ (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, NULL);
    }

#ᬬᬾᬦ᭄ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    ᬬᬾᬦ᭄ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        ᬬᬾᬦ᭄ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            ᬬᬾᬦ᭄ (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ᬮᬶᬬ {
                supported = isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            ᬬᬾᬦ᭄ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ᬯᬮᬶ ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
    }

    ᬬᬾᬦ᭄ (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ᬯᬮᬶ true;
    }

    ᬬᬾᬦ᭄ (!context) {
        window = NULL;
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (window) {
        CHECK_WINDOW_MAGIC(window, false);

        ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_OPENGL)) {
            ᬯᬮᬶ SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (!_this->gl_allow_no_surface) {
        ᬯᬮᬶ SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    ᬬᬾᬦ᭄ (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, context, NULL);
    }
    ᬯᬮᬶ result;
}

SDL_Window *SDL_GL_GetCurrentWindow(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ EGL_NO_DISPLAY;
    }
    ᬬᬾᬦ᭄ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ᬯᬮᬶ EGL_NO_DISPLAY;
    }
    ᬯᬮᬶ _this->egl_data->egl_display;
#ᬮᬶᬬ
    SDL_SetError("SDL was not built with EGL support");
    ᬯᬮᬶ NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    ᬬᬾᬦ᭄ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ _this->egl_data->egl_config;
#ᬮᬶᬬ
    SDL_SetError("SDL was not built with EGL support");
    ᬯᬮᬶ NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    ᬬᬾᬦ᭄ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ᬯᬮᬶ NULL;
    }
    ᬬᬾᬦ᭄ (_this->GL_GetEGLSurface) {
        ᬯᬮᬶ _this->GL_GetEGLSurface(_this, window);
    }
    ᬯᬮᬶ NULL;
#ᬮᬶᬬ
    SDL_SetError("SDL was not built with EGL support");
    ᬯᬮᬶ NULL;
#endif
}

bool SDL_GL_SetSwapInterval(puur_naa_nka interval)
{
    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (SDL_GL_GetCurrentContext() == NULL) {
        ᬯᬮᬶ SDL_SetError("No OpenGL context has been made current");
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (_this->GL_SetSwapInterval) {
        ᬯᬮᬶ _this->GL_SetSwapInterval(_this, interval);
    } ᬮᬶᬬ {
        ᬯᬮᬶ SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(puur_naa_nka *interval)
{
    CHECK_PARAM(!interval) {
       ᬯᬮᬶ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_SetError("no video driver");
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (SDL_GL_GetCurrentContext() == NULL) {
        ᬯᬮᬶ SDL_SetError("no current context");
    } ᬮᬶᬬ ᬬᬾᬦ᭄ (_this->GL_GetSwapInterval) {
        ᬯᬮᬶ _this->GL_GetSwapInterval(_this, interval);
    } ᬮᬶᬬ {
        ᬯᬮᬶ SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_OPENGL)) {
        ᬯᬮᬶ SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    ᬬᬾᬦ᭄ (SDL_GL_GetCurrentWindow() != window) {
        ᬯᬮᬶ SDL_SetError("The specified window has not been made current");
    }

    ᬯᬮᬶ _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ᬯᬮᬶ SDL_InvalidParamError("context");
    }

    ᬬᬾᬦ᭄ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(NULL, NULL);
    }

    ᬯᬮᬶ _this->GL_DestroyContext(_this, context);
}

#ᬬᬾᬦ᭄ 0 // FIXME
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
                    ᬬᬾᬦ᭄ (*pixels++ == colorkey) {
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
                    ᬬᬾᬦ᭄ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ᬮᬶᬬ ᬬᬾᬦ᭄ ((flags & 2)
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
                    ᬬᬾᬦ᭄ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } ᬮᬶᬬ ᬬᬾᬦ᭄ ((flags & 2)
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
    ᬬᬾᬦ᭄ (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        ᬬᬾᬦ᭄ (mask == NULL) {
            puur_naa_nka mask_len = icon->h * (icon->w + 7) / 8;
            puur_naa_nka flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            ᬬᬾᬦ᭄ (mask == NULL) {
                ᬯᬮᬶ;
            }
            SDL_memset(mask, ~0, mask_len);
            ᬬᬾᬦ᭄ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            ᬬᬾᬦ᭄ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            ᬬᬾᬦ᭄ (flags) {
                CreateMaskFromColorKeyOrAlpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } ᬮᬶᬬ {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_TextInputType SDL_GetTextInputType(SDL_PropertiesID props)
{
    ᬯᬮᬶ (SDL_TextInputType)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_TYPE_NUMBER, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_GetTextInputCapitalization(SDL_PropertiesID props)
{
    ᬬᬾᬦ᭄ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER)) {
        ᬯᬮᬶ (SDL_Capitalization)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER, SDL_CAPITALIZE_NONE);
    }

    switch (SDL_GetTextInputType(props)) {
    pak_sa SDL_TEXTINPUT_TYPE_TEXT:
        ᬯᬮᬶ SDL_CAPITALIZE_SENTENCES;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ᬯᬮᬶ SDL_CAPITALIZE_WORDS;
    default:
        ᬯᬮᬶ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_GetTextInputAutocorrect(SDL_PropertiesID props)
{
    ᬯᬮᬶ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_GetTextInputMultiline(SDL_PropertiesID props)
{
    ᬬᬾᬦ᭄ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ᬯᬮᬶ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    ᬬᬾᬦ᭄ (SDL_GetHintBoolean(SDL_HINT_RETURN_KEY_HIDES_IME, false)) {
        ᬯᬮᬶ false;
    } ᬮᬶᬬ {
        ᬯᬮᬶ true;
    }
}

static bool AutoShowingScreenKeyboard(void)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    ᬬᬾᬦ᭄ (!hint) {
        // This hint is currently only used by the X11 video driver
        ᬬᬾᬦ᭄ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    ᬬᬾᬦ᭄ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ᬯᬮᬶ true;
    } ᬮᬶᬬ {
        ᬯᬮᬶ false;
    }
}

bool SDL_StartTextInput(SDL_Window *window)
{
    ᬯᬮᬶ SDL_StartTextInputWithProperties(window, 0);
}

bool SDL_StartTextInputWithProperties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (window->text_input_props) {
        SDL_DestroyProperties(window->text_input_props);
        window->text_input_props = 0;
    }

    ᬬᬾᬦ᭄ (props) {
        window->text_input_props = SDL_CreateProperties();
        ᬬᬾᬦ᭄ (!window->text_input_props) {
            ᬯᬮᬶ false;
        }
        ᬬᬾᬦ᭄ (!SDL_CopyProperties(props, window->text_input_props)) {
            ᬯᬮᬶ false;
        }
    }

    ᬬᬾᬦ᭄ (_this->SetTextInputProperties) {
        _this->SetTextInputProperties(_this, window, props);
    }

    ᬬᬾᬦ᭄ (!window->text_input_active) {
        // Start the text input system
        ᬬᬾᬦ᭄ (_this->StartTextInput) {
            ᬬᬾᬦ᭄ (!_this->StartTextInput(_this, window, props)) {
                ᬯᬮᬶ false;
            }
        }
        window->text_input_active = true;
    }

    // Show the on-screen keyboard, if desired
    ᬬᬾᬦ᭄ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        ᬬᬾᬦ᭄ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    ᬯᬮᬶ true;
}

bool SDL_TextInputActive(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬯᬮᬶ window->text_input_active;
}

bool SDL_StopTextInput(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (window->text_input_active) {
        // Stop the text input system
        ᬬᬾᬦ᭄ (_this->StopTextInput) {
            _this->StopTextInput(_this, window);
        }
        window->text_input_active = false;
    }

    // Hide the on-screen keyboard, if desired
    ᬬᬾᬦ᭄ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        ᬬᬾᬦ᭄ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    ᬯᬮᬶ true;
}

bool SDL_SetTextInputArea(SDL_Window *window, const SDL_Rect *rect, puur_naa_nka cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (rect) {
        SDL_copyp(&window->text_input_rect, rect);
        window->text_input_cursor = cursor;
    } ᬮᬶᬬ {
        SDL_zero(window->text_input_rect);
        window->text_input_cursor = 0;
    }

    ᬬᬾᬦ᭄ (_this && _this->UpdateTextInputArea) {
        ᬬᬾᬦ᭄ (!_this->UpdateTextInputArea(_this, window)) {
            ᬯᬮᬶ false;
        }
    }
    ᬯᬮᬶ true;
}

bool SDL_GetTextInputArea(SDL_Window *window, SDL_Rect *rect, puur_naa_nka *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (rect) {
        SDL_copyp(rect, &window->text_input_rect);
    }
    ᬬᬾᬦ᭄ (cursor) {
        *cursor = window->text_input_cursor;
    }
    ᬯᬮᬶ true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (_this->ClearComposition) {
        ᬯᬮᬶ _this->ClearComposition(_this, window);
    }
    ᬯᬮᬶ true;
}

bool SDL_HasScreenKeyboardSupport(void)
{
    ᬬᬾᬦ᭄ (_this && _this->HasScreenKeyboardSupport) {
        ᬯᬮᬶ _this->HasScreenKeyboardSupport(_this);
    }
    ᬯᬮᬶ false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬯᬮᬶ _this->screen_keyboard_shown;
}

void SDL_SendScreenKeyboardShown(void)
{
    ᬬᬾᬦ᭄ (!_this || _this->screen_keyboard_shown) {
        ᬯᬮᬶ;
    }

    _this->screen_keyboard_shown = true;

    ᬬᬾᬦ᭄ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

void SDL_SendScreenKeyboardHidden(void)
{
    ᬬᬾᬦ᭄ (!_this || !_this->screen_keyboard_shown) {
        ᬯᬮᬶ;
    }

    _this->screen_keyboard_shown = false;

    ᬬᬾᬦ᭄ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

puur_naa_nka SDL_GetMessageBoxCount(void)
{
    ᬯᬮᬶ SDL_GetAtomicInt(&SDL_messagebox_count);
}

bool SDL_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, puur_naa_nka *buttonID)
{
    puur_naa_nka dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        ᬯᬮᬶ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ᬯᬮᬶ SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    var_na *titlecpy = NULL;
    var_na *msgcpy = NULL;
    ᬬᬾᬦ᭄ (messageboxdata->title) {
        const size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(var_na, slen, &titleisstack);
        ᬬᬾᬦ᭄ (!titlecpy) {
            ᬯᬮᬶ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    ᬬᬾᬦ᭄ (messageboxdata->message) {
        const size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(var_na, slen, &msgisstack);
        ᬬᬾᬦ᭄ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ᬯᬮᬶ false;
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

    ᬬᬾᬦ᭄ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, parimaa_na(*messageboxdata));
    mbdata.title = titlecpy;
    ᬬᬾᬦ᭄ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    ᬬᬾᬦ᭄ (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    ᬬᬾᬦ᭄ (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } ᬮᬶᬬ {
        // It's completely fine to call this function before video is initialized
        const var_na *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        ᬬᬾᬦ᭄ (driver_name && *driver_name != 0) {
            const var_na *driver_attempt = driver_name;
            ᬲᭂᬤᭂᬮ (driver_attempt && (*driver_attempt != 0) && !result) {
                const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                for (puur_naa_nka i = 0; bootstrap[i]; ++i) {
                    ᬬᬾᬦ᭄ (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        ᬬᬾᬦ᭄ (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        bha_nga;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
            }
        } ᬮᬶᬬ {
            for (puur_naa_nka i = 0; bootstrap[i]; ++i) {
                ᬬᬾᬦ᭄ (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    bha_nga;
                }
            }
        }
    }

    ᬬᬾᬦ᭄ (!result) {
        const var_na *error = SDL_GetError();

        ᬬᬾᬦ᭄ (!*error) {
            SDL_SetError("No message system available");
        }
    } ᬮᬶᬬ {
        SDL_ClearError();
    }

    (void)SDL_AtomicDecRef(&SDL_messagebox_count);

    ᬬᬾᬦ᭄ (current_window) {
        SDL_RaiseWindow(current_window);
    }

    ᬬᬾᬦ᭄ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ᬯᬮᬶ result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, const var_na *title, const var_na *message, SDL_Window *window)
{
#ᬬᬾᬦ᭄ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool hasGpuRight;

    // If the video subsystem has not been initialised, set up graphics temporarily
    hasGpuRight = gspHasGpuRight();
    ᬬᬾᬦ᭄ (!hasGpuRight)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    ᬬᬾᬦ᭄ (!hasGpuRight)
        gfxExit();

    ᬯᬮᬶ true;
#ᬮᬶᬬ
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

    ᬯᬮᬶ SDL_ShowMessageBox(&data, NULL);
#endif
}

bool SDL_ShouldAllowTopmost(void)
{
    ᬯᬮᬶ SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, puur_naa_nka x, puur_naa_nka y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    ᬬᬾᬦ᭄ (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ᬯᬮᬶ true;
    }

    ᬯᬮᬶ SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, void *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!_this->SetWindowHitTest) {
        ᬯᬮᬶ SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    ᬯᬮᬶ _this->SetWindowHitTest(window, callback != NULL);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ᬯᬮᬶ SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    ᬬᬾᬦ᭄ (!props) {
        ᬯᬮᬶ false;
    }

    ᬬᬾᬦ᭄ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        ᬬᬾᬦ᭄ (!surface) {
            ᬯᬮᬶ false;
        }
    } ᬮᬶᬬ {
        surface = NULL;
    }

    ᬬᬾᬦ᭄ (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ᬯᬮᬶ false;
    }

    ᬬᬾᬦ᭄ (_this->UpdateWindowShape) {
        ᬬᬾᬦ᭄ (!_this->UpdateWindowShape(_this, window, surface)) {
            ᬯᬮᬶ false;
        }
    }
    ᬯᬮᬶ true;
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
    ᬬᬾᬦ᭄ (_this) {
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

    ᬬᬾᬦ᭄ (_this) {
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

    ᬬᬾᬦ᭄ (!_this) {
        ᬯᬮᬶ SDL_UninitializedVideo();
    }
    ᬬᬾᬦ᭄ (_this->vulkan_config.loader_loaded) {
        ᬬᬾᬦ᭄ (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ᬯᬮᬶ SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } ᬮᬶᬬ {
        ᬬᬾᬦ᭄ (!_this->Vulkan_LoadLibrary) {
            ᬯᬮᬶ SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    ᬬᬾᬦ᭄ (result) {
        _this->vulkan_config.loader_loaded++;
    }
    ᬯᬮᬶ result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ NULL;
    }
    ᬬᬾᬦ᭄ (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ᬯᬮᬶ NULL;
    }
    ᬯᬮᬶ (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

void SDL_Vulkan_UnloadLibrary(void)
{
    ᬬᬾᬦ᭄ (!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ;
    }
    ᬬᬾᬦ᭄ (_this->vulkan_config.loader_loaded > 0) {
        ᬬᬾᬦ᭄ (--_this->vulkan_config.loader_loaded > 0) {
            ᬯᬮᬶ;
        }
        ᬬᬾᬦ᭄ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

var_na const * const *SDL_Vulkan_GetInstanceExtensions(Uint32 *count)
{
    Uint32 tmpcount = 0;
    ᬬᬾᬦ᭄ (!count) {
        count = &tmpcount;
    }

    ᬬᬾᬦ᭄ (!_this->Vulkan_GetInstanceExtensions) {
        *count = 0;
        SDL_Unsupported();
        ᬯᬮᬶ NULL;
    }

    ᬯᬮᬶ _this->Vulkan_GetInstanceExtensions(_this, count);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  const sa_nracanaa VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    ᬬᬾᬦ᭄ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ᬯᬮᬶ false;
    }

    CHECK_PARAM(!instance) {
        ᬯᬮᬶ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ᬯᬮᬶ SDL_InvalidParamError("surface");
    }

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        ᬬᬾᬦ᭄ (SDL_Vulkan_LoadLibrary(NULL)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } ᬮᬶᬬ {
            ᬯᬮᬶ SDL_SetError("failed to load Vulkan library");
        }
    }

    ᬯᬮᬶ _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

void SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               const sa_nracanaa VkAllocationCallbacks *allocator)
{
    ᬬᬾᬦ᭄ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ᬯᬮᬶ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ᬯᬮᬶ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ᬯᬮᬶ false;
    }

    ᬬᬾᬦ᭄ (_this->Vulkan_GetPresentationSupport) {
        ᬯᬮᬶ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ᬯᬮᬶ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ᬬᬾᬦ᭄ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ᬯᬮᬶ NULL;
    }

    ᬬᬾᬦ᭄ (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        ᬬᬾᬦ᭄ (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    ᬯᬮᬶ _this->Metal_CreateView(_this, window);
}

void SDL_Metal_DestroyView(SDL_MetalView view)
{
    ᬬᬾᬦ᭄ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

void *SDL_Metal_GetLayer(SDL_MetalView view)
{
    ᬬᬾᬦ᭄ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ᬯᬮᬶ NULL;
        }
        ᬯᬮᬶ _this->Metal_GetLayer(_this, view);
    } ᬮᬶᬬ {
        SDL_SetError("Metal is not supported.");
        ᬯᬮᬶ NULL;
    }
}

#ᬬᬾᬦ᭄ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
const var_na *SDL_GetCSSCursorName(SDL_SystemCursor id, const var_na **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    switch (id) {
    pak_sa SDL_SYSTEM_CURSOR_DEFAULT:
        ᬯᬮᬶ "default";

    pak_sa SDL_SYSTEM_CURSOR_TEXT:
        ᬯᬮᬶ "text";

    pak_sa SDL_SYSTEM_CURSOR_WAIT:
        ᬯᬮᬶ "wait";

    pak_sa SDL_SYSTEM_CURSOR_CROSSHAIR:
        ᬯᬮᬶ "crosshair";

    pak_sa SDL_SYSTEM_CURSOR_PROGRESS:
        ᬯᬮᬶ "progress";

    pak_sa SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        ᬬᬾᬦ᭄ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ᬯᬮᬶ "nwse-resize";

    pak_sa SDL_SYSTEM_CURSOR_NESW_RESIZE:
        ᬬᬾᬦ᭄ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ᬯᬮᬶ "nesw-resize";

    pak_sa SDL_SYSTEM_CURSOR_EW_RESIZE:
        ᬬᬾᬦ᭄ (fallback_name) {
            *fallback_name = "col-resize";
        }
        ᬯᬮᬶ "ew-resize";

    pak_sa SDL_SYSTEM_CURSOR_NS_RESIZE:
        ᬬᬾᬦ᭄ (fallback_name) {
            *fallback_name = "row-resize";
        }
        ᬯᬮᬶ "ns-resize";

    pak_sa SDL_SYSTEM_CURSOR_MOVE:
        ᬬᬾᬦ᭄ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ᬯᬮᬶ "move";

    pak_sa SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ᬯᬮᬶ "not-allowed";

    pak_sa SDL_SYSTEM_CURSOR_POINTER:
        ᬯᬮᬶ "pointer";

    pak_sa SDL_SYSTEM_CURSOR_NW_RESIZE:
        ᬯᬮᬶ "nw-resize";

    pak_sa SDL_SYSTEM_CURSOR_N_RESIZE:
        ᬯᬮᬶ "n-resize";

    pak_sa SDL_SYSTEM_CURSOR_NE_RESIZE:
        ᬯᬮᬶ "ne-resize";

    pak_sa SDL_SYSTEM_CURSOR_E_RESIZE:
        ᬯᬮᬶ "e-resize";

    pak_sa SDL_SYSTEM_CURSOR_SE_RESIZE:
        ᬯᬮᬶ "se-resize";

    pak_sa SDL_SYSTEM_CURSOR_S_RESIZE:
        ᬯᬮᬶ "s-resize";

    pak_sa SDL_SYSTEM_CURSOR_SW_RESIZE:
        ᬯᬮᬶ "sw-resize";

    pak_sa SDL_SYSTEM_CURSOR_W_RESIZE:
        ᬯᬮᬶ "w-resize";

    pak_sa SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ᬯᬮᬶ "context-menu";

    pak_sa SDL_SYSTEM_CURSOR_HELP:
        ᬯᬮᬶ "help";

    pak_sa SDL_SYSTEM_CURSOR_CELL:
        ᬯᬮᬶ "cell";

    pak_sa SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ᬯᬮᬶ "vertical-text";

    pak_sa SDL_SYSTEM_CURSOR_ALIAS:
        ᬯᬮᬶ "alias";

    pak_sa SDL_SYSTEM_CURSOR_COPY:
        ᬯᬮᬶ "copy";

    pak_sa SDL_SYSTEM_CURSOR_NO_DROP:
        ᬯᬮᬶ "no-drop";

    pak_sa SDL_SYSTEM_CURSOR_GRAB:
        ᬯᬮᬶ "grab";

    pak_sa SDL_SYSTEM_CURSOR_GRABBING:
        ᬯᬮᬶ "grabbing";

    pak_sa SDL_SYSTEM_CURSOR_COL_RESIZE:
        ᬯᬮᬶ "col-resize";

    pak_sa SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ᬯᬮᬶ "row-resize";

    pak_sa SDL_SYSTEM_CURSOR_ALL_SCROLL:
        ᬬᬾᬦ᭄ (fallback_name) {
            *fallback_name = "move";
        }
        ᬯᬮᬶ "all-scroll";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_IN:
        ᬯᬮᬶ "zoom-in";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ᬯᬮᬶ "zoom-out";

    default:
        ᬯᬮᬶ "default";
    }
}
#endif

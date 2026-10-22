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

#အကယ်၍ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#include <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#အကယ်၍ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
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
        ပြန်ပေး result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ပြန်ပေး result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        ပြန်ပေး result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ပြန်ပေး result;                                                  \
    }

#အကယ်၍ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
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
    အကယ်၍ (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ပြန်ပေး true;
    }
    ပြန်ပေး false;
}

static bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ပြန်ပေး !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

static bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ပြန်ပေး !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

static bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ပြန်ပေး !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

static bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ပြန်ပေး !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

static bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ပြန်ပေး !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
static bool syncHint;

static void SDL_SyncHintWatcher(void *userdata, const var_na *name, const var_na *oldValue, const var_na *newValue)
{
    syncHint = SDL_GetStringBoolean(newValue, false);
}

static void SDL_SyncIfRequired(SDL_Window *window)
{
    အကယ်၍ (syncHint) {
        SDL_SyncWindow(window);
    }
}

static void SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    အကယ်၍ (window->parent) {
        အကယ်၍ (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        အကယ်၍ (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } မဟုတ်ပါက {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = NULL;
    }

    အကယ်၍ (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        အကယ်၍ (parent->first_child) {
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
    ကိန်းပြည့် pitch;
    ကိန်းပြည့် bytes_per_pixel;
} SDL_WindowTextureData;

static Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#အကယ်၍ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    အကယ်၍ (_this->GL_CreateContext) {
        ပြန်ပေး SDL_WINDOW_OPENGL;
    }
#endif
#အကယ်၍ defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    အကယ်၍ (_this->Metal_CreateView) {
        ပြန်ပေး SDL_WINDOW_METAL;
    }
#endif
#အကယ်၍ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    အကယ်၍ (SDL_strcmp(_this->name, "openvr") == 0) {
        ပြန်ပေး SDL_WINDOW_OPENGL;
    }
#endif
    ပြန်ပေး 0;
}

static bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, void **pixels, ကိန်းပြည့် *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    const bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    ကိန်းပြည့် i;
    ကိန်းပြည့် w, h;
    const SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    အကယ်၍ (!data) {
        SDL_Renderer *renderer = NULL;
        const var_na *render_driver = NULL;

        // See if there's a render driver being requested
        const var_na *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        အကယ်၍ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        အကယ်၍ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        အကယ်၍ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = NULL;
        }

        var_na *render_driver_copy = NULL;
        အကယ်၍ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            အကယ်၍ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                var_na *prev = render_driver_copy;
                var_na *ptr = prev;
                နေစဉ် ((ptr = SDL_strchr(ptr, ',')) != NULL) {
                    *ptr = '\0';
                    const bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    အကယ်၍ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } မဟုတ်ပါက {
                        ptr++;
                        prev = ptr;
                    }
                }

                အကယ်၍ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        အကယ်၍ (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            အကယ်၍ (!renderer) {
                // The error for this specific renderer has already been set
                ပြန်ပေး false;
            }
        } မဟုတ်ပါက {
            SDL_assert(render_driver_copy == NULL);
            const ကိန်းပြည့် total = SDL_GetNumRenderDrivers();
            အတွက် (i = 0; i < total; ++i) {
                const var_na *name = SDL_GetRenderDriver(i);
                အကယ်၍ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    အကယ်၍ (renderer) {
                        bha_nga; // this will work.
                    }
                }
            }
            အကယ်၍ (!renderer) {
                ပြန်ပေး SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != NULL); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, parimaa_na(*data));
        အကယ်၍ (!data) {
            SDL_DestroyRenderer(renderer);
            ပြန်ပေး false;
        }
        အကယ်၍ (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            ပြန်ပေး false;
        }

        data->renderer = renderer;
    }

    texture_formats = (const SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, NULL);
    အကယ်၍ (!texture_formats) {
        ပြန်ပေး false;
    }

    // Free any old texture and pixel data
    အကယ်၍ (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = NULL;
    }
    SDL_free(data->pixels);
    data->pixels = NULL;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    အတွက် (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        အကယ်၍ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
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
    အကယ်၍ (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ပြန်ပေး false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        const size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        အကယ်၍ (!data->pixels) {
            ပြန်ပေး false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, NULL);

    ပြန်ပေး true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, ကိန်းပြည့် vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    အကယ်၍ (!data) {
        ပြန်ပေး false;
    }
    အကယ်၍ (!data->renderer) {
        ပြန်ပေး false;
    }
    ပြန်ပေး SDL_SetRenderVSync(data->renderer, vsync);
}

static bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, ကိန်းပြည့် *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    အကယ်၍ (!data) {
        ပြန်ပေး false;
    }
    အကယ်၍ (!data->renderer) {
        ပြန်ပေး false;
    }
    ပြန်ပေး SDL_GetRenderVSync(data->renderer, vsync);
}

static bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects, ကိန်းပြည့် numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    void *src;
    ကိန်းပြည့် w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);
    အကယ်၍ (!data || !data->texture) {
        ပြန်ပေး SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    အကယ်၍ (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (void *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        အကယ်၍ (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            ပြန်ပေး false;
        }

        အကယ်၍ (!SDL_RenderTexture(data->renderer, data->texture, NULL, NULL)) {
            ပြန်ပေး false;
        }

        SDL_RenderPresent(data->renderer);
    }
    ပြန်ပေး true;
}

static void SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    အကယ်၍ (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, NULL);

        အကယ်၍ (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        အကယ်၍ (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

static SDL_VideoDevice *_this = NULL;
static SDL_AtomicInt SDL_messagebox_count;

static ကိန်းပြည့် SDLCALL cmpmodes(const void *A, const void *B)
{
    const SDL_DisplayMode *a = (const SDL_DisplayMode *)A;
    const SDL_DisplayMode *b = (const SDL_DisplayMode *)B;
    ကိန်းပြည့် a_refresh_rate = (ကိန်းပြည့်)(a->refresh_rate * 100);
    ကိန်းပြည့် b_refresh_rate = (ကိန်းပြည့်)(b->refresh_rate * 100);
    ကိန်းပြည့် a_pixel_density = (ကိန်းပြည့်)(a->pixel_density * 100);
    ကိန်းပြည့် b_pixel_density = (ကိန်းပြည့်)(b->pixel_density * 100);

    အကယ်၍ (a->w != b->w) {
        ပြန်ပေး b->w - a->w;
    } မဟုတ်ပါက အကယ်၍ (a->h != b->h) {
        ပြန်ပေး b->h - a->h;
    } မဟုတ်ပါက အကယ်၍ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ပြန်ပေး SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } မဟုတ်ပါက အကယ်၍ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ပြန်ပေး SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } မဟုတ်ပါက အကယ်၍ (a_refresh_rate != b_refresh_rate) {
        ပြန်ပေး b_refresh_rate - a_refresh_rate;
    } မဟုတ်ပါက အကယ်၍ (a_pixel_density != b_pixel_density) {
        ပြန်ပေး a_pixel_density - b_pixel_density;
    }
    ပြန်ပေး 0;
}

bool SDL_UninitializedVideo(void)
{
    ပြန်ပေး SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
static const VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

ကိန်းပြည့် SDL_GetNumVideoDrivers(void)
{
    static ကိန်းပြည့် num_drivers = -1;

    အကယ်၍ (num_drivers >= 0) {
        ပြန်ပေး num_drivers;
    }

    num_drivers = 0;

    // Build a list of unique video drivers.
    အတွက် (ကိန်းပြည့် i = 0; bootstrap[i] != NULL; ++i) {
        bool duplicate = false;
        အတွက် (ကိန်းပြည့် j = 0; j < i; ++j) {
            အကယ်၍ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                bha_nga;
            }
        }

        အကယ်၍ (!duplicate) {
            deduped_bootstrap[num_drivers++] = bootstrap[i];
        }
    }

    ပြန်ပေး num_drivers;
}

const var_na *SDL_GetVideoDriver(ကိန်းပြည့် index)
{
    CHECK_PARAM(index < 0 || index >= SDL_GetNumVideoDrivers()) {
        SDL_InvalidParamError("index");
        ပြန်ပေး NULL;
    }
    ပြန်ပေး deduped_bootstrap[index]->name;
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
    ကိန်းပြည့် i = 0;

    // Check to make sure we don't overwrite '_this'
    အကယ်၍ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    အကယ်၍ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        goto pre_driver_error;
    }
    init_events = true;
    အကယ်၍ (!SDL_InitKeyboard()) {
        goto pre_driver_error;
    }
    init_keyboard = true;
    အကယ်၍ (!SDL_PreInitMouse()) {
        goto pre_driver_error;
    }
    init_mouse = true;
    အကယ်၍ (!SDL_InitTouch()) {
        goto pre_driver_error;
    }
    init_touch = true;
    အကယ်၍ (!SDL_InitPen()) {
        goto pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = NULL;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    အကယ်၍ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    အကယ်၍ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    အကယ်၍ (driver_name && *driver_name != 0) {
        const var_na *driver_attempt = driver_name;
        နေစဉ် (driver_attempt && *driver_attempt != 0 && !video) {
            const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            အတွက် (i = 0; bootstrap[i]; ++i) {
                အကယ်၍ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    အကယ်၍ (video) {
                        bha_nga;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
        }
    } မဟုတ်ပါက {
        အတွက် (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            အကယ်၍ (video) {
                bha_nga;
            }
        }
    }
    အကယ်၍ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } မဟုတ်ပါက {
        အကယ်၍ (driver_name) {
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
    အကယ်၍ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ပြန်ပေး false;
    }

    // Make sure some displays were added
    အကယ်၍ (_this->num_displays == 0) {
        SDL_QuitVideo();
        ပြန်ပေး SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, NULL);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    အကယ်၍ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    ပြန်ပေး true;

pre_driver_error:
    SDL_assert(_this == NULL);
    အကယ်၍ (init_pen) {
        SDL_QuitPen();
    }
    အကယ်၍ (init_touch) {
        SDL_QuitTouch();
    }
    အကယ်၍ (init_mouse) {
        SDL_QuitMouse();
    }
    အကယ်၍ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    အကယ်၍ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    ပြန်ပေး false;
}

const var_na *SDL_GetCurrentVideoDriver(void)
{
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    ပြန်ပေး _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(void)
{
    ပြန်ပေး _this;
}

bool SDL_OnVideoThread(void)
{
    ပြန်ပေး (_this && SDL_GetCurrentThreadID() == _this->thread);
}

void SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    အကယ်၍ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(void)
{
    အကယ်၍ (_this) {
        ပြန်ပေး _this->system_theme;
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_SYSTEM_THEME_UNKNOWN;
    }
}

void SDL_UpdateDesktopBounds(void)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(NULL);
    အကယ်၍ (displays) {
        အတွက် (ကိန်းပြည့် i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            အကယ်၍ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                အကယ်၍ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } မဟုတ်ပါက {
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
    အကယ်၍ (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    အကယ်၍ (mode->refresh_rate_numerator > 0) {
        အကယ်၍ (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (float)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } မဟုတ်ပါက {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(const SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    အကယ်၍ (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, parimaa_na(display.desktop_mode));
    }
    ပြန်ပေး SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(const SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    ကိန်းပြည့် i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(parimaa_na(*new_display));
    အကယ်၍ (!new_display) {
        ပြန်ပေး 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->num_displays + 1) * parimaa_na(*displays));
    အကယ်၍ (!displays) {
        SDL_free(new_display);
        ပြန်ပေး 0;
    }
    _this->displays = displays;
    _this->displays[_this->num_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    အကယ်၍ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } မဟုတ်ပါက {
        var_na name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    အကယ်၍ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    အတွက် (i = 0; i < new_display->num_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    အကယ်၍ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    ပြန်ပေး id;
}

void SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    အတွက် (window = _this->windows; window; window = window->next) {
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
    ကိန်းပြည့် display_index = SDL_GetDisplayIndex(displayID);
    အကယ်၍ (display_index < 0) {
        ပြန်ပေး;
    }

    display = _this->displays[display_index];

    အကယ်၍ (send_event) {
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

    အကယ်၍ (display_index < (_this->num_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->num_displays - display_index - 1) * parimaa_na(_this->displays[display_index]));
    }
    --_this->num_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(ကိန်းပြည့် *count)
{
    ကိန်းပြည့် i;
    SDL_DisplayID *displays;

    အကယ်၍ (!_this) {
        အကယ်၍ (count) {
            *count = 0;
        }

        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->num_displays + 1) * parimaa_na(*displays));
    အကယ်၍ (displays) {
        အကယ်၍ (count) {
            *count = _this->num_displays;
        }

        အတွက် (i = 0; i < _this->num_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } မဟုတ်ပါက {
        အကယ်၍ (count) {
            *count = 0;
        }
    }
    ပြန်ပေး displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    ကိန်းပြည့် display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    အကယ်၍ (display_index < 0) {
        ပြန်ပေး NULL;
    }
    ပြန်ပေး _this->displays[display_index];
}

static SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    အကယ်၍ (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    အကယ်၍ (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    ပြန်ပေး displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ပြန်ပေး SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(void)
{
    အကယ်၍ (!_this || _this->num_displays == 0) {
        SDL_UninitializedVideo();
        ပြန်ပေး 0;
    }
    ပြန်ပေး _this->displays[0]->id;
}

ကိန်းပြည့် SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    ကိန်းပြည့် display_index;

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး -1;
    }

    အတွက် (display_index = 0; display_index < _this->num_displays; ++display_index) {
        အကယ်၍ (displayID == _this->displays[display_index]->id) {
            ပြန်ပေး display_index;
        }
    }
    SDL_SetError("Invalid display");
    ပြန်ပေး -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ပြန်ပေး display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ပြန်ပေး SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    အကယ်၍ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ပြန်ပေး display->props;
}

const var_na *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ပြန်ပေး display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ပြန်ပေး SDL_InvalidParamError("rect");
    }

    အကယ်၍ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        အကယ်၍ (_this->GetDisplayBounds(_this, display, rect)) {
            ပြန်ပေး true;
        }
    }

    // Assume that the displays are left to right
    အကယ်၍ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } မဟုတ်ပါက {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ပြန်ပေး true;
}

static ကိန်းပြည့် ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ပြန်ပေး hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ပြန်ပေး SDL_InvalidParamError("rect");
    }

    အကယ်၍ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ပြန်ပေး true;
    }

    အကယ်၍ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        အကယ်၍ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ပြန်ပေး true;
        }
    }

    // Oh well, just give the entire display bounds.
    ပြန်ပေး SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    အကယ်၍ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ပြန်ပေး display->natural_orientation;
    } မဟုတ်ပါက {
        // Default to landscape if the driver hasn't set it
        ပြန်ပေး SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    အကယ်၍ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ပြန်ပေး display->current_orientation;
    } မဟုတ်ပါက {
        // Default to landscape if the driver hasn't set it
        ပြန်ပေး SDL_ORIENTATION_LANDSCAPE;
    }
}

void SDL_SetDisplayContentScale(SDL_VideoDisplay *display, float scale)
{
    အကယ်၍ (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        အတွက် (window = _this->windows; window; window = window->next) {
            အကယ်၍ (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

float SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ပြန်ပေး display->content_scale;
}

void SDL_SetWindowHDRProperties(SDL_Window *window, const SDL_HDROutputProperties *HDR, bool send_event)
{
    const SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    အကယ်၍ (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        အကယ်၍ (send_event) {
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

	အကယ်၍ (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    အကယ်၍ (changed && !SDL_DriverSendsHDRChanges(_this)) {
        အတွက် (SDL_Window *w = display->device->windows; w; w = w->next) {
            အကယ်၍ (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

static void SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    အကယ်၍ (display->num_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
static const SDL_DisplayMode *SDL_GetFullscreenModeMatch(const SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    အကယ်၍ (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ပြန်ပေး NULL;
    }

    SDL_memcpy(&fullscreen_mode, mode, parimaa_na(fullscreen_mode));
    အကယ်၍ (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = NULL;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    အကယ်၍ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        အကယ်၍ (!mode) {
            အတွက် (ကိန်းပြည့် i = 0; i < display->num_fullscreen_modes; ++i) {
                အကယ်၍ (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], parimaa_na(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }

        // Search for a mode with the same characteristics
        အကယ်၍ (!mode) {
            အတွက် (ကိန်းပြည့် i = 0; i < display->num_fullscreen_modes; ++i) {
                အကယ်၍ (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    bha_nga;
                }
            }
        }
    }
    ပြန်ပေး mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    ကိန်းပြည့် i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, parimaa_na(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->num_fullscreen_modes;
    အတွက် (i = 0; i < nmodes; ++i) {
        အကယ်၍ (cmpmodes(&new_mode, &modes[i]) == 0) {
            ပြန်ပေး false;
        }
    }

    // Go ahead and add the new mode
    အကယ်၍ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * parimaa_na(*modes));
        အကယ်၍ (!modes) {
            ပြန်ပေး false;
        }

        အကယ်၍ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * parimaa_na(*modes));
            အတွက် (i = 0; i < nmodes; ++i) {
                အကယ်၍ (display->current_mode == &display->fullscreen_modes[i]) {
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

    ပြန်ပေး true;
}

void SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    ကိန်းပြည့် i;

    အတွက် (i = display->num_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = NULL;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = NULL;
    display->num_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, ကိန်းပြည့် *count)
{
    ကိန်းပြည့် i;
    ကိန်းပြည့် num_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    အကယ်၍ (count) {
        *count = 0;
    }

    CHECK_DISPLAY_MAGIC(display, NULL);

    SDL_UpdateFullscreenDisplayModes(display);

    num_modes = display->num_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((num_modes + 1) * parimaa_na(*result) + num_modes * parimaa_na(**result));
    အကယ်၍ (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((num_modes + 1) * parimaa_na(*result)));
        အကယ်၍ (num_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, num_modes * parimaa_na(*modes));
        }
        အတွက် (i = 0; i < num_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = NULL;

        အကယ်၍ (count) {
            *count = num_modes;
        }
    } မဟုတ်ပါက {
        အကယ်၍ (count) {
            *count = 0;
        }
    }
    ပြန်ပေး result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, ကိန်းပြည့် w, ကိန်းပြည့် h, float refresh_rate, bool include_high_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        ပြန်ပေး SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    const SDL_DisplayMode *mode, *closest = NULL;
    float aspect_ratio;
    ကိန်းပြည့် i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    အကယ်၍ (h > 0) {
        aspect_ratio = (float)w / h;
    } မဟုတ်ပါက {
        aspect_ratio = 1.0f;
    }

    အကယ်၍ (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    အတွက် (i = 0; i < display->num_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        အကယ်၍ (w > mode->w) {
            // Out of sorted modes large enough here
            bha_nga;
        }
        အကယ်၍ (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            continue;
        }
        အကယ်၍ (mode->pixel_density > 1.0f && !include_high_density_modes) {
            continue;
        }
        အကယ်၍ (closest) {
            float current_aspect_ratio = (float)mode->w / mode->h;
            float closest_aspect_ratio = (float)closest->w / closest->h;
            အကယ်၍ (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                continue;
            }

            အကယ်၍ (mode->w == closest->w && mode->h == closest->h) {
                အကယ်၍ (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    continue;
                }
                အကယ်၍ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    continue;
                }
            }
        }

        closest = mode;
    }
    အကယ်၍ (!closest) {
        ပြန်ပေး SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    ပြန်ပေး true;
}

static bool DisplayModeChanged(const SDL_DisplayMode *old_mode, const SDL_DisplayMode *new_mode)
{
    ပြန်ပေး ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

void SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    အကယ်၍ (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ပြန်ပေး;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    အကယ်၍ (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        အကယ်၍ (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

const SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ပြန်ပေး &display->desktop_mode;
}

void SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    အကယ်၍ (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } မဟုတ်ပါက {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    အကယ်၍ (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

const SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, NULL);

    ပြန်ပေး display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    အကယ်၍ (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ပြန်ပေး true;
    }

    အကယ်၍ (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    အကယ်၍ (mode == display->current_mode) {
        ပြန်ပေး true;
    }
#endif

    // Actually change the display mode
    အကယ်၍ (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        အကယ်၍ (!result) {
            ပြန်ပေး false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ပြန်ပေး true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
static void SDL_GetClosestPointOnRect(const SDL_Rect *rect, SDL_Point *point)
{
    const ကိန်းပြည့် right = rect->x + rect->w - 1;
    const ကိန်းပြည့် bottom = rect->y + rect->h - 1;

    အကယ်၍ (point->x < rect->x) {
        point->x = rect->x;
    } မဟုတ်ပါက အကယ်၍ (point->x > right) {
        point->x = right;
    }

    အကယ်၍ (point->y < rect->y) {
        point->y = rect->y;
    } မဟုတ်ပါက အကယ်၍ (point->y > bottom) {
        point->y = bottom;
    }
}

static SDL_DisplayID GetDisplayForRect(ကိန်းပြည့် x, ကိန်းပြည့် y, ကိန်းပြည့် w, ကိန်းပြည့် h)
{
    ကိန်းပြည့် i, dist;
    SDL_DisplayID closest = 0;
    ကိန်းပြည့် closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    အကယ်၍ (_this) {
        အတွက် (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            အကယ်၍ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, NULL)) {
                ပြန်ပေး display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            အကယ်၍ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    အကယ်၍ (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    ပြန်ပေး closest;
}

void SDL_RelativeToGlobalForWindow(SDL_Window *window, ကိန်းပြည့် rel_x, ကိန်းပြည့် rel_y, ကိန်းပြည့် *abs_x, ကိန်းပြည့် *abs_y)
{
    SDL_Window *w;

    အကယ်၍ (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        အတွက် (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            အကယ်၍ (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    အကယ်၍ (abs_x) {
        *abs_x = rel_x;
    }
    အကယ်၍ (abs_y) {
        *abs_y = rel_y;
    }
}

void SDL_GlobalToRelativeForWindow(SDL_Window *window, ကိန်းပြည့် abs_x, ကိန်းပြည့် abs_y, ကိန်းပြည့် *rel_x, ကိန်းပြည့် *rel_y)
{
    SDL_Window *w;

    အကယ်၍ (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        အတွက် (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            အကယ်၍ (!SDL_WINDOW_IS_POPUP(w)) {
                bha_nga;
            }
        }
    }

    အကယ်၍ (rel_x) {
        *rel_x = abs_x;
    }
    အကယ်၍ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(const SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ပြန်ပေး 0;
    }

    ပြန်ပေး GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(const SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ပြန်ပေး 0;
    }

    ပြန်ပေး GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

static SDL_DisplayID GetDisplayAtOrigin(ကိန်းပြည့် x, ကိန်းပြည့် y)
{
    အတွက် (ကိန်းပြည့် i = 0; i < _this->num_displays; ++i) {
        SDL_Rect rect;
        const SDL_DisplayID cur_id = _this->displays[i]->id;
        အကယ်၍ (SDL_GetDisplayBounds(cur_id, &rect)) {
            အကယ်၍ (x == rect.x && y == rect.y) {
                ပြန်ပေး cur_id;
            }
        }
    }

    ပြန်ပေး 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    ကိန်းပြည့် x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    အကယ်၍ (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    အကယ်၍ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        အကယ်၍ (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } မဟုတ်ပါက {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    အကယ်၍ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ပြန်ပေး displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, NULL);

    // An explicit fullscreen display overrides all
    အကယ်၍ (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    အကယ်၍ (!displayID) {
        displayID = window->pending_displayID;
    }
    အကယ်၍ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        const ကိန်းပြည့် x = window->last_position_pending ? window->pending.x : window->x;
        const ကိန်းပြည့် y = window->last_position_pending ? window->pending.y : window->y;
        const ကိန်းပြည့် w = window->last_size_pending ? window->pending.w : window->w;
        const ကိန်းပြည့် h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        အကယ်၍ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    အကယ်၍ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    ပြန်ပေး SDL_GetVideoDisplay(displayID);
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
    အကယ်၍ (fs_display) {
        SDL_SetNumberProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } မဟုတ်ပါက {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    ပြန်ပေး GetDisplayForWindow(window);
}

static void SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    အကယ်၍ (SDL_SendsDisplayChanges(_this)) {
        ပြန်ပေး;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    အကယ်၍ (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        အကယ်၍ (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            အကယ်၍ (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                ကိန်းပြည့် old_area = old_overlap.w * old_overlap.h;
                ကိန်းပြည့် new_area = new_overlap.w * new_overlap.h;
                float new_overlap_ratio = (new_area / ((float)old_area + new_area));
                အကယ်၍ (new_overlap_ratio < 0.80) {
                    ပြန်ပေး;
                }
            }
        }
    }

    အကယ်၍ (displayID != window->displayID) {
        ကိန်းပြည့် i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        အတွက် (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            အကယ်၍ (display->fullscreen_window == window) {
                အကယ်၍ (display_index != i) {
                    အကယ်၍ (display_index < 0) {
                        display_index = i;
                    } မဟုတ်ပါက {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        အကယ်၍ (new_display->fullscreen_window &&
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

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (ကိန်းပြည့်)displayID, 0);
    }
}

float SDL_GetWindowPixelDensity(SDL_Window *window)
{
    ကိန်းပြည့် window_w, window_h, pixel_w, pixel_h;
    float pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    အကယ်၍ (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (float)pixel_w / window_w;
    }
    ပြန်ပေး pixel_density;
}

float SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ပြန်ပေး window->display_scale;
}

static void SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    float display_scale;

    အကယ်၍ (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } မဟုတ်ပါက {
        const float pixel_density = SDL_GetWindowPixelDensity(window);
        const float content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    အကယ်၍ (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = NULL;
    SDL_DisplayMode *mode = NULL;
    ကိန်းပြည့် i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    အကယ်၍ (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    အကယ်၍ (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        အကယ်၍ (!display) {
            // This should never happen, but it did...
            goto done;
        }
    } မဟုတ်ပါက {
        အတွက် (i = 0; i < _this->num_displays; ++i) {
            display = _this->displays[i];
            အကယ်၍ (display->fullscreen_window == window) {
                bha_nga;
            }
        }
        အကယ်၍ (!display || i == _this->num_displays) {
            // Already not fullscreen on any display
            display = NULL;
        }
    }

    အကယ်၍ (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        အကယ်၍ (mode) {
            window->fullscreen_exclusive = true;
        } မဟုတ်ပါက {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#အကယ်၍ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    အကယ်၍ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        အကယ်၍ (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            အကယ်၍ (display) {
                display->fullscreen_window = NULL;
            }
            goto done;
        }
        အကယ်၍ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            အကယ်၍ (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                အကယ်၍ (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    goto error;
                }
            } မဟုတ်ပါက အကယ်၍ (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                အတွက် (i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    အကယ်၍ (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, NULL);
                        အကယ်၍ (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = NULL;
                    }
                }
            }

            အကယ်၍ (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                goto done;
            }
        }
    }
#endif

    အကယ်၍ (display) {
        // Restore the video mode on other displays if needed
        အတွက် (i = 0; i < _this->num_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            အကယ်၍ (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, NULL);
                other->fullscreen_window = NULL;
            }
        }
    }

    အကယ်၍ (fullscreen) {
        ကိန်းပြည့် mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        အကယ်၍ (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        အကယ်၍ (!SDL_SetDisplayModeForDisplay(display, mode)) {
            goto error;
        }
        အကယ်၍ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            အကယ်၍ (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } မဟုတ်ပါက {
                resized = true;
            }

            အကယ်၍ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                အကယ်၍ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } မဟုတ်ပါက အကယ်၍ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                goto error;
            }
        }

        အကယ်၍ (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            အကယ်၍ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                အကယ်၍ (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } မဟုတ်ပါက {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                အကယ်၍ (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                အကယ်၍ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } မဟုတ်ပါက {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } မဟုတ်ပါက {
        bool resized = false;

        // Restore the desktop mode
        အကယ်၍ (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, NULL);
        }
        အကယ်၍ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            အကယ်၍ (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                အကယ်၍ (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } မဟုတ်ပါက {
                resized = true;
            }

            အကယ်၍ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                အကယ်၍ (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } မဟုတ်ပါက အကယ်၍ (ret == SDL_FULLSCREEN_FAILED) {
                goto error;
            }
        }

        အကယ်၍ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            အကယ်၍ (display) {
                display->fullscreen_window = NULL;
            }

            အကယ်၍ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                အကယ်၍ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } မဟုတ်ပါက {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    ပြန်ပေး true;

error:
    အကယ်၍ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ပြန်ပေး false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, const SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (mode) {
        အကယ်၍ (!SDL_GetFullscreenModeMatch(mode)) {
            ပြန်ပေး SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } မဟုတ်ပါက {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#အကယ်၍ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    အကယ်၍ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    အကယ်၍ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    ပြန်ပေး true;
}

const SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);
    CHECK_WINDOW_NOT_POPUP(window, NULL);

    အကယ်၍ (window->flags & SDL_WINDOW_FULLSCREEN) {
        ပြန်ပေး SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

void *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    အကယ်၍ (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ပြန်ပေး NULL;
    }
    ပြန်ပေး _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    const SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    အကယ်၍ (mode) {
        ပြန်ပေး mode->format;
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

static SDL_INLINE bool IsAcceptingDragAndDrop(void)
{
    အကယ်၍ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ပြန်ပေး true;
    }
    ပြန်ပေး false;
}

// prepare a newly-created window
static SDL_INLINE void PrepareDragAndDropSupport(SDL_Window *window)
{
    အကယ်၍ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
void SDL_ToggleDragAndDropSupport(void)
{
    အကယ်၍ (_this && _this->AcceptDragAndDrop) {
        const bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        အတွက် (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(ကိန်းပြည့် *count)
{
    အကယ်၍ (count) {
        *count = 0;
    }

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }

    SDL_Window *window;
    ကိန်းပြည့် num_added = 0;
    ကိန်းပြည့် num_windows = 0;
    အတွက် (window = _this->windows; window; window = window->next) {
        ++num_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((num_windows + 1) * parimaa_na(*windows));
    အကယ်၍ (!windows) {
        ပြန်ပေး NULL;
    }

    အတွက် (window = _this->windows; window; window = window->next) {
        windows[num_added++] = window;
        အကယ်၍ (num_added == num_windows) {
            // Race condition? Multi-threading not supported, ignore it
            bha_nga;
        }
    }
    windows[num_added] = NULL;

    အကယ်၍ (count) {
        *count = num_added;
    }
    ပြန်ပေး windows;
}

static void ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    အကယ်၍ (!SDL_WINDOW_IS_POPUP(window)) {
        အကယ်၍ (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        အကယ်၍ (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        အကယ်၍ (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        အကယ်၍ (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        အကယ်၍ (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        အကယ်၍ (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

static void SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    အကယ်၍ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } မဟုတ်ပါက {
        ApplyWindowFlags(window, flags);
        အကယ်၍ (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#အကယ်၍ defined(SDL_PLATFORM_LINUX)
    အကယ်၍ (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_SetWindowProgressValue(window, 0.0f);
    }
#endif
}

static bool SDL_ContextNotSupported(const var_na *name)
{
    ပြန်ပေး SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

static bool SDL_DllNotSupported(const var_na *name)
{
    ပြန်ပေး SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
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

    အတွက် (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        အကယ်၍ (SDL_WindowFlagProperties[i].invert_value) {
            အကယ်၍ (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } မဟုတ်ပါက {
            အကယ်၍ (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    ပြန်ပေး flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    const var_na *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, NULL);
    ကိန်းပြည့် x = (ကိန်းပြည့်)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    ကိန်းပြည့် y = (ကိန်းပြည့်)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_UNDEFINED);
    ကိန်းပြည့် w = (ကိန်းပြည့်)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 0);
    ကိန်းပြည့် h = (ကိန်းပြည့်)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, NULL);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    အကယ်၍ (!_this) {
        // Initialize the video system if needed
        အကယ်၍ (!SDL_Init(SDL_INIT_VIDEO)) {
            ပြန်ပေး NULL;
        }

        // Make clang-tidy happy
        အကယ်၍ (!_this) {
            ပြန်ပေး NULL;
        }
    }

    အကယ်၍ ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ပြန်ပေး NULL;
    }

    အကယ်၍ ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        အကယ်၍ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ပြန်ပေး NULL;
        }

        // Tooltip and popup menu window must specify a parent window
        အကယ်၍ (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ပြန်ပေး NULL;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    အကယ်၍ (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned ကိန်းပြည့်)type_flags);
        ပြန်ပေး NULL;
    }

    // Make sure the display list is up to date for window placement
    အကယ်၍ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    အကယ်၍ (w < 1) {
        w = 1;
    }
    အကယ်၍ (h < 1) {
        h = 1;
    }

    အကယ်၍ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        အကယ်၍ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } မဟုတ်ပါက အကယ်၍ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        အကယ်၍ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        အကယ်၍ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        အကယ်၍ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            အကယ်၍ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        အကယ်၍ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            အကယ်၍ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    အကယ်၍ (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned ကိန်းပြည့်)graphics_flags);
        ပြန်ပေး NULL;
    }

    // Some platforms have certain graphics backends enabled by default
    အကယ်၍ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    အကယ်၍ (flags & SDL_WINDOW_OPENGL) {
        အကယ်၍ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ပြန်ပေး NULL;
        }
        အကယ်၍ (!SDL_GL_LoadLibrary(NULL)) {
            ပြန်ပေး NULL;
        }
    }

    အကယ်၍ (flags & SDL_WINDOW_VULKAN) {
        အကယ်၍ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ပြန်ပေး NULL;
        }
        အကယ်၍ (!SDL_Vulkan_LoadLibrary(NULL)) {
            ပြန်ပေး NULL;
        }
    }

    အကယ်၍ (flags & SDL_WINDOW_METAL) {
        အကယ်၍ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ပြန်ပေး NULL;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, parimaa_na(*window));
    အကယ်၍ (!window) {
        ပြန်ပေး NULL;
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
    အကယ်၍ (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    အကယ်၍ (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    အကယ်၍ (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    အကယ်၍ (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    အကယ်၍ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_PushError();
        SDL_DestroyWindow(window);
        SDL_PopError();
        ပြန်ပေး NULL;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#အကယ်၍ !defined(SDL_PLATFORM_WINDOWS)
    အကယ်၍ (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    အကယ်၍ (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ပြန်ပေး window;
}

SDL_Window *SDL_CreateWindow(const var_na *title, ကိန်းပြည့် w, ကိန်းပြည့် h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    အကယ်၍ (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ပြန်ပေး window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, ကိန်းပြည့် offset_x, ကိန်းပြည့် offset_y, ကိန်းပြည့် w, ကိန်းပြည့် h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    အကယ်၍ (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ပြန်ပေး NULL;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, offset_x);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, offset_y);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, w);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, h);
    SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ပြန်ပေး window;
}

static bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    အကယ်၍ (!_this->ReconfigureWindow) {
        ပြန်ပေး false;
    }

    const SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    အကယ်၍ (graphics_flags & (graphics_flags - 1)) {
        ပြန်ပေး SDL_SetError("Conflicting window flags specified");
    }

    အကယ်၍ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ပြန်ပေး SDL_ContextNotSupported("OpenGL");
    }
    အကယ်၍ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ပြန်ပေး SDL_ContextNotSupported("Vulkan");
    }
    အကယ်၍ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ပြန်ပေး SDL_ContextNotSupported("Metal");
    }

    အကယ်၍ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        အကယ်၍ (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ပြန်ပေး false;
        }
    } မဟုတ်ပါက {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        အကယ်၍ (!_this->ReconfigureWindow(_this, window, 0)) {
            ပြန်ပေး false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        အကယ်၍ (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        အကယ်၍ (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    အကယ်၍ (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(NULL);
        အကယ်၍ (!loaded_opengl) {
            ပြန်ပေး false;
        }
    } မဟုတ်ပါက အကယ်၍ (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(NULL);
        အကယ်၍ (!loaded_vulkan) {
            ပြန်ပေး false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    အကယ်၍ (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        အကယ်၍ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        အကယ်၍ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        ပြန်ပေး false;
    }

    window->flags |= graphics_flags;

    ပြန်ပေး true;
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
    အကယ်၍ (graphics_flags & (graphics_flags - 1)) {
        ပြန်ပေး SDL_SetError("Conflicting window flags specified");
    }

    အကယ်၍ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ပြန်ပေး SDL_ContextNotSupported("OpenGL");
    }
    အကယ်၍ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ပြန်ပေး SDL_ContextNotSupported("Vulkan");
    }
    အကယ်၍ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ပြန်ပေး SDL_ContextNotSupported("Metal");
    }

    အကယ်၍ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } မဟုတ်ပါက {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    အကယ်၍ (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    အကယ်၍ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        const bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    အကယ်၍ ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        အကယ်၍ (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } မဟုတ်ပါက {
            need_gl_unload = true;
        }
    } မဟုတ်ပါက အကယ်၍ (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    အကယ်၍ ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        အကယ်၍ (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } မဟုတ်ပါက {
            need_vulkan_unload = true;
        }
    } မဟုတ်ပါက အကယ်၍ (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    အကယ်၍ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    အကယ်၍ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    အကယ်၍ (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    အကယ်၍ (need_gl_load) {
        အကယ်၍ (!SDL_GL_LoadLibrary(NULL)) {
            ပြန်ပေး false;
        }
        loaded_opengl = true;
    }

    အကယ်၍ (need_vulkan_load) {
        အကယ်၍ (!SDL_Vulkan_LoadLibrary(NULL)) {
            ပြန်ပေး false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    အကယ်၍ (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        အကယ်၍ (!_this->CreateSDLWindow(_this, window, 0)) {
            အကယ်၍ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            အကယ်၍ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            ပြန်ပေး false;
        }
    }

    အကယ်၍ (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    အကယ်၍ (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    အကယ်၍ (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    အကယ်၍ (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    အကယ်၍ (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    အကယ်၍ (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    အကယ်၍ (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ပြန်ပေး true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    အကယ်၍ (!SDL_ReconfigureWindowInternal(window, flags)) {
        ပြန်ပေး SDL_RecreateWindow(window, flags);
    }

    ပြန်ပေး true;
}

bool SDL_HasWindows(void)
{
    ပြန်ပေး _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ပြန်ပေး window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    အကယ်၍ (id) {
        အတွက် (window = _this->windows; window; window = window->next) {
            အကယ်၍ (window->id == id) {
                ပြန်ပေး window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ပြန်ပေး NULL;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    ပြန်ပေး window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    အကယ်၍ (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ပြန်ပေး window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ပြန်ပေး window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, const var_na *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (title == window->title) {
        ပြန်ပေး true;
    }
    အကယ်၍ (!title) {
        title = "";
    }
    အကယ်၍ (window->title && SDL_strcmp(title, window->title) == 0) {
        ပြန်ပေး true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    အကယ်၍ (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ပြန်ပေး true;
}

const var_na *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ပြန်ပေး window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ပြန်ပေး SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    အကယ်၍ (!window->icon) {
        ပြန်ပေး false;
    }

    အကယ်၍ (!_this->SetWindowIcon) {
        ပြန်ပေး SDL_Unsupported();
    }

    ပြန်ပေး _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, ကိန်းပြည့် x, ကိန်းပြည့် y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    const ကိန်းပြည့် w = window->last_size_pending ? window->pending.w : window->windowed.w;
    const ကိန်းပြည့် h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    အကယ်၍ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    အကယ်၍ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    အကယ်၍ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        အကယ်၍ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } မဟုတ်ပါက အကယ်၍ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        အကယ်၍ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        အကယ်၍ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            အကယ်၍ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ပြန်ပေး false;
            }
        }
        အကယ်၍ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        အကယ်၍ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } မဟုတ်ပါက {
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
    အကယ်၍ (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    အကယ်၍ (_this->SetWindowPosition) {
        const bool result = _this->SetWindowPosition(_this, window);
        အကယ်၍ (result) {
            SDL_SyncIfRequired(window);
        }
        ပြန်ပေး result;
    }

    ပြန်ပေး SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, ကိန်းပြည့် *x, ကိန်းပြည့် *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#မဟုတ်ပါက
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    အကယ်၍ (use_display_origin) {
        SDL_DisplayID displayID;

        အကယ်၍ (x) {
            *x = 0;
        }
        အကယ်၍ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        အကယ်၍ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            အကယ်၍ (x) {
                *x = bounds.x;
            }
            အကယ်၍ (y) {
                *y = bounds.y;
            }
        }
    } မဟုတ်ပါက {
        const bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        အကယ်၍ (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        အကယ်၍ (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ပြန်ပေး true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (!_this->SetWindowBordered) {
        ပြန်ပေး SDL_Unsupported();
    }

    const bool want = bordered;
    const bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    အကယ်၍ (want != have) {
        အကယ်၍ (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } မဟုတ်ပါက {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ပြန်ပေး true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (!_this->SetWindowResizable) {
        ပြန်ပေး SDL_Unsupported();
    }

    const bool want = resizable;
    const bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    အကယ်၍ (want != have) {
        အကယ်၍ (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } မဟုတ်ပါက {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ပြန်ပေး true;
}

bool SDL_SetWindowAlwaysOnTop(SDL_Window *window, bool on_top)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (!_this->SetWindowAlwaysOnTop) {
        ပြန်ပေး SDL_Unsupported();
    }

    const bool want = on_top;
    const bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_TOP) != 0);
    အကယ်၍ (want != have) {
        အကယ်၍ (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        } မဟုတ်ပါက {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_TOP;
        }
        _this->SetWindowAlwaysOnTop(_this, window, want);
    }

    ပြန်ပေး true;
}

bool SDL_SetWindowSize(SDL_Window *window, ကိန်းပြည့် w, ကိန်းပြည့် h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ပြန်ပေး SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ပြန်ပေး SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    float new_aspect = w / (float)h;
    အကယ်၍ (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (ကိန်းပြည့်)SDL_roundf(h * window->max_aspect);
    } မဟုတ်ပါက အကယ်၍ (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (ကိန်းပြည့်)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    အကယ်၍ (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    အကယ်၍ (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    အကယ်၍ (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    အကယ်၍ (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    အကယ်၍ (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_Unsupported();
    }
    ပြန်ပေး true;
}

bool SDL_GetWindowSize(SDL_Window *window, ကိန်းပြည့် *w, ကိန်းပြည့် *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    အကယ်၍ (w) {
        *w = window->w;
    }
    အကယ်၍ (h) {
        *h = window->h;
    }
    ပြန်ပေး true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, float min_aspect, float max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    အကယ်၍ (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    ကိန်းပြည့် w = window->last_size_pending ? window->pending.w : window->floating.w;
    ကိန်းပြည့် h = window->last_size_pending ? window->pending.h : window->floating.h;
    ပြန်ပေး SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, float *min_aspect, float *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    အကယ်၍ (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ပြန်ပေး true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, ကိန်းပြည့် *top, ကိန်းပြည့် *left, ကိန်းပြည့် *bottom, ကိန်းပြည့် *right)
{
    ကိန်းပြည့် dummy = 0;

    အကယ်၍ (!top) {
        top = &dummy;
    }
    အကယ်၍ (!left) {
        left = &dummy;
    }
    အကယ်၍ (!right) {
        right = &dummy;
    }
    အကယ်၍ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *top = *left = *bottom = *right = 0;

    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!_this->GetWindowBordersSize) {
        ပြန်ပေး SDL_Unsupported();
    }

    ပြန်ပေး _this->GetWindowBordersSize(_this, window, top, left, bottom, right);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, ကိန်းပြည့် *w, ကိန်းပြည့် *h)
{
    ကိန်းပြည့် filter;

    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!w) {
        w = &filter;
    }

    အကယ်၍ (!h) {
        h = &filter;
    }

    အကယ်၍ (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } မဟုတ်ပါက {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        const SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        အကယ်၍ ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } မဟုတ်ပါက {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        အကယ်၍ (mode) {
            *w = (ကိန်းပြည့်)SDL_ceilf(*w * mode->pixel_density);
            *h = (ကိန်းပြည့်)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ပြန်ပေး true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, ကိန်းပြည့် min_w, ကိန်းပြည့် min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ပြန်ပေး SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ပြန်ပေး SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ပြန်ပေး SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    အကယ်၍ (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    ကိန်းပြည့် w = window->last_size_pending ? window->pending.w : window->floating.w;
    ကိန်းပြည့် h = window->last_size_pending ? window->pending.h : window->floating.h;
    ပြန်ပေး SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, ကိန်းပြည့် *min_w, ကိန်းပြည့် *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    အကယ်၍ (min_w) {
        *min_w = window->min_w;
    }
    အကယ်၍ (min_h) {
        *min_h = window->min_h;
    }
    ပြန်ပေး true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, ကိန်းပြည့် max_w, ကိန်းပြည့် max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ပြန်ပေး SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ပြန်ပေး SDL_InvalidParamError("max_h");
    }

    အကယ်၍ ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ပြန်ပေး SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    အကယ်၍ (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    ကိန်းပြည့် w = window->last_size_pending ? window->pending.w : window->floating.w;
    ကိန်းပြည့် h = window->last_size_pending ? window->pending.h : window->floating.h;
    ပြန်ပေး SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, ကိန်းပြည့် *max_w, ကိန်းပြည့် *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    အကယ်၍ (max_w) {
        *max_w = window->max_w;
    }
    အကယ်၍ (max_h) {
        *max_h = window->max_h;
    }
    ပြန်ပေး true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ပြန်ပေး true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    အကယ်၍ (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ပြန်ပေး true;
    }

    အကယ်၍ (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } မဟုတ်ပါက {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    အတွက် (child = window->first_child; child; child = child->next_sibling) {
        အကယ်၍ (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            bha_nga;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ပြန်ပေး true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ပြန်ပေး true;
    }

    // Hide all child windows
    အတွက် (child = window->first_child; child; child = child->next_sibling) {
        အကယ်၍ (child->flags & SDL_WINDOW_HIDDEN) {
            bha_nga;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    const SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    အကယ်၍ (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } မဟုတ်ပါက {
        SDL_SetMouseFocus(NULL);
        SDL_SetKeyboardFocus(NULL);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ပြန်ပေး true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        ပြန်ပေး true;
    }
    အကယ်၍ (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ပြန်ပေး true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (!_this->MaximizeWindow) {
        ပြန်ပေး SDL_Unsupported();
    }

    အကယ်၍ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ပြန်ပေး SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ပြန်ပေး true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ပြန်ပေး true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (!_this->MinimizeWindow) {
        ပြန်ပေး SDL_Unsupported();
    }

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ပြန်ပေး true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ပြန်ပေး true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (!_this->RestoreWindow) {
        ပြန်ပေး SDL_Unsupported();
    }

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ပြန်ပေး true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ပြန်ပေး true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        အကယ်၍ (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } မဟုတ်ပါက {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ပြန်ပေး true;
    }

    အကယ်၍ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    အကယ်၍ (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    အကယ်၍ (result) {
        SDL_SyncIfRequired(window);
    }

    ပြန်ပေး result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (_this->SyncWindow) {
        ပြန်ပေး _this->SyncWindow(_this, window);
    } မဟုတ်ပါက {
        ပြန်ပေး true;
    }
}

static bool ShouldAttemptTextureFramebuffer(void)
{
    const var_na *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    အကယ်၍ (!_this->CreateWindowFramebuffer) {
        ပြန်ပေး true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    အကယ်၍ (hint && *hint) {
        အကယ်၍ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } မဟုတ်ပါက {
            attempt_texture_framebuffer = true;
        }
    } မဟုတ်ပါက {
        အကယ်၍ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } မဟုတ်ပါက {
            attempt_texture_framebuffer = false;
        }
    }
    ပြန်ပေး attempt_texture_framebuffer;
}

static SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    void *pixels = NULL;
    ကိန်းပြည့် pitch = 0;
    bool created_framebuffer = false;
    ကိန်းပြည့် w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    အကယ်၍ (!_this->checked_texture_framebuffer) {
        အကယ်၍ (ShouldAttemptTextureFramebuffer()) {
            အကယ်၍ (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } မဟုတ်ပါက {
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

    အကယ်၍ (!created_framebuffer) {
        အကယ်၍ (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            ပြန်ပေး NULL;
        }

        အကယ်၍ (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ပြန်ပေး NULL;
        }
    }

    အကယ်၍ (window->surface) {
        // We may have gone recursive and already created the surface
        ပြန်ပေး window->surface;
    }

    ပြန်ပေး SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ပြန်ပေး window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    အကယ်၍ (!window->surface_valid) {
        အကယ်၍ (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = NULL;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        အကယ်၍ (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ပြန်ပေး window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, ကိန်းပြည့် vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!_this->SetWindowFramebufferVSync) {
        ပြန်ပေး SDL_Unsupported();
    }
    ပြန်ပေး _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, ကိန်းပြည့် *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!_this->GetWindowFramebufferVSync) {
        ပြန်ပေး SDL_Unsupported();
    }
    ပြန်ပေး _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    ပြန်ပေး SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, const SDL_Rect *rects,
                                 ကိန်းပြည့် numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!window->surface_valid) {
        ပြန်ပေး SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ပြန်ပေး _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = NULL;
        window->surface_valid = false;
    }

    အကယ်၍ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        အကယ်၍ (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ပြန်ပေး true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, float opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!_this->SetWindowOpacity) {
        ပြန်ပေး SDL_Unsupported();
    }

    အကယ်၍ (opacity < 0.0f) {
        opacity = 0.0f;
    } မဟုတ်ပါက အကယ်၍ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    အကယ်၍ (result) {
        window->opacity = opacity;
    }

    ပြန်ပေး result;
}

float SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ပြန်ပေး window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    အကယ်၍ (window == parent) {
        ပြန်ပေး SDL_SetError("Cannot set the parent of a window to itself.");
    }

    အကယ်၍ (!_this->SetWindowParent) {
        ပြန်ပေး SDL_Unsupported();
    }

    အကယ်၍ (window->flags & SDL_WINDOW_MODAL) {
        ပြန်ပေး SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    အကယ်၍ (window->parent == parent) {
        ပြန်ပေး true;
    }

    const bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : NULL);

    ပြန်ပေး ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (!_this->SetWindowModal) {
        ပြန်ပေး SDL_Unsupported();
    }

    အကယ်၍ (modal) {
        အကယ်၍ (!window->parent) {
            ပြန်ပေး SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } မဟုတ်ပါက အကယ်၍ (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } မဟုတ်ပါက {
        ပြန်ပေး true; // Already not modal, so nothing to do.
    }

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        ပြန်ပေး true;
    }

    ပြန်ပေး _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_INPUT_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    နေစဉ် (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        အကယ်၍ (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_INPUT_FOCUS);
        }
    }

    *new_focus = focus;
    ပြန်ပေး set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    အတွက် (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    အတွက် (w = current_focus; w != toplevel_parent; w = w->parent) {
        အကယ်၍ (w == window) {
            found_higher_focus = true;
            bha_nga;
        }
    }

    ပြန်ပေး !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (focusable != false); // normalize the flag.
    const bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    အကယ်၍ ((want != have) && (_this->SetWindowFocusable)) {
        အကယ်၍ (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } မဟုတ်ပါက {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        အကယ်၍ (!_this->SetWindowFocusable(_this, window, want)) {
            ပြန်ပေး false;
        }
    }

    ပြန်ပေး true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    const bool want = (fill != false); // normalize the flag.
    const bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    အကယ်၍ ((want != have) && (_this->SetWindowFillDocument)) {
        အကယ်၍ (!_this->SetWindowFillDocument(_this, window, want)) {
            ပြန်ပေး false;
        } မဟုတ်ပါက အကယ်၍ (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } မဟုတ်ပါက {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ပြန်ပေး true;
}

void SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    အကယ်၍ (window->flags & SDL_WINDOW_INPUT_FOCUS) {
        အကယ်၍ (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } မဟုတ်ပါက {
            mouse_grabbed = false;
        }

        အကယ်၍ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } မဟုတ်ပါက {
            keyboard_grabbed = false;
        }
    } မဟုတ်ပါက {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    အကယ်၍ (mouse_grabbed || keyboard_grabbed) {
        အကယ်၍ (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            အကယ်၍ (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            အကယ်၍ (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } မဟုတ်ပါက အကယ်၍ (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    အကယ်၍ (_this->SetWindowMouseGrab) {
        အကယ်၍ (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    အကယ်၍ (_this->SetWindowKeyboardGrab) {
        အကယ်၍ (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    အကယ်၍ (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = NULL;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        အကယ်၍ (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } မဟုတ်ပါက {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        ပြန်ပေး true;
    }

    အကယ်၍ (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ပြန်ပေး true;
    }
    အကယ်၍ (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } မဟုတ်ပါက {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    အကယ်၍ (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ပြန်ပေး false;
    }
    ပြန်ပေး true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (window->flags & SDL_WINDOW_HIDDEN) {
        အကယ်၍ (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } မဟုတ်ပါက {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        ပြန်ပေး true;
    }

    အကယ်၍ (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ပြန်ပေး true;
    }
    အကယ်၍ (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } မဟုတ်ပါက {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    အကယ်၍ (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ပြန်ပေး false;
    }
    ပြန်ပေး true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ပြန်ပေး window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ပြန်ပေး window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(void)
{
    အကယ်၍ (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ပြန်ပေး _this->grabbed_window;
    } မဟုတ်ပါက {
        ပြန်ပေး NULL;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, const SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!_this->SetWindowMouseRect) {
        ပြန်ပေး SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    အကယ်၍ (!rect) {
        rect = &zero;
    }

    အကယ်၍ (SDL_memcmp(&window->mouse_rect, rect, parimaa_na(*rect)) == 0) {
        ပြန်ပေး true;
    }
    SDL_memcpy(&window->mouse_rect, rect, parimaa_na(*rect));

    ပြန်ပေး _this->SetWindowMouseRect(_this, window);
}

const SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    အကယ်၍ (SDL_RectEmpty(&window->mouse_rect)) {
        ပြန်ပေး NULL;
    } မဟုတ်ပါက {
        ပြန်ပေး &window->mouse_rect;
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

    အကယ်၍ (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        ပြန်ပေး true;
    }

    အကယ်၍ (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } မဟုတ်ပါက {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    အကယ်၍ (!SDL_UpdateRelativeMouseMode()) {
        အကယ်၍ (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } မဟုတ်ပါက {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        ပြန်ပေး false;
    }
    ပြန်ပေး true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ပြန်ပေး true;
    } မဟုတ်ပါက {
        ပြန်ပေး false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (_this->FlashWindow) {
        ပြန်ပေး _this->FlashWindow(_this, window, operation);
    }

    ပြန်ပေး SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ပြန်ပေး SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    အကယ်၍ (_this->ApplyWindowProgress) {
        အကယ်၍ (!_this->ApplyWindowProgress(_this, window)) {
            ပြန်ပေး false;
        }
    }

    ပြန်ပေး true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ပြန်ပေး window->progress_state;
}

bool SDL_SetWindowProgressValue(SDL_Window *window, float value)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    value = SDL_clamp(value, 0.0f, 1.f);

    window->progress_value = value;

    အကယ်၍ (_this->ApplyWindowProgress) {
        အကယ်၍ (!_this->ApplyWindowProgress(_this, window)) {
            ပြန်ပေး false;
        }
    }

    ပြန်ပေး true;
}

float SDL_GetWindowProgressValue(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ပြန်ပေး window->progress_value;
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
    အကယ်၍ (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        const bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        အကယ်၍ (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_high_density_modes = false;

            အကယ်၍ (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_high_density_modes = true;
            }
            const bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_high_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            အကယ်၍ (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } မဟုတ်ပါက {
            SDL_zero(window->current_fullscreen_mode);
        }

        အကယ်၍ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
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

    အကယ်၍ ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, NULL);
        အကယ်၍ (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

void SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    ကိန်းပြည့် pixel_w = 0, pixel_h = 0;

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
    အကယ်၍ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } မဟုတ်ပါက {
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
    အကယ်၍ (SDL_memcmp(&rect, &window->safe_rect, parimaa_na(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

void SDL_SetWindowSafeAreaInsets(SDL_Window *window, ကိန်းပြည့် left, ကိန်းပြည့် right, ကိန်းပြည့် top, ကိန်းပြည့် bottom)
{
    window->safe_inset_left = left;
    window->safe_inset_right = right;
    window->safe_inset_top = top;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    အကယ်၍ (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (rect) {
        အကယ်၍ (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } မဟုတ်ပါက {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    ပြန်ပေး true;
}

void SDL_OnWindowMinimized(SDL_Window *window)
{
    အကယ်၍ (window->flags & SDL_WINDOW_FULLSCREEN) {
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

    အကယ်၍ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

void SDL_OnWindowEnter(SDL_Window *window)
{
    အကယ်၍ (_this->OnWindowEnter) {
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

    အကယ်၍ (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

static bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    const var_na *hint;

    အကယ်၍ (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ပြန်ပေး false;
    }

#အကယ်၍ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    အကယ်၍ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        အကယ်၍ (Cocoa_IsShowingModalDialog(window)) {
            ပြန်ပေး false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } မဟုတ်ပါက အကယ်၍ (Cocoa_IsWindowInFullscreenSpace(window)) {
            ပြန်ပေး false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        extern bool Android_JNI_ShouldMinimizeOnFocusLoss(void);
        အကယ်၍ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ပြန်ပေး false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    အကယ်၍ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        အကယ်၍ (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ပြန်ပေး true;
        } မဟုတ်ပါက {
            ပြန်ပေး false;
        }
    }
    ပြန်ပေး SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

void SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    အကယ်၍ (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(void)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    အကယ်၍ (focus) {
        // Get the toplevel parent window.
        နေစဉ် (focus->parent) {
            focus = focus->parent;
        }
    }

    ပြန်ပေး focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->num_renderers + 1) * parimaa_na(*renderers));
    အကယ်၍ (!renderers) {
        ပြန်ပေး false;
    }

    window->renderers = renderers;
    window->renderers[window->num_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ပြန်ပေး true;
}

void SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    အတွက် (ကိန်းပြည့် i = 0; i < window->num_renderers; ++i) {
        အကယ်၍ (window->renderers[i] == renderer) {
            အကယ်၍ (i < (window->num_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->num_renderers - i - 1) * parimaa_na(window->renderers[i]));
            }
            --window->num_renderers;
            bha_nga;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    အကယ်၍ (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, NULL) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

void SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    နေစဉ် (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    အကယ်၍ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    အကယ်၍ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_input_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    အကယ်၍ (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    အတွက် (ကိန်းပြည့် i = 0; i < _this->num_displays; ++i) {
        အကယ်၍ (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = NULL;
        }
    }

    // Make sure this window no longer has focus
    အကယ်၍ (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(NULL);
    }
    အကယ်၍ ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    အကယ်၍ (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(NULL);
    }

    // Make no context current if this is the current context window
    အကယ်၍ (window->flags & SDL_WINDOW_OPENGL) {
        အကယ်၍ (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, NULL);
        }
    }

    အကယ်၍ (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    အကယ်၍ (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    အကယ်၍ (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    အကယ်၍ (_this->grabbed_window == window) {
        _this->grabbed_window = NULL; // ungrabbing input.
    }

    အကယ်၍ (_this->current_glwin == window) {
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
    အကယ်၍ (window->next) {
        window->next->prev = window->prev;
    }
    အကယ်၍ (window->prev) {
        window->prev->next = window->next;
    } မဟုတ်ပါက {
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
    အကယ်၍ (!_this) {
        ပြန်ပေး true;
    }
    ပြန်ပေး !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(void)
{
    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }
    အကယ်၍ (!_this->suspend_screensaver) {
        ပြန်ပေး true;
    }
    _this->suspend_screensaver = false;
    အကယ်၍ (_this->SuspendScreenSaver) {
        ပြန်ပေး _this->SuspendScreenSaver(_this);
    }

    ပြန်ပေး SDL_Unsupported();
}

bool SDL_DisableScreenSaver(void)
{
    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }
    အကယ်၍ (_this->suspend_screensaver) {
        ပြန်ပေး true;
    }
    _this->suspend_screensaver = true;
    အကယ်၍ (_this->SuspendScreenSaver) {
        ပြန်ပေး _this->SuspendScreenSaver(_this);
    }

    ပြန်ပေး SDL_Unsupported();
}

void SDL_QuitVideo(void)
{
    ကိန်းပြည့် i;

    အကယ်၍ (!_this) {
        ပြန်ပေး;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#အကယ်၍ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    နေစဉ် (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    အကယ်၍ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    အကယ်၍ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    အတွက် (i = _this->num_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->num_displays == 0);
    SDL_free(_this->displays);
    _this->displays = NULL;

    SDL_CancelClipboardData(0);

    အကယ်၍ (_this->primary_selection_text) {
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

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }
    အကယ်၍ (_this->gl_config.driver_loaded) {
        အကယ်၍ (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ပြန်ပေး SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } မဟုတ်ပါက {
        အကယ်၍ (!_this->GL_LoadLibrary) {
            ပြန်ပေး SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    အကယ်၍ (result) {
        ++_this->gl_config.driver_loaded;
    } မဟုတ်ပါက {
        အကယ်၍ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ပြန်ပေး result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(const var_na *proc)
{
    SDL_FunctionPointer func;

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    func = NULL;
    အကယ်၍ (_this->GL_GetProcAddress) {
        အကယ်၍ (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } မဟုတ်ပါက {
            SDL_SetError("No GL driver has been loaded");
        }
    } မဟုတ်ပါက {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ပြန်ပေး func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(const var_na *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    func = NULL;

    အကယ်၍ (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } မဟုတ်ပါက {
        SDL_SetError("No EGL library has been loaded");
    }

    ပြန်ပေး func;
#မဟုတ်ပါက
    SDL_SetError("SDL was not built with EGL support");
    ပြန်ပေး NULL;
#endif
}

void SDL_GL_UnloadLibrary(void)
{
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး;
    }
    အကယ်၍ (_this->gl_config.driver_loaded > 0) {
        အကယ်၍ (--_this->gl_config.driver_loaded > 0) {
            ပြန်ပေး;
        }
        အကယ်၍ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#အကယ်၍ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
typedef GLenum (APIENTRY* PFNGLGETERRORPROC) (void);
typedef void (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
typedef const GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

static SDL_INLINE bool isAtLeastGL3(const var_na *verstr)
{
    ပြန်ပေး verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(const var_na *extension)
{
#အကယ်၍ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    const var_na *extensions;
    const var_na *start;
    const var_na *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    အကယ်၍ (where || *extension == '\0') {
        ပြန်ပေး false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    အကယ်၍ (start && *start == '0') {
        ပြန်ပေး false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    အကယ်၍ (!glGetStringFunc) {
        ပြန်ပေး false;
    }

    အကယ်၍ (isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint num_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        အကယ်၍ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ပြန်ပေး false;
        }

#ifndef GL_NUM_EXTENSIONS
#define GL_NUM_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_NUM_EXTENSIONS, &num_exts);
        အတွက် (i = 0; i < num_exts; i++) {
            const var_na *thisext = (const var_na *)glGetStringiFunc(GL_EXTENSIONS, i);
            အကယ်၍ (SDL_strcmp(thisext, extension) == 0) {
                ပြန်ပေး true;
            }
        }

        ပြန်ပေး false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (const var_na *)glGetStringFunc(GL_EXTENSIONS);
    အကယ်၍ (!extensions) {
        ပြန်ပေး false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    အတွက် (;;) {
        where = SDL_strstr(start, extension);
        အကယ်၍ (!where) {
            bha_nga;
        }

        terminator = where + SDL_strlen(extension);
        အကယ်၍ (where == extensions || *(where - 1) == ' ') {
            အကယ်၍ (*terminator == ' ' || *terminator == '\0') {
                ပြန်ပေး true;
            }
        }

        start = terminator;
    }
    ပြန်ပေး false;
#မဟုတ်ပါက
    ပြန်ပေး false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
void SDL_GL_DeduceMaxSupportedESProfile(ကိန်းပြည့် *major, ကိန်းပြည့် *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#အကယ်၍ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    အကယ်၍ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } မဟုတ်ပါက အကယ်၍ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } မဟုတ်ပါက အကယ်၍ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } မဟုတ်ပါက {
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
    အကယ်၍ (!_this) {
        ပြန်ပေး;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

void SDL_GL_ResetAttributes(void)
{
    အကယ်၍ (!_this) {
        ပြန်ပေး;
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

    အကယ်၍ (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, ကိန်းပြည့် value)
{
#အကယ်၍ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
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
        အကယ်၍ (value & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", value);
            bha_nga;
        }
        _this->gl_config.flags = value;
        bha_nga;
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
        အကယ်၍ (value != 0 &&
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
    ပြန်ပေး result;
#မဟုတ်ပါက
    ပြန်ပေး SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, ကိန်းပြည့် *value)
{
#အကယ်၍ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
        ပြန်ပေး SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *value = 0;

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
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
#မဟုတ်ပါက
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *value = _this->gl_config.double_buffer;
        ပြန်ပေး true;
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
#မဟုတ်ပါက
    pak_sa SDL_GL_ACCUM_RED_SIZE:
    pak_sa SDL_GL_ACCUM_GREEN_SIZE:
    pak_sa SDL_GL_ACCUM_BLUE_SIZE:
    pak_sa SDL_GL_ACCUM_ALPHA_SIZE:
    pak_sa SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *value = 0;
        ပြန်ပေး true;
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
        ကိန်းပြည့် rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        အကယ်၍ (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            ပြန်ပေး false;
        }
        အကယ်၍ (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            ပြန်ပေး false;
        }
        အကယ်၍ (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            ပြန်ပေး false;
        }
        အကယ်၍ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            ပြန်ပေး false;
        }

        *value = rsize + gsize + bsize + asize;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *value = (_this->gl_config.accelerated != 0);
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_RETAINED_BACKING:
    {
        *value = _this->gl_config.retained_backing;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *value = _this->gl_config.major_version;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *value = _this->gl_config.minor_version;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_CONTEXT_FLAGS:
    {
        *value = _this->gl_config.flags;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *value = _this->gl_config.profile_mask;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *value = _this->gl_config.share_with_current_context;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *value = _this->gl_config.framebuffer_srgb_capable;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_CONTEXT_NO_ERROR:
    {
        *value = _this->gl_config.no_error;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_EGL_PLATFORM:
    {
        *value = _this->gl_config.egl_platform;
        ပြန်ပေး true;
    }
    pak_sa SDL_GL_FLOATBUFFERS:
    {
        အကယ်၍ (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            bha_nga;
        } မဟုတ်ပါက {
            ပြန်ပေး 0;
        }
    }
    default:
        ပြန်ပေး SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    အကယ်၍ (!glGetStringFunc) {
        ပြန်ပေး false;
    }

    အကယ်၍ (attachmentattrib && isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        အကယ်၍ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        အကယ်၍ (glGetFramebufferAttachmentParameterivFunc) {
            အကယ်၍ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            အကယ်၍ (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            အကယ်၍ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)value);
            } မဟုတ်ပါက {
                *value = 0;
            }
            အကယ်၍ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } မဟုတ်ပါက {
            ပြန်ပေး false;
        }
    } မဟုတ်ပါက
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        အကယ်၍ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)value);
        } မဟုတ်ပါက {
            ပြန်ပေး false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    အကယ်၍ (!glGetErrorFunc) {
        ပြန်ပေး false;
    }

    error = glGetErrorFunc();
    အကယ်၍ (error != GL_NO_ERROR) {
        အကယ်၍ (error == GL_INVALID_ENUM) {
            ပြန်ပေး SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } မဟုတ်ပါက အကယ်၍ (error == GL_INVALID_VALUE) {
            ပြန်ပေး SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ပြန်ပေး SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    အကယ်၍ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *value = (*value == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ပြန်ပေး true;
#မဟုတ်ပါက
    ပြန်ပေး SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = NULL;
    CHECK_WINDOW_MAGIC(window, NULL);

    အကယ်၍ (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ပြန်ပေး NULL;
    }

#အကယ်၍ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    ကိန်းပြည့် srgb_requested = -1;
    const var_na *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    အကယ်၍ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    အကယ်၍ (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, NULL);
    }

#အကယ်၍ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    အကယ်၍ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        အကယ်၍ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            အကယ်၍ (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } မဟုတ်ပါက {
                supported = isAtLeastGL3((const var_na *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            အကယ်၍ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ပြန်ပေး ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }

    အကယ်၍ (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ပြန်ပေး true;
    }

    အကယ်၍ (!context) {
        window = NULL;
    } မဟုတ်ပါက အကယ်၍ (window) {
        CHECK_WINDOW_MAGIC(window, false);

        အကယ်၍ (!(window->flags & SDL_WINDOW_OPENGL)) {
            ပြန်ပေး SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } မဟုတ်ပါက အကယ်၍ (!_this->gl_allow_no_surface) {
        ပြန်ပေး SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    အကယ်၍ (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, NULL);
        SDL_SetTLS(&_this->current_glctx_tls, context, NULL);
    }
    ပြန်ပေး result;
}

SDL_Window *SDL_GL_GetCurrentWindow(void)
{
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    ပြန်ပေး (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(void)
{
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    ပြန်ပေး (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး EGL_NO_DISPLAY;
    }
    အကယ်၍ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ပြန်ပေး EGL_NO_DISPLAY;
    }
    ပြန်ပေး _this->egl_data->egl_display;
#မဟုတ်ပါက
    SDL_SetError("SDL was not built with EGL support");
    ပြန်ပေး NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(void)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    အကယ်၍ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ပြန်ပေး NULL;
    }
    ပြန်ပေး _this->egl_data->egl_config;
#မဟုတ်ပါက
    SDL_SetError("SDL was not built with EGL support");
    ပြန်ပေး NULL;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    အကယ်၍ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        ပြန်ပေး NULL;
    }
    အကယ်၍ (_this->GL_GetEGLSurface) {
        ပြန်ပေး _this->GL_GetEGLSurface(_this, window);
    }
    ပြန်ပေး NULL;
#မဟုတ်ပါက
    SDL_SetError("SDL was not built with EGL support");
    ပြန်ပေး NULL;
#endif
}

bool SDL_GL_SetSwapInterval(ကိန်းပြည့် interval)
{
    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    } မဟုတ်ပါက အကယ်၍ (SDL_GL_GetCurrentContext() == NULL) {
        ပြန်ပေး SDL_SetError("No OpenGL context has been made current");
    } မဟုတ်ပါက အကယ်၍ (_this->GL_SetSwapInterval) {
        ပြန်ပေး _this->GL_SetSwapInterval(_this, interval);
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(ကိန်းပြည့် *interval)
{
    CHECK_PARAM(!interval) {
       ပြန်ပေး SDL_InvalidParamError("interval");
    }

    *interval = 0;

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_SetError("no video driver");
    } မဟုတ်ပါက အကယ်၍ (SDL_GL_GetCurrentContext() == NULL) {
        ပြန်ပေး SDL_SetError("no current context");
    } မဟုတ်ပါက အကယ်၍ (_this->GL_GetSwapInterval) {
        ပြန်ပေး _this->GL_GetSwapInterval(_this, interval);
    } မဟုတ်ပါက {
        ပြန်ပေး SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!(window->flags & SDL_WINDOW_OPENGL)) {
        ပြန်ပေး SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    အကယ်၍ (SDL_GL_GetCurrentWindow() != window) {
        ပြန်ပေး SDL_SetError("The specified window has not been made current");
    }

    ပြန်ပေး _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ပြန်ပေး SDL_InvalidParamError("context");
    }

    အကယ်၍ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(NULL, NULL);
    }

    ပြန်ပေး _this->GL_DestroyContext(_this, context);
}

#အကယ်၍ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
static void CreateMaskFromColorKeyOrAlpha(SDL_Surface *icon, Uint8 *mask, ကိန်းပြည့် flags)
{
    ကိန်းပြည့် x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    switch (SDL_BYTESPERPIXEL(icon->format)) {
    pak_sa 1:
        {
            Uint8 *pixels;
            အတွက် (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                အတွက် (x = 0; x < icon->w; ++x) {
                    အကယ်၍ (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        bha_nga;

    pak_sa 2:
        {
            Uint16 *pixels;
            အတွက် (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                အတွက် (x = 0; x < icon->w; ++x) {
                    အကယ်၍ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } မဟုတ်ပါက အကယ်၍ ((flags & 2)
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
            အတွက် (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                အတွက် (x = 0; x < icon->w; ++x) {
                    အကယ်၍ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } မဟုတ်ပါက အကယ်၍ ((flags & 2)
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
    အကယ်၍ (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        အကယ်၍ (mask == NULL) {
            ကိန်းပြည့် mask_len = icon->h * (icon->w + 7) / 8;
            ကိန်းပြည့် flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            အကယ်၍ (mask == NULL) {
                ပြန်ပေး;
            }
            SDL_memset(mask, ~0, mask_len);
            အကယ်၍ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            အကယ်၍ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            အကယ်၍ (flags) {
                CreateMaskFromColorKeyOrAlpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } မဟုတ်ပါက {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_TextInputType SDL_GetTextInputType(SDL_PropertiesID props)
{
    ပြန်ပေး (SDL_TextInputType)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_TYPE_NUMBER, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_GetTextInputCapitalization(SDL_PropertiesID props)
{
    အကယ်၍ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER)) {
        ပြန်ပေး (SDL_Capitalization)SDL_GetNumberProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_NUMBER, SDL_CAPITALIZE_NONE);
    }

    switch (SDL_GetTextInputType(props)) {
    pak_sa SDL_TEXTINPUT_TYPE_TEXT:
        ပြန်ပေး SDL_CAPITALIZE_SENTENCES;
    pak_sa SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ပြန်ပေး SDL_CAPITALIZE_WORDS;
    default:
        ပြန်ပေး SDL_CAPITALIZE_NONE;
    }
}

bool SDL_GetTextInputAutocorrect(SDL_PropertiesID props)
{
    ပြန်ပေး SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_GetTextInputMultiline(SDL_PropertiesID props)
{
    အကယ်၍ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ပြန်ပေး SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    အကယ်၍ (SDL_GetHintBoolean(SDL_HINT_RETURN_KEY_HIDES_IME, false)) {
        ပြန်ပေး false;
    } မဟုတ်ပါက {
        ပြန်ပေး true;
    }
}

static bool AutoShowingScreenKeyboard(void)
{
    const var_na *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    အကယ်၍ (!hint) {
        // This hint is currently only used by the X11 video driver
        အကယ်၍ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    အကယ်၍ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ပြန်ပေး true;
    } မဟုတ်ပါက {
        ပြန်ပေး false;
    }
}

bool SDL_StartTextInput(SDL_Window *window)
{
    ပြန်ပေး SDL_StartTextInputWithProperties(window, 0);
}

bool SDL_StartTextInputWithProperties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (window->text_input_props) {
        SDL_DestroyProperties(window->text_input_props);
        window->text_input_props = 0;
    }

    အကယ်၍ (props) {
        window->text_input_props = SDL_CreateProperties();
        အကယ်၍ (!window->text_input_props) {
            ပြန်ပေး false;
        }
        အကယ်၍ (!SDL_CopyProperties(props, window->text_input_props)) {
            ပြန်ပေး false;
        }
    }

    အကယ်၍ (_this->SetTextInputProperties) {
        _this->SetTextInputProperties(_this, window, props);
    }

    အကယ်၍ (!window->text_input_active) {
        // Start the text input system
        အကယ်၍ (_this->StartTextInput) {
            အကယ်၍ (!_this->StartTextInput(_this, window, props)) {
                ပြန်ပေး false;
            }
        }
        window->text_input_active = true;
    }

    // Show the on-screen keyboard, if desired
    အကယ်၍ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        အကယ်၍ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    ပြန်ပေး true;
}

bool SDL_TextInputActive(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ပြန်ပေး window->text_input_active;
}

bool SDL_StopTextInput(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (window->text_input_active) {
        // Stop the text input system
        အကယ်၍ (_this->StopTextInput) {
            _this->StopTextInput(_this, window);
        }
        window->text_input_active = false;
    }

    // Hide the on-screen keyboard, if desired
    အကယ်၍ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        အကယ်၍ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    ပြန်ပေး true;
}

bool SDL_SetTextInputArea(SDL_Window *window, const SDL_Rect *rect, ကိန်းပြည့် cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (rect) {
        SDL_copyp(&window->text_input_rect, rect);
        window->text_input_cursor = cursor;
    } မဟုတ်ပါက {
        SDL_zero(window->text_input_rect);
        window->text_input_cursor = 0;
    }

    အကယ်၍ (_this && _this->UpdateTextInputArea) {
        အကယ်၍ (!_this->UpdateTextInputArea(_this, window)) {
            ပြန်ပေး false;
        }
    }
    ပြန်ပေး true;
}

bool SDL_GetTextInputArea(SDL_Window *window, SDL_Rect *rect, ကိန်းပြည့် *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (rect) {
        SDL_copyp(rect, &window->text_input_rect);
    }
    အကယ်၍ (cursor) {
        *cursor = window->text_input_cursor;
    }
    ပြန်ပေး true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (_this->ClearComposition) {
        ပြန်ပေး _this->ClearComposition(_this, window);
    }
    ပြန်ပေး true;
}

bool SDL_HasScreenKeyboardSupport(void)
{
    အကယ်၍ (_this && _this->HasScreenKeyboardSupport) {
        ပြန်ပေး _this->HasScreenKeyboardSupport(_this);
    }
    ပြန်ပေး false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ပြန်ပေး _this->screen_keyboard_shown;
}

void SDL_SendScreenKeyboardShown(void)
{
    အကယ်၍ (!_this || _this->screen_keyboard_shown) {
        ပြန်ပေး;
    }

    _this->screen_keyboard_shown = true;

    အကယ်၍ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

void SDL_SendScreenKeyboardHidden(void)
{
    အကယ်၍ (!_this || !_this->screen_keyboard_shown) {
        ပြန်ပေး;
    }

    _this->screen_keyboard_shown = false;

    အကယ်၍ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_PushEvent(&event);
    }
}

ကိန်းပြည့် SDL_GetMessageBoxCount(void)
{
    ပြန်ပေး SDL_GetAtomicInt(&SDL_messagebox_count);
}

bool SDL_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, ကိန်းပြည့် *buttonID)
{
    ကိန်းပြည့် dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        ပြန်ပေး SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ပြန်ပေး SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    var_na *titlecpy = NULL;
    var_na *msgcpy = NULL;
    အကယ်၍ (messageboxdata->title) {
        const size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(var_na, slen, &titleisstack);
        အကယ်၍ (!titlecpy) {
            ပြန်ပေး false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    အကယ်၍ (messageboxdata->message) {
        const size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(var_na, slen, &msgisstack);
        အကယ်၍ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ပြန်ပေး false;
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

    အကယ်၍ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, parimaa_na(*messageboxdata));
    mbdata.title = titlecpy;
    အကယ်၍ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    အကယ်၍ (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    အကယ်၍ (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } မဟုတ်ပါက {
        // It's completely fine to call this function before video is initialized
        const var_na *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        အကယ်၍ (driver_name && *driver_name != 0) {
            const var_na *driver_attempt = driver_name;
            နေစဉ် (driver_attempt && (*driver_attempt != 0) && !result) {
                const var_na *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                အတွက် (ကိန်းပြည့် i = 0; bootstrap[i]; ++i) {
                    အကယ်၍ (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        အကယ်၍ (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        bha_nga;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : NULL;
            }
        } မဟုတ်ပါက {
            အတွက် (ကိန်းပြည့် i = 0; bootstrap[i]; ++i) {
                အကယ်၍ (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    bha_nga;
                }
            }
        }
    }

    အကယ်၍ (!result) {
        const var_na *error = SDL_GetError();

        အကယ်၍ (!*error) {
            SDL_SetError("No message system available");
        }
    } မဟုတ်ပါက {
        SDL_ClearError();
    }

    (void)SDL_AtomicDecRef(&SDL_messagebox_count);

    အကယ်၍ (current_window) {
        SDL_RaiseWindow(current_window);
    }

    အကယ်၍ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ပြန်ပေး result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, const var_na *title, const var_na *message, SDL_Window *window)
{
#အကယ်၍ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool hasGpuRight;

    // If the video subsystem has not been initialised, set up graphics temporarily
    hasGpuRight = gspHasGpuRight();
    အကယ်၍ (!hasGpuRight)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    အကယ်၍ (!hasGpuRight)
        gfxExit();

    ပြန်ပေး true;
#မဟုတ်ပါက
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

    ပြန်ပေး SDL_ShowMessageBox(&data, NULL);
#endif
}

bool SDL_ShouldAllowTopmost(void)
{
    ပြန်ပေး SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, ကိန်းပြည့် x, ကိန်းပြည့် y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    အကယ်၍ (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ပြန်ပေး true;
    }

    ပြန်ပေး SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, void *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!_this->SetWindowHitTest) {
        ပြန်ပေး SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    ပြန်ပေး _this->SetWindowHitTest(window, callback != NULL);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ပြန်ပေး SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    အကယ်၍ (!props) {
        ပြန်ပေး false;
    }

    အကယ်၍ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        အကယ်၍ (!surface) {
            ပြန်ပေး false;
        }
    } မဟုတ်ပါက {
        surface = NULL;
    }

    အကယ်၍ (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ပြန်ပေး false;
    }

    အကယ်၍ (_this->UpdateWindowShape) {
        အကယ်၍ (!_this->UpdateWindowShape(_this, window, surface)) {
            ပြန်ပေး false;
        }
    }
    ပြန်ပေး true;
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
    အကယ်၍ (_this) {
        SDL_Window *window;
        အတွက် (window = _this->windows; window; window = window->next) {
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

    အကယ်၍ (_this) {
        SDL_Window *window;
        အတွက် (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(const var_na *path)
{
    bool result;

    အကယ်၍ (!_this) {
        ပြန်ပေး SDL_UninitializedVideo();
    }
    အကယ်၍ (_this->vulkan_config.loader_loaded) {
        အကယ်၍ (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ပြန်ပေး SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } မဟုတ်ပါက {
        အကယ်၍ (!_this->Vulkan_LoadLibrary) {
            ပြန်ပေး SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    အကယ်၍ (result) {
        _this->vulkan_config.loader_loaded++;
    }
    ပြန်ပေး result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(void)
{
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး NULL;
    }
    အကယ်၍ (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ပြန်ပေး NULL;
    }
    ပြန်ပေး (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

void SDL_Vulkan_UnloadLibrary(void)
{
    အကယ်၍ (!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး;
    }
    အကယ်၍ (_this->vulkan_config.loader_loaded > 0) {
        အကယ်၍ (--_this->vulkan_config.loader_loaded > 0) {
            ပြန်ပေး;
        }
        အကယ်၍ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

var_na const * const *SDL_Vulkan_GetInstanceExtensions(Uint32 *count)
{
    Uint32 tmpcount = 0;
    အကယ်၍ (!count) {
        count = &tmpcount;
    }

    အကယ်၍ (!_this->Vulkan_GetInstanceExtensions) {
        *count = 0;
        SDL_Unsupported();
        ပြန်ပေး NULL;
    }

    ပြန်ပေး _this->Vulkan_GetInstanceExtensions(_this, count);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  const sa_nracanaa VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    အကယ်၍ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ပြန်ပေး false;
    }

    CHECK_PARAM(!instance) {
        ပြန်ပေး SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ပြန်ပေး SDL_InvalidParamError("surface");
    }

    အကယ်၍ (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        အကယ်၍ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        အကယ်၍ (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        အကယ်၍ (SDL_Vulkan_LoadLibrary(NULL)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } မဟုတ်ပါက {
            ပြန်ပေး SDL_SetError("failed to load Vulkan library");
        }
    }

    ပြန်ပေး _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

void SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               const sa_nracanaa VkAllocationCallbacks *allocator)
{
    အကယ်၍ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ပြန်ပေး false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ပြန်ပေး false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ပြန်ပေး false;
    }

    အကယ်၍ (_this->Vulkan_GetPresentationSupport) {
        ပြန်ပေး _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ပြန်ပေး true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, NULL);

    အကယ်၍ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ပြန်ပေး NULL;
    }

    အကယ်၍ (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        အကယ်၍ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        အကယ်၍ (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    ပြန်ပေး _this->Metal_CreateView(_this, window);
}

void SDL_Metal_DestroyView(SDL_MetalView view)
{
    အကယ်၍ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

void *SDL_Metal_GetLayer(SDL_MetalView view)
{
    အကယ်၍ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            ပြန်ပေး NULL;
        }
        ပြန်ပေး _this->Metal_GetLayer(_this, view);
    } မဟုတ်ပါက {
        SDL_SetError("Metal is not supported.");
        ပြန်ပေး NULL;
    }
}

#အကယ်၍ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
const var_na *SDL_GetCSSCursorName(SDL_SystemCursor id, const var_na **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    switch (id) {
    pak_sa SDL_SYSTEM_CURSOR_DEFAULT:
        ပြန်ပေး "default";

    pak_sa SDL_SYSTEM_CURSOR_TEXT:
        ပြန်ပေး "text";

    pak_sa SDL_SYSTEM_CURSOR_WAIT:
        ပြန်ပေး "wait";

    pak_sa SDL_SYSTEM_CURSOR_CROSSHAIR:
        ပြန်ပေး "crosshair";

    pak_sa SDL_SYSTEM_CURSOR_PROGRESS:
        ပြန်ပေး "progress";

    pak_sa SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        အကယ်၍ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ပြန်ပေး "nwse-resize";

    pak_sa SDL_SYSTEM_CURSOR_NESW_RESIZE:
        အကယ်၍ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ပြန်ပေး "nesw-resize";

    pak_sa SDL_SYSTEM_CURSOR_EW_RESIZE:
        အကယ်၍ (fallback_name) {
            *fallback_name = "col-resize";
        }
        ပြန်ပေး "ew-resize";

    pak_sa SDL_SYSTEM_CURSOR_NS_RESIZE:
        အကယ်၍ (fallback_name) {
            *fallback_name = "row-resize";
        }
        ပြန်ပေး "ns-resize";

    pak_sa SDL_SYSTEM_CURSOR_MOVE:
        အကယ်၍ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ပြန်ပေး "move";

    pak_sa SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ပြန်ပေး "not-allowed";

    pak_sa SDL_SYSTEM_CURSOR_POINTER:
        ပြန်ပေး "pointer";

    pak_sa SDL_SYSTEM_CURSOR_NW_RESIZE:
        ပြန်ပေး "nw-resize";

    pak_sa SDL_SYSTEM_CURSOR_N_RESIZE:
        ပြန်ပေး "n-resize";

    pak_sa SDL_SYSTEM_CURSOR_NE_RESIZE:
        ပြန်ပေး "ne-resize";

    pak_sa SDL_SYSTEM_CURSOR_E_RESIZE:
        ပြန်ပေး "e-resize";

    pak_sa SDL_SYSTEM_CURSOR_SE_RESIZE:
        ပြန်ပေး "se-resize";

    pak_sa SDL_SYSTEM_CURSOR_S_RESIZE:
        ပြန်ပေး "s-resize";

    pak_sa SDL_SYSTEM_CURSOR_SW_RESIZE:
        ပြန်ပေး "sw-resize";

    pak_sa SDL_SYSTEM_CURSOR_W_RESIZE:
        ပြန်ပေး "w-resize";

    pak_sa SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ပြန်ပေး "context-menu";

    pak_sa SDL_SYSTEM_CURSOR_HELP:
        ပြန်ပေး "help";

    pak_sa SDL_SYSTEM_CURSOR_CELL:
        ပြန်ပေး "cell";

    pak_sa SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ပြန်ပေး "vertical-text";

    pak_sa SDL_SYSTEM_CURSOR_ALIAS:
        ပြန်ပေး "alias";

    pak_sa SDL_SYSTEM_CURSOR_COPY:
        ပြန်ပေး "copy";

    pak_sa SDL_SYSTEM_CURSOR_NO_DROP:
        ပြန်ပေး "no-drop";

    pak_sa SDL_SYSTEM_CURSOR_GRAB:
        ပြန်ပေး "grab";

    pak_sa SDL_SYSTEM_CURSOR_GRABBING:
        ပြန်ပေး "grabbing";

    pak_sa SDL_SYSTEM_CURSOR_COL_RESIZE:
        ပြန်ပေး "col-resize";

    pak_sa SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ပြန်ပေး "row-resize";

    pak_sa SDL_SYSTEM_CURSOR_ALL_SCROLL:
        အကယ်၍ (fallback_name) {
            *fallback_name = "move";
        }
        ပြန်ပေး "all-scroll";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_IN:
        ပြန်ပေး "zoom-in";

    pak_sa SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ပြန်ပေး "zoom-out";

    default:
        ပြန်ပေး "default";
    }
}
#endif

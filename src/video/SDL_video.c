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

#அந்தர்பாவ "SDL_internal.h"

// The high-level video driver subsystem

#அந்தர்பாவ "SDL_sysvideo.h"
#அந்தர்பாவ "SDL_clipboard_c.h"
#அந்தர்பாவ "SDL_egl_c.h"
#அந்தர்பாவ "SDL_surface_c.h"
#அந்தர்பாவ "SDL_pixels_c.h"
#அந்தர்பாவ "SDL_rect_c.h"
#அந்தர்பாவ "SDL_video_c.h"
#அந்தர்பாவ "../events/SDL_events_c.h"
#அந்தர்பாவ "../SDL_hints_c.h"
#அந்தர்பாவ "../SDL_properties_c.h"
#அந்தர்பாவ "../timer/SDL_timer_c.h"
#அந்தர்பாவ "../camera/SDL_camera_c.h"
#அந்தர்பாவ "../render/SDL_sysrender.h"
#அந்தர்பாவ "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#அந்தர்பாவ <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#எனில் defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#அந்தர்பாவ <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#எனில் defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#அந்தர்பாவ <SDL3/SDL_opengles2.h>
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
#அந்தர்பாவ <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#அந்தர்பாவ <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
நிலையான VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_உள்ளீடு_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    வெற்று
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        திரும்பு result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        திரும்பு result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        திரும்பு result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        திரும்பு result;                                                  \
    }

#எனில் defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
வெளி bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
வெளி bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
வெளி bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
வெளி bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
வெளி வெறுமை SDL_UpdateLifecycleObserver(வெறுமை);
#endif

நிலையான வெறுமை SDL_CheckWindowDisplayChanged(SDL_Window *window);
நிலையான வெறுமை SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
நிலையான வெறுமை SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
நிலையான bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    எனில் (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        திரும்பு true;
    }
    திரும்பு false;
}

நிலையான bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    திரும்பு !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

நிலையான bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    திரும்பு !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

நிலையான bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    திரும்பு !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

நிலையான bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    திரும்பு !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

நிலையான bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    திரும்பு !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
நிலையான bool syncHint;

நிலையான வெறுமை SDL_SyncHintWatcher(வெறுமை *userdata, மாறிலி எழுத்து *name, மாறிலி எழுத்து *old_மதிப்பு, மாறிலி எழுத்து *new_மதிப்பு)
{
    syncHint = SDL_GetStringBoolean(new_மதிப்பு, false);
}

நிலையான வெறுமை SDL_SyncIfRequired(SDL_Window *window)
{
    எனில் (syncHint) {
        SDL_SyncWindow(window);
    }
}

நிலையான வெறுமை SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    எனில் (window->parent) {
        எனில் (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        எனில் (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } இல்லையெனில் {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = வெற்று;
    }

    எனில் (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        எனில் (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

வகைவரை கட்டமைப்பு
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    வெறுமை *pixels;
    முழு pitch;
    முழு bytes_per_pixel;
} SDL_WindowTextureData;

நிலையான Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#எனில் (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    எனில் (_this->GL_CreateContext) {
        திரும்பு SDL_WINDOW_OPENGL;
    }
#endif
#எனில் defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    எனில் (_this->Metal_CreateView) {
        திரும்பு SDL_WINDOW_METAL;
    }
#endif
#எனில் defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    எனில் (SDL_strcmp(_this->name, "openvr") == 0) {
        திரும்பு SDL_WINDOW_OPENGL;
    }
#endif
    திரும்பு 0;
}

நிலையான bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, வெறுமை **pixels, முழு *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, வெற்று);
    மாறிலி bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    முழு i;
    முழு w, h;
    மாறிலி SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    எனில் (!data) {
        SDL_Renderer *renderer = வெற்று;
        மாறிலி எழுத்து *render_driver = வெற்று;

        // See if there's a render driver being requested
        மாறிலி எழுத்து *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        எனில் (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        எனில் (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        எனில் (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = வெற்று;
        }

        எழுத்து *render_driver_copy = வெற்று;
        எனில் (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            எனில் (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                எழுத்து *prev = render_driver_copy;
                எழுத்து *ptr = prev;
                போது ((ptr = SDL_strchr(ptr, ',')) != வெற்று) {
                    *ptr = '\0';
                    மாறிலி bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    எனில் (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } இல்லையெனில் {
                        ptr++;
                        prev = ptr;
                    }
                }

                எனில் (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        எனில் (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            எனில் (!renderer) {
                // The error for this specific renderer has already been set
                திரும்பு false;
            }
        } இல்லையெனில் {
            SDL_assert(render_driver_copy == வெற்று);
            மாறிலி முழு total = SDL_Get_இலக்கம்_Render_Drivers();
            க்கு (i = 0; i < total; ++i) {
                மாறிலி எழுத்து *name = SDL_GetRenderDriver(i);
                எனில் (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    எனில் (renderer) {
                        நிறுத்து; // this will work.
                    }
                }
            }
            எனில் (!renderer) {
                திரும்பு SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != வெற்று); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, அளவு(*data));
        எனில் (!data) {
            SDL_DestroyRenderer(renderer);
            திரும்பு false;
        }
        எனில் (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            திரும்பு false;
        }

        data->renderer = renderer;
    }

    texture_formats = (மாறிலி SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, வெற்று);
    எனில் (!texture_formats) {
        திரும்பு false;
    }

    // Free any old texture and pixel data
    எனில் (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = வெற்று;
    }
    SDL_free(data->pixels);
    data->pixels = வெற்று;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    க்கு (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        எனில் (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            நிறுத்து;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    எனில் (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        திரும்பு false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        மாறிலி size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        எனில் (!data->pixels) {
            திரும்பு false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, வெற்று);

    திரும்பு true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, முழு vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, வெற்று);
    எனில் (!data) {
        திரும்பு false;
    }
    எனில் (!data->renderer) {
        திரும்பு false;
    }
    திரும்பு SDL_SetRenderVSync(data->renderer, vsync);
}

நிலையான bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, முழு *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, வெற்று);
    எனில் (!data) {
        திரும்பு false;
    }
    எனில் (!data->renderer) {
        திரும்பு false;
    }
    திரும்பு SDL_GetRenderVSync(data->renderer, vsync);
}

நிலையான bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rects, முழு numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    வெறுமை *src;
    முழு w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, வெற்று);
    எனில் (!data || !data->texture) {
        திரும்பு SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    எனில் (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (வெறுமை *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        எனில் (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            திரும்பு false;
        }

        எனில் (!SDL_RenderTexture(data->renderer, data->texture, வெற்று, வெற்று)) {
            திரும்பு false;
        }

        SDL_RenderPresent(data->renderer);
    }
    திரும்பு true;
}

நிலையான வெறுமை SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    எனில் (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, வெற்று);

        எனில் (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        எனில் (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

நிலையான SDL_VideoDevice *_this = வெற்று;
நிலையான SDL_AtomicInt SDL_messagebox_மொத்தம்;

நிலையான முழு SDLCALL cmpmodes(மாறிலி வெறுமை *A, மாறிலி வெறுமை *B)
{
    மாறிலி SDL_DisplayMode *a = (மாறிலி SDL_DisplayMode *)A;
    மாறிலி SDL_DisplayMode *b = (மாறிலி SDL_DisplayMode *)B;
    முழு a_refresh_rate = (முழு)(a->refresh_rate * 100);
    முழு b_refresh_rate = (முழு)(b->refresh_rate * 100);
    முழு a_pixel_density = (முழு)(a->pixel_density * 100);
    முழு b_pixel_density = (முழு)(b->pixel_density * 100);

    எனில் (a->w != b->w) {
        திரும்பு b->w - a->w;
    } இல்லையெனில் எனில் (a->h != b->h) {
        திரும்பு b->h - a->h;
    } இல்லையெனில் எனில் (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        திரும்பு SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } இல்லையெனில் எனில் (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        திரும்பு SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } இல்லையெனில் எனில் (a_refresh_rate != b_refresh_rate) {
        திரும்பு b_refresh_rate - a_refresh_rate;
    } இல்லையெனில் எனில் (a_pixel_density != b_pixel_density) {
        திரும்பு a_pixel_density - b_pixel_density;
    }
    திரும்பு 0;
}

bool SDL_UninitializedVideo(வெறுமை)
{
    திரும்பு SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
நிலையான மாறிலி VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

முழு SDL_Get_இலக்கம்_Video_Drivers(வெறுமை)
{
    நிலையான முழு இலக்கம்_drivers = -1;

    எனில் (இலக்கம்_drivers >= 0) {
        திரும்பு இலக்கம்_drivers;
    }

    இலக்கம்_drivers = 0;

    // Build a list of unique video drivers.
    க்கு (முழு i = 0; bootstrap[i] != வெற்று; ++i) {
        bool duplicate = false;
        க்கு (முழு j = 0; j < i; ++j) {
            எனில் (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                நிறுத்து;
            }
        }

        எனில் (!duplicate) {
            deduped_bootstrap[இலக்கம்_drivers++] = bootstrap[i];
        }
    }

    திரும்பு இலக்கம்_drivers;
}

மாறிலி எழுத்து *SDL_GetVideoDriver(முழு index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_இலக்கம்_Video_Drivers()) {
        SDL_InvalidParamError("index");
        திரும்பு வெற்று;
    }
    திரும்பு deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(மாறிலி எழுத்து *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    முழு i = 0;

    // Check to make sure we don't overwrite '_this'
    எனில் (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    எனில் (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        செல் pre_driver_error;
    }
    init_events = true;
    எனில் (!SDL_InitKeyboard()) {
        செல் pre_driver_error;
    }
    init_keyboard = true;
    எனில் (!SDL_PreInitMouse()) {
        செல் pre_driver_error;
    }
    init_mouse = true;
    எனில் (!SDL_InitTouch()) {
        செல் pre_driver_error;
    }
    init_touch = true;
    எனில் (!SDL_InitPen()) {
        செல் pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = வெற்று;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    எனில் (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    எனில் (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    எனில் (driver_name && *driver_name != 0) {
        மாறிலி எழுத்து *driver_attempt = driver_name;
        போது (driver_attempt && *driver_attempt != 0 && !video) {
            மாறிலி எழுத்து *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            க்கு (i = 0; bootstrap[i]; ++i) {
                எனில் (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    எனில் (video) {
                        நிறுத்து;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : வெற்று;
        }
    } இல்லையெனில் {
        க்கு (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            எனில் (video) {
                நிறுத்து;
            }
        }
    }
    எனில் (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } இல்லையெனில் {
        எனில் (driver_name) {
            SDL_SetError("%s not available", driver_name);
            செல் pre_driver_error;
        }
        SDL_SetError("No available video device");
        செல் pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = வெற்று;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    எனில் (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        திரும்பு false;
    }

    // Make sure some displays were added
    எனில் (_this->இலக்கம்_displays == 0) {
        SDL_QuitVideo();
        திரும்பு SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, வெற்று);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    எனில் (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    திரும்பு true;

pre_driver_error:
    SDL_assert(_this == வெற்று);
    எனில் (init_pen) {
        SDL_QuitPen();
    }
    எனில் (init_touch) {
        SDL_QuitTouch();
    }
    எனில் (init_mouse) {
        SDL_QuitMouse();
    }
    எனில் (init_keyboard) {
        SDL_QuitKeyboard();
    }
    எனில் (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    திரும்பு false;
}

மாறிலி எழுத்து *SDL_GetCurrentVideoDriver(வெறுமை)
{
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    திரும்பு _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(வெறுமை)
{
    திரும்பு _this;
}

bool SDL_OnVideoThread(வெறுமை)
{
    திரும்பு (_this && SDL_GetCurrentThreadID() == _this->thread);
}

வெறுமை SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    எனில் (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(வெறுமை)
{
    எனில் (_this) {
        திரும்பு _this->system_theme;
    } இல்லையெனில் {
        திரும்பு SDL_SYSTEM_THEME_UNKNOWN;
    }
}

வெறுமை SDL_UpdateDesktopBounds(வெறுமை)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(வெற்று);
    எனில் (displays) {
        க்கு (முழு i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            எனில் (SDL_GetDisplayBounds(displays[i], &bounds)) {
                எனில் (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } இல்லையெனில் {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

நிலையான வெறுமை SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    எனில் (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    எனில் (mode->refresh_rate_numerator > 0) {
        எனில் (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (தசம)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } இல்லையெனில் {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(மாறிலி SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    எனில் (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, அளவு(display.desktop_mode));
    }
    திரும்பு SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(மாறிலி SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    முழு i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(அளவு(*new_display));
    எனில் (!new_display) {
        திரும்பு 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->இலக்கம்_displays + 1) * அளவு(*displays));
    எனில் (!displays) {
        SDL_free(new_display);
        திரும்பு 0;
    }
    _this->displays = displays;
    _this->displays[_this->இலக்கம்_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    எனில் (display->name) {
        new_display->name = SDL_strdup(display->name);
    } இல்லையெனில் {
        எழுத்து name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    எனில் (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    க்கு (i = 0; i < new_display->இலக்கம்_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    எனில் (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    திரும்பு id;
}

வெறுமை SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    க்கு (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

வெறுமை SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

வெறுமை SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    முழு display_index = SDL_GetDisplayIndex(displayID);
    எனில் (display_index < 0) {
        திரும்பு;
    }

    display = _this->displays[display_index];

    எனில் (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = வெற்று;
    SDL_free(display->internal);
    display->internal = வெற்று;
    SDL_free(display);

    எனில் (display_index < (_this->இலக்கம்_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->இலக்கம்_displays - display_index - 1) * அளவு(_this->displays[display_index]));
    }
    --_this->இலக்கம்_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(முழு *மொத்தம்)
{
    முழு i;
    SDL_DisplayID *displays;

    எனில் (!_this) {
        எனில் (மொத்தம்) {
            *மொத்தம் = 0;
        }

        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->இலக்கம்_displays + 1) * அளவு(*displays));
    எனில் (displays) {
        எனில் (மொத்தம்) {
            *மொத்தம் = _this->இலக்கம்_displays;
        }

        க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } இல்லையெனில் {
        எனில் (மொத்தம்) {
            *மொத்தம் = 0;
        }
    }
    திரும்பு displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    முழு display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    எனில் (display_index < 0) {
        திரும்பு வெற்று;
    }
    திரும்பு _this->displays[display_index];
}

நிலையான SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    எனில் (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    திரும்பு displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    திரும்பு SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(வெறுமை)
{
    எனில் (!_this || _this->இலக்கம்_displays == 0) {
        SDL_UninitializedVideo();
        திரும்பு 0;
    }
    திரும்பு _this->displays[0]->id;
}

முழு SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    முழு display_index;

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு -1;
    }

    க்கு (display_index = 0; display_index < _this->இலக்கம்_displays; ++display_index) {
        எனில் (displayID == _this->displays[display_index]->id) {
            திரும்பு display_index;
        }
    }
    SDL_SetError("Invalid display");
    திரும்பு -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, வெற்று);

    திரும்பு display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    திரும்பு SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    எனில் (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    திரும்பு display->props;
}

மாறிலி எழுத்து *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, வெற்று);

    திரும்பு display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        திரும்பு SDL_InvalidParamError("rect");
    }

    எனில் (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        எனில் (_this->GetDisplayBounds(_this, display, rect)) {
            திரும்பு true;
        }
    }

    // Assume that the displays are left to right
    எனில் (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } இல்லையெனில் {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    திரும்பு true;
}

நிலையான முழு ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    மாறிலி எழுத்து *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    திரும்பு hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        திரும்பு SDL_InvalidParamError("rect");
    }

    எனில் (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        திரும்பு true;
    }

    எனில் (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        எனில் (_this->GetDisplayUsableBounds(_this, display, rect)) {
            திரும்பு true;
        }
    }

    // Oh well, just give the entire display bounds.
    திரும்பு SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    எனில் (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        திரும்பு display->natural_orientation;
    } இல்லையெனில் {
        // Default to landscape if the driver hasn't set it
        திரும்பு SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    எனில் (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        திரும்பு display->current_orientation;
    } இல்லையெனில் {
        // Default to landscape if the driver hasn't set it
        திரும்பு SDL_ORIENTATION_LANDSCAPE;
    }
}

வெறுமை SDL_SetDisplayContentScale(SDL_VideoDisplay *display, தசம scale)
{
    எனில் (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        க்கு (window = _this->windows; window; window = window->next) {
            எனில் (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

தசம SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    திரும்பு display->content_scale;
}

வெறுமை SDL_SetWindowHDRProperties(SDL_Window *window, மாறிலி SDL_HDROutputProperties *HDR, bool send_event)
{
    மாறிலி SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    எனில் (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        எனில் (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

வெறுமை SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, மாறிலி SDL_HDROutputProperties *HDR)
{
    மாறிலி SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    மாறிலி bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	எனில் (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    எனில் (changed && !SDL_DriverSendsHDRChanges(_this)) {
        க்கு (SDL_Window *w = display->device->windows; w; w = w->next) {
            எனில் (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

நிலையான வெறுமை SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    எனில் (display->இலக்கம்_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
நிலையான மாறிலி SDL_DisplayMode *SDL_GetFullscreenModeMatch(மாறிலி SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    எனில் (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        திரும்பு வெற்று;
    }

    SDL_memcpy(&fullscreen_mode, mode, அளவு(fullscreen_mode));
    எனில் (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = வெற்று;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    எனில் (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        எனில் (!mode) {
            க்கு (முழு i = 0; i < display->இலக்கம்_fullscreen_modes; ++i) {
                எனில் (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], அளவு(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    நிறுத்து;
                }
            }
        }

        // Search for a mode with the same characteristics
        எனில் (!mode) {
            க்கு (முழு i = 0; i < display->இலக்கம்_fullscreen_modes; ++i) {
                எனில் (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    நிறுத்து;
                }
            }
        }
    }
    திரும்பு mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, மாறிலி SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    முழு i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, அளவு(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->இலக்கம்_fullscreen_modes;
    க்கு (i = 0; i < nmodes; ++i) {
        எனில் (cmpmodes(&new_mode, &modes[i]) == 0) {
            திரும்பு false;
        }
    }

    // Go ahead and add the new mode
    எனில் (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * அளவு(*modes));
        எனில் (!modes) {
            திரும்பு false;
        }

        எனில் (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * அளவு(*modes));
            க்கு (i = 0; i < nmodes; ++i) {
                எனில் (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->இலக்கம்_fullscreen_modes++], &new_mode, அளவு(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->இலக்கம்_fullscreen_modes,
              அளவு(SDL_DisplayMode), cmpmodes);

    திரும்பு true;
}

வெறுமை SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    முழு i;

    க்கு (i = display->இலக்கம்_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = வெற்று;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = வெற்று;
    display->இலக்கம்_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, முழு *மொத்தம்)
{
    முழு i;
    முழு இலக்கம்_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    எனில் (மொத்தம்) {
        *மொத்தம் = 0;
    }

    CHECK_DISPLAY_MAGIC(display, வெற்று);

    SDL_UpdateFullscreenDisplayModes(display);

    இலக்கம்_modes = display->இலக்கம்_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((இலக்கம்_modes + 1) * அளவு(*result) + இலக்கம்_modes * அளவு(**result));
    எனில் (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((இலக்கம்_modes + 1) * அளவு(*result)));
        எனில் (இலக்கம்_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, இலக்கம்_modes * அளவு(*modes));
        }
        க்கு (i = 0; i < இலக்கம்_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = வெற்று;

        எனில் (மொத்தம்) {
            *மொத்தம் = இலக்கம்_modes;
        }
    } இல்லையெனில் {
        எனில் (மொத்தம்) {
            *மொத்தம் = 0;
        }
    }
    திரும்பு result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, முழு w, முழு h, தசம refresh_rate, bool include_உயர்வு_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        திரும்பு SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    மாறிலி SDL_DisplayMode *mode, *closest = வெற்று;
    தசம aspect_ratio;
    முழு i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    எனில் (h > 0) {
        aspect_ratio = (தசம)w / h;
    } இல்லையெனில் {
        aspect_ratio = 1.0f;
    }

    எனில் (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    க்கு (i = 0; i < display->இலக்கம்_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        எனில் (w > mode->w) {
            // Out of sorted modes large enough here
            நிறுத்து;
        }
        எனில் (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            தொடர்;
        }
        எனில் (mode->pixel_density > 1.0f && !include_உயர்வு_density_modes) {
            தொடர்;
        }
        எனில் (closest) {
            தசம current_aspect_ratio = (தசம)mode->w / mode->h;
            தசம closest_aspect_ratio = (தசம)closest->w / closest->h;
            எனில் (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                தொடர்;
            }

            எனில் (mode->w == closest->w && mode->h == closest->h) {
                எனில் (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    தொடர்;
                }
                எனில் (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    தொடர்;
                }
            }
        }

        closest = mode;
    }
    எனில் (!closest) {
        திரும்பு SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    திரும்பு true;
}

நிலையான bool DisplayModeChanged(மாறிலி SDL_DisplayMode *old_mode, மாறிலி SDL_DisplayMode *new_mode)
{
    திரும்பு ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

வெறுமை SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, மாறிலி SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    எனில் (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        திரும்பு;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    எனில் (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        எனில் (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

மாறிலி SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, வெற்று);

    திரும்பு &display->desktop_mode;
}

வெறுமை SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, மாறிலி SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    எனில் (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } இல்லையெனில் {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    எனில் (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

மாறிலி SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, வெற்று);

    திரும்பு display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    எனில் (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        திரும்பு true;
    }

    எனில் (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    எனில் (mode == display->current_mode) {
        திரும்பு true;
    }
#endif

    // Actually change the display mode
    எனில் (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        எனில் (!result) {
            திரும்பு false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    திரும்பு true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
நிலையான வெறுமை SDL_GetClosestPointOnRect(மாறிலி SDL_Rect *rect, SDL_Point *point)
{
    மாறிலி முழு வலது = rect->x + rect->w - 1;
    மாறிலி முழு bottom = rect->y + rect->h - 1;

    எனில் (point->x < rect->x) {
        point->x = rect->x;
    } இல்லையெனில் எனில் (point->x > வலது) {
        point->x = வலது;
    }

    எனில் (point->y < rect->y) {
        point->y = rect->y;
    } இல்லையெனில் எனில் (point->y > bottom) {
        point->y = bottom;
    }
}

நிலையான SDL_DisplayID GetDisplayForRect(முழு x, முழு y, முழு w, முழு h)
{
    முழு i, dist;
    SDL_DisplayID closest = 0;
    முழு closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    எனில் (_this) {
        க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            எனில் (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, வெற்று)) {
                திரும்பு display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            எனில் (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    எனில் (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    திரும்பு closest;
}

வெறுமை SDL_RelativeToGlobalForWindow(SDL_Window *window, முழு rel_x, முழு rel_y, முழு *abs_x, முழு *abs_y)
{
    SDL_Window *w;

    எனில் (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        க்கு (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            எனில் (!SDL_WINDOW_IS_POPUP(w)) {
                நிறுத்து;
            }
        }
    }

    எனில் (abs_x) {
        *abs_x = rel_x;
    }
    எனில் (abs_y) {
        *abs_y = rel_y;
    }
}

வெறுமை SDL_GlobalToRelativeForWindow(SDL_Window *window, முழு abs_x, முழு abs_y, முழு *rel_x, முழு *rel_y)
{
    SDL_Window *w;

    எனில் (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        க்கு (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            எனில் (!SDL_WINDOW_IS_POPUP(w)) {
                நிறுத்து;
            }
        }
    }

    எனில் (rel_x) {
        *rel_x = abs_x;
    }
    எனில் (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(மாறிலி SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        திரும்பு 0;
    }

    திரும்பு GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(மாறிலி SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        திரும்பு 0;
    }

    திரும்பு GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

நிலையான SDL_DisplayID GetDisplayAtOrigin(முழு x, முழு y)
{
    க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
        SDL_Rect rect;
        மாறிலி SDL_DisplayID cur_id = _this->displays[i]->id;
        எனில் (SDL_GetDisplayBounds(cur_id, &rect)) {
            எனில் (x == rect.x && y == rect.y) {
                திரும்பு cur_id;
            }
        }
    }

    திரும்பு 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    முழு x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    எனில் (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    எனில் (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } இல்லையெனில் {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    எனில் (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    திரும்பு displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, வெற்று);

    // An explicit fullscreen display overrides all
    எனில் (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    எனில் (!displayID) {
        displayID = window->pending_displayID;
    }
    எனில் (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        மாறிலி முழு x = window->last_position_pending ? window->pending.x : window->x;
        மாறிலி முழு y = window->last_position_pending ? window->pending.y : window->y;
        மாறிலி முழு w = window->last_size_pending ? window->pending.w : window->w;
        மாறிலி முழு h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        எனில் (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    எனில் (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    திரும்பு SDL_GetVideoDisplay(displayID);
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
    எனில் (fs_display) {
        SDL_Set_எண்_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } இல்லையெனில் {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    திரும்பு GetDisplayForWindow(window);
}

நிலையான வெறுமை SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    எனில் (SDL_SendsDisplayChanges(_this)) {
        திரும்பு;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    எனில் (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        எனில் (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            எனில் (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                முழு old_area = old_overlap.w * old_overlap.h;
                முழு new_area = new_overlap.w * new_overlap.h;
                தசம new_overlap_ratio = (new_area / ((தசம)old_area + new_area));
                எனில் (new_overlap_ratio < 0.80) {
                    திரும்பு;
                }
            }
        }
    }

    எனில் (displayID != window->displayID) {
        முழு i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            எனில் (display->fullscreen_window == window) {
                எனில் (display_index != i) {
                    எனில் (display_index < 0) {
                        display_index = i;
                    } இல்லையெனில் {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        எனில் (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = வெற்று;
                    }
                }
                நிறுத்து;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (முழு)displayID, 0);
    }
}

தசம SDL_GetWindowPixelDensity(SDL_Window *window)
{
    முழு window_w, window_h, pixel_w, pixel_h;
    தசம pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    எனில் (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (தசம)pixel_w / window_w;
    }
    திரும்பு pixel_density;
}

தசம SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    திரும்பு window->display_scale;
}

நிலையான வெறுமை SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    தசம display_scale;

    எனில் (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } இல்லையெனில் {
        மாறிலி தசம pixel_density = SDL_GetWindowPixelDensity(window);
        மாறிலி தசம content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    எனில் (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = வெற்று;
    SDL_DisplayMode *mode = வெற்று;
    முழு i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    எனில் (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    எனில் (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        எனில் (!display) {
            // This should never happen, but it did...
            செல் done;
        }
    } இல்லையெனில் {
        க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
            display = _this->displays[i];
            எனில் (display->fullscreen_window == window) {
                நிறுத்து;
            }
        }
        எனில் (!display || i == _this->இலக்கம்_displays) {
            // Already not fullscreen on any display
            display = வெற்று;
        }
    }

    எனில் (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        எனில் (mode) {
            window->fullscreen_exclusive = true;
        } இல்லையெனில் {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#எனில் defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    எனில் (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        எனில் (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            எனில் (display) {
                display->fullscreen_window = வெற்று;
            }
            செல் done;
        }
        எனில் (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            எனில் (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                எனில் (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    செல் error;
                }
            } இல்லையெனில் எனில் (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    எனில் (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, வெற்று);
                        எனில் (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = வெற்று;
                    }
                }
            }

            எனில் (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                செல் done;
            }
        }
    }
#endif

    எனில் (display) {
        // Restore the video mode on other displays if needed
        க்கு (i = 0; i < _this->இலக்கம்_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            எனில் (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, வெற்று);
                other->fullscreen_window = வெற்று;
            }
        }
    }

    எனில் (fullscreen) {
        முழு mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        எனில் (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        எனில் (!SDL_SetDisplayModeForDisplay(display, mode)) {
            செல் error;
        }
        எனில் (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            எனில் (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } இல்லையெனில் {
                resized = true;
            }

            எனில் (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } இல்லையெனில் எனில் (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                செல் error;
            }
        }

        எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            எனில் (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                எனில் (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } இல்லையெனில் {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                எனில் (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                எனில் (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } இல்லையெனில் {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } இல்லையெனில் {
        bool resized = false;

        // Restore the desktop mode
        எனில் (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, வெற்று);
        }
        எனில் (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            எனில் (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                எனில் (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } இல்லையெனில் {
                resized = true;
            }

            எனில் (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } இல்லையெனில் எனில் (ret == SDL_FULLSCREEN_FAILED) {
                செல் error;
            }
        }

        எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            எனில் (display) {
                display->fullscreen_window = வெற்று;
            }

            எனில் (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                எனில் (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } இல்லையெனில் {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    திரும்பு true;

error:
    எனில் (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    திரும்பு false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, மாறிலி SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (mode) {
        எனில் (!SDL_GetFullscreenModeMatch(mode)) {
            திரும்பு SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } இல்லையெனில் {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#எனில் defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    எனில் (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    எனில் (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    திரும்பு true;
}

மாறிலி SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, வெற்று);
    CHECK_WINDOW_NOT_POPUP(window, வெற்று);

    எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
        திரும்பு SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } இல்லையெனில் {
        திரும்பு SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

வெறுமை *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    எனில் (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        திரும்பு வெற்று;
    }
    திரும்பு _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    மாறிலி SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    எனில் (mode) {
        திரும்பு mode->format;
    } இல்லையெனில் {
        திரும்பு SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_உயர்வு_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_உச்சி | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

நிலையான SDL_INLINE bool IsAcceptingDragAndDrop(வெறுமை)
{
    எனில் (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        திரும்பு true;
    }
    திரும்பு false;
}

// prepare a newly-created window
நிலையான SDL_INLINE வெறுமை PrepareDragAndDropSupport(SDL_Window *window)
{
    எனில் (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
வெறுமை SDL_ToggleDragAndDropSupport(வெறுமை)
{
    எனில் (_this && _this->AcceptDragAndDrop) {
        மாறிலி bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        க்கு (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(முழு *மொத்தம்)
{
    எனில் (மொத்தம்) {
        *மொத்தம் = 0;
    }

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }

    SDL_Window *window;
    முழு இலக்கம்_added = 0;
    முழு இலக்கம்_windows = 0;
    க்கு (window = _this->windows; window; window = window->next) {
        ++இலக்கம்_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((இலக்கம்_windows + 1) * அளவு(*windows));
    எனில் (!windows) {
        திரும்பு வெற்று;
    }

    க்கு (window = _this->windows; window; window = window->next) {
        windows[இலக்கம்_added++] = window;
        எனில் (இலக்கம்_added == இலக்கம்_windows) {
            // Race condition? Multi-threading not supported, ignore it
            நிறுத்து;
        }
    }
    windows[இலக்கம்_added] = வெற்று;

    எனில் (மொத்தம்) {
        *மொத்தம் = இலக்கம்_added;
    }
    திரும்பு windows;
}

நிலையான வெறுமை ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    எனில் (!SDL_WINDOW_IS_POPUP(window)) {
        எனில் (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        எனில் (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        எனில் (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        எனில் (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        எனில் (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        எனில் (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

நிலையான வெறுமை SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    எனில் (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } இல்லையெனில் {
        ApplyWindowFlags(window, flags);
        எனில் (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#எனில் defined(SDL_PLATFORM_LINUX)
    எனில் (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_மதிப்பு(window, 0.0f);
    }
#endif
}

நிலையான bool SDL_ContextNotSupported(மாறிலி எழுத்து *name)
{
    திரும்பு SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

நிலையான bool SDL_DllNotSupported(மாறிலி எழுத்து *name)
{
    திரும்பு SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

நிலையான கட்டமைப்பு {
    மாறிலி எழுத்து *property_name;
    SDL_WindowFlags flag;
    bool invert_மதிப்பு;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_உச்சி_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_உச்சி,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_உயர்வு_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_உயர்வு_PIXEL_DENSITY,  false },
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

நிலையான SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_எண்_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_எண், 0);

    க்கு (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        எனில் (SDL_WindowFlagProperties[i].invert_மதிப்பு) {
            எனில் (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } இல்லையெனில் {
            எனில் (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    திரும்பு flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    மாறிலி எழுத்து *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, வெற்று);
    முழு x = (முழு)SDL_Get_எண்_Property(props, SDL_PROP_WINDOW_CREATE_X_எண், SDL_WINDOWPOS_UNDEFINED);
    முழு y = (முழு)SDL_Get_எண்_Property(props, SDL_PROP_WINDOW_CREATE_Y_எண், SDL_WINDOWPOS_UNDEFINED);
    முழு w = (முழு)SDL_Get_எண்_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_எண், 0);
    முழு h = (முழு)SDL_Get_எண்_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_எண், 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, வெற்று);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    எனில் (!_this) {
        // Initialize the video system if needed
        எனில் (!SDL_Init(SDL_INIT_VIDEO)) {
            திரும்பு வெற்று;
        }

        // Make clang-tidy happy
        எனில் (!_this) {
            திரும்பு வெற்று;
        }
    }

    எனில் ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        திரும்பு வெற்று;
    }

    எனில் ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        எனில் (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            திரும்பு வெற்று;
        }

        // Tooltip and popup menu window must specify a parent window
        எனில் (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            திரும்பு வெற்று;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    எனில் (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned முழு)type_flags);
        திரும்பு வெற்று;
    }

    // Make sure the display list is up to date for window placement
    எனில் (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    எனில் (w < 1) {
        w = 1;
    }
    எனில் (h < 1) {
        h = 1;
    }

    எனில் (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        எனில் ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } இல்லையெனில் எனில் ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        எனில் (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        எனில் (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        எனில் (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            எனில் (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        எனில் (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            எனில் (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    எனில் (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned முழு)graphics_flags);
        திரும்பு வெற்று;
    }

    // Some platforms have certain graphics backends enabled by default
    எனில் (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    எனில் (flags & SDL_WINDOW_OPENGL) {
        எனில் (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            திரும்பு வெற்று;
        }
        எனில் (!SDL_GL_LoadLibrary(வெற்று)) {
            திரும்பு வெற்று;
        }
    }

    எனில் (flags & SDL_WINDOW_VULKAN) {
        எனில் (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            திரும்பு வெற்று;
        }
        எனில் (!SDL_Vulkan_LoadLibrary(வெற்று)) {
            திரும்பு வெற்று;
        }
    }

    எனில் (flags & SDL_WINDOW_METAL) {
        எனில் (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            திரும்பு வெற்று;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, அளவு(*window));
    எனில் (!window) {
        திரும்பு வெற்று;
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
    எனில் (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    எனில் (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    எனில் (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    எனில் (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    எனில் (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_தள்ளு_Error();
        SDL_DestroyWindow(window);
        SDL_எடு_Error();
        திரும்பு வெற்று;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#எனில் !defined(SDL_PLATFORM_WINDOWS)
    எனில் (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    எனில் (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    திரும்பு window;
}

SDL_Window *SDL_CreateWindow(மாறிலி எழுத்து *title, முழு w, முழு h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    எனில் (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_எண், w);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_எண், h);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_எண், flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    திரும்பு window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, முழு offset_x, முழு offset_y, முழு w, முழு h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    எனில் (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        திரும்பு வெற்று;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_X_எண், offset_x);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_Y_எண், offset_y);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_எண், w);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_எண், h);
    SDL_Set_எண்_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_எண், flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    திரும்பு window;
}

நிலையான bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    எனில் (!_this->ReconfigureWindow) {
        திரும்பு false;
    }

    மாறிலி SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    எனில் (graphics_flags & (graphics_flags - 1)) {
        திரும்பு SDL_SetError("Conflicting window flags specified");
    }

    எனில் ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        திரும்பு SDL_ContextNotSupported("OpenGL");
    }
    எனில் ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        திரும்பு SDL_ContextNotSupported("Vulkan");
    }
    எனில் ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        திரும்பு SDL_ContextNotSupported("Metal");
    }

    எனில் (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        எனில் (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            திரும்பு false;
        }
    } இல்லையெனில் {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        எனில் (!_this->ReconfigureWindow(_this, window, 0)) {
            திரும்பு false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        எனில் (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        எனில் (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    எனில் (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(வெற்று);
        எனில் (!loaded_opengl) {
            திரும்பு false;
        }
    } இல்லையெனில் எனில் (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(வெற்று);
        எனில் (!loaded_vulkan) {
            திரும்பு false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    எனில் (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        எனில் (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        எனில் (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        திரும்பு false;
    }

    window->flags |= graphics_flags;

    திரும்பு true;
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
    எனில் (graphics_flags & (graphics_flags - 1)) {
        திரும்பு SDL_SetError("Conflicting window flags specified");
    }

    எனில் ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        திரும்பு SDL_ContextNotSupported("OpenGL");
    }
    எனில் ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        திரும்பு SDL_ContextNotSupported("Vulkan");
    }
    எனில் ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        திரும்பு SDL_ContextNotSupported("Metal");
    }

    எனில் (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } இல்லையெனில் {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    எனில் (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    எனில் (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        மாறிலி bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    எனில் ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        எனில் (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } இல்லையெனில் {
            need_gl_unload = true;
        }
    } இல்லையெனில் எனில் (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    எனில் ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        எனில் (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } இல்லையெனில் {
            need_vulkan_unload = true;
        }
    } இல்லையெனில் எனில் (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    எனில் (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    எனில் (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    எனில் (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    எனில் (need_gl_load) {
        எனில் (!SDL_GL_LoadLibrary(வெற்று)) {
            திரும்பு false;
        }
        loaded_opengl = true;
    }

    எனில் (need_vulkan_load) {
        எனில் (!SDL_Vulkan_LoadLibrary(வெற்று)) {
            திரும்பு false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    எனில் (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        எனில் (!_this->CreateSDLWindow(_this, window, 0)) {
            எனில் (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            எனில் (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            திரும்பு false;
        }
    }

    எனில் (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    எனில் (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    எனில் (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    எனில் (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    எனில் (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    எனில் (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    எனில் (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    திரும்பு true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    எனில் (!SDL_ReconfigureWindowInternal(window, flags)) {
        திரும்பு SDL_RecreateWindow(window, flags);
    }

    திரும்பு true;
}

bool SDL_HasWindows(வெறுமை)
{
    திரும்பு _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    திரும்பு window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    எனில் (id) {
        க்கு (window = _this->windows; window; window = window->next) {
            எனில் (window->id == id) {
                திரும்பு window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    திரும்பு வெற்று;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, வெற்று);

    திரும்பு window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    எனில் (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    திரும்பு window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    திரும்பு window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, மாறிலி எழுத்து *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (title == window->title) {
        திரும்பு true;
    }
    எனில் (!title) {
        title = "";
    }
    எனில் (window->title && SDL_strcmp(title, window->title) == 0) {
        திரும்பு true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    எனில் (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    திரும்பு true;
}

மாறிலி எழுத்து *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    திரும்பு window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        திரும்பு SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    எனில் (!window->icon) {
        திரும்பு false;
    }

    எனில் (!_this->SetWindowIcon) {
        திரும்பு SDL_Unsupported();
    }

    திரும்பு _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, முழு x, முழு y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    மாறிலி முழு w = window->last_size_pending ? window->pending.w : window->windowed.w;
    மாறிலி முழு h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    எனில் (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    எனில் (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    எனில் (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        எனில் (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } இல்லையெனில் எனில் (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        எனில் (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        எனில் (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            எனில் (!SDL_GetDisplayBounds(displayID, &bounds)) {
                திரும்பு false;
            }
        }
        எனில் (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        எனில் (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } இல்லையெனில் {
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
    எனில் (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    எனில் (_this->SetWindowPosition) {
        மாறிலி bool result = _this->SetWindowPosition(_this, window);
        எனில் (result) {
            SDL_SyncIfRequired(window);
        }
        திரும்பு result;
    }

    திரும்பு SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, முழு *x, முழு *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#இல்லையெனில்
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    எனில் (use_display_origin) {
        SDL_DisplayID displayID;

        எனில் (x) {
            *x = 0;
        }
        எனில் (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        எனில் (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            எனில் (x) {
                *x = bounds.x;
            }
            எனில் (y) {
                *y = bounds.y;
            }
        }
    } இல்லையெனில் {
        மாறிலி bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        எனில் (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        எனில் (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    திரும்பு true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (!_this->SetWindowBordered) {
        திரும்பு SDL_Unsupported();
    }

    மாறிலி bool want = bordered;
    மாறிலி bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    எனில் (want != have) {
        எனில் (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } இல்லையெனில் {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    திரும்பு true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (!_this->SetWindowResizable) {
        திரும்பு SDL_Unsupported();
    }

    மாறிலி bool want = resizable;
    மாறிலி bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    எனில் (want != have) {
        எனில் (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } இல்லையெனில் {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    திரும்பு true;
}

bool SDL_Set_Window_Always_On_உச்சி(SDL_Window *window, bool on_உச்சி)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (!_this->Set_Window_Always_On_உச்சி) {
        திரும்பு SDL_Unsupported();
    }

    மாறிலி bool want = on_உச்சி;
    மாறிலி bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_உச்சி) != 0);
    எனில் (want != have) {
        எனில் (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_உச்சி;
        } இல்லையெனில் {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_உச்சி;
        }
        _this->Set_Window_Always_On_உச்சி(_this, window, want);
    }

    திரும்பு true;
}

bool SDL_SetWindowSize(SDL_Window *window, முழு w, முழு h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        திரும்பு SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        திரும்பு SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    தசம new_aspect = w / (தசம)h;
    எனில் (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (முழு)SDL_roundf(h * window->max_aspect);
    } இல்லையெனில் எனில் (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (முழு)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    எனில் (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    எனில் (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    எனில் (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    எனில் (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    எனில் (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } இல்லையெனில் {
        திரும்பு SDL_Unsupported();
    }
    திரும்பு true;
}

bool SDL_GetWindowSize(SDL_Window *window, முழு *w, முழு *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    எனில் (w) {
        *w = window->w;
    }
    எனில் (h) {
        *h = window->h;
    }
    திரும்பு true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, தசம min_aspect, தசம max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    எனில் (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    முழு w = window->last_size_pending ? window->pending.w : window->floating.w;
    முழு h = window->last_size_pending ? window->pending.h : window->floating.h;
    திரும்பு SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, தசம *min_aspect, தசம *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    எனில் (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    திரும்பு true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, முழு *உச்சி, முழு *இடது, முழு *bottom, முழு *வலது)
{
    முழு dummy = 0;

    எனில் (!உச்சி) {
        உச்சி = &dummy;
    }
    எனில் (!இடது) {
        இடது = &dummy;
    }
    எனில் (!வலது) {
        வலது = &dummy;
    }
    எனில் (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *உச்சி = *இடது = *bottom = *வலது = 0;

    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!_this->GetWindowBordersSize) {
        திரும்பு SDL_Unsupported();
    }

    திரும்பு _this->GetWindowBordersSize(_this, window, உச்சி, இடது, bottom, வலது);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, முழு *w, முழு *h)
{
    முழு filter;

    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!w) {
        w = &filter;
    }

    எனில் (!h) {
        h = &filter;
    }

    எனில் (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } இல்லையெனில் {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        மாறிலி SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        எனில் ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } இல்லையெனில் {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        எனில் (mode) {
            *w = (முழு)SDL_ceilf(*w * mode->pixel_density);
            *h = (முழு)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    திரும்பு true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, முழு min_w, முழு min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        திரும்பு SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        திரும்பு SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        திரும்பு SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    எனில் (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    முழு w = window->last_size_pending ? window->pending.w : window->floating.w;
    முழு h = window->last_size_pending ? window->pending.h : window->floating.h;
    திரும்பு SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, முழு *min_w, முழு *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    எனில் (min_w) {
        *min_w = window->min_w;
    }
    எனில் (min_h) {
        *min_h = window->min_h;
    }
    திரும்பு true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, முழு max_w, முழு max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        திரும்பு SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        திரும்பு SDL_InvalidParamError("max_h");
    }

    எனில் ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        திரும்பு SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    எனில் (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    முழு w = window->last_size_pending ? window->pending.w : window->floating.w;
    முழு h = window->last_size_pending ? window->pending.h : window->floating.h;
    திரும்பு SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, முழு *max_w, முழு *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    எனில் (max_w) {
        *max_w = window->max_w;
    }
    எனில் (max_h) {
        *max_h = window->max_h;
    }
    திரும்பு true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!(window->flags & SDL_WINDOW_HIDDEN)) {
        திரும்பு true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    எனில் (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        திரும்பு true;
    }

    எனில் (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } இல்லையெனில் {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    க்கு (child = window->first_child; child; child = child->next_sibling) {
        எனில் (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            நிறுத்து;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    திரும்பு true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        திரும்பு true;
    }

    // Hide all child windows
    க்கு (child = window->first_child; child; child = child->next_sibling) {
        எனில் (child->flags & SDL_WINDOW_HIDDEN) {
            நிறுத்து;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    மாறிலி SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    எனில் (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } இல்லையெனில் {
        SDL_SetMouseFocus(வெற்று);
        SDL_SetKeyboardFocus(வெற்று);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    திரும்பு true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        திரும்பு true;
    }
    எனில் (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    திரும்பு true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (!_this->MaximizeWindow) {
        திரும்பு SDL_Unsupported();
    }

    எனில் (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        திரும்பு SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        திரும்பு true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    திரும்பு true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (!_this->MinimizeWindow) {
        திரும்பு SDL_Unsupported();
    }

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        திரும்பு true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    திரும்பு true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (!_this->RestoreWindow) {
        திரும்பு SDL_Unsupported();
    }

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        திரும்பு true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    திரும்பு true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        எனில் (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } இல்லையெனில் {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        திரும்பு true;
    }

    எனில் (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    எனில் (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    எனில் (result) {
        SDL_SyncIfRequired(window);
    }

    திரும்பு result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (_this->SyncWindow) {
        திரும்பு _this->SyncWindow(_this, window);
    } இல்லையெனில் {
        திரும்பு true;
    }
}

நிலையான bool ShouldAttemptTextureFramebuffer(வெறுமை)
{
    மாறிலி எழுத்து *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    எனில் (!_this->CreateWindowFramebuffer) {
        திரும்பு true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    எனில் (hint && *hint) {
        எனில் (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } இல்லையெனில் {
            attempt_texture_framebuffer = true;
        }
    } இல்லையெனில் {
        எனில் (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } இல்லையெனில் {
            attempt_texture_framebuffer = false;
        }
    }
    திரும்பு attempt_texture_framebuffer;
}

நிலையான SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    வெறுமை *pixels = வெற்று;
    முழு pitch = 0;
    bool created_framebuffer = false;
    முழு w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    எனில் (!_this->checked_texture_framebuffer) {
        எனில் (ShouldAttemptTextureFramebuffer()) {
            எனில் (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } இல்லையெனில் {
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

    எனில் (!created_framebuffer) {
        எனில் (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            திரும்பு வெற்று;
        }

        எனில் (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            திரும்பு வெற்று;
        }
    }

    எனில் (window->surface) {
        // We may have gone recursive and already created the surface
        திரும்பு window->surface;
    }

    திரும்பு SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    திரும்பு window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, வெற்று);

    எனில் (!window->surface_valid) {
        எனில் (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = வெற்று;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        எனில் (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    திரும்பு window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, முழு vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!_this->SetWindowFramebufferVSync) {
        திரும்பு SDL_Unsupported();
    }
    திரும்பு _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, முழு *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!_this->GetWindowFramebufferVSync) {
        திரும்பு SDL_Unsupported();
    }
    திரும்பு _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    திரும்பு SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, மாறிலி SDL_Rect *rects,
                                 முழு numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!window->surface_valid) {
        திரும்பு SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    திரும்பு _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = வெற்று;
        window->surface_valid = false;
    }

    எனில் (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        எனில் (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    திரும்பு true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, தசம opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!_this->SetWindowOpacity) {
        திரும்பு SDL_Unsupported();
    }

    எனில் (opacity < 0.0f) {
        opacity = 0.0f;
    } இல்லையெனில் எனில் (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    எனில் (result) {
        window->opacity = opacity;
    }

    திரும்பு result;
}

தசம SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    திரும்பு window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    எனில் (window == parent) {
        திரும்பு SDL_SetError("Cannot set the parent of a window to itself.");
    }

    எனில் (!_this->SetWindowParent) {
        திரும்பு SDL_Unsupported();
    }

    எனில் (window->flags & SDL_WINDOW_MODAL) {
        திரும்பு SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    எனில் (window->parent == parent) {
        திரும்பு true;
    }

    மாறிலி bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : வெற்று);

    திரும்பு ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (!_this->SetWindowModal) {
        திரும்பு SDL_Unsupported();
    }

    எனில் (modal) {
        எனில் (!window->parent) {
            திரும்பு SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } இல்லையெனில் எனில் (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } இல்லையெனில் {
        திரும்பு true; // Already not modal, so nothing to do.
    }

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        திரும்பு true;
    }

    திரும்பு _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_உள்ளீடு_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    போது (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        எனில் (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_உள்ளீடு_FOCUS);
        }
    }

    *new_focus = focus;
    திரும்பு set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    க்கு (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    க்கு (w = current_focus; w != toplevel_parent; w = w->parent) {
        எனில் (w == window) {
            found_higher_focus = true;
            நிறுத்து;
        }
    }

    திரும்பு !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    மாறிலி bool want = (focusable != false); // normalize the flag.
    மாறிலி bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    எனில் ((want != have) && (_this->SetWindowFocusable)) {
        எனில் (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } இல்லையெனில் {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        எனில் (!_this->SetWindowFocusable(_this, window, want)) {
            திரும்பு false;
        }
    }

    திரும்பு true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    மாறிலி bool want = (fill != false); // normalize the flag.
    மாறிலி bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    எனில் ((want != have) && (_this->SetWindowFillDocument)) {
        எனில் (!_this->SetWindowFillDocument(_this, window, want)) {
            திரும்பு false;
        } இல்லையெனில் எனில் (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } இல்லையெனில் {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    திரும்பு true;
}

வெறுமை SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    எனில் (window->flags & SDL_WINDOW_உள்ளீடு_FOCUS) {
        எனில் (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } இல்லையெனில் {
            mouse_grabbed = false;
        }

        எனில் (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } இல்லையெனில் {
            keyboard_grabbed = false;
        }
    } இல்லையெனில் {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    எனில் (mouse_grabbed || keyboard_grabbed) {
        எனில் (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            எனில் (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            எனில் (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } இல்லையெனில் எனில் (_this->grabbed_window == window) {
        _this->grabbed_window = வெற்று; // ungrabbing input.
    }

    எனில் (_this->SetWindowMouseGrab) {
        எனில் (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    எனில் (_this->SetWindowKeyboardGrab) {
        எனில் (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    எனில் (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = வெற்று;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        எனில் (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } இல்லையெனில் {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        திரும்பு true;
    }

    எனில் (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        திரும்பு true;
    }
    எனில் (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } இல்லையெனில் {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    எனில் (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        திரும்பு false;
    }
    திரும்பு true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (window->flags & SDL_WINDOW_HIDDEN) {
        எனில் (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } இல்லையெனில் {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        திரும்பு true;
    }

    எனில் (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        திரும்பு true;
    }
    எனில் (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } இல்லையெனில் {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    எனில் (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        திரும்பு false;
    }
    திரும்பு true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    திரும்பு window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    திரும்பு window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(வெறுமை)
{
    எனில் (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        திரும்பு _this->grabbed_window;
    } இல்லையெனில் {
        திரும்பு வெற்று;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, மாறிலி SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!_this->SetWindowMouseRect) {
        திரும்பு SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    எனில் (!rect) {
        rect = &zero;
    }

    எனில் (SDL_memcmp(&window->mouse_rect, rect, அளவு(*rect)) == 0) {
        திரும்பு true;
    }
    SDL_memcpy(&window->mouse_rect, rect, அளவு(*rect));

    திரும்பு _this->SetWindowMouseRect(_this, window);
}

மாறிலி SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, வெற்று);

    எனில் (SDL_RectEmpty(&window->mouse_rect)) {
        திரும்பு வெற்று;
    } இல்லையெனில் {
        திரும்பு &window->mouse_rect;
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

    எனில் (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        திரும்பு true;
    }

    எனில் (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } இல்லையெனில் {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    எனில் (!SDL_UpdateRelativeMouseMode()) {
        எனில் (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } இல்லையெனில் {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        திரும்பு false;
    }
    திரும்பு true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        திரும்பு true;
    } இல்லையெனில் {
        திரும்பு false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (_this->FlashWindow) {
        திரும்பு _this->FlashWindow(_this, window, operation);
    }

    திரும்பு SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        திரும்பு SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    எனில் (_this->ApplyWindowProgress) {
        எனில் (!_this->ApplyWindowProgress(_this, window)) {
            திரும்பு false;
        }
    }

    திரும்பு true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    திரும்பு window->progress_state;
}

bool SDL_Set_Window_Progress_மதிப்பு(SDL_Window *window, தசம மதிப்பு)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    மதிப்பு = SDL_clamp(மதிப்பு, 0.0f, 1.f);

    window->progress_மதிப்பு = மதிப்பு;

    எனில் (_this->ApplyWindowProgress) {
        எனில் (!_this->ApplyWindowProgress(_this, window)) {
            திரும்பு false;
        }
    }

    திரும்பு true;
}

தசம SDL_Get_Window_Progress_மதிப்பு(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    திரும்பு window->progress_மதிப்பு;
}

வெறுமை SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

வெறுமை SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

வெறுமை SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    எனில் (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        மாறிலி bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        எனில் (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_உயர்வு_density_modes = false;

            எனில் (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_உயர்வு_density_modes = true;
            }
            மாறிலி bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_உயர்வு_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            எனில் (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } இல்லையெனில் {
            SDL_zero(window->current_fullscreen_mode);
        }

        எனில் (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

வெறுமை SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

வெறுமை SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    எனில் ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, வெற்று);
        எனில் (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

வெறுமை SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    முழு pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

வெறுமை SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

வெறுமை SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    எனில் (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } இல்லையெனில் {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

நிலையான வெறுமை SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_இடது;
    rect.y = window->safe_inset_உச்சி;
    rect.w = window->w - (window->safe_inset_வலது + window->safe_inset_இடது);
    rect.h = window->h - (window->safe_inset_உச்சி + window->safe_inset_bottom);
    எனில் (SDL_memcmp(&rect, &window->safe_rect, அளவு(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

வெறுமை SDL_SetWindowSafeAreaInsets(SDL_Window *window, முழு இடது, முழு வலது, முழு உச்சி, முழு bottom)
{
    window->safe_inset_இடது = இடது;
    window->safe_inset_வலது = வலது;
    window->safe_inset_உச்சி = உச்சி;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    எனில் (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    எனில் (rect) {
        எனில் (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } இல்லையெனில் {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    திரும்பு true;
}

வெறுமை SDL_OnWindowMinimized(SDL_Window *window)
{
    எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

வெறுமை SDL_OnWindowMaximized(SDL_Window *window)
{
}

வெறுமை SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    எனில் (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

வெறுமை SDL_OnWindowEnter(SDL_Window *window)
{
    எனில் (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

வெறுமை SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

வெறுமை SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    எனில் (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

நிலையான bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    மாறிலி எழுத்து *hint;

    எனில் (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        திரும்பு false;
    }

#எனில் defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    எனில் (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        எனில் (Cocoa_IsShowingModalDialog(window)) {
            திரும்பு false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } இல்லையெனில் எனில் (Cocoa_IsWindowInFullscreenSpace(window)) {
            திரும்பு false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        வெளி bool Android_JNI_ShouldMinimizeOnFocusLoss(வெறுமை);
        எனில் (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            திரும்பு false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    எனில் (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        எனில் (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            திரும்பு true;
        } இல்லையெனில் {
            திரும்பு false;
        }
    }
    திரும்பு SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

வெறுமை SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    எனில் (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(வெறுமை)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    எனில் (focus) {
        // Get the toplevel parent window.
        போது (focus->parent) {
            focus = focus->parent;
        }
    }

    திரும்பு focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->இலக்கம்_renderers + 1) * அளவு(*renderers));
    எனில் (!renderers) {
        திரும்பு false;
    }

    window->renderers = renderers;
    window->renderers[window->இலக்கம்_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    திரும்பு true;
}

வெறுமை SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    க்கு (முழு i = 0; i < window->இலக்கம்_renderers; ++i) {
        எனில் (window->renderers[i] == renderer) {
            எனில் (i < (window->இலக்கம்_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->இலக்கம்_renderers - i - 1) * அளவு(window->renderers[i]));
            }
            --window->இலக்கம்_renderers;
            நிறுத்து;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    எனில் (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, வெற்று) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

வெறுமை SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    போது (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    எனில் (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    எனில் (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_உள்ளீடு_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    எனில் (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
        எனில் (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = வெற்று;
        }
    }

    // Make sure this window no longer has focus
    எனில் (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(வெற்று);
    }
    எனில் ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    எனில் (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(வெற்று);
    }

    // Make no context current if this is the current context window
    எனில் (window->flags & SDL_WINDOW_OPENGL) {
        எனில் (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, வெற்று);
        }
    }

    எனில் (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    எனில் (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    எனில் (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    எனில் (_this->grabbed_window == window) {
        _this->grabbed_window = வெற்று; // ungrabbing input.
    }

    எனில் (_this->current_glwin == window) {
        _this->current_glwin = வெற்று;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, வெற்று);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, வெற்று);

    // Unlink the window from the global window list
    எனில் (window->next) {
        window->next->prev = window->prev;
    }
    எனில் (window->prev) {
        window->prev->next = window->next;
    } இல்லையெனில் {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(வெறுமை)
{
    எனில் (!_this) {
        திரும்பு true;
    }
    திரும்பு !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(வெறுமை)
{
    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }
    எனில் (!_this->suspend_screensaver) {
        திரும்பு true;
    }
    _this->suspend_screensaver = false;
    எனில் (_this->SuspendScreenSaver) {
        திரும்பு _this->SuspendScreenSaver(_this);
    }

    திரும்பு SDL_Unsupported();
}

bool SDL_DisableScreenSaver(வெறுமை)
{
    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }
    எனில் (_this->suspend_screensaver) {
        திரும்பு true;
    }
    _this->suspend_screensaver = true;
    எனில் (_this->SuspendScreenSaver) {
        திரும்பு _this->SuspendScreenSaver(_this);
    }

    திரும்பு SDL_Unsupported();
}

வெறுமை SDL_QuitVideo(வெறுமை)
{
    முழு i;

    எனில் (!_this) {
        திரும்பு;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#எனில் 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    போது (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    எனில் (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    எனில் (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    க்கு (i = _this->இலக்கம்_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->இலக்கம்_displays == 0);
    SDL_free(_this->displays);
    _this->displays = வெற்று;

    SDL_CancelClipboardData(0);

    எனில் (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = வெற்று;
    }
    _this->விடுவி(_this);
    _this = வெற்று;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(மாறிலி எழுத்து *path)
{
    bool result;

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }
    எனில் (_this->gl_config.driver_loaded) {
        எனில் (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            திரும்பு SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } இல்லையெனில் {
        எனில் (!_this->GL_LoadLibrary) {
            திரும்பு SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    எனில் (result) {
        ++_this->gl_config.driver_loaded;
    } இல்லையெனில் {
        எனில் (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    திரும்பு result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(மாறிலி எழுத்து *proc)
{
    SDL_FunctionPointer func;

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    func = வெற்று;
    எனில் (_this->GL_GetProcAddress) {
        எனில் (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } இல்லையெனில் {
            SDL_SetError("No GL driver has been loaded");
        }
    } இல்லையெனில் {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    திரும்பு func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(மாறிலி எழுத்து *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    func = வெற்று;

    எனில் (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } இல்லையெனில் {
        SDL_SetError("No EGL library has been loaded");
    }

    திரும்பு func;
#இல்லையெனில்
    SDL_SetError("SDL was not built with EGL support");
    திரும்பு வெற்று;
#endif
}

வெறுமை SDL_GL_UnloadLibrary(வெறுமை)
{
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு;
    }
    எனில் (_this->gl_config.driver_loaded > 0) {
        எனில் (--_this->gl_config.driver_loaded > 0) {
            திரும்பு;
        }
        எனில் (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#எனில் defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
வகைவரை GLenum (APIENTRY* PFNGLGETERRORPROC) (வெறுமை);
வகைவரை வெறுமை (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
வகைவரை மாறிலி GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
வகைவரை வெறுமை (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
வகைவரை மாறிலி GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

நிலையான SDL_INLINE bool isAtLeastGL3(மாறிலி எழுத்து *verstr)
{
    திரும்பு verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(மாறிலி எழுத்து *extension)
{
#எனில் defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    மாறிலி எழுத்து *extensions;
    மாறிலி எழுத்து *start;
    மாறிலி எழுத்து *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    எனில் (where || *extension == '\0') {
        திரும்பு false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    எனில் (start && *start == '0') {
        திரும்பு false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    எனில் (!glGetStringFunc) {
        திரும்பு false;
    }

    எனில் (isAtLeastGL3((மாறிலி எழுத்து *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint இலக்கம்_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        எனில் ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            திரும்பு false;
        }

#ifndef GL_இலக்கம்_EXTENSIONS
#define GL_இலக்கம்_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_இலக்கம்_EXTENSIONS, &இலக்கம்_exts);
        க்கு (i = 0; i < இலக்கம்_exts; i++) {
            மாறிலி எழுத்து *thisext = (மாறிலி எழுத்து *)glGetStringiFunc(GL_EXTENSIONS, i);
            எனில் (SDL_strcmp(thisext, extension) == 0) {
                திரும்பு true;
            }
        }

        திரும்பு false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (மாறிலி எழுத்து *)glGetStringFunc(GL_EXTENSIONS);
    எனில் (!extensions) {
        திரும்பு false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    க்கு (;;) {
        where = SDL_strstr(start, extension);
        எனில் (!where) {
            நிறுத்து;
        }

        terminator = where + SDL_strlen(extension);
        எனில் (where == extensions || *(where - 1) == ' ') {
            எனில் (*terminator == ' ' || *terminator == '\0') {
                திரும்பு true;
            }
        }

        start = terminator;
    }
    திரும்பு false;
#இல்லையெனில்
    திரும்பு false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
வெறுமை SDL_GL_DeduceMaxSupportedESProfile(முழு *major, முழு *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#எனில் defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    எனில் (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } இல்லையெனில் எனில் (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } இல்லையெனில் எனில் (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } இல்லையெனில் {
        *major = 2;
        *minor = 0;
    }
#endif
}

வெறுமை SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   வெறுமை *userdata)
{
    எனில் (!_this) {
        திரும்பு;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

வெறுமை SDL_GL_ResetAttributes(வெறுமை)
{
    எனில் (!_this) {
        திரும்பு;
    }

    _this->egl_platformattrib_callback = வெற்று;
    _this->egl_surfaceattrib_callback = வெற்று;
    _this->egl_contextattrib_callback = வெற்று;
    _this->egl_attrib_callback_userdata = வெற்று;

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
#அல்லதெனில் defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#அல்லதெனில் defined(SDL_VIDEO_OPENGL_ES)
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

    எனில் (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, முழு மதிப்பு)
{
#எனில் defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }
    result = true;
    தேர்வு (attr) {
    நிலை SDL_GL_RED_SIZE:
        _this->gl_config.red_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_STEREO:
        _this->gl_config.stereo = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_FLAGS:
        எனில் (மதிப்பு & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", மதிப்பு);
            நிறுத்து;
        }
        _this->gl_config.flags = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_PROFILE_MASK:
        எனில் (மதிப்பு != 0 &&
            மதிப்பு != SDL_GL_CONTEXT_PROFILE_CORE &&
            மதிப்பு != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            மதிப்பு != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", மதிப்பு);
            நிறுத்து;
        }
        _this->gl_config.profile_mask = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = மதிப்பு;
        நிறுத்து;
    நிலை SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = மதிப்பு;
        நிறுத்து;
    இயல்பு:
        result = SDL_SetError("Unknown OpenGL attribute");
        நிறுத்து;
    }
    திரும்பு result;
#இல்லையெனில்
    திரும்பு SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, முழு *மதிப்பு)
{
#எனில் defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_இடது;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!மதிப்பு) {
        திரும்பு SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *மதிப்பு = 0;

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    தேர்வு (attr) {
    நிலை SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        நிறுத்து;
    நிலை SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        நிறுத்து;
    நிலை SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        நிறுத்து;
    நிலை SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        நிறுத்து;
    நிலை SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        நிறுத்து;
#இல்லையெனில்
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *மதிப்பு = _this->gl_config.double_buffer;
        திரும்பு true;
#endif
    நிலை SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        நிறுத்து;
    நிலை SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        நிறுத்து;
#ifdef SDL_VIDEO_OPENGL
    நிலை SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        நிறுத்து;
    நிலை SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        நிறுத்து;
    நிலை SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        நிறுத்து;
    நிலை SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        நிறுத்து;
    நிலை SDL_GL_STEREO:
        attrib = GL_STEREO;
        நிறுத்து;
#இல்லையெனில்
    நிலை SDL_GL_ACCUM_RED_SIZE:
    நிலை SDL_GL_ACCUM_GREEN_SIZE:
    நிலை SDL_GL_ACCUM_BLUE_SIZE:
    நிலை SDL_GL_ACCUM_ALPHA_SIZE:
    நிலை SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *மதிப்பு = 0;
        திரும்பு true;
#endif
    நிலை SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        நிறுத்து;
    நிலை SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        நிறுத்து;
    நிலை SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        நிறுத்து;
    நிலை SDL_GL_BUFFER_SIZE:
    {
        முழு rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        எனில் (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            திரும்பு false;
        }
        எனில் (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            திரும்பு false;
        }
        எனில் (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            திரும்பு false;
        }
        எனில் (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            திரும்பு false;
        }

        *மதிப்பு = rsize + gsize + bsize + asize;
        திரும்பு true;
    }
    நிலை SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *மதிப்பு = (_this->gl_config.accelerated != 0);
        திரும்பு true;
    }
    நிலை SDL_GL_RETAINED_BACKING:
    {
        *மதிப்பு = _this->gl_config.retained_backing;
        திரும்பு true;
    }
    நிலை SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *மதிப்பு = _this->gl_config.major_version;
        திரும்பு true;
    }
    நிலை SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *மதிப்பு = _this->gl_config.minor_version;
        திரும்பு true;
    }
    நிலை SDL_GL_CONTEXT_FLAGS:
    {
        *மதிப்பு = _this->gl_config.flags;
        திரும்பு true;
    }
    நிலை SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *மதிப்பு = _this->gl_config.profile_mask;
        திரும்பு true;
    }
    நிலை SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *மதிப்பு = _this->gl_config.share_with_current_context;
        திரும்பு true;
    }
    நிலை SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *மதிப்பு = _this->gl_config.framebuffer_srgb_capable;
        திரும்பு true;
    }
    நிலை SDL_GL_CONTEXT_NO_ERROR:
    {
        *மதிப்பு = _this->gl_config.no_error;
        திரும்பு true;
    }
    நிலை SDL_GL_EGL_PLATFORM:
    {
        *மதிப்பு = _this->gl_config.egl_platform;
        திரும்பு true;
    }
    நிலை SDL_GL_FLOATBUFFERS:
    {
        எனில் (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            நிறுத்து;
        } இல்லையெனில் {
            திரும்பு 0;
        }
    }
    இயல்பு:
        திரும்பு SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    எனில் (!glGetStringFunc) {
        திரும்பு false;
    }

    எனில் (attachmentattrib && isAtLeastGL3((மாறிலி எழுத்து *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        எனில் (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        எனில் (glGetFramebufferAttachmentParameterivFunc) {
            எனில் (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            எனில் (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            எனில் (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)மதிப்பு);
            } இல்லையெனில் {
                *மதிப்பு = 0;
            }
            எனில் (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } இல்லையெனில் {
            திரும்பு false;
        }
    } இல்லையெனில்
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        எனில் (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)மதிப்பு);
        } இல்லையெனில் {
            திரும்பு false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    எனில் (!glGetErrorFunc) {
        திரும்பு false;
    }

    error = glGetErrorFunc();
    எனில் (error != GL_NO_ERROR) {
        எனில் (error == GL_INVALID_ENUM) {
            திரும்பு SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } இல்லையெனில் எனில் (error == GL_INVALID_மதிப்பு) {
            திரும்பு SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        திரும்பு SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    எனில் (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *மதிப்பு = (*மதிப்பு == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    திரும்பு true;
#இல்லையெனில்
    திரும்பு SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = வெற்று;
    CHECK_WINDOW_MAGIC(window, வெற்று);

    எனில் (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        திரும்பு வெற்று;
    }

#எனில் defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    முழு srgb_requested = -1;
    மாறிலி எழுத்து *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    எனில் (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    எனில் (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, வெற்று);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, வெற்று);
    }

#எனில் defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    எனில் (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        எனில் (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            எனில் (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } இல்லையெனில் {
                supported = isAtLeastGL3((மாறிலி எழுத்து *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            எனில் (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    திரும்பு ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }

    எனில் (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        திரும்பு true;
    }

    எனில் (!context) {
        window = வெற்று;
    } இல்லையெனில் எனில் (window) {
        CHECK_WINDOW_MAGIC(window, false);

        எனில் (!(window->flags & SDL_WINDOW_OPENGL)) {
            திரும்பு SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } இல்லையெனில் எனில் (!_this->gl_allow_no_surface) {
        திரும்பு SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    எனில் (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, வெற்று);
        SDL_SetTLS(&_this->current_glctx_tls, context, வெற்று);
    }
    திரும்பு result;
}

SDL_Window *SDL_GL_GetCurrentWindow(வெறுமை)
{
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    திரும்பு (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(வெறுமை)
{
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    திரும்பு (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(வெறுமை)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு EGL_NO_DISPLAY;
    }
    எனில் (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        திரும்பு EGL_NO_DISPLAY;
    }
    திரும்பு _this->egl_data->egl_display;
#இல்லையெனில்
    SDL_SetError("SDL was not built with EGL support");
    திரும்பு வெற்று;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(வெறுமை)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    எனில் (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        திரும்பு வெற்று;
    }
    திரும்பு _this->egl_data->egl_config;
#இல்லையெனில்
    SDL_SetError("SDL was not built with EGL support");
    திரும்பு வெற்று;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    எனில் (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        திரும்பு வெற்று;
    }
    எனில் (_this->GL_GetEGLSurface) {
        திரும்பு _this->GL_GetEGLSurface(_this, window);
    }
    திரும்பு வெற்று;
#இல்லையெனில்
    SDL_SetError("SDL was not built with EGL support");
    திரும்பு வெற்று;
#endif
}

bool SDL_GL_SetSwapInterval(முழு interval)
{
    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    } இல்லையெனில் எனில் (SDL_GL_GetCurrentContext() == வெற்று) {
        திரும்பு SDL_SetError("No OpenGL context has been made current");
    } இல்லையெனில் எனில் (_this->GL_SetSwapInterval) {
        திரும்பு _this->GL_SetSwapInterval(_this, interval);
    } இல்லையெனில் {
        திரும்பு SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(முழு *interval)
{
    CHECK_PARAM(!interval) {
       திரும்பு SDL_InvalidParamError("interval");
    }

    *interval = 0;

    எனில் (!_this) {
        திரும்பு SDL_SetError("no video driver");
    } இல்லையெனில் எனில் (SDL_GL_GetCurrentContext() == வெற்று) {
        திரும்பு SDL_SetError("no current context");
    } இல்லையெனில் எனில் (_this->GL_GetSwapInterval) {
        திரும்பு _this->GL_GetSwapInterval(_this, interval);
    } இல்லையெனில் {
        திரும்பு SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!(window->flags & SDL_WINDOW_OPENGL)) {
        திரும்பு SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    எனில் (SDL_GL_GetCurrentWindow() != window) {
        திரும்பு SDL_SetError("The specified window has not been made current");
    }

    திரும்பு _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        திரும்பு SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        திரும்பு SDL_InvalidParamError("context");
    }

    எனில் (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(வெற்று, வெற்று);
    }

    திரும்பு _this->GL_DestroyContext(_this, context);
}

#எனில் 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
நிலையான வெறுமை Create_Mask_From_Color_சாவி_Or_Alpha(SDL_Surface *icon, Uint8 *mask, முழு flags)
{
    முழு x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    தேர்வு (SDL_BYTESPERPIXEL(icon->format)) {
    நிலை 1:
        {
            Uint8 *pixels;
            க்கு (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                க்கு (x = 0; x < icon->w; ++x) {
                    எனில் (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        நிறுத்து;

    நிலை 2:
        {
            Uint16 *pixels;
            க்கு (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                க்கு (x = 0; x < icon->w; ++x) {
                    எனில் ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } இல்லையெனில் எனில் ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        நிறுத்து;

    நிலை 4:
        {
            Uint32 *pixels;
            க்கு (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                க்கு (x = 0; x < icon->w; ++x) {
                    எனில் ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } இல்லையெனில் எனில் ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        நிறுத்து;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
வெறுமை SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    எனில் (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        எனில் (mask == வெற்று) {
            முழு mask_len = icon->h * (icon->w + 7) / 8;
            முழு flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            எனில் (mask == வெற்று) {
                திரும்பு;
            }
            SDL_memset(mask, ~0, mask_len);
            எனில் (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            எனில் (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            எனில் (flags) {
                Create_Mask_From_Color_சாவி_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } இல்லையெனில் {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_உள்ளீடு_Type SDL_Get_Text_உள்ளீடு_Type(SDL_PropertiesID props)
{
    திரும்பு (SDL_Text_உள்ளீடு_Type)SDL_Get_எண்_Property(props, SDL_PROP_TEXTINPUT_TYPE_எண், SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_உள்ளீடு_Capitalization(SDL_PropertiesID props)
{
    எனில் (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_எண்)) {
        திரும்பு (SDL_Capitalization)SDL_Get_எண்_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_எண், SDL_CAPITALIZE_NONE);
    }

    தேர்வு (SDL_Get_Text_உள்ளீடு_Type(props)) {
    நிலை SDL_TEXTINPUT_TYPE_TEXT:
        திரும்பு SDL_CAPITALIZE_SENTENCES;
    நிலை SDL_TEXTINPUT_TYPE_TEXT_NAME:
        திரும்பு SDL_CAPITALIZE_சொற்கள்;
    இயல்பு:
        திரும்பு SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_உள்ளீடு_Autocorrect(SDL_PropertiesID props)
{
    திரும்பு SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_உள்ளீடு_Multiline(SDL_PropertiesID props)
{
    எனில் (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        திரும்பு SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    எனில் (SDL_GetHintBoolean(SDL_HINT_RETURN_சாவி_HIDES_IME, false)) {
        திரும்பு false;
    } இல்லையெனில் {
        திரும்பு true;
    }
}

நிலையான bool AutoShowingScreenKeyboard(வெறுமை)
{
    மாறிலி எழுத்து *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    எனில் (!hint) {
        // This hint is currently only used by the X11 video driver
        எனில் (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    எனில் (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        திரும்பு true;
    } இல்லையெனில் {
        திரும்பு false;
    }
}

bool SDL_Start_Text_உள்ளீடு(SDL_Window *window)
{
    திரும்பு SDL_Start_Text_உள்ளீடு_With_Properties(window, 0);
}

bool SDL_Start_Text_உள்ளீடு_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (window->text_உள்ளீடு_props) {
        SDL_DestroyProperties(window->text_உள்ளீடு_props);
        window->text_உள்ளீடு_props = 0;
    }

    எனில் (props) {
        window->text_உள்ளீடு_props = SDL_CreateProperties();
        எனில் (!window->text_உள்ளீடு_props) {
            திரும்பு false;
        }
        எனில் (!SDL_CopyProperties(props, window->text_உள்ளீடு_props)) {
            திரும்பு false;
        }
    }

    எனில் (_this->Set_Text_உள்ளீடு_Properties) {
        _this->Set_Text_உள்ளீடு_Properties(_this, window, props);
    }

    எனில் (!window->text_உள்ளீடு_active) {
        // Start the text input system
        எனில் (_this->Start_Text_உள்ளீடு) {
            எனில் (!_this->Start_Text_உள்ளீடு(_this, window, props)) {
                திரும்பு false;
            }
        }
        window->text_உள்ளீடு_active = true;
    }

    // Show the on-screen keyboard, if desired
    எனில் (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        எனில் (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    திரும்பு true;
}

bool SDL_Text_உள்ளீடு_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    திரும்பு window->text_உள்ளீடு_active;
}

bool SDL_Stop_Text_உள்ளீடு(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (window->text_உள்ளீடு_active) {
        // Stop the text input system
        எனில் (_this->Stop_Text_உள்ளீடு) {
            _this->Stop_Text_உள்ளீடு(_this, window);
        }
        window->text_உள்ளீடு_active = false;
    }

    // Hide the on-screen keyboard, if desired
    எனில் (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        எனில் (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    திரும்பு true;
}

bool SDL_Set_Text_உள்ளீடு_Area(SDL_Window *window, மாறிலி SDL_Rect *rect, முழு cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (rect) {
        SDL_copyp(&window->text_உள்ளீடு_rect, rect);
        window->text_உள்ளீடு_cursor = cursor;
    } இல்லையெனில் {
        SDL_zero(window->text_உள்ளீடு_rect);
        window->text_உள்ளீடு_cursor = 0;
    }

    எனில் (_this && _this->Update_Text_உள்ளீடு_Area) {
        எனில் (!_this->Update_Text_உள்ளீடு_Area(_this, window)) {
            திரும்பு false;
        }
    }
    திரும்பு true;
}

bool SDL_Get_Text_உள்ளீடு_Area(SDL_Window *window, SDL_Rect *rect, முழு *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (rect) {
        SDL_copyp(rect, &window->text_உள்ளீடு_rect);
    }
    எனில் (cursor) {
        *cursor = window->text_உள்ளீடு_cursor;
    }
    திரும்பு true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (_this->ClearComposition) {
        திரும்பு _this->ClearComposition(_this, window);
    }
    திரும்பு true;
}

bool SDL_HasScreenKeyboardSupport(வெறுமை)
{
    எனில் (_this && _this->HasScreenKeyboardSupport) {
        திரும்பு _this->HasScreenKeyboardSupport(_this);
    }
    திரும்பு false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    திரும்பு _this->screen_keyboard_shown;
}

வெறுமை SDL_SendScreenKeyboardShown(வெறுமை)
{
    எனில் (!_this || _this->screen_keyboard_shown) {
        திரும்பு;
    }

    _this->screen_keyboard_shown = true;

    எனில் (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_தள்ளு_Event(&event);
    }
}

வெறுமை SDL_SendScreenKeyboardHidden(வெறுமை)
{
    எனில் (!_this || !_this->screen_keyboard_shown) {
        திரும்பு;
    }

    _this->screen_keyboard_shown = false;

    எனில் (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_தள்ளு_Event(&event);
    }
}

முழு SDL_Get_Message_Box_மொத்தம்(வெறுமை)
{
    திரும்பு SDL_GetAtomicInt(&SDL_messagebox_மொத்தம்);
}

bool SDL_ShowMessageBox(மாறிலி SDL_MessageBoxData *messageboxdata, முழு *buttonID)
{
    முழு dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        திரும்பு SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        திரும்பு SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    எழுத்து *titlecpy = வெற்று;
    எழுத்து *msgcpy = வெற்று;
    எனில் (messageboxdata->title) {
        மாறிலி size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(எழுத்து, slen, &titleisstack);
        எனில் (!titlecpy) {
            திரும்பு false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    எனில் (messageboxdata->message) {
        மாறிலி size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(எழுத்து, slen, &msgisstack);
        எனில் (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            திரும்பு false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (வெறுமை)SDL_AtomicIncRef(&SDL_messagebox_மொத்தம்);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    எனில் (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, அளவு(*messageboxdata));
    mbdata.title = titlecpy;
    எனில் (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    எனில் (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    எனில் (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } இல்லையெனில் {
        // It's completely fine to call this function before video is initialized
        மாறிலி எழுத்து *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        எனில் (driver_name && *driver_name != 0) {
            மாறிலி எழுத்து *driver_attempt = driver_name;
            போது (driver_attempt && (*driver_attempt != 0) && !result) {
                மாறிலி எழுத்து *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                க்கு (முழு i = 0; bootstrap[i]; ++i) {
                    எனில் (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        எனில் (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        நிறுத்து;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : வெற்று;
            }
        } இல்லையெனில் {
            க்கு (முழு i = 0; bootstrap[i]; ++i) {
                எனில் (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    நிறுத்து;
                }
            }
        }
    }

    எனில் (!result) {
        மாறிலி எழுத்து *error = SDL_GetError();

        எனில் (!*error) {
            SDL_SetError("No message system available");
        }
    } இல்லையெனில் {
        SDL_ClearError();
    }

    (வெறுமை)SDL_AtomicDecRef(&SDL_messagebox_மொத்தம்);

    எனில் (current_window) {
        SDL_RaiseWindow(current_window);
    }

    எனில் (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    திரும்பு result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, மாறிலி எழுத்து *title, மாறிலி எழுத்து *message, SDL_Window *window)
{
#எனில் defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_வலது;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_வலது = gsp_Has_Gpu_வலது();
    எனில் (!has_Gpu_வலது)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    எனில் (!has_Gpu_வலது)
        gfxExit();

    திரும்பு true;
#இல்லையெனில்
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

    திரும்பு SDL_ShowMessageBox(&data, வெற்று);
#endif
}

bool SDL_ShouldAllowTopmost(வெறுமை)
{
    திரும்பு SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, முழு x, முழு y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    எனில் (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        திரும்பு true;
    }

    திரும்பு SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, வெறுமை *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!_this->SetWindowHitTest) {
        திரும்பு SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    திரும்பு _this->SetWindowHitTest(window, callback != வெற்று);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        திரும்பு SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    எனில் (!props) {
        திரும்பு false;
    }

    எனில் (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        எனில் (!surface) {
            திரும்பு false;
        }
    } இல்லையெனில் {
        surface = வெற்று;
    }

    எனில் (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        திரும்பு false;
    }

    எனில் (_this->UpdateWindowShape) {
        எனில் (!_this->UpdateWindowShape(_this, window, surface)) {
            திரும்பு false;
        }
    }
    திரும்பு true;
}

/*
 * Functions used by iOS application delegates
 */
வெறுமை SDL_OnApplicationWillTerminate(வெறுமை)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

வெறுமை SDL_OnApplicationDidReceiveMemoryWarning(வெறுமை)
{
    SDL_SendAppEvent(SDL_EVENT_கீழ்_MEMORY);
}

வெறுமை SDL_OnApplicationWillEnterBackground(வெறுமை)
{
    எனில் (_this) {
        SDL_Window *window;
        க்கு (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(வெற்று);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

வெறுமை SDL_OnApplicationDidEnterBackground(வெறுமை)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

வெறுமை SDL_OnApplicationWillEnterForeground(வெறுமை)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

வெறுமை SDL_OnApplicationDidEnterForeground(வெறுமை)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    எனில் (_this) {
        SDL_Window *window;
        க்கு (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(மாறிலி எழுத்து *path)
{
    bool result;

    எனில் (!_this) {
        திரும்பு SDL_UninitializedVideo();
    }
    எனில் (_this->vulkan_config.loader_loaded) {
        எனில் (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            திரும்பு SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } இல்லையெனில் {
        எனில் (!_this->Vulkan_LoadLibrary) {
            திரும்பு SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    எனில் (result) {
        _this->vulkan_config.loader_loaded++;
    }
    திரும்பு result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(வெறுமை)
{
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு வெற்று;
    }
    எனில் (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        திரும்பு வெற்று;
    }
    திரும்பு (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

வெறுமை SDL_Vulkan_UnloadLibrary(வெறுமை)
{
    எனில் (!_this) {
        SDL_UninitializedVideo();
        திரும்பு;
    }
    எனில் (_this->vulkan_config.loader_loaded > 0) {
        எனில் (--_this->vulkan_config.loader_loaded > 0) {
            திரும்பு;
        }
        எனில் (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

எழுத்து மாறிலி * மாறிலி *SDL_Vulkan_GetInstanceExtensions(Uint32 *மொத்தம்)
{
    Uint32 tmpcount = 0;
    எனில் (!மொத்தம்) {
        மொத்தம் = &tmpcount;
    }

    எனில் (!_this->Vulkan_GetInstanceExtensions) {
        *மொத்தம் = 0;
        SDL_Unsupported();
        திரும்பு வெற்று;
    }

    திரும்பு _this->Vulkan_GetInstanceExtensions(_this, மொத்தம்);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    எனில் (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        திரும்பு false;
    }

    CHECK_PARAM(!instance) {
        திரும்பு SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        திரும்பு SDL_InvalidParamError("surface");
    }

    எனில் (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        எனில் (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        எனில் (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        எனில் (SDL_Vulkan_LoadLibrary(வெற்று)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } இல்லையெனில் {
            திரும்பு SDL_SetError("failed to load Vulkan library");
        }
    }

    திரும்பு _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

வெறுமை SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               மாறிலி கட்டமைப்பு VkAllocationCallbacks *allocator)
{
    எனில் (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        திரும்பு false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        திரும்பு false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        திரும்பு false;
    }

    எனில் (_this->Vulkan_GetPresentationSupport) {
        திரும்பு _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    திரும்பு true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, வெற்று);

    எனில் (!_this->Metal_CreateView) {
        SDL_Unsupported();
        திரும்பு வெற்று;
    }

    எனில் (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        எனில் (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        எனில் (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    திரும்பு _this->Metal_CreateView(_this, window);
}

வெறுமை SDL_Metal_DestroyView(SDL_MetalView view)
{
    எனில் (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

வெறுமை *SDL_Metal_GetLayer(SDL_MetalView view)
{
    எனில் (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            திரும்பு வெற்று;
        }
        திரும்பு _this->Metal_GetLayer(_this, view);
    } இல்லையெனில் {
        SDL_SetError("Metal is not supported.");
        திரும்பு வெற்று;
    }
}

#எனில் defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
மாறிலி எழுத்து *SDL_GetCSSCursorName(SDL_SystemCursor id, மாறிலி எழுத்து **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    தேர்வு (id) {
    நிலை SDL_SYSTEM_CURSOR_DEFAULT:
        திரும்பு "default";

    நிலை SDL_SYSTEM_CURSOR_TEXT:
        திரும்பு "text";

    நிலை SDL_SYSTEM_CURSOR_WAIT:
        திரும்பு "wait";

    நிலை SDL_SYSTEM_CURSOR_CROSSHAIR:
        திரும்பு "crosshair";

    நிலை SDL_SYSTEM_CURSOR_PROGRESS:
        திரும்பு "progress";

    நிலை SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        எனில் (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        திரும்பு "nwse-resize";

    நிலை SDL_SYSTEM_CURSOR_NESW_RESIZE:
        எனில் (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        திரும்பு "nesw-resize";

    நிலை SDL_SYSTEM_CURSOR_EW_RESIZE:
        எனில் (fallback_name) {
            *fallback_name = "col-resize";
        }
        திரும்பு "ew-resize";

    நிலை SDL_SYSTEM_CURSOR_NS_RESIZE:
        எனில் (fallback_name) {
            *fallback_name = "row-resize";
        }
        திரும்பு "ns-resize";

    நிலை SDL_SYSTEM_CURSOR_MOVE:
        எனில் (fallback_name) {
            *fallback_name = "all-scroll";
        }
        திரும்பு "move";

    நிலை SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        திரும்பு "not-allowed";

    நிலை SDL_SYSTEM_CURSOR_POINTER:
        திரும்பு "pointer";

    நிலை SDL_SYSTEM_CURSOR_NW_RESIZE:
        திரும்பு "nw-resize";

    நிலை SDL_SYSTEM_CURSOR_N_RESIZE:
        திரும்பு "n-resize";

    நிலை SDL_SYSTEM_CURSOR_NE_RESIZE:
        திரும்பு "ne-resize";

    நிலை SDL_SYSTEM_CURSOR_E_RESIZE:
        திரும்பு "e-resize";

    நிலை SDL_SYSTEM_CURSOR_SE_RESIZE:
        திரும்பு "se-resize";

    நிலை SDL_SYSTEM_CURSOR_S_RESIZE:
        திரும்பு "s-resize";

    நிலை SDL_SYSTEM_CURSOR_SW_RESIZE:
        திரும்பு "sw-resize";

    நிலை SDL_SYSTEM_CURSOR_W_RESIZE:
        திரும்பு "w-resize";

    நிலை SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        திரும்பு "context-menu";

    நிலை SDL_SYSTEM_CURSOR_HELP:
        திரும்பு "help";

    நிலை SDL_SYSTEM_CURSOR_CELL:
        திரும்பு "cell";

    நிலை SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        திரும்பு "vertical-text";

    நிலை SDL_SYSTEM_CURSOR_ALIAS:
        திரும்பு "alias";

    நிலை SDL_SYSTEM_CURSOR_COPY:
        திரும்பு "copy";

    நிலை SDL_SYSTEM_CURSOR_NO_DROP:
        திரும்பு "no-drop";

    நிலை SDL_SYSTEM_CURSOR_GRAB:
        திரும்பு "grab";

    நிலை SDL_SYSTEM_CURSOR_GRABBING:
        திரும்பு "grabbing";

    நிலை SDL_SYSTEM_CURSOR_COL_RESIZE:
        திரும்பு "col-resize";

    நிலை SDL_SYSTEM_CURSOR_ROW_RESIZE:
        திரும்பு "row-resize";

    நிலை SDL_SYSTEM_CURSOR_ALL_SCROLL:
        எனில் (fallback_name) {
            *fallback_name = "move";
        }
        திரும்பு "all-scroll";

    நிலை SDL_SYSTEM_CURSOR_ZOOM_IN:
        திரும்பு "zoom-in";

    நிலை SDL_SYSTEM_CURSOR_ZOOM_OUT:
        திரும்பு "zoom-out";

    இயல்பு:
        திரும்பு "default";
    }
}
#endif

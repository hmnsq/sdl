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

#अन्तर्भाव "SDL_internal.h"

// The high-level video driver subsystem

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_clipboard_c.h"
#अन्तर्भाव "SDL_egl_c.h"
#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_pixels_c.h"
#अन्तर्भाव "SDL_rect_c.h"
#अन्तर्भाव "SDL_video_c.h"
#अन्तर्भाव "../events/SDL_events_c.h"
#अन्तर्भाव "../SDL_hints_c.h"
#अन्तर्भाव "../SDL_properties_c.h"
#अन्तर्भाव "../timer/SDL_timer_c.h"
#अन्तर्भाव "../camera/SDL_camera_c.h"
#अन्तर्भाव "../render/SDL_sysrender.h"
#अन्तर्भाव "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#अन्तर्भाव <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#जर defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#अन्तर्भाव <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#जर defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#अन्तर्भाव <SDL3/SDL_opengles2.h>
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
#अन्तर्भाव <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#अन्तर्भाव <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
स्थिर VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_आदान_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    रिक्त
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        परत result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        परत result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        परत result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        परत result;                                                  \
    }

#जर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
बाह्य bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
बाह्य bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
बाह्य bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
बाह्य bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
बाह्य शून्य SDL_UpdateLifecycleObserver(शून्य);
#endif

स्थिर शून्य SDL_CheckWindowDisplayChanged(SDL_Window *window);
स्थिर शून्य SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
स्थिर शून्य SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
स्थिर bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    जर (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        परत true;
    }
    परत false;
}

स्थिर bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    परत !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

स्थिर bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    परत !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

स्थिर bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    परत !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

स्थिर bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    परत !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

स्थिर bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    परत !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
स्थिर bool syncHint;

स्थिर शून्य SDL_SyncHintWatcher(शून्य *userdata, स्थिरांक अक्षर *name, स्थिरांक अक्षर *old_मूल्य, स्थिरांक अक्षर *new_मूल्य)
{
    syncHint = SDL_GetStringBoolean(new_मूल्य, false);
}

स्थिर शून्य SDL_SyncIfRequired(SDL_Window *window)
{
    जर (syncHint) {
        SDL_SyncWindow(window);
    }
}

स्थिर शून्य SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    जर (window->parent) {
        जर (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        जर (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } अन्यथा {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = रिक्त;
    }

    जर (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        जर (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

प्रकारव्याख्या संरचना
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    शून्य *pixels;
    पूर्णांक pitch;
    पूर्णांक bytes_per_pixel;
} SDL_WindowTextureData;

स्थिर Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#जर (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    जर (_this->GL_CreateContext) {
        परत SDL_WINDOW_OPENGL;
    }
#endif
#जर defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    जर (_this->Metal_CreateView) {
        परत SDL_WINDOW_METAL;
    }
#endif
#जर defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    जर (SDL_strcmp(_this->name, "openvr") == 0) {
        परत SDL_WINDOW_OPENGL;
    }
#endif
    परत 0;
}

स्थिर bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, शून्य **pixels, पूर्णांक *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    स्थिरांक bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    पूर्णांक i;
    पूर्णांक w, h;
    स्थिरांक SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    जर (!data) {
        SDL_Renderer *renderer = रिक्त;
        स्थिरांक अक्षर *render_driver = रिक्त;

        // See if there's a render driver being requested
        स्थिरांक अक्षर *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        जर (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        जर (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        जर (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = रिक्त;
        }

        अक्षर *render_driver_copy = रिक्त;
        जर (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            जर (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                अक्षर *prev = render_driver_copy;
                अक्षर *ptr = prev;
                पर्यंत ((ptr = SDL_strchr(ptr, ',')) != रिक्त) {
                    *ptr = '\0';
                    स्थिरांक bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    जर (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } अन्यथा {
                        ptr++;
                        prev = ptr;
                    }
                }

                जर (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        जर (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            जर (!renderer) {
                // The error for this specific renderer has already been set
                परत false;
            }
        } अन्यथा {
            SDL_assert(render_driver_copy == रिक्त);
            स्थिरांक पूर्णांक total = SDL_Get_अंक_Render_Drivers();
            साठी (i = 0; i < total; ++i) {
                स्थिरांक अक्षर *name = SDL_GetRenderDriver(i);
                जर (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    जर (renderer) {
                        थांबा; // this will work.
                    }
                }
            }
            जर (!renderer) {
                परत SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != रिक्त); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, आकार(*data));
        जर (!data) {
            SDL_DestroyRenderer(renderer);
            परत false;
        }
        जर (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            परत false;
        }

        data->renderer = renderer;
    }

    texture_formats = (स्थिरांक SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, रिक्त);
    जर (!texture_formats) {
        परत false;
    }

    // Free any old texture and pixel data
    जर (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = रिक्त;
    }
    SDL_free(data->pixels);
    data->pixels = रिक्त;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    साठी (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        जर (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            थांबा;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    जर (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        परत false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        स्थिरांक माप_प्रकार allocsize = (माप_प्रकार)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        जर (!data->pixels) {
            परत false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, रिक्त);

    परत true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    जर (!data) {
        परत false;
    }
    जर (!data->renderer) {
        परत false;
    }
    परत SDL_SetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    जर (!data) {
        परत false;
    }
    जर (!data->renderer) {
        परत false;
    }
    परत SDL_GetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, स्थिरांक SDL_Rect *rects, पूर्णांक numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    शून्य *src;
    पूर्णांक w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    जर (!data || !data->texture) {
        परत SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    जर (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (शून्य *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        जर (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            परत false;
        }

        जर (!SDL_RenderTexture(data->renderer, data->texture, रिक्त, रिक्त)) {
            परत false;
        }

        SDL_RenderPresent(data->renderer);
    }
    परत true;
}

स्थिर शून्य SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    जर (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);

        जर (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        जर (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

स्थिर SDL_VideoDevice *_this = रिक्त;
स्थिर SDL_AtomicInt SDL_messagebox_मोजणी;

स्थिर पूर्णांक SDLCALL cmpmodes(स्थिरांक शून्य *A, स्थिरांक शून्य *B)
{
    स्थिरांक SDL_DisplayMode *a = (स्थिरांक SDL_DisplayMode *)A;
    स्थिरांक SDL_DisplayMode *b = (स्थिरांक SDL_DisplayMode *)B;
    पूर्णांक a_refresh_rate = (पूर्णांक)(a->refresh_rate * 100);
    पूर्णांक b_refresh_rate = (पूर्णांक)(b->refresh_rate * 100);
    पूर्णांक a_pixel_density = (पूर्णांक)(a->pixel_density * 100);
    पूर्णांक b_pixel_density = (पूर्णांक)(b->pixel_density * 100);

    जर (a->w != b->w) {
        परत b->w - a->w;
    } अन्यथा जर (a->h != b->h) {
        परत b->h - a->h;
    } अन्यथा जर (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        परत SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } अन्यथा जर (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        परत SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } अन्यथा जर (a_refresh_rate != b_refresh_rate) {
        परत b_refresh_rate - a_refresh_rate;
    } अन्यथा जर (a_pixel_density != b_pixel_density) {
        परत a_pixel_density - b_pixel_density;
    }
    परत 0;
}

bool SDL_UninitializedVideo(शून्य)
{
    परत SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
स्थिर स्थिरांक VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

पूर्णांक SDL_Get_अंक_Video_Drivers(शून्य)
{
    स्थिर पूर्णांक अंक_drivers = -1;

    जर (अंक_drivers >= 0) {
        परत अंक_drivers;
    }

    अंक_drivers = 0;

    // Build a list of unique video drivers.
    साठी (पूर्णांक i = 0; bootstrap[i] != रिक्त; ++i) {
        bool duplicate = false;
        साठी (पूर्णांक j = 0; j < i; ++j) {
            जर (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                थांबा;
            }
        }

        जर (!duplicate) {
            deduped_bootstrap[अंक_drivers++] = bootstrap[i];
        }
    }

    परत अंक_drivers;
}

स्थिरांक अक्षर *SDL_GetVideoDriver(पूर्णांक index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_अंक_Video_Drivers()) {
        SDL_InvalidParamError("index");
        परत रिक्त;
    }
    परत deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(स्थिरांक अक्षर *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    पूर्णांक i = 0;

    // Check to make sure we don't overwrite '_this'
    जर (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    जर (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        जा pre_driver_error;
    }
    init_events = true;
    जर (!SDL_InitKeyboard()) {
        जा pre_driver_error;
    }
    init_keyboard = true;
    जर (!SDL_PreInitMouse()) {
        जा pre_driver_error;
    }
    init_mouse = true;
    जर (!SDL_InitTouch()) {
        जा pre_driver_error;
    }
    init_touch = true;
    जर (!SDL_InitPen()) {
        जा pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = रिक्त;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    जर (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    जर (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    जर (driver_name && *driver_name != 0) {
        स्थिरांक अक्षर *driver_attempt = driver_name;
        पर्यंत (driver_attempt && *driver_attempt != 0 && !video) {
            स्थिरांक अक्षर *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            साठी (i = 0; bootstrap[i]; ++i) {
                जर (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    जर (video) {
                        थांबा;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
        }
    } अन्यथा {
        साठी (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            जर (video) {
                थांबा;
            }
        }
    }
    जर (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } अन्यथा {
        जर (driver_name) {
            SDL_SetError("%s not available", driver_name);
            जा pre_driver_error;
        }
        SDL_SetError("No available video device");
        जा pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = रिक्त;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    जर (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        परत false;
    }

    // Make sure some displays were added
    जर (_this->अंक_displays == 0) {
        SDL_QuitVideo();
        परत SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, रिक्त);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    जर (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    परत true;

pre_driver_error:
    SDL_assert(_this == रिक्त);
    जर (init_pen) {
        SDL_QuitPen();
    }
    जर (init_touch) {
        SDL_QuitTouch();
    }
    जर (init_mouse) {
        SDL_QuitMouse();
    }
    जर (init_keyboard) {
        SDL_QuitKeyboard();
    }
    जर (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    परत false;
}

स्थिरांक अक्षर *SDL_GetCurrentVideoDriver(शून्य)
{
    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    परत _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(शून्य)
{
    परत _this;
}

bool SDL_OnVideoThread(शून्य)
{
    परत (_this && SDL_GetCurrentThreadID() == _this->thread);
}

शून्य SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    जर (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(शून्य)
{
    जर (_this) {
        परत _this->system_theme;
    } अन्यथा {
        परत SDL_SYSTEM_THEME_UNKNOWN;
    }
}

शून्य SDL_UpdateDesktopBounds(शून्य)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    जर (displays) {
        साठी (पूर्णांक i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            जर (SDL_GetDisplayBounds(displays[i], &bounds)) {
                जर (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } अन्यथा {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

स्थिर शून्य SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    जर (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    जर (mode->refresh_rate_numerator > 0) {
        जर (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (दशांश)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } अन्यथा {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(स्थिरांक SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    जर (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, आकार(display.desktop_mode));
    }
    परत SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(स्थिरांक SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    पूर्णांक i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(आकार(*new_display));
    जर (!new_display) {
        परत 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->अंक_displays + 1) * आकार(*displays));
    जर (!displays) {
        SDL_free(new_display);
        परत 0;
    }
    _this->displays = displays;
    _this->displays[_this->अंक_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    जर (display->name) {
        new_display->name = SDL_strdup(display->name);
    } अन्यथा {
        अक्षर name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    जर (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    साठी (i = 0; i < new_display->अंक_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    जर (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    परत id;
}

शून्य SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    साठी (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

शून्य SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

शून्य SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    पूर्णांक display_index = SDL_GetDisplayIndex(displayID);
    जर (display_index < 0) {
        परत;
    }

    display = _this->displays[display_index];

    जर (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = रिक्त;
    SDL_free(display->internal);
    display->internal = रिक्त;
    SDL_free(display);

    जर (display_index < (_this->अंक_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->अंक_displays - display_index - 1) * आकार(_this->displays[display_index]));
    }
    --_this->अंक_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(पूर्णांक *मोजणी)
{
    पूर्णांक i;
    SDL_DisplayID *displays;

    जर (!_this) {
        जर (मोजणी) {
            *मोजणी = 0;
        }

        SDL_UninitializedVideo();
        परत रिक्त;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->अंक_displays + 1) * आकार(*displays));
    जर (displays) {
        जर (मोजणी) {
            *मोजणी = _this->अंक_displays;
        }

        साठी (i = 0; i < _this->अंक_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } अन्यथा {
        जर (मोजणी) {
            *मोजणी = 0;
        }
    }
    परत displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    पूर्णांक display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    जर (display_index < 0) {
        परत रिक्त;
    }
    परत _this->displays[display_index];
}

स्थिर SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    जर (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    जर (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    परत displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    परत SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(शून्य)
{
    जर (!_this || _this->अंक_displays == 0) {
        SDL_UninitializedVideo();
        परत 0;
    }
    परत _this->displays[0]->id;
}

पूर्णांक SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    पूर्णांक display_index;

    जर (!_this) {
        SDL_UninitializedVideo();
        परत -1;
    }

    साठी (display_index = 0; display_index < _this->अंक_displays; ++display_index) {
        जर (displayID == _this->displays[display_index]->id) {
            परत display_index;
        }
    }
    SDL_SetError("Invalid display");
    परत -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    परत display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    परत SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    जर (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    परत display->props;
}

स्थिरांक अक्षर *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    परत display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        परत SDL_InvalidParamError("rect");
    }

    जर (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        जर (_this->GetDisplayBounds(_this, display, rect)) {
            परत true;
        }
    }

    // Assume that the displays are left to right
    जर (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } अन्यथा {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    परत true;
}

स्थिर पूर्णांक ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    स्थिरांक अक्षर *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    परत hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        परत SDL_InvalidParamError("rect");
    }

    जर (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        परत true;
    }

    जर (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        जर (_this->GetDisplayUsableBounds(_this, display, rect)) {
            परत true;
        }
    }

    // Oh well, just give the entire display bounds.
    परत SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    जर (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        परत display->natural_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        परत SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    जर (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        परत display->current_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        परत SDL_ORIENTATION_LANDSCAPE;
    }
}

शून्य SDL_SetDisplayContentScale(SDL_VideoDisplay *display, दशांश scale)
{
    जर (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        साठी (window = _this->windows; window; window = window->next) {
            जर (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

दशांश SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    परत display->content_scale;
}

शून्य SDL_SetWindowHDRProperties(SDL_Window *window, स्थिरांक SDL_HDROutputProperties *HDR, bool send_event)
{
    स्थिरांक SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    जर (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        जर (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

शून्य SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, स्थिरांक SDL_HDROutputProperties *HDR)
{
    स्थिरांक SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    स्थिरांक bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	जर (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    जर (changed && !SDL_DriverSendsHDRChanges(_this)) {
        साठी (SDL_Window *w = display->device->windows; w; w = w->next) {
            जर (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

स्थिर शून्य SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    जर (display->अंक_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
स्थिर स्थिरांक SDL_DisplayMode *SDL_GetFullscreenModeMatch(स्थिरांक SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    जर (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        परत रिक्त;
    }

    SDL_memcpy(&fullscreen_mode, mode, आकार(fullscreen_mode));
    जर (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = रिक्त;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    जर (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        जर (!mode) {
            साठी (पूर्णांक i = 0; i < display->अंक_fullscreen_modes; ++i) {
                जर (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], आकार(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    थांबा;
                }
            }
        }

        // Search for a mode with the same characteristics
        जर (!mode) {
            साठी (पूर्णांक i = 0; i < display->अंक_fullscreen_modes; ++i) {
                जर (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    थांबा;
                }
            }
        }
    }
    परत mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, स्थिरांक SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    पूर्णांक i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, आकार(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->अंक_fullscreen_modes;
    साठी (i = 0; i < nmodes; ++i) {
        जर (cmpmodes(&new_mode, &modes[i]) == 0) {
            परत false;
        }
    }

    // Go ahead and add the new mode
    जर (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * आकार(*modes));
        जर (!modes) {
            परत false;
        }

        जर (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * आकार(*modes));
            साठी (i = 0; i < nmodes; ++i) {
                जर (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->अंक_fullscreen_modes++], &new_mode, आकार(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->अंक_fullscreen_modes,
              आकार(SDL_DisplayMode), cmpmodes);

    परत true;
}

शून्य SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    पूर्णांक i;

    साठी (i = display->अंक_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = रिक्त;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = रिक्त;
    display->अंक_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, पूर्णांक *मोजणी)
{
    पूर्णांक i;
    पूर्णांक अंक_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    जर (मोजणी) {
        *मोजणी = 0;
    }

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    SDL_UpdateFullscreenDisplayModes(display);

    अंक_modes = display->अंक_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((अंक_modes + 1) * आकार(*result) + अंक_modes * आकार(**result));
    जर (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((अंक_modes + 1) * आकार(*result)));
        जर (अंक_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, अंक_modes * आकार(*modes));
        }
        साठी (i = 0; i < अंक_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = रिक्त;

        जर (मोजणी) {
            *मोजणी = अंक_modes;
        }
    } अन्यथा {
        जर (मोजणी) {
            *मोजणी = 0;
        }
    }
    परत result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, पूर्णांक w, पूर्णांक h, दशांश refresh_rate, bool include_वरचा_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        परत SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    स्थिरांक SDL_DisplayMode *mode, *closest = रिक्त;
    दशांश aspect_ratio;
    पूर्णांक i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    जर (h > 0) {
        aspect_ratio = (दशांश)w / h;
    } अन्यथा {
        aspect_ratio = 1.0f;
    }

    जर (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    साठी (i = 0; i < display->अंक_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        जर (w > mode->w) {
            // Out of sorted modes large enough here
            थांबा;
        }
        जर (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            सुरूठेवा;
        }
        जर (mode->pixel_density > 1.0f && !include_वरचा_density_modes) {
            सुरूठेवा;
        }
        जर (closest) {
            दशांश current_aspect_ratio = (दशांश)mode->w / mode->h;
            दशांश closest_aspect_ratio = (दशांश)closest->w / closest->h;
            जर (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                सुरूठेवा;
            }

            जर (mode->w == closest->w && mode->h == closest->h) {
                जर (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    सुरूठेवा;
                }
                जर (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    सुरूठेवा;
                }
            }
        }

        closest = mode;
    }
    जर (!closest) {
        परत SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    परत true;
}

स्थिर bool DisplayModeChanged(स्थिरांक SDL_DisplayMode *old_mode, स्थिरांक SDL_DisplayMode *new_mode)
{
    परत ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

शून्य SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, स्थिरांक SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    जर (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        परत;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    जर (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        जर (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

स्थिरांक SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    परत &display->desktop_mode;
}

शून्य SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, स्थिरांक SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    जर (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } अन्यथा {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    जर (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

स्थिरांक SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    परत display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    जर (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        परत true;
    }

    जर (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    जर (mode == display->current_mode) {
        परत true;
    }
#endif

    // Actually change the display mode
    जर (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        जर (!result) {
            परत false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    परत true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
स्थिर शून्य SDL_GetClosestPointOnRect(स्थिरांक SDL_Rect *rect, SDL_Point *point)
{
    स्थिरांक पूर्णांक उजवा = rect->x + rect->w - 1;
    स्थिरांक पूर्णांक bottom = rect->y + rect->h - 1;

    जर (point->x < rect->x) {
        point->x = rect->x;
    } अन्यथा जर (point->x > उजवा) {
        point->x = उजवा;
    }

    जर (point->y < rect->y) {
        point->y = rect->y;
    } अन्यथा जर (point->y > bottom) {
        point->y = bottom;
    }
}

स्थिर SDL_DisplayID GetDisplayForRect(पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h)
{
    पूर्णांक i, dist;
    SDL_DisplayID closest = 0;
    पूर्णांक closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    जर (_this) {
        साठी (i = 0; i < _this->अंक_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            जर (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, रिक्त)) {
                परत display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            जर (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    जर (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    परत closest;
}

शून्य SDL_RelativeToGlobalForWindow(SDL_Window *window, पूर्णांक rel_x, पूर्णांक rel_y, पूर्णांक *abs_x, पूर्णांक *abs_y)
{
    SDL_Window *w;

    जर (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        साठी (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            जर (!SDL_WINDOW_IS_POPUP(w)) {
                थांबा;
            }
        }
    }

    जर (abs_x) {
        *abs_x = rel_x;
    }
    जर (abs_y) {
        *abs_y = rel_y;
    }
}

शून्य SDL_GlobalToRelativeForWindow(SDL_Window *window, पूर्णांक abs_x, पूर्णांक abs_y, पूर्णांक *rel_x, पूर्णांक *rel_y)
{
    SDL_Window *w;

    जर (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        साठी (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            जर (!SDL_WINDOW_IS_POPUP(w)) {
                थांबा;
            }
        }
    }

    जर (rel_x) {
        *rel_x = abs_x;
    }
    जर (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(स्थिरांक SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        परत 0;
    }

    परत GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(स्थिरांक SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        परत 0;
    }

    परत GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

स्थिर SDL_DisplayID GetDisplayAtOrigin(पूर्णांक x, पूर्णांक y)
{
    साठी (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
        SDL_Rect rect;
        स्थिरांक SDL_DisplayID cur_id = _this->displays[i]->id;
        जर (SDL_GetDisplayBounds(cur_id, &rect)) {
            जर (x == rect.x && y == rect.y) {
                परत cur_id;
            }
        }
    }

    परत 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    पूर्णांक x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    जर (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    जर (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        जर (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } अन्यथा {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    जर (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    परत displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, रिक्त);

    // An explicit fullscreen display overrides all
    जर (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    जर (!displayID) {
        displayID = window->pending_displayID;
    }
    जर (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        स्थिरांक पूर्णांक x = window->last_position_pending ? window->pending.x : window->x;
        स्थिरांक पूर्णांक y = window->last_position_pending ? window->pending.y : window->y;
        स्थिरांक पूर्णांक w = window->last_size_pending ? window->pending.w : window->w;
        स्थिरांक पूर्णांक h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        जर (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    जर (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    परत SDL_GetVideoDisplay(displayID);
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
    जर (fs_display) {
        SDL_Set_संख्या_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } अन्यथा {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    परत GetDisplayForWindow(window);
}

स्थिर शून्य SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    जर (SDL_SendsDisplayChanges(_this)) {
        परत;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    जर (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        जर (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            जर (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                पूर्णांक old_area = old_overlap.w * old_overlap.h;
                पूर्णांक new_area = new_overlap.w * new_overlap.h;
                दशांश new_overlap_ratio = (new_area / ((दशांश)old_area + new_area));
                जर (new_overlap_ratio < 0.80) {
                    परत;
                }
            }
        }
    }

    जर (displayID != window->displayID) {
        पूर्णांक i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        साठी (i = 0; i < _this->अंक_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            जर (display->fullscreen_window == window) {
                जर (display_index != i) {
                    जर (display_index < 0) {
                        display_index = i;
                    } अन्यथा {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        जर (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = रिक्त;
                    }
                }
                थांबा;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (पूर्णांक)displayID, 0);
    }
}

दशांश SDL_GetWindowPixelDensity(SDL_Window *window)
{
    पूर्णांक window_w, window_h, pixel_w, pixel_h;
    दशांश pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    जर (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (दशांश)pixel_w / window_w;
    }
    परत pixel_density;
}

दशांश SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    परत window->display_scale;
}

स्थिर शून्य SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    दशांश display_scale;

    जर (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } अन्यथा {
        स्थिरांक दशांश pixel_density = SDL_GetWindowPixelDensity(window);
        स्थिरांक दशांश content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    जर (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = रिक्त;
    SDL_DisplayMode *mode = रिक्त;
    पूर्णांक i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    जर (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    जर (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        जर (!display) {
            // This should never happen, but it did...
            जा done;
        }
    } अन्यथा {
        साठी (i = 0; i < _this->अंक_displays; ++i) {
            display = _this->displays[i];
            जर (display->fullscreen_window == window) {
                थांबा;
            }
        }
        जर (!display || i == _this->अंक_displays) {
            // Already not fullscreen on any display
            display = रिक्त;
        }
    }

    जर (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        जर (mode) {
            window->fullscreen_exclusive = true;
        } अन्यथा {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#जर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    जर (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        जर (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            जर (display) {
                display->fullscreen_window = रिक्त;
            }
            जा done;
        }
        जर (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            जर (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                जर (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    जा error;
                }
            } अन्यथा जर (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                साठी (i = 0; i < _this->अंक_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    जर (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, रिक्त);
                        जर (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = रिक्त;
                    }
                }
            }

            जर (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                जा done;
            }
        }
    }
#endif

    जर (display) {
        // Restore the video mode on other displays if needed
        साठी (i = 0; i < _this->अंक_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            जर (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, रिक्त);
                other->fullscreen_window = रिक्त;
            }
        }
    }

    जर (fullscreen) {
        पूर्णांक mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        जर (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        जर (!SDL_SetDisplayModeForDisplay(display, mode)) {
            जा error;
        }
        जर (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            जर (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } अन्यथा {
                resized = true;
            }

            जर (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                जर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } अन्यथा जर (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                जा error;
            }
        }

        जर (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            जर (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                जर (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } अन्यथा {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                जर (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                जर (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } अन्यथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } अन्यथा {
        bool resized = false;

        // Restore the desktop mode
        जर (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, रिक्त);
        }
        जर (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            जर (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                जर (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } अन्यथा {
                resized = true;
            }

            जर (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                जर (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } अन्यथा जर (ret == SDL_FULLSCREEN_FAILED) {
                जा error;
            }
        }

        जर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            जर (display) {
                display->fullscreen_window = रिक्त;
            }

            जर (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                जर (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } अन्यथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    परत true;

error:
    जर (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    परत false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, स्थिरांक SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (mode) {
        जर (!SDL_GetFullscreenModeMatch(mode)) {
            परत SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } अन्यथा {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#जर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    जर (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    जर (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    परत true;
}

स्थिरांक SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);
    CHECK_WINDOW_NOT_POPUP(window, रिक्त);

    जर (window->flags & SDL_WINDOW_FULLSCREEN) {
        परत SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } अन्यथा {
        परत SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

शून्य *SDL_GetWindowICCProfile(SDL_Window *window, माप_प्रकार *size)
{
    जर (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        परत रिक्त;
    }
    परत _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    स्थिरांक SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    जर (mode) {
        परत mode->format;
    } अन्यथा {
        परत SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_वरचा_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_शीर्ष | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

स्थिर SDL_INLINE bool IsAcceptingDragAndDrop(शून्य)
{
    जर (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        परत true;
    }
    परत false;
}

// prepare a newly-created window
स्थिर SDL_INLINE शून्य PrepareDragAndDropSupport(SDL_Window *window)
{
    जर (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
शून्य SDL_ToggleDragAndDropSupport(शून्य)
{
    जर (_this && _this->AcceptDragAndDrop) {
        स्थिरांक bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        साठी (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(पूर्णांक *मोजणी)
{
    जर (मोजणी) {
        *मोजणी = 0;
    }

    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }

    SDL_Window *window;
    पूर्णांक अंक_added = 0;
    पूर्णांक अंक_windows = 0;
    साठी (window = _this->windows; window; window = window->next) {
        ++अंक_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((अंक_windows + 1) * आकार(*windows));
    जर (!windows) {
        परत रिक्त;
    }

    साठी (window = _this->windows; window; window = window->next) {
        windows[अंक_added++] = window;
        जर (अंक_added == अंक_windows) {
            // Race condition? Multi-threading not supported, ignore it
            थांबा;
        }
    }
    windows[अंक_added] = रिक्त;

    जर (मोजणी) {
        *मोजणी = अंक_added;
    }
    परत windows;
}

स्थिर शून्य ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    जर (!SDL_WINDOW_IS_POPUP(window)) {
        जर (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        जर (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        जर (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        जर (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        जर (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        जर (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

स्थिर शून्य SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    जर (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } अन्यथा {
        ApplyWindowFlags(window, flags);
        जर (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#जर defined(SDL_PLATFORM_LINUX)
    जर (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_मूल्य(window, 0.0f);
    }
#endif
}

स्थिर bool SDL_ContextNotSupported(स्थिरांक अक्षर *name)
{
    परत SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

स्थिर bool SDL_DllNotSupported(स्थिरांक अक्षर *name)
{
    परत SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

स्थिर संरचना {
    स्थिरांक अक्षर *property_name;
    SDL_WindowFlags flag;
    bool invert_मूल्य;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_शीर्ष_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_शीर्ष,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_वरचा_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_वरचा_PIXEL_DENSITY,  false },
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

स्थिर SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    अचिन्हित i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, 0);

    साठी (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        जर (SDL_WindowFlagProperties[i].invert_मूल्य) {
            जर (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } अन्यथा {
            जर (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    परत flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    स्थिरांक अक्षर *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, रिक्त);
    पूर्णांक x = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_संख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णांक y = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_संख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णांक w = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, 0);
    पूर्णांक h = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, रिक्त);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    जर (!_this) {
        // Initialize the video system if needed
        जर (!SDL_Init(SDL_INIT_VIDEO)) {
            परत रिक्त;
        }

        // Make clang-tidy happy
        जर (!_this) {
            परत रिक्त;
        }
    }

    जर ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        परत रिक्त;
    }

    जर ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        जर (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            परत रिक्त;
        }

        // Tooltip and popup menu window must specify a parent window
        जर (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            परत रिक्त;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    जर (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (अचिन्हित पूर्णांक)type_flags);
        परत रिक्त;
    }

    // Make sure the display list is up to date for window placement
    जर (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    जर (w < 1) {
        w = 1;
    }
    जर (h < 1) {
        h = 1;
    }

    जर (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        जर ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा जर ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        जर (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        जर (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        जर (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            जर (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        जर (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            जर (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    जर (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (अचिन्हित पूर्णांक)graphics_flags);
        परत रिक्त;
    }

    // Some platforms have certain graphics backends enabled by default
    जर (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    जर (flags & SDL_WINDOW_OPENGL) {
        जर (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            परत रिक्त;
        }
        जर (!SDL_GL_LoadLibrary(रिक्त)) {
            परत रिक्त;
        }
    }

    जर (flags & SDL_WINDOW_VULKAN) {
        जर (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            परत रिक्त;
        }
        जर (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            परत रिक्त;
        }
    }

    जर (flags & SDL_WINDOW_METAL) {
        जर (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            परत रिक्त;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, आकार(*window));
    जर (!window) {
        परत रिक्त;
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
    जर (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    जर (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    जर (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    जर (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    जर (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_ढकला_Error();
        SDL_DestroyWindow(window);
        SDL_काढा_Error();
        परत रिक्त;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#जर !defined(SDL_PLATFORM_WINDOWS)
    जर (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    जर (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    परत window;
}

SDL_Window *SDL_CreateWindow(स्थिरांक अक्षर *title, पूर्णांक w, पूर्णांक h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    जर (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, w);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, h);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    परत window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, पूर्णांक offset_x, पूर्णांक offset_y, पूर्णांक w, पूर्णांक h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    जर (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        परत रिक्त;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_संख्या, offset_x);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_संख्या, offset_y);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, w);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, h);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    परत window;
}

स्थिर bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    जर (!_this->ReconfigureWindow) {
        परत false;
    }

    स्थिरांक SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    जर (graphics_flags & (graphics_flags - 1)) {
        परत SDL_SetError("Conflicting window flags specified");
    }

    जर ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        परत SDL_ContextNotSupported("OpenGL");
    }
    जर ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        परत SDL_ContextNotSupported("Vulkan");
    }
    जर ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        परत SDL_ContextNotSupported("Metal");
    }

    जर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        जर (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            परत false;
        }
    } अन्यथा {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        जर (!_this->ReconfigureWindow(_this, window, 0)) {
            परत false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        जर (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        जर (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    जर (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(रिक्त);
        जर (!loaded_opengl) {
            परत false;
        }
    } अन्यथा जर (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(रिक्त);
        जर (!loaded_vulkan) {
            परत false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    जर (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        जर (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        जर (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        परत false;
    }

    window->flags |= graphics_flags;

    परत true;
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
    जर (graphics_flags & (graphics_flags - 1)) {
        परत SDL_SetError("Conflicting window flags specified");
    }

    जर ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        परत SDL_ContextNotSupported("OpenGL");
    }
    जर ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        परत SDL_ContextNotSupported("Vulkan");
    }
    जर ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        परत SDL_ContextNotSupported("Metal");
    }

    जर (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } अन्यथा {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    जर (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    जर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        स्थिरांक bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    जर ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        जर (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } अन्यथा {
            need_gl_unload = true;
        }
    } अन्यथा जर (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    जर ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        जर (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } अन्यथा {
            need_vulkan_unload = true;
        }
    } अन्यथा जर (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    जर (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    जर (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    जर (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    जर (need_gl_load) {
        जर (!SDL_GL_LoadLibrary(रिक्त)) {
            परत false;
        }
        loaded_opengl = true;
    }

    जर (need_vulkan_load) {
        जर (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            परत false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    जर (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        जर (!_this->CreateSDLWindow(_this, window, 0)) {
            जर (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            जर (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            परत false;
        }
    }

    जर (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    जर (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    जर (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    जर (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    जर (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    जर (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    जर (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    परत true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    जर (!SDL_ReconfigureWindowInternal(window, flags)) {
        परत SDL_RecreateWindow(window, flags);
    }

    परत true;
}

bool SDL_HasWindows(शून्य)
{
    परत _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    परत window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    जर (id) {
        साठी (window = _this->windows; window; window = window->next) {
            जर (window->id == id) {
                परत window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    परत रिक्त;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    परत window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    जर (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    परत window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    परत window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, स्थिरांक अक्षर *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (title == window->title) {
        परत true;
    }
    जर (!title) {
        title = "";
    }
    जर (window->title && SDL_strcmp(title, window->title) == 0) {
        परत true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    जर (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    परत true;
}

स्थिरांक अक्षर *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    परत window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        परत SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    जर (!window->icon) {
        परत false;
    }

    जर (!_this->SetWindowIcon) {
        परत SDL_Unsupported();
    }

    परत _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    स्थिरांक पूर्णांक w = window->last_size_pending ? window->pending.w : window->windowed.w;
    स्थिरांक पूर्णांक h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    जर (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    जर (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    जर (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        जर (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा जर (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        जर (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        जर (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            जर (!SDL_GetDisplayBounds(displayID, &bounds)) {
                परत false;
            }
        }
        जर (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        जर (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } अन्यथा {
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
    जर (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    जर (_this->SetWindowPosition) {
        स्थिरांक bool result = _this->SetWindowPosition(_this, window);
        जर (result) {
            SDL_SyncIfRequired(window);
        }
        परत result;
    }

    परत SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, पूर्णांक *x, पूर्णांक *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#अन्यथा
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    जर (use_display_origin) {
        SDL_DisplayID displayID;

        जर (x) {
            *x = 0;
        }
        जर (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        जर (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            जर (x) {
                *x = bounds.x;
            }
            जर (y) {
                *y = bounds.y;
            }
        }
    } अन्यथा {
        स्थिरांक bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        जर (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        जर (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    परत true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (!_this->SetWindowBordered) {
        परत SDL_Unsupported();
    }

    स्थिरांक bool want = bordered;
    स्थिरांक bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    जर (want != have) {
        जर (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } अन्यथा {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    परत true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (!_this->SetWindowResizable) {
        परत SDL_Unsupported();
    }

    स्थिरांक bool want = resizable;
    स्थिरांक bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    जर (want != have) {
        जर (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    परत true;
}

bool SDL_Set_Window_Always_On_शीर्ष(SDL_Window *window, bool on_शीर्ष)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (!_this->Set_Window_Always_On_शीर्ष) {
        परत SDL_Unsupported();
    }

    स्थिरांक bool want = on_शीर्ष;
    स्थिरांक bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) != 0);
    जर (want != have) {
        जर (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_शीर्ष;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_शीर्ष;
        }
        _this->Set_Window_Always_On_शीर्ष(_this, window, want);
    }

    परत true;
}

bool SDL_SetWindowSize(SDL_Window *window, पूर्णांक w, पूर्णांक h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        परत SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        परत SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    दशांश new_aspect = w / (दशांश)h;
    जर (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (पूर्णांक)SDL_roundf(h * window->max_aspect);
    } अन्यथा जर (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (पूर्णांक)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    जर (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    जर (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    जर (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    जर (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    जर (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } अन्यथा {
        परत SDL_Unsupported();
    }
    परत true;
}

bool SDL_GetWindowSize(SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    जर (w) {
        *w = window->w;
    }
    जर (h) {
        *h = window->h;
    }
    परत true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, दशांश min_aspect, दशांश max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    जर (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    पूर्णांक w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णांक h = window->last_size_pending ? window->pending.h : window->floating.h;
    परत SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, दशांश *min_aspect, दशांश *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    जर (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    परत true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, पूर्णांक *शीर्ष, पूर्णांक *डावा, पूर्णांक *bottom, पूर्णांक *उजवा)
{
    पूर्णांक dummy = 0;

    जर (!शीर्ष) {
        शीर्ष = &dummy;
    }
    जर (!डावा) {
        डावा = &dummy;
    }
    जर (!उजवा) {
        उजवा = &dummy;
    }
    जर (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *शीर्ष = *डावा = *bottom = *उजवा = 0;

    CHECK_WINDOW_MAGIC(window, false);

    जर (!_this->GetWindowBordersSize) {
        परत SDL_Unsupported();
    }

    परत _this->GetWindowBordersSize(_this, window, शीर्ष, डावा, bottom, उजवा);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    पूर्णांक filter;

    CHECK_WINDOW_MAGIC(window, false);

    जर (!w) {
        w = &filter;
    }

    जर (!h) {
        h = &filter;
    }

    जर (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } अन्यथा {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        स्थिरांक SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        जर ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } अन्यथा {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        जर (mode) {
            *w = (पूर्णांक)SDL_ceilf(*w * mode->pixel_density);
            *h = (पूर्णांक)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    परत true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, पूर्णांक min_w, पूर्णांक min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        परत SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        परत SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        परत SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    जर (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    पूर्णांक w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णांक h = window->last_size_pending ? window->pending.h : window->floating.h;
    परत SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, पूर्णांक *min_w, पूर्णांक *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    जर (min_w) {
        *min_w = window->min_w;
    }
    जर (min_h) {
        *min_h = window->min_h;
    }
    परत true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, पूर्णांक max_w, पूर्णांक max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        परत SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        परत SDL_InvalidParamError("max_h");
    }

    जर ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        परत SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    जर (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    पूर्णांक w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णांक h = window->last_size_pending ? window->pending.h : window->floating.h;
    परत SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, पूर्णांक *max_w, पूर्णांक *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    जर (max_w) {
        *max_w = window->max_w;
    }
    जर (max_h) {
        *max_h = window->max_h;
    }
    परत true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    जर (!(window->flags & SDL_WINDOW_HIDDEN)) {
        परत true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    जर (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        परत true;
    }

    जर (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } अन्यथा {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    साठी (child = window->first_child; child; child = child->next_sibling) {
        जर (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            थांबा;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    परत true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        परत true;
    }

    // Hide all child windows
    साठी (child = window->first_child; child; child = child->next_sibling) {
        जर (child->flags & SDL_WINDOW_HIDDEN) {
            थांबा;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    स्थिरांक SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    जर (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } अन्यथा {
        SDL_SetMouseFocus(रिक्त);
        SDL_SetKeyboardFocus(रिक्त);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    परत true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        परत true;
    }
    जर (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    परत true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (!_this->MaximizeWindow) {
        परत SDL_Unsupported();
    }

    जर (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        परत SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        परत true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    परत true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (!_this->MinimizeWindow) {
        परत SDL_Unsupported();
    }

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        परत true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    परत true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (!_this->RestoreWindow) {
        परत SDL_Unsupported();
    }

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        परत true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    परत true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        जर (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        परत true;
    }

    जर (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    जर (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    जर (result) {
        SDL_SyncIfRequired(window);
    }

    परत result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (_this->SyncWindow) {
        परत _this->SyncWindow(_this, window);
    } अन्यथा {
        परत true;
    }
}

स्थिर bool ShouldAttemptTextureFramebuffer(शून्य)
{
    स्थिरांक अक्षर *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    जर (!_this->CreateWindowFramebuffer) {
        परत true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    जर (hint && *hint) {
        जर (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } अन्यथा {
            attempt_texture_framebuffer = true;
        }
    } अन्यथा {
        जर (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } अन्यथा {
            attempt_texture_framebuffer = false;
        }
    }
    परत attempt_texture_framebuffer;
}

स्थिर SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    शून्य *pixels = रिक्त;
    पूर्णांक pitch = 0;
    bool created_framebuffer = false;
    पूर्णांक w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    जर (!_this->checked_texture_framebuffer) {
        जर (ShouldAttemptTextureFramebuffer()) {
            जर (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } अन्यथा {
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

    जर (!created_framebuffer) {
        जर (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            परत रिक्त;
        }

        जर (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            परत रिक्त;
        }
    }

    जर (window->surface) {
        // We may have gone recursive and already created the surface
        परत window->surface;
    }

    परत SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    परत window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    जर (!window->surface_valid) {
        जर (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = रिक्त;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        जर (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    परत window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, पूर्णांक vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (!_this->SetWindowFramebufferVSync) {
        परत SDL_Unsupported();
    }
    परत _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, पूर्णांक *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (!_this->GetWindowFramebufferVSync) {
        परत SDL_Unsupported();
    }
    परत _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    परत SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, स्थिरांक SDL_Rect *rects,
                                 पूर्णांक numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (!window->surface_valid) {
        परत SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    परत _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = रिक्त;
        window->surface_valid = false;
    }

    जर (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        जर (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    परत true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, दशांश opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    जर (!_this->SetWindowOpacity) {
        परत SDL_Unsupported();
    }

    जर (opacity < 0.0f) {
        opacity = 0.0f;
    } अन्यथा जर (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    जर (result) {
        window->opacity = opacity;
    }

    परत result;
}

दशांश SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    परत window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    जर (window == parent) {
        परत SDL_SetError("Cannot set the parent of a window to itself.");
    }

    जर (!_this->SetWindowParent) {
        परत SDL_Unsupported();
    }

    जर (window->flags & SDL_WINDOW_MODAL) {
        परत SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    जर (window->parent == parent) {
        परत true;
    }

    स्थिरांक bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : रिक्त);

    परत ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (!_this->SetWindowModal) {
        परत SDL_Unsupported();
    }

    जर (modal) {
        जर (!window->parent) {
            परत SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } अन्यथा जर (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } अन्यथा {
        परत true; // Already not modal, so nothing to do.
    }

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        परत true;
    }

    परत _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_आदान_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    पर्यंत (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        जर (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_आदान_FOCUS);
        }
    }

    *new_focus = focus;
    परत set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    साठी (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    साठी (w = current_focus; w != toplevel_parent; w = w->parent) {
        जर (w == window) {
            found_higher_focus = true;
            थांबा;
        }
    }

    परत !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    स्थिरांक bool want = (focusable != false); // normalize the flag.
    स्थिरांक bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    जर ((want != have) && (_this->SetWindowFocusable)) {
        जर (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } अन्यथा {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        जर (!_this->SetWindowFocusable(_this, window, want)) {
            परत false;
        }
    }

    परत true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    स्थिरांक bool want = (fill != false); // normalize the flag.
    स्थिरांक bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    जर ((want != have) && (_this->SetWindowFillDocument)) {
        जर (!_this->SetWindowFillDocument(_this, window, want)) {
            परत false;
        } अन्यथा जर (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    परत true;
}

शून्य SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    जर (window->flags & SDL_WINDOW_आदान_FOCUS) {
        जर (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } अन्यथा {
            mouse_grabbed = false;
        }

        जर (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } अन्यथा {
            keyboard_grabbed = false;
        }
    } अन्यथा {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    जर (mouse_grabbed || keyboard_grabbed) {
        जर (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            जर (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            जर (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } अन्यथा जर (_this->grabbed_window == window) {
        _this->grabbed_window = रिक्त; // ungrabbing input.
    }

    जर (_this->SetWindowMouseGrab) {
        जर (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    जर (_this->SetWindowKeyboardGrab) {
        जर (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    जर (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = रिक्त;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        जर (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        परत true;
    }

    जर (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        परत true;
    }
    जर (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    जर (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        परत false;
    }
    परत true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (window->flags & SDL_WINDOW_HIDDEN) {
        जर (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        परत true;
    }

    जर (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        परत true;
    }
    जर (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    जर (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        परत false;
    }
    परत true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    परत window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    परत window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(शून्य)
{
    जर (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        परत _this->grabbed_window;
    } अन्यथा {
        परत रिक्त;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, स्थिरांक SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (!_this->SetWindowMouseRect) {
        परत SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    जर (!rect) {
        rect = &zero;
    }

    जर (SDL_memcmp(&window->mouse_rect, rect, आकार(*rect)) == 0) {
        परत true;
    }
    SDL_memcpy(&window->mouse_rect, rect, आकार(*rect));

    परत _this->SetWindowMouseRect(_this, window);
}

स्थिरांक SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    जर (SDL_RectEmpty(&window->mouse_rect)) {
        परत रिक्त;
    } अन्यथा {
        परत &window->mouse_rect;
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

    जर (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        परत true;
    }

    जर (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    जर (!SDL_UpdateRelativeMouseMode()) {
        जर (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } अन्यथा {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        परत false;
    }
    परत true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        परत true;
    } अन्यथा {
        परत false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (_this->FlashWindow) {
        परत _this->FlashWindow(_this, window, operation);
    }

    परत SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        परत SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    जर (_this->ApplyWindowProgress) {
        जर (!_this->ApplyWindowProgress(_this, window)) {
            परत false;
        }
    }

    परत true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    परत window->progress_state;
}

bool SDL_Set_Window_Progress_मूल्य(SDL_Window *window, दशांश मूल्य)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    मूल्य = SDL_clamp(मूल्य, 0.0f, 1.f);

    window->progress_मूल्य = मूल्य;

    जर (_this->ApplyWindowProgress) {
        जर (!_this->ApplyWindowProgress(_this, window)) {
            परत false;
        }
    }

    परत true;
}

दशांश SDL_Get_Window_Progress_मूल्य(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    परत window->progress_मूल्य;
}

शून्य SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

शून्य SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

शून्य SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    जर (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        स्थिरांक bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        जर (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_वरचा_density_modes = false;

            जर (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_वरचा_density_modes = true;
            }
            स्थिरांक bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_वरचा_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            जर (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } अन्यथा {
            SDL_zero(window->current_fullscreen_mode);
        }

        जर (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

शून्य SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

शून्य SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    जर ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, रिक्त);
        जर (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

शून्य SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    पूर्णांक pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

शून्य SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

शून्य SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    जर (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } अन्यथा {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

स्थिर शून्य SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_डावा;
    rect.y = window->safe_inset_शीर्ष;
    rect.w = window->w - (window->safe_inset_उजवा + window->safe_inset_डावा);
    rect.h = window->h - (window->safe_inset_शीर्ष + window->safe_inset_bottom);
    जर (SDL_memcmp(&rect, &window->safe_rect, आकार(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

शून्य SDL_SetWindowSafeAreaInsets(SDL_Window *window, पूर्णांक डावा, पूर्णांक उजवा, पूर्णांक शीर्ष, पूर्णांक bottom)
{
    window->safe_inset_डावा = डावा;
    window->safe_inset_उजवा = उजवा;
    window->safe_inset_शीर्ष = शीर्ष;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    जर (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    जर (rect) {
        जर (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } अन्यथा {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    परत true;
}

शून्य SDL_OnWindowMinimized(SDL_Window *window)
{
    जर (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

शून्य SDL_OnWindowMaximized(SDL_Window *window)
{
}

शून्य SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    जर (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

शून्य SDL_OnWindowEnter(SDL_Window *window)
{
    जर (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

शून्य SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

शून्य SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    जर (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

स्थिर bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    स्थिरांक अक्षर *hint;

    जर (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        परत false;
    }

#जर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    जर (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        जर (Cocoa_IsShowingModalDialog(window)) {
            परत false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } अन्यथा जर (Cocoa_IsWindowInFullscreenSpace(window)) {
            परत false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        बाह्य bool Android_JNI_ShouldMinimizeOnFocusLoss(शून्य);
        जर (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            परत false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    जर (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        जर (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            परत true;
        } अन्यथा {
            परत false;
        }
    }
    परत SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

शून्य SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    जर (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(शून्य)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    जर (focus) {
        // Get the toplevel parent window.
        पर्यंत (focus->parent) {
            focus = focus->parent;
        }
    }

    परत focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->अंक_renderers + 1) * आकार(*renderers));
    जर (!renderers) {
        परत false;
    }

    window->renderers = renderers;
    window->renderers[window->अंक_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    परत true;
}

शून्य SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    साठी (पूर्णांक i = 0; i < window->अंक_renderers; ++i) {
        जर (window->renderers[i] == renderer) {
            जर (i < (window->अंक_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->अंक_renderers - i - 1) * आकार(window->renderers[i]));
            }
            --window->अंक_renderers;
            थांबा;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    जर (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, रिक्त) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

शून्य SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    पर्यंत (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    जर (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    जर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_आदान_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    जर (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    साठी (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
        जर (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = रिक्त;
        }
    }

    // Make sure this window no longer has focus
    जर (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(रिक्त);
    }
    जर ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    जर (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(रिक्त);
    }

    // Make no context current if this is the current context window
    जर (window->flags & SDL_WINDOW_OPENGL) {
        जर (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, रिक्त);
        }
    }

    जर (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    जर (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    जर (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    जर (_this->grabbed_window == window) {
        _this->grabbed_window = रिक्त; // ungrabbing input.
    }

    जर (_this->current_glwin == window) {
        _this->current_glwin = रिक्त;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, रिक्त);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, रिक्त);

    // Unlink the window from the global window list
    जर (window->next) {
        window->next->prev = window->prev;
    }
    जर (window->prev) {
        window->prev->next = window->next;
    } अन्यथा {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(शून्य)
{
    जर (!_this) {
        परत true;
    }
    परत !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(शून्य)
{
    जर (!_this) {
        परत SDL_UninitializedVideo();
    }
    जर (!_this->suspend_screensaver) {
        परत true;
    }
    _this->suspend_screensaver = false;
    जर (_this->SuspendScreenSaver) {
        परत _this->SuspendScreenSaver(_this);
    }

    परत SDL_Unsupported();
}

bool SDL_DisableScreenSaver(शून्य)
{
    जर (!_this) {
        परत SDL_UninitializedVideo();
    }
    जर (_this->suspend_screensaver) {
        परत true;
    }
    _this->suspend_screensaver = true;
    जर (_this->SuspendScreenSaver) {
        परत _this->SuspendScreenSaver(_this);
    }

    परत SDL_Unsupported();
}

शून्य SDL_QuitVideo(शून्य)
{
    पूर्णांक i;

    जर (!_this) {
        परत;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#जर 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    पर्यंत (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    जर (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    जर (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    साठी (i = _this->अंक_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->अंक_displays == 0);
    SDL_free(_this->displays);
    _this->displays = रिक्त;

    SDL_CancelClipboardData(0);

    जर (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = रिक्त;
    }
    _this->मुक्त(_this);
    _this = रिक्त;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(स्थिरांक अक्षर *path)
{
    bool result;

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }
    जर (_this->gl_config.driver_loaded) {
        जर (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            परत SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } अन्यथा {
        जर (!_this->GL_LoadLibrary) {
            परत SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    जर (result) {
        ++_this->gl_config.driver_loaded;
    } अन्यथा {
        जर (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    परत result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(स्थिरांक अक्षर *proc)
{
    SDL_FunctionPointer func;

    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    func = रिक्त;
    जर (_this->GL_GetProcAddress) {
        जर (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } अन्यथा {
            SDL_SetError("No GL driver has been loaded");
        }
    } अन्यथा {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    परत func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(स्थिरांक अक्षर *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    func = रिक्त;

    जर (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } अन्यथा {
        SDL_SetError("No EGL library has been loaded");
    }

    परत func;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    परत रिक्त;
#endif
}

शून्य SDL_GL_UnloadLibrary(शून्य)
{
    जर (!_this) {
        SDL_UninitializedVideo();
        परत;
    }
    जर (_this->gl_config.driver_loaded > 0) {
        जर (--_this->gl_config.driver_loaded > 0) {
            परत;
        }
        जर (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#जर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
प्रकारव्याख्या GLenum (APIENTRY* PFNGLGETERRORPROC) (शून्य);
प्रकारव्याख्या शून्य (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
प्रकारव्याख्या स्थिरांक GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
प्रकारव्याख्या शून्य (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
प्रकारव्याख्या स्थिरांक GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

स्थिर SDL_INLINE bool isAtLeastGL3(स्थिरांक अक्षर *verstr)
{
    परत verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(स्थिरांक अक्षर *extension)
{
#जर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    स्थिरांक अक्षर *extensions;
    स्थिरांक अक्षर *start;
    स्थिरांक अक्षर *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    जर (where || *extension == '\0') {
        परत false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    जर (start && *start == '0') {
        परत false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    जर (!glGetStringFunc) {
        परत false;
    }

    जर (isAtLeastGL3((स्थिरांक अक्षर *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint अंक_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        जर ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            परत false;
        }

#ifndef GL_अंक_EXTENSIONS
#define GL_अंक_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_अंक_EXTENSIONS, &अंक_exts);
        साठी (i = 0; i < अंक_exts; i++) {
            स्थिरांक अक्षर *thisext = (स्थिरांक अक्षर *)glGetStringiFunc(GL_EXTENSIONS, i);
            जर (SDL_strcmp(thisext, extension) == 0) {
                परत true;
            }
        }

        परत false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (स्थिरांक अक्षर *)glGetStringFunc(GL_EXTENSIONS);
    जर (!extensions) {
        परत false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    साठी (;;) {
        where = SDL_strstr(start, extension);
        जर (!where) {
            थांबा;
        }

        terminator = where + SDL_strlen(extension);
        जर (where == extensions || *(where - 1) == ' ') {
            जर (*terminator == ' ' || *terminator == '\0') {
                परत true;
            }
        }

        start = terminator;
    }
    परत false;
#अन्यथा
    परत false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
शून्य SDL_GL_DeduceMaxSupportedESProfile(पूर्णांक *major, पूर्णांक *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#जर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    जर (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } अन्यथा जर (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } अन्यथा जर (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } अन्यथा {
        *major = 2;
        *minor = 0;
    }
#endif
}

शून्य SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   शून्य *userdata)
{
    जर (!_this) {
        परत;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

शून्य SDL_GL_ResetAttributes(शून्य)
{
    जर (!_this) {
        परत;
    }

    _this->egl_platformattrib_callback = रिक्त;
    _this->egl_surfaceattrib_callback = रिक्त;
    _this->egl_contextattrib_callback = रिक्त;
    _this->egl_attrib_callback_userdata = रिक्त;

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
#किंवाजर defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#किंवाजर defined(SDL_VIDEO_OPENGL_ES)
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

    जर (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, पूर्णांक मूल्य)
{
#जर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }
    result = true;
    निवड (attr) {
    स्थिती SDL_GL_RED_SIZE:
        _this->gl_config.red_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = मूल्य;
        थांबा;
    स्थिती SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = मूल्य;
        थांबा;
    स्थिती SDL_GL_STEREO:
        _this->gl_config.stereo = मूल्य;
        थांबा;
    स्थिती SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = मूल्य;
        थांबा;
    स्थिती SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = मूल्य;
        थांबा;
    स्थिती SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = मूल्य;
        थांबा;
    स्थिती SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = मूल्य;
        थांबा;
    स्थिती SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = मूल्य;
        थांबा;
    स्थिती SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = मूल्य;
        थांबा;
    स्थिती SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = मूल्य;
        थांबा;
    स्थिती SDL_GL_CONTEXT_FLAGS:
        जर (मूल्य & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", मूल्य);
            थांबा;
        }
        _this->gl_config.flags = मूल्य;
        थांबा;
    स्थिती SDL_GL_CONTEXT_PROFILE_MASK:
        जर (मूल्य != 0 &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_CORE &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", मूल्य);
            थांबा;
        }
        _this->gl_config.profile_mask = मूल्य;
        थांबा;
    स्थिती SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = मूल्य;
        थांबा;
    स्थिती SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = मूल्य;
        थांबा;
    स्थिती SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = मूल्य;
        थांबा;
    स्थिती SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = मूल्य;
        थांबा;
    स्थिती SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = मूल्य;
        थांबा;
    स्थिती SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = मूल्य;
        थांबा;
    पूर्वनिर्धारित:
        result = SDL_SetError("Unknown OpenGL attribute");
        थांबा;
    }
    परत result;
#अन्यथा
    परत SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, पूर्णांक *मूल्य)
{
#जर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_डावा;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!मूल्य) {
        परत SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *मूल्य = 0;

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    निवड (attr) {
    स्थिती SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        थांबा;
    स्थिती SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        थांबा;
    स्थिती SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        थांबा;
    स्थिती SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        थांबा;
    स्थिती SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        थांबा;
#अन्यथा
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *मूल्य = _this->gl_config.double_buffer;
        परत true;
#endif
    स्थिती SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        थांबा;
    स्थिती SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        थांबा;
#ifdef SDL_VIDEO_OPENGL
    स्थिती SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        थांबा;
    स्थिती SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        थांबा;
    स्थिती SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        थांबा;
    स्थिती SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        थांबा;
    स्थिती SDL_GL_STEREO:
        attrib = GL_STEREO;
        थांबा;
#अन्यथा
    स्थिती SDL_GL_ACCUM_RED_SIZE:
    स्थिती SDL_GL_ACCUM_GREEN_SIZE:
    स्थिती SDL_GL_ACCUM_BLUE_SIZE:
    स्थिती SDL_GL_ACCUM_ALPHA_SIZE:
    स्थिती SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *मूल्य = 0;
        परत true;
#endif
    स्थिती SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        थांबा;
    स्थिती SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        थांबा;
    स्थिती SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        थांबा;
    स्थिती SDL_GL_BUFFER_SIZE:
    {
        पूर्णांक rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        जर (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            परत false;
        }
        जर (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            परत false;
        }
        जर (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            परत false;
        }
        जर (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            परत false;
        }

        *मूल्य = rsize + gsize + bsize + asize;
        परत true;
    }
    स्थिती SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *मूल्य = (_this->gl_config.accelerated != 0);
        परत true;
    }
    स्थिती SDL_GL_RETAINED_BACKING:
    {
        *मूल्य = _this->gl_config.retained_backing;
        परत true;
    }
    स्थिती SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *मूल्य = _this->gl_config.major_version;
        परत true;
    }
    स्थिती SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *मूल्य = _this->gl_config.minor_version;
        परत true;
    }
    स्थिती SDL_GL_CONTEXT_FLAGS:
    {
        *मूल्य = _this->gl_config.flags;
        परत true;
    }
    स्थिती SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *मूल्य = _this->gl_config.profile_mask;
        परत true;
    }
    स्थिती SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *मूल्य = _this->gl_config.share_with_current_context;
        परत true;
    }
    स्थिती SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *मूल्य = _this->gl_config.framebuffer_srgb_capable;
        परत true;
    }
    स्थिती SDL_GL_CONTEXT_NO_ERROR:
    {
        *मूल्य = _this->gl_config.no_error;
        परत true;
    }
    स्थिती SDL_GL_EGL_PLATFORM:
    {
        *मूल्य = _this->gl_config.egl_platform;
        परत true;
    }
    स्थिती SDL_GL_FLOATBUFFERS:
    {
        जर (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            थांबा;
        } अन्यथा {
            परत 0;
        }
    }
    पूर्वनिर्धारित:
        परत SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    जर (!glGetStringFunc) {
        परत false;
    }

    जर (attachmentattrib && isAtLeastGL3((स्थिरांक अक्षर *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        जर (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        जर (glGetFramebufferAttachmentParameterivFunc) {
            जर (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            जर (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            जर (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)मूल्य);
            } अन्यथा {
                *मूल्य = 0;
            }
            जर (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } अन्यथा {
            परत false;
        }
    } अन्यथा
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        जर (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)मूल्य);
        } अन्यथा {
            परत false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    जर (!glGetErrorFunc) {
        परत false;
    }

    error = glGetErrorFunc();
    जर (error != GL_NO_ERROR) {
        जर (error == GL_INVALID_ENUM) {
            परत SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } अन्यथा जर (error == GL_INVALID_मूल्य) {
            परत SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        परत SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    जर (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *मूल्य = (*मूल्य == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    परत true;
#अन्यथा
    परत SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = रिक्त;
    CHECK_WINDOW_MAGIC(window, रिक्त);

    जर (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        परत रिक्त;
    }

#जर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    पूर्णांक srgb_requested = -1;
    स्थिरांक अक्षर *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    जर (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    जर (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, रिक्त);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, रिक्त);
    }

#जर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    जर (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        जर (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            जर (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } अन्यथा {
                supported = isAtLeastGL3((स्थिरांक अक्षर *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            जर (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    परत ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }

    जर (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        परत true;
    }

    जर (!context) {
        window = रिक्त;
    } अन्यथा जर (window) {
        CHECK_WINDOW_MAGIC(window, false);

        जर (!(window->flags & SDL_WINDOW_OPENGL)) {
            परत SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } अन्यथा जर (!_this->gl_allow_no_surface) {
        परत SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    जर (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, रिक्त);
        SDL_SetTLS(&_this->current_glctx_tls, context, रिक्त);
    }
    परत result;
}

SDL_Window *SDL_GL_GetCurrentWindow(शून्य)
{
    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    परत (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(शून्य)
{
    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    परत (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    जर (!_this) {
        SDL_UninitializedVideo();
        परत EGL_NO_DISPLAY;
    }
    जर (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        परत EGL_NO_DISPLAY;
    }
    परत _this->egl_data->egl_display;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    परत रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    जर (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        परत रिक्त;
    }
    परत _this->egl_data->egl_config;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    परत रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    जर (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        परत रिक्त;
    }
    जर (_this->GL_GetEGLSurface) {
        परत _this->GL_GetEGLSurface(_this, window);
    }
    परत रिक्त;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    परत रिक्त;
#endif
}

bool SDL_GL_SetSwapInterval(पूर्णांक interval)
{
    जर (!_this) {
        परत SDL_UninitializedVideo();
    } अन्यथा जर (SDL_GL_GetCurrentContext() == रिक्त) {
        परत SDL_SetError("No OpenGL context has been made current");
    } अन्यथा जर (_this->GL_SetSwapInterval) {
        परत _this->GL_SetSwapInterval(_this, interval);
    } अन्यथा {
        परत SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(पूर्णांक *interval)
{
    CHECK_PARAM(!interval) {
       परत SDL_InvalidParamError("interval");
    }

    *interval = 0;

    जर (!_this) {
        परत SDL_SetError("no video driver");
    } अन्यथा जर (SDL_GL_GetCurrentContext() == रिक्त) {
        परत SDL_SetError("no current context");
    } अन्यथा जर (_this->GL_GetSwapInterval) {
        परत _this->GL_GetSwapInterval(_this, interval);
    } अन्यथा {
        परत SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (!(window->flags & SDL_WINDOW_OPENGL)) {
        परत SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    जर (SDL_GL_GetCurrentWindow() != window) {
        परत SDL_SetError("The specified window has not been made current");
    }

    परत _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        परत SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        परत SDL_InvalidParamError("context");
    }

    जर (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(रिक्त, रिक्त);
    }

    परत _this->GL_DestroyContext(_this, context);
}

#जर 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
स्थिर शून्य Create_Mask_From_Color_किल्ली_Or_Alpha(SDL_Surface *icon, Uint8 *mask, पूर्णांक flags)
{
    पूर्णांक x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    निवड (SDL_BYTESPERPIXEL(icon->format)) {
    स्थिती 1:
        {
            Uint8 *pixels;
            साठी (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                साठी (x = 0; x < icon->w; ++x) {
                    जर (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        थांबा;

    स्थिती 2:
        {
            Uint16 *pixels;
            साठी (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                साठी (x = 0; x < icon->w; ++x) {
                    जर ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अन्यथा जर ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        थांबा;

    स्थिती 4:
        {
            Uint32 *pixels;
            साठी (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                साठी (x = 0; x < icon->w; ++x) {
                    जर ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अन्यथा जर ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        थांबा;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
शून्य SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    जर (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        जर (mask == रिक्त) {
            पूर्णांक mask_len = icon->h * (icon->w + 7) / 8;
            पूर्णांक flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            जर (mask == रिक्त) {
                परत;
            }
            SDL_memset(mask, ~0, mask_len);
            जर (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            जर (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            जर (flags) {
                Create_Mask_From_Color_किल्ली_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } अन्यथा {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_आदान_Type SDL_Get_Text_आदान_Type(SDL_PropertiesID props)
{
    परत (SDL_Text_आदान_Type)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_TYPE_संख्या, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_आदान_Capitalization(SDL_PropertiesID props)
{
    जर (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_संख्या)) {
        परत (SDL_Capitalization)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_संख्या, SDL_CAPITALIZE_NONE);
    }

    निवड (SDL_Get_Text_आदान_Type(props)) {
    स्थिती SDL_TEXTINPUT_TYPE_TEXT:
        परत SDL_CAPITALIZE_SENTENCES;
    स्थिती SDL_TEXTINPUT_TYPE_TEXT_NAME:
        परत SDL_CAPITALIZE_शब्द;
    पूर्वनिर्धारित:
        परत SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_आदान_Autocorrect(SDL_PropertiesID props)
{
    परत SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_आदान_Multiline(SDL_PropertiesID props)
{
    जर (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        परत SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    जर (SDL_GetHintBoolean(SDL_HINT_RETURN_किल्ली_HIDES_IME, false)) {
        परत false;
    } अन्यथा {
        परत true;
    }
}

स्थिर bool AutoShowingScreenKeyboard(शून्य)
{
    स्थिरांक अक्षर *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    जर (!hint) {
        // This hint is currently only used by the X11 video driver
        जर (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    जर (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        परत true;
    } अन्यथा {
        परत false;
    }
}

bool SDL_Start_Text_आदान(SDL_Window *window)
{
    परत SDL_Start_Text_आदान_With_Properties(window, 0);
}

bool SDL_Start_Text_आदान_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (window->text_आदान_props) {
        SDL_DestroyProperties(window->text_आदान_props);
        window->text_आदान_props = 0;
    }

    जर (props) {
        window->text_आदान_props = SDL_CreateProperties();
        जर (!window->text_आदान_props) {
            परत false;
        }
        जर (!SDL_CopyProperties(props, window->text_आदान_props)) {
            परत false;
        }
    }

    जर (_this->Set_Text_आदान_Properties) {
        _this->Set_Text_आदान_Properties(_this, window, props);
    }

    जर (!window->text_आदान_active) {
        // Start the text input system
        जर (_this->Start_Text_आदान) {
            जर (!_this->Start_Text_आदान(_this, window, props)) {
                परत false;
            }
        }
        window->text_आदान_active = true;
    }

    // Show the on-screen keyboard, if desired
    जर (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        जर (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    परत true;
}

bool SDL_Text_आदान_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    परत window->text_आदान_active;
}

bool SDL_Stop_Text_आदान(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (window->text_आदान_active) {
        // Stop the text input system
        जर (_this->Stop_Text_आदान) {
            _this->Stop_Text_आदान(_this, window);
        }
        window->text_आदान_active = false;
    }

    // Hide the on-screen keyboard, if desired
    जर (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        जर (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    परत true;
}

bool SDL_Set_Text_आदान_Area(SDL_Window *window, स्थिरांक SDL_Rect *rect, पूर्णांक cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (rect) {
        SDL_copyp(&window->text_आदान_rect, rect);
        window->text_आदान_cursor = cursor;
    } अन्यथा {
        SDL_zero(window->text_आदान_rect);
        window->text_आदान_cursor = 0;
    }

    जर (_this && _this->Update_Text_आदान_Area) {
        जर (!_this->Update_Text_आदान_Area(_this, window)) {
            परत false;
        }
    }
    परत true;
}

bool SDL_Get_Text_आदान_Area(SDL_Window *window, SDL_Rect *rect, पूर्णांक *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (rect) {
        SDL_copyp(rect, &window->text_आदान_rect);
    }
    जर (cursor) {
        *cursor = window->text_आदान_cursor;
    }
    परत true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (_this->ClearComposition) {
        परत _this->ClearComposition(_this, window);
    }
    परत true;
}

bool SDL_HasScreenKeyboardSupport(शून्य)
{
    जर (_this && _this->HasScreenKeyboardSupport) {
        परत _this->HasScreenKeyboardSupport(_this);
    }
    परत false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    परत _this->screen_keyboard_shown;
}

शून्य SDL_SendScreenKeyboardShown(शून्य)
{
    जर (!_this || _this->screen_keyboard_shown) {
        परत;
    }

    _this->screen_keyboard_shown = true;

    जर (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ढकला_Event(&event);
    }
}

शून्य SDL_SendScreenKeyboardHidden(शून्य)
{
    जर (!_this || !_this->screen_keyboard_shown) {
        परत;
    }

    _this->screen_keyboard_shown = false;

    जर (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ढकला_Event(&event);
    }
}

पूर्णांक SDL_Get_Message_Box_मोजणी(शून्य)
{
    परत SDL_GetAtomicInt(&SDL_messagebox_मोजणी);
}

bool SDL_ShowMessageBox(स्थिरांक SDL_MessageBoxData *messageboxdata, पूर्णांक *buttonID)
{
    पूर्णांक dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        परत SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        परत SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    अक्षर *titlecpy = रिक्त;
    अक्षर *msgcpy = रिक्त;
    जर (messageboxdata->title) {
        स्थिरांक माप_प्रकार slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(अक्षर, slen, &titleisstack);
        जर (!titlecpy) {
            परत false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    जर (messageboxdata->message) {
        स्थिरांक माप_प्रकार slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(अक्षर, slen, &msgisstack);
        जर (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            परत false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (शून्य)SDL_AtomicIncRef(&SDL_messagebox_मोजणी);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    जर (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, आकार(*messageboxdata));
    mbdata.title = titlecpy;
    जर (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    जर (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    जर (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } अन्यथा {
        // It's completely fine to call this function before video is initialized
        स्थिरांक अक्षर *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        जर (driver_name && *driver_name != 0) {
            स्थिरांक अक्षर *driver_attempt = driver_name;
            पर्यंत (driver_attempt && (*driver_attempt != 0) && !result) {
                स्थिरांक अक्षर *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                साठी (पूर्णांक i = 0; bootstrap[i]; ++i) {
                    जर (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        जर (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        थांबा;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
            }
        } अन्यथा {
            साठी (पूर्णांक i = 0; bootstrap[i]; ++i) {
                जर (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    थांबा;
                }
            }
        }
    }

    जर (!result) {
        स्थिरांक अक्षर *error = SDL_GetError();

        जर (!*error) {
            SDL_SetError("No message system available");
        }
    } अन्यथा {
        SDL_ClearError();
    }

    (शून्य)SDL_AtomicDecRef(&SDL_messagebox_मोजणी);

    जर (current_window) {
        SDL_RaiseWindow(current_window);
    }

    जर (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    परत result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, स्थिरांक अक्षर *title, स्थिरांक अक्षर *message, SDL_Window *window)
{
#जर defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_उजवा;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_उजवा = gsp_Has_Gpu_उजवा();
    जर (!has_Gpu_उजवा)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    जर (!has_Gpu_उजवा)
        gfxExit();

    परत true;
#अन्यथा
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

    परत SDL_ShowMessageBox(&data, रिक्त);
#endif
}

bool SDL_ShouldAllowTopmost(शून्य)
{
    परत SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    जर (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        परत true;
    }

    परत SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, शून्य *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (!_this->SetWindowHitTest) {
        परत SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    परत _this->SetWindowHitTest(window, callback != रिक्त);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    जर (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        परत SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    जर (!props) {
        परत false;
    }

    जर (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        जर (!surface) {
            परत false;
        }
    } अन्यथा {
        surface = रिक्त;
    }

    जर (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        परत false;
    }

    जर (_this->UpdateWindowShape) {
        जर (!_this->UpdateWindowShape(_this, window, surface)) {
            परत false;
        }
    }
    परत true;
}

/*
 * Functions used by iOS application delegates
 */
शून्य SDL_OnApplicationWillTerminate(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

शून्य SDL_OnApplicationDidReceiveMemoryWarning(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_खालचा_MEMORY);
}

शून्य SDL_OnApplicationWillEnterBackground(शून्य)
{
    जर (_this) {
        SDL_Window *window;
        साठी (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(रिक्त);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

शून्य SDL_OnApplicationDidEnterBackground(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

शून्य SDL_OnApplicationWillEnterForeground(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

शून्य SDL_OnApplicationDidEnterForeground(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    जर (_this) {
        SDL_Window *window;
        साठी (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(स्थिरांक अक्षर *path)
{
    bool result;

    जर (!_this) {
        परत SDL_UninitializedVideo();
    }
    जर (_this->vulkan_config.loader_loaded) {
        जर (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            परत SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } अन्यथा {
        जर (!_this->Vulkan_LoadLibrary) {
            परत SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    जर (result) {
        _this->vulkan_config.loader_loaded++;
    }
    परत result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(शून्य)
{
    जर (!_this) {
        SDL_UninitializedVideo();
        परत रिक्त;
    }
    जर (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        परत रिक्त;
    }
    परत (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

शून्य SDL_Vulkan_UnloadLibrary(शून्य)
{
    जर (!_this) {
        SDL_UninitializedVideo();
        परत;
    }
    जर (_this->vulkan_config.loader_loaded > 0) {
        जर (--_this->vulkan_config.loader_loaded > 0) {
            परत;
        }
        जर (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

अक्षर स्थिरांक * स्थिरांक *SDL_Vulkan_GetInstanceExtensions(Uint32 *मोजणी)
{
    Uint32 tmpcount = 0;
    जर (!मोजणी) {
        मोजणी = &tmpcount;
    }

    जर (!_this->Vulkan_GetInstanceExtensions) {
        *मोजणी = 0;
        SDL_Unsupported();
        परत रिक्त;
    }

    परत _this->Vulkan_GetInstanceExtensions(_this, मोजणी);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  स्थिरांक संरचना VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    जर (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        परत false;
    }

    CHECK_PARAM(!instance) {
        परत SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        परत SDL_InvalidParamError("surface");
    }

    जर (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        जर (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        जर (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        जर (SDL_Vulkan_LoadLibrary(रिक्त)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } अन्यथा {
            परत SDL_SetError("failed to load Vulkan library");
        }
    }

    परत _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

शून्य SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               स्थिरांक संरचना VkAllocationCallbacks *allocator)
{
    जर (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        परत false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        परत false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        परत false;
    }

    जर (_this->Vulkan_GetPresentationSupport) {
        परत _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    परत true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    जर (!_this->Metal_CreateView) {
        SDL_Unsupported();
        परत रिक्त;
    }

    जर (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        जर (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        जर (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    परत _this->Metal_CreateView(_this, window);
}

शून्य SDL_Metal_DestroyView(SDL_MetalView view)
{
    जर (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

शून्य *SDL_Metal_GetLayer(SDL_MetalView view)
{
    जर (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            परत रिक्त;
        }
        परत _this->Metal_GetLayer(_this, view);
    } अन्यथा {
        SDL_SetError("Metal is not supported.");
        परत रिक्त;
    }
}

#जर defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
स्थिरांक अक्षर *SDL_GetCSSCursorName(SDL_SystemCursor id, स्थिरांक अक्षर **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    निवड (id) {
    स्थिती SDL_SYSTEM_CURSOR_DEFAULT:
        परत "default";

    स्थिती SDL_SYSTEM_CURSOR_TEXT:
        परत "text";

    स्थिती SDL_SYSTEM_CURSOR_WAIT:
        परत "wait";

    स्थिती SDL_SYSTEM_CURSOR_CROSSHAIR:
        परत "crosshair";

    स्थिती SDL_SYSTEM_CURSOR_PROGRESS:
        परत "progress";

    स्थिती SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        जर (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        परत "nwse-resize";

    स्थिती SDL_SYSTEM_CURSOR_NESW_RESIZE:
        जर (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        परत "nesw-resize";

    स्थिती SDL_SYSTEM_CURSOR_EW_RESIZE:
        जर (fallback_name) {
            *fallback_name = "col-resize";
        }
        परत "ew-resize";

    स्थिती SDL_SYSTEM_CURSOR_NS_RESIZE:
        जर (fallback_name) {
            *fallback_name = "row-resize";
        }
        परत "ns-resize";

    स्थिती SDL_SYSTEM_CURSOR_MOVE:
        जर (fallback_name) {
            *fallback_name = "all-scroll";
        }
        परत "move";

    स्थिती SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        परत "not-allowed";

    स्थिती SDL_SYSTEM_CURSOR_POINTER:
        परत "pointer";

    स्थिती SDL_SYSTEM_CURSOR_NW_RESIZE:
        परत "nw-resize";

    स्थिती SDL_SYSTEM_CURSOR_N_RESIZE:
        परत "n-resize";

    स्थिती SDL_SYSTEM_CURSOR_NE_RESIZE:
        परत "ne-resize";

    स्थिती SDL_SYSTEM_CURSOR_E_RESIZE:
        परत "e-resize";

    स्थिती SDL_SYSTEM_CURSOR_SE_RESIZE:
        परत "se-resize";

    स्थिती SDL_SYSTEM_CURSOR_S_RESIZE:
        परत "s-resize";

    स्थिती SDL_SYSTEM_CURSOR_SW_RESIZE:
        परत "sw-resize";

    स्थिती SDL_SYSTEM_CURSOR_W_RESIZE:
        परत "w-resize";

    स्थिती SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        परत "context-menu";

    स्थिती SDL_SYSTEM_CURSOR_HELP:
        परत "help";

    स्थिती SDL_SYSTEM_CURSOR_CELL:
        परत "cell";

    स्थिती SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        परत "vertical-text";

    स्थिती SDL_SYSTEM_CURSOR_ALIAS:
        परत "alias";

    स्थिती SDL_SYSTEM_CURSOR_COPY:
        परत "copy";

    स्थिती SDL_SYSTEM_CURSOR_NO_DROP:
        परत "no-drop";

    स्थिती SDL_SYSTEM_CURSOR_GRAB:
        परत "grab";

    स्थिती SDL_SYSTEM_CURSOR_GRABBING:
        परत "grabbing";

    स्थिती SDL_SYSTEM_CURSOR_COL_RESIZE:
        परत "col-resize";

    स्थिती SDL_SYSTEM_CURSOR_ROW_RESIZE:
        परत "row-resize";

    स्थिती SDL_SYSTEM_CURSOR_ALL_SCROLL:
        जर (fallback_name) {
            *fallback_name = "move";
        }
        परत "all-scroll";

    स्थिती SDL_SYSTEM_CURSOR_ZOOM_IN:
        परत "zoom-in";

    स्थिती SDL_SYSTEM_CURSOR_ZOOM_OUT:
        परत "zoom-out";

    पूर्वनिर्धारित:
        परत "default";
    }
}
#endif

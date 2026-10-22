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

#यदि defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#अन्तर्भाव <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#यदि defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
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
#ifdef SDL_आगत_LINUXEV
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
        फर्काऊ result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        फर्काऊ result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        फर्काऊ result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        फर्काऊ result;                                                  \
    }

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
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
    यदि (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        फर्काऊ true;
    }
    फर्काऊ false;
}

स्थिर bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    फर्काऊ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

स्थिर bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    फर्काऊ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

स्थिर bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    फर्काऊ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

स्थिर bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    फर्काऊ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

स्थिर bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    फर्काऊ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
स्थिर bool syncHint;

स्थिर शून्य SDL_SyncHintWatcher(शून्य *userdata, अचर वर्ण *name, अचर वर्ण *old_मान, अचर वर्ण *new_मान)
{
    syncHint = SDL_GetStringBoolean(new_मान, false);
}

स्थिर शून्य SDL_SyncIfRequired(SDL_Window *window)
{
    यदि (syncHint) {
        SDL_SyncWindow(window);
    }
}

स्थिर शून्य SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    यदि (window->parent) {
        यदि (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        यदि (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } अन्यथा {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = रिक्त;
    }

    यदि (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        यदि (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

प्रकारनिर्देश संरचना
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    शून्य *pixels;
    पूर्णाङ्क pitch;
    पूर्णाङ्क bytes_per_pixel;
} SDL_WindowTextureData;

स्थिर Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#यदि (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    यदि (_this->GL_CreateContext) {
        फर्काऊ SDL_WINDOW_OPENGL;
    }
#endif
#यदि defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    यदि (_this->Metal_CreateView) {
        फर्काऊ SDL_WINDOW_METAL;
    }
#endif
#यदि defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    यदि (SDL_strcmp(_this->name, "openvr") == 0) {
        फर्काऊ SDL_WINDOW_OPENGL;
    }
#endif
    फर्काऊ 0;
}

स्थिर bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    अचर bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    पूर्णाङ्क i;
    पूर्णाङ्क w, h;
    अचर SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    यदि (!data) {
        SDL_Renderer *renderer = रिक्त;
        अचर वर्ण *render_driver = रिक्त;

        // See if there's a render driver being requested
        अचर वर्ण *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        यदि (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        यदि (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        यदि (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = रिक्त;
        }

        वर्ण *render_driver_copy = रिक्त;
        यदि (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            यदि (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                वर्ण *prev = render_driver_copy;
                वर्ण *ptr = prev;
                जबसम्म ((ptr = SDL_strchr(ptr, ',')) != रिक्त) {
                    *ptr = '\0';
                    अचर bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    यदि (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } अन्यथा {
                        ptr++;
                        prev = ptr;
                    }
                }

                यदि (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        यदि (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            यदि (!renderer) {
                // The error for this specific renderer has already been set
                फर्काऊ false;
            }
        } अन्यथा {
            SDL_assert(render_driver_copy == रिक्त);
            अचर पूर्णाङ्क total = SDL_Get_अङ्क_Render_Drivers();
            लागि (i = 0; i < total; ++i) {
                अचर वर्ण *name = SDL_GetRenderDriver(i);
                यदि (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    यदि (renderer) {
                        रोक; // this will work.
                    }
                }
            }
            यदि (!renderer) {
                फर्काऊ SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != रिक्त); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, परिमाण(*data));
        यदि (!data) {
            SDL_DestroyRenderer(renderer);
            फर्काऊ false;
        }
        यदि (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            फर्काऊ false;
        }

        data->renderer = renderer;
    }

    texture_formats = (अचर SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, रिक्त);
    यदि (!texture_formats) {
        फर्काऊ false;
    }

    // Free any old texture and pixel data
    यदि (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = रिक्त;
    }
    SDL_free(data->pixels);
    data->pixels = रिक्त;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    लागि (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        यदि (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            रोक;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    यदि (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        फर्काऊ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        अचर माप_प्रकार allocsize = (माप_प्रकार)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        यदि (!data->pixels) {
            फर्काऊ false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, रिक्त);

    फर्काऊ true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    यदि (!data) {
        फर्काऊ false;
    }
    यदि (!data->renderer) {
        फर्काऊ false;
    }
    फर्काऊ SDL_SetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    यदि (!data) {
        फर्काऊ false;
    }
    यदि (!data->renderer) {
        फर्काऊ false;
    }
    फर्काऊ SDL_GetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, अचर SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    शून्य *src;
    पूर्णाङ्क w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    यदि (!data || !data->texture) {
        फर्काऊ SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    यदि (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (शून्य *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        यदि (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            फर्काऊ false;
        }

        यदि (!SDL_RenderTexture(data->renderer, data->texture, रिक्त, रिक्त)) {
            फर्काऊ false;
        }

        SDL_RenderPresent(data->renderer);
    }
    फर्काऊ true;
}

स्थिर शून्य SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    यदि (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);

        यदि (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        यदि (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

स्थिर SDL_VideoDevice *_this = रिक्त;
स्थिर SDL_AtomicInt SDL_messagebox_गन्ती;

स्थिर पूर्णाङ्क SDLCALL cmpmodes(अचर शून्य *A, अचर शून्य *B)
{
    अचर SDL_DisplayMode *a = (अचर SDL_DisplayMode *)A;
    अचर SDL_DisplayMode *b = (अचर SDL_DisplayMode *)B;
    पूर्णाङ्क a_refresh_rate = (पूर्णाङ्क)(a->refresh_rate * 100);
    पूर्णाङ्क b_refresh_rate = (पूर्णाङ्क)(b->refresh_rate * 100);
    पूर्णाङ्क a_pixel_density = (पूर्णाङ्क)(a->pixel_density * 100);
    पूर्णाङ्क b_pixel_density = (पूर्णाङ्क)(b->pixel_density * 100);

    यदि (a->w != b->w) {
        फर्काऊ b->w - a->w;
    } अन्यथा यदि (a->h != b->h) {
        फर्काऊ b->h - a->h;
    } अन्यथा यदि (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        फर्काऊ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } अन्यथा यदि (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        फर्काऊ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } अन्यथा यदि (a_refresh_rate != b_refresh_rate) {
        फर्काऊ b_refresh_rate - a_refresh_rate;
    } अन्यथा यदि (a_pixel_density != b_pixel_density) {
        फर्काऊ a_pixel_density - b_pixel_density;
    }
    फर्काऊ 0;
}

bool SDL_UninitializedVideo(शून्य)
{
    फर्काऊ SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
स्थिर अचर VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

पूर्णाङ्क SDL_Get_अङ्क_Video_Drivers(शून्य)
{
    स्थिर पूर्णाङ्क अङ्क_drivers = -1;

    यदि (अङ्क_drivers >= 0) {
        फर्काऊ अङ्क_drivers;
    }

    अङ्क_drivers = 0;

    // Build a list of unique video drivers.
    लागि (पूर्णाङ्क i = 0; bootstrap[i] != रिक्त; ++i) {
        bool duplicate = false;
        लागि (पूर्णाङ्क j = 0; j < i; ++j) {
            यदि (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                रोक;
            }
        }

        यदि (!duplicate) {
            deduped_bootstrap[अङ्क_drivers++] = bootstrap[i];
        }
    }

    फर्काऊ अङ्क_drivers;
}

अचर वर्ण *SDL_GetVideoDriver(पूर्णाङ्क index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_अङ्क_Video_Drivers()) {
        SDL_InvalidParamError("index");
        फर्काऊ रिक्त;
    }
    फर्काऊ deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(अचर वर्ण *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    पूर्णाङ्क i = 0;

    // Check to make sure we don't overwrite '_this'
    यदि (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    यदि (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        गच्छ pre_driver_error;
    }
    init_events = true;
    यदि (!SDL_InitKeyboard()) {
        गच्छ pre_driver_error;
    }
    init_keyboard = true;
    यदि (!SDL_PreInitMouse()) {
        गच्छ pre_driver_error;
    }
    init_mouse = true;
    यदि (!SDL_InitTouch()) {
        गच्छ pre_driver_error;
    }
    init_touch = true;
    यदि (!SDL_InitPen()) {
        गच्छ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = रिक्त;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    यदि (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    यदि (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    यदि (driver_name && *driver_name != 0) {
        अचर वर्ण *driver_attempt = driver_name;
        जबसम्म (driver_attempt && *driver_attempt != 0 && !video) {
            अचर वर्ण *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            लागि (i = 0; bootstrap[i]; ++i) {
                यदि (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    यदि (video) {
                        रोक;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
        }
    } अन्यथा {
        लागि (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            यदि (video) {
                रोक;
            }
        }
    }
    यदि (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } अन्यथा {
        यदि (driver_name) {
            SDL_SetError("%s not available", driver_name);
            गच्छ pre_driver_error;
        }
        SDL_SetError("No available video device");
        गच्छ pre_driver_error;
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
    यदि (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        फर्काऊ false;
    }

    // Make sure some displays were added
    यदि (_this->अङ्क_displays == 0) {
        SDL_QuitVideo();
        फर्काऊ SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, रिक्त);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    यदि (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    फर्काऊ true;

pre_driver_error:
    SDL_assert(_this == रिक्त);
    यदि (init_pen) {
        SDL_QuitPen();
    }
    यदि (init_touch) {
        SDL_QuitTouch();
    }
    यदि (init_mouse) {
        SDL_QuitMouse();
    }
    यदि (init_keyboard) {
        SDL_QuitKeyboard();
    }
    यदि (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    फर्काऊ false;
}

अचर वर्ण *SDL_GetCurrentVideoDriver(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    फर्काऊ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(शून्य)
{
    फर्काऊ _this;
}

bool SDL_OnVideoThread(शून्य)
{
    फर्काऊ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

शून्य SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    यदि (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(शून्य)
{
    यदि (_this) {
        फर्काऊ _this->system_theme;
    } अन्यथा {
        फर्काऊ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

शून्य SDL_UpdateDesktopBounds(शून्य)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    यदि (displays) {
        लागि (पूर्णाङ्क i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            यदि (SDL_GetDisplayBounds(displays[i], &bounds)) {
                यदि (i == 0) {
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
    यदि (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    यदि (mode->refresh_rate_numerator > 0) {
        यदि (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (भिन्न)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } अन्यथा {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(अचर SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    यदि (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, परिमाण(display.desktop_mode));
    }
    फर्काऊ SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(अचर SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    पूर्णाङ्क i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(परिमाण(*new_display));
    यदि (!new_display) {
        फर्काऊ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->अङ्क_displays + 1) * परिमाण(*displays));
    यदि (!displays) {
        SDL_free(new_display);
        फर्काऊ 0;
    }
    _this->displays = displays;
    _this->displays[_this->अङ्क_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    यदि (display->name) {
        new_display->name = SDL_strdup(display->name);
    } अन्यथा {
        वर्ण name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    यदि (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    लागि (i = 0; i < new_display->अङ्क_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    यदि (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    फर्काऊ id;
}

शून्य SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    लागि (window = _this->windows; window; window = window->next) {
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
    पूर्णाङ्क display_index = SDL_GetDisplayIndex(displayID);
    यदि (display_index < 0) {
        फर्काऊ;
    }

    display = _this->displays[display_index];

    यदि (send_event) {
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

    यदि (display_index < (_this->अङ्क_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->अङ्क_displays - display_index - 1) * परिमाण(_this->displays[display_index]));
    }
    --_this->अङ्क_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(पूर्णाङ्क *गन्ती)
{
    पूर्णाङ्क i;
    SDL_DisplayID *displays;

    यदि (!_this) {
        यदि (गन्ती) {
            *गन्ती = 0;
        }

        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->अङ्क_displays + 1) * परिमाण(*displays));
    यदि (displays) {
        यदि (गन्ती) {
            *गन्ती = _this->अङ्क_displays;
        }

        लागि (i = 0; i < _this->अङ्क_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } अन्यथा {
        यदि (गन्ती) {
            *गन्ती = 0;
        }
    }
    फर्काऊ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    यदि (display_index < 0) {
        फर्काऊ रिक्त;
    }
    फर्काऊ _this->displays[display_index];
}

स्थिर SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    यदि (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    फर्काऊ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    फर्काऊ SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(शून्य)
{
    यदि (!_this || _this->अङ्क_displays == 0) {
        SDL_UninitializedVideo();
        फर्काऊ 0;
    }
    फर्काऊ _this->displays[0]->id;
}

पूर्णाङ्क SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_index;

    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ -1;
    }

    लागि (display_index = 0; display_index < _this->अङ्क_displays; ++display_index) {
        यदि (displayID == _this->displays[display_index]->id) {
            फर्काऊ display_index;
        }
    }
    SDL_SetError("Invalid display");
    फर्काऊ -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    फर्काऊ display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    फर्काऊ SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    यदि (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    फर्काऊ display->props;
}

अचर वर्ण *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    फर्काऊ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        फर्काऊ SDL_InvalidParamError("rect");
    }

    यदि (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        यदि (_this->GetDisplayBounds(_this, display, rect)) {
            फर्काऊ true;
        }
    }

    // Assume that the displays are left to right
    यदि (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } अन्यथा {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    फर्काऊ true;
}

स्थिर पूर्णाङ्क ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    अचर वर्ण *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    फर्काऊ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        फर्काऊ SDL_InvalidParamError("rect");
    }

    यदि (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        फर्काऊ true;
    }

    यदि (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        यदि (_this->GetDisplayUsableBounds(_this, display, rect)) {
            फर्काऊ true;
        }
    }

    // Oh well, just give the entire display bounds.
    फर्काऊ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    यदि (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        फर्काऊ display->natural_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        फर्काऊ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    यदि (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        फर्काऊ display->current_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        फर्काऊ SDL_ORIENTATION_LANDSCAPE;
    }
}

शून्य SDL_SetDisplayContentScale(SDL_VideoDisplay *display, भिन्न scale)
{
    यदि (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        लागि (window = _this->windows; window; window = window->next) {
            यदि (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

भिन्न SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    फर्काऊ display->content_scale;
}

शून्य SDL_SetWindowHDRProperties(SDL_Window *window, अचर SDL_HDROutputProperties *HDR, bool send_event)
{
    अचर SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    यदि (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        यदि (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

शून्य SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, अचर SDL_HDROutputProperties *HDR)
{
    अचर SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    अचर bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	यदि (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    यदि (changed && !SDL_DriverSendsHDRChanges(_this)) {
        लागि (SDL_Window *w = display->device->windows; w; w = w->next) {
            यदि (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

स्थिर शून्य SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    यदि (display->अङ्क_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
स्थिर अचर SDL_DisplayMode *SDL_GetFullscreenModeMatch(अचर SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    यदि (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        फर्काऊ रिक्त;
    }

    SDL_memcpy(&fullscreen_mode, mode, परिमाण(fullscreen_mode));
    यदि (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = रिक्त;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    यदि (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        यदि (!mode) {
            लागि (पूर्णाङ्क i = 0; i < display->अङ्क_fullscreen_modes; ++i) {
                यदि (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], परिमाण(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    रोक;
                }
            }
        }

        // Search for a mode with the same characteristics
        यदि (!mode) {
            लागि (पूर्णाङ्क i = 0; i < display->अङ्क_fullscreen_modes; ++i) {
                यदि (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    रोक;
                }
            }
        }
    }
    फर्काऊ mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, अचर SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    पूर्णाङ्क i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, परिमाण(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->अङ्क_fullscreen_modes;
    लागि (i = 0; i < nmodes; ++i) {
        यदि (cmpmodes(&new_mode, &modes[i]) == 0) {
            फर्काऊ false;
        }
    }

    // Go ahead and add the new mode
    यदि (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * परिमाण(*modes));
        यदि (!modes) {
            फर्काऊ false;
        }

        यदि (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * परिमाण(*modes));
            लागि (i = 0; i < nmodes; ++i) {
                यदि (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->अङ्क_fullscreen_modes++], &new_mode, परिमाण(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->अङ्क_fullscreen_modes,
              परिमाण(SDL_DisplayMode), cmpmodes);

    फर्काऊ true;
}

शून्य SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    पूर्णाङ्क i;

    लागि (i = display->अङ्क_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = रिक्त;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = रिक्त;
    display->अङ्क_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, पूर्णाङ्क *गन्ती)
{
    पूर्णाङ्क i;
    पूर्णाङ्क अङ्क_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    यदि (गन्ती) {
        *गन्ती = 0;
    }

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    SDL_UpdateFullscreenDisplayModes(display);

    अङ्क_modes = display->अङ्क_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((अङ्क_modes + 1) * परिमाण(*result) + अङ्क_modes * परिमाण(**result));
    यदि (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((अङ्क_modes + 1) * परिमाण(*result)));
        यदि (अङ्क_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, अङ्क_modes * परिमाण(*modes));
        }
        लागि (i = 0; i < अङ्क_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = रिक्त;

        यदि (गन्ती) {
            *गन्ती = अङ्क_modes;
        }
    } अन्यथा {
        यदि (गन्ती) {
            *गन्ती = 0;
        }
    }
    फर्काऊ result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, पूर्णाङ्क w, पूर्णाङ्क h, भिन्न refresh_rate, bool include_माथिल्लो_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        फर्काऊ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    अचर SDL_DisplayMode *mode, *closest = रिक्त;
    भिन्न aspect_ratio;
    पूर्णाङ्क i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    यदि (h > 0) {
        aspect_ratio = (भिन्न)w / h;
    } अन्यथा {
        aspect_ratio = 1.0f;
    }

    यदि (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    लागि (i = 0; i < display->अङ्क_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        यदि (w > mode->w) {
            // Out of sorted modes large enough here
            रोक;
        }
        यदि (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            जारी;
        }
        यदि (mode->pixel_density > 1.0f && !include_माथिल्लो_density_modes) {
            जारी;
        }
        यदि (closest) {
            भिन्न current_aspect_ratio = (भिन्न)mode->w / mode->h;
            भिन्न closest_aspect_ratio = (भिन्न)closest->w / closest->h;
            यदि (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                जारी;
            }

            यदि (mode->w == closest->w && mode->h == closest->h) {
                यदि (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    जारी;
                }
                यदि (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    जारी;
                }
            }
        }

        closest = mode;
    }
    यदि (!closest) {
        फर्काऊ SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    फर्काऊ true;
}

स्थिर bool DisplayModeChanged(अचर SDL_DisplayMode *old_mode, अचर SDL_DisplayMode *new_mode)
{
    फर्काऊ ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

शून्य SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, अचर SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    यदि (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        फर्काऊ;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    यदि (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        यदि (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

अचर SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    फर्काऊ &display->desktop_mode;
}

शून्य SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, अचर SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    यदि (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } अन्यथा {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    यदि (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

अचर SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    फर्काऊ display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    यदि (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        फर्काऊ true;
    }

    यदि (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    यदि (mode == display->current_mode) {
        फर्काऊ true;
    }
#endif

    // Actually change the display mode
    यदि (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        यदि (!result) {
            फर्काऊ false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    फर्काऊ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
स्थिर शून्य SDL_GetClosestPointOnRect(अचर SDL_Rect *rect, SDL_Point *point)
{
    अचर पूर्णाङ्क दायाँ = rect->x + rect->w - 1;
    अचर पूर्णाङ्क bottom = rect->y + rect->h - 1;

    यदि (point->x < rect->x) {
        point->x = rect->x;
    } अन्यथा यदि (point->x > दायाँ) {
        point->x = दायाँ;
    }

    यदि (point->y < rect->y) {
        point->y = rect->y;
    } अन्यथा यदि (point->y > bottom) {
        point->y = bottom;
    }
}

स्थिर SDL_DisplayID GetDisplayForRect(पूर्णाङ्क x, पूर्णाङ्क y, पूर्णाङ्क w, पूर्णाङ्क h)
{
    पूर्णाङ्क i, dist;
    SDL_DisplayID closest = 0;
    पूर्णाङ्क closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    यदि (_this) {
        लागि (i = 0; i < _this->अङ्क_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            यदि (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, रिक्त)) {
                फर्काऊ display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            यदि (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    यदि (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    फर्काऊ closest;
}

शून्य SDL_RelativeToGlobalForWindow(SDL_Window *window, पूर्णाङ्क rel_x, पूर्णाङ्क rel_y, पूर्णाङ्क *abs_x, पूर्णाङ्क *abs_y)
{
    SDL_Window *w;

    यदि (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        लागि (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            यदि (!SDL_WINDOW_IS_POPUP(w)) {
                रोक;
            }
        }
    }

    यदि (abs_x) {
        *abs_x = rel_x;
    }
    यदि (abs_y) {
        *abs_y = rel_y;
    }
}

शून्य SDL_GlobalToRelativeForWindow(SDL_Window *window, पूर्णाङ्क abs_x, पूर्णाङ्क abs_y, पूर्णाङ्क *rel_x, पूर्णाङ्क *rel_y)
{
    SDL_Window *w;

    यदि (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        लागि (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            यदि (!SDL_WINDOW_IS_POPUP(w)) {
                रोक;
            }
        }
    }

    यदि (rel_x) {
        *rel_x = abs_x;
    }
    यदि (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(अचर SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        फर्काऊ 0;
    }

    फर्काऊ GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(अचर SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        फर्काऊ 0;
    }

    फर्काऊ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

स्थिर SDL_DisplayID GetDisplayAtOrigin(पूर्णाङ्क x, पूर्णाङ्क y)
{
    लागि (पूर्णाङ्क i = 0; i < _this->अङ्क_displays; ++i) {
        SDL_Rect rect;
        अचर SDL_DisplayID cur_id = _this->displays[i]->id;
        यदि (SDL_GetDisplayBounds(cur_id, &rect)) {
            यदि (x == rect.x && y == rect.y) {
                फर्काऊ cur_id;
            }
        }
    }

    फर्काऊ 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    पूर्णाङ्क x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    यदि (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    यदि (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } अन्यथा {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    यदि (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    फर्काऊ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, रिक्त);

    // An explicit fullscreen display overrides all
    यदि (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    यदि (!displayID) {
        displayID = window->pending_displayID;
    }
    यदि (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        अचर पूर्णाङ्क x = window->last_position_pending ? window->pending.x : window->x;
        अचर पूर्णाङ्क y = window->last_position_pending ? window->pending.y : window->y;
        अचर पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->w;
        अचर पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        यदि (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    यदि (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    फर्काऊ SDL_GetVideoDisplay(displayID);
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
    यदि (fs_display) {
        SDL_Set_सङ्ख्या_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } अन्यथा {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    फर्काऊ GetDisplayForWindow(window);
}

स्थिर शून्य SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    यदि (SDL_SendsDisplayChanges(_this)) {
        फर्काऊ;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    यदि (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        यदि (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            यदि (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                पूर्णाङ्क old_area = old_overlap.w * old_overlap.h;
                पूर्णाङ्क new_area = new_overlap.w * new_overlap.h;
                भिन्न new_overlap_ratio = (new_area / ((भिन्न)old_area + new_area));
                यदि (new_overlap_ratio < 0.80) {
                    फर्काऊ;
                }
            }
        }
    }

    यदि (displayID != window->displayID) {
        पूर्णाङ्क i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        लागि (i = 0; i < _this->अङ्क_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            यदि (display->fullscreen_window == window) {
                यदि (display_index != i) {
                    यदि (display_index < 0) {
                        display_index = i;
                    } अन्यथा {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        यदि (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = रिक्त;
                    }
                }
                रोक;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (पूर्णाङ्क)displayID, 0);
    }
}

भिन्न SDL_GetWindowPixelDensity(SDL_Window *window)
{
    पूर्णाङ्क window_w, window_h, pixel_w, pixel_h;
    भिन्न pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    यदि (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (भिन्न)pixel_w / window_w;
    }
    फर्काऊ pixel_density;
}

भिन्न SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    फर्काऊ window->display_scale;
}

स्थिर शून्य SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    भिन्न display_scale;

    यदि (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } अन्यथा {
        अचर भिन्न pixel_density = SDL_GetWindowPixelDensity(window);
        अचर भिन्न content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    यदि (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = रिक्त;
    SDL_DisplayMode *mode = रिक्त;
    पूर्णाङ्क i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    यदि (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    यदि (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        यदि (!display) {
            // This should never happen, but it did...
            गच्छ done;
        }
    } अन्यथा {
        लागि (i = 0; i < _this->अङ्क_displays; ++i) {
            display = _this->displays[i];
            यदि (display->fullscreen_window == window) {
                रोक;
            }
        }
        यदि (!display || i == _this->अङ्क_displays) {
            // Already not fullscreen on any display
            display = रिक्त;
        }
    }

    यदि (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        यदि (mode) {
            window->fullscreen_exclusive = true;
        } अन्यथा {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    यदि (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        यदि (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            यदि (display) {
                display->fullscreen_window = रिक्त;
            }
            गच्छ done;
        }
        यदि (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            यदि (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                यदि (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    गच्छ error;
                }
            } अन्यथा यदि (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                लागि (i = 0; i < _this->अङ्क_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    यदि (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, रिक्त);
                        यदि (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = रिक्त;
                    }
                }
            }

            यदि (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                गच्छ done;
            }
        }
    }
#endif

    यदि (display) {
        // Restore the video mode on other displays if needed
        लागि (i = 0; i < _this->अङ्क_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            यदि (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, रिक्त);
                other->fullscreen_window = रिक्त;
            }
        }
    }

    यदि (fullscreen) {
        पूर्णाङ्क mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        यदि (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        यदि (!SDL_SetDisplayModeForDisplay(display, mode)) {
            गच्छ error;
        }
        यदि (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            यदि (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } अन्यथा {
                resized = true;
            }

            यदि (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                यदि (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } अन्यथा यदि (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                गच्छ error;
            }
        }

        यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            यदि (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                यदि (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } अन्यथा {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                यदि (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                यदि (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } अन्यथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } अन्यथा {
        bool resized = false;

        // Restore the desktop mode
        यदि (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, रिक्त);
        }
        यदि (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            यदि (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                यदि (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } अन्यथा {
                resized = true;
            }

            यदि (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } अन्यथा यदि (ret == SDL_FULLSCREEN_FAILED) {
                गच्छ error;
            }
        }

        यदि (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            यदि (display) {
                display->fullscreen_window = रिक्त;
            }

            यदि (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                यदि (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } अन्यथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    फर्काऊ true;

error:
    यदि (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    फर्काऊ false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, अचर SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (mode) {
        यदि (!SDL_GetFullscreenModeMatch(mode)) {
            फर्काऊ SDL_SetError("Invalid fullscreen display mode");
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

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    यदि (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    यदि (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    फर्काऊ true;
}

अचर SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);
    CHECK_WINDOW_NOT_POPUP(window, रिक्त);

    यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
        फर्काऊ SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } अन्यथा {
        फर्काऊ SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

शून्य *SDL_GetWindowICCProfile(SDL_Window *window, माप_प्रकार *size)
{
    यदि (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        फर्काऊ रिक्त;
    }
    फर्काऊ _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    अचर SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    यदि (mode) {
        फर्काऊ mode->format;
    } अन्यथा {
        फर्काऊ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_माथिल्लो_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_शीर्ष | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

स्थिर SDL_INLINE bool IsAcceptingDragAndDrop(शून्य)
{
    यदि (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        फर्काऊ true;
    }
    फर्काऊ false;
}

// prepare a newly-created window
स्थिर SDL_INLINE शून्य PrepareDragAndDropSupport(SDL_Window *window)
{
    यदि (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
शून्य SDL_ToggleDragAndDropSupport(शून्य)
{
    यदि (_this && _this->AcceptDragAndDrop) {
        अचर bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        लागि (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(पूर्णाङ्क *गन्ती)
{
    यदि (गन्ती) {
        *गन्ती = 0;
    }

    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }

    SDL_Window *window;
    पूर्णाङ्क अङ्क_added = 0;
    पूर्णाङ्क अङ्क_windows = 0;
    लागि (window = _this->windows; window; window = window->next) {
        ++अङ्क_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((अङ्क_windows + 1) * परिमाण(*windows));
    यदि (!windows) {
        फर्काऊ रिक्त;
    }

    लागि (window = _this->windows; window; window = window->next) {
        windows[अङ्क_added++] = window;
        यदि (अङ्क_added == अङ्क_windows) {
            // Race condition? Multi-threading not supported, ignore it
            रोक;
        }
    }
    windows[अङ्क_added] = रिक्त;

    यदि (गन्ती) {
        *गन्ती = अङ्क_added;
    }
    फर्काऊ windows;
}

स्थिर शून्य ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    यदि (!SDL_WINDOW_IS_POPUP(window)) {
        यदि (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        यदि (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        यदि (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        यदि (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        यदि (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        यदि (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

स्थिर शून्य SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    यदि (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } अन्यथा {
        ApplyWindowFlags(window, flags);
        यदि (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#यदि defined(SDL_PLATFORM_LINUX)
    यदि (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_मान(window, 0.0f);
    }
#endif
}

स्थिर bool SDL_ContextNotSupported(अचर वर्ण *name)
{
    फर्काऊ SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

स्थिर bool SDL_DllNotSupported(अचर वर्ण *name)
{
    फर्काऊ SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

स्थिर संरचना {
    अचर वर्ण *property_name;
    SDL_WindowFlags flag;
    bool invert_मान;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_शीर्ष_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_शीर्ष,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_माथिल्लो_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_माथिल्लो_PIXEL_DENSITY,  false },
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
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_सङ्ख्या, 0);

    लागि (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        यदि (SDL_WindowFlagProperties[i].invert_मान) {
            यदि (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } अन्यथा {
            यदि (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    फर्काऊ flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    अचर वर्ण *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, रिक्त);
    पूर्णाङ्क x = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_सङ्ख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णाङ्क y = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_सङ्ख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णाङ्क w = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_सङ्ख्या, 0);
    पूर्णाङ्क h = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_सङ्ख्या, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, रिक्त);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    यदि (!_this) {
        // Initialize the video system if needed
        यदि (!SDL_Init(SDL_INIT_VIDEO)) {
            फर्काऊ रिक्त;
        }

        // Make clang-tidy happy
        यदि (!_this) {
            फर्काऊ रिक्त;
        }
    }

    यदि ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        फर्काऊ रिक्त;
    }

    यदि ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        यदि (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            फर्काऊ रिक्त;
        }

        // Tooltip and popup menu window must specify a parent window
        यदि (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            फर्काऊ रिक्त;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    यदि (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (अचिन्हित पूर्णाङ्क)type_flags);
        फर्काऊ रिक्त;
    }

    // Make sure the display list is up to date for window placement
    यदि (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    यदि (w < 1) {
        w = 1;
    }
    यदि (h < 1) {
        h = 1;
    }

    यदि (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        यदि ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा यदि ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        यदि (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        यदि (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            यदि (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            यदि (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    यदि (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (अचिन्हित पूर्णाङ्क)graphics_flags);
        फर्काऊ रिक्त;
    }

    // Some platforms have certain graphics backends enabled by default
    यदि (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    यदि (flags & SDL_WINDOW_OPENGL) {
        यदि (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            फर्काऊ रिक्त;
        }
        यदि (!SDL_GL_LoadLibrary(रिक्त)) {
            फर्काऊ रिक्त;
        }
    }

    यदि (flags & SDL_WINDOW_VULKAN) {
        यदि (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            फर्काऊ रिक्त;
        }
        यदि (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            फर्काऊ रिक्त;
        }
    }

    यदि (flags & SDL_WINDOW_METAL) {
        यदि (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            फर्काऊ रिक्त;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, परिमाण(*window));
    यदि (!window) {
        फर्काऊ रिक्त;
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
    यदि (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    यदि (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    यदि (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    यदि (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    यदि (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_थप_Error();
        SDL_DestroyWindow(window);
        SDL_झिक_Error();
        फर्काऊ रिक्त;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#यदि !defined(SDL_PLATFORM_WINDOWS)
    यदि (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    यदि (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    फर्काऊ window;
}

SDL_Window *SDL_CreateWindow(अचर वर्ण *title, पूर्णाङ्क w, पूर्णाङ्क h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    यदि (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_सङ्ख्या, w);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_सङ्ख्या, h);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_सङ्ख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    फर्काऊ window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, पूर्णाङ्क offset_x, पूर्णाङ्क offset_y, पूर्णाङ्क w, पूर्णाङ्क h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    यदि (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        फर्काऊ रिक्त;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_सङ्ख्या, offset_x);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_सङ्ख्या, offset_y);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_सङ्ख्या, w);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_सङ्ख्या, h);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_सङ्ख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    फर्काऊ window;
}

स्थिर bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    यदि (!_this->ReconfigureWindow) {
        फर्काऊ false;
    }

    अचर SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    यदि (graphics_flags & (graphics_flags - 1)) {
        फर्काऊ SDL_SetError("Conflicting window flags specified");
    }

    यदि ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        फर्काऊ SDL_ContextNotSupported("OpenGL");
    }
    यदि ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        फर्काऊ SDL_ContextNotSupported("Vulkan");
    }
    यदि ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        फर्काऊ SDL_ContextNotSupported("Metal");
    }

    यदि (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        यदि (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            फर्काऊ false;
        }
    } अन्यथा {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        यदि (!_this->ReconfigureWindow(_this, window, 0)) {
            फर्काऊ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        यदि (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        यदि (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    यदि (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(रिक्त);
        यदि (!loaded_opengl) {
            फर्काऊ false;
        }
    } अन्यथा यदि (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(रिक्त);
        यदि (!loaded_vulkan) {
            फर्काऊ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    यदि (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        यदि (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        यदि (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        फर्काऊ false;
    }

    window->flags |= graphics_flags;

    फर्काऊ true;
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
    यदि (graphics_flags & (graphics_flags - 1)) {
        फर्काऊ SDL_SetError("Conflicting window flags specified");
    }

    यदि ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        फर्काऊ SDL_ContextNotSupported("OpenGL");
    }
    यदि ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        फर्काऊ SDL_ContextNotSupported("Vulkan");
    }
    यदि ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        फर्काऊ SDL_ContextNotSupported("Metal");
    }

    यदि (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } अन्यथा {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    यदि (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    यदि (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        अचर bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    यदि ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        यदि (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } अन्यथा {
            need_gl_unload = true;
        }
    } अन्यथा यदि (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    यदि ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        यदि (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } अन्यथा {
            need_vulkan_unload = true;
        }
    } अन्यथा यदि (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    यदि (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    यदि (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    यदि (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    यदि (need_gl_load) {
        यदि (!SDL_GL_LoadLibrary(रिक्त)) {
            फर्काऊ false;
        }
        loaded_opengl = true;
    }

    यदि (need_vulkan_load) {
        यदि (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            फर्काऊ false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    यदि (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        यदि (!_this->CreateSDLWindow(_this, window, 0)) {
            यदि (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            यदि (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            फर्काऊ false;
        }
    }

    यदि (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    यदि (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    यदि (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    यदि (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    यदि (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    यदि (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    यदि (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    फर्काऊ true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    यदि (!SDL_ReconfigureWindowInternal(window, flags)) {
        फर्काऊ SDL_RecreateWindow(window, flags);
    }

    फर्काऊ true;
}

bool SDL_HasWindows(शून्य)
{
    फर्काऊ _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    फर्काऊ window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    यदि (id) {
        लागि (window = _this->windows; window; window = window->next) {
            यदि (window->id == id) {
                फर्काऊ window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    फर्काऊ रिक्त;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    फर्काऊ window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    यदि (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    फर्काऊ window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    फर्काऊ window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, अचर वर्ण *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (title == window->title) {
        फर्काऊ true;
    }
    यदि (!title) {
        title = "";
    }
    यदि (window->title && SDL_strcmp(title, window->title) == 0) {
        फर्काऊ true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    यदि (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    फर्काऊ true;
}

अचर वर्ण *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    फर्काऊ window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        फर्काऊ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    यदि (!window->icon) {
        फर्काऊ false;
    }

    यदि (!_this->SetWindowIcon) {
        फर्काऊ SDL_Unsupported();
    }

    फर्काऊ _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    अचर पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->windowed.w;
    अचर पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    यदि (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    यदि (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    यदि (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        यदि (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा यदि (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        यदि (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        यदि (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            यदि (!SDL_GetDisplayBounds(displayID, &bounds)) {
                फर्काऊ false;
            }
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(y)) {
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
    यदि (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    यदि (_this->SetWindowPosition) {
        अचर bool result = _this->SetWindowPosition(_this, window);
        यदि (result) {
            SDL_SyncIfRequired(window);
        }
        फर्काऊ result;
    }

    फर्काऊ SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, पूर्णाङ्क *x, पूर्णाङ्क *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#अन्यथा
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    यदि (use_display_origin) {
        SDL_DisplayID displayID;

        यदि (x) {
            *x = 0;
        }
        यदि (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        यदि (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            यदि (x) {
                *x = bounds.x;
            }
            यदि (y) {
                *y = bounds.y;
            }
        }
    } अन्यथा {
        अचर bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        यदि (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        यदि (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    फर्काऊ true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->SetWindowBordered) {
        फर्काऊ SDL_Unsupported();
    }

    अचर bool want = bordered;
    अचर bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    यदि (want != have) {
        यदि (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } अन्यथा {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    फर्काऊ true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->SetWindowResizable) {
        फर्काऊ SDL_Unsupported();
    }

    अचर bool want = resizable;
    अचर bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    यदि (want != have) {
        यदि (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    फर्काऊ true;
}

bool SDL_Set_Window_Always_On_शीर्ष(SDL_Window *window, bool on_शीर्ष)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->Set_Window_Always_On_शीर्ष) {
        फर्काऊ SDL_Unsupported();
    }

    अचर bool want = on_शीर्ष;
    अचर bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) != 0);
    यदि (want != have) {
        यदि (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_शीर्ष;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_शीर्ष;
        }
        _this->Set_Window_Always_On_शीर्ष(_this, window, want);
    }

    फर्काऊ true;
}

bool SDL_SetWindowSize(SDL_Window *window, पूर्णाङ्क w, पूर्णाङ्क h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        फर्काऊ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        फर्काऊ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    भिन्न new_aspect = w / (भिन्न)h;
    यदि (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (पूर्णाङ्क)SDL_roundf(h * window->max_aspect);
    } अन्यथा यदि (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (पूर्णाङ्क)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    यदि (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    यदि (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    यदि (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    यदि (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    यदि (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } अन्यथा {
        फर्काऊ SDL_Unsupported();
    }
    फर्काऊ true;
}

bool SDL_GetWindowSize(SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    यदि (w) {
        *w = window->w;
    }
    यदि (h) {
        *h = window->h;
    }
    फर्काऊ true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, भिन्न min_aspect, भिन्न max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    यदि (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    फर्काऊ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, भिन्न *min_aspect, भिन्न *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    यदि (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    फर्काऊ true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, पूर्णाङ्क *शीर्ष, पूर्णाङ्क *बायाँ, पूर्णाङ्क *bottom, पूर्णाङ्क *दायाँ)
{
    पूर्णाङ्क dummy = 0;

    यदि (!शीर्ष) {
        शीर्ष = &dummy;
    }
    यदि (!बायाँ) {
        बायाँ = &dummy;
    }
    यदि (!दायाँ) {
        दायाँ = &dummy;
    }
    यदि (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *शीर्ष = *बायाँ = *bottom = *दायाँ = 0;

    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->GetWindowBordersSize) {
        फर्काऊ SDL_Unsupported();
    }

    फर्काऊ _this->GetWindowBordersSize(_this, window, शीर्ष, बायाँ, bottom, दायाँ);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    पूर्णाङ्क filter;

    CHECK_WINDOW_MAGIC(window, false);

    यदि (!w) {
        w = &filter;
    }

    यदि (!h) {
        h = &filter;
    }

    यदि (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } अन्यथा {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        अचर SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        यदि ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } अन्यथा {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        यदि (mode) {
            *w = (पूर्णाङ्क)SDL_ceilf(*w * mode->pixel_density);
            *h = (पूर्णाङ्क)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    फर्काऊ true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, पूर्णाङ्क min_w, पूर्णाङ्क min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        फर्काऊ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        फर्काऊ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        फर्काऊ SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    यदि (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    फर्काऊ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, पूर्णाङ्क *min_w, पूर्णाङ्क *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    यदि (min_w) {
        *min_w = window->min_w;
    }
    यदि (min_h) {
        *min_h = window->min_h;
    }
    फर्काऊ true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, पूर्णाङ्क max_w, पूर्णाङ्क max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        फर्काऊ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        फर्काऊ SDL_InvalidParamError("max_h");
    }

    यदि ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        फर्काऊ SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    यदि (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    फर्काऊ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, पूर्णाङ्क *max_w, पूर्णाङ्क *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    यदि (max_w) {
        *max_w = window->max_w;
    }
    यदि (max_h) {
        *max_h = window->max_h;
    }
    फर्काऊ true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!(window->flags & SDL_WINDOW_HIDDEN)) {
        फर्काऊ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    यदि (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        फर्काऊ true;
    }

    यदि (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } अन्यथा {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    लागि (child = window->first_child; child; child = child->next_sibling) {
        यदि (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            रोक;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    फर्काऊ true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        फर्काऊ true;
    }

    // Hide all child windows
    लागि (child = window->first_child; child; child = child->next_sibling) {
        यदि (child->flags & SDL_WINDOW_HIDDEN) {
            रोक;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    अचर SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    यदि (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } अन्यथा {
        SDL_SetMouseFocus(रिक्त);
        SDL_SetKeyboardFocus(रिक्त);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    फर्काऊ true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        फर्काऊ true;
    }
    यदि (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    फर्काऊ true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->MaximizeWindow) {
        फर्काऊ SDL_Unsupported();
    }

    यदि (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        फर्काऊ SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        फर्काऊ true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    फर्काऊ true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->MinimizeWindow) {
        फर्काऊ SDL_Unsupported();
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        फर्काऊ true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    फर्काऊ true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->RestoreWindow) {
        फर्काऊ SDL_Unsupported();
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        फर्काऊ true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    फर्काऊ true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        यदि (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        फर्काऊ true;
    }

    यदि (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    यदि (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    यदि (result) {
        SDL_SyncIfRequired(window);
    }

    फर्काऊ result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (_this->SyncWindow) {
        फर्काऊ _this->SyncWindow(_this, window);
    } अन्यथा {
        फर्काऊ true;
    }
}

स्थिर bool ShouldAttemptTextureFramebuffer(शून्य)
{
    अचर वर्ण *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    यदि (!_this->CreateWindowFramebuffer) {
        फर्काऊ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    यदि (hint && *hint) {
        यदि (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } अन्यथा {
            attempt_texture_framebuffer = true;
        }
    } अन्यथा {
        यदि (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } अन्यथा {
            attempt_texture_framebuffer = false;
        }
    }
    फर्काऊ attempt_texture_framebuffer;
}

स्थिर SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    शून्य *pixels = रिक्त;
    पूर्णाङ्क pitch = 0;
    bool created_framebuffer = false;
    पूर्णाङ्क w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    यदि (!_this->checked_texture_framebuffer) {
        यदि (ShouldAttemptTextureFramebuffer()) {
            यदि (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
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

    यदि (!created_framebuffer) {
        यदि (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            फर्काऊ रिक्त;
        }

        यदि (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            फर्काऊ रिक्त;
        }
    }

    यदि (window->surface) {
        // We may have gone recursive and already created the surface
        फर्काऊ window->surface;
    }

    फर्काऊ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    फर्काऊ window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    यदि (!window->surface_valid) {
        यदि (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = रिक्त;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        यदि (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    फर्काऊ window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, पूर्णाङ्क vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowFramebufferVSync) {
        फर्काऊ SDL_Unsupported();
    }
    फर्काऊ _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, पूर्णाङ्क *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->GetWindowFramebufferVSync) {
        फर्काऊ SDL_Unsupported();
    }
    फर्काऊ _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    फर्काऊ SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, अचर SDL_Rect *rects,
                                 पूर्णाङ्क numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!window->surface_valid) {
        फर्काऊ SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    फर्काऊ _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = रिक्त;
        window->surface_valid = false;
    }

    यदि (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        यदि (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    फर्काऊ true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, भिन्न opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowOpacity) {
        फर्काऊ SDL_Unsupported();
    }

    यदि (opacity < 0.0f) {
        opacity = 0.0f;
    } अन्यथा यदि (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    यदि (result) {
        window->opacity = opacity;
    }

    फर्काऊ result;
}

भिन्न SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    फर्काऊ window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    यदि (window == parent) {
        फर्काऊ SDL_SetError("Cannot set the parent of a window to itself.");
    }

    यदि (!_this->SetWindowParent) {
        फर्काऊ SDL_Unsupported();
    }

    यदि (window->flags & SDL_WINDOW_MODAL) {
        फर्काऊ SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    यदि (window->parent == parent) {
        फर्काऊ true;
    }

    अचर bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : रिक्त);

    फर्काऊ ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->SetWindowModal) {
        फर्काऊ SDL_Unsupported();
    }

    यदि (modal) {
        यदि (!window->parent) {
            फर्काऊ SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } अन्यथा यदि (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } अन्यथा {
        फर्काऊ true; // Already not modal, so nothing to do.
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        फर्काऊ true;
    }

    फर्काऊ _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_आगत_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    जबसम्म (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        यदि (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_आगत_FOCUS);
        }
    }

    *new_focus = focus;
    फर्काऊ set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    लागि (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    लागि (w = current_focus; w != toplevel_parent; w = w->parent) {
        यदि (w == window) {
            found_higher_focus = true;
            रोक;
        }
    }

    फर्काऊ !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    अचर bool want = (focusable != false); // normalize the flag.
    अचर bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    यदि ((want != have) && (_this->SetWindowFocusable)) {
        यदि (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } अन्यथा {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        यदि (!_this->SetWindowFocusable(_this, window, want)) {
            फर्काऊ false;
        }
    }

    फर्काऊ true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    अचर bool want = (fill != false); // normalize the flag.
    अचर bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    यदि ((want != have) && (_this->SetWindowFillDocument)) {
        यदि (!_this->SetWindowFillDocument(_this, window, want)) {
            फर्काऊ false;
        } अन्यथा यदि (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    फर्काऊ true;
}

शून्य SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    यदि (window->flags & SDL_WINDOW_आगत_FOCUS) {
        यदि (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } अन्यथा {
            mouse_grabbed = false;
        }

        यदि (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } अन्यथा {
            keyboard_grabbed = false;
        }
    } अन्यथा {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    यदि (mouse_grabbed || keyboard_grabbed) {
        यदि (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            यदि (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            यदि (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } अन्यथा यदि (_this->grabbed_window == window) {
        _this->grabbed_window = रिक्त; // ungrabbing input.
    }

    यदि (_this->SetWindowMouseGrab) {
        यदि (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    यदि (_this->SetWindowKeyboardGrab) {
        यदि (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    यदि (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = रिक्त;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        यदि (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        फर्काऊ true;
    }

    यदि (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        फर्काऊ true;
    }
    यदि (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    यदि (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        फर्काऊ false;
    }
    फर्काऊ true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        यदि (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        फर्काऊ true;
    }

    यदि (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        फर्काऊ true;
    }
    यदि (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    यदि (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        फर्काऊ false;
    }
    फर्काऊ true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    फर्काऊ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    फर्काऊ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(शून्य)
{
    यदि (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        फर्काऊ _this->grabbed_window;
    } अन्यथा {
        फर्काऊ रिक्त;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, अचर SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowMouseRect) {
        फर्काऊ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    यदि (!rect) {
        rect = &zero;
    }

    यदि (SDL_memcmp(&window->mouse_rect, rect, परिमाण(*rect)) == 0) {
        फर्काऊ true;
    }
    SDL_memcpy(&window->mouse_rect, rect, परिमाण(*rect));

    फर्काऊ _this->SetWindowMouseRect(_this, window);
}

अचर SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    यदि (SDL_RectEmpty(&window->mouse_rect)) {
        फर्काऊ रिक्त;
    } अन्यथा {
        फर्काऊ &window->mouse_rect;
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

    यदि (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        फर्काऊ true;
    }

    यदि (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    यदि (!SDL_UpdateRelativeMouseMode()) {
        यदि (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } अन्यथा {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        फर्काऊ false;
    }
    फर्काऊ true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        फर्काऊ true;
    } अन्यथा {
        फर्काऊ false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (_this->FlashWindow) {
        फर्काऊ _this->FlashWindow(_this, window, operation);
    }

    फर्काऊ SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        फर्काऊ SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    यदि (_this->ApplyWindowProgress) {
        यदि (!_this->ApplyWindowProgress(_this, window)) {
            फर्काऊ false;
        }
    }

    फर्काऊ true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    फर्काऊ window->progress_state;
}

bool SDL_Set_Window_Progress_मान(SDL_Window *window, भिन्न मान)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    मान = SDL_clamp(मान, 0.0f, 1.f);

    window->progress_मान = मान;

    यदि (_this->ApplyWindowProgress) {
        यदि (!_this->ApplyWindowProgress(_this, window)) {
            फर्काऊ false;
        }
    }

    फर्काऊ true;
}

भिन्न SDL_Get_Window_Progress_मान(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    फर्काऊ window->progress_मान;
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
    यदि (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        अचर bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        यदि (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_माथिल्लो_density_modes = false;

            यदि (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_माथिल्लो_density_modes = true;
            }
            अचर bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_माथिल्लो_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            यदि (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } अन्यथा {
            SDL_zero(window->current_fullscreen_mode);
        }

        यदि (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
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

    यदि ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, रिक्त);
        यदि (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

शून्य SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    पूर्णाङ्क pixel_w = 0, pixel_h = 0;

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
    यदि (SDL_HasMainCallbacks()) {
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

    rect.x = window->safe_inset_बायाँ;
    rect.y = window->safe_inset_शीर्ष;
    rect.w = window->w - (window->safe_inset_दायाँ + window->safe_inset_बायाँ);
    rect.h = window->h - (window->safe_inset_शीर्ष + window->safe_inset_bottom);
    यदि (SDL_memcmp(&rect, &window->safe_rect, परिमाण(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

शून्य SDL_SetWindowSafeAreaInsets(SDL_Window *window, पूर्णाङ्क बायाँ, पूर्णाङ्क दायाँ, पूर्णाङ्क शीर्ष, पूर्णाङ्क bottom)
{
    window->safe_inset_बायाँ = बायाँ;
    window->safe_inset_दायाँ = दायाँ;
    window->safe_inset_शीर्ष = शीर्ष;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    यदि (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    यदि (rect) {
        यदि (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } अन्यथा {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    फर्काऊ true;
}

शून्य SDL_OnWindowMinimized(SDL_Window *window)
{
    यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
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

    यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

शून्य SDL_OnWindowEnter(SDL_Window *window)
{
    यदि (_this->OnWindowEnter) {
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

    यदि (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

स्थिर bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    अचर वर्ण *hint;

    यदि (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        फर्काऊ false;
    }

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    यदि (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        यदि (Cocoa_IsShowingModalDialog(window)) {
            फर्काऊ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } अन्यथा यदि (Cocoa_IsWindowInFullscreenSpace(window)) {
            फर्काऊ false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        बाह्य bool Android_JNI_ShouldMinimizeOnFocusLoss(शून्य);
        यदि (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            फर्काऊ false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    यदि (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        यदि (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            फर्काऊ true;
        } अन्यथा {
            फर्काऊ false;
        }
    }
    फर्काऊ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

शून्य SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    यदि (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(शून्य)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    यदि (focus) {
        // Get the toplevel parent window.
        जबसम्म (focus->parent) {
            focus = focus->parent;
        }
    }

    फर्काऊ focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->अङ्क_renderers + 1) * परिमाण(*renderers));
    यदि (!renderers) {
        फर्काऊ false;
    }

    window->renderers = renderers;
    window->renderers[window->अङ्क_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    फर्काऊ true;
}

शून्य SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    लागि (पूर्णाङ्क i = 0; i < window->अङ्क_renderers; ++i) {
        यदि (window->renderers[i] == renderer) {
            यदि (i < (window->अङ्क_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->अङ्क_renderers - i - 1) * परिमाण(window->renderers[i]));
            }
            --window->अङ्क_renderers;
            रोक;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    यदि (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, रिक्त) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

शून्य SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    जबसम्म (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    यदि (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    यदि (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_आगत_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    यदि (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    लागि (पूर्णाङ्क i = 0; i < _this->अङ्क_displays; ++i) {
        यदि (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = रिक्त;
        }
    }

    // Make sure this window no longer has focus
    यदि (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(रिक्त);
    }
    यदि ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    यदि (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(रिक्त);
    }

    // Make no context current if this is the current context window
    यदि (window->flags & SDL_WINDOW_OPENGL) {
        यदि (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, रिक्त);
        }
    }

    यदि (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    यदि (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    यदि (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    यदि (_this->grabbed_window == window) {
        _this->grabbed_window = रिक्त; // ungrabbing input.
    }

    यदि (_this->current_glwin == window) {
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
    यदि (window->next) {
        window->next->prev = window->prev;
    }
    यदि (window->prev) {
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
    यदि (!_this) {
        फर्काऊ true;
    }
    फर्काऊ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(शून्य)
{
    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }
    यदि (!_this->suspend_screensaver) {
        फर्काऊ true;
    }
    _this->suspend_screensaver = false;
    यदि (_this->SuspendScreenSaver) {
        फर्काऊ _this->SuspendScreenSaver(_this);
    }

    फर्काऊ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(शून्य)
{
    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }
    यदि (_this->suspend_screensaver) {
        फर्काऊ true;
    }
    _this->suspend_screensaver = true;
    यदि (_this->SuspendScreenSaver) {
        फर्काऊ _this->SuspendScreenSaver(_this);
    }

    फर्काऊ SDL_Unsupported();
}

शून्य SDL_QuitVideo(शून्य)
{
    पूर्णाङ्क i;

    यदि (!_this) {
        फर्काऊ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#यदि 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    जबसम्म (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    यदि (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    यदि (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    लागि (i = _this->अङ्क_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->अङ्क_displays == 0);
    SDL_free(_this->displays);
    _this->displays = रिक्त;

    SDL_CancelClipboardData(0);

    यदि (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = रिक्त;
    }
    _this->मुक्त(_this);
    _this = रिक्त;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(अचर वर्ण *path)
{
    bool result;

    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }
    यदि (_this->gl_config.driver_loaded) {
        यदि (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            फर्काऊ SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } अन्यथा {
        यदि (!_this->GL_LoadLibrary) {
            फर्काऊ SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    यदि (result) {
        ++_this->gl_config.driver_loaded;
    } अन्यथा {
        यदि (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    फर्काऊ result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(अचर वर्ण *proc)
{
    SDL_FunctionPointer func;

    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    func = रिक्त;
    यदि (_this->GL_GetProcAddress) {
        यदि (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } अन्यथा {
            SDL_SetError("No GL driver has been loaded");
        }
    } अन्यथा {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    फर्काऊ func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(अचर वर्ण *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    func = रिक्त;

    यदि (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } अन्यथा {
        SDL_SetError("No EGL library has been loaded");
    }

    फर्काऊ func;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    फर्काऊ रिक्त;
#endif
}

शून्य SDL_GL_UnloadLibrary(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ;
    }
    यदि (_this->gl_config.driver_loaded > 0) {
        यदि (--_this->gl_config.driver_loaded > 0) {
            फर्काऊ;
        }
        यदि (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
प्रकारनिर्देश GLenum (APIENTRY* PFNGLGETERRORPROC) (शून्य);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
प्रकारनिर्देश अचर GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
प्रकारनिर्देश अचर GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

स्थिर SDL_INLINE bool isAtLeastGL3(अचर वर्ण *verstr)
{
    फर्काऊ verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(अचर वर्ण *extension)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    अचर वर्ण *extensions;
    अचर वर्ण *start;
    अचर वर्ण *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    यदि (where || *extension == '\0') {
        फर्काऊ false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    यदि (start && *start == '0') {
        फर्काऊ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    यदि (!glGetStringFunc) {
        फर्काऊ false;
    }

    यदि (isAtLeastGL3((अचर वर्ण *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint अङ्क_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        यदि ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            फर्काऊ false;
        }

#ifndef GL_अङ्क_EXTENSIONS
#define GL_अङ्क_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_अङ्क_EXTENSIONS, &अङ्क_exts);
        लागि (i = 0; i < अङ्क_exts; i++) {
            अचर वर्ण *thisext = (अचर वर्ण *)glGetStringiFunc(GL_EXTENSIONS, i);
            यदि (SDL_strcmp(thisext, extension) == 0) {
                फर्काऊ true;
            }
        }

        फर्काऊ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (अचर वर्ण *)glGetStringFunc(GL_EXTENSIONS);
    यदि (!extensions) {
        फर्काऊ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    लागि (;;) {
        where = SDL_strstr(start, extension);
        यदि (!where) {
            रोक;
        }

        terminator = where + SDL_strlen(extension);
        यदि (where == extensions || *(where - 1) == ' ') {
            यदि (*terminator == ' ' || *terminator == '\0') {
                फर्काऊ true;
            }
        }

        start = terminator;
    }
    फर्काऊ false;
#अन्यथा
    फर्काऊ false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
शून्य SDL_GL_DeduceMaxSupportedESProfile(पूर्णाङ्क *major, पूर्णाङ्क *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    यदि (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } अन्यथा यदि (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } अन्यथा यदि (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
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
    यदि (!_this) {
        फर्काऊ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

शून्य SDL_GL_ResetAttributes(शून्य)
{
    यदि (!_this) {
        फर्काऊ;
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
#अथवायदि defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#अथवायदि defined(SDL_VIDEO_OPENGL_ES)
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

    यदि (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, पूर्णाङ्क मान)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }
    result = true;
    विकल्प (attr) {
    पक्ष SDL_GL_RED_SIZE:
        _this->gl_config.red_size = मान;
        रोक;
    पक्ष SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = मान;
        रोक;
    पक्ष SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = मान;
        रोक;
    पक्ष SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = मान;
        रोक;
    पक्ष SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = मान;
        रोक;
    पक्ष SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = मान;
        रोक;
    पक्ष SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = मान;
        रोक;
    पक्ष SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = मान;
        रोक;
    पक्ष SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = मान;
        रोक;
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = मान;
        रोक;
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = मान;
        रोक;
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = मान;
        रोक;
    पक्ष SDL_GL_STEREO:
        _this->gl_config.stereo = मान;
        रोक;
    पक्ष SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = मान;
        रोक;
    पक्ष SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = मान;
        रोक;
    पक्ष SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = मान;
        रोक;
    पक्ष SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = मान;
        रोक;
    पक्ष SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = मान;
        रोक;
    पक्ष SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = मान;
        रोक;
    पक्ष SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = मान;
        रोक;
    पक्ष SDL_GL_CONTEXT_FLAGS:
        यदि (मान & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", मान);
            रोक;
        }
        _this->gl_config.flags = मान;
        रोक;
    पक्ष SDL_GL_CONTEXT_PROFILE_MASK:
        यदि (मान != 0 &&
            मान != SDL_GL_CONTEXT_PROFILE_CORE &&
            मान != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            मान != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", मान);
            रोक;
        }
        _this->gl_config.profile_mask = मान;
        रोक;
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = मान;
        रोक;
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = मान;
        रोक;
    पक्ष SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = मान;
        रोक;
    पक्ष SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = मान;
        रोक;
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = मान;
        रोक;
    पक्ष SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = मान;
        रोक;
    स्वभाव:
        result = SDL_SetError("Unknown OpenGL attribute");
        रोक;
    }
    फर्काऊ result;
#अन्यथा
    फर्काऊ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, पूर्णाङ्क *मान)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_बायाँ;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!मान) {
        फर्काऊ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *मान = 0;

    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }

    विकल्प (attr) {
    पक्ष SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        रोक;
    पक्ष SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        रोक;
    पक्ष SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        रोक;
    पक्ष SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        रोक;
    पक्ष SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        रोक;
#अन्यथा
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *मान = _this->gl_config.double_buffer;
        फर्काऊ true;
#endif
    पक्ष SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        रोक;
    पक्ष SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        रोक;
#ifdef SDL_VIDEO_OPENGL
    पक्ष SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        रोक;
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        रोक;
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        रोक;
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        रोक;
    पक्ष SDL_GL_STEREO:
        attrib = GL_STEREO;
        रोक;
#अन्यथा
    पक्ष SDL_GL_ACCUM_RED_SIZE:
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
    पक्ष SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *मान = 0;
        फर्काऊ true;
#endif
    पक्ष SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        रोक;
    पक्ष SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        रोक;
    पक्ष SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        रोक;
    पक्ष SDL_GL_BUFFER_SIZE:
    {
        पूर्णाङ्क rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        यदि (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            फर्काऊ false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            फर्काऊ false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            फर्काऊ false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            फर्काऊ false;
        }

        *मान = rsize + gsize + bsize + asize;
        फर्काऊ true;
    }
    पक्ष SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *मान = (_this->gl_config.accelerated != 0);
        फर्काऊ true;
    }
    पक्ष SDL_GL_RETAINED_BACKING:
    {
        *मान = _this->gl_config.retained_backing;
        फर्काऊ true;
    }
    पक्ष SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *मान = _this->gl_config.major_version;
        फर्काऊ true;
    }
    पक्ष SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *मान = _this->gl_config.minor_version;
        फर्काऊ true;
    }
    पक्ष SDL_GL_CONTEXT_FLAGS:
    {
        *मान = _this->gl_config.flags;
        फर्काऊ true;
    }
    पक्ष SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *मान = _this->gl_config.profile_mask;
        फर्काऊ true;
    }
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *मान = _this->gl_config.share_with_current_context;
        फर्काऊ true;
    }
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *मान = _this->gl_config.framebuffer_srgb_capable;
        फर्काऊ true;
    }
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
    {
        *मान = _this->gl_config.no_error;
        फर्काऊ true;
    }
    पक्ष SDL_GL_EGL_PLATFORM:
    {
        *मान = _this->gl_config.egl_platform;
        फर्काऊ true;
    }
    पक्ष SDL_GL_FLOATBUFFERS:
    {
        यदि (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            रोक;
        } अन्यथा {
            फर्काऊ 0;
        }
    }
    स्वभाव:
        फर्काऊ SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    यदि (!glGetStringFunc) {
        फर्काऊ false;
    }

    यदि (attachmentattrib && isAtLeastGL3((अचर वर्ण *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        यदि (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        यदि (glGetFramebufferAttachmentParameterivFunc) {
            यदि (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            यदि (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            यदि (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)मान);
            } अन्यथा {
                *मान = 0;
            }
            यदि (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } अन्यथा {
            फर्काऊ false;
        }
    } अन्यथा
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        यदि (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)मान);
        } अन्यथा {
            फर्काऊ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    यदि (!glGetErrorFunc) {
        फर्काऊ false;
    }

    error = glGetErrorFunc();
    यदि (error != GL_NO_ERROR) {
        यदि (error == GL_INVALID_ENUM) {
            फर्काऊ SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } अन्यथा यदि (error == GL_INVALID_मान) {
            फर्काऊ SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        फर्काऊ SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    यदि (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *मान = (*मान == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    फर्काऊ true;
#अन्यथा
    फर्काऊ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = रिक्त;
    CHECK_WINDOW_MAGIC(window, रिक्त);

    यदि (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        फर्काऊ रिक्त;
    }

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    पूर्णाङ्क srgb_requested = -1;
    अचर वर्ण *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    यदि (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    यदि (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, रिक्त);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, रिक्त);
    }

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    यदि (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        यदि (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            यदि (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } अन्यथा {
                supported = isAtLeastGL3((अचर वर्ण *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            यदि (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    फर्काऊ ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }

    यदि (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        फर्काऊ true;
    }

    यदि (!context) {
        window = रिक्त;
    } अन्यथा यदि (window) {
        CHECK_WINDOW_MAGIC(window, false);

        यदि (!(window->flags & SDL_WINDOW_OPENGL)) {
            फर्काऊ SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } अन्यथा यदि (!_this->gl_allow_no_surface) {
        फर्काऊ SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    यदि (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, रिक्त);
        SDL_SetTLS(&_this->current_glctx_tls, context, रिक्त);
    }
    फर्काऊ result;
}

SDL_Window *SDL_GL_GetCurrentWindow(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    फर्काऊ (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    फर्काऊ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ EGL_NO_DISPLAY;
    }
    यदि (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        फर्काऊ EGL_NO_DISPLAY;
    }
    फर्काऊ _this->egl_data->egl_display;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    फर्काऊ रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    यदि (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        फर्काऊ रिक्त;
    }
    फर्काऊ _this->egl_data->egl_config;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    फर्काऊ रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    यदि (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        फर्काऊ रिक्त;
    }
    यदि (_this->GL_GetEGLSurface) {
        फर्काऊ _this->GL_GetEGLSurface(_this, window);
    }
    फर्काऊ रिक्त;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    फर्काऊ रिक्त;
#endif
}

bool SDL_GL_SetSwapInterval(पूर्णाङ्क interval)
{
    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    } अन्यथा यदि (SDL_GL_GetCurrentContext() == रिक्त) {
        फर्काऊ SDL_SetError("No OpenGL context has been made current");
    } अन्यथा यदि (_this->GL_SetSwapInterval) {
        फर्काऊ _this->GL_SetSwapInterval(_this, interval);
    } अन्यथा {
        फर्काऊ SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(पूर्णाङ्क *interval)
{
    CHECK_PARAM(!interval) {
       फर्काऊ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    यदि (!_this) {
        फर्काऊ SDL_SetError("no video driver");
    } अन्यथा यदि (SDL_GL_GetCurrentContext() == रिक्त) {
        फर्काऊ SDL_SetError("no current context");
    } अन्यथा यदि (_this->GL_GetSwapInterval) {
        फर्काऊ _this->GL_GetSwapInterval(_this, interval);
    } अन्यथा {
        फर्काऊ SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!(window->flags & SDL_WINDOW_OPENGL)) {
        फर्काऊ SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    यदि (SDL_GL_GetCurrentWindow() != window) {
        फर्काऊ SDL_SetError("The specified window has not been made current");
    }

    फर्काऊ _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        फर्काऊ SDL_InvalidParamError("context");
    }

    यदि (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(रिक्त, रिक्त);
    }

    फर्काऊ _this->GL_DestroyContext(_this, context);
}

#यदि 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
स्थिर शून्य Create_Mask_From_Color_साँचो_Or_Alpha(SDL_Surface *icon, Uint8 *mask, पूर्णाङ्क flags)
{
    पूर्णाङ्क x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    विकल्प (SDL_BYTESPERPIXEL(icon->format)) {
    पक्ष 1:
        {
            Uint8 *pixels;
            लागि (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                लागि (x = 0; x < icon->w; ++x) {
                    यदि (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        रोक;

    पक्ष 2:
        {
            Uint16 *pixels;
            लागि (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                लागि (x = 0; x < icon->w; ++x) {
                    यदि ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अन्यथा यदि ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        रोक;

    पक्ष 4:
        {
            Uint32 *pixels;
            लागि (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                लागि (x = 0; x < icon->w; ++x) {
                    यदि ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अन्यथा यदि ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        रोक;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
शून्य SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    यदि (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        यदि (mask == रिक्त) {
            पूर्णाङ्क mask_len = icon->h * (icon->w + 7) / 8;
            पूर्णाङ्क flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            यदि (mask == रिक्त) {
                फर्काऊ;
            }
            SDL_memset(mask, ~0, mask_len);
            यदि (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            यदि (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            यदि (flags) {
                Create_Mask_From_Color_साँचो_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } अन्यथा {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_आगत_Type SDL_Get_Text_आगत_Type(SDL_PropertiesID props)
{
    फर्काऊ (SDL_Text_आगत_Type)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_TEXTINPUT_TYPE_सङ्ख्या, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_आगत_Capitalization(SDL_PropertiesID props)
{
    यदि (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_सङ्ख्या)) {
        फर्काऊ (SDL_Capitalization)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_सङ्ख्या, SDL_CAPITALIZE_NONE);
    }

    विकल्प (SDL_Get_Text_आगत_Type(props)) {
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        फर्काऊ SDL_CAPITALIZE_SENTENCES;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        फर्काऊ SDL_CAPITALIZE_शब्दहरू;
    स्वभाव:
        फर्काऊ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_आगत_Autocorrect(SDL_PropertiesID props)
{
    फर्काऊ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_आगत_Multiline(SDL_PropertiesID props)
{
    यदि (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        फर्काऊ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    यदि (SDL_GetHintBoolean(SDL_HINT_RETURN_साँचो_HIDES_IME, false)) {
        फर्काऊ false;
    } अन्यथा {
        फर्काऊ true;
    }
}

स्थिर bool AutoShowingScreenKeyboard(शून्य)
{
    अचर वर्ण *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    यदि (!hint) {
        // This hint is currently only used by the X11 video driver
        यदि (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    यदि (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        फर्काऊ true;
    } अन्यथा {
        फर्काऊ false;
    }
}

bool SDL_Start_Text_आगत(SDL_Window *window)
{
    फर्काऊ SDL_Start_Text_आगत_With_Properties(window, 0);
}

bool SDL_Start_Text_आगत_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->text_आगत_props) {
        SDL_DestroyProperties(window->text_आगत_props);
        window->text_आगत_props = 0;
    }

    यदि (props) {
        window->text_आगत_props = SDL_CreateProperties();
        यदि (!window->text_आगत_props) {
            फर्काऊ false;
        }
        यदि (!SDL_CopyProperties(props, window->text_आगत_props)) {
            फर्काऊ false;
        }
    }

    यदि (_this->Set_Text_आगत_Properties) {
        _this->Set_Text_आगत_Properties(_this, window, props);
    }

    यदि (!window->text_आगत_active) {
        // Start the text input system
        यदि (_this->Start_Text_आगत) {
            यदि (!_this->Start_Text_आगत(_this, window, props)) {
                फर्काऊ false;
            }
        }
        window->text_आगत_active = true;
    }

    // Show the on-screen keyboard, if desired
    यदि (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        यदि (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    फर्काऊ true;
}

bool SDL_Text_आगत_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    फर्काऊ window->text_आगत_active;
}

bool SDL_Stop_Text_आगत(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->text_आगत_active) {
        // Stop the text input system
        यदि (_this->Stop_Text_आगत) {
            _this->Stop_Text_आगत(_this, window);
        }
        window->text_आगत_active = false;
    }

    // Hide the on-screen keyboard, if desired
    यदि (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        यदि (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    फर्काऊ true;
}

bool SDL_Set_Text_आगत_Area(SDL_Window *window, अचर SDL_Rect *rect, पूर्णाङ्क cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (rect) {
        SDL_copyp(&window->text_आगत_rect, rect);
        window->text_आगत_cursor = cursor;
    } अन्यथा {
        SDL_zero(window->text_आगत_rect);
        window->text_आगत_cursor = 0;
    }

    यदि (_this && _this->Update_Text_आगत_Area) {
        यदि (!_this->Update_Text_आगत_Area(_this, window)) {
            फर्काऊ false;
        }
    }
    फर्काऊ true;
}

bool SDL_Get_Text_आगत_Area(SDL_Window *window, SDL_Rect *rect, पूर्णाङ्क *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (rect) {
        SDL_copyp(rect, &window->text_आगत_rect);
    }
    यदि (cursor) {
        *cursor = window->text_आगत_cursor;
    }
    फर्काऊ true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (_this->ClearComposition) {
        फर्काऊ _this->ClearComposition(_this, window);
    }
    फर्काऊ true;
}

bool SDL_HasScreenKeyboardSupport(शून्य)
{
    यदि (_this && _this->HasScreenKeyboardSupport) {
        फर्काऊ _this->HasScreenKeyboardSupport(_this);
    }
    फर्काऊ false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    फर्काऊ _this->screen_keyboard_shown;
}

शून्य SDL_SendScreenKeyboardShown(शून्य)
{
    यदि (!_this || _this->screen_keyboard_shown) {
        फर्काऊ;
    }

    _this->screen_keyboard_shown = true;

    यदि (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_थप_Event(&event);
    }
}

शून्य SDL_SendScreenKeyboardHidden(शून्य)
{
    यदि (!_this || !_this->screen_keyboard_shown) {
        फर्काऊ;
    }

    _this->screen_keyboard_shown = false;

    यदि (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_थप_Event(&event);
    }
}

पूर्णाङ्क SDL_Get_Message_Box_गन्ती(शून्य)
{
    फर्काऊ SDL_GetAtomicInt(&SDL_messagebox_गन्ती);
}

bool SDL_ShowMessageBox(अचर SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    पूर्णाङ्क dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        फर्काऊ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        फर्काऊ SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    वर्ण *titlecpy = रिक्त;
    वर्ण *msgcpy = रिक्त;
    यदि (messageboxdata->title) {
        अचर माप_प्रकार slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(वर्ण, slen, &titleisstack);
        यदि (!titlecpy) {
            फर्काऊ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    यदि (messageboxdata->message) {
        अचर माप_प्रकार slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(वर्ण, slen, &msgisstack);
        यदि (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            फर्काऊ false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (शून्य)SDL_AtomicIncRef(&SDL_messagebox_गन्ती);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    यदि (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, परिमाण(*messageboxdata));
    mbdata.title = titlecpy;
    यदि (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    यदि (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    यदि (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } अन्यथा {
        // It's completely fine to call this function before video is initialized
        अचर वर्ण *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        यदि (driver_name && *driver_name != 0) {
            अचर वर्ण *driver_attempt = driver_name;
            जबसम्म (driver_attempt && (*driver_attempt != 0) && !result) {
                अचर वर्ण *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                लागि (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                    यदि (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        यदि (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        रोक;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
            }
        } अन्यथा {
            लागि (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                यदि (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    रोक;
                }
            }
        }
    }

    यदि (!result) {
        अचर वर्ण *error = SDL_GetError();

        यदि (!*error) {
            SDL_SetError("No message system available");
        }
    } अन्यथा {
        SDL_ClearError();
    }

    (शून्य)SDL_AtomicDecRef(&SDL_messagebox_गन्ती);

    यदि (current_window) {
        SDL_RaiseWindow(current_window);
    }

    यदि (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    फर्काऊ result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, अचर वर्ण *title, अचर वर्ण *message, SDL_Window *window)
{
#यदि defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_दायाँ;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_दायाँ = gsp_Has_Gpu_दायाँ();
    यदि (!has_Gpu_दायाँ)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    यदि (!has_Gpu_दायाँ)
        gfxExit();

    फर्काऊ true;
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

    फर्काऊ SDL_ShowMessageBox(&data, रिक्त);
#endif
}

bool SDL_ShouldAllowTopmost(शून्य)
{
    फर्काऊ SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        फर्काऊ true;
    }

    फर्काऊ SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, शून्य *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowHitTest) {
        फर्काऊ SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    फर्काऊ _this->SetWindowHitTest(window, callback != रिक्त);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    यदि (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        फर्काऊ SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    यदि (!props) {
        फर्काऊ false;
    }

    यदि (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        यदि (!surface) {
            फर्काऊ false;
        }
    } अन्यथा {
        surface = रिक्त;
    }

    यदि (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        फर्काऊ false;
    }

    यदि (_this->UpdateWindowShape) {
        यदि (!_this->UpdateWindowShape(_this, window, surface)) {
            फर्काऊ false;
        }
    }
    फर्काऊ true;
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
    SDL_SendAppEvent(SDL_EVENT_तल्लो_MEMORY);
}

शून्य SDL_OnApplicationWillEnterBackground(शून्य)
{
    यदि (_this) {
        SDL_Window *window;
        लागि (window = _this->windows; window; window = window->next) {
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

    यदि (_this) {
        SDL_Window *window;
        लागि (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(अचर वर्ण *path)
{
    bool result;

    यदि (!_this) {
        फर्काऊ SDL_UninitializedVideo();
    }
    यदि (_this->vulkan_config.loader_loaded) {
        यदि (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            फर्काऊ SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } अन्यथा {
        यदि (!_this->Vulkan_LoadLibrary) {
            फर्काऊ SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    यदि (result) {
        _this->vulkan_config.loader_loaded++;
    }
    फर्काऊ result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ रिक्त;
    }
    यदि (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        फर्काऊ रिक्त;
    }
    फर्काऊ (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

शून्य SDL_Vulkan_UnloadLibrary(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        फर्काऊ;
    }
    यदि (_this->vulkan_config.loader_loaded > 0) {
        यदि (--_this->vulkan_config.loader_loaded > 0) {
            फर्काऊ;
        }
        यदि (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

वर्ण अचर * अचर *SDL_Vulkan_GetInstanceExtensions(Uint32 *गन्ती)
{
    Uint32 tmpcount = 0;
    यदि (!गन्ती) {
        गन्ती = &tmpcount;
    }

    यदि (!_this->Vulkan_GetInstanceExtensions) {
        *गन्ती = 0;
        SDL_Unsupported();
        फर्काऊ रिक्त;
    }

    फर्काऊ _this->Vulkan_GetInstanceExtensions(_this, गन्ती);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  अचर संरचना VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        फर्काऊ false;
    }

    CHECK_PARAM(!instance) {
        फर्काऊ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        फर्काऊ SDL_InvalidParamError("surface");
    }

    यदि (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        यदि (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        यदि (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        यदि (SDL_Vulkan_LoadLibrary(रिक्त)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } अन्यथा {
            फर्काऊ SDL_SetError("failed to load Vulkan library");
        }
    }

    फर्काऊ _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

शून्य SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               अचर संरचना VkAllocationCallbacks *allocator)
{
    यदि (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        फर्काऊ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        फर्काऊ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        फर्काऊ false;
    }

    यदि (_this->Vulkan_GetPresentationSupport) {
        फर्काऊ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    फर्काऊ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    यदि (!_this->Metal_CreateView) {
        SDL_Unsupported();
        फर्काऊ रिक्त;
    }

    यदि (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        यदि (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        यदि (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    फर्काऊ _this->Metal_CreateView(_this, window);
}

शून्य SDL_Metal_DestroyView(SDL_MetalView view)
{
    यदि (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

शून्य *SDL_Metal_GetLayer(SDL_MetalView view)
{
    यदि (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            फर्काऊ रिक्त;
        }
        फर्काऊ _this->Metal_GetLayer(_this, view);
    } अन्यथा {
        SDL_SetError("Metal is not supported.");
        फर्काऊ रिक्त;
    }
}

#यदि defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
अचर वर्ण *SDL_GetCSSCursorName(SDL_SystemCursor id, अचर वर्ण **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    विकल्प (id) {
    पक्ष SDL_SYSTEM_CURSOR_DEFAULT:
        फर्काऊ "default";

    पक्ष SDL_SYSTEM_CURSOR_TEXT:
        फर्काऊ "text";

    पक्ष SDL_SYSTEM_CURSOR_WAIT:
        फर्काऊ "wait";

    पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR:
        फर्काऊ "crosshair";

    पक्ष SDL_SYSTEM_CURSOR_PROGRESS:
        फर्काऊ "progress";

    पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        यदि (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        फर्काऊ "nwse-resize";

    पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE:
        यदि (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        फर्काऊ "nesw-resize";

    पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE:
        यदि (fallback_name) {
            *fallback_name = "col-resize";
        }
        फर्काऊ "ew-resize";

    पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE:
        यदि (fallback_name) {
            *fallback_name = "row-resize";
        }
        फर्काऊ "ns-resize";

    पक्ष SDL_SYSTEM_CURSOR_MOVE:
        यदि (fallback_name) {
            *fallback_name = "all-scroll";
        }
        फर्काऊ "move";

    पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        फर्काऊ "not-allowed";

    पक्ष SDL_SYSTEM_CURSOR_POINTER:
        फर्काऊ "pointer";

    पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE:
        फर्काऊ "nw-resize";

    पक्ष SDL_SYSTEM_CURSOR_N_RESIZE:
        फर्काऊ "n-resize";

    पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE:
        फर्काऊ "ne-resize";

    पक्ष SDL_SYSTEM_CURSOR_E_RESIZE:
        फर्काऊ "e-resize";

    पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE:
        फर्काऊ "se-resize";

    पक्ष SDL_SYSTEM_CURSOR_S_RESIZE:
        फर्काऊ "s-resize";

    पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE:
        फर्काऊ "sw-resize";

    पक्ष SDL_SYSTEM_CURSOR_W_RESIZE:
        फर्काऊ "w-resize";

    पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        फर्काऊ "context-menu";

    पक्ष SDL_SYSTEM_CURSOR_HELP:
        फर्काऊ "help";

    पक्ष SDL_SYSTEM_CURSOR_CELL:
        फर्काऊ "cell";

    पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        फर्काऊ "vertical-text";

    पक्ष SDL_SYSTEM_CURSOR_ALIAS:
        फर्काऊ "alias";

    पक्ष SDL_SYSTEM_CURSOR_COPY:
        फर्काऊ "copy";

    पक्ष SDL_SYSTEM_CURSOR_NO_DROP:
        फर्काऊ "no-drop";

    पक्ष SDL_SYSTEM_CURSOR_GRAB:
        फर्काऊ "grab";

    पक्ष SDL_SYSTEM_CURSOR_GRABBING:
        फर्काऊ "grabbing";

    पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE:
        फर्काऊ "col-resize";

    पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE:
        फर्काऊ "row-resize";

    पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL:
        यदि (fallback_name) {
            *fallback_name = "move";
        }
        फर्काऊ "all-scroll";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_IN:
        फर्काऊ "zoom-in";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_OUT:
        फर्काऊ "zoom-out";

    स्वभाव:
        फर्काऊ "default";
    }
}
#endif

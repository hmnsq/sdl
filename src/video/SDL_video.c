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
#ifdef SDL_निवेश_LINUXEV
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
        प्रत्यागम result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        प्रत्यागम result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        प्रत्यागम result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        प्रत्यागम result;                                                  \
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
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

स्थिर bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

स्थिर bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

स्थिर bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

स्थिर bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

स्थिर bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
स्थिर bool syncHint;

स्थिर शून्य SDL_SyncHintWatcher(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मूल्य, ध्रुव वर्ण *new_मूल्य)
{
    syncHint = SDL_GetStringBoolean(new_मूल्य, false);
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
        प्रत्यागम SDL_WINDOW_OPENGL;
    }
#endif
#यदि defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    यदि (_this->Metal_CreateView) {
        प्रत्यागम SDL_WINDOW_METAL;
    }
#endif
#यदि defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    यदि (SDL_strcmp(_this->name, "openvr") == 0) {
        प्रत्यागम SDL_WINDOW_OPENGL;
    }
#endif
    प्रत्यागम 0;
}

स्थिर bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    ध्रुव bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    पूर्णाङ्क i;
    पूर्णाङ्क w, h;
    ध्रुव SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    यदि (!data) {
        SDL_Renderer *renderer = रिक्त;
        ध्रुव वर्ण *render_driver = रिक्त;

        // See if there's a render driver being requested
        ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
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
                यावत् ((ptr = SDL_strchr(ptr, ',')) != रिक्त) {
                    *ptr = '\0';
                    ध्रुव bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
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
                प्रत्यागम false;
            }
        } अन्यथा {
            SDL_assert(render_driver_copy == रिक्त);
            ध्रुव पूर्णाङ्क total = SDL_Get_अंक_Render_Drivers();
            प्रति (i = 0; i < total; ++i) {
                ध्रुव वर्ण *name = SDL_GetRenderDriver(i);
                यदि (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    यदि (renderer) {
                        भङ्ग; // this will work.
                    }
                }
            }
            यदि (!renderer) {
                प्रत्यागम SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != रिक्त); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, परिमाण(*data));
        यदि (!data) {
            SDL_DestroyRenderer(renderer);
            प्रत्यागम false;
        }
        यदि (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            प्रत्यागम false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ध्रुव SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, रिक्त);
    यदि (!texture_formats) {
        प्रत्यागम false;
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

    प्रति (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        यदि (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            भङ्ग;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    यदि (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        प्रत्यागम false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ध्रुव माप_प्रकार allocsize = (माप_प्रकार)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        यदि (!data->pixels) {
            प्रत्यागम false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, रिक्त);

    प्रत्यागम true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    यदि (!data) {
        प्रत्यागम false;
    }
    यदि (!data->renderer) {
        प्रत्यागम false;
    }
    प्रत्यागम SDL_SetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    यदि (!data) {
        प्रत्यागम false;
    }
    यदि (!data->renderer) {
        प्रत्यागम false;
    }
    प्रत्यागम SDL_GetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    शून्य *src;
    पूर्णाङ्क w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    यदि (!data || !data->texture) {
        प्रत्यागम SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    यदि (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (शून्य *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        यदि (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            प्रत्यागम false;
        }

        यदि (!SDL_RenderTexture(data->renderer, data->texture, रिक्त, रिक्त)) {
            प्रत्यागम false;
        }

        SDL_RenderPresent(data->renderer);
    }
    प्रत्यागम true;
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
स्थिर SDL_AtomicInt SDL_messagebox_गिनती;

स्थिर पूर्णाङ्क SDLCALL cmpmodes(ध्रुव शून्य *A, ध्रुव शून्य *B)
{
    ध्रुव SDL_DisplayMode *a = (ध्रुव SDL_DisplayMode *)A;
    ध्रुव SDL_DisplayMode *b = (ध्रुव SDL_DisplayMode *)B;
    पूर्णाङ्क a_refresh_rate = (पूर्णाङ्क)(a->refresh_rate * 100);
    पूर्णाङ्क b_refresh_rate = (पूर्णाङ्क)(b->refresh_rate * 100);
    पूर्णाङ्क a_pixel_density = (पूर्णाङ्क)(a->pixel_density * 100);
    पूर्णाङ्क b_pixel_density = (पूर्णाङ्क)(b->pixel_density * 100);

    यदि (a->w != b->w) {
        प्रत्यागम b->w - a->w;
    } अन्यथा यदि (a->h != b->h) {
        प्रत्यागम b->h - a->h;
    } अन्यथा यदि (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        प्रत्यागम SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } अन्यथा यदि (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        प्रत्यागम SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } अन्यथा यदि (a_refresh_rate != b_refresh_rate) {
        प्रत्यागम b_refresh_rate - a_refresh_rate;
    } अन्यथा यदि (a_pixel_density != b_pixel_density) {
        प्रत्यागम a_pixel_density - b_pixel_density;
    }
    प्रत्यागम 0;
}

bool SDL_UninitializedVideo(शून्य)
{
    प्रत्यागम SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
स्थिर ध्रुव VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

पूर्णाङ्क SDL_Get_अंक_Video_Drivers(शून्य)
{
    स्थिर पूर्णाङ्क अंक_drivers = -1;

    यदि (अंक_drivers >= 0) {
        प्रत्यागम अंक_drivers;
    }

    अंक_drivers = 0;

    // Build a list of unique video drivers.
    प्रति (पूर्णाङ्क i = 0; bootstrap[i] != रिक्त; ++i) {
        bool duplicate = false;
        प्रति (पूर्णाङ्क j = 0; j < i; ++j) {
            यदि (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                भङ्ग;
            }
        }

        यदि (!duplicate) {
            deduped_bootstrap[अंक_drivers++] = bootstrap[i];
        }
    }

    प्रत्यागम अंक_drivers;
}

ध्रुव वर्ण *SDL_GetVideoDriver(पूर्णाङ्क index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_अंक_Video_Drivers()) {
        SDL_InvalidParamError("index");
        प्रत्यागम रिक्त;
    }
    प्रत्यागम deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ध्रुव वर्ण *driver_name)
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
        ध्रुव वर्ण *driver_attempt = driver_name;
        यावत् (driver_attempt && *driver_attempt != 0 && !video) {
            ध्रुव वर्ण *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            प्रति (i = 0; bootstrap[i]; ++i) {
                यदि (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    यदि (video) {
                        भङ्ग;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
        }
    } अन्यथा {
        प्रति (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            यदि (video) {
                भङ्ग;
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
        प्रत्यागम false;
    }

    // Make sure some displays were added
    यदि (_this->अंक_displays == 0) {
        SDL_QuitVideo();
        प्रत्यागम SDL_SetError("The video driver did not add any displays");
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
    प्रत्यागम true;

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
    प्रत्यागम false;
}

ध्रुव वर्ण *SDL_GetCurrentVideoDriver(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(शून्य)
{
    प्रत्यागम _this;
}

bool SDL_OnVideoThread(शून्य)
{
    प्रत्यागम (_this && SDL_GetCurrentThreadID() == _this->thread);
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
        प्रत्यागम _this->system_theme;
    } अन्यथा {
        प्रत्यागम SDL_SYSTEM_THEME_UNKNOWN;
    }
}

शून्य SDL_UpdateDesktopBounds(शून्य)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    यदि (displays) {
        प्रति (पूर्णाङ्क i = 0; displays[i]; ++i) {
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

SDL_DisplayID SDL_AddBasicVideoDisplay(ध्रुव SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    यदि (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, परिमाण(display.desktop_mode));
    }
    प्रत्यागम SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ध्रुव SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    पूर्णाङ्क i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(परिमाण(*new_display));
    यदि (!new_display) {
        प्रत्यागम 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->अंक_displays + 1) * परिमाण(*displays));
    यदि (!displays) {
        SDL_free(new_display);
        प्रत्यागम 0;
    }
    _this->displays = displays;
    _this->displays[_this->अंक_displays++] = new_display;

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

    प्रति (i = 0; i < new_display->अंक_fullscreen_modes; ++i) {
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

    प्रत्यागम id;
}

शून्य SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    प्रति (window = _this->windows; window; window = window->next) {
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
        प्रत्यागम;
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

    यदि (display_index < (_this->अंक_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->अंक_displays - display_index - 1) * परिमाण(_this->displays[display_index]));
    }
    --_this->अंक_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(पूर्णाङ्क *गिनती)
{
    पूर्णाङ्क i;
    SDL_DisplayID *displays;

    यदि (!_this) {
        यदि (गिनती) {
            *गिनती = 0;
        }

        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->अंक_displays + 1) * परिमाण(*displays));
    यदि (displays) {
        यदि (गिनती) {
            *गिनती = _this->अंक_displays;
        }

        प्रति (i = 0; i < _this->अंक_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } अन्यथा {
        यदि (गिनती) {
            *गिनती = 0;
        }
    }
    प्रत्यागम displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    यदि (display_index < 0) {
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->displays[display_index];
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
    प्रत्यागम displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    प्रत्यागम SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(शून्य)
{
    यदि (!_this || _this->अंक_displays == 0) {
        SDL_UninitializedVideo();
        प्रत्यागम 0;
    }
    प्रत्यागम _this->displays[0]->id;
}

पूर्णाङ्क SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_index;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम -1;
    }

    प्रति (display_index = 0; display_index < _this->अंक_displays; ++display_index) {
        यदि (displayID == _this->displays[display_index]->id) {
            प्रत्यागम display_index;
        }
    }
    SDL_SetError("Invalid display");
    प्रत्यागम -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    प्रत्यागम SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    यदि (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    प्रत्यागम display->props;
}

ध्रुव वर्ण *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        प्रत्यागम SDL_InvalidParamError("rect");
    }

    यदि (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        यदि (_this->GetDisplayBounds(_this, display, rect)) {
            प्रत्यागम true;
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
    प्रत्यागम true;
}

स्थिर पूर्णाङ्क ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    प्रत्यागम hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        प्रत्यागम SDL_InvalidParamError("rect");
    }

    यदि (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        प्रत्यागम true;
    }

    यदि (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        यदि (_this->GetDisplayUsableBounds(_this, display, rect)) {
            प्रत्यागम true;
        }
    }

    // Oh well, just give the entire display bounds.
    प्रत्यागम SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    यदि (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        प्रत्यागम display->natural_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        प्रत्यागम SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    यदि (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        प्रत्यागम display->current_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        प्रत्यागम SDL_ORIENTATION_LANDSCAPE;
    }
}

शून्य SDL_SetDisplayContentScale(SDL_VideoDisplay *display, भिन्न scale)
{
    यदि (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        प्रति (window = _this->windows; window; window = window->next) {
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

    प्रत्यागम display->content_scale;
}

शून्य SDL_SetWindowHDRProperties(SDL_Window *window, ध्रुव SDL_HDROutputProperties *HDR, bool send_event)
{
    ध्रुव SDL_HDROutputProperties HDR_clamped = {
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

शून्य SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ध्रुव SDL_HDROutputProperties *HDR)
{
    ध्रुव SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ध्रुव bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	यदि (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    यदि (changed && !SDL_DriverSendsHDRChanges(_this)) {
        प्रति (SDL_Window *w = display->device->windows; w; w = w->next) {
            यदि (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

स्थिर शून्य SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    यदि (display->अंक_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
स्थिर ध्रुव SDL_DisplayMode *SDL_GetFullscreenModeMatch(ध्रुव SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    यदि (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        प्रत्यागम रिक्त;
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
            प्रति (पूर्णाङ्क i = 0; i < display->अंक_fullscreen_modes; ++i) {
                यदि (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], परिमाण(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    भङ्ग;
                }
            }
        }

        // Search for a mode with the same characteristics
        यदि (!mode) {
            प्रति (पूर्णाङ्क i = 0; i < display->अंक_fullscreen_modes; ++i) {
                यदि (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    भङ्ग;
                }
            }
        }
    }
    प्रत्यागम mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode)
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
    nmodes = display->अंक_fullscreen_modes;
    प्रति (i = 0; i < nmodes; ++i) {
        यदि (cmpmodes(&new_mode, &modes[i]) == 0) {
            प्रत्यागम false;
        }
    }

    // Go ahead and add the new mode
    यदि (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * परिमाण(*modes));
        यदि (!modes) {
            प्रत्यागम false;
        }

        यदि (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * परिमाण(*modes));
            प्रति (i = 0; i < nmodes; ++i) {
                यदि (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->अंक_fullscreen_modes++], &new_mode, परिमाण(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->अंक_fullscreen_modes,
              परिमाण(SDL_DisplayMode), cmpmodes);

    प्रत्यागम true;
}

शून्य SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    पूर्णाङ्क i;

    प्रति (i = display->अंक_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = रिक्त;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = रिक्त;
    display->अंक_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, पूर्णाङ्क *गिनती)
{
    पूर्णाङ्क i;
    पूर्णाङ्क अंक_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    यदि (गिनती) {
        *गिनती = 0;
    }

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    SDL_UpdateFullscreenDisplayModes(display);

    अंक_modes = display->अंक_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((अंक_modes + 1) * परिमाण(*result) + अंक_modes * परिमाण(**result));
    यदि (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((अंक_modes + 1) * परिमाण(*result)));
        यदि (अंक_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, अंक_modes * परिमाण(*modes));
        }
        प्रति (i = 0; i < अंक_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = रिक्त;

        यदि (गिनती) {
            *गिनती = अंक_modes;
        }
    } अन्यथा {
        यदि (गिनती) {
            *गिनती = 0;
        }
    }
    प्रत्यागम result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, पूर्णाङ्क w, पूर्णाङ्क h, भिन्न refresh_rate, bool include_ऊपरी_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        प्रत्यागम SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ध्रुव SDL_DisplayMode *mode, *closest = रिक्त;
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

    प्रति (i = 0; i < display->अंक_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        यदि (w > mode->w) {
            // Out of sorted modes large enough here
            भङ्ग;
        }
        यदि (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            अनुवर्त;
        }
        यदि (mode->pixel_density > 1.0f && !include_ऊपरी_density_modes) {
            अनुवर्त;
        }
        यदि (closest) {
            भिन्न current_aspect_ratio = (भिन्न)mode->w / mode->h;
            भिन्न closest_aspect_ratio = (भिन्न)closest->w / closest->h;
            यदि (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                अनुवर्त;
            }

            यदि (mode->w == closest->w && mode->h == closest->h) {
                यदि (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    अनुवर्त;
                }
                यदि (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    अनुवर्त;
                }
            }
        }

        closest = mode;
    }
    यदि (!closest) {
        प्रत्यागम SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    प्रत्यागम true;
}

स्थिर bool DisplayModeChanged(ध्रुव SDL_DisplayMode *old_mode, ध्रुव SDL_DisplayMode *new_mode)
{
    प्रत्यागम ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

शून्य SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    यदि (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        प्रत्यागम;
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

ध्रुव SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम &display->desktop_mode;
}

शून्य SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode)
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

ध्रुव SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    यदि (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        प्रत्यागम true;
    }

    यदि (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    यदि (mode == display->current_mode) {
        प्रत्यागम true;
    }
#endif

    // Actually change the display mode
    यदि (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        यदि (!result) {
            प्रत्यागम false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    प्रत्यागम true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
स्थिर शून्य SDL_GetClosestPointOnRect(ध्रुव SDL_Rect *rect, SDL_Point *point)
{
    ध्रुव पूर्णाङ्क दायाँ = rect->x + rect->w - 1;
    ध्रुव पूर्णाङ्क bottom = rect->y + rect->h - 1;

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
        प्रति (i = 0; i < _this->अंक_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            यदि (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, रिक्त)) {
                प्रत्यागम display->id;
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

    प्रत्यागम closest;
}

शून्य SDL_RelativeToGlobalForWindow(SDL_Window *window, पूर्णाङ्क rel_x, पूर्णाङ्क rel_y, पूर्णाङ्क *abs_x, पूर्णाङ्क *abs_y)
{
    SDL_Window *w;

    यदि (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        प्रति (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            यदि (!SDL_WINDOW_IS_POPUP(w)) {
                भङ्ग;
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
        प्रति (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            यदि (!SDL_WINDOW_IS_POPUP(w)) {
                भङ्ग;
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

SDL_DisplayID SDL_GetDisplayForPoint(ध्रुव SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        प्रत्यागम 0;
    }

    प्रत्यागम GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ध्रुव SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        प्रत्यागम 0;
    }

    प्रत्यागम GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

स्थिर SDL_DisplayID GetDisplayAtOrigin(पूर्णाङ्क x, पूर्णाङ्क y)
{
    प्रति (पूर्णाङ्क i = 0; i < _this->अंक_displays; ++i) {
        SDL_Rect rect;
        ध्रुव SDL_DisplayID cur_id = _this->displays[i]->id;
        यदि (SDL_GetDisplayBounds(cur_id, &rect)) {
            यदि (x == rect.x && y == rect.y) {
                प्रत्यागम cur_id;
            }
        }
    }

    प्रत्यागम 0;
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
    प्रत्यागम displayID;
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
        ध्रुव पूर्णाङ्क x = window->last_position_pending ? window->pending.x : window->x;
        ध्रुव पूर्णाङ्क y = window->last_position_pending ? window->pending.y : window->y;
        ध्रुव पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->w;
        ध्रुव पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->h;

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
    प्रत्यागम SDL_GetVideoDisplay(displayID);
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
        SDL_Set_संख्या_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } अन्यथा {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    प्रत्यागम GetDisplayForWindow(window);
}

स्थिर शून्य SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    यदि (SDL_SendsDisplayChanges(_this)) {
        प्रत्यागम;
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
                    प्रत्यागम;
                }
            }
        }
    }

    यदि (displayID != window->displayID) {
        पूर्णाङ्क i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        प्रति (i = 0; i < _this->अंक_displays; ++i) {
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
                भङ्ग;
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
    प्रत्यागम pixel_density;
}

भिन्न SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    प्रत्यागम window->display_scale;
}

स्थिर शून्य SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    भिन्न display_scale;

    यदि (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } अन्यथा {
        ध्रुव भिन्न pixel_density = SDL_GetWindowPixelDensity(window);
        ध्रुव भिन्न content_scale = SDL_GetDisplayContentScale(window->displayID);

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
        प्रति (i = 0; i < _this->अंक_displays; ++i) {
            display = _this->displays[i];
            यदि (display->fullscreen_window == window) {
                भङ्ग;
            }
        }
        यदि (!display || i == _this->अंक_displays) {
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
                प्रति (i = 0; i < _this->अंक_displays; ++i) {
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
        प्रति (i = 0; i < _this->अंक_displays; ++i) {
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
    प्रत्यागम true;

error:
    यदि (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    प्रत्यागम false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ध्रुव SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (mode) {
        यदि (!SDL_GetFullscreenModeMatch(mode)) {
            प्रत्यागम SDL_SetError("Invalid fullscreen display mode");
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

    प्रत्यागम true;
}

ध्रुव SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);
    CHECK_WINDOW_NOT_POPUP(window, रिक्त);

    यदि (window->flags & SDL_WINDOW_FULLSCREEN) {
        प्रत्यागम SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } अन्यथा {
        प्रत्यागम SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

शून्य *SDL_GetWindowICCProfile(SDL_Window *window, माप_प्रकार *size)
{
    यदि (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ध्रुव SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    यदि (mode) {
        प्रत्यागम mode->format;
    } अन्यथा {
        प्रत्यागम SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ऊपरी_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_शीर्ष | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

स्थिर SDL_INLINE bool IsAcceptingDragAndDrop(शून्य)
{
    यदि (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
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
        ध्रुव bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        प्रति (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(पूर्णाङ्क *गिनती)
{
    यदि (गिनती) {
        *गिनती = 0;
    }

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    SDL_Window *window;
    पूर्णाङ्क अंक_added = 0;
    पूर्णाङ्क अंक_windows = 0;
    प्रति (window = _this->windows; window; window = window->next) {
        ++अंक_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((अंक_windows + 1) * परिमाण(*windows));
    यदि (!windows) {
        प्रत्यागम रिक्त;
    }

    प्रति (window = _this->windows; window; window = window->next) {
        windows[अंक_added++] = window;
        यदि (अंक_added == अंक_windows) {
            // Race condition? Multi-threading not supported, ignore it
            भङ्ग;
        }
    }
    windows[अंक_added] = रिक्त;

    यदि (गिनती) {
        *गिनती = अंक_added;
    }
    प्रत्यागम windows;
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
        SDL_Set_Window_Progress_मूल्य(window, 0.0f);
    }
#endif
}

स्थिर bool SDL_ContextNotSupported(ध्रुव वर्ण *name)
{
    प्रत्यागम SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

स्थिर bool SDL_DllNotSupported(ध्रुव वर्ण *name)
{
    प्रत्यागम SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

स्थिर संरचना {
    ध्रुव वर्ण *property_name;
    SDL_WindowFlags flag;
    bool invert_मूल्य;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_शीर्ष_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_शीर्ष,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_ऊपरी_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_ऊपरी_PIXEL_DENSITY,  false },
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

    प्रति (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        यदि (SDL_WindowFlagProperties[i].invert_मूल्य) {
            यदि (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } अन्यथा {
            यदि (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    प्रत्यागम flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ध्रुव वर्ण *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, रिक्त);
    पूर्णाङ्क x = (पूर्णाङ्क)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_संख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णाङ्क y = (पूर्णाङ्क)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_संख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णाङ्क w = (पूर्णाङ्क)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, 0);
    पूर्णाङ्क h = (पूर्णाङ्क)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, 0);
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
            प्रत्यागम रिक्त;
        }

        // Make clang-tidy happy
        यदि (!_this) {
            प्रत्यागम रिक्त;
        }
    }

    यदि ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        प्रत्यागम रिक्त;
    }

    यदि ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        यदि (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            प्रत्यागम रिक्त;
        }

        // Tooltip and popup menu window must specify a parent window
        यदि (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            प्रत्यागम रिक्त;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    यदि (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (अचिन्हित पूर्णाङ्क)type_flags);
        प्रत्यागम रिक्त;
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
        प्रत्यागम रिक्त;
    }

    // Some platforms have certain graphics backends enabled by default
    यदि (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    यदि (flags & SDL_WINDOW_OPENGL) {
        यदि (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            प्रत्यागम रिक्त;
        }
        यदि (!SDL_GL_LoadLibrary(रिक्त)) {
            प्रत्यागम रिक्त;
        }
    }

    यदि (flags & SDL_WINDOW_VULKAN) {
        यदि (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            प्रत्यागम रिक्त;
        }
        यदि (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            प्रत्यागम रिक्त;
        }
    }

    यदि (flags & SDL_WINDOW_METAL) {
        यदि (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            प्रत्यागम रिक्त;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, परिमाण(*window));
    यदि (!window) {
        प्रत्यागम रिक्त;
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
        SDL_धकेलो_Error();
        SDL_DestroyWindow(window);
        SDL_निकालो_Error();
        प्रत्यागम रिक्त;
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

    प्रत्यागम window;
}

SDL_Window *SDL_CreateWindow(ध्रुव वर्ण *title, पूर्णाङ्क w, पूर्णाङ्क h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    यदि (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, w);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, h);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    प्रत्यागम window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, पूर्णाङ्क offset_x, पूर्णाङ्क offset_y, पूर्णाङ्क w, पूर्णाङ्क h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    यदि (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        प्रत्यागम रिक्त;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_संख्या, offset_x);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_संख्या, offset_y);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, w);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, h);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    प्रत्यागम window;
}

स्थिर bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    यदि (!_this->ReconfigureWindow) {
        प्रत्यागम false;
    }

    ध्रुव SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    यदि (graphics_flags & (graphics_flags - 1)) {
        प्रत्यागम SDL_SetError("Conflicting window flags specified");
    }

    यदि ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        प्रत्यागम SDL_ContextNotSupported("OpenGL");
    }
    यदि ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        प्रत्यागम SDL_ContextNotSupported("Vulkan");
    }
    यदि ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        प्रत्यागम SDL_ContextNotSupported("Metal");
    }

    यदि (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        यदि (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            प्रत्यागम false;
        }
    } अन्यथा {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        यदि (!_this->ReconfigureWindow(_this, window, 0)) {
            प्रत्यागम false;
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
            प्रत्यागम false;
        }
    } अन्यथा यदि (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(रिक्त);
        यदि (!loaded_vulkan) {
            प्रत्यागम false;
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

        प्रत्यागम false;
    }

    window->flags |= graphics_flags;

    प्रत्यागम true;
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
        प्रत्यागम SDL_SetError("Conflicting window flags specified");
    }

    यदि ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        प्रत्यागम SDL_ContextNotSupported("OpenGL");
    }
    यदि ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        प्रत्यागम SDL_ContextNotSupported("Vulkan");
    }
    यदि ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        प्रत्यागम SDL_ContextNotSupported("Metal");
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
        ध्रुव bool restore_on_show = window->restore_on_show;
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
            प्रत्यागम false;
        }
        loaded_opengl = true;
    }

    यदि (need_vulkan_load) {
        यदि (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            प्रत्यागम false;
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
            प्रत्यागम false;
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

    प्रत्यागम true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    यदि (!SDL_ReconfigureWindowInternal(window, flags)) {
        प्रत्यागम SDL_RecreateWindow(window, flags);
    }

    प्रत्यागम true;
}

bool SDL_HasWindows(शून्य)
{
    प्रत्यागम _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    प्रत्यागम window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (id) {
        प्रति (window = _this->windows; window; window = window->next) {
            यदि (window->id == id) {
                प्रत्यागम window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    प्रत्यागम रिक्त;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    प्रत्यागम window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    यदि (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    प्रत्यागम window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    प्रत्यागम window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ध्रुव वर्ण *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (title == window->title) {
        प्रत्यागम true;
    }
    यदि (!title) {
        title = "";
    }
    यदि (window->title && SDL_strcmp(title, window->title) == 0) {
        प्रत्यागम true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    यदि (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    प्रत्यागम true;
}

ध्रुव वर्ण *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    प्रत्यागम window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        प्रत्यागम SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    यदि (!window->icon) {
        प्रत्यागम false;
    }

    यदि (!_this->SetWindowIcon) {
        प्रत्यागम SDL_Unsupported();
    }

    प्रत्यागम _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ध्रुव पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ध्रुव पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->windowed.h;

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
                प्रत्यागम false;
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
        ध्रुव bool result = _this->SetWindowPosition(_this, window);
        यदि (result) {
            SDL_SyncIfRequired(window);
        }
        प्रत्यागम result;
    }

    प्रत्यागम SDL_Unsupported();
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
        ध्रुव bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        यदि (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        यदि (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    प्रत्यागम true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->SetWindowBordered) {
        प्रत्यागम SDL_Unsupported();
    }

    ध्रुव bool want = bordered;
    ध्रुव bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    यदि (want != have) {
        यदि (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } अन्यथा {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    प्रत्यागम true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->SetWindowResizable) {
        प्रत्यागम SDL_Unsupported();
    }

    ध्रुव bool want = resizable;
    ध्रुव bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    यदि (want != have) {
        यदि (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    प्रत्यागम true;
}

bool SDL_Set_Window_Always_On_शीर्ष(SDL_Window *window, bool on_शीर्ष)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->Set_Window_Always_On_शीर्ष) {
        प्रत्यागम SDL_Unsupported();
    }

    ध्रुव bool want = on_शीर्ष;
    ध्रुव bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) != 0);
    यदि (want != have) {
        यदि (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_शीर्ष;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_शीर्ष;
        }
        _this->Set_Window_Always_On_शीर्ष(_this, window, want);
    }

    प्रत्यागम true;
}

bool SDL_SetWindowSize(SDL_Window *window, पूर्णाङ्क w, पूर्णाङ्क h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        प्रत्यागम SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        प्रत्यागम SDL_InvalidParamError("h");
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
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम true;
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
    प्रत्यागम true;
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
    प्रत्यागम SDL_SetWindowSize(window, w, h);
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
    प्रत्यागम true;
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
        प्रत्यागम SDL_Unsupported();
    }

    प्रत्यागम _this->GetWindowBordersSize(_this, window, शीर्ष, बायाँ, bottom, दायाँ);
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
        ध्रुव SDL_DisplayMode *mode;

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
    प्रत्यागम true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, पूर्णाङ्क min_w, पूर्णाङ्क min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        प्रत्यागम SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        प्रत्यागम SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        प्रत्यागम SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    यदि (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    प्रत्यागम SDL_SetWindowSize(window, w, h);
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
    प्रत्यागम true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, पूर्णाङ्क max_w, पूर्णाङ्क max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        प्रत्यागम SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        प्रत्यागम SDL_InvalidParamError("max_h");
    }

    यदि ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        प्रत्यागम SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    यदि (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    प्रत्यागम SDL_SetWindowSize(window, w, h);
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
    प्रत्यागम true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!(window->flags & SDL_WINDOW_HIDDEN)) {
        प्रत्यागम true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    यदि (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        प्रत्यागम true;
    }

    यदि (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } अन्यथा {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    प्रति (child = window->first_child; child; child = child->next_sibling) {
        यदि (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            भङ्ग;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    प्रत्यागम true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        प्रत्यागम true;
    }

    // Hide all child windows
    प्रति (child = window->first_child; child; child = child->next_sibling) {
        यदि (child->flags & SDL_WINDOW_HIDDEN) {
            भङ्ग;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ध्रुव SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
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
    प्रत्यागम true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        प्रत्यागम true;
    }
    यदि (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    प्रत्यागम true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->MaximizeWindow) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        प्रत्यागम SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        प्रत्यागम true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    प्रत्यागम true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->MinimizeWindow) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        प्रत्यागम true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    प्रत्यागम true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->RestoreWindow) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        प्रत्यागम true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    प्रत्यागम true;
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
        प्रत्यागम true;
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

    प्रत्यागम result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (_this->SyncWindow) {
        प्रत्यागम _this->SyncWindow(_this, window);
    } अन्यथा {
        प्रत्यागम true;
    }
}

स्थिर bool ShouldAttemptTextureFramebuffer(शून्य)
{
    ध्रुव वर्ण *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    यदि (!_this->CreateWindowFramebuffer) {
        प्रत्यागम true;
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
    प्रत्यागम attempt_texture_framebuffer;
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
            प्रत्यागम रिक्त;
        }

        यदि (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            प्रत्यागम रिक्त;
        }
    }

    यदि (window->surface) {
        // We may have gone recursive and already created the surface
        प्रत्यागम window->surface;
    }

    प्रत्यागम SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    प्रत्यागम window->surface ? true : false;
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
    प्रत्यागम window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, पूर्णाङ्क vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowFramebufferVSync) {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, पूर्णाङ्क *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->GetWindowFramebufferVSync) {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    प्रत्यागम SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ध्रुव SDL_Rect *rects,
                                 पूर्णाङ्क numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!window->surface_valid) {
        प्रत्यागम SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    प्रत्यागम _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
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
    प्रत्यागम true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, भिन्न opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowOpacity) {
        प्रत्यागम SDL_Unsupported();
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

    प्रत्यागम result;
}

भिन्न SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    प्रत्यागम window->opacity;
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
        प्रत्यागम SDL_SetError("Cannot set the parent of a window to itself.");
    }

    यदि (!_this->SetWindowParent) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (window->flags & SDL_WINDOW_MODAL) {
        प्रत्यागम SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    यदि (window->parent == parent) {
        प्रत्यागम true;
    }

    ध्रुव bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : रिक्त);

    प्रत्यागम ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (!_this->SetWindowModal) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (modal) {
        यदि (!window->parent) {
            प्रत्यागम SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } अन्यथा यदि (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } अन्यथा {
        प्रत्यागम true; // Already not modal, so nothing to do.
    }

    यदि (window->flags & SDL_WINDOW_HIDDEN) {
        प्रत्यागम true;
    }

    प्रत्यागम _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_निवेश_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    यावत् (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        यदि (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_निवेश_FOCUS);
        }
    }

    *new_focus = focus;
    प्रत्यागम set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    प्रति (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    प्रति (w = current_focus; w != toplevel_parent; w = w->parent) {
        यदि (w == window) {
            found_higher_focus = true;
            भङ्ग;
        }
    }

    प्रत्यागम !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ध्रुव bool want = (focusable != false); // normalize the flag.
    ध्रुव bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    यदि ((want != have) && (_this->SetWindowFocusable)) {
        यदि (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } अन्यथा {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        यदि (!_this->SetWindowFocusable(_this, window, want)) {
            प्रत्यागम false;
        }
    }

    प्रत्यागम true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ध्रुव bool want = (fill != false); // normalize the flag.
    ध्रुव bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    यदि ((want != have) && (_this->SetWindowFillDocument)) {
        यदि (!_this->SetWindowFillDocument(_this, window, want)) {
            प्रत्यागम false;
        } अन्यथा यदि (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    प्रत्यागम true;
}

शून्य SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    यदि (window->flags & SDL_WINDOW_निवेश_FOCUS) {
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
        प्रत्यागम true;
    }

    यदि (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        प्रत्यागम true;
    }
    यदि (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    यदि (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
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
        प्रत्यागम true;
    }

    यदि (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        प्रत्यागम true;
    }
    यदि (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    यदि (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    प्रत्यागम window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    प्रत्यागम window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(शून्य)
{
    यदि (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        प्रत्यागम _this->grabbed_window;
    } अन्यथा {
        प्रत्यागम रिक्त;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ध्रुव SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowMouseRect) {
        प्रत्यागम SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    यदि (!rect) {
        rect = &zero;
    }

    यदि (SDL_memcmp(&window->mouse_rect, rect, परिमाण(*rect)) == 0) {
        प्रत्यागम true;
    }
    SDL_memcpy(&window->mouse_rect, rect, परिमाण(*rect));

    प्रत्यागम _this->SetWindowMouseRect(_this, window);
}

ध्रुव SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    यदि (SDL_RectEmpty(&window->mouse_rect)) {
        प्रत्यागम रिक्त;
    } अन्यथा {
        प्रत्यागम &window->mouse_rect;
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
        प्रत्यागम true;
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
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (_this->FlashWindow) {
        प्रत्यागम _this->FlashWindow(_this, window, operation);
    }

    प्रत्यागम SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        प्रत्यागम SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    यदि (_this->ApplyWindowProgress) {
        यदि (!_this->ApplyWindowProgress(_this, window)) {
            प्रत्यागम false;
        }
    }

    प्रत्यागम true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    प्रत्यागम window->progress_state;
}

bool SDL_Set_Window_Progress_मूल्य(SDL_Window *window, भिन्न मूल्य)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    मूल्य = SDL_clamp(मूल्य, 0.0f, 1.f);

    window->progress_मूल्य = मूल्य;

    यदि (_this->ApplyWindowProgress) {
        यदि (!_this->ApplyWindowProgress(_this, window)) {
            प्रत्यागम false;
        }
    }

    प्रत्यागम true;
}

भिन्न SDL_Get_Window_Progress_मूल्य(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    प्रत्यागम window->progress_मूल्य;
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
        ध्रुव bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        यदि (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_ऊपरी_density_modes = false;

            यदि (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_ऊपरी_density_modes = true;
            }
            ध्रुव bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_ऊपरी_density_modes, &window->current_fullscreen_mode);

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
    प्रत्यागम true;
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
    ध्रुव वर्ण *hint;

    यदि (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        प्रत्यागम false;
    }

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    यदि (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        यदि (Cocoa_IsShowingModalDialog(window)) {
            प्रत्यागम false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } अन्यथा यदि (Cocoa_IsWindowInFullscreenSpace(window)) {
            प्रत्यागम false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        बाह्य bool Android_JNI_ShouldMinimizeOnFocusLoss(शून्य);
        यदि (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            प्रत्यागम false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    यदि (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        यदि (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            प्रत्यागम true;
        } अन्यथा {
            प्रत्यागम false;
        }
    }
    प्रत्यागम SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
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
        यावत् (focus->parent) {
            focus = focus->parent;
        }
    }

    प्रत्यागम focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->अंक_renderers + 1) * परिमाण(*renderers));
    यदि (!renderers) {
        प्रत्यागम false;
    }

    window->renderers = renderers;
    window->renderers[window->अंक_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    प्रत्यागम true;
}

शून्य SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    प्रति (पूर्णाङ्क i = 0; i < window->अंक_renderers; ++i) {
        यदि (window->renderers[i] == renderer) {
            यदि (i < (window->अंक_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->अंक_renderers - i - 1) * परिमाण(window->renderers[i]));
            }
            --window->अंक_renderers;
            भङ्ग;
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
    यावत् (window->first_child) {
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

    SDL_DestroyProperties(window->text_निवेश_props);

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
    प्रति (पूर्णाङ्क i = 0; i < _this->अंक_displays; ++i) {
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
        प्रत्यागम true;
    }
    प्रत्यागम !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(शून्य)
{
    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (!_this->suspend_screensaver) {
        प्रत्यागम true;
    }
    _this->suspend_screensaver = false;
    यदि (_this->SuspendScreenSaver) {
        प्रत्यागम _this->SuspendScreenSaver(_this);
    }

    प्रत्यागम SDL_Unsupported();
}

bool SDL_DisableScreenSaver(शून्य)
{
    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (_this->suspend_screensaver) {
        प्रत्यागम true;
    }
    _this->suspend_screensaver = true;
    यदि (_this->SuspendScreenSaver) {
        प्रत्यागम _this->SuspendScreenSaver(_this);
    }

    प्रत्यागम SDL_Unsupported();
}

शून्य SDL_QuitVideo(शून्य)
{
    पूर्णाङ्क i;

    यदि (!_this) {
        प्रत्यागम;
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
    यावत् (_this->windows) {
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

    प्रति (i = _this->अंक_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->अंक_displays == 0);
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

bool SDL_GL_LoadLibrary(ध्रुव वर्ण *path)
{
    bool result;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (_this->gl_config.driver_loaded) {
        यदि (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            प्रत्यागम SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } अन्यथा {
        यदि (!_this->GL_LoadLibrary) {
            प्रत्यागम SDL_DllNotSupported("OpenGL");
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
    प्रत्यागम result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ध्रुव वर्ण *proc)
{
    SDL_FunctionPointer func;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
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
    प्रत्यागम func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ध्रुव वर्ण *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    func = रिक्त;

    यदि (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } अन्यथा {
        SDL_SetError("No EGL library has been loaded");
    }

    प्रत्यागम func;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#endif
}

शून्य SDL_GL_UnloadLibrary(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम;
    }
    यदि (_this->gl_config.driver_loaded > 0) {
        यदि (--_this->gl_config.driver_loaded > 0) {
            प्रत्यागम;
        }
        यदि (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
प्रकारनिर्देश GLenum (APIENTRY* PFNGLGETERRORPROC) (शून्य);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
प्रकारनिर्देश ध्रुव GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
प्रकारनिर्देश ध्रुव GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

स्थिर SDL_INLINE bool isAtLeastGL3(ध्रुव वर्ण *verstr)
{
    प्रत्यागम verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ध्रुव वर्ण *extension)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ध्रुव वर्ण *extensions;
    ध्रुव वर्ण *start;
    ध्रुव वर्ण *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    यदि (where || *extension == '\0') {
        प्रत्यागम false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    यदि (start && *start == '0') {
        प्रत्यागम false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    यदि (!glGetStringFunc) {
        प्रत्यागम false;
    }

    यदि (isAtLeastGL3((ध्रुव वर्ण *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint अंक_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        यदि ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            प्रत्यागम false;
        }

#ifndef GL_अंक_EXTENSIONS
#define GL_अंक_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_अंक_EXTENSIONS, &अंक_exts);
        प्रति (i = 0; i < अंक_exts; i++) {
            ध्रुव वर्ण *thisext = (ध्रुव वर्ण *)glGetStringiFunc(GL_EXTENSIONS, i);
            यदि (SDL_strcmp(thisext, extension) == 0) {
                प्रत्यागम true;
            }
        }

        प्रत्यागम false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ध्रुव वर्ण *)glGetStringFunc(GL_EXTENSIONS);
    यदि (!extensions) {
        प्रत्यागम false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    प्रति (;;) {
        where = SDL_strstr(start, extension);
        यदि (!where) {
            भङ्ग;
        }

        terminator = where + SDL_strlen(extension);
        यदि (where == extensions || *(where - 1) == ' ') {
            यदि (*terminator == ' ' || *terminator == '\0') {
                प्रत्यागम true;
            }
        }

        start = terminator;
    }
    प्रत्यागम false;
#अन्यथा
    प्रत्यागम false;
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
        प्रत्यागम;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

शून्य SDL_GL_ResetAttributes(शून्य)
{
    यदि (!_this) {
        प्रत्यागम;
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
#नोचेद्यदि defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#नोचेद्यदि defined(SDL_VIDEO_OPENGL_ES)
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

bool SDL_GL_SetAttribute(SDL_GLAttr attr, पूर्णाङ्क मूल्य)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    result = true;
    विकल्प (attr) {
    पक्ष SDL_GL_RED_SIZE:
        _this->gl_config.red_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_STEREO:
        _this->gl_config.stereo = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_FLAGS:
        यदि (मूल्य & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", मूल्य);
            भङ्ग;
        }
        _this->gl_config.flags = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_PROFILE_MASK:
        यदि (मूल्य != 0 &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_CORE &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", मूल्य);
            भङ्ग;
        }
        _this->gl_config.profile_mask = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = मूल्य;
        भङ्ग;
    पक्ष SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = मूल्य;
        भङ्ग;
    स्वभाव:
        result = SDL_SetError("Unknown OpenGL attribute");
        भङ्ग;
    }
    प्रत्यागम result;
#अन्यथा
    प्रत्यागम SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, पूर्णाङ्क *मूल्य)
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

    CHECK_PARAM(!मूल्य) {
        प्रत्यागम SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *मूल्य = 0;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    विकल्प (attr) {
    पक्ष SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        भङ्ग;
    पक्ष SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        भङ्ग;
    पक्ष SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        भङ्ग;
    पक्ष SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        भङ्ग;
    पक्ष SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        भङ्ग;
#अन्यथा
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *मूल्य = _this->gl_config.double_buffer;
        प्रत्यागम true;
#endif
    पक्ष SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        भङ्ग;
    पक्ष SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        भङ्ग;
#ifdef SDL_VIDEO_OPENGL
    पक्ष SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        भङ्ग;
    पक्ष SDL_GL_STEREO:
        attrib = GL_STEREO;
        भङ्ग;
#अन्यथा
    पक्ष SDL_GL_ACCUM_RED_SIZE:
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
    पक्ष SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *मूल्य = 0;
        प्रत्यागम true;
#endif
    पक्ष SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        भङ्ग;
    पक्ष SDL_GL_BUFFER_SIZE:
    {
        पूर्णाङ्क rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        यदि (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            प्रत्यागम false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            प्रत्यागम false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            प्रत्यागम false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            प्रत्यागम false;
        }

        *मूल्य = rsize + gsize + bsize + asize;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *मूल्य = (_this->gl_config.accelerated != 0);
        प्रत्यागम true;
    }
    पक्ष SDL_GL_RETAINED_BACKING:
    {
        *मूल्य = _this->gl_config.retained_backing;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *मूल्य = _this->gl_config.major_version;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *मूल्य = _this->gl_config.minor_version;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_FLAGS:
    {
        *मूल्य = _this->gl_config.flags;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *मूल्य = _this->gl_config.profile_mask;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *मूल्य = _this->gl_config.share_with_current_context;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *मूल्य = _this->gl_config.framebuffer_srgb_capable;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
    {
        *मूल्य = _this->gl_config.no_error;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_EGL_PLATFORM:
    {
        *मूल्य = _this->gl_config.egl_platform;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_FLOATBUFFERS:
    {
        यदि (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            भङ्ग;
        } अन्यथा {
            प्रत्यागम 0;
        }
    }
    स्वभाव:
        प्रत्यागम SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    यदि (!glGetStringFunc) {
        प्रत्यागम false;
    }

    यदि (attachmentattrib && isAtLeastGL3((ध्रुव वर्ण *)glGetStringFunc(GL_VERSION))) {
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
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)मूल्य);
            } अन्यथा {
                *मूल्य = 0;
            }
            यदि (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } अन्यथा {
            प्रत्यागम false;
        }
    } अन्यथा
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        यदि (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)मूल्य);
        } अन्यथा {
            प्रत्यागम false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    यदि (!glGetErrorFunc) {
        प्रत्यागम false;
    }

    error = glGetErrorFunc();
    यदि (error != GL_NO_ERROR) {
        यदि (error == GL_INVALID_ENUM) {
            प्रत्यागम SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } अन्यथा यदि (error == GL_INVALID_मूल्य) {
            प्रत्यागम SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        प्रत्यागम SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    यदि (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *मूल्य = (*मूल्य == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    प्रत्यागम true;
#अन्यथा
    प्रत्यागम SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = रिक्त;
    CHECK_WINDOW_MAGIC(window, रिक्त);

    यदि (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        प्रत्यागम रिक्त;
    }

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    पूर्णाङ्क srgb_requested = -1;
    ध्रुव वर्ण *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
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
                supported = isAtLeastGL3((ध्रुव वर्ण *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            यदि (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    प्रत्यागम ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        प्रत्यागम true;
    }

    यदि (!context) {
        window = रिक्त;
    } अन्यथा यदि (window) {
        CHECK_WINDOW_MAGIC(window, false);

        यदि (!(window->flags & SDL_WINDOW_OPENGL)) {
            प्रत्यागम SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } अन्यथा यदि (!_this->gl_allow_no_surface) {
        प्रत्यागम SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    यदि (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, रिक्त);
        SDL_SetTLS(&_this->current_glctx_tls, context, रिक्त);
    }
    प्रत्यागम result;
}

SDL_Window *SDL_GL_GetCurrentWindow(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम EGL_NO_DISPLAY;
    }
    यदि (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        प्रत्यागम EGL_NO_DISPLAY;
    }
    प्रत्यागम _this->egl_data->egl_display;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->egl_data->egl_config;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        प्रत्यागम रिक्त;
    }
    यदि (_this->GL_GetEGLSurface) {
        प्रत्यागम _this->GL_GetEGLSurface(_this, window);
    }
    प्रत्यागम रिक्त;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#endif
}

bool SDL_GL_SetSwapInterval(पूर्णाङ्क interval)
{
    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    } अन्यथा यदि (SDL_GL_GetCurrentContext() == रिक्त) {
        प्रत्यागम SDL_SetError("No OpenGL context has been made current");
    } अन्यथा यदि (_this->GL_SetSwapInterval) {
        प्रत्यागम _this->GL_SetSwapInterval(_this, interval);
    } अन्यथा {
        प्रत्यागम SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(पूर्णाङ्क *interval)
{
    CHECK_PARAM(!interval) {
       प्रत्यागम SDL_InvalidParamError("interval");
    }

    *interval = 0;

    यदि (!_this) {
        प्रत्यागम SDL_SetError("no video driver");
    } अन्यथा यदि (SDL_GL_GetCurrentContext() == रिक्त) {
        प्रत्यागम SDL_SetError("no current context");
    } अन्यथा यदि (_this->GL_GetSwapInterval) {
        प्रत्यागम _this->GL_GetSwapInterval(_this, interval);
    } अन्यथा {
        प्रत्यागम SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!(window->flags & SDL_WINDOW_OPENGL)) {
        प्रत्यागम SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    यदि (SDL_GL_GetCurrentWindow() != window) {
        प्रत्यागम SDL_SetError("The specified window has not been made current");
    }

    प्रत्यागम _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        प्रत्यागम SDL_InvalidParamError("context");
    }

    यदि (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(रिक्त, रिक्त);
    }

    प्रत्यागम _this->GL_DestroyContext(_this, context);
}

#यदि 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
स्थिर शून्य Create_Mask_From_Color_कुंजी_Or_Alpha(SDL_Surface *icon, Uint8 *mask, पूर्णाङ्क flags)
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
            प्रति (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                प्रति (x = 0; x < icon->w; ++x) {
                    यदि (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        भङ्ग;

    पक्ष 2:
        {
            Uint16 *pixels;
            प्रति (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                प्रति (x = 0; x < icon->w; ++x) {
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
        भङ्ग;

    पक्ष 4:
        {
            Uint32 *pixels;
            प्रति (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                प्रति (x = 0; x < icon->w; ++x) {
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
        भङ्ग;
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
                प्रत्यागम;
            }
            SDL_memset(mask, ~0, mask_len);
            यदि (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            यदि (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            यदि (flags) {
                Create_Mask_From_Color_कुंजी_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } अन्यथा {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_निवेश_Type SDL_Get_Text_निवेश_Type(SDL_PropertiesID props)
{
    प्रत्यागम (SDL_Text_निवेश_Type)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_TYPE_संख्या, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_निवेश_Capitalization(SDL_PropertiesID props)
{
    यदि (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_संख्या)) {
        प्रत्यागम (SDL_Capitalization)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_संख्या, SDL_CAPITALIZE_NONE);
    }

    विकल्प (SDL_Get_Text_निवेश_Type(props)) {
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        प्रत्यागम SDL_CAPITALIZE_SENTENCES;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        प्रत्यागम SDL_CAPITALIZE_शब्दगण;
    स्वभाव:
        प्रत्यागम SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_निवेश_Autocorrect(SDL_PropertiesID props)
{
    प्रत्यागम SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_निवेश_Multiline(SDL_PropertiesID props)
{
    यदि (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        प्रत्यागम SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    यदि (SDL_GetHintBoolean(SDL_HINT_RETURN_कुंजी_HIDES_IME, false)) {
        प्रत्यागम false;
    } अन्यथा {
        प्रत्यागम true;
    }
}

स्थिर bool AutoShowingScreenKeyboard(शून्य)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    यदि (!hint) {
        // This hint is currently only used by the X11 video driver
        यदि (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    यदि (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम false;
    }
}

bool SDL_Start_Text_निवेश(SDL_Window *window)
{
    प्रत्यागम SDL_Start_Text_निवेश_With_Properties(window, 0);
}

bool SDL_Start_Text_निवेश_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->text_निवेश_props) {
        SDL_DestroyProperties(window->text_निवेश_props);
        window->text_निवेश_props = 0;
    }

    यदि (props) {
        window->text_निवेश_props = SDL_CreateProperties();
        यदि (!window->text_निवेश_props) {
            प्रत्यागम false;
        }
        यदि (!SDL_CopyProperties(props, window->text_निवेश_props)) {
            प्रत्यागम false;
        }
    }

    यदि (_this->Set_Text_निवेश_Properties) {
        _this->Set_Text_निवेश_Properties(_this, window, props);
    }

    यदि (!window->text_निवेश_active) {
        // Start the text input system
        यदि (_this->Start_Text_निवेश) {
            यदि (!_this->Start_Text_निवेश(_this, window, props)) {
                प्रत्यागम false;
            }
        }
        window->text_निवेश_active = true;
    }

    // Show the on-screen keyboard, if desired
    यदि (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        यदि (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    प्रत्यागम true;
}

bool SDL_Text_निवेश_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    प्रत्यागम window->text_निवेश_active;
}

bool SDL_Stop_Text_निवेश(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (window->text_निवेश_active) {
        // Stop the text input system
        यदि (_this->Stop_Text_निवेश) {
            _this->Stop_Text_निवेश(_this, window);
        }
        window->text_निवेश_active = false;
    }

    // Hide the on-screen keyboard, if desired
    यदि (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        यदि (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    प्रत्यागम true;
}

bool SDL_Set_Text_निवेश_Area(SDL_Window *window, ध्रुव SDL_Rect *rect, पूर्णाङ्क cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (rect) {
        SDL_copyp(&window->text_निवेश_rect, rect);
        window->text_निवेश_cursor = cursor;
    } अन्यथा {
        SDL_zero(window->text_निवेश_rect);
        window->text_निवेश_cursor = 0;
    }

    यदि (_this && _this->Update_Text_निवेश_Area) {
        यदि (!_this->Update_Text_निवेश_Area(_this, window)) {
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

bool SDL_Get_Text_निवेश_Area(SDL_Window *window, SDL_Rect *rect, पूर्णाङ्क *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (rect) {
        SDL_copyp(rect, &window->text_निवेश_rect);
    }
    यदि (cursor) {
        *cursor = window->text_निवेश_cursor;
    }
    प्रत्यागम true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (_this->ClearComposition) {
        प्रत्यागम _this->ClearComposition(_this, window);
    }
    प्रत्यागम true;
}

bool SDL_HasScreenKeyboardSupport(शून्य)
{
    यदि (_this && _this->HasScreenKeyboardSupport) {
        प्रत्यागम _this->HasScreenKeyboardSupport(_this);
    }
    प्रत्यागम false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    प्रत्यागम _this->screen_keyboard_shown;
}

शून्य SDL_SendScreenKeyboardShown(शून्य)
{
    यदि (!_this || _this->screen_keyboard_shown) {
        प्रत्यागम;
    }

    _this->screen_keyboard_shown = true;

    यदि (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_धकेलो_Event(&event);
    }
}

शून्य SDL_SendScreenKeyboardHidden(शून्य)
{
    यदि (!_this || !_this->screen_keyboard_shown) {
        प्रत्यागम;
    }

    _this->screen_keyboard_shown = false;

    यदि (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_धकेलो_Event(&event);
    }
}

पूर्णाङ्क SDL_Get_Message_Box_गिनती(शून्य)
{
    प्रत्यागम SDL_GetAtomicInt(&SDL_messagebox_गिनती);
}

bool SDL_ShowMessageBox(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    पूर्णाङ्क dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        प्रत्यागम SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        प्रत्यागम SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    वर्ण *titlecpy = रिक्त;
    वर्ण *msgcpy = रिक्त;
    यदि (messageboxdata->title) {
        ध्रुव माप_प्रकार slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(वर्ण, slen, &titleisstack);
        यदि (!titlecpy) {
            प्रत्यागम false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    यदि (messageboxdata->message) {
        ध्रुव माप_प्रकार slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(वर्ण, slen, &msgisstack);
        यदि (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            प्रत्यागम false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (शून्य)SDL_AtomicIncRef(&SDL_messagebox_गिनती);

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
        ध्रुव वर्ण *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        यदि (driver_name && *driver_name != 0) {
            ध्रुव वर्ण *driver_attempt = driver_name;
            यावत् (driver_attempt && (*driver_attempt != 0) && !result) {
                ध्रुव वर्ण *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                प्रति (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                    यदि (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        यदि (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        भङ्ग;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
            }
        } अन्यथा {
            प्रति (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                यदि (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    भङ्ग;
                }
            }
        }
    }

    यदि (!result) {
        ध्रुव वर्ण *error = SDL_GetError();

        यदि (!*error) {
            SDL_SetError("No message system available");
        }
    } अन्यथा {
        SDL_ClearError();
    }

    (शून्य)SDL_AtomicDecRef(&SDL_messagebox_गिनती);

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

    प्रत्यागम result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ध्रुव वर्ण *title, ध्रुव वर्ण *message, SDL_Window *window)
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

    प्रत्यागम true;
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

    प्रत्यागम SDL_ShowMessageBox(&data, रिक्त);
#endif
}

bool SDL_ShouldAllowTopmost(शून्य)
{
    प्रत्यागम SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    यदि (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        प्रत्यागम true;
    }

    प्रत्यागम SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, शून्य *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->SetWindowHitTest) {
        प्रत्यागम SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    प्रत्यागम _this->SetWindowHitTest(window, callback != रिक्त);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    यदि (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        प्रत्यागम SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    यदि (!props) {
        प्रत्यागम false;
    }

    यदि (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        यदि (!surface) {
            प्रत्यागम false;
        }
    } अन्यथा {
        surface = रिक्त;
    }

    यदि (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        प्रत्यागम false;
    }

    यदि (_this->UpdateWindowShape) {
        यदि (!_this->UpdateWindowShape(_this, window, surface)) {
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
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
    SDL_SendAppEvent(SDL_EVENT_निचला_MEMORY);
}

शून्य SDL_OnApplicationWillEnterBackground(शून्य)
{
    यदि (_this) {
        SDL_Window *window;
        प्रति (window = _this->windows; window; window = window->next) {
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
        प्रति (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ध्रुव वर्ण *path)
{
    bool result;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (_this->vulkan_config.loader_loaded) {
        यदि (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            प्रत्यागम SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } अन्यथा {
        यदि (!_this->Vulkan_LoadLibrary) {
            प्रत्यागम SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    यदि (result) {
        _this->vulkan_config.loader_loaded++;
    }
    प्रत्यागम result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        प्रत्यागम रिक्त;
    }
    प्रत्यागम (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

शून्य SDL_Vulkan_UnloadLibrary(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम;
    }
    यदि (_this->vulkan_config.loader_loaded > 0) {
        यदि (--_this->vulkan_config.loader_loaded > 0) {
            प्रत्यागम;
        }
        यदि (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

वर्ण ध्रुव * ध्रुव *SDL_Vulkan_GetInstanceExtensions(Uint32 *गिनती)
{
    Uint32 tmpcount = 0;
    यदि (!गिनती) {
        गिनती = &tmpcount;
    }

    यदि (!_this->Vulkan_GetInstanceExtensions) {
        *गिनती = 0;
        SDL_Unsupported();
        प्रत्यागम रिक्त;
    }

    प्रत्यागम _this->Vulkan_GetInstanceExtensions(_this, गिनती);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ध्रुव संरचना VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    यदि (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        प्रत्यागम false;
    }

    CHECK_PARAM(!instance) {
        प्रत्यागम SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        प्रत्यागम SDL_InvalidParamError("surface");
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
            प्रत्यागम SDL_SetError("failed to load Vulkan library");
        }
    }

    प्रत्यागम _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

शून्य SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ध्रुव संरचना VkAllocationCallbacks *allocator)
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
        प्रत्यागम false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        प्रत्यागम false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        प्रत्यागम false;
    }

    यदि (_this->Vulkan_GetPresentationSupport) {
        प्रत्यागम _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    प्रत्यागम true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    यदि (!_this->Metal_CreateView) {
        SDL_Unsupported();
        प्रत्यागम रिक्त;
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

    प्रत्यागम _this->Metal_CreateView(_this, window);
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
            प्रत्यागम रिक्त;
        }
        प्रत्यागम _this->Metal_GetLayer(_this, view);
    } अन्यथा {
        SDL_SetError("Metal is not supported.");
        प्रत्यागम रिक्त;
    }
}

#यदि defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ध्रुव वर्ण *SDL_GetCSSCursorName(SDL_SystemCursor id, ध्रुव वर्ण **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    विकल्प (id) {
    पक्ष SDL_SYSTEM_CURSOR_DEFAULT:
        प्रत्यागम "default";

    पक्ष SDL_SYSTEM_CURSOR_TEXT:
        प्रत्यागम "text";

    पक्ष SDL_SYSTEM_CURSOR_WAIT:
        प्रत्यागम "wait";

    पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR:
        प्रत्यागम "crosshair";

    पक्ष SDL_SYSTEM_CURSOR_PROGRESS:
        प्रत्यागम "progress";

    पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        यदि (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        प्रत्यागम "nwse-resize";

    पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE:
        यदि (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        प्रत्यागम "nesw-resize";

    पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE:
        यदि (fallback_name) {
            *fallback_name = "col-resize";
        }
        प्रत्यागम "ew-resize";

    पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE:
        यदि (fallback_name) {
            *fallback_name = "row-resize";
        }
        प्रत्यागम "ns-resize";

    पक्ष SDL_SYSTEM_CURSOR_MOVE:
        यदि (fallback_name) {
            *fallback_name = "all-scroll";
        }
        प्रत्यागम "move";

    पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        प्रत्यागम "not-allowed";

    पक्ष SDL_SYSTEM_CURSOR_POINTER:
        प्रत्यागम "pointer";

    पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE:
        प्रत्यागम "nw-resize";

    पक्ष SDL_SYSTEM_CURSOR_N_RESIZE:
        प्रत्यागम "n-resize";

    पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE:
        प्रत्यागम "ne-resize";

    पक्ष SDL_SYSTEM_CURSOR_E_RESIZE:
        प्रत्यागम "e-resize";

    पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE:
        प्रत्यागम "se-resize";

    पक्ष SDL_SYSTEM_CURSOR_S_RESIZE:
        प्रत्यागम "s-resize";

    पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE:
        प्रत्यागम "sw-resize";

    पक्ष SDL_SYSTEM_CURSOR_W_RESIZE:
        प्रत्यागम "w-resize";

    पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        प्रत्यागम "context-menu";

    पक्ष SDL_SYSTEM_CURSOR_HELP:
        प्रत्यागम "help";

    पक्ष SDL_SYSTEM_CURSOR_CELL:
        प्रत्यागम "cell";

    पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        प्रत्यागम "vertical-text";

    पक्ष SDL_SYSTEM_CURSOR_ALIAS:
        प्रत्यागम "alias";

    पक्ष SDL_SYSTEM_CURSOR_COPY:
        प्रत्यागम "copy";

    पक्ष SDL_SYSTEM_CURSOR_NO_DROP:
        प्रत्यागम "no-drop";

    पक्ष SDL_SYSTEM_CURSOR_GRAB:
        प्रत्यागम "grab";

    पक्ष SDL_SYSTEM_CURSOR_GRABBING:
        प्रत्यागम "grabbing";

    पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE:
        प्रत्यागम "col-resize";

    पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE:
        प्रत्यागम "row-resize";

    पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL:
        यदि (fallback_name) {
            *fallback_name = "move";
        }
        प्रत्यागम "all-scroll";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_IN:
        प्रत्यागम "zoom-in";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_OUT:
        प्रत्यागम "zoom-out";

    स्वभाव:
        प्रत्यागम "default";
    }
}
#endif

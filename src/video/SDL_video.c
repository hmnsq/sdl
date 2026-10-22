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

#सचे defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#अन्तर्भाव <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#सचे defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
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
#ifdef SDL_निवेशः_LINUXEV
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
        पटिनिवत्त result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        पटिनिवत्त result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        पटिनिवत्त result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        पटिनिवत्त result;                                                  \
    }

#सचे defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
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
    सचे (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

स्थिर bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    पटिनिवत्त !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

स्थिर bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    पटिनिवत्त !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

स्थिर bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    पटिनिवत्त !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

स्थिर bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    पटिनिवत्त !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

स्थिर bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    पटिनिवत्त !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
स्थिर bool syncHint;

स्थिर शून्य SDL_SyncHintWatcher(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    syncHint = SDL_GetStringBoolean(new_मानम्, false);
}

स्थिर शून्य SDL_SyncIfRequired(SDL_Window *window)
{
    सचे (syncHint) {
        SDL_SyncWindow(window);
    }
}

स्थिर शून्य SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    सचे (window->parent) {
        सचे (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        सचे (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } अञ्ञथा {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = रिक्त;
    }

    सचे (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        सचे (parent->first_child) {
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
#सचे (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    सचे (_this->GL_CreateContext) {
        पटिनिवत्त SDL_WINDOW_OPENGL;
    }
#endif
#सचे defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    सचे (_this->Metal_CreateView) {
        पटिनिवत्त SDL_WINDOW_METAL;
    }
#endif
#सचे defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    सचे (SDL_strcmp(_this->name, "openvr") == 0) {
        पटिनिवत्त SDL_WINDOW_OPENGL;
    }
#endif
    पटिनिवत्त 0;
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

    सचे (!data) {
        SDL_Renderer *renderer = रिक्त;
        ध्रुव वर्ण *render_driver = रिक्त;

        // See if there's a render driver being requested
        ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        सचे (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        सचे (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        सचे (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = रिक्त;
        }

        वर्ण *render_driver_copy = रिक्त;
        सचे (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            सचे (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                वर्ण *prev = render_driver_copy;
                वर्ण *ptr = prev;
                याव ((ptr = SDL_strchr(ptr, ',')) != रिक्त) {
                    *ptr = '\0';
                    ध्रुव bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    सचे (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } अञ्ञथा {
                        ptr++;
                        prev = ptr;
                    }
                }

                सचे (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        सचे (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            सचे (!renderer) {
                // The error for this specific renderer has already been set
                पटिनिवत्त false;
            }
        } अञ्ञथा {
            SDL_assert(render_driver_copy == रिक्त);
            ध्रुव पूर्णाङ्क total = SDL_Get_अङ्कः_Render_Drivers();
            अत्थाय (i = 0; i < total; ++i) {
                ध्रुव वर्ण *name = SDL_GetRenderDriver(i);
                सचे (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    सचे (renderer) {
                        भङ्ग; // this will work.
                    }
                }
            }
            सचे (!renderer) {
                पटिनिवत्त SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != रिक्त); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, परिमाण(*data));
        सचे (!data) {
            SDL_DestroyRenderer(renderer);
            पटिनिवत्त false;
        }
        सचे (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            पटिनिवत्त false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ध्रुव SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, रिक्त);
    सचे (!texture_formats) {
        पटिनिवत्त false;
    }

    // Free any old texture and pixel data
    सचे (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = रिक्त;
    }
    SDL_free(data->pixels);
    data->pixels = रिक्त;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    अत्थाय (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        सचे (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
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
    सचे (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        पटिनिवत्त false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ध्रुव size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        सचे (!data->pixels) {
            पटिनिवत्त false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, रिक्त);

    पटिनिवत्त true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    सचे (!data) {
        पटिनिवत्त false;
    }
    सचे (!data->renderer) {
        पटिनिवत्त false;
    }
    पटिनिवत्त SDL_SetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    सचे (!data) {
        पटिनिवत्त false;
    }
    सचे (!data->renderer) {
        पटिनिवत्त false;
    }
    पटिनिवत्त SDL_GetRenderVSync(data->renderer, vsync);
}

स्थिर bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    शून्य *src;
    पूर्णाङ्क w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);
    सचे (!data || !data->texture) {
        पटिनिवत्त SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    सचे (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (शून्य *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        सचे (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            पटिनिवत्त false;
        }

        सचे (!SDL_RenderTexture(data->renderer, data->texture, रिक्त, रिक्त)) {
            पटिनिवत्त false;
        }

        SDL_RenderPresent(data->renderer);
    }
    पटिनिवत्त true;
}

स्थिर शून्य SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    सचे (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, रिक्त);

        सचे (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        सचे (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

स्थिर SDL_VideoDevice *_this = रिक्त;
स्थिर SDL_AtomicInt SDL_messagebox_गणनम्;

स्थिर पूर्णाङ्क SDLCALL cmpmodes(ध्रुव शून्य *A, ध्रुव शून्य *B)
{
    ध्रुव SDL_DisplayMode *a = (ध्रुव SDL_DisplayMode *)A;
    ध्रुव SDL_DisplayMode *b = (ध्रुव SDL_DisplayMode *)B;
    पूर्णाङ्क a_refresh_rate = (पूर्णाङ्क)(a->refresh_rate * 100);
    पूर्णाङ्क b_refresh_rate = (पूर्णाङ्क)(b->refresh_rate * 100);
    पूर्णाङ्क a_pixel_density = (पूर्णाङ्क)(a->pixel_density * 100);
    पूर्णाङ्क b_pixel_density = (पूर्णाङ्क)(b->pixel_density * 100);

    सचे (a->w != b->w) {
        पटिनिवत्त b->w - a->w;
    } अञ्ञथा सचे (a->h != b->h) {
        पटिनिवत्त b->h - a->h;
    } अञ्ञथा सचे (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        पटिनिवत्त SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } अञ्ञथा सचे (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        पटिनिवत्त SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } अञ्ञथा सचे (a_refresh_rate != b_refresh_rate) {
        पटिनिवत्त b_refresh_rate - a_refresh_rate;
    } अञ्ञथा सचे (a_pixel_density != b_pixel_density) {
        पटिनिवत्त a_pixel_density - b_pixel_density;
    }
    पटिनिवत्त 0;
}

bool SDL_UninitializedVideo(शून्य)
{
    पटिनिवत्त SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
स्थिर ध्रुव VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

पूर्णाङ्क SDL_Get_अङ्कः_Video_Drivers(शून्य)
{
    स्थिर पूर्णाङ्क अङ्कः_drivers = -1;

    सचे (अङ्कः_drivers >= 0) {
        पटिनिवत्त अङ्कः_drivers;
    }

    अङ्कः_drivers = 0;

    // Build a list of unique video drivers.
    अत्थाय (पूर्णाङ्क i = 0; bootstrap[i] != रिक्त; ++i) {
        bool duplicate = false;
        अत्थाय (पूर्णाङ्क j = 0; j < i; ++j) {
            सचे (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                भङ्ग;
            }
        }

        सचे (!duplicate) {
            deduped_bootstrap[अङ्कः_drivers++] = bootstrap[i];
        }
    }

    पटिनिवत्त अङ्कः_drivers;
}

ध्रुव वर्ण *SDL_GetVideoDriver(पूर्णाङ्क index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_अङ्कः_Video_Drivers()) {
        SDL_InvalidParamError("index");
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त deduped_bootstrap[index]->name;
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
    सचे (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    सचे (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        गच्छ pre_driver_error;
    }
    init_events = true;
    सचे (!SDL_InitKeyboard()) {
        गच्छ pre_driver_error;
    }
    init_keyboard = true;
    सचे (!SDL_PreInitMouse()) {
        गच्छ pre_driver_error;
    }
    init_mouse = true;
    सचे (!SDL_InitTouch()) {
        गच्छ pre_driver_error;
    }
    init_touch = true;
    सचे (!SDL_InitPen()) {
        गच्छ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = रिक्त;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    सचे (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    सचे (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    सचे (driver_name && *driver_name != 0) {
        ध्रुव वर्ण *driver_attempt = driver_name;
        याव (driver_attempt && *driver_attempt != 0 && !video) {
            ध्रुव वर्ण *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            अत्थाय (i = 0; bootstrap[i]; ++i) {
                सचे (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    सचे (video) {
                        भङ्ग;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
        }
    } अञ्ञथा {
        अत्थाय (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            सचे (video) {
                भङ्ग;
            }
        }
    }
    सचे (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } अञ्ञथा {
        सचे (driver_name) {
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
    सचे (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        पटिनिवत्त false;
    }

    // Make sure some displays were added
    सचे (_this->अङ्कः_displays == 0) {
        SDL_QuitVideo();
        पटिनिवत्त SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, रिक्त);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    सचे (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    पटिनिवत्त true;

pre_driver_error:
    SDL_assert(_this == रिक्त);
    सचे (init_pen) {
        SDL_QuitPen();
    }
    सचे (init_touch) {
        SDL_QuitTouch();
    }
    सचे (init_mouse) {
        SDL_QuitMouse();
    }
    सचे (init_keyboard) {
        SDL_QuitKeyboard();
    }
    सचे (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    पटिनिवत्त false;
}

ध्रुव वर्ण *SDL_GetCurrentVideoDriver(शून्य)
{
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(शून्य)
{
    पटिनिवत्त _this;
}

bool SDL_OnVideoThread(शून्य)
{
    पटिनिवत्त (_this && SDL_GetCurrentThreadID() == _this->thread);
}

शून्य SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    सचे (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(शून्य)
{
    सचे (_this) {
        पटिनिवत्त _this->system_theme;
    } अञ्ञथा {
        पटिनिवत्त SDL_SYSTEM_THEME_UNKNOWN;
    }
}

शून्य SDL_UpdateDesktopBounds(शून्य)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    सचे (displays) {
        अत्थाय (पूर्णाङ्क i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            सचे (SDL_GetDisplayBounds(displays[i], &bounds)) {
                सचे (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } अञ्ञथा {
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
    सचे (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    सचे (mode->refresh_rate_numerator > 0) {
        सचे (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (भिन्न)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } अञ्ञथा {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ध्रुव SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    सचे (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, परिमाण(display.desktop_mode));
    }
    पटिनिवत्त SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ध्रुव SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    पूर्णाङ्क i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(परिमाण(*new_display));
    सचे (!new_display) {
        पटिनिवत्त 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->अङ्कः_displays + 1) * परिमाण(*displays));
    सचे (!displays) {
        SDL_free(new_display);
        पटिनिवत्त 0;
    }
    _this->displays = displays;
    _this->displays[_this->अङ्कः_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    सचे (display->name) {
        new_display->name = SDL_strdup(display->name);
    } अञ्ञथा {
        वर्ण name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    सचे (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    अत्थाय (i = 0; i < new_display->अङ्कः_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    सचे (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    पटिनिवत्त id;
}

शून्य SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    अत्थाय (window = _this->windows; window; window = window->next) {
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
    सचे (display_index < 0) {
        पटिनिवत्त;
    }

    display = _this->displays[display_index];

    सचे (send_event) {
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

    सचे (display_index < (_this->अङ्कः_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->अङ्कः_displays - display_index - 1) * परिमाण(_this->displays[display_index]));
    }
    --_this->अङ्कः_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क i;
    SDL_DisplayID *displays;

    सचे (!_this) {
        सचे (गणनम्) {
            *गणनम् = 0;
        }

        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->अङ्कः_displays + 1) * परिमाण(*displays));
    सचे (displays) {
        सचे (गणनम्) {
            *गणनम् = _this->अङ्कः_displays;
        }

        अत्थाय (i = 0; i < _this->अङ्कः_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } अञ्ञथा {
        सचे (गणनम्) {
            *गणनम् = 0;
        }
    }
    पटिनिवत्त displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    सचे (display_index < 0) {
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त _this->displays[display_index];
}

स्थिर SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    सचे (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    पटिनिवत्त displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    पटिनिवत्त SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(शून्य)
{
    सचे (!_this || _this->अङ्कः_displays == 0) {
        SDL_UninitializedVideo();
        पटिनिवत्त 0;
    }
    पटिनिवत्त _this->displays[0]->id;
}

पूर्णाङ्क SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_index;

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त -1;
    }

    अत्थाय (display_index = 0; display_index < _this->अङ्कः_displays; ++display_index) {
        सचे (displayID == _this->displays[display_index]->id) {
            पटिनिवत्त display_index;
        }
    }
    SDL_SetError("Invalid display");
    पटिनिवत्त -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    पटिनिवत्त display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    पटिनिवत्त SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    सचे (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    पटिनिवत्त display->props;
}

ध्रुव वर्ण *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    पटिनिवत्त display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        पटिनिवत्त SDL_InvalidParamError("rect");
    }

    सचे (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        सचे (_this->GetDisplayBounds(_this, display, rect)) {
            पटिनिवत्त true;
        }
    }

    // Assume that the displays are left to right
    सचे (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } अञ्ञथा {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    पटिनिवत्त true;
}

स्थिर पूर्णाङ्क ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    पटिनिवत्त hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        पटिनिवत्त SDL_InvalidParamError("rect");
    }

    सचे (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        पटिनिवत्त true;
    }

    सचे (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        सचे (_this->GetDisplayUsableBounds(_this, display, rect)) {
            पटिनिवत्त true;
        }
    }

    // Oh well, just give the entire display bounds.
    पटिनिवत्त SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    सचे (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        पटिनिवत्त display->natural_orientation;
    } अञ्ञथा {
        // Default to landscape if the driver hasn't set it
        पटिनिवत्त SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    सचे (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        पटिनिवत्त display->current_orientation;
    } अञ्ञथा {
        // Default to landscape if the driver hasn't set it
        पटिनिवत्त SDL_ORIENTATION_LANDSCAPE;
    }
}

शून्य SDL_SetDisplayContentScale(SDL_VideoDisplay *display, भिन्न scale)
{
    सचे (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        अत्थाय (window = _this->windows; window; window = window->next) {
            सचे (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

भिन्न SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    पटिनिवत्त display->content_scale;
}

शून्य SDL_SetWindowHDRProperties(SDL_Window *window, ध्रुव SDL_HDROutputProperties *HDR, bool send_event)
{
    ध्रुव SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    सचे (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        सचे (send_event) {
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

	सचे (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    सचे (changed && !SDL_DriverSendsHDRChanges(_this)) {
        अत्थाय (SDL_Window *w = display->device->windows; w; w = w->next) {
            सचे (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

स्थिर शून्य SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    सचे (display->अङ्कः_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
स्थिर ध्रुव SDL_DisplayMode *SDL_GetFullscreenModeMatch(ध्रुव SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    सचे (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        पटिनिवत्त रिक्त;
    }

    SDL_memcpy(&fullscreen_mode, mode, परिमाण(fullscreen_mode));
    सचे (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = रिक्त;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    सचे (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        सचे (!mode) {
            अत्थाय (पूर्णाङ्क i = 0; i < display->अङ्कः_fullscreen_modes; ++i) {
                सचे (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], परिमाण(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    भङ्ग;
                }
            }
        }

        // Search for a mode with the same characteristics
        सचे (!mode) {
            अत्थाय (पूर्णाङ्क i = 0; i < display->अङ्कः_fullscreen_modes; ++i) {
                सचे (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    भङ्ग;
                }
            }
        }
    }
    पटिनिवत्त mode;
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
    nmodes = display->अङ्कः_fullscreen_modes;
    अत्थाय (i = 0; i < nmodes; ++i) {
        सचे (cmpmodes(&new_mode, &modes[i]) == 0) {
            पटिनिवत्त false;
        }
    }

    // Go ahead and add the new mode
    सचे (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * परिमाण(*modes));
        सचे (!modes) {
            पटिनिवत्त false;
        }

        सचे (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * परिमाण(*modes));
            अत्थाय (i = 0; i < nmodes; ++i) {
                सचे (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->अङ्कः_fullscreen_modes++], &new_mode, परिमाण(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->अङ्कः_fullscreen_modes,
              परिमाण(SDL_DisplayMode), cmpmodes);

    पटिनिवत्त true;
}

शून्य SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    पूर्णाङ्क i;

    अत्थाय (i = display->अङ्कः_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = रिक्त;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = रिक्त;
    display->अङ्कः_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क i;
    पूर्णाङ्क अङ्कः_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    सचे (गणनम्) {
        *गणनम् = 0;
    }

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    SDL_UpdateFullscreenDisplayModes(display);

    अङ्कः_modes = display->अङ्कः_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((अङ्कः_modes + 1) * परिमाण(*result) + अङ्कः_modes * परिमाण(**result));
    सचे (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((अङ्कः_modes + 1) * परिमाण(*result)));
        सचे (अङ्कः_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, अङ्कः_modes * परिमाण(*modes));
        }
        अत्थाय (i = 0; i < अङ्कः_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = रिक्त;

        सचे (गणनम्) {
            *गणनम् = अङ्कः_modes;
        }
    } अञ्ञथा {
        सचे (गणनम्) {
            *गणनम् = 0;
        }
    }
    पटिनिवत्त result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, पूर्णाङ्क w, पूर्णाङ्क h, भिन्न refresh_rate, bool include_उच्चः_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        पटिनिवत्त SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ध्रुव SDL_DisplayMode *mode, *closest = रिक्त;
    भिन्न aspect_ratio;
    पूर्णाङ्क i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    सचे (h > 0) {
        aspect_ratio = (भिन्न)w / h;
    } अञ्ञथा {
        aspect_ratio = 1.0f;
    }

    सचे (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    अत्थाय (i = 0; i < display->अङ्कः_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        सचे (w > mode->w) {
            // Out of sorted modes large enough here
            भङ्ग;
        }
        सचे (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            अनुवर्त;
        }
        सचे (mode->pixel_density > 1.0f && !include_उच्चः_density_modes) {
            अनुवर्त;
        }
        सचे (closest) {
            भिन्न current_aspect_ratio = (भिन्न)mode->w / mode->h;
            भिन्न closest_aspect_ratio = (भिन्न)closest->w / closest->h;
            सचे (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                अनुवर्त;
            }

            सचे (mode->w == closest->w && mode->h == closest->h) {
                सचे (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    अनुवर्त;
                }
                सचे (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    अनुवर्त;
                }
            }
        }

        closest = mode;
    }
    सचे (!closest) {
        पटिनिवत्त SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    पटिनिवत्त true;
}

स्थिर bool DisplayModeChanged(ध्रुव SDL_DisplayMode *old_mode, ध्रुव SDL_DisplayMode *new_mode)
{
    पटिनिवत्त ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

शून्य SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    सचे (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        पटिनिवत्त;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    सचे (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        सचे (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ध्रुव SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    पटिनिवत्त &display->desktop_mode;
}

शून्य SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ध्रुव SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    सचे (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } अञ्ञथा {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    सचे (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ध्रुव SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    पटिनिवत्त display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    सचे (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        पटिनिवत्त true;
    }

    सचे (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    सचे (mode == display->current_mode) {
        पटिनिवत्त true;
    }
#endif

    // Actually change the display mode
    सचे (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        सचे (!result) {
            पटिनिवत्त false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    पटिनिवत्त true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
स्थिर शून्य SDL_GetClosestPointOnRect(ध्रुव SDL_Rect *rect, SDL_Point *point)
{
    ध्रुव पूर्णाङ्क दक्षिणः = rect->x + rect->w - 1;
    ध्रुव पूर्णाङ्क bottom = rect->y + rect->h - 1;

    सचे (point->x < rect->x) {
        point->x = rect->x;
    } अञ्ञथा सचे (point->x > दक्षिणः) {
        point->x = दक्षिणः;
    }

    सचे (point->y < rect->y) {
        point->y = rect->y;
    } अञ्ञथा सचे (point->y > bottom) {
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

    सचे (_this) {
        अत्थाय (i = 0; i < _this->अङ्कः_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            सचे (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, रिक्त)) {
                पटिनिवत्त display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            सचे (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    सचे (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    पटिनिवत्त closest;
}

शून्य SDL_RelativeToGlobalForWindow(SDL_Window *window, पूर्णाङ्क rel_x, पूर्णाङ्क rel_y, पूर्णाङ्क *abs_x, पूर्णाङ्क *abs_y)
{
    SDL_Window *w;

    सचे (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        अत्थाय (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            सचे (!SDL_WINDOW_IS_POPUP(w)) {
                भङ्ग;
            }
        }
    }

    सचे (abs_x) {
        *abs_x = rel_x;
    }
    सचे (abs_y) {
        *abs_y = rel_y;
    }
}

शून्य SDL_GlobalToRelativeForWindow(SDL_Window *window, पूर्णाङ्क abs_x, पूर्णाङ्क abs_y, पूर्णाङ्क *rel_x, पूर्णाङ्क *rel_y)
{
    SDL_Window *w;

    सचे (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        अत्थाय (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            सचे (!SDL_WINDOW_IS_POPUP(w)) {
                भङ्ग;
            }
        }
    }

    सचे (rel_x) {
        *rel_x = abs_x;
    }
    सचे (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ध्रुव SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        पटिनिवत्त 0;
    }

    पटिनिवत्त GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ध्रुव SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        पटिनिवत्त 0;
    }

    पटिनिवत्त GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

स्थिर SDL_DisplayID GetDisplayAtOrigin(पूर्णाङ्क x, पूर्णाङ्क y)
{
    अत्थाय (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
        SDL_Rect rect;
        ध्रुव SDL_DisplayID cur_id = _this->displays[i]->id;
        सचे (SDL_GetDisplayBounds(cur_id, &rect)) {
            सचे (x == rect.x && y == rect.y) {
                पटिनिवत्त cur_id;
            }
        }
    }

    पटिनिवत्त 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    पूर्णाङ्क x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    सचे (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    सचे (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } अञ्ञथा {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    सचे (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    पटिनिवत्त displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, रिक्त);

    // An explicit fullscreen display overrides all
    सचे (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    सचे (!displayID) {
        displayID = window->pending_displayID;
    }
    सचे (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ध्रुव पूर्णाङ्क x = window->last_position_pending ? window->pending.x : window->x;
        ध्रुव पूर्णाङ्क y = window->last_position_pending ? window->pending.y : window->y;
        ध्रुव पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->w;
        ध्रुव पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        सचे (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    सचे (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    पटिनिवत्त SDL_GetVideoDisplay(displayID);
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
    सचे (fs_display) {
        SDL_Set_सङ्ख्या_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } अञ्ञथा {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    पटिनिवत्त GetDisplayForWindow(window);
}

स्थिर शून्य SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    सचे (SDL_SendsDisplayChanges(_this)) {
        पटिनिवत्त;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    सचे (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        सचे (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            सचे (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                पूर्णाङ्क old_area = old_overlap.w * old_overlap.h;
                पूर्णाङ्क new_area = new_overlap.w * new_overlap.h;
                भिन्न new_overlap_ratio = (new_area / ((भिन्न)old_area + new_area));
                सचे (new_overlap_ratio < 0.80) {
                    पटिनिवत्त;
                }
            }
        }
    }

    सचे (displayID != window->displayID) {
        पूर्णाङ्क i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        अत्थाय (i = 0; i < _this->अङ्कः_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            सचे (display->fullscreen_window == window) {
                सचे (display_index != i) {
                    सचे (display_index < 0) {
                        display_index = i;
                    } अञ्ञथा {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        सचे (new_display->fullscreen_window &&
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

    सचे (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (भिन्न)pixel_w / window_w;
    }
    पटिनिवत्त pixel_density;
}

भिन्न SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    पटिनिवत्त window->display_scale;
}

स्थिर शून्य SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    भिन्न display_scale;

    सचे (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } अञ्ञथा {
        ध्रुव भिन्न pixel_density = SDL_GetWindowPixelDensity(window);
        ध्रुव भिन्न content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    सचे (display_scale != window->display_scale) {
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
    सचे (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    सचे (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        सचे (!display) {
            // This should never happen, but it did...
            गच्छ done;
        }
    } अञ्ञथा {
        अत्थाय (i = 0; i < _this->अङ्कः_displays; ++i) {
            display = _this->displays[i];
            सचे (display->fullscreen_window == window) {
                भङ्ग;
            }
        }
        सचे (!display || i == _this->अङ्कः_displays) {
            // Already not fullscreen on any display
            display = रिक्त;
        }
    }

    सचे (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        सचे (mode) {
            window->fullscreen_exclusive = true;
        } अञ्ञथा {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#सचे defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    सचे (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        सचे (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            सचे (display) {
                display->fullscreen_window = रिक्त;
            }
            गच्छ done;
        }
        सचे (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            सचे (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                सचे (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    गच्छ error;
                }
            } अञ्ञथा सचे (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                अत्थाय (i = 0; i < _this->अङ्कः_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    सचे (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, रिक्त);
                        सचे (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = रिक्त;
                    }
                }
            }

            सचे (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                गच्छ done;
            }
        }
    }
#endif

    सचे (display) {
        // Restore the video mode on other displays if needed
        अत्थाय (i = 0; i < _this->अङ्कः_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            सचे (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, रिक्त);
                other->fullscreen_window = रिक्त;
            }
        }
    }

    सचे (fullscreen) {
        पूर्णाङ्क mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        सचे (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        सचे (!SDL_SetDisplayModeForDisplay(display, mode)) {
            गच्छ error;
        }
        सचे (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            सचे (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } अञ्ञथा {
                resized = true;
            }

            सचे (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } अञ्ञथा सचे (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                गच्छ error;
            }
        }

        सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            सचे (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                सचे (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } अञ्ञथा {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                सचे (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                सचे (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } अञ्ञथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } अञ्ञथा {
        bool resized = false;

        // Restore the desktop mode
        सचे (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, रिक्त);
        }
        सचे (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            सचे (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                सचे (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } अञ्ञथा {
                resized = true;
            }

            सचे (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } अञ्ञथा सचे (ret == SDL_FULLSCREEN_FAILED) {
                गच्छ error;
            }
        }

        सचे (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            सचे (display) {
                display->fullscreen_window = रिक्त;
            }

            सचे (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                सचे (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } अञ्ञथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    पटिनिवत्त true;

error:
    सचे (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    पटिनिवत्त false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ध्रुव SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (mode) {
        सचे (!SDL_GetFullscreenModeMatch(mode)) {
            पटिनिवत्त SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } अञ्ञथा {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#सचे defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    सचे (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    सचे (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    पटिनिवत्त true;
}

ध्रुव SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);
    CHECK_WINDOW_NOT_POPUP(window, रिक्त);

    सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
        पटिनिवत्त SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } अञ्ञथा {
        पटिनिवत्त SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

शून्य *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    सचे (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ध्रुव SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    सचे (mode) {
        पटिनिवत्त mode->format;
    } अञ्ञथा {
        पटिनिवत्त SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_उच्चः_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_शिखरम् | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

स्थिर SDL_INLINE bool IsAcceptingDragAndDrop(शून्य)
{
    सचे (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

// prepare a newly-created window
स्थिर SDL_INLINE शून्य PrepareDragAndDropSupport(SDL_Window *window)
{
    सचे (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
शून्य SDL_ToggleDragAndDropSupport(शून्य)
{
    सचे (_this && _this->AcceptDragAndDrop) {
        ध्रुव bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        अत्थाय (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(पूर्णाङ्क *गणनम्)
{
    सचे (गणनम्) {
        *गणनम् = 0;
    }

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }

    SDL_Window *window;
    पूर्णाङ्क अङ्कः_added = 0;
    पूर्णाङ्क अङ्कः_windows = 0;
    अत्थाय (window = _this->windows; window; window = window->next) {
        ++अङ्कः_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((अङ्कः_windows + 1) * परिमाण(*windows));
    सचे (!windows) {
        पटिनिवत्त रिक्त;
    }

    अत्थाय (window = _this->windows; window; window = window->next) {
        windows[अङ्कः_added++] = window;
        सचे (अङ्कः_added == अङ्कः_windows) {
            // Race condition? Multi-threading not supported, ignore it
            भङ्ग;
        }
    }
    windows[अङ्कः_added] = रिक्त;

    सचे (गणनम्) {
        *गणनम् = अङ्कः_added;
    }
    पटिनिवत्त windows;
}

स्थिर शून्य ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    सचे (!SDL_WINDOW_IS_POPUP(window)) {
        सचे (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        सचे (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        सचे (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        सचे (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        सचे (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        सचे (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

स्थिर शून्य SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    सचे (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } अञ्ञथा {
        ApplyWindowFlags(window, flags);
        सचे (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#सचे defined(SDL_PLATFORM_LINUX)
    सचे (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_मानम्(window, 0.0f);
    }
#endif
}

स्थिर bool SDL_ContextNotSupported(ध्रुव वर्ण *name)
{
    पटिनिवत्त SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

स्थिर bool SDL_DllNotSupported(ध्रुव वर्ण *name)
{
    पटिनिवत्त SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

स्थिर संरचना {
    ध्रुव वर्ण *property_name;
    SDL_WindowFlags flag;
    bool invert_मानम्;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_शिखरम्_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_शिखरम्,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_उच्चः_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_उच्चः_PIXEL_DENSITY,  false },
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
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_सङ्ख्या, 0);

    अत्थाय (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        सचे (SDL_WindowFlagProperties[i].invert_मानम्) {
            सचे (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } अञ्ञथा {
            सचे (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    पटिनिवत्त flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ध्रुव वर्ण *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, रिक्त);
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

    सचे (!_this) {
        // Initialize the video system if needed
        सचे (!SDL_Init(SDL_INIT_VIDEO)) {
            पटिनिवत्त रिक्त;
        }

        // Make clang-tidy happy
        सचे (!_this) {
            पटिनिवत्त रिक्त;
        }
    }

    सचे ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        पटिनिवत्त रिक्त;
    }

    सचे ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        सचे (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            पटिनिवत्त रिक्त;
        }

        // Tooltip and popup menu window must specify a parent window
        सचे (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            पटिनिवत्त रिक्त;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    सचे (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned पूर्णाङ्क)type_flags);
        पटिनिवत्त रिक्त;
    }

    // Make sure the display list is up to date for window placement
    सचे (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    सचे (w < 1) {
        w = 1;
    }
    सचे (h < 1) {
        h = 1;
    }

    सचे (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        सचे ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अञ्ञथा सचे ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        सचे (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        सचे (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        सचे (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            सचे (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        सचे (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            सचे (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    सचे (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned पूर्णाङ्क)graphics_flags);
        पटिनिवत्त रिक्त;
    }

    // Some platforms have certain graphics backends enabled by default
    सचे (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    सचे (flags & SDL_WINDOW_OPENGL) {
        सचे (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            पटिनिवत्त रिक्त;
        }
        सचे (!SDL_GL_LoadLibrary(रिक्त)) {
            पटिनिवत्त रिक्त;
        }
    }

    सचे (flags & SDL_WINDOW_VULKAN) {
        सचे (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            पटिनिवत्त रिक्त;
        }
        सचे (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            पटिनिवत्त रिक्त;
        }
    }

    सचे (flags & SDL_WINDOW_METAL) {
        सचे (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            पटिनिवत्त रिक्त;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, परिमाण(*window));
    सचे (!window) {
        पटिनिवत्त रिक्त;
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
    सचे (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    सचे (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    सचे (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    सचे (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    सचे (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_प्रक्षिप_Error();
        SDL_DestroyWindow(window);
        SDL_निष्कासय_Error();
        पटिनिवत्त रिक्त;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#सचे !defined(SDL_PLATFORM_WINDOWS)
    सचे (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    सचे (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    पटिनिवत्त window;
}

SDL_Window *SDL_CreateWindow(ध्रुव वर्ण *title, पूर्णाङ्क w, पूर्णाङ्क h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    सचे (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_सङ्ख्या, w);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_सङ्ख्या, h);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_सङ्ख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    पटिनिवत्त window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, पूर्णाङ्क offset_x, पूर्णाङ्क offset_y, पूर्णाङ्क w, पूर्णाङ्क h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    सचे (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        पटिनिवत्त रिक्त;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_सङ्ख्या, offset_x);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_सङ्ख्या, offset_y);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_सङ्ख्या, w);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_सङ्ख्या, h);
    SDL_Set_सङ्ख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_सङ्ख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    पटिनिवत्त window;
}

स्थिर bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    सचे (!_this->ReconfigureWindow) {
        पटिनिवत्त false;
    }

    ध्रुव SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    सचे (graphics_flags & (graphics_flags - 1)) {
        पटिनिवत्त SDL_SetError("Conflicting window flags specified");
    }

    सचे ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        पटिनिवत्त SDL_ContextNotSupported("OpenGL");
    }
    सचे ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        पटिनिवत्त SDL_ContextNotSupported("Vulkan");
    }
    सचे ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        पटिनिवत्त SDL_ContextNotSupported("Metal");
    }

    सचे (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        सचे (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            पटिनिवत्त false;
        }
    } अञ्ञथा {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        सचे (!_this->ReconfigureWindow(_this, window, 0)) {
            पटिनिवत्त false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        सचे (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        सचे (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    सचे (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(रिक्त);
        सचे (!loaded_opengl) {
            पटिनिवत्त false;
        }
    } अञ्ञथा सचे (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(रिक्त);
        सचे (!loaded_vulkan) {
            पटिनिवत्त false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    सचे (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        सचे (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        सचे (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        पटिनिवत्त false;
    }

    window->flags |= graphics_flags;

    पटिनिवत्त true;
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
    सचे (graphics_flags & (graphics_flags - 1)) {
        पटिनिवत्त SDL_SetError("Conflicting window flags specified");
    }

    सचे ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        पटिनिवत्त SDL_ContextNotSupported("OpenGL");
    }
    सचे ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        पटिनिवत्त SDL_ContextNotSupported("Vulkan");
    }
    सचे ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        पटिनिवत्त SDL_ContextNotSupported("Metal");
    }

    सचे (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } अञ्ञथा {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    सचे (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    सचे (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ध्रुव bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    सचे ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        सचे (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } अञ्ञथा {
            need_gl_unload = true;
        }
    } अञ्ञथा सचे (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    सचे ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        सचे (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } अञ्ञथा {
            need_vulkan_unload = true;
        }
    } अञ्ञथा सचे (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    सचे (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    सचे (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    सचे (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    सचे (need_gl_load) {
        सचे (!SDL_GL_LoadLibrary(रिक्त)) {
            पटिनिवत्त false;
        }
        loaded_opengl = true;
    }

    सचे (need_vulkan_load) {
        सचे (!SDL_Vulkan_LoadLibrary(रिक्त)) {
            पटिनिवत्त false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    सचे (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        सचे (!_this->CreateSDLWindow(_this, window, 0)) {
            सचे (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            सचे (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            पटिनिवत्त false;
        }
    }

    सचे (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    सचे (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    सचे (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    सचे (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    सचे (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    सचे (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    सचे (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    पटिनिवत्त true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    सचे (!SDL_ReconfigureWindowInternal(window, flags)) {
        पटिनिवत्त SDL_RecreateWindow(window, flags);
    }

    पटिनिवत्त true;
}

bool SDL_HasWindows(शून्य)
{
    पटिनिवत्त _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    पटिनिवत्त window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    सचे (id) {
        अत्थाय (window = _this->windows; window; window = window->next) {
            सचे (window->id == id) {
                पटिनिवत्त window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    पटिनिवत्त रिक्त;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    पटिनिवत्त window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    सचे (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    पटिनिवत्त window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    पटिनिवत्त window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ध्रुव वर्ण *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (title == window->title) {
        पटिनिवत्त true;
    }
    सचे (!title) {
        title = "";
    }
    सचे (window->title && SDL_strcmp(title, window->title) == 0) {
        पटिनिवत्त true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    सचे (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    पटिनिवत्त true;
}

ध्रुव वर्ण *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    पटिनिवत्त window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        पटिनिवत्त SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    सचे (!window->icon) {
        पटिनिवत्त false;
    }

    सचे (!_this->SetWindowIcon) {
        पटिनिवत्त SDL_Unsupported();
    }

    पटिनिवत्त _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ध्रुव पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ध्रुव पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    सचे (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    सचे (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    सचे (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        सचे (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अञ्ञथा सचे (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        सचे (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        सचे (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            सचे (!SDL_GetDisplayBounds(displayID, &bounds)) {
                पटिनिवत्त false;
            }
        }
        सचे (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        सचे (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } अञ्ञथा {
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
    सचे (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    सचे (_this->SetWindowPosition) {
        ध्रुव bool result = _this->SetWindowPosition(_this, window);
        सचे (result) {
            SDL_SyncIfRequired(window);
        }
        पटिनिवत्त result;
    }

    पटिनिवत्त SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, पूर्णाङ्क *x, पूर्णाङ्क *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#अञ्ञथा
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    सचे (use_display_origin) {
        SDL_DisplayID displayID;

        सचे (x) {
            *x = 0;
        }
        सचे (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        सचे (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            सचे (x) {
                *x = bounds.x;
            }
            सचे (y) {
                *y = bounds.y;
            }
        }
    } अञ्ञथा {
        ध्रुव bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        सचे (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        सचे (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    पटिनिवत्त true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (!_this->SetWindowBordered) {
        पटिनिवत्त SDL_Unsupported();
    }

    ध्रुव bool want = bordered;
    ध्रुव bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    सचे (want != have) {
        सचे (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } अञ्ञथा {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    पटिनिवत्त true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (!_this->SetWindowResizable) {
        पटिनिवत्त SDL_Unsupported();
    }

    ध्रुव bool want = resizable;
    ध्रुव bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    सचे (want != have) {
        सचे (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } अञ्ञथा {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    पटिनिवत्त true;
}

bool SDL_Set_Window_Always_On_शिखरम्(SDL_Window *window, bool on_शिखरम्)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (!_this->Set_Window_Always_On_शिखरम्) {
        पटिनिवत्त SDL_Unsupported();
    }

    ध्रुव bool want = on_शिखरम्;
    ध्रुव bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_शिखरम्) != 0);
    सचे (want != have) {
        सचे (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_शिखरम्;
        } अञ्ञथा {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_शिखरम्;
        }
        _this->Set_Window_Always_On_शिखरम्(_this, window, want);
    }

    पटिनिवत्त true;
}

bool SDL_SetWindowSize(SDL_Window *window, पूर्णाङ्क w, पूर्णाङ्क h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        पटिनिवत्त SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        पटिनिवत्त SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    भिन्न new_aspect = w / (भिन्न)h;
    सचे (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (पूर्णाङ्क)SDL_roundf(h * window->max_aspect);
    } अञ्ञथा सचे (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (पूर्णाङ्क)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    सचे (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    सचे (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    सचे (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    सचे (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    सचे (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } अञ्ञथा {
        पटिनिवत्त SDL_Unsupported();
    }
    पटिनिवत्त true;
}

bool SDL_GetWindowSize(SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    सचे (w) {
        *w = window->w;
    }
    सचे (h) {
        *h = window->h;
    }
    पटिनिवत्त true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, भिन्न min_aspect, भिन्न max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    सचे (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    पटिनिवत्त SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, भिन्न *min_aspect, भिन्न *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    सचे (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    पटिनिवत्त true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः)
{
    पूर्णाङ्क dummy = 0;

    सचे (!शिखरम्) {
        शिखरम् = &dummy;
    }
    सचे (!वामः) {
        वामः = &dummy;
    }
    सचे (!दक्षिणः) {
        दक्षिणः = &dummy;
    }
    सचे (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *शिखरम् = *वामः = *bottom = *दक्षिणः = 0;

    CHECK_WINDOW_MAGIC(window, false);

    सचे (!_this->GetWindowBordersSize) {
        पटिनिवत्त SDL_Unsupported();
    }

    पटिनिवत्त _this->GetWindowBordersSize(_this, window, शिखरम्, वामः, bottom, दक्षिणः);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    पूर्णाङ्क filter;

    CHECK_WINDOW_MAGIC(window, false);

    सचे (!w) {
        w = &filter;
    }

    सचे (!h) {
        h = &filter;
    }

    सचे (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } अञ्ञथा {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ध्रुव SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        सचे ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } अञ्ञथा {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        सचे (mode) {
            *w = (पूर्णाङ्क)SDL_ceilf(*w * mode->pixel_density);
            *h = (पूर्णाङ्क)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    पटिनिवत्त true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, पूर्णाङ्क min_w, पूर्णाङ्क min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        पटिनिवत्त SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        पटिनिवत्त SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        पटिनिवत्त SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    सचे (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    पटिनिवत्त SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, पूर्णाङ्क *min_w, पूर्णाङ्क *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    सचे (min_w) {
        *min_w = window->min_w;
    }
    सचे (min_h) {
        *min_h = window->min_h;
    }
    पटिनिवत्त true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, पूर्णाङ्क max_w, पूर्णाङ्क max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        पटिनिवत्त SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        पटिनिवत्त SDL_InvalidParamError("max_h");
    }

    सचे ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        पटिनिवत्त SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    सचे (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    पूर्णाङ्क w = window->last_size_pending ? window->pending.w : window->floating.w;
    पूर्णाङ्क h = window->last_size_pending ? window->pending.h : window->floating.h;
    पटिनिवत्त SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, पूर्णाङ्क *max_w, पूर्णाङ्क *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    सचे (max_w) {
        *max_w = window->max_w;
    }
    सचे (max_h) {
        *max_h = window->max_h;
    }
    पटिनिवत्त true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!(window->flags & SDL_WINDOW_HIDDEN)) {
        पटिनिवत्त true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    सचे (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        पटिनिवत्त true;
    }

    सचे (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } अञ्ञथा {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    अत्थाय (child = window->first_child; child; child = child->next_sibling) {
        सचे (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            भङ्ग;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    पटिनिवत्त true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        पटिनिवत्त true;
    }

    // Hide all child windows
    अत्थाय (child = window->first_child; child; child = child->next_sibling) {
        सचे (child->flags & SDL_WINDOW_HIDDEN) {
            भङ्ग;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ध्रुव SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    सचे (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } अञ्ञथा {
        SDL_SetMouseFocus(रिक्त);
        SDL_SetKeyboardFocus(रिक्त);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    पटिनिवत्त true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        पटिनिवत्त true;
    }
    सचे (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    पटिनिवत्त true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (!_this->MaximizeWindow) {
        पटिनिवत्त SDL_Unsupported();
    }

    सचे (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        पटिनिवत्त SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        पटिनिवत्त true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    पटिनिवत्त true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (!_this->MinimizeWindow) {
        पटिनिवत्त SDL_Unsupported();
    }

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        पटिनिवत्त true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    पटिनिवत्त true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (!_this->RestoreWindow) {
        पटिनिवत्त SDL_Unsupported();
    }

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        पटिनिवत्त true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    पटिनिवत्त true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        सचे (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } अञ्ञथा {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        पटिनिवत्त true;
    }

    सचे (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    सचे (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    सचे (result) {
        SDL_SyncIfRequired(window);
    }

    पटिनिवत्त result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (_this->SyncWindow) {
        पटिनिवत्त _this->SyncWindow(_this, window);
    } अञ्ञथा {
        पटिनिवत्त true;
    }
}

स्थिर bool ShouldAttemptTextureFramebuffer(शून्य)
{
    ध्रुव वर्ण *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    सचे (!_this->CreateWindowFramebuffer) {
        पटिनिवत्त true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    सचे (hint && *hint) {
        सचे (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } अञ्ञथा {
            attempt_texture_framebuffer = true;
        }
    } अञ्ञथा {
        सचे (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } अञ्ञथा {
            attempt_texture_framebuffer = false;
        }
    }
    पटिनिवत्त attempt_texture_framebuffer;
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
    सचे (!_this->checked_texture_framebuffer) {
        सचे (ShouldAttemptTextureFramebuffer()) {
            सचे (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } अञ्ञथा {
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

    सचे (!created_framebuffer) {
        सचे (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            पटिनिवत्त रिक्त;
        }

        सचे (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            पटिनिवत्त रिक्त;
        }
    }

    सचे (window->surface) {
        // We may have gone recursive and already created the surface
        पटिनिवत्त window->surface;
    }

    पटिनिवत्त SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    पटिनिवत्त window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    सचे (!window->surface_valid) {
        सचे (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = रिक्त;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        सचे (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    पटिनिवत्त window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, पूर्णाङ्क vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!_this->SetWindowFramebufferVSync) {
        पटिनिवत्त SDL_Unsupported();
    }
    पटिनिवत्त _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, पूर्णाङ्क *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!_this->GetWindowFramebufferVSync) {
        पटिनिवत्त SDL_Unsupported();
    }
    पटिनिवत्त _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    पटिनिवत्त SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ध्रुव SDL_Rect *rects,
                                 पूर्णाङ्क numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!window->surface_valid) {
        पटिनिवत्त SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    पटिनिवत्त _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = रिक्त;
        window->surface_valid = false;
    }

    सचे (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        सचे (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    पटिनिवत्त true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, भिन्न opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    सचे (!_this->SetWindowOpacity) {
        पटिनिवत्त SDL_Unsupported();
    }

    सचे (opacity < 0.0f) {
        opacity = 0.0f;
    } अञ्ञथा सचे (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    सचे (result) {
        window->opacity = opacity;
    }

    पटिनिवत्त result;
}

भिन्न SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    पटिनिवत्त window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    सचे (window == parent) {
        पटिनिवत्त SDL_SetError("Cannot set the parent of a window to itself.");
    }

    सचे (!_this->SetWindowParent) {
        पटिनिवत्त SDL_Unsupported();
    }

    सचे (window->flags & SDL_WINDOW_MODAL) {
        पटिनिवत्त SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    सचे (window->parent == parent) {
        पटिनिवत्त true;
    }

    ध्रुव bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : रिक्त);

    पटिनिवत्त ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (!_this->SetWindowModal) {
        पटिनिवत्त SDL_Unsupported();
    }

    सचे (modal) {
        सचे (!window->parent) {
            पटिनिवत्त SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } अञ्ञथा सचे (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } अञ्ञथा {
        पटिनिवत्त true; // Already not modal, so nothing to do.
    }

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        पटिनिवत्त true;
    }

    पटिनिवत्त _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_निवेशः_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    याव (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        सचे (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_निवेशः_FOCUS);
        }
    }

    *new_focus = focus;
    पटिनिवत्त set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    अत्थाय (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    अत्थाय (w = current_focus; w != toplevel_parent; w = w->parent) {
        सचे (w == window) {
            found_higher_focus = true;
            भङ्ग;
        }
    }

    पटिनिवत्त !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ध्रुव bool want = (focusable != false); // normalize the flag.
    ध्रुव bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    सचे ((want != have) && (_this->SetWindowFocusable)) {
        सचे (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } अञ्ञथा {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        सचे (!_this->SetWindowFocusable(_this, window, want)) {
            पटिनिवत्त false;
        }
    }

    पटिनिवत्त true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ध्रुव bool want = (fill != false); // normalize the flag.
    ध्रुव bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    सचे ((want != have) && (_this->SetWindowFillDocument)) {
        सचे (!_this->SetWindowFillDocument(_this, window, want)) {
            पटिनिवत्त false;
        } अञ्ञथा सचे (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } अञ्ञथा {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    पटिनिवत्त true;
}

शून्य SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    सचे (window->flags & SDL_WINDOW_निवेशः_FOCUS) {
        सचे (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } अञ्ञथा {
            mouse_grabbed = false;
        }

        सचे (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } अञ्ञथा {
            keyboard_grabbed = false;
        }
    } अञ्ञथा {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    सचे (mouse_grabbed || keyboard_grabbed) {
        सचे (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            सचे (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            सचे (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } अञ्ञथा सचे (_this->grabbed_window == window) {
        _this->grabbed_window = रिक्त; // ungrabbing input.
    }

    सचे (_this->SetWindowMouseGrab) {
        सचे (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    सचे (_this->SetWindowKeyboardGrab) {
        सचे (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    सचे (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = रिक्त;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        सचे (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } अञ्ञथा {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        पटिनिवत्त true;
    }

    सचे (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        पटिनिवत्त true;
    }
    सचे (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } अञ्ञथा {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    सचे (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        पटिनिवत्त false;
    }
    पटिनिवत्त true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (window->flags & SDL_WINDOW_HIDDEN) {
        सचे (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } अञ्ञथा {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        पटिनिवत्त true;
    }

    सचे (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        पटिनिवत्त true;
    }
    सचे (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } अञ्ञथा {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    सचे (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        पटिनिवत्त false;
    }
    पटिनिवत्त true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    पटिनिवत्त window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    पटिनिवत्त window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(शून्य)
{
    सचे (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        पटिनिवत्त _this->grabbed_window;
    } अञ्ञथा {
        पटिनिवत्त रिक्त;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ध्रुव SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!_this->SetWindowMouseRect) {
        पटिनिवत्त SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    सचे (!rect) {
        rect = &zero;
    }

    सचे (SDL_memcmp(&window->mouse_rect, rect, परिमाण(*rect)) == 0) {
        पटिनिवत्त true;
    }
    SDL_memcpy(&window->mouse_rect, rect, परिमाण(*rect));

    पटिनिवत्त _this->SetWindowMouseRect(_this, window);
}

ध्रुव SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    सचे (SDL_RectEmpty(&window->mouse_rect)) {
        पटिनिवत्त रिक्त;
    } अञ्ञथा {
        पटिनिवत्त &window->mouse_rect;
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

    सचे (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        पटिनिवत्त true;
    }

    सचे (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } अञ्ञथा {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    सचे (!SDL_UpdateRelativeMouseMode()) {
        सचे (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } अञ्ञथा {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        पटिनिवत्त false;
    }
    पटिनिवत्त true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        पटिनिवत्त true;
    } अञ्ञथा {
        पटिनिवत्त false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (_this->FlashWindow) {
        पटिनिवत्त _this->FlashWindow(_this, window, operation);
    }

    पटिनिवत्त SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        पटिनिवत्त SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    सचे (_this->ApplyWindowProgress) {
        सचे (!_this->ApplyWindowProgress(_this, window)) {
            पटिनिवत्त false;
        }
    }

    पटिनिवत्त true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    पटिनिवत्त window->progress_state;
}

bool SDL_Set_Window_Progress_मानम्(SDL_Window *window, भिन्न मानम्)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    मानम् = SDL_clamp(मानम्, 0.0f, 1.f);

    window->progress_मानम् = मानम्;

    सचे (_this->ApplyWindowProgress) {
        सचे (!_this->ApplyWindowProgress(_this, window)) {
            पटिनिवत्त false;
        }
    }

    पटिनिवत्त true;
}

भिन्न SDL_Get_Window_Progress_मानम्(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    पटिनिवत्त window->progress_मानम्;
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
    सचे (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ध्रुव bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        सचे (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_उच्चः_density_modes = false;

            सचे (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_उच्चः_density_modes = true;
            }
            ध्रुव bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_उच्चः_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            सचे (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } अञ्ञथा {
            SDL_zero(window->current_fullscreen_mode);
        }

        सचे (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
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

    सचे ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, रिक्त);
        सचे (surface) {
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
    सचे (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } अञ्ञथा {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

स्थिर शून्य SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_वामः;
    rect.y = window->safe_inset_शिखरम्;
    rect.w = window->w - (window->safe_inset_दक्षिणः + window->safe_inset_वामः);
    rect.h = window->h - (window->safe_inset_शिखरम् + window->safe_inset_bottom);
    सचे (SDL_memcmp(&rect, &window->safe_rect, परिमाण(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

शून्य SDL_SetWindowSafeAreaInsets(SDL_Window *window, पूर्णाङ्क वामः, पूर्णाङ्क दक्षिणः, पूर्णाङ्क शिखरम्, पूर्णाङ्क bottom)
{
    window->safe_inset_वामः = वामः;
    window->safe_inset_दक्षिणः = दक्षिणः;
    window->safe_inset_शिखरम् = शिखरम्;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    सचे (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    सचे (rect) {
        सचे (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } अञ्ञथा {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    पटिनिवत्त true;
}

शून्य SDL_OnWindowMinimized(SDL_Window *window)
{
    सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
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

    सचे (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

शून्य SDL_OnWindowEnter(SDL_Window *window)
{
    सचे (_this->OnWindowEnter) {
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

    सचे (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

स्थिर bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ध्रुव वर्ण *hint;

    सचे (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        पटिनिवत्त false;
    }

#सचे defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    सचे (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        सचे (Cocoa_IsShowingModalDialog(window)) {
            पटिनिवत्त false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } अञ्ञथा सचे (Cocoa_IsWindowInFullscreenSpace(window)) {
            पटिनिवत्त false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        बाह्य bool Android_JNI_ShouldMinimizeOnFocusLoss(शून्य);
        सचे (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            पटिनिवत्त false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    सचे (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        सचे (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            पटिनिवत्त true;
        } अञ्ञथा {
            पटिनिवत्त false;
        }
    }
    पटिनिवत्त SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

शून्य SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    सचे (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(शून्य)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    सचे (focus) {
        // Get the toplevel parent window.
        याव (focus->parent) {
            focus = focus->parent;
        }
    }

    पटिनिवत्त focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->अङ्कः_renderers + 1) * परिमाण(*renderers));
    सचे (!renderers) {
        पटिनिवत्त false;
    }

    window->renderers = renderers;
    window->renderers[window->अङ्कः_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    पटिनिवत्त true;
}

शून्य SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    अत्थाय (पूर्णाङ्क i = 0; i < window->अङ्कः_renderers; ++i) {
        सचे (window->renderers[i] == renderer) {
            सचे (i < (window->अङ्कः_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->अङ्कः_renderers - i - 1) * परिमाण(window->renderers[i]));
            }
            --window->अङ्कः_renderers;
            भङ्ग;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    सचे (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, रिक्त) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

शून्य SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    याव (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    सचे (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    सचे (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_निवेशः_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    सचे (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    अत्थाय (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
        सचे (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = रिक्त;
        }
    }

    // Make sure this window no longer has focus
    सचे (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(रिक्त);
    }
    सचे ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    सचे (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(रिक्त);
    }

    // Make no context current if this is the current context window
    सचे (window->flags & SDL_WINDOW_OPENGL) {
        सचे (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, रिक्त);
        }
    }

    सचे (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    सचे (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    सचे (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    सचे (_this->grabbed_window == window) {
        _this->grabbed_window = रिक्त; // ungrabbing input.
    }

    सचे (_this->current_glwin == window) {
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
    सचे (window->next) {
        window->next->prev = window->prev;
    }
    सचे (window->prev) {
        window->prev->next = window->next;
    } अञ्ञथा {
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
    सचे (!_this) {
        पटिनिवत्त true;
    }
    पटिनिवत्त !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(शून्य)
{
    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }
    सचे (!_this->suspend_screensaver) {
        पटिनिवत्त true;
    }
    _this->suspend_screensaver = false;
    सचे (_this->SuspendScreenSaver) {
        पटिनिवत्त _this->SuspendScreenSaver(_this);
    }

    पटिनिवत्त SDL_Unsupported();
}

bool SDL_DisableScreenSaver(शून्य)
{
    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }
    सचे (_this->suspend_screensaver) {
        पटिनिवत्त true;
    }
    _this->suspend_screensaver = true;
    सचे (_this->SuspendScreenSaver) {
        पटिनिवत्त _this->SuspendScreenSaver(_this);
    }

    पटिनिवत्त SDL_Unsupported();
}

शून्य SDL_QuitVideo(शून्य)
{
    पूर्णाङ्क i;

    सचे (!_this) {
        पटिनिवत्त;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#सचे 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    याव (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    सचे (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    सचे (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    अत्थाय (i = _this->अङ्कः_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->अङ्कः_displays == 0);
    SDL_free(_this->displays);
    _this->displays = रिक्त;

    SDL_CancelClipboardData(0);

    सचे (_this->primary_selection_text) {
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

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }
    सचे (_this->gl_config.driver_loaded) {
        सचे (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            पटिनिवत्त SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } अञ्ञथा {
        सचे (!_this->GL_LoadLibrary) {
            पटिनिवत्त SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    सचे (result) {
        ++_this->gl_config.driver_loaded;
    } अञ्ञथा {
        सचे (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    पटिनिवत्त result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ध्रुव वर्ण *proc)
{
    SDL_FunctionPointer func;

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    func = रिक्त;
    सचे (_this->GL_GetProcAddress) {
        सचे (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } अञ्ञथा {
            SDL_SetError("No GL driver has been loaded");
        }
    } अञ्ञथा {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    पटिनिवत्त func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ध्रुव वर्ण *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    func = रिक्त;

    सचे (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } अञ्ञथा {
        SDL_SetError("No EGL library has been loaded");
    }

    पटिनिवत्त func;
#अञ्ञथा
    SDL_SetError("SDL was not built with EGL support");
    पटिनिवत्त रिक्त;
#endif
}

शून्य SDL_GL_UnloadLibrary(शून्य)
{
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त;
    }
    सचे (_this->gl_config.driver_loaded > 0) {
        सचे (--_this->gl_config.driver_loaded > 0) {
            पटिनिवत्त;
        }
        सचे (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#सचे defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
प्रकारनिर्देश GLenum (APIENTRY* PFNGLGETERRORPROC) (शून्य);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
प्रकारनिर्देश ध्रुव GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
प्रकारनिर्देश ध्रुव GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

स्थिर SDL_INLINE bool isAtLeastGL3(ध्रुव वर्ण *verstr)
{
    पटिनिवत्त verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ध्रुव वर्ण *extension)
{
#सचे defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ध्रुव वर्ण *extensions;
    ध्रुव वर्ण *start;
    ध्रुव वर्ण *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    सचे (where || *extension == '\0') {
        पटिनिवत्त false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    सचे (start && *start == '0') {
        पटिनिवत्त false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    सचे (!glGetStringFunc) {
        पटिनिवत्त false;
    }

    सचे (isAtLeastGL3((ध्रुव वर्ण *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint अङ्कः_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        सचे ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            पटिनिवत्त false;
        }

#ifndef GL_अङ्कः_EXTENSIONS
#define GL_अङ्कः_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_अङ्कः_EXTENSIONS, &अङ्कः_exts);
        अत्थाय (i = 0; i < अङ्कः_exts; i++) {
            ध्रुव वर्ण *thisext = (ध्रुव वर्ण *)glGetStringiFunc(GL_EXTENSIONS, i);
            सचे (SDL_strcmp(thisext, extension) == 0) {
                पटिनिवत्त true;
            }
        }

        पटिनिवत्त false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ध्रुव वर्ण *)glGetStringFunc(GL_EXTENSIONS);
    सचे (!extensions) {
        पटिनिवत्त false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    अत्थाय (;;) {
        where = SDL_strstr(start, extension);
        सचे (!where) {
            भङ्ग;
        }

        terminator = where + SDL_strlen(extension);
        सचे (where == extensions || *(where - 1) == ' ') {
            सचे (*terminator == ' ' || *terminator == '\0') {
                पटिनिवत्त true;
            }
        }

        start = terminator;
    }
    पटिनिवत्त false;
#अञ्ञथा
    पटिनिवत्त false;
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
#सचे defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    सचे (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } अञ्ञथा सचे (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } अञ्ञथा सचे (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } अञ्ञथा {
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
    सचे (!_this) {
        पटिनिवत्त;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

शून्य SDL_GL_ResetAttributes(शून्य)
{
    सचे (!_this) {
        पटिनिवत्त;
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

    सचे (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, पूर्णाङ्क मानम्)
{
#सचे defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }
    result = true;
    विकल्प (attr) {
    पक्ष SDL_GL_RED_SIZE:
        _this->gl_config.red_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = मानम्;
        भङ्ग;
    पक्ष SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = मानम्;
        भङ्ग;
    पक्ष SDL_GL_STEREO:
        _this->gl_config.stereo = मानम्;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = मानम्;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = मानम्;
        भङ्ग;
    पक्ष SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = मानम्;
        भङ्ग;
    पक्ष SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_FLAGS:
        सचे (मानम् & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", मानम्);
            भङ्ग;
        }
        _this->gl_config.flags = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_PROFILE_MASK:
        सचे (मानम् != 0 &&
            मानम् != SDL_GL_CONTEXT_PROFILE_CORE &&
            मानम् != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            मानम् != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", मानम्);
            भङ्ग;
        }
        _this->gl_config.profile_mask = मानम्;
        भङ्ग;
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = मानम्;
        भङ्ग;
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = मानम्;
        भङ्ग;
    पक्ष SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = मानम्;
        भङ्ग;
    स्वभाव:
        result = SDL_SetError("Unknown OpenGL attribute");
        भङ्ग;
    }
    पटिनिवत्त result;
#अञ्ञथा
    पटिनिवत्त SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, पूर्णाङ्क *मानम्)
{
#सचे defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_वामः;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!मानम्) {
        पटिनिवत्त SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *मानम् = 0;

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
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
#अञ्ञथा
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *मानम् = _this->gl_config.double_buffer;
        पटिनिवत्त true;
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
#अञ्ञथा
    पक्ष SDL_GL_ACCUM_RED_SIZE:
    पक्ष SDL_GL_ACCUM_GREEN_SIZE:
    पक्ष SDL_GL_ACCUM_BLUE_SIZE:
    पक्ष SDL_GL_ACCUM_ALPHA_SIZE:
    पक्ष SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *मानम् = 0;
        पटिनिवत्त true;
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
        सचे (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            पटिनिवत्त false;
        }
        सचे (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            पटिनिवत्त false;
        }
        सचे (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            पटिनिवत्त false;
        }
        सचे (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            पटिनिवत्त false;
        }

        *मानम् = rsize + gsize + bsize + asize;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *मानम् = (_this->gl_config.accelerated != 0);
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_RETAINED_BACKING:
    {
        *मानम् = _this->gl_config.retained_backing;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *मानम् = _this->gl_config.major_version;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *मानम् = _this->gl_config.minor_version;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_CONTEXT_FLAGS:
    {
        *मानम् = _this->gl_config.flags;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *मानम् = _this->gl_config.profile_mask;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *मानम् = _this->gl_config.share_with_current_context;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *मानम् = _this->gl_config.framebuffer_srgb_capable;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
    {
        *मानम् = _this->gl_config.no_error;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_EGL_PLATFORM:
    {
        *मानम् = _this->gl_config.egl_platform;
        पटिनिवत्त true;
    }
    पक्ष SDL_GL_FLOATBUFFERS:
    {
        सचे (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            भङ्ग;
        } अञ्ञथा {
            पटिनिवत्त 0;
        }
    }
    स्वभाव:
        पटिनिवत्त SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    सचे (!glGetStringFunc) {
        पटिनिवत्त false;
    }

    सचे (attachmentattrib && isAtLeastGL3((ध्रुव वर्ण *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        सचे (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        सचे (glGetFramebufferAttachmentParameterivFunc) {
            सचे (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            सचे (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            सचे (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)मानम्);
            } अञ्ञथा {
                *मानम् = 0;
            }
            सचे (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } अञ्ञथा {
            पटिनिवत्त false;
        }
    } अञ्ञथा
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        सचे (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)मानम्);
        } अञ्ञथा {
            पटिनिवत्त false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    सचे (!glGetErrorFunc) {
        पटिनिवत्त false;
    }

    error = glGetErrorFunc();
    सचे (error != GL_NO_ERROR) {
        सचे (error == GL_INVALID_ENUM) {
            पटिनिवत्त SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } अञ्ञथा सचे (error == GL_INVALID_मानम्) {
            पटिनिवत्त SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        पटिनिवत्त SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    सचे (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *मानम् = (*मानम् == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    पटिनिवत्त true;
#अञ्ञथा
    पटिनिवत्त SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = रिक्त;
    CHECK_WINDOW_MAGIC(window, रिक्त);

    सचे (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        पटिनिवत्त रिक्त;
    }

#सचे defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    पूर्णाङ्क srgb_requested = -1;
    ध्रुव वर्ण *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    सचे (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    सचे (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, रिक्त);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, रिक्त);
    }

#सचे defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    सचे (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        सचे (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            सचे (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } अञ्ञथा {
                supported = isAtLeastGL3((ध्रुव वर्ण *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            सचे (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    पटिनिवत्त ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }

    सचे (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        पटिनिवत्त true;
    }

    सचे (!context) {
        window = रिक्त;
    } अञ्ञथा सचे (window) {
        CHECK_WINDOW_MAGIC(window, false);

        सचे (!(window->flags & SDL_WINDOW_OPENGL)) {
            पटिनिवत्त SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } अञ्ञथा सचे (!_this->gl_allow_no_surface) {
        पटिनिवत्त SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    सचे (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, रिक्त);
        SDL_SetTLS(&_this->current_glctx_tls, context, रिक्त);
    }
    पटिनिवत्त result;
}

SDL_Window *SDL_GL_GetCurrentWindow(शून्य)
{
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(शून्य)
{
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त EGL_NO_DISPLAY;
    }
    सचे (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        पटिनिवत्त EGL_NO_DISPLAY;
    }
    पटिनिवत्त _this->egl_data->egl_display;
#अञ्ञथा
    SDL_SetError("SDL was not built with EGL support");
    पटिनिवत्त रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(शून्य)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    सचे (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त _this->egl_data->egl_config;
#अञ्ञथा
    SDL_SetError("SDL was not built with EGL support");
    पटिनिवत्त रिक्त;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    सचे (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        पटिनिवत्त रिक्त;
    }
    सचे (_this->GL_GetEGLSurface) {
        पटिनिवत्त _this->GL_GetEGLSurface(_this, window);
    }
    पटिनिवत्त रिक्त;
#अञ्ञथा
    SDL_SetError("SDL was not built with EGL support");
    पटिनिवत्त रिक्त;
#endif
}

bool SDL_GL_SetSwapInterval(पूर्णाङ्क interval)
{
    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    } अञ्ञथा सचे (SDL_GL_GetCurrentContext() == रिक्त) {
        पटिनिवत्त SDL_SetError("No OpenGL context has been made current");
    } अञ्ञथा सचे (_this->GL_SetSwapInterval) {
        पटिनिवत्त _this->GL_SetSwapInterval(_this, interval);
    } अञ्ञथा {
        पटिनिवत्त SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(पूर्णाङ्क *interval)
{
    CHECK_PARAM(!interval) {
       पटिनिवत्त SDL_InvalidParamError("interval");
    }

    *interval = 0;

    सचे (!_this) {
        पटिनिवत्त SDL_SetError("no video driver");
    } अञ्ञथा सचे (SDL_GL_GetCurrentContext() == रिक्त) {
        पटिनिवत्त SDL_SetError("no current context");
    } अञ्ञथा सचे (_this->GL_GetSwapInterval) {
        पटिनिवत्त _this->GL_GetSwapInterval(_this, interval);
    } अञ्ञथा {
        पटिनिवत्त SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!(window->flags & SDL_WINDOW_OPENGL)) {
        पटिनिवत्त SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    सचे (SDL_GL_GetCurrentWindow() != window) {
        पटिनिवत्त SDL_SetError("The specified window has not been made current");
    }

    पटिनिवत्त _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        पटिनिवत्त SDL_InvalidParamError("context");
    }

    सचे (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(रिक्त, रिक्त);
    }

    पटिनिवत्त _this->GL_DestroyContext(_this, context);
}

#सचे 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
स्थिर शून्य Create_Mask_From_Color_कुञ्चिका_Or_Alpha(SDL_Surface *icon, Uint8 *mask, पूर्णाङ्क flags)
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
            अत्थाय (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                अत्थाय (x = 0; x < icon->w; ++x) {
                    सचे (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        भङ्ग;

    पक्ष 2:
        {
            Uint16 *pixels;
            अत्थाय (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                अत्थाय (x = 0; x < icon->w; ++x) {
                    सचे ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अञ्ञथा सचे ((flags & 2)
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
            अत्थाय (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                अत्थाय (x = 0; x < icon->w; ++x) {
                    सचे ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अञ्ञथा सचे ((flags & 2)
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
    सचे (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        सचे (mask == रिक्त) {
            पूर्णाङ्क mask_len = icon->h * (icon->w + 7) / 8;
            पूर्णाङ्क flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            सचे (mask == रिक्त) {
                पटिनिवत्त;
            }
            SDL_memset(mask, ~0, mask_len);
            सचे (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            सचे (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            सचे (flags) {
                Create_Mask_From_Color_कुञ्चिका_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } अञ्ञथा {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_निवेशः_Type SDL_Get_Text_निवेशः_Type(SDL_PropertiesID props)
{
    पटिनिवत्त (SDL_Text_निवेशः_Type)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_TEXTINPUT_TYPE_सङ्ख्या, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_निवेशः_Capitalization(SDL_PropertiesID props)
{
    सचे (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_सङ्ख्या)) {
        पटिनिवत्त (SDL_Capitalization)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_सङ्ख्या, SDL_CAPITALIZE_NONE);
    }

    विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        पटिनिवत्त SDL_CAPITALIZE_SENTENCES;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        पटिनिवत्त SDL_CAPITALIZE_शब्दाः;
    स्वभाव:
        पटिनिवत्त SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_निवेशः_Autocorrect(SDL_PropertiesID props)
{
    पटिनिवत्त SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_निवेशः_Multiline(SDL_PropertiesID props)
{
    सचे (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        पटिनिवत्त SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    सचे (SDL_GetHintBoolean(SDL_HINT_RETURN_कुञ्चिका_HIDES_IME, false)) {
        पटिनिवत्त false;
    } अञ्ञथा {
        पटिनिवत्त true;
    }
}

स्थिर bool AutoShowingScreenKeyboard(शून्य)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    सचे (!hint) {
        // This hint is currently only used by the X11 video driver
        सचे (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    सचे (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        पटिनिवत्त true;
    } अञ्ञथा {
        पटिनिवत्त false;
    }
}

bool SDL_Start_Text_निवेशः(SDL_Window *window)
{
    पटिनिवत्त SDL_Start_Text_निवेशः_With_Properties(window, 0);
}

bool SDL_Start_Text_निवेशः_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (window->text_निवेशः_props) {
        SDL_DestroyProperties(window->text_निवेशः_props);
        window->text_निवेशः_props = 0;
    }

    सचे (props) {
        window->text_निवेशः_props = SDL_CreateProperties();
        सचे (!window->text_निवेशः_props) {
            पटिनिवत्त false;
        }
        सचे (!SDL_CopyProperties(props, window->text_निवेशः_props)) {
            पटिनिवत्त false;
        }
    }

    सचे (_this->Set_Text_निवेशः_Properties) {
        _this->Set_Text_निवेशः_Properties(_this, window, props);
    }

    सचे (!window->text_निवेशः_active) {
        // Start the text input system
        सचे (_this->Start_Text_निवेशः) {
            सचे (!_this->Start_Text_निवेशः(_this, window, props)) {
                पटिनिवत्त false;
            }
        }
        window->text_निवेशः_active = true;
    }

    // Show the on-screen keyboard, if desired
    सचे (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        सचे (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    पटिनिवत्त true;
}

bool SDL_Text_निवेशः_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    पटिनिवत्त window->text_निवेशः_active;
}

bool SDL_Stop_Text_निवेशः(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (window->text_निवेशः_active) {
        // Stop the text input system
        सचे (_this->Stop_Text_निवेशः) {
            _this->Stop_Text_निवेशः(_this, window);
        }
        window->text_निवेशः_active = false;
    }

    // Hide the on-screen keyboard, if desired
    सचे (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        सचे (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    पटिनिवत्त true;
}

bool SDL_Set_Text_निवेशः_Area(SDL_Window *window, ध्रुव SDL_Rect *rect, पूर्णाङ्क cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (rect) {
        SDL_copyp(&window->text_निवेशः_rect, rect);
        window->text_निवेशः_cursor = cursor;
    } अञ्ञथा {
        SDL_zero(window->text_निवेशः_rect);
        window->text_निवेशः_cursor = 0;
    }

    सचे (_this && _this->Update_Text_निवेशः_Area) {
        सचे (!_this->Update_Text_निवेशः_Area(_this, window)) {
            पटिनिवत्त false;
        }
    }
    पटिनिवत्त true;
}

bool SDL_Get_Text_निवेशः_Area(SDL_Window *window, SDL_Rect *rect, पूर्णाङ्क *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (rect) {
        SDL_copyp(rect, &window->text_निवेशः_rect);
    }
    सचे (cursor) {
        *cursor = window->text_निवेशः_cursor;
    }
    पटिनिवत्त true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (_this->ClearComposition) {
        पटिनिवत्त _this->ClearComposition(_this, window);
    }
    पटिनिवत्त true;
}

bool SDL_HasScreenKeyboardSupport(शून्य)
{
    सचे (_this && _this->HasScreenKeyboardSupport) {
        पटिनिवत्त _this->HasScreenKeyboardSupport(_this);
    }
    पटिनिवत्त false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    पटिनिवत्त _this->screen_keyboard_shown;
}

शून्य SDL_SendScreenKeyboardShown(शून्य)
{
    सचे (!_this || _this->screen_keyboard_shown) {
        पटिनिवत्त;
    }

    _this->screen_keyboard_shown = true;

    सचे (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_प्रक्षिप_Event(&event);
    }
}

शून्य SDL_SendScreenKeyboardHidden(शून्य)
{
    सचे (!_this || !_this->screen_keyboard_shown) {
        पटिनिवत्त;
    }

    _this->screen_keyboard_shown = false;

    सचे (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_प्रक्षिप_Event(&event);
    }
}

पूर्णाङ्क SDL_Get_Message_Box_गणनम्(शून्य)
{
    पटिनिवत्त SDL_GetAtomicInt(&SDL_messagebox_गणनम्);
}

bool SDL_ShowMessageBox(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
    पूर्णाङ्क dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        पटिनिवत्त SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        पटिनिवत्त SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    वर्ण *titlecpy = रिक्त;
    वर्ण *msgcpy = रिक्त;
    सचे (messageboxdata->title) {
        ध्रुव size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(वर्ण, slen, &titleisstack);
        सचे (!titlecpy) {
            पटिनिवत्त false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    सचे (messageboxdata->message) {
        ध्रुव size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(वर्ण, slen, &msgisstack);
        सचे (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            पटिनिवत्त false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (शून्य)SDL_AtomicIncRef(&SDL_messagebox_गणनम्);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    सचे (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, परिमाण(*messageboxdata));
    mbdata.title = titlecpy;
    सचे (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    सचे (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    सचे (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } अञ्ञथा {
        // It's completely fine to call this function before video is initialized
        ध्रुव वर्ण *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        सचे (driver_name && *driver_name != 0) {
            ध्रुव वर्ण *driver_attempt = driver_name;
            याव (driver_attempt && (*driver_attempt != 0) && !result) {
                ध्रुव वर्ण *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                अत्थाय (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                    सचे (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        सचे (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        भङ्ग;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : रिक्त;
            }
        } अञ्ञथा {
            अत्थाय (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                सचे (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    भङ्ग;
                }
            }
        }
    }

    सचे (!result) {
        ध्रुव वर्ण *error = SDL_GetError();

        सचे (!*error) {
            SDL_SetError("No message system available");
        }
    } अञ्ञथा {
        SDL_ClearError();
    }

    (शून्य)SDL_AtomicDecRef(&SDL_messagebox_गणनम्);

    सचे (current_window) {
        SDL_RaiseWindow(current_window);
    }

    सचे (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    पटिनिवत्त result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ध्रुव वर्ण *title, ध्रुव वर्ण *message, SDL_Window *window)
{
#सचे defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_दक्षिणः;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_दक्षिणः = gsp_Has_Gpu_दक्षिणः();
    सचे (!has_Gpu_दक्षिणः)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    सचे (!has_Gpu_दक्षिणः)
        gfxExit();

    पटिनिवत्त true;
#अञ्ञथा
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

    पटिनिवत्त SDL_ShowMessageBox(&data, रिक्त);
#endif
}

bool SDL_ShouldAllowTopmost(शून्य)
{
    पटिनिवत्त SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    सचे (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        पटिनिवत्त true;
    }

    पटिनिवत्त SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, शून्य *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!_this->SetWindowHitTest) {
        पटिनिवत्त SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    पटिनिवत्त _this->SetWindowHitTest(window, callback != रिक्त);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    सचे (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        पटिनिवत्त SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    सचे (!props) {
        पटिनिवत्त false;
    }

    सचे (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        सचे (!surface) {
            पटिनिवत्त false;
        }
    } अञ्ञथा {
        surface = रिक्त;
    }

    सचे (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        पटिनिवत्त false;
    }

    सचे (_this->UpdateWindowShape) {
        सचे (!_this->UpdateWindowShape(_this, window, surface)) {
            पटिनिवत्त false;
        }
    }
    पटिनिवत्त true;
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
    SDL_SendAppEvent(SDL_EVENT_नीचः_MEMORY);
}

शून्य SDL_OnApplicationWillEnterBackground(शून्य)
{
    सचे (_this) {
        SDL_Window *window;
        अत्थाय (window = _this->windows; window; window = window->next) {
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

    सचे (_this) {
        SDL_Window *window;
        अत्थाय (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ध्रुव वर्ण *path)
{
    bool result;

    सचे (!_this) {
        पटिनिवत्त SDL_UninitializedVideo();
    }
    सचे (_this->vulkan_config.loader_loaded) {
        सचे (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            पटिनिवत्त SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } अञ्ञथा {
        सचे (!_this->Vulkan_LoadLibrary) {
            पटिनिवत्त SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    सचे (result) {
        _this->vulkan_config.loader_loaded++;
    }
    पटिनिवत्त result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(शून्य)
{
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त रिक्त;
    }
    सचे (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        पटिनिवत्त रिक्त;
    }
    पटिनिवत्त (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

शून्य SDL_Vulkan_UnloadLibrary(शून्य)
{
    सचे (!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त;
    }
    सचे (_this->vulkan_config.loader_loaded > 0) {
        सचे (--_this->vulkan_config.loader_loaded > 0) {
            पटिनिवत्त;
        }
        सचे (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

वर्ण ध्रुव * ध्रुव *SDL_Vulkan_GetInstanceExtensions(Uint32 *गणनम्)
{
    Uint32 tmpcount = 0;
    सचे (!गणनम्) {
        गणनम् = &tmpcount;
    }

    सचे (!_this->Vulkan_GetInstanceExtensions) {
        *गणनम् = 0;
        SDL_Unsupported();
        पटिनिवत्त रिक्त;
    }

    पटिनिवत्त _this->Vulkan_GetInstanceExtensions(_this, गणनम्);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ध्रुव संरचना VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    सचे (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        पटिनिवत्त false;
    }

    CHECK_PARAM(!instance) {
        पटिनिवत्त SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        पटिनिवत्त SDL_InvalidParamError("surface");
    }

    सचे (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        सचे (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        सचे (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        सचे (SDL_Vulkan_LoadLibrary(रिक्त)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } अञ्ञथा {
            पटिनिवत्त SDL_SetError("failed to load Vulkan library");
        }
    }

    पटिनिवत्त _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

शून्य SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ध्रुव संरचना VkAllocationCallbacks *allocator)
{
    सचे (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        पटिनिवत्त false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        पटिनिवत्त false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        पटिनिवत्त false;
    }

    सचे (_this->Vulkan_GetPresentationSupport) {
        पटिनिवत्त _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    पटिनिवत्त true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, रिक्त);

    सचे (!_this->Metal_CreateView) {
        SDL_Unsupported();
        पटिनिवत्त रिक्त;
    }

    सचे (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        सचे (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        सचे (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    पटिनिवत्त _this->Metal_CreateView(_this, window);
}

शून्य SDL_Metal_DestroyView(SDL_MetalView view)
{
    सचे (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

शून्य *SDL_Metal_GetLayer(SDL_MetalView view)
{
    सचे (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            पटिनिवत्त रिक्त;
        }
        पटिनिवत्त _this->Metal_GetLayer(_this, view);
    } अञ्ञथा {
        SDL_SetError("Metal is not supported.");
        पटिनिवत्त रिक्त;
    }
}

#सचे defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ध्रुव वर्ण *SDL_GetCSSCursorName(SDL_SystemCursor id, ध्रुव वर्ण **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    विकल्प (id) {
    पक्ष SDL_SYSTEM_CURSOR_DEFAULT:
        पटिनिवत्त "default";

    पक्ष SDL_SYSTEM_CURSOR_TEXT:
        पटिनिवत्त "text";

    पक्ष SDL_SYSTEM_CURSOR_WAIT:
        पटिनिवत्त "wait";

    पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR:
        पटिनिवत्त "crosshair";

    पक्ष SDL_SYSTEM_CURSOR_PROGRESS:
        पटिनिवत्त "progress";

    पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        सचे (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        पटिनिवत्त "nwse-resize";

    पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE:
        सचे (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        पटिनिवत्त "nesw-resize";

    पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE:
        सचे (fallback_name) {
            *fallback_name = "col-resize";
        }
        पटिनिवत्त "ew-resize";

    पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE:
        सचे (fallback_name) {
            *fallback_name = "row-resize";
        }
        पटिनिवत्त "ns-resize";

    पक्ष SDL_SYSTEM_CURSOR_MOVE:
        सचे (fallback_name) {
            *fallback_name = "all-scroll";
        }
        पटिनिवत्त "move";

    पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        पटिनिवत्त "not-allowed";

    पक्ष SDL_SYSTEM_CURSOR_POINTER:
        पटिनिवत्त "pointer";

    पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE:
        पटिनिवत्त "nw-resize";

    पक्ष SDL_SYSTEM_CURSOR_N_RESIZE:
        पटिनिवत्त "n-resize";

    पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE:
        पटिनिवत्त "ne-resize";

    पक्ष SDL_SYSTEM_CURSOR_E_RESIZE:
        पटिनिवत्त "e-resize";

    पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE:
        पटिनिवत्त "se-resize";

    पक्ष SDL_SYSTEM_CURSOR_S_RESIZE:
        पटिनिवत्त "s-resize";

    पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE:
        पटिनिवत्त "sw-resize";

    पक्ष SDL_SYSTEM_CURSOR_W_RESIZE:
        पटिनिवत्त "w-resize";

    पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        पटिनिवत्त "context-menu";

    पक्ष SDL_SYSTEM_CURSOR_HELP:
        पटिनिवत्त "help";

    पक्ष SDL_SYSTEM_CURSOR_CELL:
        पटिनिवत्त "cell";

    पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        पटिनिवत्त "vertical-text";

    पक्ष SDL_SYSTEM_CURSOR_ALIAS:
        पटिनिवत्त "alias";

    पक्ष SDL_SYSTEM_CURSOR_COPY:
        पटिनिवत्त "copy";

    पक्ष SDL_SYSTEM_CURSOR_NO_DROP:
        पटिनिवत्त "no-drop";

    पक्ष SDL_SYSTEM_CURSOR_GRAB:
        पटिनिवत्त "grab";

    पक्ष SDL_SYSTEM_CURSOR_GRABBING:
        पटिनिवत्त "grabbing";

    पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE:
        पटिनिवत्त "col-resize";

    पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE:
        पटिनिवत्त "row-resize";

    पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL:
        सचे (fallback_name) {
            *fallback_name = "move";
        }
        पटिनिवत्त "all-scroll";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_IN:
        पटिनिवत्त "zoom-in";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_OUT:
        पटिनिवत्त "zoom-out";

    स्वभाव:
        पटिनिवत्त "default";
    }
}
#endif

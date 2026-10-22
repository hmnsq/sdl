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

#അന്തര്ഭാവ "SDL_internal.h"

// The high-level video driver subsystem

#അന്തര്ഭാവ "SDL_sysvideo.h"
#അന്തര്ഭാവ "SDL_clipboard_c.h"
#അന്തര്ഭാവ "SDL_egl_c.h"
#അന്തര്ഭാവ "SDL_surface_c.h"
#അന്തര്ഭാവ "SDL_pixels_c.h"
#അന്തര്ഭാവ "SDL_rect_c.h"
#അന്തര്ഭാവ "SDL_video_c.h"
#അന്തര്ഭാവ "../events/SDL_events_c.h"
#അന്തര്ഭാവ "../SDL_hints_c.h"
#അന്തര്ഭാവ "../SDL_properties_c.h"
#അന്തര്ഭാവ "../timer/SDL_timer_c.h"
#അന്തര്ഭാവ "../camera/SDL_camera_c.h"
#അന്തര്ഭാവ "../render/SDL_sysrender.h"
#അന്തര്ഭാവ "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#അന്തര്ഭാവ <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#എങ്കിൽ defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#അന്തര്ഭാവ <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#എങ്കിൽ defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#അന്തര്ഭാവ <SDL3/SDL_opengles2.h>
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
#അന്തര്ഭാവ <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#അന്തര്ഭാവ <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
സ്ഥിതം VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_നിവേശം_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    ശൂന്യ
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        തിരികെ result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        തിരികെ result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        തിരികെ result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        തിരികെ result;                                                  \
    }

#എങ്കിൽ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
ബാഹ്യ bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
ബാഹ്യ bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
ബാഹ്യ bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
ബാഹ്യ bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
ബാഹ്യ ശൂന്യം SDL_UpdateLifecycleObserver(ശൂന്യം);
#endif

സ്ഥിതം ശൂന്യം SDL_CheckWindowDisplayChanged(SDL_Window *window);
സ്ഥിതം ശൂന്യം SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
സ്ഥിതം ശൂന്യം SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
സ്ഥിതം bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    എങ്കിൽ (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        തിരികെ true;
    }
    തിരികെ false;
}

സ്ഥിതം bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    തിരികെ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

സ്ഥിതം bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    തിരികെ !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

സ്ഥിതം bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    തിരികെ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

സ്ഥിതം bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    തിരികെ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

സ്ഥിതം bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    തിരികെ !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
സ്ഥിതം bool syncHint;

സ്ഥിതം ശൂന്യം SDL_SyncHintWatcher(ശൂന്യം *userdata, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *old_മൂല്യം, സ്ഥിരം അക്ഷരം *new_മൂല്യം)
{
    syncHint = SDL_GetStringBoolean(new_മൂല്യം, false);
}

സ്ഥിതം ശൂന്യം SDL_SyncIfRequired(SDL_Window *window)
{
    എങ്കിൽ (syncHint) {
        SDL_SyncWindow(window);
    }
}

സ്ഥിതം ശൂന്യം SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    എങ്കിൽ (window->parent) {
        എങ്കിൽ (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        എങ്കിൽ (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } അല്ലെങ്കിൽ {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = ശൂന്യ;
    }

    എങ്കിൽ (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        എങ്കിൽ (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

തരനിർവചനം ഘടന
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    ശൂന്യം *pixels;
    പൂർണ്ണസംഖ്യ pitch;
    പൂർണ്ണസംഖ്യ bytes_per_pixel;
} SDL_WindowTextureData;

സ്ഥിതം Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#എങ്കിൽ (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    എങ്കിൽ (_this->GL_CreateContext) {
        തിരികെ SDL_WINDOW_OPENGL;
    }
#endif
#എങ്കിൽ defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    എങ്കിൽ (_this->Metal_CreateView) {
        തിരികെ SDL_WINDOW_METAL;
    }
#endif
#എങ്കിൽ defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    എങ്കിൽ (SDL_strcmp(_this->name, "openvr") == 0) {
        തിരികെ SDL_WINDOW_OPENGL;
    }
#endif
    തിരികെ 0;
}

സ്ഥിതം bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, ശൂന്യം **pixels, പൂർണ്ണസംഖ്യ *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ശൂന്യ);
    സ്ഥിരം bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    പൂർണ്ണസംഖ്യ i;
    പൂർണ്ണസംഖ്യ w, h;
    സ്ഥിരം SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    എങ്കിൽ (!data) {
        SDL_Renderer *renderer = ശൂന്യ;
        സ്ഥിരം അക്ഷരം *render_driver = ശൂന്യ;

        // See if there's a render driver being requested
        സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        എങ്കിൽ (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        എങ്കിൽ (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        എങ്കിൽ (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = ശൂന്യ;
        }

        അക്ഷരം *render_driver_copy = ശൂന്യ;
        എങ്കിൽ (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            എങ്കിൽ (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                അക്ഷരം *prev = render_driver_copy;
                അക്ഷരം *ptr = prev;
                ആകുമ്പോൾ ((ptr = SDL_strchr(ptr, ',')) != ശൂന്യ) {
                    *ptr = '\0';
                    സ്ഥിരം bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    എങ്കിൽ (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } അല്ലെങ്കിൽ {
                        ptr++;
                        prev = ptr;
                    }
                }

                എങ്കിൽ (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        എങ്കിൽ (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            എങ്കിൽ (!renderer) {
                // The error for this specific renderer has already been set
                തിരികെ false;
            }
        } അല്ലെങ്കിൽ {
            SDL_assert(render_driver_copy == ശൂന്യ);
            സ്ഥിരം പൂർണ്ണസംഖ്യ total = SDL_Get_അക്കം_Render_Drivers();
            വേണ്ടി (i = 0; i < total; ++i) {
                സ്ഥിരം അക്ഷരം *name = SDL_GetRenderDriver(i);
                എങ്കിൽ (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    എങ്കിൽ (renderer) {
                        നിർത്തുക; // this will work.
                    }
                }
            }
            എങ്കിൽ (!renderer) {
                തിരികെ SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ശൂന്യ); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, വലുപ്പം(*data));
        എങ്കിൽ (!data) {
            SDL_DestroyRenderer(renderer);
            തിരികെ false;
        }
        എങ്കിൽ (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            തിരികെ false;
        }

        data->renderer = renderer;
    }

    texture_formats = (സ്ഥിരം SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, ശൂന്യ);
    എങ്കിൽ (!texture_formats) {
        തിരികെ false;
    }

    // Free any old texture and pixel data
    എങ്കിൽ (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = ശൂന്യ;
    }
    SDL_free(data->pixels);
    data->pixels = ശൂന്യ;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    വേണ്ടി (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        എങ്കിൽ (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            നിർത്തുക;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    എങ്കിൽ (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        തിരികെ false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        സ്ഥിരം size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        എങ്കിൽ (!data->pixels) {
            തിരികെ false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, ശൂന്യ);

    തിരികെ true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ശൂന്യ);
    എങ്കിൽ (!data) {
        തിരികെ false;
    }
    എങ്കിൽ (!data->renderer) {
        തിരികെ false;
    }
    തിരികെ SDL_SetRenderVSync(data->renderer, vsync);
}

സ്ഥിതം bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ശൂന്യ);
    എങ്കിൽ (!data) {
        തിരികെ false;
    }
    എങ്കിൽ (!data->renderer) {
        തിരികെ false;
    }
    തിരികെ SDL_GetRenderVSync(data->renderer, vsync);
}

സ്ഥിതം bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, സ്ഥിരം SDL_Rect *rects, പൂർണ്ണസംഖ്യ numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    ശൂന്യം *src;
    പൂർണ്ണസംഖ്യ w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ശൂന്യ);
    എങ്കിൽ (!data || !data->texture) {
        തിരികെ SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    എങ്കിൽ (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (ശൂന്യം *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        എങ്കിൽ (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            തിരികെ false;
        }

        എങ്കിൽ (!SDL_RenderTexture(data->renderer, data->texture, ശൂന്യ, ശൂന്യ)) {
            തിരികെ false;
        }

        SDL_RenderPresent(data->renderer);
    }
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    എങ്കിൽ (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ശൂന്യ);

        എങ്കിൽ (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        എങ്കിൽ (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

സ്ഥിതം SDL_VideoDevice *_this = ശൂന്യ;
സ്ഥിതം SDL_AtomicInt SDL_messagebox_എണ്ണം;

സ്ഥിതം പൂർണ്ണസംഖ്യ SDLCALL cmpmodes(സ്ഥിരം ശൂന്യം *A, സ്ഥിരം ശൂന്യം *B)
{
    സ്ഥിരം SDL_DisplayMode *a = (സ്ഥിരം SDL_DisplayMode *)A;
    സ്ഥിരം SDL_DisplayMode *b = (സ്ഥിരം SDL_DisplayMode *)B;
    പൂർണ്ണസംഖ്യ a_refresh_rate = (പൂർണ്ണസംഖ്യ)(a->refresh_rate * 100);
    പൂർണ്ണസംഖ്യ b_refresh_rate = (പൂർണ്ണസംഖ്യ)(b->refresh_rate * 100);
    പൂർണ്ണസംഖ്യ a_pixel_density = (പൂർണ്ണസംഖ്യ)(a->pixel_density * 100);
    പൂർണ്ണസംഖ്യ b_pixel_density = (പൂർണ്ണസംഖ്യ)(b->pixel_density * 100);

    എങ്കിൽ (a->w != b->w) {
        തിരികെ b->w - a->w;
    } അല്ലെങ്കിൽ എങ്കിൽ (a->h != b->h) {
        തിരികെ b->h - a->h;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        തിരികെ SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        തിരികെ SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } അല്ലെങ്കിൽ എങ്കിൽ (a_refresh_rate != b_refresh_rate) {
        തിരികെ b_refresh_rate - a_refresh_rate;
    } അല്ലെങ്കിൽ എങ്കിൽ (a_pixel_density != b_pixel_density) {
        തിരികെ a_pixel_density - b_pixel_density;
    }
    തിരികെ 0;
}

bool SDL_UninitializedVideo(ശൂന്യം)
{
    തിരികെ SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
സ്ഥിതം സ്ഥിരം VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

പൂർണ്ണസംഖ്യ SDL_Get_അക്കം_Video_Drivers(ശൂന്യം)
{
    സ്ഥിതം പൂർണ്ണസംഖ്യ അക്കം_drivers = -1;

    എങ്കിൽ (അക്കം_drivers >= 0) {
        തിരികെ അക്കം_drivers;
    }

    അക്കം_drivers = 0;

    // Build a list of unique video drivers.
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; bootstrap[i] != ശൂന്യ; ++i) {
        bool duplicate = false;
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < i; ++j) {
            എങ്കിൽ (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                നിർത്തുക;
            }
        }

        എങ്കിൽ (!duplicate) {
            deduped_bootstrap[അക്കം_drivers++] = bootstrap[i];
        }
    }

    തിരികെ അക്കം_drivers;
}

സ്ഥിരം അക്ഷരം *SDL_GetVideoDriver(പൂർണ്ണസംഖ്യ index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_അക്കം_Video_Drivers()) {
        SDL_InvalidParamError("index");
        തിരികെ ശൂന്യ;
    }
    തിരികെ deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(സ്ഥിരം അക്ഷരം *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    പൂർണ്ണസംഖ്യ i = 0;

    // Check to make sure we don't overwrite '_this'
    എങ്കിൽ (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    എങ്കിൽ (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        പോകുക pre_driver_error;
    }
    init_events = true;
    എങ്കിൽ (!SDL_InitKeyboard()) {
        പോകുക pre_driver_error;
    }
    init_keyboard = true;
    എങ്കിൽ (!SDL_PreInitMouse()) {
        പോകുക pre_driver_error;
    }
    init_mouse = true;
    എങ്കിൽ (!SDL_InitTouch()) {
        പോകുക pre_driver_error;
    }
    init_touch = true;
    എങ്കിൽ (!SDL_InitPen()) {
        പോകുക pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ശൂന്യ;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    എങ്കിൽ (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    എങ്കിൽ (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    എങ്കിൽ (driver_name && *driver_name != 0) {
        സ്ഥിരം അക്ഷരം *driver_attempt = driver_name;
        ആകുമ്പോൾ (driver_attempt && *driver_attempt != 0 && !video) {
            സ്ഥിരം അക്ഷരം *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            വേണ്ടി (i = 0; bootstrap[i]; ++i) {
                എങ്കിൽ (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    എങ്കിൽ (video) {
                        നിർത്തുക;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ശൂന്യ;
        }
    } അല്ലെങ്കിൽ {
        വേണ്ടി (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            എങ്കിൽ (video) {
                നിർത്തുക;
            }
        }
    }
    എങ്കിൽ (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (driver_name) {
            SDL_SetError("%s not available", driver_name);
            പോകുക pre_driver_error;
        }
        SDL_SetError("No available video device");
        പോകുക pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ശൂന്യ;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    എങ്കിൽ (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        തിരികെ false;
    }

    // Make sure some displays were added
    എങ്കിൽ (_this->അക്കം_displays == 0) {
        SDL_QuitVideo();
        തിരികെ SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, ശൂന്യ);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    എങ്കിൽ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    തിരികെ true;

pre_driver_error:
    SDL_assert(_this == ശൂന്യ);
    എങ്കിൽ (init_pen) {
        SDL_QuitPen();
    }
    എങ്കിൽ (init_touch) {
        SDL_QuitTouch();
    }
    എങ്കിൽ (init_mouse) {
        SDL_QuitMouse();
    }
    എങ്കിൽ (init_keyboard) {
        SDL_QuitKeyboard();
    }
    എങ്കിൽ (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    തിരികെ false;
}

സ്ഥിരം അക്ഷരം *SDL_GetCurrentVideoDriver(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    തിരികെ _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(ശൂന്യം)
{
    തിരികെ _this;
}

bool SDL_OnVideoThread(ശൂന്യം)
{
    തിരികെ (_this && SDL_GetCurrentThreadID() == _this->thread);
}

ശൂന്യം SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    എങ്കിൽ (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(ശൂന്യം)
{
    എങ്കിൽ (_this) {
        തിരികെ _this->system_theme;
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SYSTEM_THEME_UNKNOWN;
    }
}

ശൂന്യം SDL_UpdateDesktopBounds(ശൂന്യം)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ശൂന്യ);
    എങ്കിൽ (displays) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            എങ്കിൽ (SDL_GetDisplayBounds(displays[i], &bounds)) {
                എങ്കിൽ (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } അല്ലെങ്കിൽ {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

സ്ഥിതം ശൂന്യം SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    എങ്കിൽ (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    എങ്കിൽ (mode->refresh_rate_numerator > 0) {
        എങ്കിൽ (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (ദശാംശം)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } അല്ലെങ്കിൽ {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(സ്ഥിരം SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    എങ്കിൽ (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, വലുപ്പം(display.desktop_mode));
    }
    തിരികെ SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(സ്ഥിരം SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    പൂർണ്ണസംഖ്യ i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(വലുപ്പം(*new_display));
    എങ്കിൽ (!new_display) {
        തിരികെ 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->അക്കം_displays + 1) * വലുപ്പം(*displays));
    എങ്കിൽ (!displays) {
        SDL_free(new_display);
        തിരികെ 0;
    }
    _this->displays = displays;
    _this->displays[_this->അക്കം_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    എങ്കിൽ (display->name) {
        new_display->name = SDL_strdup(display->name);
    } അല്ലെങ്കിൽ {
        അക്ഷരം name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    എങ്കിൽ (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    വേണ്ടി (i = 0; i < new_display->അക്കം_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    എങ്കിൽ (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    തിരികെ id;
}

ശൂന്യം SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    വേണ്ടി (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

ശൂന്യം SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

ശൂന്യം SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    പൂർണ്ണസംഖ്യ display_index = SDL_GetDisplayIndex(displayID);
    എങ്കിൽ (display_index < 0) {
        തിരികെ;
    }

    display = _this->displays[display_index];

    എങ്കിൽ (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = ശൂന്യ;
    SDL_free(display->internal);
    display->internal = ശൂന്യ;
    SDL_free(display);

    എങ്കിൽ (display_index < (_this->അക്കം_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->അക്കം_displays - display_index - 1) * വലുപ്പം(_this->displays[display_index]));
    }
    --_this->അക്കം_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(പൂർണ്ണസംഖ്യ *എണ്ണം)
{
    പൂർണ്ണസംഖ്യ i;
    SDL_DisplayID *displays;

    എങ്കിൽ (!_this) {
        എങ്കിൽ (എണ്ണം) {
            *എണ്ണം = 0;
        }

        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->അക്കം_displays + 1) * വലുപ്പം(*displays));
    എങ്കിൽ (displays) {
        എങ്കിൽ (എണ്ണം) {
            *എണ്ണം = _this->അക്കം_displays;
        }

        വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (എണ്ണം) {
            *എണ്ണം = 0;
        }
    }
    തിരികെ displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    പൂർണ്ണസംഖ്യ display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    എങ്കിൽ (display_index < 0) {
        തിരികെ ശൂന്യ;
    }
    തിരികെ _this->displays[display_index];
}

സ്ഥിതം SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    എങ്കിൽ (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    തിരികെ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    തിരികെ SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(ശൂന്യം)
{
    എങ്കിൽ (!_this || _this->അക്കം_displays == 0) {
        SDL_UninitializedVideo();
        തിരികെ 0;
    }
    തിരികെ _this->displays[0]->id;
}

പൂർണ്ണസംഖ്യ SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    പൂർണ്ണസംഖ്യ display_index;

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ -1;
    }

    വേണ്ടി (display_index = 0; display_index < _this->അക്കം_displays; ++display_index) {
        എങ്കിൽ (displayID == _this->displays[display_index]->id) {
            തിരികെ display_index;
        }
    }
    SDL_SetError("Invalid display");
    തിരികെ -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ശൂന്യ);

    തിരികെ display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    തിരികെ SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    എങ്കിൽ (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    തിരികെ display->props;
}

സ്ഥിരം അക്ഷരം *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ശൂന്യ);

    തിരികെ display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        തിരികെ SDL_InvalidParamError("rect");
    }

    എങ്കിൽ (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        എങ്കിൽ (_this->GetDisplayBounds(_this, display, rect)) {
            തിരികെ true;
        }
    }

    // Assume that the displays are left to right
    എങ്കിൽ (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } അല്ലെങ്കിൽ {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    തിരികെ true;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    തിരികെ hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        തിരികെ SDL_InvalidParamError("rect");
    }

    എങ്കിൽ (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        തിരികെ true;
    }

    എങ്കിൽ (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        എങ്കിൽ (_this->GetDisplayUsableBounds(_this, display, rect)) {
            തിരികെ true;
        }
    }

    // Oh well, just give the entire display bounds.
    തിരികെ SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    എങ്കിൽ (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        തിരികെ display->natural_orientation;
    } അല്ലെങ്കിൽ {
        // Default to landscape if the driver hasn't set it
        തിരികെ SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    എങ്കിൽ (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        തിരികെ display->current_orientation;
    } അല്ലെങ്കിൽ {
        // Default to landscape if the driver hasn't set it
        തിരികെ SDL_ORIENTATION_LANDSCAPE;
    }
}

ശൂന്യം SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ദശാംശം scale)
{
    എങ്കിൽ (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        വേണ്ടി (window = _this->windows; window; window = window->next) {
            എങ്കിൽ (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

ദശാംശം SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    തിരികെ display->content_scale;
}

ശൂന്യം SDL_SetWindowHDRProperties(SDL_Window *window, സ്ഥിരം SDL_HDROutputProperties *HDR, bool send_event)
{
    സ്ഥിരം SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    എങ്കിൽ (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        എങ്കിൽ (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

ശൂന്യം SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, സ്ഥിരം SDL_HDROutputProperties *HDR)
{
    സ്ഥിരം SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    സ്ഥിരം bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	എങ്കിൽ (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    എങ്കിൽ (changed && !SDL_DriverSendsHDRChanges(_this)) {
        വേണ്ടി (SDL_Window *w = display->device->windows; w; w = w->next) {
            എങ്കിൽ (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

സ്ഥിതം ശൂന്യം SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    എങ്കിൽ (display->അക്കം_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
സ്ഥിതം സ്ഥിരം SDL_DisplayMode *SDL_GetFullscreenModeMatch(സ്ഥിരം SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    എങ്കിൽ (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        തിരികെ ശൂന്യ;
    }

    SDL_memcpy(&fullscreen_mode, mode, വലുപ്പം(fullscreen_mode));
    എങ്കിൽ (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = ശൂന്യ;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    എങ്കിൽ (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        എങ്കിൽ (!mode) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < display->അക്കം_fullscreen_modes; ++i) {
                എങ്കിൽ (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], വലുപ്പം(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    നിർത്തുക;
                }
            }
        }

        // Search for a mode with the same characteristics
        എങ്കിൽ (!mode) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < display->അക്കം_fullscreen_modes; ++i) {
                എങ്കിൽ (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    നിർത്തുക;
                }
            }
        }
    }
    തിരികെ mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, സ്ഥിരം SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    പൂർണ്ണസംഖ്യ i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, വലുപ്പം(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->അക്കം_fullscreen_modes;
    വേണ്ടി (i = 0; i < nmodes; ++i) {
        എങ്കിൽ (cmpmodes(&new_mode, &modes[i]) == 0) {
            തിരികെ false;
        }
    }

    // Go ahead and add the new mode
    എങ്കിൽ (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * വലുപ്പം(*modes));
        എങ്കിൽ (!modes) {
            തിരികെ false;
        }

        എങ്കിൽ (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * വലുപ്പം(*modes));
            വേണ്ടി (i = 0; i < nmodes; ++i) {
                എങ്കിൽ (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->അക്കം_fullscreen_modes++], &new_mode, വലുപ്പം(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->അക്കം_fullscreen_modes,
              വലുപ്പം(SDL_DisplayMode), cmpmodes);

    തിരികെ true;
}

ശൂന്യം SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = display->അക്കം_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = ശൂന്യ;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ശൂന്യ;
    display->അക്കം_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, പൂർണ്ണസംഖ്യ *എണ്ണം)
{
    പൂർണ്ണസംഖ്യ i;
    പൂർണ്ണസംഖ്യ അക്കം_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    എങ്കിൽ (എണ്ണം) {
        *എണ്ണം = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ശൂന്യ);

    SDL_UpdateFullscreenDisplayModes(display);

    അക്കം_modes = display->അക്കം_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((അക്കം_modes + 1) * വലുപ്പം(*result) + അക്കം_modes * വലുപ്പം(**result));
    എങ്കിൽ (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((അക്കം_modes + 1) * വലുപ്പം(*result)));
        എങ്കിൽ (അക്കം_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, അക്കം_modes * വലുപ്പം(*modes));
        }
        വേണ്ടി (i = 0; i < അക്കം_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = ശൂന്യ;

        എങ്കിൽ (എണ്ണം) {
            *എണ്ണം = അക്കം_modes;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (എണ്ണം) {
            *എണ്ണം = 0;
        }
    }
    തിരികെ result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, ദശാംശം refresh_rate, bool include_മുകളിലെ_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        തിരികെ SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    സ്ഥിരം SDL_DisplayMode *mode, *closest = ശൂന്യ;
    ദശാംശം aspect_ratio;
    പൂർണ്ണസംഖ്യ i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    എങ്കിൽ (h > 0) {
        aspect_ratio = (ദശാംശം)w / h;
    } അല്ലെങ്കിൽ {
        aspect_ratio = 1.0f;
    }

    എങ്കിൽ (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    വേണ്ടി (i = 0; i < display->അക്കം_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        എങ്കിൽ (w > mode->w) {
            // Out of sorted modes large enough here
            നിർത്തുക;
        }
        എങ്കിൽ (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            തുടരുക;
        }
        എങ്കിൽ (mode->pixel_density > 1.0f && !include_മുകളിലെ_density_modes) {
            തുടരുക;
        }
        എങ്കിൽ (closest) {
            ദശാംശം current_aspect_ratio = (ദശാംശം)mode->w / mode->h;
            ദശാംശം closest_aspect_ratio = (ദശാംശം)closest->w / closest->h;
            എങ്കിൽ (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                തുടരുക;
            }

            എങ്കിൽ (mode->w == closest->w && mode->h == closest->h) {
                എങ്കിൽ (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    തുടരുക;
                }
                എങ്കിൽ (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    തുടരുക;
                }
            }
        }

        closest = mode;
    }
    എങ്കിൽ (!closest) {
        തിരികെ SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    തിരികെ true;
}

സ്ഥിതം bool DisplayModeChanged(സ്ഥിരം SDL_DisplayMode *old_mode, സ്ഥിരം SDL_DisplayMode *new_mode)
{
    തിരികെ ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

ശൂന്യം SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, സ്ഥിരം SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    എങ്കിൽ (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        തിരികെ;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    എങ്കിൽ (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        എങ്കിൽ (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

സ്ഥിരം SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ശൂന്യ);

    തിരികെ &display->desktop_mode;
}

ശൂന്യം SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, സ്ഥിരം SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    എങ്കിൽ (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } അല്ലെങ്കിൽ {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    എങ്കിൽ (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

സ്ഥിരം SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ശൂന്യ);

    തിരികെ display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    എങ്കിൽ (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        തിരികെ true;
    }

    എങ്കിൽ (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    എങ്കിൽ (mode == display->current_mode) {
        തിരികെ true;
    }
#endif

    // Actually change the display mode
    എങ്കിൽ (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        എങ്കിൽ (!result) {
            തിരികെ false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    തിരികെ true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
സ്ഥിതം ശൂന്യം SDL_GetClosestPointOnRect(സ്ഥിരം SDL_Rect *rect, SDL_Point *point)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ വലത് = rect->x + rect->w - 1;
    സ്ഥിരം പൂർണ്ണസംഖ്യ bottom = rect->y + rect->h - 1;

    എങ്കിൽ (point->x < rect->x) {
        point->x = rect->x;
    } അല്ലെങ്കിൽ എങ്കിൽ (point->x > വലത്) {
        point->x = വലത്;
    }

    എങ്കിൽ (point->y < rect->y) {
        point->y = rect->y;
    } അല്ലെങ്കിൽ എങ്കിൽ (point->y > bottom) {
        point->y = bottom;
    }
}

സ്ഥിതം SDL_DisplayID GetDisplayForRect(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    പൂർണ്ണസംഖ്യ i, dist;
    SDL_DisplayID closest = 0;
    പൂർണ്ണസംഖ്യ closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    എങ്കിൽ (_this) {
        വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            എങ്കിൽ (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ശൂന്യ)) {
                തിരികെ display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            എങ്കിൽ (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    എങ്കിൽ (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    തിരികെ closest;
}

ശൂന്യം SDL_RelativeToGlobalForWindow(SDL_Window *window, പൂർണ്ണസംഖ്യ rel_x, പൂർണ്ണസംഖ്യ rel_y, പൂർണ്ണസംഖ്യ *abs_x, പൂർണ്ണസംഖ്യ *abs_y)
{
    SDL_Window *w;

    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        വേണ്ടി (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            എങ്കിൽ (!SDL_WINDOW_IS_POPUP(w)) {
                നിർത്തുക;
            }
        }
    }

    എങ്കിൽ (abs_x) {
        *abs_x = rel_x;
    }
    എങ്കിൽ (abs_y) {
        *abs_y = rel_y;
    }
}

ശൂന്യം SDL_GlobalToRelativeForWindow(SDL_Window *window, പൂർണ്ണസംഖ്യ abs_x, പൂർണ്ണസംഖ്യ abs_y, പൂർണ്ണസംഖ്യ *rel_x, പൂർണ്ണസംഖ്യ *rel_y)
{
    SDL_Window *w;

    എങ്കിൽ (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        വേണ്ടി (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            എങ്കിൽ (!SDL_WINDOW_IS_POPUP(w)) {
                നിർത്തുക;
            }
        }
    }

    എങ്കിൽ (rel_x) {
        *rel_x = abs_x;
    }
    എങ്കിൽ (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(സ്ഥിരം SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        തിരികെ 0;
    }

    തിരികെ GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(സ്ഥിരം SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        തിരികെ 0;
    }

    തിരികെ GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

സ്ഥിതം SDL_DisplayID GetDisplayAtOrigin(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; ++i) {
        SDL_Rect rect;
        സ്ഥിരം SDL_DisplayID cur_id = _this->displays[i]->id;
        എങ്കിൽ (SDL_GetDisplayBounds(cur_id, &rect)) {
            എങ്കിൽ (x == rect.x && y == rect.y) {
                തിരികെ cur_id;
            }
        }
    }

    തിരികെ 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    പൂർണ്ണസംഖ്യ x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    എങ്കിൽ (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    എങ്കിൽ (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } അല്ലെങ്കിൽ {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    എങ്കിൽ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    തിരികെ displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, ശൂന്യ);

    // An explicit fullscreen display overrides all
    എങ്കിൽ (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    എങ്കിൽ (!displayID) {
        displayID = window->pending_displayID;
    }
    എങ്കിൽ (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        സ്ഥിരം പൂർണ്ണസംഖ്യ x = window->last_position_pending ? window->pending.x : window->x;
        സ്ഥിരം പൂർണ്ണസംഖ്യ y = window->last_position_pending ? window->pending.y : window->y;
        സ്ഥിരം പൂർണ്ണസംഖ്യ w = window->last_size_pending ? window->pending.w : window->w;
        സ്ഥിരം പൂർണ്ണസംഖ്യ h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        എങ്കിൽ (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    എങ്കിൽ (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    തിരികെ SDL_GetVideoDisplay(displayID);
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
    എങ്കിൽ (fs_display) {
        SDL_Set_സംഖ്യ_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } അല്ലെങ്കിൽ {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    തിരികെ GetDisplayForWindow(window);
}

സ്ഥിതം ശൂന്യം SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    എങ്കിൽ (SDL_SendsDisplayChanges(_this)) {
        തിരികെ;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    എങ്കിൽ (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        എങ്കിൽ (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            എങ്കിൽ (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                പൂർണ്ണസംഖ്യ old_area = old_overlap.w * old_overlap.h;
                പൂർണ്ണസംഖ്യ new_area = new_overlap.w * new_overlap.h;
                ദശാംശം new_overlap_ratio = (new_area / ((ദശാംശം)old_area + new_area));
                എങ്കിൽ (new_overlap_ratio < 0.80) {
                    തിരികെ;
                }
            }
        }
    }

    എങ്കിൽ (displayID != window->displayID) {
        പൂർണ്ണസംഖ്യ i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            എങ്കിൽ (display->fullscreen_window == window) {
                എങ്കിൽ (display_index != i) {
                    എങ്കിൽ (display_index < 0) {
                        display_index = i;
                    } അല്ലെങ്കിൽ {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        എങ്കിൽ (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = ശൂന്യ;
                    }
                }
                നിർത്തുക;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (പൂർണ്ണസംഖ്യ)displayID, 0);
    }
}

ദശാംശം SDL_GetWindowPixelDensity(SDL_Window *window)
{
    പൂർണ്ണസംഖ്യ window_w, window_h, pixel_w, pixel_h;
    ദശാംശം pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    എങ്കിൽ (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (ദശാംശം)pixel_w / window_w;
    }
    തിരികെ pixel_density;
}

ദശാംശം SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    തിരികെ window->display_scale;
}

സ്ഥിതം ശൂന്യം SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    ദശാംശം display_scale;

    എങ്കിൽ (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } അല്ലെങ്കിൽ {
        സ്ഥിരം ദശാംശം pixel_density = SDL_GetWindowPixelDensity(window);
        സ്ഥിരം ദശാംശം content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    എങ്കിൽ (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ശൂന്യ;
    SDL_DisplayMode *mode = ശൂന്യ;
    പൂർണ്ണസംഖ്യ i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    എങ്കിൽ (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    എങ്കിൽ (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        എങ്കിൽ (!display) {
            // This should never happen, but it did...
            പോകുക done;
        }
    } അല്ലെങ്കിൽ {
        വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
            display = _this->displays[i];
            എങ്കിൽ (display->fullscreen_window == window) {
                നിർത്തുക;
            }
        }
        എങ്കിൽ (!display || i == _this->അക്കം_displays) {
            // Already not fullscreen on any display
            display = ശൂന്യ;
        }
    }

    എങ്കിൽ (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        എങ്കിൽ (mode) {
            window->fullscreen_exclusive = true;
        } അല്ലെങ്കിൽ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#എങ്കിൽ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    എങ്കിൽ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        എങ്കിൽ (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            എങ്കിൽ (display) {
                display->fullscreen_window = ശൂന്യ;
            }
            പോകുക done;
        }
        എങ്കിൽ (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            എങ്കിൽ (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                എങ്കിൽ (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    പോകുക error;
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    എങ്കിൽ (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, ശൂന്യ);
                        എങ്കിൽ (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = ശൂന്യ;
                    }
                }
            }

            എങ്കിൽ (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                പോകുക done;
            }
        }
    }
#endif

    എങ്കിൽ (display) {
        // Restore the video mode on other displays if needed
        വേണ്ടി (i = 0; i < _this->അക്കം_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            എങ്കിൽ (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, ശൂന്യ);
                other->fullscreen_window = ശൂന്യ;
            }
        }
    }

    എങ്കിൽ (fullscreen) {
        പൂർണ്ണസംഖ്യ mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        എങ്കിൽ (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        എങ്കിൽ (!SDL_SetDisplayModeForDisplay(display, mode)) {
            പോകുക error;
        }
        എങ്കിൽ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            എങ്കിൽ (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } അല്ലെങ്കിൽ {
                resized = true;
            }

            എങ്കിൽ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                പോകുക error;
            }
        }

        എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            എങ്കിൽ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                എങ്കിൽ (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } അല്ലെങ്കിൽ {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                എങ്കിൽ (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                എങ്കിൽ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } അല്ലെങ്കിൽ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } അല്ലെങ്കിൽ {
        bool resized = false;

        // Restore the desktop mode
        എങ്കിൽ (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, ശൂന്യ);
        }
        എങ്കിൽ (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            എങ്കിൽ (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                എങ്കിൽ (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } അല്ലെങ്കിൽ {
                resized = true;
            }

            എങ്കിൽ (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (ret == SDL_FULLSCREEN_FAILED) {
                പോകുക error;
            }
        }

        എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            എങ്കിൽ (display) {
                display->fullscreen_window = ശൂന്യ;
            }

            എങ്കിൽ (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                എങ്കിൽ (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } അല്ലെങ്കിൽ {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    തിരികെ true;

error:
    എങ്കിൽ (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    തിരികെ false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, സ്ഥിരം SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (mode) {
        എങ്കിൽ (!SDL_GetFullscreenModeMatch(mode)) {
            തിരികെ SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } അല്ലെങ്കിൽ {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#എങ്കിൽ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    എങ്കിൽ (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    എങ്കിൽ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    തിരികെ true;
}

സ്ഥിരം SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ശൂന്യ);
    CHECK_WINDOW_NOT_POPUP(window, ശൂന്യ);

    എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        തിരികെ SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

ശൂന്യം *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    എങ്കിൽ (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        തിരികെ ശൂന്യ;
    }
    തിരികെ _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    സ്ഥിരം SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    എങ്കിൽ (mode) {
        തിരികെ mode->format;
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_മുകളിലെ_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_മുകൾ | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

സ്ഥിതം SDL_INLINE bool IsAcceptingDragAndDrop(ശൂന്യം)
{
    എങ്കിൽ (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        തിരികെ true;
    }
    തിരികെ false;
}

// prepare a newly-created window
സ്ഥിതം SDL_INLINE ശൂന്യം PrepareDragAndDropSupport(SDL_Window *window)
{
    എങ്കിൽ (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
ശൂന്യം SDL_ToggleDragAndDropSupport(ശൂന്യം)
{
    എങ്കിൽ (_this && _this->AcceptDragAndDrop) {
        സ്ഥിരം bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        വേണ്ടി (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(പൂർണ്ണസംഖ്യ *എണ്ണം)
{
    എങ്കിൽ (എണ്ണം) {
        *എണ്ണം = 0;
    }

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }

    SDL_Window *window;
    പൂർണ്ണസംഖ്യ അക്കം_added = 0;
    പൂർണ്ണസംഖ്യ അക്കം_windows = 0;
    വേണ്ടി (window = _this->windows; window; window = window->next) {
        ++അക്കം_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((അക്കം_windows + 1) * വലുപ്പം(*windows));
    എങ്കിൽ (!windows) {
        തിരികെ ശൂന്യ;
    }

    വേണ്ടി (window = _this->windows; window; window = window->next) {
        windows[അക്കം_added++] = window;
        എങ്കിൽ (അക്കം_added == അക്കം_windows) {
            // Race condition? Multi-threading not supported, ignore it
            നിർത്തുക;
        }
    }
    windows[അക്കം_added] = ശൂന്യ;

    എങ്കിൽ (എണ്ണം) {
        *എണ്ണം = അക്കം_added;
    }
    തിരികെ windows;
}

സ്ഥിതം ശൂന്യം ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    എങ്കിൽ (!SDL_WINDOW_IS_POPUP(window)) {
        എങ്കിൽ (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        എങ്കിൽ (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        എങ്കിൽ (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        എങ്കിൽ (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        എങ്കിൽ (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        എങ്കിൽ (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

സ്ഥിതം ശൂന്യം SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } അല്ലെങ്കിൽ {
        ApplyWindowFlags(window, flags);
        എങ്കിൽ (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#എങ്കിൽ defined(SDL_PLATFORM_LINUX)
    എങ്കിൽ (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_മൂല്യം(window, 0.0f);
    }
#endif
}

സ്ഥിതം bool SDL_ContextNotSupported(സ്ഥിരം അക്ഷരം *name)
{
    തിരികെ SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

സ്ഥിതം bool SDL_DllNotSupported(സ്ഥിരം അക്ഷരം *name)
{
    തിരികെ SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

സ്ഥിതം ഘടന {
    സ്ഥിരം അക്ഷരം *property_name;
    SDL_WindowFlags flag;
    bool invert_മൂല്യം;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_മുകൾ_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_മുകൾ,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_മുകളിലെ_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_മുകളിലെ_PIXEL_DENSITY,  false },
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

സ്ഥിതം SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_സംഖ്യ, 0);

    വേണ്ടി (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        എങ്കിൽ (SDL_WindowFlagProperties[i].invert_മൂല്യം) {
            എങ്കിൽ (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    തിരികെ flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    സ്ഥിരം അക്ഷരം *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, ശൂന്യ);
    പൂർണ്ണസംഖ്യ x = (പൂർണ്ണസംഖ്യ)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_X_സംഖ്യ, SDL_WINDOWPOS_UNDEFINED);
    പൂർണ്ണസംഖ്യ y = (പൂർണ്ണസംഖ്യ)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_Y_സംഖ്യ, SDL_WINDOWPOS_UNDEFINED);
    പൂർണ്ണസംഖ്യ w = (പൂർണ്ണസംഖ്യ)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_സംഖ്യ, 0);
    പൂർണ്ണസംഖ്യ h = (പൂർണ്ണസംഖ്യ)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_സംഖ്യ, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, ശൂന്യ);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    എങ്കിൽ (!_this) {
        // Initialize the video system if needed
        എങ്കിൽ (!SDL_Init(SDL_INIT_VIDEO)) {
            തിരികെ ശൂന്യ;
        }

        // Make clang-tidy happy
        എങ്കിൽ (!_this) {
            തിരികെ ശൂന്യ;
        }
    }

    എങ്കിൽ ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        എങ്കിൽ (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            തിരികെ ശൂന്യ;
        }

        // Tooltip and popup menu window must specify a parent window
        എങ്കിൽ (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            തിരികെ ശൂന്യ;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    എങ്കിൽ (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned പൂർണ്ണസംഖ്യ)type_flags);
        തിരികെ ശൂന്യ;
    }

    // Make sure the display list is up to date for window placement
    എങ്കിൽ (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    എങ്കിൽ (w < 1) {
        w = 1;
    }
    എങ്കിൽ (h < 1) {
        h = 1;
    }

    എങ്കിൽ (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        എങ്കിൽ ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } അല്ലെങ്കിൽ എങ്കിൽ ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        എങ്കിൽ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        എങ്കിൽ (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        എങ്കിൽ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            എങ്കിൽ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        എങ്കിൽ (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            എങ്കിൽ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    എങ്കിൽ (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned പൂർണ്ണസംഖ്യ)graphics_flags);
        തിരികെ ശൂന്യ;
    }

    // Some platforms have certain graphics backends enabled by default
    എങ്കിൽ (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    എങ്കിൽ (flags & SDL_WINDOW_OPENGL) {
        എങ്കിൽ (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            തിരികെ ശൂന്യ;
        }
        എങ്കിൽ (!SDL_GL_LoadLibrary(ശൂന്യ)) {
            തിരികെ ശൂന്യ;
        }
    }

    എങ്കിൽ (flags & SDL_WINDOW_VULKAN) {
        എങ്കിൽ (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            തിരികെ ശൂന്യ;
        }
        എങ്കിൽ (!SDL_Vulkan_LoadLibrary(ശൂന്യ)) {
            തിരികെ ശൂന്യ;
        }
    }

    എങ്കിൽ (flags & SDL_WINDOW_METAL) {
        എങ്കിൽ (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            തിരികെ ശൂന്യ;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, വലുപ്പം(*window));
    എങ്കിൽ (!window) {
        തിരികെ ശൂന്യ;
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
    എങ്കിൽ (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    എങ്കിൽ (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    എങ്കിൽ (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    എങ്കിൽ (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    എങ്കിൽ (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_തള്ളുക_Error();
        SDL_DestroyWindow(window);
        SDL_എടുക്കുക_Error();
        തിരികെ ശൂന്യ;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#എങ്കിൽ !defined(SDL_PLATFORM_WINDOWS)
    എങ്കിൽ (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    എങ്കിൽ (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    തിരികെ window;
}

SDL_Window *SDL_CreateWindow(സ്ഥിരം അക്ഷരം *title, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    എങ്കിൽ (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_സംഖ്യ, w);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_സംഖ്യ, h);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_സംഖ്യ, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    തിരികെ window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, പൂർണ്ണസംഖ്യ offset_x, പൂർണ്ണസംഖ്യ offset_y, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    എങ്കിൽ (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        തിരികെ ശൂന്യ;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_X_സംഖ്യ, offset_x);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_Y_സംഖ്യ, offset_y);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_സംഖ്യ, w);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_സംഖ്യ, h);
    SDL_Set_സംഖ്യ_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_സംഖ്യ, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    തിരികെ window;
}

സ്ഥിതം bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    എങ്കിൽ (!_this->ReconfigureWindow) {
        തിരികെ false;
    }

    സ്ഥിരം SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    എങ്കിൽ (graphics_flags & (graphics_flags - 1)) {
        തിരികെ SDL_SetError("Conflicting window flags specified");
    }

    എങ്കിൽ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        തിരികെ SDL_ContextNotSupported("OpenGL");
    }
    എങ്കിൽ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        തിരികെ SDL_ContextNotSupported("Vulkan");
    }
    എങ്കിൽ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        തിരികെ SDL_ContextNotSupported("Metal");
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        എങ്കിൽ (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        എങ്കിൽ (!_this->ReconfigureWindow(_this, window, 0)) {
            തിരികെ false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        എങ്കിൽ (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    എങ്കിൽ (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(ശൂന്യ);
        എങ്കിൽ (!loaded_opengl) {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(ശൂന്യ);
        എങ്കിൽ (!loaded_vulkan) {
            തിരികെ false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    എങ്കിൽ (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        എങ്കിൽ (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        എങ്കിൽ (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        തിരികെ false;
    }

    window->flags |= graphics_flags;

    തിരികെ true;
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
    എങ്കിൽ (graphics_flags & (graphics_flags - 1)) {
        തിരികെ SDL_SetError("Conflicting window flags specified");
    }

    എങ്കിൽ ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        തിരികെ SDL_ContextNotSupported("OpenGL");
    }
    എങ്കിൽ ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        തിരികെ SDL_ContextNotSupported("Vulkan");
    }
    എങ്കിൽ ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        തിരികെ SDL_ContextNotSupported("Metal");
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } അല്ലെങ്കിൽ {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    എങ്കിൽ (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    എങ്കിൽ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        സ്ഥിരം bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    എങ്കിൽ ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        എങ്കിൽ (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } അല്ലെങ്കിൽ {
            need_gl_unload = true;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    എങ്കിൽ ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        എങ്കിൽ (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } അല്ലെങ്കിൽ {
            need_vulkan_unload = true;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    എങ്കിൽ (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    എങ്കിൽ (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    എങ്കിൽ (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    എങ്കിൽ (need_gl_load) {
        എങ്കിൽ (!SDL_GL_LoadLibrary(ശൂന്യ)) {
            തിരികെ false;
        }
        loaded_opengl = true;
    }

    എങ്കിൽ (need_vulkan_load) {
        എങ്കിൽ (!SDL_Vulkan_LoadLibrary(ശൂന്യ)) {
            തിരികെ false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    എങ്കിൽ (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        എങ്കിൽ (!_this->CreateSDLWindow(_this, window, 0)) {
            എങ്കിൽ (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            എങ്കിൽ (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            തിരികെ false;
        }
    }

    എങ്കിൽ (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    എങ്കിൽ (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    എങ്കിൽ (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    എങ്കിൽ (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    എങ്കിൽ (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    എങ്കിൽ (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    എങ്കിൽ (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    തിരികെ true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    എങ്കിൽ (!SDL_ReconfigureWindowInternal(window, flags)) {
        തിരികെ SDL_RecreateWindow(window, flags);
    }

    തിരികെ true;
}

bool SDL_HasWindows(ശൂന്യം)
{
    തിരികെ _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    തിരികെ window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    എങ്കിൽ (id) {
        വേണ്ടി (window = _this->windows; window; window = window->next) {
            എങ്കിൽ (window->id == id) {
                തിരികെ window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    തിരികെ ശൂന്യ;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ശൂന്യ);

    തിരികെ window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    എങ്കിൽ (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    തിരികെ window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    തിരികെ window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, സ്ഥിരം അക്ഷരം *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (title == window->title) {
        തിരികെ true;
    }
    എങ്കിൽ (!title) {
        title = "";
    }
    എങ്കിൽ (window->title && SDL_strcmp(title, window->title) == 0) {
        തിരികെ true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    എങ്കിൽ (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    തിരികെ true;
}

സ്ഥിരം അക്ഷരം *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    തിരികെ window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        തിരികെ SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    എങ്കിൽ (!window->icon) {
        തിരികെ false;
    }

    എങ്കിൽ (!_this->SetWindowIcon) {
        തിരികെ SDL_Unsupported();
    }

    തിരികെ _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    സ്ഥിരം പൂർണ്ണസംഖ്യ w = window->last_size_pending ? window->pending.w : window->windowed.w;
    സ്ഥിരം പൂർണ്ണസംഖ്യ h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    എങ്കിൽ (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    എങ്കിൽ (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    എങ്കിൽ (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        എങ്കിൽ (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } അല്ലെങ്കിൽ എങ്കിൽ (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        എങ്കിൽ (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        എങ്കിൽ (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            എങ്കിൽ (!SDL_GetDisplayBounds(displayID, &bounds)) {
                തിരികെ false;
            }
        }
        എങ്കിൽ (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        എങ്കിൽ (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } അല്ലെങ്കിൽ {
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
    എങ്കിൽ (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    എങ്കിൽ (_this->SetWindowPosition) {
        സ്ഥിരം bool result = _this->SetWindowPosition(_this, window);
        എങ്കിൽ (result) {
            SDL_SyncIfRequired(window);
        }
        തിരികെ result;
    }

    തിരികെ SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, പൂർണ്ണസംഖ്യ *x, പൂർണ്ണസംഖ്യ *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#അല്ലെങ്കിൽ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    എങ്കിൽ (use_display_origin) {
        SDL_DisplayID displayID;

        എങ്കിൽ (x) {
            *x = 0;
        }
        എങ്കിൽ (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        എങ്കിൽ (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            എങ്കിൽ (x) {
                *x = bounds.x;
            }
            എങ്കിൽ (y) {
                *y = bounds.y;
            }
        }
    } അല്ലെങ്കിൽ {
        സ്ഥിരം bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        എങ്കിൽ (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        എങ്കിൽ (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    തിരികെ true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (!_this->SetWindowBordered) {
        തിരികെ SDL_Unsupported();
    }

    സ്ഥിരം bool want = bordered;
    സ്ഥിരം bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    എങ്കിൽ (want != have) {
        എങ്കിൽ (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } അല്ലെങ്കിൽ {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    തിരികെ true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (!_this->SetWindowResizable) {
        തിരികെ SDL_Unsupported();
    }

    സ്ഥിരം bool want = resizable;
    സ്ഥിരം bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    എങ്കിൽ (want != have) {
        എങ്കിൽ (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } അല്ലെങ്കിൽ {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    തിരികെ true;
}

bool SDL_Set_Window_Always_On_മുകൾ(SDL_Window *window, bool on_മുകൾ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (!_this->Set_Window_Always_On_മുകൾ) {
        തിരികെ SDL_Unsupported();
    }

    സ്ഥിരം bool want = on_മുകൾ;
    സ്ഥിരം bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_മുകൾ) != 0);
    എങ്കിൽ (want != have) {
        എങ്കിൽ (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_മുകൾ;
        } അല്ലെങ്കിൽ {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_മുകൾ;
        }
        _this->Set_Window_Always_On_മുകൾ(_this, window, want);
    }

    തിരികെ true;
}

bool SDL_SetWindowSize(SDL_Window *window, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        തിരികെ SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        തിരികെ SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    ദശാംശം new_aspect = w / (ദശാംശം)h;
    എങ്കിൽ (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (പൂർണ്ണസംഖ്യ)SDL_roundf(h * window->max_aspect);
    } അല്ലെങ്കിൽ എങ്കിൽ (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (പൂർണ്ണസംഖ്യ)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    എങ്കിൽ (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    എങ്കിൽ (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    എങ്കിൽ (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    എങ്കിൽ (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    എങ്കിൽ (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_Unsupported();
    }
    തിരികെ true;
}

bool SDL_GetWindowSize(SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    എങ്കിൽ (w) {
        *w = window->w;
    }
    എങ്കിൽ (h) {
        *h = window->h;
    }
    തിരികെ true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, ദശാംശം min_aspect, ദശാംശം max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    എങ്കിൽ (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    പൂർണ്ണസംഖ്യ w = window->last_size_pending ? window->pending.w : window->floating.w;
    പൂർണ്ണസംഖ്യ h = window->last_size_pending ? window->pending.h : window->floating.h;
    തിരികെ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, ദശാംശം *min_aspect, ദശാംശം *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    എങ്കിൽ (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    തിരികെ true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, പൂർണ്ണസംഖ്യ *മുകൾ, പൂർണ്ണസംഖ്യ *ഇടത്, പൂർണ്ണസംഖ്യ *bottom, പൂർണ്ണസംഖ്യ *വലത്)
{
    പൂർണ്ണസംഖ്യ dummy = 0;

    എങ്കിൽ (!മുകൾ) {
        മുകൾ = &dummy;
    }
    എങ്കിൽ (!ഇടത്) {
        ഇടത് = &dummy;
    }
    എങ്കിൽ (!വലത്) {
        വലത് = &dummy;
    }
    എങ്കിൽ (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *മുകൾ = *ഇടത് = *bottom = *വലത് = 0;

    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!_this->GetWindowBordersSize) {
        തിരികെ SDL_Unsupported();
    }

    തിരികെ _this->GetWindowBordersSize(_this, window, മുകൾ, ഇടത്, bottom, വലത്);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h)
{
    പൂർണ്ണസംഖ്യ filter;

    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!w) {
        w = &filter;
    }

    എങ്കിൽ (!h) {
        h = &filter;
    }

    എങ്കിൽ (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } അല്ലെങ്കിൽ {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        സ്ഥിരം SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        എങ്കിൽ ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } അല്ലെങ്കിൽ {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        എങ്കിൽ (mode) {
            *w = (പൂർണ്ണസംഖ്യ)SDL_ceilf(*w * mode->pixel_density);
            *h = (പൂർണ്ണസംഖ്യ)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    തിരികെ true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, പൂർണ്ണസംഖ്യ min_w, പൂർണ്ണസംഖ്യ min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        തിരികെ SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        തിരികെ SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        തിരികെ SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    എങ്കിൽ (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    പൂർണ്ണസംഖ്യ w = window->last_size_pending ? window->pending.w : window->floating.w;
    പൂർണ്ണസംഖ്യ h = window->last_size_pending ? window->pending.h : window->floating.h;
    തിരികെ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, പൂർണ്ണസംഖ്യ *min_w, പൂർണ്ണസംഖ്യ *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    എങ്കിൽ (min_w) {
        *min_w = window->min_w;
    }
    എങ്കിൽ (min_h) {
        *min_h = window->min_h;
    }
    തിരികെ true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, പൂർണ്ണസംഖ്യ max_w, പൂർണ്ണസംഖ്യ max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        തിരികെ SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        തിരികെ SDL_InvalidParamError("max_h");
    }

    എങ്കിൽ ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        തിരികെ SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    എങ്കിൽ (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    പൂർണ്ണസംഖ്യ w = window->last_size_pending ? window->pending.w : window->floating.w;
    പൂർണ്ണസംഖ്യ h = window->last_size_pending ? window->pending.h : window->floating.h;
    തിരികെ SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, പൂർണ്ണസംഖ്യ *max_w, പൂർണ്ണസംഖ്യ *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    എങ്കിൽ (max_w) {
        *max_w = window->max_w;
    }
    എങ്കിൽ (max_h) {
        *max_h = window->max_h;
    }
    തിരികെ true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!(window->flags & SDL_WINDOW_HIDDEN)) {
        തിരികെ true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    എങ്കിൽ (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        തിരികെ true;
    }

    എങ്കിൽ (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } അല്ലെങ്കിൽ {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    വേണ്ടി (child = window->first_child; child; child = child->next_sibling) {
        എങ്കിൽ (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            നിർത്തുക;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    തിരികെ true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        തിരികെ true;
    }

    // Hide all child windows
    വേണ്ടി (child = window->first_child; child; child = child->next_sibling) {
        എങ്കിൽ (child->flags & SDL_WINDOW_HIDDEN) {
            നിർത്തുക;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    സ്ഥിരം SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    എങ്കിൽ (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } അല്ലെങ്കിൽ {
        SDL_SetMouseFocus(ശൂന്യ);
        SDL_SetKeyboardFocus(ശൂന്യ);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    തിരികെ true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        തിരികെ true;
    }
    എങ്കിൽ (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    തിരികെ true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (!_this->MaximizeWindow) {
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        തിരികെ SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        തിരികെ true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    തിരികെ true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (!_this->MinimizeWindow) {
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        തിരികെ true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    തിരികെ true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (!_this->RestoreWindow) {
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        തിരികെ true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    തിരികെ true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        എങ്കിൽ (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } അല്ലെങ്കിൽ {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        തിരികെ true;
    }

    എങ്കിൽ (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    എങ്കിൽ (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    എങ്കിൽ (result) {
        SDL_SyncIfRequired(window);
    }

    തിരികെ result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (_this->SyncWindow) {
        തിരികെ _this->SyncWindow(_this, window);
    } അല്ലെങ്കിൽ {
        തിരികെ true;
    }
}

സ്ഥിതം bool ShouldAttemptTextureFramebuffer(ശൂന്യം)
{
    സ്ഥിരം അക്ഷരം *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    എങ്കിൽ (!_this->CreateWindowFramebuffer) {
        തിരികെ true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    എങ്കിൽ (hint && *hint) {
        എങ്കിൽ (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } അല്ലെങ്കിൽ {
            attempt_texture_framebuffer = true;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } അല്ലെങ്കിൽ {
            attempt_texture_framebuffer = false;
        }
    }
    തിരികെ attempt_texture_framebuffer;
}

സ്ഥിതം SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    ശൂന്യം *pixels = ശൂന്യ;
    പൂർണ്ണസംഖ്യ pitch = 0;
    bool created_framebuffer = false;
    പൂർണ്ണസംഖ്യ w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    എങ്കിൽ (!_this->checked_texture_framebuffer) {
        എങ്കിൽ (ShouldAttemptTextureFramebuffer()) {
            എങ്കിൽ (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } അല്ലെങ്കിൽ {
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

    എങ്കിൽ (!created_framebuffer) {
        എങ്കിൽ (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            തിരികെ ശൂന്യ;
        }

        എങ്കിൽ (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            തിരികെ ശൂന്യ;
        }
    }

    എങ്കിൽ (window->surface) {
        // We may have gone recursive and already created the surface
        തിരികെ window->surface;
    }

    തിരികെ SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    തിരികെ window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ശൂന്യ);

    എങ്കിൽ (!window->surface_valid) {
        എങ്കിൽ (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = ശൂന്യ;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        എങ്കിൽ (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    തിരികെ window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, പൂർണ്ണസംഖ്യ vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!_this->SetWindowFramebufferVSync) {
        തിരികെ SDL_Unsupported();
    }
    തിരികെ _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, പൂർണ്ണസംഖ്യ *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!_this->GetWindowFramebufferVSync) {
        തിരികെ SDL_Unsupported();
    }
    തിരികെ _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    തിരികെ SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, സ്ഥിരം SDL_Rect *rects,
                                 പൂർണ്ണസംഖ്യ numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!window->surface_valid) {
        തിരികെ SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    തിരികെ _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = ശൂന്യ;
        window->surface_valid = false;
    }

    എങ്കിൽ (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        എങ്കിൽ (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    തിരികെ true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, ദശാംശം opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!_this->SetWindowOpacity) {
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (opacity < 0.0f) {
        opacity = 0.0f;
    } അല്ലെങ്കിൽ എങ്കിൽ (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    എങ്കിൽ (result) {
        window->opacity = opacity;
    }

    തിരികെ result;
}

ദശാംശം SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    തിരികെ window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    എങ്കിൽ (window == parent) {
        തിരികെ SDL_SetError("Cannot set the parent of a window to itself.");
    }

    എങ്കിൽ (!_this->SetWindowParent) {
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_MODAL) {
        തിരികെ SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    എങ്കിൽ (window->parent == parent) {
        തിരികെ true;
    }

    സ്ഥിരം bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : ശൂന്യ);

    തിരികെ ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (!_this->SetWindowModal) {
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (modal) {
        എങ്കിൽ (!window->parent) {
            തിരികെ SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } അല്ലെങ്കിൽ എങ്കിൽ (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } അല്ലെങ്കിൽ {
        തിരികെ true; // Already not modal, so nothing to do.
    }

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        തിരികെ true;
    }

    തിരികെ _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_നിവേശം_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    ആകുമ്പോൾ (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        എങ്കിൽ (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_നിവേശം_FOCUS);
        }
    }

    *new_focus = focus;
    തിരികെ set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    വേണ്ടി (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    വേണ്ടി (w = current_focus; w != toplevel_parent; w = w->parent) {
        എങ്കിൽ (w == window) {
            found_higher_focus = true;
            നിർത്തുക;
        }
    }

    തിരികെ !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    സ്ഥിരം bool want = (focusable != false); // normalize the flag.
    സ്ഥിരം bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    എങ്കിൽ ((want != have) && (_this->SetWindowFocusable)) {
        എങ്കിൽ (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } അല്ലെങ്കിൽ {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        എങ്കിൽ (!_this->SetWindowFocusable(_this, window, want)) {
            തിരികെ false;
        }
    }

    തിരികെ true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    സ്ഥിരം bool want = (fill != false); // normalize the flag.
    സ്ഥിരം bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    എങ്കിൽ ((want != have) && (_this->SetWindowFillDocument)) {
        എങ്കിൽ (!_this->SetWindowFillDocument(_this, window, want)) {
            തിരികെ false;
        } അല്ലെങ്കിൽ എങ്കിൽ (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } അല്ലെങ്കിൽ {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    തിരികെ true;
}

ശൂന്യം SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    എങ്കിൽ (window->flags & SDL_WINDOW_നിവേശം_FOCUS) {
        എങ്കിൽ (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } അല്ലെങ്കിൽ {
            mouse_grabbed = false;
        }

        എങ്കിൽ (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } അല്ലെങ്കിൽ {
            keyboard_grabbed = false;
        }
    } അല്ലെങ്കിൽ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    എങ്കിൽ (mouse_grabbed || keyboard_grabbed) {
        എങ്കിൽ (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            എങ്കിൽ (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            എങ്കിൽ (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->grabbed_window == window) {
        _this->grabbed_window = ശൂന്യ; // ungrabbing input.
    }

    എങ്കിൽ (_this->SetWindowMouseGrab) {
        എങ്കിൽ (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    എങ്കിൽ (_this->SetWindowKeyboardGrab) {
        എങ്കിൽ (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    എങ്കിൽ (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = ശൂന്യ;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        എങ്കിൽ (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } അല്ലെങ്കിൽ {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        തിരികെ true;
    }

    എങ്കിൽ (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        തിരികെ true;
    }
    എങ്കിൽ (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } അല്ലെങ്കിൽ {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    എങ്കിൽ (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        തിരികെ false;
    }
    തിരികെ true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (window->flags & SDL_WINDOW_HIDDEN) {
        എങ്കിൽ (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } അല്ലെങ്കിൽ {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        തിരികെ true;
    }

    എങ്കിൽ (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        തിരികെ true;
    }
    എങ്കിൽ (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } അല്ലെങ്കിൽ {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    എങ്കിൽ (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        തിരികെ false;
    }
    തിരികെ true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    തിരികെ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    തിരികെ window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(ശൂന്യം)
{
    എങ്കിൽ (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        തിരികെ _this->grabbed_window;
    } അല്ലെങ്കിൽ {
        തിരികെ ശൂന്യ;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, സ്ഥിരം SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!_this->SetWindowMouseRect) {
        തിരികെ SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    എങ്കിൽ (!rect) {
        rect = &zero;
    }

    എങ്കിൽ (SDL_memcmp(&window->mouse_rect, rect, വലുപ്പം(*rect)) == 0) {
        തിരികെ true;
    }
    SDL_memcpy(&window->mouse_rect, rect, വലുപ്പം(*rect));

    തിരികെ _this->SetWindowMouseRect(_this, window);
}

സ്ഥിരം SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ശൂന്യ);

    എങ്കിൽ (SDL_RectEmpty(&window->mouse_rect)) {
        തിരികെ ശൂന്യ;
    } അല്ലെങ്കിൽ {
        തിരികെ &window->mouse_rect;
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

    എങ്കിൽ (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        തിരികെ true;
    }

    എങ്കിൽ (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } അല്ലെങ്കിൽ {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    എങ്കിൽ (!SDL_UpdateRelativeMouseMode()) {
        എങ്കിൽ (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } അല്ലെങ്കിൽ {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        തിരികെ false;
    }
    തിരികെ true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        തിരികെ false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (_this->FlashWindow) {
        തിരികെ _this->FlashWindow(_this, window, operation);
    }

    തിരികെ SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        തിരികെ SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    എങ്കിൽ (_this->ApplyWindowProgress) {
        എങ്കിൽ (!_this->ApplyWindowProgress(_this, window)) {
            തിരികെ false;
        }
    }

    തിരികെ true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    തിരികെ window->progress_state;
}

bool SDL_Set_Window_Progress_മൂല്യം(SDL_Window *window, ദശാംശം മൂല്യം)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    മൂല്യം = SDL_clamp(മൂല്യം, 0.0f, 1.f);

    window->progress_മൂല്യം = മൂല്യം;

    എങ്കിൽ (_this->ApplyWindowProgress) {
        എങ്കിൽ (!_this->ApplyWindowProgress(_this, window)) {
            തിരികെ false;
        }
    }

    തിരികെ true;
}

ദശാംശം SDL_Get_Window_Progress_മൂല്യം(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    തിരികെ window->progress_മൂല്യം;
}

ശൂന്യം SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

ശൂന്യം SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

ശൂന്യം SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    എങ്കിൽ (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        സ്ഥിരം bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        എങ്കിൽ (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_മുകളിലെ_density_modes = false;

            എങ്കിൽ (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_മുകളിലെ_density_modes = true;
            }
            സ്ഥിരം bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_മുകളിലെ_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            എങ്കിൽ (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } അല്ലെങ്കിൽ {
            SDL_zero(window->current_fullscreen_mode);
        }

        എങ്കിൽ (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

ശൂന്യം SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

ശൂന്യം SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    എങ്കിൽ ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, ശൂന്യ);
        എങ്കിൽ (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

ശൂന്യം SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    പൂർണ്ണസംഖ്യ pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

ശൂന്യം SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

ശൂന്യം SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    എങ്കിൽ (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } അല്ലെങ്കിൽ {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

സ്ഥിതം ശൂന്യം SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_ഇടത്;
    rect.y = window->safe_inset_മുകൾ;
    rect.w = window->w - (window->safe_inset_വലത് + window->safe_inset_ഇടത്);
    rect.h = window->h - (window->safe_inset_മുകൾ + window->safe_inset_bottom);
    എങ്കിൽ (SDL_memcmp(&rect, &window->safe_rect, വലുപ്പം(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

ശൂന്യം SDL_SetWindowSafeAreaInsets(SDL_Window *window, പൂർണ്ണസംഖ്യ ഇടത്, പൂർണ്ണസംഖ്യ വലത്, പൂർണ്ണസംഖ്യ മുകൾ, പൂർണ്ണസംഖ്യ bottom)
{
    window->safe_inset_ഇടത് = ഇടത്;
    window->safe_inset_വലത് = വലത്;
    window->safe_inset_മുകൾ = മുകൾ;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    എങ്കിൽ (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (rect) {
        എങ്കിൽ (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } അല്ലെങ്കിൽ {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    തിരികെ true;
}

ശൂന്യം SDL_OnWindowMinimized(SDL_Window *window)
{
    എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

ശൂന്യം SDL_OnWindowMaximized(SDL_Window *window)
{
}

ശൂന്യം SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    എങ്കിൽ (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

ശൂന്യം SDL_OnWindowEnter(SDL_Window *window)
{
    എങ്കിൽ (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

ശൂന്യം SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

ശൂന്യം SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    എങ്കിൽ (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

സ്ഥിതം bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    സ്ഥിരം അക്ഷരം *hint;

    എങ്കിൽ (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        തിരികെ false;
    }

#എങ്കിൽ defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    എങ്കിൽ (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        എങ്കിൽ (Cocoa_IsShowingModalDialog(window)) {
            തിരികെ false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } അല്ലെങ്കിൽ എങ്കിൽ (Cocoa_IsWindowInFullscreenSpace(window)) {
            തിരികെ false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        ബാഹ്യ bool Android_JNI_ShouldMinimizeOnFocusLoss(ശൂന്യം);
        എങ്കിൽ (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            തിരികെ false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    എങ്കിൽ (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        എങ്കിൽ (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            തിരികെ true;
        } അല്ലെങ്കിൽ {
            തിരികെ false;
        }
    }
    തിരികെ SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

ശൂന്യം SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    എങ്കിൽ (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(ശൂന്യം)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    എങ്കിൽ (focus) {
        // Get the toplevel parent window.
        ആകുമ്പോൾ (focus->parent) {
            focus = focus->parent;
        }
    }

    തിരികെ focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->അക്കം_renderers + 1) * വലുപ്പം(*renderers));
    എങ്കിൽ (!renderers) {
        തിരികെ false;
    }

    window->renderers = renderers;
    window->renderers[window->അക്കം_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    തിരികെ true;
}

ശൂന്യം SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < window->അക്കം_renderers; ++i) {
        എങ്കിൽ (window->renderers[i] == renderer) {
            എങ്കിൽ (i < (window->അക്കം_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->അക്കം_renderers - i - 1) * വലുപ്പം(window->renderers[i]));
            }
            --window->അക്കം_renderers;
            നിർത്തുക;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    എങ്കിൽ (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, ശൂന്യ) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

ശൂന്യം SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    ആകുമ്പോൾ (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    എങ്കിൽ (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    എങ്കിൽ (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_നിവേശം_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    എങ്കിൽ (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; ++i) {
        എങ്കിൽ (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = ശൂന്യ;
        }
    }

    // Make sure this window no longer has focus
    എങ്കിൽ (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(ശൂന്യ);
    }
    എങ്കിൽ ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    എങ്കിൽ (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(ശൂന്യ);
    }

    // Make no context current if this is the current context window
    എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
        എങ്കിൽ (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, ശൂന്യ);
        }
    }

    എങ്കിൽ (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    എങ്കിൽ (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    എങ്കിൽ (_this->grabbed_window == window) {
        _this->grabbed_window = ശൂന്യ; // ungrabbing input.
    }

    എങ്കിൽ (_this->current_glwin == window) {
        _this->current_glwin = ശൂന്യ;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, ശൂന്യ);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, ശൂന്യ);

    // Unlink the window from the global window list
    എങ്കിൽ (window->next) {
        window->next->prev = window->prev;
    }
    എങ്കിൽ (window->prev) {
        window->prev->next = window->next;
    } അല്ലെങ്കിൽ {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        തിരികെ true;
    }
    തിരികെ !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }
    എങ്കിൽ (!_this->suspend_screensaver) {
        തിരികെ true;
    }
    _this->suspend_screensaver = false;
    എങ്കിൽ (_this->SuspendScreenSaver) {
        തിരികെ _this->SuspendScreenSaver(_this);
    }

    തിരികെ SDL_Unsupported();
}

bool SDL_DisableScreenSaver(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }
    എങ്കിൽ (_this->suspend_screensaver) {
        തിരികെ true;
    }
    _this->suspend_screensaver = true;
    എങ്കിൽ (_this->SuspendScreenSaver) {
        തിരികെ _this->SuspendScreenSaver(_this);
    }

    തിരികെ SDL_Unsupported();
}

ശൂന്യം SDL_QuitVideo(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (!_this) {
        തിരികെ;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#എങ്കിൽ 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    ആകുമ്പോൾ (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    എങ്കിൽ (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    എങ്കിൽ (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    വേണ്ടി (i = _this->അക്കം_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->അക്കം_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ശൂന്യ;

    SDL_CancelClipboardData(0);

    എങ്കിൽ (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = ശൂന്യ;
    }
    _this->സ്വതന്ത്രം(_this);
    _this = ശൂന്യ;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(സ്ഥിരം അക്ഷരം *path)
{
    bool result;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }
    എങ്കിൽ (_this->gl_config.driver_loaded) {
        എങ്കിൽ (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            തിരികെ SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!_this->GL_LoadLibrary) {
            തിരികെ SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    എങ്കിൽ (result) {
        ++_this->gl_config.driver_loaded;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    തിരികെ result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(സ്ഥിരം അക്ഷരം *proc)
{
    SDL_FunctionPointer func;

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    func = ശൂന്യ;
    എങ്കിൽ (_this->GL_GetProcAddress) {
        എങ്കിൽ (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } അല്ലെങ്കിൽ {
            SDL_SetError("No GL driver has been loaded");
        }
    } അല്ലെങ്കിൽ {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    തിരികെ func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(സ്ഥിരം അക്ഷരം *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    func = ശൂന്യ;

    എങ്കിൽ (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } അല്ലെങ്കിൽ {
        SDL_SetError("No EGL library has been loaded");
    }

    തിരികെ func;
#അല്ലെങ്കിൽ
    SDL_SetError("SDL was not built with EGL support");
    തിരികെ ശൂന്യ;
#endif
}

ശൂന്യം SDL_GL_UnloadLibrary(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ;
    }
    എങ്കിൽ (_this->gl_config.driver_loaded > 0) {
        എങ്കിൽ (--_this->gl_config.driver_loaded > 0) {
            തിരികെ;
        }
        എങ്കിൽ (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#എങ്കിൽ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
തരനിർവചനം GLenum (APIENTRY* PFNGLGETERRORPROC) (ശൂന്യം);
തരനിർവചനം ശൂന്യം (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
തരനിർവചനം സ്ഥിരം GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
തരനിർവചനം ശൂന്യം (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
തരനിർവചനം സ്ഥിരം GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

സ്ഥിതം SDL_INLINE bool isAtLeastGL3(സ്ഥിരം അക്ഷരം *verstr)
{
    തിരികെ verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(സ്ഥിരം അക്ഷരം *extension)
{
#എങ്കിൽ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    സ്ഥിരം അക്ഷരം *extensions;
    സ്ഥിരം അക്ഷരം *start;
    സ്ഥിരം അക്ഷരം *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    എങ്കിൽ (where || *extension == '\0') {
        തിരികെ false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    എങ്കിൽ (start && *start == '0') {
        തിരികെ false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    എങ്കിൽ (!glGetStringFunc) {
        തിരികെ false;
    }

    എങ്കിൽ (isAtLeastGL3((സ്ഥിരം അക്ഷരം *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint അക്കം_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        എങ്കിൽ ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            തിരികെ false;
        }

#ifndef GL_അക്കം_EXTENSIONS
#define GL_അക്കം_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_അക്കം_EXTENSIONS, &അക്കം_exts);
        വേണ്ടി (i = 0; i < അക്കം_exts; i++) {
            സ്ഥിരം അക്ഷരം *thisext = (സ്ഥിരം അക്ഷരം *)glGetStringiFunc(GL_EXTENSIONS, i);
            എങ്കിൽ (SDL_strcmp(thisext, extension) == 0) {
                തിരികെ true;
            }
        }

        തിരികെ false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (സ്ഥിരം അക്ഷരം *)glGetStringFunc(GL_EXTENSIONS);
    എങ്കിൽ (!extensions) {
        തിരികെ false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    വേണ്ടി (;;) {
        where = SDL_strstr(start, extension);
        എങ്കിൽ (!where) {
            നിർത്തുക;
        }

        terminator = where + SDL_strlen(extension);
        എങ്കിൽ (where == extensions || *(where - 1) == ' ') {
            എങ്കിൽ (*terminator == ' ' || *terminator == '\0') {
                തിരികെ true;
            }
        }

        start = terminator;
    }
    തിരികെ false;
#അല്ലെങ്കിൽ
    തിരികെ false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
ശൂന്യം SDL_GL_DeduceMaxSupportedESProfile(പൂർണ്ണസംഖ്യ *major, പൂർണ്ണസംഖ്യ *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#എങ്കിൽ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    എങ്കിൽ (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } അല്ലെങ്കിൽ {
        *major = 2;
        *minor = 0;
    }
#endif
}

ശൂന്യം SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   ശൂന്യം *userdata)
{
    എങ്കിൽ (!_this) {
        തിരികെ;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

ശൂന്യം SDL_GL_ResetAttributes(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        തിരികെ;
    }

    _this->egl_platformattrib_callback = ശൂന്യ;
    _this->egl_surfaceattrib_callback = ശൂന്യ;
    _this->egl_contextattrib_callback = ശൂന്യ;
    _this->egl_attrib_callback_userdata = ശൂന്യ;

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
#അല്ലെങ്കിലെങ്കിൽ defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#അല്ലെങ്കിലെങ്കിൽ defined(SDL_VIDEO_OPENGL_ES)
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

    എങ്കിൽ (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, പൂർണ്ണസംഖ്യ മൂല്യം)
{
#എങ്കിൽ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }
    result = true;
    തിരഞ്ഞെടുപ്പ് (attr) {
    അവസ്ഥ SDL_GL_RED_SIZE:
        _this->gl_config.red_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_STEREO:
        _this->gl_config.stereo = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_FLAGS:
        എങ്കിൽ (മൂല്യം & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", മൂല്യം);
            നിർത്തുക;
        }
        _this->gl_config.flags = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_PROFILE_MASK:
        എങ്കിൽ (മൂല്യം != 0 &&
            മൂല്യം != SDL_GL_CONTEXT_PROFILE_CORE &&
            മൂല്യം != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            മൂല്യം != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", മൂല്യം);
            നിർത്തുക;
        }
        _this->gl_config.profile_mask = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = മൂല്യം;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = മൂല്യം;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        result = SDL_SetError("Unknown OpenGL attribute");
        നിർത്തുക;
    }
    തിരികെ result;
#അല്ലെങ്കിൽ
    തിരികെ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, പൂർണ്ണസംഖ്യ *മൂല്യം)
{
#എങ്കിൽ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_ഇടത്;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!മൂല്യം) {
        തിരികെ SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *മൂല്യം = 0;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    തിരഞ്ഞെടുപ്പ് (attr) {
    അവസ്ഥ SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        നിർത്തുക;
#അല്ലെങ്കിൽ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *മൂല്യം = _this->gl_config.double_buffer;
        തിരികെ true;
#endif
    അവസ്ഥ SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        നിർത്തുക;
#ifdef SDL_VIDEO_OPENGL
    അവസ്ഥ SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_STEREO:
        attrib = GL_STEREO;
        നിർത്തുക;
#അല്ലെങ്കിൽ
    അവസ്ഥ SDL_GL_ACCUM_RED_SIZE:
    അവസ്ഥ SDL_GL_ACCUM_GREEN_SIZE:
    അവസ്ഥ SDL_GL_ACCUM_BLUE_SIZE:
    അവസ്ഥ SDL_GL_ACCUM_ALPHA_SIZE:
    അവസ്ഥ SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *മൂല്യം = 0;
        തിരികെ true;
#endif
    അവസ്ഥ SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        നിർത്തുക;
    അവസ്ഥ SDL_GL_BUFFER_SIZE:
    {
        പൂർണ്ണസംഖ്യ rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        എങ്കിൽ (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            തിരികെ false;
        }
        എങ്കിൽ (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            തിരികെ false;
        }
        എങ്കിൽ (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            തിരികെ false;
        }
        എങ്കിൽ (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            തിരികെ false;
        }

        *മൂല്യം = rsize + gsize + bsize + asize;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *മൂല്യം = (_this->gl_config.accelerated != 0);
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_RETAINED_BACKING:
    {
        *മൂല്യം = _this->gl_config.retained_backing;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *മൂല്യം = _this->gl_config.major_version;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *മൂല്യം = _this->gl_config.minor_version;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_CONTEXT_FLAGS:
    {
        *മൂല്യം = _this->gl_config.flags;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *മൂല്യം = _this->gl_config.profile_mask;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *മൂല്യം = _this->gl_config.share_with_current_context;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *മൂല്യം = _this->gl_config.framebuffer_srgb_capable;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_CONTEXT_NO_ERROR:
    {
        *മൂല്യം = _this->gl_config.no_error;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_EGL_PLATFORM:
    {
        *മൂല്യം = _this->gl_config.egl_platform;
        തിരികെ true;
    }
    അവസ്ഥ SDL_GL_FLOATBUFFERS:
    {
        എങ്കിൽ (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            നിർത്തുക;
        } അല്ലെങ്കിൽ {
            തിരികെ 0;
        }
    }
    സ്ഥിരസ്ഥിതി:
        തിരികെ SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    എങ്കിൽ (!glGetStringFunc) {
        തിരികെ false;
    }

    എങ്കിൽ (attachmentattrib && isAtLeastGL3((സ്ഥിരം അക്ഷരം *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        എങ്കിൽ (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        എങ്കിൽ (glGetFramebufferAttachmentParameterivFunc) {
            എങ്കിൽ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            എങ്കിൽ (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            എങ്കിൽ (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)മൂല്യം);
            } അല്ലെങ്കിൽ {
                *മൂല്യം = 0;
            }
            എങ്കിൽ (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } അല്ലെങ്കിൽ {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        എങ്കിൽ (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)മൂല്യം);
        } അല്ലെങ്കിൽ {
            തിരികെ false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    എങ്കിൽ (!glGetErrorFunc) {
        തിരികെ false;
    }

    error = glGetErrorFunc();
    എങ്കിൽ (error != GL_NO_ERROR) {
        എങ്കിൽ (error == GL_INVALID_ENUM) {
            തിരികെ SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } അല്ലെങ്കിൽ എങ്കിൽ (error == GL_INVALID_മൂല്യം) {
            തിരികെ SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        തിരികെ SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    എങ്കിൽ (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *മൂല്യം = (*മൂല്യം == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    തിരികെ true;
#അല്ലെങ്കിൽ
    തിരികെ SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = ശൂന്യ;
    CHECK_WINDOW_MAGIC(window, ശൂന്യ);

    എങ്കിൽ (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        തിരികെ ശൂന്യ;
    }

#എങ്കിൽ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    പൂർണ്ണസംഖ്യ srgb_requested = -1;
    സ്ഥിരം അക്ഷരം *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    എങ്കിൽ (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    എങ്കിൽ (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, ശൂന്യ);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, ശൂന്യ);
    }

#എങ്കിൽ defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    എങ്കിൽ (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        എങ്കിൽ (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            എങ്കിൽ (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } അല്ലെങ്കിൽ {
                supported = isAtLeastGL3((സ്ഥിരം അക്ഷരം *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            എങ്കിൽ (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    തിരികെ ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }

    എങ്കിൽ (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        തിരികെ true;
    }

    എങ്കിൽ (!context) {
        window = ശൂന്യ;
    } അല്ലെങ്കിൽ എങ്കിൽ (window) {
        CHECK_WINDOW_MAGIC(window, false);

        എങ്കിൽ (!(window->flags & SDL_WINDOW_OPENGL)) {
            തിരികെ SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (!_this->gl_allow_no_surface) {
        തിരികെ SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    എങ്കിൽ (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, ശൂന്യ);
        SDL_SetTLS(&_this->current_glctx_tls, context, ശൂന്യ);
    }
    തിരികെ result;
}

SDL_Window *SDL_GL_GetCurrentWindow(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    തിരികെ (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    തിരികെ (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(ശൂന്യം)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ EGL_NO_DISPLAY;
    }
    എങ്കിൽ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        തിരികെ EGL_NO_DISPLAY;
    }
    തിരികെ _this->egl_data->egl_display;
#അല്ലെങ്കിൽ
    SDL_SetError("SDL was not built with EGL support");
    തിരികെ ശൂന്യ;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(ശൂന്യം)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    എങ്കിൽ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        തിരികെ ശൂന്യ;
    }
    തിരികെ _this->egl_data->egl_config;
#അല്ലെങ്കിൽ
    SDL_SetError("SDL was not built with EGL support");
    തിരികെ ശൂന്യ;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    എങ്കിൽ (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        തിരികെ ശൂന്യ;
    }
    എങ്കിൽ (_this->GL_GetEGLSurface) {
        തിരികെ _this->GL_GetEGLSurface(_this, window);
    }
    തിരികെ ശൂന്യ;
#അല്ലെങ്കിൽ
    SDL_SetError("SDL was not built with EGL support");
    തിരികെ ശൂന്യ;
#endif
}

bool SDL_GL_SetSwapInterval(പൂർണ്ണസംഖ്യ interval)
{
    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_GL_GetCurrentContext() == ശൂന്യ) {
        തിരികെ SDL_SetError("No OpenGL context has been made current");
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->GL_SetSwapInterval) {
        തിരികെ _this->GL_SetSwapInterval(_this, interval);
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(പൂർണ്ണസംഖ്യ *interval)
{
    CHECK_PARAM(!interval) {
       തിരികെ SDL_InvalidParamError("interval");
    }

    *interval = 0;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_SetError("no video driver");
    } അല്ലെങ്കിൽ എങ്കിൽ (SDL_GL_GetCurrentContext() == ശൂന്യ) {
        തിരികെ SDL_SetError("no current context");
    } അല്ലെങ്കിൽ എങ്കിൽ (_this->GL_GetSwapInterval) {
        തിരികെ _this->GL_GetSwapInterval(_this, interval);
    } അല്ലെങ്കിൽ {
        തിരികെ SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!(window->flags & SDL_WINDOW_OPENGL)) {
        തിരികെ SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    എങ്കിൽ (SDL_GL_GetCurrentWindow() != window) {
        തിരികെ SDL_SetError("The specified window has not been made current");
    }

    തിരികെ _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        തിരികെ SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        തിരികെ SDL_InvalidParamError("context");
    }

    എങ്കിൽ (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ശൂന്യ, ശൂന്യ);
    }

    തിരികെ _this->GL_DestroyContext(_this, context);
}

#എങ്കിൽ 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
സ്ഥിതം ശൂന്യം Create_Mask_From_Color_താക്കോൽ_Or_Alpha(SDL_Surface *icon, Uint8 *mask, പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    തിരഞ്ഞെടുപ്പ് (SDL_BYTESPERPIXEL(icon->format)) {
    അവസ്ഥ 1:
        {
            Uint8 *pixels;
            വേണ്ടി (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                വേണ്ടി (x = 0; x < icon->w; ++x) {
                    എങ്കിൽ (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        നിർത്തുക;

    അവസ്ഥ 2:
        {
            Uint16 *pixels;
            വേണ്ടി (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                വേണ്ടി (x = 0; x < icon->w; ++x) {
                    എങ്കിൽ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } അല്ലെങ്കിൽ എങ്കിൽ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        നിർത്തുക;

    അവസ്ഥ 4:
        {
            Uint32 *pixels;
            വേണ്ടി (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                വേണ്ടി (x = 0; x < icon->w; ++x) {
                    എങ്കിൽ ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } അല്ലെങ്കിൽ എങ്കിൽ ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        നിർത്തുക;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
ശൂന്യം SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    എങ്കിൽ (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        എങ്കിൽ (mask == ശൂന്യ) {
            പൂർണ്ണസംഖ്യ mask_len = icon->h * (icon->w + 7) / 8;
            പൂർണ്ണസംഖ്യ flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            എങ്കിൽ (mask == ശൂന്യ) {
                തിരികെ;
            }
            SDL_memset(mask, ~0, mask_len);
            എങ്കിൽ (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            എങ്കിൽ (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            എങ്കിൽ (flags) {
                Create_Mask_From_Color_താക്കോൽ_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } അല്ലെങ്കിൽ {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_നിവേശം_Type SDL_Get_Text_നിവേശം_Type(SDL_PropertiesID props)
{
    തിരികെ (SDL_Text_നിവേശം_Type)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_TEXTINPUT_TYPE_സംഖ്യ, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_നിവേശം_Capitalization(SDL_PropertiesID props)
{
    എങ്കിൽ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_സംഖ്യ)) {
        തിരികെ (SDL_Capitalization)SDL_Get_സംഖ്യ_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_സംഖ്യ, SDL_CAPITALIZE_NONE);
    }

    തിരഞ്ഞെടുപ്പ് (SDL_Get_Text_നിവേശം_Type(props)) {
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT:
        തിരികെ SDL_CAPITALIZE_SENTENCES;
    അവസ്ഥ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        തിരികെ SDL_CAPITALIZE_വാക്കുകൾ;
    സ്ഥിരസ്ഥിതി:
        തിരികെ SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_നിവേശം_Autocorrect(SDL_PropertiesID props)
{
    തിരികെ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_നിവേശം_Multiline(SDL_PropertiesID props)
{
    എങ്കിൽ (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        തിരികെ SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_RETURN_താക്കോൽ_HIDES_IME, false)) {
        തിരികെ false;
    } അല്ലെങ്കിൽ {
        തിരികെ true;
    }
}

സ്ഥിതം bool AutoShowingScreenKeyboard(ശൂന്യം)
{
    സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    എങ്കിൽ (!hint) {
        // This hint is currently only used by the X11 video driver
        എങ്കിൽ (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    എങ്കിൽ (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        തിരികെ false;
    }
}

bool SDL_Start_Text_നിവേശം(SDL_Window *window)
{
    തിരികെ SDL_Start_Text_നിവേശം_With_Properties(window, 0);
}

bool SDL_Start_Text_നിവേശം_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (window->text_നിവേശം_props) {
        SDL_DestroyProperties(window->text_നിവേശം_props);
        window->text_നിവേശം_props = 0;
    }

    എങ്കിൽ (props) {
        window->text_നിവേശം_props = SDL_CreateProperties();
        എങ്കിൽ (!window->text_നിവേശം_props) {
            തിരികെ false;
        }
        എങ്കിൽ (!SDL_CopyProperties(props, window->text_നിവേശം_props)) {
            തിരികെ false;
        }
    }

    എങ്കിൽ (_this->Set_Text_നിവേശം_Properties) {
        _this->Set_Text_നിവേശം_Properties(_this, window, props);
    }

    എങ്കിൽ (!window->text_നിവേശം_active) {
        // Start the text input system
        എങ്കിൽ (_this->Start_Text_നിവേശം) {
            എങ്കിൽ (!_this->Start_Text_നിവേശം(_this, window, props)) {
                തിരികെ false;
            }
        }
        window->text_നിവേശം_active = true;
    }

    // Show the on-screen keyboard, if desired
    എങ്കിൽ (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        എങ്കിൽ (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    തിരികെ true;
}

bool SDL_Text_നിവേശം_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    തിരികെ window->text_നിവേശം_active;
}

bool SDL_Stop_Text_നിവേശം(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (window->text_നിവേശം_active) {
        // Stop the text input system
        എങ്കിൽ (_this->Stop_Text_നിവേശം) {
            _this->Stop_Text_നിവേശം(_this, window);
        }
        window->text_നിവേശം_active = false;
    }

    // Hide the on-screen keyboard, if desired
    എങ്കിൽ (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        എങ്കിൽ (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    തിരികെ true;
}

bool SDL_Set_Text_നിവേശം_Area(SDL_Window *window, സ്ഥിരം SDL_Rect *rect, പൂർണ്ണസംഖ്യ cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (rect) {
        SDL_copyp(&window->text_നിവേശം_rect, rect);
        window->text_നിവേശം_cursor = cursor;
    } അല്ലെങ്കിൽ {
        SDL_zero(window->text_നിവേശം_rect);
        window->text_നിവേശം_cursor = 0;
    }

    എങ്കിൽ (_this && _this->Update_Text_നിവേശം_Area) {
        എങ്കിൽ (!_this->Update_Text_നിവേശം_Area(_this, window)) {
            തിരികെ false;
        }
    }
    തിരികെ true;
}

bool SDL_Get_Text_നിവേശം_Area(SDL_Window *window, SDL_Rect *rect, പൂർണ്ണസംഖ്യ *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (rect) {
        SDL_copyp(rect, &window->text_നിവേശം_rect);
    }
    എങ്കിൽ (cursor) {
        *cursor = window->text_നിവേശം_cursor;
    }
    തിരികെ true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (_this->ClearComposition) {
        തിരികെ _this->ClearComposition(_this, window);
    }
    തിരികെ true;
}

bool SDL_HasScreenKeyboardSupport(ശൂന്യം)
{
    എങ്കിൽ (_this && _this->HasScreenKeyboardSupport) {
        തിരികെ _this->HasScreenKeyboardSupport(_this);
    }
    തിരികെ false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    തിരികെ _this->screen_keyboard_shown;
}

ശൂന്യം SDL_SendScreenKeyboardShown(ശൂന്യം)
{
    എങ്കിൽ (!_this || _this->screen_keyboard_shown) {
        തിരികെ;
    }

    _this->screen_keyboard_shown = true;

    എങ്കിൽ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_തള്ളുക_Event(&event);
    }
}

ശൂന്യം SDL_SendScreenKeyboardHidden(ശൂന്യം)
{
    എങ്കിൽ (!_this || !_this->screen_keyboard_shown) {
        തിരികെ;
    }

    _this->screen_keyboard_shown = false;

    എങ്കിൽ (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_തള്ളുക_Event(&event);
    }
}

പൂർണ്ണസംഖ്യ SDL_Get_Message_Box_എണ്ണം(ശൂന്യം)
{
    തിരികെ SDL_GetAtomicInt(&SDL_messagebox_എണ്ണം);
}

bool SDL_ShowMessageBox(സ്ഥിരം SDL_MessageBoxData *messageboxdata, പൂർണ്ണസംഖ്യ *buttonID)
{
    പൂർണ്ണസംഖ്യ dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        തിരികെ SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        തിരികെ SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    അക്ഷരം *titlecpy = ശൂന്യ;
    അക്ഷരം *msgcpy = ശൂന്യ;
    എങ്കിൽ (messageboxdata->title) {
        സ്ഥിരം size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(അക്ഷരം, slen, &titleisstack);
        എങ്കിൽ (!titlecpy) {
            തിരികെ false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    എങ്കിൽ (messageboxdata->message) {
        സ്ഥിരം size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(അക്ഷരം, slen, &msgisstack);
        എങ്കിൽ (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            തിരികെ false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (ശൂന്യം)SDL_AtomicIncRef(&SDL_messagebox_എണ്ണം);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    എങ്കിൽ (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, വലുപ്പം(*messageboxdata));
    mbdata.title = titlecpy;
    എങ്കിൽ (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    എങ്കിൽ (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    എങ്കിൽ (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } അല്ലെങ്കിൽ {
        // It's completely fine to call this function before video is initialized
        സ്ഥിരം അക്ഷരം *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        എങ്കിൽ (driver_name && *driver_name != 0) {
            സ്ഥിരം അക്ഷരം *driver_attempt = driver_name;
            ആകുമ്പോൾ (driver_attempt && (*driver_attempt != 0) && !result) {
                സ്ഥിരം അക്ഷരം *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; bootstrap[i]; ++i) {
                    എങ്കിൽ (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        എങ്കിൽ (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        നിർത്തുക;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ശൂന്യ;
            }
        } അല്ലെങ്കിൽ {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; bootstrap[i]; ++i) {
                എങ്കിൽ (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    നിർത്തുക;
                }
            }
        }
    }

    എങ്കിൽ (!result) {
        സ്ഥിരം അക്ഷരം *error = SDL_GetError();

        എങ്കിൽ (!*error) {
            SDL_SetError("No message system available");
        }
    } അല്ലെങ്കിൽ {
        SDL_ClearError();
    }

    (ശൂന്യം)SDL_AtomicDecRef(&SDL_messagebox_എണ്ണം);

    എങ്കിൽ (current_window) {
        SDL_RaiseWindow(current_window);
    }

    എങ്കിൽ (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    തിരികെ result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, സ്ഥിരം അക്ഷരം *title, സ്ഥിരം അക്ഷരം *message, SDL_Window *window)
{
#എങ്കിൽ defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_വലത്;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_വലത് = gsp_Has_Gpu_വലത്();
    എങ്കിൽ (!has_Gpu_വലത്)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    എങ്കിൽ (!has_Gpu_വലത്)
        gfxExit();

    തിരികെ true;
#അല്ലെങ്കിൽ
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

    തിരികെ SDL_ShowMessageBox(&data, ശൂന്യ);
#endif
}

bool SDL_ShouldAllowTopmost(ശൂന്യം)
{
    തിരികെ SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    എങ്കിൽ (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        തിരികെ true;
    }

    തിരികെ SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, ശൂന്യം *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!_this->SetWindowHitTest) {
        തിരികെ SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    തിരികെ _this->SetWindowHitTest(window, callback != ശൂന്യ);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        തിരികെ SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    എങ്കിൽ (!props) {
        തിരികെ false;
    }

    എങ്കിൽ (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        എങ്കിൽ (!surface) {
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        surface = ശൂന്യ;
    }

    എങ്കിൽ (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        തിരികെ false;
    }

    എങ്കിൽ (_this->UpdateWindowShape) {
        എങ്കിൽ (!_this->UpdateWindowShape(_this, window, surface)) {
            തിരികെ false;
        }
    }
    തിരികെ true;
}

/*
 * Functions used by iOS application delegates
 */
ശൂന്യം SDL_OnApplicationWillTerminate(ശൂന്യം)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

ശൂന്യം SDL_OnApplicationDidReceiveMemoryWarning(ശൂന്യം)
{
    SDL_SendAppEvent(SDL_EVENT_താഴെയുള്ള_MEMORY);
}

ശൂന്യം SDL_OnApplicationWillEnterBackground(ശൂന്യം)
{
    എങ്കിൽ (_this) {
        SDL_Window *window;
        വേണ്ടി (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(ശൂന്യ);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

ശൂന്യം SDL_OnApplicationDidEnterBackground(ശൂന്യം)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

ശൂന്യം SDL_OnApplicationWillEnterForeground(ശൂന്യം)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

ശൂന്യം SDL_OnApplicationDidEnterForeground(ശൂന്യം)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    എങ്കിൽ (_this) {
        SDL_Window *window;
        വേണ്ടി (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(സ്ഥിരം അക്ഷരം *path)
{
    bool result;

    എങ്കിൽ (!_this) {
        തിരികെ SDL_UninitializedVideo();
    }
    എങ്കിൽ (_this->vulkan_config.loader_loaded) {
        എങ്കിൽ (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            തിരികെ SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!_this->Vulkan_LoadLibrary) {
            തിരികെ SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    എങ്കിൽ (result) {
        _this->vulkan_config.loader_loaded++;
    }
    തിരികെ result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ ശൂന്യ;
    }
    എങ്കിൽ (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        തിരികെ ശൂന്യ;
    }
    തിരികെ (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

ശൂന്യം SDL_Vulkan_UnloadLibrary(ശൂന്യം)
{
    എങ്കിൽ (!_this) {
        SDL_UninitializedVideo();
        തിരികെ;
    }
    എങ്കിൽ (_this->vulkan_config.loader_loaded > 0) {
        എങ്കിൽ (--_this->vulkan_config.loader_loaded > 0) {
            തിരികെ;
        }
        എങ്കിൽ (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

അക്ഷരം സ്ഥിരം * സ്ഥിരം *SDL_Vulkan_GetInstanceExtensions(Uint32 *എണ്ണം)
{
    Uint32 tmpcount = 0;
    എങ്കിൽ (!എണ്ണം) {
        എണ്ണം = &tmpcount;
    }

    എങ്കിൽ (!_this->Vulkan_GetInstanceExtensions) {
        *എണ്ണം = 0;
        SDL_Unsupported();
        തിരികെ ശൂന്യ;
    }

    തിരികെ _this->Vulkan_GetInstanceExtensions(_this, എണ്ണം);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  സ്ഥിരം ഘടന VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    എങ്കിൽ (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        തിരികെ false;
    }

    CHECK_PARAM(!instance) {
        തിരികെ SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        തിരികെ SDL_InvalidParamError("surface");
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        എങ്കിൽ (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        എങ്കിൽ (SDL_Vulkan_LoadLibrary(ശൂന്യ)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } അല്ലെങ്കിൽ {
            തിരികെ SDL_SetError("failed to load Vulkan library");
        }
    }

    തിരികെ _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

ശൂന്യം SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               സ്ഥിരം ഘടന VkAllocationCallbacks *allocator)
{
    എങ്കിൽ (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        തിരികെ false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        തിരികെ false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        തിരികെ false;
    }

    എങ്കിൽ (_this->Vulkan_GetPresentationSupport) {
        തിരികെ _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    തിരികെ true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ശൂന്യ);

    എങ്കിൽ (!_this->Metal_CreateView) {
        SDL_Unsupported();
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        എങ്കിൽ (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        എങ്കിൽ (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    തിരികെ _this->Metal_CreateView(_this, window);
}

ശൂന്യം SDL_Metal_DestroyView(SDL_MetalView view)
{
    എങ്കിൽ (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

ശൂന്യം *SDL_Metal_GetLayer(SDL_MetalView view)
{
    എങ്കിൽ (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            തിരികെ ശൂന്യ;
        }
        തിരികെ _this->Metal_GetLayer(_this, view);
    } അല്ലെങ്കിൽ {
        SDL_SetError("Metal is not supported.");
        തിരികെ ശൂന്യ;
    }
}

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
സ്ഥിരം അക്ഷരം *SDL_GetCSSCursorName(SDL_SystemCursor id, സ്ഥിരം അക്ഷരം **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    തിരഞ്ഞെടുപ്പ് (id) {
    അവസ്ഥ SDL_SYSTEM_CURSOR_DEFAULT:
        തിരികെ "default";

    അവസ്ഥ SDL_SYSTEM_CURSOR_TEXT:
        തിരികെ "text";

    അവസ്ഥ SDL_SYSTEM_CURSOR_WAIT:
        തിരികെ "wait";

    അവസ്ഥ SDL_SYSTEM_CURSOR_CROSSHAIR:
        തിരികെ "crosshair";

    അവസ്ഥ SDL_SYSTEM_CURSOR_PROGRESS:
        തിരികെ "progress";

    അവസ്ഥ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        എങ്കിൽ (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        തിരികെ "nwse-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        എങ്കിൽ (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        തിരികെ "nesw-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_EW_RESIZE:
        എങ്കിൽ (fallback_name) {
            *fallback_name = "col-resize";
        }
        തിരികെ "ew-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_NS_RESIZE:
        എങ്കിൽ (fallback_name) {
            *fallback_name = "row-resize";
        }
        തിരികെ "ns-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_MOVE:
        എങ്കിൽ (fallback_name) {
            *fallback_name = "all-scroll";
        }
        തിരികെ "move";

    അവസ്ഥ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        തിരികെ "not-allowed";

    അവസ്ഥ SDL_SYSTEM_CURSOR_POINTER:
        തിരികെ "pointer";

    അവസ്ഥ SDL_SYSTEM_CURSOR_NW_RESIZE:
        തിരികെ "nw-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_N_RESIZE:
        തിരികെ "n-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_NE_RESIZE:
        തിരികെ "ne-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_E_RESIZE:
        തിരികെ "e-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_SE_RESIZE:
        തിരികെ "se-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_S_RESIZE:
        തിരികെ "s-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_SW_RESIZE:
        തിരികെ "sw-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_W_RESIZE:
        തിരികെ "w-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        തിരികെ "context-menu";

    അവസ്ഥ SDL_SYSTEM_CURSOR_HELP:
        തിരികെ "help";

    അവസ്ഥ SDL_SYSTEM_CURSOR_CELL:
        തിരികെ "cell";

    അവസ്ഥ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        തിരികെ "vertical-text";

    അവസ്ഥ SDL_SYSTEM_CURSOR_ALIAS:
        തിരികെ "alias";

    അവസ്ഥ SDL_SYSTEM_CURSOR_COPY:
        തിരികെ "copy";

    അവസ്ഥ SDL_SYSTEM_CURSOR_NO_DROP:
        തിരികെ "no-drop";

    അവസ്ഥ SDL_SYSTEM_CURSOR_GRAB:
        തിരികെ "grab";

    അവസ്ഥ SDL_SYSTEM_CURSOR_GRABBING:
        തിരികെ "grabbing";

    അവസ്ഥ SDL_SYSTEM_CURSOR_COL_RESIZE:
        തിരികെ "col-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        തിരികെ "row-resize";

    അവസ്ഥ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        എങ്കിൽ (fallback_name) {
            *fallback_name = "move";
        }
        തിരികെ "all-scroll";

    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_IN:
        തിരികെ "zoom-in";

    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        തിരികെ "zoom-out";

    സ്ഥിരസ്ഥിതി:
        തിരികെ "default";
    }
}
#endif

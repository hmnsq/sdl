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

#অন্তর্ভাব "SDL_internal.h"

// The high-level video driver subsystem

#অন্তর্ভাব "SDL_sysvideo.h"
#অন্তর্ভাব "SDL_clipboard_c.h"
#অন্তর্ভাব "SDL_egl_c.h"
#অন্তর্ভাব "SDL_surface_c.h"
#অন্তর্ভাব "SDL_pixels_c.h"
#অন্তর্ভাব "SDL_rect_c.h"
#অন্তর্ভাব "SDL_video_c.h"
#অন্তর্ভাব "../events/SDL_events_c.h"
#অন্তর্ভাব "../SDL_hints_c.h"
#অন্তর্ভাব "../SDL_properties_c.h"
#অন্তর্ভাব "../timer/SDL_timer_c.h"
#অন্তর্ভাব "../camera/SDL_camera_c.h"
#অন্তর্ভাব "../render/SDL_sysrender.h"
#অন্তর্ভাব "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#অন্তর্ভাব <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#যদি defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#অন্তর্ভাব <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#যদি defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#অন্তর্ভাব <SDL3/SDL_opengles2.h>
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
#অন্তর্ভাব <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#অন্তর্ভাব <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
স্থির VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_প্রবেশ_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    রিক্ত
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        প্রত্যাগম result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        প্রত্যাগম result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        প্রত্যাগম result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        প্রত্যাগম result;                                                  \
    }

#যদি defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
বাহ্য bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
বাহ্য bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
বাহ্য bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
বাহ্য bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
বাহ্য শূন্য SDL_UpdateLifecycleObserver(শূন্য);
#endif

স্থির শূন্য SDL_CheckWindowDisplayChanged(SDL_Window *window);
স্থির শূন্য SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
স্থির শূন্য SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
স্থির bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    যদি (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        প্রত্যাগম true;
    }
    প্রত্যাগম false;
}

স্থির bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    প্রত্যাগম !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

স্থির bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    প্রত্যাগম !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

স্থির bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    প্রত্যাগম !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

স্থির bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    প্রত্যাগম !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

স্থির bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    প্রত্যাগম !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
স্থির bool syncHint;

স্থির শূন্য SDL_SyncHintWatcher(শূন্য *userdata, ধ্রুব বর্ণ *name, ধ্রুব বর্ণ *old_মান, ধ্রুব বর্ণ *new_মান)
{
    syncHint = SDL_GetStringBoolean(new_মান, false);
}

স্থির শূন্য SDL_SyncIfRequired(SDL_Window *window)
{
    যদি (syncHint) {
        SDL_SyncWindow(window);
    }
}

স্থির শূন্য SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    যদি (window->parent) {
        যদি (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        যদি (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } অন্যথা {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = রিক্ত;
    }

    যদি (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        যদি (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

প্রকারনির্দেশ সংরচনা
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    শূন্য *pixels;
    পূর্ণাঙ্ক pitch;
    পূর্ণাঙ্ক bytes_per_pixel;
} SDL_WindowTextureData;

স্থির Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#যদি (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    যদি (_this->GL_CreateContext) {
        প্রত্যাগম SDL_WINDOW_OPENGL;
    }
#endif
#যদি defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    যদি (_this->Metal_CreateView) {
        প্রত্যাগম SDL_WINDOW_METAL;
    }
#endif
#যদি defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    যদি (SDL_strcmp(_this->name, "openvr") == 0) {
        প্রত্যাগম SDL_WINDOW_OPENGL;
    }
#endif
    প্রত্যাগম 0;
}

স্থির bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণাঙ্ক *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, রিক্ত);
    ধ্রুব bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক w, h;
    ধ্রুব SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    যদি (!data) {
        SDL_Renderer *renderer = রিক্ত;
        ধ্রুব বর্ণ *render_driver = রিক্ত;

        // See if there's a render driver being requested
        ধ্রুব বর্ণ *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        যদি (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        যদি (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        যদি (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = রিক্ত;
        }

        বর্ণ *render_driver_copy = রিক্ত;
        যদি (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            যদি (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                বর্ণ *prev = render_driver_copy;
                বর্ণ *ptr = prev;
                যাবত্ ((ptr = SDL_strchr(ptr, ',')) != রিক্ত) {
                    *ptr = '\0';
                    ধ্রুব bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    যদি (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } অন্যথা {
                        ptr++;
                        prev = ptr;
                    }
                }

                যদি (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        যদি (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            যদি (!renderer) {
                // The error for this specific renderer has already been set
                প্রত্যাগম false;
            }
        } অন্যথা {
            SDL_assert(render_driver_copy == রিক্ত);
            ধ্রুব পূর্ণাঙ্ক total = SDL_Get_অঙ্ক_Render_Drivers();
            প্রতি (i = 0; i < total; ++i) {
                ধ্রুব বর্ণ *name = SDL_GetRenderDriver(i);
                যদি (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    যদি (renderer) {
                        ভঙ্গ; // this will work.
                    }
                }
            }
            যদি (!renderer) {
                প্রত্যাগম SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != রিক্ত); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, পরিমাণ(*data));
        যদি (!data) {
            SDL_DestroyRenderer(renderer);
            প্রত্যাগম false;
        }
        যদি (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            প্রত্যাগম false;
        }

        data->renderer = renderer;
    }

    texture_formats = (ধ্রুব SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, রিক্ত);
    যদি (!texture_formats) {
        প্রত্যাগম false;
    }

    // Free any old texture and pixel data
    যদি (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = রিক্ত;
    }
    SDL_free(data->pixels);
    data->pixels = রিক্ত;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    প্রতি (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        যদি (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            ভঙ্গ;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    যদি (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        প্রত্যাগম false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ধ্রুব size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        যদি (!data->pixels) {
            প্রত্যাগম false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, রিক্ত);

    প্রত্যাগম true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, রিক্ত);
    যদি (!data) {
        প্রত্যাগম false;
    }
    যদি (!data->renderer) {
        প্রত্যাগম false;
    }
    প্রত্যাগম SDL_SetRenderVSync(data->renderer, vsync);
}

স্থির bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, রিক্ত);
    যদি (!data) {
        প্রত্যাগম false;
    }
    যদি (!data->renderer) {
        প্রত্যাগম false;
    }
    প্রত্যাগম SDL_GetRenderVSync(data->renderer, vsync);
}

স্থির bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুব SDL_Rect *rects, পূর্ণাঙ্ক numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    শূন্য *src;
    পূর্ণাঙ্ক w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, রিক্ত);
    যদি (!data || !data->texture) {
        প্রত্যাগম SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    যদি (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (শূন্য *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        যদি (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            প্রত্যাগম false;
        }

        যদি (!SDL_RenderTexture(data->renderer, data->texture, রিক্ত, রিক্ত)) {
            প্রত্যাগম false;
        }

        SDL_RenderPresent(data->renderer);
    }
    প্রত্যাগম true;
}

স্থির শূন্য SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    যদি (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, রিক্ত);

        যদি (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        যদি (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

স্থির SDL_VideoDevice *_this = রিক্ত;
স্থির SDL_AtomicInt SDL_messagebox_গুনতি;

স্থির পূর্ণাঙ্ক SDLCALL cmpmodes(ধ্রুব শূন্য *A, ধ্রুব শূন্য *B)
{
    ধ্রুব SDL_DisplayMode *a = (ধ্রুব SDL_DisplayMode *)A;
    ধ্রুব SDL_DisplayMode *b = (ধ্রুব SDL_DisplayMode *)B;
    পূর্ণাঙ্ক a_refresh_rate = (পূর্ণাঙ্ক)(a->refresh_rate * 100);
    পূর্ণাঙ্ক b_refresh_rate = (পূর্ণাঙ্ক)(b->refresh_rate * 100);
    পূর্ণাঙ্ক a_pixel_density = (পূর্ণাঙ্ক)(a->pixel_density * 100);
    পূর্ণাঙ্ক b_pixel_density = (পূর্ণাঙ্ক)(b->pixel_density * 100);

    যদি (a->w != b->w) {
        প্রত্যাগম b->w - a->w;
    } অন্যথা যদি (a->h != b->h) {
        প্রত্যাগম b->h - a->h;
    } অন্যথা যদি (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        প্রত্যাগম SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } অন্যথা যদি (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        প্রত্যাগম SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } অন্যথা যদি (a_refresh_rate != b_refresh_rate) {
        প্রত্যাগম b_refresh_rate - a_refresh_rate;
    } অন্যথা যদি (a_pixel_density != b_pixel_density) {
        প্রত্যাগম a_pixel_density - b_pixel_density;
    }
    প্রত্যাগম 0;
}

bool SDL_UninitializedVideo(শূন্য)
{
    প্রত্যাগম SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
স্থির ধ্রুব VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

পূর্ণাঙ্ক SDL_Get_অঙ্ক_Video_Drivers(শূন্য)
{
    স্থির পূর্ণাঙ্ক অঙ্ক_drivers = -1;

    যদি (অঙ্ক_drivers >= 0) {
        প্রত্যাগম অঙ্ক_drivers;
    }

    অঙ্ক_drivers = 0;

    // Build a list of unique video drivers.
    প্রতি (পূর্ণাঙ্ক i = 0; bootstrap[i] != রিক্ত; ++i) {
        bool duplicate = false;
        প্রতি (পূর্ণাঙ্ক j = 0; j < i; ++j) {
            যদি (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                ভঙ্গ;
            }
        }

        যদি (!duplicate) {
            deduped_bootstrap[অঙ্ক_drivers++] = bootstrap[i];
        }
    }

    প্রত্যাগম অঙ্ক_drivers;
}

ধ্রুব বর্ণ *SDL_GetVideoDriver(পূর্ণাঙ্ক index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_অঙ্ক_Video_Drivers()) {
        SDL_InvalidParamError("index");
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ধ্রুব বর্ণ *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    পূর্ণাঙ্ক i = 0;

    // Check to make sure we don't overwrite '_this'
    যদি (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    যদি (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        গচ্ছ pre_driver_error;
    }
    init_events = true;
    যদি (!SDL_InitKeyboard()) {
        গচ্ছ pre_driver_error;
    }
    init_keyboard = true;
    যদি (!SDL_PreInitMouse()) {
        গচ্ছ pre_driver_error;
    }
    init_mouse = true;
    যদি (!SDL_InitTouch()) {
        গচ্ছ pre_driver_error;
    }
    init_touch = true;
    যদি (!SDL_InitPen()) {
        গচ্ছ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = রিক্ত;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    যদি (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    যদি (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    যদি (driver_name && *driver_name != 0) {
        ধ্রুব বর্ণ *driver_attempt = driver_name;
        যাবত্ (driver_attempt && *driver_attempt != 0 && !video) {
            ধ্রুব বর্ণ *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            প্রতি (i = 0; bootstrap[i]; ++i) {
                যদি (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    যদি (video) {
                        ভঙ্গ;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : রিক্ত;
        }
    } অন্যথা {
        প্রতি (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            যদি (video) {
                ভঙ্গ;
            }
        }
    }
    যদি (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } অন্যথা {
        যদি (driver_name) {
            SDL_SetError("%s not available", driver_name);
            গচ্ছ pre_driver_error;
        }
        SDL_SetError("No available video device");
        গচ্ছ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = রিক্ত;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    যদি (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        প্রত্যাগম false;
    }

    // Make sure some displays were added
    যদি (_this->অঙ্ক_displays == 0) {
        SDL_QuitVideo();
        প্রত্যাগম SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, রিক্ত);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    যদি (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    প্রত্যাগম true;

pre_driver_error:
    SDL_assert(_this == রিক্ত);
    যদি (init_pen) {
        SDL_QuitPen();
    }
    যদি (init_touch) {
        SDL_QuitTouch();
    }
    যদি (init_mouse) {
        SDL_QuitMouse();
    }
    যদি (init_keyboard) {
        SDL_QuitKeyboard();
    }
    যদি (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    প্রত্যাগম false;
}

ধ্রুব বর্ণ *SDL_GetCurrentVideoDriver(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(শূন্য)
{
    প্রত্যাগম _this;
}

bool SDL_OnVideoThread(শূন্য)
{
    প্রত্যাগম (_this && SDL_GetCurrentThreadID() == _this->thread);
}

শূন্য SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    যদি (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(শূন্য)
{
    যদি (_this) {
        প্রত্যাগম _this->system_theme;
    } অন্যথা {
        প্রত্যাগম SDL_SYSTEM_THEME_UNKNOWN;
    }
}

শূন্য SDL_UpdateDesktopBounds(শূন্য)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(রিক্ত);
    যদি (displays) {
        প্রতি (পূর্ণাঙ্ক i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            যদি (SDL_GetDisplayBounds(displays[i], &bounds)) {
                যদি (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } অন্যথা {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

স্থির শূন্য SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    যদি (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    যদি (mode->refresh_rate_numerator > 0) {
        যদি (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (ভিন্ন)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } অন্যথা {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ধ্রুব SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    যদি (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, পরিমাণ(display.desktop_mode));
    }
    প্রত্যাগম SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ধ্রুব SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    পূর্ণাঙ্ক i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(পরিমাণ(*new_display));
    যদি (!new_display) {
        প্রত্যাগম 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->অঙ্ক_displays + 1) * পরিমাণ(*displays));
    যদি (!displays) {
        SDL_free(new_display);
        প্রত্যাগম 0;
    }
    _this->displays = displays;
    _this->displays[_this->অঙ্ক_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    যদি (display->name) {
        new_display->name = SDL_strdup(display->name);
    } অন্যথা {
        বর্ণ name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    যদি (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    প্রতি (i = 0; i < new_display->অঙ্ক_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    যদি (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    প্রত্যাগম id;
}

শূন্য SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    প্রতি (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

শূন্য SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

শূন্য SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    পূর্ণাঙ্ক display_index = SDL_GetDisplayIndex(displayID);
    যদি (display_index < 0) {
        প্রত্যাগম;
    }

    display = _this->displays[display_index];

    যদি (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = রিক্ত;
    SDL_free(display->internal);
    display->internal = রিক্ত;
    SDL_free(display);

    যদি (display_index < (_this->অঙ্ক_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->অঙ্ক_displays - display_index - 1) * পরিমাণ(_this->displays[display_index]));
    }
    --_this->অঙ্ক_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(পূর্ণাঙ্ক *গুনতি)
{
    পূর্ণাঙ্ক i;
    SDL_DisplayID *displays;

    যদি (!_this) {
        যদি (গুনতি) {
            *গুনতি = 0;
        }

        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->অঙ্ক_displays + 1) * পরিমাণ(*displays));
    যদি (displays) {
        যদি (গুনতি) {
            *গুনতি = _this->অঙ্ক_displays;
        }

        প্রতি (i = 0; i < _this->অঙ্ক_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } অন্যথা {
        যদি (গুনতি) {
            *গুনতি = 0;
        }
    }
    প্রত্যাগম displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    পূর্ণাঙ্ক display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    যদি (display_index < 0) {
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম _this->displays[display_index];
}

স্থির SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    যদি (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    প্রত্যাগম displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    প্রত্যাগম SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(শূন্য)
{
    যদি (!_this || _this->অঙ্ক_displays == 0) {
        SDL_UninitializedVideo();
        প্রত্যাগম 0;
    }
    প্রত্যাগম _this->displays[0]->id;
}

পূর্ণাঙ্ক SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    পূর্ণাঙ্ক display_index;

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম -1;
    }

    প্রতি (display_index = 0; display_index < _this->অঙ্ক_displays; ++display_index) {
        যদি (displayID == _this->displays[display_index]->id) {
            প্রত্যাগম display_index;
        }
    }
    SDL_SetError("Invalid display");
    প্রত্যাগম -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, রিক্ত);

    প্রত্যাগম display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    প্রত্যাগম SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    যদি (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    প্রত্যাগম display->props;
}

ধ্রুব বর্ণ *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, রিক্ত);

    প্রত্যাগম display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        প্রত্যাগম SDL_InvalidParamError("rect");
    }

    যদি (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        যদি (_this->GetDisplayBounds(_this, display, rect)) {
            প্রত্যাগম true;
        }
    }

    // Assume that the displays are left to right
    যদি (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } অন্যথা {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    প্রত্যাগম true;
}

স্থির পূর্ণাঙ্ক ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ধ্রুব বর্ণ *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    প্রত্যাগম hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        প্রত্যাগম SDL_InvalidParamError("rect");
    }

    যদি (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        প্রত্যাগম true;
    }

    যদি (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        যদি (_this->GetDisplayUsableBounds(_this, display, rect)) {
            প্রত্যাগম true;
        }
    }

    // Oh well, just give the entire display bounds.
    প্রত্যাগম SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    যদি (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        প্রত্যাগম display->natural_orientation;
    } অন্যথা {
        // Default to landscape if the driver hasn't set it
        প্রত্যাগম SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    যদি (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        প্রত্যাগম display->current_orientation;
    } অন্যথা {
        // Default to landscape if the driver hasn't set it
        প্রত্যাগম SDL_ORIENTATION_LANDSCAPE;
    }
}

শূন্য SDL_SetDisplayContentScale(SDL_VideoDisplay *display, ভিন্ন scale)
{
    যদি (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        প্রতি (window = _this->windows; window; window = window->next) {
            যদি (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

ভিন্ন SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    প্রত্যাগম display->content_scale;
}

শূন্য SDL_SetWindowHDRProperties(SDL_Window *window, ধ্রুব SDL_HDROutputProperties *HDR, bool send_event)
{
    ধ্রুব SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    যদি (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        যদি (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

শূন্য SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ধ্রুব SDL_HDROutputProperties *HDR)
{
    ধ্রুব SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ধ্রুব bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	যদি (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    যদি (changed && !SDL_DriverSendsHDRChanges(_this)) {
        প্রতি (SDL_Window *w = display->device->windows; w; w = w->next) {
            যদি (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

স্থির শূন্য SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    যদি (display->অঙ্ক_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
স্থির ধ্রুব SDL_DisplayMode *SDL_GetFullscreenModeMatch(ধ্রুব SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    যদি (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        প্রত্যাগম রিক্ত;
    }

    SDL_memcpy(&fullscreen_mode, mode, পরিমাণ(fullscreen_mode));
    যদি (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = রিক্ত;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    যদি (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        যদি (!mode) {
            প্রতি (পূর্ণাঙ্ক i = 0; i < display->অঙ্ক_fullscreen_modes; ++i) {
                যদি (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], পরিমাণ(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    ভঙ্গ;
                }
            }
        }

        // Search for a mode with the same characteristics
        যদি (!mode) {
            প্রতি (পূর্ণাঙ্ক i = 0; i < display->অঙ্ক_fullscreen_modes; ++i) {
                যদি (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    ভঙ্গ;
                }
            }
        }
    }
    প্রত্যাগম mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ধ্রুব SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    পূর্ণাঙ্ক i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, পরিমাণ(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->অঙ্ক_fullscreen_modes;
    প্রতি (i = 0; i < nmodes; ++i) {
        যদি (cmpmodes(&new_mode, &modes[i]) == 0) {
            প্রত্যাগম false;
        }
    }

    // Go ahead and add the new mode
    যদি (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * পরিমাণ(*modes));
        যদি (!modes) {
            প্রত্যাগম false;
        }

        যদি (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * পরিমাণ(*modes));
            প্রতি (i = 0; i < nmodes; ++i) {
                যদি (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->অঙ্ক_fullscreen_modes++], &new_mode, পরিমাণ(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->অঙ্ক_fullscreen_modes,
              পরিমাণ(SDL_DisplayMode), cmpmodes);

    প্রত্যাগম true;
}

শূন্য SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = display->অঙ্ক_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = রিক্ত;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = রিক্ত;
    display->অঙ্ক_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, পূর্ণাঙ্ক *গুনতি)
{
    পূর্ণাঙ্ক i;
    পূর্ণাঙ্ক অঙ্ক_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    যদি (গুনতি) {
        *গুনতি = 0;
    }

    CHECK_DISPLAY_MAGIC(display, রিক্ত);

    SDL_UpdateFullscreenDisplayModes(display);

    অঙ্ক_modes = display->অঙ্ক_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((অঙ্ক_modes + 1) * পরিমাণ(*result) + অঙ্ক_modes * পরিমাণ(**result));
    যদি (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((অঙ্ক_modes + 1) * পরিমাণ(*result)));
        যদি (অঙ্ক_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, অঙ্ক_modes * পরিমাণ(*modes));
        }
        প্রতি (i = 0; i < অঙ্ক_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = রিক্ত;

        যদি (গুনতি) {
            *গুনতি = অঙ্ক_modes;
        }
    } অন্যথা {
        যদি (গুনতি) {
            *গুনতি = 0;
        }
    }
    প্রত্যাগম result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, ভিন্ন refresh_rate, bool include_উপরের_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        প্রত্যাগম SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ধ্রুব SDL_DisplayMode *mode, *closest = রিক্ত;
    ভিন্ন aspect_ratio;
    পূর্ণাঙ্ক i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    যদি (h > 0) {
        aspect_ratio = (ভিন্ন)w / h;
    } অন্যথা {
        aspect_ratio = 1.0f;
    }

    যদি (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    প্রতি (i = 0; i < display->অঙ্ক_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        যদি (w > mode->w) {
            // Out of sorted modes large enough here
            ভঙ্গ;
        }
        যদি (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            অনুবর্ত;
        }
        যদি (mode->pixel_density > 1.0f && !include_উপরের_density_modes) {
            অনুবর্ত;
        }
        যদি (closest) {
            ভিন্ন current_aspect_ratio = (ভিন্ন)mode->w / mode->h;
            ভিন্ন closest_aspect_ratio = (ভিন্ন)closest->w / closest->h;
            যদি (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                অনুবর্ত;
            }

            যদি (mode->w == closest->w && mode->h == closest->h) {
                যদি (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    অনুবর্ত;
                }
                যদি (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    অনুবর্ত;
                }
            }
        }

        closest = mode;
    }
    যদি (!closest) {
        প্রত্যাগম SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    প্রত্যাগম true;
}

স্থির bool DisplayModeChanged(ধ্রুব SDL_DisplayMode *old_mode, ধ্রুব SDL_DisplayMode *new_mode)
{
    প্রত্যাগম ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

শূন্য SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ধ্রুব SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    যদি (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        প্রত্যাগম;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    যদি (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        যদি (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

ধ্রুব SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, রিক্ত);

    প্রত্যাগম &display->desktop_mode;
}

শূন্য SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ধ্রুব SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    যদি (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } অন্যথা {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    যদি (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

ধ্রুব SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, রিক্ত);

    প্রত্যাগম display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    যদি (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        প্রত্যাগম true;
    }

    যদি (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    যদি (mode == display->current_mode) {
        প্রত্যাগম true;
    }
#endif

    // Actually change the display mode
    যদি (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        যদি (!result) {
            প্রত্যাগম false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    প্রত্যাগম true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
স্থির শূন্য SDL_GetClosestPointOnRect(ধ্রুব SDL_Rect *rect, SDL_Point *point)
{
    ধ্রুব পূর্ণাঙ্ক ডান = rect->x + rect->w - 1;
    ধ্রুব পূর্ণাঙ্ক bottom = rect->y + rect->h - 1;

    যদি (point->x < rect->x) {
        point->x = rect->x;
    } অন্যথা যদি (point->x > ডান) {
        point->x = ডান;
    }

    যদি (point->y < rect->y) {
        point->y = rect->y;
    } অন্যথা যদি (point->y > bottom) {
        point->y = bottom;
    }
}

স্থির SDL_DisplayID GetDisplayForRect(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    পূর্ণাঙ্ক i, dist;
    SDL_DisplayID closest = 0;
    পূর্ণাঙ্ক closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    যদি (_this) {
        প্রতি (i = 0; i < _this->অঙ্ক_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            যদি (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, রিক্ত)) {
                প্রত্যাগম display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            যদি (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    যদি (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    প্রত্যাগম closest;
}

শূন্য SDL_RelativeToGlobalForWindow(SDL_Window *window, পূর্ণাঙ্ক rel_x, পূর্ণাঙ্ক rel_y, পূর্ণাঙ্ক *abs_x, পূর্ণাঙ্ক *abs_y)
{
    SDL_Window *w;

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        প্রতি (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            যদি (!SDL_WINDOW_IS_POPUP(w)) {
                ভঙ্গ;
            }
        }
    }

    যদি (abs_x) {
        *abs_x = rel_x;
    }
    যদি (abs_y) {
        *abs_y = rel_y;
    }
}

শূন্য SDL_GlobalToRelativeForWindow(SDL_Window *window, পূর্ণাঙ্ক abs_x, পূর্ণাঙ্ক abs_y, পূর্ণাঙ্ক *rel_x, পূর্ণাঙ্ক *rel_y)
{
    SDL_Window *w;

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        প্রতি (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            যদি (!SDL_WINDOW_IS_POPUP(w)) {
                ভঙ্গ;
            }
        }
    }

    যদি (rel_x) {
        *rel_x = abs_x;
    }
    যদি (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ধ্রুব SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        প্রত্যাগম 0;
    }

    প্রত্যাগম GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ধ্রুব SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        প্রত্যাগম 0;
    }

    প্রত্যাগম GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

স্থির SDL_DisplayID GetDisplayAtOrigin(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; ++i) {
        SDL_Rect rect;
        ধ্রুব SDL_DisplayID cur_id = _this->displays[i]->id;
        যদি (SDL_GetDisplayBounds(cur_id, &rect)) {
            যদি (x == rect.x && y == rect.y) {
                প্রত্যাগম cur_id;
            }
        }
    }

    প্রত্যাগম 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    পূর্ণাঙ্ক x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    যদি (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    যদি (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } অন্যথা {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    যদি (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    প্রত্যাগম displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, রিক্ত);

    // An explicit fullscreen display overrides all
    যদি (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    যদি (!displayID) {
        displayID = window->pending_displayID;
    }
    যদি (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ধ্রুব পূর্ণাঙ্ক x = window->last_position_pending ? window->pending.x : window->x;
        ধ্রুব পূর্ণাঙ্ক y = window->last_position_pending ? window->pending.y : window->y;
        ধ্রুব পূর্ণাঙ্ক w = window->last_size_pending ? window->pending.w : window->w;
        ধ্রুব পূর্ণাঙ্ক h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        যদি (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    যদি (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    প্রত্যাগম SDL_GetVideoDisplay(displayID);
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
    যদি (fs_display) {
        SDL_Set_সংখ্যা_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } অন্যথা {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    প্রত্যাগম GetDisplayForWindow(window);
}

স্থির শূন্য SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    যদি (SDL_SendsDisplayChanges(_this)) {
        প্রত্যাগম;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    যদি (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        যদি (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            যদি (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                পূর্ণাঙ্ক old_area = old_overlap.w * old_overlap.h;
                পূর্ণাঙ্ক new_area = new_overlap.w * new_overlap.h;
                ভিন্ন new_overlap_ratio = (new_area / ((ভিন্ন)old_area + new_area));
                যদি (new_overlap_ratio < 0.80) {
                    প্রত্যাগম;
                }
            }
        }
    }

    যদি (displayID != window->displayID) {
        পূর্ণাঙ্ক i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        প্রতি (i = 0; i < _this->অঙ্ক_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            যদি (display->fullscreen_window == window) {
                যদি (display_index != i) {
                    যদি (display_index < 0) {
                        display_index = i;
                    } অন্যথা {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        যদি (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = রিক্ত;
                    }
                }
                ভঙ্গ;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (পূর্ণাঙ্ক)displayID, 0);
    }
}

ভিন্ন SDL_GetWindowPixelDensity(SDL_Window *window)
{
    পূর্ণাঙ্ক window_w, window_h, pixel_w, pixel_h;
    ভিন্ন pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    যদি (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (ভিন্ন)pixel_w / window_w;
    }
    প্রত্যাগম pixel_density;
}

ভিন্ন SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    প্রত্যাগম window->display_scale;
}

স্থির শূন্য SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    ভিন্ন display_scale;

    যদি (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } অন্যথা {
        ধ্রুব ভিন্ন pixel_density = SDL_GetWindowPixelDensity(window);
        ধ্রুব ভিন্ন content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    যদি (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = রিক্ত;
    SDL_DisplayMode *mode = রিক্ত;
    পূর্ণাঙ্ক i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    যদি (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    যদি (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        যদি (!display) {
            // This should never happen, but it did...
            গচ্ছ done;
        }
    } অন্যথা {
        প্রতি (i = 0; i < _this->অঙ্ক_displays; ++i) {
            display = _this->displays[i];
            যদি (display->fullscreen_window == window) {
                ভঙ্গ;
            }
        }
        যদি (!display || i == _this->অঙ্ক_displays) {
            // Already not fullscreen on any display
            display = রিক্ত;
        }
    }

    যদি (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        যদি (mode) {
            window->fullscreen_exclusive = true;
        } অন্যথা {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#যদি defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    যদি (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        যদি (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            যদি (display) {
                display->fullscreen_window = রিক্ত;
            }
            গচ্ছ done;
        }
        যদি (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            যদি (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                যদি (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    গচ্ছ error;
                }
            } অন্যথা যদি (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                প্রতি (i = 0; i < _this->অঙ্ক_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    যদি (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, রিক্ত);
                        যদি (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = রিক্ত;
                    }
                }
            }

            যদি (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                গচ্ছ done;
            }
        }
    }
#endif

    যদি (display) {
        // Restore the video mode on other displays if needed
        প্রতি (i = 0; i < _this->অঙ্ক_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            যদি (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, রিক্ত);
                other->fullscreen_window = রিক্ত;
            }
        }
    }

    যদি (fullscreen) {
        পূর্ণাঙ্ক mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        যদি (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        যদি (!SDL_SetDisplayModeForDisplay(display, mode)) {
            গচ্ছ error;
        }
        যদি (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            যদি (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } অন্যথা {
                resized = true;
            }

            যদি (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } অন্যথা যদি (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                গচ্ছ error;
            }
        }

        যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            যদি (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                যদি (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } অন্যথা {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                যদি (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                যদি (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } অন্যথা {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } অন্যথা {
        bool resized = false;

        // Restore the desktop mode
        যদি (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, রিক্ত);
        }
        যদি (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            যদি (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                যদি (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } অন্যথা {
                resized = true;
            }

            যদি (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } অন্যথা যদি (ret == SDL_FULLSCREEN_FAILED) {
                গচ্ছ error;
            }
        }

        যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            যদি (display) {
                display->fullscreen_window = রিক্ত;
            }

            যদি (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                যদি (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } অন্যথা {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    প্রত্যাগম true;

error:
    যদি (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    প্রত্যাগম false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ধ্রুব SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (mode) {
        যদি (!SDL_GetFullscreenModeMatch(mode)) {
            প্রত্যাগম SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } অন্যথা {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#যদি defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    যদি (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    যদি (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    প্রত্যাগম true;
}

ধ্রুব SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, রিক্ত);
    CHECK_WINDOW_NOT_POPUP(window, রিক্ত);

    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        প্রত্যাগম SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } অন্যথা {
        প্রত্যাগম SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

শূন্য *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    যদি (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ধ্রুব SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    যদি (mode) {
        প্রত্যাগম mode->format;
    } অন্যথা {
        প্রত্যাগম SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_উপরের_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_শীর্ষ | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

স্থির SDL_INLINE bool IsAcceptingDragAndDrop(শূন্য)
{
    যদি (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        প্রত্যাগম true;
    }
    প্রত্যাগম false;
}

// prepare a newly-created window
স্থির SDL_INLINE শূন্য PrepareDragAndDropSupport(SDL_Window *window)
{
    যদি (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
শূন্য SDL_ToggleDragAndDropSupport(শূন্য)
{
    যদি (_this && _this->AcceptDragAndDrop) {
        ধ্রুব bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        প্রতি (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(পূর্ণাঙ্ক *গুনতি)
{
    যদি (গুনতি) {
        *গুনতি = 0;
    }

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }

    SDL_Window *window;
    পূর্ণাঙ্ক অঙ্ক_added = 0;
    পূর্ণাঙ্ক অঙ্ক_windows = 0;
    প্রতি (window = _this->windows; window; window = window->next) {
        ++অঙ্ক_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((অঙ্ক_windows + 1) * পরিমাণ(*windows));
    যদি (!windows) {
        প্রত্যাগম রিক্ত;
    }

    প্রতি (window = _this->windows; window; window = window->next) {
        windows[অঙ্ক_added++] = window;
        যদি (অঙ্ক_added == অঙ্ক_windows) {
            // Race condition? Multi-threading not supported, ignore it
            ভঙ্গ;
        }
    }
    windows[অঙ্ক_added] = রিক্ত;

    যদি (গুনতি) {
        *গুনতি = অঙ্ক_added;
    }
    প্রত্যাগম windows;
}

স্থির শূন্য ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    যদি (!SDL_WINDOW_IS_POPUP(window)) {
        যদি (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        যদি (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        যদি (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        যদি (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        যদি (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        যদি (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

স্থির শূন্য SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    যদি (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } অন্যথা {
        ApplyWindowFlags(window, flags);
        যদি (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#যদি defined(SDL_PLATFORM_LINUX)
    যদি (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_মান(window, 0.0f);
    }
#endif
}

স্থির bool SDL_ContextNotSupported(ধ্রুব বর্ণ *name)
{
    প্রত্যাগম SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

স্থির bool SDL_DllNotSupported(ধ্রুব বর্ণ *name)
{
    প্রত্যাগম SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

স্থির সংরচনা {
    ধ্রুব বর্ণ *property_name;
    SDL_WindowFlags flag;
    bool invert_মান;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_শীর্ষ_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_শীর্ষ,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_উপরের_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_উপরের_PIXEL_DENSITY,  false },
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

স্থির SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_সংখ্যা, 0);

    প্রতি (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        যদি (SDL_WindowFlagProperties[i].invert_মান) {
            যদি (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } অন্যথা {
            যদি (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    প্রত্যাগম flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ধ্রুব বর্ণ *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, রিক্ত);
    পূর্ণাঙ্ক x = (পূর্ণাঙ্ক)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_X_সংখ্যা, SDL_WINDOWPOS_UNDEFINED);
    পূর্ণাঙ্ক y = (পূর্ণাঙ্ক)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_Y_সংখ্যা, SDL_WINDOWPOS_UNDEFINED);
    পূর্ণাঙ্ক w = (পূর্ণাঙ্ক)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_সংখ্যা, 0);
    পূর্ণাঙ্ক h = (পূর্ণাঙ্ক)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_সংখ্যা, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, রিক্ত);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    যদি (!_this) {
        // Initialize the video system if needed
        যদি (!SDL_Init(SDL_INIT_VIDEO)) {
            প্রত্যাগম রিক্ত;
        }

        // Make clang-tidy happy
        যদি (!_this) {
            প্রত্যাগম রিক্ত;
        }
    }

    যদি ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        প্রত্যাগম রিক্ত;
    }

    যদি ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        যদি (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            প্রত্যাগম রিক্ত;
        }

        // Tooltip and popup menu window must specify a parent window
        যদি (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            প্রত্যাগম রিক্ত;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    যদি (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned পূর্ণাঙ্ক)type_flags);
        প্রত্যাগম রিক্ত;
    }

    // Make sure the display list is up to date for window placement
    যদি (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    যদি (w < 1) {
        w = 1;
    }
    যদি (h < 1) {
        h = 1;
    }

    যদি (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        যদি ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } অন্যথা যদি ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        যদি (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        যদি (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        যদি (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            যদি (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        যদি (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            যদি (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    যদি (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned পূর্ণাঙ্ক)graphics_flags);
        প্রত্যাগম রিক্ত;
    }

    // Some platforms have certain graphics backends enabled by default
    যদি (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    যদি (flags & SDL_WINDOW_OPENGL) {
        যদি (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            প্রত্যাগম রিক্ত;
        }
        যদি (!SDL_GL_LoadLibrary(রিক্ত)) {
            প্রত্যাগম রিক্ত;
        }
    }

    যদি (flags & SDL_WINDOW_VULKAN) {
        যদি (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            প্রত্যাগম রিক্ত;
        }
        যদি (!SDL_Vulkan_LoadLibrary(রিক্ত)) {
            প্রত্যাগম রিক্ত;
        }
    }

    যদি (flags & SDL_WINDOW_METAL) {
        যদি (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            প্রত্যাগম রিক্ত;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, পরিমাণ(*window));
    যদি (!window) {
        প্রত্যাগম রিক্ত;
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
    যদি (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    যদি (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    যদি (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    যদি (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    যদি (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_ঠেলো_Error();
        SDL_DestroyWindow(window);
        SDL_বের_করো_Error();
        প্রত্যাগম রিক্ত;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#যদি !defined(SDL_PLATFORM_WINDOWS)
    যদি (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    যদি (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    প্রত্যাগম window;
}

SDL_Window *SDL_CreateWindow(ধ্রুব বর্ণ *title, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    যদি (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_সংখ্যা, w);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_সংখ্যা, h);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_সংখ্যা, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    প্রত্যাগম window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, পূর্ণাঙ্ক offset_x, পূর্ণাঙ্ক offset_y, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    যদি (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        প্রত্যাগম রিক্ত;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_X_সংখ্যা, offset_x);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_Y_সংখ্যা, offset_y);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_সংখ্যা, w);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_সংখ্যা, h);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_সংখ্যা, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    প্রত্যাগম window;
}

স্থির bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    যদি (!_this->ReconfigureWindow) {
        প্রত্যাগম false;
    }

    ধ্রুব SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    যদি (graphics_flags & (graphics_flags - 1)) {
        প্রত্যাগম SDL_SetError("Conflicting window flags specified");
    }

    যদি ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        প্রত্যাগম SDL_ContextNotSupported("OpenGL");
    }
    যদি ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        প্রত্যাগম SDL_ContextNotSupported("Vulkan");
    }
    যদি ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        প্রত্যাগম SDL_ContextNotSupported("Metal");
    }

    যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        যদি (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            প্রত্যাগম false;
        }
    } অন্যথা {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        যদি (!_this->ReconfigureWindow(_this, window, 0)) {
            প্রত্যাগম false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        যদি (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        যদি (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    যদি (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(রিক্ত);
        যদি (!loaded_opengl) {
            প্রত্যাগম false;
        }
    } অন্যথা যদি (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(রিক্ত);
        যদি (!loaded_vulkan) {
            প্রত্যাগম false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    যদি (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        যদি (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        যদি (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        প্রত্যাগম false;
    }

    window->flags |= graphics_flags;

    প্রত্যাগম true;
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
    যদি (graphics_flags & (graphics_flags - 1)) {
        প্রত্যাগম SDL_SetError("Conflicting window flags specified");
    }

    যদি ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        প্রত্যাগম SDL_ContextNotSupported("OpenGL");
    }
    যদি ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        প্রত্যাগম SDL_ContextNotSupported("Vulkan");
    }
    যদি ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        প্রত্যাগম SDL_ContextNotSupported("Metal");
    }

    যদি (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } অন্যথা {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    যদি (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        ধ্রুব bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    যদি ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        যদি (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } অন্যথা {
            need_gl_unload = true;
        }
    } অন্যথা যদি (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    যদি ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        যদি (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } অন্যথা {
            need_vulkan_unload = true;
        }
    } অন্যথা যদি (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    যদি (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    যদি (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    যদি (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    যদি (need_gl_load) {
        যদি (!SDL_GL_LoadLibrary(রিক্ত)) {
            প্রত্যাগম false;
        }
        loaded_opengl = true;
    }

    যদি (need_vulkan_load) {
        যদি (!SDL_Vulkan_LoadLibrary(রিক্ত)) {
            প্রত্যাগম false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    যদি (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        যদি (!_this->CreateSDLWindow(_this, window, 0)) {
            যদি (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            যদি (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            প্রত্যাগম false;
        }
    }

    যদি (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    যদি (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    যদি (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    যদি (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    যদি (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    যদি (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    যদি (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    প্রত্যাগম true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    যদি (!SDL_ReconfigureWindowInternal(window, flags)) {
        প্রত্যাগম SDL_RecreateWindow(window, flags);
    }

    প্রত্যাগম true;
}

bool SDL_HasWindows(শূন্য)
{
    প্রত্যাগম _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    প্রত্যাগম window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    যদি (id) {
        প্রতি (window = _this->windows; window; window = window->next) {
            যদি (window->id == id) {
                প্রত্যাগম window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    প্রত্যাগম রিক্ত;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, রিক্ত);

    প্রত্যাগম window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    যদি (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    প্রত্যাগম window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    প্রত্যাগম window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ধ্রুব বর্ণ *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (title == window->title) {
        প্রত্যাগম true;
    }
    যদি (!title) {
        title = "";
    }
    যদি (window->title && SDL_strcmp(title, window->title) == 0) {
        প্রত্যাগম true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    যদি (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    প্রত্যাগম true;
}

ধ্রুব বর্ণ *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    প্রত্যাগম window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        প্রত্যাগম SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    যদি (!window->icon) {
        প্রত্যাগম false;
    }

    যদি (!_this->SetWindowIcon) {
        প্রত্যাগম SDL_Unsupported();
    }

    প্রত্যাগম _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ধ্রুব পূর্ণাঙ্ক w = window->last_size_pending ? window->pending.w : window->windowed.w;
    ধ্রুব পূর্ণাঙ্ক h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    যদি (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    যদি (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    যদি (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        যদি (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } অন্যথা যদি (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        যদি (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        যদি (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            যদি (!SDL_GetDisplayBounds(displayID, &bounds)) {
                প্রত্যাগম false;
            }
        }
        যদি (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        যদি (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } অন্যথা {
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
    যদি (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    যদি (_this->SetWindowPosition) {
        ধ্রুব bool result = _this->SetWindowPosition(_this, window);
        যদি (result) {
            SDL_SyncIfRequired(window);
        }
        প্রত্যাগম result;
    }

    প্রত্যাগম SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, পূর্ণাঙ্ক *x, পূর্ণাঙ্ক *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#অন্যথা
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    যদি (use_display_origin) {
        SDL_DisplayID displayID;

        যদি (x) {
            *x = 0;
        }
        যদি (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        যদি (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            যদি (x) {
                *x = bounds.x;
            }
            যদি (y) {
                *y = bounds.y;
            }
        }
    } অন্যথা {
        ধ্রুব bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        যদি (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        যদি (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    প্রত্যাগম true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->SetWindowBordered) {
        প্রত্যাগম SDL_Unsupported();
    }

    ধ্রুব bool want = bordered;
    ধ্রুব bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    যদি (want != have) {
        যদি (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } অন্যথা {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    প্রত্যাগম true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->SetWindowResizable) {
        প্রত্যাগম SDL_Unsupported();
    }

    ধ্রুব bool want = resizable;
    ধ্রুব bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    যদি (want != have) {
        যদি (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } অন্যথা {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    প্রত্যাগম true;
}

bool SDL_Set_Window_Always_On_শীর্ষ(SDL_Window *window, bool on_শীর্ষ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->Set_Window_Always_On_শীর্ষ) {
        প্রত্যাগম SDL_Unsupported();
    }

    ধ্রুব bool want = on_শীর্ষ;
    ধ্রুব bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_শীর্ষ) != 0);
    যদি (want != have) {
        যদি (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_শীর্ষ;
        } অন্যথা {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_শীর্ষ;
        }
        _this->Set_Window_Always_On_শীর্ষ(_this, window, want);
    }

    প্রত্যাগম true;
}

bool SDL_SetWindowSize(SDL_Window *window, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        প্রত্যাগম SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        প্রত্যাগম SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    ভিন্ন new_aspect = w / (ভিন্ন)h;
    যদি (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (পূর্ণাঙ্ক)SDL_roundf(h * window->max_aspect);
    } অন্যথা যদি (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (পূর্ণাঙ্ক)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    যদি (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    যদি (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    যদি (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    যদি (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    যদি (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } অন্যথা {
        প্রত্যাগম SDL_Unsupported();
    }
    প্রত্যাগম true;
}

bool SDL_GetWindowSize(SDL_Window *window, পূর্ণাঙ্ক *w, পূর্ণাঙ্ক *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    যদি (w) {
        *w = window->w;
    }
    যদি (h) {
        *h = window->h;
    }
    প্রত্যাগম true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, ভিন্ন min_aspect, ভিন্ন max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    যদি (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    পূর্ণাঙ্ক w = window->last_size_pending ? window->pending.w : window->floating.w;
    পূর্ণাঙ্ক h = window->last_size_pending ? window->pending.h : window->floating.h;
    প্রত্যাগম SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, ভিন্ন *min_aspect, ভিন্ন *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    যদি (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    প্রত্যাগম true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, পূর্ণাঙ্ক *শীর্ষ, পূর্ণাঙ্ক *বাম, পূর্ণাঙ্ক *bottom, পূর্ণাঙ্ক *ডান)
{
    পূর্ণাঙ্ক dummy = 0;

    যদি (!শীর্ষ) {
        শীর্ষ = &dummy;
    }
    যদি (!বাম) {
        বাম = &dummy;
    }
    যদি (!ডান) {
        ডান = &dummy;
    }
    যদি (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *শীর্ষ = *বাম = *bottom = *ডান = 0;

    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->GetWindowBordersSize) {
        প্রত্যাগম SDL_Unsupported();
    }

    প্রত্যাগম _this->GetWindowBordersSize(_this, window, শীর্ষ, বাম, bottom, ডান);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, পূর্ণাঙ্ক *w, পূর্ণাঙ্ক *h)
{
    পূর্ণাঙ্ক filter;

    CHECK_WINDOW_MAGIC(window, false);

    যদি (!w) {
        w = &filter;
    }

    যদি (!h) {
        h = &filter;
    }

    যদি (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } অন্যথা {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ধ্রুব SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        যদি ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } অন্যথা {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        যদি (mode) {
            *w = (পূর্ণাঙ্ক)SDL_ceilf(*w * mode->pixel_density);
            *h = (পূর্ণাঙ্ক)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    প্রত্যাগম true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, পূর্ণাঙ্ক min_w, পূর্ণাঙ্ক min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        প্রত্যাগম SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        প্রত্যাগম SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        প্রত্যাগম SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    যদি (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    পূর্ণাঙ্ক w = window->last_size_pending ? window->pending.w : window->floating.w;
    পূর্ণাঙ্ক h = window->last_size_pending ? window->pending.h : window->floating.h;
    প্রত্যাগম SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, পূর্ণাঙ্ক *min_w, পূর্ণাঙ্ক *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    যদি (min_w) {
        *min_w = window->min_w;
    }
    যদি (min_h) {
        *min_h = window->min_h;
    }
    প্রত্যাগম true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, পূর্ণাঙ্ক max_w, পূর্ণাঙ্ক max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        প্রত্যাগম SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        প্রত্যাগম SDL_InvalidParamError("max_h");
    }

    যদি ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        প্রত্যাগম SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    যদি (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    পূর্ণাঙ্ক w = window->last_size_pending ? window->pending.w : window->floating.w;
    পূর্ণাঙ্ক h = window->last_size_pending ? window->pending.h : window->floating.h;
    প্রত্যাগম SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, পূর্ণাঙ্ক *max_w, পূর্ণাঙ্ক *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    যদি (max_w) {
        *max_w = window->max_w;
    }
    যদি (max_h) {
        *max_h = window->max_h;
    }
    প্রত্যাগম true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!(window->flags & SDL_WINDOW_HIDDEN)) {
        প্রত্যাগম true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    যদি (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        প্রত্যাগম true;
    }

    যদি (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } অন্যথা {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    প্রতি (child = window->first_child; child; child = child->next_sibling) {
        যদি (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            ভঙ্গ;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    প্রত্যাগম true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        প্রত্যাগম true;
    }

    // Hide all child windows
    প্রতি (child = window->first_child; child; child = child->next_sibling) {
        যদি (child->flags & SDL_WINDOW_HIDDEN) {
            ভঙ্গ;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ধ্রুব SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    যদি (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } অন্যথা {
        SDL_SetMouseFocus(রিক্ত);
        SDL_SetKeyboardFocus(রিক্ত);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    প্রত্যাগম true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        প্রত্যাগম true;
    }
    যদি (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    প্রত্যাগম true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->MaximizeWindow) {
        প্রত্যাগম SDL_Unsupported();
    }

    যদি (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        প্রত্যাগম SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        প্রত্যাগম true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    প্রত্যাগম true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->MinimizeWindow) {
        প্রত্যাগম SDL_Unsupported();
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        প্রত্যাগম true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    প্রত্যাগম true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->RestoreWindow) {
        প্রত্যাগম SDL_Unsupported();
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        প্রত্যাগম true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    প্রত্যাগম true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        যদি (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } অন্যথা {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        প্রত্যাগম true;
    }

    যদি (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    যদি (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    যদি (result) {
        SDL_SyncIfRequired(window);
    }

    প্রত্যাগম result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (_this->SyncWindow) {
        প্রত্যাগম _this->SyncWindow(_this, window);
    } অন্যথা {
        প্রত্যাগম true;
    }
}

স্থির bool ShouldAttemptTextureFramebuffer(শূন্য)
{
    ধ্রুব বর্ণ *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    যদি (!_this->CreateWindowFramebuffer) {
        প্রত্যাগম true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    যদি (hint && *hint) {
        যদি (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } অন্যথা {
            attempt_texture_framebuffer = true;
        }
    } অন্যথা {
        যদি (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } অন্যথা {
            attempt_texture_framebuffer = false;
        }
    }
    প্রত্যাগম attempt_texture_framebuffer;
}

স্থির SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    শূন্য *pixels = রিক্ত;
    পূর্ণাঙ্ক pitch = 0;
    bool created_framebuffer = false;
    পূর্ণাঙ্ক w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    যদি (!_this->checked_texture_framebuffer) {
        যদি (ShouldAttemptTextureFramebuffer()) {
            যদি (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } অন্যথা {
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

    যদি (!created_framebuffer) {
        যদি (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            প্রত্যাগম রিক্ত;
        }

        যদি (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            প্রত্যাগম রিক্ত;
        }
    }

    যদি (window->surface) {
        // We may have gone recursive and already created the surface
        প্রত্যাগম window->surface;
    }

    প্রত্যাগম SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    প্রত্যাগম window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, রিক্ত);

    যদি (!window->surface_valid) {
        যদি (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = রিক্ত;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        যদি (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    প্রত্যাগম window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, পূর্ণাঙ্ক vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowFramebufferVSync) {
        প্রত্যাগম SDL_Unsupported();
    }
    প্রত্যাগম _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, পূর্ণাঙ্ক *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->GetWindowFramebufferVSync) {
        প্রত্যাগম SDL_Unsupported();
    }
    প্রত্যাগম _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    প্রত্যাগম SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ধ্রুব SDL_Rect *rects,
                                 পূর্ণাঙ্ক numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!window->surface_valid) {
        প্রত্যাগম SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    প্রত্যাগম _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = রিক্ত;
        window->surface_valid = false;
    }

    যদি (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        যদি (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    প্রত্যাগম true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, ভিন্ন opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowOpacity) {
        প্রত্যাগম SDL_Unsupported();
    }

    যদি (opacity < 0.0f) {
        opacity = 0.0f;
    } অন্যথা যদি (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    যদি (result) {
        window->opacity = opacity;
    }

    প্রত্যাগম result;
}

ভিন্ন SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    প্রত্যাগম window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    যদি (window == parent) {
        প্রত্যাগম SDL_SetError("Cannot set the parent of a window to itself.");
    }

    যদি (!_this->SetWindowParent) {
        প্রত্যাগম SDL_Unsupported();
    }

    যদি (window->flags & SDL_WINDOW_MODAL) {
        প্রত্যাগম SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    যদি (window->parent == parent) {
        প্রত্যাগম true;
    }

    ধ্রুব bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : রিক্ত);

    প্রত্যাগম ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->SetWindowModal) {
        প্রত্যাগম SDL_Unsupported();
    }

    যদি (modal) {
        যদি (!window->parent) {
            প্রত্যাগম SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } অন্যথা যদি (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } অন্যথা {
        প্রত্যাগম true; // Already not modal, so nothing to do.
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        প্রত্যাগম true;
    }

    প্রত্যাগম _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_প্রবেশ_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    যাবত্ (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        যদি (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_প্রবেশ_FOCUS);
        }
    }

    *new_focus = focus;
    প্রত্যাগম set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    প্রতি (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    প্রতি (w = current_focus; w != toplevel_parent; w = w->parent) {
        যদি (w == window) {
            found_higher_focus = true;
            ভঙ্গ;
        }
    }

    প্রত্যাগম !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ধ্রুব bool want = (focusable != false); // normalize the flag.
    ধ্রুব bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    যদি ((want != have) && (_this->SetWindowFocusable)) {
        যদি (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } অন্যথা {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        যদি (!_this->SetWindowFocusable(_this, window, want)) {
            প্রত্যাগম false;
        }
    }

    প্রত্যাগম true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ধ্রুব bool want = (fill != false); // normalize the flag.
    ধ্রুব bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    যদি ((want != have) && (_this->SetWindowFillDocument)) {
        যদি (!_this->SetWindowFillDocument(_this, window, want)) {
            প্রত্যাগম false;
        } অন্যথা যদি (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } অন্যথা {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    প্রত্যাগম true;
}

শূন্য SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    যদি (window->flags & SDL_WINDOW_প্রবেশ_FOCUS) {
        যদি (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } অন্যথা {
            mouse_grabbed = false;
        }

        যদি (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } অন্যথা {
            keyboard_grabbed = false;
        }
    } অন্যথা {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    যদি (mouse_grabbed || keyboard_grabbed) {
        যদি (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            যদি (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            যদি (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } অন্যথা যদি (_this->grabbed_window == window) {
        _this->grabbed_window = রিক্ত; // ungrabbing input.
    }

    যদি (_this->SetWindowMouseGrab) {
        যদি (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    যদি (_this->SetWindowKeyboardGrab) {
        যদি (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    যদি (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = রিক্ত;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        যদি (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } অন্যথা {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        প্রত্যাগম true;
    }

    যদি (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        প্রত্যাগম true;
    }
    যদি (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } অন্যথা {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    যদি (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        প্রত্যাগম false;
    }
    প্রত্যাগম true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        যদি (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } অন্যথা {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        প্রত্যাগম true;
    }

    যদি (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        প্রত্যাগম true;
    }
    যদি (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } অন্যথা {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    যদি (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        প্রত্যাগম false;
    }
    প্রত্যাগম true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    প্রত্যাগম window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    প্রত্যাগম window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(শূন্য)
{
    যদি (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        প্রত্যাগম _this->grabbed_window;
    } অন্যথা {
        প্রত্যাগম রিক্ত;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ধ্রুব SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowMouseRect) {
        প্রত্যাগম SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    যদি (!rect) {
        rect = &zero;
    }

    যদি (SDL_memcmp(&window->mouse_rect, rect, পরিমাণ(*rect)) == 0) {
        প্রত্যাগম true;
    }
    SDL_memcpy(&window->mouse_rect, rect, পরিমাণ(*rect));

    প্রত্যাগম _this->SetWindowMouseRect(_this, window);
}

ধ্রুব SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, রিক্ত);

    যদি (SDL_RectEmpty(&window->mouse_rect)) {
        প্রত্যাগম রিক্ত;
    } অন্যথা {
        প্রত্যাগম &window->mouse_rect;
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

    যদি (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        প্রত্যাগম true;
    }

    যদি (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } অন্যথা {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    যদি (!SDL_UpdateRelativeMouseMode()) {
        যদি (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } অন্যথা {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        প্রত্যাগম false;
    }
    প্রত্যাগম true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        প্রত্যাগম true;
    } অন্যথা {
        প্রত্যাগম false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (_this->FlashWindow) {
        প্রত্যাগম _this->FlashWindow(_this, window, operation);
    }

    প্রত্যাগম SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        প্রত্যাগম SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    যদি (_this->ApplyWindowProgress) {
        যদি (!_this->ApplyWindowProgress(_this, window)) {
            প্রত্যাগম false;
        }
    }

    প্রত্যাগম true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    প্রত্যাগম window->progress_state;
}

bool SDL_Set_Window_Progress_মান(SDL_Window *window, ভিন্ন মান)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    মান = SDL_clamp(মান, 0.0f, 1.f);

    window->progress_মান = মান;

    যদি (_this->ApplyWindowProgress) {
        যদি (!_this->ApplyWindowProgress(_this, window)) {
            প্রত্যাগম false;
        }
    }

    প্রত্যাগম true;
}

ভিন্ন SDL_Get_Window_Progress_মান(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    প্রত্যাগম window->progress_মান;
}

শূন্য SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

শূন্য SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

শূন্য SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    যদি (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        ধ্রুব bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        যদি (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_উপরের_density_modes = false;

            যদি (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_উপরের_density_modes = true;
            }
            ধ্রুব bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_উপরের_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            যদি (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } অন্যথা {
            SDL_zero(window->current_fullscreen_mode);
        }

        যদি (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

শূন্য SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

শূন্য SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    যদি ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, রিক্ত);
        যদি (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

শূন্য SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    পূর্ণাঙ্ক pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

শূন্য SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

শূন্য SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    যদি (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } অন্যথা {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

স্থির শূন্য SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_বাম;
    rect.y = window->safe_inset_শীর্ষ;
    rect.w = window->w - (window->safe_inset_ডান + window->safe_inset_বাম);
    rect.h = window->h - (window->safe_inset_শীর্ষ + window->safe_inset_bottom);
    যদি (SDL_memcmp(&rect, &window->safe_rect, পরিমাণ(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

শূন্য SDL_SetWindowSafeAreaInsets(SDL_Window *window, পূর্ণাঙ্ক বাম, পূর্ণাঙ্ক ডান, পূর্ণাঙ্ক শীর্ষ, পূর্ণাঙ্ক bottom)
{
    window->safe_inset_বাম = বাম;
    window->safe_inset_ডান = ডান;
    window->safe_inset_শীর্ষ = শীর্ষ;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    যদি (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    যদি (rect) {
        যদি (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } অন্যথা {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    প্রত্যাগম true;
}

শূন্য SDL_OnWindowMinimized(SDL_Window *window)
{
    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

শূন্য SDL_OnWindowMaximized(SDL_Window *window)
{
}

শূন্য SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

শূন্য SDL_OnWindowEnter(SDL_Window *window)
{
    যদি (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

শূন্য SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

শূন্য SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    যদি (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

স্থির bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    ধ্রুব বর্ণ *hint;

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        প্রত্যাগম false;
    }

#যদি defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    যদি (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        যদি (Cocoa_IsShowingModalDialog(window)) {
            প্রত্যাগম false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } অন্যথা যদি (Cocoa_IsWindowInFullscreenSpace(window)) {
            প্রত্যাগম false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        বাহ্য bool Android_JNI_ShouldMinimizeOnFocusLoss(শূন্য);
        যদি (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            প্রত্যাগম false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    যদি (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        যদি (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            প্রত্যাগম true;
        } অন্যথা {
            প্রত্যাগম false;
        }
    }
    প্রত্যাগম SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

শূন্য SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    যদি (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(শূন্য)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    যদি (focus) {
        // Get the toplevel parent window.
        যাবত্ (focus->parent) {
            focus = focus->parent;
        }
    }

    প্রত্যাগম focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->অঙ্ক_renderers + 1) * পরিমাণ(*renderers));
    যদি (!renderers) {
        প্রত্যাগম false;
    }

    window->renderers = renderers;
    window->renderers[window->অঙ্ক_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    প্রত্যাগম true;
}

শূন্য SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < window->অঙ্ক_renderers; ++i) {
        যদি (window->renderers[i] == renderer) {
            যদি (i < (window->অঙ্ক_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->অঙ্ক_renderers - i - 1) * পরিমাণ(window->renderers[i]));
            }
            --window->অঙ্ক_renderers;
            ভঙ্গ;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    যদি (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, রিক্ত) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

শূন্য SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    যাবত্ (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    যদি (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_প্রবেশ_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    যদি (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    প্রতি (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; ++i) {
        যদি (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = রিক্ত;
        }
    }

    // Make sure this window no longer has focus
    যদি (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(রিক্ত);
    }
    যদি ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    যদি (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(রিক্ত);
    }

    // Make no context current if this is the current context window
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        যদি (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, রিক্ত);
        }
    }

    যদি (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    যদি (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    যদি (_this->grabbed_window == window) {
        _this->grabbed_window = রিক্ত; // ungrabbing input.
    }

    যদি (_this->current_glwin == window) {
        _this->current_glwin = রিক্ত;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, রিক্ত);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, রিক্ত);

    // Unlink the window from the global window list
    যদি (window->next) {
        window->next->prev = window->prev;
    }
    যদি (window->prev) {
        window->prev->next = window->next;
    } অন্যথা {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(শূন্য)
{
    যদি (!_this) {
        প্রত্যাগম true;
    }
    প্রত্যাগম !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(শূন্য)
{
    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }
    যদি (!_this->suspend_screensaver) {
        প্রত্যাগম true;
    }
    _this->suspend_screensaver = false;
    যদি (_this->SuspendScreenSaver) {
        প্রত্যাগম _this->SuspendScreenSaver(_this);
    }

    প্রত্যাগম SDL_Unsupported();
}

bool SDL_DisableScreenSaver(শূন্য)
{
    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }
    যদি (_this->suspend_screensaver) {
        প্রত্যাগম true;
    }
    _this->suspend_screensaver = true;
    যদি (_this->SuspendScreenSaver) {
        প্রত্যাগম _this->SuspendScreenSaver(_this);
    }

    প্রত্যাগম SDL_Unsupported();
}

শূন্য SDL_QuitVideo(শূন্য)
{
    পূর্ণাঙ্ক i;

    যদি (!_this) {
        প্রত্যাগম;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#যদি 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    যাবত্ (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    যদি (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    যদি (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    প্রতি (i = _this->অঙ্ক_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->অঙ্ক_displays == 0);
    SDL_free(_this->displays);
    _this->displays = রিক্ত;

    SDL_CancelClipboardData(0);

    যদি (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = রিক্ত;
    }
    _this->মুক্ত(_this);
    _this = রিক্ত;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(ধ্রুব বর্ণ *path)
{
    bool result;

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }
    যদি (_this->gl_config.driver_loaded) {
        যদি (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            প্রত্যাগম SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } অন্যথা {
        যদি (!_this->GL_LoadLibrary) {
            প্রত্যাগম SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    যদি (result) {
        ++_this->gl_config.driver_loaded;
    } অন্যথা {
        যদি (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    প্রত্যাগম result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ধ্রুব বর্ণ *proc)
{
    SDL_FunctionPointer func;

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    func = রিক্ত;
    যদি (_this->GL_GetProcAddress) {
        যদি (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } অন্যথা {
            SDL_SetError("No GL driver has been loaded");
        }
    } অন্যথা {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    প্রত্যাগম func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ধ্রুব বর্ণ *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    func = রিক্ত;

    যদি (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } অন্যথা {
        SDL_SetError("No EGL library has been loaded");
    }

    প্রত্যাগম func;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    প্রত্যাগম রিক্ত;
#endif
}

শূন্য SDL_GL_UnloadLibrary(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম;
    }
    যদি (_this->gl_config.driver_loaded > 0) {
        যদি (--_this->gl_config.driver_loaded > 0) {
            প্রত্যাগম;
        }
        যদি (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
প্রকারনির্দেশ GLenum (APIENTRY* PFNGLGETERRORPROC) (শূন্য);
প্রকারনির্দেশ শূন্য (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
প্রকারনির্দেশ ধ্রুব GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
প্রকারনির্দেশ শূন্য (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
প্রকারনির্দেশ ধ্রুব GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

স্থির SDL_INLINE bool isAtLeastGL3(ধ্রুব বর্ণ *verstr)
{
    প্রত্যাগম verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ধ্রুব বর্ণ *extension)
{
#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ধ্রুব বর্ণ *extensions;
    ধ্রুব বর্ণ *start;
    ধ্রুব বর্ণ *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    যদি (where || *extension == '\0') {
        প্রত্যাগম false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    যদি (start && *start == '0') {
        প্রত্যাগম false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    যদি (!glGetStringFunc) {
        প্রত্যাগম false;
    }

    যদি (isAtLeastGL3((ধ্রুব বর্ণ *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint অঙ্ক_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        যদি ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            প্রত্যাগম false;
        }

#ifndef GL_অঙ্ক_EXTENSIONS
#define GL_অঙ্ক_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_অঙ্ক_EXTENSIONS, &অঙ্ক_exts);
        প্রতি (i = 0; i < অঙ্ক_exts; i++) {
            ধ্রুব বর্ণ *thisext = (ধ্রুব বর্ণ *)glGetStringiFunc(GL_EXTENSIONS, i);
            যদি (SDL_strcmp(thisext, extension) == 0) {
                প্রত্যাগম true;
            }
        }

        প্রত্যাগম false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ধ্রুব বর্ণ *)glGetStringFunc(GL_EXTENSIONS);
    যদি (!extensions) {
        প্রত্যাগম false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    প্রতি (;;) {
        where = SDL_strstr(start, extension);
        যদি (!where) {
            ভঙ্গ;
        }

        terminator = where + SDL_strlen(extension);
        যদি (where == extensions || *(where - 1) == ' ') {
            যদি (*terminator == ' ' || *terminator == '\0') {
                প্রত্যাগম true;
            }
        }

        start = terminator;
    }
    প্রত্যাগম false;
#অন্যথা
    প্রত্যাগম false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
শূন্য SDL_GL_DeduceMaxSupportedESProfile(পূর্ণাঙ্ক *major, পূর্ণাঙ্ক *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    যদি (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } অন্যথা যদি (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } অন্যথা যদি (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } অন্যথা {
        *major = 2;
        *minor = 0;
    }
#endif
}

শূন্য SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   শূন্য *userdata)
{
    যদি (!_this) {
        প্রত্যাগম;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

শূন্য SDL_GL_ResetAttributes(শূন্য)
{
    যদি (!_this) {
        প্রত্যাগম;
    }

    _this->egl_platformattrib_callback = রিক্ত;
    _this->egl_surfaceattrib_callback = রিক্ত;
    _this->egl_contextattrib_callback = রিক্ত;
    _this->egl_attrib_callback_userdata = রিক্ত;

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
#নোচেদ্যদি defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#নোচেদ্যদি defined(SDL_VIDEO_OPENGL_ES)
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

    যদি (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, পূর্ণাঙ্ক মান)
{
#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }
    result = true;
    বিকল্প (attr) {
    পক্ষ SDL_GL_RED_SIZE:
        _this->gl_config.red_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_STEREO:
        _this->gl_config.stereo = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_FLAGS:
        যদি (মান & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", মান);
            ভঙ্গ;
        }
        _this->gl_config.flags = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_PROFILE_MASK:
        যদি (মান != 0 &&
            মান != SDL_GL_CONTEXT_PROFILE_CORE &&
            মান != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            মান != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", মান);
            ভঙ্গ;
        }
        _this->gl_config.profile_mask = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = মান;
        ভঙ্গ;
    পক্ষ SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = মান;
        ভঙ্গ;
    স্বভাব:
        result = SDL_SetError("Unknown OpenGL attribute");
        ভঙ্গ;
    }
    প্রত্যাগম result;
#অন্যথা
    প্রত্যাগম SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, পূর্ণাঙ্ক *মান)
{
#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_বাম;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!মান) {
        প্রত্যাগম SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *মান = 0;

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    বিকল্প (attr) {
    পক্ষ SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        ভঙ্গ;
#অন্যথা
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *মান = _this->gl_config.double_buffer;
        প্রত্যাগম true;
#endif
    পক্ষ SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        ভঙ্গ;
#ifdef SDL_VIDEO_OPENGL
    পক্ষ SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        ভঙ্গ;
    পক্ষ SDL_GL_STEREO:
        attrib = GL_STEREO;
        ভঙ্গ;
#অন্যথা
    পক্ষ SDL_GL_ACCUM_RED_SIZE:
    পক্ষ SDL_GL_ACCUM_GREEN_SIZE:
    পক্ষ SDL_GL_ACCUM_BLUE_SIZE:
    পক্ষ SDL_GL_ACCUM_ALPHA_SIZE:
    পক্ষ SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *মান = 0;
        প্রত্যাগম true;
#endif
    পক্ষ SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        ভঙ্গ;
    পক্ষ SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        ভঙ্গ;
    পক্ষ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        ভঙ্গ;
    পক্ষ SDL_GL_BUFFER_SIZE:
    {
        পূর্ণাঙ্ক rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        যদি (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            প্রত্যাগম false;
        }
        যদি (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            প্রত্যাগম false;
        }
        যদি (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            প্রত্যাগম false;
        }
        যদি (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            প্রত্যাগম false;
        }

        *মান = rsize + gsize + bsize + asize;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *মান = (_this->gl_config.accelerated != 0);
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_RETAINED_BACKING:
    {
        *মান = _this->gl_config.retained_backing;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *মান = _this->gl_config.major_version;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *মান = _this->gl_config.minor_version;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_CONTEXT_FLAGS:
    {
        *মান = _this->gl_config.flags;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *মান = _this->gl_config.profile_mask;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *মান = _this->gl_config.share_with_current_context;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *মান = _this->gl_config.framebuffer_srgb_capable;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_CONTEXT_NO_ERROR:
    {
        *মান = _this->gl_config.no_error;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_EGL_PLATFORM:
    {
        *মান = _this->gl_config.egl_platform;
        প্রত্যাগম true;
    }
    পক্ষ SDL_GL_FLOATBUFFERS:
    {
        যদি (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            ভঙ্গ;
        } অন্যথা {
            প্রত্যাগম 0;
        }
    }
    স্বভাব:
        প্রত্যাগম SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    যদি (!glGetStringFunc) {
        প্রত্যাগম false;
    }

    যদি (attachmentattrib && isAtLeastGL3((ধ্রুব বর্ণ *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        যদি (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        যদি (glGetFramebufferAttachmentParameterivFunc) {
            যদি (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            যদি (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            যদি (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)মান);
            } অন্যথা {
                *মান = 0;
            }
            যদি (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } অন্যথা {
            প্রত্যাগম false;
        }
    } অন্যথা
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        যদি (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)মান);
        } অন্যথা {
            প্রত্যাগম false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    যদি (!glGetErrorFunc) {
        প্রত্যাগম false;
    }

    error = glGetErrorFunc();
    যদি (error != GL_NO_ERROR) {
        যদি (error == GL_INVALID_ENUM) {
            প্রত্যাগম SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } অন্যথা যদি (error == GL_INVALID_মান) {
            প্রত্যাগম SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        প্রত্যাগম SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    যদি (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *মান = (*মান == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    প্রত্যাগম true;
#অন্যথা
    প্রত্যাগম SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = রিক্ত;
    CHECK_WINDOW_MAGIC(window, রিক্ত);

    যদি (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        প্রত্যাগম রিক্ত;
    }

#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    পূর্ণাঙ্ক srgb_requested = -1;
    ধ্রুব বর্ণ *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    যদি (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    যদি (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, রিক্ত);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, রিক্ত);
    }

#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    যদি (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        যদি (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            যদি (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } অন্যথা {
                supported = isAtLeastGL3((ধ্রুব বর্ণ *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            যদি (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    প্রত্যাগম ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }

    যদি (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        প্রত্যাগম true;
    }

    যদি (!context) {
        window = রিক্ত;
    } অন্যথা যদি (window) {
        CHECK_WINDOW_MAGIC(window, false);

        যদি (!(window->flags & SDL_WINDOW_OPENGL)) {
            প্রত্যাগম SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } অন্যথা যদি (!_this->gl_allow_no_surface) {
        প্রত্যাগম SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    যদি (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, রিক্ত);
        SDL_SetTLS(&_this->current_glctx_tls, context, রিক্ত);
    }
    প্রত্যাগম result;
}

SDL_Window *SDL_GL_GetCurrentWindow(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(শূন্য)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম EGL_NO_DISPLAY;
    }
    যদি (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        প্রত্যাগম EGL_NO_DISPLAY;
    }
    প্রত্যাগম _this->egl_data->egl_display;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    প্রত্যাগম রিক্ত;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(শূন্য)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    যদি (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম _this->egl_data->egl_config;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    প্রত্যাগম রিক্ত;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    যদি (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        প্রত্যাগম রিক্ত;
    }
    যদি (_this->GL_GetEGLSurface) {
        প্রত্যাগম _this->GL_GetEGLSurface(_this, window);
    }
    প্রত্যাগম রিক্ত;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    প্রত্যাগম রিক্ত;
#endif
}

bool SDL_GL_SetSwapInterval(পূর্ণাঙ্ক interval)
{
    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    } অন্যথা যদি (SDL_GL_GetCurrentContext() == রিক্ত) {
        প্রত্যাগম SDL_SetError("No OpenGL context has been made current");
    } অন্যথা যদি (_this->GL_SetSwapInterval) {
        প্রত্যাগম _this->GL_SetSwapInterval(_this, interval);
    } অন্যথা {
        প্রত্যাগম SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(পূর্ণাঙ্ক *interval)
{
    CHECK_PARAM(!interval) {
       প্রত্যাগম SDL_InvalidParamError("interval");
    }

    *interval = 0;

    যদি (!_this) {
        প্রত্যাগম SDL_SetError("no video driver");
    } অন্যথা যদি (SDL_GL_GetCurrentContext() == রিক্ত) {
        প্রত্যাগম SDL_SetError("no current context");
    } অন্যথা যদি (_this->GL_GetSwapInterval) {
        প্রত্যাগম _this->GL_GetSwapInterval(_this, interval);
    } অন্যথা {
        প্রত্যাগম SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!(window->flags & SDL_WINDOW_OPENGL)) {
        প্রত্যাগম SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    যদি (SDL_GL_GetCurrentWindow() != window) {
        প্রত্যাগম SDL_SetError("The specified window has not been made current");
    }

    প্রত্যাগম _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        প্রত্যাগম SDL_InvalidParamError("context");
    }

    যদি (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(রিক্ত, রিক্ত);
    }

    প্রত্যাগম _this->GL_DestroyContext(_this, context);
}

#যদি 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
স্থির শূন্য Create_Mask_From_Color_চাবি_Or_Alpha(SDL_Surface *icon, Uint8 *mask, পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    বিকল্প (SDL_BYTESPERPIXEL(icon->format)) {
    পক্ষ 1:
        {
            Uint8 *pixels;
            প্রতি (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                প্রতি (x = 0; x < icon->w; ++x) {
                    যদি (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        ভঙ্গ;

    পক্ষ 2:
        {
            Uint16 *pixels;
            প্রতি (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                প্রতি (x = 0; x < icon->w; ++x) {
                    যদি ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } অন্যথা যদি ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        ভঙ্গ;

    পক্ষ 4:
        {
            Uint32 *pixels;
            প্রতি (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                প্রতি (x = 0; x < icon->w; ++x) {
                    যদি ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } অন্যথা যদি ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        ভঙ্গ;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
শূন্য SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    যদি (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        যদি (mask == রিক্ত) {
            পূর্ণাঙ্ক mask_len = icon->h * (icon->w + 7) / 8;
            পূর্ণাঙ্ক flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            যদি (mask == রিক্ত) {
                প্রত্যাগম;
            }
            SDL_memset(mask, ~0, mask_len);
            যদি (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            যদি (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            যদি (flags) {
                Create_Mask_From_Color_চাবি_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } অন্যথা {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_প্রবেশ_Type SDL_Get_Text_প্রবেশ_Type(SDL_PropertiesID props)
{
    প্রত্যাগম (SDL_Text_প্রবেশ_Type)SDL_Get_সংখ্যা_Property(props, SDL_PROP_TEXTINPUT_TYPE_সংখ্যা, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_প্রবেশ_Capitalization(SDL_PropertiesID props)
{
    যদি (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_সংখ্যা)) {
        প্রত্যাগম (SDL_Capitalization)SDL_Get_সংখ্যা_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_সংখ্যা, SDL_CAPITALIZE_NONE);
    }

    বিকল্প (SDL_Get_Text_প্রবেশ_Type(props)) {
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT:
        প্রত্যাগম SDL_CAPITALIZE_SENTENCES;
    পক্ষ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        প্রত্যাগম SDL_CAPITALIZE_শব্দগুলি;
    স্বভাব:
        প্রত্যাগম SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_প্রবেশ_Autocorrect(SDL_PropertiesID props)
{
    প্রত্যাগম SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_প্রবেশ_Multiline(SDL_PropertiesID props)
{
    যদি (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        প্রত্যাগম SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    যদি (SDL_GetHintBoolean(SDL_HINT_RETURN_চাবি_HIDES_IME, false)) {
        প্রত্যাগম false;
    } অন্যথা {
        প্রত্যাগম true;
    }
}

স্থির bool AutoShowingScreenKeyboard(শূন্য)
{
    ধ্রুব বর্ণ *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    যদি (!hint) {
        // This hint is currently only used by the X11 video driver
        যদি (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    যদি (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        প্রত্যাগম true;
    } অন্যথা {
        প্রত্যাগম false;
    }
}

bool SDL_Start_Text_প্রবেশ(SDL_Window *window)
{
    প্রত্যাগম SDL_Start_Text_প্রবেশ_With_Properties(window, 0);
}

bool SDL_Start_Text_প্রবেশ_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->text_প্রবেশ_props) {
        SDL_DestroyProperties(window->text_প্রবেশ_props);
        window->text_প্রবেশ_props = 0;
    }

    যদি (props) {
        window->text_প্রবেশ_props = SDL_CreateProperties();
        যদি (!window->text_প্রবেশ_props) {
            প্রত্যাগম false;
        }
        যদি (!SDL_CopyProperties(props, window->text_প্রবেশ_props)) {
            প্রত্যাগম false;
        }
    }

    যদি (_this->Set_Text_প্রবেশ_Properties) {
        _this->Set_Text_প্রবেশ_Properties(_this, window, props);
    }

    যদি (!window->text_প্রবেশ_active) {
        // Start the text input system
        যদি (_this->Start_Text_প্রবেশ) {
            যদি (!_this->Start_Text_প্রবেশ(_this, window, props)) {
                প্রত্যাগম false;
            }
        }
        window->text_প্রবেশ_active = true;
    }

    // Show the on-screen keyboard, if desired
    যদি (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        যদি (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    প্রত্যাগম true;
}

bool SDL_Text_প্রবেশ_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    প্রত্যাগম window->text_প্রবেশ_active;
}

bool SDL_Stop_Text_প্রবেশ(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->text_প্রবেশ_active) {
        // Stop the text input system
        যদি (_this->Stop_Text_প্রবেশ) {
            _this->Stop_Text_প্রবেশ(_this, window);
        }
        window->text_প্রবেশ_active = false;
    }

    // Hide the on-screen keyboard, if desired
    যদি (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        যদি (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    প্রত্যাগম true;
}

bool SDL_Set_Text_প্রবেশ_Area(SDL_Window *window, ধ্রুব SDL_Rect *rect, পূর্ণাঙ্ক cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (rect) {
        SDL_copyp(&window->text_প্রবেশ_rect, rect);
        window->text_প্রবেশ_cursor = cursor;
    } অন্যথা {
        SDL_zero(window->text_প্রবেশ_rect);
        window->text_প্রবেশ_cursor = 0;
    }

    যদি (_this && _this->Update_Text_প্রবেশ_Area) {
        যদি (!_this->Update_Text_প্রবেশ_Area(_this, window)) {
            প্রত্যাগম false;
        }
    }
    প্রত্যাগম true;
}

bool SDL_Get_Text_প্রবেশ_Area(SDL_Window *window, SDL_Rect *rect, পূর্ণাঙ্ক *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (rect) {
        SDL_copyp(rect, &window->text_প্রবেশ_rect);
    }
    যদি (cursor) {
        *cursor = window->text_প্রবেশ_cursor;
    }
    প্রত্যাগম true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (_this->ClearComposition) {
        প্রত্যাগম _this->ClearComposition(_this, window);
    }
    প্রত্যাগম true;
}

bool SDL_HasScreenKeyboardSupport(শূন্য)
{
    যদি (_this && _this->HasScreenKeyboardSupport) {
        প্রত্যাগম _this->HasScreenKeyboardSupport(_this);
    }
    প্রত্যাগম false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    প্রত্যাগম _this->screen_keyboard_shown;
}

শূন্য SDL_SendScreenKeyboardShown(শূন্য)
{
    যদি (!_this || _this->screen_keyboard_shown) {
        প্রত্যাগম;
    }

    _this->screen_keyboard_shown = true;

    যদি (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ঠেলো_Event(&event);
    }
}

শূন্য SDL_SendScreenKeyboardHidden(শূন্য)
{
    যদি (!_this || !_this->screen_keyboard_shown) {
        প্রত্যাগম;
    }

    _this->screen_keyboard_shown = false;

    যদি (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ঠেলো_Event(&event);
    }
}

পূর্ণাঙ্ক SDL_Get_Message_Box_গুনতি(শূন্য)
{
    প্রত্যাগম SDL_GetAtomicInt(&SDL_messagebox_গুনতি);
}

bool SDL_ShowMessageBox(ধ্রুব SDL_MessageBoxData *messageboxdata, পূর্ণাঙ্ক *buttonID)
{
    পূর্ণাঙ্ক dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        প্রত্যাগম SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        প্রত্যাগম SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    বর্ণ *titlecpy = রিক্ত;
    বর্ণ *msgcpy = রিক্ত;
    যদি (messageboxdata->title) {
        ধ্রুব size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(বর্ণ, slen, &titleisstack);
        যদি (!titlecpy) {
            প্রত্যাগম false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    যদি (messageboxdata->message) {
        ধ্রুব size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(বর্ণ, slen, &msgisstack);
        যদি (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            প্রত্যাগম false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (শূন্য)SDL_AtomicIncRef(&SDL_messagebox_গুনতি);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    যদি (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, পরিমাণ(*messageboxdata));
    mbdata.title = titlecpy;
    যদি (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    যদি (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    যদি (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } অন্যথা {
        // It's completely fine to call this function before video is initialized
        ধ্রুব বর্ণ *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        যদি (driver_name && *driver_name != 0) {
            ধ্রুব বর্ণ *driver_attempt = driver_name;
            যাবত্ (driver_attempt && (*driver_attempt != 0) && !result) {
                ধ্রুব বর্ণ *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                প্রতি (পূর্ণাঙ্ক i = 0; bootstrap[i]; ++i) {
                    যদি (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        যদি (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        ভঙ্গ;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : রিক্ত;
            }
        } অন্যথা {
            প্রতি (পূর্ণাঙ্ক i = 0; bootstrap[i]; ++i) {
                যদি (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    ভঙ্গ;
                }
            }
        }
    }

    যদি (!result) {
        ধ্রুব বর্ণ *error = SDL_GetError();

        যদি (!*error) {
            SDL_SetError("No message system available");
        }
    } অন্যথা {
        SDL_ClearError();
    }

    (শূন্য)SDL_AtomicDecRef(&SDL_messagebox_গুনতি);

    যদি (current_window) {
        SDL_RaiseWindow(current_window);
    }

    যদি (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    প্রত্যাগম result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ধ্রুব বর্ণ *title, ধ্রুব বর্ণ *message, SDL_Window *window)
{
#যদি defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_ডান;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_ডান = gsp_Has_Gpu_ডান();
    যদি (!has_Gpu_ডান)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    যদি (!has_Gpu_ডান)
        gfxExit();

    প্রত্যাগম true;
#অন্যথা
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

    প্রত্যাগম SDL_ShowMessageBox(&data, রিক্ত);
#endif
}

bool SDL_ShouldAllowTopmost(শূন্য)
{
    প্রত্যাগম SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        প্রত্যাগম true;
    }

    প্রত্যাগম SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, শূন্য *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowHitTest) {
        প্রত্যাগম SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    প্রত্যাগম _this->SetWindowHitTest(window, callback != রিক্ত);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    যদি (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        প্রত্যাগম SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    যদি (!props) {
        প্রত্যাগম false;
    }

    যদি (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        যদি (!surface) {
            প্রত্যাগম false;
        }
    } অন্যথা {
        surface = রিক্ত;
    }

    যদি (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        প্রত্যাগম false;
    }

    যদি (_this->UpdateWindowShape) {
        যদি (!_this->UpdateWindowShape(_this, window, surface)) {
            প্রত্যাগম false;
        }
    }
    প্রত্যাগম true;
}

/*
 * Functions used by iOS application delegates
 */
শূন্য SDL_OnApplicationWillTerminate(শূন্য)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

শূন্য SDL_OnApplicationDidReceiveMemoryWarning(শূন্য)
{
    SDL_SendAppEvent(SDL_EVENT_নিচের_MEMORY);
}

শূন্য SDL_OnApplicationWillEnterBackground(শূন্য)
{
    যদি (_this) {
        SDL_Window *window;
        প্রতি (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(রিক্ত);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

শূন্য SDL_OnApplicationDidEnterBackground(শূন্য)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

শূন্য SDL_OnApplicationWillEnterForeground(শূন্য)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

শূন্য SDL_OnApplicationDidEnterForeground(শূন্য)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    যদি (_this) {
        SDL_Window *window;
        প্রতি (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ধ্রুব বর্ণ *path)
{
    bool result;

    যদি (!_this) {
        প্রত্যাগম SDL_UninitializedVideo();
    }
    যদি (_this->vulkan_config.loader_loaded) {
        যদি (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            প্রত্যাগম SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } অন্যথা {
        যদি (!_this->Vulkan_LoadLibrary) {
            প্রত্যাগম SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    যদি (result) {
        _this->vulkan_config.loader_loaded++;
    }
    প্রত্যাগম result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম রিক্ত;
    }
    যদি (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

শূন্য SDL_Vulkan_UnloadLibrary(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম;
    }
    যদি (_this->vulkan_config.loader_loaded > 0) {
        যদি (--_this->vulkan_config.loader_loaded > 0) {
            প্রত্যাগম;
        }
        যদি (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

বর্ণ ধ্রুব * ধ্রুব *SDL_Vulkan_GetInstanceExtensions(Uint32 *গুনতি)
{
    Uint32 tmpcount = 0;
    যদি (!গুনতি) {
        গুনতি = &tmpcount;
    }

    যদি (!_this->Vulkan_GetInstanceExtensions) {
        *গুনতি = 0;
        SDL_Unsupported();
        প্রত্যাগম রিক্ত;
    }

    প্রত্যাগম _this->Vulkan_GetInstanceExtensions(_this, গুনতি);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ধ্রুব সংরচনা VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        প্রত্যাগম false;
    }

    CHECK_PARAM(!instance) {
        প্রত্যাগম SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        প্রত্যাগম SDL_InvalidParamError("surface");
    }

    যদি (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        যদি (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        যদি (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        যদি (SDL_Vulkan_LoadLibrary(রিক্ত)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } অন্যথা {
            প্রত্যাগম SDL_SetError("failed to load Vulkan library");
        }
    }

    প্রত্যাগম _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

শূন্য SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ধ্রুব সংরচনা VkAllocationCallbacks *allocator)
{
    যদি (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        প্রত্যাগম false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        প্রত্যাগম false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        প্রত্যাগম false;
    }

    যদি (_this->Vulkan_GetPresentationSupport) {
        প্রত্যাগম _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    প্রত্যাগম true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, রিক্ত);

    যদি (!_this->Metal_CreateView) {
        SDL_Unsupported();
        প্রত্যাগম রিক্ত;
    }

    যদি (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        যদি (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        যদি (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    প্রত্যাগম _this->Metal_CreateView(_this, window);
}

শূন্য SDL_Metal_DestroyView(SDL_MetalView view)
{
    যদি (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

শূন্য *SDL_Metal_GetLayer(SDL_MetalView view)
{
    যদি (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            প্রত্যাগম রিক্ত;
        }
        প্রত্যাগম _this->Metal_GetLayer(_this, view);
    } অন্যথা {
        SDL_SetError("Metal is not supported.");
        প্রত্যাগম রিক্ত;
    }
}

#যদি defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ধ্রুব বর্ণ *SDL_GetCSSCursorName(SDL_SystemCursor id, ধ্রুব বর্ণ **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    বিকল্প (id) {
    পক্ষ SDL_SYSTEM_CURSOR_DEFAULT:
        প্রত্যাগম "default";

    পক্ষ SDL_SYSTEM_CURSOR_TEXT:
        প্রত্যাগম "text";

    পক্ষ SDL_SYSTEM_CURSOR_WAIT:
        প্রত্যাগম "wait";

    পক্ষ SDL_SYSTEM_CURSOR_CROSSHAIR:
        প্রত্যাগম "crosshair";

    পক্ষ SDL_SYSTEM_CURSOR_PROGRESS:
        প্রত্যাগম "progress";

    পক্ষ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        যদি (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        প্রত্যাগম "nwse-resize";

    পক্ষ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        যদি (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        প্রত্যাগম "nesw-resize";

    পক্ষ SDL_SYSTEM_CURSOR_EW_RESIZE:
        যদি (fallback_name) {
            *fallback_name = "col-resize";
        }
        প্রত্যাগম "ew-resize";

    পক্ষ SDL_SYSTEM_CURSOR_NS_RESIZE:
        যদি (fallback_name) {
            *fallback_name = "row-resize";
        }
        প্রত্যাগম "ns-resize";

    পক্ষ SDL_SYSTEM_CURSOR_MOVE:
        যদি (fallback_name) {
            *fallback_name = "all-scroll";
        }
        প্রত্যাগম "move";

    পক্ষ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        প্রত্যাগম "not-allowed";

    পক্ষ SDL_SYSTEM_CURSOR_POINTER:
        প্রত্যাগম "pointer";

    পক্ষ SDL_SYSTEM_CURSOR_NW_RESIZE:
        প্রত্যাগম "nw-resize";

    পক্ষ SDL_SYSTEM_CURSOR_N_RESIZE:
        প্রত্যাগম "n-resize";

    পক্ষ SDL_SYSTEM_CURSOR_NE_RESIZE:
        প্রত্যাগম "ne-resize";

    পক্ষ SDL_SYSTEM_CURSOR_E_RESIZE:
        প্রত্যাগম "e-resize";

    পক্ষ SDL_SYSTEM_CURSOR_SE_RESIZE:
        প্রত্যাগম "se-resize";

    পক্ষ SDL_SYSTEM_CURSOR_S_RESIZE:
        প্রত্যাগম "s-resize";

    পক্ষ SDL_SYSTEM_CURSOR_SW_RESIZE:
        প্রত্যাগম "sw-resize";

    পক্ষ SDL_SYSTEM_CURSOR_W_RESIZE:
        প্রত্যাগম "w-resize";

    পক্ষ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        প্রত্যাগম "context-menu";

    পক্ষ SDL_SYSTEM_CURSOR_HELP:
        প্রত্যাগম "help";

    পক্ষ SDL_SYSTEM_CURSOR_CELL:
        প্রত্যাগম "cell";

    পক্ষ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        প্রত্যাগম "vertical-text";

    পক্ষ SDL_SYSTEM_CURSOR_ALIAS:
        প্রত্যাগম "alias";

    পক্ষ SDL_SYSTEM_CURSOR_COPY:
        প্রত্যাগম "copy";

    পক্ষ SDL_SYSTEM_CURSOR_NO_DROP:
        প্রত্যাগম "no-drop";

    পক্ষ SDL_SYSTEM_CURSOR_GRAB:
        প্রত্যাগম "grab";

    পক্ষ SDL_SYSTEM_CURSOR_GRABBING:
        প্রত্যাগম "grabbing";

    পক্ষ SDL_SYSTEM_CURSOR_COL_RESIZE:
        প্রত্যাগম "col-resize";

    পক্ষ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        প্রত্যাগম "row-resize";

    পক্ষ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        যদি (fallback_name) {
            *fallback_name = "move";
        }
        প্রত্যাগম "all-scroll";

    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_IN:
        প্রত্যাগম "zoom-in";

    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        প্রত্যাগম "zoom-out";

    স্বভাব:
        প্রত্যাগম "default";
    }
}
#endif

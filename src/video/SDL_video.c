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
    ফাঁকা
};

#define CHECK_WINDOW_MAGIC(window, ফলাফল)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        ফেরত ফলাফল;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        ফেরত ফলাফল;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, ফলাফল)                            \
    CHECK_PARAM(!display) {                                             \
        ফেরত ফলাফল;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, ফলাফল)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        ফেরত ফলাফল;                                                  \
    }

#যদি defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
বাহ্যিক bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
বাহ্যিক bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
বাহ্যিক bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
বাহ্যিক bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
বাহ্যিক শূন্য SDL_UpdateLifecycleObserver(শূন্য);
#endif

স্থির শূন্য SDL_CheckWindowDisplayChanged(SDL_Window *window);
স্থির শূন্য SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
স্থির শূন্য SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
স্থির bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    যদি (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        ফেরত true;
    }
    ফেরত false;
}

স্থির bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    ফেরত !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

স্থির bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    ফেরত !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

স্থির bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    ফেরত !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

স্থির bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    ফেরত !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

স্থির bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    ফেরত !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
স্থির bool syncHint;

স্থির শূন্য SDL_SyncHintWatcher(শূন্য *userdata, ধ্রুবক অক্ষর *name, ধ্রুবক অক্ষর *old_মান, ধ্রুবক অক্ষর *new_মান)
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
        যদি (window->পরবর্তী_sibling) {
            window->পরবর্তী_sibling->পূর্ব_sibling = window->পূর্ব_sibling;
        }
        যদি (window->পূর্ব_sibling) {
            window->পূর্ব_sibling->পরবর্তী_sibling = window->পরবর্তী_sibling;
        } অন্যথা {
            window->parent->first_child = window->পরবর্তী_sibling;
        }

        window->parent = ফাঁকা;
    }

    যদি (parent) {
        window->parent = parent;

        window->পরবর্তী_sibling = parent->first_child;
        যদি (parent->first_child) {
            parent->first_child->পূর্ব_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

প্রকারলেখ কাঠামো
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    শূন্য *pixels;
    পূর্ণসংখ্যা pitch;
    পূর্ণসংখ্যা bytes_per_pixel;
} SDL_Window_Texture_তথ্য;

স্থির Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#যদি (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    যদি (_this->GL_CreateContext) {
        ফেরত SDL_WINDOW_OPENGL;
    }
#endif
#যদি defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    যদি (_this->Metal_CreateView) {
        ফেরত SDL_WINDOW_METAL;
    }
#endif
#যদি defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    যদি (SDL_strcmp(_this->name, "openvr") == 0) {
        ফেরত SDL_WINDOW_OPENGL;
    }
#endif
    ফেরত 0;
}

স্থির bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, শূন্য **pixels, পূর্ণসংখ্যা *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_Window_Texture_তথ্য *তথ্য = (SDL_Window_Texture_তথ্য *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ফাঁকা);
    ধ্রুবক bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    পূর্ণসংখ্যা i;
    পূর্ণসংখ্যা w, h;
    ধ্রুবক SDL_PixelFormat *texture_formats;

    SDL_Get_Window_আকার_In_Pixels(window, &w, &h);

    যদি (!তথ্য) {
        SDL_Renderer *renderer = ফাঁকা;
        ধ্রুবক অক্ষর *render_driver = ফাঁকা;

        // See if there's a render driver being requested
        ধ্রুবক অক্ষর *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
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
            render_driver = ফাঁকা;
        }

        অক্ষর *render_driver_copy = ফাঁকা;
        যদি (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            যদি (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                অক্ষর *পূর্ব = render_driver_copy;
                অক্ষর *ptr = পূর্ব;
                যখন ((ptr = SDL_strchr(ptr, ',')) != ফাঁকা) {
                    *ptr = '\0';
                    ধ্রুবক bool is_sw = (SDL_strcasecmp(পূর্ব, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    যদি (is_sw) {
                        SDL_memset(পূর্ব, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = পূর্ব;
                    } অন্যথা {
                        ptr++;
                        পূর্ব = ptr;
                    }
                }

                যদি (SDL_strcasecmp(পূর্ব, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(পূর্ব, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        যদি (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            যদি (!renderer) {
                // The error for this specific renderer has already been set
                ফেরত false;
            }
        } অন্যথা {
            SDL_assert(render_driver_copy == ফাঁকা);
            ধ্রুবক পূর্ণসংখ্যা যোগ = SDL_Get_অঙ্ক_Render_Drivers();
            জন্য (i = 0; i < যোগ; ++i) {
                ধ্রুবক অক্ষর *name = SDL_GetRenderDriver(i);
                যদি (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    যদি (renderer) {
                        বিরতি; // this will work.
                    }
                }
            }
            যদি (!renderer) {
                ফেরত SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ফাঁকা); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        তথ্য = (SDL_Window_Texture_তথ্য *)SDL_calloc(1, আকার(*তথ্য));
        যদি (!তথ্য) {
            SDL_DestroyRenderer(renderer);
            ফেরত false;
        }
        যদি (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, তথ্য)) {
            SDL_DestroyRenderer(renderer);
            ফেরত false;
        }

        তথ্য->renderer = renderer;
    }

    texture_formats = (ধ্রুবক SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(তথ্য->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, ফাঁকা);
    যদি (!texture_formats) {
        ফেরত false;
    }

    // Free any old texture and pixel data
    যদি (তথ্য->texture) {
        SDL_DestroyTexture(তথ্য->texture);
        তথ্য->texture = ফাঁকা;
    }
    SDL_free(তথ্য->pixels);
    তথ্য->pixels = ফাঁকা;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    জন্য (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        যদি (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            বিরতি;
        }
    }

    তথ্য->texture = SDL_CreateTexture(তথ্য->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    যদি (!তথ্য->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        ফেরত false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(তথ্য->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    তথ্য->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    তথ্য->pitch = (((w * তথ্য->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ধ্রুবক size_t allocsize = (size_t)h * তথ্য->pitch;
        তথ্য->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        যদি (!তথ্য->pixels) {
            ফেরত false;
        }
    }

    *pixels = তথ্য->pixels;
    *pitch = তথ্য->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(তথ্য->renderer, ফাঁকা);

    ফেরত true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা vsync)
{
    SDL_Window_Texture_তথ্য *তথ্য;

    তথ্য = (SDL_Window_Texture_তথ্য *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ফাঁকা);
    যদি (!তথ্য) {
        ফেরত false;
    }
    যদি (!তথ্য->renderer) {
        ফেরত false;
    }
    ফেরত SDL_SetRenderVSync(তথ্য->renderer, vsync);
}

স্থির bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *vsync)
{
    SDL_Window_Texture_তথ্য *তথ্য;

    তথ্য = (SDL_Window_Texture_তথ্য *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ফাঁকা);
    যদি (!তথ্য) {
        ফেরত false;
    }
    যদি (!তথ্য->renderer) {
        ফেরত false;
    }
    ফেরত SDL_GetRenderVSync(তথ্য->renderer, vsync);
}

স্থির bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects, পূর্ণসংখ্যা numrects)
{
    SDL_Window_Texture_তথ্য *তথ্য;
    SDL_Rect rect;
    শূন্য *src;
    পূর্ণসংখ্যা w, h;

    SDL_Get_Window_আকার_In_Pixels(window, &w, &h);

    তথ্য = (SDL_Window_Texture_তথ্য *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ফাঁকা);
    যদি (!তথ্য || !তথ্য->texture) {
        ফেরত SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    যদি (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (শূন্য *)((Uint8 *)তথ্য->pixels +
                       rect.y * তথ্য->pitch +
                       rect.x * তথ্য->bytes_per_pixel);
        যদি (!SDL_UpdateTexture(তথ্য->texture, &rect, src, তথ্য->pitch)) {
            ফেরত false;
        }

        যদি (!SDL_RenderTexture(তথ্য->renderer, তথ্য->texture, ফাঁকা, ফাঁকা)) {
            ফেরত false;
        }

        SDL_RenderPresent(তথ্য->renderer);
    }
    ফেরত true;
}

স্থির শূন্য SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    যদি (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_Window_Texture_তথ্য *তথ্য = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ফাঁকা);

        যদি (তথ্য->texture) {
            SDL_DestroyTexture(তথ্য->texture);
        }
        যদি (তথ্য->renderer) {
            SDL_DestroyRenderer(তথ্য->renderer);
        }
        SDL_free(তথ্য->pixels);
        SDL_free(তথ্য);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

স্থির SDL_VideoDevice *_this = ফাঁকা;
স্থির SDL_AtomicInt SDL_messagebox_গুনতি;

স্থির পূর্ণসংখ্যা SDLCALL cmpmodes(ধ্রুবক শূন্য *A, ধ্রুবক শূন্য *B)
{
    ধ্রুবক SDL_DisplayMode *a = (ধ্রুবক SDL_DisplayMode *)A;
    ধ্রুবক SDL_DisplayMode *b = (ধ্রুবক SDL_DisplayMode *)B;
    পূর্ণসংখ্যা a_refresh_rate = (পূর্ণসংখ্যা)(a->refresh_rate * 100);
    পূর্ণসংখ্যা b_refresh_rate = (পূর্ণসংখ্যা)(b->refresh_rate * 100);
    পূর্ণসংখ্যা a_pixel_density = (পূর্ণসংখ্যা)(a->pixel_density * 100);
    পূর্ণসংখ্যা b_pixel_density = (পূর্ণসংখ্যা)(b->pixel_density * 100);

    যদি (a->w != b->w) {
        ফেরত b->w - a->w;
    } অন্যথা যদি (a->h != b->h) {
        ফেরত b->h - a->h;
    } অন্যথা যদি (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        ফেরত SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } অন্যথা যদি (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        ফেরত SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } অন্যথা যদি (a_refresh_rate != b_refresh_rate) {
        ফেরত b_refresh_rate - a_refresh_rate;
    } অন্যথা যদি (a_pixel_density != b_pixel_density) {
        ফেরত a_pixel_density - b_pixel_density;
    }
    ফেরত 0;
}

bool SDL_UninitializedVideo(শূন্য)
{
    ফেরত SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
স্থির ধ্রুবক VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

পূর্ণসংখ্যা SDL_Get_অঙ্ক_Video_Drivers(শূন্য)
{
    স্থির পূর্ণসংখ্যা অঙ্ক_drivers = -1;

    যদি (অঙ্ক_drivers >= 0) {
        ফেরত অঙ্ক_drivers;
    }

    অঙ্ক_drivers = 0;

    // Build a list of unique video drivers.
    জন্য (পূর্ণসংখ্যা i = 0; bootstrap[i] != ফাঁকা; ++i) {
        bool duplicate = false;
        জন্য (পূর্ণসংখ্যা j = 0; j < i; ++j) {
            যদি (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                বিরতি;
            }
        }

        যদি (!duplicate) {
            deduped_bootstrap[অঙ্ক_drivers++] = bootstrap[i];
        }
    }

    ফেরত অঙ্ক_drivers;
}

ধ্রুবক অক্ষর *SDL_GetVideoDriver(পূর্ণসংখ্যা সূচক)
{
    CHECK_PARAM(সূচক < 0 || সূচক >= SDL_Get_অঙ্ক_Video_Drivers()) {
        SDL_InvalidParamError("index");
        ফেরত ফাঁকা;
    }
    ফেরত deduped_bootstrap[সূচক]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ধ্রুবক অক্ষর *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    পূর্ণসংখ্যা i = 0;

    // Check to make sure we don't overwrite '_this'
    যদি (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    যদি (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        যাও pre_driver_error;
    }
    init_events = true;
    যদি (!SDL_InitKeyboard()) {
        যাও pre_driver_error;
    }
    init_keyboard = true;
    যদি (!SDL_PreInitMouse()) {
        যাও pre_driver_error;
    }
    init_mouse = true;
    যদি (!SDL_InitTouch()) {
        যাও pre_driver_error;
    }
    init_touch = true;
    যদি (!SDL_InitPen()) {
        যাও pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ফাঁকা;
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
        ধ্রুবক অক্ষর *driver_attempt = driver_name;
        যখন (driver_attempt && *driver_attempt != 0 && !video) {
            ধ্রুবক অক্ষর *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            জন্য (i = 0; bootstrap[i]; ++i) {
                যদি (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    যদি (video) {
                        বিরতি;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ফাঁকা;
        }
    } অন্যথা {
        জন্য (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            যদি (video) {
                বিরতি;
            }
        }
    }
    যদি (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } অন্যথা {
        যদি (driver_name) {
            SDL_SetError("%s not available", driver_name);
            যাও pre_driver_error;
        }
        SDL_SetError("No available video device");
        যাও pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ফাঁকা;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    যদি (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        ফেরত false;
    }

    // Make sure some displays were added
    যদি (_this->অঙ্ক_displays == 0) {
        SDL_QuitVideo();
        ফেরত SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, ফাঁকা);

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
    ফেরত true;

pre_driver_error:
    SDL_assert(_this == ফাঁকা);
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
    ফেরত false;
}

ধ্রুবক অক্ষর *SDL_GetCurrentVideoDriver(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    ফেরত _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(শূন্য)
{
    ফেরত _this;
}

bool SDL_OnVideoThread(শূন্য)
{
    ফেরত (_this && SDL_GetCurrentThreadID() == _this->thread);
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
        ফেরত _this->system_theme;
    } অন্যথা {
        ফেরত SDL_SYSTEM_THEME_UNKNOWN;
    }
}

শূন্য SDL_UpdateDesktopBounds(শূন্য)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ফাঁকা);
    যদি (displays) {
        জন্য (পূর্ণসংখ্যা i = 0; displays[i]; ++i) {
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
        mode->refresh_rate = (দশমিক)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } অন্যথা {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(ধ্রুবক SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    যদি (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, আকার(display.desktop_mode));
    }
    ফেরত SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(ধ্রুবক SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    পূর্ণসংখ্যা i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(আকার(*new_display));
    যদি (!new_display) {
        ফেরত 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->অঙ্ক_displays + 1) * আকার(*displays));
    যদি (!displays) {
        SDL_free(new_display);
        ফেরত 0;
    }
    _this->displays = displays;
    _this->displays[_this->অঙ্ক_displays++] = new_display;

    id = SDL_Get_পরবর্তী_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    যদি (display->name) {
        new_display->name = SDL_strdup(display->name);
    } অন্যথা {
        অক্ষর name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    যদি (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    জন্য (i = 0; i < new_display->অঙ্ক_fullscreen_modes; ++i) {
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

    ফেরত id;
}

শূন্য SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    জন্য (window = _this->windows; window; window = window->পরবর্তী) {
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
    পূর্ণসংখ্যা display_সূচক = SDL_Get_Display_সূচক(displayID);
    যদি (display_সূচক < 0) {
        ফেরত;
    }

    display = _this->displays[display_সূচক];

    যদি (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = ফাঁকা;
    SDL_free(display->internal);
    display->internal = ফাঁকা;
    SDL_free(display);

    যদি (display_সূচক < (_this->অঙ্ক_displays - 1)) {
        SDL_memmove(&_this->displays[display_সূচক], &_this->displays[display_সূচক + 1], (_this->অঙ্ক_displays - display_সূচক - 1) * আকার(_this->displays[display_সূচক]));
    }
    --_this->অঙ্ক_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(পূর্ণসংখ্যা *গুনতি)
{
    পূর্ণসংখ্যা i;
    SDL_DisplayID *displays;

    যদি (!_this) {
        যদি (গুনতি) {
            *গুনতি = 0;
        }

        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->অঙ্ক_displays + 1) * আকার(*displays));
    যদি (displays) {
        যদি (গুনতি) {
            *গুনতি = _this->অঙ্ক_displays;
        }

        জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } অন্যথা {
        যদি (গুনতি) {
            *গুনতি = 0;
        }
    }
    ফেরত displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    পূর্ণসংখ্যা display_সূচক;

    display_সূচক = SDL_Get_Display_সূচক(displayID);
    যদি (display_সূচক < 0) {
        ফেরত ফাঁকা;
    }
    ফেরত _this->displays[display_সূচক];
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
    ফেরত displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ফেরত SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(শূন্য)
{
    যদি (!_this || _this->অঙ্ক_displays == 0) {
        SDL_UninitializedVideo();
        ফেরত 0;
    }
    ফেরত _this->displays[0]->id;
}

পূর্ণসংখ্যা SDL_Get_Display_সূচক(SDL_DisplayID displayID)
{
    পূর্ণসংখ্যা display_সূচক;

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত -1;
    }

    জন্য (display_সূচক = 0; display_সূচক < _this->অঙ্ক_displays; ++display_সূচক) {
        যদি (displayID == _this->displays[display_সূচক]->id) {
            ফেরত display_সূচক;
        }
    }
    SDL_SetError("Invalid display");
    ফেরত -1;
}

SDL_Display_তথ্য *SDL_Get_Display_Driver_তথ্য(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ফাঁকা);

    ফেরত display->internal;
}

SDL_Display_তথ্য *SDL_Get_Display_Driver_তথ্য_For_Window(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ফেরত SDL_Get_Display_Driver_তথ্য(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    যদি (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    ফেরত display->props;
}

ধ্রুবক অক্ষর *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ফাঁকা);

    ফেরত display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ফেরত SDL_InvalidParamError("rect");
    }

    যদি (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        যদি (_this->GetDisplayBounds(_this, display, rect)) {
            ফেরত true;
        }
    }

    // Assume that the displays are left to right
    যদি (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } অন্যথা {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_সূচক(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    ফেরত true;
}

স্থির পূর্ণসংখ্যা ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ধ্রুবক অক্ষর *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    ফেরত hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        ফেরত SDL_InvalidParamError("rect");
    }

    যদি (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        ফেরত true;
    }

    যদি (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        যদি (_this->GetDisplayUsableBounds(_this, display, rect)) {
            ফেরত true;
        }
    }

    // Oh well, just give the entire display bounds.
    ফেরত SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    যদি (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        ফেরত display->natural_orientation;
    } অন্যথা {
        // Default to landscape if the driver hasn't set it
        ফেরত SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    যদি (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        ফেরত display->current_orientation;
    } অন্যথা {
        // Default to landscape if the driver hasn't set it
        ফেরত SDL_ORIENTATION_LANDSCAPE;
    }
}

শূন্য SDL_SetDisplayContentScale(SDL_VideoDisplay *display, দশমিক scale)
{
    যদি (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        জন্য (window = _this->windows; window; window = window->পরবর্তী) {
            যদি (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

দশমিক SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    ফেরত display->content_scale;
}

শূন্য SDL_SetWindowHDRProperties(SDL_Window *window, ধ্রুবক SDL_HDROutputProperties *HDR, bool send_event)
{
    ধ্রুবক SDL_HDROutputProperties HDR_clamped = {
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

শূন্য SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, ধ্রুবক SDL_HDROutputProperties *HDR)
{
    ধ্রুবক SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ধ্রুবক bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	যদি (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    যদি (changed && !SDL_DriverSendsHDRChanges(_this)) {
        জন্য (SDL_Window *w = display->device->windows; w; w = w->পরবর্তী) {
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
স্থির ধ্রুবক SDL_DisplayMode *SDL_GetFullscreenModeMatch(ধ্রুবক SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    যদি (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        ফেরত ফাঁকা;
    }

    SDL_memcpy(&fullscreen_mode, mode, আকার(fullscreen_mode));
    যদি (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = ফাঁকা;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    যদি (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        যদি (!mode) {
            জন্য (পূর্ণসংখ্যা i = 0; i < display->অঙ্ক_fullscreen_modes; ++i) {
                যদি (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], আকার(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    বিরতি;
                }
            }
        }

        // Search for a mode with the same characteristics
        যদি (!mode) {
            জন্য (পূর্ণসংখ্যা i = 0; i < display->অঙ্ক_fullscreen_modes; ++i) {
                যদি (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    বিরতি;
                }
            }
        }
    }
    ফেরত mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, ধ্রুবক SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    পূর্ণসংখ্যা i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, আকার(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->অঙ্ক_fullscreen_modes;
    জন্য (i = 0; i < nmodes; ++i) {
        যদি (cmpmodes(&new_mode, &modes[i]) == 0) {
            ফেরত false;
        }
    }

    // Go ahead and add the new mode
    যদি (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * আকার(*modes));
        যদি (!modes) {
            ফেরত false;
        }

        যদি (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * আকার(*modes));
            জন্য (i = 0; i < nmodes; ++i) {
                যদি (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->অঙ্ক_fullscreen_modes++], &new_mode, আকার(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->অঙ্ক_fullscreen_modes,
              আকার(SDL_DisplayMode), cmpmodes);

    ফেরত true;
}

শূন্য SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    পূর্ণসংখ্যা i;

    জন্য (i = display->অঙ্ক_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = ফাঁকা;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ফাঁকা;
    display->অঙ্ক_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, পূর্ণসংখ্যা *গুনতি)
{
    পূর্ণসংখ্যা i;
    পূর্ণসংখ্যা অঙ্ক_modes;
    SDL_DisplayMode **ফলাফল;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    যদি (গুনতি) {
        *গুনতি = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ফাঁকা);

    SDL_UpdateFullscreenDisplayModes(display);

    অঙ্ক_modes = display->অঙ্ক_fullscreen_modes;
    ফলাফল = (SDL_DisplayMode **)SDL_malloc((অঙ্ক_modes + 1) * আকার(*ফলাফল) + অঙ্ক_modes * আকার(**ফলাফল));
    যদি (ফলাফল) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)ফলাফল + ((অঙ্ক_modes + 1) * আকার(*ফলাফল)));
        যদি (অঙ্ক_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, অঙ্ক_modes * আকার(*modes));
        }
        জন্য (i = 0; i < অঙ্ক_modes; ++i) {
            ফলাফল[i] = modes++;
        }
        ফলাফল[i] = ফাঁকা;

        যদি (গুনতি) {
            *গুনতি = অঙ্ক_modes;
        }
    } অন্যথা {
        যদি (গুনতি) {
            *গুনতি = 0;
        }
    }
    ফেরত ফলাফল;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, দশমিক refresh_rate, bool include_উপরের_density_modes, SDL_DisplayMode *ফলাফল)
{
    CHECK_PARAM(!ফলাফল) {
        ফেরত SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ধ্রুবক SDL_DisplayMode *mode, *closest = ফাঁকা;
    দশমিক aspect_ratio;
    পূর্ণসংখ্যা i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(ফলাফল);

    CHECK_DISPLAY_MAGIC(display, false);

    যদি (h > 0) {
        aspect_ratio = (দশমিক)w / h;
    } অন্যথা {
        aspect_ratio = 1.0f;
    }

    যদি (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    জন্য (i = 0; i < display->অঙ্ক_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        যদি (w > mode->w) {
            // Out of sorted modes large enough here
            বিরতি;
        }
        যদি (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            চালু;
        }
        যদি (mode->pixel_density > 1.0f && !include_উপরের_density_modes) {
            চালু;
        }
        যদি (closest) {
            দশমিক current_aspect_ratio = (দশমিক)mode->w / mode->h;
            দশমিক closest_aspect_ratio = (দশমিক)closest->w / closest->h;
            যদি (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                চালু;
            }

            যদি (mode->w == closest->w && mode->h == closest->h) {
                যদি (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    চালু;
                }
                যদি (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    চালু;
                }
            }
        }

        closest = mode;
    }
    যদি (!closest) {
        ফেরত SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(ফলাফল, closest);

    ফেরত true;
}

স্থির bool DisplayModeChanged(ধ্রুবক SDL_DisplayMode *old_mode, ধ্রুবক SDL_DisplayMode *new_mode)
{
    ফেরত ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

শূন্য SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, ধ্রুবক SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    যদি (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        ফেরত;
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

ধ্রুবক SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ফাঁকা);

    ফেরত &display->desktop_mode;
}

শূন্য SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, ধ্রুবক SDL_DisplayMode *mode)
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

ধ্রুবক SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ফাঁকা);

    ফেরত display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    যদি (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        ফেরত true;
    }

    যদি (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    যদি (mode == display->current_mode) {
        ফেরত true;
    }
#endif

    // Actually change the display mode
    যদি (_this->SetDisplayMode) {
        bool ফলাফল;

        _this->setting_display_mode = true;
        ফলাফল = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        যদি (!ফলাফল) {
            ফেরত false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    ফেরত true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
স্থির শূন্য SDL_GetClosestPointOnRect(ধ্রুবক SDL_Rect *rect, SDL_Point *point)
{
    ধ্রুবক পূর্ণসংখ্যা ডান = rect->x + rect->w - 1;
    ধ্রুবক পূর্ণসংখ্যা bottom = rect->y + rect->h - 1;

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

স্থির SDL_DisplayID GetDisplayForRect(পূর্ণসংখ্যা x, পূর্ণসংখ্যা y, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h)
{
    পূর্ণসংখ্যা i, dist;
    SDL_DisplayID closest = 0;
    পূর্ণসংখ্যা closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    যদি (_this) {
        জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            যদি (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ফাঁকা)) {
                ফেরত display->id;
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

    ফেরত closest;
}

শূন্য SDL_RelativeToGlobalForWindow(SDL_Window *window, পূর্ণসংখ্যা rel_x, পূর্ণসংখ্যা rel_y, পূর্ণসংখ্যা *abs_x, পূর্ণসংখ্যা *abs_y)
{
    SDL_Window *w;

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        জন্য (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            যদি (!SDL_WINDOW_IS_POPUP(w)) {
                বিরতি;
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

শূন্য SDL_GlobalToRelativeForWindow(SDL_Window *window, পূর্ণসংখ্যা abs_x, পূর্ণসংখ্যা abs_y, পূর্ণসংখ্যা *rel_x, পূর্ণসংখ্যা *rel_y)
{
    SDL_Window *w;

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        জন্য (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            যদি (!SDL_WINDOW_IS_POPUP(w)) {
                বিরতি;
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

SDL_DisplayID SDL_GetDisplayForPoint(ধ্রুবক SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        ফেরত 0;
    }

    ফেরত GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ধ্রুবক SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        ফেরত 0;
    }

    ফেরত GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

স্থির SDL_DisplayID GetDisplayAtOrigin(পূর্ণসংখ্যা x, পূর্ণসংখ্যা y)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < _this->অঙ্ক_displays; ++i) {
        SDL_Rect rect;
        ধ্রুবক SDL_DisplayID cur_id = _this->displays[i]->id;
        যদি (SDL_GetDisplayBounds(cur_id, &rect)) {
            যদি (x == rect.x && y == rect.y) {
                ফেরত cur_id;
            }
        }
    }

    ফেরত 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    পূর্ণসংখ্যা x, y;
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
    ফেরত displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, ফাঁকা);

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
        ধ্রুবক পূর্ণসংখ্যা x = window->last_position_pending ? window->pending.x : window->x;
        ধ্রুবক পূর্ণসংখ্যা y = window->last_position_pending ? window->pending.y : window->y;
        ধ্রুবক পূর্ণসংখ্যা w = window->last_আকার_pending ? window->pending.w : window->w;
        ধ্রুবক পূর্ণসংখ্যা h = window->last_আকার_pending ? window->pending.h : window->h;

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
    ফেরত SDL_GetVideoDisplay(displayID);
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

    ফেরত GetDisplayForWindow(window);
}

স্থির শূন্য SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    যদি (SDL_SendsDisplayChanges(_this)) {
        ফেরত;
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
                পূর্ণসংখ্যা old_area = old_overlap.w * old_overlap.h;
                পূর্ণসংখ্যা new_area = new_overlap.w * new_overlap.h;
                দশমিক new_overlap_ratio = (new_area / ((দশমিক)old_area + new_area));
                যদি (new_overlap_ratio < 0.80) {
                    ফেরত;
                }
            }
        }
    }

    যদি (displayID != window->displayID) {
        পূর্ণসংখ্যা i, display_সূচক;

        // Sanity check our fullscreen windows
        display_সূচক = SDL_Get_Display_সূচক(displayID);
        জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            যদি (display->fullscreen_window == window) {
                যদি (display_সূচক != i) {
                    যদি (display_সূচক < 0) {
                        display_সূচক = i;
                    } অন্যথা {
                        SDL_VideoDisplay *new_display = _this->displays[display_সূচক];

                        // The window was moved to a different display
                        যদি (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = ফাঁকা;
                    }
                }
                বিরতি;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (পূর্ণসংখ্যা)displayID, 0);
    }
}

দশমিক SDL_GetWindowPixelDensity(SDL_Window *window)
{
    পূর্ণসংখ্যা window_w, window_h, pixel_w, pixel_h;
    দশমিক pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    যদি (SDL_Get_Window_আকার(window, &window_w, &window_h) &&
        SDL_Get_Window_আকার_In_Pixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (দশমিক)pixel_w / window_w;
    }
    ফেরত pixel_density;
}

দশমিক SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    ফেরত window->display_scale;
}

স্থির শূন্য SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    দশমিক display_scale;

    যদি (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } অন্যথা {
        ধ্রুবক দশমিক pixel_density = SDL_GetWindowPixelDensity(window);
        ধ্রুবক দশমিক content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    যদি (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ফাঁকা;
    SDL_DisplayMode *mode = ফাঁকা;
    পূর্ণসংখ্যা i;

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
            যাও done;
        }
    } অন্যথা {
        জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
            display = _this->displays[i];
            যদি (display->fullscreen_window == window) {
                বিরতি;
            }
        }
        যদি (!display || i == _this->অঙ্ক_displays) {
            // Already not fullscreen on any display
            display = ফাঁকা;
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
                display->fullscreen_window = ফাঁকা;
            }
            যাও done;
        }
        যদি (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            যদি (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                যদি (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    যাও error;
                }
            } অন্যথা যদি (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    যদি (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, ফাঁকা);
                        যদি (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = ফাঁকা;
                    }
                }
            }

            যদি (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                যাও done;
            }
        }
    }
#endif

    যদি (display) {
        // Restore the video mode on other displays if needed
        জন্য (i = 0; i < _this->অঙ্ক_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            যদি (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, ফাঁকা);
                other->fullscreen_window = ফাঁকা;
            }
        }
    }

    যদি (fullscreen) {
        পূর্ণসংখ্যা mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        যদি (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        যদি (!SDL_SetDisplayModeForDisplay(display, mode)) {
            যাও error;
        }
        যদি (commit) {
            SDL_Fullscreen_ফলাফল ret = SDL_FULLSCREEN_SUCCEEDED;
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
                যাও error;
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

            SDL_SetDisplayModeForDisplay(display, ফাঁকা);
        }
        যদি (commit) {
            SDL_Fullscreen_ফলাফল ret = SDL_FULLSCREEN_SUCCEEDED;
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
                যাও error;
            }
        }

        যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            যদি (display) {
                display->fullscreen_window = ফাঁকা;
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
    ফেরত true;

error:
    যদি (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    ফেরত false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, ধ্রুবক SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (mode) {
        যদি (!SDL_GetFullscreenModeMatch(mode)) {
            ফেরত SDL_SetError("Invalid fullscreen display mode");
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

    ফেরত true;
}

ধ্রুবক SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ফাঁকা);
    CHECK_WINDOW_NOT_POPUP(window, ফাঁকা);

    যদি (window->flags & SDL_WINDOW_FULLSCREEN) {
        ফেরত SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } অন্যথা {
        ফেরত SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

শূন্য *SDL_GetWindowICCProfile(SDL_Window *window, size_t *আকার_2)
{
    যদি (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        ফেরত ফাঁকা;
    }
    ফেরত _this->GetWindowICCProfile(_this, window, আকার_2);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    ধ্রুবক SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    যদি (mode) {
        ফেরত mode->format;
    } অন্যথা {
        ফেরত SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_উপরের_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_শীর্ষ | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

স্থির SDL_INLINE bool IsAcceptingDragAndDrop(শূন্য)
{
    যদি (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        ফেরত true;
    }
    ফেরত false;
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
        ধ্রুবক bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        জন্য (window = _this->windows; window; window = window->পরবর্তী) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(পূর্ণসংখ্যা *গুনতি)
{
    যদি (গুনতি) {
        *গুনতি = 0;
    }

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }

    SDL_Window *window;
    পূর্ণসংখ্যা অঙ্ক_added = 0;
    পূর্ণসংখ্যা অঙ্ক_windows = 0;
    জন্য (window = _this->windows; window; window = window->পরবর্তী) {
        ++অঙ্ক_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((অঙ্ক_windows + 1) * আকার(*windows));
    যদি (!windows) {
        ফেরত ফাঁকা;
    }

    জন্য (window = _this->windows; window; window = window->পরবর্তী) {
        windows[অঙ্ক_added++] = window;
        যদি (অঙ্ক_added == অঙ্ক_windows) {
            // Race condition? Multi-threading not supported, ignore it
            বিরতি;
        }
    }
    windows[অঙ্ক_added] = ফাঁকা;

    যদি (গুনতি) {
        *গুনতি = অঙ্ক_added;
    }
    ফেরত windows;
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

স্থির bool SDL_ContextNotSupported(ধ্রুবক অক্ষর *name)
{
    ফেরত SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

স্থির bool SDL_DllNotSupported(ধ্রুবক অক্ষর *name)
{
    ফেরত SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

স্থির কাঠামো {
    ধ্রুবক অক্ষর *property_name;
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

    জন্য (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
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
    ফেরত flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    ধ্রুবক অক্ষর *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, ফাঁকা);
    পূর্ণসংখ্যা x = (পূর্ণসংখ্যা)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_X_সংখ্যা, SDL_WINDOWPOS_UNDEFINED);
    পূর্ণসংখ্যা y = (পূর্ণসংখ্যা)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_Y_সংখ্যা, SDL_WINDOWPOS_UNDEFINED);
    পূর্ণসংখ্যা w = (পূর্ণসংখ্যা)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_সংখ্যা, 0);
    পূর্ণসংখ্যা h = (পূর্ণসংখ্যা)SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_সংখ্যা, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, ফাঁকা);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    যদি (!_this) {
        // Initialize the video system if needed
        যদি (!SDL_Init(SDL_INIT_VIDEO)) {
            ফেরত ফাঁকা;
        }

        // Make clang-tidy happy
        যদি (!_this) {
            ফেরত ফাঁকা;
        }
    }

    যদি ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        ফেরত ফাঁকা;
    }

    যদি ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        যদি (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            ফেরত ফাঁকা;
        }

        // Tooltip and popup menu window must specify a parent window
        যদি (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            ফেরত ফাঁকা;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    যদি (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned পূর্ণসংখ্যা)type_flags);
        ফেরত ফাঁকা;
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
        যদি (displayID == 0 || SDL_Get_Display_সূচক(displayID) < 0) {
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
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned পূর্ণসংখ্যা)graphics_flags);
        ফেরত ফাঁকা;
    }

    // Some platforms have certain graphics backends enabled by default
    যদি (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    যদি (flags & SDL_WINDOW_OPENGL) {
        যদি (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            ফেরত ফাঁকা;
        }
        যদি (!SDL_GL_LoadLibrary(ফাঁকা)) {
            ফেরত ফাঁকা;
        }
    }

    যদি (flags & SDL_WINDOW_VULKAN) {
        যদি (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            ফেরত ফাঁকা;
        }
        যদি (!SDL_Vulkan_LoadLibrary(ফাঁকা)) {
            ফেরত ফাঁকা;
        }
    }

    যদি (flags & SDL_WINDOW_METAL) {
        যদি (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            ফেরত ফাঁকা;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, আকার(*window));
    যদি (!window) {
        ফেরত ফাঁকা;
    }
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, true);
    window->id = SDL_Get_পরবর্তী_Object_ID();
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
    window->পরবর্তী = _this->windows;
    window->is_destroying = false;
    window->displayID = GetDisplayForWindow(window);
    window->external_graphics_context = external_graphics_context;
    window->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    যদি (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    যদি (_this->windows) {
        _this->windows->পূর্ব = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    যদি (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_ঠেলো_Error();
        SDL_DestroyWindow(window);
        SDL_বের_করো_Error();
        ফেরত ফাঁকা;
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
    SDL_Check_Window_Pixel_আকার_Changed(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    ফেরত window;
}

SDL_Window *SDL_CreateWindow(ধ্রুবক অক্ষর *title, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, SDL_WindowFlags flags)
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
    ফেরত window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, পূর্ণসংখ্যা offset_x, পূর্ণসংখ্যা offset_y, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    যদি (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        ফেরত ফাঁকা;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_X_সংখ্যা, offset_x);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_Y_সংখ্যা, offset_y);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_সংখ্যা, w);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_সংখ্যা, h);
    SDL_Set_সংখ্যা_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_সংখ্যা, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    ফেরত window;
}

স্থির bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    যদি (!_this->ReconfigureWindow) {
        ফেরত false;
    }

    ধ্রুবক SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    যদি (graphics_flags & (graphics_flags - 1)) {
        ফেরত SDL_SetError("Conflicting window flags specified");
    }

    যদি ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ফেরত SDL_ContextNotSupported("OpenGL");
    }
    যদি ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ফেরত SDL_ContextNotSupported("Vulkan");
    }
    যদি ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ফেরত SDL_ContextNotSupported("Metal");
    }

    যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        যদি (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            ফেরত false;
        }
    } অন্যথা {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        যদি (!_this->ReconfigureWindow(_this, window, 0)) {
            ফেরত false;
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
        loaded_opengl = SDL_GL_LoadLibrary(ফাঁকা);
        যদি (!loaded_opengl) {
            ফেরত false;
        }
    } অন্যথা যদি (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(ফাঁকা);
        যদি (!loaded_vulkan) {
            ফেরত false;
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

        ফেরত false;
    }

    window->flags |= graphics_flags;

    ফেরত true;
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
        ফেরত SDL_SetError("Conflicting window flags specified");
    }

    যদি ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        ফেরত SDL_ContextNotSupported("OpenGL");
    }
    যদি ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        ফেরত SDL_ContextNotSupported("Vulkan");
    }
    যদি ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        ফেরত SDL_ContextNotSupported("Metal");
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
        ধ্রুবক bool restore_on_show = window->restore_on_show;
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
        যদি (!SDL_GL_LoadLibrary(ফাঁকা)) {
            ফেরত false;
        }
        loaded_opengl = true;
    }

    যদি (need_vulkan_load) {
        যদি (!SDL_Vulkan_LoadLibrary(ফাঁকা)) {
            ফেরত false;
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
            ফেরত false;
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

    যদি (_this->Set_Window_Minimum_আকার && (window->min_w || window->min_h)) {
        _this->Set_Window_Minimum_আকার(_this, window);
    }

    যদি (_this->Set_Window_Maximum_আকার && (window->max_w || window->max_h)) {
        _this->Set_Window_Maximum_আকার(_this, window);
    }

    যদি (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    যদি (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    ফেরত true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    যদি (!SDL_ReconfigureWindowInternal(window, flags)) {
        ফেরত SDL_RecreateWindow(window, flags);
    }

    ফেরত true;
}

bool SDL_HasWindows(শূন্য)
{
    ফেরত _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ফেরত window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    যদি (id) {
        জন্য (window = _this->windows; window; window = window->পরবর্তী) {
            যদি (window->id == id) {
                ফেরত window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    ফেরত ফাঁকা;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ফাঁকা);

    ফেরত window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    যদি (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    ফেরত window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    ফেরত window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, ধ্রুবক অক্ষর *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (title == window->title) {
        ফেরত true;
    }
    যদি (!title) {
        title = "";
    }
    যদি (window->title && SDL_strcmp(title, window->title) == 0) {
        ফেরত true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    যদি (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    ফেরত true;
}

ধ্রুবক অক্ষর *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    ফেরত window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        ফেরত SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    যদি (!window->icon) {
        ফেরত false;
    }

    যদি (!_this->SetWindowIcon) {
        ফেরত SDL_Unsupported();
    }

    ফেরত _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    ধ্রুবক পূর্ণসংখ্যা w = window->last_আকার_pending ? window->pending.w : window->windowed.w;
    ধ্রুবক পূর্ণসংখ্যা h = window->last_আকার_pending ? window->pending.h : window->windowed.h;

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
        যদি (displayID == 0 || SDL_Get_Display_সূচক(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        যদি (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            যদি (!SDL_GetDisplayBounds(displayID, &bounds)) {
                ফেরত false;
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
        ধ্রুবক bool ফলাফল = _this->SetWindowPosition(_this, window);
        যদি (ফলাফল) {
            SDL_SyncIfRequired(window);
        }
        ফেরত ফলাফল;
    }

    ফেরত SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, পূর্ণসংখ্যা *x, পূর্ণসংখ্যা *y)
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
        ধ্রুবক bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        যদি (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        যদি (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    ফেরত true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->SetWindowBordered) {
        ফেরত SDL_Unsupported();
    }

    ধ্রুবক bool want = bordered;
    ধ্রুবক bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    যদি (want != have) {
        যদি (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } অন্যথা {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    ফেরত true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->SetWindowResizable) {
        ফেরত SDL_Unsupported();
    }

    ধ্রুবক bool want = resizable;
    ধ্রুবক bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    যদি (want != have) {
        যদি (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } অন্যথা {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    ফেরত true;
}

bool SDL_Set_Window_Always_On_শীর্ষ(SDL_Window *window, bool on_শীর্ষ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->Set_Window_Always_On_শীর্ষ) {
        ফেরত SDL_Unsupported();
    }

    ধ্রুবক bool want = on_শীর্ষ;
    ধ্রুবক bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_শীর্ষ) != 0);
    যদি (want != have) {
        যদি (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_শীর্ষ;
        } অন্যথা {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_শীর্ষ;
        }
        _this->Set_Window_Always_On_শীর্ষ(_this, window, want);
    }

    ফেরত true;
}

bool SDL_Set_Window_আকার(SDL_Window *window, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        ফেরত SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        ফেরত SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    দশমিক new_aspect = w / (দশমিক)h;
    যদি (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (পূর্ণসংখ্যা)SDL_roundf(h * window->max_aspect);
    } অন্যথা যদি (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (পূর্ণসংখ্যা)SDL_roundf(w / window->min_aspect);
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

    window->last_আকার_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    যদি (_this->Set_Window_আকার) {
        _this->Set_Window_আকার(_this, window);
        SDL_SyncIfRequired(window);
    } অন্যথা {
        ফেরত SDL_Unsupported();
    }
    ফেরত true;
}

bool SDL_Get_Window_আকার(SDL_Window *window, পূর্ণসংখ্যা *w, পূর্ণসংখ্যা *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    যদি (w) {
        *w = window->w;
    }
    যদি (h) {
        *h = window->h;
    }
    ফেরত true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, দশমিক min_aspect, দশমিক max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    যদি (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    পূর্ণসংখ্যা w = window->last_আকার_pending ? window->pending.w : window->floating.w;
    পূর্ণসংখ্যা h = window->last_আকার_pending ? window->pending.h : window->floating.h;
    ফেরত SDL_Set_Window_আকার(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, দশমিক *min_aspect, দশমিক *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    যদি (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    ফেরত true;
}

bool SDL_Get_Window_Borders_আকার(SDL_Window *window, পূর্ণসংখ্যা *শীর্ষ, পূর্ণসংখ্যা *বাম, পূর্ণসংখ্যা *bottom, পূর্ণসংখ্যা *ডান)
{
    পূর্ণসংখ্যা dummy = 0;

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

    যদি (!_this->Get_Window_Borders_আকার) {
        ফেরত SDL_Unsupported();
    }

    ফেরত _this->Get_Window_Borders_আকার(_this, window, শীর্ষ, বাম, bottom, ডান);
}

bool SDL_Get_Window_আকার_In_Pixels(SDL_Window *window, পূর্ণসংখ্যা *w, পূর্ণসংখ্যা *h)
{
    পূর্ণসংখ্যা filter;

    CHECK_WINDOW_MAGIC(window, false);

    যদি (!w) {
        w = &filter;
    }

    যদি (!h) {
        h = &filter;
    }

    যদি (_this->Get_Window_আকার_In_Pixels) {
        _this->Get_Window_আকার_In_Pixels(_this, window, w, h);
    } অন্যথা {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        ধ্রুবক SDL_DisplayMode *mode;

        SDL_Get_Window_আকার(window, w, h);

        যদি ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } অন্যথা {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        যদি (mode) {
            *w = (পূর্ণসংখ্যা)SDL_ceilf(*w * mode->pixel_density);
            *h = (পূর্ণসংখ্যা)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    ফেরত true;
}

bool SDL_Set_Window_Minimum_আকার(SDL_Window *window, পূর্ণসংখ্যা min_w, পূর্ণসংখ্যা min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        ফেরত SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        ফেরত SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        ফেরত SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    যদি (_this->Set_Window_Minimum_আকার) {
        _this->Set_Window_Minimum_আকার(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    পূর্ণসংখ্যা w = window->last_আকার_pending ? window->pending.w : window->floating.w;
    পূর্ণসংখ্যা h = window->last_আকার_pending ? window->pending.h : window->floating.h;
    ফেরত SDL_Set_Window_আকার(window, w, h);
}

bool SDL_Get_Window_Minimum_আকার(SDL_Window *window, পূর্ণসংখ্যা *min_w, পূর্ণসংখ্যা *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    যদি (min_w) {
        *min_w = window->min_w;
    }
    যদি (min_h) {
        *min_h = window->min_h;
    }
    ফেরত true;
}

bool SDL_Set_Window_Maximum_আকার(SDL_Window *window, পূর্ণসংখ্যা max_w, পূর্ণসংখ্যা max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        ফেরত SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        ফেরত SDL_InvalidParamError("max_h");
    }

    যদি ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        ফেরত SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    যদি (_this->Set_Window_Maximum_আকার) {
        _this->Set_Window_Maximum_আকার(_this, window);
    }

    // Ensure that window is not larger than maximal size
    পূর্ণসংখ্যা w = window->last_আকার_pending ? window->pending.w : window->floating.w;
    পূর্ণসংখ্যা h = window->last_আকার_pending ? window->pending.h : window->floating.h;
    ফেরত SDL_Set_Window_আকার(window, w, h);
}

bool SDL_Get_Window_Maximum_আকার(SDL_Window *window, পূর্ণসংখ্যা *max_w, পূর্ণসংখ্যা *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    যদি (max_w) {
        *max_w = window->max_w;
    }
    যদি (max_h) {
        *max_h = window->max_h;
    }
    ফেরত true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!(window->flags & SDL_WINDOW_HIDDEN)) {
        ফেরত true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    যদি (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        ফেরত true;
    }

    যদি (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } অন্যথা {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    জন্য (child = window->first_child; child; child = child->পরবর্তী_sibling) {
        যদি (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            বিরতি;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    ফেরত true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        ফেরত true;
    }

    // Hide all child windows
    জন্য (child = window->first_child; child; child = child->পরবর্তী_sibling) {
        যদি (child->flags & SDL_WINDOW_HIDDEN) {
            বিরতি;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ধ্রুবক SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    যদি (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } অন্যথা {
        SDL_SetMouseFocus(ফাঁকা);
        SDL_SetKeyboardFocus(ফাঁকা);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    ফেরত true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        ফেরত true;
    }
    যদি (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    ফেরত true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->MaximizeWindow) {
        ফেরত SDL_Unsupported();
    }

    যদি (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        ফেরত SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        ফেরত true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ফেরত true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->MinimizeWindow) {
        ফেরত SDL_Unsupported();
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        ফেরত true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    ফেরত true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->RestoreWindow) {
        ফেরত SDL_Unsupported();
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        ফেরত true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    ফেরত true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool ফলাফল;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        যদি (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } অন্যথা {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        ফেরত true;
    }

    যদি (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    ফলাফল = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    যদি (!fullscreen || !ফলাফল) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    যদি (ফলাফল) {
        SDL_SyncIfRequired(window);
    }

    ফেরত ফলাফল;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (_this->SyncWindow) {
        ফেরত _this->SyncWindow(_this, window);
    } অন্যথা {
        ফেরত true;
    }
}

স্থির bool ShouldAttemptTextureFramebuffer(শূন্য)
{
    ধ্রুবক অক্ষর *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    যদি (!_this->CreateWindowFramebuffer) {
        ফেরত true;
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
    ফেরত attempt_texture_framebuffer;
}

স্থির SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    শূন্য *pixels = ফাঁকা;
    পূর্ণসংখ্যা pitch = 0;
    bool created_framebuffer = false;
    পূর্ণসংখ্যা w, h;

    SDL_Get_Window_আকার_In_Pixels(window, &w, &h);

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
            ফেরত ফাঁকা;
        }

        যদি (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            ফেরত ফাঁকা;
        }
    }

    যদি (window->surface) {
        // We may have gone recursive and already created the surface
        ফেরত window->surface;
    }

    ফেরত SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ফেরত window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ফাঁকা);

    যদি (!window->surface_valid) {
        যদি (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = ফাঁকা;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        যদি (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    ফেরত window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, পূর্ণসংখ্যা vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowFramebufferVSync) {
        ফেরত SDL_Unsupported();
    }
    ফেরত _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, পূর্ণসংখ্যা *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->GetWindowFramebufferVSync) {
        ফেরত SDL_Unsupported();
    }
    ফেরত _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_Get_Window_আকার_In_Pixels(window, &full_rect.w, &full_rect.h);

    ফেরত SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, ধ্রুবক SDL_Rect *rects,
                                 পূর্ণসংখ্যা numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!window->surface_valid) {
        ফেরত SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    ফেরত _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = ফাঁকা;
        window->surface_valid = false;
    }

    যদি (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        যদি (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    ফেরত true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, দশমিক opacity)
{
    bool ফলাফল;

    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowOpacity) {
        ফেরত SDL_Unsupported();
    }

    যদি (opacity < 0.0f) {
        opacity = 0.0f;
    } অন্যথা যদি (opacity > 1.0f) {
        opacity = 1.0f;
    }

    ফলাফল = _this->SetWindowOpacity(_this, window, opacity);
    যদি (ফলাফল) {
        window->opacity = opacity;
    }

    ফেরত ফলাফল;
}

দশমিক SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    ফেরত window->opacity;
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
        ফেরত SDL_SetError("Cannot set the parent of a window to itself.");
    }

    যদি (!_this->SetWindowParent) {
        ফেরত SDL_Unsupported();
    }

    যদি (window->flags & SDL_WINDOW_MODAL) {
        ফেরত SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    যদি (window->parent == parent) {
        ফেরত true;
    }

    ধ্রুবক bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : ফাঁকা);

    ফেরত ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (!_this->SetWindowModal) {
        ফেরত SDL_Unsupported();
    }

    যদি (modal) {
        যদি (!window->parent) {
            ফেরত SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } অন্যথা যদি (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } অন্যথা {
        ফেরত true; // Already not modal, so nothing to do.
    }

    যদি (window->flags & SDL_WINDOW_HIDDEN) {
        ফেরত true;
    }

    ফেরত _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_প্রবেশ_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    যখন (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        যদি (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_প্রবেশ_FOCUS);
        }
    }

    *new_focus = focus;
    ফেরত set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    জন্য (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    জন্য (w = current_focus; w != toplevel_parent; w = w->parent) {
        যদি (w == window) {
            found_higher_focus = true;
            বিরতি;
        }
    }

    ফেরত !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    ধ্রুবক bool want = (focusable != false); // normalize the flag.
    ধ্রুবক bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    যদি ((want != have) && (_this->SetWindowFocusable)) {
        যদি (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } অন্যথা {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        যদি (!_this->SetWindowFocusable(_this, window, want)) {
            ফেরত false;
        }
    }

    ফেরত true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    ধ্রুবক bool want = (fill != false); // normalize the flag.
    ধ্রুবক bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    যদি ((want != have) && (_this->SetWindowFillDocument)) {
        যদি (!_this->SetWindowFillDocument(_this, window, want)) {
            ফেরত false;
        } অন্যথা যদি (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } অন্যথা {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    ফেরত true;
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
        _this->grabbed_window = ফাঁকা; // ungrabbing input.
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
        _this->grabbed_window = ফাঁকা;
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
        ফেরত true;
    }

    যদি (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ফেরত true;
    }
    যদি (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } অন্যথা {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    যদি (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        ফেরত false;
    }
    ফেরত true;
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
        ফেরত true;
    }

    যদি (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ফেরত true;
    }
    যদি (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } অন্যথা {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    যদি (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        ফেরত false;
    }
    ফেরত true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ফেরত window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    ফেরত window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(শূন্য)
{
    যদি (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        ফেরত _this->grabbed_window;
    } অন্যথা {
        ফেরত ফাঁকা;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, ধ্রুবক SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowMouseRect) {
        ফেরত SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    যদি (!rect) {
        rect = &zero;
    }

    যদি (SDL_memcmp(&window->mouse_rect, rect, আকার(*rect)) == 0) {
        ফেরত true;
    }
    SDL_memcpy(&window->mouse_rect, rect, আকার(*rect));

    ফেরত _this->SetWindowMouseRect(_this, window);
}

ধ্রুবক SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ফাঁকা);

    যদি (SDL_RectEmpty(&window->mouse_rect)) {
        ফেরত ফাঁকা;
    } অন্যথা {
        ফেরত &window->mouse_rect;
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
        ফেরত true;
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
        ফেরত false;
    }
    ফেরত true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        ফেরত true;
    } অন্যথা {
        ফেরত false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (_this->FlashWindow) {
        ফেরত _this->FlashWindow(_this, window, operation);
    }

    ফেরত SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        ফেরত SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    যদি (_this->ApplyWindowProgress) {
        যদি (!_this->ApplyWindowProgress(_this, window)) {
            ফেরত false;
        }
    }

    ফেরত true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    ফেরত window->progress_state;
}

bool SDL_Set_Window_Progress_মান(SDL_Window *window, দশমিক মান)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    মান = SDL_clamp(মান, 0.0f, 1.f);

    window->progress_মান = মান;

    যদি (_this->ApplyWindowProgress) {
        যদি (!_this->ApplyWindowProgress(_this, window)) {
            ফেরত false;
        }
    }

    ফেরত true;
}

দশমিক SDL_Get_Window_Progress_মান(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    ফেরত window->progress_মান;
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
        ধ্রুবক bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        যদি (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_উপরের_density_modes = false;

            যদি (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_উপরের_density_modes = true;
            }
            ধ্রুবক bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
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

    SDL_Check_Window_Pixel_আকার_Changed(window);
}

শূন্য SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

শূন্য SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_Check_Window_Pixel_আকার_Changed(window);
    SDL_CheckWindowSafeAreaChanged(window);

    যদি ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, ফাঁকা);
        যদি (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

শূন্য SDL_Check_Window_Pixel_আকার_Changed(SDL_Window *window)
{
    পূর্ণসংখ্যা pixel_w = 0, pixel_h = 0;

    SDL_Get_Window_আকার_In_Pixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_আকার_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

শূন্য SDL_On_Window_Pixel_আকার_Changed(SDL_Window *window)
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
    যদি (SDL_memcmp(&rect, &window->safe_rect, আকার(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

শূন্য SDL_SetWindowSafeAreaInsets(SDL_Window *window, পূর্ণসংখ্যা বাম, পূর্ণসংখ্যা ডান, পূর্ণসংখ্যা শীর্ষ, পূর্ণসংখ্যা bottom)
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
    ফেরত true;
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
    ধ্রুবক অক্ষর *hint;

    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        ফেরত false;
    }

#যদি defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    যদি (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        যদি (Cocoa_IsShowingModalDialog(window)) {
            ফেরত false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } অন্যথা যদি (Cocoa_IsWindowInFullscreenSpace(window)) {
            ফেরত false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        বাহ্যিক bool Android_JNI_ShouldMinimizeOnFocusLoss(শূন্য);
        যদি (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            ফেরত false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    যদি (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        যদি (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            ফেরত true;
        } অন্যথা {
            ফেরত false;
        }
    }
    ফেরত SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
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
        যখন (focus->parent) {
            focus = focus->parent;
        }
    }

    ফেরত focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->অঙ্ক_renderers + 1) * আকার(*renderers));
    যদি (!renderers) {
        ফেরত false;
    }

    window->renderers = renderers;
    window->renderers[window->অঙ্ক_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    ফেরত true;
}

শূন্য SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < window->অঙ্ক_renderers; ++i) {
        যদি (window->renderers[i] == renderer) {
            যদি (i < (window->অঙ্ক_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->অঙ্ক_renderers - i - 1) * আকার(window->renderers[i]));
            }
            --window->অঙ্ক_renderers;
            বিরতি;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    যদি (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, ফাঁকা) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

শূন্য SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    যখন (window->first_child) {
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
    জন্য (পূর্ণসংখ্যা i = 0; i < _this->অঙ্ক_displays; ++i) {
        যদি (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = ফাঁকা;
        }
    }

    // Make sure this window no longer has focus
    যদি (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(ফাঁকা);
    }
    যদি ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    যদি (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(ফাঁকা);
    }

    // Make no context current if this is the current context window
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        যদি (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, ফাঁকা);
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
        _this->grabbed_window = ফাঁকা; // ungrabbing input.
    }

    যদি (_this->current_glwin == window) {
        _this->current_glwin = ফাঁকা;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, ফাঁকা);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, ফাঁকা);

    // Unlink the window from the global window list
    যদি (window->পরবর্তী) {
        window->পরবর্তী->পূর্ব = window->পূর্ব;
    }
    যদি (window->পূর্ব) {
        window->পূর্ব->পরবর্তী = window->পরবর্তী;
    } অন্যথা {
        _this->windows = window->পরবর্তী;
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
        ফেরত true;
    }
    ফেরত !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(শূন্য)
{
    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }
    যদি (!_this->suspend_screensaver) {
        ফেরত true;
    }
    _this->suspend_screensaver = false;
    যদি (_this->SuspendScreenSaver) {
        ফেরত _this->SuspendScreenSaver(_this);
    }

    ফেরত SDL_Unsupported();
}

bool SDL_DisableScreenSaver(শূন্য)
{
    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }
    যদি (_this->suspend_screensaver) {
        ফেরত true;
    }
    _this->suspend_screensaver = true;
    যদি (_this->SuspendScreenSaver) {
        ফেরত _this->SuspendScreenSaver(_this);
    }

    ফেরত SDL_Unsupported();
}

শূন্য SDL_QuitVideo(শূন্য)
{
    পূর্ণসংখ্যা i;

    যদি (!_this) {
        ফেরত;
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
    যখন (_this->windows) {
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

    জন্য (i = _this->অঙ্ক_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->অঙ্ক_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ফাঁকা;

    SDL_Cancel_Clipboard_তথ্য(0);

    যদি (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = ফাঁকা;
    }
    _this->মুক্ত(_this);
    _this = ফাঁকা;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(ধ্রুবক অক্ষর *path)
{
    bool ফলাফল;

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }
    যদি (_this->gl_config.driver_loaded) {
        যদি (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            ফেরত SDL_SetError("OpenGL library already loaded");
        }
        ফলাফল = true;
    } অন্যথা {
        যদি (!_this->GL_LoadLibrary) {
            ফেরত SDL_DllNotSupported("OpenGL");
        }
        ফলাফল = _this->GL_LoadLibrary(_this, path);
    }
    যদি (ফলাফল) {
        ++_this->gl_config.driver_loaded;
    } অন্যথা {
        যদি (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    ফেরত ফলাফল;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(ধ্রুবক অক্ষর *proc)
{
    SDL_FunctionPointer func;

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    func = ফাঁকা;
    যদি (_this->GL_GetProcAddress) {
        যদি (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } অন্যথা {
            SDL_SetError("No GL driver has been loaded");
        }
    } অন্যথা {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    ফেরত func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(ধ্রুবক অক্ষর *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    func = ফাঁকা;

    যদি (_this->egl_তথ্য) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } অন্যথা {
        SDL_SetError("No EGL library has been loaded");
    }

    ফেরত func;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    ফেরত ফাঁকা;
#endif
}

শূন্য SDL_GL_UnloadLibrary(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত;
    }
    যদি (_this->gl_config.driver_loaded > 0) {
        যদি (--_this->gl_config.driver_loaded > 0) {
            ফেরত;
        }
        যদি (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
প্রকারলেখ GLenum (APIENTRY* PFNGLGETERRORPROC) (শূন্য);
প্রকারলেখ শূন্য (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
প্রকারলেখ ধ্রুবক GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
প্রকারলেখ শূন্য (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
প্রকারলেখ ধ্রুবক GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint সূচক);
#endif

স্থির SDL_INLINE bool isAtLeastGL3(ধ্রুবক অক্ষর *verstr)
{
    ফেরত verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ধ্রুবক অক্ষর *extension)
{
#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ধ্রুবক অক্ষর *extensions;
    ধ্রুবক অক্ষর *start;
    ধ্রুবক অক্ষর *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    যদি (where || *extension == '\0') {
        ফেরত false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    যদি (start && *start == '0') {
        ফেরত false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    যদি (!glGetStringFunc) {
        ফেরত false;
    }

    যদি (isAtLeastGL3((ধ্রুবক অক্ষর *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint অঙ্ক_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        যদি ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            ফেরত false;
        }

#ifndef GL_অঙ্ক_EXTENSIONS
#define GL_অঙ্ক_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_অঙ্ক_EXTENSIONS, &অঙ্ক_exts);
        জন্য (i = 0; i < অঙ্ক_exts; i++) {
            ধ্রুবক অক্ষর *thisext = (ধ্রুবক অক্ষর *)glGetStringiFunc(GL_EXTENSIONS, i);
            যদি (SDL_strcmp(thisext, extension) == 0) {
                ফেরত true;
            }
        }

        ফেরত false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ধ্রুবক অক্ষর *)glGetStringFunc(GL_EXTENSIONS);
    যদি (!extensions) {
        ফেরত false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    জন্য (;;) {
        where = SDL_strstr(start, extension);
        যদি (!where) {
            বিরতি;
        }

        terminator = where + SDL_strlen(extension);
        যদি (where == extensions || *(where - 1) == ' ') {
            যদি (*terminator == ' ' || *terminator == '\0') {
                ফেরত true;
            }
        }

        start = terminator;
    }
    ফেরত false;
#অন্যথা
    ফেরত false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
শূন্য SDL_GL_DeduceMaxSupportedESProfile(পূর্ণসংখ্যা *major, পূর্ণসংখ্যা *minor)
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
        ফেরত;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

শূন্য SDL_GL_ResetAttributes(শূন্য)
{
    যদি (!_this) {
        ফেরত;
    }

    _this->egl_platformattrib_callback = ফাঁকা;
    _this->egl_surfaceattrib_callback = ফাঁকা;
    _this->egl_contextattrib_callback = ফাঁকা;
    _this->egl_attrib_callback_userdata = ফাঁকা;

    _this->gl_config.red_আকার = 8;
    _this->gl_config.green_আকার = 8;
    _this->gl_config.blue_আকার = 8;
    _this->gl_config.alpha_আকার = 8;
    _this->gl_config.বাফার_আকার = 0;
    _this->gl_config.depth_আকার = 16;
    _this->gl_config.stencil_আকার = 0;
    _this->gl_config.double_বাফার = 1;
    _this->gl_config.accum_red_আকার = 0;
    _this->gl_config.accum_green_আকার = 0;
    _this->gl_config.accum_blue_আকার = 0;
    _this->gl_config.accum_alpha_আকার = 0;
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
#নতুবা_যদি defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#নতুবা_যদি defined(SDL_VIDEO_OPENGL_ES)
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

bool SDL_GL_SetAttribute(SDL_GLAttr attr, পূর্ণসংখ্যা মান)
{
#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool ফলাফল;

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }
    ফলাফল = true;
    নির্বাচন (attr) {
    ক্ষেত্র SDL_GL_RED_আকার:
        _this->gl_config.red_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_GREEN_আকার:
        _this->gl_config.green_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_BLUE_আকার:
        _this->gl_config.blue_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_ALPHA_আকার:
        _this->gl_config.alpha_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_বাফার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_বাফার_আকার:
        _this->gl_config.বাফার_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_DEPTH_আকার:
        _this->gl_config.depth_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_STENCIL_আকার:
        _this->gl_config.stencil_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCUM_RED_আকার:
        _this->gl_config.accum_red_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCUM_GREEN_আকার:
        _this->gl_config.accum_green_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCUM_BLUE_আকার:
        _this->gl_config.accum_blue_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCUM_ALPHA_আকার:
        _this->gl_config.accum_alpha_আকার = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_STEREO:
        _this->gl_config.stereo = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_FLAGS:
        যদি (মান & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            ফলাফল = SDL_SetError("Unknown OpenGL context flag %d", মান);
            বিরতি;
        }
        _this->gl_config.flags = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_PROFILE_MASK:
        যদি (মান != 0 &&
            মান != SDL_GL_CONTEXT_PROFILE_CORE &&
            মান != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            মান != SDL_GL_CONTEXT_PROFILE_ES) {
            ফলাফল = SDL_SetError("Unknown OpenGL context profile %d", মান);
            বিরতি;
        }
        _this->gl_config.profile_mask = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = মান;
        বিরতি;
    ক্ষেত্র SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = মান;
        বিরতি;
    পূর্বনির্ধারিত:
        ফলাফল = SDL_SetError("Unknown OpenGL attribute");
        বিরতি;
    }
    ফেরত ফলাফল;
#অন্যথা
    ফেরত SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, পূর্ণসংখ্যা *মান)
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
        ফেরত SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *মান = 0;

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    নির্বাচন (attr) {
    ক্ষেত্র SDL_GL_RED_আকার:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_আকার;
#endif
        attrib = GL_RED_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_BLUE_আকার:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_আকার;
#endif
        attrib = GL_BLUE_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_GREEN_আকার:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_আকার;
#endif
        attrib = GL_GREEN_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_ALPHA_আকার:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_আকার;
#endif
        attrib = GL_ALPHA_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        বিরতি;
#অন্যথা
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *মান = _this->gl_config.double_বাফার;
        ফেরত true;
#endif
    ক্ষেত্র SDL_GL_DEPTH_আকার:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_আকার;
#endif
        attrib = GL_DEPTH_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_STENCIL_আকার:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_আকার;
#endif
        attrib = GL_STENCIL_BITS;
        বিরতি;
#ifdef SDL_VIDEO_OPENGL
    ক্ষেত্র SDL_GL_ACCUM_RED_আকার:
        attrib = GL_ACCUM_RED_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCUM_GREEN_আকার:
        attrib = GL_ACCUM_GREEN_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCUM_BLUE_আকার:
        attrib = GL_ACCUM_BLUE_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_ACCUM_ALPHA_আকার:
        attrib = GL_ACCUM_ALPHA_BITS;
        বিরতি;
    ক্ষেত্র SDL_GL_STEREO:
        attrib = GL_STEREO;
        বিরতি;
#অন্যথা
    ক্ষেত্র SDL_GL_ACCUM_RED_আকার:
    ক্ষেত্র SDL_GL_ACCUM_GREEN_আকার:
    ক্ষেত্র SDL_GL_ACCUM_BLUE_আকার:
    ক্ষেত্র SDL_GL_ACCUM_ALPHA_আকার:
    ক্ষেত্র SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *মান = 0;
        ফেরত true;
#endif
    ক্ষেত্র SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        বিরতি;
    ক্ষেত্র SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        বিরতি;
    ক্ষেত্র SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        বিরতি;
    ক্ষেত্র SDL_GL_বাফার_আকার:
    {
        পূর্ণসংখ্যা rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        যদি (!SDL_GL_GetAttribute(SDL_GL_RED_আকার, &rsize)) {
            ফেরত false;
        }
        যদি (!SDL_GL_GetAttribute(SDL_GL_GREEN_আকার, &gsize)) {
            ফেরত false;
        }
        যদি (!SDL_GL_GetAttribute(SDL_GL_BLUE_আকার, &bsize)) {
            ফেরত false;
        }
        যদি (!SDL_GL_GetAttribute(SDL_GL_ALPHA_আকার, &asize)) {
            ফেরত false;
        }

        *মান = rsize + gsize + bsize + asize;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *মান = (_this->gl_config.accelerated != 0);
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_RETAINED_BACKING:
    {
        *মান = _this->gl_config.retained_backing;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *মান = _this->gl_config.major_version;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *মান = _this->gl_config.minor_version;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_CONTEXT_FLAGS:
    {
        *মান = _this->gl_config.flags;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *মান = _this->gl_config.profile_mask;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *মান = _this->gl_config.share_with_current_context;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *মান = _this->gl_config.framebuffer_srgb_capable;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_CONTEXT_NO_ERROR:
    {
        *মান = _this->gl_config.no_error;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_EGL_PLATFORM:
    {
        *মান = _this->gl_config.egl_platform;
        ফেরত true;
    }
    ক্ষেত্র SDL_GL_FLOATBUFFERS:
    {
        যদি (_this->gl_config.HAS_GL_ARB_color_বাফার_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            বিরতি;
        } অন্যথা {
            ফেরত 0;
        }
    }
    পূর্বনির্ধারিত:
        ফেরত SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    যদি (!glGetStringFunc) {
        ফেরত false;
    }

    যদি (attachmentattrib && isAtLeastGL3((ধ্রুবক অক্ষর *)glGetStringFunc(GL_VERSION))) {
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
            ফেরত false;
        }
    } অন্যথা
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        যদি (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)মান);
        } অন্যথা {
            ফেরত false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    যদি (!glGetErrorFunc) {
        ফেরত false;
    }

    error = glGetErrorFunc();
    যদি (error != GL_NO_ERROR) {
        যদি (error == GL_INVALID_ENUM) {
            ফেরত SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } অন্যথা যদি (error == GL_INVALID_মান) {
            ফেরত SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        ফেরত SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    যদি (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *মান = (*মান == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    ফেরত true;
#অন্যথা
    ফেরত SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = ফাঁকা;
    CHECK_WINDOW_MAGIC(window, ফাঁকা);

    যদি (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        ফেরত ফাঁকা;
    }

#যদি defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    পূর্ণসংখ্যা srgb_requested = -1;
    ধ্রুবক অক্ষর *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    যদি (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    যদি (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, ফাঁকা);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, ফাঁকা);
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
                supported = isAtLeastGL3((ধ্রুবক অক্ষর *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            যদি (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    ফেরত ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool ফলাফল;

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }

    যদি (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        ফেরত true;
    }

    যদি (!context) {
        window = ফাঁকা;
    } অন্যথা যদি (window) {
        CHECK_WINDOW_MAGIC(window, false);

        যদি (!(window->flags & SDL_WINDOW_OPENGL)) {
            ফেরত SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } অন্যথা যদি (!_this->gl_allow_no_surface) {
        ফেরত SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    ফলাফল = _this->GL_MakeCurrent(_this, window, context);
    যদি (ফলাফল) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, ফাঁকা);
        SDL_SetTLS(&_this->current_glctx_tls, context, ফাঁকা);
    }
    ফেরত ফলাফল;
}

SDL_Window *SDL_GL_GetCurrentWindow(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    ফেরত (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    ফেরত (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(শূন্য)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত EGL_NO_DISPLAY;
    }
    যদি (!_this->egl_তথ্য) {
        SDL_SetError("There is no current EGL display");
        ফেরত EGL_NO_DISPLAY;
    }
    ফেরত _this->egl_তথ্য->egl_display;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    ফেরত ফাঁকা;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(শূন্য)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    যদি (!_this->egl_তথ্য) {
        SDL_SetError("There is no current EGL display");
        ফেরত ফাঁকা;
    }
    ফেরত _this->egl_তথ্য->egl_config;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    ফেরত ফাঁকা;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    যদি (!_this->egl_তথ্য) {
        SDL_SetError("There is no current EGL display");
        ফেরত ফাঁকা;
    }
    যদি (_this->GL_GetEGLSurface) {
        ফেরত _this->GL_GetEGLSurface(_this, window);
    }
    ফেরত ফাঁকা;
#অন্যথা
    SDL_SetError("SDL was not built with EGL support");
    ফেরত ফাঁকা;
#endif
}

bool SDL_GL_SetSwapInterval(পূর্ণসংখ্যা interval)
{
    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    } অন্যথা যদি (SDL_GL_GetCurrentContext() == ফাঁকা) {
        ফেরত SDL_SetError("No OpenGL context has been made current");
    } অন্যথা যদি (_this->GL_SetSwapInterval) {
        ফেরত _this->GL_SetSwapInterval(_this, interval);
    } অন্যথা {
        ফেরত SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(পূর্ণসংখ্যা *interval)
{
    CHECK_PARAM(!interval) {
       ফেরত SDL_InvalidParamError("interval");
    }

    *interval = 0;

    যদি (!_this) {
        ফেরত SDL_SetError("no video driver");
    } অন্যথা যদি (SDL_GL_GetCurrentContext() == ফাঁকা) {
        ফেরত SDL_SetError("no current context");
    } অন্যথা যদি (_this->GL_GetSwapInterval) {
        ফেরত _this->GL_GetSwapInterval(_this, interval);
    } অন্যথা {
        ফেরত SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!(window->flags & SDL_WINDOW_OPENGL)) {
        ফেরত SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    যদি (SDL_GL_GetCurrentWindow() != window) {
        ফেরত SDL_SetError("The specified window has not been made current");
    }

    ফেরত _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        ফেরত SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        ফেরত SDL_InvalidParamError("context");
    }

    যদি (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ফাঁকা, ফাঁকা);
    }

    ফেরত _this->GL_DestroyContext(_this, context);
}

#যদি 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
স্থির শূন্য Create_Mask_From_Color_চাবি_Or_Alpha(SDL_Surface *icon, Uint8 *mask, পূর্ণসংখ্যা flags)
{
    পূর্ণসংখ্যা x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    নির্বাচন (SDL_BYTESPERPIXEL(icon->format)) {
    ক্ষেত্র 1:
        {
            Uint8 *pixels;
            জন্য (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                জন্য (x = 0; x < icon->w; ++x) {
                    যদি (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        বিরতি;

    ক্ষেত্র 2:
        {
            Uint16 *pixels;
            জন্য (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                জন্য (x = 0; x < icon->w; ++x) {
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
        বিরতি;

    ক্ষেত্র 4:
        {
            Uint32 *pixels;
            জন্য (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                জন্য (x = 0; x < icon->w; ++x) {
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
        বিরতি;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
শূন্য SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    যদি (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        যদি (mask == ফাঁকা) {
            পূর্ণসংখ্যা mask_len = icon->h * (icon->w + 7) / 8;
            পূর্ণসংখ্যা flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            যদি (mask == ফাঁকা) {
                ফেরত;
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
    ফেরত (SDL_Text_প্রবেশ_Type)SDL_Get_সংখ্যা_Property(props, SDL_PROP_TEXTINPUT_TYPE_সংখ্যা, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_প্রবেশ_Capitalization(SDL_PropertiesID props)
{
    যদি (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_সংখ্যা)) {
        ফেরত (SDL_Capitalization)SDL_Get_সংখ্যা_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_সংখ্যা, SDL_CAPITALIZE_NONE);
    }

    নির্বাচন (SDL_Get_Text_প্রবেশ_Type(props)) {
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT:
        ফেরত SDL_CAPITALIZE_SENTENCES;
    ক্ষেত্র SDL_TEXTINPUT_TYPE_TEXT_NAME:
        ফেরত SDL_CAPITALIZE_শব্দগুলি;
    পূর্বনির্ধারিত:
        ফেরত SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_প্রবেশ_Autocorrect(SDL_PropertiesID props)
{
    ফেরত SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_প্রবেশ_Multiline(SDL_PropertiesID props)
{
    যদি (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        ফেরত SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    যদি (SDL_GetHintBoolean(SDL_HINT_RETURN_চাবি_HIDES_IME, false)) {
        ফেরত false;
    } অন্যথা {
        ফেরত true;
    }
}

স্থির bool AutoShowingScreenKeyboard(শূন্য)
{
    ধ্রুবক অক্ষর *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    যদি (!hint) {
        // This hint is currently only used by the X11 video driver
        যদি (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    যদি (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        ফেরত true;
    } অন্যথা {
        ফেরত false;
    }
}

bool SDL_Start_Text_প্রবেশ(SDL_Window *window)
{
    ফেরত SDL_Start_Text_প্রবেশ_With_Properties(window, 0);
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
            ফেরত false;
        }
        যদি (!SDL_CopyProperties(props, window->text_প্রবেশ_props)) {
            ফেরত false;
        }
    }

    যদি (_this->Set_Text_প্রবেশ_Properties) {
        _this->Set_Text_প্রবেশ_Properties(_this, window, props);
    }

    যদি (!window->text_প্রবেশ_active) {
        // Start the text input system
        যদি (_this->Start_Text_প্রবেশ) {
            যদি (!_this->Start_Text_প্রবেশ(_this, window, props)) {
                ফেরত false;
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
    ফেরত true;
}

bool SDL_Text_প্রবেশ_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ফেরত window->text_প্রবেশ_active;
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
    ফেরত true;
}

bool SDL_Set_Text_প্রবেশ_Area(SDL_Window *window, ধ্রুবক SDL_Rect *rect, পূর্ণসংখ্যা cursor)
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
            ফেরত false;
        }
    }
    ফেরত true;
}

bool SDL_Get_Text_প্রবেশ_Area(SDL_Window *window, SDL_Rect *rect, পূর্ণসংখ্যা *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (rect) {
        SDL_copyp(rect, &window->text_প্রবেশ_rect);
    }
    যদি (cursor) {
        *cursor = window->text_প্রবেশ_cursor;
    }
    ফেরত true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (_this->ClearComposition) {
        ফেরত _this->ClearComposition(_this, window);
    }
    ফেরত true;
}

bool SDL_HasScreenKeyboardSupport(শূন্য)
{
    যদি (_this && _this->HasScreenKeyboardSupport) {
        ফেরত _this->HasScreenKeyboardSupport(_this);
    }
    ফেরত false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    ফেরত _this->screen_keyboard_shown;
}

শূন্য SDL_SendScreenKeyboardShown(শূন্য)
{
    যদি (!_this || _this->screen_keyboard_shown) {
        ফেরত;
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
        ফেরত;
    }

    _this->screen_keyboard_shown = false;

    যদি (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ঠেলো_Event(&event);
    }
}

পূর্ণসংখ্যা SDL_Get_Message_Box_গুনতি(শূন্য)
{
    ফেরত SDL_GetAtomicInt(&SDL_messagebox_গুনতি);
}

bool SDL_ShowMessageBox(ধ্রুবক SDL_Message_Box_তথ্য *messageboxdata, পূর্ণসংখ্যা *buttonID)
{
    পূর্ণসংখ্যা dummybutton;
    bool ফলাফল = false;
    bool show_cursor_পূর্ব;
    SDL_Window *current_window;
    SDL_Message_Box_তথ্য mbdata;

    CHECK_PARAM(!messageboxdata) {
        ফেরত SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        ফেরত SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    অক্ষর *titlecpy = ফাঁকা;
    অক্ষর *msgcpy = ফাঁকা;
    যদি (messageboxdata->title) {
        ধ্রুবক size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(অক্ষর, slen, &titleisstack);
        যদি (!titlecpy) {
            ফেরত false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    যদি (messageboxdata->message) {
        ধ্রুবক size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(অক্ষর, slen, &msgisstack);
        যদি (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            ফেরত false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (শূন্য)SDL_AtomicIncRef(&SDL_messagebox_গুনতি);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_পূর্ব = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    যদি (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, আকার(*messageboxdata));
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
        ফলাফল = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } অন্যথা {
        // It's completely fine to call this function before video is initialized
        ধ্রুবক অক্ষর *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        যদি (driver_name && *driver_name != 0) {
            ধ্রুবক অক্ষর *driver_attempt = driver_name;
            যখন (driver_attempt && (*driver_attempt != 0) && !ফলাফল) {
                ধ্রুবক অক্ষর *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                জন্য (পূর্ণসংখ্যা i = 0; bootstrap[i]; ++i) {
                    যদি (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        যদি (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            ফলাফল = true;
                        }
                        বিরতি;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ফাঁকা;
            }
        } অন্যথা {
            জন্য (পূর্ণসংখ্যা i = 0; bootstrap[i]; ++i) {
                যদি (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    ফলাফল = true;
                    বিরতি;
                }
            }
        }
    }

    যদি (!ফলাফল) {
        ধ্রুবক অক্ষর *error = SDL_GetError();

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

    যদি (!show_cursor_পূর্ব) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    ফেরত ফলাফল;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, ধ্রুবক অক্ষর *title, ধ্রুবক অক্ষর *message, SDL_Window *window)
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

    ফেরত true;
#অন্যথা
    SDL_Message_Box_তথ্য তথ্য;
    SDL_Message_Box_Button_তথ্য button;

    SDL_zero(তথ্য);
    তথ্য.flags = flags;
    তথ্য.title = title;
    তথ্য.message = message;
    তথ্য.numbuttons = 1;
    তথ্য.buttons = &button;
    তথ্য.window = window;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.text = "OK";

    ফেরত SDL_ShowMessageBox(&তথ্য, ফাঁকা);
#endif
}

bool SDL_ShouldAllowTopmost(শূন্য)
{
    ফেরত SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    যদি (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        ফেরত true;
    }

    ফেরত SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, শূন্য *callback_তথ্য)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->SetWindowHitTest) {
        ফেরত SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_তথ্য = callback_তথ্য;

    ফেরত _this->SetWindowHitTest(window, callback != ফাঁকা);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    যদি (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        ফেরত SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    যদি (!props) {
        ফেরত false;
    }

    যদি (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        যদি (!surface) {
            ফেরত false;
        }
    } অন্যথা {
        surface = ফাঁকা;
    }

    যদি (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        ফেরত false;
    }

    যদি (_this->UpdateWindowShape) {
        যদি (!_this->UpdateWindowShape(_this, window, surface)) {
            ফেরত false;
        }
    }
    ফেরত true;
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
        জন্য (window = _this->windows; window; window = window->পরবর্তী) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(ফাঁকা);
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
        জন্য (window = _this->windows; window; window = window->পরবর্তী) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(ধ্রুবক অক্ষর *path)
{
    bool ফলাফল;

    যদি (!_this) {
        ফেরত SDL_UninitializedVideo();
    }
    যদি (_this->vulkan_config.loader_loaded) {
        যদি (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            ফেরত SDL_SetError("Vulkan loader library already loaded");
        }
        ফলাফল = true;
    } অন্যথা {
        যদি (!_this->Vulkan_LoadLibrary) {
            ফেরত SDL_DllNotSupported("Vulkan");
        }
        ফলাফল = _this->Vulkan_LoadLibrary(_this, path);
    }
    যদি (ফলাফল) {
        _this->vulkan_config.loader_loaded++;
    }
    ফেরত ফলাফল;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত ফাঁকা;
    }
    যদি (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        ফেরত ফাঁকা;
    }
    ফেরত (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

শূন্য SDL_Vulkan_UnloadLibrary(শূন্য)
{
    যদি (!_this) {
        SDL_UninitializedVideo();
        ফেরত;
    }
    যদি (_this->vulkan_config.loader_loaded > 0) {
        যদি (--_this->vulkan_config.loader_loaded > 0) {
            ফেরত;
        }
        যদি (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

অক্ষর ধ্রুবক * ধ্রুবক *SDL_Vulkan_GetInstanceExtensions(Uint32 *গুনতি)
{
    Uint32 tmpcount = 0;
    যদি (!গুনতি) {
        গুনতি = &tmpcount;
    }

    যদি (!_this->Vulkan_GetInstanceExtensions) {
        *গুনতি = 0;
        SDL_Unsupported();
        ফেরত ফাঁকা;
    }

    ফেরত _this->Vulkan_GetInstanceExtensions(_this, গুনতি);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  ধ্রুবক কাঠামো VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    যদি (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        ফেরত false;
    }

    CHECK_PARAM(!instance) {
        ফেরত SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        ফেরত SDL_InvalidParamError("surface");
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
        যদি (SDL_Vulkan_LoadLibrary(ফাঁকা)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } অন্যথা {
            ফেরত SDL_SetError("failed to load Vulkan library");
        }
    }

    ফেরত _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

শূন্য SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ধ্রুবক কাঠামো VkAllocationCallbacks *allocator)
{
    যদি (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_সূচক)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        ফেরত false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        ফেরত false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        ফেরত false;
    }

    যদি (_this->Vulkan_GetPresentationSupport) {
        ফেরত _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queue_Family_সূচক);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    ফেরত true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ফাঁকা);

    যদি (!_this->Metal_CreateView) {
        SDL_Unsupported();
        ফেরত ফাঁকা;
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

    ফেরত _this->Metal_CreateView(_this, window);
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
            ফেরত ফাঁকা;
        }
        ফেরত _this->Metal_GetLayer(_this, view);
    } অন্যথা {
        SDL_SetError("Metal is not supported.");
        ফেরত ফাঁকা;
    }
}

#যদি defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ধ্রুবক অক্ষর *SDL_GetCSSCursorName(SDL_SystemCursor id, ধ্রুবক অক্ষর **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    নির্বাচন (id) {
    ক্ষেত্র SDL_SYSTEM_CURSOR_DEFAULT:
        ফেরত "default";

    ক্ষেত্র SDL_SYSTEM_CURSOR_TEXT:
        ফেরত "text";

    ক্ষেত্র SDL_SYSTEM_CURSOR_WAIT:
        ফেরত "wait";

    ক্ষেত্র SDL_SYSTEM_CURSOR_CROSSHAIR:
        ফেরত "crosshair";

    ক্ষেত্র SDL_SYSTEM_CURSOR_PROGRESS:
        ফেরত "progress";

    ক্ষেত্র SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        যদি (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        ফেরত "nwse-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_NESW_RESIZE:
        যদি (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        ফেরত "nesw-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_EW_RESIZE:
        যদি (fallback_name) {
            *fallback_name = "col-resize";
        }
        ফেরত "ew-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_NS_RESIZE:
        যদি (fallback_name) {
            *fallback_name = "row-resize";
        }
        ফেরত "ns-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_MOVE:
        যদি (fallback_name) {
            *fallback_name = "all-scroll";
        }
        ফেরত "move";

    ক্ষেত্র SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        ফেরত "not-allowed";

    ক্ষেত্র SDL_SYSTEM_CURSOR_POINTER:
        ফেরত "pointer";

    ক্ষেত্র SDL_SYSTEM_CURSOR_NW_RESIZE:
        ফেরত "nw-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_N_RESIZE:
        ফেরত "n-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_NE_RESIZE:
        ফেরত "ne-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_E_RESIZE:
        ফেরত "e-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_SE_RESIZE:
        ফেরত "se-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_S_RESIZE:
        ফেরত "s-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_SW_RESIZE:
        ফেরত "sw-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_W_RESIZE:
        ফেরত "w-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        ফেরত "context-menu";

    ক্ষেত্র SDL_SYSTEM_CURSOR_HELP:
        ফেরত "help";

    ক্ষেত্র SDL_SYSTEM_CURSOR_CELL:
        ফেরত "cell";

    ক্ষেত্র SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        ফেরত "vertical-text";

    ক্ষেত্র SDL_SYSTEM_CURSOR_ALIAS:
        ফেরত "alias";

    ক্ষেত্র SDL_SYSTEM_CURSOR_COPY:
        ফেরত "copy";

    ক্ষেত্র SDL_SYSTEM_CURSOR_NO_DROP:
        ফেরত "no-drop";

    ক্ষেত্র SDL_SYSTEM_CURSOR_GRAB:
        ফেরত "grab";

    ক্ষেত্র SDL_SYSTEM_CURSOR_GRABBING:
        ফেরত "grabbing";

    ক্ষেত্র SDL_SYSTEM_CURSOR_COL_RESIZE:
        ফেরত "col-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_ROW_RESIZE:
        ফেরত "row-resize";

    ক্ষেত্র SDL_SYSTEM_CURSOR_ALL_SCROLL:
        যদি (fallback_name) {
            *fallback_name = "move";
        }
        ফেরত "all-scroll";

    ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_IN:
        ফেরত "zoom-in";

    ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_OUT:
        ফেরত "zoom-out";

    পূর্বনির্ধারিত:
        ফেরত "default";
    }
}
#endif

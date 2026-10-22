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

#અન્તર્ભાવ "SDL_internal.h"

// The high-level video driver subsystem

#અન્તર્ભાવ "SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_clipboard_c.h"
#અન્તર્ભાવ "SDL_egl_c.h"
#અન્તર્ભાવ "SDL_surface_c.h"
#અન્તર્ભાવ "SDL_pixels_c.h"
#અન્તર્ભાવ "SDL_rect_c.h"
#અન્તર્ભાવ "SDL_video_c.h"
#અન્તર્ભાવ "../events/SDL_events_c.h"
#અન્તર્ભાવ "../SDL_hints_c.h"
#અન્તર્ભાવ "../SDL_properties_c.h"
#અન્તર્ભાવ "../timer/SDL_timer_c.h"
#અન્તર્ભાવ "../camera/SDL_camera_c.h"
#અન્તર્ભાવ "../render/SDL_sysrender.h"
#અન્તર્ભાવ "../main/SDL_main_callbacks.h"

#ifdef SDL_VIDEO_OPENGL
#અન્તર્ભાવ <SDL3/SDL_opengl.h>
#endif // SDL_VIDEO_OPENGL

#જો defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#અન્તર્ભાવ <SDL3/SDL_opengles.h>
#endif // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#જો defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#અન્તર્ભાવ <SDL3/SDL_opengles2.h>
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
#અન્તર્ભાવ <emscripten.h>
#endif

#ifdef SDL_PLATFORM_3DS
#અન્તર્ભાવ <3ds.h>
#endif

#ifndef GL_RGBA_FLOAT_MODE_ARB
#define GL_RGBA_FLOAT_MODE_ARB 0x8820
#endif /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
સ્થિર VideoBootStrap *bootstrap[] = {
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
#ifdef SDL_આગત_LINUXEV
    &DUMMY_evdev_bootstrap,
#endif
#endif
#ifdef SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#endif
#ifdef SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#endif
    ખાલી
};

#define CHECK_WINDOW_MAGIC(window, result)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        પાછા result;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        પાછા result;                                                  \
    }

#define CHECK_DISPLAY_MAGIC(display, result)                            \
    CHECK_PARAM(!display) {                                             \
        પાછા result;                                                  \
    }                                                                   \

#define CHECK_WINDOW_NOT_POPUP(window, result)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        પાછા result;                                                  \
    }

#જો defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
બાહ્ય bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
બાહ્ય bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
બાહ્ય bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
બાહ્ય bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#endif

#ifdef SDL_VIDEO_DRIVER_UIKIT
બાહ્ય શૂન્ય SDL_UpdateLifecycleObserver(શૂન્ય);
#endif

સ્થિર શૂન્ય SDL_CheckWindowDisplayChanged(SDL_Window *window);
સ્થિર શૂન્ય SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
સ્થિર શૂન્ય SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
સ્થિર bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    જો (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        પાછા true;
    }
    પાછા false;
}

સ્થિર bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    પાછા !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

સ્થિર bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    પાછા !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

સ્થિર bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    પાછા !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

સ્થિર bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    પાછા !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

સ્થિર bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    પાછા !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
સ્થિર bool syncHint;

સ્થિર શૂન્ય SDL_SyncHintWatcher(શૂન્ય *userdata, અચલ અક્ષર *name, અચલ અક્ષર *old_કિંમત, અચલ અક્ષર *new_કિંમત)
{
    syncHint = SDL_GetStringBoolean(new_કિંમત, false);
}

સ્થિર શૂન્ય SDL_SyncIfRequired(SDL_Window *window)
{
    જો (syncHint) {
        SDL_SyncWindow(window);
    }
}

સ્થિર શૂન્ય SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    જો (window->parent) {
        જો (window->next_sibling) {
            window->next_sibling->prev_sibling = window->prev_sibling;
        }
        જો (window->prev_sibling) {
            window->prev_sibling->next_sibling = window->next_sibling;
        } નહીંતર {
            window->parent->first_child = window->next_sibling;
        }

        window->parent = ખાલી;
    }

    જો (parent) {
        window->parent = parent;

        window->next_sibling = parent->first_child;
        જો (parent->first_child) {
            parent->first_child->prev_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#define SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

પ્રકારવ્યાખ્યા સંરચના
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    શૂન્ય *pixels;
    પૂર્ણાંક pitch;
    પૂર્ણાંક bytes_per_pixel;
} SDL_WindowTextureData;

સ્થિર Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#જો (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    જો (_this->GL_CreateContext) {
        પાછા SDL_WINDOW_OPENGL;
    }
#endif
#જો defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    જો (_this->Metal_CreateView) {
        પાછા SDL_WINDOW_METAL;
    }
#endif
#જો defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    જો (SDL_strcmp(_this->name, "openvr") == 0) {
        પાછા SDL_WINDOW_OPENGL;
    }
#endif
    પાછા 0;
}

સ્થિર bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_WindowTextureData *data = (SDL_WindowTextureData *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ખાલી);
    અચલ bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    પૂર્ણાંક i;
    પૂર્ણાંક w, h;
    અચલ SDL_PixelFormat *texture_formats;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    જો (!data) {
        SDL_Renderer *renderer = ખાલી;
        અચલ અક્ષર *render_driver = ખાલી;

        // See if there's a render driver being requested
        અચલ અક્ષર *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        જો (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        જો (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        જો (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = ખાલી;
        }

        અક્ષર *render_driver_copy = ખાલી;
        જો (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            જો (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                અક્ષર *prev = render_driver_copy;
                અક્ષર *ptr = prev;
                જ્યારે ((ptr = SDL_strchr(ptr, ',')) != ખાલી) {
                    *ptr = '\0';
                    અચલ bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    જો (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } નહીંતર {
                        ptr++;
                        prev = ptr;
                    }
                }

                જો (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        જો (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            જો (!renderer) {
                // The error for this specific renderer has already been set
                પાછા false;
            }
        } નહીંતર {
            SDL_assert(render_driver_copy == ખાલી);
            અચલ પૂર્ણાંક total = SDL_Get_અંક_Render_Drivers();
            માટે (i = 0; i < total; ++i) {
                અચલ અક્ષર *name = SDL_GetRenderDriver(i);
                જો (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    જો (renderer) {
                        તોડો; // this will work.
                    }
                }
            }
            જો (!renderer) {
                પાછા SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != ખાલી); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        data = (SDL_WindowTextureData *)SDL_calloc(1, કદ(*data));
        જો (!data) {
            SDL_DestroyRenderer(renderer);
            પાછા false;
        }
        જો (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, data)) {
            SDL_DestroyRenderer(renderer);
            પાછા false;
        }

        data->renderer = renderer;
    }

    texture_formats = (અચલ SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(data->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, ખાલી);
    જો (!texture_formats) {
        પાછા false;
    }

    // Free any old texture and pixel data
    જો (data->texture) {
        SDL_DestroyTexture(data->texture);
        data->texture = ખાલી;
    }
    SDL_free(data->pixels);
    data->pixels = ખાલી;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    માટે (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        જો (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            તોડો;
        }
    }

    data->texture = SDL_CreateTexture(data->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    જો (!data->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        પાછા false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(data->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    data->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    data->pitch = (((w * data->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        અચલ size_t allocsize = (size_t)h * data->pitch;
        data->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        જો (!data->pixels) {
            પાછા false;
        }
    }

    *pixels = data->pixels;
    *pitch = data->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(data->renderer, ખાલી);

    પાછા true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ખાલી);
    જો (!data) {
        પાછા false;
    }
    જો (!data->renderer) {
        પાછા false;
    }
    પાછા SDL_SetRenderVSync(data->renderer, vsync);
}

સ્થિર bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક *vsync)
{
    SDL_WindowTextureData *data;

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ખાલી);
    જો (!data) {
        પાછા false;
    }
    જો (!data->renderer) {
        પાછા false;
    }
    પાછા SDL_GetRenderVSync(data->renderer, vsync);
}

સ્થિર bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects, પૂર્ણાંક numrects)
{
    SDL_WindowTextureData *data;
    SDL_Rect rect;
    શૂન્ય *src;
    પૂર્ણાંક w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    data = (SDL_WindowTextureData *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ખાલી);
    જો (!data || !data->texture) {
        પાછા SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    જો (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (શૂન્ય *)((Uint8 *)data->pixels +
                       rect.y * data->pitch +
                       rect.x * data->bytes_per_pixel);
        જો (!SDL_UpdateTexture(data->texture, &rect, src, data->pitch)) {
            પાછા false;
        }

        જો (!SDL_RenderTexture(data->renderer, data->texture, ખાલી, ખાલી)) {
            પાછા false;
        }

        SDL_RenderPresent(data->renderer);
    }
    પાછા true;
}

સ્થિર શૂન્ય SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    જો (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_WindowTextureData *data = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, ખાલી);

        જો (data->texture) {
            SDL_DestroyTexture(data->texture);
        }
        જો (data->renderer) {
            SDL_DestroyRenderer(data->renderer);
        }
        SDL_free(data->pixels);
        SDL_free(data);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

સ્થિર SDL_VideoDevice *_this = ખાલી;
સ્થિર SDL_AtomicInt SDL_messagebox_ગણતરી;

સ્થિર પૂર્ણાંક SDLCALL cmpmodes(અચલ શૂન્ય *A, અચલ શૂન્ય *B)
{
    અચલ SDL_DisplayMode *a = (અચલ SDL_DisplayMode *)A;
    અચલ SDL_DisplayMode *b = (અચલ SDL_DisplayMode *)B;
    પૂર્ણાંક a_refresh_rate = (પૂર્ણાંક)(a->refresh_rate * 100);
    પૂર્ણાંક b_refresh_rate = (પૂર્ણાંક)(b->refresh_rate * 100);
    પૂર્ણાંક a_pixel_density = (પૂર્ણાંક)(a->pixel_density * 100);
    પૂર્ણાંક b_pixel_density = (પૂર્ણાંક)(b->pixel_density * 100);

    જો (a->w != b->w) {
        પાછા b->w - a->w;
    } નહીંતર જો (a->h != b->h) {
        પાછા b->h - a->h;
    } નહીંતર જો (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        પાછા SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } નહીંતર જો (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        પાછા SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } નહીંતર જો (a_refresh_rate != b_refresh_rate) {
        પાછા b_refresh_rate - a_refresh_rate;
    } નહીંતર જો (a_pixel_density != b_pixel_density) {
        પાછા a_pixel_density - b_pixel_density;
    }
    પાછા 0;
}

bool SDL_UninitializedVideo(શૂન્ય)
{
    પાછા SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
સ્થિર અચલ VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

પૂર્ણાંક SDL_Get_અંક_Video_Drivers(શૂન્ય)
{
    સ્થિર પૂર્ણાંક અંક_drivers = -1;

    જો (અંક_drivers >= 0) {
        પાછા અંક_drivers;
    }

    અંક_drivers = 0;

    // Build a list of unique video drivers.
    માટે (પૂર્ણાંક i = 0; bootstrap[i] != ખાલી; ++i) {
        bool duplicate = false;
        માટે (પૂર્ણાંક j = 0; j < i; ++j) {
            જો (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                તોડો;
            }
        }

        જો (!duplicate) {
            deduped_bootstrap[અંક_drivers++] = bootstrap[i];
        }
    }

    પાછા અંક_drivers;
}

અચલ અક્ષર *SDL_GetVideoDriver(પૂર્ણાંક index)
{
    CHECK_PARAM(index < 0 || index >= SDL_Get_અંક_Video_Drivers()) {
        SDL_InvalidParamError("index");
        પાછા ખાલી;
    }
    પાછા deduped_bootstrap[index]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(અચલ અક્ષર *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    પૂર્ણાંક i = 0;

    // Check to make sure we don't overwrite '_this'
    જો (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    જો (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        જાઓ pre_driver_error;
    }
    init_events = true;
    જો (!SDL_InitKeyboard()) {
        જાઓ pre_driver_error;
    }
    init_keyboard = true;
    જો (!SDL_PreInitMouse()) {
        જાઓ pre_driver_error;
    }
    init_mouse = true;
    જો (!SDL_InitTouch()) {
        જાઓ pre_driver_error;
    }
    init_touch = true;
    જો (!SDL_InitPen()) {
        જાઓ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = ખાલી;
#ifdef SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    જો (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#endif
    જો (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    જો (driver_name && *driver_name != 0) {
        અચલ અક્ષર *driver_attempt = driver_name;
        જ્યારે (driver_attempt && *driver_attempt != 0 && !video) {
            અચલ અક્ષર *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            માટે (i = 0; bootstrap[i]; ++i) {
                જો (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    જો (video) {
                        તોડો;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ખાલી;
        }
    } નહીંતર {
        માટે (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            જો (video) {
                તોડો;
            }
        }
    }
    જો (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } નહીંતર {
        જો (driver_name) {
            SDL_SetError("%s not available", driver_name);
            જાઓ pre_driver_error;
        }
        SDL_SetError("No available video device");
        જાઓ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = ખાલી;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    જો (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        પાછા false;
    }

    // Make sure some displays were added
    જો (_this->અંક_displays == 0) {
        SDL_QuitVideo();
        પાછા SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, ખાલી);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    જો (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    પાછા true;

pre_driver_error:
    SDL_assert(_this == ખાલી);
    જો (init_pen) {
        SDL_QuitPen();
    }
    જો (init_touch) {
        SDL_QuitTouch();
    }
    જો (init_mouse) {
        SDL_QuitMouse();
    }
    જો (init_keyboard) {
        SDL_QuitKeyboard();
    }
    જો (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    પાછા false;
}

અચલ અક્ષર *SDL_GetCurrentVideoDriver(શૂન્ય)
{
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    પાછા _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(શૂન્ય)
{
    પાછા _this;
}

bool SDL_OnVideoThread(શૂન્ય)
{
    પાછા (_this && SDL_GetCurrentThreadID() == _this->thread);
}

શૂન્ય SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    જો (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(શૂન્ય)
{
    જો (_this) {
        પાછા _this->system_theme;
    } નહીંતર {
        પાછા SDL_SYSTEM_THEME_UNKNOWN;
    }
}

શૂન્ય SDL_UpdateDesktopBounds(શૂન્ય)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(ખાલી);
    જો (displays) {
        માટે (પૂર્ણાંક i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            જો (SDL_GetDisplayBounds(displays[i], &bounds)) {
                જો (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } નહીંતર {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

સ્થિર શૂન્ય SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    જો (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    જો (mode->refresh_rate_numerator > 0) {
        જો (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (દશાંશ)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } નહીંતર {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(અચલ SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    જો (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, કદ(display.desktop_mode));
    }
    પાછા SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(અચલ SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    પૂર્ણાંક i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(કદ(*new_display));
    જો (!new_display) {
        પાછા 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->અંક_displays + 1) * કદ(*displays));
    જો (!displays) {
        SDL_free(new_display);
        પાછા 0;
    }
    _this->displays = displays;
    _this->displays[_this->અંક_displays++] = new_display;

    id = SDL_GetNextObjectID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    જો (display->name) {
        new_display->name = SDL_strdup(display->name);
    } નહીંતર {
        અક્ષર name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    જો (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    માટે (i = 0; i < new_display->અંક_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    જો (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    પાછા id;
}

શૂન્ય SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    માટે (window = _this->windows; window; window = window->next) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

શૂન્ય SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

શૂન્ય SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    પૂર્ણાંક display_index = SDL_GetDisplayIndex(displayID);
    જો (display_index < 0) {
        પાછા;
    }

    display = _this->displays[display_index];

    જો (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = ખાલી;
    SDL_free(display->internal);
    display->internal = ખાલી;
    SDL_free(display);

    જો (display_index < (_this->અંક_displays - 1)) {
        SDL_memmove(&_this->displays[display_index], &_this->displays[display_index + 1], (_this->અંક_displays - display_index - 1) * કદ(_this->displays[display_index]));
    }
    --_this->અંક_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(પૂર્ણાંક *ગણતરી)
{
    પૂર્ણાંક i;
    SDL_DisplayID *displays;

    જો (!_this) {
        જો (ગણતરી) {
            *ગણતરી = 0;
        }

        SDL_UninitializedVideo();
        પાછા ખાલી;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->અંક_displays + 1) * કદ(*displays));
    જો (displays) {
        જો (ગણતરી) {
            *ગણતરી = _this->અંક_displays;
        }

        માટે (i = 0; i < _this->અંક_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } નહીંતર {
        જો (ગણતરી) {
            *ગણતરી = 0;
        }
    }
    પાછા displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    પૂર્ણાંક display_index;

    display_index = SDL_GetDisplayIndex(displayID);
    જો (display_index < 0) {
        પાછા ખાલી;
    }
    પાછા _this->displays[display_index];
}

સ્થિર SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    જો (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    જો (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    પાછા displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    પાછા SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(શૂન્ય)
{
    જો (!_this || _this->અંક_displays == 0) {
        SDL_UninitializedVideo();
        પાછા 0;
    }
    પાછા _this->displays[0]->id;
}

પૂર્ણાંક SDL_GetDisplayIndex(SDL_DisplayID displayID)
{
    પૂર્ણાંક display_index;

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા -1;
    }

    માટે (display_index = 0; display_index < _this->અંક_displays; ++display_index) {
        જો (displayID == _this->displays[display_index]->id) {
            પાછા display_index;
        }
    }
    SDL_SetError("Invalid display");
    પાછા -1;
}

SDL_DisplayData *SDL_GetDisplayDriverData(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ખાલી);

    પાછા display->internal;
}

SDL_DisplayData *SDL_GetDisplayDriverDataForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    પાછા SDL_GetDisplayDriverData(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    જો (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    પાછા display->props;
}

અચલ અક્ષર *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ખાલી);

    પાછા display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        પાછા SDL_InvalidParamError("rect");
    }

    જો (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        જો (_this->GetDisplayBounds(_this, display, rect)) {
            પાછા true;
        }
    }

    // Assume that the displays are left to right
    જો (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } નહીંતર {
        SDL_GetDisplayBounds(_this->displays[SDL_GetDisplayIndex(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    પાછા true;
}

સ્થિર પૂર્ણાંક ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    અચલ અક્ષર *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    પાછા hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        પાછા SDL_InvalidParamError("rect");
    }

    જો (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        પાછા true;
    }

    જો (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        જો (_this->GetDisplayUsableBounds(_this, display, rect)) {
            પાછા true;
        }
    }

    // Oh well, just give the entire display bounds.
    પાછા SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    જો (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        પાછા display->natural_orientation;
    } નહીંતર {
        // Default to landscape if the driver hasn't set it
        પાછા SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    જો (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        પાછા display->current_orientation;
    } નહીંતર {
        // Default to landscape if the driver hasn't set it
        પાછા SDL_ORIENTATION_LANDSCAPE;
    }
}

શૂન્ય SDL_SetDisplayContentScale(SDL_VideoDisplay *display, દશાંશ scale)
{
    જો (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        માટે (window = _this->windows; window; window = window->next) {
            જો (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

દશાંશ SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    પાછા display->content_scale;
}

શૂન્ય SDL_SetWindowHDRProperties(SDL_Window *window, અચલ SDL_HDROutputProperties *HDR, bool send_event)
{
    અચલ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    જો (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        જો (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

શૂન્ય SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, અચલ SDL_HDROutputProperties *HDR)
{
    અચલ SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    અચલ bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	જો (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    જો (changed && !SDL_DriverSendsHDRChanges(_this)) {
        માટે (SDL_Window *w = display->device->windows; w; w = w->next) {
            જો (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

સ્થિર શૂન્ય SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    જો (display->અંક_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
સ્થિર અચલ SDL_DisplayMode *SDL_GetFullscreenModeMatch(અચલ SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    જો (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        પાછા ખાલી;
    }

    SDL_memcpy(&fullscreen_mode, mode, કદ(fullscreen_mode));
    જો (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = ખાલી;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    જો (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        જો (!mode) {
            માટે (પૂર્ણાંક i = 0; i < display->અંક_fullscreen_modes; ++i) {
                જો (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], કદ(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    તોડો;
                }
            }
        }

        // Search for a mode with the same characteristics
        જો (!mode) {
            માટે (પૂર્ણાંક i = 0; i < display->અંક_fullscreen_modes; ++i) {
                જો (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    તોડો;
                }
            }
        }
    }
    પાછા mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, અચલ SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    પૂર્ણાંક i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, કદ(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->અંક_fullscreen_modes;
    માટે (i = 0; i < nmodes; ++i) {
        જો (cmpmodes(&new_mode, &modes[i]) == 0) {
            પાછા false;
        }
    }

    // Go ahead and add the new mode
    જો (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * કદ(*modes));
        જો (!modes) {
            પાછા false;
        }

        જો (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * કદ(*modes));
            માટે (i = 0; i < nmodes; ++i) {
                જો (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->અંક_fullscreen_modes++], &new_mode, કદ(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->અંક_fullscreen_modes,
              કદ(SDL_DisplayMode), cmpmodes);

    પાછા true;
}

શૂન્ય SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    પૂર્ણાંક i;

    માટે (i = display->અંક_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = ખાલી;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = ખાલી;
    display->અંક_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, પૂર્ણાંક *ગણતરી)
{
    પૂર્ણાંક i;
    પૂર્ણાંક અંક_modes;
    SDL_DisplayMode **result;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    જો (ગણતરી) {
        *ગણતરી = 0;
    }

    CHECK_DISPLAY_MAGIC(display, ખાલી);

    SDL_UpdateFullscreenDisplayModes(display);

    અંક_modes = display->અંક_fullscreen_modes;
    result = (SDL_DisplayMode **)SDL_malloc((અંક_modes + 1) * કદ(*result) + અંક_modes * કદ(**result));
    જો (result) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)result + ((અંક_modes + 1) * કદ(*result)));
        જો (અંક_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, અંક_modes * કદ(*modes));
        }
        માટે (i = 0; i < અંક_modes; ++i) {
            result[i] = modes++;
        }
        result[i] = ખાલી;

        જો (ગણતરી) {
            *ગણતરી = અંક_modes;
        }
    } નહીંતર {
        જો (ગણતરી) {
            *ગણતરી = 0;
        }
    }
    પાછા result;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, પૂર્ણાંક w, પૂર્ણાંક h, દશાંશ refresh_rate, bool include_ઉપલું_density_modes, SDL_DisplayMode *result)
{
    CHECK_PARAM(!result) {
        પાછા SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    અચલ SDL_DisplayMode *mode, *closest = ખાલી;
    દશાંશ aspect_ratio;
    પૂર્ણાંક i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(result);

    CHECK_DISPLAY_MAGIC(display, false);

    જો (h > 0) {
        aspect_ratio = (દશાંશ)w / h;
    } નહીંતર {
        aspect_ratio = 1.0f;
    }

    જો (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    માટે (i = 0; i < display->અંક_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        જો (w > mode->w) {
            // Out of sorted modes large enough here
            તોડો;
        }
        જો (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            ચાલુ;
        }
        જો (mode->pixel_density > 1.0f && !include_ઉપલું_density_modes) {
            ચાલુ;
        }
        જો (closest) {
            દશાંશ current_aspect_ratio = (દશાંશ)mode->w / mode->h;
            દશાંશ closest_aspect_ratio = (દશાંશ)closest->w / closest->h;
            જો (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                ચાલુ;
            }

            જો (mode->w == closest->w && mode->h == closest->h) {
                જો (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    ચાલુ;
                }
                જો (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    ચાલુ;
                }
            }
        }

        closest = mode;
    }
    જો (!closest) {
        પાછા SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(result, closest);

    પાછા true;
}

સ્થિર bool DisplayModeChanged(અચલ SDL_DisplayMode *old_mode, અચલ SDL_DisplayMode *new_mode)
{
    પાછા ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

શૂન્ય SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, અચલ SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    જો (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        પાછા;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    જો (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        જો (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

અચલ SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ખાલી);

    પાછા &display->desktop_mode;
}

શૂન્ય SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, અચલ SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    જો (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } નહીંતર {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    જો (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

અચલ SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, ખાલી);

    પાછા display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    જો (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        પાછા true;
    }

    જો (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#ifndef SDL_PLATFORM_RISCOS
    જો (mode == display->current_mode) {
        પાછા true;
    }
#endif

    // Actually change the display mode
    જો (_this->SetDisplayMode) {
        bool result;

        _this->setting_display_mode = true;
        result = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        જો (!result) {
            પાછા false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    પાછા true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
સ્થિર શૂન્ય SDL_GetClosestPointOnRect(અચલ SDL_Rect *rect, SDL_Point *point)
{
    અચલ પૂર્ણાંક જમણું = rect->x + rect->w - 1;
    અચલ પૂર્ણાંક bottom = rect->y + rect->h - 1;

    જો (point->x < rect->x) {
        point->x = rect->x;
    } નહીંતર જો (point->x > જમણું) {
        point->x = જમણું;
    }

    જો (point->y < rect->y) {
        point->y = rect->y;
    } નહીંતર જો (point->y > bottom) {
        point->y = bottom;
    }
}

સ્થિર SDL_DisplayID GetDisplayForRect(પૂર્ણાંક x, પૂર્ણાંક y, પૂર્ણાંક w, પૂર્ણાંક h)
{
    પૂર્ણાંક i, dist;
    SDL_DisplayID closest = 0;
    પૂર્ણાંક closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    જો (_this) {
        માટે (i = 0; i < _this->અંક_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            જો (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, ખાલી)) {
                પાછા display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            જો (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    જો (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    પાછા closest;
}

શૂન્ય SDL_RelativeToGlobalForWindow(SDL_Window *window, પૂર્ણાંક rel_x, પૂર્ણાંક rel_y, પૂર્ણાંક *abs_x, પૂર્ણાંક *abs_y)
{
    SDL_Window *w;

    જો (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        માટે (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            જો (!SDL_WINDOW_IS_POPUP(w)) {
                તોડો;
            }
        }
    }

    જો (abs_x) {
        *abs_x = rel_x;
    }
    જો (abs_y) {
        *abs_y = rel_y;
    }
}

શૂન્ય SDL_GlobalToRelativeForWindow(SDL_Window *window, પૂર્ણાંક abs_x, પૂર્ણાંક abs_y, પૂર્ણાંક *rel_x, પૂર્ણાંક *rel_y)
{
    SDL_Window *w;

    જો (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        માટે (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            જો (!SDL_WINDOW_IS_POPUP(w)) {
                તોડો;
            }
        }
    }

    જો (rel_x) {
        *rel_x = abs_x;
    }
    જો (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(અચલ SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        પાછા 0;
    }

    પાછા GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(અચલ SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        પાછા 0;
    }

    પાછા GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

સ્થિર SDL_DisplayID GetDisplayAtOrigin(પૂર્ણાંક x, પૂર્ણાંક y)
{
    માટે (પૂર્ણાંક i = 0; i < _this->અંક_displays; ++i) {
        SDL_Rect rect;
        અચલ SDL_DisplayID cur_id = _this->displays[i]->id;
        જો (SDL_GetDisplayBounds(cur_id, &rect)) {
            જો (x == rect.x && y == rect.y) {
                પાછા cur_id;
            }
        }
    }

    પાછા 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    પૂર્ણાંક x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    જો (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    જો (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        જો (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } નહીંતર {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    જો (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    પાછા displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, ખાલી);

    // An explicit fullscreen display overrides all
    જો (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    જો (!displayID) {
        displayID = window->pending_displayID;
    }
    જો (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        અચલ પૂર્ણાંક x = window->last_position_pending ? window->pending.x : window->x;
        અચલ પૂર્ણાંક y = window->last_position_pending ? window->pending.y : window->y;
        અચલ પૂર્ણાંક w = window->last_size_pending ? window->pending.w : window->w;
        અચલ પૂર્ણાંક h = window->last_size_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        જો (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    જો (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    પાછા SDL_GetVideoDisplay(displayID);
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
    જો (fs_display) {
        SDL_Set_સંખ્યા_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } નહીંતર {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    પાછા GetDisplayForWindow(window);
}

સ્થિર શૂન્ય SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    જો (SDL_SendsDisplayChanges(_this)) {
        પાછા;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    જો (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        જો (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            જો (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                પૂર્ણાંક old_area = old_overlap.w * old_overlap.h;
                પૂર્ણાંક new_area = new_overlap.w * new_overlap.h;
                દશાંશ new_overlap_ratio = (new_area / ((દશાંશ)old_area + new_area));
                જો (new_overlap_ratio < 0.80) {
                    પાછા;
                }
            }
        }
    }

    જો (displayID != window->displayID) {
        પૂર્ણાંક i, display_index;

        // Sanity check our fullscreen windows
        display_index = SDL_GetDisplayIndex(displayID);
        માટે (i = 0; i < _this->અંક_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            જો (display->fullscreen_window == window) {
                જો (display_index != i) {
                    જો (display_index < 0) {
                        display_index = i;
                    } નહીંતર {
                        SDL_VideoDisplay *new_display = _this->displays[display_index];

                        // The window was moved to a different display
                        જો (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = ખાલી;
                    }
                }
                તોડો;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (પૂર્ણાંક)displayID, 0);
    }
}

દશાંશ SDL_GetWindowPixelDensity(SDL_Window *window)
{
    પૂર્ણાંક window_w, window_h, pixel_w, pixel_h;
    દશાંશ pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    જો (SDL_GetWindowSize(window, &window_w, &window_h) &&
        SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (દશાંશ)pixel_w / window_w;
    }
    પાછા pixel_density;
}

દશાંશ SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    પાછા window->display_scale;
}

સ્થિર શૂન્ય SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    દશાંશ display_scale;

    જો (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } નહીંતર {
        અચલ દશાંશ pixel_density = SDL_GetWindowPixelDensity(window);
        અચલ દશાંશ content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    જો (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = ખાલી;
    SDL_DisplayMode *mode = ખાલી;
    પૂર્ણાંક i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    જો (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    જો (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        જો (!display) {
            // This should never happen, but it did...
            જાઓ done;
        }
    } નહીંતર {
        માટે (i = 0; i < _this->અંક_displays; ++i) {
            display = _this->displays[i];
            જો (display->fullscreen_window == window) {
                તોડો;
            }
        }
        જો (!display || i == _this->અંક_displays) {
            // Already not fullscreen on any display
            display = ખાલી;
        }
    }

    જો (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        જો (mode) {
            window->fullscreen_exclusive = true;
        } નહીંતર {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#જો defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    જો (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        જો (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            જો (display) {
                display->fullscreen_window = ખાલી;
            }
            જાઓ done;
        }
        જો (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            જો (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                જો (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    જાઓ error;
                }
            } નહીંતર જો (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                માટે (i = 0; i < _this->અંક_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    જો (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, ખાલી);
                        જો (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = ખાલી;
                    }
                }
            }

            જો (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                જાઓ done;
            }
        }
    }
#endif

    જો (display) {
        // Restore the video mode on other displays if needed
        માટે (i = 0; i < _this->અંક_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            જો (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, ખાલી);
                other->fullscreen_window = ખાલી;
            }
        }
    }

    જો (fullscreen) {
        પૂર્ણાંક mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        જો (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        જો (!SDL_SetDisplayModeForDisplay(display, mode)) {
            જાઓ error;
        }
        જો (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            જો (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } નહીંતર {
                resized = true;
            }

            જો (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                જો (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } નહીંતર જો (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                જાઓ error;
            }
        }

        જો (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            જો (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                જો (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } નહીંતર {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                જો (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                જો (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } નહીંતર {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } નહીંતર {
        bool resized = false;

        // Restore the desktop mode
        જો (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, ખાલી);
        }
        જો (commit) {
            SDL_FullscreenResult ret = SDL_FULLSCREEN_SUCCEEDED;
            જો (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                જો (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } નહીંતર {
                resized = true;
            }

            જો (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                જો (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } નહીંતર જો (ret == SDL_FULLSCREEN_FAILED) {
                જાઓ error;
            }
        }

        જો (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            જો (display) {
                display->fullscreen_window = ખાલી;
            }

            જો (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                જો (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } નહીંતર {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    પાછા true;

error:
    જો (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    પાછા false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, અચલ SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (mode) {
        જો (!SDL_GetFullscreenModeMatch(mode)) {
            પાછા SDL_SetError("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&window->requested_fullscreen_mode, mode);
    } નહીંતર {
        SDL_zero(window->requested_fullscreen_mode);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);

#જો defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    જો (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#endif
    જો (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    પાછા true;
}

અચલ SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ખાલી);
    CHECK_WINDOW_NOT_POPUP(window, ખાલી);

    જો (window->flags & SDL_WINDOW_FULLSCREEN) {
        પાછા SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } નહીંતર {
        પાછા SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

શૂન્ય *SDL_GetWindowICCProfile(SDL_Window *window, size_t *size)
{
    જો (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        પાછા ખાલી;
    }
    પાછા _this->GetWindowICCProfile(_this, window, size);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    અચલ SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    જો (mode) {
        પાછા mode->format;
    } નહીંતર {
        પાછા SDL_PIXELFORMAT_UNKNOWN;
    }
}

#define CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ઉપલું_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_ટોચ | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

સ્થિર SDL_INLINE bool IsAcceptingDragAndDrop(શૂન્ય)
{
    જો (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        પાછા true;
    }
    પાછા false;
}

// prepare a newly-created window
સ્થિર SDL_INLINE શૂન્ય PrepareDragAndDropSupport(SDL_Window *window)
{
    જો (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
શૂન્ય SDL_ToggleDragAndDropSupport(શૂન્ય)
{
    જો (_this && _this->AcceptDragAndDrop) {
        અચલ bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        માટે (window = _this->windows; window; window = window->next) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(પૂર્ણાંક *ગણતરી)
{
    જો (ગણતરી) {
        *ગણતરી = 0;
    }

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }

    SDL_Window *window;
    પૂર્ણાંક અંક_added = 0;
    પૂર્ણાંક અંક_windows = 0;
    માટે (window = _this->windows; window; window = window->next) {
        ++અંક_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((અંક_windows + 1) * કદ(*windows));
    જો (!windows) {
        પાછા ખાલી;
    }

    માટે (window = _this->windows; window; window = window->next) {
        windows[અંક_added++] = window;
        જો (અંક_added == અંક_windows) {
            // Race condition? Multi-threading not supported, ignore it
            તોડો;
        }
    }
    windows[અંક_added] = ખાલી;

    જો (ગણતરી) {
        *ગણતરી = અંક_added;
    }
    પાછા windows;
}

સ્થિર શૂન્ય ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    જો (!SDL_WINDOW_IS_POPUP(window)) {
        જો (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        જો (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        જો (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        જો (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        જો (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        જો (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

સ્થિર શૂન્ય SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    જો (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } નહીંતર {
        ApplyWindowFlags(window, flags);
        જો (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#જો defined(SDL_PLATFORM_LINUX)
    જો (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_કિંમત(window, 0.0f);
    }
#endif
}

સ્થિર bool SDL_ContextNotSupported(અચલ અક્ષર *name)
{
    પાછા SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

સ્થિર bool SDL_DllNotSupported(અચલ અક્ષર *name)
{
    પાછા SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

સ્થિર સંરચના {
    અચલ અક્ષર *property_name;
    SDL_WindowFlags flag;
    bool invert_કિંમત;
} SDL_WindowFlagProperties[] = {
    { SDL_PROP_WINDOW_CREATE_ALWAYS_ON_ટોચ_BOOLEAN,      SDL_WINDOW_ALWAYS_ON_ટોચ,       false },
    { SDL_PROP_WINDOW_CREATE_BORDERLESS_BOOLEAN,         SDL_WINDOW_BORDERLESS,          false },
    { SDL_PROP_WINDOW_CREATE_FOCUSABLE_BOOLEAN,          SDL_WINDOW_NOT_FOCUSABLE,       true },
    { SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN,         SDL_WINDOW_FULLSCREEN,          false },
    { SDL_PROP_WINDOW_CREATE_HIDDEN_BOOLEAN,             SDL_WINDOW_HIDDEN,              false },
    { SDL_PROP_WINDOW_CREATE_ઉપલું_PIXEL_DENSITY_BOOLEAN, SDL_WINDOW_ઉપલું_PIXEL_DENSITY,  false },
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

સ્થિર SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    unsigned i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_સંખ્યા, 0);

    માટે (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        જો (SDL_WindowFlagProperties[i].invert_કિંમત) {
            જો (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } નહીંતર {
            જો (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    પાછા flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    અચલ અક્ષર *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, ખાલી);
    પૂર્ણાંક x = (પૂર્ણાંક)SDL_Get_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_X_સંખ્યા, SDL_WINDOWPOS_UNDEFINED);
    પૂર્ણાંક y = (પૂર્ણાંક)SDL_Get_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_Y_સંખ્યા, SDL_WINDOWPOS_UNDEFINED);
    પૂર્ણાંક w = (પૂર્ણાંક)SDL_Get_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_સંખ્યા, 0);
    પૂર્ણાંક h = (પૂર્ણાંક)SDL_Get_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_સંખ્યા, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, ખાલી);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    જો (!_this) {
        // Initialize the video system if needed
        જો (!SDL_Init(SDL_INIT_VIDEO)) {
            પાછા ખાલી;
        }

        // Make clang-tidy happy
        જો (!_this) {
            પાછા ખાલી;
        }
    }

    જો ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        પાછા ખાલી;
    }

    જો ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        જો (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            પાછા ખાલી;
        }

        // Tooltip and popup menu window must specify a parent window
        જો (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            પાછા ખાલી;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    જો (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (unsigned પૂર્ણાંક)type_flags);
        પાછા ખાલી;
    }

    // Make sure the display list is up to date for window placement
    જો (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    જો (w < 1) {
        w = 1;
    }
    જો (h < 1) {
        h = 1;
    }

    જો (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        જો ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } નહીંતર જો ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        જો (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        જો (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        જો (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            જો (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        જો (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            જો (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    જો (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (unsigned પૂર્ણાંક)graphics_flags);
        પાછા ખાલી;
    }

    // Some platforms have certain graphics backends enabled by default
    જો (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    જો (flags & SDL_WINDOW_OPENGL) {
        જો (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            પાછા ખાલી;
        }
        જો (!SDL_GL_LoadLibrary(ખાલી)) {
            પાછા ખાલી;
        }
    }

    જો (flags & SDL_WINDOW_VULKAN) {
        જો (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            પાછા ખાલી;
        }
        જો (!SDL_Vulkan_LoadLibrary(ખાલી)) {
            પાછા ખાલી;
        }
    }

    જો (flags & SDL_WINDOW_METAL) {
        જો (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            પાછા ખાલી;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, કદ(*window));
    જો (!window) {
        પાછા ખાલી;
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
    જો (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    જો (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    જો (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    જો (_this->windows) {
        _this->windows->prev = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    જો (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_ધકેલો_Error();
        SDL_DestroyWindow(window);
        SDL_કાઢો_Error();
        પાછા ખાલી;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#જો !defined(SDL_PLATFORM_WINDOWS)
    જો (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#endif

    જો (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_CheckWindowPixelSizeChanged(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif

    SDL_ClearError();

    પાછા window;
}

SDL_Window *SDL_CreateWindow(અચલ અક્ષર *title, પૂર્ણાંક w, પૂર્ણાંક h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    જો (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_સંખ્યા, w);
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_સંખ્યા, h);
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_સંખ્યા, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    પાછા window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, પૂર્ણાંક offset_x, પૂર્ણાંક offset_y, પૂર્ણાંક w, પૂર્ણાંક h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    જો (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        પાછા ખાલી;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_X_સંખ્યા, offset_x);
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_Y_સંખ્યા, offset_y);
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_સંખ્યા, w);
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_સંખ્યા, h);
    SDL_Set_સંખ્યા_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_સંખ્યા, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    પાછા window;
}

સ્થિર bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    જો (!_this->ReconfigureWindow) {
        પાછા false;
    }

    અચલ SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    જો (graphics_flags & (graphics_flags - 1)) {
        પાછા SDL_SetError("Conflicting window flags specified");
    }

    જો ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        પાછા SDL_ContextNotSupported("OpenGL");
    }
    જો ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        પાછા SDL_ContextNotSupported("Vulkan");
    }
    જો ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        પાછા SDL_ContextNotSupported("Metal");
    }

    જો (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        જો (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            પાછા false;
        }
    } નહીંતર {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        જો (!_this->ReconfigureWindow(_this, window, 0)) {
            પાછા false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        જો (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        જો (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    જો (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(ખાલી);
        જો (!loaded_opengl) {
            પાછા false;
        }
    } નહીંતર જો (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(ખાલી);
        જો (!loaded_vulkan) {
            પાછા false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    જો (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        જો (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        જો (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        પાછા false;
    }

    window->flags |= graphics_flags;

    પાછા true;
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
    જો (graphics_flags & (graphics_flags - 1)) {
        પાછા SDL_SetError("Conflicting window flags specified");
    }

    જો ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        પાછા SDL_ContextNotSupported("OpenGL");
    }
    જો ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        પાછા SDL_ContextNotSupported("Vulkan");
    }
    જો ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        પાછા SDL_ContextNotSupported("Metal");
    }

    જો (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } નહીંતર {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    જો (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    જો (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        અચલ bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    જો ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        જો (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } નહીંતર {
            need_gl_unload = true;
        }
    } નહીંતર જો (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    જો ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        જો (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } નહીંતર {
            need_vulkan_unload = true;
        }
    } નહીંતર જો (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    જો (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    જો (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    જો (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    જો (need_gl_load) {
        જો (!SDL_GL_LoadLibrary(ખાલી)) {
            પાછા false;
        }
        loaded_opengl = true;
    }

    જો (need_vulkan_load) {
        જો (!SDL_Vulkan_LoadLibrary(ખાલી)) {
            પાછા false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    જો (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        જો (!_this->CreateSDLWindow(_this, window, 0)) {
            જો (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            જો (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            પાછા false;
        }
    }

    જો (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    જો (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    જો (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    જો (_this->SetWindowMinimumSize && (window->min_w || window->min_h)) {
        _this->SetWindowMinimumSize(_this, window);
    }

    જો (_this->SetWindowMaximumSize && (window->max_w || window->max_h)) {
        _this->SetWindowMaximumSize(_this, window);
    }

    જો (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    જો (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    પાછા true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    જો (!SDL_ReconfigureWindowInternal(window, flags)) {
        પાછા SDL_RecreateWindow(window, flags);
    }

    પાછા true;
}

bool SDL_HasWindows(શૂન્ય)
{
    પાછા _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    પાછા window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    જો (id) {
        માટે (window = _this->windows; window; window = window->next) {
            જો (window->id == id) {
                પાછા window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    પાછા ખાલી;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ખાલી);

    પાછા window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    જો (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    પાછા window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    પાછા window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, અચલ અક્ષર *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (title == window->title) {
        પાછા true;
    }
    જો (!title) {
        title = "";
    }
    જો (window->title && SDL_strcmp(title, window->title) == 0) {
        પાછા true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    જો (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    પાછા true;
}

અચલ અક્ષર *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    પાછા window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        પાછા SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    જો (!window->icon) {
        પાછા false;
    }

    જો (!_this->SetWindowIcon) {
        પાછા SDL_Unsupported();
    }

    પાછા _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, પૂર્ણાંક x, પૂર્ણાંક y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    અચલ પૂર્ણાંક w = window->last_size_pending ? window->pending.w : window->windowed.w;
    અચલ પૂર્ણાંક h = window->last_size_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    જો (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    જો (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    જો (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        જો (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } નહીંતર જો (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        જો (displayID == 0 || SDL_GetDisplayIndex(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        જો (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            જો (!SDL_GetDisplayBounds(displayID, &bounds)) {
                પાછા false;
            }
        }
        જો (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        જો (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } નહીંતર {
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
    જો (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    જો (_this->SetWindowPosition) {
        અચલ bool result = _this->SetWindowPosition(_this, window);
        જો (result) {
            SDL_SyncIfRequired(window);
        }
        પાછા result;
    }

    પાછા SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, પૂર્ણાંક *x, પૂર્ણાંક *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#ifdef SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#નહીંતર
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#endif
    જો (use_display_origin) {
        SDL_DisplayID displayID;

        જો (x) {
            *x = 0;
        }
        જો (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        જો (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            જો (x) {
                *x = bounds.x;
            }
            જો (y) {
                *y = bounds.y;
            }
        }
    } નહીંતર {
        અચલ bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        જો (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        જો (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    પાછા true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (!_this->SetWindowBordered) {
        પાછા SDL_Unsupported();
    }

    અચલ bool want = bordered;
    અચલ bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    જો (want != have) {
        જો (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } નહીંતર {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    પાછા true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (!_this->SetWindowResizable) {
        પાછા SDL_Unsupported();
    }

    અચલ bool want = resizable;
    અચલ bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    જો (want != have) {
        જો (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } નહીંતર {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    પાછા true;
}

bool SDL_Set_Window_Always_On_ટોચ(SDL_Window *window, bool on_ટોચ)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (!_this->Set_Window_Always_On_ટોચ) {
        પાછા SDL_Unsupported();
    }

    અચલ bool want = on_ટોચ;
    અચલ bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_ટોચ) != 0);
    જો (want != have) {
        જો (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_ટોચ;
        } નહીંતર {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_ટોચ;
        }
        _this->Set_Window_Always_On_ટોચ(_this, window, want);
    }

    પાછા true;
}

bool SDL_SetWindowSize(SDL_Window *window, પૂર્ણાંક w, પૂર્ણાંક h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        પાછા SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        પાછા SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    દશાંશ new_aspect = w / (દશાંશ)h;
    જો (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (પૂર્ણાંક)SDL_roundf(h * window->max_aspect);
    } નહીંતર જો (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (પૂર્ણાંક)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    જો (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    જો (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    જો (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    જો (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_size_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    જો (_this->SetWindowSize) {
        _this->SetWindowSize(_this, window);
        SDL_SyncIfRequired(window);
    } નહીંતર {
        પાછા SDL_Unsupported();
    }
    પાછા true;
}

bool SDL_GetWindowSize(SDL_Window *window, પૂર્ણાંક *w, પૂર્ણાંક *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    જો (w) {
        *w = window->w;
    }
    જો (h) {
        *h = window->h;
    }
    પાછા true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, દશાંશ min_aspect, દશાંશ max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    જો (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    પૂર્ણાંક w = window->last_size_pending ? window->pending.w : window->floating.w;
    પૂર્ણાંક h = window->last_size_pending ? window->pending.h : window->floating.h;
    પાછા SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, દશાંશ *min_aspect, દશાંશ *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    જો (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    પાછા true;
}

bool SDL_GetWindowBordersSize(SDL_Window *window, પૂર્ણાંક *ટોચ, પૂર્ણાંક *ડાબું, પૂર્ણાંક *bottom, પૂર્ણાંક *જમણું)
{
    પૂર્ણાંક dummy = 0;

    જો (!ટોચ) {
        ટોચ = &dummy;
    }
    જો (!ડાબું) {
        ડાબું = &dummy;
    }
    જો (!જમણું) {
        જમણું = &dummy;
    }
    જો (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *ટોચ = *ડાબું = *bottom = *જમણું = 0;

    CHECK_WINDOW_MAGIC(window, false);

    જો (!_this->GetWindowBordersSize) {
        પાછા SDL_Unsupported();
    }

    પાછા _this->GetWindowBordersSize(_this, window, ટોચ, ડાબું, bottom, જમણું);
}

bool SDL_GetWindowSizeInPixels(SDL_Window *window, પૂર્ણાંક *w, પૂર્ણાંક *h)
{
    પૂર્ણાંક filter;

    CHECK_WINDOW_MAGIC(window, false);

    જો (!w) {
        w = &filter;
    }

    જો (!h) {
        h = &filter;
    }

    જો (_this->GetWindowSizeInPixels) {
        _this->GetWindowSizeInPixels(_this, window, w, h);
    } નહીંતર {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        અચલ SDL_DisplayMode *mode;

        SDL_GetWindowSize(window, w, h);

        જો ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } નહીંતર {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        જો (mode) {
            *w = (પૂર્ણાંક)SDL_ceilf(*w * mode->pixel_density);
            *h = (પૂર્ણાંક)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    પાછા true;
}

bool SDL_SetWindowMinimumSize(SDL_Window *window, પૂર્ણાંક min_w, પૂર્ણાંક min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        પાછા SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        પાછા SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        પાછા SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    જો (_this->SetWindowMinimumSize) {
        _this->SetWindowMinimumSize(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    પૂર્ણાંક w = window->last_size_pending ? window->pending.w : window->floating.w;
    પૂર્ણાંક h = window->last_size_pending ? window->pending.h : window->floating.h;
    પાછા SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMinimumSize(SDL_Window *window, પૂર્ણાંક *min_w, પૂર્ણાંક *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    જો (min_w) {
        *min_w = window->min_w;
    }
    જો (min_h) {
        *min_h = window->min_h;
    }
    પાછા true;
}

bool SDL_SetWindowMaximumSize(SDL_Window *window, પૂર્ણાંક max_w, પૂર્ણાંક max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        પાછા SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        પાછા SDL_InvalidParamError("max_h");
    }

    જો ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        પાછા SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    જો (_this->SetWindowMaximumSize) {
        _this->SetWindowMaximumSize(_this, window);
    }

    // Ensure that window is not larger than maximal size
    પૂર્ણાંક w = window->last_size_pending ? window->pending.w : window->floating.w;
    પૂર્ણાંક h = window->last_size_pending ? window->pending.h : window->floating.h;
    પાછા SDL_SetWindowSize(window, w, h);
}

bool SDL_GetWindowMaximumSize(SDL_Window *window, પૂર્ણાંક *max_w, પૂર્ણાંક *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    જો (max_w) {
        *max_w = window->max_w;
    }
    જો (max_h) {
        *max_h = window->max_h;
    }
    પાછા true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    જો (!(window->flags & SDL_WINDOW_HIDDEN)) {
        પાછા true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    જો (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        પાછા true;
    }

    જો (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } નહીંતર {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    માટે (child = window->first_child; child; child = child->next_sibling) {
        જો (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            તોડો;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    પાછા true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        પાછા true;
    }

    // Hide all child windows
    માટે (child = window->first_child; child; child = child->next_sibling) {
        જો (child->flags & SDL_WINDOW_HIDDEN) {
            તોડો;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    અચલ SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    જો (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } નહીંતર {
        SDL_SetMouseFocus(ખાલી);
        SDL_SetKeyboardFocus(ખાલી);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    પાછા true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        પાછા true;
    }
    જો (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    પાછા true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (!_this->MaximizeWindow) {
        પાછા SDL_Unsupported();
    }

    જો (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        પાછા SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        પાછા true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    પાછા true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (!_this->MinimizeWindow) {
        પાછા SDL_Unsupported();
    }

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        પાછા true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    પાછા true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (!_this->RestoreWindow) {
        પાછા SDL_Unsupported();
    }

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        પાછા true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    પાછા true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        જો (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } નહીંતર {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        પાછા true;
    }

    જો (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    result = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    જો (!fullscreen || !result) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    જો (result) {
        SDL_SyncIfRequired(window);
    }

    પાછા result;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (_this->SyncWindow) {
        પાછા _this->SyncWindow(_this, window);
    } નહીંતર {
        પાછા true;
    }
}

સ્થિર bool ShouldAttemptTextureFramebuffer(શૂન્ય)
{
    અચલ અક્ષર *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    જો (!_this->CreateWindowFramebuffer) {
        પાછા true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    જો (hint && *hint) {
        જો (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } નહીંતર {
            attempt_texture_framebuffer = true;
        }
    } નહીંતર {
        જો (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } નહીંતર {
            attempt_texture_framebuffer = false;
        }
    }
    પાછા attempt_texture_framebuffer;
}

સ્થિર SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    શૂન્ય *pixels = ખાલી;
    પૂર્ણાંક pitch = 0;
    bool created_framebuffer = false;
    પૂર્ણાંક w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    જો (!_this->checked_texture_framebuffer) {
        જો (ShouldAttemptTextureFramebuffer()) {
            જો (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } નહીંતર {
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

    જો (!created_framebuffer) {
        જો (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            પાછા ખાલી;
        }

        જો (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            પાછા ખાલી;
        }
    }

    જો (window->surface) {
        // We may have gone recursive and already created the surface
        પાછા window->surface;
    }

    પાછા SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    પાછા window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ખાલી);

    જો (!window->surface_valid) {
        જો (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = ખાલી;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        જો (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    પાછા window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, પૂર્ણાંક vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (!_this->SetWindowFramebufferVSync) {
        પાછા SDL_Unsupported();
    }
    પાછા _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, પૂર્ણાંક *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (!_this->GetWindowFramebufferVSync) {
        પાછા SDL_Unsupported();
    }
    પાછા _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_GetWindowSizeInPixels(window, &full_rect.w, &full_rect.h);

    પાછા SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, અચલ SDL_Rect *rects,
                                 પૂર્ણાંક numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (!window->surface_valid) {
        પાછા SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    પાછા _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = ખાલી;
        window->surface_valid = false;
    }

    જો (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        જો (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    પાછા true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, દશાંશ opacity)
{
    bool result;

    CHECK_WINDOW_MAGIC(window, false);

    જો (!_this->SetWindowOpacity) {
        પાછા SDL_Unsupported();
    }

    જો (opacity < 0.0f) {
        opacity = 0.0f;
    } નહીંતર જો (opacity > 1.0f) {
        opacity = 1.0f;
    }

    result = _this->SetWindowOpacity(_this, window, opacity);
    જો (result) {
        window->opacity = opacity;
    }

    પાછા result;
}

દશાંશ SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    પાછા window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    જો (window == parent) {
        પાછા SDL_SetError("Cannot set the parent of a window to itself.");
    }

    જો (!_this->SetWindowParent) {
        પાછા SDL_Unsupported();
    }

    જો (window->flags & SDL_WINDOW_MODAL) {
        પાછા SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    જો (window->parent == parent) {
        પાછા true;
    }

    અચલ bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : ખાલી);

    પાછા ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (!_this->SetWindowModal) {
        પાછા SDL_Unsupported();
    }

    જો (modal) {
        જો (!window->parent) {
            પાછા SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } નહીંતર જો (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } નહીંતર {
        પાછા true; // Already not modal, so nothing to do.
    }

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        પાછા true;
    }

    પાછા _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_આગત_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    જ્યારે (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        જો (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_આગત_FOCUS);
        }
    }

    *new_focus = focus;
    પાછા set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    માટે (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    માટે (w = current_focus; w != toplevel_parent; w = w->parent) {
        જો (w == window) {
            found_higher_focus = true;
            તોડો;
        }
    }

    પાછા !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    અચલ bool want = (focusable != false); // normalize the flag.
    અચલ bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    જો ((want != have) && (_this->SetWindowFocusable)) {
        જો (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } નહીંતર {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        જો (!_this->SetWindowFocusable(_this, window, want)) {
            પાછા false;
        }
    }

    પાછા true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    અચલ bool want = (fill != false); // normalize the flag.
    અચલ bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    જો ((want != have) && (_this->SetWindowFillDocument)) {
        જો (!_this->SetWindowFillDocument(_this, window, want)) {
            પાછા false;
        } નહીંતર જો (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } નહીંતર {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    પાછા true;
}

શૂન્ય SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    જો (window->flags & SDL_WINDOW_આગત_FOCUS) {
        જો (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } નહીંતર {
            mouse_grabbed = false;
        }

        જો (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } નહીંતર {
            keyboard_grabbed = false;
        }
    } નહીંતર {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    જો (mouse_grabbed || keyboard_grabbed) {
        જો (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            જો (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            જો (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } નહીંતર જો (_this->grabbed_window == window) {
        _this->grabbed_window = ખાલી; // ungrabbing input.
    }

    જો (_this->SetWindowMouseGrab) {
        જો (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    જો (_this->SetWindowKeyboardGrab) {
        જો (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    જો (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = ખાલી;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        જો (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } નહીંતર {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        પાછા true;
    }

    જો (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        પાછા true;
    }
    જો (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } નહીંતર {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    જો (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        પાછા false;
    }
    પાછા true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (window->flags & SDL_WINDOW_HIDDEN) {
        જો (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } નહીંતર {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        પાછા true;
    }

    જો (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        પાછા true;
    }
    જો (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } નહીંતર {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    જો (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        પાછા false;
    }
    પાછા true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    પાછા window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    પાછા window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(શૂન્ય)
{
    જો (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        પાછા _this->grabbed_window;
    } નહીંતર {
        પાછા ખાલી;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, અચલ SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (!_this->SetWindowMouseRect) {
        પાછા SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    જો (!rect) {
        rect = &zero;
    }

    જો (SDL_memcmp(&window->mouse_rect, rect, કદ(*rect)) == 0) {
        પાછા true;
    }
    SDL_memcpy(&window->mouse_rect, rect, કદ(*rect));

    પાછા _this->SetWindowMouseRect(_this, window);
}

અચલ SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ખાલી);

    જો (SDL_RectEmpty(&window->mouse_rect)) {
        પાછા ખાલી;
    } નહીંતર {
        પાછા &window->mouse_rect;
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

    જો (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        પાછા true;
    }

    જો (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } નહીંતર {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    જો (!SDL_UpdateRelativeMouseMode()) {
        જો (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } નહીંતર {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        પાછા false;
    }
    પાછા true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        પાછા true;
    } નહીંતર {
        પાછા false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (_this->FlashWindow) {
        પાછા _this->FlashWindow(_this, window, operation);
    }

    પાછા SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        પાછા SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    જો (_this->ApplyWindowProgress) {
        જો (!_this->ApplyWindowProgress(_this, window)) {
            પાછા false;
        }
    }

    પાછા true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    પાછા window->progress_state;
}

bool SDL_Set_Window_Progress_કિંમત(SDL_Window *window, દશાંશ કિંમત)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    કિંમત = SDL_clamp(કિંમત, 0.0f, 1.f);

    window->progress_કિંમત = કિંમત;

    જો (_this->ApplyWindowProgress) {
        જો (!_this->ApplyWindowProgress(_this, window)) {
            પાછા false;
        }
    }

    પાછા true;
}

દશાંશ SDL_Get_Window_Progress_કિંમત(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    પાછા window->progress_કિંમત;
}

શૂન્ય SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

શૂન્ય SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

શૂન્ય SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    જો (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        અચલ bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        જો (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_ઉપલું_density_modes = false;

            જો (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_ઉપલું_density_modes = true;
            }
            અચલ bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_ઉપલું_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            જો (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } નહીંતર {
            SDL_zero(window->current_fullscreen_mode);
        }

        જો (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_CheckWindowPixelSizeChanged(window);
}

શૂન્ય SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

શૂન્ય SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_CheckWindowPixelSizeChanged(window);
    SDL_CheckWindowSafeAreaChanged(window);

    જો ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, ખાલી);
        જો (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

શૂન્ય SDL_CheckWindowPixelSizeChanged(SDL_Window *window)
{
    પૂર્ણાંક pixel_w = 0, pixel_h = 0;

    SDL_GetWindowSizeInPixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

શૂન્ય SDL_OnWindowPixelSizeChanged(SDL_Window *window)
{
    window->surface_valid = false;
}

શૂન્ય SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    જો (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } નહીંતર {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

સ્થિર શૂન્ય SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_ડાબું;
    rect.y = window->safe_inset_ટોચ;
    rect.w = window->w - (window->safe_inset_જમણું + window->safe_inset_ડાબું);
    rect.h = window->h - (window->safe_inset_ટોચ + window->safe_inset_bottom);
    જો (SDL_memcmp(&rect, &window->safe_rect, કદ(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

શૂન્ય SDL_SetWindowSafeAreaInsets(SDL_Window *window, પૂર્ણાંક ડાબું, પૂર્ણાંક જમણું, પૂર્ણાંક ટોચ, પૂર્ણાંક bottom)
{
    window->safe_inset_ડાબું = ડાબું;
    window->safe_inset_જમણું = જમણું;
    window->safe_inset_ટોચ = ટોચ;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    જો (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    જો (rect) {
        જો (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } નહીંતર {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    પાછા true;
}

શૂન્ય SDL_OnWindowMinimized(SDL_Window *window)
{
    જો (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

શૂન્ય SDL_OnWindowMaximized(SDL_Window *window)
{
}

શૂન્ય SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    જો (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

શૂન્ય SDL_OnWindowEnter(SDL_Window *window)
{
    જો (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

શૂન્ય SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

શૂન્ય SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    જો (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

સ્થિર bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    અચલ અક્ષર *hint;

    જો (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        પાછા false;
    }

#જો defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    જો (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        જો (Cocoa_IsShowingModalDialog(window)) {
            પાછા false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } નહીંતર જો (Cocoa_IsWindowInFullscreenSpace(window)) {
            પાછા false;
        }
    }
#endif

#ifdef SDL_PLATFORM_ANDROID
    {
        બાહ્ય bool Android_JNI_ShouldMinimizeOnFocusLoss(શૂન્ય);
        જો (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            પાછા false;
        }
    }
#endif

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    જો (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        જો (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            પાછા true;
        } નહીંતર {
            પાછા false;
        }
    }
    પાછા SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

શૂન્ય SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    જો (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(શૂન્ય)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    જો (focus) {
        // Get the toplevel parent window.
        જ્યારે (focus->parent) {
            focus = focus->parent;
        }
    }

    પાછા focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->અંક_renderers + 1) * કદ(*renderers));
    જો (!renderers) {
        પાછા false;
    }

    window->renderers = renderers;
    window->renderers[window->અંક_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    પાછા true;
}

શૂન્ય SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    માટે (પૂર્ણાંક i = 0; i < window->અંક_renderers; ++i) {
        જો (window->renderers[i] == renderer) {
            જો (i < (window->અંક_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->અંક_renderers - i - 1) * કદ(window->renderers[i]));
            }
            --window->અંક_renderers;
            તોડો;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    જો (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, ખાલી) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

શૂન્ય SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    જ્યારે (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    જો (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    જો (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_આગત_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    જો (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    માટે (પૂર્ણાંક i = 0; i < _this->અંક_displays; ++i) {
        જો (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = ખાલી;
        }
    }

    // Make sure this window no longer has focus
    જો (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(ખાલી);
    }
    જો ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    જો (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(ખાલી);
    }

    // Make no context current if this is the current context window
    જો (window->flags & SDL_WINDOW_OPENGL) {
        જો (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, ખાલી);
        }
    }

    જો (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    જો (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    જો (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    જો (_this->grabbed_window == window) {
        _this->grabbed_window = ખાલી; // ungrabbing input.
    }

    જો (_this->current_glwin == window) {
        _this->current_glwin = ખાલી;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, ખાલી);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, ખાલી);

    // Unlink the window from the global window list
    જો (window->next) {
        window->next->prev = window->prev;
    }
    જો (window->prev) {
        window->prev->next = window->next;
    } નહીંતર {
        _this->windows = window->next;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#ifdef SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#endif
}

bool SDL_ScreenSaverEnabled(શૂન્ય)
{
    જો (!_this) {
        પાછા true;
    }
    પાછા !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(શૂન્ય)
{
    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }
    જો (!_this->suspend_screensaver) {
        પાછા true;
    }
    _this->suspend_screensaver = false;
    જો (_this->SuspendScreenSaver) {
        પાછા _this->SuspendScreenSaver(_this);
    }

    પાછા SDL_Unsupported();
}

bool SDL_DisableScreenSaver(શૂન્ય)
{
    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }
    જો (_this->suspend_screensaver) {
        પાછા true;
    }
    _this->suspend_screensaver = true;
    જો (_this->SuspendScreenSaver) {
        પાછા _this->SuspendScreenSaver(_this);
    }

    પાછા SDL_Unsupported();
}

શૂન્ય SDL_QuitVideo(શૂન્ય)
{
    પૂર્ણાંક i;

    જો (!_this) {
        પાછા;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#જો 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#endif
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    જ્યારે (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    જો (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    જો (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    માટે (i = _this->અંક_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->અંક_displays == 0);
    SDL_free(_this->displays);
    _this->displays = ખાલી;

    SDL_CancelClipboardData(0);

    જો (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = ખાલી;
    }
    _this->મુક્ત(_this);
    _this = ખાલી;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(અચલ અક્ષર *path)
{
    bool result;

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }
    જો (_this->gl_config.driver_loaded) {
        જો (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            પાછા SDL_SetError("OpenGL library already loaded");
        }
        result = true;
    } નહીંતર {
        જો (!_this->GL_LoadLibrary) {
            પાછા SDL_DllNotSupported("OpenGL");
        }
        result = _this->GL_LoadLibrary(_this, path);
    }
    જો (result) {
        ++_this->gl_config.driver_loaded;
    } નહીંતર {
        જો (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    પાછા result;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(અચલ અક્ષર *proc)
{
    SDL_FunctionPointer func;

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    func = ખાલી;
    જો (_this->GL_GetProcAddress) {
        જો (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } નહીંતર {
            SDL_SetError("No GL driver has been loaded");
        }
    } નહીંતર {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    પાછા func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(અચલ અક્ષર *proc)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    func = ખાલી;

    જો (_this->egl_data) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } નહીંતર {
        SDL_SetError("No EGL library has been loaded");
    }

    પાછા func;
#નહીંતર
    SDL_SetError("SDL was not built with EGL support");
    પાછા ખાલી;
#endif
}

શૂન્ય SDL_GL_UnloadLibrary(શૂન્ય)
{
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા;
    }
    જો (_this->gl_config.driver_loaded > 0) {
        જો (--_this->gl_config.driver_loaded > 0) {
            પાછા;
        }
        જો (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#જો defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
પ્રકારવ્યાખ્યા GLenum (APIENTRY* PFNGLGETERRORPROC) (શૂન્ય);
પ્રકારવ્યાખ્યા શૂન્ય (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
પ્રકારવ્યાખ્યા અચલ GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
પ્રકારવ્યાખ્યા શૂન્ય (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#ifndef SDL_VIDEO_OPENGL
પ્રકારવ્યાખ્યા અચલ GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
#endif

સ્થિર SDL_INLINE bool isAtLeastGL3(અચલ અક્ષર *verstr)
{
    પાછા verstr && (SDL_atoi(verstr) >= 3);
}
#endif // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(અચલ અક્ષર *extension)
{
#જો defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    અચલ અક્ષર *extensions;
    અચલ અક્ષર *start;
    અચલ અક્ષર *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    જો (where || *extension == '\0') {
        પાછા false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    જો (start && *start == '0') {
        પાછા false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    જો (!glGetStringFunc) {
        પાછા false;
    }

    જો (isAtLeastGL3((અચલ અક્ષર *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint અંક_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        જો ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            પાછા false;
        }

#ifndef GL_અંક_EXTENSIONS
#define GL_અંક_EXTENSIONS 0x821D
#endif
        glGetIntegervFunc(GL_અંક_EXTENSIONS, &અંક_exts);
        માટે (i = 0; i < અંક_exts; i++) {
            અચલ અક્ષર *thisext = (અચલ અક્ષર *)glGetStringiFunc(GL_EXTENSIONS, i);
            જો (SDL_strcmp(thisext, extension) == 0) {
                પાછા true;
            }
        }

        પાછા false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (અચલ અક્ષર *)glGetStringFunc(GL_EXTENSIONS);
    જો (!extensions) {
        પાછા false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    માટે (;;) {
        where = SDL_strstr(start, extension);
        જો (!where) {
            તોડો;
        }

        terminator = where + SDL_strlen(extension);
        જો (where == extensions || *(where - 1) == ' ') {
            જો (*terminator == ' ' || *terminator == '\0') {
                પાછા true;
            }
        }

        start = terminator;
    }
    પાછા false;
#નહીંતર
    પાછા false;
#endif
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
શૂન્ય SDL_GL_DeduceMaxSupportedESProfile(પૂર્ણાંક *major, પૂર્ણાંક *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#જો defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    જો (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } નહીંતર જો (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } નહીંતર જો (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } નહીંતર {
        *major = 2;
        *minor = 0;
    }
#endif
}

શૂન્ય SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   શૂન્ય *userdata)
{
    જો (!_this) {
        પાછા;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

શૂન્ય SDL_GL_ResetAttributes(શૂન્ય)
{
    જો (!_this) {
        પાછા;
    }

    _this->egl_platformattrib_callback = ખાલી;
    _this->egl_surfaceattrib_callback = ખાલી;
    _this->egl_contextattrib_callback = ખાલી;
    _this->egl_attrib_callback_userdata = ખાલી;

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
#અથવાજો defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#અથવાજો defined(SDL_VIDEO_OPENGL_ES)
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

    જો (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, પૂર્ણાંક કિંમત)
{
#જો defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool result;

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }
    result = true;
    પસંદગી (attr) {
    સ્થિતિ SDL_GL_RED_SIZE:
        _this->gl_config.red_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_GREEN_SIZE:
        _this->gl_config.green_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_BLUE_SIZE:
        _this->gl_config.blue_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_ALPHA_SIZE:
        _this->gl_config.alpha_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_buffer = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_BUFFER_SIZE:
        _this->gl_config.buffer_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_DEPTH_SIZE:
        _this->gl_config.depth_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_STENCIL_SIZE:
        _this->gl_config.stencil_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_ACCUM_RED_SIZE:
        _this->gl_config.accum_red_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_ACCUM_GREEN_SIZE:
        _this->gl_config.accum_green_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_ACCUM_BLUE_SIZE:
        _this->gl_config.accum_blue_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_ACCUM_ALPHA_SIZE:
        _this->gl_config.accum_alpha_size = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_STEREO:
        _this->gl_config.stereo = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_FLAGS:
        જો (કિંમત & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            result = SDL_SetError("Unknown OpenGL context flag %d", કિંમત);
            તોડો;
        }
        _this->gl_config.flags = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_PROFILE_MASK:
        જો (કિંમત != 0 &&
            કિંમત != SDL_GL_CONTEXT_PROFILE_CORE &&
            કિંમત != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            કિંમત != SDL_GL_CONTEXT_PROFILE_ES) {
            result = SDL_SetError("Unknown OpenGL context profile %d", કિંમત);
            તોડો;
        }
        _this->gl_config.profile_mask = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = કિંમત;
        તોડો;
    સ્થિતિ SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = કિંમત;
        તોડો;
    મૂળભૂત:
        result = SDL_SetError("Unknown OpenGL attribute");
        તોડો;
    }
    પાછા result;
#નહીંતર
    પાછા SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, પૂર્ણાંક *કિંમત)
{
#જો defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
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
    GLenum attachment = GL_BACK_ડાબું;
    GLenum attachmentattrib = 0;
#endif

    CHECK_PARAM(!કિંમત) {
        પાછા SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *કિંમત = 0;

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    પસંદગી (attr) {
    સ્થિતિ SDL_GL_RED_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE;
#endif
        attrib = GL_RED_BITS;
        તોડો;
    સ્થિતિ SDL_GL_BLUE_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE;
#endif
        attrib = GL_BLUE_BITS;
        તોડો;
    સ્થિતિ SDL_GL_GREEN_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE;
#endif
        attrib = GL_GREEN_BITS;
        તોડો;
    સ્થિતિ SDL_GL_ALPHA_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE;
#endif
        attrib = GL_ALPHA_BITS;
        તોડો;
    સ્થિતિ SDL_GL_DOUBLEBUFFER:
#ifdef SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        તોડો;
#નહીંતર
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *કિંમત = _this->gl_config.double_buffer;
        પાછા true;
#endif
    સ્થિતિ SDL_GL_DEPTH_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE;
#endif
        attrib = GL_DEPTH_BITS;
        તોડો;
    સ્થિતિ SDL_GL_STENCIL_SIZE:
#ifdef SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE;
#endif
        attrib = GL_STENCIL_BITS;
        તોડો;
#ifdef SDL_VIDEO_OPENGL
    સ્થિતિ SDL_GL_ACCUM_RED_SIZE:
        attrib = GL_ACCUM_RED_BITS;
        તોડો;
    સ્થિતિ SDL_GL_ACCUM_GREEN_SIZE:
        attrib = GL_ACCUM_GREEN_BITS;
        તોડો;
    સ્થિતિ SDL_GL_ACCUM_BLUE_SIZE:
        attrib = GL_ACCUM_BLUE_BITS;
        તોડો;
    સ્થિતિ SDL_GL_ACCUM_ALPHA_SIZE:
        attrib = GL_ACCUM_ALPHA_BITS;
        તોડો;
    સ્થિતિ SDL_GL_STEREO:
        attrib = GL_STEREO;
        તોડો;
#નહીંતર
    સ્થિતિ SDL_GL_ACCUM_RED_SIZE:
    સ્થિતિ SDL_GL_ACCUM_GREEN_SIZE:
    સ્થિતિ SDL_GL_ACCUM_BLUE_SIZE:
    સ્થિતિ SDL_GL_ACCUM_ALPHA_SIZE:
    સ્થિતિ SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *કિંમત = 0;
        પાછા true;
#endif
    સ્થિતિ SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        તોડો;
    સ્થિતિ SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        તોડો;
    સ્થિતિ SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        તોડો;
    સ્થિતિ SDL_GL_BUFFER_SIZE:
    {
        પૂર્ણાંક rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        જો (!SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rsize)) {
            પાછા false;
        }
        જો (!SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gsize)) {
            પાછા false;
        }
        જો (!SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bsize)) {
            પાછા false;
        }
        જો (!SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &asize)) {
            પાછા false;
        }

        *કિંમત = rsize + gsize + bsize + asize;
        પાછા true;
    }
    સ્થિતિ SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *કિંમત = (_this->gl_config.accelerated != 0);
        પાછા true;
    }
    સ્થિતિ SDL_GL_RETAINED_BACKING:
    {
        *કિંમત = _this->gl_config.retained_backing;
        પાછા true;
    }
    સ્થિતિ SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *કિંમત = _this->gl_config.major_version;
        પાછા true;
    }
    સ્થિતિ SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *કિંમત = _this->gl_config.minor_version;
        પાછા true;
    }
    સ્થિતિ SDL_GL_CONTEXT_FLAGS:
    {
        *કિંમત = _this->gl_config.flags;
        પાછા true;
    }
    સ્થિતિ SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *કિંમત = _this->gl_config.profile_mask;
        પાછા true;
    }
    સ્થિતિ SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *કિંમત = _this->gl_config.share_with_current_context;
        પાછા true;
    }
    સ્થિતિ SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *કિંમત = _this->gl_config.framebuffer_srgb_capable;
        પાછા true;
    }
    સ્થિતિ SDL_GL_CONTEXT_NO_ERROR:
    {
        *કિંમત = _this->gl_config.no_error;
        પાછા true;
    }
    સ્થિતિ SDL_GL_EGL_PLATFORM:
    {
        *કિંમત = _this->gl_config.egl_platform;
        પાછા true;
    }
    સ્થિતિ SDL_GL_FLOATBUFFERS:
    {
        જો (_this->gl_config.HAS_GL_ARB_color_buffer_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            તોડો;
        } નહીંતર {
            પાછા 0;
        }
    }
    મૂળભૂત:
        પાછા SDL_SetError("Unknown OpenGL attribute");
    }

#ifdef SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    જો (!glGetStringFunc) {
        પાછા false;
    }

    જો (attachmentattrib && isAtLeastGL3((અચલ અક્ષર *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        જો (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        જો (glGetFramebufferAttachmentParameterivFunc) {
            જો (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            જો (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            જો (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)કિંમત);
            } નહીંતર {
                *કિંમત = 0;
            }
            જો (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } નહીંતર {
            પાછા false;
        }
    } નહીંતર
#endif
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        જો (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)કિંમત);
        } નહીંતર {
            પાછા false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    જો (!glGetErrorFunc) {
        પાછા false;
    }

    error = glGetErrorFunc();
    જો (error != GL_NO_ERROR) {
        જો (error == GL_INVALID_ENUM) {
            પાછા SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } નહીંતર જો (error == GL_INVALID_કિંમત) {
            પાછા SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        પાછા SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    જો (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *કિંમત = (*કિંમત == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    પાછા true;
#નહીંતર
    પાછા SDL_Unsupported();
#endif // SDL_VIDEO_OPENGL
}

#define NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = ખાલી;
    CHECK_WINDOW_MAGIC(window, ખાલી);

    જો (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        પાછા ખાલી;
    }

#જો defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    પૂર્ણાંક srgb_requested = -1;
    અચલ અક્ષર *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    જો (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#endif

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    જો (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, ખાલી);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, ખાલી);
    }

#જો defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    જો (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        જો (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            જો (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } નહીંતર {
                supported = isAtLeastGL3((અચલ અક્ષર *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            જો (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#endif

    પાછા ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool result;

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }

    જો (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        પાછા true;
    }

    જો (!context) {
        window = ખાલી;
    } નહીંતર જો (window) {
        CHECK_WINDOW_MAGIC(window, false);

        જો (!(window->flags & SDL_WINDOW_OPENGL)) {
            પાછા SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } નહીંતર જો (!_this->gl_allow_no_surface) {
        પાછા SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    result = _this->GL_MakeCurrent(_this, window, context);
    જો (result) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, ખાલી);
        SDL_SetTLS(&_this->current_glctx_tls, context, ખાલી);
    }
    પાછા result;
}

SDL_Window *SDL_GL_GetCurrentWindow(શૂન્ય)
{
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    પાછા (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(શૂન્ય)
{
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    પાછા (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(શૂન્ય)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા EGL_NO_DISPLAY;
    }
    જો (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        પાછા EGL_NO_DISPLAY;
    }
    પાછા _this->egl_data->egl_display;
#નહીંતર
    SDL_SetError("SDL was not built with EGL support");
    પાછા ખાલી;
#endif
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(શૂન્ય)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    જો (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        પાછા ખાલી;
    }
    પાછા _this->egl_data->egl_config;
#નહીંતર
    SDL_SetError("SDL was not built with EGL support");
    પાછા ખાલી;
#endif
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#ifdef SDL_VIDEO_OPENGL_EGL
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    જો (!_this->egl_data) {
        SDL_SetError("There is no current EGL display");
        પાછા ખાલી;
    }
    જો (_this->GL_GetEGLSurface) {
        પાછા _this->GL_GetEGLSurface(_this, window);
    }
    પાછા ખાલી;
#નહીંતર
    SDL_SetError("SDL was not built with EGL support");
    પાછા ખાલી;
#endif
}

bool SDL_GL_SetSwapInterval(પૂર્ણાંક interval)
{
    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    } નહીંતર જો (SDL_GL_GetCurrentContext() == ખાલી) {
        પાછા SDL_SetError("No OpenGL context has been made current");
    } નહીંતર જો (_this->GL_SetSwapInterval) {
        પાછા _this->GL_SetSwapInterval(_this, interval);
    } નહીંતર {
        પાછા SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(પૂર્ણાંક *interval)
{
    CHECK_PARAM(!interval) {
       પાછા SDL_InvalidParamError("interval");
    }

    *interval = 0;

    જો (!_this) {
        પાછા SDL_SetError("no video driver");
    } નહીંતર જો (SDL_GL_GetCurrentContext() == ખાલી) {
        પાછા SDL_SetError("no current context");
    } નહીંતર જો (_this->GL_GetSwapInterval) {
        પાછા _this->GL_GetSwapInterval(_this, interval);
    } નહીંતર {
        પાછા SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (!(window->flags & SDL_WINDOW_OPENGL)) {
        પાછા SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    જો (SDL_GL_GetCurrentWindow() != window) {
        પાછા SDL_SetError("The specified window has not been made current");
    }

    પાછા _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        પાછા SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        પાછા SDL_InvalidParamError("context");
    }

    જો (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(ખાલી, ખાલી);
    }

    પાછા _this->GL_DestroyContext(_this, context);
}

#જો 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
સ્થિર શૂન્ય Create_Mask_From_Color_ચાવી_Or_Alpha(SDL_Surface *icon, Uint8 *mask, પૂર્ણાંક flags)
{
    પૂર્ણાંક x, y;
    Uint32 colorkey;
#define SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    પસંદગી (SDL_BYTESPERPIXEL(icon->format)) {
    સ્થિતિ 1:
        {
            Uint8 *pixels;
            માટે (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                માટે (x = 0; x < icon->w; ++x) {
                    જો (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        તોડો;

    સ્થિતિ 2:
        {
            Uint16 *pixels;
            માટે (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                માટે (x = 0; x < icon->w; ++x) {
                    જો ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } નહીંતર જો ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        તોડો;

    સ્થિતિ 4:
        {
            Uint32 *pixels;
            માટે (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                માટે (x = 0; x < icon->w; ++x) {
                    જો ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } નહીંતર જો ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        તોડો;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
શૂન્ય SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    જો (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        જો (mask == ખાલી) {
            પૂર્ણાંક mask_len = icon->h * (icon->w + 7) / 8;
            પૂર્ણાંક flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            જો (mask == ખાલી) {
                પાછા;
            }
            SDL_memset(mask, ~0, mask_len);
            જો (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            જો (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            જો (flags) {
                Create_Mask_From_Color_ચાવી_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } નહીંતર {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#endif

SDL_Text_આગત_Type SDL_Get_Text_આગત_Type(SDL_PropertiesID props)
{
    પાછા (SDL_Text_આગત_Type)SDL_Get_સંખ્યા_Property(props, SDL_PROP_TEXTINPUT_TYPE_સંખ્યા, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_આગત_Capitalization(SDL_PropertiesID props)
{
    જો (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_સંખ્યા)) {
        પાછા (SDL_Capitalization)SDL_Get_સંખ્યા_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_સંખ્યા, SDL_CAPITALIZE_NONE);
    }

    પસંદગી (SDL_Get_Text_આગત_Type(props)) {
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT:
        પાછા SDL_CAPITALIZE_SENTENCES;
    સ્થિતિ SDL_TEXTINPUT_TYPE_TEXT_NAME:
        પાછા SDL_CAPITALIZE_શબ્દો;
    મૂળભૂત:
        પાછા SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_આગત_Autocorrect(SDL_PropertiesID props)
{
    પાછા SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_આગત_Multiline(SDL_PropertiesID props)
{
    જો (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        પાછા SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    જો (SDL_GetHintBoolean(SDL_HINT_RETURN_ચાવી_HIDES_IME, false)) {
        પાછા false;
    } નહીંતર {
        પાછા true;
    }
}

સ્થિર bool AutoShowingScreenKeyboard(શૂન્ય)
{
    અચલ અક્ષર *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    જો (!hint) {
        // This hint is currently only used by the X11 video driver
        જો (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    જો (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        પાછા true;
    } નહીંતર {
        પાછા false;
    }
}

bool SDL_Start_Text_આગત(SDL_Window *window)
{
    પાછા SDL_Start_Text_આગત_With_Properties(window, 0);
}

bool SDL_Start_Text_આગત_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (window->text_આગત_props) {
        SDL_DestroyProperties(window->text_આગત_props);
        window->text_આગત_props = 0;
    }

    જો (props) {
        window->text_આગત_props = SDL_CreateProperties();
        જો (!window->text_આગત_props) {
            પાછા false;
        }
        જો (!SDL_CopyProperties(props, window->text_આગત_props)) {
            પાછા false;
        }
    }

    જો (_this->Set_Text_આગત_Properties) {
        _this->Set_Text_આગત_Properties(_this, window, props);
    }

    જો (!window->text_આગત_active) {
        // Start the text input system
        જો (_this->Start_Text_આગત) {
            જો (!_this->Start_Text_આગત(_this, window, props)) {
                પાછા false;
            }
        }
        window->text_આગત_active = true;
    }

    // Show the on-screen keyboard, if desired
    જો (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        જો (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    પાછા true;
}

bool SDL_Text_આગત_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    પાછા window->text_આગત_active;
}

bool SDL_Stop_Text_આગત(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (window->text_આગત_active) {
        // Stop the text input system
        જો (_this->Stop_Text_આગત) {
            _this->Stop_Text_આગત(_this, window);
        }
        window->text_આગત_active = false;
    }

    // Hide the on-screen keyboard, if desired
    જો (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        જો (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    પાછા true;
}

bool SDL_Set_Text_આગત_Area(SDL_Window *window, અચલ SDL_Rect *rect, પૂર્ણાંક cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (rect) {
        SDL_copyp(&window->text_આગત_rect, rect);
        window->text_આગત_cursor = cursor;
    } નહીંતર {
        SDL_zero(window->text_આગત_rect);
        window->text_આગત_cursor = 0;
    }

    જો (_this && _this->Update_Text_આગત_Area) {
        જો (!_this->Update_Text_આગત_Area(_this, window)) {
            પાછા false;
        }
    }
    પાછા true;
}

bool SDL_Get_Text_આગત_Area(SDL_Window *window, SDL_Rect *rect, પૂર્ણાંક *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (rect) {
        SDL_copyp(rect, &window->text_આગત_rect);
    }
    જો (cursor) {
        *cursor = window->text_આગત_cursor;
    }
    પાછા true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (_this->ClearComposition) {
        પાછા _this->ClearComposition(_this, window);
    }
    પાછા true;
}

bool SDL_HasScreenKeyboardSupport(શૂન્ય)
{
    જો (_this && _this->HasScreenKeyboardSupport) {
        પાછા _this->HasScreenKeyboardSupport(_this);
    }
    પાછા false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    પાછા _this->screen_keyboard_shown;
}

શૂન્ય SDL_SendScreenKeyboardShown(શૂન્ય)
{
    જો (!_this || _this->screen_keyboard_shown) {
        પાછા;
    }

    _this->screen_keyboard_shown = true;

    જો (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ધકેલો_Event(&event);
    }
}

શૂન્ય SDL_SendScreenKeyboardHidden(શૂન્ય)
{
    જો (!_this || !_this->screen_keyboard_shown) {
        પાછા;
    }

    _this->screen_keyboard_shown = false;

    જો (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ધકેલો_Event(&event);
    }
}

પૂર્ણાંક SDL_Get_Message_Box_ગણતરી(શૂન્ય)
{
    પાછા SDL_GetAtomicInt(&SDL_messagebox_ગણતરી);
}

bool SDL_ShowMessageBox(અચલ SDL_MessageBoxData *messageboxdata, પૂર્ણાંક *buttonID)
{
    પૂર્ણાંક dummybutton;
    bool result = false;
    bool show_cursor_prev;
    SDL_Window *current_window;
    SDL_MessageBoxData mbdata;

    CHECK_PARAM(!messageboxdata) {
        પાછા SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        પાછા SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    અક્ષર *titlecpy = ખાલી;
    અક્ષર *msgcpy = ખાલી;
    જો (messageboxdata->title) {
        અચલ size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(અક્ષર, slen, &titleisstack);
        જો (!titlecpy) {
            પાછા false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    જો (messageboxdata->message) {
        અચલ size_t slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(અક્ષર, slen, &msgisstack);
        જો (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            પાછા false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (શૂન્ય)SDL_AtomicIncRef(&SDL_messagebox_ગણતરી);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    જો (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, કદ(*messageboxdata));
    mbdata.title = titlecpy;
    જો (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    જો (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    જો (_this && _this->ShowMessageBox) {
        result = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } નહીંતર {
        // It's completely fine to call this function before video is initialized
        અચલ અક્ષર *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        જો (driver_name && *driver_name != 0) {
            અચલ અક્ષર *driver_attempt = driver_name;
            જ્યારે (driver_attempt && (*driver_attempt != 0) && !result) {
                અચલ અક્ષર *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                માટે (પૂર્ણાંક i = 0; bootstrap[i]; ++i) {
                    જો (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        જો (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            result = true;
                        }
                        તોડો;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : ખાલી;
            }
        } નહીંતર {
            માટે (પૂર્ણાંક i = 0; bootstrap[i]; ++i) {
                જો (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    result = true;
                    તોડો;
                }
            }
        }
    }

    જો (!result) {
        અચલ અક્ષર *error = SDL_GetError();

        જો (!*error) {
            SDL_SetError("No message system available");
        }
    } નહીંતર {
        SDL_ClearError();
    }

    (શૂન્ય)SDL_AtomicDecRef(&SDL_messagebox_ગણતરી);

    જો (current_window) {
        SDL_RaiseWindow(current_window);
    }

    જો (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    પાછા result;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, અચલ અક્ષર *title, અચલ અક્ષર *message, SDL_Window *window)
{
#જો defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_જમણું;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_જમણું = gsp_Has_Gpu_જમણું();
    જો (!has_Gpu_જમણું)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    જો (!has_Gpu_જમણું)
        gfxExit();

    પાછા true;
#નહીંતર
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

    પાછા SDL_ShowMessageBox(&data, ખાલી);
#endif
}

bool SDL_ShouldAllowTopmost(શૂન્ય)
{
    પાછા SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, પૂર્ણાંક x, પૂર્ણાંક y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    જો (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        પાછા true;
    }

    પાછા SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, શૂન્ય *callback_data)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (!_this->SetWindowHitTest) {
        પાછા SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_data = callback_data;

    પાછા _this->SetWindowHitTest(window, callback != ખાલી);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    જો (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        પાછા SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    જો (!props) {
        પાછા false;
    }

    જો (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        જો (!surface) {
            પાછા false;
        }
    } નહીંતર {
        surface = ખાલી;
    }

    જો (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        પાછા false;
    }

    જો (_this->UpdateWindowShape) {
        જો (!_this->UpdateWindowShape(_this, window, surface)) {
            પાછા false;
        }
    }
    પાછા true;
}

/*
 * Functions used by iOS application delegates
 */
શૂન્ય SDL_OnApplicationWillTerminate(શૂન્ય)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

શૂન્ય SDL_OnApplicationDidReceiveMemoryWarning(શૂન્ય)
{
    SDL_SendAppEvent(SDL_EVENT_નીચલું_MEMORY);
}

શૂન્ય SDL_OnApplicationWillEnterBackground(શૂન્ય)
{
    જો (_this) {
        SDL_Window *window;
        માટે (window = _this->windows; window; window = window->next) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(ખાલી);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

શૂન્ય SDL_OnApplicationDidEnterBackground(શૂન્ય)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

શૂન્ય SDL_OnApplicationWillEnterForeground(શૂન્ય)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

શૂન્ય SDL_OnApplicationDidEnterForeground(શૂન્ય)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    જો (_this) {
        SDL_Window *window;
        માટે (window = _this->windows; window; window = window->next) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#define NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(અચલ અક્ષર *path)
{
    bool result;

    જો (!_this) {
        પાછા SDL_UninitializedVideo();
    }
    જો (_this->vulkan_config.loader_loaded) {
        જો (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            પાછા SDL_SetError("Vulkan loader library already loaded");
        }
        result = true;
    } નહીંતર {
        જો (!_this->Vulkan_LoadLibrary) {
            પાછા SDL_DllNotSupported("Vulkan");
        }
        result = _this->Vulkan_LoadLibrary(_this, path);
    }
    જો (result) {
        _this->vulkan_config.loader_loaded++;
    }
    પાછા result;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(શૂન્ય)
{
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા ખાલી;
    }
    જો (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        પાછા ખાલી;
    }
    પાછા (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

શૂન્ય SDL_Vulkan_UnloadLibrary(શૂન્ય)
{
    જો (!_this) {
        SDL_UninitializedVideo();
        પાછા;
    }
    જો (_this->vulkan_config.loader_loaded > 0) {
        જો (--_this->vulkan_config.loader_loaded > 0) {
            પાછા;
        }
        જો (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

અક્ષર અચલ * અચલ *SDL_Vulkan_GetInstanceExtensions(Uint32 *ગણતરી)
{
    Uint32 tmpcount = 0;
    જો (!ગણતરી) {
        ગણતરી = &tmpcount;
    }

    જો (!_this->Vulkan_GetInstanceExtensions) {
        *ગણતરી = 0;
        SDL_Unsupported();
        પાછા ખાલી;
    }

    પાછા _this->Vulkan_GetInstanceExtensions(_this, ગણતરી);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  અચલ સંરચના VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    જો (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        પાછા false;
    }

    CHECK_PARAM(!instance) {
        પાછા SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        પાછા SDL_InvalidParamError("surface");
    }

    જો (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        જો (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        જો (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        જો (SDL_Vulkan_LoadLibrary(ખાલી)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } નહીંતર {
            પાછા SDL_SetError("failed to load Vulkan library");
        }
    }

    પાછા _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

શૂન્ય SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               અચલ સંરચના VkAllocationCallbacks *allocator)
{
    જો (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queueFamilyIndex)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        પાછા false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        પાછા false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        પાછા false;
    }

    જો (_this->Vulkan_GetPresentationSupport) {
        પાછા _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queueFamilyIndex);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    પાછા true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, ખાલી);

    જો (!_this->Metal_CreateView) {
        SDL_Unsupported();
        પાછા ખાલી;
    }

    જો (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        જો (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        જો (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    પાછા _this->Metal_CreateView(_this, window);
}

શૂન્ય SDL_Metal_DestroyView(SDL_MetalView view)
{
    જો (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

શૂન્ય *SDL_Metal_GetLayer(SDL_MetalView view)
{
    જો (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            પાછા ખાલી;
        }
        પાછા _this->Metal_GetLayer(_this, view);
    } નહીંતર {
        SDL_SetError("Metal is not supported.");
        પાછા ખાલી;
    }
}

#જો defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
અચલ અક્ષર *SDL_GetCSSCursorName(SDL_SystemCursor id, અચલ અક્ષર **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    પસંદગી (id) {
    સ્થિતિ SDL_SYSTEM_CURSOR_DEFAULT:
        પાછા "default";

    સ્થિતિ SDL_SYSTEM_CURSOR_TEXT:
        પાછા "text";

    સ્થિતિ SDL_SYSTEM_CURSOR_WAIT:
        પાછા "wait";

    સ્થિતિ SDL_SYSTEM_CURSOR_CROSSHAIR:
        પાછા "crosshair";

    સ્થિતિ SDL_SYSTEM_CURSOR_PROGRESS:
        પાછા "progress";

    સ્થિતિ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        જો (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        પાછા "nwse-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_NESW_RESIZE:
        જો (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        પાછા "nesw-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_EW_RESIZE:
        જો (fallback_name) {
            *fallback_name = "col-resize";
        }
        પાછા "ew-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_NS_RESIZE:
        જો (fallback_name) {
            *fallback_name = "row-resize";
        }
        પાછા "ns-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_MOVE:
        જો (fallback_name) {
            *fallback_name = "all-scroll";
        }
        પાછા "move";

    સ્થિતિ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        પાછા "not-allowed";

    સ્થિતિ SDL_SYSTEM_CURSOR_POINTER:
        પાછા "pointer";

    સ્થિતિ SDL_SYSTEM_CURSOR_NW_RESIZE:
        પાછા "nw-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_N_RESIZE:
        પાછા "n-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_NE_RESIZE:
        પાછા "ne-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_E_RESIZE:
        પાછા "e-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_SE_RESIZE:
        પાછા "se-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_S_RESIZE:
        પાછા "s-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_SW_RESIZE:
        પાછા "sw-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_W_RESIZE:
        પાછા "w-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        પાછા "context-menu";

    સ્થિતિ SDL_SYSTEM_CURSOR_HELP:
        પાછા "help";

    સ્થિતિ SDL_SYSTEM_CURSOR_CELL:
        પાછા "cell";

    સ્થિતિ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        પાછા "vertical-text";

    સ્થિતિ SDL_SYSTEM_CURSOR_ALIAS:
        પાછા "alias";

    સ્થિતિ SDL_SYSTEM_CURSOR_COPY:
        પાછા "copy";

    સ્થિતિ SDL_SYSTEM_CURSOR_NO_DROP:
        પાછા "no-drop";

    સ્થિતિ SDL_SYSTEM_CURSOR_GRAB:
        પાછા "grab";

    સ્થિતિ SDL_SYSTEM_CURSOR_GRABBING:
        પાછા "grabbing";

    સ્થિતિ SDL_SYSTEM_CURSOR_COL_RESIZE:
        પાછા "col-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        પાછા "row-resize";

    સ્થિતિ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        જો (fallback_name) {
            *fallback_name = "move";
        }
        પાછા "all-scroll";

    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_IN:
        પાછા "zoom-in";

    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        પાછા "zoom-out";

    મૂળભૂત:
        પાછા "default";
    }
}
#endif

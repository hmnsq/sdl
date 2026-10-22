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

#समावेश "SDL_internal.h"

// The high-level video driver subsystem

#समावेश "SDL_sysvideo.h"
#समावेश "SDL_clipboard_c.h"
#समावेश "SDL_egl_c.h"
#समावेश "SDL_surface_c.h"
#समावेश "SDL_pixels_c.h"
#समावेश "SDL_rect_c.h"
#समावेश "SDL_video_c.h"
#समावेश "../events/SDL_events_c.h"
#समावेश "../SDL_hints_c.h"
#समावेश "../SDL_properties_c.h"
#समावेश "../timer/SDL_timer_c.h"
#समावेश "../camera/SDL_camera_c.h"
#समावेश "../render/SDL_sysrender.h"
#समावेश "../main/SDL_main_callbacks.h"

#अगर_घोषित SDL_VIDEO_OPENGL
#समावेश <SDL3/SDL_opengl.h>
#पूर्ण_अगर // SDL_VIDEO_OPENGL

#अगर defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#समावेश <SDL3/SDL_opengles.h>
#पूर्ण_अगर // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#अगर defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#समावेश <SDL3/SDL_opengles2.h>
#पूर्ण_अगर // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#अगर_अघोषित GL_CONTEXT_RELEASE_BEHAVIOR
#घोषणा GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#पूर्ण_अगर

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#अगर_अघोषित GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#घोषणा GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#पूर्ण_अगर

// This is always the same number between the various EXT/ARB/GLES extensions.
#अगर_अघोषित GL_FRAMEBUFFER_SRGB
#घोषणा GL_FRAMEBUFFER_SRGB 0x8DB9
#पूर्ण_अगर

#अगर_घोषित SDL_PLATFORM_EMSCRIPTEN
#समावेश <emscripten.h>
#पूर्ण_अगर

#अगर_घोषित SDL_PLATFORM_3DS
#समावेश <3ds.h>
#पूर्ण_अगर

#अगर_अघोषित GL_RGBA_FLOAT_MODE_ARB
#घोषणा GL_RGBA_FLOAT_MODE_ARB 0x8820
#पूर्ण_अगर /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
अटल VideoBootStrap *bootstrap[] = {
#अगर_घोषित SDL_VIDEO_DRIVER_PRIVATE
    &PRIVATE_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#पूर्ण_अगर
    &X11_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#अगर_घोषित SDL_निवेश_LINUXEV
    &DUMMY_evdev_bootstrap,
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#पूर्ण_अगर
    शून्य
};

#घोषणा CHECK_WINDOW_MAGIC(window, परिणाम)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        वापस परिणाम;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(window, SDL_OBJECT_TYPE_WINDOW)) {     \
        SDL_SetError("Invalid window");                                 \
        वापस परिणाम;                                                  \
    }

#घोषणा CHECK_DISPLAY_MAGIC(display, परिणाम)                            \
    CHECK_PARAM(!display) {                                             \
        वापस परिणाम;                                                  \
    }                                                                   \

#घोषणा CHECK_WINDOW_NOT_POPUP(window, परिणाम)                          \
    CHECK_PARAM(SDL_WINDOW_IS_POPUP(window)) {                          \
        SDL_SetError("Operation invalid on popup windows");             \
        वापस परिणाम;                                                  \
    }

#अगर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
बाह्य bool Cocoa_IsWindowInFullscreenSpace(SDL_Window *window);
बाह्य bool Cocoa_IsWindowInFullscreenSpaceTransition(SDL_Window *window);
बाह्य bool Cocoa_SetWindowFullscreenSpace(SDL_Window *window, bool state, bool blocking);
बाह्य bool Cocoa_IsShowingModalDialog(SDL_Window *window);
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_UIKIT
बाह्य व्योम SDL_UpdateLifecycleObserver(व्योम);
#पूर्ण_अगर

अटल व्योम SDL_CheckWindowDisplayChanged(SDL_Window *window);
अटल व्योम SDL_CheckWindowDisplayScaleChanged(SDL_Window *window);
अटल व्योम SDL_CheckWindowSafeAreaChanged(SDL_Window *window);

// Convenience functions for reading driver flags
अटल bool SDL_ModeSwitchingEmulated(SDL_VideoDevice *_this)
{
    अगर (_this->device_caps & VIDEO_DEVICE_CAPS_MODE_SWITCHING_EMULATED) {
        वापस true;
    }
    वापस false;
}

अटल bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    वापस !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

अटल bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    वापस !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

अटल bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    वापस !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

अटल bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    वापस !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

अटल bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    वापस !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
अटल bool syncHint;

अटल व्योम SDL_SyncHintWatcher(व्योम *userdata, स्थिर अक्षर *name, स्थिर अक्षर *old_मूल्य, स्थिर अक्षर *new_मूल्य)
{
    syncHint = SDL_GetStringBoolean(new_मूल्य, false);
}

अटल व्योम SDL_SyncIfRequired(SDL_Window *window)
{
    अगर (syncHint) {
        SDL_SyncWindow(window);
    }
}

अटल व्योम SDL_UpdateWindowHierarchy(SDL_Window *window, SDL_Window *parent)
{
    // Unlink the window from the existing parent.
    अगर (window->parent) {
        अगर (window->अग्र_sibling) {
            window->अग्र_sibling->पूर्व_sibling = window->पूर्व_sibling;
        }
        अगर (window->पूर्व_sibling) {
            window->पूर्व_sibling->अग्र_sibling = window->अग्र_sibling;
        } अन्यथा {
            window->parent->first_child = window->अग्र_sibling;
        }

        window->parent = शून्य;
    }

    अगर (parent) {
        window->parent = parent;

        window->अग्र_sibling = parent->first_child;
        अगर (parent->first_child) {
            parent->first_child->पूर्व_sibling = window;
        }
        parent->first_child = window;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#घोषणा SDL_PROP_WINDOW_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

प्रकार काष्ठा
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    व्योम *pixels;
    पूर्णांक pitch;
    पूर्णांक bytes_per_pixel;
} SDL_Window_Texture_तथ्य;

अटल Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#अगर (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    अगर (_this->GL_CreateContext) {
        वापस SDL_WINDOW_OPENGL;
    }
#पूर्ण_अगर
#अगर defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    अगर (_this->Metal_CreateView) {
        वापस SDL_WINDOW_METAL;
    }
#पूर्ण_अगर
#अगर defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    अगर (SDL_strcmp(_this->name, "openvr") == 0) {
        वापस SDL_WINDOW_OPENGL;
    }
#पूर्ण_अगर
    वापस 0;
}

अटल bool SDL_CreateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format, व्योम **pixels, पूर्णांक *pitch)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_Window_Texture_तथ्य *तथ्य = (SDL_Window_Texture_तथ्य *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, शून्य);
    स्थिर bool transparent = (window->flags & SDL_WINDOW_TRANSPARENT) ? true : false;
    पूर्णांक i;
    पूर्णांक w, h;
    स्थिर SDL_PixelFormat *texture_formats;

    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);

    अगर (!तथ्य) {
        SDL_Renderer *renderer = शून्य;
        स्थिर अक्षर *render_driver = शून्य;

        // See if there's a render driver being requested
        स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        अगर (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        अगर (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        अगर (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = शून्य;
        }

        अक्षर *render_driver_copy = शून्य;
        अगर (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            अगर (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                अक्षर *पूर्व = render_driver_copy;
                अक्षर *ptr = पूर्व;
                जबतक ((ptr = SDL_strchr(ptr, ',')) != शून्य) {
                    *ptr = '\0';
                    स्थिर bool is_sw = (SDL_strcasecmp(पूर्व, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    अगर (is_sw) {
                        SDL_memset(पूर्व, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = पूर्व;
                    } अन्यथा {
                        ptr++;
                        पूर्व = ptr;
                    }
                }

                अगर (SDL_strcasecmp(पूर्व, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(पूर्व, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        अगर (render_driver) {
            renderer = SDL_CreateRenderer(window, render_driver);
            SDL_free(render_driver_copy);
            अगर (!renderer) {
                // The error for this specific renderer has already been set
                वापस false;
            }
        } अन्यथा {
            SDL_assert(render_driver_copy == शून्य);
            स्थिर पूर्णांक योग = SDL_Get_अंक_Render_Drivers();
            क्रम (i = 0; i < योग; ++i) {
                स्थिर अक्षर *name = SDL_GetRenderDriver(i);
                अगर (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(window, name);
                    अगर (renderer) {
                        अवरोध; // this will work.
                    }
                }
            }
            अगर (!renderer) {
                वापस SDL_SetError("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != शून्य); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        तथ्य = (SDL_Window_Texture_तथ्य *)SDL_calloc(1, माप(*तथ्य));
        अगर (!तथ्य) {
            SDL_DestroyRenderer(renderer);
            वापस false;
        }
        अगर (!SDL_SetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, तथ्य)) {
            SDL_DestroyRenderer(renderer);
            वापस false;
        }

        तथ्य->renderer = renderer;
    }

    texture_formats = (स्थिर SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(तथ्य->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, शून्य);
    अगर (!texture_formats) {
        वापस false;
    }

    // Free any old texture and pixel data
    अगर (तथ्य->texture) {
        SDL_DestroyTexture(तथ्य->texture);
        तथ्य->texture = शून्य;
    }
    SDL_free(तथ्य->pixels);
    तथ्य->pixels = शून्य;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    क्रम (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        अगर (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_INDEXED(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            अवरोध;
        }
    }

    तथ्य->texture = SDL_CreateTexture(तथ्य->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    अगर (!तथ्य->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        वापस false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_SetTextureBlendMode(तथ्य->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    तथ्य->bytes_per_pixel = SDL_BYTESPERPIXEL(*format);
    तथ्य->pitch = (((w * तथ्य->bytes_per_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        स्थिर माप_प्रकार allocsize = (माप_प्रकार)h * तथ्य->pitch;
        तथ्य->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        अगर (!तथ्य->pixels) {
            वापस false;
        }
    }

    *pixels = तथ्य->pixels;
    *pitch = तथ्य->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_SetRenderViewport(तथ्य->renderer, शून्य);

    वापस true;
}

bool SDL_SetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक vsync)
{
    SDL_Window_Texture_तथ्य *तथ्य;

    तथ्य = (SDL_Window_Texture_तथ्य *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, शून्य);
    अगर (!तथ्य) {
        वापस false;
    }
    अगर (!तथ्य->renderer) {
        वापस false;
    }
    वापस SDL_SetRenderVSync(तथ्य->renderer, vsync);
}

अटल bool SDL_GetWindowTextureVSync(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *vsync)
{
    SDL_Window_Texture_तथ्य *तथ्य;

    तथ्य = (SDL_Window_Texture_तथ्य *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, शून्य);
    अगर (!तथ्य) {
        वापस false;
    }
    अगर (!तथ्य->renderer) {
        वापस false;
    }
    वापस SDL_GetRenderVSync(तथ्य->renderer, vsync);
}

अटल bool SDL_UpdateWindowTexture(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects, पूर्णांक numrects)
{
    SDL_Window_Texture_तथ्य *तथ्य;
    SDL_Rect rect;
    व्योम *src;
    पूर्णांक w, h;

    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);

    तथ्य = (SDL_Window_Texture_तथ्य *)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_TEXTUREDATA_POINTER, शून्य);
    अगर (!तथ्य || !तथ्य->texture) {
        वापस SDL_SetError("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    अगर (SDL_GetSpanEnclosingRect(w, h, numrects, rects, &rect)) {
        src = (व्योम *)((Uint8 *)तथ्य->pixels +
                       rect.y * तथ्य->pitch +
                       rect.x * तथ्य->bytes_per_pixel);
        अगर (!SDL_UpdateTexture(तथ्य->texture, &rect, src, तथ्य->pitch)) {
            वापस false;
        }

        अगर (!SDL_RenderTexture(तथ्य->renderer, तथ्य->texture, शून्य, शून्य)) {
            वापस false;
        }

        SDL_RenderPresent(तथ्य->renderer);
    }
    वापस true;
}

अटल व्योम SDL_DestroyWindowTexture(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    अगर (SDL_HasProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER)) {
        SDL_Window_Texture_तथ्य *तथ्य = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER, शून्य);

        अगर (तथ्य->texture) {
            SDL_DestroyTexture(तथ्य->texture);
        }
        अगर (तथ्य->renderer) {
            SDL_DestroyRenderer(तथ्य->renderer);
        }
        SDL_free(तथ्य->pixels);
        SDL_free(तथ्य);

        SDL_ClearProperty(props, SDL_PROP_WINDOW_TEXTUREDATA_POINTER);
    }
}

अटल SDL_VideoDevice *_this = शून्य;
अटल SDL_AtomicInt SDL_messagebox_गिनती;

अटल पूर्णांक SDLCALL cmpmodes(स्थिर व्योम *A, स्थिर व्योम *B)
{
    स्थिर SDL_DisplayMode *a = (स्थिर SDL_DisplayMode *)A;
    स्थिर SDL_DisplayMode *b = (स्थिर SDL_DisplayMode *)B;
    पूर्णांक a_refresh_rate = (पूर्णांक)(a->refresh_rate * 100);
    पूर्णांक b_refresh_rate = (पूर्णांक)(b->refresh_rate * 100);
    पूर्णांक a_pixel_density = (पूर्णांक)(a->pixel_density * 100);
    पूर्णांक b_pixel_density = (पूर्णांक)(b->pixel_density * 100);

    अगर (a->w != b->w) {
        वापस b->w - a->w;
    } अन्यथा अगर (a->h != b->h) {
        वापस b->h - a->h;
    } अन्यथा अगर (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        वापस SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } अन्यथा अगर (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        वापस SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } अन्यथा अगर (a_refresh_rate != b_refresh_rate) {
        वापस b_refresh_rate - a_refresh_rate;
    } अन्यथा अगर (a_pixel_density != b_pixel_density) {
        वापस a_pixel_density - b_pixel_density;
    }
    वापस 0;
}

bool SDL_UninitializedVideo(व्योम)
{
    वापस SDL_SetError("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
अटल स्थिर VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

पूर्णांक SDL_Get_अंक_Video_Drivers(व्योम)
{
    अटल पूर्णांक अंक_drivers = -1;

    अगर (अंक_drivers >= 0) {
        वापस अंक_drivers;
    }

    अंक_drivers = 0;

    // Build a list of unique video drivers.
    क्रम (पूर्णांक i = 0; bootstrap[i] != शून्य; ++i) {
        bool duplicate = false;
        क्रम (पूर्णांक j = 0; j < i; ++j) {
            अगर (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                अवरोध;
            }
        }

        अगर (!duplicate) {
            deduped_bootstrap[अंक_drivers++] = bootstrap[i];
        }
    }

    वापस अंक_drivers;
}

स्थिर अक्षर *SDL_GetVideoDriver(पूर्णांक सूचकांक)
{
    CHECK_PARAM(सूचकांक < 0 || सूचकांक >= SDL_Get_अंक_Video_Drivers()) {
        SDL_InvalidParamError("index");
        वापस शून्य;
    }
    वापस deduped_bootstrap[सूचकांक]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(स्थिर अक्षर *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    पूर्णांक i = 0;

    // Check to make sure we don't overwrite '_this'
    अगर (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    अगर (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        जाओ pre_driver_error;
    }
    init_events = true;
    अगर (!SDL_InitKeyboard()) {
        जाओ pre_driver_error;
    }
    init_keyboard = true;
    अगर (!SDL_PreInitMouse()) {
        जाओ pre_driver_error;
    }
    init_mouse = true;
    अगर (!SDL_InitTouch()) {
        जाओ pre_driver_error;
    }
    init_touch = true;
    अगर (!SDL_InitPen()) {
        जाओ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = शून्य;
#अगर_घोषित SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    अगर (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#पूर्ण_अगर
    अगर (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    अगर (driver_name && *driver_name != 0) {
        स्थिर अक्षर *driver_attempt = driver_name;
        जबतक (driver_attempt && *driver_attempt != 0 && !video) {
            स्थिर अक्षर *driver_attempt_end = SDL_strchr(driver_attempt, ',');
            माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            क्रम (i = 0; bootstrap[i]; ++i) {
                अगर (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    अगर (video) {
                        अवरोध;
                    }
                }
            }

            driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : शून्य;
        }
    } अन्यथा {
        क्रम (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            अगर (video) {
                अवरोध;
            }
        }
    }
    अगर (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } अन्यथा {
        अगर (driver_name) {
            SDL_SetError("%s not available", driver_name);
            जाओ pre_driver_error;
        }
        SDL_SetError("No available video device");
        जाओ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = शून्य;
    SDL_GL_ResetAttributes();

    // Initialize the video subsystem
    अगर (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        वापस false;
    }

    // Make sure some displays were added
    अगर (_this->अंक_displays == 0) {
        SDL_QuitVideo();
        वापस SDL_SetError("The video driver did not add any displays");
    }

    SDL_AddHintCallback(SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS, SDL_SyncHintWatcher, शून्य);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    अगर (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    वापस true;

pre_driver_error:
    SDL_assert(_this == शून्य);
    अगर (init_pen) {
        SDL_QuitPen();
    }
    अगर (init_touch) {
        SDL_QuitTouch();
    }
    अगर (init_mouse) {
        SDL_QuitMouse();
    }
    अगर (init_keyboard) {
        SDL_QuitKeyboard();
    }
    अगर (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    वापस false;
}

स्थिर अक्षर *SDL_GetCurrentVideoDriver(व्योम)
{
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    वापस _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(व्योम)
{
    वापस _this;
}

bool SDL_OnVideoThread(व्योम)
{
    वापस (_this && SDL_GetCurrentThreadID() == _this->thread);
}

व्योम SDL_SetSystemTheme(SDL_SystemTheme theme)
{
    अगर (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_SendSystemThemeChangedEvent();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(व्योम)
{
    अगर (_this) {
        वापस _this->system_theme;
    } अन्यथा {
        वापस SDL_SYSTEM_THEME_UNKNOWN;
    }
}

व्योम SDL_UpdateDesktopBounds(व्योम)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(शून्य);
    अगर (displays) {
        क्रम (पूर्णांक i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            अगर (SDL_GetDisplayBounds(displays[i], &bounds)) {
                अगर (i == 0) {
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

अटल व्योम SDL_FinalizeDisplayMode(SDL_DisplayMode *mode)
{
    // Make sure all the fields are set up correctly
    अगर (mode->pixel_density <= 0.0f) {
        mode->pixel_density = 1.0f;
    }

    अगर (mode->refresh_rate_numerator > 0) {
        अगर (mode->refresh_rate_denominator <= 0) {
            mode->refresh_rate_denominator = 1;
        }
        mode->refresh_rate = (भग्न)mode->refresh_rate_numerator / mode->refresh_rate_denominator;
    } अन्यथा {
        SDL_CalculateFraction(mode->refresh_rate, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
    }
    mode->refresh_rate = SDL_roundf(mode->refresh_rate * 100) / 100.0f;
}

SDL_DisplayID SDL_AddBasicVideoDisplay(स्थिर SDL_DisplayMode *desktop_mode)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    अगर (desktop_mode) {
        SDL_memcpy(&display.desktop_mode, desktop_mode, माप(display.desktop_mode));
    }
    वापस SDL_AddVideoDisplay(&display, false);
}

SDL_DisplayID SDL_AddVideoDisplay(स्थिर SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    पूर्णांक i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(माप(*new_display));
    अगर (!new_display) {
        वापस 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->अंक_displays + 1) * माप(*displays));
    अगर (!displays) {
        SDL_free(new_display);
        वापस 0;
    }
    _this->displays = displays;
    _this->displays[_this->अंक_displays++] = new_display;

    id = SDL_Get_अग्र_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    अगर (display->name) {
        new_display->name = SDL_strdup(display->name);
    } अन्यथा {
        अक्षर name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    अगर (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_mode.displayID = id;
    new_display->current_mode = &new_display->desktop_mode;
    SDL_FinalizeDisplayMode(&new_display->desktop_mode);

    क्रम (i = 0; i < new_display->अंक_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_SetBooleanProperty(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    अगर (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    वापस id;
}

व्योम SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_Window *window;

    // See if any windows have changed to the new display
    क्रम (window = _this->windows; window; window = window->अग्र) {
        SDL_CheckWindowDisplayChanged(window);
    }
}

व्योम SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

व्योम SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    पूर्णांक display_सूचकांक = SDL_Get_Display_सूचकांक(displayID);
    अगर (display_सूचकांक < 0) {
        वापस;
    }

    display = _this->displays[display_सूचकांक];

    अगर (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_mode.internal);
    display->desktop_mode.internal = शून्य;
    SDL_free(display->internal);
    display->internal = शून्य;
    SDL_free(display);

    अगर (display_सूचकांक < (_this->अंक_displays - 1)) {
        SDL_memmove(&_this->displays[display_सूचकांक], &_this->displays[display_सूचकांक + 1], (_this->अंक_displays - display_सूचकांक - 1) * माप(_this->displays[display_सूचकांक]));
    }
    --_this->अंक_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(पूर्णांक *गिनती)
{
    पूर्णांक i;
    SDL_DisplayID *displays;

    अगर (!_this) {
        अगर (गिनती) {
            *गिनती = 0;
        }

        SDL_UninitializedVideo();
        वापस शून्य;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->अंक_displays + 1) * माप(*displays));
    अगर (displays) {
        अगर (गिनती) {
            *गिनती = _this->अंक_displays;
        }

        क्रम (i = 0; i < _this->अंक_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } अन्यथा {
        अगर (गिनती) {
            *गिनती = 0;
        }
    }
    वापस displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    पूर्णांक display_सूचकांक;

    display_सूचकांक = SDL_Get_Display_सूचकांक(displayID);
    अगर (display_सूचकांक < 0) {
        वापस शून्य;
    }
    वापस _this->displays[display_सूचकांक];
}

अटल SDL_DisplayID GetDisplayForWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    अगर (!displayID) {
        displayID = SDL_GetDisplayForWindowPosition(window);
    }
    वापस displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    वापस SDL_GetVideoDisplay(GetDisplayForWindow(window));
}

SDL_DisplayID SDL_GetPrimaryDisplay(व्योम)
{
    अगर (!_this || _this->अंक_displays == 0) {
        SDL_UninitializedVideo();
        वापस 0;
    }
    वापस _this->displays[0]->id;
}

पूर्णांक SDL_Get_Display_सूचकांक(SDL_DisplayID displayID)
{
    पूर्णांक display_सूचकांक;

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस -1;
    }

    क्रम (display_सूचकांक = 0; display_सूचकांक < _this->अंक_displays; ++display_सूचकांक) {
        अगर (displayID == _this->displays[display_सूचकांक]->id) {
            वापस display_सूचकांक;
        }
    }
    SDL_SetError("Invalid display");
    वापस -1;
}

SDL_Display_तथ्य *SDL_Get_Display_Driver_तथ्य(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, शून्य);

    वापस display->internal;
}

SDL_Display_तथ्य *SDL_Get_Display_Driver_तथ्य_For_Window(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    वापस SDL_Get_Display_Driver_तथ्य(GetDisplayForWindow(window));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    अगर (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    वापस display->props;
}

स्थिर अक्षर *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, शून्य);

    वापस display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        वापस SDL_InvalidParamError("rect");
    }

    अगर (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        अगर (_this->GetDisplayBounds(_this, display, rect)) {
            वापस true;
        }
    }

    // Assume that the displays are left to right
    अगर (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } अन्यथा {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_सूचकांक(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_mode->w;
    rect->h = display->current_mode->h;
    वापस true;
}

अटल पूर्णांक ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    वापस hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        वापस SDL_InvalidParamError("rect");
    }

    अगर (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        वापस true;
    }

    अगर (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        अगर (_this->GetDisplayUsableBounds(_this, display, rect)) {
            वापस true;
        }
    }

    // Oh well, just give the entire display bounds.
    वापस SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    अगर (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        वापस display->natural_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        वापस SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    अगर (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        वापस display->current_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        वापस SDL_ORIENTATION_LANDSCAPE;
    }
}

व्योम SDL_SetDisplayContentScale(SDL_VideoDisplay *display, भग्न scale)
{
    अगर (scale != display->content_scale) {
        SDL_Window *window;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED, 0, 0);

        // Check the windows on this display
        क्रम (window = _this->windows; window; window = window->अग्र) {
            अगर (display->id == window->displayID) {
                SDL_CheckWindowDisplayScaleChanged(window);
            }
        }
    }
}

भग्न SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    वापस display->content_scale;
}

व्योम SDL_SetWindowHDRProperties(SDL_Window *window, स्थिर SDL_HDROutputProperties *HDR, bool send_event)
{
    स्थिर SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    अगर (window->HDR.HDR_headroom != HDR_clamped.HDR_headroom || window->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID window_props = SDL_GetWindowProperties(window);

        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_SetFloatProperty(window_props, SDL_PROP_WINDOW_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&window->HDR, &HDR_clamped);

        अगर (send_event) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HDR_STATE_CHANGED, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

व्योम SDL_SetDisplayHDRProperties(SDL_VideoDisplay *display, स्थिर SDL_HDROutputProperties *HDR)
{
    स्थिर SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    स्थिर bool changed = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	अगर (changed) {
		SDL_SetBooleanProperty(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    अगर (changed && !SDL_DriverSendsHDRChanges(_this)) {
        क्रम (SDL_Window *w = display->device->windows; w; w = w->अग्र) {
            अगर (GetDisplayForWindow(w) == display->id) {
                SDL_SetWindowHDRProperties(w, &display->HDR, true);
            }
        }
    }
}

अटल व्योम SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    अगर (display->अंक_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
अटल स्थिर SDL_DisplayMode *SDL_GetFullscreenModeMatch(स्थिर SDL_DisplayMode *mode)
{
    SDL_VideoDisplay *display;
    SDL_DisplayMode fullscreen_mode;

    अगर (mode->w <= 0 || mode->h <= 0) {
        // Use the desktop mode
        वापस शून्य;
    }

    SDL_memcpy(&fullscreen_mode, mode, माप(fullscreen_mode));
    अगर (fullscreen_mode.displayID == 0) {
        fullscreen_mode.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_FinalizeDisplayMode(&fullscreen_mode);

    mode = शून्य;

    display = SDL_GetVideoDisplay(fullscreen_mode.displayID);
    अगर (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        अगर (!mode) {
            क्रम (पूर्णांक i = 0; i < display->अंक_fullscreen_modes; ++i) {
                अगर (SDL_memcmp(&fullscreen_mode, &display->fullscreen_modes[i], माप(fullscreen_mode)) == 0) {
                    mode = &display->fullscreen_modes[i];
                    अवरोध;
                }
            }
        }

        // Search for a mode with the same characteristics
        अगर (!mode) {
            क्रम (पूर्णांक i = 0; i < display->अंक_fullscreen_modes; ++i) {
                अगर (cmpmodes(&fullscreen_mode, &display->fullscreen_modes[i]) == 0) {
                    mode = &display->fullscreen_modes[i];
                    अवरोध;
                }
            }
        }
    }
    वापस mode;
}

bool SDL_AddFullscreenDisplayMode(SDL_VideoDisplay *display, स्थिर SDL_DisplayMode *mode)
{
    SDL_DisplayMode *modes;
    SDL_DisplayMode new_mode;
    पूर्णांक i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_mode, mode, माप(new_mode));
    new_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&new_mode);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->अंक_fullscreen_modes;
    क्रम (i = 0; i < nmodes; ++i) {
        अगर (cmpmodes(&new_mode, &modes[i]) == 0) {
            वापस false;
        }
    }

    // Go ahead and add the new mode
    अगर (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_DisplayMode *)SDL_malloc((display->max_fullscreen_modes + 32) * माप(*modes));
        अगर (!modes) {
            वापस false;
        }

        अगर (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * माप(*modes));
            क्रम (i = 0; i < nmodes; ++i) {
                अगर (display->current_mode == &display->fullscreen_modes[i]) {
                    display->current_mode = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->अंक_fullscreen_modes++], &new_mode, माप(new_mode));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->अंक_fullscreen_modes,
              माप(SDL_DisplayMode), cmpmodes);

    वापस true;
}

व्योम SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    पूर्णांक i;

    क्रम (i = display->अंक_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].internal);
        display->fullscreen_modes[i].internal = शून्य;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = शून्य;
    display->अंक_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_mode = &display->desktop_mode;
}

SDL_DisplayMode **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, पूर्णांक *गिनती)
{
    पूर्णांक i;
    पूर्णांक अंक_modes;
    SDL_DisplayMode **परिणाम;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    अगर (गिनती) {
        *गिनती = 0;
    }

    CHECK_DISPLAY_MAGIC(display, शून्य);

    SDL_UpdateFullscreenDisplayModes(display);

    अंक_modes = display->अंक_fullscreen_modes;
    परिणाम = (SDL_DisplayMode **)SDL_malloc((अंक_modes + 1) * माप(*परिणाम) + अंक_modes * माप(**परिणाम));
    अगर (परिणाम) {
        SDL_DisplayMode *modes = (SDL_DisplayMode *)((Uint8 *)परिणाम + ((अंक_modes + 1) * माप(*परिणाम)));
        अगर (अंक_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, अंक_modes * माप(*modes));
        }
        क्रम (i = 0; i < अंक_modes; ++i) {
            परिणाम[i] = modes++;
        }
        परिणाम[i] = शून्य;

        अगर (गिनती) {
            *गिनती = अंक_modes;
        }
    } अन्यथा {
        अगर (गिनती) {
            *गिनती = 0;
        }
    }
    वापस परिणाम;
}

bool SDL_GetClosestFullscreenDisplayMode(SDL_DisplayID displayID, पूर्णांक w, पूर्णांक h, भग्न refresh_rate, bool include_ऊपरी_density_modes, SDL_DisplayMode *परिणाम)
{
    CHECK_PARAM(!परिणाम) {
        वापस SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    स्थिर SDL_DisplayMode *mode, *closest = शून्य;
    भग्न aspect_ratio;
    पूर्णांक i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(परिणाम);

    CHECK_DISPLAY_MAGIC(display, false);

    अगर (h > 0) {
        aspect_ratio = (भग्न)w / h;
    } अन्यथा {
        aspect_ratio = 1.0f;
    }

    अगर (refresh_rate == 0.0f) {
        refresh_rate = display->desktop_mode.refresh_rate;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    क्रम (i = 0; i < display->अंक_fullscreen_modes; ++i) {
        mode = &display->fullscreen_modes[i];

        अगर (w > mode->w) {
            // Out of sorted modes large enough here
            अवरोध;
        }
        अगर (h > mode->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            जारी;
        }
        अगर (mode->pixel_density > 1.0f && !include_ऊपरी_density_modes) {
            जारी;
        }
        अगर (closest) {
            भग्न current_aspect_ratio = (भग्न)mode->w / mode->h;
            भग्न closest_aspect_ratio = (भग्न)closest->w / closest->h;
            अगर (SDL_fabsf(aspect_ratio - closest_aspect_ratio) < SDL_fabsf(aspect_ratio - current_aspect_ratio)) {
                // The mode we already found has a better aspect ratio match
                जारी;
            }

            अगर (mode->w == closest->w && mode->h == closest->h) {
                अगर (SDL_fabsf(closest->refresh_rate - refresh_rate) < SDL_fabsf(mode->refresh_rate - refresh_rate)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    जारी;
                }
                अगर (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(mode->format)) {
                    // Prefer the highest color depth
                    जारी;
                }
            }
        }

        closest = mode;
    }
    अगर (!closest) {
        वापस SDL_SetError("Couldn't find any matching video modes");
    }

    SDL_copyp(परिणाम, closest);

    वापस true;
}

अटल bool DisplayModeChanged(स्थिर SDL_DisplayMode *old_mode, स्थिर SDL_DisplayMode *new_mode)
{
    वापस ((old_mode->displayID && old_mode->displayID != new_mode->displayID) ||
            (old_mode->format && old_mode->format != new_mode->format) ||
            (old_mode->w && old_mode->h && (old_mode->w != new_mode->w ||old_mode->h != new_mode->h)) ||
            (old_mode->pixel_density != 0.0f && old_mode->pixel_density != new_mode->pixel_density) ||
            (old_mode->refresh_rate != 0.0f && old_mode->refresh_rate != new_mode->refresh_rate));
}

व्योम SDL_SetDesktopDisplayMode(SDL_VideoDisplay *display, स्थिर SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    अगर (display->fullscreen_active) {
        // This is a temporary mode change, don't save the desktop mode
        वापस;
    }

    SDL_copyp(&last_mode, &display->desktop_mode);

    SDL_free(display->desktop_mode.internal);
    SDL_copyp(&display->desktop_mode, mode);
    display->desktop_mode.displayID = display->id;
    SDL_FinalizeDisplayMode(&display->desktop_mode);

    अगर (DisplayModeChanged(&last_mode, &display->desktop_mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED, mode->w, mode->h);
        अगर (display->current_mode == &display->desktop_mode) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
        }
    }
}

स्थिर SDL_DisplayMode *SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, शून्य);

    वापस &display->desktop_mode;
}

व्योम SDL_SetCurrentDisplayMode(SDL_VideoDisplay *display, स्थिर SDL_DisplayMode *mode)
{
    SDL_DisplayMode last_mode;

    अगर (display->current_mode) {
        SDL_copyp(&last_mode, display->current_mode);
    } अन्यथा {
        SDL_zero(last_mode);
    }

    display->current_mode = mode;

    अगर (DisplayModeChanged(&last_mode, mode)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED, mode->w, mode->h);
    }
}

स्थिर SDL_DisplayMode *SDL_GetCurrentDisplayMode(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, शून्य);

    वापस display->current_mode;
}

bool SDL_SetDisplayModeForDisplay(SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    अगर (SDL_ModeSwitchingEmulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        वापस true;
    }

    अगर (!mode) {
        mode = &display->desktop_mode;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#अगर_अघोषित SDL_PLATFORM_RISCOS
    अगर (mode == display->current_mode) {
        वापस true;
    }
#पूर्ण_अगर

    // Actually change the display mode
    अगर (_this->SetDisplayMode) {
        bool परिणाम;

        _this->setting_display_mode = true;
        परिणाम = _this->SetDisplayMode(_this, display, mode);
        _this->setting_display_mode = false;
        अगर (!परिणाम) {
            वापस false;
        }
    }

    SDL_SetCurrentDisplayMode(display, mode);

    वापस true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
अटल व्योम SDL_GetClosestPointOnRect(स्थिर SDL_Rect *rect, SDL_Point *point)
{
    स्थिर पूर्णांक दायाँ = rect->x + rect->w - 1;
    स्थिर पूर्णांक bottom = rect->y + rect->h - 1;

    अगर (point->x < rect->x) {
        point->x = rect->x;
    } अन्यथा अगर (point->x > दायाँ) {
        point->x = दायाँ;
    }

    अगर (point->y < rect->y) {
        point->y = rect->y;
    } अन्यथा अगर (point->y > bottom) {
        point->y = bottom;
    }
}

अटल SDL_DisplayID GetDisplayForRect(पूर्णांक x, पूर्णांक y, पूर्णांक w, पूर्णांक h)
{
    पूर्णांक i, dist;
    SDL_DisplayID closest = 0;
    पूर्णांक closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    अगर (_this) {
        क्रम (i = 0; i < _this->अंक_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            अगर (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, शून्य)) {
                वापस display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            अगर (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    अगर (closest == 0) {
        SDL_SetError("Couldn't find any displays");
    }

    वापस closest;
}

व्योम SDL_RelativeToGlobalForWindow(SDL_Window *window, पूर्णांक rel_x, पूर्णांक rel_y, पूर्णांक *abs_x, पूर्णांक *abs_y)
{
    SDL_Window *w;

    अगर (SDL_WINDOW_IS_POPUP(window)) {
        // Calculate the total offset of the popup from the parents
        क्रम (w = window->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            अगर (!SDL_WINDOW_IS_POPUP(w)) {
                अवरोध;
            }
        }
    }

    अगर (abs_x) {
        *abs_x = rel_x;
    }
    अगर (abs_y) {
        *abs_y = rel_y;
    }
}

व्योम SDL_GlobalToRelativeForWindow(SDL_Window *window, पूर्णांक abs_x, पूर्णांक abs_y, पूर्णांक *rel_x, पूर्णांक *rel_y)
{
    SDL_Window *w;

    अगर (SDL_WINDOW_IS_POPUP(window)) {
        // Convert absolute window coordinates to relative for a popup
        क्रम (w = window->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            अगर (!SDL_WINDOW_IS_POPUP(w)) {
                अवरोध;
            }
        }
    }

    अगर (rel_x) {
        *rel_x = abs_x;
    }
    अगर (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(स्थिर SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        वापस 0;
    }

    वापस GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(स्थिर SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        वापस 0;
    }

    वापस GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

अटल SDL_DisplayID GetDisplayAtOrigin(पूर्णांक x, पूर्णांक y)
{
    क्रम (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
        SDL_Rect rect;
        स्थिर SDL_DisplayID cur_id = _this->displays[i]->id;
        अगर (SDL_GetDisplayBounds(cur_id, &rect)) {
            अगर (x == rect.x && y == rect.y) {
                वापस cur_id;
            }
        }
    }

    वापस 0;
}

SDL_DisplayID SDL_GetDisplayForWindowPosition(SDL_Window *window)
{
    पूर्णांक x, y;
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, 0);

    अगर (_this->GetDisplayForWindow) {
        displayID = _this->GetDisplayForWindow(_this, window);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_RelativeToGlobalForWindow(window, window->x, window->y, &x, &y);

    अगर (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } अन्यथा {
            displayID = GetDisplayForRect(x, y, window->w, window->h);
        }
    }
    अगर (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    वापस displayID;
}

SDL_VideoDisplay *SDL_GetVideoDisplayForFullscreenWindow(SDL_Window *window)
{
    SDL_DisplayID displayID = 0;

    CHECK_WINDOW_MAGIC(window, शून्य);

    // An explicit fullscreen display overrides all
    अगर (window->current_fullscreen_mode.displayID) {
        displayID = window->current_fullscreen_mode.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    अगर (!displayID) {
        displayID = window->pending_displayID;
    }
    अगर (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        स्थिर पूर्णांक x = window->last_position_pending ? window->pending.x : window->x;
        स्थिर पूर्णांक y = window->last_position_pending ? window->pending.y : window->y;
        स्थिर पूर्णांक w = window->last_आकार_pending ? window->pending.w : window->w;
        स्थिर पूर्णांक h = window->last_आकार_pending ? window->pending.h : window->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        अगर (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    अगर (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    वापस SDL_GetVideoDisplay(displayID);
}

#घोषणा SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_GetDisplayForWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID window_props = SDL_GetWindowProperties(window);
    SDL_VideoDisplay *fs_display = SDL_GetVideoDisplayForFullscreenWindow(window);
    अगर (fs_display) {
        SDL_Set_संख्या_Property(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } अन्यथा {
        SDL_ClearProperty(window_props, SDL_PROP_SDL2_COMPAT_WINDOW_PREFERRED_FULLSCREEN_DISPLAY);
    }

    वापस GetDisplayForWindow(window);
}

अटल व्योम SDL_CheckWindowDisplayChanged(SDL_Window *window)
{
    अगर (SDL_SendsDisplayChanges(_this)) {
        वापस;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);

    अगर (displayID != window->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect window_rect;
        SDL_Rect old_overlap, new_overlap;

        अगर (SDL_GetDisplayBounds(window->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            window_rect.x = window->x;
            window_rect.y = window->y;
            window_rect.w = window->w;
            window_rect.h = window->h;

            अगर (SDL_GetRectIntersection(&old_bounds, &window_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &window_rect, &new_overlap)) {
                पूर्णांक old_area = old_overlap.w * old_overlap.h;
                पूर्णांक new_area = new_overlap.w * new_overlap.h;
                भग्न new_overlap_ratio = (new_area / ((भग्न)old_area + new_area));
                अगर (new_overlap_ratio < 0.80) {
                    वापस;
                }
            }
        }
    }

    अगर (displayID != window->displayID) {
        पूर्णांक i, display_सूचकांक;

        // Sanity check our fullscreen windows
        display_सूचकांक = SDL_Get_Display_सूचकांक(displayID);
        क्रम (i = 0; i < _this->अंक_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            अगर (display->fullscreen_window == window) {
                अगर (display_सूचकांक != i) {
                    अगर (display_सूचकांक < 0) {
                        display_सूचकांक = i;
                    } अन्यथा {
                        SDL_VideoDisplay *new_display = _this->displays[display_सूचकांक];

                        // The window was moved to a different display
                        अगर (new_display->fullscreen_window &&
                            new_display->fullscreen_window != window) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_MinimizeWindow(new_display->fullscreen_window);
                        }
                        new_display->fullscreen_window = window;
                        display->fullscreen_window = शून्य;
                    }
                }
                अवरोध;
            }
        }

        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, (पूर्णांक)displayID, 0);
    }
}

भग्न SDL_GetWindowPixelDensity(SDL_Window *window)
{
    पूर्णांक window_w, window_h, pixel_w, pixel_h;
    भग्न pixel_density = 1.0f;

    CHECK_WINDOW_MAGIC(window, 0.0f);

    अगर (SDL_Get_Window_आकार(window, &window_w, &window_h) &&
        SDL_Get_Window_आकार_In_Pixels(window, &pixel_w, &pixel_h)) {
        pixel_density = (भग्न)pixel_w / window_w;
    }
    वापस pixel_density;
}

भग्न SDL_GetWindowDisplayScale(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0.0f);

    वापस window->display_scale;
}

अटल व्योम SDL_CheckWindowDisplayScaleChanged(SDL_Window *window)
{
    भग्न display_scale;

    अगर (_this->GetWindowContentScale) {
        display_scale = _this->GetWindowContentScale(_this, window);
    } अन्यथा {
        स्थिर भग्न pixel_density = SDL_GetWindowPixelDensity(window);
        स्थिर भग्न content_scale = SDL_GetDisplayContentScale(window->displayID);

        display_scale = pixel_density * content_scale;
    }

    अगर (display_scale != window->display_scale) {
        window->display_scale = display_scale;
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, 0, 0);
    }
}

bool SDL_UpdateFullscreenMode(SDL_Window *window, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = शून्य;
    SDL_DisplayMode *mode = शून्य;
    पूर्णांक i;

    CHECK_WINDOW_MAGIC(window, false);

    window->fullscreen_exclusive = false;
    window->update_fullscreen_on_display_changed = false;

    // If we are in the process of hiding don't go back to fullscreen
    अगर (window->is_destroying || window->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    अगर (fullscreen) {
        display = SDL_GetVideoDisplayForFullscreenWindow(window);
        अगर (!display) {
            // This should never happen, but it did...
            जाओ done;
        }
    } अन्यथा {
        क्रम (i = 0; i < _this->अंक_displays; ++i) {
            display = _this->displays[i];
            अगर (display->fullscreen_window == window) {
                अवरोध;
            }
        }
        अगर (!display || i == _this->अंक_displays) {
            // Already not fullscreen on any display
            display = शून्य;
        }
    }

    अगर (fullscreen) {
        mode = (SDL_DisplayMode *)SDL_GetWindowFullscreenMode(window);
        अगर (mode) {
            window->fullscreen_exclusive = true;
        } अन्यथा {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(window->current_fullscreen_mode);
        }
    }

#अगर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    अगर (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        अगर (window->is_destroying && !window->last_fullscreen_exclusive_display) {
            window->fullscreen_exclusive = false;
            अगर (display) {
                display->fullscreen_window = शून्य;
            }
            जाओ done;
        }
        अगर (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            अगर (fullscreen && Cocoa_IsWindowInFullscreenSpace(window) && !window->last_fullscreen_exclusive_display && window->fullscreen_exclusive) {
                अगर (!Cocoa_SetWindowFullscreenSpace(window, false, true)) {
                    जाओ error;
                }
            } अन्यथा अगर (fullscreen && window->last_fullscreen_exclusive_display && !window->fullscreen_exclusive) {
                क्रम (i = 0; i < _this->अंक_displays; ++i) {
                    SDL_VideoDisplay *last_display = _this->displays[i];
                    अगर (last_display->fullscreen_window == window) {
                        SDL_SetDisplayModeForDisplay(last_display, शून्य);
                        अगर (_this->SetWindowFullscreen) {
                            _this->SetWindowFullscreen(_this, window, last_display, false);
                        }
                        last_display->fullscreen_window = शून्य;
                    }
                }
            }

            अगर (Cocoa_SetWindowFullscreenSpace(window, !!fullscreen, syncHint)) {
                जाओ done;
            }
        }
    }
#पूर्ण_अगर

    अगर (display) {
        // Restore the video mode on other displays if needed
        क्रम (i = 0; i < _this->अंक_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            अगर (other != display && other->fullscreen_window == window) {
                SDL_SetDisplayModeForDisplay(other, शून्य);
                other->fullscreen_window = शून्य;
            }
        }
    }

    अगर (fullscreen) {
        पूर्णांक mode_w = 0, mode_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        अगर (display->fullscreen_window &&
            display->fullscreen_window != window) {
            SDL_MinimizeWindow(display->fullscreen_window);
        }

        display->fullscreen_active = window->fullscreen_exclusive;

        अगर (!SDL_SetDisplayModeForDisplay(display, mode)) {
            जाओ error;
        }
        अगर (commit) {
            SDL_Fullscreen_परिणाम ret = SDL_FULLSCREEN_SUCCEEDED;
            अगर (_this->SetWindowFullscreen) {
                ret = _this->SetWindowFullscreen(_this, window, display, fullscreen);
            } अन्यथा {
                resized = true;
            }

            अगर (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
                }
            } अन्यथा अगर (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_active = false;
                जाओ error;
            }
        }

        अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
            display->fullscreen_window = window;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            अगर (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                अगर (mode) {
                    mode_w = mode->w;
                    mode_h = mode->h;
                    SDL_GetDisplayBounds(mode->displayID, &displayRect);
                } अन्यथा {
                    mode_w = display->desktop_mode.w;
                    mode_h = display->desktop_mode.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                अगर (window->w != mode_w || window->h != mode_h) {
                    resized = true;
                }

                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, displayRect.x, displayRect.y);

                अगर (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, mode_w, mode_h);
                } अन्यथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    } अन्यथा {
        bool resized = false;

        // Restore the desktop mode
        अगर (display) {
            display->fullscreen_active = false;

            SDL_SetDisplayModeForDisplay(display, शून्य);
        }
        अगर (commit) {
            SDL_Fullscreen_परिणाम ret = SDL_FULLSCREEN_SUCCEEDED;
            अगर (_this->SetWindowFullscreen) {
                SDL_VideoDisplay *full_screen_display = display ? display : SDL_GetVideoDisplayForFullscreenWindow(window);
                अगर (full_screen_display) {
                    ret = _this->SetWindowFullscreen(_this, window, full_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } अन्यथा {
                resized = true;
            }

            अगर (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
                }
            } अन्यथा अगर (ret == SDL_FULLSCREEN_FAILED) {
                जाओ error;
            }
        }

        अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            अगर (display) {
                display->fullscreen_window = शून्य;
            }

            अगर (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, window->windowed.x, window->windowed.y);
                अगर (resized) {
                    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window->windowed.w, window->windowed.h);
                } अन्यथा {
                    SDL_OnWindowResized(window);
                }
            }
        }
    }

done:
    window->last_fullscreen_exclusive_display = display && (window->flags & SDL_WINDOW_FULLSCREEN) && window->fullscreen_exclusive ? display->id : 0;
    वापस true;

error:
    अगर (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    वापस false;
}

bool SDL_SetWindowFullscreenMode(SDL_Window *window, स्थिर SDL_DisplayMode *mode)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (mode) {
        अगर (!SDL_GetFullscreenModeMatch(mode)) {
            वापस SDL_SetError("Invalid fullscreen display mode");
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

#अगर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    अगर (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_IsWindowInFullscreenSpaceTransition(window)) {
        SDL_SyncWindow(window);
    }
#पूर्ण_अगर
    अगर (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(window);
    }

    वापस true;
}

स्थिर SDL_DisplayMode *SDL_GetWindowFullscreenMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, शून्य);
    CHECK_WINDOW_NOT_POPUP(window, शून्य);

    अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        वापस SDL_GetFullscreenModeMatch(&window->current_fullscreen_mode);
    } अन्यथा {
        वापस SDL_GetFullscreenModeMatch(&window->requested_fullscreen_mode);
    }
}

व्योम *SDL_GetWindowICCProfile(SDL_Window *window, माप_प्रकार *आकार)
{
    अगर (!_this->GetWindowICCProfile) {
        SDL_Unsupported();
        वापस शून्य;
    }
    वापस _this->GetWindowICCProfile(_this, window, आकार);
}

SDL_PixelFormat SDL_GetWindowPixelFormat(SDL_Window *window)
{
    SDL_DisplayID displayID;
    स्थिर SDL_DisplayMode *mode;

    CHECK_WINDOW_MAGIC(window, SDL_PIXELFORMAT_UNKNOWN);

    displayID = GetDisplayForWindow(window);
    mode = SDL_GetCurrentDisplayMode(displayID);
    अगर (mode) {
        वापस mode->format;
    } अन्यथा {
        वापस SDL_PIXELFORMAT_UNKNOWN;
    }
}

#घोषणा CREATE_FLAGS \
    (SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ऊपरी_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_शीर्ष | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_VULKAN | SDL_WINDOW_MINIMIZED | SDL_WINDOW_METAL | SDL_WINDOW_TRANSPARENT | SDL_WINDOW_NOT_FOCUSABLE | SDL_WINDOW_FILL_DOCUMENT)

अटल SDL_INLINE bool IsAcceptingDragAndDrop(व्योम)
{
    अगर (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        वापस true;
    }
    वापस false;
}

// prepare a newly-created window
अटल SDL_INLINE व्योम PrepareDragAndDropSupport(SDL_Window *window)
{
    अगर (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(window, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
व्योम SDL_ToggleDragAndDropSupport(व्योम)
{
    अगर (_this && _this->AcceptDragAndDrop) {
        स्थिर bool enable = IsAcceptingDragAndDrop();
        SDL_Window *window;
        क्रम (window = _this->windows; window; window = window->अग्र) {
            _this->AcceptDragAndDrop(window, enable);
        }
    }
}

SDL_Window ** SDLCALL SDL_GetWindows(पूर्णांक *गिनती)
{
    अगर (गिनती) {
        *गिनती = 0;
    }

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }

    SDL_Window *window;
    पूर्णांक अंक_added = 0;
    पूर्णांक अंक_windows = 0;
    क्रम (window = _this->windows; window; window = window->अग्र) {
        ++अंक_windows;
    }

    SDL_Window **windows = (SDL_Window **)SDL_malloc((अंक_windows + 1) * माप(*windows));
    अगर (!windows) {
        वापस शून्य;
    }

    क्रम (window = _this->windows; window; window = window->अग्र) {
        windows[अंक_added++] = window;
        अगर (अंक_added == अंक_windows) {
            // Race condition? Multi-threading not supported, ignore it
            अवरोध;
        }
    }
    windows[अंक_added] = शून्य;

    अगर (गिनती) {
        *गिनती = अंक_added;
    }
    वापस windows;
}

अटल व्योम ApplyWindowFlags(SDL_Window *window, SDL_WindowFlags flags)
{
    अगर (!SDL_WINDOW_IS_POPUP(window)) {
        अगर (!(flags & (SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED))) {
            SDL_RestoreWindow(window);
        }
        अगर (flags & SDL_WINDOW_MAXIMIZED) {
            SDL_MaximizeWindow(window);
        }

        SDL_SetWindowFullscreen(window, (flags & SDL_WINDOW_FULLSCREEN) != 0);

        अगर (flags & SDL_WINDOW_MINIMIZED) {
            SDL_MinimizeWindow(window);
        }

        अगर (flags & SDL_WINDOW_MODAL) {
            SDL_SetWindowModal(window, true);
        }

        अगर (flags & SDL_WINDOW_MOUSE_GRABBED) {
            SDL_SetWindowMouseGrab(window, true);
        }
        अगर (flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            SDL_SetWindowKeyboardGrab(window, true);
        }
    }
}

अटल व्योम SDL_FinishWindowCreation(SDL_Window *window, SDL_WindowFlags flags)
{
    PrepareDragAndDropSupport(window);

    अगर (window->flags & SDL_WINDOW_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } अन्यथा {
        ApplyWindowFlags(window, flags);
        अगर (!(flags & SDL_WINDOW_HIDDEN)) {
            SDL_ShowWindow(window);
        }
    }

#अगर defined(SDL_PLATFORM_LINUX)
    अगर (!SDL_WINDOW_IS_POPUP(window)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_SetWindowProgressState(window, SDL_PROGRESS_STATE_NONE);
        SDL_Set_Window_Progress_मूल्य(window, 0.0f);
    }
#पूर्ण_अगर
}

अटल bool SDL_ContextNotSupported(स्थिर अक्षर *name)
{
    वापस SDL_SetError("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

अटल bool SDL_DllNotSupported(स्थिर अक्षर *name)
{
    वापस SDL_SetError("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

अटल काष्ठा {
    स्थिर अक्षर *property_name;
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

अटल SDL_WindowFlags SDL_GetWindowFlagProperties(SDL_PropertiesID props)
{
    अचिन्हित i;
    SDL_WindowFlags flags = (SDL_WindowFlags)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, 0);

    क्रम (i = 0; i < SDL_arraysize(SDL_WindowFlagProperties); ++i) {
        अगर (SDL_WindowFlagProperties[i].invert_मूल्य) {
            अगर (!SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, true)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        } अन्यथा {
            अगर (SDL_GetBooleanProperty(props, SDL_WindowFlagProperties[i].property_name, false)) {
                flags |= SDL_WindowFlagProperties[i].flag;
            }
        }
    }
    वापस flags;
}

SDL_Window *SDL_CreateWindowWithProperties(SDL_PropertiesID props)
{
    SDL_Window *window;
    स्थिर अक्षर *title = SDL_GetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, शून्य);
    पूर्णांक x = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_संख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णांक y = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_संख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णांक w = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, 0);
    पूर्णांक h = (पूर्णांक)SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, 0);
    SDL_Window *parent = (SDL_Window *)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, शून्य);
    SDL_WindowFlags flags = SDL_GetWindowFlagProperties(props);
    SDL_WindowFlags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    अगर (!_this) {
        // Initialize the video system if needed
        अगर (!SDL_Init(SDL_INIT_VIDEO)) {
            वापस शून्य;
        }

        // Make clang-tidy happy
        अगर (!_this) {
            वापस शून्य;
        }
    }

    अगर ((flags & SDL_WINDOW_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
        SDL_SetError("Modal windows must specify a parent window");
        वापस शून्य;
    }

    अगर ((flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU)) != 0) {
        अगर (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_WINDOW_SUPPORT)) {
            SDL_Unsupported();
            वापस शून्य;
        }

        // Tooltip and popup menu window must specify a parent window
        अगर (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_WINDOW)) {
            SDL_SetError("Tooltip and popup menu windows must specify a parent window");
            वापस शून्य;
        }

        // Remove invalid flags
        flags &= ~(SDL_WINDOW_MINIMIZED | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_WINDOW_UTILITY | SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_MODAL);
    अगर (type_flags & (type_flags - 1)) {
        SDL_SetError("Conflicting window type flags specified: 0x%.8x", (अचिन्हित पूर्णांक)type_flags);
        वापस शून्य;
    }

    // Make sure the display list is up to date for window placement
    अगर (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    अगर (w < 1) {
        w = 1;
    }
    अगर (h < 1) {
        h = 1;
    }

    अगर (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        अगर ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा अगर ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        अगर (displayID == 0 || SDL_Get_Display_सूचकांक(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        अगर (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        अगर (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            अगर (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        अगर (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            अगर (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    अगर (graphics_flags & (graphics_flags - 1)) {
        SDL_SetError("Conflicting window graphics flags specified: 0x%.8x", (अचिन्हित पूर्णांक)graphics_flags);
        वापस शून्य;
    }

    // Some platforms have certain graphics backends enabled by default
    अगर (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    अगर (flags & SDL_WINDOW_OPENGL) {
        अगर (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            वापस शून्य;
        }
        अगर (!SDL_GL_LoadLibrary(शून्य)) {
            वापस शून्य;
        }
    }

    अगर (flags & SDL_WINDOW_VULKAN) {
        अगर (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            वापस शून्य;
        }
        अगर (!SDL_Vulkan_LoadLibrary(शून्य)) {
            वापस शून्य;
        }
    }

    अगर (flags & SDL_WINDOW_METAL) {
        अगर (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            वापस शून्य;
        }
    }

    window = (SDL_Window *)SDL_calloc(1, माप(*window));
    अगर (!window) {
        वापस शून्य;
    }
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, true);
    window->id = SDL_Get_अग्र_Object_ID();
    window->floating.x = window->windowed.x = window->x = x;
    window->floating.y = window->windowed.y = window->y = y;
    window->floating.w = window->windowed.w = window->w = w;
    window->floating.h = window->windowed.h = window->h = h;
    window->undefined_x = undefined_x;
    window->undefined_y = undefined_y;
    window->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_GetVideoDisplayForWindow(window);
    अगर (display) {
        SDL_SetWindowHDRProperties(window, &display->HDR, false);
    }

    अगर (flags & SDL_WINDOW_FULLSCREEN || IsFullscreenOnly(_this)) {
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
    window->अग्र = _this->windows;
    window->is_destroying = false;
    window->displayID = GetDisplayForWindow(window);
    window->external_graphics_context = external_graphics_context;
    window->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    अगर (!_this->SetWindowFillDocument) {
        window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    अगर (_this->windows) {
        _this->windows->पूर्व = window;
    }
    _this->windows = window;

    // Set the parent before creation.
    SDL_UpdateWindowHierarchy(window, parent);

    अगर (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, window, props)) {
        SDL_धकेलो_Error();
        SDL_DestroyWindow(window);
        SDL_निकालो_Error();
        वापस शून्य;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#अगर !defined(SDL_PLATFORM_WINDOWS)
    अगर (window->flags & SDL_WINDOW_MINIMIZED) {
        window->flags &= ~SDL_WINDOW_MINIMIZED;
    }
#पूर्ण_अगर

    अगर (title) {
        SDL_SetWindowTitle(window, title);
    }
    SDL_FinishWindowCreation(window, flags);

    // Make sure window pixel size is up to date
    SDL_Check_Window_Pixel_आकार_Changed(window);

#अगर_घोषित SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#पूर्ण_अगर

    SDL_ClearError();

    वापस window;
}

SDL_Window *SDL_CreateWindow(स्थिर अक्षर *title, पूर्णांक w, पूर्णांक h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();
    अगर (title && *title) {
        SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, w);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, h);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    वापस window;
}

SDL_Window *SDL_CreatePopupWindow(SDL_Window *parent, पूर्णांक offset_x, पूर्णांक offset_y, पूर्णांक w, पूर्णांक h, SDL_WindowFlags flags)
{
    SDL_Window *window;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    अगर (!(flags & (SDL_WINDOW_TOOLTIP | SDL_WINDOW_POPUP_MENU))) {
        SDL_SetError("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        वापस शून्य;
    }

    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_X_संख्या, offset_x);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_Y_संख्या, offset_y);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_WIDTH_संख्या, w);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_HEIGHT_संख्या, h);
    SDL_Set_संख्या_Property(props, SDL_PROP_WINDOW_CREATE_FLAGS_संख्या, flags);
    window = SDL_CreateWindowWithProperties(props);
    SDL_DestroyProperties(props);
    वापस window;
}

अटल bool SDL_ReconfigureWindowInternal(SDL_Window *window, SDL_WindowFlags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    अगर (!_this->ReconfigureWindow) {
        वापस false;
    }

    स्थिर SDL_WindowFlags graphics_flags = flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    अगर (graphics_flags & (graphics_flags - 1)) {
        वापस SDL_SetError("Conflicting window flags specified");
    }

    अगर ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        वापस SDL_ContextNotSupported("OpenGL");
    }
    अगर ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        वापस SDL_ContextNotSupported("Vulkan");
    }
    अगर ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        वापस SDL_ContextNotSupported("Metal");
    }

    अगर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        अगर (window->flags & (SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN)) {
            वापस false;
        }
    } अन्यथा {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        अगर (!_this->ReconfigureWindow(_this, window, 0)) {
            वापस false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        अगर (window->flags & SDL_WINDOW_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        अगर (window->flags & SDL_WINDOW_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        window->flags &= ~(SDL_WINDOW_OPENGL | SDL_WINDOW_METAL | SDL_WINDOW_VULKAN);
    }

    SDL_DestroyWindowSurface(window);

    अगर (graphics_flags & SDL_WINDOW_OPENGL) {
        loaded_opengl = SDL_GL_LoadLibrary(शून्य);
        अगर (!loaded_opengl) {
            वापस false;
        }
    } अन्यथा अगर (graphics_flags & SDL_WINDOW_VULKAN) {
        loaded_vulkan = SDL_Vulkan_LoadLibrary(शून्य);
        अगर (!loaded_vulkan) {
            वापस false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    अगर (!_this->ReconfigureWindow(_this, window, graphics_flags)) {
        अगर (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        अगर (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        वापस false;
    }

    window->flags |= graphics_flags;

    वापस true;
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
    अगर (graphics_flags & (graphics_flags - 1)) {
        वापस SDL_SetError("Conflicting window flags specified");
    }

    अगर ((flags & SDL_WINDOW_OPENGL) && !_this->GL_CreateContext) {
        वापस SDL_ContextNotSupported("OpenGL");
    }
    अगर ((flags & SDL_WINDOW_VULKAN) && !_this->Vulkan_CreateSurface) {
        वापस SDL_ContextNotSupported("Vulkan");
    }
    अगर ((flags & SDL_WINDOW_METAL) && !_this->Metal_CreateView) {
        वापस SDL_ContextNotSupported("Metal");
    }

    अगर (window->flags & SDL_WINDOW_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_WINDOW_EXTERNAL;
    } अन्यथा {
        flags &= ~SDL_WINDOW_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    अगर (window->flags & SDL_WINDOW_MODAL) {
        SDL_SetWindowModal(window, false);
    }

    // Restore video mode, etc.
    अगर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        स्थिर bool restore_on_show = window->restore_on_show;
        SDL_HideWindow(window);
        window->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_DestroyWindowSurface(window);

    अगर ((window->flags & SDL_WINDOW_OPENGL) != (flags & SDL_WINDOW_OPENGL)) {
        अगर (flags & SDL_WINDOW_OPENGL) {
            need_gl_load = true;
        } अन्यथा {
            need_gl_unload = true;
        }
    } अन्यथा अगर (window->flags & SDL_WINDOW_OPENGL) {
        need_gl_unload = true;
        need_gl_load = true;
    }

    अगर ((window->flags & SDL_WINDOW_VULKAN) != (flags & SDL_WINDOW_VULKAN)) {
        अगर (flags & SDL_WINDOW_VULKAN) {
            need_vulkan_load = true;
        } अन्यथा {
            need_vulkan_unload = true;
        }
    } अन्यथा अगर (window->flags & SDL_WINDOW_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_load = true;
    }

    अगर (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    अगर (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    अगर (_this->DestroyWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        _this->DestroyWindow(_this, window);
    }

    अगर (need_gl_load) {
        अगर (!SDL_GL_LoadLibrary(शून्य)) {
            वापस false;
        }
        loaded_opengl = true;
    }

    अगर (need_vulkan_load) {
        अगर (!SDL_Vulkan_LoadLibrary(शून्य)) {
            वापस false;
        }
        loaded_vulkan = true;
    }

    window->flags = ((flags & CREATE_FLAGS) | SDL_WINDOW_HIDDEN);
    window->is_destroying = false;

    अगर (_this->CreateSDLWindow && !(flags & SDL_WINDOW_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        window->x = window->windowed.x = window->floating.x;
        window->y = window->windowed.y = window->floating.y;
        window->w = window->windowed.w = window->floating.w;
        window->h = window->windowed.h = window->floating.h;

        अगर (!_this->CreateSDLWindow(_this, window, 0)) {
            अगर (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_OPENGL;
            }
            अगर (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                window->flags &= ~SDL_WINDOW_VULKAN;
            }
            वापस false;
        }
    }

    अगर (flags & SDL_WINDOW_EXTERNAL) {
        window->flags |= SDL_WINDOW_EXTERNAL;
    }

    अगर (_this->SetWindowTitle && window->title) {
        _this->SetWindowTitle(_this, window);
    }

    अगर (_this->SetWindowIcon && window->icon) {
        _this->SetWindowIcon(_this, window, window->icon);
    }

    अगर (_this->Set_Window_Minimum_आकार && (window->min_w || window->min_h)) {
        _this->Set_Window_Minimum_आकार(_this, window);
    }

    अगर (_this->Set_Window_Maximum_आकार && (window->max_w || window->max_h)) {
        _this->Set_Window_Maximum_आकार(_this, window);
    }

    अगर (_this->SetWindowAspectRatio && (window->min_aspect > 0.0f || window->max_aspect > 0.0f)) {
        _this->SetWindowAspectRatio(_this, window);
    }

    अगर (window->hit_test) {
        _this->SetWindowHitTest(window, true);
    }

    SDL_FinishWindowCreation(window, flags);

    वापस true;
}

bool SDL_ReconfigureWindow(SDL_Window *window, SDL_WindowFlags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    अगर (!SDL_ReconfigureWindowInternal(window, flags)) {
        वापस SDL_RecreateWindow(window, flags);
    }

    वापस true;
}

bool SDL_HasWindows(व्योम)
{
    वापस _this && _this->windows;
}

SDL_WindowID SDL_GetWindowID(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    वापस window->id;
}

SDL_Window *SDL_GetWindowFromID(SDL_WindowID id)
{
    SDL_Window *window;

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    अगर (id) {
        क्रम (window = _this->windows; window; window = window->अग्र) {
            अगर (window->id == id) {
                वापस window;
            }
        }
    }
    SDL_SetError("Invalid window ID");
    वापस शून्य;
}

SDL_Window *SDL_GetWindowParent(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, शून्य);

    वापस window->parent;
}

SDL_PropertiesID SDL_GetWindowProperties(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    अगर (window->props == 0) {
        window->props = SDL_CreateProperties();
    }
    वापस window->props;
}

SDL_WindowFlags SDL_GetWindowFlags(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, 0);

    वापस window->flags | window->pending_flags;
}

bool SDL_SetWindowTitle(SDL_Window *window, स्थिर अक्षर *title)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (title == window->title) {
        वापस true;
    }
    अगर (!title) {
        title = "";
    }
    अगर (window->title && SDL_strcmp(title, window->title) == 0) {
        वापस true;
    }

    SDL_free(window->title);

    window->title = SDL_strdup(title);

    अगर (_this->SetWindowTitle) {
        _this->SetWindowTitle(_this, window);
    }
    वापस true;
}

स्थिर अक्षर *SDL_GetWindowTitle(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, "");

    वापस window->title ? window->title : "";
}

bool SDL_SetWindowIcon(SDL_Window *window, SDL_Surface *icon)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(!icon) {
        वापस SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(window->icon);

    // Convert the icon into ARGB8888
    window->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    अगर (!window->icon) {
        वापस false;
    }

    अगर (!_this->SetWindowIcon) {
        वापस SDL_Unsupported();
    }

    वापस _this->SetWindowIcon(_this, window, window->icon);
}

bool SDL_SetWindowPosition(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    SDL_DisplayID original_displayID;

    CHECK_WINDOW_MAGIC(window, false);

    स्थिर पूर्णांक w = window->last_आकार_pending ? window->pending.w : window->windowed.w;
    स्थिर पूर्णांक h = window->last_आकार_pending ? window->pending.h : window->windowed.h;

    original_displayID = GetDisplayForWindow(window);
    window->pending_displayID = 0;

    अगर (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = window->windowed.x;
    }
    अगर (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = window->windowed.y;
    }
    अगर (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        अगर (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा अगर (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        अगर (displayID == 0 || SDL_Get_Display_सूचकांक(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        window->pending_displayID = displayID;

        SDL_zero(bounds);
        अगर (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            अगर (!SDL_GetDisplayBounds(displayID, &bounds)) {
                वापस false;
            }
        }
        अगर (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        अगर (SDL_WINDOWPOS_ISCENTERED(y)) {
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
    अगर (!_this->SyncWindow && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        window->floating.x = window->windowed.x = x;
        window->floating.y = window->windowed.y = y;
    }
    window->undefined_x = false;
    window->undefined_y = false;
    window->last_position_pending = true;

    अगर (_this->SetWindowPosition) {
        स्थिर bool परिणाम = _this->SetWindowPosition(_this, window);
        अगर (परिणाम) {
            SDL_SyncIfRequired(window);
        }
        वापस परिणाम;
    }

    वापस SDL_Unsupported();
}

bool SDL_GetWindowPosition(SDL_Window *window, पूर्णांक *x, पूर्णांक *y)
{
    CHECK_WINDOW_MAGIC(window, false);

#अगर_घोषित SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#अन्यथा
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((window->flags & SDL_WINDOW_FULLSCREEN) != 0);
#पूर्ण_अगर
    अगर (use_display_origin) {
        SDL_DisplayID displayID;

        अगर (x) {
            *x = 0;
        }
        अगर (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = GetDisplayForWindow(window);
        अगर (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            अगर (x) {
                *x = bounds.x;
            }
            अगर (y) {
                *y = bounds.y;
            }
        }
    } अन्यथा {
        स्थिर bool use_pending = (window->flags & SDL_WINDOW_HIDDEN) && window->last_position_pending;
        अगर (x) {
            *x = use_pending ? window->pending.x : window->x;
        }
        अगर (y) {
            *y = use_pending ? window->pending.y : window->y;
        }
    }
    वापस true;
}

bool SDL_SetWindowBordered(SDL_Window *window, bool bordered)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (!_this->SetWindowBordered) {
        वापस SDL_Unsupported();
    }

    स्थिर bool want = bordered;
    स्थिर bool have = !(window->flags & SDL_WINDOW_BORDERLESS);
    अगर (want != have) {
        अगर (want) {
            window->flags &= ~SDL_WINDOW_BORDERLESS;
        } अन्यथा {
            window->flags |= SDL_WINDOW_BORDERLESS;
        }
        _this->SetWindowBordered(_this, window, want);
    }

    वापस true;
}

bool SDL_SetWindowResizable(SDL_Window *window, bool resizable)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (!_this->SetWindowResizable) {
        वापस SDL_Unsupported();
    }

    स्थिर bool want = resizable;
    स्थिर bool have = ((window->flags & SDL_WINDOW_RESIZABLE) != 0);
    अगर (want != have) {
        अगर (want) {
            window->flags |= SDL_WINDOW_RESIZABLE;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_RESIZABLE;
            SDL_copyp(&window->windowed, &window->floating);
        }
        _this->SetWindowResizable(_this, window, want);
    }

    वापस true;
}

bool SDL_Set_Window_Always_On_शीर्ष(SDL_Window *window, bool on_शीर्ष)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (!_this->Set_Window_Always_On_शीर्ष) {
        वापस SDL_Unsupported();
    }

    स्थिर bool want = on_शीर्ष;
    स्थिर bool have = ((window->flags & SDL_WINDOW_ALWAYS_ON_शीर्ष) != 0);
    अगर (want != have) {
        अगर (want) {
            window->flags |= SDL_WINDOW_ALWAYS_ON_शीर्ष;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_ALWAYS_ON_शीर्ष;
        }
        _this->Set_Window_Always_On_शीर्ष(_this, window, want);
    }

    वापस true;
}

bool SDL_Set_Window_आकार(SDL_Window *window, पूर्णांक w, पूर्णांक h)
{
    CHECK_WINDOW_MAGIC(window, false);

    CHECK_PARAM(w <= 0) {
        वापस SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        वापस SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    भग्न new_aspect = w / (भग्न)h;
    अगर (window->max_aspect > 0.0f && new_aspect > window->max_aspect) {
        w = (पूर्णांक)SDL_roundf(h * window->max_aspect);
    } अन्यथा अगर (window->min_aspect > 0.0f && new_aspect < window->min_aspect) {
        h = (पूर्णांक)SDL_roundf(w / window->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    अगर (window->min_w && w < window->min_w) {
        w = window->min_w;
    }
    अगर (window->max_w && w > window->max_w) {
        w = window->max_w;
    }
    अगर (window->min_h && h < window->min_h) {
        h = window->min_h;
    }
    अगर (window->max_h && h > window->max_h) {
        h = window->max_h;
    }

    window->last_आकार_pending = true;
    window->pending.w = w;
    window->pending.h = h;

    अगर (_this->Set_Window_आकार) {
        _this->Set_Window_आकार(_this, window);
        SDL_SyncIfRequired(window);
    } अन्यथा {
        वापस SDL_Unsupported();
    }
    वापस true;
}

bool SDL_Get_Window_आकार(SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    CHECK_WINDOW_MAGIC(window, false);
    अगर (w) {
        *w = window->w;
    }
    अगर (h) {
        *h = window->h;
    }
    वापस true;
}

bool SDL_SetWindowAspectRatio(SDL_Window *window, भग्न min_aspect, भग्न max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    window->min_aspect = min_aspect;
    window->max_aspect = max_aspect;

    अगर (_this->SetWindowAspectRatio) {
        _this->SetWindowAspectRatio(_this, window);
    }

    // Ensure that window has the correct aspect ratio
    पूर्णांक w = window->last_आकार_pending ? window->pending.w : window->floating.w;
    पूर्णांक h = window->last_आकार_pending ? window->pending.h : window->floating.h;
    वापस SDL_Set_Window_आकार(window, w, h);
}

bool SDL_GetWindowAspectRatio(SDL_Window *window, भग्न *min_aspect, भग्न *max_aspect)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (min_aspect) {
        *min_aspect = window->min_aspect;
    }
    अगर (max_aspect) {
        *max_aspect = window->max_aspect;
    }
    वापस true;
}

bool SDL_Get_Window_Borders_आकार(SDL_Window *window, पूर्णांक *शीर्ष, पूर्णांक *बायाँ, पूर्णांक *bottom, पूर्णांक *दायाँ)
{
    पूर्णांक dummy = 0;

    अगर (!शीर्ष) {
        शीर्ष = &dummy;
    }
    अगर (!बायाँ) {
        बायाँ = &dummy;
    }
    अगर (!दायाँ) {
        दायाँ = &dummy;
    }
    अगर (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *शीर्ष = *बायाँ = *bottom = *दायाँ = 0;

    CHECK_WINDOW_MAGIC(window, false);

    अगर (!_this->Get_Window_Borders_आकार) {
        वापस SDL_Unsupported();
    }

    वापस _this->Get_Window_Borders_आकार(_this, window, शीर्ष, बायाँ, bottom, दायाँ);
}

bool SDL_Get_Window_आकार_In_Pixels(SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    पूर्णांक filter;

    CHECK_WINDOW_MAGIC(window, false);

    अगर (!w) {
        w = &filter;
    }

    अगर (!h) {
        h = &filter;
    }

    अगर (_this->Get_Window_आकार_In_Pixels) {
        _this->Get_Window_आकार_In_Pixels(_this, window, w, h);
    } अन्यथा {
        SDL_DisplayID displayID = GetDisplayForWindow(window);
        स्थिर SDL_DisplayMode *mode;

        SDL_Get_Window_आकार(window, w, h);

        अगर ((window->flags & SDL_WINDOW_FULLSCREEN) && SDL_GetWindowFullscreenMode(window)) {
            mode = SDL_GetCurrentDisplayMode(displayID);
        } अन्यथा {
            mode = SDL_GetDesktopDisplayMode(displayID);
        }
        अगर (mode) {
            *w = (पूर्णांक)SDL_ceilf(*w * mode->pixel_density);
            *h = (पूर्णांक)SDL_ceilf(*h * mode->pixel_density);
        }
    }
    वापस true;
}

bool SDL_Set_Window_Minimum_आकार(SDL_Window *window, पूर्णांक min_w, पूर्णांक min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(min_w < 0) {
        वापस SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        वापस SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((window->max_w && min_w > window->max_w) || (window->max_h && min_h > window->max_h)) {
        वापस SDL_SetError("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    window->min_w = min_w;
    window->min_h = min_h;

    अगर (_this->Set_Window_Minimum_आकार) {
        _this->Set_Window_Minimum_आकार(_this, window);
    }

    // Ensure that window is not smaller than minimal size
    पूर्णांक w = window->last_आकार_pending ? window->pending.w : window->floating.w;
    पूर्णांक h = window->last_आकार_pending ? window->pending.h : window->floating.h;
    वापस SDL_Set_Window_आकार(window, w, h);
}

bool SDL_Get_Window_Minimum_आकार(SDL_Window *window, पूर्णांक *min_w, पूर्णांक *min_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    अगर (min_w) {
        *min_w = window->min_w;
    }
    अगर (min_h) {
        *min_h = window->min_h;
    }
    वापस true;
}

bool SDL_Set_Window_Maximum_आकार(SDL_Window *window, पूर्णांक max_w, पूर्णांक max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_PARAM(max_w < 0) {
        वापस SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        वापस SDL_InvalidParamError("max_h");
    }

    अगर ((max_w && max_w < window->min_w) ||
        (max_h && max_h < window->min_h)) {
        वापस SDL_SetError("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    window->max_w = max_w;
    window->max_h = max_h;

    अगर (_this->Set_Window_Maximum_आकार) {
        _this->Set_Window_Maximum_आकार(_this, window);
    }

    // Ensure that window is not larger than maximal size
    पूर्णांक w = window->last_आकार_pending ? window->pending.w : window->floating.w;
    पूर्णांक h = window->last_आकार_pending ? window->pending.h : window->floating.h;
    वापस SDL_Set_Window_आकार(window, w, h);
}

bool SDL_Get_Window_Maximum_आकार(SDL_Window *window, पूर्णांक *max_w, पूर्णांक *max_h)
{
    CHECK_WINDOW_MAGIC(window, false);
    अगर (max_w) {
        *max_w = window->max_w;
    }
    अगर (max_h) {
        *max_h = window->max_h;
    }
    वापस true;
}

bool SDL_ShowWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!(window->flags & SDL_WINDOW_HIDDEN)) {
        वापस true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    अगर (window->parent && (window->parent->flags & SDL_WINDOW_HIDDEN)) {
        window->restore_on_show = true;
        वापस true;
    }

    अगर (_this->ShowWindow) {
        _this->ShowWindow(_this, window);
    } अन्यथा {
        SDL_SetMouseFocus(window);
        SDL_SetKeyboardFocus(window);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);

    // Restore child windows
    क्रम (child = window->first_child; child; child = child->अग्र_sibling) {
        अगर (!child->restore_on_show && (child->flags & SDL_WINDOW_HIDDEN)) {
            अवरोध;
        }
        SDL_ShowWindow(child);
        child->restore_on_show = false;
    }
    वापस true;
}

bool SDL_HideWindow(SDL_Window *window)
{
    SDL_Window *child;
    CHECK_WINDOW_MAGIC(window, false);

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        window->restore_on_show = false;
        वापस true;
    }

    // Hide all child windows
    क्रम (child = window->first_child; child; child = child->अग्र_sibling) {
        अगर (child->flags & SDL_WINDOW_HIDDEN) {
            अवरोध;
        }
        SDL_HideWindow(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    स्थिर SDL_WindowFlags pending_mask = (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_GRABBED);
    window->pending_flags = (window->flags & pending_mask);

    window->is_hiding = true;
    अगर (_this->HideWindow) {
        _this->HideWindow(_this, window);
    } अन्यथा {
        SDL_SetMouseFocus(शून्य);
        SDL_SetKeyboardFocus(शून्य);
    }
    window->is_hiding = false;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_HIDDEN, 0, 0);
    वापस true;
}

bool SDL_RaiseWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        वापस true;
    }
    अगर (_this->RaiseWindow) {
        _this->RaiseWindow(_this, window);
    }
    वापस true;
}

bool SDL_MaximizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (!_this->MaximizeWindow) {
        वापस SDL_Unsupported();
    }

    अगर (!(window->flags & SDL_WINDOW_RESIZABLE)) {
        वापस SDL_SetError("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MAXIMIZED;
        वापस true;
    }

    _this->MaximizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    वापस true;
}

bool SDL_MinimizeWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (!_this->MinimizeWindow) {
        वापस SDL_Unsupported();
    }

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags |= SDL_WINDOW_MINIMIZED;
        वापस true;
    }

    _this->MinimizeWindow(_this, window);
    SDL_SyncIfRequired(window);
    वापस true;
}

bool SDL_RestoreWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (!_this->RestoreWindow) {
        वापस SDL_Unsupported();
    }

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        window->pending_flags &= ~(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED);
        वापस true;
    }

    _this->RestoreWindow(_this, window);
    SDL_SyncIfRequired(window);
    वापस true;
}

bool SDL_SetWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    bool परिणाम;

    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        अगर (fullscreen) {
            window->pending_flags |= SDL_WINDOW_FULLSCREEN;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_FULLSCREEN;
        }
        वापस true;
    }

    अगर (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
    }

    परिणाम = SDL_UpdateFullscreenMode(window, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    अगर (!fullscreen || !परिणाम) {
        // Clear the current fullscreen mode.
        SDL_zero(window->current_fullscreen_mode);
    }

    अगर (परिणाम) {
        SDL_SyncIfRequired(window);
    }

    वापस परिणाम;
}

bool SDL_SyncWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (_this->SyncWindow) {
        वापस _this->SyncWindow(_this, window);
    } अन्यथा {
        वापस true;
    }
}

अटल bool ShouldAttemptTextureFramebuffer(व्योम)
{
    स्थिर अक्षर *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    अगर (!_this->CreateWindowFramebuffer) {
        वापस true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    अगर (hint && *hint) {
        अगर (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } अन्यथा {
            attempt_texture_framebuffer = true;
        }
    } अन्यथा {
        अगर (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } अन्यथा {
            attempt_texture_framebuffer = false;
        }
    }
    वापस attempt_texture_framebuffer;
}

अटल SDL_Surface *SDL_CreateWindowFramebuffer(SDL_Window *window)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    व्योम *pixels = शून्य;
    पूर्णांक pitch = 0;
    bool created_framebuffer = false;
    पूर्णांक w, h;

    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    अगर (!_this->checked_texture_framebuffer) {
        अगर (ShouldAttemptTextureFramebuffer()) {
            अगर (!SDL_CreateWindowTexture(_this, window, &format, &pixels, &pitch)) {
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

    अगर (!created_framebuffer) {
        अगर (!_this->CreateWindowFramebuffer || !_this->UpdateWindowFramebuffer) {
            SDL_SetError("Window framebuffer support not available");
            वापस शून्य;
        }

        अगर (!_this->CreateWindowFramebuffer(_this, window, &format, &pixels, &pitch)) {
            वापस शून्य;
        }
    }

    अगर (window->surface) {
        // We may have gone recursive and already created the surface
        वापस window->surface;
    }

    वापस SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_WindowHasSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    वापस window->surface ? true : false;
}

SDL_Surface *SDL_GetWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, शून्य);

    अगर (!window->surface_valid) {
        अगर (window->surface) {
            window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
            SDL_DestroySurface(window->surface);
            window->surface = शून्य;
        }

        window->surface = SDL_CreateWindowFramebuffer(window);
        अगर (window->surface) {
            window->surface_valid = true;
            window->surface->internal_flags |= SDL_INTERNAL_SURFACE_DONTFREE;
        }
    }
    वापस window->surface;
}

bool SDL_SetWindowSurfaceVSync(SDL_Window *window, पूर्णांक vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!_this->SetWindowFramebufferVSync) {
        वापस SDL_Unsupported();
    }
    वापस _this->SetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_GetWindowSurfaceVSync(SDL_Window *window, पूर्णांक *vsync)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!_this->GetWindowFramebufferVSync) {
        वापस SDL_Unsupported();
    }
    वापस _this->GetWindowFramebufferVSync(_this, window, vsync);
}

bool SDL_UpdateWindowSurface(SDL_Window *window)
{
    SDL_Rect full_rect;

    CHECK_WINDOW_MAGIC(window, false);

    full_rect.x = 0;
    full_rect.y = 0;
    SDL_Get_Window_आकार_In_Pixels(window, &full_rect.w, &full_rect.h);

    वापस SDL_UpdateWindowSurfaceRects(window, &full_rect, 1);
}

bool SDL_UpdateWindowSurfaceRects(SDL_Window *window, स्थिर SDL_Rect *rects,
                                 पूर्णांक numrects)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!window->surface_valid) {
        वापस SDL_SetError("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    वापस _this->UpdateWindowFramebuffer(_this, window, rects, numrects);
}

bool SDL_DestroyWindowSurface(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (window->surface) {
        window->surface->internal_flags &= ~SDL_INTERNAL_SURFACE_DONTFREE;
        SDL_DestroySurface(window->surface);
        window->surface = शून्य;
        window->surface_valid = false;
    }

    अगर (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        अगर (_this->DestroyWindowFramebuffer) {
            _this->DestroyWindowFramebuffer(_this, window);
        }
    }
    वापस true;
}

bool SDL_SetWindowOpacity(SDL_Window *window, भग्न opacity)
{
    bool परिणाम;

    CHECK_WINDOW_MAGIC(window, false);

    अगर (!_this->SetWindowOpacity) {
        वापस SDL_Unsupported();
    }

    अगर (opacity < 0.0f) {
        opacity = 0.0f;
    } अन्यथा अगर (opacity > 1.0f) {
        opacity = 1.0f;
    }

    परिणाम = _this->SetWindowOpacity(_this, window, opacity);
    अगर (परिणाम) {
        window->opacity = opacity;
    }

    वापस परिणाम;
}

भग्न SDL_GetWindowOpacity(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);

    वापस window->opacity;
}

bool SDL_SetWindowParent(SDL_Window *window, SDL_Window *parent)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (parent) {
        CHECK_WINDOW_MAGIC(parent, false);
        CHECK_WINDOW_NOT_POPUP(parent, false);
    }

    अगर (window == parent) {
        वापस SDL_SetError("Cannot set the parent of a window to itself.");
    }

    अगर (!_this->SetWindowParent) {
        वापस SDL_Unsupported();
    }

    अगर (window->flags & SDL_WINDOW_MODAL) {
        वापस SDL_SetError("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    अगर (window->parent == parent) {
        वापस true;
    }

    स्थिर bool ret = _this->SetWindowParent(_this, window, parent);
    SDL_UpdateWindowHierarchy(window, ret ? parent : शून्य);

    वापस ret;
}

bool SDL_SetWindowModal(SDL_Window *window, bool modal)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (!_this->SetWindowModal) {
        वापस SDL_Unsupported();
    }

    अगर (modal) {
        अगर (!window->parent) {
            वापस SDL_SetError("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        window->flags |= SDL_WINDOW_MODAL;
    } अन्यथा अगर (window->flags & SDL_WINDOW_MODAL) {
        window->flags &= ~SDL_WINDOW_MODAL;
    } अन्यथा {
        वापस true; // Already not modal, so nothing to do.
    }

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        वापस true;
    }

    वापस _this->SetWindowModal(_this, window, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_Window *window, SDL_Window **new_focus)
{
    SDL_Window *focus = window->parent;
    bool set_focus = !!(window->flags & SDL_WINDOW_निवेश_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    जबतक (SDL_WINDOW_IS_POPUP(focus) && ((focus->flags & SDL_WINDOW_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        अगर (!set_focus) {
            set_focus = !!(focus->flags & SDL_WINDOW_निवेश_FOCUS);
        }
    }

    *new_focus = focus;
    वापस set_focus;
}

bool SDL_ShouldFocusPopup(SDL_Window *window)
{
    SDL_Window *toplevel_parent;
    क्रम (toplevel_parent = window->parent; SDL_WINDOW_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_Window *current_focus = toplevel_parent->keyboard_focus;
    bool found_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_Window *w;
    क्रम (w = current_focus; w != toplevel_parent; w = w->parent) {
        अगर (w == window) {
            found_higher_focus = true;
            अवरोध;
        }
    }

    वापस !found_higher_focus || w == toplevel_parent;
}

bool SDL_SetWindowFocusable(SDL_Window *window, bool focusable)
{
    CHECK_WINDOW_MAGIC(window, false);

    स्थिर bool want = (focusable != false); // normalize the flag.
    स्थिर bool have = !(window->flags & SDL_WINDOW_NOT_FOCUSABLE);
    अगर ((want != have) && (_this->SetWindowFocusable)) {
        अगर (want) {
            window->flags &= ~SDL_WINDOW_NOT_FOCUSABLE;
        } अन्यथा {
            window->flags |= SDL_WINDOW_NOT_FOCUSABLE;
        }
        अगर (!_this->SetWindowFocusable(_this, window, want)) {
            वापस false;
        }
    }

    वापस true;
}

bool SDL_SetWindowFillDocument(SDL_Window *window, bool fill)
{
    CHECK_WINDOW_MAGIC(window, false);

    स्थिर bool want = (fill != false); // normalize the flag.
    स्थिर bool have = ((window->flags & SDL_WINDOW_FILL_DOCUMENT) != 0);
    अगर ((want != have) && (_this->SetWindowFillDocument)) {
        अगर (!_this->SetWindowFillDocument(_this, window, want)) {
            वापस false;
        } अन्यथा अगर (want) {
            window->flags |= SDL_WINDOW_FILL_DOCUMENT;
        } अन्यथा {
            window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;
        }
    }

    वापस true;
}

व्योम SDL_UpdateWindowGrab(SDL_Window *window)
{
    bool keyboard_grabbed, mouse_grabbed;

    अगर (window->flags & SDL_WINDOW_निवेश_FOCUS) {
        अगर (SDL_GetMouse()->relative_mode || (window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } अन्यथा {
            mouse_grabbed = false;
        }

        अगर (window->flags & SDL_WINDOW_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } अन्यथा {
            keyboard_grabbed = false;
        }
    } अन्यथा {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    अगर (mouse_grabbed || keyboard_grabbed) {
        अगर (_this->grabbed_window && (_this->grabbed_window != window)) {
            // stealing a grab from another window!
            _this->grabbed_window->flags &= ~(SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED);
            अगर (_this->SetWindowMouseGrab) {
                _this->SetWindowMouseGrab(_this, _this->grabbed_window, false);
            }
            अगर (_this->SetWindowKeyboardGrab) {
                _this->SetWindowKeyboardGrab(_this, _this->grabbed_window, false);
            }
        }
        _this->grabbed_window = window;
    } अन्यथा अगर (_this->grabbed_window == window) {
        _this->grabbed_window = शून्य; // ungrabbing input.
    }

    अगर (_this->SetWindowMouseGrab) {
        अगर (!_this->SetWindowMouseGrab(_this, window, mouse_grabbed)) {
            window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
    }
    अगर (_this->SetWindowKeyboardGrab) {
        अगर (!_this->SetWindowKeyboardGrab(_this, window, keyboard_grabbed)) {
            window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
    }

    अगर (_this->grabbed_window && !(_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED))) {
        _this->grabbed_window = शून्य;
    }
}

bool SDL_SetWindowKeyboardGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        अगर (grabbed) {
            window->pending_flags |= SDL_WINDOW_KEYBOARD_GRABBED;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
        }
        वापस true;
    }

    अगर (!!grabbed == !!(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        वापस true;
    }
    अगर (grabbed) {
        window->flags |= SDL_WINDOW_KEYBOARD_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_KEYBOARD_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    अगर (grabbed && !(window->flags & SDL_WINDOW_KEYBOARD_GRABBED)) {
        वापस false;
    }
    वापस true;
}

bool SDL_SetWindowMouseGrab(SDL_Window *window, bool grabbed)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (window->flags & SDL_WINDOW_HIDDEN) {
        अगर (grabbed) {
            window->pending_flags |= SDL_WINDOW_MOUSE_GRABBED;
        } अन्यथा {
            window->pending_flags &= ~SDL_WINDOW_MOUSE_GRABBED;
        }
        वापस true;
    }

    अगर (!!grabbed == !!(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        वापस true;
    }
    अगर (grabbed) {
        window->flags |= SDL_WINDOW_MOUSE_GRABBED;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_MOUSE_GRABBED;
    }
    SDL_UpdateWindowGrab(window);

    अगर (grabbed && !(window->flags & SDL_WINDOW_MOUSE_GRABBED)) {
        वापस false;
    }
    वापस true;
}

bool SDL_GetWindowKeyboardGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    वापस window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_KEYBOARD_GRABBED);
}

bool SDL_GetWindowMouseGrab(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);
    वापस window == _this->grabbed_window && (_this->grabbed_window->flags & SDL_WINDOW_MOUSE_GRABBED);
}

SDL_Window *SDL_GetGrabbedWindow(व्योम)
{
    अगर (_this && _this->grabbed_window &&
        (_this->grabbed_window->flags & (SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_KEYBOARD_GRABBED)) != 0) {
        वापस _this->grabbed_window;
    } अन्यथा {
        वापस शून्य;
    }
}

bool SDL_SetWindowMouseRect(SDL_Window *window, स्थिर SDL_Rect *rect)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!_this->SetWindowMouseRect) {
        वापस SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    अगर (!rect) {
        rect = &zero;
    }

    अगर (SDL_memcmp(&window->mouse_rect, rect, माप(*rect)) == 0) {
        वापस true;
    }
    SDL_memcpy(&window->mouse_rect, rect, माप(*rect));

    वापस _this->SetWindowMouseRect(_this, window);
}

स्थिर SDL_Rect *SDL_GetWindowMouseRect(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, शून्य);

    अगर (SDL_RectEmpty(&window->mouse_rect)) {
        वापस शून्य;
    } अन्यथा {
        वापस &window->mouse_rect;
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

    अगर (enabled == SDL_GetWindowRelativeMouseMode(window)) {
        वापस true;
    }

    अगर (enabled) {
        window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
    } अन्यथा {
        window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
    }

    अगर (!SDL_UpdateRelativeMouseMode()) {
        अगर (enabled) {
            window->flags &= ~SDL_WINDOW_MOUSE_RELATIVE_MODE;
        } अन्यथा {
            window->flags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        }
        वापस false;
    }
    वापस true;
}

bool SDL_GetWindowRelativeMouseMode(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (window->flags & SDL_WINDOW_MOUSE_RELATIVE_MODE) {
        वापस true;
    } अन्यथा {
        वापस false;
    }
}

bool SDL_FlashWindow(SDL_Window *window, SDL_FlashOperation operation)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (_this->FlashWindow) {
        वापस _this->FlashWindow(_this, window, operation);
    }

    वापस SDL_Unsupported();
}

bool SDL_SetWindowProgressState(SDL_Window *window, SDL_ProgressState state)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    CHECK_PARAM(state < SDL_PROGRESS_STATE_NONE || state > SDL_PROGRESS_STATE_ERROR) {
        वापस SDL_InvalidParamError("state");
    }

    window->progress_state = state;

    अगर (_this->ApplyWindowProgress) {
        अगर (!_this->ApplyWindowProgress(_this, window)) {
            वापस false;
        }
    }

    वापस true;
}

SDL_ProgressState SDL_GetWindowProgressState(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, SDL_PROGRESS_STATE_INVALID);
    CHECK_WINDOW_NOT_POPUP(window, SDL_PROGRESS_STATE_INVALID);

    वापस window->progress_state;
}

bool SDL_Set_Window_Progress_मूल्य(SDL_Window *window, भग्न मूल्य)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    मूल्य = SDL_clamp(मूल्य, 0.0f, 1.f);

    window->progress_मूल्य = मूल्य;

    अगर (_this->ApplyWindowProgress) {
        अगर (!_this->ApplyWindowProgress(_this, window)) {
            वापस false;
        }
    }

    वापस true;
}

भग्न SDL_Get_Window_Progress_मूल्य(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, -1.0f);
    CHECK_WINDOW_NOT_POPUP(window, -1.0f);

    वापस window->progress_मूल्य;
}

व्योम SDL_OnWindowShown(SDL_Window *window)
{
    // Set window state if we have pending window flags cached
    ApplyWindowFlags(window, window->pending_flags);
    window->pending_flags = 0;
}

व्योम SDL_OnWindowHidden(SDL_Window *window)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    window->pending_flags |= (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
}

व्योम SDL_OnWindowDisplayChanged(SDL_Window *window)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    अगर (window->update_fullscreen_on_display_changed && (window->flags & SDL_WINDOW_FULLSCREEN)) {
        स्थिर bool auto_mode_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE, true);

        अगर (auto_mode_switch && (window->requested_fullscreen_mode.w != 0 || window->requested_fullscreen_mode.h != 0)) {
            SDL_DisplayID displayID = SDL_GetDisplayForWindowPosition(window);
            bool include_ऊपरी_density_modes = false;

            अगर (window->requested_fullscreen_mode.pixel_density > 1.0f) {
                include_ऊपरी_density_modes = true;
            }
            स्थिर bool found_match = SDL_GetClosestFullscreenDisplayMode(displayID, window->requested_fullscreen_mode.w, window->requested_fullscreen_mode.h,
                                                                         window->requested_fullscreen_mode.refresh_rate, include_ऊपरी_density_modes, &window->current_fullscreen_mode);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            अगर (!found_match ||
                window->requested_fullscreen_mode.w != window->current_fullscreen_mode.w ||
                window->requested_fullscreen_mode.h != window->current_fullscreen_mode.h) {
                SDL_zero(window->current_fullscreen_mode);
            }
        } अन्यथा {
            SDL_zero(window->current_fullscreen_mode);
        }

        अगर (SDL_WINDOW_FULLSCREEN_VISIBLE(window)) {
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_Window_Pixel_आकार_Changed(window);
}

व्योम SDL_OnWindowMoved(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
}

व्योम SDL_OnWindowResized(SDL_Window *window)
{
    SDL_CheckWindowDisplayChanged(window);
    SDL_Check_Window_Pixel_आकार_Changed(window);
    SDL_CheckWindowSafeAreaChanged(window);

    अगर ((window->flags & SDL_WINDOW_TRANSPARENT) && _this->UpdateWindowShape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(window->props, SDL_PROP_WINDOW_SHAPE_POINTER, शून्य);
        अगर (surface) {
            _this->UpdateWindowShape(_this, window, surface);
        }
    }
}

व्योम SDL_Check_Window_Pixel_आकार_Changed(SDL_Window *window)
{
    पूर्णांक pixel_w = 0, pixel_h = 0;

    SDL_Get_Window_आकार_In_Pixels(window, &pixel_w, &pixel_h);
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_आकार_CHANGED, pixel_w, pixel_h);

    SDL_CheckWindowDisplayScaleChanged(window);
}

व्योम SDL_On_Window_Pixel_आकार_Changed(SDL_Window *window)
{
    window->surface_valid = false;
}

व्योम SDL_OnWindowLiveResizeUpdate(SDL_Window *window)
{
    अगर (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } अन्यथा {
        // Send an expose event so the application can redraw
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

अटल व्योम SDL_CheckWindowSafeAreaChanged(SDL_Window *window)
{
    SDL_Rect rect;

    rect.x = window->safe_inset_बायाँ;
    rect.y = window->safe_inset_शीर्ष;
    rect.w = window->w - (window->safe_inset_दायाँ + window->safe_inset_बायाँ);
    rect.h = window->h - (window->safe_inset_शीर्ष + window->safe_inset_bottom);
    अगर (SDL_memcmp(&rect, &window->safe_rect, माप(rect)) != 0) {
        SDL_copyp(&window->safe_rect, &rect);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, 0, 0);
    }
}

व्योम SDL_SetWindowSafeAreaInsets(SDL_Window *window, पूर्णांक बायाँ, पूर्णांक दायाँ, पूर्णांक शीर्ष, पूर्णांक bottom)
{
    window->safe_inset_बायाँ = बायाँ;
    window->safe_inset_दायाँ = दायाँ;
    window->safe_inset_शीर्ष = शीर्ष;
    window->safe_inset_bottom = bottom;
    SDL_CheckWindowSafeAreaChanged(window);
}

bool SDL_GetWindowSafeArea(SDL_Window *window, SDL_Rect *rect)
{
    अगर (rect) {
        SDL_zerop(rect);
    }

    CHECK_WINDOW_MAGIC(window, false);

    अगर (rect) {
        अगर (SDL_RectEmpty(&window->safe_rect)) {
            rect->w = window->w;
            rect->h = window->h;
        } अन्यथा {
            SDL_copyp(rect, &window->safe_rect);
        }
    }
    वापस true;
}

व्योम SDL_OnWindowMinimized(SDL_Window *window)
{
    अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

व्योम SDL_OnWindowMaximized(SDL_Window *window)
{
}

व्योम SDL_OnWindowRestored(SDL_Window *window)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    अगर (window->flags & SDL_WINDOW_FULLSCREEN) {
        SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

व्योम SDL_OnWindowEnter(SDL_Window *window)
{
    अगर (_this->OnWindowEnter) {
        _this->OnWindowEnter(_this, window);
    }
    SDL_UpdateRelativeMouseMode();
}

व्योम SDL_OnWindowLeave(SDL_Window *window)
{
    SDL_UpdateRelativeMouseMode();
}

व्योम SDL_OnWindowFocusGained(SDL_Window *window)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    अगर (mouse && mouse->relative_mode) {
        SDL_SetMouseFocus(window);
    }

    SDL_UpdateWindowGrab(window);
}

अटल bool SDL_ShouldMinimizeOnFocusLoss(SDL_Window *window)
{
    स्थिर अक्षर *hint;

    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN) || window->is_destroying) {
        वापस false;
    }

#अगर defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    अगर (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        अगर (Cocoa_IsShowingModalDialog(window)) {
            वापस false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } अन्यथा अगर (Cocoa_IsWindowInFullscreenSpace(window)) {
            वापस false;
        }
    }
#पूर्ण_अगर

#अगर_घोषित SDL_PLATFORM_ANDROID
    {
        बाह्य bool Android_JNI_ShouldMinimizeOnFocusLoss(व्योम);
        अगर (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            वापस false;
        }
    }
#पूर्ण_अगर

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    अगर (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        अगर (window->fullscreen_exclusive && !SDL_ModeSwitchingEmulated(_this)) {
            वापस true;
        } अन्यथा {
            वापस false;
        }
    }
    वापस SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

व्योम SDL_OnWindowFocusLost(SDL_Window *window)
{
    SDL_UpdateWindowGrab(window);

    अगर (SDL_ShouldMinimizeOnFocusLoss(window)) {
        SDL_MinimizeWindow(window);
    }
}

SDL_Window *SDL_GetToplevelForKeyboardFocus(व्योम)
{
    SDL_Window *focus = SDL_GetKeyboardFocus();

    अगर (focus) {
        // Get the toplevel parent window.
        जबतक (focus->parent) {
            focus = focus->parent;
        }
    }

    वापस focus;
}

bool SDL_AddWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(window->renderers, (window->अंक_renderers + 1) * माप(*renderers));
    अगर (!renderers) {
        वापस false;
    }

    window->renderers = renderers;
    window->renderers[window->अंक_renderers++] = renderer;

    SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_RENDERER_POINTER, renderer);
    वापस true;
}

व्योम SDL_RemoveWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    क्रम (पूर्णांक i = 0; i < window->अंक_renderers; ++i) {
        अगर (window->renderers[i] == renderer) {
            अगर (i < (window->अंक_renderers - 1)) {
                SDL_memmove(&window->renderers[i], &window->renderers[i + 1], (window->अंक_renderers - i - 1) * माप(window->renderers[i]));
            }
            --window->अंक_renderers;
            अवरोध;
        }
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    अगर (SDL_GetPointerProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER, शून्य) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_WINDOW_RENDERER_POINTER);
    }
}

व्योम SDL_DestroyWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window,);

    window->is_destroying = true;

    // Destroy any child windows of this window
    जबतक (window->first_child) {
        SDL_DestroyWindow(window->first_child);
    }

    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DESTROYED, 0, 0);

    SDL_DestroyWindowSurface(window);

    SDL_Renderer *renderer = SDL_GetRenderer(window);
    अगर (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, true);
    अगर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        SDL_HideWindow(window);
    }

    SDL_DestroyProperties(window->text_निवेश_props);

    SDL_DestroyWindowTexture(_this, window);
    SDL_DestroyProperties(window->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    अगर (_this->SetWindowModal && (window->flags & SDL_WINDOW_MODAL)) {
        _this->SetWindowModal(_this, window, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    क्रम (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
        अगर (_this->displays[i]->fullscreen_window == window) {
            _this->displays[i]->fullscreen_window = शून्य;
        }
    }

    // Make sure this window no longer has focus
    अगर (SDL_GetKeyboardFocus() == window) {
        SDL_SetKeyboardFocus(शून्य);
    }
    अगर ((window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    अगर (SDL_GetMouseFocus() == window) {
        SDL_SetMouseFocus(शून्य);
    }

    // Make no context current if this is the current context window
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        अगर (_this->current_glwin == window) {
            SDL_GL_MakeCurrent(window, शून्य);
        }
    }

    अगर (_this->DestroyWindow) {
        _this->DestroyWindow(_this, window);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    अगर (window->flags & SDL_WINDOW_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    अगर (_this->grabbed_window == window) {
        _this->grabbed_window = शून्य; // ungrabbing input.
    }

    अगर (_this->current_glwin == window) {
        _this->current_glwin = शून्य;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_window, window, शून्य);

    // Now invalidate magic
    SDL_SetObjectValid(window, SDL_OBJECT_TYPE_WINDOW, false);

    // Free memory associated with the window
    SDL_free(window->title);
    SDL_DestroySurface(window->icon);

    // Unlink the window from its siblings.
    SDL_UpdateWindowHierarchy(window, शून्य);

    // Unlink the window from the global window list
    अगर (window->अग्र) {
        window->अग्र->पूर्व = window->पूर्व;
    }
    अगर (window->पूर्व) {
        window->पूर्व->अग्र = window->अग्र;
    } अन्यथा {
        _this->windows = window->अग्र;
    }

    SDL_free(window->renderers);
    SDL_free(window);

#अगर_घोषित SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#पूर्ण_अगर
}

bool SDL_ScreenSaverEnabled(व्योम)
{
    अगर (!_this) {
        वापस true;
    }
    वापस !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(व्योम)
{
    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }
    अगर (!_this->suspend_screensaver) {
        वापस true;
    }
    _this->suspend_screensaver = false;
    अगर (_this->SuspendScreenSaver) {
        वापस _this->SuspendScreenSaver(_this);
    }

    वापस SDL_Unsupported();
}

bool SDL_DisableScreenSaver(व्योम)
{
    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }
    अगर (_this->suspend_screensaver) {
        वापस true;
    }
    _this->suspend_screensaver = true;
    अगर (_this->SuspendScreenSaver) {
        वापस _this->SuspendScreenSaver(_this);
    }

    वापस SDL_Unsupported();
}

व्योम SDL_QuitVideo(व्योम)
{
    पूर्णांक i;

    अगर (!_this) {
        वापस;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#अगर 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#पूर्ण_अगर
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    जबतक (_this->windows) {
        SDL_DestroyWindow(_this->windows);
    }

    अगर (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    अगर (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    क्रम (i = _this->अंक_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->अंक_displays == 0);
    SDL_free(_this->displays);
    _this->displays = शून्य;

    SDL_Cancel_Clipboard_तथ्य(0);

    अगर (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = शून्य;
    }
    _this->मुक्त(_this);
    _this = शून्य;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_LoadLibrary(स्थिर अक्षर *path)
{
    bool परिणाम;

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }
    अगर (_this->gl_config.driver_loaded) {
        अगर (path && SDL_strcmp(path, _this->gl_config.driver_path) != 0) {
            वापस SDL_SetError("OpenGL library already loaded");
        }
        परिणाम = true;
    } अन्यथा {
        अगर (!_this->GL_LoadLibrary) {
            वापस SDL_DllNotSupported("OpenGL");
        }
        परिणाम = _this->GL_LoadLibrary(_this, path);
    }
    अगर (परिणाम) {
        ++_this->gl_config.driver_loaded;
    } अन्यथा {
        अगर (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    वापस परिणाम;
}

SDL_FunctionPointer SDL_GL_GetProcAddress(स्थिर अक्षर *proc)
{
    SDL_FunctionPointer func;

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    func = शून्य;
    अगर (_this->GL_GetProcAddress) {
        अगर (_this->gl_config.driver_loaded) {
            func = _this->GL_GetProcAddress(_this, proc);
        } अन्यथा {
            SDL_SetError("No GL driver has been loaded");
        }
    } अन्यथा {
        SDL_SetError("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    वापस func;
}

SDL_FunctionPointer SDL_EGL_GetProcAddress(स्थिर अक्षर *proc)
{
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    func = शून्य;

    अगर (_this->egl_तथ्य) {
        func = SDL_EGL_GetProcAddressInternal(_this, proc);
    } अन्यथा {
        SDL_SetError("No EGL library has been loaded");
    }

    वापस func;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    वापस शून्य;
#पूर्ण_अगर
}

व्योम SDL_GL_UnloadLibrary(व्योम)
{
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस;
    }
    अगर (_this->gl_config.driver_loaded > 0) {
        अगर (--_this->gl_config.driver_loaded > 0) {
            वापस;
        }
        अगर (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#अगर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
प्रकार GLenum (APIENTRY* PFNGLGETERRORPROC) (व्योम);
प्रकार व्योम (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
प्रकार स्थिर GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
प्रकार व्योम (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#अगर_अघोषित SDL_VIDEO_OPENGL
प्रकार स्थिर GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint सूचकांक);
#पूर्ण_अगर

अटल SDL_INLINE bool isAtLeastGL3(स्थिर अक्षर *verstr)
{
    वापस verstr && (SDL_atoi(verstr) >= 3);
}
#पूर्ण_अगर // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(स्थिर अक्षर *extension)
{
#अगर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    स्थिर अक्षर *extensions;
    स्थिर अक्षर *start;
    स्थिर अक्षर *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    अगर (where || *extension == '\0') {
        वापस false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    अगर (start && *start == '0') {
        वापस false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    अगर (!glGetStringFunc) {
        वापस false;
    }

    अगर (isAtLeastGL3((स्थिर अक्षर *)glGetStringFunc(GL_VERSION))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint अंक_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_GetProcAddress("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        अगर ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            वापस false;
        }

#अगर_अघोषित GL_अंक_EXTENSIONS
#घोषणा GL_अंक_EXTENSIONS 0x821D
#पूर्ण_अगर
        glGetIntegervFunc(GL_अंक_EXTENSIONS, &अंक_exts);
        क्रम (i = 0; i < अंक_exts; i++) {
            स्थिर अक्षर *thisext = (स्थिर अक्षर *)glGetStringiFunc(GL_EXTENSIONS, i);
            अगर (SDL_strcmp(thisext, extension) == 0) {
                वापस true;
            }
        }

        वापस false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (स्थिर अक्षर *)glGetStringFunc(GL_EXTENSIONS);
    अगर (!extensions) {
        वापस false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    क्रम (;;) {
        where = SDL_strstr(start, extension);
        अगर (!where) {
            अवरोध;
        }

        terminator = where + SDL_strlen(extension);
        अगर (where == extensions || *(where - 1) == ' ') {
            अगर (*terminator == ' ' || *terminator == '\0') {
                वापस true;
            }
        }

        start = terminator;
    }
    वापस false;
#अन्यथा
    वापस false;
#पूर्ण_अगर
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
व्योम SDL_GL_DeduceMaxSupportedESProfile(पूर्णांक *major, पूर्णांक *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#अगर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    अगर (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } अन्यथा अगर (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } अन्यथा अगर (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } अन्यथा {
        *major = 2;
        *minor = 0;
    }
#पूर्ण_अगर
}

व्योम SDL_EGL_SetAttributeCallbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   व्योम *userdata)
{
    अगर (!_this) {
        वापस;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

व्योम SDL_GL_ResetAttributes(व्योम)
{
    अगर (!_this) {
        वापस;
    }

    _this->egl_platformattrib_callback = शून्य;
    _this->egl_surfaceattrib_callback = शून्य;
    _this->egl_contextattrib_callback = शून्य;
    _this->egl_attrib_callback_userdata = शून्य;

    _this->gl_config.red_आकार = 8;
    _this->gl_config.green_आकार = 8;
    _this->gl_config.blue_आकार = 8;
    _this->gl_config.alpha_आकार = 8;
    _this->gl_config.बफर_आकार = 0;
    _this->gl_config.depth_आकार = 16;
    _this->gl_config.stencil_आकार = 0;
    _this->gl_config.double_बफर = 1;
    _this->gl_config.accum_red_आकार = 0;
    _this->gl_config.accum_green_आकार = 0;
    _this->gl_config.accum_blue_आकार = 0;
    _this->gl_config.accum_alpha_आकार = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#अगर_घोषित SDL_VIDEO_OPENGL
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 1;
    _this->gl_config.profile_mask = 0;
#या_अगर defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_version = 2;
    _this->gl_config.minor_version = 0;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#या_अगर defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_version = 1;
    _this->gl_config.minor_version = 1;
    _this->gl_config.profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#पूर्ण_अगर

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    अगर (_this->GL_SetDefaultProfileConfig) {
        _this->GL_SetDefaultProfileConfig(_this);
    }
}

bool SDL_GL_SetAttribute(SDL_GLAttr attr, पूर्णांक मूल्य)
{
#अगर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool परिणाम;

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }
    परिणाम = true;
    चयन (attr) {
    हाल SDL_GL_RED_आकार:
        _this->gl_config.red_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_GREEN_आकार:
        _this->gl_config.green_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_BLUE_आकार:
        _this->gl_config.blue_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_ALPHA_आकार:
        _this->gl_config.alpha_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_बफर = मूल्य;
        अवरोध;
    हाल SDL_GL_बफर_आकार:
        _this->gl_config.बफर_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_DEPTH_आकार:
        _this->gl_config.depth_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_STENCIL_आकार:
        _this->gl_config.stencil_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_ACCUM_RED_आकार:
        _this->gl_config.accum_red_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_ACCUM_GREEN_आकार:
        _this->gl_config.accum_green_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_ACCUM_BLUE_आकार:
        _this->gl_config.accum_blue_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_ACCUM_ALPHA_आकार:
        _this->gl_config.accum_alpha_आकार = मूल्य;
        अवरोध;
    हाल SDL_GL_STEREO:
        _this->gl_config.stereo = मूल्य;
        अवरोध;
    हाल SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = मूल्य;
        अवरोध;
    हाल SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = मूल्य;
        अवरोध;
    हाल SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = मूल्य;
        अवरोध;
    हाल SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = मूल्य;
        अवरोध;
    हाल SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = मूल्य;
        अवरोध;
    हाल SDL_GL_CONTEXT_MAJOR_VERSION:
        _this->gl_config.major_version = मूल्य;
        अवरोध;
    हाल SDL_GL_CONTEXT_MINOR_VERSION:
        _this->gl_config.minor_version = मूल्य;
        अवरोध;
    हाल SDL_GL_CONTEXT_FLAGS:
        अगर (मूल्य & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            परिणाम = SDL_SetError("Unknown OpenGL context flag %d", मूल्य);
            अवरोध;
        }
        _this->gl_config.flags = मूल्य;
        अवरोध;
    हाल SDL_GL_CONTEXT_PROFILE_MASK:
        अगर (मूल्य != 0 &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_CORE &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            मूल्य != SDL_GL_CONTEXT_PROFILE_ES) {
            परिणाम = SDL_SetError("Unknown OpenGL context profile %d", मूल्य);
            अवरोध;
        }
        _this->gl_config.profile_mask = मूल्य;
        अवरोध;
    हाल SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = मूल्य;
        अवरोध;
    हाल SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = मूल्य;
        अवरोध;
    हाल SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = मूल्य;
        अवरोध;
    हाल SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = मूल्य;
        अवरोध;
    हाल SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = मूल्य;
        अवरोध;
    हाल SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = मूल्य;
        अवरोध;
    शेष:
        परिणाम = SDL_SetError("Unknown OpenGL attribute");
        अवरोध;
    }
    वापस परिणाम;
#अन्यथा
    वापस SDL_Unsupported();
#पूर्ण_अगर // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, पूर्णांक *मूल्य)
{
#अगर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#अगर_घोषित SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_BACK_बायाँ;
    GLenum attachmentattrib = 0;
#पूर्ण_अगर

    CHECK_PARAM(!मूल्य) {
        वापस SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *मूल्य = 0;

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    चयन (attr) {
    हाल SDL_GL_RED_आकार:
#अगर_घोषित SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_आकार;
#पूर्ण_अगर
        attrib = GL_RED_BITS;
        अवरोध;
    हाल SDL_GL_BLUE_आकार:
#अगर_घोषित SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_आकार;
#पूर्ण_अगर
        attrib = GL_BLUE_BITS;
        अवरोध;
    हाल SDL_GL_GREEN_आकार:
#अगर_घोषित SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_आकार;
#पूर्ण_अगर
        attrib = GL_GREEN_BITS;
        अवरोध;
    हाल SDL_GL_ALPHA_आकार:
#अगर_घोषित SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_आकार;
#पूर्ण_अगर
        attrib = GL_ALPHA_BITS;
        अवरोध;
    हाल SDL_GL_DOUBLEBUFFER:
#अगर_घोषित SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        अवरोध;
#अन्यथा
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *मूल्य = _this->gl_config.double_बफर;
        वापस true;
#पूर्ण_अगर
    हाल SDL_GL_DEPTH_आकार:
#अगर_घोषित SDL_VIDEO_OPENGL
        attachment = GL_DEPTH;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_आकार;
#पूर्ण_अगर
        attrib = GL_DEPTH_BITS;
        अवरोध;
    हाल SDL_GL_STENCIL_आकार:
#अगर_घोषित SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_आकार;
#पूर्ण_अगर
        attrib = GL_STENCIL_BITS;
        अवरोध;
#अगर_घोषित SDL_VIDEO_OPENGL
    हाल SDL_GL_ACCUM_RED_आकार:
        attrib = GL_ACCUM_RED_BITS;
        अवरोध;
    हाल SDL_GL_ACCUM_GREEN_आकार:
        attrib = GL_ACCUM_GREEN_BITS;
        अवरोध;
    हाल SDL_GL_ACCUM_BLUE_आकार:
        attrib = GL_ACCUM_BLUE_BITS;
        अवरोध;
    हाल SDL_GL_ACCUM_ALPHA_आकार:
        attrib = GL_ACCUM_ALPHA_BITS;
        अवरोध;
    हाल SDL_GL_STEREO:
        attrib = GL_STEREO;
        अवरोध;
#अन्यथा
    हाल SDL_GL_ACCUM_RED_आकार:
    हाल SDL_GL_ACCUM_GREEN_आकार:
    हाल SDL_GL_ACCUM_BLUE_आकार:
    हाल SDL_GL_ACCUM_ALPHA_आकार:
    हाल SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *मूल्य = 0;
        वापस true;
#पूर्ण_अगर
    हाल SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        अवरोध;
    हाल SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        अवरोध;
    हाल SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        अवरोध;
    हाल SDL_GL_बफर_आकार:
    {
        पूर्णांक rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        अगर (!SDL_GL_GetAttribute(SDL_GL_RED_आकार, &rsize)) {
            वापस false;
        }
        अगर (!SDL_GL_GetAttribute(SDL_GL_GREEN_आकार, &gsize)) {
            वापस false;
        }
        अगर (!SDL_GL_GetAttribute(SDL_GL_BLUE_आकार, &bsize)) {
            वापस false;
        }
        अगर (!SDL_GL_GetAttribute(SDL_GL_ALPHA_आकार, &asize)) {
            वापस false;
        }

        *मूल्य = rsize + gsize + bsize + asize;
        वापस true;
    }
    हाल SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *मूल्य = (_this->gl_config.accelerated != 0);
        वापस true;
    }
    हाल SDL_GL_RETAINED_BACKING:
    {
        *मूल्य = _this->gl_config.retained_backing;
        वापस true;
    }
    हाल SDL_GL_CONTEXT_MAJOR_VERSION:
    {
        *मूल्य = _this->gl_config.major_version;
        वापस true;
    }
    हाल SDL_GL_CONTEXT_MINOR_VERSION:
    {
        *मूल्य = _this->gl_config.minor_version;
        वापस true;
    }
    हाल SDL_GL_CONTEXT_FLAGS:
    {
        *मूल्य = _this->gl_config.flags;
        वापस true;
    }
    हाल SDL_GL_CONTEXT_PROFILE_MASK:
    {
        *मूल्य = _this->gl_config.profile_mask;
        वापस true;
    }
    हाल SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *मूल्य = _this->gl_config.share_with_current_context;
        वापस true;
    }
    हाल SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *मूल्य = _this->gl_config.framebuffer_srgb_capable;
        वापस true;
    }
    हाल SDL_GL_CONTEXT_NO_ERROR:
    {
        *मूल्य = _this->gl_config.no_error;
        वापस true;
    }
    हाल SDL_GL_EGL_PLATFORM:
    {
        *मूल्य = _this->gl_config.egl_platform;
        वापस true;
    }
    हाल SDL_GL_FLOATBUFFERS:
    {
        अगर (_this->gl_config.HAS_GL_ARB_color_बफर_float) {
            attrib = GL_RGBA_FLOAT_MODE_ARB;
            अवरोध;
        } अन्यथा {
            वापस 0;
        }
    }
    शेष:
        वापस SDL_SetError("Unknown OpenGL attribute");
    }

#अगर_घोषित SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
    अगर (!glGetStringFunc) {
        वापस false;
    }

    अगर (attachmentattrib && isAtLeastGL3((स्थिर अक्षर *)glGetStringFunc(GL_VERSION))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_GetProcAddress("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
        अगर (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv");
        अगर (glGetFramebufferAttachmentParameterivFunc) {
            अगर (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            अगर (attachment == GL_DEPTH || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            अगर (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)मूल्य);
            } अन्यथा {
                *मूल्य = 0;
            }
            अगर (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } अन्यथा {
            वापस false;
        }
    } अन्यथा
#पूर्ण_अगर
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_GetProcAddress("glGetIntegerv");
        अगर (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)मूल्य);
        } अन्यथा {
            वापस false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_GetProcAddress("glGetError");
    अगर (!glGetErrorFunc) {
        वापस false;
    }

    error = glGetErrorFunc();
    अगर (error != GL_NO_ERROR) {
        अगर (error == GL_INVALID_ENUM) {
            वापस SDL_SetError("OpenGL error: GL_INVALID_ENUM");
        } अन्यथा अगर (error == GL_INVALID_मूल्य) {
            वापस SDL_SetError("OpenGL error: GL_INVALID_VALUE");
        }
        वापस SDL_SetError("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    अगर (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *मूल्य = (*मूल्य == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    वापस true;
#अन्यथा
    वापस SDL_Unsupported();
#पूर्ण_अगर // SDL_VIDEO_OPENGL
}

#घोषणा NOT_AN_OPENGL_WINDOW "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_Window *window)
{
    SDL_GLContext ctx = शून्य;
    CHECK_WINDOW_MAGIC(window, शून्य);

    अगर (!(window->flags & SDL_WINDOW_OPENGL)) {
        SDL_SetError(NOT_AN_OPENGL_WINDOW);
        वापस शून्य;
    }

#अगर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    पूर्णांक srgb_requested = -1;
    स्थिर अक्षर *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    अगर (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#पूर्ण_अगर

    ctx = _this->GL_CreateContext(_this, window);

    // Creating a context is assumed to make it current in the SDL driver.
    अगर (ctx) {
        _this->current_glwin = window;
        _this->current_glctx = ctx;
        SDL_SetTLS(&_this->current_glwin_tls, window, शून्य);
        SDL_SetTLS(&_this->current_glctx_tls, ctx, शून्य);
    }

#अगर defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    अगर (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_GetProcAddress(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_GetProcAddress("glGetString");
        अगर (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            अगर (_this->gl_config.profile_mask & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } अन्यथा {
                supported = isAtLeastGL3((स्थिर अक्षर *)glGetStringFunc(GL_VERSION)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            अगर (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#पूर्ण_अगर

    वापस ctx;
}

bool SDL_GL_MakeCurrent(SDL_Window *window, SDL_GLContext context)
{
    bool परिणाम;

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }

    अगर (window == SDL_GL_GetCurrentWindow() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        वापस true;
    }

    अगर (!context) {
        window = शून्य;
    } अन्यथा अगर (window) {
        CHECK_WINDOW_MAGIC(window, false);

        अगर (!(window->flags & SDL_WINDOW_OPENGL)) {
            वापस SDL_SetError(NOT_AN_OPENGL_WINDOW);
        }
    } अन्यथा अगर (!_this->gl_allow_no_surface) {
        वापस SDL_SetError("Use of OpenGL without a window is not supported on this platform");
    }

    परिणाम = _this->GL_MakeCurrent(_this, window, context);
    अगर (परिणाम) {
        _this->current_glwin = window;
        _this->current_glctx = context;
        SDL_SetTLS(&_this->current_glwin_tls, window, शून्य);
        SDL_SetTLS(&_this->current_glctx_tls, context, शून्य);
    }
    वापस परिणाम;
}

SDL_Window *SDL_GL_GetCurrentWindow(व्योम)
{
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    वापस (SDL_Window *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(व्योम)
{
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    वापस (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(व्योम)
{
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस EGL_NO_DISPLAY;
    }
    अगर (!_this->egl_तथ्य) {
        SDL_SetError("There is no current EGL display");
        वापस EGL_NO_DISPLAY;
    }
    वापस _this->egl_तथ्य->egl_display;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    वापस शून्य;
#पूर्ण_अगर
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(व्योम)
{
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    अगर (!_this->egl_तथ्य) {
        SDL_SetError("There is no current EGL display");
        वापस शून्य;
    }
    वापस _this->egl_तथ्य->egl_config;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    वापस शून्य;
#पूर्ण_अगर
}

SDL_EGLConfig SDL_EGL_GetWindowSurface(SDL_Window *window)
{
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    अगर (!_this->egl_तथ्य) {
        SDL_SetError("There is no current EGL display");
        वापस शून्य;
    }
    अगर (_this->GL_GetEGLSurface) {
        वापस _this->GL_GetEGLSurface(_this, window);
    }
    वापस शून्य;
#अन्यथा
    SDL_SetError("SDL was not built with EGL support");
    वापस शून्य;
#पूर्ण_अगर
}

bool SDL_GL_SetSwapInterval(पूर्णांक interval)
{
    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    } अन्यथा अगर (SDL_GL_GetCurrentContext() == शून्य) {
        वापस SDL_SetError("No OpenGL context has been made current");
    } अन्यथा अगर (_this->GL_SetSwapInterval) {
        वापस _this->GL_SetSwapInterval(_this, interval);
    } अन्यथा {
        वापस SDL_SetError("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(पूर्णांक *interval)
{
    CHECK_PARAM(!interval) {
       वापस SDL_InvalidParamError("interval");
    }

    *interval = 0;

    अगर (!_this) {
        वापस SDL_SetError("no video driver");
    } अन्यथा अगर (SDL_GL_GetCurrentContext() == शून्य) {
        वापस SDL_SetError("no current context");
    } अन्यथा अगर (_this->GL_GetSwapInterval) {
        वापस _this->GL_GetSwapInterval(_this, interval);
    } अन्यथा {
        वापस SDL_SetError("not implemented");
    }
}

bool SDL_GL_SwapWindow(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!(window->flags & SDL_WINDOW_OPENGL)) {
        वापस SDL_SetError(NOT_AN_OPENGL_WINDOW);
    }

    अगर (SDL_GL_GetCurrentWindow() != window) {
        वापस SDL_SetError("The specified window has not been made current");
    }

    वापस _this->GL_SwapWindow(_this, window);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        वापस SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        वापस SDL_InvalidParamError("context");
    }

    अगर (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(शून्य, शून्य);
    }

    वापस _this->GL_DestroyContext(_this, context);
}

#अगर 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
अटल व्योम Create_Mask_From_Color_कुंजी_Or_Alpha(SDL_Surface *icon, Uint8 *mask, पूर्णांक flags)
{
    पूर्णांक x, y;
    Uint32 colorkey;
#घोषणा SET_MASKBIT(icon, x, y, mask) \
    mask[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    चयन (SDL_BYTESPERPIXEL(icon->format)) {
    हाल 1:
        {
            Uint8 *pixels;
            क्रम (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                क्रम (x = 0; x < icon->w; ++x) {
                    अगर (*pixels++ == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                }
            }
        }
        अवरोध;

    हाल 2:
        {
            Uint16 *pixels;
            क्रम (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                क्रम (x = 0; x < icon->w; ++x) {
                    अगर ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अन्यथा अगर ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        अवरोध;

    हाल 4:
        {
            Uint32 *pixels;
            क्रम (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                क्रम (x = 0; x < icon->w; ++x) {
                    अगर ((flags & 1) && *pixels == colorkey) {
                        SET_MASKBIT(icon, x, y, mask);
                    } अन्यथा अगर ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        SET_MASKBIT(icon, x, y, mask);
                    }
                    pixels++;
                }
            }
        }
        अवरोध;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
व्योम SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
    अगर (icon && _this->SetIcon) {
        // Generate a mask if necessary, and create the icon!
        अगर (mask == शून्य) {
            पूर्णांक mask_len = icon->h * (icon->w + 7) / 8;
            पूर्णांक flags = 0;
            mask = (Uint8 *) SDL_malloc(mask_len);
            अगर (mask == शून्य) {
                वापस;
            }
            SDL_memset(mask, ~0, mask_len);
            अगर (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            अगर (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            अगर (flags) {
                Create_Mask_From_Color_कुंजी_Or_Alpha(icon, mask, flags);
            }
            _this->SetIcon(_this, icon, mask);
            SDL_free(mask);
        } अन्यथा {
            _this->SetIcon(_this, icon, mask);
        }
    }
}
#पूर्ण_अगर

SDL_Text_निवेश_Type SDL_Get_Text_निवेश_Type(SDL_PropertiesID props)
{
    वापस (SDL_Text_निवेश_Type)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_TYPE_संख्या, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_निवेश_Capitalization(SDL_PropertiesID props)
{
    अगर (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_संख्या)) {
        वापस (SDL_Capitalization)SDL_Get_संख्या_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_संख्या, SDL_CAPITALIZE_NONE);
    }

    चयन (SDL_Get_Text_निवेश_Type(props)) {
    हाल SDL_TEXTINPUT_TYPE_TEXT:
        वापस SDL_CAPITALIZE_SENTENCES;
    हाल SDL_TEXTINPUT_TYPE_TEXT_NAME:
        वापस SDL_CAPITALIZE_शब्दगण;
    शेष:
        वापस SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_निवेश_Autocorrect(SDL_PropertiesID props)
{
    वापस SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_निवेश_Multiline(SDL_PropertiesID props)
{
    अगर (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        वापस SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    अगर (SDL_GetHintBoolean(SDL_HINT_RETURN_कुंजी_HIDES_IME, false)) {
        वापस false;
    } अन्यथा {
        वापस true;
    }
}

अटल bool AutoShowingScreenKeyboard(व्योम)
{
    स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    अगर (!hint) {
        // This hint is currently only used by the X11 video driver
        अगर (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    अगर (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        वापस true;
    } अन्यथा {
        वापस false;
    }
}

bool SDL_Start_Text_निवेश(SDL_Window *window)
{
    वापस SDL_Start_Text_निवेश_With_Properties(window, 0);
}

bool SDL_Start_Text_निवेश_With_Properties(SDL_Window *window, SDL_PropertiesID props)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (window->text_निवेश_props) {
        SDL_DestroyProperties(window->text_निवेश_props);
        window->text_निवेश_props = 0;
    }

    अगर (props) {
        window->text_निवेश_props = SDL_CreateProperties();
        अगर (!window->text_निवेश_props) {
            वापस false;
        }
        अगर (!SDL_CopyProperties(props, window->text_निवेश_props)) {
            वापस false;
        }
    }

    अगर (_this->Set_Text_निवेश_Properties) {
        _this->Set_Text_निवेश_Properties(_this, window, props);
    }

    अगर (!window->text_निवेश_active) {
        // Start the text input system
        अगर (_this->Start_Text_निवेश) {
            अगर (!_this->Start_Text_निवेश(_this, window, props)) {
                वापस false;
            }
        }
        window->text_निवेश_active = true;
    }

    // Show the on-screen keyboard, if desired
    अगर (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(window)) {
        अगर (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, window, props);
        }
    }
    वापस true;
}

bool SDL_Text_निवेश_Active(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    वापस window->text_निवेश_active;
}

bool SDL_Stop_Text_निवेश(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (window->text_निवेश_active) {
        // Stop the text input system
        अगर (_this->Stop_Text_निवेश) {
            _this->Stop_Text_निवेश(_this, window);
        }
        window->text_निवेश_active = false;
    }

    // Hide the on-screen keyboard, if desired
    अगर (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(window)) {
        अगर (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, window);
        }
    }
    वापस true;
}

bool SDL_Set_Text_निवेश_Area(SDL_Window *window, स्थिर SDL_Rect *rect, पूर्णांक cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (rect) {
        SDL_copyp(&window->text_निवेश_rect, rect);
        window->text_निवेश_cursor = cursor;
    } अन्यथा {
        SDL_zero(window->text_निवेश_rect);
        window->text_निवेश_cursor = 0;
    }

    अगर (_this && _this->Update_Text_निवेश_Area) {
        अगर (!_this->Update_Text_निवेश_Area(_this, window)) {
            वापस false;
        }
    }
    वापस true;
}

bool SDL_Get_Text_निवेश_Area(SDL_Window *window, SDL_Rect *rect, पूर्णांक *cursor)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (rect) {
        SDL_copyp(rect, &window->text_निवेश_rect);
    }
    अगर (cursor) {
        *cursor = window->text_निवेश_cursor;
    }
    वापस true;
}

bool SDL_ClearComposition(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (_this->ClearComposition) {
        वापस _this->ClearComposition(_this, window);
    }
    वापस true;
}

bool SDL_HasScreenKeyboardSupport(व्योम)
{
    अगर (_this && _this->HasScreenKeyboardSupport) {
        वापस _this->HasScreenKeyboardSupport(_this);
    }
    वापस false;
}

bool SDL_ScreenKeyboardShown(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, false);

    वापस _this->screen_keyboard_shown;
}

व्योम SDL_SendScreenKeyboardShown(व्योम)
{
    अगर (!_this || _this->screen_keyboard_shown) {
        वापस;
    }

    _this->screen_keyboard_shown = true;

    अगर (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_धकेलो_Event(&event);
    }
}

व्योम SDL_SendScreenKeyboardHidden(व्योम)
{
    अगर (!_this || !_this->screen_keyboard_shown) {
        वापस;
    }

    _this->screen_keyboard_shown = false;

    अगर (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_धकेलो_Event(&event);
    }
}

पूर्णांक SDL_Get_Message_Box_गिनती(व्योम)
{
    वापस SDL_GetAtomicInt(&SDL_messagebox_गिनती);
}

bool SDL_ShowMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
    पूर्णांक dummybutton;
    bool परिणाम = false;
    bool show_cursor_पूर्व;
    SDL_Window *current_window;
    SDL_Message_Box_तथ्य mbdata;

    CHECK_PARAM(!messageboxdata) {
        वापस SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        वापस SDL_SetError("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    अक्षर *titlecpy = शून्य;
    अक्षर *msgcpy = शून्य;
    अगर (messageboxdata->title) {
        स्थिर माप_प्रकार slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(अक्षर, slen, &titleisstack);
        अगर (!titlecpy) {
            वापस false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    अगर (messageboxdata->message) {
        स्थिर माप_प्रकार slen = SDL_strlen(messageboxdata->message) + 1;
        msgcpy = SDL_small_alloc(अक्षर, slen, &msgisstack);
        अगर (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            वापस false;
        }
        SDL_memcpy(msgcpy, messageboxdata->message, slen);
    }

    (व्योम)SDL_AtomicIncRef(&SDL_messagebox_गिनती);

    current_window = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_SetRelativeMouseMode(false);
    show_cursor_पूर्व = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    अगर (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, माप(*messageboxdata));
    mbdata.title = titlecpy;
    अगर (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.message = msgcpy;
    अगर (!mbdata.message) {
        mbdata.message = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    अगर (_this && _this->ShowMessageBox) {
        परिणाम = _this->ShowMessageBox(_this, messageboxdata, buttonID);
    } अन्यथा {
        // It's completely fine to call this function before video is initialized
        स्थिर अक्षर *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        अगर (driver_name && *driver_name != 0) {
            स्थिर अक्षर *driver_attempt = driver_name;
            जबतक (driver_attempt && (*driver_attempt != 0) && !परिणाम) {
                स्थिर अक्षर *driver_attempt_end = SDL_strchr(driver_attempt, ',');
                माप_प्रकार driver_attempt_len = (driver_attempt_end) ? (driver_attempt_end - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                क्रम (पूर्णांक i = 0; bootstrap[i]; ++i) {
                    अगर (bootstrap[i]->ShowMessageBox && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        अगर (bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                            परिणाम = true;
                        }
                        अवरोध;
                    }
                }

                driver_attempt = (driver_attempt_end) ? (driver_attempt_end + 1) : शून्य;
            }
        } अन्यथा {
            क्रम (पूर्णांक i = 0; bootstrap[i]; ++i) {
                अगर (bootstrap[i]->ShowMessageBox && bootstrap[i]->ShowMessageBox(messageboxdata, buttonID)) {
                    परिणाम = true;
                    अवरोध;
                }
            }
        }
    }

    अगर (!परिणाम) {
        स्थिर अक्षर *error = SDL_GetError();

        अगर (!*error) {
            SDL_SetError("No message system available");
        }
    } अन्यथा {
        SDL_ClearError();
    }

    (व्योम)SDL_AtomicDecRef(&SDL_messagebox_गिनती);

    अगर (current_window) {
        SDL_RaiseWindow(current_window);
    }

    अगर (!show_cursor_पूर्व) {
        SDL_HideCursor();
    }
    SDL_UpdateRelativeMouseMode();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    वापस परिणाम;
}

bool SDL_ShowSimpleMessageBox(SDL_MessageBoxFlags flags, स्थिर अक्षर *title, स्थिर अक्षर *message, SDL_Window *window)
{
#अगर defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_दायाँ;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_दायाँ = gsp_Has_Gpu_दायाँ();
    अगर (!has_Gpu_दायाँ)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, message);
    errorDisp(&errCnf);

    अगर (!has_Gpu_दायाँ)
        gfxExit();

    वापस true;
#अन्यथा
    SDL_Message_Box_तथ्य तथ्य;
    SDL_Message_Box_Button_तथ्य button;

    SDL_zero(तथ्य);
    तथ्य.flags = flags;
    तथ्य.title = title;
    तथ्य.message = message;
    तथ्य.numbuttons = 1;
    तथ्य.buttons = &button;
    तथ्य.window = window;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.text = "OK";

    वापस SDL_ShowMessageBox(&तथ्य, शून्य);
#पूर्ण_अगर
}

bool SDL_ShouldAllowTopmost(व्योम)
{
    वापस SDL_GetHintBoolean(SDL_HINT_WINDOW_ALLOW_TOPMOST, true);
}

bool SDL_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    CHECK_WINDOW_MAGIC(window, false);
    CHECK_WINDOW_NOT_POPUP(window, false);

    अगर (_this->ShowWindowSystemMenu) {
        _this->ShowWindowSystemMenu(window, x, y);
        वापस true;
    }

    वापस SDL_Unsupported();
}

bool SDL_SetWindowHitTest(SDL_Window *window, SDL_HitTest callback, व्योम *callback_तथ्य)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!_this->SetWindowHitTest) {
        वापस SDL_Unsupported();
    }

    window->hit_test = callback;
    window->hit_test_तथ्य = callback_तथ्य;

    वापस _this->SetWindowHitTest(window, callback != शून्य);
}

bool SDL_SetWindowShape(SDL_Window *window, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_WINDOW_MAGIC(window, false);

    अगर (!(window->flags & SDL_WINDOW_TRANSPARENT)) {
        वापस SDL_SetError("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_GetWindowProperties(window);
    अगर (!props) {
        वापस false;
    }

    अगर (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        अगर (!surface) {
            वापस false;
        }
    } अन्यथा {
        surface = शून्य;
    }

    अगर (!SDL_SetSurfaceProperty(props, SDL_PROP_WINDOW_SHAPE_POINTER, surface)) {
        वापस false;
    }

    अगर (_this->UpdateWindowShape) {
        अगर (!_this->UpdateWindowShape(_this, window, surface)) {
            वापस false;
        }
    }
    वापस true;
}

/*
 * Functions used by iOS application delegates
 */
व्योम SDL_OnApplicationWillTerminate(व्योम)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

व्योम SDL_OnApplicationDidReceiveMemoryWarning(व्योम)
{
    SDL_SendAppEvent(SDL_EVENT_निचला_MEMORY);
}

व्योम SDL_OnApplicationWillEnterBackground(व्योम)
{
    अगर (_this) {
        SDL_Window *window;
        क्रम (window = _this->windows; window; window = window->अग्र) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
        }
        SDL_SetKeyboardFocus(शून्य);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

व्योम SDL_OnApplicationDidEnterBackground(व्योम)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

व्योम SDL_OnApplicationWillEnterForeground(व्योम)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

व्योम SDL_OnApplicationDidEnterForeground(व्योम)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    अगर (_this) {
        SDL_Window *window;
        क्रम (window = _this->windows; window; window = window->अग्र) {
            SDL_SetKeyboardFocus(window);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
    }
}

#घोषणा NOT_A_VULKAN_WINDOW "The specified window isn't a Vulkan window"

bool SDL_Vulkan_LoadLibrary(स्थिर अक्षर *path)
{
    bool परिणाम;

    अगर (!_this) {
        वापस SDL_UninitializedVideo();
    }
    अगर (_this->vulkan_config.loader_loaded) {
        अगर (path && SDL_strcmp(path, _this->vulkan_config.loader_path) != 0) {
            वापस SDL_SetError("Vulkan loader library already loaded");
        }
        परिणाम = true;
    } अन्यथा {
        अगर (!_this->Vulkan_LoadLibrary) {
            वापस SDL_DllNotSupported("Vulkan");
        }
        परिणाम = _this->Vulkan_LoadLibrary(_this, path);
    }
    अगर (परिणाम) {
        _this->vulkan_config.loader_loaded++;
    }
    वापस परिणाम;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(व्योम)
{
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस शून्य;
    }
    अगर (!_this->vulkan_config.loader_loaded) {
        SDL_SetError("No Vulkan loader has been loaded");
        वापस शून्य;
    }
    वापस (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

व्योम SDL_Vulkan_UnloadLibrary(व्योम)
{
    अगर (!_this) {
        SDL_UninitializedVideo();
        वापस;
    }
    अगर (_this->vulkan_config.loader_loaded > 0) {
        अगर (--_this->vulkan_config.loader_loaded > 0) {
            वापस;
        }
        अगर (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

अक्षर स्थिर * स्थिर *SDL_Vulkan_GetInstanceExtensions(Uint32 *गिनती)
{
    Uint32 tmpcount = 0;
    अगर (!गिनती) {
        गिनती = &tmpcount;
    }

    अगर (!_this->Vulkan_GetInstanceExtensions) {
        *गिनती = 0;
        SDL_Unsupported();
        वापस शून्य;
    }

    वापस _this->Vulkan_GetInstanceExtensions(_this, गिनती);
}

bool SDL_Vulkan_CreateSurface(SDL_Window *window,
                                  VkInstance instance,
                                  स्थिर काष्ठा VkAllocationCallbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_WINDOW_MAGIC(window, false);

    अगर (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        वापस false;
    }

    CHECK_PARAM(!instance) {
        वापस SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        वापस SDL_InvalidParamError("surface");
    }

    अगर (!(window->flags & SDL_WINDOW_VULKAN)) {
        // No problem, we can convert to Vulkan
        अगर (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        अगर (window->flags & SDL_WINDOW_METAL) {
            window->flags &= ~SDL_WINDOW_METAL;
            // Nothing more to do for Metal.
        }
        अगर (SDL_Vulkan_LoadLibrary(शून्य)) {
            window->flags |= SDL_WINDOW_VULKAN;
        } अन्यथा {
            वापस SDL_SetError("failed to load Vulkan library");
        }
    }

    वापस _this->Vulkan_CreateSurface(_this, window, instance, allocator, surface);
}

व्योम SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               स्थिर काष्ठा VkAllocationCallbacks *allocator)
{
    अगर (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_सूचकांक)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        वापस false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        वापस false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        वापस false;
    }

    अगर (_this->Vulkan_GetPresentationSupport) {
        वापस _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queue_Family_सूचकांक);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    वापस true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_Window *window)
{
    CHECK_WINDOW_MAGIC(window, शून्य);

    अगर (!_this->Metal_CreateView) {
        SDL_Unsupported();
        वापस शून्य;
    }

    अगर (!(window->flags & SDL_WINDOW_METAL)) {
        // No problem, we can convert to Metal
        अगर (window->flags & SDL_WINDOW_OPENGL) {
            window->flags &= ~SDL_WINDOW_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        अगर (window->flags & SDL_WINDOW_VULKAN) {
            window->flags &= ~SDL_WINDOW_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        window->flags |= SDL_WINDOW_METAL;
    }

    वापस _this->Metal_CreateView(_this, window);
}

व्योम SDL_Metal_DestroyView(SDL_MetalView view)
{
    अगर (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

व्योम *SDL_Metal_GetLayer(SDL_MetalView view)
{
    अगर (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            वापस शून्य;
        }
        वापस _this->Metal_GetLayer(_this, view);
    } अन्यथा {
        SDL_SetError("Metal is not supported.");
        वापस शून्य;
    }
}

#अगर defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
स्थिर अक्षर *SDL_GetCSSCursorName(SDL_SystemCursor id, स्थिर अक्षर **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    चयन (id) {
    हाल SDL_SYSTEM_CURSOR_DEFAULT:
        वापस "default";

    हाल SDL_SYSTEM_CURSOR_TEXT:
        वापस "text";

    हाल SDL_SYSTEM_CURSOR_WAIT:
        वापस "wait";

    हाल SDL_SYSTEM_CURSOR_CROSSHAIR:
        वापस "crosshair";

    हाल SDL_SYSTEM_CURSOR_PROGRESS:
        वापस "progress";

    हाल SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        अगर (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        वापस "nwse-resize";

    हाल SDL_SYSTEM_CURSOR_NESW_RESIZE:
        अगर (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        वापस "nesw-resize";

    हाल SDL_SYSTEM_CURSOR_EW_RESIZE:
        अगर (fallback_name) {
            *fallback_name = "col-resize";
        }
        वापस "ew-resize";

    हाल SDL_SYSTEM_CURSOR_NS_RESIZE:
        अगर (fallback_name) {
            *fallback_name = "row-resize";
        }
        वापस "ns-resize";

    हाल SDL_SYSTEM_CURSOR_MOVE:
        अगर (fallback_name) {
            *fallback_name = "all-scroll";
        }
        वापस "move";

    हाल SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        वापस "not-allowed";

    हाल SDL_SYSTEM_CURSOR_POINTER:
        वापस "pointer";

    हाल SDL_SYSTEM_CURSOR_NW_RESIZE:
        वापस "nw-resize";

    हाल SDL_SYSTEM_CURSOR_N_RESIZE:
        वापस "n-resize";

    हाल SDL_SYSTEM_CURSOR_NE_RESIZE:
        वापस "ne-resize";

    हाल SDL_SYSTEM_CURSOR_E_RESIZE:
        वापस "e-resize";

    हाल SDL_SYSTEM_CURSOR_SE_RESIZE:
        वापस "se-resize";

    हाल SDL_SYSTEM_CURSOR_S_RESIZE:
        वापस "s-resize";

    हाल SDL_SYSTEM_CURSOR_SW_RESIZE:
        वापस "sw-resize";

    हाल SDL_SYSTEM_CURSOR_W_RESIZE:
        वापस "w-resize";

    हाल SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        वापस "context-menu";

    हाल SDL_SYSTEM_CURSOR_HELP:
        वापस "help";

    हाल SDL_SYSTEM_CURSOR_CELL:
        वापस "cell";

    हाल SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        वापस "vertical-text";

    हाल SDL_SYSTEM_CURSOR_ALIAS:
        वापस "alias";

    हाल SDL_SYSTEM_CURSOR_COPY:
        वापस "copy";

    हाल SDL_SYSTEM_CURSOR_NO_DROP:
        वापस "no-drop";

    हाल SDL_SYSTEM_CURSOR_GRAB:
        वापस "grab";

    हाल SDL_SYSTEM_CURSOR_GRABBING:
        वापस "grabbing";

    हाल SDL_SYSTEM_CURSOR_COL_RESIZE:
        वापस "col-resize";

    हाल SDL_SYSTEM_CURSOR_ROW_RESIZE:
        वापस "row-resize";

    हाल SDL_SYSTEM_CURSOR_ALL_SCROLL:
        अगर (fallback_name) {
            *fallback_name = "move";
        }
        वापस "all-scroll";

    हाल SDL_SYSTEM_CURSOR_ZOOM_IN:
        वापस "zoom-in";

    हाल SDL_SYSTEM_CURSOR_ZOOM_OUT:
        वापस "zoom-out";

    शेष:
        वापस "default";
    }
}
#पूर्ण_अगर

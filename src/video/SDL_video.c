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

#ضمن "SDL_internal.h"

// The high-level video driver subsystem

#ضمن "SDL_sysvideo.h"
#ضمن "SDL_clipboard_c.h"
#ضمن "SDL_egl_c.h"
#ضمن "SDL_surface_c.h"
#ضمن "SDL_pixels_c.h"
#ضمن "SDL_rect_c.h"
#ضمن "SDL_video_c.h"
#ضمن "../events/SDL_events_c.h"
#ضمن "../SDL_hints_c.h"
#ضمن "../SDL_properties_c.h"
#ضمن "../timer/SDL_timer_c.h"
#ضمن "../camera/SDL_camera_c.h"
#ضمن "../render/SDL_sysrender.h"
#ضمن "../main/SDL_main_callbacks.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
#ضمن <SDL3/SDL_opengl.h>
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL

#إذا defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles.h>
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#إذا defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles2.h>
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#جيڪڏهن_وصف_نه_ٿيل GL_CONTEXT_RELEASE_BEHAVIOR
#وصف_ڪريو GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#جيڪڏهن_پورو

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#جيڪڏهن_وصف_نه_ٿيل GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#وصف_ڪريو GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#جيڪڏهن_پورو

// This is always the same number between the various EXT/ARB/GLES extensions.
#جيڪڏهن_وصف_نه_ٿيل GL_FRAMEBUFFER_SRGB
#وصف_ڪريو GL_FRAMEBUFFER_SRGB 0x8DB9
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_EMSCRIPTEN
#ضمن <emscripten.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_3DS
#ضمن <3ds.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل GL_RGBA_FLOAT_گهڻائي_ARB
#وصف_ڪريو GL_RGBA_FLOAT_گهڻائي_ARB 0x8820
#جيڪڏهن_پورو /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ساكن VideoBootStrap *bootstrap[] = {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_ذاتي
    &ذاتي_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#جيڪڏهن_پورو
    &X11_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#جيڪڏهن_وصف_ٿيل SDL_داخلا_LINUXEV
    &DUMMY_evdev_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#جيڪڏهن_پورو
    عدم
};

#وصف_ڪريو CHECK_دري_MAGIC(دري, نتيجو)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        أرجع نتيجو;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(دري, SDL_OBJECT_TYPE_دري)) {     \
        SDL_سيٽ_Error("Invalid window");                                 \
        أرجع نتيجو;                                                  \
    }

#وصف_ڪريو CHECK_DISPLAY_MAGIC(display, نتيجو)                            \
    CHECK_PARAM(!display) {                                             \
        أرجع نتيجو;                                                  \
    }                                                                   \

#وصف_ڪريو CHECK_دري_NOT_POPUP(دري, نتيجو)                          \
    CHECK_PARAM(SDL_دري_IS_POPUP(دري)) {                          \
        SDL_سيٽ_Error("Operation invalid on popup windows");             \
        أرجع نتيجو;                                                  \
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
خارجي bool Cocoa_Is_دري_اندريون_Fullscreen_Space(SDL_دري *دري);
خارجي bool Cocoa_Is_دري_اندريون_Fullscreen_Space_Transition(SDL_دري *دري);
خارجي bool Cocoa_سيٽ_دري_Fullscreen_Space(SDL_دري *دري, bool state, bool blocking);
خارجي bool Cocoa_IsShowingModalDialog(SDL_دري *دري);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_UIKIT
خارجي فراغ SDL_UpdateLifecycleObserver(فراغ);
#جيڪڏهن_پورو

ساكن فراغ SDL_Check_دري_Display_بدليو(SDL_دري *دري);
ساكن فراغ SDL_Check_دري_Display_Scale_بدليو(SDL_دري *دري);
ساكن فراغ SDL_Check_دري_محفوظ_Area_بدليو(SDL_دري *دري);

// Convenience functions for reading driver flags
ساكن bool SDL_گهڻائي_Switching_Emulated(SDL_VideoDevice *_this)
{
    إذا (_this->device_caps & VIDEO_DEVICE_CAPS_گهڻائي_SWITCHING_EMULATED) {
        أرجع true;
    }
    أرجع false;
}

ساكن bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ساكن bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ساكن bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ساكن bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ساكن bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    أرجع !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ساكن bool syncHint;

ساكن فراغ SDL_SyncHintWatcher(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    syncHint = SDL_GetStringBoolean(new_قدر, false);
}

ساكن فراغ SDL_SyncIfRequired(SDL_دري *دري)
{
    إذا (syncHint) {
        SDL_Sync_دري(دري);
    }
}

ساكن فراغ SDL_Update_دري_Hierarchy(SDL_دري *دري, SDL_دري *والد)
{
    // Unlink the window from the existing parent.
    إذا (دري->والد) {
        إذا (دري->ايندڙ_sibling) {
            دري->ايندڙ_sibling->prev_sibling = دري->prev_sibling;
        }
        إذا (دري->prev_sibling) {
            دري->prev_sibling->ايندڙ_sibling = دري->ايندڙ_sibling;
        } وإلا {
            دري->والد->پهريون_ٻار = دري->ايندڙ_sibling;
        }

        دري->والد = عدم;
    }

    إذا (والد) {
        دري->والد = والد;

        دري->ايندڙ_sibling = والد->پهريون_ٻار;
        إذا (والد->پهريون_ٻار) {
            والد->پهريون_ٻار->prev_sibling = دري;
        }
        والد->پهريون_ٻار = دري;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#وصف_ڪريو SDL_PROP_دري_TEXTUREDATA_اشارو "SDL.internal.window.texturedata"

تعريفنوع بنية
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    فراغ *pixels;
    صحيح pitch;
    صحيح بائيٽون_في_pixel;
} SDL_دري_Texture_معلومات;

ساكن Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#إذا (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !هدف_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    إذا (_this->GL_CreateContext) {
        أرجع SDL_دري_OPENGL;
    }
#جيڪڏهن_پورو
#إذا defined(SDL_VIDEO_METAL) && (هدف_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    إذا (_this->Metal_CreateView) {
        أرجع SDL_دري_METAL;
    }
#جيڪڏهن_پورو
#إذا defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    إذا (SDL_strcmp(_this->name, "openvr") == 0) {
        أرجع SDL_دري_OPENGL;
    }
#جيڪڏهن_پورو
    أرجع 0;
}

ساكن bool SDL_Create_دري_Texture(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    SDL_دري_Texture_معلومات *معلومات = (SDL_دري_Texture_معلومات *)SDL_Get_اشارو_Property(props, SDL_PROP_دري_TEXTUREDATA_اشارو, عدم);
    ثابت bool transparent = (دري->flags & SDL_دري_TRANSPARENT) ? true : false;
    صحيح i;
    صحيح w, h;
    ثابت SDL_PixelFormat *texture_formats;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    إذا (!معلومات) {
        SDL_Renderer *renderer = عدم;
        ثابت حرف *render_driver = عدم;

        // See if there's a render driver being requested
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        إذا (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        إذا (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        إذا (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = عدم;
        }

        حرف *render_driver_copy = عدم;
        إذا (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            إذا (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                حرف *prev = render_driver_copy;
                حرف *ptr = prev;
                طالما ((ptr = SDL_strchr(ptr, ',')) != عدم) {
                    *ptr = '\0';
                    ثابت bool is_sw = (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    إذا (is_sw) {
                        SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = prev;
                    } وإلا {
                        ptr++;
                        prev = ptr;
                    }
                }

                إذا (SDL_strcasecmp(prev, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(prev, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        إذا (render_driver) {
            renderer = SDL_CreateRenderer(دري, render_driver);
            SDL_free(render_driver_copy);
            إذا (!renderer) {
                // The error for this specific renderer has already been set
                أرجع false;
            }
        } وإلا {
            SDL_assert(render_driver_copy == عدم);
            ثابت صحيح ڪل = SDL_Get_انگ_Render_Drivers();
            لكل (i = 0; i < ڪل; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                إذا (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(دري, name);
                    إذا (renderer) {
                        اكسر; // this will work.
                    }
                }
            }
            إذا (!renderer) {
                أرجع SDL_سيٽ_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != عدم); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        معلومات = (SDL_دري_Texture_معلومات *)SDL_calloc(1, حجم(*معلومات));
        إذا (!معلومات) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }
        إذا (!SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_TEXTUREDATA_اشارو, معلومات)) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }

        معلومات->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_Get_اشارو_Property(SDL_GetRendererProperties(معلومات->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_اشارو, عدم);
    إذا (!texture_formats) {
        أرجع false;
    }

    // Free any old texture and pixel data
    إذا (معلومات->texture) {
        SDL_DestroyTexture(معلومات->texture);
        معلومات->texture = عدم;
    }
    SDL_free(معلومات->pixels);
    معلومات->pixels = عدم;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    لكل (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        إذا (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10_ٻٽو_انگ(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_اشاريي_وارو(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            اكسر;
        }
    }

    معلومات->texture = SDL_CreateTexture(معلومات->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    إذا (!معلومات->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        أرجع false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_سيٽ_Texture_Blend_گهڻائي(معلومات->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    معلومات->بائيٽون_في_pixel = SDL_BYTESPERPIXEL(*format);
    معلومات->pitch = (((w * معلومات->بائيٽون_في_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * معلومات->pitch;
        معلومات->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        إذا (!معلومات->pixels) {
            أرجع false;
        }
    }

    *pixels = معلومات->pixels;
    *pitch = معلومات->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_سيٽ_Render_Viewport(معلومات->renderer, عدم);

    أرجع true;
}

bool SDL_سيٽ_دري_Texture_VSync(SDL_VideoDevice *_this, SDL_دري *دري, صحيح vsync)
{
    SDL_دري_Texture_معلومات *معلومات;

    معلومات = (SDL_دري_Texture_معلومات *)SDL_Get_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_TEXTUREDATA_اشارو, عدم);
    إذا (!معلومات) {
        أرجع false;
    }
    إذا (!معلومات->renderer) {
        أرجع false;
    }
    أرجع SDL_سيٽ_Render_VSync(معلومات->renderer, vsync);
}

ساكن bool SDL_Get_دري_Texture_VSync(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *vsync)
{
    SDL_دري_Texture_معلومات *معلومات;

    معلومات = (SDL_دري_Texture_معلومات *)SDL_Get_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_TEXTUREDATA_اشارو, عدم);
    إذا (!معلومات) {
        أرجع false;
    }
    إذا (!معلومات->renderer) {
        أرجع false;
    }
    أرجع SDL_GetRenderVSync(معلومات->renderer, vsync);
}

ساكن bool SDL_Update_دري_Texture(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_دري_Texture_معلومات *معلومات;
    SDL_Rect rect;
    فراغ *src;
    صحيح w, h;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    معلومات = (SDL_دري_Texture_معلومات *)SDL_Get_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_TEXTUREDATA_اشارو, عدم);
    إذا (!معلومات || !معلومات->texture) {
        أرجع SDL_سيٽ_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    إذا (SDL_Get_وسعت_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (فراغ *)((Uint8 *)معلومات->pixels +
                       rect.y * معلومات->pitch +
                       rect.x * معلومات->بائيٽون_في_pixel);
        إذا (!SDL_UpdateTexture(معلومات->texture, &rect, src, معلومات->pitch)) {
            أرجع false;
        }

        إذا (!SDL_RenderTexture(معلومات->renderer, معلومات->texture, عدم, عدم)) {
            أرجع false;
        }

        SDL_RenderPresent(معلومات->renderer);
    }
    أرجع true;
}

ساكن فراغ SDL_Destroy_دري_Texture(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    إذا (SDL_HasProperty(props, SDL_PROP_دري_TEXTUREDATA_اشارو)) {
        SDL_دري_Texture_معلومات *معلومات = SDL_Get_اشارو_Property(props, SDL_PROP_دري_TEXTUREDATA_اشارو, عدم);

        إذا (معلومات->texture) {
            SDL_DestroyTexture(معلومات->texture);
        }
        إذا (معلومات->renderer) {
            SDL_DestroyRenderer(معلومات->renderer);
        }
        SDL_free(معلومات->pixels);
        SDL_free(معلومات);

        SDL_ClearProperty(props, SDL_PROP_دري_TEXTUREDATA_اشارو);
    }
}

ساكن SDL_VideoDevice *_this = عدم;
ساكن SDL_AtomicInt SDL_messagebox_ڳڻپ;

ساكن صحيح SDLCALL cmpmodes(ثابت فراغ *A, ثابت فراغ *B)
{
    ثابت SDL_Display_گهڻائي *a = (ثابت SDL_Display_گهڻائي *)A;
    ثابت SDL_Display_گهڻائي *b = (ثابت SDL_Display_گهڻائي *)B;
    صحيح a_refresh_شرح = (صحيح)(a->refresh_شرح * 100);
    صحيح b_refresh_شرح = (صحيح)(b->refresh_شرح * 100);
    صحيح a_pixel_density = (صحيح)(a->pixel_density * 100);
    صحيح b_pixel_density = (صحيح)(b->pixel_density * 100);

    إذا (a->w != b->w) {
        أرجع b->w - a->w;
    } وإلا إذا (a->h != b->h) {
        أرجع b->h - a->h;
    } وإلا إذا (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        أرجع SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } وإلا إذا (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        أرجع SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } وإلا إذا (a_refresh_شرح != b_refresh_شرح) {
        أرجع b_refresh_شرح - a_refresh_شرح;
    } وإلا إذا (a_pixel_density != b_pixel_density) {
        أرجع a_pixel_density - b_pixel_density;
    }
    أرجع 0;
}

bool SDL_UninitializedVideo(فراغ)
{
    أرجع SDL_سيٽ_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ساكن ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحيح SDL_Get_انگ_Video_Drivers(فراغ)
{
    ساكن صحيح انگ_drivers = -1;

    إذا (انگ_drivers >= 0) {
        أرجع انگ_drivers;
    }

    انگ_drivers = 0;

    // Build a list of unique video drivers.
    لكل (صحيح i = 0; bootstrap[i] != عدم; ++i) {
        bool duplicate = false;
        لكل (صحيح j = 0; j < i; ++j) {
            إذا (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                اكسر;
            }
        }

        إذا (!duplicate) {
            deduped_bootstrap[انگ_drivers++] = bootstrap[i];
        }
    }

    أرجع انگ_drivers;
}

ثابت حرف *SDL_GetVideoDriver(صحيح اشاريو)
{
    CHECK_PARAM(اشاريو < 0 || اشاريو >= SDL_Get_انگ_Video_Drivers()) {
        SDL_InvalidParamError("index");
        أرجع عدم;
    }
    أرجع deduped_bootstrap[اشاريو]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ثابت حرف *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    صحيح i = 0;

    // Check to make sure we don't overwrite '_this'
    إذا (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    إذا (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        اذهب pre_driver_error;
    }
    init_events = true;
    إذا (!SDL_InitKeyboard()) {
        اذهب pre_driver_error;
    }
    init_keyboard = true;
    إذا (!SDL_PreInitMouse()) {
        اذهب pre_driver_error;
    }
    init_mouse = true;
    إذا (!SDL_InitTouch()) {
        اذهب pre_driver_error;
    }
    init_touch = true;
    إذا (!SDL_InitPen()) {
        اذهب pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = عدم;
#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    إذا (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#جيڪڏهن_پورو
    إذا (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    إذا (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        طالما (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_پڇاڙي = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_پڇاڙي) ? (driver_attempt_پڇاڙي - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            لكل (i = 0; bootstrap[i]; ++i) {
                إذا (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    إذا (video) {
                        اكسر;
                    }
                }
            }

            driver_attempt = (driver_attempt_پڇاڙي) ? (driver_attempt_پڇاڙي + 1) : عدم;
        }
    } وإلا {
        لكل (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            إذا (video) {
                اكسر;
            }
        }
    }
    إذا (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } وإلا {
        إذا (driver_name) {
            SDL_سيٽ_Error("%s not available", driver_name);
            اذهب pre_driver_error;
        }
        SDL_سيٽ_Error("No available video device");
        اذهب pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = عدم;
    SDL_GL_Reset_خاصيتون();

    // Initialize the video subsystem
    إذا (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        أرجع false;
    }

    // Make sure some displays were added
    إذا (_this->انگ_displays == 0) {
        SDL_QuitVideo();
        أرجع SDL_سيٽ_Error("The video driver did not add any displays");
    }

    SDL_جوڙيو_Hint_Callback(SDL_HINT_VIDEO_SYNC_دري_OPERATIONS, SDL_SyncHintWatcher, عدم);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    إذا (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    أرجع true;

pre_driver_error:
    SDL_assert(_this == عدم);
    إذا (init_pen) {
        SDL_QuitPen();
    }
    إذا (init_touch) {
        SDL_QuitTouch();
    }
    إذا (init_mouse) {
        SDL_QuitMouse();
    }
    إذا (init_keyboard) {
        SDL_QuitKeyboard();
    }
    إذا (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    أرجع false;
}

ثابت حرف *SDL_GetCurrentVideoDriver(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(فراغ)
{
    أرجع _this;
}

bool SDL_OnVideoThread(فراغ)
{
    أرجع (_this && SDL_GetCurrentThreadID() == _this->thread);
}

فراغ SDL_سيٽ_System_Theme(SDL_SystemTheme theme)
{
    إذا (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_بدليو_Event();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(فراغ)
{
    إذا (_this) {
        أرجع _this->system_theme;
    } وإلا {
        أرجع SDL_SYSTEM_THEME_UNKNOWN;
    }
}

فراغ SDL_UpdateDesktopBounds(فراغ)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    إذا (displays) {
        لكل (صحيح i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            إذا (SDL_GetDisplayBounds(displays[i], &bounds)) {
                إذا (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } وإلا {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ساكن فراغ SDL_Finalize_Display_گهڻائي(SDL_Display_گهڻائي *گهڻائي)
{
    // Make sure all the fields are set up correctly
    إذا (گهڻائي->pixel_density <= 0.0f) {
        گهڻائي->pixel_density = 1.0f;
    }

    إذا (گهڻائي->refresh_شرح_numerator > 0) {
        إذا (گهڻائي->refresh_شرح_denominator <= 0) {
            گهڻائي->refresh_شرح_denominator = 1;
        }
        گهڻائي->refresh_شرح = (عائم)گهڻائي->refresh_شرح_numerator / گهڻائي->refresh_شرح_denominator;
    } وإلا {
        SDL_CalculateFraction(گهڻائي->refresh_شرح, &گهڻائي->refresh_شرح_numerator, &گهڻائي->refresh_شرح_denominator);
    }
    گهڻائي->refresh_شرح = SDL_roundf(گهڻائي->refresh_شرح * 100) / 100.0f;
}

SDL_DisplayID SDL_جوڙيو_Basic_Video_Display(ثابت SDL_Display_گهڻائي *desktop_گهڻائي)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    إذا (desktop_گهڻائي) {
        SDL_memcpy(&display.desktop_گهڻائي, desktop_گهڻائي, حجم(display.desktop_گهڻائي));
    }
    أرجع SDL_جوڙيو_Video_Display(&display, false);
}

SDL_DisplayID SDL_جوڙيو_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحيح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(حجم(*new_display));
    إذا (!new_display) {
        أرجع 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->انگ_displays + 1) * حجم(*displays));
    إذا (!displays) {
        SDL_free(new_display);
        أرجع 0;
    }
    _this->displays = displays;
    _this->displays[_this->انگ_displays++] = new_display;

    id = SDL_Get_ايندڙ_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    إذا (display->name) {
        new_display->name = SDL_strdup(display->name);
    } وإلا {
        حرف name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    إذا (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_گهڻائي.displayID = id;
    new_display->current_گهڻائي = &new_display->desktop_گهڻائي;
    SDL_Finalize_Display_گهڻائي(&new_display->desktop_گهڻائي);

    لكل (i = 0; i < new_display->انگ_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_سيٽ_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    إذا (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    أرجع id;
}

فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_دري *دري;

    // See if any windows have changed to the new display
    لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
        SDL_Check_دري_Display_بدليو(دري);
    }
}

فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

فراغ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    صحيح display_اشاريو = SDL_Get_Display_اشاريو(displayID);
    إذا (display_اشاريو < 0) {
        أرجع;
    }

    display = _this->displays[display_اشاريو];

    إذا (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_گهڻائي.اندروني);
    display->desktop_گهڻائي.اندروني = عدم;
    SDL_free(display->اندروني);
    display->اندروني = عدم;
    SDL_free(display);

    إذا (display_اشاريو < (_this->انگ_displays - 1)) {
        SDL_memmove(&_this->displays[display_اشاريو], &_this->displays[display_اشاريو + 1], (_this->انگ_displays - display_اشاريو - 1) * حجم(_this->displays[display_اشاريو]));
    }
    --_this->انگ_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحيح *ڳڻپ)
{
    صحيح i;
    SDL_DisplayID *displays;

    إذا (!_this) {
        إذا (ڳڻپ) {
            *ڳڻپ = 0;
        }

        SDL_UninitializedVideo();
        أرجع عدم;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->انگ_displays + 1) * حجم(*displays));
    إذا (displays) {
        إذا (ڳڻپ) {
            *ڳڻپ = _this->انگ_displays;
        }

        لكل (i = 0; i < _this->انگ_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } وإلا {
        إذا (ڳڻپ) {
            *ڳڻپ = 0;
        }
    }
    أرجع displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحيح display_اشاريو;

    display_اشاريو = SDL_Get_Display_اشاريو(displayID);
    إذا (display_اشاريو < 0) {
        أرجع عدم;
    }
    أرجع _this->displays[display_اشاريو];
}

ساكن SDL_DisplayID Get_Display_For_دري(SDL_دري *دري)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    إذا (دري->flags & SDL_دري_FULLSCREEN) {
        displayID = دري->current_fullscreen_گهڻائي.displayID;
    }

    إذا (!displayID) {
        displayID = SDL_Get_Display_For_دري_Position(دري);
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, 0);

    أرجع SDL_GetVideoDisplay(Get_Display_For_دري(دري));
}

SDL_DisplayID SDL_GetPrimaryDisplay(فراغ)
{
    إذا (!_this || _this->انگ_displays == 0) {
        SDL_UninitializedVideo();
        أرجع 0;
    }
    أرجع _this->displays[0]->id;
}

صحيح SDL_Get_Display_اشاريو(SDL_DisplayID displayID)
{
    صحيح display_اشاريو;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع -1;
    }

    لكل (display_اشاريو = 0; display_اشاريو < _this->انگ_displays; ++display_اشاريو) {
        إذا (displayID == _this->displays[display_اشاريو]->id) {
            أرجع display_اشاريو;
        }
    }
    SDL_سيٽ_Error("Invalid display");
    أرجع -1;
}

SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->اندروني;
}

SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات_For_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, 0);

    أرجع SDL_Get_Display_Driver_معلومات(Get_Display_For_دري(دري));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    إذا (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    أرجع display->props;
}

ثابت حرف *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        أرجع SDL_InvalidParamError("rect");
    }

    إذا (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        إذا (_this->GetDisplayBounds(_this, display, rect)) {
            أرجع true;
        }
    }

    // Assume that the displays are left to right
    إذا (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } وإلا {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_اشاريو(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_گهڻائي->w;
    rect->h = display->current_گهڻائي->h;
    أرجع true;
}

ساكن صحيح ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    أرجع hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        أرجع SDL_InvalidParamError("rect");
    }

    إذا (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        أرجع true;
    }

    إذا (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        إذا (_this->GetDisplayUsableBounds(_this, display, rect)) {
            أرجع true;
        }
    }

    // Oh well, just give the entire display bounds.
    أرجع SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    إذا (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        أرجع display->natural_orientation;
    } وإلا {
        // Default to landscape if the driver hasn't set it
        أرجع SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    إذا (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        أرجع display->current_orientation;
    } وإلا {
        // Default to landscape if the driver hasn't set it
        أرجع SDL_ORIENTATION_LANDSCAPE;
    }
}

فراغ SDL_سيٽ_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale)
{
    إذا (scale != display->content_scale) {
        SDL_دري *دري;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_بدليو, 0, 0);

        // Check the windows on this display
        لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
            إذا (display->id == دري->displayID) {
                SDL_Check_دري_Display_Scale_بدليو(دري);
            }
        }
    }
}

عائم SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    أرجع display->content_scale;
}

فراغ SDL_سيٽ_دري_HDRProperties(SDL_دري *دري, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    إذا (دري->HDR.HDR_headroom != HDR_clamped.HDR_headroom || دري->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID دري_props = SDL_Get_دري_Properties(دري);

        SDL_سيٽ_Float_Property(دري_props, SDL_PROP_دري_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_سيٽ_Float_Property(دري_props, SDL_PROP_دري_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_سيٽ_Boolean_Property(دري_props, SDL_PROP_دري_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&دري->HDR, &HDR_clamped);

        إذا (send_event) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_HDR_STATE_بدليو, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

فراغ SDL_سيٽ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ثابت bool بدليو = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	إذا (بدليو) {
		SDL_سيٽ_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    إذا (بدليو && !SDL_DriverSendsHDRChanges(_this)) {
        لكل (SDL_دري *w = display->device->windows; w; w = w->ايندڙ) {
            إذا (Get_Display_For_دري(w) == display->id) {
                SDL_سيٽ_دري_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ساكن فراغ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    إذا (display->انگ_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ساكن ثابت SDL_Display_گهڻائي *SDL_Get_Fullscreen_گهڻائي_ميلاپ(ثابت SDL_Display_گهڻائي *گهڻائي)
{
    SDL_VideoDisplay *display;
    SDL_Display_گهڻائي fullscreen_گهڻائي;

    إذا (گهڻائي->w <= 0 || گهڻائي->h <= 0) {
        // Use the desktop mode
        أرجع عدم;
    }

    SDL_memcpy(&fullscreen_گهڻائي, گهڻائي, حجم(fullscreen_گهڻائي));
    إذا (fullscreen_گهڻائي.displayID == 0) {
        fullscreen_گهڻائي.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_گهڻائي(&fullscreen_گهڻائي);

    گهڻائي = عدم;

    display = SDL_GetVideoDisplay(fullscreen_گهڻائي.displayID);
    إذا (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        إذا (!گهڻائي) {
            لكل (صحيح i = 0; i < display->انگ_fullscreen_modes; ++i) {
                إذا (SDL_memcmp(&fullscreen_گهڻائي, &display->fullscreen_modes[i], حجم(fullscreen_گهڻائي)) == 0) {
                    گهڻائي = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }

        // Search for a mode with the same characteristics
        إذا (!گهڻائي) {
            لكل (صحيح i = 0; i < display->انگ_fullscreen_modes; ++i) {
                إذا (cmpmodes(&fullscreen_گهڻائي, &display->fullscreen_modes[i]) == 0) {
                    گهڻائي = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }
    }
    أرجع گهڻائي;
}

bool SDL_جوڙيو_Fullscreen_Display_گهڻائي(SDL_VideoDisplay *display, ثابت SDL_Display_گهڻائي *گهڻائي)
{
    SDL_Display_گهڻائي *modes;
    SDL_Display_گهڻائي new_گهڻائي;
    صحيح i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_گهڻائي, گهڻائي, حجم(new_گهڻائي));
    new_گهڻائي.displayID = display->id;
    SDL_Finalize_Display_گهڻائي(&new_گهڻائي);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->انگ_fullscreen_modes;
    لكل (i = 0; i < nmodes; ++i) {
        إذا (cmpmodes(&new_گهڻائي, &modes[i]) == 0) {
            أرجع false;
        }
    }

    // Go ahead and add the new mode
    إذا (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_گهڻائي *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        إذا (!modes) {
            أرجع false;
        }

        إذا (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            لكل (i = 0; i < nmodes; ++i) {
                إذا (display->current_گهڻائي == &display->fullscreen_modes[i]) {
                    display->current_گهڻائي = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->انگ_fullscreen_modes++], &new_گهڻائي, حجم(new_گهڻائي));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->انگ_fullscreen_modes,
              حجم(SDL_Display_گهڻائي), cmpmodes);

    أرجع true;
}

فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحيح i;

    لكل (i = display->انگ_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].اندروني);
        display->fullscreen_modes[i].اندروني = عدم;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = عدم;
    display->انگ_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_گهڻائي = &display->desktop_گهڻائي;
}

SDL_Display_گهڻائي **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحيح *ڳڻپ)
{
    صحيح i;
    صحيح انگ_modes;
    SDL_Display_گهڻائي **نتيجو;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    إذا (ڳڻپ) {
        *ڳڻپ = 0;
    }

    CHECK_DISPLAY_MAGIC(display, عدم);

    SDL_UpdateFullscreenDisplayModes(display);

    انگ_modes = display->انگ_fullscreen_modes;
    نتيجو = (SDL_Display_گهڻائي **)SDL_malloc((انگ_modes + 1) * حجم(*نتيجو) + انگ_modes * حجم(**نتيجو));
    إذا (نتيجو) {
        SDL_Display_گهڻائي *modes = (SDL_Display_گهڻائي *)((Uint8 *)نتيجو + ((انگ_modes + 1) * حجم(*نتيجو)));
        إذا (انگ_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, انگ_modes * حجم(*modes));
        }
        لكل (i = 0; i < انگ_modes; ++i) {
            نتيجو[i] = modes++;
        }
        نتيجو[i] = عدم;

        إذا (ڳڻپ) {
            *ڳڻپ = انگ_modes;
        }
    } وإلا {
        إذا (ڳڻپ) {
            *ڳڻپ = 0;
        }
    }
    أرجع نتيجو;
}

bool SDL_Get_Closest_Fullscreen_Display_گهڻائي(SDL_DisplayID displayID, صحيح w, صحيح h, عائم refresh_شرح, bool include_مٿاهون_density_modes, SDL_Display_گهڻائي *نتيجو)
{
    CHECK_PARAM(!نتيجو) {
        أرجع SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_Display_گهڻائي *گهڻائي, *closest = عدم;
    عائم aspect_تناسب;
    صحيح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(نتيجو);

    CHECK_DISPLAY_MAGIC(display, false);

    إذا (h > 0) {
        aspect_تناسب = (عائم)w / h;
    } وإلا {
        aspect_تناسب = 1.0f;
    }

    إذا (refresh_شرح == 0.0f) {
        refresh_شرح = display->desktop_گهڻائي.refresh_شرح;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    لكل (i = 0; i < display->انگ_fullscreen_modes; ++i) {
        گهڻائي = &display->fullscreen_modes[i];

        إذا (w > گهڻائي->w) {
            // Out of sorted modes large enough here
            اكسر;
        }
        إذا (h > گهڻائي->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            استمر;
        }
        إذا (گهڻائي->pixel_density > 1.0f && !include_مٿاهون_density_modes) {
            استمر;
        }
        إذا (closest) {
            عائم current_aspect_تناسب = (عائم)گهڻائي->w / گهڻائي->h;
            عائم closest_aspect_تناسب = (عائم)closest->w / closest->h;
            إذا (SDL_fabsf(aspect_تناسب - closest_aspect_تناسب) < SDL_fabsf(aspect_تناسب - current_aspect_تناسب)) {
                // The mode we already found has a better aspect ratio match
                استمر;
            }

            إذا (گهڻائي->w == closest->w && گهڻائي->h == closest->h) {
                إذا (SDL_fabsf(closest->refresh_شرح - refresh_شرح) < SDL_fabsf(گهڻائي->refresh_شرح - refresh_شرح)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    استمر;
                }
                إذا (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(گهڻائي->format)) {
                    // Prefer the highest color depth
                    استمر;
                }
            }
        }

        closest = گهڻائي;
    }
    إذا (!closest) {
        أرجع SDL_سيٽ_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(نتيجو, closest);

    أرجع true;
}

ساكن bool Display_گهڻائي_بدليو(ثابت SDL_Display_گهڻائي *old_گهڻائي, ثابت SDL_Display_گهڻائي *new_گهڻائي)
{
    أرجع ((old_گهڻائي->displayID && old_گهڻائي->displayID != new_گهڻائي->displayID) ||
            (old_گهڻائي->format && old_گهڻائي->format != new_گهڻائي->format) ||
            (old_گهڻائي->w && old_گهڻائي->h && (old_گهڻائي->w != new_گهڻائي->w ||old_گهڻائي->h != new_گهڻائي->h)) ||
            (old_گهڻائي->pixel_density != 0.0f && old_گهڻائي->pixel_density != new_گهڻائي->pixel_density) ||
            (old_گهڻائي->refresh_شرح != 0.0f && old_گهڻائي->refresh_شرح != new_گهڻائي->refresh_شرح));
}

فراغ SDL_سيٽ_Desktop_Display_گهڻائي(SDL_VideoDisplay *display, ثابت SDL_Display_گهڻائي *گهڻائي)
{
    SDL_Display_گهڻائي آخري_گهڻائي;

    إذا (display->fullscreen_سرگرم) {
        // This is a temporary mode change, don't save the desktop mode
        أرجع;
    }

    SDL_copyp(&آخري_گهڻائي, &display->desktop_گهڻائي);

    SDL_free(display->desktop_گهڻائي.اندروني);
    SDL_copyp(&display->desktop_گهڻائي, گهڻائي);
    display->desktop_گهڻائي.displayID = display->id;
    SDL_Finalize_Display_گهڻائي(&display->desktop_گهڻائي);

    إذا (Display_گهڻائي_بدليو(&آخري_گهڻائي, &display->desktop_گهڻائي)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_گهڻائي_بدليو, گهڻائي->w, گهڻائي->h);
        إذا (display->current_گهڻائي == &display->desktop_گهڻائي) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_گهڻائي_بدليو, گهڻائي->w, گهڻائي->h);
        }
    }
}

ثابت SDL_Display_گهڻائي *SDL_Get_Desktop_Display_گهڻائي(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع &display->desktop_گهڻائي;
}

فراغ SDL_سيٽ_Current_Display_گهڻائي(SDL_VideoDisplay *display, ثابت SDL_Display_گهڻائي *گهڻائي)
{
    SDL_Display_گهڻائي آخري_گهڻائي;

    إذا (display->current_گهڻائي) {
        SDL_copyp(&آخري_گهڻائي, display->current_گهڻائي);
    } وإلا {
        SDL_zero(آخري_گهڻائي);
    }

    display->current_گهڻائي = گهڻائي;

    إذا (Display_گهڻائي_بدليو(&آخري_گهڻائي, گهڻائي)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_گهڻائي_بدليو, گهڻائي->w, گهڻائي->h);
    }
}

ثابت SDL_Display_گهڻائي *SDL_Get_Current_Display_گهڻائي(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->current_گهڻائي;
}

bool SDL_سيٽ_Display_گهڻائي_For_Display(SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    إذا (SDL_گهڻائي_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        أرجع true;
    }

    إذا (!گهڻائي) {
        گهڻائي = &display->desktop_گهڻائي;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#جيڪڏهن_وصف_نه_ٿيل SDL_PLATFORM_RISCOS
    إذا (گهڻائي == display->current_گهڻائي) {
        أرجع true;
    }
#جيڪڏهن_پورو

    // Actually change the display mode
    إذا (_this->سيٽ_Display_گهڻائي) {
        bool نتيجو;

        _this->setting_display_گهڻائي = true;
        نتيجو = _this->سيٽ_Display_گهڻائي(_this, display, گهڻائي);
        _this->setting_display_گهڻائي = false;
        إذا (!نتيجو) {
            أرجع false;
        }
    }

    SDL_سيٽ_Current_Display_گهڻائي(display, گهڻائي);

    أرجع true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساكن فراغ SDL_Get_Closest_نقطو_On_Rect(ثابت SDL_Rect *rect, SDL_نقطو *نقطو)
{
    ثابت صحيح ساڄو = rect->x + rect->w - 1;
    ثابت صحيح bottom = rect->y + rect->h - 1;

    إذا (نقطو->x < rect->x) {
        نقطو->x = rect->x;
    } وإلا إذا (نقطو->x > ساڄو) {
        نقطو->x = ساڄو;
    }

    إذا (نقطو->y < rect->y) {
        نقطو->y = rect->y;
    } وإلا إذا (نقطو->y > bottom) {
        نقطو->y = bottom;
    }
}

ساكن SDL_DisplayID GetDisplayForRect(صحيح x, صحيح y, صحيح w, صحيح h)
{
    صحيح i, dist;
    SDL_DisplayID closest = 0;
    صحيح closest_dist = 0x7FFFFFFF;
    SDL_نقطو closest_نقطو_on_display;
    SDL_نقطو delta;
    SDL_نقطو center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    إذا (_this) {
        لكل (i = 0; i < _this->انگ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            إذا (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, عدم)) {
                أرجع display->id;
            }

            // Snap window center to the display rect
            closest_نقطو_on_display = center;
            SDL_Get_Closest_نقطو_On_Rect(&display_rect, &closest_نقطو_on_display);

            delta.x = center.x - closest_نقطو_on_display.x;
            delta.y = center.y - closest_نقطو_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            إذا (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    إذا (closest == 0) {
        SDL_سيٽ_Error("Couldn't find any displays");
    }

    أرجع closest;
}

فراغ SDL_Relative_منزل_Global_For_دري(SDL_دري *دري, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y)
{
    SDL_دري *w;

    إذا (SDL_دري_IS_POPUP(دري)) {
        // Calculate the total offset of the popup from the parents
        لكل (w = دري->والد; w; w = w->والد) {
            rel_x += w->x;
            rel_y += w->y;

            إذا (!SDL_دري_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    إذا (abs_x) {
        *abs_x = rel_x;
    }
    إذا (abs_y) {
        *abs_y = rel_y;
    }
}

فراغ SDL_Global_منزل_Relative_For_دري(SDL_دري *دري, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y)
{
    SDL_دري *w;

    إذا (SDL_دري_IS_POPUP(دري)) {
        // Convert absolute window coordinates to relative for a popup
        لكل (w = دري->والد; w; w = w->والد) {
            abs_x -= w->x;
            abs_y -= w->y;

            إذا (!SDL_دري_IS_POPUP(w)) {
                اكسر;
            }
        }
    }

    إذا (rel_x) {
        *rel_x = abs_x;
    }
    إذا (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_Get_Display_For_نقطو(ثابت SDL_نقطو *نقطو)
{
    CHECK_PARAM(!نقطو) {
        SDL_InvalidParamError("point");
        أرجع 0;
    }

    أرجع GetDisplayForRect(نقطو->x, نقطو->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ثابت SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        أرجع 0;
    }

    أرجع GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ساكن SDL_DisplayID GetDisplayAtOrigin(صحيح x, صحيح y)
{
    لكل (صحيح i = 0; i < _this->انگ_displays; ++i) {
        SDL_Rect rect;
        ثابت SDL_DisplayID cur_id = _this->displays[i]->id;
        إذا (SDL_GetDisplayBounds(cur_id, &rect)) {
            إذا (x == rect.x && y == rect.y) {
                أرجع cur_id;
            }
        }
    }

    أرجع 0;
}

SDL_DisplayID SDL_Get_Display_For_دري_Position(SDL_دري *دري)
{
    صحيح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_دري_MAGIC(دري, 0);

    إذا (_this->Get_Display_For_دري) {
        displayID = _this->Get_Display_For_دري(_this, دري);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_منزل_Global_For_دري(دري, دري->x, دري->y, &x, &y);

    إذا (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        إذا (دري->flags & SDL_دري_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } وإلا {
            displayID = GetDisplayForRect(x, y, دري->w, دري->h);
        }
    }
    إذا (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_دري(SDL_دري *دري)
{
    SDL_DisplayID displayID = 0;

    CHECK_دري_MAGIC(دري, عدم);

    // An explicit fullscreen display overrides all
    إذا (دري->current_fullscreen_گهڻائي.displayID) {
        displayID = دري->current_fullscreen_گهڻائي.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    إذا (!displayID) {
        displayID = دري->pending_displayID;
    }
    إذا (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحيح x = دري->آخري_position_pending ? دري->pending.x : دري->x;
        ثابت صحيح y = دري->آخري_position_pending ? دري->pending.y : دري->y;
        ثابت صحيح w = دري->آخري_سائيز_pending ? دري->pending.w : دري->w;
        ثابت صحيح h = دري->آخري_سائيز_pending ? دري->pending.h : دري->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        إذا (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    إذا (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    أرجع SDL_GetVideoDisplay(displayID);
}

#وصف_ڪريو SDL_PROP_SDL2_COMPAT_دري_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID دري_props = SDL_Get_دري_Properties(دري);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_دري(دري);
    إذا (fs_display) {
        SDL_سيٽ_عدد_Property(دري_props, SDL_PROP_SDL2_COMPAT_دري_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } وإلا {
        SDL_ClearProperty(دري_props, SDL_PROP_SDL2_COMPAT_دري_PREFERRED_FULLSCREEN_DISPLAY);
    }

    أرجع Get_Display_For_دري(دري);
}

ساكن فراغ SDL_Check_دري_Display_بدليو(SDL_دري *دري)
{
    إذا (SDL_SendsDisplayChanges(_this)) {
        أرجع;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_دري_Position(دري);

    إذا (displayID != دري->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect دري_rect;
        SDL_Rect old_overlap, new_overlap;

        إذا (SDL_GetDisplayBounds(دري->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            دري_rect.x = دري->x;
            دري_rect.y = دري->y;
            دري_rect.w = دري->w;
            دري_rect.h = دري->h;

            إذا (SDL_GetRectIntersection(&old_bounds, &دري_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &دري_rect, &new_overlap)) {
                صحيح old_area = old_overlap.w * old_overlap.h;
                صحيح new_area = new_overlap.w * new_overlap.h;
                عائم new_overlap_تناسب = (new_area / ((عائم)old_area + new_area));
                إذا (new_overlap_تناسب < 0.80) {
                    أرجع;
                }
            }
        }
    }

    إذا (displayID != دري->displayID) {
        صحيح i, display_اشاريو;

        // Sanity check our fullscreen windows
        display_اشاريو = SDL_Get_Display_اشاريو(displayID);
        لكل (i = 0; i < _this->انگ_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            إذا (display->fullscreen_دري == دري) {
                إذا (display_اشاريو != i) {
                    إذا (display_اشاريو < 0) {
                        display_اشاريو = i;
                    } وإلا {
                        SDL_VideoDisplay *new_display = _this->displays[display_اشاريو];

                        // The window was moved to a different display
                        إذا (new_display->fullscreen_دري &&
                            new_display->fullscreen_دري != دري) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_دري(new_display->fullscreen_دري);
                        }
                        new_display->fullscreen_دري = دري;
                        display->fullscreen_دري = عدم;
                    }
                }
                اكسر;
            }
        }

        SDL_Send_دري_Event(دري, SDL_EVENT_دري_DISPLAY_بدليو, (صحيح)displayID, 0);
    }
}

عائم SDL_Get_دري_Pixel_Density(SDL_دري *دري)
{
    صحيح دري_w, دري_h, pixel_w, pixel_h;
    عائم pixel_density = 1.0f;

    CHECK_دري_MAGIC(دري, 0.0f);

    إذا (SDL_Get_دري_سائيز(دري, &دري_w, &دري_h) &&
        SDL_Get_دري_سائيز_اندريون_Pixels(دري, &pixel_w, &pixel_h)) {
        pixel_density = (عائم)pixel_w / دري_w;
    }
    أرجع pixel_density;
}

عائم SDL_Get_دري_Display_Scale(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, 0.0f);

    أرجع دري->display_scale;
}

ساكن فراغ SDL_Check_دري_Display_Scale_بدليو(SDL_دري *دري)
{
    عائم display_scale;

    إذا (_this->Get_دري_Content_Scale) {
        display_scale = _this->Get_دري_Content_Scale(_this, دري);
    } وإلا {
        ثابت عائم pixel_density = SDL_Get_دري_Pixel_Density(دري);
        ثابت عائم content_scale = SDL_GetDisplayContentScale(دري->displayID);

        display_scale = pixel_density * content_scale;
    }

    إذا (display_scale != دري->display_scale) {
        دري->display_scale = display_scale;
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_DISPLAY_SCALE_بدليو, 0, 0);
    }
}

bool SDL_Update_Fullscreen_گهڻائي(SDL_دري *دري, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = عدم;
    SDL_Display_گهڻائي *گهڻائي = عدم;
    صحيح i;

    CHECK_دري_MAGIC(دري, false);

    دري->fullscreen_exclusive = false;
    دري->update_fullscreen_on_display_بدليو = false;

    // If we are in the process of hiding don't go back to fullscreen
    إذا (دري->is_destroying || دري->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    إذا (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_دري(دري);
        إذا (!display) {
            // This should never happen, but it did...
            اذهب پورو;
        }
    } وإلا {
        لكل (i = 0; i < _this->انگ_displays; ++i) {
            display = _this->displays[i];
            إذا (display->fullscreen_دري == دري) {
                اكسر;
            }
        }
        إذا (!display || i == _this->انگ_displays) {
            // Already not fullscreen on any display
            display = عدم;
        }
    }

    إذا (fullscreen) {
        گهڻائي = (SDL_Display_گهڻائي *)SDL_Get_دري_Fullscreen_گهڻائي(دري);
        إذا (گهڻائي) {
            دري->fullscreen_exclusive = true;
        } وإلا {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(دري->current_fullscreen_گهڻائي);
        }
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (دري->is_destroying && !دري->آخري_fullscreen_exclusive_display) {
            دري->fullscreen_exclusive = false;
            إذا (display) {
                display->fullscreen_دري = عدم;
            }
            اذهب پورو;
        }
        إذا (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            إذا (fullscreen && Cocoa_Is_دري_اندريون_Fullscreen_Space(دري) && !دري->آخري_fullscreen_exclusive_display && دري->fullscreen_exclusive) {
                إذا (!Cocoa_سيٽ_دري_Fullscreen_Space(دري, false, true)) {
                    اذهب error;
                }
            } وإلا إذا (fullscreen && دري->آخري_fullscreen_exclusive_display && !دري->fullscreen_exclusive) {
                لكل (i = 0; i < _this->انگ_displays; ++i) {
                    SDL_VideoDisplay *آخري_display = _this->displays[i];
                    إذا (آخري_display->fullscreen_دري == دري) {
                        SDL_سيٽ_Display_گهڻائي_For_Display(آخري_display, عدم);
                        إذا (_this->سيٽ_دري_Fullscreen) {
                            _this->سيٽ_دري_Fullscreen(_this, دري, آخري_display, false);
                        }
                        آخري_display->fullscreen_دري = عدم;
                    }
                }
            }

            إذا (Cocoa_سيٽ_دري_Fullscreen_Space(دري, !!fullscreen, syncHint)) {
                اذهب پورو;
            }
        }
    }
#جيڪڏهن_پورو

    إذا (display) {
        // Restore the video mode on other displays if needed
        لكل (i = 0; i < _this->انگ_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            إذا (other != display && other->fullscreen_دري == دري) {
                SDL_سيٽ_Display_گهڻائي_For_Display(other, عدم);
                other->fullscreen_دري = عدم;
            }
        }
    }

    إذا (fullscreen) {
        صحيح گهڻائي_w = 0, گهڻائي_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        إذا (display->fullscreen_دري &&
            display->fullscreen_دري != دري) {
            SDL_Minimize_دري(display->fullscreen_دري);
        }

        display->fullscreen_سرگرم = دري->fullscreen_exclusive;

        إذا (!SDL_سيٽ_Display_گهڻائي_For_Display(display, گهڻائي)) {
            اذهب error;
        }
        إذا (commit) {
            SDL_Fullscreen_نتيجو ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->سيٽ_دري_Fullscreen) {
                ret = _this->سيٽ_دري_Fullscreen(_this, دري, display, fullscreen);
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
                    SDL_Send_دري_Event(دري, SDL_EVENT_دري_ENTER_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_سرگرم = false;
                اذهب error;
            }
        }

        إذا (دري->flags & SDL_دري_FULLSCREEN) {
            display->fullscreen_دري = دري;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                إذا (گهڻائي) {
                    گهڻائي_w = گهڻائي->w;
                    گهڻائي_h = گهڻائي->h;
                    SDL_GetDisplayBounds(گهڻائي->displayID, &displayRect);
                } وإلا {
                    گهڻائي_w = display->desktop_گهڻائي.w;
                    گهڻائي_h = display->desktop_گهڻائي.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                إذا (دري->w != گهڻائي_w || دري->h != گهڻائي_h) {
                    resized = true;
                }

                SDL_Send_دري_Event(دري, SDL_EVENT_دري_MOVED, displayRect.x, displayRect.y);

                إذا (resized) {
                    SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, گهڻائي_w, گهڻائي_h);
                } وإلا {
                    SDL_On_دري_Resized(دري);
                }
            }
        }
    } وإلا {
        bool resized = false;

        // Restore the desktop mode
        إذا (display) {
            display->fullscreen_سرگرم = false;

            SDL_سيٽ_Display_گهڻائي_For_Display(display, عدم);
        }
        إذا (commit) {
            SDL_Fullscreen_نتيجو ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->سيٽ_دري_Fullscreen) {
                SDL_VideoDisplay *ڀريل_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_دري(دري);
                إذا (ڀريل_screen_display) {
                    ret = _this->سيٽ_دري_Fullscreen(_this, دري, ڀريل_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (دري->flags & SDL_دري_FULLSCREEN) {
                    SDL_Send_دري_Event(دري, SDL_EVENT_دري_LEAVE_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                اذهب error;
            }
        }

        إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
            إذا (display) {
                display->fullscreen_دري = عدم;
            }

            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_دري_Event(دري, SDL_EVENT_دري_MOVED, دري->windowed.x, دري->windowed.y);
                إذا (resized) {
                    SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, دري->windowed.w, دري->windowed.h);
                } وإلا {
                    SDL_On_دري_Resized(دري);
                }
            }
        }
    }

پورو:
    دري->آخري_fullscreen_exclusive_display = display && (دري->flags & SDL_دري_FULLSCREEN) && دري->fullscreen_exclusive ? display->id : 0;
    أرجع true;

error:
    إذا (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    أرجع false;
}

bool SDL_سيٽ_دري_Fullscreen_گهڻائي(SDL_دري *دري, ثابت SDL_Display_گهڻائي *گهڻائي)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (گهڻائي) {
        إذا (!SDL_Get_Fullscreen_گهڻائي_ميلاپ(گهڻائي)) {
            أرجع SDL_سيٽ_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&دري->requested_fullscreen_گهڻائي, گهڻائي);
    } وإلا {
        SDL_zero(دري->requested_fullscreen_گهڻائي);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&دري->current_fullscreen_گهڻائي, &دري->requested_fullscreen_گهڻائي);

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_دري_اندريون_Fullscreen_Space_Transition(دري)) {
        SDL_Sync_دري(دري);
    }
#جيڪڏهن_پورو
    إذا (SDL_دري_FULLSCREEN_VISIBLE(دري)) {
        SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(دري);
    }

    أرجع true;
}

ثابت SDL_Display_گهڻائي *SDL_Get_دري_Fullscreen_گهڻائي(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, عدم);
    CHECK_دري_NOT_POPUP(دري, عدم);

    إذا (دري->flags & SDL_دري_FULLSCREEN) {
        أرجع SDL_Get_Fullscreen_گهڻائي_ميلاپ(&دري->current_fullscreen_گهڻائي);
    } وإلا {
        أرجع SDL_Get_Fullscreen_گهڻائي_ميلاپ(&دري->requested_fullscreen_گهڻائي);
    }
}

فراغ *SDL_Get_دري_ICCProfile(SDL_دري *دري, size_t *سائيز)
{
    إذا (!_this->Get_دري_ICCProfile) {
        SDL_Unsupported();
        أرجع عدم;
    }
    أرجع _this->Get_دري_ICCProfile(_this, دري, سائيز);
}

SDL_PixelFormat SDL_Get_دري_Pixel_Format(SDL_دري *دري)
{
    SDL_DisplayID displayID;
    ثابت SDL_Display_گهڻائي *گهڻائي;

    CHECK_دري_MAGIC(دري, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_دري(دري);
    گهڻائي = SDL_Get_Current_Display_گهڻائي(displayID);
    إذا (گهڻائي) {
        أرجع گهڻائي->format;
    } وإلا {
        أرجع SDL_PIXELFORMAT_UNKNOWN;
    }
}

#وصف_ڪريو CREATE_FLAGS \
    (SDL_دري_OPENGL | SDL_دري_BORDERLESS | SDL_دري_RESIZABLE | SDL_دري_مٿاهون_PIXEL_DENSITY | SDL_دري_ALWAYS_ON_چوٽي | SDL_دري_POPUP_MENU | SDL_دري_UTILITY | SDL_دري_TOOLTIP | SDL_دري_VULKAN | SDL_دري_MINIMIZED | SDL_دري_METAL | SDL_دري_TRANSPARENT | SDL_دري_NOT_FOCUSABLE | SDL_دري_FILL_DOCUMENT)

ساكن SDL_INLINE bool IsAcceptingDragAndDrop(فراغ)
{
    إذا (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_متن)) {
        أرجع true;
    }
    أرجع false;
}

// prepare a newly-created window
ساكن SDL_INLINE فراغ PrepareDragAndDropSupport(SDL_دري *دري)
{
    إذا (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(دري, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
فراغ SDL_ToggleDragAndDropSupport(فراغ)
{
    إذا (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_دري *دري;
        لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
            _this->AcceptDragAndDrop(دري, enable);
        }
    }
}

SDL_دري ** SDLCALL SDL_GetWindows(صحيح *ڳڻپ)
{
    إذا (ڳڻپ) {
        *ڳڻپ = 0;
    }

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    SDL_دري *دري;
    صحيح انگ_added = 0;
    صحيح انگ_windows = 0;
    لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
        ++انگ_windows;
    }

    SDL_دري **windows = (SDL_دري **)SDL_malloc((انگ_windows + 1) * حجم(*windows));
    إذا (!windows) {
        أرجع عدم;
    }

    لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
        windows[انگ_added++] = دري;
        إذا (انگ_added == انگ_windows) {
            // Race condition? Multi-threading not supported, ignore it
            اكسر;
        }
    }
    windows[انگ_added] = عدم;

    إذا (ڳڻپ) {
        *ڳڻپ = انگ_added;
    }
    أرجع windows;
}

ساكن فراغ Apply_دري_Flags(SDL_دري *دري, SDL_دري_Flags flags)
{
    إذا (!SDL_دري_IS_POPUP(دري)) {
        إذا (!(flags & (SDL_دري_MINIMIZED | SDL_دري_MAXIMIZED))) {
            SDL_Restore_دري(دري);
        }
        إذا (flags & SDL_دري_MAXIMIZED) {
            SDL_Maximize_دري(دري);
        }

        SDL_سيٽ_دري_Fullscreen(دري, (flags & SDL_دري_FULLSCREEN) != 0);

        إذا (flags & SDL_دري_MINIMIZED) {
            SDL_Minimize_دري(دري);
        }

        إذا (flags & SDL_دري_MODAL) {
            SDL_سيٽ_دري_Modal(دري, true);
        }

        إذا (flags & SDL_دري_MOUSE_GRABBED) {
            SDL_سيٽ_دري_Mouse_Grab(دري, true);
        }
        إذا (flags & SDL_دري_KEYBOARD_GRABBED) {
            SDL_سيٽ_دري_Keyboard_Grab(دري, true);
        }
    }
}

ساكن فراغ SDL_پڄاڻي_دري_Creation(SDL_دري *دري, SDL_دري_Flags flags)
{
    PrepareDragAndDropSupport(دري);

    إذا (دري->flags & SDL_دري_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } وإلا {
        Apply_دري_Flags(دري, flags);
        إذا (!(flags & SDL_دري_HIDDEN)) {
            SDL_Show_دري(دري);
        }
    }

#إذا defined(SDL_PLATFORM_LINUX)
    إذا (!SDL_دري_IS_POPUP(دري)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_سيٽ_دري_ترقي_State(دري, SDL_ترقي_STATE_NONE);
        SDL_سيٽ_دري_ترقي_قدر(دري, 0.0f);
    }
#جيڪڏهن_پورو
}

ساكن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    أرجع SDL_سيٽ_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساكن bool SDL_DllNotSupported(ثابت حرف *name)
{
    أرجع SDL_سيٽ_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ساكن بنية {
    ثابت حرف *property_name;
    SDL_دري_Flags flag;
    bool invert_قدر;
} SDL_دري_Flag_Properties[] = {
    { SDL_PROP_دري_CREATE_ALWAYS_ON_چوٽي_BOOLEAN,      SDL_دري_ALWAYS_ON_چوٽي,       false },
    { SDL_PROP_دري_CREATE_BORDERLESS_BOOLEAN,         SDL_دري_BORDERLESS,          false },
    { SDL_PROP_دري_CREATE_FOCUSABLE_BOOLEAN,          SDL_دري_NOT_FOCUSABLE,       true },
    { SDL_PROP_دري_CREATE_FULLSCREEN_BOOLEAN,         SDL_دري_FULLSCREEN,          false },
    { SDL_PROP_دري_CREATE_HIDDEN_BOOLEAN,             SDL_دري_HIDDEN,              false },
    { SDL_PROP_دري_CREATE_مٿاهون_PIXEL_DENSITY_BOOLEAN, SDL_دري_مٿاهون_PIXEL_DENSITY,  false },
    { SDL_PROP_دري_CREATE_MAXIMIZED_BOOLEAN,          SDL_دري_MAXIMIZED,           false },
    { SDL_PROP_دري_CREATE_MENU_BOOLEAN,               SDL_دري_POPUP_MENU,          false },
    { SDL_PROP_دري_CREATE_METAL_BOOLEAN,              SDL_دري_METAL,               false },
    { SDL_PROP_دري_CREATE_MINIMIZED_BOOLEAN,          SDL_دري_MINIMIZED,           false },
    { SDL_PROP_دري_CREATE_MODAL_BOOLEAN,              SDL_دري_MODAL,               false },
    { SDL_PROP_دري_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_دري_MOUSE_GRABBED,       false },
    { SDL_PROP_دري_CREATE_OPENGL_BOOLEAN,             SDL_دري_OPENGL,              false },
    { SDL_PROP_دري_CREATE_RESIZABLE_BOOLEAN,          SDL_دري_RESIZABLE,           false },
    { SDL_PROP_دري_CREATE_TRANSPARENT_BOOLEAN,        SDL_دري_TRANSPARENT,         false },
    { SDL_PROP_دري_CREATE_TOOLTIP_BOOLEAN,            SDL_دري_TOOLTIP,             false },
    { SDL_PROP_دري_CREATE_UTILITY_BOOLEAN,            SDL_دري_UTILITY,             false },
    { SDL_PROP_دري_CREATE_VULKAN_BOOLEAN,             SDL_دري_VULKAN,              false }
};

ساكن SDL_دري_Flags SDL_Get_دري_Flag_Properties(SDL_PropertiesID props)
{
    بنانشان i;
    SDL_دري_Flags flags = (SDL_دري_Flags)SDL_Get_عدد_Property(props, SDL_PROP_دري_CREATE_FLAGS_عدد, 0);

    لكل (i = 0; i < SDL_arraysize(SDL_دري_Flag_Properties); ++i) {
        إذا (SDL_دري_Flag_Properties[i].invert_قدر) {
            إذا (!SDL_GetBooleanProperty(props, SDL_دري_Flag_Properties[i].property_name, true)) {
                flags |= SDL_دري_Flag_Properties[i].flag;
            }
        } وإلا {
            إذا (SDL_GetBooleanProperty(props, SDL_دري_Flag_Properties[i].property_name, false)) {
                flags |= SDL_دري_Flag_Properties[i].flag;
            }
        }
    }
    أرجع flags;
}

SDL_دري *SDL_Create_دري_With_Properties(SDL_PropertiesID props)
{
    SDL_دري *دري;
    ثابت حرف *title = SDL_GetStringProperty(props, SDL_PROP_دري_CREATE_TITLE_STRING, عدم);
    صحيح x = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_دري_CREATE_X_عدد, SDL_WINDOWPOS_UNDEFINED);
    صحيح y = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_دري_CREATE_Y_عدد, SDL_WINDOWPOS_UNDEFINED);
    صحيح w = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_دري_CREATE_ويڪر_عدد, 0);
    صحيح h = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_دري_CREATE_اوچائي_عدد, 0);
    SDL_دري *والد = (SDL_دري *)SDL_Get_اشارو_Property(props, SDL_PROP_دري_CREATE_والد_اشارو, عدم);
    SDL_دري_Flags flags = SDL_Get_دري_Flag_Properties(props);
    SDL_دري_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_دري_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    إذا (!_this) {
        // Initialize the video system if needed
        إذا (!SDL_Init(SDL_INIT_VIDEO)) {
            أرجع عدم;
        }

        // Make clang-tidy happy
        إذا (!_this) {
            أرجع عدم;
        }
    }

    إذا ((flags & SDL_دري_MODAL) && !SDL_ObjectValid(والد, SDL_OBJECT_TYPE_دري)) {
        SDL_سيٽ_Error("Modal windows must specify a parent window");
        أرجع عدم;
    }

    إذا ((flags & (SDL_دري_TOOLTIP | SDL_دري_POPUP_MENU)) != 0) {
        إذا (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_دري_SUPPORT)) {
            SDL_Unsupported();
            أرجع عدم;
        }

        // Tooltip and popup menu window must specify a parent window
        إذا (!SDL_ObjectValid(والد, SDL_OBJECT_TYPE_دري)) {
            SDL_سيٽ_Error("Tooltip and popup menu windows must specify a parent window");
            أرجع عدم;
        }

        // Remove invalid flags
        flags &= ~(SDL_دري_MINIMIZED | SDL_دري_MAXIMIZED | SDL_دري_FULLSCREEN | SDL_دري_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_دري_UTILITY | SDL_دري_TOOLTIP | SDL_دري_POPUP_MENU | SDL_دري_MODAL);
    إذا (type_flags & (type_flags - 1)) {
        SDL_سيٽ_Error("Conflicting window type flags specified: 0x%.8x", (بنانشان صحيح)type_flags);
        أرجع عدم;
    }

    // Make sure the display list is up to date for window placement
    إذا (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    إذا (w < 1) {
        w = 1;
    }
    إذا (h < 1) {
        h = 1;
    }

    إذا (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        إذا ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وإلا إذا ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        إذا (displayID == 0 || SDL_Get_Display_اشاريو(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        إذا (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            إذا (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            إذا (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_دري_OPENGL | SDL_دري_METAL | SDL_دري_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        SDL_سيٽ_Error("Conflicting window graphics flags specified: 0x%.8x", (بنانشان صحيح)graphics_flags);
        أرجع عدم;
    }

    // Some platforms have certain graphics backends enabled by default
    إذا (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    إذا (flags & SDL_دري_OPENGL) {
        إذا (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            أرجع عدم;
        }
        إذا (!SDL_GL_ڀريو_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_دري_VULKAN) {
        إذا (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            أرجع عدم;
        }
        إذا (!SDL_Vulkan_ڀريو_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_دري_METAL) {
        إذا (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            أرجع عدم;
        }
    }

    دري = (SDL_دري *)SDL_calloc(1, حجم(*دري));
    إذا (!دري) {
        أرجع عدم;
    }
    SDL_سيٽ_Object_Valid(دري, SDL_OBJECT_TYPE_دري, true);
    دري->id = SDL_Get_ايندڙ_Object_ID();
    دري->floating.x = دري->windowed.x = دري->x = x;
    دري->floating.y = دري->windowed.y = دري->y = y;
    دري->floating.w = دري->windowed.w = دري->w = w;
    دري->floating.h = دري->windowed.h = دري->h = h;
    دري->undefined_x = undefined_x;
    دري->undefined_y = undefined_y;
    دري->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_دري(دري);
    إذا (display) {
        SDL_سيٽ_دري_HDRProperties(دري, &display->HDR, false);
    }

    إذا (flags & SDL_دري_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        دري->x = bounds.x;
        دري->y = bounds.y;
        دري->w = bounds.w;
        دري->h = bounds.h;
        دري->pending_flags |= SDL_دري_FULLSCREEN;
        flags |= SDL_دري_FULLSCREEN;
    }

    دري->flags = ((flags & CREATE_FLAGS) | SDL_دري_HIDDEN);
    دري->display_scale = 1.0f;
    دري->opacity = 1.0f;
    دري->ايندڙ = _this->windows;
    دري->is_destroying = false;
    دري->displayID = Get_Display_For_دري(دري);
    دري->external_graphics_context = external_graphics_context;
    دري->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_دري_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    إذا (!_this->سيٽ_دري_Fill_Document) {
        دري->flags &= ~SDL_دري_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    إذا (_this->windows) {
        _this->windows->prev = دري;
    }
    _this->windows = دري;

    // Set the parent before creation.
    SDL_Update_دري_Hierarchy(دري, والد);

    إذا (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, دري, props)) {
        SDL_ڌڪو_Error();
        SDL_Destroy_دري(دري);
        SDL_ڪڍو_Error();
        أرجع عدم;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#إذا !defined(SDL_PLATFORM_WINDOWS)
    إذا (دري->flags & SDL_دري_MINIMIZED) {
        دري->flags &= ~SDL_دري_MINIMIZED;
    }
#جيڪڏهن_پورو

    إذا (title) {
        SDL_سيٽ_دري_Title(دري, title);
    }
    SDL_پڄاڻي_دري_Creation(دري, flags);

    // Make sure window pixel size is up to date
    SDL_Check_دري_Pixel_سائيز_بدليو(دري);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#جيڪڏهن_پورو

    SDL_ClearError();

    أرجع دري;
}

SDL_دري *SDL_Create_دري(ثابت حرف *title, صحيح w, صحيح h, SDL_دري_Flags flags)
{
    SDL_دري *دري;
    SDL_PropertiesID props = SDL_CreateProperties();
    إذا (title && *title) {
        SDL_سيٽ_String_Property(props, SDL_PROP_دري_CREATE_TITLE_STRING, title);
    }
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_ويڪر_عدد, w);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_اوچائي_عدد, h);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_FLAGS_عدد, flags);
    دري = SDL_Create_دري_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع دري;
}

SDL_دري *SDL_Create_Popup_دري(SDL_دري *والد, صحيح وٿي_x, صحيح وٿي_y, صحيح w, صحيح h, SDL_دري_Flags flags)
{
    SDL_دري *دري;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    إذا (!(flags & (SDL_دري_TOOLTIP | SDL_دري_POPUP_MENU))) {
        SDL_سيٽ_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        أرجع عدم;
    }

    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_CREATE_والد_اشارو, والد);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_X_عدد, وٿي_x);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_Y_عدد, وٿي_y);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_ويڪر_عدد, w);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_اوچائي_عدد, h);
    SDL_سيٽ_عدد_Property(props, SDL_PROP_دري_CREATE_FLAGS_عدد, flags);
    دري = SDL_Create_دري_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع دري;
}

ساكن bool SDL_Reconfigure_دري_اندروني(SDL_دري *دري, SDL_دري_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    إذا (!_this->Reconfigure_دري) {
        أرجع false;
    }

    ثابت SDL_دري_Flags graphics_flags = flags & (SDL_دري_OPENGL | SDL_دري_METAL | SDL_دري_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_سيٽ_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_دري_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_دري_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_دري_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (!(دري->flags & SDL_دري_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        إذا (دري->flags & (SDL_دري_OPENGL | SDL_دري_METAL | SDL_دري_VULKAN)) {
            أرجع false;
        }
    } وإلا {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        إذا (!_this->Reconfigure_دري(_this, دري, 0)) {
            أرجع false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        إذا (دري->flags & SDL_دري_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        إذا (دري->flags & SDL_دري_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        دري->flags &= ~(SDL_دري_OPENGL | SDL_دري_METAL | SDL_دري_VULKAN);
    }

    SDL_Destroy_دري_Surface(دري);

    إذا (graphics_flags & SDL_دري_OPENGL) {
        loaded_opengl = SDL_GL_ڀريو_Library(عدم);
        إذا (!loaded_opengl) {
            أرجع false;
        }
    } وإلا إذا (graphics_flags & SDL_دري_VULKAN) {
        loaded_vulkan = SDL_Vulkan_ڀريو_Library(عدم);
        إذا (!loaded_vulkan) {
            أرجع false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    إذا (!_this->Reconfigure_دري(_this, دري, graphics_flags)) {
        إذا (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        إذا (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        أرجع false;
    }

    دري->flags |= graphics_flags;

    أرجع true;
}

bool SDL_Recreate_دري(SDL_دري *دري, SDL_دري_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_ڀريو = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_ڀريو = false;
    SDL_دري_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_دري_OPENGL | SDL_دري_METAL | SDL_دري_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_سيٽ_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_دري_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_دري_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_دري_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (دري->flags & SDL_دري_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_دري_EXTERNAL;
    } وإلا {
        flags &= ~SDL_دري_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    إذا (دري->flags & SDL_دري_MODAL) {
        SDL_سيٽ_دري_Modal(دري, false);
    }

    // Restore video mode, etc.
    إذا (!(دري->flags & SDL_دري_EXTERNAL)) {
        ثابت bool restore_on_show = دري->restore_on_show;
        SDL_Hide_دري(دري);
        دري->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_دري_Surface(دري);

    إذا ((دري->flags & SDL_دري_OPENGL) != (flags & SDL_دري_OPENGL)) {
        إذا (flags & SDL_دري_OPENGL) {
            need_gl_ڀريو = true;
        } وإلا {
            need_gl_unload = true;
        }
    } وإلا إذا (دري->flags & SDL_دري_OPENGL) {
        need_gl_unload = true;
        need_gl_ڀريو = true;
    }

    إذا ((دري->flags & SDL_دري_VULKAN) != (flags & SDL_دري_VULKAN)) {
        إذا (flags & SDL_دري_VULKAN) {
            need_vulkan_ڀريو = true;
        } وإلا {
            need_vulkan_unload = true;
        }
    } وإلا إذا (دري->flags & SDL_دري_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_ڀريو = true;
    }

    إذا (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    إذا (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->Destroy_دري && !(flags & SDL_دري_EXTERNAL)) {
        _this->Destroy_دري(_this, دري);
    }

    إذا (need_gl_ڀريو) {
        إذا (!SDL_GL_ڀريو_Library(عدم)) {
            أرجع false;
        }
        loaded_opengl = true;
    }

    إذا (need_vulkan_ڀريو) {
        إذا (!SDL_Vulkan_ڀريو_Library(عدم)) {
            أرجع false;
        }
        loaded_vulkan = true;
    }

    دري->flags = ((flags & CREATE_FLAGS) | SDL_دري_HIDDEN);
    دري->is_destroying = false;

    إذا (_this->CreateSDLWindow && !(flags & SDL_دري_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        دري->x = دري->windowed.x = دري->floating.x;
        دري->y = دري->windowed.y = دري->floating.y;
        دري->w = دري->windowed.w = دري->floating.w;
        دري->h = دري->windowed.h = دري->floating.h;

        إذا (!_this->CreateSDLWindow(_this, دري, 0)) {
            إذا (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                دري->flags &= ~SDL_دري_OPENGL;
            }
            إذا (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                دري->flags &= ~SDL_دري_VULKAN;
            }
            أرجع false;
        }
    }

    إذا (flags & SDL_دري_EXTERNAL) {
        دري->flags |= SDL_دري_EXTERNAL;
    }

    إذا (_this->سيٽ_دري_Title && دري->title) {
        _this->سيٽ_دري_Title(_this, دري);
    }

    إذا (_this->سيٽ_دري_Icon && دري->icon) {
        _this->سيٽ_دري_Icon(_this, دري, دري->icon);
    }

    إذا (_this->سيٽ_دري_Minimum_سائيز && (دري->min_w || دري->min_h)) {
        _this->سيٽ_دري_Minimum_سائيز(_this, دري);
    }

    إذا (_this->سيٽ_دري_وڌ_کان_وڌ_سائيز && (دري->max_w || دري->max_h)) {
        _this->سيٽ_دري_وڌ_کان_وڌ_سائيز(_this, دري);
    }

    إذا (_this->سيٽ_دري_Aspect_تناسب && (دري->min_aspect > 0.0f || دري->max_aspect > 0.0f)) {
        _this->سيٽ_دري_Aspect_تناسب(_this, دري);
    }

    إذا (دري->ڪاميابي_test) {
        _this->سيٽ_دري_ڪاميابي_Test(دري, true);
    }

    SDL_پڄاڻي_دري_Creation(دري, flags);

    أرجع true;
}

bool SDL_Reconfigure_دري(SDL_دري *دري, SDL_دري_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    إذا (!SDL_Reconfigure_دري_اندروني(دري, flags)) {
        أرجع SDL_Recreate_دري(دري, flags);
    }

    أرجع true;
}

bool SDL_HasWindows(فراغ)
{
    أرجع _this && _this->windows;
}

SDL_دري_ID SDL_Get_دري_ID(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, 0);

    أرجع دري->id;
}

SDL_دري *SDL_Get_دري_From_ID(SDL_دري_ID id)
{
    SDL_دري *دري;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (id) {
        لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
            إذا (دري->id == id) {
                أرجع دري;
            }
        }
    }
    SDL_سيٽ_Error("Invalid window ID");
    أرجع عدم;
}

SDL_دري *SDL_Get_دري_والد(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, عدم);

    أرجع دري->والد;
}

SDL_PropertiesID SDL_Get_دري_Properties(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, 0);

    إذا (دري->props == 0) {
        دري->props = SDL_CreateProperties();
    }
    أرجع دري->props;
}

SDL_دري_Flags SDL_Get_دري_Flags(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, 0);

    أرجع دري->flags | دري->pending_flags;
}

bool SDL_سيٽ_دري_Title(SDL_دري *دري, ثابت حرف *title)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (title == دري->title) {
        أرجع true;
    }
    إذا (!title) {
        title = "";
    }
    إذا (دري->title && SDL_strcmp(title, دري->title) == 0) {
        أرجع true;
    }

    SDL_free(دري->title);

    دري->title = SDL_strdup(title);

    إذا (_this->سيٽ_دري_Title) {
        _this->سيٽ_دري_Title(_this, دري);
    }
    أرجع true;
}

ثابت حرف *SDL_Get_دري_Title(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, "");

    أرجع دري->title ? دري->title : "";
}

bool SDL_سيٽ_دري_Icon(SDL_دري *دري, SDL_Surface *icon)
{
    CHECK_دري_MAGIC(دري, false);

    CHECK_PARAM(!icon) {
        أرجع SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(دري->icon);

    // Convert the icon into ARGB8888
    دري->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    إذا (!دري->icon) {
        أرجع false;
    }

    إذا (!_this->سيٽ_دري_Icon) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->سيٽ_دري_Icon(_this, دري, دري->icon);
}

bool SDL_سيٽ_دري_Position(SDL_دري *دري, صحيح x, صحيح y)
{
    SDL_DisplayID original_displayID;

    CHECK_دري_MAGIC(دري, false);

    ثابت صحيح w = دري->آخري_سائيز_pending ? دري->pending.w : دري->windowed.w;
    ثابت صحيح h = دري->آخري_سائيز_pending ? دري->pending.h : دري->windowed.h;

    original_displayID = Get_Display_For_دري(دري);
    دري->pending_displayID = 0;

    إذا (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = دري->windowed.x;
    }
    إذا (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = دري->windowed.y;
    }
    إذا (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        إذا (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وإلا إذا (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        إذا (displayID == 0 || SDL_Get_Display_اشاريو(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        دري->pending_displayID = displayID;

        SDL_zero(bounds);
        إذا (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            إذا (!SDL_GetDisplayBounds(displayID, &bounds)) {
                أرجع false;
            }
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        إذا (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } وإلا {
        /* See if the requested window position matches the origin of any displays and set
         * the pending fullscreen display ID if it does. This needs to be set early in case
         * the window is prevented from moving to the exact origin due to struts.
         */
        دري->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    دري->pending.x = x;
    دري->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    إذا (!_this->Sync_دري && (دري->flags & SDL_دري_FULLSCREEN)) {
        دري->floating.x = دري->windowed.x = x;
        دري->floating.y = دري->windowed.y = y;
    }
    دري->undefined_x = false;
    دري->undefined_y = false;
    دري->آخري_position_pending = true;

    إذا (_this->سيٽ_دري_Position) {
        ثابت bool نتيجو = _this->سيٽ_دري_Position(_this, دري);
        إذا (نتيجو) {
            SDL_SyncIfRequired(دري);
        }
        أرجع نتيجو;
    }

    أرجع SDL_Unsupported();
}

bool SDL_Get_دري_Position(SDL_دري *دري, صحيح *x, صحيح *y)
{
    CHECK_دري_MAGIC(دري, false);

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#وإلا
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((دري->flags & SDL_دري_FULLSCREEN) != 0);
#جيڪڏهن_پورو
    إذا (use_display_origin) {
        SDL_DisplayID displayID;

        إذا (x) {
            *x = 0;
        }
        إذا (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = Get_Display_For_دري(دري);
        إذا (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            إذا (x) {
                *x = bounds.x;
            }
            إذا (y) {
                *y = bounds.y;
            }
        }
    } وإلا {
        ثابت bool use_pending = (دري->flags & SDL_دري_HIDDEN) && دري->آخري_position_pending;
        إذا (x) {
            *x = use_pending ? دري->pending.x : دري->x;
        }
        إذا (y) {
            *y = use_pending ? دري->pending.y : دري->y;
        }
    }
    أرجع true;
}

bool SDL_سيٽ_دري_Bordered(SDL_دري *دري, bool bordered)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (!_this->سيٽ_دري_Bordered) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(دري->flags & SDL_دري_BORDERLESS);
    إذا (want != have) {
        إذا (want) {
            دري->flags &= ~SDL_دري_BORDERLESS;
        } وإلا {
            دري->flags |= SDL_دري_BORDERLESS;
        }
        _this->سيٽ_دري_Bordered(_this, دري, want);
    }

    أرجع true;
}

bool SDL_سيٽ_دري_Resizable(SDL_دري *دري, bool resizable)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (!_this->سيٽ_دري_Resizable) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((دري->flags & SDL_دري_RESIZABLE) != 0);
    إذا (want != have) {
        إذا (want) {
            دري->flags |= SDL_دري_RESIZABLE;
        } وإلا {
            دري->flags &= ~SDL_دري_RESIZABLE;
            SDL_copyp(&دري->windowed, &دري->floating);
        }
        _this->سيٽ_دري_Resizable(_this, دري, want);
    }

    أرجع true;
}

bool SDL_سيٽ_دري_Always_On_چوٽي(SDL_دري *دري, bool on_چوٽي)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (!_this->سيٽ_دري_Always_On_چوٽي) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = on_چوٽي;
    ثابت bool have = ((دري->flags & SDL_دري_ALWAYS_ON_چوٽي) != 0);
    إذا (want != have) {
        إذا (want) {
            دري->flags |= SDL_دري_ALWAYS_ON_چوٽي;
        } وإلا {
            دري->flags &= ~SDL_دري_ALWAYS_ON_چوٽي;
        }
        _this->سيٽ_دري_Always_On_چوٽي(_this, دري, want);
    }

    أرجع true;
}

bool SDL_سيٽ_دري_سائيز(SDL_دري *دري, صحيح w, صحيح h)
{
    CHECK_دري_MAGIC(دري, false);

    CHECK_PARAM(w <= 0) {
        أرجع SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        أرجع SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    عائم new_aspect = w / (عائم)h;
    إذا (دري->max_aspect > 0.0f && new_aspect > دري->max_aspect) {
        w = (صحيح)SDL_roundf(h * دري->max_aspect);
    } وإلا إذا (دري->min_aspect > 0.0f && new_aspect < دري->min_aspect) {
        h = (صحيح)SDL_roundf(w / دري->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    إذا (دري->min_w && w < دري->min_w) {
        w = دري->min_w;
    }
    إذا (دري->max_w && w > دري->max_w) {
        w = دري->max_w;
    }
    إذا (دري->min_h && h < دري->min_h) {
        h = دري->min_h;
    }
    إذا (دري->max_h && h > دري->max_h) {
        h = دري->max_h;
    }

    دري->آخري_سائيز_pending = true;
    دري->pending.w = w;
    دري->pending.h = h;

    إذا (_this->سيٽ_دري_سائيز) {
        _this->سيٽ_دري_سائيز(_this, دري);
        SDL_SyncIfRequired(دري);
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

bool SDL_Get_دري_سائيز(SDL_دري *دري, صحيح *w, صحيح *h)
{
    CHECK_دري_MAGIC(دري, false);
    إذا (w) {
        *w = دري->w;
    }
    إذا (h) {
        *h = دري->h;
    }
    أرجع true;
}

bool SDL_سيٽ_دري_Aspect_تناسب(SDL_دري *دري, عائم min_aspect, عائم max_aspect)
{
    CHECK_دري_MAGIC(دري, false);

    دري->min_aspect = min_aspect;
    دري->max_aspect = max_aspect;

    إذا (_this->سيٽ_دري_Aspect_تناسب) {
        _this->سيٽ_دري_Aspect_تناسب(_this, دري);
    }

    // Ensure that window has the correct aspect ratio
    صحيح w = دري->آخري_سائيز_pending ? دري->pending.w : دري->floating.w;
    صحيح h = دري->آخري_سائيز_pending ? دري->pending.h : دري->floating.h;
    أرجع SDL_سيٽ_دري_سائيز(دري, w, h);
}

bool SDL_Get_دري_Aspect_تناسب(SDL_دري *دري, عائم *min_aspect, عائم *max_aspect)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (min_aspect) {
        *min_aspect = دري->min_aspect;
    }
    إذا (max_aspect) {
        *max_aspect = دري->max_aspect;
    }
    أرجع true;
}

bool SDL_Get_دري_Borders_سائيز(SDL_دري *دري, صحيح *چوٽي, صحيح *کاٻو, صحيح *bottom, صحيح *ساڄو)
{
    صحيح dummy = 0;

    إذا (!چوٽي) {
        چوٽي = &dummy;
    }
    إذا (!کاٻو) {
        کاٻو = &dummy;
    }
    إذا (!ساڄو) {
        ساڄو = &dummy;
    }
    إذا (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *چوٽي = *کاٻو = *bottom = *ساڄو = 0;

    CHECK_دري_MAGIC(دري, false);

    إذا (!_this->Get_دري_Borders_سائيز) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->Get_دري_Borders_سائيز(_this, دري, چوٽي, کاٻو, bottom, ساڄو);
}

bool SDL_Get_دري_سائيز_اندريون_Pixels(SDL_دري *دري, صحيح *w, صحيح *h)
{
    صحيح filter;

    CHECK_دري_MAGIC(دري, false);

    إذا (!w) {
        w = &filter;
    }

    إذا (!h) {
        h = &filter;
    }

    إذا (_this->Get_دري_سائيز_اندريون_Pixels) {
        _this->Get_دري_سائيز_اندريون_Pixels(_this, دري, w, h);
    } وإلا {
        SDL_DisplayID displayID = Get_Display_For_دري(دري);
        ثابت SDL_Display_گهڻائي *گهڻائي;

        SDL_Get_دري_سائيز(دري, w, h);

        إذا ((دري->flags & SDL_دري_FULLSCREEN) && SDL_Get_دري_Fullscreen_گهڻائي(دري)) {
            گهڻائي = SDL_Get_Current_Display_گهڻائي(displayID);
        } وإلا {
            گهڻائي = SDL_Get_Desktop_Display_گهڻائي(displayID);
        }
        إذا (گهڻائي) {
            *w = (صحيح)SDL_ceilf(*w * گهڻائي->pixel_density);
            *h = (صحيح)SDL_ceilf(*h * گهڻائي->pixel_density);
        }
    }
    أرجع true;
}

bool SDL_سيٽ_دري_Minimum_سائيز(SDL_دري *دري, صحيح min_w, صحيح min_h)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_PARAM(min_w < 0) {
        أرجع SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        أرجع SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((دري->max_w && min_w > دري->max_w) || (دري->max_h && min_h > دري->max_h)) {
        أرجع SDL_سيٽ_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    دري->min_w = min_w;
    دري->min_h = min_h;

    إذا (_this->سيٽ_دري_Minimum_سائيز) {
        _this->سيٽ_دري_Minimum_سائيز(_this, دري);
    }

    // Ensure that window is not smaller than minimal size
    صحيح w = دري->آخري_سائيز_pending ? دري->pending.w : دري->floating.w;
    صحيح h = دري->آخري_سائيز_pending ? دري->pending.h : دري->floating.h;
    أرجع SDL_سيٽ_دري_سائيز(دري, w, h);
}

bool SDL_Get_دري_Minimum_سائيز(SDL_دري *دري, صحيح *min_w, صحيح *min_h)
{
    CHECK_دري_MAGIC(دري, false);
    إذا (min_w) {
        *min_w = دري->min_w;
    }
    إذا (min_h) {
        *min_h = دري->min_h;
    }
    أرجع true;
}

bool SDL_سيٽ_دري_وڌ_کان_وڌ_سائيز(SDL_دري *دري, صحيح max_w, صحيح max_h)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_PARAM(max_w < 0) {
        أرجع SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        أرجع SDL_InvalidParamError("max_h");
    }

    إذا ((max_w && max_w < دري->min_w) ||
        (max_h && max_h < دري->min_h)) {
        أرجع SDL_سيٽ_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    دري->max_w = max_w;
    دري->max_h = max_h;

    إذا (_this->سيٽ_دري_وڌ_کان_وڌ_سائيز) {
        _this->سيٽ_دري_وڌ_کان_وڌ_سائيز(_this, دري);
    }

    // Ensure that window is not larger than maximal size
    صحيح w = دري->آخري_سائيز_pending ? دري->pending.w : دري->floating.w;
    صحيح h = دري->آخري_سائيز_pending ? دري->pending.h : دري->floating.h;
    أرجع SDL_سيٽ_دري_سائيز(دري, w, h);
}

bool SDL_Get_دري_وڌ_کان_وڌ_سائيز(SDL_دري *دري, صحيح *max_w, صحيح *max_h)
{
    CHECK_دري_MAGIC(دري, false);
    إذا (max_w) {
        *max_w = دري->max_w;
    }
    إذا (max_h) {
        *max_h = دري->max_h;
    }
    أرجع true;
}

bool SDL_Show_دري(SDL_دري *دري)
{
    SDL_دري *ٻار;
    CHECK_دري_MAGIC(دري, false);

    إذا (!(دري->flags & SDL_دري_HIDDEN)) {
        أرجع true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    إذا (دري->والد && (دري->والد->flags & SDL_دري_HIDDEN)) {
        دري->restore_on_show = true;
        أرجع true;
    }

    إذا (_this->Show_دري) {
        _this->Show_دري(_this, دري);
    } وإلا {
        SDL_سيٽ_Mouse_Focus(دري);
        SDL_سيٽ_Keyboard_Focus(دري);
    }
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_SHOWN, 0, 0);

    // Restore child windows
    لكل (ٻار = دري->پهريون_ٻار; ٻار; ٻار = ٻار->ايندڙ_sibling) {
        إذا (!ٻار->restore_on_show && (ٻار->flags & SDL_دري_HIDDEN)) {
            اكسر;
        }
        SDL_Show_دري(ٻار);
        ٻار->restore_on_show = false;
    }
    أرجع true;
}

bool SDL_Hide_دري(SDL_دري *دري)
{
    SDL_دري *ٻار;
    CHECK_دري_MAGIC(دري, false);

    إذا (دري->flags & SDL_دري_HIDDEN) {
        دري->restore_on_show = false;
        أرجع true;
    }

    // Hide all child windows
    لكل (ٻار = دري->پهريون_ٻار; ٻار; ٻار = ٻار->ايندڙ_sibling) {
        إذا (ٻار->flags & SDL_دري_HIDDEN) {
            اكسر;
        }
        SDL_Hide_دري(ٻار);
        ٻار->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_دري_Flags pending_نقاب = (SDL_دري_MAXIMIZED | SDL_دري_MINIMIZED | SDL_دري_FULLSCREEN | SDL_دري_KEYBOARD_GRABBED | SDL_دري_MOUSE_GRABBED);
    دري->pending_flags = (دري->flags & pending_نقاب);

    دري->is_hiding = true;
    إذا (_this->Hide_دري) {
        _this->Hide_دري(_this, دري);
    } وإلا {
        SDL_سيٽ_Mouse_Focus(عدم);
        SDL_سيٽ_Keyboard_Focus(عدم);
    }
    دري->is_hiding = false;
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_HIDDEN, 0, 0);
    أرجع true;
}

bool SDL_Raise_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (دري->flags & SDL_دري_HIDDEN) {
        أرجع true;
    }
    إذا (_this->Raise_دري) {
        _this->Raise_دري(_this, دري);
    }
    أرجع true;
}

bool SDL_Maximize_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (!_this->Maximize_دري) {
        أرجع SDL_Unsupported();
    }

    إذا (!(دري->flags & SDL_دري_RESIZABLE)) {
        أرجع SDL_سيٽ_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    إذا (دري->flags & SDL_دري_HIDDEN) {
        دري->pending_flags |= SDL_دري_MAXIMIZED;
        أرجع true;
    }

    _this->Maximize_دري(_this, دري);
    SDL_SyncIfRequired(دري);
    أرجع true;
}

bool SDL_Minimize_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (!_this->Minimize_دري) {
        أرجع SDL_Unsupported();
    }

    إذا (دري->flags & SDL_دري_HIDDEN) {
        دري->pending_flags |= SDL_دري_MINIMIZED;
        أرجع true;
    }

    _this->Minimize_دري(_this, دري);
    SDL_SyncIfRequired(دري);
    أرجع true;
}

bool SDL_Restore_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (!_this->Restore_دري) {
        أرجع SDL_Unsupported();
    }

    إذا (دري->flags & SDL_دري_HIDDEN) {
        دري->pending_flags &= ~(SDL_دري_MAXIMIZED | SDL_دري_MINIMIZED);
        أرجع true;
    }

    _this->Restore_دري(_this, دري);
    SDL_SyncIfRequired(دري);
    أرجع true;
}

bool SDL_سيٽ_دري_Fullscreen(SDL_دري *دري, bool fullscreen)
{
    bool نتيجو;

    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (دري->flags & SDL_دري_HIDDEN) {
        إذا (fullscreen) {
            دري->pending_flags |= SDL_دري_FULLSCREEN;
        } وإلا {
            دري->pending_flags &= ~SDL_دري_FULLSCREEN;
        }
        أرجع true;
    }

    إذا (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&دري->current_fullscreen_گهڻائي, &دري->requested_fullscreen_گهڻائي);
    }

    نتيجو = SDL_Update_Fullscreen_گهڻائي(دري, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    إذا (!fullscreen || !نتيجو) {
        // Clear the current fullscreen mode.
        SDL_zero(دري->current_fullscreen_گهڻائي);
    }

    إذا (نتيجو) {
        SDL_SyncIfRequired(دري);
    }

    أرجع نتيجو;
}

bool SDL_Sync_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (_this->Sync_دري) {
        أرجع _this->Sync_دري(_this, دري);
    } وإلا {
        أرجع true;
    }
}

ساكن bool ShouldAttemptTextureFramebuffer(فراغ)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    إذا (!_this->Create_دري_Framebuffer) {
        أرجع true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    إذا (hint && *hint) {
        إذا (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } وإلا {
            attempt_texture_framebuffer = true;
        }
    } وإلا {
        إذا (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } وإلا {
            attempt_texture_framebuffer = false;
        }
    }
    أرجع attempt_texture_framebuffer;
}

ساكن SDL_Surface *SDL_Create_دري_Framebuffer(SDL_دري *دري)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    فراغ *pixels = عدم;
    صحيح pitch = 0;
    bool created_framebuffer = false;
    صحيح w, h;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    إذا (!_this->checked_texture_framebuffer) {
        إذا (ShouldAttemptTextureFramebuffer()) {
            إذا (!SDL_Create_دري_Texture(_this, دري, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } وإلا {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_دري_Framebuffer = SDL_Create_دري_Texture;
                _this->سيٽ_دري_Framebuffer_VSync = SDL_سيٽ_دري_Texture_VSync;
                _this->Get_دري_Framebuffer_VSync = SDL_Get_دري_Texture_VSync;
                _this->Update_دري_Framebuffer = SDL_Update_دري_Texture;
                _this->Destroy_دري_Framebuffer = SDL_Destroy_دري_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    إذا (!created_framebuffer) {
        إذا (!_this->Create_دري_Framebuffer || !_this->Update_دري_Framebuffer) {
            SDL_سيٽ_Error("Window framebuffer support not available");
            أرجع عدم;
        }

        إذا (!_this->Create_دري_Framebuffer(_this, دري, &format, &pixels, &pitch)) {
            أرجع عدم;
        }
    }

    إذا (دري->surface) {
        // We may have gone recursive and already created the surface
        أرجع دري->surface;
    }

    أرجع SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_دري_Has_Surface(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    أرجع دري->surface ? true : false;
}

SDL_Surface *SDL_Get_دري_Surface(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, عدم);

    إذا (!دري->surface_valid) {
        إذا (دري->surface) {
            دري->surface->اندروني_flags &= ~SDL_اندروني_SURFACE_DONTFREE;
            SDL_DestroySurface(دري->surface);
            دري->surface = عدم;
        }

        دري->surface = SDL_Create_دري_Framebuffer(دري);
        إذا (دري->surface) {
            دري->surface_valid = true;
            دري->surface->اندروني_flags |= SDL_اندروني_SURFACE_DONTFREE;
        }
    }
    أرجع دري->surface;
}

bool SDL_سيٽ_دري_Surface_VSync(SDL_دري *دري, صحيح vsync)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (!_this->سيٽ_دري_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->سيٽ_دري_Framebuffer_VSync(_this, دري, vsync);
}

bool SDL_Get_دري_Surface_VSync(SDL_دري *دري, صحيح *vsync)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (!_this->Get_دري_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->Get_دري_Framebuffer_VSync(_this, دري, vsync);
}

bool SDL_Update_دري_Surface(SDL_دري *دري)
{
    SDL_Rect ڀريل_rect;

    CHECK_دري_MAGIC(دري, false);

    ڀريل_rect.x = 0;
    ڀريل_rect.y = 0;
    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &ڀريل_rect.w, &ڀريل_rect.h);

    أرجع SDL_Update_دري_Surface_Rects(دري, &ڀريل_rect, 1);
}

bool SDL_Update_دري_Surface_Rects(SDL_دري *دري, ثابت SDL_Rect *rects,
                                 صحيح numrects)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (!دري->surface_valid) {
        أرجع SDL_سيٽ_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    أرجع _this->Update_دري_Framebuffer(_this, دري, rects, numrects);
}

bool SDL_Destroy_دري_Surface(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (دري->surface) {
        دري->surface->اندروني_flags &= ~SDL_اندروني_SURFACE_DONTFREE;
        SDL_DestroySurface(دري->surface);
        دري->surface = عدم;
        دري->surface_valid = false;
    }

    إذا (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        إذا (_this->Destroy_دري_Framebuffer) {
            _this->Destroy_دري_Framebuffer(_this, دري);
        }
    }
    أرجع true;
}

bool SDL_سيٽ_دري_Opacity(SDL_دري *دري, عائم opacity)
{
    bool نتيجو;

    CHECK_دري_MAGIC(دري, false);

    إذا (!_this->سيٽ_دري_Opacity) {
        أرجع SDL_Unsupported();
    }

    إذا (opacity < 0.0f) {
        opacity = 0.0f;
    } وإلا إذا (opacity > 1.0f) {
        opacity = 1.0f;
    }

    نتيجو = _this->سيٽ_دري_Opacity(_this, دري, opacity);
    إذا (نتيجو) {
        دري->opacity = opacity;
    }

    أرجع نتيجو;
}

عائم SDL_Get_دري_Opacity(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, -1.0f);

    أرجع دري->opacity;
}

bool SDL_سيٽ_دري_والد(SDL_دري *دري, SDL_دري *والد)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (والد) {
        CHECK_دري_MAGIC(والد, false);
        CHECK_دري_NOT_POPUP(والد, false);
    }

    إذا (دري == والد) {
        أرجع SDL_سيٽ_Error("Cannot set the parent of a window to itself.");
    }

    إذا (!_this->سيٽ_دري_والد) {
        أرجع SDL_Unsupported();
    }

    إذا (دري->flags & SDL_دري_MODAL) {
        أرجع SDL_سيٽ_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    إذا (دري->والد == والد) {
        أرجع true;
    }

    ثابت bool ret = _this->سيٽ_دري_والد(_this, دري, والد);
    SDL_Update_دري_Hierarchy(دري, ret ? والد : عدم);

    أرجع ret;
}

bool SDL_سيٽ_دري_Modal(SDL_دري *دري, bool modal)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (!_this->سيٽ_دري_Modal) {
        أرجع SDL_Unsupported();
    }

    إذا (modal) {
        إذا (!دري->والد) {
            أرجع SDL_سيٽ_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        دري->flags |= SDL_دري_MODAL;
    } وإلا إذا (دري->flags & SDL_دري_MODAL) {
        دري->flags &= ~SDL_دري_MODAL;
    } وإلا {
        أرجع true; // Already not modal, so nothing to do.
    }

    إذا (دري->flags & SDL_دري_HIDDEN) {
        أرجع true;
    }

    أرجع _this->سيٽ_دري_Modal(_this, دري, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_دري *دري, SDL_دري **new_focus)
{
    SDL_دري *focus = دري->والد;
    bool سيٽ_focus = !!(دري->flags & SDL_دري_داخلا_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    طالما (SDL_دري_IS_POPUP(focus) && ((focus->flags & SDL_دري_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->والد;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        إذا (!سيٽ_focus) {
            سيٽ_focus = !!(focus->flags & SDL_دري_داخلا_FOCUS);
        }
    }

    *new_focus = focus;
    أرجع سيٽ_focus;
}

bool SDL_ShouldFocusPopup(SDL_دري *دري)
{
    SDL_دري *toplevel_والد;
    لكل (toplevel_والد = دري->والد; SDL_دري_IS_POPUP(toplevel_والد); toplevel_والد = toplevel_والد->والد) {
    }

    SDL_دري *current_focus = toplevel_والد->keyboard_focus;
    bool مليو_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_دري *w;
    لكل (w = current_focus; w != toplevel_والد; w = w->والد) {
        إذا (w == دري) {
            مليو_higher_focus = true;
            اكسر;
        }
    }

    أرجع !مليو_higher_focus || w == toplevel_والد;
}

bool SDL_سيٽ_دري_Focusable(SDL_دري *دري, bool focusable)
{
    CHECK_دري_MAGIC(دري, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(دري->flags & SDL_دري_NOT_FOCUSABLE);
    إذا ((want != have) && (_this->سيٽ_دري_Focusable)) {
        إذا (want) {
            دري->flags &= ~SDL_دري_NOT_FOCUSABLE;
        } وإلا {
            دري->flags |= SDL_دري_NOT_FOCUSABLE;
        }
        إذا (!_this->سيٽ_دري_Focusable(_this, دري, want)) {
            أرجع false;
        }
    }

    أرجع true;
}

bool SDL_سيٽ_دري_Fill_Document(SDL_دري *دري, bool fill)
{
    CHECK_دري_MAGIC(دري, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((دري->flags & SDL_دري_FILL_DOCUMENT) != 0);
    إذا ((want != have) && (_this->سيٽ_دري_Fill_Document)) {
        إذا (!_this->سيٽ_دري_Fill_Document(_this, دري, want)) {
            أرجع false;
        } وإلا إذا (want) {
            دري->flags |= SDL_دري_FILL_DOCUMENT;
        } وإلا {
            دري->flags &= ~SDL_دري_FILL_DOCUMENT;
        }
    }

    أرجع true;
}

فراغ SDL_Update_دري_Grab(SDL_دري *دري)
{
    bool keyboard_grabbed, mouse_grabbed;

    إذا (دري->flags & SDL_دري_داخلا_FOCUS) {
        إذا (SDL_GetMouse()->relative_گهڻائي || (دري->flags & SDL_دري_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } وإلا {
            mouse_grabbed = false;
        }

        إذا (دري->flags & SDL_دري_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } وإلا {
            keyboard_grabbed = false;
        }
    } وإلا {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    إذا (mouse_grabbed || keyboard_grabbed) {
        إذا (_this->grabbed_دري && (_this->grabbed_دري != دري)) {
            // stealing a grab from another window!
            _this->grabbed_دري->flags &= ~(SDL_دري_MOUSE_GRABBED | SDL_دري_KEYBOARD_GRABBED);
            إذا (_this->سيٽ_دري_Mouse_Grab) {
                _this->سيٽ_دري_Mouse_Grab(_this, _this->grabbed_دري, false);
            }
            إذا (_this->سيٽ_دري_Keyboard_Grab) {
                _this->سيٽ_دري_Keyboard_Grab(_this, _this->grabbed_دري, false);
            }
        }
        _this->grabbed_دري = دري;
    } وإلا إذا (_this->grabbed_دري == دري) {
        _this->grabbed_دري = عدم; // ungrabbing input.
    }

    إذا (_this->سيٽ_دري_Mouse_Grab) {
        إذا (!_this->سيٽ_دري_Mouse_Grab(_this, دري, mouse_grabbed)) {
            دري->flags &= ~SDL_دري_MOUSE_GRABBED;
        }
    }
    إذا (_this->سيٽ_دري_Keyboard_Grab) {
        إذا (!_this->سيٽ_دري_Keyboard_Grab(_this, دري, keyboard_grabbed)) {
            دري->flags &= ~SDL_دري_KEYBOARD_GRABBED;
        }
    }

    إذا (_this->grabbed_دري && !(_this->grabbed_دري->flags & (SDL_دري_MOUSE_GRABBED | SDL_دري_KEYBOARD_GRABBED))) {
        _this->grabbed_دري = عدم;
    }
}

bool SDL_سيٽ_دري_Keyboard_Grab(SDL_دري *دري, bool grabbed)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (دري->flags & SDL_دري_HIDDEN) {
        إذا (grabbed) {
            دري->pending_flags |= SDL_دري_KEYBOARD_GRABBED;
        } وإلا {
            دري->pending_flags &= ~SDL_دري_KEYBOARD_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(دري->flags & SDL_دري_KEYBOARD_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        دري->flags |= SDL_دري_KEYBOARD_GRABBED;
    } وإلا {
        دري->flags &= ~SDL_دري_KEYBOARD_GRABBED;
    }
    SDL_Update_دري_Grab(دري);

    إذا (grabbed && !(دري->flags & SDL_دري_KEYBOARD_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_سيٽ_دري_Mouse_Grab(SDL_دري *دري, bool grabbed)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (دري->flags & SDL_دري_HIDDEN) {
        إذا (grabbed) {
            دري->pending_flags |= SDL_دري_MOUSE_GRABBED;
        } وإلا {
            دري->pending_flags &= ~SDL_دري_MOUSE_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(دري->flags & SDL_دري_MOUSE_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        دري->flags |= SDL_دري_MOUSE_GRABBED;
    } وإلا {
        دري->flags &= ~SDL_دري_MOUSE_GRABBED;
    }
    SDL_Update_دري_Grab(دري);

    إذا (grabbed && !(دري->flags & SDL_دري_MOUSE_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_دري_Keyboard_Grab(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);
    أرجع دري == _this->grabbed_دري && (_this->grabbed_دري->flags & SDL_دري_KEYBOARD_GRABBED);
}

bool SDL_Get_دري_Mouse_Grab(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);
    أرجع دري == _this->grabbed_دري && (_this->grabbed_دري->flags & SDL_دري_MOUSE_GRABBED);
}

SDL_دري *SDL_Get_Grabbed_دري(فراغ)
{
    إذا (_this && _this->grabbed_دري &&
        (_this->grabbed_دري->flags & (SDL_دري_MOUSE_GRABBED | SDL_دري_KEYBOARD_GRABBED)) != 0) {
        أرجع _this->grabbed_دري;
    } وإلا {
        أرجع عدم;
    }
}

bool SDL_سيٽ_دري_Mouse_Rect(SDL_دري *دري, ثابت SDL_Rect *rect)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (!_this->سيٽ_دري_Mouse_Rect) {
        أرجع SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    إذا (!rect) {
        rect = &zero;
    }

    إذا (SDL_memcmp(&دري->mouse_rect, rect, حجم(*rect)) == 0) {
        أرجع true;
    }
    SDL_memcpy(&دري->mouse_rect, rect, حجم(*rect));

    أرجع _this->سيٽ_دري_Mouse_Rect(_this, دري);
}

ثابت SDL_Rect *SDL_Get_دري_Mouse_Rect(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, عدم);

    إذا (SDL_Rect_خالي_جايون(&دري->mouse_rect)) {
        أرجع عدم;
    } وإلا {
        أرجع &دري->mouse_rect;
    }
}

bool SDL_سيٽ_دري_Relative_Mouse_گهڻائي(SDL_دري *دري, bool enabled)
{
    CHECK_دري_MAGIC(دري, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    إذا (enabled == SDL_Get_دري_Relative_Mouse_گهڻائي(دري)) {
        أرجع true;
    }

    إذا (enabled) {
        دري->flags |= SDL_دري_MOUSE_RELATIVE_گهڻائي;
    } وإلا {
        دري->flags &= ~SDL_دري_MOUSE_RELATIVE_گهڻائي;
    }

    إذا (!SDL_Update_Relative_Mouse_گهڻائي()) {
        إذا (enabled) {
            دري->flags &= ~SDL_دري_MOUSE_RELATIVE_گهڻائي;
        } وإلا {
            دري->flags |= SDL_دري_MOUSE_RELATIVE_گهڻائي;
        }
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_دري_Relative_Mouse_گهڻائي(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (دري->flags & SDL_دري_MOUSE_RELATIVE_گهڻائي) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

bool SDL_Flash_دري(SDL_دري *دري, SDL_FlashOperation operation)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (_this->Flash_دري) {
        أرجع _this->Flash_دري(_this, دري, operation);
    }

    أرجع SDL_Unsupported();
}

bool SDL_سيٽ_دري_ترقي_State(SDL_دري *دري, SDL_ترقي_State state)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    CHECK_PARAM(state < SDL_ترقي_STATE_NONE || state > SDL_ترقي_STATE_ERROR) {
        أرجع SDL_InvalidParamError("state");
    }

    دري->ترقي_state = state;

    إذا (_this->Apply_دري_ترقي) {
        إذا (!_this->Apply_دري_ترقي(_this, دري)) {
            أرجع false;
        }
    }

    أرجع true;
}

SDL_ترقي_State SDL_Get_دري_ترقي_State(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, SDL_ترقي_STATE_INVALID);
    CHECK_دري_NOT_POPUP(دري, SDL_ترقي_STATE_INVALID);

    أرجع دري->ترقي_state;
}

bool SDL_سيٽ_دري_ترقي_قدر(SDL_دري *دري, عائم قدر)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    قدر = SDL_clamp(قدر, 0.0f, 1.f);

    دري->ترقي_قدر = قدر;

    إذا (_this->Apply_دري_ترقي) {
        إذا (!_this->Apply_دري_ترقي(_this, دري)) {
            أرجع false;
        }
    }

    أرجع true;
}

عائم SDL_Get_دري_ترقي_قدر(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, -1.0f);
    CHECK_دري_NOT_POPUP(دري, -1.0f);

    أرجع دري->ترقي_قدر;
}

فراغ SDL_On_دري_Shown(SDL_دري *دري)
{
    // Set window state if we have pending window flags cached
    Apply_دري_Flags(دري, دري->pending_flags);
    دري->pending_flags = 0;
}

فراغ SDL_On_دري_Hidden(SDL_دري *دري)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    دري->pending_flags |= (دري->flags & (SDL_دري_FULLSCREEN | SDL_دري_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_LEAVE, false);
}

فراغ SDL_On_دري_Display_بدليو(SDL_دري *دري)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    إذا (دري->update_fullscreen_on_display_بدليو && (دري->flags & SDL_دري_FULLSCREEN)) {
        ثابت bool auto_گهڻائي_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_ميلاپ_EXCLUSIVE_گهڻائي_ON_MOVE, true);

        إذا (auto_گهڻائي_switch && (دري->requested_fullscreen_گهڻائي.w != 0 || دري->requested_fullscreen_گهڻائي.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_دري_Position(دري);
            bool include_مٿاهون_density_modes = false;

            إذا (دري->requested_fullscreen_گهڻائي.pixel_density > 1.0f) {
                include_مٿاهون_density_modes = true;
            }
            ثابت bool مليو_ميلاپ = SDL_Get_Closest_Fullscreen_Display_گهڻائي(displayID, دري->requested_fullscreen_گهڻائي.w, دري->requested_fullscreen_گهڻائي.h,
                                                                         دري->requested_fullscreen_گهڻائي.refresh_شرح, include_مٿاهون_density_modes, &دري->current_fullscreen_گهڻائي);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            إذا (!مليو_ميلاپ ||
                دري->requested_fullscreen_گهڻائي.w != دري->current_fullscreen_گهڻائي.w ||
                دري->requested_fullscreen_گهڻائي.h != دري->current_fullscreen_گهڻائي.h) {
                SDL_zero(دري->current_fullscreen_گهڻائي);
            }
        } وإلا {
            SDL_zero(دري->current_fullscreen_گهڻائي);
        }

        إذا (SDL_دري_FULLSCREEN_VISIBLE(دري)) {
            SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_دري_Pixel_سائيز_بدليو(دري);
}

فراغ SDL_On_دري_Moved(SDL_دري *دري)
{
    SDL_Check_دري_Display_بدليو(دري);
}

فراغ SDL_On_دري_Resized(SDL_دري *دري)
{
    SDL_Check_دري_Display_بدليو(دري);
    SDL_Check_دري_Pixel_سائيز_بدليو(دري);
    SDL_Check_دري_محفوظ_Area_بدليو(دري);

    إذا ((دري->flags & SDL_دري_TRANSPARENT) && _this->Update_دري_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_اشارو_Property(دري->props, SDL_PROP_دري_SHAPE_اشارو, عدم);
        إذا (surface) {
            _this->Update_دري_Shape(_this, دري, surface);
        }
    }
}

فراغ SDL_Check_دري_Pixel_سائيز_بدليو(SDL_دري *دري)
{
    صحيح pixel_w = 0, pixel_h = 0;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &pixel_w, &pixel_h);
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_PIXEL_سائيز_بدليو, pixel_w, pixel_h);

    SDL_Check_دري_Display_Scale_بدليو(دري);
}

فراغ SDL_On_دري_Pixel_سائيز_بدليو(SDL_دري *دري)
{
    دري->surface_valid = false;
}

فراغ SDL_On_دري_جيئرو_Resize_Update(SDL_دري *دري)
{
    إذا (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } وإلا {
        // Send an expose event so the application can redraw
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ساكن فراغ SDL_Check_دري_محفوظ_Area_بدليو(SDL_دري *دري)
{
    SDL_Rect rect;

    rect.x = دري->محفوظ_inset_کاٻو;
    rect.y = دري->محفوظ_inset_چوٽي;
    rect.w = دري->w - (دري->محفوظ_inset_ساڄو + دري->محفوظ_inset_کاٻو);
    rect.h = دري->h - (دري->محفوظ_inset_چوٽي + دري->محفوظ_inset_bottom);
    إذا (SDL_memcmp(&rect, &دري->محفوظ_rect, حجم(rect)) != 0) {
        SDL_copyp(&دري->محفوظ_rect, &rect);
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_محفوظ_AREA_بدليو, 0, 0);
    }
}

فراغ SDL_سيٽ_دري_محفوظ_Area_Insets(SDL_دري *دري, صحيح کاٻو, صحيح ساڄو, صحيح چوٽي, صحيح bottom)
{
    دري->محفوظ_inset_کاٻو = کاٻو;
    دري->محفوظ_inset_ساڄو = ساڄو;
    دري->محفوظ_inset_چوٽي = چوٽي;
    دري->محفوظ_inset_bottom = bottom;
    SDL_Check_دري_محفوظ_Area_بدليو(دري);
}

bool SDL_Get_دري_محفوظ_Area(SDL_دري *دري, SDL_Rect *rect)
{
    إذا (rect) {
        SDL_zerop(rect);
    }

    CHECK_دري_MAGIC(دري, false);

    إذا (rect) {
        إذا (SDL_Rect_خالي_جايون(&دري->محفوظ_rect)) {
            rect->w = دري->w;
            rect->h = دري->h;
        } وإلا {
            SDL_copyp(rect, &دري->محفوظ_rect);
        }
    }
    أرجع true;
}

فراغ SDL_On_دري_Minimized(SDL_دري *دري)
{
    إذا (دري->flags & SDL_دري_FULLSCREEN) {
        SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

فراغ SDL_On_دري_Maximized(SDL_دري *دري)
{
}

فراغ SDL_On_دري_Restored(SDL_دري *دري)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    إذا (دري->flags & SDL_دري_FULLSCREEN) {
        SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

فراغ SDL_On_دري_Enter(SDL_دري *دري)
{
    إذا (_this->On_دري_Enter) {
        _this->On_دري_Enter(_this, دري);
    }
    SDL_Update_Relative_Mouse_گهڻائي();
}

فراغ SDL_On_دري_Leave(SDL_دري *دري)
{
    SDL_Update_Relative_Mouse_گهڻائي();
}

فراغ SDL_On_دري_Focus_Gained(SDL_دري *دري)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    إذا (mouse && mouse->relative_گهڻائي) {
        SDL_سيٽ_Mouse_Focus(دري);
    }

    SDL_Update_دري_Grab(دري);
}

ساكن bool SDL_ShouldMinimizeOnFocusLoss(SDL_دري *دري)
{
    ثابت حرف *hint;

    إذا (!(دري->flags & SDL_دري_FULLSCREEN) || دري->is_destroying) {
        أرجع false;
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (Cocoa_IsShowingModalDialog(دري)) {
            أرجع false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } وإلا إذا (Cocoa_Is_دري_اندريون_Fullscreen_Space(دري)) {
            أرجع false;
        }
    }
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_ANDROID
    {
        خارجي bool Android_JNI_ShouldMinimizeOnFocusLoss(فراغ);
        إذا (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            أرجع false;
        }
    }
#جيڪڏهن_پورو

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    إذا (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        إذا (دري->fullscreen_exclusive && !SDL_گهڻائي_Switching_Emulated(_this)) {
            أرجع true;
        } وإلا {
            أرجع false;
        }
    }
    أرجع SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

فراغ SDL_On_دري_Focus_گم(SDL_دري *دري)
{
    SDL_Update_دري_Grab(دري);

    إذا (SDL_ShouldMinimizeOnFocusLoss(دري)) {
        SDL_Minimize_دري(دري);
    }
}

SDL_دري *SDL_GetToplevelForKeyboardFocus(فراغ)
{
    SDL_دري *focus = SDL_GetKeyboardFocus();

    إذا (focus) {
        // Get the toplevel parent window.
        طالما (focus->والد) {
            focus = focus->والد;
        }
    }

    أرجع focus;
}

bool SDL_جوڙيو_دري_Renderer(SDL_دري *دري, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(دري->renderers, (دري->انگ_renderers + 1) * حجم(*renderers));
    إذا (!renderers) {
        أرجع false;
    }

    دري->renderers = renderers;
    دري->renderers[دري->انگ_renderers++] = renderer;

    SDL_سيٽ_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_RENDERER_اشارو, renderer);
    أرجع true;
}

فراغ SDL_Remove_دري_Renderer(SDL_دري *دري, SDL_Renderer *renderer)
{
    لكل (صحيح i = 0; i < دري->انگ_renderers; ++i) {
        إذا (دري->renderers[i] == renderer) {
            إذا (i < (دري->انگ_renderers - 1)) {
                SDL_memmove(&دري->renderers[i], &دري->renderers[i + 1], (دري->انگ_renderers - i - 1) * حجم(دري->renderers[i]));
            }
            --دري->انگ_renderers;
            اكسر;
        }
    }

    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    إذا (SDL_Get_اشارو_Property(props, SDL_PROP_دري_RENDERER_اشارو, عدم) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_دري_RENDERER_اشارو);
    }
}

فراغ SDL_Destroy_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري,);

    دري->is_destroying = true;

    // Destroy any child windows of this window
    طالما (دري->پهريون_ٻار) {
        SDL_Destroy_دري(دري->پهريون_ٻار);
    }

    SDL_Send_دري_Event(دري, SDL_EVENT_دري_DESTROYED, 0, 0);

    SDL_Destroy_دري_Surface(دري);

    SDL_Renderer *renderer = SDL_GetRenderer(دري);
    إذا (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_LEAVE, true);
    إذا (!(دري->flags & SDL_دري_EXTERNAL)) {
        SDL_Hide_دري(دري);
    }

    SDL_DestroyProperties(دري->متن_داخلا_props);

    SDL_Destroy_دري_Texture(_this, دري);
    SDL_DestroyProperties(دري->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    إذا (_this->سيٽ_دري_Modal && (دري->flags & SDL_دري_MODAL)) {
        _this->سيٽ_دري_Modal(_this, دري, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    لكل (صحيح i = 0; i < _this->انگ_displays; ++i) {
        إذا (_this->displays[i]->fullscreen_دري == دري) {
            _this->displays[i]->fullscreen_دري = عدم;
        }
    }

    // Make sure this window no longer has focus
    إذا (SDL_GetKeyboardFocus() == دري) {
        SDL_سيٽ_Keyboard_Focus(عدم);
    }
    إذا ((دري->flags & SDL_دري_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    إذا (SDL_GetMouseFocus() == دري) {
        SDL_سيٽ_Mouse_Focus(عدم);
    }

    // Make no context current if this is the current context window
    إذا (دري->flags & SDL_دري_OPENGL) {
        إذا (_this->current_glwin == دري) {
            SDL_GL_MakeCurrent(دري, عدم);
        }
    }

    إذا (_this->Destroy_دري) {
        _this->Destroy_دري(_this, دري);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    إذا (دري->flags & SDL_دري_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    إذا (دري->flags & SDL_دري_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->grabbed_دري == دري) {
        _this->grabbed_دري = عدم; // ungrabbing input.
    }

    إذا (_this->current_glwin == دري) {
        _this->current_glwin = عدم;
    }

    SDL_Compare_And_مٽا_سٽا_Atomic_اشارو(&_this->wakeup_دري, دري, عدم);

    // Now invalidate magic
    SDL_سيٽ_Object_Valid(دري, SDL_OBJECT_TYPE_دري, false);

    // Free memory associated with the window
    SDL_free(دري->title);
    SDL_DestroySurface(دري->icon);

    // Unlink the window from its siblings.
    SDL_Update_دري_Hierarchy(دري, عدم);

    // Unlink the window from the global window list
    إذا (دري->ايندڙ) {
        دري->ايندڙ->prev = دري->prev;
    }
    إذا (دري->prev) {
        دري->prev->ايندڙ = دري->ايندڙ;
    } وإلا {
        _this->windows = دري->ايندڙ;
    }

    SDL_free(دري->renderers);
    SDL_free(دري);

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#جيڪڏهن_پورو
}

bool SDL_ScreenSaverEnabled(فراغ)
{
    إذا (!_this) {
        أرجع true;
    }
    أرجع !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(فراغ)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (!_this->suspend_screensaver) {
        أرجع true;
    }
    _this->suspend_screensaver = false;
    إذا (_this->SuspendScreenSaver) {
        أرجع _this->SuspendScreenSaver(_this);
    }

    أرجع SDL_Unsupported();
}

bool SDL_DisableScreenSaver(فراغ)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->suspend_screensaver) {
        أرجع true;
    }
    _this->suspend_screensaver = true;
    إذا (_this->SuspendScreenSaver) {
        أرجع _this->SuspendScreenSaver(_this);
    }

    أرجع SDL_Unsupported();
}

فراغ SDL_QuitVideo(فراغ)
{
    صحيح i;

    إذا (!_this) {
        أرجع;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#إذا 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#جيڪڏهن_پورو
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    طالما (_this->windows) {
        SDL_Destroy_دري(_this->windows);
    }

    إذا (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    إذا (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    لكل (i = _this->انگ_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->انگ_displays == 0);
    SDL_free(_this->displays);
    _this->displays = عدم;

    SDL_Cancel_Clipboard_معلومات(0);

    إذا (_this->primary_selection_متن) {
        SDL_free(_this->primary_selection_متن);
        _this->primary_selection_متن = عدم;
    }
    _this->حرر(_this);
    _this = عدم;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_ڀريو_Library(ثابت حرف *رستو)
{
    bool نتيجو;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->gl_config.driver_loaded) {
        إذا (رستو && SDL_strcmp(رستو, _this->gl_config.driver_رستو) != 0) {
            أرجع SDL_سيٽ_Error("OpenGL library already loaded");
        }
        نتيجو = true;
    } وإلا {
        إذا (!_this->GL_ڀريو_Library) {
            أرجع SDL_DllNotSupported("OpenGL");
        }
        نتيجو = _this->GL_ڀريو_Library(_this, رستو);
    }
    إذا (نتيجو) {
        ++_this->gl_config.driver_loaded;
    } وإلا {
        إذا (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    أرجع نتيجو;
}

SDL_Function_اشارو SDL_GL_Get_Proc_پتو(ثابت حرف *proc)
{
    SDL_Function_اشارو func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;
    إذا (_this->GL_Get_Proc_پتو) {
        إذا (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_پتو(_this, proc);
        } وإلا {
            SDL_سيٽ_Error("No GL driver has been loaded");
        }
    } وإلا {
        SDL_سيٽ_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    أرجع func;
}

SDL_Function_اشارو SDL_EGL_Get_Proc_پتو(ثابت حرف *proc)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    SDL_Function_اشارو func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;

    إذا (_this->egl_معلومات) {
        func = SDL_EGL_Get_Proc_پتو_اندروني(_this, proc);
    } وإلا {
        SDL_سيٽ_Error("No EGL library has been loaded");
    }

    أرجع func;
#وإلا
    SDL_سيٽ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جيڪڏهن_پورو
}

فراغ SDL_GL_UnloadLibrary(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع;
    }
    إذا (_this->gl_config.driver_loaded > 0) {
        إذا (--_this->gl_config.driver_loaded > 0) {
            أرجع;
        }
        إذا (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
تعريفنوع GLenum (APIENTRY* PFNGLGETERRORPROC) (فراغ);
تعريفنوع فراغ (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
تعريفنوع فراغ (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#جيڪڏهن_وصف_نه_ٿيل SDL_VIDEO_OPENGL
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint اشاريو);
#جيڪڏهن_پورو

ساكن SDL_INLINE bool is_At_گهٽ_کان_گهٽ_GL3(ثابت حرف *verstr)
{
    أرجع verstr && (SDL_atoi(verstr) >= 3);
}
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت حرف *extension)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت حرف *extensions;
    ثابت حرف *شروعات;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    إذا (where || *extension == '\0') {
        أرجع false;
    }
    // See if there's a hint or environment variable override
    شروعات = SDL_GetHint(extension);
    إذا (شروعات && *شروعات == '0') {
        أرجع false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتو("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (is_At_گهٽ_کان_گهٽ_GL3((ثابت حرف *)glGetStringFunc(GL_نسخو))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint انگ_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_پتو("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتو("glGetIntegerv");
        إذا ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            أرجع false;
        }

#جيڪڏهن_وصف_نه_ٿيل GL_انگ_EXTENSIONS
#وصف_ڪريو GL_انگ_EXTENSIONS 0x821D
#جيڪڏهن_پورو
        glGetIntegervFunc(GL_انگ_EXTENSIONS, &انگ_exts);
        لكل (i = 0; i < انگ_exts; i++) {
            ثابت حرف *thisext = (ثابت حرف *)glGetStringiFunc(GL_EXTENSIONS, i);
            إذا (SDL_strcmp(thisext, extension) == 0) {
                أرجع true;
            }
        }

        أرجع false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ثابت حرف *)glGetStringFunc(GL_EXTENSIONS);
    إذا (!extensions) {
        أرجع false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    شروعات = extensions;

    لكل (;;) {
        where = SDL_strstr(شروعات, extension);
        إذا (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        إذا (where == extensions || *(where - 1) == ' ') {
            إذا (*terminator == ' ' || *terminator == '\0') {
                أرجع true;
            }
        }

        شروعات = terminator;
    }
    أرجع false;
#وإلا
    أرجع false;
#جيڪڏهن_پورو
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
فراغ SDL_GL_DeduceMaxSupportedESProfile(صحيح *major, صحيح *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    إذا (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } وإلا إذا (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } وإلا إذا (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } وإلا {
        *major = 2;
        *minor = 0;
    }
#جيڪڏهن_پورو
}

فراغ SDL_EGL_سيٽ_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   فراغ *userdata)
{
    إذا (!_this) {
        أرجع;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

فراغ SDL_GL_Reset_خاصيتون(فراغ)
{
    إذا (!_this) {
        أرجع;
    }

    _this->egl_platformattrib_callback = عدم;
    _this->egl_surfaceattrib_callback = عدم;
    _this->egl_contextattrib_callback = عدم;
    _this->egl_attrib_callback_userdata = عدم;

    _this->gl_config.red_سائيز = 8;
    _this->gl_config.green_سائيز = 8;
    _this->gl_config.blue_سائيز = 8;
    _this->gl_config.alpha_سائيز = 8;
    _this->gl_config.بفر_سائيز = 0;
    _this->gl_config.اونهائي_سائيز = 16;
    _this->gl_config.stencil_سائيز = 0;
    _this->gl_config.double_بفر = 1;
    _this->gl_config.accum_red_سائيز = 0;
    _this->gl_config.accum_green_سائيز = 0;
    _this->gl_config.accum_blue_سائيز = 0;
    _this->gl_config.accum_alpha_سائيز = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    _this->gl_config.major_نسخو = 2;
    _this->gl_config.minor_نسخو = 1;
    _this->gl_config.profile_نقاب = 0;
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_نسخو = 2;
    _this->gl_config.minor_نسخو = 0;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_نسخو = 1;
    _this->gl_config.minor_نسخو = 1;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
#جيڪڏهن_پورو

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    إذا (_this->GL_سيٽ_Default_Profile_Config) {
        _this->GL_سيٽ_Default_Profile_Config(_this);
    }
}

bool SDL_GL_سيٽ_Attribute(SDL_GLAttr attr, صحيح قدر)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool نتيجو;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    نتيجو = true;
    بدل (attr) {
    حالة SDL_GL_RED_سائيز:
        _this->gl_config.red_سائيز = قدر;
        اكسر;
    حالة SDL_GL_GREEN_سائيز:
        _this->gl_config.green_سائيز = قدر;
        اكسر;
    حالة SDL_GL_BLUE_سائيز:
        _this->gl_config.blue_سائيز = قدر;
        اكسر;
    حالة SDL_GL_ALPHA_سائيز:
        _this->gl_config.alpha_سائيز = قدر;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_بفر = قدر;
        اكسر;
    حالة SDL_GL_بفر_سائيز:
        _this->gl_config.بفر_سائيز = قدر;
        اكسر;
    حالة SDL_GL_اونهائي_سائيز:
        _this->gl_config.اونهائي_سائيز = قدر;
        اكسر;
    حالة SDL_GL_STENCIL_سائيز:
        _this->gl_config.stencil_سائيز = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_RED_سائيز:
        _this->gl_config.accum_red_سائيز = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_سائيز:
        _this->gl_config.accum_green_سائيز = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_سائيز:
        _this->gl_config.accum_blue_سائيز = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_سائيز:
        _this->gl_config.accum_alpha_سائيز = قدر;
        اكسر;
    حالة SDL_GL_STEREO:
        _this->gl_config.stereo = قدر;
        اكسر;
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = قدر;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = قدر;
        اكسر;
    حالة SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = قدر;
        اكسر;
    حالة SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = قدر;
        اكسر;
    حالة SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_MAJOR_نسخو:
        _this->gl_config.major_نسخو = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_MINOR_نسخو:
        _this->gl_config.minor_نسخو = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_FLAGS:
        إذا (قدر & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            نتيجو = SDL_سيٽ_Error("Unknown OpenGL context flag %d", قدر);
            اكسر;
        }
        _this->gl_config.flags = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_PROFILE_نقاب:
        إذا (قدر != 0 &&
            قدر != SDL_GL_CONTEXT_PROFILE_CORE &&
            قدر != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            قدر != SDL_GL_CONTEXT_PROFILE_ES) {
            نتيجو = SDL_سيٽ_Error("Unknown OpenGL context profile %d", قدر);
            اكسر;
        }
        _this->gl_config.profile_نقاب = قدر;
        اكسر;
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = قدر;
        اكسر;
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = قدر;
        اكسر;
    حالة SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = قدر;
        اكسر;
    افتراضي:
        نتيجو = SDL_سيٽ_Error("Unknown OpenGL attribute");
        اكسر;
    }
    أرجع نتيجو;
#وإلا
    أرجع SDL_Unsupported();
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحيح *قدر)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_پٺ_کاٻو;
    GLenum attachmentattrib = 0;
#جيڪڏهن_پورو

    CHECK_PARAM(!قدر) {
        أرجع SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *قدر = 0;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    بدل (attr) {
    حالة SDL_GL_RED_سائيز:
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_سائيز;
#جيڪڏهن_پورو
        attrib = GL_RED_بٽ;
        اكسر;
    حالة SDL_GL_BLUE_سائيز:
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_سائيز;
#جيڪڏهن_پورو
        attrib = GL_BLUE_بٽ;
        اكسر;
    حالة SDL_GL_GREEN_سائيز:
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_سائيز;
#جيڪڏهن_پورو
        attrib = GL_GREEN_بٽ;
        اكسر;
    حالة SDL_GL_ALPHA_سائيز:
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_سائيز;
#جيڪڏهن_پورو
        attrib = GL_ALPHA_بٽ;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        اكسر;
#وإلا
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *قدر = _this->gl_config.double_بفر;
        أرجع true;
#جيڪڏهن_پورو
    حالة SDL_GL_اونهائي_سائيز:
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        attachment = GL_اونهائي;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_اونهائي_سائيز;
#جيڪڏهن_پورو
        attrib = GL_اونهائي_بٽ;
        اكسر;
    حالة SDL_GL_STENCIL_سائيز:
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_سائيز;
#جيڪڏهن_پورو
        attrib = GL_STENCIL_بٽ;
        اكسر;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    حالة SDL_GL_ACCUM_RED_سائيز:
        attrib = GL_ACCUM_RED_بٽ;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_سائيز:
        attrib = GL_ACCUM_GREEN_بٽ;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_سائيز:
        attrib = GL_ACCUM_BLUE_بٽ;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_سائيز:
        attrib = GL_ACCUM_ALPHA_بٽ;
        اكسر;
    حالة SDL_GL_STEREO:
        attrib = GL_STEREO;
        اكسر;
#وإلا
    حالة SDL_GL_ACCUM_RED_سائيز:
    حالة SDL_GL_ACCUM_GREEN_سائيز:
    حالة SDL_GL_ACCUM_BLUE_سائيز:
    حالة SDL_GL_ACCUM_ALPHA_سائيز:
    حالة SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *قدر = 0;
        أرجع true;
#جيڪڏهن_پورو
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        اكسر;
    حالة SDL_GL_بفر_سائيز:
    {
        صحيح rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        إذا (!SDL_GL_GetAttribute(SDL_GL_RED_سائيز, &rsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_GREEN_سائيز, &gsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_BLUE_سائيز, &bsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_ALPHA_سائيز, &asize)) {
            أرجع false;
        }

        *قدر = rsize + gsize + bsize + asize;
        أرجع true;
    }
    حالة SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *قدر = (_this->gl_config.accelerated != 0);
        أرجع true;
    }
    حالة SDL_GL_RETAINED_BACKING:
    {
        *قدر = _this->gl_config.retained_backing;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MAJOR_نسخو:
    {
        *قدر = _this->gl_config.major_نسخو;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MINOR_نسخو:
    {
        *قدر = _this->gl_config.minor_نسخو;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_FLAGS:
    {
        *قدر = _this->gl_config.flags;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_PROFILE_نقاب:
    {
        *قدر = _this->gl_config.profile_نقاب;
        أرجع true;
    }
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *قدر = _this->gl_config.share_with_current_context;
        أرجع true;
    }
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *قدر = _this->gl_config.framebuffer_srgb_capable;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_NO_ERROR:
    {
        *قدر = _this->gl_config.no_error;
        أرجع true;
    }
    حالة SDL_GL_EGL_PLATFORM:
    {
        *قدر = _this->gl_config.egl_platform;
        أرجع true;
    }
    حالة SDL_GL_FLOATBUFFERS:
    {
        إذا (_this->gl_config.HAS_GL_ARB_color_بفر_float) {
            attrib = GL_RGBA_FLOAT_گهڻائي_ARB;
            اكسر;
        } وإلا {
            أرجع 0;
        }
    }
    افتراضي:
        أرجع SDL_سيٽ_Error("Unknown OpenGL attribute");
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتو("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (attachmentattrib && is_At_گهٽ_کان_گهٽ_GL3((ثابت حرف *)glGetStringFunc(GL_نسخو))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_پتو("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_پتو("glBindFramebuffer");
        إذا (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_پتو("glGetFramebufferAttachmentParameteriv");
        إذا (glGetFramebufferAttachmentParameterivFunc) {
            إذا (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            إذا (attachment == GL_اونهائي || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            إذا (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)قدر);
            } وإلا {
                *قدر = 0;
            }
            إذا (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } وإلا {
            أرجع false;
        }
    } وإلا
#جيڪڏهن_پورو
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتو("glGetIntegerv");
        إذا (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)قدر);
        } وإلا {
            أرجع false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_پتو("glGetError");
    إذا (!glGetErrorFunc) {
        أرجع false;
    }

    error = glGetErrorFunc();
    إذا (error != GL_NO_ERROR) {
        إذا (error == GL_INVALID_ENUM) {
            أرجع SDL_سيٽ_Error("OpenGL error: GL_INVALID_ENUM");
        } وإلا إذا (error == GL_INVALID_قدر) {
            أرجع SDL_سيٽ_Error("OpenGL error: GL_INVALID_VALUE");
        }
        أرجع SDL_سيٽ_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    إذا (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *قدر = (*قدر == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    أرجع true;
#وإلا
    أرجع SDL_Unsupported();
#جيڪڏهن_پورو // SDL_VIDEO_OPENGL
}

#وصف_ڪريو NOT_AN_OPENGL_دري "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_دري *دري)
{
    SDL_GLContext ctx = عدم;
    CHECK_دري_MAGIC(دري, عدم);

    إذا (!(دري->flags & SDL_دري_OPENGL)) {
        SDL_سيٽ_Error(NOT_AN_OPENGL_دري);
        أرجع عدم;
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحيح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    إذا (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#جيڪڏهن_پورو

    ctx = _this->GL_CreateContext(_this, دري);

    // Creating a context is assumed to make it current in the SDL driver.
    إذا (ctx) {
        _this->current_glwin = دري;
        _this->current_glctx = ctx;
        SDL_سيٽ_TLS(&_this->current_glwin_tls, دري, عدم);
        SDL_سيٽ_TLS(&_this->current_glctx_tls, ctx, عدم);
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    إذا (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_پتو(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتو("glGetString");
        إذا (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            إذا (_this->gl_config.profile_نقاب & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } وإلا {
                supported = is_At_گهٽ_کان_گهٽ_GL3((ثابت حرف *)glGetStringFunc(GL_نسخو)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            إذا (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#جيڪڏهن_پورو

    أرجع ctx;
}

bool SDL_GL_MakeCurrent(SDL_دري *دري, SDL_GLContext context)
{
    bool نتيجو;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (دري == SDL_GL_Get_Current_دري() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        أرجع true;
    }

    إذا (!context) {
        دري = عدم;
    } وإلا إذا (دري) {
        CHECK_دري_MAGIC(دري, false);

        إذا (!(دري->flags & SDL_دري_OPENGL)) {
            أرجع SDL_سيٽ_Error(NOT_AN_OPENGL_دري);
        }
    } وإلا إذا (!_this->gl_allow_no_surface) {
        أرجع SDL_سيٽ_Error("Use of OpenGL without a window is not supported on this platform");
    }

    نتيجو = _this->GL_MakeCurrent(_this, دري, context);
    إذا (نتيجو) {
        _this->current_glwin = دري;
        _this->current_glctx = context;
        SDL_سيٽ_TLS(&_this->current_glwin_tls, دري, عدم);
        SDL_سيٽ_TLS(&_this->current_glctx_tls, context, عدم);
    }
    أرجع نتيجو;
}

SDL_دري *SDL_GL_Get_Current_دري(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع (SDL_دري *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(فراغ)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع EGL_NO_DISPLAY;
    }
    إذا (!_this->egl_معلومات) {
        SDL_سيٽ_Error("There is no current EGL display");
        أرجع EGL_NO_DISPLAY;
    }
    أرجع _this->egl_معلومات->egl_display;
#وإلا
    SDL_سيٽ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جيڪڏهن_پورو
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(فراغ)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_معلومات) {
        SDL_سيٽ_Error("There is no current EGL display");
        أرجع عدم;
    }
    أرجع _this->egl_معلومات->egl_config;
#وإلا
    SDL_سيٽ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جيڪڏهن_پورو
}

SDL_EGLConfig SDL_EGL_Get_دري_Surface(SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_معلومات) {
        SDL_سيٽ_Error("There is no current EGL display");
        أرجع عدم;
    }
    إذا (_this->GL_GetEGLSurface) {
        أرجع _this->GL_GetEGLSurface(_this, دري);
    }
    أرجع عدم;
#وإلا
    SDL_سيٽ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جيڪڏهن_پورو
}

bool SDL_GL_سيٽ_مٽا_سٽا_Interval(صحيح interval)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_سيٽ_Error("No OpenGL context has been made current");
    } وإلا إذا (_this->GL_سيٽ_مٽا_سٽا_Interval) {
        أرجع _this->GL_سيٽ_مٽا_سٽا_Interval(_this, interval);
    } وإلا {
        أرجع SDL_سيٽ_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_مٽا_سٽا_Interval(صحيح *interval)
{
    CHECK_PARAM(!interval) {
       أرجع SDL_InvalidParamError("interval");
    }

    *interval = 0;

    إذا (!_this) {
        أرجع SDL_سيٽ_Error("no video driver");
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_سيٽ_Error("no current context");
    } وإلا إذا (_this->GL_Get_مٽا_سٽا_Interval) {
        أرجع _this->GL_Get_مٽا_سٽا_Interval(_this, interval);
    } وإلا {
        أرجع SDL_سيٽ_Error("not implemented");
    }
}

bool SDL_GL_مٽا_سٽا_دري(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (!(دري->flags & SDL_دري_OPENGL)) {
        أرجع SDL_سيٽ_Error(NOT_AN_OPENGL_دري);
    }

    إذا (SDL_GL_Get_Current_دري() != دري) {
        أرجع SDL_سيٽ_Error("The specified window has not been made current");
    }

    أرجع _this->GL_مٽا_سٽا_دري(_this, دري);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        أرجع SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        أرجع SDL_InvalidParamError("context");
    }

    إذا (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(عدم, عدم);
    }

    أرجع _this->GL_DestroyContext(_this, context);
}

#إذا 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ساكن فراغ Create_نقاب_From_Color_ڪنجي_Or_Alpha(SDL_Surface *icon, Uint8 *نقاب, صحيح flags)
{
    صحيح x, y;
    Uint32 colorkey;
#وصف_ڪريو سيٽ_MASKBIT(icon, x, y, نقاب) \
    نقاب[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    بدل (SDL_BYTESPERPIXEL(icon->format)) {
    حالة 1:
        {
            Uint8 *pixels;
            لكل (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                لكل (x = 0; x < icon->w; ++x) {
                    إذا (*pixels++ == colorkey) {
                        سيٽ_MASKBIT(icon, x, y, نقاب);
                    }
                }
            }
        }
        اكسر;

    حالة 2:
        {
            Uint16 *pixels;
            لكل (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                لكل (x = 0; x < icon->w; ++x) {
                    إذا ((flags & 1) && *pixels == colorkey) {
                        سيٽ_MASKBIT(icon, x, y, نقاب);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سيٽ_MASKBIT(icon, x, y, نقاب);
                    }
                    pixels++;
                }
            }
        }
        اكسر;

    حالة 4:
        {
            Uint32 *pixels;
            لكل (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                لكل (x = 0; x < icon->w; ++x) {
                    إذا ((flags & 1) && *pixels == colorkey) {
                        سيٽ_MASKBIT(icon, x, y, نقاب);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سيٽ_MASKBIT(icon, x, y, نقاب);
                    }
                    pixels++;
                }
            }
        }
        اكسر;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
فراغ SDL_WM_سيٽ_Icon(SDL_Surface *icon, Uint8 *نقاب)
{
    إذا (icon && _this->سيٽ_Icon) {
        // Generate a mask if necessary, and create the icon!
        إذا (نقاب == عدم) {
            صحيح نقاب_len = icon->h * (icon->w + 7) / 8;
            صحيح flags = 0;
            نقاب = (Uint8 *) SDL_malloc(نقاب_len);
            إذا (نقاب == عدم) {
                أرجع;
            }
            SDL_memset(نقاب, ~0, نقاب_len);
            إذا (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            إذا (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            إذا (flags) {
                Create_نقاب_From_Color_ڪنجي_Or_Alpha(icon, نقاب, flags);
            }
            _this->سيٽ_Icon(_this, icon, نقاب);
            SDL_free(نقاب);
        } وإلا {
            _this->سيٽ_Icon(_this, icon, نقاب);
        }
    }
}
#جيڪڏهن_پورو

SDL_متن_داخلا_Type SDL_Get_متن_داخلا_Type(SDL_PropertiesID props)
{
    أرجع (SDL_متن_داخلا_Type)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_TYPE_عدد, SDL_TEXTINPUT_TYPE_متن);
}

SDL_Capitalization SDL_Get_متن_داخلا_Capitalization(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_عدد)) {
        أرجع (SDL_Capitalization)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_عدد, SDL_CAPITALIZE_NONE);
    }

    بدل (SDL_Get_متن_داخلا_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن:
        أرجع SDL_CAPITALIZE_SENTENCES;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        أرجع SDL_CAPITALIZE_لفظ;
    افتراضي:
        أرجع SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_متن_داخلا_Autocorrect(SDL_PropertiesID props)
{
    أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_متن_داخلا_Multiline(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_RETURN_ڪنجي_HIDES_IME, false)) {
        أرجع false;
    } وإلا {
        أرجع true;
    }
}

ساكن bool AutoShowingScreenKeyboard(فراغ)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    إذا (!hint) {
        // This hint is currently only used by the X11 video driver
        إذا (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    إذا (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

bool SDL_شروعات_متن_داخلا(SDL_دري *دري)
{
    أرجع SDL_شروعات_متن_داخلا_With_Properties(دري, 0);
}

bool SDL_شروعات_متن_داخلا_With_Properties(SDL_دري *دري, SDL_PropertiesID props)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (دري->متن_داخلا_props) {
        SDL_DestroyProperties(دري->متن_داخلا_props);
        دري->متن_داخلا_props = 0;
    }

    إذا (props) {
        دري->متن_داخلا_props = SDL_CreateProperties();
        إذا (!دري->متن_داخلا_props) {
            أرجع false;
        }
        إذا (!SDL_CopyProperties(props, دري->متن_داخلا_props)) {
            أرجع false;
        }
    }

    إذا (_this->سيٽ_متن_داخلا_Properties) {
        _this->سيٽ_متن_داخلا_Properties(_this, دري, props);
    }

    إذا (!دري->متن_داخلا_سرگرم) {
        // Start the text input system
        إذا (_this->شروعات_متن_داخلا) {
            إذا (!_this->شروعات_متن_داخلا(_this, دري, props)) {
                أرجع false;
            }
        }
        دري->متن_داخلا_سرگرم = true;
    }

    // Show the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(دري)) {
        إذا (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, دري, props);
        }
    }
    أرجع true;
}

bool SDL_متن_داخلا_سرگرم(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    أرجع دري->متن_داخلا_سرگرم;
}

bool SDL_Stop_متن_داخلا(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (دري->متن_داخلا_سرگرم) {
        // Stop the text input system
        إذا (_this->Stop_متن_داخلا) {
            _this->Stop_متن_داخلا(_this, دري);
        }
        دري->متن_داخلا_سرگرم = false;
    }

    // Hide the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(دري)) {
        إذا (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, دري);
        }
    }
    أرجع true;
}

bool SDL_سيٽ_متن_داخلا_Area(SDL_دري *دري, ثابت SDL_Rect *rect, صحيح cursor)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (rect) {
        SDL_copyp(&دري->متن_داخلا_rect, rect);
        دري->متن_داخلا_cursor = cursor;
    } وإلا {
        SDL_zero(دري->متن_داخلا_rect);
        دري->متن_داخلا_cursor = 0;
    }

    إذا (_this && _this->Update_متن_داخلا_Area) {
        إذا (!_this->Update_متن_داخلا_Area(_this, دري)) {
            أرجع false;
        }
    }
    أرجع true;
}

bool SDL_Get_متن_داخلا_Area(SDL_دري *دري, SDL_Rect *rect, صحيح *cursor)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (rect) {
        SDL_copyp(rect, &دري->متن_داخلا_rect);
    }
    إذا (cursor) {
        *cursor = دري->متن_داخلا_cursor;
    }
    أرجع true;
}

bool SDL_ClearComposition(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (_this->ClearComposition) {
        أرجع _this->ClearComposition(_this, دري);
    }
    أرجع true;
}

bool SDL_HasScreenKeyboardSupport(فراغ)
{
    إذا (_this && _this->HasScreenKeyboardSupport) {
        أرجع _this->HasScreenKeyboardSupport(_this);
    }
    أرجع false;
}

bool SDL_ScreenKeyboardShown(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, false);

    أرجع _this->screen_keyboard_shown;
}

فراغ SDL_SendScreenKeyboardShown(فراغ)
{
    إذا (!_this || _this->screen_keyboard_shown) {
        أرجع;
    }

    _this->screen_keyboard_shown = true;

    إذا (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ڌڪو_Event(&event);
    }
}

فراغ SDL_SendScreenKeyboardHidden(فراغ)
{
    إذا (!_this || !_this->screen_keyboard_shown) {
        أرجع;
    }

    _this->screen_keyboard_shown = false;

    إذا (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ڌڪو_Event(&event);
    }
}

صحيح SDL_Get_پيغام_Box_ڳڻپ(فراغ)
{
    أرجع SDL_GetAtomicInt(&SDL_messagebox_ڳڻپ);
}

bool SDL_Show_پيغام_Box(ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
    صحيح dummybutton;
    bool نتيجو = false;
    bool show_cursor_prev;
    SDL_دري *current_دري;
    SDL_پيغام_Box_معلومات mbdata;

    CHECK_PARAM(!messageboxdata) {
        أرجع SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        أرجع SDL_سيٽ_Error("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    حرف *titlecpy = عدم;
    حرف *msgcpy = عدم;
    إذا (messageboxdata->title) {
        ثابت size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(حرف, slen, &titleisstack);
        إذا (!titlecpy) {
            أرجع false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    إذا (messageboxdata->پيغام) {
        ثابت size_t slen = SDL_strlen(messageboxdata->پيغام) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        إذا (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            أرجع false;
        }
        SDL_memcpy(msgcpy, messageboxdata->پيغام, slen);
    }

    (فراغ)SDL_AtomicIncRef(&SDL_messagebox_ڳڻپ);

    current_دري = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_سيٽ_Relative_Mouse_گهڻائي(false);
    show_cursor_prev = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    إذا (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, حجم(*messageboxdata));
    mbdata.title = titlecpy;
    إذا (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.پيغام = msgcpy;
    إذا (!mbdata.پيغام) {
        mbdata.پيغام = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    إذا (_this && _this->Show_پيغام_Box) {
        نتيجو = _this->Show_پيغام_Box(_this, messageboxdata, buttonID);
    } وإلا {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        إذا (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            طالما (driver_attempt && (*driver_attempt != 0) && !نتيجو) {
                ثابت حرف *driver_attempt_پڇاڙي = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_پڇاڙي) ? (driver_attempt_پڇاڙي - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                لكل (صحيح i = 0; bootstrap[i]; ++i) {
                    إذا (bootstrap[i]->Show_پيغام_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        إذا (bootstrap[i]->Show_پيغام_Box(messageboxdata, buttonID)) {
                            نتيجو = true;
                        }
                        اكسر;
                    }
                }

                driver_attempt = (driver_attempt_پڇاڙي) ? (driver_attempt_پڇاڙي + 1) : عدم;
            }
        } وإلا {
            لكل (صحيح i = 0; bootstrap[i]; ++i) {
                إذا (bootstrap[i]->Show_پيغام_Box && bootstrap[i]->Show_پيغام_Box(messageboxdata, buttonID)) {
                    نتيجو = true;
                    اكسر;
                }
            }
        }
    }

    إذا (!نتيجو) {
        ثابت حرف *error = SDL_GetError();

        إذا (!*error) {
            SDL_سيٽ_Error("No message system available");
        }
    } وإلا {
        SDL_ClearError();
    }

    (فراغ)SDL_AtomicDecRef(&SDL_messagebox_ڳڻپ);

    إذا (current_دري) {
        SDL_Raise_دري(current_دري);
    }

    إذا (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_گهڻائي();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    أرجع نتيجو;
}

bool SDL_Show_Simple_پيغام_Box(SDL_پيغام_Box_Flags flags, ثابت حرف *title, ثابت حرف *پيغام, SDL_دري *دري)
{
#إذا defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_ساڄو;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_ساڄو = gsp_Has_Gpu_ساڄو();
    إذا (!has_Gpu_ساڄو)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_متن_لفظ_WRAP, CFG_LANGUAGE_EN);
    error_متن(&errCnf, پيغام);
    errorDisp(&errCnf);

    إذا (!has_Gpu_ساڄو)
        gfxExit();

    أرجع true;
#وإلا
    SDL_پيغام_Box_معلومات معلومات;
    SDL_پيغام_Box_Button_معلومات button;

    SDL_zero(معلومات);
    معلومات.flags = flags;
    معلومات.title = title;
    معلومات.پيغام = پيغام;
    معلومات.numbuttons = 1;
    معلومات.buttons = &button;
    معلومات.دري = دري;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.متن = "OK";

    أرجع SDL_Show_پيغام_Box(&معلومات, عدم);
#جيڪڏهن_پورو
}

bool SDL_ShouldAllowTopmost(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_دري_ALLOW_TOPMOST, true);
}

bool SDL_Show_دري_System_Menu(SDL_دري *دري, صحيح x, صحيح y)
{
    CHECK_دري_MAGIC(دري, false);
    CHECK_دري_NOT_POPUP(دري, false);

    إذا (_this->Show_دري_System_Menu) {
        _this->Show_دري_System_Menu(دري, x, y);
        أرجع true;
    }

    أرجع SDL_Unsupported();
}

bool SDL_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, SDL_ڪاميابي_Test callback, فراغ *callback_معلومات)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (!_this->سيٽ_دري_ڪاميابي_Test) {
        أرجع SDL_Unsupported();
    }

    دري->ڪاميابي_test = callback;
    دري->ڪاميابي_test_معلومات = callback_معلومات;

    أرجع _this->سيٽ_دري_ڪاميابي_Test(دري, callback != عدم);
}

bool SDL_سيٽ_دري_Shape(SDL_دري *دري, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_دري_MAGIC(دري, false);

    إذا (!(دري->flags & SDL_دري_TRANSPARENT)) {
        أرجع SDL_سيٽ_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_دري_Properties(دري);
    إذا (!props) {
        أرجع false;
    }

    إذا (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        إذا (!surface) {
            أرجع false;
        }
    } وإلا {
        surface = عدم;
    }

    إذا (!SDL_سيٽ_Surface_Property(props, SDL_PROP_دري_SHAPE_اشارو, surface)) {
        أرجع false;
    }

    إذا (_this->Update_دري_Shape) {
        إذا (!_this->Update_دري_Shape(_this, دري, surface)) {
            أرجع false;
        }
    }
    أرجع true;
}

/*
 * Functions used by iOS application delegates
 */
فراغ SDL_OnApplicationWillTerminate(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

فراغ SDL_On_Application_Did_Receive_يادگيري_Warning(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_هيٺيون_يادگيري);
}

فراغ SDL_OnApplicationWillEnterBackground(فراغ)
{
    إذا (_this) {
        SDL_دري *دري;
        لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
        }
        SDL_سيٽ_Keyboard_Focus(عدم);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

فراغ SDL_OnApplicationDidEnterBackground(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

فراغ SDL_OnApplicationWillEnterForeground(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

فراغ SDL_OnApplicationDidEnterForeground(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    إذا (_this) {
        SDL_دري *دري;
        لكل (دري = _this->windows; دري; دري = دري->ايندڙ) {
            SDL_سيٽ_Keyboard_Focus(دري);
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESTORED, 0, 0);
        }
    }
}

#وصف_ڪريو NOT_A_VULKAN_دري "The specified window isn't a Vulkan window"

bool SDL_Vulkan_ڀريو_Library(ثابت حرف *رستو)
{
    bool نتيجو;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->vulkan_config.loader_loaded) {
        إذا (رستو && SDL_strcmp(رستو, _this->vulkan_config.loader_رستو) != 0) {
            أرجع SDL_سيٽ_Error("Vulkan loader library already loaded");
        }
        نتيجو = true;
    } وإلا {
        إذا (!_this->Vulkan_ڀريو_Library) {
            أرجع SDL_DllNotSupported("Vulkan");
        }
        نتيجو = _this->Vulkan_ڀريو_Library(_this, رستو);
    }
    إذا (نتيجو) {
        _this->vulkan_config.loader_loaded++;
    }
    أرجع نتيجو;
}

SDL_Function_اشارو SDL_Vulkan_GetVkGetInstanceProcAddr(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->vulkan_config.loader_loaded) {
        SDL_سيٽ_Error("No Vulkan loader has been loaded");
        أرجع عدم;
    }
    أرجع (SDL_Function_اشارو)_this->vulkan_config.vkGetInstanceProcAddr;
}

فراغ SDL_Vulkan_UnloadLibrary(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع;
    }
    إذا (_this->vulkan_config.loader_loaded > 0) {
        إذا (--_this->vulkan_config.loader_loaded > 0) {
            أرجع;
        }
        إذا (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *ڳڻپ)
{
    Uint32 tmpcount = 0;
    إذا (!ڳڻپ) {
        ڳڻپ = &tmpcount;
    }

    إذا (!_this->Vulkan_GetInstanceExtensions) {
        *ڳڻپ = 0;
        SDL_Unsupported();
        أرجع عدم;
    }

    أرجع _this->Vulkan_GetInstanceExtensions(_this, ڳڻپ);
}

bool SDL_Vulkan_CreateSurface(SDL_دري *دري,
                                  VkInstance instance,
                                  ثابت بنية Vk_ورهاست_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_دري_MAGIC(دري, false);

    إذا (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        أرجع false;
    }

    CHECK_PARAM(!instance) {
        أرجع SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        أرجع SDL_InvalidParamError("surface");
    }

    إذا (!(دري->flags & SDL_دري_VULKAN)) {
        // No problem, we can convert to Vulkan
        إذا (دري->flags & SDL_دري_OPENGL) {
            دري->flags &= ~SDL_دري_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (دري->flags & SDL_دري_METAL) {
            دري->flags &= ~SDL_دري_METAL;
            // Nothing more to do for Metal.
        }
        إذا (SDL_Vulkan_ڀريو_Library(عدم)) {
            دري->flags |= SDL_دري_VULKAN;
        } وإلا {
            أرجع SDL_سيٽ_Error("failed to load Vulkan library");
        }
    }

    أرجع _this->Vulkan_CreateSurface(_this, دري, instance, allocator, surface);
}

فراغ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية Vk_ورهاست_Callbacks *allocator)
{
    إذا (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 قطار_Family_اشاريو)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        أرجع false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        أرجع false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        أرجع false;
    }

    إذا (_this->Vulkan_GetPresentationSupport) {
        أرجع _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, قطار_Family_اشاريو);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    أرجع true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_دري *دري)
{
    CHECK_دري_MAGIC(دري, عدم);

    إذا (!_this->Metal_CreateView) {
        SDL_Unsupported();
        أرجع عدم;
    }

    إذا (!(دري->flags & SDL_دري_METAL)) {
        // No problem, we can convert to Metal
        إذا (دري->flags & SDL_دري_OPENGL) {
            دري->flags &= ~SDL_دري_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (دري->flags & SDL_دري_VULKAN) {
            دري->flags &= ~SDL_دري_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        دري->flags |= SDL_دري_METAL;
    }

    أرجع _this->Metal_CreateView(_this, دري);
}

فراغ SDL_Metal_DestroyView(SDL_MetalView view)
{
    إذا (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

فراغ *SDL_Metal_GetLayer(SDL_MetalView view)
{
    إذا (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            أرجع عدم;
        }
        أرجع _this->Metal_GetLayer(_this, view);
    } وإلا {
        SDL_سيٽ_Error("Metal is not supported.");
        أرجع عدم;
    }
}

#إذا defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ثابت حرف *SDL_GetCSSCursorName(SDL_SystemCursor id, ثابت حرف **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    بدل (id) {
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
        أرجع "default";

    حالة SDL_SYSTEM_CURSOR_متن:
        أرجع "text";

    حالة SDL_SYSTEM_CURSOR_WAIT:
        أرجع "wait";

    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
        أرجع "crosshair";

    حالة SDL_SYSTEM_CURSOR_ترقي:
        أرجع "progress";

    حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        إذا (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        أرجع "nwse-resize";

    حالة SDL_SYSTEM_CURSOR_NESW_RESIZE:
        إذا (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        أرجع "nesw-resize";

    حالة SDL_SYSTEM_CURSOR_EW_RESIZE:
        إذا (fallback_name) {
            *fallback_name = "col-resize";
        }
        أرجع "ew-resize";

    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
        إذا (fallback_name) {
            *fallback_name = "row-resize";
        }
        أرجع "ns-resize";

    حالة SDL_SYSTEM_CURSOR_MOVE:
        إذا (fallback_name) {
            *fallback_name = "all-scroll";
        }
        أرجع "move";

    حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        أرجع "not-allowed";

    حالة SDL_SYSTEM_CURSOR_اشارو:
        أرجع "pointer";

    حالة SDL_SYSTEM_CURSOR_NW_RESIZE:
        أرجع "nw-resize";

    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
        أرجع "n-resize";

    حالة SDL_SYSTEM_CURSOR_NE_RESIZE:
        أرجع "ne-resize";

    حالة SDL_SYSTEM_CURSOR_E_RESIZE:
        أرجع "e-resize";

    حالة SDL_SYSTEM_CURSOR_SE_RESIZE:
        أرجع "se-resize";

    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
        أرجع "s-resize";

    حالة SDL_SYSTEM_CURSOR_SW_RESIZE:
        أرجع "sw-resize";

    حالة SDL_SYSTEM_CURSOR_W_RESIZE:
        أرجع "w-resize";

    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        أرجع "context-menu";

    حالة SDL_SYSTEM_CURSOR_HELP:
        أرجع "help";

    حالة SDL_SYSTEM_CURSOR_CELL:
        أرجع "cell";

    حالة SDL_SYSTEM_CURSOR_VERTICAL_متن:
        أرجع "vertical-text";

    حالة SDL_SYSTEM_CURSOR_ALIAS:
        أرجع "alias";

    حالة SDL_SYSTEM_CURSOR_COPY:
        أرجع "copy";

    حالة SDL_SYSTEM_CURSOR_NO_DROP:
        أرجع "no-drop";

    حالة SDL_SYSTEM_CURSOR_GRAB:
        أرجع "grab";

    حالة SDL_SYSTEM_CURSOR_GRABBING:
        أرجع "grabbing";

    حالة SDL_SYSTEM_CURSOR_کانو_RESIZE:
        أرجع "col-resize";

    حالة SDL_SYSTEM_CURSOR_صف_RESIZE:
        أرجع "row-resize";

    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        إذا (fallback_name) {
            *fallback_name = "move";
        }
        أرجع "all-scroll";

    حالة SDL_SYSTEM_CURSOR_ZOOM_اندريون:
        أرجع "zoom-in";

    حالة SDL_SYSTEM_CURSOR_ZOOM_ٻاهريون:
        أرجع "zoom-out";

    افتراضي:
        أرجع "default";
    }
}
#جيڪڏهن_پورو

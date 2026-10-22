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

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
#ضمن <SDL3/SDL_opengl.h>
#جے_انت // SDL_VIDEO_OPENGL

#إذا defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles.h>
#جے_انت // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#إذا defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles2.h>
#جے_انت // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#جے_بنا_تعریف GL_CONTEXT_RELEASE_BEHAVIOR
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#جے_انت

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#جے_بنا_تعریف GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#جے_انت

// This is always the same number between the various EXT/ARB/GLES extensions.
#جے_بنا_تعریف GL_FRAMEBUFFER_SRGB
#تعریف_کرو GL_FRAMEBUFFER_SRGB 0x8DB9
#جے_انت

#جے_تعریف_شدہ SDL_PLATFORM_EMSCRIPTEN
#ضمن <emscripten.h>
#جے_انت

#جے_تعریف_شدہ SDL_PLATFORM_3DS
#ضمن <3ds.h>
#جے_انت

#جے_بنا_تعریف GL_RGBA_FLOAT_منوال_ARB
#تعریف_کرو GL_RGBA_FLOAT_منوال_ARB 0x8820
#جے_انت /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ساكن VideoBootStrap *bootstrap[] = {
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_نجی
    &نجی_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#جے_انت
    &X11_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#جے_تعریف_شدہ SDL_داخلہ_LINUXEV
    &DUMMY_evdev_bootstrap,
#جے_انت
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#جے_انت
    عدم
};

#تعریف_کرو CHECK_کھڑکی_MAGIC(کھڑکی, نتیجہ)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        أرجع نتیجہ;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(کھڑکی, SDL_OBJECT_TYPE_کھڑکی)) {     \
        SDL_سیٹ_Error("Invalid window");                                 \
        أرجع نتیجہ;                                                  \
    }

#تعریف_کرو CHECK_DISPLAY_MAGIC(display, نتیجہ)                            \
    CHECK_PARAM(!display) {                                             \
        أرجع نتیجہ;                                                  \
    }                                                                   \

#تعریف_کرو CHECK_کھڑکی_NOT_POPUP(کھڑکی, نتیجہ)                          \
    CHECK_PARAM(SDL_کھڑکی_IS_POPUP(کھڑکی)) {                          \
        SDL_سیٹ_Error("Operation invalid on popup windows");             \
        أرجع نتیجہ;                                                  \
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
خارجي bool Cocoa_Is_کھڑکی_وچ_Fullscreen_Space(SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_Is_کھڑکی_وچ_Fullscreen_Space_Transition(SDL_کھڑکی *کھڑکی);
خارجي bool Cocoa_سیٹ_کھڑکی_Fullscreen_Space(SDL_کھڑکی *کھڑکی, bool state, bool blocking);
خارجي bool Cocoa_IsShowingModalDialog(SDL_کھڑکی *کھڑکی);
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
خارجي فراغ SDL_UpdateLifecycleObserver(فراغ);
#جے_انت

ساكن فراغ SDL_Check_کھڑکی_Display_بدلیا(SDL_کھڑکی *کھڑکی);
ساكن فراغ SDL_Check_کھڑکی_Display_Scale_بدلیا(SDL_کھڑکی *کھڑکی);
ساكن فراغ SDL_Check_کھڑکی_محفوظ_Area_بدلیا(SDL_کھڑکی *کھڑکی);

// Convenience functions for reading driver flags
ساكن bool SDL_منوال_Switching_Emulated(SDL_VideoDevice *_this)
{
    إذا (_this->device_caps & VIDEO_DEVICE_CAPS_منوال_SWITCHING_EMULATED) {
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

ساكن فراغ SDL_SyncIfRequired(SDL_کھڑکی *کھڑکی)
{
    إذا (syncHint) {
        SDL_Sync_کھڑکی(کھڑکی);
    }
}

ساكن فراغ SDL_Update_کھڑکی_Hierarchy(SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا)
{
    // Unlink the window from the existing parent.
    إذا (کھڑکی->ماپا) {
        إذا (کھڑکی->اگلا_sibling) {
            کھڑکی->اگلا_sibling->prev_sibling = کھڑکی->prev_sibling;
        }
        إذا (کھڑکی->prev_sibling) {
            کھڑکی->prev_sibling->اگلا_sibling = کھڑکی->اگلا_sibling;
        } وإلا {
            کھڑکی->ماپا->پہلا_بچہ = کھڑکی->اگلا_sibling;
        }

        کھڑکی->ماپا = عدم;
    }

    إذا (ماپا) {
        کھڑکی->ماپا = ماپا;

        کھڑکی->اگلا_sibling = ماپا->پہلا_بچہ;
        إذا (ماپا->پہلا_بچہ) {
            ماپا->پہلا_بچہ->prev_sibling = کھڑکی;
        }
        ماپا->پہلا_بچہ = کھڑکی;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#تعریف_کرو SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر "SDL.internal.window.texturedata"

تعريفنوع بنية
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    فراغ *pixels;
    صحيح pitch;
    صحيح بائٹاں_فی_pixel;
} SDL_کھڑکی_Texture_انکڑے;

ساكن Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#إذا (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !نشانہ_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    إذا (_this->GL_CreateContext) {
        أرجع SDL_کھڑکی_OPENGL;
    }
#جے_انت
#إذا defined(SDL_VIDEO_METAL) && (نشانہ_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    إذا (_this->Metal_CreateView) {
        أرجع SDL_کھڑکی_METAL;
    }
#جے_انت
#إذا defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    إذا (SDL_strcmp(_this->name, "openvr") == 0) {
        أرجع SDL_کھڑکی_OPENGL;
    }
#جے_انت
    أرجع 0;
}

ساكن bool SDL_Create_کھڑکی_Texture(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_کھڑکی_Texture_انکڑے *انکڑے = (SDL_کھڑکی_Texture_انکڑے *)SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, عدم);
    ثابت bool transparent = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) ? true : false;
    صحيح i;
    صحيح w, h;
    ثابت SDL_PixelFormat *texture_formats;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);

    إذا (!انکڑے) {
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
            renderer = SDL_CreateRenderer(کھڑکی, render_driver);
            SDL_free(render_driver_copy);
            إذا (!renderer) {
                // The error for this specific renderer has already been set
                أرجع false;
            }
        } وإلا {
            SDL_assert(render_driver_copy == عدم);
            ثابت صحيح کل = SDL_Get_عدد_Render_Drivers();
            لكل (i = 0; i < کل; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                إذا (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(کھڑکی, name);
                    إذا (renderer) {
                        اكسر; // this will work.
                    }
                }
            }
            إذا (!renderer) {
                أرجع SDL_سیٹ_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != عدم); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        انکڑے = (SDL_کھڑکی_Texture_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
        إذا (!انکڑے) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }
        إذا (!SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, انکڑے)) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }

        انکڑے->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_Get_اشارہ_گر_Property(SDL_GetRendererProperties(انکڑے->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_اشارہ_گر, عدم);
    إذا (!texture_formats) {
        أرجع false;
    }

    // Free any old texture and pixel data
    إذا (انکڑے->texture) {
        SDL_DestroyTexture(انکڑے->texture);
        انکڑے->texture = عدم;
    }
    SDL_free(انکڑے->pixels);
    انکڑے->pixels = عدم;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    لكل (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        إذا (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_اشاریہ_دار(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            اكسر;
        }
    }

    انکڑے->texture = SDL_CreateTexture(انکڑے->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    إذا (!انکڑے->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        أرجع false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_سیٹ_Texture_Blend_منوال(انکڑے->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    انکڑے->بائٹاں_فی_pixel = SDL_BYTESPERPIXEL(*format);
    انکڑے->pitch = (((w * انکڑے->بائٹاں_فی_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * انکڑے->pitch;
        انکڑے->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        إذا (!انکڑے->pixels) {
            أرجع false;
        }
    }

    *pixels = انکڑے->pixels;
    *pitch = انکڑے->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_سیٹ_Render_Viewport(انکڑے->renderer, عدم);

    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Texture_VSync(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح vsync)
{
    SDL_کھڑکی_Texture_انکڑے *انکڑے;

    انکڑے = (SDL_کھڑکی_Texture_انکڑے *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, عدم);
    إذا (!انکڑے) {
        أرجع false;
    }
    إذا (!انکڑے->renderer) {
        أرجع false;
    }
    أرجع SDL_سیٹ_Render_VSync(انکڑے->renderer, vsync);
}

ساكن bool SDL_Get_کھڑکی_Texture_VSync(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *vsync)
{
    SDL_کھڑکی_Texture_انکڑے *انکڑے;

    انکڑے = (SDL_کھڑکی_Texture_انکڑے *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, عدم);
    إذا (!انکڑے) {
        أرجع false;
    }
    إذا (!انکڑے->renderer) {
        أرجع false;
    }
    أرجع SDL_GetRenderVSync(انکڑے->renderer, vsync);
}

ساكن bool SDL_Update_کھڑکی_Texture(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_کھڑکی_Texture_انکڑے *انکڑے;
    SDL_Rect rect;
    فراغ *src;
    صحيح w, h;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);

    انکڑے = (SDL_کھڑکی_Texture_انکڑے *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, عدم);
    إذا (!انکڑے || !انکڑے->texture) {
        أرجع SDL_سیٹ_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    إذا (SDL_Get_وسعت_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (فراغ *)((Uint8 *)انکڑے->pixels +
                       rect.y * انکڑے->pitch +
                       rect.x * انکڑے->بائٹاں_فی_pixel);
        إذا (!SDL_UpdateTexture(انکڑے->texture, &rect, src, انکڑے->pitch)) {
            أرجع false;
        }

        إذا (!SDL_RenderTexture(انکڑے->renderer, انکڑے->texture, عدم, عدم)) {
            أرجع false;
        }

        SDL_RenderPresent(انکڑے->renderer);
    }
    أرجع true;
}

ساكن فراغ SDL_Destroy_کھڑکی_Texture(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    إذا (SDL_HasProperty(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر)) {
        SDL_کھڑکی_Texture_انکڑے *انکڑے = SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, عدم);

        إذا (انکڑے->texture) {
            SDL_DestroyTexture(انکڑے->texture);
        }
        إذا (انکڑے->renderer) {
            SDL_DestroyRenderer(انکڑے->renderer);
        }
        SDL_free(انکڑے->pixels);
        SDL_free(انکڑے);

        SDL_ClearProperty(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر);
    }
}

ساكن SDL_VideoDevice *_this = عدم;
ساكن SDL_AtomicInt SDL_messagebox_گنتی;

ساكن صحيح SDLCALL cmpmodes(ثابت فراغ *A, ثابت فراغ *B)
{
    ثابت SDL_Display_منوال *a = (ثابت SDL_Display_منوال *)A;
    ثابت SDL_Display_منوال *b = (ثابت SDL_Display_منوال *)B;
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
    أرجع SDL_سیٹ_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ساكن ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحيح SDL_Get_عدد_Video_Drivers(فراغ)
{
    ساكن صحيح عدد_drivers = -1;

    إذا (عدد_drivers >= 0) {
        أرجع عدد_drivers;
    }

    عدد_drivers = 0;

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
            deduped_bootstrap[عدد_drivers++] = bootstrap[i];
        }
    }

    أرجع عدد_drivers;
}

ثابت حرف *SDL_GetVideoDriver(صحيح اشاریہ)
{
    CHECK_PARAM(اشاریہ < 0 || اشاریہ >= SDL_Get_عدد_Video_Drivers()) {
        SDL_InvalidParamError("index");
        أرجع عدم;
    }
    أرجع deduped_bootstrap[اشاریہ]->name;
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
#جے_تعریف_شدہ SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    إذا (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#جے_انت
    إذا (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    إذا (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        طالما (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_سرا = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_سرا) ? (driver_attempt_سرا - driver_attempt)
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

            driver_attempt = (driver_attempt_سرا) ? (driver_attempt_سرا + 1) : عدم;
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
            SDL_سیٹ_Error("%s not available", driver_name);
            اذهب pre_driver_error;
        }
        SDL_سیٹ_Error("No available video device");
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
    SDL_GL_Reset_گن();

    // Initialize the video subsystem
    إذا (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        أرجع false;
    }

    // Make sure some displays were added
    إذا (_this->عدد_displays == 0) {
        SDL_QuitVideo();
        أرجع SDL_سیٹ_Error("The video driver did not add any displays");
    }

    SDL_جوڑو_Hint_Callback(SDL_HINT_VIDEO_SYNC_کھڑکی_OPERATIONS, SDL_SyncHintWatcher, عدم);

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

فراغ SDL_سیٹ_System_Theme(SDL_SystemTheme theme)
{
    إذا (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_بدلیا_Event();
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

ساكن فراغ SDL_Finalize_Display_منوال(SDL_Display_منوال *منوال)
{
    // Make sure all the fields are set up correctly
    إذا (منوال->pixel_density <= 0.0f) {
        منوال->pixel_density = 1.0f;
    }

    إذا (منوال->refresh_شرح_numerator > 0) {
        إذا (منوال->refresh_شرح_denominator <= 0) {
            منوال->refresh_شرح_denominator = 1;
        }
        منوال->refresh_شرح = (عائم)منوال->refresh_شرح_numerator / منوال->refresh_شرح_denominator;
    } وإلا {
        SDL_CalculateFraction(منوال->refresh_شرح, &منوال->refresh_شرح_numerator, &منوال->refresh_شرح_denominator);
    }
    منوال->refresh_شرح = SDL_roundf(منوال->refresh_شرح * 100) / 100.0f;
}

SDL_DisplayID SDL_جوڑو_Basic_Video_Display(ثابت SDL_Display_منوال *desktop_منوال)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    إذا (desktop_منوال) {
        SDL_memcpy(&display.desktop_منوال, desktop_منوال, حجم(display.desktop_منوال));
    }
    أرجع SDL_جوڑو_Video_Display(&display, false);
}

SDL_DisplayID SDL_جوڑو_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحيح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(حجم(*new_display));
    إذا (!new_display) {
        أرجع 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->عدد_displays + 1) * حجم(*displays));
    إذا (!displays) {
        SDL_free(new_display);
        أرجع 0;
    }
    _this->displays = displays;
    _this->displays[_this->عدد_displays++] = new_display;

    id = SDL_Get_اگلا_Object_ID();
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

    new_display->desktop_منوال.displayID = id;
    new_display->current_منوال = &new_display->desktop_منوال;
    SDL_Finalize_Display_منوال(&new_display->desktop_منوال);

    لكل (i = 0; i < new_display->عدد_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_سیٹ_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    إذا (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    أرجع id;
}

فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_کھڑکی *کھڑکی;

    // See if any windows have changed to the new display
    لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        SDL_Check_کھڑکی_Display_بدلیا(کھڑکی);
    }
}

فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

فراغ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    صحيح display_اشاریہ = SDL_Get_Display_اشاریہ(displayID);
    إذا (display_اشاریہ < 0) {
        أرجع;
    }

    display = _this->displays[display_اشاریہ];

    إذا (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_منوال.اندرونی);
    display->desktop_منوال.اندرونی = عدم;
    SDL_free(display->اندرونی);
    display->اندرونی = عدم;
    SDL_free(display);

    إذا (display_اشاریہ < (_this->عدد_displays - 1)) {
        SDL_memmove(&_this->displays[display_اشاریہ], &_this->displays[display_اشاریہ + 1], (_this->عدد_displays - display_اشاریہ - 1) * حجم(_this->displays[display_اشاریہ]));
    }
    --_this->عدد_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحيح *گنتی)
{
    صحيح i;
    SDL_DisplayID *displays;

    إذا (!_this) {
        إذا (گنتی) {
            *گنتی = 0;
        }

        SDL_UninitializedVideo();
        أرجع عدم;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->عدد_displays + 1) * حجم(*displays));
    إذا (displays) {
        إذا (گنتی) {
            *گنتی = _this->عدد_displays;
        }

        لكل (i = 0; i < _this->عدد_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } وإلا {
        إذا (گنتی) {
            *گنتی = 0;
        }
    }
    أرجع displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحيح display_اشاریہ;

    display_اشاریہ = SDL_Get_Display_اشاریہ(displayID);
    إذا (display_اشاریہ < 0) {
        أرجع عدم;
    }
    أرجع _this->displays[display_اشاریہ];
}

ساكن SDL_DisplayID Get_Display_For_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        displayID = کھڑکی->current_fullscreen_منوال.displayID;
    }

    إذا (!displayID) {
        displayID = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    أرجع SDL_GetVideoDisplay(Get_Display_For_کھڑکی(کھڑکی));
}

SDL_DisplayID SDL_GetPrimaryDisplay(فراغ)
{
    إذا (!_this || _this->عدد_displays == 0) {
        SDL_UninitializedVideo();
        أرجع 0;
    }
    أرجع _this->displays[0]->id;
}

صحيح SDL_Get_Display_اشاریہ(SDL_DisplayID displayID)
{
    صحيح display_اشاریہ;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع -1;
    }

    لكل (display_اشاریہ = 0; display_اشاریہ < _this->عدد_displays; ++display_اشاریہ) {
        إذا (displayID == _this->displays[display_اشاریہ]->id) {
            أرجع display_اشاریہ;
        }
    }
    SDL_سیٹ_Error("Invalid display");
    أرجع -1;
}

SDL_Display_انکڑے *SDL_Get_Display_Driver_انکڑے(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->اندرونی;
}

SDL_Display_انکڑے *SDL_Get_Display_Driver_انکڑے_For_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    أرجع SDL_Get_Display_Driver_انکڑے(Get_Display_For_کھڑکی(کھڑکی));
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
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_اشاریہ(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_منوال->w;
    rect->h = display->current_منوال->h;
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

فراغ SDL_سیٹ_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale)
{
    إذا (scale != display->content_scale) {
        SDL_کھڑکی *کھڑکی;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_بدلیا, 0, 0);

        // Check the windows on this display
        لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            إذا (display->id == کھڑکی->displayID) {
                SDL_Check_کھڑکی_Display_Scale_بدلیا(کھڑکی);
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

فراغ SDL_سیٹ_کھڑکی_HDRProperties(SDL_کھڑکی *کھڑکی, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    إذا (کھڑکی->HDR.HDR_headroom != HDR_clamped.HDR_headroom || کھڑکی->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID کھڑکی_props = SDL_Get_کھڑکی_Properties(کھڑکی);

        SDL_سیٹ_Float_Property(کھڑکی_props, SDL_PROP_کھڑکی_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_سیٹ_Float_Property(کھڑکی_props, SDL_PROP_کھڑکی_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_سیٹ_Boolean_Property(کھڑکی_props, SDL_PROP_کھڑکی_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&کھڑکی->HDR, &HDR_clamped);

        إذا (send_event) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_HDR_STATE_بدلیا, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

فراغ SDL_سیٹ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ثابت bool بدلیا = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	إذا (بدلیا) {
		SDL_سیٹ_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    إذا (بدلیا && !SDL_DriverSendsHDRChanges(_this)) {
        لكل (SDL_کھڑکی *w = display->device->windows; w; w = w->اگلا) {
            إذا (Get_Display_For_کھڑکی(w) == display->id) {
                SDL_سیٹ_کھڑکی_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ساكن فراغ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    إذا (display->عدد_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ساكن ثابت SDL_Display_منوال *SDL_Get_Fullscreen_منوال_میل(ثابت SDL_Display_منوال *منوال)
{
    SDL_VideoDisplay *display;
    SDL_Display_منوال fullscreen_منوال;

    إذا (منوال->w <= 0 || منوال->h <= 0) {
        // Use the desktop mode
        أرجع عدم;
    }

    SDL_memcpy(&fullscreen_منوال, منوال, حجم(fullscreen_منوال));
    إذا (fullscreen_منوال.displayID == 0) {
        fullscreen_منوال.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_منوال(&fullscreen_منوال);

    منوال = عدم;

    display = SDL_GetVideoDisplay(fullscreen_منوال.displayID);
    إذا (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        إذا (!منوال) {
            لكل (صحيح i = 0; i < display->عدد_fullscreen_modes; ++i) {
                إذا (SDL_memcmp(&fullscreen_منوال, &display->fullscreen_modes[i], حجم(fullscreen_منوال)) == 0) {
                    منوال = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }

        // Search for a mode with the same characteristics
        إذا (!منوال) {
            لكل (صحيح i = 0; i < display->عدد_fullscreen_modes; ++i) {
                إذا (cmpmodes(&fullscreen_منوال, &display->fullscreen_modes[i]) == 0) {
                    منوال = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }
    }
    أرجع منوال;
}

bool SDL_جوڑو_Fullscreen_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال)
{
    SDL_Display_منوال *modes;
    SDL_Display_منوال new_منوال;
    صحيح i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_منوال, منوال, حجم(new_منوال));
    new_منوال.displayID = display->id;
    SDL_Finalize_Display_منوال(&new_منوال);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->عدد_fullscreen_modes;
    لكل (i = 0; i < nmodes; ++i) {
        إذا (cmpmodes(&new_منوال, &modes[i]) == 0) {
            أرجع false;
        }
    }

    // Go ahead and add the new mode
    إذا (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_منوال *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        إذا (!modes) {
            أرجع false;
        }

        إذا (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            لكل (i = 0; i < nmodes; ++i) {
                إذا (display->current_منوال == &display->fullscreen_modes[i]) {
                    display->current_منوال = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->عدد_fullscreen_modes++], &new_منوال, حجم(new_منوال));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->عدد_fullscreen_modes,
              حجم(SDL_Display_منوال), cmpmodes);

    أرجع true;
}

فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحيح i;

    لكل (i = display->عدد_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].اندرونی);
        display->fullscreen_modes[i].اندرونی = عدم;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = عدم;
    display->عدد_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_منوال = &display->desktop_منوال;
}

SDL_Display_منوال **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحيح *گنتی)
{
    صحيح i;
    صحيح عدد_modes;
    SDL_Display_منوال **نتیجہ;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    إذا (گنتی) {
        *گنتی = 0;
    }

    CHECK_DISPLAY_MAGIC(display, عدم);

    SDL_UpdateFullscreenDisplayModes(display);

    عدد_modes = display->عدد_fullscreen_modes;
    نتیجہ = (SDL_Display_منوال **)SDL_malloc((عدد_modes + 1) * حجم(*نتیجہ) + عدد_modes * حجم(**نتیجہ));
    إذا (نتیجہ) {
        SDL_Display_منوال *modes = (SDL_Display_منوال *)((Uint8 *)نتیجہ + ((عدد_modes + 1) * حجم(*نتیجہ)));
        إذا (عدد_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, عدد_modes * حجم(*modes));
        }
        لكل (i = 0; i < عدد_modes; ++i) {
            نتیجہ[i] = modes++;
        }
        نتیجہ[i] = عدم;

        إذا (گنتی) {
            *گنتی = عدد_modes;
        }
    } وإلا {
        إذا (گنتی) {
            *گنتی = 0;
        }
    }
    أرجع نتیجہ;
}

bool SDL_Get_Closest_Fullscreen_Display_منوال(SDL_DisplayID displayID, صحيح w, صحيح h, عائم refresh_شرح, bool include_بلند_density_modes, SDL_Display_منوال *نتیجہ)
{
    CHECK_PARAM(!نتیجہ) {
        أرجع SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_Display_منوال *منوال, *closest = عدم;
    عائم aspect_تناسب;
    صحيح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(نتیجہ);

    CHECK_DISPLAY_MAGIC(display, false);

    إذا (h > 0) {
        aspect_تناسب = (عائم)w / h;
    } وإلا {
        aspect_تناسب = 1.0f;
    }

    إذا (refresh_شرح == 0.0f) {
        refresh_شرح = display->desktop_منوال.refresh_شرح;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    لكل (i = 0; i < display->عدد_fullscreen_modes; ++i) {
        منوال = &display->fullscreen_modes[i];

        إذا (w > منوال->w) {
            // Out of sorted modes large enough here
            اكسر;
        }
        إذا (h > منوال->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            استمر;
        }
        إذا (منوال->pixel_density > 1.0f && !include_بلند_density_modes) {
            استمر;
        }
        إذا (closest) {
            عائم current_aspect_تناسب = (عائم)منوال->w / منوال->h;
            عائم closest_aspect_تناسب = (عائم)closest->w / closest->h;
            إذا (SDL_fabsf(aspect_تناسب - closest_aspect_تناسب) < SDL_fabsf(aspect_تناسب - current_aspect_تناسب)) {
                // The mode we already found has a better aspect ratio match
                استمر;
            }

            إذا (منوال->w == closest->w && منوال->h == closest->h) {
                إذا (SDL_fabsf(closest->refresh_شرح - refresh_شرح) < SDL_fabsf(منوال->refresh_شرح - refresh_شرح)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    استمر;
                }
                إذا (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(منوال->format)) {
                    // Prefer the highest color depth
                    استمر;
                }
            }
        }

        closest = منوال;
    }
    إذا (!closest) {
        أرجع SDL_سیٹ_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(نتیجہ, closest);

    أرجع true;
}

ساكن bool Display_منوال_بدلیا(ثابت SDL_Display_منوال *old_منوال, ثابت SDL_Display_منوال *new_منوال)
{
    أرجع ((old_منوال->displayID && old_منوال->displayID != new_منوال->displayID) ||
            (old_منوال->format && old_منوال->format != new_منوال->format) ||
            (old_منوال->w && old_منوال->h && (old_منوال->w != new_منوال->w ||old_منوال->h != new_منوال->h)) ||
            (old_منوال->pixel_density != 0.0f && old_منوال->pixel_density != new_منوال->pixel_density) ||
            (old_منوال->refresh_شرح != 0.0f && old_منوال->refresh_شرح != new_منوال->refresh_شرح));
}

فراغ SDL_سیٹ_Desktop_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال)
{
    SDL_Display_منوال آخری_منوال;

    إذا (display->fullscreen_سرگرم) {
        // This is a temporary mode change, don't save the desktop mode
        أرجع;
    }

    SDL_copyp(&آخری_منوال, &display->desktop_منوال);

    SDL_free(display->desktop_منوال.اندرونی);
    SDL_copyp(&display->desktop_منوال, منوال);
    display->desktop_منوال.displayID = display->id;
    SDL_Finalize_Display_منوال(&display->desktop_منوال);

    إذا (Display_منوال_بدلیا(&آخری_منوال, &display->desktop_منوال)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_منوال_بدلیا, منوال->w, منوال->h);
        إذا (display->current_منوال == &display->desktop_منوال) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_منوال_بدلیا, منوال->w, منوال->h);
        }
    }
}

ثابت SDL_Display_منوال *SDL_Get_Desktop_Display_منوال(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع &display->desktop_منوال;
}

فراغ SDL_سیٹ_Current_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال)
{
    SDL_Display_منوال آخری_منوال;

    إذا (display->current_منوال) {
        SDL_copyp(&آخری_منوال, display->current_منوال);
    } وإلا {
        SDL_zero(آخری_منوال);
    }

    display->current_منوال = منوال;

    إذا (Display_منوال_بدلیا(&آخری_منوال, منوال)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_منوال_بدلیا, منوال->w, منوال->h);
    }
}

ثابت SDL_Display_منوال *SDL_Get_Current_Display_منوال(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->current_منوال;
}

bool SDL_سیٹ_Display_منوال_For_Display(SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    إذا (SDL_منوال_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        أرجع true;
    }

    إذا (!منوال) {
        منوال = &display->desktop_منوال;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#جے_بنا_تعریف SDL_PLATFORM_RISCOS
    إذا (منوال == display->current_منوال) {
        أرجع true;
    }
#جے_انت

    // Actually change the display mode
    إذا (_this->سیٹ_Display_منوال) {
        bool نتیجہ;

        _this->setting_display_منوال = true;
        نتیجہ = _this->سیٹ_Display_منوال(_this, display, منوال);
        _this->setting_display_منوال = false;
        إذا (!نتیجہ) {
            أرجع false;
        }
    }

    SDL_سیٹ_Current_Display_منوال(display, منوال);

    أرجع true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساكن فراغ SDL_Get_Closest_نقطہ_On_Rect(ثابت SDL_Rect *rect, SDL_نقطہ *نقطہ)
{
    ثابت صحيح دایاں = rect->x + rect->w - 1;
    ثابت صحيح bottom = rect->y + rect->h - 1;

    إذا (نقطہ->x < rect->x) {
        نقطہ->x = rect->x;
    } وإلا إذا (نقطہ->x > دایاں) {
        نقطہ->x = دایاں;
    }

    إذا (نقطہ->y < rect->y) {
        نقطہ->y = rect->y;
    } وإلا إذا (نقطہ->y > bottom) {
        نقطہ->y = bottom;
    }
}

ساكن SDL_DisplayID GetDisplayForRect(صحيح x, صحيح y, صحيح w, صحيح h)
{
    صحيح i, dist;
    SDL_DisplayID closest = 0;
    صحيح closest_dist = 0x7FFFFFFF;
    SDL_نقطہ closest_نقطہ_on_display;
    SDL_نقطہ delta;
    SDL_نقطہ center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    إذا (_this) {
        لكل (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            إذا (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, عدم)) {
                أرجع display->id;
            }

            // Snap window center to the display rect
            closest_نقطہ_on_display = center;
            SDL_Get_Closest_نقطہ_On_Rect(&display_rect, &closest_نقطہ_on_display);

            delta.x = center.x - closest_نقطہ_on_display.x;
            delta.y = center.y - closest_نقطہ_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            إذا (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    إذا (closest == 0) {
        SDL_سیٹ_Error("Couldn't find any displays");
    }

    أرجع closest;
}

فراغ SDL_Relative_منزل_Global_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y)
{
    SDL_کھڑکی *w;

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Calculate the total offset of the popup from the parents
        لكل (w = کھڑکی->ماپا; w; w = w->ماپا) {
            rel_x += w->x;
            rel_y += w->y;

            إذا (!SDL_کھڑکی_IS_POPUP(w)) {
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

فراغ SDL_Global_منزل_Relative_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y)
{
    SDL_کھڑکی *w;

    إذا (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Convert absolute window coordinates to relative for a popup
        لكل (w = کھڑکی->ماپا; w; w = w->ماپا) {
            abs_x -= w->x;
            abs_y -= w->y;

            إذا (!SDL_کھڑکی_IS_POPUP(w)) {
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

SDL_DisplayID SDL_Get_Display_For_نقطہ(ثابت SDL_نقطہ *نقطہ)
{
    CHECK_PARAM(!نقطہ) {
        SDL_InvalidParamError("point");
        أرجع 0;
    }

    أرجع GetDisplayForRect(نقطہ->x, نقطہ->y, 1, 1);
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
    لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
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

SDL_DisplayID SDL_Get_Display_For_کھڑکی_Position(SDL_کھڑکی *کھڑکی)
{
    صحيح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    إذا (_this->Get_Display_For_کھڑکی) {
        displayID = _this->Get_Display_For_کھڑکی(_this, کھڑکی);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_منزل_Global_For_کھڑکی(کھڑکی, کھڑکی->x, کھڑکی->y, &x, &y);

    إذا (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } وإلا {
            displayID = GetDisplayForRect(x, y, کھڑکی->w, کھڑکی->h);
        }
    }
    إذا (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_DisplayID displayID = 0;

    CHECK_کھڑکی_MAGIC(کھڑکی, عدم);

    // An explicit fullscreen display overrides all
    إذا (کھڑکی->current_fullscreen_منوال.displayID) {
        displayID = کھڑکی->current_fullscreen_منوال.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    إذا (!displayID) {
        displayID = کھڑکی->pending_displayID;
    }
    إذا (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحيح x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->x;
        ثابت صحيح y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->y;
        ثابت صحيح w = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : کھڑکی->w;
        ثابت صحيح h = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : کھڑکی->h;

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

#تعریف_کرو SDL_PROP_SDL2_COMPAT_کھڑکی_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID کھڑکی_props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_کھڑکی(کھڑکی);
    إذا (fs_display) {
        SDL_سیٹ_نمبر_Property(کھڑکی_props, SDL_PROP_SDL2_COMPAT_کھڑکی_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } وإلا {
        SDL_ClearProperty(کھڑکی_props, SDL_PROP_SDL2_COMPAT_کھڑکی_PREFERRED_FULLSCREEN_DISPLAY);
    }

    أرجع Get_Display_For_کھڑکی(کھڑکی);
}

ساكن فراغ SDL_Check_کھڑکی_Display_بدلیا(SDL_کھڑکی *کھڑکی)
{
    إذا (SDL_SendsDisplayChanges(_this)) {
        أرجع;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);

    إذا (displayID != کھڑکی->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect کھڑکی_rect;
        SDL_Rect old_overlap, new_overlap;

        إذا (SDL_GetDisplayBounds(کھڑکی->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            کھڑکی_rect.x = کھڑکی->x;
            کھڑکی_rect.y = کھڑکی->y;
            کھڑکی_rect.w = کھڑکی->w;
            کھڑکی_rect.h = کھڑکی->h;

            إذا (SDL_GetRectIntersection(&old_bounds, &کھڑکی_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &کھڑکی_rect, &new_overlap)) {
                صحيح old_area = old_overlap.w * old_overlap.h;
                صحيح new_area = new_overlap.w * new_overlap.h;
                عائم new_overlap_تناسب = (new_area / ((عائم)old_area + new_area));
                إذا (new_overlap_تناسب < 0.80) {
                    أرجع;
                }
            }
        }
    }

    إذا (displayID != کھڑکی->displayID) {
        صحيح i, display_اشاریہ;

        // Sanity check our fullscreen windows
        display_اشاریہ = SDL_Get_Display_اشاریہ(displayID);
        لكل (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            إذا (display->fullscreen_کھڑکی == کھڑکی) {
                إذا (display_اشاریہ != i) {
                    إذا (display_اشاریہ < 0) {
                        display_اشاریہ = i;
                    } وإلا {
                        SDL_VideoDisplay *new_display = _this->displays[display_اشاریہ];

                        // The window was moved to a different display
                        إذا (new_display->fullscreen_کھڑکی &&
                            new_display->fullscreen_کھڑکی != کھڑکی) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_کھڑکی(new_display->fullscreen_کھڑکی);
                        }
                        new_display->fullscreen_کھڑکی = کھڑکی;
                        display->fullscreen_کھڑکی = عدم;
                    }
                }
                اكسر;
            }
        }

        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DISPLAY_بدلیا, (صحيح)displayID, 0);
    }
}

عائم SDL_Get_کھڑکی_Pixel_Density(SDL_کھڑکی *کھڑکی)
{
    صحيح کھڑکی_w, کھڑکی_h, pixel_w, pixel_h;
    عائم pixel_density = 1.0f;

    CHECK_کھڑکی_MAGIC(کھڑکی, 0.0f);

    إذا (SDL_Get_کھڑکی_ناپ(کھڑکی, &کھڑکی_w, &کھڑکی_h) &&
        SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &pixel_w, &pixel_h)) {
        pixel_density = (عائم)pixel_w / کھڑکی_w;
    }
    أرجع pixel_density;
}

عائم SDL_Get_کھڑکی_Display_Scale(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0.0f);

    أرجع کھڑکی->display_scale;
}

ساكن فراغ SDL_Check_کھڑکی_Display_Scale_بدلیا(SDL_کھڑکی *کھڑکی)
{
    عائم display_scale;

    إذا (_this->Get_کھڑکی_Content_Scale) {
        display_scale = _this->Get_کھڑکی_Content_Scale(_this, کھڑکی);
    } وإلا {
        ثابت عائم pixel_density = SDL_Get_کھڑکی_Pixel_Density(کھڑکی);
        ثابت عائم content_scale = SDL_GetDisplayContentScale(کھڑکی->displayID);

        display_scale = pixel_density * content_scale;
    }

    إذا (display_scale != کھڑکی->display_scale) {
        کھڑکی->display_scale = display_scale;
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DISPLAY_SCALE_بدلیا, 0, 0);
    }
}

bool SDL_Update_Fullscreen_منوال(SDL_کھڑکی *کھڑکی, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = عدم;
    SDL_Display_منوال *منوال = عدم;
    صحيح i;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    کھڑکی->fullscreen_exclusive = false;
    کھڑکی->update_fullscreen_on_display_بدلیا = false;

    // If we are in the process of hiding don't go back to fullscreen
    إذا (کھڑکی->is_destroying || کھڑکی->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    إذا (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_کھڑکی(کھڑکی);
        إذا (!display) {
            // This should never happen, but it did...
            اذهب پورا;
        }
    } وإلا {
        لكل (i = 0; i < _this->عدد_displays; ++i) {
            display = _this->displays[i];
            إذا (display->fullscreen_کھڑکی == کھڑکی) {
                اكسر;
            }
        }
        إذا (!display || i == _this->عدد_displays) {
            // Already not fullscreen on any display
            display = عدم;
        }
    }

    إذا (fullscreen) {
        منوال = (SDL_Display_منوال *)SDL_Get_کھڑکی_Fullscreen_منوال(کھڑکی);
        إذا (منوال) {
            کھڑکی->fullscreen_exclusive = true;
        } وإلا {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(کھڑکی->current_fullscreen_منوال);
        }
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (کھڑکی->is_destroying && !کھڑکی->آخری_fullscreen_exclusive_display) {
            کھڑکی->fullscreen_exclusive = false;
            إذا (display) {
                display->fullscreen_کھڑکی = عدم;
            }
            اذهب پورا;
        }
        إذا (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            إذا (fullscreen && Cocoa_Is_کھڑکی_وچ_Fullscreen_Space(کھڑکی) && !کھڑکی->آخری_fullscreen_exclusive_display && کھڑکی->fullscreen_exclusive) {
                إذا (!Cocoa_سیٹ_کھڑکی_Fullscreen_Space(کھڑکی, false, true)) {
                    اذهب error;
                }
            } وإلا إذا (fullscreen && کھڑکی->آخری_fullscreen_exclusive_display && !کھڑکی->fullscreen_exclusive) {
                لكل (i = 0; i < _this->عدد_displays; ++i) {
                    SDL_VideoDisplay *آخری_display = _this->displays[i];
                    إذا (آخری_display->fullscreen_کھڑکی == کھڑکی) {
                        SDL_سیٹ_Display_منوال_For_Display(آخری_display, عدم);
                        إذا (_this->سیٹ_کھڑکی_Fullscreen) {
                            _this->سیٹ_کھڑکی_Fullscreen(_this, کھڑکی, آخری_display, false);
                        }
                        آخری_display->fullscreen_کھڑکی = عدم;
                    }
                }
            }

            إذا (Cocoa_سیٹ_کھڑکی_Fullscreen_Space(کھڑکی, !!fullscreen, syncHint)) {
                اذهب پورا;
            }
        }
    }
#جے_انت

    إذا (display) {
        // Restore the video mode on other displays if needed
        لكل (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            إذا (other != display && other->fullscreen_کھڑکی == کھڑکی) {
                SDL_سیٹ_Display_منوال_For_Display(other, عدم);
                other->fullscreen_کھڑکی = عدم;
            }
        }
    }

    إذا (fullscreen) {
        صحيح منوال_w = 0, منوال_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        إذا (display->fullscreen_کھڑکی &&
            display->fullscreen_کھڑکی != کھڑکی) {
            SDL_Minimize_کھڑکی(display->fullscreen_کھڑکی);
        }

        display->fullscreen_سرگرم = کھڑکی->fullscreen_exclusive;

        إذا (!SDL_سیٹ_Display_منوال_For_Display(display, منوال)) {
            اذهب error;
        }
        إذا (commit) {
            SDL_Fullscreen_نتیجہ ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->سیٹ_کھڑکی_Fullscreen) {
                ret = _this->سیٹ_کھڑکی_Fullscreen(_this, کھڑکی, display, fullscreen);
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_ENTER_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_سرگرم = false;
                اذهب error;
            }
        }

        إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
            display->fullscreen_کھڑکی = کھڑکی;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                إذا (منوال) {
                    منوال_w = منوال->w;
                    منوال_h = منوال->h;
                    SDL_GetDisplayBounds(منوال->displayID, &displayRect);
                } وإلا {
                    منوال_w = display->desktop_منوال.w;
                    منوال_h = display->desktop_منوال.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                إذا (کھڑکی->w != منوال_w || کھڑکی->h != منوال_h) {
                    resized = true;
                }

                SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, displayRect.x, displayRect.y);

                إذا (resized) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, منوال_w, منوال_h);
                } وإلا {
                    SDL_On_کھڑکی_Resized(کھڑکی);
                }
            }
        }
    } وإلا {
        bool resized = false;

        // Restore the desktop mode
        إذا (display) {
            display->fullscreen_سرگرم = false;

            SDL_سیٹ_Display_منوال_For_Display(display, عدم);
        }
        إذا (commit) {
            SDL_Fullscreen_نتیجہ ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->سیٹ_کھڑکی_Fullscreen) {
                SDL_VideoDisplay *بھریا_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_کھڑکی(کھڑکی);
                إذا (بھریا_screen_display) {
                    ret = _this->سیٹ_کھڑکی_Fullscreen(_this, کھڑکی, بھریا_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                اذهب error;
            }
        }

        إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            إذا (display) {
                display->fullscreen_کھڑکی = عدم;
            }

            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, کھڑکی->windowed.x, کھڑکی->windowed.y);
                إذا (resized) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->windowed.w, کھڑکی->windowed.h);
                } وإلا {
                    SDL_On_کھڑکی_Resized(کھڑکی);
                }
            }
        }
    }

پورا:
    کھڑکی->آخری_fullscreen_exclusive_display = display && (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && کھڑکی->fullscreen_exclusive ? display->id : 0;
    أرجع true;

error:
    إذا (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    أرجع false;
}

bool SDL_سیٹ_کھڑکی_Fullscreen_منوال(SDL_کھڑکی *کھڑکی, ثابت SDL_Display_منوال *منوال)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (منوال) {
        إذا (!SDL_Get_Fullscreen_منوال_میل(منوال)) {
            أرجع SDL_سیٹ_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&کھڑکی->requested_fullscreen_منوال, منوال);
    } وإلا {
        SDL_zero(کھڑکی->requested_fullscreen_منوال);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&کھڑکی->current_fullscreen_منوال, &کھڑکی->requested_fullscreen_منوال);

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_کھڑکی_وچ_Fullscreen_Space_Transition(کھڑکی)) {
        SDL_Sync_کھڑکی(کھڑکی);
    }
#جے_انت
    إذا (SDL_کھڑکی_FULLSCREEN_VISIBLE(کھڑکی)) {
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(کھڑکی);
    }

    أرجع true;
}

ثابت SDL_Display_منوال *SDL_Get_کھڑکی_Fullscreen_منوال(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, عدم);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, عدم);

    إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        أرجع SDL_Get_Fullscreen_منوال_میل(&کھڑکی->current_fullscreen_منوال);
    } وإلا {
        أرجع SDL_Get_Fullscreen_منوال_میل(&کھڑکی->requested_fullscreen_منوال);
    }
}

فراغ *SDL_Get_کھڑکی_ICCProfile(SDL_کھڑکی *کھڑکی, size_t *ناپ)
{
    إذا (!_this->Get_کھڑکی_ICCProfile) {
        SDL_Unsupported();
        أرجع عدم;
    }
    أرجع _this->Get_کھڑکی_ICCProfile(_this, کھڑکی, ناپ);
}

SDL_PixelFormat SDL_Get_کھڑکی_Pixel_Format(SDL_کھڑکی *کھڑکی)
{
    SDL_DisplayID displayID;
    ثابت SDL_Display_منوال *منوال;

    CHECK_کھڑکی_MAGIC(کھڑکی, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_کھڑکی(کھڑکی);
    منوال = SDL_Get_Current_Display_منوال(displayID);
    إذا (منوال) {
        أرجع منوال->format;
    } وإلا {
        أرجع SDL_PIXELFORMAT_UNKNOWN;
    }
}

#تعریف_کرو CREATE_FLAGS \
    (SDL_کھڑکی_OPENGL | SDL_کھڑکی_BORDERLESS | SDL_کھڑکی_RESIZABLE | SDL_کھڑکی_بلند_PIXEL_DENSITY | SDL_کھڑکی_ALWAYS_ON_چوٹی | SDL_کھڑکی_POPUP_MENU | SDL_کھڑکی_UTILITY | SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_VULKAN | SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_METAL | SDL_کھڑکی_TRANSPARENT | SDL_کھڑکی_NOT_FOCUSABLE | SDL_کھڑکی_FILL_DOCUMENT)

ساكن SDL_INLINE bool IsAcceptingDragAndDrop(فراغ)
{
    إذا (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_متن)) {
        أرجع true;
    }
    أرجع false;
}

// prepare a newly-created window
ساكن SDL_INLINE فراغ PrepareDragAndDropSupport(SDL_کھڑکی *کھڑکی)
{
    إذا (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(کھڑکی, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
فراغ SDL_ToggleDragAndDropSupport(فراغ)
{
    إذا (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_کھڑکی *کھڑکی;
        لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            _this->AcceptDragAndDrop(کھڑکی, enable);
        }
    }
}

SDL_کھڑکی ** SDLCALL SDL_GetWindows(صحيح *گنتی)
{
    إذا (گنتی) {
        *گنتی = 0;
    }

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    SDL_کھڑکی *کھڑکی;
    صحيح عدد_added = 0;
    صحيح عدد_windows = 0;
    لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        ++عدد_windows;
    }

    SDL_کھڑکی **windows = (SDL_کھڑکی **)SDL_malloc((عدد_windows + 1) * حجم(*windows));
    إذا (!windows) {
        أرجع عدم;
    }

    لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        windows[عدد_added++] = کھڑکی;
        إذا (عدد_added == عدد_windows) {
            // Race condition? Multi-threading not supported, ignore it
            اكسر;
        }
    }
    windows[عدد_added] = عدم;

    إذا (گنتی) {
        *گنتی = عدد_added;
    }
    أرجع windows;
}

ساكن فراغ Apply_کھڑکی_Flags(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    إذا (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        إذا (!(flags & (SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_MAXIMIZED))) {
            SDL_Restore_کھڑکی(کھڑکی);
        }
        إذا (flags & SDL_کھڑکی_MAXIMIZED) {
            SDL_Maximize_کھڑکی(کھڑکی);
        }

        SDL_سیٹ_کھڑکی_Fullscreen(کھڑکی, (flags & SDL_کھڑکی_FULLSCREEN) != 0);

        إذا (flags & SDL_کھڑکی_MINIMIZED) {
            SDL_Minimize_کھڑکی(کھڑکی);
        }

        إذا (flags & SDL_کھڑکی_MODAL) {
            SDL_سیٹ_کھڑکی_Modal(کھڑکی, true);
        }

        إذا (flags & SDL_کھڑکی_MOUSE_GRABBED) {
            SDL_سیٹ_کھڑکی_Mouse_Grab(کھڑکی, true);
        }
        إذا (flags & SDL_کھڑکی_KEYBOARD_GRABBED) {
            SDL_سیٹ_کھڑکی_Keyboard_Grab(کھڑکی, true);
        }
    }
}

ساكن فراغ SDL_انت_کھڑکی_Creation(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    PrepareDragAndDropSupport(کھڑکی);

    إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } وإلا {
        Apply_کھڑکی_Flags(کھڑکی, flags);
        إذا (!(flags & SDL_کھڑکی_HIDDEN)) {
            SDL_Show_کھڑکی(کھڑکی);
        }
    }

#إذا defined(SDL_PLATFORM_LINUX)
    إذا (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_سیٹ_کھڑکی_ترقی_State(کھڑکی, SDL_ترقی_STATE_NONE);
        SDL_سیٹ_کھڑکی_ترقی_قدر(کھڑکی, 0.0f);
    }
#جے_انت
}

ساكن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    أرجع SDL_سیٹ_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساكن bool SDL_DllNotSupported(ثابت حرف *name)
{
    أرجع SDL_سیٹ_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ساكن بنية {
    ثابت حرف *property_name;
    SDL_کھڑکی_Flags flag;
    bool invert_قدر;
} SDL_کھڑکی_Flag_Properties[] = {
    { SDL_PROP_کھڑکی_CREATE_ALWAYS_ON_چوٹی_BOOLEAN,      SDL_کھڑکی_ALWAYS_ON_چوٹی,       false },
    { SDL_PROP_کھڑکی_CREATE_BORDERLESS_BOOLEAN,         SDL_کھڑکی_BORDERLESS,          false },
    { SDL_PROP_کھڑکی_CREATE_FOCUSABLE_BOOLEAN,          SDL_کھڑکی_NOT_FOCUSABLE,       true },
    { SDL_PROP_کھڑکی_CREATE_FULLSCREEN_BOOLEAN,         SDL_کھڑکی_FULLSCREEN,          false },
    { SDL_PROP_کھڑکی_CREATE_HIDDEN_BOOLEAN,             SDL_کھڑکی_HIDDEN,              false },
    { SDL_PROP_کھڑکی_CREATE_بلند_PIXEL_DENSITY_BOOLEAN, SDL_کھڑکی_بلند_PIXEL_DENSITY,  false },
    { SDL_PROP_کھڑکی_CREATE_MAXIMIZED_BOOLEAN,          SDL_کھڑکی_MAXIMIZED,           false },
    { SDL_PROP_کھڑکی_CREATE_MENU_BOOLEAN,               SDL_کھڑکی_POPUP_MENU,          false },
    { SDL_PROP_کھڑکی_CREATE_METAL_BOOLEAN,              SDL_کھڑکی_METAL,               false },
    { SDL_PROP_کھڑکی_CREATE_MINIMIZED_BOOLEAN,          SDL_کھڑکی_MINIMIZED,           false },
    { SDL_PROP_کھڑکی_CREATE_MODAL_BOOLEAN,              SDL_کھڑکی_MODAL,               false },
    { SDL_PROP_کھڑکی_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_کھڑکی_MOUSE_GRABBED,       false },
    { SDL_PROP_کھڑکی_CREATE_OPENGL_BOOLEAN,             SDL_کھڑکی_OPENGL,              false },
    { SDL_PROP_کھڑکی_CREATE_RESIZABLE_BOOLEAN,          SDL_کھڑکی_RESIZABLE,           false },
    { SDL_PROP_کھڑکی_CREATE_TRANSPARENT_BOOLEAN,        SDL_کھڑکی_TRANSPARENT,         false },
    { SDL_PROP_کھڑکی_CREATE_TOOLTIP_BOOLEAN,            SDL_کھڑکی_TOOLTIP,             false },
    { SDL_PROP_کھڑکی_CREATE_UTILITY_BOOLEAN,            SDL_کھڑکی_UTILITY,             false },
    { SDL_PROP_کھڑکی_CREATE_VULKAN_BOOLEAN,             SDL_کھڑکی_VULKAN,              false }
};

ساكن SDL_کھڑکی_Flags SDL_Get_کھڑکی_Flag_Properties(SDL_PropertiesID props)
{
    بنانشانی i;
    SDL_کھڑکی_Flags flags = (SDL_کھڑکی_Flags)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_FLAGS_نمبر, 0);

    لكل (i = 0; i < SDL_arraysize(SDL_کھڑکی_Flag_Properties); ++i) {
        إذا (SDL_کھڑکی_Flag_Properties[i].invert_قدر) {
            إذا (!SDL_GetBooleanProperty(props, SDL_کھڑکی_Flag_Properties[i].property_name, true)) {
                flags |= SDL_کھڑکی_Flag_Properties[i].flag;
            }
        } وإلا {
            إذا (SDL_GetBooleanProperty(props, SDL_کھڑکی_Flag_Properties[i].property_name, false)) {
                flags |= SDL_کھڑکی_Flag_Properties[i].flag;
            }
        }
    }
    أرجع flags;
}

SDL_کھڑکی *SDL_Create_کھڑکی_With_Properties(SDL_PropertiesID props)
{
    SDL_کھڑکی *کھڑکی;
    ثابت حرف *title = SDL_GetStringProperty(props, SDL_PROP_کھڑکی_CREATE_TITLE_STRING, عدم);
    صحيح x = (صحيح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_X_نمبر, SDL_WINDOWPOS_UNDEFINED);
    صحيح y = (صحيح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_Y_نمبر, SDL_WINDOWPOS_UNDEFINED);
    صحيح w = (صحيح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_چوڑائی_نمبر, 0);
    صحيح h = (صحيح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_اچائی_نمبر, 0);
    SDL_کھڑکی *ماپا = (SDL_کھڑکی *)SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_CREATE_ماپا_اشارہ_گر, عدم);
    SDL_کھڑکی_Flags flags = SDL_Get_کھڑکی_Flag_Properties(props);
    SDL_کھڑکی_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_کھڑکی_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

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

    إذا ((flags & SDL_کھڑکی_MODAL) && !SDL_ObjectValid(ماپا, SDL_OBJECT_TYPE_کھڑکی)) {
        SDL_سیٹ_Error("Modal windows must specify a parent window");
        أرجع عدم;
    }

    إذا ((flags & (SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_POPUP_MENU)) != 0) {
        إذا (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT)) {
            SDL_Unsupported();
            أرجع عدم;
        }

        // Tooltip and popup menu window must specify a parent window
        إذا (!SDL_ObjectValid(ماپا, SDL_OBJECT_TYPE_کھڑکی)) {
            SDL_سیٹ_Error("Tooltip and popup menu windows must specify a parent window");
            أرجع عدم;
        }

        // Remove invalid flags
        flags &= ~(SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_کھڑکی_UTILITY | SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_POPUP_MENU | SDL_کھڑکی_MODAL);
    إذا (type_flags & (type_flags - 1)) {
        SDL_سیٹ_Error("Conflicting window type flags specified: 0x%.8x", (بنانشانی صحيح)type_flags);
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
        إذا (displayID == 0 || SDL_Get_Display_اشاریہ(displayID) < 0) {
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
    graphics_flags = flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        SDL_سیٹ_Error("Conflicting window graphics flags specified: 0x%.8x", (بنانشانی صحيح)graphics_flags);
        أرجع عدم;
    }

    // Some platforms have certain graphics backends enabled by default
    إذا (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    إذا (flags & SDL_کھڑکی_OPENGL) {
        إذا (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            أرجع عدم;
        }
        إذا (!SDL_GL_لدو_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_کھڑکی_VULKAN) {
        إذا (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            أرجع عدم;
        }
        إذا (!SDL_Vulkan_لدو_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_کھڑکی_METAL) {
        إذا (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            أرجع عدم;
        }
    }

    کھڑکی = (SDL_کھڑکی *)SDL_calloc(1, حجم(*کھڑکی));
    إذا (!کھڑکی) {
        أرجع عدم;
    }
    SDL_سیٹ_Object_Valid(کھڑکی, SDL_OBJECT_TYPE_کھڑکی, true);
    کھڑکی->id = SDL_Get_اگلا_Object_ID();
    کھڑکی->floating.x = کھڑکی->windowed.x = کھڑکی->x = x;
    کھڑکی->floating.y = کھڑکی->windowed.y = کھڑکی->y = y;
    کھڑکی->floating.w = کھڑکی->windowed.w = کھڑکی->w = w;
    کھڑکی->floating.h = کھڑکی->windowed.h = کھڑکی->h = h;
    کھڑکی->undefined_x = undefined_x;
    کھڑکی->undefined_y = undefined_y;
    کھڑکی->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کھڑکی(کھڑکی);
    إذا (display) {
        SDL_سیٹ_کھڑکی_HDRProperties(کھڑکی, &display->HDR, false);
    }

    إذا (flags & SDL_کھڑکی_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        کھڑکی->x = bounds.x;
        کھڑکی->y = bounds.y;
        کھڑکی->w = bounds.w;
        کھڑکی->h = bounds.h;
        کھڑکی->pending_flags |= SDL_کھڑکی_FULLSCREEN;
        flags |= SDL_کھڑکی_FULLSCREEN;
    }

    کھڑکی->flags = ((flags & CREATE_FLAGS) | SDL_کھڑکی_HIDDEN);
    کھڑکی->display_scale = 1.0f;
    کھڑکی->opacity = 1.0f;
    کھڑکی->اگلا = _this->windows;
    کھڑکی->is_destroying = false;
    کھڑکی->displayID = Get_Display_For_کھڑکی(کھڑکی);
    کھڑکی->external_graphics_context = external_graphics_context;
    کھڑکی->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_کھڑکی_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    إذا (!_this->سیٹ_کھڑکی_Fill_Document) {
        کھڑکی->flags &= ~SDL_کھڑکی_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    إذا (_this->windows) {
        _this->windows->prev = کھڑکی;
    }
    _this->windows = کھڑکی;

    // Set the parent before creation.
    SDL_Update_کھڑکی_Hierarchy(کھڑکی, ماپا);

    إذا (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, کھڑکی, props)) {
        SDL_ڈالو_Error();
        SDL_Destroy_کھڑکی(کھڑکی);
        SDL_نکالو_Error();
        أرجع عدم;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#إذا !defined(SDL_PLATFORM_WINDOWS)
    إذا (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
        کھڑکی->flags &= ~SDL_کھڑکی_MINIMIZED;
    }
#جے_انت

    إذا (title) {
        SDL_سیٹ_کھڑکی_Title(کھڑکی, title);
    }
    SDL_انت_کھڑکی_Creation(کھڑکی, flags);

    // Make sure window pixel size is up to date
    SDL_Check_کھڑکی_Pixel_ناپ_بدلیا(کھڑکی);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#جے_انت

    SDL_ClearError();

    أرجع کھڑکی;
}

SDL_کھڑکی *SDL_Create_کھڑکی(ثابت حرف *title, صحيح w, صحيح h, SDL_کھڑکی_Flags flags)
{
    SDL_کھڑکی *کھڑکی;
    SDL_PropertiesID props = SDL_CreateProperties();
    إذا (title && *title) {
        SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_CREATE_TITLE_STRING, title);
    }
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_چوڑائی_نمبر, w);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_اچائی_نمبر, h);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_FLAGS_نمبر, flags);
    کھڑکی = SDL_Create_کھڑکی_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع کھڑکی;
}

SDL_کھڑکی *SDL_Create_Popup_کھڑکی(SDL_کھڑکی *ماپا, صحيح وتھ_x, صحيح وتھ_y, صحيح w, صحيح h, SDL_کھڑکی_Flags flags)
{
    SDL_کھڑکی *کھڑکی;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    إذا (!(flags & (SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_POPUP_MENU))) {
        SDL_سیٹ_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        أرجع عدم;
    }

    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_CREATE_ماپا_اشارہ_گر, ماپا);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_X_نمبر, وتھ_x);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_Y_نمبر, وتھ_y);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_چوڑائی_نمبر, w);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_اچائی_نمبر, h);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_FLAGS_نمبر, flags);
    کھڑکی = SDL_Create_کھڑکی_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع کھڑکی;
}

ساكن bool SDL_Reconfigure_کھڑکی_اندرونی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    إذا (!_this->Reconfigure_کھڑکی) {
        أرجع false;
    }

    ثابت SDL_کھڑکی_Flags graphics_flags = flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_سیٹ_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_کھڑکی_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_کھڑکی_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_کھڑکی_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        إذا (کھڑکی->flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN)) {
            أرجع false;
        }
    } وإلا {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        إذا (!_this->Reconfigure_کھڑکی(_this, کھڑکی, 0)) {
            أرجع false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        إذا (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        کھڑکی->flags &= ~(SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    }

    SDL_Destroy_کھڑکی_Surface(کھڑکی);

    إذا (graphics_flags & SDL_کھڑکی_OPENGL) {
        loaded_opengl = SDL_GL_لدو_Library(عدم);
        إذا (!loaded_opengl) {
            أرجع false;
        }
    } وإلا إذا (graphics_flags & SDL_کھڑکی_VULKAN) {
        loaded_vulkan = SDL_Vulkan_لدو_Library(عدم);
        إذا (!loaded_vulkan) {
            أرجع false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    إذا (!_this->Reconfigure_کھڑکی(_this, کھڑکی, graphics_flags)) {
        إذا (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        إذا (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        أرجع false;
    }

    کھڑکی->flags |= graphics_flags;

    أرجع true;
}

bool SDL_Recreate_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_لدو = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_لدو = false;
    SDL_کھڑکی_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_سیٹ_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_کھڑکی_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_کھڑکی_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_کھڑکی_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_کھڑکی_EXTERNAL;
    } وإلا {
        flags &= ~SDL_کھڑکی_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    إذا (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        SDL_سیٹ_کھڑکی_Modal(کھڑکی, false);
    }

    // Restore video mode, etc.
    إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        ثابت bool restore_on_show = کھڑکی->restore_on_show;
        SDL_Hide_کھڑکی(کھڑکی);
        کھڑکی->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_کھڑکی_Surface(کھڑکی);

    إذا ((کھڑکی->flags & SDL_کھڑکی_OPENGL) != (flags & SDL_کھڑکی_OPENGL)) {
        إذا (flags & SDL_کھڑکی_OPENGL) {
            need_gl_لدو = true;
        } وإلا {
            need_gl_unload = true;
        }
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        need_gl_unload = true;
        need_gl_لدو = true;
    }

    إذا ((کھڑکی->flags & SDL_کھڑکی_VULKAN) != (flags & SDL_کھڑکی_VULKAN)) {
        إذا (flags & SDL_کھڑکی_VULKAN) {
            need_vulkan_لدو = true;
        } وإلا {
            need_vulkan_unload = true;
        }
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_لدو = true;
    }

    إذا (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    إذا (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->Destroy_کھڑکی && !(flags & SDL_کھڑکی_EXTERNAL)) {
        _this->Destroy_کھڑکی(_this, کھڑکی);
    }

    إذا (need_gl_لدو) {
        إذا (!SDL_GL_لدو_Library(عدم)) {
            أرجع false;
        }
        loaded_opengl = true;
    }

    إذا (need_vulkan_لدو) {
        إذا (!SDL_Vulkan_لدو_Library(عدم)) {
            أرجع false;
        }
        loaded_vulkan = true;
    }

    کھڑکی->flags = ((flags & CREATE_FLAGS) | SDL_کھڑکی_HIDDEN);
    کھڑکی->is_destroying = false;

    إذا (_this->CreateSDLWindow && !(flags & SDL_کھڑکی_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        کھڑکی->x = کھڑکی->windowed.x = کھڑکی->floating.x;
        کھڑکی->y = کھڑکی->windowed.y = کھڑکی->floating.y;
        کھڑکی->w = کھڑکی->windowed.w = کھڑکی->floating.w;
        کھڑکی->h = کھڑکی->windowed.h = کھڑکی->floating.h;

        إذا (!_this->CreateSDLWindow(_this, کھڑکی, 0)) {
            إذا (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                کھڑکی->flags &= ~SDL_کھڑکی_OPENGL;
            }
            إذا (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                کھڑکی->flags &= ~SDL_کھڑکی_VULKAN;
            }
            أرجع false;
        }
    }

    إذا (flags & SDL_کھڑکی_EXTERNAL) {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;
    }

    إذا (_this->سیٹ_کھڑکی_Title && کھڑکی->title) {
        _this->سیٹ_کھڑکی_Title(_this, کھڑکی);
    }

    إذا (_this->سیٹ_کھڑکی_Icon && کھڑکی->icon) {
        _this->سیٹ_کھڑکی_Icon(_this, کھڑکی, کھڑکی->icon);
    }

    إذا (_this->سیٹ_کھڑکی_Minimum_ناپ && (کھڑکی->min_w || کھڑکی->min_h)) {
        _this->سیٹ_کھڑکی_Minimum_ناپ(_this, کھڑکی);
    }

    إذا (_this->سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ && (کھڑکی->max_w || کھڑکی->max_h)) {
        _this->سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(_this, کھڑکی);
    }

    إذا (_this->سیٹ_کھڑکی_Aspect_تناسب && (کھڑکی->min_aspect > 0.0f || کھڑکی->max_aspect > 0.0f)) {
        _this->سیٹ_کھڑکی_Aspect_تناسب(_this, کھڑکی);
    }

    إذا (کھڑکی->کامیابی_test) {
        _this->سیٹ_کھڑکی_کامیابی_Test(کھڑکی, true);
    }

    SDL_انت_کھڑکی_Creation(کھڑکی, flags);

    أرجع true;
}

bool SDL_Reconfigure_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    إذا (!SDL_Reconfigure_کھڑکی_اندرونی(کھڑکی, flags)) {
        أرجع SDL_Recreate_کھڑکی(کھڑکی, flags);
    }

    أرجع true;
}

bool SDL_HasWindows(فراغ)
{
    أرجع _this && _this->windows;
}

SDL_کھڑکی_ID SDL_Get_کھڑکی_ID(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    أرجع کھڑکی->id;
}

SDL_کھڑکی *SDL_Get_کھڑکی_From_ID(SDL_کھڑکی_ID id)
{
    SDL_کھڑکی *کھڑکی;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (id) {
        لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            إذا (کھڑکی->id == id) {
                أرجع کھڑکی;
            }
        }
    }
    SDL_سیٹ_Error("Invalid window ID");
    أرجع عدم;
}

SDL_کھڑکی *SDL_Get_کھڑکی_ماپا(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, عدم);

    أرجع کھڑکی->ماپا;
}

SDL_PropertiesID SDL_Get_کھڑکی_Properties(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    إذا (کھڑکی->props == 0) {
        کھڑکی->props = SDL_CreateProperties();
    }
    أرجع کھڑکی->props;
}

SDL_کھڑکی_Flags SDL_Get_کھڑکی_Flags(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    أرجع کھڑکی->flags | کھڑکی->pending_flags;
}

bool SDL_سیٹ_کھڑکی_Title(SDL_کھڑکی *کھڑکی, ثابت حرف *title)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (title == کھڑکی->title) {
        أرجع true;
    }
    إذا (!title) {
        title = "";
    }
    إذا (کھڑکی->title && SDL_strcmp(title, کھڑکی->title) == 0) {
        أرجع true;
    }

    SDL_free(کھڑکی->title);

    کھڑکی->title = SDL_strdup(title);

    إذا (_this->سیٹ_کھڑکی_Title) {
        _this->سیٹ_کھڑکی_Title(_this, کھڑکی);
    }
    أرجع true;
}

ثابت حرف *SDL_Get_کھڑکی_Title(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, "");

    أرجع کھڑکی->title ? کھڑکی->title : "";
}

bool SDL_سیٹ_کھڑکی_Icon(SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    CHECK_PARAM(!icon) {
        أرجع SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(کھڑکی->icon);

    // Convert the icon into ARGB8888
    کھڑکی->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    إذا (!کھڑکی->icon) {
        أرجع false;
    }

    إذا (!_this->سیٹ_کھڑکی_Icon) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->سیٹ_کھڑکی_Icon(_this, کھڑکی, کھڑکی->icon);
}

bool SDL_سیٹ_کھڑکی_Position(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y)
{
    SDL_DisplayID original_displayID;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    ثابت صحيح w = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : کھڑکی->windowed.w;
    ثابت صحيح h = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : کھڑکی->windowed.h;

    original_displayID = Get_Display_For_کھڑکی(کھڑکی);
    کھڑکی->pending_displayID = 0;

    إذا (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = کھڑکی->windowed.x;
    }
    إذا (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = کھڑکی->windowed.y;
    }
    إذا (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        إذا (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وإلا إذا (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        إذا (displayID == 0 || SDL_Get_Display_اشاریہ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        کھڑکی->pending_displayID = displayID;

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
        کھڑکی->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    کھڑکی->pending.x = x;
    کھڑکی->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    إذا (!_this->Sync_کھڑکی && (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        کھڑکی->floating.x = کھڑکی->windowed.x = x;
        کھڑکی->floating.y = کھڑکی->windowed.y = y;
    }
    کھڑکی->undefined_x = false;
    کھڑکی->undefined_y = false;
    کھڑکی->آخری_position_pending = true;

    إذا (_this->سیٹ_کھڑکی_Position) {
        ثابت bool نتیجہ = _this->سیٹ_کھڑکی_Position(_this, کھڑکی);
        إذا (نتیجہ) {
            SDL_SyncIfRequired(کھڑکی);
        }
        أرجع نتیجہ;
    }

    أرجع SDL_Unsupported();
}

bool SDL_Get_کھڑکی_Position(SDL_کھڑکی *کھڑکی, صحيح *x, صحيح *y)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

#جے_تعریف_شدہ SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#وإلا
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) != 0);
#جے_انت
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
        displayID = Get_Display_For_کھڑکی(کھڑکی);
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
        ثابت bool use_pending = (کھڑکی->flags & SDL_کھڑکی_HIDDEN) && کھڑکی->آخری_position_pending;
        إذا (x) {
            *x = use_pending ? کھڑکی->pending.x : کھڑکی->x;
        }
        إذا (y) {
            *y = use_pending ? کھڑکی->pending.y : کھڑکی->y;
        }
    }
    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Bordered(SDL_کھڑکی *کھڑکی, bool bordered)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_Bordered) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS);
    إذا (want != have) {
        إذا (want) {
            کھڑکی->flags &= ~SDL_کھڑکی_BORDERLESS;
        } وإلا {
            کھڑکی->flags |= SDL_کھڑکی_BORDERLESS;
        }
        _this->سیٹ_کھڑکی_Bordered(_this, کھڑکی, want);
    }

    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Resizable(SDL_کھڑکی *کھڑکی, bool resizable)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_Resizable) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((کھڑکی->flags & SDL_کھڑکی_RESIZABLE) != 0);
    إذا (want != have) {
        إذا (want) {
            کھڑکی->flags |= SDL_کھڑکی_RESIZABLE;
        } وإلا {
            کھڑکی->flags &= ~SDL_کھڑکی_RESIZABLE;
            SDL_copyp(&کھڑکی->windowed, &کھڑکی->floating);
        }
        _this->سیٹ_کھڑکی_Resizable(_this, کھڑکی, want);
    }

    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Always_On_چوٹی(SDL_کھڑکی *کھڑکی, bool on_چوٹی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_Always_On_چوٹی) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = on_چوٹی;
    ثابت bool have = ((کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) != 0);
    إذا (want != have) {
        إذا (want) {
            کھڑکی->flags |= SDL_کھڑکی_ALWAYS_ON_چوٹی;
        } وإلا {
            کھڑکی->flags &= ~SDL_کھڑکی_ALWAYS_ON_چوٹی;
        }
        _this->سیٹ_کھڑکی_Always_On_چوٹی(_this, کھڑکی, want);
    }

    أرجع true;
}

bool SDL_سیٹ_کھڑکی_ناپ(SDL_کھڑکی *کھڑکی, صحيح w, صحيح h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

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
    إذا (کھڑکی->max_aspect > 0.0f && new_aspect > کھڑکی->max_aspect) {
        w = (صحيح)SDL_roundf(h * کھڑکی->max_aspect);
    } وإلا إذا (کھڑکی->min_aspect > 0.0f && new_aspect < کھڑکی->min_aspect) {
        h = (صحيح)SDL_roundf(w / کھڑکی->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    إذا (کھڑکی->min_w && w < کھڑکی->min_w) {
        w = کھڑکی->min_w;
    }
    إذا (کھڑکی->max_w && w > کھڑکی->max_w) {
        w = کھڑکی->max_w;
    }
    إذا (کھڑکی->min_h && h < کھڑکی->min_h) {
        h = کھڑکی->min_h;
    }
    إذا (کھڑکی->max_h && h > کھڑکی->max_h) {
        h = کھڑکی->max_h;
    }

    کھڑکی->آخری_ناپ_pending = true;
    کھڑکی->pending.w = w;
    کھڑکی->pending.h = h;

    إذا (_this->سیٹ_کھڑکی_ناپ) {
        _this->سیٹ_کھڑکی_ناپ(_this, کھڑکی);
        SDL_SyncIfRequired(کھڑکی);
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

bool SDL_Get_کھڑکی_ناپ(SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    إذا (w) {
        *w = کھڑکی->w;
    }
    إذا (h) {
        *h = کھڑکی->h;
    }
    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Aspect_تناسب(SDL_کھڑکی *کھڑکی, عائم min_aspect, عائم max_aspect)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    کھڑکی->min_aspect = min_aspect;
    کھڑکی->max_aspect = max_aspect;

    إذا (_this->سیٹ_کھڑکی_Aspect_تناسب) {
        _this->سیٹ_کھڑکی_Aspect_تناسب(_this, کھڑکی);
    }

    // Ensure that window has the correct aspect ratio
    صحيح w = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
    صحيح h = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
    أرجع SDL_سیٹ_کھڑکی_ناپ(کھڑکی, w, h);
}

bool SDL_Get_کھڑکی_Aspect_تناسب(SDL_کھڑکی *کھڑکی, عائم *min_aspect, عائم *max_aspect)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (min_aspect) {
        *min_aspect = کھڑکی->min_aspect;
    }
    إذا (max_aspect) {
        *max_aspect = کھڑکی->max_aspect;
    }
    أرجع true;
}

bool SDL_Get_کھڑکی_Borders_ناپ(SDL_کھڑکی *کھڑکی, صحيح *چوٹی, صحيح *بایاں, صحيح *bottom, صحيح *دایاں)
{
    صحيح dummy = 0;

    إذا (!چوٹی) {
        چوٹی = &dummy;
    }
    إذا (!بایاں) {
        بایاں = &dummy;
    }
    إذا (!دایاں) {
        دایاں = &dummy;
    }
    إذا (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *چوٹی = *بایاں = *bottom = *دایاں = 0;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!_this->Get_کھڑکی_Borders_ناپ) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->Get_کھڑکی_Borders_ناپ(_this, کھڑکی, چوٹی, بایاں, bottom, دایاں);
}

bool SDL_Get_کھڑکی_ناپ_وچ_Pixels(SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h)
{
    صحيح filter;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!w) {
        w = &filter;
    }

    إذا (!h) {
        h = &filter;
    }

    إذا (_this->Get_کھڑکی_ناپ_وچ_Pixels) {
        _this->Get_کھڑکی_ناپ_وچ_Pixels(_this, کھڑکی, w, h);
    } وإلا {
        SDL_DisplayID displayID = Get_Display_For_کھڑکی(کھڑکی);
        ثابت SDL_Display_منوال *منوال;

        SDL_Get_کھڑکی_ناپ(کھڑکی, w, h);

        إذا ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && SDL_Get_کھڑکی_Fullscreen_منوال(کھڑکی)) {
            منوال = SDL_Get_Current_Display_منوال(displayID);
        } وإلا {
            منوال = SDL_Get_Desktop_Display_منوال(displayID);
        }
        إذا (منوال) {
            *w = (صحيح)SDL_ceilf(*w * منوال->pixel_density);
            *h = (صحيح)SDL_ceilf(*h * منوال->pixel_density);
        }
    }
    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Minimum_ناپ(SDL_کھڑکی *کھڑکی, صحيح min_w, صحيح min_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_PARAM(min_w < 0) {
        أرجع SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        أرجع SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((کھڑکی->max_w && min_w > کھڑکی->max_w) || (کھڑکی->max_h && min_h > کھڑکی->max_h)) {
        أرجع SDL_سیٹ_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    کھڑکی->min_w = min_w;
    کھڑکی->min_h = min_h;

    إذا (_this->سیٹ_کھڑکی_Minimum_ناپ) {
        _this->سیٹ_کھڑکی_Minimum_ناپ(_this, کھڑکی);
    }

    // Ensure that window is not smaller than minimal size
    صحيح w = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
    صحيح h = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
    أرجع SDL_سیٹ_کھڑکی_ناپ(کھڑکی, w, h);
}

bool SDL_Get_کھڑکی_Minimum_ناپ(SDL_کھڑکی *کھڑکی, صحيح *min_w, صحيح *min_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    إذا (min_w) {
        *min_w = کھڑکی->min_w;
    }
    إذا (min_h) {
        *min_h = کھڑکی->min_h;
    }
    أرجع true;
}

bool SDL_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(SDL_کھڑکی *کھڑکی, صحيح max_w, صحيح max_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_PARAM(max_w < 0) {
        أرجع SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        أرجع SDL_InvalidParamError("max_h");
    }

    إذا ((max_w && max_w < کھڑکی->min_w) ||
        (max_h && max_h < کھڑکی->min_h)) {
        أرجع SDL_سیٹ_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    کھڑکی->max_w = max_w;
    کھڑکی->max_h = max_h;

    إذا (_this->سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ) {
        _this->سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(_this, کھڑکی);
    }

    // Ensure that window is not larger than maximal size
    صحيح w = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
    صحيح h = کھڑکی->آخری_ناپ_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
    أرجع SDL_سیٹ_کھڑکی_ناپ(کھڑکی, w, h);
}

bool SDL_Get_کھڑکی_ودھ_توں_ودھ_ناپ(SDL_کھڑکی *کھڑکی, صحيح *max_w, صحيح *max_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    إذا (max_w) {
        *max_w = کھڑکی->max_w;
    }
    إذا (max_h) {
        *max_h = کھڑکی->max_h;
    }
    أرجع true;
}

bool SDL_Show_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی *بچہ;
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
        أرجع true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    إذا (کھڑکی->ماپا && (کھڑکی->ماپا->flags & SDL_کھڑکی_HIDDEN)) {
        کھڑکی->restore_on_show = true;
        أرجع true;
    }

    إذا (_this->Show_کھڑکی) {
        _this->Show_کھڑکی(_this, کھڑکی);
    } وإلا {
        SDL_سیٹ_Mouse_Focus(کھڑکی);
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);

    // Restore child windows
    لكل (بچہ = کھڑکی->پہلا_بچہ; بچہ; بچہ = بچہ->اگلا_sibling) {
        إذا (!بچہ->restore_on_show && (بچہ->flags & SDL_کھڑکی_HIDDEN)) {
            اكسر;
        }
        SDL_Show_کھڑکی(بچہ);
        بچہ->restore_on_show = false;
    }
    أرجع true;
}

bool SDL_Hide_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی *بچہ;
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->restore_on_show = false;
        أرجع true;
    }

    // Hide all child windows
    لكل (بچہ = کھڑکی->پہلا_بچہ; بچہ; بچہ = بچہ->اگلا_sibling) {
        إذا (بچہ->flags & SDL_کھڑکی_HIDDEN) {
            اكسر;
        }
        SDL_Hide_کھڑکی(بچہ);
        بچہ->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_کھڑکی_Flags pending_نقاب = (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_KEYBOARD_GRABBED | SDL_کھڑکی_MOUSE_GRABBED);
    کھڑکی->pending_flags = (کھڑکی->flags & pending_نقاب);

    کھڑکی->is_hiding = true;
    إذا (_this->Hide_کھڑکی) {
        _this->Hide_کھڑکی(_this, کھڑکی);
    } وإلا {
        SDL_سیٹ_Mouse_Focus(عدم);
        SDL_سیٹ_Keyboard_Focus(عدم);
    }
    کھڑکی->is_hiding = false;
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
    أرجع true;
}

bool SDL_Raise_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        أرجع true;
    }
    إذا (_this->Raise_کھڑکی) {
        _this->Raise_کھڑکی(_this, کھڑکی);
    }
    أرجع true;
}

bool SDL_Maximize_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (!_this->Maximize_کھڑکی) {
        أرجع SDL_Unsupported();
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        أرجع SDL_سیٹ_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->pending_flags |= SDL_کھڑکی_MAXIMIZED;
        أرجع true;
    }

    _this->Maximize_کھڑکی(_this, کھڑکی);
    SDL_SyncIfRequired(کھڑکی);
    أرجع true;
}

bool SDL_Minimize_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (!_this->Minimize_کھڑکی) {
        أرجع SDL_Unsupported();
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->pending_flags |= SDL_کھڑکی_MINIMIZED;
        أرجع true;
    }

    _this->Minimize_کھڑکی(_this, کھڑکی);
    SDL_SyncIfRequired(کھڑکی);
    أرجع true;
}

bool SDL_Restore_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (!_this->Restore_کھڑکی) {
        أرجع SDL_Unsupported();
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->pending_flags &= ~(SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED);
        أرجع true;
    }

    _this->Restore_کھڑکی(_this, کھڑکی);
    SDL_SyncIfRequired(کھڑکی);
    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Fullscreen(SDL_کھڑکی *کھڑکی, bool fullscreen)
{
    bool نتیجہ;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        إذا (fullscreen) {
            کھڑکی->pending_flags |= SDL_کھڑکی_FULLSCREEN;
        } وإلا {
            کھڑکی->pending_flags &= ~SDL_کھڑکی_FULLSCREEN;
        }
        أرجع true;
    }

    إذا (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&کھڑکی->current_fullscreen_منوال, &کھڑکی->requested_fullscreen_منوال);
    }

    نتیجہ = SDL_Update_Fullscreen_منوال(کھڑکی, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    إذا (!fullscreen || !نتیجہ) {
        // Clear the current fullscreen mode.
        SDL_zero(کھڑکی->current_fullscreen_منوال);
    }

    إذا (نتیجہ) {
        SDL_SyncIfRequired(کھڑکی);
    }

    أرجع نتیجہ;
}

bool SDL_Sync_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (_this->Sync_کھڑکی) {
        أرجع _this->Sync_کھڑکی(_this, کھڑکی);
    } وإلا {
        أرجع true;
    }
}

ساكن bool ShouldAttemptTextureFramebuffer(فراغ)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    إذا (!_this->Create_کھڑکی_Framebuffer) {
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

ساكن SDL_Surface *SDL_Create_کھڑکی_Framebuffer(SDL_کھڑکی *کھڑکی)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    فراغ *pixels = عدم;
    صحيح pitch = 0;
    bool created_framebuffer = false;
    صحيح w, h;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    إذا (!_this->checked_texture_framebuffer) {
        إذا (ShouldAttemptTextureFramebuffer()) {
            إذا (!SDL_Create_کھڑکی_Texture(_this, کھڑکی, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } وإلا {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_کھڑکی_Framebuffer = SDL_Create_کھڑکی_Texture;
                _this->سیٹ_کھڑکی_Framebuffer_VSync = SDL_سیٹ_کھڑکی_Texture_VSync;
                _this->Get_کھڑکی_Framebuffer_VSync = SDL_Get_کھڑکی_Texture_VSync;
                _this->Update_کھڑکی_Framebuffer = SDL_Update_کھڑکی_Texture;
                _this->Destroy_کھڑکی_Framebuffer = SDL_Destroy_کھڑکی_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    إذا (!created_framebuffer) {
        إذا (!_this->Create_کھڑکی_Framebuffer || !_this->Update_کھڑکی_Framebuffer) {
            SDL_سیٹ_Error("Window framebuffer support not available");
            أرجع عدم;
        }

        إذا (!_this->Create_کھڑکی_Framebuffer(_this, کھڑکی, &format, &pixels, &pitch)) {
            أرجع عدم;
        }
    }

    إذا (کھڑکی->surface) {
        // We may have gone recursive and already created the surface
        أرجع کھڑکی->surface;
    }

    أرجع SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_کھڑکی_Has_Surface(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    أرجع کھڑکی->surface ? true : false;
}

SDL_Surface *SDL_Get_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, عدم);

    إذا (!کھڑکی->surface_valid) {
        إذا (کھڑکی->surface) {
            کھڑکی->surface->اندرونی_flags &= ~SDL_اندرونی_SURFACE_DONTFREE;
            SDL_DestroySurface(کھڑکی->surface);
            کھڑکی->surface = عدم;
        }

        کھڑکی->surface = SDL_Create_کھڑکی_Framebuffer(کھڑکی);
        إذا (کھڑکی->surface) {
            کھڑکی->surface_valid = true;
            کھڑکی->surface->اندرونی_flags |= SDL_اندرونی_SURFACE_DONTFREE;
        }
    }
    أرجع کھڑکی->surface;
}

bool SDL_سیٹ_کھڑکی_Surface_VSync(SDL_کھڑکی *کھڑکی, صحيح vsync)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->سیٹ_کھڑکی_Framebuffer_VSync(_this, کھڑکی, vsync);
}

bool SDL_Get_کھڑکی_Surface_VSync(SDL_کھڑکی *کھڑکی, صحيح *vsync)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!_this->Get_کھڑکی_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->Get_کھڑکی_Framebuffer_VSync(_this, کھڑکی, vsync);
}

bool SDL_Update_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
    SDL_Rect بھریا_rect;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    بھریا_rect.x = 0;
    بھریا_rect.y = 0;
    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &بھریا_rect.w, &بھریا_rect.h);

    أرجع SDL_Update_کھڑکی_Surface_Rects(کھڑکی, &بھریا_rect, 1);
}

bool SDL_Update_کھڑکی_Surface_Rects(SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects,
                                 صحيح numrects)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!کھڑکی->surface_valid) {
        أرجع SDL_سیٹ_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    أرجع _this->Update_کھڑکی_Framebuffer(_this, کھڑکی, rects, numrects);
}

bool SDL_Destroy_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (کھڑکی->surface) {
        کھڑکی->surface->اندرونی_flags &= ~SDL_اندرونی_SURFACE_DONTFREE;
        SDL_DestroySurface(کھڑکی->surface);
        کھڑکی->surface = عدم;
        کھڑکی->surface_valid = false;
    }

    إذا (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        إذا (_this->Destroy_کھڑکی_Framebuffer) {
            _this->Destroy_کھڑکی_Framebuffer(_this, کھڑکی);
        }
    }
    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Opacity(SDL_کھڑکی *کھڑکی, عائم opacity)
{
    bool نتیجہ;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_Opacity) {
        أرجع SDL_Unsupported();
    }

    إذا (opacity < 0.0f) {
        opacity = 0.0f;
    } وإلا إذا (opacity > 1.0f) {
        opacity = 1.0f;
    }

    نتیجہ = _this->سیٹ_کھڑکی_Opacity(_this, کھڑکی, opacity);
    إذا (نتیجہ) {
        کھڑکی->opacity = opacity;
    }

    أرجع نتیجہ;
}

عائم SDL_Get_کھڑکی_Opacity(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, -1.0f);

    أرجع کھڑکی->opacity;
}

bool SDL_سیٹ_کھڑکی_ماپا(SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (ماپا) {
        CHECK_کھڑکی_MAGIC(ماپا, false);
        CHECK_کھڑکی_NOT_POPUP(ماپا, false);
    }

    إذا (کھڑکی == ماپا) {
        أرجع SDL_سیٹ_Error("Cannot set the parent of a window to itself.");
    }

    إذا (!_this->سیٹ_کھڑکی_ماپا) {
        أرجع SDL_Unsupported();
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        أرجع SDL_سیٹ_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    إذا (کھڑکی->ماپا == ماپا) {
        أرجع true;
    }

    ثابت bool ret = _this->سیٹ_کھڑکی_ماپا(_this, کھڑکی, ماپا);
    SDL_Update_کھڑکی_Hierarchy(کھڑکی, ret ? ماپا : عدم);

    أرجع ret;
}

bool SDL_سیٹ_کھڑکی_Modal(SDL_کھڑکی *کھڑکی, bool modal)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_Modal) {
        أرجع SDL_Unsupported();
    }

    إذا (modal) {
        إذا (!کھڑکی->ماپا) {
            أرجع SDL_سیٹ_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        کھڑکی->flags |= SDL_کھڑکی_MODAL;
    } وإلا إذا (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        کھڑکی->flags &= ~SDL_کھڑکی_MODAL;
    } وإلا {
        أرجع true; // Already not modal, so nothing to do.
    }

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        أرجع true;
    }

    أرجع _this->سیٹ_کھڑکی_Modal(_this, کھڑکی, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_کھڑکی *کھڑکی, SDL_کھڑکی **new_focus)
{
    SDL_کھڑکی *focus = کھڑکی->ماپا;
    bool سیٹ_focus = !!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    طالما (SDL_کھڑکی_IS_POPUP(focus) && ((focus->flags & SDL_کھڑکی_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->ماپا;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        إذا (!سیٹ_focus) {
            سیٹ_focus = !!(focus->flags & SDL_کھڑکی_داخلہ_FOCUS);
        }
    }

    *new_focus = focus;
    أرجع سیٹ_focus;
}

bool SDL_ShouldFocusPopup(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی *toplevel_ماپا;
    لكل (toplevel_ماپا = کھڑکی->ماپا; SDL_کھڑکی_IS_POPUP(toplevel_ماپا); toplevel_ماپا = toplevel_ماپا->ماپا) {
    }

    SDL_کھڑکی *current_focus = toplevel_ماپا->keyboard_focus;
    bool لبھیا_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_کھڑکی *w;
    لكل (w = current_focus; w != toplevel_ماپا; w = w->ماپا) {
        إذا (w == کھڑکی) {
            لبھیا_higher_focus = true;
            اكسر;
        }
    }

    أرجع !لبھیا_higher_focus || w == toplevel_ماپا;
}

bool SDL_سیٹ_کھڑکی_Focusable(SDL_کھڑکی *کھڑکی, bool focusable)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE);
    إذا ((want != have) && (_this->سیٹ_کھڑکی_Focusable)) {
        إذا (want) {
            کھڑکی->flags &= ~SDL_کھڑکی_NOT_FOCUSABLE;
        } وإلا {
            کھڑکی->flags |= SDL_کھڑکی_NOT_FOCUSABLE;
        }
        إذا (!_this->سیٹ_کھڑکی_Focusable(_this, کھڑکی, want)) {
            أرجع false;
        }
    }

    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Fill_Document(SDL_کھڑکی *کھڑکی, bool fill)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((کھڑکی->flags & SDL_کھڑکی_FILL_DOCUMENT) != 0);
    إذا ((want != have) && (_this->سیٹ_کھڑکی_Fill_Document)) {
        إذا (!_this->سیٹ_کھڑکی_Fill_Document(_this, کھڑکی, want)) {
            أرجع false;
        } وإلا إذا (want) {
            کھڑکی->flags |= SDL_کھڑکی_FILL_DOCUMENT;
        } وإلا {
            کھڑکی->flags &= ~SDL_کھڑکی_FILL_DOCUMENT;
        }
    }

    أرجع true;
}

فراغ SDL_Update_کھڑکی_Grab(SDL_کھڑکی *کھڑکی)
{
    bool keyboard_grabbed, mouse_grabbed;

    إذا (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
        إذا (SDL_GetMouse()->relative_منوال || (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } وإلا {
            mouse_grabbed = false;
        }

        إذا (کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } وإلا {
            keyboard_grabbed = false;
        }
    } وإلا {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    إذا (mouse_grabbed || keyboard_grabbed) {
        إذا (_this->grabbed_کھڑکی && (_this->grabbed_کھڑکی != کھڑکی)) {
            // stealing a grab from another window!
            _this->grabbed_کھڑکی->flags &= ~(SDL_کھڑکی_MOUSE_GRABBED | SDL_کھڑکی_KEYBOARD_GRABBED);
            إذا (_this->سیٹ_کھڑکی_Mouse_Grab) {
                _this->سیٹ_کھڑکی_Mouse_Grab(_this, _this->grabbed_کھڑکی, false);
            }
            إذا (_this->سیٹ_کھڑکی_Keyboard_Grab) {
                _this->سیٹ_کھڑکی_Keyboard_Grab(_this, _this->grabbed_کھڑکی, false);
            }
        }
        _this->grabbed_کھڑکی = کھڑکی;
    } وإلا إذا (_this->grabbed_کھڑکی == کھڑکی) {
        _this->grabbed_کھڑکی = عدم; // ungrabbing input.
    }

    إذا (_this->سیٹ_کھڑکی_Mouse_Grab) {
        إذا (!_this->سیٹ_کھڑکی_Mouse_Grab(_this, کھڑکی, mouse_grabbed)) {
            کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_GRABBED;
        }
    }
    إذا (_this->سیٹ_کھڑکی_Keyboard_Grab) {
        إذا (!_this->سیٹ_کھڑکی_Keyboard_Grab(_this, کھڑکی, keyboard_grabbed)) {
            کھڑکی->flags &= ~SDL_کھڑکی_KEYBOARD_GRABBED;
        }
    }

    إذا (_this->grabbed_کھڑکی && !(_this->grabbed_کھڑکی->flags & (SDL_کھڑکی_MOUSE_GRABBED | SDL_کھڑکی_KEYBOARD_GRABBED))) {
        _this->grabbed_کھڑکی = عدم;
    }
}

bool SDL_سیٹ_کھڑکی_Keyboard_Grab(SDL_کھڑکی *کھڑکی, bool grabbed)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        إذا (grabbed) {
            کھڑکی->pending_flags |= SDL_کھڑکی_KEYBOARD_GRABBED;
        } وإلا {
            کھڑکی->pending_flags &= ~SDL_کھڑکی_KEYBOARD_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        کھڑکی->flags |= SDL_کھڑکی_KEYBOARD_GRABBED;
    } وإلا {
        کھڑکی->flags &= ~SDL_کھڑکی_KEYBOARD_GRABBED;
    }
    SDL_Update_کھڑکی_Grab(کھڑکی);

    إذا (grabbed && !(کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_سیٹ_کھڑکی_Mouse_Grab(SDL_کھڑکی *کھڑکی, bool grabbed)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        إذا (grabbed) {
            کھڑکی->pending_flags |= SDL_کھڑکی_MOUSE_GRABBED;
        } وإلا {
            کھڑکی->pending_flags &= ~SDL_کھڑکی_MOUSE_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        کھڑکی->flags |= SDL_کھڑکی_MOUSE_GRABBED;
    } وإلا {
        کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_GRABBED;
    }
    SDL_Update_کھڑکی_Grab(کھڑکی);

    إذا (grabbed && !(کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_کھڑکی_Keyboard_Grab(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    أرجع کھڑکی == _this->grabbed_کھڑکی && (_this->grabbed_کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED);
}

bool SDL_Get_کھڑکی_Mouse_Grab(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    أرجع کھڑکی == _this->grabbed_کھڑکی && (_this->grabbed_کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED);
}

SDL_کھڑکی *SDL_Get_Grabbed_کھڑکی(فراغ)
{
    إذا (_this && _this->grabbed_کھڑکی &&
        (_this->grabbed_کھڑکی->flags & (SDL_کھڑکی_MOUSE_GRABBED | SDL_کھڑکی_KEYBOARD_GRABBED)) != 0) {
        أرجع _this->grabbed_کھڑکی;
    } وإلا {
        أرجع عدم;
    }
}

bool SDL_سیٹ_کھڑکی_Mouse_Rect(SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rect)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_Mouse_Rect) {
        أرجع SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    إذا (!rect) {
        rect = &zero;
    }

    إذا (SDL_memcmp(&کھڑکی->mouse_rect, rect, حجم(*rect)) == 0) {
        أرجع true;
    }
    SDL_memcpy(&کھڑکی->mouse_rect, rect, حجم(*rect));

    أرجع _this->سیٹ_کھڑکی_Mouse_Rect(_this, کھڑکی);
}

ثابت SDL_Rect *SDL_Get_کھڑکی_Mouse_Rect(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, عدم);

    إذا (SDL_Rect_خالی_تھاواں(&کھڑکی->mouse_rect)) {
        أرجع عدم;
    } وإلا {
        أرجع &کھڑکی->mouse_rect;
    }
}

bool SDL_سیٹ_کھڑکی_Relative_Mouse_منوال(SDL_کھڑکی *کھڑکی, bool enabled)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    إذا (enabled == SDL_Get_کھڑکی_Relative_Mouse_منوال(کھڑکی)) {
        أرجع true;
    }

    إذا (enabled) {
        کھڑکی->flags |= SDL_کھڑکی_MOUSE_RELATIVE_منوال;
    } وإلا {
        کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_RELATIVE_منوال;
    }

    إذا (!SDL_Update_Relative_Mouse_منوال()) {
        إذا (enabled) {
            کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_RELATIVE_منوال;
        } وإلا {
            کھڑکی->flags |= SDL_کھڑکی_MOUSE_RELATIVE_منوال;
        }
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_کھڑکی_Relative_Mouse_منوال(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (کھڑکی->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

bool SDL_Flash_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (_this->Flash_کھڑکی) {
        أرجع _this->Flash_کھڑکی(_this, کھڑکی, operation);
    }

    أرجع SDL_Unsupported();
}

bool SDL_سیٹ_کھڑکی_ترقی_State(SDL_کھڑکی *کھڑکی, SDL_ترقی_State state)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    CHECK_PARAM(state < SDL_ترقی_STATE_NONE || state > SDL_ترقی_STATE_ERROR) {
        أرجع SDL_InvalidParamError("state");
    }

    کھڑکی->ترقی_state = state;

    إذا (_this->Apply_کھڑکی_ترقی) {
        إذا (!_this->Apply_کھڑکی_ترقی(_this, کھڑکی)) {
            أرجع false;
        }
    }

    أرجع true;
}

SDL_ترقی_State SDL_Get_کھڑکی_ترقی_State(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, SDL_ترقی_STATE_INVALID);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, SDL_ترقی_STATE_INVALID);

    أرجع کھڑکی->ترقی_state;
}

bool SDL_سیٹ_کھڑکی_ترقی_قدر(SDL_کھڑکی *کھڑکی, عائم قدر)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    قدر = SDL_clamp(قدر, 0.0f, 1.f);

    کھڑکی->ترقی_قدر = قدر;

    إذا (_this->Apply_کھڑکی_ترقی) {
        إذا (!_this->Apply_کھڑکی_ترقی(_this, کھڑکی)) {
            أرجع false;
        }
    }

    أرجع true;
}

عائم SDL_Get_کھڑکی_ترقی_قدر(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, -1.0f);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, -1.0f);

    أرجع کھڑکی->ترقی_قدر;
}

فراغ SDL_On_کھڑکی_Shown(SDL_کھڑکی *کھڑکی)
{
    // Set window state if we have pending window flags cached
    Apply_کھڑکی_Flags(کھڑکی, کھڑکی->pending_flags);
    کھڑکی->pending_flags = 0;
}

فراغ SDL_On_کھڑکی_Hidden(SDL_کھڑکی *کھڑکی)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    کھڑکی->pending_flags |= (کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, false);
}

فراغ SDL_On_کھڑکی_Display_بدلیا(SDL_کھڑکی *کھڑکی)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    إذا (کھڑکی->update_fullscreen_on_display_بدلیا && (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        ثابت bool auto_منوال_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_میل_EXCLUSIVE_منوال_ON_MOVE, true);

        إذا (auto_منوال_switch && (کھڑکی->requested_fullscreen_منوال.w != 0 || کھڑکی->requested_fullscreen_منوال.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);
            bool include_بلند_density_modes = false;

            إذا (کھڑکی->requested_fullscreen_منوال.pixel_density > 1.0f) {
                include_بلند_density_modes = true;
            }
            ثابت bool لبھیا_میل = SDL_Get_Closest_Fullscreen_Display_منوال(displayID, کھڑکی->requested_fullscreen_منوال.w, کھڑکی->requested_fullscreen_منوال.h,
                                                                         کھڑکی->requested_fullscreen_منوال.refresh_شرح, include_بلند_density_modes, &کھڑکی->current_fullscreen_منوال);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            إذا (!لبھیا_میل ||
                کھڑکی->requested_fullscreen_منوال.w != کھڑکی->current_fullscreen_منوال.w ||
                کھڑکی->requested_fullscreen_منوال.h != کھڑکی->current_fullscreen_منوال.h) {
                SDL_zero(کھڑکی->current_fullscreen_منوال);
            }
        } وإلا {
            SDL_zero(کھڑکی->current_fullscreen_منوال);
        }

        إذا (SDL_کھڑکی_FULLSCREEN_VISIBLE(کھڑکی)) {
            SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_کھڑکی_Pixel_ناپ_بدلیا(کھڑکی);
}

فراغ SDL_On_کھڑکی_Moved(SDL_کھڑکی *کھڑکی)
{
    SDL_Check_کھڑکی_Display_بدلیا(کھڑکی);
}

فراغ SDL_On_کھڑکی_Resized(SDL_کھڑکی *کھڑکی)
{
    SDL_Check_کھڑکی_Display_بدلیا(کھڑکی);
    SDL_Check_کھڑکی_Pixel_ناپ_بدلیا(کھڑکی);
    SDL_Check_کھڑکی_محفوظ_Area_بدلیا(کھڑکی);

    إذا ((کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) && _this->Update_کھڑکی_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_اشارہ_گر_Property(کھڑکی->props, SDL_PROP_کھڑکی_SHAPE_اشارہ_گر, عدم);
        إذا (surface) {
            _this->Update_کھڑکی_Shape(_this, کھڑکی, surface);
        }
    }
}

فراغ SDL_Check_کھڑکی_Pixel_ناپ_بدلیا(SDL_کھڑکی *کھڑکی)
{
    صحيح pixel_w = 0, pixel_h = 0;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &pixel_w, &pixel_h);
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_PIXEL_ناپ_بدلیا, pixel_w, pixel_h);

    SDL_Check_کھڑکی_Display_Scale_بدلیا(کھڑکی);
}

فراغ SDL_On_کھڑکی_Pixel_ناپ_بدلیا(SDL_کھڑکی *کھڑکی)
{
    کھڑکی->surface_valid = false;
}

فراغ SDL_On_کھڑکی_جیوندا_Resize_Update(SDL_کھڑکی *کھڑکی)
{
    إذا (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } وإلا {
        // Send an expose event so the application can redraw
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ساكن فراغ SDL_Check_کھڑکی_محفوظ_Area_بدلیا(SDL_کھڑکی *کھڑکی)
{
    SDL_Rect rect;

    rect.x = کھڑکی->محفوظ_inset_بایاں;
    rect.y = کھڑکی->محفوظ_inset_چوٹی;
    rect.w = کھڑکی->w - (کھڑکی->محفوظ_inset_دایاں + کھڑکی->محفوظ_inset_بایاں);
    rect.h = کھڑکی->h - (کھڑکی->محفوظ_inset_چوٹی + کھڑکی->محفوظ_inset_bottom);
    إذا (SDL_memcmp(&rect, &کھڑکی->محفوظ_rect, حجم(rect)) != 0) {
        SDL_copyp(&کھڑکی->محفوظ_rect, &rect);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_محفوظ_AREA_بدلیا, 0, 0);
    }
}

فراغ SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(SDL_کھڑکی *کھڑکی, صحيح بایاں, صحيح دایاں, صحيح چوٹی, صحيح bottom)
{
    کھڑکی->محفوظ_inset_بایاں = بایاں;
    کھڑکی->محفوظ_inset_دایاں = دایاں;
    کھڑکی->محفوظ_inset_چوٹی = چوٹی;
    کھڑکی->محفوظ_inset_bottom = bottom;
    SDL_Check_کھڑکی_محفوظ_Area_بدلیا(کھڑکی);
}

bool SDL_Get_کھڑکی_محفوظ_Area(SDL_کھڑکی *کھڑکی, SDL_Rect *rect)
{
    إذا (rect) {
        SDL_zerop(rect);
    }

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (rect) {
        إذا (SDL_Rect_خالی_تھاواں(&کھڑکی->محفوظ_rect)) {
            rect->w = کھڑکی->w;
            rect->h = کھڑکی->h;
        } وإلا {
            SDL_copyp(rect, &کھڑکی->محفوظ_rect);
        }
    }
    أرجع true;
}

فراغ SDL_On_کھڑکی_Minimized(SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

فراغ SDL_On_کھڑکی_Maximized(SDL_کھڑکی *کھڑکی)
{
}

فراغ SDL_On_کھڑکی_Restored(SDL_کھڑکی *کھڑکی)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    إذا (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

فراغ SDL_On_کھڑکی_Enter(SDL_کھڑکی *کھڑکی)
{
    إذا (_this->On_کھڑکی_Enter) {
        _this->On_کھڑکی_Enter(_this, کھڑکی);
    }
    SDL_Update_Relative_Mouse_منوال();
}

فراغ SDL_On_کھڑکی_Leave(SDL_کھڑکی *کھڑکی)
{
    SDL_Update_Relative_Mouse_منوال();
}

فراغ SDL_On_کھڑکی_Focus_Gained(SDL_کھڑکی *کھڑکی)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    إذا (mouse && mouse->relative_منوال) {
        SDL_سیٹ_Mouse_Focus(کھڑکی);
    }

    SDL_Update_کھڑکی_Grab(کھڑکی);
}

ساكن bool SDL_ShouldMinimizeOnFocusLoss(SDL_کھڑکی *کھڑکی)
{
    ثابت حرف *hint;

    إذا (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) || کھڑکی->is_destroying) {
        أرجع false;
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (Cocoa_IsShowingModalDialog(کھڑکی)) {
            أرجع false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } وإلا إذا (Cocoa_Is_کھڑکی_وچ_Fullscreen_Space(کھڑکی)) {
            أرجع false;
        }
    }
#جے_انت

#جے_تعریف_شدہ SDL_PLATFORM_ANDROID
    {
        خارجي bool Android_JNI_ShouldMinimizeOnFocusLoss(فراغ);
        إذا (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            أرجع false;
        }
    }
#جے_انت

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    إذا (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        إذا (کھڑکی->fullscreen_exclusive && !SDL_منوال_Switching_Emulated(_this)) {
            أرجع true;
        } وإلا {
            أرجع false;
        }
    }
    أرجع SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

فراغ SDL_On_کھڑکی_Focus_گواچا(SDL_کھڑکی *کھڑکی)
{
    SDL_Update_کھڑکی_Grab(کھڑکی);

    إذا (SDL_ShouldMinimizeOnFocusLoss(کھڑکی)) {
        SDL_Minimize_کھڑکی(کھڑکی);
    }
}

SDL_کھڑکی *SDL_GetToplevelForKeyboardFocus(فراغ)
{
    SDL_کھڑکی *focus = SDL_GetKeyboardFocus();

    إذا (focus) {
        // Get the toplevel parent window.
        طالما (focus->ماپا) {
            focus = focus->ماپا;
        }
    }

    أرجع focus;
}

bool SDL_جوڑو_کھڑکی_Renderer(SDL_کھڑکی *کھڑکی, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(کھڑکی->renderers, (کھڑکی->عدد_renderers + 1) * حجم(*renderers));
    إذا (!renderers) {
        أرجع false;
    }

    کھڑکی->renderers = renderers;
    کھڑکی->renderers[کھڑکی->عدد_renderers++] = renderer;

    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_RENDERER_اشارہ_گر, renderer);
    أرجع true;
}

فراغ SDL_Remove_کھڑکی_Renderer(SDL_کھڑکی *کھڑکی, SDL_Renderer *renderer)
{
    لكل (صحيح i = 0; i < کھڑکی->عدد_renderers; ++i) {
        إذا (کھڑکی->renderers[i] == renderer) {
            إذا (i < (کھڑکی->عدد_renderers - 1)) {
                SDL_memmove(&کھڑکی->renderers[i], &کھڑکی->renderers[i + 1], (کھڑکی->عدد_renderers - i - 1) * حجم(کھڑکی->renderers[i]));
            }
            --کھڑکی->عدد_renderers;
            اكسر;
        }
    }

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    إذا (SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_RENDERER_اشارہ_گر, عدم) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_کھڑکی_RENDERER_اشارہ_گر);
    }
}

فراغ SDL_Destroy_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی,);

    کھڑکی->is_destroying = true;

    // Destroy any child windows of this window
    طالما (کھڑکی->پہلا_بچہ) {
        SDL_Destroy_کھڑکی(کھڑکی->پہلا_بچہ);
    }

    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DESTROYED, 0, 0);

    SDL_Destroy_کھڑکی_Surface(کھڑکی);

    SDL_Renderer *renderer = SDL_GetRenderer(کھڑکی);
    إذا (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, true);
    إذا (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        SDL_Hide_کھڑکی(کھڑکی);
    }

    SDL_DestroyProperties(کھڑکی->متن_داخلہ_props);

    SDL_Destroy_کھڑکی_Texture(_this, کھڑکی);
    SDL_DestroyProperties(کھڑکی->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    إذا (_this->سیٹ_کھڑکی_Modal && (کھڑکی->flags & SDL_کھڑکی_MODAL)) {
        _this->سیٹ_کھڑکی_Modal(_this, کھڑکی, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
        إذا (_this->displays[i]->fullscreen_کھڑکی == کھڑکی) {
            _this->displays[i]->fullscreen_کھڑکی = عدم;
        }
    }

    // Make sure this window no longer has focus
    إذا (SDL_GetKeyboardFocus() == کھڑکی) {
        SDL_سیٹ_Keyboard_Focus(عدم);
    }
    إذا ((کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    إذا (SDL_GetMouseFocus() == کھڑکی) {
        SDL_سیٹ_Mouse_Focus(عدم);
    }

    // Make no context current if this is the current context window
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        إذا (_this->current_glwin == کھڑکی) {
            SDL_GL_MakeCurrent(کھڑکی, عدم);
        }
    }

    إذا (_this->Destroy_کھڑکی) {
        _this->Destroy_کھڑکی(_this, کھڑکی);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    إذا (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->grabbed_کھڑکی == کھڑکی) {
        _this->grabbed_کھڑکی = عدم; // ungrabbing input.
    }

    إذا (_this->current_glwin == کھڑکی) {
        _this->current_glwin = عدم;
    }

    SDL_Compare_And_وٹاندرا_Atomic_اشارہ_گر(&_this->wakeup_کھڑکی, کھڑکی, عدم);

    // Now invalidate magic
    SDL_سیٹ_Object_Valid(کھڑکی, SDL_OBJECT_TYPE_کھڑکی, false);

    // Free memory associated with the window
    SDL_free(کھڑکی->title);
    SDL_DestroySurface(کھڑکی->icon);

    // Unlink the window from its siblings.
    SDL_Update_کھڑکی_Hierarchy(کھڑکی, عدم);

    // Unlink the window from the global window list
    إذا (کھڑکی->اگلا) {
        کھڑکی->اگلا->prev = کھڑکی->prev;
    }
    إذا (کھڑکی->prev) {
        کھڑکی->prev->اگلا = کھڑکی->اگلا;
    } وإلا {
        _this->windows = کھڑکی->اگلا;
    }

    SDL_free(کھڑکی->renderers);
    SDL_free(کھڑکی);

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#جے_انت
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
#جے_انت
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    طالما (_this->windows) {
        SDL_Destroy_کھڑکی(_this->windows);
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

    لكل (i = _this->عدد_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->عدد_displays == 0);
    SDL_free(_this->displays);
    _this->displays = عدم;

    SDL_Cancel_Clipboard_انکڑے(0);

    إذا (_this->primary_selection_متن) {
        SDL_free(_this->primary_selection_متن);
        _this->primary_selection_متن = عدم;
    }
    _this->حرر(_this);
    _this = عدم;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_لدو_Library(ثابت حرف *رستہ)
{
    bool نتیجہ;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->gl_config.driver_loaded) {
        إذا (رستہ && SDL_strcmp(رستہ, _this->gl_config.driver_رستہ) != 0) {
            أرجع SDL_سیٹ_Error("OpenGL library already loaded");
        }
        نتیجہ = true;
    } وإلا {
        إذا (!_this->GL_لدو_Library) {
            أرجع SDL_DllNotSupported("OpenGL");
        }
        نتیجہ = _this->GL_لدو_Library(_this, رستہ);
    }
    إذا (نتیجہ) {
        ++_this->gl_config.driver_loaded;
    } وإلا {
        إذا (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    أرجع نتیجہ;
}

SDL_Function_اشارہ_گر SDL_GL_Get_Proc_پتہ(ثابت حرف *proc)
{
    SDL_Function_اشارہ_گر func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;
    إذا (_this->GL_Get_Proc_پتہ) {
        إذا (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_پتہ(_this, proc);
        } وإلا {
            SDL_سیٹ_Error("No GL driver has been loaded");
        }
    } وإلا {
        SDL_سیٹ_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    أرجع func;
}

SDL_Function_اشارہ_گر SDL_EGL_Get_Proc_پتہ(ثابت حرف *proc)
{
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    SDL_Function_اشارہ_گر func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;

    إذا (_this->egl_انکڑے) {
        func = SDL_EGL_Get_Proc_پتہ_اندرونی(_this, proc);
    } وإلا {
        SDL_سیٹ_Error("No EGL library has been loaded");
    }

    أرجع func;
#وإلا
    SDL_سیٹ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جے_انت
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
#جے_بنا_تعریف SDL_VIDEO_OPENGL
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint اشاریہ);
#جے_انت

ساكن SDL_INLINE bool is_At_گھٹ_توں_گھٹ_GL3(ثابت حرف *verstr)
{
    أرجع verstr && (SDL_atoi(verstr) >= 3);
}
#جے_انت // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت حرف *extension)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت حرف *extensions;
    ثابت حرف *شروع;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    إذا (where || *extension == '\0') {
        أرجع false;
    }
    // See if there's a hint or environment variable override
    شروع = SDL_GetHint(extension);
    إذا (شروع && *شروع == '0') {
        أرجع false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتہ("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (is_At_گھٹ_توں_گھٹ_GL3((ثابت حرف *)glGetStringFunc(GL_نسخہ))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint عدد_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_پتہ("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتہ("glGetIntegerv");
        إذا ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            أرجع false;
        }

#جے_بنا_تعریف GL_عدد_EXTENSIONS
#تعریف_کرو GL_عدد_EXTENSIONS 0x821D
#جے_انت
        glGetIntegervFunc(GL_عدد_EXTENSIONS, &عدد_exts);
        لكل (i = 0; i < عدد_exts; i++) {
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

    شروع = extensions;

    لكل (;;) {
        where = SDL_strstr(شروع, extension);
        إذا (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        إذا (where == extensions || *(where - 1) == ' ') {
            إذا (*terminator == ' ' || *terminator == '\0') {
                أرجع true;
            }
        }

        شروع = terminator;
    }
    أرجع false;
#وإلا
    أرجع false;
#جے_انت
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
#جے_انت
}

فراغ SDL_EGL_سیٹ_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
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

فراغ SDL_GL_Reset_گن(فراغ)
{
    إذا (!_this) {
        أرجع;
    }

    _this->egl_platformattrib_callback = عدم;
    _this->egl_surfaceattrib_callback = عدم;
    _this->egl_contextattrib_callback = عدم;
    _this->egl_attrib_callback_userdata = عدم;

    _this->gl_config.red_ناپ = 8;
    _this->gl_config.green_ناپ = 8;
    _this->gl_config.blue_ناپ = 8;
    _this->gl_config.alpha_ناپ = 8;
    _this->gl_config.بفر_ناپ = 0;
    _this->gl_config.ڈونگھائی_ناپ = 16;
    _this->gl_config.stencil_ناپ = 0;
    _this->gl_config.double_بفر = 1;
    _this->gl_config.accum_red_ناپ = 0;
    _this->gl_config.accum_green_ناپ = 0;
    _this->gl_config.accum_blue_ناپ = 0;
    _this->gl_config.accum_alpha_ناپ = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    _this->gl_config.major_نسخہ = 2;
    _this->gl_config.minor_نسخہ = 1;
    _this->gl_config.profile_نقاب = 0;
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_نسخہ = 2;
    _this->gl_config.minor_نسخہ = 0;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_نسخہ = 1;
    _this->gl_config.minor_نسخہ = 1;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
#جے_انت

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    إذا (_this->GL_سیٹ_Default_Profile_Config) {
        _this->GL_سیٹ_Default_Profile_Config(_this);
    }
}

bool SDL_GL_سیٹ_Attribute(SDL_GLAttr attr, صحيح قدر)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool نتیجہ;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    نتیجہ = true;
    بدل (attr) {
    حالة SDL_GL_RED_ناپ:
        _this->gl_config.red_ناپ = قدر;
        اكسر;
    حالة SDL_GL_GREEN_ناپ:
        _this->gl_config.green_ناپ = قدر;
        اكسر;
    حالة SDL_GL_BLUE_ناپ:
        _this->gl_config.blue_ناپ = قدر;
        اكسر;
    حالة SDL_GL_ALPHA_ناپ:
        _this->gl_config.alpha_ناپ = قدر;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_بفر = قدر;
        اكسر;
    حالة SDL_GL_بفر_ناپ:
        _this->gl_config.بفر_ناپ = قدر;
        اكسر;
    حالة SDL_GL_ڈونگھائی_ناپ:
        _this->gl_config.ڈونگھائی_ناپ = قدر;
        اكسر;
    حالة SDL_GL_STENCIL_ناپ:
        _this->gl_config.stencil_ناپ = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_RED_ناپ:
        _this->gl_config.accum_red_ناپ = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_ناپ:
        _this->gl_config.accum_green_ناپ = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_ناپ:
        _this->gl_config.accum_blue_ناپ = قدر;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_ناپ:
        _this->gl_config.accum_alpha_ناپ = قدر;
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
    حالة SDL_GL_CONTEXT_MAJOR_نسخہ:
        _this->gl_config.major_نسخہ = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_MINOR_نسخہ:
        _this->gl_config.minor_نسخہ = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_FLAGS:
        إذا (قدر & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            نتیجہ = SDL_سیٹ_Error("Unknown OpenGL context flag %d", قدر);
            اكسر;
        }
        _this->gl_config.flags = قدر;
        اكسر;
    حالة SDL_GL_CONTEXT_PROFILE_نقاب:
        إذا (قدر != 0 &&
            قدر != SDL_GL_CONTEXT_PROFILE_CORE &&
            قدر != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            قدر != SDL_GL_CONTEXT_PROFILE_ES) {
            نتیجہ = SDL_سیٹ_Error("Unknown OpenGL context profile %d", قدر);
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
        نتیجہ = SDL_سیٹ_Error("Unknown OpenGL attribute");
        اكسر;
    }
    أرجع نتیجہ;
#وإلا
    أرجع SDL_Unsupported();
#جے_انت // SDL_VIDEO_OPENGL
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
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_پٹھ_بایاں;
    GLenum attachmentattrib = 0;
#جے_انت

    CHECK_PARAM(!قدر) {
        أرجع SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *قدر = 0;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    بدل (attr) {
    حالة SDL_GL_RED_ناپ:
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_ناپ;
#جے_انت
        attrib = GL_RED_بٹ;
        اكسر;
    حالة SDL_GL_BLUE_ناپ:
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_ناپ;
#جے_انت
        attrib = GL_BLUE_بٹ;
        اكسر;
    حالة SDL_GL_GREEN_ناپ:
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_ناپ;
#جے_انت
        attrib = GL_GREEN_بٹ;
        اكسر;
    حالة SDL_GL_ALPHA_ناپ:
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_ناپ;
#جے_انت
        attrib = GL_ALPHA_بٹ;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        اكسر;
#وإلا
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *قدر = _this->gl_config.double_بفر;
        أرجع true;
#جے_انت
    حالة SDL_GL_ڈونگھائی_ناپ:
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        attachment = GL_ڈونگھائی;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ڈونگھائی_ناپ;
#جے_انت
        attrib = GL_ڈونگھائی_بٹ;
        اكسر;
    حالة SDL_GL_STENCIL_ناپ:
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_ناپ;
#جے_انت
        attrib = GL_STENCIL_بٹ;
        اكسر;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    حالة SDL_GL_ACCUM_RED_ناپ:
        attrib = GL_ACCUM_RED_بٹ;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_ناپ:
        attrib = GL_ACCUM_GREEN_بٹ;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_ناپ:
        attrib = GL_ACCUM_BLUE_بٹ;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_ناپ:
        attrib = GL_ACCUM_ALPHA_بٹ;
        اكسر;
    حالة SDL_GL_STEREO:
        attrib = GL_STEREO;
        اكسر;
#وإلا
    حالة SDL_GL_ACCUM_RED_ناپ:
    حالة SDL_GL_ACCUM_GREEN_ناپ:
    حالة SDL_GL_ACCUM_BLUE_ناپ:
    حالة SDL_GL_ACCUM_ALPHA_ناپ:
    حالة SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *قدر = 0;
        أرجع true;
#جے_انت
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        اكسر;
    حالة SDL_GL_بفر_ناپ:
    {
        صحيح rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        إذا (!SDL_GL_GetAttribute(SDL_GL_RED_ناپ, &rsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_GREEN_ناپ, &gsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_BLUE_ناپ, &bsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_ALPHA_ناپ, &asize)) {
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
    حالة SDL_GL_CONTEXT_MAJOR_نسخہ:
    {
        *قدر = _this->gl_config.major_نسخہ;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MINOR_نسخہ:
    {
        *قدر = _this->gl_config.minor_نسخہ;
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
            attrib = GL_RGBA_FLOAT_منوال_ARB;
            اكسر;
        } وإلا {
            أرجع 0;
        }
    }
    افتراضي:
        أرجع SDL_سیٹ_Error("Unknown OpenGL attribute");
    }

#جے_تعریف_شدہ SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتہ("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (attachmentattrib && is_At_گھٹ_توں_گھٹ_GL3((ثابت حرف *)glGetStringFunc(GL_نسخہ))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_پتہ("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_پتہ("glBindFramebuffer");
        إذا (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_پتہ("glGetFramebufferAttachmentParameteriv");
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
            إذا (attachment == GL_ڈونگھائی || attachment == GL_STENCIL) {
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
#جے_انت
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتہ("glGetIntegerv");
        إذا (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)قدر);
        } وإلا {
            أرجع false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_پتہ("glGetError");
    إذا (!glGetErrorFunc) {
        أرجع false;
    }

    error = glGetErrorFunc();
    إذا (error != GL_NO_ERROR) {
        إذا (error == GL_INVALID_ENUM) {
            أرجع SDL_سیٹ_Error("OpenGL error: GL_INVALID_ENUM");
        } وإلا إذا (error == GL_INVALID_قدر) {
            أرجع SDL_سیٹ_Error("OpenGL error: GL_INVALID_VALUE");
        }
        أرجع SDL_سیٹ_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    إذا (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *قدر = (*قدر == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    أرجع true;
#وإلا
    أرجع SDL_Unsupported();
#جے_انت // SDL_VIDEO_OPENGL
}

#تعریف_کرو NOT_AN_OPENGL_کھڑکی "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_کھڑکی *کھڑکی)
{
    SDL_GLContext ctx = عدم;
    CHECK_کھڑکی_MAGIC(کھڑکی, عدم);

    إذا (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
        SDL_سیٹ_Error(NOT_AN_OPENGL_کھڑکی);
        أرجع عدم;
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحيح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    إذا (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#جے_انت

    ctx = _this->GL_CreateContext(_this, کھڑکی);

    // Creating a context is assumed to make it current in the SDL driver.
    إذا (ctx) {
        _this->current_glwin = کھڑکی;
        _this->current_glctx = ctx;
        SDL_سیٹ_TLS(&_this->current_glwin_tls, کھڑکی, عدم);
        SDL_سیٹ_TLS(&_this->current_glctx_tls, ctx, عدم);
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    إذا (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_پتہ(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتہ("glGetString");
        إذا (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            إذا (_this->gl_config.profile_نقاب & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } وإلا {
                supported = is_At_گھٹ_توں_گھٹ_GL3((ثابت حرف *)glGetStringFunc(GL_نسخہ)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            إذا (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#جے_انت

    أرجع ctx;
}

bool SDL_GL_MakeCurrent(SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    bool نتیجہ;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (کھڑکی == SDL_GL_Get_Current_کھڑکی() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        أرجع true;
    }

    إذا (!context) {
        کھڑکی = عدم;
    } وإلا إذا (کھڑکی) {
        CHECK_کھڑکی_MAGIC(کھڑکی, false);

        إذا (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
            أرجع SDL_سیٹ_Error(NOT_AN_OPENGL_کھڑکی);
        }
    } وإلا إذا (!_this->gl_allow_no_surface) {
        أرجع SDL_سیٹ_Error("Use of OpenGL without a window is not supported on this platform");
    }

    نتیجہ = _this->GL_MakeCurrent(_this, کھڑکی, context);
    إذا (نتیجہ) {
        _this->current_glwin = کھڑکی;
        _this->current_glctx = context;
        SDL_سیٹ_TLS(&_this->current_glwin_tls, کھڑکی, عدم);
        SDL_سیٹ_TLS(&_this->current_glctx_tls, context, عدم);
    }
    أرجع نتیجہ;
}

SDL_کھڑکی *SDL_GL_Get_Current_کھڑکی(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع (SDL_کھڑکی *)SDL_GetTLS(&_this->current_glwin_tls);
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
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع EGL_NO_DISPLAY;
    }
    إذا (!_this->egl_انکڑے) {
        SDL_سیٹ_Error("There is no current EGL display");
        أرجع EGL_NO_DISPLAY;
    }
    أرجع _this->egl_انکڑے->egl_display;
#وإلا
    SDL_سیٹ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جے_انت
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(فراغ)
{
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_انکڑے) {
        SDL_سیٹ_Error("There is no current EGL display");
        أرجع عدم;
    }
    أرجع _this->egl_انکڑے->egl_config;
#وإلا
    SDL_سیٹ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جے_انت
}

SDL_EGLConfig SDL_EGL_Get_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_انکڑے) {
        SDL_سیٹ_Error("There is no current EGL display");
        أرجع عدم;
    }
    إذا (_this->GL_GetEGLSurface) {
        أرجع _this->GL_GetEGLSurface(_this, کھڑکی);
    }
    أرجع عدم;
#وإلا
    SDL_سیٹ_Error("SDL was not built with EGL support");
    أرجع عدم;
#جے_انت
}

bool SDL_GL_سیٹ_وٹاندرا_Interval(صحيح interval)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_سیٹ_Error("No OpenGL context has been made current");
    } وإلا إذا (_this->GL_سیٹ_وٹاندرا_Interval) {
        أرجع _this->GL_سیٹ_وٹاندرا_Interval(_this, interval);
    } وإلا {
        أرجع SDL_سیٹ_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_وٹاندرا_Interval(صحيح *interval)
{
    CHECK_PARAM(!interval) {
       أرجع SDL_InvalidParamError("interval");
    }

    *interval = 0;

    إذا (!_this) {
        أرجع SDL_سیٹ_Error("no video driver");
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_سیٹ_Error("no current context");
    } وإلا إذا (_this->GL_Get_وٹاندرا_Interval) {
        أرجع _this->GL_Get_وٹاندرا_Interval(_this, interval);
    } وإلا {
        أرجع SDL_سیٹ_Error("not implemented");
    }
}

bool SDL_GL_وٹاندرا_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
        أرجع SDL_سیٹ_Error(NOT_AN_OPENGL_کھڑکی);
    }

    إذا (SDL_GL_Get_Current_کھڑکی() != کھڑکی) {
        أرجع SDL_سیٹ_Error("The specified window has not been made current");
    }

    أرجع _this->GL_وٹاندرا_کھڑکی(_this, کھڑکی);
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
ساكن فراغ Create_نقاب_From_Color_کلید_Or_Alpha(SDL_Surface *icon, Uint8 *نقاب, صحيح flags)
{
    صحيح x, y;
    Uint32 colorkey;
#تعریف_کرو سیٹ_MASKBIT(icon, x, y, نقاب) \
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
                        سیٹ_MASKBIT(icon, x, y, نقاب);
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
                        سیٹ_MASKBIT(icon, x, y, نقاب);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سیٹ_MASKBIT(icon, x, y, نقاب);
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
                        سیٹ_MASKBIT(icon, x, y, نقاب);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سیٹ_MASKBIT(icon, x, y, نقاب);
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
فراغ SDL_WM_سیٹ_Icon(SDL_Surface *icon, Uint8 *نقاب)
{
    إذا (icon && _this->سیٹ_Icon) {
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
                Create_نقاب_From_Color_کلید_Or_Alpha(icon, نقاب, flags);
            }
            _this->سیٹ_Icon(_this, icon, نقاب);
            SDL_free(نقاب);
        } وإلا {
            _this->سیٹ_Icon(_this, icon, نقاب);
        }
    }
}
#جے_انت

SDL_متن_داخلہ_Type SDL_Get_متن_داخلہ_Type(SDL_PropertiesID props)
{
    أرجع (SDL_متن_داخلہ_Type)SDL_Get_نمبر_Property(props, SDL_PROP_TEXTINPUT_TYPE_نمبر, SDL_TEXTINPUT_TYPE_متن);
}

SDL_Capitalization SDL_Get_متن_داخلہ_Capitalization(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_نمبر)) {
        أرجع (SDL_Capitalization)SDL_Get_نمبر_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_نمبر, SDL_CAPITALIZE_NONE);
    }

    بدل (SDL_Get_متن_داخلہ_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن:
        أرجع SDL_CAPITALIZE_SENTENCES;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        أرجع SDL_CAPITALIZE_الفاظ;
    افتراضي:
        أرجع SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_متن_داخلہ_Autocorrect(SDL_PropertiesID props)
{
    أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_متن_داخلہ_Multiline(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_RETURN_کلید_HIDES_IME, false)) {
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

bool SDL_شروع_متن_داخلہ(SDL_کھڑکی *کھڑکی)
{
    أرجع SDL_شروع_متن_داخلہ_With_Properties(کھڑکی, 0);
}

bool SDL_شروع_متن_داخلہ_With_Properties(SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (کھڑکی->متن_داخلہ_props) {
        SDL_DestroyProperties(کھڑکی->متن_داخلہ_props);
        کھڑکی->متن_داخلہ_props = 0;
    }

    إذا (props) {
        کھڑکی->متن_داخلہ_props = SDL_CreateProperties();
        إذا (!کھڑکی->متن_داخلہ_props) {
            أرجع false;
        }
        إذا (!SDL_CopyProperties(props, کھڑکی->متن_داخلہ_props)) {
            أرجع false;
        }
    }

    إذا (_this->سیٹ_متن_داخلہ_Properties) {
        _this->سیٹ_متن_داخلہ_Properties(_this, کھڑکی, props);
    }

    إذا (!کھڑکی->متن_داخلہ_سرگرم) {
        // Start the text input system
        إذا (_this->شروع_متن_داخلہ) {
            إذا (!_this->شروع_متن_داخلہ(_this, کھڑکی, props)) {
                أرجع false;
            }
        }
        کھڑکی->متن_داخلہ_سرگرم = true;
    }

    // Show the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(کھڑکی)) {
        إذا (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, کھڑکی, props);
        }
    }
    أرجع true;
}

bool SDL_متن_داخلہ_سرگرم(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    أرجع کھڑکی->متن_داخلہ_سرگرم;
}

bool SDL_Stop_متن_داخلہ(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (کھڑکی->متن_داخلہ_سرگرم) {
        // Stop the text input system
        إذا (_this->Stop_متن_داخلہ) {
            _this->Stop_متن_داخلہ(_this, کھڑکی);
        }
        کھڑکی->متن_داخلہ_سرگرم = false;
    }

    // Hide the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(کھڑکی)) {
        إذا (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, کھڑکی);
        }
    }
    أرجع true;
}

bool SDL_سیٹ_متن_داخلہ_Area(SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rect, صحيح cursor)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (rect) {
        SDL_copyp(&کھڑکی->متن_داخلہ_rect, rect);
        کھڑکی->متن_داخلہ_cursor = cursor;
    } وإلا {
        SDL_zero(کھڑکی->متن_داخلہ_rect);
        کھڑکی->متن_داخلہ_cursor = 0;
    }

    إذا (_this && _this->Update_متن_داخلہ_Area) {
        إذا (!_this->Update_متن_داخلہ_Area(_this, کھڑکی)) {
            أرجع false;
        }
    }
    أرجع true;
}

bool SDL_Get_متن_داخلہ_Area(SDL_کھڑکی *کھڑکی, SDL_Rect *rect, صحيح *cursor)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (rect) {
        SDL_copyp(rect, &کھڑکی->متن_داخلہ_rect);
    }
    إذا (cursor) {
        *cursor = کھڑکی->متن_داخلہ_cursor;
    }
    أرجع true;
}

bool SDL_ClearComposition(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (_this->ClearComposition) {
        أرجع _this->ClearComposition(_this, کھڑکی);
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

bool SDL_ScreenKeyboardShown(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

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
        SDL_ڈالو_Event(&event);
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
        SDL_ڈالو_Event(&event);
    }
}

صحيح SDL_Get_سنیہا_Box_گنتی(فراغ)
{
    أرجع SDL_GetAtomicInt(&SDL_messagebox_گنتی);
}

bool SDL_Show_سنیہا_Box(ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID)
{
    صحيح dummybutton;
    bool نتیجہ = false;
    bool show_cursor_prev;
    SDL_کھڑکی *current_کھڑکی;
    SDL_سنیہا_Box_انکڑے mbdata;

    CHECK_PARAM(!messageboxdata) {
        أرجع SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        أرجع SDL_سیٹ_Error("Invalid number of buttons");
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

    إذا (messageboxdata->سنیہا) {
        ثابت size_t slen = SDL_strlen(messageboxdata->سنیہا) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        إذا (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            أرجع false;
        }
        SDL_memcpy(msgcpy, messageboxdata->سنیہا, slen);
    }

    (فراغ)SDL_AtomicIncRef(&SDL_messagebox_گنتی);

    current_کھڑکی = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_سیٹ_Relative_Mouse_منوال(false);
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
    mbdata.سنیہا = msgcpy;
    إذا (!mbdata.سنیہا) {
        mbdata.سنیہا = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    إذا (_this && _this->Show_سنیہا_Box) {
        نتیجہ = _this->Show_سنیہا_Box(_this, messageboxdata, buttonID);
    } وإلا {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        إذا (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            طالما (driver_attempt && (*driver_attempt != 0) && !نتیجہ) {
                ثابت حرف *driver_attempt_سرا = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_سرا) ? (driver_attempt_سرا - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                لكل (صحيح i = 0; bootstrap[i]; ++i) {
                    إذا (bootstrap[i]->Show_سنیہا_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        إذا (bootstrap[i]->Show_سنیہا_Box(messageboxdata, buttonID)) {
                            نتیجہ = true;
                        }
                        اكسر;
                    }
                }

                driver_attempt = (driver_attempt_سرا) ? (driver_attempt_سرا + 1) : عدم;
            }
        } وإلا {
            لكل (صحيح i = 0; bootstrap[i]; ++i) {
                إذا (bootstrap[i]->Show_سنیہا_Box && bootstrap[i]->Show_سنیہا_Box(messageboxdata, buttonID)) {
                    نتیجہ = true;
                    اكسر;
                }
            }
        }
    }

    إذا (!نتیجہ) {
        ثابت حرف *error = SDL_GetError();

        إذا (!*error) {
            SDL_سیٹ_Error("No message system available");
        }
    } وإلا {
        SDL_ClearError();
    }

    (فراغ)SDL_AtomicDecRef(&SDL_messagebox_گنتی);

    إذا (current_کھڑکی) {
        SDL_Raise_کھڑکی(current_کھڑکی);
    }

    إذا (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_منوال();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    أرجع نتیجہ;
}

bool SDL_Show_Simple_سنیہا_Box(SDL_سنیہا_Box_Flags flags, ثابت حرف *title, ثابت حرف *سنیہا, SDL_کھڑکی *کھڑکی)
{
#إذا defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_دایاں;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_دایاں = gsp_Has_Gpu_دایاں();
    إذا (!has_Gpu_دایاں)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_متن_لفظ_WRAP, CFG_LANGUAGE_EN);
    error_متن(&errCnf, سنیہا);
    errorDisp(&errCnf);

    إذا (!has_Gpu_دایاں)
        gfxExit();

    أرجع true;
#وإلا
    SDL_سنیہا_Box_انکڑے انکڑے;
    SDL_سنیہا_Box_Button_انکڑے button;

    SDL_zero(انکڑے);
    انکڑے.flags = flags;
    انکڑے.title = title;
    انکڑے.سنیہا = سنیہا;
    انکڑے.numbuttons = 1;
    انکڑے.buttons = &button;
    انکڑے.کھڑکی = کھڑکی;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.متن = "OK";

    أرجع SDL_Show_سنیہا_Box(&انکڑے, عدم);
#جے_انت
}

bool SDL_ShouldAllowTopmost(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_کھڑکی_ALLOW_TOPMOST, true);
}

bool SDL_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    إذا (_this->Show_کھڑکی_System_Menu) {
        _this->Show_کھڑکی_System_Menu(کھڑکی, x, y);
        أرجع true;
    }

    أرجع SDL_Unsupported();
}

bool SDL_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, SDL_کامیابی_Test callback, فراغ *callback_انکڑے)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!_this->سیٹ_کھڑکی_کامیابی_Test) {
        أرجع SDL_Unsupported();
    }

    کھڑکی->کامیابی_test = callback;
    کھڑکی->کامیابی_test_انکڑے = callback_انکڑے;

    أرجع _this->سیٹ_کھڑکی_کامیابی_Test(کھڑکی, callback != عدم);
}

bool SDL_سیٹ_کھڑکی_Shape(SDL_کھڑکی *کھڑکی, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    إذا (!(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT)) {
        أرجع SDL_سیٹ_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_کھڑکی_Properties(کھڑکی);
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

    إذا (!SDL_سیٹ_Surface_Property(props, SDL_PROP_کھڑکی_SHAPE_اشارہ_گر, surface)) {
        أرجع false;
    }

    إذا (_this->Update_کھڑکی_Shape) {
        إذا (!_this->Update_کھڑکی_Shape(_this, کھڑکی, surface)) {
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

فراغ SDL_On_Application_Did_Receive_حافظہ_Warning(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_کم_حافظہ);
}

فراغ SDL_OnApplicationWillEnterBackground(فراغ)
{
    إذا (_this) {
        SDL_کھڑکی *کھڑکی;
        لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
        }
        SDL_سیٹ_Keyboard_Focus(عدم);
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
        SDL_کھڑکی *کھڑکی;
        لكل (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            SDL_سیٹ_Keyboard_Focus(کھڑکی);
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
        }
    }
}

#تعریف_کرو NOT_A_VULKAN_کھڑکی "The specified window isn't a Vulkan window"

bool SDL_Vulkan_لدو_Library(ثابت حرف *رستہ)
{
    bool نتیجہ;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->vulkan_config.loader_loaded) {
        إذا (رستہ && SDL_strcmp(رستہ, _this->vulkan_config.loader_رستہ) != 0) {
            أرجع SDL_سیٹ_Error("Vulkan loader library already loaded");
        }
        نتیجہ = true;
    } وإلا {
        إذا (!_this->Vulkan_لدو_Library) {
            أرجع SDL_DllNotSupported("Vulkan");
        }
        نتیجہ = _this->Vulkan_لدو_Library(_this, رستہ);
    }
    إذا (نتیجہ) {
        _this->vulkan_config.loader_loaded++;
    }
    أرجع نتیجہ;
}

SDL_Function_اشارہ_گر SDL_Vulkan_GetVkGetInstanceProcAddr(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->vulkan_config.loader_loaded) {
        SDL_سیٹ_Error("No Vulkan loader has been loaded");
        أرجع عدم;
    }
    أرجع (SDL_Function_اشارہ_گر)_this->vulkan_config.vkGetInstanceProcAddr;
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

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *گنتی)
{
    Uint32 tmpcount = 0;
    إذا (!گنتی) {
        گنتی = &tmpcount;
    }

    إذا (!_this->Vulkan_GetInstanceExtensions) {
        *گنتی = 0;
        SDL_Unsupported();
        أرجع عدم;
    }

    أرجع _this->Vulkan_GetInstanceExtensions(_this, گنتی);
}

bool SDL_Vulkan_CreateSurface(SDL_کھڑکی *کھڑکی,
                                  VkInstance instance,
                                  ثابت بنية Vk_ونڈ_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

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

    إذا (!(کھڑکی->flags & SDL_کھڑکی_VULKAN)) {
        // No problem, we can convert to Vulkan
        إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
            کھڑکی->flags &= ~SDL_کھڑکی_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (کھڑکی->flags & SDL_کھڑکی_METAL) {
            کھڑکی->flags &= ~SDL_کھڑکی_METAL;
            // Nothing more to do for Metal.
        }
        إذا (SDL_Vulkan_لدو_Library(عدم)) {
            کھڑکی->flags |= SDL_کھڑکی_VULKAN;
        } وإلا {
            أرجع SDL_سیٹ_Error("failed to load Vulkan library");
        }
    }

    أرجع _this->Vulkan_CreateSurface(_this, کھڑکی, instance, allocator, surface);
}

فراغ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية Vk_ونڈ_Callbacks *allocator)
{
    إذا (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 قطار_Family_اشاریہ)
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
        أرجع _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, قطار_Family_اشاریہ);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    أرجع true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, عدم);

    إذا (!_this->Metal_CreateView) {
        SDL_Unsupported();
        أرجع عدم;
    }

    إذا (!(کھڑکی->flags & SDL_کھڑکی_METAL)) {
        // No problem, we can convert to Metal
        إذا (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
            کھڑکی->flags &= ~SDL_کھڑکی_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
            کھڑکی->flags &= ~SDL_کھڑکی_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        کھڑکی->flags |= SDL_کھڑکی_METAL;
    }

    أرجع _this->Metal_CreateView(_this, کھڑکی);
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
        SDL_سیٹ_Error("Metal is not supported.");
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

    حالة SDL_SYSTEM_CURSOR_ترقی:
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

    حالة SDL_SYSTEM_CURSOR_اشارہ_گر:
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

    حالة SDL_SYSTEM_CURSOR_خانہ_RESIZE:
        أرجع "col-resize";

    حالة SDL_SYSTEM_CURSOR_صف_RESIZE:
        أرجع "row-resize";

    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        إذا (fallback_name) {
            *fallback_name = "move";
        }
        أرجع "all-scroll";

    حالة SDL_SYSTEM_CURSOR_ZOOM_وچ:
        أرجع "zoom-in";

    حالة SDL_SYSTEM_CURSOR_ZOOM_باہرلا:
        أرجع "zoom-out";

    افتراضي:
        أرجع "default";
    }
}
#جے_انت

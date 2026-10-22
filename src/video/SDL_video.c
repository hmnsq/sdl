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

#که_تعریف_شوی SDL_VIDEO_OPENGL
#ضمن <SDL3/SDL_opengl.h>
#د_که_پای // SDL_VIDEO_OPENGL

#إذا defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles.h>
#د_که_پای // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#إذا defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles2.h>
#د_که_پای // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#که_نه_تعریف_شوی GL_CONTEXT_RELEASE_BEHAVIOR
#تعریف_کړه GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#د_که_پای

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#که_نه_تعریف_شوی GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#تعریف_کړه GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#د_که_پای

// This is always the same number between the various EXT/ARB/GLES extensions.
#که_نه_تعریف_شوی GL_FRAMEBUFFER_SRGB
#تعریف_کړه GL_FRAMEBUFFER_SRGB 0x8DB9
#د_که_پای

#که_تعریف_شوی SDL_PLATFORM_EMSCRIPTEN
#ضمن <emscripten.h>
#د_که_پای

#که_تعریف_شوی SDL_PLATFORM_3DS
#ضمن <3ds.h>
#د_که_پای

#که_نه_تعریف_شوی GL_RGBA_FLOAT_ډېرپېښ_ARB
#تعریف_کړه GL_RGBA_FLOAT_ډېرپېښ_ARB 0x8820
#د_که_پای /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ساكن VideoBootStrap *bootstrap[] = {
#که_تعریف_شوی SDL_VIDEO_DRIVER_شخصي
    &شخصي_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#د_که_پای
    &X11_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#که_تعریف_شوی SDL_ننوت_LINUXEV
    &DUMMY_evdev_bootstrap,
#د_که_پای
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#د_که_پای
    عدم
};

#تعریف_کړه CHECK_کړکۍ_MAGIC(کړکۍ, پایله)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        أرجع پایله;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(کړکۍ, SDL_OBJECT_TYPE_کړکۍ)) {     \
        SDL_سېټ_Error("Invalid window");                                 \
        أرجع پایله;                                                  \
    }

#تعریف_کړه CHECK_DISPLAY_MAGIC(display, پایله)                            \
    CHECK_PARAM(!display) {                                             \
        أرجع پایله;                                                  \
    }                                                                   \

#تعریف_کړه CHECK_کړکۍ_NOT_POPUP(کړکۍ, پایله)                          \
    CHECK_PARAM(SDL_کړکۍ_IS_POPUP(کړکۍ)) {                          \
        SDL_سېټ_Error("Operation invalid on popup windows");             \
        أرجع پایله;                                                  \
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
خارجي bool Cocoa_Is_کړکۍ_دننه_Fullscreen_Space(SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_Is_کړکۍ_دننه_Fullscreen_Space_Transition(SDL_کړکۍ *کړکۍ);
خارجي bool Cocoa_سېټ_کړکۍ_Fullscreen_Space(SDL_کړکۍ *کړکۍ, bool state, bool blocking);
خارجي bool Cocoa_IsShowingModalDialog(SDL_کړکۍ *کړکۍ);
#د_که_پای

#که_تعریف_شوی SDL_VIDEO_DRIVER_UIKIT
خارجي فراغ SDL_UpdateLifecycleObserver(فراغ);
#د_که_پای

ساكن فراغ SDL_Check_کړکۍ_Display_بدل_شوی(SDL_کړکۍ *کړکۍ);
ساكن فراغ SDL_Check_کړکۍ_Display_Scale_بدل_شوی(SDL_کړکۍ *کړکۍ);
ساكن فراغ SDL_Check_کړکۍ_خوندي_Area_بدل_شوی(SDL_کړکۍ *کړکۍ);

// Convenience functions for reading driver flags
ساكن bool SDL_ډېرپېښ_Switching_Emulated(SDL_VideoDevice *_this)
{
    إذا (_this->device_caps & VIDEO_DEVICE_CAPS_ډېرپېښ_SWITCHING_EMULATED) {
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

ساكن فراغ SDL_SyncHintWatcher(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_ارزښت, ثابت حرف *new_ارزښت)
{
    syncHint = SDL_GetStringBoolean(new_ارزښت, false);
}

ساكن فراغ SDL_SyncIfRequired(SDL_کړکۍ *کړکۍ)
{
    إذا (syncHint) {
        SDL_Sync_کړکۍ(کړکۍ);
    }
}

ساكن فراغ SDL_Update_کړکۍ_Hierarchy(SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار)
{
    // Unlink the window from the existing parent.
    إذا (کړکۍ->پلار) {
        إذا (کړکۍ->بل_sibling) {
            کړکۍ->بل_sibling->prev_sibling = کړکۍ->prev_sibling;
        }
        إذا (کړکۍ->prev_sibling) {
            کړکۍ->prev_sibling->بل_sibling = کړکۍ->بل_sibling;
        } وإلا {
            کړکۍ->پلار->لومړی_ماشوم = کړکۍ->بل_sibling;
        }

        کړکۍ->پلار = عدم;
    }

    إذا (پلار) {
        کړکۍ->پلار = پلار;

        کړکۍ->بل_sibling = پلار->لومړی_ماشوم;
        إذا (پلار->لومړی_ماشوم) {
            پلار->لومړی_ماشوم->prev_sibling = کړکۍ;
        }
        پلار->لومړی_ماشوم = کړکۍ;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#تعریف_کړه SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر "SDL.internal.window.texturedata"

تعريفنوع بنية
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    فراغ *pixels;
    صحيح pitch;
    صحيح بایټونه_فی_pixel;
} SDL_کړکۍ_Texture_معلومات;

ساكن Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#إذا (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !موخه_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    إذا (_this->GL_CreateContext) {
        أرجع SDL_کړکۍ_OPENGL;
    }
#د_که_پای
#إذا defined(SDL_VIDEO_METAL) && (موخه_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    إذا (_this->Metal_CreateView) {
        أرجع SDL_کړکۍ_METAL;
    }
#د_که_پای
#إذا defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    إذا (SDL_strcmp(_this->name, "openvr") == 0) {
        أرجع SDL_کړکۍ_OPENGL;
    }
#د_که_پای
    أرجع 0;
}

ساكن bool SDL_Create_کړکۍ_Texture(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    SDL_کړکۍ_Texture_معلومات *معلومات = (SDL_کړکۍ_Texture_معلومات *)SDL_Get_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر, عدم);
    ثابت bool transparent = (کړکۍ->flags & SDL_کړکۍ_TRANSPARENT) ? true : false;
    صحيح i;
    صحيح w, h;
    ثابت SDL_PixelFormat *texture_formats;

    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &w, &h);

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
            renderer = SDL_CreateRenderer(کړکۍ, render_driver);
            SDL_free(render_driver_copy);
            إذا (!renderer) {
                // The error for this specific renderer has already been set
                أرجع false;
            }
        } وإلا {
            SDL_assert(render_driver_copy == عدم);
            ثابت صحيح ټول = SDL_Get_عدد_Render_Drivers();
            لكل (i = 0; i < ټول; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                إذا (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(کړکۍ, name);
                    إذا (renderer) {
                        اكسر; // this will work.
                    }
                }
            }
            إذا (!renderer) {
                أرجع SDL_سېټ_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != عدم); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        معلومات = (SDL_کړکۍ_Texture_معلومات *)SDL_calloc(1, حجم(*معلومات));
        إذا (!معلومات) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }
        إذا (!SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر, معلومات)) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }

        معلومات->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_Get_اشاره_ګر_Property(SDL_GetRendererProperties(معلومات->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_اشاره_ګر, عدم);
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
            !SDL_ISPIXELFORMAT_10_بټ(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_شاخصي(texture_format) &&
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
    SDL_سېټ_Texture_Blend_ډېرپېښ(معلومات->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    معلومات->بایټونه_فی_pixel = SDL_BYTESPERPIXEL(*format);
    معلومات->pitch = (((w * معلومات->بایټونه_فی_pixel) + 3) & ~3);

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
    SDL_سېټ_Render_Viewport(معلومات->renderer, عدم);

    أرجع true;
}

bool SDL_سېټ_کړکۍ_Texture_VSync(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح vsync)
{
    SDL_کړکۍ_Texture_معلومات *معلومات;

    معلومات = (SDL_کړکۍ_Texture_معلومات *)SDL_Get_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر, عدم);
    إذا (!معلومات) {
        أرجع false;
    }
    إذا (!معلومات->renderer) {
        أرجع false;
    }
    أرجع SDL_سېټ_Render_VSync(معلومات->renderer, vsync);
}

ساكن bool SDL_Get_کړکۍ_Texture_VSync(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *vsync)
{
    SDL_کړکۍ_Texture_معلومات *معلومات;

    معلومات = (SDL_کړکۍ_Texture_معلومات *)SDL_Get_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر, عدم);
    إذا (!معلومات) {
        أرجع false;
    }
    إذا (!معلومات->renderer) {
        أرجع false;
    }
    أرجع SDL_GetRenderVSync(معلومات->renderer, vsync);
}

ساكن bool SDL_Update_کړکۍ_Texture(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_کړکۍ_Texture_معلومات *معلومات;
    SDL_Rect rect;
    فراغ *src;
    صحيح w, h;

    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &w, &h);

    معلومات = (SDL_کړکۍ_Texture_معلومات *)SDL_Get_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر, عدم);
    إذا (!معلومات || !معلومات->texture) {
        أرجع SDL_سېټ_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    إذا (SDL_Get_پراختیا_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (فراغ *)((Uint8 *)معلومات->pixels +
                       rect.y * معلومات->pitch +
                       rect.x * معلومات->بایټونه_فی_pixel);
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

ساكن فراغ SDL_Destroy_کړکۍ_Texture(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    إذا (SDL_HasProperty(props, SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر)) {
        SDL_کړکۍ_Texture_معلومات *معلومات = SDL_Get_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر, عدم);

        إذا (معلومات->texture) {
            SDL_DestroyTexture(معلومات->texture);
        }
        إذا (معلومات->renderer) {
            SDL_DestroyRenderer(معلومات->renderer);
        }
        SDL_free(معلومات->pixels);
        SDL_free(معلومات);

        SDL_ClearProperty(props, SDL_PROP_کړکۍ_TEXTUREDATA_اشاره_ګر);
    }
}

ساكن SDL_VideoDevice *_this = عدم;
ساكن SDL_AtomicInt SDL_messagebox_شمېر;

ساكن صحيح SDLCALL cmpmodes(ثابت فراغ *A, ثابت فراغ *B)
{
    ثابت SDL_Display_ډېرپېښ *a = (ثابت SDL_Display_ډېرپېښ *)A;
    ثابت SDL_Display_ډېرپېښ *b = (ثابت SDL_Display_ډېرپېښ *)B;
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
    أرجع SDL_سېټ_Error("Video subsystem has not been initialized");
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

ثابت حرف *SDL_GetVideoDriver(صحيح شاخص)
{
    CHECK_PARAM(شاخص < 0 || شاخص >= SDL_Get_عدد_Video_Drivers()) {
        SDL_InvalidParamError("index");
        أرجع عدم;
    }
    أرجع deduped_bootstrap[شاخص]->name;
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
#که_تعریف_شوی SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    إذا (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#د_که_پای
    إذا (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    إذا (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        طالما (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_پای_ټکی = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_پای_ټکی) ? (driver_attempt_پای_ټکی - driver_attempt)
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

            driver_attempt = (driver_attempt_پای_ټکی) ? (driver_attempt_پای_ټکی + 1) : عدم;
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
            SDL_سېټ_Error("%s not available", driver_name);
            اذهب pre_driver_error;
        }
        SDL_سېټ_Error("No available video device");
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
    SDL_GL_Reset_ځانګړتیاوې();

    // Initialize the video subsystem
    إذا (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        أرجع false;
    }

    // Make sure some displays were added
    إذا (_this->عدد_displays == 0) {
        SDL_QuitVideo();
        أرجع SDL_سېټ_Error("The video driver did not add any displays");
    }

    SDL_جمع_کړه_Hint_Callback(SDL_HINT_VIDEO_SYNC_کړکۍ_OPERATIONS, SDL_SyncHintWatcher, عدم);

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

فراغ SDL_سېټ_System_Theme(SDL_SystemTheme theme)
{
    إذا (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_بدل_شوی_Event();
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

ساكن فراغ SDL_Finalize_Display_ډېرپېښ(SDL_Display_ډېرپېښ *ډېرپېښ)
{
    // Make sure all the fields are set up correctly
    إذا (ډېرپېښ->pixel_density <= 0.0f) {
        ډېرپېښ->pixel_density = 1.0f;
    }

    إذا (ډېرپېښ->refresh_شرح_numerator > 0) {
        إذا (ډېرپېښ->refresh_شرح_denominator <= 0) {
            ډېرپېښ->refresh_شرح_denominator = 1;
        }
        ډېرپېښ->refresh_شرح = (عائم)ډېرپېښ->refresh_شرح_numerator / ډېرپېښ->refresh_شرح_denominator;
    } وإلا {
        SDL_CalculateFraction(ډېرپېښ->refresh_شرح, &ډېرپېښ->refresh_شرح_numerator, &ډېرپېښ->refresh_شرح_denominator);
    }
    ډېرپېښ->refresh_شرح = SDL_roundf(ډېرپېښ->refresh_شرح * 100) / 100.0f;
}

SDL_DisplayID SDL_جمع_کړه_Basic_Video_Display(ثابت SDL_Display_ډېرپېښ *desktop_ډېرپېښ)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    إذا (desktop_ډېرپېښ) {
        SDL_memcpy(&display.desktop_ډېرپېښ, desktop_ډېرپېښ, حجم(display.desktop_ډېرپېښ));
    }
    أرجع SDL_جمع_کړه_Video_Display(&display, false);
}

SDL_DisplayID SDL_جمع_کړه_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event)
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

    id = SDL_Get_بل_Object_ID();
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

    new_display->desktop_ډېرپېښ.displayID = id;
    new_display->current_ډېرپېښ = &new_display->desktop_ډېرپېښ;
    SDL_Finalize_Display_ډېرپېښ(&new_display->desktop_ډېرپېښ);

    لكل (i = 0; i < new_display->عدد_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_سېټ_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    إذا (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    أرجع id;
}

فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_کړکۍ *کړکۍ;

    // See if any windows have changed to the new display
    لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
        SDL_Check_کړکۍ_Display_بدل_شوی(کړکۍ);
    }
}

فراغ SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

فراغ SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    صحيح display_شاخص = SDL_Get_Display_شاخص(displayID);
    إذا (display_شاخص < 0) {
        أرجع;
    }

    display = _this->displays[display_شاخص];

    إذا (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_ډېرپېښ.دننی);
    display->desktop_ډېرپېښ.دننی = عدم;
    SDL_free(display->دننی);
    display->دننی = عدم;
    SDL_free(display);

    إذا (display_شاخص < (_this->عدد_displays - 1)) {
        SDL_memmove(&_this->displays[display_شاخص], &_this->displays[display_شاخص + 1], (_this->عدد_displays - display_شاخص - 1) * حجم(_this->displays[display_شاخص]));
    }
    --_this->عدد_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحيح *شمېر)
{
    صحيح i;
    SDL_DisplayID *displays;

    إذا (!_this) {
        إذا (شمېر) {
            *شمېر = 0;
        }

        SDL_UninitializedVideo();
        أرجع عدم;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->عدد_displays + 1) * حجم(*displays));
    إذا (displays) {
        إذا (شمېر) {
            *شمېر = _this->عدد_displays;
        }

        لكل (i = 0; i < _this->عدد_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } وإلا {
        إذا (شمېر) {
            *شمېر = 0;
        }
    }
    أرجع displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحيح display_شاخص;

    display_شاخص = SDL_Get_Display_شاخص(displayID);
    إذا (display_شاخص < 0) {
        أرجع عدم;
    }
    أرجع _this->displays[display_شاخص];
}

ساكن SDL_DisplayID Get_Display_For_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        displayID = کړکۍ->current_fullscreen_ډېرپېښ.displayID;
    }

    إذا (!displayID) {
        displayID = SDL_Get_Display_For_کړکۍ_Position(کړکۍ);
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, 0);

    أرجع SDL_GetVideoDisplay(Get_Display_For_کړکۍ(کړکۍ));
}

SDL_DisplayID SDL_GetPrimaryDisplay(فراغ)
{
    إذا (!_this || _this->عدد_displays == 0) {
        SDL_UninitializedVideo();
        أرجع 0;
    }
    أرجع _this->displays[0]->id;
}

صحيح SDL_Get_Display_شاخص(SDL_DisplayID displayID)
{
    صحيح display_شاخص;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع -1;
    }

    لكل (display_شاخص = 0; display_شاخص < _this->عدد_displays; ++display_شاخص) {
        إذا (displayID == _this->displays[display_شاخص]->id) {
            أرجع display_شاخص;
        }
    }
    SDL_سېټ_Error("Invalid display");
    أرجع -1;
}

SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->دننی;
}

SDL_Display_معلومات *SDL_Get_Display_Driver_معلومات_For_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, 0);

    أرجع SDL_Get_Display_Driver_معلومات(Get_Display_For_کړکۍ(کړکۍ));
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
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_شاخص(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_ډېرپېښ->w;
    rect->h = display->current_ډېرپېښ->h;
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

فراغ SDL_سېټ_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale)
{
    إذا (scale != display->content_scale) {
        SDL_کړکۍ *کړکۍ;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_بدل_شوی, 0, 0);

        // Check the windows on this display
        لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
            إذا (display->id == کړکۍ->displayID) {
                SDL_Check_کړکۍ_Display_Scale_بدل_شوی(کړکۍ);
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

فراغ SDL_سېټ_کړکۍ_HDRProperties(SDL_کړکۍ *کړکۍ, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    إذا (کړکۍ->HDR.HDR_headroom != HDR_clamped.HDR_headroom || کړکۍ->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID کړکۍ_props = SDL_Get_کړکۍ_Properties(کړکۍ);

        SDL_سېټ_Float_Property(کړکۍ_props, SDL_PROP_کړکۍ_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_سېټ_Float_Property(کړکۍ_props, SDL_PROP_کړکۍ_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_سېټ_Boolean_Property(کړکۍ_props, SDL_PROP_کړکۍ_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&کړکۍ->HDR, &HDR_clamped);

        إذا (send_event) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_HDR_STATE_بدل_شوی, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

فراغ SDL_سېټ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ثابت bool بدل_شوی = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	إذا (بدل_شوی) {
		SDL_سېټ_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    إذا (بدل_شوی && !SDL_DriverSendsHDRChanges(_this)) {
        لكل (SDL_کړکۍ *w = display->device->windows; w; w = w->بل) {
            إذا (Get_Display_For_کړکۍ(w) == display->id) {
                SDL_سېټ_کړکۍ_HDRProperties(w, &display->HDR, true);
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
ساكن ثابت SDL_Display_ډېرپېښ *SDL_Get_Fullscreen_ډېرپېښ_سمون(ثابت SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_VideoDisplay *display;
    SDL_Display_ډېرپېښ fullscreen_ډېرپېښ;

    إذا (ډېرپېښ->w <= 0 || ډېرپېښ->h <= 0) {
        // Use the desktop mode
        أرجع عدم;
    }

    SDL_memcpy(&fullscreen_ډېرپېښ, ډېرپېښ, حجم(fullscreen_ډېرپېښ));
    إذا (fullscreen_ډېرپېښ.displayID == 0) {
        fullscreen_ډېرپېښ.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_ډېرپېښ(&fullscreen_ډېرپېښ);

    ډېرپېښ = عدم;

    display = SDL_GetVideoDisplay(fullscreen_ډېرپېښ.displayID);
    إذا (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        إذا (!ډېرپېښ) {
            لكل (صحيح i = 0; i < display->عدد_fullscreen_modes; ++i) {
                إذا (SDL_memcmp(&fullscreen_ډېرپېښ, &display->fullscreen_modes[i], حجم(fullscreen_ډېرپېښ)) == 0) {
                    ډېرپېښ = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }

        // Search for a mode with the same characteristics
        إذا (!ډېرپېښ) {
            لكل (صحيح i = 0; i < display->عدد_fullscreen_modes; ++i) {
                إذا (cmpmodes(&fullscreen_ډېرپېښ, &display->fullscreen_modes[i]) == 0) {
                    ډېرپېښ = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }
    }
    أرجع ډېرپېښ;
}

bool SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(SDL_VideoDisplay *display, ثابت SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_Display_ډېرپېښ *modes;
    SDL_Display_ډېرپېښ new_ډېرپېښ;
    صحيح i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_ډېرپېښ, ډېرپېښ, حجم(new_ډېرپېښ));
    new_ډېرپېښ.displayID = display->id;
    SDL_Finalize_Display_ډېرپېښ(&new_ډېرپېښ);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->عدد_fullscreen_modes;
    لكل (i = 0; i < nmodes; ++i) {
        إذا (cmpmodes(&new_ډېرپېښ, &modes[i]) == 0) {
            أرجع false;
        }
    }

    // Go ahead and add the new mode
    إذا (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_ډېرپېښ *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        إذا (!modes) {
            أرجع false;
        }

        إذا (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            لكل (i = 0; i < nmodes; ++i) {
                إذا (display->current_ډېرپېښ == &display->fullscreen_modes[i]) {
                    display->current_ډېرپېښ = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->عدد_fullscreen_modes++], &new_ډېرپېښ, حجم(new_ډېرپېښ));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->عدد_fullscreen_modes,
              حجم(SDL_Display_ډېرپېښ), cmpmodes);

    أرجع true;
}

فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحيح i;

    لكل (i = display->عدد_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].دننی);
        display->fullscreen_modes[i].دننی = عدم;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = عدم;
    display->عدد_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_ډېرپېښ = &display->desktop_ډېرپېښ;
}

SDL_Display_ډېرپېښ **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحيح *شمېر)
{
    صحيح i;
    صحيح عدد_modes;
    SDL_Display_ډېرپېښ **پایله;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    إذا (شمېر) {
        *شمېر = 0;
    }

    CHECK_DISPLAY_MAGIC(display, عدم);

    SDL_UpdateFullscreenDisplayModes(display);

    عدد_modes = display->عدد_fullscreen_modes;
    پایله = (SDL_Display_ډېرپېښ **)SDL_malloc((عدد_modes + 1) * حجم(*پایله) + عدد_modes * حجم(**پایله));
    إذا (پایله) {
        SDL_Display_ډېرپېښ *modes = (SDL_Display_ډېرپېښ *)((Uint8 *)پایله + ((عدد_modes + 1) * حجم(*پایله)));
        إذا (عدد_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, عدد_modes * حجم(*modes));
        }
        لكل (i = 0; i < عدد_modes; ++i) {
            پایله[i] = modes++;
        }
        پایله[i] = عدم;

        إذا (شمېر) {
            *شمېر = عدد_modes;
        }
    } وإلا {
        إذا (شمېر) {
            *شمېر = 0;
        }
    }
    أرجع پایله;
}

bool SDL_Get_Closest_Fullscreen_Display_ډېرپېښ(SDL_DisplayID displayID, صحيح w, صحيح h, عائم refresh_شرح, bool include_لوړ_density_modes, SDL_Display_ډېرپېښ *پایله)
{
    CHECK_PARAM(!پایله) {
        أرجع SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_Display_ډېرپېښ *ډېرپېښ, *closest = عدم;
    عائم aspect_نسبت;
    صحيح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(پایله);

    CHECK_DISPLAY_MAGIC(display, false);

    إذا (h > 0) {
        aspect_نسبت = (عائم)w / h;
    } وإلا {
        aspect_نسبت = 1.0f;
    }

    إذا (refresh_شرح == 0.0f) {
        refresh_شرح = display->desktop_ډېرپېښ.refresh_شرح;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    لكل (i = 0; i < display->عدد_fullscreen_modes; ++i) {
        ډېرپېښ = &display->fullscreen_modes[i];

        إذا (w > ډېرپېښ->w) {
            // Out of sorted modes large enough here
            اكسر;
        }
        إذا (h > ډېرپېښ->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            استمر;
        }
        إذا (ډېرپېښ->pixel_density > 1.0f && !include_لوړ_density_modes) {
            استمر;
        }
        إذا (closest) {
            عائم current_aspect_نسبت = (عائم)ډېرپېښ->w / ډېرپېښ->h;
            عائم closest_aspect_نسبت = (عائم)closest->w / closest->h;
            إذا (SDL_fabsf(aspect_نسبت - closest_aspect_نسبت) < SDL_fabsf(aspect_نسبت - current_aspect_نسبت)) {
                // The mode we already found has a better aspect ratio match
                استمر;
            }

            إذا (ډېرپېښ->w == closest->w && ډېرپېښ->h == closest->h) {
                إذا (SDL_fabsf(closest->refresh_شرح - refresh_شرح) < SDL_fabsf(ډېرپېښ->refresh_شرح - refresh_شرح)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    استمر;
                }
                إذا (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(ډېرپېښ->format)) {
                    // Prefer the highest color depth
                    استمر;
                }
            }
        }

        closest = ډېرپېښ;
    }
    إذا (!closest) {
        أرجع SDL_سېټ_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(پایله, closest);

    أرجع true;
}

ساكن bool Display_ډېرپېښ_بدل_شوی(ثابت SDL_Display_ډېرپېښ *old_ډېرپېښ, ثابت SDL_Display_ډېرپېښ *new_ډېرپېښ)
{
    أرجع ((old_ډېرپېښ->displayID && old_ډېرپېښ->displayID != new_ډېرپېښ->displayID) ||
            (old_ډېرپېښ->format && old_ډېرپېښ->format != new_ډېرپېښ->format) ||
            (old_ډېرپېښ->w && old_ډېرپېښ->h && (old_ډېرپېښ->w != new_ډېرپېښ->w ||old_ډېرپېښ->h != new_ډېرپېښ->h)) ||
            (old_ډېرپېښ->pixel_density != 0.0f && old_ډېرپېښ->pixel_density != new_ډېرپېښ->pixel_density) ||
            (old_ډېرپېښ->refresh_شرح != 0.0f && old_ډېرپېښ->refresh_شرح != new_ډېرپېښ->refresh_شرح));
}

فراغ SDL_سېټ_Desktop_Display_ډېرپېښ(SDL_VideoDisplay *display, ثابت SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_Display_ډېرپېښ وروستی_ډېرپېښ;

    إذا (display->fullscreen_فعال) {
        // This is a temporary mode change, don't save the desktop mode
        أرجع;
    }

    SDL_copyp(&وروستی_ډېرپېښ, &display->desktop_ډېرپېښ);

    SDL_free(display->desktop_ډېرپېښ.دننی);
    SDL_copyp(&display->desktop_ډېرپېښ, ډېرپېښ);
    display->desktop_ډېرپېښ.displayID = display->id;
    SDL_Finalize_Display_ډېرپېښ(&display->desktop_ډېرپېښ);

    إذا (Display_ډېرپېښ_بدل_شوی(&وروستی_ډېرپېښ, &display->desktop_ډېرپېښ)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_ډېرپېښ_بدل_شوی, ډېرپېښ->w, ډېرپېښ->h);
        إذا (display->current_ډېرپېښ == &display->desktop_ډېرپېښ) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_ډېرپېښ_بدل_شوی, ډېرپېښ->w, ډېرپېښ->h);
        }
    }
}

ثابت SDL_Display_ډېرپېښ *SDL_Get_Desktop_Display_ډېرپېښ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع &display->desktop_ډېرپېښ;
}

فراغ SDL_سېټ_Current_Display_ډېرپېښ(SDL_VideoDisplay *display, ثابت SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_Display_ډېرپېښ وروستی_ډېرپېښ;

    إذا (display->current_ډېرپېښ) {
        SDL_copyp(&وروستی_ډېرپېښ, display->current_ډېرپېښ);
    } وإلا {
        SDL_zero(وروستی_ډېرپېښ);
    }

    display->current_ډېرپېښ = ډېرپېښ;

    إذا (Display_ډېرپېښ_بدل_شوی(&وروستی_ډېرپېښ, ډېرپېښ)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_ډېرپېښ_بدل_شوی, ډېرپېښ->w, ډېرپېښ->h);
    }
}

ثابت SDL_Display_ډېرپېښ *SDL_Get_Current_Display_ډېرپېښ(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->current_ډېرپېښ;
}

bool SDL_سېټ_Display_ډېرپېښ_For_Display(SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    إذا (SDL_ډېرپېښ_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        أرجع true;
    }

    إذا (!ډېرپېښ) {
        ډېرپېښ = &display->desktop_ډېرپېښ;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#که_نه_تعریف_شوی SDL_PLATFORM_RISCOS
    إذا (ډېرپېښ == display->current_ډېرپېښ) {
        أرجع true;
    }
#د_که_پای

    // Actually change the display mode
    إذا (_this->سېټ_Display_ډېرپېښ) {
        bool پایله;

        _this->setting_display_ډېرپېښ = true;
        پایله = _this->سېټ_Display_ډېرپېښ(_this, display, ډېرپېښ);
        _this->setting_display_ډېرپېښ = false;
        إذا (!پایله) {
            أرجع false;
        }
    }

    SDL_سېټ_Current_Display_ډېرپېښ(display, ډېرپېښ);

    أرجع true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساكن فراغ SDL_Get_Closest_ټکی_On_Rect(ثابت SDL_Rect *rect, SDL_ټکی *ټکی)
{
    ثابت صحيح ښی = rect->x + rect->w - 1;
    ثابت صحيح bottom = rect->y + rect->h - 1;

    إذا (ټکی->x < rect->x) {
        ټکی->x = rect->x;
    } وإلا إذا (ټکی->x > ښی) {
        ټکی->x = ښی;
    }

    إذا (ټکی->y < rect->y) {
        ټکی->y = rect->y;
    } وإلا إذا (ټکی->y > bottom) {
        ټکی->y = bottom;
    }
}

ساكن SDL_DisplayID GetDisplayForRect(صحيح x, صحيح y, صحيح w, صحيح h)
{
    صحيح i, dist;
    SDL_DisplayID closest = 0;
    صحيح closest_dist = 0x7FFFFFFF;
    SDL_ټکی closest_ټکی_on_display;
    SDL_ټکی delta;
    SDL_ټکی center;
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
            closest_ټکی_on_display = center;
            SDL_Get_Closest_ټکی_On_Rect(&display_rect, &closest_ټکی_on_display);

            delta.x = center.x - closest_ټکی_on_display.x;
            delta.y = center.y - closest_ټکی_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            إذا (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    إذا (closest == 0) {
        SDL_سېټ_Error("Couldn't find any displays");
    }

    أرجع closest;
}

فراغ SDL_Relative_منزل_Global_For_کړکۍ(SDL_کړکۍ *کړکۍ, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y)
{
    SDL_کړکۍ *w;

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        // Calculate the total offset of the popup from the parents
        لكل (w = کړکۍ->پلار; w; w = w->پلار) {
            rel_x += w->x;
            rel_y += w->y;

            إذا (!SDL_کړکۍ_IS_POPUP(w)) {
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

فراغ SDL_Global_منزل_Relative_For_کړکۍ(SDL_کړکۍ *کړکۍ, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y)
{
    SDL_کړکۍ *w;

    إذا (SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        // Convert absolute window coordinates to relative for a popup
        لكل (w = کړکۍ->پلار; w; w = w->پلار) {
            abs_x -= w->x;
            abs_y -= w->y;

            إذا (!SDL_کړکۍ_IS_POPUP(w)) {
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

SDL_DisplayID SDL_Get_Display_For_ټکی(ثابت SDL_ټکی *ټکی)
{
    CHECK_PARAM(!ټکی) {
        SDL_InvalidParamError("point");
        أرجع 0;
    }

    أرجع GetDisplayForRect(ټکی->x, ټکی->y, 1, 1);
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

SDL_DisplayID SDL_Get_Display_For_کړکۍ_Position(SDL_کړکۍ *کړکۍ)
{
    صحيح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_کړکۍ_MAGIC(کړکۍ, 0);

    إذا (_this->Get_Display_For_کړکۍ) {
        displayID = _this->Get_Display_For_کړکۍ(_this, کړکۍ);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_منزل_Global_For_کړکۍ(کړکۍ, کړکۍ->x, کړکۍ->y, &x, &y);

    إذا (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } وإلا {
            displayID = GetDisplayForRect(x, y, کړکۍ->w, کړکۍ->h);
        }
    }
    إذا (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    SDL_DisplayID displayID = 0;

    CHECK_کړکۍ_MAGIC(کړکۍ, عدم);

    // An explicit fullscreen display overrides all
    إذا (کړکۍ->current_fullscreen_ډېرپېښ.displayID) {
        displayID = کړکۍ->current_fullscreen_ډېرپېښ.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    إذا (!displayID) {
        displayID = کړکۍ->pending_displayID;
    }
    إذا (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحيح x = کړکۍ->وروستی_position_pending ? کړکۍ->pending.x : کړکۍ->x;
        ثابت صحيح y = کړکۍ->وروستی_position_pending ? کړکۍ->pending.y : کړکۍ->y;
        ثابت صحيح w = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : کړکۍ->w;
        ثابت صحيح h = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : کړکۍ->h;

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

#تعریف_کړه SDL_PROP_SDL2_COMPAT_کړکۍ_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID کړکۍ_props = SDL_Get_کړکۍ_Properties(کړکۍ);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_کړکۍ(کړکۍ);
    إذا (fs_display) {
        SDL_سېټ_شمېره_Property(کړکۍ_props, SDL_PROP_SDL2_COMPAT_کړکۍ_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } وإلا {
        SDL_ClearProperty(کړکۍ_props, SDL_PROP_SDL2_COMPAT_کړکۍ_PREFERRED_FULLSCREEN_DISPLAY);
    }

    أرجع Get_Display_For_کړکۍ(کړکۍ);
}

ساكن فراغ SDL_Check_کړکۍ_Display_بدل_شوی(SDL_کړکۍ *کړکۍ)
{
    إذا (SDL_SendsDisplayChanges(_this)) {
        أرجع;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_کړکۍ_Position(کړکۍ);

    إذا (displayID != کړکۍ->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect کړکۍ_rect;
        SDL_Rect old_overlap, new_overlap;

        إذا (SDL_GetDisplayBounds(کړکۍ->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            کړکۍ_rect.x = کړکۍ->x;
            کړکۍ_rect.y = کړکۍ->y;
            کړکۍ_rect.w = کړکۍ->w;
            کړکۍ_rect.h = کړکۍ->h;

            إذا (SDL_GetRectIntersection(&old_bounds, &کړکۍ_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &کړکۍ_rect, &new_overlap)) {
                صحيح old_area = old_overlap.w * old_overlap.h;
                صحيح new_area = new_overlap.w * new_overlap.h;
                عائم new_overlap_نسبت = (new_area / ((عائم)old_area + new_area));
                إذا (new_overlap_نسبت < 0.80) {
                    أرجع;
                }
            }
        }
    }

    إذا (displayID != کړکۍ->displayID) {
        صحيح i, display_شاخص;

        // Sanity check our fullscreen windows
        display_شاخص = SDL_Get_Display_شاخص(displayID);
        لكل (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            إذا (display->fullscreen_کړکۍ == کړکۍ) {
                إذا (display_شاخص != i) {
                    إذا (display_شاخص < 0) {
                        display_شاخص = i;
                    } وإلا {
                        SDL_VideoDisplay *new_display = _this->displays[display_شاخص];

                        // The window was moved to a different display
                        إذا (new_display->fullscreen_کړکۍ &&
                            new_display->fullscreen_کړکۍ != کړکۍ) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_کړکۍ(new_display->fullscreen_کړکۍ);
                        }
                        new_display->fullscreen_کړکۍ = کړکۍ;
                        display->fullscreen_کړکۍ = عدم;
                    }
                }
                اكسر;
            }
        }

        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_DISPLAY_بدل_شوی, (صحيح)displayID, 0);
    }
}

عائم SDL_Get_کړکۍ_Pixel_Density(SDL_کړکۍ *کړکۍ)
{
    صحيح کړکۍ_w, کړکۍ_h, pixel_w, pixel_h;
    عائم pixel_density = 1.0f;

    CHECK_کړکۍ_MAGIC(کړکۍ, 0.0f);

    إذا (SDL_Get_کړکۍ_اندازه(کړکۍ, &کړکۍ_w, &کړکۍ_h) &&
        SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &pixel_w, &pixel_h)) {
        pixel_density = (عائم)pixel_w / کړکۍ_w;
    }
    أرجع pixel_density;
}

عائم SDL_Get_کړکۍ_Display_Scale(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, 0.0f);

    أرجع کړکۍ->display_scale;
}

ساكن فراغ SDL_Check_کړکۍ_Display_Scale_بدل_شوی(SDL_کړکۍ *کړکۍ)
{
    عائم display_scale;

    إذا (_this->Get_کړکۍ_Content_Scale) {
        display_scale = _this->Get_کړکۍ_Content_Scale(_this, کړکۍ);
    } وإلا {
        ثابت عائم pixel_density = SDL_Get_کړکۍ_Pixel_Density(کړکۍ);
        ثابت عائم content_scale = SDL_GetDisplayContentScale(کړکۍ->displayID);

        display_scale = pixel_density * content_scale;
    }

    إذا (display_scale != کړکۍ->display_scale) {
        کړکۍ->display_scale = display_scale;
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_DISPLAY_SCALE_بدل_شوی, 0, 0);
    }
}

bool SDL_Update_Fullscreen_ډېرپېښ(SDL_کړکۍ *کړکۍ, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = عدم;
    SDL_Display_ډېرپېښ *ډېرپېښ = عدم;
    صحيح i;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    کړکۍ->fullscreen_exclusive = false;
    کړکۍ->update_fullscreen_on_display_بدل_شوی = false;

    // If we are in the process of hiding don't go back to fullscreen
    إذا (کړکۍ->is_destroying || کړکۍ->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    إذا (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_کړکۍ(کړکۍ);
        إذا (!display) {
            // This should never happen, but it did...
            اذهب بشپړ;
        }
    } وإلا {
        لكل (i = 0; i < _this->عدد_displays; ++i) {
            display = _this->displays[i];
            إذا (display->fullscreen_کړکۍ == کړکۍ) {
                اكسر;
            }
        }
        إذا (!display || i == _this->عدد_displays) {
            // Already not fullscreen on any display
            display = عدم;
        }
    }

    إذا (fullscreen) {
        ډېرپېښ = (SDL_Display_ډېرپېښ *)SDL_Get_کړکۍ_Fullscreen_ډېرپېښ(کړکۍ);
        إذا (ډېرپېښ) {
            کړکۍ->fullscreen_exclusive = true;
        } وإلا {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(کړکۍ->current_fullscreen_ډېرپېښ);
        }
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (کړکۍ->is_destroying && !کړکۍ->وروستی_fullscreen_exclusive_display) {
            کړکۍ->fullscreen_exclusive = false;
            إذا (display) {
                display->fullscreen_کړکۍ = عدم;
            }
            اذهب بشپړ;
        }
        إذا (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            إذا (fullscreen && Cocoa_Is_کړکۍ_دننه_Fullscreen_Space(کړکۍ) && !کړکۍ->وروستی_fullscreen_exclusive_display && کړکۍ->fullscreen_exclusive) {
                إذا (!Cocoa_سېټ_کړکۍ_Fullscreen_Space(کړکۍ, false, true)) {
                    اذهب error;
                }
            } وإلا إذا (fullscreen && کړکۍ->وروستی_fullscreen_exclusive_display && !کړکۍ->fullscreen_exclusive) {
                لكل (i = 0; i < _this->عدد_displays; ++i) {
                    SDL_VideoDisplay *وروستی_display = _this->displays[i];
                    إذا (وروستی_display->fullscreen_کړکۍ == کړکۍ) {
                        SDL_سېټ_Display_ډېرپېښ_For_Display(وروستی_display, عدم);
                        إذا (_this->سېټ_کړکۍ_Fullscreen) {
                            _this->سېټ_کړکۍ_Fullscreen(_this, کړکۍ, وروستی_display, false);
                        }
                        وروستی_display->fullscreen_کړکۍ = عدم;
                    }
                }
            }

            إذا (Cocoa_سېټ_کړکۍ_Fullscreen_Space(کړکۍ, !!fullscreen, syncHint)) {
                اذهب بشپړ;
            }
        }
    }
#د_که_پای

    إذا (display) {
        // Restore the video mode on other displays if needed
        لكل (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            إذا (other != display && other->fullscreen_کړکۍ == کړکۍ) {
                SDL_سېټ_Display_ډېرپېښ_For_Display(other, عدم);
                other->fullscreen_کړکۍ = عدم;
            }
        }
    }

    إذا (fullscreen) {
        صحيح ډېرپېښ_w = 0, ډېرپېښ_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        إذا (display->fullscreen_کړکۍ &&
            display->fullscreen_کړکۍ != کړکۍ) {
            SDL_Minimize_کړکۍ(display->fullscreen_کړکۍ);
        }

        display->fullscreen_فعال = کړکۍ->fullscreen_exclusive;

        إذا (!SDL_سېټ_Display_ډېرپېښ_For_Display(display, ډېرپېښ)) {
            اذهب error;
        }
        إذا (commit) {
            SDL_Fullscreen_پایله ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->سېټ_کړکۍ_Fullscreen) {
                ret = _this->سېټ_کړکۍ_Fullscreen(_this, کړکۍ, display, fullscreen);
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
                    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_ENTER_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_فعال = false;
                اذهب error;
            }
        }

        إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
            display->fullscreen_کړکۍ = کړکۍ;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                إذا (ډېرپېښ) {
                    ډېرپېښ_w = ډېرپېښ->w;
                    ډېرپېښ_h = ډېرپېښ->h;
                    SDL_GetDisplayBounds(ډېرپېښ->displayID, &displayRect);
                } وإلا {
                    ډېرپېښ_w = display->desktop_ډېرپېښ.w;
                    ډېرپېښ_h = display->desktop_ډېرپېښ.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                إذا (کړکۍ->w != ډېرپېښ_w || کړکۍ->h != ډېرپېښ_h) {
                    resized = true;
                }

                SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, displayRect.x, displayRect.y);

                إذا (resized) {
                    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, ډېرپېښ_w, ډېرپېښ_h);
                } وإلا {
                    SDL_On_کړکۍ_Resized(کړکۍ);
                }
            }
        }
    } وإلا {
        bool resized = false;

        // Restore the desktop mode
        إذا (display) {
            display->fullscreen_فعال = false;

            SDL_سېټ_Display_ډېرپېښ_For_Display(display, عدم);
        }
        إذا (commit) {
            SDL_Fullscreen_پایله ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->سېټ_کړکۍ_Fullscreen) {
                SDL_VideoDisplay *ډک_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_کړکۍ(کړکۍ);
                إذا (ډک_screen_display) {
                    ret = _this->سېټ_کړکۍ_Fullscreen(_this, کړکۍ, ډک_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
                    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_LEAVE_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                اذهب error;
            }
        }

        إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
            إذا (display) {
                display->fullscreen_کړکۍ = عدم;
            }

            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MOVED, کړکۍ->windowed.x, کړکۍ->windowed.y);
                إذا (resized) {
                    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESIZED, کړکۍ->windowed.w, کړکۍ->windowed.h);
                } وإلا {
                    SDL_On_کړکۍ_Resized(کړکۍ);
                }
            }
        }
    }

بشپړ:
    کړکۍ->وروستی_fullscreen_exclusive_display = display && (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && کړکۍ->fullscreen_exclusive ? display->id : 0;
    أرجع true;

error:
    إذا (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    أرجع false;
}

bool SDL_سېټ_کړکۍ_Fullscreen_ډېرپېښ(SDL_کړکۍ *کړکۍ, ثابت SDL_Display_ډېرپېښ *ډېرپېښ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (ډېرپېښ) {
        إذا (!SDL_Get_Fullscreen_ډېرپېښ_سمون(ډېرپېښ)) {
            أرجع SDL_سېټ_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&کړکۍ->requested_fullscreen_ډېرپېښ, ډېرپېښ);
    } وإلا {
        SDL_zero(کړکۍ->requested_fullscreen_ډېرپېښ);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&کړکۍ->current_fullscreen_ډېرپېښ, &کړکۍ->requested_fullscreen_ډېرپېښ);

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_کړکۍ_دننه_Fullscreen_Space_Transition(کړکۍ)) {
        SDL_Sync_کړکۍ(کړکۍ);
    }
#د_که_پای
    إذا (SDL_کړکۍ_FULLSCREEN_VISIBLE(کړکۍ)) {
        SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(کړکۍ);
    }

    أرجع true;
}

ثابت SDL_Display_ډېرپېښ *SDL_Get_کړکۍ_Fullscreen_ډېرپېښ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, عدم);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, عدم);

    إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        أرجع SDL_Get_Fullscreen_ډېرپېښ_سمون(&کړکۍ->current_fullscreen_ډېرپېښ);
    } وإلا {
        أرجع SDL_Get_Fullscreen_ډېرپېښ_سمون(&کړکۍ->requested_fullscreen_ډېرپېښ);
    }
}

فراغ *SDL_Get_کړکۍ_ICCProfile(SDL_کړکۍ *کړکۍ, size_t *اندازه)
{
    إذا (!_this->Get_کړکۍ_ICCProfile) {
        SDL_Unsupported();
        أرجع عدم;
    }
    أرجع _this->Get_کړکۍ_ICCProfile(_this, کړکۍ, اندازه);
}

SDL_PixelFormat SDL_Get_کړکۍ_Pixel_Format(SDL_کړکۍ *کړکۍ)
{
    SDL_DisplayID displayID;
    ثابت SDL_Display_ډېرپېښ *ډېرپېښ;

    CHECK_کړکۍ_MAGIC(کړکۍ, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_کړکۍ(کړکۍ);
    ډېرپېښ = SDL_Get_Current_Display_ډېرپېښ(displayID);
    إذا (ډېرپېښ) {
        أرجع ډېرپېښ->format;
    } وإلا {
        أرجع SDL_PIXELFORMAT_UNKNOWN;
    }
}

#تعریف_کړه CREATE_FLAGS \
    (SDL_کړکۍ_OPENGL | SDL_کړکۍ_BORDERLESS | SDL_کړکۍ_RESIZABLE | SDL_کړکۍ_لوړ_PIXEL_DENSITY | SDL_کړکۍ_ALWAYS_ON_سر | SDL_کړکۍ_POPUP_MENU | SDL_کړکۍ_UTILITY | SDL_کړکۍ_TOOLTIP | SDL_کړکۍ_VULKAN | SDL_کړکۍ_MINIMIZED | SDL_کړکۍ_METAL | SDL_کړکۍ_TRANSPARENT | SDL_کړکۍ_NOT_FOCUSABLE | SDL_کړکۍ_FILL_DOCUMENT)

ساكن SDL_INLINE bool IsAcceptingDragAndDrop(فراغ)
{
    إذا (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_متن)) {
        أرجع true;
    }
    أرجع false;
}

// prepare a newly-created window
ساكن SDL_INLINE فراغ PrepareDragAndDropSupport(SDL_کړکۍ *کړکۍ)
{
    إذا (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(کړکۍ, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
فراغ SDL_ToggleDragAndDropSupport(فراغ)
{
    إذا (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_کړکۍ *کړکۍ;
        لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
            _this->AcceptDragAndDrop(کړکۍ, enable);
        }
    }
}

SDL_کړکۍ ** SDLCALL SDL_GetWindows(صحيح *شمېر)
{
    إذا (شمېر) {
        *شمېر = 0;
    }

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    SDL_کړکۍ *کړکۍ;
    صحيح عدد_added = 0;
    صحيح عدد_windows = 0;
    لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
        ++عدد_windows;
    }

    SDL_کړکۍ **windows = (SDL_کړکۍ **)SDL_malloc((عدد_windows + 1) * حجم(*windows));
    إذا (!windows) {
        أرجع عدم;
    }

    لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
        windows[عدد_added++] = کړکۍ;
        إذا (عدد_added == عدد_windows) {
            // Race condition? Multi-threading not supported, ignore it
            اكسر;
        }
    }
    windows[عدد_added] = عدم;

    إذا (شمېر) {
        *شمېر = عدد_added;
    }
    أرجع windows;
}

ساكن فراغ Apply_کړکۍ_Flags(SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags)
{
    إذا (!SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        إذا (!(flags & (SDL_کړکۍ_MINIMIZED | SDL_کړکۍ_MAXIMIZED))) {
            SDL_Restore_کړکۍ(کړکۍ);
        }
        إذا (flags & SDL_کړکۍ_MAXIMIZED) {
            SDL_Maximize_کړکۍ(کړکۍ);
        }

        SDL_سېټ_کړکۍ_Fullscreen(کړکۍ, (flags & SDL_کړکۍ_FULLSCREEN) != 0);

        إذا (flags & SDL_کړکۍ_MINIMIZED) {
            SDL_Minimize_کړکۍ(کړکۍ);
        }

        إذا (flags & SDL_کړکۍ_MODAL) {
            SDL_سېټ_کړکۍ_Modal(کړکۍ, true);
        }

        إذا (flags & SDL_کړکۍ_MOUSE_GRABBED) {
            SDL_سېټ_کړکۍ_Mouse_Grab(کړکۍ, true);
        }
        إذا (flags & SDL_کړکۍ_KEYBOARD_GRABBED) {
            SDL_سېټ_کړکۍ_Keyboard_Grab(کړکۍ, true);
        }
    }
}

ساكن فراغ SDL_پای_کړکۍ_Creation(SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags)
{
    PrepareDragAndDropSupport(کړکۍ);

    إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } وإلا {
        Apply_کړکۍ_Flags(کړکۍ, flags);
        إذا (!(flags & SDL_کړکۍ_HIDDEN)) {
            SDL_Show_کړکۍ(کړکۍ);
        }
    }

#إذا defined(SDL_PLATFORM_LINUX)
    إذا (!SDL_کړکۍ_IS_POPUP(کړکۍ)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_سېټ_کړکۍ_پرمختګ_State(کړکۍ, SDL_پرمختګ_STATE_NONE);
        SDL_سېټ_کړکۍ_پرمختګ_ارزښت(کړکۍ, 0.0f);
    }
#د_که_پای
}

ساكن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    أرجع SDL_سېټ_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساكن bool SDL_DllNotSupported(ثابت حرف *name)
{
    أرجع SDL_سېټ_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ساكن بنية {
    ثابت حرف *property_name;
    SDL_کړکۍ_Flags flag;
    bool invert_ارزښت;
} SDL_کړکۍ_Flag_Properties[] = {
    { SDL_PROP_کړکۍ_CREATE_ALWAYS_ON_سر_BOOLEAN,      SDL_کړکۍ_ALWAYS_ON_سر,       false },
    { SDL_PROP_کړکۍ_CREATE_BORDERLESS_BOOLEAN,         SDL_کړکۍ_BORDERLESS,          false },
    { SDL_PROP_کړکۍ_CREATE_FOCUSABLE_BOOLEAN,          SDL_کړکۍ_NOT_FOCUSABLE,       true },
    { SDL_PROP_کړکۍ_CREATE_FULLSCREEN_BOOLEAN,         SDL_کړکۍ_FULLSCREEN,          false },
    { SDL_PROP_کړکۍ_CREATE_HIDDEN_BOOLEAN,             SDL_کړکۍ_HIDDEN,              false },
    { SDL_PROP_کړکۍ_CREATE_لوړ_PIXEL_DENSITY_BOOLEAN, SDL_کړکۍ_لوړ_PIXEL_DENSITY,  false },
    { SDL_PROP_کړکۍ_CREATE_MAXIMIZED_BOOLEAN,          SDL_کړکۍ_MAXIMIZED,           false },
    { SDL_PROP_کړکۍ_CREATE_MENU_BOOLEAN,               SDL_کړکۍ_POPUP_MENU,          false },
    { SDL_PROP_کړکۍ_CREATE_METAL_BOOLEAN,              SDL_کړکۍ_METAL,               false },
    { SDL_PROP_کړکۍ_CREATE_MINIMIZED_BOOLEAN,          SDL_کړکۍ_MINIMIZED,           false },
    { SDL_PROP_کړکۍ_CREATE_MODAL_BOOLEAN,              SDL_کړکۍ_MODAL,               false },
    { SDL_PROP_کړکۍ_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_کړکۍ_MOUSE_GRABBED,       false },
    { SDL_PROP_کړکۍ_CREATE_OPENGL_BOOLEAN,             SDL_کړکۍ_OPENGL,              false },
    { SDL_PROP_کړکۍ_CREATE_RESIZABLE_BOOLEAN,          SDL_کړکۍ_RESIZABLE,           false },
    { SDL_PROP_کړکۍ_CREATE_TRANSPARENT_BOOLEAN,        SDL_کړکۍ_TRANSPARENT,         false },
    { SDL_PROP_کړکۍ_CREATE_TOOLTIP_BOOLEAN,            SDL_کړکۍ_TOOLTIP,             false },
    { SDL_PROP_کړکۍ_CREATE_UTILITY_BOOLEAN,            SDL_کړکۍ_UTILITY,             false },
    { SDL_PROP_کړکۍ_CREATE_VULKAN_BOOLEAN,             SDL_کړکۍ_VULKAN,              false }
};

ساكن SDL_کړکۍ_Flags SDL_Get_کړکۍ_Flag_Properties(SDL_PropertiesID props)
{
    بینښه i;
    SDL_کړکۍ_Flags flags = (SDL_کړکۍ_Flags)SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_FLAGS_شمېره, 0);

    لكل (i = 0; i < SDL_arraysize(SDL_کړکۍ_Flag_Properties); ++i) {
        إذا (SDL_کړکۍ_Flag_Properties[i].invert_ارزښت) {
            إذا (!SDL_GetBooleanProperty(props, SDL_کړکۍ_Flag_Properties[i].property_name, true)) {
                flags |= SDL_کړکۍ_Flag_Properties[i].flag;
            }
        } وإلا {
            إذا (SDL_GetBooleanProperty(props, SDL_کړکۍ_Flag_Properties[i].property_name, false)) {
                flags |= SDL_کړکۍ_Flag_Properties[i].flag;
            }
        }
    }
    أرجع flags;
}

SDL_کړکۍ *SDL_Create_کړکۍ_With_Properties(SDL_PropertiesID props)
{
    SDL_کړکۍ *کړکۍ;
    ثابت حرف *title = SDL_GetStringProperty(props, SDL_PROP_کړکۍ_CREATE_TITLE_STRING, عدم);
    صحيح x = (صحيح)SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_X_شمېره, SDL_WINDOWPOS_UNDEFINED);
    صحيح y = (صحيح)SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_Y_شمېره, SDL_WINDOWPOS_UNDEFINED);
    صحيح w = (صحيح)SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_پلنوالی_شمېره, 0);
    صحيح h = (صحيح)SDL_Get_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_لوړوالی_شمېره, 0);
    SDL_کړکۍ *پلار = (SDL_کړکۍ *)SDL_Get_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_CREATE_پلار_اشاره_ګر, عدم);
    SDL_کړکۍ_Flags flags = SDL_Get_کړکۍ_Flag_Properties(props);
    SDL_کړکۍ_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_کړکۍ_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

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

    إذا ((flags & SDL_کړکۍ_MODAL) && !SDL_ObjectValid(پلار, SDL_OBJECT_TYPE_کړکۍ)) {
        SDL_سېټ_Error("Modal windows must specify a parent window");
        أرجع عدم;
    }

    إذا ((flags & (SDL_کړکۍ_TOOLTIP | SDL_کړکۍ_POPUP_MENU)) != 0) {
        إذا (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_کړکۍ_SUPPORT)) {
            SDL_Unsupported();
            أرجع عدم;
        }

        // Tooltip and popup menu window must specify a parent window
        إذا (!SDL_ObjectValid(پلار, SDL_OBJECT_TYPE_کړکۍ)) {
            SDL_سېټ_Error("Tooltip and popup menu windows must specify a parent window");
            أرجع عدم;
        }

        // Remove invalid flags
        flags &= ~(SDL_کړکۍ_MINIMIZED | SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_کړکۍ_UTILITY | SDL_کړکۍ_TOOLTIP | SDL_کړکۍ_POPUP_MENU | SDL_کړکۍ_MODAL);
    إذا (type_flags & (type_flags - 1)) {
        SDL_سېټ_Error("Conflicting window type flags specified: 0x%.8x", (بینښه صحيح)type_flags);
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
        إذا (displayID == 0 || SDL_Get_Display_شاخص(displayID) < 0) {
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
    graphics_flags = flags & (SDL_کړکۍ_OPENGL | SDL_کړکۍ_METAL | SDL_کړکۍ_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        SDL_سېټ_Error("Conflicting window graphics flags specified: 0x%.8x", (بینښه صحيح)graphics_flags);
        أرجع عدم;
    }

    // Some platforms have certain graphics backends enabled by default
    إذا (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    إذا (flags & SDL_کړکۍ_OPENGL) {
        إذا (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            أرجع عدم;
        }
        إذا (!SDL_GL_بارول_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_کړکۍ_VULKAN) {
        إذا (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            أرجع عدم;
        }
        إذا (!SDL_Vulkan_بارول_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_کړکۍ_METAL) {
        إذا (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            أرجع عدم;
        }
    }

    کړکۍ = (SDL_کړکۍ *)SDL_calloc(1, حجم(*کړکۍ));
    إذا (!کړکۍ) {
        أرجع عدم;
    }
    SDL_سېټ_Object_Valid(کړکۍ, SDL_OBJECT_TYPE_کړکۍ, true);
    کړکۍ->id = SDL_Get_بل_Object_ID();
    کړکۍ->floating.x = کړکۍ->windowed.x = کړکۍ->x = x;
    کړکۍ->floating.y = کړکۍ->windowed.y = کړکۍ->y = y;
    کړکۍ->floating.w = کړکۍ->windowed.w = کړکۍ->w = w;
    کړکۍ->floating.h = کړکۍ->windowed.h = کړکۍ->h = h;
    کړکۍ->undefined_x = undefined_x;
    کړکۍ->undefined_y = undefined_y;
    کړکۍ->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_کړکۍ(کړکۍ);
    إذا (display) {
        SDL_سېټ_کړکۍ_HDRProperties(کړکۍ, &display->HDR, false);
    }

    إذا (flags & SDL_کړکۍ_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        کړکۍ->x = bounds.x;
        کړکۍ->y = bounds.y;
        کړکۍ->w = bounds.w;
        کړکۍ->h = bounds.h;
        کړکۍ->pending_flags |= SDL_کړکۍ_FULLSCREEN;
        flags |= SDL_کړکۍ_FULLSCREEN;
    }

    کړکۍ->flags = ((flags & CREATE_FLAGS) | SDL_کړکۍ_HIDDEN);
    کړکۍ->display_scale = 1.0f;
    کړکۍ->opacity = 1.0f;
    کړکۍ->بل = _this->windows;
    کړکۍ->is_destroying = false;
    کړکۍ->displayID = Get_Display_For_کړکۍ(کړکۍ);
    کړکۍ->external_graphics_context = external_graphics_context;
    کړکۍ->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_کړکۍ_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    إذا (!_this->سېټ_کړکۍ_Fill_Document) {
        کړکۍ->flags &= ~SDL_کړکۍ_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    إذا (_this->windows) {
        _this->windows->prev = کړکۍ;
    }
    _this->windows = کړکۍ;

    // Set the parent before creation.
    SDL_Update_کړکۍ_Hierarchy(کړکۍ, پلار);

    إذا (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, کړکۍ, props)) {
        SDL_ټېل_Error();
        SDL_Destroy_کړکۍ(کړکۍ);
        SDL_راوباسه_Error();
        أرجع عدم;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#إذا !defined(SDL_PLATFORM_WINDOWS)
    إذا (کړکۍ->flags & SDL_کړکۍ_MINIMIZED) {
        کړکۍ->flags &= ~SDL_کړکۍ_MINIMIZED;
    }
#د_که_پای

    إذا (title) {
        SDL_سېټ_کړکۍ_Title(کړکۍ, title);
    }
    SDL_پای_کړکۍ_Creation(کړکۍ, flags);

    // Make sure window pixel size is up to date
    SDL_Check_کړکۍ_Pixel_اندازه_بدل_شوی(کړکۍ);

#که_تعریف_شوی SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#د_که_پای

    SDL_ClearError();

    أرجع کړکۍ;
}

SDL_کړکۍ *SDL_Create_کړکۍ(ثابت حرف *title, صحيح w, صحيح h, SDL_کړکۍ_Flags flags)
{
    SDL_کړکۍ *کړکۍ;
    SDL_PropertiesID props = SDL_CreateProperties();
    إذا (title && *title) {
        SDL_سېټ_String_Property(props, SDL_PROP_کړکۍ_CREATE_TITLE_STRING, title);
    }
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_پلنوالی_شمېره, w);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_لوړوالی_شمېره, h);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_FLAGS_شمېره, flags);
    کړکۍ = SDL_Create_کړکۍ_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع کړکۍ;
}

SDL_کړکۍ *SDL_Create_Popup_کړکۍ(SDL_کړکۍ *پلار, صحيح دننه_واټن_x, صحيح دننه_واټن_y, صحيح w, صحيح h, SDL_کړکۍ_Flags flags)
{
    SDL_کړکۍ *کړکۍ;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    إذا (!(flags & (SDL_کړکۍ_TOOLTIP | SDL_کړکۍ_POPUP_MENU))) {
        SDL_سېټ_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        أرجع عدم;
    }

    SDL_سېټ_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_CREATE_پلار_اشاره_ګر, پلار);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_X_شمېره, دننه_واټن_x);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_Y_شمېره, دننه_واټن_y);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_پلنوالی_شمېره, w);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_لوړوالی_شمېره, h);
    SDL_سېټ_شمېره_Property(props, SDL_PROP_کړکۍ_CREATE_FLAGS_شمېره, flags);
    کړکۍ = SDL_Create_کړکۍ_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع کړکۍ;
}

ساكن bool SDL_Reconfigure_کړکۍ_دننی(SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    إذا (!_this->Reconfigure_کړکۍ) {
        أرجع false;
    }

    ثابت SDL_کړکۍ_Flags graphics_flags = flags & (SDL_کړکۍ_OPENGL | SDL_کړکۍ_METAL | SDL_کړکۍ_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_سېټ_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_کړکۍ_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_کړکۍ_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_کړکۍ_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        إذا (کړکۍ->flags & (SDL_کړکۍ_OPENGL | SDL_کړکۍ_METAL | SDL_کړکۍ_VULKAN)) {
            أرجع false;
        }
    } وإلا {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        إذا (!_this->Reconfigure_کړکۍ(_this, کړکۍ, 0)) {
            أرجع false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        إذا (کړکۍ->flags & SDL_کړکۍ_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        کړکۍ->flags &= ~(SDL_کړکۍ_OPENGL | SDL_کړکۍ_METAL | SDL_کړکۍ_VULKAN);
    }

    SDL_Destroy_کړکۍ_Surface(کړکۍ);

    إذا (graphics_flags & SDL_کړکۍ_OPENGL) {
        loaded_opengl = SDL_GL_بارول_Library(عدم);
        إذا (!loaded_opengl) {
            أرجع false;
        }
    } وإلا إذا (graphics_flags & SDL_کړکۍ_VULKAN) {
        loaded_vulkan = SDL_Vulkan_بارول_Library(عدم);
        إذا (!loaded_vulkan) {
            أرجع false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    إذا (!_this->Reconfigure_کړکۍ(_this, کړکۍ, graphics_flags)) {
        إذا (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        إذا (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        أرجع false;
    }

    کړکۍ->flags |= graphics_flags;

    أرجع true;
}

bool SDL_Recreate_کړکۍ(SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_بارول = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_بارول = false;
    SDL_کړکۍ_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_کړکۍ_OPENGL | SDL_کړکۍ_METAL | SDL_کړکۍ_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_سېټ_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_کړکۍ_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_کړکۍ_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_کړکۍ_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_کړکۍ_EXTERNAL;
    } وإلا {
        flags &= ~SDL_کړکۍ_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    إذا (کړکۍ->flags & SDL_کړکۍ_MODAL) {
        SDL_سېټ_کړکۍ_Modal(کړکۍ, false);
    }

    // Restore video mode, etc.
    إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL)) {
        ثابت bool restore_on_show = کړکۍ->restore_on_show;
        SDL_Hide_کړکۍ(کړکۍ);
        کړکۍ->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_کړکۍ_Surface(کړکۍ);

    إذا ((کړکۍ->flags & SDL_کړکۍ_OPENGL) != (flags & SDL_کړکۍ_OPENGL)) {
        إذا (flags & SDL_کړکۍ_OPENGL) {
            need_gl_بارول = true;
        } وإلا {
            need_gl_unload = true;
        }
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        need_gl_unload = true;
        need_gl_بارول = true;
    }

    إذا ((کړکۍ->flags & SDL_کړکۍ_VULKAN) != (flags & SDL_کړکۍ_VULKAN)) {
        إذا (flags & SDL_کړکۍ_VULKAN) {
            need_vulkan_بارول = true;
        } وإلا {
            need_vulkan_unload = true;
        }
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_بارول = true;
    }

    إذا (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    إذا (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->Destroy_کړکۍ && !(flags & SDL_کړکۍ_EXTERNAL)) {
        _this->Destroy_کړکۍ(_this, کړکۍ);
    }

    إذا (need_gl_بارول) {
        إذا (!SDL_GL_بارول_Library(عدم)) {
            أرجع false;
        }
        loaded_opengl = true;
    }

    إذا (need_vulkan_بارول) {
        إذا (!SDL_Vulkan_بارول_Library(عدم)) {
            أرجع false;
        }
        loaded_vulkan = true;
    }

    کړکۍ->flags = ((flags & CREATE_FLAGS) | SDL_کړکۍ_HIDDEN);
    کړکۍ->is_destroying = false;

    إذا (_this->CreateSDLWindow && !(flags & SDL_کړکۍ_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        کړکۍ->x = کړکۍ->windowed.x = کړکۍ->floating.x;
        کړکۍ->y = کړکۍ->windowed.y = کړکۍ->floating.y;
        کړکۍ->w = کړکۍ->windowed.w = کړکۍ->floating.w;
        کړکۍ->h = کړکۍ->windowed.h = کړکۍ->floating.h;

        إذا (!_this->CreateSDLWindow(_this, کړکۍ, 0)) {
            إذا (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                کړکۍ->flags &= ~SDL_کړکۍ_OPENGL;
            }
            إذا (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                کړکۍ->flags &= ~SDL_کړکۍ_VULKAN;
            }
            أرجع false;
        }
    }

    إذا (flags & SDL_کړکۍ_EXTERNAL) {
        کړکۍ->flags |= SDL_کړکۍ_EXTERNAL;
    }

    إذا (_this->سېټ_کړکۍ_Title && کړکۍ->title) {
        _this->سېټ_کړکۍ_Title(_this, کړکۍ);
    }

    إذا (_this->سېټ_کړکۍ_Icon && کړکۍ->icon) {
        _this->سېټ_کړکۍ_Icon(_this, کړکۍ, کړکۍ->icon);
    }

    إذا (_this->سېټ_کړکۍ_Minimum_اندازه && (کړکۍ->min_w || کړکۍ->min_h)) {
        _this->سېټ_کړکۍ_Minimum_اندازه(_this, کړکۍ);
    }

    إذا (_this->سېټ_کړکۍ_اعظمي_اندازه && (کړکۍ->max_w || کړکۍ->max_h)) {
        _this->سېټ_کړکۍ_اعظمي_اندازه(_this, کړکۍ);
    }

    إذا (_this->سېټ_کړکۍ_Aspect_نسبت && (کړکۍ->min_aspect > 0.0f || کړکۍ->max_aspect > 0.0f)) {
        _this->سېټ_کړکۍ_Aspect_نسبت(_this, کړکۍ);
    }

    إذا (کړکۍ->موندنه_test) {
        _this->سېټ_کړکۍ_موندنه_Test(کړکۍ, true);
    }

    SDL_پای_کړکۍ_Creation(کړکۍ, flags);

    أرجع true;
}

bool SDL_Reconfigure_کړکۍ(SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    إذا (!SDL_Reconfigure_کړکۍ_دننی(کړکۍ, flags)) {
        أرجع SDL_Recreate_کړکۍ(کړکۍ, flags);
    }

    أرجع true;
}

bool SDL_HasWindows(فراغ)
{
    أرجع _this && _this->windows;
}

SDL_کړکۍ_ID SDL_Get_کړکۍ_ID(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, 0);

    أرجع کړکۍ->id;
}

SDL_کړکۍ *SDL_Get_کړکۍ_From_ID(SDL_کړکۍ_ID id)
{
    SDL_کړکۍ *کړکۍ;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (id) {
        لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
            إذا (کړکۍ->id == id) {
                أرجع کړکۍ;
            }
        }
    }
    SDL_سېټ_Error("Invalid window ID");
    أرجع عدم;
}

SDL_کړکۍ *SDL_Get_کړکۍ_پلار(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, عدم);

    أرجع کړکۍ->پلار;
}

SDL_PropertiesID SDL_Get_کړکۍ_Properties(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, 0);

    إذا (کړکۍ->props == 0) {
        کړکۍ->props = SDL_CreateProperties();
    }
    أرجع کړکۍ->props;
}

SDL_کړکۍ_Flags SDL_Get_کړکۍ_Flags(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, 0);

    أرجع کړکۍ->flags | کړکۍ->pending_flags;
}

bool SDL_سېټ_کړکۍ_Title(SDL_کړکۍ *کړکۍ, ثابت حرف *title)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (title == کړکۍ->title) {
        أرجع true;
    }
    إذا (!title) {
        title = "";
    }
    إذا (کړکۍ->title && SDL_strcmp(title, کړکۍ->title) == 0) {
        أرجع true;
    }

    SDL_free(کړکۍ->title);

    کړکۍ->title = SDL_strdup(title);

    إذا (_this->سېټ_کړکۍ_Title) {
        _this->سېټ_کړکۍ_Title(_this, کړکۍ);
    }
    أرجع true;
}

ثابت حرف *SDL_Get_کړکۍ_Title(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, "");

    أرجع کړکۍ->title ? کړکۍ->title : "";
}

bool SDL_سېټ_کړکۍ_Icon(SDL_کړکۍ *کړکۍ, SDL_Surface *icon)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    CHECK_PARAM(!icon) {
        أرجع SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(کړکۍ->icon);

    // Convert the icon into ARGB8888
    کړکۍ->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    إذا (!کړکۍ->icon) {
        أرجع false;
    }

    إذا (!_this->سېټ_کړکۍ_Icon) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->سېټ_کړکۍ_Icon(_this, کړکۍ, کړکۍ->icon);
}

bool SDL_سېټ_کړکۍ_Position(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y)
{
    SDL_DisplayID original_displayID;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    ثابت صحيح w = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : کړکۍ->windowed.w;
    ثابت صحيح h = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : کړکۍ->windowed.h;

    original_displayID = Get_Display_For_کړکۍ(کړکۍ);
    کړکۍ->pending_displayID = 0;

    إذا (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = کړکۍ->windowed.x;
    }
    إذا (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = کړکۍ->windowed.y;
    }
    إذا (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        إذا (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } وإلا إذا (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        إذا (displayID == 0 || SDL_Get_Display_شاخص(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        کړکۍ->pending_displayID = displayID;

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
        کړکۍ->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    کړکۍ->pending.x = x;
    کړکۍ->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    إذا (!_this->Sync_کړکۍ && (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        کړکۍ->floating.x = کړکۍ->windowed.x = x;
        کړکۍ->floating.y = کړکۍ->windowed.y = y;
    }
    کړکۍ->undefined_x = false;
    کړکۍ->undefined_y = false;
    کړکۍ->وروستی_position_pending = true;

    إذا (_this->سېټ_کړکۍ_Position) {
        ثابت bool پایله = _this->سېټ_کړکۍ_Position(_this, کړکۍ);
        إذا (پایله) {
            SDL_SyncIfRequired(کړکۍ);
        }
        أرجع پایله;
    }

    أرجع SDL_Unsupported();
}

bool SDL_Get_کړکۍ_Position(SDL_کړکۍ *کړکۍ, صحيح *x, صحيح *y)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

#که_تعریف_شوی SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#وإلا
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) != 0);
#د_که_پای
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
        displayID = Get_Display_For_کړکۍ(کړکۍ);
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
        ثابت bool use_pending = (کړکۍ->flags & SDL_کړکۍ_HIDDEN) && کړکۍ->وروستی_position_pending;
        إذا (x) {
            *x = use_pending ? کړکۍ->pending.x : کړکۍ->x;
        }
        إذا (y) {
            *y = use_pending ? کړکۍ->pending.y : کړکۍ->y;
        }
    }
    أرجع true;
}

bool SDL_سېټ_کړکۍ_Bordered(SDL_کړکۍ *کړکۍ, bool bordered)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_Bordered) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(کړکۍ->flags & SDL_کړکۍ_BORDERLESS);
    إذا (want != have) {
        إذا (want) {
            کړکۍ->flags &= ~SDL_کړکۍ_BORDERLESS;
        } وإلا {
            کړکۍ->flags |= SDL_کړکۍ_BORDERLESS;
        }
        _this->سېټ_کړکۍ_Bordered(_this, کړکۍ, want);
    }

    أرجع true;
}

bool SDL_سېټ_کړکۍ_Resizable(SDL_کړکۍ *کړکۍ, bool resizable)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_Resizable) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((کړکۍ->flags & SDL_کړکۍ_RESIZABLE) != 0);
    إذا (want != have) {
        إذا (want) {
            کړکۍ->flags |= SDL_کړکۍ_RESIZABLE;
        } وإلا {
            کړکۍ->flags &= ~SDL_کړکۍ_RESIZABLE;
            SDL_copyp(&کړکۍ->windowed, &کړکۍ->floating);
        }
        _this->سېټ_کړکۍ_Resizable(_this, کړکۍ, want);
    }

    أرجع true;
}

bool SDL_سېټ_کړکۍ_Always_On_سر(SDL_کړکۍ *کړکۍ, bool on_سر)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_Always_On_سر) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = on_سر;
    ثابت bool have = ((کړکۍ->flags & SDL_کړکۍ_ALWAYS_ON_سر) != 0);
    إذا (want != have) {
        إذا (want) {
            کړکۍ->flags |= SDL_کړکۍ_ALWAYS_ON_سر;
        } وإلا {
            کړکۍ->flags &= ~SDL_کړکۍ_ALWAYS_ON_سر;
        }
        _this->سېټ_کړکۍ_Always_On_سر(_this, کړکۍ, want);
    }

    أرجع true;
}

bool SDL_سېټ_کړکۍ_اندازه(SDL_کړکۍ *کړکۍ, صحيح w, صحيح h)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

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
    إذا (کړکۍ->max_aspect > 0.0f && new_aspect > کړکۍ->max_aspect) {
        w = (صحيح)SDL_roundf(h * کړکۍ->max_aspect);
    } وإلا إذا (کړکۍ->min_aspect > 0.0f && new_aspect < کړکۍ->min_aspect) {
        h = (صحيح)SDL_roundf(w / کړکۍ->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    إذا (کړکۍ->min_w && w < کړکۍ->min_w) {
        w = کړکۍ->min_w;
    }
    إذا (کړکۍ->max_w && w > کړکۍ->max_w) {
        w = کړکۍ->max_w;
    }
    إذا (کړکۍ->min_h && h < کړکۍ->min_h) {
        h = کړکۍ->min_h;
    }
    إذا (کړکۍ->max_h && h > کړکۍ->max_h) {
        h = کړکۍ->max_h;
    }

    کړکۍ->وروستی_اندازه_pending = true;
    کړکۍ->pending.w = w;
    کړکۍ->pending.h = h;

    إذا (_this->سېټ_کړکۍ_اندازه) {
        _this->سېټ_کړکۍ_اندازه(_this, کړکۍ);
        SDL_SyncIfRequired(کړکۍ);
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

bool SDL_Get_کړکۍ_اندازه(SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    إذا (w) {
        *w = کړکۍ->w;
    }
    إذا (h) {
        *h = کړکۍ->h;
    }
    أرجع true;
}

bool SDL_سېټ_کړکۍ_Aspect_نسبت(SDL_کړکۍ *کړکۍ, عائم min_aspect, عائم max_aspect)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    کړکۍ->min_aspect = min_aspect;
    کړکۍ->max_aspect = max_aspect;

    إذا (_this->سېټ_کړکۍ_Aspect_نسبت) {
        _this->سېټ_کړکۍ_Aspect_نسبت(_this, کړکۍ);
    }

    // Ensure that window has the correct aspect ratio
    صحيح w = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : کړکۍ->floating.w;
    صحيح h = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : کړکۍ->floating.h;
    أرجع SDL_سېټ_کړکۍ_اندازه(کړکۍ, w, h);
}

bool SDL_Get_کړکۍ_Aspect_نسبت(SDL_کړکۍ *کړکۍ, عائم *min_aspect, عائم *max_aspect)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (min_aspect) {
        *min_aspect = کړکۍ->min_aspect;
    }
    إذا (max_aspect) {
        *max_aspect = کړکۍ->max_aspect;
    }
    أرجع true;
}

bool SDL_Get_کړکۍ_Borders_اندازه(SDL_کړکۍ *کړکۍ, صحيح *سر, صحيح *کیڼ, صحيح *bottom, صحيح *ښی)
{
    صحيح dummy = 0;

    إذا (!سر) {
        سر = &dummy;
    }
    إذا (!کیڼ) {
        کیڼ = &dummy;
    }
    إذا (!ښی) {
        ښی = &dummy;
    }
    إذا (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *سر = *کیڼ = *bottom = *ښی = 0;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!_this->Get_کړکۍ_Borders_اندازه) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->Get_کړکۍ_Borders_اندازه(_this, کړکۍ, سر, کیڼ, bottom, ښی);
}

bool SDL_Get_کړکۍ_اندازه_دننه_Pixels(SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h)
{
    صحيح filter;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!w) {
        w = &filter;
    }

    إذا (!h) {
        h = &filter;
    }

    إذا (_this->Get_کړکۍ_اندازه_دننه_Pixels) {
        _this->Get_کړکۍ_اندازه_دننه_Pixels(_this, کړکۍ, w, h);
    } وإلا {
        SDL_DisplayID displayID = Get_Display_For_کړکۍ(کړکۍ);
        ثابت SDL_Display_ډېرپېښ *ډېرپېښ;

        SDL_Get_کړکۍ_اندازه(کړکۍ, w, h);

        إذا ((کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) && SDL_Get_کړکۍ_Fullscreen_ډېرپېښ(کړکۍ)) {
            ډېرپېښ = SDL_Get_Current_Display_ډېرپېښ(displayID);
        } وإلا {
            ډېرپېښ = SDL_Get_Desktop_Display_ډېرپېښ(displayID);
        }
        إذا (ډېرپېښ) {
            *w = (صحيح)SDL_ceilf(*w * ډېرپېښ->pixel_density);
            *h = (صحيح)SDL_ceilf(*h * ډېرپېښ->pixel_density);
        }
    }
    أرجع true;
}

bool SDL_سېټ_کړکۍ_Minimum_اندازه(SDL_کړکۍ *کړکۍ, صحيح min_w, صحيح min_h)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_PARAM(min_w < 0) {
        أرجع SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        أرجع SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((کړکۍ->max_w && min_w > کړکۍ->max_w) || (کړکۍ->max_h && min_h > کړکۍ->max_h)) {
        أرجع SDL_سېټ_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    کړکۍ->min_w = min_w;
    کړکۍ->min_h = min_h;

    إذا (_this->سېټ_کړکۍ_Minimum_اندازه) {
        _this->سېټ_کړکۍ_Minimum_اندازه(_this, کړکۍ);
    }

    // Ensure that window is not smaller than minimal size
    صحيح w = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : کړکۍ->floating.w;
    صحيح h = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : کړکۍ->floating.h;
    أرجع SDL_سېټ_کړکۍ_اندازه(کړکۍ, w, h);
}

bool SDL_Get_کړکۍ_Minimum_اندازه(SDL_کړکۍ *کړکۍ, صحيح *min_w, صحيح *min_h)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    إذا (min_w) {
        *min_w = کړکۍ->min_w;
    }
    إذا (min_h) {
        *min_h = کړکۍ->min_h;
    }
    أرجع true;
}

bool SDL_سېټ_کړکۍ_اعظمي_اندازه(SDL_کړکۍ *کړکۍ, صحيح max_w, صحيح max_h)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_PARAM(max_w < 0) {
        أرجع SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        أرجع SDL_InvalidParamError("max_h");
    }

    إذا ((max_w && max_w < کړکۍ->min_w) ||
        (max_h && max_h < کړکۍ->min_h)) {
        أرجع SDL_سېټ_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    کړکۍ->max_w = max_w;
    کړکۍ->max_h = max_h;

    إذا (_this->سېټ_کړکۍ_اعظمي_اندازه) {
        _this->سېټ_کړکۍ_اعظمي_اندازه(_this, کړکۍ);
    }

    // Ensure that window is not larger than maximal size
    صحيح w = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.w : کړکۍ->floating.w;
    صحيح h = کړکۍ->وروستی_اندازه_pending ? کړکۍ->pending.h : کړکۍ->floating.h;
    أرجع SDL_سېټ_کړکۍ_اندازه(کړکۍ, w, h);
}

bool SDL_Get_کړکۍ_اعظمي_اندازه(SDL_کړکۍ *کړکۍ, صحيح *max_w, صحيح *max_h)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    إذا (max_w) {
        *max_w = کړکۍ->max_w;
    }
    إذا (max_h) {
        *max_h = کړکۍ->max_h;
    }
    أرجع true;
}

bool SDL_Show_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ *ماشوم;
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!(کړکۍ->flags & SDL_کړکۍ_HIDDEN)) {
        أرجع true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    إذا (کړکۍ->پلار && (کړکۍ->پلار->flags & SDL_کړکۍ_HIDDEN)) {
        کړکۍ->restore_on_show = true;
        أرجع true;
    }

    إذا (_this->Show_کړکۍ) {
        _this->Show_کړکۍ(_this, کړکۍ);
    } وإلا {
        SDL_سېټ_Mouse_Focus(کړکۍ);
        SDL_سېټ_Keyboard_Focus(کړکۍ);
    }
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_SHOWN, 0, 0);

    // Restore child windows
    لكل (ماشوم = کړکۍ->لومړی_ماشوم; ماشوم; ماشوم = ماشوم->بل_sibling) {
        إذا (!ماشوم->restore_on_show && (ماشوم->flags & SDL_کړکۍ_HIDDEN)) {
            اكسر;
        }
        SDL_Show_کړکۍ(ماشوم);
        ماشوم->restore_on_show = false;
    }
    أرجع true;
}

bool SDL_Hide_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ *ماشوم;
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        کړکۍ->restore_on_show = false;
        أرجع true;
    }

    // Hide all child windows
    لكل (ماشوم = کړکۍ->لومړی_ماشوم; ماشوم; ماشوم = ماشوم->بل_sibling) {
        إذا (ماشوم->flags & SDL_کړکۍ_HIDDEN) {
            اكسر;
        }
        SDL_Hide_کړکۍ(ماشوم);
        ماشوم->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_کړکۍ_Flags pending_ماسک = (SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_MINIMIZED | SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_KEYBOARD_GRABBED | SDL_کړکۍ_MOUSE_GRABBED);
    کړکۍ->pending_flags = (کړکۍ->flags & pending_ماسک);

    کړکۍ->is_hiding = true;
    إذا (_this->Hide_کړکۍ) {
        _this->Hide_کړکۍ(_this, کړکۍ);
    } وإلا {
        SDL_سېټ_Mouse_Focus(عدم);
        SDL_سېټ_Keyboard_Focus(عدم);
    }
    کړکۍ->is_hiding = false;
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_HIDDEN, 0, 0);
    أرجع true;
}

bool SDL_Raise_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        أرجع true;
    }
    إذا (_this->Raise_کړکۍ) {
        _this->Raise_کړکۍ(_this, کړکۍ);
    }
    أرجع true;
}

bool SDL_Maximize_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (!_this->Maximize_کړکۍ) {
        أرجع SDL_Unsupported();
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_RESIZABLE)) {
        أرجع SDL_سېټ_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        کړکۍ->pending_flags |= SDL_کړکۍ_MAXIMIZED;
        أرجع true;
    }

    _this->Maximize_کړکۍ(_this, کړکۍ);
    SDL_SyncIfRequired(کړکۍ);
    أرجع true;
}

bool SDL_Minimize_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (!_this->Minimize_کړکۍ) {
        أرجع SDL_Unsupported();
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        کړکۍ->pending_flags |= SDL_کړکۍ_MINIMIZED;
        أرجع true;
    }

    _this->Minimize_کړکۍ(_this, کړکۍ);
    SDL_SyncIfRequired(کړکۍ);
    أرجع true;
}

bool SDL_Restore_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (!_this->Restore_کړکۍ) {
        أرجع SDL_Unsupported();
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        کړکۍ->pending_flags &= ~(SDL_کړکۍ_MAXIMIZED | SDL_کړکۍ_MINIMIZED);
        أرجع true;
    }

    _this->Restore_کړکۍ(_this, کړکۍ);
    SDL_SyncIfRequired(کړکۍ);
    أرجع true;
}

bool SDL_سېټ_کړکۍ_Fullscreen(SDL_کړکۍ *کړکۍ, bool fullscreen)
{
    bool پایله;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        إذا (fullscreen) {
            کړکۍ->pending_flags |= SDL_کړکۍ_FULLSCREEN;
        } وإلا {
            کړکۍ->pending_flags &= ~SDL_کړکۍ_FULLSCREEN;
        }
        أرجع true;
    }

    إذا (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&کړکۍ->current_fullscreen_ډېرپېښ, &کړکۍ->requested_fullscreen_ډېرپېښ);
    }

    پایله = SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    إذا (!fullscreen || !پایله) {
        // Clear the current fullscreen mode.
        SDL_zero(کړکۍ->current_fullscreen_ډېرپېښ);
    }

    إذا (پایله) {
        SDL_SyncIfRequired(کړکۍ);
    }

    أرجع پایله;
}

bool SDL_Sync_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (_this->Sync_کړکۍ) {
        أرجع _this->Sync_کړکۍ(_this, کړکۍ);
    } وإلا {
        أرجع true;
    }
}

ساكن bool ShouldAttemptTextureFramebuffer(فراغ)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    إذا (!_this->Create_کړکۍ_Framebuffer) {
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

ساكن SDL_Surface *SDL_Create_کړکۍ_Framebuffer(SDL_کړکۍ *کړکۍ)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    فراغ *pixels = عدم;
    صحيح pitch = 0;
    bool created_framebuffer = false;
    صحيح w, h;

    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    إذا (!_this->checked_texture_framebuffer) {
        إذا (ShouldAttemptTextureFramebuffer()) {
            إذا (!SDL_Create_کړکۍ_Texture(_this, کړکۍ, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } وإلا {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_کړکۍ_Framebuffer = SDL_Create_کړکۍ_Texture;
                _this->سېټ_کړکۍ_Framebuffer_VSync = SDL_سېټ_کړکۍ_Texture_VSync;
                _this->Get_کړکۍ_Framebuffer_VSync = SDL_Get_کړکۍ_Texture_VSync;
                _this->Update_کړکۍ_Framebuffer = SDL_Update_کړکۍ_Texture;
                _this->Destroy_کړکۍ_Framebuffer = SDL_Destroy_کړکۍ_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    إذا (!created_framebuffer) {
        إذا (!_this->Create_کړکۍ_Framebuffer || !_this->Update_کړکۍ_Framebuffer) {
            SDL_سېټ_Error("Window framebuffer support not available");
            أرجع عدم;
        }

        إذا (!_this->Create_کړکۍ_Framebuffer(_this, کړکۍ, &format, &pixels, &pitch)) {
            أرجع عدم;
        }
    }

    إذا (کړکۍ->surface) {
        // We may have gone recursive and already created the surface
        أرجع کړکۍ->surface;
    }

    أرجع SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_کړکۍ_Has_Surface(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    أرجع کړکۍ->surface ? true : false;
}

SDL_Surface *SDL_Get_کړکۍ_Surface(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, عدم);

    إذا (!کړکۍ->surface_valid) {
        إذا (کړکۍ->surface) {
            کړکۍ->surface->دننی_flags &= ~SDL_دننی_SURFACE_DONTFREE;
            SDL_DestroySurface(کړکۍ->surface);
            کړکۍ->surface = عدم;
        }

        کړکۍ->surface = SDL_Create_کړکۍ_Framebuffer(کړکۍ);
        إذا (کړکۍ->surface) {
            کړکۍ->surface_valid = true;
            کړکۍ->surface->دننی_flags |= SDL_دننی_SURFACE_DONTFREE;
        }
    }
    أرجع کړکۍ->surface;
}

bool SDL_سېټ_کړکۍ_Surface_VSync(SDL_کړکۍ *کړکۍ, صحيح vsync)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->سېټ_کړکۍ_Framebuffer_VSync(_this, کړکۍ, vsync);
}

bool SDL_Get_کړکۍ_Surface_VSync(SDL_کړکۍ *کړکۍ, صحيح *vsync)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!_this->Get_کړکۍ_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->Get_کړکۍ_Framebuffer_VSync(_this, کړکۍ, vsync);
}

bool SDL_Update_کړکۍ_Surface(SDL_کړکۍ *کړکۍ)
{
    SDL_Rect ډک_rect;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    ډک_rect.x = 0;
    ډک_rect.y = 0;
    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &ډک_rect.w, &ډک_rect.h);

    أرجع SDL_Update_کړکۍ_Surface_Rects(کړکۍ, &ډک_rect, 1);
}

bool SDL_Update_کړکۍ_Surface_Rects(SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rects,
                                 صحيح numrects)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!کړکۍ->surface_valid) {
        أرجع SDL_سېټ_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    أرجع _this->Update_کړکۍ_Framebuffer(_this, کړکۍ, rects, numrects);
}

bool SDL_Destroy_کړکۍ_Surface(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (کړکۍ->surface) {
        کړکۍ->surface->دننی_flags &= ~SDL_دننی_SURFACE_DONTFREE;
        SDL_DestroySurface(کړکۍ->surface);
        کړکۍ->surface = عدم;
        کړکۍ->surface_valid = false;
    }

    إذا (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        إذا (_this->Destroy_کړکۍ_Framebuffer) {
            _this->Destroy_کړکۍ_Framebuffer(_this, کړکۍ);
        }
    }
    أرجع true;
}

bool SDL_سېټ_کړکۍ_Opacity(SDL_کړکۍ *کړکۍ, عائم opacity)
{
    bool پایله;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_Opacity) {
        أرجع SDL_Unsupported();
    }

    إذا (opacity < 0.0f) {
        opacity = 0.0f;
    } وإلا إذا (opacity > 1.0f) {
        opacity = 1.0f;
    }

    پایله = _this->سېټ_کړکۍ_Opacity(_this, کړکۍ, opacity);
    إذا (پایله) {
        کړکۍ->opacity = opacity;
    }

    أرجع پایله;
}

عائم SDL_Get_کړکۍ_Opacity(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, -1.0f);

    أرجع کړکۍ->opacity;
}

bool SDL_سېټ_کړکۍ_پلار(SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (پلار) {
        CHECK_کړکۍ_MAGIC(پلار, false);
        CHECK_کړکۍ_NOT_POPUP(پلار, false);
    }

    إذا (کړکۍ == پلار) {
        أرجع SDL_سېټ_Error("Cannot set the parent of a window to itself.");
    }

    إذا (!_this->سېټ_کړکۍ_پلار) {
        أرجع SDL_Unsupported();
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_MODAL) {
        أرجع SDL_سېټ_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    إذا (کړکۍ->پلار == پلار) {
        أرجع true;
    }

    ثابت bool ret = _this->سېټ_کړکۍ_پلار(_this, کړکۍ, پلار);
    SDL_Update_کړکۍ_Hierarchy(کړکۍ, ret ? پلار : عدم);

    أرجع ret;
}

bool SDL_سېټ_کړکۍ_Modal(SDL_کړکۍ *کړکۍ, bool modal)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_Modal) {
        أرجع SDL_Unsupported();
    }

    إذا (modal) {
        إذا (!کړکۍ->پلار) {
            أرجع SDL_سېټ_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        کړکۍ->flags |= SDL_کړکۍ_MODAL;
    } وإلا إذا (کړکۍ->flags & SDL_کړکۍ_MODAL) {
        کړکۍ->flags &= ~SDL_کړکۍ_MODAL;
    } وإلا {
        أرجع true; // Already not modal, so nothing to do.
    }

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        أرجع true;
    }

    أرجع _this->سېټ_کړکۍ_Modal(_this, کړکۍ, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_کړکۍ *کړکۍ, SDL_کړکۍ **new_focus)
{
    SDL_کړکۍ *focus = کړکۍ->پلار;
    bool سېټ_focus = !!(کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    طالما (SDL_کړکۍ_IS_POPUP(focus) && ((focus->flags & SDL_کړکۍ_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->پلار;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        إذا (!سېټ_focus) {
            سېټ_focus = !!(focus->flags & SDL_کړکۍ_ننوت_FOCUS);
        }
    }

    *new_focus = focus;
    أرجع سېټ_focus;
}

bool SDL_ShouldFocusPopup(SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ *toplevel_پلار;
    لكل (toplevel_پلار = کړکۍ->پلار; SDL_کړکۍ_IS_POPUP(toplevel_پلار); toplevel_پلار = toplevel_پلار->پلار) {
    }

    SDL_کړکۍ *current_focus = toplevel_پلار->keyboard_focus;
    bool وموندل_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_کړکۍ *w;
    لكل (w = current_focus; w != toplevel_پلار; w = w->پلار) {
        إذا (w == کړکۍ) {
            وموندل_higher_focus = true;
            اكسر;
        }
    }

    أرجع !وموندل_higher_focus || w == toplevel_پلار;
}

bool SDL_سېټ_کړکۍ_Focusable(SDL_کړکۍ *کړکۍ, bool focusable)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(کړکۍ->flags & SDL_کړکۍ_NOT_FOCUSABLE);
    إذا ((want != have) && (_this->سېټ_کړکۍ_Focusable)) {
        إذا (want) {
            کړکۍ->flags &= ~SDL_کړکۍ_NOT_FOCUSABLE;
        } وإلا {
            کړکۍ->flags |= SDL_کړکۍ_NOT_FOCUSABLE;
        }
        إذا (!_this->سېټ_کړکۍ_Focusable(_this, کړکۍ, want)) {
            أرجع false;
        }
    }

    أرجع true;
}

bool SDL_سېټ_کړکۍ_Fill_Document(SDL_کړکۍ *کړکۍ, bool fill)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((کړکۍ->flags & SDL_کړکۍ_FILL_DOCUMENT) != 0);
    إذا ((want != have) && (_this->سېټ_کړکۍ_Fill_Document)) {
        إذا (!_this->سېټ_کړکۍ_Fill_Document(_this, کړکۍ, want)) {
            أرجع false;
        } وإلا إذا (want) {
            کړکۍ->flags |= SDL_کړکۍ_FILL_DOCUMENT;
        } وإلا {
            کړکۍ->flags &= ~SDL_کړکۍ_FILL_DOCUMENT;
        }
    }

    أرجع true;
}

فراغ SDL_Update_کړکۍ_Grab(SDL_کړکۍ *کړکۍ)
{
    bool keyboard_grabbed, mouse_grabbed;

    إذا (کړکۍ->flags & SDL_کړکۍ_ننوت_FOCUS) {
        إذا (SDL_GetMouse()->relative_ډېرپېښ || (کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } وإلا {
            mouse_grabbed = false;
        }

        إذا (کړکۍ->flags & SDL_کړکۍ_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } وإلا {
            keyboard_grabbed = false;
        }
    } وإلا {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    إذا (mouse_grabbed || keyboard_grabbed) {
        إذا (_this->grabbed_کړکۍ && (_this->grabbed_کړکۍ != کړکۍ)) {
            // stealing a grab from another window!
            _this->grabbed_کړکۍ->flags &= ~(SDL_کړکۍ_MOUSE_GRABBED | SDL_کړکۍ_KEYBOARD_GRABBED);
            إذا (_this->سېټ_کړکۍ_Mouse_Grab) {
                _this->سېټ_کړکۍ_Mouse_Grab(_this, _this->grabbed_کړکۍ, false);
            }
            إذا (_this->سېټ_کړکۍ_Keyboard_Grab) {
                _this->سېټ_کړکۍ_Keyboard_Grab(_this, _this->grabbed_کړکۍ, false);
            }
        }
        _this->grabbed_کړکۍ = کړکۍ;
    } وإلا إذا (_this->grabbed_کړکۍ == کړکۍ) {
        _this->grabbed_کړکۍ = عدم; // ungrabbing input.
    }

    إذا (_this->سېټ_کړکۍ_Mouse_Grab) {
        إذا (!_this->سېټ_کړکۍ_Mouse_Grab(_this, کړکۍ, mouse_grabbed)) {
            کړکۍ->flags &= ~SDL_کړکۍ_MOUSE_GRABBED;
        }
    }
    إذا (_this->سېټ_کړکۍ_Keyboard_Grab) {
        إذا (!_this->سېټ_کړکۍ_Keyboard_Grab(_this, کړکۍ, keyboard_grabbed)) {
            کړکۍ->flags &= ~SDL_کړکۍ_KEYBOARD_GRABBED;
        }
    }

    إذا (_this->grabbed_کړکۍ && !(_this->grabbed_کړکۍ->flags & (SDL_کړکۍ_MOUSE_GRABBED | SDL_کړکۍ_KEYBOARD_GRABBED))) {
        _this->grabbed_کړکۍ = عدم;
    }
}

bool SDL_سېټ_کړکۍ_Keyboard_Grab(SDL_کړکۍ *کړکۍ, bool grabbed)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        إذا (grabbed) {
            کړکۍ->pending_flags |= SDL_کړکۍ_KEYBOARD_GRABBED;
        } وإلا {
            کړکۍ->pending_flags &= ~SDL_کړکۍ_KEYBOARD_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(کړکۍ->flags & SDL_کړکۍ_KEYBOARD_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        کړکۍ->flags |= SDL_کړکۍ_KEYBOARD_GRABBED;
    } وإلا {
        کړکۍ->flags &= ~SDL_کړکۍ_KEYBOARD_GRABBED;
    }
    SDL_Update_کړکۍ_Grab(کړکۍ);

    إذا (grabbed && !(کړکۍ->flags & SDL_کړکۍ_KEYBOARD_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_سېټ_کړکۍ_Mouse_Grab(SDL_کړکۍ *کړکۍ, bool grabbed)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        إذا (grabbed) {
            کړکۍ->pending_flags |= SDL_کړکۍ_MOUSE_GRABBED;
        } وإلا {
            کړکۍ->pending_flags &= ~SDL_کړکۍ_MOUSE_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        کړکۍ->flags |= SDL_کړکۍ_MOUSE_GRABBED;
    } وإلا {
        کړکۍ->flags &= ~SDL_کړکۍ_MOUSE_GRABBED;
    }
    SDL_Update_کړکۍ_Grab(کړکۍ);

    إذا (grabbed && !(کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_کړکۍ_Keyboard_Grab(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    أرجع کړکۍ == _this->grabbed_کړکۍ && (_this->grabbed_کړکۍ->flags & SDL_کړکۍ_KEYBOARD_GRABBED);
}

bool SDL_Get_کړکۍ_Mouse_Grab(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    أرجع کړکۍ == _this->grabbed_کړکۍ && (_this->grabbed_کړکۍ->flags & SDL_کړکۍ_MOUSE_GRABBED);
}

SDL_کړکۍ *SDL_Get_Grabbed_کړکۍ(فراغ)
{
    إذا (_this && _this->grabbed_کړکۍ &&
        (_this->grabbed_کړکۍ->flags & (SDL_کړکۍ_MOUSE_GRABBED | SDL_کړکۍ_KEYBOARD_GRABBED)) != 0) {
        أرجع _this->grabbed_کړکۍ;
    } وإلا {
        أرجع عدم;
    }
}

bool SDL_سېټ_کړکۍ_Mouse_Rect(SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rect)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_Mouse_Rect) {
        أرجع SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    إذا (!rect) {
        rect = &zero;
    }

    إذا (SDL_memcmp(&کړکۍ->mouse_rect, rect, حجم(*rect)) == 0) {
        أرجع true;
    }
    SDL_memcpy(&کړکۍ->mouse_rect, rect, حجم(*rect));

    أرجع _this->سېټ_کړکۍ_Mouse_Rect(_this, کړکۍ);
}

ثابت SDL_Rect *SDL_Get_کړکۍ_Mouse_Rect(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, عدم);

    إذا (SDL_Rect_تشه(&کړکۍ->mouse_rect)) {
        أرجع عدم;
    } وإلا {
        أرجع &کړکۍ->mouse_rect;
    }
}

bool SDL_سېټ_کړکۍ_Relative_Mouse_ډېرپېښ(SDL_کړکۍ *کړکۍ, bool enabled)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    إذا (enabled == SDL_Get_کړکۍ_Relative_Mouse_ډېرپېښ(کړکۍ)) {
        أرجع true;
    }

    إذا (enabled) {
        کړکۍ->flags |= SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ;
    } وإلا {
        کړکۍ->flags &= ~SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ;
    }

    إذا (!SDL_Update_Relative_Mouse_ډېرپېښ()) {
        إذا (enabled) {
            کړکۍ->flags &= ~SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ;
        } وإلا {
            کړکۍ->flags |= SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ;
        }
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_کړکۍ_Relative_Mouse_ډېرپېښ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (کړکۍ->flags & SDL_کړکۍ_MOUSE_RELATIVE_ډېرپېښ) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

bool SDL_Flash_کړکۍ(SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (_this->Flash_کړکۍ) {
        أرجع _this->Flash_کړکۍ(_this, کړکۍ, operation);
    }

    أرجع SDL_Unsupported();
}

bool SDL_سېټ_کړکۍ_پرمختګ_State(SDL_کړکۍ *کړکۍ, SDL_پرمختګ_State state)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    CHECK_PARAM(state < SDL_پرمختګ_STATE_NONE || state > SDL_پرمختګ_STATE_ERROR) {
        أرجع SDL_InvalidParamError("state");
    }

    کړکۍ->پرمختګ_state = state;

    إذا (_this->Apply_کړکۍ_پرمختګ) {
        إذا (!_this->Apply_کړکۍ_پرمختګ(_this, کړکۍ)) {
            أرجع false;
        }
    }

    أرجع true;
}

SDL_پرمختګ_State SDL_Get_کړکۍ_پرمختګ_State(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, SDL_پرمختګ_STATE_INVALID);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, SDL_پرمختګ_STATE_INVALID);

    أرجع کړکۍ->پرمختګ_state;
}

bool SDL_سېټ_کړکۍ_پرمختګ_ارزښت(SDL_کړکۍ *کړکۍ, عائم ارزښت)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    ارزښت = SDL_clamp(ارزښت, 0.0f, 1.f);

    کړکۍ->پرمختګ_ارزښت = ارزښت;

    إذا (_this->Apply_کړکۍ_پرمختګ) {
        إذا (!_this->Apply_کړکۍ_پرمختګ(_this, کړکۍ)) {
            أرجع false;
        }
    }

    أرجع true;
}

عائم SDL_Get_کړکۍ_پرمختګ_ارزښت(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, -1.0f);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, -1.0f);

    أرجع کړکۍ->پرمختګ_ارزښت;
}

فراغ SDL_On_کړکۍ_Shown(SDL_کړکۍ *کړکۍ)
{
    // Set window state if we have pending window flags cached
    Apply_کړکۍ_Flags(کړکۍ, کړکۍ->pending_flags);
    کړکۍ->pending_flags = 0;
}

فراغ SDL_On_کړکۍ_Hidden(SDL_کړکۍ *کړکۍ)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    کړکۍ->pending_flags |= (کړکۍ->flags & (SDL_کړکۍ_FULLSCREEN | SDL_کړکۍ_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_LEAVE, false);
}

فراغ SDL_On_کړکۍ_Display_بدل_شوی(SDL_کړکۍ *کړکۍ)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    إذا (کړکۍ->update_fullscreen_on_display_بدل_شوی && (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN)) {
        ثابت bool auto_ډېرپېښ_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_سمون_EXCLUSIVE_ډېرپېښ_ON_MOVE, true);

        إذا (auto_ډېرپېښ_switch && (کړکۍ->requested_fullscreen_ډېرپېښ.w != 0 || کړکۍ->requested_fullscreen_ډېرپېښ.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_کړکۍ_Position(کړکۍ);
            bool include_لوړ_density_modes = false;

            إذا (کړکۍ->requested_fullscreen_ډېرپېښ.pixel_density > 1.0f) {
                include_لوړ_density_modes = true;
            }
            ثابت bool وموندل_سمون = SDL_Get_Closest_Fullscreen_Display_ډېرپېښ(displayID, کړکۍ->requested_fullscreen_ډېرپېښ.w, کړکۍ->requested_fullscreen_ډېرپېښ.h,
                                                                         کړکۍ->requested_fullscreen_ډېرپېښ.refresh_شرح, include_لوړ_density_modes, &کړکۍ->current_fullscreen_ډېرپېښ);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            إذا (!وموندل_سمون ||
                کړکۍ->requested_fullscreen_ډېرپېښ.w != کړکۍ->current_fullscreen_ډېرپېښ.w ||
                کړکۍ->requested_fullscreen_ډېرپېښ.h != کړکۍ->current_fullscreen_ډېرپېښ.h) {
                SDL_zero(کړکۍ->current_fullscreen_ډېرپېښ);
            }
        } وإلا {
            SDL_zero(کړکۍ->current_fullscreen_ډېرپېښ);
        }

        إذا (SDL_کړکۍ_FULLSCREEN_VISIBLE(کړکۍ)) {
            SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_کړکۍ_Pixel_اندازه_بدل_شوی(کړکۍ);
}

فراغ SDL_On_کړکۍ_Moved(SDL_کړکۍ *کړکۍ)
{
    SDL_Check_کړکۍ_Display_بدل_شوی(کړکۍ);
}

فراغ SDL_On_کړکۍ_Resized(SDL_کړکۍ *کړکۍ)
{
    SDL_Check_کړکۍ_Display_بدل_شوی(کړکۍ);
    SDL_Check_کړکۍ_Pixel_اندازه_بدل_شوی(کړکۍ);
    SDL_Check_کړکۍ_خوندي_Area_بدل_شوی(کړکۍ);

    إذا ((کړکۍ->flags & SDL_کړکۍ_TRANSPARENT) && _this->Update_کړکۍ_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_اشاره_ګر_Property(کړکۍ->props, SDL_PROP_کړکۍ_SHAPE_اشاره_ګر, عدم);
        إذا (surface) {
            _this->Update_کړکۍ_Shape(_this, کړکۍ, surface);
        }
    }
}

فراغ SDL_Check_کړکۍ_Pixel_اندازه_بدل_شوی(SDL_کړکۍ *کړکۍ)
{
    صحيح pixel_w = 0, pixel_h = 0;

    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &pixel_w, &pixel_h);
    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_PIXEL_اندازه_بدل_شوی, pixel_w, pixel_h);

    SDL_Check_کړکۍ_Display_Scale_بدل_شوی(کړکۍ);
}

فراغ SDL_On_کړکۍ_Pixel_اندازه_بدل_شوی(SDL_کړکۍ *کړکۍ)
{
    کړکۍ->surface_valid = false;
}

فراغ SDL_On_کړکۍ_ژوندی_Resize_Update(SDL_کړکۍ *کړکۍ)
{
    إذا (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } وإلا {
        // Send an expose event so the application can redraw
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ساكن فراغ SDL_Check_کړکۍ_خوندي_Area_بدل_شوی(SDL_کړکۍ *کړکۍ)
{
    SDL_Rect rect;

    rect.x = کړکۍ->خوندي_inset_کیڼ;
    rect.y = کړکۍ->خوندي_inset_سر;
    rect.w = کړکۍ->w - (کړکۍ->خوندي_inset_ښی + کړکۍ->خوندي_inset_کیڼ);
    rect.h = کړکۍ->h - (کړکۍ->خوندي_inset_سر + کړکۍ->خوندي_inset_bottom);
    إذا (SDL_memcmp(&rect, &کړکۍ->خوندي_rect, حجم(rect)) != 0) {
        SDL_copyp(&کړکۍ->خوندي_rect, &rect);
        SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_خوندي_AREA_بدل_شوی, 0, 0);
    }
}

فراغ SDL_سېټ_کړکۍ_خوندي_Area_Insets(SDL_کړکۍ *کړکۍ, صحيح کیڼ, صحيح ښی, صحيح سر, صحيح bottom)
{
    کړکۍ->خوندي_inset_کیڼ = کیڼ;
    کړکۍ->خوندي_inset_ښی = ښی;
    کړکۍ->خوندي_inset_سر = سر;
    کړکۍ->خوندي_inset_bottom = bottom;
    SDL_Check_کړکۍ_خوندي_Area_بدل_شوی(کړکۍ);
}

bool SDL_Get_کړکۍ_خوندي_Area(SDL_کړکۍ *کړکۍ, SDL_Rect *rect)
{
    إذا (rect) {
        SDL_zerop(rect);
    }

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (rect) {
        إذا (SDL_Rect_تشه(&کړکۍ->خوندي_rect)) {
            rect->w = کړکۍ->w;
            rect->h = کړکۍ->h;
        } وإلا {
            SDL_copyp(rect, &کړکۍ->خوندي_rect);
        }
    }
    أرجع true;
}

فراغ SDL_On_کړکۍ_Minimized(SDL_کړکۍ *کړکۍ)
{
    إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

فراغ SDL_On_کړکۍ_Maximized(SDL_کړکۍ *کړکۍ)
{
}

فراغ SDL_On_کړکۍ_Restored(SDL_کړکۍ *کړکۍ)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    إذا (کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) {
        SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

فراغ SDL_On_کړکۍ_Enter(SDL_کړکۍ *کړکۍ)
{
    إذا (_this->On_کړکۍ_Enter) {
        _this->On_کړکۍ_Enter(_this, کړکۍ);
    }
    SDL_Update_Relative_Mouse_ډېرپېښ();
}

فراغ SDL_On_کړکۍ_Leave(SDL_کړکۍ *کړکۍ)
{
    SDL_Update_Relative_Mouse_ډېرپېښ();
}

فراغ SDL_On_کړکۍ_Focus_Gained(SDL_کړکۍ *کړکۍ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    إذا (mouse && mouse->relative_ډېرپېښ) {
        SDL_سېټ_Mouse_Focus(کړکۍ);
    }

    SDL_Update_کړکۍ_Grab(کړکۍ);
}

ساكن bool SDL_ShouldMinimizeOnFocusLoss(SDL_کړکۍ *کړکۍ)
{
    ثابت حرف *hint;

    إذا (!(کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) || کړکۍ->is_destroying) {
        أرجع false;
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (Cocoa_IsShowingModalDialog(کړکۍ)) {
            أرجع false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } وإلا إذا (Cocoa_Is_کړکۍ_دننه_Fullscreen_Space(کړکۍ)) {
            أرجع false;
        }
    }
#د_که_پای

#که_تعریف_شوی SDL_PLATFORM_ANDROID
    {
        خارجي bool Android_JNI_ShouldMinimizeOnFocusLoss(فراغ);
        إذا (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            أرجع false;
        }
    }
#د_که_پای

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    إذا (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        إذا (کړکۍ->fullscreen_exclusive && !SDL_ډېرپېښ_Switching_Emulated(_this)) {
            أرجع true;
        } وإلا {
            أرجع false;
        }
    }
    أرجع SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

فراغ SDL_On_کړکۍ_Focus_ورک(SDL_کړکۍ *کړکۍ)
{
    SDL_Update_کړکۍ_Grab(کړکۍ);

    إذا (SDL_ShouldMinimizeOnFocusLoss(کړکۍ)) {
        SDL_Minimize_کړکۍ(کړکۍ);
    }
}

SDL_کړکۍ *SDL_GetToplevelForKeyboardFocus(فراغ)
{
    SDL_کړکۍ *focus = SDL_GetKeyboardFocus();

    إذا (focus) {
        // Get the toplevel parent window.
        طالما (focus->پلار) {
            focus = focus->پلار;
        }
    }

    أرجع focus;
}

bool SDL_جمع_کړه_کړکۍ_Renderer(SDL_کړکۍ *کړکۍ, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(کړکۍ->renderers, (کړکۍ->عدد_renderers + 1) * حجم(*renderers));
    إذا (!renderers) {
        أرجع false;
    }

    کړکۍ->renderers = renderers;
    کړکۍ->renderers[کړکۍ->عدد_renderers++] = renderer;

    SDL_سېټ_اشاره_ګر_Property(SDL_Get_کړکۍ_Properties(کړکۍ), SDL_PROP_کړکۍ_RENDERER_اشاره_ګر, renderer);
    أرجع true;
}

فراغ SDL_Remove_کړکۍ_Renderer(SDL_کړکۍ *کړکۍ, SDL_Renderer *renderer)
{
    لكل (صحيح i = 0; i < کړکۍ->عدد_renderers; ++i) {
        إذا (کړکۍ->renderers[i] == renderer) {
            إذا (i < (کړکۍ->عدد_renderers - 1)) {
                SDL_memmove(&کړکۍ->renderers[i], &کړکۍ->renderers[i + 1], (کړکۍ->عدد_renderers - i - 1) * حجم(کړکۍ->renderers[i]));
            }
            --کړکۍ->عدد_renderers;
            اكسر;
        }
    }

    SDL_PropertiesID props = SDL_Get_کړکۍ_Properties(کړکۍ);
    إذا (SDL_Get_اشاره_ګر_Property(props, SDL_PROP_کړکۍ_RENDERER_اشاره_ګر, عدم) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_کړکۍ_RENDERER_اشاره_ګر);
    }
}

فراغ SDL_Destroy_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ,);

    کړکۍ->is_destroying = true;

    // Destroy any child windows of this window
    طالما (کړکۍ->لومړی_ماشوم) {
        SDL_Destroy_کړکۍ(کړکۍ->لومړی_ماشوم);
    }

    SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_DESTROYED, 0, 0);

    SDL_Destroy_کړکۍ_Surface(کړکۍ);

    SDL_Renderer *renderer = SDL_GetRenderer(کړکۍ);
    إذا (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_ډېرپېښ(کړکۍ, SDL_FULLSCREEN_OP_LEAVE, true);
    إذا (!(کړکۍ->flags & SDL_کړکۍ_EXTERNAL)) {
        SDL_Hide_کړکۍ(کړکۍ);
    }

    SDL_DestroyProperties(کړکۍ->متن_ننوت_props);

    SDL_Destroy_کړکۍ_Texture(_this, کړکۍ);
    SDL_DestroyProperties(کړکۍ->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    إذا (_this->سېټ_کړکۍ_Modal && (کړکۍ->flags & SDL_کړکۍ_MODAL)) {
        _this->سېټ_کړکۍ_Modal(_this, کړکۍ, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    لكل (صحيح i = 0; i < _this->عدد_displays; ++i) {
        إذا (_this->displays[i]->fullscreen_کړکۍ == کړکۍ) {
            _this->displays[i]->fullscreen_کړکۍ = عدم;
        }
    }

    // Make sure this window no longer has focus
    إذا (SDL_GetKeyboardFocus() == کړکۍ) {
        SDL_سېټ_Keyboard_Focus(عدم);
    }
    إذا ((کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    إذا (SDL_GetMouseFocus() == کړکۍ) {
        SDL_سېټ_Mouse_Focus(عدم);
    }

    // Make no context current if this is the current context window
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        إذا (_this->current_glwin == کړکۍ) {
            SDL_GL_MakeCurrent(کړکۍ, عدم);
        }
    }

    إذا (_this->Destroy_کړکۍ) {
        _this->Destroy_کړکۍ(_this, کړکۍ);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    إذا (کړکۍ->flags & SDL_کړکۍ_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->grabbed_کړکۍ == کړکۍ) {
        _this->grabbed_کړکۍ = عدم; // ungrabbing input.
    }

    إذا (_this->current_glwin == کړکۍ) {
        _this->current_glwin = عدم;
    }

    SDL_Compare_And_بدلون_Atomic_اشاره_ګر(&_this->wakeup_کړکۍ, کړکۍ, عدم);

    // Now invalidate magic
    SDL_سېټ_Object_Valid(کړکۍ, SDL_OBJECT_TYPE_کړکۍ, false);

    // Free memory associated with the window
    SDL_free(کړکۍ->title);
    SDL_DestroySurface(کړکۍ->icon);

    // Unlink the window from its siblings.
    SDL_Update_کړکۍ_Hierarchy(کړکۍ, عدم);

    // Unlink the window from the global window list
    إذا (کړکۍ->بل) {
        کړکۍ->بل->prev = کړکۍ->prev;
    }
    إذا (کړکۍ->prev) {
        کړکۍ->prev->بل = کړکۍ->بل;
    } وإلا {
        _this->windows = کړکۍ->بل;
    }

    SDL_free(کړکۍ->renderers);
    SDL_free(کړکۍ);

#که_تعریف_شوی SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#د_که_پای
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
#د_که_پای
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    طالما (_this->windows) {
        SDL_Destroy_کړکۍ(_this->windows);
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

bool SDL_GL_بارول_Library(ثابت حرف *لار)
{
    bool پایله;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->gl_config.driver_loaded) {
        إذا (لار && SDL_strcmp(لار, _this->gl_config.driver_لار) != 0) {
            أرجع SDL_سېټ_Error("OpenGL library already loaded");
        }
        پایله = true;
    } وإلا {
        إذا (!_this->GL_بارول_Library) {
            أرجع SDL_DllNotSupported("OpenGL");
        }
        پایله = _this->GL_بارول_Library(_this, لار);
    }
    إذا (پایله) {
        ++_this->gl_config.driver_loaded;
    } وإلا {
        إذا (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    أرجع پایله;
}

SDL_Function_اشاره_ګر SDL_GL_Get_Proc_پته(ثابت حرف *proc)
{
    SDL_Function_اشاره_ګر func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;
    إذا (_this->GL_Get_Proc_پته) {
        إذا (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_پته(_this, proc);
        } وإلا {
            SDL_سېټ_Error("No GL driver has been loaded");
        }
    } وإلا {
        SDL_سېټ_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    أرجع func;
}

SDL_Function_اشاره_ګر SDL_EGL_Get_Proc_پته(ثابت حرف *proc)
{
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    SDL_Function_اشاره_ګر func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;

    إذا (_this->egl_معلومات) {
        func = SDL_EGL_Get_Proc_پته_دننی(_this, proc);
    } وإلا {
        SDL_سېټ_Error("No EGL library has been loaded");
    }

    أرجع func;
#وإلا
    SDL_سېټ_Error("SDL was not built with EGL support");
    أرجع عدم;
#د_که_پای
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
#که_نه_تعریف_شوی SDL_VIDEO_OPENGL
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint شاخص);
#د_که_پای

ساكن SDL_INLINE bool is_At_لږترلږه_GL3(ثابت حرف *verstr)
{
    أرجع verstr && (SDL_atoi(verstr) >= 3);
}
#د_که_پای // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت حرف *extension)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت حرف *extensions;
    ثابت حرف *پیل;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    إذا (where || *extension == '\0') {
        أرجع false;
    }
    // See if there's a hint or environment variable override
    پیل = SDL_GetHint(extension);
    إذا (پیل && *پیل == '0') {
        أرجع false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پته("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (is_At_لږترلږه_GL3((ثابت حرف *)glGetStringFunc(GL_نسخه))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint عدد_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_پته("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پته("glGetIntegerv");
        إذا ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            أرجع false;
        }

#که_نه_تعریف_شوی GL_عدد_EXTENSIONS
#تعریف_کړه GL_عدد_EXTENSIONS 0x821D
#د_که_پای
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

    پیل = extensions;

    لكل (;;) {
        where = SDL_strstr(پیل, extension);
        إذا (!where) {
            اكسر;
        }

        terminator = where + SDL_strlen(extension);
        إذا (where == extensions || *(where - 1) == ' ') {
            إذا (*terminator == ' ' || *terminator == '\0') {
                أرجع true;
            }
        }

        پیل = terminator;
    }
    أرجع false;
#وإلا
    أرجع false;
#د_که_پای
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
#د_که_پای
}

فراغ SDL_EGL_سېټ_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
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

فراغ SDL_GL_Reset_ځانګړتیاوې(فراغ)
{
    إذا (!_this) {
        أرجع;
    }

    _this->egl_platformattrib_callback = عدم;
    _this->egl_surfaceattrib_callback = عدم;
    _this->egl_contextattrib_callback = عدم;
    _this->egl_attrib_callback_userdata = عدم;

    _this->gl_config.red_اندازه = 8;
    _this->gl_config.green_اندازه = 8;
    _this->gl_config.blue_اندازه = 8;
    _this->gl_config.alpha_اندازه = 8;
    _this->gl_config.بفر_اندازه = 0;
    _this->gl_config.ژوروالی_اندازه = 16;
    _this->gl_config.stencil_اندازه = 0;
    _this->gl_config.double_بفر = 1;
    _this->gl_config.accum_red_اندازه = 0;
    _this->gl_config.accum_green_اندازه = 0;
    _this->gl_config.accum_blue_اندازه = 0;
    _this->gl_config.accum_alpha_اندازه = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#که_تعریف_شوی SDL_VIDEO_OPENGL
    _this->gl_config.major_نسخه = 2;
    _this->gl_config.minor_نسخه = 1;
    _this->gl_config.profile_ماسک = 0;
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_نسخه = 2;
    _this->gl_config.minor_نسخه = 0;
    _this->gl_config.profile_ماسک = SDL_GL_CONTEXT_PROFILE_ES;
#وإلاإذا defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_نسخه = 1;
    _this->gl_config.minor_نسخه = 1;
    _this->gl_config.profile_ماسک = SDL_GL_CONTEXT_PROFILE_ES;
#د_که_پای

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    إذا (_this->GL_سېټ_Default_Profile_Config) {
        _this->GL_سېټ_Default_Profile_Config(_this);
    }
}

bool SDL_GL_سېټ_Attribute(SDL_GLAttr attr, صحيح ارزښت)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool پایله;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    پایله = true;
    بدل (attr) {
    حالة SDL_GL_RED_اندازه:
        _this->gl_config.red_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_GREEN_اندازه:
        _this->gl_config.green_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_BLUE_اندازه:
        _this->gl_config.blue_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_ALPHA_اندازه:
        _this->gl_config.alpha_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_بفر = ارزښت;
        اكسر;
    حالة SDL_GL_بفر_اندازه:
        _this->gl_config.بفر_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_ژوروالی_اندازه:
        _this->gl_config.ژوروالی_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_STENCIL_اندازه:
        _this->gl_config.stencil_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_ACCUM_RED_اندازه:
        _this->gl_config.accum_red_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_اندازه:
        _this->gl_config.accum_green_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_اندازه:
        _this->gl_config.accum_blue_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_اندازه:
        _this->gl_config.accum_alpha_اندازه = ارزښت;
        اكسر;
    حالة SDL_GL_STEREO:
        _this->gl_config.stereo = ارزښت;
        اكسر;
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = ارزښت;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = ارزښت;
        اكسر;
    حالة SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = ارزښت;
        اكسر;
    حالة SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = ارزښت;
        اكسر;
    حالة SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = ارزښت;
        اكسر;
    حالة SDL_GL_CONTEXT_MAJOR_نسخه:
        _this->gl_config.major_نسخه = ارزښت;
        اكسر;
    حالة SDL_GL_CONTEXT_MINOR_نسخه:
        _this->gl_config.minor_نسخه = ارزښت;
        اكسر;
    حالة SDL_GL_CONTEXT_FLAGS:
        إذا (ارزښت & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            پایله = SDL_سېټ_Error("Unknown OpenGL context flag %d", ارزښت);
            اكسر;
        }
        _this->gl_config.flags = ارزښت;
        اكسر;
    حالة SDL_GL_CONTEXT_PROFILE_ماسک:
        إذا (ارزښت != 0 &&
            ارزښت != SDL_GL_CONTEXT_PROFILE_CORE &&
            ارزښت != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            ارزښت != SDL_GL_CONTEXT_PROFILE_ES) {
            پایله = SDL_سېټ_Error("Unknown OpenGL context profile %d", ارزښت);
            اكسر;
        }
        _this->gl_config.profile_ماسک = ارزښت;
        اكسر;
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = ارزښت;
        اكسر;
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = ارزښت;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = ارزښت;
        اكسر;
    حالة SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = ارزښت;
        اكسر;
    حالة SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = ارزښت;
        اكسر;
    حالة SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = ارزښت;
        اكسر;
    افتراضي:
        پایله = SDL_سېټ_Error("Unknown OpenGL attribute");
        اكسر;
    }
    أرجع پایله;
#وإلا
    أرجع SDL_Unsupported();
#د_که_پای // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحيح *ارزښت)
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
#که_تعریف_شوی SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_شا_کیڼ;
    GLenum attachmentattrib = 0;
#د_که_پای

    CHECK_PARAM(!ارزښت) {
        أرجع SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *ارزښت = 0;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    بدل (attr) {
    حالة SDL_GL_RED_اندازه:
#که_تعریف_شوی SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_اندازه;
#د_که_پای
        attrib = GL_RED_بټونه;
        اكسر;
    حالة SDL_GL_BLUE_اندازه:
#که_تعریف_شوی SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_اندازه;
#د_که_پای
        attrib = GL_BLUE_بټونه;
        اكسر;
    حالة SDL_GL_GREEN_اندازه:
#که_تعریف_شوی SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_اندازه;
#د_که_پای
        attrib = GL_GREEN_بټونه;
        اكسر;
    حالة SDL_GL_ALPHA_اندازه:
#که_تعریف_شوی SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_اندازه;
#د_که_پای
        attrib = GL_ALPHA_بټونه;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
#که_تعریف_شوی SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        اكسر;
#وإلا
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *ارزښت = _this->gl_config.double_بفر;
        أرجع true;
#د_که_پای
    حالة SDL_GL_ژوروالی_اندازه:
#که_تعریف_شوی SDL_VIDEO_OPENGL
        attachment = GL_ژوروالی;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ژوروالی_اندازه;
#د_که_پای
        attrib = GL_ژوروالی_بټونه;
        اكسر;
    حالة SDL_GL_STENCIL_اندازه:
#که_تعریف_شوی SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_اندازه;
#د_که_پای
        attrib = GL_STENCIL_بټونه;
        اكسر;
#که_تعریف_شوی SDL_VIDEO_OPENGL
    حالة SDL_GL_ACCUM_RED_اندازه:
        attrib = GL_ACCUM_RED_بټونه;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_اندازه:
        attrib = GL_ACCUM_GREEN_بټونه;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_اندازه:
        attrib = GL_ACCUM_BLUE_بټونه;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_اندازه:
        attrib = GL_ACCUM_ALPHA_بټونه;
        اكسر;
    حالة SDL_GL_STEREO:
        attrib = GL_STEREO;
        اكسر;
#وإلا
    حالة SDL_GL_ACCUM_RED_اندازه:
    حالة SDL_GL_ACCUM_GREEN_اندازه:
    حالة SDL_GL_ACCUM_BLUE_اندازه:
    حالة SDL_GL_ACCUM_ALPHA_اندازه:
    حالة SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *ارزښت = 0;
        أرجع true;
#د_که_پای
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        اكسر;
    حالة SDL_GL_بفر_اندازه:
    {
        صحيح rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        إذا (!SDL_GL_GetAttribute(SDL_GL_RED_اندازه, &rsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_GREEN_اندازه, &gsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_BLUE_اندازه, &bsize)) {
            أرجع false;
        }
        إذا (!SDL_GL_GetAttribute(SDL_GL_ALPHA_اندازه, &asize)) {
            أرجع false;
        }

        *ارزښت = rsize + gsize + bsize + asize;
        أرجع true;
    }
    حالة SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *ارزښت = (_this->gl_config.accelerated != 0);
        أرجع true;
    }
    حالة SDL_GL_RETAINED_BACKING:
    {
        *ارزښت = _this->gl_config.retained_backing;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MAJOR_نسخه:
    {
        *ارزښت = _this->gl_config.major_نسخه;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MINOR_نسخه:
    {
        *ارزښت = _this->gl_config.minor_نسخه;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_FLAGS:
    {
        *ارزښت = _this->gl_config.flags;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_PROFILE_ماسک:
    {
        *ارزښت = _this->gl_config.profile_ماسک;
        أرجع true;
    }
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *ارزښت = _this->gl_config.share_with_current_context;
        أرجع true;
    }
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *ارزښت = _this->gl_config.framebuffer_srgb_capable;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_NO_ERROR:
    {
        *ارزښت = _this->gl_config.no_error;
        أرجع true;
    }
    حالة SDL_GL_EGL_PLATFORM:
    {
        *ارزښت = _this->gl_config.egl_platform;
        أرجع true;
    }
    حالة SDL_GL_FLOATBUFFERS:
    {
        إذا (_this->gl_config.HAS_GL_ARB_color_بفر_float) {
            attrib = GL_RGBA_FLOAT_ډېرپېښ_ARB;
            اكسر;
        } وإلا {
            أرجع 0;
        }
    }
    افتراضي:
        أرجع SDL_سېټ_Error("Unknown OpenGL attribute");
    }

#که_تعریف_شوی SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پته("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (attachmentattrib && is_At_لږترلږه_GL3((ثابت حرف *)glGetStringFunc(GL_نسخه))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_پته("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_پته("glBindFramebuffer");
        إذا (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_پته("glGetFramebufferAttachmentParameteriv");
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
            إذا (attachment == GL_ژوروالی || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            إذا (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)ارزښت);
            } وإلا {
                *ارزښت = 0;
            }
            إذا (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } وإلا {
            أرجع false;
        }
    } وإلا
#د_که_پای
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پته("glGetIntegerv");
        إذا (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)ارزښت);
        } وإلا {
            أرجع false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_پته("glGetError");
    إذا (!glGetErrorFunc) {
        أرجع false;
    }

    error = glGetErrorFunc();
    إذا (error != GL_NO_ERROR) {
        إذا (error == GL_INVALID_ENUM) {
            أرجع SDL_سېټ_Error("OpenGL error: GL_INVALID_ENUM");
        } وإلا إذا (error == GL_INVALID_ارزښت) {
            أرجع SDL_سېټ_Error("OpenGL error: GL_INVALID_VALUE");
        }
        أرجع SDL_سېټ_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    إذا (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *ارزښت = (*ارزښت == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    أرجع true;
#وإلا
    أرجع SDL_Unsupported();
#د_که_پای // SDL_VIDEO_OPENGL
}

#تعریف_کړه NOT_AN_OPENGL_کړکۍ "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_کړکۍ *کړکۍ)
{
    SDL_GLContext ctx = عدم;
    CHECK_کړکۍ_MAGIC(کړکۍ, عدم);

    إذا (!(کړکۍ->flags & SDL_کړکۍ_OPENGL)) {
        SDL_سېټ_Error(NOT_AN_OPENGL_کړکۍ);
        أرجع عدم;
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحيح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    إذا (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#د_که_پای

    ctx = _this->GL_CreateContext(_this, کړکۍ);

    // Creating a context is assumed to make it current in the SDL driver.
    إذا (ctx) {
        _this->current_glwin = کړکۍ;
        _this->current_glctx = ctx;
        SDL_سېټ_TLS(&_this->current_glwin_tls, کړکۍ, عدم);
        SDL_سېټ_TLS(&_this->current_glctx_tls, ctx, عدم);
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    إذا (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_پته(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پته("glGetString");
        إذا (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            إذا (_this->gl_config.profile_ماسک & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } وإلا {
                supported = is_At_لږترلږه_GL3((ثابت حرف *)glGetStringFunc(GL_نسخه)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            إذا (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#د_که_پای

    أرجع ctx;
}

bool SDL_GL_MakeCurrent(SDL_کړکۍ *کړکۍ, SDL_GLContext context)
{
    bool پایله;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (کړکۍ == SDL_GL_Get_Current_کړکۍ() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        أرجع true;
    }

    إذا (!context) {
        کړکۍ = عدم;
    } وإلا إذا (کړکۍ) {
        CHECK_کړکۍ_MAGIC(کړکۍ, false);

        إذا (!(کړکۍ->flags & SDL_کړکۍ_OPENGL)) {
            أرجع SDL_سېټ_Error(NOT_AN_OPENGL_کړکۍ);
        }
    } وإلا إذا (!_this->gl_allow_no_surface) {
        أرجع SDL_سېټ_Error("Use of OpenGL without a window is not supported on this platform");
    }

    پایله = _this->GL_MakeCurrent(_this, کړکۍ, context);
    إذا (پایله) {
        _this->current_glwin = کړکۍ;
        _this->current_glctx = context;
        SDL_سېټ_TLS(&_this->current_glwin_tls, کړکۍ, عدم);
        SDL_سېټ_TLS(&_this->current_glctx_tls, context, عدم);
    }
    أرجع پایله;
}

SDL_کړکۍ *SDL_GL_Get_Current_کړکۍ(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع (SDL_کړکۍ *)SDL_GetTLS(&_this->current_glwin_tls);
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
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع EGL_NO_DISPLAY;
    }
    إذا (!_this->egl_معلومات) {
        SDL_سېټ_Error("There is no current EGL display");
        أرجع EGL_NO_DISPLAY;
    }
    أرجع _this->egl_معلومات->egl_display;
#وإلا
    SDL_سېټ_Error("SDL was not built with EGL support");
    أرجع عدم;
#د_که_پای
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(فراغ)
{
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_معلومات) {
        SDL_سېټ_Error("There is no current EGL display");
        أرجع عدم;
    }
    أرجع _this->egl_معلومات->egl_config;
#وإلا
    SDL_سېټ_Error("SDL was not built with EGL support");
    أرجع عدم;
#د_که_پای
}

SDL_EGLConfig SDL_EGL_Get_کړکۍ_Surface(SDL_کړکۍ *کړکۍ)
{
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_معلومات) {
        SDL_سېټ_Error("There is no current EGL display");
        أرجع عدم;
    }
    إذا (_this->GL_GetEGLSurface) {
        أرجع _this->GL_GetEGLSurface(_this, کړکۍ);
    }
    أرجع عدم;
#وإلا
    SDL_سېټ_Error("SDL was not built with EGL support");
    أرجع عدم;
#د_که_پای
}

bool SDL_GL_سېټ_بدلون_Interval(صحيح interval)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_سېټ_Error("No OpenGL context has been made current");
    } وإلا إذا (_this->GL_سېټ_بدلون_Interval) {
        أرجع _this->GL_سېټ_بدلون_Interval(_this, interval);
    } وإلا {
        أرجع SDL_سېټ_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_بدلون_Interval(صحيح *interval)
{
    CHECK_PARAM(!interval) {
       أرجع SDL_InvalidParamError("interval");
    }

    *interval = 0;

    إذا (!_this) {
        أرجع SDL_سېټ_Error("no video driver");
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_سېټ_Error("no current context");
    } وإلا إذا (_this->GL_Get_بدلون_Interval) {
        أرجع _this->GL_Get_بدلون_Interval(_this, interval);
    } وإلا {
        أرجع SDL_سېټ_Error("not implemented");
    }
}

bool SDL_GL_بدلون_کړکۍ(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!(کړکۍ->flags & SDL_کړکۍ_OPENGL)) {
        أرجع SDL_سېټ_Error(NOT_AN_OPENGL_کړکۍ);
    }

    إذا (SDL_GL_Get_Current_کړکۍ() != کړکۍ) {
        أرجع SDL_سېټ_Error("The specified window has not been made current");
    }

    أرجع _this->GL_بدلون_کړکۍ(_this, کړکۍ);
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
ساكن فراغ Create_ماسک_From_Color_کلی_Or_Alpha(SDL_Surface *icon, Uint8 *ماسک, صحيح flags)
{
    صحيح x, y;
    Uint32 colorkey;
#تعریف_کړه سېټ_MASKBIT(icon, x, y, ماسک) \
    ماسک[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    بدل (SDL_BYTESPERPIXEL(icon->format)) {
    حالة 1:
        {
            Uint8 *pixels;
            لكل (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                لكل (x = 0; x < icon->w; ++x) {
                    إذا (*pixels++ == colorkey) {
                        سېټ_MASKBIT(icon, x, y, ماسک);
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
                        سېټ_MASKBIT(icon, x, y, ماسک);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سېټ_MASKBIT(icon, x, y, ماسک);
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
                        سېټ_MASKBIT(icon, x, y, ماسک);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سېټ_MASKBIT(icon, x, y, ماسک);
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
فراغ SDL_WM_سېټ_Icon(SDL_Surface *icon, Uint8 *ماسک)
{
    إذا (icon && _this->سېټ_Icon) {
        // Generate a mask if necessary, and create the icon!
        إذا (ماسک == عدم) {
            صحيح ماسک_len = icon->h * (icon->w + 7) / 8;
            صحيح flags = 0;
            ماسک = (Uint8 *) SDL_malloc(ماسک_len);
            إذا (ماسک == عدم) {
                أرجع;
            }
            SDL_memset(ماسک, ~0, ماسک_len);
            إذا (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            إذا (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            إذا (flags) {
                Create_ماسک_From_Color_کلی_Or_Alpha(icon, ماسک, flags);
            }
            _this->سېټ_Icon(_this, icon, ماسک);
            SDL_free(ماسک);
        } وإلا {
            _this->سېټ_Icon(_this, icon, ماسک);
        }
    }
}
#د_که_پای

SDL_متن_ننوت_Type SDL_Get_متن_ننوت_Type(SDL_PropertiesID props)
{
    أرجع (SDL_متن_ننوت_Type)SDL_Get_شمېره_Property(props, SDL_PROP_TEXTINPUT_TYPE_شمېره, SDL_TEXTINPUT_TYPE_متن);
}

SDL_Capitalization SDL_Get_متن_ننوت_Capitalization(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_شمېره)) {
        أرجع (SDL_Capitalization)SDL_Get_شمېره_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_شمېره, SDL_CAPITALIZE_NONE);
    }

    بدل (SDL_Get_متن_ننوت_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن:
        أرجع SDL_CAPITALIZE_SENTENCES;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        أرجع SDL_CAPITALIZE_ټکي;
    افتراضي:
        أرجع SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_متن_ننوت_Autocorrect(SDL_PropertiesID props)
{
    أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_متن_ننوت_Multiline(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_RETURN_کلی_HIDES_IME, false)) {
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

bool SDL_پیل_متن_ننوت(SDL_کړکۍ *کړکۍ)
{
    أرجع SDL_پیل_متن_ننوت_With_Properties(کړکۍ, 0);
}

bool SDL_پیل_متن_ننوت_With_Properties(SDL_کړکۍ *کړکۍ, SDL_PropertiesID props)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (کړکۍ->متن_ننوت_props) {
        SDL_DestroyProperties(کړکۍ->متن_ننوت_props);
        کړکۍ->متن_ننوت_props = 0;
    }

    إذا (props) {
        کړکۍ->متن_ننوت_props = SDL_CreateProperties();
        إذا (!کړکۍ->متن_ننوت_props) {
            أرجع false;
        }
        إذا (!SDL_CopyProperties(props, کړکۍ->متن_ننوت_props)) {
            أرجع false;
        }
    }

    إذا (_this->سېټ_متن_ننوت_Properties) {
        _this->سېټ_متن_ننوت_Properties(_this, کړکۍ, props);
    }

    إذا (!کړکۍ->متن_ننوت_فعال) {
        // Start the text input system
        إذا (_this->پیل_متن_ننوت) {
            إذا (!_this->پیل_متن_ننوت(_this, کړکۍ, props)) {
                أرجع false;
            }
        }
        کړکۍ->متن_ننوت_فعال = true;
    }

    // Show the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(کړکۍ)) {
        إذا (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, کړکۍ, props);
        }
    }
    أرجع true;
}

bool SDL_متن_ننوت_فعال(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    أرجع کړکۍ->متن_ننوت_فعال;
}

bool SDL_Stop_متن_ننوت(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (کړکۍ->متن_ننوت_فعال) {
        // Stop the text input system
        إذا (_this->Stop_متن_ننوت) {
            _this->Stop_متن_ننوت(_this, کړکۍ);
        }
        کړکۍ->متن_ننوت_فعال = false;
    }

    // Hide the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(کړکۍ)) {
        إذا (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, کړکۍ);
        }
    }
    أرجع true;
}

bool SDL_سېټ_متن_ننوت_Area(SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rect, صحيح cursor)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (rect) {
        SDL_copyp(&کړکۍ->متن_ننوت_rect, rect);
        کړکۍ->متن_ننوت_cursor = cursor;
    } وإلا {
        SDL_zero(کړکۍ->متن_ننوت_rect);
        کړکۍ->متن_ننوت_cursor = 0;
    }

    إذا (_this && _this->Update_متن_ننوت_Area) {
        إذا (!_this->Update_متن_ننوت_Area(_this, کړکۍ)) {
            أرجع false;
        }
    }
    أرجع true;
}

bool SDL_Get_متن_ننوت_Area(SDL_کړکۍ *کړکۍ, SDL_Rect *rect, صحيح *cursor)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (rect) {
        SDL_copyp(rect, &کړکۍ->متن_ننوت_rect);
    }
    إذا (cursor) {
        *cursor = کړکۍ->متن_ننوت_cursor;
    }
    أرجع true;
}

bool SDL_ClearComposition(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (_this->ClearComposition) {
        أرجع _this->ClearComposition(_this, کړکۍ);
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

bool SDL_ScreenKeyboardShown(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

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
        SDL_ټېل_Event(&event);
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
        SDL_ټېل_Event(&event);
    }
}

صحيح SDL_Get_پیغام_Box_شمېر(فراغ)
{
    أرجع SDL_GetAtomicInt(&SDL_messagebox_شمېر);
}

bool SDL_Show_پیغام_Box(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
    صحيح dummybutton;
    bool پایله = false;
    bool show_cursor_prev;
    SDL_کړکۍ *current_کړکۍ;
    SDL_پیغام_Box_معلومات mbdata;

    CHECK_PARAM(!messageboxdata) {
        أرجع SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        أرجع SDL_سېټ_Error("Invalid number of buttons");
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

    إذا (messageboxdata->پیغام) {
        ثابت size_t slen = SDL_strlen(messageboxdata->پیغام) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        إذا (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            أرجع false;
        }
        SDL_memcpy(msgcpy, messageboxdata->پیغام, slen);
    }

    (فراغ)SDL_AtomicIncRef(&SDL_messagebox_شمېر);

    current_کړکۍ = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_سېټ_Relative_Mouse_ډېرپېښ(false);
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
    mbdata.پیغام = msgcpy;
    إذا (!mbdata.پیغام) {
        mbdata.پیغام = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    إذا (_this && _this->Show_پیغام_Box) {
        پایله = _this->Show_پیغام_Box(_this, messageboxdata, buttonID);
    } وإلا {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        إذا (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            طالما (driver_attempt && (*driver_attempt != 0) && !پایله) {
                ثابت حرف *driver_attempt_پای_ټکی = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_پای_ټکی) ? (driver_attempt_پای_ټکی - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                لكل (صحيح i = 0; bootstrap[i]; ++i) {
                    إذا (bootstrap[i]->Show_پیغام_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        إذا (bootstrap[i]->Show_پیغام_Box(messageboxdata, buttonID)) {
                            پایله = true;
                        }
                        اكسر;
                    }
                }

                driver_attempt = (driver_attempt_پای_ټکی) ? (driver_attempt_پای_ټکی + 1) : عدم;
            }
        } وإلا {
            لكل (صحيح i = 0; bootstrap[i]; ++i) {
                إذا (bootstrap[i]->Show_پیغام_Box && bootstrap[i]->Show_پیغام_Box(messageboxdata, buttonID)) {
                    پایله = true;
                    اكسر;
                }
            }
        }
    }

    إذا (!پایله) {
        ثابت حرف *error = SDL_GetError();

        إذا (!*error) {
            SDL_سېټ_Error("No message system available");
        }
    } وإلا {
        SDL_ClearError();
    }

    (فراغ)SDL_AtomicDecRef(&SDL_messagebox_شمېر);

    إذا (current_کړکۍ) {
        SDL_Raise_کړکۍ(current_کړکۍ);
    }

    إذا (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_ډېرپېښ();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    أرجع پایله;
}

bool SDL_Show_Simple_پیغام_Box(SDL_پیغام_Box_Flags flags, ثابت حرف *title, ثابت حرف *پیغام, SDL_کړکۍ *کړکۍ)
{
#إذا defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_ښی;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_ښی = gsp_Has_Gpu_ښی();
    إذا (!has_Gpu_ښی)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_متن_کلمه_WRAP, CFG_LANGUAGE_EN);
    error_متن(&errCnf, پیغام);
    errorDisp(&errCnf);

    إذا (!has_Gpu_ښی)
        gfxExit();

    أرجع true;
#وإلا
    SDL_پیغام_Box_معلومات معلومات;
    SDL_پیغام_Box_Button_معلومات button;

    SDL_zero(معلومات);
    معلومات.flags = flags;
    معلومات.title = title;
    معلومات.پیغام = پیغام;
    معلومات.numbuttons = 1;
    معلومات.buttons = &button;
    معلومات.کړکۍ = کړکۍ;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.متن = "OK";

    أرجع SDL_Show_پیغام_Box(&معلومات, عدم);
#د_که_پای
}

bool SDL_ShouldAllowTopmost(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_کړکۍ_ALLOW_TOPMOST, true);
}

bool SDL_Show_کړکۍ_System_Menu(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);
    CHECK_کړکۍ_NOT_POPUP(کړکۍ, false);

    إذا (_this->Show_کړکۍ_System_Menu) {
        _this->Show_کړکۍ_System_Menu(کړکۍ, x, y);
        أرجع true;
    }

    أرجع SDL_Unsupported();
}

bool SDL_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, SDL_موندنه_Test callback, فراغ *callback_معلومات)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!_this->سېټ_کړکۍ_موندنه_Test) {
        أرجع SDL_Unsupported();
    }

    کړکۍ->موندنه_test = callback;
    کړکۍ->موندنه_test_معلومات = callback_معلومات;

    أرجع _this->سېټ_کړکۍ_موندنه_Test(کړکۍ, callback != عدم);
}

bool SDL_سېټ_کړکۍ_Shape(SDL_کړکۍ *کړکۍ, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_کړکۍ_MAGIC(کړکۍ, false);

    إذا (!(کړکۍ->flags & SDL_کړکۍ_TRANSPARENT)) {
        أرجع SDL_سېټ_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_کړکۍ_Properties(کړکۍ);
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

    إذا (!SDL_سېټ_Surface_Property(props, SDL_PROP_کړکۍ_SHAPE_اشاره_ګر, surface)) {
        أرجع false;
    }

    إذا (_this->Update_کړکۍ_Shape) {
        إذا (!_this->Update_کړکۍ_Shape(_this, کړکۍ, surface)) {
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

فراغ SDL_On_Application_Did_Receive_حافظه_Warning(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_ټیټ_حافظه);
}

فراغ SDL_OnApplicationWillEnterBackground(فراغ)
{
    إذا (_this) {
        SDL_کړکۍ *کړکۍ;
        لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_MINIMIZED, 0, 0);
        }
        SDL_سېټ_Keyboard_Focus(عدم);
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
        SDL_کړکۍ *کړکۍ;
        لكل (کړکۍ = _this->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
            SDL_سېټ_Keyboard_Focus(کړکۍ);
            SDL_Send_کړکۍ_Event(کړکۍ, SDL_EVENT_کړکۍ_RESTORED, 0, 0);
        }
    }
}

#تعریف_کړه NOT_A_VULKAN_کړکۍ "The specified window isn't a Vulkan window"

bool SDL_Vulkan_بارول_Library(ثابت حرف *لار)
{
    bool پایله;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->vulkan_config.loader_loaded) {
        إذا (لار && SDL_strcmp(لار, _this->vulkan_config.loader_لار) != 0) {
            أرجع SDL_سېټ_Error("Vulkan loader library already loaded");
        }
        پایله = true;
    } وإلا {
        إذا (!_this->Vulkan_بارول_Library) {
            أرجع SDL_DllNotSupported("Vulkan");
        }
        پایله = _this->Vulkan_بارول_Library(_this, لار);
    }
    إذا (پایله) {
        _this->vulkan_config.loader_loaded++;
    }
    أرجع پایله;
}

SDL_Function_اشاره_ګر SDL_Vulkan_GetVkGetInstanceProcAddr(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->vulkan_config.loader_loaded) {
        SDL_سېټ_Error("No Vulkan loader has been loaded");
        أرجع عدم;
    }
    أرجع (SDL_Function_اشاره_ګر)_this->vulkan_config.vkGetInstanceProcAddr;
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

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *شمېر)
{
    Uint32 tmpcount = 0;
    إذا (!شمېر) {
        شمېر = &tmpcount;
    }

    إذا (!_this->Vulkan_GetInstanceExtensions) {
        *شمېر = 0;
        SDL_Unsupported();
        أرجع عدم;
    }

    أرجع _this->Vulkan_GetInstanceExtensions(_this, شمېر);
}

bool SDL_Vulkan_CreateSurface(SDL_کړکۍ *کړکۍ,
                                  VkInstance instance,
                                  ثابت بنية Vk_ویش_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, false);

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

    إذا (!(کړکۍ->flags & SDL_کړکۍ_VULKAN)) {
        // No problem, we can convert to Vulkan
        إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
            کړکۍ->flags &= ~SDL_کړکۍ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (کړکۍ->flags & SDL_کړکۍ_METAL) {
            کړکۍ->flags &= ~SDL_کړکۍ_METAL;
            // Nothing more to do for Metal.
        }
        إذا (SDL_Vulkan_بارول_Library(عدم)) {
            کړکۍ->flags |= SDL_کړکۍ_VULKAN;
        } وإلا {
            أرجع SDL_سېټ_Error("failed to load Vulkan library");
        }
    }

    أرجع _this->Vulkan_CreateSurface(_this, کړکۍ, instance, allocator, surface);
}

فراغ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية Vk_ویش_Callbacks *allocator)
{
    إذا (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 کتار_Family_شاخص)
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
        أرجع _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, کتار_Family_شاخص);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    أرجع true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_کړکۍ *کړکۍ)
{
    CHECK_کړکۍ_MAGIC(کړکۍ, عدم);

    إذا (!_this->Metal_CreateView) {
        SDL_Unsupported();
        أرجع عدم;
    }

    إذا (!(کړکۍ->flags & SDL_کړکۍ_METAL)) {
        // No problem, we can convert to Metal
        إذا (کړکۍ->flags & SDL_کړکۍ_OPENGL) {
            کړکۍ->flags &= ~SDL_کړکۍ_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (کړکۍ->flags & SDL_کړکۍ_VULKAN) {
            کړکۍ->flags &= ~SDL_کړکۍ_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        کړکۍ->flags |= SDL_کړکۍ_METAL;
    }

    أرجع _this->Metal_CreateView(_this, کړکۍ);
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
        SDL_سېټ_Error("Metal is not supported.");
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

    حالة SDL_SYSTEM_CURSOR_پرمختګ:
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

    حالة SDL_SYSTEM_CURSOR_اشاره_ګر:
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

    حالة SDL_SYSTEM_CURSOR_ستون_RESIZE:
        أرجع "col-resize";

    حالة SDL_SYSTEM_CURSOR_لیکه_RESIZE:
        أرجع "row-resize";

    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        إذا (fallback_name) {
            *fallback_name = "move";
        }
        أرجع "all-scroll";

    حالة SDL_SYSTEM_CURSOR_ZOOM_دننه:
        أرجع "zoom-in";

    حالة SDL_SYSTEM_CURSOR_ZOOM_بهر:
        أرجع "zoom-out";

    افتراضي:
        أرجع "default";
    }
}
#د_که_پای

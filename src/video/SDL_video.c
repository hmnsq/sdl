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

#اگر_تعریف_شده SDL_VIDEO_OPENGL
#ضمن <SDL3/SDL_opengl.h>
#پایان_اگر // SDL_VIDEO_OPENGL

#إذا defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles.h>
#پایان_اگر // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#إذا defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#ضمن <SDL3/SDL_opengles2.h>
#پایان_اگر // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#اگر_تعریف_نشده GL_CONTEXT_RELEASE_BEHAVIOR
#تعریف_کن GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#پایان_اگر

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#اگر_تعریف_نشده GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#تعریف_کن GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#پایان_اگر

// This is always the same number between the various EXT/ARB/GLES extensions.
#اگر_تعریف_نشده GL_FRAMEBUFFER_SRGB
#تعریف_کن GL_FRAMEBUFFER_SRGB 0x8DB9
#پایان_اگر

#اگر_تعریف_شده SDL_PLATFORM_EMSCRIPTEN
#ضمن <emscripten.h>
#پایان_اگر

#اگر_تعریف_شده SDL_PLATFORM_3DS
#ضمن <3ds.h>
#پایان_اگر

#اگر_تعریف_نشده GL_RGBA_FLOAT_نما_ARB
#تعریف_کن GL_RGBA_FLOAT_نما_ARB 0x8820
#پایان_اگر /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ساكن VideoBootStrap *bootstrap[] = {
#اگر_تعریف_شده SDL_VIDEO_DRIVER_خصوصی
    &خصوصی_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#پایان_اگر
    &X11_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#اگر_تعریف_شده SDL_درون_داد_LINUXEV
    &DUMMY_evdev_bootstrap,
#پایان_اگر
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#پایان_اگر
    عدم
};

#تعریف_کن CHECK_پنجره_MAGIC(پنجره, نتیجه)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        أرجع نتیجه;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(پنجره, SDL_OBJECT_TYPE_پنجره)) {     \
        SDL_مجموعه_Error("Invalid window");                                 \
        أرجع نتیجه;                                                  \
    }

#تعریف_کن CHECK_DISPLAY_MAGIC(display, نتیجه)                            \
    CHECK_PARAM(!display) {                                             \
        أرجع نتیجه;                                                  \
    }                                                                   \

#تعریف_کن CHECK_پنجره_NOT_POPUP(پنجره, نتیجه)                          \
    CHECK_PARAM(SDL_پنجره_IS_POPUP(پنجره)) {                          \
        SDL_مجموعه_Error("Operation invalid on popup windows");             \
        أرجع نتیجه;                                                  \
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
خارجي bool Cocoa_Is_پنجره_درون_Fullscreen_Space(SDL_پنجره *پنجره);
خارجي bool Cocoa_Is_پنجره_درون_Fullscreen_Space_Transition(SDL_پنجره *پنجره);
خارجي bool Cocoa_مجموعه_پنجره_Fullscreen_Space(SDL_پنجره *پنجره, bool state, bool blocking);
خارجي bool Cocoa_IsShowingModalDialog(SDL_پنجره *پنجره);
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_UIKIT
خارجي فراغ SDL_UpdateLifecycleObserver(فراغ);
#پایان_اگر

ساكن فراغ SDL_Check_پنجره_Display_تغییریافته(SDL_پنجره *پنجره);
ساكن فراغ SDL_Check_پنجره_Display_Scale_تغییریافته(SDL_پنجره *پنجره);
ساكن فراغ SDL_Check_پنجره_امن_Area_تغییریافته(SDL_پنجره *پنجره);

// Convenience functions for reading driver flags
ساكن bool SDL_نما_Switching_Emulated(SDL_VideoDevice *_this)
{
    إذا (_this->device_caps & VIDEO_DEVICE_CAPS_نما_SWITCHING_EMULATED) {
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

ساكن فراغ SDL_SyncHintWatcher(فراغ *userdata, ثابت حرف *name, ثابت حرف *old_مقدار, ثابت حرف *new_مقدار)
{
    syncHint = SDL_GetStringBoolean(new_مقدار, false);
}

ساكن فراغ SDL_SyncIfRequired(SDL_پنجره *پنجره)
{
    إذا (syncHint) {
        SDL_Sync_پنجره(پنجره);
    }
}

ساكن فراغ SDL_Update_پنجره_Hierarchy(SDL_پنجره *پنجره, SDL_پنجره *والد)
{
    // Unlink the window from the existing parent.
    إذا (پنجره->والد) {
        إذا (پنجره->بعدی_sibling) {
            پنجره->بعدی_sibling->prev_sibling = پنجره->prev_sibling;
        }
        إذا (پنجره->prev_sibling) {
            پنجره->prev_sibling->بعدی_sibling = پنجره->بعدی_sibling;
        } وإلا {
            پنجره->والد->اولی_فرزند = پنجره->بعدی_sibling;
        }

        پنجره->والد = عدم;
    }

    إذا (والد) {
        پنجره->والد = والد;

        پنجره->بعدی_sibling = والد->اولی_فرزند;
        إذا (والد->اولی_فرزند) {
            والد->اولی_فرزند->prev_sibling = پنجره;
        }
        والد->اولی_فرزند = پنجره;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#تعریف_کن SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر "SDL.internal.window.texturedata"

تعريفنوع بنية
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    فراغ *pixels;
    صحيح pitch;
    صحيح بایتها_در_هر_pixel;
} SDL_پنجره_Texture_داده;

ساكن Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#إذا (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !هدف_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    إذا (_this->GL_CreateContext) {
        أرجع SDL_پنجره_OPENGL;
    }
#پایان_اگر
#إذا defined(SDL_VIDEO_METAL) && (هدف_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    إذا (_this->Metal_CreateView) {
        أرجع SDL_پنجره_METAL;
    }
#پایان_اگر
#إذا defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    إذا (SDL_strcmp(_this->name, "openvr") == 0) {
        أرجع SDL_پنجره_OPENGL;
    }
#پایان_اگر
    أرجع 0;
}

ساكن bool SDL_Create_پنجره_Texture(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PixelFormat *format, فراغ **pixels, صحيح *pitch)
{
    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
    SDL_پنجره_Texture_داده *داده = (SDL_پنجره_Texture_داده *)SDL_Get_اشاره_گر_Property(props, SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر, عدم);
    ثابت bool transparent = (پنجره->flags & SDL_پنجره_TRANSPARENT) ? true : false;
    صحيح i;
    صحيح w, h;
    ثابت SDL_PixelFormat *texture_formats;

    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &w, &h);

    إذا (!داده) {
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
            renderer = SDL_CreateRenderer(پنجره, render_driver);
            SDL_free(render_driver_copy);
            إذا (!renderer) {
                // The error for this specific renderer has already been set
                أرجع false;
            }
        } وإلا {
            SDL_assert(render_driver_copy == عدم);
            ثابت صحيح مجموع = SDL_Get_رقم_Render_Drivers();
            لكل (i = 0; i < مجموع; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                إذا (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(پنجره, name);
                    إذا (renderer) {
                        اكسر; // this will work.
                    }
                }
            }
            إذا (!renderer) {
                أرجع SDL_مجموعه_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != عدم); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        داده = (SDL_پنجره_Texture_داده *)SDL_calloc(1, حجم(*داده));
        إذا (!داده) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }
        إذا (!SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر, داده)) {
            SDL_DestroyRenderer(renderer);
            أرجع false;
        }

        داده->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_Get_اشاره_گر_Property(SDL_GetRendererProperties(داده->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_اشاره_گر, عدم);
    إذا (!texture_formats) {
        أرجع false;
    }

    // Free any old texture and pixel data
    إذا (داده->texture) {
        SDL_DestroyTexture(داده->texture);
        داده->texture = عدم;
    }
    SDL_free(داده->pixels);
    داده->pixels = عدم;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    لكل (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        إذا (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10_بیت(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_نمایهای(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            اكسر;
        }
    }

    داده->texture = SDL_CreateTexture(داده->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    إذا (!داده->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        أرجع false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_مجموعه_Texture_Blend_نما(داده->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    داده->بایتها_در_هر_pixel = SDL_BYTESPERPIXEL(*format);
    داده->pitch = (((w * داده->بایتها_در_هر_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * داده->pitch;
        داده->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        إذا (!داده->pixels) {
            أرجع false;
        }
    }

    *pixels = داده->pixels;
    *pitch = داده->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_مجموعه_Render_Viewport(داده->renderer, عدم);

    أرجع true;
}

bool SDL_مجموعه_پنجره_Texture_VSync(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح vsync)
{
    SDL_پنجره_Texture_داده *داده;

    داده = (SDL_پنجره_Texture_داده *)SDL_Get_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر, عدم);
    إذا (!داده) {
        أرجع false;
    }
    إذا (!داده->renderer) {
        أرجع false;
    }
    أرجع SDL_مجموعه_Render_VSync(داده->renderer, vsync);
}

ساكن bool SDL_Get_پنجره_Texture_VSync(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *vsync)
{
    SDL_پنجره_Texture_داده *داده;

    داده = (SDL_پنجره_Texture_داده *)SDL_Get_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر, عدم);
    إذا (!داده) {
        أرجع false;
    }
    إذا (!داده->renderer) {
        أرجع false;
    }
    أرجع SDL_GetRenderVSync(داده->renderer, vsync);
}

ساكن bool SDL_Update_پنجره_Texture(SDL_VideoDevice *_this, SDL_پنجره *پنجره, ثابت SDL_Rect *rects, صحيح numrects)
{
    SDL_پنجره_Texture_داده *داده;
    SDL_Rect rect;
    فراغ *src;
    صحيح w, h;

    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &w, &h);

    داده = (SDL_پنجره_Texture_داده *)SDL_Get_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر, عدم);
    إذا (!داده || !داده->texture) {
        أرجع SDL_مجموعه_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    إذا (SDL_Get_بازه_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (فراغ *)((Uint8 *)داده->pixels +
                       rect.y * داده->pitch +
                       rect.x * داده->بایتها_در_هر_pixel);
        إذا (!SDL_UpdateTexture(داده->texture, &rect, src, داده->pitch)) {
            أرجع false;
        }

        إذا (!SDL_RenderTexture(داده->renderer, داده->texture, عدم, عدم)) {
            أرجع false;
        }

        SDL_RenderPresent(داده->renderer);
    }
    أرجع true;
}

ساكن فراغ SDL_Destroy_پنجره_Texture(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
    إذا (SDL_HasProperty(props, SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر)) {
        SDL_پنجره_Texture_داده *داده = SDL_Get_اشاره_گر_Property(props, SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر, عدم);

        إذا (داده->texture) {
            SDL_DestroyTexture(داده->texture);
        }
        إذا (داده->renderer) {
            SDL_DestroyRenderer(داده->renderer);
        }
        SDL_free(داده->pixels);
        SDL_free(داده);

        SDL_ClearProperty(props, SDL_PROP_پنجره_TEXTUREDATA_اشاره_گر);
    }
}

ساكن SDL_VideoDevice *_this = عدم;
ساكن SDL_AtomicInt SDL_messagebox_شمار;

ساكن صحيح SDLCALL cmpmodes(ثابت فراغ *A, ثابت فراغ *B)
{
    ثابت SDL_Display_نما *a = (ثابت SDL_Display_نما *)A;
    ثابت SDL_Display_نما *b = (ثابت SDL_Display_نما *)B;
    صحيح a_refresh_نرخ = (صحيح)(a->refresh_نرخ * 100);
    صحيح b_refresh_نرخ = (صحيح)(b->refresh_نرخ * 100);
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
    } وإلا إذا (a_refresh_نرخ != b_refresh_نرخ) {
        أرجع b_refresh_نرخ - a_refresh_نرخ;
    } وإلا إذا (a_pixel_density != b_pixel_density) {
        أرجع a_pixel_density - b_pixel_density;
    }
    أرجع 0;
}

bool SDL_UninitializedVideo(فراغ)
{
    أرجع SDL_مجموعه_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ساكن ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحيح SDL_Get_رقم_Video_Drivers(فراغ)
{
    ساكن صحيح رقم_drivers = -1;

    إذا (رقم_drivers >= 0) {
        أرجع رقم_drivers;
    }

    رقم_drivers = 0;

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
            deduped_bootstrap[رقم_drivers++] = bootstrap[i];
        }
    }

    أرجع رقم_drivers;
}

ثابت حرف *SDL_GetVideoDriver(صحيح شاخص)
{
    CHECK_PARAM(شاخص < 0 || شاخص >= SDL_Get_رقم_Video_Drivers()) {
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
#اگر_تعریف_شده SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    إذا (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#پایان_اگر
    إذا (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    إذا (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        طالما (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_انتها = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_انتها) ? (driver_attempt_انتها - driver_attempt)
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

            driver_attempt = (driver_attempt_انتها) ? (driver_attempt_انتها + 1) : عدم;
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
            SDL_مجموعه_Error("%s not available", driver_name);
            اذهب pre_driver_error;
        }
        SDL_مجموعه_Error("No available video device");
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
    SDL_GL_Reset_صفات();

    // Initialize the video subsystem
    إذا (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        أرجع false;
    }

    // Make sure some displays were added
    إذا (_this->رقم_displays == 0) {
        SDL_QuitVideo();
        أرجع SDL_مجموعه_Error("The video driver did not add any displays");
    }

    SDL_جمع_کن_Hint_Callback(SDL_HINT_VIDEO_SYNC_پنجره_OPERATIONS, SDL_SyncHintWatcher, عدم);

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

فراغ SDL_مجموعه_System_Theme(SDL_SystemTheme theme)
{
    إذا (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_تغییریافته_Event();
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

ساكن فراغ SDL_Finalize_Display_نما(SDL_Display_نما *نما)
{
    // Make sure all the fields are set up correctly
    إذا (نما->pixel_density <= 0.0f) {
        نما->pixel_density = 1.0f;
    }

    إذا (نما->refresh_نرخ_numerator > 0) {
        إذا (نما->refresh_نرخ_denominator <= 0) {
            نما->refresh_نرخ_denominator = 1;
        }
        نما->refresh_نرخ = (عائم)نما->refresh_نرخ_numerator / نما->refresh_نرخ_denominator;
    } وإلا {
        SDL_CalculateFraction(نما->refresh_نرخ, &نما->refresh_نرخ_numerator, &نما->refresh_نرخ_denominator);
    }
    نما->refresh_نرخ = SDL_roundf(نما->refresh_نرخ * 100) / 100.0f;
}

SDL_DisplayID SDL_جمع_کن_Basic_Video_Display(ثابت SDL_Display_نما *desktop_نما)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    إذا (desktop_نما) {
        SDL_memcpy(&display.desktop_نما, desktop_نما, حجم(display.desktop_نما));
    }
    أرجع SDL_جمع_کن_Video_Display(&display, false);
}

SDL_DisplayID SDL_جمع_کن_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحيح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(حجم(*new_display));
    إذا (!new_display) {
        أرجع 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->رقم_displays + 1) * حجم(*displays));
    إذا (!displays) {
        SDL_free(new_display);
        أرجع 0;
    }
    _this->displays = displays;
    _this->displays[_this->رقم_displays++] = new_display;

    id = SDL_Get_بعدی_Object_ID();
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

    new_display->desktop_نما.displayID = id;
    new_display->current_نما = &new_display->desktop_نما;
    SDL_Finalize_Display_نما(&new_display->desktop_نما);

    لكل (i = 0; i < new_display->رقم_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_مجموعه_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    إذا (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    أرجع id;
}

فراغ SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_پنجره *پنجره;

    // See if any windows have changed to the new display
    لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
        SDL_Check_پنجره_Display_تغییریافته(پنجره);
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
    SDL_free(display->desktop_نما.داخلی);
    display->desktop_نما.داخلی = عدم;
    SDL_free(display->داخلی);
    display->داخلی = عدم;
    SDL_free(display);

    إذا (display_شاخص < (_this->رقم_displays - 1)) {
        SDL_memmove(&_this->displays[display_شاخص], &_this->displays[display_شاخص + 1], (_this->رقم_displays - display_شاخص - 1) * حجم(_this->displays[display_شاخص]));
    }
    --_this->رقم_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحيح *شمار)
{
    صحيح i;
    SDL_DisplayID *displays;

    إذا (!_this) {
        إذا (شمار) {
            *شمار = 0;
        }

        SDL_UninitializedVideo();
        أرجع عدم;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->رقم_displays + 1) * حجم(*displays));
    إذا (displays) {
        إذا (شمار) {
            *شمار = _this->رقم_displays;
        }

        لكل (i = 0; i < _this->رقم_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } وإلا {
        إذا (شمار) {
            *شمار = 0;
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

ساكن SDL_DisplayID Get_Display_For_پنجره(SDL_پنجره *پنجره)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        displayID = پنجره->current_fullscreen_نما.displayID;
    }

    إذا (!displayID) {
        displayID = SDL_Get_Display_For_پنجره_Position(پنجره);
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, 0);

    أرجع SDL_GetVideoDisplay(Get_Display_For_پنجره(پنجره));
}

SDL_DisplayID SDL_GetPrimaryDisplay(فراغ)
{
    إذا (!_this || _this->رقم_displays == 0) {
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

    لكل (display_شاخص = 0; display_شاخص < _this->رقم_displays; ++display_شاخص) {
        إذا (displayID == _this->displays[display_شاخص]->id) {
            أرجع display_شاخص;
        }
    }
    SDL_مجموعه_Error("Invalid display");
    أرجع -1;
}

SDL_Display_داده *SDL_Get_Display_Driver_داده(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->داخلی;
}

SDL_Display_داده *SDL_Get_Display_Driver_داده_For_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, 0);

    أرجع SDL_Get_Display_Driver_داده(Get_Display_For_پنجره(پنجره));
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
    rect->w = display->current_نما->w;
    rect->h = display->current_نما->h;
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

فراغ SDL_مجموعه_Display_Content_Scale(SDL_VideoDisplay *display, عائم scale)
{
    إذا (scale != display->content_scale) {
        SDL_پنجره *پنجره;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_تغییریافته, 0, 0);

        // Check the windows on this display
        لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
            إذا (display->id == پنجره->displayID) {
                SDL_Check_پنجره_Display_Scale_تغییریافته(پنجره);
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

فراغ SDL_مجموعه_پنجره_HDRProperties(SDL_پنجره *پنجره, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    إذا (پنجره->HDR.HDR_headroom != HDR_clamped.HDR_headroom || پنجره->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID پنجره_props = SDL_Get_پنجره_Properties(پنجره);

        SDL_مجموعه_Float_Property(پنجره_props, SDL_PROP_پنجره_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_مجموعه_Float_Property(پنجره_props, SDL_PROP_پنجره_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_مجموعه_Boolean_Property(پنجره_props, SDL_PROP_پنجره_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&پنجره->HDR, &HDR_clamped);

        إذا (send_event) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_HDR_STATE_تغییریافته, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

فراغ SDL_مجموعه_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ثابت bool تغییریافته = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	إذا (تغییریافته) {
		SDL_مجموعه_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    إذا (تغییریافته && !SDL_DriverSendsHDRChanges(_this)) {
        لكل (SDL_پنجره *w = display->device->windows; w; w = w->بعدی) {
            إذا (Get_Display_For_پنجره(w) == display->id) {
                SDL_مجموعه_پنجره_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ساكن فراغ SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    إذا (display->رقم_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ساكن ثابت SDL_Display_نما *SDL_Get_Fullscreen_نما_تطابق(ثابت SDL_Display_نما *نما)
{
    SDL_VideoDisplay *display;
    SDL_Display_نما fullscreen_نما;

    إذا (نما->w <= 0 || نما->h <= 0) {
        // Use the desktop mode
        أرجع عدم;
    }

    SDL_memcpy(&fullscreen_نما, نما, حجم(fullscreen_نما));
    إذا (fullscreen_نما.displayID == 0) {
        fullscreen_نما.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_نما(&fullscreen_نما);

    نما = عدم;

    display = SDL_GetVideoDisplay(fullscreen_نما.displayID);
    إذا (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        إذا (!نما) {
            لكل (صحيح i = 0; i < display->رقم_fullscreen_modes; ++i) {
                إذا (SDL_memcmp(&fullscreen_نما, &display->fullscreen_modes[i], حجم(fullscreen_نما)) == 0) {
                    نما = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }

        // Search for a mode with the same characteristics
        إذا (!نما) {
            لكل (صحيح i = 0; i < display->رقم_fullscreen_modes; ++i) {
                إذا (cmpmodes(&fullscreen_نما, &display->fullscreen_modes[i]) == 0) {
                    نما = &display->fullscreen_modes[i];
                    اكسر;
                }
            }
        }
    }
    أرجع نما;
}

bool SDL_جمع_کن_Fullscreen_Display_نما(SDL_VideoDisplay *display, ثابت SDL_Display_نما *نما)
{
    SDL_Display_نما *modes;
    SDL_Display_نما new_نما;
    صحيح i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_نما, نما, حجم(new_نما));
    new_نما.displayID = display->id;
    SDL_Finalize_Display_نما(&new_نما);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->رقم_fullscreen_modes;
    لكل (i = 0; i < nmodes; ++i) {
        إذا (cmpmodes(&new_نما, &modes[i]) == 0) {
            أرجع false;
        }
    }

    // Go ahead and add the new mode
    إذا (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_نما *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        إذا (!modes) {
            أرجع false;
        }

        إذا (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            لكل (i = 0; i < nmodes; ++i) {
                إذا (display->current_نما == &display->fullscreen_modes[i]) {
                    display->current_نما = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->رقم_fullscreen_modes++], &new_نما, حجم(new_نما));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->رقم_fullscreen_modes,
              حجم(SDL_Display_نما), cmpmodes);

    أرجع true;
}

فراغ SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحيح i;

    لكل (i = display->رقم_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].داخلی);
        display->fullscreen_modes[i].داخلی = عدم;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = عدم;
    display->رقم_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_نما = &display->desktop_نما;
}

SDL_Display_نما **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحيح *شمار)
{
    صحيح i;
    صحيح رقم_modes;
    SDL_Display_نما **نتیجه;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    إذا (شمار) {
        *شمار = 0;
    }

    CHECK_DISPLAY_MAGIC(display, عدم);

    SDL_UpdateFullscreenDisplayModes(display);

    رقم_modes = display->رقم_fullscreen_modes;
    نتیجه = (SDL_Display_نما **)SDL_malloc((رقم_modes + 1) * حجم(*نتیجه) + رقم_modes * حجم(**نتیجه));
    إذا (نتیجه) {
        SDL_Display_نما *modes = (SDL_Display_نما *)((Uint8 *)نتیجه + ((رقم_modes + 1) * حجم(*نتیجه)));
        إذا (رقم_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, رقم_modes * حجم(*modes));
        }
        لكل (i = 0; i < رقم_modes; ++i) {
            نتیجه[i] = modes++;
        }
        نتیجه[i] = عدم;

        إذا (شمار) {
            *شمار = رقم_modes;
        }
    } وإلا {
        إذا (شمار) {
            *شمار = 0;
        }
    }
    أرجع نتیجه;
}

bool SDL_Get_Closest_Fullscreen_Display_نما(SDL_DisplayID displayID, صحيح w, صحيح h, عائم refresh_نرخ, bool include_بالا_density_modes, SDL_Display_نما *نتیجه)
{
    CHECK_PARAM(!نتیجه) {
        أرجع SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_Display_نما *نما, *closest = عدم;
    عائم aspect_نسبت;
    صحيح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(نتیجه);

    CHECK_DISPLAY_MAGIC(display, false);

    إذا (h > 0) {
        aspect_نسبت = (عائم)w / h;
    } وإلا {
        aspect_نسبت = 1.0f;
    }

    إذا (refresh_نرخ == 0.0f) {
        refresh_نرخ = display->desktop_نما.refresh_نرخ;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    لكل (i = 0; i < display->رقم_fullscreen_modes; ++i) {
        نما = &display->fullscreen_modes[i];

        إذا (w > نما->w) {
            // Out of sorted modes large enough here
            اكسر;
        }
        إذا (h > نما->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            استمر;
        }
        إذا (نما->pixel_density > 1.0f && !include_بالا_density_modes) {
            استمر;
        }
        إذا (closest) {
            عائم current_aspect_نسبت = (عائم)نما->w / نما->h;
            عائم closest_aspect_نسبت = (عائم)closest->w / closest->h;
            إذا (SDL_fabsf(aspect_نسبت - closest_aspect_نسبت) < SDL_fabsf(aspect_نسبت - current_aspect_نسبت)) {
                // The mode we already found has a better aspect ratio match
                استمر;
            }

            إذا (نما->w == closest->w && نما->h == closest->h) {
                إذا (SDL_fabsf(closest->refresh_نرخ - refresh_نرخ) < SDL_fabsf(نما->refresh_نرخ - refresh_نرخ)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    استمر;
                }
                إذا (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(نما->format)) {
                    // Prefer the highest color depth
                    استمر;
                }
            }
        }

        closest = نما;
    }
    إذا (!closest) {
        أرجع SDL_مجموعه_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(نتیجه, closest);

    أرجع true;
}

ساكن bool Display_نما_تغییریافته(ثابت SDL_Display_نما *old_نما, ثابت SDL_Display_نما *new_نما)
{
    أرجع ((old_نما->displayID && old_نما->displayID != new_نما->displayID) ||
            (old_نما->format && old_نما->format != new_نما->format) ||
            (old_نما->w && old_نما->h && (old_نما->w != new_نما->w ||old_نما->h != new_نما->h)) ||
            (old_نما->pixel_density != 0.0f && old_نما->pixel_density != new_نما->pixel_density) ||
            (old_نما->refresh_نرخ != 0.0f && old_نما->refresh_نرخ != new_نما->refresh_نرخ));
}

فراغ SDL_مجموعه_Desktop_Display_نما(SDL_VideoDisplay *display, ثابت SDL_Display_نما *نما)
{
    SDL_Display_نما آخرین_نما;

    إذا (display->fullscreen_فعال) {
        // This is a temporary mode change, don't save the desktop mode
        أرجع;
    }

    SDL_copyp(&آخرین_نما, &display->desktop_نما);

    SDL_free(display->desktop_نما.داخلی);
    SDL_copyp(&display->desktop_نما, نما);
    display->desktop_نما.displayID = display->id;
    SDL_Finalize_Display_نما(&display->desktop_نما);

    إذا (Display_نما_تغییریافته(&آخرین_نما, &display->desktop_نما)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_نما_تغییریافته, نما->w, نما->h);
        إذا (display->current_نما == &display->desktop_نما) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_نما_تغییریافته, نما->w, نما->h);
        }
    }
}

ثابت SDL_Display_نما *SDL_Get_Desktop_Display_نما(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع &display->desktop_نما;
}

فراغ SDL_مجموعه_Current_Display_نما(SDL_VideoDisplay *display, ثابت SDL_Display_نما *نما)
{
    SDL_Display_نما آخرین_نما;

    إذا (display->current_نما) {
        SDL_copyp(&آخرین_نما, display->current_نما);
    } وإلا {
        SDL_zero(آخرین_نما);
    }

    display->current_نما = نما;

    إذا (Display_نما_تغییریافته(&آخرین_نما, نما)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_نما_تغییریافته, نما->w, نما->h);
    }
}

ثابت SDL_Display_نما *SDL_Get_Current_Display_نما(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, عدم);

    أرجع display->current_نما;
}

bool SDL_مجموعه_Display_نما_For_Display(SDL_VideoDisplay *display, SDL_Display_نما *نما)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    إذا (SDL_نما_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        أرجع true;
    }

    إذا (!نما) {
        نما = &display->desktop_نما;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#اگر_تعریف_نشده SDL_PLATFORM_RISCOS
    إذا (نما == display->current_نما) {
        أرجع true;
    }
#پایان_اگر

    // Actually change the display mode
    إذا (_this->مجموعه_Display_نما) {
        bool نتیجه;

        _this->setting_display_نما = true;
        نتیجه = _this->مجموعه_Display_نما(_this, display, نما);
        _this->setting_display_نما = false;
        إذا (!نتیجه) {
            أرجع false;
        }
    }

    SDL_مجموعه_Current_Display_نما(display, نما);

    أرجع true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساكن فراغ SDL_Get_Closest_نقطه_On_Rect(ثابت SDL_Rect *rect, SDL_نقطه *نقطه)
{
    ثابت صحيح راست = rect->x + rect->w - 1;
    ثابت صحيح bottom = rect->y + rect->h - 1;

    إذا (نقطه->x < rect->x) {
        نقطه->x = rect->x;
    } وإلا إذا (نقطه->x > راست) {
        نقطه->x = راست;
    }

    إذا (نقطه->y < rect->y) {
        نقطه->y = rect->y;
    } وإلا إذا (نقطه->y > bottom) {
        نقطه->y = bottom;
    }
}

ساكن SDL_DisplayID GetDisplayForRect(صحيح x, صحيح y, صحيح w, صحيح h)
{
    صحيح i, dist;
    SDL_DisplayID closest = 0;
    صحيح closest_dist = 0x7FFFFFFF;
    SDL_نقطه closest_نقطه_on_display;
    SDL_نقطه delta;
    SDL_نقطه center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    إذا (_this) {
        لكل (i = 0; i < _this->رقم_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            إذا (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, عدم)) {
                أرجع display->id;
            }

            // Snap window center to the display rect
            closest_نقطه_on_display = center;
            SDL_Get_Closest_نقطه_On_Rect(&display_rect, &closest_نقطه_on_display);

            delta.x = center.x - closest_نقطه_on_display.x;
            delta.y = center.y - closest_نقطه_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            إذا (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    إذا (closest == 0) {
        SDL_مجموعه_Error("Couldn't find any displays");
    }

    أرجع closest;
}

فراغ SDL_Relative_مقصد_Global_For_پنجره(SDL_پنجره *پنجره, صحيح rel_x, صحيح rel_y, صحيح *abs_x, صحيح *abs_y)
{
    SDL_پنجره *w;

    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        // Calculate the total offset of the popup from the parents
        لكل (w = پنجره->والد; w; w = w->والد) {
            rel_x += w->x;
            rel_y += w->y;

            إذا (!SDL_پنجره_IS_POPUP(w)) {
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

فراغ SDL_Global_مقصد_Relative_For_پنجره(SDL_پنجره *پنجره, صحيح abs_x, صحيح abs_y, صحيح *rel_x, صحيح *rel_y)
{
    SDL_پنجره *w;

    إذا (SDL_پنجره_IS_POPUP(پنجره)) {
        // Convert absolute window coordinates to relative for a popup
        لكل (w = پنجره->والد; w; w = w->والد) {
            abs_x -= w->x;
            abs_y -= w->y;

            إذا (!SDL_پنجره_IS_POPUP(w)) {
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

SDL_DisplayID SDL_Get_Display_For_نقطه(ثابت SDL_نقطه *نقطه)
{
    CHECK_PARAM(!نقطه) {
        SDL_InvalidParamError("point");
        أرجع 0;
    }

    أرجع GetDisplayForRect(نقطه->x, نقطه->y, 1, 1);
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
    لكل (صحيح i = 0; i < _this->رقم_displays; ++i) {
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

SDL_DisplayID SDL_Get_Display_For_پنجره_Position(SDL_پنجره *پنجره)
{
    صحيح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_پنجره_MAGIC(پنجره, 0);

    إذا (_this->Get_Display_For_پنجره) {
        displayID = _this->Get_Display_For_پنجره(_this, پنجره);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_مقصد_Global_For_پنجره(پنجره, پنجره->x, پنجره->y, &x, &y);

    إذا (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } وإلا {
            displayID = GetDisplayForRect(x, y, پنجره->w, پنجره->h);
        }
    }
    إذا (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    أرجع displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_پنجره(SDL_پنجره *پنجره)
{
    SDL_DisplayID displayID = 0;

    CHECK_پنجره_MAGIC(پنجره, عدم);

    // An explicit fullscreen display overrides all
    إذا (پنجره->current_fullscreen_نما.displayID) {
        displayID = پنجره->current_fullscreen_نما.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    إذا (!displayID) {
        displayID = پنجره->pending_displayID;
    }
    إذا (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحيح x = پنجره->آخرین_position_pending ? پنجره->pending.x : پنجره->x;
        ثابت صحيح y = پنجره->آخرین_position_pending ? پنجره->pending.y : پنجره->y;
        ثابت صحيح w = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : پنجره->w;
        ثابت صحيح h = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : پنجره->h;

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

#تعریف_کن SDL_PROP_SDL2_COMPAT_پنجره_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID پنجره_props = SDL_Get_پنجره_Properties(پنجره);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_پنجره(پنجره);
    إذا (fs_display) {
        SDL_مجموعه_عدد_Property(پنجره_props, SDL_PROP_SDL2_COMPAT_پنجره_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } وإلا {
        SDL_ClearProperty(پنجره_props, SDL_PROP_SDL2_COMPAT_پنجره_PREFERRED_FULLSCREEN_DISPLAY);
    }

    أرجع Get_Display_For_پنجره(پنجره);
}

ساكن فراغ SDL_Check_پنجره_Display_تغییریافته(SDL_پنجره *پنجره)
{
    إذا (SDL_SendsDisplayChanges(_this)) {
        أرجع;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_پنجره_Position(پنجره);

    إذا (displayID != پنجره->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect پنجره_rect;
        SDL_Rect old_overlap, new_overlap;

        إذا (SDL_GetDisplayBounds(پنجره->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            پنجره_rect.x = پنجره->x;
            پنجره_rect.y = پنجره->y;
            پنجره_rect.w = پنجره->w;
            پنجره_rect.h = پنجره->h;

            إذا (SDL_GetRectIntersection(&old_bounds, &پنجره_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &پنجره_rect, &new_overlap)) {
                صحيح old_area = old_overlap.w * old_overlap.h;
                صحيح new_area = new_overlap.w * new_overlap.h;
                عائم new_overlap_نسبت = (new_area / ((عائم)old_area + new_area));
                إذا (new_overlap_نسبت < 0.80) {
                    أرجع;
                }
            }
        }
    }

    إذا (displayID != پنجره->displayID) {
        صحيح i, display_شاخص;

        // Sanity check our fullscreen windows
        display_شاخص = SDL_Get_Display_شاخص(displayID);
        لكل (i = 0; i < _this->رقم_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            إذا (display->fullscreen_پنجره == پنجره) {
                إذا (display_شاخص != i) {
                    إذا (display_شاخص < 0) {
                        display_شاخص = i;
                    } وإلا {
                        SDL_VideoDisplay *new_display = _this->displays[display_شاخص];

                        // The window was moved to a different display
                        إذا (new_display->fullscreen_پنجره &&
                            new_display->fullscreen_پنجره != پنجره) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_پنجره(new_display->fullscreen_پنجره);
                        }
                        new_display->fullscreen_پنجره = پنجره;
                        display->fullscreen_پنجره = عدم;
                    }
                }
                اكسر;
            }
        }

        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_DISPLAY_تغییریافته, (صحيح)displayID, 0);
    }
}

عائم SDL_Get_پنجره_Pixel_Density(SDL_پنجره *پنجره)
{
    صحيح پنجره_w, پنجره_h, pixel_w, pixel_h;
    عائم pixel_density = 1.0f;

    CHECK_پنجره_MAGIC(پنجره, 0.0f);

    إذا (SDL_Get_پنجره_اندازه(پنجره, &پنجره_w, &پنجره_h) &&
        SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &pixel_w, &pixel_h)) {
        pixel_density = (عائم)pixel_w / پنجره_w;
    }
    أرجع pixel_density;
}

عائم SDL_Get_پنجره_Display_Scale(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, 0.0f);

    أرجع پنجره->display_scale;
}

ساكن فراغ SDL_Check_پنجره_Display_Scale_تغییریافته(SDL_پنجره *پنجره)
{
    عائم display_scale;

    إذا (_this->Get_پنجره_Content_Scale) {
        display_scale = _this->Get_پنجره_Content_Scale(_this, پنجره);
    } وإلا {
        ثابت عائم pixel_density = SDL_Get_پنجره_Pixel_Density(پنجره);
        ثابت عائم content_scale = SDL_GetDisplayContentScale(پنجره->displayID);

        display_scale = pixel_density * content_scale;
    }

    إذا (display_scale != پنجره->display_scale) {
        پنجره->display_scale = display_scale;
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_DISPLAY_SCALE_تغییریافته, 0, 0);
    }
}

bool SDL_Update_Fullscreen_نما(SDL_پنجره *پنجره, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = عدم;
    SDL_Display_نما *نما = عدم;
    صحيح i;

    CHECK_پنجره_MAGIC(پنجره, false);

    پنجره->fullscreen_exclusive = false;
    پنجره->update_fullscreen_on_display_تغییریافته = false;

    // If we are in the process of hiding don't go back to fullscreen
    إذا (پنجره->is_destroying || پنجره->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    إذا (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_پنجره(پنجره);
        إذا (!display) {
            // This should never happen, but it did...
            اذهب انجامشده;
        }
    } وإلا {
        لكل (i = 0; i < _this->رقم_displays; ++i) {
            display = _this->displays[i];
            إذا (display->fullscreen_پنجره == پنجره) {
                اكسر;
            }
        }
        إذا (!display || i == _this->رقم_displays) {
            // Already not fullscreen on any display
            display = عدم;
        }
    }

    إذا (fullscreen) {
        نما = (SDL_Display_نما *)SDL_Get_پنجره_Fullscreen_نما(پنجره);
        إذا (نما) {
            پنجره->fullscreen_exclusive = true;
        } وإلا {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(پنجره->current_fullscreen_نما);
        }
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (پنجره->is_destroying && !پنجره->آخرین_fullscreen_exclusive_display) {
            پنجره->fullscreen_exclusive = false;
            إذا (display) {
                display->fullscreen_پنجره = عدم;
            }
            اذهب انجامشده;
        }
        إذا (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            إذا (fullscreen && Cocoa_Is_پنجره_درون_Fullscreen_Space(پنجره) && !پنجره->آخرین_fullscreen_exclusive_display && پنجره->fullscreen_exclusive) {
                إذا (!Cocoa_مجموعه_پنجره_Fullscreen_Space(پنجره, false, true)) {
                    اذهب error;
                }
            } وإلا إذا (fullscreen && پنجره->آخرین_fullscreen_exclusive_display && !پنجره->fullscreen_exclusive) {
                لكل (i = 0; i < _this->رقم_displays; ++i) {
                    SDL_VideoDisplay *آخرین_display = _this->displays[i];
                    إذا (آخرین_display->fullscreen_پنجره == پنجره) {
                        SDL_مجموعه_Display_نما_For_Display(آخرین_display, عدم);
                        إذا (_this->مجموعه_پنجره_Fullscreen) {
                            _this->مجموعه_پنجره_Fullscreen(_this, پنجره, آخرین_display, false);
                        }
                        آخرین_display->fullscreen_پنجره = عدم;
                    }
                }
            }

            إذا (Cocoa_مجموعه_پنجره_Fullscreen_Space(پنجره, !!fullscreen, syncHint)) {
                اذهب انجامشده;
            }
        }
    }
#پایان_اگر

    إذا (display) {
        // Restore the video mode on other displays if needed
        لكل (i = 0; i < _this->رقم_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            إذا (other != display && other->fullscreen_پنجره == پنجره) {
                SDL_مجموعه_Display_نما_For_Display(other, عدم);
                other->fullscreen_پنجره = عدم;
            }
        }
    }

    إذا (fullscreen) {
        صحيح نما_w = 0, نما_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        إذا (display->fullscreen_پنجره &&
            display->fullscreen_پنجره != پنجره) {
            SDL_Minimize_پنجره(display->fullscreen_پنجره);
        }

        display->fullscreen_فعال = پنجره->fullscreen_exclusive;

        إذا (!SDL_مجموعه_Display_نما_For_Display(display, نما)) {
            اذهب error;
        }
        إذا (commit) {
            SDL_Fullscreen_نتیجه ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->مجموعه_پنجره_Fullscreen) {
                ret = _this->مجموعه_پنجره_Fullscreen(_this, پنجره, display, fullscreen);
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
                    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_ENTER_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_فعال = false;
                اذهب error;
            }
        }

        إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
            display->fullscreen_پنجره = پنجره;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                إذا (نما) {
                    نما_w = نما->w;
                    نما_h = نما->h;
                    SDL_GetDisplayBounds(نما->displayID, &displayRect);
                } وإلا {
                    نما_w = display->desktop_نما.w;
                    نما_h = display->desktop_نما.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                إذا (پنجره->w != نما_w || پنجره->h != نما_h) {
                    resized = true;
                }

                SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MOVED, displayRect.x, displayRect.y);

                إذا (resized) {
                    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, نما_w, نما_h);
                } وإلا {
                    SDL_On_پنجره_Resized(پنجره);
                }
            }
        }
    } وإلا {
        bool resized = false;

        // Restore the desktop mode
        إذا (display) {
            display->fullscreen_فعال = false;

            SDL_مجموعه_Display_نما_For_Display(display, عدم);
        }
        إذا (commit) {
            SDL_Fullscreen_نتیجه ret = SDL_FULLSCREEN_SUCCEEDED;
            إذا (_this->مجموعه_پنجره_Fullscreen) {
                SDL_VideoDisplay *پر_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_پنجره(پنجره);
                إذا (پر_screen_display) {
                    ret = _this->مجموعه_پنجره_Fullscreen(_this, پنجره, پر_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } وإلا {
                resized = true;
            }

            إذا (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
                    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_LEAVE_FULLSCREEN, 0, 0);
                }
            } وإلا إذا (ret == SDL_FULLSCREEN_FAILED) {
                اذهب error;
            }
        }

        إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN)) {
            إذا (display) {
                display->fullscreen_پنجره = عدم;
            }

            إذا (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MOVED, پنجره->windowed.x, پنجره->windowed.y);
                إذا (resized) {
                    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESIZED, پنجره->windowed.w, پنجره->windowed.h);
                } وإلا {
                    SDL_On_پنجره_Resized(پنجره);
                }
            }
        }
    }

انجامشده:
    پنجره->آخرین_fullscreen_exclusive_display = display && (پنجره->flags & SDL_پنجره_FULLSCREEN) && پنجره->fullscreen_exclusive ? display->id : 0;
    أرجع true;

error:
    إذا (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    أرجع false;
}

bool SDL_مجموعه_پنجره_Fullscreen_نما(SDL_پنجره *پنجره, ثابت SDL_Display_نما *نما)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (نما) {
        إذا (!SDL_Get_Fullscreen_نما_تطابق(نما)) {
            أرجع SDL_مجموعه_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&پنجره->requested_fullscreen_نما, نما);
    } وإلا {
        SDL_zero(پنجره->requested_fullscreen_نما);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&پنجره->current_fullscreen_نما, &پنجره->requested_fullscreen_نما);

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    إذا (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_پنجره_درون_Fullscreen_Space_Transition(پنجره)) {
        SDL_Sync_پنجره(پنجره);
    }
#پایان_اگر
    إذا (SDL_پنجره_FULLSCREEN_VISIBLE(پنجره)) {
        SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(پنجره);
    }

    أرجع true;
}

ثابت SDL_Display_نما *SDL_Get_پنجره_Fullscreen_نما(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, عدم);
    CHECK_پنجره_NOT_POPUP(پنجره, عدم);

    إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        أرجع SDL_Get_Fullscreen_نما_تطابق(&پنجره->current_fullscreen_نما);
    } وإلا {
        أرجع SDL_Get_Fullscreen_نما_تطابق(&پنجره->requested_fullscreen_نما);
    }
}

فراغ *SDL_Get_پنجره_ICCProfile(SDL_پنجره *پنجره, size_t *اندازه)
{
    إذا (!_this->Get_پنجره_ICCProfile) {
        SDL_Unsupported();
        أرجع عدم;
    }
    أرجع _this->Get_پنجره_ICCProfile(_this, پنجره, اندازه);
}

SDL_PixelFormat SDL_Get_پنجره_Pixel_Format(SDL_پنجره *پنجره)
{
    SDL_DisplayID displayID;
    ثابت SDL_Display_نما *نما;

    CHECK_پنجره_MAGIC(پنجره, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_پنجره(پنجره);
    نما = SDL_Get_Current_Display_نما(displayID);
    إذا (نما) {
        أرجع نما->format;
    } وإلا {
        أرجع SDL_PIXELFORMAT_UNKNOWN;
    }
}

#تعریف_کن CREATE_FLAGS \
    (SDL_پنجره_OPENGL | SDL_پنجره_BORDERLESS | SDL_پنجره_RESIZABLE | SDL_پنجره_بالا_PIXEL_DENSITY | SDL_پنجره_ALWAYS_ON_بالاترین | SDL_پنجره_POPUP_MENU | SDL_پنجره_UTILITY | SDL_پنجره_TOOLTIP | SDL_پنجره_VULKAN | SDL_پنجره_MINIMIZED | SDL_پنجره_METAL | SDL_پنجره_TRANSPARENT | SDL_پنجره_NOT_FOCUSABLE | SDL_پنجره_FILL_DOCUMENT)

ساكن SDL_INLINE bool IsAcceptingDragAndDrop(فراغ)
{
    إذا (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_متن)) {
        أرجع true;
    }
    أرجع false;
}

// prepare a newly-created window
ساكن SDL_INLINE فراغ PrepareDragAndDropSupport(SDL_پنجره *پنجره)
{
    إذا (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(پنجره, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
فراغ SDL_ToggleDragAndDropSupport(فراغ)
{
    إذا (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_پنجره *پنجره;
        لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
            _this->AcceptDragAndDrop(پنجره, enable);
        }
    }
}

SDL_پنجره ** SDLCALL SDL_GetWindows(صحيح *شمار)
{
    إذا (شمار) {
        *شمار = 0;
    }

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }

    SDL_پنجره *پنجره;
    صحيح رقم_added = 0;
    صحيح رقم_windows = 0;
    لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
        ++رقم_windows;
    }

    SDL_پنجره **windows = (SDL_پنجره **)SDL_malloc((رقم_windows + 1) * حجم(*windows));
    إذا (!windows) {
        أرجع عدم;
    }

    لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
        windows[رقم_added++] = پنجره;
        إذا (رقم_added == رقم_windows) {
            // Race condition? Multi-threading not supported, ignore it
            اكسر;
        }
    }
    windows[رقم_added] = عدم;

    إذا (شمار) {
        *شمار = رقم_added;
    }
    أرجع windows;
}

ساكن فراغ Apply_پنجره_Flags(SDL_پنجره *پنجره, SDL_پنجره_Flags flags)
{
    إذا (!SDL_پنجره_IS_POPUP(پنجره)) {
        إذا (!(flags & (SDL_پنجره_MINIMIZED | SDL_پنجره_MAXIMIZED))) {
            SDL_Restore_پنجره(پنجره);
        }
        إذا (flags & SDL_پنجره_MAXIMIZED) {
            SDL_Maximize_پنجره(پنجره);
        }

        SDL_مجموعه_پنجره_Fullscreen(پنجره, (flags & SDL_پنجره_FULLSCREEN) != 0);

        إذا (flags & SDL_پنجره_MINIMIZED) {
            SDL_Minimize_پنجره(پنجره);
        }

        إذا (flags & SDL_پنجره_MODAL) {
            SDL_مجموعه_پنجره_Modal(پنجره, true);
        }

        إذا (flags & SDL_پنجره_MOUSE_GRABBED) {
            SDL_مجموعه_پنجره_Mouse_Grab(پنجره, true);
        }
        إذا (flags & SDL_پنجره_KEYBOARD_GRABBED) {
            SDL_مجموعه_پنجره_Keyboard_Grab(پنجره, true);
        }
    }
}

ساكن فراغ SDL_پایان_پنجره_Creation(SDL_پنجره *پنجره, SDL_پنجره_Flags flags)
{
    PrepareDragAndDropSupport(پنجره);

    إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } وإلا {
        Apply_پنجره_Flags(پنجره, flags);
        إذا (!(flags & SDL_پنجره_HIDDEN)) {
            SDL_Show_پنجره(پنجره);
        }
    }

#إذا defined(SDL_PLATFORM_LINUX)
    إذا (!SDL_پنجره_IS_POPUP(پنجره)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_مجموعه_پنجره_پیشرفت_State(پنجره, SDL_پیشرفت_STATE_NONE);
        SDL_مجموعه_پنجره_پیشرفت_مقدار(پنجره, 0.0f);
    }
#پایان_اگر
}

ساكن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    أرجع SDL_مجموعه_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساكن bool SDL_DllNotSupported(ثابت حرف *name)
{
    أرجع SDL_مجموعه_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ساكن بنية {
    ثابت حرف *property_name;
    SDL_پنجره_Flags flag;
    bool invert_مقدار;
} SDL_پنجره_Flag_Properties[] = {
    { SDL_PROP_پنجره_CREATE_ALWAYS_ON_بالاترین_BOOLEAN,      SDL_پنجره_ALWAYS_ON_بالاترین,       false },
    { SDL_PROP_پنجره_CREATE_BORDERLESS_BOOLEAN,         SDL_پنجره_BORDERLESS,          false },
    { SDL_PROP_پنجره_CREATE_FOCUSABLE_BOOLEAN,          SDL_پنجره_NOT_FOCUSABLE,       true },
    { SDL_PROP_پنجره_CREATE_FULLSCREEN_BOOLEAN,         SDL_پنجره_FULLSCREEN,          false },
    { SDL_PROP_پنجره_CREATE_HIDDEN_BOOLEAN,             SDL_پنجره_HIDDEN,              false },
    { SDL_PROP_پنجره_CREATE_بالا_PIXEL_DENSITY_BOOLEAN, SDL_پنجره_بالا_PIXEL_DENSITY,  false },
    { SDL_PROP_پنجره_CREATE_MAXIMIZED_BOOLEAN,          SDL_پنجره_MAXIMIZED,           false },
    { SDL_PROP_پنجره_CREATE_MENU_BOOLEAN,               SDL_پنجره_POPUP_MENU,          false },
    { SDL_PROP_پنجره_CREATE_METAL_BOOLEAN,              SDL_پنجره_METAL,               false },
    { SDL_PROP_پنجره_CREATE_MINIMIZED_BOOLEAN,          SDL_پنجره_MINIMIZED,           false },
    { SDL_PROP_پنجره_CREATE_MODAL_BOOLEAN,              SDL_پنجره_MODAL,               false },
    { SDL_PROP_پنجره_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_پنجره_MOUSE_GRABBED,       false },
    { SDL_PROP_پنجره_CREATE_OPENGL_BOOLEAN,             SDL_پنجره_OPENGL,              false },
    { SDL_PROP_پنجره_CREATE_RESIZABLE_BOOLEAN,          SDL_پنجره_RESIZABLE,           false },
    { SDL_PROP_پنجره_CREATE_TRANSPARENT_BOOLEAN,        SDL_پنجره_TRANSPARENT,         false },
    { SDL_PROP_پنجره_CREATE_TOOLTIP_BOOLEAN,            SDL_پنجره_TOOLTIP,             false },
    { SDL_PROP_پنجره_CREATE_UTILITY_BOOLEAN,            SDL_پنجره_UTILITY,             false },
    { SDL_PROP_پنجره_CREATE_VULKAN_BOOLEAN,             SDL_پنجره_VULKAN,              false }
};

ساكن SDL_پنجره_Flags SDL_Get_پنجره_Flag_Properties(SDL_PropertiesID props)
{
    بیعلامت i;
    SDL_پنجره_Flags flags = (SDL_پنجره_Flags)SDL_Get_عدد_Property(props, SDL_PROP_پنجره_CREATE_FLAGS_عدد, 0);

    لكل (i = 0; i < SDL_arraysize(SDL_پنجره_Flag_Properties); ++i) {
        إذا (SDL_پنجره_Flag_Properties[i].invert_مقدار) {
            إذا (!SDL_GetBooleanProperty(props, SDL_پنجره_Flag_Properties[i].property_name, true)) {
                flags |= SDL_پنجره_Flag_Properties[i].flag;
            }
        } وإلا {
            إذا (SDL_GetBooleanProperty(props, SDL_پنجره_Flag_Properties[i].property_name, false)) {
                flags |= SDL_پنجره_Flag_Properties[i].flag;
            }
        }
    }
    أرجع flags;
}

SDL_پنجره *SDL_Create_پنجره_With_Properties(SDL_PropertiesID props)
{
    SDL_پنجره *پنجره;
    ثابت حرف *title = SDL_GetStringProperty(props, SDL_PROP_پنجره_CREATE_TITLE_STRING, عدم);
    صحيح x = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_پنجره_CREATE_X_عدد, SDL_WINDOWPOS_UNDEFINED);
    صحيح y = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_پنجره_CREATE_Y_عدد, SDL_WINDOWPOS_UNDEFINED);
    صحيح w = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_پنجره_CREATE_عرض_عدد, 0);
    صحيح h = (صحيح)SDL_Get_عدد_Property(props, SDL_PROP_پنجره_CREATE_ارتفاع_عدد, 0);
    SDL_پنجره *والد = (SDL_پنجره *)SDL_Get_اشاره_گر_Property(props, SDL_PROP_پنجره_CREATE_والد_اشاره_گر, عدم);
    SDL_پنجره_Flags flags = SDL_Get_پنجره_Flag_Properties(props);
    SDL_پنجره_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_پنجره_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

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

    إذا ((flags & SDL_پنجره_MODAL) && !SDL_ObjectValid(والد, SDL_OBJECT_TYPE_پنجره)) {
        SDL_مجموعه_Error("Modal windows must specify a parent window");
        أرجع عدم;
    }

    إذا ((flags & (SDL_پنجره_TOOLTIP | SDL_پنجره_POPUP_MENU)) != 0) {
        إذا (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_پنجره_SUPPORT)) {
            SDL_Unsupported();
            أرجع عدم;
        }

        // Tooltip and popup menu window must specify a parent window
        إذا (!SDL_ObjectValid(والد, SDL_OBJECT_TYPE_پنجره)) {
            SDL_مجموعه_Error("Tooltip and popup menu windows must specify a parent window");
            أرجع عدم;
        }

        // Remove invalid flags
        flags &= ~(SDL_پنجره_MINIMIZED | SDL_پنجره_MAXIMIZED | SDL_پنجره_FULLSCREEN | SDL_پنجره_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_پنجره_UTILITY | SDL_پنجره_TOOLTIP | SDL_پنجره_POPUP_MENU | SDL_پنجره_MODAL);
    إذا (type_flags & (type_flags - 1)) {
        SDL_مجموعه_Error("Conflicting window type flags specified: 0x%.8x", (بیعلامت صحيح)type_flags);
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
    graphics_flags = flags & (SDL_پنجره_OPENGL | SDL_پنجره_METAL | SDL_پنجره_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        SDL_مجموعه_Error("Conflicting window graphics flags specified: 0x%.8x", (بیعلامت صحيح)graphics_flags);
        أرجع عدم;
    }

    // Some platforms have certain graphics backends enabled by default
    إذا (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    إذا (flags & SDL_پنجره_OPENGL) {
        إذا (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            أرجع عدم;
        }
        إذا (!SDL_GL_بارگیری_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_پنجره_VULKAN) {
        إذا (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            أرجع عدم;
        }
        إذا (!SDL_Vulkan_بارگیری_Library(عدم)) {
            أرجع عدم;
        }
    }

    إذا (flags & SDL_پنجره_METAL) {
        إذا (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            أرجع عدم;
        }
    }

    پنجره = (SDL_پنجره *)SDL_calloc(1, حجم(*پنجره));
    إذا (!پنجره) {
        أرجع عدم;
    }
    SDL_مجموعه_Object_Valid(پنجره, SDL_OBJECT_TYPE_پنجره, true);
    پنجره->id = SDL_Get_بعدی_Object_ID();
    پنجره->floating.x = پنجره->windowed.x = پنجره->x = x;
    پنجره->floating.y = پنجره->windowed.y = پنجره->y = y;
    پنجره->floating.w = پنجره->windowed.w = پنجره->w = w;
    پنجره->floating.h = پنجره->windowed.h = پنجره->h = h;
    پنجره->undefined_x = undefined_x;
    پنجره->undefined_y = undefined_y;
    پنجره->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_پنجره(پنجره);
    إذا (display) {
        SDL_مجموعه_پنجره_HDRProperties(پنجره, &display->HDR, false);
    }

    إذا (flags & SDL_پنجره_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        پنجره->x = bounds.x;
        پنجره->y = bounds.y;
        پنجره->w = bounds.w;
        پنجره->h = bounds.h;
        پنجره->pending_flags |= SDL_پنجره_FULLSCREEN;
        flags |= SDL_پنجره_FULLSCREEN;
    }

    پنجره->flags = ((flags & CREATE_FLAGS) | SDL_پنجره_HIDDEN);
    پنجره->display_scale = 1.0f;
    پنجره->opacity = 1.0f;
    پنجره->بعدی = _this->windows;
    پنجره->is_destroying = false;
    پنجره->displayID = Get_Display_For_پنجره(پنجره);
    پنجره->external_graphics_context = external_graphics_context;
    پنجره->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_پنجره_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    إذا (!_this->مجموعه_پنجره_Fill_Document) {
        پنجره->flags &= ~SDL_پنجره_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    إذا (_this->windows) {
        _this->windows->prev = پنجره;
    }
    _this->windows = پنجره;

    // Set the parent before creation.
    SDL_Update_پنجره_Hierarchy(پنجره, والد);

    إذا (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, پنجره, props)) {
        SDL_افزودن_Error();
        SDL_Destroy_پنجره(پنجره);
        SDL_برداشت_Error();
        أرجع عدم;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#إذا !defined(SDL_PLATFORM_WINDOWS)
    إذا (پنجره->flags & SDL_پنجره_MINIMIZED) {
        پنجره->flags &= ~SDL_پنجره_MINIMIZED;
    }
#پایان_اگر

    إذا (title) {
        SDL_مجموعه_پنجره_Title(پنجره, title);
    }
    SDL_پایان_پنجره_Creation(پنجره, flags);

    // Make sure window pixel size is up to date
    SDL_Check_پنجره_Pixel_اندازه_تغییریافته(پنجره);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#پایان_اگر

    SDL_ClearError();

    أرجع پنجره;
}

SDL_پنجره *SDL_Create_پنجره(ثابت حرف *title, صحيح w, صحيح h, SDL_پنجره_Flags flags)
{
    SDL_پنجره *پنجره;
    SDL_PropertiesID props = SDL_CreateProperties();
    إذا (title && *title) {
        SDL_مجموعه_String_Property(props, SDL_PROP_پنجره_CREATE_TITLE_STRING, title);
    }
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_عرض_عدد, w);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_ارتفاع_عدد, h);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_FLAGS_عدد, flags);
    پنجره = SDL_Create_پنجره_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع پنجره;
}

SDL_پنجره *SDL_Create_Popup_پنجره(SDL_پنجره *والد, صحيح جابه_جایی_x, صحيح جابه_جایی_y, صحيح w, صحيح h, SDL_پنجره_Flags flags)
{
    SDL_پنجره *پنجره;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    إذا (!(flags & (SDL_پنجره_TOOLTIP | SDL_پنجره_POPUP_MENU))) {
        SDL_مجموعه_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        أرجع عدم;
    }

    SDL_مجموعه_اشاره_گر_Property(props, SDL_PROP_پنجره_CREATE_والد_اشاره_گر, والد);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_X_عدد, جابه_جایی_x);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_Y_عدد, جابه_جایی_y);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_عرض_عدد, w);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_ارتفاع_عدد, h);
    SDL_مجموعه_عدد_Property(props, SDL_PROP_پنجره_CREATE_FLAGS_عدد, flags);
    پنجره = SDL_Create_پنجره_With_Properties(props);
    SDL_DestroyProperties(props);
    أرجع پنجره;
}

ساكن bool SDL_Reconfigure_پنجره_داخلی(SDL_پنجره *پنجره, SDL_پنجره_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    إذا (!_this->Reconfigure_پنجره) {
        أرجع false;
    }

    ثابت SDL_پنجره_Flags graphics_flags = flags & (SDL_پنجره_OPENGL | SDL_پنجره_METAL | SDL_پنجره_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_مجموعه_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_پنجره_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_پنجره_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_پنجره_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        إذا (پنجره->flags & (SDL_پنجره_OPENGL | SDL_پنجره_METAL | SDL_پنجره_VULKAN)) {
            أرجع false;
        }
    } وإلا {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        إذا (!_this->Reconfigure_پنجره(_this, پنجره, 0)) {
            أرجع false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        إذا (پنجره->flags & SDL_پنجره_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        إذا (پنجره->flags & SDL_پنجره_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        پنجره->flags &= ~(SDL_پنجره_OPENGL | SDL_پنجره_METAL | SDL_پنجره_VULKAN);
    }

    SDL_Destroy_پنجره_Surface(پنجره);

    إذا (graphics_flags & SDL_پنجره_OPENGL) {
        loaded_opengl = SDL_GL_بارگیری_Library(عدم);
        إذا (!loaded_opengl) {
            أرجع false;
        }
    } وإلا إذا (graphics_flags & SDL_پنجره_VULKAN) {
        loaded_vulkan = SDL_Vulkan_بارگیری_Library(عدم);
        إذا (!loaded_vulkan) {
            أرجع false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    إذا (!_this->Reconfigure_پنجره(_this, پنجره, graphics_flags)) {
        إذا (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        إذا (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        أرجع false;
    }

    پنجره->flags |= graphics_flags;

    أرجع true;
}

bool SDL_Recreate_پنجره(SDL_پنجره *پنجره, SDL_پنجره_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_بارگیری = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_بارگیری = false;
    SDL_پنجره_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_پنجره_OPENGL | SDL_پنجره_METAL | SDL_پنجره_VULKAN);
    إذا (graphics_flags & (graphics_flags - 1)) {
        أرجع SDL_مجموعه_Error("Conflicting window flags specified");
    }

    إذا ((flags & SDL_پنجره_OPENGL) && !_this->GL_CreateContext) {
        أرجع SDL_ContextNotSupported("OpenGL");
    }
    إذا ((flags & SDL_پنجره_VULKAN) && !_this->Vulkan_CreateSurface) {
        أرجع SDL_ContextNotSupported("Vulkan");
    }
    إذا ((flags & SDL_پنجره_METAL) && !_this->Metal_CreateView) {
        أرجع SDL_ContextNotSupported("Metal");
    }

    إذا (پنجره->flags & SDL_پنجره_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_پنجره_EXTERNAL;
    } وإلا {
        flags &= ~SDL_پنجره_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    إذا (پنجره->flags & SDL_پنجره_MODAL) {
        SDL_مجموعه_پنجره_Modal(پنجره, false);
    }

    // Restore video mode, etc.
    إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL)) {
        ثابت bool restore_on_show = پنجره->restore_on_show;
        SDL_Hide_پنجره(پنجره);
        پنجره->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_پنجره_Surface(پنجره);

    إذا ((پنجره->flags & SDL_پنجره_OPENGL) != (flags & SDL_پنجره_OPENGL)) {
        إذا (flags & SDL_پنجره_OPENGL) {
            need_gl_بارگیری = true;
        } وإلا {
            need_gl_unload = true;
        }
    } وإلا إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        need_gl_unload = true;
        need_gl_بارگیری = true;
    }

    إذا ((پنجره->flags & SDL_پنجره_VULKAN) != (flags & SDL_پنجره_VULKAN)) {
        إذا (flags & SDL_پنجره_VULKAN) {
            need_vulkan_بارگیری = true;
        } وإلا {
            need_vulkan_unload = true;
        }
    } وإلا إذا (پنجره->flags & SDL_پنجره_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_بارگیری = true;
    }

    إذا (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    إذا (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->Destroy_پنجره && !(flags & SDL_پنجره_EXTERNAL)) {
        _this->Destroy_پنجره(_this, پنجره);
    }

    إذا (need_gl_بارگیری) {
        إذا (!SDL_GL_بارگیری_Library(عدم)) {
            أرجع false;
        }
        loaded_opengl = true;
    }

    إذا (need_vulkan_بارگیری) {
        إذا (!SDL_Vulkan_بارگیری_Library(عدم)) {
            أرجع false;
        }
        loaded_vulkan = true;
    }

    پنجره->flags = ((flags & CREATE_FLAGS) | SDL_پنجره_HIDDEN);
    پنجره->is_destroying = false;

    إذا (_this->CreateSDLWindow && !(flags & SDL_پنجره_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        پنجره->x = پنجره->windowed.x = پنجره->floating.x;
        پنجره->y = پنجره->windowed.y = پنجره->floating.y;
        پنجره->w = پنجره->windowed.w = پنجره->floating.w;
        پنجره->h = پنجره->windowed.h = پنجره->floating.h;

        إذا (!_this->CreateSDLWindow(_this, پنجره, 0)) {
            إذا (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                پنجره->flags &= ~SDL_پنجره_OPENGL;
            }
            إذا (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                پنجره->flags &= ~SDL_پنجره_VULKAN;
            }
            أرجع false;
        }
    }

    إذا (flags & SDL_پنجره_EXTERNAL) {
        پنجره->flags |= SDL_پنجره_EXTERNAL;
    }

    إذا (_this->مجموعه_پنجره_Title && پنجره->title) {
        _this->مجموعه_پنجره_Title(_this, پنجره);
    }

    إذا (_this->مجموعه_پنجره_Icon && پنجره->icon) {
        _this->مجموعه_پنجره_Icon(_this, پنجره, پنجره->icon);
    }

    إذا (_this->مجموعه_پنجره_Minimum_اندازه && (پنجره->min_w || پنجره->min_h)) {
        _this->مجموعه_پنجره_Minimum_اندازه(_this, پنجره);
    }

    إذا (_this->مجموعه_پنجره_بیشینه_اندازه && (پنجره->max_w || پنجره->max_h)) {
        _this->مجموعه_پنجره_بیشینه_اندازه(_this, پنجره);
    }

    إذا (_this->مجموعه_پنجره_Aspect_نسبت && (پنجره->min_aspect > 0.0f || پنجره->max_aspect > 0.0f)) {
        _this->مجموعه_پنجره_Aspect_نسبت(_this, پنجره);
    }

    إذا (پنجره->اصابت_test) {
        _this->مجموعه_پنجره_اصابت_Test(پنجره, true);
    }

    SDL_پایان_پنجره_Creation(پنجره, flags);

    أرجع true;
}

bool SDL_Reconfigure_پنجره(SDL_پنجره *پنجره, SDL_پنجره_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    إذا (!SDL_Reconfigure_پنجره_داخلی(پنجره, flags)) {
        أرجع SDL_Recreate_پنجره(پنجره, flags);
    }

    أرجع true;
}

bool SDL_HasWindows(فراغ)
{
    أرجع _this && _this->windows;
}

SDL_پنجره_ID SDL_Get_پنجره_ID(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, 0);

    أرجع پنجره->id;
}

SDL_پنجره *SDL_Get_پنجره_From_ID(SDL_پنجره_ID id)
{
    SDL_پنجره *پنجره;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (id) {
        لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
            إذا (پنجره->id == id) {
                أرجع پنجره;
            }
        }
    }
    SDL_مجموعه_Error("Invalid window ID");
    أرجع عدم;
}

SDL_پنجره *SDL_Get_پنجره_والد(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, عدم);

    أرجع پنجره->والد;
}

SDL_PropertiesID SDL_Get_پنجره_Properties(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, 0);

    إذا (پنجره->props == 0) {
        پنجره->props = SDL_CreateProperties();
    }
    أرجع پنجره->props;
}

SDL_پنجره_Flags SDL_Get_پنجره_Flags(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, 0);

    أرجع پنجره->flags | پنجره->pending_flags;
}

bool SDL_مجموعه_پنجره_Title(SDL_پنجره *پنجره, ثابت حرف *title)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (title == پنجره->title) {
        أرجع true;
    }
    إذا (!title) {
        title = "";
    }
    إذا (پنجره->title && SDL_strcmp(title, پنجره->title) == 0) {
        أرجع true;
    }

    SDL_free(پنجره->title);

    پنجره->title = SDL_strdup(title);

    إذا (_this->مجموعه_پنجره_Title) {
        _this->مجموعه_پنجره_Title(_this, پنجره);
    }
    أرجع true;
}

ثابت حرف *SDL_Get_پنجره_Title(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, "");

    أرجع پنجره->title ? پنجره->title : "";
}

bool SDL_مجموعه_پنجره_Icon(SDL_پنجره *پنجره, SDL_Surface *icon)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    CHECK_PARAM(!icon) {
        أرجع SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(پنجره->icon);

    // Convert the icon into ARGB8888
    پنجره->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    إذا (!پنجره->icon) {
        أرجع false;
    }

    إذا (!_this->مجموعه_پنجره_Icon) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->مجموعه_پنجره_Icon(_this, پنجره, پنجره->icon);
}

bool SDL_مجموعه_پنجره_Position(SDL_پنجره *پنجره, صحيح x, صحيح y)
{
    SDL_DisplayID original_displayID;

    CHECK_پنجره_MAGIC(پنجره, false);

    ثابت صحيح w = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : پنجره->windowed.w;
    ثابت صحيح h = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : پنجره->windowed.h;

    original_displayID = Get_Display_For_پنجره(پنجره);
    پنجره->pending_displayID = 0;

    إذا (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = پنجره->windowed.x;
    }
    إذا (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = پنجره->windowed.y;
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

        پنجره->pending_displayID = displayID;

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
        پنجره->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    پنجره->pending.x = x;
    پنجره->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    إذا (!_this->Sync_پنجره && (پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        پنجره->floating.x = پنجره->windowed.x = x;
        پنجره->floating.y = پنجره->windowed.y = y;
    }
    پنجره->undefined_x = false;
    پنجره->undefined_y = false;
    پنجره->آخرین_position_pending = true;

    إذا (_this->مجموعه_پنجره_Position) {
        ثابت bool نتیجه = _this->مجموعه_پنجره_Position(_this, پنجره);
        إذا (نتیجه) {
            SDL_SyncIfRequired(پنجره);
        }
        أرجع نتیجه;
    }

    أرجع SDL_Unsupported();
}

bool SDL_Get_پنجره_Position(SDL_پنجره *پنجره, صحيح *x, صحيح *y)
{
    CHECK_پنجره_MAGIC(پنجره, false);

#اگر_تعریف_شده SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#وإلا
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((پنجره->flags & SDL_پنجره_FULLSCREEN) != 0);
#پایان_اگر
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
        displayID = Get_Display_For_پنجره(پنجره);
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
        ثابت bool use_pending = (پنجره->flags & SDL_پنجره_HIDDEN) && پنجره->آخرین_position_pending;
        إذا (x) {
            *x = use_pending ? پنجره->pending.x : پنجره->x;
        }
        إذا (y) {
            *y = use_pending ? پنجره->pending.y : پنجره->y;
        }
    }
    أرجع true;
}

bool SDL_مجموعه_پنجره_Bordered(SDL_پنجره *پنجره, bool bordered)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (!_this->مجموعه_پنجره_Bordered) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(پنجره->flags & SDL_پنجره_BORDERLESS);
    إذا (want != have) {
        إذا (want) {
            پنجره->flags &= ~SDL_پنجره_BORDERLESS;
        } وإلا {
            پنجره->flags |= SDL_پنجره_BORDERLESS;
        }
        _this->مجموعه_پنجره_Bordered(_this, پنجره, want);
    }

    أرجع true;
}

bool SDL_مجموعه_پنجره_Resizable(SDL_پنجره *پنجره, bool resizable)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (!_this->مجموعه_پنجره_Resizable) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((پنجره->flags & SDL_پنجره_RESIZABLE) != 0);
    إذا (want != have) {
        إذا (want) {
            پنجره->flags |= SDL_پنجره_RESIZABLE;
        } وإلا {
            پنجره->flags &= ~SDL_پنجره_RESIZABLE;
            SDL_copyp(&پنجره->windowed, &پنجره->floating);
        }
        _this->مجموعه_پنجره_Resizable(_this, پنجره, want);
    }

    أرجع true;
}

bool SDL_مجموعه_پنجره_Always_On_بالاترین(SDL_پنجره *پنجره, bool on_بالاترین)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (!_this->مجموعه_پنجره_Always_On_بالاترین) {
        أرجع SDL_Unsupported();
    }

    ثابت bool want = on_بالاترین;
    ثابت bool have = ((پنجره->flags & SDL_پنجره_ALWAYS_ON_بالاترین) != 0);
    إذا (want != have) {
        إذا (want) {
            پنجره->flags |= SDL_پنجره_ALWAYS_ON_بالاترین;
        } وإلا {
            پنجره->flags &= ~SDL_پنجره_ALWAYS_ON_بالاترین;
        }
        _this->مجموعه_پنجره_Always_On_بالاترین(_this, پنجره, want);
    }

    أرجع true;
}

bool SDL_مجموعه_پنجره_اندازه(SDL_پنجره *پنجره, صحيح w, صحيح h)
{
    CHECK_پنجره_MAGIC(پنجره, false);

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
    إذا (پنجره->max_aspect > 0.0f && new_aspect > پنجره->max_aspect) {
        w = (صحيح)SDL_roundf(h * پنجره->max_aspect);
    } وإلا إذا (پنجره->min_aspect > 0.0f && new_aspect < پنجره->min_aspect) {
        h = (صحيح)SDL_roundf(w / پنجره->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    إذا (پنجره->min_w && w < پنجره->min_w) {
        w = پنجره->min_w;
    }
    إذا (پنجره->max_w && w > پنجره->max_w) {
        w = پنجره->max_w;
    }
    إذا (پنجره->min_h && h < پنجره->min_h) {
        h = پنجره->min_h;
    }
    إذا (پنجره->max_h && h > پنجره->max_h) {
        h = پنجره->max_h;
    }

    پنجره->آخرین_اندازه_pending = true;
    پنجره->pending.w = w;
    پنجره->pending.h = h;

    إذا (_this->مجموعه_پنجره_اندازه) {
        _this->مجموعه_پنجره_اندازه(_this, پنجره);
        SDL_SyncIfRequired(پنجره);
    } وإلا {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

bool SDL_Get_پنجره_اندازه(SDL_پنجره *پنجره, صحيح *w, صحيح *h)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    إذا (w) {
        *w = پنجره->w;
    }
    إذا (h) {
        *h = پنجره->h;
    }
    أرجع true;
}

bool SDL_مجموعه_پنجره_Aspect_نسبت(SDL_پنجره *پنجره, عائم min_aspect, عائم max_aspect)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    پنجره->min_aspect = min_aspect;
    پنجره->max_aspect = max_aspect;

    إذا (_this->مجموعه_پنجره_Aspect_نسبت) {
        _this->مجموعه_پنجره_Aspect_نسبت(_this, پنجره);
    }

    // Ensure that window has the correct aspect ratio
    صحيح w = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : پنجره->floating.w;
    صحيح h = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : پنجره->floating.h;
    أرجع SDL_مجموعه_پنجره_اندازه(پنجره, w, h);
}

bool SDL_Get_پنجره_Aspect_نسبت(SDL_پنجره *پنجره, عائم *min_aspect, عائم *max_aspect)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (min_aspect) {
        *min_aspect = پنجره->min_aspect;
    }
    إذا (max_aspect) {
        *max_aspect = پنجره->max_aspect;
    }
    أرجع true;
}

bool SDL_Get_پنجره_Borders_اندازه(SDL_پنجره *پنجره, صحيح *بالاترین, صحيح *چپ, صحيح *bottom, صحيح *راست)
{
    صحيح dummy = 0;

    إذا (!بالاترین) {
        بالاترین = &dummy;
    }
    إذا (!چپ) {
        چپ = &dummy;
    }
    إذا (!راست) {
        راست = &dummy;
    }
    إذا (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *بالاترین = *چپ = *bottom = *راست = 0;

    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!_this->Get_پنجره_Borders_اندازه) {
        أرجع SDL_Unsupported();
    }

    أرجع _this->Get_پنجره_Borders_اندازه(_this, پنجره, بالاترین, چپ, bottom, راست);
}

bool SDL_Get_پنجره_اندازه_درون_Pixels(SDL_پنجره *پنجره, صحيح *w, صحيح *h)
{
    صحيح filter;

    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!w) {
        w = &filter;
    }

    إذا (!h) {
        h = &filter;
    }

    إذا (_this->Get_پنجره_اندازه_درون_Pixels) {
        _this->Get_پنجره_اندازه_درون_Pixels(_this, پنجره, w, h);
    } وإلا {
        SDL_DisplayID displayID = Get_Display_For_پنجره(پنجره);
        ثابت SDL_Display_نما *نما;

        SDL_Get_پنجره_اندازه(پنجره, w, h);

        إذا ((پنجره->flags & SDL_پنجره_FULLSCREEN) && SDL_Get_پنجره_Fullscreen_نما(پنجره)) {
            نما = SDL_Get_Current_Display_نما(displayID);
        } وإلا {
            نما = SDL_Get_Desktop_Display_نما(displayID);
        }
        إذا (نما) {
            *w = (صحيح)SDL_ceilf(*w * نما->pixel_density);
            *h = (صحيح)SDL_ceilf(*h * نما->pixel_density);
        }
    }
    أرجع true;
}

bool SDL_مجموعه_پنجره_Minimum_اندازه(SDL_پنجره *پنجره, صحيح min_w, صحيح min_h)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_PARAM(min_w < 0) {
        أرجع SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        أرجع SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((پنجره->max_w && min_w > پنجره->max_w) || (پنجره->max_h && min_h > پنجره->max_h)) {
        أرجع SDL_مجموعه_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    پنجره->min_w = min_w;
    پنجره->min_h = min_h;

    إذا (_this->مجموعه_پنجره_Minimum_اندازه) {
        _this->مجموعه_پنجره_Minimum_اندازه(_this, پنجره);
    }

    // Ensure that window is not smaller than minimal size
    صحيح w = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : پنجره->floating.w;
    صحيح h = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : پنجره->floating.h;
    أرجع SDL_مجموعه_پنجره_اندازه(پنجره, w, h);
}

bool SDL_Get_پنجره_Minimum_اندازه(SDL_پنجره *پنجره, صحيح *min_w, صحيح *min_h)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    إذا (min_w) {
        *min_w = پنجره->min_w;
    }
    إذا (min_h) {
        *min_h = پنجره->min_h;
    }
    أرجع true;
}

bool SDL_مجموعه_پنجره_بیشینه_اندازه(SDL_پنجره *پنجره, صحيح max_w, صحيح max_h)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_PARAM(max_w < 0) {
        أرجع SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        أرجع SDL_InvalidParamError("max_h");
    }

    إذا ((max_w && max_w < پنجره->min_w) ||
        (max_h && max_h < پنجره->min_h)) {
        أرجع SDL_مجموعه_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    پنجره->max_w = max_w;
    پنجره->max_h = max_h;

    إذا (_this->مجموعه_پنجره_بیشینه_اندازه) {
        _this->مجموعه_پنجره_بیشینه_اندازه(_this, پنجره);
    }

    // Ensure that window is not larger than maximal size
    صحيح w = پنجره->آخرین_اندازه_pending ? پنجره->pending.w : پنجره->floating.w;
    صحيح h = پنجره->آخرین_اندازه_pending ? پنجره->pending.h : پنجره->floating.h;
    أرجع SDL_مجموعه_پنجره_اندازه(پنجره, w, h);
}

bool SDL_Get_پنجره_بیشینه_اندازه(SDL_پنجره *پنجره, صحيح *max_w, صحيح *max_h)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    إذا (max_w) {
        *max_w = پنجره->max_w;
    }
    إذا (max_h) {
        *max_h = پنجره->max_h;
    }
    أرجع true;
}

bool SDL_Show_پنجره(SDL_پنجره *پنجره)
{
    SDL_پنجره *فرزند;
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!(پنجره->flags & SDL_پنجره_HIDDEN)) {
        أرجع true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    إذا (پنجره->والد && (پنجره->والد->flags & SDL_پنجره_HIDDEN)) {
        پنجره->restore_on_show = true;
        أرجع true;
    }

    إذا (_this->Show_پنجره) {
        _this->Show_پنجره(_this, پنجره);
    } وإلا {
        SDL_مجموعه_Mouse_Focus(پنجره);
        SDL_مجموعه_Keyboard_Focus(پنجره);
    }
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_SHOWN, 0, 0);

    // Restore child windows
    لكل (فرزند = پنجره->اولی_فرزند; فرزند; فرزند = فرزند->بعدی_sibling) {
        إذا (!فرزند->restore_on_show && (فرزند->flags & SDL_پنجره_HIDDEN)) {
            اكسر;
        }
        SDL_Show_پنجره(فرزند);
        فرزند->restore_on_show = false;
    }
    أرجع true;
}

bool SDL_Hide_پنجره(SDL_پنجره *پنجره)
{
    SDL_پنجره *فرزند;
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        پنجره->restore_on_show = false;
        أرجع true;
    }

    // Hide all child windows
    لكل (فرزند = پنجره->اولی_فرزند; فرزند; فرزند = فرزند->بعدی_sibling) {
        إذا (فرزند->flags & SDL_پنجره_HIDDEN) {
            اكسر;
        }
        SDL_Hide_پنجره(فرزند);
        فرزند->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_پنجره_Flags pending_ماسک = (SDL_پنجره_MAXIMIZED | SDL_پنجره_MINIMIZED | SDL_پنجره_FULLSCREEN | SDL_پنجره_KEYBOARD_GRABBED | SDL_پنجره_MOUSE_GRABBED);
    پنجره->pending_flags = (پنجره->flags & pending_ماسک);

    پنجره->is_hiding = true;
    إذا (_this->Hide_پنجره) {
        _this->Hide_پنجره(_this, پنجره);
    } وإلا {
        SDL_مجموعه_Mouse_Focus(عدم);
        SDL_مجموعه_Keyboard_Focus(عدم);
    }
    پنجره->is_hiding = false;
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_HIDDEN, 0, 0);
    أرجع true;
}

bool SDL_Raise_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        أرجع true;
    }
    إذا (_this->Raise_پنجره) {
        _this->Raise_پنجره(_this, پنجره);
    }
    أرجع true;
}

bool SDL_Maximize_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (!_this->Maximize_پنجره) {
        أرجع SDL_Unsupported();
    }

    إذا (!(پنجره->flags & SDL_پنجره_RESIZABLE)) {
        أرجع SDL_مجموعه_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        پنجره->pending_flags |= SDL_پنجره_MAXIMIZED;
        أرجع true;
    }

    _this->Maximize_پنجره(_this, پنجره);
    SDL_SyncIfRequired(پنجره);
    أرجع true;
}

bool SDL_Minimize_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (!_this->Minimize_پنجره) {
        أرجع SDL_Unsupported();
    }

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        پنجره->pending_flags |= SDL_پنجره_MINIMIZED;
        أرجع true;
    }

    _this->Minimize_پنجره(_this, پنجره);
    SDL_SyncIfRequired(پنجره);
    أرجع true;
}

bool SDL_Restore_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (!_this->Restore_پنجره) {
        أرجع SDL_Unsupported();
    }

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        پنجره->pending_flags &= ~(SDL_پنجره_MAXIMIZED | SDL_پنجره_MINIMIZED);
        أرجع true;
    }

    _this->Restore_پنجره(_this, پنجره);
    SDL_SyncIfRequired(پنجره);
    أرجع true;
}

bool SDL_مجموعه_پنجره_Fullscreen(SDL_پنجره *پنجره, bool fullscreen)
{
    bool نتیجه;

    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        إذا (fullscreen) {
            پنجره->pending_flags |= SDL_پنجره_FULLSCREEN;
        } وإلا {
            پنجره->pending_flags &= ~SDL_پنجره_FULLSCREEN;
        }
        أرجع true;
    }

    إذا (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&پنجره->current_fullscreen_نما, &پنجره->requested_fullscreen_نما);
    }

    نتیجه = SDL_Update_Fullscreen_نما(پنجره, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    إذا (!fullscreen || !نتیجه) {
        // Clear the current fullscreen mode.
        SDL_zero(پنجره->current_fullscreen_نما);
    }

    إذا (نتیجه) {
        SDL_SyncIfRequired(پنجره);
    }

    أرجع نتیجه;
}

bool SDL_Sync_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (_this->Sync_پنجره) {
        أرجع _this->Sync_پنجره(_this, پنجره);
    } وإلا {
        أرجع true;
    }
}

ساكن bool ShouldAttemptTextureFramebuffer(فراغ)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    إذا (!_this->Create_پنجره_Framebuffer) {
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

ساكن SDL_Surface *SDL_Create_پنجره_Framebuffer(SDL_پنجره *پنجره)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    فراغ *pixels = عدم;
    صحيح pitch = 0;
    bool created_framebuffer = false;
    صحيح w, h;

    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    إذا (!_this->checked_texture_framebuffer) {
        إذا (ShouldAttemptTextureFramebuffer()) {
            إذا (!SDL_Create_پنجره_Texture(_this, پنجره, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } وإلا {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_پنجره_Framebuffer = SDL_Create_پنجره_Texture;
                _this->مجموعه_پنجره_Framebuffer_VSync = SDL_مجموعه_پنجره_Texture_VSync;
                _this->Get_پنجره_Framebuffer_VSync = SDL_Get_پنجره_Texture_VSync;
                _this->Update_پنجره_Framebuffer = SDL_Update_پنجره_Texture;
                _this->Destroy_پنجره_Framebuffer = SDL_Destroy_پنجره_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    إذا (!created_framebuffer) {
        إذا (!_this->Create_پنجره_Framebuffer || !_this->Update_پنجره_Framebuffer) {
            SDL_مجموعه_Error("Window framebuffer support not available");
            أرجع عدم;
        }

        إذا (!_this->Create_پنجره_Framebuffer(_this, پنجره, &format, &pixels, &pitch)) {
            أرجع عدم;
        }
    }

    إذا (پنجره->surface) {
        // We may have gone recursive and already created the surface
        أرجع پنجره->surface;
    }

    أرجع SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_پنجره_Has_Surface(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    أرجع پنجره->surface ? true : false;
}

SDL_Surface *SDL_Get_پنجره_Surface(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, عدم);

    إذا (!پنجره->surface_valid) {
        إذا (پنجره->surface) {
            پنجره->surface->داخلی_flags &= ~SDL_داخلی_SURFACE_DONTFREE;
            SDL_DestroySurface(پنجره->surface);
            پنجره->surface = عدم;
        }

        پنجره->surface = SDL_Create_پنجره_Framebuffer(پنجره);
        إذا (پنجره->surface) {
            پنجره->surface_valid = true;
            پنجره->surface->داخلی_flags |= SDL_داخلی_SURFACE_DONTFREE;
        }
    }
    أرجع پنجره->surface;
}

bool SDL_مجموعه_پنجره_Surface_VSync(SDL_پنجره *پنجره, صحيح vsync)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!_this->مجموعه_پنجره_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->مجموعه_پنجره_Framebuffer_VSync(_this, پنجره, vsync);
}

bool SDL_Get_پنجره_Surface_VSync(SDL_پنجره *پنجره, صحيح *vsync)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!_this->Get_پنجره_Framebuffer_VSync) {
        أرجع SDL_Unsupported();
    }
    أرجع _this->Get_پنجره_Framebuffer_VSync(_this, پنجره, vsync);
}

bool SDL_Update_پنجره_Surface(SDL_پنجره *پنجره)
{
    SDL_Rect پر_rect;

    CHECK_پنجره_MAGIC(پنجره, false);

    پر_rect.x = 0;
    پر_rect.y = 0;
    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &پر_rect.w, &پر_rect.h);

    أرجع SDL_Update_پنجره_Surface_Rects(پنجره, &پر_rect, 1);
}

bool SDL_Update_پنجره_Surface_Rects(SDL_پنجره *پنجره, ثابت SDL_Rect *rects,
                                 صحيح numrects)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!پنجره->surface_valid) {
        أرجع SDL_مجموعه_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    أرجع _this->Update_پنجره_Framebuffer(_this, پنجره, rects, numrects);
}

bool SDL_Destroy_پنجره_Surface(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (پنجره->surface) {
        پنجره->surface->داخلی_flags &= ~SDL_داخلی_SURFACE_DONTFREE;
        SDL_DestroySurface(پنجره->surface);
        پنجره->surface = عدم;
        پنجره->surface_valid = false;
    }

    إذا (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        إذا (_this->Destroy_پنجره_Framebuffer) {
            _this->Destroy_پنجره_Framebuffer(_this, پنجره);
        }
    }
    أرجع true;
}

bool SDL_مجموعه_پنجره_Opacity(SDL_پنجره *پنجره, عائم opacity)
{
    bool نتیجه;

    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!_this->مجموعه_پنجره_Opacity) {
        أرجع SDL_Unsupported();
    }

    إذا (opacity < 0.0f) {
        opacity = 0.0f;
    } وإلا إذا (opacity > 1.0f) {
        opacity = 1.0f;
    }

    نتیجه = _this->مجموعه_پنجره_Opacity(_this, پنجره, opacity);
    إذا (نتیجه) {
        پنجره->opacity = opacity;
    }

    أرجع نتیجه;
}

عائم SDL_Get_پنجره_Opacity(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, -1.0f);

    أرجع پنجره->opacity;
}

bool SDL_مجموعه_پنجره_والد(SDL_پنجره *پنجره, SDL_پنجره *والد)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (والد) {
        CHECK_پنجره_MAGIC(والد, false);
        CHECK_پنجره_NOT_POPUP(والد, false);
    }

    إذا (پنجره == والد) {
        أرجع SDL_مجموعه_Error("Cannot set the parent of a window to itself.");
    }

    إذا (!_this->مجموعه_پنجره_والد) {
        أرجع SDL_Unsupported();
    }

    إذا (پنجره->flags & SDL_پنجره_MODAL) {
        أرجع SDL_مجموعه_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    إذا (پنجره->والد == والد) {
        أرجع true;
    }

    ثابت bool ret = _this->مجموعه_پنجره_والد(_this, پنجره, والد);
    SDL_Update_پنجره_Hierarchy(پنجره, ret ? والد : عدم);

    أرجع ret;
}

bool SDL_مجموعه_پنجره_Modal(SDL_پنجره *پنجره, bool modal)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (!_this->مجموعه_پنجره_Modal) {
        أرجع SDL_Unsupported();
    }

    إذا (modal) {
        إذا (!پنجره->والد) {
            أرجع SDL_مجموعه_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        پنجره->flags |= SDL_پنجره_MODAL;
    } وإلا إذا (پنجره->flags & SDL_پنجره_MODAL) {
        پنجره->flags &= ~SDL_پنجره_MODAL;
    } وإلا {
        أرجع true; // Already not modal, so nothing to do.
    }

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        أرجع true;
    }

    أرجع _this->مجموعه_پنجره_Modal(_this, پنجره, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_پنجره *پنجره, SDL_پنجره **new_focus)
{
    SDL_پنجره *focus = پنجره->والد;
    bool مجموعه_focus = !!(پنجره->flags & SDL_پنجره_درون_داد_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    طالما (SDL_پنجره_IS_POPUP(focus) && ((focus->flags & SDL_پنجره_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->والد;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        إذا (!مجموعه_focus) {
            مجموعه_focus = !!(focus->flags & SDL_پنجره_درون_داد_FOCUS);
        }
    }

    *new_focus = focus;
    أرجع مجموعه_focus;
}

bool SDL_ShouldFocusPopup(SDL_پنجره *پنجره)
{
    SDL_پنجره *toplevel_والد;
    لكل (toplevel_والد = پنجره->والد; SDL_پنجره_IS_POPUP(toplevel_والد); toplevel_والد = toplevel_والد->والد) {
    }

    SDL_پنجره *current_focus = toplevel_والد->keyboard_focus;
    bool یافت_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_پنجره *w;
    لكل (w = current_focus; w != toplevel_والد; w = w->والد) {
        إذا (w == پنجره) {
            یافت_higher_focus = true;
            اكسر;
        }
    }

    أرجع !یافت_higher_focus || w == toplevel_والد;
}

bool SDL_مجموعه_پنجره_Focusable(SDL_پنجره *پنجره, bool focusable)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(پنجره->flags & SDL_پنجره_NOT_FOCUSABLE);
    إذا ((want != have) && (_this->مجموعه_پنجره_Focusable)) {
        إذا (want) {
            پنجره->flags &= ~SDL_پنجره_NOT_FOCUSABLE;
        } وإلا {
            پنجره->flags |= SDL_پنجره_NOT_FOCUSABLE;
        }
        إذا (!_this->مجموعه_پنجره_Focusable(_this, پنجره, want)) {
            أرجع false;
        }
    }

    أرجع true;
}

bool SDL_مجموعه_پنجره_Fill_Document(SDL_پنجره *پنجره, bool fill)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((پنجره->flags & SDL_پنجره_FILL_DOCUMENT) != 0);
    إذا ((want != have) && (_this->مجموعه_پنجره_Fill_Document)) {
        إذا (!_this->مجموعه_پنجره_Fill_Document(_this, پنجره, want)) {
            أرجع false;
        } وإلا إذا (want) {
            پنجره->flags |= SDL_پنجره_FILL_DOCUMENT;
        } وإلا {
            پنجره->flags &= ~SDL_پنجره_FILL_DOCUMENT;
        }
    }

    أرجع true;
}

فراغ SDL_Update_پنجره_Grab(SDL_پنجره *پنجره)
{
    bool keyboard_grabbed, mouse_grabbed;

    إذا (پنجره->flags & SDL_پنجره_درون_داد_FOCUS) {
        إذا (SDL_GetMouse()->relative_نما || (پنجره->flags & SDL_پنجره_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } وإلا {
            mouse_grabbed = false;
        }

        إذا (پنجره->flags & SDL_پنجره_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } وإلا {
            keyboard_grabbed = false;
        }
    } وإلا {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    إذا (mouse_grabbed || keyboard_grabbed) {
        إذا (_this->grabbed_پنجره && (_this->grabbed_پنجره != پنجره)) {
            // stealing a grab from another window!
            _this->grabbed_پنجره->flags &= ~(SDL_پنجره_MOUSE_GRABBED | SDL_پنجره_KEYBOARD_GRABBED);
            إذا (_this->مجموعه_پنجره_Mouse_Grab) {
                _this->مجموعه_پنجره_Mouse_Grab(_this, _this->grabbed_پنجره, false);
            }
            إذا (_this->مجموعه_پنجره_Keyboard_Grab) {
                _this->مجموعه_پنجره_Keyboard_Grab(_this, _this->grabbed_پنجره, false);
            }
        }
        _this->grabbed_پنجره = پنجره;
    } وإلا إذا (_this->grabbed_پنجره == پنجره) {
        _this->grabbed_پنجره = عدم; // ungrabbing input.
    }

    إذا (_this->مجموعه_پنجره_Mouse_Grab) {
        إذا (!_this->مجموعه_پنجره_Mouse_Grab(_this, پنجره, mouse_grabbed)) {
            پنجره->flags &= ~SDL_پنجره_MOUSE_GRABBED;
        }
    }
    إذا (_this->مجموعه_پنجره_Keyboard_Grab) {
        إذا (!_this->مجموعه_پنجره_Keyboard_Grab(_this, پنجره, keyboard_grabbed)) {
            پنجره->flags &= ~SDL_پنجره_KEYBOARD_GRABBED;
        }
    }

    إذا (_this->grabbed_پنجره && !(_this->grabbed_پنجره->flags & (SDL_پنجره_MOUSE_GRABBED | SDL_پنجره_KEYBOARD_GRABBED))) {
        _this->grabbed_پنجره = عدم;
    }
}

bool SDL_مجموعه_پنجره_Keyboard_Grab(SDL_پنجره *پنجره, bool grabbed)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        إذا (grabbed) {
            پنجره->pending_flags |= SDL_پنجره_KEYBOARD_GRABBED;
        } وإلا {
            پنجره->pending_flags &= ~SDL_پنجره_KEYBOARD_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(پنجره->flags & SDL_پنجره_KEYBOARD_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        پنجره->flags |= SDL_پنجره_KEYBOARD_GRABBED;
    } وإلا {
        پنجره->flags &= ~SDL_پنجره_KEYBOARD_GRABBED;
    }
    SDL_Update_پنجره_Grab(پنجره);

    إذا (grabbed && !(پنجره->flags & SDL_پنجره_KEYBOARD_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_مجموعه_پنجره_Mouse_Grab(SDL_پنجره *پنجره, bool grabbed)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (پنجره->flags & SDL_پنجره_HIDDEN) {
        إذا (grabbed) {
            پنجره->pending_flags |= SDL_پنجره_MOUSE_GRABBED;
        } وإلا {
            پنجره->pending_flags &= ~SDL_پنجره_MOUSE_GRABBED;
        }
        أرجع true;
    }

    إذا (!!grabbed == !!(پنجره->flags & SDL_پنجره_MOUSE_GRABBED)) {
        أرجع true;
    }
    إذا (grabbed) {
        پنجره->flags |= SDL_پنجره_MOUSE_GRABBED;
    } وإلا {
        پنجره->flags &= ~SDL_پنجره_MOUSE_GRABBED;
    }
    SDL_Update_پنجره_Grab(پنجره);

    إذا (grabbed && !(پنجره->flags & SDL_پنجره_MOUSE_GRABBED)) {
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_پنجره_Keyboard_Grab(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    أرجع پنجره == _this->grabbed_پنجره && (_this->grabbed_پنجره->flags & SDL_پنجره_KEYBOARD_GRABBED);
}

bool SDL_Get_پنجره_Mouse_Grab(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    أرجع پنجره == _this->grabbed_پنجره && (_this->grabbed_پنجره->flags & SDL_پنجره_MOUSE_GRABBED);
}

SDL_پنجره *SDL_Get_Grabbed_پنجره(فراغ)
{
    إذا (_this && _this->grabbed_پنجره &&
        (_this->grabbed_پنجره->flags & (SDL_پنجره_MOUSE_GRABBED | SDL_پنجره_KEYBOARD_GRABBED)) != 0) {
        أرجع _this->grabbed_پنجره;
    } وإلا {
        أرجع عدم;
    }
}

bool SDL_مجموعه_پنجره_Mouse_Rect(SDL_پنجره *پنجره, ثابت SDL_Rect *rect)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!_this->مجموعه_پنجره_Mouse_Rect) {
        أرجع SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    إذا (!rect) {
        rect = &zero;
    }

    إذا (SDL_memcmp(&پنجره->mouse_rect, rect, حجم(*rect)) == 0) {
        أرجع true;
    }
    SDL_memcpy(&پنجره->mouse_rect, rect, حجم(*rect));

    أرجع _this->مجموعه_پنجره_Mouse_Rect(_this, پنجره);
}

ثابت SDL_Rect *SDL_Get_پنجره_Mouse_Rect(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, عدم);

    إذا (SDL_Rect_خالی(&پنجره->mouse_rect)) {
        أرجع عدم;
    } وإلا {
        أرجع &پنجره->mouse_rect;
    }
}

bool SDL_مجموعه_پنجره_Relative_Mouse_نما(SDL_پنجره *پنجره, bool enabled)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    إذا (enabled == SDL_Get_پنجره_Relative_Mouse_نما(پنجره)) {
        أرجع true;
    }

    إذا (enabled) {
        پنجره->flags |= SDL_پنجره_MOUSE_RELATIVE_نما;
    } وإلا {
        پنجره->flags &= ~SDL_پنجره_MOUSE_RELATIVE_نما;
    }

    إذا (!SDL_Update_Relative_Mouse_نما()) {
        إذا (enabled) {
            پنجره->flags &= ~SDL_پنجره_MOUSE_RELATIVE_نما;
        } وإلا {
            پنجره->flags |= SDL_پنجره_MOUSE_RELATIVE_نما;
        }
        أرجع false;
    }
    أرجع true;
}

bool SDL_Get_پنجره_Relative_Mouse_نما(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (پنجره->flags & SDL_پنجره_MOUSE_RELATIVE_نما) {
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

bool SDL_Flash_پنجره(SDL_پنجره *پنجره, SDL_FlashOperation operation)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (_this->Flash_پنجره) {
        أرجع _this->Flash_پنجره(_this, پنجره, operation);
    }

    أرجع SDL_Unsupported();
}

bool SDL_مجموعه_پنجره_پیشرفت_State(SDL_پنجره *پنجره, SDL_پیشرفت_State state)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    CHECK_PARAM(state < SDL_پیشرفت_STATE_NONE || state > SDL_پیشرفت_STATE_ERROR) {
        أرجع SDL_InvalidParamError("state");
    }

    پنجره->پیشرفت_state = state;

    إذا (_this->Apply_پنجره_پیشرفت) {
        إذا (!_this->Apply_پنجره_پیشرفت(_this, پنجره)) {
            أرجع false;
        }
    }

    أرجع true;
}

SDL_پیشرفت_State SDL_Get_پنجره_پیشرفت_State(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, SDL_پیشرفت_STATE_INVALID);
    CHECK_پنجره_NOT_POPUP(پنجره, SDL_پیشرفت_STATE_INVALID);

    أرجع پنجره->پیشرفت_state;
}

bool SDL_مجموعه_پنجره_پیشرفت_مقدار(SDL_پنجره *پنجره, عائم مقدار)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    مقدار = SDL_clamp(مقدار, 0.0f, 1.f);

    پنجره->پیشرفت_مقدار = مقدار;

    إذا (_this->Apply_پنجره_پیشرفت) {
        إذا (!_this->Apply_پنجره_پیشرفت(_this, پنجره)) {
            أرجع false;
        }
    }

    أرجع true;
}

عائم SDL_Get_پنجره_پیشرفت_مقدار(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, -1.0f);
    CHECK_پنجره_NOT_POPUP(پنجره, -1.0f);

    أرجع پنجره->پیشرفت_مقدار;
}

فراغ SDL_On_پنجره_Shown(SDL_پنجره *پنجره)
{
    // Set window state if we have pending window flags cached
    Apply_پنجره_Flags(پنجره, پنجره->pending_flags);
    پنجره->pending_flags = 0;
}

فراغ SDL_On_پنجره_Hidden(SDL_پنجره *پنجره)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    پنجره->pending_flags |= (پنجره->flags & (SDL_پنجره_FULLSCREEN | SDL_پنجره_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_LEAVE, false);
}

فراغ SDL_On_پنجره_Display_تغییریافته(SDL_پنجره *پنجره)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    إذا (پنجره->update_fullscreen_on_display_تغییریافته && (پنجره->flags & SDL_پنجره_FULLSCREEN)) {
        ثابت bool auto_نما_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_تطابق_EXCLUSIVE_نما_ON_MOVE, true);

        إذا (auto_نما_switch && (پنجره->requested_fullscreen_نما.w != 0 || پنجره->requested_fullscreen_نما.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_پنجره_Position(پنجره);
            bool include_بالا_density_modes = false;

            إذا (پنجره->requested_fullscreen_نما.pixel_density > 1.0f) {
                include_بالا_density_modes = true;
            }
            ثابت bool یافت_تطابق = SDL_Get_Closest_Fullscreen_Display_نما(displayID, پنجره->requested_fullscreen_نما.w, پنجره->requested_fullscreen_نما.h,
                                                                         پنجره->requested_fullscreen_نما.refresh_نرخ, include_بالا_density_modes, &پنجره->current_fullscreen_نما);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            إذا (!یافت_تطابق ||
                پنجره->requested_fullscreen_نما.w != پنجره->current_fullscreen_نما.w ||
                پنجره->requested_fullscreen_نما.h != پنجره->current_fullscreen_نما.h) {
                SDL_zero(پنجره->current_fullscreen_نما);
            }
        } وإلا {
            SDL_zero(پنجره->current_fullscreen_نما);
        }

        إذا (SDL_پنجره_FULLSCREEN_VISIBLE(پنجره)) {
            SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_پنجره_Pixel_اندازه_تغییریافته(پنجره);
}

فراغ SDL_On_پنجره_Moved(SDL_پنجره *پنجره)
{
    SDL_Check_پنجره_Display_تغییریافته(پنجره);
}

فراغ SDL_On_پنجره_Resized(SDL_پنجره *پنجره)
{
    SDL_Check_پنجره_Display_تغییریافته(پنجره);
    SDL_Check_پنجره_Pixel_اندازه_تغییریافته(پنجره);
    SDL_Check_پنجره_امن_Area_تغییریافته(پنجره);

    إذا ((پنجره->flags & SDL_پنجره_TRANSPARENT) && _this->Update_پنجره_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_اشاره_گر_Property(پنجره->props, SDL_PROP_پنجره_SHAPE_اشاره_گر, عدم);
        إذا (surface) {
            _this->Update_پنجره_Shape(_this, پنجره, surface);
        }
    }
}

فراغ SDL_Check_پنجره_Pixel_اندازه_تغییریافته(SDL_پنجره *پنجره)
{
    صحيح pixel_w = 0, pixel_h = 0;

    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &pixel_w, &pixel_h);
    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_PIXEL_اندازه_تغییریافته, pixel_w, pixel_h);

    SDL_Check_پنجره_Display_Scale_تغییریافته(پنجره);
}

فراغ SDL_On_پنجره_Pixel_اندازه_تغییریافته(SDL_پنجره *پنجره)
{
    پنجره->surface_valid = false;
}

فراغ SDL_On_پنجره_زنده_Resize_Update(SDL_پنجره *پنجره)
{
    إذا (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } وإلا {
        // Send an expose event so the application can redraw
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ساكن فراغ SDL_Check_پنجره_امن_Area_تغییریافته(SDL_پنجره *پنجره)
{
    SDL_Rect rect;

    rect.x = پنجره->امن_inset_چپ;
    rect.y = پنجره->امن_inset_بالاترین;
    rect.w = پنجره->w - (پنجره->امن_inset_راست + پنجره->امن_inset_چپ);
    rect.h = پنجره->h - (پنجره->امن_inset_بالاترین + پنجره->امن_inset_bottom);
    إذا (SDL_memcmp(&rect, &پنجره->امن_rect, حجم(rect)) != 0) {
        SDL_copyp(&پنجره->امن_rect, &rect);
        SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_امن_AREA_تغییریافته, 0, 0);
    }
}

فراغ SDL_مجموعه_پنجره_امن_Area_Insets(SDL_پنجره *پنجره, صحيح چپ, صحيح راست, صحيح بالاترین, صحيح bottom)
{
    پنجره->امن_inset_چپ = چپ;
    پنجره->امن_inset_راست = راست;
    پنجره->امن_inset_بالاترین = بالاترین;
    پنجره->امن_inset_bottom = bottom;
    SDL_Check_پنجره_امن_Area_تغییریافته(پنجره);
}

bool SDL_Get_پنجره_امن_Area(SDL_پنجره *پنجره, SDL_Rect *rect)
{
    إذا (rect) {
        SDL_zerop(rect);
    }

    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (rect) {
        إذا (SDL_Rect_خالی(&پنجره->امن_rect)) {
            rect->w = پنجره->w;
            rect->h = پنجره->h;
        } وإلا {
            SDL_copyp(rect, &پنجره->امن_rect);
        }
    }
    أرجع true;
}

فراغ SDL_On_پنجره_Minimized(SDL_پنجره *پنجره)
{
    إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

فراغ SDL_On_پنجره_Maximized(SDL_پنجره *پنجره)
{
}

فراغ SDL_On_پنجره_Restored(SDL_پنجره *پنجره)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    إذا (پنجره->flags & SDL_پنجره_FULLSCREEN) {
        SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

فراغ SDL_On_پنجره_Enter(SDL_پنجره *پنجره)
{
    إذا (_this->On_پنجره_Enter) {
        _this->On_پنجره_Enter(_this, پنجره);
    }
    SDL_Update_Relative_Mouse_نما();
}

فراغ SDL_On_پنجره_Leave(SDL_پنجره *پنجره)
{
    SDL_Update_Relative_Mouse_نما();
}

فراغ SDL_On_پنجره_Focus_Gained(SDL_پنجره *پنجره)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    إذا (mouse && mouse->relative_نما) {
        SDL_مجموعه_Mouse_Focus(پنجره);
    }

    SDL_Update_پنجره_Grab(پنجره);
}

ساكن bool SDL_ShouldMinimizeOnFocusLoss(SDL_پنجره *پنجره)
{
    ثابت حرف *hint;

    إذا (!(پنجره->flags & SDL_پنجره_FULLSCREEN) || پنجره->is_destroying) {
        أرجع false;
    }

#إذا defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    إذا (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        إذا (Cocoa_IsShowingModalDialog(پنجره)) {
            أرجع false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } وإلا إذا (Cocoa_Is_پنجره_درون_Fullscreen_Space(پنجره)) {
            أرجع false;
        }
    }
#پایان_اگر

#اگر_تعریف_شده SDL_PLATFORM_ANDROID
    {
        خارجي bool Android_JNI_ShouldMinimizeOnFocusLoss(فراغ);
        إذا (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            أرجع false;
        }
    }
#پایان_اگر

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    إذا (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        إذا (پنجره->fullscreen_exclusive && !SDL_نما_Switching_Emulated(_this)) {
            أرجع true;
        } وإلا {
            أرجع false;
        }
    }
    أرجع SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

فراغ SDL_On_پنجره_Focus_گمشده(SDL_پنجره *پنجره)
{
    SDL_Update_پنجره_Grab(پنجره);

    إذا (SDL_ShouldMinimizeOnFocusLoss(پنجره)) {
        SDL_Minimize_پنجره(پنجره);
    }
}

SDL_پنجره *SDL_GetToplevelForKeyboardFocus(فراغ)
{
    SDL_پنجره *focus = SDL_GetKeyboardFocus();

    إذا (focus) {
        // Get the toplevel parent window.
        طالما (focus->والد) {
            focus = focus->والد;
        }
    }

    أرجع focus;
}

bool SDL_جمع_کن_پنجره_Renderer(SDL_پنجره *پنجره, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(پنجره->renderers, (پنجره->رقم_renderers + 1) * حجم(*renderers));
    إذا (!renderers) {
        أرجع false;
    }

    پنجره->renderers = renderers;
    پنجره->renderers[پنجره->رقم_renderers++] = renderer;

    SDL_مجموعه_اشاره_گر_Property(SDL_Get_پنجره_Properties(پنجره), SDL_PROP_پنجره_RENDERER_اشاره_گر, renderer);
    أرجع true;
}

فراغ SDL_Remove_پنجره_Renderer(SDL_پنجره *پنجره, SDL_Renderer *renderer)
{
    لكل (صحيح i = 0; i < پنجره->رقم_renderers; ++i) {
        إذا (پنجره->renderers[i] == renderer) {
            إذا (i < (پنجره->رقم_renderers - 1)) {
                SDL_memmove(&پنجره->renderers[i], &پنجره->renderers[i + 1], (پنجره->رقم_renderers - i - 1) * حجم(پنجره->renderers[i]));
            }
            --پنجره->رقم_renderers;
            اكسر;
        }
    }

    SDL_PropertiesID props = SDL_Get_پنجره_Properties(پنجره);
    إذا (SDL_Get_اشاره_گر_Property(props, SDL_PROP_پنجره_RENDERER_اشاره_گر, عدم) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_پنجره_RENDERER_اشاره_گر);
    }
}

فراغ SDL_Destroy_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره,);

    پنجره->is_destroying = true;

    // Destroy any child windows of this window
    طالما (پنجره->اولی_فرزند) {
        SDL_Destroy_پنجره(پنجره->اولی_فرزند);
    }

    SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_DESTROYED, 0, 0);

    SDL_Destroy_پنجره_Surface(پنجره);

    SDL_Renderer *renderer = SDL_GetRenderer(پنجره);
    إذا (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_نما(پنجره, SDL_FULLSCREEN_OP_LEAVE, true);
    إذا (!(پنجره->flags & SDL_پنجره_EXTERNAL)) {
        SDL_Hide_پنجره(پنجره);
    }

    SDL_DestroyProperties(پنجره->متن_درون_داد_props);

    SDL_Destroy_پنجره_Texture(_this, پنجره);
    SDL_DestroyProperties(پنجره->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    إذا (_this->مجموعه_پنجره_Modal && (پنجره->flags & SDL_پنجره_MODAL)) {
        _this->مجموعه_پنجره_Modal(_this, پنجره, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    لكل (صحيح i = 0; i < _this->رقم_displays; ++i) {
        إذا (_this->displays[i]->fullscreen_پنجره == پنجره) {
            _this->displays[i]->fullscreen_پنجره = عدم;
        }
    }

    // Make sure this window no longer has focus
    إذا (SDL_GetKeyboardFocus() == پنجره) {
        SDL_مجموعه_Keyboard_Focus(عدم);
    }
    إذا ((پنجره->flags & SDL_پنجره_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    إذا (SDL_GetMouseFocus() == پنجره) {
        SDL_مجموعه_Mouse_Focus(عدم);
    }

    // Make no context current if this is the current context window
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        إذا (_this->current_glwin == پنجره) {
            SDL_GL_MakeCurrent(پنجره, عدم);
        }
    }

    إذا (_this->Destroy_پنجره) {
        _this->Destroy_پنجره(_this, پنجره);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    إذا (پنجره->flags & SDL_پنجره_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    إذا (پنجره->flags & SDL_پنجره_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    إذا (_this->grabbed_پنجره == پنجره) {
        _this->grabbed_پنجره = عدم; // ungrabbing input.
    }

    إذا (_this->current_glwin == پنجره) {
        _this->current_glwin = عدم;
    }

    SDL_Compare_And_جابجا_Atomic_اشاره_گر(&_this->wakeup_پنجره, پنجره, عدم);

    // Now invalidate magic
    SDL_مجموعه_Object_Valid(پنجره, SDL_OBJECT_TYPE_پنجره, false);

    // Free memory associated with the window
    SDL_free(پنجره->title);
    SDL_DestroySurface(پنجره->icon);

    // Unlink the window from its siblings.
    SDL_Update_پنجره_Hierarchy(پنجره, عدم);

    // Unlink the window from the global window list
    إذا (پنجره->بعدی) {
        پنجره->بعدی->prev = پنجره->prev;
    }
    إذا (پنجره->prev) {
        پنجره->prev->بعدی = پنجره->بعدی;
    } وإلا {
        _this->windows = پنجره->بعدی;
    }

    SDL_free(پنجره->renderers);
    SDL_free(پنجره);

#اگر_تعریف_شده SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#پایان_اگر
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
#پایان_اگر
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    طالما (_this->windows) {
        SDL_Destroy_پنجره(_this->windows);
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

    لكل (i = _this->رقم_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->رقم_displays == 0);
    SDL_free(_this->displays);
    _this->displays = عدم;

    SDL_Cancel_Clipboard_داده(0);

    إذا (_this->primary_selection_متن) {
        SDL_free(_this->primary_selection_متن);
        _this->primary_selection_متن = عدم;
    }
    _this->حرر(_this);
    _this = عدم;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_بارگیری_Library(ثابت حرف *مسیر)
{
    bool نتیجه;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->gl_config.driver_loaded) {
        إذا (مسیر && SDL_strcmp(مسیر, _this->gl_config.driver_مسیر) != 0) {
            أرجع SDL_مجموعه_Error("OpenGL library already loaded");
        }
        نتیجه = true;
    } وإلا {
        إذا (!_this->GL_بارگیری_Library) {
            أرجع SDL_DllNotSupported("OpenGL");
        }
        نتیجه = _this->GL_بارگیری_Library(_this, مسیر);
    }
    إذا (نتیجه) {
        ++_this->gl_config.driver_loaded;
    } وإلا {
        إذا (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    أرجع نتیجه;
}

SDL_Function_اشاره_گر SDL_GL_Get_Proc_آدرس(ثابت حرف *proc)
{
    SDL_Function_اشاره_گر func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;
    إذا (_this->GL_Get_Proc_آدرس) {
        إذا (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_آدرس(_this, proc);
        } وإلا {
            SDL_مجموعه_Error("No GL driver has been loaded");
        }
    } وإلا {
        SDL_مجموعه_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    أرجع func;
}

SDL_Function_اشاره_گر SDL_EGL_Get_Proc_آدرس(ثابت حرف *proc)
{
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    SDL_Function_اشاره_گر func;

    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    func = عدم;

    إذا (_this->egl_داده) {
        func = SDL_EGL_Get_Proc_آدرس_داخلی(_this, proc);
    } وإلا {
        SDL_مجموعه_Error("No EGL library has been loaded");
    }

    أرجع func;
#وإلا
    SDL_مجموعه_Error("SDL was not built with EGL support");
    أرجع عدم;
#پایان_اگر
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
#اگر_تعریف_نشده SDL_VIDEO_OPENGL
تعريفنوع ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint شاخص);
#پایان_اگر

ساكن SDL_INLINE bool is_At_کمترین_GL3(ثابت حرف *verstr)
{
    أرجع verstr && (SDL_atoi(verstr) >= 3);
}
#پایان_اگر // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

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

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_آدرس("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (is_At_کمترین_GL3((ثابت حرف *)glGetStringFunc(GL_نسخه))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint رقم_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_آدرس("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_آدرس("glGetIntegerv");
        إذا ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            أرجع false;
        }

#اگر_تعریف_نشده GL_رقم_EXTENSIONS
#تعریف_کن GL_رقم_EXTENSIONS 0x821D
#پایان_اگر
        glGetIntegervFunc(GL_رقم_EXTENSIONS, &رقم_exts);
        لكل (i = 0; i < رقم_exts; i++) {
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
#پایان_اگر
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
#پایان_اگر
}

فراغ SDL_EGL_مجموعه_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
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

فراغ SDL_GL_Reset_صفات(فراغ)
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
    _this->gl_config.میانگیر_اندازه = 0;
    _this->gl_config.عمق_اندازه = 16;
    _this->gl_config.stencil_اندازه = 0;
    _this->gl_config.double_میانگیر = 1;
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

#اگر_تعریف_شده SDL_VIDEO_OPENGL
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
#پایان_اگر

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    إذا (_this->GL_مجموعه_Default_Profile_Config) {
        _this->GL_مجموعه_Default_Profile_Config(_this);
    }
}

bool SDL_GL_مجموعه_Attribute(SDL_GLAttr attr, صحيح مقدار)
{
#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool نتیجه;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    نتیجه = true;
    بدل (attr) {
    حالة SDL_GL_RED_اندازه:
        _this->gl_config.red_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_GREEN_اندازه:
        _this->gl_config.green_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_BLUE_اندازه:
        _this->gl_config.blue_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_ALPHA_اندازه:
        _this->gl_config.alpha_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_میانگیر = مقدار;
        اكسر;
    حالة SDL_GL_میانگیر_اندازه:
        _this->gl_config.میانگیر_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_عمق_اندازه:
        _this->gl_config.عمق_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_STENCIL_اندازه:
        _this->gl_config.stencil_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_ACCUM_RED_اندازه:
        _this->gl_config.accum_red_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_اندازه:
        _this->gl_config.accum_green_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_اندازه:
        _this->gl_config.accum_blue_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_اندازه:
        _this->gl_config.accum_alpha_اندازه = مقدار;
        اكسر;
    حالة SDL_GL_STEREO:
        _this->gl_config.stereo = مقدار;
        اكسر;
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = مقدار;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = مقدار;
        اكسر;
    حالة SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = مقدار;
        اكسر;
    حالة SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = مقدار;
        اكسر;
    حالة SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = مقدار;
        اكسر;
    حالة SDL_GL_CONTEXT_MAJOR_نسخه:
        _this->gl_config.major_نسخه = مقدار;
        اكسر;
    حالة SDL_GL_CONTEXT_MINOR_نسخه:
        _this->gl_config.minor_نسخه = مقدار;
        اكسر;
    حالة SDL_GL_CONTEXT_FLAGS:
        إذا (مقدار & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            نتیجه = SDL_مجموعه_Error("Unknown OpenGL context flag %d", مقدار);
            اكسر;
        }
        _this->gl_config.flags = مقدار;
        اكسر;
    حالة SDL_GL_CONTEXT_PROFILE_ماسک:
        إذا (مقدار != 0 &&
            مقدار != SDL_GL_CONTEXT_PROFILE_CORE &&
            مقدار != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            مقدار != SDL_GL_CONTEXT_PROFILE_ES) {
            نتیجه = SDL_مجموعه_Error("Unknown OpenGL context profile %d", مقدار);
            اكسر;
        }
        _this->gl_config.profile_ماسک = مقدار;
        اكسر;
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = مقدار;
        اكسر;
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = مقدار;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = مقدار;
        اكسر;
    حالة SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = مقدار;
        اكسر;
    حالة SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = مقدار;
        اكسر;
    حالة SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = مقدار;
        اكسر;
    افتراضي:
        نتیجه = SDL_مجموعه_Error("Unknown OpenGL attribute");
        اكسر;
    }
    أرجع نتیجه;
#وإلا
    أرجع SDL_Unsupported();
#پایان_اگر // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحيح *مقدار)
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
#اگر_تعریف_شده SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_پشت_چپ;
    GLenum attachmentattrib = 0;
#پایان_اگر

    CHECK_PARAM(!مقدار) {
        أرجع SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *مقدار = 0;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    بدل (attr) {
    حالة SDL_GL_RED_اندازه:
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_اندازه;
#پایان_اگر
        attrib = GL_RED_بیتها;
        اكسر;
    حالة SDL_GL_BLUE_اندازه:
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_اندازه;
#پایان_اگر
        attrib = GL_BLUE_بیتها;
        اكسر;
    حالة SDL_GL_GREEN_اندازه:
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_اندازه;
#پایان_اگر
        attrib = GL_GREEN_بیتها;
        اكسر;
    حالة SDL_GL_ALPHA_اندازه:
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_اندازه;
#پایان_اگر
        attrib = GL_ALPHA_بیتها;
        اكسر;
    حالة SDL_GL_DOUBLEBUFFER:
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        اكسر;
#وإلا
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *مقدار = _this->gl_config.double_میانگیر;
        أرجع true;
#پایان_اگر
    حالة SDL_GL_عمق_اندازه:
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        attachment = GL_عمق;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_عمق_اندازه;
#پایان_اگر
        attrib = GL_عمق_بیتها;
        اكسر;
    حالة SDL_GL_STENCIL_اندازه:
#اگر_تعریف_شده SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_اندازه;
#پایان_اگر
        attrib = GL_STENCIL_بیتها;
        اكسر;
#اگر_تعریف_شده SDL_VIDEO_OPENGL
    حالة SDL_GL_ACCUM_RED_اندازه:
        attrib = GL_ACCUM_RED_بیتها;
        اكسر;
    حالة SDL_GL_ACCUM_GREEN_اندازه:
        attrib = GL_ACCUM_GREEN_بیتها;
        اكسر;
    حالة SDL_GL_ACCUM_BLUE_اندازه:
        attrib = GL_ACCUM_BLUE_بیتها;
        اكسر;
    حالة SDL_GL_ACCUM_ALPHA_اندازه:
        attrib = GL_ACCUM_ALPHA_بیتها;
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
        *مقدار = 0;
        أرجع true;
#پایان_اگر
    حالة SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        اكسر;
    حالة SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        اكسر;
    حالة SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        اكسر;
    حالة SDL_GL_میانگیر_اندازه:
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

        *مقدار = rsize + gsize + bsize + asize;
        أرجع true;
    }
    حالة SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *مقدار = (_this->gl_config.accelerated != 0);
        أرجع true;
    }
    حالة SDL_GL_RETAINED_BACKING:
    {
        *مقدار = _this->gl_config.retained_backing;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MAJOR_نسخه:
    {
        *مقدار = _this->gl_config.major_نسخه;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_MINOR_نسخه:
    {
        *مقدار = _this->gl_config.minor_نسخه;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_FLAGS:
    {
        *مقدار = _this->gl_config.flags;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_PROFILE_ماسک:
    {
        *مقدار = _this->gl_config.profile_ماسک;
        أرجع true;
    }
    حالة SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *مقدار = _this->gl_config.share_with_current_context;
        أرجع true;
    }
    حالة SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *مقدار = _this->gl_config.framebuffer_srgb_capable;
        أرجع true;
    }
    حالة SDL_GL_CONTEXT_NO_ERROR:
    {
        *مقدار = _this->gl_config.no_error;
        أرجع true;
    }
    حالة SDL_GL_EGL_PLATFORM:
    {
        *مقدار = _this->gl_config.egl_platform;
        أرجع true;
    }
    حالة SDL_GL_FLOATBUFFERS:
    {
        إذا (_this->gl_config.HAS_GL_ARB_color_میانگیر_float) {
            attrib = GL_RGBA_FLOAT_نما_ARB;
            اكسر;
        } وإلا {
            أرجع 0;
        }
    }
    افتراضي:
        أرجع SDL_مجموعه_Error("Unknown OpenGL attribute");
    }

#اگر_تعریف_شده SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_آدرس("glGetString");
    إذا (!glGetStringFunc) {
        أرجع false;
    }

    إذا (attachmentattrib && is_At_کمترین_GL3((ثابت حرف *)glGetStringFunc(GL_نسخه))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_آدرس("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_آدرس("glBindFramebuffer");
        إذا (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_آدرس("glGetFramebufferAttachmentParameteriv");
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
            إذا (attachment == GL_عمق || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            إذا (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)مقدار);
            } وإلا {
                *مقدار = 0;
            }
            إذا (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } وإلا {
            أرجع false;
        }
    } وإلا
#پایان_اگر
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_آدرس("glGetIntegerv");
        إذا (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)مقدار);
        } وإلا {
            أرجع false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_آدرس("glGetError");
    إذا (!glGetErrorFunc) {
        أرجع false;
    }

    error = glGetErrorFunc();
    إذا (error != GL_NO_ERROR) {
        إذا (error == GL_INVALID_ENUM) {
            أرجع SDL_مجموعه_Error("OpenGL error: GL_INVALID_ENUM");
        } وإلا إذا (error == GL_INVALID_مقدار) {
            أرجع SDL_مجموعه_Error("OpenGL error: GL_INVALID_VALUE");
        }
        أرجع SDL_مجموعه_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    إذا (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *مقدار = (*مقدار == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    أرجع true;
#وإلا
    أرجع SDL_Unsupported();
#پایان_اگر // SDL_VIDEO_OPENGL
}

#تعریف_کن NOT_AN_OPENGL_پنجره "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_پنجره *پنجره)
{
    SDL_GLContext ctx = عدم;
    CHECK_پنجره_MAGIC(پنجره, عدم);

    إذا (!(پنجره->flags & SDL_پنجره_OPENGL)) {
        SDL_مجموعه_Error(NOT_AN_OPENGL_پنجره);
        أرجع عدم;
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحيح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    إذا (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#پایان_اگر

    ctx = _this->GL_CreateContext(_this, پنجره);

    // Creating a context is assumed to make it current in the SDL driver.
    إذا (ctx) {
        _this->current_glwin = پنجره;
        _this->current_glctx = ctx;
        SDL_مجموعه_TLS(&_this->current_glwin_tls, پنجره, عدم);
        SDL_مجموعه_TLS(&_this->current_glctx_tls, ctx, عدم);
    }

#إذا defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    إذا (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_آدرس(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_آدرس("glGetString");
        إذا (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            إذا (_this->gl_config.profile_ماسک & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } وإلا {
                supported = is_At_کمترین_GL3((ثابت حرف *)glGetStringFunc(GL_نسخه)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            إذا (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#پایان_اگر

    أرجع ctx;
}

bool SDL_GL_MakeCurrent(SDL_پنجره *پنجره, SDL_GLContext context)
{
    bool نتیجه;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }

    إذا (پنجره == SDL_GL_Get_Current_پنجره() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        أرجع true;
    }

    إذا (!context) {
        پنجره = عدم;
    } وإلا إذا (پنجره) {
        CHECK_پنجره_MAGIC(پنجره, false);

        إذا (!(پنجره->flags & SDL_پنجره_OPENGL)) {
            أرجع SDL_مجموعه_Error(NOT_AN_OPENGL_پنجره);
        }
    } وإلا إذا (!_this->gl_allow_no_surface) {
        أرجع SDL_مجموعه_Error("Use of OpenGL without a window is not supported on this platform");
    }

    نتیجه = _this->GL_MakeCurrent(_this, پنجره, context);
    إذا (نتیجه) {
        _this->current_glwin = پنجره;
        _this->current_glctx = context;
        SDL_مجموعه_TLS(&_this->current_glwin_tls, پنجره, عدم);
        SDL_مجموعه_TLS(&_this->current_glctx_tls, context, عدم);
    }
    أرجع نتیجه;
}

SDL_پنجره *SDL_GL_Get_Current_پنجره(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    أرجع (SDL_پنجره *)SDL_GetTLS(&_this->current_glwin_tls);
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
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع EGL_NO_DISPLAY;
    }
    إذا (!_this->egl_داده) {
        SDL_مجموعه_Error("There is no current EGL display");
        أرجع EGL_NO_DISPLAY;
    }
    أرجع _this->egl_داده->egl_display;
#وإلا
    SDL_مجموعه_Error("SDL was not built with EGL support");
    أرجع عدم;
#پایان_اگر
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(فراغ)
{
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_داده) {
        SDL_مجموعه_Error("There is no current EGL display");
        أرجع عدم;
    }
    أرجع _this->egl_داده->egl_config;
#وإلا
    SDL_مجموعه_Error("SDL was not built with EGL support");
    أرجع عدم;
#پایان_اگر
}

SDL_EGLConfig SDL_EGL_Get_پنجره_Surface(SDL_پنجره *پنجره)
{
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->egl_داده) {
        SDL_مجموعه_Error("There is no current EGL display");
        أرجع عدم;
    }
    إذا (_this->GL_GetEGLSurface) {
        أرجع _this->GL_GetEGLSurface(_this, پنجره);
    }
    أرجع عدم;
#وإلا
    SDL_مجموعه_Error("SDL was not built with EGL support");
    أرجع عدم;
#پایان_اگر
}

bool SDL_GL_مجموعه_جابجا_Interval(صحيح interval)
{
    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_مجموعه_Error("No OpenGL context has been made current");
    } وإلا إذا (_this->GL_مجموعه_جابجا_Interval) {
        أرجع _this->GL_مجموعه_جابجا_Interval(_this, interval);
    } وإلا {
        أرجع SDL_مجموعه_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_جابجا_Interval(صحيح *interval)
{
    CHECK_PARAM(!interval) {
       أرجع SDL_InvalidParamError("interval");
    }

    *interval = 0;

    إذا (!_this) {
        أرجع SDL_مجموعه_Error("no video driver");
    } وإلا إذا (SDL_GL_GetCurrentContext() == عدم) {
        أرجع SDL_مجموعه_Error("no current context");
    } وإلا إذا (_this->GL_Get_جابجا_Interval) {
        أرجع _this->GL_Get_جابجا_Interval(_this, interval);
    } وإلا {
        أرجع SDL_مجموعه_Error("not implemented");
    }
}

bool SDL_GL_جابجا_پنجره(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!(پنجره->flags & SDL_پنجره_OPENGL)) {
        أرجع SDL_مجموعه_Error(NOT_AN_OPENGL_پنجره);
    }

    إذا (SDL_GL_Get_Current_پنجره() != پنجره) {
        أرجع SDL_مجموعه_Error("The specified window has not been made current");
    }

    أرجع _this->GL_جابجا_پنجره(_this, پنجره);
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
ساكن فراغ Create_ماسک_From_Color_کلید_Or_Alpha(SDL_Surface *icon, Uint8 *ماسک, صحيح flags)
{
    صحيح x, y;
    Uint32 colorkey;
#تعریف_کن مجموعه_MASKBIT(icon, x, y, ماسک) \
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
                        مجموعه_MASKBIT(icon, x, y, ماسک);
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
                        مجموعه_MASKBIT(icon, x, y, ماسک);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        مجموعه_MASKBIT(icon, x, y, ماسک);
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
                        مجموعه_MASKBIT(icon, x, y, ماسک);
                    } وإلا إذا ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        مجموعه_MASKBIT(icon, x, y, ماسک);
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
فراغ SDL_WM_مجموعه_Icon(SDL_Surface *icon, Uint8 *ماسک)
{
    إذا (icon && _this->مجموعه_Icon) {
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
                Create_ماسک_From_Color_کلید_Or_Alpha(icon, ماسک, flags);
            }
            _this->مجموعه_Icon(_this, icon, ماسک);
            SDL_free(ماسک);
        } وإلا {
            _this->مجموعه_Icon(_this, icon, ماسک);
        }
    }
}
#پایان_اگر

SDL_متن_درون_داد_Type SDL_Get_متن_درون_داد_Type(SDL_PropertiesID props)
{
    أرجع (SDL_متن_درون_داد_Type)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_TYPE_عدد, SDL_TEXTINPUT_TYPE_متن);
}

SDL_Capitalization SDL_Get_متن_درون_داد_Capitalization(SDL_PropertiesID props)
{
    إذا (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_عدد)) {
        أرجع (SDL_Capitalization)SDL_Get_عدد_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_عدد, SDL_CAPITALIZE_NONE);
    }

    بدل (SDL_Get_متن_درون_داد_Type(props)) {
    حالة SDL_TEXTINPUT_TYPE_متن:
        أرجع SDL_CAPITALIZE_SENTENCES;
    حالة SDL_TEXTINPUT_TYPE_متن_NAME:
        أرجع SDL_CAPITALIZE_واژگان;
    افتراضي:
        أرجع SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_متن_درون_داد_Autocorrect(SDL_PropertiesID props)
{
    أرجع SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_متن_درون_داد_Multiline(SDL_PropertiesID props)
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

bool SDL_شروع_متن_درون_داد(SDL_پنجره *پنجره)
{
    أرجع SDL_شروع_متن_درون_داد_With_Properties(پنجره, 0);
}

bool SDL_شروع_متن_درون_داد_With_Properties(SDL_پنجره *پنجره, SDL_PropertiesID props)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (پنجره->متن_درون_داد_props) {
        SDL_DestroyProperties(پنجره->متن_درون_داد_props);
        پنجره->متن_درون_داد_props = 0;
    }

    إذا (props) {
        پنجره->متن_درون_داد_props = SDL_CreateProperties();
        إذا (!پنجره->متن_درون_داد_props) {
            أرجع false;
        }
        إذا (!SDL_CopyProperties(props, پنجره->متن_درون_داد_props)) {
            أرجع false;
        }
    }

    إذا (_this->مجموعه_متن_درون_داد_Properties) {
        _this->مجموعه_متن_درون_داد_Properties(_this, پنجره, props);
    }

    إذا (!پنجره->متن_درون_داد_فعال) {
        // Start the text input system
        إذا (_this->شروع_متن_درون_داد) {
            إذا (!_this->شروع_متن_درون_داد(_this, پنجره, props)) {
                أرجع false;
            }
        }
        پنجره->متن_درون_داد_فعال = true;
    }

    // Show the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(پنجره)) {
        إذا (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, پنجره, props);
        }
    }
    أرجع true;
}

bool SDL_متن_درون_داد_فعال(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    أرجع پنجره->متن_درون_داد_فعال;
}

bool SDL_Stop_متن_درون_داد(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (پنجره->متن_درون_داد_فعال) {
        // Stop the text input system
        إذا (_this->Stop_متن_درون_داد) {
            _this->Stop_متن_درون_داد(_this, پنجره);
        }
        پنجره->متن_درون_داد_فعال = false;
    }

    // Hide the on-screen keyboard, if desired
    إذا (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(پنجره)) {
        إذا (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, پنجره);
        }
    }
    أرجع true;
}

bool SDL_مجموعه_متن_درون_داد_Area(SDL_پنجره *پنجره, ثابت SDL_Rect *rect, صحيح cursor)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (rect) {
        SDL_copyp(&پنجره->متن_درون_داد_rect, rect);
        پنجره->متن_درون_داد_cursor = cursor;
    } وإلا {
        SDL_zero(پنجره->متن_درون_داد_rect);
        پنجره->متن_درون_داد_cursor = 0;
    }

    إذا (_this && _this->Update_متن_درون_داد_Area) {
        إذا (!_this->Update_متن_درون_داد_Area(_this, پنجره)) {
            أرجع false;
        }
    }
    أرجع true;
}

bool SDL_Get_متن_درون_داد_Area(SDL_پنجره *پنجره, SDL_Rect *rect, صحيح *cursor)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (rect) {
        SDL_copyp(rect, &پنجره->متن_درون_داد_rect);
    }
    إذا (cursor) {
        *cursor = پنجره->متن_درون_داد_cursor;
    }
    أرجع true;
}

bool SDL_ClearComposition(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (_this->ClearComposition) {
        أرجع _this->ClearComposition(_this, پنجره);
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

bool SDL_ScreenKeyboardShown(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, false);

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
        SDL_افزودن_Event(&event);
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
        SDL_افزودن_Event(&event);
    }
}

صحيح SDL_Get_پیام_Box_شمار(فراغ)
{
    أرجع SDL_GetAtomicInt(&SDL_messagebox_شمار);
}

bool SDL_Show_پیام_Box(ثابت SDL_پیام_Box_داده *messageboxdata, صحيح *buttonID)
{
    صحيح dummybutton;
    bool نتیجه = false;
    bool show_cursor_prev;
    SDL_پنجره *current_پنجره;
    SDL_پیام_Box_داده mbdata;

    CHECK_PARAM(!messageboxdata) {
        أرجع SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        أرجع SDL_مجموعه_Error("Invalid number of buttons");
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

    إذا (messageboxdata->پیام) {
        ثابت size_t slen = SDL_strlen(messageboxdata->پیام) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        إذا (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            أرجع false;
        }
        SDL_memcpy(msgcpy, messageboxdata->پیام, slen);
    }

    (فراغ)SDL_AtomicIncRef(&SDL_messagebox_شمار);

    current_پنجره = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_مجموعه_Relative_Mouse_نما(false);
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
    mbdata.پیام = msgcpy;
    إذا (!mbdata.پیام) {
        mbdata.پیام = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    إذا (_this && _this->Show_پیام_Box) {
        نتیجه = _this->Show_پیام_Box(_this, messageboxdata, buttonID);
    } وإلا {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        إذا (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            طالما (driver_attempt && (*driver_attempt != 0) && !نتیجه) {
                ثابت حرف *driver_attempt_انتها = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_انتها) ? (driver_attempt_انتها - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                لكل (صحيح i = 0; bootstrap[i]; ++i) {
                    إذا (bootstrap[i]->Show_پیام_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        إذا (bootstrap[i]->Show_پیام_Box(messageboxdata, buttonID)) {
                            نتیجه = true;
                        }
                        اكسر;
                    }
                }

                driver_attempt = (driver_attempt_انتها) ? (driver_attempt_انتها + 1) : عدم;
            }
        } وإلا {
            لكل (صحيح i = 0; bootstrap[i]; ++i) {
                إذا (bootstrap[i]->Show_پیام_Box && bootstrap[i]->Show_پیام_Box(messageboxdata, buttonID)) {
                    نتیجه = true;
                    اكسر;
                }
            }
        }
    }

    إذا (!نتیجه) {
        ثابت حرف *error = SDL_GetError();

        إذا (!*error) {
            SDL_مجموعه_Error("No message system available");
        }
    } وإلا {
        SDL_ClearError();
    }

    (فراغ)SDL_AtomicDecRef(&SDL_messagebox_شمار);

    إذا (current_پنجره) {
        SDL_Raise_پنجره(current_پنجره);
    }

    إذا (!show_cursor_prev) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_نما();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    أرجع نتیجه;
}

bool SDL_Show_Simple_پیام_Box(SDL_پیام_Box_Flags flags, ثابت حرف *title, ثابت حرف *پیام, SDL_پنجره *پنجره)
{
#إذا defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_راست;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_راست = gsp_Has_Gpu_راست();
    إذا (!has_Gpu_راست)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_متن_کلمه_WRAP, CFG_LANGUAGE_EN);
    error_متن(&errCnf, پیام);
    errorDisp(&errCnf);

    إذا (!has_Gpu_راست)
        gfxExit();

    أرجع true;
#وإلا
    SDL_پیام_Box_داده داده;
    SDL_پیام_Box_Button_داده button;

    SDL_zero(داده);
    داده.flags = flags;
    داده.title = title;
    داده.پیام = پیام;
    داده.numbuttons = 1;
    داده.buttons = &button;
    داده.پنجره = پنجره;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.متن = "OK";

    أرجع SDL_Show_پیام_Box(&داده, عدم);
#پایان_اگر
}

bool SDL_ShouldAllowTopmost(فراغ)
{
    أرجع SDL_GetHintBoolean(SDL_HINT_پنجره_ALLOW_TOPMOST, true);
}

bool SDL_Show_پنجره_System_Menu(SDL_پنجره *پنجره, صحيح x, صحيح y)
{
    CHECK_پنجره_MAGIC(پنجره, false);
    CHECK_پنجره_NOT_POPUP(پنجره, false);

    إذا (_this->Show_پنجره_System_Menu) {
        _this->Show_پنجره_System_Menu(پنجره, x, y);
        أرجع true;
    }

    أرجع SDL_Unsupported();
}

bool SDL_مجموعه_پنجره_اصابت_Test(SDL_پنجره *پنجره, SDL_اصابت_Test callback, فراغ *callback_داده)
{
    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!_this->مجموعه_پنجره_اصابت_Test) {
        أرجع SDL_Unsupported();
    }

    پنجره->اصابت_test = callback;
    پنجره->اصابت_test_داده = callback_داده;

    أرجع _this->مجموعه_پنجره_اصابت_Test(پنجره, callback != عدم);
}

bool SDL_مجموعه_پنجره_Shape(SDL_پنجره *پنجره, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_پنجره_MAGIC(پنجره, false);

    إذا (!(پنجره->flags & SDL_پنجره_TRANSPARENT)) {
        أرجع SDL_مجموعه_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_پنجره_Properties(پنجره);
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

    إذا (!SDL_مجموعه_Surface_Property(props, SDL_PROP_پنجره_SHAPE_اشاره_گر, surface)) {
        أرجع false;
    }

    إذا (_this->Update_پنجره_Shape) {
        إذا (!_this->Update_پنجره_Shape(_this, پنجره, surface)) {
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
    SDL_SendAppEvent(SDL_EVENT_کم_حافظه);
}

فراغ SDL_OnApplicationWillEnterBackground(فراغ)
{
    إذا (_this) {
        SDL_پنجره *پنجره;
        لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_MINIMIZED, 0, 0);
        }
        SDL_مجموعه_Keyboard_Focus(عدم);
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
        SDL_پنجره *پنجره;
        لكل (پنجره = _this->windows; پنجره; پنجره = پنجره->بعدی) {
            SDL_مجموعه_Keyboard_Focus(پنجره);
            SDL_Send_پنجره_Event(پنجره, SDL_EVENT_پنجره_RESTORED, 0, 0);
        }
    }
}

#تعریف_کن NOT_A_VULKAN_پنجره "The specified window isn't a Vulkan window"

bool SDL_Vulkan_بارگیری_Library(ثابت حرف *مسیر)
{
    bool نتیجه;

    إذا (!_this) {
        أرجع SDL_UninitializedVideo();
    }
    إذا (_this->vulkan_config.loader_loaded) {
        إذا (مسیر && SDL_strcmp(مسیر, _this->vulkan_config.loader_مسیر) != 0) {
            أرجع SDL_مجموعه_Error("Vulkan loader library already loaded");
        }
        نتیجه = true;
    } وإلا {
        إذا (!_this->Vulkan_بارگیری_Library) {
            أرجع SDL_DllNotSupported("Vulkan");
        }
        نتیجه = _this->Vulkan_بارگیری_Library(_this, مسیر);
    }
    إذا (نتیجه) {
        _this->vulkan_config.loader_loaded++;
    }
    أرجع نتیجه;
}

SDL_Function_اشاره_گر SDL_Vulkan_GetVkGetInstanceProcAddr(فراغ)
{
    إذا (!_this) {
        SDL_UninitializedVideo();
        أرجع عدم;
    }
    إذا (!_this->vulkan_config.loader_loaded) {
        SDL_مجموعه_Error("No Vulkan loader has been loaded");
        أرجع عدم;
    }
    أرجع (SDL_Function_اشاره_گر)_this->vulkan_config.vkGetInstanceProcAddr;
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

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *شمار)
{
    Uint32 tmpcount = 0;
    إذا (!شمار) {
        شمار = &tmpcount;
    }

    إذا (!_this->Vulkan_GetInstanceExtensions) {
        *شمار = 0;
        SDL_Unsupported();
        أرجع عدم;
    }

    أرجع _this->Vulkan_GetInstanceExtensions(_this, شمار);
}

bool SDL_Vulkan_CreateSurface(SDL_پنجره *پنجره,
                                  VkInstance instance,
                                  ثابت بنية Vk_تخصیص_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_پنجره_MAGIC(پنجره, false);

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

    إذا (!(پنجره->flags & SDL_پنجره_VULKAN)) {
        // No problem, we can convert to Vulkan
        إذا (پنجره->flags & SDL_پنجره_OPENGL) {
            پنجره->flags &= ~SDL_پنجره_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (پنجره->flags & SDL_پنجره_METAL) {
            پنجره->flags &= ~SDL_پنجره_METAL;
            // Nothing more to do for Metal.
        }
        إذا (SDL_Vulkan_بارگیری_Library(عدم)) {
            پنجره->flags |= SDL_پنجره_VULKAN;
        } وإلا {
            أرجع SDL_مجموعه_Error("failed to load Vulkan library");
        }
    }

    أرجع _this->Vulkan_CreateSurface(_this, پنجره, instance, allocator, surface);
}

فراغ SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت بنية Vk_تخصیص_Callbacks *allocator)
{
    إذا (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 صف_Family_شاخص)
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
        أرجع _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, صف_Family_شاخص);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    أرجع true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_پنجره *پنجره)
{
    CHECK_پنجره_MAGIC(پنجره, عدم);

    إذا (!_this->Metal_CreateView) {
        SDL_Unsupported();
        أرجع عدم;
    }

    إذا (!(پنجره->flags & SDL_پنجره_METAL)) {
        // No problem, we can convert to Metal
        إذا (پنجره->flags & SDL_پنجره_OPENGL) {
            پنجره->flags &= ~SDL_پنجره_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        إذا (پنجره->flags & SDL_پنجره_VULKAN) {
            پنجره->flags &= ~SDL_پنجره_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        پنجره->flags |= SDL_پنجره_METAL;
    }

    أرجع _this->Metal_CreateView(_this, پنجره);
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
        SDL_مجموعه_Error("Metal is not supported.");
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

    حالة SDL_SYSTEM_CURSOR_پیشرفت:
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

    حالة SDL_SYSTEM_CURSOR_اشاره_گر:
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

    حالة SDL_SYSTEM_CURSOR_ردیف_RESIZE:
        أرجع "row-resize";

    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        إذا (fallback_name) {
            *fallback_name = "move";
        }
        أرجع "all-scroll";

    حالة SDL_SYSTEM_CURSOR_ZOOM_درون:
        أرجع "zoom-in";

    حالة SDL_SYSTEM_CURSOR_ZOOM_بیرون:
        أرجع "zoom-out";

    افتراضي:
        أرجع "default";
    }
}
#پایان_اگر

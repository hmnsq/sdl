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

#شامل "SDL_internal.h"

// The high-level video driver subsystem

#شامل "SDL_sysvideo.h"
#شامل "SDL_clipboard_c.h"
#شامل "SDL_egl_c.h"
#شامل "SDL_surface_c.h"
#شامل "SDL_pixels_c.h"
#شامل "SDL_rect_c.h"
#شامل "SDL_video_c.h"
#شامل "../events/SDL_events_c.h"
#شامل "../SDL_hints_c.h"
#شامل "../SDL_properties_c.h"
#شامل "../timer/SDL_timer_c.h"
#شامل "../camera/SDL_camera_c.h"
#شامل "../render/SDL_sysrender.h"
#شامل "../main/SDL_main_callbacks.h"

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
#شامل <SDL3/SDL_opengl.h>
#اگر_ختم // SDL_VIDEO_OPENGL

#اگر defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#شامل <SDL3/SDL_opengles.h>
#اگر_ختم // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#اگر defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#شامل <SDL3/SDL_opengles2.h>
#اگر_ختم // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#اگر_غیر_تعریف_شدہ GL_CONTEXT_RELEASE_BEHAVIOR
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#اگر_ختم

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#اگر_غیر_تعریف_شدہ GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#تعریف_کرو GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#اگر_ختم

// This is always the same number between the various EXT/ARB/GLES extensions.
#اگر_غیر_تعریف_شدہ GL_FRAMEBUFFER_SRGB
#تعریف_کرو GL_FRAMEBUFFER_SRGB 0x8DB9
#اگر_ختم

#اگر_تعریف_شدہ SDL_PLATFORM_EMSCRIPTEN
#شامل <emscripten.h>
#اگر_ختم

#اگر_تعریف_شدہ SDL_PLATFORM_3DS
#شامل <3ds.h>
#اگر_ختم

#اگر_غیر_تعریف_شدہ GL_RGBA_FLOAT_منوال_ARB
#تعریف_کرو GL_RGBA_FLOAT_منوال_ARB 0x8820
#اگر_ختم /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
ساکن VideoBootStrap *bootstrap[] = {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_نجی
    &نجی_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#اگر_ختم
    &X11_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#اگر_تعریف_شدہ SDL_داخلہ_LINUXEV
    &DUMMY_evdev_bootstrap,
#اگر_ختم
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#اگر_ختم
    تہی
};

#تعریف_کرو CHECK_کھڑکی_MAGIC(کھڑکی, نتیجہ)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        واپس نتیجہ;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(کھڑکی, SDL_OBJECT_TYPE_کھڑکی)) {     \
        SDL_سیٹ_Error("Invalid window");                                 \
        واپس نتیجہ;                                                  \
    }

#تعریف_کرو CHECK_DISPLAY_MAGIC(display, نتیجہ)                            \
    CHECK_PARAM(!display) {                                             \
        واپس نتیجہ;                                                  \
    }                                                                   \

#تعریف_کرو CHECK_کھڑکی_NOT_POPUP(کھڑکی, نتیجہ)                          \
    CHECK_PARAM(SDL_کھڑکی_IS_POPUP(کھڑکی)) {                          \
        SDL_سیٹ_Error("Operation invalid on popup windows");             \
        واپس نتیجہ;                                                  \
    }

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
خارجی bool Cocoa_Is_کھڑکی_اندر_Fullscreen_Space(SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_Is_کھڑکی_اندر_Fullscreen_Space_Transition(SDL_کھڑکی *کھڑکی);
خارجی bool Cocoa_سیٹ_کھڑکی_Fullscreen_Space(SDL_کھڑکی *کھڑکی, bool state, bool blocking);
خارجی bool Cocoa_IsShowingModalDialog(SDL_کھڑکی *کھڑکی);
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
خارجی خالی SDL_UpdateLifecycleObserver(خالی);
#اگر_ختم

ساکن خالی SDL_Check_کھڑکی_Display_بدلا(SDL_کھڑکی *کھڑکی);
ساکن خالی SDL_Check_کھڑکی_Display_Scale_بدلا(SDL_کھڑکی *کھڑکی);
ساکن خالی SDL_Check_کھڑکی_محفوظ_Area_بدلا(SDL_کھڑکی *کھڑکی);

// Convenience functions for reading driver flags
ساکن bool SDL_منوال_Switching_Emulated(SDL_VideoDevice *_this)
{
    اگر (_this->device_caps & VIDEO_DEVICE_CAPS_منوال_SWITCHING_EMULATED) {
        واپس true;
    }
    واپس false;
}

ساکن bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    واپس !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

ساکن bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    واپس !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

ساکن bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    واپس !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

ساکن bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    واپس !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

ساکن bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    واپس !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
ساکن bool syncHint;

ساکن خالی SDL_SyncHintWatcher(خالی *userdata, ثابت حرف *name, ثابت حرف *old_قدر, ثابت حرف *new_قدر)
{
    syncHint = SDL_GetStringBoolean(new_قدر, false);
}

ساکن خالی SDL_SyncIfRequired(SDL_کھڑکی *کھڑکی)
{
    اگر (syncHint) {
        SDL_Sync_کھڑکی(کھڑکی);
    }
}

ساکن خالی SDL_Update_کھڑکی_Hierarchy(SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد)
{
    // Unlink the window from the existing parent.
    اگر (کھڑکی->والد) {
        اگر (کھڑکی->اگلا_sibling) {
            کھڑکی->اگلا_sibling->پچھلا_sibling = کھڑکی->پچھلا_sibling;
        }
        اگر (کھڑکی->پچھلا_sibling) {
            کھڑکی->پچھلا_sibling->اگلا_sibling = کھڑکی->اگلا_sibling;
        } ورنہ {
            کھڑکی->والد->پہلا_بچہ = کھڑکی->اگلا_sibling;
        }

        کھڑکی->والد = تہی;
    }

    اگر (والد) {
        کھڑکی->والد = والد;

        کھڑکی->اگلا_sibling = والد->پہلا_بچہ;
        اگر (والد->پہلا_بچہ) {
            والد->پہلا_بچہ->پچھلا_sibling = کھڑکی;
        }
        والد->پہلا_بچہ = کھڑکی;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#تعریف_کرو SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر "SDL.internal.window.texturedata"

قسمتعریف ساخت
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    خالی *pixels;
    صحیح pitch;
    صحیح بائٹیں_فی_pixel;
} SDL_کھڑکی_Texture_ڈیٹا;

ساکن Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#اگر (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !ہدف_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    اگر (_this->GL_CreateContext) {
        واپس SDL_کھڑکی_OPENGL;
    }
#اگر_ختم
#اگر defined(SDL_VIDEO_METAL) && (ہدف_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    اگر (_this->Metal_CreateView) {
        واپس SDL_کھڑکی_METAL;
    }
#اگر_ختم
#اگر defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    اگر (SDL_strcmp(_this->name, "openvr") == 0) {
        واپس SDL_کھڑکی_OPENGL;
    }
#اگر_ختم
    واپس 0;
}

ساکن bool SDL_Create_کھڑکی_Texture(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format, خالی **pixels, صحیح *pitch)
{
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    SDL_کھڑکی_Texture_ڈیٹا *ڈیٹا = (SDL_کھڑکی_Texture_ڈیٹا *)SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, تہی);
    ثابت bool transparent = (کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) ? true : false;
    صحیح i;
    صحیح w, h;
    ثابت SDL_PixelFormat *texture_formats;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);

    اگر (!ڈیٹا) {
        SDL_Renderer *renderer = تہی;
        ثابت حرف *render_driver = تہی;

        // See if there's a render driver being requested
        ثابت حرف *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        اگر (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        اگر (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        اگر (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = تہی;
        }

        حرف *render_driver_copy = تہی;
        اگر (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            اگر (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                حرف *پچھلا = render_driver_copy;
                حرف *ptr = پچھلا;
                جب ((ptr = SDL_strchr(ptr, ',')) != تہی) {
                    *ptr = '\0';
                    ثابت bool is_sw = (SDL_strcasecmp(پچھلا, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    اگر (is_sw) {
                        SDL_memset(پچھلا, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = پچھلا;
                    } ورنہ {
                        ptr++;
                        پچھلا = ptr;
                    }
                }

                اگر (SDL_strcasecmp(پچھلا, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(پچھلا, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        اگر (render_driver) {
            renderer = SDL_CreateRenderer(کھڑکی, render_driver);
            SDL_free(render_driver_copy);
            اگر (!renderer) {
                // The error for this specific renderer has already been set
                واپس false;
            }
        } ورنہ {
            SDL_assert(render_driver_copy == تہی);
            ثابت صحیح کل = SDL_Get_عدد_Render_Drivers();
            برائے (i = 0; i < کل; ++i) {
                ثابت حرف *name = SDL_GetRenderDriver(i);
                اگر (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(کھڑکی, name);
                    اگر (renderer) {
                        توڑو; // this will work.
                    }
                }
            }
            اگر (!renderer) {
                واپس SDL_سیٹ_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != تہی); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        ڈیٹا = (SDL_کھڑکی_Texture_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
        اگر (!ڈیٹا) {
            SDL_DestroyRenderer(renderer);
            واپس false;
        }
        اگر (!SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, ڈیٹا)) {
            SDL_DestroyRenderer(renderer);
            واپس false;
        }

        ڈیٹا->renderer = renderer;
    }

    texture_formats = (ثابت SDL_PixelFormat *)SDL_Get_اشارہ_گر_Property(SDL_GetRendererProperties(ڈیٹا->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_اشارہ_گر, تہی);
    اگر (!texture_formats) {
        واپس false;
    }

    // Free any old texture and pixel data
    اگر (ڈیٹا->texture) {
        SDL_DestroyTexture(ڈیٹا->texture);
        ڈیٹا->texture = تہی;
    }
    SDL_free(ڈیٹا->pixels);
    ڈیٹا->pixels = تہی;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    برائے (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        اگر (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10_ثنائی_ہندسہ(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_اشاریہ_دار(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            توڑو;
        }
    }

    ڈیٹا->texture = SDL_CreateTexture(ڈیٹا->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    اگر (!ڈیٹا->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        واپس false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_سیٹ_Texture_Blend_منوال(ڈیٹا->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    ڈیٹا->بائٹیں_فی_pixel = SDL_BYTESPERPIXEL(*format);
    ڈیٹا->pitch = (((w * ڈیٹا->بائٹیں_فی_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ثابت size_t allocsize = (size_t)h * ڈیٹا->pitch;
        ڈیٹا->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        اگر (!ڈیٹا->pixels) {
            واپس false;
        }
    }

    *pixels = ڈیٹا->pixels;
    *pitch = ڈیٹا->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_سیٹ_Render_Viewport(ڈیٹا->renderer, تہی);

    واپس true;
}

bool SDL_سیٹ_کھڑکی_Texture_VSync(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح vsync)
{
    SDL_کھڑکی_Texture_ڈیٹا *ڈیٹا;

    ڈیٹا = (SDL_کھڑکی_Texture_ڈیٹا *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, تہی);
    اگر (!ڈیٹا) {
        واپس false;
    }
    اگر (!ڈیٹا->renderer) {
        واپس false;
    }
    واپس SDL_سیٹ_Render_VSync(ڈیٹا->renderer, vsync);
}

ساکن bool SDL_Get_کھڑکی_Texture_VSync(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *vsync)
{
    SDL_کھڑکی_Texture_ڈیٹا *ڈیٹا;

    ڈیٹا = (SDL_کھڑکی_Texture_ڈیٹا *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, تہی);
    اگر (!ڈیٹا) {
        واپس false;
    }
    اگر (!ڈیٹا->renderer) {
        واپس false;
    }
    واپس SDL_GetRenderVSync(ڈیٹا->renderer, vsync);
}

ساکن bool SDL_Update_کھڑکی_Texture(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects, صحیح numrects)
{
    SDL_کھڑکی_Texture_ڈیٹا *ڈیٹا;
    SDL_Rect rect;
    خالی *src;
    صحیح w, h;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);

    ڈیٹا = (SDL_کھڑکی_Texture_ڈیٹا *)SDL_Get_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, تہی);
    اگر (!ڈیٹا || !ڈیٹا->texture) {
        واپس SDL_سیٹ_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    اگر (SDL_Get_وسعت_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (خالی *)((Uint8 *)ڈیٹا->pixels +
                       rect.y * ڈیٹا->pitch +
                       rect.x * ڈیٹا->بائٹیں_فی_pixel);
        اگر (!SDL_UpdateTexture(ڈیٹا->texture, &rect, src, ڈیٹا->pitch)) {
            واپس false;
        }

        اگر (!SDL_RenderTexture(ڈیٹا->renderer, ڈیٹا->texture, تہی, تہی)) {
            واپس false;
        }

        SDL_RenderPresent(ڈیٹا->renderer);
    }
    واپس true;
}

ساکن خالی SDL_Destroy_کھڑکی_Texture(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    اگر (SDL_HasProperty(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر)) {
        SDL_کھڑکی_Texture_ڈیٹا *ڈیٹا = SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر, تہی);

        اگر (ڈیٹا->texture) {
            SDL_DestroyTexture(ڈیٹا->texture);
        }
        اگر (ڈیٹا->renderer) {
            SDL_DestroyRenderer(ڈیٹا->renderer);
        }
        SDL_free(ڈیٹا->pixels);
        SDL_free(ڈیٹا);

        SDL_ClearProperty(props, SDL_PROP_کھڑکی_TEXTUREDATA_اشارہ_گر);
    }
}

ساکن SDL_VideoDevice *_this = تہی;
ساکن SDL_AtomicInt SDL_messagebox_گنتی;

ساکن صحیح SDLCALL cmpmodes(ثابت خالی *A, ثابت خالی *B)
{
    ثابت SDL_Display_منوال *a = (ثابت SDL_Display_منوال *)A;
    ثابت SDL_Display_منوال *b = (ثابت SDL_Display_منوال *)B;
    صحیح a_refresh_شرح = (صحیح)(a->refresh_شرح * 100);
    صحیح b_refresh_شرح = (صحیح)(b->refresh_شرح * 100);
    صحیح a_pixel_density = (صحیح)(a->pixel_density * 100);
    صحیح b_pixel_density = (صحیح)(b->pixel_density * 100);

    اگر (a->w != b->w) {
        واپس b->w - a->w;
    } ورنہ اگر (a->h != b->h) {
        واپس b->h - a->h;
    } ورنہ اگر (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        واپس SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } ورنہ اگر (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        واپس SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } ورنہ اگر (a_refresh_شرح != b_refresh_شرح) {
        واپس b_refresh_شرح - a_refresh_شرح;
    } ورنہ اگر (a_pixel_density != b_pixel_density) {
        واپس a_pixel_density - b_pixel_density;
    }
    واپس 0;
}

bool SDL_UninitializedVideo(خالی)
{
    واپس SDL_سیٹ_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
ساکن ثابت VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

صحیح SDL_Get_عدد_Video_Drivers(خالی)
{
    ساکن صحیح عدد_drivers = -1;

    اگر (عدد_drivers >= 0) {
        واپس عدد_drivers;
    }

    عدد_drivers = 0;

    // Build a list of unique video drivers.
    برائے (صحیح i = 0; bootstrap[i] != تہی; ++i) {
        bool duplicate = false;
        برائے (صحیح j = 0; j < i; ++j) {
            اگر (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                توڑو;
            }
        }

        اگر (!duplicate) {
            deduped_bootstrap[عدد_drivers++] = bootstrap[i];
        }
    }

    واپس عدد_drivers;
}

ثابت حرف *SDL_GetVideoDriver(صحیح اشاریہ)
{
    CHECK_PARAM(اشاریہ < 0 || اشاریہ >= SDL_Get_عدد_Video_Drivers()) {
        SDL_InvalidParamError("index");
        واپس تہی;
    }
    واپس deduped_bootstrap[اشاریہ]->name;
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
    صحیح i = 0;

    // Check to make sure we don't overwrite '_this'
    اگر (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    اگر (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        جاؤ pre_driver_error;
    }
    init_events = true;
    اگر (!SDL_InitKeyboard()) {
        جاؤ pre_driver_error;
    }
    init_keyboard = true;
    اگر (!SDL_PreInitMouse()) {
        جاؤ pre_driver_error;
    }
    init_mouse = true;
    اگر (!SDL_InitTouch()) {
        جاؤ pre_driver_error;
    }
    init_touch = true;
    اگر (!SDL_InitPen()) {
        جاؤ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = تہی;
#اگر_تعریف_شدہ SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    اگر (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#اگر_ختم
    اگر (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    اگر (driver_name && *driver_name != 0) {
        ثابت حرف *driver_attempt = driver_name;
        جب (driver_attempt && *driver_attempt != 0 && !video) {
            ثابت حرف *driver_attempt_انتہا = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_انتہا) ? (driver_attempt_انتہا - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            برائے (i = 0; bootstrap[i]; ++i) {
                اگر (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    اگر (video) {
                        توڑو;
                    }
                }
            }

            driver_attempt = (driver_attempt_انتہا) ? (driver_attempt_انتہا + 1) : تہی;
        }
    } ورنہ {
        برائے (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            اگر (video) {
                توڑو;
            }
        }
    }
    اگر (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } ورنہ {
        اگر (driver_name) {
            SDL_سیٹ_Error("%s not available", driver_name);
            جاؤ pre_driver_error;
        }
        SDL_سیٹ_Error("No available video device");
        جاؤ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = تہی;
    SDL_GL_Reset_اوصاف();

    // Initialize the video subsystem
    اگر (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        واپس false;
    }

    // Make sure some displays were added
    اگر (_this->عدد_displays == 0) {
        SDL_QuitVideo();
        واپس SDL_سیٹ_Error("The video driver did not add any displays");
    }

    SDL_جوڑو_Hint_Callback(SDL_HINT_VIDEO_SYNC_کھڑکی_OPERATIONS, SDL_SyncHintWatcher, تہی);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    اگر (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    واپس true;

pre_driver_error:
    SDL_assert(_this == تہی);
    اگر (init_pen) {
        SDL_QuitPen();
    }
    اگر (init_touch) {
        SDL_QuitTouch();
    }
    اگر (init_mouse) {
        SDL_QuitMouse();
    }
    اگر (init_keyboard) {
        SDL_QuitKeyboard();
    }
    اگر (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    واپس false;
}

ثابت حرف *SDL_GetCurrentVideoDriver(خالی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    واپس _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(خالی)
{
    واپس _this;
}

bool SDL_OnVideoThread(خالی)
{
    واپس (_this && SDL_GetCurrentThreadID() == _this->thread);
}

خالی SDL_سیٹ_System_Theme(SDL_SystemTheme theme)
{
    اگر (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_بدلا_Event();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(خالی)
{
    اگر (_this) {
        واپس _this->system_theme;
    } ورنہ {
        واپس SDL_SYSTEM_THEME_UNKNOWN;
    }
}

خالی SDL_UpdateDesktopBounds(خالی)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(تہی);
    اگر (displays) {
        برائے (صحیح i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            اگر (SDL_GetDisplayBounds(displays[i], &bounds)) {
                اگر (i == 0) {
                    SDL_copyp(&rect, &bounds);
                } ورنہ {
                    SDL_GetRectUnion(&rect, &bounds, &rect);
                }
            }
        }
        SDL_free(displays);
    }
    SDL_copyp(&_this->desktop_bounds, &rect);
}

ساکن خالی SDL_Finalize_Display_منوال(SDL_Display_منوال *منوال)
{
    // Make sure all the fields are set up correctly
    اگر (منوال->pixel_density <= 0.0f) {
        منوال->pixel_density = 1.0f;
    }

    اگر (منوال->refresh_شرح_numerator > 0) {
        اگر (منوال->refresh_شرح_denominator <= 0) {
            منوال->refresh_شرح_denominator = 1;
        }
        منوال->refresh_شرح = (اعشاری)منوال->refresh_شرح_numerator / منوال->refresh_شرح_denominator;
    } ورنہ {
        SDL_CalculateFraction(منوال->refresh_شرح, &منوال->refresh_شرح_numerator, &منوال->refresh_شرح_denominator);
    }
    منوال->refresh_شرح = SDL_roundf(منوال->refresh_شرح * 100) / 100.0f;
}

SDL_DisplayID SDL_جوڑو_Basic_Video_Display(ثابت SDL_Display_منوال *desktop_منوال)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    اگر (desktop_منوال) {
        SDL_memcpy(&display.desktop_منوال, desktop_منوال, حجم(display.desktop_منوال));
    }
    واپس SDL_جوڑو_Video_Display(&display, false);
}

SDL_DisplayID SDL_جوڑو_Video_Display(ثابت SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    صحیح i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(حجم(*new_display));
    اگر (!new_display) {
        واپس 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->عدد_displays + 1) * حجم(*displays));
    اگر (!displays) {
        SDL_free(new_display);
        واپس 0;
    }
    _this->displays = displays;
    _this->displays[_this->عدد_displays++] = new_display;

    id = SDL_Get_اگلا_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    اگر (display->name) {
        new_display->name = SDL_strdup(display->name);
    } ورنہ {
        حرف name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    اگر (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_منوال.displayID = id;
    new_display->current_منوال = &new_display->desktop_منوال;
    SDL_Finalize_Display_منوال(&new_display->desktop_منوال);

    برائے (i = 0; i < new_display->عدد_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_سیٹ_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    اگر (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    واپس id;
}

خالی SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_کھڑکی *کھڑکی;

    // See if any windows have changed to the new display
    برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        SDL_Check_کھڑکی_Display_بدلا(کھڑکی);
    }
}

خالی SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

خالی SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    صحیح display_اشاریہ = SDL_Get_Display_اشاریہ(displayID);
    اگر (display_اشاریہ < 0) {
        واپس;
    }

    display = _this->displays[display_اشاریہ];

    اگر (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_منوال.اندرونی_2);
    display->desktop_منوال.اندرونی_2 = تہی;
    SDL_free(display->اندرونی_2);
    display->اندرونی_2 = تہی;
    SDL_free(display);

    اگر (display_اشاریہ < (_this->عدد_displays - 1)) {
        SDL_memmove(&_this->displays[display_اشاریہ], &_this->displays[display_اشاریہ + 1], (_this->عدد_displays - display_اشاریہ - 1) * حجم(_this->displays[display_اشاریہ]));
    }
    --_this->عدد_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(صحیح *گنتی)
{
    صحیح i;
    SDL_DisplayID *displays;

    اگر (!_this) {
        اگر (گنتی) {
            *گنتی = 0;
        }

        SDL_UninitializedVideo();
        واپس تہی;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->عدد_displays + 1) * حجم(*displays));
    اگر (displays) {
        اگر (گنتی) {
            *گنتی = _this->عدد_displays;
        }

        برائے (i = 0; i < _this->عدد_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } ورنہ {
        اگر (گنتی) {
            *گنتی = 0;
        }
    }
    واپس displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    صحیح display_اشاریہ;

    display_اشاریہ = SDL_Get_Display_اشاریہ(displayID);
    اگر (display_اشاریہ < 0) {
        واپس تہی;
    }
    واپس _this->displays[display_اشاریہ];
}

ساکن SDL_DisplayID Get_Display_For_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        displayID = کھڑکی->current_fullscreen_منوال.displayID;
    }

    اگر (!displayID) {
        displayID = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);
    }
    واپس displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    واپس SDL_GetVideoDisplay(Get_Display_For_کھڑکی(کھڑکی));
}

SDL_DisplayID SDL_GetPrimaryDisplay(خالی)
{
    اگر (!_this || _this->عدد_displays == 0) {
        SDL_UninitializedVideo();
        واپس 0;
    }
    واپس _this->displays[0]->id;
}

صحیح SDL_Get_Display_اشاریہ(SDL_DisplayID displayID)
{
    صحیح display_اشاریہ;

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس -1;
    }

    برائے (display_اشاریہ = 0; display_اشاریہ < _this->عدد_displays; ++display_اشاریہ) {
        اگر (displayID == _this->displays[display_اشاریہ]->id) {
            واپس display_اشاریہ;
        }
    }
    SDL_سیٹ_Error("Invalid display");
    واپس -1;
}

SDL_Display_ڈیٹا *SDL_Get_Display_Driver_ڈیٹا(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, تہی);

    واپس display->اندرونی_2;
}

SDL_Display_ڈیٹا *SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    واپس SDL_Get_Display_Driver_ڈیٹا(Get_Display_For_کھڑکی(کھڑکی));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    اگر (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    واپس display->props;
}

ثابت حرف *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, تہی);

    واپس display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        واپس SDL_InvalidParamError("rect");
    }

    اگر (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        اگر (_this->GetDisplayBounds(_this, display, rect)) {
            واپس true;
        }
    }

    // Assume that the displays are left to right
    اگر (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } ورنہ {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_اشاریہ(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_منوال->w;
    rect->h = display->current_منوال->h;
    واپس true;
}

ساکن صحیح ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    واپس hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        واپس SDL_InvalidParamError("rect");
    }

    اگر (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        واپس true;
    }

    اگر (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        اگر (_this->GetDisplayUsableBounds(_this, display, rect)) {
            واپس true;
        }
    }

    // Oh well, just give the entire display bounds.
    واپس SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    اگر (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        واپس display->natural_orientation;
    } ورنہ {
        // Default to landscape if the driver hasn't set it
        واپس SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    اگر (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        واپس display->current_orientation;
    } ورنہ {
        // Default to landscape if the driver hasn't set it
        واپس SDL_ORIENTATION_LANDSCAPE;
    }
}

خالی SDL_سیٹ_Display_Content_Scale(SDL_VideoDisplay *display, اعشاری scale)
{
    اگر (scale != display->content_scale) {
        SDL_کھڑکی *کھڑکی;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_بدلا, 0, 0);

        // Check the windows on this display
        برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            اگر (display->id == کھڑکی->displayID) {
                SDL_Check_کھڑکی_Display_Scale_بدلا(کھڑکی);
            }
        }
    }
}

اعشاری SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    واپس display->content_scale;
}

خالی SDL_سیٹ_کھڑکی_HDRProperties(SDL_کھڑکی *کھڑکی, ثابت SDL_HDROutputProperties *HDR, bool send_event)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    اگر (کھڑکی->HDR.HDR_headroom != HDR_clamped.HDR_headroom || کھڑکی->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID کھڑکی_props = SDL_Get_کھڑکی_Properties(کھڑکی);

        SDL_سیٹ_Float_Property(کھڑکی_props, SDL_PROP_کھڑکی_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_سیٹ_Float_Property(کھڑکی_props, SDL_PROP_کھڑکی_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_سیٹ_Boolean_Property(کھڑکی_props, SDL_PROP_کھڑکی_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&کھڑکی->HDR, &HDR_clamped);

        اگر (send_event) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_HDR_STATE_بدلا, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

خالی SDL_سیٹ_Display_HDRProperties(SDL_VideoDisplay *display, ثابت SDL_HDROutputProperties *HDR)
{
    ثابت SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ثابت bool بدلا = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	اگر (بدلا) {
		SDL_سیٹ_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    اگر (بدلا && !SDL_DriverSendsHDRChanges(_this)) {
        برائے (SDL_کھڑکی *w = display->device->windows; w; w = w->اگلا) {
            اگر (Get_Display_For_کھڑکی(w) == display->id) {
                SDL_سیٹ_کھڑکی_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

ساکن خالی SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    اگر (display->عدد_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
ساکن ثابت SDL_Display_منوال *SDL_Get_Fullscreen_منوال_مطابقت(ثابت SDL_Display_منوال *منوال)
{
    SDL_VideoDisplay *display;
    SDL_Display_منوال fullscreen_منوال;

    اگر (منوال->w <= 0 || منوال->h <= 0) {
        // Use the desktop mode
        واپس تہی;
    }

    SDL_memcpy(&fullscreen_منوال, منوال, حجم(fullscreen_منوال));
    اگر (fullscreen_منوال.displayID == 0) {
        fullscreen_منوال.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_منوال(&fullscreen_منوال);

    منوال = تہی;

    display = SDL_GetVideoDisplay(fullscreen_منوال.displayID);
    اگر (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        اگر (!منوال) {
            برائے (صحیح i = 0; i < display->عدد_fullscreen_modes; ++i) {
                اگر (SDL_memcmp(&fullscreen_منوال, &display->fullscreen_modes[i], حجم(fullscreen_منوال)) == 0) {
                    منوال = &display->fullscreen_modes[i];
                    توڑو;
                }
            }
        }

        // Search for a mode with the same characteristics
        اگر (!منوال) {
            برائے (صحیح i = 0; i < display->عدد_fullscreen_modes; ++i) {
                اگر (cmpmodes(&fullscreen_منوال, &display->fullscreen_modes[i]) == 0) {
                    منوال = &display->fullscreen_modes[i];
                    توڑو;
                }
            }
        }
    }
    واپس منوال;
}

bool SDL_جوڑو_Fullscreen_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال)
{
    SDL_Display_منوال *modes;
    SDL_Display_منوال new_منوال;
    صحیح i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_منوال, منوال, حجم(new_منوال));
    new_منوال.displayID = display->id;
    SDL_Finalize_Display_منوال(&new_منوال);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->عدد_fullscreen_modes;
    برائے (i = 0; i < nmodes; ++i) {
        اگر (cmpmodes(&new_منوال, &modes[i]) == 0) {
            واپس false;
        }
    }

    // Go ahead and add the new mode
    اگر (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_منوال *)SDL_malloc((display->max_fullscreen_modes + 32) * حجم(*modes));
        اگر (!modes) {
            واپس false;
        }

        اگر (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * حجم(*modes));
            برائے (i = 0; i < nmodes; ++i) {
                اگر (display->current_منوال == &display->fullscreen_modes[i]) {
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

    واپس true;
}

خالی SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    صحیح i;

    برائے (i = display->عدد_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].اندرونی_2);
        display->fullscreen_modes[i].اندرونی_2 = تہی;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = تہی;
    display->عدد_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_منوال = &display->desktop_منوال;
}

SDL_Display_منوال **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, صحیح *گنتی)
{
    صحیح i;
    صحیح عدد_modes;
    SDL_Display_منوال **نتیجہ;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    اگر (گنتی) {
        *گنتی = 0;
    }

    CHECK_DISPLAY_MAGIC(display, تہی);

    SDL_UpdateFullscreenDisplayModes(display);

    عدد_modes = display->عدد_fullscreen_modes;
    نتیجہ = (SDL_Display_منوال **)SDL_malloc((عدد_modes + 1) * حجم(*نتیجہ) + عدد_modes * حجم(**نتیجہ));
    اگر (نتیجہ) {
        SDL_Display_منوال *modes = (SDL_Display_منوال *)((Uint8 *)نتیجہ + ((عدد_modes + 1) * حجم(*نتیجہ)));
        اگر (عدد_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, عدد_modes * حجم(*modes));
        }
        برائے (i = 0; i < عدد_modes; ++i) {
            نتیجہ[i] = modes++;
        }
        نتیجہ[i] = تہی;

        اگر (گنتی) {
            *گنتی = عدد_modes;
        }
    } ورنہ {
        اگر (گنتی) {
            *گنتی = 0;
        }
    }
    واپس نتیجہ;
}

bool SDL_Get_Closest_Fullscreen_Display_منوال(SDL_DisplayID displayID, صحیح w, صحیح h, اعشاری refresh_شرح, bool include_بلند_density_modes, SDL_Display_منوال *نتیجہ)
{
    CHECK_PARAM(!نتیجہ) {
        واپس SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ثابت SDL_Display_منوال *منوال, *closest = تہی;
    اعشاری aspect_تناسب;
    صحیح i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(نتیجہ);

    CHECK_DISPLAY_MAGIC(display, false);

    اگر (h > 0) {
        aspect_تناسب = (اعشاری)w / h;
    } ورنہ {
        aspect_تناسب = 1.0f;
    }

    اگر (refresh_شرح == 0.0f) {
        refresh_شرح = display->desktop_منوال.refresh_شرح;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    برائے (i = 0; i < display->عدد_fullscreen_modes; ++i) {
        منوال = &display->fullscreen_modes[i];

        اگر (w > منوال->w) {
            // Out of sorted modes large enough here
            توڑو;
        }
        اگر (h > منوال->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            جاری;
        }
        اگر (منوال->pixel_density > 1.0f && !include_بلند_density_modes) {
            جاری;
        }
        اگر (closest) {
            اعشاری current_aspect_تناسب = (اعشاری)منوال->w / منوال->h;
            اعشاری closest_aspect_تناسب = (اعشاری)closest->w / closest->h;
            اگر (SDL_fabsf(aspect_تناسب - closest_aspect_تناسب) < SDL_fabsf(aspect_تناسب - current_aspect_تناسب)) {
                // The mode we already found has a better aspect ratio match
                جاری;
            }

            اگر (منوال->w == closest->w && منوال->h == closest->h) {
                اگر (SDL_fabsf(closest->refresh_شرح - refresh_شرح) < SDL_fabsf(منوال->refresh_شرح - refresh_شرح)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    جاری;
                }
                اگر (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(منوال->format)) {
                    // Prefer the highest color depth
                    جاری;
                }
            }
        }

        closest = منوال;
    }
    اگر (!closest) {
        واپس SDL_سیٹ_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(نتیجہ, closest);

    واپس true;
}

ساکن bool Display_منوال_بدلا(ثابت SDL_Display_منوال *old_منوال, ثابت SDL_Display_منوال *new_منوال)
{
    واپس ((old_منوال->displayID && old_منوال->displayID != new_منوال->displayID) ||
            (old_منوال->format && old_منوال->format != new_منوال->format) ||
            (old_منوال->w && old_منوال->h && (old_منوال->w != new_منوال->w ||old_منوال->h != new_منوال->h)) ||
            (old_منوال->pixel_density != 0.0f && old_منوال->pixel_density != new_منوال->pixel_density) ||
            (old_منوال->refresh_شرح != 0.0f && old_منوال->refresh_شرح != new_منوال->refresh_شرح));
}

خالی SDL_سیٹ_Desktop_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال)
{
    SDL_Display_منوال آخری_منوال;

    اگر (display->fullscreen_فعال) {
        // This is a temporary mode change, don't save the desktop mode
        واپس;
    }

    SDL_copyp(&آخری_منوال, &display->desktop_منوال);

    SDL_free(display->desktop_منوال.اندرونی_2);
    SDL_copyp(&display->desktop_منوال, منوال);
    display->desktop_منوال.displayID = display->id;
    SDL_Finalize_Display_منوال(&display->desktop_منوال);

    اگر (Display_منوال_بدلا(&آخری_منوال, &display->desktop_منوال)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_منوال_بدلا, منوال->w, منوال->h);
        اگر (display->current_منوال == &display->desktop_منوال) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_منوال_بدلا, منوال->w, منوال->h);
        }
    }
}

ثابت SDL_Display_منوال *SDL_Get_Desktop_Display_منوال(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, تہی);

    واپس &display->desktop_منوال;
}

خالی SDL_سیٹ_Current_Display_منوال(SDL_VideoDisplay *display, ثابت SDL_Display_منوال *منوال)
{
    SDL_Display_منوال آخری_منوال;

    اگر (display->current_منوال) {
        SDL_copyp(&آخری_منوال, display->current_منوال);
    } ورنہ {
        SDL_zero(آخری_منوال);
    }

    display->current_منوال = منوال;

    اگر (Display_منوال_بدلا(&آخری_منوال, منوال)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_منوال_بدلا, منوال->w, منوال->h);
    }
}

ثابت SDL_Display_منوال *SDL_Get_Current_Display_منوال(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, تہی);

    واپس display->current_منوال;
}

bool SDL_سیٹ_Display_منوال_For_Display(SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    اگر (SDL_منوال_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        واپس true;
    }

    اگر (!منوال) {
        منوال = &display->desktop_منوال;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#اگر_غیر_تعریف_شدہ SDL_PLATFORM_RISCOS
    اگر (منوال == display->current_منوال) {
        واپس true;
    }
#اگر_ختم

    // Actually change the display mode
    اگر (_this->سیٹ_Display_منوال) {
        bool نتیجہ;

        _this->setting_display_منوال = true;
        نتیجہ = _this->سیٹ_Display_منوال(_this, display, منوال);
        _this->setting_display_منوال = false;
        اگر (!نتیجہ) {
            واپس false;
        }
    }

    SDL_سیٹ_Current_Display_منوال(display, منوال);

    واپس true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
ساکن خالی SDL_Get_Closest_نقطہ_On_Rect(ثابت SDL_Rect *rect, SDL_نقطہ *نقطہ)
{
    ثابت صحیح دایاں = rect->x + rect->w - 1;
    ثابت صحیح bottom = rect->y + rect->h - 1;

    اگر (نقطہ->x < rect->x) {
        نقطہ->x = rect->x;
    } ورنہ اگر (نقطہ->x > دایاں) {
        نقطہ->x = دایاں;
    }

    اگر (نقطہ->y < rect->y) {
        نقطہ->y = rect->y;
    } ورنہ اگر (نقطہ->y > bottom) {
        نقطہ->y = bottom;
    }
}

ساکن SDL_DisplayID GetDisplayForRect(صحیح x, صحیح y, صحیح w, صحیح h)
{
    صحیح i, dist;
    SDL_DisplayID closest = 0;
    صحیح closest_dist = 0x7FFFFFFF;
    SDL_نقطہ closest_نقطہ_on_display;
    SDL_نقطہ delta;
    SDL_نقطہ center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    اگر (_this) {
        برائے (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            اگر (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, تہی)) {
                واپس display->id;
            }

            // Snap window center to the display rect
            closest_نقطہ_on_display = center;
            SDL_Get_Closest_نقطہ_On_Rect(&display_rect, &closest_نقطہ_on_display);

            delta.x = center.x - closest_نقطہ_on_display.x;
            delta.y = center.y - closest_نقطہ_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            اگر (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    اگر (closest == 0) {
        SDL_سیٹ_Error("Couldn't find any displays");
    }

    واپس closest;
}

خالی SDL_Relative_مقصد_Global_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحیح rel_x, صحیح rel_y, صحیح *abs_x, صحیح *abs_y)
{
    SDL_کھڑکی *w;

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Calculate the total offset of the popup from the parents
        برائے (w = کھڑکی->والد; w; w = w->والد) {
            rel_x += w->x;
            rel_y += w->y;

            اگر (!SDL_کھڑکی_IS_POPUP(w)) {
                توڑو;
            }
        }
    }

    اگر (abs_x) {
        *abs_x = rel_x;
    }
    اگر (abs_y) {
        *abs_y = rel_y;
    }
}

خالی SDL_Global_مقصد_Relative_For_کھڑکی(SDL_کھڑکی *کھڑکی, صحیح abs_x, صحیح abs_y, صحیح *rel_x, صحیح *rel_y)
{
    SDL_کھڑکی *w;

    اگر (SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // Convert absolute window coordinates to relative for a popup
        برائے (w = کھڑکی->والد; w; w = w->والد) {
            abs_x -= w->x;
            abs_y -= w->y;

            اگر (!SDL_کھڑکی_IS_POPUP(w)) {
                توڑو;
            }
        }
    }

    اگر (rel_x) {
        *rel_x = abs_x;
    }
    اگر (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_Get_Display_For_نقطہ(ثابت SDL_نقطہ *نقطہ)
{
    CHECK_PARAM(!نقطہ) {
        SDL_InvalidParamError("point");
        واپس 0;
    }

    واپس GetDisplayForRect(نقطہ->x, نقطہ->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ثابت SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        واپس 0;
    }

    واپس GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

ساکن SDL_DisplayID GetDisplayAtOrigin(صحیح x, صحیح y)
{
    برائے (صحیح i = 0; i < _this->عدد_displays; ++i) {
        SDL_Rect rect;
        ثابت SDL_DisplayID cur_id = _this->displays[i]->id;
        اگر (SDL_GetDisplayBounds(cur_id, &rect)) {
            اگر (x == rect.x && y == rect.y) {
                واپس cur_id;
            }
        }
    }

    واپس 0;
}

SDL_DisplayID SDL_Get_Display_For_کھڑکی_Position(SDL_کھڑکی *کھڑکی)
{
    صحیح x, y;
    SDL_DisplayID displayID = 0;

    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    اگر (_this->Get_Display_For_کھڑکی) {
        displayID = _this->Get_Display_For_کھڑکی(_this, کھڑکی);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_مقصد_Global_For_کھڑکی(کھڑکی, کھڑکی->x, کھڑکی->y, &x, &y);

    اگر (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } ورنہ {
            displayID = GetDisplayForRect(x, y, کھڑکی->w, کھڑکی->h);
        }
    }
    اگر (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    واپس displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_DisplayID displayID = 0;

    CHECK_کھڑکی_MAGIC(کھڑکی, تہی);

    // An explicit fullscreen display overrides all
    اگر (کھڑکی->current_fullscreen_منوال.displayID) {
        displayID = کھڑکی->current_fullscreen_منوال.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    اگر (!displayID) {
        displayID = کھڑکی->pending_displayID;
    }
    اگر (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ثابت صحیح x = کھڑکی->آخری_position_pending ? کھڑکی->pending.x : کھڑکی->x;
        ثابت صحیح y = کھڑکی->آخری_position_pending ? کھڑکی->pending.y : کھڑکی->y;
        ثابت صحیح w = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : کھڑکی->w;
        ثابت صحیح h = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : کھڑکی->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        اگر (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    اگر (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    واپس SDL_GetVideoDisplay(displayID);
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
    اگر (fs_display) {
        SDL_سیٹ_نمبر_Property(کھڑکی_props, SDL_PROP_SDL2_COMPAT_کھڑکی_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } ورنہ {
        SDL_ClearProperty(کھڑکی_props, SDL_PROP_SDL2_COMPAT_کھڑکی_PREFERRED_FULLSCREEN_DISPLAY);
    }

    واپس Get_Display_For_کھڑکی(کھڑکی);
}

ساکن خالی SDL_Check_کھڑکی_Display_بدلا(SDL_کھڑکی *کھڑکی)
{
    اگر (SDL_SendsDisplayChanges(_this)) {
        واپس;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);

    اگر (displayID != کھڑکی->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect کھڑکی_rect;
        SDL_Rect old_overlap, new_overlap;

        اگر (SDL_GetDisplayBounds(کھڑکی->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            کھڑکی_rect.x = کھڑکی->x;
            کھڑکی_rect.y = کھڑکی->y;
            کھڑکی_rect.w = کھڑکی->w;
            کھڑکی_rect.h = کھڑکی->h;

            اگر (SDL_GetRectIntersection(&old_bounds, &کھڑکی_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &کھڑکی_rect, &new_overlap)) {
                صحیح old_area = old_overlap.w * old_overlap.h;
                صحیح new_area = new_overlap.w * new_overlap.h;
                اعشاری new_overlap_تناسب = (new_area / ((اعشاری)old_area + new_area));
                اگر (new_overlap_تناسب < 0.80) {
                    واپس;
                }
            }
        }
    }

    اگر (displayID != کھڑکی->displayID) {
        صحیح i, display_اشاریہ;

        // Sanity check our fullscreen windows
        display_اشاریہ = SDL_Get_Display_اشاریہ(displayID);
        برائے (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            اگر (display->fullscreen_کھڑکی == کھڑکی) {
                اگر (display_اشاریہ != i) {
                    اگر (display_اشاریہ < 0) {
                        display_اشاریہ = i;
                    } ورنہ {
                        SDL_VideoDisplay *new_display = _this->displays[display_اشاریہ];

                        // The window was moved to a different display
                        اگر (new_display->fullscreen_کھڑکی &&
                            new_display->fullscreen_کھڑکی != کھڑکی) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_کھڑکی(new_display->fullscreen_کھڑکی);
                        }
                        new_display->fullscreen_کھڑکی = کھڑکی;
                        display->fullscreen_کھڑکی = تہی;
                    }
                }
                توڑو;
            }
        }

        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DISPLAY_بدلا, (صحیح)displayID, 0);
    }
}

اعشاری SDL_Get_کھڑکی_Pixel_Density(SDL_کھڑکی *کھڑکی)
{
    صحیح کھڑکی_w, کھڑکی_h, pixel_w, pixel_h;
    اعشاری pixel_density = 1.0f;

    CHECK_کھڑکی_MAGIC(کھڑکی, 0.0f);

    اگر (SDL_Get_کھڑکی_سائز(کھڑکی, &کھڑکی_w, &کھڑکی_h) &&
        SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &pixel_w, &pixel_h)) {
        pixel_density = (اعشاری)pixel_w / کھڑکی_w;
    }
    واپس pixel_density;
}

اعشاری SDL_Get_کھڑکی_Display_Scale(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0.0f);

    واپس کھڑکی->display_scale;
}

ساکن خالی SDL_Check_کھڑکی_Display_Scale_بدلا(SDL_کھڑکی *کھڑکی)
{
    اعشاری display_scale;

    اگر (_this->Get_کھڑکی_Content_Scale) {
        display_scale = _this->Get_کھڑکی_Content_Scale(_this, کھڑکی);
    } ورنہ {
        ثابت اعشاری pixel_density = SDL_Get_کھڑکی_Pixel_Density(کھڑکی);
        ثابت اعشاری content_scale = SDL_GetDisplayContentScale(کھڑکی->displayID);

        display_scale = pixel_density * content_scale;
    }

    اگر (display_scale != کھڑکی->display_scale) {
        کھڑکی->display_scale = display_scale;
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DISPLAY_SCALE_بدلا, 0, 0);
    }
}

bool SDL_Update_Fullscreen_منوال(SDL_کھڑکی *کھڑکی, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = تہی;
    SDL_Display_منوال *منوال = تہی;
    صحیح i;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    کھڑکی->fullscreen_exclusive = false;
    کھڑکی->update_fullscreen_on_display_بدلا = false;

    // If we are in the process of hiding don't go back to fullscreen
    اگر (کھڑکی->is_destroying || کھڑکی->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    اگر (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_کھڑکی(کھڑکی);
        اگر (!display) {
            // This should never happen, but it did...
            جاؤ مکمل;
        }
    } ورنہ {
        برائے (i = 0; i < _this->عدد_displays; ++i) {
            display = _this->displays[i];
            اگر (display->fullscreen_کھڑکی == کھڑکی) {
                توڑو;
            }
        }
        اگر (!display || i == _this->عدد_displays) {
            // Already not fullscreen on any display
            display = تہی;
        }
    }

    اگر (fullscreen) {
        منوال = (SDL_Display_منوال *)SDL_Get_کھڑکی_Fullscreen_منوال(کھڑکی);
        اگر (منوال) {
            کھڑکی->fullscreen_exclusive = true;
        } ورنہ {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(کھڑکی->current_fullscreen_منوال);
        }
    }

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    اگر (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        اگر (کھڑکی->is_destroying && !کھڑکی->آخری_fullscreen_exclusive_display) {
            کھڑکی->fullscreen_exclusive = false;
            اگر (display) {
                display->fullscreen_کھڑکی = تہی;
            }
            جاؤ مکمل;
        }
        اگر (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            اگر (fullscreen && Cocoa_Is_کھڑکی_اندر_Fullscreen_Space(کھڑکی) && !کھڑکی->آخری_fullscreen_exclusive_display && کھڑکی->fullscreen_exclusive) {
                اگر (!Cocoa_سیٹ_کھڑکی_Fullscreen_Space(کھڑکی, false, true)) {
                    جاؤ error;
                }
            } ورنہ اگر (fullscreen && کھڑکی->آخری_fullscreen_exclusive_display && !کھڑکی->fullscreen_exclusive) {
                برائے (i = 0; i < _this->عدد_displays; ++i) {
                    SDL_VideoDisplay *آخری_display = _this->displays[i];
                    اگر (آخری_display->fullscreen_کھڑکی == کھڑکی) {
                        SDL_سیٹ_Display_منوال_For_Display(آخری_display, تہی);
                        اگر (_this->سیٹ_کھڑکی_Fullscreen) {
                            _this->سیٹ_کھڑکی_Fullscreen(_this, کھڑکی, آخری_display, false);
                        }
                        آخری_display->fullscreen_کھڑکی = تہی;
                    }
                }
            }

            اگر (Cocoa_سیٹ_کھڑکی_Fullscreen_Space(کھڑکی, !!fullscreen, syncHint)) {
                جاؤ مکمل;
            }
        }
    }
#اگر_ختم

    اگر (display) {
        // Restore the video mode on other displays if needed
        برائے (i = 0; i < _this->عدد_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            اگر (other != display && other->fullscreen_کھڑکی == کھڑکی) {
                SDL_سیٹ_Display_منوال_For_Display(other, تہی);
                other->fullscreen_کھڑکی = تہی;
            }
        }
    }

    اگر (fullscreen) {
        صحیح منوال_w = 0, منوال_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        اگر (display->fullscreen_کھڑکی &&
            display->fullscreen_کھڑکی != کھڑکی) {
            SDL_Minimize_کھڑکی(display->fullscreen_کھڑکی);
        }

        display->fullscreen_فعال = کھڑکی->fullscreen_exclusive;

        اگر (!SDL_سیٹ_Display_منوال_For_Display(display, منوال)) {
            جاؤ error;
        }
        اگر (commit) {
            SDL_Fullscreen_نتیجہ ret = SDL_FULLSCREEN_SUCCEEDED;
            اگر (_this->سیٹ_کھڑکی_Fullscreen) {
                ret = _this->سیٹ_کھڑکی_Fullscreen(_this, کھڑکی, display, fullscreen);
            } ورنہ {
                resized = true;
            }

            اگر (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_ENTER_FULLSCREEN, 0, 0);
                }
            } ورنہ اگر (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_فعال = false;
                جاؤ error;
            }
        }

        اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
            display->fullscreen_کھڑکی = کھڑکی;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            اگر (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                اگر (منوال) {
                    منوال_w = منوال->w;
                    منوال_h = منوال->h;
                    SDL_GetDisplayBounds(منوال->displayID, &displayRect);
                } ورنہ {
                    منوال_w = display->desktop_منوال.w;
                    منوال_h = display->desktop_منوال.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                اگر (کھڑکی->w != منوال_w || کھڑکی->h != منوال_h) {
                    resized = true;
                }

                SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, displayRect.x, displayRect.y);

                اگر (resized) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, منوال_w, منوال_h);
                } ورنہ {
                    SDL_On_کھڑکی_Resized(کھڑکی);
                }
            }
        }
    } ورنہ {
        bool resized = false;

        // Restore the desktop mode
        اگر (display) {
            display->fullscreen_فعال = false;

            SDL_سیٹ_Display_منوال_For_Display(display, تہی);
        }
        اگر (commit) {
            SDL_Fullscreen_نتیجہ ret = SDL_FULLSCREEN_SUCCEEDED;
            اگر (_this->سیٹ_کھڑکی_Fullscreen) {
                SDL_VideoDisplay *بھرا_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_کھڑکی(کھڑکی);
                اگر (بھرا_screen_display) {
                    ret = _this->سیٹ_کھڑکی_Fullscreen(_this, کھڑکی, بھرا_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } ورنہ {
                resized = true;
            }

            اگر (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
                }
            } ورنہ اگر (ret == SDL_FULLSCREEN_FAILED) {
                جاؤ error;
            }
        }

        اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
            اگر (display) {
                display->fullscreen_کھڑکی = تہی;
            }

            اگر (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MOVED, کھڑکی->windowed.x, کھڑکی->windowed.y);
                اگر (resized) {
                    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESIZED, کھڑکی->windowed.w, کھڑکی->windowed.h);
                } ورنہ {
                    SDL_On_کھڑکی_Resized(کھڑکی);
                }
            }
        }
    }

مکمل:
    کھڑکی->آخری_fullscreen_exclusive_display = display && (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && کھڑکی->fullscreen_exclusive ? display->id : 0;
    واپس true;

error:
    اگر (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    واپس false;
}

bool SDL_سیٹ_کھڑکی_Fullscreen_منوال(SDL_کھڑکی *کھڑکی, ثابت SDL_Display_منوال *منوال)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (منوال) {
        اگر (!SDL_Get_Fullscreen_منوال_مطابقت(منوال)) {
            واپس SDL_سیٹ_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&کھڑکی->requested_fullscreen_منوال, منوال);
    } ورنہ {
        SDL_zero(کھڑکی->requested_fullscreen_منوال);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&کھڑکی->current_fullscreen_منوال, &کھڑکی->requested_fullscreen_منوال);

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    اگر (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_کھڑکی_اندر_Fullscreen_Space_Transition(کھڑکی)) {
        SDL_Sync_کھڑکی(کھڑکی);
    }
#اگر_ختم
    اگر (SDL_کھڑکی_FULLSCREEN_VISIBLE(کھڑکی)) {
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(کھڑکی);
    }

    واپس true;
}

ثابت SDL_Display_منوال *SDL_Get_کھڑکی_Fullscreen_منوال(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, تہی);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, تہی);

    اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        واپس SDL_Get_Fullscreen_منوال_مطابقت(&کھڑکی->current_fullscreen_منوال);
    } ورنہ {
        واپس SDL_Get_Fullscreen_منوال_مطابقت(&کھڑکی->requested_fullscreen_منوال);
    }
}

خالی *SDL_Get_کھڑکی_ICCProfile(SDL_کھڑکی *کھڑکی, size_t *سائز)
{
    اگر (!_this->Get_کھڑکی_ICCProfile) {
        SDL_Unsupported();
        واپس تہی;
    }
    واپس _this->Get_کھڑکی_ICCProfile(_this, کھڑکی, سائز);
}

SDL_PixelFormat SDL_Get_کھڑکی_Pixel_Format(SDL_کھڑکی *کھڑکی)
{
    SDL_DisplayID displayID;
    ثابت SDL_Display_منوال *منوال;

    CHECK_کھڑکی_MAGIC(کھڑکی, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_کھڑکی(کھڑکی);
    منوال = SDL_Get_Current_Display_منوال(displayID);
    اگر (منوال) {
        واپس منوال->format;
    } ورنہ {
        واپس SDL_PIXELFORMAT_UNKNOWN;
    }
}

#تعریف_کرو CREATE_FLAGS \
    (SDL_کھڑکی_OPENGL | SDL_کھڑکی_BORDERLESS | SDL_کھڑکی_RESIZABLE | SDL_کھڑکی_بلند_PIXEL_DENSITY | SDL_کھڑکی_ALWAYS_ON_چوٹی | SDL_کھڑکی_POPUP_MENU | SDL_کھڑکی_UTILITY | SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_VULKAN | SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_METAL | SDL_کھڑکی_TRANSPARENT | SDL_کھڑکی_NOT_FOCUSABLE | SDL_کھڑکی_FILL_DOCUMENT)

ساکن SDL_INLINE bool IsAcceptingDragAndDrop(خالی)
{
    اگر (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_متن)) {
        واپس true;
    }
    واپس false;
}

// prepare a newly-created window
ساکن SDL_INLINE خالی PrepareDragAndDropSupport(SDL_کھڑکی *کھڑکی)
{
    اگر (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(کھڑکی, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
خالی SDL_ToggleDragAndDropSupport(خالی)
{
    اگر (_this && _this->AcceptDragAndDrop) {
        ثابت bool enable = IsAcceptingDragAndDrop();
        SDL_کھڑکی *کھڑکی;
        برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            _this->AcceptDragAndDrop(کھڑکی, enable);
        }
    }
}

SDL_کھڑکی ** SDLCALL SDL_GetWindows(صحیح *گنتی)
{
    اگر (گنتی) {
        *گنتی = 0;
    }

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }

    SDL_کھڑکی *کھڑکی;
    صحیح عدد_added = 0;
    صحیح عدد_windows = 0;
    برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        ++عدد_windows;
    }

    SDL_کھڑکی **windows = (SDL_کھڑکی **)SDL_malloc((عدد_windows + 1) * حجم(*windows));
    اگر (!windows) {
        واپس تہی;
    }

    برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        windows[عدد_added++] = کھڑکی;
        اگر (عدد_added == عدد_windows) {
            // Race condition? Multi-threading not supported, ignore it
            توڑو;
        }
    }
    windows[عدد_added] = تہی;

    اگر (گنتی) {
        *گنتی = عدد_added;
    }
    واپس windows;
}

ساکن خالی Apply_کھڑکی_Flags(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    اگر (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        اگر (!(flags & (SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_MAXIMIZED))) {
            SDL_Restore_کھڑکی(کھڑکی);
        }
        اگر (flags & SDL_کھڑکی_MAXIMIZED) {
            SDL_Maximize_کھڑکی(کھڑکی);
        }

        SDL_سیٹ_کھڑکی_Fullscreen(کھڑکی, (flags & SDL_کھڑکی_FULLSCREEN) != 0);

        اگر (flags & SDL_کھڑکی_MINIMIZED) {
            SDL_Minimize_کھڑکی(کھڑکی);
        }

        اگر (flags & SDL_کھڑکی_MODAL) {
            SDL_سیٹ_کھڑکی_Modal(کھڑکی, true);
        }

        اگر (flags & SDL_کھڑکی_MOUSE_GRABBED) {
            SDL_سیٹ_کھڑکی_Mouse_Grab(کھڑکی, true);
        }
        اگر (flags & SDL_کھڑکی_KEYBOARD_GRABBED) {
            SDL_سیٹ_کھڑکی_Keyboard_Grab(کھڑکی, true);
        }
    }
}

ساکن خالی SDL_اختتام_کھڑکی_Creation(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    PrepareDragAndDropSupport(کھڑکی);

    اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } ورنہ {
        Apply_کھڑکی_Flags(کھڑکی, flags);
        اگر (!(flags & SDL_کھڑکی_HIDDEN)) {
            SDL_Show_کھڑکی(کھڑکی);
        }
    }

#اگر defined(SDL_PLATFORM_LINUX)
    اگر (!SDL_کھڑکی_IS_POPUP(کھڑکی)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_سیٹ_کھڑکی_پیش_رفت_State(کھڑکی, SDL_پیش_رفت_STATE_NONE);
        SDL_سیٹ_کھڑکی_پیش_رفت_قدر(کھڑکی, 0.0f);
    }
#اگر_ختم
}

ساکن bool SDL_ContextNotSupported(ثابت حرف *name)
{
    واپس SDL_سیٹ_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

ساکن bool SDL_DllNotSupported(ثابت حرف *name)
{
    واپس SDL_سیٹ_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

ساکن ساخت {
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

ساکن SDL_کھڑکی_Flags SDL_Get_کھڑکی_Flag_Properties(SDL_PropertiesID props)
{
    غیرعلامتی i;
    SDL_کھڑکی_Flags flags = (SDL_کھڑکی_Flags)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_FLAGS_نمبر, 0);

    برائے (i = 0; i < SDL_arraysize(SDL_کھڑکی_Flag_Properties); ++i) {
        اگر (SDL_کھڑکی_Flag_Properties[i].invert_قدر) {
            اگر (!SDL_GetBooleanProperty(props, SDL_کھڑکی_Flag_Properties[i].property_name, true)) {
                flags |= SDL_کھڑکی_Flag_Properties[i].flag;
            }
        } ورنہ {
            اگر (SDL_GetBooleanProperty(props, SDL_کھڑکی_Flag_Properties[i].property_name, false)) {
                flags |= SDL_کھڑکی_Flag_Properties[i].flag;
            }
        }
    }
    واپس flags;
}

SDL_کھڑکی *SDL_Create_کھڑکی_With_Properties(SDL_PropertiesID props)
{
    SDL_کھڑکی *کھڑکی;
    ثابت حرف *title = SDL_GetStringProperty(props, SDL_PROP_کھڑکی_CREATE_TITLE_STRING, تہی);
    صحیح x = (صحیح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_X_نمبر, SDL_WINDOWPOS_UNDEFINED);
    صحیح y = (صحیح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_Y_نمبر, SDL_WINDOWPOS_UNDEFINED);
    صحیح w = (صحیح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_چوڑائی_نمبر, 0);
    صحیح h = (صحیح)SDL_Get_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_اونچائی_نمبر, 0);
    SDL_کھڑکی *والد = (SDL_کھڑکی *)SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_CREATE_والد_اشارہ_گر, تہی);
    SDL_کھڑکی_Flags flags = SDL_Get_کھڑکی_Flag_Properties(props);
    SDL_کھڑکی_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_کھڑکی_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    اگر (!_this) {
        // Initialize the video system if needed
        اگر (!SDL_Init(SDL_INIT_VIDEO)) {
            واپس تہی;
        }

        // Make clang-tidy happy
        اگر (!_this) {
            واپس تہی;
        }
    }

    اگر ((flags & SDL_کھڑکی_MODAL) && !SDL_ObjectValid(والد, SDL_OBJECT_TYPE_کھڑکی)) {
        SDL_سیٹ_Error("Modal windows must specify a parent window");
        واپس تہی;
    }

    اگر ((flags & (SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_POPUP_MENU)) != 0) {
        اگر (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_کھڑکی_SUPPORT)) {
            SDL_Unsupported();
            واپس تہی;
        }

        // Tooltip and popup menu window must specify a parent window
        اگر (!SDL_ObjectValid(والد, SDL_OBJECT_TYPE_کھڑکی)) {
            SDL_سیٹ_Error("Tooltip and popup menu windows must specify a parent window");
            واپس تہی;
        }

        // Remove invalid flags
        flags &= ~(SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_کھڑکی_UTILITY | SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_POPUP_MENU | SDL_کھڑکی_MODAL);
    اگر (type_flags & (type_flags - 1)) {
        SDL_سیٹ_Error("Conflicting window type flags specified: 0x%.8x", (غیرعلامتی صحیح)type_flags);
        واپس تہی;
    }

    // Make sure the display list is up to date for window placement
    اگر (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    اگر (w < 1) {
        w = 1;
    }
    اگر (h < 1) {
        h = 1;
    }

    اگر (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        اگر ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ورنہ اگر ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        اگر (displayID == 0 || SDL_Get_Display_اشاریہ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        اگر (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            اگر (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            اگر (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    اگر (graphics_flags & (graphics_flags - 1)) {
        SDL_سیٹ_Error("Conflicting window graphics flags specified: 0x%.8x", (غیرعلامتی صحیح)graphics_flags);
        واپس تہی;
    }

    // Some platforms have certain graphics backends enabled by default
    اگر (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    اگر (flags & SDL_کھڑکی_OPENGL) {
        اگر (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            واپس تہی;
        }
        اگر (!SDL_GL_بھرو_Library(تہی)) {
            واپس تہی;
        }
    }

    اگر (flags & SDL_کھڑکی_VULKAN) {
        اگر (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            واپس تہی;
        }
        اگر (!SDL_Vulkan_بھرو_Library(تہی)) {
            واپس تہی;
        }
    }

    اگر (flags & SDL_کھڑکی_METAL) {
        اگر (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            واپس تہی;
        }
    }

    کھڑکی = (SDL_کھڑکی *)SDL_calloc(1, حجم(*کھڑکی));
    اگر (!کھڑکی) {
        واپس تہی;
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
    اگر (display) {
        SDL_سیٹ_کھڑکی_HDRProperties(کھڑکی, &display->HDR, false);
    }

    اگر (flags & SDL_کھڑکی_FULLSCREEN || IsFullscreenOnly(_this)) {
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

    اگر (!_this->سیٹ_کھڑکی_Fill_Document) {
        کھڑکی->flags &= ~SDL_کھڑکی_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    اگر (_this->windows) {
        _this->windows->پچھلا = کھڑکی;
    }
    _this->windows = کھڑکی;

    // Set the parent before creation.
    SDL_Update_کھڑکی_Hierarchy(کھڑکی, والد);

    اگر (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, کھڑکی, props)) {
        SDL_ڈالو_Error();
        SDL_Destroy_کھڑکی(کھڑکی);
        SDL_نکالو_Error();
        واپس تہی;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#اگر !defined(SDL_PLATFORM_WINDOWS)
    اگر (کھڑکی->flags & SDL_کھڑکی_MINIMIZED) {
        کھڑکی->flags &= ~SDL_کھڑکی_MINIMIZED;
    }
#اگر_ختم

    اگر (title) {
        SDL_سیٹ_کھڑکی_Title(کھڑکی, title);
    }
    SDL_اختتام_کھڑکی_Creation(کھڑکی, flags);

    // Make sure window pixel size is up to date
    SDL_Check_کھڑکی_Pixel_سائز_بدلا(کھڑکی);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#اگر_ختم

    SDL_ClearError();

    واپس کھڑکی;
}

SDL_کھڑکی *SDL_Create_کھڑکی(ثابت حرف *title, صحیح w, صحیح h, SDL_کھڑکی_Flags flags)
{
    SDL_کھڑکی *کھڑکی;
    SDL_PropertiesID props = SDL_CreateProperties();
    اگر (title && *title) {
        SDL_سیٹ_String_Property(props, SDL_PROP_کھڑکی_CREATE_TITLE_STRING, title);
    }
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_چوڑائی_نمبر, w);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_اونچائی_نمبر, h);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_FLAGS_نمبر, flags);
    کھڑکی = SDL_Create_کھڑکی_With_Properties(props);
    SDL_DestroyProperties(props);
    واپس کھڑکی;
}

SDL_کھڑکی *SDL_Create_Popup_کھڑکی(SDL_کھڑکی *والد, صحیح انحراف_x, صحیح انحراف_y, صحیح w, صحیح h, SDL_کھڑکی_Flags flags)
{
    SDL_کھڑکی *کھڑکی;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    اگر (!(flags & (SDL_کھڑکی_TOOLTIP | SDL_کھڑکی_POPUP_MENU))) {
        SDL_سیٹ_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        واپس تہی;
    }

    SDL_سیٹ_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_CREATE_والد_اشارہ_گر, والد);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_X_نمبر, انحراف_x);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_Y_نمبر, انحراف_y);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_چوڑائی_نمبر, w);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_اونچائی_نمبر, h);
    SDL_سیٹ_نمبر_Property(props, SDL_PROP_کھڑکی_CREATE_FLAGS_نمبر, flags);
    کھڑکی = SDL_Create_کھڑکی_With_Properties(props);
    SDL_DestroyProperties(props);
    واپس کھڑکی;
}

ساکن bool SDL_Reconfigure_کھڑکی_اندرونی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    اگر (!_this->Reconfigure_کھڑکی) {
        واپس false;
    }

    ثابت SDL_کھڑکی_Flags graphics_flags = flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    اگر (graphics_flags & (graphics_flags - 1)) {
        واپس SDL_سیٹ_Error("Conflicting window flags specified");
    }

    اگر ((flags & SDL_کھڑکی_OPENGL) && !_this->GL_CreateContext) {
        واپس SDL_ContextNotSupported("OpenGL");
    }
    اگر ((flags & SDL_کھڑکی_VULKAN) && !_this->Vulkan_CreateSurface) {
        واپس SDL_ContextNotSupported("Vulkan");
    }
    اگر ((flags & SDL_کھڑکی_METAL) && !_this->Metal_CreateView) {
        واپس SDL_ContextNotSupported("Metal");
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        اگر (کھڑکی->flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN)) {
            واپس false;
        }
    } ورنہ {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        اگر (!_this->Reconfigure_کھڑکی(_this, کھڑکی, 0)) {
            واپس false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        اگر (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        کھڑکی->flags &= ~(SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    }

    SDL_Destroy_کھڑکی_Surface(کھڑکی);

    اگر (graphics_flags & SDL_کھڑکی_OPENGL) {
        loaded_opengl = SDL_GL_بھرو_Library(تہی);
        اگر (!loaded_opengl) {
            واپس false;
        }
    } ورنہ اگر (graphics_flags & SDL_کھڑکی_VULKAN) {
        loaded_vulkan = SDL_Vulkan_بھرو_Library(تہی);
        اگر (!loaded_vulkan) {
            واپس false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    اگر (!_this->Reconfigure_کھڑکی(_this, کھڑکی, graphics_flags)) {
        اگر (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        اگر (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        واپس false;
    }

    کھڑکی->flags |= graphics_flags;

    واپس true;
}

bool SDL_Recreate_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_بھرو = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_بھرو = false;
    SDL_کھڑکی_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_کھڑکی_OPENGL | SDL_کھڑکی_METAL | SDL_کھڑکی_VULKAN);
    اگر (graphics_flags & (graphics_flags - 1)) {
        واپس SDL_سیٹ_Error("Conflicting window flags specified");
    }

    اگر ((flags & SDL_کھڑکی_OPENGL) && !_this->GL_CreateContext) {
        واپس SDL_ContextNotSupported("OpenGL");
    }
    اگر ((flags & SDL_کھڑکی_VULKAN) && !_this->Vulkan_CreateSurface) {
        واپس SDL_ContextNotSupported("Vulkan");
    }
    اگر ((flags & SDL_کھڑکی_METAL) && !_this->Metal_CreateView) {
        واپس SDL_ContextNotSupported("Metal");
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_کھڑکی_EXTERNAL;
    } ورنہ {
        flags &= ~SDL_کھڑکی_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    اگر (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        SDL_سیٹ_کھڑکی_Modal(کھڑکی, false);
    }

    // Restore video mode, etc.
    اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        ثابت bool restore_on_show = کھڑکی->restore_on_show;
        SDL_Hide_کھڑکی(کھڑکی);
        کھڑکی->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_کھڑکی_Surface(کھڑکی);

    اگر ((کھڑکی->flags & SDL_کھڑکی_OPENGL) != (flags & SDL_کھڑکی_OPENGL)) {
        اگر (flags & SDL_کھڑکی_OPENGL) {
            need_gl_بھرو = true;
        } ورنہ {
            need_gl_unload = true;
        }
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        need_gl_unload = true;
        need_gl_بھرو = true;
    }

    اگر ((کھڑکی->flags & SDL_کھڑکی_VULKAN) != (flags & SDL_کھڑکی_VULKAN)) {
        اگر (flags & SDL_کھڑکی_VULKAN) {
            need_vulkan_بھرو = true;
        } ورنہ {
            need_vulkan_unload = true;
        }
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_بھرو = true;
    }

    اگر (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    اگر (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    اگر (_this->Destroy_کھڑکی && !(flags & SDL_کھڑکی_EXTERNAL)) {
        _this->Destroy_کھڑکی(_this, کھڑکی);
    }

    اگر (need_gl_بھرو) {
        اگر (!SDL_GL_بھرو_Library(تہی)) {
            واپس false;
        }
        loaded_opengl = true;
    }

    اگر (need_vulkan_بھرو) {
        اگر (!SDL_Vulkan_بھرو_Library(تہی)) {
            واپس false;
        }
        loaded_vulkan = true;
    }

    کھڑکی->flags = ((flags & CREATE_FLAGS) | SDL_کھڑکی_HIDDEN);
    کھڑکی->is_destroying = false;

    اگر (_this->CreateSDLWindow && !(flags & SDL_کھڑکی_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        کھڑکی->x = کھڑکی->windowed.x = کھڑکی->floating.x;
        کھڑکی->y = کھڑکی->windowed.y = کھڑکی->floating.y;
        کھڑکی->w = کھڑکی->windowed.w = کھڑکی->floating.w;
        کھڑکی->h = کھڑکی->windowed.h = کھڑکی->floating.h;

        اگر (!_this->CreateSDLWindow(_this, کھڑکی, 0)) {
            اگر (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                کھڑکی->flags &= ~SDL_کھڑکی_OPENGL;
            }
            اگر (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                کھڑکی->flags &= ~SDL_کھڑکی_VULKAN;
            }
            واپس false;
        }
    }

    اگر (flags & SDL_کھڑکی_EXTERNAL) {
        کھڑکی->flags |= SDL_کھڑکی_EXTERNAL;
    }

    اگر (_this->سیٹ_کھڑکی_Title && کھڑکی->title) {
        _this->سیٹ_کھڑکی_Title(_this, کھڑکی);
    }

    اگر (_this->سیٹ_کھڑکی_Icon && کھڑکی->icon) {
        _this->سیٹ_کھڑکی_Icon(_this, کھڑکی, کھڑکی->icon);
    }

    اگر (_this->سیٹ_کھڑکی_Minimum_سائز && (کھڑکی->min_w || کھڑکی->min_h)) {
        _this->سیٹ_کھڑکی_Minimum_سائز(_this, کھڑکی);
    }

    اگر (_this->سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز && (کھڑکی->max_w || کھڑکی->max_h)) {
        _this->سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(_this, کھڑکی);
    }

    اگر (_this->سیٹ_کھڑکی_Aspect_تناسب && (کھڑکی->min_aspect > 0.0f || کھڑکی->max_aspect > 0.0f)) {
        _this->سیٹ_کھڑکی_Aspect_تناسب(_this, کھڑکی);
    }

    اگر (کھڑکی->کامیابی_test) {
        _this->سیٹ_کھڑکی_کامیابی_Test(کھڑکی, true);
    }

    SDL_اختتام_کھڑکی_Creation(کھڑکی, flags);

    واپس true;
}

bool SDL_Reconfigure_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    اگر (!SDL_Reconfigure_کھڑکی_اندرونی(کھڑکی, flags)) {
        واپس SDL_Recreate_کھڑکی(کھڑکی, flags);
    }

    واپس true;
}

bool SDL_HasWindows(خالی)
{
    واپس _this && _this->windows;
}

SDL_کھڑکی_ID SDL_Get_کھڑکی_ID(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    واپس کھڑکی->id;
}

SDL_کھڑکی *SDL_Get_کھڑکی_From_ID(SDL_کھڑکی_ID id)
{
    SDL_کھڑکی *کھڑکی;

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    اگر (id) {
        برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            اگر (کھڑکی->id == id) {
                واپس کھڑکی;
            }
        }
    }
    SDL_سیٹ_Error("Invalid window ID");
    واپس تہی;
}

SDL_کھڑکی *SDL_Get_کھڑکی_والد(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, تہی);

    واپس کھڑکی->والد;
}

SDL_PropertiesID SDL_Get_کھڑکی_Properties(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    اگر (کھڑکی->props == 0) {
        کھڑکی->props = SDL_CreateProperties();
    }
    واپس کھڑکی->props;
}

SDL_کھڑکی_Flags SDL_Get_کھڑکی_Flags(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, 0);

    واپس کھڑکی->flags | کھڑکی->pending_flags;
}

bool SDL_سیٹ_کھڑکی_Title(SDL_کھڑکی *کھڑکی, ثابت حرف *title)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (title == کھڑکی->title) {
        واپس true;
    }
    اگر (!title) {
        title = "";
    }
    اگر (کھڑکی->title && SDL_strcmp(title, کھڑکی->title) == 0) {
        واپس true;
    }

    SDL_free(کھڑکی->title);

    کھڑکی->title = SDL_strdup(title);

    اگر (_this->سیٹ_کھڑکی_Title) {
        _this->سیٹ_کھڑکی_Title(_this, کھڑکی);
    }
    واپس true;
}

ثابت حرف *SDL_Get_کھڑکی_Title(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, "");

    واپس کھڑکی->title ? کھڑکی->title : "";
}

bool SDL_سیٹ_کھڑکی_Icon(SDL_کھڑکی *کھڑکی, SDL_Surface *icon)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    CHECK_PARAM(!icon) {
        واپس SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(کھڑکی->icon);

    // Convert the icon into ARGB8888
    کھڑکی->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    اگر (!کھڑکی->icon) {
        واپس false;
    }

    اگر (!_this->سیٹ_کھڑکی_Icon) {
        واپس SDL_Unsupported();
    }

    واپس _this->سیٹ_کھڑکی_Icon(_this, کھڑکی, کھڑکی->icon);
}

bool SDL_سیٹ_کھڑکی_Position(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y)
{
    SDL_DisplayID original_displayID;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    ثابت صحیح w = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : کھڑکی->windowed.w;
    ثابت صحیح h = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : کھڑکی->windowed.h;

    original_displayID = Get_Display_For_کھڑکی(کھڑکی);
    کھڑکی->pending_displayID = 0;

    اگر (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = کھڑکی->windowed.x;
    }
    اگر (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = کھڑکی->windowed.y;
    }
    اگر (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        اگر (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } ورنہ اگر (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        اگر (displayID == 0 || SDL_Get_Display_اشاریہ(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        کھڑکی->pending_displayID = displayID;

        SDL_zero(bounds);
        اگر (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            اگر (!SDL_GetDisplayBounds(displayID, &bounds)) {
                واپس false;
            }
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        اگر (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } ورنہ {
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
    اگر (!_this->Sync_کھڑکی && (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        کھڑکی->floating.x = کھڑکی->windowed.x = x;
        کھڑکی->floating.y = کھڑکی->windowed.y = y;
    }
    کھڑکی->undefined_x = false;
    کھڑکی->undefined_y = false;
    کھڑکی->آخری_position_pending = true;

    اگر (_this->سیٹ_کھڑکی_Position) {
        ثابت bool نتیجہ = _this->سیٹ_کھڑکی_Position(_this, کھڑکی);
        اگر (نتیجہ) {
            SDL_SyncIfRequired(کھڑکی);
        }
        واپس نتیجہ;
    }

    واپس SDL_Unsupported();
}

bool SDL_Get_کھڑکی_Position(SDL_کھڑکی *کھڑکی, صحیح *x, صحیح *y)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

#اگر_تعریف_شدہ SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#ورنہ
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) != 0);
#اگر_ختم
    اگر (use_display_origin) {
        SDL_DisplayID displayID;

        اگر (x) {
            *x = 0;
        }
        اگر (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = Get_Display_For_کھڑکی(کھڑکی);
        اگر (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            اگر (x) {
                *x = bounds.x;
            }
            اگر (y) {
                *y = bounds.y;
            }
        }
    } ورنہ {
        ثابت bool use_pending = (کھڑکی->flags & SDL_کھڑکی_HIDDEN) && کھڑکی->آخری_position_pending;
        اگر (x) {
            *x = use_pending ? کھڑکی->pending.x : کھڑکی->x;
        }
        اگر (y) {
            *y = use_pending ? کھڑکی->pending.y : کھڑکی->y;
        }
    }
    واپس true;
}

bool SDL_سیٹ_کھڑکی_Bordered(SDL_کھڑکی *کھڑکی, bool bordered)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_Bordered) {
        واپس SDL_Unsupported();
    }

    ثابت bool want = bordered;
    ثابت bool have = !(کھڑکی->flags & SDL_کھڑکی_BORDERLESS);
    اگر (want != have) {
        اگر (want) {
            کھڑکی->flags &= ~SDL_کھڑکی_BORDERLESS;
        } ورنہ {
            کھڑکی->flags |= SDL_کھڑکی_BORDERLESS;
        }
        _this->سیٹ_کھڑکی_Bordered(_this, کھڑکی, want);
    }

    واپس true;
}

bool SDL_سیٹ_کھڑکی_Resizable(SDL_کھڑکی *کھڑکی, bool resizable)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_Resizable) {
        واپس SDL_Unsupported();
    }

    ثابت bool want = resizable;
    ثابت bool have = ((کھڑکی->flags & SDL_کھڑکی_RESIZABLE) != 0);
    اگر (want != have) {
        اگر (want) {
            کھڑکی->flags |= SDL_کھڑکی_RESIZABLE;
        } ورنہ {
            کھڑکی->flags &= ~SDL_کھڑکی_RESIZABLE;
            SDL_copyp(&کھڑکی->windowed, &کھڑکی->floating);
        }
        _this->سیٹ_کھڑکی_Resizable(_this, کھڑکی, want);
    }

    واپس true;
}

bool SDL_سیٹ_کھڑکی_Always_On_چوٹی(SDL_کھڑکی *کھڑکی, bool on_چوٹی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_Always_On_چوٹی) {
        واپس SDL_Unsupported();
    }

    ثابت bool want = on_چوٹی;
    ثابت bool have = ((کھڑکی->flags & SDL_کھڑکی_ALWAYS_ON_چوٹی) != 0);
    اگر (want != have) {
        اگر (want) {
            کھڑکی->flags |= SDL_کھڑکی_ALWAYS_ON_چوٹی;
        } ورنہ {
            کھڑکی->flags &= ~SDL_کھڑکی_ALWAYS_ON_چوٹی;
        }
        _this->سیٹ_کھڑکی_Always_On_چوٹی(_this, کھڑکی, want);
    }

    واپس true;
}

bool SDL_سیٹ_کھڑکی_سائز(SDL_کھڑکی *کھڑکی, صحیح w, صحیح h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    CHECK_PARAM(w <= 0) {
        واپس SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        واپس SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    اعشاری new_aspect = w / (اعشاری)h;
    اگر (کھڑکی->max_aspect > 0.0f && new_aspect > کھڑکی->max_aspect) {
        w = (صحیح)SDL_roundf(h * کھڑکی->max_aspect);
    } ورنہ اگر (کھڑکی->min_aspect > 0.0f && new_aspect < کھڑکی->min_aspect) {
        h = (صحیح)SDL_roundf(w / کھڑکی->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    اگر (کھڑکی->min_w && w < کھڑکی->min_w) {
        w = کھڑکی->min_w;
    }
    اگر (کھڑکی->max_w && w > کھڑکی->max_w) {
        w = کھڑکی->max_w;
    }
    اگر (کھڑکی->min_h && h < کھڑکی->min_h) {
        h = کھڑکی->min_h;
    }
    اگر (کھڑکی->max_h && h > کھڑکی->max_h) {
        h = کھڑکی->max_h;
    }

    کھڑکی->آخری_سائز_pending = true;
    کھڑکی->pending.w = w;
    کھڑکی->pending.h = h;

    اگر (_this->سیٹ_کھڑکی_سائز) {
        _this->سیٹ_کھڑکی_سائز(_this, کھڑکی);
        SDL_SyncIfRequired(کھڑکی);
    } ورنہ {
        واپس SDL_Unsupported();
    }
    واپس true;
}

bool SDL_Get_کھڑکی_سائز(SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    اگر (w) {
        *w = کھڑکی->w;
    }
    اگر (h) {
        *h = کھڑکی->h;
    }
    واپس true;
}

bool SDL_سیٹ_کھڑکی_Aspect_تناسب(SDL_کھڑکی *کھڑکی, اعشاری min_aspect, اعشاری max_aspect)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    کھڑکی->min_aspect = min_aspect;
    کھڑکی->max_aspect = max_aspect;

    اگر (_this->سیٹ_کھڑکی_Aspect_تناسب) {
        _this->سیٹ_کھڑکی_Aspect_تناسب(_this, کھڑکی);
    }

    // Ensure that window has the correct aspect ratio
    صحیح w = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
    صحیح h = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
    واپس SDL_سیٹ_کھڑکی_سائز(کھڑکی, w, h);
}

bool SDL_Get_کھڑکی_Aspect_تناسب(SDL_کھڑکی *کھڑکی, اعشاری *min_aspect, اعشاری *max_aspect)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (min_aspect) {
        *min_aspect = کھڑکی->min_aspect;
    }
    اگر (max_aspect) {
        *max_aspect = کھڑکی->max_aspect;
    }
    واپس true;
}

bool SDL_Get_کھڑکی_Borders_سائز(SDL_کھڑکی *کھڑکی, صحیح *چوٹی, صحیح *بایاں, صحیح *bottom, صحیح *دایاں)
{
    صحیح dummy = 0;

    اگر (!چوٹی) {
        چوٹی = &dummy;
    }
    اگر (!بایاں) {
        بایاں = &dummy;
    }
    اگر (!دایاں) {
        دایاں = &dummy;
    }
    اگر (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *چوٹی = *بایاں = *bottom = *دایاں = 0;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!_this->Get_کھڑکی_Borders_سائز) {
        واپس SDL_Unsupported();
    }

    واپس _this->Get_کھڑکی_Borders_سائز(_this, کھڑکی, چوٹی, بایاں, bottom, دایاں);
}

bool SDL_Get_کھڑکی_سائز_اندر_Pixels(SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h)
{
    صحیح filter;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!w) {
        w = &filter;
    }

    اگر (!h) {
        h = &filter;
    }

    اگر (_this->Get_کھڑکی_سائز_اندر_Pixels) {
        _this->Get_کھڑکی_سائز_اندر_Pixels(_this, کھڑکی, w, h);
    } ورنہ {
        SDL_DisplayID displayID = Get_Display_For_کھڑکی(کھڑکی);
        ثابت SDL_Display_منوال *منوال;

        SDL_Get_کھڑکی_سائز(کھڑکی, w, h);

        اگر ((کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) && SDL_Get_کھڑکی_Fullscreen_منوال(کھڑکی)) {
            منوال = SDL_Get_Current_Display_منوال(displayID);
        } ورنہ {
            منوال = SDL_Get_Desktop_Display_منوال(displayID);
        }
        اگر (منوال) {
            *w = (صحیح)SDL_ceilf(*w * منوال->pixel_density);
            *h = (صحیح)SDL_ceilf(*h * منوال->pixel_density);
        }
    }
    واپس true;
}

bool SDL_سیٹ_کھڑکی_Minimum_سائز(SDL_کھڑکی *کھڑکی, صحیح min_w, صحیح min_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_PARAM(min_w < 0) {
        واپس SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        واپس SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((کھڑکی->max_w && min_w > کھڑکی->max_w) || (کھڑکی->max_h && min_h > کھڑکی->max_h)) {
        واپس SDL_سیٹ_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    کھڑکی->min_w = min_w;
    کھڑکی->min_h = min_h;

    اگر (_this->سیٹ_کھڑکی_Minimum_سائز) {
        _this->سیٹ_کھڑکی_Minimum_سائز(_this, کھڑکی);
    }

    // Ensure that window is not smaller than minimal size
    صحیح w = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
    صحیح h = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
    واپس SDL_سیٹ_کھڑکی_سائز(کھڑکی, w, h);
}

bool SDL_Get_کھڑکی_Minimum_سائز(SDL_کھڑکی *کھڑکی, صحیح *min_w, صحیح *min_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    اگر (min_w) {
        *min_w = کھڑکی->min_w;
    }
    اگر (min_h) {
        *min_h = کھڑکی->min_h;
    }
    واپس true;
}

bool SDL_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(SDL_کھڑکی *کھڑکی, صحیح max_w, صحیح max_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_PARAM(max_w < 0) {
        واپس SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        واپس SDL_InvalidParamError("max_h");
    }

    اگر ((max_w && max_w < کھڑکی->min_w) ||
        (max_h && max_h < کھڑکی->min_h)) {
        واپس SDL_سیٹ_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    کھڑکی->max_w = max_w;
    کھڑکی->max_h = max_h;

    اگر (_this->سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز) {
        _this->سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(_this, کھڑکی);
    }

    // Ensure that window is not larger than maximal size
    صحیح w = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.w : کھڑکی->floating.w;
    صحیح h = کھڑکی->آخری_سائز_pending ? کھڑکی->pending.h : کھڑکی->floating.h;
    واپس SDL_سیٹ_کھڑکی_سائز(کھڑکی, w, h);
}

bool SDL_Get_کھڑکی_زیادہ_سے_زیادہ_سائز(SDL_کھڑکی *کھڑکی, صحیح *max_w, صحیح *max_h)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    اگر (max_w) {
        *max_w = کھڑکی->max_w;
    }
    اگر (max_h) {
        *max_h = کھڑکی->max_h;
    }
    واپس true;
}

bool SDL_Show_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی *بچہ;
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!(کھڑکی->flags & SDL_کھڑکی_HIDDEN)) {
        واپس true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    اگر (کھڑکی->والد && (کھڑکی->والد->flags & SDL_کھڑکی_HIDDEN)) {
        کھڑکی->restore_on_show = true;
        واپس true;
    }

    اگر (_this->Show_کھڑکی) {
        _this->Show_کھڑکی(_this, کھڑکی);
    } ورنہ {
        SDL_سیٹ_Mouse_Focus(کھڑکی);
        SDL_سیٹ_Keyboard_Focus(کھڑکی);
    }
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_SHOWN, 0, 0);

    // Restore child windows
    برائے (بچہ = کھڑکی->پہلا_بچہ; بچہ; بچہ = بچہ->اگلا_sibling) {
        اگر (!بچہ->restore_on_show && (بچہ->flags & SDL_کھڑکی_HIDDEN)) {
            توڑو;
        }
        SDL_Show_کھڑکی(بچہ);
        بچہ->restore_on_show = false;
    }
    واپس true;
}

bool SDL_Hide_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی *بچہ;
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->restore_on_show = false;
        واپس true;
    }

    // Hide all child windows
    برائے (بچہ = کھڑکی->پہلا_بچہ; بچہ; بچہ = بچہ->اگلا_sibling) {
        اگر (بچہ->flags & SDL_کھڑکی_HIDDEN) {
            توڑو;
        }
        SDL_Hide_کھڑکی(بچہ);
        بچہ->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ثابت SDL_کھڑکی_Flags pending_نقاب = (SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED | SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_KEYBOARD_GRABBED | SDL_کھڑکی_MOUSE_GRABBED);
    کھڑکی->pending_flags = (کھڑکی->flags & pending_نقاب);

    کھڑکی->is_hiding = true;
    اگر (_this->Hide_کھڑکی) {
        _this->Hide_کھڑکی(_this, کھڑکی);
    } ورنہ {
        SDL_سیٹ_Mouse_Focus(تہی);
        SDL_سیٹ_Keyboard_Focus(تہی);
    }
    کھڑکی->is_hiding = false;
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_HIDDEN, 0, 0);
    واپس true;
}

bool SDL_Raise_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        واپس true;
    }
    اگر (_this->Raise_کھڑکی) {
        _this->Raise_کھڑکی(_this, کھڑکی);
    }
    واپس true;
}

bool SDL_Maximize_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (!_this->Maximize_کھڑکی) {
        واپس SDL_Unsupported();
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_RESIZABLE)) {
        واپس SDL_سیٹ_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->pending_flags |= SDL_کھڑکی_MAXIMIZED;
        واپس true;
    }

    _this->Maximize_کھڑکی(_this, کھڑکی);
    SDL_SyncIfRequired(کھڑکی);
    واپس true;
}

bool SDL_Minimize_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (!_this->Minimize_کھڑکی) {
        واپس SDL_Unsupported();
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->pending_flags |= SDL_کھڑکی_MINIMIZED;
        واپس true;
    }

    _this->Minimize_کھڑکی(_this, کھڑکی);
    SDL_SyncIfRequired(کھڑکی);
    واپس true;
}

bool SDL_Restore_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (!_this->Restore_کھڑکی) {
        واپس SDL_Unsupported();
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        کھڑکی->pending_flags &= ~(SDL_کھڑکی_MAXIMIZED | SDL_کھڑکی_MINIMIZED);
        واپس true;
    }

    _this->Restore_کھڑکی(_this, کھڑکی);
    SDL_SyncIfRequired(کھڑکی);
    واپس true;
}

bool SDL_سیٹ_کھڑکی_Fullscreen(SDL_کھڑکی *کھڑکی, bool fullscreen)
{
    bool نتیجہ;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        اگر (fullscreen) {
            کھڑکی->pending_flags |= SDL_کھڑکی_FULLSCREEN;
        } ورنہ {
            کھڑکی->pending_flags &= ~SDL_کھڑکی_FULLSCREEN;
        }
        واپس true;
    }

    اگر (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&کھڑکی->current_fullscreen_منوال, &کھڑکی->requested_fullscreen_منوال);
    }

    نتیجہ = SDL_Update_Fullscreen_منوال(کھڑکی, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    اگر (!fullscreen || !نتیجہ) {
        // Clear the current fullscreen mode.
        SDL_zero(کھڑکی->current_fullscreen_منوال);
    }

    اگر (نتیجہ) {
        SDL_SyncIfRequired(کھڑکی);
    }

    واپس نتیجہ;
}

bool SDL_Sync_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (_this->Sync_کھڑکی) {
        واپس _this->Sync_کھڑکی(_this, کھڑکی);
    } ورنہ {
        واپس true;
    }
}

ساکن bool ShouldAttemptTextureFramebuffer(خالی)
{
    ثابت حرف *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    اگر (!_this->Create_کھڑکی_Framebuffer) {
        واپس true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    اگر (hint && *hint) {
        اگر (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } ورنہ {
            attempt_texture_framebuffer = true;
        }
    } ورنہ {
        اگر (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } ورنہ {
            attempt_texture_framebuffer = false;
        }
    }
    واپس attempt_texture_framebuffer;
}

ساکن SDL_Surface *SDL_Create_کھڑکی_Framebuffer(SDL_کھڑکی *کھڑکی)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    خالی *pixels = تہی;
    صحیح pitch = 0;
    bool created_framebuffer = false;
    صحیح w, h;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    اگر (!_this->checked_texture_framebuffer) {
        اگر (ShouldAttemptTextureFramebuffer()) {
            اگر (!SDL_Create_کھڑکی_Texture(_this, کھڑکی, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } ورنہ {
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

    اگر (!created_framebuffer) {
        اگر (!_this->Create_کھڑکی_Framebuffer || !_this->Update_کھڑکی_Framebuffer) {
            SDL_سیٹ_Error("Window framebuffer support not available");
            واپس تہی;
        }

        اگر (!_this->Create_کھڑکی_Framebuffer(_this, کھڑکی, &format, &pixels, &pitch)) {
            واپس تہی;
        }
    }

    اگر (کھڑکی->surface) {
        // We may have gone recursive and already created the surface
        واپس کھڑکی->surface;
    }

    واپس SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_کھڑکی_Has_Surface(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    واپس کھڑکی->surface ? true : false;
}

SDL_Surface *SDL_Get_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, تہی);

    اگر (!کھڑکی->surface_valid) {
        اگر (کھڑکی->surface) {
            کھڑکی->surface->اندرونی_flags &= ~SDL_اندرونی_SURFACE_DONTFREE;
            SDL_DestroySurface(کھڑکی->surface);
            کھڑکی->surface = تہی;
        }

        کھڑکی->surface = SDL_Create_کھڑکی_Framebuffer(کھڑکی);
        اگر (کھڑکی->surface) {
            کھڑکی->surface_valid = true;
            کھڑکی->surface->اندرونی_flags |= SDL_اندرونی_SURFACE_DONTFREE;
        }
    }
    واپس کھڑکی->surface;
}

bool SDL_سیٹ_کھڑکی_Surface_VSync(SDL_کھڑکی *کھڑکی, صحیح vsync)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_Framebuffer_VSync) {
        واپس SDL_Unsupported();
    }
    واپس _this->سیٹ_کھڑکی_Framebuffer_VSync(_this, کھڑکی, vsync);
}

bool SDL_Get_کھڑکی_Surface_VSync(SDL_کھڑکی *کھڑکی, صحیح *vsync)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!_this->Get_کھڑکی_Framebuffer_VSync) {
        واپس SDL_Unsupported();
    }
    واپس _this->Get_کھڑکی_Framebuffer_VSync(_this, کھڑکی, vsync);
}

bool SDL_Update_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
    SDL_Rect بھرا_rect;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    بھرا_rect.x = 0;
    بھرا_rect.y = 0;
    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &بھرا_rect.w, &بھرا_rect.h);

    واپس SDL_Update_کھڑکی_Surface_Rects(کھڑکی, &بھرا_rect, 1);
}

bool SDL_Update_کھڑکی_Surface_Rects(SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects,
                                 صحیح numrects)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!کھڑکی->surface_valid) {
        واپس SDL_سیٹ_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    واپس _this->Update_کھڑکی_Framebuffer(_this, کھڑکی, rects, numrects);
}

bool SDL_Destroy_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (کھڑکی->surface) {
        کھڑکی->surface->اندرونی_flags &= ~SDL_اندرونی_SURFACE_DONTFREE;
        SDL_DestroySurface(کھڑکی->surface);
        کھڑکی->surface = تہی;
        کھڑکی->surface_valid = false;
    }

    اگر (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        اگر (_this->Destroy_کھڑکی_Framebuffer) {
            _this->Destroy_کھڑکی_Framebuffer(_this, کھڑکی);
        }
    }
    واپس true;
}

bool SDL_سیٹ_کھڑکی_Opacity(SDL_کھڑکی *کھڑکی, اعشاری opacity)
{
    bool نتیجہ;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_Opacity) {
        واپس SDL_Unsupported();
    }

    اگر (opacity < 0.0f) {
        opacity = 0.0f;
    } ورنہ اگر (opacity > 1.0f) {
        opacity = 1.0f;
    }

    نتیجہ = _this->سیٹ_کھڑکی_Opacity(_this, کھڑکی, opacity);
    اگر (نتیجہ) {
        کھڑکی->opacity = opacity;
    }

    واپس نتیجہ;
}

اعشاری SDL_Get_کھڑکی_Opacity(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, -1.0f);

    واپس کھڑکی->opacity;
}

bool SDL_سیٹ_کھڑکی_والد(SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (والد) {
        CHECK_کھڑکی_MAGIC(والد, false);
        CHECK_کھڑکی_NOT_POPUP(والد, false);
    }

    اگر (کھڑکی == والد) {
        واپس SDL_سیٹ_Error("Cannot set the parent of a window to itself.");
    }

    اگر (!_this->سیٹ_کھڑکی_والد) {
        واپس SDL_Unsupported();
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        واپس SDL_سیٹ_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    اگر (کھڑکی->والد == والد) {
        واپس true;
    }

    ثابت bool ret = _this->سیٹ_کھڑکی_والد(_this, کھڑکی, والد);
    SDL_Update_کھڑکی_Hierarchy(کھڑکی, ret ? والد : تہی);

    واپس ret;
}

bool SDL_سیٹ_کھڑکی_Modal(SDL_کھڑکی *کھڑکی, bool modal)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_Modal) {
        واپس SDL_Unsupported();
    }

    اگر (modal) {
        اگر (!کھڑکی->والد) {
            واپس SDL_سیٹ_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        کھڑکی->flags |= SDL_کھڑکی_MODAL;
    } ورنہ اگر (کھڑکی->flags & SDL_کھڑکی_MODAL) {
        کھڑکی->flags &= ~SDL_کھڑکی_MODAL;
    } ورنہ {
        واپس true; // Already not modal, so nothing to do.
    }

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        واپس true;
    }

    واپس _this->سیٹ_کھڑکی_Modal(_this, کھڑکی, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_کھڑکی *کھڑکی, SDL_کھڑکی **new_focus)
{
    SDL_کھڑکی *focus = کھڑکی->والد;
    bool سیٹ_focus = !!(کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    جب (SDL_کھڑکی_IS_POPUP(focus) && ((focus->flags & SDL_کھڑکی_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->والد;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        اگر (!سیٹ_focus) {
            سیٹ_focus = !!(focus->flags & SDL_کھڑکی_داخلہ_FOCUS);
        }
    }

    *new_focus = focus;
    واپس سیٹ_focus;
}

bool SDL_ShouldFocusPopup(SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی *toplevel_والد;
    برائے (toplevel_والد = کھڑکی->والد; SDL_کھڑکی_IS_POPUP(toplevel_والد); toplevel_والد = toplevel_والد->والد) {
    }

    SDL_کھڑکی *current_focus = toplevel_والد->keyboard_focus;
    bool ملا_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_کھڑکی *w;
    برائے (w = current_focus; w != toplevel_والد; w = w->والد) {
        اگر (w == کھڑکی) {
            ملا_higher_focus = true;
            توڑو;
        }
    }

    واپس !ملا_higher_focus || w == toplevel_والد;
}

bool SDL_سیٹ_کھڑکی_Focusable(SDL_کھڑکی *کھڑکی, bool focusable)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    ثابت bool want = (focusable != false); // normalize the flag.
    ثابت bool have = !(کھڑکی->flags & SDL_کھڑکی_NOT_FOCUSABLE);
    اگر ((want != have) && (_this->سیٹ_کھڑکی_Focusable)) {
        اگر (want) {
            کھڑکی->flags &= ~SDL_کھڑکی_NOT_FOCUSABLE;
        } ورنہ {
            کھڑکی->flags |= SDL_کھڑکی_NOT_FOCUSABLE;
        }
        اگر (!_this->سیٹ_کھڑکی_Focusable(_this, کھڑکی, want)) {
            واپس false;
        }
    }

    واپس true;
}

bool SDL_سیٹ_کھڑکی_Fill_Document(SDL_کھڑکی *کھڑکی, bool fill)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    ثابت bool want = (fill != false); // normalize the flag.
    ثابت bool have = ((کھڑکی->flags & SDL_کھڑکی_FILL_DOCUMENT) != 0);
    اگر ((want != have) && (_this->سیٹ_کھڑکی_Fill_Document)) {
        اگر (!_this->سیٹ_کھڑکی_Fill_Document(_this, کھڑکی, want)) {
            واپس false;
        } ورنہ اگر (want) {
            کھڑکی->flags |= SDL_کھڑکی_FILL_DOCUMENT;
        } ورنہ {
            کھڑکی->flags &= ~SDL_کھڑکی_FILL_DOCUMENT;
        }
    }

    واپس true;
}

خالی SDL_Update_کھڑکی_Grab(SDL_کھڑکی *کھڑکی)
{
    bool keyboard_grabbed, mouse_grabbed;

    اگر (کھڑکی->flags & SDL_کھڑکی_داخلہ_FOCUS) {
        اگر (SDL_GetMouse()->relative_منوال || (کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } ورنہ {
            mouse_grabbed = false;
        }

        اگر (کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } ورنہ {
            keyboard_grabbed = false;
        }
    } ورنہ {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    اگر (mouse_grabbed || keyboard_grabbed) {
        اگر (_this->grabbed_کھڑکی && (_this->grabbed_کھڑکی != کھڑکی)) {
            // stealing a grab from another window!
            _this->grabbed_کھڑکی->flags &= ~(SDL_کھڑکی_MOUSE_GRABBED | SDL_کھڑکی_KEYBOARD_GRABBED);
            اگر (_this->سیٹ_کھڑکی_Mouse_Grab) {
                _this->سیٹ_کھڑکی_Mouse_Grab(_this, _this->grabbed_کھڑکی, false);
            }
            اگر (_this->سیٹ_کھڑکی_Keyboard_Grab) {
                _this->سیٹ_کھڑکی_Keyboard_Grab(_this, _this->grabbed_کھڑکی, false);
            }
        }
        _this->grabbed_کھڑکی = کھڑکی;
    } ورنہ اگر (_this->grabbed_کھڑکی == کھڑکی) {
        _this->grabbed_کھڑکی = تہی; // ungrabbing input.
    }

    اگر (_this->سیٹ_کھڑکی_Mouse_Grab) {
        اگر (!_this->سیٹ_کھڑکی_Mouse_Grab(_this, کھڑکی, mouse_grabbed)) {
            کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_GRABBED;
        }
    }
    اگر (_this->سیٹ_کھڑکی_Keyboard_Grab) {
        اگر (!_this->سیٹ_کھڑکی_Keyboard_Grab(_this, کھڑکی, keyboard_grabbed)) {
            کھڑکی->flags &= ~SDL_کھڑکی_KEYBOARD_GRABBED;
        }
    }

    اگر (_this->grabbed_کھڑکی && !(_this->grabbed_کھڑکی->flags & (SDL_کھڑکی_MOUSE_GRABBED | SDL_کھڑکی_KEYBOARD_GRABBED))) {
        _this->grabbed_کھڑکی = تہی;
    }
}

bool SDL_سیٹ_کھڑکی_Keyboard_Grab(SDL_کھڑکی *کھڑکی, bool grabbed)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        اگر (grabbed) {
            کھڑکی->pending_flags |= SDL_کھڑکی_KEYBOARD_GRABBED;
        } ورنہ {
            کھڑکی->pending_flags &= ~SDL_کھڑکی_KEYBOARD_GRABBED;
        }
        واپس true;
    }

    اگر (!!grabbed == !!(کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED)) {
        واپس true;
    }
    اگر (grabbed) {
        کھڑکی->flags |= SDL_کھڑکی_KEYBOARD_GRABBED;
    } ورنہ {
        کھڑکی->flags &= ~SDL_کھڑکی_KEYBOARD_GRABBED;
    }
    SDL_Update_کھڑکی_Grab(کھڑکی);

    اگر (grabbed && !(کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED)) {
        واپس false;
    }
    واپس true;
}

bool SDL_سیٹ_کھڑکی_Mouse_Grab(SDL_کھڑکی *کھڑکی, bool grabbed)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        اگر (grabbed) {
            کھڑکی->pending_flags |= SDL_کھڑکی_MOUSE_GRABBED;
        } ورنہ {
            کھڑکی->pending_flags &= ~SDL_کھڑکی_MOUSE_GRABBED;
        }
        واپس true;
    }

    اگر (!!grabbed == !!(کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
        واپس true;
    }
    اگر (grabbed) {
        کھڑکی->flags |= SDL_کھڑکی_MOUSE_GRABBED;
    } ورنہ {
        کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_GRABBED;
    }
    SDL_Update_کھڑکی_Grab(کھڑکی);

    اگر (grabbed && !(کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED)) {
        واپس false;
    }
    واپس true;
}

bool SDL_Get_کھڑکی_Keyboard_Grab(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    واپس کھڑکی == _this->grabbed_کھڑکی && (_this->grabbed_کھڑکی->flags & SDL_کھڑکی_KEYBOARD_GRABBED);
}

bool SDL_Get_کھڑکی_Mouse_Grab(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    واپس کھڑکی == _this->grabbed_کھڑکی && (_this->grabbed_کھڑکی->flags & SDL_کھڑکی_MOUSE_GRABBED);
}

SDL_کھڑکی *SDL_Get_Grabbed_کھڑکی(خالی)
{
    اگر (_this && _this->grabbed_کھڑکی &&
        (_this->grabbed_کھڑکی->flags & (SDL_کھڑکی_MOUSE_GRABBED | SDL_کھڑکی_KEYBOARD_GRABBED)) != 0) {
        واپس _this->grabbed_کھڑکی;
    } ورنہ {
        واپس تہی;
    }
}

bool SDL_سیٹ_کھڑکی_Mouse_Rect(SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rect)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_Mouse_Rect) {
        واپس SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    اگر (!rect) {
        rect = &zero;
    }

    اگر (SDL_memcmp(&کھڑکی->mouse_rect, rect, حجم(*rect)) == 0) {
        واپس true;
    }
    SDL_memcpy(&کھڑکی->mouse_rect, rect, حجم(*rect));

    واپس _this->سیٹ_کھڑکی_Mouse_Rect(_this, کھڑکی);
}

ثابت SDL_Rect *SDL_Get_کھڑکی_Mouse_Rect(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, تہی);

    اگر (SDL_Rect_خالی_خانے(&کھڑکی->mouse_rect)) {
        واپس تہی;
    } ورنہ {
        واپس &کھڑکی->mouse_rect;
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

    اگر (enabled == SDL_Get_کھڑکی_Relative_Mouse_منوال(کھڑکی)) {
        واپس true;
    }

    اگر (enabled) {
        کھڑکی->flags |= SDL_کھڑکی_MOUSE_RELATIVE_منوال;
    } ورنہ {
        کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_RELATIVE_منوال;
    }

    اگر (!SDL_Update_Relative_Mouse_منوال()) {
        اگر (enabled) {
            کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_RELATIVE_منوال;
        } ورنہ {
            کھڑکی->flags |= SDL_کھڑکی_MOUSE_RELATIVE_منوال;
        }
        واپس false;
    }
    واپس true;
}

bool SDL_Get_کھڑکی_Relative_Mouse_منوال(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (کھڑکی->flags & SDL_کھڑکی_MOUSE_RELATIVE_منوال) {
        واپس true;
    } ورنہ {
        واپس false;
    }
}

bool SDL_Flash_کھڑکی(SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (_this->Flash_کھڑکی) {
        واپس _this->Flash_کھڑکی(_this, کھڑکی, operation);
    }

    واپس SDL_Unsupported();
}

bool SDL_سیٹ_کھڑکی_پیش_رفت_State(SDL_کھڑکی *کھڑکی, SDL_پیش_رفت_State state)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    CHECK_PARAM(state < SDL_پیش_رفت_STATE_NONE || state > SDL_پیش_رفت_STATE_ERROR) {
        واپس SDL_InvalidParamError("state");
    }

    کھڑکی->پیش_رفت_state = state;

    اگر (_this->Apply_کھڑکی_پیش_رفت) {
        اگر (!_this->Apply_کھڑکی_پیش_رفت(_this, کھڑکی)) {
            واپس false;
        }
    }

    واپس true;
}

SDL_پیش_رفت_State SDL_Get_کھڑکی_پیش_رفت_State(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, SDL_پیش_رفت_STATE_INVALID);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, SDL_پیش_رفت_STATE_INVALID);

    واپس کھڑکی->پیش_رفت_state;
}

bool SDL_سیٹ_کھڑکی_پیش_رفت_قدر(SDL_کھڑکی *کھڑکی, اعشاری قدر)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    قدر = SDL_clamp(قدر, 0.0f, 1.f);

    کھڑکی->پیش_رفت_قدر = قدر;

    اگر (_this->Apply_کھڑکی_پیش_رفت) {
        اگر (!_this->Apply_کھڑکی_پیش_رفت(_this, کھڑکی)) {
            واپس false;
        }
    }

    واپس true;
}

اعشاری SDL_Get_کھڑکی_پیش_رفت_قدر(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, -1.0f);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, -1.0f);

    واپس کھڑکی->پیش_رفت_قدر;
}

خالی SDL_On_کھڑکی_Shown(SDL_کھڑکی *کھڑکی)
{
    // Set window state if we have pending window flags cached
    Apply_کھڑکی_Flags(کھڑکی, کھڑکی->pending_flags);
    کھڑکی->pending_flags = 0;
}

خالی SDL_On_کھڑکی_Hidden(SDL_کھڑکی *کھڑکی)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    کھڑکی->pending_flags |= (کھڑکی->flags & (SDL_کھڑکی_FULLSCREEN | SDL_کھڑکی_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, false);
}

خالی SDL_On_کھڑکی_Display_بدلا(SDL_کھڑکی *کھڑکی)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    اگر (کھڑکی->update_fullscreen_on_display_بدلا && (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN)) {
        ثابت bool auto_منوال_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_مطابقت_EXCLUSIVE_منوال_ON_MOVE, true);

        اگر (auto_منوال_switch && (کھڑکی->requested_fullscreen_منوال.w != 0 || کھڑکی->requested_fullscreen_منوال.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_کھڑکی_Position(کھڑکی);
            bool include_بلند_density_modes = false;

            اگر (کھڑکی->requested_fullscreen_منوال.pixel_density > 1.0f) {
                include_بلند_density_modes = true;
            }
            ثابت bool ملا_مطابقت = SDL_Get_Closest_Fullscreen_Display_منوال(displayID, کھڑکی->requested_fullscreen_منوال.w, کھڑکی->requested_fullscreen_منوال.h,
                                                                         کھڑکی->requested_fullscreen_منوال.refresh_شرح, include_بلند_density_modes, &کھڑکی->current_fullscreen_منوال);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            اگر (!ملا_مطابقت ||
                کھڑکی->requested_fullscreen_منوال.w != کھڑکی->current_fullscreen_منوال.w ||
                کھڑکی->requested_fullscreen_منوال.h != کھڑکی->current_fullscreen_منوال.h) {
                SDL_zero(کھڑکی->current_fullscreen_منوال);
            }
        } ورنہ {
            SDL_zero(کھڑکی->current_fullscreen_منوال);
        }

        اگر (SDL_کھڑکی_FULLSCREEN_VISIBLE(کھڑکی)) {
            SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_کھڑکی_Pixel_سائز_بدلا(کھڑکی);
}

خالی SDL_On_کھڑکی_Moved(SDL_کھڑکی *کھڑکی)
{
    SDL_Check_کھڑکی_Display_بدلا(کھڑکی);
}

خالی SDL_On_کھڑکی_Resized(SDL_کھڑکی *کھڑکی)
{
    SDL_Check_کھڑکی_Display_بدلا(کھڑکی);
    SDL_Check_کھڑکی_Pixel_سائز_بدلا(کھڑکی);
    SDL_Check_کھڑکی_محفوظ_Area_بدلا(کھڑکی);

    اگر ((کھڑکی->flags & SDL_کھڑکی_TRANSPARENT) && _this->Update_کھڑکی_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_Get_اشارہ_گر_Property(کھڑکی->props, SDL_PROP_کھڑکی_SHAPE_اشارہ_گر, تہی);
        اگر (surface) {
            _this->Update_کھڑکی_Shape(_this, کھڑکی, surface);
        }
    }
}

خالی SDL_Check_کھڑکی_Pixel_سائز_بدلا(SDL_کھڑکی *کھڑکی)
{
    صحیح pixel_w = 0, pixel_h = 0;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &pixel_w, &pixel_h);
    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_PIXEL_سائز_بدلا, pixel_w, pixel_h);

    SDL_Check_کھڑکی_Display_Scale_بدلا(کھڑکی);
}

خالی SDL_On_کھڑکی_Pixel_سائز_بدلا(SDL_کھڑکی *کھڑکی)
{
    کھڑکی->surface_valid = false;
}

خالی SDL_On_کھڑکی_زندہ_Resize_Update(SDL_کھڑکی *کھڑکی)
{
    اگر (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } ورنہ {
        // Send an expose event so the application can redraw
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

ساکن خالی SDL_Check_کھڑکی_محفوظ_Area_بدلا(SDL_کھڑکی *کھڑکی)
{
    SDL_Rect rect;

    rect.x = کھڑکی->محفوظ_inset_بایاں;
    rect.y = کھڑکی->محفوظ_inset_چوٹی;
    rect.w = کھڑکی->w - (کھڑکی->محفوظ_inset_دایاں + کھڑکی->محفوظ_inset_بایاں);
    rect.h = کھڑکی->h - (کھڑکی->محفوظ_inset_چوٹی + کھڑکی->محفوظ_inset_bottom);
    اگر (SDL_memcmp(&rect, &کھڑکی->محفوظ_rect, حجم(rect)) != 0) {
        SDL_copyp(&کھڑکی->محفوظ_rect, &rect);
        SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_محفوظ_AREA_بدلا, 0, 0);
    }
}

خالی SDL_سیٹ_کھڑکی_محفوظ_Area_Insets(SDL_کھڑکی *کھڑکی, صحیح بایاں, صحیح دایاں, صحیح چوٹی, صحیح bottom)
{
    کھڑکی->محفوظ_inset_بایاں = بایاں;
    کھڑکی->محفوظ_inset_دایاں = دایاں;
    کھڑکی->محفوظ_inset_چوٹی = چوٹی;
    کھڑکی->محفوظ_inset_bottom = bottom;
    SDL_Check_کھڑکی_محفوظ_Area_بدلا(کھڑکی);
}

bool SDL_Get_کھڑکی_محفوظ_Area(SDL_کھڑکی *کھڑکی, SDL_Rect *rect)
{
    اگر (rect) {
        SDL_zerop(rect);
    }

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (rect) {
        اگر (SDL_Rect_خالی_خانے(&کھڑکی->محفوظ_rect)) {
            rect->w = کھڑکی->w;
            rect->h = کھڑکی->h;
        } ورنہ {
            SDL_copyp(rect, &کھڑکی->محفوظ_rect);
        }
    }
    واپس true;
}

خالی SDL_On_کھڑکی_Minimized(SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

خالی SDL_On_کھڑکی_Maximized(SDL_کھڑکی *کھڑکی)
{
}

خالی SDL_On_کھڑکی_Restored(SDL_کھڑکی *کھڑکی)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    اگر (کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) {
        SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

خالی SDL_On_کھڑکی_Enter(SDL_کھڑکی *کھڑکی)
{
    اگر (_this->On_کھڑکی_Enter) {
        _this->On_کھڑکی_Enter(_this, کھڑکی);
    }
    SDL_Update_Relative_Mouse_منوال();
}

خالی SDL_On_کھڑکی_Leave(SDL_کھڑکی *کھڑکی)
{
    SDL_Update_Relative_Mouse_منوال();
}

خالی SDL_On_کھڑکی_Focus_Gained(SDL_کھڑکی *کھڑکی)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    اگر (mouse && mouse->relative_منوال) {
        SDL_سیٹ_Mouse_Focus(کھڑکی);
    }

    SDL_Update_کھڑکی_Grab(کھڑکی);
}

ساکن bool SDL_ShouldMinimizeOnFocusLoss(SDL_کھڑکی *کھڑکی)
{
    ثابت حرف *hint;

    اگر (!(کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) || کھڑکی->is_destroying) {
        واپس false;
    }

#اگر defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    اگر (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        اگر (Cocoa_IsShowingModalDialog(کھڑکی)) {
            واپس false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } ورنہ اگر (Cocoa_Is_کھڑکی_اندر_Fullscreen_Space(کھڑکی)) {
            واپس false;
        }
    }
#اگر_ختم

#اگر_تعریف_شدہ SDL_PLATFORM_ANDROID
    {
        خارجی bool Android_JNI_ShouldMinimizeOnFocusLoss(خالی);
        اگر (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            واپس false;
        }
    }
#اگر_ختم

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    اگر (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        اگر (کھڑکی->fullscreen_exclusive && !SDL_منوال_Switching_Emulated(_this)) {
            واپس true;
        } ورنہ {
            واپس false;
        }
    }
    واپس SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

خالی SDL_On_کھڑکی_Focus_گمشدہ(SDL_کھڑکی *کھڑکی)
{
    SDL_Update_کھڑکی_Grab(کھڑکی);

    اگر (SDL_ShouldMinimizeOnFocusLoss(کھڑکی)) {
        SDL_Minimize_کھڑکی(کھڑکی);
    }
}

SDL_کھڑکی *SDL_GetToplevelForKeyboardFocus(خالی)
{
    SDL_کھڑکی *focus = SDL_GetKeyboardFocus();

    اگر (focus) {
        // Get the toplevel parent window.
        جب (focus->والد) {
            focus = focus->والد;
        }
    }

    واپس focus;
}

bool SDL_جوڑو_کھڑکی_Renderer(SDL_کھڑکی *کھڑکی, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(کھڑکی->renderers, (کھڑکی->عدد_renderers + 1) * حجم(*renderers));
    اگر (!renderers) {
        واپس false;
    }

    کھڑکی->renderers = renderers;
    کھڑکی->renderers[کھڑکی->عدد_renderers++] = renderer;

    SDL_سیٹ_اشارہ_گر_Property(SDL_Get_کھڑکی_Properties(کھڑکی), SDL_PROP_کھڑکی_RENDERER_اشارہ_گر, renderer);
    واپس true;
}

خالی SDL_Remove_کھڑکی_Renderer(SDL_کھڑکی *کھڑکی, SDL_Renderer *renderer)
{
    برائے (صحیح i = 0; i < کھڑکی->عدد_renderers; ++i) {
        اگر (کھڑکی->renderers[i] == renderer) {
            اگر (i < (کھڑکی->عدد_renderers - 1)) {
                SDL_memmove(&کھڑکی->renderers[i], &کھڑکی->renderers[i + 1], (کھڑکی->عدد_renderers - i - 1) * حجم(کھڑکی->renderers[i]));
            }
            --کھڑکی->عدد_renderers;
            توڑو;
        }
    }

    SDL_PropertiesID props = SDL_Get_کھڑکی_Properties(کھڑکی);
    اگر (SDL_Get_اشارہ_گر_Property(props, SDL_PROP_کھڑکی_RENDERER_اشارہ_گر, تہی) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_کھڑکی_RENDERER_اشارہ_گر);
    }
}

خالی SDL_Destroy_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی,);

    کھڑکی->is_destroying = true;

    // Destroy any child windows of this window
    جب (کھڑکی->پہلا_بچہ) {
        SDL_Destroy_کھڑکی(کھڑکی->پہلا_بچہ);
    }

    SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_DESTROYED, 0, 0);

    SDL_Destroy_کھڑکی_Surface(کھڑکی);

    SDL_Renderer *renderer = SDL_GetRenderer(کھڑکی);
    اگر (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_منوال(کھڑکی, SDL_FULLSCREEN_OP_LEAVE, true);
    اگر (!(کھڑکی->flags & SDL_کھڑکی_EXTERNAL)) {
        SDL_Hide_کھڑکی(کھڑکی);
    }

    SDL_DestroyProperties(کھڑکی->متن_داخلہ_props);

    SDL_Destroy_کھڑکی_Texture(_this, کھڑکی);
    SDL_DestroyProperties(کھڑکی->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    اگر (_this->سیٹ_کھڑکی_Modal && (کھڑکی->flags & SDL_کھڑکی_MODAL)) {
        _this->سیٹ_کھڑکی_Modal(_this, کھڑکی, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    برائے (صحیح i = 0; i < _this->عدد_displays; ++i) {
        اگر (_this->displays[i]->fullscreen_کھڑکی == کھڑکی) {
            _this->displays[i]->fullscreen_کھڑکی = تہی;
        }
    }

    // Make sure this window no longer has focus
    اگر (SDL_GetKeyboardFocus() == کھڑکی) {
        SDL_سیٹ_Keyboard_Focus(تہی);
    }
    اگر ((کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    اگر (SDL_GetMouseFocus() == کھڑکی) {
        SDL_سیٹ_Mouse_Focus(تہی);
    }

    // Make no context current if this is the current context window
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        اگر (_this->current_glwin == کھڑکی) {
            SDL_GL_MakeCurrent(کھڑکی, تہی);
        }
    }

    اگر (_this->Destroy_کھڑکی) {
        _this->Destroy_کھڑکی(_this, کھڑکی);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    اگر (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    اگر (_this->grabbed_کھڑکی == کھڑکی) {
        _this->grabbed_کھڑکی = تہی; // ungrabbing input.
    }

    اگر (_this->current_glwin == کھڑکی) {
        _this->current_glwin = تہی;
    }

    SDL_Compare_And_تبادلہ_Atomic_اشارہ_گر(&_this->wakeup_کھڑکی, کھڑکی, تہی);

    // Now invalidate magic
    SDL_سیٹ_Object_Valid(کھڑکی, SDL_OBJECT_TYPE_کھڑکی, false);

    // Free memory associated with the window
    SDL_free(کھڑکی->title);
    SDL_DestroySurface(کھڑکی->icon);

    // Unlink the window from its siblings.
    SDL_Update_کھڑکی_Hierarchy(کھڑکی, تہی);

    // Unlink the window from the global window list
    اگر (کھڑکی->اگلا) {
        کھڑکی->اگلا->پچھلا = کھڑکی->پچھلا;
    }
    اگر (کھڑکی->پچھلا) {
        کھڑکی->پچھلا->اگلا = کھڑکی->اگلا;
    } ورنہ {
        _this->windows = کھڑکی->اگلا;
    }

    SDL_free(کھڑکی->renderers);
    SDL_free(کھڑکی);

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#اگر_ختم
}

bool SDL_ScreenSaverEnabled(خالی)
{
    اگر (!_this) {
        واپس true;
    }
    واپس !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(خالی)
{
    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }
    اگر (!_this->suspend_screensaver) {
        واپس true;
    }
    _this->suspend_screensaver = false;
    اگر (_this->SuspendScreenSaver) {
        واپس _this->SuspendScreenSaver(_this);
    }

    واپس SDL_Unsupported();
}

bool SDL_DisableScreenSaver(خالی)
{
    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }
    اگر (_this->suspend_screensaver) {
        واپس true;
    }
    _this->suspend_screensaver = true;
    اگر (_this->SuspendScreenSaver) {
        واپس _this->SuspendScreenSaver(_this);
    }

    واپس SDL_Unsupported();
}

خالی SDL_QuitVideo(خالی)
{
    صحیح i;

    اگر (!_this) {
        واپس;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#اگر 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#اگر_ختم
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    جب (_this->windows) {
        SDL_Destroy_کھڑکی(_this->windows);
    }

    اگر (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    اگر (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    برائے (i = _this->عدد_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->عدد_displays == 0);
    SDL_free(_this->displays);
    _this->displays = تہی;

    SDL_Cancel_Clipboard_ڈیٹا(0);

    اگر (_this->primary_selection_متن) {
        SDL_free(_this->primary_selection_متن);
        _this->primary_selection_متن = تہی;
    }
    _this->آزاد(_this);
    _this = تہی;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_بھرو_Library(ثابت حرف *راستہ)
{
    bool نتیجہ;

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }
    اگر (_this->gl_config.driver_loaded) {
        اگر (راستہ && SDL_strcmp(راستہ, _this->gl_config.driver_راستہ) != 0) {
            واپس SDL_سیٹ_Error("OpenGL library already loaded");
        }
        نتیجہ = true;
    } ورنہ {
        اگر (!_this->GL_بھرو_Library) {
            واپس SDL_DllNotSupported("OpenGL");
        }
        نتیجہ = _this->GL_بھرو_Library(_this, راستہ);
    }
    اگر (نتیجہ) {
        ++_this->gl_config.driver_loaded;
    } ورنہ {
        اگر (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    واپس نتیجہ;
}

SDL_Function_اشارہ_گر SDL_GL_Get_Proc_پتہ(ثابت حرف *proc)
{
    SDL_Function_اشارہ_گر func;

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    func = تہی;
    اگر (_this->GL_Get_Proc_پتہ) {
        اگر (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_پتہ(_this, proc);
        } ورنہ {
            SDL_سیٹ_Error("No GL driver has been loaded");
        }
    } ورنہ {
        SDL_سیٹ_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    واپس func;
}

SDL_Function_اشارہ_گر SDL_EGL_Get_Proc_پتہ(ثابت حرف *proc)
{
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    SDL_Function_اشارہ_گر func;

    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    func = تہی;

    اگر (_this->egl_ڈیٹا) {
        func = SDL_EGL_Get_Proc_پتہ_اندرونی(_this, proc);
    } ورنہ {
        SDL_سیٹ_Error("No EGL library has been loaded");
    }

    واپس func;
#ورنہ
    SDL_سیٹ_Error("SDL was not built with EGL support");
    واپس تہی;
#اگر_ختم
}

خالی SDL_GL_UnloadLibrary(خالی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس;
    }
    اگر (_this->gl_config.driver_loaded > 0) {
        اگر (--_this->gl_config.driver_loaded > 0) {
            واپس;
        }
        اگر (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
قسمتعریف GLenum (APIENTRY* PFNGLGETERRORPROC) (خالی);
قسمتعریف خالی (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
قسمتعریف ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
قسمتعریف خالی (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#اگر_غیر_تعریف_شدہ SDL_VIDEO_OPENGL
قسمتعریف ثابت GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint اشاریہ);
#اگر_ختم

ساکن SDL_INLINE bool is_At_کم_سے_کم_GL3(ثابت حرف *verstr)
{
    واپس verstr && (SDL_atoi(verstr) >= 3);
}
#اگر_ختم // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ثابت حرف *extension)
{
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ثابت حرف *extensions;
    ثابت حرف *آغاز;
    ثابت حرف *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    اگر (where || *extension == '\0') {
        واپس false;
    }
    // See if there's a hint or environment variable override
    آغاز = SDL_GetHint(extension);
    اگر (آغاز && *آغاز == '0') {
        واپس false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتہ("glGetString");
    اگر (!glGetStringFunc) {
        واپس false;
    }

    اگر (is_At_کم_سے_کم_GL3((ثابت حرف *)glGetStringFunc(GL_نسخہ))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint عدد_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_پتہ("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتہ("glGetIntegerv");
        اگر ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            واپس false;
        }

#اگر_غیر_تعریف_شدہ GL_عدد_EXTENSIONS
#تعریف_کرو GL_عدد_EXTENSIONS 0x821D
#اگر_ختم
        glGetIntegervFunc(GL_عدد_EXTENSIONS, &عدد_exts);
        برائے (i = 0; i < عدد_exts; i++) {
            ثابت حرف *thisext = (ثابت حرف *)glGetStringiFunc(GL_EXTENSIONS, i);
            اگر (SDL_strcmp(thisext, extension) == 0) {
                واپس true;
            }
        }

        واپس false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ثابت حرف *)glGetStringFunc(GL_EXTENSIONS);
    اگر (!extensions) {
        واپس false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    آغاز = extensions;

    برائے (;;) {
        where = SDL_strstr(آغاز, extension);
        اگر (!where) {
            توڑو;
        }

        terminator = where + SDL_strlen(extension);
        اگر (where == extensions || *(where - 1) == ' ') {
            اگر (*terminator == ' ' || *terminator == '\0') {
                واپس true;
            }
        }

        آغاز = terminator;
    }
    واپس false;
#ورنہ
    واپس false;
#اگر_ختم
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
خالی SDL_GL_DeduceMaxSupportedESProfile(صحیح *major, صحیح *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    اگر (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } ورنہ اگر (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } ورنہ اگر (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } ورنہ {
        *major = 2;
        *minor = 0;
    }
#اگر_ختم
}

خالی SDL_EGL_سیٹ_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   خالی *userdata)
{
    اگر (!_this) {
        واپس;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

خالی SDL_GL_Reset_اوصاف(خالی)
{
    اگر (!_this) {
        واپس;
    }

    _this->egl_platformattrib_callback = تہی;
    _this->egl_surfaceattrib_callback = تہی;
    _this->egl_contextattrib_callback = تہی;
    _this->egl_attrib_callback_userdata = تہی;

    _this->gl_config.red_سائز = 8;
    _this->gl_config.green_سائز = 8;
    _this->gl_config.blue_سائز = 8;
    _this->gl_config.alpha_سائز = 8;
    _this->gl_config.بفر_سائز = 0;
    _this->gl_config.گہرائی_سائز = 16;
    _this->gl_config.stencil_سائز = 0;
    _this->gl_config.double_بفر = 1;
    _this->gl_config.accum_red_سائز = 0;
    _this->gl_config.accum_green_سائز = 0;
    _this->gl_config.accum_blue_سائز = 0;
    _this->gl_config.accum_alpha_سائز = 0;
    _this->gl_config.stereo = 0;
    _this->gl_config.multisamplebuffers = 0;
    _this->gl_config.multisamplesamples = 0;
    _this->gl_config.floatbuffers = 0;
    _this->gl_config.retained_backing = 1;
    _this->gl_config.accelerated = -1; // accelerated or not, both are fine

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    _this->gl_config.major_نسخہ = 2;
    _this->gl_config.minor_نسخہ = 1;
    _this->gl_config.profile_نقاب = 0;
#وگرنہ_اگر defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_نسخہ = 2;
    _this->gl_config.minor_نسخہ = 0;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
#وگرنہ_اگر defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_نسخہ = 1;
    _this->gl_config.minor_نسخہ = 1;
    _this->gl_config.profile_نقاب = SDL_GL_CONTEXT_PROFILE_ES;
#اگر_ختم

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    اگر (_this->GL_سیٹ_Default_Profile_Config) {
        _this->GL_سیٹ_Default_Profile_Config(_this);
    }
}

bool SDL_GL_سیٹ_Attribute(SDL_GLAttr attr, صحیح قدر)
{
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool نتیجہ;

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }
    نتیجہ = true;
    انتخاب (attr) {
    حالت SDL_GL_RED_سائز:
        _this->gl_config.red_سائز = قدر;
        توڑو;
    حالت SDL_GL_GREEN_سائز:
        _this->gl_config.green_سائز = قدر;
        توڑو;
    حالت SDL_GL_BLUE_سائز:
        _this->gl_config.blue_سائز = قدر;
        توڑو;
    حالت SDL_GL_ALPHA_سائز:
        _this->gl_config.alpha_سائز = قدر;
        توڑو;
    حالت SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_بفر = قدر;
        توڑو;
    حالت SDL_GL_بفر_سائز:
        _this->gl_config.بفر_سائز = قدر;
        توڑو;
    حالت SDL_GL_گہرائی_سائز:
        _this->gl_config.گہرائی_سائز = قدر;
        توڑو;
    حالت SDL_GL_STENCIL_سائز:
        _this->gl_config.stencil_سائز = قدر;
        توڑو;
    حالت SDL_GL_ACCUM_RED_سائز:
        _this->gl_config.accum_red_سائز = قدر;
        توڑو;
    حالت SDL_GL_ACCUM_GREEN_سائز:
        _this->gl_config.accum_green_سائز = قدر;
        توڑو;
    حالت SDL_GL_ACCUM_BLUE_سائز:
        _this->gl_config.accum_blue_سائز = قدر;
        توڑو;
    حالت SDL_GL_ACCUM_ALPHA_سائز:
        _this->gl_config.accum_alpha_سائز = قدر;
        توڑو;
    حالت SDL_GL_STEREO:
        _this->gl_config.stereo = قدر;
        توڑو;
    حالت SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = قدر;
        توڑو;
    حالت SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = قدر;
        توڑو;
    حالت SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = قدر;
        توڑو;
    حالت SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = قدر;
        توڑو;
    حالت SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = قدر;
        توڑو;
    حالت SDL_GL_CONTEXT_MAJOR_نسخہ:
        _this->gl_config.major_نسخہ = قدر;
        توڑو;
    حالت SDL_GL_CONTEXT_MINOR_نسخہ:
        _this->gl_config.minor_نسخہ = قدر;
        توڑو;
    حالت SDL_GL_CONTEXT_FLAGS:
        اگر (قدر & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            نتیجہ = SDL_سیٹ_Error("Unknown OpenGL context flag %d", قدر);
            توڑو;
        }
        _this->gl_config.flags = قدر;
        توڑو;
    حالت SDL_GL_CONTEXT_PROFILE_نقاب:
        اگر (قدر != 0 &&
            قدر != SDL_GL_CONTEXT_PROFILE_CORE &&
            قدر != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            قدر != SDL_GL_CONTEXT_PROFILE_ES) {
            نتیجہ = SDL_سیٹ_Error("Unknown OpenGL context profile %d", قدر);
            توڑو;
        }
        _this->gl_config.profile_نقاب = قدر;
        توڑو;
    حالت SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = قدر;
        توڑو;
    حالت SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = قدر;
        توڑو;
    حالت SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = قدر;
        توڑو;
    حالت SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = قدر;
        توڑو;
    حالت SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = قدر;
        توڑو;
    حالت SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = قدر;
        توڑو;
    طےشدہ:
        نتیجہ = SDL_سیٹ_Error("Unknown OpenGL attribute");
        توڑو;
    }
    واپس نتیجہ;
#ورنہ
    واپس SDL_Unsupported();
#اگر_ختم // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, صحیح *قدر)
{
#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_عقب_بایاں;
    GLenum attachmentattrib = 0;
#اگر_ختم

    CHECK_PARAM(!قدر) {
        واپس SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *قدر = 0;

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    انتخاب (attr) {
    حالت SDL_GL_RED_سائز:
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_سائز;
#اگر_ختم
        attrib = GL_RED_بٹ;
        توڑو;
    حالت SDL_GL_BLUE_سائز:
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_سائز;
#اگر_ختم
        attrib = GL_BLUE_بٹ;
        توڑو;
    حالت SDL_GL_GREEN_سائز:
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_سائز;
#اگر_ختم
        attrib = GL_GREEN_بٹ;
        توڑو;
    حالت SDL_GL_ALPHA_سائز:
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_سائز;
#اگر_ختم
        attrib = GL_ALPHA_بٹ;
        توڑو;
    حالت SDL_GL_DOUBLEBUFFER:
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        توڑو;
#ورنہ
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *قدر = _this->gl_config.double_بفر;
        واپس true;
#اگر_ختم
    حالت SDL_GL_گہرائی_سائز:
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        attachment = GL_گہرائی;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_گہرائی_سائز;
#اگر_ختم
        attrib = GL_گہرائی_بٹ;
        توڑو;
    حالت SDL_GL_STENCIL_سائز:
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_سائز;
#اگر_ختم
        attrib = GL_STENCIL_بٹ;
        توڑو;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    حالت SDL_GL_ACCUM_RED_سائز:
        attrib = GL_ACCUM_RED_بٹ;
        توڑو;
    حالت SDL_GL_ACCUM_GREEN_سائز:
        attrib = GL_ACCUM_GREEN_بٹ;
        توڑو;
    حالت SDL_GL_ACCUM_BLUE_سائز:
        attrib = GL_ACCUM_BLUE_بٹ;
        توڑو;
    حالت SDL_GL_ACCUM_ALPHA_سائز:
        attrib = GL_ACCUM_ALPHA_بٹ;
        توڑو;
    حالت SDL_GL_STEREO:
        attrib = GL_STEREO;
        توڑو;
#ورنہ
    حالت SDL_GL_ACCUM_RED_سائز:
    حالت SDL_GL_ACCUM_GREEN_سائز:
    حالت SDL_GL_ACCUM_BLUE_سائز:
    حالت SDL_GL_ACCUM_ALPHA_سائز:
    حالت SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *قدر = 0;
        واپس true;
#اگر_ختم
    حالت SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        توڑو;
    حالت SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        توڑو;
    حالت SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        توڑو;
    حالت SDL_GL_بفر_سائز:
    {
        صحیح rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        اگر (!SDL_GL_GetAttribute(SDL_GL_RED_سائز, &rsize)) {
            واپس false;
        }
        اگر (!SDL_GL_GetAttribute(SDL_GL_GREEN_سائز, &gsize)) {
            واپس false;
        }
        اگر (!SDL_GL_GetAttribute(SDL_GL_BLUE_سائز, &bsize)) {
            واپس false;
        }
        اگر (!SDL_GL_GetAttribute(SDL_GL_ALPHA_سائز, &asize)) {
            واپس false;
        }

        *قدر = rsize + gsize + bsize + asize;
        واپس true;
    }
    حالت SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *قدر = (_this->gl_config.accelerated != 0);
        واپس true;
    }
    حالت SDL_GL_RETAINED_BACKING:
    {
        *قدر = _this->gl_config.retained_backing;
        واپس true;
    }
    حالت SDL_GL_CONTEXT_MAJOR_نسخہ:
    {
        *قدر = _this->gl_config.major_نسخہ;
        واپس true;
    }
    حالت SDL_GL_CONTEXT_MINOR_نسخہ:
    {
        *قدر = _this->gl_config.minor_نسخہ;
        واپس true;
    }
    حالت SDL_GL_CONTEXT_FLAGS:
    {
        *قدر = _this->gl_config.flags;
        واپس true;
    }
    حالت SDL_GL_CONTEXT_PROFILE_نقاب:
    {
        *قدر = _this->gl_config.profile_نقاب;
        واپس true;
    }
    حالت SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *قدر = _this->gl_config.share_with_current_context;
        واپس true;
    }
    حالت SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *قدر = _this->gl_config.framebuffer_srgb_capable;
        واپس true;
    }
    حالت SDL_GL_CONTEXT_NO_ERROR:
    {
        *قدر = _this->gl_config.no_error;
        واپس true;
    }
    حالت SDL_GL_EGL_PLATFORM:
    {
        *قدر = _this->gl_config.egl_platform;
        واپس true;
    }
    حالت SDL_GL_FLOATBUFFERS:
    {
        اگر (_this->gl_config.HAS_GL_ARB_color_بفر_float) {
            attrib = GL_RGBA_FLOAT_منوال_ARB;
            توڑو;
        } ورنہ {
            واپس 0;
        }
    }
    طےشدہ:
        واپس SDL_سیٹ_Error("Unknown OpenGL attribute");
    }

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتہ("glGetString");
    اگر (!glGetStringFunc) {
        واپس false;
    }

    اگر (attachmentattrib && is_At_کم_سے_کم_GL3((ثابت حرف *)glGetStringFunc(GL_نسخہ))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_پتہ("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_پتہ("glBindFramebuffer");
        اگر (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_پتہ("glGetFramebufferAttachmentParameteriv");
        اگر (glGetFramebufferAttachmentParameterivFunc) {
            اگر (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            اگر (attachment == GL_گہرائی || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            اگر (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)قدر);
            } ورنہ {
                *قدر = 0;
            }
            اگر (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } ورنہ {
            واپس false;
        }
    } ورنہ
#اگر_ختم
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_پتہ("glGetIntegerv");
        اگر (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)قدر);
        } ورنہ {
            واپس false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_پتہ("glGetError");
    اگر (!glGetErrorFunc) {
        واپس false;
    }

    error = glGetErrorFunc();
    اگر (error != GL_NO_ERROR) {
        اگر (error == GL_INVALID_ENUM) {
            واپس SDL_سیٹ_Error("OpenGL error: GL_INVALID_ENUM");
        } ورنہ اگر (error == GL_INVALID_قدر) {
            واپس SDL_سیٹ_Error("OpenGL error: GL_INVALID_VALUE");
        }
        واپس SDL_سیٹ_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    اگر (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *قدر = (*قدر == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    واپس true;
#ورنہ
    واپس SDL_Unsupported();
#اگر_ختم // SDL_VIDEO_OPENGL
}

#تعریف_کرو NOT_AN_OPENGL_کھڑکی "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_کھڑکی *کھڑکی)
{
    SDL_GLContext ctx = تہی;
    CHECK_کھڑکی_MAGIC(کھڑکی, تہی);

    اگر (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
        SDL_سیٹ_Error(NOT_AN_OPENGL_کھڑکی);
        واپس تہی;
    }

#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    صحیح srgb_requested = -1;
    ثابت حرف *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    اگر (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#اگر_ختم

    ctx = _this->GL_CreateContext(_this, کھڑکی);

    // Creating a context is assumed to make it current in the SDL driver.
    اگر (ctx) {
        _this->current_glwin = کھڑکی;
        _this->current_glctx = ctx;
        SDL_سیٹ_TLS(&_this->current_glwin_tls, کھڑکی, تہی);
        SDL_سیٹ_TLS(&_this->current_glctx_tls, ctx, تہی);
    }

#اگر defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    اگر (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_پتہ(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_پتہ("glGetString");
        اگر (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            اگر (_this->gl_config.profile_نقاب & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } ورنہ {
                supported = is_At_کم_سے_کم_GL3((ثابت حرف *)glGetStringFunc(GL_نسخہ)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            اگر (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#اگر_ختم

    واپس ctx;
}

bool SDL_GL_MakeCurrent(SDL_کھڑکی *کھڑکی, SDL_GLContext context)
{
    bool نتیجہ;

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }

    اگر (کھڑکی == SDL_GL_Get_Current_کھڑکی() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        واپس true;
    }

    اگر (!context) {
        کھڑکی = تہی;
    } ورنہ اگر (کھڑکی) {
        CHECK_کھڑکی_MAGIC(کھڑکی, false);

        اگر (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
            واپس SDL_سیٹ_Error(NOT_AN_OPENGL_کھڑکی);
        }
    } ورنہ اگر (!_this->gl_allow_no_surface) {
        واپس SDL_سیٹ_Error("Use of OpenGL without a window is not supported on this platform");
    }

    نتیجہ = _this->GL_MakeCurrent(_this, کھڑکی, context);
    اگر (نتیجہ) {
        _this->current_glwin = کھڑکی;
        _this->current_glctx = context;
        SDL_سیٹ_TLS(&_this->current_glwin_tls, کھڑکی, تہی);
        SDL_سیٹ_TLS(&_this->current_glctx_tls, context, تہی);
    }
    واپس نتیجہ;
}

SDL_کھڑکی *SDL_GL_Get_Current_کھڑکی(خالی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    واپس (SDL_کھڑکی *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(خالی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    واپس (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(خالی)
{
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس EGL_NO_DISPLAY;
    }
    اگر (!_this->egl_ڈیٹا) {
        SDL_سیٹ_Error("There is no current EGL display");
        واپس EGL_NO_DISPLAY;
    }
    واپس _this->egl_ڈیٹا->egl_display;
#ورنہ
    SDL_سیٹ_Error("SDL was not built with EGL support");
    واپس تہی;
#اگر_ختم
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(خالی)
{
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    اگر (!_this->egl_ڈیٹا) {
        SDL_سیٹ_Error("There is no current EGL display");
        واپس تہی;
    }
    واپس _this->egl_ڈیٹا->egl_config;
#ورنہ
    SDL_سیٹ_Error("SDL was not built with EGL support");
    واپس تہی;
#اگر_ختم
}

SDL_EGLConfig SDL_EGL_Get_کھڑکی_Surface(SDL_کھڑکی *کھڑکی)
{
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    اگر (!_this->egl_ڈیٹا) {
        SDL_سیٹ_Error("There is no current EGL display");
        واپس تہی;
    }
    اگر (_this->GL_GetEGLSurface) {
        واپس _this->GL_GetEGLSurface(_this, کھڑکی);
    }
    واپس تہی;
#ورنہ
    SDL_سیٹ_Error("SDL was not built with EGL support");
    واپس تہی;
#اگر_ختم
}

bool SDL_GL_سیٹ_تبادلہ_Interval(صحیح interval)
{
    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    } ورنہ اگر (SDL_GL_GetCurrentContext() == تہی) {
        واپس SDL_سیٹ_Error("No OpenGL context has been made current");
    } ورنہ اگر (_this->GL_سیٹ_تبادلہ_Interval) {
        واپس _this->GL_سیٹ_تبادلہ_Interval(_this, interval);
    } ورنہ {
        واپس SDL_سیٹ_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_Get_تبادلہ_Interval(صحیح *interval)
{
    CHECK_PARAM(!interval) {
       واپس SDL_InvalidParamError("interval");
    }

    *interval = 0;

    اگر (!_this) {
        واپس SDL_سیٹ_Error("no video driver");
    } ورنہ اگر (SDL_GL_GetCurrentContext() == تہی) {
        واپس SDL_سیٹ_Error("no current context");
    } ورنہ اگر (_this->GL_Get_تبادلہ_Interval) {
        واپس _this->GL_Get_تبادلہ_Interval(_this, interval);
    } ورنہ {
        واپس SDL_سیٹ_Error("not implemented");
    }
}

bool SDL_GL_تبادلہ_کھڑکی(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!(کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
        واپس SDL_سیٹ_Error(NOT_AN_OPENGL_کھڑکی);
    }

    اگر (SDL_GL_Get_Current_کھڑکی() != کھڑکی) {
        واپس SDL_سیٹ_Error("The specified window has not been made current");
    }

    واپس _this->GL_تبادلہ_کھڑکی(_this, کھڑکی);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        واپس SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        واپس SDL_InvalidParamError("context");
    }

    اگر (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(تہی, تہی);
    }

    واپس _this->GL_DestroyContext(_this, context);
}

#اگر 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
ساکن خالی Create_نقاب_From_Color_کلید_Or_Alpha(SDL_Surface *icon, Uint8 *نقاب, صحیح flags)
{
    صحیح x, y;
    Uint32 colorkey;
#تعریف_کرو سیٹ_MASKBIT(icon, x, y, نقاب) \
    نقاب[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    انتخاب (SDL_BYTESPERPIXEL(icon->format)) {
    حالت 1:
        {
            Uint8 *pixels;
            برائے (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                برائے (x = 0; x < icon->w; ++x) {
                    اگر (*pixels++ == colorkey) {
                        سیٹ_MASKBIT(icon, x, y, نقاب);
                    }
                }
            }
        }
        توڑو;

    حالت 2:
        {
            Uint16 *pixels;
            برائے (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                برائے (x = 0; x < icon->w; ++x) {
                    اگر ((flags & 1) && *pixels == colorkey) {
                        سیٹ_MASKBIT(icon, x, y, نقاب);
                    } ورنہ اگر ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سیٹ_MASKBIT(icon, x, y, نقاب);
                    }
                    pixels++;
                }
            }
        }
        توڑو;

    حالت 4:
        {
            Uint32 *pixels;
            برائے (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                برائے (x = 0; x < icon->w; ++x) {
                    اگر ((flags & 1) && *pixels == colorkey) {
                        سیٹ_MASKBIT(icon, x, y, نقاب);
                    } ورنہ اگر ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        سیٹ_MASKBIT(icon, x, y, نقاب);
                    }
                    pixels++;
                }
            }
        }
        توڑو;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
خالی SDL_WM_سیٹ_Icon(SDL_Surface *icon, Uint8 *نقاب)
{
    اگر (icon && _this->سیٹ_Icon) {
        // Generate a mask if necessary, and create the icon!
        اگر (نقاب == تہی) {
            صحیح نقاب_len = icon->h * (icon->w + 7) / 8;
            صحیح flags = 0;
            نقاب = (Uint8 *) SDL_malloc(نقاب_len);
            اگر (نقاب == تہی) {
                واپس;
            }
            SDL_memset(نقاب, ~0, نقاب_len);
            اگر (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            اگر (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            اگر (flags) {
                Create_نقاب_From_Color_کلید_Or_Alpha(icon, نقاب, flags);
            }
            _this->سیٹ_Icon(_this, icon, نقاب);
            SDL_free(نقاب);
        } ورنہ {
            _this->سیٹ_Icon(_this, icon, نقاب);
        }
    }
}
#اگر_ختم

SDL_متن_داخلہ_Type SDL_Get_متن_داخلہ_Type(SDL_PropertiesID props)
{
    واپس (SDL_متن_داخلہ_Type)SDL_Get_نمبر_Property(props, SDL_PROP_TEXTINPUT_TYPE_نمبر, SDL_TEXTINPUT_TYPE_متن);
}

SDL_Capitalization SDL_Get_متن_داخلہ_Capitalization(SDL_PropertiesID props)
{
    اگر (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_نمبر)) {
        واپس (SDL_Capitalization)SDL_Get_نمبر_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_نمبر, SDL_CAPITALIZE_NONE);
    }

    انتخاب (SDL_Get_متن_داخلہ_Type(props)) {
    حالت SDL_TEXTINPUT_TYPE_متن:
        واپس SDL_CAPITALIZE_SENTENCES;
    حالت SDL_TEXTINPUT_TYPE_متن_NAME:
        واپس SDL_CAPITALIZE_الفاظ;
    طےشدہ:
        واپس SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_متن_داخلہ_Autocorrect(SDL_PropertiesID props)
{
    واپس SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_متن_داخلہ_Multiline(SDL_PropertiesID props)
{
    اگر (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        واپس SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    اگر (SDL_GetHintBoolean(SDL_HINT_RETURN_کلید_HIDES_IME, false)) {
        واپس false;
    } ورنہ {
        واپس true;
    }
}

ساکن bool AutoShowingScreenKeyboard(خالی)
{
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    اگر (!hint) {
        // This hint is currently only used by the X11 video driver
        اگر (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    اگر (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        واپس true;
    } ورنہ {
        واپس false;
    }
}

bool SDL_آغاز_متن_داخلہ(SDL_کھڑکی *کھڑکی)
{
    واپس SDL_آغاز_متن_داخلہ_With_Properties(کھڑکی, 0);
}

bool SDL_آغاز_متن_داخلہ_With_Properties(SDL_کھڑکی *کھڑکی, SDL_PropertiesID props)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (کھڑکی->متن_داخلہ_props) {
        SDL_DestroyProperties(کھڑکی->متن_داخلہ_props);
        کھڑکی->متن_داخلہ_props = 0;
    }

    اگر (props) {
        کھڑکی->متن_داخلہ_props = SDL_CreateProperties();
        اگر (!کھڑکی->متن_داخلہ_props) {
            واپس false;
        }
        اگر (!SDL_CopyProperties(props, کھڑکی->متن_داخلہ_props)) {
            واپس false;
        }
    }

    اگر (_this->سیٹ_متن_داخلہ_Properties) {
        _this->سیٹ_متن_داخلہ_Properties(_this, کھڑکی, props);
    }

    اگر (!کھڑکی->متن_داخلہ_فعال) {
        // Start the text input system
        اگر (_this->آغاز_متن_داخلہ) {
            اگر (!_this->آغاز_متن_داخلہ(_this, کھڑکی, props)) {
                واپس false;
            }
        }
        کھڑکی->متن_داخلہ_فعال = true;
    }

    // Show the on-screen keyboard, if desired
    اگر (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(کھڑکی)) {
        اگر (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, کھڑکی, props);
        }
    }
    واپس true;
}

bool SDL_متن_داخلہ_فعال(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    واپس کھڑکی->متن_داخلہ_فعال;
}

bool SDL_Stop_متن_داخلہ(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (کھڑکی->متن_داخلہ_فعال) {
        // Stop the text input system
        اگر (_this->Stop_متن_داخلہ) {
            _this->Stop_متن_داخلہ(_this, کھڑکی);
        }
        کھڑکی->متن_داخلہ_فعال = false;
    }

    // Hide the on-screen keyboard, if desired
    اگر (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(کھڑکی)) {
        اگر (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, کھڑکی);
        }
    }
    واپس true;
}

bool SDL_سیٹ_متن_داخلہ_Area(SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rect, صحیح cursor)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (rect) {
        SDL_copyp(&کھڑکی->متن_داخلہ_rect, rect);
        کھڑکی->متن_داخلہ_cursor = cursor;
    } ورنہ {
        SDL_zero(کھڑکی->متن_داخلہ_rect);
        کھڑکی->متن_داخلہ_cursor = 0;
    }

    اگر (_this && _this->Update_متن_داخلہ_Area) {
        اگر (!_this->Update_متن_داخلہ_Area(_this, کھڑکی)) {
            واپس false;
        }
    }
    واپس true;
}

bool SDL_Get_متن_داخلہ_Area(SDL_کھڑکی *کھڑکی, SDL_Rect *rect, صحیح *cursor)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (rect) {
        SDL_copyp(rect, &کھڑکی->متن_داخلہ_rect);
    }
    اگر (cursor) {
        *cursor = کھڑکی->متن_داخلہ_cursor;
    }
    واپس true;
}

bool SDL_ClearComposition(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (_this->ClearComposition) {
        واپس _this->ClearComposition(_this, کھڑکی);
    }
    واپس true;
}

bool SDL_HasScreenKeyboardSupport(خالی)
{
    اگر (_this && _this->HasScreenKeyboardSupport) {
        واپس _this->HasScreenKeyboardSupport(_this);
    }
    واپس false;
}

bool SDL_ScreenKeyboardShown(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    واپس _this->screen_keyboard_shown;
}

خالی SDL_SendScreenKeyboardShown(خالی)
{
    اگر (!_this || _this->screen_keyboard_shown) {
        واپس;
    }

    _this->screen_keyboard_shown = true;

    اگر (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_ڈالو_Event(&event);
    }
}

خالی SDL_SendScreenKeyboardHidden(خالی)
{
    اگر (!_this || !_this->screen_keyboard_shown) {
        واپس;
    }

    _this->screen_keyboard_shown = false;

    اگر (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_ڈالو_Event(&event);
    }
}

صحیح SDL_Get_پیغام_Box_گنتی(خالی)
{
    واپس SDL_GetAtomicInt(&SDL_messagebox_گنتی);
}

bool SDL_Show_پیغام_Box(ثابت SDL_پیغام_Box_ڈیٹا *messageboxdata, صحیح *buttonID)
{
    صحیح dummybutton;
    bool نتیجہ = false;
    bool show_cursor_پچھلا;
    SDL_کھڑکی *current_کھڑکی;
    SDL_پیغام_Box_ڈیٹا mbdata;

    CHECK_PARAM(!messageboxdata) {
        واپس SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        واپس SDL_سیٹ_Error("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    حرف *titlecpy = تہی;
    حرف *msgcpy = تہی;
    اگر (messageboxdata->title) {
        ثابت size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(حرف, slen, &titleisstack);
        اگر (!titlecpy) {
            واپس false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    اگر (messageboxdata->پیغام) {
        ثابت size_t slen = SDL_strlen(messageboxdata->پیغام) + 1;
        msgcpy = SDL_small_alloc(حرف, slen, &msgisstack);
        اگر (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            واپس false;
        }
        SDL_memcpy(msgcpy, messageboxdata->پیغام, slen);
    }

    (خالی)SDL_AtomicIncRef(&SDL_messagebox_گنتی);

    current_کھڑکی = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_سیٹ_Relative_Mouse_منوال(false);
    show_cursor_پچھلا = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    اگر (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, حجم(*messageboxdata));
    mbdata.title = titlecpy;
    اگر (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.پیغام = msgcpy;
    اگر (!mbdata.پیغام) {
        mbdata.پیغام = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    اگر (_this && _this->Show_پیغام_Box) {
        نتیجہ = _this->Show_پیغام_Box(_this, messageboxdata, buttonID);
    } ورنہ {
        // It's completely fine to call this function before video is initialized
        ثابت حرف *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        اگر (driver_name && *driver_name != 0) {
            ثابت حرف *driver_attempt = driver_name;
            جب (driver_attempt && (*driver_attempt != 0) && !نتیجہ) {
                ثابت حرف *driver_attempt_انتہا = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_انتہا) ? (driver_attempt_انتہا - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                برائے (صحیح i = 0; bootstrap[i]; ++i) {
                    اگر (bootstrap[i]->Show_پیغام_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        اگر (bootstrap[i]->Show_پیغام_Box(messageboxdata, buttonID)) {
                            نتیجہ = true;
                        }
                        توڑو;
                    }
                }

                driver_attempt = (driver_attempt_انتہا) ? (driver_attempt_انتہا + 1) : تہی;
            }
        } ورنہ {
            برائے (صحیح i = 0; bootstrap[i]; ++i) {
                اگر (bootstrap[i]->Show_پیغام_Box && bootstrap[i]->Show_پیغام_Box(messageboxdata, buttonID)) {
                    نتیجہ = true;
                    توڑو;
                }
            }
        }
    }

    اگر (!نتیجہ) {
        ثابت حرف *error = SDL_GetError();

        اگر (!*error) {
            SDL_سیٹ_Error("No message system available");
        }
    } ورنہ {
        SDL_ClearError();
    }

    (خالی)SDL_AtomicDecRef(&SDL_messagebox_گنتی);

    اگر (current_کھڑکی) {
        SDL_Raise_کھڑکی(current_کھڑکی);
    }

    اگر (!show_cursor_پچھلا) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_منوال();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    واپس نتیجہ;
}

bool SDL_Show_Simple_پیغام_Box(SDL_پیغام_Box_Flags flags, ثابت حرف *title, ثابت حرف *پیغام, SDL_کھڑکی *کھڑکی)
{
#اگر defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_دایاں;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_دایاں = gsp_Has_Gpu_دایاں();
    اگر (!has_Gpu_دایاں)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_متن_لفظ_WRAP, CFG_LANGUAGE_EN);
    error_متن(&errCnf, پیغام);
    errorDisp(&errCnf);

    اگر (!has_Gpu_دایاں)
        gfxExit();

    واپس true;
#ورنہ
    SDL_پیغام_Box_ڈیٹا ڈیٹا;
    SDL_پیغام_Box_Button_ڈیٹا button;

    SDL_zero(ڈیٹا);
    ڈیٹا.flags = flags;
    ڈیٹا.title = title;
    ڈیٹا.پیغام = پیغام;
    ڈیٹا.numbuttons = 1;
    ڈیٹا.buttons = &button;
    ڈیٹا.کھڑکی = کھڑکی;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.متن = "OK";

    واپس SDL_Show_پیغام_Box(&ڈیٹا, تہی);
#اگر_ختم
}

bool SDL_ShouldAllowTopmost(خالی)
{
    واپس SDL_GetHintBoolean(SDL_HINT_کھڑکی_ALLOW_TOPMOST, true);
}

bool SDL_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);
    CHECK_کھڑکی_NOT_POPUP(کھڑکی, false);

    اگر (_this->Show_کھڑکی_System_Menu) {
        _this->Show_کھڑکی_System_Menu(کھڑکی, x, y);
        واپس true;
    }

    واپس SDL_Unsupported();
}

bool SDL_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, SDL_کامیابی_Test callback, خالی *callback_ڈیٹا)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!_this->سیٹ_کھڑکی_کامیابی_Test) {
        واپس SDL_Unsupported();
    }

    کھڑکی->کامیابی_test = callback;
    کھڑکی->کامیابی_test_ڈیٹا = callback_ڈیٹا;

    واپس _this->سیٹ_کھڑکی_کامیابی_Test(کھڑکی, callback != تہی);
}

bool SDL_سیٹ_کھڑکی_Shape(SDL_کھڑکی *کھڑکی, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!(کھڑکی->flags & SDL_کھڑکی_TRANSPARENT)) {
        واپس SDL_سیٹ_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_کھڑکی_Properties(کھڑکی);
    اگر (!props) {
        واپس false;
    }

    اگر (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        اگر (!surface) {
            واپس false;
        }
    } ورنہ {
        surface = تہی;
    }

    اگر (!SDL_سیٹ_Surface_Property(props, SDL_PROP_کھڑکی_SHAPE_اشارہ_گر, surface)) {
        واپس false;
    }

    اگر (_this->Update_کھڑکی_Shape) {
        اگر (!_this->Update_کھڑکی_Shape(_this, کھڑکی, surface)) {
            واپس false;
        }
    }
    واپس true;
}

/*
 * Functions used by iOS application delegates
 */
خالی SDL_OnApplicationWillTerminate(خالی)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

خالی SDL_On_Application_Did_Receive_حافظہ_Warning(خالی)
{
    SDL_SendAppEvent(SDL_EVENT_کم_حافظہ);
}

خالی SDL_OnApplicationWillEnterBackground(خالی)
{
    اگر (_this) {
        SDL_کھڑکی *کھڑکی;
        برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_MINIMIZED, 0, 0);
        }
        SDL_سیٹ_Keyboard_Focus(تہی);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

خالی SDL_OnApplicationDidEnterBackground(خالی)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

خالی SDL_OnApplicationWillEnterForeground(خالی)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

خالی SDL_OnApplicationDidEnterForeground(خالی)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    اگر (_this) {
        SDL_کھڑکی *کھڑکی;
        برائے (کھڑکی = _this->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            SDL_سیٹ_Keyboard_Focus(کھڑکی);
            SDL_Send_کھڑکی_Event(کھڑکی, SDL_EVENT_کھڑکی_RESTORED, 0, 0);
        }
    }
}

#تعریف_کرو NOT_A_VULKAN_کھڑکی "The specified window isn't a Vulkan window"

bool SDL_Vulkan_بھرو_Library(ثابت حرف *راستہ)
{
    bool نتیجہ;

    اگر (!_this) {
        واپس SDL_UninitializedVideo();
    }
    اگر (_this->vulkan_config.loader_loaded) {
        اگر (راستہ && SDL_strcmp(راستہ, _this->vulkan_config.loader_راستہ) != 0) {
            واپس SDL_سیٹ_Error("Vulkan loader library already loaded");
        }
        نتیجہ = true;
    } ورنہ {
        اگر (!_this->Vulkan_بھرو_Library) {
            واپس SDL_DllNotSupported("Vulkan");
        }
        نتیجہ = _this->Vulkan_بھرو_Library(_this, راستہ);
    }
    اگر (نتیجہ) {
        _this->vulkan_config.loader_loaded++;
    }
    واپس نتیجہ;
}

SDL_Function_اشارہ_گر SDL_Vulkan_GetVkGetInstanceProcAddr(خالی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس تہی;
    }
    اگر (!_this->vulkan_config.loader_loaded) {
        SDL_سیٹ_Error("No Vulkan loader has been loaded");
        واپس تہی;
    }
    واپس (SDL_Function_اشارہ_گر)_this->vulkan_config.vkGetInstanceProcAddr;
}

خالی SDL_Vulkan_UnloadLibrary(خالی)
{
    اگر (!_this) {
        SDL_UninitializedVideo();
        واپس;
    }
    اگر (_this->vulkan_config.loader_loaded > 0) {
        اگر (--_this->vulkan_config.loader_loaded > 0) {
            واپس;
        }
        اگر (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

حرف ثابت * ثابت *SDL_Vulkan_GetInstanceExtensions(Uint32 *گنتی)
{
    Uint32 tmpcount = 0;
    اگر (!گنتی) {
        گنتی = &tmpcount;
    }

    اگر (!_this->Vulkan_GetInstanceExtensions) {
        *گنتی = 0;
        SDL_Unsupported();
        واپس تہی;
    }

    واپس _this->Vulkan_GetInstanceExtensions(_this, گنتی);
}

bool SDL_Vulkan_CreateSurface(SDL_کھڑکی *کھڑکی,
                                  VkInstance instance,
                                  ثابت ساخت Vk_تخصیص_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, false);

    اگر (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        واپس false;
    }

    CHECK_PARAM(!instance) {
        واپس SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        واپس SDL_InvalidParamError("surface");
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_VULKAN)) {
        // No problem, we can convert to Vulkan
        اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
            کھڑکی->flags &= ~SDL_کھڑکی_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        اگر (کھڑکی->flags & SDL_کھڑکی_METAL) {
            کھڑکی->flags &= ~SDL_کھڑکی_METAL;
            // Nothing more to do for Metal.
        }
        اگر (SDL_Vulkan_بھرو_Library(تہی)) {
            کھڑکی->flags |= SDL_کھڑکی_VULKAN;
        } ورنہ {
            واپس SDL_سیٹ_Error("failed to load Vulkan library");
        }
    }

    واپس _this->Vulkan_CreateSurface(_this, کھڑکی, instance, allocator, surface);
}

خالی SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ثابت ساخت Vk_تخصیص_Callbacks *allocator)
{
    اگر (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 قطار_Family_اشاریہ)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        واپس false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        واپس false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        واپس false;
    }

    اگر (_this->Vulkan_GetPresentationSupport) {
        واپس _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, قطار_Family_اشاریہ);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    واپس true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_کھڑکی *کھڑکی)
{
    CHECK_کھڑکی_MAGIC(کھڑکی, تہی);

    اگر (!_this->Metal_CreateView) {
        SDL_Unsupported();
        واپس تہی;
    }

    اگر (!(کھڑکی->flags & SDL_کھڑکی_METAL)) {
        // No problem, we can convert to Metal
        اگر (کھڑکی->flags & SDL_کھڑکی_OPENGL) {
            کھڑکی->flags &= ~SDL_کھڑکی_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        اگر (کھڑکی->flags & SDL_کھڑکی_VULKAN) {
            کھڑکی->flags &= ~SDL_کھڑکی_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        کھڑکی->flags |= SDL_کھڑکی_METAL;
    }

    واپس _this->Metal_CreateView(_this, کھڑکی);
}

خالی SDL_Metal_DestroyView(SDL_MetalView view)
{
    اگر (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

خالی *SDL_Metal_GetLayer(SDL_MetalView view)
{
    اگر (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            واپس تہی;
        }
        واپس _this->Metal_GetLayer(_this, view);
    } ورنہ {
        SDL_سیٹ_Error("Metal is not supported.");
        واپس تہی;
    }
}

#اگر defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ثابت حرف *SDL_GetCSSCursorName(SDL_SystemCursor id, ثابت حرف **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    انتخاب (id) {
    حالت SDL_SYSTEM_CURSOR_DEFAULT:
        واپس "default";

    حالت SDL_SYSTEM_CURSOR_متن:
        واپس "text";

    حالت SDL_SYSTEM_CURSOR_WAIT:
        واپس "wait";

    حالت SDL_SYSTEM_CURSOR_CROSSHAIR:
        واپس "crosshair";

    حالت SDL_SYSTEM_CURSOR_پیش_رفت:
        واپس "progress";

    حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        اگر (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        واپس "nwse-resize";

    حالت SDL_SYSTEM_CURSOR_NESW_RESIZE:
        اگر (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        واپس "nesw-resize";

    حالت SDL_SYSTEM_CURSOR_EW_RESIZE:
        اگر (fallback_name) {
            *fallback_name = "col-resize";
        }
        واپس "ew-resize";

    حالت SDL_SYSTEM_CURSOR_NS_RESIZE:
        اگر (fallback_name) {
            *fallback_name = "row-resize";
        }
        واپس "ns-resize";

    حالت SDL_SYSTEM_CURSOR_MOVE:
        اگر (fallback_name) {
            *fallback_name = "all-scroll";
        }
        واپس "move";

    حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        واپس "not-allowed";

    حالت SDL_SYSTEM_CURSOR_اشارہ_گر:
        واپس "pointer";

    حالت SDL_SYSTEM_CURSOR_NW_RESIZE:
        واپس "nw-resize";

    حالت SDL_SYSTEM_CURSOR_N_RESIZE:
        واپس "n-resize";

    حالت SDL_SYSTEM_CURSOR_NE_RESIZE:
        واپس "ne-resize";

    حالت SDL_SYSTEM_CURSOR_E_RESIZE:
        واپس "e-resize";

    حالت SDL_SYSTEM_CURSOR_SE_RESIZE:
        واپس "se-resize";

    حالت SDL_SYSTEM_CURSOR_S_RESIZE:
        واپس "s-resize";

    حالت SDL_SYSTEM_CURSOR_SW_RESIZE:
        واپس "sw-resize";

    حالت SDL_SYSTEM_CURSOR_W_RESIZE:
        واپس "w-resize";

    حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        واپس "context-menu";

    حالت SDL_SYSTEM_CURSOR_HELP:
        واپس "help";

    حالت SDL_SYSTEM_CURSOR_CELL:
        واپس "cell";

    حالت SDL_SYSTEM_CURSOR_VERTICAL_متن:
        واپس "vertical-text";

    حالت SDL_SYSTEM_CURSOR_ALIAS:
        واپس "alias";

    حالت SDL_SYSTEM_CURSOR_COPY:
        واپس "copy";

    حالت SDL_SYSTEM_CURSOR_NO_DROP:
        واپس "no-drop";

    حالت SDL_SYSTEM_CURSOR_GRAB:
        واپس "grab";

    حالت SDL_SYSTEM_CURSOR_GRABBING:
        واپس "grabbing";

    حالت SDL_SYSTEM_CURSOR_ستون_RESIZE:
        واپس "col-resize";

    حالت SDL_SYSTEM_CURSOR_صف_RESIZE:
        واپس "row-resize";

    حالت SDL_SYSTEM_CURSOR_ALL_SCROLL:
        اگر (fallback_name) {
            *fallback_name = "move";
        }
        واپس "all-scroll";

    حالت SDL_SYSTEM_CURSOR_ZOOM_اندر:
        واپس "zoom-in";

    حالت SDL_SYSTEM_CURSOR_ZOOM_برآمد:
        واپس "zoom-out";

    طےشدہ:
        واپس "default";
    }
}
#اگر_ختم

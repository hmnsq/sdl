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

#अन्तर्भाव "SDL_internal.h"

// The high-level video driver subsystem

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_clipboard_c.h"
#अन्तर्भाव "SDL_egl_c.h"
#अन्तर्भाव "SDL_surface_c.h"
#अन्तर्भाव "SDL_pixels_c.h"
#अन्तर्भाव "SDL_rect_c.h"
#अन्तर्भाव "SDL_video_c.h"
#अन्तर्भाव "../events/SDL_events_c.h"
#अन्तर्भाव "../SDL_hints_c.h"
#अन्तर्भाव "../SDL_properties_c.h"
#अन्तर्भाव "../timer/SDL_timer_c.h"
#अन्तर्भाव "../camera/SDL_camera_c.h"
#अन्तर्भाव "../render/SDL_sysrender.h"
#अन्तर्भाव "../main/SDL_main_callbacks.h"

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
#अन्तर्भाव <SDL3/SDL_opengl.h>
#यदि_अन्तः // SDL_VIDEO_OPENGL

#यदि defined(SDL_VIDEO_OPENGL_ES) && !defined(SDL_VIDEO_OPENGL)
#अन्तर्भाव <SDL3/SDL_opengles.h>
#यदि_अन्तः // SDL_VIDEO_OPENGL_ES && !SDL_VIDEO_OPENGL

// GL and GLES2 headers conflict on Linux 32 bits
#यदि defined(SDL_VIDEO_OPENGL_ES2) && !defined(SDL_VIDEO_OPENGL)
#अन्तर्भाव <SDL3/SDL_opengles2.h>
#यदि_अन्तः // SDL_VIDEO_OPENGL_ES2 && !SDL_VIDEO_OPENGL

// GL_CONTEXT_RELEASE_BEHAVIOR and GL_CONTEXT_RELEASE_BEHAVIOR_KHR have the same number.
#यदि_अपरिभाषितम् GL_CONTEXT_RELEASE_BEHAVIOR
#परिभाषय GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#यदि_अन्तः

// GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH and GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR have the same number.
#यदि_अपरिभाषितम् GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH
#परिभाषय GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#यदि_अन्तः

// This is always the same number between the various EXT/ARB/GLES extensions.
#यदि_अपरिभाषितम् GL_FRAMEBUFFER_SRGB
#परिभाषय GL_FRAMEBUFFER_SRGB 0x8DB9
#यदि_अन्तः

#यदि_परिभाषितम् SDL_PLATFORM_EMSCRIPTEN
#अन्तर्भाव <emscripten.h>
#यदि_अन्तः

#यदि_परिभाषितम् SDL_PLATFORM_3DS
#अन्तर्भाव <3ds.h>
#यदि_अन्तः

#यदि_अपरिभाषितम् GL_RGBA_FLOAT_बहुलकम्_ARB
#परिभाषय GL_RGBA_FLOAT_बहुलकम्_ARB 0x8820
#यदि_अन्तः /* GL_RGBA_FLOAT_MODE_ARB */

// Available video drivers
स्थिर VideoBootStrap *bootstrap[] = {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_वैयक्तिकम्
    &वैयक्तिकम्_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_COCOA
    &COCOA_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_preferred_bootstrap,
#यदि_अन्तः
    &X11_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND
    &Wayland_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VIVANTE
    &VIVANTE_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WINDOWS
    &WINDOWS_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_HAIKU
    &HAIKU_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_UIKIT
    &UIKIT_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID
    &Android_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OPENHARMONY
    &OPENHARMONY_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_PS2
    &PS2_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_PSP
    &PSP_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_VITA
    &VITA_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_N3DS
    &N3DS_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_NGAGE
    &NGAGE_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_KMSDRM
    &KMSDRM_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RISCOS
    &RISCOS_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_RPI
    &RPI_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_EMSCRIPTEN
    &Emscripten_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_QNX
    &QNX_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OFFSCREEN
    &OFFSCREEN_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_DUMMY
    &DUMMY_bootstrap,
#यदि_परिभाषितम् SDL_निवेशः_LINUXEV
    &DUMMY_evdev_bootstrap,
#यदि_अन्तः
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_DOSVESA
    &DOSVESA_bootstrap,
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_OPENVR
    &OPENVR_bootstrap,
#यदि_अन्तः
    रिक्त
};

#परिभाषय CHECK_गवाक्षः_MAGIC(गवाक्षः, परिणाम)                              \
    CHECK_PARAM(!_this) {                                               \
        SDL_UninitializedVideo();                                       \
        प्रत्यागम परिणाम;                                                  \
    }                                                                   \
    CHECK_PARAM(!SDL_ObjectValid(गवाक्षः, SDL_OBJECT_TYPE_गवाक्षः)) {     \
        SDL_समुच्चयः_Error("Invalid window");                                 \
        प्रत्यागम परिणाम;                                                  \
    }

#परिभाषय CHECK_DISPLAY_MAGIC(display, परिणाम)                            \
    CHECK_PARAM(!display) {                                             \
        प्रत्यागम परिणाम;                                                  \
    }                                                                   \

#परिभाषय CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, परिणाम)                          \
    CHECK_PARAM(SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {                          \
        SDL_समुच्चयः_Error("Operation invalid on popup windows");             \
        प्रत्यागम परिणाम;                                                  \
    }

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
// Support for macOS fullscreen spaces, etc.
बाह्य bool Cocoa_Is_गवाक्षः_अन्तर्_Fullscreen_Space(SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_Is_गवाक्षः_अन्तर्_Fullscreen_Space_Transition(SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_समुच्चयः_गवाक्षः_Fullscreen_Space(SDL_गवाक्षः *गवाक्षः, bool state, bool blocking);
बाह्य bool Cocoa_IsShowingModalDialog(SDL_गवाक्षः *गवाक्षः);
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_UIKIT
बाह्य शून्य SDL_UpdateLifecycleObserver(शून्य);
#यदि_अन्तः

स्थिर शून्य SDL_Check_गवाक्षः_Display_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः);
स्थिर शून्य SDL_Check_गवाक्षः_Display_Scale_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः);
स्थिर शून्य SDL_Check_गवाक्षः_Safe_Area_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः);

// Convenience functions for reading driver flags
स्थिर bool SDL_बहुलकम्_Switching_Emulated(SDL_VideoDevice *_this)
{
    यदि (_this->device_caps & VIDEO_DEVICE_CAPS_बहुलकम्_SWITCHING_EMULATED) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

स्थिर bool SDL_SendsFullscreenDimensions(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_FULLSCREEN_DIMENSIONS);
}

स्थिर bool IsFullscreenOnly(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_FULLSCREEN_ONLY);
}

स्थिर bool SDL_SendsDisplayChanges(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_DISPLAY_CHANGES);
}

स्थिर bool SDL_DriverSendsHDRChanges(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SENDS_HDR_CHANGES);
}

स्थिर bool SDL_DriverHasSlowFramebuffer(SDL_VideoDevice *_this)
{
    प्रत्यागम !!(_this->device_caps & VIDEO_DEVICE_CAPS_SLOW_FRAMEBUFFER);
}

// Hint to treat all window ops as synchronous
स्थिर bool syncHint;

स्थिर शून्य SDL_SyncHintWatcher(शून्य *userdata, ध्रुव वर्ण *name, ध्रुव वर्ण *old_मानम्, ध्रुव वर्ण *new_मानम्)
{
    syncHint = SDL_GetStringBoolean(new_मानम्, false);
}

स्थिर शून्य SDL_SyncIfRequired(SDL_गवाक्षः *गवाक्षः)
{
    यदि (syncHint) {
        SDL_Sync_गवाक्षः(गवाक्षः);
    }
}

स्थिर शून्य SDL_Update_गवाक्षः_Hierarchy(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent)
{
    // Unlink the window from the existing parent.
    यदि (गवाक्षः->parent) {
        यदि (गवाक्षः->अग्र_sibling) {
            गवाक्षः->अग्र_sibling->पूर्व_sibling = गवाक्षः->पूर्व_sibling;
        }
        यदि (गवाक्षः->पूर्व_sibling) {
            गवाक्षः->पूर्व_sibling->अग्र_sibling = गवाक्षः->अग्र_sibling;
        } अन्यथा {
            गवाक्षः->parent->first_child = गवाक्षः->अग्र_sibling;
        }

        गवाक्षः->parent = रिक्त;
    }

    यदि (parent) {
        गवाक्षः->parent = parent;

        गवाक्षः->अग्र_sibling = parent->first_child;
        यदि (parent->first_child) {
            parent->first_child->पूर्व_sibling = गवाक्षः;
        }
        parent->first_child = गवाक्षः;
    }
}

// Support for framebuffer emulation using an accelerated renderer

#परिभाषय SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER "SDL.internal.window.texturedata"

प्रकारनिर्देश संरचना
{
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    शून्य *pixels;
    पूर्णाङ्क pitch;
    पूर्णाङ्क अष्टकानि_प्रत्येकम्_pixel;
} SDL_गवाक्षः_Texture_दत्त;

स्थिर Uint32 SDL_DefaultGraphicsBackends(SDL_VideoDevice *_this)
{
#यदि (defined(SDL_VIDEO_OPENGL) && defined(SDL_PLATFORM_MACOS)) || (defined(SDL_PLATFORM_IOS) && !TARGET_OS_MACCATALYST) || defined(SDL_PLATFORM_QNXNTO)
    यदि (_this->GL_CreateContext) {
        प्रत्यागम SDL_गवाक्षः_OPENGL;
    }
#यदि_अन्तः
#यदि defined(SDL_VIDEO_METAL) && (TARGET_OS_MACCATALYST || defined(SDL_PLATFORM_MACOS) || defined(SDL_PLATFORM_IOS))
    यदि (_this->Metal_CreateView) {
        प्रत्यागम SDL_गवाक्षः_METAL;
    }
#यदि_अन्तः
#यदि defined(SDL_VIDEO_OPENGL) && defined(SDL_VIDEO_DRIVER_OPENVR)
    यदि (SDL_strcmp(_this->name, "openvr") == 0) {
        प्रत्यागम SDL_गवाक्षः_OPENGL;
    }
#यदि_अन्तः
    प्रत्यागम 0;
}

स्थिर bool SDL_Create_गवाक्षः_Texture(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format, शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    SDL_गवाक्षः_Texture_दत्त *दत्त = (SDL_गवाक्षः_Texture_दत्त *)SDL_GetPointerProperty(props, SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER, रिक्त);
    ध्रुव bool transparent = (गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) ? true : false;
    पूर्णाङ्क i;
    पूर्णाङ्क w, h;
    ध्रुव SDL_PixelFormat *texture_formats;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);

    यदि (!दत्त) {
        SDL_Renderer *renderer = रिक्त;
        ध्रुव वर्ण *render_driver = रिक्त;

        // See if there's a render driver being requested
        ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
        यदि (hint && *hint != '0' && *hint != '1' &&
            SDL_strcasecmp(hint, "true") != 0 &&
            SDL_strcasecmp(hint, "false") != 0 &&
            SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) != 0) {
            render_driver = hint;
        }

        यदि (!render_driver) {
            render_driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
        }
        यदि (render_driver && SDL_strcasecmp(render_driver, SDL_SOFTWARE_RENDERER) == 0) {
            render_driver = रिक्त;
        }

        वर्ण *render_driver_copy = रिक्त;
        यदि (render_driver && *render_driver) {
            render_driver_copy = SDL_strdup(render_driver);
            render_driver = render_driver_copy;
            यदि (render_driver_copy) {  // turn any "software" requests into "xxxxxxxx" so we don't end up in infinite recursion.
                वर्ण *पूर्व = render_driver_copy;
                वर्ण *ptr = पूर्व;
                यावत् ((ptr = SDL_strchr(ptr, ',')) != रिक्त) {
                    *ptr = '\0';
                    ध्रुव bool is_sw = (SDL_strcasecmp(पूर्व, SDL_SOFTWARE_RENDERER) == 0);
                    *ptr = ',';
                    यदि (is_sw) {
                        SDL_memset(पूर्व, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                        ptr = पूर्व;
                    } अन्यथा {
                        ptr++;
                        पूर्व = ptr;
                    }
                }

                यदि (SDL_strcasecmp(पूर्व, SDL_SOFTWARE_RENDERER) == 0) {
                    SDL_memset(पूर्व, 'x', SDL_strlen(SDL_SOFTWARE_RENDERER));
                }
            }
        }

        // Check to see if there's a specific driver requested
        यदि (render_driver) {
            renderer = SDL_CreateRenderer(गवाक्षः, render_driver);
            SDL_free(render_driver_copy);
            यदि (!renderer) {
                // The error for this specific renderer has already been set
                प्रत्यागम false;
            }
        } अन्यथा {
            SDL_assert(render_driver_copy == रिक्त);
            ध्रुव पूर्णाङ्क योग = SDL_Get_अङ्कः_Render_Drivers();
            प्रति (i = 0; i < योग; ++i) {
                ध्रुव वर्ण *name = SDL_GetRenderDriver(i);
                यदि (name && SDL_strcmp(name, SDL_SOFTWARE_RENDERER) != 0) {
                    renderer = SDL_CreateRenderer(गवाक्षः, name);
                    यदि (renderer) {
                        भङ्ग; // this will work.
                    }
                }
            }
            यदि (!renderer) {
                प्रत्यागम SDL_समुच्चयः_Error("No hardware accelerated renderers available");
            }
        }

        SDL_assert(renderer != रिक्त); // should have explicitly checked this above.

        // Create the data after we successfully create the renderer (bug #1116)
        दत्त = (SDL_गवाक्षः_Texture_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
        यदि (!दत्त) {
            SDL_DestroyRenderer(renderer);
            प्रत्यागम false;
        }
        यदि (!SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER, दत्त)) {
            SDL_DestroyRenderer(renderer);
            प्रत्यागम false;
        }

        दत्त->renderer = renderer;
    }

    texture_formats = (ध्रुव SDL_PixelFormat *)SDL_GetPointerProperty(SDL_GetRendererProperties(दत्त->renderer), SDL_PROP_RENDERER_TEXTURE_FORMATS_POINTER, रिक्त);
    यदि (!texture_formats) {
        प्रत्यागम false;
    }

    // Free any old texture and pixel data
    यदि (दत्त->texture) {
        SDL_DestroyTexture(दत्त->texture);
        दत्त->texture = रिक्त;
    }
    SDL_free(दत्त->pixels);
    दत्त->pixels = रिक्त;

    // Find the first format with or without an alpha channel
    *format = texture_formats[0];

    प्रति (i = 0; texture_formats[i] != SDL_PIXELFORMAT_UNKNOWN; ++i) {
        SDL_PixelFormat texture_format = texture_formats[i];
        यदि (!SDL_ISPIXELFORMAT_FOURCC(texture_format) &&
            !SDL_ISPIXELFORMAT_10BIT(texture_format) &&
            !SDL_ISPIXELFORMAT_FLOAT(texture_format) &&
            !SDL_ISPIXELFORMAT_अनुक्रमितम्(texture_format) &&
            (!transparent || SDL_ISPIXELFORMAT_ALPHA(texture_format))) {
            *format = texture_format;
            भङ्ग;
        }
    }

    दत्त->texture = SDL_CreateTexture(दत्त->renderer, *format,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      w, h);
    यदि (!दत्त->texture) {
        // codechecker_false_positive [Malloc] Static analyzer doesn't realize allocated `data` is saved to SDL_PROP_WINDOW_TEXTUREDATA_POINTER and not leaked here.
        प्रत्यागम false; // NOLINT(clang-analyzer-unix.Malloc)
    }
    SDL_समुच्चयः_Texture_Blend_बहुलकम्(दत्त->texture, SDL_BLENDMODE_NONE);

    // Create framebuffer data
    दत्त->अष्टकानि_प्रत्येकम्_pixel = SDL_BYTESPERPIXEL(*format);
    दत्त->pitch = (((w * दत्त->अष्टकानि_प्रत्येकम्_pixel) + 3) & ~3);

    {
        // Make static analysis happy about potential SDL_malloc(0) calls.
        ध्रुव size_t allocsize = (size_t)h * दत्त->pitch;
        दत्त->pixels = SDL_malloc((allocsize > 0) ? allocsize : 1);
        यदि (!दत्त->pixels) {
            प्रत्यागम false;
        }
    }

    *pixels = दत्त->pixels;
    *pitch = दत्त->pitch;

    // Make sure we're not double-scaling the viewport
    SDL_समुच्चयः_Render_Viewport(दत्त->renderer, रिक्त);

    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Texture_VSync(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क vsync)
{
    SDL_गवाक्षः_Texture_दत्त *दत्त;

    दत्त = (SDL_गवाक्षः_Texture_दत्त *)SDL_GetPointerProperty(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER, रिक्त);
    यदि (!दत्त) {
        प्रत्यागम false;
    }
    यदि (!दत्त->renderer) {
        प्रत्यागम false;
    }
    प्रत्यागम SDL_समुच्चयः_Render_VSync(दत्त->renderer, vsync);
}

स्थिर bool SDL_Get_गवाक्षः_Texture_VSync(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *vsync)
{
    SDL_गवाक्षः_Texture_दत्त *दत्त;

    दत्त = (SDL_गवाक्षः_Texture_दत्त *)SDL_GetPointerProperty(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER, रिक्त);
    यदि (!दत्त) {
        प्रत्यागम false;
    }
    यदि (!दत्त->renderer) {
        प्रत्यागम false;
    }
    प्रत्यागम SDL_GetRenderVSync(दत्त->renderer, vsync);
}

स्थिर bool SDL_Update_गवाक्षः_Texture(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects, पूर्णाङ्क numrects)
{
    SDL_गवाक्षः_Texture_दत्त *दत्त;
    SDL_Rect rect;
    शून्य *src;
    पूर्णाङ्क w, h;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);

    दत्त = (SDL_गवाक्षः_Texture_दत्त *)SDL_GetPointerProperty(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER, रिक्त);
    यदि (!दत्त || !दत्त->texture) {
        प्रत्यागम SDL_समुच्चयः_Error("No window texture data");
    }

    // Update a single rect that contains subrects for best DMA performance
    यदि (SDL_Get_विस्तृतिः_Enclosing_Rect(w, h, numrects, rects, &rect)) {
        src = (शून्य *)((Uint8 *)दत्त->pixels +
                       rect.y * दत्त->pitch +
                       rect.x * दत्त->अष्टकानि_प्रत्येकम्_pixel);
        यदि (!SDL_UpdateTexture(दत्त->texture, &rect, src, दत्त->pitch)) {
            प्रत्यागम false;
        }

        यदि (!SDL_RenderTexture(दत्त->renderer, दत्त->texture, रिक्त, रिक्त)) {
            प्रत्यागम false;
        }

        SDL_RenderPresent(दत्त->renderer);
    }
    प्रत्यागम true;
}

स्थिर शून्य SDL_Destroy_गवाक्षः_Texture(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    यदि (SDL_HasProperty(props, SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER)) {
        SDL_गवाक्षः_Texture_दत्त *दत्त = SDL_GetPointerProperty(props, SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER, रिक्त);

        यदि (दत्त->texture) {
            SDL_DestroyTexture(दत्त->texture);
        }
        यदि (दत्त->renderer) {
            SDL_DestroyRenderer(दत्त->renderer);
        }
        SDL_free(दत्त->pixels);
        SDL_free(दत्त);

        SDL_ClearProperty(props, SDL_PROP_गवाक्षः_TEXTUREDATA_POINTER);
    }
}

स्थिर SDL_VideoDevice *_this = रिक्त;
स्थिर SDL_AtomicInt SDL_messagebox_गणनम्;

स्थिर पूर्णाङ्क SDLCALL cmpmodes(ध्रुव शून्य *A, ध्रुव शून्य *B)
{
    ध्रुव SDL_Display_बहुलकम् *a = (ध्रुव SDL_Display_बहुलकम् *)A;
    ध्रुव SDL_Display_बहुलकम् *b = (ध्रुव SDL_Display_बहुलकम् *)B;
    पूर्णाङ्क a_refresh_दरः = (पूर्णाङ्क)(a->refresh_दरः * 100);
    पूर्णाङ्क b_refresh_दरः = (पूर्णाङ्क)(b->refresh_दरः * 100);
    पूर्णाङ्क a_pixel_density = (पूर्णाङ्क)(a->pixel_density * 100);
    पूर्णाङ्क b_pixel_density = (पूर्णाङ्क)(b->pixel_density * 100);

    यदि (a->w != b->w) {
        प्रत्यागम b->w - a->w;
    } अन्यथा यदि (a->h != b->h) {
        प्रत्यागम b->h - a->h;
    } अन्यथा यदि (SDL_BITSPERPIXEL(a->format) != SDL_BITSPERPIXEL(b->format)) {
        प्रत्यागम SDL_BITSPERPIXEL(b->format) - SDL_BITSPERPIXEL(a->format);
    } अन्यथा यदि (SDL_PIXELLAYOUT(a->format) != SDL_PIXELLAYOUT(b->format)) {
        प्रत्यागम SDL_PIXELLAYOUT(b->format) - SDL_PIXELLAYOUT(a->format);
    } अन्यथा यदि (a_refresh_दरः != b_refresh_दरः) {
        प्रत्यागम b_refresh_दरः - a_refresh_दरः;
    } अन्यथा यदि (a_pixel_density != b_pixel_density) {
        प्रत्यागम a_pixel_density - b_pixel_density;
    }
    प्रत्यागम 0;
}

bool SDL_UninitializedVideo(शून्य)
{
    प्रत्यागम SDL_समुच्चयः_Error("Video subsystem has not been initialized");
}

// Deduplicated list of video bootstrap drivers.
स्थिर ध्रुव VideoBootStrap *deduped_bootstrap[SDL_arraysize(bootstrap) - 1];

पूर्णाङ्क SDL_Get_अङ्कः_Video_Drivers(शून्य)
{
    स्थिर पूर्णाङ्क अङ्कः_drivers = -1;

    यदि (अङ्कः_drivers >= 0) {
        प्रत्यागम अङ्कः_drivers;
    }

    अङ्कः_drivers = 0;

    // Build a list of unique video drivers.
    प्रति (पूर्णाङ्क i = 0; bootstrap[i] != रिक्त; ++i) {
        bool duplicate = false;
        प्रति (पूर्णाङ्क j = 0; j < i; ++j) {
            यदि (SDL_strcmp(bootstrap[i]->name, bootstrap[j]->name) == 0) {
                duplicate = true;
                भङ्ग;
            }
        }

        यदि (!duplicate) {
            deduped_bootstrap[अङ्कः_drivers++] = bootstrap[i];
        }
    }

    प्रत्यागम अङ्कः_drivers;
}

ध्रुव वर्ण *SDL_GetVideoDriver(पूर्णाङ्क सूचकांक)
{
    CHECK_PARAM(सूचकांक < 0 || सूचकांक >= SDL_Get_अङ्कः_Video_Drivers()) {
        SDL_InvalidParamError("index");
        प्रत्यागम रिक्त;
    }
    प्रत्यागम deduped_bootstrap[सूचकांक]->name;
}

/*
 * Initialize the video and event subsystems -- determine native pixel format
 */
bool SDL_InitVideo(ध्रुव वर्ण *driver_name)
{
    SDL_VideoDevice *video;
    bool init_events = false;
    bool init_keyboard = false;
    bool init_mouse = false;
    bool init_touch = false;
    bool init_pen = false;
    पूर्णाङ्क i = 0;

    // Check to make sure we don't overwrite '_this'
    यदि (_this) {
        SDL_QuitVideo();
    }

    SDL_InitTicks();

    // Start the event loop
    यदि (!SDL_InitSubSystem(SDL_INIT_EVENTS)) {
        गच्छ pre_driver_error;
    }
    init_events = true;
    यदि (!SDL_InitKeyboard()) {
        गच्छ pre_driver_error;
    }
    init_keyboard = true;
    यदि (!SDL_PreInitMouse()) {
        गच्छ pre_driver_error;
    }
    init_mouse = true;
    यदि (!SDL_InitTouch()) {
        गच्छ pre_driver_error;
    }
    init_touch = true;
    यदि (!SDL_InitPen()) {
        गच्छ pre_driver_error;
    }
    init_pen = true;

    // Select the proper video driver
    video = रिक्त;
#यदि_परिभाषितम् SDL_PLATFORM_LINUX
    // https://github.com/libsdl-org/SDL/issues/12247
    यदि (SDL_IsUbuntuTouch()) {
        driver_name = "wayland";
    }
#यदि_अन्तः
    यदि (!driver_name) {
        driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
    }
    यदि (driver_name && *driver_name != 0) {
        ध्रुव वर्ण *driver_attempt = driver_name;
        यावत् (driver_attempt && *driver_attempt != 0 && !video) {
            ध्रुव वर्ण *driver_attempt_अन्तः = SDL_strchr(driver_attempt, ',');
            size_t driver_attempt_len = (driver_attempt_अन्तः) ? (driver_attempt_अन्तः - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);

            प्रति (i = 0; bootstrap[i]; ++i) {
                यदि (!bootstrap[i]->is_preferred &&
                    (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                    (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                    video = bootstrap[i]->create();
                    यदि (video) {
                        भङ्ग;
                    }
                }
            }

            driver_attempt = (driver_attempt_अन्तः) ? (driver_attempt_अन्तः + 1) : रिक्त;
        }
    } अन्यथा {
        प्रति (i = 0; bootstrap[i]; ++i) {
            video = bootstrap[i]->create();
            यदि (video) {
                भङ्ग;
            }
        }
    }
    यदि (video) {
        SDL_DebugLogBackend("video", bootstrap[i]->name);
    } अन्यथा {
        यदि (driver_name) {
            SDL_समुच्चयः_Error("%s not available", driver_name);
            गच्छ pre_driver_error;
        }
        SDL_समुच्चयः_Error("No available video device");
        गच्छ pre_driver_error;
    }

    /* From this point on, use SDL_QuitVideo to cleanup on error, rather than
    pre_driver_error. */
    _this = video;
    _this->name = bootstrap[i]->name;
    _this->thread = SDL_GetCurrentThreadID();

    // Set some very sane GL defaults
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = रिक्त;
    SDL_GL_Reset_गुणाः();

    // Initialize the video subsystem
    यदि (!_this->VideoInit(_this)) {
        SDL_QuitVideo();
        प्रत्यागम false;
    }

    // Make sure some displays were added
    यदि (_this->अङ्कः_displays == 0) {
        SDL_QuitVideo();
        प्रत्यागम SDL_समुच्चयः_Error("The video driver did not add any displays");
    }

    SDL_सङ्कलय_Hint_Callback(SDL_HINT_VIDEO_SYNC_गवाक्षः_OPERATIONS, SDL_SyncHintWatcher, रिक्त);

    /* Disable the screen saver by default. This is a change from <= 2.0.1,
       but most things using SDL are games or media players; you wouldn't
       want a screensaver to trigger if you're playing exclusively with a
       joystick, or passively watching a movie. Things that use SDL but
       function more like a normal desktop app should explicitly re-enable the
       screensaver. */
    यदि (!SDL_GetHintBoolean(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, false)) {
        SDL_DisableScreenSaver();
    }

    SDL_PostInitMouse();

    // We're ready to go!
    प्रत्यागम true;

pre_driver_error:
    SDL_assert(_this == रिक्त);
    यदि (init_pen) {
        SDL_QuitPen();
    }
    यदि (init_touch) {
        SDL_QuitTouch();
    }
    यदि (init_mouse) {
        SDL_QuitMouse();
    }
    यदि (init_keyboard) {
        SDL_QuitKeyboard();
    }
    यदि (init_events) {
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
    }
    प्रत्यागम false;
}

ध्रुव वर्ण *SDL_GetCurrentVideoDriver(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->name;
}

SDL_VideoDevice *SDL_GetVideoDevice(शून्य)
{
    प्रत्यागम _this;
}

bool SDL_OnVideoThread(शून्य)
{
    प्रत्यागम (_this && SDL_GetCurrentThreadID() == _this->thread);
}

शून्य SDL_समुच्चयः_System_Theme(SDL_SystemTheme theme)
{
    यदि (_this && theme != _this->system_theme) {
        _this->system_theme = theme;
        SDL_Send_System_Theme_परिवर्तितम्_Event();
    }
}

SDL_SystemTheme SDL_GetSystemTheme(शून्य)
{
    यदि (_this) {
        प्रत्यागम _this->system_theme;
    } अन्यथा {
        प्रत्यागम SDL_SYSTEM_THEME_UNKNOWN;
    }
}

शून्य SDL_UpdateDesktopBounds(शून्य)
{
    SDL_Rect rect;
    SDL_zero(rect);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    यदि (displays) {
        प्रति (पूर्णाङ्क i = 0; displays[i]; ++i) {
            SDL_Rect bounds;
            यदि (SDL_GetDisplayBounds(displays[i], &bounds)) {
                यदि (i == 0) {
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

स्थिर शून्य SDL_Finalize_Display_बहुलकम्(SDL_Display_बहुलकम् *बहुलकम्)
{
    // Make sure all the fields are set up correctly
    यदि (बहुलकम्->pixel_density <= 0.0f) {
        बहुलकम्->pixel_density = 1.0f;
    }

    यदि (बहुलकम्->refresh_दरः_numerator > 0) {
        यदि (बहुलकम्->refresh_दरः_denominator <= 0) {
            बहुलकम्->refresh_दरः_denominator = 1;
        }
        बहुलकम्->refresh_दरः = (भिन्न)बहुलकम्->refresh_दरः_numerator / बहुलकम्->refresh_दरः_denominator;
    } अन्यथा {
        SDL_CalculateFraction(बहुलकम्->refresh_दरः, &बहुलकम्->refresh_दरः_numerator, &बहुलकम्->refresh_दरः_denominator);
    }
    बहुलकम्->refresh_दरः = SDL_roundf(बहुलकम्->refresh_दरः * 100) / 100.0f;
}

SDL_DisplayID SDL_सङ्कलय_Basic_Video_Display(ध्रुव SDL_Display_बहुलकम् *desktop_बहुलकम्)
{
    SDL_VideoDisplay display;

    SDL_zero(display);
    यदि (desktop_बहुलकम्) {
        SDL_memcpy(&display.desktop_बहुलकम्, desktop_बहुलकम्, परिमाण(display.desktop_बहुलकम्));
    }
    प्रत्यागम SDL_सङ्कलय_Video_Display(&display, false);
}

SDL_DisplayID SDL_सङ्कलय_Video_Display(ध्रुव SDL_VideoDisplay *display, bool send_event)
{
    SDL_VideoDisplay **displays, *new_display;
    SDL_DisplayID id;
    SDL_PropertiesID props;
    पूर्णाङ्क i;

    new_display = (SDL_VideoDisplay *)SDL_malloc(परिमाण(*new_display));
    यदि (!new_display) {
        प्रत्यागम 0;
    }

    displays = (SDL_VideoDisplay **)SDL_realloc(_this->displays, (_this->अङ्कः_displays + 1) * परिमाण(*displays));
    यदि (!displays) {
        SDL_free(new_display);
        प्रत्यागम 0;
    }
    _this->displays = displays;
    _this->displays[_this->अङ्कः_displays++] = new_display;

    id = SDL_Get_अग्र_Object_ID();
    SDL_copyp(new_display, display);
    new_display->id = id;
    new_display->device = _this;
    यदि (display->name) {
        new_display->name = SDL_strdup(display->name);
    } अन्यथा {
        वर्ण name[32];

        SDL_itoa(id, name, 10);
        new_display->name = SDL_strdup(name);
    }
    यदि (new_display->content_scale == 0.0f) {
        new_display->content_scale = 1.0f;
    }

    new_display->desktop_बहुलकम्.displayID = id;
    new_display->current_बहुलकम् = &new_display->desktop_बहुलकम्;
    SDL_Finalize_Display_बहुलकम्(&new_display->desktop_बहुलकम्);

    प्रति (i = 0; i < new_display->अङ्कः_fullscreen_modes; ++i) {
        new_display->fullscreen_modes[i].displayID = id;
    }

    new_display->HDR.HDR_headroom = SDL_max(display->HDR.HDR_headroom, 1.0f);
    new_display->HDR.SDR_white_level = SDL_max(display->HDR.SDR_white_level, 1.0f);

    props = SDL_GetDisplayProperties(id);
    SDL_समुच्चयः_Boolean_Property(props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, new_display->HDR.HDR_headroom > 1.0f);

    SDL_UpdateDesktopBounds();

    यदि (send_event) {
        SDL_SendDisplayEvent(new_display, SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }

    प्रत्यागम id;
}

शून्य SDL_OnDisplayAdded(SDL_VideoDisplay *display)
{
    SDL_गवाक्षः *गवाक्षः;

    // See if any windows have changed to the new display
    प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        SDL_Check_गवाक्षः_Display_परिवर्तितम्(गवाक्षः);
    }
}

शून्य SDL_OnDisplayMoved(SDL_VideoDisplay *display)
{
    SDL_UpdateDesktopBounds();
}

शून्य SDL_DelVideoDisplay(SDL_DisplayID displayID, bool send_event)
{
    SDL_VideoDisplay *display;
    पूर्णाङ्क display_सूचकांक = SDL_Get_Display_सूचकांक(displayID);
    यदि (display_सूचकांक < 0) {
        प्रत्यागम;
    }

    display = _this->displays[display_सूचकांक];

    यदि (send_event) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_REMOVED, 0, 0);
    }

    SDL_DestroyProperties(display->props);
    SDL_free(display->name);
    SDL_ResetFullscreenDisplayModes(display);
    SDL_free(display->desktop_बहुलकम्.आन्तरिकम्);
    display->desktop_बहुलकम्.आन्तरिकम् = रिक्त;
    SDL_free(display->आन्तरिकम्);
    display->आन्तरिकम् = रिक्त;
    SDL_free(display);

    यदि (display_सूचकांक < (_this->अङ्कः_displays - 1)) {
        SDL_memmove(&_this->displays[display_सूचकांक], &_this->displays[display_सूचकांक + 1], (_this->अङ्कः_displays - display_सूचकांक - 1) * परिमाण(_this->displays[display_सूचकांक]));
    }
    --_this->अङ्कः_displays;

    SDL_UpdateDesktopBounds();
}

SDL_DisplayID *SDL_GetDisplays(पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क i;
    SDL_DisplayID *displays;

    यदि (!_this) {
        यदि (गणनम्) {
            *गणनम् = 0;
        }

        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    displays = (SDL_DisplayID *)SDL_malloc((_this->अङ्कः_displays + 1) * परिमाण(*displays));
    यदि (displays) {
        यदि (गणनम्) {
            *गणनम् = _this->अङ्कः_displays;
        }

        प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
            displays[i] = _this->displays[i]->id;
        }
        displays[i] = 0;
    } अन्यथा {
        यदि (गणनम्) {
            *गणनम् = 0;
        }
    }
    प्रत्यागम displays;
}

SDL_VideoDisplay *SDL_GetVideoDisplay(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_सूचकांक;

    display_सूचकांक = SDL_Get_Display_सूचकांक(displayID);
    यदि (display_सूचकांक < 0) {
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->displays[display_सूचकांक];
}

स्थिर SDL_DisplayID Get_Display_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    SDL_DisplayID displayID = 0;

    // An explicit fullscreen display overrides all
    यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        displayID = गवाक्षः->current_fullscreen_बहुलकम्.displayID;
    }

    यदि (!displayID) {
        displayID = SDL_Get_Display_For_गवाक्षः_Position(गवाक्षः);
    }
    प्रत्यागम displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0);

    प्रत्यागम SDL_GetVideoDisplay(Get_Display_For_गवाक्षः(गवाक्षः));
}

SDL_DisplayID SDL_GetPrimaryDisplay(शून्य)
{
    यदि (!_this || _this->अङ्कः_displays == 0) {
        SDL_UninitializedVideo();
        प्रत्यागम 0;
    }
    प्रत्यागम _this->displays[0]->id;
}

पूर्णाङ्क SDL_Get_Display_सूचकांक(SDL_DisplayID displayID)
{
    पूर्णाङ्क display_सूचकांक;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम -1;
    }

    प्रति (display_सूचकांक = 0; display_सूचकांक < _this->अङ्कः_displays; ++display_सूचकांक) {
        यदि (displayID == _this->displays[display_सूचकांक]->id) {
            प्रत्यागम display_सूचकांक;
        }
    }
    SDL_समुच्चयः_Error("Invalid display");
    प्रत्यागम -1;
}

SDL_Display_दत्त *SDL_Get_Display_Driver_दत्त(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम display->आन्तरिकम्;
}

SDL_Display_दत्त *SDL_Get_Display_Driver_दत्त_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0);

    प्रत्यागम SDL_Get_Display_Driver_दत्त(Get_Display_For_गवाक्षः(गवाक्षः));
}

SDL_PropertiesID SDL_GetDisplayProperties(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0);

    यदि (display->props == 0) {
        display->props = SDL_CreateProperties();
    }
    प्रत्यागम display->props;
}

ध्रुव वर्ण *SDL_GetDisplayName(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम display->name;
}

bool SDL_GetDisplayBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        प्रत्यागम SDL_InvalidParamError("rect");
    }

    यदि (_this->GetDisplayBounds) {
        SDL_zerop(rect);
        यदि (_this->GetDisplayBounds(_this, display, rect)) {
            प्रत्यागम true;
        }
    }

    // Assume that the displays are left to right
    यदि (displayID == SDL_GetPrimaryDisplay()) {
        rect->x = 0;
        rect->y = 0;
    } अन्यथा {
        SDL_GetDisplayBounds(_this->displays[SDL_Get_Display_सूचकांक(displayID) - 1]->id, rect);
        rect->x += rect->w;
    }
    rect->w = display->current_बहुलकम्->w;
    rect->h = display->current_बहुलकम्->h;
    प्रत्यागम true;
}

स्थिर पूर्णाङ्क ParseDisplayUsableBoundsHint(SDL_Rect *rect)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_DISPLAY_USABLE_BOUNDS);
    प्रत्यागम hint && (SDL_sscanf(hint, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->w, &rect->h) == 4);
}

bool SDL_GetDisplayUsableBounds(SDL_DisplayID displayID, SDL_Rect *rect)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, false);

    CHECK_PARAM(!rect) {
        प्रत्यागम SDL_InvalidParamError("rect");
    }

    यदि (displayID == SDL_GetPrimaryDisplay() && ParseDisplayUsableBoundsHint(rect)) {
        प्रत्यागम true;
    }

    यदि (_this->GetDisplayUsableBounds) {
        SDL_zerop(rect);
        यदि (_this->GetDisplayUsableBounds(_this, display, rect)) {
            प्रत्यागम true;
        }
    }

    // Oh well, just give the entire display bounds.
    प्रत्यागम SDL_GetDisplayBounds(displayID, rect);
}

SDL_DisplayOrientation SDL_GetNaturalDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    यदि (display->natural_orientation != SDL_ORIENTATION_UNKNOWN) {
        प्रत्यागम display->natural_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        प्रत्यागम SDL_ORIENTATION_LANDSCAPE;
    }
}

SDL_DisplayOrientation SDL_GetCurrentDisplayOrientation(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, SDL_ORIENTATION_UNKNOWN);

    यदि (display->current_orientation != SDL_ORIENTATION_UNKNOWN) {
        प्रत्यागम display->current_orientation;
    } अन्यथा {
        // Default to landscape if the driver hasn't set it
        प्रत्यागम SDL_ORIENTATION_LANDSCAPE;
    }
}

शून्य SDL_समुच्चयः_Display_Content_Scale(SDL_VideoDisplay *display, भिन्न scale)
{
    यदि (scale != display->content_scale) {
        SDL_गवाक्षः *गवाक्षः;

        display->content_scale = scale;
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CONTENT_SCALE_परिवर्तितम्, 0, 0);

        // Check the windows on this display
        प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            यदि (display->id == गवाक्षः->displayID) {
                SDL_Check_गवाक्षः_Display_Scale_परिवर्तितम्(गवाक्षः);
            }
        }
    }
}

भिन्न SDL_GetDisplayContentScale(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, 0.0f);

    प्रत्यागम display->content_scale;
}

शून्य SDL_समुच्चयः_गवाक्षः_HDRProperties(SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_HDROutputProperties *HDR, bool send_event)
{
    ध्रुव SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };

    यदि (गवाक्षः->HDR.HDR_headroom != HDR_clamped.HDR_headroom || गवाक्षः->HDR.SDR_white_level != HDR_clamped.SDR_white_level) {
        SDL_PropertiesID गवाक्षः_props = SDL_Get_गवाक्षः_Properties(गवाक्षः);

        SDL_समुच्चयः_Float_Property(गवाक्षः_props, SDL_PROP_गवाक्षः_HDR_HEADROOM_FLOAT, HDR_clamped.HDR_headroom);
        SDL_समुच्चयः_Float_Property(गवाक्षः_props, SDL_PROP_गवाक्षः_SDR_WHITE_LEVEL_FLOAT, HDR_clamped.SDR_white_level);
        SDL_समुच्चयः_Boolean_Property(गवाक्षः_props, SDL_PROP_गवाक्षः_HDR_ENABLED_BOOLEAN, HDR_clamped.HDR_headroom > 1.0f);
        SDL_copyp(&गवाक्षः->HDR, &HDR_clamped);

        यदि (send_event) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_HDR_STATE_परिवर्तितम्, HDR_clamped.HDR_headroom > 1.0f, 0);
        }
    }
}

शून्य SDL_समुच्चयः_Display_HDRProperties(SDL_VideoDisplay *display, ध्रुव SDL_HDROutputProperties *HDR)
{
    ध्रुव SDL_HDROutputProperties HDR_clamped = {
        SDL_max(HDR->SDR_white_level, 1.0f),
        SDL_max(HDR->HDR_headroom, 1.0f)
    };
    ध्रुव bool परिवर्तितम् = HDR_clamped.SDR_white_level != display->HDR.SDR_white_level ||
                         HDR_clamped.HDR_headroom != display->HDR.HDR_headroom;

    SDL_copyp(&display->HDR, &HDR_clamped);

	यदि (परिवर्तितम्) {
		SDL_समुच्चयः_Boolean_Property(display->props, SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, display->HDR.HDR_headroom > 1.0f);
	}

    यदि (परिवर्तितम् && !SDL_DriverSendsHDRChanges(_this)) {
        प्रति (SDL_गवाक्षः *w = display->device->windows; w; w = w->अग्र) {
            यदि (Get_Display_For_गवाक्षः(w) == display->id) {
                SDL_समुच्चयः_गवाक्षः_HDRProperties(w, &display->HDR, true);
            }
        }
    }
}

स्थिर शून्य SDL_UpdateFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    यदि (display->अङ्कः_fullscreen_modes == 0 && _this->GetDisplayModes) {
        _this->GetDisplayModes(_this, display);
    }
}

// Return the matching mode as a pointer into our current mode list
स्थिर ध्रुव SDL_Display_बहुलकम् *SDL_Get_Fullscreen_बहुलकम्_मेलनम्(ध्रुव SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_VideoDisplay *display;
    SDL_Display_बहुलकम् fullscreen_बहुलकम्;

    यदि (बहुलकम्->w <= 0 || बहुलकम्->h <= 0) {
        // Use the desktop mode
        प्रत्यागम रिक्त;
    }

    SDL_memcpy(&fullscreen_बहुलकम्, बहुलकम्, परिमाण(fullscreen_बहुलकम्));
    यदि (fullscreen_बहुलकम्.displayID == 0) {
        fullscreen_बहुलकम्.displayID = SDL_GetPrimaryDisplay();
    }
    SDL_Finalize_Display_बहुलकम्(&fullscreen_बहुलकम्);

    बहुलकम् = रिक्त;

    display = SDL_GetVideoDisplay(fullscreen_बहुलकम्.displayID);
    यदि (display) {
        SDL_UpdateFullscreenDisplayModes(display);

        // Search for an exact match
        यदि (!बहुलकम्) {
            प्रति (पूर्णाङ्क i = 0; i < display->अङ्कः_fullscreen_modes; ++i) {
                यदि (SDL_memcmp(&fullscreen_बहुलकम्, &display->fullscreen_modes[i], परिमाण(fullscreen_बहुलकम्)) == 0) {
                    बहुलकम् = &display->fullscreen_modes[i];
                    भङ्ग;
                }
            }
        }

        // Search for a mode with the same characteristics
        यदि (!बहुलकम्) {
            प्रति (पूर्णाङ्क i = 0; i < display->अङ्कः_fullscreen_modes; ++i) {
                यदि (cmpmodes(&fullscreen_बहुलकम्, &display->fullscreen_modes[i]) == 0) {
                    बहुलकम् = &display->fullscreen_modes[i];
                    भङ्ग;
                }
            }
        }
    }
    प्रत्यागम बहुलकम्;
}

bool SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(SDL_VideoDisplay *display, ध्रुव SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Display_बहुलकम् *modes;
    SDL_Display_बहुलकम् new_बहुलकम्;
    पूर्णाङ्क i, nmodes;

    // Finalize the mode for the display
    SDL_memcpy(&new_बहुलकम्, बहुलकम्, परिमाण(new_बहुलकम्));
    new_बहुलकम्.displayID = display->id;
    SDL_Finalize_Display_बहुलकम्(&new_बहुलकम्);

    // Make sure we don't already have the mode in the list
    modes = display->fullscreen_modes;
    nmodes = display->अङ्कः_fullscreen_modes;
    प्रति (i = 0; i < nmodes; ++i) {
        यदि (cmpmodes(&new_बहुलकम्, &modes[i]) == 0) {
            प्रत्यागम false;
        }
    }

    // Go ahead and add the new mode
    यदि (nmodes == display->max_fullscreen_modes) {
        modes = (SDL_Display_बहुलकम् *)SDL_malloc((display->max_fullscreen_modes + 32) * परिमाण(*modes));
        यदि (!modes) {
            प्रत्यागम false;
        }

        यदि (display->fullscreen_modes) {
            // Copy the list and update the current mode pointer, if necessary.
            SDL_memcpy(modes, display->fullscreen_modes, nmodes * परिमाण(*modes));
            प्रति (i = 0; i < nmodes; ++i) {
                यदि (display->current_बहुलकम् == &display->fullscreen_modes[i]) {
                    display->current_बहुलकम् = &modes[i];
                }
            }

            SDL_free(display->fullscreen_modes);
        }

        display->fullscreen_modes = modes;
        display->max_fullscreen_modes += 32;
    }
    SDL_memcpy(&modes[display->अङ्कः_fullscreen_modes++], &new_बहुलकम्, परिमाण(new_बहुलकम्));

    // Re-sort video modes
    SDL_qsort(display->fullscreen_modes, display->अङ्कः_fullscreen_modes,
              परिमाण(SDL_Display_बहुलकम्), cmpmodes);

    प्रत्यागम true;
}

शून्य SDL_ResetFullscreenDisplayModes(SDL_VideoDisplay *display)
{
    पूर्णाङ्क i;

    प्रति (i = display->अङ्कः_fullscreen_modes; i--;) {
        SDL_free(display->fullscreen_modes[i].आन्तरिकम्);
        display->fullscreen_modes[i].आन्तरिकम् = रिक्त;
    }
    SDL_free(display->fullscreen_modes);
    display->fullscreen_modes = रिक्त;
    display->अङ्कः_fullscreen_modes = 0;
    display->max_fullscreen_modes = 0;
    display->current_बहुलकम् = &display->desktop_बहुलकम्;
}

SDL_Display_बहुलकम् **SDL_GetFullscreenDisplayModes(SDL_DisplayID displayID, पूर्णाङ्क *गणनम्)
{
    पूर्णाङ्क i;
    पूर्णाङ्क अङ्कः_modes;
    SDL_Display_बहुलकम् **परिणाम;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    यदि (गणनम्) {
        *गणनम् = 0;
    }

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    SDL_UpdateFullscreenDisplayModes(display);

    अङ्कः_modes = display->अङ्कः_fullscreen_modes;
    परिणाम = (SDL_Display_बहुलकम् **)SDL_malloc((अङ्कः_modes + 1) * परिमाण(*परिणाम) + अङ्कः_modes * परिमाण(**परिणाम));
    यदि (परिणाम) {
        SDL_Display_बहुलकम् *modes = (SDL_Display_बहुलकम् *)((Uint8 *)परिणाम + ((अङ्कः_modes + 1) * परिमाण(*परिणाम)));
        यदि (अङ्कः_modes) {
            SDL_memcpy(modes, display->fullscreen_modes, अङ्कः_modes * परिमाण(*modes));
        }
        प्रति (i = 0; i < अङ्कः_modes; ++i) {
            परिणाम[i] = modes++;
        }
        परिणाम[i] = रिक्त;

        यदि (गणनम्) {
            *गणनम् = अङ्कः_modes;
        }
    } अन्यथा {
        यदि (गणनम्) {
            *गणनम् = 0;
        }
    }
    प्रत्यागम परिणाम;
}

bool SDL_Get_Closest_Fullscreen_Display_बहुलकम्(SDL_DisplayID displayID, पूर्णाङ्क w, पूर्णाङ्क h, भिन्न refresh_दरः, bool include_उच्चः_density_modes, SDL_Display_बहुलकम् *परिणाम)
{
    CHECK_PARAM(!परिणाम) {
        प्रत्यागम SDL_InvalidParamError("closest"); // Parameter `result` is called `closest` in the header.
    }

    ध्रुव SDL_Display_बहुलकम् *बहुलकम्, *closest = रिक्त;
    भिन्न aspect_अनुपातः;
    पूर्णाङ्क i;
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    SDL_zerop(परिणाम);

    CHECK_DISPLAY_MAGIC(display, false);

    यदि (h > 0) {
        aspect_अनुपातः = (भिन्न)w / h;
    } अन्यथा {
        aspect_अनुपातः = 1.0f;
    }

    यदि (refresh_दरः == 0.0f) {
        refresh_दरः = display->desktop_बहुलकम्.refresh_दरः;
    }

    SDL_UpdateFullscreenDisplayModes(display);

    प्रति (i = 0; i < display->अङ्कः_fullscreen_modes; ++i) {
        बहुलकम् = &display->fullscreen_modes[i];

        यदि (w > बहुलकम्->w) {
            // Out of sorted modes large enough here
            भङ्ग;
        }
        यदि (h > बहुलकम्->h) {
            /* Wider, but not tall enough, due to a different aspect ratio.
             * This mode must be skipped, but closer modes may still follow */
            अनुवर्त;
        }
        यदि (बहुलकम्->pixel_density > 1.0f && !include_उच्चः_density_modes) {
            अनुवर्त;
        }
        यदि (closest) {
            भिन्न current_aspect_अनुपातः = (भिन्न)बहुलकम्->w / बहुलकम्->h;
            भिन्न closest_aspect_अनुपातः = (भिन्न)closest->w / closest->h;
            यदि (SDL_fabsf(aspect_अनुपातः - closest_aspect_अनुपातः) < SDL_fabsf(aspect_अनुपातः - current_aspect_अनुपातः)) {
                // The mode we already found has a better aspect ratio match
                अनुवर्त;
            }

            यदि (बहुलकम्->w == closest->w && बहुलकम्->h == closest->h) {
                यदि (SDL_fabsf(closest->refresh_दरः - refresh_दरः) < SDL_fabsf(बहुलकम्->refresh_दरः - refresh_दरः)) {
                    /* We already found a mode and the new mode is further from our
                     * refresh rate target */
                    अनुवर्त;
                }
                यदि (SDL_BYTESPERPIXEL(closest->format) > SDL_BYTESPERPIXEL(बहुलकम्->format)) {
                    // Prefer the highest color depth
                    अनुवर्त;
                }
            }
        }

        closest = बहुलकम्;
    }
    यदि (!closest) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't find any matching video modes");
    }

    SDL_copyp(परिणाम, closest);

    प्रत्यागम true;
}

स्थिर bool Display_बहुलकम्_परिवर्तितम्(ध्रुव SDL_Display_बहुलकम् *old_बहुलकम्, ध्रुव SDL_Display_बहुलकम् *new_बहुलकम्)
{
    प्रत्यागम ((old_बहुलकम्->displayID && old_बहुलकम्->displayID != new_बहुलकम्->displayID) ||
            (old_बहुलकम्->format && old_बहुलकम्->format != new_बहुलकम्->format) ||
            (old_बहुलकम्->w && old_बहुलकम्->h && (old_बहुलकम्->w != new_बहुलकम्->w ||old_बहुलकम्->h != new_बहुलकम्->h)) ||
            (old_बहुलकम्->pixel_density != 0.0f && old_बहुलकम्->pixel_density != new_बहुलकम्->pixel_density) ||
            (old_बहुलकम्->refresh_दरः != 0.0f && old_बहुलकम्->refresh_दरः != new_बहुलकम्->refresh_दरः));
}

शून्य SDL_समुच्चयः_Desktop_Display_बहुलकम्(SDL_VideoDisplay *display, ध्रुव SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Display_बहुलकम् चरमः_बहुलकम्;

    यदि (display->fullscreen_सक्रिय) {
        // This is a temporary mode change, don't save the desktop mode
        प्रत्यागम;
    }

    SDL_copyp(&चरमः_बहुलकम्, &display->desktop_बहुलकम्);

    SDL_free(display->desktop_बहुलकम्.आन्तरिकम्);
    SDL_copyp(&display->desktop_बहुलकम्, बहुलकम्);
    display->desktop_बहुलकम्.displayID = display->id;
    SDL_Finalize_Display_बहुलकम्(&display->desktop_बहुलकम्);

    यदि (Display_बहुलकम्_परिवर्तितम्(&चरमः_बहुलकम्, &display->desktop_बहुलकम्)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_DESKTOP_बहुलकम्_परिवर्तितम्, बहुलकम्->w, बहुलकम्->h);
        यदि (display->current_बहुलकम् == &display->desktop_बहुलकम्) {
            SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_बहुलकम्_परिवर्तितम्, बहुलकम्->w, बहुलकम्->h);
        }
    }
}

ध्रुव SDL_Display_बहुलकम् *SDL_Get_Desktop_Display_बहुलकम्(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम &display->desktop_बहुलकम्;
}

शून्य SDL_समुच्चयः_Current_Display_बहुलकम्(SDL_VideoDisplay *display, ध्रुव SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Display_बहुलकम् चरमः_बहुलकम्;

    यदि (display->current_बहुलकम्) {
        SDL_copyp(&चरमः_बहुलकम्, display->current_बहुलकम्);
    } अन्यथा {
        SDL_zero(चरमः_बहुलकम्);
    }

    display->current_बहुलकम् = बहुलकम्;

    यदि (Display_बहुलकम्_परिवर्तितम्(&चरमः_बहुलकम्, बहुलकम्)) {
        SDL_SendDisplayEvent(display, SDL_EVENT_DISPLAY_CURRENT_बहुलकम्_परिवर्तितम्, बहुलकम्->w, बहुलकम्->h);
    }
}

ध्रुव SDL_Display_बहुलकम् *SDL_Get_Current_Display_बहुलकम्(SDL_DisplayID displayID)
{
    SDL_VideoDisplay *display = SDL_GetVideoDisplay(displayID);

    CHECK_DISPLAY_MAGIC(display, रिक्त);

    प्रत्यागम display->current_बहुलकम्;
}

bool SDL_समुच्चयः_Display_बहुलकम्_For_Display(SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    /* Mode switching is being emulated per-window; nothing to do and cannot fail,
     * except for XWayland, which still needs the actual mode setting call since
     * it's emulated via the XRandR interface.
     */
    यदि (SDL_बहुलकम्_Switching_Emulated(_this) && SDL_strcmp(_this->name, "x11") != 0) {
        प्रत्यागम true;
    }

    यदि (!बहुलकम्) {
        बहुलकम् = &display->desktop_बहुलकम्;
    }

    // On RISC OS, it's necessary to switch from the desktop to single-tasking
    // fullscreen so that it can handle switching back to the desktop correctly.
#यदि_अपरिभाषितम् SDL_PLATFORM_RISCOS
    यदि (बहुलकम् == display->current_बहुलकम्) {
        प्रत्यागम true;
    }
#यदि_अन्तः

    // Actually change the display mode
    यदि (_this->समुच्चयः_Display_बहुलकम्) {
        bool परिणाम;

        _this->setting_display_बहुलकम् = true;
        परिणाम = _this->समुच्चयः_Display_बहुलकम्(_this, display, बहुलकम्);
        _this->setting_display_बहुलकम् = false;
        यदि (!परिणाम) {
            प्रत्यागम false;
        }
    }

    SDL_समुच्चयः_Current_Display_बहुलकम्(display, बहुलकम्);

    प्रत्यागम true;
}

/**
 * If x, y are outside of rect, snaps them to the closest point inside rect
 * (between rect->x, rect->y, inclusive, and rect->x + w, rect->y + h, exclusive)
 */
स्थिर शून्य SDL_GetClosestPointOnRect(ध्रुव SDL_Rect *rect, SDL_Point *point)
{
    ध्रुव पूर्णाङ्क दक्षिणः = rect->x + rect->w - 1;
    ध्रुव पूर्णाङ्क bottom = rect->y + rect->h - 1;

    यदि (point->x < rect->x) {
        point->x = rect->x;
    } अन्यथा यदि (point->x > दक्षिणः) {
        point->x = दक्षिणः;
    }

    यदि (point->y < rect->y) {
        point->y = rect->y;
    } अन्यथा यदि (point->y > bottom) {
        point->y = bottom;
    }
}

स्थिर SDL_DisplayID GetDisplayForRect(पूर्णाङ्क x, पूर्णाङ्क y, पूर्णाङ्क w, पूर्णाङ्क h)
{
    पूर्णाङ्क i, dist;
    SDL_DisplayID closest = 0;
    पूर्णाङ्क closest_dist = 0x7FFFFFFF;
    SDL_Point closest_point_on_display;
    SDL_Point delta;
    SDL_Point center;
    center.x = x + w / 2;
    center.y = y + h / 2;

    यदि (_this) {
        प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];
            SDL_Rect display_rect;
            SDL_GetDisplayBounds(display->id, &display_rect);

            // Check if the window is fully enclosed
            यदि (SDL_GetRectEnclosingPoints(&center, 1, &display_rect, रिक्त)) {
                प्रत्यागम display->id;
            }

            // Snap window center to the display rect
            closest_point_on_display = center;
            SDL_GetClosestPointOnRect(&display_rect, &closest_point_on_display);

            delta.x = center.x - closest_point_on_display.x;
            delta.y = center.y - closest_point_on_display.y;
            dist = (delta.x * delta.x + delta.y * delta.y);
            यदि (dist < closest_dist) {
                closest = display->id;
                closest_dist = dist;
            }
        }
    }

    यदि (closest == 0) {
        SDL_समुच्चयः_Error("Couldn't find any displays");
    }

    प्रत्यागम closest;
}

शून्य SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क rel_x, पूर्णाङ्क rel_y, पूर्णाङ्क *abs_x, पूर्णाङ्क *abs_y)
{
    SDL_गवाक्षः *w;

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        // Calculate the total offset of the popup from the parents
        प्रति (w = गवाक्षः->parent; w; w = w->parent) {
            rel_x += w->x;
            rel_y += w->y;

            यदि (!SDL_गवाक्षः_IS_POPUP(w)) {
                भङ्ग;
            }
        }
    }

    यदि (abs_x) {
        *abs_x = rel_x;
    }
    यदि (abs_y) {
        *abs_y = rel_y;
    }
}

शून्य SDL_Global_गन्तव्यम्_Relative_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क abs_x, पूर्णाङ्क abs_y, पूर्णाङ्क *rel_x, पूर्णाङ्क *rel_y)
{
    SDL_गवाक्षः *w;

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        // Convert absolute window coordinates to relative for a popup
        प्रति (w = गवाक्षः->parent; w; w = w->parent) {
            abs_x -= w->x;
            abs_y -= w->y;

            यदि (!SDL_गवाक्षः_IS_POPUP(w)) {
                भङ्ग;
            }
        }
    }

    यदि (rel_x) {
        *rel_x = abs_x;
    }
    यदि (rel_y) {
        *rel_y = abs_y;
    }
}

SDL_DisplayID SDL_GetDisplayForPoint(ध्रुव SDL_Point *point)
{
    CHECK_PARAM(!point) {
        SDL_InvalidParamError("point");
        प्रत्यागम 0;
    }

    प्रत्यागम GetDisplayForRect(point->x, point->y, 1, 1);
}

SDL_DisplayID SDL_GetDisplayForRect(ध्रुव SDL_Rect *rect)
{
    CHECK_PARAM(!rect) {
        SDL_InvalidParamError("rect");
        प्रत्यागम 0;
    }

    प्रत्यागम GetDisplayForRect(rect->x, rect->y, rect->w, rect->h);
}

स्थिर SDL_DisplayID GetDisplayAtOrigin(पूर्णाङ्क x, पूर्णाङ्क y)
{
    प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
        SDL_Rect rect;
        ध्रुव SDL_DisplayID cur_id = _this->displays[i]->id;
        यदि (SDL_GetDisplayBounds(cur_id, &rect)) {
            यदि (x == rect.x && y == rect.y) {
                प्रत्यागम cur_id;
            }
        }
    }

    प्रत्यागम 0;
}

SDL_DisplayID SDL_Get_Display_For_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः)
{
    पूर्णाङ्क x, y;
    SDL_DisplayID displayID = 0;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0);

    यदि (_this->Get_Display_For_गवाक्षः) {
        displayID = _this->Get_Display_For_गवाक्षः(_this, गवाक्षः);
    }

    /* A backend implementation may fail to get a display for the window
     * (for example if the window is off-screen), but other code may expect it
     * to succeed in that situation, so we fall back to a generic position-
     * based implementation in that case. */
    SDL_Relative_गन्तव्यम्_Global_For_गवाक्षः(गवाक्षः, गवाक्षः->x, गवाक्षः->y, &x, &y);

    यदि (!displayID) {
        /* Fullscreen windows may be larger than the display if they were moved between differently sized
         * displays and the new position was received before the new size or vice versa. Using the center
         * of the window rect in this case can report the wrong display, so use the origin.
         */
        यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
            displayID = GetDisplayForRect(x, y, 1, 1);
        } अन्यथा {
            displayID = GetDisplayForRect(x, y, गवाक्षः->w, गवाक्षः->h);
        }
    }
    यदि (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    प्रत्यागम displayID;
}

SDL_VideoDisplay *SDL_Get_Video_Display_For_Fullscreen_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    SDL_DisplayID displayID = 0;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, रिक्त);

    // An explicit fullscreen display overrides all
    यदि (गवाक्षः->current_fullscreen_बहुलकम्.displayID) {
        displayID = गवाक्षः->current_fullscreen_बहुलकम्.displayID;
    }

    /* This is used to handle the very common pattern of SDL_SetWindowPosition()
     * followed immediately by SDL_SetWindowFullscreen() to make the window fullscreen
     * desktop on a specific display. If the backend doesn't support changing the
     * window position, or an async window manager hasn't yet actually moved the window,
     * the current position won't be updated at the time of the fullscreen call.
     */
    यदि (!displayID) {
        displayID = गवाक्षः->pending_displayID;
    }
    यदि (!displayID) {
        // Use the pending position and dimensions, if available, otherwise, use the current.
        ध्रुव पूर्णाङ्क x = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.x : गवाक्षः->x;
        ध्रुव पूर्णाङ्क y = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.y : गवाक्षः->y;
        ध्रुव पूर्णाङ्क w = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : गवाक्षः->w;
        ध्रुव पूर्णाङ्क h = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : गवाक्षः->h;

        // Check if the window is exactly at the origin of a display. Otherwise, fall back to the generic check.
        displayID = GetDisplayAtOrigin(x, y);
        यदि (!displayID) {
            displayID = GetDisplayForRect(x, y, w, h);
        }
    }
    यदि (!displayID) {
        // Use the primary display for a window if we can't find it anywhere else
        displayID = SDL_GetPrimaryDisplay();
    }
    प्रत्यागम SDL_GetVideoDisplay(displayID);
}

#परिभाषय SDL_PROP_SDL2_COMPAT_गवाक्षः_PREFERRED_FULLSCREEN_DISPLAY "sdl2-compat.window.preferred_fullscreen_display"

SDL_DisplayID SDL_Get_Display_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0);

    /* sdl2-compat calls this function to get a display on which to make the window fullscreen,
     * so pass it the preferred fullscreen display ID in a property.
     */
    SDL_PropertiesID गवाक्षः_props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    SDL_VideoDisplay *fs_display = SDL_Get_Video_Display_For_Fullscreen_गवाक्षः(गवाक्षः);
    यदि (fs_display) {
        SDL_समुच्चयः_सङ्ख्या_Property(गवाक्षः_props, SDL_PROP_SDL2_COMPAT_गवाक्षः_PREFERRED_FULLSCREEN_DISPLAY, fs_display->id);
    } अन्यथा {
        SDL_ClearProperty(गवाक्षः_props, SDL_PROP_SDL2_COMPAT_गवाक्षः_PREFERRED_FULLSCREEN_DISPLAY);
    }

    प्रत्यागम Get_Display_For_गवाक्षः(गवाक्षः);
}

स्थिर शून्य SDL_Check_गवाक्षः_Display_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः)
{
    यदि (SDL_SendsDisplayChanges(_this)) {
        प्रत्यागम;
    }

    SDL_DisplayID displayID = SDL_Get_Display_For_गवाक्षः_Position(गवाक्षः);

    यदि (displayID != गवाक्षः->displayID) {
        // See if we are fully committed to the new display
        // 80% is about the right value, tested with 350% scale on the left monitor and 100% scale on the right
        SDL_Rect old_bounds, new_bounds;
        SDL_Rect गवाक्षः_rect;
        SDL_Rect old_overlap, new_overlap;

        यदि (SDL_GetDisplayBounds(गवाक्षः->displayID, &old_bounds) &&
            SDL_GetDisplayBounds(displayID, &new_bounds)) {
            गवाक्षः_rect.x = गवाक्षः->x;
            गवाक्षः_rect.y = गवाक्षः->y;
            गवाक्षः_rect.w = गवाक्षः->w;
            गवाक्षः_rect.h = गवाक्षः->h;

            यदि (SDL_GetRectIntersection(&old_bounds, &गवाक्षः_rect, &old_overlap) &&
                SDL_GetRectIntersection(&new_bounds, &गवाक्षः_rect, &new_overlap)) {
                पूर्णाङ्क old_area = old_overlap.w * old_overlap.h;
                पूर्णाङ्क new_area = new_overlap.w * new_overlap.h;
                भिन्न new_overlap_अनुपातः = (new_area / ((भिन्न)old_area + new_area));
                यदि (new_overlap_अनुपातः < 0.80) {
                    प्रत्यागम;
                }
            }
        }
    }

    यदि (displayID != गवाक्षः->displayID) {
        पूर्णाङ्क i, display_सूचकांक;

        // Sanity check our fullscreen windows
        display_सूचकांक = SDL_Get_Display_सूचकांक(displayID);
        प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
            SDL_VideoDisplay *display = _this->displays[i];

            यदि (display->fullscreen_गवाक्षः == गवाक्षः) {
                यदि (display_सूचकांक != i) {
                    यदि (display_सूचकांक < 0) {
                        display_सूचकांक = i;
                    } अन्यथा {
                        SDL_VideoDisplay *new_display = _this->displays[display_सूचकांक];

                        // The window was moved to a different display
                        यदि (new_display->fullscreen_गवाक्षः &&
                            new_display->fullscreen_गवाक्षः != गवाक्षः) {
                            // Uh oh, there's already a fullscreen window here; minimize it
                            SDL_Minimize_गवाक्षः(new_display->fullscreen_गवाक्षः);
                        }
                        new_display->fullscreen_गवाक्षः = गवाक्षः;
                        display->fullscreen_गवाक्षः = रिक्त;
                    }
                }
                भङ्ग;
            }
        }

        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_DISPLAY_परिवर्तितम्, (पूर्णाङ्क)displayID, 0);
    }
}

भिन्न SDL_Get_गवाक्षः_Pixel_Density(SDL_गवाक्षः *गवाक्षः)
{
    पूर्णाङ्क गवाक्षः_w, गवाक्षः_h, pixel_w, pixel_h;
    भिन्न pixel_density = 1.0f;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0.0f);

    यदि (SDL_Get_गवाक्षः_आकार(गवाक्षः, &गवाक्षः_w, &गवाक्षः_h) &&
        SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &pixel_w, &pixel_h)) {
        pixel_density = (भिन्न)pixel_w / गवाक्षः_w;
    }
    प्रत्यागम pixel_density;
}

भिन्न SDL_Get_गवाक्षः_Display_Scale(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0.0f);

    प्रत्यागम गवाक्षः->display_scale;
}

स्थिर शून्य SDL_Check_गवाक्षः_Display_Scale_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः)
{
    भिन्न display_scale;

    यदि (_this->Get_गवाक्षः_Content_Scale) {
        display_scale = _this->Get_गवाक्षः_Content_Scale(_this, गवाक्षः);
    } अन्यथा {
        ध्रुव भिन्न pixel_density = SDL_Get_गवाक्षः_Pixel_Density(गवाक्षः);
        ध्रुव भिन्न content_scale = SDL_GetDisplayContentScale(गवाक्षः->displayID);

        display_scale = pixel_density * content_scale;
    }

    यदि (display_scale != गवाक्षः->display_scale) {
        गवाक्षः->display_scale = display_scale;
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_DISPLAY_SCALE_परिवर्तितम्, 0, 0);
    }
}

bool SDL_Update_Fullscreen_बहुलकम्(SDL_गवाक्षः *गवाक्षः, SDL_FullscreenOp fullscreen, bool commit)
{
    SDL_VideoDisplay *display = रिक्त;
    SDL_Display_बहुलकम् *बहुलकम् = रिक्त;
    पूर्णाङ्क i;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    गवाक्षः->fullscreen_exclusive = false;
    गवाक्षः->update_fullscreen_on_display_परिवर्तितम् = false;

    // If we are in the process of hiding don't go back to fullscreen
    यदि (गवाक्षः->is_destroying || गवाक्षः->is_hiding) {
        fullscreen = SDL_FULLSCREEN_OP_LEAVE;
    }

    // Get the correct display for this operation
    यदि (fullscreen) {
        display = SDL_Get_Video_Display_For_Fullscreen_गवाक्षः(गवाक्षः);
        यदि (!display) {
            // This should never happen, but it did...
            गच्छ समाप्तम्;
        }
    } अन्यथा {
        प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
            display = _this->displays[i];
            यदि (display->fullscreen_गवाक्षः == गवाक्षः) {
                भङ्ग;
            }
        }
        यदि (!display || i == _this->अङ्कः_displays) {
            // Already not fullscreen on any display
            display = रिक्त;
        }
    }

    यदि (fullscreen) {
        बहुलकम् = (SDL_Display_बहुलकम् *)SDL_Get_गवाक्षः_Fullscreen_बहुलकम्(गवाक्षः);
        यदि (बहुलकम्) {
            गवाक्षः->fullscreen_exclusive = true;
        } अन्यथा {
            // Make sure the current mode is zeroed for fullscreen desktop.
            SDL_zero(गवाक्षः->current_fullscreen_बहुलकम्);
        }
    }

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* if the window is going away and no resolution change is necessary,
       do nothing, or else we may trigger an ugly double-transition
     */
    यदि (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        यदि (गवाक्षः->is_destroying && !गवाक्षः->चरमः_fullscreen_exclusive_display) {
            गवाक्षः->fullscreen_exclusive = false;
            यदि (display) {
                display->fullscreen_गवाक्षः = रिक्त;
            }
            गच्छ समाप्तम्;
        }
        यदि (commit) {
            // If we're switching between a fullscreen Space and exclusive fullscreen, we need to get back to normal first.
            यदि (fullscreen && Cocoa_Is_गवाक्षः_अन्तर्_Fullscreen_Space(गवाक्षः) && !गवाक्षः->चरमः_fullscreen_exclusive_display && गवाक्षः->fullscreen_exclusive) {
                यदि (!Cocoa_समुच्चयः_गवाक्षः_Fullscreen_Space(गवाक्षः, false, true)) {
                    गच्छ error;
                }
            } अन्यथा यदि (fullscreen && गवाक्षः->चरमः_fullscreen_exclusive_display && !गवाक्षः->fullscreen_exclusive) {
                प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
                    SDL_VideoDisplay *चरमः_display = _this->displays[i];
                    यदि (चरमः_display->fullscreen_गवाक्षः == गवाक्षः) {
                        SDL_समुच्चयः_Display_बहुलकम्_For_Display(चरमः_display, रिक्त);
                        यदि (_this->समुच्चयः_गवाक्षः_Fullscreen) {
                            _this->समुच्चयः_गवाक्षः_Fullscreen(_this, गवाक्षः, चरमः_display, false);
                        }
                        चरमः_display->fullscreen_गवाक्षः = रिक्त;
                    }
                }
            }

            यदि (Cocoa_समुच्चयः_गवाक्षः_Fullscreen_Space(गवाक्षः, !!fullscreen, syncHint)) {
                गच्छ समाप्तम्;
            }
        }
    }
#यदि_अन्तः

    यदि (display) {
        // Restore the video mode on other displays if needed
        प्रति (i = 0; i < _this->अङ्कः_displays; ++i) {
            SDL_VideoDisplay *other = _this->displays[i];
            यदि (other != display && other->fullscreen_गवाक्षः == गवाक्षः) {
                SDL_समुच्चयः_Display_बहुलकम्_For_Display(other, रिक्त);
                other->fullscreen_गवाक्षः = रिक्त;
            }
        }
    }

    यदि (fullscreen) {
        पूर्णाङ्क बहुलकम्_w = 0, बहुलकम्_h = 0;
        bool resized = false;

        // Hide any other fullscreen window on this display
        यदि (display->fullscreen_गवाक्षः &&
            display->fullscreen_गवाक्षः != गवाक्षः) {
            SDL_Minimize_गवाक्षः(display->fullscreen_गवाक्षः);
        }

        display->fullscreen_सक्रिय = गवाक्षः->fullscreen_exclusive;

        यदि (!SDL_समुच्चयः_Display_बहुलकम्_For_Display(display, बहुलकम्)) {
            गच्छ error;
        }
        यदि (commit) {
            SDL_Fullscreen_परिणाम ret = SDL_FULLSCREEN_SUCCEEDED;
            यदि (_this->समुच्चयः_गवाक्षः_Fullscreen) {
                ret = _this->समुच्चयः_गवाक्षः_Fullscreen(_this, गवाक्षः, display, fullscreen);
            } अन्यथा {
                resized = true;
            }

            यदि (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window is fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
                    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_ENTER_FULLSCREEN, 0, 0);
                }
            } अन्यथा यदि (ret == SDL_FULLSCREEN_FAILED) {
                display->fullscreen_सक्रिय = false;
                गच्छ error;
            }
        }

        यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
            display->fullscreen_गवाक्षः = गवाक्षः;

            /* Android may not resize the window to exactly what our fullscreen mode is,
             * especially on windowed Android environments like the Chromebook or Samsung DeX.
             * Given this, we shouldn't use the mode size. Android's SetWindowFullscreen
             * will generate the window event for us with the proper final size.
             *
             * This is also unnecessary on Cocoa, Wayland, Win32, and X11 (will send SDL_EVENT_WINDOW_RESIZED).
             */
            यदि (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Rect displayRect;

                यदि (बहुलकम्) {
                    बहुलकम्_w = बहुलकम्->w;
                    बहुलकम्_h = बहुलकम्->h;
                    SDL_GetDisplayBounds(बहुलकम्->displayID, &displayRect);
                } अन्यथा {
                    बहुलकम्_w = display->desktop_बहुलकम्.w;
                    बहुलकम्_h = display->desktop_बहुलकम्.h;
                    SDL_GetDisplayBounds(display->id, &displayRect);
                }

                यदि (गवाक्षः->w != बहुलकम्_w || गवाक्षः->h != बहुलकम्_h) {
                    resized = true;
                }

                SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, displayRect.x, displayRect.y);

                यदि (resized) {
                    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, बहुलकम्_w, बहुलकम्_h);
                } अन्यथा {
                    SDL_On_गवाक्षः_Resized(गवाक्षः);
                }
            }
        }
    } अन्यथा {
        bool resized = false;

        // Restore the desktop mode
        यदि (display) {
            display->fullscreen_सक्रिय = false;

            SDL_समुच्चयः_Display_बहुलकम्_For_Display(display, रिक्त);
        }
        यदि (commit) {
            SDL_Fullscreen_परिणाम ret = SDL_FULLSCREEN_SUCCEEDED;
            यदि (_this->समुच्चयः_गवाक्षः_Fullscreen) {
                SDL_VideoDisplay *पूर्णम्_screen_display = display ? display : SDL_Get_Video_Display_For_Fullscreen_गवाक्षः(गवाक्षः);
                यदि (पूर्णम्_screen_display) {
                    ret = _this->समुच्चयः_गवाक्षः_Fullscreen(_this, गवाक्षः, पूर्णम्_screen_display, SDL_FULLSCREEN_OP_LEAVE);
                }
            } अन्यथा {
                resized = true;
            }

            यदि (ret == SDL_FULLSCREEN_SUCCEEDED) {
                // Window left fullscreen immediately upon return. If the driver hasn't already sent the event, do so now.
                यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
                    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_LEAVE_FULLSCREEN, 0, 0);
                }
            } अन्यथा यदि (ret == SDL_FULLSCREEN_FAILED) {
                गच्छ error;
            }
        }

        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
            यदि (display) {
                display->fullscreen_गवाक्षः = रिक्त;
            }

            यदि (!SDL_SendsFullscreenDimensions(_this)) {
                SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, गवाक्षः->windowed.x, गवाक्षः->windowed.y);
                यदि (resized) {
                    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, गवाक्षः->windowed.w, गवाक्षः->windowed.h);
                } अन्यथा {
                    SDL_On_गवाक्षः_Resized(गवाक्षः);
                }
            }
        }
    }

समाप्तम्:
    गवाक्षः->चरमः_fullscreen_exclusive_display = display && (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && गवाक्षः->fullscreen_exclusive ? display->id : 0;
    प्रत्यागम true;

error:
    यदि (fullscreen) {
        // Something went wrong and the window is no longer fullscreen.
        SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_LEAVE, commit);
    }
    प्रत्यागम false;
}

bool SDL_समुच्चयः_गवाक्षः_Fullscreen_बहुलकम्(SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Display_बहुलकम् *बहुलकम्)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (बहुलकम्) {
        यदि (!SDL_Get_Fullscreen_बहुलकम्_मेलनम्(बहुलकम्)) {
            प्रत्यागम SDL_समुच्चयः_Error("Invalid fullscreen display mode");
        }

        // Save the mode so we can look up the closest match later
        SDL_copyp(&गवाक्षः->requested_fullscreen_बहुलकम्, बहुलकम्);
    } अन्यथा {
        SDL_zero(गवाक्षः->requested_fullscreen_बहुलकम्);
    }

    /* Copy to the current mode now, in case an asynchronous fullscreen window request
     * is in progress. It will be overwritten if a new request is made.
     */
    SDL_copyp(&गवाक्षः->current_fullscreen_बहुलकम्, &गवाक्षः->requested_fullscreen_बहुलकम्);

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    /* If this is called while in the middle of a Cocoa fullscreen spaces transition,
     * wait until the transition has completed, or the window can wind up in a weird,
     * broken state if a mode switch occurs while in a fullscreen space.
     */
    यदि (SDL_strcmp(_this->name, "cocoa") == 0 && Cocoa_Is_गवाक्षः_अन्तर्_Fullscreen_Space_Transition(गवाक्षः)) {
        SDL_Sync_गवाक्षः(गवाक्षः);
    }
#यदि_अन्तः
    यदि (SDL_गवाक्षः_FULLSCREEN_VISIBLE(गवाक्षः)) {
        SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_UPDATE, true);
        SDL_SyncIfRequired(गवाक्षः);
    }

    प्रत्यागम true;
}

ध्रुव SDL_Display_बहुलकम् *SDL_Get_गवाक्षः_Fullscreen_बहुलकम्(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, रिक्त);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, रिक्त);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        प्रत्यागम SDL_Get_Fullscreen_बहुलकम्_मेलनम्(&गवाक्षः->current_fullscreen_बहुलकम्);
    } अन्यथा {
        प्रत्यागम SDL_Get_Fullscreen_बहुलकम्_मेलनम्(&गवाक्षः->requested_fullscreen_बहुलकम्);
    }
}

शून्य *SDL_Get_गवाक्षः_ICCProfile(SDL_गवाक्षः *गवाक्षः, size_t *आकार)
{
    यदि (!_this->Get_गवाक्षः_ICCProfile) {
        SDL_Unsupported();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->Get_गवाक्षः_ICCProfile(_this, गवाक्षः, आकार);
}

SDL_PixelFormat SDL_Get_गवाक्षः_Pixel_Format(SDL_गवाक्षः *गवाक्षः)
{
    SDL_DisplayID displayID;
    ध्रुव SDL_Display_बहुलकम् *बहुलकम्;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, SDL_PIXELFORMAT_UNKNOWN);

    displayID = Get_Display_For_गवाक्षः(गवाक्षः);
    बहुलकम् = SDL_Get_Current_Display_बहुलकम्(displayID);
    यदि (बहुलकम्) {
        प्रत्यागम बहुलकम्->format;
    } अन्यथा {
        प्रत्यागम SDL_PIXELFORMAT_UNKNOWN;
    }
}

#परिभाषय CREATE_FLAGS \
    (SDL_गवाक्षः_OPENGL | SDL_गवाक्षः_BORDERLESS | SDL_गवाक्षः_RESIZABLE | SDL_गवाक्षः_उच्चः_PIXEL_DENSITY | SDL_गवाक्षः_ALWAYS_ON_शिखरम् | SDL_गवाक्षः_POPUP_MENU | SDL_गवाक्षः_UTILITY | SDL_गवाक्षः_TOOLTIP | SDL_गवाक्षः_VULKAN | SDL_गवाक्षः_MINIMIZED | SDL_गवाक्षः_METAL | SDL_गवाक्षः_TRANSPARENT | SDL_गवाक्षः_NOT_FOCUSABLE | SDL_गवाक्षः_FILL_DOCUMENT)

स्थिर SDL_INLINE bool IsAcceptingDragAndDrop(शून्य)
{
    यदि (SDL_EventEnabled(SDL_EVENT_DROP_FILE) || SDL_EventEnabled(SDL_EVENT_DROP_TEXT)) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

// prepare a newly-created window
स्थिर SDL_INLINE शून्य PrepareDragAndDropSupport(SDL_गवाक्षः *गवाक्षः)
{
    यदि (_this->AcceptDragAndDrop) {
        _this->AcceptDragAndDrop(गवाक्षः, IsAcceptingDragAndDrop());
    }
}

// toggle d'n'd for all existing windows.
शून्य SDL_ToggleDragAndDropSupport(शून्य)
{
    यदि (_this && _this->AcceptDragAndDrop) {
        ध्रुव bool enable = IsAcceptingDragAndDrop();
        SDL_गवाक्षः *गवाक्षः;
        प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            _this->AcceptDragAndDrop(गवाक्षः, enable);
        }
    }
}

SDL_गवाक्षः ** SDLCALL SDL_GetWindows(पूर्णाङ्क *गणनम्)
{
    यदि (गणनम्) {
        *गणनम् = 0;
    }

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }

    SDL_गवाक्षः *गवाक्षः;
    पूर्णाङ्क अङ्कः_added = 0;
    पूर्णाङ्क अङ्कः_windows = 0;
    प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        ++अङ्कः_windows;
    }

    SDL_गवाक्षः **windows = (SDL_गवाक्षः **)SDL_malloc((अङ्कः_windows + 1) * परिमाण(*windows));
    यदि (!windows) {
        प्रत्यागम रिक्त;
    }

    प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
        windows[अङ्कः_added++] = गवाक्षः;
        यदि (अङ्कः_added == अङ्कः_windows) {
            // Race condition? Multi-threading not supported, ignore it
            भङ्ग;
        }
    }
    windows[अङ्कः_added] = रिक्त;

    यदि (गणनम्) {
        *गणनम् = अङ्कः_added;
    }
    प्रत्यागम windows;
}

स्थिर शून्य Apply_गवाक्षः_Flags(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags)
{
    यदि (!SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        यदि (!(flags & (SDL_गवाक्षः_MINIMIZED | SDL_गवाक्षः_MAXIMIZED))) {
            SDL_Restore_गवाक्षः(गवाक्षः);
        }
        यदि (flags & SDL_गवाक्षः_MAXIMIZED) {
            SDL_Maximize_गवाक्षः(गवाक्षः);
        }

        SDL_समुच्चयः_गवाक्षः_Fullscreen(गवाक्षः, (flags & SDL_गवाक्षः_FULLSCREEN) != 0);

        यदि (flags & SDL_गवाक्षः_MINIMIZED) {
            SDL_Minimize_गवाक्षः(गवाक्षः);
        }

        यदि (flags & SDL_गवाक्षः_MODAL) {
            SDL_समुच्चयः_गवाक्षः_Modal(गवाक्षः, true);
        }

        यदि (flags & SDL_गवाक्षः_MOUSE_GRABBED) {
            SDL_समुच्चयः_गवाक्षः_Mouse_Grab(गवाक्षः, true);
        }
        यदि (flags & SDL_गवाक्षः_KEYBOARD_GRABBED) {
            SDL_समुच्चयः_गवाक्षः_Keyboard_Grab(गवाक्षः, true);
        }
    }
}

स्थिर शून्य SDL_Finish_गवाक्षः_Creation(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags)
{
    PrepareDragAndDropSupport(गवाक्षः);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
        // Whoever has created the window has already applied whatever flags are needed
    } अन्यथा {
        Apply_गवाक्षः_Flags(गवाक्षः, flags);
        यदि (!(flags & SDL_गवाक्षः_HIDDEN)) {
            SDL_Show_गवाक्षः(गवाक्षः);
        }
    }

#यदि defined(SDL_PLATFORM_LINUX)
    यदि (!SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        // On Linux the progress state is persisted throughout multiple program runs, so reset state on window creation
        SDL_समुच्चयः_गवाक्षः_प्रगतिः_State(गवाक्षः, SDL_प्रगतिः_STATE_NONE);
        SDL_समुच्चयः_गवाक्षः_प्रगतिः_मानम्(गवाक्षः, 0.0f);
    }
#यदि_अन्तः
}

स्थिर bool SDL_ContextNotSupported(ध्रुव वर्ण *name)
{
    प्रत्यागम SDL_समुच्चयः_Error("%s support is either not configured in SDL "
                        "or not available in current SDL video driver "
                        "(%s) or platform",
                        name,
                        _this->name);
}

स्थिर bool SDL_DllNotSupported(ध्रुव वर्ण *name)
{
    प्रत्यागम SDL_समुच्चयः_Error("No dynamic %s support in current SDL video driver (%s)", name, _this->name);
}

स्थिर संरचना {
    ध्रुव वर्ण *property_name;
    SDL_गवाक्षः_Flags flag;
    bool invert_मानम्;
} SDL_गवाक्षः_Flag_Properties[] = {
    { SDL_PROP_गवाक्षः_CREATE_ALWAYS_ON_शिखरम्_BOOLEAN,      SDL_गवाक्षः_ALWAYS_ON_शिखरम्,       false },
    { SDL_PROP_गवाक्षः_CREATE_BORDERLESS_BOOLEAN,         SDL_गवाक्षः_BORDERLESS,          false },
    { SDL_PROP_गवाक्षः_CREATE_FOCUSABLE_BOOLEAN,          SDL_गवाक्षः_NOT_FOCUSABLE,       true },
    { SDL_PROP_गवाक्षः_CREATE_FULLSCREEN_BOOLEAN,         SDL_गवाक्षः_FULLSCREEN,          false },
    { SDL_PROP_गवाक्षः_CREATE_HIDDEN_BOOLEAN,             SDL_गवाक्षः_HIDDEN,              false },
    { SDL_PROP_गवाक्षः_CREATE_उच्चः_PIXEL_DENSITY_BOOLEAN, SDL_गवाक्षः_उच्चः_PIXEL_DENSITY,  false },
    { SDL_PROP_गवाक्षः_CREATE_MAXIMIZED_BOOLEAN,          SDL_गवाक्षः_MAXIMIZED,           false },
    { SDL_PROP_गवाक्षः_CREATE_MENU_BOOLEAN,               SDL_गवाक्षः_POPUP_MENU,          false },
    { SDL_PROP_गवाक्षः_CREATE_METAL_BOOLEAN,              SDL_गवाक्षः_METAL,               false },
    { SDL_PROP_गवाक्षः_CREATE_MINIMIZED_BOOLEAN,          SDL_गवाक्षः_MINIMIZED,           false },
    { SDL_PROP_गवाक्षः_CREATE_MODAL_BOOLEAN,              SDL_गवाक्षः_MODAL,               false },
    { SDL_PROP_गवाक्षः_CREATE_MOUSE_GRABBED_BOOLEAN,      SDL_गवाक्षः_MOUSE_GRABBED,       false },
    { SDL_PROP_गवाक्षः_CREATE_OPENGL_BOOLEAN,             SDL_गवाक्षः_OPENGL,              false },
    { SDL_PROP_गवाक्षः_CREATE_RESIZABLE_BOOLEAN,          SDL_गवाक्षः_RESIZABLE,           false },
    { SDL_PROP_गवाक्षः_CREATE_TRANSPARENT_BOOLEAN,        SDL_गवाक्षः_TRANSPARENT,         false },
    { SDL_PROP_गवाक्षः_CREATE_TOOLTIP_BOOLEAN,            SDL_गवाक्षः_TOOLTIP,             false },
    { SDL_PROP_गवाक्षः_CREATE_UTILITY_BOOLEAN,            SDL_गवाक्षः_UTILITY,             false },
    { SDL_PROP_गवाक्षः_CREATE_VULKAN_BOOLEAN,             SDL_गवाक्षः_VULKAN,              false }
};

स्थिर SDL_गवाक्षः_Flags SDL_Get_गवाक्षः_Flag_Properties(SDL_PropertiesID props)
{
    अचिह्नित i;
    SDL_गवाक्षः_Flags flags = (SDL_गवाक्षः_Flags)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_FLAGS_सङ्ख्या, 0);

    प्रति (i = 0; i < SDL_arraysize(SDL_गवाक्षः_Flag_Properties); ++i) {
        यदि (SDL_गवाक्षः_Flag_Properties[i].invert_मानम्) {
            यदि (!SDL_GetBooleanProperty(props, SDL_गवाक्षः_Flag_Properties[i].property_name, true)) {
                flags |= SDL_गवाक्षः_Flag_Properties[i].flag;
            }
        } अन्यथा {
            यदि (SDL_GetBooleanProperty(props, SDL_गवाक्षः_Flag_Properties[i].property_name, false)) {
                flags |= SDL_गवाक्षः_Flag_Properties[i].flag;
            }
        }
    }
    प्रत्यागम flags;
}

SDL_गवाक्षः *SDL_Create_गवाक्षः_With_Properties(SDL_PropertiesID props)
{
    SDL_गवाक्षः *गवाक्षः;
    ध्रुव वर्ण *title = SDL_GetStringProperty(props, SDL_PROP_गवाक्षः_CREATE_TITLE_STRING, रिक्त);
    पूर्णाङ्क x = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_X_सङ्ख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णाङ्क y = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_Y_सङ्ख्या, SDL_WINDOWPOS_UNDEFINED);
    पूर्णाङ्क w = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_विस्तारः_सङ्ख्या, 0);
    पूर्णाङ्क h = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_HEIGHT_सङ्ख्या, 0);
    SDL_गवाक्षः *parent = (SDL_गवाक्षः *)SDL_GetPointerProperty(props, SDL_PROP_गवाक्षः_CREATE_PARENT_POINTER, रिक्त);
    SDL_गवाक्षः_Flags flags = SDL_Get_गवाक्षः_Flag_Properties(props);
    SDL_गवाक्षः_Flags type_flags, graphics_flags;
    SDL_DisplayID displayID = 0;
    bool undefined_x = false;
    bool undefined_y = false;
    bool external_graphics_context = SDL_GetBooleanProperty(props, SDL_PROP_गवाक्षः_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, false);

    यदि (!_this) {
        // Initialize the video system if needed
        यदि (!SDL_Init(SDL_INIT_VIDEO)) {
            प्रत्यागम रिक्त;
        }

        // Make clang-tidy happy
        यदि (!_this) {
            प्रत्यागम रिक्त;
        }
    }

    यदि ((flags & SDL_गवाक्षः_MODAL) && !SDL_ObjectValid(parent, SDL_OBJECT_TYPE_गवाक्षः)) {
        SDL_समुच्चयः_Error("Modal windows must specify a parent window");
        प्रत्यागम रिक्त;
    }

    यदि ((flags & (SDL_गवाक्षः_TOOLTIP | SDL_गवाक्षः_POPUP_MENU)) != 0) {
        यदि (!(_this->device_caps & VIDEO_DEVICE_CAPS_HAS_POPUP_गवाक्षः_SUPPORT)) {
            SDL_Unsupported();
            प्रत्यागम रिक्त;
        }

        // Tooltip and popup menu window must specify a parent window
        यदि (!SDL_ObjectValid(parent, SDL_OBJECT_TYPE_गवाक्षः)) {
            SDL_समुच्चयः_Error("Tooltip and popup menu windows must specify a parent window");
            प्रत्यागम रिक्त;
        }

        // Remove invalid flags
        flags &= ~(SDL_गवाक्षः_MINIMIZED | SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_BORDERLESS);
    }

    // Ensure no more than one of these flags is set
    type_flags = flags & (SDL_गवाक्षः_UTILITY | SDL_गवाक्षः_TOOLTIP | SDL_गवाक्षः_POPUP_MENU | SDL_गवाक्षः_MODAL);
    यदि (type_flags & (type_flags - 1)) {
        SDL_समुच्चयः_Error("Conflicting window type flags specified: 0x%.8x", (अचिह्नित पूर्णाङ्क)type_flags);
        प्रत्यागम रिक्त;
    }

    // Make sure the display list is up to date for window placement
    यदि (_this->RefreshDisplays) {
        _this->RefreshDisplays(_this);
    }

    // Some platforms can't create zero-sized windows
    यदि (w < 1) {
        w = 1;
    }
    यदि (h < 1) {
        h = 1;
    }

    यदि (SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISUNDEFINED(y) ||
        SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_Rect bounds;

        यदि ((SDL_WINDOWPOS_ISUNDEFINED(x) || SDL_WINDOWPOS_ISCENTERED(x)) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा यदि ((SDL_WINDOWPOS_ISUNDEFINED(y) || SDL_WINDOWPOS_ISCENTERED(y)) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        यदि (displayID == 0 || SDL_Get_Display_सूचकांक(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        SDL_zero(bounds);
        SDL_GetDisplayUsableBounds(displayID, &bounds);
        यदि (w > bounds.w || h > bounds.h) {
            // This window is larger than the usable bounds, just center on the display
            SDL_GetDisplayBounds(displayID, &bounds);
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISUNDEFINED(x)) {
            यदि (SDL_WINDOWPOS_ISUNDEFINED(x)) {
                undefined_x = true;
            }
            x = bounds.x + (bounds.w - w) / 2;
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(y) || SDL_WINDOWPOS_ISUNDEFINED(y)) {
            यदि (SDL_WINDOWPOS_ISUNDEFINED(y)) {
                undefined_y = true;
            }
            y = bounds.y + (bounds.h - h) / 2;
        }
    }

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_गवाक्षः_OPENGL | SDL_गवाक्षः_METAL | SDL_गवाक्षः_VULKAN);
    यदि (graphics_flags & (graphics_flags - 1)) {
        SDL_समुच्चयः_Error("Conflicting window graphics flags specified: 0x%.8x", (अचिह्नित पूर्णाङ्क)graphics_flags);
        प्रत्यागम रिक्त;
    }

    // Some platforms have certain graphics backends enabled by default
    यदि (!graphics_flags && !external_graphics_context) {
        flags |= SDL_DefaultGraphicsBackends(_this);
    }

    यदि (flags & SDL_गवाक्षः_OPENGL) {
        यदि (!_this->GL_CreateContext) {
            SDL_ContextNotSupported("OpenGL");
            प्रत्यागम रिक्त;
        }
        यदि (!SDL_GL_आरोपय_Library(रिक्त)) {
            प्रत्यागम रिक्त;
        }
    }

    यदि (flags & SDL_गवाक्षः_VULKAN) {
        यदि (!_this->Vulkan_CreateSurface) {
            SDL_ContextNotSupported("Vulkan");
            प्रत्यागम रिक्त;
        }
        यदि (!SDL_Vulkan_आरोपय_Library(रिक्त)) {
            प्रत्यागम रिक्त;
        }
    }

    यदि (flags & SDL_गवाक्षः_METAL) {
        यदि (!_this->Metal_CreateView) {
            SDL_ContextNotSupported("Metal");
            प्रत्यागम रिक्त;
        }
    }

    गवाक्षः = (SDL_गवाक्षः *)SDL_calloc(1, परिमाण(*गवाक्षः));
    यदि (!गवाक्षः) {
        प्रत्यागम रिक्त;
    }
    SDL_समुच्चयः_Object_Valid(गवाक्षः, SDL_OBJECT_TYPE_गवाक्षः, true);
    गवाक्षः->id = SDL_Get_अग्र_Object_ID();
    गवाक्षः->floating.x = गवाक्षः->windowed.x = गवाक्षः->x = x;
    गवाक्षः->floating.y = गवाक्षः->windowed.y = गवाक्षः->y = y;
    गवाक्षः->floating.w = गवाक्षः->windowed.w = गवाक्षः->w = w;
    गवाक्षः->floating.h = गवाक्षः->windowed.h = गवाक्षः->h = h;
    गवाक्षः->undefined_x = undefined_x;
    गवाक्षः->undefined_y = undefined_y;
    गवाक्षः->pending_displayID = displayID;

    SDL_VideoDisplay *display = SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः);
    यदि (display) {
        SDL_समुच्चयः_गवाक्षः_HDRProperties(गवाक्षः, &display->HDR, false);
    }

    यदि (flags & SDL_गवाक्षः_FULLSCREEN || IsFullscreenOnly(_this)) {
        SDL_Rect bounds;

        SDL_GetDisplayBounds(display ? display->id : SDL_GetPrimaryDisplay(), &bounds);
        गवाक्षः->x = bounds.x;
        गवाक्षः->y = bounds.y;
        गवाक्षः->w = bounds.w;
        गवाक्षः->h = bounds.h;
        गवाक्षः->pending_flags |= SDL_गवाक्षः_FULLSCREEN;
        flags |= SDL_गवाक्षः_FULLSCREEN;
    }

    गवाक्षः->flags = ((flags & CREATE_FLAGS) | SDL_गवाक्षः_HIDDEN);
    गवाक्षः->display_scale = 1.0f;
    गवाक्षः->opacity = 1.0f;
    गवाक्षः->अग्र = _this->windows;
    गवाक्षः->is_destroying = false;
    गवाक्षः->displayID = Get_Display_For_गवाक्षः(गवाक्षः);
    गवाक्षः->external_graphics_context = external_graphics_context;
    गवाक्षः->constrain_popup = SDL_GetBooleanProperty(props, SDL_PROP_गवाक्षः_CREATE_CONSTRAIN_POPUP_BOOLEAN, true);

    यदि (!_this->समुच्चयः_गवाक्षः_Fill_Document) {
        गवाक्षः->flags &= ~SDL_गवाक्षः_FILL_DOCUMENT;  // not an error, just unsupported here, so remove the flag.
    }

    यदि (_this->windows) {
        _this->windows->पूर्व = गवाक्षः;
    }
    _this->windows = गवाक्षः;

    // Set the parent before creation.
    SDL_Update_गवाक्षः_Hierarchy(गवाक्षः, parent);

    यदि (_this->CreateSDLWindow && !_this->CreateSDLWindow(_this, गवाक्षः, props)) {
        SDL_प्रक्षिप_Error();
        SDL_Destroy_गवाक्षः(गवाक्षः);
        SDL_निष्कासय_Error();
        प्रत्यागम रिक्त;
    }

    /* Clear minimized if not on windows, only windows handles it at create rather than FinishWindowCreation,
     * but it's important or window focus will get broken on windows!
     */
#यदि !defined(SDL_PLATFORM_WINDOWS)
    यदि (गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
        गवाक्षः->flags &= ~SDL_गवाक्षः_MINIMIZED;
    }
#यदि_अन्तः

    यदि (title) {
        SDL_समुच्चयः_गवाक्षः_Title(गवाक्षः, title);
    }
    SDL_Finish_गवाक्षः_Creation(गवाक्षः, flags);

    // Make sure window pixel size is up to date
    SDL_Check_गवाक्षः_Pixel_आकार_परिवर्तितम्(गवाक्षः);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#यदि_अन्तः

    SDL_ClearError();

    प्रत्यागम गवाक्षः;
}

SDL_गवाक्षः *SDL_Create_गवाक्षः(ध्रुव वर्ण *title, पूर्णाङ्क w, पूर्णाङ्क h, SDL_गवाक्षः_Flags flags)
{
    SDL_गवाक्षः *गवाक्षः;
    SDL_PropertiesID props = SDL_CreateProperties();
    यदि (title && *title) {
        SDL_समुच्चयः_String_Property(props, SDL_PROP_गवाक्षः_CREATE_TITLE_STRING, title);
    }
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_विस्तारः_सङ्ख्या, w);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_HEIGHT_सङ्ख्या, h);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_FLAGS_सङ्ख्या, flags);
    गवाक्षः = SDL_Create_गवाक्षः_With_Properties(props);
    SDL_DestroyProperties(props);
    प्रत्यागम गवाक्षः;
}

SDL_गवाक्षः *SDL_Create_Popup_गवाक्षः(SDL_गवाक्षः *parent, पूर्णाङ्क विस्थापनम्_x, पूर्णाङ्क विस्थापनम्_y, पूर्णाङ्क w, पूर्णाङ्क h, SDL_गवाक्षः_Flags flags)
{
    SDL_गवाक्षः *गवाक्षः;
    SDL_PropertiesID props = SDL_CreateProperties();

    // Popups must specify either the tooltip or popup menu window flags
    यदि (!(flags & (SDL_गवाक्षः_TOOLTIP | SDL_गवाक्षः_POPUP_MENU))) {
        SDL_समुच्चयः_Error("Popup windows must specify either the 'SDL_WINDOW_TOOLTIP' or the 'SDL_WINDOW_POPUP_MENU' flag");
        प्रत्यागम रिक्त;
    }

    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_CREATE_PARENT_POINTER, parent);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_X_सङ्ख्या, विस्थापनम्_x);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_Y_सङ्ख्या, विस्थापनम्_y);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_विस्तारः_सङ्ख्या, w);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_HEIGHT_सङ्ख्या, h);
    SDL_समुच्चयः_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_CREATE_FLAGS_सङ्ख्या, flags);
    गवाक्षः = SDL_Create_गवाक्षः_With_Properties(props);
    SDL_DestroyProperties(props);
    प्रत्यागम गवाक्षः;
}

स्थिर bool SDL_Reconfigure_गवाक्षः_आन्तरिकम्(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags)
{
    bool loaded_opengl = false;
    bool loaded_vulkan = false;

    यदि (!_this->Reconfigure_गवाक्षः) {
        प्रत्यागम false;
    }

    ध्रुव SDL_गवाक्षः_Flags graphics_flags = flags & (SDL_गवाक्षः_OPENGL | SDL_गवाक्षः_METAL | SDL_गवाक्षः_VULKAN);
    यदि (graphics_flags & (graphics_flags - 1)) {
        प्रत्यागम SDL_समुच्चयः_Error("Conflicting window flags specified");
    }

    यदि ((flags & SDL_गवाक्षः_OPENGL) && !_this->GL_CreateContext) {
        प्रत्यागम SDL_ContextNotSupported("OpenGL");
    }
    यदि ((flags & SDL_गवाक्षः_VULKAN) && !_this->Vulkan_CreateSurface) {
        प्रत्यागम SDL_ContextNotSupported("Vulkan");
    }
    यदि ((flags & SDL_गवाक्षः_METAL) && !_this->Metal_CreateView) {
        प्रत्यागम SDL_ContextNotSupported("Metal");
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL)) {
        // Only attempt to reconfigure if the window has no existing graphics flags.
        यदि (गवाक्षः->flags & (SDL_गवाक्षः_OPENGL | SDL_गवाक्षः_METAL | SDL_गवाक्षः_VULKAN)) {
            प्रत्यागम false;
        }
    } अन्यथा {
        // Can't destroy and recreate an external window, so try our best to reconfigure it.
        यदि (!_this->Reconfigure_गवाक्षः(_this, गवाक्षः, 0)) {
            प्रत्यागम false;
        }

        // Reload the GL/Vulkan libraries in case the profile changed.
        यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
            SDL_GL_UnloadLibrary();
        }
        यदि (गवाक्षः->flags & SDL_गवाक्षः_VULKAN) {
            SDL_Vulkan_UnloadLibrary();
        }

        गवाक्षः->flags &= ~(SDL_गवाक्षः_OPENGL | SDL_गवाक्षः_METAL | SDL_गवाक्षः_VULKAN);
    }

    SDL_Destroy_गवाक्षः_Surface(गवाक्षः);

    यदि (graphics_flags & SDL_गवाक्षः_OPENGL) {
        loaded_opengl = SDL_GL_आरोपय_Library(रिक्त);
        यदि (!loaded_opengl) {
            प्रत्यागम false;
        }
    } अन्यथा यदि (graphics_flags & SDL_गवाक्षः_VULKAN) {
        loaded_vulkan = SDL_Vulkan_आरोपय_Library(रिक्त);
        यदि (!loaded_vulkan) {
            प्रत्यागम false;
        }
    }

    // Try to reconfigure the window for the requested graphics flags.
    यदि (!_this->Reconfigure_गवाक्षः(_this, गवाक्षः, graphics_flags)) {
        यदि (loaded_opengl) {
            SDL_GL_UnloadLibrary();
        }
        यदि (loaded_vulkan) {
            SDL_Vulkan_UnloadLibrary();
        }

        प्रत्यागम false;
    }

    गवाक्षः->flags |= graphics_flags;

    प्रत्यागम true;
}

bool SDL_Recreate_गवाक्षः(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags)
{
    bool loaded_opengl = false;
    bool need_gl_unload = false;
    bool need_gl_आरोपय = false;
    bool loaded_vulkan = false;
    bool need_vulkan_unload = false;
    bool need_vulkan_आरोपय = false;
    SDL_गवाक्षः_Flags graphics_flags;

    // ensure no more than one of these flags is set
    graphics_flags = flags & (SDL_गवाक्षः_OPENGL | SDL_गवाक्षः_METAL | SDL_गवाक्षः_VULKAN);
    यदि (graphics_flags & (graphics_flags - 1)) {
        प्रत्यागम SDL_समुच्चयः_Error("Conflicting window flags specified");
    }

    यदि ((flags & SDL_गवाक्षः_OPENGL) && !_this->GL_CreateContext) {
        प्रत्यागम SDL_ContextNotSupported("OpenGL");
    }
    यदि ((flags & SDL_गवाक्षः_VULKAN) && !_this->Vulkan_CreateSurface) {
        प्रत्यागम SDL_ContextNotSupported("Vulkan");
    }
    यदि ((flags & SDL_गवाक्षः_METAL) && !_this->Metal_CreateView) {
        प्रत्यागम SDL_ContextNotSupported("Metal");
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
        // Can't destroy and re-create external windows, hrm
        flags |= SDL_गवाक्षः_EXTERNAL;
    } अन्यथा {
        flags &= ~SDL_गवाक्षः_EXTERNAL;
    }

    // If this is a modal dialog, clear the modal status.
    यदि (गवाक्षः->flags & SDL_गवाक्षः_MODAL) {
        SDL_समुच्चयः_गवाक्षः_Modal(गवाक्षः, false);
    }

    // Restore video mode, etc.
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL)) {
        ध्रुव bool restore_on_show = गवाक्षः->restore_on_show;
        SDL_Hide_गवाक्षः(गवाक्षः);
        गवाक्षः->restore_on_show = restore_on_show;
    }

    // Tear down the old native window
    SDL_Destroy_गवाक्षः_Surface(गवाक्षः);

    यदि ((गवाक्षः->flags & SDL_गवाक्षः_OPENGL) != (flags & SDL_गवाक्षः_OPENGL)) {
        यदि (flags & SDL_गवाक्षः_OPENGL) {
            need_gl_आरोपय = true;
        } अन्यथा {
            need_gl_unload = true;
        }
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        need_gl_unload = true;
        need_gl_आरोपय = true;
    }

    यदि ((गवाक्षः->flags & SDL_गवाक्षः_VULKAN) != (flags & SDL_गवाक्षः_VULKAN)) {
        यदि (flags & SDL_गवाक्षः_VULKAN) {
            need_vulkan_आरोपय = true;
        } अन्यथा {
            need_vulkan_unload = true;
        }
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_VULKAN) {
        need_vulkan_unload = true;
        need_vulkan_आरोपय = true;
    }

    यदि (need_gl_unload) {
        SDL_GL_UnloadLibrary();
    }

    यदि (need_vulkan_unload) {
        SDL_Vulkan_UnloadLibrary();
    }

    यदि (_this->Destroy_गवाक्षः && !(flags & SDL_गवाक्षः_EXTERNAL)) {
        _this->Destroy_गवाक्षः(_this, गवाक्षः);
    }

    यदि (need_gl_आरोपय) {
        यदि (!SDL_GL_आरोपय_Library(रिक्त)) {
            प्रत्यागम false;
        }
        loaded_opengl = true;
    }

    यदि (need_vulkan_आरोपय) {
        यदि (!SDL_Vulkan_आरोपय_Library(रिक्त)) {
            प्रत्यागम false;
        }
        loaded_vulkan = true;
    }

    गवाक्षः->flags = ((flags & CREATE_FLAGS) | SDL_गवाक्षः_HIDDEN);
    गवाक्षः->is_destroying = false;

    यदि (_this->CreateSDLWindow && !(flags & SDL_गवाक्षः_EXTERNAL)) {
        /* Reset the window size to the original floating value, so the
         * recreated window has the proper base size.
         */
        गवाक्षः->x = गवाक्षः->windowed.x = गवाक्षः->floating.x;
        गवाक्षः->y = गवाक्षः->windowed.y = गवाक्षः->floating.y;
        गवाक्षः->w = गवाक्षः->windowed.w = गवाक्षः->floating.w;
        गवाक्षः->h = गवाक्षः->windowed.h = गवाक्षः->floating.h;

        यदि (!_this->CreateSDLWindow(_this, गवाक्षः, 0)) {
            यदि (loaded_opengl) {
                SDL_GL_UnloadLibrary();
                गवाक्षः->flags &= ~SDL_गवाक्षः_OPENGL;
            }
            यदि (loaded_vulkan) {
                SDL_Vulkan_UnloadLibrary();
                गवाक्षः->flags &= ~SDL_गवाक्षः_VULKAN;
            }
            प्रत्यागम false;
        }
    }

    यदि (flags & SDL_गवाक्षः_EXTERNAL) {
        गवाक्षः->flags |= SDL_गवाक्षः_EXTERNAL;
    }

    यदि (_this->समुच्चयः_गवाक्षः_Title && गवाक्षः->title) {
        _this->समुच्चयः_गवाक्षः_Title(_this, गवाक्षः);
    }

    यदि (_this->समुच्चयः_गवाक्षः_Icon && गवाक्षः->icon) {
        _this->समुच्चयः_गवाक्षः_Icon(_this, गवाक्षः, गवाक्षः->icon);
    }

    यदि (_this->समुच्चयः_गवाक्षः_Minimum_आकार && (गवाक्षः->min_w || गवाक्षः->min_h)) {
        _this->समुच्चयः_गवाक्षः_Minimum_आकार(_this, गवाक्षः);
    }

    यदि (_this->समुच्चयः_गवाक्षः_अधिकतमम्_आकार && (गवाक्षः->max_w || गवाक्षः->max_h)) {
        _this->समुच्चयः_गवाक्षः_अधिकतमम्_आकार(_this, गवाक्षः);
    }

    यदि (_this->समुच्चयः_गवाक्षः_Aspect_अनुपातः && (गवाक्षः->min_aspect > 0.0f || गवाक्षः->max_aspect > 0.0f)) {
        _this->समुच्चयः_गवाक्षः_Aspect_अनुपातः(_this, गवाक्षः);
    }

    यदि (गवाक्षः->लब्धम्_test) {
        _this->समुच्चयः_गवाक्षः_लब्धम्_Test(गवाक्षः, true);
    }

    SDL_Finish_गवाक्षः_Creation(गवाक्षः, flags);

    प्रत्यागम true;
}

bool SDL_Reconfigure_गवाक्षः(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags)
{
    // Try to reconfigure the window for the desired flags first, before completely destroying and recreating it.
    यदि (!SDL_Reconfigure_गवाक्षः_आन्तरिकम्(गवाक्षः, flags)) {
        प्रत्यागम SDL_Recreate_गवाक्षः(गवाक्षः, flags);
    }

    प्रत्यागम true;
}

bool SDL_HasWindows(शून्य)
{
    प्रत्यागम _this && _this->windows;
}

SDL_गवाक्षः_ID SDL_Get_गवाक्षः_ID(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0);

    प्रत्यागम गवाक्षः->id;
}

SDL_गवाक्षः *SDL_Get_गवाक्षः_From_ID(SDL_गवाक्षः_ID id)
{
    SDL_गवाक्षः *गवाक्षः;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (id) {
        प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            यदि (गवाक्षः->id == id) {
                प्रत्यागम गवाक्षः;
            }
        }
    }
    SDL_समुच्चयः_Error("Invalid window ID");
    प्रत्यागम रिक्त;
}

SDL_गवाक्षः *SDL_Get_गवाक्षः_Parent(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, रिक्त);

    प्रत्यागम गवाक्षः->parent;
}

SDL_PropertiesID SDL_Get_गवाक्षः_Properties(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0);

    यदि (गवाक्षः->props == 0) {
        गवाक्षः->props = SDL_CreateProperties();
    }
    प्रत्यागम गवाक्षः->props;
}

SDL_गवाक्षः_Flags SDL_Get_गवाक्षः_Flags(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, 0);

    प्रत्यागम गवाक्षः->flags | गवाक्षः->pending_flags;
}

bool SDL_समुच्चयः_गवाक्षः_Title(SDL_गवाक्षः *गवाक्षः, ध्रुव वर्ण *title)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (title == गवाक्षः->title) {
        प्रत्यागम true;
    }
    यदि (!title) {
        title = "";
    }
    यदि (गवाक्षः->title && SDL_strcmp(title, गवाक्षः->title) == 0) {
        प्रत्यागम true;
    }

    SDL_free(गवाक्षः->title);

    गवाक्षः->title = SDL_strdup(title);

    यदि (_this->समुच्चयः_गवाक्षः_Title) {
        _this->समुच्चयः_गवाक्षः_Title(_this, गवाक्षः);
    }
    प्रत्यागम true;
}

ध्रुव वर्ण *SDL_Get_गवाक्षः_Title(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, "");

    प्रत्यागम गवाक्षः->title ? गवाक्षः->title : "";
}

bool SDL_समुच्चयः_गवाक्षः_Icon(SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    CHECK_PARAM(!icon) {
        प्रत्यागम SDL_InvalidParamError("icon");
    }

    SDL_DestroySurface(गवाक्षः->icon);

    // Convert the icon into ARGB8888
    गवाक्षः->icon = SDL_ConvertSurface(icon, SDL_PIXELFORMAT_ARGB8888);
    यदि (!गवाक्षः->icon) {
        प्रत्यागम false;
    }

    यदि (!_this->समुच्चयः_गवाक्षः_Icon) {
        प्रत्यागम SDL_Unsupported();
    }

    प्रत्यागम _this->समुच्चयः_गवाक्षः_Icon(_this, गवाक्षः, गवाक्षः->icon);
}

bool SDL_समुच्चयः_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_DisplayID original_displayID;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    ध्रुव पूर्णाङ्क w = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : गवाक्षः->windowed.w;
    ध्रुव पूर्णाङ्क h = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : गवाक्षः->windowed.h;

    original_displayID = Get_Display_For_गवाक्षः(गवाक्षः);
    गवाक्षः->pending_displayID = 0;

    यदि (SDL_WINDOWPOS_ISUNDEFINED(x)) {
        x = गवाक्षः->windowed.x;
    }
    यदि (SDL_WINDOWPOS_ISUNDEFINED(y)) {
        y = गवाक्षः->windowed.y;
    }
    यदि (SDL_WINDOWPOS_ISCENTERED(x) || SDL_WINDOWPOS_ISCENTERED(y)) {
        SDL_DisplayID displayID = original_displayID;
        SDL_Rect bounds;

        यदि (SDL_WINDOWPOS_ISCENTERED(x) && (x & 0xFFFF)) {
            displayID = (x & 0xFFFF);
        } अन्यथा यदि (SDL_WINDOWPOS_ISCENTERED(y) && (y & 0xFFFF)) {
            displayID = (y & 0xFFFF);
        }
        यदि (displayID == 0 || SDL_Get_Display_सूचकांक(displayID) < 0) {
            displayID = SDL_GetPrimaryDisplay();
        }

        गवाक्षः->pending_displayID = displayID;

        SDL_zero(bounds);
        यदि (!SDL_GetDisplayUsableBounds(displayID, &bounds) || w > bounds.w || h > bounds.h) {
            यदि (!SDL_GetDisplayBounds(displayID, &bounds)) {
                प्रत्यागम false;
            }
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(x)) {
            x = bounds.x + (bounds.w - w) / 2;
        }
        यदि (SDL_WINDOWPOS_ISCENTERED(y)) {
            y = bounds.y + (bounds.h - h) / 2;
        }
    } अन्यथा {
        /* See if the requested window position matches the origin of any displays and set
         * the pending fullscreen display ID if it does. This needs to be set early in case
         * the window is prevented from moving to the exact origin due to struts.
         */
        गवाक्षः->pending_displayID = GetDisplayAtOrigin(x, y);
    }

    गवाक्षः->pending.x = x;
    गवाक्षः->pending.y = y;

    /* Windows are placed at the coordinates received while in fullscreen after leaving fullscreen.
     * Asynchronous backends need special handling in this case.
     */
    यदि (!_this->Sync_गवाक्षः && (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        गवाक्षः->floating.x = गवाक्षः->windowed.x = x;
        गवाक्षः->floating.y = गवाक्षः->windowed.y = y;
    }
    गवाक्षः->undefined_x = false;
    गवाक्षः->undefined_y = false;
    गवाक्षः->चरमः_position_pending = true;

    यदि (_this->समुच्चयः_गवाक्षः_Position) {
        ध्रुव bool परिणाम = _this->समुच्चयः_गवाक्षः_Position(_this, गवाक्षः);
        यदि (परिणाम) {
            SDL_SyncIfRequired(गवाक्षः);
        }
        प्रत्यागम परिणाम;
    }

    प्रत्यागम SDL_Unsupported();
}

bool SDL_Get_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *x, पूर्णाङ्क *y)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

#यदि_परिभाषितम् SDL_PLATFORM_MACOS
    // On newer MacBooks, the fullscreen window might be placed below the camera notch, so use the actual window position
    bool use_display_origin = false;
#अन्यथा
    // Fullscreen windows are always at their display's origin
    bool use_display_origin = ((गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) != 0);
#यदि_अन्तः
    यदि (use_display_origin) {
        SDL_DisplayID displayID;

        यदि (x) {
            *x = 0;
        }
        यदि (y) {
            *y = 0;
        }

        /* Find the window's monitor and update to the
           monitor offset. */
        displayID = Get_Display_For_गवाक्षः(गवाक्षः);
        यदि (displayID != 0) {
            SDL_Rect bounds;

            SDL_zero(bounds);

            SDL_GetDisplayBounds(displayID, &bounds);
            यदि (x) {
                *x = bounds.x;
            }
            यदि (y) {
                *y = bounds.y;
            }
        }
    } अन्यथा {
        ध्रुव bool use_pending = (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) && गवाक्षः->चरमः_position_pending;
        यदि (x) {
            *x = use_pending ? गवाक्षः->pending.x : गवाक्षः->x;
        }
        यदि (y) {
            *y = use_pending ? गवाक्षः->pending.y : गवाक्षः->y;
        }
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Bordered(SDL_गवाक्षः *गवाक्षः, bool bordered)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_Bordered) {
        प्रत्यागम SDL_Unsupported();
    }

    ध्रुव bool want = bordered;
    ध्रुव bool have = !(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS);
    यदि (want != have) {
        यदि (want) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_BORDERLESS;
        } अन्यथा {
            गवाक्षः->flags |= SDL_गवाक्षः_BORDERLESS;
        }
        _this->समुच्चयः_गवाक्षः_Bordered(_this, गवाक्षः, want);
    }

    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Resizable(SDL_गवाक्षः *गवाक्षः, bool resizable)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_Resizable) {
        प्रत्यागम SDL_Unsupported();
    }

    ध्रुव bool want = resizable;
    ध्रुव bool have = ((गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) != 0);
    यदि (want != have) {
        यदि (want) {
            गवाक्षः->flags |= SDL_गवाक्षः_RESIZABLE;
        } अन्यथा {
            गवाक्षः->flags &= ~SDL_गवाक्षः_RESIZABLE;
            SDL_copyp(&गवाक्षः->windowed, &गवाक्षः->floating);
        }
        _this->समुच्चयः_गवाक्षः_Resizable(_this, गवाक्षः, want);
    }

    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Always_On_शिखरम्(SDL_गवाक्षः *गवाक्षः, bool on_शिखरम्)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_Always_On_शिखरम्) {
        प्रत्यागम SDL_Unsupported();
    }

    ध्रुव bool want = on_शिखरम्;
    ध्रुव bool have = ((गवाक्षः->flags & SDL_गवाक्षः_ALWAYS_ON_शिखरम्) != 0);
    यदि (want != have) {
        यदि (want) {
            गवाक्षः->flags |= SDL_गवाक्षः_ALWAYS_ON_शिखरम्;
        } अन्यथा {
            गवाक्षः->flags &= ~SDL_गवाक्षः_ALWAYS_ON_शिखरम्;
        }
        _this->समुच्चयः_गवाक्षः_Always_On_शिखरम्(_this, गवाक्षः, want);
    }

    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_आकार(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क w, पूर्णाङ्क h)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    CHECK_PARAM(w <= 0) {
        प्रत्यागम SDL_InvalidParamError("w");
    }
    CHECK_PARAM(h <= 0) {
        प्रत्यागम SDL_InvalidParamError("h");
    }

    // It is possible for the aspect ratio constraints to not satisfy the size constraints.
    // The size constraints will override the aspect ratio constraints so we will apply the
    // the aspect ratio constraints first
    भिन्न new_aspect = w / (भिन्न)h;
    यदि (गवाक्षः->max_aspect > 0.0f && new_aspect > गवाक्षः->max_aspect) {
        w = (पूर्णाङ्क)SDL_roundf(h * गवाक्षः->max_aspect);
    } अन्यथा यदि (गवाक्षः->min_aspect > 0.0f && new_aspect < गवाक्षः->min_aspect) {
        h = (पूर्णाङ्क)SDL_roundf(w / गवाक्षः->min_aspect);
    }

    // Make sure we don't exceed any window size limits
    यदि (गवाक्षः->min_w && w < गवाक्षः->min_w) {
        w = गवाक्षः->min_w;
    }
    यदि (गवाक्षः->max_w && w > गवाक्षः->max_w) {
        w = गवाक्षः->max_w;
    }
    यदि (गवाक्षः->min_h && h < गवाक्षः->min_h) {
        h = गवाक्षः->min_h;
    }
    यदि (गवाक्षः->max_h && h > गवाक्षः->max_h) {
        h = गवाक्षः->max_h;
    }

    गवाक्षः->चरमः_आकार_pending = true;
    गवाक्षः->pending.w = w;
    गवाक्षः->pending.h = h;

    यदि (_this->समुच्चयः_गवाक्षः_आकार) {
        _this->समुच्चयः_गवाक्षः_आकार(_this, गवाक्षः);
        SDL_SyncIfRequired(गवाक्षः);
    } अन्यथा {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम true;
}

bool SDL_Get_गवाक्षः_आकार(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    यदि (w) {
        *w = गवाक्षः->w;
    }
    यदि (h) {
        *h = गवाक्षः->h;
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Aspect_अनुपातः(SDL_गवाक्षः *गवाक्षः, भिन्न min_aspect, भिन्न max_aspect)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    गवाक्षः->min_aspect = min_aspect;
    गवाक्षः->max_aspect = max_aspect;

    यदि (_this->समुच्चयः_गवाक्षः_Aspect_अनुपातः) {
        _this->समुच्चयः_गवाक्षः_Aspect_अनुपातः(_this, गवाक्षः);
    }

    // Ensure that window has the correct aspect ratio
    पूर्णाङ्क w = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : गवाक्षः->floating.w;
    पूर्णाङ्क h = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : गवाक्षः->floating.h;
    प्रत्यागम SDL_समुच्चयः_गवाक्षः_आकार(गवाक्षः, w, h);
}

bool SDL_Get_गवाक्षः_Aspect_अनुपातः(SDL_गवाक्षः *गवाक्षः, भिन्न *min_aspect, भिन्न *max_aspect)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (min_aspect) {
        *min_aspect = गवाक्षः->min_aspect;
    }
    यदि (max_aspect) {
        *max_aspect = गवाक्षः->max_aspect;
    }
    प्रत्यागम true;
}

bool SDL_Get_गवाक्षः_Borders_आकार(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः)
{
    पूर्णाङ्क dummy = 0;

    यदि (!शिखरम्) {
        शिखरम् = &dummy;
    }
    यदि (!वामः) {
        वामः = &dummy;
    }
    यदि (!दक्षिणः) {
        दक्षिणः = &dummy;
    }
    यदि (!bottom) {
        bottom = &dummy;
    }

    // Always initialize, so applications don't have to care
    *शिखरम् = *वामः = *bottom = *दक्षिणः = 0;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!_this->Get_गवाक्षः_Borders_आकार) {
        प्रत्यागम SDL_Unsupported();
    }

    प्रत्यागम _this->Get_गवाक्षः_Borders_आकार(_this, गवाक्षः, शिखरम्, वामः, bottom, दक्षिणः);
}

bool SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    पूर्णाङ्क filter;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!w) {
        w = &filter;
    }

    यदि (!h) {
        h = &filter;
    }

    यदि (_this->Get_गवाक्षः_आकार_अन्तर्_Pixels) {
        _this->Get_गवाक्षः_आकार_अन्तर्_Pixels(_this, गवाक्षः, w, h);
    } अन्यथा {
        SDL_DisplayID displayID = Get_Display_For_गवाक्षः(गवाक्षः);
        ध्रुव SDL_Display_बहुलकम् *बहुलकम्;

        SDL_Get_गवाक्षः_आकार(गवाक्षः, w, h);

        यदि ((गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && SDL_Get_गवाक्षः_Fullscreen_बहुलकम्(गवाक्षः)) {
            बहुलकम् = SDL_Get_Current_Display_बहुलकम्(displayID);
        } अन्यथा {
            बहुलकम् = SDL_Get_Desktop_Display_बहुलकम्(displayID);
        }
        यदि (बहुलकम्) {
            *w = (पूर्णाङ्क)SDL_ceilf(*w * बहुलकम्->pixel_density);
            *h = (पूर्णाङ्क)SDL_ceilf(*h * बहुलकम्->pixel_density);
        }
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क min_w, पूर्णाङ्क min_h)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_PARAM(min_w < 0) {
        प्रत्यागम SDL_InvalidParamError("min_w");
    }
    CHECK_PARAM(min_h < 0) {
        प्रत्यागम SDL_InvalidParamError("min_h");
    }

    CHECK_PARAM((गवाक्षः->max_w && min_w > गवाक्षः->max_w) || (गवाक्षः->max_h && min_h > गवाक्षः->max_h)) {
        प्रत्यागम SDL_समुच्चयः_Error("SDL_SetWindowMinimumSize(): Tried to set minimum size larger than maximum size");
    }

    गवाक्षः->min_w = min_w;
    गवाक्षः->min_h = min_h;

    यदि (_this->समुच्चयः_गवाक्षः_Minimum_आकार) {
        _this->समुच्चयः_गवाक्षः_Minimum_आकार(_this, गवाक्षः);
    }

    // Ensure that window is not smaller than minimal size
    पूर्णाङ्क w = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : गवाक्षः->floating.w;
    पूर्णाङ्क h = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : गवाक्षः->floating.h;
    प्रत्यागम SDL_समुच्चयः_गवाक्षः_आकार(गवाक्षः, w, h);
}

bool SDL_Get_गवाक्षः_Minimum_आकार(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *min_w, पूर्णाङ्क *min_h)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    यदि (min_w) {
        *min_w = गवाक्षः->min_w;
    }
    यदि (min_h) {
        *min_h = गवाक्षः->min_h;
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_अधिकतमम्_आकार(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क max_w, पूर्णाङ्क max_h)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_PARAM(max_w < 0) {
        प्रत्यागम SDL_InvalidParamError("max_w");
    }
    CHECK_PARAM(max_h < 0) {
        प्रत्यागम SDL_InvalidParamError("max_h");
    }

    यदि ((max_w && max_w < गवाक्षः->min_w) ||
        (max_h && max_h < गवाक्षः->min_h)) {
        प्रत्यागम SDL_समुच्चयः_Error("SDL_SetWindowMaximumSize(): Tried to set maximum size smaller than minimum size");
    }

    गवाक्षः->max_w = max_w;
    गवाक्षः->max_h = max_h;

    यदि (_this->समुच्चयः_गवाक्षः_अधिकतमम्_आकार) {
        _this->समुच्चयः_गवाक्षः_अधिकतमम्_आकार(_this, गवाक्षः);
    }

    // Ensure that window is not larger than maximal size
    पूर्णाङ्क w = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.w : गवाक्षः->floating.w;
    पूर्णाङ्क h = गवाक्षः->चरमः_आकार_pending ? गवाक्षः->pending.h : गवाक्षः->floating.h;
    प्रत्यागम SDL_समुच्चयः_गवाक्षः_आकार(गवाक्षः, w, h);
}

bool SDL_Get_गवाक्षः_अधिकतमम्_आकार(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *max_w, पूर्णाङ्क *max_h)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    यदि (max_w) {
        *max_w = गवाक्षः->max_w;
    }
    यदि (max_h) {
        *max_h = गवाक्षः->max_h;
    }
    प्रत्यागम true;
}

bool SDL_Show_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः *child;
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_HIDDEN)) {
        प्रत्यागम true;
    }

    // If the parent is hidden, set the flag to restore this when the parent is shown
    यदि (गवाक्षः->parent && (गवाक्षः->parent->flags & SDL_गवाक्षः_HIDDEN)) {
        गवाक्षः->restore_on_show = true;
        प्रत्यागम true;
    }

    यदि (_this->Show_गवाक्षः) {
        _this->Show_गवाक्षः(_this, गवाक्षः);
    } अन्यथा {
        SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
        SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
    }
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_SHOWN, 0, 0);

    // Restore child windows
    प्रति (child = गवाक्षः->first_child; child; child = child->अग्र_sibling) {
        यदि (!child->restore_on_show && (child->flags & SDL_गवाक्षः_HIDDEN)) {
            भङ्ग;
        }
        SDL_Show_गवाक्षः(child);
        child->restore_on_show = false;
    }
    प्रत्यागम true;
}

bool SDL_Hide_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः *child;
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        गवाक्षः->restore_on_show = false;
        प्रत्यागम true;
    }

    // Hide all child windows
    प्रति (child = गवाक्षः->first_child; child; child = child->अग्र_sibling) {
        यदि (child->flags & SDL_गवाक्षः_HIDDEN) {
            भङ्ग;
        }
        SDL_Hide_गवाक्षः(child);
        child->restore_on_show = true;
    }

    // Store the flags for restoration later.
    ध्रुव SDL_गवाक्षः_Flags pending_आवरणम् = (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_MINIMIZED | SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_KEYBOARD_GRABBED | SDL_गवाक्षः_MOUSE_GRABBED);
    गवाक्षः->pending_flags = (गवाक्षः->flags & pending_आवरणम्);

    गवाक्षः->is_hiding = true;
    यदि (_this->Hide_गवाक्षः) {
        _this->Hide_गवाक्षः(_this, गवाक्षः);
    } अन्यथा {
        SDL_समुच्चयः_Mouse_Focus(रिक्त);
        SDL_समुच्चयः_Keyboard_Focus(रिक्त);
    }
    गवाक्षः->is_hiding = false;
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_HIDDEN, 0, 0);
    प्रत्यागम true;
}

bool SDL_Raise_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        प्रत्यागम true;
    }
    यदि (_this->Raise_गवाक्षः) {
        _this->Raise_गवाक्षः(_this, गवाक्षः);
    }
    प्रत्यागम true;
}

bool SDL_Maximize_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (!_this->Maximize_गवाक्षः) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE)) {
        प्रत्यागम SDL_समुच्चयः_Error("A window without the 'SDL_WINDOW_RESIZABLE' flag can't be maximized");
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        गवाक्षः->pending_flags |= SDL_गवाक्षः_MAXIMIZED;
        प्रत्यागम true;
    }

    _this->Maximize_गवाक्षः(_this, गवाक्षः);
    SDL_SyncIfRequired(गवाक्षः);
    प्रत्यागम true;
}

bool SDL_Minimize_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (!_this->Minimize_गवाक्षः) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        गवाक्षः->pending_flags |= SDL_गवाक्षः_MINIMIZED;
        प्रत्यागम true;
    }

    _this->Minimize_गवाक्षः(_this, गवाक्षः);
    SDL_SyncIfRequired(गवाक्षः);
    प्रत्यागम true;
}

bool SDL_Restore_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (!_this->Restore_गवाक्षः) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        गवाक्षः->pending_flags &= ~(SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_MINIMIZED);
        प्रत्यागम true;
    }

    _this->Restore_गवाक्षः(_this, गवाक्षः);
    SDL_SyncIfRequired(गवाक्षः);
    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Fullscreen(SDL_गवाक्षः *गवाक्षः, bool fullscreen)
{
    bool परिणाम;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        यदि (fullscreen) {
            गवाक्षः->pending_flags |= SDL_गवाक्षः_FULLSCREEN;
        } अन्यथा {
            गवाक्षः->pending_flags &= ~SDL_गवाक्षः_FULLSCREEN;
        }
        प्रत्यागम true;
    }

    यदि (fullscreen) {
        // Set the current fullscreen mode to the desired mode
        SDL_copyp(&गवाक्षः->current_fullscreen_बहुलकम्, &गवाक्षः->requested_fullscreen_बहुलकम्);
    }

    परिणाम = SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, fullscreen ? SDL_FULLSCREEN_OP_ENTER : SDL_FULLSCREEN_OP_LEAVE, true);

    यदि (!fullscreen || !परिणाम) {
        // Clear the current fullscreen mode.
        SDL_zero(गवाक्षः->current_fullscreen_बहुलकम्);
    }

    यदि (परिणाम) {
        SDL_SyncIfRequired(गवाक्षः);
    }

    प्रत्यागम परिणाम;
}

bool SDL_Sync_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (_this->Sync_गवाक्षः) {
        प्रत्यागम _this->Sync_गवाक्षः(_this, गवाक्षः);
    } अन्यथा {
        प्रत्यागम true;
    }
}

स्थिर bool ShouldAttemptTextureFramebuffer(शून्य)
{
    ध्रुव वर्ण *hint;
    bool attempt_texture_framebuffer;

    // If the driver doesn't support window framebuffers, always use the render API.
    यदि (!_this->Create_गवाक्षः_Framebuffer) {
        प्रत्यागम true;
    }

    // See if there's a hint override
    hint = SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION);
    यदि (hint && *hint) {
        यदि (*hint == '0' || SDL_strcasecmp(hint, "false") == 0 || SDL_strcasecmp(hint, SDL_SOFTWARE_RENDERER) == 0) {
            attempt_texture_framebuffer = false;
        } अन्यथा {
            attempt_texture_framebuffer = true;
        }
    } अन्यथा {
        यदि (SDL_DriverHasSlowFramebuffer(_this)) {
            attempt_texture_framebuffer = true;
        } अन्यथा {
            attempt_texture_framebuffer = false;
        }
    }
    प्रत्यागम attempt_texture_framebuffer;
}

स्थिर SDL_Surface *SDL_Create_गवाक्षः_Framebuffer(SDL_गवाक्षः *गवाक्षः)
{
    SDL_PixelFormat format = SDL_PIXELFORMAT_UNKNOWN;
    शून्य *pixels = रिक्त;
    पूर्णाङ्क pitch = 0;
    bool created_framebuffer = false;
    पूर्णाङ्क w, h;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);

    /* This will switch the video backend from using a software surface to
       using a GPU texture through the 2D render API, if we think this would
       be more efficient. This only checks once, on demand. */
    यदि (!_this->checked_texture_framebuffer) {
        यदि (ShouldAttemptTextureFramebuffer()) {
            यदि (!SDL_Create_गवाक्षः_Texture(_this, गवाक्षः, &format, &pixels, &pitch)) {
                /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc),
                   !!! FIXME:  we probably need to clean this up so it doesn't interfere with
                   !!! FIXME:  a software fallback at the system level (can we blit to an
                   !!! FIXME:  OpenGL window? etc). */
            } अन्यथा {
                // future attempts will just try to use a texture framebuffer.
                /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture
                   !!! FIXME:  framebuffer at the right places; is it feasible we could have an
                   !!! FIXME:  accelerated OpenGL window and a second ends up in software? */
                _this->Create_गवाक्षः_Framebuffer = SDL_Create_गवाक्षः_Texture;
                _this->समुच्चयः_गवाक्षः_Framebuffer_VSync = SDL_समुच्चयः_गवाक्षः_Texture_VSync;
                _this->Get_गवाक्षः_Framebuffer_VSync = SDL_Get_गवाक्षः_Texture_VSync;
                _this->Update_गवाक्षः_Framebuffer = SDL_Update_गवाक्षः_Texture;
                _this->Destroy_गवाक्षः_Framebuffer = SDL_Destroy_गवाक्षः_Texture;
                created_framebuffer = true;
            }
        }

        _this->checked_texture_framebuffer = true; // don't check this again.
    }

    यदि (!created_framebuffer) {
        यदि (!_this->Create_गवाक्षः_Framebuffer || !_this->Update_गवाक्षः_Framebuffer) {
            SDL_समुच्चयः_Error("Window framebuffer support not available");
            प्रत्यागम रिक्त;
        }

        यदि (!_this->Create_गवाक्षः_Framebuffer(_this, गवाक्षः, &format, &pixels, &pitch)) {
            प्रत्यागम रिक्त;
        }
    }

    यदि (गवाक्षः->surface) {
        // We may have gone recursive and already created the surface
        प्रत्यागम गवाक्षः->surface;
    }

    प्रत्यागम SDL_CreateSurfaceFrom(w, h, format, pixels, pitch);
}

bool SDL_गवाक्षः_Has_Surface(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    प्रत्यागम गवाक्षः->surface ? true : false;
}

SDL_Surface *SDL_Get_गवाक्षः_Surface(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, रिक्त);

    यदि (!गवाक्षः->surface_valid) {
        यदि (गवाक्षः->surface) {
            गवाक्षः->surface->आन्तरिकम्_flags &= ~SDL_आन्तरिकम्_SURFACE_DONTFREE;
            SDL_DestroySurface(गवाक्षः->surface);
            गवाक्षः->surface = रिक्त;
        }

        गवाक्षः->surface = SDL_Create_गवाक्षः_Framebuffer(गवाक्षः);
        यदि (गवाक्षः->surface) {
            गवाक्षः->surface_valid = true;
            गवाक्षः->surface->आन्तरिकम्_flags |= SDL_आन्तरिकम्_SURFACE_DONTFREE;
        }
    }
    प्रत्यागम गवाक्षः->surface;
}

bool SDL_समुच्चयः_गवाक्षः_Surface_VSync(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क vsync)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_Framebuffer_VSync) {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम _this->समुच्चयः_गवाक्षः_Framebuffer_VSync(_this, गवाक्षः, vsync);
}

bool SDL_Get_गवाक्षः_Surface_VSync(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *vsync)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!_this->Get_गवाक्षः_Framebuffer_VSync) {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम _this->Get_गवाक्षः_Framebuffer_VSync(_this, गवाक्षः, vsync);
}

bool SDL_Update_गवाक्षः_Surface(SDL_गवाक्षः *गवाक्षः)
{
    SDL_Rect पूर्णम्_rect;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    पूर्णम्_rect.x = 0;
    पूर्णम्_rect.y = 0;
    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &पूर्णम्_rect.w, &पूर्णम्_rect.h);

    प्रत्यागम SDL_Update_गवाक्षः_Surface_Rects(गवाक्षः, &पूर्णम्_rect, 1);
}

bool SDL_Update_गवाक्षः_Surface_Rects(SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects,
                                 पूर्णाङ्क numrects)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!गवाक्षः->surface_valid) {
        प्रत्यागम SDL_समुच्चयः_Error("Window surface is invalid, please call SDL_GetWindowSurface() to get a new surface");
    }

    SDL_assert(_this->checked_texture_framebuffer); // we should have done this before we had a valid surface.

    प्रत्यागम _this->Update_गवाक्षः_Framebuffer(_this, गवाक्षः, rects, numrects);
}

bool SDL_Destroy_गवाक्षः_Surface(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (गवाक्षः->surface) {
        गवाक्षः->surface->आन्तरिकम्_flags &= ~SDL_आन्तरिकम्_SURFACE_DONTFREE;
        SDL_DestroySurface(गवाक्षः->surface);
        गवाक्षः->surface = रिक्त;
        गवाक्षः->surface_valid = false;
    }

    यदि (_this->checked_texture_framebuffer) { // never checked? No framebuffer to destroy. Don't risk calling the wrong implementation.
        यदि (_this->Destroy_गवाक्षः_Framebuffer) {
            _this->Destroy_गवाक्षः_Framebuffer(_this, गवाक्षः);
        }
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Opacity(SDL_गवाक्षः *गवाक्षः, भिन्न opacity)
{
    bool परिणाम;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_Opacity) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (opacity < 0.0f) {
        opacity = 0.0f;
    } अन्यथा यदि (opacity > 1.0f) {
        opacity = 1.0f;
    }

    परिणाम = _this->समुच्चयः_गवाक्षः_Opacity(_this, गवाक्षः, opacity);
    यदि (परिणाम) {
        गवाक्षः->opacity = opacity;
    }

    प्रत्यागम परिणाम;
}

भिन्न SDL_Get_गवाक्षः_Opacity(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, -1.0f);

    प्रत्यागम गवाक्षः->opacity;
}

bool SDL_समुच्चयः_गवाक्षः_Parent(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (parent) {
        CHECK_गवाक्षः_MAGIC(parent, false);
        CHECK_गवाक्षः_NOT_POPUP(parent, false);
    }

    यदि (गवाक्षः == parent) {
        प्रत्यागम SDL_समुच्चयः_Error("Cannot set the parent of a window to itself.");
    }

    यदि (!_this->समुच्चयः_गवाक्षः_Parent) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_MODAL) {
        प्रत्यागम SDL_समुच्चयः_Error("Modal windows cannot change parents; call SDL_SetWindowModal() to clear modal status first.");
    }

    यदि (गवाक्षः->parent == parent) {
        प्रत्यागम true;
    }

    ध्रुव bool ret = _this->समुच्चयः_गवाक्षः_Parent(_this, गवाक्षः, parent);
    SDL_Update_गवाक्षः_Hierarchy(गवाक्षः, ret ? parent : रिक्त);

    प्रत्यागम ret;
}

bool SDL_समुच्चयः_गवाक्षः_Modal(SDL_गवाक्षः *गवाक्षः, bool modal)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_Modal) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (modal) {
        यदि (!गवाक्षः->parent) {
            प्रत्यागम SDL_समुच्चयः_Error("Window must have a parent to enable the modal state; use SDL_SetWindowParent() to set the parent first.");
        }
        गवाक्षः->flags |= SDL_गवाक्षः_MODAL;
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_MODAL) {
        गवाक्षः->flags &= ~SDL_गवाक्षः_MODAL;
    } अन्यथा {
        प्रत्यागम true; // Already not modal, so nothing to do.
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        प्रत्यागम true;
    }

    प्रत्यागम _this->समुच्चयः_गवाक्षः_Modal(_this, गवाक्षः, modal);
}

bool SDL_ShouldRelinquishPopupFocus(SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः **new_focus)
{
    SDL_गवाक्षः *focus = गवाक्षः->parent;
    bool समुच्चयः_focus = !!(गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS);

    // Find the highest level window, up to the toplevel parent, that isn't being hidden or destroyed, and can grab the keyboard focus.
    यावत् (SDL_गवाक्षः_IS_POPUP(focus) && ((focus->flags & SDL_गवाक्षः_NOT_FOCUSABLE) || focus->is_hiding || focus->is_destroying)) {
        focus = focus->parent;

        // If some window in the chain currently had focus, set it to the new lowest-level window.
        यदि (!समुच्चयः_focus) {
            समुच्चयः_focus = !!(focus->flags & SDL_गवाक्षः_निवेशः_FOCUS);
        }
    }

    *new_focus = focus;
    प्रत्यागम समुच्चयः_focus;
}

bool SDL_ShouldFocusPopup(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः *toplevel_parent;
    प्रति (toplevel_parent = गवाक्षः->parent; SDL_गवाक्षः_IS_POPUP(toplevel_parent); toplevel_parent = toplevel_parent->parent) {
    }

    SDL_गवाक्षः *current_focus = toplevel_parent->keyboard_focus;
    bool प्राप्तम्_higher_focus = false;

    /* Traverse the window tree from the currently focused window to the toplevel parent and see if we encounter
     * the new focus request. If the new window is found, a higher-level window already has focus.
     */
    SDL_गवाक्षः *w;
    प्रति (w = current_focus; w != toplevel_parent; w = w->parent) {
        यदि (w == गवाक्षः) {
            प्राप्तम्_higher_focus = true;
            भङ्ग;
        }
    }

    प्रत्यागम !प्राप्तम्_higher_focus || w == toplevel_parent;
}

bool SDL_समुच्चयः_गवाक्षः_Focusable(SDL_गवाक्षः *गवाक्षः, bool focusable)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    ध्रुव bool want = (focusable != false); // normalize the flag.
    ध्रुव bool have = !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE);
    यदि ((want != have) && (_this->समुच्चयः_गवाक्षः_Focusable)) {
        यदि (want) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_NOT_FOCUSABLE;
        } अन्यथा {
            गवाक्षः->flags |= SDL_गवाक्षः_NOT_FOCUSABLE;
        }
        यदि (!_this->समुच्चयः_गवाक्षः_Focusable(_this, गवाक्षः, want)) {
            प्रत्यागम false;
        }
    }

    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Fill_Document(SDL_गवाक्षः *गवाक्षः, bool fill)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    ध्रुव bool want = (fill != false); // normalize the flag.
    ध्रुव bool have = ((गवाक्षः->flags & SDL_गवाक्षः_FILL_DOCUMENT) != 0);
    यदि ((want != have) && (_this->समुच्चयः_गवाक्षः_Fill_Document)) {
        यदि (!_this->समुच्चयः_गवाक्षः_Fill_Document(_this, गवाक्षः, want)) {
            प्रत्यागम false;
        } अन्यथा यदि (want) {
            गवाक्षः->flags |= SDL_गवाक्षः_FILL_DOCUMENT;
        } अन्यथा {
            गवाक्षः->flags &= ~SDL_गवाक्षः_FILL_DOCUMENT;
        }
    }

    प्रत्यागम true;
}

शून्य SDL_Update_गवाक्षः_Grab(SDL_गवाक्षः *गवाक्षः)
{
    bool keyboard_grabbed, mouse_grabbed;

    यदि (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS) {
        यदि (SDL_GetMouse()->relative_बहुलकम् || (गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED)) {
            mouse_grabbed = true;
        } अन्यथा {
            mouse_grabbed = false;
        }

        यदि (गवाक्षः->flags & SDL_गवाक्षः_KEYBOARD_GRABBED) {
            keyboard_grabbed = true;
        } अन्यथा {
            keyboard_grabbed = false;
        }
    } अन्यथा {
        mouse_grabbed = false;
        keyboard_grabbed = false;
    }

    यदि (mouse_grabbed || keyboard_grabbed) {
        यदि (_this->grabbed_गवाक्षः && (_this->grabbed_गवाक्षः != गवाक्षः)) {
            // stealing a grab from another window!
            _this->grabbed_गवाक्षः->flags &= ~(SDL_गवाक्षः_MOUSE_GRABBED | SDL_गवाक्षः_KEYBOARD_GRABBED);
            यदि (_this->समुच्चयः_गवाक्षः_Mouse_Grab) {
                _this->समुच्चयः_गवाक्षः_Mouse_Grab(_this, _this->grabbed_गवाक्षः, false);
            }
            यदि (_this->समुच्चयः_गवाक्षः_Keyboard_Grab) {
                _this->समुच्चयः_गवाक्षः_Keyboard_Grab(_this, _this->grabbed_गवाक्षः, false);
            }
        }
        _this->grabbed_गवाक्षः = गवाक्षः;
    } अन्यथा यदि (_this->grabbed_गवाक्षः == गवाक्षः) {
        _this->grabbed_गवाक्षः = रिक्त; // ungrabbing input.
    }

    यदि (_this->समुच्चयः_गवाक्षः_Mouse_Grab) {
        यदि (!_this->समुच्चयः_गवाक्षः_Mouse_Grab(_this, गवाक्षः, mouse_grabbed)) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_MOUSE_GRABBED;
        }
    }
    यदि (_this->समुच्चयः_गवाक्षः_Keyboard_Grab) {
        यदि (!_this->समुच्चयः_गवाक्षः_Keyboard_Grab(_this, गवाक्षः, keyboard_grabbed)) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_KEYBOARD_GRABBED;
        }
    }

    यदि (_this->grabbed_गवाक्षः && !(_this->grabbed_गवाक्षः->flags & (SDL_गवाक्षः_MOUSE_GRABBED | SDL_गवाक्षः_KEYBOARD_GRABBED))) {
        _this->grabbed_गवाक्षः = रिक्त;
    }
}

bool SDL_समुच्चयः_गवाक्षः_Keyboard_Grab(SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        यदि (grabbed) {
            गवाक्षः->pending_flags |= SDL_गवाक्षः_KEYBOARD_GRABBED;
        } अन्यथा {
            गवाक्षः->pending_flags &= ~SDL_गवाक्षः_KEYBOARD_GRABBED;
        }
        प्रत्यागम true;
    }

    यदि (!!grabbed == !!(गवाक्षः->flags & SDL_गवाक्षः_KEYBOARD_GRABBED)) {
        प्रत्यागम true;
    }
    यदि (grabbed) {
        गवाक्षः->flags |= SDL_गवाक्षः_KEYBOARD_GRABBED;
    } अन्यथा {
        गवाक्षः->flags &= ~SDL_गवाक्षः_KEYBOARD_GRABBED;
    }
    SDL_Update_गवाक्षः_Grab(गवाक्षः);

    यदि (grabbed && !(गवाक्षः->flags & SDL_गवाक्षः_KEYBOARD_GRABBED)) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_HIDDEN) {
        यदि (grabbed) {
            गवाक्षः->pending_flags |= SDL_गवाक्षः_MOUSE_GRABBED;
        } अन्यथा {
            गवाक्षः->pending_flags &= ~SDL_गवाक्षः_MOUSE_GRABBED;
        }
        प्रत्यागम true;
    }

    यदि (!!grabbed == !!(गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED)) {
        प्रत्यागम true;
    }
    यदि (grabbed) {
        गवाक्षः->flags |= SDL_गवाक्षः_MOUSE_GRABBED;
    } अन्यथा {
        गवाक्षः->flags &= ~SDL_गवाक्षः_MOUSE_GRABBED;
    }
    SDL_Update_गवाक्षः_Grab(गवाक्षः);

    यदि (grabbed && !(गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED)) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool SDL_Get_गवाक्षः_Keyboard_Grab(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    प्रत्यागम गवाक्षः == _this->grabbed_गवाक्षः && (_this->grabbed_गवाक्षः->flags & SDL_गवाक्षः_KEYBOARD_GRABBED);
}

bool SDL_Get_गवाक्षः_Mouse_Grab(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    प्रत्यागम गवाक्षः == _this->grabbed_गवाक्षः && (_this->grabbed_गवाक्षः->flags & SDL_गवाक्षः_MOUSE_GRABBED);
}

SDL_गवाक्षः *SDL_Get_Grabbed_गवाक्षः(शून्य)
{
    यदि (_this && _this->grabbed_गवाक्षः &&
        (_this->grabbed_गवाक्षः->flags & (SDL_गवाक्षः_MOUSE_GRABBED | SDL_गवाक्षः_KEYBOARD_GRABBED)) != 0) {
        प्रत्यागम _this->grabbed_गवाक्षः;
    } अन्यथा {
        प्रत्यागम रिक्त;
    }
}

bool SDL_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rect)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_Mouse_Rect) {
        प्रत्यागम SDL_Unsupported();
    }

    SDL_Rect zero = { 0, 0, 0, 0 };
    यदि (!rect) {
        rect = &zero;
    }

    यदि (SDL_memcmp(&गवाक्षः->mouse_rect, rect, परिमाण(*rect)) == 0) {
        प्रत्यागम true;
    }
    SDL_memcpy(&गवाक्षः->mouse_rect, rect, परिमाण(*rect));

    प्रत्यागम _this->समुच्चयः_गवाक्षः_Mouse_Rect(_this, गवाक्षः);
}

ध्रुव SDL_Rect *SDL_Get_गवाक्षः_Mouse_Rect(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, रिक्त);

    यदि (SDL_Rect_रिक्तानि(&गवाक्षः->mouse_rect)) {
        प्रत्यागम रिक्त;
    } अन्यथा {
        प्रत्यागम &गवाक्षः->mouse_rect;
    }
}

bool SDL_समुच्चयः_गवाक्षः_Relative_Mouse_बहुलकम्(SDL_गवाक्षः *गवाक्षः, bool enabled)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    /* If the app toggles relative mode directly, it probably shouldn't
     * also be emulating it using repeated mouse warps, so disable
     * mouse warp emulation by default.
     */
    SDL_DisableMouseWarpEmulation();

    यदि (enabled == SDL_Get_गवाक्षः_Relative_Mouse_बहुलकम्(गवाक्षः)) {
        प्रत्यागम true;
    }

    यदि (enabled) {
        गवाक्षः->flags |= SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्;
    } अन्यथा {
        गवाक्षः->flags &= ~SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्;
    }

    यदि (!SDL_Update_Relative_Mouse_बहुलकम्()) {
        यदि (enabled) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्;
        } अन्यथा {
            गवाक्षः->flags |= SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्;
        }
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool SDL_Get_गवाक्षः_Relative_Mouse_बहुलकम्(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_MOUSE_RELATIVE_बहुलकम्) {
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम false;
    }
}

bool SDL_Flash_गवाक्षः(SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (_this->Flash_गवाक्षः) {
        प्रत्यागम _this->Flash_गवाक्षः(_this, गवाक्षः, operation);
    }

    प्रत्यागम SDL_Unsupported();
}

bool SDL_समुच्चयः_गवाक्षः_प्रगतिः_State(SDL_गवाक्षः *गवाक्षः, SDL_प्रगतिः_State state)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    CHECK_PARAM(state < SDL_प्रगतिः_STATE_NONE || state > SDL_प्रगतिः_STATE_ERROR) {
        प्रत्यागम SDL_InvalidParamError("state");
    }

    गवाक्षः->प्रगतिः_state = state;

    यदि (_this->Apply_गवाक्षः_प्रगतिः) {
        यदि (!_this->Apply_गवाक्षः_प्रगतिः(_this, गवाक्षः)) {
            प्रत्यागम false;
        }
    }

    प्रत्यागम true;
}

SDL_प्रगतिः_State SDL_Get_गवाक्षः_प्रगतिः_State(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, SDL_प्रगतिः_STATE_INVALID);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, SDL_प्रगतिः_STATE_INVALID);

    प्रत्यागम गवाक्षः->प्रगतिः_state;
}

bool SDL_समुच्चयः_गवाक्षः_प्रगतिः_मानम्(SDL_गवाक्षः *गवाक्षः, भिन्न मानम्)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    मानम् = SDL_clamp(मानम्, 0.0f, 1.f);

    गवाक्षः->प्रगतिः_मानम् = मानम्;

    यदि (_this->Apply_गवाक्षः_प्रगतिः) {
        यदि (!_this->Apply_गवाक्षः_प्रगतिः(_this, गवाक्षः)) {
            प्रत्यागम false;
        }
    }

    प्रत्यागम true;
}

भिन्न SDL_Get_गवाक्षः_प्रगतिः_मानम्(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, -1.0f);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, -1.0f);

    प्रत्यागम गवाक्षः->प्रगतिः_मानम्;
}

शून्य SDL_On_गवाक्षः_Shown(SDL_गवाक्षः *गवाक्षः)
{
    // Set window state if we have pending window flags cached
    Apply_गवाक्षः_Flags(गवाक्षः, गवाक्षः->pending_flags);
    गवाक्षः->pending_flags = 0;
}

शून्य SDL_On_गवाक्षः_Hidden(SDL_गवाक्षः *गवाक्षः)
{
    /* Store the maximized and fullscreen flags for restoration later, in case
     * this was initiated by the window manager due to the window being unmapped
     * when minimized.
     */
    गवाक्षः->pending_flags |= (गवाक्षः->flags & (SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_MAXIMIZED));

    // The window is already hidden at this point, so just change the mode back if necessary.
    SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_LEAVE, false);
}

शून्य SDL_On_गवाक्षः_Display_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः)
{
    // Don't run this if a fullscreen change was made in an event watcher callback in response to a display changed event.
    यदि (गवाक्षः->update_fullscreen_on_display_परिवर्तितम् && (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
        ध्रुव bool auto_बहुलकम्_switch = SDL_GetHintBoolean(SDL_HINT_VIDEO_मेलनम्_EXCLUSIVE_बहुलकम्_ON_MOVE, true);

        यदि (auto_बहुलकम्_switch && (गवाक्षः->requested_fullscreen_बहुलकम्.w != 0 || गवाक्षः->requested_fullscreen_बहुलकम्.h != 0)) {
            SDL_DisplayID displayID = SDL_Get_Display_For_गवाक्षः_Position(गवाक्षः);
            bool include_उच्चः_density_modes = false;

            यदि (गवाक्षः->requested_fullscreen_बहुलकम्.pixel_density > 1.0f) {
                include_उच्चः_density_modes = true;
            }
            ध्रुव bool प्राप्तम्_मेलनम् = SDL_Get_Closest_Fullscreen_Display_बहुलकम्(displayID, गवाक्षः->requested_fullscreen_बहुलकम्.w, गवाक्षः->requested_fullscreen_बहुलकम्.h,
                                                                         गवाक्षः->requested_fullscreen_बहुलकम्.refresh_दरः, include_उच्चः_density_modes, &गवाक्षः->current_fullscreen_बहुलकम्);

            // If a mode without matching dimensions was not found, just go to fullscreen desktop.
            यदि (!प्राप्तम्_मेलनम् ||
                गवाक्षः->requested_fullscreen_बहुलकम्.w != गवाक्षः->current_fullscreen_बहुलकम्.w ||
                गवाक्षः->requested_fullscreen_बहुलकम्.h != गवाक्षः->current_fullscreen_बहुलकम्.h) {
                SDL_zero(गवाक्षः->current_fullscreen_बहुलकम्);
            }
        } अन्यथा {
            SDL_zero(गवाक्षः->current_fullscreen_बहुलकम्);
        }

        यदि (SDL_गवाक्षः_FULLSCREEN_VISIBLE(गवाक्षः)) {
            SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_UPDATE, true);
        }
    }

    SDL_Check_गवाक्षः_Pixel_आकार_परिवर्तितम्(गवाक्षः);
}

शून्य SDL_On_गवाक्षः_Moved(SDL_गवाक्षः *गवाक्षः)
{
    SDL_Check_गवाक्षः_Display_परिवर्तितम्(गवाक्षः);
}

शून्य SDL_On_गवाक्षः_Resized(SDL_गवाक्षः *गवाक्षः)
{
    SDL_Check_गवाक्षः_Display_परिवर्तितम्(गवाक्षः);
    SDL_Check_गवाक्षः_Pixel_आकार_परिवर्तितम्(गवाक्षः);
    SDL_Check_गवाक्षः_Safe_Area_परिवर्तितम्(गवाक्षः);

    यदि ((गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) && _this->Update_गवाक्षः_Shape) {
        SDL_Surface *surface = (SDL_Surface *)SDL_GetPointerProperty(गवाक्षः->props, SDL_PROP_गवाक्षः_SHAPE_POINTER, रिक्त);
        यदि (surface) {
            _this->Update_गवाक्षः_Shape(_this, गवाक्षः, surface);
        }
    }
}

शून्य SDL_Check_गवाक्षः_Pixel_आकार_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः)
{
    पूर्णाङ्क pixel_w = 0, pixel_h = 0;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &pixel_w, &pixel_h);
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_PIXEL_आकार_परिवर्तितम्, pixel_w, pixel_h);

    SDL_Check_गवाक्षः_Display_Scale_परिवर्तितम्(गवाक्षः);
}

शून्य SDL_On_गवाक्षः_Pixel_आकार_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः)
{
    गवाक्षः->surface_valid = false;
}

शून्य SDL_On_गवाक्षः_जीवितम्_Resize_Update(SDL_गवाक्षः *गवाक्षः)
{
    यदि (SDL_HasMainCallbacks()) {
        SDL_IterateMainCallbacks(false);
    } अन्यथा {
        // Send an expose event so the application can redraw
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 1, 0);
    }

    SDL_PumpEventMaintenance();
}

स्थिर शून्य SDL_Check_गवाक्षः_Safe_Area_परिवर्तितम्(SDL_गवाक्षः *गवाक्षः)
{
    SDL_Rect rect;

    rect.x = गवाक्षः->safe_inset_वामः;
    rect.y = गवाक्षः->safe_inset_शिखरम्;
    rect.w = गवाक्षः->w - (गवाक्षः->safe_inset_दक्षिणः + गवाक्षः->safe_inset_वामः);
    rect.h = गवाक्षः->h - (गवाक्षः->safe_inset_शिखरम् + गवाक्षः->safe_inset_bottom);
    यदि (SDL_memcmp(&rect, &गवाक्षः->safe_rect, परिमाण(rect)) != 0) {
        SDL_copyp(&गवाक्षः->safe_rect, &rect);
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_SAFE_AREA_परिवर्तितम्, 0, 0);
    }
}

शून्य SDL_समुच्चयः_गवाक्षः_Safe_Area_Insets(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क वामः, पूर्णाङ्क दक्षिणः, पूर्णाङ्क शिखरम्, पूर्णाङ्क bottom)
{
    गवाक्षः->safe_inset_वामः = वामः;
    गवाक्षः->safe_inset_दक्षिणः = दक्षिणः;
    गवाक्षः->safe_inset_शिखरम् = शिखरम्;
    गवाक्षः->safe_inset_bottom = bottom;
    SDL_Check_गवाक्षः_Safe_Area_परिवर्तितम्(गवाक्षः);
}

bool SDL_Get_गवाक्षः_Safe_Area(SDL_गवाक्षः *गवाक्षः, SDL_Rect *rect)
{
    यदि (rect) {
        SDL_zerop(rect);
    }

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (rect) {
        यदि (SDL_Rect_रिक्तानि(&गवाक्षः->safe_rect)) {
            rect->w = गवाक्षः->w;
            rect->h = गवाक्षः->h;
        } अन्यथा {
            SDL_copyp(rect, &गवाक्षः->safe_rect);
        }
    }
    प्रत्यागम true;
}

शून्य SDL_On_गवाक्षः_Minimized(SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_LEAVE, false);
    }
}

शून्य SDL_On_गवाक्षः_Maximized(SDL_गवाक्षः *गवाक्षः)
{
}

शून्य SDL_On_गवाक्षः_Restored(SDL_गवाक्षः *गवाक्षः)
{
    /*
     * FIXME: Is this fine to just remove this, or should it be preserved just
     * for the fullscreen case? In principle it seems like just hiding/showing
     * windows shouldn't affect the stacking order; maybe the right fix is to
     * re-decouple OnWindowShown and OnWindowRestored.
     */
    // SDL_RaiseWindow(window);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) {
        SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_ENTER, false);
    }
}

शून्य SDL_On_गवाक्षः_Enter(SDL_गवाक्षः *गवाक्षः)
{
    यदि (_this->On_गवाक्षः_Enter) {
        _this->On_गवाक्षः_Enter(_this, गवाक्षः);
    }
    SDL_Update_Relative_Mouse_बहुलकम्();
}

शून्य SDL_On_गवाक्षः_Leave(SDL_गवाक्षः *गवाक्षः)
{
    SDL_Update_Relative_Mouse_बहुलकम्();
}

शून्य SDL_On_गवाक्षः_Focus_Gained(SDL_गवाक्षः *गवाक्षः)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    यदि (mouse && mouse->relative_बहुलकम्) {
        SDL_समुच्चयः_Mouse_Focus(गवाक्षः);
    }

    SDL_Update_गवाक्षः_Grab(गवाक्षः);
}

स्थिर bool SDL_ShouldMinimizeOnFocusLoss(SDL_गवाक्षः *गवाक्षः)
{
    ध्रुव वर्ण *hint;

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) || गवाक्षः->is_destroying) {
        प्रत्यागम false;
    }

#यदि defined(SDL_PLATFORM_MACOS) && defined(SDL_VIDEO_DRIVER_COCOA)
    यदि (SDL_strcmp(_this->name, "cocoa") == 0) { // don't do this for X11, etc
        यदि (Cocoa_IsShowingModalDialog(गवाक्षः)) {
            प्रत्यागम false;  // modal system dialogs can live over fullscreen windows, don't minimize.
        } अन्यथा यदि (Cocoa_Is_गवाक्षः_अन्तर्_Fullscreen_Space(गवाक्षः)) {
            प्रत्यागम false;
        }
    }
#यदि_अन्तः

#यदि_परिभाषितम् SDL_PLATFORM_ANDROID
    {
        बाह्य bool Android_JNI_ShouldMinimizeOnFocusLoss(शून्य);
        यदि (!Android_JNI_ShouldMinimizeOnFocusLoss()) {
            प्रत्यागम false;
        }
    }
#यदि_अन्तः

    // Real fullscreen windows should minimize on focus loss so the desktop video mode is restored
    hint = SDL_GetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
    यदि (!hint || !*hint || SDL_strcasecmp(hint, "auto") == 0) {
        यदि (गवाक्षः->fullscreen_exclusive && !SDL_बहुलकम्_Switching_Emulated(_this)) {
            प्रत्यागम true;
        } अन्यथा {
            प्रत्यागम false;
        }
    }
    प्रत्यागम SDL_GetHintBoolean(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, false);
}

शून्य SDL_On_गवाक्षः_Focus_नष्टम्(SDL_गवाक्षः *गवाक्षः)
{
    SDL_Update_गवाक्षः_Grab(गवाक्षः);

    यदि (SDL_ShouldMinimizeOnFocusLoss(गवाक्षः)) {
        SDL_Minimize_गवाक्षः(गवाक्षः);
    }
}

SDL_गवाक्षः *SDL_GetToplevelForKeyboardFocus(शून्य)
{
    SDL_गवाक्षः *focus = SDL_GetKeyboardFocus();

    यदि (focus) {
        // Get the toplevel parent window.
        यावत् (focus->parent) {
            focus = focus->parent;
        }
    }

    प्रत्यागम focus;
}

bool SDL_सङ्कलय_गवाक्षः_Renderer(SDL_गवाक्षः *गवाक्षः, SDL_Renderer *renderer)
{
    SDL_Renderer **renderers = (SDL_Renderer **)SDL_realloc(गवाक्षः->renderers, (गवाक्षः->अङ्कः_renderers + 1) * परिमाण(*renderers));
    यदि (!renderers) {
        प्रत्यागम false;
    }

    गवाक्षः->renderers = renderers;
    गवाक्षः->renderers[गवाक्षः->अङ्कः_renderers++] = renderer;

    SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_RENDERER_POINTER, renderer);
    प्रत्यागम true;
}

शून्य SDL_Remove_गवाक्षः_Renderer(SDL_गवाक्षः *गवाक्षः, SDL_Renderer *renderer)
{
    प्रति (पूर्णाङ्क i = 0; i < गवाक्षः->अङ्कः_renderers; ++i) {
        यदि (गवाक्षः->renderers[i] == renderer) {
            यदि (i < (गवाक्षः->अङ्कः_renderers - 1)) {
                SDL_memmove(&गवाक्षः->renderers[i], &गवाक्षः->renderers[i + 1], (गवाक्षः->अङ्कः_renderers - i - 1) * परिमाण(गवाक्षः->renderers[i]));
            }
            --गवाक्षः->अङ्कः_renderers;
            भङ्ग;
        }
    }

    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    यदि (SDL_GetPointerProperty(props, SDL_PROP_गवाक्षः_RENDERER_POINTER, रिक्त) == renderer) {
        SDL_ClearProperty(props, SDL_PROP_गवाक्षः_RENDERER_POINTER);
    }
}

शून्य SDL_Destroy_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः,);

    गवाक्षः->is_destroying = true;

    // Destroy any child windows of this window
    यावत् (गवाक्षः->first_child) {
        SDL_Destroy_गवाक्षः(गवाक्षः->first_child);
    }

    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_DESTROYED, 0, 0);

    SDL_Destroy_गवाक्षः_Surface(गवाक्षः);

    SDL_Renderer *renderer = SDL_GetRenderer(गवाक्षः);
    यदि (renderer) {
        SDL_DestroyRendererWithoutFreeing(renderer);
    }

    // Restore video mode, etc.
    SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_LEAVE, true);
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL)) {
        SDL_Hide_गवाक्षः(गवाक्षः);
    }

    SDL_DestroyProperties(गवाक्षः->text_निवेशः_props);

    SDL_Destroy_गवाक्षः_Texture(_this, गवाक्षः);
    SDL_DestroyProperties(गवाक्षः->props);

    /* Clear the modal status, but don't unset the parent just yet, as it
     * may be needed later in the destruction process if a backend needs
     * to update the input focus.
     */
    यदि (_this->समुच्चयः_गवाक्षः_Modal && (गवाक्षः->flags & SDL_गवाक्षः_MODAL)) {
        _this->समुच्चयः_गवाक्षः_Modal(_this, गवाक्षः, false);
    }

    // Make sure the destroyed window isn't referenced by any display as a fullscreen window.
    प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
        यदि (_this->displays[i]->fullscreen_गवाक्षः == गवाक्षः) {
            _this->displays[i]->fullscreen_गवाक्षः = रिक्त;
        }
    }

    // Make sure this window no longer has focus
    यदि (SDL_GetKeyboardFocus() == गवाक्षः) {
        SDL_समुच्चयः_Keyboard_Focus(रिक्त);
    }
    यदि ((गवाक्षः->flags & SDL_गवाक्षः_MOUSE_CAPTURE)) {
        SDL_UpdateMouseCapture(true);
    }
    यदि (SDL_GetMouseFocus() == गवाक्षः) {
        SDL_समुच्चयः_Mouse_Focus(रिक्त);
    }

    // Make no context current if this is the current context window
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        यदि (_this->current_glwin == गवाक्षः) {
            SDL_GL_MakeCurrent(गवाक्षः, रिक्त);
        }
    }

    यदि (_this->Destroy_गवाक्षः) {
        _this->Destroy_गवाक्षः(_this, गवाक्षः);
    }

    // Unload the graphics libraries after the window is destroyed, which may clean up EGL surfaces
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        SDL_GL_UnloadLibrary();
    }
    यदि (गवाक्षः->flags & SDL_गवाक्षः_VULKAN) {
        SDL_Vulkan_UnloadLibrary();
    }

    यदि (_this->grabbed_गवाक्षः == गवाक्षः) {
        _this->grabbed_गवाक्षः = रिक्त; // ungrabbing input.
    }

    यदि (_this->current_glwin == गवाक्षः) {
        _this->current_glwin = रिक्त;
    }

    SDL_CompareAndSwapAtomicPointer(&_this->wakeup_गवाक्षः, गवाक्षः, रिक्त);

    // Now invalidate magic
    SDL_समुच्चयः_Object_Valid(गवाक्षः, SDL_OBJECT_TYPE_गवाक्षः, false);

    // Free memory associated with the window
    SDL_free(गवाक्षः->title);
    SDL_DestroySurface(गवाक्षः->icon);

    // Unlink the window from its siblings.
    SDL_Update_गवाक्षः_Hierarchy(गवाक्षः, रिक्त);

    // Unlink the window from the global window list
    यदि (गवाक्षः->अग्र) {
        गवाक्षः->अग्र->पूर्व = गवाक्षः->पूर्व;
    }
    यदि (गवाक्षः->पूर्व) {
        गवाक्षः->पूर्व->अग्र = गवाक्षः->अग्र;
    } अन्यथा {
        _this->windows = गवाक्षः->अग्र;
    }

    SDL_free(गवाक्षः->renderers);
    SDL_free(गवाक्षः);

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_UIKIT
    SDL_UpdateLifecycleObserver();
#यदि_अन्तः
}

bool SDL_ScreenSaverEnabled(शून्य)
{
    यदि (!_this) {
        प्रत्यागम true;
    }
    प्रत्यागम !_this->suspend_screensaver;
}

bool SDL_EnableScreenSaver(शून्य)
{
    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (!_this->suspend_screensaver) {
        प्रत्यागम true;
    }
    _this->suspend_screensaver = false;
    यदि (_this->SuspendScreenSaver) {
        प्रत्यागम _this->SuspendScreenSaver(_this);
    }

    प्रत्यागम SDL_Unsupported();
}

bool SDL_DisableScreenSaver(शून्य)
{
    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (_this->suspend_screensaver) {
        प्रत्यागम true;
    }
    _this->suspend_screensaver = true;
    यदि (_this->SuspendScreenSaver) {
        प्रत्यागम _this->SuspendScreenSaver(_this);
    }

    प्रत्यागम SDL_Unsupported();
}

शून्य SDL_QuitVideo(शून्य)
{
    पूर्णाङ्क i;

    यदि (!_this) {
        प्रत्यागम;
    }

    _this->is_quitting = true;

    // Halt event processing before doing anything else
#यदि 0 // This was moved to the end to fix a memory leak
    SDL_QuitPen();
#यदि_अन्तः
    SDL_QuitTouch();
    SDL_QuitMouse();
    SDL_QuitKeyboard();
    SDL_QuitSubSystem(SDL_INIT_EVENTS);

    SDL_EnableScreenSaver();

    // Clean up the system video
    यावत् (_this->windows) {
        SDL_Destroy_गवाक्षः(_this->windows);
    }

    यदि (_this->gl_config.driver_loaded && _this->GL_UnloadLibrary) {
        _this->GL_UnloadLibrary(_this);
        _this->gl_config.driver_loaded = 0;
    }
    यदि (_this->vulkan_config.loader_loaded && _this->Vulkan_UnloadLibrary) {
        _this->Vulkan_UnloadLibrary(_this);
        _this->vulkan_config.loader_loaded = 0;
    }

    _this->VideoQuit(_this);

    प्रति (i = _this->अङ्कः_displays; i--; ) {
        SDL_VideoDisplay *display = _this->displays[i];
        SDL_DelVideoDisplay(display->id, false);
    }

    SDL_assert(_this->अङ्कः_displays == 0);
    SDL_free(_this->displays);
    _this->displays = रिक्त;

    SDL_Cancel_Clipboard_दत्त(0);

    यदि (_this->primary_selection_text) {
        SDL_free(_this->primary_selection_text);
        _this->primary_selection_text = रिक्त;
    }
    _this->मुक्त(_this);
    _this = रिक्त;

    // This needs to happen after the video subsystem has removed pen data
    SDL_QuitPen();
}

bool SDL_GL_आरोपय_Library(ध्रुव वर्ण *मार्गः)
{
    bool परिणाम;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (_this->gl_config.driver_loaded) {
        यदि (मार्गः && SDL_strcmp(मार्गः, _this->gl_config.driver_मार्गः) != 0) {
            प्रत्यागम SDL_समुच्चयः_Error("OpenGL library already loaded");
        }
        परिणाम = true;
    } अन्यथा {
        यदि (!_this->GL_आरोपय_Library) {
            प्रत्यागम SDL_DllNotSupported("OpenGL");
        }
        परिणाम = _this->GL_आरोपय_Library(_this, मार्गः);
    }
    यदि (परिणाम) {
        ++_this->gl_config.driver_loaded;
    } अन्यथा {
        यदि (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
    प्रत्यागम परिणाम;
}

SDL_FunctionPointer SDL_GL_Get_Proc_स्थानाङ्कः(ध्रुव वर्ण *proc)
{
    SDL_FunctionPointer func;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    func = रिक्त;
    यदि (_this->GL_Get_Proc_स्थानाङ्कः) {
        यदि (_this->gl_config.driver_loaded) {
            func = _this->GL_Get_Proc_स्थानाङ्कः(_this, proc);
        } अन्यथा {
            SDL_समुच्चयः_Error("No GL driver has been loaded");
        }
    } अन्यथा {
        SDL_समुच्चयः_Error("No dynamic GL support in current SDL video driver (%s)", _this->name);
    }
    प्रत्यागम func;
}

SDL_FunctionPointer SDL_EGL_Get_Proc_स्थानाङ्कः(ध्रुव वर्ण *proc)
{
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    SDL_FunctionPointer func;

    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    func = रिक्त;

    यदि (_this->egl_दत्त) {
        func = SDL_EGL_Get_Proc_स्थानाङ्कः_आन्तरिकम्(_this, proc);
    } अन्यथा {
        SDL_समुच्चयः_Error("No EGL library has been loaded");
    }

    प्रत्यागम func;
#अन्यथा
    SDL_समुच्चयः_Error("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#यदि_अन्तः
}

शून्य SDL_GL_UnloadLibrary(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम;
    }
    यदि (_this->gl_config.driver_loaded > 0) {
        यदि (--_this->gl_config.driver_loaded > 0) {
            प्रत्यागम;
        }
        यदि (_this->GL_UnloadLibrary) {
            _this->GL_UnloadLibrary(_this);
        }
    }
}

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
प्रकारनिर्देश GLenum (APIENTRY* PFNGLGETERRORPROC) (शून्य);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
प्रकारनिर्देश ध्रुव GLubyte *(APIENTRY* PFNGLGETSTRINGPROC) (GLenum name);
प्रकारनिर्देश शून्य (APIENTRY* PFNGLENABLEPROC) (GLenum cap);
#यदि_अपरिभाषितम् SDL_VIDEO_OPENGL
प्रकारनिर्देश ध्रुव GLubyte *(APIENTRY* PFNGLGETSTRINGIPROC) (GLenum name, GLuint सूचकांक);
#यदि_अन्तः

स्थिर SDL_INLINE bool is_At_न्यूनतमम्_GL3(ध्रुव वर्ण *verstr)
{
    प्रत्यागम verstr && (SDL_atoi(verstr) >= 3);
}
#यदि_अन्तः // SDL_VIDEO_OPENGL || SDL_VIDEO_OPENGL_ES || SDL_VIDEO_OPENGL_ES2

bool SDL_GL_ExtensionSupported(ध्रुव वर्ण *extension)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETSTRINGPROC glGetStringFunc;
    ध्रुव वर्ण *extensions;
    ध्रुव वर्ण *start;
    ध्रुव वर्ण *where, *terminator;

    // Extension names should not have spaces.
    where = SDL_strchr(extension, ' ');
    यदि (where || *extension == '\0') {
        प्रत्यागम false;
    }
    // See if there's a hint or environment variable override
    start = SDL_GetHint(extension);
    यदि (start && *start == '0') {
        प्रत्यागम false;
    }

    // Lookup the available extensions

    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetString");
    यदि (!glGetStringFunc) {
        प्रत्यागम false;
    }

    यदि (is_At_न्यूनतमम्_GL3((ध्रुव वर्ण *)glGetStringFunc(GL_संस्करणम्))) {
        PFNGLGETSTRINGIPROC glGetStringiFunc;
        PFNGLGETINTEGERVPROC glGetIntegervFunc;
        GLint अङ्कः_exts = 0;
        GLint i;

        glGetStringiFunc = (PFNGLGETSTRINGIPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetStringi");
        glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetIntegerv");
        यदि ((!glGetStringiFunc) || (!glGetIntegervFunc)) {
            प्रत्यागम false;
        }

#यदि_अपरिभाषितम् GL_अङ्कः_EXTENSIONS
#परिभाषय GL_अङ्कः_EXTENSIONS 0x821D
#यदि_अन्तः
        glGetIntegervFunc(GL_अङ्कः_EXTENSIONS, &अङ्कः_exts);
        प्रति (i = 0; i < अङ्कः_exts; i++) {
            ध्रुव वर्ण *thisext = (ध्रुव वर्ण *)glGetStringiFunc(GL_EXTENSIONS, i);
            यदि (SDL_strcmp(thisext, extension) == 0) {
                प्रत्यागम true;
            }
        }

        प्रत्यागम false;
    }

    // Try the old way with glGetString(GL_EXTENSIONS) ...

    extensions = (ध्रुव वर्ण *)glGetStringFunc(GL_EXTENSIONS);
    यदि (!extensions) {
        प्रत्यागम false;
    }
    /*
     * It takes a bit of care to be fool-proof about parsing the OpenGL
     * extensions string. Don't be fooled by sub-strings, etc.
     */

    start = extensions;

    प्रति (;;) {
        where = SDL_strstr(start, extension);
        यदि (!where) {
            भङ्ग;
        }

        terminator = where + SDL_strlen(extension);
        यदि (where == extensions || *(where - 1) == ' ') {
            यदि (*terminator == ' ' || *terminator == '\0') {
                प्रत्यागम true;
            }
        }

        start = terminator;
    }
    प्रत्यागम false;
#अन्यथा
    प्रत्यागम false;
#यदि_अन्तः
}

/* Deduce supported ES profile versions from the supported
   ARB_ES*_compatibility extensions. There is no direct query.

   This is normally only called when the OpenGL driver supports
   {GLX,WGL}_EXT_create_context_es2_profile.
 */
शून्य SDL_GL_DeduceMaxSupportedESProfile(पूर्णाङ्क *major, पूर्णाङ्क *minor)
{
// THIS REQUIRES AN EXISTING GL CONTEXT THAT HAS BEEN MADE CURRENT.
// Please refer to https://bugzilla.libsdl.org/show_bug.cgi?id=3725 for discussion.
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    /* XXX This is fragile; it will break in the event of release of
     * new versions of OpenGL ES.
     */
    यदि (SDL_GL_ExtensionSupported("GL_ARB_ES3_2_compatibility")) {
        *major = 3;
        *minor = 2;
    } अन्यथा यदि (SDL_GL_ExtensionSupported("GL_ARB_ES3_1_compatibility")) {
        *major = 3;
        *minor = 1;
    } अन्यथा यदि (SDL_GL_ExtensionSupported("GL_ARB_ES3_compatibility")) {
        *major = 3;
        *minor = 0;
    } अन्यथा {
        *major = 2;
        *minor = 0;
    }
#यदि_अन्तः
}

शून्य SDL_EGL_समुच्चयः_Attribute_Callbacks(SDL_EGLAttribArrayCallback platformAttribCallback,
                                   SDL_EGLIntArrayCallback surfaceAttribCallback,
                                   SDL_EGLIntArrayCallback contextAttribCallback,
                                   शून्य *userdata)
{
    यदि (!_this) {
        प्रत्यागम;
    }
    _this->egl_platformattrib_callback = platformAttribCallback;
    _this->egl_surfaceattrib_callback = surfaceAttribCallback;
    _this->egl_contextattrib_callback = contextAttribCallback;
    _this->egl_attrib_callback_userdata = userdata;
}

शून्य SDL_GL_Reset_गुणाः(शून्य)
{
    यदि (!_this) {
        प्रत्यागम;
    }

    _this->egl_platformattrib_callback = रिक्त;
    _this->egl_surfaceattrib_callback = रिक्त;
    _this->egl_contextattrib_callback = रिक्त;
    _this->egl_attrib_callback_userdata = रिक्त;

    _this->gl_config.red_आकार = 8;
    _this->gl_config.green_आकार = 8;
    _this->gl_config.blue_आकार = 8;
    _this->gl_config.alpha_आकार = 8;
    _this->gl_config.बफर_आकार = 0;
    _this->gl_config.गभीरता_आकार = 16;
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

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    _this->gl_config.major_संस्करणम् = 2;
    _this->gl_config.minor_संस्करणम् = 1;
    _this->gl_config.profile_आवरणम् = 0;
#नोचेद्यदि defined(SDL_VIDEO_OPENGL_ES2)
    _this->gl_config.major_संस्करणम् = 2;
    _this->gl_config.minor_संस्करणम् = 0;
    _this->gl_config.profile_आवरणम् = SDL_GL_CONTEXT_PROFILE_ES;
#नोचेद्यदि defined(SDL_VIDEO_OPENGL_ES)
    _this->gl_config.major_संस्करणम् = 1;
    _this->gl_config.minor_संस्करणम् = 1;
    _this->gl_config.profile_आवरणम् = SDL_GL_CONTEXT_PROFILE_ES;
#यदि_अन्तः

    _this->gl_config.flags = 0;
    _this->gl_config.framebuffer_srgb_capable = 0;
    _this->gl_config.no_error = 0;
    _this->gl_config.release_behavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH;
    _this->gl_config.reset_notification = SDL_GL_CONTEXT_RESET_NO_NOTIFICATION;

    _this->gl_config.share_with_current_context = 0;

    _this->gl_config.egl_platform = 0;

    यदि (_this->GL_समुच्चयः_Default_Profile_Config) {
        _this->GL_समुच्चयः_Default_Profile_Config(_this);
    }
}

bool SDL_GL_समुच्चयः_Attribute(SDL_GLAttr attr, पूर्णाङ्क मानम्)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    bool परिणाम;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    परिणाम = true;
    विकल्प (attr) {
    पक्ष SDL_GL_RED_आकार:
        _this->gl_config.red_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_GREEN_आकार:
        _this->gl_config.green_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_BLUE_आकार:
        _this->gl_config.blue_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ALPHA_आकार:
        _this->gl_config.alpha_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_DOUBLEBUFFER:
        _this->gl_config.double_बफर = मानम्;
        भङ्ग;
    पक्ष SDL_GL_बफर_आकार:
        _this->gl_config.बफर_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_गभीरता_आकार:
        _this->gl_config.गभीरता_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_STENCIL_आकार:
        _this->gl_config.stencil_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_RED_आकार:
        _this->gl_config.accum_red_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_GREEN_आकार:
        _this->gl_config.accum_green_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_BLUE_आकार:
        _this->gl_config.accum_blue_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_ALPHA_आकार:
        _this->gl_config.accum_alpha_आकार = मानम्;
        भङ्ग;
    पक्ष SDL_GL_STEREO:
        _this->gl_config.stereo = मानम्;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLEBUFFERS:
        _this->gl_config.multisamplebuffers = मानम्;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLESAMPLES:
        _this->gl_config.multisamplesamples = मानम्;
        भङ्ग;
    पक्ष SDL_GL_FLOATBUFFERS:
        _this->gl_config.floatbuffers = मानम्;
        भङ्ग;
    पक्ष SDL_GL_ACCELERATED_VISUAL:
        _this->gl_config.accelerated = मानम्;
        भङ्ग;
    पक्ष SDL_GL_RETAINED_BACKING:
        _this->gl_config.retained_backing = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_MAJOR_संस्करणम्:
        _this->gl_config.major_संस्करणम् = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_MINOR_संस्करणम्:
        _this->gl_config.minor_संस्करणम् = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_FLAGS:
        यदि (मानम् & ~(SDL_GL_CONTEXT_DEBUG_FLAG |
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG |
                      SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG |
                      SDL_GL_CONTEXT_RESET_ISOLATION_FLAG)) {
            परिणाम = SDL_समुच्चयः_Error("Unknown OpenGL context flag %d", मानम्);
            भङ्ग;
        }
        _this->gl_config.flags = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_PROFILE_आवरणम्:
        यदि (मानम् != 0 &&
            मानम् != SDL_GL_CONTEXT_PROFILE_CORE &&
            मानम् != SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
            मानम् != SDL_GL_CONTEXT_PROFILE_ES) {
            परिणाम = SDL_समुच्चयः_Error("Unknown OpenGL context profile %d", मानम्);
            भङ्ग;
        }
        _this->gl_config.profile_आवरणम् = मानम्;
        भङ्ग;
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
        _this->gl_config.share_with_current_context = मानम्;
        भङ्ग;
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
        _this->gl_config.framebuffer_srgb_capable = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        _this->gl_config.release_behavior = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RESET_NOTIFICATION:
        _this->gl_config.reset_notification = मानम्;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
        _this->gl_config.no_error = मानम्;
        भङ्ग;
    पक्ष SDL_GL_EGL_PLATFORM:
        _this->gl_config.egl_platform = मानम्;
        भङ्ग;
    स्वभाव:
        परिणाम = SDL_समुच्चयः_Error("Unknown OpenGL attribute");
        भङ्ग;
    }
    प्रत्यागम परिणाम;
#अन्यथा
    प्रत्यागम SDL_Unsupported();
#यदि_अन्तः // SDL_VIDEO_OPENGL
}

bool SDL_GL_GetAttribute(SDL_GLAttr attr, पूर्णाङ्क *मानम्)
{
#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    PFNGLGETERRORPROC glGetErrorFunc;
    GLenum attrib = 0;
    GLenum error = 0;

    /*
     * Some queries in Core Profile desktop OpenGL 3+ contexts require
     * glGetFramebufferAttachmentParameteriv instead of glGetIntegerv. Note that
     * the enums we use for the former function don't exist in OpenGL ES 2, and
     * the function itself doesn't exist prior to OpenGL 3 and OpenGL ES 2.
     */
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    PFNGLGETSTRINGPROC glGetStringFunc;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivFunc;
    GLenum attachment = GL_पृष्ठभागः_वामः;
    GLenum attachmentattrib = 0;
#यदि_अन्तः

    CHECK_PARAM(!मानम्) {
        प्रत्यागम SDL_InvalidParamError("value");
    }

    // Clear value in any case
    *मानम् = 0;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    विकल्प (attr) {
    पक्ष SDL_GL_RED_आकार:
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_RED_आकार;
#यदि_अन्तः
        attrib = GL_RED_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_BLUE_आकार:
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_BLUE_आकार;
#यदि_अन्तः
        attrib = GL_BLUE_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_GREEN_आकार:
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_GREEN_आकार;
#यदि_अन्तः
        attrib = GL_GREEN_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_ALPHA_आकार:
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_आकार;
#यदि_अन्तः
        attrib = GL_ALPHA_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_DOUBLEBUFFER:
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        attrib = GL_DOUBLEBUFFER;
        भङ्ग;
#अन्यथा
        // OpenGL ES 1.0 and above specifications have EGL_SINGLE_BUFFER
        // parameter which switches double buffer to single buffer. OpenGL ES
        // SDL driver must set proper value after initialization
        *मानम् = _this->gl_config.double_बफर;
        प्रत्यागम true;
#यदि_अन्तः
    पक्ष SDL_GL_गभीरता_आकार:
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        attachment = GL_गभीरता;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_गभीरता_आकार;
#यदि_अन्तः
        attrib = GL_गभीरता_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_STENCIL_आकार:
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
        attachment = GL_STENCIL;
        attachmentattrib = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_आकार;
#यदि_अन्तः
        attrib = GL_STENCIL_द्वयङ्काः;
        भङ्ग;
#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    पक्ष SDL_GL_ACCUM_RED_आकार:
        attrib = GL_ACCUM_RED_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_GREEN_आकार:
        attrib = GL_ACCUM_GREEN_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_BLUE_आकार:
        attrib = GL_ACCUM_BLUE_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_ACCUM_ALPHA_आकार:
        attrib = GL_ACCUM_ALPHA_द्वयङ्काः;
        भङ्ग;
    पक्ष SDL_GL_STEREO:
        attrib = GL_STEREO;
        भङ्ग;
#अन्यथा
    पक्ष SDL_GL_ACCUM_RED_आकार:
    पक्ष SDL_GL_ACCUM_GREEN_आकार:
    पक्ष SDL_GL_ACCUM_BLUE_आकार:
    पक्ष SDL_GL_ACCUM_ALPHA_आकार:
    पक्ष SDL_GL_STEREO:
        // none of these are supported in OpenGL ES
        *मानम् = 0;
        प्रत्यागम true;
#यदि_अन्तः
    पक्ष SDL_GL_MULTISAMPLEBUFFERS:
        attrib = GL_SAMPLE_BUFFERS;
        भङ्ग;
    पक्ष SDL_GL_MULTISAMPLESAMPLES:
        attrib = GL_SAMPLES;
        भङ्ग;
    पक्ष SDL_GL_CONTEXT_RELEASE_BEHAVIOR:
        attrib = GL_CONTEXT_RELEASE_BEHAVIOR;
        भङ्ग;
    पक्ष SDL_GL_बफर_आकार:
    {
        पूर्णाङ्क rsize = 0, gsize = 0, bsize = 0, asize = 0;

        // There doesn't seem to be a single flag in OpenGL for this!
        यदि (!SDL_GL_GetAttribute(SDL_GL_RED_आकार, &rsize)) {
            प्रत्यागम false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_GREEN_आकार, &gsize)) {
            प्रत्यागम false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_BLUE_आकार, &bsize)) {
            प्रत्यागम false;
        }
        यदि (!SDL_GL_GetAttribute(SDL_GL_ALPHA_आकार, &asize)) {
            प्रत्यागम false;
        }

        *मानम् = rsize + gsize + bsize + asize;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_ACCELERATED_VISUAL:
    {
        // Note that we can _not_ reasonably detect this once we have a context.
        *मानम् = (_this->gl_config.accelerated != 0);
        प्रत्यागम true;
    }
    पक्ष SDL_GL_RETAINED_BACKING:
    {
        *मानम् = _this->gl_config.retained_backing;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_MAJOR_संस्करणम्:
    {
        *मानम् = _this->gl_config.major_संस्करणम्;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_MINOR_संस्करणम्:
    {
        *मानम् = _this->gl_config.minor_संस्करणम्;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_FLAGS:
    {
        *मानम् = _this->gl_config.flags;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_PROFILE_आवरणम्:
    {
        *मानम् = _this->gl_config.profile_आवरणम्;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_SHARE_WITH_CURRENT_CONTEXT:
    {
        *मानम् = _this->gl_config.share_with_current_context;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_FRAMEBUFFER_SRGB_CAPABLE:
    {
        *मानम् = _this->gl_config.framebuffer_srgb_capable;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_CONTEXT_NO_ERROR:
    {
        *मानम् = _this->gl_config.no_error;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_EGL_PLATFORM:
    {
        *मानम् = _this->gl_config.egl_platform;
        प्रत्यागम true;
    }
    पक्ष SDL_GL_FLOATBUFFERS:
    {
        यदि (_this->gl_config.HAS_GL_ARB_color_बफर_float) {
            attrib = GL_RGBA_FLOAT_बहुलकम्_ARB;
            भङ्ग;
        } अन्यथा {
            प्रत्यागम 0;
        }
    }
    स्वभाव:
        प्रत्यागम SDL_समुच्चयः_Error("Unknown OpenGL attribute");
    }

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetString");
    यदि (!glGetStringFunc) {
        प्रत्यागम false;
    }

    यदि (attachmentattrib && is_At_न्यूनतमम्_GL3((ध्रुव वर्ण *)glGetStringFunc(GL_संस्करणम्))) {
        // glGetFramebufferAttachmentParameteriv needs to operate on the window framebuffer for this, so bind FBO 0 if necessary.
        GLint current_fbo = 0;
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC) SDL_GL_Get_Proc_स्थानाङ्कः("glGetIntegerv");
        PFNGLBINDFRAMEBUFFERPROC glBindFramebufferFunc = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glBindFramebuffer");
        यदि (glGetIntegervFunc && glBindFramebufferFunc) {
            glGetIntegervFunc(GL_DRAW_FRAMEBUFFER_BINDING, &current_fbo);
        }

        glGetFramebufferAttachmentParameterivFunc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetFramebufferAttachmentParameteriv");
        यदि (glGetFramebufferAttachmentParameterivFunc) {
            यदि (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, 0);
            }
            // glGetFramebufferAttachmentParameterivFunc may cause GL_INVALID_OPERATION when querying depth/stencil size if the
            // bits is 0. From the GL docs:
            //      If the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE, then either no framebuffer is bound to target;
            //      or a default framebuffer is queried, attachment is GL_DEPTH or GL_STENCIL, and the number of depth or stencil bits,
            //      respectively, is zero. In this case querying pname GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME will return zero, and all
            //      other queries will generate an error.
            GLint fbo_type = GL_FRAMEBUFFER_DEFAULT;
            यदि (attachment == GL_गभीरता || attachment == GL_STENCIL) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &fbo_type);
            }
            यदि (fbo_type != GL_NONE) {
                glGetFramebufferAttachmentParameterivFunc(GL_FRAMEBUFFER, attachment, attachmentattrib, (GLint *)मानम्);
            } अन्यथा {
                *मानम् = 0;
            }
            यदि (glBindFramebufferFunc && (current_fbo != 0)) {
                glBindFramebufferFunc(GL_DRAW_FRAMEBUFFER, current_fbo);
            }
        } अन्यथा {
            प्रत्यागम false;
        }
    } अन्यथा
#यदि_अन्तः
    {
        PFNGLGETINTEGERVPROC glGetIntegervFunc = (PFNGLGETINTEGERVPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetIntegerv");
        यदि (glGetIntegervFunc) {
            glGetIntegervFunc(attrib, (GLint *)मानम्);
        } अन्यथा {
            प्रत्यागम false;
        }
    }

    glGetErrorFunc = (PFNGLGETERRORPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetError");
    यदि (!glGetErrorFunc) {
        प्रत्यागम false;
    }

    error = glGetErrorFunc();
    यदि (error != GL_NO_ERROR) {
        यदि (error == GL_INVALID_ENUM) {
            प्रत्यागम SDL_समुच्चयः_Error("OpenGL error: GL_INVALID_ENUM");
        } अन्यथा यदि (error == GL_INVALID_मानम्) {
            प्रत्यागम SDL_समुच्चयः_Error("OpenGL error: GL_INVALID_VALUE");
        }
        प्रत्यागम SDL_समुच्चयः_Error("OpenGL error: %08X", error);
    }

    // convert GL_CONTEXT_RELEASE_BEHAVIOR values back to SDL_GL_CONTEXT_RELEASE_BEHAVIOR values
    यदि (attr == SDL_GL_CONTEXT_RELEASE_BEHAVIOR) {
        *मानम् = (*मानम् == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH) ? SDL_GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH : SDL_GL_CONTEXT_RELEASE_BEHAVIOR_NONE;
    }

    प्रत्यागम true;
#अन्यथा
    प्रत्यागम SDL_Unsupported();
#यदि_अन्तः // SDL_VIDEO_OPENGL
}

#परिभाषय NOT_AN_OPENGL_गवाक्षः "The specified window isn't an OpenGL window"

SDL_GLContext SDL_GL_CreateContext(SDL_गवाक्षः *गवाक्षः)
{
    SDL_GLContext ctx = रिक्त;
    CHECK_गवाक्षः_MAGIC(गवाक्षः, रिक्त);

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_OPENGL)) {
        SDL_समुच्चयः_Error(NOT_AN_OPENGL_गवाक्षः);
        प्रत्यागम रिक्त;
    }

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    पूर्णाङ्क srgb_requested = -1;
    ध्रुव वर्ण *srgbhint = SDL_GetHint(SDL_HINT_OPENGL_FORCE_SRGB_FRAMEBUFFER);
    यदि (srgbhint && *srgbhint) {
        srgb_requested = SDL_GetStringBoolean(srgbhint, false) ? 1 : 0;
    }

#यदि_अन्तः

    ctx = _this->GL_CreateContext(_this, गवाक्षः);

    // Creating a context is assumed to make it current in the SDL driver.
    यदि (ctx) {
        _this->current_glwin = गवाक्षः;
        _this->current_glctx = ctx;
        SDL_समुच्चयः_TLS(&_this->current_glwin_tls, गवाक्षः, रिक्त);
        SDL_समुच्चयः_TLS(&_this->current_glctx_tls, ctx, रिक्त);
    }

#यदि defined(SDL_VIDEO_OPENGL) || defined(SDL_VIDEO_OPENGL_ES) || defined(SDL_VIDEO_OPENGL_ES2)
    // try to force the window framebuffer to the requested sRGB state.
    यदि (srgb_requested != -1) {
        PFNGLENABLEPROC glToggleFunc = (PFNGLENABLEPROC) SDL_GL_Get_Proc_स्थानाङ्कः(srgb_requested ? "glEnable" : "glDisable");
        PFNGLGETSTRINGPROC glGetStringFunc = (PFNGLGETSTRINGPROC)SDL_GL_Get_Proc_स्थानाङ्कः("glGetString");
        यदि (glToggleFunc && glGetStringFunc) {
            bool supported = false;
            यदि (_this->gl_config.profile_आवरणम् & SDL_GL_CONTEXT_PROFILE_ES) {
                supported = SDL_GL_ExtensionSupported("GL_EXT_sRGB_write_control");  // GL_FRAMEBUFFER_SRGB is not core in any GLES version at the moment.
            } अन्यथा {
                supported = is_At_न्यूनतमम्_GL3((ध्रुव वर्ण *)glGetStringFunc(GL_संस्करणम्)) ||  // no extensions needed in OpenGL 3+.
                            SDL_GL_ExtensionSupported("GL_EXT_framebuffer_sRGB") ||
                            SDL_GL_ExtensionSupported("GL_ARB_framebuffer_sRGB");
            }

            यदि (supported) {
                glToggleFunc(GL_FRAMEBUFFER_SRGB);
            }
        }
    }
#यदि_अन्तः

    प्रत्यागम ctx;
}

bool SDL_GL_MakeCurrent(SDL_गवाक्षः *गवाक्षः, SDL_GLContext context)
{
    bool परिणाम;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }

    यदि (गवाक्षः == SDL_GL_Get_Current_गवाक्षः() &&
        context == SDL_GL_GetCurrentContext()) {
        // We're already current.
        प्रत्यागम true;
    }

    यदि (!context) {
        गवाक्षः = रिक्त;
    } अन्यथा यदि (गवाक्षः) {
        CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_OPENGL)) {
            प्रत्यागम SDL_समुच्चयः_Error(NOT_AN_OPENGL_गवाक्षः);
        }
    } अन्यथा यदि (!_this->gl_allow_no_surface) {
        प्रत्यागम SDL_समुच्चयः_Error("Use of OpenGL without a window is not supported on this platform");
    }

    परिणाम = _this->GL_MakeCurrent(_this, गवाक्षः, context);
    यदि (परिणाम) {
        _this->current_glwin = गवाक्षः;
        _this->current_glctx = context;
        SDL_समुच्चयः_TLS(&_this->current_glwin_tls, गवाक्षः, रिक्त);
        SDL_समुच्चयः_TLS(&_this->current_glctx_tls, context, रिक्त);
    }
    प्रत्यागम परिणाम;
}

SDL_गवाक्षः *SDL_GL_Get_Current_गवाक्षः(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम (SDL_गवाक्षः *)SDL_GetTLS(&_this->current_glwin_tls);
}

SDL_GLContext SDL_GL_GetCurrentContext(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम (SDL_GLContext)SDL_GetTLS(&_this->current_glctx_tls);
}

SDL_EGLDisplay SDL_EGL_GetCurrentDisplay(शून्य)
{
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम EGL_NO_DISPLAY;
    }
    यदि (!_this->egl_दत्त) {
        SDL_समुच्चयः_Error("There is no current EGL display");
        प्रत्यागम EGL_NO_DISPLAY;
    }
    प्रत्यागम _this->egl_दत्त->egl_display;
#अन्यथा
    SDL_समुच्चयः_Error("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#यदि_अन्तः
}

SDL_EGLConfig SDL_EGL_GetCurrentConfig(शून्य)
{
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (!_this->egl_दत्त) {
        SDL_समुच्चयः_Error("There is no current EGL display");
        प्रत्यागम रिक्त;
    }
    प्रत्यागम _this->egl_दत्त->egl_config;
#अन्यथा
    SDL_समुच्चयः_Error("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#यदि_अन्तः
}

SDL_EGLConfig SDL_EGL_Get_गवाक्षः_Surface(SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (!_this->egl_दत्त) {
        SDL_समुच्चयः_Error("There is no current EGL display");
        प्रत्यागम रिक्त;
    }
    यदि (_this->GL_GetEGLSurface) {
        प्रत्यागम _this->GL_GetEGLSurface(_this, गवाक्षः);
    }
    प्रत्यागम रिक्त;
#अन्यथा
    SDL_समुच्चयः_Error("SDL was not built with EGL support");
    प्रत्यागम रिक्त;
#यदि_अन्तः
}

bool SDL_GL_समुच्चयः_Swap_Interval(पूर्णाङ्क interval)
{
    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    } अन्यथा यदि (SDL_GL_GetCurrentContext() == रिक्त) {
        प्रत्यागम SDL_समुच्चयः_Error("No OpenGL context has been made current");
    } अन्यथा यदि (_this->GL_समुच्चयः_Swap_Interval) {
        प्रत्यागम _this->GL_समुच्चयः_Swap_Interval(_this, interval);
    } अन्यथा {
        प्रत्यागम SDL_समुच्चयः_Error("Setting the swap interval is not supported");
    }
}

bool SDL_GL_GetSwapInterval(पूर्णाङ्क *interval)
{
    CHECK_PARAM(!interval) {
       प्रत्यागम SDL_InvalidParamError("interval");
    }

    *interval = 0;

    यदि (!_this) {
        प्रत्यागम SDL_समुच्चयः_Error("no video driver");
    } अन्यथा यदि (SDL_GL_GetCurrentContext() == रिक्त) {
        प्रत्यागम SDL_समुच्चयः_Error("no current context");
    } अन्यथा यदि (_this->GL_GetSwapInterval) {
        प्रत्यागम _this->GL_GetSwapInterval(_this, interval);
    } अन्यथा {
        प्रत्यागम SDL_समुच्चयः_Error("not implemented");
    }
}

bool SDL_GL_Swap_गवाक्षः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_OPENGL)) {
        प्रत्यागम SDL_समुच्चयः_Error(NOT_AN_OPENGL_गवाक्षः);
    }

    यदि (SDL_GL_Get_Current_गवाक्षः() != गवाक्षः) {
        प्रत्यागम SDL_समुच्चयः_Error("The specified window has not been made current");
    }

    प्रत्यागम _this->GL_Swap_गवाक्षः(_this, गवाक्षः);
}

bool SDL_GL_DestroyContext(SDL_GLContext context)
{
    CHECK_PARAM(!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    CHECK_PARAM(!context) {
        प्रत्यागम SDL_InvalidParamError("context");
    }

    यदि (SDL_GL_GetCurrentContext() == context) {
        SDL_GL_MakeCurrent(रिक्त, रिक्त);
    }

    प्रत्यागम _this->GL_DestroyContext(_this, context);
}

#यदि 0 // FIXME
/*
 * Utility function used by SDL_WM_SetIcon(); flags & 1 for color key, flags
 * & 2 for alpha channel.
 */
स्थिर शून्य Create_आवरणम्_From_Color_कुञ्चिका_Or_Alpha(SDL_Surface *icon, Uint8 *आवरणम्, पूर्णाङ्क flags)
{
    पूर्णाङ्क x, y;
    Uint32 colorkey;
#परिभाषय समुच्चयः_MASKBIT(icon, x, y, आवरणम्) \
    आवरणम्[(y * ((icon->w + 7) / 8)) + (x / 8)] &= ~(0x01 << (7 - (x % 8)))

    colorkey = icon->format->colorkey;
    विकल्प (SDL_BYTESPERPIXEL(icon->format)) {
    पक्ष 1:
        {
            Uint8 *pixels;
            प्रति (y = 0; y < icon->h; ++y) {
                pixels = (Uint8 *) icon->pixels + y * icon->pitch;
                प्रति (x = 0; x < icon->w; ++x) {
                    यदि (*pixels++ == colorkey) {
                        समुच्चयः_MASKBIT(icon, x, y, आवरणम्);
                    }
                }
            }
        }
        भङ्ग;

    पक्ष 2:
        {
            Uint16 *pixels;
            प्रति (y = 0; y < icon->h; ++y) {
                pixels = (Uint16 *) icon->pixels + y * icon->pitch / 2;
                प्रति (x = 0; x < icon->w; ++x) {
                    यदि ((flags & 1) && *pixels == colorkey) {
                        समुच्चयः_MASKBIT(icon, x, y, आवरणम्);
                    } अन्यथा यदि ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        समुच्चयः_MASKBIT(icon, x, y, आवरणम्);
                    }
                    pixels++;
                }
            }
        }
        भङ्ग;

    पक्ष 4:
        {
            Uint32 *pixels;
            प्रति (y = 0; y < icon->h; ++y) {
                pixels = (Uint32 *) icon->pixels + y * icon->pitch / 4;
                प्रति (x = 0; x < icon->w; ++x) {
                    यदि ((flags & 1) && *pixels == colorkey) {
                        समुच्चयः_MASKBIT(icon, x, y, आवरणम्);
                    } अन्यथा यदि ((flags & 2)
                               && (*pixels & icon->format->Amask) == 0) {
                        समुच्चयः_MASKBIT(icon, x, y, आवरणम्);
                    }
                    pixels++;
                }
            }
        }
        भङ्ग;
    }
}

/*
 * Sets the window manager icon for the display window.
 */
शून्य SDL_WM_समुच्चयः_Icon(SDL_Surface *icon, Uint8 *आवरणम्)
{
    यदि (icon && _this->समुच्चयः_Icon) {
        // Generate a mask if necessary, and create the icon!
        यदि (आवरणम् == रिक्त) {
            पूर्णाङ्क आवरणम्_len = icon->h * (icon->w + 7) / 8;
            पूर्णाङ्क flags = 0;
            आवरणम् = (Uint8 *) SDL_malloc(आवरणम्_len);
            यदि (आवरणम् == रिक्त) {
                प्रत्यागम;
            }
            SDL_memset(आवरणम्, ~0, आवरणम्_len);
            यदि (icon->flags & SDL_SRCCOLORKEY)
                flags |= 1;
            यदि (icon->flags & SDL_SRCALPHA)
                flags |= 2;
            यदि (flags) {
                Create_आवरणम्_From_Color_कुञ्चिका_Or_Alpha(icon, आवरणम्, flags);
            }
            _this->समुच्चयः_Icon(_this, icon, आवरणम्);
            SDL_free(आवरणम्);
        } अन्यथा {
            _this->समुच्चयः_Icon(_this, icon, आवरणम्);
        }
    }
}
#यदि_अन्तः

SDL_Text_निवेशः_Type SDL_Get_Text_निवेशः_Type(SDL_PropertiesID props)
{
    प्रत्यागम (SDL_Text_निवेशः_Type)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_TEXTINPUT_TYPE_सङ्ख्या, SDL_TEXTINPUT_TYPE_TEXT);
}

SDL_Capitalization SDL_Get_Text_निवेशः_Capitalization(SDL_PropertiesID props)
{
    यदि (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_सङ्ख्या)) {
        प्रत्यागम (SDL_Capitalization)SDL_Get_सङ्ख्या_Property(props, SDL_PROP_TEXTINPUT_CAPITALIZATION_सङ्ख्या, SDL_CAPITALIZE_NONE);
    }

    विकल्प (SDL_Get_Text_निवेशः_Type(props)) {
    पक्ष SDL_TEXTINPUT_TYPE_TEXT:
        प्रत्यागम SDL_CAPITALIZE_SENTENCES;
    पक्ष SDL_TEXTINPUT_TYPE_TEXT_NAME:
        प्रत्यागम SDL_CAPITALIZE_शब्दाः;
    स्वभाव:
        प्रत्यागम SDL_CAPITALIZE_NONE;
    }
}

bool SDL_Get_Text_निवेशः_Autocorrect(SDL_PropertiesID props)
{
    प्रत्यागम SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_AUTOCORRECT_BOOLEAN, true);
}

bool SDL_Get_Text_निवेशः_Multiline(SDL_PropertiesID props)
{
    यदि (SDL_HasProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN)) {
        प्रत्यागम SDL_GetBooleanProperty(props, SDL_PROP_TEXTINPUT_MULTILINE_BOOLEAN, false);
    }

    यदि (SDL_GetHintBoolean(SDL_HINT_RETURN_कुञ्चिका_HIDES_IME, false)) {
        प्रत्यागम false;
    } अन्यथा {
        प्रत्यागम true;
    }
}

स्थिर bool AutoShowingScreenKeyboard(शून्य)
{
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_ENABLE_SCREEN_KEYBOARD);
    यदि (!hint) {
        // This hint is currently only used by the X11 video driver
        यदि (SDL_strcmp(_this->name, "x11") == 0) {
            hint = SDL_GetHint(SDL_HINT_ENABLE_STEAM_SCREEN_KEYBOARD);
        }
    }
    यदि (((!hint || SDL_strcasecmp(hint, "auto") == 0) && !SDL_HasKeyboard()) ||
        SDL_GetStringBoolean(hint, false)) {
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम false;
    }
}

bool SDL_Start_Text_निवेशः(SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम SDL_Start_Text_निवेशः_With_Properties(गवाक्षः, 0);
}

bool SDL_Start_Text_निवेशः_With_Properties(SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID props)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (गवाक्षः->text_निवेशः_props) {
        SDL_DestroyProperties(गवाक्षः->text_निवेशः_props);
        गवाक्षः->text_निवेशः_props = 0;
    }

    यदि (props) {
        गवाक्षः->text_निवेशः_props = SDL_CreateProperties();
        यदि (!गवाक्षः->text_निवेशः_props) {
            प्रत्यागम false;
        }
        यदि (!SDL_CopyProperties(props, गवाक्षः->text_निवेशः_props)) {
            प्रत्यागम false;
        }
    }

    यदि (_this->समुच्चयः_Text_निवेशः_Properties) {
        _this->समुच्चयः_Text_निवेशः_Properties(_this, गवाक्षः, props);
    }

    यदि (!गवाक्षः->text_निवेशः_सक्रिय) {
        // Start the text input system
        यदि (_this->Start_Text_निवेशः) {
            यदि (!_this->Start_Text_निवेशः(_this, गवाक्षः, props)) {
                प्रत्यागम false;
            }
        }
        गवाक्षः->text_निवेशः_सक्रिय = true;
    }

    // Show the on-screen keyboard, if desired
    यदि (AutoShowingScreenKeyboard() && !SDL_ScreenKeyboardShown(गवाक्षः)) {
        यदि (_this->ShowScreenKeyboard) {
            _this->ShowScreenKeyboard(_this, गवाक्षः, props);
        }
    }
    प्रत्यागम true;
}

bool SDL_Text_निवेशः_सक्रिय(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    प्रत्यागम गवाक्षः->text_निवेशः_सक्रिय;
}

bool SDL_Stop_Text_निवेशः(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (गवाक्षः->text_निवेशः_सक्रिय) {
        // Stop the text input system
        यदि (_this->Stop_Text_निवेशः) {
            _this->Stop_Text_निवेशः(_this, गवाक्षः);
        }
        गवाक्षः->text_निवेशः_सक्रिय = false;
    }

    // Hide the on-screen keyboard, if desired
    यदि (AutoShowingScreenKeyboard() && SDL_ScreenKeyboardShown(गवाक्षः)) {
        यदि (_this->HideScreenKeyboard) {
            _this->HideScreenKeyboard(_this, गवाक्षः);
        }
    }
    प्रत्यागम true;
}

bool SDL_समुच्चयः_Text_निवेशः_Area(SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rect, पूर्णाङ्क cursor)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (rect) {
        SDL_copyp(&गवाक्षः->text_निवेशः_rect, rect);
        गवाक्षः->text_निवेशः_cursor = cursor;
    } अन्यथा {
        SDL_zero(गवाक्षः->text_निवेशः_rect);
        गवाक्षः->text_निवेशः_cursor = 0;
    }

    यदि (_this && _this->Update_Text_निवेशः_Area) {
        यदि (!_this->Update_Text_निवेशः_Area(_this, गवाक्षः)) {
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

bool SDL_Get_Text_निवेशः_Area(SDL_गवाक्षः *गवाक्षः, SDL_Rect *rect, पूर्णाङ्क *cursor)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (rect) {
        SDL_copyp(rect, &गवाक्षः->text_निवेशः_rect);
    }
    यदि (cursor) {
        *cursor = गवाक्षः->text_निवेशः_cursor;
    }
    प्रत्यागम true;
}

bool SDL_ClearComposition(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (_this->ClearComposition) {
        प्रत्यागम _this->ClearComposition(_this, गवाक्षः);
    }
    प्रत्यागम true;
}

bool SDL_HasScreenKeyboardSupport(शून्य)
{
    यदि (_this && _this->HasScreenKeyboardSupport) {
        प्रत्यागम _this->HasScreenKeyboardSupport(_this);
    }
    प्रत्यागम false;
}

bool SDL_ScreenKeyboardShown(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    प्रत्यागम _this->screen_keyboard_shown;
}

शून्य SDL_SendScreenKeyboardShown(शून्य)
{
    यदि (!_this || _this->screen_keyboard_shown) {
        प्रत्यागम;
    }

    _this->screen_keyboard_shown = true;

    यदि (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_SHOWN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_SHOWN;
        event.common.timestamp = 0;
        SDL_प्रक्षिप_Event(&event);
    }
}

शून्य SDL_SendScreenKeyboardHidden(शून्य)
{
    यदि (!_this || !_this->screen_keyboard_shown) {
        प्रत्यागम;
    }

    _this->screen_keyboard_shown = false;

    यदि (SDL_EventEnabled(SDL_EVENT_SCREEN_KEYBOARD_HIDDEN)) {
        SDL_Event event;
        event.type = SDL_EVENT_SCREEN_KEYBOARD_HIDDEN;
        event.common.timestamp = 0;
        SDL_प्रक्षिप_Event(&event);
    }
}

पूर्णाङ्क SDL_Get_सन्देशः_Box_गणनम्(शून्य)
{
    प्रत्यागम SDL_GetAtomicInt(&SDL_messagebox_गणनम्);
}

bool SDL_Show_सन्देशः_Box(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID)
{
    पूर्णाङ्क dummybutton;
    bool परिणाम = false;
    bool show_cursor_पूर्व;
    SDL_गवाक्षः *current_गवाक्षः;
    SDL_सन्देशः_Box_दत्त mbdata;

    CHECK_PARAM(!messageboxdata) {
        प्रत्यागम SDL_InvalidParamError("messageboxdata");
    }
    CHECK_PARAM(messageboxdata->numbuttons < 0) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid number of buttons");
    }

    // in case either the title or message was a pointer from SDL_GetError(), make a copy
    // now, as we'll likely overwrite error state in here.
    bool titleisstack = false, msgisstack = false;
    वर्ण *titlecpy = रिक्त;
    वर्ण *msgcpy = रिक्त;
    यदि (messageboxdata->title) {
        ध्रुव size_t slen = SDL_strlen(messageboxdata->title) + 1;
        titlecpy = SDL_small_alloc(वर्ण, slen, &titleisstack);
        यदि (!titlecpy) {
            प्रत्यागम false;
        }
        SDL_memcpy(titlecpy, messageboxdata->title, slen);
    }

    यदि (messageboxdata->सन्देशः) {
        ध्रुव size_t slen = SDL_strlen(messageboxdata->सन्देशः) + 1;
        msgcpy = SDL_small_alloc(वर्ण, slen, &msgisstack);
        यदि (!msgcpy) {
            SDL_small_free(titlecpy, titleisstack);
            प्रत्यागम false;
        }
        SDL_memcpy(msgcpy, messageboxdata->सन्देशः, slen);
    }

    (शून्य)SDL_AtomicIncRef(&SDL_messagebox_गणनम्);

    current_गवाक्षः = SDL_GetKeyboardFocus();
    SDL_UpdateMouseCapture(false);
    SDL_समुच्चयः_Relative_Mouse_बहुलकम्(false);
    show_cursor_पूर्व = SDL_CursorVisible();
    SDL_ShowCursor();
    SDL_ResetKeyboard();

    यदि (!buttonID) {
        buttonID = &dummybutton;
    }

    SDL_memcpy(&mbdata, messageboxdata, परिमाण(*messageboxdata));
    mbdata.title = titlecpy;
    यदि (!mbdata.title) {
        mbdata.title = "";
    }
    mbdata.सन्देशः = msgcpy;
    यदि (!mbdata.सन्देशः) {
        mbdata.सन्देशः = "";
    }
    messageboxdata = &mbdata;

    SDL_ClearError();

    यदि (_this && _this->Show_सन्देशः_Box) {
        परिणाम = _this->Show_सन्देशः_Box(_this, messageboxdata, buttonID);
    } अन्यथा {
        // It's completely fine to call this function before video is initialized
        ध्रुव वर्ण *driver_name = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        यदि (driver_name && *driver_name != 0) {
            ध्रुव वर्ण *driver_attempt = driver_name;
            यावत् (driver_attempt && (*driver_attempt != 0) && !परिणाम) {
                ध्रुव वर्ण *driver_attempt_अन्तः = SDL_strchr(driver_attempt, ',');
                size_t driver_attempt_len = (driver_attempt_अन्तः) ? (driver_attempt_अन्तः - driver_attempt)
                                                                     : SDL_strlen(driver_attempt);
                प्रति (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                    यदि (bootstrap[i]->Show_सन्देशः_Box && (driver_attempt_len == SDL_strlen(bootstrap[i]->name)) &&
                        (SDL_strncasecmp(bootstrap[i]->name, driver_attempt, driver_attempt_len) == 0)) {
                        यदि (bootstrap[i]->Show_सन्देशः_Box(messageboxdata, buttonID)) {
                            परिणाम = true;
                        }
                        भङ्ग;
                    }
                }

                driver_attempt = (driver_attempt_अन्तः) ? (driver_attempt_अन्तः + 1) : रिक्त;
            }
        } अन्यथा {
            प्रति (पूर्णाङ्क i = 0; bootstrap[i]; ++i) {
                यदि (bootstrap[i]->Show_सन्देशः_Box && bootstrap[i]->Show_सन्देशः_Box(messageboxdata, buttonID)) {
                    परिणाम = true;
                    भङ्ग;
                }
            }
        }
    }

    यदि (!परिणाम) {
        ध्रुव वर्ण *error = SDL_GetError();

        यदि (!*error) {
            SDL_समुच्चयः_Error("No message system available");
        }
    } अन्यथा {
        SDL_ClearError();
    }

    (शून्य)SDL_AtomicDecRef(&SDL_messagebox_गणनम्);

    यदि (current_गवाक्षः) {
        SDL_Raise_गवाक्षः(current_गवाक्षः);
    }

    यदि (!show_cursor_पूर्व) {
        SDL_HideCursor();
    }
    SDL_Update_Relative_Mouse_बहुलकम्();
    SDL_UpdateMouseCapture(false);

    SDL_small_free(msgcpy, msgisstack);
    SDL_small_free(titlecpy, titleisstack);

    प्रत्यागम परिणाम;
}

bool SDL_Show_Simple_सन्देशः_Box(SDL_सन्देशः_Box_Flags flags, ध्रुव वर्ण *title, ध्रुव वर्ण *सन्देशः, SDL_गवाक्षः *गवाक्षः)
{
#यदि defined(SDL_PLATFORM_3DS)
    errorConf errCnf;
    bool has_Gpu_दक्षिणः;

    // If the video subsystem has not been initialised, set up graphics temporarily
    has_Gpu_दक्षिणः = gsp_Has_Gpu_दक्षिणः();
    यदि (!has_Gpu_दक्षिणः)
        gfxInitDefault();

    errorInit(&errCnf, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
    errorText(&errCnf, सन्देशः);
    errorDisp(&errCnf);

    यदि (!has_Gpu_दक्षिणः)
        gfxExit();

    प्रत्यागम true;
#अन्यथा
    SDL_सन्देशः_Box_दत्त दत्त;
    SDL_सन्देशः_Box_Button_दत्त button;

    SDL_zero(दत्त);
    दत्त.flags = flags;
    दत्त.title = title;
    दत्त.सन्देशः = सन्देशः;
    दत्त.numbuttons = 1;
    दत्त.buttons = &button;
    दत्त.गवाक्षः = गवाक्षः;

    SDL_zero(button);
    button.flags |= SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
    button.flags |= SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
    button.text = "OK";

    प्रत्यागम SDL_Show_सन्देशः_Box(&दत्त, रिक्त);
#यदि_अन्तः
}

bool SDL_ShouldAllowTopmost(शून्य)
{
    प्रत्यागम SDL_GetHintBoolean(SDL_HINT_गवाक्षः_ALLOW_TOPMOST, true);
}

bool SDL_Show_गवाक्षः_System_Menu(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);
    CHECK_गवाक्षः_NOT_POPUP(गवाक्षः, false);

    यदि (_this->Show_गवाक्षः_System_Menu) {
        _this->Show_गवाक्षः_System_Menu(गवाक्षः, x, y);
        प्रत्यागम true;
    }

    प्रत्यागम SDL_Unsupported();
}

bool SDL_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, SDL_लब्धम्_Test callback, शून्य *callback_दत्त)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!_this->समुच्चयः_गवाक्षः_लब्धम्_Test) {
        प्रत्यागम SDL_Unsupported();
    }

    गवाक्षः->लब्धम्_test = callback;
    गवाक्षः->लब्धम्_test_दत्त = callback_दत्त;

    प्रत्यागम _this->समुच्चयः_गवाक्षः_लब्धम्_Test(गवाक्षः, callback != रिक्त);
}

bool SDL_समुच्चयः_गवाक्षः_Shape(SDL_गवाक्षः *गवाक्षः, SDL_Surface *shape)
{
    SDL_PropertiesID props;
    SDL_Surface *surface;

    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT)) {
        प्रत्यागम SDL_समुच्चयः_Error("Window must be created with SDL_WINDOW_TRANSPARENT");
    }

    props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    यदि (!props) {
        प्रत्यागम false;
    }

    यदि (shape) {
        surface = SDL_ConvertSurface(shape, SDL_PIXELFORMAT_ARGB32);
        यदि (!surface) {
            प्रत्यागम false;
        }
    } अन्यथा {
        surface = रिक्त;
    }

    यदि (!SDL_समुच्चयः_Surface_Property(props, SDL_PROP_गवाक्षः_SHAPE_POINTER, surface)) {
        प्रत्यागम false;
    }

    यदि (_this->Update_गवाक्षः_Shape) {
        यदि (!_this->Update_गवाक्षः_Shape(_this, गवाक्षः, surface)) {
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

/*
 * Functions used by iOS application delegates
 */
शून्य SDL_OnApplicationWillTerminate(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_TERMINATING);
}

शून्य SDL_On_Application_Did_Receive_स्मृतिः_Warning(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_नीचः_स्मृतिः);
}

शून्य SDL_OnApplicationWillEnterBackground(शून्य)
{
    यदि (_this) {
        SDL_गवाक्षः *गवाक्षः;
        प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MINIMIZED, 0, 0);
        }
        SDL_समुच्चयः_Keyboard_Focus(रिक्त);
    }
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_BACKGROUND);
}

शून्य SDL_OnApplicationDidEnterBackground(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_BACKGROUND);
}

शून्य SDL_OnApplicationWillEnterForeground(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_WILL_ENTER_FOREGROUND);
}

शून्य SDL_OnApplicationDidEnterForeground(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_DID_ENTER_FOREGROUND);

    यदि (_this) {
        SDL_गवाक्षः *गवाक्षः;
        प्रति (गवाक्षः = _this->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
        }
    }
}

#परिभाषय NOT_A_VULKAN_गवाक्षः "The specified window isn't a Vulkan window"

bool SDL_Vulkan_आरोपय_Library(ध्रुव वर्ण *मार्गः)
{
    bool परिणाम;

    यदि (!_this) {
        प्रत्यागम SDL_UninitializedVideo();
    }
    यदि (_this->vulkan_config.loader_loaded) {
        यदि (मार्गः && SDL_strcmp(मार्गः, _this->vulkan_config.loader_मार्गः) != 0) {
            प्रत्यागम SDL_समुच्चयः_Error("Vulkan loader library already loaded");
        }
        परिणाम = true;
    } अन्यथा {
        यदि (!_this->Vulkan_आरोपय_Library) {
            प्रत्यागम SDL_DllNotSupported("Vulkan");
        }
        परिणाम = _this->Vulkan_आरोपय_Library(_this, मार्गः);
    }
    यदि (परिणाम) {
        _this->vulkan_config.loader_loaded++;
    }
    प्रत्यागम परिणाम;
}

SDL_FunctionPointer SDL_Vulkan_GetVkGetInstanceProcAddr(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम रिक्त;
    }
    यदि (!_this->vulkan_config.loader_loaded) {
        SDL_समुच्चयः_Error("No Vulkan loader has been loaded");
        प्रत्यागम रिक्त;
    }
    प्रत्यागम (SDL_FunctionPointer)_this->vulkan_config.vkGetInstanceProcAddr;
}

शून्य SDL_Vulkan_UnloadLibrary(शून्य)
{
    यदि (!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम;
    }
    यदि (_this->vulkan_config.loader_loaded > 0) {
        यदि (--_this->vulkan_config.loader_loaded > 0) {
            प्रत्यागम;
        }
        यदि (_this->Vulkan_UnloadLibrary) {
            _this->Vulkan_UnloadLibrary(_this);
        }
    }
}

वर्ण ध्रुव * ध्रुव *SDL_Vulkan_GetInstanceExtensions(Uint32 *गणनम्)
{
    Uint32 tmpcount = 0;
    यदि (!गणनम्) {
        गणनम् = &tmpcount;
    }

    यदि (!_this->Vulkan_GetInstanceExtensions) {
        *गणनम् = 0;
        SDL_Unsupported();
        प्रत्यागम रिक्त;
    }

    प्रत्यागम _this->Vulkan_GetInstanceExtensions(_this, गणनम्);
}

bool SDL_Vulkan_CreateSurface(SDL_गवाक्षः *गवाक्षः,
                                  VkInstance instance,
                                  ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator,
                                  VkSurfaceKHR *surface)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, false);

    यदि (!_this->Vulkan_CreateSurface) {
        SDL_Unsupported();
        प्रत्यागम false;
    }

    CHECK_PARAM(!instance) {
        प्रत्यागम SDL_InvalidParamError("instance");
    }

    CHECK_PARAM(!surface) {
        प्रत्यागम SDL_InvalidParamError("surface");
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_VULKAN)) {
        // No problem, we can convert to Vulkan
        यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        यदि (गवाक्षः->flags & SDL_गवाक्षः_METAL) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_METAL;
            // Nothing more to do for Metal.
        }
        यदि (SDL_Vulkan_आरोपय_Library(रिक्त)) {
            गवाक्षः->flags |= SDL_गवाक्षः_VULKAN;
        } अन्यथा {
            प्रत्यागम SDL_समुच्चयः_Error("failed to load Vulkan library");
        }
    }

    प्रत्यागम _this->Vulkan_CreateSurface(_this, गवाक्षः, instance, allocator, surface);
}

शून्य SDL_Vulkan_DestroySurface(VkInstance instance,
                               VkSurfaceKHR surface,
                               ध्रुव संरचना Vk_आवण्टनम्_Callbacks *allocator)
{
    यदि (_this && instance && surface && _this->Vulkan_DestroySurface) {
        _this->Vulkan_DestroySurface(_this, instance, surface, allocator);
    }
}

bool SDL_Vulkan_GetPresentationSupport(VkInstance instance,
                                           VkPhysicalDevice physicalDevice,
                                           Uint32 queue_Family_सूचकांक)
{
    CHECK_PARAM(!_this) {
        SDL_UninitializedVideo();
        प्रत्यागम false;
    }

    CHECK_PARAM(!instance) {
        SDL_InvalidParamError("instance");
        प्रत्यागम false;
    }

    CHECK_PARAM(!physicalDevice) {
        SDL_InvalidParamError("physicalDevice");
        प्रत्यागम false;
    }

    यदि (_this->Vulkan_GetPresentationSupport) {
        प्रत्यागम _this->Vulkan_GetPresentationSupport(_this, instance, physicalDevice, queue_Family_सूचकांक);
    }

    /* If the backend does not have this function then it does not have a
     * WSI function to query it; in other words it's not necessary to check
     * as it is always supported.
     */
    प्रत्यागम true;
}

SDL_MetalView SDL_Metal_CreateView(SDL_गवाक्षः *गवाक्षः)
{
    CHECK_गवाक्षः_MAGIC(गवाक्षः, रिक्त);

    यदि (!_this->Metal_CreateView) {
        SDL_Unsupported();
        प्रत्यागम रिक्त;
    }

    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_METAL)) {
        // No problem, we can convert to Metal
        यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_OPENGL;
            SDL_GL_UnloadLibrary();
        }
        यदि (गवाक्षः->flags & SDL_गवाक्षः_VULKAN) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_VULKAN;
            SDL_Vulkan_UnloadLibrary();
        }
        गवाक्षः->flags |= SDL_गवाक्षः_METAL;
    }

    प्रत्यागम _this->Metal_CreateView(_this, गवाक्षः);
}

शून्य SDL_Metal_DestroyView(SDL_MetalView view)
{
    यदि (_this && view && _this->Metal_DestroyView) {
        _this->Metal_DestroyView(_this, view);
    }
}

शून्य *SDL_Metal_GetLayer(SDL_MetalView view)
{
    यदि (_this && _this->Metal_GetLayer) {
        CHECK_PARAM(!view) {
            SDL_InvalidParamError("view");
            प्रत्यागम रिक्त;
        }
        प्रत्यागम _this->Metal_GetLayer(_this, view);
    } अन्यथा {
        SDL_समुच्चयः_Error("Metal is not supported.");
        प्रत्यागम रिक्त;
    }
}

#यदि defined(SDL_VIDEO_DRIVER_X11) || defined(SDL_VIDEO_DRIVER_WAYLAND) || defined(SDL_VIDEO_DRIVER_EMSCRIPTEN)
ध्रुव वर्ण *SDL_GetCSSCursorName(SDL_SystemCursor id, ध्रुव वर्ण **fallback_name)
{
    // Reference: https://www.w3.org/TR/css-ui-4/#cursor
    // Also in: https://www.freedesktop.org/wiki/Specifications/cursor-spec/
    विकल्प (id) {
    पक्ष SDL_SYSTEM_CURSOR_DEFAULT:
        प्रत्यागम "default";

    पक्ष SDL_SYSTEM_CURSOR_TEXT:
        प्रत्यागम "text";

    पक्ष SDL_SYSTEM_CURSOR_WAIT:
        प्रत्यागम "wait";

    पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR:
        प्रत्यागम "crosshair";

    पक्ष SDL_SYSTEM_CURSOR_प्रगतिः:
        प्रत्यागम "progress";

    पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE:
        यदि (fallback_name) {
            // only a single arrow
            *fallback_name = "nw-resize";
        }
        प्रत्यागम "nwse-resize";

    पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE:
        यदि (fallback_name) {
            // only a single arrow
            *fallback_name = "ne-resize";
        }
        प्रत्यागम "nesw-resize";

    पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE:
        यदि (fallback_name) {
            *fallback_name = "col-resize";
        }
        प्रत्यागम "ew-resize";

    पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE:
        यदि (fallback_name) {
            *fallback_name = "row-resize";
        }
        प्रत्यागम "ns-resize";

    पक्ष SDL_SYSTEM_CURSOR_MOVE:
        यदि (fallback_name) {
            *fallback_name = "all-scroll";
        }
        प्रत्यागम "move";

    पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED:
        प्रत्यागम "not-allowed";

    पक्ष SDL_SYSTEM_CURSOR_POINTER:
        प्रत्यागम "pointer";

    पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE:
        प्रत्यागम "nw-resize";

    पक्ष SDL_SYSTEM_CURSOR_N_RESIZE:
        प्रत्यागम "n-resize";

    पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE:
        प्रत्यागम "ne-resize";

    पक्ष SDL_SYSTEM_CURSOR_E_RESIZE:
        प्रत्यागम "e-resize";

    पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE:
        प्रत्यागम "se-resize";

    पक्ष SDL_SYSTEM_CURSOR_S_RESIZE:
        प्रत्यागम "s-resize";

    पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE:
        प्रत्यागम "sw-resize";

    पक्ष SDL_SYSTEM_CURSOR_W_RESIZE:
        प्रत्यागम "w-resize";

    पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU:
        प्रत्यागम "context-menu";

    पक्ष SDL_SYSTEM_CURSOR_HELP:
        प्रत्यागम "help";

    पक्ष SDL_SYSTEM_CURSOR_CELL:
        प्रत्यागम "cell";

    पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        प्रत्यागम "vertical-text";

    पक्ष SDL_SYSTEM_CURSOR_ALIAS:
        प्रत्यागम "alias";

    पक्ष SDL_SYSTEM_CURSOR_COPY:
        प्रत्यागम "copy";

    पक्ष SDL_SYSTEM_CURSOR_NO_DROP:
        प्रत्यागम "no-drop";

    पक्ष SDL_SYSTEM_CURSOR_GRAB:
        प्रत्यागम "grab";

    पक्ष SDL_SYSTEM_CURSOR_GRABBING:
        प्रत्यागम "grabbing";

    पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE:
        प्रत्यागम "col-resize";

    पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE:
        प्रत्यागम "row-resize";

    पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL:
        यदि (fallback_name) {
            *fallback_name = "move";
        }
        प्रत्यागम "all-scroll";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_अन्तर्:
        प्रत्यागम "zoom-in";

    पक्ष SDL_SYSTEM_CURSOR_ZOOM_बहिर्गमनम्:
        प्रत्यागम "zoom-out";

    स्वभाव:
        प्रत्यागम "default";
    }
}
#यदि_अन्तः
